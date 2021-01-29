/*
 * File:   controller.c
 * Author: Congnan(Jonas)
 *
 * Created on January 26, 2021, 5:08 PM
 */


#include "xc.h"
#include "controller.h"

void initControllerset(Controllerset *cset){
    // below are default values for controllers 
    // !!! modify accordingly
    // (PI){kp, ki, e_sum, sp, enable, rawVelocityR, L, desiredVelocityR, L}  
    cset->DL = (PI){0.1, 0.1, 0, 0, 0};
    cset->DR = (PI){0.1, 0.1, 0, 0, 0};
    cset->DF = (PI){0.1, 0.1, 0, 0, 0};
    cset->VL = (PI){0.1, 0.1, 0, 0, 0};
    cset->VR = (PI){0.1, 0.1, 0, 0, 0};
}



void setPI (PI *controller, float sp){
    controller->e_sum = 0;
    controller->sp = sp;
}

void enablePI (PI *controller){
    controller->enable = 1;
}

void disablePI (PI *controller){
    controller->enable = 0;
}

float stepPI(PI *controller, float pv){ 
    if (controller->enable == 1){
        float error = controller->sp - pv; // calculate current error of the system
        controller->e_sum = controller->e_sum + error; // update integral of error
        float adjust = controller->kp * error + controller->ki * controller->e_sum;

        return adjust;
    }
    else {
        return 0; // if controller disabled return 0
    }
}

