#include "simmodule.h"
#include "parammanager.h"
#include "globaldata.h"
#include "zss_cmd.pb.h"
#include "src_cmd.pb.h"
#include "messages_robocup_ssl_robot_status.pb.h"
#include "grSim_Packet.pb.h"
#include <chrono>
#include <thread>
#include <cmath>
#include <geometry.h>
#include <qdebug.h>
#include "test.h"
#include "staticparams.h"
#include "communicator.h"
namespace Owl {
namespace {
bool trans_dribble(double dribble) {
    return dribble>1;
}
double trans_length(double v) {
    return v / 1000.0;
}
double trans_vr(double v) {
    return v;/// 40.0; from angel to 1/40 rad
}
std::thread* blueReceiveThread = nullptr;
std::thread* yellowReceiveThread = nullptr;

grSim_Packet grsim_packet;
//grSim_Packet empty_grsim_packet;
grSim_Commands *grsim_commands;
grSim_Robot_Command *grsim_robots[PARAM::ROBOTMAXID];

auto opm = Owl::OParamManager::Instance();
auto cpm = Owl::CParamManager::Instance();
auto vpm = Owl::VParamManager::Instance();
auto sipm = Owl::SIParamManager::Instance();
auto skpm = Owl::SKParamManager::Instance();
}
SimModule::SimModule(QObject *parent) : QObject(parent) {
    grsim_commands = grsim_packet.mutable_commands();
    for (int i = 0; i < PARAM::ROBOTMAXID; i++) {
        grsim_robots[i] = grsim_commands->add_robot_commands();
    }
    for (int i = 0; i < PARAM::ROBOTMAXID; i++) {
        grsim_robots[i]->set_id(i);
        grsim_robots[i]->set_kickspeedx(0);
        grsim_robots[i]->set_kickspeedz(0);
        grsim_robots[i]->set_velnormal(0);
        grsim_robots[i]->set_veltangent(0);
        grsim_robots[i]->set_velangular(0);
        grsim_robots[i]->set_spinner(false);
        grsim_robots[i]->set_wheelsspeed(false);
    }
    //for(int i = 0; i < PARAM::TEAMS; i++) {
    //    if(connectSim(i)){
    //        switch (i) {
    //        case PARAM::BLUE:
    //            blueReceiveThread = new std::thread([=] {readBlueData();});
    //            blueReceiveThread->detach();
    //            break;
    //        case PARAM::YELLOW:
    //            yellowReceiveThread = new std::thread([=] {readYellowData();});
    //            yellowReceiveThread->detach();
    //            break;
    //        }
    //    }
    //}
}

SimModule::~SimModule() {
    yellowReceiveSocket.abort();
    blueReceiveSocket.abort();
    delete blueReceiveThread;
    blueReceiveThread = nullptr;
    delete yellowReceiveThread;
    yellowReceiveThread = nullptr;
}

bool SimModule::connectSim(bool color) {
    if(color) {
        if(yellowReceiveSocket.bind(QHostAddress::AnyIPv4, cpm->yellow_status, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
            qDebug() << "Yellow connect successfully!!! --simmodule";
            if (yellowReceiveThread == nullptr) {
                yellowReceiveThread = new std::thread([=] {readYellowData(); });
                yellowReceiveThread->detach();
            }
            return true;
        }
        return false;
    }
    if(blueReceiveSocket.bind(QHostAddress::AnyIPv4, cpm->blue_status, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qDebug() << "Blue connect successfully!!! --simmodule";
        if (blueReceiveThread == nullptr) {
            blueReceiveThread = new std::thread([=] {readBlueData(); });
            blueReceiveThread->detach();
        }
        return true;
    }
    return false;
}

bool SimModule::disconnectSim(bool color) {
    if(color) {
        yellowReceiveSocket.disconnectFromHost();
    } else {
        blueReceiveSocket.disconnectFromHost();
    }
    return true;
}

void SimModule::readBlueData() {
    qDebug() << "Reading Blue Data!";
    QByteArray datagram;
    while(true){
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        while(blueReceiveSocket.state() == QUdpSocket::BoundState && blueReceiveSocket.hasPendingDatagrams()) {
            ZSS::Protocol::Robots_Status robotsPacket;
            //Robots_Status robotsPacket;
            datagram.resize(blueReceiveSocket.pendingDatagramSize());
            blueReceiveSocket.readDatagram(datagram.data(), datagram.size());
            robotsPacket.ParseFromArray(datagram, datagram.size());
            for (int i = 0; i < robotsPacket.robots_status_size(); ++i) {
                if (robotsPacket.robots_status(i).has_login_name() && robotsPacket.robots_status(i).login_name() != opm->LoginName)
                    break;
                int id = robotsPacket.robots_status(i).robot_id();
                bool infrared = robotsPacket.robots_status(i).infrared();
                bool isFlatKick = robotsPacket.robots_status(i).flat_kick();
                bool isChipKick = robotsPacket.robots_status(i).chip_kick();
                GlobalData::Instance()->robotInfoMutex.lock();
                GlobalData::Instance()->robotInformation[PARAM::BLUE][id].infrared = infrared;
                GlobalData::Instance()->robotInformation[PARAM::BLUE][id].flat = isFlatKick;
                GlobalData::Instance()->robotInformation[PARAM::BLUE][id].chip = isChipKick;
                GlobalData::Instance()->robotInfoMutex.unlock();
                qDebug() << "Blue id: " << id << "  infrared: " << infrared << "  flat: " << isFlatKick << "  chip: " << isChipKick;
                ZCommunicator::Instance()->sendCommand(PARAM::BLUE, id);
                //emit receiveSimInfo(PARAM::BLUE, id);
            }
        }
    }
}

void SimModule::readYellowData() {
     qDebug() << "Reading Yellow Data!";
    QByteArray datagram;
    while(true){
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        while(yellowReceiveSocket.state() == QUdpSocket::BoundState && yellowReceiveSocket.hasPendingDatagrams()) {
            ZSS::Protocol::Robots_Status robotsPacket;       
            //Robots_Status robotsPacket;
            datagram.resize(yellowReceiveSocket.pendingDatagramSize());
            yellowReceiveSocket.readDatagram(datagram.data(), datagram.size());
            robotsPacket.ParseFromArray(datagram, datagram.size());
            for (int i = 0; i < robotsPacket.robots_status_size(); ++i) {
                if (robotsPacket.robots_status(i).has_login_name() && robotsPacket.robots_status(i).login_name() != opm->LoginName)
                    break;
                int id = robotsPacket.robots_status(i).robot_id();
                bool infrared = robotsPacket.robots_status(i).infrared();
                bool isFlatKick = robotsPacket.robots_status(i).flat_kick();
                bool isChipKick = robotsPacket.robots_status(i).chip_kick();
                GlobalData::Instance()->robotInfoMutex.lock();
                GlobalData::Instance()->robotInformation[PARAM::YELLOW][id].infrared = infrared;
                GlobalData::Instance()->robotInformation[PARAM::YELLOW][id].flat = isFlatKick;
                GlobalData::Instance()->robotInformation[PARAM::YELLOW][id].chip = isChipKick;
                GlobalData::Instance()->robotInfoMutex.unlock();
    //            qDebug() << "Yellow id: " << id << "  infrared: " << infrared << "  flat: " << isFlatKick << "  chip: " << isChipKick;
                ZCommunicator::Instance()->sendCommand(PARAM::YELLOW, id);
                //emit receiveSimInfo(PARAM::YELLOW, id);
            }           
        }
    }
}

void SimModule::sendSim(int t, ZSS::Protocol::Robots_Command& command) {
//void SimModule::sendSim(int t, rbk::protocol::SRC_Cmd& command) {
    // 线上赛仿真器如果用grSim，下一行要注掉
    grsim_packet.set_login_name(opm->LoginName);
    grsim_commands->set_timestamp(0);
    if (t == 0) {
        grsim_commands->set_isteamyellow(false);
    } else if (t == 1) {
        grsim_commands->set_isteamyellow(true);
    } else {
        qDebug() << "Team ERROR in Simmodule !";
    }
    int command_size = command.command_size();
    for (int i = 0; i < command_size; i++) {
        auto commands = command.command(i);
        auto id = commands.robot_id();
        grsim_robots[id]->set_id(id);
        grsim_robots[id]->set_wheelsspeed(false);
        //set flatkick or chipkick
        if (!commands.kick()) {
        //if (commands.flat_kick()!=0) {
            grsim_robots[id]->set_kickspeedz(0);
            //grsim_robots[id]->set_kickspeedx(trans_length(commands.power()));
            grsim_robots[id]->set_kickspeedx(commands.power() >= skpm->MAX_BALL_SPEED? skpm->MAX_BALL_SPEED : commands.power());
            //grsim_robots[id]->set_kickspeedx(commands.flat_kick());
        } else {
        //else if (commands.chip_kick()!=0){
            double radian = vpm->chipAngle * cpm->PI / 180.0;
            double vx = sqrt(commands.power() * sipm->Gravity / 2.0 / tan(radian));
            vx = vx >= (skpm->MAX_BALL_SPEED * cos(radian))? (skpm->MAX_BALL_SPEED * cos(radian)) : vx;
            //double vx = sqrt(trans_length(commands.power()) * spm->Gravity / 2.0 / tan(radian));
            //double vx = sqrt(commands.chip_kick() * spm->Gravity / 2.0 / tan(radian));
            double vz = vx * tan(radian);
            grsim_robots[id]->set_kickspeedz(vx);
            grsim_robots[id]->set_kickspeedx(vz);
        }
        //set velocity and dribble
        double vx = commands.velocity_x();
        double vy = -commands.velocity_y();
        double vr = -commands.velocity_r();
        double dt = 1. / sipm->DesiredFPS;
        double theta = - vr * dt;
        CVector v(vx, vy);
        v = v.rotate(theta);
        if (fabs(theta) > 0.00001) {
            //            if (i==0) cout << theta << " " <<vx << " "<< vy << " ";
            v = v * theta / (2 * sin(theta / 2));
            vx = v.x();
            vy = v.y();
            //            if (i==0) cout << vx << " "<< vy << " " << endl;
        }
        grsim_robots[id]->set_veltangent(vx);
        grsim_robots[id]->set_velnormal(vy);
        grsim_robots[id]->set_velangular(vr);
        grsim_robots[id]->set_spinner(commands.dribbler_spin() > 0);
        //grsim_robots[id]->set_veltangent(trans_length(vx));
        //grsim_robots[id]->set_velnormal(-trans_length(vy));
        //grsim_robots[id]->set_velangular(-trans_vr(vr));
        //grsim_robots[id]->set_spinner(trans_dribble(commands.dribbler_spin()));
    }
    //grsim_packet.set_noise(Test::Instance()->noise);
    //grsim_packet.set_vanish(Test::Instance()->vanish);

    int size = grsim_packet.ByteSize();
    QByteArray data(size, 0);
    grsim_packet.SerializeToArray(data.data(), data.size());
    command_socket.writeDatagram(data, size, QHostAddress(cpm->sim_address), cpm->sim_send);
    for (int i = 0; i < PARAM::ROBOTMAXID; i++) {
        grsim_robots[i]->set_id(i);
        grsim_robots[i]->set_kickspeedx(0);
        grsim_robots[i]->set_kickspeedz(0);
        grsim_robots[i]->set_velnormal(0);
        grsim_robots[i]->set_veltangent(0);
        grsim_robots[i]->set_velangular(0);
        grsim_robots[i]->set_spinner(false);
        grsim_robots[i]->set_wheelsspeed(false);
    }
}
/**
void SimModule::sendEmptySim() {
    grsim_packet.set_noise(Test::Instance()->noise);
    grsim_packet.set_vanish(Test::Instance()->vanish);
    int size = grsim_packet.ByteSize();
    QByteArray data(size, 0);
    grsim_packet.SerializeToArray(data.data(), data.size());
    command_socket.writeDatagram(data, size, QHostAddress(cpm->local_address), cpm->sim_send);
}
**/
}

