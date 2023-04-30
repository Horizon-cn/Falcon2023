#include "ballReceiverAttributeSet.h"

namespace {
	CGeoPoint goalCentre(-Param::Field::PITCH_LENGTH / 2, 0);
}

//attribute define
//算法基本移植于GPU支援算点
DEFINE_ATTRIBUTE_NEW(TooFar4Pass);//太远传球比较难
DEFINE_ATTRIBUTE_NEW(TooClose4Pass);//太近传球没意义
DEFINE_ATTRIBUTE_NEW(EasyBlock);//只考虑投影，我方是否有球员能够断球
//DEFINE_ATTRIBUTE_NEW(AffectShoot);//前场影响原本的射门，感觉不适用于防守体系
DEFINE_ATTRIBUTE_NEW(NearSideLine);//靠近边线，接球困难，容易出界
DEFINE_ATTRIBUTE_NEW(EasyShoot);//只考虑投影，我方是否有球员能够阻挡射门

//attribute evaluate
EVALUATE_ATTRIBUTE_NEW(TooFar4Pass)
{
	double dist = vision->TheirPlayer(num).Pos().dist(vision->Ball().Pos());
	setValue(max(0.0, dist - 500));
	if (dist < 200)
		setValue(200 - dist + 100);
}

EVALUATE_ATTRIBUTE_NEW(TooClose4Pass)
{
	double dist = vision->TheirPlayer(num).Pos().dist(vision->Ball().Pos());
	if (dist < 200)
		setValue(300 - dist);
	else
		setValue(0);
}

EVALUATE_ATTRIBUTE_NEW(EasyBlock)
{
	double tempValue = 0;
	const BallVisionT& ball = vision->Ball();
	const PlayerVisionT& enemy = vision->TheirPlayer(num);
	CGeoLine passLine(ball.Pos(), enemy.Pos());
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
	{
		const PlayerVisionT& blocker = vision->OurPlayer(i);
		if (!blocker.Valid())
			continue;
		CGeoPoint blockerProj = passLine.projection(blocker.Pos());
		double blocker2projDist = blocker.Pos().dist(blockerProj);
		double ball2projDist = ball.Pos().dist(blockerProj);
		// 敌方距离传球线较远或敌方距离球较近，可以不考虑敌方对传球线的影响
		if (blocker2projDist > 300 || ball2projDist < 10)
			continue;
		double ratio_dist = blocker2projDist / ball2projDist;
		//假设我方球员速度仅有球速的0.6，则该比值大于0.6时该我方球员对传球无影响
		if (Utils::InBetween(blockerProj, ball.Pos(), enemy.Pos()))
			tempValue += max(0.0, 0.6 - ratio_dist);
	}
	setValue(tempValue);
}

EVALUATE_ATTRIBUTE_NEW(NearSideLine)
{
	const PlayerVisionT& enemy = vision->TheirPlayer(num);
	setValue(std::max(0.0, fabs(enemy.Y()) - Param::Field::PITCH_WIDTH / 2 + 100));
}

EVALUATE_ATTRIBUTE_NEW(EasyShoot)
{
	double tempValue = 0;
	const BallVisionT& ball = vision->Ball();
	const PlayerVisionT& enemy = vision->TheirPlayer(num);
	CGeoLine shootLine(goalCentre, enemy.Pos());
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
	{
		const PlayerVisionT& blocker = vision->OurPlayer(i);
		if (!blocker.Valid()||i==0)//0:目前我方Goalie
			continue;
		CGeoPoint blockerProj = shootLine.projection(blocker.Pos());
		double blocker2projDist = blocker.Pos().dist(blockerProj);
		double ball2projDist = ball.Pos().dist(blockerProj);
		// 我方距离射门线较远或我方距离球较近，可以不考虑对传球线的影响
		if (blocker2projDist > 300 || ball2projDist < 10)
			continue;
		double ratio_dist = blocker2projDist / ball2projDist;
		//射门时球速较大，且上述算法使用球门中点进行计算，实际射门会有更多选择，因此敌人对自己射门的阻挡会更小
		if (Utils::InBetween(blockerProj, ball.Pos(), enemy.Pos()))
			tempValue += max(0.0, 0.3 - ratio_dist);
	}
	setValue(tempValue);
}

void CballReceiverAttributeSet::setAttributes()
{
	ADD_ATTRIBUTE_NEW(TooFar4Pass);
	ADD_ATTRIBUTE_NEW(TooClose4Pass);
	ADD_ATTRIBUTE_NEW(EasyBlock);
	ADD_ATTRIBUTE_NEW(NearSideLine);
	ADD_ATTRIBUTE_NEW(EasyShoot);
}
