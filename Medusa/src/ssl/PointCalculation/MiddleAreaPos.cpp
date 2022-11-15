/************************************************************************/
/* Copyright (c) ShanghaiJiaoTongUniversity							    */
/* Team：		SRC											            */
/************************************************************************/
/* File:	  MiddleAreaPos.cpp											*/
/* Func:	  球在我半场中侧，对手挑球传中时，用于防守对方接应队员头球的点*/
/* Author:	  和家平 2020-07-18											*/
/* Refer:	  ###														*/
/* E-mail:	  hejiaping2016@sjtu.edu.cn									*/
/************************************************************************/

#include "CornerAreaPos.h"
#include "param.h"
#include "utils.h"
#include "WorldModel/WorldModel.h"
#include "GDebugEngine.h"
#include <math.h>
#include "defence/DefenceInfo.h"
#include <ssl/ParamManagerNew.h>

namespace{
	bool debug = false;	

	const double GoalBuffer = 2;
	CGeoPoint GOAL_LEFT_POS;
	CGeoPoint GOAL_RIGHT_POS;
	CGeoPoint GOAL_CENTRE_POS;

	const double CHANGE_BUFFER = 50;
	const double ABSOLUTELY_IN = 5; //敌人已经彻底进入禁区，不再考虑

	const double extremeMiddleDefDist = 90;//一边发角球时，如果头球车位置y值超过该边，则不予盯防
	const double OPP_PRE_TIME = 1.5;//对敌人的带速度位置预测时间
	const double OPP_REAL_PRE_TIME = 0.2;//对敌人真实位置的预测时间
	const double DEAL_HIT_DIST = 35;//待联防的两车较近的时候再进入状态
	const double EXTREME_ANGLE = Param::Math::PI * 37 / 180;  //给defendMiddle留空间
};

CMiddleAreaPos::CMiddleAreaPos()
{
	//本算法的初始化
	_MAPos = CGeoPoint(0,0);
	_lastMAPos = CGeoPoint(0,0);
	GOAL_LEFT_POS = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2 - GoalBuffer);
	GOAL_RIGHT_POS = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2 + GoalBuffer);
	GOAL_CENTRE_POS = CGeoPoint(-Param::Field::PITCH_LENGTH / 2,0);
	_MlastCycle = 0;
	//_forMarkingPos = CGeoPoint(0,0);
	//_headAttackEnemy = 0;
}

CMiddleAreaPos::~CMiddleAreaPos()
{}

CGeoPoint CMiddleAreaPos::getMiddleAreaPos(const CVisionModule* pVision)
{
	if (pVision->Cycle() == _MlastCycle) {
		return _lastMAPos;
	} else{
		_MlastCycle = pVision->Cycle();
	}
	//生成中卫点
	setPos(generateMiddlePos(pVision));	
	return _MAPos;
}

//bool CCornerAreaPos::isUsed(const CVisionModule* pVision)
//{
//	if (pVision->Cycle() - _MlastCycle > 3)
//	{
//		_headAttackEnemy = 0;
//		_dealWithHit = false;
//		return false;
//	} else return true;
//}

CGeoPoint CMiddleAreaPos::generateMiddlePos(const CVisionModule* pVision)
{
	_MAPos = CGeoPoint(-335,0); //已修改为Brazil zhyaic
	//以下部分没有反向计算！！
	const BallVisionT& ball = pVision->Ball();
	const CGeoPoint ballPos = ball.Pos();
	static posSide ballSide = POS_SIDE_RIGHT;
	const string refMsg = WorldModel::Instance()->CurrentRefereeMsg();
	/*if ("theirIndirectKick" == refMsg || "theirDirectKick" == refMsg || "theirKickOff" == refMsg || "gameStop" == refMsg)
	{
		if (ballPos.y() > 0)
		{
			ballSide = POS_SIDE_RIGHT;
		} else ballSide = POS_SIDE_LEFT;
	}*/	
	if (ballPos.y() > 0)
	{
		ballSide = POS_SIDE_RIGHT;
	}
	else ballSide = POS_SIDE_LEFT;
	int attackNum = DefenceInfo::Instance()->getAttackNum();
	//求取破防成功的最近队员
	int enemyBreakMe = -1;
	double minDist = 1000;
	for (int i = 0;i < attackNum;++i)
	{
		int enemyNum = DefenceInfo::Instance()->getAttackOppNumByPri(i);
		if (!Utils::PlayerNumValid(enemyNum)) {
			continue;
		}
		const PlayerVisionT& opp = pVision->TheirPlayer(enemyNum);
		if (opp.Valid() && !Utils::InOurPenaltyArea(opp.Pos(),ABSOLUTELY_IN))
		{
			CGeoPoint oppPos = opp.Pos();
			CGeoPoint oppPrePos = oppPos + Utils::Polar2Vector(opp.Vel().mod()*OPP_PRE_TIME,opp.Vel().dir());
			if (POS_SIDE_LEFT == ballSide)
			{
				if (oppPrePos.y() > extremeMiddleDefDist)
				{
					continue;
				}
			} else if (POS_SIDE_RIGHT == ballSide)
			{
				if (oppPrePos.y() < -1 * extremeMiddleDefDist)
				{
					continue;
				}
			}
			//判断是否盯防良好
			bool markWell = true;
			double markerDistFactor = DefenceInfo::Instance()->getOppPlayerByNum(enemyNum)->getAttributeValue("AMarkerDistFactor");
			double markerDirFactor = DefenceInfo::Instance()->getOppPlayerByNum(enemyNum)->getAttributeValue("AMarkerDirFactor");
			if (markerDirFactor > Param::Math::PI * 100 / 180 ||
				markerDistFactor > 150						||
				sin(markerDirFactor) * markerDistFactor > 30)
			{
				markWell = false;
			}
			if (false == markWell)
			{
				double nowDist = oppPos.dist(GOAL_CENTRE_POS);
				if (nowDist < minDist)
				{
					minDist = nowDist;
					enemyBreakMe = enemyNum;
				}
			}
		}
	}
	//如果没有破防成功的队员，则只找到离得最近的队员
	if (enemyBreakMe<0)
	{
		minDist = 1000;
		for (int i = 0;i < attackNum;++i)
		{
			int enemyNum = DefenceInfo::Instance()->getAttackOppNumByPri(i);
			if (!Utils::PlayerNumValid(enemyNum)) {
				continue;
			}
			const PlayerVisionT& opp = pVision->TheirPlayer(enemyNum);
			if (opp.Valid() && !Utils::InOurPenaltyArea(opp.Pos(),ABSOLUTELY_IN))
			{				
				CGeoPoint oppPos = opp.Pos();
				CGeoPoint oppPrePos = oppPos + Utils::Polar2Vector(opp.Vel().mod()*OPP_PRE_TIME,opp.Vel().dir());
				if (POS_SIDE_LEFT == ballSide)
				{
					if (oppPrePos.y() > extremeMiddleDefDist)
					{
						continue;
					}
				} else if (POS_SIDE_RIGHT == ballSide)
				{
					if (oppPrePos.y() <  -1 * extremeMiddleDefDist)
					{
						continue;
					}
				}
				double nowDist = oppPos.dist(GOAL_CENTRE_POS);
				if (nowDist < minDist)
				{
					minDist = nowDist;
					enemyBreakMe = enemyNum;
				}
			}
		}
	}
	//取点
	CGeoPoint targetPos = CGeoPoint(0,0);
	if (POS_SIDE_LEFT == ballSide)
	{
		targetPos = CGeoPoint(-(Param::Field::PITCH_LENGTH/2-queryParamByName("data\\ssl\\params\\params.xml", "PENALTY_AREA_DEPTH")),Param::Field::PENALTY_AREA_WIDTH/2); // 已修改为Brazil zhyaic
	} else if (POS_SIDE_RIGHT == ballSide)
	{
		targetPos = CGeoPoint(-(Param::Field::PITCH_LENGTH/2-queryParamByName("data\\ssl\\params\\params.xml", "PENALTY_AREA_DEPTH")),-Param::Field::PENALTY_AREA_WIDTH/2); // 已修改为Brazil zhyaic
	}

	if (enemyBreakMe>=0)//敌人存在
	{
		const PlayerVisionT& headOpp = pVision->TheirPlayer(enemyBreakMe);
		targetPos = headOpp.Pos() + Utils::Polar2Vector(headOpp.Vel().mod()*OPP_REAL_PRE_TIME,headOpp.Vel().dir());
		double angle_goal2target = CVector(targetPos - GOAL_CENTRE_POS).dir();
		if (POS_SIDE_LEFT == ballSide)
		{
			if (angle_goal2target >= EXTREME_ANGLE)
			{
				targetPos = GOAL_CENTRE_POS + Utils::Polar2Vector(150*Param::Field::RATIO,0.8* EXTREME_ANGLE);  //在超出中场防守范围时，中卫不大幅度向上，重点依然在中场
			}else if (angle_goal2target <= -1*EXTREME_ANGLE)
			{
				targetPos = GOAL_CENTRE_POS + Utils::Polar2Vector(150*Param::Field::RATIO,-0.8*EXTREME_ANGLE);
			}
		}else if (POS_SIDE_RIGHT == ballSide)
		{
			if (angle_goal2target <= -1*EXTREME_ANGLE)
			{
				targetPos = GOAL_CENTRE_POS + Utils::Polar2Vector(150*Param::Field::RATIO,-0.8*EXTREME_ANGLE);
			}else if (angle_goal2target >= EXTREME_ANGLE)
			{
				targetPos = GOAL_CENTRE_POS + Utils::Polar2Vector(150*Param::Field::RATIO,0.8*EXTREME_ANGLE);
			}
		}		
	}
	//开始反向计算，注意！！
	CGeoPoint RTargetPos = DefendUtils::reversePoint(targetPos);
	CGeoPoint RblockPos = DefendUtils::calcDefenderPointV2(RTargetPos,CVector(DefendUtils::reversePoint(GOAL_CENTRE_POS) - RTargetPos).dir(),POS_SIDE_MIDDLE,0,1.0);
	_MAPos = DefendUtils::reversePoint(RblockPos);
	//解决本点与盯人相冲突的问题
	//if (WorldModel::Instance()->getEnemySituation().queryMarked(enemyBreakMe))//有人盯防
	//{
	//	if (Utils::InOurPenaltyArea(targetPos,CHANGE_BUFFER))//在我禁区外一圈
	//	{
	//		int defenderNum = WorldModel::Instance()->getOurMarkDenfender(enemyBreakMe);
	//		if (pVision->OurPlayer(defenderNum).Valid() && _MAPos.dist(pVision->OurPlayer(defenderNum).Pos()) < DEAL_HIT_DIST)//而且盯人点和防头球点距离很近
	//		{
	//			_headAttackEnemy = enemyBreakMe;
	//			_dealWithHit = true;
	//			const PlayerVisionT& me = pVision->OurPlayer(defenderNum);
	//			if (/*me.Y() < _MAPos.y()*/CVector(me.Pos() - GOAL_CENTRE_POS).dir() - CVector(_MAPos - GOAL_CENTRE_POS).dir() < 0)//盯人者 在 防头球者左边 ，防头球者走到右边
	//			{
	//				RblockPos = DefendUtils::calcDefenderPoint(RTargetPos,CVector(DefendUtils::reversePoint(GOAL_CENTRE_POS) - RTargetPos).dir(),POS_SIDE_LEFT);//注意这里的POS_SIDE_LEFT没有错
	//				_forMarkingPos = DefendUtils::reversePoint(DefendUtils::calcDefenderPoint(RTargetPos,CVector(DefendUtils::reversePoint(GOAL_CENTRE_POS) - RTargetPos).dir() + 0.05,POS_SIDE_RIGHT));
	//				_MAPos = DefendUtils::reversePoint(RblockPos);
	//			} else 
	//			{
	//				RblockPos = DefendUtils::calcDefenderPoint(RTargetPos,CVector(DefendUtils::reversePoint(GOAL_CENTRE_POS) - RTargetPos).dir(),POS_SIDE_RIGHT);
	//				_forMarkingPos = DefendUtils::reversePoint(DefendUtils::calcDefenderPoint(RTargetPos,CVector(DefendUtils::reversePoint(GOAL_CENTRE_POS) - RTargetPos).dir() - 0.05,POS_SIDE_LEFT));
	//				_MAPos = DefendUtils::reversePoint(RblockPos);
	//			}
	//		}
	//	}			
	//}

	_lastMAPos = _MAPos;
	return _MAPos;
}
