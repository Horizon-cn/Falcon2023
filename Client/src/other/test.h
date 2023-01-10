//2021年中国赛备赛用于调试视觉滤波算法
#ifndef TEST_H
#define TEST_H

#include <QObject>
#include "singleton.h"
#include <QTime>

class CTest : public QObject
{
    Q_OBJECT
public:

    explicit CTest(QObject *parent = nullptr);
    ~CTest();

    //for state estimation debug
    bool testing = false, start = false, changed = true;
    //bool runScripts = true;
    QTime t0, t1, t2;
    //QString lastState = "run0";
    //float noise = 0, vanish = 0;
    //int lastcnt=-2, cnt = -1;
    int file_num, current_file_num;
    //double max_ballSpeed, min_ballSpeed;
    //int state = 1;
    void setMode(bool, bool);
    //void judgeStateMachine(QString);
    //void setNoise();
    //void storeTestingData();    //for state estimation
    //void storeTestingDataV1();
    void storeTestingDataV2();
    void writeToFile(bool, double);
    void writeDataInfo();

signals:

public slots:
};

typedef Falcon::MeyersSingleton<CTest> Test;
#endif // TEST_H
