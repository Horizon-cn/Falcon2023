// Intercept.h
#pragma once

#include <cmath> // For std::sqrt, std::cos, and std::sin
#include "geometry.h"

class Intercept {
public:
    Intercept(const CGeoPoint& O, const double& DIR, const CGeoPoint& A);
    
    CGeoPoint FootH() const;
    CGeoLine LineM() const;
    double DistanceAH() const;
    double DistanceOH() const;

private:
    CGeoPoint O;
    double DIR;
    CGeoPoint A;
    CGeoLine M;
    CGeoPoint H;
    double AHdist; // 注意：这个成员变量在您提供的代码中已声明但未使用
};

// 函数声明
double timeOH(double v0, double s);
double getdistback(const double& SAH, const double& TAH);
CGeoPoint backpos(const CGeoPoint& A, const CGeoPoint& H, double distback);
