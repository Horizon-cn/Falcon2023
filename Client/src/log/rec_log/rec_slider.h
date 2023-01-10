#ifndef REC_SLIDER_H
#define REC_SLIDER_H

#include <QObject>
#include <QQmlEngine>
#include "singleton.h"
#include "rec_player.h"

class rec_slider: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString maxTime READ rmaxTime WRITE setmaxTime NOTIFY maxTimechanged)
    Q_PROPERTY(QString durTime READ rdurTime WRITE setdurTime NOTIFY durTimechanged)
    Q_PROPERTY(QString recName READ rrecName WRITE setrecName NOTIFY recNamechanged)    
    Q_PROPERTY(double currentFrame READ rcurrentFrame WRITE setcurrentFrame NOTIFY currentFramechanged)
    Q_PROPERTY(double maximumValue READ rmaximumValue WRITE setmaximumValue NOTIFY maximumValuechanged)
    Q_PROPERTY(double stepSize READ rstepSize WRITE setstepSize NOTIFY stepSizechanged)
public:
    static QObject* Instance(QQmlEngine* engine = nullptr, QJSEngine* scriptEngine = nullptr){
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        static rec_slider* Instance = new rec_slider();
        return Instance;
    }
    explicit rec_slider(QObject* parent = nullptr);
    Q_INVOKABLE QString maxTime = "00:00.000";
    Q_INVOKABLE QString durTime = "00:00.000";
    Q_INVOKABLE QString recName = "No rec file is playing.";
    Q_INVOKABLE QString filename = " ";
    Q_INVOKABLE double maximumValue = 1;
    Q_INVOKABLE double stepSize = 1;
    Q_INVOKABLE int currentFrame = 0;
    Q_INVOKABLE void loadFile(QString filename);
    Q_INVOKABLE void toggleStopped();
    Q_INVOKABLE void setStopped(bool p);
    Q_INVOKABLE void setPlayerRate(int playerRate);
//    Q_INVOKABLE void stopRec();
    Q_INVOKABLE void seekFrame(int value);
//    Q_INVOKABLE void slowlyPlay(int value);
    Q_INVOKABLE int getMaxFrame() {return maxFrame;}
    Q_INVOKABLE QString getFilename() {return filename;}
    QString rmaxTime() {
        return maxTime;
    }
    QString rdurTime() {
        return durTime;
    }
    QString rrecName() {
        return recName;
    }
    double rmaximumValue() {
        return maximumValue;
    }
    double rstepSize() {
        return stepSize;
    }
    int rcurrentFrame() {
        return currentFrame;
    }
    void setmaxTime(QString smaxTime) {
        maxTime = smaxTime;
        emit maxTimechanged();
    }
    void setdurTime(QString sdurTime) {
        durTime = sdurTime;
        emit durTimechanged();
    }
    void setrecName(QString srecName) {
        recName = srecName;
        emit recNamechanged();
    }
    void setmaximumValue(double smaximumValue) {
        maximumValue = smaximumValue;
        emit maximumValuechanged();
    }
    void setstepSize(double sstepSize) {
        stepSize = sstepSize;
        emit stepSizechanged();
    }
    void setcurrentFrame(int scurrentFrame) {
        currentFrame = scurrentFrame;
        emit currentFramechanged();
    }
    int maxFrame = 0;
signals:
  void maxTimechanged();
  void durTimechanged();
  void recNamechanged();
  void maximumValuechanged();
  void stepSizechanged();
  void currentFramechanged();
private:
    CRecPlayer _player;
private slots:
  void updateTime(int frame);

};

typedef Falcon::MeyersSingleton<rec_slider> RecSlider;

#endif // REC_SLIDER_H
