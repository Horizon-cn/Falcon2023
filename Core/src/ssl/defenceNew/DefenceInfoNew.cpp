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

CDefenceInfoNew::CDefenceInfoNew() :isInTheirPass(false)
{
	display_debug_info = paramManager->display_debug_info;
	_chaserPotientialList.resize(Param::Field::MAX_PLAYER, 0);
	_receiverPotientialList.resize(Param::Field::MAX_PLAYER, 0);
	_ballChaserList.reserve(Param::Field::MAX_PLAYER);
	_ballChaserList.push_back(0);
	_ballChaserSteadyList.reserve(Param::Field::MAX_PLAYER);
	_ballChaserSteadyList.push_back(0);
	_ballReceiverList.reserve(Param::Field::MAX_PLAYER);
	_ballReceiverSteadyList.reserve(Param::Field::MAX_PLAYER);
}

CDefenceInfoNew::~CDefenceInfoNew()
{
}

void CDefenceInfoNew::updateDefenceInfoNew(const CVisionModule* pVision)
{
	updateBallChaserList(pVision);
	updateBallReceiverList(pVision);
	checkPass(pVision);
}

void CDefenceInfoNew::updateBallChaserList(const CVisionModule* pVision)
{
	_lastChaserPotientialList = _chaserPotientialList;
	_chaserPotientialList.clear();
	//加权计算追球潜力，越小越容易拿球
	for (int num = 0; num < Param::Field::MAX_PLAYER; num++)
		_chaserPotientialList.push_back(ballChaserAttributeSet::Instance()->evaluate(pVision, num));
	//持球者直接覆盖计算结果为最优
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
		if (BallStatus::Instance()->getBallPossession(false, i))
			_chaserPotientialList[i] = 0;
	//门将不应太容易成为最优
	_chaserPotientialList[pVision->TheirGoalie()] *= 1.5;
	_chaserPotientialList[pVision->TheirGoalie()] += 0.2;
	//与上一帧加权
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
		_chaserPotientialList[i] = _chaserPotientialList[i] * 0.75 + _lastChaserPotientialList[i] * 0.25;
	//不可见球员排除，在阈值内的成为BallChaser并按潜力排序
	_ballChaserList.clear();
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
		_ballChaserList.push_back(i);
	_ballChaserList.erase(remove_if(_ballChaserList.begin(), _ballChaserList.end(),
		[&](int num) {return (!pVision->TheirPlayer(num).Valid()) || _chaserPotientialList[num] >= 0.75; }),
		_ballChaserList.end());
	sort(_ballChaserList.begin(), _ballChaserList.end(),
		[&](int num1, int num2) {return _chaserPotientialList[num1] < _chaserPotientialList[num2]; });
	//目前使用接口的地方不判断是否存在ballChaser，故需要保底
	if (_ballChaserList.empty())
		_ballChaserList.push_back(0);
	//特定情况下更新Steady
	//todo 原defenceinfo的设计考虑的是具体人员是否相同，以及考虑了接球车nomark，这个再想想
	if (_ballChaserList[0] != _ballChaserSteadyList[0] ||
		_ballChaserList.size() != _ballChaserSteadyList.size())
		_ballChaserSteadyList = _ballChaserList;
	//debug输出
	//debug_arr(_ballChaserList, CGeoPoint(100, -350));
	//debug_arr(_ballChaserSteadyList, CGeoPoint(-400, -350));
}

void CDefenceInfoNew::updateBallReceiverList(const CVisionModule* pVision)
{
	_lastReceiverPotientialList = _receiverPotientialList;
	_receiverPotientialList.clear();
	//加权计算接球潜力，越小越容易作为接球者被传球
	for (int num = 0; num < Param::Field::MAX_PLAYER; num++)
		_receiverPotientialList.push_back(ballReceiverAttributeSet::Instance()->evaluate(pVision, num));
	//持球者不能是Receiver
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
		if (BallStatus::Instance()->getBallPossession(false, i))
			_receiverPotientialList[i] = 255;
	//门将不应太容易成为最优
	_receiverPotientialList[pVision->TheirGoalie()] *= 1.5;
	//与上一帧加权
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
		_receiverPotientialList[i] = _receiverPotientialList[i] * 0.75 + _lastReceiverPotientialList[i] * 0.25;
	//不可见球员排除，在阈值内的成为BallReceiver并按潜力排序
	_ballReceiverList.clear();
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++)
		_ballReceiverList.push_back(i);
	_ballReceiverList.erase(remove_if(_ballReceiverList.begin(), _ballReceiverList.end(),
		[&](int num) {return (!pVision->TheirPlayer(num).Valid()) || _receiverPotientialList[num] >= 1000; }),
		_ballReceiverList.end());
	sort(_ballReceiverList.begin(), _ballReceiverList.end(),
		[&](int num1, int num2) {return _receiverPotientialList[num1] < _receiverPotientialList[num2]; });
	//特定情况下更新Steady
	if (_ballReceiverList[0] != _ballReceiverSteadyList[0] ||
		_ballReceiverList.size() != _ballReceiverSteadyList.size())
		_ballReceiverSteadyList = _ballReceiverList;
	//debug输出
	debug_arr(_ballReceiverList, CGeoPoint(100, -250));
	debug_arr(_ballReceiverSteadyList, CGeoPoint(-400, -250));
}
//传球时的特殊处理
void CDefenceInfoNew::checkPass(const CVisionModule* pVision)
{
	if (isInTheirPass)
	{
		//判断是否仍在传球状态
		const BallVisionT& ball = pVision->Ball();
		const PlayerVisionT& receiver = pVision->TheirPlayer(_receiver);
		double ball2ReceiverDir = (receiver.Pos() - ball.Pos()).dir();
		double angleDiff = fabs(Utils::Normalize(ball2ReceiverDir - ball.Vel().dir()));
		double ball2ReceiverDist = ball.Pos().dist(receiver.Pos());
		if (angleDiff > Param::Math::PI / 2.0 || ball2ReceiverDist > 450 || ball2ReceiverDist < 100)
			isInTheirPass = false;
	}
	else
	{
		if (BallStatus::Instance()->IsBallKickedOut())
		{
			for (_kicker = 0; _kicker < 2 * Param::Field::MAX_PLAYER; _kicker++)
				if (BallStatus::Instance()->IsBallKickedOut(_kicker))
					break;
			if (_kicker >= Param::Field::MAX_PLAYER)//TheirKick
			{
				_kicker -= Param::Field::MAX_PLAYER;
				matchReceiver(pVision);
				if (_receiver != -1)
					isInTheirPass = true;
			}
		}
	}
	//接球者作为新的BallChaser，同时从BallReceiver移除
	if (isInTheirPass)
	{
		auto temp = find(_ballChaserList.begin(), _ballChaserList.end(), _receiver);
		if (temp != _ballChaserList.end())
			rotate(_ballChaserList.begin(), temp, temp + 1);
		else
			_ballChaserList.insert(_ballChaserList.begin(), _receiver);
		auto tmp = find(_ballReceiverList.begin(), _ballReceiverList.end(), _receiver);
		if (tmp != _ballReceiverList.end())
			_ballReceiverList.erase(tmp);
	}
}

int CDefenceInfoNew::matchReceiver(const CVisionModule* pVision)
{
	const BallVisionT& ball = pVision->Ball();
	for (int maybeReceiverNum : _ballReceiverList)
	{
		const PlayerVisionT& maybeReceiver = pVision->TheirPlayer(maybeReceiverNum);
		double ball2ReceiverDir = (maybeReceiver.Pos() - ball.Pos()).dir();
		double angleDiff = fabs(Utils::Normalize(ball2ReceiverDir - ball.Vel().dir()));
		double ball2ReceiverDist = ball.Pos().dist(maybeReceiver.Pos());
		if (angleDiff > Param::Math::PI / 2.0 || ball2ReceiverDist > 450 || ball2ReceiverDist < 100)
			continue;
		return maybeReceiverNum;
	}
	return -1;
}
