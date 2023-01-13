/**
#include "optionobject.h"

namespace {
    auto opm = Owl::OParamManager::Instance();
    auto cpm = Owl::CParamManager::Instance();
}

optionObject::optionObject()
{
    sending = false;
}
optionObject::~optionObject(){
    udpAbort();
    QThread::quit();
}

bool optionObject::udpSetup(){
    try {
        //udpSocket.bind(QHostAddress::AnyIPv4,cpm->optionPort,QUdpSocket::ShareAddress);
        //udpSocket.joinMulticastGroup(QHostAddress(cpm->local_address));
    } catch (_exception &e) {
        qDebug()<<"Error in optionObject socket: "<<e.type;
        return false;
    }
    return true;
}

void optionObject::sendOption(){
    //Sent Option message to rbk
    //Contents of Message: color: yellow or blue side: left or right sim: real or simulation
    option_Setting option; //protobuf msg of src_option
    int refPort = opm->isYellow? opm->refereePortToYellow : opm->refereePortToBlue;
    
    option.set_isright(opm->isRight);
    option.set_isyellow(opm->isYellow);
    option.set_isreal(!opm->isSimulation);
    option.set_refereeip(cpm->referee_address.toStdString());
    option.set_refport(refPort);
    option.set_serialport(opm->serialPort.toStdString());

    int size = option.ByteSize();
    QByteArray buffer(size,0);
    option.SerializeToArray(buffer.data(),buffer.size());

    GlobalData::Instance()->ctrlCMutex.lock();
    bool sw = GlobalData::Instance()->ctrlC;
    GlobalData::Instance()->ctrlCMutex.unlock();
    if(!sw){
        qDebug()<<"Send option:---isRight:"<<opm->isRight<<"||---isYellow:"<<opm->isYellow<<"||---isReal:"<<!opm->isSimulation<<"||---refereeIP:"<<cpm->referee_address<<"||---refPort:"<<refPort<<"||---serialPort:"<<opm->serialPort<<"||---";
        for(int i=0;i<400;i++){
            udpSocket.writeDatagram(buffer.data(),buffer.size(),QHostAddress(cpm->local_address),cpm->optionPort);
            Sleep(20);
        }
    }
}

void optionObject::udpAbort(){
    udpSocket.abort();
}

void optionObject::start(){
    while (sending) Sleep(20);
    qDebug() << "Finish Sending";
    while (QThread::isRunning()) {
        QThread::quit();
    }
    qDebug()<<"QThread status" << QThread::isRunning();
    QThread::start();
}

void optionObject::run(){
    sending = true;
    sendOption();
    sending = false;
}
**/