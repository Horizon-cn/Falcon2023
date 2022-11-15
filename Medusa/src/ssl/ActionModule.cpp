/************************************************************************/
/* Copyright (c) CSC-RL, Zhejiang University							*/
/* Team:			SSL-ZJUNlict										*/
/* HomePage: http://www.nlict.zju.edu.cn/ssl/WelcomePage.html			*/
/************************************************************************/
/* File:	ActionModule.h												*/
/* Brief:	C++ Implementation: Action	execution						*/
/* Func:	Provide an action command send interface					*/
/* Author:	cliffyin, 2012, 08											*/
/* Refer:	NONE														*/
/* E-mail:	cliffyin007@gmail.com										*/
/************************************************************************/	

#include "SSLStrategy.h"

#include "ActionModule.h"
#include <tinyxml/ParamReader.h>
#include <WorldModel/KickStatus.h>
#include <WorldModel/DribbleStatus.h>
#include <TaskMediator.h>
#include <PlayerCommandV2.h>

#include <CommandFactory.h>
//#include <PathPlan/PathPlanner.h>
#include <BallStatus.h>
#include <robokit/core/rbk_config.h>

CActionModule::CActionModule(const COptionModule* pOption,CVisionModule* pVision,const CDecisionModule* pDecision)
: _pOption(pOption),_pVision(pVision),_pDecision(pDecision)
{
	rbk::Config::Instance()->get("simOppo", isYellow);
	//cmds_socket.bind(cmd_bind_port[(int)isYellow]);
}

CActionModule::~CActionModule(void)
{

}

// 用于当场上有的车号大于5的情况
bool CActionModule::sendAction(const GameInfoT& vInfo)
{
	rbk::protocol::SRC_Cmd cmds;

	/************************************************************************/
	/* 第一步：遍历小车，执行赋予的任务，生成动作指令                       */
	/************************************************************************/
	for (int vecNum = 0; vecNum < Param::Field::MAX_PLAYER; ++ vecNum) {
		rbk::protocol::Message_SSL_Command* ssl_cmd = nullptr;
		// 获取当前小车任务
		CPlayerTask* pTask = TaskMediator::Instance()->getPlayerTask(vecNum);
		// 没有任务，跳过
		if (NULL == pTask) {
			continue;
		}

		// 执行skill，任务层层调用执行，得到最终的指令：<vx vy w> + <kick dribble>
		// 执行的结果：命令接口（仿真-DCom，实物-CommandSender） + 指令记录（运动-Vision，踢控-PlayInterface)
		bool dribble = false;
		CPlayerCommand* pCmd = NULL;
		pCmd = pTask->execute(_pVision); 

		if (!pCmd) {
			std::cout<<"PlayerCommand execute is Null "<<vecNum<<std::endl;
		}
		// 跑：有效的运动指令
		if (pCmd) {
			dribble = pCmd->dribble() > 0;
			// 下发运动 <vx vy w>
			if(ssl_cmd == nullptr){
				ssl_cmd = cmds.add_command();
				//LogInfo("action module number in lua: " << pCmd->number());
				//LogInfo("action module number in real: " << vInfo.player[pCmd->number()].ID);
				ssl_cmd->set_robot_id(vInfo.player[pCmd->number()].ID);
			}
			// for rbk
			//pCmd->execute(IS_SIMULATION, robotIndex[vecNum-1]);
			((CPlayerSpeedV2*)pCmd)->setSpeedtoSSLCmd(ssl_cmd);
			// 记录指令
			_pVision->SetPlayerCommand(pCmd->number(), pCmd);
		}

		// 踢：有效的踢控指令
		double kickPower = 0.0;
		double chipkickDist = 0.0;
		double passdist = 0.0;
		if (KickStatus::Instance()->needKick(vecNum) && pCmd) {
			// 更新踢相关参数
			kickPower = KickStatus::Instance()->getKickPower(vecNum);
			chipkickDist = KickStatus::Instance()->getChipKickDist(vecNum);
			passdist = KickStatus::Instance()->getPassDist(vecNum);
			// 涉及到平/挑射分档，这里只关系相关参数，实际分档请关注 CommandSender
			CPlayerKickV2 kickCmd(vecNum, kickPower, chipkickDist, passdist, dribble);
			// 机构动作 <kick dribble>
			//kickCmd.execute(IS_SIMULATION);
			if(ssl_cmd == nullptr){
				ssl_cmd = cmds.add_command();
				ssl_cmd->set_robot_id(vInfo.player[pCmd->number()].ID);
			}
			kickCmd.setKicktoSSLCmd(ssl_cmd);
		}

		// 记录命令
		//std::cout << "kickPower: " << kickPower << std::endl;
		BallStatus::Instance()->setCommand(vecNum, kickPower, chipkickDist, dribble, _pVision->Cycle());
	}
	
	//sendToOwl(cmds);

	/************************************************************************/
	/* 第二步：指令清空处理                                                 */
	/************************************************************************/
	// 清除上一周期的射门指令
	KickStatus::Instance()->clearAll();
	// 清除上一周期的控球指令
	DribbleStatus::Instance()->clearDribbleCommand();
	//// 清除上一周期的障碍物标记
	//CPathPlanner::resetObstacleMask();

	GRBKHandle::Instance()->publishTopic(cmds);
	return true;
}

bool CActionModule::sendNoAction(const GameInfoT& vInfo)
{
	rbk::protocol::SRC_Cmd cmds;
	//TODO: make num compatible!!!!!!!!2020-11-05!!!!!!!!!!!!!!!!!!!!
	for (int vecNum = 0; vecNum < Param::Field::MAX_PLAYER - 10; ++ vecNum) {
		// 生成停止命令
		CPlayerCommand *pCmd = CmdFactory::Instance()->newCommand(CPlayerSpeedV2(vecNum,0,0,0,0));
		// 执行且下发
		//pCmd->execute(IS_SIMULATION);
		rbk::protocol::Message_SSL_Command* ssl_cmd = cmds.add_command();
		ssl_cmd->set_robot_id(vInfo.player[pCmd->number()].ID);
		((CPlayerSpeedV2*)pCmd)->setSpeedtoSSLCmd(ssl_cmd);
		// 记录指令
		_pVision->SetPlayerCommand(pCmd->number(), pCmd);
	}
	GRBKHandle::Instance()->publishTopic(cmds);
	return true;
}

void CActionModule::sendToOwl(const rbk::protocol::SRC_Cmd& cmds)
{
	SRC_cmds = new rbk::protocol::SRC_Cmd;
	int totalnum = cmds.command_size();
	//LogInfo(totalnum);
	if (totalnum >= 24) {
		LogWarn("!!!!!!!!!To Many Command Message To Owl!!!!!!!!!!!!!!!!!!!!!!!!");
		return;
	}

	for (int i = 0; i < totalnum; i++) {
		auto& cmd = cmds.command(i);
		rbk::protocol::Message_SSL_Command *SRC_cmd = SRC_cmds->add_command();
		SRC_cmd->set_robot_id(cmd.robot_id());
		SRC_cmd->set_velocity_x(cmd.velocity_x());
		SRC_cmd->set_velocity_y(cmd.velocity_y());
		SRC_cmd->set_velocity_r(cmd.velocity_r());
		SRC_cmd->set_flat_kick(cmd.flat_kick());
		SRC_cmd->set_chip_kick(cmd.chip_kick());
		SRC_cmd->set_dribbler_spin(cmd.dribbler_spin());
	}
	//发送cmd//
	int size = SRC_cmds->ByteSize();
	char *output = new char[size];
	SRC_cmds->SerializeToArray(output, size);
	cmds_socket.writeTo(output, size, "127.0.0.1", cmd_port[(int)isYellow]);
	//cmds_socket.writeTo(output, size, "127.0.0.1", cmd_port[0]);

	//删除掉message的部分，回收空间//
	SRC_cmds->Clear();
	delete[]SRC_cmds;
}
