#include "Rush.h"
#include "SmartGotoPosition.h"
#include "skill/Factory.h"
#include <utils.h>
#include <TaskMediator.h>
#include <GDebugEngine.h>
#include <WorldModel/RobotCapability.h>
#include <CommandFactory.h>
#include <MotionControl/ControlModel.h>
#include <iostream>
#include <PathPlan/RRTPathPlannerNew.h>

namespace {
    bool verBos = false;
	bool DRAW_PATH = false;
	bool DRAW_OBS = false;

	// 底层运动控制参数 ： 默认增大平动的控制性能
	double MAX_TRANSLATION_SPEED = 400;
	double MAX_TRANSLATION_ACC = 400;
	double MAX_ROTATION_SPEED = 15;
	double MAX_ROTATION_ACC = 15;
	double MAX_TRANSLATION_DEC = 400;

	enum Rush_State {
		GetBall = 1,
		Turn,
		Check,
		Rush_Start,
		Rush_Stop,
		End,
	};
}
using namespace Param::Vehicle::V2;

CRush::CRush()
{
	_lastCycle = 0;
}
// 调试信息显示
void CRush::toStream(std::ostream& os) const
{
	os << "Rush to " << task().player.pos;
}

/// 规划接口
void CRush::plan(const CVisionModule* pVision)
{
	if (pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1) {
		setState(BEGINNING);
		cnt = 0;
	}

	GDebugEngine::Instance()->gui_debug_x(old_pos, COLOR_ORANGE);
	playerFlag = task().player.flag;
	const int vecNumber = task().executor;
	CGeoPoint TargetPos = task().player.pos;

	// 接入视觉信息
	const PlayerVisionT& self = pVision->OurPlayer(vecNumber);
	CGeoPoint myPos = self.Pos();
	CGeoPoint ballPos = pVision->Ball().Pos();

	CGeoPoint ReadyPos =ballPos+Utils::Polar2Vector(30,Utils::Normalize((TargetPos-ballPos).dir() + Param::Math::PI));
	double ReadyDir=Utils::Normalize((TargetPos - ballPos).dir());

	//拿球状态判断
	double possession = BallStatus::Instance()->getBallPossession(true, vecNumber);

	int new_state = state(), old_state = state();
    do {
        old_state = new_state;

        switch (old_state) {
        case BEGINNING:
            new_state = GetBall;
            break;

		case GetBall:
			if (possession > 0.9) {
				if ((TargetPos - ballPos).mod() < 50) {
					new_state = End;
					cnt = 0;
				}
				else {
					new_state = Turn;
					cnt = 0;
				}
			}
			cnt++;
			break;
		case Turn:
			if (fabs(Utils::Normalize((TargetPos - ballPos).dir() - (ballPos - myPos).dir())) < Param::Math::PI / 36) {
				new_state = Rush_Start;
				cnt = 0;
			}
			else if (cnt > 100) {
				new_state = Check;
				cnt = 0;
			}
			cnt++;
			break;
		case Check:
			if ((ballPos - myPos).mod() > 10) {
				new_state = GetBall;
				cnt = 0;
			}
			cnt++;
			break;
        case Rush_Start:
			if ((ballPos - myPos).mod() > 50) {
				new_state = GetBall;
				cnt = 0;
			}
			else if ((ballPos - old_pos).mod() > 50) {
				new_state = Rush_Stop;
				cnt = 0;
			}
			else if(fabs(Utils::Normalize((ballPos - myPos).dir() - (TargetPos - ballPos).dir())) > Param::Math::PI / 2) {
				new_state = GetBall;
				cnt = 0;
			}
			cnt++;
            break;
        case Rush_Stop:
			if ((TargetPos - ballPos).mod() < 50) {
				new_state = GetBall;
				cnt = 0;
			}
			else if (cnt > 25) {
				old_pos = ballPos;
				new_state = Rush_Start;
				cnt = 0;
			}
			cnt++;
            break;
        case End:
			if ((TargetPos - ballPos).mod() > 50) {
				new_state = BEGINNING;
				cnt = 0;
			}
			cnt++;
            break;
        default:
            new_state = BEGINNING;
            break;
        }
    } while (false);

	setState(new_state);
    TaskT rushTask(task());

    switch (state()) {
	case GetBall:
	{	
		setSubTask(PlayerRole::makeItNoneTrajGetBall(vecNumber, (TargetPos-ballPos).dir(), CVector(0, 0), PlayerStatus::DRIBBLING));
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -200), "GetBall");
	}
	break;

	case Turn:
	{
		setSubTask(PlayerRole::makeItSimpleGoto(vecNumber, myPos, (TargetPos - ballPos).dir(), CVector(0, 0), 0, PlayerStatus::DRIBBLING));
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -200), "Turn");
	}
	break;

	case Check:
	{
		CGeoPoint checkPos=myPos+Utils::Polar2Vector(5,Utils::Normalize((TargetPos - ballPos).dir() + Param::Math::PI));
		setSubTask(PlayerRole::makeItSimpleGoto(vecNumber, checkPos, (TargetPos - ballPos).dir(), CVector(0, 0), 0));
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -200), "Check");
	}
	break;

    case Rush_Start:
    {
		CGeoPoint rushPos = calc_point(pVision, vecNumber, TargetPos);
		GDebugEngine::Instance()->gui_debug_x(rushPos, COLOR_GREEN);
		CVector vec_1 = (TargetPos - ballPos) / (TargetPos - ballPos).mod() * 3;
		CVector vec_2 = (ballPos - myPos) / (ballPos - myPos).mod();
		double rushDir = (vec_1 + vec_2).dir();
		rushTask.player.pos = rushPos;
		rushTask.player.angle = rushDir;
		rushTask.player.vel = CVector(0, 0);
		rushTask.player.rotvel = 0;
		rushTask.player.max_acceleration = MAX_TRANSLATION_ACC;
		rushTask.player.max_deceleration = MAX_TRANSLATION_DEC;
		rushTask.player.max_speed = MAX_TRANSLATION_SPEED;
		rushTask.player.max_rot_acceleration = MAX_ROTATION_ACC;
		rushTask.player.max_rot_speed = MAX_ROTATION_SPEED;

		setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(rushTask));
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -200), "Rush_Start");
    }
    break;

    case Rush_Stop:
    {
		CGeoPoint rushPos = myPos+ Utils::Polar2Vector(3,Utils::Normalize((TargetPos-myPos).dir()));
		GDebugEngine::Instance()->gui_debug_x(rushPos, COLOR_GREEN);
		CVector vec_1 = (TargetPos - ballPos) / (TargetPos - ballPos).mod() * 3;
		CVector vec_2 = (ballPos - myPos) / (ballPos - myPos).mod();
		double rushDir = (vec_1 + vec_2).dir();
		rushTask.player.pos = rushPos;
		rushTask.player.angle = rushDir;
		rushTask.player.vel = CVector(0, 0);
		rushTask.player.rotvel = 0;
		rushTask.player.max_acceleration = MAX_TRANSLATION_ACC;
		rushTask.player.max_deceleration = MAX_TRANSLATION_DEC;
		rushTask.player.max_speed = MAX_TRANSLATION_SPEED;
		rushTask.player.max_rot_acceleration = MAX_ROTATION_ACC;
		rushTask.player.max_rot_speed = MAX_ROTATION_SPEED;
		rushTask.player.flag = PlayerStatus::DODGE_BALL;

		setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(rushTask));
		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -200), "Rush_Stop");
    }
    break;

    case End:
    {
		rushTask.player.pos = TargetPos;
		rushTask.player.angle = (TargetPos-myPos).dir();
		rushTask.player.vel = CVector(0, 0);
		rushTask.player.rotvel = 0;
		rushTask.player.max_acceleration = MAX_TRANSLATION_ACC;
		rushTask.player.max_deceleration = MAX_TRANSLATION_DEC;
		rushTask.player.max_speed = MAX_TRANSLATION_SPEED;
		rushTask.player.max_rot_acceleration = MAX_ROTATION_ACC;
		rushTask.player.max_rot_speed = MAX_ROTATION_SPEED;
		rushTask.player.flag = PlayerStatus::DRIBBLING;

		setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(rushTask));

		GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, -200), "End");
    }
    break;
    default:
        break;
    }

    _lastCycle = pVision->Cycle();

    CPlayerTask::plan(pVision);
}

CPlayerCommand* CRush::execute(const CVisionModule* pVision)
{
	if (_directCommand) {
		return _directCommand;
	}

	if (subTask()) {
		return subTask()->execute(pVision);
	}

	return NULL;
}

CGeoPoint CRush::calc_point(const CVisionModule* pVision, const int vecNumber, const CGeoPoint TargetPos)
{
	const PlayerVisionT& self = pVision->OurPlayer(vecNumber);
	CGeoPoint myPos = self.Pos();
	CGeoPoint ballPos = pVision->Ball().Pos();
	
	CVector vec_1 = (TargetPos - ballPos) / (TargetPos - ballPos).mod() * 3;
	CVector vec_2 = (ballPos - myPos) / (ballPos - myPos).mod();
	double dir = (vec_1+vec_2).dir();
	double dist = 50 - (ballPos - myPos).mod();
	if ((ballPos - myPos).mod() > 100) {
		dist = -50;
	}
	CGeoPoint point = ballPos + Utils::Polar2Vector(dist, dir);
	if ((ballPos - TargetPos).mod() < 50) {
		point = ballPos + Utils::Polar2Vector((ballPos - TargetPos).mod(), dir);
	}

	return point;
}