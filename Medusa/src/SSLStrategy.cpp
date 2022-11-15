#include "SSLStrategy.h"
RBK_INHERIT_SOURCE(SSLStrategy)
#include <iostream>
#include <WorldModel/WorldModel.h>
#include "DecisionModule.h"
#include "ActionModule.h"
#include <tinyxml/ParamReader.h>
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
#include <robokit/core/model.h>
#include <robokit/core/rbk_config.h>
#include <TimeCounter.h>

ZSS::Protocol::Debug_Msgs guiDebugMsgs;
std::string CParamReader::_paramFileName = "zeus2005";

//extern CEvent *visionEvent;
CMutex* _best_visiondata_copy_mutex = 0;
CMutex* _value_getter_mutex = 0;
bool IS_SIMULATION = false;
bool VERBOSE_MODE = false;
CUsecTimer _usecTimer;
CUsecTimer _usecTime2;

HANDLE _vision_event;

SSLStrategy::SSLStrategy(void)
{
	rbk::Config::Instance()->get("simulation", IS_SIMULATION);
}

SSLStrategy::~SSLStrategy(void)
{
}

void SSLStrategy::messageRawVisionCallBack(google::protobuf::Message*)
{
	PulseEvent(_vision_event);
}

void SSLStrategy::run(){
	//std::string value;
	//pParamServer->get("IsReal", value);
	//IS_SIMULATION = value == "0" ? 0 : 1;
	PARAM_READER->readParams();
	_vision_event = CreateEvent(NULL, TRUE, FALSE, NULL);
	initializeSingleton();
	ofstream file;
	CCtrlBreakHandler breakHandler;
	SLEEP(1000);
	COptionModule option; //����������ã�right or left, yellow or blue
	vision->registerOption(&option);
	WORLD_MODEL->registerVision(vision);
	WORLD_MODEL->registerOption(&option);
	CDecisionModule decision(&option, vision);
	CActionModule action(&option, vision, &decision);
	MATCH_STATE->initialize(&option,vision);

	_best_visiondata_copy_mutex = new CMutex;
	_value_getter_mutex = new CMutex;
	GPUBestAlgThread::Instance()->initialize(VISION_MODULE);
	GameInfoT gameInfo;
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	while (true) {
		double usedtime = 0.0f;
		double totalusedtime = 0.0f;
		WaitForSingleObject(_vision_event, INFINITE);

		if (! DataReceiver4rbk::Instance()->getGameInfo(&option,gameInfo)) {
			continue;
		}

		if (VERBOSE_MODE) {
			if (gameInfo.cycle % 2 == 0) {
				_usecTime2.start();
			}
			else {
				_usecTime2.stop();
				LogInfo(" Currrent cycle : " << gameInfo.cycle << " : " << 1000000.0f/_usecTime2.time() << "\n";)
			}
			_usecTimer.start();
			vision->SetRefRecvMsg(gameInfo);
			vision->SetNewVision(gameInfo);

			_usecTimer.stop();

			if (gameInfo.cycle % 10 == 0) {
				usedtime = _usecTimer.time() / 1000.0f;
				totalusedtime += usedtime;
			}
		}
		else {
			vision->SetRefRecvMsg(gameInfo);
			vision->SetNewVision(gameInfo);
		}
		
		if (breakHandler.halted()){
			decision.DoDecision(true);
			action.sendNoAction(gameInfo);
		} else {
			decision.DoDecision(false);
			action.sendAction(gameInfo);
		}

		publishTopic(guiDebugMsgs);
		guiDebugMsgs.Clear();
	}
}
void SSLStrategy::loadFromConfigFile(){

}
void SSLStrategy::setSubscriberCallBack(){
	setTopicCallBack<rbk::protocol::SRC_RawVision>(&SSLStrategy::messageRawVisionCallBack,this);
	createPublisher<ZSS::Protocol::Debug_Msgs>();
	createPublisher<rbk::protocol::SRC_Cmd>();
	setTopicCallBack<SSL_Referee>();
	setTopicCallBack<rbk::protocol::Robots_Status>();
}