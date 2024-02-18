#include "TechDefenceRobot.h"

#include "VisionModule.h"
#include "Global.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846


#include <iostream>
#include "GDebugEngine.h"
#include "Vision/VisionModule.h"
#include "skill/Factory.h"
#include "utils.h"
#include "WorldModel/DribbleStatus.h"
#include "RobotSensor.h"
#include "param.h"
#include "WorldModel/WorldModel.h"


#include <vector>
#include <variant>
#include <string>
#include <cmath>
using namespace std;

namespace {enum TDstate {getball ,wait};}
int findIndex(const std::vector<int>& vec, int target) {
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {return std::distance(vec.begin(), it);}
    std::cout<<"INDEX NOT FOUND";return -1;}
bool eraseElement(std::vector<int>& vec, int target) {
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {vec.erase(it);return true;}
    return false;}
double normalizeAngle1(double angle) {
    while (angle > M_PI) angle -= 2 * M_PI;
    while (angle <= -M_PI) angle += 2 * M_PI;
    return angle;}
double sortdir(double A, double B, double dir, double vel,double threshold) {
    if ((A >= dir && dir >= B) || (B >= dir && dir >= A)) {
        if (vel > threshold) {return normalizeAngle1(std::max(A, B));}
        else if (vel<=-threshold) {return normalizeAngle1(std::min(A, B));}}
    return 0;}
double amidDir(double A, double B, double dir,double vel,double Vthreshold) {
    const double thres = 0.2;
    double A1 = A;
    double B1 = B;
    double A2 = A;
    double B2 = B;
    if (std::abs(A - B) > M_PI) {
        if (A < 0) {A1 = 2 * M_PI + A;}
        if (B < 0) {B1 = 2 * M_PI + B;}
        if (A > 0) {A2 = A - 2 * M_PI;}
        if (B > 0) {B2 = B - 2 * M_PI;}}
    double tortn1 = sortdir(A1, B1, dir, vel,Vthreshold);
    double tortn2 = sortdir(A2, B2, dir, vel,Vthreshold);
    return tortn1 || tortn2 || 0;}
double gotoAngle(double a,double b,double c,double d,double DIR,double VR){
    double a_c=amidDir(a,c,DIR,VR,0.2);
    if (amidDir(a,d,DIR,1,0)){return a;}
    else if (amidDir(d,b,DIR,1,0)){return c;}
    else if (a_c){return a_c;}
    else if (amidDir(a,b,DIR,1,0)){return a;}
    else if (amidDir(b,c,DIR,1,0)){return c;}}
class twoDPos{
private:
public:
    double x;
    double y;
    twoDPos(double x_ = 0, double y_ = 0)
    {x = x_;y = y_;}};
twoDPos CalcQieDian1(twoDPos ptCenter, twoDPos ptOutside, double dbRadious) {
    struct point {double x, y;};
    point E, F, G, H;
    double r = dbRadious;E.x = ptOutside.x - ptCenter.x;E.y = ptOutside.y - ptCenter.y; 
    double t = r / sqrt(E.x * E.x + E.y * E.y);F.x = E.x * t;F.y = E.y * t; 
    double a = acos(t);G.x = F.x * cos(a) - F.y * sin(a);G.y = F.x * sin(a) + F.y * cos(a); H.x = G.x + ptCenter.x;H.y = G.y + ptCenter.y; 
    return twoDPos(int(H.x), int(H.y));
    }
twoDPos CalcQieDian2(twoDPos ptCenter, twoDPos ptOutside, double dbRadious) {
    struct point
    {double x, y;};
    point E, F, G, H;
    double r = dbRadious;E.x = ptOutside.x - ptCenter.x;E.y = ptOutside.y - ptCenter.y; 
    double t = r / sqrt(E.x * E.x + E.y * E.y);F.x = E.x * t;F.y = E.y * t; 
    double a = -acos(t);G.x = F.x * cos(a) - F.y * sin(a);G.y = F.x * sin(a) + F.y * cos(a); H.x = G.x + ptCenter.x;H.y = G.y + ptCenter.y; 
    return twoDPos(int(H.x), int(H.y));}
std::pair<double, double> ball2circle(CGeoPoint ballpos,double ballDir, CGeoPoint cirpos, double cr,int option){
    double ballx=ballpos.x();double bally=ballpos.y();double cx=cirpos.x();double cy=cirpos.y();
    twoDPos ballPos(ballx, bally);
    twoDPos circlePos(cx, cy);
    twoDPos contact1 = CalcQieDian1(circlePos, ballPos, cr);twoDPos contact2 = CalcQieDian2(circlePos, ballPos, cr);
    double dirA = atan((contact1.y - ballPos.y) / (contact1.x - ballPos.x));double dirB = atan((contact2.y - ballPos.y) / (contact2.x - ballPos.x));
    if (option==0){return std::make_pair(amidDir(dirA,dirB,ballDir,1,0),0.0);}
    else if (option==1){return std::make_pair(dirA,dirB);}}
CGeoPoint midpoint1(const CGeoPoint& A, const CGeoPoint& B) {return CGeoPoint((A.x() + B.x()) / 2.0, (A.y() + B.y()) / 2.0);}
CTechDefence::CTechDefence(){}

void CTechDefence::plan(const CVisionModule* pVision)
{
//----------------------------------------------INITIALIZE ALL PLAYER INFOS AND BALL INFOS
    std::vector<const PlayerVisionT*> OPptrs;
    std::vector<const PlayerVisionT*> TPptrs;
    std::vector<int> OProlenums;
    std::vector<int>TProlenums;
    for (int irole = 0; irole <= Param::Field::MAX_PLAYER; ++irole)
    {
        const PlayerVisionT& OPtmp = pVision->OurPlayer(irole);
        const PlayerVisionT& TPtmp = pVision->TheirPlayer(irole);
        if (OPtmp.Valid()){OPptrs.push_back(&OPtmp);OProlenums.push_back(irole);}
        if (TPtmp.Valid()){TPptrs.push_back(&TPtmp);TProlenums.push_back(irole);}
    }
    const BallVisionT& ball = pVision->Ball();
//-------------------------------------------------CALCULATE WHICH CIRCLE TO FOCUS(RETURN CAR NUM)
    int focusNum=1;//car num
//-------------------------------------------------CALCULATE a,b,c,d,DIR,VR of the certain car num
    CGeoPoint A=TPptrs[findIndex(TProlenums,focusNum)]->Pos();
    double DIR=TPptrs[findIndex(TProlenums,focusNum)]->Dir();
    double VR=TPptrs[findIndex(TProlenums,focusNum)]->RotVel();
    std::vector<int>TProlenumsR=TProlenums;
    eraseElement(TProlenumsR,focusNum);
    CGeoPoint A2=TPptrs[findIndex(TProlenums,TProlenumsR[0])]->Pos();
    CGeoPoint A3=TPptrs[findIndex(TProlenums,TProlenumsR[1])]->Pos();
    CGeoPoint O=ball.Pos();
    CGeoPoint M=midpoint1(A2,A3);
    CVector AM(M.x()-A.x(),M.y()-A.y());
    double b=AM.dir();
    double d=normalizeAngle1(b-M_PI);
    auto ac=ball2circle(A,DIR,M,78*2,1);
    double a=ac.first;
    double c=ac.second;
// //-------------------------------------------------DEBUG INFOS
    std::cout<<"OProlenums:[";for (int i : OProlenums) {std::cout << i << " ";}std::cout <<"]"<< std::endl;
    std::cout<<"TProlenums:[";for (int i : TProlenums) {std::cout << i << " ";}std::cout <<"]"<< std::endl;
    std::cout<<"TProlenumsR:[";for (int i : TProlenumsR) {std::cout << i << " ";}std::cout <<"]"<< std::endl;
    // std::cout<<"findIndex(TProlenums,TProlenumsR[1])="<<findIndex(TProlenums,TProlenumsR[1])<<std::endl;
    // std::cout<<"TPptrs[1] pos x="<<TPptrs[TProlenumsR[0]]->Pos().x()<<std::endl;
    std::cout<<"b:{"<<b<<"};d{"<<d<<"};a{"<<a<<"};c{"<<c<<std::endl;
    GDebugEngine::Instance()->gui_debug_msg(M, "M", COLOR_PURPLE);
    GDebugEngine::Instance()->gui_debug_msg(A, "A", COLOR_PURPLE);

//-------------------------------------------------GO TO WHICH ANGLE
    // double JamAngle=gotoAngle(a,b,c,d,DIR,VR);


//-------------------------------------------------SET TASK 
    TaskT taskR1(task());
    int rolenum=task().executor;
    taskR1.executor=1;
    // OProlenums[0];
    // taskR1.player.pos=B;
	setSubTask(TaskFactoryV2::Instance()->GotoPosition(taskR1));//将taskR1给走位subtask执行
	CStatedTask::plan(pVision);
}

CTechDefence::~CTechDefence() {}

CPlayerCommand* CTechDefence::execute(const CVisionModule* pVision)
{if (subTask()){return subTask()->execute(pVision);} return NULL;}
#endif