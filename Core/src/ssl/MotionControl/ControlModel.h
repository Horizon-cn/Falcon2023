/************************************************************************/
/* Copyright (c) CSC-RL, Zhejiang University							*/
/* Team:		ZJUNlict												*/
/* HomePage:	http://www.nlict.zju.edu.cn/ssl/WelcomePage.html		*/
/************************************************************************/
/* File:	ControlModel.h												*/
/* Brief:	C++ Interface:	Motion Control Warpper						*/
/* Func:	Support calling motion control algorithms					*/
/* Author:	cliffyin, 2012, 04											*/
/* Refer:	some papers													*/
/* E-mail:	cliffyin@zju.edu.cn		cliffyin007@gmail.com				*/
/* Version:	0.0.1														*/
/* Changelog:	2012-04-10	create										*/
/************************************************************************/

#ifndef _CONTROL_MODEL_H_
#define _CONTROL_MODEL_H_

//////////////////////////////////////////////////////////////////////////
// include files
#include <vector>
#include <WorldModel/WorldDefine.h>			// for RobotPose define
#include <MotionControl/CMmotion.h>
using namespace std;

//////////////////////////////////////////////////////////////////////////
// define the CControlModel class used to support motion control 
// similar to an external wrapper
class CControlModel {
public:
	/// Trapezoidal control from CMU : none-zero final velocity trajectory
	void makeCmTrajectory(const PlayerVisionT& start, const PlayerVisionT& final, const PlayerCapabilityT& capability, nonZeroMode mode = FAST);

	/// Test NewMotion From TYH. Date:20230409
	void makeCmTrajectoryTest(const PlayerVisionT& start, const PlayerVisionT & final, const PlayerCapabilityT& capability, nonZeroMode mode);

	/// Get the real-time next step
	const PlayerVisionT& getNextStep() const { return _nextStep; }

	/// Get the real-time full trajectory
	const vector< vector<double> >& getFullPath() const { return _pathList; }

private:
	/// Next State for the robot includes velocities
	PlayerVisionT _nextStep;

	/// Full Trajectory for the robot
	vector< vector<double> > _pathList;
};

#endif 
