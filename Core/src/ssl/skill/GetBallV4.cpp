
/********************************************************************/
/* GetBallV4

    建议搭配Dribble食用
    受不了了一拳打爆GetBall

        by TanYuhong  2023.5.7
/********************************************************************/

#include "GetBallV4.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "skill/Factory.h"
#include <utils.h>
#include <WorldModel/DribbleStatus.h>
#include "BallSpeedModel.h"
#include <RobotSensor.h>
#include <WorldModel/KickStatus.h>
#include <WorldModel.h>
#include <TaskMediator.h>
#include "MotionControl/CMmotion.h"


namespace {
    // 状态执行查看器 TODO

    // 需要用到的常量
    const double newVehicleBuffer = 0.6;               // 小嘴巴机器人PLAYER_FRONT_TO_CENTER补偿
    const double ballPredictBaseTime = 0.2;            // 球预测的基础时间
    const double SpeedLimitForPredictTime = 120;       // 球在该速度以上则加大预测时间
    const double nearBallRadius = 12;                  // 小车半径+球半径+2~3视频误差裕度,判定是否需要AVOIDBALL的半径
    double ball2myheadLimit = 3;                       // 小嘴巴车嘴长7cm，球半径2cm，想要稳定拿住球需要(7-2)/2=2.5cm 再加1.0的余值
    const double directGetBallDist = 20;               // 直接冲上去拿球的距离
    const double avoidBallSuccessDist = 25;            // 判定避球成功的距离 25
    const double minGetBallDist = 17;                  // 最小拿球距离 17
    const double maxGetBallDist = 25;				   // 最大拿球距离 25
    const double AllowFaceToFinalDist = 200;           // 进入该距离后开始转向
    const double transverseBallSpeed = 20;             // 对拿球产生影响的最低横向球速 ori：30
    const bool Allow_Start_Dribble = true;             // 控球控制阈值
    const double DribbleLevel = 3;                     // 控球力度等级	
    const double extremeAngle = Param::Math::PI/* * 176 / 180.0*/;
    const double directGetBballDirLimit = Param::Math::PI / 20.0;
    const int maxFrared = 125;	//红外极大值
    const int MaxRotateCnt = 100;

    // 开关量
    bool DEBUG_ENGINE = false;                          // 调试模式
    bool IS_DRIBBLE = false;                            // 吸球
    const bool USE_BALL_SPEED_MODEL = false;            // 应用球速模型

    //用到的静态变量
    bool trueNeedAvoidBall = false;
    int avoidBallCount = 0;
    int fraredOn = 0;
    int fraredOff = 0;
    double GETBALL_BIAS = -2.5; // 原来是2.5
    double BALL_NEAR_ROBOT = 20;

    double roll_acc = 200;
    double slide_acc = 500;
    double transition_speed = 400;

    double HEAD_LIMIT = 3;
}

CGetBallV4::CGetBallV4()
{
    GETBALL_BIAS = ParamManager::Instance()->GETBALL_BIAS;
    BALL_NEAR_ROBOT = ParamManager::Instance()->BALL_NEAR_ROBOT;
    HEAD_LIMIT = ParamManager::Instance()->HEAD_LIMIT;
    DEBUG_ENGINE = ParamManager::Instance()->GetBall_Debug;
    IS_DRIBBLE = ParamManager::Instance()->IS_DRIBBLE;

    roll_acc = ParamManager::Instance()->roll_acc;
    slide_acc = ParamManager::Instance()->slide_acc;
    transition_speed = ParamManager::Instance()->transition_speed;

    _lastCycle = 0;
}

void CGetBallV4::plan(const CVisionModule* pVision)
{
    ball2myheadLimit = HEAD_LIMIT;
    // 内部状态进行重置
    if (pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1) {
        setState(BEGINNING);
        trueNeedAvoidBall = false;
        avoidBallCount = 0;
    }

    const BallVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const CGeoPoint myhead = me.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer, me.Dir());
    const CVector self2ball = ball.Pos() - me.Pos();
    const CVector ball2self = me.Pos() - ball.Pos();
    const CVector head2ball = ball.Pos() - myhead;

    const double StopDist = task().player.rotvel;
    //	cout << "StopDist:\t" << StopDist << endl;


    double finalDir = task().player.angle;
    double reverse_finalDir = Utils::Normalize(finalDir + Param::Math::PI);


    // 是否开启debug模式
    if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_line(me.Pos(), me.Pos() + Utils::Polar2Vector(1000, finalDir), COLOR_RED);
    if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_line(me.Pos(), me.Pos() + Utils::Polar2Vector(1000, self2ball.dir()), COLOR_PURPLE);

    double BallPosWithVelFactorTmp = ballPredictBaseTime;

    double dAngle_ball2myhead_ballvel = Utils::Normalize(Utils::Normalize(head2ball.dir() + Param::Math::PI) - ball.Vel().dir());
    double dAngle_self2ball_medir = Utils::Normalize(self2ball.dir() - me.Dir());
    double dAngle_finalDir2ballVel = Utils::Normalize(finalDir - ball.Vel().dir());

    // 球在车正前方对球预测时间的影响，考虑红外
    bool frared = RobotSensor::Instance()->IsInfraredOn(robotNum);

    // 带有小缓存功能的红外
    if (frared) {
        fraredOn = fraredOn >= maxFrared ? maxFrared : fraredOn + 1;
        fraredOff = 0;
    }
    else {
        fraredOn = 0;
        fraredOff = fraredOff >= maxFrared ? maxFrared : fraredOff + 1;
    }

    CVector ballVel = ball.Vel();
    /********************************************************************/
    /* 预测BallPosWithVelFactorTmp时间之后的球位置  by lsp */
    /********************************************************************/
    CGeoPoint ballPosWithVel = CGeoPoint(0, 0);
    if (me.Pos().dist(ball.Pos()) < BALL_NEAR_ROBOT || ballVel.mod() < 70) {
        ballPosWithVel = ball.Pos();
        GDebugEngine::Instance()->gui_debug_msg(ballPosWithVel, "too slow ball");
    }
    else {
        // 粗略计算预测球的位置
        // 修改了拿球的预测时间，从三个角度考虑，车到球运动轨迹的距离，车的朝向，车的运动速度
        CGeoLine ball_line(ball.Pos(), ball.Pos() + ballVel);
        CGeoPoint projection_point = ball_line.projection(me.Pos());
        double projection2me_dist = projection_point.dist(me.Pos());
        double angle_diff = Param::Math::PI - abs(abs(me.Dir()) - abs(ballVel.dir()));
        if (me.Vel().mod() > 20) {
            double vel_dir = me.Vel().dir();
            double vel_dir_diff = abs(vel_dir - (projection_point - me.Pos()).dir());
            BallPosWithVelFactorTmp += (vel_dir_diff - Param::Math::PI / 2) / 8;
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 0), QString("vel dir diff time:%5").arg((vel_dir_diff - Param::Math::PI / 2) / 5).toStdString().c_str());
        }

        BallPosWithVelFactorTmp += projection2me_dist / 400;
        BallPosWithVelFactorTmp += angle_diff / 15;

        // 粗略计算预测球的位置
        if (ballVel.mod() < transition_speed) {
            if (ballVel.mod() / roll_acc < BallPosWithVelFactorTmp) {
                ballPosWithVel = ball.Pos() + ballVel.unit() * (ballVel.mod() * BallPosWithVelFactorTmp - 0.5 * roll_acc * BallPosWithVelFactorTmp * BallPosWithVelFactorTmp);
                GDebugEngine::Instance()->gui_debug_msg(ballPosWithVel, QString("short roll ball, time:%5").arg(BallPosWithVelFactorTmp).toStdString().c_str());
            }
            else {
                ballPosWithVel = ball.Pos() + ballVel.unit() * (ballVel.mod2() / roll_acc * 0.5);
                GDebugEngine::Instance()->gui_debug_msg(ballPosWithVel, QString("long roll ball, time:%5").arg(BallPosWithVelFactorTmp).toStdString().c_str());
            }
        }
        else {
            float time2roll = (ballVel.mod() - transition_speed) / slide_acc;
            float timeslide = transition_speed / roll_acc;
            if (BallPosWithVelFactorTmp < time2roll) {
                ballPosWithVel = ball.Pos() + ballVel.unit() * (ballVel.mod() * BallPosWithVelFactorTmp - 0.5 * slide_acc * BallPosWithVelFactorTmp * BallPosWithVelFactorTmp);
            }
            else if (BallPosWithVelFactorTmp < time2roll + timeslide) {
                float slide_dist = (ballVel.mod2() - transition_speed * transition_speed) / slide_acc * 0.5;
                float roll_time = BallPosWithVelFactorTmp - time2roll;
                float roll_dist = transition_speed * roll_time - 0.5 * roll_acc * roll_time * roll_time;
                ballPosWithVel = ball.Pos() + ballVel.unit() * (roll_dist + slide_dist);
            }
            else {
                float slide_dist = (ballVel.mod2() - transition_speed * transition_speed) / slide_acc * 0.5;
                float roll_dist = transition_speed * transition_speed / roll_acc * 2;
                ballPosWithVel = ball.Pos() + ballVel.unit() * (roll_dist + slide_dist);
            }
            GDebugEngine::Instance()->gui_debug_msg(ballPosWithVel, "slide ball");
        }
    }
    if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_arc(ballPosWithVel, 20, 0, 360, COLOR_YELLOW);


    TaskT getball_task(task());
    getball_task.player.rotvel = 0.0;
    getball_task.player.needdribble = false;

    // 标签设置说明如下
    /*
    拿球标签: PlayerStatus::GOTO_GRASP_BALL	 --> 不管调用该任务的上层是否有设置，都强行予以设置，表征拿球
    避球标签: PlayerStatus::DODGE_BALL		 --> 不管调用该任务的上层是否有设置，都强行不予设置，表征不避球
    控球标签: PlayerStatus::DRIBBLING		 --> 结合上层决定是否开启控球
    */
    getball_task.player.flag = getball_task.player.flag | PlayerStatus::DODGE_OUR_DEFENSE_BOX;//躲避我方禁区!!
    getball_task.player.flag = getball_task.player.flag;	//设置拿球标签
    getball_task.player.flag = getball_task.player.flag & (~PlayerStatus::DODGE_BALL);		//取消避球标签
    if (!(getball_task.player.flag & PlayerStatus::DRIBBLING))
        getball_task.player.flag = getball_task.player.flag & (~PlayerStatus::DRIBBLING);	//取消控球标签
    getball_task.player.flag |= PlayerStatus::ALLOW_DSS;

    const CGeoLine myheadLine = CGeoLine(myhead, Utils::Normalize(me.Dir() + Param::Math::PI / 2.0));
    const CGeoPoint ball2myheadLine_ProjPoint = myheadLine.projection(ballPosWithVel);
    double dAngDiff_self2ball_finaldir = fabs(Utils::Normalize(self2ball.dir() - finalDir));
    bool isBallFrontOfMyhead = myhead.dist(ball2myheadLine_ProjPoint) < ball2myheadLimit ? true : false;  //球到嘴巴线的投影点在可以拿球的范围内
    bool isInDirectGetBallCircle = me.Pos().dist(ballPosWithVel) < directGetBallDist ? true : false;     //是否在直接冲上去拿球距离之内
    bool isGetBallDirReached = fabs(dAngDiff_self2ball_finaldir) < directGetBballDirLimit;
    bool isCanDirectGetBall = isBallFrontOfMyhead && isInDirectGetBallCircle && isGetBallDirReached;      //重要布尔量:是否能直接上前拿球
    bool dirOut = fabs(dAngDiff_self2ball_finaldir) > Param::Math::PI / 18.0;
    bool canNOTDirectGetBall = !isBallFrontOfMyhead || !isInDirectGetBallCircle || dirOut;
    bool isInNearBallCircle = me.Pos().dist(ball.Pos()) < nearBallRadius ? true : false;                 //是否在AVOIDBALL小圈之内
    bool isBallBesideMe = false;
    bool isBallBehindMe = false;
    if (isInNearBallCircle)
    {
        if (canNOTDirectGetBall)
        {
            if (fabs(dAngDiff_self2ball_finaldir) > Param::Math::PI / 2.0)
            {
                isBallBehindMe = true;
            }
            else isBallBesideMe = true;
        }
    }
    /*
    double diffAngleVel2Final = fabs(dAngDiff_self2ball_finaldir);
    int sign = diffAngleVel2Final > Param::Math::PI / 2.0 ? 1 : 0;
    if (ball.Pos().dist(me.Pos()) > AllowFaceToFinalDist)
        getball_task.player.angle = Utils::Normalize(self2ball.dir() + sign * Param::Math::PI);
    else getball_task.player.angle = finalDir;
    */
    getball_task.player.angle = finalDir;
    int _executor = robotNum;
    double ball2meDist = ball2self.mod();
    switch (_state)
    {
    case BEGIN:
        if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.3) _state = HAVE;
        else _state = LARGE;
        break;
    case LARGE:
        if (LARGECanToROTATE(pVision, finalDir)) _state = ROTATE;
        break;
    case ROTATAE:
        if (ROTATECanToDIRECT(pVision, finalDir) || _RotateCnt > MaxRotateCnt) _state = DIRECT;
        if (WeMustReturnLARGE(pVision, finalDir)) _state = LARGE;
        break;
    case DIRECT:
        if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.3) _state = HAVE;
        else if (WeMustReturnLARGE(pVision, finalDir)) _state = LARGE;
        break;
    case HAVE:
        if (BallStatus::Instance()->getBallPossession(true, _executor) == 0 && ball2meDist > 10) _state = LARGE;
        if ((BallStatus::Instance()->getBallPossession(true, _executor) > 0.3) && MustUseLargeToAdjust(pVision, _executor, finalDir) == 1) _state = LEAVEBACK;
        break;
    
    case LEAVEBACK:
        if (BallStatus::Instance()->getBallPossession(true, _executor) == 0 && ball2meDist > minGetBallDist) _state = LARGE;
        break;
    }

    char state[100];
    sprintf(state, "%f", (double)_state);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 0), state, COLOR_YELLOW);
    if (_state != ROTATE) _RotateCnt = 0;
    else _RotateCnt++;

    switch (_state)
    {
    case LARGE:
        getball_task.player.pos = GenerateLargeAnglePoint(pVision, finalDir, 0);
        if (pVision->GetCurrentRefereeMsg() == "ourIndirectKick" || pVision->GetCurrentRefereeMsg() == "ourDirectKick" || pVision->GetCurrentRefereeMsg() == "ourKickOff")
            getball_task.player.flag = getball_task.player.flag | (PlayerStatus::DODGE_BALL);
        break;

    case ROTATAE:
        getball_task.player.pos = me.Pos();
        getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
        getball_task.player.needdribble = IS_DRIBBLE;
        break;
    case DIRECT:
        getball_task.player.pos = Ball_Predict_Pos(pVision) + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer + Param::Field::BALL_SIZE + StopDist + GETBALL_BIAS, reverse_finalDir); // 预测球的位置 + 5.85     
        getball_task.player.angle = (ball.Pos() - me.Pos()).dir();

        getball_task.player.needdribble = IS_DRIBBLE;
        break;
    case HAVE:
        getball_task.player.pos = me.Pos();
        getball_task.player.angle = finalDir;
        getball_task.player.needdribble = IS_DRIBBLE;
        break;

    case LEAVEBACK:
        getball_task.player.pos = Ball_Predict_Pos(pVision) + Utils::Polar2Vector(20, Utils::Normalize((ball.Pos() - me.Pos()).dir()) + Param::Math::PI); // 预测球的位置 + 5.85     
        getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
        getball_task.player.needdribble = 0;
        getball_task.player.flag = getball_task.player.flag & (~PlayerStatus::DRIBBLING);	//取消控球标签
        break;
    }
    // 调用底层控制
    CTRL_METHOD mode = task().player.specified_ctrl_method;
    getball_task.player.is_specify_ctrl_method = true;
    getball_task.player.specified_ctrl_method = mode;
    setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(getball_task));

    _lastCycle = pVision->Cycle();
    CStatedTask::plan(pVision);
}




CPlayerCommand* CGetBallV4::execute(const CVisionModule* pVision)
{
    if (subTask()) {
        return subTask()->execute(pVision);
    }
    return NULL;
}




//--------------------------------------------//
//--------------------------------------------//
//-------用GPUBestAlgThread预测球的位置-------//
//--------------------------------------------//
//--------------------------------------------//
CGeoPoint CGetBallV4::PredictForBall(int frame, const CVisionModule* pVision) //用GPUBestAlgThread获得球的位置
{
    CGeoPoint Point;
    
    const BallVisionT& ball = pVision->Ball();
     Point = GPUBestAlgThread::Instance()->getBallPosFromFrame(ball.Pos(), ball.Vel(), frame);
    

    //Point = BallSpeedModel::Instance()->posForTime(frame, pVision);
    return Point;
}

int CGetBallV4::PredictForRobot(CGeoPoint point, const CVisionModule* pVision)//机械人到球预测位置的时间
{
    const int Robotnum = task().executor;
    PlayerCapabilityT capability;
    const PlayerVisionT& Robot = pVision->OurPlayer(Robotnum);

    const bool isGoalie = (Robotnum == TaskMediator::Instance()->goalie());
    const bool isBack = (Robotnum == TaskMediator::Instance()->leftBack()) ||
        (Robotnum == TaskMediator::Instance()->rightBack()) ||
        (Robotnum == TaskMediator::Instance()->singleBack()) ||
        (Robotnum == TaskMediator::Instance()->sideBack()) ||
        (Robotnum == TaskMediator::Instance()->defendMiddle());
    const bool isMultiBack = TaskMediator::Instance()->isMultiBack(Robotnum);

    // 底层控制方法参数
    double SLOW_FACTOR = 0.5;

    // 底层运动控制参数 ： 默认增大平动的控制性能
    double MAX_TRANSLATION_SPEED = 200;
    double MAX_TRANSLATION_ACC = 200;
    double MAX_TRANSLATION_DEC = 200;

    double TRANSLATION_ACC_LIMIT = 200;
    double TRANSLATION_SPEED_LIMIT = 200;

    /// 守门员专用
    double MAX_TRANSLATION_SPEED_GOALIE = 200;
    double MAX_TRANSLATION_ACC_GOALIE = 200;
    double MAX_TRANSLATION_DEC_GOALIE = 200;

    /// 后卫专用
    double MAX_TRANSLATION_SPEED_BACK = 200;
    double MAX_TRANSLATION_ACC_BACK = 200;
    double MAX_TRANSLATION_DEC_BACK = 200;



    //----------------//
    if (Robotnum == TaskMediator::Instance()->goalie()) {
        capability.maxSpeed = MAX_TRANSLATION_SPEED_GOALIE;
    }
    else if (TaskMediator::Instance()->leftBack() != 0 && Robotnum == TaskMediator::Instance()->leftBack()
        || TaskMediator::Instance()->rightBack() != 0 && Robotnum == TaskMediator::Instance()->rightBack()
        || TaskMediator::Instance()->singleBack() != 0 && Robotnum == TaskMediator::Instance()->singleBack()
        || TaskMediator::Instance()->sideBack() != 0 && Robotnum == TaskMediator::Instance()->sideBack()
        || isMultiBack)
    {
        capability.maxSpeed = MAX_TRANSLATION_SPEED_BACK;
    }
    else
    {
        capability.maxSpeed = MAX_TRANSLATION_SPEED;
    }

    if (task().player.max_speed > 1e-8) {
        capability.maxSpeed = task().player.max_speed > TRANSLATION_SPEED_LIMIT ? TRANSLATION_SPEED_LIMIT : task().player.max_speed;
    }

    if (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop") {
        capability.maxSpeed = 140;
    }

    if (WorldModel::Instance()->CurrentRefereeMsg() == "ourBallPlacement")
    {
        capability.maxSpeed *= SLOW_FACTOR;
    }
    const double time_factor = 1.5;
    double usedtime = expectedCMPathTime(Robot, point, capability, CVector(0, 0), time_factor, 0);
    double frame = usedtime * 60;
    char msg[100];
    sprintf(msg, "%f", frame);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(260, 260), msg, COLOR_YELLOW);

    return frame;
}

CGeoPoint CGetBallV4::GenerateLargeAnglePoint(const CVisionModule* pVision, const double finalDir, const bool debug) {
    const BallVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const CGeoPoint myhead = me.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer, me.Dir());
    const CVector self2ball = ball.Pos() - me.Pos();
    const CVector ball2self = me.Pos() - ball.Pos();
    const CVector head2ball = ball.Pos() - myhead;
    double theta_Dir = ball2self.dir();
    int sign = Utils::Normalize((theta_Dir - finalDir)) > 0 ? 1 : -1;
    theta_Dir = Utils::Normalize(theta_Dir + sign * Param::Math::PI * 65 / 180.0); //Param::Math::PI * 75 / 180.0
    if (ball.Vel().mod() * sin(fabs(Utils::Normalize(ball.Vel().dir() - finalDir))) < transverseBallSpeed)//球速相对目标方向较小的时候
    {
        if (fabs(Utils::Normalize(theta_Dir - finalDir)) > extremeAngle)
        {
            if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(me.Pos() + CVector(0, 50), "extreme angle", COLOR_WHITE);
            theta_Dir = Utils::Normalize(finalDir + sign * extremeAngle);
        }
    }
    //距离计算
    //if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_line(me.Pos(), me.Pos() + Utils::Polar2Vector(1000, theta_Dir), COLOR_WHITE);
    double theta = fabs(Utils::Normalize(theta_Dir - finalDir));
    double getBallDist = minGetBallDist + (maxGetBallDist - minGetBallDist) * (1 + cos(theta));
    if (getBallDist > maxGetBallDist)
    {
        getBallDist = maxGetBallDist;
    }
    CGeoPoint target = Ball_Predict_Pos(pVision) + Utils::Polar2Vector(getBallDist, theta_Dir);
    if (ball.Vel().mod() < 15) {
        CGeoLine JudgeLine1 = CGeoLine(ball.Pos(), finalDir);
        CGeoLine JudgeLine2 = CGeoLine(me.Pos(), target);
        CGeoLineLineIntersection LineIntersection = CGeoLineLineIntersection(JudgeLine1, JudgeLine2);
        if (LineIntersection.Intersectant()) {
            CGeoPoint Intersection = LineIntersection.IntersectPoint();
            CGeoSegment JudgeSegment = CGeoSegment(me.Pos(), target);
            if (JudgeSegment.IsPointOnLineOnSegment(Intersection)) {
                target = Ball_Predict_Pos(pVision) + Utils::Polar2Vector(getBallDist, Utils::Normalize(finalDir + Param::Math::PI));
            }
        }
    }
    else {
        if((ball.Pos() - me.Pos()).theta(ball.Vel()) < Param::Math::PI * 60 / 180.0)
            target = Ball_Predict_Pos(pVision) + Utils::Polar2Vector(getBallDist, Utils::Normalize(finalDir + Param::Math::PI));
        else target = Ball_Predict_Pos(pVision) + Utils::Polar2Vector(getBallDist, ball.Vel().dir());
    }
    //cout << "GETBALLDIST:   " << getBallDist << "MOD:   " << (target - me.Pos()).mod() << endl;

    bool DEBUG_ENGINE = debug;
    if (DEBUG_ENGINE) {
        CVector self2ball = ball.Pos() - me.Pos();
        CVector self2target = target - me.Pos();
        char getBallDistdebugmsg[100];
        char moddebugmsg[100];
        char balldebugmsg[100];
        char thetadebugmsg[100];
        sprintf(getBallDistdebugmsg, "%f", getBallDist);
        sprintf(moddebugmsg, "%f", (target - me.Pos()).mod());
        sprintf(balldebugmsg, "%f", (ball.Pos() - me.Pos()).mod());
        sprintf(thetadebugmsg, "%f", self2ball.theta(self2target) / Param::Math::PI * 180);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-320, -350), getBallDistdebugmsg, COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-320, -300), moddebugmsg, COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-320, -250), balldebugmsg, COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-320, -200), thetadebugmsg, COLOR_YELLOW);

    }

    return target;
}
bool CGetBallV4::JudgeLargeBack(const CVisionModule* pVision, CGeoPoint target) {
    const BallVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    CVector self2ball = ball.Pos() - me.Pos();
    CVector self2target = target - me.Pos();
    if (fabs(self2ball.theta(self2target)) > Param::Math::PI * 0.5)return true;
    return false;
}
CGeoPoint CGetBallV4::Ball_Predict_Pos(const CVisionModule* pVision)//返回最佳的点
{
    CGeoPoint point;
    int FrameMin = 1, FrameMax = 200, FramePerfect = 200;
    while (FrameMin <= FrameMax)
    {
        int mid = (FrameMin + FrameMax) / 2;
        int TmpTime = PredictForRobot(PredictForBall(mid, pVision), pVision);

        if (TmpTime <= mid)
        {
            FrameMax = mid - 1;
            FramePerfect = mid;
        }
        else
        {
            FrameMin = mid + 1;
        }
    }
    const BallVisionT& ball = pVision->Ball();
    if(ball.Vel().mod() > 20) 
        point = PredictForBall(FramePerfect + 10, pVision);
    else  point = PredictForBall(FramePerfect, pVision);
    return point;
}

bool CGetBallV4::LARGECanToROTATE(const CVisionModule* pVision, const double finalDir)
{
    CGeoPoint LargeTarget = GenerateLargeAnglePoint(pVision, finalDir, 0);
    const BallVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    if (ball.Vel().mod() < 20 && (LargeTarget - me.Pos()).mod() < 5) return 1;
    return 0;
}
bool CGetBallV4::ROTATECanToDIRECT(const CVisionModule* pVision, const double finalDir)
{
    const BallVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const CVector self2ball = ball.Pos() - me.Pos();
    if (fabs(Utils::Normalize(finalDir - me.Dir())) < Param::Math::PI * 8 / 180.0) return 1;
    return 0;
}
bool CGetBallV4::WeMustReturnLARGE(const CVisionModule* pVision, const double finalDir)
{
    const BallVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const CVector self2ball = ball.Pos() - me.Pos();
    double ball2meDist = self2ball.mod();
    // cout << ball2meDist << endl;
    if (ball.Vel().mod() > 30 || ball2meDist > 30)
        return 1;
    return 0;
}
bool CGetBallV4::MustUseLargeToAdjust(const CVisionModule* pVision, const int _executor, const double finalDir){
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(_executor);
    if (fabs(Utils::Normalize(finalDir - me.Dir())) > Param::Math::PI * 20 / 180.0) return 1;
    else return 0;
}



