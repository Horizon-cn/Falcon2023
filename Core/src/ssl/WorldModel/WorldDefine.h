#ifndef _WORLD_DEFINE_H_
#define _WORLD_DEFINE_H_
#include <geometry.h>
/************************************************************************/
/*                       TranslationT                                    */
/************************************************************************/
class TranslationT {
public:
	TranslationT() : _valid(false), _pos(CGeoPoint(-9999, -9999)) { }
	const CGeoPoint& Pos() const {
		return _pos;
	}
	void SetPos(double x, double y) {
		_pos = CGeoPoint(x, y);
	}
	void SetPos(const CGeoPoint& pos) {
		_pos = pos;
	}
	double X() const {
		return _pos.x();
	}
	double Y() const {
		return _pos.y();
	}
	void SetVel(double x, double y) {
		_vel = CVector(x, y);
	}
	void SetVel(const CVector& vel) {
		_vel = vel;
	}
	void SetAcc(double x, double y) {
		_acc = CVector(x, y);
	}
	void SetAcc(const CVector& acc) {
		_acc = acc;
	}
	const CVector& Vel() const {
		return _vel;
	}
	const CVector& Acc() const {
		return _acc;
	}
	double VelX() const {
		return _vel.x();
	}
	double VelY() const {
		return _vel.y();
	}
	double AccX() const {
		return _acc.x();
	}
	double AccY() const {
		return _acc.y();
	}
	void SetValid(bool v) {
		_valid = v;
	}
	bool Valid() const {
		return _valid;
	}
private:
	CGeoPoint _pos;
	CVector _vel;
	CVector _acc;
	bool _valid;
};
/************************************************************************/
/*                      ChipPosT                                   */
/************************************************************************/
class ChipPosT {
public:
	ChipPosT() { }
	const CGeoPoint& ChipPredictPos() const {
		return _chipPredict;
	}
	void SetChipPredict(const CGeoPoint& chipPos) {
		_chipPredict = chipPos;
	}
	void SetChipPredict(double x, double y) {
		_chipPredict = CGeoPoint(x, y);
	}
private:
	CGeoPoint _chipPredict; //挑球预测
};

/************************************************************************/
/*                        机器人姿态数据结构                               */
/************************************************************************/
struct RotationT { // 目标信息
public:
	RotationT() : _dir(0), _rotVel(0) { }
	double Dir() const {
		return _dir;
	}
	void SetDir(double d) {
		_dir = d;
	}
	double RotVel() const {
		return _rotVel;
	}
	void SetRotVel(double d) {
		_rotVel = d;
	}
private:
	double _dir; // 朝向
	double _rotVel; // 旋转速度
};
/************************************************************************/
/*                      PlayerTypeT                                     */
/************************************************************************/
//class PlayerTypeT {
//public:
//	PlayerTypeT() : _type(0) {}
//	void SetType(int t) {
//		_type = t;
//	}
//	int Type() const {
//		return _type;
//	}
//private:
//	int _type;
//};
/************************************************************************/
/*                       PlayerVisionT                                  */
/************************************************************************/
class PlayerVisionT : public TranslationT, public RotationT {

};

/************************************************************************/
/*                       BallVisionT                                  */
/************************************************************************/
class BallVisionT : public TranslationT, public ChipPosT {

};

/************************************************************************/
/*                        机器人能力数据结构                               */
/************************************************************************/
struct PlayerCapabilityT {
	PlayerCapabilityT() : maxAccel(0), maxSpeed(0), maxAngularAccel(0), maxAngularSpeed(0), maxDec(0), maxAngularDec(0), maxSpeedX(0), maxSpeedY(0){}
	double maxAccel; // 最大加速度
	double maxSpeed; // 最大速度
	double maxAngularAccel; // 最大角加速度
	double maxAngularSpeed; // 最大角速度
	double maxDec;          // 最大减速度
	double maxAngularDec;   // 最大角减速度
	double maxSpeedX; // 最大纵向速度 by Tyh
	double maxSpeedY; // 最大横向速度 by Tyh
};

struct ROBOTINFO
{
	int nRobotNum;

	bool bInfraredInfo;
	short nKickInfo;
};

#endif // _WORLD_DEFINE_H_
