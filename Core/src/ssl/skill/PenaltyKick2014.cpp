#include "PenaltyKick2014.h"
#include "skill/Factory.h"
#include <CommandFactory.h>
#include <utils.h>
#include <Vision/VisionModule.h>
#include <WorldModel/KickStatus.h>
#include <WorldModel/DribbleStatus.h>
#include <WorldModel/RobotCapability.h>
#include <WorldModel/WorldModel.h>
#include "GDebugEngine.h"

namespace{
    bool VERBOSE_MODE = false;

    const double MOVE_TO_KICK_POINT_SPEED = 100; // 走到开球点的速度
    const double KICK_PREPARE_DIST = 15;
    double goalBuffer = 3;
    CGeoPoint ourGoal;
    CGeoPoint leftGoal;
    CGeoPoint rightGoal;
    double ROTATE_ANGLE = Param::Math::PI/3;
    enum PenaltyKickState{
        PREPARING = 1, // 走到踢球点
        WAITING = 2, //
        ROTATING = 3, // 突然转身
        KICKING = 4,
    };
}

CPenaltyKick2014::CPenaltyKick2014()
{
    ourGoal = CGeoPoint(Param::Field::PITCH_LENGTH/2,0);
    leftGoal = CGeoPoint(Param::Field::PITCH_LENGTH/2,-Param::Field::GOAL_WIDTH/2+goalBuffer);
    rightGoal = CGeoPoint(Param::Field::PITCH_LENGTH/2,Param::Field::GOAL_WIDTH/2-goalBuffer);
    _lastCycle = 0;
    _theirGoalie = 0;
    _targetside = 0;
    _round = 0;
}

void CPenaltyKick2014::plan(const CVisionModule* pVision)
{
    if( state() == BEGINNING || pVision->Cycle() - _lastCycle > 6){
        setState(PREPARING);
        _theirGoalie = 0;
        for (int i=0;i<Param::Field::MAX_PLAYER;i++){
            if (Utils::InTheirPenaltyArea(pVision->TheirPlayer(i).Pos(),0)){
                _theirGoalie = i;
            }
        }
        int tempnum = 0;
        if(pVision->TheirPlayer(_theirGoalie).Pos().y()<0)
            tempnum = 1;
        _waitingcount = 0;
        _round = 0;
        if (tempnum == 0){ // 打左边
            _targetPoint = leftGoal;
            _targetside = 0;
            cout<<"left kick"<<endl;
        }else{
            _targetPoint = rightGoal;
            _targetside =1;
            cout<<"right kick"<<endl;
        }
    }
    //状态机执行
    switch( state() ){
    case BEGINNING:
    case PREPARING:
        cout<<"in V1 PENALTY"<<endl;
        cout<<"PENALTY PREPARING"<<endl;
        planPrepare(pVision);
        break;
    case WAITING:
        planWaiting(pVision);
        cout<<"PENALTY WAITING"<<endl;
        //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,0),"waiting");
        break;
    case ROTATING:
        planRotate(pVision);
        cout<<"PENALTY ROTATING"<<endl;
        //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,0),"rotating");
        break;
    case KICKING:
        planKick(pVision);
        cout<<"PENALTY KICKING"<<endl;
        //GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,0),"kicking");
        break;
    };
    //cout<<"goaliePoint "<<pVision->TheirPlayer(_theirGoalie).Pos()<<endl;
    CStatedTask::plan(pVision);
    _lastCycle = pVision->Cycle();
}

void CPenaltyKick2014::planPrepare(const CVisionModule* pVision)
{
    int rolenum = task().executor;
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(rolenum);
    CVector ball2goal;
    CGeoPoint startPos;
    ball2goal = _targetPoint - ball.Pos();
    startPos = ball.Pos()+Utils::Polar2Vector(-16,ball2goal.dir());
    TaskT vecTask(task());
    vecTask.player.pos = startPos;
    vecTask.player.angle = ball2goal.dir();
    setSubTask(TaskFactoryV2::Instance()->GotoPosition(vecTask));
    if (me.Pos().dist(startPos)<5 && abs(me.Dir() - ball2goal.dir()) < Param::Math::PI/36){
        setState(WAITING);
        planWaiting(pVision);
    }else{
        setState(PREPARING);
    }
}

void CPenaltyKick2014::planWaiting(const CVisionModule* pVision)
{
    TaskT vecTask(task());
    int rolenum = task().executor;
    const BallVisionT& ball = pVision->Ball();
    DribbleStatus::Instance()->setDribbleCommand(rolenum,0);
    KickStatus::Instance()->setKick(rolenum,9999);
    /*
    if (_theirGoalie!=0){
        setState(ROTATING);
        if (_targetside == 0) {
            //朝右边转
            _targetside =1;
            _targetPoint = rightGoal;
        }else{
            //朝左边转
            _targetside =0;
            _targetPoint = leftGoal;
        }
        planRotate(pVision);
    }
    else{
    */
        _waitingcount = 0;
        vecTask.player.pos = ball.Pos()+Utils::Polar2Vector(-8,(_targetPoint-ball.Pos()).dir());
        vecTask.player.angle = (_targetPoint -ball.Pos()).dir();
        setState(KICKING);
        setSubTask(TaskFactoryV2::Instance()->GotoPosition(vecTask));

}

void CPenaltyKick2014::planRotate(const CVisionModule* pVision)
{
    TaskT vecTask(task());
    int rolenum = task().executor;
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(rolenum);
    KickStatus::Instance()->setKick(rolenum,9999);
    CVector ball2Target;
    ball2Target = _targetPoint - ball.Pos();
    double ball2TargetDir = ball2Target.dir();
    if (!(me.Pos().dist(ball.Pos()+Utils::Polar2Vector(-KICK_PREPARE_DIST,ball2TargetDir))<5
        && abs(me.Dir() - ball2TargetDir) < Param::Math::PI/36)){
            vecTask.player.pos = ball.Pos()+Utils::Polar2Vector(-KICK_PREPARE_DIST,ball2TargetDir);
            vecTask.player.angle =ball2TargetDir;
            setState(ROTATING);
            setSubTask(TaskFactoryV2::Instance()->GotoPosition(vecTask));
    }else{
        _round ++ ;
        if ((canShoot(pVision) || _waitingcount>6) && _round>=2){
            _round = 0;
            _waitingcount = 0;
            vecTask.player.pos = ball.Pos()+Utils::Polar2Vector(-8,ball2TargetDir);
            vecTask.player.angle = ball2TargetDir;
            setSubTask(TaskFactoryV2::Instance()->GotoPosition(vecTask));
            setState(KICKING);
        }else{
            if (_targetside == 0){
                _targetside =1;
                _targetPoint = rightGoal;
            }else{
                _targetside = 0;
                _targetPoint = leftGoal;
            }
            cout<<"count = "<<_waitingcount<<endl;
            _waitingcount++;
            ball2TargetDir =(_targetPoint - ball.Pos()).dir();
            vecTask.player.pos = ball.Pos()+Utils::Polar2Vector(-KICK_PREPARE_DIST,ball2TargetDir);
            vecTask.player.angle =ball2TargetDir;
            setState(ROTATING);
            setSubTask(TaskFactoryV2::Instance()->GotoPosition(vecTask));
        }
    }
}

void CPenaltyKick2014::planKick(const CVisionModule* pVision)
{
    TaskT vecTask(task());
    int rolenum = task().executor;
    const BallVisionT& ball = pVision->Ball();
    KickStatus::Instance()->setKick(rolenum,9999);
    vecTask.player.pos = ball.Pos()+Utils::Polar2Vector(-6   ,(_targetPoint-ball.Pos()).dir());
    vecTask.player.angle = (_targetPoint -ball.Pos()).dir();
    setSubTask(TaskFactoryV2::Instance()->GotoPosition(vecTask));

}

bool CPenaltyKick2014::canShoot(const CVisionModule* pVision)
{
    bool result = false;
    double preframe = 0.1;
    CGeoPoint pregoaliePoint = pVision->TheirPlayer(_theirGoalie).Pos();
    double vel = pVision->TheirPlayer(_theirGoalie).VelY();
    //if (vel>0){
    //pregoaliePoint = pregoaliePoint + Utils::Polar2Vector(preframe*vel,Param::Math::PI/2);
    //cout<<"right moving"<<endl;
    //}else{
    //pregoaliePoint = pregoaliePoint + Utils::Polar2Vector(preframe*vel,Param::Math::PI/2);
    ////cout<<"left moving"<<endl;
    //}
    if ((pregoaliePoint.dist(_targetPoint)>30 &&
        pVision->TheirPlayer(_theirGoalie).Vel().mod()<40)||
        (pregoaliePoint.dist(_targetPoint)>35 &&
        pVision->TheirPlayer(_theirGoalie).Vel().mod()<60)){
            //cout<<pVision->Cycle()<<"  "<<pregoaliePoint.dist(_targetPoint)<<" "<<pVision->TheirPlayer(_theirGoalie).Vel().mod()<<" can Shoot"<<endl;
            //cout<<pVision->TheirPlayer(_theirGoalie).Pos()<<endl;
            result = true;
    }
    return result;
}
