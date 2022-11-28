#ifndef _GoTECHCHALPOS_H_
#define _GoTECHCHALPOS_H_
#include <skill/PlayerTask.h>

/**********************************************************/
/* Skill: TechChalPos
/* by tyh:
/**********************************************************/

class CGoTechChalPos :public CStatedTask {
public:
    CGoTechChalPos();
    virtual void plan(const CVisionModule* pVision);
    virtual bool isEmpty() const { return false; }
    virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:

private:
    CGeoPoint GenerateFrontPoint(const CVisionModule* pVision,const int IsBack);
    CGeoPoint GenerateMiddlePoint(const CVisionModule* pVision);
    bool CanShoot(const CVisionModule* pVision, const CGeoPoint StartPoint);
    bool CanPass(const CVisionModule* pVision, const CGeoPoint StartPoint);
    double TheMinDistBetweenTheOppAndTheLine(const CVisionModule* pVision, const CGeoPoint startPoint, const CGeoPoint targetPoint);
    const CGeoPoint GoalMiddlePoint = CGeoPoint(600, 0);
    const CGeoPoint GoalLeftPoint = CGeoPoint(600, 60);
    const CGeoPoint GoalRightPoint = CGeoPoint(600, -60);
    double k_m = 5.0;
    CGeoPoint FrontPoint;
    CGeoPoint MiddlePoint;
};

#endif
