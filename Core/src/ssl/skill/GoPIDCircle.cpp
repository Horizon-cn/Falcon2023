#include "GoPIDCircle.h"
#include <utils.h>
#include "skill/Factory.h"
#include <CommandFactory.h>
#include <Vision/VisionModule.h>
#include <WorldModel/RobotCapability.h>
#include <sstream>
#include <TaskMediator.h>
#include <WorldModel/robot_power.h>
#include <WorldModel/DribbleStatus.h>
#include <GDebugEngine.h>
#include <fstream>
#include "param.h"
using namespace Param::Vehicle::V2;
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

	double stopBallAvoidDist = 70.0;
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

	/// 底层控制方法参数
	int TASK_TARGET_COLOR = COLOR_CYAN;
	int SAO_ACTION = 0;

	double Y_COMPENSATE_K = 0.0035;
	double Y_COMPENSATE_B = -0.1042;
	double SLOW_FACTOR = 0.5;
}

CGoPIDCircle::CGoPIDCircle()
{
	LastError = AccuError = 0;
	Ki = 0;
	Kp = 0.009;
	Kd = 0;
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
	}
}
/*
PlayerCapabilityT CGoPIDCircle::setCapability(const CVisionModule* pVision) {
	PlayerCapabilityT capability;
	return capability;
}
*/
/*
PlayerCapabilityT CGoPIDCircle::setCapability(const CVisionModule* pVision) {
	const int vecNumber = task().executor;
	const bool isGoalie = (vecNumber == TaskMediator::Instance()->goalie());
	const bool isBack = (vecNumber == TaskMediator::Instance()->leftBack()) ||
		(vecNumber == TaskMediator::Instance()->rightBack()) ||
		(vecNumber == TaskMediator::Instance()->singleBack()) ||
		(vecNumber == TaskMediator::Instance()->sideBack()) ||
		(vecNumber == TaskMediator::Instance()->defendMiddle());
	const bool isMultiBack = TaskMediator::Instance()->isMultiBack(vecNumber);

	const int playerFlag = task().player.flag;
	PlayerCapabilityT capability;

	// Traslation 确定运动参数
	if (vecNumber == TaskMediator::Instance()->goalie()) {
		capability.maxSpeed = MAX_TRANSLATION_SPEED_GOALIE;
		capability.maxAccel = MAX_TRANSLATION_ACC_GOALIE;
		capability.maxDec = MAX_TRANSLATION_DEC_GOALIE;
		// Rotation	  确定转动运动参数
		capability.maxAngularSpeed = MAX_ROTATION_SPEED_GOALIE;
		capability.maxAngularAccel = MAX_ROTATION_ACC_GOALIE;
		capability.maxAngularDec = MAX_ROTATION_ACC_GOALIE;
	}
	else if (TaskMediator::Instance()->leftBack() != 0 && vecNumber == TaskMediator::Instance()->leftBack()
		|| TaskMediator::Instance()->rightBack() != 0 && vecNumber == TaskMediator::Instance()->rightBack()
		|| TaskMediator::Instance()->singleBack() != 0 && vecNumber == TaskMediator::Instance()->singleBack()
		|| TaskMediator::Instance()->sideBack() != 0 && vecNumber == TaskMediator::Instance()->sideBack()
		|| isMultiBack) {
		capability.maxSpeed = MAX_TRANSLATION_SPEED_BACK;
		capability.maxAccel = MAX_TRANSLATION_ACC_BACK;
		capability.maxDec = MAX_TRANSLATION_DEC_BACK;
		// Rotation	  确定转动运动参数
		capability.maxAngularSpeed = MAX_ROTATION_SPEED_BACK;
		capability.maxAngularAccel = MAX_ROTATION_ACC_BACK;
		capability.maxAngularDec = MAX_ROTATION_ACC_BACK;
	}
	else {
		capability.maxSpeed = MAX_TRANSLATION_SPEED;
		capability.maxAccel = MAX_TRANSLATION_ACC;
		capability.maxDec = MAX_TRANSLATION_DEC;
		// Rotation	  确定转动运动参数
		capability.maxAngularSpeed = MAX_ROTATION_SPEED;
		capability.maxAngularAccel = MAX_ROTATION_ACC;
		capability.maxAngularDec = MAX_ROTATION_ACC;
	}
	if (task().player.max_acceleration > 1e-8) {
		capability.maxAccel = task().player.max_acceleration > TRANSLATION_ACC_LIMIT ? TRANSLATION_ACC_LIMIT : task().player.max_acceleration;
		if (isGoalie || isBack || isMultiBack)
			capability.maxAccel = task().player.max_acceleration;
		capability.maxDec = capability.maxAccel;
	}
	if (task().player.max_speed > 1e-8) {
		capability.maxSpeed = task().player.max_speed > TRANSLATION_SPEED_LIMIT ? TRANSLATION_SPEED_LIMIT : task().player.max_speed;
	}

	if (task().player.max_rot_acceleration > 1e-8) {
		capability.maxAngularAccel = task().player.max_rot_acceleration > TRANSLATION_ROTATE_ACC_LIMIT ? TRANSLATION_ROTATE_ACC_LIMIT : task().player.max_rot_acceleration;
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
	return capability;
}
*/


CGoPIDCircle::~CGoPIDCircle() {

}
void CGoPIDCircle::plan(const CVisionModule* pVision) {
	return;
}
CPlayerCommand* CGoPIDCircle::execute(const CVisionModule* pVision) {
	const int vecNumber = task().executor;
	const bool isDribble = PlayerStatus::DRIBBLING;

	const bool isBack = (vecNumber == TaskMediator::Instance()->leftBack()) ||
		(vecNumber == TaskMediator::Instance()->rightBack()) ||
		(vecNumber == TaskMediator::Instance()->singleBack()) ||
		(vecNumber == TaskMediator::Instance()->sideBack()) ||
		(vecNumber == TaskMediator::Instance()->defendMiddle());
	const bool isMultiBack = TaskMediator::Instance()->isMultiBack(vecNumber);

	CCommandFactory* pCmdFactory = CmdFactory::Instance();
	//PlayerCapabilityT capability = setCapability(pVision);

	bool opt = task().player.left_or_right;
	const CGeoPoint Center = task().player.pos;
	double Radius = task().player.GoRadius;
	const PlayerVisionT& self = pVision->OurPlayer(vecNumber);
	// 小车信息
	double selfDir = self.Dir();
	const CGeoPoint& selfPos = self.Pos();
	// 小车朝向和位置
	double rotVel = PIDController(pVision, vecNumber, Center, Radius, opt);
	
	return pCmdFactory->newCommand(CPlayerSpeedV2(vecNumber, 200.0, 0.0, rotVel, 0));
	// 目标位置
	return NULL;

}

double CGoPIDCircle::PIDController(const CVisionModule* pVision, const int vecNumber, CGeoPoint Center, double Radius, bool opt) {
	const PlayerVisionT& self = pVision->OurPlayer(vecNumber);
	CGeoPoint selfpos = self.Pos();
	double Dist = (selfpos - Center).mod();
	double Error = Dist - Radius;
	double Ret = Ki * AccuError + Kd * (Error - LastError) + Kp * Error;

	printf("Error:%.3lf Ki:%.3lf Kd:%.3lf, Kp:%.3lf, Out:%.3lf\n", Error, Ki * AccuError, Kd * (Error - LastError), Kp * Error, LimitOmiga(Ret) * opt);
	AccuError = LimitAccu(AccuError + Error);
	LastError = Error;
	return LimitOmiga(Ret) * opt;
}
double CGoPIDCircle::LimitAccu(double Input) {
	if (Input > 1.0)return 1.0;
	if (Input < -1.0)return -1.0;
	return Input;
}
double CGoPIDCircle::LimitOmiga(double Input) {
	if (Input > MAX_ROTATION_SPEED)return MAX_ROTATION_SPEED;
	if (Input < -1.0 * MAX_ROTATION_SPEED)return -1.0 * MAX_ROTATION_SPEED;
	return Input;
}