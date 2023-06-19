#include "SpeedTest.h"
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

namespace {
	
}

CSpeedTest::CSpeedTest()
{
	
}

void CSpeedTest::plan(const CVisionModule* pVision)
{
	//以下解析参数中task()的参数名字不具有实际意义，仅为传参方便使用
	const int num = task().executor;
	const CGeoPoint start_pos = task().player.pos;
	const CGeoPoint end_pos = task().ball.pos;
	const double v_start = task().player.speed_x;
	const double v_end = task().player.speed_y;
	const double v_step = task().player.rotvel;

	CPlayerTask* pTask;

	CGeoPoint target = end_pos;
	double dir = (start_pos - end_pos).dir();
	pTask = PlayerRole::makeItGoto(num, target, dir);
	
	setSubTask(pTask);
	CStatedTask::plan(pVision);
}

CPlayerCommand* CSpeedTest::execute(const CVisionModule* pVision)
{
	if (subTask())
	{
		return subTask()->execute(pVision);
	}
	return NULL;
}