#ifndef GUARDPOS_H
#define GUARDPOS_H

#include "Vision/VisionModule.h"
#include "singleton.h"
#include "PointCalculation/MarkingPosV2.h"

class CGuardPos
{
public:
	CGuardPos();
	CGeoPoint backPos(int guardNum, int index);
	void setBackNum(int realNum, int index);
	enum Tback_state { NOT_BACK, MISSING_BACK, COMING_BACK, READY_BACK };
	struct TbackStatus {
		TbackStatus() :pos(CGeoPoint()), num(0), cycle(0), state(NOT_BACK) {}
		CGeoPoint pos;
		int num;
		int cycle;
		Tback_state state;
	};

private:
	void checkBackPos();
	CGeoPoint chooseTargetPos();
	void generatePos(TbackStatus* status_begin, TbackStatus* status_end, CGeoPoint target);
	void adjustBackPos();
	bool leftNextPos(CGeoPoint basePos, CGeoPoint& nextPos, double dist = -9999);
	bool rightNextPos(CGeoPoint basePos, CGeoPoint& nextPos, double dist = -9999);

	int _cycle;
	int _guardNum;
	int ready_cnt, coming_cnt, missing_cnt;
	TbackStatus _status[Param::Field::MAX_PLAYER];
};

typedef Falcon::NormalSingleton<CGuardPos> GuardPos;
#endif // GUARDPOS_H
