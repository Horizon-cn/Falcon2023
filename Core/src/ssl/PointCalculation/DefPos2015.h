#ifndef _DEFPOS_2015_H_
#define _DEFPOS_2015_H_

#include "geometry.h"
#include "singleton.h"

struct Defend2015 {
    CGeoPoint leftD;    // 左后卫站位点
    CGeoPoint rightD;   // 右后卫站位点
    CGeoPoint helperD;
	CGeoPoint leftFrontD; //左边后位靠前站点
	CGeoPoint rightFrontD;
	CGeoPoint leftBackD;
	CGeoPoint rightBackD;
	CGeoPoint leftCenD;    // 左中后卫站位点
	CGeoPoint rightCenD;    // 右后卫站位点
    CGeoPoint middleD;  // middle站位点
    CGeoPoint singleD;
    CGeoPoint goalieD;
    CGeoPoint sideD;

    CGeoPoint getSidePos() { return sideD; }
    CGeoPoint getLeftPos() { return leftD;}
    CGeoPoint getRightPos() { return rightD; }
    CGeoPoint getHelperPos() { return helperD; }
	CGeoPoint getLeftCenPos() { return leftCenD; }
	CGeoPoint getRightCenPos() { return rightCenD; }
    CGeoPoint getMiddlePos() { return middleD; }
    CGeoPoint getSinglePos() { return singleD; }
    CGeoPoint getGoaliePos() { return goalieD; }
};

class CVisionModule;

class CDefPos2015 {
  public:
    CDefPos2015();
    ~CDefPos2015() {}

    void generatePos(const CVisionModule* pVision);
    Defend2015 getDefPos2015(const CVisionModule* pVision);
    double checkCollision(int myself, CGeoPoint targetPoint, const CVisionModule* pVision);
		
		const CGeoPoint& getSidePos() { return _defendPoints.sideD; }
		const CGeoPoint& getLeftPos() { return _defendPoints.leftD; }
		const CGeoPoint& getRightPos() { return _defendPoints.rightD; }
        const CGeoPoint& getHelperPos() { return _defendPoints.helperD; }
		const CGeoPoint& getLeftCenPos() { return _defendPoints.leftCenD; }
		const CGeoPoint& getRightCenPos() { return _defendPoints.rightCenD; }
		const CGeoPoint& getMiddlePos() { return _defendPoints.middleD; }
		const CGeoPoint& getSinglePos() { return _defendPoints.singleD; }
		const CGeoPoint& getGoaliePos() { return _defendPoints.goalieD; }

  protected:
    int _lastCycle;

    Defend2015 _defendPoints;   
    CGeoPoint _RdefendTarget;  //防守目标点
    CGeoPoint _laststoredgoaliePoint;
    double _RdefendDir;  //防守朝向    
    double _RleftgoalDir;
    double _RrightgoalDir;
    double _RmiddlegoalDir;
    double _RgoalieLeftDir;
    double _RgoalieRightDir;
    double _RleftmostDir;
    double _RrightmostDir;
};

typedef Falcon::NormalSingleton<CDefPos2015> DefPos2015;

#endif 
