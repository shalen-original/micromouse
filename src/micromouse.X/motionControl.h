// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MOTION_CONTROL_H
#define	MOTION_CONTROL_H

#include <xc.h> // include processor files - each processor file is guarded.  

// initializes the motion control module
void initMotionControl(void);

// general move function (where both motor move have to turn with same speed)
void move(int steps, int maxSpeed, int exitSpeed);
// uses move() to move straight ahead
void driveStraight(int steps, int maxSpeed, int exitSpeed);
// turn 90° smoothly (motors not with same speed)
void turn90Left(int maxSpeed);
void turn90Right(int maxSpeed);
// rotates while standing (both motors with same speed, but inversed to each other)
void spin(int steps, int maxSpeed);

#endif	/* MOTION_CONTROL_H */

