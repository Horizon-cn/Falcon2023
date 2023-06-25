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

		S_GOTOBALL = 1,//若球在场外使用该state开始
		S_GOTOBALL_1, //若球在场内使用该state
		S_GETBALL,
		S_TURN,
		S_CHECK,
		S_BACK
	};
	bool VERBOSE = true; //
	const int dribblePower = 3; //吸球力度
	const int maxGetBall = 50;
	const double stopDist = 3;
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
	double S_GOTOBALL_getball_dir = Utils::Normalize((ball.Pos() - me.Pos()).dir() + (Param::Math::PI) / 4);//场外拿球小车朝向
	double ball2barget = Utils::Normalize((ball.Pos() - targetPos).dir());
	double finalDir = task().player.angle;
	const double exit_speed = 50;                    //exit speed
	double back_speed_x = exit_speed * cos(finalDir + Param::Math::PI);
	double back_speed_y = exit_speed * sin(finalDir + Param::Math::PI);
	double targetdir = Utils::Normalize((targetPos - ball.Pos()).dir());
	CVector me2ball = ball.Pos() - me.Pos();
	CVector me2target = target - me.Pos();
	CVector target2ball = ball.Pos() - target;
	CVector ball2ourGoal = ball.Pos() - ourGoal;
	CVector ourGoal2ball = ourGoal - ball.Pos();

	//开场时球的位置
	bool BallisOutside = std::abs(ball.Pos().y()) >= Param::Field::PITCH_WIDTH / 2 ? true : false;



	//拿球状态判断
	double possession = BallStatus::Instance()->getBallPossession(true, vecNumber);

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
		if (possession >= 0.75) {
			new_state = S_TURN;
			cnt = 0;
		}
		cnt++;
		break;

		//吸球行进
	case S_TURN:
		if ((ball.Pos() - targetPos).mod() < 13) {
			new_state = S_CHECK;
			cnt = 0;
		}
		else if (me2ball.mod() > 20) {
			if (++cnt >= 50) {
				new_state = BEGINNING;
				cnt = 0;
			}
		}
		else {
			cnt = 0;
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
		setSubTask(PlayerRole::makeItSlowGetBall(vecNumber, S_GOTOBALL_getball_dir, PlayerStatus::DRIBBLING | PlayerStatus::ALLOW_DSS | PlayerStatus::NOT_DODGE_PENALTY));
	}
	else if (S_GOTOBALL_1 == state()) {
		setSubTask(PlayerRole::makeItNoneTrajGetBallForStatic(vecNumber, finalDir, CVector(0, 0), flags | PlayerStatus::DODGE_BALL | PlayerStatus::NOT_DODGE_PENALTY, stopDist));
	}
	else if (S_GETBALL == state()) {
		setSubTask(PlayerRole::makeItSlowGetBall(vecNumber, faceDir, flags | PlayerStatus::DRIBBLING | PlayerStatus::NOT_DODGE_PENALTY));
	}
	else if (S_TURN == state()) {//TODO：吸球后退
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
	else if (S_CHECK == state()) {
		if (cnt >= WAIT_BUFFER / 20)
			DribbleStatus::Instance()->setDribbleCommand(vecNumber, 0);//关吸球

		setSubTask(PlayerRole::makeItRun(vecNumber, 0.0, 0.0, 0.0, flags | PlayerStatus::NOT_DODGE_PENALTY));

	}
	else if (S_BACK == state()) {
//<<<<<<< HEAD
		setSubTask(PlayerRole::makeItGoto(vecNumber,ball.Pos()+ Utils::Polar2Vector(100, Utils::Normalize((me.Pos()-ball.Pos()).dir())), flags | PlayerStatus::NOT_DODGE_PENALTY | PlayerStatus::DODGE_BALL));
		DribbleStatus::Instance()->setDribbleCommand(vecNumber, 0);//关吸球
	}
//=======
		setSubTask(PlayerRole::makeItRun(vecNumber, -100 * cos(me.Dir()), -100 * sin(me.Dir()), 0.0, flags | PlayerStatus::NOT_DODGE_PENALTY | PlayerStatus::DODGE_BALL));
		DribbleStatus::Instance()->setDribbleCommand(vecNumber, 0);//关吸球
	}
	else if (S_END == state()) {
		if (ball.Pos().y() >= 0) {
			setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(70, Utils::Normalize(ball2ourGoal.dir() + Param::Math::PI * 120 / 180)), me2ball.dir(), CVector(0, 0), 0, flags | PlayerStatus::NOT_DODGE_PENALTY | PlayerStatus::DODGE_BALL));
		}
		else {
			setSubTask(PlayerRole::makeItGoto(vecNumber, ball.Pos() + Utils::Polar2Vector(70, Utils::Normalize(ball2ourGoal.dir() - Param::Math::PI * 120 / 180)), me2ball.dir(), CVector(0, 0), 0, flags | PlayerStatus::NOT_DODGE_PENALTY | PlayerStatus::DODGE_BALL));
		}

		DribbleStatus::Instance()->setDribbleCommand(vecNumber, 0);//关吸球

	}
//>>>>>>> 9d119eb64869c83bb0e152f13afc6f493a0286d9

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
	bool dirVisionHasBall;
	double meDir = me.Dir();
	double me2Ball = (ball.Pos() - me.Pos()).dir();
	double meDir_me2Ball_Diff = abs(Utils::Normalize((meDir - me2Ball)));
	if (meDir_me2Ball_Diff < Param::Math::PI / 9.0) {
		dirVisionHasBall = true;
	}
	else {
		dirVisionHasBall = false;
	}
	bool isVisionPossession = dirVisionHasBall && distVisionHasBall;
	return isVisionPossession;
}
