#include <PathPlan/BSplineCurver.h>
#include <GDebugEngine.h>
using namespace Eigen;

void BSplineCurver::initCurver(int k, vector<CGeoPoint> wayPts, bool PASS_PTS)
{
	_numSegments = wayPts.size() - 1;
	_k = k;
	_curverPts.clear();
	_curverPts.reserve(_numSegments * 2 + 2);
	UQuasiUniform();

	vector<CGeoPoint> m_wayPts = OnWayPts(k, wayPts, PASS_PTS);
	//在此进行反向求控制点
	addControlPoints(m_wayPts);
}

//build quasi-uniform nodevector
void BSplineCurver::UQuasiUniform()
{
	_nodeVector4p.clear();
	int piecewise = _numSegments - _k + 1;//节点矢量分段数//
	if (piecewise <= 0)
	{
		qDebug() << "need more points";
	}
	else
	{
		for (int itor = 0; itor < _k + 1; itor++)
		{
			_nodeVector4p.push_back(1.0);
			_nodeVector4p.insert(_nodeVector4p.begin(), 0.0);//build up 000...111
		}

		for (int flag = 0; flag < piecewise - 1; flag++)
		{
			double node2add = _nodeVector4p[_k + flag] + 1.0 / piecewise;
			auto where2add = _nodeVector4p.begin() + _k + 1 + flag;
			_nodeVector4p.insert(where2add, node2add);//build up the AP in the middle of 0s and 1s
		}
		_nodeVector4v.assign(_nodeVector4p.begin() + 1, _nodeVector4p.end() - 1);   //准均匀求导法则，直接去掉首末点
		_nodeVector4a.assign(_nodeVector4v.begin() + 1, _nodeVector4v.end() - 1);
	}

	//LogInfo("nodeVector as ");
	//for (int i = 0; i < _nodeVector.size(); i++)
	//{
	//	cout << _nodeVector[i] << " ";
	//}
	//cout << "\n";
}

//calculate Ni,k(u)
double BSplineCurver::baseFunction(int i, int k, double u, const vector <double> nodeVector)
{
	double Nik_u = 0.0;
	if (0 == k)
	{
		if ((u >= nodeVector[i]) && (u < nodeVector[i + 1]) || ((u >= nodeVector[i]) && (u <= nodeVector[i + 1]) && u == 1))
		{
			Nik_u = 1.0;
		}
		else
		{
			Nik_u = 0.0;
		}
	}
	else
	{
		double length1 = nodeVector[i + k] - nodeVector[i];
		double length2 = nodeVector[i + k + 1] - nodeVector[i + 1];
		if (length1 < 1e-5)
		{
			length1 = 1.0;
		}
		if (length2 < 1e-5)
		{
			length2 = 1.0;
		}
		Nik_u = (u - nodeVector[i]) / length1 * baseFunction(i, k - 1, u, nodeVector) + (nodeVector[i + k + 1] - u) / length2 * baseFunction(i + 1, k - 1, u, nodeVector);
	}
	return Nik_u;
}

vector<CGeoPoint> BSplineCurver::OnWayPts(int k, const vector<CGeoPoint> wayPts, bool PASS_PTS)
{
	if (PASS_PTS == false)
	{
		return wayPts;          //不经过真实控制点模式，即老模式，直接过
	}
	else
	{
		//std::string sep = "\n----------------------------------------\n";
		//qDebug() << QString::fromStdString(sep);
		IOFormat HeavyFmt(FullPrecision, 0, ", ", ";\n", "[", "]", "[", "]");
		//_CopyWayPts.clear();
		int num = wayPts.size();
		MatrixXd P(2, num);
		for (int i = 0; i < num; i++)
		{
			//_CopyWayPts.push_back(wayPts[i]);
			P(0, i) = wayPts[i].x();
			P(1, i) = wayPts[i].y();  //行代表坐标，列代表点, 把waypts里的点转换成坐标
		}

		MatrixXd phi(num, num);
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				phi(i, j) = baseFunction(j, k, i / double(_numSegments), _nodeVector4p);
			}
		}
		phi(_numSegments, _numSegments) = 1;

		MatrixXd FinalP,phiT,PT;  //计算过程中矩阵
		phiT = phi.transpose();
		PT = P.transpose();
		MatrixXd A = phiT*phi;
		MatrixXd b = phiT*PT;
		FinalP = A.ldlt().solve(b);  // 整体即为 P=\left(\Phi^T\Phi\right)^{-1}\Phi^TQ
		//LogInfo("off way pts by: "<<(A*FinalP - b).norm());
		vector<CGeoPoint> m_wayPts;
		m_wayPts.clear();
		for (int i = 0; i <= _numSegments; i++)
		{
			m_wayPts.push_back(CGeoPoint(FinalP(i, 0), FinalP(i, 1))); //构建新的wayPts
		}
		return m_wayPts;
	}
}

CGeoPoint BSplineCurver::getPos(double u)
{
	CGeoPoint point4u(0, 0);
	for (int i = 0; i <= _numSegments; i++)
	{
		point4u = point4u + _controlPts4p[i] * baseFunction(i, _k, u, _nodeVector4p);
	}
	return point4u;
}

CVector BSplineCurver::getVel(double u)
{
	CVector point4u(0, 0);
	for (int i = 0; i <= _numSegments - 1; i++)
	{
		point4u = point4u + _controlPts4v[i] * baseFunction(i, _k - 1, u, _nodeVector4v);
	}
	return point4u;
}

CVector BSplineCurver::getAcc(double u)
{
	CVector point4u(0, 0);
	for (int i = 0; i <= _numSegments - 2; i++)
	{
		point4u = point4u + _controlPts4a[i] * baseFunction(i, _k - 2, u, _nodeVector4a);
	}
	return point4u;
}

void BSplineCurver::addControlPoints(const vector<CGeoPoint> wayPts)
{
	_controlPts4p.clear();
	for (CGeoPoint i : wayPts) {
		_controlPts4p.push_back(CVector(i.x(), i.y()));
	}

	_controlPts4v.clear();
	CVector point2add(0, 0);
	for (int i = 0; i <= _numSegments - 1; i++)
	{
		point2add = (_controlPts4p[i + 1] - _controlPts4p[i]) * _k / (_nodeVector4v[i + _k] - _nodeVector4v[i]);
		_controlPts4v.push_back(point2add);
	}

	_controlPts4a.clear();
	for (int i = 0; i <= _numSegments - 2; i++)
	{
		point2add = (_controlPts4v[i + 1] - _controlPts4v[i]) * (_k - 1) / (_nodeVector4a[i + _k - 1] - _nodeVector4a[i]);
		_controlPts4a.push_back(point2add);
	}
}

void BSplineCurver::addCurverPoints(const CVector& start, const CVector& final)
{
	//LogInfo("adding point");
	for (double u = 0; u <= 1.0; u += 1.0 / _numSegments / 2)
	{
		//LogInfo("u = " << u);
		CGeoPoint tempPos = getPos(u);
		CVector tempVel = getVel(u);
		CVector tempAcc = getAcc(u);
		CurverPoint tempPoint(u, tempPos, tempVel, tempAcc);
		try
		{
			_curverPts.push_back(tempPoint);
		}
		catch (const std::exception& e)
		{
			qDebug() << e.what();
		}
		//LogInfo("size:"<<_curverPts.size());
	}
	_curverPts.begin()->setUdot(start);
	_curverPts.end()->setUdot(final);
}

void BSplineCurver::addCurverPoints(const CVector& start, const double timeStep)
{
	vector<CurverPoint> temp_curverPts;
	temp_curverPts.push_back(*_curverPts.begin());
	vector<double> u = { 0.01 }; //(_curverPts.begin() + 1)->U() / 2
/**	for (double temp_u = 1.0 / _numSegments / 2; temp_u <= 1.0; temp_u += 1.0 / _numSegments / 2)
	{
		u.push_back(temp_u);
	}**/
	for (int i = 0; i < u.size(); i++)
	{
		CGeoPoint tempPos = getPos(u[i]);
		CVector tempVel = getVel(u[i]);
		CVector tempAcc = getAcc(u[i]);
		CurverPoint tempPoint(u[i], tempPos, tempVel, tempAcc);
		try
		{
			temp_curverPts.push_back(tempPoint);
		}
		catch (const std::exception& e)
		{
			qDebug() << e.what();
		}
	}
	temp_curverPts.push_back(*(_curverPts.begin() + 1));
	_curverPts = temp_curverPts;
}

void BSplineCurver::drawCurverPoints()
{
	for (CurverPoint i : _curverPts)
	{
		//LogInfo("checkPoint4."<<i.U());
		GDebugEngine::Instance()->gui_debug_arc(i.P(), 10, 0, 360, COLOR_RED);
		GDebugEngine::Instance()->gui_debug_line(i.P(), i.P() + i.Pdot()*0.1, COLOR_WHITE);
		if (i.U() != 0)
			GDebugEngine::Instance()->gui_debug_msg(i.P(), QString::number(i.Vel().mod()).toStdString().c_str(), COLOR_BLUE);
		//GDebugEngine::Instance()->gui_debug_line(i.P(), i.P() + i.Pddot() * 0.1, COLOR_YELLOW);
		//GDebugEngine::Instance()->gui_debug_arc(i.P() + i.CurvaVec(), i.CurvaVec().mod(), 0, 360, COLOR_YELLOW);
	}
	for (CVector pos : _controlPts4p)
	{
		GDebugEngine::Instance()->gui_debug_arc(CGeoPoint(pos.x(), pos.y()), 10, 0, 360, COLOR_YELLOW);
	}
}

void BSplinePlanner::initPlanner(vector<CGeoPoint> wayPts, const PlayerCapabilityT& cap, bool PASS_PTS)
{
	int rank = 2;
	_curver.initCurver(rank, wayPts,PASS_PTS);
	_curver.setVelConstr(cap.maxSpeed);
	_curver.setAccConstr(cap.maxDec, cap.maxAccel);
}

void BSplinePlanner::smoothPath(const CVector& start, const CVector& final,double lowerBnd,int iteration,bool drawTraj)
{
	_curver.addCurverPoints(start, final);
	_curver.forwardScan(lowerBnd,iteration);
	if(drawTraj)
		_curver.drawCurverPoints();
}

void BSplinePlanner::smoothPath(const CVector& start, const double timeStep, double lowerBnd, int iteration, bool drawTraj)
{
	_curver.addCurverPoints(start, timeStep);
	_curver.forwardScan(lowerBnd, iteration);
	if (drawTraj)
		_curver.drawCurverPoints();
}

void BSplineCurver::forwardScan(double lowerBnd,int iteration)
{
	int MAX_ITERATION = iteration;
	//LogInfo("in forwardScan");
	for (vector <CurverPoint>::iterator i = _curverPts.begin() + 1; i <= _curverPts.begin() + 2; i++)
	{
		int iteration = 0;
		double lastUdot = i->Udot();
		while (!forwardNewUdot(i))
		{
			iteration++;
			(i - 1)->reduceUdot(lowerBnd);
			if (iteration >= MAX_ITERATION)
			{
				//qDebug() << "MAX_ITERATION, BREAK";
				break;
			}
			else if (lastUdot == i->Udot()) {
				//qDebug() << "no change, break";
				break;
			}				
			lastUdot = i->Udot();
		}
	}
}

bool BSplineCurver::forwardNewUdot(vector <CurverPoint>::iterator i)
{
	//LogInfo("last udot: " << (i-1)->Udot());
	//LogInfo("current udot: " << i->Udot());
	CGeoPoint posU = i->P();
	CVector velU = i->Pdot();
	CVector accU = i->Pddot();
	double curva = i->Curva();
	double du = i->U() - (i - 1)->U();
	double lastUdot = (i - 1)->Udot();

	CGeoPoint lastPosU = (i - 1)->P();
	CVector lastVelU = (i - 1)->Vel(); //(i - 1)->Pdot();
	CVector lastAccU = (i - 1)->Pddot();
	CVector averageAccU = (lastAccU * lastUdot + accU) / 2;

	//Vel constraints
	double scale = velU.mod2();
	double udotsqr1 = _maxVel * _maxVel / scale;
	double udotsqr2 = _maxDec * curva / scale;

	double udotsqr3 = 0.0;//upper bnd
	double udotsqr4 = 0.0;//upper bnd
	double udotsqr5 = 0.0;//lower bnd
	double udotsqr6 = 0.0;//lower bnd
	//Acc constraints
	//double scale4a_x = velU.x() / 2 / du;
	//double udotsqrXup = (_maxAcc + scale4a_x * lastUdot * lastUdot) / (scale4a_x + accU.x());
	//double udotsqrXlo = (-_maxDec + scale4a_x * lastUdot * lastUdot) / (scale4a_x + accU.x());
	double vx2 = velU.x() * velU.x();
	double lastVx2 = lastVelU.x() * lastVelU.x();
	double x = fabs(lastPosU.x() - posU.x());
	double udotsqrXup = fabs((lastVx2 + 2 * _maxAcc * x) / vx2); //fabs((lastVx2 + 2 * _maxAcc * x) / (lastVx2 + 2 * averageAccU.x() * x)); 
	double udotsqrXlo = fabs((lastVx2 - 2 * _maxDec * x) / vx2); //fabs((lastVx2 - 2 * _maxDec * x) / (lastVx2 + 2 * averageAccU.x() * x));
	if (udotsqrXup > udotsqrXlo)
	{
		udotsqr3 = udotsqrXup;
		udotsqr5 = udotsqrXlo;
	}
	else
	{
		udotsqr3 = udotsqrXlo;
		udotsqr5 = udotsqrXup;
	}

	//double scale4a_y = velU.y() / 2 / du; //accU.y() + 
	//double udotsqrYup = (_maxAcc + scale4a_y * lastUdot * lastUdot) / (scale4a_y + accU.y());
	//double udotsqrYlo = (-_maxDec + scale4a_y * lastUdot * lastUdot) / (scale4a_y + accU.y());
	double vy2 = velU.y() * velU.y();
	double lastVy2 = lastVelU.y()* lastVelU.y();
	double y = fabs(lastPosU.y() - posU.y());
	double udotsqrYup = fabs((lastVy2 + 2 * _maxAcc * y) / vy2); //fabs((lastVy2 + 2 * _maxAcc * y) / (lastVy2 + 2 * averageAccU.y() * y)); 
	double udotsqrYlo = fabs((lastVy2 - 2 * _maxDec * y) / vy2); //fabs((lastVy2 - 2 * _maxDec * y) / (lastVy2 + 2 * averageAccU.y() * y));
	if (udotsqrYup > udotsqrYlo)
	{
		udotsqr4 = udotsqrYup;
		udotsqr6 = udotsqrYlo;
	}
	else
	{
		udotsqr4 = udotsqrYlo;
		udotsqr6 = udotsqrYup;
	}

	double udotsqrup = max(min(min(udotsqr1, udotsqr2), min(udotsqr3, udotsqr4)),0.01);
	double udotsqrlo = max(udotsqr5, udotsqr6);

	double newUdot = 0.0;
	if (udotsqrup >= udotsqrlo)
	{
		newUdot = sqrt(udotsqrup);
		//qDebug() << "have a solution_____________________" << newUdot << udotsqrup << udotsqr1 << udotsqr2 << udotsqr3 << udotsqr4;
		i->setUdot(newUdot);
		return true;
	}
	else//no feasible solution
	{
		newUdot = sqrt(udotsqrup);
		//qDebug() << "no feasible solution_____________________" << newUdot << udotsqrup << udotsqr1 << udotsqr2 << udotsqr3 << udotsqr4;
		i->setUdot(newUdot);
		return false;
	}
}

stateNew BSplinePlanner::getNextState()
{
	stateNew nextState;
	nextState = _curver.getNextCurverPoint();
	return nextState;
}

stateNew BSplineCurver::getNextCurverPoint()
{
	stateNew nextState;
	//printUdot();
	nextState.pos = (_curverPts.begin() + 1)->P();
	nextState.vel = (_curverPts.begin() + 1)->Vel();
	//std::cout << "pdot: " << (_curverPts.begin() + 1)->Pdot() << " " << (_curverPts.begin() + 1)->Pdot().mod() 
	//	<< " " << (_curverPts.begin() + 1)->Udot() << std::endl;
	//std::cout << "vel: " << nextState.vel << " " << nextState.vel.mod() << std::endl;
	//std::cout << std::endl;
	return nextState;
}

void BSplineCurver::printUdot()
{
	for (CurverPoint i : _curverPts)
	{
		qDebug() << "current u: " << i.U();
		qDebug() << "current udot: " << i.Udot();
	}
}