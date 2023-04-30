#ifndef __DEFENCE_INFO_NEW_H__
#define __DEFENCE_INFO_NEW_H__

#include "defenceNew/ballChaserAttributeSet.h"
#include "defenceNew//ballReceiverAttributeSet.h"
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
	int getBallChaserNum() { return _ballChaserList.size(); }
	const TenemyList& getBallChaserList() { return _ballChaserList; }
	int getSteadyBallChaserNum() { return _ballChaserSteadyList.size(); }
	const TenemyList& getSteadyBallChaserList() { return _ballChaserSteadyList; }
	int getBestBallReceiver() { if (_ballReceiverList.empty()) return 0; else return _ballReceiverList[0]; }
	int getBallReceiverNum() { return _ballReceiverList.size(); }
	const TenemyList& getBallReceiverList() { return _ballReceiverList; }
	int getSteadyBallReceiverNum() { return _ballReceiverSteadyList.size(); }
	const TenemyList& getSteadyBallReceiverList() { return _ballReceiverSteadyList; }
private:
	void updateBallChaserList(const CVisionModule* pVision);
	void updateBallReceiverList(const CVisionModule* pVision);
private:
	TenemyList _ballChaserList, _ballChaserSteadyList, _ballReceiverList, _ballReceiverSteadyList;
	TpotientialList _chaserPotientialList, _lastChaserPotientialList, _receiverPotientialList, _lastReceiverPotientialList;
};

typedef Falcon::NormalSingleton<CDefenceInfoNew> DefenceInfoNew;

#endif
