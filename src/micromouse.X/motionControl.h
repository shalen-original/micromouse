#include "controllerUtils.h"

#ifndef MOTION_CONTROL_H
#define	MOTION_CONTROL_H


// initializes the motion control module
void initMotionControl(Controllerset *cset);

// general move function (where both motor move have to turn with same speed)
void move(Controllerset *cset, float rawVelocity);

// uses outer wheel to turn
void turn(Controllerset *cset, float rawVelocity);

// rotates while standing (both motors with same speed, but inversed to each other)
void spin(Controllerset *cset, float rawVelocity);

// update current information of the micromouse
void update(void); //TODO

#endif	/* MOTION_CONTROL_H */

