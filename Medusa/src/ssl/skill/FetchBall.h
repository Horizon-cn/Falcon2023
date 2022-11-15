/************************************************************************/
/* Copyright (c) SRC, Shanghai Jiao Tong University 					*/
/* Team：		SRC         											*/
/* HomePage:	https://gitlab.com/src-ssl                      		*/
/************************************************************************/
/* File:	  FetchBall.cpp 											*/
/* Func:	  边线处拿球的skill                       					*/
/* Author:	  SUN CHANGJIANG, 2020.7.14									*/
/* E-mail:	  SCJ0013@sjtu.edu.cn										*/
/* Version:	  0.0.1														*/
/************************************************************************/

#ifndef _FETCH_BALL__
#define _FETCH_BALL__
#include <skill/PlayerTask.h>

/**
@brief    边线处取球
@details  2020中国赛挑战赛*/
class CFetchBall :public CStatedTask {
public:
	CFetchBall();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: FetchBall\n"; }
	bool CFetchBall::isVisionHasBall(const CVisionModule* pVision, const int vecNumber);

private:
	bool goBackBall;
	bool notDribble;
	int MIN_DIST;
	int cnt;
	int _lastCycle;
	int _lastRunner;
	CGeoPoint _mePos;
	CPlayerCommand * _directCommand;
	int meGetBall = 0;
	int meLoseBall = 0;
};

#endif
