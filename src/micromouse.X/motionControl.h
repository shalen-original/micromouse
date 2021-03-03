// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MOTION_CONTROL_H
#define	MOTION_CONTROL_H

#include <xc.h> // include processor files - each processor file is guarded.  

// initializes the motion control module
void initMotionControl(void);

// general move function (where both motor move have to turn with same speed)
void move(float rawVelocity);

// uses outer wheel to turn
void turn(float rawVelocity);

// rotates while standing (both motors with same speed, but inversed to each other)
void spin(float rawVelocity);

#endif	/* MOTION_CONTROL_H */

