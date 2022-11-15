/************************************************************************/
/*		modified by tyh
		22.7.10
		chaseKickV2
*/
/************************************************************************/
#include "PenaltyKickV2.h"
#include <Vision/VisionModule.h>
#include <WorldModel/KickStatus.h>
#include "RobotSensor.h"
#include "skill/Factory.h"
#include <WorldModel/WorldModel.h>
#include "WorldModel/DribbleStatus.h"
#include "PointCalculation/IndirectDefender.h"
#include <utils.h>
#include <BestPlayer.h>
#include "KickDirection.h"
#include <GDebugEngine.h>
#include <iostream>
#include <BestPlayer.h>
#include <TaskMediator.h>


void CPenaltyKickV2::plan(const CVisionModule* pVision) {
	//Cycle loop
	const int HUGE_POWER = 1000;
	const int LIGHT_POWER = 500;
	const bool DEBUG_ENGINE = true;
	int _executor = task().executor;
	int flag = task().player.flag | PlayerStatus::DODGE_OUR_DEFENSE_BOX;
	int flag_not_dribble = flag & (~PlayerStatus::DRIBBLING);

	//information of images  »ñÈ¡vision
	const PlayerVisionT& me = pVision->OurPlayer(_executor);
	const BallVisionT& ball = pVision->Ball();
	double kickDir = (CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, 0) - pVision->Ball().Pos()).dir();

	if (DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "PENALTY", COLOR_CYAN);
	if (ball.Pos().x() < 0) {
		KickStatus::Instance()->setChipKick(_executor, HUGE_POWER);
		setSubTask(PlayerRole::makeItChaseKickV2(_executor, kickDir, flag_not_dribble));
	}
	else
	{
		KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
		CVector shootTarget = CVector(Param::Field::PITCH_LENGTH, 30);
		CVector dirPos = shootTarget - CVector(ball.Pos().x(), ball.Pos().y());
		kickDir = dirPos.dir();
		KickStatus::Instance()->setKick(_executor, LIGHT_POWER);
		setSubTask(PlayerRole::makeItChaseKickV2(_executor, kickDir, flag_not_dribble));
	}

	CStatedTask::plan(pVision);
}

CPlayerCommand* CPenaltyKickV2::execute(const CVisionModule* pVision) {
	if (subTask()) {
		return subTask()->execute(pVision);
	}
	if (_directCommand) {
		return _directCommand;
	}
	return 0;
}

