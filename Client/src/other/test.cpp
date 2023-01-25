#include "test.h"
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QDataStream>
#include <QDir>
#include "globaldata.h"
#include "simmodule.h"
#include "parammanager.h"
namespace{
    QIODevice* ballIO;
    QString ballFileName;
    QFile ballFile;
    QDataStream ballStream;
    //QIODevice* robotIO;
    //QString robotFileName;
   // QFile robotFile;
    //QDataStream robotStream;
    //auto opm = Owl::OParamManager::Instance();
}
CTest::CTest(QObject *parent) : QObject(parent)
{
    //opm->loadParam(file_num, "Test/init_file", 0);
    //opm->loadParam(current_file_num, "Test/init_file", 0);
    //opm->loadParam(max_ballSpeed, "Test/max_ballSpeed", 10000);
    //opm->loadParam(min_ballSpeed, "Test/min_ballSpeed", 2000);
}

CTest::~CTest(){
    //opm->changeParam("Test/init_file", current_file_num);
}

void CTest::setMode(bool isTesting, bool runTestingScripts){
    testing = isTesting;
    if(!testing){ //reset
        start = false;
    //    changed = true;
    //    current_file_num++;
    }
    else {
        file_num = 0; //++;
    //    runScripts = runTestingScripts;
    //    if(!runScripts){
            start = true;
            t0 = QTime::currentTime();
    //    }
    }
}
/**
void CTest::judgeStateMachine(QString s){
    lastcnt = cnt;
    if(s=="run1" && lastState=="run0"){
        start = true;
        t1 = QTime::currentTime();
    }
    if(start){
        if(s=="run1" && (lastState=="run5"||lastState=="run0")){
            cnt++;
            changed = false;
        }
        else if(s=="end") start = false;
        if(s=="run1" || s=="run5") lastState=s;
    }
}

void CTest::setNoise(){
    qDebug()<<"setNoise: "<<cnt;
    switch(cnt){
    case 0:
        noise = 0;
        vanish = 0;
        break;
    case 1:
        noise = 5;
        vanish = 0;
        break;
    case 2:
        noise = 10;
        vanish = 0;
        break;
    case 3:
        noise = 20;
        vanish = 0;
        break;
    case 4:
        noise = 40;
        vanish = 0;
        break;
    case 5:
        noise = 0;
        vanish = 0.2;
        break;
    case 6:
        noise = 0;
        vanish = 0.4;
        break;
    case 7:
        noise = 0;
        vanish = 0.6;
        break;
    case 8:
        noise = 0;
        vanish = 0.7;
        break;
    case 9:
        noise = 0;
        vanish = 0.8;
        break;
    }
    changed = true;
    QTime t = QTime::currentTime();
    while(t.msecsTo(QTime::currentTime())<5);
}

void CTest::storeTestingData() {
    switch(runScripts){
        case true:
        storeTestingDataV1();
        break;
        case false:
        storeTestingDataV2();
        break;
    }
}

void CTest::storeTestingDataV1() {

    if(Test::Instance()->cnt!=Test::Instance()->lastcnt){
        if(!changed) setNoise();
        ballIO = nullptr;
        ballFile.close();
        ballFileName = QString("Test/5/")+QString("ball_N")+QString::number(Test::Instance()->noise)
                                     +QString("V")+QString::number(Test::Instance()->vanish)+QString(".txt");
        ballFile.setFileName(ballFileName);
        ballFile.open(QIODevice::WriteOnly | QIODevice::Append);
        ballIO = &ballFile;
        ballStream.setDevice(ballIO);

        robotIO = nullptr;
        robotFile.close();
        robotFileName = QString("Test/5/")+QString("robot_N")+QString::number(Test::Instance()->noise)
                                      +QString("V")+QString::number(Test::Instance()->vanish)+QString(".txt");
        robotFile.setFileName(robotFileName);
        robotFile.open(QIODevice::WriteOnly | QIODevice::Append);
        robotIO = &robotFile;
        robotStream.setDevice(robotIO);
        writeDataInfo();
    }
    t2 = QTime::currentTime();
    int delt_time = t1.msecsTo(t2);
    writeToFile(0,delt_time);
    writeToFile(0,GlobalData::Instance()->processBall[0].ball->raw.pos.x());
    writeToFile(0,GlobalData::Instance()->processBall[0].ball->raw.pos.y());
    writeToFile(0,GlobalData::Instance()->processBall[0].ball->pos.x());
    writeToFile(0,GlobalData::Instance()->processBall[0].ball->pos.y());
    writeToFile(0,GlobalData::Instance()->processBall[0].ball->raw.vel.vx());
    writeToFile(0,GlobalData::Instance()->processBall[0].ball->raw.vel.vy());
    writeToFile(0,GlobalData::Instance()->processBall[0].ball->velocity.x());
    writeToFile(0,GlobalData::Instance()->processBall[0].ball->velocity.y());
//    writeToFile(0,GlobalData::Instance()->ballfilterPosVel[0][0]);
//    writeToFile(0,GlobalData::Instance()->ballfilterPosVel[0][1]);
//    writeToFile(0,GlobalData::Instance()->ballfilterPosVel[1][0]);
//    writeToFile(0,GlobalData::Instance()->ballfilterPosVel[1][1]);
    writeToFile(0,GlobalData::Instance()->maintain[0].ball->pos.x());
    writeToFile(0,GlobalData::Instance()->maintain[0].ball->pos.y());
    writeToFile(0,GlobalData::Instance()->maintain[0].ball->predict_pos.x());
    writeToFile(0,GlobalData::Instance()->maintain[0].ball->predict_pos.y());
    writeToFile(0,GlobalData::Instance()->maintain[0].ball->velocity.x());
    writeToFile(0,GlobalData::Instance()->maintain[0].ball->velocity.y());
    ballStream.writeRawData("\n",1);

    writeToFile(1,delt_time);
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].raw.pos.x());
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].raw.pos.y());
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].raw.angle);
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].pos.x());
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].pos.y());
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].angle);
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].raw.vel.vx());
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].raw.vel.vy());
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].raw.vel.vr);
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].velocity.vx());
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].velocity.vy());
    writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].velocity.vr);
    writeToFile(1,GlobalData::Instance()->robotCommand[0][0].robotSpeed[0].vx());
    writeToFile(1,GlobalData::Instance()->robotCommand[0][0].robotSpeed[0].vy());
    writeToFile(1,GlobalData::Instance()->robotCommand[0][0].robotSpeed[0].vr);
//    writeToFile(1,GlobalData::Instance()->robotfilterPosVel[0][0][0][0]);
//    writeToFile(1,GlobalData::Instance()->robotfilterPosVel[0][0][0][1]);
//    writeToFile(1,GlobalData::Instance()->robotfilterPosVel[0][0][0][2]);
//    writeToFile(1,GlobalData::Instance()->robotfilterPosVel[0][0][1][0]);
//    writeToFile(1,GlobalData::Instance()->robotfilterPosVel[0][0][1][1]);
//    writeToFile(1,GlobalData::Instance()->robotfilterPosVel[0][0][1][2]);
    writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].pos.x());
    writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].pos.y());
    writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].angle);
    writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].velocity.vx());
    writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].velocity.vy());
    writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].velocity.vr);
    writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].accelerate.x());
    writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].accelerate.y());
    robotStream.writeRawData("\n",1);
}
**/
void CTest::storeTestingDataV2() {

    if(file_num==0){//current_file_num+1){
        ballIO = nullptr;
        ballFile.close();
        QDateTime datetime;
        ballFileName = QString("../LOG/BallSpeed").append(datetime.currentDateTime().toString("yyyy-MM-dd-HH-mm-ss")).append(".txt"); //QString("Test/6/")+QString("ball")+QString::number(file_num)+QString(".txt");
        QDir::setCurrent(qApp->applicationDirPath());
        ballFile.setFileName(ballFileName);
        ballFile.open(QIODevice::WriteOnly | QIODevice::Append);
        ballIO = &ballFile;
        ballStream.setDevice(ballIO);

        //robotIO = nullptr;
        //robotFile.close();
        //robotFileName = QString("Test/6/")+QString("robot")+QString::number(file_num)+QString(".txt");
        //robotFile.setFileName(robotFileName);
        //robotFile.open(QIODevice::WriteOnly | QIODevice::Append);
        //robotIO = &robotFile;
        //robotStream.setDevice(robotIO);
        writeDataInfo();
        file_num++;
    }
    if(GlobalData::Instance()->maintain[0].ball->valid) {
    //if(GlobalData::Instance()->maintain[0].ball->velocity.mod()>min_ballSpeed && GlobalData::Instance()->maintain[0].ball->velocity.mod()<max_ballSpeed) {
    //    state = 1;
        t2 = QTime::currentTime();
        int delt_time = t0.msecsTo(t2);
        writeToFile(0,delt_time); 
    //writeToFile(0,GlobalData::Instance()->processBall[0].ball->raw.pos.x());
    //writeToFile(0,GlobalData::Instance()->processBall[0].ball->raw.pos.y());
    //writeToFile(0,GlobalData::Instance()->camera[2][0].ball[0].pos.x());
    //writeToFile(0,GlobalData::Instance()->camera[2][0].ball[0].pos.y());
    //writeToFile(0,GlobalData::Instance()->processBall[0].ball->pos.x());
    //writeToFile(0,GlobalData::Instance()->processBall[0].ball->pos.y());
    //writeToFile(0,GlobalData::Instance()->processBall[0].ball->raw.vel.vx());
    //writeToFile(0,GlobalData::Instance()->processBall[0].ball->raw.vel.vy());
    //writeToFile(0,GlobalData::Instance()->processBall[0].ball->velocity.x());
    //writeToFile(0,GlobalData::Instance()->processBall[0].ball->velocity.y());
        writeToFile(0,GlobalData::Instance()->maintain[0].ball->velocity.x());
        writeToFile(0,GlobalData::Instance()->maintain[0].ball->velocity.y());
        writeToFile(0,GlobalData::Instance()->maintain[0].ball->velocity.mod());
        writeToFile(0,GlobalData::Instance()->maintain[0].ball->pos.x());
        writeToFile(0,GlobalData::Instance()->maintain[0].ball->pos.y());
    }
    //else if(state) {
    //        t2 = QTime::currentTime();
    //        int delt_time = t0.msecsTo(t2);
    //        writeToFile(0,delt_time);
    //        state = 0;
    //    }
    else return;
    ballStream.writeRawData("\n",1);

    //writeToFile(1,delt_time);
    //writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].raw.pos.x());
    //writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].raw.pos.y());
    //writeToFile(1,GlobalData::Instance()->processRobot[0].robot[0][0].raw.angle);
    //writeToFile(1,GlobalData::Instance()->camera[2][0].robot[0][0].pos.x());
    //writeToFile(1,GlobalData::Instance()->camera[2][0].robot[0][0].pos.y());
    //writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].pos.x());
    //writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].pos.y());
    //writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].angle);
    //writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].velocity.vx());
    //writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].velocity.vy());
    //writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].velocity.vr);
    //writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].accelerate.x());
    //writeToFile(1,GlobalData::Instance()->maintain[0].robot[0][0].accelerate.y());
    //robotStream.writeRawData("\n",1);
}

void CTest::writeDataInfo(){
    //const char* info = "time\trealX\trealY\tVisionX\tVisionY\t"
    //                   "realVx\trealVy\tVisionVx\tVisionVy\t"
    //                   //"filteredX\tfilteredY\tfilteredVx\tfilteredVy\t"
    //                   "EstimatedX\tEstimatedY\tPredixtedX\tPredictedY\tEstimatedVx\tEstimatedVy";
    const char* info = "time(ms)\tVx(mm/s)\tVy(mm/s)\tVel(mm/s)\tX(mm)\tY(mm)";
    ballStream.writeRawData(info, strlen(info));
    //info = "time\trealX\trealY\trealR\tVisionX\tVisionY\tVisionR\t"
    //       "realVx\trealVy\trealVr\tVisionVx\tVisionVy\tVisionVr\tCmdVx\tCmdVy\tCmdVr\t"
    //       //"filteredX\tfilteredY\tfilteredR\tfilteredVx\tfilteredVy\tfilteredVr\t"
    //       "EstimatedX\tEstimatedY\tEstimatedR\tEstimatedVx\tEstimatedVy\tEstimatedVr\tEstimatedAx\tEstimatedAy";
    //robotStream.writeRawData(info, strlen(info));
    ballStream.writeRawData("\n",1);
    //robotStream.writeRawData("\n",1);
}

void CTest::writeToFile(bool isrobot, double num){
    std::string str = std::to_string(num);
    const char* ch = str.data();
    ballStream.writeRawData(ch,strlen(ch));
    ballStream.writeRawData("\t",1);
    //isrobot? robotStream.writeRawData(ch,strlen(ch)):ballStream.writeRawData(ch,strlen(ch));
    //isrobot? robotStream.writeRawData("\t",1): ballStream.writeRawData("\t",1);
}
