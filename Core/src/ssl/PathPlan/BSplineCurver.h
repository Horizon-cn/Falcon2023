#ifndef BSPLINECURVER_H
#define BSPLINECURVER_H
#include "PathPlan/ObstacleNew.h"
#include <Eigen/Dense>  //矩阵运算库，已经添加于RBK_RUN_2015\plugins\SSLStrategy\src\ssl下
///==============================================================================================================================//
///                                        BSplineCurver class definition
///==============================================================================================================================//
class CurverPoint {
public:
	CurverPoint() {}
	~CurverPoint() {}
	CurverPoint(double u, const CGeoPoint& p, const CVector& pdot, const CVector& pddot) {
		_u = u;
		_udot = 0.0;
		_uddot = 0.0;
		_p = p;
		_pdot = pdot;
		_pddot = pddot;
		double result = (fabs(pdot ^ pddot));
		result = result < 0.01 ? 0.01 : result;
		_curva = pdot.mod() * pdot.mod() * pdot.mod() / result;
		_alpha = pdot.unit();
		_gamma = pdot ^ pddot;
		_beta = _alpha ^ _gamma;
	}
	CVector Vel() const {
		return _pdot * _udot; 
	}
	double U() const { return _u; }
	double Udot() const { return _udot; }
	CGeoPoint P() const { return _p; }
	CVector Pdot() const { return _pdot; }
	CVector Pddot() const { return _pddot; }
	CVector CurvaVec() const { return _beta * _curva; }
	double Curva() const { return _curva; }
	void setUdot(const CVector& vel) {
		_udot = vel * _pdot / _pdot.mod() / _pdot.mod();
		//_udot = vel * _pdot / _pdot.mod();
		//double ctheta = _udot/vel.mod();
		//LogInfo("costheta: "<<ctheta);
	}
	void setUdot(double udot) {
		_udot = udot;
	}
	void reduceUdot(double lowBnd) {
		if (_udot > lowBnd) {
			_udot = (_udot + lowBnd) / 2.0;
		}
	}
private:
	double _u;
	double _udot;
	double _uddot;
	CGeoPoint _p;
	CVector _pdot;
	CVector _pddot;
	CVector _alpha;//单位切矢//
	CVector _beta;//主法矢//
	double _gamma;//副法矢//
	double _curva;
};


class BSplineCurver {//curve the full path using quasi-uniform spline
public:
	BSplineCurver() {}
	~BSplineCurver() {}
	void initCurver(int k, vector<CGeoPoint> wayPts, bool PASS_PTS);
	void addCurverPoints(const CVector& start, const CVector& final);
	void addCurverPoints(const CVector& start, const double timeStep);
	void setVelConstr(double maxVel) {
		_maxVel = maxVel;
	}
	void setAccConstr(double minAcc, double maxAcc) {
		_maxDec = minAcc;
		_maxAcc = maxAcc;
	}
	void forwardScan(double lowerBnd,int iteration);
	void drawCurverPoints();
	stateNew getNextCurverPoint();
private:
	int _numSegments;//segments of BSpline
	int _k; //ranks of BSpline
	vector < double > _nodeVector4p;
	vector < double > _nodeVector4v;
	vector < double > _nodeVector4a;

	vector < CVector > _controlPts4p;
	vector < CVector > _controlPts4v;
	vector < CVector > _controlPts4a;

	CGeoPoint getPos(double u);
	CVector getVel(double u);
	CVector getAcc(double u);
	vector<CurverPoint> _curverPts;
	vector<CGeoPoint> _CopyWayPts;   //Store the waypts got by RRT

	void UQuasiUniform();
	vector<CGeoPoint> OnWayPts(int k, const vector<CGeoPoint> wayPts, bool PASS_PTS);
	void addControlPoints(const vector<CGeoPoint> wayPts);

	double baseFunction(int i, int k, double u, const vector <double> nodeVector);//Ni,k (u)

	double _maxVel;
	double _maxDec;
	double _maxAcc;
	bool forwardNewUdot(vector <CurverPoint>::iterator i);
	void printUdot();
};

class BSplinePlanner {
public:
	BSplinePlanner() {}
	~BSplinePlanner() {}
	void initPlanner( vector<CGeoPoint> wayPts, const PlayerCapabilityT& cap, bool PASS_PTS);
	void smoothPath(const CVector& start, const CVector& final,double lowerBnd,int iteration,bool drawTraj);
	void smoothPath(const CVector& start, const double timeStep, double lowerBnd, int iteration, bool drawTraj);
	stateNew getNextState();
private:
	BSplineCurver _curver;
	double calcNextVel(double curva);
};
#endif // BSPLINECURVER_H
