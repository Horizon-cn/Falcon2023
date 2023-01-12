#ifndef REMOTESIM_H
#define REMOTESIM_H

#include <QObject>
#include <QUdpSocket>
#include "singleton.h"
#include "zss_cmd.pb.h"

namespace ZSS{

class RemoteSim : public QObject
{
    Q_OBJECT
public:
    RemoteSim(QObject *parent = 0);
    ~RemoteSim();
    bool connectSim(bool);
    bool disconnectSim(bool);
    void sendSim(int t, ZSS::Protocol::Robots_Command& command);
private slots:
    void readBlueData();
    void readYellowData();
private:
    QByteArray tx;
    QByteArray rx;
    QString receiveAddress;
    QUdpSocket blueReceiveSocket;
    QUdpSocket yellowReceiveSocket;
    QUdpSocket command_socket;
    QString RemoteAddress;
signals:
    void receiveRemoteInfo(int,int);
};

typedef Falcon::MeyersSingleton<RemoteSim> ZRemoteSimModule;
}
#endif // REMOTESIM_H
