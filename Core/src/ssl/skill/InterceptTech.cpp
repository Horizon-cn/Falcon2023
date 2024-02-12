// Intercept.cpp
#include "InterceptTech.h" 

// Intercept 类的构造函数
Intercept::Intercept(const CGeoPoint& O, const double& DIR, const CGeoPoint& A) 
    : O(O), DIR(DIR), A(A), M(O, CGeoPoint(O.x() + std::cos(DIR), O.y() + std::sin(DIR))) {
    H = M.projection(A); // 计算垂足H并存储
}

// 返回垂足H的坐标
CGeoPoint Intercept::FootH() const {
    return H;
}

// 返回射线M
CGeoLine Intercept::LineM() const {
    return M;
}

// 返回A到H的距离
double Intercept::DistanceAH() const {
    return A.dist(H);
}

// 返回O到H的距离
double Intercept::DistanceOH() const {
    return O.dist(H);
}

// 计算从O到H的时间
double timeOH(double v0, double s) {
    double a = -1.93;
    double discriminant = v0 * v0 - 2 * a * (-s);
    if (discriminant < 0) {
        // 这里处理无解的情况
        return (v0 > 0.5) ? 0.1 : -1; // 假设无解时返回-1
    }
    double t = (-v0 + std::sqrt(discriminant)) / a;
    return t;
}

// 根据SAH和TAH计算distback
double getdistback(const double& SAH, const double& TAH) {
    double maxa = 4;
    double SF = 0.5 * maxa * std::pow(TAH, 2);
    if (SAH >= SF) {
        return 2 * SAH;
    } else if (0.5 * SF < SAH && SAH < SF) {
        double T2 = TAH * std::pow((SF - SAH) / (2 * SF), 0.5);
        return maxa * std::pow((TAH - T2), 2);
    }
    return SAH;
}

// 根据A, H和distback计算B点的位置
CGeoPoint backpos(const CGeoPoint& A, const CGeoPoint& H, double distback) {
    double dx = H.x() - A.x();
    double dy = H.y() - A.y();
    double lengthAH = std::sqrt(dx * dx + dy * dy);
    double unitX = dx / lengthAH;
    double unitY = dy / lengthAH;
    double Bx = A.x() + unitX * distback;
    double By = A.y() + unitY * distback;
    return CGeoPoint(Bx, By);
}
