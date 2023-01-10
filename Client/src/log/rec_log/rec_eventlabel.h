#ifndef REC_EVENTLABEL_H
#define REC_EVENTLABEL_H
#include <QObject>
#include <QQmlEngine>
#include <QFile>
#include <QList>
#include <fstream>
#include <geometry.h>
#include "singleton.h"
#include "zss_rec.pb.h"
#include "staticparams.h"
namespace {
struct ball {
    CGeoPoint pos;
    CVector vel;
    int camera_id;
    bool valid = false;
};
struct robot {
    CGeoPoint pos;
    CVector vel;
    CVector dir;
    double dirvel;
    int camera_id;
    bool valid = false;
};
struct frame {
    QList<ball> ballList;
    QList<robot> botList[PARAM::TEAMS][PARAM::ROBOTMAXID];
    ball realBall;
    robot bot[PARAM::TEAMS][PARAM::ROBOTMAXID];
    qint64 timestamp;
    int state = 0;
    int possessBallRobotID = -1;
};
}
class RecEventLabel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString logName READ rlogName WRITE setlogName NOTIFY logNamechanged)
public:
    explicit RecEventLabel(QObject *parent = nullptr);
    ~RecEventLabel();
    static QObject* Instance(QQmlEngine* engine = nullptr, QJSEngine* scriptEngine = nullptr){
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        static RecEventLabel* Instance = new RecEventLabel();
        return Instance;
    }
    Q_INVOKABLE void loadFile(QString filename);
    Q_INVOKABLE QString logName = "No log is loaded.";
    Q_INVOKABLE bool processLabel();
    QString rlogName() {
        return logName;
    }
    void setlogName(QString slogName) {
        logName = slogName;
        emit logNamechanged();
    }
    QFile* replayFile;
    ZSS::Protocol::RecMessages recMsgs;
    int startFrame = 0, endFrame = 0, camNum = 0;
signals:
    void logNamechanged();
private:
    void saveLabel();
    void processMessage();
    void parseDetection(const ZSS::Protocol::RecMessages&);
    void parseDetection(const ZSS::Protocol::RecMessage&, ::frame&);
    int ballInMouth(int,int);
    int calCamNum();
    void prepare();
    void writeToFile(QString);
    QString logTime(int);
    QList<::frame> frames;
    const int BALL_POSSESSION_BLUE = 0x01;
    const int BALL_POSSESSION_YELLOW = 0x02;
    const int BALL_POSSESSION_UNKNOWN = 0x04;
};

#endif // REC_EVENTLABEL_H
