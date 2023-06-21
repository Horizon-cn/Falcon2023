#ifndef __SPEED_TEST_H__
#define __SPEED_TEST_H__
#include "PlayerTask.h"
#include "BufferCounter.h"
#include "param.h"
#include <QFile>

#include "GotoPosition.h"
#include <utils.h>
#include "skill/Factory.h"
#include <CommandFactory.h>
#include <Vision/VisionModule.h>
#include <WorldModel/RobotCapability.h>
#include <sstream>
#include <TaskMediator.h>
#include <MotionControl/ControlModel.h>
#include <WorldModel/robot_power.h>
#include <WorldModel/DribbleStatus.h>
#include <GDebugEngine.h>
#include "MotionControl/DynamicsSafetySearch.h"
#include "MotionControl/CMmotion.h"
#include <fstream>
#include "param.h"

class CSpeedTest :public CStatedTask {
public:
	CSpeedTest();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: CSpeedTest\n"; }
private:
	//模拟GotoPosition，获取其localVel。临时方法
	CVector simulate_local(const CVisionModule* pVision);
	PlayerCapabilityT setCapability(const CVisionModule* pVision);

	enum State {
		STATE_INIT,
		STATE_GET_READY,
		STATE_GOTO_1,
		STATE_GOTO_2,
		STATE_STOP,
		STATE_FAIL
	};
	QFile* _file1, * _file2;
	QTextStream* _out1, * _out2;
	State _state;
	CBufferCounter statusCounter;
	int velocityCounter;
	double _v;
};

#endif //__SPEED_TEST_H__
