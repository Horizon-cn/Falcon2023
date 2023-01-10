#ifndef CDEBUGGER_H
#define CDEBUGGER_H

#include <QObject>
#include <QUdpSocket>
#include "singleton.h"
// temp before merge medusa TODO
class CDebugger : public QObject
{
    Q_OBJECT
public:
    explicit CDebugger(QObject *parent = nullptr);
    ~CDebugger();
    void start(int);
    void stop(int);

public slots:
    void receiveBlue();
    void receiveYellow();
private:
    
};
typedef Falcon::MeyersSingleton<CDebugger> Debugger;
#endif // CDEBUGGER_H
