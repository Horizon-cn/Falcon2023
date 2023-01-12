#ifndef CNETWORKINTERFACES_H
#define CNETWORKINTERFACES_H
#include <QObject>
#include <QStringList>
#include <QNetworkInterface>
#include <singleton.h>
class CNetworkInterfaces: public QObject {
    Q_OBJECT
public:
    explicit CNetworkInterfaces(QObject *parent = nullptr);
    QNetworkInterface getFromIndex(const int index){ return QNetworkInterface::interfaceFromName(interfaces[index]); }
    Q_INVOKABLE QStringList getInterfaces(){ return interfaces; }
    Q_INVOKABLE void updateInterfaces();
    //Q_INVOKABLE void changeVisionInterface(int);
    QStringList getGrsimInterfaces() { return grsimInterfaces; }
    QString getLocalAddress();
    bool Ping(const QString ip);
private:
    QStringList interfaces;
    QStringList grsimInterfaces;
};
typedef Falcon::MeyersSingleton <CNetworkInterfaces> NetworkInterfaces;
#endif // CNETWORKINTERFACES_H
