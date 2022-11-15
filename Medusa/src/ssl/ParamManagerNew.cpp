#include "ParamManagerNew.h"

double stringToDouble(std::string num)
{
	bool minus = false;      //标记是否是负数
	std::string real = num;       //real表示num的绝对值
	if (num.at(0) == '-')
	{
		minus = true;
		real = num.substr(1, num.size() - 1);
	}

	char c;
	int i = 0;
	double result = 0.0, dec = 10.0;
	bool isDec = false;       //标记是否有小数
	unsigned long size = real.size();
	while (i < size)
	{
		c = real.at(i);
		if (c == '.')
		{//包含小数
			isDec = true;
			i++;
			continue;
		}
		if (!isDec)
		{
			result = result * 10 + c - '0';
		}
		else
		{//识别小数点之后都进入这个分支
			result = result + (c - '0') / dec;
			dec *= 10;
		}
		i++;
	}

	if (minus == true) {
		result = -result;
	}

	return result;
}

tinyxml2::XMLElement* queryParamNode(tinyxml2::XMLElement* root, std::string paramName)
{

	tinyxml2::XMLElement* paramNode = root->FirstChildElement("Param");
	while (paramNode != NULL)
	{
		if (paramNode->Attribute("Name") == paramName)
			break;
		paramNode = paramNode->NextSiblingElement();//下一个兄弟节点
	}
	return paramNode;
}

double queryParamByName(char* xmlPath, std::string paramName)
{
	tinyxml2::XMLDocument doc;
	std::string value;
	if (doc.LoadFile(xmlPath) != 0)
	{
		return NULL;
	}
	tinyxml2::XMLElement* root = doc.RootElement();
	tinyxml2::XMLElement* paramNode = queryParamNode(root, paramName);

	if (paramNode != NULL)
	{
		value = paramNode->Attribute("Value");
	}
	return stringToDouble(value);
}

CParamManagerNew::CParamManagerNew()
{
	inifile::IniFile ini;
	ini.Load("data\\ssl\\params\\ssl.ini");

	/************************************************************************/
	/*                           调试开关                                    */
	/************************************************************************/
	// GotoPosition 中的调试开关
	ini.get("Debug", "DRAW_TARGET", &DRAW_TARGET);
	ini.get("Debug", "RECORD_NUM", &RECORD_NUM);
	ini.get("Debug", "RECORD_COMMAND", &RECORD_COMMAND);
	ini.get("Debug", "NOT_MOVE", &NOT_MOVE);

	// SmartGotoPosition 中的调试开关
	ini.get("Debug", "DRAW_RRT", &DRAW_RRT);
	ini.get("Debug", "DRAW_TRAJ", &DRAW_TRAJ);
	ini.get("Debug", "DRAW_OBS", &DRAW_OBS);
	ini.get("Debug", "DRAW_BALLPLACE_AREA", &DRAW_BALLPLACE_AREA);
	ini.get("Debug", "DRAW_PENALTY_DEBUG_MSG", &DRAW_PENALTY_DEBUG_MSG);

	// TouchKick 中的调试开关
	ini.get("Debug", "TOUCH_SHIFT_DIST", &TOUCH_SHIFT_DIST);
	ini.get("Debug", "TOUCH_Debug", &TOUCH_Debug);
	// Defence 中的调试开关
	ini.get("Defence", "DEFENCE_DEBUG_MODE", &DEFENCE_DEBUG_MODE);
	ini.get("Defence", "ATTACK_DEF_MODE", &ATTACK_DEF_MODE);
	ini.get("Defence", "GOALIE_EVALUATE", &GOALIE_EVALUATE);
	ini.get("Defence", "MARKING_MODE", &MARKING_MODE);

	ini.get("Motion", "PERIOD_MOVE_X", &PERIOD_MOVE_X);
	ini.get("Motion", "PERIOD_MOVE_Y", &PERIOD_MOVE_Y);
	ini.get("Motion", "PERIOD_MOVE_ROT", &PERIOD_MOVE_ROT);
	ini.get("Motion", "A_MAX_1", &A_MAX_1);
	ini.get("Motion", "V_LIMIT_1", &V_LIMIT_1);
	ini.get("Motion", "PERIOD_V_LIMIT_1", &PERIOD_V_LIMIT_1);
	ini.get("Motion", "V_LIMIT_2", &V_LIMIT_2);
	ini.get("Motion", "PERIOD_V_LIMIT_2", &PERIOD_V_LIMIT_2);
	ini.get("Motion", "A_MAX_2", &A_MAX_2);
	ini.get("Motion", "V_LIMIT_3", &V_LIMIT_3);
	ini.get("Motion", "PERIOD_V_LIMIT_3", &PERIOD_V_LIMIT_3);
	ini.get("Motion", "V_LIMIT_4", &V_LIMIT_4);
	ini.get("Motion", "PERIOD_V_LIMIT_4", &PERIOD_V_LIMIT_4);
	ini.get("Motion", "PlACEBALL_SPEED", &PlACEBALL_SPEED);
	ini.get("Motion", "PlACEBALL_ROT_SPEED", &PlACEBALL_ROT_SPEED);
	ini.get("Motion", "PlACEBALL_ACCELERATION", &PlACEBALL_ACCELERATION);
	ini.get("Motion", "PlACEBALL_DECELERATION", &PlACEBALL_DECELERATION);
	ini.get("Motion", "PlACEBALL_ROT_ACCELERATION", &PlACEBALL_ROT_ACCELERATION);
	ini.get("Motion", "PlACEBALL_CLOSE_DISTANCE", &PlACEBALL_CLOSE_DISTANCE);
	ini.get("Motion", "D_MAX_FACTOR", &D_MAX_FACTOR);
	ini.get("Motion", "MAX_WHEEL_SPEED", &MAX_WHEEL_SPEED);

	ini.get("Field", "PENALTY_AREA_DEPTH", &PENALTY_AREA_DEPTH);
	ini.get("Field", "FIELD_WALL_DIST", &FIELD_WALL_DIST);
	ini.get("Field", "SUPPORT_DIST", &SUPPORT_DIST);

	ini.get("Goalie", "SLOW_BALL_SPD", &SLOW_BALL_SPD);
	ini.get("Goalie", "KICKPOWER_GOALIE", &KICKPOWER_GOALIE);
	ini.get("Goalie", "HAVE_BALL_DIST", &HAVE_BALL_DIST);
	ini.get("Goalie", "CLOSE_DIST", &CLOSE_DIST);
	ini.get("Goalie", "CHALLENGE_BALL_DIST", &CHALLENGE_BALL_DIST);
	ini.get("Goalie", "BLOCK_DIST", &BLOCK_DIST);

	// Add by tyh
	ini.get("Advance", "KICK_DIST", &KICK_DIST);
	ini.get("Advance", "WantToLessShoot", &WantToLessShoot);
	ini.get("Advance", "RELIEF_DIST", &RELIEF_DIST);
	ini.get("Advance", "OPP_HAS_BALL_DIST", &OPP_HAS_BALL_DIST);
	ini.get("Advance", "CanPassToWingDist", &CanPassToWingDist);
	ini.get("Advance", "CanWingShootDist", &CanWingShootDist);
	ini.get("Advance", "SHOOT_PRECISION", &SHOOT_PRECISION);
	ini.get("Advance", "AdGetBallBias", &AdGetBallBias);
	ini.get("Advance", "BalltoMeVelTime", &BalltoMeVelTime);

	ini.get("Advance", "KICKPOWER", &KICKPOWER);
	ini.get("Advance", "CHIPPOWER", &CHIPPOWER);
	ini.get("Advance", "ADV_FPASSPOWER", &ADV_FPASSPOWER);
	ini.get("Advance", "ADV_CPASSPOWER", &ADV_CPASSPOWER);
	ini.get("Advance", "RELIEF_POWER", &RELIEF_POWER);
	ini.get("Advance", "BACK_POWER", &BACK_POWER);
	ini.get("Advance", "Advance_DEBUG_ENGINE", &Advance_DEBUG_ENGINE);

	ini.get("BREAK", "BACK_DRIBBLE_SPEED", &BREAK_BACK_DRIBBLE_SPEED);
	ini.get("BREAK", "SHOOT_ACCURACY", &BREAK_SHOOT_ACCURACY);
	ini.get("BREAK", "DEBUG", &BREAK_DEBUG);
	ini.get("BREAK", "COEF_BLOCKSCORE", &COEF_BLOCKSCORE);
	ini.get("BREAK", "COEF_DISTSCORE", &COEF_DISTSCORE);
	ini.get("BREAK", "COEF_NEARSCORE", &COEF_NEARSCORE);

	// Add by tyh
	ini.get("ReceivePass", "PassBalltoMeVel", &PassBalltoMeVel);
}


CParamManagerNew::~CParamManagerNew()
{
}
