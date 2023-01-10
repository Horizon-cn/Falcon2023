#ifndef DEALBALL_H
#define DEALBALL_H

#include <singleton.h>
#include "globaldata.h"
#include "messageformat.h"
#include "geometry.h"
#include "kalmanfilter.h"
#include "chipsolver.h"
#include "visionmodule.h"
#include <QTime>
#include "staticparams.h"
#include "parammanager.h"
/**
 * @brief main class of process ball
 */
class CDealBall {
  public:
    CDealBall();
    void run();
    void choseBall();
    int getValid() {
        return validBall;
    }
    double getBallSpeed() {
        return result.ball[0].velocity.mod();
    }
//    void updateVel(const Matrix2d tempMatrix, ReceiveVisionMessage& result);
    void updateVel(Owl::ReceiveVisionMessage& result);
    int getFPS(){return VisionModule::Instance()->FPS==0? Owl::OParamManager::Instance()->frameRate:VisionModule::Instance()->FPS;}
                //{return Owl::VParamManager::Instance()->frameRate;}
    double dt;
    double dt1;
    int ballState;
    int infraredcnt;
  private:
    double posDist(CGeoPoint, CGeoPoint);
    bool isValidInfo(Owl::Ball);
    bool ballNearVechile(Owl::Ball, double);
    void init();
    void mergeBall();
    double calculateWeight(int camID, CGeoPoint);
//    void checkInfrared(ReceiveVisionMessage& result);
    bool ballInRobot(CGeoPoint);
    void checkInfrared(Owl::Ball ball);
    Owl::Ball ballSequence[PARAM::BALLNUM][PARAM::CAMERA];
    Owl::Ball lastBall, currentBall, simBall;
    double lastPossible, currentPossible;
    Owl::ReceiveVisionMessage result;
    int actualBallNum = 0;
    int ourTeam;
    int validBall; //bool validBall;
    double upPossible, downPossible,decidePossible;
    long long _cycle, lastFrame, currentFrame;
    double _lastValidDir;

    PosFilter ballKalmanFilter;
    Chipsolver chipsolver;
    double initPosCov, posMeasErr, posModelErr;
    //QTime timeStamp;
    double FPS;
    double lostFrame;

    bool touchGround(const Owl::Ball&);

    void project(int , Owl::Ball&);
};
typedef Falcon::MeyersSingleton<CDealBall> DealBall;
#endif // DEALBALL_H
