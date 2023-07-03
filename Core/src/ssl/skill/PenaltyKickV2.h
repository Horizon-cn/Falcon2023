#ifndef  _PENALTY_KICK_V2_H_
#define _PENALTY_KICK_V2_H_

#include <skill/PlayerTask.h>
#include "DefendUtils.h"
/************************************************************************/
/*		modified by jlc
        2023.5
        long dist penalty, rebuilt based on Advance
*/
/************************************************************************/
class CPenaltyKickV2 : public CStatedTask {
public:
    CPenaltyKickV2();
    ~CPenaltyKickV2();
    virtual void plan(const CVisionModule* pVision);
    virtual CPlayerCommand* execute(const CVisionModule* pVision);
    virtual bool isEmpty() const { return false; }

private:
    enum {
        BEGIN = 0,
        GET,
        KICK,
        BREAKSHOOT,
        LIGHT_KICK
    };
    int _lastCycle;
    int _state;
    int _cycle;
    int infraredOn;
    int meHasBall;
    int meLoseBall;

    int opponentID;

    /**********************************************************
    * Description: ²ÎÊýÁÐ±í ÒÑŸ­·ÅÈëiniµÄŸö²ßÐÔ²ÎÊýµ÷Õû
    *              µ÷Õû²ßÂÔµÄÇãÏò
    * Author: Ì·Óîºê
    * Created Date: 2022/10/10
    ***********************************************************/
    //advance²ÎÊý byTYH  2022.10
    double KICK_DIST;  /*ÉäÃÅÔÊÐí·¶Î§ ÔœžßÔœÈÝÒ×ÉäÃÅ*/
    int WantToLessShoot; /*ÉäÃÅÇãÏò£¬ÔœµÍÔœÈÝÒ×ÉäÃÅ ×îµÍÎª0 ×îžßÎª5*/
    double RELIEF_DIST;  /*GETÖÐœôŒ±×Ž¿öÏÂµÄRELIEFÅÐ¶ÏŸàÀë*/
    double OPP_HAS_BALL_DIST; /*ÅÐ¶ÏµÐ·œÊÇ·ñÓÐÇòµÄŸàÀë ÐèÒªµ÷Õû*/
    double CanPassToWingDist; /*AdvanceÄÜ¹»Ž«žø±ß·æµÄÁÙœçŸàÀë*/
    double CanWingShootDist; /*±ß·æÄÜ¹»ÉäÃÅµÄÁÙœçŸàÀë*/
    double SHOOT_PRECISION; /*ÔÊÐíÉäÃÅ×îÐ¡Ÿ«¶ÈœÇ·ÖÄž£¬ÔœŽóÔœÂýÔœŸ«È· */
    double GetBallBias; /*GetballÆ«ÒÆÁ¿ ÐèÒªŸßÌåÈ¥µ÷ */
    double BalltoMeVel;/*AdvanceŽ«ÇòžøÎÒÖ÷¶¯È¥œÓµÄÁÙœçËÙ¶È*/
    bool shootfarflag;
    /*ÉäÃÅÁŠ¶È²ÎÊý*/
    int KICKPOWER;
    int CHIPPOWER;
    int ADV_FPASSPOWER;
    int ADV_CPASSPOWER;
    int RELIEF_POWER;
    int  BACK_POWER;
    int Advance_DEBUG_ENGINE;
    /**********************************************************
    * Description: ÍšÓÃ²ÎÊý
    * Author: Ì·Óîºê
    * Created Date: 2022/10/10
    ***********************************************************/
    CGeoPoint theirLeft = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2);
    CGeoPoint theirRight = CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2);
    CGeoPoint theirCenter = CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0);
    CGeoPoint ourGoal = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
    const CGeoLine GOATLINE = CGeoLine(CGeoPoint(600, -60), CGeoPoint(600, 60));

    CGeoPoint SupportPoint[9];

    int last_pass = 0; /*ÈýÈËœø¹¥œÅ±Ÿ*/
    double last_dir_deviation = 100;
    double last_target_dir = 0; /*isDirOkËùÐèœÇ¶È*/
    double KickorPassDir = 0;/*Ž«ÇòÓëÉäÃÅµÄ·œÏò ÓŠžÃÓÃÒ»žö±äÁ¿±íÊŸ ŸßÓÐ¿É³ÖÐø»¯µÄ×÷ÓÃ*/

    /**********************************************************
    * Description: ÒýÈëNormalpush
    * Author: jlc
    * Created Date: 2022/11/18
    ***********************************************************/
    int normalPushCnt;


    /**********************************************************
    * Description: Œì²âÀàº¯Êý£¬ÓÃÓÚÊÓŸõÓëÎ»ÖÃÅÐ¶Ï
    * Author: Ì·Óîºê
    * Created Date: 2022/10/10
    ***********************************************************/
    bool isVisionHasBall(const CVisionModule* pVision, const int vecNumber);

    //Use _theirPenaltyGoalie here
    bool Me2OppTooclose(const CVisionModule* pVision, const int vecNumber);
    bool isDirOK(const CVisionModule* pVision, int vecNumber, double targetDir, int ShootOrPass);
    /**********************************************************
        * Description: 状态切换判定类函数，用于状态转化之间的判断
        * Author: 谭宇宏
        * Created Date: 2022/10/10
    ***********************************************************/
    bool tendToShoot(const CVisionModule* pVision, int vecNumber);
    bool isTheLineBlocked(const CVisionModule* pVision, CGeoPoint startPoint, CGeoPoint targetPoint);

    /**********************************************************
        * Description: 生成类函数，具有具体实义
        * Author: 谭宇宏
        * Created Date: 2022/10/10
    ***********************************************************/
    double JustChipDir(const CVisionModule* pVision, int vecNumber);
    CGeoPoint GenerateBreakShootPoint(const CVisionModule* pVision, int vecNumber);

    /**********************************************************
        * Description: fornormalpush
        * Author: jlc
        * Created Date: 2022/11/18
    ***********************************************************/
    //bool isMePassedOpp(const CVisionModule* pVision, const int vecNumber);
    double generateNormalPushDir(const CVisionModule* pVision, const int vecNumber);
    CGeoPoint generateNormalPushPoint(const CVisionModule* pVision, const int vecNumber);

protected:

    CPlayerCommand* _directCommand;
};
#endif
