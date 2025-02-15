#include "KickDirection.h"
#include <ShootRangeList.h>
#include "BallStatus.h"
#include "GDebugEngine.h"
#include "Compensate.h"
#include<fstream>
#include<sstream>
#include "Global.h"

extern bool IS_SIMULATION;

namespace {
	bool needAdjust = true;								// 重要参数，踢球角度补偿开关
	const double CompensationMaxAngle = Param::Math::PI*2.0/180;

	CGeoPoint Shoot2Goal;
	const double MinShootWidth = 3*Param::Field::BALL_SIZE;
	const double DiffAngle_TPB_Max = Param::Math::PI/2.0;	// 踢球目标-车-球 夹角
	const double DiffAngle_TPBV_Min = Param::Math::PI/36.0;	// 踢球目标-车-球速反向
	const double CompensationBallMinSpeed = 50;				// 50cm/s
	const double BaseBallSpeed = 50;						// 50cm/s

	const double CriticalDist2Ball = 50;					// 50cm
	const double compensateDist = 90;
	double last_compensate_value = 0;
	
	const bool VERBOSE_MODE = false;
	bool testcompensate=false;
	double compensatevalue[100][50];
	double SHOOT_BLOCKED_RANGE = 3;
	double w = Param::Field::GOAL_WIDTH;
    double goal[9] = { -0.4 * w,-0.3 * w,-0.2 * w,-0.1 * w,0,0.1 * w,0.2 * w,0.3 * w,0.4 * w };
};


CKickDirection::CKickDirection( )
{
	reset();
	Shoot2Goal = CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, 0.0);
#ifdef WIN32
    const string path ="..\\data\\ssl\\play_books\\";
#else
    const string path ="../data/ssl/play_books/";
#endif
    string fullname = path +"data.txt";
	ifstream infile(fullname.c_str());
	if (!infile) {
		cerr << "error opening file data"<< endl;
		exit(-1);
	}
	string line;
	int rowcount;
	int columncount;
	getline(infile,line);
	istringstream lineStream(line);
	lineStream>>rowcount>>columncount;
	for (int i =0;i<rowcount;i++){
		getline(infile,line);
		istringstream lineStream(line);
		for(int j=0;j<columncount;j++){
			lineStream>>compensatevalue[i][j];
		}
	}
};

void CKickDirection::reset() 
{
	_kick_valid = false;
	_is_compensated = false;

	_raw_kick_dir = 0.0;
	_compensate_value = 0.0;
	_real_kick_dir = 0.0;

	_kick_target = Shoot2Goal;
	_compensate_factor = 0.0;
}

void CKickDirection::GenerateShootDir(const int player, const CGeoPoint pos)
{
	///> 进行重置
	reset();
	CVisionModule* pVision = vision;
	const BallVisionT & ball = pVision->Ball();
	const PlayerVisionT & kicker = pVision->OurPlayer(player);
	
	///> 计算踢球的方向,并生成踢球目标
	CShootRangeList shootRangeList(pVision, player, pos);
	const CValueRange* bestRange = NULL;
	const CValueRangeList& shootRange = shootRangeList.getShootRange();
	if (shootRange.size() > 0) {
		bestRange = shootRange.getMaxRangeWidth();
		if (bestRange && bestRange->getWidth() > MinShootWidth) {	// 要求射门空档足够大
			_kick_valid = true;
			_raw_kick_dir = bestRange->getMiddle();
			//GDebugEngine::Instance()->gui_debug_line(kicker.Pos(),kicker.Pos()+Utils::Polar2Vector(500,_raw_kick_dir),COLOR_RED);
			CGeoLine shootLine = CGeoLine(kicker.Pos(),kicker.Pos()+Utils::Polar2Vector(500,_raw_kick_dir));
			CGeoLine bottomLine = CGeoLine(CGeoPoint(Param::Field::PITCH_LENGTH/2.0,-50),CGeoPoint(Param::Field::PITCH_LENGTH/2.0,+50));
			CGeoLineLineIntersection intersect = CGeoLineLineIntersection(shootLine,bottomLine);
			if (intersect.Intersectant()) {
				_kick_target = intersect.IntersectPoint();
			}
		}
	} else{
		_kick_target = Shoot2Goal;
	}


	///> 踢球方向补偿
	CVector self2ball = ball.Pos() - kicker.Pos();
	double ballVelDir = ball.Vel().dir();
	double ballVelReverse = Utils::Normalize(ballVelDir+Param::Math::PI);	// 球速反向
	
	if (VERBOSE_MODE) {
		GDebugEngine::Instance()->gui_debug_line(kicker.Pos(),kicker.Pos()+Utils::Polar2Vector(1000,_real_kick_dir),COLOR_CYAN);
		GDebugEngine::Instance()->gui_debug_line(kicker.Pos(),kicker.Pos()+Utils::Polar2Vector(1000,_raw_kick_dir),COLOR_WHITE);
		GDebugEngine::Instance()->gui_debug_line(kicker.Pos(),kicker.Pos()+Utils::Polar2Vector(1000,kicker.Dir()),COLOR_BLACK);
	}
	
	// bug fix [5/16/2011 cliffyin]
	if (! _kick_valid) {
		_raw_kick_dir  = (Shoot2Goal- kicker.Pos()).dir();
		_real_kick_dir = (Shoot2Goal- kicker.Pos()).dir();
		_kick_target = Shoot2Goal;
	}

	//查表方式补偿

	double ballspeed = ball.Vel().mod();
	double tempdir = (Utils::Normalize(Utils::Normalize(pVision->Ball().Vel().dir()+Param::Math::PI)-(_kick_target - pVision->OurPlayer(player).Pos()).dir()))*180/Param::Math::PI;
	int ratio = 0;
	if (tempdir>0){
		ratio = 1;
	}else{
		ratio = -1;
	}
	rawdir=abs((Utils::Normalize(Utils::Normalize(pVision->Ball().Vel().dir()+Param::Math::PI)-(_kick_target - pVision->OurPlayer(player).Pos()).dir()))*180/Param::Math::PI);
	if (rawdir > 80){
		rawdir = 80;
		//cout<<"kickdirection rawdir changed to 80"<<endl;
	}
	_compensate_value = Compensate::Instance()->checkCompensate(player,ballspeed,rawdir);
	if (pVision->Ball().Vel().mod()<10){
		_compensate_value = 0;
	}
	if (IS_SIMULATION){
		_compensate_value = 0;
	}
	_real_kick_dir= Utils::Normalize(Utils::Normalize(ratio*_compensate_value*Param::Math::PI/180)+_raw_kick_dir);
	if(pVision->Ball().Vel().mod()<50){
		_real_kick_dir = _raw_kick_dir;
	}
	//cout<<vision->Cycle()<<" "<<ballspeed<<" "<<rawdir<<" "<<_compensate_value<<endl;
    _real_kick_dir = getPointShootDir(pVision, pVision->OurPlayer(player).Pos());
    _raw_kick_dir = getPointShootDir(pVision, pVision->OurPlayer(player).Pos());
    return;
}

double CKickDirection::calCompensate(double x, double y)
{
	double compensate=0;
    if (y<=20){
		compensate = 0;
	}else if(y>20 && y<50){
		compensate = 0.01*x+0.01*y+6;
	}else if (y>50){
		compensate = 0.01*x+0.005*y+9.5;
	}
	return compensate;
}

double CKickDirection::calGussiFuncA(double x1, double y1,double x2,double y2){
    double gamma = 0.1088;
	double result=0;
	double sum=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	result= exp((-1.0)*gamma*sum);
   return result;
}

double CKickDirection::calGussiFuncB(double x1, double y1,double x2,double y2){
	double gamma = 0.0039;
	double result=0;
	double sum=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	result= exp((-1.0)*gamma*sum);
	return result;
}


double CKickDirection::getPointShootDir(const CVisionModule* pVision, CGeoPoint startPoint) {

	int n = 0;
	const BallVisionT& ball = pVision->Ball();
	bool shootBlocked = false;
	CGeoPoint projectionPoint;
	double k_m = SHOOT_BLOCKED_RANGE;//ball2theirbest / 15;

	double opp2LineDist_max = 0;
	int best_i = -1;
    for (int i = 1;i < 8;i++) {
		//去除同边角，不易进球，易撞球门
		if (i == 0) {
            if (startPoint.y() < -0.5 * Param::Field::PITCH_WIDTH + 150 ||
				(startPoint.x() > 0.5 * Param::Field::PITCH_LENGTH - 150 && startPoint.y() < -0.5 * Param::Field::PITCH_WIDTH + 200) ||
				(startPoint.x() > 0.5 * Param::Field::PITCH_LENGTH - 200 && startPoint.y() < -0.5 * Param::Field::PITCH_WIDTH + 180))
                continue;
		}
		if (i == 1) {
			if ((startPoint.x() > 0.5 * Param::Field::PITCH_LENGTH - 100 && startPoint.y() < -0.5 * Param::Field::PITCH_WIDTH + 200) ||
				(startPoint.x() > 0.5 * Param::Field::PITCH_LENGTH - 200 && startPoint.y() < -0.5 * Param::Field::PITCH_WIDTH + 180))

				continue;
		}
        if (i == 7) {
			if ((startPoint.x() > 0.5 * Param::Field::PITCH_LENGTH - 100 && startPoint.y() > 0.5 * Param::Field::PITCH_WIDTH - 200) ||
				(startPoint.x() > 0.5 * Param::Field::PITCH_LENGTH - 200 && startPoint.y() > 0.5 * Param::Field::PITCH_WIDTH - 180))

				continue;
		}
        if (i == 8) {
            if (startPoint.y() > 0.5 * Param::Field::PITCH_WIDTH - 150 ||
				(startPoint.x() > 0.5 * Param::Field::PITCH_LENGTH - 150 && startPoint.y() > 0.5 * Param::Field::PITCH_WIDTH - 200) ||
				(startPoint.x() > 0.5 * Param::Field::PITCH_LENGTH - 200 && startPoint.y() > 0.5 * Param::Field::PITCH_WIDTH - 180))
                continue;
		}
		double shootDir = (CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, goal[i]) - startPoint).dir();
		CGeoLine ball2ourGoal = CGeoLine(startPoint, shootDir);
		double opp2LineDist = 1000;
		n = 0;
		while (n <= Param::Field::MAX_PLAYER) {
			if (!pVision->TheirPlayer(n).Valid()) { n++; continue; }
			projectionPoint = ball2ourGoal.projection(pVision->TheirPlayer(n).Pos());
			if (opp2LineDist > (projectionPoint - pVision->TheirPlayer(n).Pos()).mod() && projectionPoint.x() >= startPoint.x()) {
				opp2LineDist = (projectionPoint - pVision->TheirPlayer(n).Pos()).mod();
			}
			n++;
		}
		if (opp2LineDist_max < opp2LineDist) {
			opp2LineDist_max = opp2LineDist;
			best_i = i;
		}
	}
	double shootDir = (CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, goal[best_i]) - startPoint).dir();
	TheShootPoint = CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, goal[best_i]);

	if (opp2LineDist_max < k_m * Param::Vehicle::V2::PLAYER_SIZE) {
		shootBlocked = true;
		//return 1000;
	}
	return shootDir;
}

CGeoPoint CKickDirection::GetTheShootPoint(const CVisionModule* pVision, CGeoPoint startPoint) {
	getPointShootDir(pVision, startPoint);
	return TheShootPoint;
}
