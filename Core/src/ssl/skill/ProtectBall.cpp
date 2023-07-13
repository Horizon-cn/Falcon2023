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
#include "defenceNew/DefenceInfoNew.h"

namespace
{
    enum ProtectBall_State {
        Approach_Ball=1,
        Protect_Ball,
        Block, 
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

    // 预测系数a
    const double a=3;// 需要根据实际情况调整
    // 计算预测时间
    double ballSpeed = ball.Vel().mod(); // 球的速度
    double predictTime =ballSpeed/a;
    // 计算预测位置
    CGeoPoint predictBallPos=BallSpeedModel::Instance()->posForTime(predictTime,pVision);
    // 显示预测位置
    GDebugEngine::Instance()->gui_debug_msg(predictBallPos,"P",COLOR_RED);

    double self2predictDist =(predictBallPos-self.Pos()).mod();
    const int advancer = TaskMediator::Instance()->advancer();
    const int theirBestPlayer = DefenceInfoNew::Instance()->getBestBallChaser();
    double advancer2BallDist = (ball.Pos() - pVision->OurPlayer(advancer).Pos()).mod();
    double oppo2BallDist = (ball.Pos() - pVision->TheirPlayer(theirBestPlayer).Pos()).mod();
    double self2BallDist = (ball.Pos() - self.Pos()).mod();
    double self2OppoDist = (pVision->TheirPlayer(theirBestPlayer).Pos() - self.Pos()).mod();
    double oppo2BallDir = Utils::Normalize((ball.Pos() - pVision->TheirPlayer(theirBestPlayer).Pos()).dir());
    CVector oppo2Ball = ball.Pos() - pVision->TheirPlayer(theirBestPlayer).Pos();
    CVector advancer2oppo= pVision->TheirPlayer(theirBestPlayer).Pos() - pVision->OurPlayer(advancer).Pos();
    CGeoPoint ourGoalPos = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
    CVector advancer2Ball = ball.Pos() - pVision->OurPlayer(advancer).Pos();
    CGeoPoint targetPos = task().player.pos;
    double self2targetDist = (targetPos - self.Pos()).mod();
 
    int new_state = state(), old_state = state();
    do {
        old_state = new_state;

        switch (old_state){
        case BEGINNING:
            if (oppo2BallDist < 40) {
                if (verBos) cout << "BEGINNING-->Block" << endl;
                new_state = Block;
            }
            else if (self2predictDist > 100) {
                if (verBos) cout << "BEGINNING-->Approach_Ball" << endl;
                new_state = Approach_Ball;
            }
            else if (oppo2BallDist > 40 && self2predictDist <= 100) {
                if (verBos) cout << "BEGINNING-->Protect_Ball" << endl;
                new_state = Protect_Ball;
            }
            else {
                new_state = BEGINNING;
            }
            break;
        case Approach_Ball:
            if (oppo2BallDist < 40) {
                if (verBos) cout << "Approach_Ball-->Block" << endl;
                new_state = Block;
            }
            else {
                new_state = Approach_Ball;
            }
            break;
        case Protect_Ball:
            if (oppo2BallDist < 40) {
                if (verBos) cout << "Protect_Ball-->Block" << endl;
                new_state = Block;
            }
            else if (self2predictDist > 100) {
                if (verBos) cout << "Protect_Ball-->Approach_Ball" << endl;
                new_state = Approach_Ball;
            }else {
                new_state = Protect_Ball;
            }
            break;
        case Block:
            if (oppo2BallDist > 40) {
                if (verBos) cout << "Block-->Protect_Ball" << endl;
                new_state = Protect_Ball;
            }
            else {
                new_state = Block;
            }
            break;
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

    switch (state()){
    case Approach_Ball:
        {
            CGeoPoint approachBallPos;
            double dir = Utils::Normalize(advancer2Ball.dir());
            if (Utils::Normalize(fabs(dir - (self.Pos()-predictBallPos).dir())) <= Param::Math::PI / 4) {
                CGeoPoint Pos1 = predictBallPos + Utils::Polar2Vector(70, Utils::Normalize((self.Pos() - predictBallPos).dir() - Param::Math::PI / 4));
                CGeoPoint Pos2 = predictBallPos + Utils::Polar2Vector(70, Utils::Normalize((self.Pos() - predictBallPos).dir() + Param::Math::PI / 4));
                //GDebugEngine::Instance()->gui_debug_x(Pos1, COLOR_BLUE); //测试用
                //GDebugEngine::Instance()->gui_debug_x(Pos2, COLOR_BLUE); //测试用
                double Dist1 = (Pos1 - self.Pos()).mod();
                double Dist2 = (Pos2 - self.Pos()).mod();
                if (Dist1 < Dist2) {
                    approachBallPos = Pos1;
                }
                else {
                    approachBallPos = Pos2;
                }
            }
            else {
                approachBallPos = predictBallPos + Utils::Polar2Vector(70, Utils::Normalize((self.Pos()-predictBallPos).dir()));
            }
            double approachBallDir = (approachBallPos - self.Pos()).dir();
            protectTask.player.pos=approachBallPos;
            protectTask.player.angle=approachBallDir;
            protectTask.player.vel=CVector(0,0);
            protectTask.player.rotvel=0;
            protectTask.player.max_acceleration=1000;
            protectTask.player.max_deceleration=1000;

            setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(protectTask));
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,200), "Approach Ball");
        }
        break;
 
    case Protect_Ball:
        {
            
            CGeoPoint protectBallPos; 
            double dir = Utils::Normalize(advancer2oppo.dir());
            double dist=0;
            if (advancer2oppo.mod() / 2 > 20) {
                dist=advancer2oppo.mod() / 2;
            }
            else {
                dist = 20;
            }
            if (Utils::Normalize(fabs(dir - advancer2Ball.dir())) <= Param::Math::PI / 4) {
                CGeoPoint Pos1 = predictBallPos + Utils::Polar2Vector(dist, Utils::Normalize(advancer2Ball.dir() - Param::Math::PI / 4));
                CGeoPoint Pos2 = predictBallPos + Utils::Polar2Vector(dist, Utils::Normalize(advancer2Ball.dir() + Param::Math::PI / 4));
                //GDebugEngine::Instance()->gui_debug_x(Pos1, COLOR_GREEN); //测试用
                //GDebugEngine::Instance()->gui_debug_x(Pos2, COLOR_GREEN); //测试用
                double Dist1 = (Pos1 - pVision->TheirPlayer(theirBestPlayer).Pos()).mod();
                double Dist2 = (Pos2 - pVision->TheirPlayer(theirBestPlayer).Pos()).mod();
                if (Dist1 < Dist2) {
                    protectBallPos = Pos1;
                }
                else {
                    protectBallPos = Pos2;
                }
            }
            else {
                protectBallPos = predictBallPos + Utils::Polar2Vector(dist, Utils::Normalize(advancer2oppo.dir()));
            }
            double protectBallDir = (Utils::Normalize((predictBallPos - pVision->TheirPlayer(theirBestPlayer).Pos()).dir()) + Utils::Normalize((predictBallPos - self.Pos()).dir())) / 2;
            protectTask.player.pos= protectBallPos;
            protectTask.player.angle=protectBallDir;
            protectTask.player.vel=CVector(0,0);
            protectTask.player.rotvel=0;
            protectTask.player.max_acceleration=1000;
            protectTask.player.max_deceleration=1000;
            setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(protectTask));
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,200), "Protect Ball");
        }
        break;
    case Block:
        {
            CGeoPoint BlockPos = CGeoPoint(0, 0);
            int h = sqrt(400 - advancer2oppo.mod() * advancer2oppo.mod() / 4);
            CGeoPoint BlockPos1 = pVision->OurPlayer(advancer).Pos() + Utils::Polar2Vector(advancer2oppo.mod() / 2, Utils::Normalize(advancer2oppo.dir())) + Utils::Polar2Vector(h, Utils::Normalize(advancer2oppo.dir() + Param::Math::PI / 2));
            CGeoPoint BlockPos2 = pVision->OurPlayer(advancer).Pos() + Utils::Polar2Vector(advancer2oppo.mod() / 2, Utils::Normalize(advancer2oppo.dir())) + Utils::Polar2Vector(h, Utils::Normalize(advancer2oppo.dir() - Param::Math::PI / 2));
            double dist1 = (BlockPos1 - self.Pos()).mod();
            double dist2 = (BlockPos2 - self.Pos()).mod();
            if (dist1<dist2) {
				BlockPos = BlockPos1;
			}
            else {
				BlockPos = BlockPos2;
			}
            if ((BlockPos - self.Pos()).mod() < 5) {
                if (dist1 > dist2) {
                    BlockPos = BlockPos1;
                }
                else {
                    BlockPos = BlockPos2;
                }
            }
            //GDebugEngine::Instance()->gui_debug_x(BlockPos, COLOR_BLUE);//测试用
            double BlockDir = Utils::Normalize((ball.Pos()-self.Pos()).dir());
			protectTask.player.pos=BlockPos;
			protectTask.player.angle=BlockDir;
			protectTask.player.vel=CVector(0,0);
			protectTask.player.rotvel=0;
			protectTask.player.max_acceleration=1000;
			protectTask.player.max_deceleration=1000;
			setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(protectTask));
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,200), "Block");
        }
        break;
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
