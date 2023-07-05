#ifndef SIDEPOS_H
#define SIDEPOS_H

#include "Vision/VisionModule.h"
#include "singleton.h"

class CSidePos
{
public:
	CSidePos();
	CGeoPoint ultraPos();
	CGeoPoint chooseTargetPos();
};

typedef Falcon::NormalSingleton<CSidePos> SidePos;
#endif // SIDEPOS_H
