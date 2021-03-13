#include "controllerUtils.h"
#include "controller.h"
#include "halapi.h"

void distanceControl(Controllerset *cset){
    /* Scenario 1: Corridor 
     * achieve same distances to left and right walls (168mm/2 = 84mm)
     * 
     * Scenario 2: One side opening
     * achieve constant distance to one wall (168mm/2 = 84mm)
     * 
     * Scenario 3: Both side opening
     * achieve same speed on both wheels*/
    float sensorR = getDistanceRight_mm();
    float sensorL = getDistanceLeft_mm();
    float sensorF = getDistanceFront_mm();
    
    int validF = sensorF >= 40 && sensorF <= 150;// front sensor only used when close to maze wall
    int validR = sensorR >= 20 && sensorR <= 150;// check whether sensors have valid values
    int validL = sensorL >= 20 && sensorL <= 150;

    if (validR && validL){ //scenario 1
        float sp = 84;        
        _setPI(&cset->D.L,sp);
        _setPI(&cset->D.R,sp);  
        
        _enablePI(&cset->D.L);
        _enablePI(&cset->D.R); 
    }
    else if (validR && !validL){ //scenario 2 only right wall
        float sp = 84;
        _setPI(&cset->D.R,sp); 
        
        _enablePI(&cset->D.R);
        _disablePI(&cset->D.L);
    }
    else if (validL && !validR){ //scenario 2 only left wall
        float sp = 84;
        _setPI(&cset->D.L,sp);
        
        _enablePI(&cset->D.L); 
        _disablePI(&cset->D.R);
    }
    else if (!validL && !validR){ //scenario 3 
        _disablePI(&cset->D.R);
        _disablePI(&cset->D.L);
    }

    if (validF){ // disable DF if front sensor value not valid
        _enablePI(&cset->D.F);
    }
    else if (!validF) {
        _disablePI(&cset->D.F);
        _clearPI(&cset->D.F);
    }

    float adjustR = _stepPI(&cset->D.R, sensorR); // calculate control adjustment
    float adjustL = _stepPI(&cset->D.L, sensorL);
    float adjustF = _stepPI(&cset->D.F, sensorF);

    cset->desiredVelocityR += (adjustR + adjustF); // update desired velocity based on adjustment
    cset->desiredVelocityL += (adjustL + adjustF); 
    
    _setPI(&cset->V.R,cset->desiredVelocityR); // set desired values for velocity controller
    _setPI(&cset->V.L,cset->desiredVelocityL);
    
    _clearPI(&cset->V.R); // everytime new desired velocity comes, clear accumulated error
    _clearPI(&cset->V.L);
}

void velocityControl(Controllerset *cset){
    //-----------------execute once for initialization--------------------------
    static float lastEncoderL = 0; 
    static float lastEncoderR = 0;

    //----------------------regular execution-----------------------------------
    
    float currentEncoderL = getMotorLeftPosition_ticks(); // update current encoder position
    float currentEncoderR = getMotorRightPosition_ticks();

    float wheelSpeedL = _getWheelSpeed(lastEncoderL, currentEncoderL, TIMER2_FREQUENCY); // compute current wheel speed(mm/s)
    float wheelSpeedR = _getWheelSpeed(lastEncoderR, currentEncoderR, TIMER2_FREQUENCY); 
    
    float adjustR = _stepPI(&cset->V.R, wheelSpeedR);
    float adjustL = _stepPI(&cset->V.L, wheelSpeedL);  
    
    float lookupPWMR = _lookupPWM(cset->desiredVelocityR);
    float lookupPWML = _lookupPWM(cset->desiredVelocityL);


    float finalPWMR= lookupPWMR + adjustR;
    float finalPWML= lookupPWML + adjustL;
    
    if (finalPWMR>= 0)
        {setMotorRightForward(finalPWMR);}
    else
        {setMotorRightBackward(-1*finalPWMR);}
    
    if (finalPWML>= 0)
        {setMotorLeftForward(finalPWML);}
    else
        {setMotorLeftBackward(-1*finalPWML);}
    
    lastEncoderL = currentEncoderL; // last thing is to update value of last tick
    lastEncoderR = currentEncoderR;
}
