#include "dealrobot.h"
#include "globaldata.h"
#include "matrix2d.h"
#include "field.h"
#include <iostream>
#include <qdebug.h>
#include <functional>
#include <algorithm>
#include <cmath>
#include <QTime>
namespace {
auto opm = Owl::OParamManager::Instance();
auto vpm = Owl::VParamManager::Instance();
int DIFF_VECHILE_MAX_DIFF = 600;//1000
float MAX_SPEED[PARAM::ROBOTMAXID] = {6000,6000,6000,6000,6000,6000};
float MAX_ROTATION_SPEED[PARAM::ROBOTMAXID] = {15,5,5,5,5,5};
float MAX_ACCELERATE[PARAM::ROBOTMAXID] = {29000,0,-1000,4000,30000,30000};
// 由于图像的一次事故，帧率和系统延时改变了
const double TOTAL_MOV_LATED_FRAME = 4.0f; //平移的延时(原来为4.2)
const int NUM_MOV_LATENCY_FRAMES = static_cast<int>(TOTAL_MOV_LATED_FRAME);
const float MOV_LATENCY_FRACTION  = TOTAL_MOV_LATED_FRAME - static_cast<float>(NUM_MOV_LATENCY_FRAMES);

const double TOTAL_DIR_LATED_FRAME = 2.0f; //转动的延时
const int NUM_DIR_LATENCY_FRAMES = static_cast<int>(TOTAL_DIR_LATED_FRAME);
const float DIR_LATENCY_FRACTION  = TOTAL_DIR_LATED_FRAME - static_cast<float>(NUM_DIR_LATENCY_FRAMES);
}

CDealRobot::CDealRobot() {
    upPossible = 0.1;
    decidePossible = vpm->carMinBelieveFrame * upPossible;
    ourDownPossible = (1.0 - decidePossible) / vpm->ourCarMaxLostFrame;
    theirDownPossible = (1.0 - decidePossible) / vpm->theirCarMaxLostFrame;
    initPosCov = 100; posMeasErr = 20; posModelErr = 0.2; 
    for (int id = 0; id < PARAM::ROBOTMAXID; id++) {
        	posFilter[PARAM::BLUE][id] = PosFilter(initPosCov, posMeasErr, posModelErr);
        	posFilter[PARAM::YELLOW][id] = PosFilter(initPosCov, posMeasErr, posModelErr);
            //dirFilter[PARAM::BLUE][id] = PosFilter(initPosCov, posMeasErr, posModelErr);
            //dirFilter[PARAM::YELLOW][id] = PosFilter(initPosCov, posMeasErr, posModelErr);
            dirFilter[PARAM::BLUE][id] = DirFilter(initPosCov, posMeasErr, posModelErr);
            dirFilter[PARAM::YELLOW][id] = DirFilter(initPosCov, posMeasErr, posModelErr);
            lastValid[PARAM::BLUE][id] = 1 / getFPS();
            lastValid[PARAM::YELLOW][id] = 1 / getFPS();
            visionProblem[PARAM::BLUE][id] = false;
            visionProblem[PARAM::YELLOW][id] = false;
    }
}

double CDealRobot::posDist(CGeoPoint pos1, CGeoPoint pos2) {
    return std::sqrt((pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) + (pos1.y() - pos2.y()) * ((pos1.y() - pos2.y())));
}

bool CDealRobot::isValidInfo(Owl::Robot robot) {
    if (abs(robot.pos.x()) < opm->field_length / 2 + opm->extendLength && abs(robot.pos.y()) < opm->field_width / 2 + opm->extendLength && fabs(robot.angle) <= 10)
        return true;
    else
        return false;
}

double CDealRobot::calculateWeight(int camID, CGeoPoint roboPos) {
    Owl::SingleCamera camera = GlobalData::Instance()->cameraMatrix[camID];
    if (roboPos.x() > camera.leftedge.max && roboPos.x() < camera.rightedge.max &&
            roboPos.y() > camera.downedge.max && roboPos.y() < camera.upedge.max)
        return 1;
    else if (roboPos.x() < camera.leftedge.max && roboPos.x() > camera.leftedge.min)
        return abs(roboPos.x() - camera.leftedge.min) / abs(camera.leftedge.max - camera.leftedge.min);
    else if (roboPos.x() > camera.rightedge.max && roboPos.x() < camera.rightedge.min)
        return abs(roboPos.x() - camera.rightedge.min) / abs(camera.rightedge.max - camera.rightedge.min);
    else if (roboPos.y() < camera.downedge.max && roboPos.y() > camera.downedge.min)
        return abs(roboPos.y() - camera.downedge.min) / abs(camera.downedge.max - camera.downedge.min);
    else if (roboPos.y() > camera.upedge.max && roboPos.y() < camera.upedge.min)
        return abs(roboPos.y() - camera.upedge.min) / abs(camera.upedge.max - camera.upedge.min);
    else return 0.0001;//to deal with can see out of border situation
}

void CDealRobot::init() {
    result.init();
    FPS = getFPS();

    for (int roboId = 0; roboId < PARAM::ROBOTMAXID; roboId++)
        for (int camId = 0; camId < opm->total_cameras; camId++) {
            robotSeqence[PARAM::BLUE][roboId][camId].fill(-1, -1, -32767, -32767, 0);
            robotSeqence[PARAM::YELLOW][roboId][camId].fill(-1, -1, -32767, -32767, 0);
        }         
    for (int i = 0; i < opm->total_cameras; i++) {
        if(GlobalData::Instance()->cameraUpdate[i]) {
            for (int j = 0; j < GlobalData::Instance()->camera[i][0].robotSize[PARAM::BLUE]; j++) {
                Owl::Robot robot = GlobalData::Instance()->camera[i][0].robot[PARAM::BLUE][j];
                if (GlobalData::Instance()->robotPossible[PARAM::BLUE][robot.id] < decidePossible)
                    //当这是新车的时候//
                    robotSeqence[PARAM::BLUE][robot.id][i] = robot;
                else if  (lastRobot[PARAM::BLUE][robot.id].pos.dist(robot.pos) < DIFF_VECHILE_MAX_DIFF)
                    robotSeqence[PARAM::BLUE][robot.id][i] = robot;
            }
            for (int j = 0; j < GlobalData::Instance()->camera[i][0].robotSize[PARAM::YELLOW]; j++) {
                Owl::Robot robot = GlobalData::Instance()->camera[i][0].robot[PARAM::YELLOW][j];
                if (GlobalData::Instance()->robotPossible[PARAM::YELLOW][robot.id] < decidePossible)
                    robotSeqence[PARAM::YELLOW][robot.id][i] = robot;
                else if  (lastRobot[PARAM::YELLOW][robot.id].pos.dist(robot.pos) < DIFF_VECHILE_MAX_DIFF)
                    robotSeqence[PARAM::YELLOW][robot.id][i] = robot;
            }
        }
    }
    for (int i = 0; i < PARAM::ROBOTMAXID - 1; i++) {
        Owl::Robot temp(-1, -32767, -32767, 0, -1);
        sortTemp[PARAM::BLUE][i] = temp;
        sortTemp[PARAM::YELLOW][i] = temp;
    }
}

void CDealRobot::mergeRobot() {
    for (int roboId = 0; roboId < PARAM::ROBOTMAXID; roboId++) {
        bool foundBlue = false, foundYellow = false;
        double blueWeight = 0, yellowWeight = 0;
        CGeoPoint blueAverage(0, 0), yellowAverage(0, 0);
        Owl::RawInfo br, yr;
        double blueAngle = 0, yellowAngle = 0;
        for (int camId = 0; camId < opm->total_cameras; camId++) {
            double _weight = 0;
            if(robotSeqence[PARAM::BLUE][roboId][camId].pos.x() > -30000 && robotSeqence[PARAM::BLUE][roboId][camId].pos.y() > -30000) {
                foundBlue = true;
                _weight = calculateWeight(camId, robotSeqence[PARAM::BLUE][roboId][camId].pos);
                blueWeight += _weight;
                blueAverage.setX(blueAverage.x() + robotSeqence[PARAM::BLUE][roboId][camId].pos.x() * _weight);
                
                blueAverage.setY(blueAverage.y() + robotSeqence[PARAM::BLUE][roboId][camId].pos.y() * _weight);
                br.fill(robotSeqence[PARAM::BLUE][roboId][camId].raw);
                blueAngle = robotSeqence[PARAM::BLUE][roboId][camId].angle;
                //blueAngle += robotSeqence[PARAM::BLUE][roboId][camId].angle * _weight;
            }
            _weight = 0;
            if(robotSeqence[PARAM::YELLOW][roboId][camId].pos.x() > -30000 && robotSeqence[PARAM::YELLOW][roboId][camId].pos.y() > -30000) {
                foundYellow = true;
                _weight = calculateWeight(camId, robotSeqence[PARAM::YELLOW][roboId][camId].pos);
                yellowWeight += _weight;
                yellowAverage.setX(yellowAverage.x() + robotSeqence[PARAM::YELLOW][roboId][camId].pos.x() * _weight);
                yellowAverage.setY(yellowAverage.y() + robotSeqence[PARAM::YELLOW][roboId][camId].pos.y() * _weight);
                yr.fill(robotSeqence[PARAM::YELLOW][roboId][camId].raw);
                yellowAngle = robotSeqence[PARAM::YELLOW][roboId][camId].angle;
                //yellowAngle += robotSeqence[PARAM::YELLOW][roboId][camId].angle * _weight;
            }
        }
        if (foundBlue) { 
            Owl::Robot ave(PARAM::BLUE, blueAverage.x() / blueWeight, blueAverage.y() / blueWeight, blueAngle, roboId, br);
            result.addRobot(ave);
        }
        if (foundYellow) {
            Owl::Robot ave(PARAM::YELLOW, yellowAverage.x() / yellowWeight, yellowAverage.y() / yellowWeight, yellowAngle, roboId, yr);
            result.addRobot(ave);
        }
    }
}

void CDealRobot::sortRobot(int color) {
    for (int id = 0; id < PARAM::ROBOTMAXID; id++) {
        bool found = false;
        for (int i = 0; i < result.robotSize[color]; i++)
            if (result.robot[color][i].id == id ) {
                if ((isValidInfo(result.robot[color][i])) &&
                        (GlobalData::Instance()->robotPossible[color][id] < decidePossible
                         || result.robot[color][i].pos.dist(lastRobot[color][id].pos) < DIFF_VECHILE_MAX_DIFF)) {
                    currentRobot[color][id] = result.robot[color][i];
                    if (lastValid[color][id] == 0) lastValid[color][id] = 1 / FPS;
                    found = true;
                }
            }
        currentRobot[color][id].accelerate = lastRobot[color][id].accelerate;
        currentRobot[color][id].velocity.vxy = lastRobot[color][id].velocity.vxy + lastRobot[color][id].accelerate * lastValid[color][id];
        currentRobot[color][id].velocity.vr = lastRobot[color][id].velocity.vr;
        if (found)  GlobalData::Instance()->robotPossible[color][id] += upPossible;
        else { // 没看到车，猜测一个原始位置//
            currentRobot[color][id].pos = lastRobot[color][id].pos + lastRobot[color][id].velocity.vxy * lastValid[color][id] + lastRobot[color][id].accelerate * pow(lastValid[color][id], 2) / 2;
            currentRobot[color][id].angle = lastRobot[color][id].angle + lastRobot[color][id].velocity.vr * lastValid[color][id];
            currentRobot[color][id].raw = result.robot[color][id].raw; //upadte the raw vision
            if (GlobalData::Instance()->robotPossible[color][id] >= decidePossible)
                if (GlobalData::Instance()->commandMissingFrame[color] >= 20)
                    GlobalData::Instance()->robotPossible[color][id] -= theirDownPossible;
                else
                    GlobalData::Instance()->robotPossible[color][id] -= ourDownPossible;
            else GlobalData::Instance()->robotPossible[color][id] -= decidePossible;
        }
        if (GlobalData::Instance()->robotPossible[color][id] > 1.0) GlobalData::Instance()->robotPossible[color][id] = 1.0;
        if(GlobalData::Instance()->robotPossible[color][id] < 0.0)  GlobalData::Instance()->robotPossible[color][id] = 0.0;
    }
    validNum[color] = 0;
    for (int id = 0; id < PARAM::ROBOTMAXID; id++) {
        if(GlobalData::Instance()->robotPossible[color][id] >= decidePossible) {
            sortTemp[color][validNum[color]++] = currentRobot[color][id];
        }
        else if (lastValid[color][id] != 0) lastValid[color][id] += 1 / FPS;
        if (lastValid[color][id] * FPS > vpm->maxLostFrame) {
            lastValid[color][id] = 0;
        }
        if (lastValid[color][id] * FPS > vpm->ourCarMaxLostFrame) visionProblem[color][id] = true;
        else visionProblem[color][id] = false;
    }
    //sort
    for (int i = 0; i < validNum[color] - 1; i++) {
        int maxj = i;
        for (int j = i + 1; j < validNum[color]; j++)
            if (GlobalData::Instance()->robotPossible[color][sortTemp[color][maxj].id] <
                    GlobalData::Instance()->robotPossible[color][sortTemp[color][j].id]) maxj = j;
        if (maxj != i) {
            Owl::Robot temp;
            temp = sortTemp[color][maxj];
            sortTemp[color][maxj] = sortTemp[color][i];
            sortTemp[color][i] = temp;
        }
    }
}

void CDealRobot::run() {
    init();
    mergeRobot();
    sortRobot(PARAM::BLUE);
    sortRobot(PARAM::YELLOW);
    result.init();
    //重新加入概率排序后的车
    for (int i = 0; i < validNum[PARAM::BLUE]; i++)
        result.addRobot(sortTemp[PARAM::BLUE][i]);
    for (int i = 0; i < validNum[PARAM::YELLOW]; i++)
        result.addRobot(sortTemp[PARAM::YELLOW][i]);
    //qDebug("try to push robot");
    GlobalData::Instance()->processRobot.push(result);
    //t1 = QTime::currentTime();
    //double dt = VisionModule::Instance()->t.msecsTo(t1);
    //qDebug()<<"camera to proccess"<<dt;
}

void CDealRobot::updateVel(int team, Owl::ReceiveVisionMessage& result) {
    
    for (int i = 0; i < validNum[team]; i++) {
        Owl::Robot & robot = result.robot[team][i];
        //朝向滤波
        auto &playerRotVel = dirFilter[team][robot.id];
        if(!playerRotVel.isInit()) {
            playerRotVel.initState(robot.angle, robot.velocity.vr);
        }

        playerRotVel.setTransitionMat(lastValid[team][robot.id]);
        //playerPosVel.predict2(lastRobot[team][robot.id].accelerate);
        double dir = playerRotVel.postEstimatedDir();
        playerRotVel.predict();
        playerRotVel.set(0, dir);
        playerRotVel.update2(robot.angle);

        double filterDir = playerRotVel.postEstimatedDir();
        double rotVel = playerRotVel.postEstimatedVel();

        robot.angle = filterDir;
        //robot.angle = playerRotVel.normalize(robot.angle);
        //playerRotVel.set(0, robot.angle);
        robot.velocity.vr = rotVel;
        if(abs(robot.velocity.vr) > MAX_ROTATION_SPEED[robot.id]) {
            robot.velocity.vr = robot.velocity.vr > 0? MAX_ROTATION_SPEED[robot.id] : MAX_ROTATION_SPEED[robot.id] * (-1);
            playerRotVel.set(1, robot.velocity.vr);
        }

        //位置滤波
        auto & playerPosVel = posFilter[team][robot.id];
        if(!playerPosVel.isInit()) {
            playerPosVel.initState(robot.pos, robot.velocity.vxy);
        }
        
        playerPosVel.setTransitionMat(lastValid[team][robot.id]);
        if(lastValid[team][robot.id] != 1 / FPS) lastValid[team][robot.id] = 1 / FPS;

        //robot.velocity.vxy = (robot.pos - GlobalData::Instance()->maintain[0].robot[team][robot.id].pos) / lastValid[team][robot.id];
        robot.velocity.vxy = GlobalData::Instance()->robotCommand[team][0].robotSpeed[robot.id].vxy;
        robot.accelerate = (robot.velocity.vxy - lastRobot[team][robot.id].velocity.vxy) / lastValid[team][robot.id];
        /**if(robot.velocity.vxy.mod() + vpm->thresholdToDec < lastRobot[team][robot.id].velocity.vxy.mod()) {
            if(robot.accelerate.mod() > vpm->deceleration) {
                double sin = robot.accelerate.x() / robot.accelerate.mod(), cos = robot.accelerate.y() / robot.accelerate.mod();
                robot.accelerate = CVector(sin, cos) * vpm->deceleration;
            }
        }
        else {**/
            //robot.velocity.vxy = (robot.pos - GlobalData::Instance()->maintain[0].robot[team][robot.id].pos) / lastValid[team][robot.id];
            //robot.accelerate = (robot.velocity.vxy - lastRobot[team][robot.id].velocity.vxy) / lastValid[team][robot.id];
            if(robot.accelerate.mod() > vpm->acceleration) {
                double sin = robot.accelerate.x() / robot.accelerate.mod(), cos = robot.accelerate.y() / robot.accelerate.mod();
                robot.accelerate = CVector(sin, cos) * vpm->acceleration;
            }
        //}
            /**if(robot.velocity.vxy.mod() > lastRobot[team][robot.id].velocity.vxy.mod() + vpm->thresholdToAcc) {
                if(robot.accelerate.mod() > vpm->acceleration) {
                    double sin = robot.accelerate.x() / robot.accelerate.mod(), cos = robot.accelerate.y() / robot.accelerate.mod();
                    robot.accelerate = CVector(sin, cos) * vpm->acceleration;
                }
            }
        else robot.accelerate = CVector(0, 0);**/

        //playerPosVel.predict2(lastRobot[team][robot.id].accelerate);
        playerPosVel.predict2(robot.accelerate);
        //playerPosVel.predict();
        playerPosVel.update2(robot.pos);
        
        CGeoPoint filtPoint = playerPosVel.postEstimatedPos();
        CVector PlayVel = playerPosVel.postEstimatedVel();

        robot.pos = filtPoint;
        robot.velocity.vxy = PlayVel;
        if(robot.velocity.vxy.mod() > MAX_SPEED[robot.id]) {
            double sin = robot.velocity.vx() / robot.velocity.vxy.mod(), cos = robot.velocity.vy() / robot.velocity.vxy.mod();
            robot.velocity.vxy = CVector(sin, cos) * MAX_SPEED[robot.id];
            playerPosVel.set(2, (robot.velocity.vx()+GlobalData::Instance()->robotCommand[team][0].robotSpeed[robot.id].vx())/2);
            playerPosVel.set(3, (robot.velocity.vy()+GlobalData::Instance()->robotCommand[team][0].robotSpeed[robot.id].vy())/2);
        }

        historyVel[team][robot.id].push(PlayVel);

        const int size = 5;
        double v[size], v_angle[size];
        int ii = 0;
        for (ii = 0; ii < size; ii++) {
            //if (GlobalData::Instance()->maintain.size() < ii) break;
            CVector vxy = historyVel[team][robot.id][-ii];
            v[ii] = vxy.mod();
            v_angle[ii] = atan2(vxy.y(), vxy.x());
        }
        sort(v,v+ii,std::greater<double>());
        robot.velocity.vxy = CVector(v[ii/2]*std::cos(v_angle[0]), v[ii/2]*std::sin(v_angle[0]));

        /**if (fabs(robot.angle) > 10) {
            playerRotVel = DirFilter(initPosCov, posMeasErr, posModelErr);
            robot.angle = 0;
            robot.velocity.vr = 0;
            //lastValid[team][robot.id] += 1 / FPS;
        }
        if (abs(robot.pos.x()) > opm->field_length / 2 + opm->extendLength && abs(robot.pos.y()) > opm->field_width / 2 + opm->extendLength) {
            playerPosVel = PosFilter(initPosCov, posMeasErr, posModelErr);
            robot.pos = CGeoPoint(-32767, -32767);
            lastRobot[team][robot.id].pos = CGeoPoint(0, 0);
            robot.velocity.vxy = CVector(0,0);
            robot.accelerate = CVector(0,0);
            //lastValid[team][robot.id] += 1 / FPS;
        }
        else {
            lastRobot[team][robot.id].pos = robot.pos;
        }
        lastRobot[team][robot.id].angle = robot.angle;
        lastRobot[team][robot.id].velocity = robot.velocity;
        lastRobot[team][robot.id].accelerate = robot.accelerate;**/
        if (!isValidInfo(robot)) {
            playerRotVel = DirFilter(initPosCov, posMeasErr, posModelErr);
            playerPosVel = PosFilter(initPosCov, posMeasErr, posModelErr);
            robot.fill(-1, -1, -32767, -32767, 0, robot.raw);
            lastRobot[team][robot.id].fill(-1, -1, 0, 0, 0);
        }
        else lastRobot[team][robot.id] = robot;
        //lastRobot[team][robot.id].accelerate = (GlobalData::Instance()->robotCommand[team][0].robotSpeed[robot.id].vxy - lastRobot[team][robot.id].velocity.vxy) / lastValid[team][robot.id];
    }
}
