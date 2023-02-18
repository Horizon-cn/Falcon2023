#include <iostream>
#include <WorldModel/WorldModel.h>
#include "DecisionModule.h"
#include "ActionModule.h"
#include <CtrlBreakHandler.h>
#include <GDebugEngine.h>
#include "bayes/MatchState.h"
#include "gpuBestAlgThread.h"
#include "Global.h"
#include "DefendUtils.h"
#include "Compensate.h"
#include "zss_debug.pb.h"
#include "referee.pb.h"
#include "src_cmd.pb.h"
#include "src_rawvision.pb.h"
#include "Vision/DataReceiver4rbk.h"
#include <thread>
#include <QCoreApplication>
#include <ParamManagerNew.h>
#include <QDir>
#include "RobotSensor.h"

//#ifdef WIN32
//#include <windows.h>
//#endif // WIN32

ZSS::Protocol::Debug_Msgs guiDebugMsgs;

//extern CEvent *visionEvent;
QMutex* _best_visiondata_copy_mutex = 0;
QMutex* _value_getter_mutex = 0;
QMutex* _debug_mutex = 0;
bool IS_SIMULATION = false;
bool VERBOSE_MODE = false;

//HANDLE _vision_event;

void run(){
    IS_SIMULATION = OParamManager::Instance()->isSimulation;
    qDebug() << "IS_SIMULATION : " << IS_SIMULATION;
    //_vision_event = CreateEvent(NULL, TRUE, FALSE, NULL);
    initializeSingleton(); // init parammanager first
    CCtrlBreakHandler breakHandler;
    // SLEEP(1000);
    COptionModule option; // right or left, yellow or blue
	vision->registerOption(&option);
	WORLD_MODEL->registerVision(vision);
	WORLD_MODEL->registerOption(&option);
	CDecisionModule decision(&option, vision);
	CActionModule action(&option, vision, &decision);
	MATCH_STATE->initialize(&option,vision);

    _best_visiondata_copy_mutex = new QMutex;
    _value_getter_mutex = new QMutex;
    _debug_mutex = new QMutex;
	GPUBestAlgThread::Instance()->initialize(VISION_MODULE);
	GameInfoT gameInfo;
    DataReceiver4rbk::Instance();
    RobotSensor::Instance();
    //SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
    
	while (true) {
        //WaitForSingleObject(_vision_event, INFINITY);

		if (! DataReceiver4rbk::Instance()->getGameInfo(&option,gameInfo)) {
			continue;
		}
        
        vision->SetRefRecvMsg(gameInfo);
        vision->SetNewVision(gameInfo);
		
        if (breakHandler.halted()){
            decision.DoDecision(true);
            action.sendNoAction(gameInfo);
        } else {
			decision.DoDecision(false);
			action.sendAction(gameInfo);
        }

        GDebugEngine::Instance()->send(option.MyColor() == TEAM_BLUE);
		guiDebugMsgs.Clear();
	}
}

int main(int argc, char* argv[]) {
    qDebug() << QDir::currentPath();
    //SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
    QCoreApplication a(argc, argv);
//    OParamManager::Instance()->setFileName();
    OParamManager::Instance()->update();
//    CParamManager::Instance()->setFileName();
    CParamManager::Instance()->update();
//    VParamManager::Instance()->setFileName();
//    SParamManager::Instance()->setFileName();
//    ParamManager::Instance()->setFileName();
    ParamManager::Instance()->update();
    std::thread t(run);
    t.detach();
    return a.exec();
}
