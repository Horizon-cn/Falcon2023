/*
测试GotoPosition的处理速度与实车速度的关系
目前采用僵硬移植，故测试前请保证模拟的是GotoPosition的最新代码

其实更合理的处理方式是，用lua完成来回跑与提速，原始数据记录直接放进GotoPosition，并另用脚本对原始数据记录进行加工

目前bug：初始速度少一轮记录
*/

#include "SpeedTest.h"
#include <QDir>
#include <qdatetime.h>
//temp GotoPosition的头文件
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
//temp Gotoposition的namespace
namespace {
	/// 调试开关
	bool DRAW_TARGET = false;
	bool RECORD_COMMAND = false;
	ofstream velCommandData("../data/vel_command_record.txt");
	bool NOT_MOVE = false;

	/// 用于解决到点晃动的问题
	const double DIST_REACH_CRITICAL = 2;	// [unit : cm]

	/// 底层运动控制参数 ： 默认增大平动的控制性能
	double MAX_TRANSLATION_SPEED = 200;
	double MAX_TRANSLATION_ACC = 200;
	double MAX_ROTATION_SPEED = 5;
	double MAX_ROTATION_ACC = 15;
	double MAX_TRANSLATION_DEC = 200;

	double TRANSLATION_ACC_LIMIT = 200;
	double TRANSLATION_SPEED_LIMIT = 200;
	double TRANSLATION_ROTATE_ACC_LIMIT = 50;

	double stopBallAvoidDist = 50;
	/// 守门员专用
	double MAX_TRANSLATION_SPEED_GOALIE = 200;
	double MAX_TRANSLATION_ACC_GOALIE = 200;
	double MAX_TRANSLATION_DEC_GOALIE = 200;
	double MAX_ROTATION_ACC_GOALIE = 15;
	double MAX_ROTATION_SPEED_GOALIE = 15;

	/// 后卫专用
	double MAX_TRANSLATION_SPEED_BACK = 200;
	double MAX_TRANSLATION_ACC_BACK = 200;
	double MAX_TRANSLATION_DEC_BACK = 200;
	double MAX_ROTATION_ACC_BACK = 15;
	double MAX_ROTATION_SPEED_BACK = 15;

	// 限定小车横向纵向运动速度

	double MAX_TRANSLATION_SPEED_X = 500;
	double MAX_TRANSLATION_SPEED_Y = 500;

	/// 底层控制方法参数
	int TASK_TARGET_COLOR = COLOR_CYAN;
	int SAO_ACTION = 0;

	double Y_COMPENSATE_K = 0.0035;
	double Y_COMPENSATE_B = -0.1042;
	double SLOW_FACTOR = 0.5;
}
using namespace Param::Vehicle::V2;

CSpeedTest::CSpeedTest() :_state(STATE_INIT), velocityCounter(1)
{
	QString time = QDateTime::currentDateTime().toString("hh-mm-ss");
	QString name1 = dir.path() + "/1-" + time + ".txt";
	QString name2 = dir.path() + "/2-" + time + ".txt";
	_file1 = new QFile(name1);
	_file2 = new QFile(name2);
	_out1 = new QTextStream(_file1);
	_out2 = new QTextStream(_file2);
	//temp GotoPosition的初始化
	DRAW_TARGET = paramManager->DRAW_TARGET;
	RECORD_COMMAND = paramManager->RECORD_COMMAND;
	NOT_MOVE = paramManager->NOT_MOVE;
	{
		SLOW_FACTOR = ParamManager::Instance()->SLOW_FACTOR;

		// 守门员单独控制平动参数
		MAX_TRANSLATION_SPEED_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_SPEED_GOALIE;
		MAX_TRANSLATION_ACC_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_ACC_GOALIE;
		MAX_TRANSLATION_DEC_GOALIE = ParamManager::Instance()->MAX_TRANSLATION_DEC_GOALIE;
		MAX_ROTATION_ACC_GOALIE = ParamManager::Instance()->MAX_ROTATION_ACC_GOALIE;
		MAX_ROTATION_SPEED_GOALIE = ParamManager::Instance()->MAX_ROTATION_SPEED_GOALIE;

		// 后卫单独控制平动参数
		MAX_TRANSLATION_SPEED_BACK = ParamManager::Instance()->MAX_TRANSLATION_SPEED_BACK;
		MAX_TRANSLATION_ACC_BACK = ParamManager::Instance()->MAX_TRANSLATION_ACC_BACK;
		MAX_TRANSLATION_DEC_BACK = ParamManager::Instance()->MAX_TRANSLATION_DEC_BACK;
		MAX_ROTATION_ACC_BACK = ParamManager::Instance()->MAX_ROTATION_ACC_BACK;
		MAX_ROTATION_SPEED_BACK = ParamManager::Instance()->MAX_ROTATION_SPEED_BACK;

		// 其他车的平动参数
		MAX_TRANSLATION_SPEED = ParamManager::Instance()->MAX_TRANSLATION_SPEED;
		MAX_TRANSLATION_ACC = ParamManager::Instance()->MAX_TRANSLATION_ACC;
		MAX_TRANSLATION_DEC = ParamManager::Instance()->MAX_TRANSLATION_DEC;

		MAX_ROTATION_SPEED = ParamManager::Instance()->MAX_ROTATION_SPEED;
		MAX_ROTATION_ACC = ParamManager::Instance()->MAX_ROTATION_ACC;

		TRANSLATION_ACC_LIMIT = ParamManager::Instance()->TRANSLATION_ACC_LIMIT;
		TRANSLATION_SPEED_LIMIT = ParamManager::Instance()->TRANSLATION_SPEED_LIMIT;
		TRANSLATION_ROTATE_ACC_LIMIT = ParamManager::Instance()->TRANSLATION_ROTATE_ACC_LIMIT;

		MAX_TRANSLATION_SPEED_X = ParamManager::Instance()->MAX_TRANSLATION_SPEED_X;
		MAX_TRANSLATION_SPEED_Y = ParamManager::Instance()->MAX_TRANSLATION_SPEED_Y;
	}
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
				_state = STATE_FAIL;
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
			} else {
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
			//(*_out1) << "#" << endl;
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
			//(*_out1) << "#" << endl;
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

	GDebugEngine::Instance()->gui_debug_msg(debug_pos1, ("speed test: " + to_string(_v)).c_str());
	CPlayerTask* pTask;
	RET_VEL ret;
	switch (_state)
	{
	case STATE_GET_READY:
		playerTask.player.pos = pos1;
		pTask = TaskFactoryV2::Instance()->GotoPosition(playerTask);
		break;
	case STATE_GOTO_1:
		playerTask.player.pos = pos2;
		pTask = TaskFactoryV2::Instance()->GotoPosition(playerTask);
		reset(playerTask);
		ret = simulate_local(pVision);
		(*_out1) << _v << " " << pVision->Cycle() << " " << me.Pos().x() << " " << me.Pos().y() << " " <<
			ret.globalVel.x() << " " << ret.globalVel.y() << " " << ret.localVel.x() << " " << ret.localVel.y() << " " << endl;
		break;
	case STATE_GOTO_2:
		playerTask.player.pos = pos1;
		pTask = TaskFactoryV2::Instance()->GotoPosition(playerTask);
		reset(playerTask);
		ret = simulate_local(pVision);
		(*_out1) << _v << " " << pVision->Cycle() << " " << me.Pos().x() << " " << me.Pos().y() << " " <<
			ret.globalVel.x() << " " << ret.globalVel.y() << " " << ret.localVel.x() << " " << ret.localVel.y() << " " << endl;
		break;
	case STATE_STOP:
		pTask = PlayerRole::makeItStop(num);
		GDebugEngine::Instance()->gui_debug_msg(debug_pos2, "speed test finish!");
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

CSpeedTest::RET_VEL CSpeedTest::simulate_local(const CVisionModule* pVision)
{
	/************************************************************************/
	/* 任务参数解析                                                         */
	/************************************************************************/
	const int vecNumber = task().executor;
	const PlayerVisionT& self = pVision->OurPlayer(vecNumber);
	// 小车的位置
	const CGeoPoint& vecPos = self.Pos();
	// 目标的位置
	CGeoPoint target = task().player.pos;
	const CVector player2target = target - vecPos;
	const double dist = player2target.mod();

	int playerFlag = task().player.flag;
	const bool IsGoMiddle = task().player.IsGoMiddle; // 现在是否走在中间点
	const bool isDribble = playerFlag & PlayerStatus::DRIBBLING;

	const bool isGoalie = (vecNumber == TaskMediator::Instance()->goalie());
	const bool isBack = TaskMediator::Instance()->isBack(vecNumber);
	const bool isMultiBack = TaskMediator::Instance()->isMultiBack(vecNumber);

	/************************************************************************/
	/* 修正非法目标点输入                                                     */
	/************************************************************************/
	if (isnan(target.x()) || isnan(target.y())) {
		target = self.Pos();
		cout << "Target Pos is NaN, vecNumber is : " << vecNumber << endl;
	}
	double arrivedDist = self.Vel().mod() * 0.12 + 0.1;
	// 记录当前的规划执行目标点
	DRAW_TARGET = 0;
	if (DRAW_TARGET) {
		GDebugEngine::Instance()->gui_debug_x(target, TASK_TARGET_COLOR);
		GDebugEngine::Instance()->gui_debug_line(self.Pos(), target, TASK_TARGET_COLOR);
		if (task().player.vel.mod() > 1e-8) {
			GDebugEngine::Instance()->gui_debug_line(target, target + task().player.vel / 10, COLOR_WHITE);
		}
	}

	/************************************************************************/
	/* 确定运动性能参数 确定只使用OmniAuto配置标签中的参数                      */
	/************************************************************************/
	CCommandFactory* pCmdFactory = CmdFactory::Instance();
	PlayerCapabilityT capability = setCapability(pVision);

	/************************************************************************/
	/* 确定初末状态，结合选取的控制方式生成运动指令                             */
	/************************************************************************/
	// 设定目标状态
	PlayerVisionT final;
	final.SetPos(target);
	final.SetDir((playerFlag & (PlayerStatus::TURN_AROUND_FRONT)) ? self.Dir() : task().player.angle);
	final.SetVel(task().player.vel);
	final.SetRotVel(task().player.rotvel);

	// 调用控制方法
	CControlModel control;
	nonZeroMode mode = FAST;

	// 进行轨迹生成并记录理想执行时间
	//control.makeCmTrajectory(self, final, capability, mode);					// CMU 非零速到点
	static int idx = 0;

	control.makeCmTrajectoryTest(self, final, capability, mode, IsGoMiddle);
	//control.makeCmTrajectory(self, final, capability, mode);
	float usedtime = target.dist(self.Pos()) / capability.maxSpeed / 1.414;		// 单位：秒
	const double time_factor = 1.5;
	usedtime = expectedCMPathTime(self, final.Pos(), capability, task().player.vel, time_factor, IsGoMiddle);

	/************************************************************************/
	/* 调用动态避障模块（DSS），对轨迹生成模块运动指令进行避碰检查	*/
	/************************************************************************/
	// 获取轨迹生成模块在全局坐标系中的速度指令
	CVector globalVel = control.getNextStep().Vel();
	//cout << "vel:  "<<globalVel.mod() << endl;
	// 如果是门将或者后卫且距离禁区比较远，需要打开DSS避障，防止刚匹配的后卫和出击较远的门将发生碰撞
	// 在禁区边的后卫允许撞车，否则容易被进球!!!
	// 其他球员强制全部开DSS
	if (!((isGoalie || isBack || isMultiBack) && Utils::InOurPenaltyArea(vecPos, 40))) {
		playerFlag |= PlayerStatus::ALLOW_DSS;
	}

	if (playerFlag & PlayerStatus::ALLOW_DSS) {
		int priority = 0;
		CVector tempVel = DynamicSafetySearch::Instance()->SafetySearch(vecNumber, globalVel, pVision, priority, target, task().player.flag, usedtime, capability.maxAccel);
		// 不加这个在stop的时候车可能会冲出去
		if (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop" && tempVel.mod() > 150) {
		} else {
			globalVel = tempVel;
		}
	}

	/************************************************************************/
	/* 处理最后的指令                                                        */
	/************************************************************************/
	// 靠近系数调整，用于解决到点晃动的问题 [7/2/2011 cliffyin]
	double alpha = 1.0;
	if (dist <= DIST_REACH_CRITICAL) {
		alpha *= sqrt(dist / DIST_REACH_CRITICAL);
	}
	// 车坐标系里面的速度
	CVector localVel = (globalVel * alpha).rotate(-self.Dir());

	return RET_VEL(globalVel, localVel);
}

PlayerCapabilityT CSpeedTest::setCapability(const CVisionModule* pVision) {
	const int vecNumber = task().executor;
	const bool isGoalie = (vecNumber == TaskMediator::Instance()->goalie());
	const bool isBack = TaskMediator::Instance()->isBack(vecNumber);
	const bool isMultiBack = TaskMediator::Instance()->isMultiBack(vecNumber);

	const int playerFlag = task().player.flag;
	PlayerCapabilityT capability;

	// Traslation 确定运动参数
	if (isGoalie) {
		capability.maxSpeed = MAX_TRANSLATION_SPEED_GOALIE;
		capability.maxAccel = MAX_TRANSLATION_ACC_GOALIE;
		capability.maxDec = MAX_TRANSLATION_DEC_GOALIE;
		// Rotation	  确定转动运动参数
		capability.maxAngularSpeed = MAX_ROTATION_SPEED_GOALIE;
		capability.maxAngularAccel = MAX_ROTATION_ACC_GOALIE;
		capability.maxAngularDec = MAX_ROTATION_ACC_GOALIE;
	} else if (isBack || isMultiBack) {
		capability.maxSpeed = MAX_TRANSLATION_SPEED_BACK;
		capability.maxAccel = MAX_TRANSLATION_ACC_BACK;
		capability.maxDec = MAX_TRANSLATION_DEC_BACK;
		// Rotation	  确定转动运动参数
		capability.maxAngularSpeed = MAX_ROTATION_SPEED_BACK;
		capability.maxAngularAccel = MAX_ROTATION_ACC_BACK;
		capability.maxAngularDec = MAX_ROTATION_ACC_BACK;
	} else {
		capability.maxSpeed = MAX_TRANSLATION_SPEED;
		capability.maxAccel = MAX_TRANSLATION_ACC;
		capability.maxDec = MAX_TRANSLATION_DEC;
		// Rotation	  确定转动运动参数
		capability.maxAngularSpeed = MAX_ROTATION_SPEED;
		capability.maxAngularAccel = MAX_ROTATION_ACC;
		capability.maxAngularDec = MAX_ROTATION_ACC;
	}



	if (task().player.max_acceleration > 1e-8) {

		if (!task().player.IsGetBaller)
			capability.maxAccel = task().player.max_acceleration > TRANSLATION_ACC_LIMIT ? TRANSLATION_ACC_LIMIT : task().player.max_acceleration;
		else capability.maxAccel = task().player.max_acceleration;

		if (isGoalie || isBack || isMultiBack)
			capability.maxAccel = task().player.max_acceleration;
		capability.maxDec = capability.maxAccel;
	}
	if (task().player.max_speed > 1e-8) {

		if (!task().player.IsGetBaller)
			capability.maxSpeed = task().player.max_speed > TRANSLATION_SPEED_LIMIT ? TRANSLATION_SPEED_LIMIT : task().player.max_speed;
		else capability.maxSpeed = task().player.max_speed;

	}

	if (task().player.max_rot_acceleration > 1e-8) {

		if (!task().player.IsGetBaller)
			capability.maxAngularAccel = task().player.max_rot_acceleration > TRANSLATION_ROTATE_ACC_LIMIT ? TRANSLATION_ROTATE_ACC_LIMIT : task().player.max_rot_acceleration;
		else capability.maxAngularAccel = task().player.max_rot_acceleration;

		capability.maxAngularDec = capability.maxAngularAccel;
	}

	if (task().player.max_rot_speed > 1e-8) {
		capability.maxAngularSpeed = task().player.max_rot_speed;
	}

	if (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop") {
		capability.maxSpeed = 140;
	}

	if (WorldModel::Instance()->CurrentRefereeMsg() == "ourBallPlacement")
	{
		capability.maxSpeed *= SLOW_FACTOR;
	}

	capability.maxSpeedX = MAX_TRANSLATION_SPEED_X;
	capability.maxSpeedY = MAX_TRANSLATION_SPEED_Y;

	return capability;
}