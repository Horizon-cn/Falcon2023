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

namespace {
	bool goalie_debug;

	CGeoPoint goalCentre(-Param::Field::PITCH_LENGTH / 2, 0);
	CGeoLine baseLine(goalCentre, Param::Math::PI / 2);
	CGeoLine moveLine(goalCentre + CVector(Param::Field::PENALTY_AREA_DEPTH / 4.0, 0), Param::Math::PI / 2);
	CGeoPoint trickPoint(goalCentre + Utils::Polar2Vector(Param::Field::PENALTY_AREA_DEPTH, 0));
}

CGoalie2022::CGoalie2022() :lastSaveCycle(0), startCycle_ballInsidePenalty(0), startCycle_ballOutsidePenalty(0),
needSave(false), needClear(false), needSupport(false), needAdjust(false), isNewSave(false),
trickStart(false), trickFinish(false), needAttack(false),
cycle_ballInsidePenalty(0), cycle_penaltyAttack(0)
{
	goalie_debug = paramManager->GOALIE_DEBUG;
}

const void DEBUG(const char msg[], int mode = 0) {
	CGeoPoint p;
	switch (mode) {
	case 0:
		p.fill(-Param::Field::PITCH_LENGTH * 0.6, 0);
		break;
	case 1:
		p.fill(-Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2);
		break;
	case 2:
		p.fill(-Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2);
		break;
	case 3:
		p.fill(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH, Param::Field::PENALTY_AREA_WIDTH / 2);
		break;
	case 4:
		p.fill(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH, -Param::Field::PENALTY_AREA_WIDTH / 2);
		break;
	default:
		p.fill(0, 0);
		break;
	}
	if (goalie_debug) {
		GDebugEngine::Instance()->gui_debug_msg(p, msg);
	}
}

void CGoalie2022::plan(const CVisionModule* pVision)
{
	updateSelfJudge();
	updateBallJudge();

	if (task().player.isPenalty) { // 点球状态机
		if (needAdjust) {
			setState(ADJUST);
		} else if (vision->gameState().theirPenaltyKick()) {
			setState(PENALTY_WAIT);
			trickStart = trickFinish = false;
		} else {
			switch (state()) {
			case ADJUST:
				setState(NORMAL);
				break;
			case PENALTY_WAIT:
				if (vision->gameState().gameOn()) {
					setState(NORMAL);
				}
				break;
			case NORMAL:
				if (needSave) {
					setState(SAVE);
				} else if (needAttack) {
					setState(PENALTY_ATTACK);
				} else if (trickStart && !trickFinish) {
					setState(PENALTY_TRICK);
				}
				break;
			case SAVE:
				if (needAttack) {
					setState(PENALTY_ATTACK);
				} else if (!needSave) {
					setState(NORMAL);
				}
				break;
			case PENALTY_TRICK:
				if (needSave) {
					setState(SAVE);
					trickFinish = true;
				} else if (trickFinish) {
					setState(NORMAL);
				}
				break;
			case PENALTY_ATTACK:
				if (needSave && cycle_penaltyAttack < 0.5 * Param::Vision::FRAME_RATE) {
					setState(SAVE);
				}
				break;
			}
		}
	} else { // 非点球状态机
		if (false) {
			setState(TEST);
		} else if (needAdjust) {
			setState(ADJUST);
		} else if (vision->gameState().gameOff()) {
			setState(NORMAL);
		} else if (needSave) {
			setState(SAVE);
		} else if (needClear) {
			setState(CLEAR);
		} else if (needSupport) {
			setState(SUPPORT);
		} else {
			setState(NORMAL);
		}
	}

	updateCycleCounter();

	switch (state()) {
	case TEST:
		break;
	case PENALTY_WAIT:
		DEBUG("wait");
		setSubTask(PlayerRole::makeItGoto(task().executor, CGeoPoint(-Param::Field::PITCH_LENGTH/2, 0), 0, task().player.flag));
		break;
	case PENALTY_TRICK:
		DEBUG("trick");
		setSubTask(PlayerRole::makeItGoto(task().executor, trickPoint, 0, task().player.flag));
		break;
	case ADJUST:
		DEBUG("adjust");
		setSubTask(adjustTask());
		break;
	case NORMAL:
		DEBUG("normal");
		setSubTask(normalTask());
		break;
	case SAVE:
		DEBUG("save");
		setSubTask(saveTask());
		break;
	case CLEAR:
		DEBUG("clear");
		setSubTask(clearTask());
		break;
	case SUPPORT:
		DEBUG("support");
		setSubTask(supportTask());
		break;
	case PENALTY_ATTACK:
		DEBUG("attack");
		setSubTask(attackTask());
		break;
	}

	CStatedTask::plan(pVision);
}

void CGoalie2022::updateSelfJudge()
{
	const PlayerVisionT& me = vision->OurPlayer(task().executor);
	if (me.X() < -Param::Field::PITCH_LENGTH / 2
		&& Utils::InBetween(fabs(me.Y()), Param::Field::GOAL_WIDTH / 2, Param::Field::GOAL_WIDTH / 2 + 20)) {
		needAdjust = true;
	} else {
		needAdjust = false;
	}
}

void CGoalie2022::updateBallJudge()
{
	needSave = needAttack = needClear = needSupport = false;

	const BallVisionT& ball = vision->Ball();
	if (!ball.Valid())
		return;

	bool maybeShoot = false;
	double dist_ball2goal;
	if (ball.VelX() < 0 && ball.Vel().mod() > 50) {
		CGeoLine ballVelLine(ball.Pos(), ball.Vel().dir());
		CGeoLineLineIntersection interseciton(baseLine, ballVelLine);
		if (interseciton.Intersectant()) {
			CGeoPoint goalPoint = interseciton.IntersectPoint(); // 进球点
			if (fabs(goalPoint.y()) < Param::Field::GOAL_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE) {
				// todo 考虑球以大速度滚向射门路线上的敌人并touch打另一边
				dist_ball2goal = ball.Pos().dist(goalPoint);
				// 离得远的低速球不需要考虑
				if (dist_ball2goal > 2 * Param::Field::GOAL_WIDTH) { // 使用球门宽度作为度量单位，必要时参数化
					CVector predictSpd = BallSpeedModel::Instance()->speedForDist(dist_ball2goal - Param::Field::GOAL_WIDTH, vision);
					CGeoPoint p = ball.Pos() + ball.Vel().unit() * (dist_ball2goal - Param::Field::PENALTY_AREA_DEPTH);
					GDebugEngine::Instance()->gui_debug_msg(p, ("predict v: " + to_string(predictSpd.mod())).c_str());
					if (predictSpd.mod() > 20) {
						maybeShoot = true;
					}
				} else {
					maybeShoot = true;
				}
			}
		}
	}
	if (maybeShoot) {
		DEBUG("maybe shoot", 1);
		if (isMeReady4Ball(dist_ball2goal)) {
			if (canMeAttack()) {
				needAttack = true;
			} else {
				needClear = true;
			}
		} else { // not ready
			needSave = true;
		}
	} else if (Utils::InOurPenaltyArea(ball.Pos(), 0)) {
		if (ball.Vel().mod() < 30) {
			if (cycle_ballInsidePenalty > 5 * Param::Vision::FRAME_RATE) { //  规则：对于处在禁区内的球，守门员需要在10s内将球清出禁区
				needClear = true;
			} else {
				for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
					const PlayerVisionT& enemy = vision->TheirPlayer(i);
					if (enemy.Valid() &&
						enemy.Pos().dist(ball.Pos()) < 100 || Utils::InOurPenaltyArea(enemy.Pos(), 100)) {
						needClear = true;
					}
				}
				needSupport = true;
			}
		} else {
		}
	} else if (canMeAttack()) {
		needAttack = true;
	} else if (task().player.isPenalty && !trickStart && !trickFinish) {
		const PlayerVisionT& enemy = vision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
		if (enemy.Pos().dist(ball.Pos()) < 50 && enemy.Pos().x() < 0 && enemy.Pos().x() > -200) {
			trickStart = true;
		} else {
		}
	} else if (trickStart && !trickFinish) {
		const PlayerVisionT& me = vision->OurPlayer(task().executor);
		if (me.Pos().dist(trickPoint) < 20) {
			trickFinish = true;
		} else {
		}
	} else {
	}
}

void CGoalie2022::updateCycleCounter() {
	if (state() == SAVE) {
		if (vision->Cycle() - lastSaveCycle > Param::Vision::FRAME_RATE) {
			isNewSave = true;
		}
		lastSaveCycle = vision->Cycle();
	}

	if (state() == PENALTY_ATTACK) {
		cycle_penaltyAttack++;
	} else {
		cycle_penaltyAttack = 0;
	}

	const BallVisionT& ball = vision->Ball();
	// 球在禁区内停留帧数，为防止犯规，当视觉抖动时认为球在禁区内
	if (vision->gameState().gameOff() ||
		(!Utils::InOurPenaltyArea(ball.Pos(), 0) && vision->Cycle() - startCycle_ballOutsidePenalty > Param::Vision::FRAME_RATE / 5)) {
		startCycle_ballInsidePenalty = vision->Cycle();
	} else if (Utils::InOurPenaltyArea(ball.Pos(), 0)) {
		startCycle_ballOutsidePenalty = vision->Cycle();
	}
	cycle_ballInsidePenalty = vision->Cycle() - startCycle_ballInsidePenalty;
	if (cycle_ballInsidePenalty > Param::Vision::FRAME_RATE) {
		DEBUG(to_string(cycle_ballInsidePenalty).c_str(), 2);
	}
}


CPlayerTask* CGoalie2022::adjustTask()
{
	int myNum = task().executor;
	const PlayerVisionT& me = vision->OurPlayer(myNum);
	CGeoPoint adjustPos(-Param::Field::PITCH_LENGTH / 2 + 30, Param::Field::GOAL_WIDTH / 2);
	return PlayerRole::makeItGoto(myNum, syntYPos(me.Pos(), adjustPos), me.Dir(), task().player.flag);
}

CPlayerTask* CGoalie2022::normalTask()
{
	int myNum = task().executor;

	const BallVisionT& ball = vision->Ball();
	const PlayerVisionT& enemy = vision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	CGeoPoint defenceTarget = ball.Valid() ? ball.Pos() : enemy.Pos();//todo 防守共同目标选取

	CGeoPoint defPoint = generateNormalPoint(defenceTarget); // 目的是做好准备，对方射门时能在最好的位置扑球

	double dir;
	const PlayerVisionT& me = vision->OurPlayer(myNum);
	if (ball.Valid()) {
		dir = CVector(ball.Pos() - me.Pos()).dir();
	} else {
		dir = CVector(me.Pos() - goalCentre).dir();
	}

	int flag = task().player.flag;

	return PlayerRole::makeItGoto(myNum, defPoint, dir, flag);
}

CPlayerTask* CGoalie2022::saveTask()
{
	/************************************************************************/
	/* 扑球时，若假设球和人匀速，则需要在球速线上找点P，使得P到人近，到球远（比值尽量小）
	   容易发现，P-人-球为直角。同时，若这个点是人恰好扑到球的点，在扑球过程中点的生成是稳定的
	   但是，现实中，守门员需要加速，而速度如果一开始慢的话会导致生成点的位置改变（后移），继而导致守门员变向、加速不及时
	   因此，使用缓冲机制来计算扑球点 by SYLG */
	   /************************************************************************/
	static CGeoPoint savePoint;
	const BallVisionT& ball = vision->Ball();
	CGeoLine ballVelLine(ball.Pos(), ball.Vel().dir());
	CGeoPoint projection = ballVelLine.projection(savePoint);
	if (projection.dist(savePoint) > 0.6 * Param::Vehicle::V2::PLAYER_SIZE || isNewSave)
		savePoint = generateSavePoint();
	if (goalie_debug)
		GDebugEngine::Instance()->gui_debug_msg(savePoint, "s", COLOR_BLUE);

	int robotNum = task().executor;
	const PlayerVisionT& me = vision->OurPlayer(robotNum);

	int flag = task().player.flag;
	flag |= PlayerStatus::QUICKLY;
	flag |= PlayerStatus::DRIBBLING;

	return PlayerRole::makeItGoto(robotNum, savePoint, me.Dir(), flag);
}

CPlayerTask* CGoalie2022::clearTask()
{
	int myNum = task().executor;
	const PlayerVisionT& me = vision->OurPlayer(myNum);
	const BallVisionT& ball = vision->Ball();

	double clearDir = calcClearDir();

	double precision;
	if (cycle_ballInsidePenalty < 5 * Param::Vision::FRAME_RATE) {
		precision = Param::Math::PI / 18;
	} else if (cycle_ballInsidePenalty < 8 * Param::Vision::FRAME_RATE) {
		precision = Param::Math::PI / 8;
	} else {
		precision = Param::Math::PI;
	}
	if (fabs(Utils::Normalize(me.Dir() - clearDir)) < precision) {
		KickStatus::Instance()->setChipKick(myNum, 550);
	}

	int flag = task().player.flag;
	flag |= PlayerStatus::DRIBBLING;

	return PlayerRole::makeItNoneTrajGetBall(myNum, clearDir, CVector(0, 0), flag);
}

// 支援的目的：把球大脚到前场的同时保持我方控球率
// 在目前挑球传接技术未成熟的情况下，仅使用极其简单的判断逻辑
CPlayerTask* CGoalie2022::supportTask()
{
	int myNum = task().executor;

	const BallVisionT& ball = vision->Ball();
	CGeoPoint leftSupportTarget(Param::Field::PITCH_LENGTH / 4, -Param::Field::PITCH_WIDTH / 4);
	CGeoPoint rightSupportTarget(Param::Field::PITCH_LENGTH / 4, Param::Field::PITCH_WIDTH / 4);
	double supportDir;
	if (nearestEnemyFrom(leftSupportTarget) > nearestEnemyFrom(rightSupportTarget)) {
		supportDir = (leftSupportTarget - ball.Pos()).dir();
	} else {
		supportDir = (rightSupportTarget - ball.Pos()).dir();
	}

	const PlayerVisionT& me = vision->OurPlayer(myNum);
	if (fabs(Utils::Normalize(me.Dir() - supportDir) < Param::Math::PI / 18)) {
		KickStatus::Instance()->setChipKick(myNum, 550);
	}

	int flag = task().player.flag;
	flag |= PlayerStatus::DRIBBLING;

	return PlayerRole::makeItNoneTrajGetBall(myNum, supportDir, CVector(0, 0), flag);
}

CPlayerTask* CGoalie2022::attackTask()
{
	int myNum = task().executor;
	const PlayerVisionT& me = vision->OurPlayer(myNum);
	double dir = me.Dir();
	int flags = task().player.flag;
	return PlayerRole::makeItNoneTrajGetBall(myNum, dir, CVector(0, 0), flags);
}

bool CGoalie2022::isMeReady4Ball(double dist_ball2goal)
{
	const PlayerVisionT& me = vision->OurPlayer(task().executor);
	if (me.Vel().mod() > 20) {
		return false;
	}
	double biasAngle;//考虑球速方向具有一定误差
	if (dist_ball2goal > 200) {
		biasAngle = Param::Math::PI / 18;
	} else if (dist_ball2goal > 100) {
		biasAngle = Param::Math::PI / 36;
	} else {
		biasAngle = Param::Math::PI / 72;
	}
	CGeoCirlce myReadyCircle(me.Pos(), Param::Vehicle::V2::PLAYER_SIZE);
	const BallVisionT& ball = vision->Ball();
	CGeoLine ballVelLine_biasLeft(ball.Pos(), Utils::Normalize(ball.Vel().dir() - biasAngle));
	CGeoLine ballVelLine_biasRight(ball.Pos(), Utils::Normalize(ball.Vel().dir() + biasAngle));
	CGeoLineCircleIntersection intersectLeft(ballVelLine_biasLeft, myReadyCircle);
	CGeoLineCircleIntersection intersectRight(ballVelLine_biasRight, myReadyCircle);
	if (intersectLeft.intersectant() && intersectRight.intersectant()) {
		return true;
	} else {
		return false;
	}
}

bool CGoalie2022::canMeAttack()
{
	const BallVisionT& ball = vision->Ball();
	const PlayerVisionT& enemy = vision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	const PlayerVisionT& me = vision->OurPlayer(task().executor);

	double me2ballDist = me.Pos().dist(ball.Pos());
	double enemy2ballDist = enemy.Pos().dist(ball.Pos());

	const double v_enemy = 300;
	const double v_me = 200;

	if (!task().player.isPenalty) {
		return false;
	} else if (enemy2ballDist < 100) {
		return false;
	} else if (ball.Vel().mod() < 30) {
		if (me2ballDist / enemy2ballDist < 0.6) {
			DEBUG("slow ball, far enemy", 3);
			return true;
		} else if (enemy.Vel().mod() < 100 && me2ballDist / enemy2ballDist < 0.8) {
			DEBUG("slow ball, slow enemy", 3);
			return true;
		} else {
			return false;
		}
	} else if (ball.Vel().mod() > v_enemy) {
		DEBUG("fast ball", 3);
		return true;
	} else { // 球速适中，判断位置
		double enemyGetBallTime = enemy2ballDist / (v_enemy - ball.Vel().mod());
		double meGetBallTime = me2ballDist / (v_me + ball.Vel().mod());
		if (meGetBallTime / enemyGetBallTime < 0.8) {
			DEBUG("I get ball first", 3);
			return true;
		} else {
			return false;
		}
	}
}

bool CGoalie2022::isPosInCornerShootArea(const CGeoPoint& pos)
{
	CGeoPoint convertPos = syntYPos(CGeoPoint(0, 1), pos); // 在 y>0 的半场考虑
	CGeoPoint penaltyRightCorner(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH, Param::Field::PENALTY_AREA_WIDTH / 2);
	CGeoPoint leftGoalPost(-Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2);
	double dir_pos2leftGoalPost = (convertPos - leftGoalPost).dir();
	double dir_penaltyRightCorner2leftGoalPost = (penaltyRightCorner - leftGoalPost).dir();
	return dir_pos2leftGoalPost > dir_penaltyRightCorner2leftGoalPost;
}

CGeoPoint CGoalie2022::generateNormalPoint(CGeoPoint defenceTarget)
{
	CGeoPoint defPoint;
	int method;
	if (task().player.isPenalty) {
		method = paramManager->PENALTY_CALC_METHOD;
	} else {
		method = paramManager->NORMAL_CALC_METHOD;
	}
	switch (method) {
	case 0: // 传统算法 球门中心连线
		if (isPosInCornerShootArea(defenceTarget)) { //封死近角
			defPoint = syntYPos(defenceTarget, CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + Param::Vehicle::V2::PLAYER_SIZE, Param::Field::GOAL_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE));
		} else {
			CGeoLine defenceLine(defenceTarget, goalCentre);
			CGeoLineLineIntersection intersect(defenceLine, moveLine);
			if (!intersect.Intersectant())
				defPoint = goalCentre;
			else
				defPoint = intersect.IntersectPoint();
		}
		break;
	case 1: // 角平分线算点法 by jj
		defPoint = CGeoPoint(0, 0);
		break;
	case 2: // （点球使用）加权随机摇摆
	{
		CGeoPoint defCentre;//防守中心，影响随机点的分布
		const PlayerVisionT& enemy = vision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
		CGeoLine defLine;
		if (fabs(enemy.Dir()) <= Param::Math::PI / 2) {
			defLine = CGeoLine(defenceTarget, goalCentre);
		} else {
			defLine = CGeoLine(enemy.Pos(), enemy.Dir());
		}
		CGeoLineLineIntersection intersect(defLine, baseLine);
		if (intersect.Intersectant()) {
			defCentre = intersect.IntersectPoint();
		} else {
			defCentre = goalCentre;
		}

		static const int random_num = paramManager->RANDOM_NUM;
		static const double random_start = paramManager->RANDOM_MIN;
		static const double random_end = paramManager->RANDOM_MAX;
		// 在[start,end]生成n个点
		double random_step = (random_end - random_start) / double(random_num - 1);
		double move_x = moveLine.point1().x();
		vector<CGeoPoint> random_points;
		random_points.reserve(random_num);
		for (int i = 0; i < random_num; i++) {
			random_points.emplace_back(move_x, (random_start + i * random_step) * Param::Field::GOAL_WIDTH);
		}

		if (goalie_debug)
			for (auto& p : random_points)
				GDebugEngine::Instance()->gui_debug_x(p, COLOR_GREEN);

		default_random_engine generator{ (unsigned int)vision->Cycle() };
		vector<int> weight_vector;
		weight_vector.reserve(random_num);
		for (auto& p : random_points)
			weight_vector.push_back(100000 / sqrt(defCentre.dist(p)) / std::log10(30 + p.dist(CGeoPoint(move_x, 0))));
		discrete_distribution<int> weight(weight_vector.begin(), weight_vector.end());
		//固定间隔帧数进行随机生成
		static int generate_index = weight(generator);
		static int interval_cnt = 0;
		static const int generate_interval = paramManager->STABLE_FRAME_INTERVAL;
		interval_cnt++;
		if (interval_cnt > generate_interval) {
			interval_cnt = 0;
			generate_index = weight(generator);
		}
		defPoint = random_points[generate_index];
	}
	break;
	default:
		cout << "ERROR in choosing normal point generation method!\n";
		break;
	}
	return defPoint;
}

CGeoPoint CGoalie2022::generateSavePoint()
{
	// 算点逻辑详见 saveTask, 该模型缺陷：只考虑匀速，未考虑门将的初始速度
	const BallVisionT& ball = vision->Ball();
	const PlayerVisionT& me = vision->OurPlayer(task().executor);
	CGeoLine ballVelLine(ball.Pos(), ball.Vel().dir());
	CVector ball2me(ball.Pos() - me.Pos());
	CGeoLine me_vertical2_me2ballLine(me.Pos(), ball2me.dir() + Param::Math::PI / 2);
	CGeoLineLineIntersection intersect(ballVelLine, me_vertical2_me2ballLine);
	CGeoPoint savePoint;
	if (intersect.Intersectant() && Utils::InOurPenaltyArea(intersect.IntersectPoint(), 0)) {
		savePoint = intersect.IntersectPoint();
	} else {
		intersect = CGeoLineLineIntersection(ballVelLine, moveLine);
		if (!intersect.Intersectant()) {
			savePoint = goalCentre;
		} else {
			savePoint = intersect.IntersectPoint();
		}
		double limit_y = Param::Field::GOAL_WIDTH / 2.0 - 3.0;
		if (fabs(savePoint.y()) > limit_y) {
			savePoint.setY(savePoint.y() / fabs(savePoint.y()) * limit_y);
		}
	}
	return savePoint;
}

double CGoalie2022::calcClearDir()
{
	static const double BLOCK_DIST = paramManager->BLOCK_DIST; // 在这个距离内的人会挡住挑球轨迹
	int myNum = task().executor;
	const PlayerVisionT& me = vision->OurPlayer(myNum);
	const BallVisionT& ball = vision->Ball();

	if (me.Pos().dist(ball.Pos()) > 20) {
		return 0; // 还没拿到球，节省算力
	}

	double dir_me2ball = (ball.Pos() - me.Pos()).dir();
	vector<double> blockDirList{ -Param::Math::PI, Param::Math::PI };
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		CGeoPoint pos = vision->OurPlayer(i).Pos();
		if (pos.dist(ball.Pos()) < BLOCK_DIST && i != myNum) {
			blockDirList.push_back((pos - ball.Pos()).dir());
		}
		pos = vision->TheirPlayer(i).Pos();
		if (pos.dist(ball.Pos()) < BLOCK_DIST) {
			blockDirList.push_back((pos - ball.Pos()).dir());
		}
	}
	sort(blockDirList.begin(), blockDirList.end());

	double allowedAngle;
	if (cycle_ballInsidePenalty < 5 * Param::Vision::FRAME_RATE) {
		allowedAngle = Param::Math::PI / 3;
	} else if (cycle_ballInsidePenalty < 7 * Param::Vision::FRAME_RATE) {
		allowedAngle = Param::Math::PI / 5;
	} else {
		allowedAngle = Param::Math::PI / 10;
	}

	vector<double> clearDirList;
	for (int i = 0; i < blockDirList.size() - 1; i++) {
		if (blockDirList[i + 1] - blockDirList[i] > allowedAngle) {
			clearDirList.push_back((blockDirList[i + 1] + blockDirList[i]) / 2);
		}
	}

	// 防乌龙
	CGeoPoint pos_leftDanger(-Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE);
	CGeoPoint pos_rightDanger(-Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE);
	double dir_ball2leftDanger = (pos_leftDanger - ball.Pos()).dir();
	double dir_ball2rightDanger = (pos_rightDanger - ball.Pos()).dir();
	function<bool(double)> erase_standard;
	if (dir_ball2leftDanger < 0 && dir_ball2rightDanger>0) {
		erase_standard = [&](double dir) {return dir< dir_ball2leftDanger || dir >dir_ball2rightDanger; };
	} else if (dir_ball2leftDanger * dir_ball2rightDanger >= 0) {
		erase_standard = [&](double dir) {return dir< dir_ball2leftDanger && dir >dir_ball2rightDanger; };
	} else {
		erase_standard = [](double) {return false; };
		cout << "ERROR in clear ball dir: unexpected situation!";
	}
	clearDirList.erase(remove_if(clearDirList.begin(), clearDirList.end(), erase_standard), clearDirList.end());

	for (auto& dir : clearDirList) {
		GDebugEngine::Instance()->gui_debug_x(ball.Pos() + Utils::Polar2Vector(20, dir), COLOR_GREEN);
	}

	double clearBallDir;
	if (clearDirList.empty()) {
		clearBallDir = dir_me2ball;
	} else {
		sort(clearDirList.begin(), clearDirList.end(),
			[&](double dir1, double dir2) {return fabs(Utils::Normalize(dir1 - dir_me2ball)) < fabs(Utils::Normalize(dir2 - dir_me2ball)); });
		clearBallDir = clearDirList[0];
	}
	GDebugEngine::Instance()->gui_debug_line(ball.Pos(), ball.Pos() + Utils::Polar2Vector(600, clearBallDir), COLOR_BLUE);
	return clearBallDir;
}

double CGoalie2022::nearestEnemyFrom(CGeoPoint p)
{
	vector<double> dists;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		const PlayerVisionT& enemy = vision->TheirPlayer(i);
		if (enemy.Valid()) {
			dists.push_back(enemy.Pos().dist(p));
		}
	}
	if (dists.empty()) {
		return 9999999;
	} else {
		return *min_element(dists.begin(), dists.end());
	}
}

CGeoPoint CGoalie2022::syntYPos(const CGeoPoint& ref, const CGeoPoint& target)
{
	int sign = (ref.y() > 0) - (ref.y() < 0);
	return CGeoPoint(target.x(), sign * fabs(target.y()));
}

CPlayerCommand* CGoalie2022::execute(const CVisionModule* pVision)
{
	if (subTask()) {
		return subTask()->execute(pVision);
	}
	return NULL;
}