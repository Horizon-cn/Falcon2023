#ifndef GUARDPOS_H
#define GUARDPOS_H

#include "Vision/VisionModule.h"
#include "singleton.h"

class CGuardPos
{
public:
    CGuardPos();
    CGeoPoint backPos(int guardNum, int index);
    void setBackNum(int realNum, int index);
    int checkValidNum(int guardNum);
    bool validBackPos(CGeoPoint backPos, int realNum);
    int missingBackIndex(int i);
private:
    void generatePos(int guardNum);
    CGeoLineRectangleIntersection intersecMiddle(int enemyNum);
    CGeoLineRectangleIntersection intersecMiddleNoBall(int enemyNum);
    bool leftNextPos(CGeoPoint basePos, CGeoPoint& nextPos, double dist=-9999);
    bool rightNextPos(CGeoPoint basePos, CGeoPoint& nextPos, double dist=-9999);
    void checkBackPos(int guardNum);
    void adjustBackPos(int guardNum);
    int ready_cnt;
    int ready_index;
    CGeoLineRectangleIntersection _intersecMiddle;
    CGeoPoint _backPos[Param::Field::MAX_PLAYER];
    int _backNum[Param::Field::MAX_PLAYER];
    int _missingBack[Param::Field::MAX_PLAYER];
    bool _readyBack[Param::Field::MAX_PLAYER];
    int _backCycle[Param::Field::MAX_PLAYER];
};

typedef Falcon::NormalSingleton<CGuardPos> GuardPos;
#endif // GUARDPOS_H
