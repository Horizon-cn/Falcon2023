#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "Vision/VisionModule.h"
#include "WorldModel/DribbleStatus.h"
#include "WorldModel/KickStatus.h"
#include "GDebugEngine.h"
#include "WorldModel/WorldModel.h"
#include "singleton.h"
#include "KickDirection.h"
#include "PointCalculation/DefPos2015.h"
#include "PointCalculation/DefPos2013.h"
#include "PointCalculation/TandemPos.h"
#include "PointCalculation/ChipBallJudge.h"
#include "gpuBestAlgThread.h"
#include "BestPlayer.h"
#include "defence/DefenceInfo.h"
#include "PointCalculation/IndirectDefender.h"
#include "PointCalculation/SupportPos.h"
#include "PointCalculation/GuardPos.h"
#include "ParamManagerNew.h"
#include "PointCalculation/SupportPos2022.h"

extern CParamManagerNew* paramManager;
extern CVisionModule*  vision;
extern CKickStatus*    kickStatus;
extern CDribbleStatus* dribbleStatus;
extern CGDebugEngine*  debugEngine;
extern CWorldModel*	   world;
extern CKickDirection* kickDirection;
extern CGPUBestAlgThread* bestAlg;
extern CDefPos2015* defPos2015;
extern CGuardPos* guardPos;
extern CDefPos2013* defPos2013;
extern CTandemPos* tandemPos;
extern CBestPlayer* bestPlayer;
extern CDefenceInfo* defenceInfo;
extern CChipBallJudge* chipBallJudge;
extern CIndirectDefender* indirectDefender;
extern CSupportPos* supportPos;
extern CSupportPos2022* supportPos2022;
void initializeSingleton();
#endif