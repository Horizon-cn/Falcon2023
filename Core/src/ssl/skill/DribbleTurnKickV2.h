#ifndef _DRIBBLE_TURN_KICK_V2_
#define _DRIBBLE_TURN_KICK_V2_
#include <skill/PlayerTask.h>

class CDribbleTurnKickV2 :public CStatedTask
{
public:
	CDribbleTurnKickV2();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: DribbleTurnKickV2\n"; }

private:
	
};
#endif