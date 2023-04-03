#include "Break.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "RobotSensor.h"
#include "skill/Factory.h"
#include <MotionControl/ControlModel.h>
#include <utils.h>
#include <WorldModel/DribbleStatus.h>
#include <MotionControl/ControlModel.h>
#include "GDebugEngine.h"
#include "TaskMediator.h"
#include "BestPlayer.h"
#include <string>
#include <ctime>
#include <algorithm>
#include <math.h>


//****************************/
/* 2022-05-01 pjt   beta 0.1    */
/* 2022-07-25 pjt   beta 0.2    */
/* 2022-10-26 pjt   beta 0.3    */
/* 2022-11-25 pjt   beta 1.0    suitable for penalty*/

/*****************************/
namespace {
    bool   DEBUG;

    //使用ini
    double SHOOT_ACCURACY;
    double MAX_ACC;
    double MAX_VEL;
    double MAX_ROT_ACC;
    double MAX_ROT_SPEED;
    double CHECK_OBSTCLE_DIST;
    double DRIBBLE_DIST;
    double COEF_NEARSCORE;
    double COEF_BLOCKSCORE;
    double COEF_DISTSCORE;
    bool safeMode;
    int maxFrared;

    const double DEBUG_TEXT_HIGH = 23 * 10;

    //视主机性能调节
    const int MOD_NUM = 2;
    const int ANGEL_MOD = 12;


    const int RADIUS = Param::Vehicle::V2::PLAYER_SIZE * 2;



}

int CBreak::index;
CGeoPoint CBreak::point[5];

CBreak::CBreak() {

    SHOOT_ACCURACY = paramManager->BREAK_SHOOT_ACCURACY;
    DEBUG = paramManager->BREAK_DEBUG;
    COEF_BLOCKSCORE = paramManager->COEF_BLOCKSCORE;
    COEF_DISTSCORE = paramManager->COEF_DISTSCORE;
    COEF_NEARSCORE = paramManager->COEF_NEARSCORE;

    CHECK_OBSTCLE_DIST = 1000;
    DRIBBLE_DIST = 80;
    safeMode = false;



    MAX_ACC = 100;
    MAX_VEL = 100;
    MAX_ROT_ACC = 20;
    MAX_ROT_SPEED = 2000;
  
    lastFrameposition = CGeoPoint(-9999, -9999);

}

void CBreak::plan(const CVisionModule* pVision) {

    if ((pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1)) {

        move_point = CGeoPoint(-9999 * 10, -9999 * 10);
        dribblePoint = pVision->OurPlayer(task().executor).Pos();
        isDribble = false;

    }

    //记录目前执行车号和最具威胁车号
    int vecNumber = task().executor;
    int oppNum = BestPlayer::Instance()->getTheirBestPlayer();
    int goalieNum = pVision->TheirGoalie();

    //由视觉和lua获得变量
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const PlayerVisionT& enemy = pVision->TheirPlayer(oppNum);
    const PlayerVisionT& goalie =pVision->TheirPlayer(goalieNum);
    const CGeoPoint passTarget = task().player.pos;

    double penaltyX=0.0;
    double penaltyY=0.0;



    //decoding flag

    bool isPenalty=task().player.flag&PlayerStatus::PENALTY_KICK;
    bool isSpin=task().player.flag&PlayerStatus::SPIN;

    //后续可考虑加入挑射
    bool isChip = false;

    // 传球精度控制（默认为SHOOT_ACCURACY)
    double precision = task().player.kickprecision > 0 ? task().player.kickprecision : SHOOT_ACCURACY;
    if(isPenalty)precision=3;

    //踢球相关向量和方向
    CVector me2Ball = ball.Pos() - me.Pos();
    CVector me2Enemy=enemy.Pos()-me.Pos();
    double deltax=me2Enemy.x();
    double deltay=me2Enemy.y();
    double me2enemy_dist = me2Enemy.mod();
    double alphaangle=fabs(Utils::Normalize(me2Ball.dir() - me2Enemy.dir())) ;
    bool criterion=Utils::Normalize(me2Ball.dir() - me2Enemy.dir())>0;
    const CVector me2target = passTarget - me.Pos();
    double finalDir = me2target.dir();

    bool canShoot = true;
    bool needBreakThrough = false;

    //当定点设置在禁区内时判定为进行射门
    double passpower = 100;
    bool shootGoal = Utils::InTheirPenaltyArea(passTarget, 0);

    double power = shootGoal ? 10000 : passpower;

    //以下是运行逻辑

    bool frared = (RobotSensor::Instance()->IsInfraredOn(vecNumber));// || isVisionHasBall(pVision, task().executor);


    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -425), ("Frared Status:" + to_string(frared)).c_str(), COLOR_YELLOW);

    if (!frared)
    {
        dribblePoint = me.Pos();

    }
    GDebugEngine::Instance()->gui_debug_x(dribblePoint, COLOR_RED);
    GDebugEngine::Instance()->gui_debug_arc(dribblePoint, 100, 0, 360, COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), ("Dribble Status:" + to_string(frared)).c_str(), COLOR_YELLOW);


    TaskT grabTask(task());


    grabTask.player.angle = finalDir;
   

    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 0), ("Dribble" + to_string(1)).c_str(), COLOR_YELLOW);
   /*if (pVision->Cycle() % 60 == 0) {
        move_point = calc_point(pVision, vecNumber, passTarget, dribblePoint, isChip, canShoot, needBreakThrough);
    }
    else {
        calc_point(pVision, vecNumber, passTarget, dribblePoint, isChip, canShoot, needBreakThrough);
    }*/
    CGeoPoint target = calc_point(pVision, vecNumber, passTarget, dribblePoint, isChip, canShoot, needBreakThrough);
    if (isSetPoint(pVision, point, target)) {
        move_point = target;
    }
    else if (pVision->Cycle() % 60 == 0) {
        move_point = target;
    }
    else {
        calc_point(pVision, vecNumber, passTarget, dribblePoint, isChip, canShoot, needBreakThrough);
    }
    index += 1;
    index %= 5;
    point[index]= target;
    for (int i = 0; i < 5; i++) {
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-400, -400+20*i), ("point[" + to_string(i) + "] (" + to_string(point[i].x()) + "," + to_string(point[i].y()) + ")").c_str(), COLOR_YELLOW);
    }
    if (DEBUG) GDebugEngine::Instance()->gui_debug_line(dribblePoint, move_point, COLOR_PURPLE);
    grabTask.player.max_acceleration=120;
    grabTask.player.max_deceleration=120;


    if (isPenalty)
    {
        cout<<"isPenalty"<<endl;
        penaltyX=me.Pos().x()+10.0;
        penaltyY=move_point.y()/*>0?-DRIBBLE_DIST:DRIBBLE_DIST*/;
        grabTask.player.pos=CGeoPoint(penaltyX,penaltyY);
        grabTask.player.max_acceleration=100;
        grabTask.player.max_deceleration=100;
        GDebugEngine::Instance()->gui_debug_x(CGeoPoint(penaltyX,penaltyY),COLOR_BLACK);
    }

    else
    {
        grabTask.player.pos = move_point;
    }


    GDebugEngine::Instance()->gui_debug_x(move_point, COLOR_RED);
    GDebugEngine::Instance()->gui_debug_x(passTarget, COLOR_RED);
    grabTask.player.flag |= PlayerStatus::ALLOW_DSS;
    setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(grabTask));


    if (DEBUG) {
        GDebugEngine::Instance()->gui_debug_line(me.Pos(), me.Pos() + Utils::Polar2Vector(1000 * 10, finalDir), COLOR_RED);
        GDebugEngine::Instance()->gui_debug_line(me.Pos(), me.Pos() + Utils::Polar2Vector(1000 * 10, me.Dir()), COLOR_BLUE);
    }
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -450), ("Canshoot:" + to_string(canShoot)).c_str(), COLOR_YELLOW);
    auto vel_vertical_target = std::sin(me.Vel().dir() - me2target.dir()) * me.Vel().mod();

    cout<<canShoot<<' '<<fabs(Utils::Normalize(me.Dir() - finalDir))<<' '<<precision * Param::Math::PI / 180.0 <<' '<< fabs(vel_vertical_target)<<endl;

    if (canShoot && fabs(Utils::Normalize(me.Dir() - finalDir)) < precision * Param::Math::PI / 180.0 && fabs(vel_vertical_target) < 50) {
        cout << "shoot!!!" << endl;
        DribbleStatus::Instance()->setDribbleCommand(vecNumber, 0);
        KickStatus::Instance()->setKick(vecNumber, power);//力度可调

    }
    DribbleStatus::Instance()->setDribbleCommand(vecNumber, 3);

    _lastCycle = pVision->Cycle();
    return CStatedTask::plan(pVision);
}


//execute
CPlayerCommand* CBreak::execute(const CVisionModule* pVision) {
    if (subTask()) {
        return subTask()->execute(pVision);
    }
    return NULL;
}
//视觉有球，保留
bool CBreak::isVisionHasBall(const CVisionModule* pVision, const int vecNumber) {
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const BallVisionT& ball = pVision->Ball();
    double visionJudgDist = 20;

    bool distVisionHasBall = CVector(me.Pos() - ball.Pos()).mod() <= visionJudgDist;

    bool dirVisionHasBall;
    double meDir = me.Dir();
    double me2Ball = (ball.Pos() - me.Pos()).dir();
    double meDir_me2Ball_Diff = abs(Utils::Normalize((meDir - me2Ball)));
    if (meDir_me2Ball_Diff < Param::Math::PI / 9.0) {
        dirVisionHasBall = true;
    }
    else {
        dirVisionHasBall = false;
    }
    bool isVisionPossession = dirVisionHasBall && distVisionHasBall;
    return false;
}

CGeoPoint CBreak::makeInCircle(const CGeoPoint& point, const CGeoPoint& center, double radius) {
    radius = DRIBBLE_DIST;
    CVector vec = point - center;
    double dist = vec.mod();
    vec = vec * radius / dist;

    return center + vec;
}
//算点

    //解耦路径规划与射门判断

CGeoPoint CBreak::calc_point(const CVisionModule* pVision, const int vecNumber, const CGeoPoint& target, const CGeoPoint& dribblePoint, const bool isChip, bool& canShoot, bool& needBreakThrough) {



        const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
        double max_straight_dist = 0;
        double to_target_dist = 9999 * 10;
        auto move_point = me.Pos();

        std::vector<CGeoPoint> enemy_points;
        CVector me2target = target - dribblePoint;


        //将在参与防守的敌方车入队
        for (int i = 0; i < 8; i++) {
            auto test_enemy = pVision->TheirPlayer(i);
            if (test_enemy.Valid() && !Utils::InTheirPenaltyArea(test_enemy.Pos(), 0))
                enemy_points.push_back(test_enemy.Pos());
        }



        if (DEBUG) {
            for (auto test_enemy : enemy_points) GDebugEngine::Instance()->gui_debug_arc(test_enemy, RADIUS, 0.0f, 360.0f, COLOR_BLACK);
        }


        //测试当前点,若当前点可直接射门，则直接返回
        CGeoPoint test_point = me.Pos();
        auto test_seg = CGeoSegment(test_point, target);
        canShoot = true;
        needBreakThrough = false;
        for (auto test_enemy : enemy_points) {
            auto projection = test_seg.projection(test_enemy);
            auto projection_dist = (projection - test_enemy).mod();
            auto to_projection_dist = (projection - test_point).mod();
            auto straight_dist = (test_enemy - test_point).mod();

            //if ((test_seg.IsPointOnLineOnSegment(projection) && (projection_dist/to_projection_dist) < (120/Param::Vehicle::V2::PLAYER_SIZE*2))) {
            if ((test_seg.IsPointOnLineOnSegment(projection) && projection_dist< Param::Vehicle::V2::PLAYER_SIZE)) {
                canShoot = false;
                needBreakThrough = true;
                break;
            }


        }
        if (canShoot)
        {
            //cout << "don't need dribble here";

            return test_point;
        }
        else
        {
            //当前点不行，选定若干个角度分别计算得分，取得分最高的点进行移动
            std::vector<double>point_score_list;
            std::vector<CGeoPoint>point_list;

            for (int i = -ANGEL_MOD; i < ANGEL_MOD; i++) {

                //生成test_point
                CVector vec = Utils::Polar2Vector(double(DRIBBLE_DIST),
                    Utils::Normalize(me2target.dir() + i * Param::Math::PI / ANGEL_MOD));

                CGeoPoint test_point = me.Pos() + vec;

                if((test_point-dribblePoint).mod()>DRIBBLE_DIST){
                    test_point = makeInCircle(test_point, dribblePoint, DRIBBLE_DIST);
                }
                if (DEBUG) GDebugEngine::Instance()->gui_debug_x(test_point, COLOR_YELLOW);

                if (!Utils::IsInField(test_point, 0))
                {
                    test_point = Utils::MakeInField(test_point, 0);
                    if (DEBUG) GDebugEngine::Instance()->gui_debug_x(test_point, COLOR_BLUE);
                }

                if (Utils::InTheirPenaltyArea(test_point, 0))
                {
                    test_point = Utils::MakeOutOfTheirPenaltyArea(test_point, 0);

                }
                bool tempflag=false;
                auto run_seg = CGeoSegment(test_point, me.Pos());

                for (auto test_enemy : enemy_points) {




                    auto projection = run_seg.projection(test_enemy);
                    if (run_seg.IsPointOnLineOnSegment(projection)){
                    double projection_dist = (projection - test_enemy).mod();
                    double to_projection_dist = (projection - test_point).mod();
                    double straight_dist = (test_enemy - test_point).mod();
                    if(projection_dist<40)
                    {
                        tempflag=true;
                        if (DEBUG) GDebugEngine::Instance()->gui_debug_x(test_point, COLOR_PURPLE);
                        break;
                    }}


                }
                if(tempflag)continue;




                auto test_seg = CGeoSegment(test_point, target);

                //测试点与目标点的距离

                //该指标与敌方车没有关系，越小越好
                double dist_score = (test_point - target).mod();

                //计算测试点处敌方车辆阻挡球路情况得分,越小越好
                double block_score = 0;
                //记录离测试点最近的敌方车辆距离得分，越小越好
                double near_score = 9999;
                for (auto test_enemy : enemy_points) {



                    auto projection = test_seg.projection(test_enemy);
                    double projection_dist = (projection - test_enemy).mod();
                    double to_projection_dist = (projection - test_point).mod();
                    double straight_dist = (test_enemy - test_point).mod();

                    near_score = (straight_dist <  near_score) ? (straight_dist) : near_score;
                    if (test_seg.IsPointOnLineOnSegment(projection)) {//不在连线上的车不考虑

                        block_score += projection_dist;


                    }
                }

                near_score = 1/(near_score);
                cout<<"dist_score"<<dist_score;
                cout<<"  block_score"<<block_score;
                cout<<"  near_score"<<near_score<<endl;
                double overall_score = COEF_BLOCKSCORE * block_score + COEF_DISTSCORE * dist_score + COEF_NEARSCORE * near_score;
                point_score_list.push_back(overall_score);
                point_list.push_back(test_point);
                GDebugEngine::Instance()->gui_debug_x(test_point, COLOR_YELLOW);








            }
            if(point_score_list.empty()||point_list.empty())
            {
                cout<<"error";
                return me.Pos();
            }
            else
            {
            int selected_pos = std::min_element(point_score_list.begin(),point_score_list.end())-point_score_list.begin();

            move_point = point_list[selected_pos];

            return move_point;
            }
        }




}
bool CBreak::isSetPoint(const CVisionModule* pVision, const CGeoPoint* point, const CGeoPoint& target) {
    int i = 0;
    double x = 0, y = 0;
    for (i = 0; i < 5; i++) {
        x += point[i].x();
        y += point[i].y();
    }
    x /= 5; y /= 5;
    if (sqrt(pow(x - target.x(), 2) + pow(y - target.y(), 2)) > 5)
        return true;
    else
        return false;

}
double CBreak::holdBallDir(const CVisionModule *pVision, int robotNum){
    static const int DIS_THRESHOLD = 800;

    // 计算多人包夹时的角度
    double finalAngle = 0;
    double coeff = 0;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    for(int i=0; i<Param::Field::MAX_PLAYER; i++){
        if(!pVision->TheirPlayer(i).Valid()) continue;
        if(pVision->TheirPlayer(i).Pos().dist(me.Pos()) > DIS_THRESHOLD) continue;
        const PlayerVisionT& enemy = pVision->TheirPlayer(i);
        CVector enemy2me = me.Pos() - enemy.Pos();
        double targetAngle = enemy2me.dir()/* > 0 ? 2*Param::Math::PI - enemy2me.dir() : -1*enemy2me.dir()*/;
        finalAngle += targetAngle/enemy2me.mod();
        coeff += 1/enemy2me.mod();
    }
    if(std::fabs(finalAngle) < 1e-4) return 1e8;

    finalAngle /= coeff;
    // 计算最佳距离
    double anotherAngle = finalAngle < Param::Math::PI ? finalAngle + Param::Math::PI : finalAngle - Param::Math::PI;
    double diff1 = 0, diff2 = 0;
    for(int i=0; i<Param::Field::MAX_PLAYER; i++){
        if(!pVision->TheirPlayer(i).Valid()) continue;
        if(pVision->TheirPlayer(i).Pos().dist(me.Pos()) > DIS_THRESHOLD) continue;
        const PlayerVisionT& enemy = pVision->TheirPlayer(i);
        CVector enemy2me = me.Pos() - enemy.Pos();
        double targetAngle = enemy2me.dir()/* > 0 ? 2*Param::Math::PI - enemy2me.dir() : -1*enemy2me.dir()*/;
        double d_angle1 = fabs(targetAngle-finalAngle) < Param::Math::PI ? fabs(targetAngle-finalAngle) : 2*Param::Math::PI - fabs(targetAngle-finalAngle);
        diff1 += d_angle1/enemy2me.mod();
        double d_angle2 = abs(targetAngle-anotherAngle) < Param::Math::PI ? fabs(targetAngle-anotherAngle) : 2*Param::Math::PI - fabs(targetAngle-anotherAngle);
        diff2 += d_angle2/enemy2me.mod();
    }
    if(diff1 > diff2)finalAngle = anotherAngle;         
    return finalAngle;
}


