#include "xc.h"
#include "controllerUtils.h"

void _setrawVelocityL(Controllerset *cset, float speed){
    cset->rawVelocityL = speed;
}

void _setrawVelocityR(Controllerset *cset, float speed){
    cset->rawVelocityR = speed;
}

void _setPI (PI *controller, float desired_value){
    controller->e_sum = 0;
    controller->sp = desired_value;
}

void _enablePI (PI *controller){
    controller->enable = 1;
}

void _disablePI (PI *controller){
    controller->enable = 0;
}

float _stepPI(PI *controller, float pv){ // pv stands for present value
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

