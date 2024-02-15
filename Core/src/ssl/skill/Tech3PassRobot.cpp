#include "Tech3PassRobot.h"

#include "VisionModule.h"
#include "Global.h"




#include <iostream>
#include "GDebugEngine.h"
#include "Vision/VisionModule.h"
#include "skill/Factory.h"
#include "utils.h"
#include "WorldModel/DribbleStatus.h"
#include "RobotSensor.h"
#include "param.h"
#include "WorldModel/WorldModel.h"
#include "BallStatus.h"

#include <vector>
#include <variant>
#include <string>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
CTech3Pass:: CTech3Pass(){}
CTech3Pass:: ~CTech3Pass(){}
CGeoPoint CTech3Pass::limitpos(CGeoPoint pos, const CVisionModule* pVision)
{
    int runner = task().executor;
    const PlayerVisionT& self = pVision->OurPlayer(runner);
    const CGeoPoint mypos = self.Pos();
    //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 0), to_string(minn).c_str(), COLOR_RED);
    //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 50), to_string(centre.y()).c_str(), COLOR_RED);
    const CVector target2center = centre - pos;
    const double dis = target2center.mod();
    //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-500, -350), to_string(dis).c_str(), COLOR_RED);
    if(dis < 30) return pos;
    else
        return centre + target2center.unit() * 30;
}

void CTech3Pass:: passto(int num, const CVisionModule* pVision)
{
    int runner = task().executor;
    const BallVisionT& ball = pVision->Ball();
    CVector ball2me, receiver2me;
    TaskT subtask(task());
    subtask.executor = runner;
    double minn = 1000000;
    for (int i = 0; i <= 2; i++)
    {
        const CVector player2target = pVision->OurPlayer(runner).Pos() - circleCenter[i];
        const double dis = player2target.mod();
        if (minn > dis)
            minn = dis, centre = circleCenter[i];
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 0 + 10 * i), to_string(i).c_str(), COLOR_RED);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 50 + 10 * i), to_string(dis).c_str(), COLOR_RED);
    }
    const CGeoCirlce mecircle(centre, 30);
    CGeoLine ballline(ball.Pos(), ball.Vel().dir());
    CGeoLineCircleIntersection waitpoint (ballline, mecircle);
    switch(state())
    {
        case BEGINNING: 
            setState(state_ready);
        break;
        case state_ready: 
            if (CVector(centre - ball.Pos()).mod() <= 30)
                setState(state_pass);
            //if(runner == num && CVector(centre - ball.Pos()).mod() <= 120)
            if(runner == num && ball.Vel().mod() > 0.5)
                setState(state_wait);
        break; 
        case state_wait:
            if(CVector(centre - ball.Pos()).mod() > 120 )
                setState(state_ready);
            // if(BallStatus::Instance()->getBallPossession(false, runner) > 0.5)
            //     setState(state_pass);
        break;
        case state_pass:
            if(CVector(centre - ball.Pos()).mod() > 30)
                setState(state_ready);
        break;
    }
    
    switch(state())
    {
        case state_ready:
            subtask.player.pos = limitpos(ball.Pos(), pVision);
            subtask.player.angle = CVector(ball.Pos() - subtask.player.pos).dir();
            setSubTask(TaskFactoryV2::Instance()->GotoPosition(subtask));
            break;
        case state_wait:
            ball2me = ball.Pos() - pVision->OurPlayer(runner).Pos();

            if(CVector(centre - ball.Pos()).mod() <= 30)
                setSubTask(PlayerRole::makeItNoneTrajGetBall(num, ball2me.dir()));
            else if(CVector(centre - ball.Pos()).mod() <= 50)
            {
                GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 100), "step2", COLOR_YELLOW);
                subtask.player.pos = waitpoint.point1().midPoint(waitpoint.point2());
                subtask.player.angle = CVector(ball.Pos() - subtask.player.pos).dir();
                setSubTask(TaskFactoryV2::Instance()->GotoPosition(subtask));
            }
            else
            {
                GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 100), "step1", COLOR_YELLOW);
                subtask.player.pos = (CVector(waitpoint.point2() - ball.Pos()).mod() < CVector(waitpoint.point1() - ball.Pos()).mod()) ? waitpoint.point1() : waitpoint.point2();
                subtask.player.angle = CVector(ball.Pos() - subtask.player.pos).dir();
                setSubTask(TaskFactoryV2::Instance()->GotoPosition(subtask));
            }
            break;
        case state_pass:
            // limitpos(ball.Pos(), pVision);
            receiver2me = CVector(pVision->OurPlayer(num).Pos() - pVision->OurPlayer(runner).Pos());
            ball2me = CVector(ball.Pos() - pVision->OurPlayer(runner).Pos());
            // if(BallStatus::Instance()->getBallPossession(false, runner) <= 0.5)
            setSubTask(PlayerRole::makeItNoneTrajGetBall(runner, receiver2me.dir()));
            if(BallStatus::Instance()->getBallPossession(true, runner) > 0.8 && fabs(receiver2me.dir() - ball2me.dir()) < 0.05)
            {
                
                setSubTask(PlayerRole::makeItNoneTrajGetBall(runner, receiver2me.dir()));
                // GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 100), to_string(fabs(receiver2me.dir())).c_str(), COLOR_YELLOW);
                // GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 130), to_string(fabs(ball2me.dir())).c_str(), COLOR_YELLOW);

                KickStatus::Instance()->setKick(runner, 500);
                //setSubTask(PlayerRole::makeItChaseKickV2(runner, dir.dir()));
            }
            // }
            // subtask.player.angle = dir.dir();
            // setSubTask(TaskFactoryV2::Instance()->fPassBall(subtask));
            // setSubTask(PlayerRole::makeItChaseKickV2(runner, dir.dir(),0, 500));
            break;
    }
    //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-500, -350), (std::to_string(state())).c_str, COLOR_RED);

    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-500 + 40 * runner, 0), to_string(state()).c_str(), COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-500 + 100 * runner, -150), to_string(CVector(pVision->OurPlayer(runner).Pos() - ball.Pos()).mod()).c_str(), COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-500 + 40 * runner, -350), to_string(runner).c_str(), COLOR_RED);
    CStatedTask::plan(pVision);
}
void CTech3Pass:: plan(const CVisionModule* pVision)
{
    int num;
    num = 2;
    GDebugEngine::Instance()->gui_debug_arc(circleCenter[0], 30,0,360, COLOR_RED);
    GDebugEngine::Instance()->gui_debug_arc(circleCenter[0], 120,0,360, COLOR_RED);
	GDebugEngine::Instance()->gui_debug_arc(circleCenter[1], 30,0,360, COLOR_RED);
	GDebugEngine::Instance()->gui_debug_arc(circleCenter[2], 30,0,360, COLOR_RED);
    passto(num, pVision);
}
CPlayerCommand* CTech3Pass:: execute(const CVisionModule * pVision)
{
    if(subTask())
    {
        return subTask()->execute(pVision);
    }
    return NULL;
}