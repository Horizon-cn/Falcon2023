#include "rec_recorder.h"
#include "visionmodule.h"
#include "globaldata.h"
#include "globalsettings.h"
#include "field.h"
#include <qdebug.h>
#include <QDateTime>
#include <QDataStream>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "staticparams.h"

namespace  {
auto GS = GlobalSettings::Instance();
//RecMsg recMsg;
bool isRun = false;
bool recordRawVision = true;
bool isNewPacketRecv = false;

QFile recordFile;
QIODevice* recIO;
QString filename;

//QTime timer;
}
RecRecorder::RecRecorder(QQuickItem *parent): QQuickItem(parent) {
    connect(VisionModule::Instance(), SIGNAL(recvPacket()), this, SLOT(markNewPacket()));
}
RecRecorder::~RecRecorder() {
    stop();
    delete recIO;
}
void RecRecorder::start() {
    isRun = true;
//        qDebug() << "I AM RUNNING";
    QDateTime datetime;
//        qDebug() << datetime.currentDateTime().toString("yyyy-MM-dd-HH-mm-ss");
    filename = QString("../LOG/Rec").append(datetime.currentDateTime().toString("yyyy-MM-dd-HH-mm-ss")).append(".log");
//    recordFile = new QFile(filename);
    QDir::setCurrent(qApp->applicationDirPath());
    recordFile.setFileName(filename);
//    recordFile.open(QIODevice::WriteOnly | QIODevice::Append);
//    recIO = &recordFile;
//    recordFile->open(QIODevice::WriteOnly | QIODevice::Append);
    isNewPacketRecv = false;
}

void RecRecorder::store() {
    if (isRun && isNewPacketRecv) {
        ZSS::Protocol::RecMessage* recMsg;
        ZSS::Protocol::TeamRobotMsg* processMsg;
        ZSS::Protocol::TeamRobotMsg* maintain;
        ZSS::Protocol::Robot4Rec* robot4Rec;
        ZSS::Protocol::Ball4Rec* ball4Rec;
        ZSS::Protocol::Debug_Msgs* debugMsgs;

        recMsg = recMsgs.add_recmsgs();

        //ctrlc
        GlobalData::Instance()->ctrlCMutex.lock();
        recMsg->set_ctrlc(GlobalData::Instance()->ctrlC);
        GlobalData::Instance()->ctrlCMutex.unlock();
        //selectedArea
        recMsg->mutable_selectedarea()->set_maxx(GS->maximumX);
        recMsg->mutable_selectedarea()->set_maxy(GS->maximumY);
        recMsg->mutable_selectedarea()->set_minx(GS->minimumX);
        recMsg->mutable_selectedarea()->set_miny(GS->minimumY);
        //maintainVision
        //processRobot
        const Owl::OriginMessage &robot_vision = GlobalData::Instance()->processRobot[0];
        recMsg->mutable_maintainvision()->set_lasttouch(GlobalData::Instance()->lastTouch % PARAM::ROBOTMAXID);
        recMsg->mutable_maintainvision()->set_lasttouchteam(GlobalData::Instance()->lastTouch < PARAM::ROBOTMAXID ? PARAM::BLUE : PARAM::YELLOW);
        for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
            processMsg = recMsg->mutable_maintainvision()->add_processmsg();
            processMsg->set_size(robot_vision.robotSize[color]);
            for(int j = 0; j < robot_vision.robotSize[color]; j++) {
                robot4Rec = processMsg->add_robot();
                robot4Rec->set_id(robot_vision.robot[color][j].id);
                robot4Rec->set_posx(robot_vision.robot[color][j].pos.x());
                robot4Rec->set_posy(robot_vision.robot[color][j].pos.y());
                robot4Rec->set_angle(robot_vision.robot[color][j].angle);
            }
        }
        //maintainRobot
        auto& maintainMsg = GlobalData::Instance()->maintain[0];
        for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
            maintain = recMsg->mutable_maintainvision()->add_maintain();
            maintain->set_size(maintainMsg.robotSize[color]);
            for(int j = 0; j < maintainMsg.robotSize[color]; j++) {
                robot4Rec = maintain->add_robot();
                robot4Rec->set_posx(maintainMsg.robot[color][j].pos.x());
                robot4Rec->set_posy(maintainMsg.robot[color][j].pos.y());
                robot4Rec->set_angle(maintainMsg.robot[color][j].angle);
            }
        }
        //maintainBall
        recMsg->mutable_maintainvision()->mutable_balls()->set_size(maintainMsg.ballSize);
        for(int j = 0; j < maintainMsg.ballSize; j++) {
            ball4Rec = recMsg->mutable_maintainvision()->mutable_balls()->add_ball();
            ball4Rec->set_posx(maintainMsg.ball[j].pos.x());
            ball4Rec->set_posy(maintainMsg.ball[j].pos.y());
            ball4Rec->set_valid(maintainMsg.ball[j].valid);
        }
        //debugMsgs
        GlobalData::Instance()->debugMutex.lock();
        for (int team = PARAM::BLUE; team <= PARAM::YELLOW; team++) {
            debugMsgs = recMsg->add_debugmsgs();
            if (team == 0) {
                debugMsgs->ParseFromArray(GlobalData::Instance()->debugBlueMessages.data(), GlobalData::Instance()->debugBlueMessages.size());
            } else {
                debugMsgs->ParseFromArray(GlobalData::Instance()->debugYellowMessages.data(), GlobalData::Instance()->debugYellowMessages.size());
            }
        }

        GlobalData::Instance()->debugMutex.unlock();

    }
}

void RecRecorder::storeRaw() {
    if (isRun && isNewPacketRecv) {
        SSL_WrapperPacket* ssl_wrapperPacket;
        //rawVisions
        if(recordRawVision) {
            ssl_wrapperPacket = recMsgs.add_ssl_wrapperpacket();
            ssl_wrapperPacket->CopyFrom(GlobalData::Instance()->ssl_wrapperPacket);
        }
    }
}

void RecRecorder::cut(bool isCutting) {
    isRun = !isCutting;
}

void RecRecorder::stop() {
    isRun = false;
    recordFile.open(QIODevice::WriteOnly | QIODevice::Append);
    recIO = &recordFile;

    QDataStream stream(recIO);
    int size = recMsgs.ByteSize();
    QByteArray buffer(size, 0);
    recMsgs.SerializeToArray(buffer.data(), buffer.size());
    stream<<buffer;

    //st << totalbuf;
    QFileInfo afterFile(filename);
    recIO = nullptr;
    recordFile.close();
    if (afterFile.size() < 1) {
       recordFile.remove();
    }
    recIO = nullptr;
    recordFile.close();
    recMsgs.Clear();
}

void RecRecorder::setRecordRawVision (bool _recordRawVision){
    recordRawVision = _recordRawVision;
}

void RecRecorder::markNewPacket(){
    isNewPacketRecv = true;
}
