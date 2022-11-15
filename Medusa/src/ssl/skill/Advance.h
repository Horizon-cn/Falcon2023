#ifndef  _ADVANCE_
#define _ADVANCE_

#include <skill/PlayerTask.h>
#include "DefendUtils.h"
/**********************************************************
* High Level Skill: Advance Ball Up Field / Down Field
* Description: 通过：拿球-->传球-->射门：进行进攻或者角球制造
*			   驼峰命名
* Author: 谭宇宏
* Created Date: 2022/10/10
***********************************************************/

struct PassDirOrPos {
	double dir;
	CGeoPoint pos;
};

class CAdvance : public  CStatedTask{

public:

	CAdvance();
	~CAdvance();
	CAdvance(const CGeoPoint& ballTarget);
	virtual void plan(const CVisionModule* pVision);
	virtual CPlayerCommand* execute(const CVisionModule * pVision);
	virtual bool isEmpty()const{return false;}

private:
	enum {
		BEGIN = 0,
		GET,
		KICK,
		PASS,
		JUSTCHIPPASS,
		BREAKSHOOT,
		BREAKPASS
	};
	int _lastCycle;
	int _state;
	int _cycle;
	int infraredOn;
	int meHasBall;
	int meLoseBall;

	int opponentID;
	int NumberOfSupport;/* Gpu算点的进攻点数量 */
	int NowIsShoot; 
	/**********************************************************
	* Description: 参数列表 已经放入ini的决策性参数调整
	*              调整策略的倾向
	* Author: 谭宇宏
	* Created Date: 2022/10/10
	***********************************************************/
	//advance参数 byTYH  2022.10
	double KICK_DIST ;  /*射门允许范围 越高越容易射门*/
	int WantToLessShoot ; /*射门倾向，越低越容易射门 最低为0 最高为5*/
	double RELIEF_DIST ;  /*GET中紧急状况下的RELIEF判断距离*/
	double OPP_HAS_BALL_DIST ; /*判断敌方是否有球的距离 需要调整*/
	double CanPassToWingDist ; /*Advance能够传给边锋的临界距离*/
	double CanWingShootDist ; /*边锋能够射门的临界距离*/
	double SHOOT_PRECISION ; /*允许射门最小精度角分母，越大越慢越精确 */
	double GetBallBias; /*Getball偏移量 需要具体去调 */
	double BalltoMeVelTime;/*Advance传球给我主动去接的临界Time*/
	/*射门力度参数*/
	int KICKPOWER ;
	int CHIPPOWER ;
	int ADV_FPASSPOWER ;
	int ADV_CPASSPOWER ;
	int RELIEF_POWER ;
	int  BACK_POWER ;
	int Advance_DEBUG_ENGINE;
	/**********************************************************
	* Description: 通用参数 
	* Author: 谭宇宏
	* Created Date: 2022/10/10
	***********************************************************/
	CGeoPoint theirLeft = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2);
	CGeoPoint theirRight = CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2);
	CGeoPoint theirCenter = CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0);
	CGeoPoint ourGoal = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);

	CGeoPoint SupportPoint[9];

	int LastPassPoint = 0; /*持久化传球方向*/
	double last_dir_deviation = 100;
	double last_target_dir = 0; /*isDirOk所需角度*/
	double KickorPassDir = 0;/*传球与射门的方向 应该用一个变量表示 具有可持续化的作用*/
	bool IsMeSupport = 0;

	/**********************************************************
	* Description: 检测类函数，用于视觉与位置判断
	* Author: 谭宇宏
	* Created Date: 2022/10/10
	***********************************************************/
	bool isVisionHasBall(const CVisionModule* pVision, const int vecNumber);
	bool checkOppHasBall(const CVisionModule* pVision);
	int getTheirMostClosetoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos);
	bool checkBallFront(const CVisionModule* pVision, double angle);
	bool IsOurNearHere(const CVisionModule* pVision, CGeoPoint checkPoint, const int vecNumber);

	bool Me2OppTooclose(const CVisionModule* pVision, const int vecNumber);
	bool isPassBalltoMe(const CVisionModule* pVision, int vecNumber);
	bool isDirOK(const CVisionModule* pVision, int vecNumber, double targetDir, int ShootOrPass);
	bool isInBreakArea(const CVisionModule* pVision, int vecNumber);
	bool JudgeIsMeSupport(const CVisionModule* pVision, int vecNumber);
	/**********************************************************
	* Description: 状态切换判定类函数，用于状态转化之间的判断
	* Author: 谭宇宏
	* Created Date: 2022/10/10
***********************************************************/
	int toChipOrToFlat(const CVisionModule* pVision, int vecNumber);
	bool tendToShoot(const CVisionModule* pVision, int vecNumber);
	int CanSupportKick(const CVisionModule* pVision, int vecNumber);
	bool isTheLineBlocked(const CVisionModule* pVision, CGeoPoint startPoint, CGeoPoint targetPoint);

	/**********************************************************
	* Description: 防守类函数，仅限于GET中使用
	* Author: 谭宇宏
	* Created Date: 2022/10/10
***********************************************************/
	bool isOppFaceOurDoor(const CVisionModule* pVision, double angle);
	bool checkTheyCanShoot(const CVisionModule* pVision, int vecNumber);
/**********************************************************
	* Description: 生成类函数，具有具体实义
	* Author: 谭宇宏
	* Created Date: 2022/10/10
***********************************************************/

	PassDirOrPos PassDirInside(const CVisionModule* pVision, int vecNumber);
	double PassDir(const CVisionModule* pVision, int vecNumber);
	CGeoPoint GenerateBreakShootPoint(const CVisionModule* pVision, int vecNumber);
	CGeoPoint GenerateBreakPassPoint(const CVisionModule* pVision, int vecNumber);
	double TheMinDistBetweenTheOppAndTheLine(const CVisionModule* pVision, CGeoPoint startPoint, CGeoPoint targetPoint);

protected:

	CPlayerCommand* _directCommand;
};
#endif