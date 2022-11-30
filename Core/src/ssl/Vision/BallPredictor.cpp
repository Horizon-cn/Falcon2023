#include "BallPredictor.h"


namespace {
	const double VERBOSE_MODE = false;
	const int MAX_BALL_LOST_TIME = 30;
	const int NORMAL_BALL_LOST_TIME = 8;
	const double ZERRO_SPEED = 10; // 速度小于这个值认为静止//
	bool IS_ERROR_RECORD = false; //比较Neural的预测效果//
	double _lastValidDir = 0; // 记录球速大于100cm/s时的速度方向，作为球速低时的速度方向值。以免球速低时方向跳动；（效果还不确定，interceptAndShooter验证情况不佳）//

	//bool LOG_BALL_SPEED = true;
	//std::ofstream ballSpeedLog;

	double BALL_DELC_CHANGE_POINT = 250;
	double BALL_FAST_DEC = 360;
	double BALL_SLOW_DEC = 27.5;
}


CBallPredictor::CBallPredictor()
{
}

CBallPredictor::~CBallPredictor()
{
}

void CBallPredictor::updateVision(const GameInfoT& vInfo, bool invert)
{
	BallVisionData& thisCycle = _visionLogger.getVision(vInfo.cycle);
	const int invertFactor = invert ? -1 : 1;

	thisCycle.SetVel(vInfo.ball.vel*invertFactor);
	thisCycle.SetChipPredict(vInfo.ball.chipPredict.x,vInfo.ball.chipPredict.y);
	thisCycle.SetPos(vInfo.ball.pos.x * invertFactor,  vInfo.ball.pos.y * invertFactor);
	thisCycle.SetValid(vInfo.ball.pos.valid);
	thisCycle.cycle = vInfo.cycle;
	return;
}