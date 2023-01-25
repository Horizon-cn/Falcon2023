/**
* @file param.h
* 本文件定义程序中用到的各种参数.
* @date 10/1/2002
* @version 1.0
* @author peter@mail.ustc.edu.cn
*/
#ifndef _PARAM_H_
#define _PARAM_H_
#include "os_param.h" // 和系统有关的参数
#include "singleton.h"
#include "ParamManagerNew.h"
/**
* 参数名字空间Param.
* 这个名字空间定义了程序中用到的所有的参数
*/		

namespace Param{
	const auto a = OParamManager::Instance()->setFileName("./");
	const auto b = VParamManager::Instance()->setFileName("./");
	//const int CAMERA = 8;
	//const int BALLNUM = 20;
	//const int BLUE = 0;
	//const int YELLOW = 1;
	//const int BALLMERGEDISTANCE = 0;
	//const int ROBOTMERGEDOSTANCE = 100;
	//const int TEAMS = 2;
	namespace Field{
		const int POS_SIDE_LEFT = 1;
		const int POS_SIDE_RIGHT = -1;
		const int MAX_PLAYER = 16;

		/* 长度单位均为厘米,时间单位均为秒,质量单位为克,角度单位为弧度 */
		/* Ball */
		const double BALL_SIZE = VParamManager::Instance()->value("Physics/ballradius", 21.5).toDouble()*0.1*2; //5; // 半径?直径
		//const double BALL_DECAY = -0.8; // 阻力对球的加速度和速度成正比,单位为 /s
		/* Player */
		const double MAX_PLAYER_SIZE = OParamManager::Instance()->value("Size/carDiameter", 180).toDouble() * 0.1; //18;
		/* Field */
		const QString field = OParamManager::Instance()->value("Alert", "field", "Division_A").toString();
		//const double GOAL_POST_AVOID_LENGTH = 2;         //伸进场地内门柱的避障长度
		const double GOAL_POST_THICKNESS = OParamManager::Instance()->value(field + "/goal_thickness", 20).toDouble() * 0.1; //2;           //门柱宽度
		//const int MAX_BALL_SPEED = 630;
		const bool   IF_USE_ELLIPSE = OParamManager::Instance()->value("Division_B", "if_ellipse_penalty", false).toBool(); //false;             // whether use ellipse penalty

		const double PITCH_LENGTH = OParamManager::Instance()->value(field + "/field_length", 12000).toDouble() * 0.1; //1200; // 场地长
		const double PITCH_WIDTH = OParamManager::Instance()->value(field + "/field_width", 9000).toDouble() * 0.1; //900; // 场地宽
		const double PITCH_MARGIN = OParamManager::Instance()->value(field + "/field_line_width", 10).toDouble() * 0.1; //1; // 场地的边界宽度
		const double CENTER_CIRCLE_R = OParamManager::Instance()->value(field + "/center_radius", 500).toDouble() * 0.1 * 2; //100; // 中圈半径?直径
		const double PENALTY_AREA_WIDTH = OParamManager::Instance()->value(field + "/penalty_width", 2400).toDouble() * 0.1; //240; // 禁区宽度
		const double PENALTY_AREA_DEPTH = OParamManager::Instance()->value(field + "/penalty_depth", 1200).toDouble() * 0.1; //120; // 禁区深度
		const double PENALTY_AREA_R = OParamManager::Instance()->value("Division_B/penalty_radius", 800).toDouble() * 0.1; //80; // 两个圆弧
		const double PENALTY_AREA_L = OParamManager::Instance()->value("Division_B/penalty_area_l", 350).toDouble() * 0.1; //35; // 连接两个圆弧的线段
		const double PENALTY_L = 50;
		const double PENALTY_MARK_X = OParamManager::Instance()->value(field + "/penalty_point", 1200).toDouble() * 0.1; //480; // 点球点的X坐标
		const double FIELD_WALL_DIST = OParamManager::Instance()->value(field + "/field_margin", 300).toDouble() * 0.1;  //20; // 场地护栏到边界的距离
		const double GOAL_WIDTH = OParamManager::Instance()->value(field + "/goal_width", 1200).toDouble() * 0.1; //120; // 球门宽度
		const double GOAL_DEPTH = OParamManager::Instance()->value(field + "/goal_depth", 200).toDouble() * 0.1; //20; // 球门深度
		const double FREE_KICK_AVOID_BALL_DIST = OParamManager::Instance()->value(field + "/field_free_kick", 700).toDouble() * 0.1; //50; // 开任意球的时候,对方必须离球这么远
		const double RATIO = 1.5;
	}
	namespace Math{
		const double PI = VParamManager::Instance()->value("Physics/PI", 3.14159265358979323846).toDouble(); //3.14159265358979323846;
		//const double test = SingleParamManager::Instance()->test_double;
	}
	namespace Vehicle{
		namespace V2{
			const double PLAYER_SIZE = OParamManager::Instance()->value("Size/carDiameter", 180).toDouble() * 0.05; //9;
			const double PLAYER_FRONT_TO_CENTER = VParamManager::Instance()->value("Physics/botCenterToMouth", 76).toDouble() * 0.1; //7.6;
			const double KICK_ANGLE = ::Param::Math::PI*17/180; // 可以击球的最大相对身体角度
			//const double DRIBBLE_SIZE = PLAYER_FRONT_TO_CENTER + ::Param::Field::BALL_SIZE; // 带球时离球的距离
			const double DRIBBLE_ANGLE = ::Param::Math::PI * 17 / 180; // 可以带球的最大相对身体角度
			//const double HEAD_ANGLE = 57*Param::Math::PI / 180; // 前面的开口角度
			const double TOUCH_SHIFT_DIST = 9.96; //做Touch时后退的距离
		}
	}
	namespace AvoidDist{
		const double TEAMMATE_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE * 3;;
		//const double OPP_AVOID_DIST = Param::Field::MAX_PLAYER_SIZE;
		//const double BALL_AVOID_DIST = Param::Field::BALL_SIZE / 2 + 2.0f;
	}
	namespace Vision{
		const double FRAME_RATE = OParamManager::Instance()->value("Alert/frameRate", 75).toDouble(); //75; // 每秒桢数
	}
	namespace Latency{ 
		const float TOTAL_LATED_FRAME = VParamManager::Instance()->value("Physics/total_lated_frame", 4.7).toFloat(); //4.7f; // 延迟的周期数,四舍五入
	}
	namespace Rule{
		const int Version = 2019; // 规则的版本
		const double MaxDribbleDist = 50; // 最大带球距离
	}
}
#endif
