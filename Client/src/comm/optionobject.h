#ifndef OPTIONOBJECT_H
#define OPTIONOBJECT_H

#include <QThread>

#include "src_option.pb.h"
#include "globaldata.h"
#include "parammanager.h"
#include "actionmodule.h"

#include <exception>
#include <Windows.h>

#include <QUdpSocket>
#include <QDebug>
#include "staticparams.h"
class optionObject : public QThread
{
    Q_OBJECT
public:
    explicit optionObject();
    ~optionObject();

    Q_INVOKABLE void start();
    Q_INVOKABLE bool udpSetup();
    Q_INVOKABLE void udpAbort();
    Q_INVOKABLE void sendOption();
    Q_INVOKABLE bool processIsRunning() const{return QThread::isRunning();} 

private:
    void run();
    bool sending;
    QUdpSocket udpSocket;

signals:

public slots:
};

#endif // OPTIONOBJECT_H
