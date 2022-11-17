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

};

#endif
