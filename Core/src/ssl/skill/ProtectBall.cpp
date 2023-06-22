#include "GDebugEngine.h"
#include "skill/Factory.h"
#include <utils.h>
#include "param.h"
#include <cmath>
#include "utils.h"
#include <Vision/VisionModule.h>
#include "BallStatus.h"
#include "ProtectBall.h"
#include "PointCalculation/TouchKickPos.h"
#include "WorldModel/WorldModel.h"
#include "BestPlayer.h"
#include "BallSpeedModel.h"
#include "TaskMediator.h"

namespace
{
    enum ProtectBall_State {
        Approach_Ball = 1,
        Protect_Ball = 2,
        Defence = 3, 
    };
    bool verBos = false;
    const int State_Counter_Num=3;
};
int CProtectBall::protectBallNum = -1;
CProtectBall::CProtectBall()
{
    _lastCycle = 0;
    _stateCounter=0;
}

void CProtectBall::plan(const CVisionModule* pVision)
{

    if ( pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1){
        setState(BEGINNING);
        _stateCounter=0;
    }
    const int runner = task().executor;
    int flags = task().player.flag;

    const PlayerVisionT& self = pVision->OurPlayer(runner);
    const BallVisionT& ball = pVision->Ball();
    const double a=5;//可以根据实际情况调整
    // 计算预测时间
    double ballSpeed = ball.Vel().mod(); // 球的速度
    double predictTime =ballSpeed/a;
    // 计算预测位置
    CGeoPoint predictBallPos=BallSpeedModel::Instance()->posForTime(predictTime,pVision);
    //显示预测位置
    GDebugEngine::Instance()->gui_debug_msg(predictBallPos,"X",COLOR_RED);

    double self2predictDist =(predictBallPos-self.Pos()).mod();
    const int advancer = TaskMediator::Instance()->advancer();
    const int theirBestPlayer = NormalPlayUtils::getTheirMostClosetoPos(pVision, ball.Pos());
    double advancer2BallDist = (ball.Pos() - pVision->OurPlayer(advancer).Pos()).mod();
    double oppo2BallDist = (ball.Pos() - pVision->TheirPlayer(theirBestPlayer).Pos()).mod();
    double self2BallDist = (ball.Pos() - self.Pos()).mod();
    double self2OppoDist = (pVision->TheirPlayer(theirBestPlayer).Pos() - self.Pos()).mod();
 
    int new_state = state(), old_state = state();
    do {
        old_state = new_state;

        if (self2predictDist > 100)
            new_state = Approach_Ball;
        else if (self2predictDist < 100)
            new_state = Protect_Ball;
        else if (oppo2BallDist < 20)
            new_state = Defence;
      
        //break;

        switch (old_state){
        case BEGINNING:
            {
                if(self2predictDist > 100){
                    if(verBos) cout<<"BEGINNING-->Approach_Ball"<<endl;
                    new_state = Approach_Ball;
                }
                else{
                    if(verBos) cout<<"BEGINNING-->Protect_Ball"<<endl;
                    new_state = Protect_Ball;
                }
                break;
            }
        case Approach_Ball:
           if(oppo2BallDist<20&&advancer2BallDist>oppo2BallDist){
                if(verBos) cout<<"Approach_Ball-->Defence"<<endl;
                new_state = Defence;
           }
           break;
        case Protect_Ball:
            if(oppo2BallDist<20 ){
                if(verBos) cout<<"Protect_Ball-->Defence"<<endl;
                new_state = Defence;
            }
            break;
        case Defence:
            if (oppo2BallDist > 100) {
				if(verBos) cout<<"Defence-->Protect_Ball"<<endl;
				new_state = Protect_Ball;
			}
        default:
            new_state = BEGINNING;
            break;
        }
    } while (false);
    if (_stateCounter==0){
        setState(new_state);
        _stateCounter++;
    }else{
        if (new_state==state()){
            _stateCounter=min(State_Counter_Num,_stateCounter+1);
        }else{
            _stateCounter=max(0,_stateCounter-1);
        }
    }

    TaskT protectTask(task());
    double SetAcc = 600 - ballSpeed;

    switch (state()){
    case Approach_Ball:
        {
            CGeoPoint approachBallPos = ball.Pos() + Utils::Polar2Vector(oppo2BallDist/2, Utils::Normalize((pVision->TheirPlayer(theirBestPlayer).Pos() - ball.Pos()).dir()));
            double approachBallDir = (approachBallPos - self.Pos()).dir();
            protectTask.player.pos=approachBallPos;
            protectTask.player.angle=approachBallDir;
            protectTask.player.vel=CVector(0,0);
            protectTask.player.rotvel=0;
            protectTask.player.max_acceleration=SetAcc;
            protectTask.player.max_deceleration=1000;

            setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(protectTask));
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,200), "Approach Ball");
            protectBallNum = TaskMediator::Instance()->ballProtecter();
        }
        break;
 
    case Protect_Ball:
        {
            static CGeoPoint lastProtectBallPos;
            CGeoPoint protectBallPos;
            protectBallPos = pVision->TheirPlayer(theirBestPlayer).Pos() + Utils::Polar2Vector(2*Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER, Utils::Normalize((ball.Pos()-pVision->TheirPlayer(theirBestPlayer).Pos()).dir()));
            double protectBallDir = Utils::Normalize((ball.Pos() - pVision->TheirPlayer(theirBestPlayer).Pos()).dir());
            if (KickStatus::Instance()->getChipKickDist(advancer) == 0 && KickStatus::Instance()->getKickPower(advancer) == 0)
                lastProtectBallPos = protectBallPos;
            protectTask.player.pos=lastProtectBallPos;
            protectTask.player.angle=protectBallDir;
            protectTask.player.vel=CVector(0,0);
            protectTask.player.rotvel=0;
            //protectTask.executor = protectBallNum;
            protectTask.player.max_acceleration=SetAcc;
            protectTask.player.max_deceleration=1000;
            setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(protectTask));
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,200), "Protect Ball");
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,250),("protectBallNUm:"+to_string(protectBallNum)).c_str(), COLOR_YELLOW);
        }
        break;
    case Defence:
        {
            CGeoPoint defencePos = ball.Pos() + Utils::Polar2Vector(100, Utils::Normalize((ball.Pos()-pVision->TheirPlayer(theirBestPlayer).Pos()).dir()));
			double defenceDir = (ball.Pos()-self.Pos()).dir();
			protectTask.player.pos=defencePos;
			protectTask.player.angle=defenceDir;
			protectTask.player.vel=CVector(0,0);
			protectTask.player.rotvel=0;
			protectTask.player.max_acceleration=600;
			protectTask.player.max_deceleration=1000;
            protectTask.executor = protectBallNum;
			setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(protectTask));
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,200), "Defence");
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 250), ("DefenceNUm:" + to_string(protectBallNum)).c_str(), COLOR_YELLOW);
        }
    default:
        break;
    }

    _lastCycle = pVision->Cycle();

    CPlayerTask::plan(pVision);
}

CPlayerCommand* CProtectBall::execute(const CVisionModule* pVision)
{
    if (_directCommand) {
        return _directCommand;
    }

    if (subTask()) {
        return subTask()->execute(pVision);
    }

    return NULL;
}
