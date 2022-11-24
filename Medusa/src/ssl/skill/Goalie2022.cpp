#include "Goalie2022.h"
#include "PointCalculation/DefPos2013.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "skill/Factory.h"
#include <utils.h>
#include <WorldModel/DribbleStatus.h>
#include "WorldModel/KickStatus.h"
#include <RobotSensor.h>
#include "param.h"
#include "BallSpeedModel.h"
#include "WorldModel/WorldModel.h"
#include <TaskMediator.h>
//#include <atlstr.h>

//#define DEBUGING
#ifdef DEBUGING
#define MSG(x) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,-350), x)
#define DBG(x) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,-300), x)
#else
#define MSG(x) {}
#define DBG(x) {}
#endif

namespace {
    CGeoPoint goalCenter;
    double PENALTY_BUFFER;
    double SLOW_BALL_SPD;
    int KICKPOWER;
    double HAVE_BALL_DIST;
    double CLOSE_DIST;
    bool AGGRESSIVE_GOALIE;
    double CHALLENGE_BALL_DIST;
    double BLOCK_DIST;
}

CGoalie2022::CGoalie2022()
{
    goalCenter = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
    PENALTY_BUFFER = 0.1 * Param::Field::PENALTY_AREA_DEPTH;
    SLOW_BALL_SPD = paramManager->SLOW_BALL_SPD;
    KICKPOWER = paramManager->KICKPOWER_GOALIE;
    HAVE_BALL_DIST = paramManager->HAVE_BALL_DIST;
    CLOSE_DIST = paramManager->CLOSE_DIST;
    AGGRESSIVE_GOALIE = false ;//paramManager->AGGRESSIVE_GOALIE;
    CHALLENGE_BALL_DIST = paramManager->CHALLENGE_BALL_DIST;
    BLOCK_DIST = paramManager->BLOCK_DIST;
}

void CGoalie2022::plan(const CVisionModule* pVision)
{
    int purpose = evaluate(pVision);
    CPlayerTask* pTask;
    switch (purpose) {
    case TEST:
        break;
    case NORMAL:
        pTask = normalTask(pVision);
        break;
    case SUPPORT:
        pTask = supportTask(pVision);
        break;
    case CLEAR_BALL:
        pTask = clearBallTask(pVision);
        break;
    case ATTACK_ENEMY:
        pTask = attackEnemyTask(pVision);
        break;
    }
    setSubTask(pTask);
    CStatedTask::plan(pVision);
}

CPlayerCommand* CGoalie2022::execute(const CVisionModule* pVision)
{
    if (subTask())
    {
        return subTask()->execute(pVision);
    }
    return NULL;
}

int CGoalie2022::evaluate(const CVisionModule* pVision)
{
    int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const PlayerVisionT enemy = pVision->TheirPlayer(BestPlayer::Instance()->getTheirBestPlayer());
    const BallVisionT& ball = pVision->Ball();

    if (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop") {
        DBG("evaluate: game stop");
        return NORMAL;
    } else if (!ball.Valid()) {
        DBG("evaluate: invalid ball");
        return NORMAL;
    } else if (IsFarFromBack(ball.Pos())) {
        DBG("evaluate: far ball");
        return NORMAL;
    } else if (ShouldAttack(pVision)) {
        DBG("evaluate: danger, attack enemy");
        return ATTACK_ENEMY;
    } else if (Utils::InOurPenaltyArea(ball.Pos(), PENALTY_BUFFER)) {
        if (ball.Vel().mod() < SLOW_BALL_SPD) {
            if (enemy.Pos().dist(ball.Pos()) < HAVE_BALL_DIST) {
                //&& Utils::InOurPenaltyArea(enemy.Pos(), -10)) {
                DBG("evaluate: slow ball, enemy inside, clear ball");
                return CLEAR_BALL;
            } else {
                DBG("evaluate: slow ball, safe to support");
                return SUPPORT;
            }
        } else {//球速较高
            if (DefendUtils::isBallShotToTheGoal()) {
                DBG("evaluate: fast ball, to goal, emergency");
                return NORMAL;//实际情况紧急，不确定NORMAL能否应对
            } else {
                DBG("evaluate: fast ball, not to goal");
                return NORMAL;
            }
        }
    } else {
        DBG("evaluate: normal");
        return NORMAL;
    }
}

bool CGoalie2022::ShouldAttack(const CVisionModule* pVision)
{
    /************************************************************************/
    /* 若对面在靠中前的位置打算单刀，且我方后卫支援困难，这种时候就要主动出击。
       同时，主动出击风险较大，因此用return false添加限制逻辑为主  by SYLG */
    /************************************************************************/
    if (!AGGRESSIVE_GOALIE)
        return false;
    int robotNum = task().executor;
    const PlayerVisionT& enemy = pVision->TheirPlayer(BestPlayer::Instance()->getTheirBestPlayer());
    const BallVisionT& ball = pVision->Ball();

    if (abs(enemy.Pos().y()) > Param::Field::PENALTY_AREA_WIDTH / 2.0 + 30
        || enemy.Pos().dist(ball.Pos()) > CLOSE_DIST)
        return false;
    for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
    {
        if (robotNum != i)
        {
            const PlayerVisionT& helper_i = pVision->OurPlayer(i);
            if (helper_i.Pos().dist(enemy.Pos()) < CLOSE_DIST
                || helper_i.Pos().dist(ball.Pos()) < CLOSE_DIST)//已经有帮手了
                return false;
        }
    }
    //现行防守框架下，有后卫则无需支援
    if (TaskMediator::Instance()->leftBack() || TaskMediator::Instance()->rightBack() || TaskMediator::Instance()->singleBack())
        return false;
    //综合判断敌我形势。目前这一段还比较粗糙 by SYLG
    int free_enemy = 0;
    for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
    {
        const PlayerVisionT& enemy_i = pVision->TheirPlayer(i);
        if (IsFarFromBack(enemy_i.Pos()) == false)
        {
            free_enemy++;
            for (int j = 0; j < Param::Field::MAX_PLAYER; j++)
            {
                if (pVision->OurPlayer(j).Pos().dist(enemy_i.Pos()) < CLOSE_DIST)
                {
                    free_enemy--;
                    break;
                }
            }
        }
    }
    return free_enemy <= 1;
}

inline bool CGoalie2022::IsFarFromBack(const CGeoPoint& pos, int x)
{
    return pos.x() > x;
}

CPlayerTask* CGoalie2022::normalTask(const CVisionModule* pVision)
{
    MSG("goalie in normal");

    int robotNum = task().executor;

    CGeoPoint DefPoint = DefPos2015::Instance()->getDefPos2015(pVision).getGoaliePos();

    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);

    double dir;
    if (ball.Valid()) {
        dir = CVector(ball.Pos() - me.Pos()).dir();
    } else {
        dir = CVector(me.Pos() - goalCenter).dir();
    }

    int flag = task().player.flag;
    flag |= PlayerStatus::QUICKLY;

    return PlayerRole::makeItGoto(robotNum, DefPoint, dir, flag);
}

CPlayerTask* CGoalie2022::supportTask(const CVisionModule* pVision)
{
    MSG("goalie in support");

    int robotNum = task().executor;
    int leaderNum = BestPlayer::Instance()->getOurBestPlayer();

    if (robotNum == leaderNum) {//实际情况下不太可能出现
        return clearBallTask(pVision);
    }

    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const PlayerVisionT& leader = pVision->OurPlayer(leaderNum);

    double dir = CVector(leader.Pos()-me.Pos()).dir();

    //中国赛临时支援策略
    dir = CVector(CGeoPoint(400,0)-me.Pos()).dir();

    int flag = task().player.flag;
    flag |= PlayerStatus::QUICKLY;
    flag |= PlayerStatus::DRIBBLING;

    double power = 500;
    KickStatus::Instance()->setChipKick(robotNum, power);
    return PlayerRole::makeItNoneTrajGetBall(robotNum, dir, CVector(0, 0), flag);
}

CPlayerTask* CGoalie2022::clearBallTask(const CVisionModule* pVision)
{
    //防乌龙还没写进来
    MSG("goalie in clear");

    int robotNum = task().executor;

    double dir = CalClearBallDir(pVision);

    int flag = task().player.flag;
    flag |= PlayerStatus::QUICKLY;
    flag |= PlayerStatus::DRIBBLING;

    return PlayerRole::makeItNoneTrajGetBall(robotNum, dir, CVector(0, 0), flag);
    //拿到球后通过lua层面检测会自己踢出去
}

CPlayerTask* CGoalie2022::attackEnemyTask(const CVisionModule* pVision)
{
    MSG("goalie in attack");

    int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const PlayerVisionT& enemy = pVision->TheirPlayer(BestPlayer::Instance()->getTheirBestPlayer());
    const BallVisionT& ball = pVision->Ball();

    //距敌人过近时会因路径不可达而跑歪，此时直接抢球即可
    CGeoPoint pos;
    if (me.Pos().dist(enemy.Pos())> CHALLENGE_BALL_DIST) {
        pos = enemy.Pos();
    } else {
        pos = ball.Pos();
    }

    double dir;
    if (ball.Valid()) {
        dir = CVector(ball.Pos() - me.Pos()).dir();
    } else {
        dir = CVector(me.Pos() - goalCenter).dir();
    }

    int flag = task().player.flag;
    flag |= PlayerStatus::QUICKLY;
    flag |= PlayerStatus::DRIBBLING;

    return PlayerRole::makeItGoto(robotNum, pos, dir, flag);
}

double CGoalie2022::CalClearBallDir(const CVisionModule * pVision)
{
    /************************************************************************/
    /* 清球角度的计算。目前战术安排均采用双后卫即leftBack+rightBack策略，
       因此仅重写相关部分的逻辑，单后卫的代码继承于Goalie2013
       且在目前规则与代码框架下，理论上不需要此部分代码，仅作为留档保留于此 by SYLG */
    /************************************************************************/
    int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT enemy = pVision->TheirPlayer(BestPlayer::Instance()->getTheirBestPlayer());
    double clearBallDir = 0;
    if (TaskMediator::Instance()->singleBack() == 0 && TaskMediator::Instance()->leftBack() != 0) {
        CGeoPoint leftpos = DefPos2015::Instance()->getDefPos2015(pVision).getLeftPos();
        CGeoPoint rightpos = DefPos2015::Instance()->getDefPos2015(pVision).getRightPos();
        double ball2leftDir = (DefPos2015::Instance()->getDefPos2015(pVision).getLeftPos() - ball.Pos()).dir();// -0.3;
        double ball2rightDir = (DefPos2015::Instance()->getDefPos2015(pVision).getRightPos() - ball.Pos()).dir();// +0.3;
        double goal2ballDir = CVector(ball.Pos() - goalCenter).dir();
        GDebugEngine::Instance()->gui_debug_line(ball.Pos(), ball.Pos() + Utils::Polar2Vector(200, ball2leftDir), COLOR_BLACK);
        GDebugEngine::Instance()->gui_debug_line(ball.Pos(), ball.Pos() + Utils::Polar2Vector(200, ball2rightDir), COLOR_BLACK);
        if (goal2ballDir>ball2leftDir && goal2ballDir<ball2rightDir)
        {
            if (ball2rightDir - ball2leftDir > Param::Math::PI / 2) {
                clearBallDir = Utils::Normalize((ball2leftDir + ball2rightDir) / 2);
            } else {
                vector<double> blockDirList{-Param::Math::PI,Param::Math::PI};
                for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
                {
                    CGeoPoint pos = pVision->OurPlayer(i).Pos();
                    if (pos.dist(ball.Pos()) < BLOCK_DIST && i!=robotNum)
                        blockDirList.push_back((pos-ball.Pos()).dir());
                    pos = pVision->TheirPlayer(i).Pos();
                    if (pos.dist(ball.Pos()) < BLOCK_DIST)
                        blockDirList.push_back((pos - ball.Pos()).dir());
                }
                sort(blockDirList.begin(), blockDirList.end());
                double maxAngle = 0;
                for (int i = 0; i < blockDirList.size() - 1; i++)
                    if (blockDirList[i + 1] - blockDirList[i] > maxAngle) {
                        maxAngle = blockDirList[i + 1] - blockDirList[i];
                        clearBallDir = (blockDirList[i + 1] + blockDirList[i]) / 2.0;
                    }
            }
        } else {
            clearBallDir = Utils::Normalize(goal2ballDir);
        }
    } else if (TaskMediator::Instance()->singleBack() != 0) {
        double goal2singledir = (DefPos2015::Instance()->getDefPos2015(pVision).getSinglePos() - ball.Pos()).dir();
        if (std::abs(goal2singledir - clearBallDir) < Param::Math::PI / 18) {
            if (std::abs(clearBallDir) > Param::Math::PI / 10) {
                clearBallDir = -clearBallDir;
                if (std::abs(clearBallDir) > Param::Math::PI * 70 / 180) {
                    if (clearBallDir < 0) {
                        clearBallDir = clearBallDir + Param::Math::PI / 9;
                    } else {
                        clearBallDir = clearBallDir - Param::Math::PI / 9;
                    }
                }
            } else {
                clearBallDir = clearBallDir + Param::Math::PI * 7 / 18;
            }
        }
    } else {
        clearBallDir = CVector(ball.Pos() - goalCenter).dir();
    }

    //太近了还是直接用原始方向比较稳妥
    if (enemy.Pos().dist(ball.Pos()) < CLOSE_DIST) {
        clearBallDir = CVector(ball.Pos() - goalCenter).dir();
    }

    //角度限制
    if (clearBallDir >= Param::Math::PI * 80 / 180.0) {
        clearBallDir = Param::Math::PI * 80 / 180.0;
    } else if (clearBallDir <= -Param::Math::PI * 80 / 180.0) {
        clearBallDir = -Param::Math::PI * 80 / 180.0;
    }

    GDebugEngine::Instance()->gui_debug_line(ball.Pos(), ball.Pos() + Utils::Polar2Vector(600, clearBallDir), COLOR_BLUE);
    return clearBallDir;
}
