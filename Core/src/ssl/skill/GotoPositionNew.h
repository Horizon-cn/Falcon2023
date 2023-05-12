/*************************************************
* 新版车控skill(V2)，旨在用全新规划替代SmartGoto
* Author: Jia Shenhan
* Created Date: 2019/5/10
**************************************************/
#ifndef _GOTO_POSITION_NEW_H_
#define _GOTO_POSITION_NEW_H_
#include <skill/PlayerTask.h>
#include <geometry.h>
#include "PathPlan/ObstacleNew.h"
/************************************************************************/
/*                     CBezierGotoPosition / 跑位                          */
/************************************************************************/

struct PlayerCapabilityT;

struct PID {
public:
	void init(double p, double i, double d) {
		this->p = p;
		this->i = i;
		this->d = d;
		a = p + i + d;
		b = p + 2 * d;
		c = d;
		e1 = e2 = e3 = 0;
		output = 0;
	}
	double step(double error) {
		e3 = e2;
		e2 = e1;
		e1 = error;
		output += (a * e1 - b * e2 + c * e3);
		return output;
	}
private:
	double p, i, d;
	double a, b, c;
	double e1, e2, e3;
	double output;
};

class CGotoPositionNew : public CPlayerTask {
public:
	CGotoPositionNew();
	virtual void plan(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const;
private:
	CGeoPoint _target;
	int playerFlag;
	PID anglePID;
	CGeoPoint finalPointBallPlacement(const CGeoPoint &startPoint, const CGeoPoint &target, const CGeoPoint &segPoint1, const CGeoPoint &segPoint2, const double avoidLength, ObstaclesNew& obst, bool& canDirect);
	void validateFinalTarget(CGeoPoint& finalTarget, const CVisionModule* pVision, bool shrinkTheirPenalty, double avoidLength, bool isGoalie);
	PlayerCapabilityT setCapability(const CVisionModule* pVision);
	void drawPath(bool drawPathPoints, bool drawPathLine, bool drawViaPoints, int vecNumber);
	bool validateStartPoint(CGeoPoint &startPoint, double avoidLength, bool isGoalie, ObstaclesNew *obs);
	vector < CGeoPoint > forBack(const CVisionModule* _pVision, const int vecNum, const CGeoPoint& startPos, const CGeoPoint& targetPos);
};

#endif
