
/************************************************************************/
/* 23.2.18 fixed commentary by Yuhong Tan                                                          */
/************************************************************************/

#include "SmartGotoPosition.h"
#include "skill/Factory.h"
#include <utils.h>
#include <TaskMediator.h>
#include <GDebugEngine.h>
#include <WorldModel/RobotCapability.h>
#include <CommandFactory.h>
#include <MotionControl/ControlModel.h>
#include <iostream>
#include <PathPlan/RRTPathPlannerNew.h>

namespace {
    bool DRAW_RRT = false;
    bool DRAW_TRAJ = false;
    bool DRAW_OBS = false;
    bool DRAW_BALLPLACE_AREA = false;
    bool DRAW_PENALTY_DEBUG_MSG = false;

    const double SlowFactor = 0.5;
    const double FastFactor = 1.2;
    // 底层运动控制参数 ： 默认增大平动的控制性能
    double MAX_TRANSLATION_SPEED = 200;
    double MAX_TRANSLATION_ACC = 200;
    double MAX_ROTATION_SPEED = 15;
    double MAX_ROTATION_ACC = 15;
    double MAX_TRANSLATION_DEC = 200;

    double TRANSLATION_ACC_LIMIT = 200;
    double TRANSLATION_SPEED_LIMIT = 200;
    double TRANSLATION_ROTATE_ACC_LIMIT = 15;

    // 守门员专用运动参数
    double MAX_TRANSLATION_SPEED_GOALIE = 200;
    double MAX_TRANSLATION_ACC_GOALIE = 200;
    double MAX_TRANSLATION_DEC_GOALIE = 200;
    double MAX_ROTATION_ACC_GOALIE = 15;
    double MAX_ROTATION_SPEED_GOALIE = 15;

    /// 后卫专用
    double MAX_TRANSLATION_SPEED_BACK = 200;
    double MAX_TRANSLATION_ACC_BACK = 200;
    double MAX_TRANSLATION_DEC_BACK = 200;
    double MAX_ROTATION_ACC_BACK = 200;
    double MAX_ROTATION_SPEED_BACK = 200;

    // 避碰规划
    const double safeVelFactorFront = 1.0;
    const double safeVelFactorBack = 1.0;

    double stopBallAvoidDist = 50;
    double ballPlacementDist = 50;

    /// related to rrt
    double startToRotateToTargetDirDist = 20;
    pair < vector < pair < stateNew, size_t > >, vector < pair < stateNew, size_t > > > tree[Param::Field::MAX_PLAYER];
    CRRTPathPlannerNew planner[Param::Field::MAX_PLAYER];
    vector < stateNew > viaPoint[Param::Field::MAX_PLAYER];

    CGeoPoint lastPoint[Param::Field::MAX_PLAYER];
    CGeoPoint lastTarget[Param::Field::MAX_PLAYER];
    CGeoPoint nextPoint[Param::Field::MAX_PLAYER];
    const double TEAMMATE_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE + 4.0f;// 2014/03/13 修改，为了减少stop的时候卡住的概率 yys
    const double OPP_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE + 5.5f;
    const double BALL_AVOID_DIST = Param::Field::BALL_SIZE + 5.0f;
}
using namespace Param::Vehicle::V2;

CSmartGotoPosition::CSmartGotoPosition()
{
    DRAW_RRT = paramManager->DRAW_RRT;
    DRAW_TRAJ = paramManager->DRAW_TRAJ;
    DRAW_OBS = paramManager->DRAW_OBS;
    DRAW_BALLPLACE_AREA = paramManager->DRAW_BALLPLACE_AREA;
    DRAW_PENALTY_DEBUG_MSG = paramManager->DRAW_PENALTY_DEBUG_MSG;

    {
        // 守门员单独控制平动参数
        MAX_TRANSLATION_SPEED_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_SPEED_GOALIE;
        MAX_TRANSLATION_ACC_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_ACC_GOALIE;
        MAX_TRANSLATION_DEC_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_DEC_GOALIE;
        MAX_ROTATION_ACC_GOALIE = ParamManager::Instance()->MAX_ROTATION_ACC_GOALIE;
        MAX_ROTATION_SPEED_GOALIE = ParamManager::Instance()->MAX_ROTATION_SPEED_GOALIE;

        // 后卫单独控制平动参数
        MAX_TRANSLATION_SPEED_BACK = ParamManager::Instance()->MAX_TRANSLATION_SPEED_BACK;
        MAX_TRANSLATION_ACC_BACK = ParamManager::Instance()->MAX_TRANSLATION_ACC_BACK;
        MAX_TRANSLATION_DEC_BACK = ParamManager::Instance()->MAX_TRANSLATION_DEC_BACK;
        MAX_ROTATION_ACC_BACK = ParamManager::Instance()->MAX_ROTATION_ACC_BACK;
        MAX_ROTATION_SPEED_BACK = ParamManager::Instance()->MAX_ROTATION_SPEED_BACK;

        // 其他车的平动参数
        MAX_TRANSLATION_SPEED = ParamManager::Instance()->MAX_TRANSLATION_SPEED;
        MAX_TRANSLATION_ACC = ParamManager::Instance()->MAX_TRANSLATION_ACC;
        MAX_TRANSLATION_DEC = ParamManager::Instance()->MAX_TRANSLATION_DEC;

        MAX_ROTATION_SPEED = ParamManager::Instance()->MAX_ROTATION_SPEED;
        MAX_ROTATION_ACC = ParamManager::Instance()->MAX_ROTATION_ACC;

        TRANSLATION_ACC_LIMIT = ParamManager::Instance()->TRANSLATION_ACC_LIMIT;
        TRANSLATION_SPEED_LIMIT = ParamManager::Instance()->TRANSLATION_SPEED_LIMIT;
        TRANSLATION_ROTATE_ACC_LIMIT = ParamManager::Instance()->TRANSLATION_ROTATE_ACC_LIMIT;
    }
}

// 调试信息显示
void CSmartGotoPosition::toStream(std::ostream& os) const
{
    os << "Smart going to " << task().player.pos;
}

/// 规划接口
void CSmartGotoPosition::plan(const CVisionModule* pVision)
{
    /************************************************************************/
    /* 任务参数解析                                                          */
    /************************************************************************/
    // 获取任务参数
    playerFlag = task().player.flag;
    const bool isDribble = task().player.needdribble;
    const int vecNumber = task().executor;
    CGeoPoint finalTargetPos = task().player.pos;

    // 接入视觉信息
    const PlayerVisionT& self = pVision->OurPlayer(vecNumber);
    CGeoPoint myPos = self.Pos();
    CGeoPoint ballPos = pVision->Ball().Pos();

    // 标志位，判断是否为后卫或者守门员
    const bool isGoalie = (vecNumber == TaskMediator::Instance()->goalie());
    const bool isBack = TaskMediator::Instance()->isBack(vecNumber);
    const bool isMultiBack = TaskMediator::Instance()->isMultiBack(vecNumber);



    const bool isAdvancer = (vecNumber != 0 && vecNumber == TaskMediator::Instance()->advancer());

    // 判断为，判断需要躲避的指定区域，包括圆圈和放球椭圆
    bool avoidBallCircle = (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop") || (playerFlag & PlayerStatus::AVOID_STOP_BALL_CIRCLE);
    bool avoidOurBallPlacementArea = (WorldModel::Instance()->CurrentRefereeMsg() == "ourBallPlacement");
    bool avoidTheirBallPlacementArea = (WorldModel::Instance()->CurrentRefereeMsg() == "theirBallPlacement");
    bool shrinkTheirPenalty = Utils::InTheirPenaltyArea(finalTargetPos, 40) || Utils::InTheirPenaltyArea(myPos, 40);

    // 运动参数设置
    _capability = setCapability(pVision);

    /*
    grabTask.player.max_acceleration = MAX_ACC;
    grabTask.player.max_deceleration = MAX_ACC;
    grabTask.player.max_rot_acceleration = MAX_ROT_ACC;
    grabTask.player.max_rot_speed = MAX_ROT_VEL;
    */
    /************************************************************************/
    /* 避障区域生成                                                          */
    /************************************************************************/
    // 确定避障范围
    double buffer = 1.5;
    if (self.Vel().mod() < 200) {
        buffer = 1.5;
    }
    else if (self.Vel().mod() < 300) {
        buffer = 1.5 + (self.Vel().mod() - 200) / 100;
    }
    else {
        buffer = 2.5;
    }

    if ((self.Pos() - finalTargetPos).mod() < 100) {
        buffer /= 2;
    }
    if (isGoalie || ((isBack || isMultiBack) && Utils::InOurPenaltyArea(myPos, 40)) || WorldModel::Instance()->CurrentRefereeMsg() == "ourTimeout") {
        buffer = 0;
    }
    double avoidLength = Param::Vehicle::V2::PLAYER_SIZE + buffer;
    float avoidBallFix = 3;
    if (pVision->GetCurrentRefereeMsg() == "ourIndirectKick" || pVision->GetCurrentRefereeMsg() == "ourDirectKick" || pVision->GetCurrentRefereeMsg() == "ourKickOff")
        avoidBallFix = 1.5;

    // 生成避障区域
    ObstaclesNew obsNew(avoidLength);
    //if (isAdvancer || isBack || isGoalie)
    //    obsNew.addObs(pVision, task(), DRAW_OBS, Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 0.5, Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 0.5, Param::Field::BALL_SIZE + avoidBallFix);
    // if (isAdvancer || isBack || isGoalie)
    //    obsNew.addObs(pVision, task(), DRAW_OBS, Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 2, Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 0.5, Param::Field::BALL_SIZE + avoidBallFix);

    if (isAdvancer || isBack || isGoalie)
        obsNew.addObs(pVision, task(), DRAW_OBS, Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 2, Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 0.5, Param::Field::BALL_SIZE + avoidBallFix);
    else
        obsNew.addObs(pVision, task(), DRAW_OBS, Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 5, Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 0.5, Param::Field::BALL_SIZE + avoidBallFix);
    

    /************************************************************************/
    /* 目标点更新                                                            */
    /************************************************************************/

    // 在己方放球或对方放球需要避开开球到放球点之间半径为50cm的圆
    int leaderNumber = paramManager->PlACEBALL_PLAYER_NUM;
    // ObstaclesNew obsNewNew(avoidLength);
    // obsNewNew.addLongCircle(segP1, segP2, CVector(0.0, 0.0), ballPlacementDist, OBS_LONG_CIRCLE_NEW, false, true);
    //
    if (avoidTheirBallPlacementArea || (avoidOurBallPlacementArea && vecNumber != leaderNumber)) {
        CGeoPoint segP1 = pVision->Ball().Pos(), segP2(pVision->getBallPlacementPosition().x(), pVision->getBallPlacementPosition().y());
        bool addObs = false;
        finalTargetPos = finalPointBallPlacement(myPos, finalTargetPos, segP1, segP2, avoidLength * 2.0, obsNew, addObs);
        if (addObs) obsNew.addLongCircle(segP1, segP2, CVector(0.0, 0.0), ballPlacementDist, OBS_LONG_CIRCLE_NEW, false, true);
        if (DRAW_BALLPLACE_AREA) obsNew.drawLongCircle(segP1, segP2, ballPlacementDist);
    }

    // 在正常模式下需要保证最终点在禁区外，场地内，车身外
    else {
        validateFinalTarget(finalTargetPos, pVision, shrinkTheirPenalty, avoidLength, isGoalie);
        // 躲避stop状态中的球圈
        if (avoidBallCircle) {
            CGeoPoint ballPos = pVision->Ball().Pos();
            finalTargetPos = Utils::MakeOutOfCircle(ballPos, stopBallAvoidDist, finalTargetPos, avoidLength);
        }
    }

    /************************************************************************/
    /* 确定下发速度                                                         */
    /************************************************************************/
    // 处理非零速时的末速度，避免车因为非零速冲进禁区或冲出场外
    CVector velNew = validateFinalVel(isGoalie, self.Pos(), finalTargetPos, task().player.vel);

    // 申明新任务
    TaskT newTask(task());
    newTask.player.pos = finalTargetPos;
    newTask.player.vel = velNew;

    // 发球时添加避球标签
    if (pVision->GetCurrentRefereeMsg() == "ourIndirectKick" || pVision->GetCurrentRefereeMsg() == "ourDirectKick" || pVision->GetCurrentRefereeMsg() == "ourKickOff")
        newTask.player.flag = newTask.player.flag & (PlayerStatus::DODGE_BALL);

    /************************************************************************/
    /* 开始规划路径                                                        */
    /************************************************************************/
    stateNew startNew, targetNew;

    // 处理规划起点
    startNew.pos = myPos;
    int stuckBuffer = 0;
    int stuckTres = 10;
    while (!validateStartPoint(myPos, avoidLength, isGoalie, obsNew) && stuckBuffer < stuckTres) {
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,0), "I'm stuck");
        startNew.pos = Utils::MakeOutOfTheirPenaltyArea(myPos, 100);
        stuckBuffer++; }

    // 处理规划终点
    targetNew.pos = finalTargetPos;
    CGeoPoint middlePoint = finalTargetPos;

    // 到达中间点的判据，让整条路径更加连贯
    double arrivedDist = self.Vel().mod() * 0.2  + 10;

    //cout << arrivedDist << ' ' << (lastPoint[vecNumber] - self.Pos()).mod() << endl;
    // 第一种情况：可以直接到目标点
    if (obsNew.check(startNew.pos, targetNew.pos) || obsNew.check(self.Pos(), targetNew.pos) ||
        self.Pos().dist(finalTargetPos) < Param::Vehicle::V2::PLAYER_SIZE * 2) {
        middlePoint = finalTargetPos;
        nextPoint[vecNumber] = finalTargetPos;
    }
    // 第二种情况，在禁区附近特殊处理
    //else if (!(playerFlag & PlayerStatus::NOT_DODGE_PENALTY) && (Utils::InTheirPenaltyArea(self.Pos(), 40) || (!isGoalie && Utils::InOurPenaltyArea(self.Pos(), 40)))) {
    //    middlePoint = dealPlanFail(self.Pos(), targetNew.pos, avoidLength, shrinkTheirPenalty);
    //}
    // 第二种情况：上次规划的中间点仍然可以用（最终目标点没有变，则整条路经有意义；我与中间点之间无障碍，中间点与下一个中间点之间也无障碍），且还没有到达中间点
    else if (lastTarget[vecNumber] == targetNew.pos && obsNew.check(startNew.pos, lastPoint[vecNumber]) && obsNew.check(nextPoint[vecNumber], lastPoint[vecNumber]) && (lastPoint[vecNumber] - self.Pos()).mod() > arrivedDist) {
        middlePoint = lastPoint[vecNumber];
    }
    // 第三种情况：其它，则重新规划
    else {
        planner[vecNumber].initPlanner(250, 15, 20, 0.05, 0.55, Param::Vehicle::V2::PLAYER_SIZE);
        planner[vecNumber].planPath(&obsNew, startNew, targetNew);
        viaPoint[vecNumber] = planner[vecNumber].getPathPoints();

        // 规划成功的情况则给中间点赋值，一般都是有中间点的
        if (viaPoint[vecNumber].size() > 2) {
            middlePoint = viaPoint[vecNumber][1].pos;
            nextPoint[vecNumber] = viaPoint[vecNumber][2].pos;
        }
    }

    //GDebugEngine::Instance()->gui_debug_x(lastPoint[vecNumber], 1);

    // 记录中间点，作为下一次规划基础
    lastPoint[vecNumber] = middlePoint;
    lastTarget[vecNumber] = targetNew.pos;
    
    bool needRush2Ball = Utils::InTheirPenaltyArea(ballPos, 10) && !Utils::InTheirPenaltyArea(ballPos, 0); // 球在禁区外且很靠近禁区，直接冲击
    if (!isGoalie && !(playerFlag & PlayerStatus::NOT_DODGE_PENALTY) && !needRush2Ball) {
        middlePoint = dealPlanFail(myPos, middlePoint, avoidLength, shrinkTheirPenalty);
        while (Utils::InTheirPenaltyArea(middlePoint, 10)) { // 规划的点会闯入禁区，修正
            middlePoint = middlePoint + Utils::Polar2Vector(1, (middlePoint - CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0)).dir());
        }
        while (Utils::InOurPenaltyArea(middlePoint, 10)) { // 规划的点会闯入禁区，修正
            middlePoint = middlePoint + Utils::Polar2Vector(1, (middlePoint - CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0)).dir());
        }
        lastPoint[vecNumber] = middlePoint;
    }

    newTask.player.pos = middlePoint;
    //GDebugEngine::Instance()->gui_debug_x(middlePoint, 1);
    //GDebugEngine::Instance()->gui_debug_x(finalTargetPos, 2);
    
    // 非零速到达中间点，零速只有在可以直接到时才执行
    if (middlePoint.dist(task().player.pos) > 50) newTask.player.IsGoMiddle = true;
    else newTask.player.IsGoMiddle = false;

    // 控制吸球力度
    if (isDribble || (playerFlag & PlayerStatus::DRIBBLING)) DribbleStatus::Instance()->setDribbleCommand(vecNumber, 3);

    /************************************************************************/
    /* 调试信息显示                                                           */
    /************************************************************************/
    // 信息输出：画出当前位置点，初始目标点，处理过的目标点
    if (DRAW_TRAJ) {
        GDebugEngine::Instance()->gui_debug_x(myPos, COLOR_PURPLE);
        GDebugEngine::Instance()->gui_debug_arc(self.Pos(), avoidLength, 0, 360, 1);
        //GDebugEngine::Instance()->gui_debug_x(task().player.pos, COLOR_RED);
        GDebugEngine::Instance()->gui_debug_x(finalTargetPos, COLOR_YELLOW);
    }

    // 信息输出：画出RRT撒点，看规划范围是否正确
    if (DRAW_RRT && vecNumber == 1) {
        tree[vecNumber] = planner[vecNumber].getNodes();
        for (size_t i = 0; viaPoint[vecNumber].size() > 0 && i < viaPoint[vecNumber].size() - 1; i++) {
            GDebugEngine::Instance()->gui_debug_line(viaPoint[vecNumber][i].pos, viaPoint[vecNumber][i + 1].pos, COLOR_CYAN);
        }
        for (size_t i = 1; !tree[vecNumber].first.empty() && i < tree[vecNumber].first.size(); i += 1) {
            GDebugEngine::Instance()->gui_debug_x(tree[vecNumber].first[i].first.pos, COLOR_GREEN);
        }
        for (size_t i = 1; !tree[vecNumber].second.empty() && i < tree[vecNumber].second.size(); i++) {
            GDebugEngine::Instance()->gui_debug_x(tree[vecNumber].second[i].first.pos, COLOR_YELLOW);
        }
    }

    /************************************************************************/
    /* 下达子任务                                                            */
    /************************************************************************/
    setSubTask(TaskFactoryV2::Instance()->GotoPosition(newTask));
    _lastCycle = pVision->Cycle();
    CPlayerTask::plan(pVision);
    return;
}

PlayerCapabilityT CSmartGotoPosition::setCapability(const CVisionModule* pVision) {
    const int vecNumber = task().executor;
    const bool isGoalie = (vecNumber == TaskMediator::Instance()->goalie());
    const bool isBack = TaskMediator::Instance()->isBack(vecNumber);
    const bool isMultiBack = TaskMediator::Instance()->isMultiBack(vecNumber);
    const CGeoPoint mePos = pVision->OurPlayer(vecNumber).Pos();
    const int playerFlag = task().player.flag;
    PlayerCapabilityT capability;

    /// 设置平动参数和转动参数
    if (isGoalie) {
        // Traslation 确定平动运动参数
        capability.maxSpeed = MAX_TRANSLATION_SPEED_GOALIE;
        capability.maxAccel = MAX_TRANSLATION_ACC_GOALIE;
        capability.maxDec = MAX_TRANSLATION_DEC_GOALIE;
        // Rotation	  确定转动运动参数
        capability.maxAngularSpeed = MAX_ROTATION_SPEED_GOALIE;
        capability.maxAngularAccel = MAX_ROTATION_ACC_GOALIE;
        capability.maxAngularDec = MAX_ROTATION_ACC_GOALIE;
    }
    else if (isBack || isMultiBack) {
        // Traslation 确定平动运动参数
        capability.maxSpeed = MAX_TRANSLATION_SPEED_BACK;
        capability.maxAccel = MAX_TRANSLATION_ACC_BACK;
        capability.maxDec = MAX_TRANSLATION_DEC_BACK;
        // Rotation	  确定转动运动参数
        capability.maxAngularSpeed = MAX_ROTATION_SPEED_BACK;
        capability.maxAngularAccel = MAX_ROTATION_ACC_BACK;
        capability.maxAngularDec = MAX_ROTATION_ACC_BACK;
    }
    else {
        // Traslation 确定平动运动参数
        capability.maxSpeed = MAX_TRANSLATION_SPEED;
        capability.maxAccel = MAX_TRANSLATION_ACC;
        capability.maxDec = MAX_TRANSLATION_DEC;
        // Rotation	  确定转动运动参数
        capability.maxAngularSpeed = MAX_ROTATION_SPEED;
        capability.maxAngularAccel = MAX_ROTATION_ACC;
        capability.maxAngularDec = MAX_ROTATION_ACC;
    }


    // 指定加速度上限；
    /*if (task().player.max_acceleration > 1e-8 && !(isBack && !Utils::InOurPenaltyArea(mePos, 40))) {*/
    if (task().player.max_acceleration > 1e-8) {
        capability.maxAccel = task().player.max_acceleration > TRANSLATION_ACC_LIMIT ? TRANSLATION_ACC_LIMIT : task().player.max_acceleration;
        capability.maxDec = capability.maxAccel;
    }
    // 指定速度上限
    if (task().player.max_speed > 1e-8) {
        capability.maxSpeed = task().player.max_speed > TRANSLATION_SPEED_LIMIT ? TRANSLATION_SPEED_LIMIT : task().player.max_speed;
    }
    // 最大转动加速度上限
    if (task().player.max_rot_acceleration > 1e-8) {
        capability.maxAngularAccel = task().player.max_rot_acceleration > TRANSLATION_ROTATE_ACC_LIMIT ? TRANSLATION_ROTATE_ACC_LIMIT : task().player.max_rot_acceleration;
        capability.maxAngularDec = capability.maxAngularAccel;
    }
    // 最大转速上限----其实没什么用
    if (task().player.max_rot_speed > 1e-8) {
        capability.maxAngularSpeed = task().player.max_rot_speed;
    }

    // GameStop状态不能超速
    if (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop") {
        capability.maxSpeed = 500;
        capability.maxAccel = 400;
        capability.maxDec = 400;
    }

    if (task().player.max_acceleration)_capability.maxAccel = task().player.max_acceleration;
    if (task().player.max_deceleration)_capability.maxDec = task().player.max_deceleration;
    if (task().player.max_rot_acceleration)_capability.maxAngularDec = task().player.max_rot_acceleration;
    if (task().player.max_rot_acceleration)_capability.maxAngularAccel = task().player.max_rot_acceleration;
    if (task().player.max_rot_speed)_capability.maxAngularSpeed = task().player.max_rot_speed;


    return capability;
}

// 处理无效目标点: 在禁区内、在车身内、在场地外. Modified by HXY.
void CSmartGotoPosition::validateFinalTarget(CGeoPoint& finalTarget, const CVisionModule* pVision, bool shrinkTheirPenalty, double avoidLength, bool isGoalie) {
    // 定位球 (FREE_KICK) 的时候需要多避对方禁区20厘米.
    double theirPenaltyAvoidLength = avoidLength;
    if (playerFlag & PlayerStatus::FREE_KICK) {
        theirPenaltyAvoidLength += 20.0;
    }
    else if (!shrinkTheirPenalty) {
        theirPenaltyAvoidLength += Param::Vehicle::V2::PLAYER_SIZE;
    }
    // 同时满足不是放球而且不带 NOT_DODGE_PENALTY 标志位的情况下才会更正目标点
    if  (WorldModel::Instance()->CurrentRefereeMsg() != "ourBallPlacement" && !(playerFlag & PlayerStatus::NOT_DODGE_PENALTY)) {
        finalTarget = Utils::MakeInField(finalTarget, -1*Param::Field::FIELD_WALL_DIST);
        // 如果球员现在就在禁区里，优先退出
        if (!isGoalie && Utils::InOurPenaltyArea(finalTarget, avoidLength))
            finalTarget = Utils::MakeOutOfOurPenaltyArea(finalTarget, avoidLength);
        else if (Utils::InTheirPenaltyArea(finalTarget, theirPenaltyAvoidLength))
            finalTarget = Utils::MakeOutOfTheirPenaltyArea(finalTarget, theirPenaltyAvoidLength);
    }
}

bool CSmartGotoPosition::validateStartPoint(CGeoPoint& startPoint, double avoidLength, bool isGoalie, ObstaclesNew &obs) {
    if (!(playerFlag & PlayerStatus::NOT_DODGE_PENALTY)) {
        if (!isGoalie && Utils::InOurPenaltyArea(startPoint, avoidLength))
            startPoint = Utils::MakeOutOfOurPenaltyArea(startPoint, avoidLength);
        if (Utils::InTheirPenaltyArea(startPoint, avoidLength)) {  //debug from chen siyuan 2021/3/17
            if (playerFlag & PlayerStatus::FREE_KICK) {
                startPoint = Utils::MakeOutOfTheirPenaltyArea(startPoint, 3 * avoidLength);
            }
            else {
                startPoint = Utils::MakeOutOfTheirPenaltyArea(startPoint, 3 * avoidLength);
            }

        }
    }
    CGeoPoint originStartPoint = startPoint;
    CVector adjustVec(0, 0);
    int obsNum = obs.getNum(), i = 0;
    for (i = 0; i < obsNum; i++) {
        if (!obs.obs[i].check(startPoint)) {

            if (obs.obs[i].getType() == OBS_CIRCLE_NEW) {
                adjustVec = adjustVec + Utils::Polar2Vector((avoidLength + obs.obs[i].getRadius() - obs.obs[i].getStart().dist(startPoint)), (startPoint - obs.obs[i].getStart()).dir());
            }
            else if (obs.obs[i].getType() == OBS_LONG_CIRCLE_NEW) {
                CGeoPoint nearPoint = obs.obs[i].getStart().dist(startPoint) > obs.obs[i].getEnd().dist(startPoint) ? obs.obs[i].getEnd() : obs.obs[i].getStart();
                adjustVec = adjustVec + Utils::Polar2Vector(avoidLength + obs.obs[i].getRadius() - nearPoint.dist(startPoint), (startPoint - nearPoint).dir());
            }
        }
    }

    if (obs.check(startPoint)) {
        return true;//out of obstacle, success
    }
    else
    {
        double adjustStep = Param::Vehicle::V2::PLAYER_SIZE;
        double adjustVecMod = adjustVec.mod();
        if (abs(adjustVecMod) < 1e-5 || isnan(adjustVecMod)) adjustVecMod = 1.0;  // sqrt(0)bug from chen siyuan
        adjustVec = adjustVec / adjustVecMod;
        startPoint = startPoint + adjustVec * adjustStep;
        return false;//still in obstacle, failed
    }
}

// 考虑到点后的速度对末位置的漂移影响，速度在垂直于轨迹线方向对初始位置的影响
CVector CSmartGotoPosition::validateFinalVel(const bool isGoalie, const CGeoPoint& startPos, const CGeoPoint &targetPos, const CVector &targetVel) {

    if (targetVel.mod() < 1e-8) return CVector(0.0, 0.0);
    double distToStop, velMod, adjustStep, factorFront, factorBack, distToTarget, maxFinalSpeedAccordingToDist;
    CGeoPoint stopPosFront, stopPosBack;
    CVector velNew = targetVel;
    CVector velDir = targetVel / targetVel.mod();
    distToTarget = startPos.dist(targetPos);


    if (distToTarget < 1e-8 || _capability.maxAccel < 1e-8)
        return CVector(0.0, 0.0);
    maxFinalSpeedAccordingToDist = sqrt(2 * _capability.maxAccel * distToTarget * 0.5);
    if (maxFinalSpeedAccordingToDist > _capability.maxSpeed)
        maxFinalSpeedAccordingToDist = _capability.maxSpeed;

    if (targetVel.mod() > maxFinalSpeedAccordingToDist)
        velNew = velDir * maxFinalSpeedAccordingToDist;
    velMod = velNew.mod();
    factorFront = safeVelFactorFront;
    factorBack = safeVelFactorBack;
    adjustStep = 5;

    if (_capability.maxDec < 1e-8) return CVector(0.0, 0.0);
    distToStop = pow(targetVel.mod(), 2) / (2.0 * _capability.maxDec);
    stopPosFront = targetPos + velDir * distToStop * factorFront;
    stopPosBack = targetPos + velDir * (-distToStop) * factorBack;

    while (!Utils::IsInField(stopPosFront, Param::Vehicle::V2::PLAYER_SIZE) ||
        Utils::InTheirPenaltyArea(stopPosFront, Param::Vehicle::V2::PLAYER_SIZE) ||
        (!isGoalie && Utils::InOurPenaltyArea(stopPosFront, Param::Vehicle::V2::PLAYER_SIZE)) ||
        !Utils::IsInField(stopPosBack, Param::Vehicle::V2::PLAYER_SIZE) ||
        Utils::InTheirPenaltyArea(stopPosBack, Param::Vehicle::V2::PLAYER_SIZE) ||
        (!isGoalie && Utils::InOurPenaltyArea(stopPosBack, Param::Vehicle::V2::PLAYER_SIZE))) {
        velMod -= adjustStep;
        if (velMod < 0) return CVector(0.0, 0.0);
        velNew = velDir * velMod;
        if (_capability.maxSpeed > 1e-8 && safeVelFactorFront > 1.0)
            factorFront = velNew.mod() * (safeVelFactorFront - 1.0) / _capability.maxSpeed + 1.0;
        if (_capability.maxSpeed > 1e-8 && safeVelFactorBack > 1.0)
            factorBack = velNew.mod() * (safeVelFactorBack - 1.0) / _capability.maxSpeed + 1.0;
        factorFront = (factorFront >= 1.0) ? factorFront : 1.0;
        factorBack = (factorBack >= 1.0) ? factorBack : 1.0;
        if (_capability.maxDec < 1e-8) return CVector(0.0, 0.0);
        distToStop = pow(velNew.mod(), 2) / (2.0 * _capability.maxDec);
        stopPosFront = targetPos + velDir * distToStop * factorFront;
        stopPosBack = targetPos + velDir * (-distToStop) * factorBack;
    }
    return velNew;
}

// 单独处理禁区有关的规划失败问题
CGeoPoint CSmartGotoPosition::dealPlanFail(CGeoPoint startPoint, CGeoPoint nextPoint, double avoidLength, bool shrinkTheirPenalty) {

    double buffer = 0;
    if (WorldModel::Instance()->CurrentRefereeMsg() == "ourIndirectKick" || WorldModel::Instance()->CurrentRefereeMsg() == "theirIndirectKick"
        || WorldModel::Instance()->CurrentRefereeMsg() == "gameStop")
        buffer += 20;

    CGeoRectangle theirPenalty(CGeoPoint(Param::Field::PITCH_LENGTH / 2 -Param::Field::PENALTY_AREA_DEPTH-buffer, -Param::Field::PENALTY_AREA_WIDTH / 2-buffer), CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2 +buffer));
    CGeoRectangle ourPenalty(CGeoPoint(-Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2-buffer), CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH+buffer, Param::Field::PENALTY_AREA_WIDTH / 2+buffer));
    CGeoLine pathLine(startPoint, nextPoint);
    // if (!shrinkTheirPenalty) {
    //     theirPenalty = CGeoRectangle(CGeoPoint(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - Param::Vehicle::V2::PLAYER_SIZE, -Param::Field::PENALTY_AREA_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE), CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE));
    // }
    CGeoLineRectangleIntersection theirInter(pathLine, theirPenalty);
    CGeoLineRectangleIntersection ourInter(pathLine, ourPenalty);
    CGeoPoint nextPointNew = nextPoint;
    CGeoPoint candidate11 = CGeoPoint(theirPenalty._point[1].x() - avoidLength - OPP_AVOID_DIST, theirPenalty._point[1].y() + avoidLength + OPP_AVOID_DIST),
        // candidate12 = CGeoPoint(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - avoidLength - OPP_AVOID_DIST, Param::Field::PENALTY_AREA_WIDTH / 2 - avoidLength - OPP_AVOID_DIST),
        candidate21 = CGeoPoint(theirPenalty._point[1].x() - avoidLength - OPP_AVOID_DIST, theirPenalty._point[3].y() - avoidLength - OPP_AVOID_DIST),
        // candidate22 = CGeoPoint(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - avoidLength - OPP_AVOID_DIST, -Param::Field::PENALTY_AREA_WIDTH / 2 + avoidLength + OPP_AVOID_DIST),
        candidate31 = CGeoPoint(ourPenalty._point[3].x() + avoidLength + OPP_AVOID_DIST, ourPenalty._point[1].y() + avoidLength + OPP_AVOID_DIST),
        // candidate32 = CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + avoidLength + OPP_AVOID_DIST, Param::Field::PENALTY_AREA_WIDTH / 2 - avoidLength - OPP_AVOID_DIST),
        candidate41 = CGeoPoint(ourPenalty._point[3].x() + avoidLength + OPP_AVOID_DIST, ourPenalty._point[3].y() - avoidLength - OPP_AVOID_DIST); // ,
        // candidate42 = CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + avoidLength + OPP_AVOID_DIST, -Param::Field::PENALTY_AREA_WIDTH / 2 + avoidLength + OPP_AVOID_DIST);
    if (DRAW_PENALTY_DEBUG_MSG) {
        GDebugEngine::Instance()->gui_debug_x(candidate11);
        GDebugEngine::Instance()->gui_debug_x(candidate21);
        GDebugEngine::Instance()->gui_debug_x(candidate31);
        GDebugEngine::Instance()->gui_debug_x(candidate41);
        // GDebugEngine::Instance()->gui_debug_x(candidate12);
        // GDebugEngine::Instance()->gui_debug_x(candidate22);
        // GDebugEngine::Instance()->gui_debug_x(candidate32);
        // GDebugEngine::Instance()->gui_debug_x(candidate42);
    }

    double isTheirMiddle = 0, isOurMiddle = 0;
    if (theirInter.intersectant()) {
        CGeoPoint theirInterPoint = theirInter.point1().midPoint(theirInter.point2());
        isTheirMiddle = (theirInterPoint.x() - startPoint.x()) * (theirInterPoint.x() - nextPoint.x()) + (theirInterPoint.y() - startPoint.y()) * (theirInterPoint.y() - nextPoint.y());
    }
    if (ourInter.intersectant()) {
        CGeoPoint ourInterPoint = ourInter.point1().midPoint(ourInter.point2());
        isOurMiddle = (ourInterPoint.x() - startPoint.x()) * (ourInterPoint.x() - nextPoint.x()) + (ourInterPoint.y() - startPoint.y()) * (ourInterPoint.y() - nextPoint.y());
    }
    if (isTheirMiddle < 0) {
        double next2StartDir = Utils::Normalize((nextPoint - startPoint).dir());
        if ((next2StartDir > -Param::Math::PI / 2 && next2StartDir < 0) || (next2StartDir > Param::Math::PI / 2 && next2StartDir < Param::Math::PI))
            nextPointNew = candidate21;
        else if ((next2StartDir > 0 && next2StartDir < Param::Math::PI / 2) || (next2StartDir > -Param::Math::PI && next2StartDir < -Param::Math::PI / 2))
            nextPointNew = candidate11;
        if (nextPoint.y() < -Param::Field::PENALTY_AREA_WIDTH / 2 && startPoint.y() > Param::Field::PENALTY_AREA_WIDTH / 2 
            && nextPoint.x() >= startPoint.x() && startPoint.x() > theirPenalty._point[1].x() - Param::Vehicle::V2::PLAYER_SIZE)
            nextPointNew = candidate11;
        else if (nextPoint.y() > Param::Field::PENALTY_AREA_WIDTH / 2 && startPoint.y() < -Param::Field::PENALTY_AREA_WIDTH / 2 
            && nextPoint.x() >= startPoint.x() && startPoint.x() > theirPenalty._point[1].x() - Param::Vehicle::V2::PLAYER_SIZE)
            nextPointNew = candidate21;
    }
    else if (isOurMiddle < 0) {
        double next2StartDir = Utils::Normalize((nextPoint - startPoint).dir());
        if ((next2StartDir > -Param::Math::PI / 2 && next2StartDir < 0) || (next2StartDir > Param::Math::PI / 2 && next2StartDir < Param::Math::PI))
            nextPointNew = candidate31;
        else if ((next2StartDir > 0 && next2StartDir < Param::Math::PI / 2) || (next2StartDir > -Param::Math::PI && next2StartDir < -Param::Math::PI / 2))
            nextPointNew = candidate41;
        if (nextPoint.y() < -Param::Field::PENALTY_AREA_WIDTH / 2 && startPoint.y() > Param::Field::PENALTY_AREA_WIDTH / 2
            && nextPoint.x() <= startPoint.x() && startPoint.x() < ourPenalty._point[3].x() + Param::Vehicle::V2::PLAYER_SIZE)
            nextPointNew = candidate31;
        else if (nextPoint.y() > Param::Field::PENALTY_AREA_WIDTH / 2 && startPoint.y() < -Param::Field::PENALTY_AREA_WIDTH / 2
            && nextPoint.x() <= startPoint.x() && startPoint.x() < ourPenalty._point[3].x() + Param::Vehicle::V2::PLAYER_SIZE)
            nextPointNew = candidate41;
        /**
        if (!((startPoint.y() > Param::Field::PENALTY_AREA_WIDTH / 2 && nextPoint.y() > Param::Field::PENALTY_AREA_WIDTH / 2) ||
            (startPoint.y() < -Param::Field::PENALTY_AREA_WIDTH / 2 && nextPoint.y() < -Param::Field::PENALTY_AREA_WIDTH / 2) ||
            (startPoint.y() < Param::Field::PENALTY_AREA_WIDTH / 2 && startPoint.y() > -Param::Field::PENALTY_AREA_WIDTH / 2 && nextPoint.y() < Param::Field::PENALTY_AREA_WIDTH / 2 && nextPoint.y() > -Param::Field::PENALTY_AREA_WIDTH / 2))) {

            if (startPoint.x() > Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH) {
                if (startPoint.y() > Param::Field::PENALTY_AREA_WIDTH / 2) {
                    nextPointNew = candidate11;
                    if (nextPoint.dist(candidate12) < nextPoint.dist(candidate12) && startPoint.dist(candidate11) < 5)
                        nextPointNew = candidate12;
                }
                else {
                    nextPointNew = candidate21;
                    if (nextPoint.dist(candidate22) < nextPoint.dist(candidate22) && startPoint.dist(candidate21) < 5)
                        nextPointNew = candidate22;
                }
            }
            else if (startPoint.x() < -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH) {
                if (startPoint.y() > Param::Field::PENALTY_AREA_WIDTH / 2) {
                    nextPointNew = candidate31;
                    if (nextPoint.dist(candidate32) < nextPoint.dist(candidate32) && startPoint.dist(candidate31) < 5)
                        nextPointNew = candidate32;
                }
                else {
                    nextPointNew = candidate41;
                    if (nextPoint.dist(candidate42) < nextPoint.dist(candidate42) && startPoint.dist(candidate41) < 5)
                        nextPointNew = candidate42;
                }
            }
            else if (nextPoint.x() > Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH) {
                if (nextPoint.y() > Param::Field::PENALTY_AREA_WIDTH / 2) {
                    nextPointNew = candidate12;
                    if (nextPoint.dist(candidate11) < nextPoint.dist(candidate12) && startPoint.dist(candidate12) < 5)
                        nextPointNew = candidate11;
                }
                else {
                    nextPointNew = candidate22;
                    if (nextPoint.dist(candidate21) < nextPoint.dist(candidate22) && startPoint.dist(candidate22) < 5)
                        nextPointNew = candidate21;
                }
            }
            else if (nextPoint.x() < -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH) {
                if (nextPoint.y() > Param::Field::PENALTY_AREA_WIDTH / 2) {
                    nextPointNew = candidate32;
                    if (nextPoint.dist(candidate31) < nextPoint.dist(candidate32) && startPoint.dist(candidate32) < 5)
                        nextPointNew = candidate31;
                }
                else {
                    nextPointNew = candidate42;
                    if (nextPoint.dist(candidate41) < nextPoint.dist(candidate42) && startPoint.dist(candidate42) < 5)
                        nextPointNew = candidate41;
                }
            }
        }
        **/
    }
    
    return nextPointNew;
}

CGeoPoint CSmartGotoPosition::finalPointBallPlacement(const CGeoPoint &startPoint, const CGeoPoint &target, const CGeoPoint &segPoint1, const CGeoPoint &segPoint2, const double avoidLength, ObstaclesNew& obst, bool& canDirect) {
    CGeoPoint targetNew = target;
    CGeoPoint projectionPoint = CGeoPoint(1e8, 1e8);
    CGeoSegment obsSegment(segPoint1, segPoint2);
    CGeoSegment pathLine(startPoint, target);
    double obsRadius = ballPlacementDist;
    const double CAN_PASS_ANGLE = Param::Math::PI / 9;
    CVector segVec = segPoint1 - segPoint2;
    CVector adjustDir = segVec.rotate(Param::Math::PI / 2).unit();
    double adjustStep = 5.0;
    double avoidBuffer = 60;
    canDirect = true;

    ///情况1：自己和目标都在区域内，把自己移出区域并作为新的目标点；
    if (obsSegment.dist2Point(startPoint) < obsRadius + avoidLength /*&&
            obsSegment.dist2Point(target) < obsRadius + avoidLength*/) {
        GDebugEngine::Instance()->gui_debug_msg(startPoint, "Me In, Target In", COLOR_ORANGE);
        targetNew = startPoint;
        projectionPoint = startPoint;
        while (obsSegment.dist2Point(targetNew) < obsRadius + avoidLength) {
            targetNew = targetNew + adjustDir * adjustStep;
        }
        if (targetNew.dist(startPoint) > obsRadius + avoidLength) {
            adjustDir = -adjustDir;
            targetNew = targetNew + (adjustDir) * (2 * (obsRadius + avoidLength + adjustStep));
        }
        targetNew = targetNew + adjustDir * avoidBuffer;
        CGeoPoint originTargetNew = targetNew;
        double adjustBuffer = avoidBuffer;
        while (!Utils::IsInField(targetNew, 0) ||
            Utils::InOurPenaltyArea(targetNew, avoidLength) ||
            Utils::InTheirPenaltyArea(targetNew, avoidLength)) {
            targetNew = targetNew + (adjustDir) * (2 * (obsRadius + avoidLength + adjustStep + adjustBuffer));
            adjustBuffer -= 10;
            if (adjustBuffer < 10) break;
        }

        adjustDir = -adjustDir;
        adjustBuffer = avoidBuffer;
        targetNew = originTargetNew;
        while (!Utils::IsInField(targetNew, 0) ||
            Utils::InOurPenaltyArea(targetNew, avoidLength) ||
            Utils::InTheirPenaltyArea(targetNew, avoidLength)) {
            targetNew = targetNew + (adjustDir) * (2 * (obsRadius + avoidLength + adjustStep + adjustBuffer));
            adjustBuffer -= 10;
            if (adjustBuffer < 10) break;
        }
        //        targetNew = targetNew + adjustDir * avoidBuffer;
        if (avoidBuffer < 10)
            targetNew = CGeoPoint(0.0, 0.0);
        canDirect = false;
    }

    ///情况2： 自己在区域外，目标在区域内，将目标移动到己方区域边界
    else if (obsSegment.dist2Point(startPoint) > obsRadius + avoidLength &&
        obsSegment.dist2Segment(pathLine) < obsRadius + avoidLength) {
        GDebugEngine::Instance()->gui_debug_msg(startPoint, "Me Out, Target In", COLOR_ORANGE);
        targetNew = target;
        projectionPoint = startPoint;
        targetNew = startPoint;
        //        while(obsSegment.dist2Point(targetNew) < obsRadius + avoidLength)
        //            targetNew = targetNew + adjustDir * adjustStep;
        //        if(obsSegment.dist2Segment(CGeoSegment(startPoint, targetNew)) < obsRadius + avoidLength) {
        //            adjustDir = -adjustDir;
        //            targetNew = targetNew + (adjustDir) * (2 * (obsRadius + avoidLength + adjustStep));
        //        }
        //        targetNew = targetNew + adjustDir * avoidBuffer;
        //        if(!Utils::IsInField(targetNew, avoidLength) || Utils::InOurPenaltyArea(targetNew, avoidLength) || Utils::InTheirPenaltyArea(targetNew, avoidLength)) {
        //            adjustDir = -adjustDir;
        //            targetNew = targetNew + (adjustDir) * (2 * (obsRadius + avoidLength + adjustStep) + avoidBuffer);
        //        }
        //        targetNew = targetNew + adjustDir * avoidBuffer;
        canDirect = false;
    }

    //情况3：自己和目标点都在区域外，且分居区域两侧，将自己尽可能向靠近目标点的区域外同侧移动
    else if (obsSegment.dist2Point(startPoint) > obsRadius + avoidLength && obsSegment.dist2Point(target) > obsRadius + avoidLength && obsSegment.dist2Segment(CGeoSegment(startPoint, target)) < obsRadius + avoidLength) {
        GDebugEngine::Instance()->gui_debug_msg(startPoint, "Me Out, Target Out", 0);
        targetNew = startPoint;
        projectionPoint = target;
        CVector adjustDir2 = segVec.unit();
        CVector me2Target = target - startPoint;
        if (fabs(fabs(Utils::Normalize(me2Target.dir() - adjustDir2.dir())) - Param::Math::PI / 2) < CAN_PASS_ANGLE) return target;
        if (adjustDir2 * me2Target < 0)
            adjustDir2 = -adjustDir2;
        while (me2Target * adjustDir2 > 0) {
            targetNew = targetNew + adjustDir2 * adjustStep;
            me2Target = target - targetNew;
        }
        if (obsSegment.dist2Point(targetNew) > obsRadius + avoidLength + adjustStep) {
            if (obsSegment.dist2Point(targetNew + adjustDir) < obsSegment.dist2Point(targetNew)) {
                targetNew = targetNew + adjustDir * (obsSegment.dist2Point(targetNew) - obsRadius - avoidLength - adjustStep);
            }
            else {
                targetNew = targetNew + (-adjustDir) * (obsSegment.dist2Point(targetNew) - obsRadius - avoidLength - adjustStep);
            }
        }

    }

    //情况4：自己在区域内，目标在区域外，新目标点为目标点向自己方向移动的区域边界对应点
    else if (obsSegment.dist2Point(startPoint) < obsRadius + avoidLength && obsSegment.dist2Point(target) > obsRadius + avoidLength) {
        GDebugEngine::Instance()->gui_debug_msg(startPoint, "Me In, Target Out", 0);
        targetNew = target;
        projectionPoint = startPoint;
        CVector adjustDir2 = segVec.unit();
        CVector target2Me = startPoint - targetNew;
        if (fabs(fabs(Utils::Normalize(target2Me.dir() - adjustDir2.dir())) - Param::Math::PI / 2) < CAN_PASS_ANGLE) return target;
        if (adjustDir2 * target2Me < 0)
            adjustDir2 = -adjustDir2;
        while (target2Me * adjustDir2 > 0) {
            targetNew = targetNew + adjustDir2 * adjustStep;
            target2Me = startPoint - targetNew;
        }
        if (obsSegment.dist2Point(targetNew) > obsRadius + avoidLength + adjustStep) {
            if (obsSegment.dist2Point(targetNew + adjustDir) < obsSegment.dist2Point(targetNew))
                targetNew = targetNew + adjustDir * (obsSegment.dist2Point(targetNew) - obsRadius - avoidLength - adjustStep);
            else
                targetNew = targetNew + (-adjustDir) * (obsSegment.dist2Point(targetNew) - obsRadius - avoidLength - adjustStep);
        }
    }
    return targetNew;
}
