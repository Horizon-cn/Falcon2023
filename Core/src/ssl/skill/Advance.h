#ifndef  _ADVANCE_
#define _ADVANCE_

#include <skill/PlayerTask.h>
#include "DefendUtils.h"
/**********************************************************
* High Level Skill: Advance Ball Up Field / Down Field
* Description: ?????????-->????-->????????§ß??????????????
*			   ???????
* Author: ?????
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
        PUSHOUT,
        BREAKPASS
    };
    int _lastCycle;
    int _state;
    int _cycle;
    int infraredOn;
    int meHasBall;
    int meLoseBall;

    int opponentID;
    int NumberOfSupport;/* Gpu??????????????? */
    int NowIsShoot;
    int NumOfOurPlayer;
    /**********************************************************
    * Description: ?????§Ò? ???????ini??????????????
    *              ?????????????
    * Author: ?????
    * Created Date: 2022/10/10
    ***********************************************************/
    //advance???? byTYH  2022.10
    double KICK_DIST ;  /*??????????¦¶ ????????????*/
    int WantToLessShoot ; /*?????????????????????? ?????0 ?????5*/
    double RELIEF_DIST ;  /*GET?§ß?????????RELIEF?§Ø????*/
    double OPP_HAS_BALL_DIST ; /*?§Ø?§Ù????????????? ???????*/
    double CanPassToWingDist ; /*Advance???????????????????*/
    double CanWingShootDist ; /*??????????????????*/
    double SHOOT_PRECISION ; /*??????????§³??????????????????? */
    double GetBallBias; /*Getball????? ?????????? */
    double BalltoMeVelTime;/*Advance???????????????????Time*/
    double OBSTACLE_RADIUS;
    /*???????????*/
    int KICKPOWER ;
    int CHIPPOWER ;
    int ADV_FPASSPOWER_Alpha;
    int ADV_CPASSPOWER_Alpha ;
    int RELIEF_POWER ;
    int  BACK_POWER ;
    int Advance_DEBUG_ENGINE;
    double LARGE_ADJUST_ANGLE;
    int PUSHPOWER;
    double tmpDir = 1.57;
    /**********************************************************
    * Description: ??¨°???
    * Author: ?????
    * Created Date: 2022/10/10
    ***********************************************************/
    const CGeoLine GOATLINE = CGeoLine(CGeoPoint(600, -60), CGeoPoint(600, 60));
    const CGeoPoint GOATPoint1 = CGeoPoint(600, 50);
    const CGeoPoint GOATPoint2 = CGeoPoint(600, -50);
    CGeoPoint theirLeft = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2);
    CGeoPoint theirRight = CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2);
    CGeoPoint theirCenter = CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0);
    CGeoPoint ourGoal = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);

    CGeoPoint SupportPoint[6];

    int LastPassPoint = 0; /*????????????*/
    double last_dir_deviation = 100;
    double last_target_dir = 0; /*isDirOk???????*/
    double KickorPassDir = 0;/*?????????????? ??????????????? ???§á????????????*/
    double LastPassDirToJudge = 0;

    bool IsMeSupport = 0;

    /**********************************************************
    * Description: ???????????????????¦Ë???§Ø?
    * Author: ?????
    * Created Date: 2022/10/10
    ***********************************************************/
    bool isVisionHasBall(const CVisionModule* pVision, const int vecNumber);
    bool checkOppHasBall(const CVisionModule* pVision);
    int getTheirMostClosetoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos);
    bool checkBallFront(const CVisionModule* pVision, double angle);
    bool IsOurNearHere(const CVisionModule* pVision, const int supportIndex);
    bool IsOurNearHere(const CVisionModule* pVision, CGeoPoint checkPoint, const int vecNumber);

    bool Me2OppTooclose(const CVisionModule* pVision, const int vecNumber);
    bool isPassBalltoMe(const CVisionModule* pVision, int vecNumber);
    bool isDirOK(const CVisionModule* pVision, int vecNumber, double targetDir, int ShootOrPass);
    
    bool isInBreakArea(const CVisionModule* pVision, int vecNumber);
    bool isInTheCornerArea(const CVisionModule* pVision, int vecNumber);
    bool MeIsInTheSide(const CVisionModule* pVision, int vecNumber);
    
    bool JudgeIsMeSupport(const CVisionModule* pVision, int vecNumber);
    bool JudgePassMeIsBeBlocked(const CVisionModule *pVision, int vecNumber);
    bool AdJudgeBreakCanDo(const CVisionModule *pVision, int vecNumber, CGeoPoint TargetPoint);
    /**********************************************************
    * Description: ???§Ý??§Ø??????????????????????§Ø?
    * Author: ?????
    * Created Date: 2022/10/10
***********************************************************/
    int toChipOrToFlat(const CVisionModule* pVision, int vecNumber,CGeoPoint TargetPoint);
    bool tendToShoot(const CVisionModule* pVision, int vecNumber);
    int CanSupportKick(const CVisionModule* pVision, int vecNumber);
    bool isTheLineBlocked(const CVisionModule* pVision, CGeoPoint startPoint, CGeoPoint targetPoint);
    int TheirRobotInBreakArea(const CVisionModule* pVision, const int vecNumber);
    /**********************************************************
    * Description: ????????????????GET?????
    * Author: ?????
    * Created Date: 2022/10/10
***********************************************************/
    bool isOppFaceOurDoor(const CVisionModule* pVision, double angle);
    bool checkTheyCanShoot(const CVisionModule* pVision, int vecNumber);


    bool OppIsNearThanMe(const CVisionModule* pVision, const int vecNumber);

    double generateOppIsNearThanMeDir(const CVisionModule* pVision, const int vecNumber);
    double generateOppIsFarThanMeDir(const CVisionModule* pVision, const int vecNumber);
    bool OppIsFarThanMe(const CVisionModule* pVision, const int vecNumber);
/**********************************************************
    * Description: ?????????????§à??????
    * Author: ?????
    * Created Date: 2022/10/10
***********************************************************/

    PassDirOrPos PassDirInside(const CVisionModule* pVision, int vecNumber);
    double PassDir(const CVisionModule* pVision, int vecNumber);
    CGeoPoint GenerateBreakShootPoint(const CVisionModule* pVision, int vecNumber);
    CGeoPoint GenerateBreakPassPoint(const CVisionModule* pVision, int vecNumber);
    double TheMinDistBetweenTheOppAndTheLine(const CVisionModule* pVision, CGeoPoint startPoint, CGeoPoint targetPoint);
    double GetFPassPower(CGeoPoint StartPoint, CGeoPoint targetPoint);
    double GetCPassPower(CGeoPoint StartPoint, CGeoPoint targetPoint);

    CGeoPoint generateNormalPushPoint(const CVisionModule* pVision, const int vecNumber);
    double generateGetballDir(const CVisionModule* pVision, const int vecNumber);

    int GenerateStateOfFoulTrouble(const CVisionModule* pVision, const int vecNumber);

    bool canScore(const CVisionModule* pVision, const int vecNumber, const double radius, const double dir);
protected:

    CPlayerCommand* _directCommand;
};
#endif
