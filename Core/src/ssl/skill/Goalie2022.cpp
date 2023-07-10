#include "Goalie2022.h"
#include <random>

#include "GDebugEngine.h"
#include "Vision/VisionModule.h"
#include "skill/Factory.h"
#include "utils.h"
#include "WorldModel/DribbleStatus.h"
#include "RobotSensor.h"
#include "param.h"
#include "WorldModel/WorldModel.h"
#include "TaskMediator.h"
#include "defenceNew/DefenceInfoNew.h"
#include "gpuBestAlgThread.h"

#define DEBUG_EVALUATE(x) {if(goalie_debug) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-Param::Field::PITCH_LENGTH*0.6,0), x);}

namespace {
	bool goalie_debug, is_penalty;
	int this_shoot_cycle = 0;
	const CGeoPoint goalCenter(-Param::Field::PITCH_LENGTH / 2, 0);
	CGeoPoint trickPoint;
	CGeoPoint savePoint(goalCenter);
	CGeoLine BaseLine(goalCenter, Param::Math::PI / 2);
	CGeoLine moveLine(goalCenter + CVector(Param::Field::PENALTY_AREA_DEPTH / 4.0, 0), Param::Math::PI / 2);
	const double PENALTY_BUFFER = 0.05 * Param::Field::PENALTY_AREA_DEPTH;
	double HAVE_BALL_DIST;
	double CLOSE_DIST;
	bool AGGRESSIVE_GOALIE;
	double CHALLENGE_BALL_DIST;
	double BLOCK_DIST;
}

CGoalie2022::CGoalie2022() :last_penalty_status(PENALTY_WAIT), last_penalty_attack_cycle(0)
{
	goalie_debug = paramManager->GOALIE_DEBUG;
	trickPoint = CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH * paramManager->TRICKPOS_DIV_PENALTY, 0);
	HAVE_BALL_DIST = paramManager->HAVE_BALL_DIST;
	CLOSE_DIST = paramManager->CLOSE_DIST;
	AGGRESSIVE_GOALIE = paramManager->AGGRESSIVE_GOALIE;
	CHALLENGE_BALL_DIST = paramManager->CHALLENGE_BALL_DIST;
	BLOCK_DIST = paramManager->BLOCK_DIST;
}

void CGoalie2022::plan(const CVisionModule* pVision)
{
	is_penalty = task().player.isPenalty;
	Tevaluate purpose = evaluate(pVision);
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
	case SAVE:
		if (is_penalty)
			last_penalty_status = PENALTY_TRICK_FINISH;
		pTask = saveTask(pVision);
		break;
	case SUPPORT:
		pTask = supportTask(pVision);
		break;
	case CLEAR_BALL:
		if (is_penalty)
			last_penalty_status = PENALTY_TRICK_FINISH;
		pTask = clearBallTask(pVision);
		break;
	case ATTACK_ENEMY_PENALTY:
		last_penalty_attack_cycle = pVision->Cycle();
		pTask = attackEnemyPenaltyTask(pVision);
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

CGoalie2022::Tevaluate CGoalie2022::evaluate(const CVisionModule* pVision)
{
	int robotNum = task().executor;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const PlayerVisionT& enemy = pVision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	const BallVisionT& ball = pVision->Ball();

	if (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop" || vision->gameState().ballPlacement()) {
		DEBUG_EVALUATE("evaluate: stop");
		return NORMAL;
	} else if (!ball.Valid()) {
		DEBUG_EVALUATE("evaluate: invalid ball");
		return NORMAL;
	} else if (ShouldAttackPenalty(pVision)) {
		DEBUG_EVALUATE("evaluate: attack enemy in penalty");
		return ATTACK_ENEMY_PENALTY;
	} /*else if (IsFarFromBack(ball.Pos())) {
		DEBUG_EVALUATE("evaluate: far ball");
		return NORMAL;
	}*/ else if (isBallShot2Goal(pVision)) {
		DEBUG_EVALUATE("evaluate: danger, save ball!");
		return SAVE;
	} else if (ball.Vel().mod() < 20 && Utils::InOurPenaltyArea(ball.Pos(), PENALTY_BUFFER)) {
		if (CanSupport(pVision)) {
			DEBUG_EVALUATE("evaluate: slow ball, safe to support");
			return SUPPORT;
		} else {
			DEBUG_EVALUATE("evaluate: slow ball, enemy inside, clear ball");
			return CLEAR_BALL;
		}

		if (is_penalty || enemy.Pos().dist(ball.Pos()) < HAVE_BALL_DIST) {
			DEBUG_EVALUATE("evaluate: slow ball, enemy inside, clear ball");
			return CLEAR_BALL;
		} else {
			DEBUG_EVALUATE("evaluate: slow ball, safe to support");
			return SUPPORT;
		}
	} else if (ShouldAttack(pVision)) {
		DEBUG_EVALUATE("evaluate: attack enemy");
		return ATTACK_ENEMY;
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
	if (interseciton.Intersectant() == false) {
		return false;
	}
	CGeoPoint point = interseciton.IntersectPoint();
	if (fabs(point.y()) > Param::Field::GOAL_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE) {
		return false;
	}
	if (Ball.Vel().mod() < 50) {
		return false;
	}
	double ball2goal = Ball.Pos().dist(goalCenter);
	if (ball2goal > 1.5 * Param::Field::PENALTY_AREA_DEPTH) {
		CVector predict_speed = BallSpeedModel::Instance()->speedForDist(ball2goal - Param::Field::PENALTY_AREA_DEPTH, pVision);
		//CGeoPoint predict = Ball.Pos() + Ball.Vel().unit() * (ball2goal - Param::Field::PENALTY_AREA_DEPTH);
		//GDebugEngine::Instance()->gui_debug_msg(predict, ("predict v: " + to_string(predict_speed.mod())).c_str());
		if (isnan(predict_speed.mod()) || predict_speed.mod() < 100)
			return false;
	}

	return true;
}

bool CGoalie2022::CanSupport(const CVisionModule* pVision)
{
	const BallVisionT& ball = pVision->Ball();

	if (is_penalty)
		return false;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
	{
		const PlayerVisionT& enemy = pVision->TheirPlayer(i);
		if (!enemy.Valid())
			continue;
		if (enemy.Pos().dist(ball.Pos()) < HAVE_BALL_DIST)
			return false;
		if (Utils::InOurPenaltyArea(enemy.Pos(), CLOSE_DIST))
			return false;
	}
	// enemy.Pos().dist(ball.Pos()) < HAVE_BALL_DIST
}

bool CGoalie2022::ShouldAttack(const CVisionModule* pVision)
{
	/************************************************************************/
	/* 若对面在靠中前的位置打算单刀，且我方后卫支援困难，这种时候就要主动出击。
	   同时，主动出击风险较大，因此用return false添加限制逻辑为主  by SYLG */
	   /************************************************************************/
	if (!AGGRESSIVE_GOALIE)
		return false;
	int robotNum = task().executor;
	const PlayerVisionT& enemy = pVision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	const BallVisionT& ball = pVision->Ball();
	if (IsFarFromBack(enemy.Pos(), -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH * 2))
		return false;
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
// 点球如果敌人踢球前带太远，我们更容易抢到球，直接上去拿球
bool CGoalie2022::ShouldAttackPenalty(const CVisionModule* pVision)
{
	BallVisionT Ball = pVision->Ball();
	GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(300, 0), to_string(Ball.Vel().mod()).c_str());
	PlayerVisionT me = pVision->OurPlayer(task().executor);
	PlayerVisionT enemy = pVision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	double me2ballDist = Ball.Pos().dist(me.Pos());
	double ball2meDir = (me.Pos() - Ball.Pos()).dir();
	double enemy2ballDist = Ball.Pos().dist(enemy.Pos());
	double ball2enemyDir = (enemy.Pos() - Ball.Pos()).dir();
	double v_enemy = 250;
	double v_me = 100;
	// 过近扑救不需要
	if (pVision->Cycle() - this_shoot_cycle < 100 && Ball.Pos().x() < -300 && me.Pos().x()<-400 && Ball.Vel().mod()>300)
		return false;
	// 稳定状态机，冲出去就别犹豫
	if (pVision->Cycle() - last_penalty_attack_cycle < 15)
		return true;
	if (!is_penalty)
		return false;
	if (Ball.Pos().dist(enemy.Pos()) < 100)
		return false;
	if (Ball.Vel().mod() < 30)
	{
		if (me2ballDist / enemy2ballDist < 0.6)
			return true;
		else if (enemy.Vel().mod() < 100 && me2ballDist / enemy2ballDist < 0.8)
			return true;
		else
			return false;
	} else if (Ball.Vel().mod() > v_enemy) {//fast ball, enemy can't chase
		CGeoLine ballVelLine(Ball.Pos(), Ball.Vel().dir());
		CGeoPoint proj = ballVelLine.projection(me.Pos());
		if (   proj.dist(me.Pos())<1.5*Param::Vehicle::V2::PLAYER_SIZE    /*fabs(Utils::Normalize(ball2meDir - Ball.Vel().dir())) < Param::Math::PI / 18*/) {
			return true;
		} else {
			return false;
		}
	} else { // 球速适中，判断位置
		double enemyGetBallTime = enemy2ballDist / (v_enemy - Ball.Vel().mod());
		double meGetBallTime = me2ballDist / (v_me + Ball.Vel().mod());

		return false;//todo
	}


	return false;
}

inline bool CGoalie2022::IsFarFromBack(const CGeoPoint& pos, int x)
{
	return pos.x() > x;
}

CPlayerTask* CGoalie2022::normalTask(const CVisionModule* pVision)
{
	int robotNum = task().executor;

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
	if (isPosInCornerShootArea(defenceTarget)) //封死近角
		DefPoint = syntYPos(defenceTarget, CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + Param::Vehicle::V2::PLAYER_SIZE, Param::Field::GOAL_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE));
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

CPlayerTask* CGoalie2022::saveTask(const CVisionModule* pVision)
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
	CGeoPoint projection = ballVelLine.projection(savePoint);
	if (projection.dist(savePoint) > Param::Vehicle::V2::PLAYER_SIZE || pVision->Cycle() - this_shoot_cycle > 50)
		generateSavePoint(pVision);
	this_shoot_cycle = pVision->Cycle();
	if (goalie_debug)
		GDebugEngine::Instance()->gui_debug_msg(savePoint, "r", COLOR_BLUE);

	int robotNum = task().executor;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);

	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;
	flag |= PlayerStatus::DRIBBLING;

	return PlayerRole::makeItGoto(robotNum, savePoint, me.Dir(), flag);
}


CGoalie2022::supportStruct::supportStruct(const CVisionModule* pVision, int i, int robotNum)
{
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const BallVisionT& ball = pVision->Ball();
	supporterNum = TaskMediator::Instance()->supporter(i);
	supportPoint = GPUBestAlgThread::Instance()->getBestPointFromArea(i);
	CVector ball2supporter(supportPoint - ball.Pos());
	angleDiff = fabs(me.Dir() - ball2supporter.dir());
}
CPlayerTask* CGoalie2022::supportTask(const CVisionModule* pVision)
{
	//由于实车效果不理想 暂缓 by SYLG 5.15
	//临时解决方案开始
	{
		int robotNum = task().executor;
		const PlayerVisionT& me = pVision->OurPlayer(robotNum);
		double dir = CVector(CGeoPoint(400, 0) - me.Pos()).dir();
		int flag = task().player.flag;
		flag |= PlayerStatus::QUICKLY;
		flag |= PlayerStatus::DRIBBLING;
		return PlayerRole::makeItNoneTrajGetBallForStatic(robotNum, dir, CVector(0, 0), flag);
	}
	//临时解决方案结束

	int robotNum = task().executor;
	const BallVisionT& ball = pVision->Ball();

	vector<supportStruct> supportStructs;
	supportStructs.reserve(AREANUM);
	for (int i = 0; i < AREANUM; i++)
		supportStructs[i] = supportStruct(pVision, i, robotNum);
	//支援点筛选：支援者到位，转动角度差不大（不然太慢），一定要安全
	supportStructs.erase(remove_if(supportStructs.begin(), supportStructs.end(),
		[&](const auto& item) {
		int supporterNum = item.supporterNum;
		const PlayerVisionT& supporter = pVision->OurPlayer(supporterNum);
		CGeoPoint supportPoint = item.supportPoint;
		double angleDiff = item.angleDiff;
		if (supporterNum == 0 || supporter.Pos().dist(supportPoint) > 100 || angleDiff > Param::Math::PI / 2)
			return true;

		CGeoLine passLine(ball.Pos(), supporter.Pos());
		for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
		{
			const PlayerVisionT& blocker = pVision->TheirPlayer(i);
			if (!blocker.Valid())
				continue;
			CGeoPoint blockerProj = passLine.projection(blocker.Pos());
			double blocker2projDist = blocker.Pos().dist(blockerProj);
			double ball2projDist = ball.Pos().dist(blockerProj);
			if (blocker2projDist > 300 || ball2projDist < 10)
				continue;
			double ratio_dist = blocker2projDist / ball2projDist;
			if (ratio_dist < 1.2)
				return true;
		}
		return false;
	}), supportStructs.end());
	sort(supportStructs.begin(), supportStructs.end(), [&](const auto& a, const auto& b) {return a.angleDiff < b.angleDiff;	});

	if (supportStructs.empty())
		return clearBallTask(pVision);

	double finalDir = supportStructs[0].angleDiff;

	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;
	flag |= PlayerStatus::DRIBBLING;

	double dist = (ball.Pos() - supportStructs[0].supportPoint).mod() - Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER;
	double power = sqrt(powf(ParamManager::Instance()->FASTEST_RECEIVE_VEL, 2) + 2 * ParamManager::Instance()->BALL_DEC * dist);
	power = min(power, (double)Param::Rule::MAX_BALL_SPEED);

	return PlayerRole::makeItDribbleTurnKickV2(robotNum, finalDir, 7.0 * Param::Math::PI / 180.0, 0, power);
	//todo1 isAdvance和target有啥用 问zyj
	//todo2 改变flag，不然守门员用不了
	//todo3 怎么告诉supporter我要传给他
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

	//return PlayerRole::makeItGoto(robotNum, ball.Pos(), dir, flag);//todo need test
	return PlayerRole::makeItNoneTrajGetBall(robotNum, dir, CVector(0, 0), flag);
	//拿到球后通过lua层面检测会自己踢出去
}

CPlayerTask* CGoalie2022::attackEnemyPenaltyTask(const CVisionModule* pVision)
{
	int robotNum = task().executor;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const BallVisionT& ball = pVision->Ball();
	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;
	flag |= PlayerStatus::DRIBBLING;
	return PlayerRole::makeItGoto(robotNum, ball.Pos(), me.Dir(), flag);
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
	flag |= PlayerStatus::NOT_AVOID_OUR_VEHICLE;
	flag |= PlayerStatus::NOT_AVOID_THEIR_VEHICLE;
	flag |= PlayerStatus::QUICKLY;
	flag |= PlayerStatus::DRIBBLING;

	return PlayerRole::makeItNoneTrajGetBall(robotNum, dir, CVector(0, 0), flag);
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

	static int random_num = paramManager->RANDOM_NUM;
	static double random_start = paramManager->RANDOM_MIN;
	static double random_end = paramManager->RANDOM_MAX;
	double random_step = (random_end - random_start) / double(random_num - 1);
	double random_current = random_start - random_step;

	double move_x = moveLine.point1().x();
	//if (!pVision->gameState().gameOn()) // 点球规则
	//	move_x = -Param::Field::PITCH_LENGTH / 2;

	vector<CGeoPoint> random_points(random_num);
	generate(random_points.begin(), random_points.end(), //generate points between [begin,end]
		[&]() {
		random_current += random_step;
		return CGeoPoint(move_x, random_current * Param::Field::GOAL_WIDTH); });
	if (goalie_debug)
		for (auto& p : random_points)
			GDebugEngine::Instance()->gui_debug_x(p, COLOR_GREEN);
	default_random_engine generator{ (unsigned int)pVision->Cycle() };
	vector<int> weight_vector;
	weight_vector.reserve(random_num);
	for (auto& p : random_points)
		weight_vector.push_back(100000 / sqrt(defCenter.dist(p)) / std::log10(30 + p.dist(CGeoPoint(move_x, 0))));
	discrete_distribution<int> weight(weight_vector.begin(), weight_vector.end());
	//固定间隔帧数进行随机生成
	static int generate_index = weight(generator);
	static int interval_cnt = 0;
	static const int generate_interval = paramManager->STABLE_FRAME_INTERVAL;
	interval_cnt++;
	if (interval_cnt > generate_interval)
	{
		interval_cnt = 0;
		generate_index = weight(generator);
	}
	int robotNum = task().executor;

	CGeoPoint finalPos = random_points[generate_index];

	//点球向前晃人
	Tpenalty penalty_status = last_penalty_status;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	switch (last_penalty_status)
	{
	case PENALTY_WAIT:
		if (pVision->gameState().gameOn() && enemy.Pos().x() < 0)
			penalty_status = PENALTY_TRICK_START;
		break;
	case PENALTY_TRICK_START:
		if (me.Pos().dist(trickPoint) < 20)
			penalty_status = PENALTY_TRICK_FINISH;
		break;
	case PENALTY_TRICK_FINISH:
		if (pVision->gameState().gameOff())
			penalty_status = PENALTY_WAIT;
		break;
	}
	last_penalty_status = penalty_status;
	if (penalty_status == PENALTY_TRICK_START)
		finalPos = trickPoint;

	double dir = 0;

	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;

	return PlayerRole::makeItGoto(robotNum, finalPos, dir, flag);
}

void CGoalie2022::generateSavePoint(const CVisionModule* pVision)
{
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& me = pVision->OurPlayer(task().executor);
	CGeoLine ballVelLine(ball.Pos(), ball.Vel().dir());
	CVector ball2me(ball.Pos() - me.Pos());
	CGeoLine me_vertical2_me2ballLine(me.Pos(), ball2me.dir() + Param::Math::PI / 2);
	CGeoLineLineIntersection intersect(ballVelLine, me_vertical2_me2ballLine);
	if (intersect.Intersectant() && Utils::InOurPenaltyArea(intersect.IntersectPoint(), 0))
		savePoint = intersect.IntersectPoint();
	else
	{
		intersect = CGeoLineLineIntersection(ballVelLine, moveLine);
		if (!intersect.Intersectant())
			savePoint = goalCenter;
		else
			savePoint = intersect.IntersectPoint();
		double limit_y = Param::Field::GOAL_WIDTH / 2.0 - 5.0;
		if (fabs(savePoint.y()) > limit_y)
			savePoint.setY(savePoint.y() / fabs(savePoint.y()) * limit_y);
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
				vector<double> blockDirList{ -Param::Math::PI, Param::Math::PI };
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

CGeoPoint CGoalie2022::syntYPos(CGeoPoint reference, CGeoPoint target)
{
	int sign = (reference.y() > 0) - (reference.y() < 0);
	return CGeoPoint(target.x(), sign * target.y());
}

bool CGoalie2022::isPosInCornerShootArea(CGeoPoint pos)
{
	CGeoPoint penaltyLeftCorner(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH, -Param::Field::PENALTY_AREA_WIDTH / 2);
	CGeoPoint penaltyRightCorner(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH, Param::Field::PENALTY_AREA_WIDTH / 2);
	CGeoPoint leftGoalPost(-Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2);
	CGeoPoint rightGoalPost(-Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2);
	double angle_pos2leftGoalPost = (pos - leftGoalPost).dir();
	double angle_penaltyRightCorner2leftGoalPost = (penaltyRightCorner - leftGoalPost).dir();
	double angle_pos2rightGoalPost = (pos - rightGoalPost).dir();
	double angle_penaltyLeftCorner2rightGoalPost = (penaltyLeftCorner - rightGoalPost).dir();
	return (angle_pos2leftGoalPost > angle_penaltyRightCorner2leftGoalPost) || (angle_pos2rightGoalPost < angle_penaltyLeftCorner2rightGoalPost);
}
