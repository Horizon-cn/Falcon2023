#ifndef __GOALIE_2022_H__
#define __GOALIE_2022_H__
#include "PlayerTask.h"
#include "param.h"

class CGoalie2022 :public CStatedTask {
public:
	enum GoalieState { NORMAL, SAVE, CLEAR, SUPPORT, PENALTY_WAIT, PENALTY_TRICK, PENALTY_ATTACK, TEST ,NEED_TO_BE_RESCUED };
	CGoalie2022();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: CGoalie2022\n"; }
private:
	void updateBallJudgementOfGoalie();
	void updateCycleCounter();

	CPlayerTask* normalTask();
	CPlayerTask* saveTask();
	CPlayerTask* clearTask();
	CPlayerTask* supportTask();
	CPlayerTask* attackTask();
	CPlayerTask* rescueTask();

	bool isMeReady4Ball(double dist_ball2goal);
	bool canMeAttack();
	bool isPosInCornerShootArea(const CGeoPoint& pos);
	CGeoPoint generateNormalPoint(CGeoPoint defenceTarget);
	CGeoPoint generateSavePoint();
	double calcClearDir();
	double nearestEnemyFrom(CGeoPoint p);
	CGeoPoint syntYPos(const CGeoPoint& ref, const CGeoPoint& target);

	int lastSaveCycle, startCycle_ballInsidePenalty, startCycle_ballOutsidePenalty;
	bool needSave, needClear, needSupport;
	bool trickStart, trickFinish, needAttack;
	bool isNewSave,need_to_be_rescued;
	int cycle_ballInsidePenalty,cycle_penaltyAttack;
};

#endif //__GOALIE_2022_H__