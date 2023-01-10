/** 2021年夏令营制作，关卡设计，可以作为自动裁判盒的基础
#ifndef __GAME_H__
#define __GAME_H__

#include <QObject>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QMutex>
#include <QPainterPath>
#include <QInputDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QTime>
#include <QAxObject>
#include <singleton.h>
class CGame : public QObject {
    Q_OBJECT
public:
    CGame();
    ~CGame();
    void setChallengeMode(int);
    void endChallenge();
    void showCurrentProgress();
    void judgeBallState();
    void startTimer();
    void createGameRecorder();
    void stopGameRecorder();
    bool start;

private:
    bool isGoal();
    bool outOfBoundary();
    bool hasCrashed();
    QString getCrashedCar();
    void hasOverSpeed();
    bool hasOverHeight();
    void detectFaults();
    void report(int);
    void isTrailMode();
    void isGradeMode();
    bool setOptions();
    bool checkNewStart();
    void calGrade();
    void dealWithData();
    void writeGameInfo();
    void writeToFile();
    QTime t0;
    double delta_time;
    double param_width, param_height, param_goalWidth, param_goalDepth;
    int isGrade;
    QString formation, mode, spec_rule, recorder;
    int cur_formation, cur_speed, cur_mode, cur_rate, cur_spec_rule, cur_trail;
    double minTime, single_grade, total_grade;
    int success_num;

    double maxTime, maxDist, maxSpeed, fixDist; //s
    int formation_num, speed_num, mode_num, rate_num, spec_rule_num, trail_num;
    double basic_score[30], K_time[30], K_mode[30], K_rate[30], K_spec[30];
    double speed_mode[30];

    bool detectFault, detectCrash, detectOverSpeed, detectOverHeight;
    bool overSpeed;
    QStringList list, crashedCar, total_faults;

    int cur_recorder;
    QString filepath;
    int rowCount;

private slots:
    void OnClicked();

};
typedef Falcon::MeyersSingleton<CGame> Game;

#endif // __GAME_H__
**/