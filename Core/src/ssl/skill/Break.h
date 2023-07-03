#ifndef _BREAK_H_
#define _BREAK_H_
#include <skill/PlayerTask.h>
#include "Param.h"

/**********************************************************/
/* Skill: ???????¨°
/* by pjt:
/**********************************************************/

class CBreak :public CStatedTask {
public:
    CBreak();
    virtual void plan(const CVisionModule* pVision);
    virtual bool isEmpty() const { return false; }
    virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
    //virtual void toStream(std::ostream& os) const { os << "Skill: ZBreak\n" << std::endl; }
private:
    int _lastCycle;
    bool isDribble = false;
    int grabMode;
    int last_mode;
    int fraredOn;
    int fraredOff;
    CGeoPoint dribblePoint;
    CGeoPoint move_point;

    CGeoPoint point[20];
    int running_index;
    CGeoPoint theirLeft = CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2);
    CGeoPoint theirRight = CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2);

    bool isSetPoint(const CVisionModule* pVision, const CGeoPoint* point, const CGeoPoint& target);

    //help track robot trace
    CGeoPoint lastFrameposition;
    double dribbleDist = 0;
    bool isVisionHasBall(const CVisionModule* pVision, const int vecNumber);
    CGeoPoint makeInCircle(const CGeoPoint& point, const CGeoPoint& center, double radius);
    CGeoPoint calc_point(const CVisionModule* pVision, const int vecNumber, const CGeoPoint& target, const CGeoPoint& dribblePoint, const bool isChip, bool& canShoot, bool& needBreakThrough, bool& isPenalty);
    double holdBallDir(const CVisionModule *pVision, int robotNum);
    bool canScore(const CVisionModule* pVision, const int vecNumber, const double radius, const double dir);
};

#endif
