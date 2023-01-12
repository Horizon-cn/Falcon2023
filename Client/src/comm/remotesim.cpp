#include <thread>
#include "remotesim.h"
#include "globaldata.h"
#include "communicator.h"
#include "staticparams.h"
#include "grSim_Packet.pb.h"
#include "grSim_Commands.pb.h"
#include "networkinterfaces.h"
#include "parammanager.h"

namespace ZSS {

grSim_Packet grsim_packet_yellow;
grSim_Commands *grsim_commands_yellow;
grSim_Robot_Command *grsim_robots_yellow[PARAM::ROBOTMAXID];

grSim_Packet grsim_packet_blue;
grSim_Commands *grsim_commands_blue;
grSim_Robot_Command *grsim_robots_blue[PARAM::ROBOTMAXID];

std::thread* blueReceiveThread = nullptr;
std::thread* yellowReceiveThread = nullptr;

auto opm = Owl::OParamManager::Instance();
auto cpm = Owl::CParamManager::Instance();
auto vpm = Owl::VParamManager::Instance();

bool trans_dribble(double dribble) {
    return dribble>1;
}

double trans_length(double v) {
    return v / 1000.0;
}

double trans_vr(double v) {
    return v;/// 40.0; from angel to 1/40 rad
}

RemoteSim::RemoteSim(QObject *parent) : QObject(parent)
{
    grsim_commands_yellow = grsim_packet_yellow.mutable_commands();
    grsim_commands_blue = grsim_packet_blue.mutable_commands();
    for (int i = 0; i < PARAM::ROBOTMAXID; i++) {
        grsim_robots_yellow[i] = grsim_commands_yellow->add_robot_commands();
        grsim_robots_blue[i] = grsim_commands_blue->add_robot_commands();
    }
    for (int i = 0; i < PARAM::ROBOTMAXID; i++) {
        grsim_robots_yellow[i]->set_id(i);
        grsim_robots_yellow[i]->set_kickspeedx(0);
        grsim_robots_yellow[i]->set_kickspeedz(0);
        grsim_robots_yellow[i]->set_velnormal(0);
        grsim_robots_yellow[i]->set_veltangent(0);
        grsim_robots_yellow[i]->set_velangular(0);
        grsim_robots_yellow[i]->set_spinner(false);
        grsim_robots_yellow[i]->set_wheelsspeed(false);
    }
    for (int i = 0; i < PARAM::ROBOTMAXID; i++) {
        grsim_robots_blue[i]->set_id(i);
        grsim_robots_blue[i]->set_kickspeedx(0);
        grsim_robots_blue[i]->set_kickspeedz(0);
        grsim_robots_blue[i]->set_velnormal(0);
        grsim_robots_blue[i]->set_veltangent(0);
        grsim_robots_blue[i]->set_velangular(0);
        grsim_robots_blue[i]->set_spinner(false);
        grsim_robots_blue[i]->set_wheelsspeed(false);
    }
    for(int i = 0; i < PARAM::TEAMS; i++) {
        if(connectSim(i)){
            switch (i) {
            case 0:
                blueReceiveThread = new std::thread([=] {readBlueData();});
                blueReceiveThread->detach();
                break;
            case 1:
                yellowReceiveThread = new std::thread([=] {readYellowData();});
                yellowReceiveThread->detach();
                break;
            }
        }
    }
}

bool RemoteSim::disconnectSim(bool color) {
    if(color) {
        yellowReceiveSocket.disconnectFromHost();
    } else {
        blueReceiveSocket.disconnectFromHost();
    }
    return true;
}

RemoteSim::~RemoteSim() {
    yellowReceiveSocket.abort();
    blueReceiveSocket.abort();
}

bool RemoteSim::connectSim(bool color) {
    if(color) {
        if(yellowReceiveSocket.bind(QHostAddress::AnyIPv4, cpm->yellow_status, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
            qDebug() << "Yellow connect successfully!!! --remotesim";
            return true;
        }
        return false;
    }
    if(blueReceiveSocket.bind(QHostAddress::AnyIPv4, cpm->blue_status, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qDebug() << "Blue connect successfully!!! --remotesim";
        return true;
    }
    return false;
}

void RemoteSim::readBlueData() {
    qDebug() << "Reading Blue Data!";
    QByteArray datagram;
    //int i =0;
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
        while(blueReceiveSocket.state() == QUdpSocket::BoundState && blueReceiveSocket.hasPendingDatagrams()) {
            ZSS::Protocol::Robots_Status robotsPacket;
            datagram.resize(blueReceiveSocket.pendingDatagramSize());
            blueReceiveSocket.readDatagram(datagram.data(), datagram.size());
            robotsPacket.ParseFromArray(datagram, datagram.size());
            //qDebug()<<"size"<<robotsPacket.robots_status_size()<<i;
            //i++;
            for (int i = 0; i < robotsPacket.robots_status_size(); ++i) {
                int id = robotsPacket.robots_status(i).robot_id();
                bool infrared = robotsPacket.robots_status(i).infrared();
                bool isFlatKick = robotsPacket.robots_status(i).flat_kick();
                bool isChipKick = robotsPacket.robots_status(i).chip_kick();
                GlobalData::Instance()->robotInfoMutex.lock();
                GlobalData::Instance()->robotInformation[PARAM::BLUE][id].infrared = infrared;
                //qDebug()<<"infrared"<<infrared;
                GlobalData::Instance()->robotInformation[PARAM::BLUE][id].flat = isFlatKick;
                GlobalData::Instance()->robotInformation[PARAM::BLUE][id].chip = isChipKick;
                GlobalData::Instance()->robotInfoMutex.unlock();
                //ZCommunicator::instance()->sendCommand(PARAM::BLUE, id);
                emit receiveRemoteInfo(PARAM::BLUE, id);
            }
        }
    }
}

void RemoteSim::readYellowData() {
    qDebug() << "Reading Yellow Data!";
    QByteArray datagram;
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
        while(yellowReceiveSocket.state() == QUdpSocket::BoundState && yellowReceiveSocket.hasPendingDatagrams()) {
            ZSS::Protocol::Robots_Status robotsPacket;
            datagram.resize(yellowReceiveSocket.pendingDatagramSize());
            yellowReceiveSocket.readDatagram(datagram.data(), datagram.size());
            robotsPacket.ParseFromArray(datagram, datagram.size());
            qDebug()<<"receive";
            for (int i = 0; i < robotsPacket.robots_status_size(); ++i) {
                int id = robotsPacket.robots_status(i).robot_id();
                bool infrared = robotsPacket.robots_status(i).infrared();
                bool isFlatKick = robotsPacket.robots_status(i).flat_kick();
                bool isChipKick = robotsPacket.robots_status(i).chip_kick();
                GlobalData::Instance()->robotInfoMutex.lock();
                GlobalData::Instance()->robotInformation[PARAM::YELLOW][id].infrared = infrared;
                GlobalData::Instance()->robotInformation[PARAM::YELLOW][id].flat = isFlatKick;
                GlobalData::Instance()->robotInformation[PARAM::YELLOW][id].chip = isChipKick;
                GlobalData::Instance()->robotInfoMutex.unlock();
                //ZCommunicator::instance()->sendCommand(PARAM::YELLOW, id);
                emit receiveRemoteInfo(PARAM::YELLOW, id);
            }
        }
    }
}

void RemoteSim::sendSim(int t, ZSS::Protocol::Robots_Command& command) {
    if(t != 0 && t != 1) {
        qDebug() << "Team ERROR in Simmodule !";
        return;
    }
    grSim_Packet& grsim_packet = (t == 0 ? grsim_packet_blue : grsim_packet_yellow);
    grSim_Commands * grsim_commands = (t == 0 ? grsim_commands_blue : grsim_commands_yellow);
    grSim_Robot_Command **grsim_robots = (t == 0 ? grsim_robots_blue : grsim_robots_yellow);
    grsim_commands->set_isteamyellow(t == 0 ? false : true);
    grsim_commands->set_timestamp(0);
    int command_size = command.command_size();
    for (int i = 0; i < command_size; i++) {
        auto commands = command.command(i);
        auto id = commands.robot_id();
        grsim_robots[id]->set_id(id);
        grsim_robots[id]->set_wheelsspeed(false);
        //set flatkick or chipkick
        if (!commands.kick()) {
            grsim_robots[id]->set_kickspeedz(0);
            grsim_robots[id]->set_kickspeedx(commands.power() >= 6.5? 6.5 : commands.power());
        } else {
            double radian = vpm->chipAngle * vpm->PI / 180.0;
            double vx = sqrt(commands.power() * vpm->G / 2.0 / tan(radian));
            vx = vx >= (6.5 * cos(radian))? (6.5 * cos(radian)) : vx;
            double vz = vx * tan(radian);
            grsim_robots[id]->set_kickspeedz(vx);
            grsim_robots[id]->set_kickspeedx(vz);
        }
        //set velocity and dribble
        double vx = commands.velocity_x();
        double vy = -commands.velocity_y();
        double vr = -commands.velocity_r();
        /**
        double dt = 1. / opm->FRAME_RATE;
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
        **/
        grsim_robots[id]->set_veltangent(vx);
        grsim_robots[id]->set_velnormal(vy);
        grsim_robots[id]->set_velangular(vr);
        grsim_robots[id]->set_spinner(commands.dribbler_spin() > 0);
    }
    int size = grsim_packet.ByteSize();
    QByteArray data(size, 0);
    grsim_packet.SerializeToArray(data.data(), data.size());
    int index = ZCommunicator::Instance()->getGrsimInterfaceIndex();
    RemoteAddress = NetworkInterfaces::Instance()->getGrsimInterfaces()[index];
    command_socket.writeDatagram(data, size, QHostAddress(RemoteAddress), cpm->sim_send);
//    qDebug() << RemoteAddress << cpm->sim_send;
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

}
