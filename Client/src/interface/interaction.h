#ifndef __INTERACTION_H__
#define __INTERACTION_H__

#include <QObject>
#include "staticparams.h"
#include "parammanager.h"
#include "actionmodule.h"
class Interaction : public QObject {
    Q_OBJECT
  public:
    explicit Interaction(QObject *parent = nullptr);
    ~Interaction();
    
    //Q_INVOKABLE void chooseRBKpath(int);
    //Q_INVOKABLE QString getRBKpath(int team) { return RBKpath[team]; }
    //Q_INVOKABLE void chooseSIMpath();
    //Q_INVOKABLE QString getSIMpath() { return SIMpath; }
    //Q_INVOKABLE void chooseCraypath();
    //Q_INVOKABLE QString getCraypath() { return Craypath; }
    Q_INVOKABLE bool controlBlueRBK(bool);
    Q_INVOKABLE bool controlYellowRBK(bool);
    Q_INVOKABLE bool controlSim(bool,bool);
    //Q_INVOKABLE bool controlCray(bool);
    Q_INVOKABLE bool controlMonitor(bool);
    Q_INVOKABLE bool changeRBKSettings(bool, bool);
    Q_INVOKABLE bool connectRadio(bool,int,int);
    Q_INVOKABLE bool connectSim(bool,int);
    Q_INVOKABLE void kill(bool);
    Q_INVOKABLE void controlProcess(int, bool);

    Q_INVOKABLE int  getCameraMaxNumber() { return PARAM::CAMERA; }
    Q_INVOKABLE int  getCameraNumber() { return Owl::OParamManager::Instance()->total_cameras; }
    Q_INVOKABLE void controlCamera(int, bool);
    Q_INVOKABLE void setVision(bool, bool);

    Q_INVOKABLE static void setRecorder(bool);
    Q_INVOKABLE void setRecorderCut(bool);
    Q_INVOKABLE void setRecordRawVision(bool);
    Q_INVOKABLE void setPlayerRawVision(bool);
    //Q_INVOKABLE bool chooseLogToPlay();
    Q_INVOKABLE void setIfEdgeTest(bool);
    Q_INVOKABLE void setTestMode(bool isTesting, bool runTestingScripts);

    Q_INVOKABLE void getBasicInfo();
    Q_INVOKABLE void getMoreInfo();
    //Q_INVOKABLE void showCurrentGrade(int);
    //Q_INVOKABLE void setChallengeMode(int);
    //Q_INVOKABLE void endChallenge();
    //Q_INVOKABLE void showCurrentProgress();
    //Q_INVOKABLE void startTimer();
    //Q_INVOKABLE void createGameRecorder();
    //Q_INVOKABLE void stopGameRecorder();

    Q_INVOKABLE QStringList getInterfaces();
    Q_INVOKABLE void updateInterfaces();
    Q_INVOKABLE void changeVisionInterface(int);
    Q_INVOKABLE void changeGrsimInterface(int);
    Q_INVOKABLE QStringList getGrsimInterfaces();
    
    Q_INVOKABLE bool connectSerialPort(bool);
    Q_INVOKABLE bool changeSerialFrequency(int);
    Q_INVOKABLE bool changeSerialPort(int);
    Q_INVOKABLE QStringList getSerialPortsList();
    Q_INVOKABLE int getFrequency();
    Q_INVOKABLE int getMaxFrequency();
    Q_INVOKABLE QStringList getFrequencyList();
    Q_INVOKABLE void updateCommandParams(int, int, int, int, bool, int, int, bool, int);
    Q_INVOKABLE bool sendCommand(int);
    Q_INVOKABLE bool getInfrared(int);

    Q_INVOKABLE void startRecordCommands(bool);

    Q_INVOKABLE void updatePlayList();
    Q_INVOKABLE QStringList getPlayList();
    Q_INVOKABLE void changeReadyPlay(int);
    Q_INVOKABLE void defineScriptsSetting();

private:
    QString RBKpath[PARAM::TEAMS];
    QString RBKdirectory[PARAM::TEAMS];
    QString SIMpath;
    QString SIMdirectory;
    //QString Craypath;
    //QString Craydirectory;

public slots:

};

#endif // __INTERACTION_H__
