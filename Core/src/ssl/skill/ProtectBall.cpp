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
        Approach_Ball = 1,
        Protect_Ball = 2,
        Defence = 3, 
        Back = 4,
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

 
    int new_state = state(), old_state = state();
    do {
        old_state = new_state;

        switch (old_state){
        case BEGINNING:
            {
            if (oppo2BallDist < 40) {
                if (verBos) cout << "BEGINNING-->Defence" << endl;
                new_state = Defence;
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
            }
        case Approach_Ball:
            if (oppo2BallDist < 40) {
                if (verBos) cout << "Approach_Ball-->Defence" << endl;
                new_state = Defence;
            }
            else {
                new_state = Approach_Ball;
            }
            break;
        case Protect_Ball:
            if (oppo2BallDist < 40) {
                if (verBos) cout << "Protect_Ball-->Defence" << endl;
                new_state = Defence;
            }
            else if (self2predictDist > 100) {
                if (verBos) cout << "Protect_Ball-->Approach_Ball" << endl;
                new_state = Approach_Ball;
            }else {
                new_state = Protect_Ball;
            }
            break;
        case Back:
            if (self2OppoDist > 2 * Param::Vehicle::V2::PLAYER_SIZE+5) {
                if(verBos) cout << "Back-->Defence" << endl;
                new_state = Defence;
            }
        case Defence:
            if (oppo2BallDist > 40) {
                if (verBos) cout << "Defence-->Protect_Ball" << endl;
                new_state = Protect_Ball;
            }
            else if (self2OppoDist <= 2 * Param::Vehicle::V2::PLAYER_SIZE+5) {
                if (verBos) cout << "Defence-->Back" << endl;
                new_state = Back;
            }
            else {
                new_state = Defence;
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
                CGeoPoint Pos1 = predictBallPos + Utils::Polar2Vector(50, Utils::Normalize((self.Pos() - predictBallPos).dir() - Param::Math::PI / 4));
                CGeoPoint Pos2 = predictBallPos + Utils::Polar2Vector(50, Utils::Normalize((self.Pos() - predictBallPos).dir() + Param::Math::PI / 4));
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
                approachBallPos = predictBallPos + Utils::Polar2Vector(50, Utils::Normalize((self.Pos()-predictBallPos).dir()));
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
            if (advancer2oppo.mod() / 2 > 40) {
                dist=advancer2oppo.mod() / 2;
            }
            else {
                dist = 40;
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
    case Back:
        {
            CVector vec_1 = (CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0) - predictBallPos) / (CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0) - predictBallPos).mod();
            CVector vec_2 = oppo2Ball / oppo2Ball.mod();
            CGeoPoint defencePos = CGeoPoint(0, 0);
            if (oppo2BallDir > -Param::Math::PI * 2 / 3 && oppo2BallDir < Param::Math::PI * 2 / 3) {
                defencePos = predictBallPos + Utils::Polar2Vector(75, Utils::Normalize((predictBallPos - CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0)).dir() + Param::Math::PI));
            }
            else {
                defencePos = predictBallPos + Utils::Polar2Vector(75, Utils::Normalize(((vec_1 + vec_2) / 2).dir()));//方向修正
            }

            CGeoPoint backPos = CGeoPoint(0, 0);
            double dir = (Utils::Normalize((pVision->TheirPlayer(theirBestPlayer).Pos() - self.Pos()).dir()));
            CGeoPoint Pos1 = self.Pos() + Utils::Polar2Vector(2 * Param::Vehicle::V2::PLAYER_SIZE + 7, Utils::Normalize(dir - Param::Math::PI / 4));
            CGeoPoint Pos2 = self.Pos() + Utils::Polar2Vector(2 * Param::Vehicle::V2::PLAYER_SIZE + 7, Utils::Normalize(dir + Param::Math::PI / 4));
            //GDebugEngine::Instance()->gui_debug_x(Pos1, COLOR_BLUE); //测试用
            //GDebugEngine::Instance()->gui_debug_x(Pos2, COLOR_BLUE); //测试用
            double Dist1 = (Pos1 - defencePos).mod();
            double Dist2 = (Pos2 - defencePos).mod();
            if (Dist1 < Dist2) {
                backPos = Pos1;
            }
            else {
                backPos = Pos2;
            }
            double backDir = Utils::Normalize((defencePos - self.Pos()).dir());
            protectTask.player.pos = backPos;
            protectTask.player.angle = backDir;
            protectTask.player.vel = CVector(0, 0);
            protectTask.player.rotvel = 0;
            protectTask.player.max_acceleration = 1000;
            protectTask.player.max_deceleration = 1000;
            setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(protectTask));
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 200), "Back");
        }
        break;
    case Defence:
        {
            CVector vec_1 = (CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0) - predictBallPos) / (CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0) - predictBallPos).mod();
            CVector vec_2 = oppo2Ball / oppo2Ball.mod();
            CGeoPoint defencePos = CGeoPoint(0, 0);
            if (oppo2BallDir > -Param::Math::PI * 2 / 3 && oppo2BallDir < Param::Math::PI * 2 / 3) {
                defencePos = predictBallPos + Utils::Polar2Vector(75, Utils::Normalize((predictBallPos - CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0)).dir() + Param::Math::PI));
            }
            else {
                defencePos = predictBallPos + Utils::Polar2Vector(75, Utils::Normalize(((vec_1+vec_2)/2).dir()));//方向修正
            }
			double defenceDir = (predictBallPos -self.Pos()).dir();
			protectTask.player.pos=defencePos;
			protectTask.player.angle=defenceDir;
			protectTask.player.vel=CVector(0,0);
			protectTask.player.rotvel=0;
			protectTask.player.max_acceleration=1000;
			protectTask.player.max_deceleration=1000;
			setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(protectTask));
			GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,200), "Defence");
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
