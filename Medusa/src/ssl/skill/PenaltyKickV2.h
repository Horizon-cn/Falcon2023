#pragma once
#ifndef  _PENALTY_KICK_V2_H_
#define _PENALTY_KICK_V2_H_

#include <skill/PlayerTask.h>

class CPenaltyKickV2 : public CStatedTask {
public:
	CPenaltyKickV2() {}
	~CPenaltyKickV2(){}
	virtual void plan(const CVisionModule* pVision);
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
	virtual bool isEmpty() const { return false; }

protected:
	CPlayerCommand* _directCommand;
};
#endif