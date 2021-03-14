#include "boolean.h"

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

// define a struct for information updates
typedef struct{
    BOOL wallRight; // if right wall exist
    BOOL wallLeft; // if left wall exist
    float distance; // average of both motor distances
    float angle; // turned angle
} infoUpdate;

// define a set to contain all controllers (VR,VL,DR,DL,DF)
typedef struct{
    velocityControllers V;
    distanceControllers D;
    float rawVelocityR;
    float rawVelocityL;
    float desiredVelocityR;
    float desiredVelocityL;
    infoUpdate info;
    int API; // 0:no, 1:move, 2:rotate, 3:spin
} Controllerset;

typedef struct {
    float velocity;
    float PWM;
} PWMCurvePoint;

// user level API to set Left motor speed
void _setRawVelocityL(Controllerset *cset, float speed);

// user level API to set Right motor speed
void _setRawVelocityR(Controllerset *cset, float speed);

// clear accumulated error inside controller
void _clearPI (PI *controller);

// set control goal (set point)
void _setPI (PI *controller, float sp);

// enable controller
void _enablePI (PI *controller);

// disable controller
void _disablePI (PI *controller);

// receive pv (measurement), step controller and return value for control
float _stepPI(PI *controller, float pv);

// select API 
// 0:no, 1:move, 2:rotate, 3:spin
void _selectAPI(Controllerset *cset, int API);

// intermediate function used to interpolate PWM curve
float _interpolatePWMCurve(const PWMCurvePoint *curve, int N_points, float desiredVelocity);

// look up PWM for desired velocity
float _lookupPWM(float desiredVelocity);

// compute wheel speed (mm/s) according to QEI counts
float _getWheelSpeed(float lastCount,float currentCount,int timerFrequency);

// compute wheel distance (mm) according to QEI counts
float _getWheelDistance(float lastCount,float currentCount);

#endif	/* CONTROLLERUTILS_H */


