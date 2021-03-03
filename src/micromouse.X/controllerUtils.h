#ifndef CONTROLLERUTILS_H
#define	CONTROLLERUTILS_H

// define a class to represent PI controller
typedef struct{
    float kp; // P portion parameter
    float ki; // I portion parameter
    float e_sum; //previous sum of error
    float sp; // set point(desired outcome)
    int enable; // 1: enable controller , 0: disable controller
} PI;

typedef struct{
    PI R; // Velocity controller Right motor
    PI L; // Velocity controller Left motor
} velocityControllers;

typedef struct{
    PI R; // Distance controller Right sensor
    PI L; // Distance controller Left sensor
    PI F; // Distance controller Front sensor
} distanceControllers;

// define a set to contain all controllers (VR,VL,DR,DL,DF)
typedef struct{
    velocityControllers V;
    distanceControllers D;
    float rawVelocityR;
    float rawVelocityL;
    float desiredVelocityR;
    float desiredVelocityL;
} Controllerset;

// user level API to set Left motor speed
void _setrawVelocityL(Controllerset *cset, float speed);

// user level API to set Right motor speed
void _setrawVelocityR(Controllerset *cset, float speed);

// set control goal (set point)
void _setPI (PI *controller, float sp);

// enable controller
void _enablePI (PI *controller);

// disable controller
void _disablePI (PI *controller);

// receive pv (measurement), step controller and return value for control
float _stepPI(PI *controller, float pv);

#endif	/* CONTROLLERUTILS_H */


