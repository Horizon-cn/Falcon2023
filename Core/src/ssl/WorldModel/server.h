#ifndef _ZSS_SERVER_H_
#define _ZSS_SERVER_H_
#include "geometry.h"

#include "matrix2d.h"

typedef struct PosT {
	PosT() : valid(0), x(0), y(0) {}
	int valid;
	float x;
	float y;
	void setValid(int _value) {
		valid = _value;
	}
} PosT;

typedef struct VehicleInfoT{
	VehicleInfoT() : dir(0), type(0), dirvel(0) {}
	PosT pos;
	int ID;
	bool isYellow;
	CVector vel;
	CVector acc;
	float dir;//radius
	float dirvel;
	int type;
	Matrix2d P;
	Matrix2d Q;
} 	VehicleInfoT;

typedef struct BallInfoT {
	BallInfoT() {}
	PosT pos;
	PosT chipPredict;
	CVector vel;
	Matrix2d P;
	Matrix2d Q;
} 	BallInfoT;

typedef struct RefInfoT {
	RefInfoT() {}
	int blueGoal;
	int yellowGoal;
	int blueGoalie;
	int yellowGoalie;
	unsigned short timeRemain;
	PosT ballPlacement;
} 	RefInfoT;

typedef struct GameInfoT_
{
	int cycle;
	VehicleInfoT player[32];//for every player num on field, 16 each now
	BallInfoT ball;
	RefInfoT refMsg;
	int mode;
    int next_mode;
} 	GameInfoT;

#endif // _ZSS_SERVER_H_
