#ifndef _GET_BALL_V5_H__
#define _GET_BALL_V5_H__
#include <skill/PlayerTask.h>

/**********************************************************
* Skill: GetBallV5
* Description:拿球第5版，适用于小嘴巴底盘
***********************************************************/

class CGetBallV5 :public CStatedTask {
public:
	CGetBallV5();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: GetBallV5\n"; }
	int PredictForRobot(CGeoPoint point, const CVisionModule* pVision);
	CGeoPoint Ball_Predict_Pos(const CVisionModule* pVision);
	CGeoPoint PredictForBall(int frame, const CVisionModule* pVision);
	CGeoPoint GeneratePoint(const CVisionModule* pVision, double finalDir, const bool debug);
	bool JudgeLargeBack(const CVisionModule* pVision, CGeoPoint target);
	bool LARGECanToROTATE(const CVisionModule* pVision, const double finalDir);
	bool ROTATECanToDIRECT(const CVisionModule* pVision, double finalDir);
	bool WeMustReturnLARGE(const CVisionModule* pVision, const double finalDir);
	bool MustUseLargeToAdjust(const CVisionModule* pVision, const int _executor, const double finalDir);
	int getTheirMostClosetoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos);
	bool OppIsNearThanMe(const CVisionModule* pVision, const int vecNumber);
	bool Me2OppTooclose(const CVisionModule* pVision, const int vecNumber);
	CGeoPoint GenerateLargeAnglePoint(const CVisionModule* pVision, double finalDir, const bool debug);
	bool HaveBeenBlockPoint(const CVisionModule* pVision, const int vecNumber);
	bool checkOppHasBall(const CVisionModule* pVision);
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
	double OPP_HAS_BALL_DIST = 12;
};

#endif //_GET_BALL_V4_H__