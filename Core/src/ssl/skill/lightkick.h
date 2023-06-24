#ifndef _LIGHT_KICK_
#define _LIGHT_KICK_
#include <skill/PlayerTask.h>

class Clightkick :public CStatedTask
{
public:
	Clightkick();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: DribbleTurnKickV2\n"; }

private:
	
};
#endif