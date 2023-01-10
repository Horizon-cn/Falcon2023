#include "collisiondetect.h"
#include "messageformat.h"
#include "staticparams.h"
#include "parammanager.h"
namespace {
    auto vpm = Owl::VParamManager::Instance();
}
CCollisionDetect::CCollisionDetect() {
    for (int i = 0; i < PARAM::ROBOTMAXID; i++) {
        our_collision[i] = -1;
        opp_collision[i] = -1;
    }
    current_check_num = 0;
    current_check_side = 0;
}
bool CCollisionDetect::ballIsOnEdge(CGeoPoint ball) {
    if(ball.x() < -LENGTH_THERESHOLD || ball.x() > LENGTH_THERESHOLD ||
            ball.y() < -WIDTH_THERESHOLD || ball.y() > WIDTH_THERESHOLD) return true;
    return false;
}

bool CCollisionDetect::ballCloseEnough2Analyze(int color) {
    Owl::ReceiveVisionMessage _pVision = GlobalData::Instance()->maintain[0];
    bool found = false;
    for (int i = 0; i < _pVision.robotSize[color]; i++)
        if (_pVision.ball[0].pos.dist(_pVision.robot[color][i].pos) < DETECT_DIST) {
            found = true;
            break;
        }
    return found;
}

void CCollisionDetect::ballRobotCollision(Owl::ReceiveVisionMessage & result) {
    //first test near ball
    int OurTouchNum = -1, TheirTouchNum = -1;
    for (int roboId = 0; roboId < PARAM::ROBOTMAXID; roboId++) {
        bool foundBlue = true, foundYellow = true;
        for (int frame = 0; frame > -NEAR_VECHILE_MIN_FRAME; frame--) {
            bool foundBlueCar = false, foundYellowCar = false;
            Owl::Ball ball = GlobalData::Instance()->maintain[frame].ball[0];
            for (int i = 0; i < GlobalData::Instance()->maintain[frame].robotSize[PARAM::BLUE]; i++)
                if (GlobalData::Instance()->maintain[frame].robot[PARAM::BLUE][i].id == roboId
                        && GlobalData::Instance()->maintain[frame].robot[PARAM::BLUE][i].pos.dist(ball.pos) >= 85
                        && GlobalData::Instance()->maintain[frame].robot[PARAM::BLUE][i].pos.dist(ball.pos) <= 125)
                    foundBlueCar = true;
            for (int i = 0; i < GlobalData::Instance()->maintain[frame].robotSize[PARAM::YELLOW]; i++)
                if (GlobalData::Instance()->maintain[frame].robot[PARAM::YELLOW][i].id == roboId
                        && GlobalData::Instance()->maintain[frame].robot[PARAM::YELLOW][i].pos.dist(ball.pos) >= 85
                        && GlobalData::Instance()->maintain[frame].robot[PARAM::YELLOW][i].pos.dist(ball.pos) <= 125)
                    foundYellowCar = true;
            if (!foundBlueCar) foundBlue = false;
            if (!foundYellowCar) foundYellow = false;
        }
        if (foundBlue) {
            OurTouchNum = roboId;
        }
        if (foundYellow) {
            TheirTouchNum = roboId;
        }
    }

    if (OurTouchNum != -1 && TheirTouchNum == -1) {
        result.ball[0].ball_state_machine.ballState = _touched;
        GlobalData::Instance()->lastTouch = PARAM::BLUE * PARAM::ROBOTMAXID + OurTouchNum;
        return;
        //std::cout<<"the ball touch OUR robot:num:"<<OurTouchNum<<" id:"<<GlobalData::Instance()->maintain[LinePoint[j]].robot[PARAM::BLUE][OurTouchNum].id<<std::endl;
    } else if (TheirTouchNum != -1 && OurTouchNum == -1) {
        result.ball[0].ball_state_machine.ballState = _touched;
        GlobalData::Instance()->lastTouch = PARAM::YELLOW * PARAM::ROBOTMAXID + TheirTouchNum;
        //std::cout<<"the ball touch THEIR robot:num:"<<TheirTouchNum<<" id:"<<GlobalData::Instance()->maintain[LinePoint[j]].robot[PARAM::YELLOW][TheirTouchNum].id<<std::endl;
        return;
    } else if (OurTouchNum != -1 && TheirTouchNum != -1) {
        //争球
        result.ball[0].ball_state_machine.ballState = _struggle;
        GlobalData::Instance()->lastTouch = -1;
        //std::cout << "CANNOT decide the ball between OUR player no." << OurTouchNum << " and THEIR player No." << TheirTouchNum << std::endl;
        return;
    }

    //use split and merge algorithm
    LinePoint[1] = -MAX_FRAME_NUM + 1;
    LinePoint[2] = 0;
    PointN = 2;
    while (true) {
        int pi = 1, maxi = 1, i = -MAX_FRAME_NUM + 1;
        double maxDis = -1;
        while (pi < PointN) {
            const auto &p1 = GlobalData::Instance()->maintain[LinePoint[pi]];
            const auto &p2 = GlobalData::Instance()->maintain[LinePoint[pi + 1]];
            const auto& q = GlobalData::Instance()->maintain[i];
            CGeoPoint p1BallPos(p1.ball[0].pos.x(), p1.ball[0].pos.y());
            CGeoPoint p2BallPos(p2.ball[0].pos.x(), p2.ball[0].pos.y());
            CGeoPoint qBallPos(q.ball[0].pos.x(), q.ball[0].pos.y());
            CGeoSegment PassLine(p1BallPos, p2BallPos);
            double d = qBallPos.dist(PassLine.projection(qBallPos));
            //------------------IMPOTANT------------
            //CGeoSegment PassLine(p1.BallPos, p2.BallPos);
            //d = q.BallPos.dist(PassLine.projection(q.BallPos));
            //std::cout << "ball" << i << " @" << qBallPos<< "\t with d:" << d << std::endl;
            if (d > maxDis && d > SPLIT_THRESHOLD && i != LinePoint[pi] && i != LinePoint[pi + 1]) {
                maxi = i;
                maxDis = d;
            }
            if (i == LinePoint[pi + 1]) pi++;
            i++;
        }
        //std::cout << "-----------------\n";
        if (maxi == 1) break;
        for (i = PointN; i > 0; i--) {
            if (LinePoint[i] < maxi) break;
            LinePoint[i + 1] = LinePoint[i];
        }
        PointN++;
        LinePoint[i + 1] = maxi;
    }
    if (PointN > 2) {
        int OurTouchNum = -1, TheirTouchNum = -1, j = PointN - 1;
        double OurTouchDis = 200.0, TheirTouchDis = 200.0;
        //std::cout << "found PointN=" << PointN << "\tball pos" << GlobalData::Instance()->maintain[LinePoint[j]].ball[0].pos.x << std::endl;
        CGeoPoint ballpos(GlobalData::Instance()->maintain[LinePoint[j]].ball[0].pos);
        for (int i = 0; i < GlobalData::Instance()->maintain[LinePoint[j]].robotSize[PARAM::BLUE]; i++) {
            CGeoPoint tempos(GlobalData::Instance()->maintain[LinePoint[j]].robot[PARAM::BLUE][i].pos);
            if (ballpos.dist(tempos) < OurTouchDis) {
                OurTouchDis = ballpos.dist(tempos);
                OurTouchNum = i;
            }
        }
        for (int i = 0; i < GlobalData::Instance()->maintain[LinePoint[j]].robotSize[PARAM::YELLOW]; i++) {
            CGeoPoint tempos(GlobalData::Instance()->maintain[LinePoint[j]].robot[PARAM::YELLOW][i].pos);
            if (ballpos.dist(tempos) < TheirTouchDis) {
                TheirTouchDis = ballpos.dist(tempos);
                TheirTouchNum = i;
            }
        }
        if (OurTouchNum != -1 && ((TheirTouchNum != -1 && OurTouchDis <= TheirTouchDis - 5) || TheirTouchNum == -1)) {
            result.ball[0].ball_state_machine.ballState = _touched;
            //LastTouch = 1;
            GlobalData::Instance()->lastTouch = PARAM::BLUE * PARAM::ROBOTMAXID + GlobalData::Instance()->maintain[LinePoint[j]].robot[PARAM::BLUE][OurTouchNum].id;
            //std::cout<<"the ball touch OUR robot:num:"<<OurTouchNum<<" id:"<<GlobalData::Instance()->maintain[LinePoint[j]].robot[PARAM::BLUE][OurTouchNum].id<<std::endl;
        } else if (TheirTouchNum != -1 && ((OurTouchNum != -1 && TheirTouchDis <= OurTouchDis - 5) || OurTouchNum == -1)) {
            result.ball[0].ball_state_machine.ballState = _touched;
            //LastTouch = 2;
            GlobalData::Instance()->lastTouch = PARAM::YELLOW * PARAM::ROBOTMAXID + GlobalData::Instance()->maintain[LinePoint[j]].robot[PARAM::YELLOW][TheirTouchNum].id;
            //std::cout<<"the ball touch THEIR robot:num:"<<TheirTouchNum<<" id:"<<GlobalData::Instance()->maintain[LinePoint[j]].robot[PARAM::YELLOW][TheirTouchNum].id<<std::endl;
        } else if (OurTouchNum != -1 && TheirTouchNum != -1 && abs(OurTouchDis - TheirTouchDis) <= 5) {
            //争球
            result.ball[0].ball_state_machine.ballState = _struggle;
            //LastTouch = 0;
            GlobalData::Instance()->lastTouch = -1;
            //std::cout << "CANNOT decide the ball between OUR player no." << OurTouchNum << " and THEIR player No." << TheirTouchNum << std::endl;
        } else if (ballIsOnEdge(GlobalData::Instance()->maintain[LinePoint[j]].ball[0].pos)) {
            //LastTouch = 3;
            GlobalData::Instance()->lastTouch = -1;
            //std::cout << "the ball touch WALL" << std::endl;
        }
    }
}

void  CCollisionDetect::visionAlart() {


}

bool CCollisionDetect::robotsCollision(Owl::ReceiveVisionMessage& result) //两小车相撞
{
    if (current_check_side == 0) {
        // 检查我方的车
        for (int i = 0; i < PARAM::ROBOTMAXID; i++) { //依次检测对方小车
            if (result.robot[PARAM::YELLOW][i].valid) { //对方图像有效，i为对方小车序号
                if (opp_collision[i] != -1 && opp_collision[i] != current_check_num) //current_check_num我方特定小车序号
                    continue; // 不是和我撞
                if (opp_collision[i] != -1 && opp_collision[i] == current_check_num) {  //对手i号车与我方current_check_num号车碰撞
                    our_collision[current_check_num] = i; //和我方相撞的对手车号
                    break; // 检测过了，是和我撞
                }

                // 还没检测过是否碰撞
                const CGeoPoint& oppPos = result.robot[PARAM::YELLOW][i].pos;
                const CGeoPoint& ourPos = result.robot[PARAM::BLUE][current_check_num].pos;
                if (oppPos.dist(ourPos) < vpm->robotsCollisionDist) { //距离小于球员最大尺寸，认为发生碰撞
                    our_collision[current_check_num] = i;
                    opp_collision[i] = current_check_num;
                    break;
                }
            }
        }
        /*if ( our_collision[current_check_num] > 0 )
            cout<<"our:"<<current_check_num<<" collide with their "<<our_collision[current_check_num]<<endl;*/
        return our_collision[current_check_num] > 0; //true则有碰撞
    }

    else {
        // 检查对方车
        for (int i = 0; i < PARAM::ROBOTMAXID; i++){
            if (result.robot[PARAM::BLUE][i].valid){
                if ( our_collision[i] != -1 && our_collision[i] != current_check_num )
                    continue; // 不是和我撞
                if ( our_collision[i] != -1 && our_collision[i] == current_check_num){
                    opp_collision[current_check_num] = i;
                    break; // 检测过了，是和我撞
                }

                // 还没检测过
                const CGeoPoint& oppPos = result.robot[PARAM::YELLOW][current_check_num].pos;
                const CGeoPoint& ourPos = result.robot[PARAM::BLUE][i].pos;
                if ( ourPos.dist(oppPos) < vpm->robotsCollisionDist ){
                    opp_collision[current_check_num] = i;
                    our_collision[i] = current_check_num;
                    break;
                }
            }
        }

        return opp_collision[current_check_num] > 0;
    }
}

void CCollisionDetect::setCheckNum(int side, int robotID)
{
    current_check_side = side;
    current_check_num = robotID;
}

void CCollisionDetect::clearLastResult(int side)
{
    for (int i = 0; i < PARAM::ROBOTMAXID; i++) {
        side? our_collision[i] = -1 : opp_collision[i] = -1;
    }
}
