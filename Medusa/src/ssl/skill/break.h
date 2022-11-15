#ifndef _BREAK_H_
#define _BREAK_H_
#include <skill/PlayerTask.h>

/**********************************************************/
/* Skill: Í»ÆÆ³öÇò
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

    //help track robot trace
    CGeoPoint lastFrameposition;
    double dribbleDist = 0;
    bool CBreak::isVisionHasBall(const CVisionModule* pVision, const int vecNumber);
};

#endif 