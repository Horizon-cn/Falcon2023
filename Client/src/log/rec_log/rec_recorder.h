#ifndef REC_RECORDER_H
#define REC_RECORDER_H
#include "zss_rec.pb.h"
#include "singleton.h"
#include <QQuickItem>

class RecRecorder : public QQuickItem
{
    Q_OBJECT
public:
    RecRecorder(QQuickItem *parent=0);
    ~RecRecorder();
    void start();
    void cut(bool);
    void stop();
    void store();
    void storeRaw();
    void setRecordRawVision(bool);

private:
    QList <QByteArray> buffers;
    ZSS::Protocol::RecMessages recMsgs;

private slots:
    void markNewPacket();
};

typedef Falcon::MeyersSingleton<RecRecorder> ZRecRecorder;

#endif // REC_RECORDER_H
