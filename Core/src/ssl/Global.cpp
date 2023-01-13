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
CIndirectDefender* indirectDefender;
CTandemPos* tandemPos;
CBestPlayer* bestPlayer;
CDefenceInfo* defenceInfo;
CChipBallJudge* chipBallJudge;
CSupportPos* supportPos;
CSupportPos2022* supportPos2022;
CParamManagerSkill* paramManager;
ParamManagerOwl* oParamManager;
ParamManagerCfg* cParamManager;

void initializeSingleton()
{
	paramManager    = ParamManager::Instance();
	oParamManager   = OParamManager::Instance();
	cParamManager   = CParamManager::Instance();
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
	defPos2013		= DefPos2013::Instance();
	bestPlayer		= BestPlayer::Instance();
	defenceInfo		= DefenceInfo::Instance();
	tandemPos		= TandemPos::Instance();
	chipBallJudge	= ChipBallJudge::Instance();
	indirectDefender= IndirectDefender::Instance();
}
