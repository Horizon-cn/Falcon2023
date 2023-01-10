#include "maintain.h"
#include "globaldata.h"
#include "collisiondetect.h"
#include "visionmodule.h"
#include "field.h"
#include "dealball.h"
#include "dealrobot.h"
#include "ballrecords.h"
#include "chipsolver.h"
#include <QTime>
#include "game.h"
#include "test.h"
#include "staticparams.h"
#define MAX_BALL_PER_FRAME 200

using namespace std;
namespace {}

CMaintain::CMaintain() {
//    initPosCov = 100; posMeasErr = 20; posModelErr = 0.2;
//    ballKalmanFilter = PosFilter(initPosCov, posMeasErr, posModelErr);
//    timeStamp = 0;
}

CMaintain::~CMaintain() {}

void CMaintain::init() {
    result.init();
    result.addBall(GlobalData::Instance()->processBall[0].ball[0]);
    result.ball[0].valid = DealBall::Instance()->getValid();
    for (int i = 0; i < GlobalData::Instance()->processRobot[0].robotSize[PARAM::BLUE]; i++)
        result.addRobot(GlobalData::Instance()->processRobot[0].robot[PARAM::BLUE][i]);
    for (int i = 0; i < GlobalData::Instance()->processRobot[0].robotSize[PARAM::YELLOW]; i++)
        result.addRobot(GlobalData::Instance()->processRobot[0].robot[PARAM::YELLOW][i]);
}

double CMaintain::getpredict_x() {
    return result.ball[0].predict_pos.x();
}

double CMaintain::getpredict_y() {
    return result.ball[0].predict_pos.y();
}

void CMaintain::run() {  //TODO move to visionmodule
    init();
    //必须保证processrobot数组里为真值，否则产生误差累计
    DealRobot::Instance()->updateVel(PARAM::BLUE, result);
    //qDebug()<<"updateBlueRobotVel";
    //QTime t2 = QTime::currentTime();
    //double dt = DealRobot::Instance()->t1.msecsTo(t2);
    //qDebug()<<"process to maintain"<<dt;
    DealRobot::Instance()->updateVel(PARAM::YELLOW, result);
    //qDebug()<<"updateYellowRobotVel";
    DealBall::Instance()->updateVel(result);
    //qDebug()<<"updateBallVel";
    GlobalData::Instance()->maintain.push(result);
    
    //if(Game::Instance()->start) Game::Instance()->judgeBallState();
    if(Test::Instance()->start) Test::Instance()->storeTestingDataV2(); //storeTestingData(); //test mode
}
