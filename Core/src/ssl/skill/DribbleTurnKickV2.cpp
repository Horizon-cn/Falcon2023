#include "DribbleTurnKickV2.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "skill/Factory.h"
#include <utils.h>
#include <WorldModel/DribbleStatus.h>
#include <RobotSensor.h>
#include <CommandFactory.h>
#include <WorldModel/KickStatus.h>

namespace {
	
}

CDribbleTurnKickV2::CDribbleTurnKickV2()
{
}

void CDribbleTurnKickV2::plan(const CVisionModule* pVision)
{
	int runner = task().executor;
	double finalDir = task().player.angle;
	double precision = task().player.kickprecision;
	bool ischipkick = task().player.ischipkick;
	double power = task().player.kickpower;

	const PlayerVisionT& me = pVision->OurPlayer(runner);
	const BallVisionT& ball = pVision->Ball();

	CPlayerTask* pTask;
	DribbleStatus::Instance()->setDribbleCommand(runner, 3);
	if (abs(Utils::Normalize(me.Dir() - finalDir)) > precision)
	{
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "turn");
		pTask = PlayerRole::makeItSimpleGoto(runner, me.Pos(), finalDir);
		KickStatus::Instance()->clearAll();
	}
	else
	{
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "turn");
		KickStatus::Instance()->setKick(runner, power);
		pTask = PlayerRole::makeItJustKick(runner, ischipkick, power);
	}
	setSubTask(pTask);
	CStatedTask::plan(pVision);
}

CPlayerCommand* CDribbleTurnKickV2::execute(const CVisionModule* pVision)
{
	if (subTask())
	{
		return subTask()->execute(pVision);
	}
	return NULL;
}
