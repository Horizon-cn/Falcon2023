#include "TimeDelayTest.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "skill/Factory.h"
#include <utils.h>
#include <CommandFactory.h>
#include <math.h>
#include <fstream>
#include <QTime>

using namespace std;

namespace{
	const bool Verbose = true;	
	const CGeoPoint startPoint = CGeoPoint(-150,0);
	const int speedBase = 100;
	const int timeBase = 200;
	bool canTakeTest = false;
	unsigned int countNum = 0;
	ofstream timeDelayData("../data/timeDelayData.txt");
	//ofstream timeDelayData_X("../data/timeDelayData_X.txt");
    QTime cur_time;
}

CTimeDelayTest::CTimeDelayTest()
{
	_lastCycle = 0;
	_directCommand = NULL;
	static bool isOutPut = true;
	if (isOutPut == true)
	{
		timeDelayData<<"time,send_x_speed,pos_x,pos_y,dir"<<endl;
		isOutPut = false;
        cur_time = QTime::currentTime();
	}	
}

void CTimeDelayTest::plan(const CVisionModule* pVision)
{	
	_directCommand = NULL;
	//first time come in this skill
	static bool isIn = true;
	if (Verbose)
	{
		if (isIn == true)
		{
			cout<<endl<<"Taking Time Delay Test"<<endl;
			isIn = false;
			canTakeTest = true; //false;
		//	countNum = 0;
		}
	}
	//
	if ( pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1 ){
		//setState(BEGINNING);
		canTakeTest = false;
		//countNum = 0;
	}
	//vision
	const int myNum = task().executor;
	//const PlayerVisionT & me = pVision->OurPlayer(myNum);

	//if (false == canTakeTest)
	//{
	//	if (me.Pos().dist(startPoint) < 5 && Utils::Normalize(me.Dir()-Param::Math::PI/2.0) < 3 * Param::Math::PI / 180)
	//	{
	//		canTakeTest = true;
	//	}
	//}

	if (false == canTakeTest)
	{
		setSubTask(PlayerRole::makeItStop(myNum));
		//setSubTask(PlayerRole::makeItGoto(myNum,startPoint,Param::Math::PI/2.0));
	} 
	else{
		//double x_speed = speedBase * sin((countNum % timeBase) * 2.0 * Param::Math::PI / timeBase);
		//setSubTask(PlayerRole::makeItRun(myNum,0.0,x_speed,0.5 * (Param::Math::PI/2.0-me.Dir())));
		double x_speed = 50;
		_directCommand = CmdFactory::Instance()->newCommand(CPlayerSpeedV2(myNum,x_speed,0.0,0.0,true));
        double cost_time = fabs(QTime::currentTime().msecsTo(cur_time));
        timeDelayData << cost_time * 0.001 << "," << x_speed << ",";
		timeDelayData << pVision->OurPlayer(myNum).X() << "," << pVision->OurPlayer(myNum).Y() << "," << pVision->OurPlayer(myNum).Dir() << endl;
		//countNum++;
	}

	_lastCycle = pVision->Cycle();
	CStatedTask::plan(pVision);
}

CPlayerCommand* CTimeDelayTest::execute(const CVisionModule* pVision)
{
	if( _directCommand ){
		return _directCommand;
	} else if (subTask())
	{
		return subTask()->execute(pVision);
	}
	return NULL;
}
