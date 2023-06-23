#ifndef __CHaseToGetBall_H__
#define __CHaseToGetBall_H__
#include <skill/PlayerTask.h>

/**********************************************************
* Skill: CHaseToGetBall
* Description: 复杂的追踢追球getball，考虑球速在内
* Author: TYH
* E-mail: tyheeeer@sjtu.edu.com
* Created Date: 2023.6.24

***********************************************************/

class CChaseToGetBall :public CStatedTask {
public:
	CChaseToGetBall();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: ChaseKickV2\n"; }

private:
	bool faceTheirGoal(const CVisionModule* pVision, const int executor);
	CGeoPoint checkPointAvoidOurPenalty(const CVisionModule* pVision, CGeoPoint targetPoint);
	CPlayerCommand* _directCommand;	//直接发送命令
	int _lastCycle;
	int _stateCounter;
	int _goKickCouter;
	double _compensateDir;
	int _relinquishCounter;
	int _openKickCounter;
};

#endif //__CHaseToGetBall_H__