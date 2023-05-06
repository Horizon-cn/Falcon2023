#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
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
    void setGrsimInterfaceIndex(const int index);
    int getGrsimInterfaceIndex() {return grsimInterfaceIndex;}
    int getFPS(int);
    const Owl::RobotCommands getCommands(int t) {
        return commandBuffer[t];
    }
    void clearCommands() {
        commandBuffer[PARAM::BLUE] = Owl::RobotCommands();
        commandBuffer[PARAM::YELLOW] = Owl::RobotCommands();
    }
    void startRecordCommands(bool);
    void recordCommands(ZSS::Protocol::Robots_Command);
    //void recordCommands(rbk::protocol::SRC_Cmd);
    void sendCommand(int, int);
  private slots:
    void receiveCommand(int);
    //void sendEmptyCmd(int);
  private:
    QUdpSocket sendSockets, receiveSocket[PARAM::TEAMS];
    QStringList networkInterfaceNames;
    QStringList networkInterfaceReadableNames;
    Owl::RobotCommands commandBuffer[PARAM::TEAMS];
    int networkInterfaceIndex;
    int grsimInterfaceIndex;
    QString filename;
    bool startRecord = false;
};
typedef Falcon::MeyersSingleton<Communicator> ZCommunicator;
#endif // COMMUNICATOR_H
