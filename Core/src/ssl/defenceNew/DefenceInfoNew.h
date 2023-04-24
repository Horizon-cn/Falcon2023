#ifndef __DEFENCE_INFO_NEW_H__
#define __DEFENCE_INFO_NEW_H__

#include "defenceNew/ballChaserAttributeSet.h"
#include "Vision/VisionModule.h"
#include "param.h"
#include "geometry.h"

using namespace std;

class CDefenceInfoNew
{
	typedef vector<int> TenemyList;
	typedef vector<double> TpotientialList;
public:
	CDefenceInfoNew();
	~CDefenceInfoNew();
	//每帧更新
	void updateDefenceInfoNew(const CVisionModule* pVision);
	//防守信息接口
	int getBestBallChaser() { return _ballChaserList[0]; }
	const TenemyList& getBallChaserList() { return _ballChaserList; }
	const TenemyList& getSteadyBallChaserList() { return _ballChaserSteadyList; }
	int getBestBallReceiver() { return _ballReceiverList[0]; }
	const TenemyList& getBallReceiverList() { return _ballReceiverList; }
	const TenemyList& getSteadyBallReceiverList() { return _ballReceiverSteadyList; }
private:
	void updateBallChaserList(const CVisionModule* pVision);
	void updateBallReceiverList(const CVisionModule* pVision);
private:
	TenemyList _ballChaserList, _ballChaserSteadyList, _ballReceiverList, _ballReceiverSteadyList;
	TpotientialList _potientialList, _lastPotientialList;
};

typedef Falcon::NormalSingleton<CDefenceInfoNew> DefenceInfoNew;

#endif
