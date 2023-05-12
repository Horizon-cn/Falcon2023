#ifndef __BALL_CHASER_ATTRIBUTE_SET__
#define __BALL_CHASER_ATTRIBUTE_SET__

#include "AttributeSetNew.h"
#include "singleton.h"

class CballChaserAttributeSet :public CAttributeSetNew
{
public:
	CballChaserAttributeSet() { setAttributes(); }
protected:
	void setAttributes();
};

typedef Falcon::NormalSingleton<CballChaserAttributeSet> ballChaserAttributeSet;

#endif