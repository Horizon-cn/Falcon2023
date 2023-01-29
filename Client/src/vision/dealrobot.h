#ifndef DEALROBOT_H
#define DEALROBOT_H
#include "kalmanfilter.h"
#include "kalmanfilterdir.h"
#include "visionmodule.h"
#include "globaldata.h"
#include "parammanager.h"
#include <singleton.h>
#include <messageformat.h>
#include <QTime>
#include "dataqueue.hpp"
#include "staticparams.h"
/**
 * @brief main class of process robot
 */
class CDealRobot {
  public:
    CDealRobot();
    void run();
    void mergeRobot();
    void trustRobot();
    void selectRobot();
    void updateVel2(int team, Owl::ReceiveVisionMessage& result);
    void updateVel(int team, Owl::ReceiveVisionMessage& result);
    Matrix2d& getP(int team, int num, int cam){return posFilter[team][num].getP();}
    Matrix2d& getQ(int team, int num, int cam){return posFilter[team][num].getQ();}
    int getFPS(){return Owl::SIParamManager::Instance()->DesiredFPS;}
                //{return VisionModule::Instance()->FPS==0? Owl::SIParamManager::Instance()->DesiredFPS:VisionModule::Instance()->FPS;}
//    bool updateCommand(Owl::Protocol::Robot_Command command);
    QTime t1;
    bool visionProblem[PARAM::TEAMS][PARAM::ROBOTMAXID];

  private:
    Owl::Robot robotSeqence[PARAM::TEAMS][PARAM::ROBOTMAXID][PARAM::CAMERA];
    Owl::ReceiveVisionMessage result;
    Owl::Robot sortTemp[PARAM::TEAMS][PARAM::ROBOTMAXID];
    Owl::Robot lastRobot[PARAM::TEAMS][PARAM::ROBOTMAXID];
    Owl::Robot currentRobot[PARAM::TEAMS][PARAM::ROBOTMAXID];
    void init();
    double posDist(CGeoPoint, CGeoPoint);
    double calculateWeight(int camID, CGeoPoint roboPos);
    void sortRobot(int);
    bool isValidInfo(Owl::Robot);
    double initPosCov, posMeasErr, posModelErr;
    PosFilter posFilter[PARAM::TEAMS][PARAM::ROBOTMAXID];
    //PosFilter dirFilter[PARAM::TEAMS][PARAM::ROBOTMAXID];
    DirFilter dirFilter[PARAM::TEAMS][PARAM::ROBOTMAXID];
    double lastValid[PARAM::TEAMS][PARAM::ROBOTMAXID];
    int validNum[PARAM::TEAMS];
    double upPossible, decidePossible, ourDownPossible, theirDownPossible;
    //QTime timeStamp;
    double FPS;
    
    DataQueue<CVector> historyVel[PARAM::TEAMS][PARAM::ROBOTMAXID];
};
typedef Falcon::MeyersSingleton <CDealRobot> DealRobot;

#endif // DEALROBOT_H
