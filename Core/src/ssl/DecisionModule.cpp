/************************************************************************/
/* Copyright (c) CSC-RL, Zhejiang University							*/
/* Team:			SSL-ZJUNlict										*/
/* HomePage: http://www.nlict.zju.edu.cn/ssl/WelcomePage.html			*/
/************************************************************************/
/* File:	DecisionModule.h											*/
/* Brief:	C++ Implementation: Decision	execution					*/
/* Func:	Provide a decision interface for Strategy, Play selecting	*/
/* Author:	cliffyin, 2012, 08											*/
/* Refer:	NONE														*/
/* E-mail:	cliffyin007@gmail.com										*/
/************************************************************************/

#include "DecisionModule.h"
//#include <skill/Factory.h>
#include <TaskMediator.h>
#include <QDir>
#include "LuaModule.h"
#include "Semaphore.h"
extern Semaphore vision_to_decision;
Semaphore decision_to_action(0);
namespace {
	/// 是否状态化的策略库
	bool USE_LUA_SCRIPTS = true;
}

CDecisionModule::CDecisionModule(const COptionModule* pOption, CVisionModule* pVision): _pOption(pOption),_pVision(pVision)
{		
		if(USE_LUA_SCRIPTS){
			//LuaModule::Instance()->RunScript("../lua_scripts/test/Init.lua");
			LuaModule::Instance()->RunScript("../lua_scripts/ssl/StartZeus.lua");
		}
}

CDecisionModule::~CDecisionModule(void)
{
	
}

void CDecisionModule::DoDecision(const bool visualStop)
{
	vision_to_decision.Wait();
	/************************************************************************/
	/* 清空上一周期的历史任务                                               */
	/************************************************************************/
	TaskMediator::Instance()->cleanOldTasks();

	/************************************************************************/
	/* 选取合适的Play，进行任务分配                                         */
	/************************************************************************/
    GenerateTasks(visualStop);	
	
	/************************************************************************/
	/* 进行任务的规划，逐次进行子任务的设定                                 */
	/* 每个队员都分配了skill,并对每个skill进行了规划						*/
	/* (除了GotoPosition里的命令计算还没执行,需要在execute时执行)			*/
	/************************************************************************/
	PlanTasks();

	decision_to_action.Signal();
	return ;
}

void CDecisionModule::GenerateTasks(const bool visualStop)
{
	// 图像停止 ： 收不到 或者 暂停接受
	if (visualStop) {
		//// 每辆小车下发停止任务
		//for (int vecNumber = 1; vecNumber <= Param::Field::MAX_PLAYER; ++ vecNumber) {
		//	TaskMediator::Instance()->setPlayerTask(vecNumber, PlayerRole::makeItStop(vecNumber), LowestPriority);
		//}
		return;
	}

	DoTeamMode();
   
	return ;
}

void CDecisionModule::DoTeamMode()
{
	// 两种策略库进行决策规划
	if (USE_LUA_SCRIPTS){
		//LuaModule::Instance()->RunScript("../lua_scripts/test/SelectPlay.lua");
		LuaModule::Instance()->RunScript("../lua_scripts/ssl/SelectPlay.lua");
	} else {
        qDebug()<<"other decision yet to be implemented, plz use lua";
	}
	
	return ;
}

void CDecisionModule::PlanTasks()
{
	/************************************************************************/
	/* 按照task的优先级执行:简单的冒泡排序法                                */
	/************************************************************************/
	// 结构定义
    typedef std::pair< int, int > TaskPair;
    typedef std::vector< TaskPair > TaskPairList;

	// 用于存储队员号及其任务的优先级
    TaskPairList taskPairList;	
	taskPairList.clear();

	// 根据获取到得小车任务，进行优先级排序
    for (int num = 0; num < Param::Field::MAX_PLAYER; ++ num) {
		// TODO 只有场上看得到且被赋予任务的小车才进行优先级排序，是否会存在问题
		if (/*_pVision->OurPlayer(num).Valid() && */TaskMediator::Instance()->getPlayerTask(num)) {
			// 存储所有已经设定好任务的队员,它的skill的priority,用来排序;
			taskPairList.push_back(TaskPair(num, TaskMediator::Instance()->getPlayerTaskPriority(num)));
		}
    }

    if (! taskPairList.empty()) {
		// 冒泡法排序,优先级高的在前
		for (int i = 0; i < taskPairList.size()-1; ++ i) {
			for (int j = i+1; j < taskPairList.size(); ++ j) {
				if (taskPairList[i].second < taskPairList[j].second){
					std::swap(taskPairList[i],taskPairList[j]); // 交换顺序
				}
			}
		}
		
		// 按照任务优先级排序的结果进行相对应的任务规划：主要是子任务的设置
		// 一个问题，针对上面由于图像丢车的情况，会如何处理，是否会不进行对应的任务规划
		for (int i = 0; i < taskPairList.size(); ++ i) {
			// 根据taskPairList中的优先级排序,执行各个skill的plan函数,得到各机器人下一周期的GotoPosition任务(任何skill最终都会归属到该基本skill来)
			// (该任务会在之后ActionModule的sendAction函数通过调用各skill的execute函数而得到执行,
			// 并最终计算出各机器人下一周期的x,y速度,是否控球射门等底层指令)
			TaskMediator::Instance()->getPlayerTask(taskPairList[i].first)->plan(_pVision);
		}
	}

	// TODO 对于没有任务的分配到情况予以打印提示，但先不予以处理
	// 最基本的作法是赋予急停处理的任务 MakeUpTask(num)

	return ;
}
