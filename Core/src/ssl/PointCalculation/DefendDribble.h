/************************************************************************/
/* Copyright (c) Shanghai Jiao Tong University							*/
/* Team：		SRC-SJTU								                */
/************************************************************************/
/* File:	  DefendDribble.h											*/
/* Func:	  始终站在吸球车和球门连线间 不让其转身直接射门             */
/* Author:	  和家平 2020-10-24			                                */
/* Refer:	  ###														*/
/* E-mail:	  hejiaping2016@sjtu.edu.cn									*/
/* Version:	  0.0.1														*/
/************************************************************************/

#ifndef _DEFEND_DRIBBLE_H_  //防止被多重定义
#define  _DEFEND_DRIBBLE_H_

#include "PointCalculation/AtomPos.h"
#include <singleton.h>
#include "DefendUtils.h"

class CVisionModule;

class CDefendDribble 
{
public:
	struct TheirPlayerXPair {
		TheirPlayerXPair(int n, double p) : num(n), coordX(p) { }
		bool operator < (const TheirPlayerXPair& n) const { return coordX < n.coordX; }
		int num;					// player number
		double coordX;			// Player X coordinate
	};
	typedef std::vector< TheirPlayerXPair > TheirPlayerXList;
	CDefendDribble();
	~CDefendDribble();

	TheirPlayerXList _TheirPlayerXList;

	/**
	@生成防范吸球车直接射门的点
	*/
	CGeoPoint generateDeDribblePos(const CVisionModule* pVision);

	CGeoPoint getDeDribblePos(const CVisionModule* pVision);

private:
	CGeoPoint _DeDribblePos; //防范吸球车的点
	CGeoPoint _lastDeDribblePos; 
	int _lastCycle;
};

typedef Falcon::NormalSingleton< CDefendDribble > DefendDribble;

#endif //_DEFEND_DRIBBLE_H


