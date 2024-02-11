#include "TechDefenceRobot.h"

#include "VisionModule.h"
#include "Global.h"



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

using namespace std;

namespace {
enum TDstate {getball ,wait};//setState(getball);if (state()==getball);
}



CTechDefence::CTechDefence() 
{
	
}

void CTechDefence::plan(const CVisionModule* pVision)
{
	TaskT taskR1(task());
	int rolenum=task().executor;
	taskR1.executor=rolenum;
//----------------------------------------------
	std::vector<const PlayerVisionT*> OPptrs;
	for (int irole = 1; irole <= Param::Field::MAX_PLAYER; ++irole)
	{
		const PlayerVisionT& OPtmp=pVision->OurPlayer(irole);
		if (OPtmp.Valid())
		{
			OPptrs.push_back(&OPtmp);
		}
	}
	if (OPptrs.size() != 3) 
	{
	    std::cout << "OPptrs length error: " << OPptrs.size() << std::endl;
	}
	std::cout<< OPptrs[1]->Vel().mod();
	//OPptrs consists of three pointers that represent our three players that are present on the field.
	//To call their information,use OPptrs[1]->Vel().mod() or OPptrs[1]->Dir()
// ---------------------------------------------
	CGeoPoint POS1(122, 13);
    CGeoPoint POS3(123, 40);
	const PlayerVisionT& theirCar = pVision->TheirPlayer(1);
	const PlayerVisionT& ourCar =pVision->OurPlayer(1);// ourCar.Dir()   or:pVision->AllPlayer(i).Pos().dist(ball.Pos())
	const PlayerVisionT& thisCar =pVision->OurPlayer(task().executor);
	const BallVisionT& ball = pVision->Ball();//ball.Pos().X()和ball().Pos().Y()  ball.Vel().mod() 
	auto ans="a";
// ---------------------------------------------
	
//----------------------------------------------
	if (ans = "pick")
	{

	}
	setSubTask(TaskFactoryV2::Instance()->GotoPosition(taskR1));//将taskR1给走位subtask执行
	CStatedTask::plan(pVision);
}
	


CTechDefence::~CTechDefence() {

}


CPlayerCommand* CTechDefence::execute(const CVisionModule* pVision)
{
	if (subTask()){
		return subTask()->execute(pVision);
	}
	return NULL;
}