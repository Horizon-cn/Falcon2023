#include "Marking.h"
#include <skill/Factory.h>
#include "defenceNew/DefenceInfoNew.h"
#include "Vision/VisionModule.h"
#include "utils.h"
#include "GDebugEngine.h"
#include "geometry.h"
#include "WorldModel/WorldModel.h"
#include "defence/DefenceInfo.h"
#include "PointCalculation/MarkingPosV2.h"
#include <ssl/ParamManagerNew.h>

namespace {
	static bool FRIENDLY_MODE = false;//友好盯人
	static bool NOT_VOILENCE = false;//不采取暴力模式,优先级高于FRIENDLY_MODE

	const bool VERBOSE_MODE = false;

	CGeoPoint ourGoalPoint;       //我方球门

	const double simpleGotoDirLimt = Param::Math::PI * 150 / 180;
	const double enemyPredictTime = 3;											//敌人的位置预测
	const double simpleGotoStrictDirLimt = Param::Math::PI * 70 / 180;			//更加严厉的角度限制
	const double PATH_PLAN_CHANGE_DIST = 75;									//修改该值以获得更好的速度规划变动点!!!
	const double FRIENDLY_DIST_LIMIT = 10;										//友好模式 距离限制

	bool kickOffSide[Param::Field::MAX_PLAYER] = { false,false,false,false,false,false };

	const double kMarkingFrontMinDist = Param::Field::PITCH_WIDTH * 2 / 3;
	const CGeoPoint kOurGoal = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
	const double kEnemyReceiverOffsetThresholdIn = 25;
	const double kEnemyRecieverOffsetThresholdOut = 40;
}
CMarking::CMarking()
{
	ourGoalPoint = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
	enemyNum = 1;
	_lastCycle = 0;

	// 判断是否绕前截球使用的变量
	needToUpdateTheirKicker = true;
	isMeCloserToBall = false;
	isTheirKickerPosSafe = false;
	isBallToEnemy = false;
	deny_the_ball = false;

	// 从xml中读取盯人模式 0是友好模式，1是普通模式，2是暴力模式
	int MARKING_MODE = ParamManager::Instance()->MARKING_MODE;


	//////////////////////////////////////////////////////////////////////////
	//NOT_VOILENCE = false:暴力模式
	//NOT_VOILENCE = true,FRIENDLY_MODE = false：普通模式	
	//NOT_VOILENCE = true,FRIENDLY_MODE = true：友好模式
	//////////////////////////////////////////////////////////////////////////
	switch (MARKING_MODE) {
	case 0:  // 友好模式
		NOT_VOILENCE = true;
		FRIENDLY_MODE = true;
		break;
	case 1:  // 普通模式
		NOT_VOILENCE = true;
		FRIENDLY_MODE = false;
		break;
	case 2:  // 暴力模式
		NOT_VOILENCE = false;
		FRIENDLY_MODE = false;
		break;
	}
}

void CMarking::plan(const CVisionModule* pVision)
{
	//内部状态进行重置
	if (pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1)
	{
		setState(BEGINNING);
	}

	const BallVisionT& ball = pVision->Ball();
	int vecNumber = task().executor;                                 //我方小车
	int enemyNum = task().ball.Sender;                             //敌方
	bool front = task().ball.front;
	double markMethod = task().player.angle;
	CGeoPoint markPos = task().player.pos;

	//向worldModel中注册盯人信息，重要！！
	DefenceInfo::Instance()->setMarkList(pVision, vecNumber, enemyNum);

	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& enemy = pVision->TheirPlayer(enemyNum);
	CGeoPoint enemyPos = enemy.Pos();
	CGeoPoint mePos = me.Pos();
	CVector markPos2me = mePos - markPos;
	CVector markPos2ourGoal = ourGoalPoint - markPos;

	/****************************
	*      判断是否要绕前截球      *
	*	    By Soap 2015-4-27     *
	*****************************/
	//const PlayerVisionT* theirKicker = &pVision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	const PlayerVisionT* theirKicker = &pVision->TheirPlayer(DefenceInfo::Instance()->getSteadyAttackOppNumByPri(0));
	double ballToEnemyDir = (enemy.Pos() - ball.Pos()).dir();
	double meToBallDist = me.Pos().dist(ball.Pos());
	double enemyToBallDist = enemy.Pos().dist(ball.Pos());

	double theirKickerToBallDir = (ball.Pos() - theirKicker->Pos()).dir();
	double diffDirBetweenEnemyToBallAndEnemyOrientation = fabs(Utils::Normalize(theirKickerToBallDir - theirKicker->Dir()));
	bool isBallPassedByEnemy = diffDirBetweenEnemyToBallAndEnemyOrientation < Param::Math::PI * 75 / 180
		&& theirKicker->Pos().dist(ball.Pos()) > 15
		&& ball.Vel().mod() > 50;

	if (isBallPassedByEnemy == false) {

		if (isMeCloserToBall == true) {
			if (meToBallDist > enemyToBallDist + Param::Vehicle::V2::PLAYER_SIZE)
				isMeCloserToBall = false;
		} else {
			if (enemyToBallDist > meToBallDist + Param::Vehicle::V2::PLAYER_SIZE)
				isMeCloserToBall = true;
		}

		double penaltyLineX = -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH;
		if (theirKicker->Pos().x() < penaltyLineX) {
			isTheirKickerPosSafe = false;
		} else if (fabs(theirKicker->Pos().y() - enemy.Pos().y()) > kMarkingFrontMinDist) {
			if (isTheirKickerPosSafe == true) {
				if (enemy.Pos().dist(kOurGoal) < Param::Field::PENALTY_AREA_WIDTH / 2 + Param::Field::MAX_PLAYER_SIZE * 2.5)
					isTheirKickerPosSafe = false;
			} else {
				if (enemy.Pos().dist(kOurGoal) > Param::Field::PENALTY_AREA_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE * 3.5)
					isTheirKickerPosSafe = true;
			}
		} else {
			isTheirKickerPosSafe = false;
		}

		bool isAbleToGetBall = false;
		if (isMeCloserToBall == true && enemyToBallDist > Param::Field::MAX_PLAYER_SIZE * 4)
			isAbleToGetBall = true;

		if (deny_the_ball == false) {
			if (isTheirKickerPosSafe == true && isAbleToGetBall == true)
				deny_the_ball = true;
			else if (ball.Pos().x() > 0)
				deny_the_ball = true;
		}
	} else {

		double diffDir = fabs(Utils::Normalize(ballToEnemyDir - ball.Vel().dir()));
		double offsetDist = enemyToBallDist * tan(diffDir);

		/*
		if (deny_the_ball == true) {
			if (isBallToEnemy == false) {
				if (diffDir < Param::Math::PI / 24)
					isBallToEnemy = true;
			} else {
				if (diffDir > Param::Math::PI / 12)
					isBallToEnemy = false;
			}
		}
		*/

		if (deny_the_ball == true) {
			if (isBallToEnemy == false) {
				if (offsetDist < kEnemyReceiverOffsetThresholdIn)
					isBallToEnemy = true;
			} else {
				if (offsetDist > kEnemyRecieverOffsetThresholdOut)
					isBallToEnemy = false;
			}
		}

		//cout << pVision->Cycle() << " - deny_the_ball: " << deny_the_ball << endl;
		deny_the_ball = isBallToEnemy;
	}

	double me2ballDir = CVector(ball.Pos() - mePos).dir();
	double me2theirGoalDir = CVector(CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, 0) - mePos).dir();
	TaskT MarkingTask(task());
	//避禁区
	MarkingTask.player.flag |= PlayerStatus::DODGE_OUR_DEFENSE_BOX;
	//定位球避开开球50cm区域
	const string refMsg = WorldModel::Instance()->CurrentRefereeMsg();
	if ("theirIndirectKick" == refMsg || "theirDirectKick" == refMsg || "theirKickOff" == refMsg || "gameStop" == refMsg)
	{
		MarkingTask.player.flag |= PlayerStatus::DODGE_REFEREE_AREA;
	}

	//路径规划设置
	if (me.Pos().dist(markPos) < PATH_PLAN_CHANGE_DIST)
	{
		//采用CMU的轨迹规划
		MarkingTask.player.is_specify_ctrl_method = true;
		MarkingTask.player.specified_ctrl_method = CMU_TRAJ;
	}

	//横向被甩开补充
	CVector opp2ourGoalVector = CVector(ourGoalPoint - enemyPos);
	CVector oppVel = enemy.Vel();
	double angle_oppVel_opp2Goal = fabs(Utils::Normalize(opp2ourGoalVector.dir() - oppVel.dir()));
	double sinPre = std::sin(angle_oppVel_opp2Goal);
	double cosPre = std::cos(angle_oppVel_opp2Goal);
	double dist = fabs(pVision->TheirPlayer(enemyNum).Y() - mePos.y());
	//cout<<sinPre<<" "<<oppVel.mod()<<" "<<dist<<endl;

	//避障设置
	CVector enemyPos2me = mePos - enemyPos;
	CVector enemyPos2ourGoal = ourGoalPoint - enemyPos;
	bool friendlyAngleOK = fabs(Utils::Normalize(enemyPos2ourGoal.dir() - enemyPos2me.dir())) < simpleGotoDirLimt;
	bool friendlyLimit = true;
	if (FRIENDLY_MODE && NOT_VOILENCE)
	{
		friendlyLimit = fabs(Utils::Normalize(enemyPos2ourGoal.dir() - enemyPos2me.dir())) < simpleGotoStrictDirLimt;
	}
	if (sinPre > 0.8 && oppVel.mod() > 40) {
		GDebugEngine::Instance()->gui_debug_msg(markPos, "M", COLOR_PURPLE);
		double ratio = 0;
		double absvel = fabs(enemy.Vel().y());
		if (absvel > 120) {
			ratio = 1;
		} else if (absvel > 80 && absvel <= 120) {
			ratio = 0.025 * absvel - 2;
		} else {
			ratio = 0;
		}

		double shiftDist = ratio * oppVel.y();
		if (shiftDist < -100) {
			shiftDist = -100;
		}
		if (shiftDist > 100) {
			shiftDist = 100;
		}
		//shiftDist = 0;
		markPos = markPos + Utils::Polar2Vector(shiftDist, Param::Math::PI / 2);

	}

	//对方朝着盯人车
	CGeoSegment enemySeg = CGeoSegment(enemyPos, enemyPos + Utils::Polar2Vector(500, enemy.Vel().dir()));
	CGeoPoint meProj = enemySeg.projection(mePos);
	if (enemy.Vel().mod() > 80) {
		if (enemySeg.IsPointOnLineOnSegment(meProj) && meProj.dist(mePos) < 45 && mePos.dist(enemyPos) > 60) {
			markPos = mePos;
			GDebugEngine::Instance()->gui_debug_line(enemyPos, enemyPos + Utils::Polar2Vector(500, enemy.Vel().dir()), COLOR_WHITE);
		}
	}

	if (Utils::OutOfField(markPos, 0)) {
		markPos = Utils::MakeInField(markPos, 20);
	}
	//GDebugEngine::Instance()->gui_debug_msg(markPos,"M",COLOR_YELLOW);
	MarkingTask.player.pos = markPos;
	MarkingTask.player.angle = CVector(CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, 0) - me.Pos()).dir();
	//MarkingTask.player.angle = 0;
	//GDebugEngine::Instance()->gui_debug_line(mePos,mePos+Utils::Polar2Vector(500,MarkingTask.player.angle),COLOR_WHITE);
	MarkingTask.player.max_acceleration = 650;
	MarkingTask.player.is_specify_ctrl_method = true;
	MarkingTask.player.specified_ctrl_method = CMU_TRAJ;
	//当是角球区域，盯人车对着球
	if (("theirIndirectKick" == refMsg || "theirDirectKick" == refMsg || "gameStop" == refMsg) && pVision->Ball().X() < 0) {
		//cout<<"markingCorner"<<endl;
		MarkingTask.player.angle = me2ballDir;
	}
	if (DefenceInfo::Instance()->getOppPlayerByNum(enemyNum)->isTheRole("RReceiver"))
	{
		MarkingTask.player.max_acceleration = 1000;
		MarkingTask.player.is_specify_ctrl_method = true;
		MarkingTask.player.specified_ctrl_method = CMU_TRAJ;
		if (true == NameSpaceMarkingPosV2::DENY_LOG[enemyNum] && fabs(Utils::Normalize(me2ballDir - me2theirGoalDir)) < Param::Math::PI * 60 / 180)
		{
			MarkingTask.player.angle = me2theirGoalDir;
			markMethod = me2theirGoalDir;
		}
	}
	bool checkKickOffArea = false;
	if ("theirIndirectKick" == refMsg || "theirDirectKick" == refMsg) {
		if (pVision->Ball().Y() > 0) {
			kickOffSide[vecNumber] = false;
		} else {
			kickOffSide[vecNumber] = true;
		}
	}
	if (kickOffSide[vecNumber] == false) {
		CGeoPoint leftUp = CGeoPoint(Param::Field::PITCH_LENGTH / 2, 30 + 20);
		CGeoPoint rightDown = CGeoPoint(80, Param::Field::PITCH_WIDTH / 2);
		if (DefenceInfo::Instance()->checkInRecArea(enemyNum, pVision, MarkField(leftUp, rightDown))) {
			checkKickOffArea = true;
		}
	} else if (kickOffSide[vecNumber] == true) {
		CGeoPoint leftUp = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::PITCH_WIDTH / 2);
		CGeoPoint rightDown = CGeoPoint(80, -30 - 20);
		if (DefenceInfo::Instance()->checkInRecArea(enemyNum, pVision, MarkField(leftUp, rightDown))) {
			checkKickOffArea = true;
		}
	}
	if (markMethod < 100)
	{
		//cout<<"toBall"<<endl;
		MarkingTask.player.angle = markMethod;
	}

	if (deny_the_ball == true && front == true)
	{
		//MarkingTask.player.flag |= PlayerStatus::NOT_AVOID_THEIR_VEHICLE;
		//cout<<MarkingTask.player.flag<<endl;
		DefenceInfo::Instance()->setMarkMode(vecNumber, enemyNum, true);
		setSubTask(PlayerRole::makeItMarkingFront(vecNumber, enemyNum, MarkingTask.player.angle, MarkingTask.player.flag));
		//cout<< pVision->Cycle() <<" front Mode" << endl;
	} else if ((friendlyAngleOK && friendlyLimit) || !NOT_VOILENCE)
	{
		//不避开对手车
//		MarkingTask.player.flag |= PlayerStatus::NOT_AVOID_THEIR_VEHICLE;
		DefenceInfo::Instance()->setMarkMode(vecNumber, enemyNum, false);
		//cout<<MarkingTask.player.flag<<endl;
		setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(MarkingTask));
	} else {
		//cout<<MarkingTask.player.flag<<endl;
		if (ball.Pos().x() < -300) {
			//			MarkingTask.player.flag |= PlayerStatus::NOT_AVOID_THEIR_VEHICLE;
		}
		DefenceInfo::Instance()->setMarkMode(vecNumber, enemyNum, false);
		setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(MarkingTask));
	}
	// if (MarkingTask.player.flag & PlayerStatus::ALLOW_DSS)
		// cout << "This is DSS!" << endl;
	GDebugEngine::Instance()->gui_debug_msg(MarkingTask.player.pos, "M", COLOR_WHITE);
	//cout<<enemyNum<<": "<<pVision->TheirPlayer(enemyNum).Vel().mod()<<" "<<vecNumber<<endl;
	_lastCycle = pVision->Cycle();
	CStatedTask::plan(pVision);
}


CPlayerCommand* CMarking::execute(const CVisionModule* pVision)
{
	if (subTask()) {
		return subTask()->execute(pVision);
	}
	return NULL;
}

