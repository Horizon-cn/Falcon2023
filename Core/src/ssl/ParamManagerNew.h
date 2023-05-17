#ifndef PARAMMANAGERNEW_H
#define PARAMMANAGERNEW_H

#include <QSettings>
#include <QDebug>
#include "singleton.h"
#include "params.h"

//struct GetBallParam {
//    double back_bias;
//};
class ParamManagerOwl : public Falcon::ParamManager {
public:
    ParamManagerOwl() : ParamManager("../data/owl2.ini") { setFileName("./"); update(); }
    ~ParamManagerOwl() {}
    void update()
    {
        //Global Settings
        loadParam(LoginName, "Alert/LoginName", "SRC");
        loadParam(isSimulation, "Alert/isSimulation", true);
        loadParam(isYellow, "Alert/isYellow", false);
        loadParam(isRight, "Alert/isRight", false);
        //Useful Ports
        loadParam(refereePortToBlue, "AlertPorts/refereePortToBlue", 10002);
        loadParam(refereePortToYellow, "AlertPorts/refereePortToYellow", 10004);
    }
public:
    //Global Settings
    std::string LoginName;
    bool isSimulation, isYellow, isRight;
    //Useful Ports
    int refereePortToBlue, refereePortToYellow;
};
typedef Falcon::MeyersSingleton<ParamManagerOwl> OParamManager;
class ParamManagerCfg : public Falcon::ParamManager {
public:
    ParamManagerCfg() : ParamManager("../data/cfg.ini") { setFileName("./"); update(); }
    ~ParamManagerCfg() {}
    void update() {
        //IP address
        loadParam(local_address, "IP/local_address", "127.0.0.1");
        loadParam(referee_address, "IP/referee_address", "224.5.23.1");
        //internal port
        loadParam(blue_control, "Ports/blue_control", 50011);
        loadParam(yellow_control, "Ports/yellow_control", 50012);
        loadParam(blue_feedback, "Ports/blue_feedback", 60001);
        loadParam(yellow_feedback, "Ports/yellow_feedback", 60002);
        loadParam(blue_vision, "Ports/blue_vision", 23333);
        loadParam(yellow_vision, "Ports/yellow_vision", 23334);
        loadParam(blue_debug, "Ports/blue_debug", 20001);
        loadParam(yellow_debug, "Ports/yellow_debug", 20002);
        loadParam(blue_heat, "Ports/blue_heat", 20003);
        loadParam(yellow_heat, "Ports/yellow_heat", 20004);
    }
public:
    QString local_address, referee_address;
    int blue_control, yellow_control;
    int blue_feedback, yellow_feedback;
    int blue_vision, yellow_vision;
    int blue_debug, yellow_debug;
    int blue_heat, yellow_heat;
};
typedef Falcon::MeyersSingleton<ParamManagerCfg> CParamManager;
class ParamManagerVision : public Falcon::ParamManager {
public:
    ParamManagerVision() : ParamManager("../data/vision.ini") { setFileName("./"); }
    ~ParamManagerVision() {}
};
typedef Falcon::MeyersSingleton<ParamManagerVision> VParamManager;
class ParamManagerSimulator : public Falcon::ParamManager {
public:
    ParamManagerSimulator() : ParamManager("../data/simulator.ini") { setFileName("./"); }
    ~ParamManagerSimulator() {}
};
typedef Falcon::MeyersSingleton<ParamManagerSimulator> SParamManager;
class CParamManagerSkill : public Falcon::ParamManager {
    public:
        CParamManagerSkill() : ParamManager("../data/skill.ini") { setFileName("./"); update(); }
        ~CParamManagerSkill() {}
        void update()
        {
            loadParam(DRAW_TARGET, "Debug/DRAW_TARGET", 0);
            loadParam(RECORD_NUM, "Debug/RECORD_NUM", 1);
            loadParam(RECORD_COMMAND, "Debug/RECORD_COMMAND", 0);
            loadParam(NOT_MOVE, "Debug/NOT_MOVE", 0);
            loadParam(DRAW_RRT, "Debug/DRAW_RRT", 0);
            loadParam(DRAW_TRAJ, "Debug/DRAW_TRAJ", 0);
            loadParam(DRAW_OBS, "Debug/DRAW_OBS", 1);
            loadParam(DRAW_BALLPLACE_AREA, "Debug/DRAW_BALLPLACE_AREA", 0);
            loadParam(DRAW_PENALTY_DEBUG_MSG, "Debug/DRAW_PENALTY_DEBUG_MSG", 1);

            loadParam(BUFFER, "GotoPositionNew/BUFFER", 10);
            loadParam(INFLAT_RATIO, "GotoPositionNew/INFLAT_RATIO", 1.0);
            loadParam(LOWER_BND_UDOT, "GotoPositionNew/LOWER_BND_UDOT", 2.0);
            loadParam(MAX_SEARCH_ITERATION, "GotoPositionNew/MAX_SEARCH_ITERATION", 2);
            loadParam(COUNTPLAN_THRESHOLD, "GotoPositionNew/COUNTPLAN_THRESHOLD", 90);

            loadParam(TOUCH_SHIFT_DIST, "TOUCHKICK/TOUCH_SHIFT_DIST", 9.96);
            loadParam(TOUCH_Debug, "TOUCHKICK/TOUCH_Debug", 0);

            loadParam(DEFENCE_DEBUG_MODE, "Defence/DEFENCE_DEBUG_MODE", 1);
            loadParam(ATTACK_DEF_MODE, "Defence/ATTACK_DEF_MODE", 1);
            loadParam(GOALIE_EVALUATE, "Defence/GOALIE_EVALUATE", 0);
            loadParam(MARKING_MODE, "Defence/MARKING_MODE", 0);
            loadParam(DENY_BALL_MODE, "Defence/DENY_BALL_MODE", 1);
            loadParam(BACK_LINE_MODE, "Defence/BACK_LINE_MODE", 1);
            loadParam(SPECIAL_AREA_BACK_LINE_MODE, "Defence/SPECIAL_AREA_BACK_LINE_MODE", 0);
            loadParam(SIDEBACK_MARKING_MODE, "Defence/SIDEBACK_MARKING_MODE", 1);
            loadParam(GOALIE_FILL_IN_MODE, "Defence/GOALIE_FILL_IN_MODE", 0);

            loadParam(display_debug_info, "DefenceNew/display_debug_info", 1);
            loadParam(factor_ballChaserTest, "DefenceNew/factor_ballChaserTest", 0);
            loadParam(factor_Dist2BallNormalized, "DefenceNew/factor_Dist2BallNormalized", 0.7);
            loadParam(factor_Dist2BallProjModified, "DefenceNew/factor_Dist2BallProjModified", 0.7);
            loadParam(factor_BallMovingCost, "DefenceNew/factor_BallMovingCost", 0.35);
            loadParam(factor_TooFar4Pass, "DefenceNew/factor_TooFar4Pass", 0.01);
            loadParam(factor_TooClose4Pass, "DefenceNew/factor_TooClose4Pass", 1);
            loadParam(factor_TooFar4Shoot, "DefenceNew/factor_TooFar4Shoot", 0.1);
            loadParam(factor_EasyBlock, "DefenceNew/factor_EasyBlock", 100);
            loadParam(factor_NearSideLine, "DefenceNew/factor_NearSideLine", 1);
            loadParam(factor_EasyShoot, "DefenceNew/factor_EasyShoot", 50);

            loadParam(PERIOD_MOVE_X, "Motion/PERIOD_MOVE_X", 0.07692);
            loadParam(PERIOD_MOVE_Y, "Motion/PERIOD_MOVE_Y", 0.013);
            loadParam(PERIOD_MOVE_ROT, "Motion/PERIOD_MOVE_ROT", 0.0625);
            loadParam(A_MAX_1, "Motion/A_MAX_1", 600);
            loadParam(V_LIMIT_1, "Motion/V_LIMIT_1", 150);
            loadParam(PERIOD_V_LIMIT_1, "Motion/PERIOD_V_LIMIT_1", 0.0625);
            loadParam(V_LIMIT_2, "Motion/V_LIMIT_2", 50);
            loadParam(PERIOD_V_LIMIT_2, "Motion/PERIOD_V_LIMIT_2", 0.05);
            loadParam(A_MAX_2, "Motion/A_MAX_2", 480);
            loadParam(V_LIMIT_3, "Motion/V_LIMIT_3", 150);
            loadParam(PERIOD_V_LIMIT_3, "Motion/PERIOD_V_LIMIT_3", 0.03);
            loadParam(V_LIMIT_4, "Motion/V_LIMIT_4", 50);
            loadParam(PERIOD_V_LIMIT_4, "Motion/PERIOD_V_LIMIT_4", 0.033);
            loadParam(D_MAX_FACTOR, "Motion/D_MAX_FACTOR", 0.5);
            loadParam(MAX_WHEEL_SPEED, "Motion/MAX_WHEEL_SPEED", 200000);
            loadParam(PlACEBALL_SPEED, "Motion/PlACEBALL_SPEED", 150);
            loadParam(PlACEBALL_ROT_SPEED, "Motion/PlACEBALL_ROT_SPEED", 3);
            loadParam(PlACEBALL_ACCELERATION, "Motion/PlACEBALL_ACCELERATION", 50);
            loadParam(PlACEBALL_DECELERATION, "Motion/PlACEBALL_DECELERATION", 50);
            loadParam(PlACEBALL_ROT_ACCELERATION, "Motion/PlACEBALL_ROT_ACCELERATION", 3);
            loadParam(PlACEBALL_CLOSE_DISTANCE, "Motion/PlACEBALL_CLOSE_DISTANCE", 100);

            loadParam(SUPPORT_DIST, "Support/SUPPORT_DIST", 1);

            loadParam(GOALIE_DEBUG, "Goalie/GOALIE_DEBUG", 1);
            loadParam(AGGRESSIVE_GOALIE, "Goalie/AGGRESSIVE_GOALIE", 1);
            loadParam(SLOW_BALL_SPD, "Goalie/SLOW_BALL_SPD", 25.0);
            loadParam(KICKPOWER_GOALIE, "Goalie/KICKPOWER_GOALIE", 550);
            loadParam(HAVE_BALL_DIST, "Goalie/HAVE_BALL_DIST", 30);
            loadParam(CLOSE_DIST, "Goalie/CLOSE_DIST", 30);
            loadParam(CHALLENGE_BALL_DIST, "Goalie/CHALLENGE_BALL_DIST", 60);
            loadParam(BLOCK_DIST, "Goalie/BLOCK_DIST", 60);

            loadParam(RANDOM_NUM, "PenaltyGoalie/RANDOM_NUM", 5);
            loadParam(RANDOM_MIN, "PenaltyGoalie/RANDOM_MIN", -0.3);
            loadParam(RANDOM_MAX, "PenaltyGoalie/RANDOM_MAX", 0.3);
            loadParam(STABLE_FRAME_INTERVAL, "PenaltyGoalie/STABLE_FRAME_INTERVAL", 5);
            loadParam(TRICKPOS_DIV_PENALTY, "PenaltyGoalie/TRICKPOS_DIV_PENALTY", 1);
           
            loadParam(BREAK_SHOOT_ACCURACY, "BREAK/SHOOT_ACCURACY", 10);
            loadParam(BREAK_DEBUG, "BREAK/DEBUG", 1);
            loadParam(COEF_BLOCKSCORE, "BREAK/COEF_BLOCKSCORE", 10);
            loadParam(COEF_NEARSCORE, "BREAK/COEF_NEARSCORE", 1);
            loadParam(COEF_DISTSCORE, "BREAK/COEF_DISTSCORE", 0.5);
            loadParam(BREAK_ACC, "BREAK/ACC", 200);
            loadParam(BREAK_VEL, "BREAK/VEL", 500);
            loadParam(BREAK_ROT_ACC, "BREAK/ROT_ACC", 50);
            loadParam(BREAK_ROT_VEL, "BREAK/ROT_VEL", 100);
            loadParam(BREAK_OBSTACLE_RADIUS, "BREAK/OBSTACLE_RADIUS", 5);




            loadParam(KICK_DIST, "Advance/KICK_DIST", 400);
            loadParam(WantToLessShoot, "Advance/WantToLessShoot", 3);
            loadParam(RELIEF_DIST, "Advance/RELIEF_DIST", 280);
            loadParam(OPP_HAS_BALL_DIST, "Advance/OPP_HAS_BALL_DIST", 30);
            loadParam(CanPassToWingDist, "Advance/CanPassToWingDist", 600);
            loadParam(CanWingShootDist, "Advance/CanWingShootDist", 500);
            loadParam(SHOOT_PRECISION, "Advance/SHOOT_PRECISION", 7);
            loadParam(AdGetBallBias, "Advance/AdGetBallBias", 0);
            loadParam(BalltoMeVelTime, "Advance/BalltoMeVelTime", 1.0);
            loadParam(KICKPOWER, "Advance/KICKPOWER", 700);
            loadParam(CHIPPOWER, "Advance/CHIPPOWER", 240);
            loadParam(ADV_FPASSPOWER, "Advance/ADV_FPASSPOWER", 2);
            loadParam(ADV_CPASSPOWER, "Advance/ADV_CPASSPOWER", 1);
            loadParam(ADV_PUSHPOWER, "Advance/ADV_PUSHPOWER", 35.0);
            loadParam(RELIEF_POWER, "Advance/RELIEF_POWER", 400);
            loadParam(BACK_POWER, "Advance/BACK_POWER", 300);
            loadParam(BACK_POWER_V3, "Advance/BACK_POWER_V3", 160);
            loadParam(Advance_DEBUG_ENGINE, "Advance/Advance_DEBUG_ENGINE", 1);
            loadParam(PassBalltoMeVel, "Advance/PassBalltoMeVel", 200);
            loadParam(WEAK_OPP, "Advance/WEAK_OPP", 1);
            loadParam(CIRCLE_FRONT, "Advance/CIRCLE_FRONT", 1);
            loadParam(USE_DRIBBLE_TURN, "Advance/USE_DRIBBLE_TURN", 1);
            loadParam(CHIP_ANGLE, "Advance/CHIP_ANGLE", 15);
            loadParam(FLAT_DIST, "Advance/FLAT_DIST", 600);
            loadParam(PULL_DIST, "Advance/PULL_DIST", 450);
            loadParam(RELIEF_BIAS, "Advance/RELIEF_BIAS", 350);
            loadParam(TEND_TO_SHOOT_FLAG, "Advance/TEND_TO_SHOOT_FLAG", 23);
            loadParam(SHOOT_BLOCKED_RANGE, "Advance/SHOOT_BLOCKED_RANGE", 1.4);
            loadParam(PASS_BLOCKED_RANGE, "Advance/PASS_BLOCKED_RANGE", 5);
            loadParam(BALL_DEC, "Advance/BALL_DEC", 98.0);
            loadParam(FASTEST_RECEIVE_VEL, "Advance/FASTEST_RECEIVE_VEL", 80.0);
            loadParam(maxChipDist, "Advance/maxChipDist", 460.0);

            loadParam(CHASEKICK_TOPENALTY_GAP, "ChaseKick/CHASEKICK_TOPENALTY_GAP", 10);
            loadParam(CHASEKICK_ENDVEL_STARTX, "ChaseKick/CHASEKICK_ENDVEL_STARTX", 0);
            loadParam(CHASEKICK_MAXENDVEL, "ChaseKick/CHASEKICK_MAXENDVEL", 0);
            loadParam(ChaseKick_Debug, "ChaseKick/Debug", 1);

            loadParam(VERBOSE, "PlaceBall/VERBOSE", 0);
            loadParam(WAIT_BUFFER, "PlaceBall/WAIT_BUFFER", 60);
            loadParam(GETBALLMAXCNT, "PlaceBall/GETBALLMAXCNT", 10);

            loadParam(HEAD_LIMIT, "GetBall/HEAD_LIMIT", 15);
            loadParam(GETBALL_BIAS, "GetBall/GETBALL_BIAS", -3);
            loadParam(IS_DRIBBLE, "GetBall/IS_DRIBBLE", 1);
            loadParam(BALL_NEAR_ROBOT, "GetBall/BALL_NEAR_ROBOT", 20);
            loadParam(GetBall_Debug, "GetBall/Debug", 1);
            loadParam(roll_acc, "GetBall/roll_acc", 200);
            loadParam(slide_acc, "GetBall/slide_acc", 500);
            loadParam(transition_speed, "GetBall/transition_speed", 400);
            loadParam(LARGE_ADJUST_ANGLE, "GetBall/LARGE_ADJUST_ANGLE", 20.0);
            loadParam(GetBall_Precision_alpha, "GetBall_Precision_alpha", 3.0);

            loadParam(CATEGORY, "PENALTY_DEFENCE/CATEGORY", 3);
            loadParam(FRAME, "PENALTY_DEFENCE/FRAME", 0);
            loadParam(AHEAD, "PENALTY_DEFENCE/AHEAD", 20);

            loadParam(CheckBackPos, "MultiBack/CheckBackPos", true);
            loadParam(dangerVel, "MultiBack/dangerVel", 15);
            loadParam(dangerDist, "MultiBack/dangerDist", 50);
            loadParam(defendBreak, "MultiBack/defendBreak", true);

            loadParam(BAYESLIST, "CMatchState/BAYESLIST", "BayesParams1");
            loadParam(BAYESPARAM, "CMatchState/BAYESPARAM", "Skuba_Attack");

            loadParam(SLOW_FACTOR, "Capability/SLOW_FACTOR", 0.65);
            loadParam(MAX_TRANSLATION_SPEED_GOALIE, "Capability/MAX_TRANSLATION_SPEED_GOALIE", 300);
            loadParam(MAX_TRANSLATION_ACC_GOALIE, "Capability/MAX_TRANSLATION_ACC_GOALIE", 300);
            loadParam(MAX_TRANSLATION_DEC_GOALIE, "Capability/MAX_TRANSLATION_DEC_GOALIE", 300);
            loadParam(MAX_ROTATION_ACC_GOALIE, "Capability/MAX_ROTATION_ACC_GOALIE", 5);
            loadParam(MAX_ROTATION_SPEED_GOALIE, "Capability/MAX_ROTATION_SPEED_GOALIE", 10);
            loadParam(MAX_TRANSLATION_SPEED_BACK, "Capability/MAX_TRANSLATION_SPEED_BACK", 300);
            loadParam(MAX_TRANSLATION_ACC_BACK, "Capability/MAX_TRANSLATION_ACC_BACK", 300);
            loadParam(MAX_TRANSLATION_DEC_BACK, "Capability/MAX_TRANSLATION_DEC_BACK", 300);
            loadParam(MAX_ROTATION_ACC_BACK, "Capability/MAX_ROTATION_ACC_BACK", 5);
            loadParam(MAX_ROTATION_SPEED_BACK, "Capability/MAX_ROTATION_SPEED_BACK", 10);
            loadParam(MAX_TRANSLATION_SPEED, "Capability/MAX_TRANSLATION_SPEED", 300);
            loadParam(MAX_TRANSLATION_ACC, "Capability/MAX_TRANSLATION_ACC", 100);
            loadParam(MAX_TRANSLATION_DEC, "Capability/MAX_TRANSLATION_DEC", 300);
            loadParam(MAX_ROTATION_ACC, "Capability/MAX_ROTATION_ACC", 5);
            loadParam(MAX_ROTATION_SPEED, "Capability/MAX_ROTATION_SPEED", 10);
            loadParam(TRANSLATION_ACC_LIMIT, "Capability/TRANSLATION_ACC_LIMIT", 500);
            loadParam(TRANSLATION_SPEED_LIMIT, "Capability/TRANSLATION_SPEED_LIMIT", 300);
            loadParam(TRANSLATION_ROTATE_ACC_LIMIT, "Capability/TRANSLATION_ROTATE_ACC_LIMIT", 5);
            loadParam(MAX_TRANSLATION_SPEED_X, "Capability/MAX_TRANSLATION_SPEED_X", 500);
            loadParam(MAX_TRANSLATION_SPEED_Y, "Capability/MAX_TRANSLATION_SPEED_Y", 500);

            loadParam(PENALTY_FIGHT, "General/PENALTY_FIGHT", 1);

            loadParam(maxFrame, "BallStatus/maxFrame", 10);
            loadParam(ourVisionJudgeDist, "BallStatus/ourVisionJudgeDist", 11.3);
            loadParam(ourVisionJudgeDir, "BallStatus/ourVisionJudgeDir", 30);
            loadParam(theirVisionJudgeDist, "BallStatus/theirVisionJudgeDist", 20);
            loadParam(theirVisionJudgeDir, "BallStatus/theirVisionJudgeDir", 30);

            loadParam(boundaryVersion, "GpuBestAlg/boundaryVersion", 1);
            loadParam(step, "GpuBestAlg/step", 10);
            loadParam(startPosX, "GpuBestAlg/startPosX", -600);
            loadParam(startPosY, "GpuBestAlg/startPosY", -450);
        }
    public:
        // GotoPosition 中的调试开关
        int DRAW_TARGET;
        int RECORD_NUM;
        int RECORD_COMMAND;
        int NOT_MOVE;
        // SmartGotoPosition 中的调试开关
        int DRAW_RRT;
        int DRAW_TRAJ;
        int DRAW_OBS;
        int DRAW_BALLPLACE_AREA;
        int DRAW_PENALTY_DEBUG_MSG;
        // GotoPositionNew 中的调试变量
        double BUFFER;
        double INFLAT_RATIO;
        double LOWER_BND_UDOT;
        int MAX_SEARCH_ITERATION;
        int COUNTPLAN_THRESHOLD;
        // TouchKick 中的调试开关
        int TOUCH_SHIFT_DIST;
        int TOUCH_Debug;
        // Defence 中的调试开关
        bool DEFENCE_DEBUG_MODE;
        bool ATTACK_DEF_MODE;
        bool GOALIE_EVALUATE;
        int MARKING_MODE;
        int DENY_BALL_MODE;
        int BACK_LINE_MODE;
        int SPECIAL_AREA_BACK_LINE_MODE;
        int SIDEBACK_MARKING_MODE;
        int GOALIE_FILL_IN_MODE;
        // DefenceNew
        bool display_debug_info;
        double factor_ballChaserTest;
        double factor_Dist2BallNormalized;
        double factor_Dist2BallProjModified;
        double factor_BallMovingCost;
        double factor_TooFar4Pass;
        double factor_TooClose4Pass;
        double factor_TooFar4Shoot;
        double factor_EasyBlock;
        double factor_NearSideLine;
        double factor_EasyShoot;
        // 电机参数
        double PERIOD_MOVE_X;
        double PERIOD_MOVE_Y;
        double PERIOD_MOVE_ROT;
        double A_MAX_1;
        double V_LIMIT_1;
        double PERIOD_V_LIMIT_1;
        double V_LIMIT_2;
        double PERIOD_V_LIMIT_2;
        double A_MAX_2;
        double V_LIMIT_3;
        double PERIOD_V_LIMIT_3;
        double V_LIMIT_4;
        double PERIOD_V_LIMIT_4;
        double PlACEBALL_SPEED;
        double PlACEBALL_ROT_SPEED;
        double PlACEBALL_ACCELERATION;
        double PlACEBALL_DECELERATION;
        double PlACEBALL_ROT_ACCELERATION;
        double PlACEBALL_CLOSE_DISTANCE;
        int PlACEBALL_PLAYER_NUM;
        double D_MAX_FACTOR;
        double MAX_WHEEL_SPEED;
        // Support参数
        double SUPPORT_DIST;
        //GetBallParam GET_BALL_PARAM;
        // Goalie2022参数 by SYLG
        bool GOALIE_DEBUG;
        bool AGGRESSIVE_GOALIE;
        double SLOW_BALL_SPD;
        int KICKPOWER_GOALIE;
        double HAVE_BALL_DIST;
        double CLOSE_DIST;
        double CHALLENGE_BALL_DIST;
        double BLOCK_DIST;
        // Goalie2022点球参数 by SYLG
        int RANDOM_NUM;
        double RANDOM_MIN;
        double RANDOM_MAX;
        int STABLE_FRAME_INTERVAL;
        double TRICKPOS_DIV_PENALTY;
        //break 参数
        double BREAK_SHOOT_ACCURACY;
        bool BREAK_DEBUG;
        double COEF_NEARSCORE;
        double COEF_BLOCKSCORE;
        double COEF_DISTSCORE;
        double BREAK_ACC;
        double BREAK_VEL;
        double BREAK_ROT_VEL;
        double BREAK_ROT_ACC;
        double BREAK_OBSTACLE_RADIUS;

        //advance参数 byTYH  2022.10
        double KICK_DIST;  /*射门允许范围 越高越容易射门*/
        int WantToLessShoot ; /*射门倾向，越低越容易射门 最低为0 最高为5*/
        double RELIEF_DIST ;  /*GET中紧急状况下的RELIEF判断距离*/
        double OPP_HAS_BALL_DIST; /*判断敌方是否有球的距离 需要调整*/
        double CanPassToWingDist; /*Advance能够传给边锋的临界距离*/
        double CanWingShootDist; /*边锋能够射门的临界距离*/
        double SHOOT_PRECISION;	/*允许射门最小精度角分母，越大越慢越精确 最低为7最高17*/
        double AdGetBallBias;  /*Getball的偏移量*/
        double BalltoMeVelTime;/*Advance传球给我主动去接的临界时间*/
        bool WEAK_OPP;
        bool CIRCLE_FRONT;
        bool USE_DRIBBLE_TURN;
        int CHIP_ANGLE;
        int FLAT_DIST;
        int PULL_DIST;
        int RELIEF_BIAS;
        double TEND_TO_SHOOT_FLAG;
        double SHOOT_BLOCKED_RANGE;
        double PASS_BLOCKED_RANGE;
        double BALL_DEC;
        double FASTEST_RECEIVE_VEL;
        double maxChipDist;
        /*射门力度参数*/
        double KICKPOWER;
        double CHIPPOWER;
        double ADV_FPASSPOWER;
        double ADV_CPASSPOWER;
        double ADV_PUSHPOWER;
        double RELIEF_POWER;
        double  BACK_POWER;
        double BACK_POWER_V3;
        bool Advance_DEBUG_ENGINE ;
        /*ReceivePass add by tyh*/
        double PassBalltoMeVel;
        // ChaseKick
        int CHASEKICK_TOPENALTY_GAP;
        int CHASEKICK_ENDVEL_STARTX;
        int CHASEKICK_MAXENDVEL;
        bool ChaseKick_Debug;
        // PlaceBall
        bool VERBOSE;
        int WAIT_BUFFER;
        int GETBALLMAXCNT;
        // GetBall
        int HEAD_LIMIT;
        int GETBALL_BIAS;
        bool IS_DRIBBLE;
        int BALL_NEAR_ROBOT;
        bool GetBall_Debug;
        double roll_acc;
        double slide_acc;
        double transition_speed;
        double LARGE_ADJUST_ANGLE;
        double GetBall_Precision_alpha;
        // PENALTY_DEFENCE
        int CATEGORY;
        int FRAME;
        int AHEAD;
        // MultiBack
        bool CheckBackPos;
        int dangerVel;
        int dangerDist;
        bool defendBreak;
        // MatchState
        QString BAYESLIST;
        QString BAYESPARAM;
        //Capability
        double SLOW_FACTOR;
        int MAX_TRANSLATION_SPEED_GOALIE;
        int MAX_TRANSLATION_ACC_GOALIE;
        int MAX_TRANSLATION_DEC_GOALIE;
        int MAX_ROTATION_ACC_GOALIE;
        int MAX_ROTATION_SPEED_GOALIE;
        int MAX_TRANSLATION_SPEED_BACK;
        int MAX_TRANSLATION_ACC_BACK;
        int MAX_TRANSLATION_DEC_BACK;
        int MAX_ROTATION_ACC_BACK;
        int MAX_ROTATION_SPEED_BACK;
        int MAX_TRANSLATION_SPEED;
        int MAX_TRANSLATION_ACC;
        int MAX_TRANSLATION_DEC;
        int MAX_ROTATION_ACC;
        int MAX_ROTATION_SPEED;
        int TRANSLATION_ACC_LIMIT;
        int TRANSLATION_SPEED_LIMIT;
        int TRANSLATION_ROTATE_ACC_LIMIT;
        int MAX_TRANSLATION_SPEED_X;
        int MAX_TRANSLATION_SPEED_Y;

        // General
        bool PENALTY_FIGHT;
        // BallStatus
        int maxFrame;
        double ourVisionJudgeDist;
        double ourVisionJudgeDir;
        double theirVisionJudgeDist;
        double theirVisionJudgeDir;
        // GpuBestAlg
        int boundaryVersion;
        int step;
        int startPosX;
        int startPosY;
};
typedef Falcon::NormalSingleton< CParamManagerSkill > ParamManager;

#endif // PARAMMANAGERNEW_H
