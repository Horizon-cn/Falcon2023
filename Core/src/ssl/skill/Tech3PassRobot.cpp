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
CTech3Pass:: CTech3Pass()
{

}
CTech3Pass:: ~CTech3Pass(){}
int CTech3Pass:: buff = 0;
int CTech3Pass:: num = -1; //
int CTech3Pass:: ifstep2 = 0;
int CTech3Pass:: ifstart = 0;
//=================================================================初始化(可以考虑放进构造函数)

CGeoPoint CTech3Pass::limitpos(CGeoPoint pos, int fla)
{
    int runner = task().executor;
    // const CVector target2center = centre - pos;
    const CVector target2center = (pos - centre) * fla;
    const double dis = target2center.mod();
    if(dis < 30) return pos;
    else
        return centre + target2center.unit() * 30;
}
//================================================================限制走位的函数,pos为要走的点,fla缺省则返回pos与圆心连线和圆周的交点,若fla为-1则返回延长线和圆周的交点

CGeoPoint midpoint(const CGeoPoint& A, const CGeoPoint& B) {
    return CGeoPoint((A.x() + B.x()) / 2.0, (A.y() + B.y()) / 2.0);
}

// Function to calculate the cross product of two vectors A and B
double crossProduct(const CGeoPoint& A, const CGeoPoint& B, const CGeoPoint& C) {
    CGeoPoint AB(B.x() - A.x(), B.y() - A.y());
    CGeoPoint AC(C.x() - A.x(), C.y() - A.y());
    return AB.x() * AC.y() - AB.y() * AC.x();
}

// Main function to determine on which side of the line through A1 and AM the point B1 lies
CGeoPoint CTech3Pass:: passwho(const CGeoPoint& A1, const CGeoPoint& A2, const CGeoPoint& A3, const CGeoPoint& B1) {
    CGeoPoint AM = midpoint(A2, A3);
    double cp = crossProduct(A1, AM, B1);
    // Assuming positive cross product means B1 is on the same side as A2 relative to the line A1-AM
    if (cp > 0) {
        return A3; // B1 is on the side of A3,need to turn to A2
    } else {
        return A2; // B1 is on the side of A2,need to turn to A3
    }
}

int postonum(const CGeoPoint& pos, const CVisionModule* pVision)//位置转球员号码
{
    for(int irole = 0; irole <= Param::Field::MAX_PLAYER; irole++)
    {
        const PlayerVisionT& player = pVision->OurPlayer(irole);
        if(player.Valid())
            if(CVector(player.Pos() - pos).mod() < 3)
                return irole;
    }
}
int CTech3Pass::passwho(const CVisionModule* pVision)
{
    if(BallStatus::Instance()->getBallPossession(true, num) > 0.8 || num == -1)//判断新一轮传球是否开始
    {    
        //num = num % 3 + 1;
        CGeoPoint playerpos[4];
        int cur = 0;
        for(int irole = 0; irole <= Param::Field::MAX_PLAYER; irole++)
        {
            const PlayerVisionT& player = pVision->OurPlayer(irole);
            if(irole == num)    continue;
            if(player.Valid())
                playerpos[cur++] = player.Pos();
        }
        for(int irole = 0; irole <= Param::Field::MAX_PLAYER; irole++)
        {
            const PlayerVisionT& player = pVision->TheirPlayer(irole);
            if(player.Valid())
                playerpos[cur++] = player.Pos();
        }
        num = postonum(passwho(pVision->OurPlayer(num).Pos(), playerpos[0], playerpos[1], playerpos[2]), pVision);
        buff = 0;
        ifstep2 = 0;
    }
    return num;
}
//============================================================================================passsho部分在新一轮传球开始前决定好将球传给谁

bool CTech3Pass:: passwhen(const CVisionModule* pVision)
{
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(task().executor);
    for (int irole = 0; irole <= Param::Field::MAX_PLAYER; irole++)
    {
        const PlayerVisionT& player = pVision->TheirPlayer(irole);
        if (player.Valid())
        {
            CVector enemy2ball = player.Pos() - ball.Pos();
            if(fabs(enemy2ball.dir() - me.Dir()) > 0.05)
                return true;
        }
    }
    return false;
}
//======================================================================================================passwhen部分决定进入pass状态后什么时候传最好

void CTech3Pass:: passto(const int num, const CVisionModule* pVision)
{
    // GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 20), to_string(num).c_str(), COLOR_BLUE);
    int runner = task().executor;
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(runner);
    CVector ball2me, receiver2me;
    TaskT subtask(task());
    subtask.executor = runner;
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
            if (runner == num && ball.Vel().mod() > 100)
                setState(state_wait);
        break; 
        case state_wait:
            if (runner == num && ball.Vel().mod() < 100)
                setState(state_ready);
            if (BallStatus::Instance()->getBallPossession(true, runner) > 0.8)
                setState(state_pass);
        break;
        case state_pass:
            if(CVector(centre - ball.Pos()).mod() > 30)
                setState(state_ready);
        break;
    }
//-------------------------------------------------------------------------------状态机分配 ready为跑位到初始站位, wait为后撤缓冲接球, pass为传球

    switch(state())
    {
        case state_ready:
            //subtask.player.pos = limitpos(ball.Pos(), pVision);
            subtask.player.pos = (limitpos(ball.Pos(), -1).midPoint(centre));
            //subtask.player.pos = centre;
            subtask.player.angle = CVector(ball.Pos() - subtask.player.pos).dir();
            setSubTask(TaskFactoryV2::Instance()->GotoPosition(subtask));
            break;
        case state_wait:
            ball2me = ball.Pos() - pVision->OurPlayer(runner).Pos();
            if(CVector(centre - ball.Pos()).mod() <= 30)
                setSubTask(PlayerRole::makeItNoneTrajGetBall(num, ball2me.dir()));
            //else if(CVector(centre - ball.Pos()).mod() <= 90)
            else if(ifstep2)
            {
                GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 100), "step2", COLOR_YELLOW);
                //subtask.player.pos = waitpoint.point1().midPoint(waitpoint.point2());
                subtask.player.pos = (CVector(waitpoint.point2() - ball.Pos()).mod() < CVector(waitpoint.point1() - ball.Pos()).mod()) ? waitpoint.point1() : waitpoint.point2();
                GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 0), to_string(subtask.player.pos.x()).c_str(), COLOR_WHITE);
                GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 50), to_string(subtask.player.pos.y()).c_str(), COLOR_WHITE);
                subtask.player.angle = ball2me.dir();
                setSubTask(TaskFactoryV2::Instance()->GotoPosition(subtask));
            }
            else
            {
                GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100 + 100 * runner, 100), "step1", COLOR_YELLOW);
                //subtask.player.pos = (CVector(waitpoint.point2() - ball.Pos()).mod() < CVector(waitpoint.point1() - ball.Pos()).mod()) ? waitpoint.point1() : waitpoint.point2();
                subtask.player.pos = limitpos(ballline.projection(pVision->OurPlayer(runner).Pos()));
                subtask.player.angle = ball2me.dir();
                if(CVector(pVision->OurPlayer(runner).Pos() - subtask.player.pos).mod() < 3)
                    ifstep2 = 1;
                setSubTask(TaskFactoryV2::Instance()->GotoPosition(subtask));
                
            }
            break;
        case state_pass:
            receiver2me = CVector(pVision->OurPlayer(num).Pos() - pVision->OurPlayer(runner).Pos());
            ball2me = CVector(ball.Pos() - pVision->OurPlayer(runner).Pos());
            if(fabs(receiver2me.dir() - ball2me.dir()) < 0.1) buff++;
            setSubTask(PlayerRole::makeItNoneTrajGetBall(runner, receiver2me.dir()));
            if(BallStatus::Instance()->getBallPossession(true, runner) > 0.8 && 
                ((fabs(receiver2me.dir() - pVision->OurPlayer(runner).Dir()) < 0.05) || 
                buff > 30) && fabs(me.RotVel()) < 0.1 && passwhen(pVision))
                //------------------------------------------------------------------------------passwhen 有待完善
            {
                setSubTask(PlayerRole::makeItNoneTrajGetBall(runner, receiver2me.dir()));
                
                GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, 100), "kick", COLOR_YELLOW);
                buff = 0;

                KickStatus::Instance()->setKick(runner, 600);
                //setSubTask(PlayerRole::makeItChaseKickV2(runner, dir.dir()));
            }
    }
    CStatedTask::plan(pVision);
}
//=================================================================================================================================具体pass实现

void CTech3Pass:: plan(const CVisionModule* pVision)
{   
    double minn = 1000000;
    const BallVisionT& ball = pVision->Ball();
    int runner = task().executor;
    GDebugEngine::Instance()->gui_debug_arc(circleCenter[0], 30,0,360, COLOR_RED);
    GDebugEngine::Instance()->gui_debug_arc(circleCenter[0], 90,0,360, COLOR_RED);
	GDebugEngine::Instance()->gui_debug_arc(circleCenter[1], 30,0,360, COLOR_RED);
	GDebugEngine::Instance()->gui_debug_arc(circleCenter[2], 30,0,360, COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 0), to_string(ball.Vel().mod()).c_str(), COLOR_BLUE);
    
    
    for (int i = 0; i <= 2; i++)
    {
        const CVector player2target = pVision->OurPlayer(runner).Pos() - circleCenter[i];
        const double dis = player2target.mod();
        if (minn > dis)
            minn = dis, centre = circleCenter[i];
    }
//---------------------------------------------------------------------确定当前机器人所处圆心
    for(int irole = 0; irole <= Param::Field::MAX_PLAYER; irole++)
    {
        const PlayerVisionT& runner = pVision->OurPlayer(irole);
        
        if(runner.Valid())
            if(CVector(ball.Pos() - runner.Pos()).mod() <= 45)
                ifstart = 1;
    }
    if(ifstart)
        passto(passwho(pVision), pVision);
    else
    {
        TaskT subtask(task());
        subtask.player.pos = limitpos(ball.Pos(), -1);
        subtask.player.angle = CVector(ball.Pos() - pVision->OurPlayer(runner).Pos()).dir();
        setSubTask(TaskFactoryV2::Instance()->GotoPosition(subtask));
    }
//--------------------------------------------------------------------新增开始的摆球状态, 方便摆球
}


CPlayerCommand* CTech3Pass:: execute(const CVisionModule * pVision)
{
    if(subTask())
    {
        return subTask()->execute(pVision);
    }
    return NULL;
}