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
    }
    
    CGeoPoint FootH() const {
        return H; // 直接返回计算得到的垂足
    }

    CGeoLine LineM() const {
        return M; // 直接返回计算得到的射线
    }

    double DistanceAH() const {
        return A.dist(H); // 直接返回A到H的距离
    }
    double DistanceOH() const {
    	return O.dist(H);
    }

private:
    CGeoPoint O;
    double DIR;
    CGeoPoint A;
    CGeoLine M;
    CGeoPoint H;
    double AHdist;
};
double timeOH(double v0, double s) {
    // a = -std::abs(a);
    double a=-1.93;
    double t = (-v0 + std::sqrt(v0 * v0 - 2 * a * (-s))) / a;
    
    return t;
}
double distback(const double& SAH, const double& TAH) {
	double maxa=4;
    double SF = 0.5 * maxa * std::pow(TAH, 2); // 使用std::pow进行幂运算
    if (SAH >= SF) {
        return 2 * SF; // 假设这里是期望的返回逻辑
    } else if (0.5 * SF < SAH && SAH < SF) { // 分开进行比较
        double T2 = TAH * std::pow((SF - SAH) / (2 * SF), 0.5); // 再次使用std::pow
        return 0.5 * maxa * std::pow(2 * (TAH - T2), 2); // 修改括号和幂运算
    }
    return 0; // 如果上述条件都不满足，应该有一个默认返回值
}


CTechDefence::CTechDefence() 
{
	
}

void CTechDefence::plan(const CVisionModule* pVision)
{
	TaskT taskR1(task());
	int rolenum=task().executor;
	taskR1.executor=rolenum;
	//set the executor of this plan
//----------------------------------------------INITIALIZE ALL INFOS
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
// ---------------------------------------------PREPARE INPUTS FOR CALSS INTERCEPT 
	CGeoPoint O;
	O=ball.Pos(); // 射线的起点
    double DIR =ball.Vel().dir(); 
    CGeoPoint A(3, 1); // 射线外的点A,应该先有一个谁快要接到球的判断车号，或踢球者也可以改这个谁快要接到球的车号
// ----------------------------------------------GET INFOS FROM CLASS INTERCEPT
    Intercept calculator(O, DIR, A);
    CGeoPoint H = calculator.FootH(); // 获取垂足H的坐标
    CGeoLine M = calculator.LineM(); // 获取射线M
    double SAH = calculator.DistanceAH(); // 获取A到H的距离
    std::cout << "FootH: (" << H.x() <<","<<H.y()<<")";  
//----------------------------------------------PREPARE INFOS FOR VIRTUAL TARGET POS TO MAKE INTERCEPTION FASTER
    double TAH=timeOH(ball.Vel().mod(),SAH);
    std::cout << "DistanceAH: " << SAH ;
//----------------------------------------------CALCULATE DISTBACK AND POSBACK TO MAKE INTERCEPTION FASTER
    double backdist=distback(SAH,TAH);
    std::cout <<"backdist<"<<backdist<<">";
//----------------------------------------------SET SUB TASKS
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