#include <string>
#include "DefenceInfoNew.h"
#include "TaskMediator.h"
#include "GDebugEngine.h"

namespace {
	bool display_debug_info;
}

#define debug_arr(arr,p) if(display_debug_info){\
	QString str_##arr;\
	str_##arr.append(QString(#arr));\
	for (auto i : arr)\
	str_##arr.append(QString(" %1").arg(i));\
	GDebugEngine::Instance()->gui_debug_msg(p, str_##arr.toLatin1(), COLOR_YELLOW);\
}

CDefenceInfoNew::CDefenceInfoNew()
{
	display_debug_info = paramManager->display_debug_info;
	_potientialList.resize(Param::Field::MAX_PLAYER, 0);
	_ballChaserList.reserve(Param::Field::MAX_PLAYER);
	_ballChaserList.push_back(0);
	_ballChaserSteadyList.reserve(Param::Field::MAX_PLAYER);
	_ballChaserSteadyList.push_back(0);
}

CDefenceInfoNew::~CDefenceInfoNew()
{
}

void CDefenceInfoNew::updateDefenceInfoNew(const CVisionModule* pVision)
{
	updateBallChaserList(pVision);
	updateBallReceiverList(pVision);
}

void CDefenceInfoNew::updateBallChaserList(const CVisionModule* pVision)
{
	_lastPotientialList = _potientialList;
	_potientialList.clear();
	//加权计算追球潜力，越小越容易拿球
	for (int num = 0; num < Param::Field::MAX_PLAYER; num++)
		_potientialList.push_back(ballChaserAttributeSet::Instance()->evaluate(pVision, num));
	//持球者直接覆盖计算结果为最优
	//todo 等待BallStatus移植
	{
		double OurLooseBallCtrlDist = Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 3.5;
		double OurLooseBallCtrlAngle = Param::Math::PI * 15 / 180;
		double OurStrictBallCtrlDist = Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 1.5;
		double OurStrictBallCtrlAngle = Param::Math::PI * 10 / 180;
		for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
		{
			if (!pVision->TheirPlayer(i).Valid())
				continue;
			CVector player2Ball = pVision->Ball().Pos() - pVision->TheirPlayer(i).Pos();
			double distPlayer2Ball = player2Ball.mod();
			double dAnglePlayer2Ball = fabs(Utils::Normalize(player2Ball.dir() - pVision->TheirPlayer(i).Dir()));
			bool ballLooseCtrl = (distPlayer2Ball < OurLooseBallCtrlDist && dAnglePlayer2Ball < OurLooseBallCtrlAngle);
			bool ballStrictCtrl = (distPlayer2Ball < OurStrictBallCtrlDist && dAnglePlayer2Ball < OurStrictBallCtrlAngle);
			extern bool IS_SIMULATION;
			if (!IS_SIMULATION) {
				ballLooseCtrl = ballLooseCtrl || RobotSensor::Instance()->IsInfraredOn(i);
				ballStrictCtrl = ballStrictCtrl || RobotSensor::Instance()->IsInfraredOn(i);
			}
			if (ballLooseCtrl)
				_potientialList[i] = 0.1;
			if (ballStrictCtrl)
				_potientialList[i] = 0;
		}
	}
	//门将不应太容易成为最优
	_potientialList[pVision->TheirGoalie()] *= 1.5;
	_potientialList[pVision->TheirGoalie()] += 0.2;
	//与上一帧加权
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
		_potientialList[i] = _potientialList[i] * 0.75 + _lastPotientialList[i] * 0.25;
	//不可见球员排除，在阈值内的成为BallChaser并按潜力排序
	_ballChaserList.clear();
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
		_ballChaserList.push_back(i);
	_ballChaserList.erase(remove_if(_ballChaserList.begin(), _ballChaserList.end(),
		[&](int num) {return (!pVision->TheirPlayer(num).Valid()) || _potientialList[num] >= 0.75; }),
		_ballChaserList.end());
	sort(_ballChaserList.begin(), _ballChaserList.end(),
		[&](int num1, int num2) {return _potientialList[num1] < _potientialList[num2]; });
	//目前使用接口的地方不判断是否存在ballChaser，故需要保底
	if (_ballChaserList.empty())
		_ballChaserList.push_back(0);
	//特定情况下更新Steady
	//todo 原defenceinfo的设计考虑的是具体人员是否相同，以及考虑了接球车nomark，这个再想想
	if (_ballChaserList[0] != _ballChaserSteadyList[0] ||
		_ballChaserList.size() != _ballChaserSteadyList.size())
		_ballChaserSteadyList = _ballChaserList;
	//debug输出
	debug_arr(_ballChaserList, CGeoPoint(100, -350));
	debug_arr(_ballChaserSteadyList, CGeoPoint(-400, -350));
}

void CDefenceInfoNew::updateBallReceiverList(const CVisionModule* pVision)
{
}
