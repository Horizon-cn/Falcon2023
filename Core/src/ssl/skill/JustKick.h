#ifndef __JUSTKICK_H__
#define __JUSTKICK_H__
#include "PlayerTask.h"
#include "param.h"

class CJustKick :public CStatedTask {
public:
	CJustKick();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: CJustKick\n"; }
};

#endif //__JUSTKICK_H__
