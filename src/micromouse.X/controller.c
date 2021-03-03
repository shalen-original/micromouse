/*
 * File:   controller.c
 * Author: congnan
 *
 * Created on March 3, 2021, 10:09 AM
 */


#include "controllerUtils.h"
#include "controller.h"

void initControllerset(Controllerset *cset){
    // below are default values for controllers 
    // !!! modify accordingly
    // (PI){kp, ki, e_sum, sp, enable}  
    cset->D.R = (PI){0.1, 0.1, 0, 0, 0};
    cset->D.L = (PI){0.1, 0.1, 0, 0, 0};
    cset->D.F = (PI){0.1, 0.1, 0, 0, 0};
    cset->V.R = (PI){0.1, 0.1, 0, 0, 0};
    cset->V.L = (PI){0.1, 0.1, 0, 0, 0};
    cset->rawVelocityL = 0;
    cset->rawVelocityR = 0;
    cset->desiredVelocityL = 0;
    cset->desiredVelocityR = 0;
}

