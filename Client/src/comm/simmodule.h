#ifndef SIMMODULE_H
#define SIMMODULE_H
#include <QObject>
#include <QMutex>
#include <QUdpSocket>
#include "singleton.h"
#include "zss_cmd.pb.h"
#include "src_cmd.pb.h"

namespace Owl{
class SimModule : public QObject{
    Q_OBJECT
public:
    SimModule(QObject *parent = 0);
    ~SimModule();
    bool connectSim(bool);
    bool disconnectSim(bool);
    //void sendSim(int t, Owl::Protocol::Robots_Command& command);
    void sendSim(int t, rbk::protocol::SRC_Cmd& command);
    //void sendEmptySim();
private slots:
    void readBlueData();
    void readYellowData();
private:
    QByteArray tx;
    QByteArray rx;
    // QUdpSocket sendSocket;
    QString receiveAddress;
    QUdpSocket blueReceiveSocket;
    QUdpSocket yellowReceiveSocket;
    QMutex robotInfoMutex;
    QUdpSocket command_socket;
signals:
    void receiveSimInfo(int,int);
};
typedef Falcon::MeyersSingleton<SimModule> ZSimModule;
}
#endif
