#include <Vision/VisionModule.h>
#include <WorldModel/RobotCapability.h>
#include <TaskMediator.h>
#include "PassRangeList.h"
#include "param.h"

namespace {
	
}

/********************************************************************************************/
/*  返回当前ballPos不被对方车阻挡的RangeList（离散列表） 	Modified by JLC                     */
/********************************************************************************************/
CPassRangeList::CPassRangeList(const CVisionModule* pVision)
{
	if (lastCycle != pVision->Cycle()) { // 重新计算
		lastCycle = pVision->Cycle();

		lastLeftPassList.clear(); // 清空
		lastRightPassList.clear(); // 清空
		
		CGeoPoint startPos = pVision->Ball().Pos();
		CGeoPoint leftLeftPost, leftRightPost, rightLeftPost, rightRightPost;
		if (startPos.x() < -200) {
			leftLeftPost.fill(0, -Param::Field::PITCH_WIDTH / 2);
			leftRightPost.fill(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2);

			rightLeftPost.fill(Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2);
			rightRightPost.fill(0, Param::Field::PITCH_WIDTH / 2);
		}
		else {
			if (startPos.y() > Param::Field::PENALTY_AREA_WIDTH / 2) {
				leftLeftPost.fill(0, -Param::Field::PITCH_WIDTH / 2);
				leftRightPost.fill(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2);

				rightLeftPost.fill(Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2);
				rightRightPost.fill(Param::Field::PITCH_LENGTH / 2, Param::Field::PITCH_WIDTH / 2);
			}
			else if (startPos.y() < -Param::Field::PENALTY_AREA_WIDTH / 2) {
				leftLeftPost.fill(Param::Field::PITCH_LENGTH / 2, -Param::Field::PITCH_WIDTH / 2);
				leftRightPost.fill(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2);

				rightLeftPost.fill(Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2);
				rightRightPost.fill(0, Param::Field::PITCH_WIDTH / 2);
			}
			else {
				leftLeftPost.fill(Param::Field::PITCH_LENGTH / 2, -Param::Field::PITCH_WIDTH / 2);
				leftRightPost.fill(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2);

				rightLeftPost.fill(Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2);
				rightRightPost.fill(Param::Field::PITCH_LENGTH / 2, Param::Field::PITCH_WIDTH / 2);
			}
		}

		const double leftLeftPostAngle = (leftLeftPost - startPos).dir();
		const double leftRightPostAngle = (leftRightPost - startPos).dir();
		lastLeftPassList.add(CValueRange(leftLeftPostAngle, leftRightPostAngle)); // 初始化
		const double rightLeftPostAngle = (rightLeftPost - startPos).dir();
		const double rightRightPostAngle = (rightRightPost - startPos).dir();
		lastRightPassList.add(CValueRange(rightLeftPostAngle, rightRightPostAngle)); // 初始化

		//做减法挑选区域
		for (int i = 0; i < Param::Field::MAX_PLAYER; ++i) {
			if (pVision->TheirPlayer(i).Valid() && pVision->TheirPlayer(i).X() > startPos.x()) {
				const CGeoPoint& playerPos = pVision->TheirPlayer(i).Pos();
				const CVector startPos2player = playerPos - startPos;
				const double playerDist = startPos2player.mod() - Param::Field::MAX_PLAYER_SIZE / 2;
				const double playerDir = startPos2player.dir();
				const double angleRange = (playerDist <= Param::Field::MAX_PLAYER_SIZE / 2 ? Param::Math::PI / 2 : std::asin(Param::Field::MAX_PLAYER_SIZE / 2 / playerDist)); // 挡住的角度
				if (playerDist < 15) {
					continue; // 敌方围住车时，不考虑敌方对球的阻挡
				}
				lastLeftPassList.removeAngleRange(playerDir, angleRange, playerDist);
				lastRightPassList.removeAngleRange(playerDir, angleRange, playerDist);
			}
		}

		//if (startPos.x() < 250 && abs(startPos.y()) < 180) {
		//	// 只考虑在自己前方的传球位置
		//	const CGeoPoint leftPost(startPos.x(), -Param::Field::PITCH_WIDTH / 2);
		//	const CGeoPoint rightPost(startPos.x(), Param::Field::PITCH_WIDTH / 2);
		//	const double leftPostAngle = (leftPost - startPos).dir();
		//	const double rightPostAngle = (rightPost - startPos).dir();
		//	const double leftPostDist = (leftPost - startPos).mod();
		//	const double rightPostDist = (rightPost - startPos).mod();

		//	// 不考虑通过禁区的范围
		//	const CGeoPoint leftRemovePost(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH, -Param::Field::PENALTY_AREA_WIDTH / 2);
		//	const CGeoPoint rightRemovePost(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH, Param::Field::PENALTY_AREA_WIDTH / 2);
		//	const double leftRemovePostAngle = (leftRemovePost - startPos).dir();
		//	const double rightRemovePostAngle = (rightRemovePost - startPos).dir();
		//	const double leftRemovePostDist = (leftRemovePost - startPos).mod();
		//	const double rightRemovePostDist = (rightRemovePost - startPos).mod();


		//	lastPassList.add(CValueRange(leftPostAngle, rightPostAngle, leftPostDist, rightPostDist)); // 初始化
		//	lastPassList.remove(CValueRange(leftRemovePostAngle, rightRemovePostAngle)); // 去除经过禁区的部分
		//	lastPassList.remove(CValueRange(1.04, 1.6));
		//	lastPassList.remove(CValueRange(-1.6, -1.04));
		//	for (int i = 0; i < Param::Field::MAX_PLAYER; ++i) {
		//		if (pVision->TheirPlayer(i).Valid() && pVision->TheirPlayer(i).X() > startPos.x()) {
		//			const CGeoPoint& playerPos = pVision->TheirPlayer(i).Pos();
		//			const CVector startPos2player = playerPos - startPos;
		//			const double playerDist = startPos2player.mod() - Param::Field::MAX_PLAYER_SIZE / 2;
		//			const double playerDir = startPos2player.dir();
		//			const double angleRange = (playerDist <= Param::Field::MAX_PLAYER_SIZE / 2 ? Param::Math::PI / 2 : std::asin(Param::Field::MAX_PLAYER_SIZE / 2 / playerDist)); // 挡住的角度
		//			if (playerDist < 15) {
		//				continue; // 敌方围住车时，不考虑敌方对球的阻挡
		//			}
		//			lastPassList.removeAngleRange(playerDir, angleRange, playerDist);
		//		}
		//	}
		//}
		//else {
		//	if (startPos.y() > 0){
		//		// 初始传球范围
		//		const CGeoPoint leftPost(0, -Param::Field::PITCH_WIDTH / 2);
		//		const CGeoPoint rightPost(Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2);
		//		const double leftPostAngle = (leftPost - startPos).dir();
		//		const double rightPostAngle = (rightPost - startPos).dir();
		//		const double leftPostDist = (leftPost - startPos).mod();
		//		const double rightPostDist = (rightPost - startPos).mod();

		//		lastPassList.add(CValueRange(leftPostAngle, rightPostAngle, leftPostDist, rightPostDist)); // 初始化
		//		for (int i = 0; i < Param::Field::MAX_PLAYER; ++i) {
		//			if (pVision->TheirPlayer(i).Valid() && pVision->TheirPlayer(i).X() > 0) {
		//				const CGeoPoint& playerPos = pVision->TheirPlayer(i).Pos();
		//				const CVector startPos2player = playerPos - startPos;
		//				const double playerDist = startPos2player.mod() - Param::Field::MAX_PLAYER_SIZE / 2;
		//				const double playerDir = startPos2player.dir();
		//				const double angleRange = (playerDist <= Param::Field::MAX_PLAYER_SIZE / 2 ? Param::Math::PI / 2 : std::asin(Param::Field::MAX_PLAYER_SIZE / 2 / playerDist)); // 挡住的角度
		//				if (playerDist < 20) {
		//					continue; // 敌方围住车时，不考虑敌方对球的阻挡
		//				}
		//				lastPassList.removeAngleRange(playerDir, angleRange, playerDist);
		//			}
		//		}
		//	}
		//	else {
		//		// 初始传球范围
		//		const CGeoPoint leftPost(0, Param::Field::PITCH_WIDTH / 2);
		//		const CGeoPoint rightPost(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2);
		//		const double leftPostAngle = (leftPost - startPos).dir();
		//		const double rightPostAngle = (rightPost - startPos).dir();
		//		const double leftPostDist = (leftPost - startPos).mod();
		//		const double rightPostDist = (rightPost - startPos).mod();

		//		lastPassList.add(CValueRange(leftPostAngle, rightPostAngle, leftPostDist, rightPostDist)); // 初始化
		//		for (int i = 0; i < Param::Field::MAX_PLAYER; ++i) {
		//			if (pVision->TheirPlayer(i).Valid() && pVision->TheirPlayer(i).X() > 0) {
		//				const CGeoPoint& playerPos = pVision->TheirPlayer(i).Pos();
		//				const CVector startPos2player = playerPos - startPos;
		//				const double playerDist = startPos2player.mod() - Param::Field::MAX_PLAYER_SIZE / 2;
		//				const double playerDir = startPos2player.dir();
		//				const double angleRange = (playerDist <= Param::Field::MAX_PLAYER_SIZE / 2 ? Param::Math::PI / 2 : std::asin(Param::Field::MAX_PLAYER_SIZE / 2 / playerDist)); // 挡住的角度
		//				if (playerDist < 20) {
		//					continue; // 敌方围住车时，不考虑敌方对球的阻挡
		//				}
		//				lastPassList.removeAngleRange(playerDir, angleRange, playerDist);
		//			}
		//		}
		//	}
		//}
	}
}

const CValueRangeList& CPassRangeList::getLeftPassRange()
{
	return lastLeftPassList;
}

const CValueRangeList& CPassRangeList::getRightPassRange()
{
	return lastRightPassList;
}