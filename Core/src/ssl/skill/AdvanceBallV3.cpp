﻿#include "AdvanceBallV3.h"
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

namespace {
	int KICKPOWER = 550;
	int CHIPPOWER = 240;
	int ADV_FPASSPOWER = 480;//ADV_FPASSPOWER
	int ADV_CPASSPOWER = 230;//ADV_CPASSPOWER
	int RELIEF_POWER = 400;
	int RELIEF_POWER_V3 = 400;
	int BACK_POWER = 300;
	int BACK_POWER_V3 = 300;
	int TEND_TO_SHOOT_FLAG = 25;
	double SHOOT_PRECISION = 15;
	double SHOOT_BLOCKED_RANGE = 3;
	double PASS_BLOCKED_RANGE = 7;
	bool DEBUG_ENGINE = false;     //  output information of debug or not
	bool WEAK_OPP = false;     //
	bool USE_DRIBBLE_TURN = false;     //be true when encounter weak teams 

	CGeoPoint theirLeft = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2);
	CGeoPoint theirRight = CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2);
	CGeoPoint theirCenter = CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0);
	CGeoPoint ourGoal = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
	CGeoPoint relief_l_pos = CGeoPoint(200, -180);//left relief target
	CGeoPoint relief_r_pos = CGeoPoint(200, 180);//right relief target
	const int maxFrared = 100 * 1.25;  // make  number of infrared frames the maximum
	const int maxMeHasBall = int(50 * 1.25);
	double OPP_HAS_BALL_DIST = 30;
	double CIRCLE_FRONT = true;
	CGeoPoint pullBallTarget = CGeoPoint(0, 0);
	CGeoPoint dragBallTarget = CGeoPoint(0, 0);
	int meHasBallMaxCnt = 1;
	int maxNormalPushCnt = 100;
	double CHIP_ANGLE = 15;
	int RELIEF_BIAS = 180;// the bias of relief target
	double FLAT_DIST = 300;
	double PULL_DIST = 450;
	double RELIEF_DIST = 280;
}

CAdvanceBallV3::CAdvanceBallV3() {
    OPP_HAS_BALL_DIST = ParamManager::Instance()->OPP_HAS_BALL_DIST;
    WEAK_OPP = ParamManager::Instance()->WEAK_OPP;
    USE_DRIBBLE_TURN = ParamManager::Instance()->USE_DRIBBLE_TURN;
    CIRCLE_FRONT = ParamManager::Instance()->CIRCLE_FRONT;
    KICKPOWER = ParamManager::Instance()->KICKPOWER;
    CHIPPOWER = ParamManager::Instance()->CHIPPOWER;
    DEBUG_ENGINE = ParamManager::Instance()->Advance_DEBUG_ENGINE;
    //SHOOT_PRECISION = ParamManager::Instance()->SHOOT_PRECISION;
    CHIP_ANGLE = ParamManager::Instance()->CHIP_ANGLE;
    FLAT_DIST = ParamManager::Instance()->FLAT_DIST;
    PULL_DIST = ParamManager::Instance()->PULL_DIST;
    RELIEF_DIST = ParamManager::Instance()->RELIEF_DIST;
    RELIEF_POWER = ParamManager::Instance()->RELIEF_POWER;
    RELIEF_BIAS = ParamManager::Instance()->RELIEF_BIAS;
    BACK_POWER = ParamManager::Instance()->BACK_POWER;
    BACK_POWER_V3 = ParamManager::Instance()->BACK_POWER_V3;
    ADV_FPASSPOWER = ParamManager::Instance()->ADV_FPASSPOWER;
    ADV_CPASSPOWER = ParamManager::Instance()->ADV_CPASSPOWER;
    TEND_TO_SHOOT_FLAG = ParamManager::Instance()->TEND_TO_SHOOT_FLAG;
    SHOOT_BLOCKED_RANGE = ParamManager::Instance()->SHOOT_BLOCKED_RANGE;
    PASS_BLOCKED_RANGE = ParamManager::Instance()->PASS_BLOCKED_RANGE;
	pullCnt = 0;
	turnCnt = 0;
	pullBackFlag = false;
	normalPushCnt = 0;
	dribbleTurnFinalDir = Param::Math::PI / 2;
}

CAdvanceBallV3::~CAdvanceBallV3() {
}

void CAdvanceBallV3::plan(const CVisionModule* pVision) {
	//Cycle loop
	cout << "advance____________________" << endl;
	pullBackFlag = USE_DRIBBLE_TURN;
	if (pVision->Cycle() - _cycle > Param::Vision::FRAME_RATE * 0.1) {
		_state = BEGINNING;
	}
	//information of task
	int _executor = task().executor;
	int goalieNumber = 0;
	//cout << "_executor: " << _executor << endl;
	int flag = task().player.flag | PlayerStatus::DODGE_OUR_DEFENSE_BOX;
	int flag_not_dribble = flag & (~PlayerStatus::DRIBBLING);
	int flag_dribble = (~PlayerStatus::DRIBBLING);
	//目前在前场的球员
	int NumofPlayerInFrontfiled = 0;
	//information of images
	const PlayerVisionT& me = pVision->OurPlayer(_executor);
	const BallVisionT& ball = pVision->Ball();
	double BallToOurGoal = (ball.Pos() - ourGoal).mod();
	double kickDir = (CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, 0) - pVision->Ball().Pos()).dir();
	double passDir = 0;
	double vel_flat = 5;//velosity of flatpass (m/s)
	int tandemNum = task().ball.receiver;
	relief_l_pos = CGeoPoint(200, -RELIEF_BIAS);
	relief_r_pos = CGeoPoint(200, RELIEF_BIAS);
	//cout << "tandem: " << tandemNum << endl;
	if (tandemNum != 0 && pVision->OurPlayer(tandemNum).Valid()) {
		const PlayerVisionT& ourTandem = pVision->OurPlayer(tandemNum);
		if (me.Pos().y() < ourTandem.Pos().y()) {
			dribbleTurnFinalDir = Param::Math::PI / 2;
		}
		else {
			dribbleTurnFinalDir = -Param::Math::PI / 2;
		}
	}

	//information of angle
	const CVector self2Ball = ball.Pos() - me.Pos();
	//cout << self2Ball.mod() << endl;
	CVector ball2TheirCenter = theirCenter - ball.Pos();
	//information of infrared 
	bool frared = RobotSensor::Instance()->IsInfraredOn(_executor);

	//check how many consecutive frames have detected information of infrared
	if (frared) { infraredOn = infraredOn >= maxFrared ? maxFrared : infraredOn + 1; }
	else { infraredOn = 0; }

	bool is_runner_dir_ok = WorldModel::Instance()->KickDirArrived(pVision->Cycle(), kickDir, Param::Math::PI / SHOOT_PRECISION, _executor);
	//bool is_runner_dir_ok_penaltyArea = WorldModel::Instance()->KickDirArrived(pVision->Cycle(), kickDir, Param::Math::PI / 9, _executor);
	bool pass_dir_ok = false;
	_pushBallTarget = theirCenter;

	//Treatment of the enemy
	bool isOppHasBall = checkOppHasBall(pVision);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);                               // The vision of the opponent's most threatening robot
	const CVector opp2ball = ball.Pos() - opp.Pos();
	double ball2oppDist = opp2ball.mod();						                               // The distance between opponent's most threatening robot and the ball
	double ball2meDist = (ball.Pos() - me.Pos()).mod();
	double Me2Receiver = (me.Pos() - pVision->OurPlayer(tandemNum).Pos()).mod();
	CVector me2goal = theirCenter - me.Pos();					                               // The distance between our robot for grabbing ball and the center of Opponent goal 
	double me2BestOppDist = CVector(pVision->TheirPlayer(opponentID).Pos() - me.Pos()).mod();  // The distance between our robot for grabbing ball and opponent's most threatening robot

																							   //to judge whether we have ball
	bool isMeHasBall;
	bool isMechHasBall = infraredOn >= 1;                         // Infrared sensors have detected the ball
	bool visionHasBall = isVisionHasBall(pVision, _executor);     // Vision have detected the ball

	isMeHasBall = isMechHasBall || visionHasBall;
	if (isMeHasBall) {
		meHasBall = meHasBall >= maxMeHasBall ? maxMeHasBall : meHasBall + 1;
		meLoseBall = 0;
	}
	else {
		meHasBall = 0;
		meLoseBall = meLoseBall >= maxMeHasBall ? maxMeHasBall : meLoseBall + 1;
	}

	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (pVision->OurPlayer(i).Valid() && i != goalieNumber) {
			if (pVision->OurPlayer(i).Pos().x() > Param::Field::PITCH_LENGTH / 10) {
				NumofPlayerInFrontfiled += 1;
			}
		}
		else {
			continue;
		}
	}

	switch (_state) {
	case BEGINNING:
		_state = GOTO;
		//if (DEBUG_ENGINE) { cout << "BEGINNING-->GOTO" << endl; }
		break;
	case GOTO:
		if (pVision->GetCurrentRefereeMsg() == "ourPenaltyKick") {
			_state = PENALTY;
			break;
		}
		if (BallToOurGoal < RELIEF_DIST && ball2oppDist>30) {
			_state = RELIEF;
			break;
		}
		if (meHasBall > meHasBallMaxCnt) {
			if (pullBackFlag == true && oppBlockMe(pVision, _executor) && me2goal.mod() < 1.4 * PULL_DIST) {
				pullCnt++;
				if (pullCnt > 3) {
					pullCnt = 0;
					pullBackFlag = false;
					pullBallTarget = me.Pos() + Utils::Polar2Vector(70, Utils::Normalize(me.Dir() + Param::Math::PI));
					_state = DRIBBLE_PULL;
					if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -375), "turn to Dribblepull", COLOR_YELLOW);
					//if (DEBUG_ENGINE) { cout << "goto-->dribblePull" << endl; }
				}
			}
			else {
				if (oppBlockMe(pVision, _executor) && ball2oppDist > 25 && ball2oppDist < 60) {
					if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, 400), "GOTOtoNORMALPUSH", COLOR_YELLOW);
					_state = NORMAL_PUSH;
				}
				else if (tendToShoot(pVision, _executor, TEND_TO_SHOOT_FLAG)) {
					//if (DEBUG_ENGINE) { cout << "goto-->kick" << endl; }
					//cout << "here here here" << endl;
					if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 400), (tendToShoot(pVision, _executor, TEND_TO_SHOOT_FLAG) ? "1" : "0"), COLOR_ORANGE);
					_state = KICK;
				}
				else if ((ball2oppDist >= 35 && me2goal.mod() < 1.2 * PULL_DIST && !tendToShoot(pVision, _executor, TEND_TO_SHOOT_FLAG) && (NumofPlayerInFrontfiled > 1 || me.X() < pVision->OurPlayer(tandemNum).X())) && toChipOrToFlat(pVision, _executor, tandemNum) == 2) {
					//if (DEBUG_ENGINE) { cout << "goto-->flatpass" << endl; }
					//dragBallTarget= me.Pos() + Utils::Polar2Vector(30, Utils::Normalize(me.Dir() + Param::Math::PI));
					_state = FLATPASS;
				}
				else if ((ball2oppDist >= 35 && me2goal.mod() < 1.2 * PULL_DIST && !tendToShoot(pVision, _executor, TEND_TO_SHOOT_FLAG) && (NumofPlayerInFrontfiled > 1 || me.X() < pVision->OurPlayer(tandemNum).X())) && toChipOrToFlat(pVision, _executor, tandemNum) == 1) {
					//if (DEBUG_ENGINE) { cout << "goto-->chippass" << endl; }
					//dragBallTarget = me.Pos() + Utils::Polar2Vector(30, Utils::Normalize(me.Dir() + Param::Math::PI));
					_state = CHIPPASS;
				}
				//else if (meHasBall > meHasBallMaxCnt && toChipOrToFlat(pVision, _executor, tandemNum) == 0) {
				//	//if (DEBUG_ENGINE) { cout << "goto-->kickenemy" << endl; }
				//	_state = KICK;//should be KICKENEMY，haven't finished
				//}
			}

		}


		if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(270, -400), "STILL_GOTO", COLOR_YELLOW);
		break;
	case PENALTY:
		if (ball.Pos().x() > 440) {
			_state = KICK;
		}
		break;
	case RELIEF:
		if (meLoseBall > 10) {
			//if (DEBUG_ENGINE) { cout << "dribble --> goto" << endl; }
			_state = GOTO;
		}
		break;
	case NORMAL_PUSH:
		normalPushCnt++;
		if (meHasBall > meHasBallMaxCnt&& isMePassedOpp(pVision, _executor) && tendToShoot(pVision, _executor, TEND_TO_SHOOT_FLAG)) {
			//if (DEBUG_ENGINE) { cout << "normal push --> kick" << endl; }
			_state = KICK;
		}
		else if (meLoseBall > 1 || isMePassedOpp(pVision, _executor)) {
			//if (DEBUG_ENGINE) { cout << "normal push --> goto" << endl; }
			_state = GOTO;
		}
		else if (USE_DRIBBLE_TURN && tandemNum != 0 && pVision->OurPlayer(tandemNum).Valid() && normalPushCnt > maxNormalPushCnt&& ball.Pos().x() > 0) {
			//if (DEBUG_ENGINE) { cout << "normal push --> dribble turn" << endl; }
			normalPushCnt = 0;
			_state = DRIBBLE_TURN;
		}
		break;
	case DRIBBLE_PULL:
		if (meLoseBall > 4 || (self2Ball.mod() > 20 || me.Pos().dist(pullBallTarget) < 10 && ball.Valid())) {
			//if (DEBUG_ENGINE) { cout << "dribble --> goto" << endl; }
			_state = GOTO;
		}
		if (me.Pos().dist(pullBallTarget) < 10 && meHasBall > meHasBallMaxCnt&& tendToShoot(pVision, _executor, TEND_TO_SHOOT_FLAG)) {
			//if (DEBUG_ENGINE) { cout << "dribble --> kick" << endl; }
			_state = KICK;
		}
		break;
	case DRIBBLE_TURN:
	{
		if (abs(Utils::Normalize(me.Dir() - dribbleTurnFinalDir)) < Param::Math::PI / 36) {
			//if (DEBUG_ENGINE) { cout << "dribble turn --> light kick" << endl; }
			_state = LIGHT_KICK;
		}
		else if (meLoseBall > 10 * 1.25) {
			//if (DEBUG_ENGINE) { cout << "dribble turn --> goto" << endl; }
			_state = GOTO;
		}
		break;
	}
	case LIGHT_KICK:
		if (meLoseBall > 30 * 1.25) {
			//if (DEBUG_ENGINE) { cout << "light kick --> goto" << endl; }
			_state = GOTO;
		}
		break;
	case KICK:
		if (meLoseBall > 2) {
			//if (DEBUG_ENGINE) { cout << "kick --> goto" << endl; }
			_state = GOTO;
		}
		break;
	case CHIPPASS:
		if (meLoseBall > 10 && ball2oppDist < 35) {
			if (DEBUG_ENGINE) { cout << "chippass --> goto" << endl; }
			_state = GOTO;
		}
		break;
	case FLATPASS:
		if (meLoseBall > 10 && ball2oppDist < 35) {
			if (DEBUG_ENGINE) { cout << "flatpass --> goto" << endl; }
			_state = GOTO;
		}
		break;
	case STOP:
		setSubTask(PlayerRole::makeItStop(_executor));
		break;
	default:
		_state = BEGINNING;
		break;
	}

	//if (isToTheirGoal && _state!= NORMAL_PUSH && _state != DRIBBLE_PULL && _state != STOP && _state != DRIBBLE_TURN && _state != LIGHT_KICK) {
	//	KickStatus::Instance()->setKick(_executor, KICKPOWER); 
	//}

	flag = flag | PlayerStatus::DRIBBLING;

	if ((ball.X() < -Param::Field::PITCH_LENGTH / 4) && (abs(ball.Y()) > Param::Field::PENALTY_AREA_R)) { // ball: x < -151.25, |y| > 85
		_pushBallTarget = ball.Pos() + Utils::Polar2Vector(100, 0);
	}
	else { calcPushTarget(pVision); }

	//cout << "_state: " << _state << " " << pVision->Cycle() << endl;

	switch (_state) {
	case GOTO:
		if (Utils::InOurPenaltyArea(ball.Pos(), 10)) {
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "Ball in our pen", COLOR_CYAN);
			blockingOuterOppTime(pVision, _executor);
		}
		else if (!ball.Valid()) { // when the ball can be detected by vision,force the top towards it
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "Ball invalid", COLOR_CYAN);
			double faceDir = opp.Dir() + Param::Math::PI;
			setSubTask(PlayerRole::makeItChaseKickV1(_executor, faceDir, flag_not_dribble));
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in GOTO1", COLOR_ORANGE);
		}
		else if (checkUsingVoilence(pVision, _executor)) {
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "violence", COLOR_CYAN);
			voilenceActionTime(pVision, _executor);
		}
		else if (checkTheyCanShoot(pVision, _executor)) { //when oppoent ready to shoot,force the top towards it
			//pullBackFlag = false;
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "they can shoot", COLOR_CYAN);
			double faceDir = opp.Dir() + Param::Math::PI;
			setSubTask(PlayerRole::makeItChaseKickV1(_executor, faceDir, flag_not_dribble));
			//setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor,faceDir));
			if (ball2meDist < 30 && ball2oppDist < 30) {
				pullBackFlag = true;
				pullCnt++;
			}
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in GOTO2", COLOR_ORANGE);
		}
		else if (ballMoving2Opp(pVision) && ball.Vel().mod() > 100 && !meNearballThanOpp(pVision, _executor) && oppBetweenBallAndMe(pVision, _executor)) {
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "Blocking opp", COLOR_CYAN);
			//cout << "blockingBestOppTime!!!" << endl;
			blockingBestOppTime(pVision, _executor);
		}
		else {
			KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
			kickDir = KickDirection::Instance()->getRealKickDir();

			if (!ballOnTheirHalf(pVision)) { // ball in our half-field - 50(The radius of the middle circle)
											 /*				passDir = ((pVision->OurPlayer(tandemNum).Y() < 0 ? relief_l_pos : relief_r_pos) - me.Pos()).dir();*/
				if (ball.Pos().x() > -(Param::Field::PITCH_LENGTH / 2) + RELIEF_DIST) {
					if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "Ball in mid field", COLOR_CYAN);
					setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
					//setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, kickDir));
					if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in GOTO3", COLOR_ORANGE);
				}
				else {
					/*double directToTheirGoalDir = Utils::Normalize((theirCenter - ball.Pos()).dir());
					if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "Ball in back field", COLOR_CYAN);
					setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, passDir, CVector(0, 0), flag_not_dribble, (-1.0)));
					if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in GOTO4", COLOR_ORANGE);*/
					KickStatus::Instance()->setChipKick(_executor, BACK_POWER);
					setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));

				}
				//cout << "here here here" << endl;
			}
			else { //ball in opponent's half-field + 50 (The radius of the middle circle)
				if (Utils::InTheirPenaltyArea(ball.Pos(), 0)) { // ball in opponent's exclusion zone
					if (!Utils::InTheirPenaltyArea(me.Pos(), 0)) { // our robot not in opponent's exclusion zone
																   // cout << Utils::InTheirPenaltyArea(me.Pos(), 0) << endl;
						if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "Ball and me in their pen", COLOR_CYAN);
						setSubTask(PlayerRole::makeItGoto(_executor, ball.Pos(), kickDir, CVector(0, 0), 0, flag_not_dribble));
					}
					else {
						// cout << Utils::InTheirPenaltyArea(me.Pos(), 0) << endl;
						if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "Ball in their pen", COLOR_CYAN);
						setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
						if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in GOTO5", COLOR_ORANGE);
					}
				}
				else { // ball not in opponent's exclusion zone
					pullBackFlag = false;
					if (ballBetweentMeAndOpp(pVision, _executor) && me2goal.mod() < PULL_DIST) { // (opponent's most threatening robot face to their goal) and (ball is between our robot and opponent's most threatening robot)
						pullBackFlag = true;
						pullCnt++;
						KickStatus::Instance()->clearAll();
						if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "ball between me and opp", COLOR_CYAN);
						const CGeoSegment self2targetSeg = CGeoSegment(me.Pos(), me.Pos() + Utils::Polar2Vector(800, Utils::Normalize(kickDir)));
						const bool isOppoentOnBallMovingSeg = self2targetSeg.IsPointOnLineOnSegment(opp.Pos());
						if (NumofPlayerInFrontfiled == 1 && !isOppoentOnBallMovingSeg && pullCnt > 150) {
							KickStatus::Instance()->setKick(_executor, KICKPOWER);
							setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
						}
						else { setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble)); }
						//setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
						//setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, kickDir));
						if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in GOTO6", COLOR_ORANGE);

					}
					else { // easily jump to this part
						if (ball2oppDist < Param::Vehicle::V2::PLAYER_SIZE * 8) {
							if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "Ball close to opp", COLOR_CYAN);
							double faceDir = generateNormalPushDir(pVision, _executor);
							if (pVision->GetCurrentRefereeMsg() == "ourPenaltyKick" && pVision->OurPlayer(task().executor).Pos().x() < 225) {
								KickStatus::Instance()->setChipKick(_executor, BACK_POWER_V3);
								setSubTask(PlayerRole::makeItChaseKickV1(_executor, faceDir, flag_not_dribble));
							}
							KickStatus::Instance()->setKick(_executor, KICKPOWER);
							setSubTask(PlayerRole::makeItChaseKickV1(_executor, faceDir, flag_not_dribble));
							//setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, kickDir));
							if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in GOTO7", COLOR_ORANGE);
							//cout << "here here here here here  " << pVision->Cycle() << endl;
						}
						else {
							if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(ball.Pos(), "Ball far from opp", COLOR_CYAN);
							if (pVision->GetCurrentRefereeMsg() == "ourPenaltyKick" && pVision->OurPlayer(task().executor).Pos().x() < 225) {
								KickStatus::Instance()->setChipKick(_executor, BACK_POWER_V3);
								setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
							}
							setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
							//setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, kickDir));
							//if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in GOTO8", COLOR_ORANGE);
							//cout << "there there there there there" << endl;
						}
					}
				}
			}
		}
		break;
	case PENALTY:
		if (ball.Pos().x() < 0) {
			KickStatus::Instance()->setChipKick(_executor, BACK_POWER_V3);
			setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
			break;
		}
		else
		{
			KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
			CVector shootTarget = CVector(450, 30);
			//if (rand() % 2 == 0) {
			//	CVector shootTarget = CVector(450, -50 + rand() % 21);
			//}
			//else
			//{
			//	CVector shootTarget = CVector(450, 50 - rand() % 21);
			//}
			CVector dirPos = shootTarget - CVector(ball.Pos().x(), ball.Pos().y());
			kickDir = dirPos.dir();
			KickStatus::Instance()->setKick(_executor, RELIEF_POWER);
			setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
		}
		break;
	case RELIEF:
		/*		if (!(pVision->OurPlayer(tandemNum).Valid())) {
		KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
		kickDir = KickDirection::Instance()->getRealKickDir();
		KickStatus::Instance()->setChipKick(_executor, RELIEF_POWER);
		setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
		}
		else {
		if (pVision->OurPlayer(tandemNum).Y() < RELIEF_BIAS || pVision->OurPlayer(tandemNum).Y() > -RELIEF_BIAS) {
		passDir = ((pVision->OurPlayer(tandemNum).VelY() < 0 ? relief_l_pos : relief_r_pos) - me.Pos()).dir();
		}
		passDir = ((pVision->OurPlayer(tandemNum).Y() < 0 ? relief_l_pos : relief_r_pos) - me.Pos()).dir();
		pass_dir_ok = abs(me.Dir() - passDir) < 1.5*Param::Math::PI / SHOOT_PRECISION;
		if (pass_dir_ok) {
		KickStatus::Instance()->setChipKick(_executor, RELIEF_POWER);
		setSubTask(PlayerRole::makeItChaseKickV1(_executor, passDir, flag_not_dribble));
		if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in RELIEF", COLOR_ORANGE);
		}
		setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, passDir));
		}*/
		KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
		kickDir = KickDirection::Instance()->getRealKickDir();
		if (pVision->GetCurrentRefereeMsg() == "ourPenaltyKick" && pVision->OurPlayer(task().executor).Pos().x() < 225) {
			KickStatus::Instance()->setChipKick(_executor, BACK_POWER_V3);
			setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
		}
		KickStatus::Instance()->setChipKick(_executor, RELIEF_POWER);
		setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
		break;
	case DRIBBLE_PULL:
		if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -375), "turn to Dribblepull", COLOR_YELLOW);
		if ((!pVision->OurPlayer(tandemNum).Valid()) || NumofPlayerInFrontfiled == 1) {
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-20, -375), "Only One Attacker", COLOR_YELLOW);
			KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
			kickDir = KickDirection::Instance()->getRealKickDir();
			setSubTask(PlayerRole::makeItSimpleGoto(_executor, pullBallTarget, kickDir, CVector(0, 0), -4, flag));
			if (ball2meDist < 20 && ball2oppDist>25) {
				KickStatus::Instance()->setChipKick(_executor, 0.4 * ADV_CPASSPOWER);
				setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
			}
		}
		else if (me2goal.mod() > PULL_DIST&& me2goal.mod() < 1.4 * PULL_DIST && ball2meDist < 15) {
			setSubTask(PlayerRole::makeItSimpleGoto(_executor, me.Pos() + Utils::Polar2Vector(40, Utils::Normalize(me.Dir() + Param::Math::PI)), me.Dir(), CVector(0, 0), -4, flag));
			KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
			kickDir = KickDirection::Instance()->getRealKickDir();
			if (ball2meDist < 20 && ball2oppDist>25) {
				KickStatus::Instance()->setChipKick(_executor, 0.0009 * ADV_CPASSPOWER * me2goal.mod());
				setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
			}
		}
		else {
			if (me2goal.mod() <= PULL_DIST && ball2meDist < 15 && ball2oppDist>35 && pass_dir_ok) {
				_state = GOTO;
				break;
			}
			setSubTask(PlayerRole::makeItSimpleGoto(_executor, pullBallTarget, kickDir, CVector(0, 0), -4, flag));
		}
		break;
	case NORMAL_PUSH:
		KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
		if (!ballOnTheirHalf(pVision)) { //our half-field - 50(radius of the middle circle)
			kickDir = KickDirection::Instance()->getRealKickDir();
		}
		else {
			kickDir = generateNormalPushDir(pVision, _executor);
		}
		if (normalPushCnt > 60 * 1.25 && USE_DRIBBLE_TURN) {
			DribbleStatus::Instance()->setDribbleCommand(_executor, 2);
			setSubTask(PlayerRole::makeItChaseKickV2(_executor, kickDir, flag));
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in NorPush", COLOR_ORANGE);
		}
		else {
			//cout << "here" << endl;
			//setSubTask(PlayerRole::makeItCrazyPush(_executor, kickDir));
			setSubTask(PlayerRole::makeItChaseKickV2(_executor, kickDir, flag_not_dribble));
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in NorPush", COLOR_ORANGE);
		}
		break;
	case DRIBBLE_TURN:
		setSubTask(PlayerRole::makeItDribbleTurn(_executor, dribbleTurnFinalDir, Param::Math::PI / 36));
		break;
	case LIGHT_KICK:
		KickStatus::Instance()->clearAll();
		KickStatus::Instance()->setKick(_executor, 1); // kick lightly
		break;
	case KICK:
		KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
		kickDir = KickDirection::Instance()->getRealKickDir();
		KickStatus::Instance()->clearAll();
		if (pVision->GetCurrentRefereeMsg() == "ourPenaltyKick" && pVision->OurPlayer(task().executor).Pos().x() < 225) {
			KickStatus::Instance()->setChipKick(_executor, BACK_POWER_V3);
			setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
		}
		if (ballInTheirPenaltyArea(pVision, _executor)) {
			setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in KICK", COLOR_ORANGE);
		}
		else {
			if (is_runner_dir_ok) {
				decideChipOrShoot(pVision, kickDir, _executor);
				setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
				if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in KICK", COLOR_ORANGE);
			}
			//cout << "there there there" << endl;
			setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, kickDir));
			//setSubTask(PlayerRole::makeItChaseKickV1(_executor, kickDir, flag_not_dribble));
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in KICK", COLOR_ORANGE);
		}
		break;
	case FLATPASS:
		//passDir=(CGeoPoint(0,0)- pVision->OurPlayer(_executor).Pos()).dir();
		//KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
		passDir = ((pVision->OurPlayer(tandemNum).Pos() + pVision->OurPlayer(tandemNum).Vel() / vel_flat) - pVision->OurPlayer(_executor).Pos()).dir();//依据接球车速度做传球点修正
		pass_dir_ok = abs(me.Dir() - passDir) < 0.8 * Param::Math::PI / SHOOT_PRECISION;
		if (pass_dir_ok) {
			if (ball2oppDist < 50) {
				break;
			}
			KickStatus::Instance()->setKick(_executor,ADV_FPASSPOWER * sqrt(Me2Receiver));//KICKPOWER need to correct
			setSubTask(PlayerRole::makeItChaseKickV1(_executor, passDir, flag_not_dribble));
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in FLATPASS", COLOR_ORANGE);
		}
		else {
			if (ball2oppDist < 50) {
				break;
			}
			setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, passDir, CVector(0, 0), flag_not_dribble, (-2.0)));
			//setSubTask(PlayerRole::makeItSimpleGoto(_executor, me.Pos() + Utils::Polar2Vector(30, Utils::Normalize(me.Dir() + Param::Math::PI)), passDir, CVector(0, 0), 0, flag));
		}

		if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "In FLATPASS", COLOR_YELLOW);
		break;
	case CHIPPASS:
		//KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
		passDir = ((pVision->OurPlayer(tandemNum).Pos() + pVision->OurPlayer(tandemNum).Vel() / vel_flat) - pVision->OurPlayer(_executor).Pos()).dir();//依据接球车速度做传球点修正
		pass_dir_ok = abs(me.Dir() - passDir) < 0.7 * Param::Math::PI / SHOOT_PRECISION;
		if (pass_dir_ok) {
			if (ball2oppDist < 35) {
				break;
			}
			KickStatus::Instance()->setChipKick(_executor, 0.0026 * ADV_CPASSPOWER * Me2Receiver);//KICKPOWER need to correct
			setSubTask(PlayerRole::makeItChaseKickV1(_executor, passDir, flag_not_dribble));
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in CHIPPASS", COLOR_ORANGE);
		}
		else {
			if (ball2oppDist < 35) {
				break;
			}
			setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, passDir, CVector(0, 0), flag_not_dribble, (-2.0)));
			//setSubTask(PlayerRole::makeItSimpleGoto(_executor, me.Pos() + Utils::Polar2Vector(30, Utils::Normalize(me.Dir() + Param::Math::PI)), passDir, CVector(0, 0), 0, flag));
		}
		if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "In CHIPPASS", COLOR_YELLOW);
		break;
	}


	_cycle = pVision->Cycle();
	CStatedTask::plan(pVision);
}

//functions for judging position
bool CAdvanceBallV3::ballInTheirPenaltyArea(const CVisionModule* pVision, const int vecNumber) {
	const BallVisionT& ball = pVision->Ball();
	return Utils::InTheirPenaltyArea(ball.Pos(), 0);
}

bool CAdvanceBallV3::checkBallBehind(const CVisionModule* pVision, double angle) {
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	CVector ball2opp = opp.Pos() - ball.Pos();
	bool ballDirBehindOpp = abs(Utils::Normalize(opp.Dir() - ball2opp.dir())) < angle;
	bool ballDistBehindOpp = ball2opp.mod() < OPP_HAS_BALL_DIST;
	//GDebugEngine::Instance()->gui_debug_line(opp.Pos(),opp.Pos() + Utils::Polar2Vector(200 , 0),COLOR_BLACK);
	bool isBallBehindOpp = ballDirBehindOpp && ballDistBehindOpp;
	return isBallBehindOpp;
}

bool CAdvanceBallV3::checkBallFront(const CVisionModule* pVision, double angle) {
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	CVector opp2ball = ball.Pos() - opp.Pos();
	bool ballDirFrontOpp = abs(Utils::Normalize(opp.Dir() - opp2ball.dir())) < angle;
	bool ballDistFrontOpp = opp2ball.mod() < OPP_HAS_BALL_DIST + 10;
	//GDebugEngine::Instance()->gui_debug_line(opp.Pos(),opp.Pos() + Utils::Polar2Vector(200 , 0),COLOR_BLACK);
	bool isBallFrontOpp = ballDirFrontOpp && ballDistFrontOpp;
	return isBallFrontOpp;
}

bool CAdvanceBallV3::ballBetweentMeAndOpp(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	double kickDir = KickDirection::Instance()->getRealKickDir();
	const CGeoSegment self2targetSeg = CGeoSegment(me.Pos(), me.Pos() + Utils::Polar2Vector(800, Utils::Normalize(kickDir)));

	CVector me2Ball = ball.Pos() - me.Pos();
	CVector ball2Opp = opp.Pos() - ball.Pos();
	const bool isOppoentOnBallMovingSeg = self2targetSeg.IsPointOnLineOnSegment(opp.Pos());

	if (abs(Utils::Normalize(me2Ball.dir() - ball2Opp.dir())) < Param::Math::PI * 55 / 180 && isOppoentOnBallMovingSeg) {
		return true;
	}
	else {
		return false;
	}
}

bool CAdvanceBallV3::meFaceOpp(const CVisionModule* pVision, const int vecNumber) { // two robots face to face,and very close to each other
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();

	const double meDir = me.Dir();
	const double oppDir = opp.Dir();
	const double meToOppDist = (me.Pos() - opp.Pos()).mod();

	if ((abs(Utils::Normalize(meDir - oppDir)) > Param::Math::PI / 1.5) && meToOppDist < 30.0) {
		return true;
	}
	else {
		return false;
	}
}

bool CAdvanceBallV3::checkBallFrontOrBehindBigPre(const CVisionModule* pVision) {
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	double opp2BallDir = CVector(ball.Pos() - opp.Pos()).dir();
	double oppDir = opp.Dir();
	double opp2BallDir_oppDir_Diff = abs(Utils::Normalize(opp2BallDir - oppDir));
	bool isBallFrontOpp;
	isBallFrontOpp = opp2BallDir_oppDir_Diff < Param::Math::PI * 2.0 / 3.0;
	return isBallFrontOpp;
}

bool CAdvanceBallV3::isOppFaceTheirDoor(const CVisionModule* pVision, const double angle) {
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	double opp2BallDist = (opp.Pos() - ball.Pos()).mod();
	double judgeAngle = abs(Utils::Normalize((opp.Dir() - CVector(CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, 0) - opp.Pos()).dir()))); //Abs( the angle of (the direction of opponent's most threatening robot) and (the direction of the robot towards the center of their gate) )
	bool isFaceTheirDoor = judgeAngle < angle || judgeAngle == angle;
	bool isBallNearOpp = opp2BallDist < OPP_HAS_BALL_DIST;
	//GDebugEngine::Instance()->gui_debug_line(opp.Pos(), opp.Pos() + Utils::Polar2Vector(200,Utils::Normalize(opp.Dir() + Param::Math::PI / 3)),COLOR_WHITE);
	//GDebugEngine::Instance()->gui_debug_line(opp.Pos(), opp.Pos() + Utils::Polar2Vector(200,Utils::Normalize(opp.Dir() - Param::Math::PI / 3)),COLOR_WHITE);
	return isFaceTheirDoor && isBallNearOpp;
}

bool CAdvanceBallV3::isOppFaceOurDoor(const CVisionModule* pVision, double angle) {
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	double opp2BallDist = (opp.Pos() - ball.Pos()).mod();
	bool isBallNearOpp = opp2BallDist < OPP_HAS_BALL_DIST;
	double judgeAngle = abs(Utils::Normalize((opp.Dir() - CVector(CGeoPoint(-Param::Field::PITCH_LENGTH / 2.0, 0) - opp.Pos()).dir())));
	bool isFaceOurDoor = judgeAngle < angle || judgeAngle == angle;
	return isFaceOurDoor && isBallNearOpp;
}

bool CAdvanceBallV3::ballOnTheirHalf(const CVisionModule* pVision) {
	if (pVision->Ball().X() > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool CAdvanceBallV3::meFaceTheirDoor(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	double me2GoalAngle;
	me2GoalAngle = abs(Utils::Normalize((CVector(CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, 0) - me.Pos()).dir() - me.Dir())));
	if (me2GoalAngle < Param::Math::PI / 3) {
		return true;
	}
	else {
		return false;
	}
}

//functions of action
void CAdvanceBallV3::voilenceActionTime(const CVisionModule* pVision, int vecNumber) {
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	CVector opp2me = CVector(me.Pos() - opp.Pos());
	CGeoPoint faceTarget = ball.Pos();
	double extr_dist = 0.0;
	CVector self2ball = ball.Pos() - me.Pos();
	if (self2ball.mod() > 60) {
		extr_dist = self2ball.mod() * self2ball.mod() / 500;
		if (extr_dist > 150) {
			extr_dist = 150;
		}
		CGeoPoint fast_point = faceTarget + Utils::Polar2Vector(extr_dist, (faceTarget - me.Pos()).dir());
		if (!Utils::OutOfField(fast_point, 0)) {
			faceTarget = fast_point;
		}
	}
	CVector finalSpeed = Utils::Polar2Vector(500, (faceTarget - me.Pos()).dir());
	TaskT task;
	task.executor = vecNumber;
	task.player.angle = Utils::Normalize(self2ball.dir() + Param::Math::PI);
	task.player.max_acceleration = 650;
	task.player.pos = opp.Pos();
	task.player.vel = finalSpeed;
	task.player.max_deceleration = 650;
	setSubTask(TaskFactoryV2::Instance()->GotoPosition(task));
}

void CAdvanceBallV3::blockingOuterOppTime(const CVisionModule* pVision, int vecNumber) {
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	int flag = task().player.flag;

	CGeoPoint blockingIntoPenaltyPoint = CGeoPoint(0, 0);
	int theirBestPlayerOutOurPenalty = 0;
	double theirBestPlayerOutOurPenalty2Goal = 0;

	const CBestPlayer::PlayerList& oppList = BestPlayer::Instance()->theirFastestPlayerToBallList();
	int OppNum = oppList.size();
	for (int i = 0; i < OppNum; i++) {
		CGeoPoint oppPos = pVision->TheirPlayer(oppList[i].num).Pos();
		if (!Utils::InOurPenaltyArea(oppPos, 0)) {
			theirBestPlayerOutOurPenalty = oppList[i].num;
			posSide side = POS_SIDE_MIDDLE;
			theirBestPlayerOutOurPenalty2Goal = CVector(oppPos - CGeoPoint(-Param::Field::PITCH_LENGTH / 2.0, 0)).dir();
			blockingIntoPenaltyPoint = DefendUtils::calcPenaltyLinePoint(theirBestPlayerOutOurPenalty2Goal, side, 1);
			break;
		}
	}
	double me2TheOppDir = (pVision->TheirPlayer(theirBestPlayerOutOurPenalty).Pos() - me.Pos()).dir();
	setSubTask(PlayerRole::makeItSimpleGoto(vecNumber, blockingIntoPenaltyPoint, me2TheOppDir, CVector(0, 0), 0, flag));
}

void CAdvanceBallV3::blockingBestOppTime(const CVisionModule* pVision, int vecNumber) {
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	CGeoSegment oppShootLine = CGeoSegment(opp.Pos(), CGeoPoint(-Param::Field::PITCH_LENGTH / 2.0, 0));
	CGeoCirlce oppCircle = CGeoCirlce(opp.Pos(), OPP_HAS_BALL_DIST * 0.8);
	CGeoSegmentCircleIntersection intersectionPoint = CGeoSegmentCircleIntersection(oppShootLine, oppCircle);
	CGeoPoint movingPoint = intersectionPoint.point1();
	CVector me2Ball = ball.Pos() - me.Pos();
	//setSubTask(PlayerRole::makeItSimpleGoto(vecNumber, movingPoint, me2Ball.dir(), CVector(0, 0), 0, 0));
	setSubTask(PlayerRole::makeItGoto(vecNumber, movingPoint, me2Ball.dir(), CVector(0, 0), 0, 0));
}

//functions for conditional judgment
bool CAdvanceBallV3::ballMoving2Opp(const CVisionModule* pVision) {
	const BallVisionT& ball = pVision->Ball();
	if (opponentID > 0) {
		const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
		CVector ball2enemy = opp.Pos() - ball.Pos();
		double diff_ballMoving2Opp = Utils::Normalize(ball2enemy.dir() - ball.Vel().dir());
		if (ball.Valid() && abs(diff_ballMoving2Opp) < Param::Math::PI / 12) {
			//cout << "ballMoning2Opp!!!" << endl;
			return true;
		}
	}
	return false;
}

bool CAdvanceBallV3::isMePassedOpp(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();

	CVector me2opp = opp.Pos() - me.Pos();
	CVector opp2Ball = ball.Pos() - opp.Pos();
	CVector ball2Opp = opp.Pos() - ball.Pos();
	CVector me2Ball = ball.Pos() - me.Pos();
	bool meDirControlBall = abs(Utils::Normalize(me2Ball.dir() - me.Dir())) < Param::Math::PI / 4;
	bool meDistControlBall = me2Ball.mod() < Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + 10.5;
	bool mePassOpp_1 = abs(Utils::Normalize(me2Ball.dir() - me2opp.dir())) > Param::Math::PI / 2.5;
	bool mePassOpp_2 = abs(Utils::Normalize(opp.Dir() - ball2Opp.dir())) < Param::Math::PI / 3.0;
	if (meDistControlBall && meDistControlBall && (mePassOpp_1 || mePassOpp_2) || me2opp.mod() > 25) {
		// GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 0), "PASS!!!!!!!!!!!", COLOR_WHITE);
		return true;
	}
	else {
		return false;
	}
}

bool CAdvanceBallV3::isVisionHasBall(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	double visionJudgDist = 11;
	bool distVisionHasBall = CVector(me.Pos() - ball.Pos()).mod() <= visionJudgDist;
	// cout << CVector(me.Pos() - ball.Pos()).mod() << endl;
	bool dirVisionHasBall;
	double meDir = me.Dir();
	double me2Ball = (ball.Pos() - me.Pos()).dir();
	double meDir_me2Ball_Diff = abs(Utils::Normalize((meDir - me2Ball)));
	if (meDir_me2Ball_Diff < Param::Math::PI / 6.0) {
		dirVisionHasBall = true;
	}
	else {
		dirVisionHasBall = false;
	}
	bool isVisionPossession = dirVisionHasBall && distVisionHasBall;
	return isVisionPossession;
}

bool CAdvanceBallV3::isShootBlockedInPenaltyArea(const CVisionModule* pVision, const int vecNumber)
{
	//to judge whether a series of shooting angle be blocked of not 

	//imformation of images
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	//to judge whether be blocked or not
	bool isBlocked;

	KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
	double kickDir = KickDirection::Instance()->getRealKickDir();

	CGeoLine ball2ourGoal = /*CGeoLine(me.Pos(),ourGoal); */CGeoLine(me.Pos(), kickDir);
	CGeoPoint projectionPoint = ball2ourGoal.projection(opp.Pos());
	double opp2LineDist = (projectionPoint - opp.Pos()).mod();
	//	bool isPassOpp;//false means haven't passed
	//isPassOpp =/*Utils::Normalize( me.Dir() - (opp.Pos() - me.Pos()).dir()) > Param::Math::PI/3; */isMePassedOpp(pVision,vecNumber);

	isBlocked = opp2LineDist < (Param::Vehicle::V2::PLAYER_SIZE + 5)/*&& !isPassOpp*/;
	//cout <<"opp2LineDist"<<opp2LineDist<<"   dist:"<<opp2LineDist<<" "<<endl;
	if (isBlocked) {
		return true;
	}
	else {
		return false;
	}
}

bool CAdvanceBallV3::isShootBlocked(const CVisionModule* pVision, const int vecNumber) {
	//to judge whether a series of shooting angle be blocked of not

	//imformation of images
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);

	KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
	double kickDir = KickDirection::Instance()->getRealKickDir();

	CGeoLine ball2ourGoal = /*CGeoLine(me.Pos(),ourGoal); */CGeoLine(me.Pos(), kickDir);
	CGeoPoint theirGoal(Param::Field::PITCH_LENGTH / 2, 0);
	CVector ball2theirGoal = theirGoal - ball.Pos();
	double shootRange = 0;
	shootRange = ball2theirGoal.mod() * abs(Param::Math::PI / 180 * CHIP_ANGLE);
	//cout << "opp2LineDist:"<<opp2LineDist<<"  "<<"isPassOpp"<<isPassOpp<<endl;
	if (shootRange > Param::Field::GOAL_WIDTH) {
		return true;
	}
	else {
		CGeoPoint projectionPoint = ball2ourGoal.projection(opp.Pos());
		double opp2LineDist = (projectionPoint - opp.Pos()).mod();
		bool isPassOpp = isMePassedOpp(pVision, vecNumber);
		bool isBlocked = opp2LineDist < 1.5 * Param::Vehicle::V2::PLAYER_SIZE && !isPassOpp;
		if (isBlocked && (ball2theirGoal.mod() > CHIPPOWER))
		{
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "want to chip", COLOR_CYAN);

			return true;
		}
		return false;
	}
}

bool CAdvanceBallV3::checkOppHasBall(const CVisionModule* pVision) {
	int _executor = task().executor;
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(_executor);
	const CVector self2ball = ball.Pos() - me.Pos();
	//compute the datas of opponent's most threatening robot
	opponentID = 0;

	const CBestPlayer::PlayerList& oppList = BestPlayer::Instance()->theirFastestPlayerToBallList();
	if (oppList.size() < 1)
		return false;
	else
		opponentID = oppList[0].num;

	if (!pVision->TheirPlayer(opponentID).Valid()) {
		opponentID = getTheirMostClosetoPosPlayerNum(pVision, pVision->Ball().Pos());
	}
	const PlayerVisionT& opponent = pVision->TheirPlayer(opponentID);

	//mark opponent's most threatening robot
	if (true && DEBUG_ENGINE) {
		drawBestOpp(opponent.Pos());
	}

	CVector opponent2ball = ball.Pos() - opponent.Pos();
	CVector opp2ourGoal = ourGoal - opponent.Pos();
	double opponent2ball_diff = fabs(Utils::Normalize(opponent2ball.dir() - opponent.Dir()));
	double judgeDist = OPP_HAS_BALL_DIST;
	if (opponent2ball.mod() < judgeDist && opponent2ball_diff < Param::Math::PI * 70 / 180)
		return true; // take opponent's direction into consideration.If direction not towards the ball,ignore it
	else
		return false;
}

//bool CAdvanceBallV3::checkUsingVoilence(const CVisionModule*pVision, int vecNumber) {
//	const BallVisionT& ball = pVision->Ball();
//	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
//	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
//	CVector opp2ball = ball.Pos() - opp.Pos();
//	if (ball.X() < 0 && !WEAK_OPP && isOppFaceOurDoor(pVision)&&checkBallFront(pVision) && !ballBetweentMeAndOpp(pVision,vecNumber)) {
//		return true;
//	}
//	else { return false; }
//}

bool CAdvanceBallV3::checkUsingVoilence(const CVisionModule* pVision, int vecNumber) {
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	CVector opp2ball = ball.Pos() - opp.Pos();
	if (!WEAK_OPP && isOppFaceOurDoor(pVision, Param::Math::PI / 3.0) && checkBallFront(pVision, Param::Math::PI / 3.0) && (!ballBetweentMeAndOpp(pVision, vecNumber) || me.Pos().x() > opp.Pos().x())) {
		return true;
	}
	else { return false; }
}

bool CAdvanceBallV3::checkTheyCanShoot(const CVisionModule* pVision, int vecNumber) {
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

//bool cadvanceballv3::oppblockme(const cvisionmodule* pvision, const int vecnumber) {
//	const ballvisiont& ball = pvision->ball();
//	const playervisiont& me = pvision->ourplayer(vecnumber);
//	const playervisiont& opp = pvision->theirplayer(opponentid);
//	cgeoline shootline = cgeoline(me.pos(), cvector(ball.pos() - me.pos()).dir());
//	cgeopoint projecpoint = shootline.projection(opp.pos());
//	cvector me2goal = theircenter - me.pos();
//	cvector me2ball = ball.pos() - me.pos();
//	cvector ball2opp = opp.pos() - ball.pos();
//	cvector me2opp = opp.pos() - me.pos();
//	bool isballnearopp = (ball2opp.mod() < 35);
//	bool ismefacetheirgoal = abs(utils::normalize(me.dir() - me2goal.dir())) < param::math::pi / 6.0;
//	bool oppfrontme = abs(utils::normalize(me2ball.dir() - me2opp.dir())) < param::math::pi / 2.0;
//	if (projecpoint.dist(opp.pos()) < 3*param::vehicle::v2::player_size + param::field::ball_size /*&& (ball.pos().x() > me.pos().x() && ball.pos().x() < opp.pos().x())*/) {
//	return true && /*ismefacetheirgoal &&*/ isballnearopp && oppfrontme; //;
//	}
//	else {
//	return false;
//	}
//}

bool CAdvanceBallV3::oppBlockMe(const CVisionModule* pVision, const int vecNumber) {
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	CGeoLine shootLine = CGeoLine(me.Pos(), CVector(ball.Pos() - me.Pos()).dir());
	CVector me2Goal = theirCenter - me.Pos();
	CVector me2Ball = ball.Pos() - me.Pos();
	CGeoPoint projectionPoint;
	int n = 0;
	double opp2LineDist = 0;
	while (n <= Param::Field::MAX_PLAYER) {
		if (!pVision->TheirPlayer(n).Valid()) { n++; continue; }
		projectionPoint = shootLine.projection(pVision->TheirPlayer(n).Pos());
		CVector ball2opp = opp.Pos() - ball.Pos();
		CVector me2Opp = opp.Pos() - me.Pos();
		bool isBallNearOpp = (ball2opp.mod() < 35);
		bool isMeFaceTheirGoal = abs(Utils::Normalize(me.Dir() - me2Goal.dir())) < Param::Math::PI / 6.0;
		bool oppFrontMe = abs(Utils::Normalize(me2Ball.dir() - me2Opp.dir())) < Param::Math::PI / 2.0;

		opp2LineDist = (projectionPoint - pVision->TheirPlayer(n).Pos()).mod();

		if (opp2LineDist < 3 * Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE && isBallNearOpp && oppFrontMe) {
			return  true;
		}
		n++;
	}
	return false;

}




bool CAdvanceBallV3::selectChipKick(const CVisionModule* pVision, int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	if (!opp.Valid()) { return true; }
	KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
	double kickDir = KickDirection::Instance()->getRealKickDir();
	CVector ball2opp = opp.Pos() - ball.Pos();
	CVector me2ball = ball.Pos() - me.Pos();
	CGeoLine ball2Goal = CGeoLine(ball.Pos(), kickDir);
	CGeoPoint projPoint = ball2Goal.projection(opp.Pos());
	double blockDist = opp.Pos().dist(projPoint);
	double oppDist = opp.Pos().dist(ball.Pos());
	if (oppDist > 20) {
		return true;
	}
	return false;
}

//functions for calculation
void CAdvanceBallV3::calcPushTarget(const CVisionModule* pVision) {
	int _executor = task().executor;
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(_executor);
	const CVector self2ball = ball.Pos() - me.Pos();

	// priority is given to whether there is congestion in the direction of the goal
	CVector ball2theirGoal = theirCenter - ball.Pos();
	bool is_shootline_blocked = false;
	int opp_best_index = 0;
	double oppDist2Ball = 1000;
	int left_opp_num = 0;
	int right_opp_num = 0;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (!pVision->TheirPlayer(i).Valid())
			continue;

		const PlayerVisionT& opp = pVision->TheirPlayer(i);
		if (opp.Pos().dist(theirCenter) < 80)
			continue;

		CVector ball2opp = opp.Pos() - ball.Pos();
		double diff_block = Utils::Normalize(ball2opp.dir() - ball2theirGoal.dir());

		if (abs(diff_block) < Param::Math::PI / 4 && ball2opp.mod() < 50)
			is_shootline_blocked = true;

		if (opp.Y() > 0)
			right_opp_num++;
		else
			left_opp_num++;

		if (ball2opp.mod() < oppDist2Ball) {
			opp_best_index = i;
			oppDist2Ball = ball2opp.mod();
		}
	}

	//only if robot has controlled the ball safely, can the function  considers to change the pushTarget
	bool safe_change_dir = false;
	if (opp_best_index > 0) {
		const PlayerVisionT& bestOpp = pVision->TheirPlayer(opp_best_index);
		CVector bestOpp2ball = ball.Pos() - bestOpp.Pos();
		double usBlockAngle = Utils::Normalize(bestOpp2ball.dir() - self2ball.dir());
		if (RobotSensor::Instance()->IsInfraredOn(_executor) &&
			abs(usBlockAngle) < Param::Math::PI / 2.0)
			safe_change_dir = true;
	}

	if (!safe_change_dir) {
		_pushBallTarget = theirCenter;
		return;
	}

	if (!is_shootline_blocked)
		attack_side = ATTACK_TO_CENTER;
	else if (attack_side == ATTACK_TO_CENTER) {
		attack_side = left_opp_num > right_opp_num ? ATTACK_TO_RIGHT : ATTACK_TO_LEFT;
	}
	else if (attack_side == ATTACK_TO_LEFT) {
		attack_side = left_opp_num > right_opp_num + 1 ? ATTACK_TO_RIGHT : ATTACK_TO_LEFT;
	}
	else {
		attack_side = right_opp_num > left_opp_num + 1 ? ATTACK_TO_LEFT : ATTACK_TO_RIGHT;
	}

	// check the position of the nearest teammate
	double minDist = 100;
	int friendID = 0;
	int friendSide = 0; // 1 means right,-1 means left
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (i == _executor)
			continue;
		if (!pVision->OurPlayer(i).Valid())
			continue;
		const PlayerVisionT& myfriend = pVision->OurPlayer(i);
		if (myfriend.Pos().dist(ourGoal) < 80)
			continue;

		double friendDist = myfriend.Pos().dist(me.Pos());
		if (friendDist < minDist) {
			friendID = i;
			minDist = friendDist;
			CVector ball2friend = myfriend.Pos() - ball.Pos();
			double diff2friend = Utils::Normalize(ball2friend.dir() - self2ball.dir());
			//cout<<"No."<<i<<" diff friend:"<<Utils::Rad2Deg(diff2friend)<<endl;
			if (abs(diff2friend) > 5 * Param::Math::PI / 12)
				continue;

			// assume that the direction when our robot catch the ball is towards opponent's half-field
			friendSide = diff2friend > 0 ? 1 : -1;
		}
	}

	double push_dir;
	if (friendSide != 0) {
		const PlayerVisionT& selected_friend = pVision->OurPlayer(friendID);
		CGeoPoint friend_front = selected_friend.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER, selected_friend.Dir());
		CVector ball2friend = friend_front - ball.Pos();
		double temp_diff = Utils::Normalize(ball2theirGoal.dir() - ball2friend.dir());
		push_dir = Utils::Normalize(ball2friend.dir() + 0.2 * temp_diff);
		if (friendSide > 0)
			push_dir = min(Param::Math::PI / 2, push_dir);
		else if (friendSide < 0)
			push_dir = max(-Param::Math::PI / 2, push_dir);
	}

	switch (attack_side) {
	case ATTACK_TO_CENTER: // if no be blocked,attack towards the middle
		_pushBallTarget = theirCenter;
		break;
	case ATTACK_TO_LEFT:
		if (friendSide < 0 || friendSide > 0 && ball.Y() < Param::Field::PITCH_WIDTH / 2 - 80)
			_pushBallTarget = ball.Pos() + Utils::Polar2Vector(60, push_dir);
		else {
			double pd = Utils::Normalize(ball2theirGoal.dir() - Param::Math::PI / 3);
			pd = max(-Param::Math::PI / 2, pd);
			_pushBallTarget = ball.Pos() + Utils::Polar2Vector(60, pd);
			//cout<<"attack left\n";
		}
		break;
	case ATTACK_TO_RIGHT:
		if (friendSide > 0 || friendSide < 0 && ball.Y() > -Param::Field::PITCH_WIDTH / 2 + 80)
			_pushBallTarget = ball.Pos() + Utils::Polar2Vector(60, push_dir);
		else {
			double pd = Utils::Normalize(ball2theirGoal.dir() + Param::Math::PI / 3);
			pd = min(Param::Math::PI / 2, pd);
			_pushBallTarget = ball.Pos() + Utils::Polar2Vector(60, pd);
			//cout<<"attack right\n";
		}
		break;
	}
}

bool CAdvanceBallV3::checkEnoughSpaceToTurnKick(const CVisionModule* pVision) {
	const BallVisionT& ball = pVision->Ball();
	CGeoPoint goalCenter = CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, 0);
	double ball2GoalCenterDist = (ball.Pos() - goalCenter).mod();
	if (ball2GoalCenterDist > 120 && ball2GoalCenterDist < 230) {
		return true;
	}
	else
		return false;
}

void CAdvanceBallV3::decideChipOrShoot(const CVisionModule* pVision, double& kickDir, const int vecNumber)
{
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);

	bool shootBlocked; //true means be blocked,chipshoot; false means not be blocked,flatshoot

	CGeoLine ball2ourGoal = /*CGeoLine(me.Pos(),ourGoal); */CGeoLine(me.Pos(), kickDir);
	CGeoPoint theirGoal(Param::Field::PITCH_LENGTH / 2, 0);
	CVector ball2theirGoal = theirGoal - ball.Pos();
	double shootRange = 0;
	shootRange = ball2theirGoal.mod() * abs(Param::Math::PI / 180 * CHIP_ANGLE);
	//cout << "opp2LineDist:"<<opp2LineDist<<"  "<<"isPassOpp"<<isPassOpp<<endl;
	if (shootRange > Param::Field::GOAL_WIDTH) {
		if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "too far chip", COLOR_CYAN);
		KickStatus::Instance()->setChipKick(vecNumber, 0.4 * CHIPPOWER);
	}
	else {
		CGeoPoint projectionPoint = ball2ourGoal.projection(opp.Pos());
		double opp2LineDist = (projectionPoint - opp.Pos()).mod();
		bool isPassOpp = isMePassedOpp(pVision, vecNumber);
		bool isBlocked = opp2LineDist < Param::Vehicle::V2::PLAYER_SIZE && !isPassOpp;
		if (ball2theirGoal.mod() < FLAT_DIST)
		{
			if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "close flat", COLOR_CYAN);
			KickStatus::Instance()->setKick(vecNumber, KICKPOWER);
		}
		else {
			if ((me.Pos() - opp.Pos()).mod() > 25 && !checkEnoughSpaceToTurnKick(pVision)) {
				if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), " blocked chip", COLOR_CYAN);
				KickStatus::Instance()->setChipKick(vecNumber, 0.4 * CHIPPOWER);
			}
			else
			{
				if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "open flat", COLOR_CYAN);
				KickStatus::Instance()->setKick(vecNumber, KICKPOWER);
			}
		}
	}
}

void CAdvanceBallV3::drawBestOpp(const CGeoPoint& oppPos) {
	GDebugEngine::Instance()->gui_debug_msg(oppPos, "Best Opp!!!!!!!!!!", COLOR_WHITE);
}

CPlayerCommand* CAdvanceBallV3::execute(const CVisionModule* pVision) {
	if (subTask()) {
		return subTask()->execute(pVision);
	}
	if (_directCommand) {
		return _directCommand;
	}
	return 0;
}

bool CAdvanceBallV3::faceTheirGoal(const CVisionModule* pVision, const int executor) {
	double dist = Param::Field::PITCH_LENGTH / 2 - pVision->OurPlayer(executor).Pos().x();
	double buffer = 0;
	const CGeoPoint theirLeft = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2 - buffer);
	const CGeoPoint theirRight = CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2 + buffer);
	double leftAngle = Utils::Normalize((theirLeft - pVision->OurPlayer(executor).Pos()).dir());
	double rightAngle = Utils::Normalize((theirRight - pVision->OurPlayer(executor).Pos()).dir());
	double myDir = pVision->OurPlayer(executor).Dir();

	double rawLeftAngle = Utils::Normalize((theirLeft - pVision->OurPlayer(executor).Pos()).dir());
	double rawRifhtAngle = Utils::Normalize((theirRight - pVision->OurPlayer(executor).Pos()).dir());
	double myRawDir = pVision->OurPlayer(executor).Dir();

	bool isToTheirGoal = ((myDir > leftAngle) && (myDir < rightAngle));
	bool isRawToTheirGoal = ((myRawDir > rawLeftAngle) && (myRawDir < rawRifhtAngle));

	if (DEBUG_ENGINE) {
		GDebugEngine::Instance()->gui_debug_line(theirLeft, pVision->OurPlayer(executor).Pos());
		GDebugEngine::Instance()->gui_debug_line(theirRight, pVision->OurPlayer(executor).Pos());
		GDebugEngine::Instance()->gui_debug_line(pVision->OurPlayer(executor).Pos() + Utils::Polar2Vector(100, myDir), pVision->OurPlayer(executor).Pos());

		GDebugEngine::Instance()->gui_debug_line(theirLeft, pVision->OurPlayer(executor).Pos());
		GDebugEngine::Instance()->gui_debug_line(theirRight, pVision->OurPlayer(executor).Pos());
		GDebugEngine::Instance()->gui_debug_line(pVision->OurPlayer(executor).Pos() + Utils::Polar2Vector(100, myRawDir), pVision->OurPlayer(executor).Pos());
	}
	return (isToTheirGoal || isRawToTheirGoal);
}

int CAdvanceBallV3::getTheirMostClosetoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos) {
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

// todo
double CAdvanceBallV3::generateNormalPushDir(const CVisionModule* pVision, const int vecNumber) {
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	double faceDir = 0.0;
	if (!opp.Valid()) {
		KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
		faceDir = KickDirection::Instance()->getRealKickDir();
		return faceDir;
	}
	if (abs(ball.Pos().y()) < Param::Field::PITCH_WIDTH / 2 * 0.4 || me.Pos().x() < -50 || isOppFaceTheirDoor(pVision) || !checkBallFront(pVision, Param::Math::PI / 4.0)) {
		//cout << "there there there" << endl;
		KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
		faceDir = KickDirection::Instance()->getRealKickDir();
		return faceDir;
	}
	else if (abs(ball.Pos().y()) > Param::Field::PITCH_WIDTH / 2 * 0.70) {
		//cout << "here here here" << endl;
		faceDir = opp.Dir() + Param::Math::PI;
		return faceDir;
	}
	else {
		KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
		double kickDir = KickDirection::Instance()->getRealKickDir();
		double maxDir = Utils::Normalize(opp.Dir() + Param::Math::PI);
		double diffDir = Utils::Normalize(kickDir - maxDir);
		if (abs(diffDir) < Param::Math::PI / 15 || (kickDir > 0 && maxDir > kickDir) || (kickDir < 0 && maxDir < kickDir)) {
			return kickDir;
		}
		else {
			faceDir = Utils::Normalize(kickDir - diffDir * (3.33 * (abs(ball.Pos().y()) / (Param::Field::PITCH_WIDTH / 2)) - 1.33));
			return faceDir;
		}
	}
}

bool CAdvanceBallV3::meNearballThanOpp(const CVisionModule* pVision, const int vecNumber) {
	bool meNearBall = false;
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	double me2ballDist = (me.Pos() - ball.Pos()).mod();
	double opp2ballDist = (opp.Pos() - ball.Pos()).mod();
	if (opp2ballDist - me2ballDist > Param::Vehicle::V2::PLAYER_SIZE * 1.5) {
		meNearBall = true;
	}
	else {
		meNearBall = false;
	}
	return meNearBall;
}

bool CAdvanceBallV3::oppBetweenBallAndMe(const CVisionModule* pVision, const int vecNumber) {
	bool oppBetween = false;
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
	const BallVisionT& ball = pVision->Ball();
	CVector opp2ball = ball.Pos() - opp.Pos();
	CVector me2opp = opp.Pos() - me.Pos();
	if (abs(Utils::Normalize(opp2ball.dir() - me2opp.dir())) < Param::Math::PI / 3.0) {
		oppBetween = true;
	}
	else if (abs(Utils::Normalize(opp2ball.dir() - me2opp.dir())) < Param::Math::PI / 2.0 && me2opp.mod() < Param::Vehicle::V2::PLAYER_SIZE * 3) {
		oppBetween = true;
	}
	else {
		oppBetween = false;
	}
	return oppBetween;
}
//functions for judging passing
bool CAdvanceBallV3::tendToShoot(const CVisionModule* pVision, int vecNumber, int k_bottom) {
	/*const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);

	bool shootBlocked; //true被挡，挑射；false，没被挡，平射

	KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
	double kickDir = KickDirection::Instance()->getRealKickDir();
	CGeoLine ball2ourGoal =CGeoLine(me.Pos(), kickDir);
	CGeoPoint projectionPoint = ball2ourGoal.projection(opp.Pos());
	double ball2theirbest = (ball.Pos() - opp.Pos()).mod();
	double k_m = ball2theirbest / k_bottom;
	double opp2LineDist = (projectionPoint - opp.Pos()).mod();
	shootBlocked = opp2LineDist < k_m*Param::Vehicle::V2::PLAYER_SIZE ;*/

	int n = 0;
	int best_n = 0;
	//information of image
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const BallVisionT& ball = pVision->Ball();
	bool shootBlocked = false;
	KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
	double kickDir = KickDirection::Instance()->getRealKickDir();
	CGeoLine ball2ourGoal = /*CGeoLine(me.Pos(),ourGoal); */CGeoLine(me.Pos(), kickDir);
	CGeoPoint projectionPoint;
	double k_m = SHOOT_BLOCKED_RANGE;//ball2theirbest / 15;
	double opp2LineDist = 1000;
	while (n <= Param::Field::MAX_PLAYER) {
		if (!pVision->TheirPlayer(n).Valid()) { n++; continue; }
		projectionPoint = ball2ourGoal.projection(pVision->TheirPlayer(n).Pos());
		if (opp2LineDist > (projectionPoint - pVision->TheirPlayer(n).Pos()).mod() && projectionPoint.x() >= me.X()) {
			opp2LineDist = (projectionPoint - pVision->TheirPlayer(n).Pos()).mod();
			best_n = n;
			if (opp2LineDist < k_m * Param::Vehicle::V2::PLAYER_SIZE) {
				shootBlocked = true;
				break;
			}
		}
		n++;
	}
	KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
	bool kickValid = KickDirection::Instance()->getIsKickValid();
	const PlayerVisionT& opp = pVision->TheirPlayer(best_n);
	double me2theirbest = (me.Pos() - opp.Pos()).mod();
	double me2goal = (me.Pos() - theirCenter).mod();
	if (shootBlocked || me2goal > 600) {
		return false;
	}
	else {
		return kickValid;
	}
}

int CAdvanceBallV3::toChipOrToFlat(const CVisionModule* pVision, int vecNumber, int recNumber) {//参考isShootBlocked()
																												//判断如果平传会不会可能被挡住
	if (!(pVision->OurPlayer(recNumber).Valid())) {
		return 0;//not find the robot can be passed to
	}
	int n = 0;
	int best_n = 0;
	//information of image
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& ourTandem = pVision->OurPlayer(recNumber);
	const BallVisionT& ball = pVision->Ball();
	bool passBlocked = false;
	double passDir = (ourTandem.Pos() - me.Pos()).dir();//this is the simpliest  passing path
	CGeoLine ball2ourTandem = /*CGeoLine(me.Pos(),ourGoal); */CGeoLine(me.Pos(), passDir);
	CGeoPoint projectionPoint;
	double k_m = PASS_BLOCKED_RANGE;//ball2theirbest / 15;
	double opp2LineDist = 1000;
	while (n <= Param::Field::MAX_PLAYER) {
		if (!pVision->TheirPlayer(n).Valid()) { n++; continue; }
		projectionPoint = ball2ourTandem.projection(pVision->TheirPlayer(n).Pos());
		if (opp2LineDist > (projectionPoint - pVision->TheirPlayer(n).Pos()).mod()) {
			opp2LineDist = (projectionPoint - pVision->TheirPlayer(n).Pos()).mod();
			best_n = n;
			if (opp2LineDist < k_m * Param::Vehicle::V2::PLAYER_SIZE) {
				passBlocked = true;
				break;
			}
		}
		n++;
	}//to judge whether be blocked or not
	const PlayerVisionT& opp = pVision->TheirPlayer(best_n);
	double me2theirbest = (me.Pos() - opp.Pos()).mod();
	bool isPassOpp;//false means haven't passed
	//cout << "opp2LineDist:"<<opp2LineDist<<"  "<<"isPassOpp"<<isPassOpp<<endl;
	if (passBlocked) {
		return 1;//passing path be blocked
	}
	else {
		return 2;//passing path not be blocked
	}
}

bool CAdvanceBallV3::InPenaltyKick() {
	if (vision->GetCurrentRefereeMsg() == "ourPenaltyKick") return true;
	else return false;
}
