#include "communicator.h"
#include <QNetworkInterface>
#include "actionmodule.h"
#include "simmodule.h"
#include "remotesim.h"
#include "parammanager.h"
#include "globaldata.h"
#include "globalsettings.h"
#include <mutex>
#include <thread>
#include "staticparams.h"
#include <fstream>
#include <QString>
#include <QDateTime>
namespace {
int fps[PARAM::TEAMS] = {0, 0};
std::mutex m_fps;
std::thread* receiveThread[PARAM::TEAMS];
auto opm = Owl::OParamManager::Instance(); 
auto cpm = Owl::CParamManager::Instance();
}
int Communicator::getFPS(int t) {
    int res = 0;
    m_fps.lock();
    res = fps[t];
    fps[t] = 0;
    m_fps.unlock();
    return res;
}

void Communicator::setGrsimInterfaceIndex(const int index) {
    grsimInterfaceIndex = index;
}

Communicator::Communicator(QObject *parent) : QObject(parent) {
    QObject::connect(Owl::ZSimModule::Instance(), SIGNAL(receiveSimInfo(int, int)), this, SLOT(sendCommand(int, int)));
    QObject::connect(ZSS::ZRemoteSimModule::Instance(), SIGNAL(receiveRemoteInfo(int, int)), this, SLOT(sendCommand(int, int)),Qt::DirectConnection);
    QObject::connect(Owl::ActionModule::Instance(), SIGNAL(receiveRobotInfo(int, int)), this, SLOT(sendCommand(int, int)));
    for(int i = 0; i < PARAM::TEAMS; i++) {
        /** connect(&receiveSocket[i], &QUdpSocket::readyRead, [ = ]() {
            receiveCommand(i);
        });**/
        if(connectMedusa(i)) { //连接
            receiveThread[i] = new std::thread([ = ] {receiveCommand(i);}); //接受cmd
            //receiveThread[i] = new std::thread([ = ] {sendEmptyCmd(i);});
            receiveThread[i]->detach();
        }
    }
}
Communicator::~Communicator() {
    sendSockets.disconnectFromHost();
    for(int i = 0; i < PARAM::TEAMS; i++) {
        receiveSocket[i].abort();
    }
}
bool Communicator::connectMedusa(int team) {
    int port = team == PARAM::BLUE? cpm->blue_control : cpm->yellow_control;
    if (receiveSocket[team].bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        return true;
    }
    qDebug() << "Bind ERROR";
    disconnectMedusa(team);
    return false;
}
bool Communicator::disconnectMedusa(int team) {
    receiveSocket[team].disconnectFromHost();
    return true;
}

void Communicator::receiveCommand(int t) {
    QByteArray datagram;
    while(true) {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        while (receiveSocket[t].state() == QUdpSocket::BoundState && receiveSocket[t].hasPendingDatagrams()) {
            m_fps.lock();
            fps[t]++;
            m_fps.unlock();
            datagram.resize(receiveSocket[t].pendingDatagramSize());
            receiveSocket[t].readDatagram(datagram.data(), datagram.size());
            //rbk::protocol::SRC_Cmd commands;
            ZSS::Protocol::Robots_Command commands;
            commands.ParseFromArray(datagram, datagram.size());
            commandBuffer[t].valid = true;
            for(int i = 0; i < commands.command_size(); i++) {
                auto& command = commands.command(i);
                Owl::RobotSpeed rs(command.velocity_x()*1000, command.velocity_y()*(-1000), command.velocity_r()*(-1));
//                qDebug()<<"commands"<<command.velocity_x()<<command.velocity_y()<<command.velocity_r();
                commandBuffer[t].robotSpeed[command.robot_id()] = rs;
            }
            if (startRecord) recordCommands(commands);
            //qDebug()<<"isSimulation"<<opm->isSimulation;
            if(opm->isSimulation) {
                //qDebug()<<"sendSim";
                if (grsimInterfaceIndex==0 && opm->useSimInside)
                    Owl::ZSimModule::Instance()->sendSim(t, commands);
                else
                    ZSS::ZRemoteSimModule::Instance()->sendSim(t, commands);
            } else {
                for (int i = 0; i < commands.command_size(); i++) {
                    auto command = commands.command(i);
                    Owl::ActionModule::Instance()->updateCommandParams(command.robot_id(), command.velocity_x()*100, command.velocity_y()*100, 
                        command.velocity_r()*40, command.dribbler_spin()>0, command.dribbler_spin()*3, command.kick(), command.power()>0, command.power()*100);
                }
                Owl::ActionModule::Instance()->sendLegacy(commands.command_size());
            }
            //if(opm->isSimulation) Owl::ZSimModule::Instance()->sendEmptySim();
        }
    }
}

void Communicator::sendCommand(int team, int id) {
    GlobalData::Instance()->robotInfoMutex.lock();
    bool infrared = GlobalData::Instance()->robotInformation[team][id].infrared;
    bool flat = GlobalData::Instance()->robotInformation[team][id].flat;
    bool chip = GlobalData::Instance()->robotInformation[team][id].chip;
    GlobalData::Instance()->robotInfoMutex.unlock();

    ZSS::Protocol::Robot_Status robot_status;
    robot_status.set_robot_id(id);
    //rbk::protocol::Robot_Status robot_status;
    //robot_status.set_robot(id);
    robot_status.set_infrared(infrared);
    robot_status.set_flat_kick(flat);
    robot_status.set_chip_kick(chip);

    int size = robot_status.ByteSize();
    QByteArray datagram(size, 0);
    robot_status.SerializeToArray(datagram.data(), size);
    int port = team == 0? cpm->blue_feedback : cpm->yellow_feedback;
    sendSockets.writeDatagram(datagram.data(), size, QHostAddress(cpm->local_address), port);
}
/**
void Communicator::sendEmptyCmd(int t) {
    while(true){
        std::this_thread::sleep_for(std::chrono::microseconds(5));
        Owl::ZSimModule::Instance()->sendEmptySim();
   }
}
**/
void Communicator::startRecordCommands(bool start) {
    if (start) {
        QDateTime currentTime;
        filename = qApp->applicationDirPath()+"/../LOG/"+currentTime.currentDateTime().toString("yyyy.MM.dd.hh.mm.ss.zzz") + ".txt";
    }
    startRecord = start;
}
//void Communicator::recordCommands(rbk::protocol::SRC_Cmd commands) {
void Communicator::recordCommands(ZSS::Protocol::Robots_Command commands) {
    std::ofstream outfile;
    outfile.open(filename.toLatin1(), std::ios::app);
    for(int i = 0; i < commands.command_size(); i++) {
        auto& command = commands.command(i);
        int id = command.robot_id();
        float vx = command.velocity_x() * 100;
        float vy = command.velocity_y() * 100;
        float vr = command.velocity_r() * 100;
        float flat = command.kick() ? 0 : command.power();
        float chip = command.kick() ? command.power() : 0;
        //float flat = command.flat_kick();
        //float chip = command.chip_kick(); 
        float dribble = command.dribbler_spin();
        outfile<<id<<" "<<vx<<" "<<vy<<" "<<vr<<" "<<dribble<<" "<<1<<" "<<0<<" "<<0<<" "<<0<<"\n";
    }
    outfile.close();
}
