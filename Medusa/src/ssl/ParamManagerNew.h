#include <tinyxml2/tinyxml2.h>
#include <param.h>
#include <tinyxml/ParamReader.h>
#include <inifile/inifile2.h>

#ifndef PARAMMANAGERNEW_H
#define PARAMMANAGERNEW_H

double queryParamByName(char* xmlPath, std::string paramName);

struct GetBallParam {
    double back_bias;
};

class CParamManagerNew {
public:
    CParamManagerNew();
    ~CParamManagerNew();

    /************************************************************************/
    /*                           调试开关                                    */
    /************************************************************************/
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

	// TouchKick 中的调试开关
	int TOUCH_SHIFT_DIST;
	int TOUCH_Debug;
    
    // Defence 中的调试开关
    bool DEFENCE_DEBUG_MODE;
    bool ATTACK_DEF_MODE;
    bool GOALIE_EVALUATE;
    int MARKING_MODE;

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

    // 场地参数
    double FIELD_WALL_DIST;
    double PENALTY_AREA_DEPTH;

    double SUPPORT_DIST;
    GetBallParam GET_BALL_PARAM;

	// Goalie2022参数 by SYLG
	double SLOW_BALL_SPD;
	int KICKPOWER_GOALIE;
	double HAVE_BALL_DIST;
	double CLOSE_DIST;
	double CHALLENGE_BALL_DIST;
	double BLOCK_DIST;

    //break 参数
    double BREAK_BACK_DRIBBLE_SPEED;
    double BREAK_SHOOT_ACCURACY;
    bool BREAK_DEBUG;
    double COEF_NEARSCORE;
    double COEF_BLOCKSCORE;
    double COEF_DISTSCORE;
    
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
    /*射门力度参数*/
    int KICKPOWER;
    int CHIPPOWER;
    int ADV_FPASSPOWER;
    int ADV_CPASSPOWER;
    int RELIEF_POWER;
    int  BACK_POWER;
    bool Advance_DEBUG_ENGINE ;

    /*ReceivePass add by tyh*/
    double PassBalltoMeVel;

private:
};

typedef NormalSingleton< CParamManagerNew > ParamManager;

#endif // PARAMMANAGERNEW_H
