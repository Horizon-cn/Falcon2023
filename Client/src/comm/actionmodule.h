#ifndef ZACTIONMODULE_H
#define ZACTIONMODULE_H
#include <QObject>
#include <QMutex>
#include <QUdpSocket>
#include <QSerialPort>
#include "singleton.h"
#include "zss_cmd.pb.h"
#include "src_cmd.pb.h"
#include "staticparams.h"
namespace Owl {
class ActionModule : public QObject {
    Q_OBJECT
  public:
    ActionModule(QObject *parent = 0);
    ~ActionModule();
    //void sendLegacy(int t, const Owl::Protocol::Robots_Command&);
    void sendLegacy(int t, const rbk::protocol::SRC_Cmd&);
    bool connectRadio(int, int);
    bool disconnectRadio(int);
    int team[PARAM::TEAMS];
  private slots:
    void readData();
  private:
    void sendStartPacket(int, int);
  private:
    QByteArray tx;
    QByteArray rx;
    QUdpSocket sendSocket;
    QUdpSocket receiveSocket;
    QMutex robotInfoMutex;
  signals:
    void receiveRobotInfo(int, int);
};
typedef Falcon::MeyersSingleton<ActionModule> ZActionModule;

class ActionModuleSerialVersion : public QObject
{
    Q_OBJECT
public:
    ActionModuleSerialVersion(QObject *parent = 0);
    ~ActionModuleSerialVersion();
    bool changeFrequency(int);
    int getFrequency(){return frequency;}
    int getMaxFrequency(){return 9;}
    QStringList& updatePortsList();
    bool changePorts(int);
    std::string getSerialPort(){return serial.portName().toStdString();}
    bool openSerialPort();
    bool closeSerialPort();
    void setMedusaSettings(bool,bool);
    void sendLegacy(const ZSS::Protocol::Robots_Command&);
    QSerialPort serial;
signals:
    void receiveRobotInfo(int,int);
private slots:
    void readData();
private:
    void sendStartPacket();
private:
    QStringList ports;
    int frequency = 8;
    QByteArray tx;
    QByteArray rx;
    int _color;
    int _side;
};
typedef Falcon::MeyersSingleton<ActionModuleSerialVersion> NActionModule;
}
#endif // ZACTIONMODULE_H
