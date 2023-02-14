#include "actionmodule.h"
#include <QtSerialPort/QSerialPortInfo>
#include "parammanager.h"
#include "crc.h"
#include "globaldata.h"
namespace Owl {
    namespace {
        const int TRANSMIT_PACKET_SIZE = 25;
        const int TRANS_FEEDBACK_SIZE = 25; //18; //20;
        const int ROBOTS_PER_PACKET = 4; //3;
        const int MAX_PACKET_NUM = 4;

        auto opm = OParamManager::Instance();
        auto kpm = KParamManager::Instance();

        int limit_speed(int vel) {
            if (abs(vel) > 511) {
                if (vel > 0)
                    return 511;
                else
                    return -511;
            }
            return vel;
        }
        int convertKickPower(int num, int mode, int power) {
            if (num >= PARAM::ROBOTMAXID) return 0;
            power = fabs(power); // 防止离谱的错误参数
            if (kpm->convertPower) {
                if (mode == 0) {
                    power = (int)(0.00001 * kpm->flat_a[num] * power * power + kpm->flat_b[num] * power + kpm->flat_c[num]);
                    if (power > kpm->flat_max[num]) {
                        power = kpm->flat_max[num];
                    }
                    else if (power < kpm->flat_min[num]) {
                        power = kpm->flat_min[num];
                    }
                }
                else if (mode == 1) {
                    int newPower = 0;
                    newPower = (int)(kpm->chip_a[num] * power * power + kpm->chip_b[num] * power + kpm->chip_c[num]);
                    if (newPower > kpm->chip_max[num] || power > 400) {
                        newPower = kpm->chip_max[num];
                    }
                    else if (newPower < kpm->chip_min[num]) {
                        newPower = kpm->chip_min[num];
                    }
                    power = newPower;
                }
            }          
            return (power > 127 ? 127 : power);
        }
    }
	CActionModule::CActionModule(QObject* parent) : QObject(parent) {
        std::fill_n(shoot, PARAM::ROBOTMAXID, false);
        std::fill_n(ctrl, PARAM::ROBOTMAXID, false);
        std::fill_n(shootMode, PARAM::ROBOTMAXID, false);
        std::fill_n(robotID, PARAM::ROBOTMAXID, PARAM::ROBOTMAXID);
        std::fill_n(velX, PARAM::ROBOTMAXID, 0);
        std::fill_n(velY, PARAM::ROBOTMAXID, 0);
        std::fill_n(velR, PARAM::ROBOTMAXID, 0);
        std::fill_n(ctrlPowerLevel, PARAM::ROBOTMAXID, 0);
        std::fill_n(shootPowerLevel, PARAM::ROBOTMAXID, 0);
        frequency = 0;
		updatePortsList();
        serial.setBaudRate(QSerialPort::Baud115200);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop); //QSerialPort::TwoStop
        tx.resize(TRANSMIT_PACKET_SIZE);
        rx.resize(TRANS_FEEDBACK_SIZE);
        tx[0] = 0x40;
        connect(&serial, &QSerialPort::readyRead, this, &CActionModule::readData);
	}
    CActionModule::~CActionModule() {
        disconnect(&serial);
        closeSerialPort();
    }
    bool CActionModule::changeFrequency(int frequency) {
        if (frequency >= 0 && frequency <= getMaxFrequency()) {
            qDebug() << "change Frequency... : " << frequency;
            this->frequency = frequency;
            return true;
        }
        return false;
    }
    QStringList& CActionModule::updatePortsList() {
        this->ports.clear();
        const auto& ports = QSerialPortInfo::availablePorts();
        for (const auto& port : ports) {
            this->ports.append(port.portName());
        }
        if (this->ports.size() > 0)
            serial.setPortName(this->ports[this->ports.size() - 1]);
        return this->ports;
    }
    bool CActionModule::changePorts(int portNum) {
        if (portNum < ports.size() && portNum >= 0) {
            serial.setPortName(ports[portNum]);
            return true;
        }
        serial.setPortName("");
        return false;
    }
    bool CActionModule::openSerialPort() {
        if (serial.isOpen()) {
            serial.close();
        }
        if (serial.open(QIODevice::ReadWrite)) {
            qDebug() << "SerialPort connected... : " << serial.portName();
            sendStartPacket();
            opm->updateParam(opm->serialPort, "AlertPorts/serialPort", serial.portName(), true);
            return true;
        }
        qDebug() << "SerialPort connect failed... : " << serial.portName();
        return false;
    }
    bool CActionModule::closeSerialPort() {
        if (serial.isOpen()) {
            serial.close();
            qDebug() << "SerialPort Disconnected... : " << serial.portName();
            return true;
        }
        return false;
    }
    void CActionModule::sendStartPacket() {
        QByteArray startPacket1(TRANSMIT_PACKET_SIZE, 0);
        QByteArray startPacket2(TRANSMIT_PACKET_SIZE, 0);
        startPacket1[0] = (char)0xff;
        startPacket1[1] = (char)0xb0;
        startPacket1[2] = (char)0x01;
        startPacket1[3] = (char)0x02;
        startPacket1[4] = (char)0x03;
        startPacket1[TRANSMIT_PACKET_SIZE - 1] = 0x31;
        //startPacket1[TRANSMIT_PACKET_SIZE - 1] = CCrc8::calc((unsigned char*)(startPacket1.data()), TRANSMIT_PACKET_SIZE - 1);

        startPacket2[0] = (char)0xff;
        startPacket2[1] = (char)0xb0;
        startPacket2[2] = (char)0x04;
        startPacket2[3] = (char)0x05;
        startPacket2[4] = (char)0x06;
        startPacket2[5] = 0x10 + frequency;
        startPacket2[TRANSMIT_PACKET_SIZE - 1] = CCrc8::calc((unsigned char*)(startPacket2.data()), TRANSMIT_PACKET_SIZE - 1);
        serial.write(startPacket1);
        serial.flush();
        if (serial.waitForBytesWritten(2000)) {
            if (serial.waitForReadyRead(2000)) {
                serial.readAll();
                while (serial.waitForReadyRead(10))
                    serial.readAll();
            }
        }
        else {
            qDebug() << "Start packet write timeout!";
        }
        serial.write(startPacket2);
        serial.flush();
    }
    void CActionModule::updateCommandParams(int robotID, int velX, int velY, int velR, bool ctrl, int ctrlLevel, bool mode, bool shoot, int power) {
        this->robotID[robotID] = robotID;
        this->velX[robotID] = limit_speed(velX); this->velY[robotID] = limit_speed(velY); this->velR[robotID] = limit_speed(velR);
        this->ctrl[robotID] = ctrl;
        this->shootMode[robotID] = mode; this->shoot[robotID] = shoot; this->shootPowerLevel[robotID] = convertKickPower(robotID, mode, power);
        this->ctrlPowerLevel[robotID] = ctrlLevel;
    }
    //发送指令
    bool CActionModule::sendLegacy(int robotNum) {
        static int packetNum = 0;
        if (serial.portName() != "") {
            std::sort(robotID, robotID + PARAM::ROBOTMAXID);
            //qDebug()<<"robotNum"<<robotNum;
            for (int i = 0; i <= MAX_PACKET_NUM; i++) {
                if (robotNum <= i * ROBOTS_PER_PACKET) {
                    packetNum = i;
                    break;
                }
            }
            //qDebug()<<"packetNum"<<packetNum;
            for (int i = 0; i < packetNum; i++) {
                //encode(i * ROBOTS_PER_PACKET);
                encodeNew(i * ROBOTS_PER_PACKET);
                //if (shoot[0]) qDebug() << shoot[0] << "command" << tx.toHex();
                serial.write(tx.data(), TRANSMIT_PACKET_SIZE);
                serial.flush();
                //serial.waitForBytesWritten(TRANSMIT_PACKET_SIZE * 8.0 * 1000 / 115200 + 0.6); //ms 延时包括串口传输和发射机发送时间
            }
            std::fill_n(robotID, PARAM::ROBOTMAXID, PARAM::ROBOTMAXID);
            return true;
        }
        return false;
    }
    //编码
    bool CActionModule::encode(int startNum) {
        tx.fill(0);
        //head, always 0xff
        tx[0] = 0xff;
        for (int i = 0; i < ROBOTS_PER_PACKET; i++) {
            int real_num = robotID[startNum + i];
            //qDebug()<<"robotID"<<real_num;
            // num
            if (real_num == PARAM::ROBOTMAXID) break;
            if (real_num > 7) {
                tx[1] = tx[1] + (1 << (real_num - 8));
            }
            else {
                tx[2] = tx[2] + (1 << (real_num));
            }
            // shoot
            tx[i * 4 + 3] = (shootMode[real_num] << 6) & 0xFF;
            //ctrl
            tx[i * 4 + 3] = tx[i * 4 + 3] | (ctrl[real_num] ? ((ctrlPowerLevel[real_num] & 0x03) << 4) : 0);
            // vx
            tx[i * 4 + 4] = ((velX[real_num] >= 0) ? 0 : 0x80) | (abs(velX[real_num]) & 0x7f);
            if (tx[i * 4 + 4] == char(0xFF)) {
                tx[i * 4 + 4] = 0xFE;
            }
            //qDebug()<<"velX"<<velX[real_num];
            // vy 
            tx[i * 4 + 5] = ((velY[real_num] >= 0) ? 0 : 0x80) | (abs(velY[real_num]) & 0x7f);
            if (tx[i * 4 + 5] == char(0xFF)) {
                tx[i * 4 + 5] = 0xFE;
            }
            // vr
            tx[i * 4 + 6] = ((velR[real_num] >= 0) ? 0 : 0x80) | (abs(velR[real_num]) & 0x7f);
            if (tx[i * 4 + 6] == char(0xFF)) {
                tx[i * 4 + 6] = 0xFE;
            }
            tx[i * 1 + 15] = ((abs(velX[real_num]) & 0x180) >> 1) | ((abs(velY[real_num]) & 0x180) >> 3) | ((abs(velR[real_num]) & 0x180) >> 5);
            // kick pow
            tx[i * 1 + 18] = (shoot[real_num] ? shootPowerLevel[real_num] : 0) & 0x7f;
        }
        return true;
    }
    bool CActionModule::encodeNew(int startNum) {
        tx.fill(0);
        //head, always 0xff
        tx[0] = 0xff;
        for (int i = 0; i < ROBOTS_PER_PACKET; i++) {
            int real_num = robotID[startNum + i];
            //qDebug()<<"robotID"<<real_num;
            // num
            if (real_num == PARAM::ROBOTMAXID) break;
            if (real_num > 7) {
                tx[1] = tx[1] + (1 << (real_num - 8)) & 0xFF;
            }
            else {
                tx[2] = tx[2] + (1 << (real_num)) & 0xFF;
            }
            // shoot
            tx[i * 4 + 3] = (shootMode[real_num] << 6) & 0xFF;
            //ctrl
            tx[i * 4 + 3] = tx[i * 4 + 3] | (ctrl[real_num] ? ((ctrlPowerLevel[real_num] & 0x03) << 4) : 0);
            // vx
            tx[i * 4 + 4] = ((velX[real_num] >= 0) ? 0 : 0x80) | (abs(velX[real_num]) & 0x7f);
            if (tx[i * 4 + 4] == char(0xFF)) {
                tx[i * 4 + 4] = 0xFE;
            }
            //qDebug()<<"velX"<<velX[real_num];
            // vy 
            tx[i * 4 + 5] = ((velY[real_num] >= 0) ? 0 : 0x80) | (abs(velY[real_num]) & 0x7f);
            if (tx[i * 4 + 5] == char(0xFF)) {
                tx[i * 4 + 5] = 0xFE;
            }
            // vr
            tx[i * 4 + 6] = ((velR[real_num] >= 0) ? 0 : 0x80) | (abs(velR[real_num]) & 0x7f);
            if (tx[i * 4 + 6] == char(0xFF)) {
                tx[i * 4 + 6] = 0xFE;
            }
            // high bits
            tx[i * 4 + 3] = tx[i * 4 + 3] | ((abs(velX[real_num]) & 0x180) >> 5) | ((abs(velY[real_num]) & 0x180) >> 7);
            tx[19] = tx[19] | ((abs(velR[real_num]) & 0x180) >> (2 * i + 1));
            // kick pow
            tx[i * 1 + 20] = (shoot[real_num] ? shootPowerLevel[real_num] : 0) & 0x7f;
        }
        return true;
    }
    void CActionModule::readData() {
        //serial.waitForReadyRead(100);
        QByteArray data = serial.readAll();
        //qDebug() << "readData" << data.toHex();
        int id = 0;
        bool dribble = false;
        int change_num = 0, change_cnt = 0;
        for (unsigned int i = 0; i < data.length(); i++) {
            if (data[i] == (char)0xff && i + 5 < data.length()) {
                if (data[i + 1] == (char)0x02) {
                    id = ((quint8)data[i + 2] & 0x0F) - 1;//old protocal
                    if (id >= PARAM::ROBOTMAXID)
                        break;
                    GlobalData::Instance()->robotInfoMutex.lock();
                    GlobalData::Instance()->robotInformation[opm->isYellow][id].infrared = ((quint8)data[i + 3] & 0x40) > 0;
                    GlobalData::Instance()->robotInformation[opm->isYellow][id].flat = ((quint8)data[i + 3] & 0x20) >> 5 > 0;
                    GlobalData::Instance()->robotInformation[opm->isYellow][id].chip = ((quint8)data[i + 3] & 0x10) >> 4 > 0;
                    dribble = (data[i + 3] & 0x08) >> 3;
                    change_num = data[i + 4] & 0xff;
                    change_cnt = data[i + 5] & 0x0f;
                    GlobalData::Instance()->robotInfoMutex.unlock();
                    emit receiveRobotInfo(opm->isYellow, id);
                }
            }
        }
    }
}