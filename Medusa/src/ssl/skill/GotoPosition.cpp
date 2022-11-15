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
/************************************************************************/
/*                                                                      */
/************************************************************************/
namespace {
	/// 调试开关
	bool DRAW_TARGET = false;
	bool RECORD_COMMAND = false;
	ofstream velCommandData("./data/vel_command_record.txt");
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

	/// 底层控制方法参数
	int TASK_TARGET_COLOR = COLOR_CYAN;
	int SAO_ACTION = 0;

	double Y_COMPENSATE_K = 0.0035;
	double Y_COMPENSATE_B = -0.1042;
	double SLOW_FACTOR = 0.5;
}
using namespace Param::Vehicle::V2;

/// 构造函数 ： 参数初始化
CGotoPosition::CGotoPosition()
{
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

/// 输出流 ： 参数显示
void CGotoPosition::toStream(std::ostream& os) const
{
	os << "Going to " << task().player.pos << " angle:" << task().player.angle;
}

/// 规划入口
void CGotoPosition::plan(const CVisionModule* pVision)
{
	return;
}

/// 执行接口
CPlayerCommand* CGotoPosition::execute(const CVisionModule* pVision)
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

	playerFlag = task().player.flag;
	const bool isDribble = playerFlag & PlayerStatus::DRIBBLING;

	const bool isBack = (vecNumber == TaskMediator::Instance()->leftBack()) ||
		(vecNumber == TaskMediator::Instance()->rightBack()) ||
		(vecNumber == TaskMediator::Instance()->singleBack()) ||
		(vecNumber == TaskMediator::Instance()->sideBack()) ||
		(vecNumber == TaskMediator::Instance()->defendMiddle());
	
	/************************************************************************/
	/* 修正非法目标点输入                                                     */
	/************************************************************************/
	if (isnan(target.x()) || isnan(target.y())) {
		target = self.Pos();
		cout << "Target Pos is NaN, vecNumber is : " << vecNumber << endl;
	}
	double arrivedDist = self.Vel().mod() * 0.12 + 0.1;
	// 记录当前的规划执行目标点
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
	control.makeCmTrajectory(self, final, capability, mode);					// CMU 非零速到点

	float usedtime = target.dist(self.Pos()) / capability.maxSpeed / 1.414;		// 单位：秒
	const double time_factor = 1.5;
	usedtime = expectedCMPathTime(self, final.Pos(), capability.maxAccel, capability.maxSpeed, time_factor);

	/************************************************************************/
	/* 调用动态避障模块（DSS），对轨迹生成模块运动指令进行避碰检查	*/
	/************************************************************************/
	// 获取轨迹生成模块在全局坐标系中的速度指令
	CVector globalVel = control.getNextStep().Vel();

	// 如果是后卫且距离禁区比较远，需要打开DSS避障，防止刚匹配的后卫发生碰撞
	// 在禁区边的后卫允许撞车，否则容易被进球!!!
	if (isBack && !Utils::InOurPenaltyArea(vecPos, 40)) {
		playerFlag |= PlayerStatus::ALLOW_DSS;
	}

	if (playerFlag & PlayerStatus::ALLOW_DSS) {
		int priority = 0;
		CVector tempVel = DynamicSafetySearch::Instance()->SafetySearch(vecNumber, globalVel, pVision, priority, target, task().player.flag, usedtime, capability.maxAccel);
		// 不加这个在stop的时候车可能会冲出去
		if (WorldModel::Instance()->CurrentRefereeMsg() == "gameStop" && tempVel.mod() > 150) { 
		}
		else {
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
	CVector localVel = (globalVel*alpha).rotate(-self.Dir());

	// 车坐标系里面的旋转速度
	double rotVel = control.getNextStep().RotVel();	
	if ((fabs(Utils::Normalize(final.Dir() - self.Dir())) <= Param::Math::PI * 5 / 180)) rotVel /= 2;

	// 车的吸球指令
	unsigned char dribblePower = 0;
	if (isDribble) {
		dribblePower = DRIBBLE_NORAML;
	}
	else {
		unsigned char set_power = DribbleStatus::Instance()->getDribbleCommand(vecNumber);
		if (set_power > 0) {
			dribblePower = set_power;
		}
		else {
			dribblePower = DRIBBLE_DISABLED;
		}
	}

	if (RECORD_COMMAND && vecNumber == paramManager->RECORD_NUM) {
		velCommandData << vecPos.x() << "  " << vecPos.y() <<"  "<< self.Dir() << "  " << globalVel.x() << " " << globalVel.y()<<"  "<< rotVel << std::endl;
	}

    if(NOT_MOVE)
		return pCmdFactory->newCommand(CPlayerSpeedV2(vecNumber, 0, 0, 0, dribblePower));
	else
		return pCmdFactory->newCommand(CPlayerSpeedV2(vecNumber, localVel.x(), localVel.y(), rotVel, dribblePower));
}

PlayerCapabilityT CGotoPosition::setCapability(const CVisionModule *pVision) {
	const int vecNumber = task().executor;
	const bool isGoalie = (vecNumber == TaskMediator::Instance()->goalie());
	const bool isBack = (vecNumber == TaskMediator::Instance()->leftBack()) ||
		(vecNumber == TaskMediator::Instance()->rightBack()) ||
		(vecNumber == TaskMediator::Instance()->singleBack()) ||
		(vecNumber == TaskMediator::Instance()->sideBack()) ||
		(vecNumber == TaskMediator::Instance()->defendMiddle());

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
		|| TaskMediator::Instance()->sideBack() != 0 && vecNumber == TaskMediator::Instance()->sideBack()) {
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
		if (isGoalie || isBack)
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
