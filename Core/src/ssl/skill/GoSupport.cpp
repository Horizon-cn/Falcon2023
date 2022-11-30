#include "GoSupport.h"
#include <Vision/VisionModule.h>
#include <WorldModel/KickStatus.h>
#include "RobotSensor.h"
#include "skill/Factory.h"
#include <WorldModel/WorldModel.h>
#include "WorldModel/DribbleStatus.h"
#include <utils.h>
#include <GDebugEngine.h>
#include <iostream>
#include <TaskMediator.h>
#include "PassRangeList.h"


namespace {
	CGeoPoint goalPoint(Param::Field::PITCH_LENGTH, 0);
	CGeoLine endLine(CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::PITCH_WIDTH / 2), -1.57);
	CGeoLine myEndLine(CGeoPoint(-Param::Field::PITCH_LENGTH / 2, -Param::Field::PITCH_WIDTH / 2), -1.57);
	CGeoLine leftSideLine(CGeoPoint(0, -Param::Field::PITCH_WIDTH / 2 + 20), 0);
	CGeoLine rightSideLine(CGeoPoint(0, Param::Field::PITCH_WIDTH / 2 - 20), 0);
}

CGoSupport::CGoSupport() {

}

CGoSupport::~CGoSupport() {

}

void CGoSupport::plan(const CVisionModule* pVision)
{
	/********************************************************************************************/
	/*  划分进攻区域，指定当前车状态			  Modified by JLC                                   */
	/********************************************************************************************/

	int robotNum = task().executor;
	bool leftOrRight = task().player.left_or_right; // 0:右侧区域 1:左侧区域
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const BallVisionT& ball = pVision->Ball();
	const CGeoPoint& ballPos = ball.Pos();
	const CVector& ballVel = ball.Vel();
	int intersectArea = 0;   // 0:未相交 1:与左侧区域相交 2;与右侧区域相交
	bool waitingBall = 0;   // 是否在球速的延长线上等球
	bool roleChange = 0;
	bool hasSelfClosePlayer = 0;	//当前场上有可以和自己配合的车（距离近）


	CGeoPoint taskPoint(0,0);
	float taskDir = 0;

	if (leftOrRight) {
		roleChange = ((_lastLeftPlayerPos - me.Pos()).mod() > 20);
		_lastLeftPlayerPos = me.Pos();
	}
	else {
		roleChange = ((_lastRightPlayerPos - me.Pos()).mod() > 20);
		_lastRightPlayerPos = me.Pos();
	}
	
	//计算hasSelfClosePlayer
	for (int i = 0; i < Param::Field::MAX_PLAYER; ++i) {
		if (pVision->OurPlayer(i).Valid()) {
			CGeoPoint selfPlayerPos = pVision->OurPlayer(i).Pos();
			CGeoLine ballRuningLine(ballPos, ballVel.dir());	// 球速的延长线
			CGeoPoint proPoint = ballRuningLine.projection(selfPlayerPos);	// 当前球员关于球速线的对称点
			double dist = proPoint.dist(selfPlayerPos);
			if (dist < 30 && abs(pVision->OurPlayer(i).Dir() - ballVel.dir()) > Param::Math::PI / 6 ){	
				hasSelfClosePlayer = 1;
				break;
			}
		}
	}

	TaskT myTask(task());
	myTask.player.angle = 0.0;
	myTask.player.pos = CGeoPoint(0, 0);

	if (ballVel.mod() > 50) {
		intersectArea = isectSeg(pVision);
	}

	bool ballRunningMe = (intersectArea == 1 && leftOrRight == 1) || (intersectArea == 2 && leftOrRight == 0);
	//球速指向本球员区域时，ballRunningMe = 1
	waitingBall = (ballVel.mod() > 50) && ballRunningMe;
	
	/********************************************************************************************/
	/*  制定task，执行进攻任务，此处调用SupportPos2022		Modified by JLC                         */
	/********************************************************************************************/

	//充当支援车
	if (!waitingBall) {
		if (leftOrRight) {
			taskPoint = SupportPos2022::Instance()->getSupportPos(pVision).getLeftSupportPos();
			double dir1 = (goalPoint - taskPoint).dir();
			double dir2 = (ballPos - taskPoint).dir();
			taskDir = (dir1 + dir2) / 2;
			if (taskDir * dir1 < 0) {
				taskDir += 3.14;
			}
		}
		else {
			taskPoint = SupportPos2022::Instance()->getSupportPos(pVision).getRightSupportPos();
			double dir1 = (goalPoint - taskPoint).dir();
			double dir2 = (ballPos - taskPoint).dir();
			taskDir = (dir1 + dir2) / 2;
			if (taskDir * dir1 < 0) {
				taskDir += 3.14;
			}
		}
	}

	else {
		if (hasSelfClosePlayer) {	
			// 附近有支援车
			CVector actualVector(-100, 0);
			taskPoint = ballPos + actualVector;
			taskDir = (goalPoint - me.Pos()).dir();
			if (!leftOrRight) {
				taskDir += Param::Math::PI;
			}
		}
		else if (leftOrRight) {	//左侧区域
			if (intersectArea == 1) {
				double middleDir = ballVel.dir();
				CGeoLine ballRuningLine(ballPos, middleDir);
				double maxDist = calcMaxDist(pVision, middleDir, ballRuningLine);
				CVector actualVector(0.7 * maxDist * cos(middleDir), 0.7 * maxDist * sin(middleDir));
				taskPoint = ballPos + actualVector;
				taskDir = middleDir + Param::Math::PI;
			}
			else {
				taskPoint = SupportPos2022::Instance()->getSupportPos(pVision).getLeftSupportPos();
				double dir1 = (goalPoint - taskPoint).dir();
				double dir2 = (ballPos - taskPoint).dir();
				taskDir = (dir1 + dir2) / 2;
				if (taskDir * dir1 < 0) {
					taskDir += 3.14;
				}
			}
		}
		else {	//右侧区域
			if (intersectArea == 2) {
				double middleDir = ballVel.dir();
				CGeoLine ballRuningLine(ballPos, middleDir);
				double maxDist = calcMaxDist(pVision, middleDir, ballRuningLine);
				CVector actualVector(0.7 * maxDist * cos(middleDir), 0.7 * maxDist * sin(middleDir));
				taskPoint = ballPos + actualVector;
				taskDir = middleDir + Param::Math::PI;
			}
			else {
				taskPoint = SupportPos2022::Instance()->getSupportPos(pVision).getRightSupportPos();
				double dir1 = (goalPoint - taskPoint).dir();
				double dir2 = (ballPos - taskPoint).dir();
				taskDir = (dir1 + dir2) / 2;

				if (taskDir * dir1 < 0) {
					taskDir += 3.14;
				}
			}
		}
	}

	if (waitingBall) {
		GDebugEngine::Instance()->gui_debug_msg(taskPoint, "WAITING BALL");
	}
	else {
		GDebugEngine::Instance()->gui_debug_msg(taskPoint, "NOT WAITING BALL");
	}

	// 注意，生成的位置在这里发生了改变
	// 如果不在这里处理，那么可能由于球位置发生的剧烈变化导致目标位置过于不连续
	// 并且在一些情况下目标位置与advance位置过于接近，需要进行特殊处理
	// 因此选择20CM的步长，逐步使其到达目标点
	float stepDist = 50;
	CVector targetVector = taskPoint - me.Pos();
	if (targetVector.mod() > stepDist) {
		taskPoint = me.Pos() + targetVector.unit() * stepDist;
	}

	myTask.player.pos = taskPoint;
	myTask.player.angle = taskDir;

	setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(myTask));
	CPlayerTask::plan(pVision);
}


CPlayerCommand* CGoSupport::execute(const CVisionModule* pVision)
{
	if (subTask()) {
		return subTask()->execute(pVision);
	}
	return NULL;
}

/********************************************************************************************/
/*  计算进攻区域，返回值传向intersectArea  Modified by JLC                                    */ 
/********************************************************************************************/
int CGoSupport::isectSeg(const CVisionModule* pVision) {
	// 0:未相交 1:与左侧区域相交 2;与右侧区域相交
	const BallVisionT& ball = pVision->Ball();
	const CGeoPoint& ballPos = ball.Pos();
	float ballPosX = ballPos.x();
	float ballPosY = ballPos.y();
	const CVector& ballVel = ball.Vel();
	float ballVelX = ballVel.x();
	float ballVelY = ballVel.y();

	// 判断是否有可能直接进球，若是球朝球门飞去，则返回 0
	// 球与左右门柱的夹角
	float leftBoundaryDir = (CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2) - ballPos).dir();
	float rightBoundaryDir = (CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2) - ballPos).dir();
	if (ballVel.dir() < rightBoundaryDir && ballVel.dir() > leftBoundaryDir) {
		return 0;
	}

	// 判断与左侧区域是否相交
	if (ballPosX > 0 && ballPosY < -Param::Field::PENALTY_AREA_WIDTH / 2) {	
		// 球在该左侧区域里
		return 1;
	}
	else { // 球不在左侧区域里
		if (abs(ballVelX) < 1e-6 && ballVelY < 0 && ballPosX > 0) { 
			// 往左滚的球
			return 1;
		}
		else if (abs(ballVelY) < 1e-6 && ballVelX > 0 && ballPosY < -Param::Field::PENALTY_AREA_WIDTH / 2) {	
			// 左路往前滚
			return 1;
		}
		else {
			float t1 = (-Param::Field::PENALTY_AREA_WIDTH / 2 - ballPosY) / ballVelY;
			float t2 = (-Param::Field::PITCH_WIDTH / 2 - ballPosY) / ballVelY;

			float t3 = -ballPosX / ballVelX;
			float t4 = (Param::Field::PITCH_LENGTH / 2 - ballPosX) / ballVelX;

			if (t1 > t2) { float tmp = t2; t2 = t1; t1 = tmp; }
			if (t3 > t4) { float tmp = t4; t4 = t3; t3 = tmp; }
			
			float tmp = max(t1, t3);
			float tmin = max(tmp, 0.0f);
			float tmax = min(t2, t4);

			if (tmin < tmax) {	
				//到左宽度边界的时间比深度更短
				return 1;
			}
		}
	}
	// 判断与右侧区域是否相交
	if (ballPosX > 0 && ballPosY > Param::Field::PENALTY_AREA_WIDTH / 2) { 
		// 球在右侧区域里
		return 2;
	}
	else { 
		// 球不在右侧区域里
		if (abs(ballVelX) < 1e-6 && ballVelY > 0 && ballPosX > 0) {
			return 2;
		}
		else if (abs(ballVelY) < 1e-6 && ballVelX > 0 && ballPosY > Param::Field::PENALTY_AREA_WIDTH / 2) {
			return 2;
		}
		else {
			float t1 = (Param::Field::PENALTY_AREA_WIDTH / 2 - ballPosY) / ballVelY;
			float t2 = (Param::Field::PITCH_WIDTH / 2 - ballPosY) / ballVelY;

			float t3 = -ballPosX / ballVelX;
			float t4 = (Param::Field::PITCH_LENGTH / 2 - ballPosX) / ballVelX;

			if (t1 > t2) { float tmp = t2; t2 = t1; t1 = tmp; }
			if (t3 > t4) { float tmp = t4; t4 = t3; t3 = tmp; }

			float tmp = max(t1, t3);
			float tmin = max(tmp, 0.0f);
			float tmax = min(t2, t4);

			if (tmin < tmax) {	
				//到右宽度边界的时间比深度更短
				return 2;
			}
		}
	}
	return 0;
}

/********************************************************************************************/
/*  计算进攻区域，返回值传向intersectArea  Modified by JLC                                    */
/********************************************************************************************/
double CGoSupport::calcMaxDist(const CVisionModule* pVision, double middleDir, CGeoLine angleBisector) {
	CGeoPoint ballPos = (pVision->Ball()).Pos();
	double maxDist = 0;
	if (middleDir > 0 && middleDir < 1.57) {
		CGeoLineLineIntersection cross1(angleBisector, rightSideLine);
		CGeoPoint point1 = cross1.IntersectPoint();
		CGeoLineLineIntersection cross2(angleBisector, endLine);
		CGeoPoint point2 = cross2.IntersectPoint();
		maxDist = min(ballPos.dist(point1), ballPos.dist(point2));
	}
	else if (middleDir >= 1.57) {
		CGeoLineLineIntersection cross1(angleBisector, rightSideLine);
		CGeoPoint point1 = cross1.IntersectPoint();
		CGeoLineLineIntersection cross2(angleBisector, myEndLine);
		CGeoPoint point2 = cross2.IntersectPoint();
		maxDist = min(ballPos.dist(point1), ballPos.dist(point2));
	}
	else if (middleDir <= 0 && middleDir > -1.57) {
		CGeoLineLineIntersection cross1(angleBisector, leftSideLine);
		CGeoPoint point1 = cross1.IntersectPoint();
		CGeoLineLineIntersection cross2(angleBisector, endLine);
		CGeoPoint point2 = cross2.IntersectPoint();
		maxDist = min(ballPos.dist(point1), ballPos.dist(point2));
	}
	else {
		CGeoLineLineIntersection cross1(angleBisector, leftSideLine);
		CGeoPoint point1 = cross1.IntersectPoint();
		CGeoLineLineIntersection cross2(angleBisector, myEndLine);
		CGeoPoint point2 = cross2.IntersectPoint();
		maxDist = min(ballPos.dist(point1), ballPos.dist(point2));
	}
	return maxDist;
}

