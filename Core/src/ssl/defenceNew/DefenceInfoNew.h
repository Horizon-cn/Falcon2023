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
	void addMarker() { _markerAmount++; };
	//防守信息接口
	bool isBestBallChaserChanged() { return _ballChaserChanged; }
	int getBestBallChaser() { return _ballChaserList[0]; }
	int getBallChaserNum() { return _ballChaserList.size(); }
	const TenemyList& getBallChaserList() { return _ballChaserList; }
	int getSteadyBallChaserNum() { return _ballChaserSteadyList.size(); }
	const TenemyList& getSteadyBallChaserList() { return _ballChaserSteadyList; }

	bool isBestBallReceiverChanged() { return _ballReceiverChanged; }
	int getBestBallReceiver() { if (_ballReceiverSteadyList.empty()) return 0; else return _ballReceiverSteadyList[0]; }
	int getBallReceiverNum() { return _ballReceiverList.size(); }
	const TenemyList& getBallReceiverList() { return _ballReceiverList; }
	int getSteadyBallReceiverNum() { return _ballReceiverSteadyList.size(); }
	int getSteadyBallReceiverByPri(int i) { i = max(0, min(i, (int)_ballReceiverSteadyList.size() - 1)); return _ballReceiverSteadyList[i]; }
private:
	void updateBallChaserList(const CVisionModule* pVision);
	void updateBallReceiverList(const CVisionModule* pVision);
	void checkProtect(const CVisionModule* pVision);
	void checkPass(const CVisionModule* pVision);
	void matchProtecter(const CVisionModule* pVision);
	void matchReceiver(const CVisionModule* pVision);
	void updateSteady();
private:
	TenemyList _ballChaserList, _ballChaserSteadyList, _ballReceiverList, _ballReceiverSteadyList;
	TpotientialList _chaserPotientialList, _lastChaserPotientialList, _receiverPotientialList, _lastReceiverPotientialList;
	bool isNeedProtect, isInTheirPass, _ballChaserChanged, _ballReceiverChanged;
	int _kicker, _receiver, _protecter, _markerAmount, _lastMarkerAmount;
};

typedef Falcon::NormalSingleton<CDefenceInfoNew> DefenceInfoNew;

#endif
