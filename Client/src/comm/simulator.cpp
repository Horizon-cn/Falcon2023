#include "simulator.h"
#include "parammanager.h"
#include "globaldata.h"
#include <QtDebug>
#include <QtMath>
#include "staticparams.h"
namespace{
auto opm = Owl::OParamManager::Instance();
auto cpm = Owl::CParamManager::Instance();
//double xIn[PARAM::ROBOTMAXID*2] = { 0.3,  0.6,  0.9,  1.2, 1.5, 1.8, 2.1, 2.4, 2.7, 3.0, 3.3, 3.6, 3.9, 4.2, 4.5, 4.8};
//double yOut[PARAM::ROBOTMAXID*2] = { -5.4, -5.4, -5.4, -5.4, -5.4, -5.4, -5.4, -5.4, -5.4, -5.4, -5.4, -5.4 };
//double xOut[PARAM::ROBOTMAXID*2] = { 0.4,  0.8,  1.2,  1.6,  2.0,  2.4, 2.8, 3.2, 3.6, 4.0, 4.4, 4.8 };
//double yIn[PARAM::ROBOTMAXID*2] = { -4.0, -4.0, -4.0, -4.0, -4.0, -4.0, -4.0, -4.0, -4.0, -4.0, -4.0, -4.0 };
}
CSimulator::CSimulator(QObject *parent) : QObject(parent)
{
    if (opm->useSimInside) {

    }
    else {
        sendSocket.setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
    }
}
CSimulator::~CSimulator(){
    sendSocket.abort();
}
void CSimulator::setBall(double x,double y,double vx,double vy){
    grSim_Packet packet;
    auto* replacement = packet.mutable_replacement();
    auto* ball = replacement->mutable_ball();
    ball->set_x(x);
    ball->set_y(y);
    ball->set_vx(vx);
    ball->set_vy(vy);
    send(&packet);
}
void CSimulator::setRobot(double x,double y,int id,bool team,double dir,bool turnon){
    grSim_Packet packet;
    auto* replacement = packet.mutable_replacement();
    auto* robot = replacement->add_robots();
    robot->set_x(x);
    robot->set_y(y);
    robot->set_id(id);
    robot->set_dir(dir);
    robot->set_yellowteam(team);
    robot->set_turnon(turnon);
    send(&packet);
}
void CSimulator::controlRobot(int num,bool team){
    grSim_Packet packet;
    double dir = (team ? 180 : 0);
    double ratio = (team ? 1 : -1);
    auto* replacement = packet.mutable_replacement();
    for(int i=0;i<num;i++){
        auto* robot = replacement->add_robots();
        robot->set_x(ratio*(i+1)*0.3);
        robot->set_y(0);//(yIn[i]);
        robot->set_id(i);
        robot->set_dir(dir);
        robot->set_yellowteam(team);
        robot->set_turnon(true);
    }
    for(int i=num;i<PARAM::ROBOTMAXID;i++){
        auto* robot = replacement->add_robots();
        robot->set_x(ratio*i*0.3);
        robot->set_y(-5.5);
        robot->set_id(i);
        robot->set_dir(dir);
        robot->set_yellowteam(team);
        robot->set_turnon(false);
    }
    send(&packet);
}
void CSimulator::controlSingleRobot(int num,bool team){
    grSim_Packet packet;
    double dir = (team ? 180 : 0);
    double ratio = (team ? 1 : -1);
    auto* replacement = packet.mutable_replacement();
    auto& vision = GlobalData::Instance()->processRobot[0];
    auto* robot = replacement->add_robots();
    if (vision.robotIndex[team][num] == -1) {
        robot->set_x(ratio*(num+1)*0.3);
        robot->set_y(0);//(yIn[i]);
        robot->set_id(num);
        robot->set_dir(dir);
        robot->set_yellowteam(team);
        robot->set_turnon(true);
    }
    else {
        robot->set_x(ratio*num*0.3);
        robot->set_y(-5.5);
        robot->set_id(num);
        robot->set_dir(dir);
        robot->set_yellowteam(team);
        robot->set_turnon(false);
    }
    send(&packet);
}
void CSimulator::send(grSim_Packet* packet){
    if (opm->useSimInside) {

    }
    else {
        packet->set_login_name(opm->LoginName);
        int size = packet->ByteSize();
        QByteArray buffer(size,0);
        packet->SerializeToArray(buffer.data(), size);
        sendSocket.writeDatagram(buffer,size, QHostAddress(cpm->sim_address), cpm->sim_send);
    }
}
