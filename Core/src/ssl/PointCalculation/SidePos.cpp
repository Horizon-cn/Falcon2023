#include "SidePos.h"
#include "Global.h"
#include "DefPos2015.h"
#include "TaskMediator.h"

namespace {
	CGeoPoint GOALCENTRE(-Param::Field::PITCH_LENGTH / 2, 0);
}

CSidePos::CSidePos()
{
}

CGeoPoint CSidePos::ultraPos()
{
	double sidex = -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + Param::Vehicle::V2::PLAYER_SIZE;
	double sidey = Param::Field::PENALTY_AREA_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE;
	CGeoPoint target = chooseTargetPos();
	if (target.y() > Param::Field::PENALTY_AREA_WIDTH / 2) {
		return CGeoPoint(sidex, -sidey);
	} else if (target.y() < -Param::Field::PENALTY_AREA_WIDTH / 2) {
		return CGeoPoint(sidex, sidey);
	} else {
		// sideback的异侧
		int y_side = 1;
		if (TaskMediator::Instance()->sideBackUltra() != 0) {
			CGeoPoint side_origin = DefPos2015::Instance()->getSidePos();
			if (side_origin.y() > 0) {
				y_side = -1;
			}
		}
		return CGeoPoint(sidex, sidey * y_side);
	}
}

CGeoPoint CSidePos::chooseTargetPos()
{
	const BallVisionT& Ball = vision->Ball();
	const PlayerVisionT enemy = vision->TheirPlayer(DefenceInfoNew::Instance()->getBestBallChaser());
	CGeoPoint defendTarget;
	if (Ball.Valid()) {
		if (Ball.Pos().dist(enemy.Pos()) < 50 && GOALCENTRE.dist(enemy.Pos()) < 300) { //敌方离球门很近，看敌方会更准
			defendTarget = enemy.Pos();
		} else {
			defendTarget = Ball.Pos();
		}
	} else {
		defendTarget = enemy.Pos();
	}
	return defendTarget;
}
