#ifndef  _GO_SUPPORT_H_
#define _GO_SUPPORT_H_
#include <skill/PlayerTask.h>
#include "ValueRange.h"
#include <list>

/**********************************************************
* Skill: GoSupport
* Description: GoSupport
* Author: csy
* Created Date: 2022/3/28
***********************************************************/

class CGoSupport :public CStatedTask {
	typedef std::list< CValueRange > RangeList;
public:
	CGoSupport();
	~CGoSupport();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
	int isectSeg(const CVisionModule* pVision);
	double calcMaxDist(const CVisionModule* pVision, double middleDir, CGeoLine angleBisector);

protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: GoSupport\n"; }

private:
	CGeoPoint _lastLeftPlayerPos;
	CGeoPoint _lastRightPlayerPos;
};

#endif //_GO_SUPPORT_H_