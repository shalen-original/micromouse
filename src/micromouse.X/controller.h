#ifndef CONTROLLER_H
#define	CONTROLLER_H

// define a class to represent PI controller
typedef struct{
    float kp; // P portion parameter
    float ki; // I portion parameter
    float e_sum; //previous sum of error
    float sp; // set point(desired outcome)
    int enable; // 1: enable controller , 0: disable controller
} PI;

// define a set to contain all controllers (VR,VL,DR,DL)
typedef struct{
    PI VR; // Velocity controller Right motor
    PI VL; // Velocity controller Left motor
    PI DR; // Distance controller Right sensor
    PI DL; // Distance controller Left sensor
    PI DF; // Distance controller Front sensor
} Controllerset;

// initialize the set
void initControllerset(Controllerset*);

// reset controller to new desired sp (set point)
void setPI (PI *controller, float sp);

// receive pv (measurement), step controller and return adjust value for pwm/ velocity
float stepPI(PI *controller, float pv);

#endif	/* CONTROLLER_H */


