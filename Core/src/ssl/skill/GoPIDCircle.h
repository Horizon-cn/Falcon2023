#ifndef  _GoPIDCircle_
#define _GoPIDCircle_

#include <skill/PlayerTask.h>
#include <geometry.h>
/**********************************************************
* High Level Skill: Advance Ball Up Field / Down Field
* Description: ?????????-->????-->????????§ß??????????????
*			   ???????
* Author: ?????
* Created Date: 2022/10/10
***********************************************************/

class CGoPIDCircle : public  CStatedTask {

public:

    CGoPIDCircle();
    ~CGoPIDCircle();
    virtual void plan(const CVisionModule* pVision);
    virtual CPlayerCommand* execute(const CVisionModule* pVision);
    virtual bool isEmpty()const { return false; }
private:
    //PlayerCapabilityT setCapability(const CVisionModule* pVision);
    double LastError;
    double AccuError;
    double Ki;
    double Kp;
    double Kd;
    double PIDController(const CVisionModule* pVision, const int vecNumber, CGeoPoint Center, double Radius, bool opt);
    double LimitAccu(double Input);
    double LimitOmiga(double Input);
protected:

    CPlayerCommand* _directCommand;
};
#endif
