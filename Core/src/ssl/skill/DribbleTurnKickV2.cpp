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
	CGeoPoint dribblePoint = CGeoPoint(9999, 9999);
	int _lastCycle = 0;
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
	const CGeoPoint Target = task().player.pos;
	const PlayerVisionT& me = pVision->OurPlayer(runner);
	const BallVisionT& ball = pVision->Ball();
	
	int DoNotEnterDefenseBox = PlayerStatus::DODGE_OUR_DEFENSE_BOX;
	int AllowDribbleFlag = PlayerStatus::DRIBBLING;
	int ShootAllowDribble = DoNotEnterDefenseBox | AllowDribbleFlag;
	int ShootNotNeedDribble = DoNotEnterDefenseBox & (~AllowDribbleFlag);

	CPlayerTask* pTask;

	// if (abs(Utils::Normalize(me.Dir() - finalDir)) > 80.0 * Param::Math::PI / 180 || (BallStatus::Instance()->getBallPossession(true, runner) == 0 )) {
	if (BallStatus::Instance()->getBallPossession(true, runner) == 0) {
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "GET");
		pTask = PlayerRole::makeItNoneTrajGetBall(runner, finalDir, CVector(0, 0), ShootNotNeedDribble, 0);
	}
	else if (abs(Utils::Normalize(me.Dir() - finalDir)) > precision)
	{
		DribbleStatus::Instance()->setDribbleCommand(runner, 3);
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, 100), "turn");
		if ((pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1) || BallStatus::Instance()->getBallPossession(true, runner) == 0
			|| dribblePoint == CGeoPoint(9999, 9999)) {
			dribblePoint = me.Pos();
		}
		if (me.Pos().dist(dribblePoint) < 100 && fabs(ball.Pos().x()) < Param::Field::PITCH_LENGTH / 2 - Param::Field::BALL_SIZE
			&& fabs(ball.Pos().y()) < Param::Field::PITCH_WIDTH / 2 - Param::Field::BALL_SIZE) { // 防止dribble too far 或者 出界
			CGeoPoint target = ball.Pos() + Utils::Polar2Vector(ball.Pos().dist(me.Pos()), Utils::Normalize(finalDir + Param::Math::PI));
			pTask = PlayerRole::makeItGoto(runner, target, finalDir, PlayerStatus::DODGE_BALL); // 小Break
		}
		else
			pTask = PlayerRole::makeItSimpleGoto(runner, me.Pos(), finalDir); // 转向过慢
		//KickStatus::Instance()->clearAll();
	}
	else
	{
		DribbleStatus::Instance()->setDribbleCommand(runner, 3);
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
