#ifndef __SPEED_TEST_H__
#define __SPEED_TEST_H__
#include "PlayerTask.h"
#include "param.h"

class CSpeedTest :public CStatedTask {
public:
	CSpeedTest();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: CSpeedTest\n"; }
private:
	};

#endif //__SPEED_TEST_H__
