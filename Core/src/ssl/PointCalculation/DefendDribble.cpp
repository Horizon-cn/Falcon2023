/************************************************************************/
/* Copyright (c) Shanghai Jiao Tong University							*/
/* Team：		SRC-SJTU								                */
/************************************************************************/
/* File:	  DefendDribble.cpp											*/
/* Func:	  始终站在吸球车和接球车间 不让其传球                       */
/* Author:	  和家平 2020-10-24	 V2 2021-05-03 		                    */
/* Refer:	  ###														*/
/* E-mail:	  hejiaping2016@sjtu.edu.cn									*/
/* Version:	  0.0.2														*/
/************************************************************************/

#include "DefendDribble.h"
#include "param.h"
#include "utils.h"
#include "WorldModel/WorldModel.h"
#include "GDebugEngine.h"
#include <math.h>
#include "defence/DefenceInfo.h"
#include "BestPlayer.h"
#include <ssl/ParamManagerNew.h>

namespace {
	bool debug = false;

	const double GoalBuffer = 2;
	CGeoPoint GOAL_LEFT_POS;
	CGeoPoint GOAL_RIGHT_POS;
	CGeoPoint GOAL_CENTRE_POS;

	const double CHANGE_MODE_BUFFER = Param::Vehicle::V2::PLAYER_SIZE * 2.5; //跟车模式和站禁区线模式转换阈值
	const double ABSOLUTELY_IN = 3; //敌人已经彻底进入禁区，不再考虑

	const double OPP_PRE_TIME = 1.5;//对敌人的带速度位置预测时间
	const double OPP_REAL_PRE_TIME = 1;//对敌人真实位置的预测时间
};

CDefendDribble::CDefendDribble()
{
	//本算法的初始化
    _DeDribblePos = CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + ParamManager::Instance()->PENALTY_AREA_DEPTH + 20, 0);
    _lastDeDribblePos = CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + ParamManager::Instance()->PENALTY_AREA_DEPTH + 20, 0);
	GOAL_LEFT_POS = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2 - GoalBuffer);
	GOAL_RIGHT_POS = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2 + GoalBuffer);
	GOAL_CENTRE_POS = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
	_lastCycle = 0;
	//_forMarkingPos = CGeoPoint(0,0);
	//_headAttackEnemy = 0;
}

CDefendDribble::~CDefendDribble()
{}

CGeoPoint CDefendDribble::getDeDribblePos(const CVisionModule* pVision)
{
	if (pVision->Cycle() == _lastCycle) {
		return _lastDeDribblePos;
	}
	else {
		_lastCycle = pVision->Cycle();
	}
	//生成防范吸球点
	generateDeDribblePos(pVision);
	return _DeDribblePos;
}

CGeoPoint CDefendDribble::generateDeDribblePos(const CVisionModule* pVision)
{
    _DeDribblePos = CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + ParamManager::Instance()->PENALTY_AREA_DEPTH + 20, 0);
	//以下部分不进行反向计算
	const BallVisionT& ball = pVision->Ball();
	const CGeoPoint ballPos = ball.Pos();
	const CBestPlayer::PlayerList& oppList = BestPlayer::Instance()->theirFastestPlayerToBallList();
	int enemyNum = oppList[0].num;     //新版判断bestplayer方法，与advance一致,一般是带球车
	int SecondEnemyNum = 0;
	_TheirPlayerXList.clear();         //敌方x坐标排序,找出距离我方最近的车
	int n = 0;
	while (n <= Param::Field::MAX_PLAYER) {
		if (!pVision->TheirPlayer(n).Valid()) { _TheirPlayerXList.push_back(TheirPlayerXPair(n, Param::Field::PITCH_LENGTH / 2)); n++; continue; }
		_TheirPlayerXList.push_back(TheirPlayerXPair(n, pVision->TheirPlayer(n).Pos().x()));
		n++;
	}
	std::sort(_TheirPlayerXList.begin(), _TheirPlayerXList.end());
	//int enemyNum = BestPlayer::Instance()->getTheirBestPlayer(); //找到对方带球车，目前判断为bestplayer,具体还需实际测试
	if (_TheirPlayerXList[0].num == oppList[1].num) {
		SecondEnemyNum = oppList[1].num;    //尝试着对接球车进行判断，即威胁度排第二的车，如果效果不好，选择离我方球门最近的车
	}
	else if (_TheirPlayerXList[0].num == oppList[0].num) {
		SecondEnemyNum = _TheirPlayerXList[1].num;
	}
	else { SecondEnemyNum = _TheirPlayerXList[0].num; }
	const PlayerVisionT& enemyLeader = pVision->TheirPlayer(enemyNum);
	const PlayerVisionT& enemyReceiver = pVision->TheirPlayer(SecondEnemyNum);
	CGeoPoint enemyPos = enemyLeader.Pos();
	CGeoPoint enemyReceiverPos = enemyReceiver.Pos();
	GDebugEngine::Instance()->gui_debug_msg(enemyReceiverPos, "Receiver Opp!!!!!!!!!!", COLOR_WHITE);
	const CVector Receiver2Opp = enemyPos - enemyReceiverPos;
	const double Receiver2Oppdist = Receiver2Opp.mod();
	CGeoPoint targetPos = CGeoPoint(-315, 0);
	if (enemyLeader.Valid() && enemyReceiver.Valid() && enemyReceiverPos.x() > 0)                            //接球车在对方半场，站在半场线，同y坐标
	{
		targetPos = CGeoPoint(0, enemyReceiverPos.y());
		_DeDribblePos = targetPos;
	}
	else if (enemyLeader.Valid() && enemyReceiver.Valid())         //离接球车一定身位，封堵传球连线
	{
		double angle_enemy2goal = CVector(GOAL_CENTRE_POS - enemyPos).dir();
		targetPos = enemyReceiverPos + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_SIZE * 4 + enemyReceiver.Vel().mod() * OPP_REAL_PRE_TIME, Receiver2Opp.dir());
		int moveStep = 0;
		if(Utils::InOurPenaltyArea(enemyReceiverPos, 30) || enemyReceiverPos.x() > -30 ){ targetPos = enemyReceiverPos + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_SIZE * 2 + enemyReceiver.Vel().mod() * OPP_REAL_PRE_TIME, Receiver2Opp.dir()); }
		if (Receiver2Oppdist < Param::Vehicle::V2::PLAYER_SIZE * 2)
		{
			targetPos = enemyReceiverPos + Utils::Polar2Vector(Receiver2Oppdist / 2.0, Receiver2Opp.dir());
		}
		while (Utils::InOurPenaltyArea(targetPos, Param::Vehicle::V2::PLAYER_SIZE * 0.5))    //防止生成点在禁区内
		{
			moveStep += 1;
			targetPos = enemyReceiverPos + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_SIZE * (2 + moveStep), Receiver2Opp.dir());
		}
		_DeDribblePos = targetPos;
	}
	//进入离禁区较近区域，站球门线，策略同defendHead
	else if (enemyLeader.Valid() && enemyReceiver.Valid() && Utils::InOurPenaltyArea(enemyPos, CHANGE_MODE_BUFFER) && Utils::InOurPenaltyArea(enemyReceiverPos, CHANGE_MODE_BUFFER) && !Utils::InOurPenaltyArea(enemyLeader.Pos(), ABSOLUTELY_IN))
	{
		targetPos = enemyReceiverPos + Utils::Polar2Vector(enemyReceiver.Vel().mod()*OPP_REAL_PRE_TIME, enemyReceiver.Vel().dir());
		CGeoPoint RTargetPos = DefendUtils::reversePoint(targetPos);
		CGeoPoint RblockPos = DefendUtils::calcDefenderPointV2(RTargetPos, CVector(DefendUtils::reversePoint(GOAL_CENTRE_POS) - RTargetPos).dir(), POS_SIDE_MIDDLE, 0, 1.0);
		_DeDribblePos = DefendUtils::reversePoint(RblockPos);
	}

	_lastDeDribblePos = _DeDribblePos;
	return _DeDribblePos;

}
