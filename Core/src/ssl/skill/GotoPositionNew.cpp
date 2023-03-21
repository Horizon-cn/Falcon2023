#include "GotoPositionNew.h"
#include <utils.h>
#include "skill/Factory.h"
#include <CommandFactory.h>
#include <Vision/VisionModule.h>
#include <WorldModel/RobotCapability.h>
#include <sstream>
#include <TaskMediator.h>
#include <MotionControl/ControlModel.h>
#include <WorldModel/robot_power.h>
#include <WorldModel/DribbleStatus.h>

#include <GDebugEngine.h>
#include "MotionControl/DynamicsSafetySearch.h"
#include "PathPlan/PathPlanner.h"
#include <fstream>
#include "PathPlan/BezierCurveNew.h"
#include "PathPlan/BezierMotion.h"
#include <PathPlan/RRTPathPlannerNew.h>
#include <iostream>
#include <PathPlan/BSplineCurver.h>
/************************************************************************/
/*                                                                      */
/************************************************************************/
namespace {
	/// debug switch
	bool drawPathLine = false;

	/// dealing with the shaking when approaching the target
	const double DIST_REACH_CRITICAL = 2;	// [unit : cm]
	const double SlowFactor = 0.5;
	const double FastFactor = 1.2;

	double stopBallAvoidDist = 50;
	double ballPlacementDist = 60;
	double BUFFER = 5.5;

	/// motion control parameters
	double MAX_TRANSLATION_SPEED = 400;		// [unit : cm/s]
	double MAX_TRANSLATION_ACC = 600;		// [unit : cm/s2]
	double MAX_ROTATION_SPEED = 5;			// [unit : rad/s]
	double MAX_ROTATION_ACC = 15;			// [unit : rad/s2]
	double TRANSLATION_ACC_LIMIT = 1000;
	double MAX_TRANSLATION_DEC = 650;

	/// for goalie
	double MAX_TRANSLATION_SPEED_GOALIE;
	double MAX_TRANSLATION_ACC_GOALIE;
	double MAX_TRANSLATION_DEC_GOALIE;
	double MAX_ROTATION_ACC_GOALIE = 15;
	double MAX_ROTATION_SPEED_GOALIE = 15;

	/// for guards
	double MAX_TRANSLATION_SPEED_BACK;
	double MAX_TRANSLATION_ACC_BACK;
	double MAX_TRANSLATION_DEC_BACK;
	double MAX_ROTATION_ACC_BACK = 15;
	double MAX_ROTATION_SPEED_BACK = 15;

	/// control method parameter
	int TASK_TARGET_COLOR = COLOR_CYAN;

	PlanType playType = RRT;

	bool PASS_PTS = true; //control if pass the real points got by RRT 困在球门里不开

	bool DRAW_OBS = false;
	bool DRAW_RRT = false;
	bool DRAW_TRAJ = false;
	double LOWER_BND_UDOT = 0.0;
	int MAX_SEARCH_ITERATION = 2;
	int COUNTPLAN_THRESHOLD = 40;
	double INFLAT_RATIO = 1.0;
	const double minVelConstr = 150;
	const double thresholdL = 20;
	const double thresholdS = 10;
	const double swapPathCost = 40;
	const double stopDecFactor = 3.0;
	const double angleToContri = Param::Math::PI / 10.0;
	const double onlyRotateScale = 2.5;

	const double FRAME_PERIOD = 1.0 / Param::Vision::FRAME_RATE;
	const double TEAMMATE_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE + 4.0f;
	const double OPP_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE + 5.5f;
	const double BALL_AVOID_DIST = Param::Field::BALL_SIZE + 5.0f;

	bool lastIsDirect[Param::Field::MAX_PLAYER]{ false };
	bool firstplaned = true;                                      //检查是否为第一次规划，即之前是否已经有规划好的路径
	int  countplan = 0;                                           //每隔一段时间清零，强制更新copyviapoints
	double flatVelFactor[Param::Field::MAX_PLAYER];
	CGeoPoint lastTarget[Param::Field::MAX_PLAYER];
	pair < vector < pair < stateNew, size_t > >, vector < pair < stateNew, size_t > > > tree[Param::Field::MAX_PLAYER];
	vector<CGeoPoint> viaPoints[Param::Field::MAX_PLAYER];
	vector<CGeoPoint> copyviaPoints[Param::Field::MAX_PLAYER];    //viaPoints备份，用于不重新规划时执行路径
	vector<CGeoPoint> pathPoints[Param::Field::MAX_PLAYER];
	stateNew nextState[Param::Field::MAX_PLAYER];
	BezierController controller[Param::Field::MAX_PLAYER];
	CRRTPathPlannerNew plannerNew[Param::Field::MAX_PLAYER];
	BSplinePlanner trajPlanner[Param::Field::MAX_PLAYER];
}
using namespace Param::Vehicle::V2;

CGotoPositionNew::CGotoPositionNew() {
	DRAW_RRT = paramManager->DRAW_RRT;
	DRAW_TRAJ = paramManager->DRAW_TRAJ;
	DRAW_OBS = paramManager->DRAW_OBS;
	BUFFER = paramManager->BUFFER;
	INFLAT_RATIO = paramManager->INFLAT_RATIO;
	LOWER_BND_UDOT = paramManager->LOWER_BND_UDOT;
	MAX_SEARCH_ITERATION = paramManager->MAX_SEARCH_ITERATION;
	COUNTPLAN_THRESHOLD = paramManager->COUNTPLAN_THRESHOLD;
	{
		// 守门员单独控制平动参数
		MAX_TRANSLATION_SPEED_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_SPEED_GOALIE;
		MAX_TRANSLATION_ACC_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_ACC_GOALIE;
		MAX_TRANSLATION_DEC_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_DEC_GOALIE;
		MAX_ROTATION_ACC_GOALIE = ParamManager::Instance()->MAX_ROTATION_ACC_GOALIE;
		MAX_ROTATION_SPEED_GOALIE = ParamManager::Instance()->MAX_ROTATION_SPEED_GOALIE;

		// 后卫单独控制平动参数
		MAX_TRANSLATION_SPEED_BACK = ParamManager::Instance()->MAX_TRANSLATION_SPEED_BACK;
		MAX_TRANSLATION_ACC_BACK = ParamManager::Instance()->MAX_TRANSLATION_ACC_BACK;
		MAX_TRANSLATION_DEC_BACK = ParamManager::Instance()->MAX_TRANSLATION_DEC_BACK;
		MAX_ROTATION_ACC_BACK = ParamManager::Instance()->MAX_ROTATION_ACC_BACK;
		MAX_ROTATION_SPEED_BACK = ParamManager::Instance()->MAX_ROTATION_SPEED_BACK;

		// 其他车的平动参数
		MAX_TRANSLATION_SPEED = ParamManager::Instance()->MAX_TRANSLATION_SPEED;
		MAX_TRANSLATION_ACC = ParamManager::Instance()->MAX_TRANSLATION_ACC;
		MAX_TRANSLATION_DEC = ParamManager::Instance()->MAX_TRANSLATION_DEC;

		MAX_ROTATION_SPEED = ParamManager::Instance()->MAX_ROTATION_SPEED;
		MAX_ROTATION_ACC = ParamManager::Instance()->MAX_ROTATION_ACC;

		TRANSLATION_ACC_LIMIT = ParamManager::Instance()->TRANSLATION_ACC_LIMIT;
	}
	anglePID.init(2, 0, 0);
}

void CGotoPositionNew::toStream(std::ostream& os) const {
	os << "Going to " << task().player.pos << " angle:" << task().player.angle;
}

void CGotoPositionNew::plan(const CVisionModule* pVision) {
	/************************************************************************/
	/* 任务参数解析                                                         */
	/************************************************************************/
	const int vecNumber = task().executor;
	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const double vecDir = me.Dir();
	playerFlag = task().player.flag;
	CGeoPoint targetPos = task().player.pos;
	CGeoPoint startPosForRRT = me.Pos();
	const bool isGoalie = vecNumber == TaskMediator::Instance()->goalie();
	const bool isBack = (vecNumber == TaskMediator::Instance()->leftBack())
		|| (vecNumber == TaskMediator::Instance()->rightBack());
	const double targetDir = task().player.angle;
	bool avoidOurBallPlacementArea = (WorldModel::Instance()->CurrentRefereeMsg() == "ourBallPlacement");
	bool avoidTheirBallPlacementArea = (WorldModel::Instance()->CurrentRefereeMsg() == "theirBallPlacement");
	bool avoidBallCircle = (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop") || (playerFlag & PlayerStatus::AVOID_STOP_BALL_CIRCLE);
	const bool shrinkTheirPenalty = false;
	PlayerCapabilityT capability = setCapability(pVision);
	int leaderNumber = paramManager->PlACEBALL_PLAYER_NUM;

	if (isBack || isGoalie) {
		BUFFER = 0.0;
	}
	double avoidDist = Param::Vehicle::V2::PLAYER_SIZE + BUFFER;
	ObstaclesNew* obs = new ObstaclesNew(avoidDist);
	obs->addObs(pVision, task(), DRAW_OBS, OPP_AVOID_DIST * INFLAT_RATIO, TEAMMATE_AVOID_DIST * INFLAT_RATIO, BALL_AVOID_DIST * INFLAT_RATIO);
	//对方放球需要避开球到放球点之间半径为50cm的圈//
	if (avoidTheirBallPlacementArea || (avoidOurBallPlacementArea && vecNumber != leaderNumber)) {
		CGeoPoint segP1 = pVision->Ball().Pos(), segP2(pVision->getBallPlacementPosition().x(), pVision->getBallPlacementPosition().y());
		bool addObs;
		targetPos = finalPointBallPlacement(me.Pos(), targetPos, segP1, segP2, avoidDist, *obs, addObs);
		//        if(addObs) {
		//            obsNew.addLongCircle(segP1, segP2, CVector(0.0, 0.0), ballPlacementDist, OBS_LONG_CIRCLE_NEW, false, true);
		//        }
		obs->drawLongCircle(segP1, segP2, ballPlacementDist);
	}

	//处理无效目标点:在禁区内、在车身内、在场地外//
	if (!avoidTheirBallPlacementArea)
		validateFinalTarget(targetPos, pVision, shrinkTheirPenalty, avoidDist, isGoalie);

	//躲避stop状态中的球圈//
	if (avoidBallCircle) {
		CGeoPoint ballPos = pVision->Ball().Pos();
		targetPos = Utils::MakeOutOfCircle(ballPos, stopBallAvoidDist, targetPos, avoidDist);
	}

	if ((pVision->GetCurrentRefereeMsg() == "ourIndirectKick" || pVision->GetCurrentRefereeMsg() == "ourDirectKick" || pVision->GetCurrentRefereeMsg() == "ourKickOff" || pVision->GetCurrentRefereeMsg() == "ourBallPlacement")) {
		PASS_PTS = false;
	}

	//将初始点远离障碍物，防止RRT规划失败//
	int stuckBuffer = 0;
	int stuckTres = 10;
	while (!validateStartPoint(startPosForRRT, avoidDist, isGoalie, obs) && stuckBuffer < stuckTres)
	{
		startPosForRRT = Utils::MakeOutOfTheirPenaltyArea(me.Pos(),100);
		stuckBuffer++;
		PASS_PTS = false;
	}
	if (stuckBuffer >= stuckTres)
	{
		GDebugEngine::Instance()->gui_debug_msg(me.Pos(), "nope, I'm stuck", COLOR_YELLOW);
	}

	if (DRAW_TRAJ) {
		//GDebugEngine::Instance()->gui_debug_arc(startPosForRRT, avoidDist, 0, 360, COLOR_ORANGE);
		//GDebugEngine::Instance()->gui_debug_x(targetPos, COLOR_YELLOW);
	}

	const CVector player2target = targetPos - me.Pos();
	const double dist = player2target.mod();

	//    CVector realVel((me.Pos().x() - meLast.Pos().x()) * Param::Vision::FRAME_RATE, (me.Pos().y() - meLast.Pos().y()) * Param::Vision::FRAME_RATE);
	stateNew start(me.Pos(), vecDir, me.Vel(), me.RotVel()); // nextState[vecNumber].vel, 
	stateNew startForRRT(startPosForRRT, vecDir, me.Vel(), me.RotVel());
	stateNew target(targetPos, targetDir, task().player.vel, task().player.rotvel);

	//    for(int i = 0; i < obs->getNum(); i++) {
	//        if(obs->obs[i].getType() == OBS_RECTANGLE_NEW && obs->obs[i].getStart().x() < 0.0)
	//            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0.0, 0.0), QString("%1").arg(obs->obs[i].check(CGeoSegment(me.Pos(), targetPos))).toLatin1());
	//    }
	//    cout << obs->getNum() << endl;

	bool newTarget = false;
	if (targetPos.dist(lastTarget[vecNumber]) > 1e-8) {
		newTarget = true;
		lastTarget[vecNumber] = targetPos;
	}
	//第一种情况：可以直接到目标//
	//if (obs->check(start.pos, target.pos) ||
	//	(me.Pos().dist(targetPos) < Param::Vehicle::V2::PLAYER_SIZE * 2)) {
	//	nextState[vecNumber] = target;
	//}
	//else {
		bool planned = false;
		//if (isBack) {
		//	viaPoints[vecNumber].clear();
		//	viaPoints[vecNumber].push_back(startForRRT.pos);
		//	vector < CGeoPoint > viaBack = forBack(pVision, vecNumber, me.Pos(), targetPos);
		//	//            if(viaBack.size() == 1 && (obs->check(startForRRT.pos, viaBack[0]) || obs->check(viaBack[0], targetPos))) {
		//	//                viaPoints[0].push_back(viaBack[0]);
		//	//                planned = true;
		//	//            }
		//	for (auto itor : viaBack) {
		//		viaPoints[vecNumber].push_back(itor);
		//	}
		//	planned = !viaBack.empty();
		//	viaPoints[vecNumber].push_back(targetPos);
		//}
		//if (!firstplaned) {
		//	if (countplan <= COUNTPLAN_THRESHOLD && obs->check(me.Pos(), nextState[vecNumber].pos) && me.Pos().dist(nextState[vecNumber].pos) >= 15 && copyviaPoints[vecNumber].size() != 0) //当前状态与下一状态之间无障碍物,距离大于一个车（防止在下一状态处停滞）且已有备份路径，不用重新规划
		//	{
		//		planned = true;
		//		countplan += 1;
		//	}
		//	else
		//	{
		//		planned = false;
		//		countplan = 0;
		//	}
		//}
		if (!planned) {
			//if (!plannerNew[vecNumber].plannerInitted())
				plannerNew[vecNumber].initPlanner(400, 20, 15, 0.05, 0.55, Param::Field::MAX_PLAYER_SIZE);
			plannerNew[vecNumber].planPath(obs, startForRRT, target);
			vector < stateNew > path = plannerNew[vecNumber].getPathPoints();
			viaPoints[vecNumber].clear();
			copyviaPoints[vecNumber].clear();
			if (path[0].pos.dist(me.Pos()) < 1e-8) {
				for (auto itor : path) {
					viaPoints[vecNumber].push_back(itor.pos);
					copyviaPoints[vecNumber].push_back(itor.pos);
				}
			}
			else {
				CVector dir1 = path[0].pos - me.Pos();
				CVector dir2 = path[1].pos - path[0].pos;
				viaPoints[vecNumber].push_back(me.Pos());
				copyviaPoints[vecNumber].push_back(me.Pos());
				//if start dir does not change much, omit first via point.
				int firstIdx = 0;
				if (fabs(Utils::Normalize(dir1.dir() - dir2.dir())) < angleToContri)
				{
					firstIdx = 1;
				}
				while (firstIdx < path.size()) {
					viaPoints[vecNumber].push_back(path[firstIdx].pos);
					copyviaPoints[vecNumber].push_back(path[firstIdx].pos);
					firstIdx++;
				}
			}
		}

		drawPath(DRAW_RRT, false, DRAW_TRAJ, vecNumber);
		if (viaPoints[vecNumber].size() < 3)//Bspline only deal with multiple-points motion planning
		{
		//	if (DRAW_TRAJ)
		//		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(170, -Param::Field::PITCH_WIDTH / 2), "GO_STRAIGHT", COLOR_CYAN);
		//	nextState[vecNumber] = target;
			CGeoPoint middlePoint = viaPoints[vecNumber][0].midPoint(viaPoints[vecNumber][1]);
			viaPoints[vecNumber].push_back(middlePoint);
		}
		//else
		//{
			// 自适应加速度
		static double lastPlayerVel = -1;
		static CGeoPoint lastPlayerPos;
		if (lastPlayerVel >= 0) {
			double currentDist = me.Pos().dist(lastPlayerPos);
			double currentDiff4V2 = me.Vel().mod() * me.Vel().mod() - lastPlayerVel * lastPlayerVel;
			double currentAcc = currentDiff4V2 / 2 / currentDist;
			double targetDist = nextState[vecNumber].pos.dist(lastPlayerPos);
			double targetDiff4V2 = nextState[vecNumber].vel.mod() * nextState[vecNumber].vel.mod() - lastPlayerVel * lastPlayerVel;
			double targetAcc = targetDiff4V2 / 2 / targetDist;
			if (targetAcc >= 0) {
				capability.maxAccel *= fabs(targetAcc / currentAcc);
				qDebug() << "has changed acc" << capability.maxAccel;
			}	
			else {
				capability.maxDec *= fabs(targetAcc / currentAcc);
				qDebug() << "has changed dec" << capability.maxDec;
			}			
		}
		lastPlayerPos = me.Pos();
		lastPlayerVel = me.Vel().mod();
			trajPlanner[vecNumber].initPlanner(viaPoints[vecNumber], capability, PASS_PTS);
			trajPlanner[vecNumber].smoothPath(start.vel, target.vel, LOWER_BND_UDOT, MAX_SEARCH_ITERATION, DRAW_TRAJ);
			trajPlanner[vecNumber].smoothPath(start.vel, 0.005, LOWER_BND_UDOT, MAX_SEARCH_ITERATION, DRAW_TRAJ);
			nextState[vecNumber] = trajPlanner[vecNumber].getNextState();
		//}
	//}


	if (DRAW_TRAJ) {
		GDebugEngine::Instance()->gui_debug_x(nextState[vecNumber].pos, COLOR_CYAN);
		//GDebugEngine::Instance()->gui_debug_line(nextState[vecNumber].pos, nextState[vecNumber].pos + nextState[vecNumber].vel, COLOR_BLUE);
		//GDebugEngine::Instance()->gui_debug_msg(nextState[vecNumber].pos, QString::number(nextState[vecNumber].vel.mod()).toStdString().c_str(), COLOR_BLUE);
	}
	firstplaned = false;

	//设置新的子任务//
	TaskT newTask(task());
	//newTask.player.pos = nextState[vecNumber].pos;
	//newTask.player.vel = nextState[vecNumber].vel;
	//setSubTask(TaskFactoryV2::Instance()->GotoPosition(newTask));
	
	newTask.player.speed_x = nextState[vecNumber].vel.x();
	newTask.player.speed_y = nextState[vecNumber].vel.y();
	// 角度环PID控制
	newTask.player.rotate_speed = anglePID.step(Utils::Normalize(task().player.angle - me.Dir()));
	if (newTask.player.rotate_speed > MAX_ROTATION_SPEED)
		newTask.player.rotate_speed = MAX_ROTATION_SPEED;
	else if (newTask.player.rotate_speed < -MAX_ROTATION_SPEED)
		newTask.player.rotate_speed = -MAX_ROTATION_SPEED;
	double rotAcc = Utils::Normalize(newTask.player.rotate_speed - me.RotVel());
	if (rotAcc > MAX_ROTATION_ACC)
		rotAcc = MAX_ROTATION_ACC;
	else if (rotAcc < -MAX_ROTATION_ACC)
		rotAcc = -MAX_ROTATION_ACC;
	newTask.player.rotate_speed = 0; // me.RotVel() + rotAcc;
	//std::cout << diff_angle << " " << newTask.player.rotate_speed << std::endl;
	setSubTask(TaskFactoryV2::Instance()->Speed(newTask));
	
	CPlayerTask::plan(pVision);
	return;
}

PlayerCapabilityT CGotoPositionNew::setCapability(const CVisionModule* pVision) {
	const int vecNumber = task().executor;
	const int playerFlag = task().player.flag;
	PlayerCapabilityT capability;

	// Traslation
	if (vecNumber == TaskMediator::Instance()->goalie()) {
		capability.maxSpeed = MAX_TRANSLATION_SPEED_GOALIE;
		capability.maxAccel = MAX_TRANSLATION_ACC_GOALIE;
		capability.maxDec = MAX_TRANSLATION_DEC_GOALIE;
		// Rotation	  确定转动运动参数//
		capability.maxAngularSpeed = MAX_ROTATION_SPEED_GOALIE;
		capability.maxAngularAccel = MAX_ROTATION_ACC_GOALIE;
		capability.maxAngularDec = MAX_ROTATION_ACC_GOALIE;
	}
	else if (TaskMediator::Instance()->leftBack() != 0 && vecNumber == TaskMediator::Instance()->leftBack()
		|| TaskMediator::Instance()->rightBack() != 0 && vecNumber == TaskMediator::Instance()->rightBack()
		|| TaskMediator::Instance()->singleBack() != 0 && vecNumber == TaskMediator::Instance()->singleBack()
		|| TaskMediator::Instance()->sideBack() != 0 && vecNumber == TaskMediator::Instance()->sideBack()) {
		capability.maxSpeed = MAX_TRANSLATION_SPEED_BACK;
		capability.maxAccel = MAX_TRANSLATION_ACC_BACK;
		capability.maxDec = MAX_TRANSLATION_DEC_BACK;
		// Rotation	  确定转动运动参数//
		capability.maxAngularSpeed = MAX_ROTATION_SPEED_BACK;
		capability.maxAngularAccel = MAX_ROTATION_ACC_BACK;
		capability.maxAngularDec = MAX_ROTATION_ACC_BACK;
	}
	else {
		capability.maxSpeed = MAX_TRANSLATION_SPEED;
		capability.maxAccel = MAX_TRANSLATION_ACC;
		capability.maxDec = MAX_TRANSLATION_DEC;
		// Rotation	  确定转动运动参数//
		capability.maxAngularSpeed = MAX_ROTATION_SPEED;
		capability.maxAngularAccel = MAX_ROTATION_ACC;
		capability.maxAngularDec = MAX_ROTATION_ACC;
	}


	if (task().player.max_acceleration > 1) {
		capability.maxAccel = task().player.max_acceleration > TRANSLATION_ACC_LIMIT ? TRANSLATION_ACC_LIMIT : task().player.max_acceleration;
		capability.maxDec = capability.maxAccel;
	}
	if (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop") {
		const BallVisionT ball = pVision->Ball();
		if (ball.Pos().x() < -240 && abs(ball.Pos().y()) > 150) {
			capability.maxSpeed = 100;
		}
		else {
			capability.maxSpeed = 150;
		}
	}

	return capability;
}

void CGotoPositionNew::validateFinalTarget(CGeoPoint& finalTarget, const CVisionModule* pVision, bool shrinkTheirPenalty, double avoidLength, bool isGoalie) {
	//free kick的时候需要多避对方禁区20cm//
	double theirPenaltyAvoidLength = avoidLength;
	if (playerFlag & PlayerStatus::FREE_KICK) {
		theirPenaltyAvoidLength += 20.0;
	}
	else if (!shrinkTheirPenalty) {
		theirPenaltyAvoidLength += Param::Vehicle::V2::PLAYER_SIZE;
	}
	//界外和禁区内的点调整进来//
	if (WorldModel::Instance()->CurrentRefereeMsg() != "ourBallPlacement" || !(playerFlag & PlayerStatus::NOT_DODGE_PENALTY)) {
		finalTarget = Utils::MakeInField(finalTarget, -avoidLength * 2);
		if (!isGoalie && Utils::InOurPenaltyArea(finalTarget, avoidLength))
			finalTarget = Utils::MakeOutOfOurPenaltyArea(finalTarget, avoidLength);
		if (Utils::InTheirPenaltyArea(finalTarget, theirPenaltyAvoidLength)) {
			finalTarget = Utils::MakeOutOfTheirPenaltyArea(finalTarget, theirPenaltyAvoidLength);
		}
	}
}

//bool CGotoPositionNew::validateStartPoint(CGeoPoint &startPos, const PlayerVisionT &me, ObstaclesNew *obst, const PlayerCapabilityT& capability, double avoidLength, bool isGoalie, bool isBack) {
//
//	CGeoPoint myPos = me.Pos();
//	if (WorldModel::Instance()->CurrentRefereeMsg() != "ourPenaltyKick" && WorldModel::Instance()->CurrentRefereeMsg() != "ourBallPlacement") {
//		if (!isGoalie && Utils::InOurPenaltyArea(startPos, avoidLength))
//			startPos = Utils::MakeOutOfOurPenaltyArea(startPos, avoidLength*3);
//		if (Utils::InTheirPenaltyArea(startPos, avoidLength))
//			startPos = Utils::MakeOutOfTheirPenaltyArea(startPos, avoidLength*3);
//	}
//
//	int obsNum = obst->getNum();
//	for (int i = 0; i < obsNum; i++) {
//		if (obst->obs[i].getType() != OBS_RECTANGLE_NEW && !obst->obs[i].check(startPos)) {
//			if (obst->obs[i].getType() == OBS_CIRCLE_NEW) {
//				if (startPos.dist(myPos) > (avoidLength + obst->obs[i].getRadius()) * 1.2) {
//					startPos = Utils::MakeOutOfCircle(obst->obs[i].getStart(), obst->obs[i].getRadius(), startPos, avoidLength);
//				}
//				else {
//					startPos = Utils::MakeOutOfCircle(obst->obs[i].getStart(), Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER, startPos, Param::Vehicle::V2::DRIBBLE_SIZE);
//				}
//			}
//			else {
//				if (startPos.dist(myPos) > (avoidLength + obst->obs[i].getRadius()) * 1.2) {
//					startPos = Utils::MakeOutOfLongCircle(obst->obs[i].getStart(), obst->obs[i].getEnd(), obst->obs[i].getRadius(), startPos, avoidLength);
//				}
//				else {
//					startPos = Utils::MakeOutOfLongCircle(obst->obs[i].getStart(), obst->obs[i].getEnd(), Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER, startPos, Param::Vehicle::V2::DRIBBLE_SIZE);
//				}
//			}
//		}
//	}
//	if (me.Vel().mod() < 20 || isBack) return true;
//	CVector meVel = me.Vel();
//	double distToStop = pow(meVel.mod(), 2) / (2 * capability.maxDec);
//	if (me.Vel().mod() > 250)
//		distToStop *= 2.0;
//	CVector adjustDir = meVel / meVel.mod();
//	CGeoPoint startPosNew = startPos + adjustDir * distToStop;
//
//	if (!obst->check(startPos, startPosNew)) return false;
//	if (me.Vel().mod() > minVelConstr)
//		startPos = startPosNew;
//	return true;
//}
bool CGotoPositionNew::validateStartPoint(CGeoPoint& startPoint, double avoidLength, bool isGoalie, ObstaclesNew* obs) {
	//PASS_PTS = false;  // 避免卡在球门里
	if (!(playerFlag & PlayerStatus::NOT_DODGE_PENALTY)) {
		if (!isGoalie && Utils::InOurPenaltyArea(startPoint, avoidLength))
			startPoint = Utils::MakeOutOfOurPenaltyArea(startPoint, avoidLength);
		if (Utils::InTheirPenaltyArea(startPoint, avoidLength)) {  //debug from chen siyuan 2021/3/17
			if (playerFlag & PlayerStatus::FREE_KICK) {
				startPoint = Utils::MakeOutOfTheirPenaltyArea(startPoint, 3 * avoidLength);
			}
			else {
				startPoint = Utils::MakeOutOfTheirPenaltyArea(startPoint, 3 * avoidLength);
			}

		}
	}
	CGeoPoint originStartPoint = startPoint;
	CVector adjustVec(0, 0);
	int obsNum = obs->getNum(), i = 0;
	for (i = 0; i < obsNum; i++) {
		if (!obs->obs[i].check(startPoint)) {

			if (obs->obs[i].getType() == OBS_CIRCLE_NEW) {
				adjustVec = adjustVec + Utils::Polar2Vector((avoidLength + obs->obs[i].getRadius() - obs->obs[i].getStart().dist(startPoint)), (startPoint - obs->obs[i].getStart()).dir());
			}
			else if (obs->obs[i].getType() == OBS_LONG_CIRCLE_NEW) {
				CGeoPoint nearPoint = obs->obs[i].getStart().dist(startPoint) > obs->obs[i].getEnd().dist(startPoint) ? obs->obs[i].getEnd() : obs->obs[i].getStart();
				adjustVec = adjustVec + Utils::Polar2Vector(avoidLength + obs->obs[i].getRadius() - nearPoint.dist(startPoint), (startPoint - nearPoint).dir());
			}
		}
	}

	if (obs->check(startPoint)) {
		return true;//out of obstacle, success 
	}
	else
	{
		double adjustStep = Param::Vehicle::V2::PLAYER_SIZE;
		double adjustVecMod = adjustVec.mod();
		if (abs(adjustVecMod) < 1e-5 || isnan(adjustVecMod)) adjustVecMod = 1.0;  // sqrt(0)bug from chen siyuan
		adjustVec = adjustVec / adjustVecMod;
		startPoint = startPoint + adjustVec * adjustStep;
		return false;//still in obstacle, failed
	}
}

vector < CGeoPoint > CGotoPositionNew::forBack(const CVisionModule* _pVision, const int vecNum, const CGeoPoint& startPos, const CGeoPoint& targetPos) {
	vector < CGeoPoint > result;
	result.clear();
	CGeoPoint anotherBack;
	CGeoPoint mePos = _pVision->OurPlayer(vecNum).Pos();
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (i != vecNum && (i == TaskMediator::Instance()->leftBack() ||
			i == TaskMediator::Instance()->rightBack()) &&
			_pVision->OurPlayer(i).Valid()) {
			anotherBack = _pVision->OurPlayer(i).Pos();
			break;
		}
	}
	CVector me2another = anotherBack - mePos;
	//GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0.0, 0.0), me2another.mod(), COLOR_GREEN);
	CGeoPoint candidate1(-455, -135), candidate2(-455, 135),
		candidateOut1(-450, -160), candidateOut2(-450, 160);
	if (startPos.x() < -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + Param::Vehicle::V2::PLAYER_SIZE &&
		targetPos.x() < -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + Param::Vehicle::V2::PLAYER_SIZE) {
		if (startPos.y() * targetPos.y() < 0.0) {
			if (startPos.y() < 0) {
				if (fabs(Utils::Normalize(me2another.dir() - (candidate1 - mePos).dir())) > Param::Math::PI / 2 || me2another.mod() > 4.0 * Param::Vehicle::V2::PLAYER_SIZE) {
					result.push_back(candidate1);
					result.push_back(candidate2);
				}
				else {
					result.push_back(CGeoPoint(startPos.x(), -160));
					result.push_back(candidateOut1);
					result.push_back(candidateOut2);
					result.push_back(CGeoPoint(targetPos.x(), 160));
				}
			}
			else {
				if (fabs(Utils::Normalize(me2another.dir() - (candidate2 - mePos).dir())) > Param::Math::PI / 2 || me2another.mod() > 4.0 * Param::Vehicle::V2::PLAYER_SIZE) {
					result.push_back(candidate2);
					result.push_back(candidate1);
				}
				else {
					result.push_back(CGeoPoint(startPos.x(), 160));
					result.push_back(candidateOut2);
					result.push_back(candidateOut1);
					result.push_back(CGeoPoint(targetPos.x(), -160));
				}
			}
		}
	}
	else if (!(startPos.x() > -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + Param::Vehicle::V2::PLAYER_SIZE &&
		targetPos.x() > -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + Param::Vehicle::V2::PLAYER_SIZE)) {
		if (startPos.x() < -Param::Field::PITCH_LENGTH / 2 +Param::Field::PENALTY_AREA_DEPTH + Param::Vehicle::V2::PLAYER_SIZE) {
			if (startPos.y() > 0) {
				if (fabs(Utils::Normalize(me2another.dir() - (candidate2 - mePos).dir())) > Param::Math::PI / 2 || me2another.mod() > 4.0 * Param::Vehicle::V2::PLAYER_SIZE)
					result.push_back(candidate2);
				else {
					result.push_back(CGeoPoint(startPos.x(), 160));
					result.push_back(candidateOut2);
					result.push_back(CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + 160, targetPos.y()));
				}
			}
			else {
				if (fabs(Utils::Normalize(me2another.dir() - (candidate1 - mePos).dir())) > Param::Math::PI / 2 || me2another.mod() > 4.0 * Param::Vehicle::V2::PLAYER_SIZE)
					result.push_back(candidate1);
				else {
					result.push_back(CGeoPoint(startPos.x(), -160));
					result.push_back(candidateOut1);
					result.push_back(CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + 160, targetPos.y()));
				}
			}
		}
		else {
			if (targetPos.y() > 0) {
				if (fabs(Utils::Normalize(me2another.dir() - (candidate2 - mePos).dir())) > Param::Math::PI / 2 || me2another.mod() > 4.0 * Param::Vehicle::V2::PLAYER_SIZE)
					result.push_back(candidate2);
				else {
					result.push_back(CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + 160, startPos.y()));
					result.push_back(candidateOut2);
					result.push_back(CGeoPoint(targetPos.x(), 160));
				}
			}
			else {
				if (fabs(Utils::Normalize(me2another.dir() - (candidate1 - mePos).dir())) > Param::Math::PI / 2 || me2another.mod() > 4.0 * Param::Vehicle::V2::PLAYER_SIZE)
					result.push_back(candidate1);
				else {
					result.push_back(CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + 160, startPos.y()));
					result.push_back(candidateOut1);
					result.push_back(CGeoPoint(targetPos.x(), -160));
				}
			}
		}
	}
	return result;
}

void CGotoPositionNew::drawPath(bool drawPathPoints, bool drawPathLine, bool drawViaPoints, int vecNumber) {

	tree[vecNumber] = plannerNew[vecNumber].getNodes();
	for (size_t i = 1; drawPathPoints && !tree[vecNumber].first.empty() && i < tree[vecNumber].first.size(); i += 1) {
		//GDebugEngine::Instance()->gui_debug_line(tree[vecNumber].first[i].first.pos, tree[vecNumber].first[tree[vecNumber].first[i].second].first.pos, COLOR_GREEN);
		GDebugEngine::Instance()->gui_debug_x(tree[vecNumber].first[i].first.pos, COLOR_GREEN);
	}
	for (size_t i = 1; drawPathPoints && !tree[vecNumber].second.empty() && i < tree[vecNumber].second.size(); i++) {
		//GDebugEngine::Instance()->gui_debug_line(tree[vecNumber].second[i].first.pos, tree[vecNumber].second[tree[vecNumber].second[i].second].first.pos, COLOR_YELLOW);
		GDebugEngine::Instance()->gui_debug_x(tree[vecNumber].second[i].first.pos, COLOR_YELLOW);
	}

	for (int i = 0; drawViaPoints && i < viaPoints[vecNumber].size(); i++) {
		GDebugEngine::Instance()->gui_debug_arc(viaPoints[vecNumber][i], Param::Vehicle::V2::PLAYER_SIZE, 0, 360, COLOR_GREEN);
	}
}

CGeoPoint CGotoPositionNew::finalPointBallPlacement(const CGeoPoint& startPoint, const CGeoPoint& target, const CGeoPoint& segPoint1, const CGeoPoint& segPoint2, const double avoidLength, ObstaclesNew& obst, bool& canDirect) {
	CGeoPoint targetNew = target;
	CGeoPoint projectionPoint = CGeoPoint(1e8, 1e8);
	CGeoSegment obsSegment(segPoint1, segPoint2);
	CGeoSegment pathLine(startPoint, target);
	double obsRadius = ballPlacementDist;
	const double CAN_PASS_ANGLE = Param::Math::PI / 9;
	CVector segVec = segPoint1 - segPoint2;
	CVector adjustDir = segVec.rotate(Param::Math::PI / 2).unit();
	double adjustStep = 5.0;
	double avoidBuffer = 60;
	canDirect = true;

	///情况1：自己和目标都在区域内，把自己移出区域并作为新的目标点；//
	if (obsSegment.dist2Point(startPoint) < obsRadius + avoidLength /*&&
			obsSegment.dist2Point(target) < obsRadius + avoidLength*/) {
		GDebugEngine::Instance()->gui_debug_msg(startPoint, "Me In, Target In", COLOR_ORANGE);
		targetNew = startPoint;
		projectionPoint = startPoint;
		while (obsSegment.dist2Point(targetNew) < obsRadius + avoidLength) {
			targetNew = targetNew + adjustDir * adjustStep;
		}
		if (targetNew.dist(startPoint) > obsRadius + avoidLength) {
			adjustDir = -adjustDir;
			targetNew = targetNew + (adjustDir) * (2 * (obsRadius + avoidLength + adjustStep));
		}
		targetNew = targetNew + adjustDir * avoidBuffer;
		CGeoPoint originTargetNew = targetNew;
		double adjustBuffer = avoidBuffer;
		while (!Utils::IsInField(targetNew, 0) ||
			Utils::InOurPenaltyArea(targetNew, avoidLength) ||
			Utils::InTheirPenaltyArea(targetNew, avoidLength)) {
			targetNew = targetNew + (adjustDir) * (2 * (obsRadius + avoidLength + adjustStep + adjustBuffer));
			adjustBuffer -= 10;
			if (adjustBuffer < 10) break;
		}

		adjustDir = -adjustDir;
		adjustBuffer = avoidBuffer;
		targetNew = originTargetNew;
		while (!Utils::IsInField(targetNew, 0) ||
			Utils::InOurPenaltyArea(targetNew, avoidLength) ||
			Utils::InTheirPenaltyArea(targetNew, avoidLength)) {
			targetNew = targetNew + (adjustDir) * (2 * (obsRadius + avoidLength + adjustStep + adjustBuffer));
			adjustBuffer -= 10;
			if (adjustBuffer < 10) break;
		}
		//        targetNew = targetNew + adjustDir * avoidBuffer;
		if (avoidBuffer < 10)
			targetNew = CGeoPoint(0.0, 0.0);
		canDirect = false;
	}

	///情况2： 自己在区域外，目标在区域内，将目标移动到己方区域边界//
	else if (obsSegment.dist2Point(startPoint) > obsRadius + avoidLength &&
		obsSegment.dist2Segment(pathLine) < obsRadius + avoidLength) {
		GDebugEngine::Instance()->gui_debug_msg(startPoint, "Me Out, Target In", COLOR_ORANGE);
		targetNew = target;
		projectionPoint = startPoint;
		targetNew = startPoint;
		//        while(obsSegment.dist2Point(targetNew) < obsRadius + avoidLength)
		//            targetNew = targetNew + adjustDir * adjustStep;
		//        if(obsSegment.dist2Segment(CGeoSegment(startPoint, targetNew)) < obsRadius + avoidLength) {
		//            adjustDir = -adjustDir;
		//            targetNew = targetNew + (adjustDir) * (2 * (obsRadius + avoidLength + adjustStep));
		//        }
		//        targetNew = targetNew + adjustDir * avoidBuffer;
		//        if(!Utils::IsInField(targetNew, avoidLength) || Utils::InOurPenaltyArea(targetNew, avoidLength) || Utils::InTheirPenaltyArea(targetNew, avoidLength)) {
		//            adjustDir = -adjustDir;
		//            targetNew = targetNew + (adjustDir) * (2 * (obsRadius + avoidLength + adjustStep) + avoidBuffer);
		//        }
		//        targetNew = targetNew + adjustDir * avoidBuffer;
		canDirect = false;
	}

	///情况3：自己和目标点都在区域外，且分居区域两侧，将自己尽可能向靠近目标点的区域外同侧移动//
	else if (obsSegment.dist2Point(startPoint) > obsRadius + avoidLength && obsSegment.dist2Point(target) > obsRadius + avoidLength && obsSegment.dist2Segment(CGeoSegment(startPoint, target)) < obsRadius + avoidLength) {
		GDebugEngine::Instance()->gui_debug_msg(startPoint, "Me Out, Target Out", 0);
		targetNew = startPoint;
		projectionPoint = target;
		CVector adjustDir2 = segVec.unit();
		CVector me2Target = target - startPoint;
		if (fabs(fabs(Utils::Normalize(me2Target.dir() - adjustDir2.dir())) - Param::Math::PI / 2) < CAN_PASS_ANGLE) return target;
		if (adjustDir2 * me2Target < 0)
			adjustDir2 = -adjustDir2;
		while (me2Target * adjustDir2 > 0) {
			targetNew = targetNew + adjustDir2 * adjustStep;
			me2Target = target - targetNew;
		}
		if (obsSegment.dist2Point(targetNew) > obsRadius + avoidLength + adjustStep) {
			if (obsSegment.dist2Point(targetNew + adjustDir) < obsSegment.dist2Point(targetNew)) {
				targetNew = targetNew + adjustDir * (obsSegment.dist2Point(targetNew) - obsRadius - avoidLength - adjustStep);
			}
			else {
				targetNew = targetNew + (-adjustDir) * (obsSegment.dist2Point(targetNew) - obsRadius - avoidLength - adjustStep);
			}
		}

	}

	///情况4：自己在区域内，目标在区域外，新目标点为目标点向自己方向移动的区域边界对应点//
	else if (obsSegment.dist2Point(startPoint) < obsRadius + avoidLength && obsSegment.dist2Point(target) > obsRadius + avoidLength) {
		GDebugEngine::Instance()->gui_debug_msg(startPoint, "Me In, Target Out", 0);
		targetNew = target;
		projectionPoint = startPoint;
		CVector adjustDir2 = segVec.unit();
		CVector target2Me = startPoint - targetNew;
		if (fabs(fabs(Utils::Normalize(target2Me.dir() - adjustDir2.dir())) - Param::Math::PI / 2) < CAN_PASS_ANGLE) return target;
		if (adjustDir2 * target2Me < 0)
			adjustDir2 = -adjustDir2;
		while (target2Me * adjustDir2 > 0) {
			targetNew = targetNew + adjustDir2 * adjustStep;
			target2Me = startPoint - targetNew;
		}
		if (obsSegment.dist2Point(targetNew) > obsRadius + avoidLength + adjustStep) {
			if (obsSegment.dist2Point(targetNew + adjustDir) < obsSegment.dist2Point(targetNew))
				targetNew = targetNew + adjustDir * (obsSegment.dist2Point(targetNew) - obsRadius - avoidLength - adjustStep);
			else
				targetNew = targetNew + (-adjustDir) * (obsSegment.dist2Point(targetNew) - obsRadius - avoidLength - adjustStep);
		}
	}
	///如果前面初步调整得到的目标点在障碍物中，则进一步搜索//
//    if(!obst.check(targetNew)) {
//        CGeoPoint originTargetNew = targetNew;
//        CVector xAdjustDir = segVec.unit();
//        CVector yAdjustDir;
//        if(Utils::IsInField(projectionPoint, -20))
//            yAdjustDir = (targetNew - projectionPoint).unit();
//        else
//            yAdjustDir = adjustDir;
//        if(obsSegment.dist2Point(targetNew) > obsSegment.dist2Point(targetNew + yAdjustDir))
//            yAdjustDir = -adjustDir;
//        double totalAvoidDist = 0.0;
//        double maxAvoidDist = 100;
//        adjustStep = 9.0;
//        bool reversed = false;
//        while(totalAvoidDist < maxAvoidDist && !obst.check(targetNew)) {
//            targetNew = targetNew + xAdjustDir * adjustStep;
//            CVector testVec = targetNew - projectionPoint;
//            if(fabs(fabs(Utils::Normalize(testVec.dir() - xAdjustDir.dir())) - Param::Math::PI / 2) > CAN_PASS_ANGLE / 1.5) {
//                if(!reversed) {
//                    xAdjustDir = -xAdjustDir;
//                    targetNew = originTargetNew;
//                    reversed = true;
//                } else {
//                    targetNew = originTargetNew = originTargetNew + yAdjustDir * adjustStep;
//                    totalAvoidDist += adjustStep;
//                    reversed = false;
//                }
//            }
//        }
//        if(!obst.check(targetNew) && obsSegment.dist2Point(startPoint) > obsRadius + avoidLength)
//            targetNew = startPoint;
//    }

	return targetNew;
}