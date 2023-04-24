#ifndef __ATTRIBUTE_SET_NEW_H__
#define __ATTRIBUTE_SET_NEW_H__

#include <vector>
#include <utility>
#include "AttributeNew.h"

//抽象属性集，加权得到分数，权重自动从参数管理器获取
class CAttributeSetNew
{
	typedef std::pair<double, CAttributeNew*> TattributePair;//权值和对应的属性
public:
	CAttributeSetNew() {};
	~CAttributeSetNew()
	{
		for (auto attributePair : _attributePairList)
		{
			delete attributePair.second;
		}
	}

	double evaluate(const CVisionModule* pVision, int num)
	{
		double score = 0;
		for (auto& attributePair : _attributePairList)
		{
			attributePair.second->evaluate(pVision, num);
			score += attributePair.first * attributePair.second->getValue();
		}
		return score;
	}
protected:
	virtual void setAttributes() = 0;
	std::vector<TattributePair> _attributePairList;
};

//实例化属性集所用的宏定义

#define DEFINE_ATTRIBUTE_NEW(attr_class) \
class attr_class:CAttributeNew \
{ \
public:	\
	attr_class():CAttributeNew(#attr_class){}; \
	void evaluate(const CVisionModule* pVision,const int num); \
};

#define EVALUATE_ATTRIBUTE_NEW(attr_class) \
void attr_class::evaluate(const CVisionModule *pVision, const int num)

#define ADD_ATTRIBUTE_NEW(attr_class) \
_attributePairList.emplace_back(paramManager->factor_##attr_class,(CAttributeNew*)new attr_class)

#endif