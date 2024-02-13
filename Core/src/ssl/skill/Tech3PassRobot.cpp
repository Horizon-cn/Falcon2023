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
using namespace std;

// namespace 
// {
// enum TDstate {getball ,wait};//setState(getball);if (state()==getball);
// }





CTech3Pass::CTech3Pass() 
{
	
}

void CTech3Pass::plan(const CVisionModule* pVision)
{
	TaskT taskR1(task());
	int rolenum=task().executor;
    std::cout<<"task().executor"<<rolenum<<std::endl;
	taskR1.executor=rolenum;
//----------------------------------------------INITIALIZE ALL PLAYER INFOS AND BALL INFOS
	std::vector<const PlayerVisionT*> OPptrs;
    std::vector<int> rolenums;
	for (int irole = 0; irole <= Param::Field::MAX_PLAYER; ++irole)
	{
		const PlayerVisionT& OPtmp=pVision->OurPlayer(irole);
		if (OPtmp.Valid())
		{
			OPptrs.push_back(&OPtmp);
            rolenums.push_back(irole);
		}
	}
    for (int i : rolenums) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
// -----------------------------------------------CALCULATE THREE POINTS
	enum states {PrepareAndPass,Receive};
	setState(PrepareAndPass);
	CGeoPoint B;
	switch(state())
	{
	case PrepareAndPass:
	    if (rolenum==rolenums[1])
	    {
	    	B=CGeoPoint(-75,-130);
	    }
	    else if (rolenum==rolenums[2])
	    {
	    	B=CGeoPoint(-75,130);
	    }
	    else if (rolenum==rolenums[3])
	    {
	    	B=CGeoPoint(150,0);
	    }
	    taskR1.player.pos=B;
	    setSubTask(TaskFactoryV2::Instance()->GotoPosition(taskR1));//将taskR1给走位subtask执行
		CStatedTask::plan(pVision);
		break;
	case Receive:
		break;
	default:
		break;
	}
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