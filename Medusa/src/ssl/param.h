/**
* @file param.h
* 本文件定义程序中用到的各种参数.
* @date 10/1/2002
* @version 1.0
* @author peter@mail.ustc.edu.cn
*/
#ifndef _PARAM_H_
#define _PARAM_H_
#include <os_param.h> // 和系统有关的参数
//#include "ParamManagerNew.h"
/**
* 参数名字空间Param.
* 这个名字空间定义了程序中用到的所有的参数
*/
namespace Param{
	const int CAMERA = 8;
	const int BALLNUM = 20;
	const int BLUE = 0;
	const int YELLOW = 1;
	const int BALLMERGEDISTANCE = 0;
	const int ROBOTMERGEDOSTANCE = 100;
	const int TEAMS = 2;
	namespace Field{
		const int POS_SIDE_LEFT = 1;
		const int POS_SIDE_RIGHT = -1;
		const int MAX_PLAYER = 16;

		/* 长度单位均为厘米,时间单位均为秒,质量单位为克,角度单位为弧度 */
		/* Ball */
		const double BALL_SIZE	= 5; // 半径
		const double BALL_DECAY = -0.8; // 阻力对球的加速度和速度成正比,单位为 /s
		/* Player */
		const double MAX_PLAYER_SIZE = 18;
		/* Field */
		const double GOAL_POST_AVOID_LENGTH = 2;         //伸进场地内门柱的避障长度
		const double GOAL_POST_THICKNESS = 2;           //门柱宽度
		const int MAX_BALL_SPEED = 630;
		const bool   IF_USE_ELLIPSE = false;             // whether use ellipse penalty

		const double PITCH_LENGTH = 1200; // 场地长
		const double PITCH_WIDTH = 900; // 场地宽
		const double PITCH_MARGIN = 1; // 场地的边界宽度
		const double CENTER_CIRCLE_R = 100; // 中圈半径
		const double PENALTY_AREA_WIDTH = 240; // 禁区宽度
		const double PENALTY_AREA_DEPTH = 120; // 禁区深度
		const double PENALTY_AREA_R = 80; // 两个圆弧
		const double PENALTY_AREA_L = 35; // 连接两个圆弧的线段
		const double PENALTY_L = 50;
		const double PENALTY_MARK_X = 480; // 点球点的X坐标
		const double FIELD_WALL_DIST = 20; // 场地护栏到边界的距离
		const double GOAL_WIDTH = 120; // 球门宽度
		const double GOAL_DEPTH = 20; // 球门深度
		const double FREE_KICK_AVOID_BALL_DIST = 50; // 开任意球的时候,对方必须离球这么远
		const double RATIO = 1.5;
	}
	namespace Math{
		const double PI = 3.14159265358979323846;
		//const double test = SingleParamManager::Instance()->test_double;
	}
	namespace Vehicle{
		namespace V2{
			const double PLAYER_SIZE = 9;
			const double PLAYER_FRONT_TO_CENTER = 7.6;
			const double KICK_ANGLE = ::Param::Math::PI*17/180; // 可以击球的最大相对身体角度
			const double DRIBBLE_SIZE = PLAYER_FRONT_TO_CENTER + ::Param::Field::BALL_SIZE; // 带球时离球的距离
			const double DRIBBLE_ANGLE = ::Param::Math::PI * 17 / 180; // 可以带球的最大相对身体角度
			const double HEAD_ANGLE = 57*Param::Math::PI / 180; // 前面的开口角度
			const double TOUCH_SHIFT_DIST = 9.96; //做Touch时后退的距离
		}
	}
	namespace AvoidDist{
		const double TEAMMATE_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE * 3;;
		const double OPP_AVOID_DIST = Param::Field::MAX_PLAYER_SIZE;
		const double BALL_AVOID_DIST = Param::Field::BALL_SIZE / 2 + 2.0f;
	}
	namespace Vision{
		const double FRAME_RATE = 75; // 每秒桢数
	}
	namespace Latency{ 
        const float TOTAL_LATED_FRAME = 4.7f; // 延迟的周期数,四舍五入
	}
	namespace Rule{
		const int Version = 2019; // 规则的版本
		const double MaxDribbleDist = 50; // 最大带球距离
	}
}
#endif
