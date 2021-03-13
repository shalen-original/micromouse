#include "xc.h"
#include "controllerUtils.h"
#include "utils.h"

void _setRawVelocityL(Controllerset *cset, float speed){
    cset->rawVelocityL = speed;
}

void _setRawVelocityR(Controllerset *cset, float speed){
    cset->rawVelocityR = speed;
}
void _clearPI (PI *controller){
    controller->e_sum = 0;
}

void _setPI (PI *controller, float desired_value){
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

float _interpolatePWMCurve(const PWMCurvePoint *curve, int N_points, float desiredVelocity) {
    float minVelocity = 0;
    float maxVelocity = 316;
    
    if (desiredVelocity < minVelocity || desiredVelocity > maxVelocity)
        return -6; // TODO: connect to error.h
              
    int pointIndex, i; // allocate the range desiredVelocity falls in
    for (i = 0; i <= N_points - 2; i++) {
        if (curve[i].velocity <= desiredVelocity && curve[i + 1].velocity > desiredVelocity){
            pointIndex = i; // assign pointINdex the start index
            break;
        }
    }
    
    PWMCurvePoint head = curve[pointIndex];
    PWMCurvePoint tail = curve[pointIndex + 1];
    
    float delta = (desiredVelocity - head.velocity) / (tail.velocity - head.velocity);
    return lerp(delta, head.PWM, tail.PWM);
}

#define N_POINTS_PWMCurvePoint 2

PWMCurvePoint samplekurve[] = { // MUST be sorted by velocity ASCENDING
    { 0, 0 },
    {316, 1 },
};

float _lookupPWM(float desiredVelocity){
    if (desiredVelocity >= 0){
        return _interpolatePWMCurve(samplekurve, N_POINTS_PWMCurvePoint, desiredVelocity);
    }
    else{ 
        return -1*_interpolatePWMCurve(samplekurve, N_POINTS_PWMCurvePoint, -1*desiredVelocity);} 
    
    return -7;// connect to error.h
    
}
    

float _getWheelSpeed(float lastCount,float currentCount,int timerFrequency){
    /* ### Hardware related parameters ###
     * N_pulse: pulses per revolution (=16 for our motor) 
     * K_e: edge gain (=4 in our case)
     * Gr: gear ratio (=33 in our case)
     * Dwheel: wheel diameter(=40 mm)
     * 
     * Documentation on 'Build a micromouse from scratch.pdf' page 58
     * 
     * ### Formula ###
     * Count per second(/s)
     * V_cps = (currentCount - lastCount) * timerFrequency 
     * 
     * Angle per count (°)
     * alpha = 360/ N_pulse
     * 
     * angular velocity(°/s)
     * V_angular = V_cps * alpha /(K_e * Gr)
     * 
     * wheel velocity (mm/s)
     * V_wheel = V_angular/ 360 * 3.14* Dwheel 
     */
    
    int N_pulse =16;
    int K_e =4;
    int Gr=33;
    int Dwheel =40;

    float V_cps = (currentCount - lastCount) * timerFrequency;

    float alpha = 360/ N_pulse;
    
    float V_angular = V_cps * alpha /(K_e * Gr);

    float V_wheel = V_angular/ 360 * 3.142 * Dwheel;
    
    return V_wheel;
}

