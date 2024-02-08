#ifndef TechDefence_h__
#define TechDefence_h__
#include <skill/PlayerTask.h>
class CTechDefenceRobot : public CStatedTask{
public:
	CTechDefenceRobot();
	virtual void plan(const CVisionModule* pVision);
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty() const { return false;}
protected:
};