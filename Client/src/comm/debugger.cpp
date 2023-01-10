#include "debugger.h"
#include "globaldata.h"
#include "staticparams.h"
#include <thread>
namespace {
    std::thread* blueDebuggerThread = nullptr;
    std::thread* yellowDebuggerThread = nullptr;
    auto cpm = Owl::CParamManager::Instance();
}
CDebugger::CDebugger(QObject *parent) : QObject(parent){}

CDebugger::~CDebugger(){
    stop(PARAM::BLUE);
    stop(PARAM::YELLOW);
}

void CDebugger::start(int team){
    if(team == PARAM::BLUE){
    //    QObject::connect(&receiverBlue,SIGNAL(readyRead()),this,SLOT(receiveBlue()),Qt::DirectConnection);
        blueDebuggerThread = new std::thread([=] {receiveBlue();});
        blueDebuggerThread->detach();
    }
    else if(team == PARAM::YELLOW){
    //    QObject::connect(&receiverYellow,SIGNAL(readyRead()),this,SLOT(receiveYellow()),Qt::DirectConnection);
        yellowDebuggerThread = new std::thread([=] {receiveYellow();});
        yellowDebuggerThread->detach();
    }
}

void CDebugger::stop(int team){
    if(team == PARAM::BLUE){
        delete blueDebuggerThread;
        blueDebuggerThread = nullptr;
    }
    else if(team == PARAM::YELLOW){
        delete yellowDebuggerThread;
        yellowDebuggerThread = nullptr;
    }
}

void CDebugger::receiveBlue(){
    QUdpSocket receiverBlue;
    if(!receiverBlue.bind(QHostAddress::AnyIPv4, cpm->blue_debug, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)){
        qDebug()<<"Fail to bind blue debug";
    }
    auto& datagram = GlobalData::Instance()->debugBlueMessages;
    while(true){
        std::this_thread::sleep_for(std::chrono::microseconds(5));
        while (receiverBlue.state() == QUdpSocket::BoundState && receiverBlue.hasPendingDatagrams()) {
            GlobalData::Instance()->debugMutex.lock();
            datagram.resize(receiverBlue.pendingDatagramSize());
            receiverBlue.readDatagram(datagram.data(),datagram.size());
            GlobalData::Instance()->debugMutex.unlock();
        }
    }
}

void CDebugger::receiveYellow(){
    QUdpSocket receiverYellow;
    if (!receiverYellow.bind(QHostAddress::AnyIPv4, cpm->yellow_debug, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)){
        qDebug()<<"Fail to bind yellow debug";
    }
    auto& datagram = GlobalData::Instance()->debugYellowMessages;
    while(true){
        std::this_thread::sleep_for(std::chrono::microseconds(5));
        while (receiverYellow.state() == QUdpSocket::BoundState && receiverYellow.hasPendingDatagrams()) {
            GlobalData::Instance()->debugMutex.lock();
            datagram.resize(receiverYellow.pendingDatagramSize());
            receiverYellow.readDatagram(datagram.data(),datagram.size());
            GlobalData::Instance()->debugMutex.unlock();
        }
    }
}
