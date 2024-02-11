#include "TechDefenceRobot.h"

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

namespace 
{
enum TDstate {getball ,wait};//setState(getball);if (state()==getball);
}


// 假设 CGeoPoint 和 CGeoLine 的定义如前所述
class Intercept {
public:
    Intercept(const CGeoPoint& O, const double& DIR, const CGeoPoint& A) 
        : O(O), DIR(DIR), A(A), M(O, CGeoPoint(O.x() + std::cos(DIR), O.y() + std::sin(DIR))) {
        H = M.projection(A); // 计算垂足H并存储
        AHdist = A.dist(H); // 计算A到H的距离并存储
    }
    
    CGeoPoint FootH() const {
        return H; // 直接返回计算得到的垂足
    }

    CGeoLine LineM() const {
        return M; // 直接返回计算得到的射线
    }

    double DistanceAH() const {
        return AHdist; // 直接返回A到H的距离
    }

private:
    CGeoPoint O;
    double DIR;
    CGeoPoint A;
    CGeoLine M;
    CGeoPoint H;
    double AHdist;
};



CTechDefence::CTechDefence() 
{
	
}

void CTechDefence::plan(const CVisionModule* pVision)
{
	TaskT taskR1(task());
	int rolenum=task().executor;
	taskR1.executor=rolenum;
	//set the executor of this plan
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
	const BallVisionT& ball = pVision->Ball();//ball.Pos().X()和ball().Pos().Y()  ball.Vel().mod() 
// ---------------------------------------------
	CGeoPoint O(0, 0); // 射线的起点
    double DIR = M_PI / 4; // 射线的方向，以弧度表示，这里是45度角
    CGeoPoint A(3, 1); // 射线外的点A

    Intercept calculator(O, DIR, A);
    CGeoPoint H = calculator.FootH(); // 获取垂足H的坐标
    CGeoLine M = calculator.LineM(); // 获取射线M
    double distance = calculator.DistanceAH(); // 获取A到H的距离
    std::cout << "FootH: (" << H.x() <<","<<H.y()<<")";
    // std::cout << "LineM: " << M << std::endl;
    std::cout << "DistanceAH: " << distance ;
//----------------------------------------------
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
#endif