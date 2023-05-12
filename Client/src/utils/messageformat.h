#ifndef __MESSAGEFORMAT_H__
#define __MESSAGEFORMAT_H__
#include <iostream>
#include "geometry.h"
#include "ballstate.h"
#include <list>
#include "staticparams.h"
#include <QDateTime>

/************************************************************************/
/*                 Basic Vision Classes                                 */
/************************************************************************/
namespace Owl{
//enum ballState {received, touched, kicked, struggle, chip_pass, flat_pass};
struct RobotInformation {
    bool infrared;
    bool flat;
    bool chip;
    double battery;
    double capacitance;
    double wheelSpeed[4];
    QTime wheelSpeedTimestamp;
    bool wheelSpeedUpdate;
    RobotInformation(): infrared(false), flat(false), chip(false), battery(0), capacitance(0) {
        std::fill_n(wheelSpeed, 4, 0);
        wheelSpeedTimestamp = QTime::currentTime();
        wheelSpeedUpdate = false;
    }
    bool fill(bool infrared, bool flat, bool chip, double battery, double capacitance){
        this->infrared = infrared;
        this->flat = flat;
        this->chip = chip;
        this->battery = battery;
        this->capacitance = capacitance;
        return true;
    }
    bool fill(const RobotInformation& r){
        return fill(r.infrared, r.flat, r.chip, r.battery, r.capacitance);
    }
};
struct RobotSpeed {
    CVector vxy;
    float vr;
    RobotSpeed(): vxy(), vr(0) {}
    RobotSpeed(float _x, float _y, float _r):
        vxy(_x, _y), vr(_r) {}
    RobotSpeed(CVector v, float _r):
        vxy(v), vr(_r) {}
    float vx() const{return vxy.x();}
    float vy() const{return vxy.y();}
};
struct RobotCommands {
    RobotSpeed robotSpeed[PARAM::ROBOTMAXID];
    bool valid;
    RobotCommands(): valid(false) {
        for (int i = 0; i < PARAM::ROBOTMAXID; i++)
            robotSpeed[i] = RobotSpeed();
    }
};
struct RawInfo {
    CGeoPoint pos;
    double angle;
    RobotSpeed vel;
    RawInfo(): pos(), vel(), angle(0) {}
    RawInfo(double rawX, double rawY, double rawVx, double rawVy, double _raw_angle = 0, double _raw_rotVel = 0){
        pos.fill(rawX, rawY);
        angle = _raw_angle;
        vel = RobotSpeed(rawVx, rawVy, _raw_rotVel);
    }
    bool fill(double rawX, double rawY, double rawVx, double rawVy, double _raw_angle = 0, double _raw_rotVel = 0){
        this->pos.fill(rawX, rawY);
        this->angle = _raw_angle;
        this->vel = RobotSpeed(rawVx, rawVy, _raw_rotVel);
        return true;
    }
    bool fill(const RawInfo& r){
        return fill(r.pos.x(), r.pos.y(), r.vel.vx(), r.vel.vy(), r.angle, r.vel.vr);
    }
};

struct Ball {
    bool valid = false;
    int cameraID;
    CGeoPoint pos;
    CGeoPoint predict_pos;
    double height;
    CVector velocity;
    CVector accelerate;
    RawInfo raw;
    Ballstate ball_state_machine;
    Ball(): pos(), height(0), raw(), velocity() {}

    bool fill(double x, double y, RawInfo r = RawInfo(), double height = 0, int id = -1, CVector vel = CVector()) {
        this->pos.fill(x,y);
        this->raw.fill(r);
        this->height = height;
        this->velocity = vel;
        this->cameraID = id;
        return true;
    }
    bool fill(CGeoPoint p, RawInfo r = RawInfo(), double height = 0, int id = -1, CVector vel = CVector()) {
        return fill(p.x(), p.y(), r, height, id, vel);
    }
    bool fill(const Ball& ball) {
        return fill(ball.pos.x(), ball.pos.y(), ball.raw, ball.height, ball.cameraID, ball.velocity);
    }
};
struct Robot {
    bool valid;
    int team;
    int id;

    CGeoPoint pos;
    CGeoPoint predict_pos;
    double angle;
    RobotSpeed velocity;
    CVector accelerate;

    RawInfo raw;
    Robot(): team(-1), id(-1), valid(false), accelerate(), raw(), velocity() {}
    Robot(int _team, double _x, double _y, double _angle, int _id = -1, RawInfo r = RawInfo(), RobotSpeed vel = RobotSpeed(), CVector acc = CVector(0,0)) {
        valid = _id>=0 && _id<PARAM::ROBOTMAXID && _team>=PARAM::BLUE && _team<PARAM::TEAMS ? true: false;
        id = _id;
        team = _team;
        pos = CGeoPoint(_x, _y);
        angle = _angle;
        raw = r;
        velocity = vel;
        accelerate = acc;
    }
    Robot(int _team, CGeoPoint p, double _angle, int _id = -1, RawInfo r = RawInfo(), RobotSpeed vel = RobotSpeed(), CVector acc = CVector(0,0)) {
        valid = _id>=0 && _id<PARAM::ROBOTMAXID && _team>=PARAM::BLUE && _team<PARAM::TEAMS ? true: false;
        id = _id;
        team = _team;
        pos = p;
        angle = _angle;
        raw = r;
        velocity = vel;
        accelerate = acc;
    }
    bool fill(int _team, int _id, double _x, double _y, double angle, RawInfo r = RawInfo(), RobotSpeed vel = RobotSpeed(), CVector acc = CVector(0,0)) {
        valid = _id>=0 && _id<PARAM::ROBOTMAXID && _team>=PARAM::BLUE && _team<PARAM::TEAMS ? true: false;
        this->team = _team;
        this->id = _id;
        this->pos = CGeoPoint(_x, _y);
        this->raw = r;
        this->angle = angle;
        this->velocity = vel;
        this->accelerate = acc;
        return valid;
    }
    bool fill(int _team, int _id, CGeoPoint p, double angle, RawInfo r = RawInfo(), RobotSpeed vel = RobotSpeed(), CVector acc = CVector(0,0)) {
        return fill(_team, _id, p.x(), p.y(), angle, r, vel, acc);
    }
    bool fill(const Robot& robot) {
        return fill(robot.team, robot.id, robot.pos, robot.angle, robot.raw, robot.velocity, robot.accelerate);
    }
};
struct CameraEdge {
    double min, max;
};
struct SingleCamera {
    unsigned short id;
    CGeoPoint campos;
    double height;
    CameraEdge leftedge, rightedge, upedge, downedge;
    SingleCamera(): height(3500) {} //set 3500mm as an example
    void fillCenter(double x, double y) {
        campos.fill(x, y);
        leftedge.min = rightedge.min = x;
        upedge.min = downedge.min = y;
    }
    void fillCenter(CGeoPoint p) {
        fillCenter(p.x(), p.y());
    }
};
struct CameraFix {
    double theta, t1, t2;
    CameraFix(): theta(0), t1(0), t2(0) {}
};

//* Robot store the data, Index and Size exist for the index search for robots;
//* Index : -1 means not exist, or it means the index in Robot Array;
//* VisionMessage use for the final processed vision data.
class OriginMessage {
  public:
    unsigned short robotSize[PARAM::TEAMS];
    unsigned short ballSize;
    Robot robot[PARAM::TEAMS][PARAM::ROBOTMAXID];
    Ball ball[PARAM::BALLNUM];
    int robotIndex[PARAM::TEAMS][PARAM::ROBOTMAXID];
    OriginMessage(): ballSize(0) {
        robotSize[PARAM::BLUE] = robotSize[PARAM::YELLOW] = 0;
        std::fill_n(&robotIndex[0][0], PARAM::TEAMS * PARAM::ROBOTMAXID, -1);
    }
    void init() {
        robotSize[PARAM::BLUE] = robotSize[PARAM::YELLOW] = ballSize = 0;
        std::fill_n(&robotIndex[0][0], PARAM::TEAMS * PARAM::ROBOTMAXID, -1);
        ball[0].pos.fill(-32767, -32767);
    }
    bool addBall(double x, double y, RawInfo r = RawInfo(), CVector vel = CVector(), double height = 0, int id = -1) {
        return ballSize >= PARAM::BALLNUM ? false : ball[ballSize++].fill(x, y, r, height, id, vel);
    }
    bool addBall(CGeoPoint point, RawInfo r = RawInfo(), double height = 0, int id = -1, CVector vel = CVector()) {
        return addBall(point.x(), point.y(), r, vel, height, id);
    }
    bool addBall(const Ball& b) {
        return addBall(b.pos, b.raw, b.height, b.cameraID, b.velocity);
    }
    bool addRobot(int color, int id, double x, double y, double angel, RawInfo r = RawInfo(), RobotSpeed vel = RobotSpeed()) {
        if(robotSize[color] > PARAM::ROBOTMAXID)
            return false;
        robotIndex[color][id] = robotSize[color];
        return robot[color][robotSize[color]++].fill(color, id, x, y, angel, r, vel);
    }
    bool addRobot(int color, int id, CGeoPoint pos, double angel, RawInfo r = RawInfo(), RobotSpeed vel = RobotSpeed()) {
        return addRobot(color, id, pos.x(), pos.y(), angel, r, vel);
    }
    bool addRobot(const Robot& r) {
        return addRobot(r.team, r.id, r.pos, r.angle, r.raw, r.velocity);
    }

};

class ReceiveVisionMessage: public OriginMessage {
  public:
    unsigned short camID;
    unsigned long long frame;
    double captureTime; // ![1] TODO -> gjy

    ReceiveVisionMessage(): camID(-1), frame(-1), captureTime(-1) {}
    void clear() {
        captureTime = frame = camID = -1;
        ballSize = robotSize[PARAM::BLUE] = robotSize[PARAM::YELLOW] = 0;
    }
};
}
#endif // __MESSAGEFORMAT_H__
