#ifndef RUSH_H
#define RUSH_H

#include <skill/PlayerTask.h>
#include <WorldModel/WorldDefine.h>
#include <Vision/VisionModule.h>
#include "PathPlan/ObstacleNew.h"

class CRush : public CStatedTask {
public:
	CRush();
	virtual void plan(const CVisionModule* pVision);
	virtual CPlayerCommand* execute(const CVisionModule* pVision);

protected:
	virtual void toStream(std::ostream& os) const;

private:
	int cnt;
	int _lastCycle;
	int playerFlag;
	CGeoPoint old_pos;
	CPlayerCommand* _directCommand;
	CGeoPoint calc_point(const CVisionModule* pVision, const int vecNumber, const CGeoPoint TargetPos);
};
#endif RUSH_H