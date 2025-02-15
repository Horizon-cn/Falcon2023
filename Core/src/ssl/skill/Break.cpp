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
#include "defenceNew/DefenceInfoNew.h"
#include <string>
#include <ctime>
#include <algorithm>
#include <math.h>

#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>

#define OURPLAYER_NUM	16
#define THEIRPLAYER_NUM 16
#define BALL_NUM		1

#ifdef ENABLE_CUDA
extern "C" int break_calc_with_gpu(float* target_point_cpu, int target_point_num, float* pos_info_cpu, int pos_info_num, int angle_mod, int dist_mod, float* results, float* vis_points, bool isPenalty);
#else
int break_calc_with_gpu(float* target_point_cpu, int target_point_num, float* pos_info_cpu, int pos_info_num, int angle_mod, int dist_mod, float* results, float* vis_points, bool isPenalty) { return 0; }
#endif

std::string date_time(std::time_t posix)
{
    char buf[20]; // big enough for 2015-07-08 10:06:51\0
    std::tm tp = *std::localtime(&posix);
    return { buf, std::strftime(buf, sizeof(buf), "%F %T", &tp) };
}

std::string stamp()
{
    using namespace std;
    using namespace std::chrono;

    // get absolute wall time
    auto now = system_clock::now();

    // find the number of milliseconds
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // build output string
    std::ostringstream oss;
    oss.fill('0');

    // convert absolute time to time_t seconds
    // and convert to "date time"
    oss << date_time(system_clock::to_time_t(now));
    oss << '.' << setw(3) << ms.count();

    return oss.str();
}

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
    double MAX_ROT_VEL;
    double CHECK_OBSTCLE_DIST;
    double DRIBBLE_DIST;
    double COEF_NEARSCORE;
    double COEF_BLOCKSCORE;
    double COEF_DISTSCORE;
    double OBSTACLE_RADIUS;
    bool safeMode;
    int maxFrared;

    const double DEBUG_TEXT_HIGH = 23 * 10;

    //视主机性能调节
    const int MOD_NUM = 15;
    const int ANGEL_MOD = 20;


    const int RADIUS = Param::Vehicle::V2::PLAYER_SIZE * 2;



}



CBreak::CBreak() {

    SHOOT_ACCURACY = paramManager->BREAK_SHOOT_ACCURACY;
    DEBUG = paramManager->BREAK_DEBUG;
    COEF_BLOCKSCORE = paramManager->COEF_BLOCKSCORE;
    COEF_DISTSCORE = paramManager->COEF_DISTSCORE;
    COEF_NEARSCORE = paramManager->COEF_NEARSCORE;
    OBSTACLE_RADIUS = paramManager->BREAK_OBSTACLE_RADIUS;
    MAX_ACC = paramManager->BREAK_ACC;
    MAX_VEL = paramManager->BREAK_VEL;
    MAX_ROT_ACC = paramManager->BREAK_ROT_ACC;
    MAX_ROT_VEL = paramManager->BREAK_ROT_VEL;

    CHECK_OBSTCLE_DIST = 1000;
    DRIBBLE_DIST = 70.0;
    safeMode = false;


    lastFrameposition = CGeoPoint(-9999, -9999);

    running_index = 0;


}

void CBreak::plan(const CVisionModule* pVision) {

    if ((pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1)) {

        move_point = CGeoPoint(-9999 * 10, -9999 * 10);
        if(task().player.pos.x() == -1000)
            dribblePoint = pVision->OurPlayer(task().executor).Pos();
        isDribble = false;
        running_index = 0;

    }
    if (task().player.pos.x() != -1000)
        dribblePoint = task().player.pos;//pVision->OurPlayer(task().executor).Pos();
    string time1 = stamp();
    //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 0), ("Dribble Status:" + time1).c_str(), COLOR_YELLOW);

    //记录目前执行车号和最具威胁车号
    int vecNumber = task().executor;
    int oppNum = DefenceInfoNew::Instance()->getBestBallChaser();
    int goalieNum = pVision->TheirGoalie();

    //由视觉和lua获得变量
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const PlayerVisionT& enemy = pVision->TheirPlayer(oppNum);
    const PlayerVisionT& goalie = pVision->TheirPlayer(goalieNum);

    CGeoPoint passTarget = CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0);
    bool shootGoal = task().player.needkick; // Utils::InTheirPenaltyArea(passTarget, 0); // 不在门里，是传球 // Utils::InTheirPenaltyArea(passTarget, 0);

    if (shootGoal) {
        float corrected_parameter = (fabs(me.VelY()) * 0.2 + 5 > 20) ? 20 : fabs(me.VelY()) * 0.2 + 5;
        CGeoPoint TargetUp = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2 + 5 + corrected_parameter);
        CGeoPoint TargetDown = CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2 - 5 - corrected_parameter);
        passTarget = TargetUp;
        double thetaUp = (TargetUp - ball.Pos()).dir();
        double thetaDown = (TargetDown - ball.Pos()).dir();
        if (me.Dir() < thetaUp) passTarget = TargetDown;
        else if (me.Dir() > thetaDown)passTarget = TargetUp;
    }
    double penaltyX = 0.0;
    double penaltyY = 0.0;



    //decoding flag

    bool isPenalty = task().player.flag & PlayerStatus::PENALTY_KICK;
    bool isSpin = task().player.flag & PlayerStatus::SPIN;

    //后续可考虑加入挑射
    bool isChip = false;

    //踢球相关向量和方向
    CVector me2Ball = ball.Pos() - me.Pos();
    CVector me2Enemy = enemy.Pos() - me.Pos();
    double deltax = me2Enemy.x();
    double deltay = me2Enemy.y();
    double me2enemy_dist = me2Enemy.mod();
    double alphaangle = fabs(Utils::Normalize(me2Ball.dir() - me2Enemy.dir()));
    bool criterion = Utils::Normalize(me2Ball.dir() - me2Enemy.dir()) > 0;
    //const CVector me2target = passTarget - me.Pos();
    const CVector me2target = CGeoPoint(Param::Field::PITCH_LENGTH / 2 + 15, 0) - me.Pos();
    double finalDir = me2target.dir();

    bool canShoot = true;
    bool needBreakThrough = false;

    //当定点设置在禁区内时判定为进行射门
    bool isChipKick = task().player.ischipkick;
    double passpower = task().player.kickpower; // 100;
    //bool shootGoal = (passTarget.x() == Param::Field::PITCH_LENGTH / 2 && fabs(passTarget.y()) <= Param::Field::GOAL_WIDTH / 2); // 不在门里，是传球 // Utils::InTheirPenaltyArea(passTarget, 0);

    double power = shootGoal ? Param::Rule::MAX_BALL_SPEED : passpower;
    power = power * 10;
    //以下是运行逻辑

    bool frared = (RobotSensor::Instance()->IsInfraredOn(vecNumber));// || isVisionHasBall(pVision, task().executor);


    //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -425), ("Frared Status:" + to_string(frared)).c_str(), COLOR_YELLOW);

    //if (!frared)
    if (BallStatus::Instance()->getBallPossession(true, vecNumber) == 0)
    {
        if (task().player.pos.x() == -1000)
            //dribblePoint = task().player.pos;
            dribblePoint = me.Pos();

    }
    GDebugEngine::Instance()->gui_debug_x(dribblePoint, COLOR_RED);  // 不是这个
    GDebugEngine::Instance()->gui_debug_arc(dribblePoint, 100, 0, 360, COLOR_RED);
    //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), ("Dribble Status:" + to_string(frared)).c_str(), COLOR_YELLOW);


    TaskT grabTask(task());
    ////////
    if (canScore(pVision, vecNumber, OBSTACLE_RADIUS, me.Dir()))
        grabTask.player.angle = me.Dir();
    else////added here
        if (task().player.needkick)
        grabTask.player.angle = finalDir;
    else
        grabTask.player.angle = task().player.angle;

    //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 0), ("Dribble" + to_string(1)).c_str(), COLOR_YELLOW);
   /*if (pVision->Cycle() % 60 == 0) {
        move_point = calc_point(pVision, vecNumber, passTarget, dribblePoint, isChip, canShoot, needBreakThrough);
    }
    else {
        calc_point(pVision, vecNumber, passTarget, dribblePoint, isChip, canShoot, needBreakThrough);
    }*/
    clock_t begin, end;
    begin = clock();
    CGeoPoint target = calc_point(pVision, vecNumber, passTarget, dribblePoint, isChip, canShoot, needBreakThrough, isPenalty);
    end = clock();

    //std::cout << "best break point calc time (GPU): " << double(end - begin) / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
    if (isSetPoint(pVision, point, me.Pos())) {
        move_point = target;
    }
    else if (pVision->Cycle() % 5 == 0) {
        move_point = target;
    }

    running_index += 1;
    running_index %= 20;
    point[running_index] = me.Pos();
    /*
    for (int i = 0; i < 5; i++) {
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-400, -400+20*i), ("point[" + to_string(i) + "] (" + to_string(point[i].x()) + "," + to_string(point[i].y()) + ")").c_str(), COLOR_YELLOW);
    }
    */
    if (DEBUG) GDebugEngine::Instance()->gui_debug_line(dribblePoint, move_point, COLOR_PURPLE);

    grabTask.player.max_acceleration = MAX_ACC;
    grabTask.player.max_deceleration = MAX_ACC;
    grabTask.player.max_rot_acceleration = MAX_ROT_ACC;
    grabTask.player.max_rot_speed = MAX_ROT_VEL;



    if (isPenalty)
    {
        //cout<<"isPenalty"<<endl;
        grabTask.player.pos = target;
        grabTask.player.max_acceleration = MAX_ACC;
        grabTask.player.max_deceleration = MAX_ACC;
        GDebugEngine::Instance()->gui_debug_x(CGeoPoint(penaltyX, penaltyY), COLOR_BLACK);
    }

    else
        /////////
        if (canScore(pVision, vecNumber, OBSTACLE_RADIUS, me.Dir()))
        {
            grabTask.player.pos = me.Pos();
        }
        else//added here
    {
        grabTask.player.pos = move_point;
    }


    GDebugEngine::Instance()->gui_debug_x(move_point, COLOR_RED); // 不是这个
    GDebugEngine::Instance()->gui_debug_x(passTarget, COLOR_RED); // 是这个
    grabTask.player.flag |= PlayerStatus::ALLOW_DSS;

    auto breakvector = move_point - me.Pos();


    setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(grabTask));


    if (DEBUG) {
        GDebugEngine::Instance()->gui_debug_line(me.Pos(), me.Pos() + Utils::Polar2Vector(1000 * 10, finalDir), COLOR_RED);
        GDebugEngine::Instance()->gui_debug_line(me.Pos(), me.Pos() + Utils::Polar2Vector(1000 * 10, me.Dir()), COLOR_BLUE);
    }
    bool dirok = canScore(pVision, vecNumber, OBSTACLE_RADIUS, me.Dir());
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -425), ("Canshoot:" + to_string(dirok)).c_str(), COLOR_YELLOW);
    auto vel_vertical_target = std::sin(me.Vel().dir() - me2target.dir()) * me.Vel().mod();


    DribbleStatus::Instance()->setDribbleCommand(vecNumber, 3);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -425), ("Canscore:" + to_string(dirok)).c_str(), COLOR_YELLOW);


    if (shootGoal && dirok) {
        KickStatus::Instance()->setKick(vecNumber, power);//力度可调
    }
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






CGeoPoint CBreak::calc_point(const CVisionModule* pVision, const int vecNumber, const CGeoPoint& target, const CGeoPoint& dribblePoint, const bool isChip, bool& canShoot, bool& needBreakThrough, bool& isPenalty) {



    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    double max_straight_dist = 0;
    double to_target_dist = 9999 * 10;
    auto move_point = me.Pos();

    std::vector<CGeoPoint> enemy_points;
    CVector me2target = target - dribblePoint;


    //将在参与防守的敌方车入队
    for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
        auto test_enemy = pVision->TheirPlayer(i);
        //if (test_enemy.Valid() && !Utils::InTheirPenaltyArea(test_enemy.Pos(), 0))
            //enemy_points.push_back(test_enemy.Pos());
        if (test_enemy.Valid())
            enemy_points.push_back(test_enemy.Pos());
    }



    if (DEBUG) {
        for (auto test_enemy : enemy_points) GDebugEngine::Instance()->gui_debug_arc(test_enemy, RADIUS, 0.0f, 360.0f, COLOR_BLACK);
    }


    //测试当前点,若当前点可直接射门，则直接返回
    CGeoPoint test_point = me.Pos();
    auto test_seg = CGeoSegment(pVision->Ball().Pos(), target); // 球门终点到我的距离
    canShoot = true;
    needBreakThrough = false;
    for (auto test_enemy : enemy_points) { //枚举一个敌人
        auto projection = test_seg.projection(test_enemy);  //算敌人到线段投影
        float projection_dist = max((projection - pVision->Ball().Pos()).mod() - Param::Vehicle::V2::PLAYER_SIZE, 0.0);  //球到投影点的距离
        auto to_projection_dist = (projection - test_point).mod();  //另一半距离
        auto straight_dist = (test_enemy - test_point).mod(); //敌人到我的距离
        auto Opp2Projection = (projection - test_enemy).mod();
        //float nearEnemyThreshold = task().player.ispass ? 2 : 15 * Param::Math::PI / 180.0;

        //float nearEnemyThreshold = task().player.ispass ? 2 : 15 * Param::Math::PI / 180.0;
        float nearEnemyThreshold = task().player.needkick ? 5.5 : 3.5;


        //if ((test_seg.IsPointOnLineOnSegment(projection) && ((projection_dist/to_projection_dist) < (15*Param::Math::PI/180.0))||(to_projection_dist<15&&projection_dist<15))) {
        //if ((test_seg.IsPointOnLineOnSegment(projection) && ((projection_dist / to_projection_dist) < (nearEnemyThreshold))  )) {
        /*if ((test_seg.IsPointOnLineOnSegment(projection) && projection_dist< Param::Vehicle::V2::PLAYER_SIZE)) {*/


        if ((test_seg.IsPointOnLineOnSegment(projection) && ((projection_dist / fabs((Opp2Projection - Param::Vehicle::V2::PLAYER_SIZE))) > (nearEnemyThreshold)))) {


            canShoot = false;
            needBreakThrough = true;
            break;
        }
    }
    bool dirok = canScore(pVision, vecNumber, OBSTACLE_RADIUS, me.Dir());
    double finalDir = me2target.dir();
    //if (canShoot)
    if (task().player.needkick && dirok)
    {
        //cout << "don't score" << endl;
        return test_point;
    }
    else if (isPenalty)
    {
        int _palyer_pos_num = 6;
        int pos_num = 2 + 1 + 2 + 1 + 2 + 2 + OURPLAYER_NUM * _palyer_pos_num + THEIRPLAYER_NUM * _palyer_pos_num;
        int pos_size = pos_num * sizeof(float);
        int target_point_num = 15;
        float corrected_parameter = (fabs(me.VelY()) * 0.2 + 5 > 20) ? 20 : fabs(me.VelY()) * 0.2 + 5;
        float target_step = (Param::Field::GOAL_WIDTH - 2 * corrected_parameter) / (target_point_num - 1);
        CGeoPoint target_point = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2 + corrected_parameter);
        int target_size = 2 * target_point_num * sizeof(float);
        int results_size = 3 * target_point_num * sizeof(float);


        float* pos_info = (float*)malloc(pos_size); // 用于存储计算后的结果
        float* target_info = (float*)malloc(target_size);
        float* results = (float*)malloc(results_size);
        float* vis_points = (float*)malloc(3 * (ANGEL_MOD * 2 - 1) * (MOD_NUM - 1) * sizeof(float));

        if (pos_info == nullptr || target_info == nullptr || results == nullptr) {
            return test_point;
        }

        pos_info[0] = dribblePoint.x();
        pos_info[1] = dribblePoint.y();
        pos_info[2] = DRIBBLE_DIST;
        pos_info[3] = me.Pos().x();
        pos_info[4] = me.Pos().y();
        pos_info[5] = me.Dir();
        pos_info[6] = pVision->Ball().Pos().x();
        pos_info[7] = pVision->Ball().Pos().y();
        pos_info[8] = pVision->Ball().VelX();
        pos_info[9] = pVision->Ball().VelY();
        // 己方机器人信息
        int our_start_idx = 10;    // 在数组中开始存储的位置
        float* our_player_info = pos_info + our_start_idx;
        for (int i = 0; i < OURPLAYER_NUM; i++) {
            if (pVision->OurPlayer(i).Valid()) {
                const PlayerVisionT& ourPlayer = pVision->OurPlayer(i);
                our_player_info[_palyer_pos_num * i] = 1.0;
                our_player_info[_palyer_pos_num * i + 1] = ourPlayer.X();
                our_player_info[_palyer_pos_num * i + 2] = ourPlayer.Y();
                our_player_info[_palyer_pos_num * i + 3] = ourPlayer.Dir();
                our_player_info[_palyer_pos_num * i + 4] = ourPlayer.VelX();
                our_player_info[_palyer_pos_num * i + 5] = ourPlayer.VelY();
            }
            else {
                for (int j = 0; j < _palyer_pos_num; j++) {
                    our_player_info[_palyer_pos_num * i + j] = 0.0;
                }
            }
        }
        // 敌方机器人信息
        int their_start_idx = 10 + _palyer_pos_num * OURPLAYER_NUM; // 在数组中开始存储的位置
        float* their_player_info = pos_info + their_start_idx;
        for (int i = 0; i < THEIRPLAYER_NUM; i++) {
            if (pVision->TheirPlayer(i).Valid()) {
                const PlayerVisionT& theirPlayer = pVision->TheirPlayer(i);
                their_player_info[_palyer_pos_num * i] = 1.0;
                their_player_info[_palyer_pos_num * i + 1] = theirPlayer.X();
                their_player_info[_palyer_pos_num * i + 2] = theirPlayer.Y();
                their_player_info[_palyer_pos_num * i + 3] = theirPlayer.Dir();
                their_player_info[_palyer_pos_num * i + 4] = theirPlayer.VelX();
                their_player_info[_palyer_pos_num * i + 5] = theirPlayer.VelY();
            }
            else {
                for (int j = 0; j < _palyer_pos_num; j++) {
                    their_player_info[_palyer_pos_num * i + j] = 0.0;
                }
            }
        }

        // 生成目标点信息：
        for (int i = 0; i < target_point_num; i++) {
            target_info[2 * i] = target_point.x();
            target_info[2 * i + 1] = target_point.y() + i * target_step;
            CGeoPoint now_place = CGeoPoint(target_info[2 * i], target_info[2 * i + 1]);
            for (int player_num = 0; player_num < Param::Field::MAX_PLAYER; player_num++) {
                if (pVision->TheirPlayer(player_num).Valid()) {
                    if (pVision->TheirPlayer(player_num).Pos().dist(now_place) < OBSTACLE_RADIUS && i) {
                        target_info[2 * i] = target_info[2 * (i - 1)];
                        target_info[2 * i + 1] = target_info[2 * (i - 1) + 1];

                    }
                }
            }
        }
        // 这里会返回值，如果是0则可能GPU计算出现问题，建议切换为CPU去计算
        break_calc_with_gpu(target_info, target_point_num, pos_info, pos_num, ANGEL_MOD, MOD_NUM, results, vis_points, isPenalty);

        //std::cout << "break start find best point" << std::endl;
        float best_score = 2147483647;
        float best_idx = -1;
        CGeoPoint best_point(250, 0);
        for (int i = 0; i < target_point_num; i++) {
            CGeoPoint target_point(target_info[2 * i], target_info[2 * i + 1]);
            float current_score = results[3 * i];
            CGeoPoint move_point(results[3 * i + 1], results[3 * i + 2]);

            if (move_point.x() > Param::Field::PITCH_LENGTH / 2) {
                continue;
            }
            // 换成大场之后这个参数要改！！！！！！！！！！！！！！！！！！！！！！！！！
            // 
            //std::cout << "i: " << i << " | current score: " << current_score << " | move_point: " << move_point << std::endl;
            if (best_score > current_score || i == 0) {
                best_score = current_score;
                best_point = move_point;
                best_idx = i;
            }
        }
        //std::cout << "best point: " << best_point << " | best idx: " << best_idx << " | best score: " << best_score << std::endl;
        if (DEBUG) {
            for (int i = 0; i < target_point_num; i++) {
                CGeoPoint target_point(target_info[2 * i], target_info[2 * i + 1]);
                float current_score = results[3 * i];
                CGeoPoint move_point(results[3 * i + 1], results[3 * i + 2]);
                int color = COLOR_YELLOW;
                if (i == best_idx) {
                    color = COLOR_GREEN;
                }
                GDebugEngine::Instance()->gui_debug_x(target_point, color);
                GDebugEngine::Instance()->gui_debug_x(move_point, color);
                GDebugEngine::Instance()->gui_debug_line(target_point, move_point, color);
            }

        }
        if (DEBUG) {
            for (int i = 0; i < (ANGEL_MOD * 2 - 1) * (MOD_NUM - 1); i++) {
                //CGeoPoint cur_point(vis_points[3 * i + 1], vis_points[3 * i + 2]);
                //std::cout << vis_points[3 * i] << " ";
                //GDebugEngine::Instance()->gui_debug_x(cur_point, COLOR_GREEN);
            }

        }
        /*best_point.x() / fabs(best_point.x()) *
        best_point.y() / fabs(best_point.y()) *
*/
        //if (best_point == CGeoPoint(0, 0) || best_point == me.Pos())
            //return best_point = me.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER, Utils::Normalize(me.Dir()));

        /*
        if (abs(best_point.y()) > Param::Field::PENALTY_AREA_WIDTH / 2 + 30 || abs(best_point.x()) < (Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - 30)) {
            if (abs(best_point.y()) > Param::Field::PENALTY_AREA_WIDTH / 2 + 30)
                best_point.setY((Param::Field::PENALTY_AREA_WIDTH / 2 + 30));
            if (abs(best_point.x()) < (Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - 30))
                best_point.setX((Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - 30));
        }
        if ((best_point - dribblePoint).mod() > DRIBBLE_DIST) {  // dribblePoint是中心点还是当前点？？？？
            best_point = makeInCircle(best_point, dribblePoint, DRIBBLE_DIST);
        }*/

        GDebugEngine::Instance()->gui_debug_x(best_point, COLOR_ORANGE);
        return best_point;
    }
    else if (task().player.needkick)  // 需要进行射门
    {
        //std::cout << "============break calc with gpu===============" << std::endl;
        // 使用GPU
        int _palyer_pos_num = 6;
        int pos_num = 2 + 1 + 2 + 1 + 2 + 2 + OURPLAYER_NUM * _palyer_pos_num + THEIRPLAYER_NUM * _palyer_pos_num;
        int pos_size = pos_num * sizeof(float);
        int target_point_num = 15;
        float corrected_parameter = (fabs(me.VelY()) * 0.2 + 5 > 20) ? 20 : fabs(me.VelY()) * 0.2 + 5;
        float target_step = (Param::Field::GOAL_WIDTH - 2 * corrected_parameter) / (target_point_num - 1);
        CGeoPoint target_point = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2 + corrected_parameter);
        int target_size = 2 * target_point_num * sizeof(float);
        int results_size = 3 * target_point_num * sizeof(float);


            float* pos_info = (float*)malloc(pos_size); // 用于存储计算后的结果
            float* target_info = (float*)malloc(target_size);
            float* results = (float*)malloc(results_size);
            float* vis_points = (float*)malloc(3 * (ANGEL_MOD * 2 - 1) * (MOD_NUM - 1) * sizeof(float));

        if (pos_info == nullptr || target_info == nullptr || results == nullptr) {
            return test_point;
        }

        pos_info[0] = dribblePoint.x();
        pos_info[1] = dribblePoint.y();
        pos_info[2] = DRIBBLE_DIST;
        pos_info[3] = me.Pos().x();
        pos_info[4] = me.Pos().y();
        pos_info[5] = me.Dir();
        pos_info[6] = pVision->Ball().Pos().x();
        pos_info[7] = pVision->Ball().Pos().y();
        pos_info[8] = pVision->Ball().VelX();
        pos_info[9] = pVision->Ball().VelY();
        // 己方机器人信息
        int our_start_idx = 10;    // 在数组中开始存储的位置
        float* our_player_info = pos_info + our_start_idx;
        for (int i = 0; i < OURPLAYER_NUM; i++) {
            if (pVision->OurPlayer(i).Valid()) {
                const PlayerVisionT& ourPlayer = pVision->OurPlayer(i);
                our_player_info[_palyer_pos_num * i] = 1.0;
                our_player_info[_palyer_pos_num * i + 1] = ourPlayer.X();
                our_player_info[_palyer_pos_num * i + 2] = ourPlayer.Y();
                our_player_info[_palyer_pos_num * i + 3] = ourPlayer.Dir();
                our_player_info[_palyer_pos_num * i + 4] = ourPlayer.VelX();
                our_player_info[_palyer_pos_num * i + 5] = ourPlayer.VelY();
            }
            else {
                for (int j = 0; j < _palyer_pos_num; j++) {
                    our_player_info[_palyer_pos_num * i + j] = 0.0;
                }
            }
        }
        // 敌方机器人信息
        int their_start_idx = 10 + _palyer_pos_num * OURPLAYER_NUM; // 在数组中开始存储的位置
        float* their_player_info = pos_info + their_start_idx;
        for (int i = 0; i < THEIRPLAYER_NUM; i++) {
            if (pVision->TheirPlayer(i).Valid()) {
                const PlayerVisionT& theirPlayer = pVision->TheirPlayer(i);
                their_player_info[_palyer_pos_num * i] = 1.0;
                their_player_info[_palyer_pos_num * i + 1] = theirPlayer.X();
                their_player_info[_palyer_pos_num * i + 2] = theirPlayer.Y();
                their_player_info[_palyer_pos_num * i + 3] = theirPlayer.Dir();
                their_player_info[_palyer_pos_num * i + 4] = theirPlayer.VelX();
                their_player_info[_palyer_pos_num * i + 5] = theirPlayer.VelY();
            }
            else {
                for (int j = 0; j < _palyer_pos_num; j++) {
                    their_player_info[_palyer_pos_num * i + j] = 0.0;
                }
            }
        }

        // 生成目标点信息：
        for (int i = 0; i < target_point_num; i++) {
            target_info[2 * i] = target_point.x();
            target_info[2 * i + 1] = target_point.y() + i * target_step;
            CGeoPoint now_place = CGeoPoint(target_info[2 * i], target_info[2 * i + 1]);
            for (int player_num = 0; player_num < Param::Field::MAX_PLAYER; player_num++) {
                if (pVision->TheirPlayer(player_num).Valid()) {
                    if (pVision->TheirPlayer(player_num).Pos().dist(now_place) < OBSTACLE_RADIUS && i) {
                        target_info[2 * i] = target_info[2 * (i - 1)];
                        target_info[2 * i + 1] = target_info[2 * (i - 1) + 1];

                    }
                }
            }
        }
        // 这里会返回值，如果是0则可能GPU计算出现问题，建议切换为CPU去计算
        break_calc_with_gpu(target_info, target_point_num, pos_info, pos_num, ANGEL_MOD, MOD_NUM, results, vis_points, isPenalty);

        //std::cout << "break start find best point" << std::endl;
        float best_score = 2147483647;
        float best_idx = -1;
        CGeoPoint best_point(250, 0);
        for (int i = 0; i < target_point_num; i++) {
            CGeoPoint target_point(target_info[2 * i], target_info[2 * i + 1]);
            float current_score = results[3 * i];
            CGeoPoint move_point(results[3 * i + 1], results[3 * i + 2]);

            if (move_point.x() > Param::Field::PITCH_LENGTH / 2) {
                continue;
            }
            // 换成大场之后这个参数要改！！！！！！！！！！！！！！！！！！！！！！！！！
            // 
            //std::cout << "i: " << i << " | current score: " << current_score << " | move_point: " << move_point << std::endl;
            if (best_score > current_score || i == 0) {
                best_score = current_score;
                best_point = move_point;
                best_idx = i;
            }
        }
        //std::cout << "best point: " << best_point << " | best idx: " << best_idx << " | best score: " << best_score << std::endl;
        if (DEBUG) {
            for (int i = 0; i < target_point_num; i++) {
                CGeoPoint target_point(target_info[2 * i], target_info[2 * i + 1]);
                float current_score = results[3 * i];
                CGeoPoint move_point(results[3 * i + 1], results[3 * i + 2]);
                int color = COLOR_YELLOW;
                if (i == best_idx) {
                    color = COLOR_GREEN;
                }
                GDebugEngine::Instance()->gui_debug_x(target_point, color);
                GDebugEngine::Instance()->gui_debug_x(move_point, color);
                GDebugEngine::Instance()->gui_debug_line(target_point, move_point, color);
            }

        }
        if (DEBUG) {
            for (int i = 0; i < (ANGEL_MOD * 2 - 1) * (MOD_NUM - 1); i++) {
                //CGeoPoint cur_point(vis_points[3 * i + 1], vis_points[3 * i + 2]);
                //std::cout << vis_points[3 * i] << " ";
                //GDebugEngine::Instance()->gui_debug_x(cur_point, COLOR_GREEN);
            }

        }
        /*best_point.x() / fabs(best_point.x()) *
        best_point.y() / fabs(best_point.y()) *
*/
        if (best_point == CGeoPoint(0, 0) || best_point == me.Pos())
            return best_point = me.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER, Utils::Normalize(me.Dir()));

        /*
        if (abs(best_point.y()) > Param::Field::PENALTY_AREA_WIDTH / 2 + 30 || abs(best_point.x()) < (Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - 30)) {
            if (abs(best_point.y()) > Param::Field::PENALTY_AREA_WIDTH / 2 + 30)
                best_point.setY((Param::Field::PENALTY_AREA_WIDTH / 2 + 30));
            if (abs(best_point.x()) < (Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - 30))
                best_point.setX((Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - 30));
        }
        
            }*/
        if ((best_point - dribblePoint).mod() > DRIBBLE_DIST)   // dribblePoint是中心点还是当前点？？？？
                    best_point = makeInCircle(best_point, dribblePoint, DRIBBLE_DIST);
        GDebugEngine::Instance()->gui_debug_x(best_point, COLOR_ORANGE);
        return best_point;
    }


    else  //breaking 
    {
        CGeoPoint best_point(250, 0);
        //cout << "calc_here" << endl;
        double dist = 1000;
        int num = 0;
        for (int player_num = 0; player_num < Param::Field::MAX_PLAYER; player_num++) {
            if (pVision->TheirPlayer(player_num).Valid()) {
                if (pVision->TheirPlayer(player_num).Pos().dist(me.Pos()) < dist) {
                    dist = pVision->TheirPlayer(player_num).Pos().dist(me.Pos());
                    num = player_num;
                }
            }
        }
        int x_min = max((int)(me.X() - DRIBBLE_DIST) + 1, -(int)(Param::Field::PITCH_LENGTH / 2)), x_max = min((int)(me.X() + DRIBBLE_DIST) - 1, (int)(Param::Field::PITCH_LENGTH / 2));
        int y_min = max((int)(me.Y() - DRIBBLE_DIST) + 1, -(int)(Param::Field::PITCH_WIDTH / 2)), y_max = min((int)(me.Y() + DRIBBLE_DIST) - 1, (int)(Param::Field::PITCH_WIDTH / 2));
        double dist_score_dribble, to_goal_score_dribble, final_score = 10000000, y_score, total_score;
        double para_dist, para_goal, para_y = 0.4;
        /*
        if (dist >= 80 || pVision->TheirPlayer(num).X() < me.X())
            para_dist = -0.2, para_goal = 1.2;
        else
            para_dist = -1.5, para_goal = 0.3;
        */
        para_dist = -0.2 - dist / 60; para_goal = 1.2 - dist / 80;
        for (int x_test = x_min; x_test <= x_max; x_test += 10)
        {
            for (int y_test = y_min; y_test <= y_max; y_test += 10)
            {
                CGeoPoint now_point = CGeoPoint(x_test, y_test);
                dist_score_dribble = 0;
                y_score = 0;
                for (int player_num = 0; player_num < Param::Field::MAX_PLAYER; player_num++) {
                    if (pVision->TheirPlayer(player_num).Valid()) {
                        if (pVision->TheirPlayer(player_num).Pos().dist(now_point) < 160) {
                            dist_score_dribble = dist_score_dribble + CVector(pVision->TheirPlayer(player_num).Pos() - now_point).mod();
                            y_score = max(fabs(me.Y() - pVision->TheirPlayer(player_num).Y()), y_score);
                        }
                    }
                }
                CGeoPoint goal_point = CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0);
                to_goal_score_dribble = CVector(now_point - goal_point).mod();
                total_score = para_dist * dist_score_dribble + para_goal * to_goal_score_dribble + para_y * y_score;
                if (final_score > total_score)
                {
                    best_point = now_point;
                    final_score = total_score;
                }
                //cout << "now_point  " << CGeoPoint(x_test, y_test) << "  total_score:  " << total_score << endl;
            }
        }
        if ((best_point - dribblePoint).mod() > DRIBBLE_DIST) {  // dribblePoint是中心点还是当前点？？？？
            best_point = makeInCircle(best_point, dribblePoint, DRIBBLE_DIST);
        }
        //if (DEBUG) GDebugEngine::Instance()->gui_debug_x(best_point, COLOR_YELLOW);
        if (!Utils::IsInField(best_point, 0)) // 将点移动到场地中
        {
            best_point = Utils::MakeInField(best_point, 0);
            //if (DEBUG) GDebugEngine::Instance()->gui_debug_x(best_point, COLOR_BLUE);
        }
        GDebugEngine::Instance()->gui_debug_x(best_point, COLOR_ORANGE);
        return best_point;
    }
}

bool CBreak::isSetPoint(const CVisionModule* pVision, const CGeoPoint* point, const CGeoPoint& target) {
    int i = 0;
    double x = 0, y = 0;
    for (i = 0; i < 20; i++) {
        x += point[i].x();
        y += point[i].y();
    }
    x /= 20.0; y /= 20.0;

    if (sqrt(pow(x - target.x(), 2) + pow(y - target.y(), 2)) > 10)
        return true;
    else
        return false;

}



bool CBreak::canScore(const CVisionModule* pVision, const int vecNumber, const double radius, const double dir) {
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);

    bool flag = true;
    double x1 = me.X(), y1 = me.Y(), theta = dir;
    float corrected_parameter = fabs(me.VelY()) * 0.2;
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -450), ("theta:" + to_string(theta)).c_str(), COLOR_YELLOW);
    if ((theta >= -Param::Math::PI && theta <= -Param::Math::PI / 2) || ((theta <= Param::Math::PI && theta >= Param::Math::PI / 2))) {
        flag = false;
    }
    if (Param::Field::MAX_PLAYER == 0)
    {
        double projection = y1 + tan(theta) * (Param::Field::PITCH_LENGTH / 2 - x1);
        if (fabs(projection) + 2 + corrected_parameter > (Param::Field::GOAL_WIDTH - 40) / 2) {
            flag = false;
        }
    }
    for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
        if (!pVision->TheirPlayer(i).Valid()) continue;
        auto enemy = pVision->TheirPlayer(i);
        double x = enemy.X(), y = enemy.Y();
        if (x < me.X()) continue;
        CGeoLine my_direction(me.Pos(), theta);
        CGeoPoint projection_point = my_direction.projection(enemy.Pos());
        //double r = fabs(y - y1 - tan(theta) * x + tan(theta) * x1) / sqrt(1 + tan(theta) * tan(theta));
        double r = projection_point.dist(enemy.Pos());
        double projection = y1 + tan(theta) * (Param::Field::PITCH_LENGTH / 2 - x1);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -500), ("r:" + to_string(r)).c_str(), COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -475), ("radius:" + to_string(radius)).c_str(), COLOR_YELLOW);
        //changed 6.29
        if (pVision->TheirPlayer(i).Vel().mod() < 50) {
            if (r < radius  || fabs(projection) + 2 + corrected_parameter>(Param::Field::GOAL_WIDTH - 40) / 2) {
                flag = false;
                break;
            }
        }
        else if (r < radius || fabs(projection) + 2 + corrected_parameter>(Param::Field::GOAL_WIDTH - 40) / 2) {
            flag = false;
            break;
        }
    }
    /*
    char projection[100];
    sprintf(projection, "%f", projection);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(160, 230), projection, COLOR_YELLOW);
    */
    CGeoLine ShootLine = CGeoLine(me.Pos(), me.Dir());
    CGeoLine GoalLine = CGeoLine(theirLeft, theirRight);
    CGeoSegment Goal = CGeoSegment(theirLeft, theirRight);
    CGeoLineLineIntersection LineIntersection = CGeoLineLineIntersection(GoalLine, ShootLine);
    if (LineIntersection.Intersectant() == 0)return false;
    CGeoPoint Intersection = LineIntersection.IntersectPoint();
    if (Goal.IsPointOnLineOnSegment(Intersection) == 0) flag = false;
    /*
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -450), ("CanScore:" + to_string(flag)).c_str(), COLOR_YELLOW);
    */
    return flag;

}