/************************************************************************/
/* Copyright (c) SRC, Shanghai Jiao Tong University 					*/
/* Team£º		SRC         											*/
/* HomePage:	https://gitlab.com/src-ssl                      		*/
/************************************************************************/
/* File:	  FetchBall.cpp 											*/
/* Func:	  ±ßÏß´¦ÄÃÇòµÄskill                       					*/
/* Author:	  SUN CHANGJIANG, 2020.7.14									*/
/* E-mail:	  SCJ0013@sjtu.edu.cn										*/
/* Version:	  0.0.1														*/
/************************************************************************/

#include "FetchBall.h"
#include "skill/Factory.h"
#include <utils.h>
#include <WorldModel/DribbleStatus.h>
#include "TaskMediator.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "RobotSensor.h"

namespace {
	enum fetch_ball_state
	{

		S_GOTOBALL = 1,//若球在场外使用该state开始
		S_GOTOBALL_1, //若球在场内使用该state
		S_GETBALL,
		S_TURN,
		S_END,
		S_CHECK,
		S_BACK
	};
	bool VERBOSE = true; //
	const int dribblePower = 3; //吸球力度
	const int maxGetBall = 50;
	const double stopDist = 3;
	int GETBALLMAXCNT = 5;
	int WAIT_BUFFER = 5;

	int fraredOn = 0;
	int fraredOff = 0;
}

CFetchBall::CFetchBall() {
	{
		DECLARE_PARAM_READER_BEGIN(PlaceBall)
			READ_PARAM(VERBOSE)
			READ_PARAM(GETBALLMAXCNT)
			READ_PARAM(WAIT_BUFFER)
			DECLARE_PARAM_READER_END
	}
}

void CFetchBall::plan(const CVisionModule* pVision) {
	if (pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1) {
		setState(BEGINNING);
		fraredOn = 0;
		fraredOff = 0;
		cnt = 0;
	}
	const int flags = task().player.flag;
	const BallVisionT& ball = pVision->Ball();
	const CGeoPoint target = task().player.pos;
	const CGeoPoint targetPos = task().ball.pos;
	const CGeoPoint ourGoal = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
	const int vecNumber = task().executor;
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	//double adjustPre				= task().player.speed_x;
	double adjustPre = 0.2;
	double faceDir = Utils::Normalize((ball.Pos() - me.Pos()).dir());
	double S_GOTOBALL_getball_dir = Utils::Normalize((ball.Pos() - me.Pos()).dir() + (Param::Math::PI) / 4);//场外拿球小车朝向
	double ball2barget = Utils::Normalize((ball.Pos() - targetPos).dir());
	double finalDir = task().player.angle;
	const double exit_speed = 50;                    //exit speed
	double back_speed_x = exit_speed * cos(finalDir + Param::Math::PI);
	double back_speed_y = exit_speed * sin(finalDir + Param::Math::PI);
	CVector me2ball = ball.Pos() - me.Pos();
	CVector me2target = target - me.Pos();
	CVector target2ball = ball.Pos() - target;
	CVector ball2ourGoal = ball.Pos() - ourGoal;
	CVector ourGoal2ball = ourGoal - ball.Pos();

	//开场时球的位置
	bool BallisOutside = std::abs(ball.Pos().y()) >= Param::Field::PITCH_WIDTH / 2 ? true : false;

	//拿球状态判断
	bool frared = RobotSensor::Instance()->IsInfraredOn(vecNumber); //获得红外信息
	if (frared) { fraredOn = fraredOn >= 1024 ? 1024 : fraredOn + 1;	fraredOff = 0; }
	else { fraredOn = 0; fraredOff = fraredOff >= 1024 ? 1024 : fraredOff + 1; }

	//拿球状态判断
	bool isGetBall;
	bool fraGetBall = fraredOn >= 1; //红外是否拿到球
	bool visionGetBall = isVisionHasBall(pVision, vecNumber); //红外与视觉融合
	isGetBall = fraGetBall || visionGetBall;
	if (isGetBall) {
		meGetBall = meGetBall >= maxGetBall ? maxGetBall : meGetBall + 1;
		meLoseBall = 0;
	}
	else {
		meGetBall = 0;
		meLoseBall = meLoseBall >= maxGetBall ? maxGetBall : meLoseBall + 1;
	}

	/********************set subTask********************/
	/*状态机跳转   -by lsp*/
	/***************************************************/
	int new_state = state();
	switch (state()) {
		//初始阶段
	case BEGINNING:
		if (std::abs(ball.Pos().y()) >= (Param::Field::PITCH_WIDTH / 2 - 30)) new_state = S_GOTOBALL;
		else new_state = S_GOTOBALL_1;
		break;

		//场内拿球
	case S_GOTOBALL_1:
		if (std::abs(ball.Pos().y()) >= (Param::Field::PITCH_WIDTH / 2 - 30)) new_state = S_GOTOBALL;
		else if ((me.Pos() - ball.Pos()).mod() < 20 && std::abs((me.Pos() - ball.Pos()).dir() - (ball.Pos() - targetPos).dir()) < 0.5) {
			new_state = S_GETBALL;
			//new_state = S_GOTOBALL;
		}
		break;
		//场外拿球
	case S_GOTOBALL:
		if ((me.Pos() - ball.Pos()).mod() < 20) {
			new_state = S_GETBALL;
			//new_state = S_GOTOBALL;
		}
		break;
		//拿球
	case S_GETBALL:
		//判断是否拿到球
		if (meGetBall >= GETBALLMAXCNT) {
			new_state = S_TURN;
			cnt = 0;
		}
		cnt++;
		break;
		//吸球行进
	case S_TURN:
		if ((ball.Pos() - targetPos).mod() < 13) {
			//if (abs(Utils::Normalize(me.Dir() - finalDir)) < adjustPre) {
			new_state = S_CHECK;
		}
		else if (me2ball.mod() > 20) {
			new_state = BEGINNING;
		}
		break;
		//判断是否放球到正确位置
	case S_CHECK:
		if (cnt >= WAIT_BUFFER) {
			new_state = S_BACK;
			cnt = 0;
		}
		cnt++;
		break;
		//放球结束，后退阶段
	case S_BACK:
		if (me.Pos().dist(targetPos) > 40) {
			new_state = S_END;
		}
		else if ((ball.Pos() - targetPos).mod() > 15) {
			new_state = BEGINNING;
		}
		break;
		//结束状态
	case S_END:
		if ((ball.Pos() - targetPos).mod() > 15) {
			new_state = BEGINNING;
		}
		break;
	default:
		new_state = BEGINNING;
		break;
	}

	/***************************************************/
	/*调试信息      -by lsp*/
	/***************************************************/
	if (true)
	{
		if (S_GOTOBALL == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_GOTOBALL", COLOR_CYAN);
		}
		else if (S_GOTOBALL_1 == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_GOTOBALL_1", COLOR_CYAN);
		}
		else if (S_GETBALL == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_GETBALL", COLOR_CYAN);
		}
		else if (S_TURN == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_TURN", COLOR_CYAN);
		}
		else if (S_END == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_END", COLOR_CYAN);
		}
		else if (S_CHECK == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_CHECK", COLOR_CYAN);
		}
		else if (S_BACK == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_BACK", COLOR_CYAN);
		}
	}

	setState(new_state);
	DribbleStatus::Instance()->setDribbleCommand(vecNumber, dribblePower);

	/***************************************************/
	/*执行具体动作 -by lsp*/
	/***************************************************/

	if (S_GOTOBALL == state()) {
		//CGeoPoint gotoPoint = Utils::MakeInField(ball.Pos(), 2 * Param::Vehicle::V2::PLAYER_SIZE);
		//setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos(), me2ball.dir(), PlayerStatus::ALLOW_DSS));
		//setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos(),-ball2barget, PlayerStatus::ALLOW_DSS | PlayerStatus::DODGE_BALL));
		setSubTask(PlayerRole::makeItSlowGetBall(vecNumber, S_GOTOBALL_getball_dir, PlayerStatus::DRIBBLING | PlayerStatus::ALLOW_DSS | PlayerStatus::NOT_DODGE_PENALTY));
		//setSubTask(PlayerRole::makeItSlowGetBall(vecNumber, faceDir, PlayerStatus::DRIBBLING | PlayerStatus::ALLOW_DSS | PlayerStatus::NOT_DODGE_PENALTY));
	}
	else if (S_GOTOBALL_1 == state()) {
		setSubTask(PlayerRole::makeItNoneTrajGetBall(vecNumber, finalDir, CVector(0, 0), flags | PlayerStatus::DODGE_BALL, stopDist));
	}
	else if (S_GETBALL == state()) {
		//setSubTask(PlayerRole::makeItSimpleGoto(vecNumber, me.Pos(), finalDir, CVector(0, 0), 3.5, PlayerStatus::DRIBBLING | PlayerStatus::ALLOW_DSS | PlayerStatus::NOT_DODGE_PENALTY));
		//setSubTask(PlayerRole::makeItNoneTrajGetBall(vecNumber, faceDir, CVector(0, 0), flags, stopDist));
		//setSubTask(PlayerRole::makeItGoto(vecNumber,ball.Pos(),faceDir , PlayerStatus::DRIBBLING));
		setSubTask(PlayerRole::makeItSlowGetBall(vecNumber, faceDir, flags | PlayerStatus::DRIBBLING));
	}
	else if (S_TURN == state()) {//TODO：吸球后退
		setSubTask(PlayerRole::makeItSimpleGoto(vecNumber, targetPos + me2ball.unit() * (-Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER), faceDir, CVector(0, 0), 0.0, PlayerStatus::DRIBBLING | PlayerStatus::ALLOW_DSS));
	}
	else if (S_CHECK == state()) {
		if (cnt >= WAIT_BUFFER / 2)
			DribbleStatus::Instance()->setDribbleCommand(vecNumber, 0);//关吸球
		setSubTask(PlayerRole::makeItRun(vecNumber, 0.0, 0.0, 0.0, flags));
	}
	else if (S_BACK == state()) {
		setSubTask(PlayerRole::makeItRun(vecNumber, -100 * cos(me.Dir()), -100 * sin(me.Dir()), 0.0, flags));
		// if (ball.Pos().y() >= 0) {
		// 	if (me.Dir()>=0 &&me.Dir()<=Param::Math::PI / 2.0) {
		// 		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(50, Utils::Normalize(ball2ourGoal.dir() + Param::Math::PI * 120 / 180)), me2ball.dir(), CVector(0, 0), 0, flags));
		// 	}
		// 	else if (me.Dir() <= 0 && me.Dir()> -Param::Math::PI / 2.0) {
		// 		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(50, Utils::Normalize(ourGoal2ball.dir())), me2ball.dir(), CVector(0, 0), 0, flags));
		// 	}
		// 	else if (me.Dir() == -Param::Math::PI / 2.0) {
		// 		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(50, Param::Math::PI / 2.0), me2ball.dir(), CVector(0, 0), 0, flags));
		// 	}
		// 	else if (me.Dir() < -Param::Math::PI / 2.0 && me.Dir()>= -Param::Math::PI) {
		// 		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(50, -Param::Math::PI / 6.0), me2ball.dir(), CVector(0, 0), 0, flags));
		// 	}
		// 	else {
		// 		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(50, Utils::Normalize(ball2ourGoal.dir())), me2ball.dir(), CVector(0, 0), 0, flags));
		// 	}
		// }
		// else {
		// 	if (me.Dir() >= 0 && me.Dir() <= Param::Math::PI / 2.0) {
		// 		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(50, Utils::Normalize(ourGoal2ball.dir())), me2ball.dir(), CVector(0, 0), 0, flags));
		// 	}
		// 	else if (me.Dir() <= 0 && me.Dir()> -Param::Math::PI / 2.0) {
		// 		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(50, Utils::Normalize(ball2ourGoal.dir() - Param::Math::PI * 120 / 180)), me2ball.dir(), CVector(0, 0), 0, flags));
		// 	}
		// 	else if (me.Dir() == -Param::Math::PI / 2.0) {
		// 		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(50, Param::Math::PI / 2.0), me2ball.dir(), CVector(0, 0), 0, flags));
		// 	}
		// 	else if (me.Dir() < -Param::Math::PI / 2.0 && me.Dir() >= -Param::Math::PI) {
		// 		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(50, Utils::Normalize(ball2ourGoal.dir())), me2ball.dir(), CVector(0, 0), 0, flags));
		// 	}
		// 	else {
		// 		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(50, -Param::Math::PI / 2.0), me2ball.dir(), CVector(0, 0), 0, flags));
		// 	}
		// }
		DribbleStatus::Instance()->setDribbleCommand(vecNumber, 0);//关吸球
	}
	else if (S_END == state()) {
		//setSubTask(PlayerRole::makeItRun(vecNumber, 0.0, 0.0, 0.0, flags));
		if (ball.Pos().y() >= 0) {
			setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(70, Utils::Normalize(ball2ourGoal.dir() + Param::Math::PI * 120 / 180)), me2ball.dir(), CVector(0, 0), 0, flags));
		}
		else {
			setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(70, Utils::Normalize(ball2ourGoal.dir() - Param::Math::PI * 120 / 180)), me2ball.dir(), CVector(0, 0), 0, flags));
		}

		DribbleStatus::Instance()->setDribbleCommand(vecNumber, 0);//关吸球

	}

	_lastCycle = pVision->Cycle();
	return CStatedTask::plan(pVision);

}

CPlayerCommand* CFetchBall::execute(const CVisionModule* pVision) {
	if (subTask()) {
		return subTask()->execute(pVision);
	}
	return nullptr;
}

bool CFetchBall::isVisionHasBall(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	double visionJudgDist = 11.1;
	bool distVisionHasBall = CVector(me.Pos() - ball.Pos()).mod() <= visionJudgDist;
	//cout << CVector(me.Pos() - ball.Pos()).mod() << endl;
	bool dirVisionHasBall;
	double meDir = me.Dir();
	double me2Ball = (ball.Pos() - me.Pos()).dir();
	double meDir_me2Ball_Diff = abs(Utils::Normalize((meDir - me2Ball)));
	if (meDir_me2Ball_Diff < Param::Math::PI / 9.0) {
		dirVisionHasBall = true;
	}
	else {
		dirVisionHasBall = false;
		//cout << "dir vision dont has ball" << endl;
	}
	bool isVisionPossession = dirVisionHasBall && distVisionHasBall;
	return isVisionPossession;
}