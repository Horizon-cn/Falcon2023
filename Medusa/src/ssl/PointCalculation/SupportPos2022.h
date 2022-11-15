#ifndef  _SUPPORT_POS_2022_H_
#define _SUPPORT_POS_2022_H_
#include <skill/PlayerTask.h>
#include "ValueRange.h"
#include <list>

/**********************************************************
* Description: SupportPos
* Author: csy
* Created Date: 2022/3/28
***********************************************************/

struct SupportPosStruct2022 {
    CGeoPoint leftSupportPos;
    CGeoPoint rightSupportPos;

    CGeoPoint getLeftSupportPos() { return leftSupportPos; }
    CGeoPoint getRightSupportPos() { return rightSupportPos; }
};



class CSupportPos2022 {
	typedef std::list< CValueRange > RangeList;
public:
	CSupportPos2022();
	~CSupportPos2022();
	virtual void generateSupportPoint(const CVisionModule* pVision);
	virtual SupportPosStruct2022 getSupportPos(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	int getAreaScore(const CVisionModule* pVision, double v_max, double v_min);
	CGeoPoint generateBestPoint(const CVisionModule* pVision, double v_max, double v_min, double maxDist);
	
	double calcMaxDist(const CVisionModule* pVision, double middleDir, CGeoLine angleBisector);

protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: GoSupport\n"; }

private:
	SupportPosStruct2022 _supportPosStruct2022;
	int _lastCycle;
};

typedef NormalSingleton< CSupportPos2022 > SupportPos2022;

#endif //_SUPPORT_POS_2022_H_