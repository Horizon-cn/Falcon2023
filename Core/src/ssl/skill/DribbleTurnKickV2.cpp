#include "DribbleTurnKickV2.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "skill/Factory.h"
#include <utils.h>
#include <WorldModel/DribbleStatus.h>
#include <RobotSensor.h>
#include <CommandFactory.h>
#include <WorldModel/KickStatus.h>
#include "Global.h"

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
	bool isAdvancer = task().player.isAdvancer;
	const CGeoPoint Target = task().player.pos;
	const PlayerVisionT& me = pVision->OurPlayer(runner);
	const BallVisionT& ball = pVision->Ball();
	
	int DoNotEnterDefenseBox = PlayerStatus::DODGE_OUR_DEFENSE_BOX;
	int AllowDribbleFlag = PlayerStatus::DRIBBLING;
	int ShootAllowDribble = DoNotEnterDefenseBox | AllowDribbleFlag;
	int ShootNotNeedDribble = DoNotEnterDefenseBox & (~AllowDribbleFlag);

	CPlayerTask* pTask;

	if (abs(Utils::Normalize(me.Dir() - finalDir)) > 80.0 * Param::Math::PI / 180 || (BallStatus::Instance()->getBallPossession(true, runner) == 0 )) {
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "GET");
		pTask = PlayerRole::makeItNoneTrajGetBall(runner, finalDir, CVector(0, 0), ShootNotNeedDribble, 0);
	}
	else if (abs(Utils::Normalize(me.Dir() - finalDir)) > precision)
	{
		DribbleStatus::Instance()->setDribbleCommand(runner, 3);
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "turn");
		pTask = PlayerRole::makeItSimpleGoto(runner, me.Pos(), finalDir);
		//KickStatus::Instance()->clearAll();
	}
	else
	{
		DribbleStatus::Instance()->setDribbleCommand(runner, 3);
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "turn");
		KickStatus::Instance()->setKick(runner, power);
		pTask = PlayerRole::makeItJustKick(runner, ischipkick, power);
		if(isAdvancer) KickStatus::Instance()->setAdvancerPassTo(Target);
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
