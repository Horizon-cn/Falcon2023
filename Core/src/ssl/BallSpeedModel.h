#ifndef _BALL_SPEED_MODEL_H_
#define _BALL_SPEED_MODEL_H_

#include "Vision/VisionModule.h"

class CBallSpeedModel{
public:
	CBallSpeedModel();
	CVector speedForTime(int frame, const CVisionModule* pVision);   // 计算若干帧以后的速度
	CVector speedForDist(double dist, const CVisionModule* pVision); // 计算若干距离后的速度
	double timeForDist(double dist, const CVisionModule* pVision);      // 计算球运动若干距离的时间
	CGeoPoint posForTime(int frame, const CVisionModule* pVision);   // 计算若干帧以后的绝对位置
	void update( const CVisionModule* pVision );  // 更新
	double CalKickInitSpeed(const double dist);   // 计算一定距离所需踢球初速度
private:
	CVector _ballVel;
	CVector _lastBallVel;
	CGeoPoint _ballPos;
	double cal_acc;
	double _last_dist;
};
typedef Falcon::NormalSingleton< CBallSpeedModel > BallSpeedModel;
#endif // _BALL_SPEED_MODEL_H_

