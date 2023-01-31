#ifndef __INTERACTION4FIELD_H__
#define __INTERACTION4FIELD_H__

#include <QObject>
#include "visionmodule.h"
#include "communicator.h"
#include "field.h"
#include "dealball.h"
class Interaction4Field : public QObject
{
    Q_OBJECT
public:
    explicit Interaction4Field(QObject *parent = 0);
    ~Interaction4Field();
    Q_INVOKABLE int getFPS(){ return VisionModule::Instance()->getFPS();}
    Q_INVOKABLE int getRBKFPS(int team){ return ZCommunicator::Instance()->getFPS(team); }
    Q_INVOKABLE double getBallVelocity() {
        return DealBall::Instance()->getBallSpeed();
    }
    Q_INVOKABLE void setArea(int a,int b,int c,int d);
    Q_INVOKABLE void resetArea();
//    Q_INVOKABLE void moveField(int,int);
    Q_INVOKABLE void setSize(int,int);
//    Q_INVOKABLE void setPlacementPoint(int,int);
    Q_INVOKABLE void setCtrlC();
    Q_INVOKABLE int getRealX(int);
    Q_INVOKABLE int getRealY(int);
//    Q_INVOKABLE void keyPress(QKeyEvent* event);
//    Q_INVOKABLE void keyRelease(QKeyEvent* event);
    Q_INVOKABLE void robotControl(int, int);
    Q_INVOKABLE void singleRobotControl(int, int);
    Q_INVOKABLE void saveFormation();
    void generateFormationJson(QJsonDocument& jsonDoc);
    Q_INVOKABLE static void readFormationJson(QString);
    Q_INVOKABLE static QStringList getFormationFileName();
    Q_INVOKABLE QString getMenubar_CrtFile() const {return menubar_crt_file;}
    Q_INVOKABLE static QStringList getLayoutFileName();
    Q_INVOKABLE QString setLayoutFileName();
    Q_INVOKABLE void setCurrentLayout(QString text) { lastLayout = text; qDebug() << "Current Layout is " << text; }
    Q_INVOKABLE QString getLastLayout() const { return lastLayout; }
    Q_INVOKABLE QString getLayoutPath() { return qApp->applicationDirPath() + "/../Layout/"; }
private:
    static QString menubar_crt_file;
    QString lastLayout;
Q_SIGNALS:
    void moveFieldSignal(int,int);
signals:
public slots:
};

#endif // __INTERACTION4FIELD_H__
