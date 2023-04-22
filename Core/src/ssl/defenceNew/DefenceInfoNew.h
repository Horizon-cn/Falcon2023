#ifndef __DEFENCE_INFO_NEW_H__
#define __DEFENCE_INFO_NEW_H__

#include <iostream>
#include "defenceNew\ballChaserAttributeSet.h"
#include "Vision/VisionModule.h"
#include "param.h"
#include "geometry.h"

//class CAttributeSet;

using namespace std;

class CDefenceInfoNew
{
	typedef vector<int> enemyList;
	typedef pair<int, double> TplayerPotientialPair;
	typedef vector<TplayerPotientialPair> TplayerPotientialList;
public:
	CDefenceInfoNew();
	~CDefenceInfoNew();
	//每帧更新
	void updateDefenceInfoNew(const CVisionModule* pVision);
	//防守信息接口
	enemyList GetBallChaserList() { return _ballChaserList; };
	enemyList GetSteadyBallChaserList() { return _ballChaserSteadyList; };
	enemyList GetBallReceiverList() { return _ballReceiverList; };
	enemyList GetSteadyBallReceiverList() { return _ballReceiverSteadyList; };
private:
	void updateBallChaserList(const CVisionModule* pVision);
	void updateBallReceiverList(const CVisionModule* pVision);
private:
	enemyList _ballChaserList, _ballChaserSteadyList, _ballReceiverList, _ballReceiverSteadyList;
	TplayerPotientialList _potientialList, _lastPotientialList;
	//CAttributeSetNew _chaserAttrSet,_receiverAttrSet;
};

typedef Falcon::NormalSingleton<CDefenceInfoNew> DefenceInfoNew;

#endif
