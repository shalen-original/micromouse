/*
 * File:   controller.c
 * Author: Congnan(Jonas)
 *
 * Created on January 26, 2021, 5:08 PM
 */


#include "xc.h"
#include "controller.h"

typedef struct{
    float kp; // P portion parameter
    float ki; // I portion parameter
    float e_sum; //previous sum of error
    float sp; // set point(desired outcome)
} PI;

typedef struct{
    PI VR; // Velocity controller Right motor
    PI VL; // Velocity controller Left motor
    PI DR; // Distance controller Right sensor
    PI DL; // Distance controller Left sensor
} Controllerset;


Controllerset initControllerset(){
    
    Controllerset cset;
    // below are default values for controllers !!! modify possible
    cset.DL = {0.1, 0.1, 0, 0};
    cset.DR = {0.1, 0.1, 0, 0};
    cset.VL = {0.1, 0.1, 0, 0};
    cset.VR = {0.1, 0.1, 0, 0};
    
    return cset;
}


void resetPI (PI *controller, float sp){
    controller->e_sum = 0;
    controller->sp = sp;
}
float stepPI(PI *controller, float pv){ 
    
    float error = controller->sp - pv; // calculate current error of the system
    controller->e_sum = controller->e_sum + error; // update integral of error
    float adjust = controller->kp * error + controller->ki * controller->e_sum;
    
    return adjust;
}