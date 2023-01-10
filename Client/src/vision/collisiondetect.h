#ifndef COLLISIONDETECT_H
#define COLLISIONDETECT_H
#include "singleton.h"
#include "globaldata.h"
#include "geometry.h"
#include "staticparams.h"

#define DETECT_DIST 300 //detect whether the ball in 300mm of vechile
#define SPLIT_THRESHOLD 20  //split
#define NEAR_VECHILE_MIN_FRAME 5 //keep frame to detect ball SLIGHTLY touch vechile
#define LENGTH_THERESHOLD 5800
#define WIDTH_THERESHOLD 4400
#define MAX_FRAME_NUM 20    //split and merge frame num
#define SPLIT_THRESHOLD 20  //split
#define CHIP_DIS 10
class CCollisionDetect {
  public:
    CCollisionDetect();
    //virtual ~CCollisionDetect();
    void visionAlart();
    void ballRobotCollision(Owl::ReceiveVisionMessage & result); //小车与球碰撞，分析球的状态 如果要分析车与球的位置，须知道迭代时间，线性预测
    bool ballCloseEnough2Analyze(int);
    bool ballIsOnEdge(CGeoPoint);
    bool robotsCollision(Owl::ReceiveVisionMessage& result); //两小车相撞
    void setCheckNum(int side, int robotID);
    void clearLastResult(int side);

  private:
    int LinePoint[MAX_FRAME_NUM];
    int _RecordFlag = 0;
    int _RecordIndex = -1;
    int PointN;
    //int LastTouch=0;//0 for struggle; 1 for our ;2 for their; 3 for wall;
    int our_collision[PARAM::ROBOTMAXID]; //和我方相撞的车号
    int opp_collision[PARAM::ROBOTMAXID];
    int current_check_num; //确定车号
    int current_check_side; //确定队伍

};
typedef Falcon::MeyersSingleton<CCollisionDetect> CollisionDetect;

#endif // COLLISIONDETECT_H
