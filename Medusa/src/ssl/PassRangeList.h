#ifndef _PASS_RANGE_LIST_H_
#define _PASS_RANGE_LIST_H_
#include <ValueRange.h>
#include "Vision/VisionModule.h"
#include <vector>
/**
* CShootRangeList.
* 产生一个可传球的角度域 列表
*
*/

class CPassRangeList {
public:
	CPassRangeList(const CVisionModule* pVision);
	const CValueRangeList& getLeftPassRange();
	const CValueRangeList& getRightPassRange();

private:
	// 保留上次的，防止重复计算
	CValueRangeList lastLeftPassList; // 上次击球射门
	CValueRangeList lastRightPassList; // 上次击球射门
	int lastCycle; // 上次的时间
	CGeoPoint lastPoint;

};
#endif // _PASS_RANGE_LIST_H_