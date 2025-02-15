#ifndef _GET_BALL_V3_H__
#define _GET_BALL_V3_H__
#include <skill/PlayerTask.h>

/**********************************************************
* Skill: GetBallV3
* Description:��������棬������С��͵���
***********************************************************/

class CGetBallV3 :public CStatedTask {
public:
	CGetBallV3();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: GetBallV3\n"; }
	int PredictForRobot(CGeoPoint point, const CVisionModule* pVision);
	CGeoPoint Ball_Predict_Pos(const CVisionModule* pVision);
	CGeoPoint PredictForBall(int frame, const CVisionModule* pVision);
	CGeoPoint GenerateLargeAnglePoint(const CVisionModule* pVision, const double finalDir, const bool debug);
	bool JudgeLargeBack(const CVisionModule* pVision, CGeoPoint target);
private:
	int _lastCycle;
};

#endif //_GET_BALL_V3_H__