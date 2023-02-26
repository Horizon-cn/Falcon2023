#ifndef CSCRIPTSINTERFACES_H
#define CSCRIPTSINTERFACES_H
#include <QObject>
#include <QStringList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <singleton.h>
class CScriptsInterfaces : public QObject {
    Q_OBJECT
public:
    explicit CScriptsInterfaces(QObject* parent = nullptr);
    void updatePlayList();
    void changeReadyPlay(int);
    void writeJsonFile();
    QStringList getPlayList() { return playList; }
private:
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QStringList playList;
};
typedef Falcon::MeyersSingleton <CScriptsInterfaces> ScriptsInterfaces;
#endif // CNETWORKINTERFACES_H