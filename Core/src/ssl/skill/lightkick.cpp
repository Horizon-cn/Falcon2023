#include "lightkick.h"
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
    const double newVehicleBuffer = 0.6;
    int _lastCycle = 0;
}

Clightkick::Clightkick()
{
}

void Clightkick::plan(const CVisionModule* pVision)
{
	int runner = task().executor;
	double finalDir = task().player.angle;

	CPlayerTask* pTask;
    const PlayerVisionT& me = pVision->OurPlayer(runner);
    const BallVisionT& ball = pVision->Ball();
    const CGeoPoint myhead = me.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer, me.Dir());
    const CVector self2ball = ball.Pos() - me.Pos();
    const CVector ball2self = me.Pos() - ball.Pos();
    const double StopDist = task().player.rotvel;

    TaskT lightkick(task());
    
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -350), "lightkick", COLOR_WHITE);
    
    if (fabs(me.Dir() - finalDir) < Param::Math::PI * 22 / 180 && me.X() < ball.X() && fabs((ball.Pos() - me.Pos()).dir() - finalDir) < Param::Math::PI * 22 / 180) {
        lightkick.player.pos = ball.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer + Param::Field::BALL_SIZE + StopDist, Utils::Normalize((ball.Pos() - me.Pos()).dir())); // 预测球的位置 + 5.85     这个长度越大离球越远
        lightkick.player.needdribble = 0;
        if (BallStatus::Instance()->getBallPossession(true, runner) > 0)
            lightkick.player.angle = finalDir;
        else 
            lightkick.player.angle = (ball.Pos() - me.Pos()).dir();
        KickStatus::Instance()->setKick(runner, 50);
        setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(lightkick));
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(320, -350), "pushkick", COLOR_WHITE);
    }
    else {
        setSubTask(PlayerRole::makeItNoneTrajGetBall(runner, finalDir, CVector(0, 0), 0, 0));
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(320, -350), "must get", COLOR_WHITE);
    }
    CStatedTask::plan(pVision);
}

CPlayerCommand* Clightkick::execute(const CVisionModule* pVision)
{
	if (subTask())
	{
		return subTask()->execute(pVision);
	}
	return NULL;
}
