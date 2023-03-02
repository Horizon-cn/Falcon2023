#include "rec_player.h"
#include "field.h"
#include "globaldata.h"
#include "globalsettings.h"
#include "visionmodule.h"
#include "rec_recorder.h"
#include <QIODevice>
#include <QDataStream>
#include <QTime>
#include <QtDebug>
#include "staticparams.h"
#include <iostream>
#include <fstream>
namespace  {
    auto opm = Owl::OParamManager::Instance();
    auto GS = GlobalSettings::Instance();
    //std::ofstream outFile;
}
CRecPlayer::CRecPlayer() {
    udpSendSocket = nullptr;
    //outFile.open("test.csv", std::ios::out | std::ios::trunc);
    // 写入标题行
    //outFile << "team" << "," << "id" << "," << "x" << "," << "y" << std::endl;
}

CRecPlayer::~CRecPlayer() {
    //outFile.close();
    stop();
    //delete replayFile;
    //replayFile = nullptr;
    //udpSendSocket.abort();
    //udpSendSocket = nullptr;
    QThread::quit();
}

bool CRecPlayer::loadRec(QString &filename, int &maxframe) {
    num = 0;
    replayFile = new QFile(filename);
    if (replayFile->open(QIODevice::ReadOnly)) {
        QIODevice* recIO;
        recIO = replayFile;
        QDataStream stream(recIO);
        QByteArray packet;
        stream >> packet;
        recMsgs.ParseFromArray(packet.data(), packet.size());
        maxframe = recMsgs.recmsgs_size() - 2;
        delete replayFile;
        replayFile = nullptr;
        return true;
    }
    qDebug() << "open filed";
    return false;
}

bool CRecPlayer::start(int position) {
    if (position > recMsgs.recmsgs_size() - 1) {
        return false;
    }

    _currentFrame = position;

    _run = true;
    QThread::start(); //运行run()

    return true;
}

void CRecPlayer::slowly(int position) {
    if (position > recMsgs.recmsgs_size() - 1) {
        return;
    }

    _currentFrame = position;

    QThread::start();
}

void CRecPlayer::stop() {
    _run = false;
    QThread::wait();
    //QThread::quit();
}

bool CRecPlayer::good() {
    return recMsgs.recmsgs_size() > 0;
}

void CRecPlayer::sendMessage(const QByteArray& packet) {
    qDebug() << "sendmessage is called" ;
    ZSS::Protocol::RecMessage recMsg;
    recMsg.ParseFromArray(packet.data(), packet.size());
    //ctrlc
    GlobalData::Instance()->ctrlCMutex.lock();
    GlobalData::Instance()->ctrlC = recMsg.ctrlc();
    GlobalData::Instance()->ctrlCMutex.unlock();
    //selectedArea
    GS->maximumX = recMsg.selectedarea().maxx();
    GS->minimumX = recMsg.selectedarea().minx();
    GS->maximumY = recMsg.selectedarea().maxy();
    GS->minimumY = recMsg.selectedarea().miny();
    //maintainVision
    GlobalData::Instance()->lastTouch = recMsg.maintainvision().lasttouchteam() == PARAM::BLUE ? recMsg.maintainvision().lasttouch() : recMsg.maintainvision().lasttouch() + PARAM::ROBOTMAXID;
    Owl::ReceiveVisionMessage result;
    for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
//        processMsg = recMsg->mutable_maintainvision()->add_processmsg();
//        processMsg->set_size(robot_vision.robotSize[color]);
        for(int j = 0; j < recMsg.maintainvision().processmsg(color).size(); j++) {
            result.addRobot(color,
                            recMsg.maintainvision().processmsg(color).robot(j).id(),
                            recMsg.maintainvision().processmsg(color).robot(j).posx(),
                            recMsg.maintainvision().processmsg(color).robot(j).posy(),
                            recMsg.maintainvision().processmsg(color).robot(j).angle());
        }
    }
    GlobalData::Instance()->processRobot.push(result);
//    qDebug() << "FUCKING MSG" << GlobalData::Instance()->processRobot[0].robotSize[0];
//    auto& maintainMsg = GlobalData::Instance()->maintain[0];
    Owl::ReceiveVisionMessage maintainResult;
    for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
//        maintain = recMsg->mutable_maintainvision()->add_maintain();
//        maintain->set_size(maintainMsg.robotSize[color]);
        for(int j = 0; j < recMsg.maintainvision().maintain(color).size(); j++) {
            maintainResult.addRobot(color,
                                    recMsg.maintainvision().maintain(color).robot(j).id(),
                                    recMsg.maintainvision().maintain(color).robot(j).posx(),
                                    recMsg.maintainvision().maintain(color).robot(j).posy(),
                                    recMsg.maintainvision().maintain(color).robot(j).angle());
        }
    }
//    recMsg->mutable_maintainvision()->mutable_balls()->set_size(maintainMsg.ballSize);
    for(int j = 0; j < recMsg.maintainvision().balls().size(); j++) {
        maintainResult.addBall(recMsg.maintainvision().balls().ball(j).posx(),
                               recMsg.maintainvision().balls().ball(j).posy());
        maintainResult.ball[j].valid = recMsg.maintainvision().balls().ball(j).valid();
    }
    GlobalData::Instance()->maintain.push(maintainResult);
    //debugMsgs
    GlobalData::Instance()->debugMutex.lock();
    ZSS::Protocol::Debug_Msgs debugMsgs;
    for (int team = PARAM::BLUE; team <= PARAM::YELLOW; team++) {
        debugMsgs = recMsg.debugmsgs(team);
        int size = debugMsgs.ByteSize();
        if (team == 0) {
            GlobalData::Instance()->debugBlueMessages.resize(size);
            debugMsgs.SerializeToArray(GlobalData::Instance()->debugBlueMessages.data(), size);
        } else {
            GlobalData::Instance()->debugYellowMessages.resize(size);
            debugMsgs.SerializeToArray(GlobalData::Instance()->debugYellowMessages.data(), size);
        }
//        qDebug() << "FUCK DEBUG MESSAGE SIZE" <<  debugMsgs.ByteSize() << GlobalData::Instance()->debugBlueMessages.size();
    }
    GlobalData::Instance()->debugMutex.unlock();
    
}

void CRecPlayer::sendMessage(const ZSS::Protocol::RecMessage& recMsg) {
    //qDebug()<<"RecPlayer::sendMessage"<<calCamNum();
    //ctrlc
    GlobalData::Instance()->ctrlCMutex.lock();
    GlobalData::Instance()->ctrlC = recMsg.ctrlc();
    GlobalData::Instance()->ctrlCMutex.unlock();
    //selectedArea
    GS->maximumX = recMsg.selectedarea().maxx();
    GS->minimumX = recMsg.selectedarea().minx();
    GS->maximumY = recMsg.selectedarea().maxy();
    GS->minimumY = recMsg.selectedarea().miny();
    //maintainVision
    GlobalData::Instance()->lastTouch = recMsg.maintainvision().lasttouchteam() == PARAM::BLUE ? recMsg.maintainvision().lasttouch() : recMsg.maintainvision().lasttouch() + PARAM::ROBOTMAXID;
    Owl::ReceiveVisionMessage result;
    for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
        for(int j = 0; j < recMsg.maintainvision().processmsg(color).size(); j++) {
            result.addRobot(color,
                            recMsg.maintainvision().processmsg(color).robot(j).id(),
                            recMsg.maintainvision().processmsg(color).robot(j).posx(),
                            recMsg.maintainvision().processmsg(color).robot(j).posy(),
                            recMsg.maintainvision().processmsg(color).robot(j).angle());
            //std::string team = color == 0 ? "BLUE" : "YELLOW";
            //outFile << team << "," << std::to_string(recMsg.maintainvision().processmsg(color).robot(j).id()) << ","
            //    << std::to_string(recMsg.maintainvision().processmsg(color).robot(j).posx()) << ","
            //    << std::to_string(recMsg.maintainvision().processmsg(color).robot(j).posy()) << std::endl;
        }
    }
    GlobalData::Instance()->processRobot.push(result);
    Owl::ReceiveVisionMessage maintainResult;
    for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
        for(int j = 0; j < recMsg.maintainvision().maintain(color).size(); j++) {
            maintainResult.addRobot(color,
                                    recMsg.maintainvision().maintain(color).robot(j).id(),
                                    recMsg.maintainvision().maintain(color).robot(j).posx(),
                                    recMsg.maintainvision().maintain(color).robot(j).posy(),
                                    recMsg.maintainvision().maintain(color).robot(j).angle());
        }
    }
    for(int j = 0; j < recMsg.maintainvision().balls().size(); j++) {
        maintainResult.addBall(recMsg.maintainvision().balls().ball(j).posx(),
                               recMsg.maintainvision().balls().ball(j).posy());
        maintainResult.ball[j].valid = recMsg.maintainvision().balls().ball(j).valid();
    }
    GlobalData::Instance()->maintain.push(maintainResult);
    //debugMsgs
    GlobalData::Instance()->debugMutex.lock();
    ZSS::Protocol::Debug_Msgs debugMsgs;
    for (int team = PARAM::BLUE; team <= PARAM::YELLOW; team++) {
        debugMsgs = recMsg.debugmsgs(team);
        int size = debugMsgs.ByteSize();
        if (team == 0) {
            GlobalData::Instance()->debugBlueMessages.resize(size);
            debugMsgs.SerializeToArray(GlobalData::Instance()->debugBlueMessages.data(), size);
        } else {
            GlobalData::Instance()->debugYellowMessages.resize(size);
            debugMsgs.SerializeToArray(GlobalData::Instance()->debugYellowMessages.data(), size);
        }
    }
    GlobalData::Instance()->debugMutex.unlock();
}

void CRecPlayer::sendMessage(const SSL_WrapperPacket packet) {
    Owl::ReceiveVisionMessage message;
    const SSL_DetectionFrame& detection = packet.detection();
    message.camID = detection.camera_id();
    if (message.camID >= PARAM::CAMERA || message.camID < 0) {
        qDebug() << "get invalid camera id : " << message.camID;
        return;
    }
    int ballSize = detection.balls_size();
    int blueSize = detection.robots_blue_size();
    int yellowSize = detection.robots_yellow_size();

    for (int i = 0; i < ballSize; i++) {
        const SSL_DetectionBall& ball = detection.balls(i);
        if (GlobalSettings::Instance()->inChosenArea(GS->saoConvert(CGeoPoint(ball.x(), ball.y())))) {
            //message.addBall(GS->saoConvert(CGeoPoint(ball.x(), ball.y())));
            //message.addBall(GS->saoConvert(CGeoPoint(ball.x(), ball.y())),GS->saoConvert(CGeoPoint(ball.pixel_x(),ball.pixel_y())));
            CGeoPoint rawPos(GS->saoConvert(CGeoPoint(ball.pixel_x(), ball.pixel_y())));
            Owl::RawInfo r(rawPos.x(), rawPos.y(), ball.realvelx(), ball.realvely());
            message.addBall(GS->saoConvert(CGeoPoint(ball.x(), ball.y())), r, ball.z());
        }
    }

    for (int i = 0; i < blueSize; i++) {
        const SSL_DetectionRobot& robot = detection.robots_blue(i);
        if (GlobalSettings::Instance()->inChosenArea(GS->saoConvert(CGeoPoint(robot.x(), robot.y()))) && robot.robot_id() < PARAM::ROBOTMAXID) {
            //message.addRobot(PARAM::BLUE, robot.robot_id(), GS->saoConvert(CGeoPoint(robot.x(), robot.y())), GS->saoConvert(robot.orientation()), GS->saoConvert(CGeoPoint(robot.pixel_x(), robot.pixel_y())));
            CGeoPoint rawPos(GS->saoConvert(CGeoPoint(robot.pixel_x(), robot.pixel_y())));
            Owl::RawInfo r(rawPos.x(), rawPos.y(), robot.realvelx(), robot.realvely(), GS->saoConvert(robot.pixel_orien()), robot.realvelr() * 0.001);
            message.addRobot(PARAM::BLUE, robot.robot_id(), GS->saoConvert(CGeoPoint(robot.x(), robot.y())), GS->saoConvert(robot.orientation()), r);
        }
    }
    for (int i = 0; i < yellowSize; i++) {
        const SSL_DetectionRobot& robot = detection.robots_yellow(i);
        if (GlobalSettings::Instance()->inChosenArea(GS->saoConvert(CGeoPoint(robot.x(), robot.y()))) && robot.robot_id() < PARAM::ROBOTMAXID) {
            //message.addRobot(PARAM::YELLOW, robot.robot_id(), GS->saoConvert(CGeoPoint(robot.x(), robot.y())), GS->saoConvert(robot.orientation()), GS->saoConvert(CGeoPoint(robot.pixel_x(), robot.pixel_y())));
            CGeoPoint rawPos(GS->saoConvert(CGeoPoint(robot.pixel_x(), robot.pixel_y())));
            Owl::RawInfo r(rawPos.x(), rawPos.y(), robot.realvelx(), robot.realvely(), GS->saoConvert(robot.pixel_orien()), robot.realvelr() * 0.001);
            message.addRobot(PARAM::YELLOW, robot.robot_id(), GS->saoConvert(CGeoPoint(robot.x(), robot.y())), GS->saoConvert(robot.orientation()), r);
        }
    }
    GlobalData::Instance()->camera[message.camID].push(message);
    GlobalData::Instance()->cameraUpdate[message.camID] = true;
}

int CRecPlayer::calCamNum() {
    int cam[PARAM::CAMERA] = {0,0,0,0,0,0,0,0};
    int i = 0;
    for (; i <= PARAM::CAMERA; i++) {
        if (!cam[recMsgs.ssl_wrapperpacket(i).detection().camera_id()]){
            cam[recMsgs.ssl_wrapperpacket(i).detection().camera_id()] = 1;
            continue;
        }
        else
            break;
    }
    return i;
}

void CRecPlayer::sendMessageToWeb(const QByteArray* packet){
    udpSendSocket->writeDatagram((char*)packet->data(), packet->size(), QHostAddress("224.5.23.2"), 10020);
}

void CRecPlayer::sendMessageToWeb(const SSL_WrapperPacket* ssl_wrapperpacket){
    QByteArray buffer(ssl_wrapperpacket->ByteSize(),0);
    ssl_wrapperpacket->SerializeToArray(buffer.data(),buffer.size());
    udpSendSocket->writeDatagram(buffer.data(),buffer.size(),QHostAddress("224.5.23.2"),10020);
}

void CRecPlayer::playLogVision() {
    emit VisionModule::Instance()->recvPacket();
    if(playRawVision) {
        for(int i=0;i<num;i++) {
            const SSL_WrapperPacket packet = recMsgs.ssl_wrapperpacket(_currentFrame*num+i);
            sendMessage(packet);
            GlobalData::Instance()->ssl_wrapperPacket.CopyFrom(packet);        
            ZRecRecorder::Instance()->storeRaw();
        }
        //VisionModule::Instance()->dealWithData();
        //GlobalData::Instance()->processRobot.pop();
        //GlobalData::Instance()->maintain.pop();
    }
    sendMessage(recMsgs.recmsgs(_currentFrame));
    ZRecRecorder::Instance()->store();
    //sendMessageToWeb(&recMsgs.ssl_wrapperpacket(_currentFrame));
    emit positionChanged(_currentFrame);
    emit VisionModule::Instance()->needDraw();
}

void CRecPlayer::run() {
    num = num==0? calCamNum():num;
    qDebug()<<"Camera Number"<<num;
    //if(udpSendSocket==nullptr){ udpSendSocket = new QUdpSocket(); }
    playLogVision();
    while (_run && ++_currentFrame < recMsgs.recmsgs_size() - 1 && this->isRunning()) {
        playLogVision();
        QThread::currentThread()->msleep(12/playerRate);
    }
}
