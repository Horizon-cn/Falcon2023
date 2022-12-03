#pragma once
#ifndef  _ADVANCE_BALL_V4_H_
#define _ADVANCE_BALL_V4_H_

#include "PlayerTask.h"
#include "param.h"
/**********************************************************
* High Level Skill: Advance Ball
* Author: yys
* Created Date: 2014/07/11
***********************************************************/
class CAdvanceBallV4 : public CStatedTask {
public:
	CAdvanceBallV4();
	~CAdvanceBallV4();
	CAdvanceBallV4(const CGeoPoint& ballTarget);
	virtual void plan(const CVisionModule* pVision);
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
	virtual bool isEmpty() const { return false; }
private:
	enum {
		GOTO = 1,
		NORMAL_PUSH,
		DRIBBLE_TURN,
		LIGHT_KICK,
		DRIBBLE_PULL,
		KICK,
		CHIPPASS,
		FLATPASS,
		RELIEF,
		SOMBRERO,
		STOP
	};
	enum {
		ATTACK_TO_CENTER,
		ATTACK_TO_LEFT,
		ATTACK_TO_RIGHT
	};
	void checkNorPushNextState(const CVisionModule* pVision, const int vecNumber);
	//位置判断函数//
	bool Me2OppTooclose(const CVisionModule* pVision, const int vecNumber);
	bool ballOnTheirHalf(const CVisionModule* pVision);
	bool checkBallFront(const CVisionModule* pVision, double angle = Param::Math::PI / 3.0);
	//	bool checkBallBehind(const CVisionModule* pVision, double angle = Param::Math::PI / 3.0);
	//	bool checkBallFrontOrBehindBigPre(const CVisionModule* pVision);
	bool ballInTheirPenaltyArea(const CVisionModule* pVision, const int vecNumber);
	bool ballBetweentMeAndOpp(const CVisionModule* pVision, const int vecNumber);
	bool meNearballThanOpp(const CVisionModule* pVision, const int vecNumber);
	bool oppBetweenBallAndMe(const CVisionModule* pVision, const int vecNumber);
	//条件判断函数//
	bool oppRushMe(const CVisionModule* pVision, int vecNumber);
	bool isPassBalltoMe(const CVisionModule* pVision, int vecNumber);
	bool ballMoving2Opp(const CVisionModule* pVision);
	void decideChipOrShoot(const CVisionModule* pVision, double& kickDir, const int vecNumver);
	bool oppBlockMe(const CVisionModule* pVision, const int vecNumber);
	bool selectChipKick(const CVisionModule* pVision, int vecNumber);
	//checkOppHasBall没有考虑车朝向的问题
	bool checkOppHasBall(const CVisionModule* pVision);
	bool isShootBlocked(const CVisionModule* pVision, const int vecNumber);
	bool isMePassedOpp(const CVisionModule* pVision, const int vecNumber);
	bool isVisionHasBall(const CVisionModule* pVision, const int vecNumber);
	bool checkUsingVoilence(const CVisionModule* pVision, int vecNumber);
	bool checkTheyCanShoot(const CVisionModule* pVision, int vecNumber);
	//朝向判断函数//
	bool isOppFaceOurDoor(const CVisionModule* pVision, double angle = Param::Math::PI / 3.0);
	bool isOppFaceTheirDoor(const CVisionModule* pVision, const double angle = Param::Math::PI / 3.0);
	bool meFaceTheirDoor(const CVisionModule* pVision, const int vecNumber);
	//	bool meFaceOpp(const CVisionModule* pVision, const int vecNumber);
	bool faceTheirGoal(const CVisionModule* pVision, const int executor);
	//动作函数//
	void voilenceActionTime(const CVisionModule* pVision, int vecNumber);
	void blockingOuterOppTime(const CVisionModule* pVision, int vecNumber);
	void blockingBestOppTime(const CVisionModule* pVision, int vecNumber);
	//计算函数//
	void calcPushTarget(const CVisionModule* pVision);
	//true为有空档吸球转身射门，false为没有空档
	bool checkEnoughSpaceToTurnKick(const CVisionModule* pVision);
	bool isShootBlockedInPenaltyArea(const CVisionModule* pVision, const int vecNumber);
	int getTheirMostClosetoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos);
	double generateNormalPushDir(const CVisionModule* pVision, const int vecNumber);
	//传球判断//
	bool tendToShoot(const CVisionModule* pVision, int vecNumber, int k_bottom);//目前十分简陋只能用isShootBlocked来判断
	int toChipOrToFlat(const CVisionModule* pVision, int vecNumber);//判断是平传还是挑传,K_empty表示传球路径上的空旷程度
	bool isBlocked(const CVisionModule* pVision, CGeoPoint startPoint, CGeoPoint targetPoint);
	double pointShootDir(const CVisionModule* pVision, CGeoPoint startPoint);
	double flatPassDir(const CVisionModule* pVision, int vecNumber);
	int passkick(const CVisionModule* pVision, int vecNumber);
	bool isDirOK(const CVisionModule* pVision, double myDir, CGeoPoint myPos, double targetDir);

	int pullCnt;
	double finalTurnDir;
	double pullBallDir;
	CGeoPoint rushPoint;
	double rushDir;
	int rushCnt;
	bool rushFlag;
	int turnCnt;
	CGeoPoint turnPos;
	int _lastCycle;
	int _state;
	int _cycle;
	int infraredOn;
	int meHasBall;
	int meLoseBall;
	int opponentID; //敌方最有威胁的车
	int opponentNearestID; //敌方在我面前最近的车
	int attack_side;
	CGeoPoint _pushBallTarget;
	bool pullBackFlag;
	int normalPushCnt;
	double dribbleTurnFinalDir;

protected:
	CPlayerCommand* _directCommand;
};
#endif
