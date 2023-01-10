#ifndef __GLOBAL_DATA__
#define __GLOBAL_DATA__
#include "singleton.h"
#include "dataqueue.hpp"
#include "messageformat.h"
#include "ballrecords.h"
#include "zss_cmd.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include <QMutex>
#include "staticparams.h"

class CGlobalData {
  public:
    CGlobalData();
    void initVision();
    void setCameraMatrix();
    bool processControl[PARAM::PROCESS]; //0:blue rbk 1:yellow rbk 2:sim 3:Cray
    QMutex robotInfoMutex;
    Owl::RobotInformation robotInformation[PARAM::TEAMS][PARAM::ROBOTMAXID];
    double robotPossible[PARAM::TEAMS][PARAM::ROBOTMAXID];
    DataQueue<Owl::RobotCommands> robotCommand[PARAM::TEAMS];
    int commandMissingFrame[PARAM::TEAMS];
    bool cameraUpdate[PARAM::CAMERA];
    bool cameraControl[PARAM::CAMERA];
    Owl::SingleCamera cameraMatrix[PARAM::CAMERA];
    DataQueue<Owl::ReceiveVisionMessage> camera[PARAM::CAMERA];
    DataQueue<Owl::ReceiveVisionMessage> processBall;
    DataQueue<Owl::ReceiveVisionMessage> processRobot;
    DataQueue<Owl::ReceiveVisionMessage> maintain;
    DataQueue<BallRecord> ballrecords;
    int lastTouch;//Be attention it's id!!!
    QMutex debugMutex;// debugMessages;
    QByteArray debugBlueMessages;
    QByteArray debugYellowMessages;
    QMutex blueHeatMutex, yellowHeatMutex;
    QByteArray blueHeatMap, yellowHeatMap;
    SSL_WrapperPacket ssl_wrapperPacket;
    bool ctrlC;
    QMutex ctrlCMutex;
    int refereeMode;
    bool updateSimVision;//about internal sim
    QByteArray simVision;

  private:
    void setCameraMatrixA();
    void setCameraMatrixB();
    void saoConvertEdge();
};
typedef Falcon::MeyersSingleton<CGlobalData> GlobalData;
#endif // __GLOBAL_DATA__
