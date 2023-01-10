#include <QTime>
#include <QtDebug>
#include <QElapsedTimer>
#include "refereebox.h"
#include "parammanager.h"
#include "ssl_referee.pb.h"
#include "globalsettings.h"
#include "globaldata.h"
#include "game.h"
void multicastCommand(int state);

namespace {
    auto opm = Owl::OParamManager::Instance();
    auto cpm = Owl::CParamManager::Instance();
}

RefereeBox::RefereeBox(QObject *parent) : QObject(parent),currentCommand(GameState::HALTED),nextCommand(GameState::HALTED),udpReceiveSocket(){
    sendSocket.setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
    currentStage = 1;
    commandCounter = 1;
}
RefereeBox::~RefereeBox(){
    sendSocket.abort();
    disconnect(&udpReceiveSocket);
    udpReceiveSocket.abort();
}
void RefereeBox::changeStage(){
    stageMutex.lock();
    currentStage = (currentStage + 1) % 14;
    stageMutex.unlock();
}
void RefereeBox::changeCommand(int command){
    commandMutex.lock();
    currentCommand = command;
    commandCounter++;
    commandMutex.unlock();
}
void RefereeBox::multicastCommand(){
    Referee ssl_referee;
    ssl_referee.set_packet_timestamp(0);//todo
    
    stageMutex.lock();
    ssl_referee.set_stage(Referee_Stage(currentStage));
    ssl_referee.set_stage_time_left(0);//todo
    stageMutex.unlock();

    commandMutex.lock();
    ssl_referee.set_command(Referee_Command(currentCommand));
    ssl_referee.set_command_counter(commandCounter);//todo
    commandMutex.unlock();

    ssl_referee.set_command_timestamp(0);//todo
    Referee_TeamInfo *yellow = ssl_referee.mutable_yellow();
    yellow->set_name(opm->blueTeam.toStdString());
    yellow->set_score(0);//todo
    yellow->set_red_cards(0);//todo
    //yellow->set_yellow_card_times(0,0); //todo
    yellow->set_yellow_cards(0);//todo
    yellow->set_timeouts(0.0);//todo
    yellow->set_timeout_time(0.0);//todo
    yellow->set_goalkeeper(0); //todo
    Referee_TeamInfo *blue = ssl_referee.mutable_blue();
    blue->set_name(opm->yellowTeam.toStdString());
    blue->set_score(0);//todo
    blue->set_red_cards(0);//todo
    //blue->set_yellow_card_times(0,0); //todo
    blue->set_yellow_cards(0);//todo
    blue->set_timeouts(0.0);//todo
    blue->set_timeout_time(0.0);//todo
    blue->set_goalkeeper(0); //todo
    Referee_Point *point = ssl_referee.mutable_designated_position();
    point->set_x(GlobalSettings::Instance()->ballPlacementX);
    point->set_y(GlobalSettings::Instance()->ballPlacementY);
    // add test for next_command
    ssl_referee.set_next_command(Referee_Command(nextCommand));
    int size = ssl_referee.ByteSize();
    QByteArray buffer(size,0);
    ssl_referee.SerializeToArray(buffer.data(), buffer.size());
    sendSocket.writeDatagram(buffer.data(), buffer.size(), QHostAddress(cpm->referee_address), opm->refereePortToBlue);
    sendSocket.writeDatagram(buffer.data(), buffer.size(), QHostAddress(cpm->referee_address), opm->refereePortToYellow);
    if(GlobalData::Instance()->refereeMode==1)
        sendSocket.writeDatagram(buffer.data(), buffer.size(), QHostAddress(cpm->referee_address), cpm->refereePortToAutoRef);
}
void RefereeBox::changeRefereeMode(int refMode) {
    GlobalData::Instance()->refereeMode = refMode; //false Manual Control
    qDebug()<<"changeRefereeMode "<<GlobalData::Instance()->refereeMode<<" "<<refMode;
    if(refMode==2) {
        udpReceiveSocket.bind(QHostAddress::AnyIPv4, cpm->refereePortFromGC, QUdpSocket::ShareAddress);
        udpReceiveSocket.joinMulticastGroup(QHostAddress(cpm->ssl_address));
        connect(&udpReceiveSocket, SIGNAL(readyRead()), this, SLOT(multicastGC()), Qt::DirectConnection);
        qDebug()<<"connect to GC";
    }
    else {
        disconnect(&udpReceiveSocket);
        udpReceiveSocket.abort();
        qDebug()<<"disconnect with GC";
    }
}
void RefereeBox::multicastGC() {
    static QByteArray datagram;
    while (udpReceiveSocket.hasPendingDatagrams()) {
        datagram.resize(udpReceiveSocket.pendingDatagramSize());
        udpReceiveSocket.readDatagram(datagram.data(), datagram.size());
        sendSocket.writeDatagram(datagram.data(), datagram.size(), QHostAddress(cpm->referee_address), opm->refereePortToBlue);
        sendSocket.writeDatagram(datagram.data(), datagram.size(), QHostAddress(cpm->referee_address), opm->refereePortToYellow);
        sendSocket.writeDatagram(datagram.data(), datagram.size(), QHostAddress(cpm->referee_address), cpm->refereePortToAutoRef);
        qDebug()<<"finish multicastGC";
    }
}
