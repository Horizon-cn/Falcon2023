#ifndef __SPEED_TEST_H__
#define __SPEED_TEST_H__
#include "PlayerTask.h"
#include "BufferCounter.h"
#include "param.h"
#include <QFile>

class CSpeedTest :public CStatedTask {
public:
	CSpeedTest();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: CSpeedTest\n"; }
private:
	enum State {
		STATE_INIT,
		STATE_GET_READY,
		STATE_GOTO_1,
		STATE_GOTO_2,
		STATE_STOP,
		STATE_FAIL
	};
	QFile *_file1, *_file2;
	QTextStream *_out1, *_out2;
	State _state;
	CBufferCounter statusCounter;
	int velocityCounter;
	double _v;
};

#endif //__SPEED_TEST_H__
