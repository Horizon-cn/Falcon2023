#include "Global.h"

CVisionModule*   vision;
CKickStatus*    kickStatus;
CDribbleStatus* dribbleStatus;
CGDebugEngine*  debugEngine;
CWorldModel*	world;
CKickDirection* kickDirection;
CGPUBestAlgThread* bestAlg;
CDefPos2015* defPos2015;
CDefPos2013* defPos2013;
CGuardPos* guardPos;
CSidePos* sidePos;
CIndirectDefender* indirectDefender;
CTandemPos* tandemPos;
CBestPlayer* bestPlayer;
CDefenceInfo* defenceInfo;
CDefenceInfoNew* defenceInfoNew;
CChipBallJudge* chipBallJudge;
CSupportPos* supportPos;
CSupportPos2022* supportPos2022;
CParamManagerSkill* paramManager;
ParamManagerOwl* oParamManager;
ParamManagerCfg* cParamManager;
ParamManagerVision* vParamManager;
ParamManagerSimulator* sParamManager;
CRobotSensor* robotSensor;

void initializeSingleton()
{
	paramManager    = ParamManager::Instance();
	oParamManager   = OParamManager::Instance();
	cParamManager   = CParamManager::Instance();
	vParamManager   = VParamManager::Instance();
	sParamManager   = SParamManager::Instance();
	vision			= VisionModule::Instance();
    kickStatus		= KickStatus::Instance();
	dribbleStatus	= DribbleStatus::Instance();
    debugEngine		= GDebugEngine::Instance();
    world			= WorldModel::Instance();
	kickDirection	= KickDirection::Instance();
	bestAlg			= GPUBestAlgThread::Instance();
	supportPos		= SupportPos::Instance();
	supportPos2022  = SupportPos2022::Instance();
	defPos2015		= DefPos2015::Instance();
	guardPos        = GuardPos::Instance();
	sidePos			= SidePos::Instance();
	defPos2013		= DefPos2013::Instance();
	bestPlayer		= BestPlayer::Instance();
	defenceInfo		= DefenceInfo::Instance();
	defenceInfoNew  = DefenceInfoNew::Instance();
	tandemPos		= TandemPos::Instance();
	chipBallJudge	= ChipBallJudge::Instance();
	indirectDefender= IndirectDefender::Instance();
	robotSensor		= RobotSensor::Instance();
}
