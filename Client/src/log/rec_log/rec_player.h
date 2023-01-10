#ifndef REC_PLAYER_H
#define REC_PLAYER_H
#include <QThread>
#include <QFile>
#include <QUdpSocket>
#include "zss_rec.pb.h"
#include "geometry.h"
#include "messageformat.h"
#include "singleton.h"

class CRecPlayer : public QThread
{
    Q_OBJECT
public:
    CRecPlayer();
    ~CRecPlayer();
    bool loadRec(QString& filename, int& maxframe);
    bool start(int position);
    void stop();
    bool good();
    void pause();
    void slowly(int position);
    void setPlayerRate(int playerRate) { this->playerRate = playerRate; }
    void setPlayerRawVision(bool playRawVision) { this->playRawVision = playRawVision; }
signals:
    void positionChanged(int frame);
private:
    void run();
    int calCamNum();
    void playLogVision();
    void sendMessage(const QByteArray& packet);
    void sendMessage(const ZSS::Protocol::RecMessage& recMsg);
    void sendMessage(const SSL_WrapperPacket packet);
    void sendMessageToWeb(const QByteArray* packet);
    void sendMessageToWeb(const SSL_WrapperPacket* ssl_wrapperpacket);

    bool _run;
    int _currentFrame;
    int num;
    int playerRate = 1;
    bool playRawVision = true;
    QFile* replayFile;
    // QList <QByteArray> packets;
    QUdpSocket* udpSendSocket;
    ZSS::Protocol::RecMessages recMsgs;
};

typedef Falcon::MeyersSingleton<CRecPlayer> RecPlayer;

#endif // REC_PLAYER_H
