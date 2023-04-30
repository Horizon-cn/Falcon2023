#ifndef __BALL_RECEIVER_ATTRIBUTE_SET__
#define __BALL_RECEIVER_ATTRIBUTE_SET__

#include "AttributeSetNew.h"
#include "singleton.h"

class CballReceiverAttributeSet :public CAttributeSetNew
{
public:
	CballReceiverAttributeSet() { setAttributes(); }
protected:
	void setAttributes();
};

typedef Falcon::NormalSingleton<CballReceiverAttributeSet> ballReceiverAttributeSet;

#endif