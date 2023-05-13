/************************************************************************/
/*		modified by 江亮成
        2023.5
        long dist penalty, rebuilt based on Advance
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
#include "defenceNew/DefenceInfoNew.h"
#include "KickDirection.h"
#include <GDebugEngine.h>
#include <iostream>
#include <BestPlayer.h>
#include <TaskMediator.h>
#include "Global.h"


CPenaltyKickV2::CPenaltyKickV2()
{
    KICK_DIST = paramManager->KICK_DIST;  /*射门允许范围 越高越容易射门*/
    WantToLessShoot = paramManager->WantToLessShoot; /*射门倾向，越低越容易射门 最低为0 最高为5*/
    RELIEF_DIST = paramManager->RELIEF_DIST;  /*GET中紧急状况下的RELIEF判断距离*/
    OPP_HAS_BALL_DIST = paramManager->OPP_HAS_BALL_DIST; /*判断敌方是否有球的距离 需要调整*/
    CanPassToWingDist = paramManager->CanPassToWingDist; /*Advance能够传给边锋的临界距离*/
    CanWingShootDist = paramManager->CanWingShootDist; /*边锋能够射门的临界距离*/
    SHOOT_PRECISION = paramManager->SHOOT_PRECISION;	/*允许射门最小精度角分母，越大越慢越精确 最低为7最高17*/
    GetBallBias = paramManager->AdGetBallBias;	/*AdvanceGetball的偏差*/
    BalltoMeVel = paramManager->BalltoMeVelTime; /*Advance传球给我主动去接的临界速度*/
    /*射门力度参数*/
    KICKPOWER = paramManager->KICKPOWER;
    CHIPPOWER = paramManager->CHIPPOWER; // 暂时不用了
    ADV_FPASSPOWER = paramManager->ADV_FPASSPOWER;
    ADV_CPASSPOWER = paramManager->ADV_CPASSPOWER;
    RELIEF_POWER = paramManager->RELIEF_POWER;
    BACK_POWER = paramManager->BACK_POWER;
    Advance_DEBUG_ENGINE = paramManager->Advance_DEBUG_ENGINE;
}


CPenaltyKickV2::~CPenaltyKickV2() {

}

void CPenaltyKickV2::plan(const CVisionModule* pVision)
{
    if (pVision->Cycle() - _cycle > Param::Vision::FRAME_RATE * 0.1) {
        _state = BEGIN;
    }
    /**********************************************************
    * Description: 初始化必要基础参数列表
    * Author: 谭宇宏
    * Created Date: 2022/10/10
    ***********************************************************/
    const int maxFrared = 100 * 1.25;
    const int maxMeHasBall = int(50 * 1.25);
    int _executor = task().executor;
    int tandemNum = task().ball.receiver;
    int DoNotEnterDefenseBox = PlayerStatus::DODGE_OUR_DEFENSE_BOX;
    int AllowDribbleFlag = PlayerStatus::DRIBBLING;
    int ShootAllowDribble = DoNotEnterDefenseBox | AllowDribbleFlag;
    int ShootNotNeedDribble = DoNotEnterDefenseBox & (~AllowDribbleFlag);
    bool frared = RobotSensor::Instance()->IsInfraredOn(_executor);
    if (frared) { infraredOn = infraredOn >= maxFrared ? maxFrared : infraredOn + 1; }
    else { infraredOn = 0; }

    /**********************************************************
    * Description: 初始化任务参数列表
    * Author: 谭宇宏
    * Created Date: 2022/10/10
    ***********************************************************/
    const PlayerVisionT& me = pVision->OurPlayer(_executor);
    const BallVisionT& ball = pVision->Ball();
    int GoalieNumber = 0;
    bool isMeHasBall = false;
    bool isMechHasBall = infraredOn >= 2;
    printf("%d\n", infraredOn);
    bool visionHasBall = isVisionHasBall(pVision, _executor);
    isMeHasBall = isMechHasBall; //isMechHasBall&&
    if (isMeHasBall) {
        meHasBall = meHasBall >= maxMeHasBall ? maxMeHasBall : meHasBall + 1;
        meLoseBall = 0;
    }
    else {
        meHasBall = 0;
        meLoseBall = meLoseBall >= maxMeHasBall ? maxMeHasBall : meLoseBall + 1;
    }
    opponentID = pVision->TheirPenaltyGoalie();
    double BallToOurGoal = (ball.Pos() - ourGoal).mod();
    CVector me2goal = theirCenter - me.Pos();
    const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
    const CVector opp2ball = ball.Pos() - opp.Pos();
    double ball2oppDist = opp2ball.mod();
    double ball2meDist = (ball.Pos() - me.Pos()).mod();
    KickorPassDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(_executor).Pos());
    CGeoPoint ShootPoint, PassPoint;/*传球与射门的方向 应该用一个变量表示 具有可持续化的作用*/

    NormalPlayUtils::generatePassPoint(ball.Pos(), SupportPoint[0], SupportPoint[1], SupportPoint[2], SupportPoint[3]);
    /* Gpu算点 */

    /**********************************************************
    * Description: 屏幕右侧 画出has与lose的图像
    * Author: 谭宇宏
    * Created Date: 2022/10/10
    ***********************************************************/
    if (Advance_DEBUG_ENGINE) {
        GDebugEngine::Instance()->gui_debug_x(CGeoPoint(-545, -int(300 * meHasBall / maxMeHasBall)), COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_x(CGeoPoint(-575, -int(300 * meLoseBall / maxMeHasBall)), COLOR_ORANGE);
        GDebugEngine::Instance()->gui_debug_x(CGeoPoint(-545, -int(300 * meHasBall / maxMeHasBall)), COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_x(CGeoPoint(-575, -int(300 * meLoseBall / maxMeHasBall)), COLOR_ORANGE);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-545, -300), "HAS", COLOR_BLACK);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-575, -300), "LOSE", COLOR_BLACK);
    }

    /**********************************************************
    * Description: 状态分配
    * Author: 江亮成
    * Created Date: 2023/5/9
    ***********************************************************/
    switch (_state) {
    case BEGIN:
        _state = GET;
        break;
    case GET:
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push GET", COLOR_YELLOW);
        if (meHasBall > 5) {
            if (me2goal.mod() < KICK_DIST) {
                if (tendToShoot(pVision, _executor)) {
                    _state = KICK; break;
                }
                else if (Me2OppTooclose(pVision, _executor)) {
                    _state = CHIP; break;
                }
                else {
                    _state = BREAKSHOOT; break;
                }
            }
            else {
                if (fabs(opp.VelX()) > 150 ) {
                    _state = CHIP; break;
                }
                else if (Me2OppTooclose(pVision, _executor)) {
                    _state = CHIP; break;
                }
                else if (me2goal.mod() > KICK_DIST + 30){
                    _state = NORMAL_PUSH; break;
                }
                else {
                    _state = BREAKSHOOT; break;
                }
            }
        }
        else { _state = GET; break; }
    case CHIP: //emergency chip
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push CHIP", COLOR_YELLOW);
        if (meLoseBall > 15 && ball2meDist > 10) _state = GET;
        break;
    case CHIP1: //directintotheirgoal
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push CHIP1", COLOR_YELLOW);
        if (meLoseBall > 15 && ball2meDist > 10) _state = GET;
        break;
    case KICK:
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push KICK", COLOR_YELLOW);
        if (meLoseBall > 15 && ball2meDist > 10) _state = GET;
        break;
    case BREAKSHOOT:
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -400), "Push BREAKSHOOT", COLOR_YELLOW);
        if (meLoseBall > 18 && ball2meDist > 10) _state = GET;
        break;
    case NORMAL_PUSH:
        normalPushCnt++;
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, 400), "GETtoNORMALPUSH", COLOR_YELLOW);
        if (meLoseBall > 10 * 1.25) {
            if (Advance_DEBUG_ENGINE) { cout << "normalpush --> get" << endl; }
            _state = GET;
        }
        else if (me2goal.mod() < KICK_DIST || Me2OppTooclose(pVision, _executor)) {
            if (Advance_DEBUG_ENGINE) { cout << "normalpush-> breakshoot" << endl; }
            if (tendToShoot(pVision, _executor)) {
                if(isMeHasBall > 5)
                    _state = KICK;
                else
                    _state = GET;
                break;
            }
            else{
                if(isMeHasBall > 5)
                    _state = BREAKSHOOT;
                else
                    _state = GET;
                break;
            }
        }
        else if (abs(Utils::Normalize(me.Dir() - me2goal.dir())) < Param::Math::PI / 36) {
            if (Advance_DEBUG_ENGINE) { cout << "normalpush --> light kick" << endl; }
            _state = LIGHT_KICK;
        }

        break;
    case LIGHT_KICK:
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, 400), "LIGHT KICk", COLOR_YELLOW);
        if (Advance_DEBUG_ENGINE) { cout << "light kick -> lightkick" << endl; }
        if (meLoseBall > 30 * 1) {
            //if (DEBUG_ENGINE) { cout << "light kick --> goto" << endl; }
            _state = GET;
        }
        else if (me2goal.mod() < KICK_DIST || Me2OppTooclose(pVision, _executor)) {
            if (Advance_DEBUG_ENGINE) { cout << "light kick -> shoot" << endl; }
            if (tendToShoot(pVision, _executor)) {
                if(isMeHasBall > 5)
                    _state = KICK;
                else
                    _state = GET;
                break;
            }
            else{
                if(isMeHasBall > 5)
                    _state = BREAKSHOOT;
                else
                    _state = GET;
                break;
            }
        }
        break;
    }


    /**********************************************************
    * Description: 状态执行
    * Author: 谭宇宏
    * Created Date: 2022/10/10
    ***********************************************************/
    switch (_state) {
    case GET:
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "let GET", COLOR_YELLOW);
        if (!ball.Valid()) {
            /*球不合法的情况*/
            if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "Ball invalid", COLOR_ORANGE);
            double faceDir = opp.Dir() + Param::Math::PI;
            setSubTask(PlayerRole::makeItChaseKickV2(_executor, faceDir, ShootNotNeedDribble));
        }
        else {
            /*并没有得到球 需要去getball*/
            if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -300), "LOSE and GETBALL", COLOR_ORANGE);
            //KickorPassDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(_executor).Pos());
            /*此处朝向可持久化即可 不需要进行改变*/
            setSubTask(PlayerRole::makeItNoneTrajGetBallV3(_executor, KickorPassDir, CVector(0, 0), ShootNotNeedDribble, GetBallBias));
        }
        break;
    case KICK:   // 射门
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "KICK", COLOR_YELLOW);
        KickorPassDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(_executor).Pos());
        KickStatus::Instance()->clearAll();
        if (Utils::InTheirPenaltyArea(ball.Pos(), 0)) {
            /*如果球在对方禁区*/
            if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "ball in their PEN", COLOR_ORANGE);
            KickStatus::Instance()->setKick(_executor, KICKPOWER);
            setSubTask(PlayerRole::makeItShootBallV2(_executor, KickorPassDir, ShootNotNeedDribble));
        }
        else {
            /*正常KICK阶段  需要区分是否方向已经转向成功  此处尚未完备可能存在BUG*/
            if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "Let Kick", COLOR_ORANGE);
            if (isDirOK(pVision, _executor, KickorPassDir, 1)) {
                if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "Kick isDirOK", COLOR_ORANGE);
                KickStatus::Instance()->setKick(_executor, KICKPOWER);
                setSubTask(PlayerRole::makeItShootBallV2(_executor, KickorPassDir, ShootNotNeedDribble));
            }
            else {
                //setSubTask(PlayerRole::makeItGoAndTurnKickV4(_executor, kickDir));
                setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, KickorPassDir, CVector(0, 0), ShootNotNeedDribble, GetBallBias));
                if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "Kick is NOT DirOK ", COLOR_ORANGE);
            }
        }
        break;
    case CHIP:
        KickorPassDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(_executor).Pos());
        KickStatus::Instance()->clearAll();
            /*正常KICK阶段  需要区分是否方向已经转向成功  此处尚未完备可能存在BUG*/
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "Let Chip", COLOR_ORANGE);
        if (isDirOK(pVision, _executor, KickorPassDir, 1)) {
            if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "Chip isDirOK", COLOR_ORANGE);
            KickStatus::Instance()->setChipKick(_executor, me2goal.mod() - 50);
        }
        else {
            //setSubTask(PlayerRole::makeItGoAndTurnKickV4(_executor, kickDir));
            setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, KickorPassDir, CVector(0, 0), ShootNotNeedDribble, GetBallBias));
            if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "Chip is NOT DirOK ", COLOR_ORANGE);
        }
        break;
    case CHIP1:
        KickorPassDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(_executor).Pos());
        KickStatus::Instance()->clearAll();
            /*正常KICK阶段  需要区分是否方向已经转向成功  此处尚未完备可能存在BUG*/
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -400), "Let Chip", COLOR_ORANGE);
        if (isDirOK(pVision, _executor, KickorPassDir, 1)) {
            if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "Chip isDirOK", COLOR_ORANGE);
            KickStatus::Instance()->setChipKick(_executor, me2goal.mod() - 80);
        }
        else {
            //setSubTask(PlayerRole::makeItGoAndTurnKickV4(_executor, kickDir));
            setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, KickorPassDir, CVector(0, 0), ShootNotNeedDribble, GetBallBias));
            if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500, -350), "Chip is NOT DirOK ", COLOR_ORANGE);
        }
        break;
    case BREAKSHOOT:
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200, -400), "BREAKSHOOT", COLOR_YELLOW);
        KickStatus::Instance()->clearAll();
        ShootPoint = GenerateBreakShootPoint(pVision, _executor);
        setSubTask(PlayerRole::makeItBreak(_executor, ShootPoint, 1));
        break;
    case NORMAL_PUSH:
        KickDirection::Instance()->GenerateShootDir(_executor, pVision->OurPlayer(_executor).Pos());
        if (pVision->Ball().X() <= 0) { //our half-field - 50(radius of the middle circle)
            KickorPassDir = KickDirection::Instance()->getRealKickDir();
        }
        else {
            KickorPassDir = generateNormalPushDir(pVision, _executor);
        }
        setSubTask(PlayerRole::makeItNoneTrajGetBall(_executor, KickorPassDir, CVector(0, 0), ShootNotNeedDribble, GetBallBias));
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -350), "finish in NorPush", COLOR_ORANGE);
        break;
    case LIGHT_KICK:
        KickStatus::Instance()->clearAll();
        if(pVision->Ball().X() <= -80)
            KickStatus::Instance()->setKick(_executor, 100);
        else if(pVision->Ball().X() <= 50)
            KickStatus::Instance()->setKick(_executor, 80); // kick lightly
        else
            KickStatus::Instance()->setKick(_executor, 50);
        break;
    }

    _cycle = pVision->Cycle();
    CStatedTask::plan(pVision);
}

/**********************************************************
    * Description: 检测类函数，用于视觉与位置等判断
    * Author: 谭宇宏
    * Created Date: 2022/10/10
***********************************************************/
bool CPenaltyKickV2::isVisionHasBall(const CVisionModule* pVision, const int vecNumber) {
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const BallVisionT& ball = pVision->Ball();
    double visionJudgDist = 12;
    bool distVisionHasBall = CVector(me.Pos() - ball.Pos()).mod() <= visionJudgDist;
    bool dirVisionHasBall;
    double meDir = me.Dir();
    double me2Ball = (ball.Pos() - me.Pos()).dir();
    double meDir_me2Ball_Diff = abs(Utils::Normalize((meDir - me2Ball)));
    if (meDir_me2Ball_Diff < Param::Math::PI / 6.0)
        dirVisionHasBall = true;
    else
        dirVisionHasBall = false;
    bool isVisionPossession = dirVisionHasBall && distVisionHasBall;
    return isVisionPossession;
}



bool CPenaltyKickV2::isTheLineBlocked(const CVisionModule* pVision, CGeoPoint startPoint, CGeoPoint targetPoint) {
    /*该条路径上是否会被敌人阻挡*/
    int n = 0;
    const BallVisionT& ball = pVision->Ball();
    bool passBlocked = false;
    double passDir = (targetPoint - startPoint).dir();
    CGeoLine start2Target = CGeoLine(startPoint, passDir);
    CGeoPoint projectionPoint;
    double k_m = 4;
    double opp2LineDist = 1000;
    while (n <= Param::Field::MAX_PLAYER) {
        if (!pVision->TheirPlayer(n).Valid()) { n++; continue; }
        projectionPoint = start2Target.projection(pVision->TheirPlayer(n).Pos());
        if (opp2LineDist > (projectionPoint - pVision->TheirPlayer(n).Pos()).mod() && projectionPoint.x() < Param::Field::PITCH_LENGTH / 2.0 && projectionPoint.x() > startPoint.x()) {
            opp2LineDist = (projectionPoint - pVision->TheirPlayer(n).Pos()).mod();
            if (opp2LineDist < k_m * Param::Vehicle::V2::PLAYER_SIZE) {
                passBlocked = true;
                break;
            }
        }
        n++;
    }
    return passBlocked;
}

//bug here: opp2Ball
bool CPenaltyKickV2::Me2OppTooclose(const CVisionModule* pVision, const int vecNumber) { //是否太近了
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
    const BallVisionT& ball = pVision->Ball();
    CVector me2Ball = ball.Pos() - me.Pos();
    CVector me2Opp = opp.Pos() - me.Pos();
    CVector Opp2Ball = ball.Pos() - opp.Pos();
    if (abs(me2Ball.mod()) < 80 && abs(Opp2Ball.mod()) < 200) {
        if (Advance_DEBUG_ENGINE) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(450, 450), "TOO CLOSE with ball", COLOR_ORANGE);
        return true;
    }
    return false;
}

bool CPenaltyKickV2::isDirOK(const CVisionModule* pVision, int vecNumber, double targetDir, int ShootOrPass) {
    double ShootPrecision = SHOOT_PRECISION;
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
    double myDir = me.Dir();
    CVector opp2ball = ball.Pos() - opp.Pos();
    CVector ball2goal = theirCenter - ball.Pos();
    if (!ShootOrPass) ShootPrecision = ShootPrecision * 0.85;
    last_target_dir = targetDir;
    //printf("%d %.5lf %.5lf\n", ShootOrPass, myDir, targetDir);
    if (abs(targetDir - last_target_dir) > 0.3 * Param::Math::PI / SHOOT_PRECISION) {
        last_dir_deviation = 100;  //重置角度差
    }
    if (Me2OppTooclose(pVision, vecNumber)) {
        /*太近了 快射*/
        if (abs(myDir - targetDir) < Param::Math::PI / SHOOT_PRECISION) {
            last_dir_deviation = 100;
            return true;
        }
    }
    if ((ShootOrPass && ball2goal.mod() < 250) || (opp2ball.mod() < 200)) {
        /*如果现在是射门且距离球门足够近 不需要过多的调整
          如果敌人离我比较近了 再调整就无法出球了*/
        if (abs(myDir - targetDir) < 0.35 * Param::Math::PI / SHOOT_PRECISION) {
            last_dir_deviation = 100;
            return true;
        }
    }
    if (abs(myDir - targetDir) > 0.25 * Param::Math::PI / SHOOT_PRECISION) {
        /*如果角度过大 应当为false*/
        last_dir_deviation = myDir - targetDir;
        return false;
    }
    else if ((abs(myDir - targetDir) > abs(last_dir_deviation) || (myDir - targetDir) * last_dir_deviation <= 0)) {
        /*如果相比上次角度并没有得到有效调整*/
        if (abs(myDir - targetDir) < 0.2 * Param::Math::PI / SHOOT_PRECISION) {
            /*误差相对而言可以接受了*/
            last_dir_deviation = 100;
            return true;
        }
    }
    else if (abs(myDir - targetDir) < 0.15 * Param::Math::PI / SHOOT_PRECISION) {
        /*尽管仍然在调整 但是可以在误差允许的范围内射门*/
        last_dir_deviation = 100;
        return true;
    }
    last_dir_deviation = myDir - targetDir;
    return false;
}


/**********************************************************
    * Description: 状态切换判定类函数，用于状态转化之间的判断
    * Author: 谭宇宏
    * Created Date: 2022/10/10
***********************************************************/
bool CPenaltyKickV2::tendToShoot(const CVisionModule* pVision, int vecNumber) {
    /*判断现在能否射门*/
    // NEEDMODIFY
    int n = 0;
    int best_n = 0;
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const BallVisionT& ball = pVision->Ball();
    bool shootBlocked = false;

    double kickDir = KickDirection::Instance()->getPointShootDir(pVision, pVision->OurPlayer(vecNumber).Pos());
    if (fabs(kickDir - 1000.0) < 10) return false;
    CGeoLine ball2ourGoal = CGeoLine(me.Pos(), kickDir);
    CGeoPoint projectionPoint;
    double k_m = WantToLessShoot;
    double opp2LineDist = 1000;
    while (n <= Param::Field::MAX_PLAYER) {
        if (!pVision->TheirPlayer(n).Valid()) { n++; continue; }
        projectionPoint = ball2ourGoal.projection(pVision->TheirPlayer(n).Pos());
        if (opp2LineDist > (projectionPoint - pVision->TheirPlayer(n).Pos()).mod() && projectionPoint.x() >= me.X()) {
            opp2LineDist = (projectionPoint - pVision->TheirPlayer(n).Pos()).mod();
            best_n = n;
            if (opp2LineDist < k_m * Param::Vehicle::V2::PLAYER_SIZE) {
                shootBlocked = true;
                break;
            }
        }
        n++;
    }
    KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());

    const PlayerVisionT& opp = pVision->TheirPlayer(best_n);
    double me2theirbest = (me.Pos() - opp.Pos()).mod();
    double me2goal = (me.Pos() - theirCenter).mod();
    bool kickValid = KickDirection::Instance()->getIsKickValid();

    /*
    const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);


    double opp2goal = Param::Field::PITCH_LENGTH / 2.0 - opp.Pos().x();
    if (opp2goal < 10) shootBlocked = true;
    */

    if (shootBlocked) return false;
    else return kickValid;
}


/**********************************************************
    * Description: 生成类函数，具有具体实义
    * Author: 谭宇宏
    * Created Date: 2022/10/10
***********************************************************/
double CPenaltyKickV2::JustChipDir(const CVisionModule* pVision, int vecNumber) {
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    CGeoPoint passPointLeft = SupportPos2022::Instance()->getSupportPos(pVision).getLeftSupportPos();
    CGeoPoint passPointRight = SupportPos2022::Instance()->getSupportPos(pVision).getRightSupportPos();
    double LeftShootDir = KickDirection::Instance()->getPointShootDir(pVision, passPointLeft);
    double RightShootDir = KickDirection::Instance()->getPointShootDir(pVision, passPointRight);
    double passDir = 0;
    int pass = 0;
    double me2left = (me.Pos() - passPointLeft).mod();
    double me2right = (me.Pos() - passPointRight).mod();
    if (me2left > me2right) {
        pass = 1;
        passDir = (passPointLeft - me.Pos()).dir();
    }
    if (me2left < me2right) {
        pass = 2;
        passDir = (passPointRight - me.Pos()).dir();
    }
    if (abs(me2left - me2right) < 50) {
        if (last_pass == 1) {
            pass = 1;
            passDir = (passPointLeft - me.Pos()).dir();
        }
        if (last_pass == 2) {
            pass = 2;
            passDir = (passPointRight - me.Pos()).dir();
        }
        if (last_pass == 0) {
            passDir = (passPointLeft - me.Pos()).dir();
            pass = 1;
        }
    }
    if (me2left < 200) {
        pass = 2;
        passDir = (passPointRight - me.Pos()).dir();
    }
    if (me2right < 200) {
        pass = 1;
        passDir = (passPointLeft - me.Pos()).dir();
    }
    last_pass = pass;
    return passDir;
}

CGeoPoint CPenaltyKickV2::GenerateBreakShootPoint(const CVisionModule* pVision, int vecNumber) {
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    CGeoPoint ShootPoint =KickDirection::Instance()->GetTheShootPoint(pVision, me.Pos());
    ShootPoint.setY(ShootPoint.y() - me.VelY()*3);
    if(me.Y() < -120)ShootPoint.setY(ShootPoint.y() + me.VelX()*2 + me.Y()*0.75);
    else if(me.Y() > 120)ShootPoint.setY(ShootPoint.y() - me.VelX()*2 - me.Y()*0.75);
    //double MeVel = me.VelY()
    if(ShootPoint.y() < -80)ShootPoint.setY(-80);
    if(ShootPoint.y() > 80)ShootPoint.setY(80);

    return ShootPoint;
}

/**********************************************************
    * Description: for normalpush
    * Author: jlc
    * Created Date: 2022/11/18
***********************************************************/

double CPenaltyKickV2::generateNormalPushDir(const CVisionModule* pVision, const int vecNumber) {
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
    const BallVisionT& ball = pVision->Ball();
    double faceDir = 0.0;
    return faceDir;
    if (!opp.Valid()) {
        KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
        faceDir = KickDirection::Instance()->getRealKickDir();
        return faceDir;
    }
    if (abs(ball.Pos().y()) < Param::Field::PITCH_WIDTH / 2 * 0.4 || me.Pos().x() < -50 /* || !checkBallFront(pVision, Param::Math::PI / 4.0)*/) {
        //cout << "there there there" << endl;
        KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
        faceDir = KickDirection::Instance()->getRealKickDir();
        return faceDir;
    }
    else if (abs(ball.Pos().y()) > Param::Field::PITCH_WIDTH / 2 * 0.70) {
        //cout << "here here here" << endl;
        faceDir = opp.Dir() + Param::Math::PI;
        return faceDir;
    }
    else {
        KickDirection::Instance()->GenerateShootDir(vecNumber, pVision->OurPlayer(vecNumber).Pos());
        double kickDir = KickDirection::Instance()->getRealKickDir();
        double maxDir = Utils::Normalize(opp.Dir() + Param::Math::PI);
        double diffDir = Utils::Normalize(kickDir - maxDir);
        if (abs(diffDir) < Param::Math::PI / 15 || (kickDir > 0 && maxDir > kickDir) || (kickDir < 0 && maxDir < kickDir)) {
            return kickDir;
        }
        else {
            faceDir = Utils::Normalize(kickDir - diffDir * (3.33 * (abs(ball.Pos().y()) / (Param::Field::PITCH_WIDTH / 2)) - 1.33));
            return faceDir;
        }
    }
}
/*bool CPenaltyKickV2::isMePassedOpp(const CVisionModule* pVision, const int vecNumber) {
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const PlayerVisionT& opp = pVision->TheirPlayer(opponentID);
    const BallVisionT& ball = pVision->Ball();

    CVector me2opp = opp.Pos() - me.Pos();
    CVector opp2Ball = ball.Pos() - opp.Pos();
    CVector ball2Opp = opp.Pos() - ball.Pos();
    CVector me2Ball = ball.Pos() - me.Pos();
    bool meDirControlBall = abs(Utils::Normalize(me2Ball.dir() - me.Dir())) < Param::Math::PI / 4;
    bool meDistControlBall = me2Ball.mod() < Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + 10.5;
    bool mePassOpp_1 = abs(Utils::Normalize(me2Ball.dir() - me2opp.dir())) > Param::Math::PI / 2.5;
    bool mePassOpp_2 = abs(Utils::Normalize(opp.Dir() - ball2Opp.dir())) < Param::Math::PI / 3.0;
    if (meDistControlBall && meDistControlBall && (mePassOpp_1 || mePassOpp_2) || me2opp.mod() > 25) {
        // GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 0), "PASS!!!!!!!!!!!", COLOR_WHITE);
        return true;
    }
    else {
        return false;
    }
}*/

CPlayerCommand* CPenaltyKickV2::execute(const CVisionModule* pVision) {
    if (subTask()) {
        return subTask()->execute(pVision);
    }
    if (_directCommand) {
        return _directCommand;
    }
    return 0;
}

