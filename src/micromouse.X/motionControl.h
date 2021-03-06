#include "controllerUtils.h"

#ifndef MOTION_CONTROL_H
#define	MOTION_CONTROL_H



// initializes the motion control module
void initMotionControl(Controllerset *cset);

/* Go straight line
 * both motors set to rawVelocity(mm/s)
 */ 
void move(Controllerset *cset, float rawVelocity);

/* Rotate while running
 * outer wheel set to rawVelocity(mm/s), inner wheel stop 
 * +: turn right
 * -: turn left
 */   
void turn(Controllerset *cset, float rawVelocity);

/* Rotate on the spot
 * both motors set to rawVelocity(mm/s), but reversed to each other
 * +: turn right
 * -: turn left
 */   
void spin(Controllerset *cset, float rawVelocity);

#endif	/* MOTION_CONTROL_H */

