#ifndef PARAMMANAGER_H
#define PARAMMANAGER_H
#include <QApplication>
#include <QSettings>
#include <QString>
#include <QDebug>
#include "singleton.h"
#include "params.h"

namespace Owl {
class ParamManagerOwl: public Falcon::ParamManager {
  public:
    ParamManagerOwl(): ParamManager("../data/owl2.ini") {}
    ~ParamManagerOwl() {}
    template <class T>
    void updateParam(T& var, const QString & key, const QVariant & value, bool update) {
      changeParam(key, value);
      if(update) loadParam(var, key); //loadParamFromFile();
    }
    void updateParam(const QString & group, const QString & key, const QVariant & value, bool update) {
      changeParam(group, key, value);
      if(update) loadParamFromFile();
    }
    void loadParamFromFile() {
      //Global Settings
      loadParam(LoginName, "Alert/LoginName", 0);
      loadParam(isSimulation, "Alert/isSimulation", true);
      loadParam(isYellow, "Alert/isYellow", false);
      loadParam(isRight, "Alert/isRight", false);
      loadParam(field, "Alert/field", "Division_A");
      loadParam(updateGeometry, "Alert/updateGeometry", false);
      loadParam(saoAction, "Alert/saoAction", 0);
      loadParam(frameRate, "Alert/frameRate", 75);
      //Useful Ports
      loadParam(refereePortToBlue,"AlertPorts/refereePortToBlue",10002);
      loadParam(refereePortToYellow,"AlertPorts/refereePortToYellow",10004);
      loadParam(VisionSim, "AlertPorts/VisionSim", 10020);
      loadParam(VisionReal, "AlertPorts/VisionReal", 10005);
      loadParam(VisionRemote, "AlertPorts/VisionRemote", 10066);
      loadParam(serialPort, "AlertPorts/serialPort", "COM3");
      //Canvas
      loadParam(canvasHeight, "Canvas/canvasHeight", 960);
      loadParam(canvasWidth, "Canvas/canvasWidth", 1280);
      loadParam(param_canvasWidth, "Canvas/param_canvasWidth", 13200);
      loadParam(param_canvasHeight, "Canvas/param_canvasHeight", 9900);
      //DebugMessages
      loadParam(debug, "DebugMessages/debug", true);
      loadParam(type_arc, "DebugMessages/type_arc", true);
      loadParam(type_line, "DebugMessages/type_line", true);
      loadParam(type_points, "DebugMessages/type_points", true);
      loadParam(type_text, "DebugMessages/type_text", true);
      loadParam(type_robot, "DebugMessages/type_robot", true);
      //HeatMap
      loadParam(HeatMap, "HeatMap/HeatMap", false);
      loadParam(drawStep, "HeatMap/drawStep", 100);
      loadParam(startPosX, "HeatMap/startPosX", -6000);
      loadParam(startPosY, "HeatMap/startPosY", -4500);
      //Size
      loadParam(ballDiameter, "Size/ballDiameter", 100);
      loadParam(shadowDiameter, "Size/shadowDiameter", 30);
      loadParam(carDiameter, "Size/carDiameter", 180);
      loadParam(carFaceWidth, "Size/carFaceWidth", 120);
      loadParam(numberSize, "Size/numberSize", 200);
      loadParam(debugPointSize, "Size/debugPointSize", 5);
      //Field
      loadParam(field_length, field+"/field_length", 12000);
      loadParam(field_width, field+"/field_width", 9000);
      loadParam(goal_width, field+"/goal_width", 1200);
      loadParam(goal_depth, field+"/goal_depth",  200);
      loadParam(penalty_depth, field+"/penalty_depth", 1200);
      loadParam(penalty_width, field+"/penalty_width", 2400);
      loadParam(center_radius, field+"/center_radius",  500);
      if(field == "Division_B") {
        loadParam(if_ellipse_penalty, field+"/if_ellipse_penalty", false);
        loadParam(penalty_radius, field+"/penalty_radius", 800);
        loadParam(penalty_area_l, field+"/penalty_area_l", 350);
      }
      loadParam(extendLength, field+"/extendLength", 200);
      //Team
      loadParam(blueTeam, "Team/blueTeam", "SRC");
      loadParam(yellowTeam, "Team/yellowTeam", "SRC");
      loadParam(KeeperID, "Team/KeeperID", 0);
      //Camera Settings
      loadParam(total_cameras, "Camera/total_cameras", 1);
      //Special Vision Process
      loadParam(projection, "Vision/projection", false);
      loadParam(detectBallInRobot, "Vision/detectBallInRobot", true);
      loadParam(FilteDirection, "Vision/FilteDirection", false);
      //Simulator
      loadParam(useSimInside, "Simulator/useSimInside", false);
      //Display Settings
      loadParam(display_height, "Display/display_height", 360);
      loadParam(display_team, "Display/display_team", "Blue");
      loadParam(display_teamIndex, "Display/display_teamIndex", 0);
      loadParam(display_robotID, "Display/display_robotID", 1);
      loadParam(display_mode, "Display/display_mode", "Vxy");
      loadParam(display_modeIndex, "Display/display_modeIndex", 0);
      loadParam(horizontLines, "Display/horizontLines", 10);
      loadParam(limitation, "Display/limitation", 6.5);
      loadParam(maximum, "Display/maximum", 10);
    }
  public:
    //Global Settings
    int LoginName;
    bool isSimulation, isYellow, isRight;
    QString field;
    bool updateGeometry;
    int saoAction;
    double frameRate;
    //Useful Ports
    int refereePortToBlue, refereePortToYellow;
    int VisionSim, VisionReal, VisionRemote;
    QString serialPort;
    //Canvas
    int canvasWidth, canvasHeight;
    int param_canvasWidth, param_canvasHeight;
    //DebugMessages
    bool debug, type_arc, type_line, type_points, type_text, type_robot;
     //HeatMap
    bool HeatMap;
    int drawStep;
    int startPosX;
    int startPosY;
    //Size
    int ballDiameter, shadowDiameter, carDiameter, carFaceWidth, numberSize, debugPointSize;
    //Field
    int line_thickness;
    int field_length, field_width, center_radius;
    int penalty_width, penalty_depth;
    int goal_thickness, goal_depth, goal_width;
    int realWidth, realHeight;
    int extendLength;
    bool if_ellipse_penalty;
    int penalty_radius, penalty_area_l;
    //Team
    QString blueTeam, yellowTeam;
    int KeeperID;
    //Camera Settings
    int total_cameras;
    //Special Vision Process
    bool projection, detectBallInRobot, FilteDirection;
    //Simulator
    bool useSimInside;
    //Display Settings
    int horizontLines;
    double limitation, maximum, display_height;
    QString display_team, display_mode;
    int display_teamIndex, display_robotID, display_modeIndex;
};
class ParamManagerCfg: public Falcon::ParamManager {
  public:
    ParamManagerCfg(): ParamManager("../data/cfg.ini") {}
    ~ParamManagerCfg() {}
    template <class T>
    void updateParam(T& var, const QString & key, const QVariant & value, bool update) {
      changeParam(key, value);
      if(update) loadParam(var, key); //loadParamFromFile();
    }
    void updateParam(const QString & group, const QString & key, const QVariant & value, bool update) {
      changeParam(group, key, value);
      if(update) loadParamFromFile();
    }
    void loadParamFromFile() {
      //software path
      loadParam(BlueRBKPath, "Path/BlueRBKPath", "CHOOSE CONTROLLER PATH");
      loadParam(YellowRBKPath, "Path/YellowRBKPath", "CHOOSE CONTROLLER PATH");
      loadParam(grSimPath, "Path/grSimPath", "CHOOSE SIMULATOR PATH");
      loadParam(CrayPath, "Path/CrayPath", "CHOOSE Cray PATH");
      //IP address
      loadParam(local_address, "IP/local_address", "127.0.0.1");
      loadParam(referee_address, "IP/referee_address", "224.5.23.1");
      loadParam(ssl_address, "IP/ssl_address", "224.5.23.2");
      loadParam(sim_address, "IP/sim_address", "224.5.23.3");
      loadParam(GC_Address, "IP/GC_Address", "127.0.0.1");
      //internal port
      loadParam(sim_send, "Ports/sim_send", 20011);
      loadParam(blue_status, "Ports/blue_status", 30011);
      loadParam(yellow_status, "Ports/yellow_status", 30012);
      loadParam(blue_control, "Ports/blue_control", 50011);
      loadParam(yellow_control, "Ports/yellow_control", 50012);
      loadParam(blue_feedback, "Ports/blue_feedback", 60001);
      loadParam(yellow_feedback, "Ports/yellow_feedback", 60002);
      loadParam(blue_vision, "Ports/blue_vision", 23333);
      loadParam(yellow_vision, "Ports/yellow_vision", 23334);
      loadParam(blue_debug, "Ports/blue_debug", 20001);
      loadParam(yellow_debug, "Ports/yellow_debug", 20002);
      loadParam(blue_heat, "Ports/blue_heat", 20003);
      loadParam(yellow_heat, "Ports/yellow_heat", 20004);
      loadParam(optionPort, "Ports/optionPort", 23231);
      loadParam(GC_Port, "Ports/GC_Port", 10008);
      loadParam(refereePortFromGC, "Ports/refereePortFromGC", 10003);
      loadParam(refereePortToAutoRef, "Ports/refereePortToAutoRef", 10007);
      loadParam(VisionAutoRef, "Ports/VisionAutoRef", 10006);
      //Version
      loadParam(version, "Basic/version", "2022.4.23");
    }
  public:
    QString BlueRBKPath, YellowRBKPath, grSimPath, CrayPath;
    QString local_address, sim_address, referee_address, ssl_address, GC_Address;
    int sim_send;
    int blue_status, yellow_status;
    int blue_control, yellow_control;
    int blue_feedback, yellow_feedback;
    int blue_vision, yellow_vision;
    int blue_debug, yellow_debug;
    int blue_heat, yellow_heat;
    int optionPort;
    int GC_Port;
    int refereePortToAutoRef, VisionAutoRef, refereePortFromGC;
    QString version;
};
class ParamManagerVision: public Falcon::ParamManager {
  public:
    ParamManagerVision(): ParamManager("../data/vision.ini") {}
    ~ParamManagerVision() {}
    template <class T>
    void updateParam(T& var, const QString & key, const QVariant & value, bool update) {
      changeParam(key, value);
      if(update) loadParam(var, key); //loadParamFromFile();
    }
    void updateParam(const QString & group, const QString & key, const QVariant & value, bool update) {
      changeParam(group, key, value);
      if(update) loadParamFromFile();
    }
    void loadParamFromFile() {
      //DealRobot
      loadParam(robotMergeDist, "Robot/robotMergeDist", 100);
      loadParam(carMinBelieveFrame, "Robot/carMinBelieveFrame", 3);
      loadParam(theirCarMaxLostFrame, "Robot/theirCarMaxLostFrame", 15);
      loadParam(ourCarMaxLostFrame, "Robot/ourCarMaxLostFrame", 150);
      loadParam(maxLostFrame, "Robot/maxLostFrame", 1800);
      loadParam(deceleration, "Robot/deceleration", 29000);
      loadParam(acceleration, "Robot/acceleration", 0);
      loadParam(thresholdToDec, "Robot/thresholdToDec", -1000);
      loadParam(thresholdToAcc, "Robot/thresholdToAcc", 4000);
      //DealBall
      loadParam(ballMergeDist, "Ball/ballMergeDist", 140);
      loadParam(ballMinBelieveFrame, "Ball/ballMinBelieveFrame", 10);
      loadParam(inValidSpeed, "Ball/inValidSpeed", 12000);
      //Kalman
      loadParam(ballFollowProp, "Kalman/ballFollowProp", 1.0);
      //Collision
      loadParam(robotsCollisionDist, "Collision/robotsCollisionDist", 180);
      //Physics
      loadParam(G, "Physics/G", 9.8);
      loadParam(PI, "Physics/PI", 3.14159265358979323846);
      loadParam(chipAngle, "Physics/chipAngle", 45);
      loadParam(botCenterToMouth, "Physics/botCenterToMouth", 76);
      loadParam(ballradius, "Physics/ballradius", 21.5);
      loadParam(total_lated_frame, "Physics/total_lated_frame", 4.7);
      loadParam(v_switch, "Physics/v_switch", 2000);
      loadParam(acc_slide, "Physics/acc_slide", -4000);
      loadParam(acc_roll, "Physics/acc_roll", -325);
      loadParam(ball_delc_change_point, "Physics/ball_delc_change_point", 250);
      loadParam(ball_fast_dec, "Physics/ball_fast_dec", 360);
      loadParam(ball_slow_dec, "Physics/ball_slow_dec", 27.5);
    }
  public:
    //DealRobot
    double robotMergeDist;
    double carMinBelieveFrame, theirCarMaxLostFrame, ourCarMaxLostFrame, maxLostFrame;
    double deceleration, acceleration;
    double thresholdToDec, thresholdToAcc;
    //DealBall
    double ballMergeDist;
    double ballMinBelieveFrame;
    double inValidSpeed;
    //Kalman
    double ballFollowProp;
    //Collision
    double robotsCollisionDist;
    //Physics
    double G;
    double PI;
    double chipAngle;
    double botCenterToMouth;
    double ballradius;
    double total_lated_frame;
    double v_switch;
    double acc_slide;
    double acc_roll;
    double ball_delc_change_point;
    double ball_fast_dec;
    double ball_slow_dec;
};
class ParamManagerKickParam: public Falcon::ParamManager {
  public:
    ParamManagerKickParam(): ParamManager("../data/kickparam.ini") {}
    ~ParamManagerKickParam() {}
};
class ParamManagerLogClip: public Falcon::ParamManager {
  public:
    ParamManagerLogClip(): ParamManager("../data/logclip.ini") {}
    ~ParamManagerLogClip() {}
};
typedef Falcon::MeyersSingleton<ParamManagerOwl> OParamManager;
typedef Falcon::MeyersSingleton<ParamManagerCfg> CParamManager;
typedef Falcon::MeyersSingleton<ParamManagerVision> VParamManager;
typedef Falcon::MeyersSingleton<ParamManagerKickParam> KParamManager;
typedef Falcon::MeyersSingleton<ParamManagerLogClip> LParamManager;
}

#endif // PARAMMANAGER_H

// void QSettings::setPath(Format format, Scope scope, const QString &path)
// QSettings settings("./myapp.ini", QSettings::IniFormat);
