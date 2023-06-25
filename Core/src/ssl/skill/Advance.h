#ifndef  _ADVANCE_
#define _ADVANCE_

#include <skill/PlayerTask.h>
#include "DefendUtils.h"
/**********************************************************
* High Level Skill: Advance Ball Up Field / Down Field
* Description: ?????????-->????-->????????н??????????????
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
        BREAKING,
        BLOCK,
        CHASEKICK,
        CHASEPUSH
    };
    enum {
        DefenceArea = 0,
        SideArea,
        CornerArea,
        KICKArea,
        CanNOTBreakArea,
        CenterArea,
        ReliefArea,
    };
    int _lastCycle;
    int _state;
    int _cycle;
    int infraredOn;
    int meHasBall;
    int meLoseBall;

    int opponentID;
    int Oppfront;

    int NumberOfSupport;/* Gpu??????????????? */
    int NowIsShoot;
    int NumOfOurPlayer;

    int MeIsInWhichArea;
    /**********************************************************
    * Description: ?????б? ???????ini??????????????
    *              ?????????????
    * Author: ?????
    * Created Date: 2022/10/10
    ***********************************************************/
    //advance???? byTYH  2022.10
    double KICK_DIST ;  /*??????????Χ ????????????*/
    double WantToLessShoot ; /*?????????????????????? ?????0 ?????5*/
    double RELIEF_DIST ;  /*GET?н?????????RELIEF?ж????*/
    double OPP_HAS_BALL_DIST ; /*?ж?з????????????? ???????*/
    double CanPassToWingDist ; /*Advance???????????????????*/
    double CanWingShootDist ; /*??????????????????*/
    double PASS_PRECISION ; /*??????????С??????????????????? */
    double GetBallBias; /*Getball????? ?????????? */
    double BalltoMeVelTime;/*Advance???????????????????Time*/
    double OBSTACLE_RADIUS;
    /*???????????*/
    double KICKPOWER ;
    double CHIPPOWER ;
    double ADV_FPASSPOWER_Alpha;
    double ADV_CPASSPOWER_Alpha ;
    double RELIEF_POWER ;
    double  BACK_POWER ;
    int Advance_DEBUG_ENGINE;
    double LARGE_ADJUST_ANGLE;
    double PUSHPOWER;
    double tmpDir = 1.57;
    /**********************************************************
    * Description: ??ò???
    * Author: ?????
    * Created Date: 2022/10/10
    ***********************************************************/
    const CGeoLine GOATLINE = CGeoLine(CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2), CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2));
    const CGeoPoint GOATPoint1 = CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2 - 10);
    const CGeoPoint GOATPoint2 = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2 + 10);
    CGeoPoint theirLeft = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2);
    CGeoPoint theirRight = CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2);
    CGeoPoint theirCenter = CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0);
    CGeoPoint ourGoal = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);

    int NumOfTheirPlayerfrontMe;
    CGeoPoint SupportPoint[6];

    int LastPassPoint = 0; /*????????????*/
    double last_dir_deviation = 100;
    double last_target_dir = 0; /*isDirOk???????*/
    double KickorPassDir = 0;/*?????????????? ??????????????? ???п????????????*/

    bool IHaveSupport = false;
    int TheBestSupportNumber = 1;

    CGeoPoint ShootPoint, PassPoint;/*传球与射门的方向 应该用一个变量表示 具有可持续化的作用*/

    /**********************************************************
    * Description: ???????????????????λ???ж?
    * Author: ?????
    * Created Date: 2022/10/10
    ***********************************************************/
    bool isVisionHasBall(const CVisionModule* pVision, const int vecNumber);
    bool checkOppHasBall(const CVisionModule* pVision);
    int getTheirMostClosetoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos);
    int getTheirMostCloseAndFronttoPosPlayerNum(const CVisionModule* pVision, CGeoPoint pos);
    bool checkBallFront(const CVisionModule* pVision, double angle);
    bool IsOurNearHere(const CVisionModule* pVision, const int supportIndex);
    bool IsOurNearHere(const CVisionModule* pVision, CGeoPoint checkPoint, const int vecNumber);

    bool isDirOK(const CVisionModule* pVision, int vecNumber, double targetDir, int IsShoot);
    bool Me2OppTooclose(const CVisionModule* pVision, const int vecNumber);
    bool isPassBalltoMe(const CVisionModule* pVision, int vecNumber);
    /*
    bool isInBreakArea(const CVisionModule* pVision, int vecNumber);
    bool isInTheCornerArea(const CVisionModule* pVision, int vecNumber);
    bool MeIsInTheSide(const CVisionModule* pVision, int vecNumber);
    
    bool JudgeIsMeSupport(const CVisionModule* pVision, int vecNumber);
    bool JudgePassMeIsBeBlocked(const CVisionModule *pVision, int vecNumber);
    
    bool AdJudgeBreakCanDo(const CVisionModule *pVision, int vecNumber, CGeoPoint TargetPoint);
    */
    int InWhichArea(const CVisionModule* pVision, int vecNumber);

    bool WeCanAlwaysSetKick(const CVisionModule* pVision, const int vecNumber);
    /**********************************************************
    * Description: ???л??ж??????????????????????ж?
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

    bool WeNeedBlockTheBall(const CVisionModule* pVision, const int vecNumber);
    bool OppIsNearThanMe(const CVisionModule* pVision, const int vecNumber);

    double generateOppIsNearThanMeDir(const CVisionModule* pVision, const int vecNumber);
    double generateOppIsFarThanMeDir(const CVisionModule* pVision, const int vecNumber);
    bool OppIsFarThanMe(const CVisionModule* pVision, const int vecNumber);
/**********************************************************
    * Description: ?????????????о??????
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
    int opp_ahead(const CVisionModule* pVision, const int vecNumber);
    int GenerateNextState(const CVisionModule* pVision, const int vecNumber);
    int CanWeUseChaseBecauseOfGetBallV3(const CVisionModule* pVision, const int vecNumber);
protected:

    CPlayerCommand* _directCommand;
};
#endif
