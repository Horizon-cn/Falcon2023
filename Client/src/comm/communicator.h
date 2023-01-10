#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QMutex>
#include <QUdpSocket>
#include <singleton.h>
#include "globaldata.h"
#include "staticparams.h"
#include "zss_cmd.pb.h"
#include "src_cmd.pb.h"
#include "messages_robocup_ssl_robot_status.pb.h"
class Communicator : public QObject {
    Q_OBJECT
  public:
    explicit Communicator(QObject *parent = nullptr);
    ~Communicator();
    bool connectMedusa(int);
    bool disconnectMedusa(int);
    int getFPS(int);
    const Owl::RobotCommands getCommands(int t) {
        return commandBuffer[t];
    }
    void clearCommands() {
        commandBuffer[PARAM::BLUE] = Owl::RobotCommands();
    }
    void startRecordCommands(bool);
    void recordCommands(rbk::protocol::SRC_Cmd);
  private slots:
    void receiveCommand(int);
    void sendCommand(int, int);
    //void sendEmptyCmd(int);
  private:
    QUdpSocket sendSockets, receiveSocket[PARAM::TEAMS];
    QStringList networkInterfaceNames;
    QStringList networkInterfaceReadableNames;
    Owl::RobotCommands commandBuffer[PARAM::TEAMS];
    int networkInterfaceIndex;
    QMutex robotInfoMutex;
    bool isSimulation;
    QString filename;
    bool startRecord = false;
};
typedef Falcon::MeyersSingleton<Communicator> ZCommunicator;
#endif // COMMUNICATOR_H
