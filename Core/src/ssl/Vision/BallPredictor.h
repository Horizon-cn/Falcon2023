/**
* @file BallPredictor.h
* @date $Date: 2020/07/27$
* @version $Revision: 2.0 $
* @author loganshi@sjtu.edu.cn
*/

#ifndef _BALL_PREDICTOR_H_
#define _BALL_PREDICTOR_H_
#include "WorldModel/WorldDefine.h"
#include "WorldModel/server.h"
#include <vector>

namespace {
	const int MAX_LOGS = 16;
}

struct BallVisionData : public BallVisionT {
	int cycle;
};

class CBallVisionLogger {
public:
	bool visionValid(int cycle) const { return _vision[cycle % MAX_LOGS].cycle == cycle; }
	const BallVisionData& getVision(int cycle) const { return _vision[cycle % MAX_LOGS]; }
	BallVisionData& getVision(int cycle) { return _vision[cycle % MAX_LOGS]; }
	void setVision(int cycle, const BallVisionData& vision)
	{
		_vision[cycle % MAX_LOGS] = vision;
		_vision[cycle % MAX_LOGS].cycle = cycle;
	}

private:
	BallVisionData _vision[MAX_LOGS];
};
class CBallPredictor{
public:
	CBallPredictor();
	~CBallPredictor();
	void updateVision(const GameInfoT& vInfo, bool invert);
	void setPos(const CGeoPoint & pos){
		_visionLogger.getVision(_cycle).SetPos(pos);
	}
	void setPos(int cycle,const CGeoPoint & pos) {
		_visionLogger.getVision(cycle).SetPos(pos);
	}
	void setVel(const CVector & vel){
		_visionLogger.getVision(_cycle).SetVel(vel);
	}
	void setVel(int cycle, const CVector & vel) {
		_visionLogger.getVision(cycle).SetVel(vel);
	}
	const BallVisionT& getResult(int cycle) const { return _visionLogger.getVision(cycle); }
	const BallVisionT& getResult() const { return _visionLogger.getVision(_cycle); }

private:
	CBallVisionLogger _visionLogger;
	int _cycle;
};
#endif // _BALL_PREDICTOR_H_

