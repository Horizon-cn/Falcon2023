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
#include "BallStatus.h"

namespace {
	enum fetch_ball_state
	{

		S_GOTOBALL = 1,
		S_GETBALL,
		S_BACK,
		S_TURN,
		S_PULL,
		S_CHECK,
		S_END
	};
	bool VERBOSE = true;
	const int maxGetBall = 50;
	const double stopDist = 0;
	int GETBALLMAXCNT = 5;
	int WAIT_BUFFER = 2000;

	int fraredOn = 0;
	int fraredOff = 0;
}

CFetchBall::CFetchBall() {
	{
		VERBOSE = ParamManager::Instance()->VERBOSE;
		GETBALLMAXCNT = ParamManager::Instance()->GETBALLMAXCNT;
		WAIT_BUFFER = ParamManager::Instance()->WAIT_BUFFER;
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
	CGeoPoint CentrePoint = CGeoPoint(0, 0);
	double S_GOTOBALL_getball_dir = Utils::Normalize((ball.Pos() - targetPos).dir());//场外拿球小车朝向
	double ball2barget = Utils::Normalize((ball.Pos() - targetPos).dir());
	double finalDir = task().player.angle;
	const double exit_speed = 50;                    //exit speed
	double back_speed_x = exit_speed * cos(finalDir + Param::Math::PI);
	double back_speed_y = exit_speed * sin(finalDir + Param::Math::PI);
	double targetdir = Utils::Normalize((targetPos - ball.Pos()).dir());
	CVector me2ball = ball.Pos() - me.Pos();
	CVector me2target = target - me.Pos();
	double me2targetDir = me2target.dir();
	double centre2meDir = (me.Pos() - CentrePoint).dir();
	CVector target2ball = ball.Pos() - target;
	CVector ball2ourGoal = ball.Pos() - ourGoal;
	CVector ourGoal2ball = ourGoal - ball.Pos();
	bool isBallOutside = (abs(ball.Pos().y()) > (Param::Field::PITCH_WIDTH / 2 - 50)) || (abs(ball.Pos().x())) > (Param::Field::PITCH_LENGTH / 2 - 50);
	bool isMeOutside = (abs(me.Pos().y()) > (Param::Field::PITCH_WIDTH / 2 - 60)) || (abs(me.Pos().x())) > (Param::Field::PITCH_LENGTH / 2 - 60);
	bool isTargetOutside = (abs(targetPos.y()) > (Param::Field::PITCH_WIDTH / 2 - 50)) || (abs(targetPos.x())) > (Param::Field::PITCH_LENGTH / 2 - 50);


	//拿球状态判断
	double possession = BallStatus::Instance()->getBallPossession(true, vecNumber);

	/********************set subTask********************/
	/*状态机跳转   -by lsp*/
	/***************************************************/
	int new_state = state();
	switch (state()) {
	case BEGINNING:
		if (isBallOutside) {
			new_state = S_GOTOBALL;
			cnt = 0;
		}
		else {
			new_state = S_GOTOBALL;
			cnt = 0;
		}
		cnt++;
		break;

	case S_GOTOBALL:
		if ((me.Pos() - ball.Pos()).mod() < 20) {
			new_state = S_GETBALL;
			cnt = 0;
		}
		cnt++;
		break;

	case S_GETBALL:
		if (!isTargetOutside) {
			if (possession >= 0.9) {
				new_state = S_TURN;
				cnt = 0;
			}
			else {
				if (cnt >= 100)
					new_state = S_BACK;
				cnt = 0;
			}
		}
		else {
			if (possession >= 0.9) {
				new_state = S_PULL;
				cnt = 0;
			}
			else {
				if (cnt >= 100)
					new_state = S_BACK;
				cnt = 0;
			}
		}

		cnt++;
		break;

	case S_BACK:
		if (!isMeOutside) {
			new_state = S_GOTOBALL;
			cnt = 0;
		}
		cnt++;
		break;

		//吸球行进
	case S_TURN:
		if ((ball.Pos() - targetPos).mod() < 5 || ((me.Pos() - targetPos).mod() < 10 && !isVisionHasBall(pVision, vecNumber))) {
			new_state = S_CHECK;
			cnt = 0;
		}
		else {
			cnt = 0;
		}
		cnt++;
		break;
	case S_PULL:
		if ((ball.Pos() - targetPos).mod() < 5 || ((me.Pos() - targetPos).mod() < 10 && !isVisionHasBall(pVision, vecNumber))) {
			new_state = S_CHECK;
			cnt = 0;
		}
		else {
			cnt = 0;
		}
		cnt++;
		break;
		//判断是否放球到正确位置
	case S_CHECK:
		if (cnt >= WAIT_BUFFER) {
			new_state = S_END;
			cnt = 0;
		}
		cnt++;
		break;
		//放球结束，后退阶段
	case S_END:
		if ((ball.Pos() - targetPos).mod() > 15 && cnt++ > 100) {
			new_state = BEGINNING;
			cnt = 0;
		}
		cnt++;
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
		else if (S_GETBALL == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_GETBALL", COLOR_CYAN);
		}
		else if (S_BACK == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_BACK", COLOR_CYAN);
		}
		else if (S_TURN == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_TURN", COLOR_CYAN);
		}
		else if (S_PULL == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_PULL", COLOR_CYAN);
		}
		else if (S_CHECK == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_CHECK", COLOR_CYAN);
		}
		else if (S_END == getState())
		{
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -170), "F_S_END", COLOR_CYAN);
		}

	}

	setState(new_state);
	DribbleStatus::Instance()->setDribbleCommand(vecNumber, 3);

	/***************************************************/
	/*执行具体动作 -by lsp*/
	/***************************************************/

	if (S_GOTOBALL == state()) {
		setSubTask(PlayerRole::makeItNoneTrajGetBallForStatic(vecNumber, S_GOTOBALL_getball_dir, CVector(0, 0), flags | PlayerStatus::DODGE_BALL | PlayerStatus::NOT_DODGE_PENALTY, stopDist));
	}
	else if (S_GETBALL == state()) {
		setSubTask(PlayerRole::makeItNoneTrajGetBallForStatic(vecNumber, S_GOTOBALL_getball_dir, CVector(0, 0), flags | PlayerStatus::DRIBBLING | PlayerStatus::NOT_DODGE_PENALTY));
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -220), ("cnt: " + to_string(cnt)).c_str(), COLOR_GREEN);
	}
	else if (S_BACK == state()) {
		TaskT playerTask;
		playerTask.executor = vecNumber;
		playerTask.player.pos = me.Pos() + Utils::Polar2Vector(50, Utils::Normalize(me2targetDir));
		playerTask.player.angle = targetdir + Param::Math::PI;
		playerTask.player.vel = CVector(0, 0);
		playerTask.player.rotvel = 0.0;
		playerTask.player.flag = PlayerStatus::DRIBBLING | PlayerStatus::ALLOW_DSS | PlayerStatus::NOT_DODGE_PENALTY;
		playerTask.player.max_speed = paramManager->PlACEBALL_SPEED;
		playerTask.player.max_rot_speed = paramManager->PlACEBALL_ROT_SPEED;
		playerTask.player.max_acceleration = paramManager->PlACEBALL_ACCELERATION;
		playerTask.player.max_deceleration = paramManager->PlACEBALL_DECELERATION;
		playerTask.player.max_rot_acceleration = paramManager->PlACEBALL_ROT_ACCELERATION;
		setSubTask(TaskFactoryV2::Instance()->GotoPosition(playerTask));
	}
	else if (S_TURN == state()) {//TODO：吸球转身前进
		TaskT playerTask;
		playerTask.executor = vecNumber;
		playerTask.player.pos = targetPos + me2ball.unit() * (-Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER);
		playerTask.player.angle = targetdir;
		playerTask.player.vel = CVector(0, 0);
		playerTask.player.rotvel = 0.0;
		playerTask.player.flag = PlayerStatus::DRIBBLING | PlayerStatus::ALLOW_DSS | PlayerStatus::NOT_DODGE_PENALTY;
		playerTask.player.max_speed = paramManager->PlACEBALL_SPEED;
		playerTask.player.max_rot_speed = paramManager->PlACEBALL_ROT_SPEED;
		playerTask.player.max_acceleration = paramManager->PlACEBALL_ACCELERATION;
		playerTask.player.max_deceleration = paramManager->PlACEBALL_DECELERATION;
		playerTask.player.max_rot_acceleration = paramManager->PlACEBALL_ROT_ACCELERATION;
		setSubTask(TaskFactoryV2::Instance()->GotoPosition(playerTask));
	}
	else if (S_PULL == state()) {//TODO：吸球后退
		TaskT playerTask;
		playerTask.executor = vecNumber;
		playerTask.player.pos = targetPos + me2ball.unit() * (-Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER);
		playerTask.player.angle = targetdir + Param::Math::PI;
		playerTask.player.vel = CVector(0, 0);
		playerTask.player.rotvel = 0.0;
		playerTask.player.flag = PlayerStatus::DRIBBLING | PlayerStatus::ALLOW_DSS | PlayerStatus::NOT_DODGE_PENALTY;
		playerTask.player.max_speed = paramManager->PlACEBALL_SPEED;
		playerTask.player.max_rot_speed = paramManager->PlACEBALL_ROT_SPEED;
		playerTask.player.max_acceleration = paramManager->PlACEBALL_ACCELERATION;
		playerTask.player.max_deceleration = paramManager->PlACEBALL_DECELERATION;
		playerTask.player.max_rot_acceleration = paramManager->PlACEBALL_ROT_ACCELERATION;
		setSubTask(TaskFactoryV2::Instance()->GotoPosition(playerTask));
	}
	else if (S_CHECK == state()) {
		if (cnt >= WAIT_BUFFER / 20)
			DribbleStatus::Instance()->setDribbleCommand(vecNumber, 0);//关吸球

		setSubTask(PlayerRole::makeItRun(vecNumber, 0.0, 0.0, 0.0, flags | PlayerStatus::NOT_DODGE_PENALTY));

	}
	else if (S_END == state()) {
		setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(100, Utils::Normalize((me.Pos() - ball.Pos()).dir())), flags | PlayerStatus::NOT_DODGE_PENALTY | PlayerStatus::DODGE_BALL));
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
	double visionJudgDist = 11.3;
	bool distVisionHasBall = CVector(me.Pos() - ball.Pos()).mod() <= visionJudgDist;
	bool dirVisionHasBall;
	double playerDir = me.Dir();
	double player2Ball = (ball.Pos() - me.Pos()).dir();
	double playerDir_player2Ball_Diff = fabs(Utils::Normalize((playerDir - player2Ball)));
	if (playerDir_player2Ball_Diff < visionJudgDist * Param::Math::PI / 180.0)
		dirVisionHasBall = true;
	else
		dirVisionHasBall = false;
	bool isVisionPossession = dirVisionHasBall && distVisionHasBall;
	return isVisionPossession;

}
