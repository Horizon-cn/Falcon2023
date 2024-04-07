#ifndef __ChaseToPenalty_H__
#define __ChaseToPenalty_H__
#include <skill/PlayerTask.h>

class CChaseToPenalty :public CStatedTask {
public:
	CChaseToPenalty();
    virtual void plan(const CVisionModule* pVision);
    virtual bool isEmpty()const { return false; }
    virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
    ;
private:
    CPlayerCommand* _directCommand;
};

#endif //__ChaseToPenalty_H__