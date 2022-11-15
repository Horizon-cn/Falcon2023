#include "RobotSensor.h"

#include "BestPlayer.h"
#include <WorldModel/WorldModel.h>
#include <fstream>
#include "Global.h"
#include "zss_cmd.pb.h"
#include <thread>
#include <QUdpSocket>
#include <QMutex>
#include "staticparams.h"
#include <QNetworkInterface>

using namespace std;

extern bool IS_SIMULATION;

namespace {
    std::thread* robot_status_thread = nullptr;
    QUdpSocket* robot_status_socket = nullptr;
    QMutex robot_status_mutex;
	//ofstream stopmsgfile("D:\\stopmsg.txt");
	bool debug = true;
}

CRobotSensor::CRobotSensor()
{
    auto pOption = new COptionModule();
    int team = (pOption->MyColor() == TEAM_YELLOW);
    delete pOption;
    robot_status_socket = new QUdpSocket();
    robot_status_socket->bind(QHostAddress::AnyIPv4, ZSS::Athena::CONTROL_BACK_RECEIVE[team], QUdpSocket::ShareAddress);
    robot_status_thread = new std::thread([=] {receiveRobotStatus();});
    robot_status_thread->detach();
	// 数据进行初始化
	memset(_isValid, false, sizeof(_isValid));

    for(int i = 0; i < Param::Field::MAX_PLAYER; i ++) {
        robotInfoBuffer[i].bInfraredInfo = false;
        robotInfoBuffer[i].nKickInfo = 0;
        robotInfoBuffer[i].nRobotNum = 0;
        rawDataBuffer[i] = robotInfoBuffer[i];
	}
}

CRobotSensor::~CRobotSensor()
{
    delete robot_status_socket;
    robot_status_socket = nullptr;
    delete robot_status_thread;
    robot_status_thread = nullptr;
}

void CRobotSensor::receiveRobotStatus()
{
    ZSS::Protocol::Robot_Status robot_status;
    QByteArray datagram;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (robot_status_socket->state() == QUdpSocket::BoundState && robot_status_socket->hasPendingDatagrams()) {
            datagram.resize(robot_status_socket->pendingDatagramSize());
            robot_status_socket->readDatagram(datagram.data(), datagram.size());
            robot_status.ParseFromArray(datagram, datagram.size());
            if (!robot_status.has_robot_id()) {
                qDebug()<<"no robot status";
                continue;
            }
            auto&& id = robot_status.robot_id();
            if(id < 0 || id >= Param::Field::MAX_PLAYER) {
                qDebug() << "ERROR received error robot id in command interface." << id;
                continue;
            }
            robot_status_mutex.lock();
            rawDataBuffer[id].bInfraredInfo = robot_status.infrared();
            rawDataBuffer[id].nRobotNum = id;
            rawDataBuffer[id].nKickInfo = robot_status.chip_kick() || robot_status.flat_kick();
            qDebug()<<"receive"<<rawDataBuffer[id].nRobotNum<<"infrared"<<rawDataBuffer[id].bInfraredInfo<<"kick"<<rawDataBuffer[id].nKickInfo;
            robot_status_mutex.unlock();
        }
    }
}

void CRobotSensor::Update(int cycle)
{
    static int last_cycle = 0;
    if (cycle == last_cycle)
        return;
    last_cycle = cycle;
    robot_status_mutex.lock();
    for (int i = 0; i < Param::Field::MAX_PLAYER; i ++) {
        robotInfoBuffer[i] = rawDataBuffer[i];
        if (robotInfoBuffer[i].nRobotNum == i)
            _isValid[i] = true;
        else
            _isValid[i] = false;
    }
    robot_status_mutex.unlock();
}

bool CRobotSensor::IsInfraredOn(int num)				
{ 
    return robotInfoBuffer[num].bInfraredInfo;
}

