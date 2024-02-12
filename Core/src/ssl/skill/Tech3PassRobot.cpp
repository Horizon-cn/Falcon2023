#include "Tech3PassRobot.h"

#include "VisionModule.h"
#include "Global.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846


#include <iostream>
#include "GDebugEngine.h"
#include "Vision/VisionModule.h"
#include "skill/Factory.h"
#include "utils.h"
#include "WorldModel/DribbleStatus.h"
#include "RobotSensor.h"
#include "param.h"
#include "WorldModel/WorldModel.h"


#include <vector>
#include <variant>
#include <string>
#include <cmath>
#include "InterceptTech.h"
using namespace std;

namespace 
{
enum TDstate {getball ,wait};//setState(getball);if (state()==getball);
}




CTech3Pass::CTech3Pass() 
{
	
}

void CTech3Pass::plan(const CVisionModule* pVision)
{
	TaskT taskR1(task());
	int rolenum=task().executor;
	taskR1.executor=0;
	//set the executor of this plan
//----------------------------------------------INITIALIZE ALL PLAYER INFOS AND BALL INFOS
	std::vector<const PlayerVisionT*> OPptrs;
	for (int irole = 1; irole <= Param::Field::MAX_PLAYER; ++irole)
	{
		const PlayerVisionT& OPtmp=pVision->OurPlayer(irole);
		if (OPtmp.Valid())
		{
			OPptrs.push_back(&OPtmp);
		}
	}
	const BallVisionT& ball = pVision->Ball();//ball.Pos().x() ball().Pos().y()  ball.Vel().mod() ball.Vel().dir()
//-------------------------------------------------BASIC PASSING BALL

// ---------------------------------------------PREPARE INPUTS FOR CLASS INTERCEPT 
	CGeoPoint O=ball.Pos(); // 射线的起点
    double DIR =ball.Vel().dir(); 
    CGeoPoint A=OPptrs[1]->Pos(); // 射线外的点A,应该先有一个谁快要接到球的判断车号，或踢球者也可以改这个谁快要接到球的车号
// ----------------------------------------------GET INFOS FROM CLASS INTERCEPT
    
    Intercept calculator(O, DIR, A);
    CGeoPoint H = calculator.FootH(); // 获取垂足H的坐标
    CGeoLine M = calculator.LineM(); // 获取射线M
    double SAH = calculator.DistanceAH()*0.01; // 获取A到H的距离
    double SOH=calculator.DistanceOH()*0.01;
    double VB=ball.Vel().mod()*0.01;
    double VOP=OPptrs[1]->Vel().mod()*0.01;
//----------------------------------------------PREPARE INFOS FOR DISTBACK TO MAKE INTERCEPTION FASTER(TAH,SAH)
    double TAH=timeOH(VB,SOH); 
//----------------------------------------------CALCULATE DISTBACK
    // double distback=getdistback(SAH,TAH);
    double distback;
    double maxa=3;
    double SF = 0.5 * maxa * std::pow(TAH, 2)+TAH*VOP;
    if (SAH>=SF-0.1) //添加车运动方向-->H 的限制
    {
    	distback = 1000;
	} else 
	{
    	distback = 0;
	}
//----------------------------------------------CALCULATE POINTBACK FROM DISTBACK
    CGeoPoint B= backpos(A,H,distback);
    taskR1.player.pos=B;
//----------------------------------------------PRINT ALL INFOS
    GDebugEngine::Instance()->gui_debug_msg(O,"O", COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(H,"HH", COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(A,"AAA", COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(B,"BBBB", COLOR_RED);
    CGeoPoint O0(0,0);
    CGeoPoint O1(0,20);
    CGeoPoint O2(0,40);
    CGeoPoint O3(0,60);
    CGeoPoint O4(0,80);
    CGeoPoint O5(0,100);
	GDebugEngine::Instance()->gui_debug_msg(O0, ("TAH: " + std::to_string(TAH)).c_str(), COLOR_RED);
	GDebugEngine::Instance()->gui_debug_msg(O1, ("SAH: " + std::to_string(SAH)).c_str(), COLOR_RED);
	GDebugEngine::Instance()->gui_debug_msg(O2, ("SF: " + std::to_string(SF)).c_str(), COLOR_RED);
	GDebugEngine::Instance()->gui_debug_msg(O3, ("VOP: " + std::to_string(VOP)).c_str(), COLOR_RED);
	GDebugEngine::Instance()->gui_debug_msg(O4, ("VB: " + std::to_string(VB)).c_str(), COLOR_RED);
	GDebugEngine::Instance()->gui_debug_msg(O5, ("SOH: " + std::to_string(SOH)).c_str(), COLOR_RED);
   	GDebugEngine::Instance()->gui_debug_line(O,H,COLOR_WHITE);
   	GDebugEngine::Instance()->gui_debug_line(A,B,COLOR_WHITE);

//----------------------------------------------SET SUB TASKS
	setSubTask(TaskFactoryV2::Instance()->GotoPosition(taskR1));//将taskR1给走位subtask执行
	CStatedTask::plan(pVision);
}


CTech3Pass::~CTech3Pass() {

}


CPlayerCommand* CTech3Pass::execute(const CVisionModule* pVision)
{
	if (subTask()){
		return subTask()->execute(pVision);
	}
	return NULL;
}
#endif