#ifndef __ATTRIBUTE_NEW_H__
#define __ATTRIBUTE_NEW_H__

#include "Vision/VisionModule.h"
#include "ParamManagerNew.h"

using namespace std;

//抽象的属性 包含属性评价方法、属性值，属性的名称只能在初始化时指定
//从原DefenceInfo移植并略微修改，name属性目前没用上，如果后续也没用上可以考虑直接删除
class CAttributeNew
{
public:
	CAttributeNew(const string name) :_name(name), _value(0) {}
	~CAttributeNew() {}

	//评价的接口,num是对手车的车号
	virtual void evaluate(const CVisionModule* pVision, const int num) = 0;

	//获取评价值
	double getValue() { return _value; }
	string getName() { return _name; }

protected:
	void setValue(double theValue) { _value = theValue; }

private:
	double _value;
	string _name;
};

#endif