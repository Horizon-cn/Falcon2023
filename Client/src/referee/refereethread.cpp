﻿/**
#include "refereethread.h"
#include "parammanager.h"
#include <QHostAddress>
namespace {
auto opm = Owl::OParamManager::Instance();
auto cpm = Owl::CParamManager::Instance();
}
CRefereeThread::CRefereeThread() {
    client = new QTcpSocket();
}

CRefereeThread::~CRefereeThread() {
    disconnectTCP();
}
bool CRefereeThread::connectTcp(QHostAddress address, quint16 port) {
    client->bind(45000);
    client->connectToHost(address, port, QTcpSocket::ReadWrite);
    bool connected = client->waitForConnected();
    qDebug() << client->localPort();
    if (!connected) {
        qDebug() << "ERROR : Establish TCP to game controller fail. ";
    } else {
        qDebug() << "Establish TCP to game controller success, wait for First receive";
    }
    return connected;
}
bool CRefereeThread::disconnectTCP() {
    client->abort();
    if (client->state() != QAbstractSocket::UnconnectedState) {
        qDebug() << "ERROR fail to disconnect" << client->state();
    } else {
        qDebug() << "TCP successfully disconnect! ";
        return true;
    }
    return false;
}

ControllerToTeam CRefereeThread::receiveControllerReply() {
    ControllerToTeam* controllerToTeam = new ControllerToTeam();
    client->waitForReadyRead();
    QByteArray buffer(10, 0);
    if (client->bytesAvailable() > 0) {
        buffer.clear();
        buffer = client -> readAll();

        google::protobuf::io::CodedInputStream* input =
            new google::protobuf::io::CodedInputStream((google::protobuf::uint8*)buffer.data(), buffer.size()) ;
        bool eof = false;
        if (!google::protobuf::util::ParseDelimitedFromCodedStream(controllerToTeam, input, &eof)) {
            qDebug() << "Unable to parse Controller Reply";
        } else {
            qDebug() << "Receive controller reply";// << QString::fromStdString(controllerToTeam->ShortDebugString());
        }
        return *controllerToTeam;
    }
    qDebug() << "ERROR: fail to receive ControllerReply";
    return *controllerToTeam;
}

bool CRefereeThread::registerTeam() {
    QByteArray buffer(10, 0);

    //Receive VERY first Reply
    ControllerReply controllerReply = receiveControllerReply().controller_reply();
    std::string nextToken = controllerReply.next_token();
    qDebug() << "receive TOKEN" << QString::fromStdString(nextToken);

    //Send Register Packet
    TeamRegistration* teamRegistration = new TeamRegistration();
    teamRegistration->set_team_name("SRC");
    
    //Signature* teamSignature = teamRegistration->mutable_signature();
    //teamSignature->set_token(nextToken);
    //generatePkcsSig();
    
    buffer.clear();
    buffer.resize(teamRegistration->ByteSize() + 2);
    google::protobuf::io::ArrayOutputStream arrout(buffer.data(), buffer.size());
    google::protobuf::io::CodedOutputStream output(&arrout) ;
    google::protobuf::util::SerializeDelimitedToCodedStream(*teamRegistration, &output);
    if ( client->write(buffer.data(), buffer.size()) > 0 ) {
        qDebug() << "Register Packet Send ";
    } else {
        qDebug() << "ERROR: fail to Register Packet Send";
        return false;
    }

    //Receive Result
    controllerReply = receiveControllerReply().controller_reply();
    if (controllerReply.status_code() == ControllerReply_StatusCode_OK ) {
        qDebug() << "Register SRC success Verified Status"
                 << controllerReply.verification();
        return true;
    } else {
        qDebug() << "ERROR : fail to RegisterTeam:"
                 << QString::fromStdString(controllerReply.ShortDebugString());
        return false;
    }
    return true;
}

bool CRefereeThread::requestKeeper(int keeper_num) {
    QByteArray buffer(10, 0);
    TeamToController teamToController = TeamToController();
    teamToController.set_desired_keeper(keeper_num);
    buffer.clear();
    buffer.resize(teamToController.ByteSize() + 2);
    google::protobuf::io::ArrayOutputStream arrout(buffer.data(), buffer.size());
    google::protobuf::io::CodedOutputStream output(&arrout) ;
    google::protobuf::util::SerializeDelimitedToCodedStream(teamToController, &output);
    if ( client->write(buffer.data(), buffer.size()) > 0 ) {
        qDebug() << "Register Packet Send " << QString::fromStdString(teamToController.ShortDebugString());
    } else {
        qDebug() << "ERROR: fail to Register Packet Send";
        return false;
    }

    ControllerReply controllerReply = receiveControllerReply().controller_reply();
    qDebug() << QString::fromStdString( controllerReply.ShortDebugString());
    if (controllerReply.status_code() == ControllerReply_StatusCode_OK ) {
        qDebug() << " success Verified Status"
                 << controllerReply.verification();
        return true;
    } else {
        qDebug() << "ERROR : fail to Send Message:"
                 << QString::fromStdString( controllerReply.ShortDebugString());
        return false;
    }
}

bool CRefereeThread::advantageChoice(bool _stop) {
    QByteArray buffer(10, 0);
    TeamToController teamToController = TeamToController();
    _stop ? teamToController.set_advantage_response(TeamToController_AdvantageResponse_STOP) :
    teamToController.set_advantage_response(TeamToController_AdvantageResponse_CONTINUE);
    buffer.clear();
    buffer.resize(teamToController.ByteSize() + 2);
    google::protobuf::io::ArrayOutputStream arrout(buffer.data(), buffer.size());
    google::protobuf::io::CodedOutputStream output(&arrout) ;
    google::protobuf::util::SerializeDelimitedToCodedStream(teamToController, &output);
    if ( client->write(buffer.data(), buffer.size()) > 0 ) {
        qDebug() << "Register Packet Send " << QString::fromStdString(teamToController.ShortDebugString());
    } else {
        qDebug() << "ERROR: fail to Register Packet Send";
        return false;
    }

    ControllerReply controllerReply = receiveControllerReply().controller_reply();
    qDebug() << QString::fromStdString( controllerReply.ShortDebugString());
    if (controllerReply.status_code() == ControllerReply_StatusCode_OK ) {
        qDebug() << " success Verified Status"
                 << controllerReply.verification();
        return true;
    } else {
        qDebug() << "ERROR : fail to Send Message:"
                 << QString::fromStdString( controllerReply.ShortDebugString());
        return false;
    }
}

void CRefereeThread::run() {
    qDebug()<<"refereeThread";
    connectTcp(QHostAddress(cpm->GC_Address), cpm->GC_Port);
    registerTeam();
    requestKeeper(opm->KeeperID);
//    disconnectTCP();
}
**/
