/************************************************************************/
/* Copyright (c) CSC-RL, Zhejiang University							*/
/* Team:		ZJUNlict												*/
/* HomePage:	http://www.nlict.zju.edu.cn/ssl/WelcomePage.html		*/
/************************************************************************/
/* File:	ControlModel.cpp											*/
/* Brief:	C++ Implementation:	Motion Control Warpper					*/
/* Func:	Support calling motion control algorithms					*/
/* Author:	cliffyin, 2012, 04											*/
/* Refer:	some papers													*/
/* E-mail:	cliffyin@zju.edu.cn		cliffyin007@gmail.com				*/
/* Version:	0.0.1														*/
/* Changelog:	2012-04-10	create										*/
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// include files
#include "ControlModel.h"					// for self include
#include <utils.h>							// for some helper functions

#include <cornell/Trajectory.h>				// for Cornell BangBang
#include <cornell/TrajectorySupport.h>

#include <MotionControl/CMmotion.h>
#include <param.h>

using namespace std;

/// Trapezoidal control from CMU : none-zero final velocity trajectory
void CControlModel::makeCmTrajectory(const PlayerVisionT& start, const PlayerVisionT& final, const PlayerCapabilityT& capability, nonZeroMode mode)
{
	_pathList.clear();
	double accel_factor = 1.5;
	double angle_accel_factor = 6.5;

	//cout << "ControlModel"<< endl;
	//cout << start.X()<<" "<<start.Y()<<" "<<start.Vel().mod()<<" "<<start.RotVel()<< endl;
	//cout << final.X() << " " << final.Y() << " " << final.Vel().mod() << endl;
	goto_point_omni(start, final, capability, accel_factor, angle_accel_factor, _nextStep, mode);

}

/// Test NewMotion From TYH. Date:20230409
void CControlModel::makeCmTrajectoryTest(const PlayerVisionT& start, const PlayerVisionT & final, const PlayerCapabilityT& capability, nonZeroMode mode, bool IsGoMiddle)
{
	_pathList.clear();
	double accel_factor = 1.5;
	double angle_accel_factor = 6.5;

	goto_point_omni_test(start, final, capability, accel_factor, angle_accel_factor, _nextStep, mode, IsGoMiddle);
}
