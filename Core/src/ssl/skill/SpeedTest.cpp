#include "SpeedTest.h"
#include <QDir>
#include <qdatetime.h>

#include "GDebugEngine.h"
#include "Vision/VisionModule.h"
#include "skill/Factory.h"
#include "utils.h"
#include "WorldModel/DribbleStatus.h"
#include "RobotSensor.h"
#include "param.h"
#include "WorldModel/WorldModel.h"
#include "TaskMediator.h"

namespace {
	double distThreshold = 10;
	int waitBuf = 100;
	int forceBuf = 99999;
	int repeatTime = 2;
	CGeoPoint debug_pos1(100, 100);
	CGeoPoint debug_pos2(-100, -100);
	QDir dir("../data/speed_test/");
}
//todo 1 路径不存在
CSpeedTest::CSpeedTest() :_state(STATE_INIT), velocityCounter(1)
{
	QString time = QDateTime::currentDateTime().toString("hh-mm-ss");
	QString name1 = dir.path() + "/1-" + time + ".txt";
	QString name2 = dir.path() + "/2-" + time + ".txt";
	_file1 = new QFile(name1);
	_file2 = new QFile(name2);
	_out1 = new QTextStream(_file1);
	_out2 = new QTextStream(_file2);
}

void CSpeedTest::plan(const CVisionModule* pVision)
{
	//以下解析参数中task()的参数名字不具有实际意义，仅为传参方便使用
	const int num = task().executor;
	const CGeoPoint pos1 = task().player.pos;
	const CGeoPoint pos2 = task().ball.pos;
	const double v_start = task().player.speed_x;
	const double v_end = task().player.speed_y;
	const double v_step = task().player.rotvel;

	const PlayerVisionT& me = pVision->OurPlayer(num);
	switch (_state)
	{
	case STATE_INIT:
		_v = v_start;
		_state = STATE_GET_READY;
		statusCounter.startCount(vision->Cycle(), pos1.dist(me.Pos()) < distThreshold, waitBuf, forceBuf);
		if (!dir.exists())
		{
			if (!dir.mkpath("."))
			{
				_state=STATE_FAIL;
			}
		}
		if (!_file1->open(QIODevice::WriteOnly | QIODevice::Text))
		{
			_state = STATE_FAIL;
		}
		if (!_file2->open(QIODevice::WriteOnly | QIODevice::Text))
		{
			_state = STATE_FAIL;
		}
		break;
	case STATE_GET_READY:
		if (statusCounter.timeOut(vision->Cycle(), pos1.dist(me.Pos()) < distThreshold)) {
			statusCounter.clear();
			_state = STATE_GOTO_1;
			//(*_out2) << _v << " " << pVision->Cycle() << " ";
		}
		break;
	case STATE_GOTO_1:
		if (statusCounter.isClear(vision->Cycle())) {
			statusCounter.startCount(vision->Cycle(), pos2.dist(me.Pos()) < distThreshold, waitBuf, forceBuf);
			(*_out2) << _v << " " << pVision->Cycle() << " ";
			if (velocityCounter < repeatTime) {
				velocityCounter++;
			}
			else {
				velocityCounter = 1;
				_v += v_step;
				if (_v > v_end) {
					_state = STATE_STOP;
					(*_out2) << pVision->Cycle() << endl;
					_file1->close();
					_file2->close();
				}
			}
		}
		if (statusCounter.timeOut(vision->Cycle(), pos2.dist(me.Pos()) < distThreshold)) {
			statusCounter.clear();
			_state = STATE_GOTO_2;
			(*_out1) << "#" << endl;
			(*_out2) << pVision->Cycle() << endl;
		}
		break;
	case STATE_GOTO_2:
		if (statusCounter.isClear(vision->Cycle())) {
			statusCounter.startCount(vision->Cycle(), pos1.dist(me.Pos()) < distThreshold, waitBuf, forceBuf);
			(*_out2) << _v << " " << pVision->Cycle() << " ";
		}
		if (statusCounter.timeOut(vision->Cycle(), (pos1.dist(me.Pos()) < distThreshold))) {
			statusCounter.clear();
			_state = STATE_GOTO_1;
			(*_out1) << "#" << endl;
			(*_out2) << pVision->Cycle() << endl;
		}
		break;
	}

	static TaskT playerTask;
	playerTask.executor = num;
	playerTask.player.vel = CVector(0.0, 0.0);
	playerTask.player.rotvel = 0;
	playerTask.player.angle = (pos1 - pos2).dir();
	playerTask.player.flag = 0;
	playerTask.ball.Sender = 0;
	playerTask.player.max_speed = _v;

	GDebugEngine::Instance()->gui_debug_msg(debug_pos1, to_string(_v).c_str());//todo 目前只能显示，不能控制速度
	CPlayerTask* pTask;
	switch (_state)
	{
	case STATE_GET_READY:
		playerTask.player.pos = pos1;
		pTask = TaskFactoryV2::Instance()->SmartGotoPosition(playerTask);
		break;
	case STATE_GOTO_1:
		playerTask.player.pos = pos2;
		pTask = TaskFactoryV2::Instance()->SmartGotoPosition(playerTask);
		(*_out1) << _v << " " << pVision->Cycle() << " " << me.Pos().x() << " " << me.Pos().y() << endl;
		break;
	case STATE_GOTO_2:
		playerTask.player.pos = pos1;
		pTask = TaskFactoryV2::Instance()->SmartGotoPosition(playerTask);
		(*_out1) << _v << " " << pVision->Cycle() << " " << me.Pos().x() << " " << me.Pos().y() << endl;
		break;
	case STATE_STOP:
		pTask = PlayerRole::makeItStop(num);
		break;
	case STATE_FAIL:
		pTask = PlayerRole::makeItStop(num);
		GDebugEngine::Instance()->gui_debug_msg(debug_pos2, "file IO error!");
	}
	setSubTask(pTask);
	CStatedTask::plan(pVision);
}

CPlayerCommand* CSpeedTest::execute(const CVisionModule* pVision)
{
	if (subTask())
	{
		return subTask()->execute(pVision);
	}
	return NULL;
}