#include "visionmodule.h"
#include "communicator.h"
#include "globaldata.h"
#include "maintain.h"
#include "dealball.h"
#include "dealrobot.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include "field.h"
#include "parammanager.h"
#include "globalsettings.h"
#include "rec_recorder.h"
#include <QElapsedTimer>
#include <QtDebug>
#include <QFile>
#include "staticparams.h"
#include "networkinterfaces.h"
#include "Semaphore.h"
Semaphore visionEvent;
namespace {
    std::thread* visionReceiveThread = nullptr;
    std::thread* visionParseThread = nullptr;
    auto GS = GlobalSettings::Instance();
    auto opm = Owl::OParamManager::Instance();
    auto vpm = Owl::VParamManager::Instance();
    auto cpm = Owl::CParamManager::Instance();
    int vision_port; //= opm->isSimulation ? opm->VisionSim : opm->VisionReal;
}
/**
 * @brief CVisionModule consturctor
 * @param parent
 */
CVisionModule::CVisionModule(QObject *parent)
    : QObject(parent)
    , udpReceiveSocket()
    , udpResendSocket()
    , IF_EDGE_TEST(false)
    , _interface(0)
    {

    }

CVisionModule::~CVisionModule() {
    udpSocketDisconnect();
}

void CVisionModule::setIfEdgeTest(bool isEdgeTest) {
    IF_EDGE_TEST = isEdgeTest;
}
/**
 * @brief connect UDP for receive vision
 */
void CVisionModule::udpSocketConnect() {
    GlobalData::Instance()->initVision();
    int grsimInterface = ZCommunicator::Instance()->getGrsimInterfaceIndex();
    if (!opm->isSimulation) {
        vision_port = opm->VisionReal;
    }
    else if(grsimInterface != 0) {
        vision_port = opm->VisionRemote;
    }
    else {
        vision_port = opm->VisionSim;
    }
    if (!opm->isSimulation || grsimInterface != 0 || !opm->useSimInside) {
        //qDebug() << "VisionPort : " << vision_port;

        udpReceiveSocket.bind(QHostAddress::AnyIPv4, vision_port, QUdpSocket::ShareAddress);
        //udpReceiveSocket.joinMulticastGroup(QHostAddress(cpm->ssl_address));
        udpReceiveSocket.joinMulticastGroup(QHostAddress(cpm->ssl_address), NetworkInterfaces::Instance()->getFromIndex(_interface));
        connect(&udpReceiveSocket, SIGNAL(readyRead()), this, SLOT(storeData()), Qt::DirectConnection);
        /**
        visionReceiveThread = new std::thread([=] {receiveVision();});
        visionReceiveThread->detach();
        visionParseThread = new std::thread([=] {parseVision(); });
        visionParseThread->detach();
        **/
    }
    else {

    }
}
void CVisionModule::setInterfaceIndex(const int index) { _interface = index; }
/**
 * @brief disconnect UDP
 */
void CVisionModule::udpSocketDisconnect() {
    if (IF_EDGE_TEST) {
        for (int i = 0; i < opm->total_cameras; i++) {
            Owl::SingleCamera& currentCamera = GlobalData::Instance()->cameraMatrix[i];
            vpm->changeParam("Camera" + QString::number(i) + "Leftmin", currentCamera.leftedge.min);
            vpm->changeParam("Camera" + QString::number(i) + "Leftmax", currentCamera.leftedge.max);
            vpm->changeParam("Camera" + QString::number(i) + "Rightmin", currentCamera.rightedge.min);
            vpm->changeParam("Camera" + QString::number(i) + "Rightmax", currentCamera.rightedge.max);
            vpm->changeParam("Camera" + QString::number(i) + "Upmin", currentCamera.upedge.min);
            vpm->changeParam("Camera" + QString::number(i) + "Upmax", currentCamera.upedge.max);
            vpm->changeParam("Camera" + QString::number(i) + "Downmin", currentCamera.downedge.min);
            vpm->changeParam("Camera" + QString::number(i) + "Downmax", currentCamera.downedge.max);
        }
    }
    disconnect(&udpReceiveSocket);
    udpReceiveSocket.abort();
    udpResendSocket.abort();
    delete visionReceiveThread;
    visionReceiveThread = nullptr;
    delete visionParseThread;
    visionParseThread = nullptr;
}
/**
 * @brief CVisionModule::storeData
 */
void CVisionModule::storeData() {
    static QByteArray datagram;
    while (udpReceiveSocket.hasPendingDatagrams()) {
        datagram.resize(udpReceiveSocket.pendingDatagramSize());
        udpReceiveSocket.readDatagram(datagram.data(), datagram.size());
        if(GlobalData::Instance()->refereeMode){
            udpResendSocket.writeDatagram(datagram.data(), datagram.size(), QHostAddress(cpm->ssl_address), cpm->VisionAutoRef);
            qDebug()<<"resend to autoref";
        }
        parse((void*)datagram.data(), datagram.size());
    }
}
void CVisionModule::receiveVision(){
    auto& datagram = GlobalData::Instance()->rec_vision;
    udpReceiveSocket.bind(QHostAddress::AnyIPv4, vision_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    udpReceiveSocket.joinMulticastGroup(QHostAddress(cpm->ssl_address), NetworkInterfaces::Instance()->getFromIndex(_interface));
    while (true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        while (udpReceiveSocket.state() == QUdpSocket::BoundState && udpReceiveSocket.hasPendingDatagrams()) {
            GlobalData::Instance()->visionMutex.lock();
            datagram.resize(udpReceiveSocket.pendingDatagramSize());
            udpReceiveSocket.readDatagram(datagram.data(),datagram.size());
            if(GlobalData::Instance()->refereeMode){
                udpResendSocket.writeDatagram(datagram.data(), datagram.size(), QHostAddress(cpm->ssl_address), cpm->VisionAutoRef);
                qDebug()<<"resend to autoref";
            }
            GlobalData::Instance()->visionMutex.unlock();
            visionEvent.Signal();
        }
    }
}
/**
 * @brief process data
 * @return
 */
bool CVisionModule::dealWithData() {
    counter++;
    if (IF_EDGE_TEST) edgeTest();
    DealBall::Instance()->run();
    //qDebug("dealing after ball");
    DealRobot::Instance()->run();
    //qDebug("dealing after robot");
    Maintain::Instance()->run();
    return true;
}
void CVisionModule::parseVision() {
    static QByteArray datagram;
    while (true) {
        visionEvent.Wait();
        GlobalData::Instance()->visionMutex.lock();
        datagram = GlobalData::Instance()->rec_vision;
        GlobalData::Instance()->visionMutex.unlock();
        parse((void*)datagram.data(), datagram.size());
    }
}
/**
 * @brief parse camera vision message
 * @param ptr
 * @param size
 */
void CVisionModule::parse(void * ptr, int size) {
    static SSL_WrapperPacket packet;
    Owl::ReceiveVisionMessage message;
    packet.ParseFromArray(ptr, size);
    if (packet.has_login_name() && opm->LoginName != packet.login_name())
        return;
    if (packet.has_geometry() && opm->updateGeometry) {
        const SSL_GeometryFieldSize& field = packet.geometry().field();
        
        if (field.field_length() && field.field_width()) {
            
        }
    }
    if (packet.has_detection()) {
        //t = QTime::currentTime();
        const SSL_DetectionFrame& detection = packet.detection();
        message.camID = detection.camera_id();
        if (message.camID >= opm->total_cameras || message.camID < 0 || !GlobalData::Instance()->cameraControl[message.camID]) {
            qDebug() << "get invalid camera id : " << message.camID;
            return;
        }
        
        int ballSize = detection.balls_size();
        int blueSize = detection.robots_blue_size();
        int yellowSize = detection.robots_yellow_size();

        for (int i = 0; i < ballSize; i++) {
            const SSL_DetectionBall& ball = detection.balls(i);
            if (GS->inChosenArea(GS->saoConvert(CGeoPoint(ball.x(), ball.y())))) {
                //message.addBall(GS->saoConvert(CGeoPoint(ball.x(), ball.y())));
                //message.addBall(GS->saoConvert(CGeoPoint(ball.x(), ball.y())),GS->saoConvert(CGeoPoint(ball.pixel_x(),ball.pixel_y())));
                CGeoPoint rawPos(GS->saoConvert(CGeoPoint(ball.pixel_x(), ball.pixel_y())));
                Owl::RawInfo r(rawPos.x(), rawPos.y(), ball.realvelx(), ball.realvely());
                message.addBall(GS->saoConvert(CGeoPoint(ball.x(), ball.y())), r, ball.z());
            }
        }

        for (int i = 0; i < blueSize; i++) {
            const SSL_DetectionRobot& robot = detection.robots_blue(i);
            if (GS->inChosenArea(GS->saoConvert(CGeoPoint(robot.x(), robot.y())))
                    && robot.robot_id() < PARAM::ROBOTMAXID) {
                //message.addRobot(PARAM::BLUE, robot.robot_id(), GS->saoConvert(CGeoPoint(robot.x(), robot.y())), GS->saoConvert(robot.orientation()), GS->saoConvert(CGeoPoint(robot.pixel_x(), robot.pixel_y())));
                CGeoPoint rawPos(GS->saoConvert(CGeoPoint(robot.pixel_x(), robot.pixel_y())));
                Owl::RawInfo r(rawPos.x(), rawPos.y(), robot.realvelx(), robot.realvely(), GS->saoConvert(robot.pixel_orien()), robot.realvelr() * 0.001);
                message.addRobot(PARAM::BLUE, robot.robot_id(), GS->saoConvert(CGeoPoint(robot.x(), robot.y())), GS->saoConvert(robot.orientation()), r);
            }
        }
        for (int i = 0; i < yellowSize; i++) {
            const SSL_DetectionRobot& robot = detection.robots_yellow(i);
            if (GS->inChosenArea(GS->saoConvert(CGeoPoint(robot.x(), robot.y())))
                    && robot.robot_id() < PARAM::ROBOTMAXID) {
                //message.addRobot(PARAM::YELLOW, robot.robot_id(), GS->saoConvert(CGeoPoint(robot.x(), robot.y())), GS->saoConvert(robot.orientation()), GS->saoConvert(CGeoPoint(robot.pixel_x(), robot.pixel_y())));
                CGeoPoint rawPos(GS->saoConvert(CGeoPoint(robot.pixel_x(), robot.pixel_y())));
                Owl::RawInfo r(rawPos.x(), rawPos.y(), robot.realvelx(), robot.realvely(), GS->saoConvert(robot.pixel_orien()), robot.realvelr() * 0.001);
                message.addRobot(PARAM::YELLOW, robot.robot_id(), GS->saoConvert(CGeoPoint(robot.x(), robot.y())), GS->saoConvert(robot.orientation()), r);
            }
        }
        GlobalData::Instance()->camera[message.camID].push(message);
        GlobalData::Instance()->cameraUpdate[message.camID] = true;
        GlobalData::Instance()->ssl_wrapperPacket.CopyFrom(packet);
        emit recvPacket();
        ZRecRecorder::Instance()->storeRaw();
    }
    if (collectNewVision()) {
        double time = std::clock();
        checkCommand();
        dealWithData();
        //qDebug("deal done");
        udpSend();
        ZRecRecorder::Instance()->store();
        std::fill_n(GlobalData::Instance()->cameraUpdate, opm->total_cameras, false);
        emit needDraw();
        //qDebug()<<std::clock()-time;
    }
}

void CVisionModule::checkCommand() {
    for (int team = 0; team < PARAM::TEAMS; team++) {
        auto commands = ZCommunicator::Instance()->getCommands(team);
        if (commands.valid) {
            GlobalData::Instance()->robotCommand[team].push(commands);
            GlobalData::Instance()->commandMissingFrame[team] = 0;
        } else {
            commands = Owl::RobotCommands();
            GlobalData::Instance()->robotCommand[team].push(commands);
            GlobalData::Instance()->commandMissingFrame[team] >= 20 ?
            GlobalData::Instance()->commandMissingFrame[team] = 20 :
            GlobalData::Instance()->commandMissingFrame[team]++;
        }
    }
    ZCommunicator::Instance()->clearCommands();
}

void  CVisionModule::udpSend() {
    //udp start
    static QUdpSocket udpSendSocket;
    detectionFrame.set_login_name(opm->LoginName);
    auto detectionBall = detectionFrame.mutable_balls();
    Owl::ReceiveVisionMessage result = GlobalData::Instance()->maintain[0];
    if (result.ballSize > 0) {
        detectionBall->set_x(result.ball[0].pos.x());
        if (result.ball[0].pos.y() == 0) detectionBall->set_y(float(0.1));
        else detectionBall->set_y(result.ball[0].pos.y());//to fix a role match bug 2018.6.15
        CVector TransferVel(result.ball[0].velocity.x(), result.ball[0].velocity.y());
        detectionBall->set_vel_x(TransferVel.x());
        detectionBall->set_vel_y(TransferVel.y());
        detectionBall->set_valid(DealBall::Instance()->getValid());
        detectionBall->set_last_touch(GlobalData::Instance()->lastTouch);
        detectionBall->set_ball_state(result.ball[0].ball_state_machine.ballState);
        detectionBall->set_raw_x(GlobalData::Instance()->processBall[0].ball[0].pos.x());
        detectionBall->set_raw_y(GlobalData::Instance()->processBall[0].ball[0].pos.y());
        detectionBall->set_chip_predict_x(GlobalData::Instance()->maintain[0].ball[0].predict_pos.x());
        detectionBall->set_chip_predict_y(GlobalData::Instance()->maintain[0].ball[0].predict_pos.y());
    } else {
        detectionBall->set_valid(false);
        detectionBall->set_x(-32767);
        detectionBall->set_y(-32767);
    }
    for (int team = 0; team < PARAM::TEAMS; team++) {
        for (int i = 0; i < result.robotSize[team]; i++) {
            if (i >= PARAM::ROBOTMAXID) break; //for sending MAX 11 car possible
            if (result.robot[team][i].id < 0 || result.robot[team][i].id >= PARAM::ROBOTMAXID)
                continue;
            Vision_DetectionRobot* robot;
            if (team == 0 )  robot = detectionFrame.add_robots_blue();
            else robot = detectionFrame.add_robots_yellow();
            robot->set_x(result.robot[team][i].pos.x());
            robot->set_y(result.robot[team][i].pos.y());
            robot->set_orientation(result.robot[team][i].angle);
            robot->set_robot_id(result.robot[team][i].id);
            if(result.robot[team][i].id < 0) qDebug()<<result.robot[team][i].id;
            CVector TransferVel(result.robot[team][i].velocity.vx(),
                                result.robot[team][i].velocity.vy());
            robot->set_vel_x(TransferVel.x());
            robot->set_vel_y(TransferVel.y());
            robot->set_rotate_vel(result.robot[team][i].velocity.vr);
            //robot->set_vel_x(GlobalData::Instance()->processRobot[-1].robot[team][i].raw.vel.vx());
            //robot->set_vel_y(GlobalData::Instance()->processRobot[-1].robot[team][i].raw.vel.vy());
            //robot->set_rotate_vel(GlobalData::Instance()->processRobot[-1].robot[team][i].raw.vel.vr);
            //robot->set_vel_x(GlobalData::Instance()->robotCommand[team][0].robotSpeed[result.robot[team][i].id].vx());
            //robot->set_vel_y(GlobalData::Instance()->robotCommand[team][0].robotSpeed[result.robot[team][i].id].vy());
            //robot->set_rotate_vel(GlobalData::Instance()->robotCommand[team][0].robotSpeed[result.robot[team][i].id].vr);
            robot->set_accelerate_x(result.robot[team][i].accelerate.x());
            robot->set_accelerate_y(result.robot[team][i].accelerate.y());
            robot->set_raw_x(GlobalData::Instance()->processRobot[-1].robot[team][i].pos.x());
            robot->set_raw_y(GlobalData::Instance()->processRobot[-1].robot[team][i].pos.y());
            robot->set_raw_orientation(GlobalData::Instance()->processRobot[-1].robot[team][i].angle);
            robot->set_valid(true);
        }
    }

    int size = detectionFrame.ByteSize();
    QByteArray buffer(size, 0);
    detectionFrame.SerializeToArray(buffer.data(), buffer.size());
    GlobalData::Instance()->ctrlCMutex.lock();
    bool sw = GlobalData::Instance()->ctrlC;
    GlobalData::Instance()->ctrlCMutex.unlock();
    if(!sw) { //需要发两个端口以供对打
        if(GlobalData::Instance()->processControl[PARAM::BLUE])
            udpSendSocket.writeDatagram(buffer.data(), buffer.size(), QHostAddress(cpm->local_address), cpm->blue_vision);
        if(GlobalData::Instance()->processControl[PARAM::YELLOW])
            udpSendSocket.writeDatagram(buffer.data(), buffer.size(), QHostAddress(cpm->local_address), cpm->yellow_vision);
        udpSendSocket.abort();
    }
    detectionFrame.clear_robots_blue();
    detectionFrame.clear_robots_yellow();
}

/**
 * @brief judge if all needed camera vision is collected
 * @return
 */
bool CVisionModule::collectNewVision() {
    for (int i = 0; i < opm->total_cameras; i++) {
        if (GlobalData::Instance()->cameraControl[i] && !GlobalData::Instance()->cameraUpdate[i])
            return false;
    }
    return true;
} 
/**
 * @brief filed edgeTest
 */
void CVisionModule::edgeTest() {
    for (int i = 0; i < opm->total_cameras; i++) {
        if (GlobalData::Instance()->cameraControl[i] == true) {
            Owl::SingleCamera& currentCamera = GlobalData::Instance()->cameraMatrix[i];
            for(int j = 0; j < GlobalData::Instance()->camera[i][0].ballSize; j++) {
                Owl::Ball currentball = GlobalData::Instance()->camera[i][0].ball[j];
                if (currentball.pos.x() < currentCamera.leftedge.min) currentCamera.leftedge.min = currentball.pos.x();
                if (currentball.pos.x() > currentCamera.rightedge.min) currentCamera.rightedge.min = currentball.pos.x();
                if (currentball.pos.y() > currentCamera.upedge.min) currentCamera.upedge.min = currentball.pos.y();
                if (currentball.pos.y() < currentCamera.downedge.min) currentCamera.downedge.min = currentball.pos.y();
            }
        }
    }
    for (int i = 0; i < opm->total_cameras; i++) {
        if (GlobalData::Instance()->cameraControl[i] == true) {
            Owl::SingleCamera& currentCamera = GlobalData::Instance()->cameraMatrix[i];
            currentCamera.leftedge.max = currentCamera.leftedge.min;
            currentCamera.rightedge.max = currentCamera.rightedge.min;
            currentCamera.upedge.max = currentCamera.upedge.min;
            currentCamera.downedge.max = currentCamera.downedge.min;
            for (int j = 0; j < opm->total_cameras; j++)
                if(GlobalData::Instance()->cameraControl[j] == true && i != j) {
                    Owl::SingleCamera otherCamera = GlobalData::Instance()->cameraMatrix[j];
                    if (currentCamera.leftedge.max < otherCamera.rightedge.min && currentCamera.campos.x() > otherCamera.rightedge.min)
                        currentCamera.leftedge.max = otherCamera.rightedge.min;
                    if (currentCamera.rightedge.max > otherCamera.leftedge.min && currentCamera.campos.x() < otherCamera.leftedge.min)
                        currentCamera.rightedge.max = otherCamera.leftedge.min;
                    if (currentCamera.upedge.max > otherCamera.downedge.min && currentCamera.campos.y() < otherCamera.downedge.min)
                        currentCamera.upedge.max = otherCamera.downedge.min;
                    if (currentCamera.downedge.max < otherCamera.upedge.min && currentCamera.campos.y() > otherCamera.upedge.min)
                        currentCamera.downedge.max = otherCamera.upedge.min;
                }
        }
    }
}
/**
 * @brief getFPS for front
 * @return
 */
quint16 CVisionModule::getFPS() {
    //static QElapsedTimer timer;
    static QTime last_t, t;
    static double dt = 0;
    static bool ifStart = false;
    static quint64 lastCount;
    static quint16 result;
    if (!ifStart) {
        ifStart = true;
        last_t = QTime::currentTime();
        //timer.start();
        lastCount = counter;
        return 0;
    }
    t = QTime::currentTime();
    dt = last_t.msecsTo(t);
    last_t = t;
    result = (counter - lastCount) * 1000.0 / dt;
    //result = (counter - lastCount) * 1000.0 / timer.restart();
    lastCount = counter;
    FPS = int(result);
    return result;
}
