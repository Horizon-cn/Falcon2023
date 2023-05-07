#ifndef _GET_BALL_V4_H__
#define _GET_BALL_V4_H__
#include <skill/PlayerTask.h>

/**********************************************************
* Skill: GetBallV4
* Description:拿球第4版，适用于小嘴巴底盘
***********************************************************/

class CGetBallV4 :public CStatedTask {
public:
	CGetBallV4();
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
	bool LARGECanToROTATE(const CVisionModule* pVision, const double finalDir);
	bool ROTATECanToDIRECT(const CVisionModule* pVision, const double finalDir);
	bool WeMustReturnLARGE(const CVisionModule* pVision, const double finalDir);
private:
	enum {
		BEGIN = 0,
		LARGE,
		ROTATAE,
		DIRECT,
		HAVE,
	};
	int _state;
	int _lastCycle;
};

#endif //_GET_BALL_V4_H__