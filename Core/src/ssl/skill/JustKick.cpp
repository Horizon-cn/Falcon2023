#include "JustKick.h"
#include "PointCalculation/DefPos2013.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "skill/Factory.h"
#include <utils.h>
#include <WorldModel/DribbleStatus.h>
#include "WorldModel/KickStatus.h"
#include <RobotSensor.h>
#include "param.h"
#include "BallSpeedModel.h"
#include "WorldModel/WorldModel.h"
#include <TaskMediator.h>

CJustKick::CJustKick()
{

}

void CJustKick::plan(const CVisionModule* pVision)
{
	int robotnum = task().executor;
	int ischipkick = task().player.ischipkick;
	double power = task().player.kickpower;
	int flag = task().player.flag;
	if (ischipkick)
		KickStatus::Instance()->setChipKick(robotnum, power);
	else
		KickStatus::Instance()->setKick(robotnum, power);
	
	double vx, vy, vw;
	const PlayerVisionT& me = pVision->OurPlayer(robotnum);
	vx = me.VelX();
	vy = me.VelY();
	vw = me.RotVel();
	CPlayerTask* pTask = PlayerRole::makeItRunLocalVersion(robotnum,vx,vy,vw);
	setSubTask(pTask);
	CStatedTask::plan(pVision);
}

CPlayerCommand* CJustKick::execute(const CVisionModule* pVision)
{
	if (subTask())
	{
		return subTask()->execute(pVision);
	}
	return NULL;
}