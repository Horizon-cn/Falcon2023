#ifndef __GOALIE_2022_H__
#define __GOALIE_2022_H__
#include "PlayerTask.h"
#include "param.h"

class CGoalie2022 :public CStatedTask {
public:
	enum Tevaluate { NORMAL, RESCUE, SUPPORT, CLEAR_BALL, ATTACK_ENEMY, TEST };
	enum Tpenalty { PENALTY_WAIT, PENALTY_TRICK_START, PENALTY_TRICK_FINISH };
	struct supportStruct {
		supportStruct(const CVisionModule* pVision, int i, int robotNum);
		int supporterNum; CGeoPoint supportPoint; double angleDiff;
	};
	CGoalie2022();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: CGoalie2022\n"; }
private:
	Tevaluate evaluate(const CVisionModule* pVision);
	inline bool IsFarFromBack(const CGeoPoint& pos, int x = -Param::Field::PITCH_LENGTH * 0.1);
	bool ShouldAttack(const CVisionModule* pVision);
	bool isBallShot2Goal(const CVisionModule* pVision);
	CPlayerTask* normalTask(const CVisionModule* pVision);
	CPlayerTask* rescueTask(const CVisionModule* pVision);
	CPlayerTask* supportTask(const CVisionModule* pVision);
	CPlayerTask* clearBallTask(const CVisionModule* pVision);
	CPlayerTask* attackEnemyTask(const CVisionModule* pVision);
	CPlayerTask* penaltyTask(const CVisionModule* pVision);
	void generateRescuePoint(const CVisionModule* pVision);
	double CalClearBallDir(const CVisionModule* pVision);

	Tpenalty last_penalty_status;
};

#endif //__GOALIE_2022_H__
