#include "Goalie2022.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "skill/Factory.h"
#include <utils.h>
#include <WorldModel/DribbleStatus.h>
#include <RobotSensor.h>
#include "param.h"
#include "BallSpeedModel.h"
#include "WorldModel/WorldModel.h"
#include <TaskMediator.h>
#include "defenceNew/DefenceInfoNew.h"
#include <random>

#define DEBUG_EVALUATE(x) {if(goalie_debug) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,-300), x);}

namespace {
	bool goalie_debug,is_penalty;
	const CGeoPoint goalCenter(-Param::Field::PITCH_LENGTH / 2, 0);
	const CGeoPoint RLeftGoalPost(-Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2);
	const CGeoPoint RRightGoalPost(-Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2);
	CGeoLine BaseLine(RLeftGoalPost, RRightGoalPost);
	CGeoLine moveLine(goalCenter + CVector(Param::Field::PENALTY_AREA_DEPTH / 4.0, 0), Param::Math::PI / 2);
	const double PENALTY_BUFFER = 0.1 * Param::Field::PENALTY_AREA_DEPTH;
	double SLOW_BALL_SPD;
	int KICKPOWER;
	double HAVE_BALL_DIST;
	double CLOSE_DIST;
	bool AGGRESSIVE_GOALIE;
	double CHALLENGE_BALL_DIST;
	double BLOCK_DIST;
}

CGoalie2022::CGoalie2022() :this_shoot_cycle(0), rescuePoint(goalCenter)
{
	goalie_debug = paramManager->GOALIE_DEBUG;
	SLOW_BALL_SPD = paramManager->SLOW_BALL_SPD;
	KICKPOWER = paramManager->KICKPOWER_GOALIE;
	HAVE_BALL_DIST = paramManager->HAVE_BALL_DIST;
	CLOSE_DIST = paramManager->CLOSE_DIST;
	AGGRESSIVE_GOALIE = paramManager->AGGRESSIVE_GOALIE;
	CHALLENGE_BALL_DIST = paramManager->CHALLENGE_BALL_DIST;
	BLOCK_DIST = paramManager->BLOCK_DIST;
}

void CGoalie2022::plan(const CVisionModule* pVision)
{
	is_penalty = task().player.isPenalty;
	int purpose = evaluate(pVision);
	CPlayerTask* pTask;
	switch (purpose) {
	case TEST:
		break;
	case NORMAL:
		if (is_penalty)
			pTask = penaltyTask(pVision);
		else
			pTask = normalTask(pVision);
		break;
	case RESCUE:
		pTask = rescueTask(pVision);
		break;
	case SUPPORT:
		pTask = supportTask(pVision);
		break;
	case CLEAR_BALL:
		pTask = clearBallTask(pVision);
		break;
	case ATTACK_ENEMY:
		pTask = attackEnemyTask(pVision);
		break;
	}
	setSubTask(pTask);
	CStatedTask::plan(pVision);
}

CPlayerCommand* CGoalie2022::execute(const CVisionModule* pVision)
{
	if (subTask())
	{
		return subTask()->execute(pVision);
	}
	return NULL;
}

int CGoalie2022::evaluate(const CVisionModule* pVision)
{
	int robotNum = task().executor;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const PlayerVisionT& enemy = pVision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	const BallVisionT& ball = pVision->Ball();

	if (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop") {
		DEBUG_EVALUATE("evaluate: game stop");
		return NORMAL;
	} else if (!ball.Valid()) {
		DEBUG_EVALUATE("evaluate: invalid ball");
		return NORMAL;
	} else if (IsFarFromBack(ball.Pos())) {
		DEBUG_EVALUATE("evaluate: far ball");
		return NORMAL;
	} else if (ShouldAttack(pVision)) {
		DEBUG_EVALUATE("evaluate: danger, attack enemy");
		return ATTACK_ENEMY;
	} else if (ball.Vel().mod() > SLOW_BALL_SPD) {
		if (isBallShot2Goal(pVision)) {
			DEBUG_EVALUATE("evaluate: fast ball, to goal, emergency");
			return RESCUE;
		} else {
			DEBUG_EVALUATE("evaluate: fast ball, not to goal");
			return NORMAL;
		}
	} else if (Utils::InOurPenaltyArea(ball.Pos(), PENALTY_BUFFER)) {
		if (enemy.Pos().dist(ball.Pos()) < HAVE_BALL_DIST) {
			DEBUG_EVALUATE("evaluate: slow ball, enemy inside, clear ball");
			return CLEAR_BALL;
		} else {
			DEBUG_EVALUATE("evaluate: slow ball, safe to support");
			return SUPPORT;
		}
	} else {
		DEBUG_EVALUATE("evaluate: normal");
		return NORMAL;
	}
}

bool CGoalie2022::isBallShot2Goal(const CVisionModule* pVision)
{
	const BallVisionT& Ball = pVision->Ball();
	if (Ball.VelX() >= 0)
		return false;
	CGeoLine BallVelLine(Ball.Pos(), Ball.Vel().dir());
	CGeoLineLineIntersection interseciton(BaseLine, BallVelLine);
	if (interseciton.Intersectant() == true) {
		CGeoPoint point = interseciton.IntersectPoint();
		if (fabs(point.y()) < Param::Field::PENALTY_AREA_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE)
			return true;
	}
	return false;
}

bool CGoalie2022::ShouldAttack(const CVisionModule* pVision)
{
	/************************************************************************/
	/* 若对面在靠中前的位置打算单刀，且我方后卫支援困难，这种时候就要主动出击。
	   同时，主动出击风险较大，因此用return false添加限制逻辑为主  by SYLG */
	   /************************************************************************/
	if (!AGGRESSIVE_GOALIE)
		return false;
	if (is_penalty)
		return false;
	int robotNum = task().executor;
	const PlayerVisionT& enemy = pVision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	const BallVisionT& ball = pVision->Ball();

	if (abs(enemy.Pos().y()) > Param::Field::PENALTY_AREA_WIDTH / 2.0 + 30
		|| enemy.Pos().dist(ball.Pos()) > CLOSE_DIST)
		return false;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
	{
		if (robotNum != i)
		{
			const PlayerVisionT& helper_i = pVision->OurPlayer(i);
			if (!helper_i.Valid())
				continue;
			if (helper_i.Pos().dist(enemy.Pos()) < CLOSE_DIST
				|| helper_i.Pos().dist(ball.Pos()) < CLOSE_DIST)//已经有帮手了
				return false;
		}
	}
	//现行防守框架下，有后卫则无需支援
	if (TaskMediator::Instance()->leftBack() || TaskMediator::Instance()->rightBack() || TaskMediator::Instance()->singleBack())
		return false;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (TaskMediator::Instance()->isMultiBack(i))
			return false;
	}
	//综合判断敌我形势。目前这一段还比较粗糙 by SYLG
	int free_enemy = 0;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
	{
		const PlayerVisionT& enemy_i = pVision->TheirPlayer(i);
		if (IsFarFromBack(enemy_i.Pos()) == false)
		{
			free_enemy++;
			for (int j = 0; j < Param::Field::MAX_PLAYER; j++)
			{
				if (pVision->OurPlayer(j).Pos().dist(enemy_i.Pos()) < CLOSE_DIST)
				{
					free_enemy--;
					break;
				}
			}
		}
	}
	return free_enemy <= 1;
}

inline bool CGoalie2022::IsFarFromBack(const CGeoPoint& pos, int x)
{
	return pos.x() > x;
}

CPlayerTask* CGoalie2022::normalTask(const CVisionModule* pVision)
{
	int robotNum = task().executor;

	//CGeoPoint DefPoint = DefPos2015::Instance()->getDefPos2015(pVision).getGoaliePos();
	CGeoPoint DefPoint;
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& enemy = pVision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	CGeoPoint defenceTarget = ball.Valid() ? ball.Pos() : enemy.Pos();
	CGeoLine defenceLine(defenceTarget, goalCenter);
	CGeoLineLineIntersection intersect(defenceLine, moveLine);
	if (!intersect.Intersectant())
		DefPoint = goalCenter;
	else
		DefPoint = intersect.IntersectPoint();
	double limit_y = Param::Field::GOAL_WIDTH / 2.0 - 5.0;
	if (fabs(DefPoint.y()) > limit_y)
		DefPoint.setY(DefPoint.y() / fabs(DefPoint.y()) * limit_y);

	double dir;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	if (ball.Valid()) {
		dir = CVector(ball.Pos() - me.Pos()).dir();
	} else {
		dir = CVector(me.Pos() - goalCenter).dir();
	}

	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;

	return PlayerRole::makeItGoto(robotNum, DefPoint, dir, flag);
}

CPlayerTask* CGoalie2022::rescueTask(const CVisionModule* pVision)
{
	/************************************************************************/
	/* 扑球时，若假设球和人匀速，则需要在球速线上找点P，使得P到人近，到球远（比值尽量小）
	   容易发现，P-人-球为直角。同时，若这个点是人恰好扑到球的点，在扑球过程中点的生成是稳定的
	   但是，现实中，守门员需要加速，而速度如果一开始慢的话会导致生成点的位置改变（后移），继而导致守门员变向、加速不及时
	   因此，维护敌方射门的简单状态机，仅在射门开始的时候计算扑球点 by SYLG */
	   /************************************************************************/
	//能挡住球的前提下一次射门仅计算一次点位
	const BallVisionT& ball = pVision->Ball();
	CGeoLine ballVelLine(ball.Pos(), ball.Vel().dir());
	CGeoPoint projection = ballVelLine.projection(rescuePoint);
	if (projection.dist(rescuePoint) > 10 || pVision->Cycle() - this_shoot_cycle > 100)
		generateRescuePoint(pVision);
	this_shoot_cycle = pVision->Cycle();
	GDebugEngine::Instance()->gui_debug_msg(rescuePoint, "r", COLOR_BLUE);

	int robotNum = task().executor;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);

	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;
	flag |= PlayerStatus::DRIBBLING;

	return PlayerRole::makeItGoto(robotNum, rescuePoint, me.Dir(), flag);
}
//struct PassDirOrPos {
//	double dir;
//	CGeoPoint pos;
//};
//PassDirOrPos PassDirInside(const CVisionModule* pVision, int vecNumber) {
//	PassDirOrPos ReturnValue;
//	/*判断SupportPoint点位是否可以使用*/
//	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
//	bool isOurNearPoint[9] = { 0 }/*, isBlockPoint[9] = { 0 }*/, isCanUse[9] = { 0 }, OneOfUsCanShoot = 0;
//	int TheNumberOfCanShootPoint = 0, NowShootNumber = 0, TheidxOfCanShootPoint[9] = { 0 };
//	double ShootDir[9] = { 0 }, ChangeDir[9] = { 0 }, DistToPoint[9] = { 0 }, DistOppToTheLine[9] = { 0 };
//	double FinalDir = 0;
//	/*依次为：我是否有人在传球点附近，敌人是否阻挡该传球路径，该点能否使用，我们有没有点满足要求，能够shoot的点的idx*/
//	/*依次为：满足要求的点的数量TheNumberOfCanShootPoint，持久化点的number，shootdir，需要转变方向的Dir，最终角度Dir*/
//	for (int i = 0; i < NumberOfSupport; ++i) {
//		isOurNearPoint[i] = IsOurNearHere(pVision, SupportPoint[i], vecNumber);
//		//isBlockPoint[i] = isTheLineBlocked(pVision, me.Pos(), SupportPoint[i]);
//		DistOppToTheLine[i] = TheMinDistBetweenTheOppAndTheLine(pVision, me.Pos(), SupportPoint[i]);
//		ShootDir[i] = KickDirection::Instance()->getPointShootDir(pVision, SupportPoint[i]);
//		DistToPoint[i] = (SupportPoint[i] - me.Pos()).mod();
//		ChangeDir[i] = me.Dir() - (SupportPoint[i] - me.Pos()).dir();
//		isCanUse[i] = isOurNearPoint[i] && /*(!isBlockPoint[i]) &&*/ (ShootDir[i] != 1000) && (SupportPoint[i].x() > me.X());
//		/*当前点可以射门的条件：我方有人在旁边，没有阻挡，射门可以*/
//		if (isCanUse[i])OneOfUsCanShoot = 1;
//	}
//	ReturnValue.dir = (SupportPoint[LastPassPoint] - me.Pos()).dir();
//	ReturnValue.pos = SupportPoint[LastPassPoint];
//	if (SupportPoint[LastPassPoint].x() > me.X() && isOurNearPoint[LastPassPoint] && (abs(me.Dir() - (SupportPoint[LastPassPoint] - me.Pos()).dir()) < 0.5 * Param::Math::PI / SHOOT_PRECISION)) {
//		return ReturnValue;
//	}
//	/*保持系统稳定性 */
//
//	if (OneOfUsCanShoot) {
//		/*如果其中有一个满足大前提，就只考虑这些可以满足要求的点*/
//		IsMeSupport = JudgeIsMeSupport(pVision, vecNumber);
//		if (IsMeSupport) {
//			if (isCanUse[1]) {
//				ReturnValue.dir = (SupportPoint[1] - me.Pos()).dir();
//				ReturnValue.pos = SupportPoint[1];
//				return ReturnValue;
//			}
//			if (isCanUse[4]) {
//				ReturnValue.dir = (SupportPoint[4] - me.Pos()).dir();
//				ReturnValue.pos = SupportPoint[4];
//				return ReturnValue;
//			}
//		}
//		for (int i = 0; i < NumberOfSupport; ++i)
//			if (isCanUse[i] && SupportPoint[i].x() > -330)TheidxOfCanShootPoint[TheNumberOfCanShootPoint++] = i;
//	} else {
//		/*否则就有人的地方全都可以传 因为现在已经在决定传球方向了*/
//		IsMeSupport = JudgeIsMeSupport(pVision, vecNumber);
//		if (IsMeSupport) {
//			if (isOurNearPoint[1]) {
//				ReturnValue.dir = (SupportPoint[1] - me.Pos()).dir();
//				ReturnValue.pos = SupportPoint[1];
//				return ReturnValue;
//			}
//			if (isOurNearPoint[4]) {
//				ReturnValue.dir = (SupportPoint[4] - me.Pos()).dir();
//				ReturnValue.pos = SupportPoint[4];
//				return ReturnValue;
//			}
//		}
//		for (int i = 0; i < NumberOfSupport; ++i)
//			if (isOurNearPoint[i] && SupportPoint[i].x() > -330)TheidxOfCanShootPoint[TheNumberOfCanShootPoint++] = i;
//	}
//	double NowValue = -1, MinValue = 1e9; int Maxidx = -1;
//	for (int i = 0; i < TheNumberOfCanShootPoint; ++i) {
//		int NowIdx = TheidxOfCanShootPoint[i];
//		NowValue = ChangeDir[NowIdx];
//		if (NowValue < MinValue)Maxidx = NowIdx, MinValue = NowValue;
//	}
//	if (Maxidx < 0)Maxidx = 1;
//	NowShootNumber = Maxidx;
//	ReturnValue.dir = (SupportPoint[NowShootNumber] - me.Pos()).dir();
//	ReturnValue.pos = SupportPoint[NowShootNumber];
//	LastPassPoint = NowShootNumber;
//	return ReturnValue;
//}
CPlayerTask* CGoalie2022::supportTask(const CVisionModule* pVision)
{
	int robotNum = task().executor;
	int leaderNum = BestPlayer::Instance()->getOurBestPlayer();

	if (robotNum == leaderNum) {//实际情况下不太可能出现
		return clearBallTask(pVision);
	}

	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const PlayerVisionT& leader = pVision->OurPlayer(leaderNum);

	double dir = CVector(leader.Pos() - me.Pos()).dir();

	//中国赛临时支援策略
	dir = CVector(CGeoPoint(400, 0) - me.Pos()).dir();

	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;
	flag |= PlayerStatus::DRIBBLING;

	double power = 500;
	KickStatus::Instance()->setChipKick(robotNum, power);
	return PlayerRole::makeItNoneTrajGetBall(robotNum, dir, CVector(0, 0), flag);
}

CPlayerTask* CGoalie2022::clearBallTask(const CVisionModule* pVision)
{
	//防乌龙还没写进来

	const BallVisionT& ball = pVision->Ball();
	int robotNum = task().executor;

	double dir = CalClearBallDir(pVision);

	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;
	flag |= PlayerStatus::DRIBBLING;

	return PlayerRole::makeItGoto(robotNum, ball.Pos(), dir, flag);//todo need test
	//return PlayerRole::makeItNoneTrajGetBall(robotNum, dir, CVector(0, 0), flag);
	//拿到球后通过lua层面检测会自己踢出去
}

CPlayerTask* CGoalie2022::attackEnemyTask(const CVisionModule* pVision)
{
	int robotNum = task().executor;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const PlayerVisionT& enemy = pVision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	const BallVisionT& ball = pVision->Ball();

	//距敌人过近时会因路径不可达而跑歪，此时直接抢球即可
	CGeoPoint pos;
	if (me.Pos().dist(enemy.Pos()) > CHALLENGE_BALL_DIST) {
		pos = enemy.Pos();
	} else {
		pos = ball.Pos();
	}

	double dir;
	if (ball.Valid()) {
		dir = CVector(ball.Pos() - me.Pos()).dir();
	} else {
		dir = CVector(me.Pos() - goalCenter).dir();
	}

	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;
	flag |= PlayerStatus::DRIBBLING;

	return PlayerRole::makeItGoto(robotNum, pos, dir, flag);
}

CPlayerTask* CGoalie2022::penaltyTask(const CVisionModule* pVision)
{
	CGeoPoint defCenter;//防守中心，影响随机点的分布
	const PlayerVisionT& enemy = pVision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	CGeoLine defLine(enemy.Pos(), enemy.Dir());
	if (fabs(enemy.Dir()) <= Param::Math::PI / 2)
		defLine = CGeoLine(enemy.Pos(), goalCenter);
	CGeoLineLineIntersection intersect(defLine, BaseLine);
	if (intersect.Intersectant())
		defCenter = intersect.IntersectPoint();
	else
		defCenter = goalCenter;

	int random_num = 5;
	double random_start = -0.3;
	double random_end = 0.3;
	double random_step = (random_end - random_start) / double(random_num - 1);
	double random_current = random_start - random_step;

	vector<CGeoPoint> random_points(random_num);
	generate(random_points.begin(), random_points.end(), //generate points between [begin,end]
		[&]() {
		random_current += random_step;
		return CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH / 6, random_current * Param::Field::GOAL_WIDTH); });
	if (goalie_debug)
		for (auto& p : random_points)
			GDebugEngine::Instance()->gui_debug_x(p, COLOR_GREEN);
	default_random_engine generator{ (unsigned int)pVision->Cycle() };
	vector<int> weight_vector;
	weight_vector.reserve(random_num);
	for (auto& p : random_points)
		weight_vector.push_back(100000 / sqrt(defCenter.dist(p)) / std::log10(30 + p.dist(goalCenter)));
	discrete_distribution<int> weight(weight_vector.begin(), weight_vector.end());
	//固定间隔帧数进行随机生成
	static int generate_index = weight(generator);
	static int interval_cnt = 0;
	const int generate_interval = 5;
	interval_cnt++;
	if (interval_cnt > generate_interval)
	{
		interval_cnt = 0;
		generate_index = weight(generator);
	}
	int robotNum = task().executor;

	double dir;
	CGeoPoint finalPos = random_points[generate_index];
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const BallVisionT& ball = pVision->Ball();
	//if (ball.Valid()) {
	//	dir = CVector(ball.Pos() - me.Pos()).dir();
	//} else {
	//	dir = CVector(me.Pos() - goalCenter).dir();
	//}
	dir = 0;

	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;

	return PlayerRole::makeItGoto(robotNum, finalPos, dir, flag);
}

void CGoalie2022::generateRescuePoint(const CVisionModule* pVision)
{
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(task().executor);
	CGeoLine ballVelLine(ball.Pos(), ball.Vel().dir());
	CVector ball2me(ball.Pos() - me.Pos());
	CGeoLine me_vertical2_me2ballLine(me.Pos(), ball2me.dir() + Param::Math::PI / 2);
	CGeoLineLineIntersection intersect(ballVelLine, me_vertical2_me2ballLine);
	if (intersect.Intersectant() && Utils::InOurPenaltyArea(intersect.IntersectPoint(), 0))
		rescuePoint = intersect.IntersectPoint();
	else
	{
		intersect = CGeoLineLineIntersection(ballVelLine, moveLine);
		if (!intersect.Intersectant())
			rescuePoint = goalCenter;
		else
			rescuePoint = intersect.IntersectPoint();
		double limit_y = Param::Field::GOAL_WIDTH / 2.0 - 5.0;
		if (fabs(rescuePoint.y()) > limit_y)
			rescuePoint.setY(rescuePoint.y() / fabs(rescuePoint.y()) * limit_y);
	}
}

double CGoalie2022::CalClearBallDir(const CVisionModule* pVision)
{
	/************************************************************************/
	/* 清球角度的计算。目前战术安排均采用双后卫即leftBack+rightBack策略，
	   因此仅重写相关部分的逻辑，单后卫的代码继承于Goalie2013
	   且在目前规则与代码框架下，理论上不需要此部分代码，仅作为留档保留于此 by SYLG */
	   /************************************************************************/
	int robotNum = task().executor;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& enemy = pVision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	double clearBallDir = 0;
	if (TaskMediator::Instance()->singleBack() == 0 && TaskMediator::Instance()->leftBack() != 0) {
		CGeoPoint leftpos = DefPos2015::Instance()->getDefPos2015(pVision).getLeftPos();
		CGeoPoint rightpos = DefPos2015::Instance()->getDefPos2015(pVision).getRightPos();
		double ball2leftDir = (DefPos2015::Instance()->getDefPos2015(pVision).getLeftPos() - ball.Pos()).dir();// -0.3;
		double ball2rightDir = (DefPos2015::Instance()->getDefPos2015(pVision).getRightPos() - ball.Pos()).dir();// +0.3;
		double goal2ballDir = CVector(ball.Pos() - goalCenter).dir();
		GDebugEngine::Instance()->gui_debug_line(ball.Pos(), ball.Pos() + Utils::Polar2Vector(200, ball2leftDir), COLOR_BLACK);
		GDebugEngine::Instance()->gui_debug_line(ball.Pos(), ball.Pos() + Utils::Polar2Vector(200, ball2rightDir), COLOR_BLACK);
		if (goal2ballDir > ball2leftDir && goal2ballDir < ball2rightDir)
		{
			if (ball2rightDir - ball2leftDir > Param::Math::PI / 2) {
				clearBallDir = Utils::Normalize((ball2leftDir + ball2rightDir) / 2);
			} else {
				vector<double> blockDirList{ -Param::Math::PI,Param::Math::PI };
				for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
				{
					CGeoPoint pos = pVision->OurPlayer(i).Pos();
					if (pos.dist(ball.Pos()) < BLOCK_DIST && i != robotNum)
						blockDirList.push_back((pos - ball.Pos()).dir());
					pos = pVision->TheirPlayer(i).Pos();
					if (pos.dist(ball.Pos()) < BLOCK_DIST)
						blockDirList.push_back((pos - ball.Pos()).dir());
				}
				sort(blockDirList.begin(), blockDirList.end());
				double maxAngle = 0;
				for (int i = 0; i < blockDirList.size() - 1; i++)
					if (blockDirList[i + 1] - blockDirList[i] > maxAngle) {
						maxAngle = blockDirList[i + 1] - blockDirList[i];
						clearBallDir = (blockDirList[i + 1] + blockDirList[i]) / 2.0;
					}
			}
		} else {
			clearBallDir = Utils::Normalize(goal2ballDir);
		}
	} else if (TaskMediator::Instance()->singleBack() != 0) {
		double goal2singledir = (DefPos2015::Instance()->getDefPos2015(pVision).getSinglePos() - ball.Pos()).dir();
		if (std::abs(goal2singledir - clearBallDir) < Param::Math::PI / 18) {
			if (std::abs(clearBallDir) > Param::Math::PI / 10) {
				clearBallDir = -clearBallDir;
				if (std::abs(clearBallDir) > Param::Math::PI * 70 / 180) {
					if (clearBallDir < 0) {
						clearBallDir = clearBallDir + Param::Math::PI / 9;
					} else {
						clearBallDir = clearBallDir - Param::Math::PI / 9;
					}
				}
			} else {
				clearBallDir = clearBallDir + Param::Math::PI * 7 / 18;
			}
		}
	} else {
		clearBallDir = CVector(ball.Pos() - goalCenter).dir();
	}

	//太近了还是直接用原始方向比较稳妥
	if (enemy.Pos().dist(ball.Pos()) < CLOSE_DIST) {
		clearBallDir = CVector(ball.Pos() - goalCenter).dir();
	}

	//角度限制
	if (clearBallDir >= Param::Math::PI * 80 / 180.0) {
		clearBallDir = Param::Math::PI * 80 / 180.0;
	} else if (clearBallDir <= -Param::Math::PI * 80 / 180.0) {
		clearBallDir = -Param::Math::PI * 80 / 180.0;
	}

	GDebugEngine::Instance()->gui_debug_line(ball.Pos(), ball.Pos() + Utils::Polar2Vector(600, clearBallDir), COLOR_BLUE);
	return clearBallDir;
}
