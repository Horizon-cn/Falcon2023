#include "ChaseToPenalty.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "skill/Factory.h"
#include <utils.h>
#include <MotionControl/ControlModel.h>
#include <cornell/Trajectory.h>
#include <WorldModel/RobotCapability.h>
#include <MotionControl/CMmotion.h>
#include <RobotSensor.h>
#include "utils.h"
#include "ShootRangeList.h"
#include <CommandFactory.h>
#include "PointCalculation/TouchKickPos.h"
#include "BallSpeedModel.h"
#include <GDebugEngine.h>

#include "WorldModel/KickStatus.h"
#include "WorldModel/WorldModel.h"

#include <cmath>
#include <WorldModel/DribbleStatus.h>
#include <BestPlayer.h>
#include "defenceNew/DefenceInfoNew.h"
using namespace Param;
namespace
{

}

CChaseToPenalty::CChaseToPenalty()
{
	_directCommand = NULL;
}

void CChaseToPenalty::plan(const CVisionModule* pVision)
{
	_directCommand = NULL;
	const BallVisionT& ball = pVision->Ball();
	const int robotNum = task().executor;
	const int realNum = robotNum;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const int playerFlag = task().player.flag;
	const int enemyLeaderNum = DefenceInfoNew::Instance()->getBestBallChaser();          //?��???????��??
	const PlayerVisionT& enemyLeader = pVision->TheirPlayer(enemyLeaderNum);
}

CPlayerCommand* CChaseToPenalty::execute(const CVisionModule* pVision)
{
	if( subTask() ){
		return subTask()->execute(pVision);
	}
	if( _directCommand != NULL ){
		return _directCommand;
	}
	return NULL;
}