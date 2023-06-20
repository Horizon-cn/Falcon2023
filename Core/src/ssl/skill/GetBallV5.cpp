/********************************************************************/
/* GetBallV4

    建议搭配Dribble食用
    受不了了一拳打爆GetBall

        by TanYuhong  2023.5.7
/********************************************************************/

#include "GetBallV5.h"
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
    const int MaxRotateCnt = 200;
    const int MaxLargeCnt = 100;
    //lsf 6/19
    const int DRIBBLE_DIST = 80;
    bool get_ball_last_frame = false;
    // 开关量
    bool DEBUG_ENGINE = false;                          // 调试模式
    bool IS_DRIBBLE = false;                            // 吸球
    const bool USE_BALL_SPEED_MODEL = false;            // 应用球速模型

    //用到的静态变量
    double GETBALL_BIAS = -2.5; // 原来是2.5
    double BALL_NEAR_ROBOT = 20;

    double roll_acc = 200;
    double slide_acc = 500;
    double transition_speed = 400;
    double LARGE_ADJUST_ANGLE = 20;

    double HEAD_LIMIT = 3;

    CGeoPoint theirCenter = CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0);
    CGeoPoint begin_dribble;
}

CGetBallV5::CGetBallV5()
{
    GETBALL_BIAS = ParamManager::Instance()->GETBALL_BIAS;
    BALL_NEAR_ROBOT = ParamManager::Instance()->BALL_NEAR_ROBOT;
    HEAD_LIMIT = ParamManager::Instance()->HEAD_LIMIT;
    DEBUG_ENGINE = ParamManager::Instance()->GetBall_Debug;
    IS_DRIBBLE = ParamManager::Instance()->IS_DRIBBLE;

    roll_acc = ParamManager::Instance()->roll_acc;
    slide_acc = ParamManager::Instance()->slide_acc;
    transition_speed = ParamManager::Instance()->transition_speed;
    LARGE_ADJUST_ANGLE = ParamManager::Instance()->LARGE_ADJUST_ANGLE;
    GetBall_Precision_alpha = ParamManager::Instance()->GetBall_Precision_alpha;

    OPP_HAS_BALL_DIST = ParamManager::Instance()->OPP_HAS_BALL_DIST; 
    _lastCycle = 0;
}

void CGetBallV5::plan(const CVisionModule* pVision)
{
    ball2myheadLimit = HEAD_LIMIT;
    // 内部状态进行重置
    if (pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1) {
        setState(BEGINNING);
    }

    const BallVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const CGeoPoint myhead = me.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer, me.Dir());
    const CVector self2ball = ball.Pos() - me.Pos();
    const CVector ball2self = me.Pos() - ball.Pos();

    const double StopDist = task().player.rotvel;
    //	cout << "StopDist:\t" << StopDist << endl;

    opponentID = getTheirMostClosetoPosPlayerNum(pVision, pVision->Ball().Pos());
    const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
    double finalDir = task().player.angle;
    double reverse_finalDir = Utils::Normalize(finalDir + Param::Math::PI);



    CVector ballVel = ball.Vel();

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


    getball_task.player.angle = finalDir;
    int _executor = robotNum;
    double ball2meDist = ball2self.mod();

    bool HasSetSubtask = false;
    bool DEBUG_ENGINE = 1;
    if (DEBUG_ENGINE) {
        CVector self2ball = ball.Pos() - me.Pos();

        char have[100];
        char deltaBall[100];
        char deltaTheta[100];
        char velmsg[100];
        //sprintf(getBallDistdebugmsg, "%f", getBallDist);
        sprintf(have, "%f", BallStatus::Instance()->getBallPossession(true, _executor));
        sprintf(deltaBall, "%f", self2ball.mod());
        sprintf(deltaTheta, "%f", Utils::Normalize(self2ball.dir() - me.Dir()) * 180 / Param::Math::PI);
        sprintf(velmsg, "%f", ball.Vel().mod());

        //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-320, -350), getBallDistdebugmsg, COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-320, -300), have, COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-320, -250), deltaTheta, COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-320, -200), deltaBall, COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-320, -150), velmsg, COLOR_YELLOW);


    }
    if (BallStatus::Instance()->getBallPossession(true, _executor) <= 0.3)
        get_ball_last_frame = false;

    if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.3 && get_ball_last_frame == false)
    {
        get_ball_last_frame = true;
        begin_dribble = CGeoPoint(me.X(), me.Y());
    }
    else if(BallStatus::Instance()->getBallPossession(true, _executor) > 0.3 && get_ball_last_frame == true && sqrt(pow(begin_dribble.x() - me.X(), 2) + pow(begin_dribble.y() - me.Y(), 2)) > DRIBBLE_DIST)
        {
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -345), "KICK", COLOR_YELLOW);
            KickStatus::Instance()->setBothKick(_executor, 0, 600);
        }
        

    char havemsg[100];
    if (checkOppHasBall(pVision)) { // 敌人拿到了球
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -245), "The opponent gets the ball", COLOR_YELLOW);
        const CVector opp2ball = (ball.Pos() - opp.Pos());
        if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.3) { //我拿到球了
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -225), "I get the ball", COLOR_YELLOW);
            getball_task.player.pos = me.Pos() + Utils::Polar2Vector(maxGetBallDist, Utils::Normalize((me.Pos() - ball.Pos()).dir())); // 预测球的位置 + 5.85     这个长度越大离球越远
            getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
        }
        else { //我没拿到球
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -225), "I don't get the ball", COLOR_YELLOW);
            if ( fabs((ball.Pos() - opp.Pos()).theta(me.Pos() - ball.Pos())) > Param::Math::PI * 20 / 180) {
                getball_task.player.pos = ball.Pos() + Utils::Polar2Vector(maxGetBallDist, Utils::Normalize((ball.Pos() - opp.Pos()).dir())); // 预测球的位置 + 5.85     这个长度越大离球越远
                getball_task.player.angle = (opp.Pos() - ball.Pos()).dir();
            }
            else {
                getball_task.player.pos = ball.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer + Param::Field::BALL_SIZE + StopDist + GETBALL_BIAS, Utils::Normalize((ball.Pos() - opp.Pos()).dir()));
                getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
            }
        }
        getball_task.player.needdribble = IS_DRIBBLE;
    }
    else if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.3) { // 我已经拿到球了
        double slowfactor = 1;
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -225), "I get the ball", COLOR_YELLOW);
        if (fabs(me.Dir() - finalDir) < 0.03)
            getball_task.player.pos = ball.Pos();// me.Pos();
        else 
            getball_task.player.pos = GenerateLargeAnglePoint(pVision, finalDir, 0);

        if (fabs(me.Dir() - finalDir) > Param::Math::PI * 60 / 180) {
            getball_task.player.max_acceleration = getball_task.player.max_deceleration = 650;
            getball_task.player.max_rot_acceleration = 15 * slowfactor;
            getball_task.player.max_deceleration = 15 * slowfactor;
        }
        else if (fabs(me.Dir() - finalDir) < Param::Math::PI * 20 / 180) {
            getball_task.player.max_acceleration = getball_task.player.max_deceleration = 300;
            getball_task.player.max_rot_acceleration = 6 * slowfactor;
            getball_task.player.max_deceleration = 6 * slowfactor;
        }

        getball_task.player.angle = finalDir;
        getball_task.player.needdribble = !IS_DRIBBLE;

        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-250, 0), havemsg, COLOR_YELLOW);
    }
    else if (ball.Vel().mod() > 30) { // 动态状态下
        
        bool IsFast = (ball.Vel().mod() >= 150);
        bool IsMedium = (ball.Vel().mod() >= 50 && ball.Vel().mod() < 150);
        bool IsSlow = (ball.Vel().mod() < 50);
        bool IsBehind = (fabs(Utils::Normalize((ball.Pos() - me.Pos()).dir() - ball.Vel().dir())) < Param::Math::PI * 60 / 180);

        if (IsFast) {
            CGeoPoint expectedGetPos = Ball_Predict_Pos(pVision);
            bool IsMyPosIsOK = (fabs(Utils::Normalize((me.Pos() - ball.Pos()).dir() - ball.Vel().dir())) < Param::Math::PI * 1.5 / 180);
            bool IsMyDirIsOK = (fabs(Utils::Normalize((ball.Pos() - me.Pos()).dir() - me.Dir())) < Param::Math::PI * 1.55 / 180);
            if (IsMyPosIsOK && IsMyDirIsOK) {
                getball_task.player.pos = ball.Pos() + Utils::Polar2Vector(-Param::Field::BALL_SIZE, Utils::Normalize((me.Pos() - ball.Pos()).dir())); // 预测球的位置 + 5.85     这个长度越大离球越远
                getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
                getball_task.player.needdribble = IS_DRIBBLE;
            }
            else {
                getball_task.player.pos = expectedGetPos;
                getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
            }
        }
        else if (IsMedium) {
            CGeoPoint expectedGetPos = Ball_Predict_Pos(pVision);
            if (IsBehind) {
                bool IsMyPosIsOK = (fabs(Utils::Normalize((me.Pos() - ball.Pos()).dir() - ball.Vel().dir())) < Param::Math::PI * 1.5 / 180);
                bool IsMyDirIsOK = (fabs(Utils::Normalize((ball.Pos() - me.Pos()).dir() - me.Dir())) < Param::Math::PI * 1.5 / 180);
                if (IsMyPosIsOK && IsMyDirIsOK) {
                    getball_task.player.pos = ball.Pos() + Utils::Polar2Vector(-Param::Field::BALL_SIZE, Utils::Normalize((me.Pos() - ball.Pos()).dir())); // 预测球的位置 + 5.85     这个长度越大离球越远
                    getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
                    getball_task.player.needdribble = IS_DRIBBLE;
                }
                else {
                    getball_task.player.pos = expectedGetPos;
                    getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
                }
            }
            else {
                bool IsMyPosIsOK = (fabs(Utils::Normalize((ball.Pos() - me.Pos()).dir() - ball.Vel().dir())) < Param::Math::PI * 1.5 / 180);
                bool IsMyDirIsOK = (fabs(Utils::Normalize((ball.Pos() - me.Pos()).dir() - me.Dir())) < Param::Math::PI * 1.5 / 180);
                if (IsMyPosIsOK && IsMyDirIsOK) {
                    getball_task.player.pos = ball.Pos() + ball.Vel() * 0.5;//Utils::Polar2Vector(ball.Vel().mod() * 0.5, Utils::Normalize((me.Pos() - ball.Pos()).dir())); // 预测球的位置 + 5.85     这个长度越大离球越远
                    getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
                    getball_task.player.needdribble = IS_DRIBBLE;
                }
                else {
                    getball_task.player.pos = ball.Pos();
                    getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
                }
            }
        }
        else {
            getball_task.player.pos = ball.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer + Param::Field::BALL_SIZE + StopDist + GETBALL_BIAS, Utils::Normalize((me.Pos() - ball.Pos()).dir())); // 预测球的位置 + 5.85     这个长度越大离球越远
            getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
            getball_task.player.needdribble = IS_DRIBBLE;
        }
    }
    else { // 静态状态下，没有人干扰我
        double slowfactor = 1;
        getball_task.player.pos = ball.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer + Param::Field::BALL_SIZE + StopDist + GETBALL_BIAS, Utils::Normalize((me.Pos() - ball.Pos()).dir())); // 预测球的位置 + 5.85     这个长度越大离球越远
        getball_task.player.angle = (ball.Pos() - me.Pos()).dir();
        if (fabs(me.Dir() - finalDir) > Param::Math::PI * 215 / 180) {
            getball_task.player.max_rot_acceleration = 14 * slowfactor;
            getball_task.player.max_deceleration = 14 * slowfactor;
        }
        else if (fabs(me.Dir() - finalDir) > Param::Math::PI * 135 / 180) {
            getball_task.player.max_rot_acceleration = 10 * slowfactor;
            getball_task.player.max_deceleration = 10 * slowfactor;
        }
        else if (fabs(me.Dir() - finalDir) < Param::Math::PI * 10 / 180) {
            getball_task.player.max_rot_acceleration = 3 * slowfactor;
            getball_task.player.max_deceleration = 3 * slowfactor;
        }
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-250, 0), havemsg, COLOR_YELLOW);

    }
    // 调用底层控制
    CTRL_METHOD mode = task().player.specified_ctrl_method;
    getball_task.player.is_specify_ctrl_method = true;
    getball_task.player.specified_ctrl_method = mode;

    // 是否开启debug模式
    if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_line(me.Pos(), me.Pos() + Utils::Polar2Vector(1000, finalDir), COLOR_CYAN);
    if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_line(me.Pos(), me.Pos() + Utils::Polar2Vector(1000, getball_task.player.angle), COLOR_RED);
    if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_line(me.Pos(), me.Pos() + Utils::Polar2Vector(1000, me.Dir()), COLOR_PURPLE);
    if ((me.Pos() - ball.Pos()).mod() < 75)
        getball_task.player.needdribble = IS_DRIBBLE;
    else getball_task.player.needdribble = !IS_DRIBBLE;
    getball_task.player.IsGetBaller = true;
    
    setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(getball_task));
    //setSubTask(PlayerRole::makeItStop(_executor, 0));
    _lastCycle = pVision->Cycle();
    CStatedTask::plan(pVision);
}




CPlayerCommand* CGetBallV5::execute(const CVisionModule* pVision)
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
CGeoPoint CGetBallV5::PredictForBall(int frame, const CVisionModule* pVision) //用GPUBestAlgThread获得球的位置
{
    CGeoPoint Point;
    
    const BallVisionT& ball = pVision->Ball();
     Point = GPUBestAlgThread::Instance()->getBallPosFromFrame(ball.Pos(), ball.Vel(), frame);
    

    //Point = BallSpeedModel::Instance()->posForTime(frame, pVision);
    return Point;
}

int CGetBallV5::PredictForRobot(CGeoPoint point, const CVisionModule* pVision)//机械人到球预测位置的时间
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
    capability.maxAccel = capability.maxDec = 200;
    const double time_factor = 1.5;
    double usedtime = expectedCMPathTime(Robot, point, capability, CVector(0, 0), time_factor, 0);
    //cout << usedtime << endl;
    double frame = usedtime * 60;
    char msg[100];
    sprintf(msg, "%f", frame);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(260, 260), msg, COLOR_YELLOW);

    return frame;
}

CGeoPoint CGetBallV5::GeneratePoint(const CVisionModule* pVision, double finalDir, const bool debug) {

    CGeoPoint target = Ball_Predict_Pos(pVision);
    return target;
}
bool CGetBallV5::JudgeLargeBack(const CVisionModule* pVision, CGeoPoint target) {
    const BallVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    CVector self2ball = ball.Pos() - me.Pos();
    CVector self2target = target - me.Pos();
    if (fabs(self2ball.theta(self2target)) > Param::Math::PI * 0.5)return true;
    return false;
}
CGeoPoint CGetBallV5::Ball_Predict_Pos(const CVisionModule* pVision)//返回最佳的点
{
    const BallVisionT& ball = pVision->Ball();
    if (ball.Vel().mod() < 5)
        return ball.Pos();
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
    point = PredictForBall(FramePerfect, pVision);
    return point;
}

bool CGetBallV5::LARGECanToROTATE(const CVisionModule* pVision, const double finalDir)
{

    return 0;
}
bool CGetBallV5::WeMustReturnLARGE(const CVisionModule* pVision, const double finalDir)
{
    const BallVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const CVector self2ball = ball.Pos() - me.Pos();
    double ball2meDist = self2ball.mod();
    // cout << ball2meDist << endl;
    if (ball.Vel().mod() > 70 || ball2meDist > 30)
        return 1;
    return 0;
}
bool CGetBallV5::MustUseLargeToAdjust(const CVisionModule* pVision, const int _executor, const double finalDir){
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(_executor);
    if (fabs(Utils::Normalize(finalDir - me.Dir())) > Param::Math::PI * LARGE_ADJUST_ANGLE / 180.0) return 1;
    else return 0;
}

bool CGetBallV5::ROTATECanToDIRECT(const CVisionModule* pVision, double finalDir){

    double Precision = Param::Math::PI * GetBall_Precision_alpha / 180;
    //double offset = 0.05;

    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(task().executor);
    const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
    double myDir = me.Dir();
    CVector opp2ball = ball.Pos() - opp.Pos();
    CVector ball2goal = theirCenter - ball.Pos();
    //if (!ShootOrPass) ShootPrecision = ShootPrecision * 0.8;
    /*if (myDir - targetDir > 0)targetDir -= offset;
    else targetDir += offset;
    */
    finalDir = (ball.Pos() - me.Pos()).dir();

    if (fabs(finalDir - last_final_dir) > 4.0 * Precision) {

        last_final_dir = finalDir;
    }
    if (fabs(finalDir - me.Dir()) < Precision) {
        return true;

    }
    else return false;


    if (Me2OppTooclose(pVision, task().executor)) {
        if (fabs(myDir - finalDir) < 1.5 * Precision) {
            last_dir_deviation = 100;
            return true;
        }
    }
    if (fabs(myDir - finalDir) > 1.5 * Precision) {
        last_dir_deviation = myDir - finalDir;
        return false;
    }
    else if ((fabs(myDir - finalDir) > fabs(last_dir_deviation) || (myDir - finalDir) * last_dir_deviation <= 0)) {
        if (fabs(myDir - finalDir) < 1.25 * Precision) {
            last_dir_deviation = 100;
            return true;
        }
    }
    else if (fabs(myDir - finalDir) < Precision) {
        last_dir_deviation = 100;
        return true;
    }
    last_dir_deviation = myDir - finalDir;
    return false;
}

int CGetBallV5::getTheirMostClosetoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos) {
    double dist = 1000;
    int num = 0;
    for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
        if (pVision->TheirPlayer(i).Valid()) {
            if (pVision->TheirPlayer(i).Pos().dist(pos) < dist) {
                dist = pVision->TheirPlayer(i).Pos().dist(pos);
                num = i;
            }
        }
    }
    return num;
}

bool CGetBallV5::Me2OppTooclose(const CVisionModule* pVision, const int vecNumber) {
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
    const BallVisionT& ball = pVision->Ball();
    CVector me2Ball = ball.Pos() - me.Pos();
    CVector me2Opp = opp.Pos() - me.Pos();

    const double threshold = 70;


    if ((abs(me2Ball.mod()) < threshold && abs(me2Opp.mod()) < threshold * 1.5) && (me2Ball.dir() - me2Opp.dir() < Param::Math::PI / 3)) {
        return true;
    }
    return false;
}
bool CGetBallV5::OppIsNearThanMe(const CVisionModule* pVision, const int vecNumber) {
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
    const BallVisionT& ball = pVision->Ball();
    CVector me2Ball = ball.Pos() - me.Pos();
    CVector Ball2Opp = opp.Pos() - ball.Pos();

    const double threshold = 70;
    if (me2Ball.mod() > Ball2Opp.mod() || Ball2Opp.mod() < 20)return true;
    return false;
}


bool CGetBallV5::checkOppHasBall(const CVisionModule* pVision) {
    int _executor = task().executor;
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(_executor);
    const CVector self2ball = ball.Pos() - me.Pos();
    opponentID = getTheirMostClosetoPosPlayerNum(pVision, pVision->Ball().Pos());
    const PlayerVisionT& opponent = pVision->TheirPlayer(opponentID);
    if (DEBUG_ENGINE)GDebugEngine::Instance()->gui_debug_msg(opponent.Pos(), "Best Opp!", COLOR_WHITE);
    CVector opponent2ball = ball.Pos() - opponent.Pos();
    double opponent2ball_diff = fabs(Utils::Normalize(opponent2ball.dir() - opponent.Dir()));
    double judgeDist = OPP_HAS_BALL_DIST;
    if (opponent2ball.mod() < judgeDist && opponent2ball_diff < Param::Math::PI * 16 / 180)
        return true; // take opponent's direction into consideration.If direction not towards the ball,ignore it
    else
        return false;
}
CGeoPoint CGetBallV5::GenerateLargeAnglePoint(const CVisionModule* pVision, double finalDir, const bool debug) {
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
    if (Me2OppTooclose(pVision, robotNum));
    else getBallDist = (me.Pos() - ball.Pos()).mod();
    CGeoPoint target = ball.Pos() + Utils::Polar2Vector(getBallDist, theta_Dir);
    if (ball.Vel().mod() < 25) {
        CGeoLine JudgeLine1 = CGeoLine(ball.Pos(), finalDir);
        CGeoLine JudgeLine2 = CGeoLine(me.Pos(), target);
        CGeoLineLineIntersection LineIntersection = CGeoLineLineIntersection(JudgeLine1, JudgeLine2);
        if (LineIntersection.Intersectant()) {
            CGeoPoint Intersection = LineIntersection.IntersectPoint();
            CGeoSegment JudgeSegment = CGeoSegment(me.Pos(), target);
            if (JudgeSegment.IsPointOnLineOnSegment(Intersection)) {
                //double theta1 = (Intersection - me.Pos()).dir();
                //CGeoPoint target1 = Intersection + Utils::Polar2Vector(2, Utils::Normalize(theta1));
                //finalDir = (ball.Pos() - target1).dir();
                target = ball.Pos() + Utils::Polar2Vector(getBallDist, Utils::Normalize(finalDir + Param::Math::PI));
            }
        }
    }
    else {
        if (fabs((ball.Pos() - me.Pos()).theta(ball.Vel())) < Param::Math::PI * 20 / 180.0)
            target = ball.Pos() + Utils::Polar2Vector(getBallDist, Utils::Normalize(finalDir + Param::Math::PI));
        else target = ball.Pos() + Utils::Polar2Vector(getBallDist, ball.Vel().dir());
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