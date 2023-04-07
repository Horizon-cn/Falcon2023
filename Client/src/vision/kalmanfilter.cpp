#define _USE_MATH_DEFINES
#include "kalmanfilter.h"
#include "parammanager.h"
#include <iostream>
#include <math.h>

namespace {
    auto vpm = Owl::VParamManager::Instance();
}

KalmanFilter::KalmanFilter(int _stateNum, int _measNum, int _ctrlNum):
    ifInit(false),
    stateNum(_stateNum),
    measNum(_measNum),
    ctrlNum(_ctrlNum) 
{
    K(_stateNum, _measNum);
    //P(4,4);
    P = Matrix2d::createIdentity(_stateNum) * 5;
    x(_stateNum, 1);
    A = Matrix2d::createIdentity(_stateNum);
    Q = Matrix2d::createIdentity(_stateNum) * 0.4;
    //Q(Matrix2d::createIdentity(4) * 0.2);
    H = Matrix2d::createIdentity(_measNum, _stateNum);
    R = Matrix2d::createIdentity(_measNum) * 10;
    //R(Matrix2d::createIdentity(2) * 20);
    B = Matrix2d::createIdentity(_stateNum, _ctrlNum);
    x_(_stateNum, 1);
    P_(_stateNum, _stateNum);
    z(_measNum, 1);
}

KalmanFilter::~KalmanFilter() {

}
/**
 * @brief init Kalman filter
 * @param px
 * @param py
 * @param vx
 * @param vy
 */
void KalmanFilter::init(double px, double py, double vx, double vy) {
    this->x = Matrix2d(stateNum, 1, { px, py, vx, vy });
    this->K  = Matrix2d(stateNum, measNum);
    this->P  = Matrix2d::createIdentity(stateNum) * 5;
    A(0, 2) = A(1, 3) = 1;
    ifInit = true;
}

void KalmanFilter::init(Matrix2d m) {
    this->x = m;
    ifInit = true;
}

/**
 * @brief update module of Kalman filter
 * @param px
 * @param py
 * @return
 */
const Matrix2d& KalmanFilter::update(double px, double py) {
    if (ifInit == false) {
        ifInit = true;
        init(px, py, 0, 0);
    }
    z = Matrix2d(2, 1, { px, py });
    x_ = A * x;   // 因为update一直跟着predict，所以不用考虑输入 ？？？？
    P_ = A * P * A.transpose() + Q;
    K  = P_ * H.transpose() * ((H * P_ * H.transpose() + R).inverse());
    x  = x_ + K * (z - H * x_);
    P  = P_ - K * H * P_;
    return x;
}

void KalmanFilter::_predict(Matrix2d ctrlMat){
    x_ = A * x + B * ctrlMat;
    P_ = A * P * A.transpose() + Q;
}

void KalmanFilter::_update2(Matrix2d measMat){
    K  = P_ * H.transpose() * ((H * P_ * H.transpose() + R).inverse());
    x  = x_ + K * (measMat - H * x_);
    P  = P_ - K * H * P_;
}

/**
 * @brief not update just follow
 * @param px
 * @param py
 * @return
 */
const Matrix2d& KalmanFilter::follow(double px, double py) {
    if (vpm->ballFollowProp < 0 || vpm->ballFollowProp > 1) vpm->updateParam(vpm->ballFollowProp, "Kalman/ballFollowProp", 1, true);
    x = Matrix2d(4, 1, { z(0, 0), z(1, 0), vpm->ballFollowProp * (px - z(0, 0)) + (1-vpm->ballFollowProp) * x(2, 0), vpm->ballFollowProp * (py - z(1, 0)) + (1-vpm->ballFollowProp) * x(3, 0) });
    return update(px, py);
}

void KalmanFilter::setTransitionMat(double dt){
    A.createIdentity(stateNum);
    B = Matrix2d::createIdentity(stateNum, ctrlNum);
    for (int i=0; i < stateNum/2; i++) A(i, i+stateNum/2) = dt;
    for (int i=0; i < stateNum/2; i++) {
        B(i, i) = 0.5 * pow(dt,2);
        B(i+stateNum/2, i) = dt;
    }
    setModelErrorMat(modelErr, dt);
}

void KalmanFilter::setCovarianceMat(double cov){
    P.createIdentity(stateNum)*cov;
}

void KalmanFilter::setMeasErrorMat(double err){
    R.Matrix2d::createIdentity(measNum)*err;
}

void KalmanFilter::setControlMat(double ctrl) {

}

void KalmanFilter::setModelErrorMat(double err, double dt){
    double sigma_2 = 3 * err * pow(dt, -3);
    double dt3 = pow(dt, 3) * sigma_2 / 3;
    double dt2 = pow(dt, 2) * sigma_2 / 2;
    double dt1 = dt * sigma_2;
    for(int i = 0; i < stateNum; i++){
        Q(i, i) = i < stateNum / 2? dt3: dt1;
        if(i < stateNum / 2) Q(i, i + stateNum / 2) = Q(i + stateNum / 2, i) = dt2;
    }
}

/************************************************************************/
/*                        Pos Filter                                 */
/************************************************************************/
PosFilter::PosFilter(double _initCov, double _measErr, double _modelErr) : KalmanFilter(4, 2, 2) {
    setCovarianceMat(_initCov);
    setMeasErrorMat(_measErr);
    modelErr = _modelErr;
}

void PosFilter::initState(double px, double py, double vx, double vy) {
    this->x = Matrix2d(stateNum, 1, { px, py, vx, vy });
    init(x);
}

void PosFilter::predict(double ux, double uy){
    Matrix2d u;
    u = Matrix2d(ctrlNum, 1, {ux, uy});
    _predict(u);
//    qDebug()<<"A";
//    for(int i=0;i<4;i++){
//        qDebug()<<A(i,0)<<A(i,1)<<A(i,2)<<A(i,3);
//    }
//    qDebug()<<"P_";
//    for(int i=0;i<4;i++){
//        qDebug()<<P_(i,0)<<P_(i,1)<<P_(i,2)<<P_(i,3);
//    }
}

void PosFilter::predict2(double ux, double uy){
    Matrix2d u;
    u = Matrix2d(ctrlNum, 1, {ux, uy});
    x_ = A * x + B * u;
    P_ = A * P * A.transpose() + Q;
}

void PosFilter::update2(double zx, double zy){
    z = Matrix2d(ctrlNum, 1, { zx, zy });
    _update2(z);
}

/**CGeoPoint PosFilter::predictedPos(double t) const{
    if(t == 0) t = lastTimestamp;
    return postEstimatedPos() + postEstimatedVel()*(t-lastTimestamp);
}**/

/************************************************************************/
/*                        Dir Filter                                 */
/************************************************************************/
DirFilter::DirFilter(double _initCov, double _measErr, double _modelErr) : KalmanFilter(2, 1, 1) {
    setCovarianceMat(_initCov);
    setMeasErrorMat(_measErr);
    modelErr = _modelErr;
}

void DirFilter::initState(double angle, double rotVel) {
    this->x = Matrix2d(stateNum, 1, { angle, rotVel });
    init(x);
}

void DirFilter::predict(double ur){
    Matrix2d u;
    u = Matrix2d(ctrlNum, 1, {ur});
    _predict(u);
}

void DirFilter::predict2(double ur){
    Matrix2d u;
    u = Matrix2d(ctrlNum, 1, {ur});
    x_ = A * x + B * u;
    P_ = A * P * A.transpose() + Q;
}

void DirFilter::update2(double ang){
//    double temp = ang > x(0,0) ? -2 * M_PI : 2 * M_PI;
//    while (std::abs(ang - x(0,0)) > M_PI) ang += temp;
    z = Matrix2d(ctrlNum, 1, {ang});
    _update2(z);
}

/**double DirFilter::predictedDir(double t) const{
    if(t == 0) t = lastTimestamp;
    return postEstimatedDir() + postEstimatedVel()*(t-lastTimestamp);
}**/

double DirFilter::normalize(double angle) {
    if (fabs(angle) > 10 ) {
        std::cout << angle << " Normalize Error" << std::endl;
        return 0;
    }
    const double M_2PI = M_PI * 2;
    // 快速粗调整
    angle -= (int)(angle / M_2PI) * M_2PI;

    // 细调整 (-PI,PI]
    while( angle > M_PI ) {
        angle -= M_2PI;
    }

    while( angle <= -M_PI ) {
        angle += M_2PI;
    }

    return angle;
}
