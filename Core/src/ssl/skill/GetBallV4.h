#ifndef _GET_BALL_V4_H__
#define _GET_BALL_V4_H__
#include <skill/PlayerTask.h>

/**********************************************************
* Skill: GetBallV4
* Description:�����4�棬������С��͵���
***********************************************************/

class CGetBallV4 :public CStatedTask {
public:
	CGetBallV4();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: GetBallV4\n"; }

	CGeoPoint GenerateLargeAnglePoint(const CVisionModule* pVision, double finalDir, const bool debug);
	bool JudgeLargeBack(const CVisionModule* pVision, CGeoPoint target);
	bool LARGECanToROTATE(const CVisionModule* pVision, const double finalDir);
	bool ROTATECanToDIRECT(const CVisionModule* pVision, double finalDir);
	bool WeMustReturnLARGE(const CVisionModule* pVision, const double finalDir);
	bool MustUseLargeToAdjust(const CVisionModule* pVision, const int _executor, const double finalDir);
	int getTheirMostClosetoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos);
	bool OppIsNearThanMe(const CVisionModule* pVision, const int vecNumber);
	bool Me2OppTooclose(const CVisionModule* pVision, const int vecNumber);
private:
	enum {
		BEGIN = 0,
		LARGE,
		ROTATAE,
		DIRECT,
		HAVE,
		LEAVEBACK,
	};
	int _state;
	int _lastCycle;
	int _RotateCnt;
	int _LargeCnt;
	int opponentID;
	double last_final_dir;
	double last_dir_deviation = 100;
	double GetBall_Precision_alpha = 3.0;
};

#endif //_GET_BALL_V4_H__