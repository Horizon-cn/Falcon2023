#ifndef CM_MOTION_H
#define CM_MOTION_H
#include <WorldModel/WorldDefine.h>
//inline bool finite(double num)
//{
//	return fabs(num)<9999;
//}

static CVector last_csy_command(0.0, 0.0);

enum nonZeroMode {
    FAST,
    ACCURATE
};

enum planType {
    MOVE_X,
    MOVE_Y,
    ROTATE
};

float motion_time_1d(float dx,float vel0,float vel1,
					 float max_vel,float max_accel,
					 float &t_accel,float &t_cruise,float &t_decel);
void compute_motion_1d(double x0, double v0, double v1,
                       double a_max, double d_max, double v_max, double a_factor, double vel_factor,
                       double &traj_accel, double &traj_time, double &traj_time_acc, double &traj_time_dec, double &traj_time_flat, planType pT, nonZeroMode mode = FAST);
void compute_motion_1d_test(double x0, double v0, double v1,
	double a_max, double d_max, double v_max, double a_factor, double vel_factor,
	double& traj_accel, double& traj_time, double& traj_time_acc, double& traj_time_dec, double& traj_time_flat, planType pT, nonZeroMode mode = FAST);
void compute_motion_2d(CVector x0, CVector v0, CVector v1,
					   double a_max, double d_max, double v_max, double a_factor,
                       CVector &traj_accel, double &time, double &time_acc, double &time_dec, double &time_flat, nonZeroMode mode = FAST);
void compute_motion_2d_test(CVector x0, CVector v0, CVector v1,
					   double a_max, double d_max, double v_max, double selfDir, double vx_max, double vy_max, double a_factor,
					   CVector& traj_accel, double& time, double& time_acc, double& time_dec, double& time_flat, nonZeroMode mode = FAST, bool IsGoMiddle = false);

double compute_stop(double v, double max_a);
void goto_point_omni( const PlayerVisionT& start,
					 const PlayerVisionT& final,
					 const PlayerCapabilityT& capability,
					 const double& accel_factor,
					 const double& angle_accel_factor,
					 PlayerVisionT& nextStep,
                     nonZeroMode mode = FAST);

void goto_point_omni_test(const PlayerVisionT& start,
	const PlayerVisionT & final,
	const PlayerCapabilityT& capability,
	const double& accel_factor,
	const double& angle_accel_factor,
	PlayerVisionT& nextStep,
	nonZeroMode mode = FAST, bool IsGoMiddle = false);

double expectedCMPathTime(const PlayerVisionT& start, const CGeoPoint& final, PlayerCapabilityT capability, CVector target_vel, double accel_factor, bool IsGoMiddle);
double predictedTime(const PlayerVisionT& start, const CGeoPoint& Target, const CVector& targetVel = CVector(0, 0));
double predictedTimeWithRawVel(const PlayerVisionT& start, const CGeoPoint & Target, const CVector& targetVel = CVector(0, 0));
double predictedTheirTime(const PlayerVisionT& start, const CGeoPoint& Target, const CVector& targetVel = CVector(0, 0));
double predictedTime2d(const PlayerVisionT& start, const CGeoPoint& final, double maxAccel, double maxVelocity, double accel_factor);
double predictedTime1d(const double& start, const double& end, const double& startVel, const double& maxAccel, const double& maxVelocity, const double endVel = 0);
bool predictRushSpeed(const PlayerVisionT& start, const CGeoPoint& final, const double& time, const PlayerCapabilityT& capability, CVector& targetVel);

void openSpeedCircle(const PlayerVisionT& start, const double dist2Center, const int rotateMethod, const double finalAngle, PlayerVisionT& nextStep, const double dirDiff = 0.0);


#endif
