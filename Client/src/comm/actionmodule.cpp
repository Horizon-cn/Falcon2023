#include "actionmodule.h"
#include "parammanager.h"
#include "globaldata.h"
#include "dealrobot.h"
#include <QtDebug>
#include <chrono>
#include <thread>
#include <cmath>
#include "staticparams.h"
namespace Owl {
namespace {
const int TRANSMIT_PACKET_SIZE = 25;
const int TRANS_FEEDBACK_SIZE = 26;
const int TRANSMIT_START_PACKET_SIZE = 6;
const int PORT_SEND = 1003;
const int PORT_RECEIVE = 10030; //TMP
const double FULL_BATTERY = 224.0;
const double LOW_BATTERY = 196.0;
const double FULL_CAPACITANCE = 254.0;
const double LOW_CAPACITANCE = 29.0;
auto opm = Owl::OParamManager::Instance();
auto vpm = Owl::VParamManager::Instance();
//void encodeLegacy(const Owl::Protocol::Robot_Command&, QByteArray&, int);
void encodeLegacy(const rbk::protocol::Message_SSL_Command&, QByteArray&, int);
quint8 kickStandardization(quint8, bool, quint16);
const QString radioSendAddress[PARAM::TEAMS] = {"10.12.225.142", "10.12.225.109"};
const QString radioReceiveAddress[PARAM::TEAMS] = {"10.12.225.142", "127.0.0.1"};   // infrared 目前用的都是 radioReceiveAddress[1]
std::thread* receiveThread = nullptr;
}

ActionModule::ActionModule(QObject *parent) : QObject(parent), team{-1, -1} {
    tx.resize(TRANSMIT_PACKET_SIZE);
    tx[0] = 0x40;
    while(!receiveSocket.bind(QHostAddress::AnyIPv4, PORT_RECEIVE, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)){
        receiveThread = new std::thread([ = ] {readData();});
        receiveThread->detach();
        qDebug() << "****** start receive actionModule ! ******";
    }
    QObject::connect(&receiveSocket, SIGNAL(readyRead()), this, SLOT(readData()), Qt::DirectConnection);
}

ActionModule::~ActionModule() {
    disconnect(&receiveSocket);
    sendSocket.disconnectFromHost();
    receiveSocket.disconnectFromHost();
}

bool ActionModule::connectRadio(int id, int frq) {
    if(id >= 0 && id < PARAM::TEAMS) {
        team[id] = opm->isYellow ? PARAM::YELLOW : PARAM::BLUE;
        qDebug() << "connectRadio : " << id << (team[id] ? "YELLOW" : "BLUE") << frq;
        //sendStartPacket(id, frq);
        return true;
    } else
        qDebug() << "ERROR id in connectRadio function!";
    return false;
}

bool ActionModule::disconnectRadio(int id) {
    if(id >= 0 && id < PARAM::TEAMS) {
        team[id] = -1;
        sendSocket.disconnectFromHost();
        return true;
    } else
        qDebug() << "ERROR id in disconnectRadio function!";
    return false;
}

void ActionModule::sendStartPacket(int t, int frequency) {
    // this 't' is id
    QByteArray startPacketSend(TRANSMIT_START_PACKET_SIZE, 0);
    QByteArray startPacketReceive(TRANSMIT_START_PACKET_SIZE, 0);
    if(frequency == 8) {
        startPacketSend[0] = (char)0xf0;
        startPacketSend[1] = (char)0x5a;
        startPacketSend[2] = (char)0x5a;
        startPacketSend[3] = (char)0x01;
        startPacketSend[4] = (char)0x02;
        startPacketSend[5] = (char)0xa7;

        startPacketReceive[0] = (char)0xf0;
        startPacketReceive[1] = (char)0x5a;
        startPacketReceive[2] = (char)0x5a;
        startPacketReceive[3] = (char)0x02;
        startPacketReceive[4] = (char)0x02;
        startPacketReceive[5] = (char)0xa8;
    } else if(frequency == 6) {
        startPacketSend[0] = (char)0xf0;
        startPacketSend[1] = (char)0x18;
        startPacketSend[2] = (char)0x5a;
        startPacketSend[3] = (char)0x01;
        startPacketSend[4] = (char)0x02;
        startPacketSend[5] = (char)0x65;

        startPacketReceive[0] = (char)0xf0;
        startPacketReceive[1] = (char)0x18;
        startPacketReceive[2] = (char)0x18;
        startPacketReceive[3] = (char)0x02;
        startPacketReceive[4] = (char)0x02;
        startPacketReceive[5] = (char)0x24;
    } else {
        qDebug() << "Frequency ERROR !!!";
    }
    sendSocket.writeDatagram(startPacketSend, TRANSMIT_START_PACKET_SIZE, QHostAddress(radioSendAddress[t]), PORT_SEND);
    receiveSocket.writeDatagram(startPacketReceive, TRANSMIT_START_PACKET_SIZE, QHostAddress(radioReceiveAddress[t]), PORT_SEND);
    std::this_thread::sleep_for(std::chrono::milliseconds(4));
    qDebug() << "Frequency:" << frequency << " Send IP:" << radioSendAddress[t] << " Receive IP:" << radioReceiveAddress[t];
}

//void ActionModule::sendLegacy(int t, const Owl::Protocol::Robots_Command& commands) {
void ActionModule::sendLegacy(int t, const rbk::protocol::SRC_Cmd& commands) {
    // this 't' is color
    auto& socket = sendSocket;
    int id = -1;
    if(t == team[0])
        id = 0;
    else if(t == team[1])
        id = 1;
    else
        return;
    int size = commands.command_size();
    int count = 0;
    tx.fill(0x00);
    tx[0] = 0x40;
    for(int i = 0; i < size; i++) {
        if(count == 4) {
            socket.writeDatagram(tx.data(), TRANSMIT_PACKET_SIZE, QHostAddress(radioSendAddress[id]), PORT_SEND);
            std::this_thread::sleep_for(std::chrono::microseconds(3000));
            tx.fill(0x00);
            tx[0] = 0x40;
            count = 0;
        }
        auto& command = commands.command(i);
        encodeLegacy(command, this->tx, count++);
    }
    //qDebug() << "sendLegacy : " << (t ? "Yellow" : "Blue") << id << "size:" << size;
    socket.writeDatagram(tx.data(), TRANSMIT_PACKET_SIZE, QHostAddress(radioSendAddress[id]), PORT_SEND);
}

void ActionModule::readData() {
    static QHostAddress address;
    static int color;
    static int count[PARAM::TEAMS][PARAM::ROBOTMAXID];
    for (int color = PARAM::BLUE; color < PARAM::TEAMS; color++) {
        for (int j = 0; j < PARAM::ROBOTMAXID; j++ ) {
            count[color][j] = 0;
        }
    }
    while(true) {
        std::this_thread::sleep_for(std::chrono::microseconds(5));
        /**if(!opm->isSimulation) {
            for (int color = PARAM::BLUE; color < PARAM::TEAMS; color++) {
                for (int j = 0; j < PARAM::ROBOTMAXID; j++ ) {
                    if (count[color][j]++ > 1000) {
                        robotInfoMutex.lock();
                        GlobalData::Instance()->robotInformation[color][j].infrared = false;
                        GlobalData::Instance()->robotInformation[color][j].flat = false;
                        GlobalData::Instance()->robotInformation[color][j].chip = false;
                        count[color][j] = 0;
//                        qDebug() << "FUCK" << color << j;
                        robotInfoMutex.unlock();
//                        emit receiveRobotInfo(color, j);
                    }
                }
            }
        }*/
        while (receiveSocket.state() == QUdpSocket::BoundState && receiveSocket.hasPendingDatagrams()) {
            rx.resize(receiveSocket.pendingDatagramSize());
            receiveSocket.readDatagram(rx.data(), rx.size());
            rbk::protocol::Robots_Status status;
            status.ParseFromArray(rx, rx.size());
            for(int i = 0; i < status.robots_status_size(); i++) {
                auto& singleStatus = status.robots_status(i);
                int id = singleStatus.robot();
                bool infrared = singleStatus.infrared();
                bool flat = singleStatus.flat_kick();
                bool chip = singleStatus.chip_kick();
                bool ctrl = singleStatus.controlled();
                color = singleStatus.team();
                count[color][id] = 0;
                uint32_t changed_num = singleStatus.change_num();
                uint32_t changed_cnt = singleStatus.change_cnt();
                //robotInfoMutex.lock();
                GlobalData::Instance()->robotInformation[color][id].infrared = infrared;
                GlobalData::Instance()->robotInformation[color][id].flat = flat;
                GlobalData::Instance()->robotInformation[color][id].chip = chip;
                GlobalData::Instance()->robotInformation[color][id].battery = 100;
                GlobalData::Instance()->robotInformation[color][id].capacitance = 1;
                //robotInfoMutex.unlock();
                if(infrared) qDebug()<<color<<id<<"has infrared";
                emit receiveRobotInfo(color, id);
                //GlobalData::Instance()->robotInformation[color][id].battery = std::min(std::max((battery - LOW_BATTERY) / (FULL_BATTERY - LOW_BATTERY), 0.0), 1.0);
                //GlobalData::Instance()->robotInformation[color][id].capacitance = std::min(std::max((capacitance - LOW_CAPACITANCE) / (FULL_CAPACITANCE - LOW_CAPACITANCE), 0.0), 1.0);
            }
            return;
            /*
            receiveSocket.readDatagram(rx.data(), rx.size(), &address);
            color = (address.toString() == radioReceiveAddress[0]) ? team[0] : team[1];
            if (color == -1) {
                qDebug() << "Receive Error Message from:" << address << "in actionmodule.cpp";
                break;
            }
            auto& data = rx;
            int id = 0;
            bool infrared = false;
            bool flat = false;
            bool chip = false;
            int battery = 0;
            int capacitance = 0;
            short wheelVel[4] = {0};

            if(data[0] == (char)0xff && data[1] == (char)0x02) {
                id       = (quint8)data[2] - 1;//real robot 1-12 -> 0-11
                infrared = (quint8)data[3] & 0x40;
                flat     = (quint8)data[3] & 0x20;
                chip     = (quint8)data[3] & 0x10;
                battery  = (quint8)data[4];
                capacitance = (quint8)data[5];
                wheelVel[0] = (quint16)(data[6] << 8) + data[7];
                wheelVel[1] = 1 + (short)~(data[8] << 8) + data[9];
                wheelVel[2] = 1 + (short)~(data[10] << 8) + data[11];
                wheelVel[3] = (quint16)(data[12] << 8) + data[13];
                qDebug()<<id<<infrared;

                robotInfoMutex.lock();
                count[color][id] = 0;
                GlobalData::Instance()->robotInformation[color][id].infrared = infrared;
                GlobalData::Instance()->robotInformation[color][id].flat = flat;
                GlobalData::Instance()->robotInformation[color][id].chip = chip;
                GlobalData::Instance()->robotInformation[color][id].battery = std::min(std::max((battery - LOW_BATTERY) / (FULL_BATTERY - LOW_BATTERY), 0.0), 1.0);
                GlobalData::Instance()->robotInformation[color][id].capacitance = std::min(std::max((capacitance - LOW_CAPACITANCE) / (FULL_CAPACITANCE - LOW_CAPACITANCE), 0.0), 1.0);
                robotInfoMutex.unlock();
                //emit receiveRobotInfo(color, id);
            }
            qDebug() << rx.toHex();
            qDebug() << color << id << infrared << flat << address;
            */
        }
    }
}
namespace {
//void encodeLegacy(const Owl::Protocol::Robot_Command& command, QByteArray& tx, int num) {
void encodeLegacy(const rbk::protocol::Message_SSL_Command& command, QByteArray& tx, int num) {
    // send back to vision module
    // num 0 ~ 3
    // id  0 ~ 15
    quint8 id = (quint8)command.robot_id();
    double origin_vx = command.velocity_x();
    double origin_vy = command.velocity_y();
    double origin_vr = command.velocity_r();
    double dt = 1. / Owl::SIParamManager::Instance()->DesiredFPS;
    double theta = - origin_vr * dt;
    CVector v(origin_vx, origin_vy);
    v = v.rotate(theta);
    if (fabs(theta) > 0.00001) {
        //            if (i==0) cout << theta << " " <<vx << " "<< vy << " ";
        v = v * theta / (2 * sin(theta / 2));
        origin_vx = v.x();
        origin_vy = v.y();
        //            if (i==0) cout << vx << " "<< vy << " " << endl;
    }


    qint16 vx = (qint16)(origin_vx);
    qint16 vy = (qint16)(origin_vy);
    qint16 vr = (qint16)(origin_vr * 40);
    qint16 abs_vx = std::abs(vx);
    qint16 abs_vy = std::abs(vy);
    qint16 abs_vr = std::abs(vr);
    //if(abs(vx) > 0.1) qDebug() << "id: " << id<< "  "<<num*4 + 1<< "  "<<vx;
    // flat&chip m/s -> cm/s
    // kick   1 : chip   0 : flat`
    //bool kick = command.kick();
    //quint16 speed = command.power();
    bool kick = command.flat_kick()==0? 1:0;
    quint16 speed = kick? command.chip_kick(): command.flat_kick();
    quint8 power = 0;
    if(speed > 0.5) {
        //power = kickStandardization(id, kick, (quint16)(command.power()));
        power = kickStandardization(id, kick, (quint16)(speed));
    }
//    qDebug() << "id: " << id << "power: " << power << "speed: " << command.power();
    // dribble -1 ~ +1 -> -3 ~ +3
    qint8 dribble = command.dribbler_spin() > 0.5 ? 3 : 0;
    tx[0] = (tx[0]) | (1 << (3 - num));
    tx[num * 4 + 1] = ((quint8)kick << 6) | dribble << 4 | id;
    tx[num * 4 + 2] = (vx >> 8 & 0x80) | (abs_vx & 0x7f);
    tx[num * 4 + 3] = (vy >> 8 & 0x80) | (abs_vy & 0x7f);
    tx[num * 4 + 4] = (vr >> 8 & 0x80) | (abs_vr & 0x7f);
    tx[num  + 17] = (abs_vx >> 1 & 0xc0) | (abs_vy >> 3 & 0x30) | (abs_vr >> 7 & 0x0f);
    tx[num  + 21] = power;
}

quint8 kickStandardization(quint8 id, bool mode, quint16 power) {
    //if(power > 1) qDebug() << "id: "<<id<<" power: "<<power;
    double new_power = 0;
    double a, b, c;
    double min_power, max_power;
    QString key = "";

    float ratio = mode ? 1 : 0.00001;
    key = QString("Robot%1/%2_A").arg(id).arg(mode ? "CHIP" : "FLAT");
    KParamManager::Instance()->loadParam(a, key, 0);
    key = QString("Robot%1/%2_B").arg(id).arg(mode ? "CHIP" : "FLAT");
    KParamManager::Instance()->loadParam(b, key, 1);
    key = QString("Robot%1/%2_C").arg(id).arg(mode ? "CHIP" : "FLAT");
    KParamManager::Instance()->loadParam(c, key, 0);
    key = QString("Robot%1/%2_MIN").arg(id).arg(mode ? "CHIP" : "FLAT");
    KParamManager::Instance()->loadParam(min_power, key, 15);
    key = QString("Robot%1/%2_MAX").arg(id).arg(mode ? "CHIP" : "FLAT");
    KParamManager::Instance()->loadParam(max_power, key, 70);
    new_power = (int)( ratio * a * power * power + b * power + c);
    new_power = std::max(min_power, std::min(new_power, max_power));
    new_power = std::max(10.0, std::min(new_power, 127.0));
    return (quint8)new_power;
}
} // namespace Owl::anonymous
}
