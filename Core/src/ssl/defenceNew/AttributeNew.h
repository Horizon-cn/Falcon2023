#ifndef __ATTRIBUTE_NEW_H__
#define __ATTRIBUTE_NEW_H__

#include "Global.h"

using namespace std;

//抽象的属性 包含属性评价方法、属性值，属性的名称只能在初始化时指定
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