#ifndef __VISIONMODULE_H__
#define __VISIONMODULE_H__

#include <QObject>
#include <QUdpSocket>
#include <QTime>
#include "singleton.h"
#include "vision_detection.pb.h"
#include "messageformat.h"
class CVisionModule : public QObject {
    Q_OBJECT
  public:
    CVisionModule(QObject *parent = 0);
    ~CVisionModule();
    void udpSocketConnect();
    void udpSocketDisconnect();
    void parse(void *, int);
    void setIfEdgeTest(bool);
    quint16 getFPS();
    bool dealWithData();
    int FPS;
    QTime t;
    void setInterfaceIndex(const int);
  signals:
    void needDraw();
    void recvPacket();
  public slots:
    void storeData();
  private:
    void receiveVision();
    void parseVision();
    void edgeTest();
    void udpSend();
    void checkCommand();
    bool collectNewVision();
    QUdpSocket udpReceiveSocket, udpResendSocket;
    quint64 counter;
    int _interface;
    bool IF_EDGE_TEST;
    Vision_DetectionFrame detectionFrame;
};
typedef Falcon::MeyersSingleton <CVisionModule> VisionModule;
#endif // __VISIONMODULE_H__
