#include "GoaliePosV1.h"
#include <GDebugEngine.h>
#include "ShootRangeList.h"

#include "TaskMediator.h"
#include "ValueRange.h"
#include <vector>
#include <random>
#include <math.h>
#include "BestPlayer.h"
#include <map>

#define DEBUGGING
#ifdef DEBUGGING
#define DBG_BOOL(y,var) {if(var)GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,y), #var"=true");else GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,y), #var"=false");}
#else
#define DBG_BOOL(y,var) {}
#define DBG_MSG(msg,)
#endif

CGoaliePosV1::CGoaliePosV1()
{

}

int CGoaliePosV1::GetNearestEnemy(const CVisionModule *pVision)
{
    CGeoPoint goal_center(- Param::Field::PITCH_LENGTH / 2, 0);
    double nearest_dist = Param::Field::PITCH_LENGTH;
    int enemy_num = 1;
    for (int i = 0; i < Param::Field::MAX_PLAYER; i ++)
    {
        if (pVision->TheirPlayer(i).Valid() == true)
        {
            if (pVision->TheirPlayer(i).Pos().dist(goal_center) < nearest_dist)
            {
                nearest_dist = pVision->TheirPlayer(i).Pos().dist(goal_center);
                enemy_num = i;
            }
        }
    }
    return enemy_num;
}
CGeoPoint CGoaliePosV1::GetPenaltyShootPos(const CVisionModule *pVision)
{
    const BallVisionT ball = pVision->Ball();
    const PlayerVisionT& enemy = pVision->TheirPlayer(this->GetNearestEnemy(pVision));
    double enemy_dir = enemy.Dir();
    CGeoLine enemy_sht_line(enemy.Pos(), enemy.Pos() + Utils::Polar2Vector(10, enemy_dir));
    if (enemy_dir < Param::Math::PI / 2 && enemy_dir > - Param::Math::PI / 2)
    {
        enemy_sht_line = CGeoLine(ball.Pos(), ball.Pos() + Utils::Polar2Vector(10, Param::Math::PI));
    }
    // 不应该用加大的球门 [6/15/2011 zhanfei]
    const double goalie_x = Param::Vehicle::V2::PLAYER_SIZE + 1;
    const CGeoLine goal_line(CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + goalie_x, Param::Field::GOAL_WIDTH / 2)
        , CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + goalie_x, -Param::Field::GOAL_WIDTH / 2));
    const CGeoLineLineIntersection lli(enemy_sht_line, goal_line);
    CGeoPoint pen_sht_pos;
    if (lli.Intersectant() == false)
    {
        pen_sht_pos = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
    }
    else
    {
        pen_sht_pos = lli.IntersectPoint();
    }
    const double GOAL_BUFFER = -3;
    if (pen_sht_pos.y() < -Param::Field::GOAL_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE - GOAL_BUFFER)
    {
        pen_sht_pos = CGeoPoint(pen_sht_pos.x(), -Param::Field::GOAL_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE - GOAL_BUFFER);
    }
    else if (pen_sht_pos.y() > Param::Field::GOAL_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE + GOAL_BUFFER)
    {
        pen_sht_pos = CGeoPoint(pen_sht_pos.x(), Param::Field::GOAL_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE + GOAL_BUFFER);
    }
    return pen_sht_pos;
}
CGeoPoint CGoaliePosV1::GetPenaltyShootPosV2(const CVisionModule *pVision)
{
    const BallVisionT ball = pVision->Ball();
    const PlayerVisionT& enemy = pVision->TheirPlayer(this->GetNearestEnemy(pVision));
    double enemy_dir = enemy.Dir();

    int GoalBuffer = 2;
    double Ball2LeftDir = (CGeoPoint(-Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2 + GoalBuffer) - ball.Pos()).dir();
    double Ball2RightDir =( CGeoPoint(-Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2 - GoalBuffer) - ball.Pos()).dir();
    bool BallSpeed = (ball.Vel().mod() >= 30);
    bool outOfShooter=true;
//    bool outOfShooter = !(DefenceInfo::Instance()->getBallTaken());
    bool BallDirLimit = !Utils::InBetween(ball.Vel().dir(), Ball2LeftDir - Param::Math::PI * 10 / 180 , Ball2RightDir + Param::Math::PI * 10 / 180);
    bool BallShot = BallSpeed && outOfShooter && BallDirLimit;
//    bool enemyHasShot =enemy.Pos().dist(ball.Pos()) < 40
//        && Utils::InBetween(Utils::Normalize((ball.Pos() - enemy.Pos()).dir() + Param::Math::PI), Ball2LeftDir - Param::Math::PI * 10 / 180, Ball2RightDir + Param::Math::PI * 10 / 180)
//        && BallSpeed && outOfShooter && ball.VelX() < 0;
//    BallShot = BallShot || enemyHasShot;
    DBG_BOOL(-300,BallSpeed);
    DBG_BOOL(-350, outOfShooter);
    DBG_BOOL(-400, BallDirLimit);
//    DBG_BOOL(-250, enemyHasShot);


    const double goalie_x = Param::Vehicle::V2::PLAYER_SIZE + 1;
    CGeoPoint pen_sht_pos;

    if (BallShot) {
        CGeoLine ball_line(ball.Pos(),ball.Pos()+Utils::Polar2Vector(10,ball.Vel().dir()));
        const CGeoLine goal_line(CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + goalie_x, Param::Field::GOAL_WIDTH / 2)
            , CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + goalie_x, -Param::Field::GOAL_WIDTH / 2));
        const CGeoLineLineIntersection lli(ball_line, goal_line);
        if (lli.Intersectant() == false)
        {
            pen_sht_pos = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
        } else
        {
            pen_sht_pos = lli.IntersectPoint();
        }
    } else {
        CGeoLine enemy_sht_line(enemy.Pos(), enemy.Pos() + Utils::Polar2Vector(10, enemy_dir));
        if (enemy_dir < Param::Math::PI / 2 && enemy_dir > -Param::Math::PI / 2)
        {
            enemy_sht_line = CGeoLine(ball.Pos(), ball.Pos() + Utils::Polar2Vector(10, Param::Math::PI));
        }
        const CGeoLine goal_line(CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + goalie_x, Param::Field::GOAL_WIDTH / 2)
            , CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + goalie_x, -Param::Field::GOAL_WIDTH / 2));
        const CGeoLineLineIntersection lli(enemy_sht_line, goal_line);
        if (lli.Intersectant() == false)
        {
            pen_sht_pos = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
        } else
        {
            pen_sht_pos = lli.IntersectPoint();
        }
        const double GOAL_BUFFER = -10;
        if (pen_sht_pos.y() < -Param::Field::GOAL_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE - GOAL_BUFFER)
        {
            pen_sht_pos = CGeoPoint(pen_sht_pos.x(), -Param::Field::GOAL_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE - GOAL_BUFFER);
        } else if (pen_sht_pos.y() > Param::Field::GOAL_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE + GOAL_BUFFER)
        {
            pen_sht_pos = CGeoPoint(pen_sht_pos.x(), Param::Field::GOAL_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE + GOAL_BUFFER);
        }
    }
    return pen_sht_pos;
}

CGeoPoint CGoaliePosV1::GetPenaltyShootPosV3(const CVisionModule *pVision)
{
    const BallVisionT ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(0);
    const PlayerVisionT& enemy = pVision->TheirPlayer(this->GetNearestEnemy(pVision));
    double enemy_dir = enemy.Dir();

    int GoalBuffer = 2;
    double Ball2LeftDir = (CGeoPoint(-Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2 + GoalBuffer) - ball.Pos()).dir();
    double Ball2RightDir = (CGeoPoint(-Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2 - GoalBuffer) - ball.Pos()).dir();
    bool BallSpeed = (ball.Vel().mod() >= 10);
    bool outOfShooter = true;
//    bool outOfShooter = !(DefenceInfo::Instance()->getBallTaken());
    bool BallDirLimit = !Utils::InBetween(ball.Vel().dir(), Ball2LeftDir - Param::Math::PI * 10 / 180, Ball2RightDir + Param::Math::PI * 10 / 180);
    bool BallShot = BallSpeed && outOfShooter && BallDirLimit;
//    bool enemyHasShot = enemy.Pos().dist(ball.Pos()) < 40
//        && Utils::InBetween(Utils::Normalize((ball.Pos() - enemy.Pos()).dir() + Param::Math::PI), Ball2LeftDir - Param::Math::PI * 10 / 180, Ball2RightDir + Param::Math::PI * 10 / 180)
//        && BallSpeed && outOfShooter && ball.VelX() < 0;
    BallShot = BallShot;
    DBG_BOOL(-300, BallSpeed);
    DBG_BOOL(-350, outOfShooter);
    DBG_BOOL(-400, BallDirLimit);
//    DBG_BOOL(-250, enemyHasShot);


    const double goalie_x = Param::Vehicle::V2::PLAYER_SIZE + 1;
    CGeoPoint pen_sht_pos;

    if (BallShot) {
        CGeoLine ball_line(ball.Pos(), ball.Pos() + Utils::Polar2Vector(10, ball.Vel().dir()));
        const CGeoLine goal_line(CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + goalie_x, Param::Field::GOAL_WIDTH / 2)
            , CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + goalie_x, -Param::Field::GOAL_WIDTH / 2));
        const CGeoLineLineIntersection lli(ball_line, goal_line);
        if (lli.Intersectant() == false)
        {
            pen_sht_pos = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
        } else
        {
            pen_sht_pos = lli.IntersectPoint();
        }
        GDebugEngine::Instance()->gui_debug_x(pen_sht_pos,COLOR_ORANGE);
        pen_sht_pos=pen_sht_pos+Utils::Polar2Vector(30,(pen_sht_pos-me.Pos()).dir());
        GDebugEngine::Instance()->gui_debug_x(pen_sht_pos,COLOR_RED);
    } else {
        int random_num=5;
        vector<CGeoPoint> random_points;
        for (int i = 1; i <= random_num; i++) {
            double y = Param::Field::GOAL_WIDTH*(0.5-double(i)/double(random_num+1));
            random_points.push_back(CGeoPoint(-Param::Field::PITCH_LENGTH/2,y));
        }

        CGeoLine enemy_sht_line(enemy.Pos(), enemy.Pos() + Utils::Polar2Vector(10, enemy_dir));
        if (enemy_dir < Param::Math::PI / 2 && enemy_dir > -Param::Math::PI / 2)
        {
            enemy_sht_line = CGeoLine(ball.Pos(), ball.Pos() + Utils::Polar2Vector(10, Param::Math::PI));
        }
        const CGeoLine goal_line(CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + goalie_x, Param::Field::GOAL_WIDTH / 2)
            , CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + goalie_x, -Param::Field::GOAL_WIDTH / 2));
        const CGeoLineLineIntersection lli(enemy_sht_line, goal_line);
        if (lli.Intersectant() == false)
        {
            pen_sht_pos = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
        } else
        {
            pen_sht_pos = lli.IntersectPoint();
        }
        const double GOAL_BUFFER = -10;
        if (pen_sht_pos.y() < -Param::Field::GOAL_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE - GOAL_BUFFER)
        {
            pen_sht_pos = CGeoPoint(pen_sht_pos.x(), -Param::Field::GOAL_WIDTH / 2 + Param::Vehicle::V2::PLAYER_SIZE - GOAL_BUFFER);
        } else if (pen_sht_pos.y() > Param::Field::GOAL_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE + GOAL_BUFFER)
        {
            pen_sht_pos = CGeoPoint(pen_sht_pos.x(), Param::Field::GOAL_WIDTH / 2 - Param::Vehicle::V2::PLAYER_SIZE + GOAL_BUFFER);
        }
        GDebugEngine::Instance()->gui_debug_x(pen_sht_pos,COLOR_RED);
        //random
        std::default_random_engine generator{(unsigned int)pVision->Cycle()};
        vector<int> weight_vector;
        for (auto p : random_points) {
            weight_vector.push_back(100000 / sqrt(pen_sht_pos.dist(p)));
        }
        std::discrete_distribution<int> weight(weight_vector.begin(),weight_vector.end());
        int x = weight(generator);
#ifdef DEBUGGING
        printf("cycle: %d size of random_points: %d\tsize of weight_vector: %d\nweights: ",pVision->Cycle(),random_points.size(),weight_vector.size());
        for (auto w : weight_vector)
            printf("%d ", w);
        printf("\nx= %d\n", x);
#endif
        pen_sht_pos = random_points[x];
    }
    return pen_sht_pos;
}
