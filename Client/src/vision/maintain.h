#ifndef MAINTAIN_H
#define MAINTAIN_H
#include "singleton.h"
//#include "vision_detection.pb.h"
#include "kalmanfilter.h"
#include "chipsolver.h"
#include <messageformat.h>
/**
 * @brief Maintain and combine the result of dealrobot and dealball
 */
class CMaintain {
  public:
    CMaintain();
    ~CMaintain();
    void run();
    void init();
    void ChipPrediction();
    void StateMachine();
    double getpredict_x();
    double getpredict_y();
    //Matrix2d& getP(){return ballKalmanFilter.getP();}
    //Matrix2d& getQ(){return ballKalmanFilter.getQ();}

  private:
    Owl::ReceiveVisionMessage result;
    BallRecord ballrecord;

};
typedef Falcon::MeyersSingleton<CMaintain> Maintain;

#endif // MAINTAIN_H
