#include "ballChaserAttributeSet.h"

//attribute define
DEFINE_ATTRIBUTE_NEW(ballChaserTest);//for test 
DEFINE_ATTRIBUTE_NEW(Dist2BallNormalized);//归一化（同一帧所有车最大值为1）的到球的距离
DEFINE_ATTRIBUTE_NEW(Dist2BallProjModified);//归一化（超过80均为1，最小为0.125）的到球速线投影的距离，再根据球速档位修正系数
DEFINE_ATTRIBUTE_NEW(BallMovingCost);//追球模型，源代码移植，合理性存疑

//attribute evaluate
EVALUATE_ATTRIBUTE_NEW(ballChaserTest)
{
	setValue(pVision->TheirPlayer(num).Valid());
}

EVALUATE_ATTRIBUTE_NEW(Dist2BallNormalized)
{
	vector<double> Dist2BallList;
	for (int theirNum = 0; theirNum < Param::Field::MAX_PLAYER; theirNum++)
	{
		const PlayerVisionT& enemy = pVision->TheirPlayer(theirNum);
		if (enemy.Valid())
			Dist2BallList.push_back((enemy.Pos() - pVision->Ball().Pos()).mod());
		else
			Dist2BallList.push_back(0);
	}
	if (Dist2BallList.empty())
		setValue(1);
	else
		setValue(Dist2BallList[num] / (*max_element(Dist2BallList.begin(), Dist2BallList.end()) + 1e-8));
}

EVALUATE_ATTRIBUTE_NEW(Dist2BallProjModified)
{
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& player = pVision->TheirPlayer(num);

	double yDistFactor = 0;
	if (ball.Vel().mod() > 600) {
		yDistFactor = 1.3;
	} else if (ball.Vel().mod() > 400) {
		yDistFactor = 1.1;
	} else if (ball.Vel().mod() > 350) {
		yDistFactor = 1;
	} else if (ball.Vel().mod() > 280) {
		yDistFactor = 0.8;
	} else if (ball.Vel().mod() > 220) {
		yDistFactor = 0.65;
	} else if (ball.Vel().mod() > 160) {
		yDistFactor = 0.45;
	} else if (ball.Vel().mod() > 100) {
		yDistFactor = 0.3;
	} else if (ball.Vel().mod() > 70) {
		yDistFactor = 0.1;
	}

	if (!ball.Valid())
	{
		setValue(0);
		return;
	}
	CGeoLine ballVelLine = CGeoLine(ball.Pos(), ball.Vel().dir());
	CGeoPoint proj = ballVelLine.projection(player.Pos());
	double dist = player.Pos().dist(proj);
	double maxProjDist = 80;
	dist = clamp(dist, 10.0, maxProjDist);

	setValue(yDistFactor * dist / maxProjDist);
}

EVALUATE_ATTRIBUTE_NEW(BallMovingCost)
{
	const BallVisionT& ball = pVision->Ball();
	const PlayerVisionT& player = pVision->TheirPlayer(num);

	if (ball.Valid() && ball.Vel().mod() < 70)
	{
		setValue(0);
		return;
	}

	double limited_ball_speed = 800;
	if (!ball.Valid())
		limited_ball_speed = 50;
	CVector playerToBall = ball.Pos() - player.Pos();
	double angleDiff = ball.Vel().dir() - playerToBall.dir();
	double velDiff = min(ball.Vel().mod(), limited_ball_speed);
	double ballMovingCost = velDiff * fabs(cos(angleDiff));
	//ballMovingCost += velDiff * fabs(sin(Param::Math::PI-fabs(angleDiff)));

	//todo 归一化应采用更合理的方式
	double maxDist = 1;
	vector<double> Dist2BallList;
	for (int theirNum = 0; theirNum < Param::Field::MAX_PLAYER; ++theirNum)
	{
		const PlayerVisionT enemy = pVision->TheirPlayer(theirNum);
		if (enemy.Valid())
			Dist2BallList.push_back((enemy.Pos() - pVision->Ball().Pos()).mod());
	}
	if (Dist2BallList.empty())
		maxDist = ballMovingCost;
	else
		maxDist = *max_element(Dist2BallList.begin(), Dist2BallList.end());
	setValue(ballMovingCost / maxDist);
}

void CballChaserAttributeSet::setAttributes()
{
	ADD_ATTRIBUTE_NEW(ballChaserTest);
	ADD_ATTRIBUTE_NEW(Dist2BallNormalized);
	ADD_ATTRIBUTE_NEW(Dist2BallProjModified);
	ADD_ATTRIBUTE_NEW(BallMovingCost);
}
