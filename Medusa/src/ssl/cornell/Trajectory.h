#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "TrajectoryStructs.h"
#include <WorldModel/WorldDefine.h>

double distance(double x1, double y1, double x2, double y2);

//=================================================
// TIMING FUNCTIONS

double expectedPathTime( const PlayerVisionT& start, const CGeoPoint& final, double maxAccel, double maxVelocity );

double expectedFastPathTime( const PlayerVisionT& start, const CGeoPoint& final, double maxAccel, double maxVelocity );

// 考虑平动和朝向的到点时间估计
double expectedFullPathTime(const PlayerVisionT& start,
							const PlayerVisionT& final,
							double frameRate,
							const PlayerCapabilityT& capability);
//=================================================
// TRAJECTORY GENERATION FUNCTIONS

void zeroFinalVelocityPath( const PlayerVisionT& start,
                            const PlayerVisionT& final,
                            double frameRate,
                            const PlayerCapabilityT& capability,
						    PlayerVisionT& nextStep
                          );

void fastPath( const PlayerVisionT& start,
               const PlayerVisionT& final,
               double frameRate,
               const PlayerCapabilityT& capability,
	           PlayerVisionT& nextStep,
			   const double finalVelDir = 0  
			);

//=================================================
// TRAJECTORY GENERATION FUNCTIONS

double zeroFinalVelocityTheta(const PlayerVisionT& start,
							  const PlayerVisionT& final,
							  double frameRate,
							  const PlayerCapabilityT& capability
							  );

//=================================================
// PROPORTIONAL GAIN FUNCTIONS

void proportionalGainPath(const PlayerVisionT& start,
                          const PlayerVisionT& final,
                          double frameRate,
                          const PlayerCapabilityT& capability,
						  PlayerVisionT& nextStep
                         );


double proportionalGainTheta(const PlayerVisionT& start,
                           const PlayerVisionT& final,
                           double frameRate,
                           const PlayerCapabilityT& capability
                          );


#endif // TRAJECTORY_H

