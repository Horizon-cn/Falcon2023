#include "rec_eventlabel.h"
#include "globaldata.h"
#include "parammanager.h"
#include "messages_robocup_ssl_detection.pb.h"
#include <QtEndian>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QDataStream>
#include <QTime>
#include "staticparams.h"
namespace {
    QIODevice* labelIO;
    QString labelFileName;
    QFile labelFile;
    QDataStream labelStream;
    auto opm = Owl::OParamManager::Instance();
}
RecEventLabel::RecEventLabel(QObject *parent) : QObject(parent) {}

RecEventLabel::~RecEventLabel() {
    labelIO = nullptr;
    delete labelIO;
}

void RecEventLabel::loadFile(QString filename) {
#ifdef WIN32
    filename.remove(QString("file:///"));
#else
    filename.remove(QString("file://"));
#endif
    replayFile = new QFile(filename);
    if (replayFile->open(QIODevice::ReadOnly)) {
        QIODevice* recIO;
        recIO = replayFile;
        QDataStream stream(recIO);
        QByteArray packet;
        stream >> packet;
        recMsgs.ParseFromArray(packet.data(), packet.size());
        delete replayFile;
        replayFile = nullptr;
        setlogName(filename);
    }
    if (recMsgs.recmsgs_size() <= 0){
        setlogName("Import Error File");
    }
    else{
        startFrame = camNum = 0;
        endFrame = recMsgs.recmsgs_size() - 1;
    }
}
bool RecEventLabel::processLabel() {
    prepare();
    processMessage();
    saveLabel();
    setlogName("Process Done");
    return false;
}
void RecEventLabel::prepare(){
    QDateTime datetime;
    labelFileName = QString("Label/").append(datetime.currentDateTime().toString("yyyy-MM-dd-HH-mm-ss")).append(".txt");
    labelFile.setFileName(labelFileName);
    labelFile.open(QIODevice::WriteOnly | QIODevice::Append);
    labelIO = &labelFile;
    labelStream.setDevice(labelIO);
}
void RecEventLabel::writeToFile(QString eventLabel){
    std::string str = eventLabel.toStdString();
    const char* ch = str.data();
    labelStream.writeRawData(ch,strlen(ch));
    labelStream.writeRawData("\n",1);
}
void RecEventLabel::saveLabel(){
    labelIO = nullptr;
    labelFile.close();
    recMsgs.Clear();
}
void RecEventLabel::parseDetection(const ZSS::Protocol::RecMessages& recMsgs) {
    for(int frameIndex = startFrame; frameIndex <= endFrame; frameIndex++){
        ::frame _frame;
        for(int camera = 0; camera < camNum; camera++){
            const SSL_WrapperPacket packet = recMsgs.ssl_wrapperpacket(frameIndex * camNum + camera);
            const SSL_DetectionFrame& detection = packet.detection();
            if (detection.camera_id() >= PARAM::CAMERA || detection.camera_id() < 0) {
                qDebug() << "get invalid camera id : " << detection.camera_id();
                return;
            }
            for(int i = 0; i < detection.balls_size(); i++){
                ::ball _ball;
                _ball.pos.setX(detection.balls(i).x());
                _ball.pos.setY(detection.balls(i).y());
                _frame.ballList.append(_ball);
            }
            for(int i = 0; i < detection.robots_blue_size(); i++){
                ::robot _robot;
                _robot.pos.setX(detection.robots_blue(i).x());
                _robot.pos.setY(detection.robots_blue(i).y());
                _robot.dir = CVector(std::cos(detection.robots_blue(i).orientation()), std::sin(detection.robots_blue(i).orientation()));
                _frame.botList[PARAM::BLUE][detection.robots_blue(i).robot_id()].append(_robot);
            }
            for(int i = 0; i < detection.robots_yellow_size(); i++){
                ::robot _robot;
                _robot.pos.setX(detection.robots_yellow(i).x());
                _robot.pos.setY(detection.robots_yellow(i).y());
                _robot.dir = CVector(std::cos(detection.robots_yellow(i).orientation()), std::sin(detection.robots_yellow(i).orientation()));
                _frame.botList[PARAM::YELLOW][detection.robots_yellow(i).robot_id()].append(_robot);
            }
        }
        //处理real
        double tempX, tempY;
        if(_frame.ballList.size() > 0) {
            tempX = tempY = 0;
            for (int i = 0; i < _frame.ballList.size(); i++) {
                tempX += _frame.ballList.at(i).pos.x();
                tempY += _frame.ballList.at(i).pos.y();
            }
            _frame.realBall.pos.setX((double)tempX / _frame.ballList.size());
            _frame.realBall.pos.setY((double)tempY / _frame.ballList.size());
            _frame.realBall.valid = true;
        }
        for (int id = 0; id < PARAM::ROBOTMAXID; id++) {
            if (_frame.botList[PARAM::BLUE][id].size() > 0) {
                tempX = tempY = 0;
                for (int i = 0; i < _frame.botList[PARAM::BLUE][id].size(); i++) {
                    tempX += _frame.botList[PARAM::BLUE][id].at(i).pos.x();
                    tempY += _frame.botList[PARAM::BLUE][id].at(i).pos.y();
                }
                _frame.bot[PARAM::BLUE][id].pos.setX((double)tempX / _frame.botList[PARAM::BLUE][id].size());
                _frame.bot[PARAM::BLUE][id].pos.setY((double)tempY / _frame.botList[PARAM::BLUE][id].size());
                _frame.bot[PARAM::BLUE][id].dir = _frame.botList[PARAM::BLUE][id].at(0).dir;
                _frame.bot[PARAM::BLUE][id].valid = true;
            }
            if (_frame.botList[PARAM::YELLOW][id].size() > 0) {
                tempX = tempY = 0;
                for (int i = 0; i < _frame.botList[PARAM::YELLOW][id].size(); i++) {
                    tempX += _frame.botList[PARAM::YELLOW][id].at(i).pos.x();
                    tempY += _frame.botList[PARAM::YELLOW][id].at(i).pos.y();
                }
                _frame.bot[PARAM::YELLOW][id].pos.setX((double)tempX / _frame.botList[PARAM::YELLOW][id].size());
                _frame.bot[PARAM::YELLOW][id].pos.setY((double)tempY / _frame.botList[PARAM::YELLOW][id].size());
                _frame.bot[PARAM::YELLOW][id].dir = _frame.botList[PARAM::YELLOW][id].at(0).dir;
                _frame.bot[PARAM::YELLOW][id].valid = true;
            }
        }
        frames.push_back(_frame);
    }
}
void RecEventLabel::parseDetection(const ZSS::Protocol::RecMessage& recMsg, ::frame& _frame) {
    for (int i = 0 ; i < recMsg.maintainvision().balls().size(); i++) {
        ::ball _ball;
        //_ball.camera_id = detection.camera_id();
        _ball.pos.setX(recMsg.maintainvision().balls().ball(i).posx());
        _ball.pos.setY(recMsg.maintainvision().balls().ball(i).posy());
        _frame.ballList.append(_ball);
    }
    for(int color = PARAM::BLUE; color <= PARAM::YELLOW; color++) {
        for (int i = 0; i < recMsg.maintainvision().processmsg(color).size(); i++) {
            ::robot _robot;
            //_robot.camera_id = detection.camera_id();
            _robot.pos.setX(recMsg.maintainvision().processmsg(color).robot(i).posx());
            _robot.pos.setY(recMsg.maintainvision().processmsg(color).robot(i).posy());
            _robot.dir = CVector(std::cos(recMsg.maintainvision().processmsg(color).robot(i).angle()), std::sin(recMsg.maintainvision().processmsg(color).robot(i).angle()));
            _frame.botList[color][recMsg.maintainvision().processmsg(color).robot(i).id()].append(_robot);
//          qDebug() << detection.robots_blue(i).robot_id() << _robot.dir.x() << _robot.dir.y() << _robot.dir.mod();
        }
    }
    //处理real
    double tempX, tempY;
    if(_frame.ballList.size() > 0) {
        tempX = tempY = 0;
        for (int i = 0; i < _frame.ballList.size(); i++) {
            tempX += _frame.ballList.at(i).pos.x();
            tempY += _frame.ballList.at(i).pos.y();
        }
        _frame.realBall.pos.setX((double)tempX / _frame.ballList.size());
        _frame.realBall.pos.setY((double)tempY / _frame.ballList.size());
        _frame.realBall.valid = true;
    }
    for (int id = 0; id < PARAM::ROBOTMAXID; id++) {
        if (_frame.botList[PARAM::BLUE][id].size() > 0) {
            tempX = tempY = 0;
            for (int i = 0; i < _frame.botList[PARAM::BLUE][id].size(); i++) {
                tempX += _frame.botList[PARAM::BLUE][id].at(i).pos.x();
                tempY += _frame.botList[PARAM::BLUE][id].at(i).pos.y();
            }
            _frame.bot[PARAM::BLUE][id].pos.setX((double)tempX / _frame.botList[PARAM::BLUE][id].size());
            _frame.bot[PARAM::BLUE][id].pos.setY((double)tempY / _frame.botList[PARAM::BLUE][id].size());
            _frame.bot[PARAM::BLUE][id].dir = _frame.botList[PARAM::BLUE][id].at(0).dir;
            _frame.bot[PARAM::BLUE][id].valid = true;
        }
        if (_frame.botList[PARAM::YELLOW][id].size() > 0) {
            tempX = tempY = 0;
            for (int i = 0; i < _frame.botList[PARAM::YELLOW][id].size(); i++) {
                tempX += _frame.botList[PARAM::YELLOW][id].at(i).pos.x();
                tempY += _frame.botList[PARAM::YELLOW][id].at(i).pos.y();
            }
            _frame.bot[PARAM::YELLOW][id].pos.setX((double)tempX / _frame.botList[PARAM::YELLOW][id].size());
            _frame.bot[PARAM::YELLOW][id].pos.setY((double)tempY / _frame.botList[PARAM::YELLOW][id].size());
            _frame.bot[PARAM::YELLOW][id].dir = _frame.botList[PARAM::YELLOW][id].at(0).dir;
            _frame.bot[PARAM::YELLOW][id].valid = true;
        }
    }
}
void RecEventLabel::processMessage() {
    int _frameDuration;
    frames.clear();

    //每帧读入原始视觉信息
    camNum = camNum == 0? calCamNum() : camNum;
    parseDetection(recMsgs); //read vision
    _frameDuration = endFrame - startFrame + 1;
    /**for (int frameGroupIndex = startFrame; frameGroupIndex <= endFrame ; frameGroupIndex++) {
        //每帧读入处理好的视觉信息
        ::frame _frame;
        parseDetection(recMsgs.recmsgs(frameGroupIndex), _frame); //read vision
        frames.push_back(_frame);
        _frameDuration = endFrame - startFrame + 1;
    }**/
    //compute Vel
    int deltaD, deltaI;
    for (int frameIndex = 0; frameIndex < _frameDuration ; frameIndex++) {
        if (frames.at(frameIndex).realBall.valid) {
            for (deltaD = 0; deltaD >= -3; deltaD--)
                if (frameIndex + deltaD < 0 || !frames.at(frameIndex + deltaD).realBall.valid)
                    break;
            deltaD++;
            for (deltaI = 0; deltaI <= 3; deltaI++)
                if (frameIndex + deltaI >= _frameDuration || !frames.at(frameIndex + deltaI).realBall.valid)
                    break;
            deltaI--;
            CVector _vel = (frames.at(frameIndex + deltaD).realBall.pos - frames.at(frameIndex + deltaI).realBall.pos)
                           / (deltaI - deltaD);
            frames[frameIndex].realBall.vel = _vel;
//            qDebug() << "Current position" << frames.at(frameIndex).realBall.pos.x() << frames.at(frameIndex).realBall.pos.y();
//            qDebug() << "Current frame" << logTime(frameIndex + startFrame) << _vel.x() << _vel.y() << "within" << deltaI - deltaD << "frames";
        } else {
//            qDebug() << "Current frame" << frameIndex + startFrame << "has no BAll";
        }
    }
    //BallPossession
    int ballinBlue = -1, ballinYellow = -1, inPossession = -1;
    double BlueBallPossessionEvents = 0, YellowBallPossessionEvents = 0, BallConflictEvents = 0;
    writeToFile("BALL POSSESSION");
    for (int frameIndex = 0; frameIndex < _frameDuration ; frameIndex++) {
        ballinBlue = ballInMouth(PARAM::BLUE, frameIndex); //考虑是否在没有球视觉时也判断
        ballinYellow =  ballInMouth(PARAM::YELLOW, frameIndex);
        if (ballinBlue >= 0 && ballinYellow >= 0) {
            //争球，球被看到：极少情况/几乎没有
            if(inPossession != -2){
                writeToFile(logTime(frameIndex + startFrame) + " has conflict");
                inPossession = -2; //conflict
            }
            frames[frameIndex].state |= BALL_POSSESSION_UNKNOWN;
        } else if (frames[frameIndex].realBall.valid) {
            //看得到球
            if(ballinBlue >= 0) {
                if(ballinBlue != inPossession){
                    writeToFile(logTime(frameIndex + startFrame) + " BLUE IN " + QString::number(ballinBlue));
                    inPossession = ballinBlue;
                }
                frames[frameIndex].possessBallRobotID = ballinBlue;
                frames[frameIndex].state |= BALL_POSSESSION_BLUE;
                BlueBallPossessionEvents++;
            } else if (ballinYellow >= 0) {
                if(ballinYellow + PARAM::ROBOTMAXID != inPossession){
                    writeToFile(logTime(frameIndex + startFrame) + " YELLOW IN " + QString::number(ballinYellow));
                    inPossession = PARAM::ROBOTMAXID + ballinYellow;
                }
                frames[frameIndex].possessBallRobotID = ballinYellow;
                frames[frameIndex].state |= BALL_POSSESSION_YELLOW;
                YellowBallPossessionEvents++;
            } else {
                if(inPossession != -3){
                    writeToFile(logTime(frameIndex + startFrame) + " has a free ball");
                    inPossession = -3; //free ball
                }
                frames[frameIndex].state |= BALL_POSSESSION_UNKNOWN;
            }
        } else if (!frames[frameIndex].realBall.valid) {
            //看不见球，怀疑有车近身带球
            if (inPossession >= 0) {
                if (inPossession < PARAM::ROBOTMAXID) {
                    //writeToFile(logTime(frameIndex + startFrame) + " BLUE IN " + QString::number(inPossession));
                    frames[frameIndex].possessBallRobotID = inPossession;
                    frames[frameIndex].state |= BALL_POSSESSION_BLUE;
                    BlueBallPossessionEvents++;
                } else {
                    //writeToFile(logTime(frameIndex + startFrame) + " YELLOW IN " + QString::number(inPossession - PARAM::ROBOTMAXID));
                    frames[frameIndex].possessBallRobotID = inPossession - PARAM::ROBOTMAXID;
                    frames[frameIndex].state |= BALL_POSSESSION_YELLOW;
                    YellowBallPossessionEvents++;
                }
            } else {
                // 视觉丢失，或是在争球
                if(inPossession != -4){
                    writeToFile(logTime(frameIndex + startFrame) + " has no vision of ball");
                    inPossession = -4;
                }
                frames[frameIndex].state |= BALL_POSSESSION_UNKNOWN;
            }
        }
    }
    double BlueBallPossessionRate = BlueBallPossessionEvents / (BlueBallPossessionEvents + YellowBallPossessionEvents) * 100;
    double YellowBallPossessionRate = 100 - BlueBallPossessionRate;
    //Dribbling
    CGeoPoint startDribblingPoint;
    bool isDribbling = false;
    int DribblingEvents = 0;
    writeToFile(" ");writeToFile("Dribbling");
    for (int frameIndex = 0; frameIndex < _frameDuration ; frameIndex++) {
        if (!isDribbling) {
            //还没吸球
            if (frames[frameIndex].realBall.valid && (frames[frameIndex].state & BALL_POSSESSION_BLUE)) {
                isDribbling = true;
                startDribblingPoint = frames[frameIndex].realBall.pos;
            } else if(frames[frameIndex].realBall.valid && (frames[frameIndex].state & BALL_POSSESSION_YELLOW)) {
                isDribbling = true;
                startDribblingPoint = frames[frameIndex].realBall.pos;
            }
        } else {
            //吸球状态
            if (frames[frameIndex].state & BALL_POSSESSION_UNKNOWN) {
                isDribbling = false;
            } else if(frames[frameIndex].realBall.valid &&
                      startDribblingPoint.dist(frames[frameIndex].realBall.pos) >= 1000.0) {
                if (frames[frameIndex].state & BALL_POSSESSION_BLUE)
                    writeToFile(logTime(frameIndex + startFrame)+" BLUE "+QString::number(frames[frameIndex].possessBallRobotID)+" at ("+QString::number(frames[frameIndex].realBall.pos.x())+","+QString::number(frames[frameIndex].realBall.pos.y())+") with dist of "+QString::number(startDribblingPoint.dist(frames[frameIndex].realBall.pos)));
                else
                    writeToFile(logTime(frameIndex + startFrame)+" YELLOW "+QString::number(frames[frameIndex].possessBallRobotID)+" at ("+QString::number(frames[frameIndex].realBall.pos.x())+","+QString::number(frames[frameIndex].realBall.pos.y())+") with dist of "+QString::number(startDribblingPoint.dist(frames[frameIndex].realBall.pos)));
                DribblingEvents++;
            }
        }
    }
    //Passing
    bool isPassing = false;
    int passingStartFrame, passingTeam = -1, passingRobotID = -1, PassingEvents = 0;
    writeToFile(" ");writeToFile("Passing");
    for (int frameIndex = 1; frameIndex < _frameDuration; frameIndex++) {
        if (!isPassing  && (frames[frameIndex].state & BALL_POSSESSION_UNKNOWN)) {
            //不在传球且球自由状态
            if ((frames[frameIndex - 1].state & BALL_POSSESSION_BLUE)
                    && frames[frameIndex].realBall.valid ){//&& frames[frameIndex].realBall.vel.mod() > 100) {
                isPassing = true;
                passingTeam = PARAM::BLUE;
                passingStartFrame = frameIndex;
                passingRobotID = frames[frameIndex + startFrame - 1].possessBallRobotID;
                //passingRobotID = resultLabels.ball_possession_labels(frameIndex + startFrame - 1).robot_id();
                //qDebug() << logTime(frameIndex + startFrame) << "MAYBE blue from" << passingRobotID;
                writeToFile(logTime(frameIndex + startFrame) + " MAYBE blue from " + QString::number(passingRobotID));
            } else if ((frames[frameIndex - 1].state & BALL_POSSESSION_YELLOW)
                       && frames[frameIndex].realBall.valid ){//&& frames[frameIndex].realBall.vel.mod() > 100) {
                isPassing = true;
                passingTeam = PARAM::YELLOW;
                passingStartFrame = frameIndex;
                //passingRobotID = resultLabels.ball_possession_labels(frameIndex + startFrame - 1).robot_id();
                passingRobotID = frames[frameIndex + startFrame - 1].possessBallRobotID;
                //qDebug() << logTime(frameIndex + startFrame) << "MAYBE YELLOW from" << passingRobotID;
                writeToFile(logTime(frameIndex + startFrame) + " MAYBE YELLOW from " + QString::number(passingRobotID));
            }
        } else if (isPassing) {
            if (frames[frameIndex].state & BALL_POSSESSION_BLUE) {
                //PassingLabel* _passingLabel =  resultLabels.add_passing_labels();
                //_passingLabel->set_start_frame(passingStartFrame + startFrame);
                //_passingLabel->set_end_frame(frameIndex + startFrame);
                //_passingLabel->set_passer_id(passingRobotID);
                //if (passingTeam == PARAM::BLUE && resultLabels.ball_possession_labels(frameIndex + startFrame).robot_id() != passingRobotID) {
                if (passingTeam == PARAM::BLUE && frames[frameIndex + startFrame].possessBallRobotID != passingRobotID) {
                    //_passingLabel->set_successful(true);
                    //_passingLabel->set_passer_team(BLUE_TEAM);
                    //_passingLabel->set_receiver_id(resultLabels.ball_possession_labels(frameIndex + startFrame).robot_id());
                    //qDebug() << "WTF" << logTime(frameIndex + startFrame) << resultLabels.ball_possession_labels(frameIndex + startFrame).robot_id() << passingRobotID << _passingLabel->passer_id()
                    //         << QString::fromStdString(_passingLabel->ShortDebugString());
                    writeToFile(logTime(frameIndex + startFrame) + " successful passing from " + QString::number(passingRobotID) + " to " + QString::number(frames[frameIndex + startFrame].possessBallRobotID));
                } else {
                    //_passingLabel->set_successful(false);
                    //_passingLabel->set_passer_team(passingTeam==PARAM::BLUE?BLUE_TEAM:YELLOW_TEAM);
                    //_passingLabel->set_passer_team(YELLOW_TEAM);
                    //qDebug() << "Pass Failed " << QString::fromStdString(_passingLabel->ShortDebugString()) << frames[frameIndex].realBall.vel.mod();
                    writeToFile(logTime(frameIndex + startFrame) + " Pass Failed ");
                }
                PassingEvents++;
                isPassing = false;
                passingStartFrame = -1;
                passingTeam = -1;
                passingRobotID = -1;
            } else if (frames[frameIndex].state & BALL_POSSESSION_YELLOW) {
                //PassingLabel* _passingLabel =  resultLabels.add_passing_labels();
                //_passingLabel->set_start_frame(passingStartFrame + startFrame);
                //_passingLabel->set_end_frame(frameIndex + startFrame);
                //_passingLabel->set_passer_id(passingRobotID);
                //if (passingTeam == PARAM::YELLOW && resultLabels.ball_possession_labels(frameIndex + startFrame).robot_id() != passingRobotID) {
                if (passingTeam == PARAM::YELLOW && frames[frameIndex + startFrame].possessBallRobotID != passingRobotID) {
                    //_passingLabel->set_successful(true);
                    //_passingLabel->set_passer_team(YELLOW_TEAM);
                    //_passingLabel->set_receiver_id(resultLabels.ball_possession_labels(frameIndex + startFrame).robot_id());
                    //qDebug() << "WTF" << logTime(frameIndex + startFrame) << resultLabels.ball_possession_labels(frameIndex + startFrame).robot_id() << passingRobotID << _passingLabel->passer_id()
                    //         << QString::fromStdString(_passingLabel->ShortDebugString());
                    writeToFile(logTime(frameIndex + startFrame) + " successful passing from " + QString::number(passingRobotID) + " to " + QString::number(frames[frameIndex + startFrame].possessBallRobotID));
                } else {
                    //_passingLabel->set_successful(false);
                    //_passingLabel->set_passer_team(passingTeam==PARAM::BLUE?BLUE_TEAM:YELLOW_TEAM);
                    //_passingLabel->set_passer_team(BLUE_TEAM);
                    //qDebug() << "Pass Failed " << QString::fromStdString(_passingLabel->ShortDebugString()) << frames[frameIndex].realBall.vel.mod();
                    writeToFile(logTime(frameIndex + startFrame) + " Pass Failed ");
                }
                PassingEvents++;
                isPassing = false;
                passingStartFrame = -1;
                passingTeam = -1;
                passingRobotID = -1;
            } else if (frameIndex - passingStartFrame >= 30 && frames[frameIndex].realBall.valid
                       && std::abs(frames[frameIndex].realBall.vel.dir()-frames[passingStartFrame].realBall.vel.dir()) > 3.14159 / 9) {
                //球速线变化20度
                //PassingLabel* _passingLabel =  resultLabels.add_passing_labels();
                //_passingLabel->set_start_frame(passingStartFrame + startFrame);
                //_passingLabel->set_end_frame(frameIndex + startFrame);
                //_passingLabel->set_passer_id(passingRobotID);
                //_passingLabel->set_successful(false);
                if (passingTeam == PARAM::BLUE)
                    //_passingLabel->set_passer_team(BLUE_TEAM);
                    writeToFile(logTime(frameIndex + startFrame) + " Pass Failed ");
                else
                    //_passingLabel->set_passer_team(YELLOW_TEAM);
                    writeToFile(logTime(frameIndex + startFrame) + " Pass Failed ");
                PassingEvents++;
                //qDebug() << "FUCK!!!" << QString::fromStdString(_passingLabel->ShortDebugString());
                isPassing = false;
                passingStartFrame = -1;
                passingTeam = -1;
                passingRobotID = -1;
            }
        }
    }
    if (isPassing) {
        //最后还是在PASSING 状态
        //PassingLabel* _passingLabel =  resultLabels.add_passing_labels();
        //_passingLabel->set_start_frame(passingStartFrame + startFrame);
        //_passingLabel->set_end_frame(endFrame);
        //_passingLabel->set_passer_id(passingRobotID);
        //_passingLabel->set_successful(false);
        if (passingTeam == PARAM::BLUE)
            //_passingLabel->set_passer_team(BLUE_TEAM);
            writeToFile(logTime(passingStartFrame + startFrame) + " to " + logTime(endFrame) + " MAYBE BLUE from " + QString::number(passingRobotID));
        else
            //_passingLabel->set_passer_team(YELLOW_TEAM);
            writeToFile(logTime(passingStartFrame + startFrame) + " to " + logTime(endFrame) + " MAYBE YELLOW from " + QString::number(passingRobotID));
        //qDebug() << "FUCK!!!" << QString::fromStdString(_passingLabel->ShortDebugString());
        PassingEvents++;
    }
    //Goal/GoalShot
    int GoalEvents = 0, thresholdDist = 70;
    bool newGoalFlag = false;
    CGeoPoint centerPoint(0,0);
    writeToFile(" ");writeToFile("Goal");
    for (int frameIndex = 0; frameIndex < _frameDuration ; frameIndex++) {
        if (frames[frameIndex].realBall.valid){
            if(!newGoalFlag&&abs(frames[frameIndex].realBall.pos.x())>opm->field_length/2+thresholdDist&&abs(frames[frameIndex].realBall.pos.x())<opm->field_length/2+opm->goal_depth&&abs(frames[frameIndex].realBall.pos.y())<opm->goal_width/2){
                writeToFile(logTime(frameIndex + startFrame)+" might get a goal ");
                GoalEvents++;
                newGoalFlag = true;
            }
            else if(newGoalFlag&&centerPoint.dist(frames[frameIndex].realBall.pos)<thresholdDist){
                newGoalFlag = false;
            }
        }
    }
    writeToFile(" "); writeToFile("Finally process");
    writeToFile("Blue BallPossesion Rate: "+QString::number(BlueBallPossessionRate)+"% Yellow BallPossesion Rate: "+QString::number(YellowBallPossessionRate)+"%");
    writeToFile(QString::number(DribblingEvents)+" Dribbling Events ");
    writeToFile(QString::number(PassingEvents)+" Passing Events ");
    writeToFile(QString::number(GoalEvents)+" Goal Events ");
}
int RecEventLabel::ballInMouth(int team, int frameIndex) {
    if (!frames[frameIndex].realBall.valid) {
//        qDebug() << "frame" << frameIndex << "found NO ball";
        return -1;
    }
    for (int robotID = 0 ; robotID < PARAM::ROBOTMAXID; robotID++) {
        if (frames[frameIndex].bot[team][robotID].valid &&
                frames[frameIndex].realBall.pos.dist(frames[frameIndex].bot[team][robotID].pos) >= 70 &&
                frames[frameIndex].realBall.pos.dist(frames[frameIndex].bot[team][robotID].pos) <= 140 &&
                std::abs( frames[frameIndex].bot[team][robotID].dir.dir()-CVector(frames[frameIndex].realBall.pos - frames[frameIndex].bot[team][robotID].pos).dir()) < 3.1416 / 3) {
//            qDebug() << "frame" << frameIndex << "found ball in" << team << robotID << "mouth";
            return robotID;
        }
    }
    return -1;
}
QString RecEventLabel::logTime(int currentFrame) {
    int fps = 1000/75;
    return QString("%1:%2.%3")
        .arg((int) ((currentFrame) * fps / 1E3) / 60)
        .arg((int) ((currentFrame) * fps / 1E3) % 60, 2, 10, QChar('0'))
        .arg((int) ((currentFrame) * fps) % 1000, 3, 10, QChar('0'));
}
int RecEventLabel::calCamNum() {
    int cam[PARAM::CAMERA] = {0,0,0,0,0,0,0,0};
    int i = 0;
    for (; i <= PARAM::CAMERA; i++) {
        if (!cam[recMsgs.ssl_wrapperpacket(i).detection().camera_id()]){
            cam[recMsgs.ssl_wrapperpacket(i).detection().camera_id()] = 1;
            continue;
        }
        else
            break;
    }
    return i;
}


