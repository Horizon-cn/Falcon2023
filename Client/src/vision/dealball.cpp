#include "dealball.h"
#include "globaldata.h"
#include "collisiondetect.h"
#include "chipsolver.h"
#include "matrix2d.h"
#include "simulator.h"
#include <iostream>
#include "communicator.h"

#define MAX_BALL_PER_FRAME 200
#define MIN_FILT_DIST 150

namespace {
    auto opm = Owl::OParamManager::Instance();
    auto vpm = Owl::VParamManager::Instance();
    auto sipm = Owl::SIParamManager::Instance();
    long long min(long long a, long long b ) {
        if (a < b) return a;
        else return b;
    }
}
/**
 * @brief CDealball
 */
CDealBall::CDealBall() {
    //upPossible = 1.0 / vpm->ballMinBelieveFrame;
    downPossible = 0.05;
    upPossible = 0.1;
    decidePossible = vpm->ballMinBelieveFrame * upPossible;
    lastBall.pos.setX(0);
    lastBall.pos.setY(0);
    initPosCov = 100; posMeasErr = 20; posModelErr = 0.2;
    ballKalmanFilter = PosFilter(initPosCov, posMeasErr, posModelErr);
}
/**
 * @brief CDealball::posDist
 * @param pos1
 * @param pos2
 * @return
 */
double CDealBall::posDist(CGeoPoint pos1, CGeoPoint pos2) {
    return std::sqrt((pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) + (pos1.y() - pos2.y()) * ((pos1.y() - pos2.y())));
}

bool CDealBall::isValidInfo(Owl::Ball ball) {
    if (abs(ball.pos.x()) < opm->field_length / 2 + opm->field_wall_dist && abs(ball.pos.y()) < opm->field_width / 2 + opm->field_wall_dist)
        return true;
    else
        return false;
}

bool CDealBall::ballInRobot(CGeoPoint ballPos) {
    if(infraredcnt == 1 || ballState) return false;
    Owl::ReceiveVisionMessage maintain = GlobalData::Instance()->maintain[0];
    for (int team = 0; team < PARAM::TEAMS; team++) {
        for (int id = 0; id < PARAM::ROBOTMAXID; id++){
            if(maintain.robotIndex[team][id] == -1) continue;
            if (maintain.robot[team][maintain.robotIndex[team][id]].pos.dist(ballPos) <= sipm->CenterFromKicker)
                return true;
        }
    }
    return false;
}

bool CDealBall::ballNearVechile(Owl::Ball curentBall, double dist) {
    bool answer = false;
    Owl::ReceiveVisionMessage result = GlobalData::Instance()->maintain[-1];
    for (int i = 0; i < result.robotSize[PARAM::BLUE]; i++) {
        if (result.robot[PARAM::BLUE][i].pos.dist(curentBall.pos) <= dist ) answer = true;
    }
    for (int i = 0; i < result.robotSize[PARAM::YELLOW]; i++)
        if (result.robot[PARAM::YELLOW][i].pos.dist(curentBall.pos) < dist) answer = true;
    return answer;
}

double CDealBall::calculateWeight(int camID, CGeoPoint ballPos) {
    Owl::SingleCamera camera = GlobalData::Instance()->cameraMatrix[camID];
    if (ballPos.x() > camera.leftedge.max && ballPos.x() < camera.rightedge.max &&
            ballPos.y() > camera.downedge.max && ballPos.y() < camera.upedge.max)
        return 1;
    else if (ballPos.x() < camera.leftedge.max && ballPos.x() > camera.leftedge.min)
        return abs(ballPos.x() - camera.leftedge.min) / abs(camera.leftedge.max - camera.leftedge.min);
    else if (ballPos.x() > camera.rightedge.max && ballPos.x() < camera.rightedge.min)
        return abs(ballPos.x() - camera.rightedge.min) / abs(camera.rightedge.max - camera.rightedge.min);
    else if (ballPos.y() < camera.downedge.max && ballPos.y() > camera.downedge.min)
        return abs(ballPos.y() - camera.downedge.min) / abs(camera.downedge.max - camera.downedge.min);
    else if (ballPos.y() > camera.upedge.max && ballPos.y() < camera.upedge.min)
        return abs(ballPos.y() - camera.upedge.min) / abs(camera.upedge.max - camera.upedge.min);
    else return 1e-8;//0.01 to deal with can see out of border situation
}

void CDealBall::init() {
    _cycle = GlobalData::Instance()->processBall.cycle() + 1;
    result.init();
    FPS = getFPS();
    dt = 1 / sipm->DesiredFPS;
    //dt = 1 / FPS;
    //dt1 = 1 / FPS;
    //qDebug()<<"dt1"<<dt1;

    for(int i = 0; i < PARAM::BALLNUM; i++)
        for(int j = 0; j < opm->total_cameras; j++)
            ballSequence[i][j].fill(-32767, -32767);
    for (int i = 0; i < opm->total_cameras; i++) {
        if (GlobalData::Instance()->cameraUpdate[i]) {//old result has only one ball, only need to add new ball
            for(int j = 0; j < GlobalData::Instance()->camera[i][0].ballSize; j++) {
                //currentball = GlobalData::Instance()->camera[i][0].ball[j];
                if (!isValidInfo(GlobalData::Instance()->camera[i][0].ball[j])) continue;
                simBall = GlobalData::Instance()->camera[i][0].ball[j];
                if (vpm->projection && opm->isSimulation && !touchGround(simBall)){
                    project(i, simBall);
                    result.addBall(simBall.pos, simBall.raw, simBall.height, i);
                }
                else
                    result.addBall(GlobalData::Instance()->camera[i][0].ball[j].pos, GlobalData::Instance()->camera[i][0].ball[j].raw, 0, i);
            }
        }
    }

//    if (result.ballSize == 0) validBall = false;
//    else validBall = true;
}

void CDealBall::mergeBall() {
    int i, j;
    actualBallNum = 0;
    for ( i = 0; i < result.ballSize; i++) {
        bool found = false;
        for (j = 0; j < actualBallNum; j++) {
            for (int id = 0; id < opm->total_cameras; id++)
                if (posDist(result.ball[i].pos, ballSequence[j][id].pos) < vpm->ballMergeDist) {
                    found = true;
                    break;
                }
            if (found) break;
        }
        if (found) ballSequence[j][result.ball[i].cameraID].fill(result.ball[i]); //close balls have the same id, one camera has 'j' balls
        else ballSequence[actualBallNum++][result.ball[i].cameraID].fill(result.ball[i]); //too far from other balls to add a new possibility
    }

    result.init(); //validBall = false,not see a ball
    //if (!validBall && GlobalData::Instance()->maintain[-1].ball[0].ball_state_machine.ballState == _struggle)
    //    result.addBall(GlobalData::Instance()->maintain[-1].ball[0]);
    //else {
        for (i = 0; i < actualBallNum; i++) { //many balls, merge by cameras
            double weight = 0;
            CGeoPoint average(0, 0);
            //CGeoPoint averageRawPos(0,0);
            CGeoPoint rawPos(0,0);
            Owl::RawInfo r(0,0,0,0);
            for(j = 0; j < opm->total_cameras; j++) {
                if (ballSequence[i][j].pos.x() > -30000 && ballSequence[i][j].pos.y() > -30000) {
                    Owl::SingleCamera camera = GlobalData::Instance()->cameraMatrix[j];
                    double _weight;
                    _weight = calculateWeight(j, ballSequence[i][j].pos);
                    _weight = std::pow(posDist(ballSequence[i][j].pos, GlobalData::Instance()->cameraMatrix[camera.id].campos) / 1000.0, -2.0);
                    weight += _weight;
                    average.setX(average.x() + ballSequence[i][j].pos.x() * _weight);
                    average.setY(average.y() + ballSequence[i][j].pos.y() * _weight);
                    //averageRawPos.setX(averageRawPos.x() + ballSequence[i][j].rawPos.x() * _weight);
                    //averageRawPos.setY(averageRawPos.y() + ballSequence[i][j].rawPos.y() * _weight);
                    r.fill(ballSequence[i][j].raw);
                }
            }
            //if (weight != 0) result.addBall(average.x() / weight, average.y() / weight);
            //if (weight != 0) result.addBall(average.x() / weight, average.y() / weight, averageRawPos.x() /weight, averageRawPos.y() /weight);
            if (weight != 0) result.addBall(average.x() / weight, average.y() / weight, r);
        } 
    //}
}

void CDealBall::choseBall() { 
    float dis = 32767; //32767
    int id = -1;
    for (int i = 0; i < result.ballSize; i++) {
        if (result.ball[i].pos.dist(lastBall.pos) < dis) {// && isValidInfo(result.ball[i])) {
            dis = result.ball[i].pos.dist(lastBall.pos); //the nearest to last ball
            id = i; //choose a ball from serval balls
        }
    }
    if (result.ballSize > 0) { //&& dis < min(2000, MAX_BALL_PER_FRAME * (_cycle - lastFrame))) {
    //if (id != -1) {
        lastBall = result.ball[id];
        lastFrame = _cycle;
        validBall = 1; //true;
    }
    else {
        //if(GlobalData::Instance()->maintain[0].ball[0].ball_state_machine.ballState == _struggle)
        //    lastBall = GlobalData::Instance()->maintain[0].ball[0];
        //else {
            lastBall.pos = lastBall.pos + lastBall.velocity * dt + lastBall.accelerate * pow(dt, 2) / 2;
        //}
        //checkInfrared(GlobalData::Instance()->maintain[0].ball[0]);
        lastBall.raw = result.ball[0].raw;
        validBall = 0; //false;
        /**if (lastPossible >= decidePossible)
            if (_cycle - lastFrame >= 20)
                lastPossible -= downPossible;
            else
                lastPossible += upPossible;
        else lastPossible -= decidePossible;**/
    }
    //checkInfrared(GlobalData::Instance()->maintain[0].ball[0]);
    //if (lastPossible > 1.0) lastPossible = 1.0;
    //if (lastPossible < 0.0) lastPossible = 0.0;
    //if (lastPossible >= decidePossible) {
        result.init();
        result.addBall(lastBall);
    //} 

    //possiblity
    /**if (lastBall.pos.dist(result.ball[id].pos) < min(2000, MAX_BALL_PER_FRAME * (_cycle - lastFrame))) {
        lastBall = result.ball[id];
        lastFrame = _cycle;
        lastPossible = 1;
        currentPossible = 0;
    } else if(currentBall.pos.dist(result.ball[id].pos) < min(2000, MAX_BALL_PER_FRAME * (_cycle - currentFrame))) {
        currentBall = result.ball[id];
        currentFrame = _cycle;
        currentPossible += upPossible;
        lastPossible -= downPossible;
    } else {
        currentBall = result.ball[id];
        currentFrame = _cycle;
        currentPossible = upPossible;
        lastPossible -= downPossible;
    }
    result.init();
    if (lastPossible >= currentPossible)
        result.addBall(lastBall);
    else {
        result.addBall(currentBall);
        lastBall = currentBall;
        lastFrame = currentFrame;
        lastPossible = currentPossible;
        currentPossible = 0;
    }**/
}

//void CDealBall::checkInfrared(ReceiveVisionMessage& result) {
void CDealBall::checkInfrared(Owl::Ball ball) {/**
    infraredcnt = 0;
    Owl::Ball infraredBall;
    Owl::ReceiveVisionMessage maintain = GlobalData::Instance()->maintain[0];
    double Threshold_v = 60, Threshold_h = 75;
    for (int team = 0; team < PARAM::TEAMS; team ++) {
        for (int id = 0; id < PARAM::ROBOTMAXID && infraredcnt < 2; id++){
            if (GlobalData::Instance()->robotInformation[team][id].infrared) {            
                if (maintain.robotIndex[team][id] == -1) continue;
                CGeoPoint botPos = maintain.robot[team][maintain.robotIndex[team][id]].pos;
                double botDir =  maintain.robot[team][maintain.robotIndex[team][id]].angle;
                CVector angleVector = CVector(cos(botDir), sin(botDir));
                infraredBall.pos = ( botPos + angleVector * sipm->CenterFromKicker );
                
                CVector ballPosVector = ball.pos - infraredBall.pos;
                double verticalDist = ballPosVector.x()*angleVector.x()+ballPosVector.y()*angleVector.y(),
                       horizontalDist = abs(ballPosVector.x()*angleVector.y()-ballPosVector.y()*angleVector.x());
                if (validBall) {
                    Threshold_v = 14;
                    Threshold_h = 18;
                } 
                if(verticalDist>=0 && verticalDist<Threshold_v && horizontalDist<Threshold_h) infraredcnt++;

                // bool tooFarFromVisionBall = false;
                // for (int visionball = 0; visionball < result.ballSize; visionball++) {
                //     if(infraredBall.pos.dist(result.ball[visionball].pos)>150) {
                //         tooFarFromVisionBall = true;
                        //GlobalData::Instance()->robotInformation[team][id].infrared = false;
                //     }
                // }
                // if((result.ballSize > 0 && !tooFarFromVisionBall) || result.ballSize == 0) {
                //     infraredcnt ++;
                // }
            }
        }
    }
    //qDebug()<<"cnt"<<infraredcnt;
    if (infraredcnt == 1 ) {
        //result.init();
        //result.addBall(infraredBall); // todo: needs sao convert
        lastBall = infraredBall;
        validBall = 2;
//      qDebug()<<"add infrared";
    }**/

    Owl::ReceiveVisionMessage maintain = GlobalData::Instance()->maintain[0];
    for (int team = 0; team < PARAM::TEAMS; team++) {
        for (int id = 0; id < PARAM::ROBOTMAXID; id++) {
            if (GlobalData::Instance()->robotInformation[team][id].infrared) {
                if (maintain.robotIndex[team][id] == -1) continue; // 车视觉丢失，无法检验
                Owl::Robot robot = maintain.robot[team][maintain.robotIndex[team][id]];
                if (validBall) {	// 球看到，作红外信号假象检查，因为通讯可能会丢
                    if (ball.pos.dist(robot.pos) > sipm->RobotRadius + 2 * sipm->BallRadius + 50) {
                        GlobalData::Instance()->robotInformation[team][id].infrared = false;
                        ZCommunicator::Instance()->sendCommand(team, id);
                    }
                }
                else {				// 球看不到，根据红外信号纠正球的位置
                    ball.pos = robot.pos + CVector((sipm->RobotRadius + sipm->BallRadius) * cos(robot.angle), 
                        (sipm->RobotRadius + sipm->BallRadius) * sin(robot.angle));
                    ball.velocity = robot.velocity.vxy;
                    validBall = 2;
                    break;
                }
            }
        }
    }
}

void CDealBall::run() {
    //result.init();
    // TODO fill_n
    //for(int i = 0; i < PARAM::BALLNUM; i++)
    //    for(int j = 0; j < opm->total_cameras; j++)
    //        ballSequence[i][j].fill(-32767, -32767);

    init();
    //CVector ballTravel ;
    //if (validBall) {
        mergeBall();
        choseBall();
        //checkInfrared(result);

        //qDebug("deal ball here");
        //result.addBall(simBall);
        //lastBall = simBall;
        //lastFrame = _cycle;
        //lastPossible = 1;
        //currentPossible = 0;
    //} 
    /**else {
        CVector lastVel = GlobalData::Instance()->maintain[0].ball[0].velocity / sipm->DesiredFPS;

        if (GlobalData::Instance()->maintain[0].ball[0].velocity.mod() >= vpm->v_switch)
            ballTravel = lastVel + lastVel.unit() * (vpm->acc_slide / sipm->DesiredFPS / sipm->DesiredFPS / 2 ) ;
        else if (GlobalData::Instance()->maintain[0].ball[0].velocity.mod() <= 1e-8)
            ballTravel = CVector(0, 0);
        else
            ballTravel = lastVel +  lastVel.unit() * (vpm->acc_roll / sipm->DesiredFPS / sipm->DesiredFPS / 2 );
        //result.addBall(GlobalData::Instance()->maintain[0].ball[0].pos + ballTravel);
        //result.addBall(GlobalData::Instance()->maintain[0].ball[0].pos + ballTravel, GlobalData::Instance()->maintain[0].ball[0].rawPos );
        result.addBall(GlobalData::Instance()->maintain[0].ball[0].pos + ballTravel, GlobalData::Instance()->maintain[0].ball[0].raw);

        lastBall = GlobalData::Instance()->maintain[0].ball[0];
        lastPossible = 1;
    }
//    qDebug()<<"maintain"<<GlobalData::Instance()->maintain[0].ball[0].pos.x();
//    qDebug()<<"visionball"<<result.ball[0].pos.x();

    checkInfrared(result);
    if (infraredcnt != 1 ) {
        //result.addBall(GlobalData::Instance()->maintain[0].ball[0].pos + ballTravel);
    }**/
//    qDebug()<<"ball"<<result.ballSize<<result.ball[0].valid<<result.ball[0].pos.x();
    GlobalData::Instance()->processBall.push(result);
}

//void CDealBall::updateVel(const Matrix2d tempMatrix, ReceiveVisionMessage& result) {
void CDealBall::updateVel(Owl::ReceiveVisionMessage& result) {
    bool isFar = false;
    //timeStamp += 1 / sipm->DesiredFPS;

    if(!ballKalmanFilter.isInit()) {
        ballKalmanFilter.initState(result.ball[0].pos, CVector(0, 0));
    }
    //Ball Statemachine
    if (CollisionDetect::Instance()->ballCloseEnough2Analyze(PARAM::BLUE) ||
        CollisionDetect::Instance()->ballCloseEnough2Analyze(PARAM::YELLOW) ||
        CollisionDetect::Instance()->ballIsOnEdge(result.ball[0].pos))
    //离车近//
    {
        if(GlobalData::Instance()->ballrecords.validSize() > 0) {
            chipsolver.reset();
        }

        //判断碰撞//
        CollisionDetect::Instance()->ballRobotCollision(result);
        //ball kalmanfilter FOLLOW
        ballKalmanFilter.follow(result.ball[0].pos);
    } else {
    //离车远//
        isFar = true;
    }  
    //ball kalmanfilter
    //double dt = timeStamp - ballKalmanFilter.lastTimestamp;
    //ballKalmanFilter.lastTimestamp = timeStamp;
    ballKalmanFilter.setTransitionMat(dt);
    //ballKalmanFilter.predict2(result.ball[0].accelerate);
    ballKalmanFilter.predict();
    ballKalmanFilter.update2(result.ball[0].pos);
    result.ball[0].pos = ballKalmanFilter.postEstimatedPos();
    result.ball[0].velocity = ballKalmanFilter.postEstimatedVel();
    result.ball[0].accelerate = (result.ball[0].velocity - GlobalData::Instance()->maintain[0].ball[0].velocity) / dt;

    //result.ball[0].fill(result.ball[0].pos.x(), result.ball[0].pos.y(), 0, result.ball[0].velocity);

    ballState = 0;
    if(isFar) {
        CVector3 realpos;
        //result.ball[0].predict_pos = chipsolver.dealresult(realpos); TODO:disable here for improving FPS
        result.ball[0].predict_pos = CGeoPoint(0,0);
        CGeoLine line(result.ball[0].pos, GlobalData::Instance()->maintain[-7].ball[0].pos);
        CGeoPoint middlePoint(GlobalData::Instance()->maintain[-4].ball[0].pos);
        if(line.projection(middlePoint).dist(middlePoint) > 1.0 )
            if (line.projection(middlePoint).dist(middlePoint) > CHIP_DIS &&
                result.ball[0].pos.dist(GlobalData::Instance()->maintain[0].ball[0].pos) < 20) {
//                  std::cout << "FUCK!!! ball dist=" << result.ball[0].pos.dist(GlobalData::Instance()->maintain[0].ball[0].pos) << std::endl;
                result.ball[0].ball_state_machine.ballState = _chip_pass;
                ballState = 1;
//                  result.ball[0].fill(realpos.x(), realpos.y(), realpos.z(), CVector(0, 0)); ///TO TEST!!!
            } else {
                result.ball[0].ball_state_machine.ballState = _flat_pass;
                ballState = 0;
            }
    }

    if(!isValidInfo(result.ball[0]) || result.ball[0].velocity.mod()>vpm->inValidSpeed) {
        result.ball[0] = lastBall;
        result.ball[0].accelerate = result.ball[0].velocity = CVector(0,0);
    }
    else if(opm->isSimulation && vpm->detectBallInRobot && ballInRobot(result.ball[0].pos)) {
        result.ball[0].pos = result.ball[0].pos + -GlobalData::Instance()->maintain[0].ball[0].velocity*dt;
        Simulator::Instance()->setBall(result.ball[0].pos.x()*0.001, result.ball[0].pos.y()*0.001, 0, 0);
        result.ball[0].velocity = -GlobalData::Instance()->maintain[0].ball[0].velocity;
        result.ball[0].accelerate = CVector(0,0);
        lastBall = result.ball[0];
        validBall = 0;
    }
    else lastBall = result.ball[0];

    checkInfrared(lastBall); // 红外特殊处理

/**
    // 1.进行Kalman滤波，估计球的位置以及球速//
    CGeoPoint filtPoint (tempMatrix(0, 0), tempMatrix(1, 0));
    CVector ballVel(tempMatrix(2, 0)* sipm->DesiredFPS, tempMatrix(3, 0)*sipm->DesiredFPS);
    ballVel = ballVel / lostFrame;
    result.ball[0].fill(filtPoint.x(), filtPoint.y(), 0, ballVel);
    // 2.延时补偿，根据延时帧率将位置和速度进行修正//
    for( int i = 0; i < vpm->total_lated_frame; ++i ) {
        //thisCycle.SetPos(thisCycle.Pos() + thisCycle.Vel() / sipm->DesiredFPS);
        CVector uniVec = ballVel / (ballVel.mod() + 1.0);
        if ( ballVel.mod() > vpm->ball_delc_change_point )
            ballVel = ( uniVec * ( ballVel.mod() - vpm->ball_fast_dec / sipm->DesiredFPS ));
        else if ( ballVel.mod() > 50 )
            ballVel = ( uniVec * ( ballVel.mod() - vpm->ball_slow_dec / sipm->DesiredFPS ));
        else {
            ballVel = (CVector(0, 0));
        }
    }
    // 3.估计球速大小及方向，特别是方向
    if(lastPossible > 0.3) { //MAYBE FIX
        // 计算球速方向:
        double movingDirection = ballVel.dir();
        _lastValidDir = movingDirection;
        ballVel.setVector(ballVel.mod()*std::cos(movingDirection), ballVel.mod()*std::sin(movingDirection));
    } else {
        double predictDir = _lastValidDir;
        double velMod = ballVel.mod();
        if (velMod < 0.1) {
            velMod = 0.1;
        }
        ballVel.setVector(velMod * std::cos(predictDir), velMod * std::sin(predictDir));
    }

    if (infraredcnt == 1 ) {
        ballVel = CVector(0, 0);
    }
    result.ball[0].fill(result.ball[0].pos.x(), result.ball[0].pos.y(), 0, ballVel);
//    qDebug()<<"speed"<<ballVel.x()<<ballVel.y();
    if(validBall) lostFrame = 1;
    else lostFrame ++;
**/
}

bool CDealBall::touchGround(const Owl::Ball &ball) {
    return fabs(ball.height - sipm->BallRadius) < 10;
}

void CDealBall::project(int camId, Owl::Ball &ball) {
    Owl::SingleCamera cam = GlobalData::Instance()->cameraMatrix[camId];
    CVector toCamDist = ball.pos - cam.campos;
    double toCamHeight = fabs(cam.height - ball.height);
    double proj_x = cam.campos.x() + (toCamDist.x() /  toCamHeight) * cam.height,
           proj_y = cam.campos.y() + (toCamDist.y() / toCamHeight) * cam.height;
//    qDebug()<<toCamHeight<<toCamDist.x()<<ball.pos.x()<<proj_x;
    ball.pos = CGeoPoint(proj_x, proj_y);
}
