#include "GuardPos.h"
#include "GDebugEngine.h"
#include "Global.h"
#include "param.h"
#include "TaskMediator.h"

namespace {
    const CGeoPoint GOAL_MIDDLE = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
    const CGeoPoint GOAL_LEFT = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, -Param::Field::PITCH_WIDTH / 2);
    const CGeoPoint GOAL_RIGHT = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, Param::Field::PITCH_WIDTH / 2);
    const double MIN_DIST_TO_PENALTY = Param::Vehicle::V2::PLAYER_SIZE * 2;
    const double MIN_DIST_TO_TEAMMATE = Param::Vehicle::V2::PLAYER_SIZE * 2 + Param::Field::BALL_SIZE * 2;
    // ???????????¶∂
    CGeoPoint PENALTY_RIGHT_UP(-Param::Field::PITCH_LENGTH / 2 + ParamManager::Instance()->PENALTY_AREA_DEPTH + MIN_DIST_TO_PENALTY, -(Param::Field::PENALTY_AREA_WIDTH / 2 + MIN_DIST_TO_PENALTY));
    CGeoPoint PENALTY_RIGHT_DOWN(-Param::Field::PITCH_LENGTH / 2 + ParamManager::Instance()->PENALTY_AREA_DEPTH + MIN_DIST_TO_PENALTY, Param::Field::PENALTY_AREA_WIDTH / 2 + MIN_DIST_TO_PENALTY);
    CGeoPoint PENALTY_LEFT_UP(-Param::Field::PITCH_LENGTH / 2, -(Param::Field::PENALTY_AREA_WIDTH / 2 + MIN_DIST_TO_PENALTY));
    CGeoPoint PENALTY_LEFT_DOWN(-Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2 + MIN_DIST_TO_PENALTY);
    CGeoRectangle guardMoveRec(PENALTY_LEFT_UP, PENALTY_RIGHT_DOWN);
    // ????????????
    CGeoPoint LEFTBACK_CRITICAL_POINT = CGeoPoint(-(Param::Field::PITCH_LENGTH / 2 - ParamManager::Instance()->PENALTY_AREA_DEPTH - Param::Vehicle::V2::PLAYER_SIZE), -Param::Field::PITCH_WIDTH / 2);
    CGeoPoint RIGHTBACK_CRITICAL_POINT = CGeoPoint(-(Param::Field::PITCH_LENGTH / 2 - ParamManager::Instance()->PENALTY_AREA_DEPTH - Param::Vehicle::V2::PLAYER_SIZE), Param::Field::PITCH_WIDTH / 2);
    bool DEBUG_GUARD_POS = false;
    const double VALID_THRESHOLD = 500;

    bool CheckBackPos = true;
    int dangerVel = 15;
    int dangerDist = 50;
    CGeoPoint DebugPoint(-650, -470);
}

CGuardPos::CGuardPos()
{
    std::fill_n(_backNum, Param::Field::MAX_PLAYER, TaskMediator::Instance()->goalie());
    std::fill_n(_backCycle, Param::Field::MAX_PLAYER, 0);
    std::fill_n(_readyBack, Param::Field::MAX_PLAYER, true);
    CheckBackPos = ParamManager::Instance()->CheckBackPos;
    dangerVel = ParamManager::Instance()->dangerVel;
    dangerDist = ParamManager::Instance()->dangerDist;
}

void CGuardPos::generatePos(int guardNum)
{
    // ????????????
    guardNum = std::min(Param::Field::MAX_PLAYER, std::max(1, guardNum));
    const BallVisionT& Ball = vision->Ball();
    // ????????
    int bestenemy = BestPlayer::Instance()->getTheirBestPlayer();
    CGeoPoint defendTarget = Ball.Valid() ? Ball.Pos() : vision->TheirPlayer(bestenemy).Pos();
    if ((defendTarget - GOAL_MIDDLE).dir() > (RIGHTBACK_CRITICAL_POINT - GOAL_MIDDLE).dir()) // ???Target????????????/??????????Ì‡????????????
        defendTarget = RIGHTBACK_CRITICAL_POINT;
    else if ((defendTarget - GOAL_MIDDLE).dir() < (LEFTBACK_CRITICAL_POINT - GOAL_MIDDLE).dir())
        defendTarget = LEFTBACK_CRITICAL_POINT;
    GDebugEngine::Instance()->gui_debug_msg(defendTarget, "target", COLOR_CYAN);

    CGeoLine targetToMiddle(defendTarget, GOAL_MIDDLE); // ???????????????
    CGeoLine targetToLeft(defendTarget, GOAL_LEFT);
    CGeoLine targetToRight(defendTarget, GOAL_RIGHT);
    CGeoLine EnemyDir(defendTarget, vision->TheirPlayer(bestenemy).Dir());
    double diffAngle = vision->TheirPlayer(bestenemy).Dir() - (GOAL_MIDDLE - defendTarget).dir();
    // ??????????????????????????????????????????????¶À
    CGeoLineRectangleIntersection intersecMiddle(targetToMiddle, guardMoveRec);
    if (vision->TheirPlayer(bestenemy).Pos().dist(defendTarget) < 20 && defendTarget.x() < -250 && fabs(diffAngle) < atan(0.5))
        intersecMiddle = CGeoLineRectangleIntersection(EnemyDir, guardMoveRec);
    if (intersecMiddle.intersectant()) {
        // ?ß‹???
        bool leftValid = true, rightValid = true;
        if (guardNum % 2 == 1) { // ?????????????ßﬁ?????ß‹???
            _backPos[guardNum / 2] = intersecMiddle.point2().dist(GOAL_MIDDLE) < 1e-8 ? intersecMiddle.point1() : intersecMiddle.point2(); // ????ß⁄????????????ß÷?????????
            for (int i = 0; i < guardNum / 2; i++) { // ???ß‹????????????????????????????????
                leftValid = leftNextPos(_backPos[guardNum / 2 - i], _backPos[guardNum / 2 - i - 1]);
                rightValid = rightNextPos(_backPos[guardNum / 2 + i], _backPos[guardNum / 2 + i + 1]);
            }
        }
        else { // ???????????????ß‹???
            CGeoPoint intersecPos = intersecMiddle.point2().dist(GOAL_MIDDLE) < 1e-8 ? intersecMiddle.point1() : intersecMiddle.point2();
            leftValid = leftNextPos(intersecPos, _backPos[guardNum / 2 - 1], MIN_DIST_TO_TEAMMATE / 2);
            rightValid = rightNextPos(intersecPos, _backPos[guardNum / 2], MIN_DIST_TO_TEAMMATE / 2);
            for (int i = 0; i < (guardNum - 2) / 2; i++) {
                leftValid = leftNextPos(_backPos[guardNum / 2 - 1 - i], _backPos[guardNum / 2 - 2 - i]);
                rightValid = rightNextPos(_backPos[guardNum / 2 + i], _backPos[guardNum / 2 + 1 + i]);
            }
        }
        if (!leftValid) { // ???????????¶À?®∞???????????????????????????????????????
            for (int i = 1; i < guardNum; i++) {
                rightNextPos(_backPos[i - 1], _backPos[i]);
            }
        }
        if (!rightValid) {
            for (int i = 1; i < guardNum; i++) {
                leftNextPos(_backPos[guardNum - i], _backPos[guardNum - i - 1]);
            }
        }
    }
    else {
        std::cout << "GUARDPOS: NO INTERSECTION!!!\n";
    }
    if (DEBUG_GUARD_POS) {
        for (int i = 0; i < guardNum; i++) {
            //GDebugEngine::Instance()->gui_debug_msg(_backPos[i], QString::number(i, 16).toLatin1(), COLOR_CYAN);
        }
    }
}

CGeoPoint CGuardPos::backPos(int guardNum, int index)
{
    // ????????????
    // guardNum = std::min(Param::Field::MAX_PLAYER, std::max(1, guardNum));
    index = std::min(guardNum, std::max(1, index));
    checkBackPos(guardNum);
    generatePos(guardNum);
    adjustBackPos(guardNum);
    return _backPos[index - 1];
}

void CGuardPos::checkBackPos(int guardNum)
{
    // 2020???ß€???????????????????????????????????????????????????
    // ???????????????
    ready_cnt = 0;
    if (!CheckBackPos || (guardNum != 3 && guardNum != 2)) return;
    for (int i = 0; i < guardNum; i++) {
        if (vision->OurPlayer(_backNum[i]).Pos().dist(_backPos[i]) > dangerDist ||
            abs(_backCycle[i] - vision->Cycle()) > 10 || _backNum[i] == TaskMediator::Instance()->goalie())
            _readyBack[i] = false;
        else {
            _readyBack[i] = true;
            ready_cnt++;
            ready_index = i;
        }
    }
}

void CGuardPos::adjustBackPos(int guardNum)
{
    if (!CheckBackPos || (guardNum != 3 && guardNum != 2)) return;
    const BallVisionT& Ball = vision->Ball();
    int bestenemy = BestPlayer::Instance()->getTheirBestPlayer();
    double defendTargetPosX = Ball.Valid() ? Ball.X() : vision->TheirPlayer(bestenemy).X();
    double defendTargetPosY = Ball.Valid() ? Ball.Y() : vision->TheirPlayer(bestenemy).Y();
    double defendTargetVelX = Ball.Valid() ? Ball.VelX() : vision->TheirPlayer(bestenemy).VelX();
    double defendTargetVelY = Ball.Valid() ? Ball.VelY() : vision->TheirPlayer(bestenemy).VelY();
    bool leftDanger = (defendTargetPosX > PENALTY_RIGHT_UP.x() && defendTargetVelY < -dangerVel) ||
            (defendTargetPosX < PENALTY_RIGHT_UP.x() && defendTargetPosY > 0 && defendTargetVelX > dangerVel) ||
            (defendTargetPosX < PENALTY_RIGHT_UP.x() && defendTargetPosY < 0 && defendTargetVelX < -dangerVel);
    bool rightDanger = (defendTargetPosX > PENALTY_RIGHT_UP.x() && defendTargetVelY > dangerVel) ||
                    (defendTargetPosX < PENALTY_RIGHT_UP.x() && defendTargetPosY > 0 && defendTargetVelX < -dangerVel) ||
                    (defendTargetPosX < PENALTY_RIGHT_UP.x() && defendTargetPosY < 0 && defendTargetVelX > dangerVel);
    CGeoPoint midPoint = _backPos[1], rightPoint = _backPos[2], leftPoint = _backPos[0];
    switch (ready_cnt) {
    case 1:
        GDebugEngine::Instance()->gui_debug_msg(DebugPoint, "SingleBack");
        if (guardNum == 2) {
            midPoint = _backPos[0].midPoint(_backPos[1]);
            rightPoint = _backPos[1];
        }
        if (leftDanger)
            _backPos[ready_cnt] = midPoint.midPoint(leftPoint);
        else if (rightDanger)
            _backPos[ready_cnt] = midPoint.midPoint(rightPoint);
        else
            _backPos[ready_cnt] = midPoint;
        break;
    case 2:
        if (guardNum == 2) break;
        if (!_readyBack[1]) { // ?ß‹????????????¶À??????left/rightBack
            GDebugEngine::Instance()->gui_debug_msg(DebugPoint, "MiddleBack");
            _backPos[0] = midPoint.midPoint(leftPoint);
            _backPos[2] = midPoint.midPoint(rightPoint);
        }
        else if (!_readyBack[0] && leftDanger) { // ??????????????????????
            GDebugEngine::Instance()->gui_debug_msg(DebugPoint, "LeftBack");
            _backPos[2] = midPoint;
            _backPos[1] = leftPoint;
        }
        else if (!_readyBack[2] && rightDanger) { // ?????????????????????
            GDebugEngine::Instance()->gui_debug_msg(DebugPoint, "RightBack");
            _backPos[0] = midPoint;
            _backPos[1] = rightPoint;
        }
        break;
    default:
        GDebugEngine::Instance()->gui_debug_msg(DebugPoint, "NoneBack");
        break;
    }
}

void CGuardPos::setBackNum(int realNum, int index)
{
    if (index < 1 || index > Param::Field::MAX_PLAYER) {
        std::cout << "ERROR in GuardPos: back num out of range\n" << index;
        return;
    }
    _backCycle[index - 1] = vision->Cycle();
    _backNum[index - 1] = realNum;
    TaskMediator::Instance()->setMultiBack(realNum);
    //qDebug() << "backNum" << realNum << index;
}

int CGuardPos::checkValidNum(int guardNum)
{
    int validCnt = 0;
    int missingCnt = 0;
    for (int i = 0; i < guardNum; ++i) {
        //        GDebugEngine::Instance()->gui_debug_msg(vision->OurPlayer(i).Pos(), QString::number(i, 16).toLatin1(), COLOR_RED);
        if (validBackPos(_backPos[i], _backNum[i]))
            validCnt++;
        else {
            _missingBack[missingCnt] = i + 1;
            missingCnt++;
        }
    }
    return validCnt;
}

bool CGuardPos::validBackPos(CGeoPoint backPos, int realNum)
{
    return vision->OurPlayer(realNum).Pos().dist(backPos) <= VALID_THRESHOLD;
}

int CGuardPos::missingBackIndex(int i)
{
    if (i < 1 || i > Param::Field::MAX_PLAYER) {
        std::cout << "ERROR in GuardPos: missing back out of range\n";
        i = std::min(Param::Field::MAX_PLAYER, std::max(1, i));
    }
    return _missingBack[i - 1];
}

bool CGuardPos::leftNextPos(CGeoPoint basePos, CGeoPoint& nextPos, double dist)
{
    if (dist < 0) dist = MIN_DIST_TO_TEAMMATE;
    if (basePos.y() >= PENALTY_RIGHT_UP.y() + dist && fabs(basePos.x() - PENALTY_RIGHT_DOWN.x()) < 1e-8) { // ????????
        // GDebugEngine::Instance()->gui_debug_msg(GOAL_MIDDLE, "mode 1");
        nextPos = basePos + CVector(0, -dist);
    }
    else if (basePos.y() < PENALTY_RIGHT_UP.y() + dist) {
        if (fabs(basePos.x() - PENALTY_RIGHT_UP.x()) < 1e-8) { // ??????????????????????°§
            // GDebugEngine::Instance()->gui_debug_msg(GOAL_MIDDLE, "mode 2");
            nextPos = PENALTY_RIGHT_UP + CVector(-sqrt(pow(dist, 2) - pow(basePos.y() - PENALTY_RIGHT_UP.y(), 2)), 0);
        }
        else if (fabs(basePos.x() - PENALTY_LEFT_UP.x()) >= dist) { // ???????°§
            // GDebugEngine::Instance()->gui_debug_msg(GOAL_MIDDLE, "mode 3");
            nextPos = basePos + CVector(-dist, 0);
        }
        else { // ?ß‹?????¶À??????????????????¶ƒ??????
            // GDebugEngine::Instance()->gui_debug_msg(GOAL_MIDDLE, "mode 4");
            nextPos = PENALTY_LEFT_UP;
            return false;
        }
    }
    else {
        if (fabs(basePos.x() - PENALTY_RIGHT_DOWN.x()) <= dist) { // ??????????????????????????????ú˝???????????????????????????????????
            // GDebugEngine::Instance()->gui_debug_msg(GOAL_MIDDLE, "mode 5");
            nextPos = PENALTY_RIGHT_DOWN + CVector(0, -sqrt(pow(dist, 2) - pow(basePos.x() - PENALTY_RIGHT_DOWN.x(), 2))); //??????????????ß‹??????????????????????dist
        }
        else { // ?????°¿?°§
            // GDebugEngine::Instance()->gui_debug_msg(GOAL_MIDDLE, "mode 6");
            nextPos = basePos + CVector(dist, 0);
        }
    }
    return true;
}

bool CGuardPos::rightNextPos(CGeoPoint basePos, CGeoPoint &nextPos, double dist)
{
    if (dist < 0) dist = MIN_DIST_TO_TEAMMATE;
    if (basePos.y() <= PENALTY_RIGHT_DOWN.y() - dist && fabs(basePos.x() - PENALTY_RIGHT_UP.x()) < 1e-8) {
        nextPos = basePos + CVector(0, dist);
    }
    else if (basePos.y() > PENALTY_RIGHT_DOWN.y() - dist) {
        if (fabs(basePos.x() - PENALTY_RIGHT_DOWN.x()) < 1e-8) {
            nextPos = PENALTY_RIGHT_DOWN + CVector(-sqrt(pow(dist, 2) - pow(basePos.y() - PENALTY_RIGHT_DOWN.y(), 2)), 0);
        }
        else if (fabs(basePos.x() - PENALTY_LEFT_DOWN.x()) >= dist) {
            nextPos = basePos + CVector(-dist, 0);
        }
        else {
            nextPos = PENALTY_LEFT_DOWN;
            return false;
        }
    }
    else {
        if (fabs(basePos.x() - PENALTY_RIGHT_UP.x()) <= dist) {
            nextPos = PENALTY_RIGHT_UP + CVector(0, sqrt(pow(dist, 2) - pow(basePos.x() - PENALTY_RIGHT_UP.x(), 2)));
        }
        else {
            nextPos = basePos + CVector(dist, 0);
        }
    }
    return true;
}
