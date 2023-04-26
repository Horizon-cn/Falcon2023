// Time-stamp: <14:27:11  10-13-2009>

#include <Vision/VisionModule.h>
#include <WorldModel/WorldModel.h>
#include <utils.h>
#include <playmode.h>
#include <WorldModel/DribbleStatus.h>
#include <TaskMediator.h>
#include <BestPlayer.h>

#include <fstream>
#include <RobotSensor.h>
#include <GDebugEngine.h>
#include <BallStatus.h>
#include <BallSpeedModel.h>
#include "bayes/MatchState.h"
#include "defence/DefenceInfo.h"
#include "Semaphore.h"
Semaphore vision_to_decision(0);
Semaphore vision_to_cuda(0);
///
/// @file   VisionModule.cpp
/// @author Yonghai Wu <liunian@zju.edu.cn>
/// @date   Tue Oct 13 14:26:36 2009
/// 
/// @brief  视觉预处理，包括滤波，预测等等
/// 
/// 
///
extern bool IS_SIMULATION; // 是否仿真

namespace {
	bool VERBOSE_MODE = false; // 输出信息
	bool PENALTY_FIGHT = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn	CVisionModule::CVisionModule(const COptionModule* pOption) : _pOption(pOption),
/// 	_timeCycle(0), _lastTimeCycle(0),  _ballKicked(false),
/// 	_ballInvalidMovedCycle(0),_chipkickDist(0.0),_kickerDir(0.0)
///
/// @brief	Constructor. 
///
/// @author	Yonghai Wu
/// @date	2009-10-13
///
/// @param	pOption	If non-null, the option. 
////////////////////////////////////////////////////////////////////////////////////////////////////

CVisionModule::CVisionModule() 
:_timeCycle(0), _lastTimeCycle(0), _ballKicked(false), _ourGoalie(0), _theirGoalie(-1), _theirGoalieStrategyNum(0)
{	
	WorldModel::Instance()->registerVision(this);
	{
        PENALTY_FIGHT = ParamManager::Instance()->PENALTY_FIGHT;
	}


	for (int i=0; i < Param::Field::MAX_PLAYER; i++){
		//恢复初始化对方车预测为能识别角度信息
		_theirPlayerPredictor[i].setIsHasRotation(false);
	}

	_theirPenaltyNum = 0;
	_ballVelChangeCouter = false;
}


void CVisionModule::registerOption(const COptionModule* pOption)
{
	_pOption = pOption;
	_gameState.init(pOption->MyColor());
    _next_gameState.init(pOption->MyColor());
}

CVisionModule::~CVisionModule(void)
{

}


void CVisionModule::SetRefRecvMsg(const GameInfoT msg)
{
	const bool invert = !(_pOption->MySide() == Param::Field::POS_SIDE_LEFT);
	const int invertFactor = invert ? -1 : 1;
	if (_pOption->MyColor() == TEAM_BLUE) {
		_ourGoal = msg.refMsg.blueGoal;
		_theirGoal = msg.refMsg.yellowGoal;
		_ourGoalie = msg.refMsg.blueGoalie;
		_theirGoalie = msg.refMsg.yellowGoalie;
	}
	else {
		_ourGoal = msg.refMsg.yellowGoal;
		_theirGoal = msg.refMsg.blueGoal;
		_ourGoalie = msg.refMsg.yellowGoalie;
		_theirGoalie = msg.refMsg.blueGoalie;
	}
	_ballPlacementPosition.setX(invertFactor * msg.refMsg.ballPlacement.x);
	_ballPlacementPosition.setY(invertFactor * msg.refMsg.ballPlacement.y);
	//std::cout << "ball placement pos is : " << _ballPlacementPosition << std::endl;
}

void CVisionModule::SetNewVision(const GameInfoT& vInfo)
{	
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////重要说明，请注意////////////////////////////
	//	定义我方小车位置在左侧，对方车位置在右侧，笛卡尔坐标定义<x y theta>	//
	//	比赛时不管是左边还是右边，对于策略处理而言统一定义为我方在左半场	//
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// 默认我方在球场的左边，切记
	const bool invert = !(_pOption->MySide() == Param::Field::POS_SIDE_LEFT);

	/////////////////////////////////////////////////////////////////////////////
	/// @brief Step 0. 比赛开始时，记录调试信息，辅助调试
	/////////////////////////////////////////////////////////////////////////////
	// 更新当前的时间周期
	SetCycle(vInfo.cycle); 
	
	// 更新新图像数据中的原始球信息
	_lastRawBallPos = _rawBallPos;
	_rawBallPos.SetValid(vInfo.ball.pos.valid);
	// add by zhyaic 2013.6.3 原始的位置应该反向
	const int invertFactor = invert ? -1 : 1;
	_rawBallPos.SetPos(vInfo.ball.pos.x * invertFactor,vInfo.ball.pos.y * invertFactor);
	
	/////////////////////////////////////////////////////////////////////////////
    /// @brief Step 1. 进行球预测,也就是输入当前球的观测进行滤波
    /////////////////////////////////////////////////////////////////////////////
    _ballPredictor.updateVision(vInfo, invert);
	
	//printf("%d\n", RobotCapFactory::Instance()->getRobotCap(0,2)->maxSpeed(0));
	/////////////////////////////////////////////////////////////////////////////
	/// @brief Step 2: 进行我方和对方机器人位置预测，关注滤波器
    /////////////////////////////////////////////////////////////////////////////
	const BallVisionT& thisBall = _ballPredictor.getResult(Cycle());
	// 确定球员的信息是否需要反向，确保正确更新比赛双方球员的信息
	for (int i = 0; i < Param::Field::MAX_PLAYER; ++ i) {
		const VehicleInfoT& ourPlayer = vInfo.player[i];
		const VehicleInfoT& theirPlayer = vInfo.player[i+Param::Field::MAX_PLAYER];
		_ourPlayerPredictor[i].updateVision(vInfo.cycle, ourPlayer, thisBall, invert);
		_theirPlayerPredictor[i].updateVision(vInfo.cycle, theirPlayer, thisBall, invert);
		//GDebugEngine::Instance()->gui_debug_line(OurPlayer(i).Pos(), OurPlayer(i).Pos() + OurPlayer(i).Vel());
	}
	GDebugEngine::Instance()->gui_debug_line(Ball().Pos() , Ball().Pos() + Ball().Vel());

	//【#TODO】更新双方当前在场上的球员数量，我方排除门将，对方全部
	CheckBothSidePlayerNum();

    /////////////////////////////////////////////////////////////////////////////
	/// @brief Step 3: 更新双向通讯的数据，仅针对实物模式
    /////////////////////////////////////////////////////////////////////////////
    RobotSensor::Instance()->Update(this->Cycle());
	
	judgeBallVelStable();

	/////////////////////////////////////////////////////////////////////////////
	/// @brief Step 4: 更新与决策相关部分的上层信息
	/////////////////////////////////////////////////////////////////////////////
	// 【#TODO】 球状态模块更新状态, 这部分到时仍需要再细致调试下
	BallStatus::Instance()->UpdateBallStatus(this);

	// 【#TODO】 更新敌我双方对于球的势能，越小越有利于拿球，贝叶斯滤波中有使用
	BestPlayer::Instance()->update(this); 
	
	// 【#TODO】 更新贝叶斯滤波器，评估目前比赛攻防形式
	// MatchState::Instance()->update();

	DefenceInfo::Instance()->updateDefenceInfo(this);

	/////////////////////////////////////////////////////////////////////////////
	/// @brief Step 5: 更新裁判盒信息 及处理球数据相关的特殊情况
	/////////////////////////////////////////////////////////////////////////////
	CheckKickoffStatus(vInfo);
	int ref_mode = vInfo.mode;
    int next_ref_mode = vInfo.next_mode;
	// 更新裁判盒信息，一般当且仅当比赛模式为停球状态时，判断球是否被踢出
    if (ref_mode >= PMStop && ref_mode < PMNone) {
        _gameState.transition(playModePair[ref_mode].ch, _ballKicked);
        _next_gameState.transition(playModePair[next_ref_mode].ch, _ballKicked);
	}

	//更新裁判盒信息
	UpdateRefereeMsg();

	// 特殊情况一
	// 一些特殊比赛状态下，对于球的特殊处理，与场地的尺寸参数相关
	// 一般要求球看不到才予以处理
    /**if (!IS_SIMULATION) {
		if (_gameState.kickoff()) {				// 开球时
			if (!Ball().Valid() || Ball().Pos().dist(CGeoPoint(0,0)) > 20) {
				_ballPredictor.setPos(Cycle(),CGeoPoint(0,0));
				_ballPredictor.setVel(Cycle(),CVector(0,0));
			}
		}
		double penaltyX = Param::Field::PENALTY_MARK_X;

		if (!PENALTY_FIGHT) {
			if (_gameState.ourPenaltyKick()) {		// 我方点球时
				if (!Ball().Valid() || Ball().Pos().dist(CGeoPoint(penaltyX,0)) > 20) {
					_ballPredictor.setPos(Cycle(),CGeoPoint(penaltyX,0));
					_ballPredictor.setVel(Cycle(),CVector(0,0));
				}
			}

			if (_gameState.theirPenaltyKick()) {	// 对方点球时
				if (!Ball().Valid() || Ball().Pos().dist(CGeoPoint(-penaltyX,0)) > 20) {
					_ballPredictor.setPos(CGeoPoint(-penaltyX,0));
					_ballPredictor.setVel(Cycle(),CVector(0,0));
				}
			}
		}
    }**/
    /**
	// 特殊情况二：
	// 红外有信息，若球没看到，则予以位置修正，球若看到则检查红外信号，用以替换owl2中的处理 zyj
	bool sensorBall = false;
	double ball_size = 2.15;
	double minDist2Ball = 50; //Param::Vehicle::V2::PLAYER_SIZE + ball_size + 5; //cm
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (RobotSensor::Instance()->IsInfoValid(i) && RobotSensor::Instance()->IsInfraredOn(i)) {
            sensorBall = true;
			if (Ball().Valid()) {	// 球看到，作红外信号假象检查，因为通讯可能会丢
				if (Ball().Pos().dist(OurPlayer(i).Pos()) > Param::Vehicle::V2::PLAYER_SIZE + ball_size + 5) {
                    RobotSensor::Instance()->ResetInraredOn(i);
                    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-600, -450), QString("Infrared Reset").arg(i).toLatin1());
				}
			}
			else {	// 球看不到，根据红外信号纠正球的位置，如果有多辆车，选择上一帧最近的，若上一帧球车相距较远，则认为红外故障
                if (_lastRawBallPos.Pos().dist(OurPlayer(i).Pos()) < minDist2Ball) {
					minDist2Ball = _lastRawBallPos.Pos().dist(OurPlayer(i).Pos());
					_ballPredictor.setPos(OurPlayer(i).Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_SIZE + ball_size, OurPlayer(i).Dir()));
					_ballPredictor.setVel(Cycle(), CVector(0, 0)); //OurPlayer(i).Vel()
                    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-600, -450), QString("Infrared Fix").arg(i).toLatin1());
				}
			}
		}
    }**//**
    double ball_size = 2.15;
	bool sensorBall = false;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i ++) {
		if (RobotSensor::Instance()->IsInfoValid(i) && RobotSensor::Instance()->IsInfraredOn(i)) {
			sensorBall = true;
			if (Ball().Valid()) {	// 球看到，作红外信号假象检查，因为通讯可能会丢
				if (Ball().Pos().dist(OurPlayer(i).Pos()) > Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE + 5) {
					RobotSensor::Instance()->ResetInraredOn(i);
				}
			} else {				// 球看不到，根据红外信号纠正球的位置
                _ballPredictor.setPos(OurPlayer(i).Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_SIZE + ball_size,OurPlayer(i).Dir()));
                _ballPredictor.setVel(Cycle(), OurPlayer(i).Vel());
			}

			break;
		}
	}**/
	/////////////////////////////////////////////////////////////////////////////
	/// @brief Step 7: 向调试面板中显示一些必要的信息
	/////////////////////////////////////////////////////////////////////////////

	// 输出当前球的预测位置 ： 忽略球是否在场上
	// GDebugEngine::Instance()->gui_debug_x(this->Ball().Pos(),COLOR_RED);
	// 输出当前球的预测速度 并 输出数值直观显示
	// GDebugEngine::Instance()->gui_debug_line(this->Ball().Pos(),BallSpeedModel::Instance()->posForTime(20,this),COLOR_ORANGE);

	// 输出我方小车的预测位置 : 忽略车是否在场上
	// for (int i = 0; i < Param::Field::MAX_PLAYER; i ++) {
	// 	GDebugEngine::Instance()->gui_debug_robot(OurPlayer(i).Pos(), OurPlayer(i).Dir());
	// }
	// 输出我方小车的红外信号
	// if (sensorBall) {
		//qDebug() << "received infrared";
	// 	 GDebugEngine::Instance()->gui_debug_arc(Ball().Pos(), 6*Param::Field::BALL_SIZE, 0, 360, COLOR_PURPLE);
	// 	 GDebugEngine::Instance()->gui_debug_arc(Ball().Pos(), 3*Param::Field::BALL_SIZE, 0, 360, COLOR_PURPLE);
	// }
	vision_to_decision.Signal();
	vision_to_cuda.Signal();
	return ;
}

void CVisionModule::CheckKickoffStatus(const GameInfoT& info)
{
	if (_gameState.canEitherKickBall()) {	// 若允许去踢球
		if (! _ballKicked ){	// 球没有被判断为踢出
			if (gameState().ourRestart()) {
				const double OUR_BALL_KICKEDBUFFER = 5 + 3;	
				const CVector ballMoved = Ball().Pos() - _ballPosSinceNotKicked;
				if( ballMoved.mod2() > OUR_BALL_KICKEDBUFFER * OUR_BALL_KICKEDBUFFER ){
					_ballKicked = true;
				}
			} else {
				CBestPlayer::PlayerList theirList =  BestPlayer::Instance()->theirFastestPlayerToBallList();
				if (theirList.empty()) {
					_ballKicked = false;
				} else {
					const double THEIR_BALL_KICKED_BUFFER = 5 + 5;
					const CVector ballMoved = Ball().Pos() - _ballPosSinceNotKicked;
					if( ballMoved.mod2() > THEIR_BALL_KICKED_BUFFER * THEIR_BALL_KICKED_BUFFER ){
						_ballKicked = true;
					}
				}
			}
				
		}
	} else {					// 球已经被判断为踢出
		_ballKicked = false;
		_ballPosSinceNotKicked = Ball().Pos();
	}

	return ;
}

void CVisionModule::CheckBothSidePlayerNum()
{
	// 统计我方实际在场上的小车个数
	_validNum = 0;
	int tempGoalieNum = TaskMediator::Instance()->goalie();
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (OurPlayer(i).Valid() && i != tempGoalieNum) {
			_validNum++;
		}
	}
	_validNum = _validNum>(Param::Field::MAX_PLAYER)?(Param::Field::MAX_PLAYER):_validNum;

	// 统计对方实际在场上的小车个数
	_TheirValidNum = 0;
	for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
		if (TheirPlayer(i).Valid()) {
			_TheirValidNum ++;
		}
	}
	_TheirValidNum = _TheirValidNum > Param::Field::MAX_PLAYER ? Param::Field::MAX_PLAYER : _TheirValidNum;

//    if (_theirGoalie >=0 && _theirGoalie < Param::Field::MAX_PLAYER) return;
//    if (_theirGoalie >=0 && _theirGoalie < Param::Field::MAX_PLAYER && !Utils::InTheirPenaltyArea(TheirPlayer(_theirGoalie).Pos(),0))
//        return;	
	int dist = 1000;
    int tempTheirGoalie=_theirGoalie;
    for(int i=0;i<Param::Field::MAX_PLAYER;i++)
    {
        double d = TheirPlayer(i).Pos().dist(CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0));
        if(d<dist)
        {
            dist=d;
            tempTheirGoalie=i;
        }
    }
    if(Utils::InTheirPenaltyArea(TheirPlayer(tempTheirGoalie).Pos(),0) && !Utils::InTheirPenaltyArea(TheirPlayer(_theirGoalie).Pos(),0))
    {
        _theirGoalie = tempTheirGoalie;
    }

	return;
}

void CVisionModule::SetPlayerCommand(int num, const CPlayerCommand* pCmd)
{
	_ourPlayerPredictor[num].updateCommand(Cycle(), pCmd);
	CDribbleStatus* dribbleStatus = DribbleStatus::Instance();
	if( pCmd->dribble() ){
		dribbleStatus->setDribbleOn(pCmd->number(), Cycle(), Ball().Pos());
		GDebugEngine::Instance()->gui_debug_arc(Ball().Pos(), 10, 0, 360, COLOR_PURPLE);
	}else{
		dribbleStatus->setDribbleOff(pCmd->number());
	}

	return ;
}

void CVisionModule::UpdateRefereeMsg()
{
	if (_lastRefereeMsg != _refereeMsg && _refereeMsg == "theirPenaltyKick") { // 记录当前是对方第几个点球
		_theirPenaltyNum++;
	}

	_lastRefereeMsg=_refereeMsg;
	if (! _gameState.canMove()) {
		_refereeMsg = "gameHalt";
	} else if( _gameState.gameOver()/* || _pVision->gameState().isOurTimeout() */){
		_refereeMsg = "gameOver";
	} else if( _gameState.isOurTimeout() ){
		_refereeMsg = "ourTimeout";
	} else if (_gameState.isTheirTimeout()) {
		_refereeMsg = "gameHalt";
	} else if(!_gameState.allowedNearBall()){
		// 对方发球
		if(_gameState.theirIndirectKick()){
			_refereeMsg = "theirIndirectKick";
		} else if (_gameState.theirDirectKick()){
			_refereeMsg = "theirIndirectKick";
		} else if (_gameState.theirKickoff()){
			_refereeMsg = "theirKickOff";
		} else if (_gameState.theirPenaltyKick()){
			_refereeMsg = "theirPenaltyKick";
		} else if (_gameState.theirBallPlacement()) {
			_refereeMsg = "theirBallPlacement";
			GDebugEngine::Instance()->gui_debug_x(_ballPlacementPosition, COLOR_YELLOW);
			GDebugEngine::Instance()->gui_debug_msg(_ballPlacementPosition, "BP_Point", COLOR_WHITE);
			GDebugEngine::Instance()->gui_debug_arc(_ballPlacementPosition, 15, 0, 360, COLOR_WHITE);
        } else {
            //if (_next_gameState.theirIndirectKick() || _next_gameState.theirDirectKick())
            //    _refereeMsg = "theirIndirectKick";
            //else
                _refereeMsg = "gameStop";
		}
	} else if( _gameState.ourRestart()){
		if( _gameState.ourKickoff() ) {
			_refereeMsg = "ourKickOff";
		} else if(_gameState.penaltyKick()){
			_refereeMsg = "ourPenaltyKick";
		} else if(_gameState.ourIndirectKick()){
			_refereeMsg = "ourIndirectKick";
		} else if(_gameState.ourDirectKick()){
			_refereeMsg = "ourIndirectKick";
		}
	} else if (_gameState.ourBallPlacement()) {
			_refereeMsg = "ourBallPlacement";
			GDebugEngine::Instance()->gui_debug_x(_ballPlacementPosition, COLOR_YELLOW);
			GDebugEngine::Instance()->gui_debug_msg(_ballPlacementPosition, "BP_Point", COLOR_WHITE);
			GDebugEngine::Instance()->gui_debug_arc(_ballPlacementPosition, 15, 0, 360, COLOR_WHITE);
	} else {
		_refereeMsg ="";
	}
}

const string CVisionModule::GetCurrentRefereeMsg() const{
	return _refereeMsg;
}

const string CVisionModule::GetLastRefereeMsg() const{
	return _lastRefereeMsg;
}


void CVisionModule::judgeBallVelStable(){
	if (ballVelValid())
	{
		if (fabs(Utils::Normalize(this->Ball().Vel().dir()-this->Ball(_lastTimeCycle-2).Vel().dir()))>Param::Math::PI*10/180 && this->Ball().Vel().mod()>20)
		{
			_ballVelChangeCouter++;
			_ballVelChangeCouter=min(_ballVelChangeCouter,4);
		}else{
			_ballVelChangeCouter--;
			_ballVelChangeCouter=max(_ballVelChangeCouter,0);
		}
		if (_ballVelChangeCouter>=3){
			_ballVelDirChanged=true;		
		}
		if (_ballVelChangeCouter==0)
		{
			_ballVelDirChanged=false;
		}
	}

}

bool CVisionModule::ballVelValid(){
	if (!_rawBallPos.Valid() || fabs(_rawBallPos.X() - _lastRawBallPos.X())<0.0000000001 )
	{
		return false;
	}else{
		return true;
	}
}
