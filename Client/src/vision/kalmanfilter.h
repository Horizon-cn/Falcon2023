#ifndef KALMANFILTER_H
#define KALMANFILTER_H
#include "matrix2d.h"
#include "geometry.h"
#include <QTime>

/**
 * @brief The KalmanFilter class
 */
class  KalmanFilter {
  public:
    KalmanFilter(int, int, int);
    ~KalmanFilter();

    void init(Matrix2d);
    void init(double, double, double, double);

    void _predict(Matrix2d);
    void _update2(Matrix2d);

    const Matrix2d& update(double, double);
    const Matrix2d& update(CGeoPoint pos) {
        return update(pos.x(), pos.y());
    }
    const Matrix2d& follow(double, double);
    const Matrix2d& follow(CGeoPoint pos) {
        return follow(pos.x(), pos.y());
    }
    Matrix2d& getP(){return P;}
    Matrix2d& getQ(){return Q;}
    void set(int num, double data){
        x(num, 0) = data;
    }

    double lastTimestamp = 0;
    //QTime lastTimestamp = QTime::currentTime();
    bool isInit() {return ifInit;}
    void setTransitionMat(double);

  protected:
    Matrix2d K;
    Matrix2d P;
    Matrix2d x;
    Matrix2d A;
    Matrix2d Q;
    Matrix2d H;
    Matrix2d R;
    Matrix2d B;
    Matrix2d x_;
    Matrix2d P_;
    Matrix2d z;
    bool ifInit;
    int stateNum, measNum, ctrlNum;
    double modelErr;
    void setCovarianceMat(double);
    void setMeasErrorMat(double);
    void setModelErrorMat(double, double);
    void setControlMat(double);
};

class PosFilter : public KalmanFilter{
  public:
    PosFilter() : KalmanFilter(4, 2, 2) {}
    PosFilter(double, double, double);
    void initState(double, double, double, double);
    void initState(CGeoPoint p, CVector v){
        initState(p.x(), p.y(), v.x(), v.y());
    }
    void predict(double ux = 0, double uy = 0);
    void predict2(double ux, double uy);
    void predict2(CVector up){
        predict2(up.x(), up.y());
    }
    void update2(double zx, double zy);
    void update2(CGeoPoint p){
        update2(p.x(), p.y());
    }
    void update4(CGeoPoint p, CGeoPoint v) {

    }

    const Matrix2d & postEstimatedState() const{return x;} 
    CGeoPoint postEstimatedPos() const{return CGeoPoint(x(0,0),x(1,0));}
    CVector postEstimatedVel() const{return CVector(x(2,0),x(3,0));}
    CVector postErrorCovPos() const{return CVector(sqrt(P(0,0)), sqrt(P(1,1)));}
    CVector postErrorCovVel() const{return CVector(sqrt(P(2,2)), sqrt(P(3,3)));}
    CGeoPoint priorEstimatedPos() const{return CGeoPoint(x_(0,0),x_(1,0));}
    CVector priorEstimatedVel() const{return CVector(x_(2,0),x_(3,0));}
    CGeoPoint predictedPos(double t = 0) const;
    CVector predictedVel() const{return CVector(x(2,0),x(3,0));}
};

class DirFilter : public KalmanFilter{
  public:
    DirFilter() : KalmanFilter (2, 1, 1) {}
    DirFilter(double, double, double);
    void initState(double, double rotVel = 0);
    
    void predict(double ur = 0);
    void predict2(double ur);
    void update2(double ang);
    double normalize(double angle);

    double postEstimatedDir() const {return x(0,0);}
    double postEstimatedVel() const {return x(1,0);}
    double postErrorCovDir() const {return sqrt(P(0,0));}
    double postErrorCovVel() const {return sqrt(P(1,1));}
    double priorEstimatedDir() const{ return x_(0,0);}
    double priorEstimatedVel() const{ return x_(1,0);}
    double predictedDir(double t) const;
    double predictedVel() const {return x(1,0);}
};

#endif // KALMANFILTER_H
