#ifndef PARAMMANAGER_H
#define PARAMMANAGER_H
#include <QSettings>
#include <QDebug>
#include "singleton.h"
namespace ZSS {
class ParamManager {
  public:
    ParamManager();
    ParamManager(const QString&);
    ~ParamManager();
    bool loadParam(QChar&, const QString&, QChar d = 0);
    bool loadParam(int&, const QString&, int d = 0);
    bool loadParam(double&, const QString&, double d = 0);
    bool loadParam(QString&, const QString&, QString d = "");
    bool loadParam(bool&, const QString&, bool d = false);
    bool changeParam(const QString&, const QVariant&);
    bool changeParam(const QString&, const QString&, const QVariant&);
    QStringList allKeys();
    QStringList allKeys(const QString&);
    QStringList allGroups();
    QVariant value(const QString&, const QVariant& defaultValue = QVariant());
    QVariant value(const QString&, const QString&, const QVariant& defaultValue = QVariant());
    void sync();
    void clear();
  protected:
    QSettings *settings;
};
class ParamManagerZSS: public ParamManager {
  public:
    ParamManagerZSS(): ParamManager("../data/zss.ini") {}
    ~ParamManagerZSS() {}
};
class ParamManagerKickParam: public ParamManager {
  public:
    ParamManagerKickParam(): ParamManager("../data/kickparam.ini") {}
    ~ParamManagerKickParam() {}
};
class ParamManagerVisionParam: public ParamManager {
  public:
    ParamManagerVisionParam(): ParamManager("../data/visionparam.ini") {}
    ~ParamManagerVisionParam() {}
};
class ParamManagerTemp: public ParamManager {
  public:
    ParamManagerTemp(): ParamManager("../data/temp.ini") {}
    ~ParamManagerTemp() {}
};
class ParamManagerLogClip: public ParamManager {
  public:
    ParamManagerLogClip(): ParamManager("../data/logclip.ini") {}
    ~ParamManagerLogClip() {}
};
class ParamManagerPoint: public ParamManager {
  public:
    ParamManagerPoint(): ParamManager("../data/pointForMessi.ini") {}
    ~ParamManagerPoint() {}
};
class ParamManagerSim: public ParamManager{
public:
    ParamManagerSim():ParamManager("../data/zss_simulator.ini"){}
    ~ParamManagerSim(){}
};
typedef Falcon::MeyersSingleton<ParamManagerZSS> ZParamManager;
typedef Falcon::MeyersSingleton<ParamManagerKickParam> KParamManager;
typedef Falcon::MeyersSingleton<ParamManagerVisionParam> VParamManager;
typedef Falcon::MeyersSingleton<ParamManagerTemp> TParamManager;
typedef Falcon::MeyersSingleton<ParamManagerLogClip> LParamManager;
typedef Falcon::MeyersSingleton<ParamManagerPoint> PParamManager;
typedef Falcon::MeyersSingleton<ParamManagerSim> SParamManager;
}

#endif // PARAMMANAGER_H

// void QSettings::setPath(Format format, Scope scope, const QString &path)
// QSettings settings("./myapp.ini", QSettings::IniFormat);
