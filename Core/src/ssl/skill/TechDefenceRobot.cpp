#include "TechDefenceRobot.h"

#include "VisionModule.h"
#include "Global.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
int rJam=45;
vector<CGeoPoint>  centers  = { CGeoPoint(75,-130), CGeoPoint(75,130), CGeoPoint(-150,0) };
vector<CGeoCirlce> Circles  = { CGeoCirlce(centers[0], rJam), CGeoCirlce(centers[1], rJam), CGeoCirlce(centers[2], rJam) };
int findIndex(const std::vector<int>& vec, int target) {
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {return std::distance(vec.begin(), it);}
    std::cout<<"INDEX NOT FOUND";return -1;}
bool eraseElement(std::vector<int>& vec, int target) {
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {vec.erase(it);return true;}
    return false;}
void drawDir(CGeoPoint A,double DIR,string msg){
    CGeoPoint D(A.x() + 100 * std::cos(DIR), A.y() + 100 * std::sin(DIR));
    CGeoSegment AD(A,D);
    GDebugEngine::Instance()->gui_debug_line(A,D,COLOR_YELLOW);
    GDebugEngine::Instance()->gui_debug_msg(D,(msg).c_str(), COLOR_RED);}
double qiexiandir[3];
void getcircledir (const CGeoPoint& playerpos, const CGeoPoint& centre, const double r){
    // CGeoLine player2centre(playerpos, centre);
    const CVector player2centre = playerpos - centre;
    const double vertical = player2centre.dir() + 3.1415926/2;
    const CGeoPoint p1 (centre.x() + r * cos(vertical), centre.y() + r * sin(vertical));
    const CGeoPoint p2 (centre.x() - r * cos(vertical), centre.y() - r * sin(vertical));
    const CVector player2p1 = playerpos - p1;
    const CVector player2p2 = playerpos - p2;
    qiexiandir[0] = player2p1.dir() < player2p2.dir() ? player2p1.dir() : player2p2.dir();
    qiexiandir[1] = player2p1.dir() > player2p2.dir() ? player2p1.dir() : player2p2.dir();}
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
    if      (tortn1!=0) {return tortn1;}
    else if (tortn2!=0) {return tortn2;}
    else                {return 0;}}
double gotoAngle(double a,double b,double c,double d,double DIR,double VR,CGeoPoint A){
    double a_c=amidDir(a,c,DIR,VR,0.2);
    std::cout<<"amidDir("<<a<<c<<DIR<<VR<<0.1<<"->"<<a_c<<std::endl;
    if      (amidDir(a,d,DIR,1,0)){drawDir(A,DIR,"a d");return a;}
    else if (amidDir(d,c,DIR,1,0)){drawDir(A,DIR,"d c");return c;}
    else if (a_c)                 {drawDir(A,DIR,to_string(a_c).c_str());return a_c;}
    else if (amidDir(a,b,DIR,1,0)){drawDir(A,DIR,"a b");return a;}
    else if (amidDir(b,c,DIR,1,0)){drawDir(A,DIR,"b c");return c;}
    return DIR;}
CGeoPoint JamA2Jampos(CGeoPoint Apos,double DIR){   
    int icircle;
    for(int i = 0; i < 3; ++i){if (centers[i].dist(Apos)<32){icircle=i;break;}}
    CGeoPoint JamP(Apos.x() + 200 * std::cos(DIR), Apos.y() + 200 * std::sin(DIR));
    CGeoSegment JamPline(JamP,Apos);
    GDebugEngine::Instance()->gui_debug_line(JamP,Apos,COLOR_CYAN);
    CGeoSegmentCircleIntersection Intersection = CGeoSegmentCircleIntersection(JamPline,Circles[icircle]);
    return Intersection.point1();}
int whichTPclose(std::vector<const PlayerVisionT*> TPptrs,std::vector<int>TProlenums,CGeoPoint center)
{
<<<<<<< HEAD
for (size_t i = 0; i < TPptrs.size(); ++i)
=======
enum TDstate {getball ,wait};//setState(getball);if (state()==getball);
}
double normalizeAngle(double angle) {
    while (angle > M_PI) angle -= 2 * M_PI;
    while (angle <= -M_PI) angle += 2 * M_PI;
    return angle;
}
bool DIRsame(double angle1, double angle2) {
    const double tolerance = 30 * M_PI / 180; // 5度转换为弧度
    angle1 = normalizeAngle(angle1);
    angle2 = normalizeAngle(angle2);
    double diff = std::abs(angle1 - angle2);
    double sum = std::abs(angle1 + angle2);
    bool same= diff <= tolerance || (std::abs(angle1) > M_PI - tolerance && std::abs(angle2) > M_PI - tolerance && sum <= tolerance);
    CGeoPoint T(0,-30);
    if (same){GDebugEngine::Instance()->gui_debug_msg(T,"same", COLOR_RED);}
    return same;
}
CGeoPoint backpos(const CGeoPoint& A, const CGeoPoint& H, double distback) {
    // 计算向量AH
    double dx = H.x() - A.x();
    double dy = H.y() - A.y();
    
    // 计算AH向量的长度
    double lengthAH = std::sqrt(dx * dx + dy * dy);
    
    // 计算单位向量的方向
    double unitX = dx / lengthAH;
    double unitY = dy / lengthAH;
    
    // 根据distback正负确定B点在AH的同方向还是反方向
    // 并计算B点的坐标
    double Bx = A.x() + unitX * distback;
    double By = A.y() + unitY * distback;
    
    return CGeoPoint(Bx, By);
}

// 假设 CGeoPoint 和 CGeoLine 的定义如前所述
class Intercept {
public:
    Intercept(const CGeoPoint& O, const double& DIR, const CGeoPoint& A)
        : O(O), DIR(DIR), A(A), M(O, CGeoPoint(O.x() + std::cos(DIR), O.y() + std::sin(DIR))) {
        H = M.projection(A); // 计算垂足H并存储
        SOH = O.dist(H);
    }
    
    CGeoPoint FootH() const {
        return H; // 直接返回计算得到的垂足
    }

    CGeoPoint AHPFootH(double AHP) const {
        // 计算O到H的方向
        double SHP=A.dist(H)*tan(AHP);
        double ohDir = (H - O).dir();
        if(!DIRsame(DIR,ohDir)) {
            GDebugEngine::Instance()->gui_debug_msg(O,"O", COLOR_PURPLE);
            GDebugEngine::Instance()->gui_debug_msg(H,"H", COLOR_PURPLE);
            return backpos(H, O, SHP); 
        } else {
            GDebugEngine::Instance()->gui_debug_msg(O,"O", COLOR_YELLOW);
            GDebugEngine::Instance()->gui_debug_msg(H,"H", COLOR_YELLOW);
            return backpos(O, H, SOH + SHP);// 如果方向相反，延伸距离需要为负
        }
    }

    CGeoLine LineM() const {
        return M; // 直接返回计算得到的射线
    }

    double DistanceAH() const {
        return A.dist(H); // 直接返回A到H的距离
    }

    double DistanceOH() const {
        return SOH;
    }
    double OHDIR() const {
        return (H - O).dir();
    }

private:
    CGeoPoint O;
    double DIR;
    CGeoPoint A;
    CGeoLine M;
    CGeoPoint H;
    double SOH; // H到O的距离
};


double timeOH(double v0, double s) {
    double a = -1.93;
    double discriminant = v0 * v0 - 2 * a * (-s);
    if (discriminant < 0) {
        if (v0>0.5)
        {
        	return -v0/a;
        }

    }
    double t = (-v0 + std::sqrt(discriminant)) / a;
    return t;
}

double getdistback(const double& SAH, const double& TAH) {
	double maxa=4;
    double SF = 0.5 * maxa * std::pow(TAH, 2); // 使用std::pow进行幂运算
    if (SAH >= SF) {
        return 2 * SAH; // 假设这里是期望的返回逻辑
    } else if (0.5 * SF < SAH && SAH < SF) { // 分开进行比较
        double T2 = TAH * std::pow((SF - SAH) / (2 * SF), 0.5); // 再次使用std::pow
        return maxa * std::pow( (TAH - T2), 2); // 修改括号和幂运算
    }
    return SAH;
}
#include <cmath> // For std::sqrt, std::cos, and std::sin
#include <iostream>

// Assuming CGeoPoint and CGeoLine classes are defined as provided above



CTechDefence::CTechDefence() 
>>>>>>> 6fc00ba2d41d4c28fe68f1337005ac8fe1a66584
{
    CGeoPoint TPpos=TPptrs[i]->Pos();
    // std::cout<<"TPptrs["<<i<<"]->Pos()=("<<TPpos.x()<<","<<TPpos.y()<<")"<<std::endl;
    if (TPpos.dist(center)<35){
        // std::cout<<"CAR NUM CLOSE TO BALL CIRCLE IS:"<<TProlenums[i]<<"with index"<<i<<std::endl;
        return TProlenums[i];}
}
return -1;
}
CGeoPoint midpoint1(const CGeoPoint& A, const CGeoPoint& B) {return CGeoPoint((A.x() + B.x()) / 2.0, (A.y() + B.y()) / 2.0);}
CTechDefence::CTechDefence(){}

<<<<<<< HEAD
void CTechDefence::plan(const CVisionModule* pVision){
    CGeoPoint O1(75, -130);
    CGeoPoint O2(75, 130);
    CGeoPoint O3(-150, 0);
    GDebugEngine::Instance()->gui_debug_arc(O1, 30, 0, 360, COLOR_YELLOW);
    GDebugEngine::Instance()->gui_debug_arc(O2, 30, 0, 360, COLOR_YELLOW);
    GDebugEngine::Instance()->gui_debug_arc(O3, 30, 0, 360, COLOR_YELLOW);
//----------------------------------------------INITIALIZE ALL PLAYER INFOS AND BALL INFOS
    std::vector<const PlayerVisionT*> OPptrs;
    std::vector<const PlayerVisionT*> TPptrs;
    std::vector<int> OProlenums;
    std::vector<int>TProlenums;
    for (int irole = 0; irole <= Param::Field::MAX_PLAYER; ++irole){
        const PlayerVisionT& OPtmp = pVision->OurPlayer(irole);
        const PlayerVisionT& TPtmp = pVision->TheirPlayer(irole);
        if (OPtmp.Valid()){OPptrs.push_back(&OPtmp);OProlenums.push_back(irole);}
        if (TPtmp.Valid()){TPptrs.push_back(&TPtmp);TProlenums.push_back(irole);}}
    const BallVisionT& ball = pVision->Ball();
    CGeoPoint ballpos=ball.Pos();
//-------------------------------------------------CALCULATE WHICH CIRCLE TO FOCUS(RETURN CAR NUM)
    int focusNum=-1;//index from TPptrs
    for (int i = 0; i < 3; ++i)
    {
        if (centers[i].dist(ballpos)<40)
            {
                GDebugEngine::Instance()->gui_debug_msg(centers[i],"this circle has ball",COLOR_WHITE);
                focusNum=whichTPclose(TPptrs,TProlenums,centers[i]);
                // std::cout<<"TProlenums:[";for (int i : TProlenums) {std::cout << i << " ";}std::cout <<"]"<< std::endl;
                // std:cout<<"whichTPclose(TPptrs,TProlenums,centers[i])"<<"TPptrs[0]"
                // <<TPptrs[0]->Pos().y()<<"TPptrs[1]"<<TPptrs[1]->Pos().y()<<"TPptrs[2]"<<TPptrs[2]->Pos().y()
                // <<"centers[i]=("<<centers[i].x()<<","<<centers[i].y()<<")\n->"<<focusNum<<"\n";
                break;
            }
    }
    
    if (focusNum==-1){
        for (int i = 0; i < 3; ++i)
        {
            getcircledir(ballpos,centers[i],35);
            double qiexianA1=normalizeAngle1(qiexiandir[0]-M_PI);
            double qiexianA2=normalizeAngle1(qiexiandir[1]-M_PI);
            drawDir(ballpos,qiexianA1,to_string(qiexianA1).c_str());
            drawDir(ballpos,qiexianA2,to_string(qiexianA2).c_str());
            if (amidDir(qiexianA1,qiexianA2,ball.Vel().dir(),1,0)&&ball.Vel().mod()>50)
            {
                focusNum=whichTPclose(TPptrs,TProlenums,centers[i]);
                break;
            }
        }
    }
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, -100), ("focusnum:"+to_string(focusNum)).c_str(), COLOR_BLUE);
//-------------------------------------------------INITIALIZE STATE SWITCHING AND TASK
TaskT taskR1(task());
int rolenum=task().executor;
taskR1.executor=OProlenums[0];
CGeoPoint Jampos;
double DIR=0;
if (focusNum!=-1){
//-------------------------------------------------CALCULATE a,b,c,d,DIR,VR of the certain car num
    CGeoPoint A=TPptrs[findIndex(TProlenums,focusNum)]->Pos();
    DIR=TPptrs[findIndex(TProlenums,focusNum)]->Dir();
    // double VR=OPptrs[0]->RotVel();
    double VR=TPptrs[findIndex(TProlenums,focusNum)]->RotVel();
    CGeoPoint ORA(0,0);
    GDebugEngine::Instance()->gui_debug_msg(ORA, ("rotate velo" + std::to_string(VR)).c_str(), COLOR_RED);
    std::vector<int>TProlenumsR=TProlenums;
    eraseElement(TProlenumsR,focusNum);
    CGeoPoint A2=TPptrs[findIndex(TProlenums,TProlenumsR[0])]->Pos();
    CGeoPoint A3=TPptrs[findIndex(TProlenums,TProlenumsR[1])]->Pos();
    CGeoPoint O=ball.Pos();
    CGeoPoint M=midpoint1(A2,A3);
    CVector AM(M.x()-A.x(),M.y()-A.y());
    double b=AM.dir();
    double d=normalizeAngle1(b-M_PI);
    // auto ac=ball2circle(A,DIR,M,45*2,1);
    // double a=ac.first;
    // double c=ac.second;
    getcircledir(A,M,150);
    double a=normalizeAngle1(qiexiandir[0]-M_PI);
    double c=normalizeAngle1(qiexiandir[1]-M_PI);
// //-------------------------------------------------DEBUG INFOS
    // std::cout<<"OProlenums:[";for (int i : OProlenums) {std::cout << i << " ";}std::cout <<"]"<< std::endl;
    // std::cout<<"TProlenums:[";for (int i : TProlenums) {std::cout << i << " ";}std::cout <<"]"<< std::endl;
    // std::cout<<"TProlenumsR:[";for (int i : TProlenumsR) {std::cout << i << " ";}std::cout <<"]"<< std::endl;
    // std::cout<<"findIndex(TProlenums,TProlenumsR[1])="<<findIndex(TProlenums,TProlenumsR[1])<<std::endl;
    // std::cout<<"TPptrs[1] pos x="<<TPptrs[TProlenumsR[0]]->Pos().x()<<std::endl;
    // std::cout<<"b:{"<<b<<"};d{"<<d<<"};a{"<<a<<"};c{"<<c<<"}"<<std::endl;
    drawDir(A,a,"a");drawDir(A,b,"b");drawDir(A,c,"c");drawDir(A,d,"d");
//-------------------------------------------------GO TO WHICH ANGLE
    double JamAngle=gotoAngle(a,b,c,d,DIR,VR,A);
    drawDir(A,JamAngle,"JamAngle");
    Jampos=JamA2Jampos(A,JamAngle);
//-------------------------------------------------SET TASK 
    taskR1.player.pos=Jampos;
    taskR1.player.angle=normalizeAngle1(DIR-M_PI);
    // 
}else{
    // CVector ball2me = ball.Pos() - OPptrs[0]->Pos();
	// setSubTask(PlayerRole::makeItChaseKickV1(OProlenums[0],ball2me.dir()));
    taskR1.player.pos=OPptrs[0]->Pos();
=======
void CTechDefence::plan(const CVisionModule* pVision)
{
	TaskT taskR1(task());
	int rolenum=task().executor;
//----------------------------------------------INITIALIZE ALL PLAYER INFOS AND BALL INFOS
	std::vector<const PlayerVisionT*> OPptrs;
    std::vector<int> rolenums;
	for (int irole = 0; irole <= Param::Field::MAX_PLAYER; ++irole)
	{
		const PlayerVisionT& OPtmp=pVision->OurPlayer(irole);
		if (OPtmp.Valid())
		{
			OPptrs.push_back(&OPtmp);
            rolenums.push_back(irole);
		}
	}
	const BallVisionT& ball = pVision->Ball();//ball.Pos().x() ball().Pos().y()  ball.Vel().mod() ball.Vel().dir()
//----------------------------------------------PRINT ROLE NUM INFOS
    for (int i : rolenums) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout<<"task().executor"<<rolenum<<std::endl;
    taskR1.executor=rolenums[1];
// ---------------------------------------------PREPARE INPUTS FOR CLASS INTERCEPT 
	CGeoPoint O=ball.Pos(); // 射线的起点
    double DIR =ball.Vel().dir(); 
    CGeoPoint A=OPptrs[1]->Pos(); // 射线外的点A,应该先有一个谁快要接到球的判断车号，或踢球者也可以改这个谁快要接到球的车号
// ----------------------------------------------GET INFOS FROM CLASS INTERCEPT
    
    Intercept calculator(O, DIR, A);
    CGeoLine M = calculator.LineM(); 
    double VB=ball.Vel().mod()*0.01;
    double VOP=OPptrs[1]->Vel().mod()*0.01;
    double maxa=3;
    double SAH;
    double SOH;
    double TAH;
    double distback;
    double SF;
    double AHP=0;
    std::vector<double> SAHs;
    std::vector<double> SFs;
    CGeoPoint H;
// -----------------------------------------------WHETHER THERE IS ENOUGH TIME TO INTERCEPT THE BALL
    H=calculator.AHPFootH(0);
    SAH = A.dist(H)*0.01; // 获取A到H的距离
    SOH=O.dist(H)*0.01;
    TAH=timeOH(VB,SOH); 
    // double distback=getdistback(SAH,TAH);
    SF = 0.5 * maxa * std::pow(TAH, 2)+TAH*VOP;
    if (SAH>=SF-0.1) //添加车运动方向-->H 的限制
    {
// --------------------------------------------THERE IS NO AMPLE TIME TO INTERCEPT THE BALL.DECIDE ON THE INTERCEPT ANGLE
        distback=1000;
        for (AHP=0;AHP<M_PI/2;AHP+=0.1)
        {

            H=calculator.AHPFootH(AHP);
            SAH = A.dist(H)*0.01; // 获取A到H的距离
            SOH=O.dist(H)*0.01;
            TAH=timeOH(VB,SOH); 
            SF = 0.5 * maxa * std::pow(TAH, 2)+TAH*VOP;
            if (SAH+0.16<SF) //添加车运动方向-->H 的限制
            {
                break;   
            }
            SAHs.push_back(SAH);
            SFs.push_back(SF);
        }
    }else 
    {
        distback=0;
    }
//----------------------------------------------CALCULATE POINTBACK FROM DISTBACK.THE distback AND H ARE RENEWED
    CGeoPoint B= backpos(A,H,distback);
    taskR1.player.pos=B;
//----------------------------------------------PRINT ALL INFOS
    GDebugEngine::Instance()->gui_debug_msg(O,"O", COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(H,"HH", COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(A,"AAA", COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(B,"BBBB", COLOR_RED);
    CGeoPoint O0(0,0);
    CGeoPoint O1(0,20);
    CGeoPoint O2(0,40);
    CGeoPoint O3(0,60);
    CGeoPoint O4(0,80);
    CGeoPoint O5(0,100);
    CGeoPoint O6(0,120);
    CGeoPoint O7(0,140);
    CGeoPoint O8(0,160);
	GDebugEngine::Instance()->gui_debug_msg(O0, ("TAH: " + std::to_string(TAH)).c_str(), COLOR_RED);
	GDebugEngine::Instance()->gui_debug_msg(O1, ("SAH: " + std::to_string(SAH)).c_str(), COLOR_RED);
	GDebugEngine::Instance()->gui_debug_msg(O2, ("SF: " + std::to_string(SF)).c_str(), COLOR_RED);
	GDebugEngine::Instance()->gui_debug_msg(O3, ("VOP: " + std::to_string(VOP)).c_str(), COLOR_RED);
	GDebugEngine::Instance()->gui_debug_msg(O4, ("VB: " + std::to_string(VB)).c_str(), COLOR_RED);
	GDebugEngine::Instance()->gui_debug_msg(O5, ("SOH: " + std::to_string(SOH)).c_str(), COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(O6, ("AHP: " + std::to_string(AHP)).c_str(), COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(O7, ("DIR: " + std::to_string(DIR)).c_str(), COLOR_RED);
    GDebugEngine::Instance()->gui_debug_msg(O8, ("OHDIR: " + std::to_string(calculator.OHDIR())).c_str(), COLOR_RED);
   	GDebugEngine::Instance()->gui_debug_line(O,H,COLOR_WHITE);
   	GDebugEngine::Instance()->gui_debug_line(A,B,COLOR_WHITE);
    CGeoPoint A1(75,-130);
    CGeoPoint A2(75,130);
    CGeoPoint A3(-150,0);
    GDebugEngine::Instance()->gui_debug_arc(A1,30,0,360, COLOR_YELLOW);
    GDebugEngine::Instance()->gui_debug_arc(A2,30,0,360, COLOR_YELLOW);
    GDebugEngine::Instance()->gui_debug_arc(A3,30,0,360, COLOR_YELLOW);
    for (double iSAH:SAHs)
    {
        
        GDebugEngine::Instance()->gui_debug_msg(B,"BBBB", COLOR_RED);
    }

//----------------------------------------------SET SUB TASKS
	setSubTask(TaskFactoryV2::Instance()->GotoPosition(taskR1));//将taskR1给走位subtask执行
    
	CStatedTask::plan(pVision);
>>>>>>> 6fc00ba2d41d4c28fe68f1337005ac8fe1a66584
}
setSubTask(TaskFactoryV2::Instance()->GotoPosition(taskR1));//将taskR1给走位subtask执行
CStatedTask::plan(pVision);}
CTechDefence::~CTechDefence() {}

CPlayerCommand* CTechDefence::execute(const CVisionModule* pVision)
{if (subTask()){return subTask()->execute(pVision);} return NULL;}
