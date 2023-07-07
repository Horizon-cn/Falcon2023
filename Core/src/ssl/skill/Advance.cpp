/*
	22.10.10  written by tyh
	ADVANCE NEW
*/
#include "Advance.h"
#include <Vision/VisionModule.h>
#include <WorldModel/KickStatus.h>
#include "RobotSensor.h"
#include "skill/Factory.h"
#include <WorldModel/WorldModel.h>
#include "WorldModel/DribbleStatus.h"
#include "PointCalculation/IndirectDefender.h"
#include <utils.h>
#include <BestPlayer.h>
#include "KickDirection.h"
#include <GDebugEngine.h>
#include <iostream>
#include <BestPlayer.h>
#include <TaskMediator.h>
#include "Global.h"
#include <cstring>

CAdvance::CAdvance()
{
	NowIsShoot = 0;
	KickorPassDir = 0;
	KICK_DIST = paramManager->KICK_DIST;  /*射门允许范围 越高越容易射门*/
	WantToLessShoot = paramManager->WantToLessShoot; /*射门倾向，越低越容易射门*/
	RELIEF_DIST = paramManager->RELIEF_DIST;  /*GET中紧急状况下的RELIEF判断距离*/
	OPP_HAS_BALL_DIST = paramManager->OPP_HAS_BALL_DIST; /*判断敌方是否有球的距离 需要调整*/
	CanPassToWingDist = paramManager->CanPassToWingDist; /*Advance能够传给边锋的临界距离*/
	CanWingShootDist = paramManager->CanWingShootDist; /*边锋能够射门的临界距离*/
	PASS_PRECISION = paramManager->PASS_PRECISION;	/*允许射门最小精度角分母，越大越慢越精确 最低为7最高17*/
	GetBallBias = paramManager->AdGetBallBias;	/*AdvanceGetball的偏差*/
	BalltoMeVelTime = paramManager->BalltoMeVelTime; /*Advance传球给我主动去接的临界时间*/
	OBSTACLE_RADIUS = paramManager->BREAK_OBSTACLE_RADIUS;
	/*射门力度参数*/
	KICKPOWER = paramManager->KICKPOWER;
	CHIPPOWER = paramManager->CHIPPOWER; // 暂时不用了
	ADV_FPASSPOWER_Alpha = paramManager->ADV_FPASSPOWER;
	ADV_CPASSPOWER_Alpha = paramManager->ADV_CPASSPOWER;
	PUSHPOWER = paramManager->ADV_PUSHPOWER;
	// max:600 350
	RELIEF_POWER = paramManager->RELIEF_POWER;
	BACK_POWER = paramManager->BACK_POWER;
	Advance_DEBUG_ENGINE = paramManager->Advance_DEBUG_ENGINE;
	// GetBallV4
	LARGE_ADJUST_ANGLE = paramManager->LARGE_ADJUST_ANGLE;

	DribbleForBreak.DribblePoint = CGeoPoint(-999, -999);
	DribbleForBreak.state = LoseBallForDribble;
	DribbleForBreak.TheMaxDistBetweenMeAndTheBallFortheLose = 1e9;
}


CAdvance::~CAdvance() {

}

void CAdvance::plan(const CVisionModule* pVision)
{
	if (pVision->Cycle() - _cycle > Param::Vision::FRAME_RATE * 0.1) {
		_state = BEGIN;
	}
	/**********************************************************
	* Description: 初始化必要基础参数列表
	* Author: 谭宇宏
	* Created Date: 2022/10/10
	***********************************************************/

	int _executor = task().executor;

	int DoNotEnterDefenseBox = PlayerStatus::DODGE_OUR_DEFENSE_BOX;
	int AllowDribbleFlag = PlayerStatus::DRIBBLING;
	int ShootAllowDribble = DoNotEnterDefenseBox | AllowDribbleFlag;
	int ShootNotNeedDribble = DoNotEnterDefenseBox & (~AllowDribbleFlag);

	/**********************************************************
	* Description: 初始化任务参数列表
	* Author: 谭宇宏
	* Created Date: 2022/10/10
	***********************************************************/
	const PlayerVisionT& me = pVision->OurPlayer(_executor);
	const BallVisionT& ball = pVision->Ball();
	int GoalieNumber = 0;
	int NumofPlayerInFrontfiled = 0;


	double BallToOurGoal = (ball.Pos() - ourGoal).mod();
	CVector me2goal = theirCenter - me.Pos();
	bool isOppHasBall = checkOppHasBall(pVision);
	isBallVeryNearTheOpp = isBallVeryNearTheOppAndIMustGET(pVision);

	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const CVector opp2ball = ball.Pos() - opp.Pos();
	double ball2oppDist = opp2ball.mod();
	double ball2meDist = (ball.Pos() - me.Pos()).mod();

	double me2BestOppDist = CVector(pVision->TheirPlayer(opponentID).Pos() - me.Pos()).mod();

	if (fabs(KickorPassDir) < 1e-3) {
		//ShootPoint = GenerateShootDir;
		KickorPassDir = GenerateShootDir(pVision, _executor);
	}
	
	if (WeCanAlwaysSetKick(pVision, _executor))
		KickStatus::Instance()->setKick(_executor, KICKPOWER);
	else KickStatus::Instance()->setBothKick(_executor, 0, 0);
	
	NumberOfSupport = min(6, AREANUM);/*暂时只考虑对面半场六个*/
	for (int i = 0; i < NumberOfSupport; ++i)
		SupportPoint[i] = GPUBestAlgThread::Instance()->getBestPointFromArea(i);/* Gpu算点 */

	IHaveSupport = CanSupportKick(pVision, _executor); // 是否存在支援车,并生成支援车

	//500，-300 -290
	if (Advance_DEBUG_ENGINE) {
		char IsSupportOkMsg[100];
		char TheBestSupportMsg[100];
		//sprintf(getBallDistdebugmsg, "%f", getBallDist);
		sprintf(IsSupportOkMsg, "%d", IHaveSupport);
		sprintf(TheBestSupportMsg, "%d", TheBestSupportNumber);
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -300), "IsSupportOK:", COLOR_YELLOW);
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -275), "TheBestSPidx:", COLOR_YELLOW);
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(600, -300), IsSupportOkMsg, COLOR_YELLOW);
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(600, -275), TheBestSupportMsg, COLOR_YELLOW);
	}
	NumOfOurPlayer = NumOfTheirPlayerfrontMe = 0;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (pVision->OurPlayer(i).Valid() && i != GoalieNumber) {
			NumOfOurPlayer++;
			if (pVision->OurPlayer(i).Pos().x() > Param::Field::PITCH_LENGTH / 10)
				NumofPlayerInFrontfiled++;
		}
		if (pVision->TheirPlayer(i).Valid()) {
			if (pVision->OurPlayer(i).Pos().x() > me.Pos().x())
				NumOfTheirPlayerfrontMe++;
		}
	}
	// 可视化球的预测位置
	/*
	for (int i = 0; i < 6; i++) {
		CGeoPoint ball_predict_pos = GPUBestAlgThread::Instance()->getBallPosFromFrame(ball.Pos(), ball.Vel(), i * 8);
		GDebugEngine::Instance()->gui_debug_msg(ball_predict_pos, (to_string(i * 8)).c_str(), COLOR_YELLOW);
		GDebugEngine::Instance()->gui_debug_x(ball_predict_pos, COLOR_BLUE);
	}
	*/
	/**********************************************************
	* Description: 状态分配
	* Author: 谭宇宏
	* Created Date: 2022/10/10
	***********************************************************/
	Advance_DEBUG_ENGINE = 1;
	MeIsInWhichArea = InWhichArea(pVision, _executor);

	UpdateTheDribblePointForbreak(pVision, _executor);

	switch (_state) {
	case BEGIN:
		_state = GET;
		break;
	case GET:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push GET", COLOR_YELLOW);
		if (isOppHasBall || isBallVeryNearTheOpp){
			_state = GET;
			break;
		}
		else if (BallStatus::Instance()->getBallPossession(true, _executor) == 0 && ball2meDist > 10) 
			_state = GET;
		/*
		else if (NumOfOurPlayer >= 3 && NumOfOurPlayer <= 5)
		{
			if (me.X() < 0)
				_state = JUSTCHIPPASS;
			else if (me.X() < Param::Field::PITCH_LENGTH / 6)
				_state = BREAKING;
			else
				_state = BREAKSHOOT;
			break;
		}*/
		if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.3) {
			_state = GenerateNextState(pVision, _executor);
			break;
		}
		else {
			_state = GenerateNextState(pVision, _executor);
			if (CanWeUseChaseBecauseOfGetBallV3(pVision, _executor)) {
				if (_state == KICK) {
					_state = CHASEKICK;
					break;
				}
			}
			if (OppIsFarThanMe(pVision, _executor) && _state == PUSHOUT) {
				_state = PUSHOUT;
				break;
			}
			_state = GET;
			break;
		}
		break;

	case KICK:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push KICK", COLOR_YELLOW);
		if (BallStatus::Instance()->getBallPossession(true, _executor) == 0 && ball2meDist > 10) _state = GET;
		//  这个状态跳转有点问题
		else if ((!isDirOK(pVision, _executor, KickorPassDir, 1)) && fabs(Utils::Normalize((me.Dir() - KickorPassDir))) < Param::Math::PI * 1.5 / 180) {
			if (MeIsInWhichArea != CenterArea) {
				_state = BREAKSHOOT;
				NowIsShoot = 2;
			}
			else _state = BREAKING, NowIsShoot = 0;
		}
		break;
	case PASS:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push PASS", COLOR_YELLOW);
		if (BallStatus::Instance()->getBallPossession(true, _executor) == 0 && ball2meDist > 10) _state = GET;
		if (Me2OppTooclose(pVision, _executor)) _state = BREAKING;
		break;
	case JUSTCHIPPASS:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push CHIP", COLOR_YELLOW);
		if (BallStatus::Instance()->getBallPossession(true, _executor) == 0 && ball2meDist > 10) _state = GET;
		if (Me2OppTooclose(pVision, _executor)) _state = BREAKING;
		break;
	case BREAKSHOOT:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push BREAK", COLOR_YELLOW);
		if (BallStatus::Instance()->getBallPossession(true, _executor) == 0 && ball2meDist > 10) _state = GET;
		break;
	case PUSHOUT:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push OUT", COLOR_YELLOW);
		if (isOppHasBall || isBallVeryNearTheOpp) {
			_state = GET;
			break;
		}
		if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.3) {
			_state = GenerateNextState(pVision, _executor);
			if (_state == KICK) NowIsShoot = 1;
			else if (_state == BREAKSHOOT)NowIsShoot = 2;
			break;
		}
		else {
			_state = GenerateNextState(pVision, _executor);
			if (CanWeUseChaseBecauseOfGetBallV3(pVision, _executor)) {
				if (_state == KICK) {
					_state = CHASEKICK;
					break;
				}
			}
			if (OppIsFarThanMe(pVision, _executor) && _state == PUSHOUT) {
				_state = PUSHOUT;
				break;
			}
			_state = GET;
			break;
		}
		break;
	case BREAKING:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push Breaking", COLOR_YELLOW);
		if (BallStatus::Instance()->getBallPossession(true, _executor) == 0 && ball2meDist > 10) _state = GET;
		break;
	case CHASEKICK:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push CHASEKICK", COLOR_YELLOW);
		if (isOppHasBall || isBallVeryNearTheOpp) {
			_state = GET;
			break;
		}
		if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.9) {
			_state = BREAKSHOOT;
			break;
		}
		else if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.3) {
			_state = CHASEKICK;
			break;
		}
		else {
			_state = GenerateNextState(pVision, _executor);
			if (CanWeUseChaseBecauseOfGetBallV3(pVision, _executor)) {
				if (_state == KICK) {
					_state = CHASEKICK;
					break;
				}
			}
			else _state = GET;
		}
		break;
		/*
	case CHASEPUSH:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push CHASEPUSH", COLOR_YELLOW);
		if (GenerateNextState(pVision, _executor) != PUSHOUT || !CanWeUseChaseBecauseOfGetBallV3(pVision, _executor)) _state = GET;
		if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.3) _state = PUSHOUT;
		break;
		*/
	}
	
	/*
	if (BallStatus::Instance()->getBallPossession(true, _executor) > 0.3) {
		//_state = PUSHOUT;
		//_state = GET;
		//_state = BREAKSHOOT;
		_state = PASS;
	}
	else _state = GET;
	*/
	/**********************************************************
	* Description: 状态执行
	* Author: 谭宇宏
	* Created Date: 2022/10/10
	***********************************************************/
	bool isChipKick = 0;
	double kickPower = 0;

	double ThePower = 0;
	if (_state != KICK && _state != BREAKSHOOT) {
		NowIsShoot = 0;
	}
	switch (_state) {
	case GET:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "let GET", COLOR_YELLOW);
		if (ball2meDist > 50 || (isPassBalltoMe(pVision, _executor)))NowIsShoot = 0;
		/*清空shoot标记*/
		if (!ball.Valid()) {
			/*球不合法的情况*/
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "Ball invalid", COLOR_ORANGE);
			double faceDir = opp.Dir() + Param::Math::PI;
			setSubTask(PlayerRole::makeItChaseKickV2(_executor, faceDir, ShootNotNeedDribble));
		}
		else if (checkTheyCanShoot(pVision, _executor)) {
			/*敌人有射门机会 进行封堵*/
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "they can shoot", COLOR_ORANGE);
			double faceDir = opp.Dir() + Param::Math::PI;
			setSubTask(PlayerRole::makeItChaseKickV2(_executor, faceDir, ShootNotNeedDribble));
		}
		
		else if (isPassBalltoMe(pVision, _executor) ) {
			/*我方给我进行传球*/
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "pass ball to me", COLOR_ORANGE);

			if (me2goal.mod() < KICK_DIST && (Me2OppTooclose(pVision, _executor))) {
				KickorPassDir = GenerateShootDir(pVision, _executor);
				//KickorPassDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(_executor).Pos());
			}
			else KickorPassDir = (PassPoint - me.Pos()).dir();
			setSubTask(PlayerRole::makeItReceivePass(_executor, KickorPassDir));
		}
	
		else {
			/*并没有得到球 需要去getball*/
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -300), "LOSE and GETBALL", COLOR_ORANGE);
			//KickorPassDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(_executor).Pos());
			/*此处朝向可持久化即可 不需要进行改变*/
			setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, KickorPassDir, CVector(0, 0), ShootNotNeedDribble, GetBallBias));
		}
		break;
	case KICK:   // 射门
		NowIsShoot = 1;
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "KICK", COLOR_YELLOW);
		KickorPassDir = GenerateShootDir(pVision, _executor);
		//KickorPassDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(_executor).Pos());
		if (Utils::InTheirPenaltyArea(ball.Pos(), 0)) {
			/*如果球在对方禁区*/
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "ball in their PEN", COLOR_ORANGE);
			KickStatus::Instance()->setKick(_executor, KICKPOWER);
			//setSubTask(PlayerRole::makeItShootBallV2(_executor, KickorPassDir, ShootNotNeedDribble));
		}
		else {
			/*正常KICK阶段  需要区分是否方向已经转向成功  此处尚未完备可能存在BUG*/
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "Let Kick", COLOR_ORANGE);
			if (isDirOK(pVision, _executor, KickorPassDir, 1)) {
				if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "Kick isDirOK", COLOR_ORANGE);
				setSubTask(PlayerRole::makeItJustKick(_executor, 0, KICKPOWER));
			}
			else {
				if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "Kick is NOT DirOK ", COLOR_ORANGE);
				KickorPassDir = GenerateShootDir(pVision, _executor);
				setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, KickorPassDir, CVector(0, 0), ShootNotNeedDribble, GetBallBias));
			}
		}
		break;
	case PASS:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "PASS", COLOR_YELLOW);
		PassPoint = SupportPoint[TheBestSupportNumber];
		KickorPassDir = (PassPoint - me.Pos()).dir();

		if (isDirOK(pVision, _executor, KickorPassDir, 0)) {
			bool IsFlatKick = toChipOrToFlat(pVision, _executor, PassPoint);
			if (IsFlatKick) {
				ThePower = GetFPassPower(me.Pos(), PassPoint);
			}
			else {
				ThePower = GetCPassPower(me.Pos(), PassPoint);
			}
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "PASS isDirOK", COLOR_ORANGE);

			setSubTask(PlayerRole::makeItJustKick(_executor, !IsFlatKick, ThePower));
			//setSubTask(PlayerRole::makeItSimpleGoto(_executor, ball.Pos(), (ball.Pos() - me.Pos()).dir(), task().player.flag));
			TaskMediator::Instance()->setAdvancerPassTo(PassPoint, NumberOfSupport);
		}
		else {
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "PASS is NOT DirOK ", COLOR_ORANGE);
			setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, KickorPassDir, CVector(0, 0), ShootNotNeedDribble, GetBallBias));
		}
		break;

	case JUSTCHIPPASS:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "JUSTCHIP", COLOR_YELLOW);
		//KickStatus::Instance()->setBothKick(_executor, 0, 0);
		if (IHaveSupport) {
			PassPoint = SupportPoint[TheBestSupportNumber];
			KickorPassDir = (PassPoint - me.Pos()).dir();
			ThePower = GetCPassPower(me.Pos(), PassPoint);
		}
		else {
			PassPoint = theirCenter;
			KickorPassDir = (PassPoint - me.Pos()).dir();
			ThePower = GetCPassPower(me.Pos(), PassPoint) * 0.8;
		}
		if (isDirOK(pVision, _executor, KickorPassDir, 0)) {
			setSubTask(PlayerRole::makeItJustKick(_executor, 1, ThePower));
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "JUSTCHIP isDirOK", COLOR_ORANGE);
			TaskMediator::Instance()->setAdvancerPassTo(PassPoint, NumberOfSupport);
		}
		else {
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "JUSTCHIP is NOT DirOK ", COLOR_ORANGE);
			setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, KickorPassDir, CVector(0, 0), ShootNotNeedDribble, GetBallBias));
		}
		break;

	case BREAKSHOOT:
		NowIsShoot = 2;
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "BREAKSHOOT", COLOR_YELLOW);
		//KickStatus::Instance()->setBothKick(_executor, 0, 0);
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -420), ("Opp_Ahead:"+ to_string(opp_ahead(pVision, _executor))).c_str(), COLOR_YELLOW);
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -440), ("CanSupportKick:" + to_string(CanSupportKick(pVision, _executor))).c_str(), COLOR_YELLOW);
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -460), ("ClosetoPosPlayerDist:" + to_string(pVision->TheirPlayer(getTheirMostClosetoPosPlayerNum(pVision, SupportPoint[TheBestSupportNumber])).Pos().dist(SupportPoint[TheBestSupportNumber]))).c_str(), COLOR_YELLOW);
		if (opp_ahead(pVision, _executor)>=5 && IHaveSupport && pVision->TheirPlayer(getTheirMostClosetoPosPlayerNum(pVision, SupportPoint[TheBestSupportNumber])).Pos().dist(SupportPoint[TheBestSupportNumber]) >= 60)
		{
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "BREAKPASS__PASS", COLOR_YELLOW);
			PassPoint = SupportPoint[TheBestSupportNumber];
			GDebugEngine::Instance()->gui_debug_x(SupportPoint[TheBestSupportNumber], COLOR_CYAN);
			KickorPassDir = (PassPoint - me.Pos()).dir();
			GDebugEngine::Instance()->gui_debug_line(me.Pos(), SupportPoint[TheBestSupportNumber], COLOR_CYAN);
			if (isDirOK(pVision, _executor, KickorPassDir, 0))
			{
				ThePower = GetCPassPower(me.Pos(), PassPoint);
				setSubTask(PlayerRole::makeItJustKick(_executor, 1, ThePower));
				TaskMediator::Instance()->setAdvancerPassTo(PassPoint, NumberOfSupport);
			}
			else
			{
				setSubTask(PlayerRole::makeItBreak(_executor, KickorPassDir, false, false, false, DribbleForBreak.DribblePoint));
			}
		}
		else
		{
			ShootPoint = (pVision->Cycle() % 60 == 0) ? GenerateBreakShootPoint(pVision, _executor) : ShootPoint;
			KickorPassDir = (ShootPoint - me.Pos()).dir(); 
			setSubTask(PlayerRole::makeItBreak(_executor, 0.0, true, false, false, DribbleForBreak.DribblePoint));

		}
		
		break;

	case BREAKING:
	{
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "BREAKPASS", COLOR_YELLOW);
		KickorPassDir = GenerateShootDir(pVision, _executor);
		if (isDirOK(pVision, _executor, KickorPassDir, 1)) {  //能射门了
			if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "BREAKPASS__KICK", COLOR_YELLOW);
			setSubTask(PlayerRole::makeItJustKick(_executor, 0, KICKPOWER));
		}
		else
		{
			if (IHaveSupport) {
				PassPoint = SupportPoint[TheBestSupportNumber];
				KickorPassDir = (PassPoint - me.Pos()).dir();
				ThePower = GetCPassPower(me.Pos(), PassPoint);
			}
			else {
				PassPoint = theirCenter;
				KickorPassDir = (PassPoint - me.Pos()).dir();
				ThePower = GetCPassPower(me.Pos(), PassPoint) * 0.8;
			}
			if (isDirOK(pVision, _executor, KickorPassDir, 0)) {   //如果能传球
				if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "BREAKPASS__PASS", COLOR_YELLOW);
				setSubTask(PlayerRole::makeItJustKick(_executor, 1, ThePower));
				TaskMediator::Instance()->setAdvancerPassTo(PassPoint, NumberOfSupport);
			}
			else
			{
				bool flag = true;
				for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
					if (!pVision->TheirPlayer(i).Valid()) continue;
					auto enemy = pVision->TheirPlayer(i);
					double x = enemy.X(), y = enemy.Y();
					double x1 = me.X(), y1 = me.Y(), theta = me.Dir();
					if (x < me.X() || enemy.Pos().dist(me.Pos())>200) continue;
					CGeoLine my_direction(me.Pos(), theta);
					CGeoPoint projection_point = my_direction.projection(enemy.Pos());
					double r = projection_point.dist(enemy.Pos());
					double me2prodist = projection_point.dist(me.Pos());
					if (!((r > 40 || me2prodist > 150) && me.Dir() <= Param::Math::PI / 3 && me.Dir() >= -Param::Math::PI / 3 && fabs(me.Y()) < Param::Field::PITCH_WIDTH * 2 / 3))
						flag = false;
				}
				if (me2BestOppDist > 40)  //80 mayebe too large
				{
					PassPoint = generateNormalPushPoint(pVision, _executor);// : PassPoint;
					KickorPassDir = (PassPoint - me.Pos()).dir();
					setSubTask(PlayerRole::makeItlightkick(_executor, KickorPassDir));
				}
				else if (flag)
				{
					setSubTask(PlayerRole::makeItlightkick(_executor, me.Dir()));
					if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "BREAKPASS__PUSH", COLOR_YELLOW);
				}
				else {
					setSubTask(PlayerRole::makeItBreak(_executor, generateBreakingDir(pVision, _executor), false, false, false, DribbleForBreak.DribblePoint));
					//setSubTask(PlayerRole::makeItBreak(_executor, generateBreakingDir(pVision, _executor), false, false, false));
				}
			}
		}
		break;
	}

	case PUSHOUT:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "PUSHOUT", COLOR_YELLOW);
		
		PassPoint = generateNormalPushPoint(pVision, _executor);// : PassPoint;
		KickorPassDir = (PassPoint - me.Pos()).dir();
		if(OppIsFarThanMe(pVision, _executor))
			setSubTask(PlayerRole::makeItlightkick(_executor, KickorPassDir));
		else
			setSubTask(PlayerRole::makeItlightkick(_executor, KickorPassDir, 180));
		break;

	case CHASEKICK:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "CHASEKICK", COLOR_YELLOW);
		KickorPassDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(_executor).Pos());
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "CHASEKICK", COLOR_ORANGE);
		setSubTask(PlayerRole::makeItChaseKickV2(_executor, KickorPassDir, ShootNotNeedDribble));
		break;
		/*
	case CHASEPUSH:
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "CHASEPUSH", COLOR_YELLOW);
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "CHASEPUSH", COLOR_ORANGE);
		PassPoint = generateNormalPushPoint(pVision, _executor);
		KickorPassDir = (PassPoint - me.Pos()).dir();
		if(fabs(me.Dir()) < 1.5) KickStatus::Instance()->setKick(_executor, 90);
		else KickStatus::Instance()->setKick(_executor, 0);
		setSubTask(PlayerRole::makeItChaseKickV2(_executor, KickorPassDir, ShootNotNeedDribble, GetFPassPower(ball.Pos(), PassPoint)));
		break;
	*/
	}
	//setSubTask(PlayerRole::makeItStop(_executor, 0));
	_cycle = pVision->Cycle();
	CStatedTask::plan(pVision);
}

/**********************************************************
	* Description: 检测类函数，用于视觉与位置等判断
	* Author: 谭宇宏
	* Created Date: 2022/10/10
***********************************************************/
bool CAdvance::isVisionHasBall(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	double visionJudgDist = 11.3;
	bool distVisionHasBall = CVector(me.Pos() - ball.Pos()).mod() <= visionJudgDist;
	bool dirVisionHasBall;
	double meDir = me.Dir();
	double me2Ball = (ball.Pos() - me.Pos()).dir();
	double meDir_me2Ball_Diff = abs(Utils::Normalize((meDir - me2Ball)));
	if (meDir_me2Ball_Diff < Param::Math::PI / 6.0)
		dirVisionHasBall = true;
	else
		dirVisionHasBall = false;
	bool isVisionPossession = dirVisionHasBall && distVisionHasBall;
	return isVisionPossession;
}

bool CAdvance::checkOppHasBall(const CVisionModule* pVision) {
	int _executor = task().executor;
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(_executor);
	const CVector self2ball = ball.Pos() - me.Pos();
	opponentID = getTheirMostClosetoPosPlayerNum(pVision, pVision->Ball().Pos());
	Oppfront = getTheirMostCloseAndFronttoPosPlayerNum(pVision, pVision->Ball().Pos());
	const PlayerVisionT& opponent = pVision->TheirPlayer(opponentID);
	if (Advance_DEBUG_ENGINE)GDebugEngine::Instance()->gui_debug_msg(opponent.Pos(), "Best Opp!", COLOR_WHITE);
	CVector opponent2ball = ball.Pos() - opponent.Pos();
	double opponent2ball_diff = fabs(Utils::Normalize(opponent2ball.dir() - opponent.Dir()));
	double judgeDist = OPP_HAS_BALL_DIST;
	double Dirthreshold = 16.0;
	if (opponent2ball.mod() < judgeDist && opponent2ball_diff < Param::Math::PI * Dirthreshold / 180)
		return true; // take opponent's direction into consideration.If direction not towards the ball,ignore it
	else
		return false;
}
int CAdvance::getTheirMostClosetoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos) {
	double dist = 1000;
	int num = 0;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (pVision->TheirPlayer(i).Valid()) {
			if (pVision->TheirPlayer(i).Pos().dist(pos) < dist) {
				dist = pVision->TheirPlayer(i).Pos().dist(pos);
				num = i;
			}
		}
	}
	return num;
}
int CAdvance::getTheirMostCloseAndFronttoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos) {
	double dist = 1000;
	int num = 0;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (pVision->TheirPlayer(i).Valid()) {
			if (pVision->TheirPlayer(i).Pos().dist(pos) < dist && pVision->TheirPlayer(i).X() > pos.x()) {
				dist = pVision->TheirPlayer(i).Pos().dist(pos);
				num = i;
			}
		}
	}
	return num;
}
bool CAdvance::checkBallFront(const CVisionModule* pVision, double angle) {
	/*判断球是否在敌人前面 存在夹角要求*/

	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	CVector opp2ball = ball.Pos() - opp.Pos();
	bool ballDirFrontOpp = abs(Utils::Normalize(opp.Dir() - opp2ball.dir())) < angle;
	bool ballDistFrontOpp = opp2ball.mod() < OPP_HAS_BALL_DIST + 10;
	//GDebugEngine::Instance()->gui_debug_line(opp.Pos(),opp.Pos() + Utils::Polar2Vector(200 , 0),COLOR_BLACK);
	bool isBallFrontOpp = ballDirFrontOpp && ballDistFrontOpp;
	//printf("here %d\n",isBallFrontOpp);
	return isBallFrontOpp;
}

bool CAdvance::isPassBalltoMe(const CVisionModule* pVision, int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	CVector ball2me = me.Pos() - ball.Pos();
	double diff_ballMoving2Me = Utils::Normalize(ball2me.dir() - ball.Vel().dir());
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	CVector opp2me = me.Pos() - opp.Pos();
	//    printf("%.3f %.3f\n",(opp.Pos() - me.Pos()).mod(), Utils::Normalize(ball2me.dir() - opp2me.dir()));
	bool nearBoundary = fabs(me.Pos().x()) > Param::Field::PITCH_LENGTH / 2 - Param::Vehicle::V2::PLAYER_SIZE * 4 ||
		fabs(me.Pos().y()) > Param::Field::PITCH_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE * 4; // 靠近边界不能让开
	if ((opp.Pos() - me.Pos()).mod() < 60 && Utils::Normalize(ball2me.dir() - opp2me.dir()) < Param::Math::PI / 7 && !nearBoundary) return false;
	if (ball.Vel().mod() < 175.0 && !nearBoundary) return false;
	if (ball.Valid() && abs(diff_ballMoving2Me) < Param::Math::PI / 7.5 && (ball2me.mod() / ball.Vel().mod() < BalltoMeVelTime)) {//
		return true;
	}
	return false;
}

bool CAdvance::isTheLineBlocked(const CVisionModule* pVision, CGeoPoint startPoint, CGeoPoint targetPoint) {
	/*该条路径上是否会被敌人阻挡*/
	double k_m = WantToLessShoot;
	double opp2LineDist = TheMinDistBetweenTheOppAndTheLine(pVision, startPoint, targetPoint);
	if (opp2LineDist < k_m * Param::Vehicle::V2::PLAYER_SIZE)return true;
	return false;
}

bool CAdvance::IsOurNearHere(const CVisionModule* pVision, int supportIndex, int vecNumber) {
	int supporter = TaskMediator::Instance()->supporter(supportIndex);
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	if(pVision->OurPlayer(supporter).Pos().dist(me.Pos()) > 160)
		if (supporter != 0 && pVision->OurPlayer(supporter).Pos().dist(SupportPoint[supportIndex]) < 60)
			return true;
	return false;
}

/*这里有bug？*/

int CAdvance::TheirRobotInBreakArea(const CVisionModule* pVision, const int vecNumber) {
	int cnt = 0, n = 0;
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	while (n <= Param::Field::MAX_PLAYER) {
		if (!pVision->TheirPlayer(n).Valid()) { n++; continue; }
		const PlayerVisionT& opp = pVision->TheirPlayer(n);
		double x = opp.X(), y = opp.Y();
		cnt += (abs(y) < 180 && (x > 250 || x > me.Pos().x()));
		n++;
	}
	return cnt;
}
bool CAdvance::isDirOK(const CVisionModule* pVision, int vecNumber, double targetDir, int IsShoot) {
	if (IsShoot) {
		return canScore(pVision, vecNumber, OBSTACLE_RADIUS, pVision->OurPlayer(vecNumber).Dir());
	}
	double PASSPrecision = PASS_PRECISION * Param::Math::PI / 180;
	//double offset = 0.05;
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	//double my2ballDir = (ball.Pos() - me.Pos()).dir();
	double myDir = me.Dir();
	CVector opp2ball = ball.Pos() - opp.Pos();
	CVector ball2goal = theirCenter - ball.Pos();

	//if (fabs(my2ballDir - targetDir) < PASSPrecision) return true;
	if (fabs(Utils::Normalize(myDir - targetDir)) < PASSPrecision) return true;

	else return false;
}
/*
*		The Data List
		const double PITCH_LENGTH = OParamManager::Instance()->value(field + "/field_length", 12000).toDouble() * 0.1; //1200; // 场地长
		const double PITCH_WIDTH = OParamManager::Instance()->value(field + "/field_width", 9000).toDouble() * 0.1; //900; // 场地宽
		const double PITCH_MARGIN = OParamManager::Instance()->value(field + "/field_line_width", 10).toDouble() * 0.1; //1; // 场地的边界宽度
		const double CENTER_CIRCLE_R = OParamManager::Instance()->value(field + "/center_radius", 500).toDouble() * 0.1 * 2; //100; // 中圈半径?直径
		const double PENALTY_AREA_WIDTH = OParamManager::Instance()->value(field + "/penalty_width", 2400).toDouble() * 0.1; //240; // 禁区宽度
		const double PENALTY_AREA_DEPTH = OParamManager::Instance()->value(field + "/penalty_depth", 1200).toDouble() * 0.1; //120; // 禁区深度

		DefenceArea = 0,
		SideArea,
		CornerArea,
		KICKArea,
		CanNOTBreakArea,
		CenterArea

		*/

int CAdvance::InWhichArea(const CVisionModule* pVision, int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const double MeX = me.X(), MeY = me.Y();
	const double DefenceLineX = 0.0 * Param::Field::PITCH_LENGTH / 900;
	const double SideLineY = 235.0 * Param::Field::PITCH_WIDTH / 600;
	const double CornerLineX = 350.0 * Param::Field::PITCH_LENGTH / 900;
	const double KICKDist = KICK_DIST * Param::Field::PITCH_LENGTH / 900;
	const double CanNotBreakAreaX = 425.0 * Param::Field::PITCH_LENGTH / 900;
	const double CanNotBreakAreaY = 260.0 * Param::Field::PITCH_WIDTH / 600;
	const double ReliefDist = RELIEF_DIST * Param::Field::PITCH_LENGTH / 900;
	int NowArea = 0;
	if ((me.Pos() - ourGoal).mod() < ReliefDist) {
		NowArea = ReliefArea;
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(525, -345), "ReliefArea", COLOR_CYAN);
	}
	else if (MeX < DefenceLineX) {
		NowArea = DefenceArea;
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(525, -345), "DefenceArea", COLOR_CYAN);
	}
	else if (MeX > CanNotBreakAreaX || fabs(MeY) > CanNotBreakAreaY) {
		NowArea = CanNOTBreakArea;
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(525, -345), "CanNOTBreakArea", COLOR_CYAN);
	}
	else if (fabs(MeX) > CornerLineX) {
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(525, -345), "CornerArea", COLOR_CYAN);
		NowArea = CornerArea;
	}
	else if (fabs(MeY) > SideLineY) {
		NowArea = SideArea;
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(525, -345), "SideArea", COLOR_CYAN);
	}
	else if ((me.Pos() - theirCenter).mod() < KICKDist) {
		NowArea = KICKArea;
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(525, -345), "KICKArea", COLOR_CYAN);
	}
	else {
		NowArea = CenterArea;
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(525, -345), "CenterArea", COLOR_CYAN);
	}
	return NowArea;
}
/**********************************************************
	* Description: 状态切换判定类函数，用于状态转化之间的判断
	* Author: 谭宇宏
	* Created Date: 2022/10/10
***********************************************************/
bool CAdvance::tendToShoot(const CVisionModule* pVision, int vecNumber) {
	/*判断现在能否射门*/
	// NEEDMODIFY
	if (MeIsInWhichArea == KICKArea || MeIsInWhichArea == CornerArea || MeIsInWhichArea == CanNOTBreakArea) {
		int n = 0;
		int best_n = 0;
		const BallVisionT& ball = pVision->Ball();
		const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
		bool shootBlocked = false;
		double kickDir = KickDirection::Instance()->getPointShootDir(pVision, ball.Pos());
		if (fabs(kickDir - 1000.0) < 10) return false;
		/*修复tendToShoot与getPointShootDir判断不兼容的问题*/
		CGeoLine ball2ourGoal = CGeoLine(ball.Pos(), kickDir);
		CGeoPoint projectionPoint;
		double k_m = WantToLessShoot;
		double opp2LineDist = 1000;
		while (n <= Param::Field::MAX_PLAYER) {
			const PlayerVisionT& opp = pVision->TheirPlayer(n);
			if (!opp.Valid()) { n++; continue; }
			if (opp.Pos().dist(ball.Pos()) < 50) {
				k_m = 1.0;
			}
			else k_m = WantToLessShoot;
			projectionPoint = ball2ourGoal.projection(opp.Pos());
			if (opp2LineDist > (projectionPoint - opp.Pos()).mod() && projectionPoint.x() >= ball.X()) {
				opp2LineDist = (projectionPoint - opp.Pos()).mod();
				best_n = n;
				if (opp2LineDist < k_m * Param::Vehicle::V2::PLAYER_SIZE) {
					shootBlocked = true;
					break;
				}
			}
			n++;
		}
		if (shootBlocked) return false;
		else return true;
	}

	else {
		// NEEDMODIFY
		int n = 0;
		int best_n = 0;
		const BallVisionT& ball = pVision->Ball();
		bool shootBlocked = false;
		double kickDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(vecNumber).Pos());
		double VShoot = 650, MinAllowDist = Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE;
		double Me2Projection = 0, opp2Projection = 1e9;
		if (fabs(kickDir - 1000.0) < 10) return false;

		CGeoLine ball2ourGoal = CGeoLine(ball.Pos(), kickDir);
		CGeoPoint projectionPoint;
		double k_m = WantToLessShoot;   //3.5
		double opp2LineDist = 1000;
		while (n <= Param::Field::MAX_PLAYER) {
			if (!pVision->TheirPlayer(n).Valid()) { n++; continue; }
			const PlayerVisionT& opp = pVision->TheirPlayer(n);
			projectionPoint = ball2ourGoal.projection(pVision->TheirPlayer(n).Pos());
			Me2Projection = projectionPoint.dist(ball.Pos());
			opp2Projection = projectionPoint.dist(opp.Pos());
			double VMove = max(50.0, opp.Vel().mod());
			if (projectionPoint.x() >= ball.X()) {
				if (Me2Projection / VShoot < (opp2Projection - MinAllowDist) / VMove) {
					return false;
				}
			}
			n++;
		}
		return true;
	}
}

int CAdvance::CanSupportKick(const CVisionModule* pVision, int vecNumber) {
	/*
	bool IsTestPass = 0;
	if (IsTestPass) {
		for (int i = 0; i < 6; ++i) {
			const PlayerVisionT& friends = pVision->OurPlayer(i);
			if (pVision->OurPlayer(i).Valid() && i != vecNumber) {
				PassDirOrPos ReturnValue;
				ReturnValue.dir = (friends.Pos() - pVision->OurPlayer(vecNumber).Pos()).dir();
				ReturnValue.pos = friends.Pos();
				//LastPassPoint = NowShootNumber;//保存当前状态
				return ReturnValue;
			}
		}
	}
	*/

	//返回值
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	//当前持球车号
	bool isOurNearPointAndFarOfMe[15] = { 0 }, NearThanMe[15] = { 0 }, OneOfUsCanShoot = 0, isCanUse[15] = {0};
	int TheNumberOfCanShootPoint = 0, TheidxOfCanShootPoint[9] = { 0 };
	double ShootDir[15] = { 0 }, ChangeDir[15] = { 0 }, FinalDir = 0, theMinOppDistToThePoint[15] = {0};
	
	double theMinOppDist_threshold = 50, supportMustNearerDist = 100;
	/**********************************************************************************************************************/
	//判定支撑点是否可用

	for (int i = 0; i < NumberOfSupport; ++i) {
		isOurNearPointAndFarOfMe[i] = IsOurNearHere(pVision, i, vecNumber);
		ChangeDir[i] = fabs(Utils::Normalize(me.Dir() - (SupportPoint[i] - me.Pos()).dir()));								//传球到点“我”需要改变的角度
		theMinOppDistToThePoint[i] =  pVision->TheirPlayer(getTheirMostClosetoPosPlayerNum(pVision, SupportPoint[i])).Pos().dist(SupportPoint[i]);
		NearThanMe[i] = (theirCenter.dist(SupportPoint[i]) + supportMustNearerDist < theirCenter.dist(me.Pos()));
		
		if (isOurNearPointAndFarOfMe[i] && theMinOppDistToThePoint[i] > theMinOppDist_threshold) {
			
			if (MeIsInWhichArea == CanNOTBreakArea || MeIsInWhichArea == CornerArea || MeIsInWhichArea == KICKArea) {
				isCanUse[i] = 1;
			}
			else {
				isCanUse[i] = NearThanMe[i];
			}
		}
		if (isCanUse[i])
		{
			OneOfUsCanShoot = 1;
		}
	}
	if (!OneOfUsCanShoot)
	{
		TheBestSupportNumber = 1;
		return 0;
	}
	else {
		int idx = -1, minDir = 1e9;
		for (int i = 0; i < NumberOfSupport; ++i) {
			if (isCanUse[i]) {
				if (ChangeDir[i] < minDir)idx = i, minDir = ChangeDir[i];
			}
		}
		TheBestSupportNumber = idx;
	}
	return 1;
}
int CAdvance::toChipOrToFlat(const CVisionModule* pVision, int vecNumber, CGeoPoint TargetPoint) {
	// 0chip 1flat
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	if (isTheLineBlocked(pVision, me.Pos(), TargetPoint) && me.Pos().dist(TargetPoint) <= ParamManager::Instance()->maxChipDist)return 0;

	return 1;
}

/**********************************************************
	* Description: 防守类函数，仅限于GET中使用
	* Author: 谭宇宏
	* Created Date: 2022/10/10
***********************************************************/
bool CAdvance::isOppFaceOurDoor(const CVisionModule* pVision, double angle) {
	//判断是否球距离opp很近，opp距离我们球门很近
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	double opp2BallDist = (opp.Pos() - ball.Pos()).mod();
	bool isBallNearOpp = opp2BallDist < OPP_HAS_BALL_DIST;
	double judgeAngle = abs(Utils::Normalize((opp.Dir() - CVector(CGeoPoint(-Param::Field::PITCH_LENGTH / 2.0, 0) - opp.Pos()).dir())));
	bool isFaceOurDoor = judgeAngle < angle || judgeAngle == angle;
	return isFaceOurDoor && isBallNearOpp;
}
bool CAdvance::checkTheyCanShoot(const CVisionModule* pVision, int vecNumber) {
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	CVector opp2ball = ball.Pos() - opp.Pos();
	CVector me2ball = ball.Pos() - me.Pos();
	double opp2ballDist = opp2ball.mod();
	double me2ballDist = me2ball.mod();
	if (isOppFaceOurDoor(pVision, Param::Math::PI / 6.0) && checkBallFront(pVision, Param::Math::PI / 6.0) && ((me2ballDist - opp2ballDist) > -5) && (opp.Pos() - ourGoal).mod() < Param::Field::GOAL_WIDTH / 2) {
		return true;
	}
	else { return false; }
}

/**********************************************************
	* Description: 生成类函数，具有具体实义
	* Author: 谭宇宏
	* Created Date: 2022/10/10
***********************************************************/
double CAdvance::TheMinDistBetweenTheOppAndTheLine(const CVisionModule* pVision, CGeoPoint startPoint, CGeoPoint targetPoint) {
	/*该条路径上是否会被敌人阻挡*/
	int n = 0;
	const BallVisionT& ball = pVision->Ball();
	double passDir = (targetPoint - startPoint).dir();
	CGeoLine start2Target = CGeoLine(startPoint, passDir);
	CGeoPoint projectionPoint;
	double opp2LineDist = 1000;
	while (n <= Param::Field::MAX_PLAYER) {
		if (!pVision->TheirPlayer(n).Valid()) { n++; continue; }
		projectionPoint = start2Target.projection(pVision->TheirPlayer(n).Pos());
		double r = (projectionPoint - startPoint).x() * (projectionPoint - targetPoint).x() + (projectionPoint - startPoint).y() * (projectionPoint - targetPoint).y();
		if (opp2LineDist > (projectionPoint - pVision->TheirPlayer(n).Pos()).mod() && r < 0) { // projectionPoint.x() < Param::Field::PITCH_LENGTH / 2.0 && projectionPoint.x() > startPoint.x()) {
			opp2LineDist = (projectionPoint - pVision->TheirPlayer(n).Pos()).mod();
		}
		n++;
	}
	return opp2LineDist;
}
CGeoPoint CAdvance::GenerateBreakShootPoint(const CVisionModule* pVision, int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	CGeoPoint ShootPoint = KickDirection::Instance()->GetTheShootPoint(pVision, me.Pos());
	ShootPoint.setY(ShootPoint.y() - me.VelY() * 1.5);
	if (me.Y() < -120)ShootPoint.setY(ShootPoint.y() + me.VelX() * 1 - me.Y() * 0.25);
	else if (me.Y() > 120)ShootPoint.setY(ShootPoint.y() - me.VelX() * 1 - me.Y() * 0.25);
	//double MeVel = me.VelY()
	if (ShootPoint.y() < -60)ShootPoint.setY(-60);
	if (ShootPoint.y() > 60)ShootPoint.setY(60);

	return ShootPoint;
}
double CAdvance::GenerateShootDir(const CVisionModule* pVision, int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	CGeoPoint TargetUp = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2 + 5);
	CGeoPoint TargetDown = CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2 - 5);
	double FinalTarget = KickDirection::Instance()->getPointShootDir(pVision, me.Pos());
	double thetaUp = (TargetUp - ball.Pos()).dir();
	double thetaDown = (TargetDown - ball.Pos()).dir();
	if (me.Dir() < thetaUp) FinalTarget = (TargetDown - me.Pos()).dir();
	else if (me.Dir() > thetaDown)FinalTarget = (TargetUp - me.Pos()).dir();
	return FinalTarget;
}

CGeoPoint CAdvance::GenerateBreakPassPoint(const CVisionModule* pVision, int vecNumber) {

	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	PassPoint = SupportPoint[TheBestSupportNumber];
	KickorPassDir = (PassPoint - me.Pos()).dir();
	PassPoint.setY(PassPoint.y() - me.VelY() * 0.75);
	if (me.Y() < -90)PassPoint.setY(PassPoint.y() + me.VelX() * 0.4);
	else if (me.Y() > 90)PassPoint.setY(PassPoint.y() - me.VelX() * 0.4);
	return PassPoint;
}

double CAdvance::GetFPassPower(CGeoPoint StartPoint, CGeoPoint targetPoint) {
	double dist = (StartPoint - targetPoint).mod() - Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER;
	double passPower = sqrt(powf(ParamManager::Instance()->FASTEST_RECEIVE_VEL, 2) + 2 * ParamManager::Instance()->BALL_DEC * dist) * ADV_FPASSPOWER_Alpha;
	return min(passPower, (double)Param::Rule::MAX_BALL_SPEED - 10);
	// return max(min(650.0, ADV_FPASSPOWER_Alpha* dist ), 200.0);
}
double CAdvance::GetCPassPower(CGeoPoint StartPoint, CGeoPoint targetPoint) {
	double dist = ((StartPoint - targetPoint).mod() - 9.0 * Param::Vehicle::V2::PLAYER_SIZE) * ADV_CPASSPOWER_Alpha;
	return min(ParamManager::Instance()->maxChipDist, dist);
	// return min(460.0, ADV_CPASSPOWER_Alpha * dist);
}

CGeoPoint CAdvance::generateNormalPushPoint(const CVisionModule* pVision, const int vecNumber) {

	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	const double VectorDist = 200;
	CGeoPoint FinalTarget = CGeoPoint(-999, -999);
	/*
	double faceDir = 0.0;

	const double DirEpsilon = Param::Math::PI / 180 * 5;
	
	const double ThresholdForOpp = 60;

	return me.Pos() + Utils::Polar2Vector(VectorDist, (theirCenter - me.Pos()).dir());

	double Dist = -1e9;
	for (int step = -5; step <= 5; ++step) {
		const CGeoPoint target = me.Pos() + Utils::Polar2Vector(VectorDist, Param::Math::PI / 180 * 5 * step);
		const double SingleDist = TheMinDistBetweenTheOppAndTheLine(pVision, me.Pos(), target);
		if (SingleDist > Dist) FinalTarget = target, Dist = SingleDist;
		//GDebugEngine::Instance()->gui_debug_x(target, COLOR_BLUE);
	}
	if (Dist > ThresholdForOpp) {
		Dist = 1e9;
		for (int step = -5; step <= 5; ++step) {
			const CGeoPoint target = me.Pos() + Utils::Polar2Vector(VectorDist, Param::Math::PI / 180 * 5 * step);
			if (TheMinDistBetweenTheOppAndTheLine(pVision, me.Pos(), target) < 60)continue;
			const double SingleDist = (target - theirCenter).mod();
			if (SingleDist < Dist) FinalTarget = target, Dist = SingleDist;
			//GDebugEngine::Instance()->gui_debug_x(target, COLOR_BLUE);
		}
	}
	//GDebugEngine::Instance()->gui_debug_x(FinalTarget, COLOR_BLUE);
	*/
	FinalTarget = me.Pos() + Utils::Polar2Vector(VectorDist, (theirCenter - me.Pos()).dir());
	return FinalTarget;
}
double CAdvance::generateGetballDir(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	const CVector me2ball = me.Pos() - ball.Pos();
	double faceDir = 0.0;
	if (ball.Vel().mod() > 20) {
		faceDir = Utils::Normalize(Param::Math::PI + ball.Vel().dir());
	}
	else {
		faceDir = (ball.Pos() - me.Pos()).dir();
	}
	return faceDir;
}
int CAdvance::GenerateStateOfFoulTrouble(const CVisionModule* pVision, const int vecNumber) {
	if (tendToShoot(pVision, vecNumber)) return KICK;
	else return KICK;
}

bool CAdvance::Me2OppTooclose(const CVisionModule* pVision, const int vecNumber) { //是否太近了
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	CVector me2Ball = ball.Pos() - me.Pos();
	CVector me2Opp = opp.Pos() - me.Pos();

	char me2opp[100];
	sprintf(me2opp, "%f", me2Opp.mod());
	//changed by lsf

	if (me2Opp.mod() <= 40 && opp.X() > me.X() && fabs(Utils::Normalize(me2Ball.dir() - me2Opp.dir())) < Param::Math::PI / 3) {
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(450, 450), "TOO CLOSE with ball", COLOR_ORANGE);
		return true;
	}
	/*
	if (me2Ball.mod() * 1.5 > me2Opp.mod() && fabs(Utils::Normalize(me2Ball.dir() - me2Opp.dir())) < Param::Math::PI / 3) {
		if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(450, 450), "TOO CLOSE with ball", COLOR_ORANGE);
		return true;
	}*/
	return false;
}
bool CAdvance::OppIsFarThanMe(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const PlayerVisionT& opp2 = pVision->TheirPlayer(Oppfront);
	const BallVisionT& ball = pVision->Ball();
	CVector me2Ball = ball.Pos() - me.Pos();
	CVector Ball2Opp = opp2.Pos() - ball.Pos();

	const double threshold = 110;
	if (!(pVision->TheirPlayer(Oppfront).Valid())) {
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(450, 475), "Far Than Opp with ball", COLOR_ORANGE);
		return true;
	}
	if ((me2Ball.mod() < Ball2Opp.mod() && Ball2Opp.mod() > threshold)) {
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(450, 475), "Far Than Opp with ball", COLOR_ORANGE);
		return true;
	}
	if (fabs(Utils::Normalize((me2Ball.dir() - Ball2Opp.dir()))) < Param::Math::PI / 3 || Ball2Opp.mod() < threshold * 0.6)
		return false;
	GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(450, 475), "Far Than Opp with ball", COLOR_ORANGE);
	return true;
}

double CAdvance::generateOppIsNearThanMeDir(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	//return Utils::Normalize((opp.Pos() - ball.Pos()).dir() + 20 * Param::Math::PI / 180);
	return Utils::Normalize((opp.Pos() - ball.Pos()).dir());// +20 * Param::Math::PI / 180);
}
double CAdvance::generateOppIsFarThanMeDir(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	//return Utils::Normalize((opp.Pos() - ball.Pos()).dir() + 20 * Param::Math::PI / 180);
	return Utils::Normalize((ball.Pos() - opp.Pos()).dir());// +20 * Param::Math::PI / 180);
}

bool CAdvance::canScore(const CVisionModule* pVision, const int vecNumber, const double radius, const double dir) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);

	bool flag = true;
	double x1 = me.X(), y1 = me.Y(), theta = dir;
	if (!(fabs(me.Dir()) < Param::Math::PI / 2))return false;
	if (Param::Field::MAX_PLAYER == 0)
	{
		double projection = y1 + tan(theta) * (Param::Field::PITCH_LENGTH / 2 - x1);
		if (fabs(projection) + 2 > (Param::Field::GOAL_WIDTH) / 2 - 13) {
			flag = false;
		}

	}

	double projection = y1 + tan(theta) * (Param::Field::PITCH_LENGTH / 2 - x1);
	if (fabs(projection) + 5 > (Param::Field::GOAL_WIDTH) / 2 - 15) {
		flag = false;
		return false;
	}

	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (!pVision->TheirPlayer(i).Valid()) continue;
		auto enemy = pVision->TheirPlayer(i);
		double x = enemy.X(), y = enemy.Y();
		if (x < me.X())continue;
		double r = fabs(y - y1 - tan(theta) * x + tan(theta) * x1) / sqrt(1 + tan(theta) * tan(theta));
		if (enemy.Pos().dist(me.Pos()) < 50.0) {
			if (r < Param::Vehicle::V2::PLAYER_SIZE * 1.15) {
				flag = false;
				break;
			}
		}
		else {
			if (r < radius) {
				flag = false;
				break;
			}
		}
	}
	/*
	char projection[100];
	sprintf(projection, "%f", projection);
	GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(160, 230), projection, COLOR_YELLOW);
	*/
	CGeoLine ShootLine = CGeoLine(me.Pos(), me.Dir());
	CGeoLine GoalLine = CGeoLine(theirLeft, theirRight);
	CGeoSegment Goal = CGeoSegment(theirLeft, theirRight);
	CGeoLineLineIntersection LineIntersection = CGeoLineLineIntersection(GoalLine, ShootLine);
	if (LineIntersection.Intersectant() == 0)return false;
	CGeoPoint Intersection = LineIntersection.IntersectPoint();
	if (Goal.IsPointOnLineOnSegment(Intersection) == 0) flag = false;
	if (Intersection.x() < me.X())return false;
	/*
	GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -450), ("CanScore:" + to_string(flag)).c_str(), COLOR_YELLOW);
	*/
	return flag;

}

bool CAdvance::WeNeedBlockTheBall(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->OurPlayer(opponentID);
	if (fabs(Utils::Normalize((opp.Dir() - (opp.Pos() - ourGoal).dir()))) < 30 * Param::Math::PI / 180) {
		return true;
	}
	else return false;
}


int CAdvance::opp_ahead(const CVisionModule* pVision, const int vecNumber) {
	int cnt = 0;
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	double x1 = me.X(), y1 = me.Y();
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (!pVision->TheirPlayer(i).Valid()) continue;
		auto enemy = pVision->TheirPlayer(i);
		double x = enemy.X(), y = enemy.Y();
		if (x > x1 && fabs(y) < Param::Field::PITCH_WIDTH * 4 / 5)
			cnt++;
	}
	return cnt;
}

bool CAdvance::WeCanAlwaysSetKick(const CVisionModule* pVision, const int vecNumber) {
	
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);

	if (_state == BREAKSHOOT) {
		if (me.Vel().mod() > 20)return false;
	}


	if (MeIsInWhichArea == CenterArea)
		if (canScore(pVision, vecNumber, OBSTACLE_RADIUS * 2.5, me.Dir()))
			return true;
		else return false;
	if(MeIsInWhichArea == KICKArea)
		if (canScore(pVision, vecNumber, OBSTACLE_RADIUS, me.Dir()))
			return true;
		else return false;
	return false;
}


int CAdvance::GenerateNextState(const CVisionModule* pVision, const int vecNumber) {
	// 需要完全拿住球
	/*DefenceArea = 0,
	SideArea,
	CenterArea
	CornerArea,
	KICKArea,
	CanNOTBreakArea,*/
	/*如果我和球门之间的距离小于KICK_DIST，考虑顺序为 shoot->break->pass */
	if ((NowIsShoot == 1)) {
		return KICK;
	}
	else if ((NowIsShoot == 2) && MeIsInWhichArea != CanNOTBreakArea && MeIsInWhichArea != CornerArea) {
		return BREAKSHOOT;
	} // 持久化

	else if (Me2OppTooclose(pVision, vecNumber)) {
		if (MeIsInWhichArea == KICKArea) {
			if (tendToShoot(pVision, vecNumber))
				return KICK;
			else return BREAKSHOOT;
		}
		else if (MeIsInWhichArea == CenterArea) {
			if (NumOfTheirPlayerfrontMe <= 2)
				return BREAKSHOOT;
			return BREAKING;
		}
		return BREAKING;
	}
	else if (MeIsInWhichArea == ReliefArea) {
		//return JUSTCHIPPASS;
		return JUSTCHIPPASS;
		//return PUSHOUT;
		//return PASS;
	}
	
	else if (MeIsInWhichArea == DefenceArea) { // 在后场防守区域
		if (IHaveSupport)
			return PASS;
		if (OppIsFarThanMe(pVision, vecNumber))
			return PUSHOUT;
		return JUSTCHIPPASS;
	}
	else if (MeIsInWhichArea == SideArea) { // 在双边区域
		if (IHaveSupport)
			return PASS;
		else if (OppIsFarThanMe(pVision, vecNumber))
			return PUSHOUT;
		else {
			return BREAKING;
		}	
	}
	else if (MeIsInWhichArea == CenterArea) { // 在前中场
		if (tendToShoot(pVision, vecNumber)) {
			return KICK;
		}  // 首先判断射门
		else if (!IHaveSupport) {  // 不存在支援车
			return PUSHOUT;
		}
		else {	// 存在支援车
			return PASS;
		}
	}	
	else if (MeIsInWhichArea == CornerArea) { //在角球区
		if (tendToShoot(pVision, vecNumber)) {
			return KICK;
		}
		else if (IHaveSupport) { //pass first
			return PASS;
		}
		else {	
			return KICK;
		}	
	}	
	else if (MeIsInWhichArea == CanNOTBreakArea) {  // 不能break
		if (tendToShoot(pVision, vecNumber)) {
			return KICK;
		}
		if (IHaveSupport) { //pass first
			return PASS;
		}
		else {
			return KICK;
		}  
	}	
	else { // Kick区域
		if (tendToShoot(pVision, vecNumber)) {
			return KICK;
		}  // 首先判断射门
		else if (MeIsInWhichArea != CanNOTBreakArea) {  // 不存在支援车 //
			return BREAKSHOOT;
		}
		else if (IHaveSupport) {
			return PASS;
		}
		else BREAKING;
	}
	return KICK;
}

int CAdvance::CanWeUseChaseBecauseOfGetBallV3(const CVisionModule* pVision, const int vecNumber) {
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const CVector opp2ball = ball.Pos() - opp.Pos();
	double deltaTheta1 = fabs(Utils::Normalize(ball.Vel().dir() - (ball.Pos() - me.Pos()).dir()));
	// 球速方向与我面向球的方向夹角小于20度
	double deltaTheta2 = fabs(Utils::Normalize(KickorPassDir - (ball.Pos() - me.Pos()).dir()));
	// 当前射门方向与我面向球的方向夹角小于20度
	bool VelModFlag = ball.Vel().mod() < 80;
	// 球速小于80
	bool VelDirFlag = (ball.Vel().mod() < 20) || (deltaTheta1 < 20.0 / 180 * Param::Math::PI);// || deltaTheta1 > 160.0 / 180 * Param::Math::PI);
	// 球速小于10 或者 球速方向与我面向球的方向夹角小于20度
	bool OppFlag = opp2ball.mod() > 40 || opp2ball.mod() > (me.Pos() - ball.Pos()).mod() * 1.5;
	// 敌人距离球大于40 或者敌人距离球比我距离球的1.5倍更大
	bool FinalDirFlag = (deltaTheta2 < 20.0 / 180 * Param::Math::PI);// || deltaTheta2 > 160.0 / 180 * Param::Math::PI);
	// 当前射门方向与我面向球的方向夹角小于20度

	if ((theirCenter - me.Pos()).mod() < KICK_DIST * 0.65 && VelModFlag && VelDirFlag) return true;
	// 球门线前，不用考虑opp
	return VelModFlag && VelDirFlag && OppFlag && FinalDirFlag;
}

bool CAdvance::isBallVeryNearTheOppAndIMustGET(const CVisionModule* pVision) {
	int _executor = task().executor;
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& opponent = pVision->TheirPlayer(opponentID);
	CVector opponent2ball = ball.Pos() - opponent.Pos();
	double judgeDist = OPP_HAS_BALL_DIST + 3.0;
	if (opponent2ball.mod() < judgeDist)
		return true; // take opponent's direction into consideration.If direction not towards the ball,ignore it
	else
		return false;
}

double CAdvance::generateBreakingDir(const CVisionModule* pVision, const int vecNumber) {
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);

	int Nextstate = 0;
	if ((NowIsShoot == 1) || ((NowIsShoot == 2) && MeIsInWhichArea != CanNOTBreakArea)) {
		Nextstate = KICK;
	} // 持久化
	else if (MeIsInWhichArea == ReliefArea) {
		Nextstate = PASS;
	}
	else if (MeIsInWhichArea == DefenceArea) { // 在后场防守区域
		if (OppIsFarThanMe(pVision, vecNumber))
			Nextstate = KICK;
		else Nextstate = PASS;
	}
	else if (MeIsInWhichArea == SideArea) { // 在双边区域
		if (IHaveSupport)
			Nextstate = PASS;
		else Nextstate = KICK;
	}
	else if (MeIsInWhichArea == CenterArea || MeIsInWhichArea == CornerArea || MeIsInWhichArea == CanNOTBreakArea) { // 在前中场
		if (tendToShoot(pVision, vecNumber) || (!IHaveSupport))
			Nextstate = KICK;
		else Nextstate = PASS;
	}
	else { // Kick区域
		if (tendToShoot(pVision, vecNumber)) {
			Nextstate =  KICK;
		}  // 首先判断射门
		else if (MeIsInWhichArea != CanNOTBreakArea) {  // 不存在支援车 //
			Nextstate = KICK;
		}
		else if (IHaveSupport) {
			Nextstate =  PASS;
		}
	}

	if (Nextstate == PASS) {
		return 	(SupportPoint[TheBestSupportNumber] - me.Pos()).dir();
	}
	else {
		return (theirCenter - me.Pos()).dir();
	}
}

void CAdvance::UpdateTheDribblePointForbreak(const CVisionModule* pVision, const int vecNumber) {
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	
	if (DribbleForBreak.TheMaxDistBetweenMeAndTheBallFortheLose > 1e4) {
		DribbleForBreak.TheMaxDistBetweenMeAndTheBallFortheLose = me.Pos().dist(ball.Pos());
	}// 如果是未初始的Dist，需要直接初始化
	else {// lose阶段，一直取最大的离球距离
		DribbleForBreak.TheMaxDistBetweenMeAndTheBallFortheLose = max(me.Pos().dist(ball.Pos()), DribbleForBreak.TheMaxDistBetweenMeAndTheBallFortheLose);
	}

	if (DribbleForBreak.state == LoseBallForDribble) {// 上一时刻是lose
		if (BallStatus::Instance()->getBallPossession(true, vecNumber) > 0.3) { // 这一时刻拿到了球
			DribbleForBreak.state = HaveBallForDribble;
			if (DribbleForBreak.TheMaxDistBetweenMeAndTheBallFortheLose > 18.0) { // 只有球离开我的距离超过了18，我才会更新我的DribblePoint
				DribbleForBreak.DribblePoint = me.Pos();
				DribbleForBreak.TheMaxDistBetweenMeAndTheBallFortheLose = me.Pos().dist(ball.Pos());
			}
		}
		else { // 这一时刻仍然是lose
			//不做操作
		}
	}
	else {// 上一时刻拿到了球
		if (BallStatus::Instance()->getBallPossession(true, vecNumber) > 0.3) { // 这一时刻同样拿到了球
			//不做操作
		}
		else { // 这一时刻球丢失了
			DribbleForBreak.state = LoseBallForDribble;// 更新状态
			DribbleForBreak.TheMaxDistBetweenMeAndTheBallFortheLose = me.Pos().dist(ball.Pos()); // 重新计数，但是不更新DribblePoint，因为可能重新拿回来
		}
	}
}

CPlayerCommand* CAdvance::execute(const CVisionModule* pVision)
{
	if (subTask()) {
		return subTask()->execute(pVision);
	}
	if (_directCommand) {
		return _directCommand;
	}
	return 0;
}

