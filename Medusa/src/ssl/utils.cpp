#include "utils.h"
#include "WorldModel/WorldModel.h"
#include "param.h"
#include <GDebugEngine.h>
#include <iostream>
#include "ParamManagerNew.h"
#include "Global.h"

namespace Utils {
	double dirDiff(const CVector& v1, const CVector& v2) { return fabs(Normalize(v1.dir() - v2.dir())); }
	double Normalize(double angle)
	{
		/*
		if (fabs(angle) > 10) {
			cout << angle << " Normalize Error!!!!!!!!!!!!!!!!!!!!" << endl;
			return 0;
		}
		*/
		static const double M_2PI = Param::Math::PI * 2;
		// ï¿½ï¿½ï¿½Ù´Öµï¿½ï¿½ï¿½
		angle -= (int)(angle / M_2PI) * M_2PI;

		// Ï¸ï¿½ï¿½ï¿½ï¿½ (-PI,PI]
		while (angle > Param::Math::PI) {
			angle -= M_2PI;
		}

		while (angle <= -Param::Math::PI) {
			angle += M_2PI;
		}

		return angle;
	}
	CVector Polar2Vector(double m, double angle)
	{
		return CVector(m*std::cos(angle), m*std::sin(angle));
	}
	double VectorDot(const CVector& v1, const CVector& v2)
	{
		return v1.x()*v2.x() + v1.y()*v2.y();
	}
	bool InBetween(const CGeoPoint& p, const CGeoPoint& p1, const CGeoPoint& p2)
	{
		return p.x() >= (std::min)(p1.x(), p2.x()) && p.x() <= (std::max)(p1.x(), p2.x())
			&& p.y() >= (std::min)(p1.y(), p2.y()) && p.y() <= (std::max)(p1.y(), p2.y());
	}
	bool InBetween(double v, double v1, double v2)
	{
		return (v > v1 && v < v2) || (v < v1 && v > v2);
	}
	bool InBetween(const CVector& v, const CVector& v1, const CVector& v2, double buffer)
	{

		double d = v.dir(), d1 = v1.dir(), d2 = v2.dir();
		return AngleBetween(d, d1, d2, buffer);
	}

	bool AngleBetween(double d, double d1, double d2, double buffer)
	{
		using namespace Param::Math;
		// d, d1, d2Îªï¿½ï¿½ï¿½ï¿½v, v1, v2ï¿½Ä·ï¿½ï¿½ò»¡¶ï¿½

		// ï¿½ï¿½vï¿½ï¿½v1ï¿½ï¿½v2ï¿½Ä½Ç¶ï¿½ï¿½ï¿½ï¿½ï¿½Ð¡,ï¿½ï¿½bufferï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Î§Ö®ï¿½ï¿½Ê±,ï¿½ï¿½Îªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		double error = (std::min)(std::fabs(Normalize(d - d1)), std::fabs(Normalize(d - d2)));
		if (error < buffer) {
			return true;
		}

		if (std::fabs(d1 - d2) < PI) {
			// ï¿½ï¿½Ö±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÖµÐ¡ï¿½ï¿½PIÊ±, dÓ¦ï¿½Ã´ï¿½ï¿½ï¿½Ð¡ï¿½ï¿½,Ð¡ï¿½Ú´ï¿½ï¿?
			return InBetween(d, d1, d2);
		}
		else {
			// ï¿½ï¿½Îªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
			return InBetween(Normalize(d + PI), Normalize(d1 + PI), Normalize(d2 + PI));
		}
	}

	// ½«ÅÜÎ»µã¸üÕýÔÚÇò³¡ÄÚ. Modified by HXY.
	CGeoPoint MakeInField(const CGeoPoint& p, const double buffer) {
		auto new_p = p;
		if (new_p.x() < buffer - Param::Field::PITCH_LENGTH / 2) new_p.setX(buffer - Param::Field::PITCH_LENGTH / 2);
		if (new_p.x() > Param::Field::PITCH_LENGTH / 2 - buffer) new_p.setX(Param::Field::PITCH_LENGTH / 2 - buffer);
		if (new_p.y() < buffer - Param::Field::PITCH_WIDTH / 2) new_p.setY(buffer - Param::Field::PITCH_WIDTH / 2);
		if (new_p.y() > Param::Field::PITCH_WIDTH / 2 - buffer) new_p.setY(Param::Field::PITCH_WIDTH / 2 - buffer);
		return new_p;
	}

	// ÅÐ¶ÏÎ»ÖÃÊÇ·ñÔÚ¼º·½½ûÇø. Modified by HXY.
	bool InOurPenaltyArea(const CGeoPoint& p, const double buffer) {
		// bufferÎªÕý±íÊ¾½ûÇøÍâÀ©
		return (p.x() < -Param::Field::PITCH_LENGTH / 2 + paramManager->PENALTY_AREA_DEPTH + buffer
			&& std::fabs(p.y()) < Param::Field::PENALTY_AREA_WIDTH / 2 + buffer);
	}

	// ÅÐ¶ÏÎ»ÖÃÊÇ·ñÔÚµÐ·½½ûÇø. Modified by HXY.
	bool InTheirPenaltyArea(const CGeoPoint& p, const double buffer) {
		// bufferÎªÕý±íÊ¾½ûÇøÍâÀ©
		return (p.x() > Param::Field::PITCH_LENGTH / 2 - paramManager->PENALTY_AREA_DEPTH - buffer
			&& std::fabs(p.y()) < Param::Field::PENALTY_AREA_WIDTH / 2 + buffer);
	}


	bool InTheirPenaltyAreaWithVel(const PlayerVisionT& me, const double buffer) {
		CVector vel = me.Vel();
		CGeoPoint pos = me.Pos();
		//        GDebugEngine::Instance()->gui_debug_x(pos + Polar2Vector(pow(vel.mod(), 2) / (2 * 400), vel.dir()));
		if (me.Vel().mod() < 30) return InTheirPenaltyArea(me.Pos(), buffer);
		if (InTheirPenaltyArea(pos + Polar2Vector(pow(vel.mod(), 2) / (2 * 400), vel.dir()), buffer)) {
			return true;
		}
		else return false;
	}

	bool IsInField(const CGeoPoint p, double buffer) {
		return (p.x() > buffer - Param::Field::PITCH_LENGTH / 2 && p.x() < Param::Field::PITCH_LENGTH / 2 - buffer &&
			p.y() > buffer - Param::Field::PITCH_WIDTH / 2 && p.y() < Param::Field::PITCH_WIDTH / 2 - buffer);
	}
	bool IsInFieldV2(const CGeoPoint p, double buffer) {
		return (IsInField(p, buffer) && !Utils::InOurPenaltyArea(p, buffer) && !Utils::InTheirPenaltyArea(p, buffer));
	}

	bool OutOfField(const CGeoPoint& p, const double buffer)	//bufferÎªï¿½ï¿½ï¿½Ú³ï¿½ï¿½Ú£ï¿½ï¿½ï¿½ï¿½Ú³ï¿½ï¿½ï¿½
	{
		// 2014-06-26 ×¢ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï»áµ¼ï¿½Â½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í³ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?yys
		//if( std::fabs(p.y()) < Param::Field::GOAL_WIDTH/2 ){ // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		//	cout << "here here here" << endl;
		//	return p.x() < FieldLeft() - Param::Field::GOAL_DEPTH/3 
		//		|| p.x() > FieldRight() + Param::Field::GOAL_DEPTH/3;
		//}
		return p.x() < FieldLeft() + buffer || p.x() > FieldRight() - buffer
			|| p.y() < FieldTop() + buffer || p.y() > FieldBottom() - buffer;
	}

	// ½«ÅÜÎ»µã¸üÕýµ½ÎÒ·½½ûÇøÒÔÍâ. Modified by HXY.
	CGeoPoint MakeOutOfOurPenaltyArea(const CGeoPoint& p, const double buffer) {
		// Èç¹ûÔÚÖ´ÐÐ·ÅÇò£¬²»ÐèÒª¸üÕý
		if (WorldModel::Instance()->CurrentRefereeMsg() == "ourBallPlacement")
			return p;

		if (p.y() > 0) {
			// ¸ù¾Ýµ½½ûÇøÓÒ²à½ü»¹ÊÇµ½½ûÇøÉÏ·½½üÀ´Ñ¡Ôñ
			if (-Param::Field::PITCH_LENGTH / 2 + paramManager->PENALTY_AREA_DEPTH - p.x() < Param::Field::PENALTY_AREA_WIDTH / 2 - p.y())
			// ¸üÕýµ½½ûÇøÓÒ²à
				return CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + paramManager->PENALTY_AREA_DEPTH + buffer, p.y());
			// ¸üÕýµ½½ûÇøÉÏ·½
			else return CGeoPoint(p.x(), Param::Field::PENALTY_AREA_WIDTH / 2 + buffer);
		}
		else {
			// ¸ù¾Ýµ½½ûÇøÓÒ²à½ü»¹ÊÇµ½½ûÇøÏÂ·½½üÀ´Ñ¡Ôñ
			if (-Param::Field::PITCH_LENGTH / 2 + paramManager->PENALTY_AREA_DEPTH - p.x() < p.y() - (-Param::Field::PENALTY_AREA_WIDTH / 2))
			// ¸üÕýµ½½ûÇøÓÒ²à	
				return CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + paramManager->PENALTY_AREA_DEPTH + buffer, p.y());
			// ¸üÕýµ½½ûÇøÏÂ·½
			else return CGeoPoint(p.x(), -Param::Field::PENALTY_AREA_WIDTH / 2 - buffer);
		}
	}

	// ½«ÅÜÎ»µã¸üÕýµ½µÐ·½½ûÇøÒÔÍâ. Modified by HXY.
	CGeoPoint MakeOutOfTheirPenaltyArea(const CGeoPoint& p, const double buffer) {
		// Èç¹ûÔÚÖ´ÐÐ·ÅÇò£¬²»ÐèÒª¸üÕý
		if (WorldModel::Instance()->CurrentRefereeMsg() == "ourBallPlacement")
			return p;
		
		if (p.y() > 0) {
			// ¸ù¾Ýµ½½ûÇø×ó²à½ü»¹ÊÇµ½½ûÇøÉÏ·½½üÀ´Ñ¡Ôñ
			if (p.x() - Param::Field::PITCH_LENGTH / 2 + paramManager->PENALTY_AREA_DEPTH < Param::Field::PENALTY_AREA_WIDTH / 2 - p.y())
			// ¸üÕýµ½½ûÇø×ó²à
				return CGeoPoint(Param::Field::PITCH_LENGTH / 2 - paramManager->PENALTY_AREA_DEPTH - buffer, p.y());
			// ¸üÕýµ½½ûÇøÉÏ·½
			else return CGeoPoint(p.x(), Param::Field::PENALTY_AREA_WIDTH / 2 + buffer);
		}
		else {
			// ¸ù¾Ýµ½½ûÇø×ó²à½ü»¹ÊÇµ½½ûÇøÏÂ·½½üÀ´Ñ¡Ôñ
			if (p.x() - Param::Field::PITCH_LENGTH / 2 + paramManager->PENALTY_AREA_DEPTH < Param::Field::PENALTY_AREA_WIDTH / 2 + p.y())
			// ¸üÕýµ½½ûÇø×ó²à	
				return CGeoPoint(Param::Field::PITCH_LENGTH / 2 - paramManager->PENALTY_AREA_DEPTH - buffer, p.y());
			// ¸üÕýµ½½ûÇøÏÂ·½
			else return CGeoPoint(p.x(), -Param::Field::PENALTY_AREA_WIDTH / 2 - buffer);
		}
		/**
		CGeoPoint fixPoint = p;
		while (Utils::InTheirPenaltyArea(fixPoint, buffer)) { //ÐÞÕý³ö½ûÇø
			fixPoint = fixPoint + Utils::Polar2Vector(1, (fixPoint - CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0)).dir());
		}
		return fixPoint;
		**/
	}

	CGeoPoint MakeOutOfCircle(const CGeoPoint& center, const double radius, const CGeoPoint& target, const double buffer, const bool isBack, const CGeoPoint& mePos, const CVector adjustVec) {
		CGeoPoint p(target);
		CVector adjustDir;
		if (isBack) {
			adjustDir = mePos - target;
		}
		else if (adjustVec.x() < 1e4)
			adjustDir = adjustVec;
		else {
			adjustDir = target - center;
			if (adjustDir.mod() < Param::Vehicle::V2::PLAYER_SIZE / 2.0)
				adjustDir = mePos - target;
		}

		adjustDir = adjustDir / adjustDir.mod();
		double adjustUnit = 0.5;
		while (p.dist(center) < radius + buffer)
			p = p + adjustDir * adjustUnit;
		return p;
	}

	CGeoPoint MakeOutOfLongCircle(const CGeoPoint& seg_start, const CGeoPoint& seg_end, const double radius, const CGeoPoint& target, const double buffer, const CVector adjustVec) {
		CGeoSegment segment(seg_start, seg_end);
		CGeoPoint p(target);
		CGeoPoint nearPoint = (seg_start.dist(target) < seg_end.dist(target) ? seg_start : seg_end);
		CVector adjustDir = target - nearPoint;
		if (adjustDir.x() < 1e4)
			adjustDir = adjustVec;
		adjustDir = adjustDir / adjustDir.mod();
		double adjustUnit = 0.5;
		while (segment.dist2Point(p) < radius + buffer)
			p = p + adjustDir * adjustUnit;
		return p;
	}

	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
	CGeoPoint MakeOutOfRectangle(const CGeoPoint &recP1, const CGeoPoint &recP2, const CGeoPoint &target, const double buffer) {
		double leftBound = min(recP1.x(), recP2.x());
		double rightBound = max(recP1.x(), recP2.x());
		double upperBound = max(recP1.y(), recP2.y());
		double lowerBound = min(recP1.y(), recP2.y());
		double middleY = (upperBound + lowerBound) / 2.0;
		double middleX = (leftBound + rightBound) / 2.0;

		CGeoPoint targetNew = target;
		if (targetNew.y() < upperBound + buffer &&
			targetNew.y() > lowerBound - buffer &&
			targetNew.x() > leftBound - buffer &&
			targetNew.x() < rightBound + buffer) {
			if (fabs(middleX) < Param::Field::PITCH_LENGTH / 2 + Param::Field::GOAL_DEPTH * 2.0 / 3.0) { //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
				double xInside = copysign(min(fabs(leftBound), fabs(rightBound)), leftBound);
				double yInside = copysign(min(fabs(upperBound), fabs(lowerBound)), lowerBound);
				double yOutside = copysign(max(fabs(upperBound), fabs(lowerBound)), lowerBound);
				if (fabs(targetNew.x()) < fabs(xInside)) {
					targetNew.setX(xInside - copysign(buffer, xInside));
				}
				else if (fabs(targetNew.y()) < fabs(yInside)) {
					targetNew.setY(yInside - copysign(buffer, yInside));
				}
				else if (fabs(targetNew.y()) > fabs(yOutside)) {
					targetNew.setY(yInside + copysign(buffer, yOutside));
				}
				else if (fabs(targetNew.y()) < fabs(middleY)) { //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í·ï¿½ï¿½æ£¬Êµï¿½Ê²ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
					targetNew.setY(yInside - copysign(buffer, yInside));
				}
				else {
					targetNew.setY(yInside + copysign(buffer, yOutside));
				}
			}
			else { //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
				double xInside = copysign(min(fabs(leftBound), fabs(rightBound)), leftBound);
				if (fabs(targetNew.x()) < fabs(xInside)) {
					targetNew.setX(xInside - copysign(buffer, xInside));
				}
				else if (targetNew.y() < lowerBound) {
					targetNew.setY(lowerBound - buffer);
				}
				else if (targetNew.y() > upperBound) {
					targetNew.setY(upperBound + buffer);
				}
				else if (targetNew.y() < 0) { //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í·ï¿½ï¿½æ£¬Êµï¿½Ê²ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
					targetNew.setY(lowerBound - buffer);
				}
				else {
					targetNew.setY(upperBound + buffer);
				}
			}
		}


		return targetNew;
	}


	CGeoPoint MakeOutOfCircleAndInField(const CGeoPoint& center, const double radius, const CGeoPoint& p, const double buffer)
	{
		const CVector p2c = p - center;
		const double dist = p2c.mod();
		if (dist > radius + buffer || dist < 0.01) { // ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½
			return p;
		}
		CGeoPoint newPos(center + p2c * (radius + buffer) / dist);
		CGeoRectangle fieldRect(FieldLeft() + buffer, FieldTop() + buffer, FieldRight() - buffer, FieldBottom() - buffer);
		if (!fieldRect.HasPoint(newPos)) { // ï¿½Ú³ï¿½ï¿½ï¿½,Ñ¡ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò²ï¿½ï¿½ï¿½Ô²ï¿½ÚµÄ³ï¿½ï¿½Úµï¿½
			CGeoCirlce avoidCircle(center, radius + buffer);
			std::vector< CGeoPoint > intPoints;
			for (int i = 0; i < 4; ++i) {
				CGeoLine fieldLine(fieldRect._point[i % 4], fieldRect._point[(i + 1) % 4]);
				CGeoLineCircleIntersection fieldLineCircleInt(fieldLine, avoidCircle);
				if (fieldLineCircleInt.intersectant()) {
					intPoints.push_back(fieldLineCircleInt.point1());
					intPoints.push_back(fieldLineCircleInt.point2());
				}
			}
			double minDist = 1000.0;
			CGeoPoint minPoint = newPos;
			for (unsigned int i = 0; i < intPoints.size(); ++i) {
				double cDist = p.dist(intPoints[i]);
				if (cDist < minDist) {
					minDist = cDist;
					minPoint = intPoints[i];
				}
			}
			return minPoint;
		}

		return newPos; // Ô²ï¿½ï¿½ï¿½ï¿½ï¿½pï¿½ï¿½ï¿½ï¿½Äµï¿?
	}


	bool PlayerNumValid(int num)
	{
		if (num >= 0 && num < Param::Field::MAX_PLAYER) {
			return true;
		}
		else {
			return false;
		}
	}
	// ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÏµÄµï¿½, Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½(ï¿½Ç¶ï¿½), ï¿½Ò³ï¿½Ò»ï¿½ï¿½ï¿½Ú½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ø¸Ã·ï¿½ï¿½ï¿½ï¿½
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ß½Ï½ï¿½ï¿½Äµï¿?
	CGeoPoint GetOutSidePenaltyPos(double dir, double delta, const CGeoPoint targetPoint)
	{
		//double delta = Param::Field::MAX_PLAYER_SIZE + 1.5;
		CGeoPoint pInter = GetInterPos(dir, targetPoint);
		CGeoPoint pDefend = pInter + Polar2Vector(delta, dir);
		return pDefend;
	}

	CGeoPoint GetOutTheirSidePenaltyPos(double dir, double delta, const CGeoPoint& targetPoint) {
		CGeoPoint pInter = GetTheirInterPos(dir, targetPoint);
		return (pInter + Polar2Vector(delta, dir));
	}

	// GetDefendPosï¿½Ä´ï¿½ï¿½ï¿½Ï¸ï¿½ï¿½
	// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í·ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í½ï¿½ï¿½ï¿½ï¿½ßµÄ½ï¿½ï¿½ï¿?
	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ú½ï¿½ï¿½ï¿½ï¿½ï¿½
	//modified by Wang in 2018/3/17
	CGeoPoint GetInterPos(double dir, const CGeoPoint targetPoint) {
		using namespace Param::Field;
		if (IF_USE_ELLIPSE) {
			// ellipse penalty
			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½,ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½Ê¾
			CGeoCirlce c1(CGeoPoint(-PITCH_LENGTH / 2, PENALTY_AREA_L / 2), PENALTY_AREA_R);
			CGeoCirlce c2(CGeoPoint(-PITCH_LENGTH / 2, -PENALTY_AREA_L / 2), PENALTY_AREA_R);
			CGeoPoint targetPointInstead = targetPoint;
			if (dir >= Param::Math::PI / 2 - 5 / 180 * Param::Math::PI && dir <= Param::Math::PI)
				return CGeoPoint(-PITCH_LENGTH / 2, PENALTY_AREA_L / 2 + PENALTY_AREA_R);
			else if (dir <= -Param::Math::PI / 2 + 5 / 180 * Param::Math::PI && dir >= -Param::Math::PI)
				return CGeoPoint(-PITCH_LENGTH / 2, -PENALTY_AREA_L / 2 - PENALTY_AREA_R);

			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½Ö±ï¿½ï¿½(pLine),ï¿½ï¿½Ö±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¾
			CGeoPoint pend1(-PITCH_LENGTH / 2 + PENALTY_AREA_R, PENALTY_AREA_L / 2);
			CGeoPoint pend2(-PITCH_LENGTH / 2 + PENALTY_AREA_R, -PENALTY_AREA_L / 2);
			CGeoLine pLine(pend1, pend2);
			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Äµï¿½Í·ï¿½ï¿½ï¿? ï¿½ï¿½Ò»ï¿½ï¿½Ö±ï¿½ï¿½
			CGeoLine dirLine(targetPointInstead, dir);

			// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½c1ï¿½Ä½ï¿½ï¿½ï¿½
			if (targetPoint.y() == c1.Center().y())
			{
				if (dir >= 0 && dir < Param::Math::PI / 2)
				{
					CGeoPoint p = c1.Center() + Polar2Vector(PENALTY_AREA_R, dir);
					return p;
				}
			}
			else {
				CGeoLineCircleIntersection dirLine_c1_inter(dirLine, c1);
				if (dirLine_c1_inter.intersectant())
				{
					CGeoPoint p1 = dirLine_c1_inter.point1();
					CGeoPoint p2 = dirLine_c1_inter.point2();
					double dir1 = Normalize((p1 - c1.Center()).dir());
					double dir2 = Normalize((p2 - c1.Center()).dir());
					if (dir1 >= 0 && dir1 <= Param::Math::PI / 2)
					{
						return p1;

					}
					else if (dir2 >= 0 && dir2 <= Param::Math::PI / 2)
					{
						return p2;

					}
				}
			}

			// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½c2ï¿½Ä½ï¿½ï¿½ï¿½
			if (targetPoint.y() == c2.Center().y())
			{
				if (dir <= 0 && dir > (-Param::Math::PI / 2))
				{
					CGeoPoint p = c2.Center() + Polar2Vector(PENALTY_AREA_R, dir);
					return p;
				}
			}
			else {
				CGeoLineCircleIntersection dirLine_c2_inter(dirLine, c2);
				if (dirLine_c2_inter.intersectant())
				{
					CGeoPoint p1 = dirLine_c2_inter.point1();
					CGeoPoint p2 = dirLine_c2_inter.point2();
					double dir1 = Normalize((p1 - c2.Center()).dir());
					double dir2 = Normalize((p2 - c2.Center()).dir());
					if (dir1 >= (-Param::Math::PI / 2) && dir1 <= 0)
					{
						return p1;

					}
					else if (dir2 >= (-Param::Math::PI / 2) && dir2 <= 0)
					{
						return p2;

					}
				}
			}
			// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½ï¿½ß¶ï¿½pLineï¿½Ä½ï¿½ï¿½ï¿½
			CGeoLineLineIntersection pline_dirline_inter(pLine, dirLine);
			if (pline_dirline_inter.Intersectant())
			{
				CGeoPoint p = pline_dirline_inter.IntersectPoint();
				if (p.y() <= pend1.y() && p.y() >= pend2.y())
				{
					return p;

				}
			}
			//// ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½Ä¬ï¿½Ïµï¿½,ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ðµï¿½
//            std::cout<<"our default pos!!"<<std::endl;
			return CGeoPoint(-PITCH_LENGTH / 2 + PENALTY_AREA_R, 0);
		}
		else {
			// rectangle penalty
			CGeoPoint p1(-PITCH_LENGTH / 2, -PENALTY_AREA_WIDTH / 2);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			CGeoPoint p2(-PITCH_LENGTH / 2 + PENALTY_AREA_DEPTH, -PENALTY_AREA_WIDTH / 2);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			CGeoPoint p3(-PITCH_LENGTH / 2 + PENALTY_AREA_DEPTH, PENALTY_AREA_WIDTH / 2);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			CGeoPoint p4(-PITCH_LENGTH / 2, PENALTY_AREA_WIDTH / 2);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			CGeoLine line1(p1, p2);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
			CGeoLine line2(p2, p3);//ï¿½ï¿½ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½
			CGeoLine line3(p3, p4);//ï¿½ï¿½ï¿½ï¿½ï¿½Ò±ï¿½ï¿½ï¿½
			CGeoLine dirLine(targetPoint, dir);

			CGeoLineLineIntersection inter1(line1, dirLine);
			CGeoLineLineIntersection inter2(line2, dirLine);
			CGeoLineLineIntersection inter3(line3, dirLine);

			CGeoPoint inter_p1 = inter1.IntersectPoint();
			GDebugEngine::Instance()->gui_debug_x(inter_p1, 3);//ï¿½ï¿½
			CGeoPoint inter_p2 = inter2.IntersectPoint();
			GDebugEngine::Instance()->gui_debug_x(inter_p2, 4);//ï¿½ï¿½
			CGeoPoint inter_p3 = inter3.IntersectPoint();
			GDebugEngine::Instance()->gui_debug_x(inter_p3, 9);//ï¿½ï¿½
			CGeoPoint returnPoint = targetPoint;//ï¿½ï¿½ï¿½ï¿½Öµ

			//if (targetPoint.x() >= -PITCH_LENGTH / 2 + PENALTY_AREA_DEPTH) {
			if (targetPoint.y() <= 0) {//case 1
				if (InOurPenaltyArea(inter_p1, 10)) returnPoint = inter_p1;
				else returnPoint = inter_p2;
			}
			else {//case 2
				if (InOurPenaltyArea(inter_p3, 10)) returnPoint = inter_p3;
				else returnPoint = inter_p2;//ï¿½ï¿½ï¿½Ñ¡ï¿½ï¿?
			}
			GDebugEngine::Instance()->gui_debug_x(returnPoint, 0);
			CGeoPoint p0(-PITCH_LENGTH / 2, 0);
			GDebugEngine::Instance()->gui_debug_line(returnPoint, p0, 0);
			return returnPoint;
		}
		//}
		/*
		else if (std::fabs(targetPoint.y()) <= PENALTY_AREA_WIDTH / 2) {//case 3
			if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
			else return p2;//ï¿½ï¿½ï¿½Ñ¡ï¿½ï¿?
		}
		else {
			if (targetPoint.y() <= 0) {//case 4
				if (InOurPenaltyArea(inter_p1, 0)) return inter_p1;
				else if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
				else return p2;//ï¿½ï¿½ï¿½Ñ¡ï¿½ï¿?
			}
			else {//case 5
				if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
				else if (InOurPenaltyArea(inter_p3, 0)) return inter_p3;
				else return p3;//ï¿½ï¿½ï¿½Ñ¡ï¿½ï¿?
			}
		}
		*/
	}
	//modified by Wang in 2018/3/17
	CGeoPoint GetTheirInterPos(double dir, const CGeoPoint& targetPoint) {
		using namespace Param::Field;
		if (IF_USE_ELLIPSE) {
			// ellipse penalty
			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½,ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½Ê¾
			CGeoCirlce c1(CGeoPoint(-PITCH_LENGTH / 2, PENALTY_AREA_L / 2), PENALTY_AREA_R);
			CGeoCirlce c2(CGeoPoint(-PITCH_LENGTH / 2, -PENALTY_AREA_L / 2), PENALTY_AREA_R);
			CGeoPoint targetPointInstead = targetPoint;
			if (dir >= Param::Math::PI / 2 - 5 / 180 * Param::Math::PI && dir <= Param::Math::PI)
				return CGeoPoint(-PITCH_LENGTH / 2, PENALTY_AREA_L / 2 + PENALTY_AREA_R);
			else if (dir <= -Param::Math::PI / 2 + 5 / 180 * Param::Math::PI && dir >= -Param::Math::PI)
				return CGeoPoint(-PITCH_LENGTH / 2, -PENALTY_AREA_L / 2 - PENALTY_AREA_R);

			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½Ö±ï¿½ï¿½(pLine),ï¿½ï¿½Ö±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¾
			CGeoPoint pend1(-PITCH_LENGTH / 2 + PENALTY_AREA_R, PENALTY_AREA_L / 2);
			CGeoPoint pend2(-PITCH_LENGTH / 2 + PENALTY_AREA_R, -PENALTY_AREA_L / 2);
			CGeoLine pLine(pend1, pend2);
			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Äµï¿½Í·ï¿½ï¿½ï¿? ï¿½ï¿½Ò»ï¿½ï¿½Ö±ï¿½ï¿½
			CGeoLine dirLine(targetPointInstead, dir);

			// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½c1ï¿½Ä½ï¿½ï¿½ï¿½
			if (targetPoint.y() == c1.Center().y())
			{
				if (dir >= 0 && dir < Param::Math::PI / 2)
				{
					CGeoPoint p = c1.Center() + Polar2Vector(PENALTY_AREA_R, dir);
					return p;
				}
			}
			else {
				CGeoLineCircleIntersection dirLine_c1_inter(dirLine, c1);
				if (dirLine_c1_inter.intersectant())
				{
					CGeoPoint p1 = dirLine_c1_inter.point1();
					CGeoPoint p2 = dirLine_c1_inter.point2();
					double dir1 = Normalize((p1 - c1.Center()).dir());
					double dir2 = Normalize((p2 - c1.Center()).dir());
					if (dir1 >= 0 && dir1 <= Param::Math::PI / 2)
					{
						return p1;

					}
					else if (dir2 >= 0 && dir2 <= Param::Math::PI / 2)
					{
						return p2;

					}
				}
			}

			// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½c2ï¿½Ä½ï¿½ï¿½ï¿½
			if (targetPoint.y() == c2.Center().y())
			{
				if (dir <= 0 && dir > (-Param::Math::PI / 2))
				{
					CGeoPoint p = c2.Center() + Polar2Vector(PENALTY_AREA_R, dir);
					return p;
				}
			}
			else {
				CGeoLineCircleIntersection dirLine_c2_inter(dirLine, c2);
				if (dirLine_c2_inter.intersectant())
				{
					CGeoPoint p1 = dirLine_c2_inter.point1();
					CGeoPoint p2 = dirLine_c2_inter.point2();
					double dir1 = Normalize((p1 - c2.Center()).dir());
					double dir2 = Normalize((p2 - c2.Center()).dir());
					if (dir1 >= (-Param::Math::PI / 2) && dir1 <= 0)
					{
						return p1;

					}
					else if (dir2 >= (-Param::Math::PI / 2) && dir2 <= 0)
					{
						return p2;

					}
				}
			}
			// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½ï¿½ß¶ï¿½pLineï¿½Ä½ï¿½ï¿½ï¿½
			CGeoLineLineIntersection pline_dirline_inter(pLine, dirLine);
			if (pline_dirline_inter.Intersectant())
			{
				CGeoPoint p = pline_dirline_inter.IntersectPoint();
				if (p.y() <= pend1.y() && p.y() >= pend2.y())
				{
					return p;

				}
			}
			//// ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½Ä¬ï¿½Ïµï¿½,ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ðµï¿½
//            std::cout<<"our default pos!!"<<std::endl;
			return CGeoPoint(-PITCH_LENGTH / 2 + PENALTY_AREA_R, 0);
		}
		else {
			// rectangle penalty
			CGeoPoint p1(PITCH_LENGTH / 2, -PENALTY_AREA_WIDTH / 2);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			CGeoPoint p2(PITCH_LENGTH / 2 - PENALTY_AREA_DEPTH, -PENALTY_AREA_WIDTH / 2);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			CGeoPoint p3(PITCH_LENGTH / 2 - PENALTY_AREA_DEPTH, PENALTY_AREA_WIDTH / 2);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			CGeoPoint p4(PITCH_LENGTH / 2, PENALTY_AREA_WIDTH / 2);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			CGeoLine line1(p1, p2);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
			CGeoLine line2(p2, p3);//ï¿½ï¿½ï¿½ï¿½ï¿½Â±ï¿½ï¿½ï¿½
			CGeoLine line3(p3, p4);//ï¿½ï¿½ï¿½ï¿½ï¿½Ò±ï¿½ï¿½ï¿½
			CGeoLine dirLine(targetPoint, dir);

			CGeoLineLineIntersection inter1(line1, dirLine);
			CGeoLineLineIntersection inter2(line2, dirLine);
			CGeoLineLineIntersection inter3(line3, dirLine);

			CGeoPoint inter_p1 = inter1.IntersectPoint();
			CGeoPoint inter_p2 = inter2.IntersectPoint();
			CGeoPoint inter_p3 = inter3.IntersectPoint();
			CGeoPoint returnPoint = targetPoint;//ï¿½ï¿½ï¿½ï¿½Öµ

			if (targetPoint.x() >= PITCH_LENGTH / 2 - PENALTY_AREA_DEPTH) {
				if (targetPoint.y() <= 0) {//case 1
					if (InOurPenaltyArea(inter_p1, 0)) return inter_p1;
					else return p2;//ï¿½ï¿½ï¿½Ñ¡ï¿½ï¿?
				}
				else {//case 2
					if (InOurPenaltyArea(inter_p3, 0)) return inter_p3;
					else return p3;//ï¿½ï¿½ï¿½Ñ¡ï¿½ï¿?
				}
			}
			else if (std::fabs(targetPoint.y()) <= PENALTY_AREA_WIDTH / 2) {//case 3
				if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
				else return p2;//ï¿½ï¿½ï¿½Ñ¡ï¿½ï¿?
			}
			else {
				if (targetPoint.y() <= 0) {//case 4
					if (InOurPenaltyArea(inter_p1, 0)) return inter_p1;
					else if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
					else return p2;//ï¿½ï¿½ï¿½Ñ¡ï¿½ï¿?
				}
				else {//case 5
					if (InOurPenaltyArea(inter_p2, 0)) return inter_p2;
					else if (InOurPenaltyArea(inter_p3, 0)) return inter_p3;
					else return p3;//ï¿½ï¿½ï¿½Ñ¡ï¿½ï¿?
				}
			}
		}
	}
	/*
	CGeoPoint GetInterPos(double dir, const CGeoPoint targetPoint)
	{
		using namespace Param::Field;
		if (Param::Rule::Version == 2008)
		{
			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½,ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½Ê¾
			CGeoCirlce c1(CGeoPoint(-PITCH_LENGTH/2,  PENALTY_AREA_L/2), PENALTY_AREA_R);
			CGeoCirlce c2(CGeoPoint(-PITCH_LENGTH/2, -PENALTY_AREA_L/2), PENALTY_AREA_R);
			CGeoPoint targetPointInstead = targetPoint;
			if (dir >= Param::Math::PI/2 - 5/180*Param::Math::PI && dir <= Param::Math::PI)
		return CGeoPoint(-PITCH_LENGTH/2,PENALTY_AREA_L/2+PENALTY_AREA_R);
			else if (dir <= -Param::Math::PI/2 + 5/180*Param::Math::PI && dir >= -Param::Math::PI)
				return CGeoPoint(-PITCH_LENGTH/2,-PENALTY_AREA_L/2-PENALTY_AREA_R);

			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½Ö±ï¿½ï¿½(pLine),ï¿½ï¿½Ö±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¾
			CGeoPoint pend1(-PITCH_LENGTH/2+PENALTY_AREA_R,  PENALTY_AREA_L/2);
			CGeoPoint pend2(-PITCH_LENGTH/2+PENALTY_AREA_R, -PENALTY_AREA_L/2);
			CGeoLine pLine(pend1, pend2);
			// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Äµï¿½Í·ï¿½ï¿½ï¿? ï¿½ï¿½Ò»ï¿½ï¿½Ö±ï¿½ï¿½
			CGeoLine dirLine(targetPointInstead, dir);

			// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½c1ï¿½Ä½ï¿½ï¿½ï¿½
			if (targetPoint.y() == c1.Center().y())
			{
				if (dir>=0 && dir<Param::Math::PI/2)
				{
					CGeoPoint p = c1.Center()+Polar2Vector(PENALTY_AREA_R,dir);
					return p;
				}
			}
			else{
				CGeoLineCircleIntersection dirLine_c1_inter(dirLine, c1);
				if (dirLine_c1_inter.intersectant())
				{
					CGeoPoint p1 = dirLine_c1_inter.point1();
					CGeoPoint p2 = dirLine_c1_inter.point2();
					double dir1 = Normalize((p1-c1.Center()).dir());
					double dir2 = Normalize((p2-c1.Center()).dir());
					if (dir1>=0 && dir1<=Param::Math::PI/2)
					{
						return p1;

					}
					else if (dir2>=0 && dir2<=Param::Math::PI/2)
					{
						return p2;

					}
				}
			}

			// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½c2ï¿½Ä½ï¿½ï¿½ï¿½
			if (targetPoint.y() == c2.Center().y())
			{
				if ( dir<=0 && dir>(-Param::Math::PI/2))
				{
					CGeoPoint p = c2.Center()+Polar2Vector(PENALTY_AREA_R,dir);
					return p;
				}
			}
			else{
				CGeoLineCircleIntersection dirLine_c2_inter(dirLine, c2);
				if (dirLine_c2_inter.intersectant())
				{
					CGeoPoint p1 = dirLine_c2_inter.point1();
					CGeoPoint p2 = dirLine_c2_inter.point2();
					double dir1 = Normalize((p1-c2.Center()).dir());
					double dir2 = Normalize((p2-c2.Center()).dir());
					if (dir1>=(-Param::Math::PI/2) && dir1<=0)
					{
						return p1;

					}
					else if (dir2>=(-Param::Math::PI/2) && dir2<=0)
					{
						return p2;

					}
				}
			}
			// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½ï¿½ß¶ï¿½pLineï¿½Ä½ï¿½ï¿½ï¿½
			CGeoLineLineIntersection pline_dirline_inter(pLine, dirLine);
			if (pline_dirline_inter.Intersectant())
			{
				CGeoPoint p = pline_dirline_inter.IntersectPoint();
				if (p.y() <= pend1.y() && p.y() >= pend2.y())
				{
					return p;

				}
			}
			//// ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½Ä¬ï¿½Ïµï¿½,ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ðµï¿½
			std::cout<<"our default pos!!"<<std::endl;
			return CGeoPoint(-PITCH_LENGTH/2+PENALTY_AREA_R, 0);
	}
		else if (Param::Rule::Version == 2004)
		{
			CGeoCirlce penaltyCircle(CGeoPoint(-PITCH_LENGTH/2, 0),PENALTY_AREA_WIDTH/2);
			CGeoLine dirLine(targetPoint,dir);
			CGeoLineCircleIntersection dirLine_penaltyCircle(dirLine,penaltyCircle);
			if (dirLine_penaltyCircle.intersectant())
			{
				CGeoPoint p = !Utils::IsInField(dirLine_penaltyCircle.point1())?dirLine_penaltyCircle.point2():dirLine_penaltyCircle.point1();
				return p;
			}
		}
		return CGeoPoint(-PITCH_LENGTH/2+PENALTY_AREA_WIDTH/2, 0);
	}

	CGeoPoint GetTheirInterPos(double dir, const CGeoPoint& targetPoint) {
		using namespace Param::Field;
		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½,ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½Ê¾
		CGeoCirlce c1(CGeoPoint(PITCH_LENGTH/2, PENALTY_AREA_L/2), PENALTY_AREA_R);
		CGeoCirlce c2(CGeoPoint(PITCH_LENGTH/2, -PENALTY_AREA_L/2), PENALTY_AREA_R);
		if (dir <= Param::Math::PI/2 + 5/180*Param::Math::PI && dir >= 0)
			return CGeoPoint(PITCH_LENGTH/2, PENALTY_AREA_L/2 + PENALTY_AREA_R);
		else if	 (dir >= -Param::Math::PI - 5/180*Param::Math::PI	&& dir <= 0)
			return CGeoPoint(PITCH_LENGTH/2, -(PENALTY_AREA_L/2 + PENALTY_AREA_R));

		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½Ö±ï¿½ï¿½(pLine),ï¿½ï¿½Ö±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¾
		CGeoPoint pend1(PITCH_LENGTH/2 - PENALTY_AREA_R, PENALTY_AREA_L/2);
		CGeoPoint pend2(PITCH_LENGTH/2 - PENALTY_AREA_R, -PENALTY_AREA_L/2);
		CGeoLine pLine(pend1, pend2);
		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Äµï¿½Í·ï¿½ï¿½ï¿? ï¿½ï¿½Ò»ï¿½ï¿½Ö±ï¿½ï¿½
		CGeoLine dirLine(targetPoint, dir);

		// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½c1ï¿½Ä½ï¿½ï¿½ï¿½
		if (abs(targetPoint.y() - c1.Center().y()) < 0.0001) {
			if (dir > Param::Math::PI/2 && dir < Param::Math::PI) {
				CGeoPoint p = c1.Center() + Polar2Vector(PENALTY_AREA_R, dir);
				return p;
			}
		} else {
			CGeoLineCircleIntersection dirLine_c1_inter(dirLine, c1);
			if (dirLine_c1_inter.intersectant()) {
				CGeoPoint p1 = dirLine_c1_inter.point1();
				CGeoPoint p2 = dirLine_c1_inter.point2();
				double dir1 = Normalize((p1-c1.Center()).dir());
				double dir2 = Normalize((p2-c1.Center()).dir());
				if (dir1 >= Param::Math::PI / 2 && dir1 <= Param::Math::PI)
					return p1;
				else if (dir2 >= Param::Math::PI / 2 && dir2 <= Param::Math::PI)
					return p2;
			}
		}
		// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½c2ï¿½Ä½ï¿½ï¿½ï¿½
		if (abs(targetPoint.y() - c2.Center().y()) < 0.0001) {
			if (dir < -Param::Math::PI/2 && dir > -Param::Math::PI) {
				CGeoPoint p = c2.Center() + Polar2Vector(PENALTY_AREA_R, dir);
				return p;
			}
		} else {
			CGeoLineCircleIntersection dirLine_c2_inter(dirLine, c2);
			if (dirLine_c2_inter.intersectant()) {
				CGeoPoint p1 = dirLine_c2_inter.point1();
				CGeoPoint p2 = dirLine_c2_inter.point2();
				double dir1 = Normalize((p1-c2.Center()).dir());
				double dir2 = Normalize((p2-c2.Center()).dir());
				if (dir1 <= -Param::Math::PI/2 && dir1 >= -Param::Math::PI)
					return p1;
				else if (dir2 <= -Param::Math::PI/2 && dir2 >= -Param::Math::PI)
					return p2;
			}
		}
		// ï¿½ï¿½ï¿½Ö±ï¿½ßºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô²ï¿½ï¿½ï¿½ï¿½ï¿½ß¶ï¿½pLineï¿½Ä½ï¿½ï¿½ï¿½
		CGeoLineLineIntersection pline_dirline_inter(pLine, dirLine);
		if (pline_dirline_inter.Intersectant()) {
			CGeoPoint p = pline_dirline_inter.IntersectPoint();
			if (p.y() <= pend1.y() && p.y() >= pend2.y())
				return p;
		}
		//// ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½Ä¬ï¿½Ïµï¿½,ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ðµï¿½
		std::cout<<"our default pos!!"<<std::endl;
		return CGeoPoint(PITCH_LENGTH / 2 - PENALTY_AREA_R, 0);
	}
	*/
	float SquareRootFloat(float number) {
		long i;
		float x, y;
		const float f = 1.5F;

		x = number * 0.5F;
		y = number;
		i = *(long *)&y;
		i = 0x5f3759df - (i >> 1);
		y = *(float *)&i;
		y = y * (f - (x * y * y));
		y = y * (f - (x * y * y));
		return number * y;
	}
	bool canGo(const CVisionModule* pVision, const int vecNumber, const CGeoPoint& target, const int flags, const double avoidBuffer)//ï¿½Ð¶ï¿½ï¿½Ç·ï¿½ï¿½ï¿½ï¿½Ö±ï¿½Óµï¿½ï¿½ï¿½Ä¿ï¿½ï¿½ï¿½
	{
		static bool _canGo = true;
		const CGeoPoint& vecPos = pVision->OurPlayer(vecNumber).Pos();
		CGeoSegment moving_seg(vecPos, target);
		const double minBlockDist2 = (Param::Field::MAX_PLAYER_SIZE / 2 + avoidBuffer) * (Param::Field::MAX_PLAYER_SIZE / 2 + avoidBuffer);
		for (int i = 0; i < Param::Field::MAX_PLAYER * 2; ++i) { // ï¿½ï¿½Â·ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ã»ï¿½ï¿½ï¿½ï¿½
			if (i == vecNumber || !pVision->AllPlayer(i).Valid()) {
				continue;
			}
			const CGeoPoint& obs_pos = pVision->AllPlayer(i).Pos();
			if ((obs_pos - target).mod2() < minBlockDist2) {
				_canGo = false;
				return _canGo;
			}
			CGeoPoint prj_point = moving_seg.projection(obs_pos);
			if (moving_seg.IsPointOnLineOnSegment(prj_point)) {
				const double blockedDist2 = (obs_pos - prj_point).mod2();
				if (blockedDist2 < minBlockDist2 && blockedDist2 < (obs_pos - vecPos).mod2()) {
					_canGo = false;
					return _canGo;
				}
			}
		}
		if (_canGo && (flags & PlayerStatus::DODGE_BALL)) { // ï¿½ï¿½ï¿½ï¿½ï¿?
			const CGeoPoint& obs_pos = pVision->Ball().Pos();
			CGeoPoint prj_point = moving_seg.projection(obs_pos);
			if (obs_pos.dist(prj_point) < avoidBuffer + Param::Field::BALL_SIZE && moving_seg.IsPointOnLineOnSegment(prj_point)) {
				_canGo = false;
				return _canGo;
			}
		}
		if (_canGo && (flags & PlayerStatus::DODGE_OUR_DEFENSE_BOX)) { // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ë±¾ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
			if (Param::Rule::Version == 2003) {	// 2003ï¿½ï¿½Ä¹ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ç¾ï¿½ï¿½ï¿½
				CGeoRectangle defenseBox(-Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2 - avoidBuffer, -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_WIDTH + avoidBuffer, Param::Field::PENALTY_AREA_WIDTH / 2 + avoidBuffer);
				CGeoLineRectangleIntersection intersection(moving_seg, defenseBox);
				if (intersection.intersectant()) {
					if (moving_seg.IsPointOnLineOnSegment(intersection.point1()) || moving_seg.IsPointOnLineOnSegment(intersection.point2())) {
						_canGo = false; // Òªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
						return _canGo;
					}
				}
			}
			else if (Param::Rule::Version == 2004) { // 2004ï¿½ï¿½Ä¹ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ç°ï¿½Ô²ï¿½ï¿½
				CGeoCirlce defenseBox(CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0), Param::Field::PENALTY_AREA_WIDTH / 2 + avoidBuffer);
				CGeoLineCircleIntersection intersection(moving_seg, defenseBox);
				if (intersection.intersectant()) {
					if (moving_seg.IsPointOnLineOnSegment(intersection.point1()) || moving_seg.IsPointOnLineOnSegment(intersection.point2())) {
						_canGo = false; // Òªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
						return _canGo;
					}
				}
			}
			// 2019, china open, ellipse penalty
			else if (Param::Rule::Version == 2019 &&
				Param::Field::IF_USE_ELLIPSE) {
				CGeoCirlce c1(CGeoPoint(-Param::Field::PITCH_LENGTH / 2,
					Param::Field::PENALTY_AREA_L / 2),
					Param::Field::PENALTY_AREA_R + avoidBuffer);
				CGeoCirlce c2(CGeoPoint(-Param::Field::PITCH_LENGTH / 2,
					-Param::Field::PENALTY_AREA_L / 2),
					Param::Field::PENALTY_AREA_R + avoidBuffer);
				CGeoRectangle defenseBox(
					-Param::Field::PITCH_LENGTH / 2 +
					Param::Field::PENALTY_AREA_R +
					avoidBuffer,
					-Param::Field::PENALTY_AREA_L / 2,
					-Param::Field::PITCH_LENGTH / 2,
					Param::Field::PENALTY_AREA_L / 2);
				CGeoLineCircleIntersection intersection1(moving_seg, c1);
				CGeoLineCircleIntersection intersection2(moving_seg, c2);
				CGeoLineRectangleIntersection intersection3(moving_seg,
					defenseBox);
				if (intersection1.intersectant() ||
					intersection2.intersectant() ||
					intersection3.intersectant()) {
					if (moving_seg.IsPointOnLineOnSegment(intersection1.point1()) ||
						moving_seg.IsPointOnLineOnSegment(intersection1.point2()) ||
						moving_seg.IsPointOnLineOnSegment(intersection2.point1()) ||
						moving_seg.IsPointOnLineOnSegment(intersection2.point2()) ||
						moving_seg.IsPointOnLineOnSegment(intersection3.point1()) ||
						moving_seg.IsPointOnLineOnSegment(intersection3.point2())) {
						_canGo = false; // Òªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
						return _canGo;
					}
				}

			}
			else {// 2018ï¿½ï¿½Ä¹ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ç¾ï¿½ï¿½ï¿½
				CGeoRectangle defenseBox(-Param::Field::PITCH_LENGTH / 2 + queryParamByName("data\\ssl\\params\\params.xml", "PENALTY_AREA_DEPTH") + avoidBuffer, -Param::Field::PENALTY_AREA_WIDTH / 2 - avoidBuffer, -Param::Field::PITCH_LENGTH / 2, Param::Field::PENALTY_AREA_WIDTH / 2 + avoidBuffer);
				CGeoLineRectangleIntersection intersection(moving_seg, defenseBox);
				if (intersection.intersectant()) {
					if (moving_seg.IsPointOnLineOnSegment(intersection.point1()) || moving_seg.IsPointOnLineOnSegment(intersection.point2())) {
						_canGo = false; // Òªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
						return _canGo;
					}
				}
			}
		}
		return _canGo;
	}

	bool isValidFlatPass(const CVisionModule *pVision, CGeoPoint start, CGeoPoint end, bool isShoot, bool ignoreCloseEnemy, bool ignoreTheirGuard) {
		// ï¿½Ð¶ï¿½ï¿½Ü·ï¿½ï¿½ï¿½Ä½Ç¶ï¿½ï¿½ï¿½ï¿½ï¿?
		static const double CLOSE_ANGLE_LIMIT = 8 * Param::Math::PI / 180;
		static const double FAR_ANGLE_LIMIT = 12 * Param::Math::PI / 180;
		static const double CLOSE_THRESHOLD = 50;
		static const double THEIR_ROBOT_INTER_THREADHOLD = 30;
		static const double SAFE_DIST = 50;
		static const double CLOSE_ENEMY_DIST = 50;

		bool valid = true;
		//        if(!isShoot){
		//            // Ê¹ï¿½ï¿½ï¿½ï¿½ï¿½Î½ï¿½ï¿½Ð¼ï¿½ï¿½ï¿½
		//            CVector passLine = end - start;
		//            double passDir = passLine.dir();
		//            for (int i = 0; i < Param::Field::MAX_PLAYER; ++i) {
		//                if(pVision->theirPlayer(i).Valid()){
		//                    if(ignoreCloseEnemy && pVision->theirPlayer(i).Pos().dist(start) < CLOSE_ENEMY_DIST) continue;
		//                    if(ignoreTheirGuard && Utils::InTheirPenaltyArea(pVision->theirPlayer(i).Pos(), 30)) continue;
		//                    CGeoPoint enemyPos = pVision->theirPlayer(i).Pos();
		//                    CVector enemyLine = enemyPos - start;
		//                    double enemyDir = enemyLine.dir();
		//                    // ï¿½ï¿½ï¿½ï¿½Ð·ï¿½ï¿½ï¿½ï¿½ë´«ï¿½ï¿½ï¿½ï¿½Â·ï¿½Ä²ï¿½ï¿½
		//                    double diffAngle = fabs(enemyDir - passDir);
		//                    diffAngle = diffAngle > Param::Math::PI ? 2*Param::Math::PI - diffAngle : diffAngle;
		//                    // ï¿½ï¿½ï¿½ã²¹ï¿½ï¿½ï¿½ï¿½
		//                    double compensateAngle = fabs(atan2(Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE, start.dist(enemyPos)));
		//        //            qDebug() << "compensate angle: " << enemyPos.x() << enemyPos.y() << enemyDir << passDir << compensateAngle;
		//                    double distanceToEnemy = start.dist(enemyPos);
		//                    double limit_angle = distanceToEnemy > CLOSE_THRESHOLD ? FAR_ANGLE_LIMIT : CLOSE_ANGLE_LIMIT;
		//        //            qDebug() << "limit_angle: " << i << diffAngle << distanceToEnemy << (distanceToEnemy > CLOSE_THRESHOLD) << limit_angle << (diffAngle < limit_angle);
		//                    if(diffAngle - compensateAngle < limit_angle && enemyPos.dist(start) < end.dist(start) + SAFE_DIST){
		//                        valid = false;
		//                        break;
		//                    }
		//                }
		//            }
		//        }
				// Ê¹ï¿½ï¿½Æ½ï¿½ï¿½ï¿½ß½ï¿½ï¿½Ð¼ï¿½ï¿½ã£¬ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Î¼ï¿½ï¿½ã²»×¼ï¿½ï¿½ï¿½ï¿?
		CGeoSegment BallLine(start, end);
		for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
			if (!pVision->TheirPlayer(i).Valid()) continue;
			if (ignoreCloseEnemy && pVision->TheirPlayer(i).Pos().dist(start) < CLOSE_ENEMY_DIST) continue;
			if (ignoreTheirGuard && Utils::InTheirPenaltyArea(pVision->TheirPlayer(i).Pos(), 30)) continue;
			CGeoPoint targetPos = pVision->TheirPlayer(i).Pos();
			double dist = BallLine.dist2Point(targetPos);
			if (dist < THEIR_ROBOT_INTER_THREADHOLD) {
				valid = false;
				break;
			}
		}
		return valid;
	}

	bool isValidChipPass(const CVisionModule *pVision, CGeoPoint start, CGeoPoint end) {
		// ï¿½Ð¶ï¿½ï¿½Ü·ï¿½ï¿½ï¿½Ä½Ç¶ï¿½ï¿½ï¿½ï¿½ï¿?
		static const double ANGLE_LIMIT = 5 * Param::Math::PI / 180;
		static const double CLOSE_SAFE_DIST = 50;
		static const double FAR_SAFE_DIST = 50;
		static const double FRONT_SAFE_DIST = 30;

		bool valid = true;
		// Ê¹ï¿½ï¿½ï¿½ï¿½ï¿½Î½ï¿½ï¿½Ð¼ï¿½ï¿½ï¿½
		CVector passLine = end - start;
		double passDir = passLine.dir();
		for (int i = 0; i < Param::Field::MAX_PLAYER; ++i) {
			if (pVision->TheirPlayer(i).Valid()) {
				CGeoPoint enemyPos = pVision->TheirPlayer(i).Pos();
				CVector enemyLine = enemyPos - start;
				double enemyDir = enemyLine.dir();
				// ï¿½ï¿½ï¿½ï¿½Ð·ï¿½ï¿½ï¿½ï¿½ë´«ï¿½ï¿½ï¿½ï¿½Â·ï¿½Ä²ï¿½ï¿½
				double diffAngle = fabs(enemyDir - passDir);
				diffAngle = diffAngle > Param::Math::PI ? 2 * Param::Math::PI - diffAngle : diffAngle;
				// ï¿½ï¿½ï¿½ã²¹ï¿½ï¿½ï¿½ï¿½
				double compensateAngle = fabs(atan2(Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE, start.dist(enemyPos)));
				//            qDebug() << "compensate angle: " << enemyPos.x() << enemyPos.y() << enemyDir << passDir << compensateAngle;
				if (diffAngle - compensateAngle < ANGLE_LIMIT && ((enemyPos.dist(start) < end.dist(start) + FAR_SAFE_DIST && enemyPos.dist(start) > end.dist(start) - CLOSE_SAFE_DIST) || enemyPos.dist(start) < FRONT_SAFE_DIST)) {
					valid = false;
					break;
				}
			}
		}
		return valid;
	}

	//µãµ½Ïß¶ÎµÄ¾àÀë£¨Óëµãµ½Ö±ÏßµÄ¾àÀë²»Í¬£©
	double dist_SegToPoint(double segFirstX, double segFirstY, double segSecondX, double segSecondY, double pointX, double pointY) {

		double projectionX = 0.0, projectionY = 0.0;  //µã(pointX,pointY)ÔÚÖ±ÏßÉÏµÄÍ¶Ó°µã
		if (segFirstX == segSecondX) {
			projectionX = segFirstX;
			projectionY = pointY;
		}
		else {
			double k = (segSecondY - segFirstY) / (segSecondX - segFirstX);
			projectionX = (k * k * segFirstX + k * (pointY - segFirstY) + pointX) / (k * k + 1);
			projectionY = k * (projectionX - segFirstX) + segFirstY;
		}
		bool pointOnSegment = point_OnLineOnSeg(segFirstX, segFirstY, segSecondX, segSecondY, projectionX, projectionY);//Í¶Ó°µãÊÇ·ñÔÚÏß¶ÎÉÏ
		if (pointOnSegment) {
			return sqrt(pow(projectionX - pointX, 2) + pow(projectionY - pointY, 2));
		}
		else {
			double dist2P1 = sqrt(pow(pointX - segFirstX, 2) + pow(pointY - segFirstY, 2));
			double dist2P2 = sqrt(pow(pointX - segSecondX, 2) + pow(pointY - segSecondY, 2));
			return min_Obs(dist2P1, dist2P2);    //µãµ½½ü¶ËµãµÄ¾àÀë
		}
	}

	//ball_placement
	CGeoPoint MakeOutOfLongCircle(double segFirstX, double segFirstY, double segSecondX, double segSecondY, const CGeoPoint &p) {
		double avoid_dist = 55.0;
		double pointX = p.x();
		double pointY = p.y();


		double projectionX = 0.0, projectionY = 0.0;  //µã(pointX,pointY)ÔÚÖ±ÏßÉÏµÄÍ¶Ó°µã
		if (segFirstX == segSecondX) {
			projectionX = segFirstX;
			projectionY = pointY;
		}
		else {
			double k = (segSecondY - segFirstY) / (segSecondX - segFirstX);
			projectionX = (k * k * segFirstX + k * (pointY - segFirstY) + pointX) / (k * k + 1);
			projectionY = k * (projectionX - segFirstX) + segFirstY;
		}
		bool pointOnSegment = point_OnLineOnSeg(segFirstX, segFirstY, segSecondX, segSecondY, projectionX, projectionY);//Í¶Ó°µãÊÇ·ñÔÚÏß¶ÎÉÏ
		if (pointOnSegment) {
			CVector direction(p.x() - projectionX, p.y() - projectionY);
			CVector add = direction / direction.mod() * avoid_dist;

			return CGeoPoint(add.x() + projectionX, add.y() + projectionY);

			//return sqrt(pow(projectionX - pointX, 2) + pow(projectionY - pointY, 2));
		}
		else {
			double dist2P1 = sqrt(pow(pointX - segFirstX, 2) + pow(pointY - segFirstY, 2));
			double dist2P2 = sqrt(pow(pointX - segSecondX, 2) + pow(pointY - segSecondY, 2));
			if (dist2P1 < dist2P2) {
				CVector direction(p.x() - segFirstX, p.y() - segFirstY);
				CVector add = direction / direction.mod() * avoid_dist;

				return CGeoPoint(add.x() + segFirstX, add.y() + segFirstY);
			}
			else {
				CVector direction(p.x() - segSecondX, p.y() - segSecondY);
				CVector add = direction / direction.mod() * avoid_dist;

				return CGeoPoint(add.x() + segSecondX, add.y() + segSecondY);
			}
			//return minObs(dist2P1, dist2P2);    //µãµ½½ü¶ËµãµÄ¾àÀë
		}
	}

	//ÅÐ¶ÏÖ±ÏßÉÏµÄµãÊÇ·ñÔÚÏß¶ÎÉÏ
	bool point_OnLineOnSeg(const double segFirstX, const double segFirstY, const double segSecondX, const double segSecondY, const double pointX, const double pointY) {
		bool pointOnSegment;
		if (fabs(segFirstX - segSecondX) > fabs(segFirstY - segSecondY))
			pointOnSegment = (pointX > min_Obs(segFirstX, segSecondX)) && (pointX < max_Obs(segFirstX, segSecondX));
		else
			pointOnSegment = (pointY > min_Obs(segFirstY, segSecondY)) && (pointY < max_Obs(segFirstY, segSecondY));
		return pointOnSegment;
	}

	double min_Obs(double a, double b) {
		if (a < b) return a;
		return b;
	}

	double max_Obs(double a, double b) {
		if (a < b) return b;
		return a;
	}
}

