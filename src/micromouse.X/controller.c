#include "controllerUtils.h"
#include "controller.h"
#include "halapi.h"
#include "directionControl.h"

void distanceControl(Controllerset *cset){
    /* Scenario 1: Corridor 
     * achieve same distances to left and right walls (168mm/2 = 84mm)
     * 
     * Scenario 2: One side opening
     * achieve constant distance to one wall (168mm/2 = 84mm)
     * 
     * Scenario 3: Both side opening
     * achieve same speed on both wheels*/
    
    //---read sensors---
    float sensorR = getDistanceRight_mm();
    float sensorL = getDistanceLeft_mm();
    float sensorF = getDistanceFront_mm();
    
    //---write info for update()---
    if (sensorR <= 150){
        cset->info.sensorR = TRUE;
    }
    else{
        cset->info.sensorR = FALSE;
    }
    if (sensorL <= 150){
        cset->info.sensorL = TRUE;
    }
    else{
        cset->info.sensorL = FALSE;
    }
    if (sensorF <= 150){
        cset->info.sensorF = TRUE;
    }
    else{
        cset->info.sensorF = FALSE;
    }
    
    //---check sensor validity for distance controllers---
    int validF = sensorF >= 40 && sensorF <= 150;// front sensor only used when close to maze wall
    int validR = sensorR >= 20 && sensorR <= 150;// check whether sensors have valid values
    int validL = sensorL >= 20 && sensorL <= 150;
    
    if (cset->API == 1) { // move()
        
        //---set distance controllers---
        if (validR && validL){ //scenario 1
            float sp = 71.5f;        
            _setPI(&cset->D.L,sp);
            _setPI(&cset->D.R,sp);  

            _enablePI(&cset->D.L);
            _enablePI(&cset->D.R); 
        }
        else if (validR && !validL){ //scenario 2 only right wall
            float sp = 71.5f;
            _setPI(&cset->D.R,sp); 

            _enablePI(&cset->D.R);
            _disablePI(&cset->D.L);
        }
        else if (validL && !validR){ //scenario 2 only left wall
            float sp = 71.5f;
            _setPI(&cset->D.L,sp);

            _enablePI(&cset->D.L); 
            _disablePI(&cset->D.R);
        }
        else if (!validL && !validR){ //scenario 3 
            _disablePI(&cset->D.R);
            _disablePI(&cset->D.L);
        }

        if (validF){ 
            _enablePI(&cset->D.F);
        }
        else if (!validF) {
            _disablePI(&cset->D.F);
            _clearPI(&cset->D.F);
        }
    }
    else {
        _disablePI(&cset->D.R); // // turn() / spin(), switch off distance controllers
        _disablePI(&cset->D.L);
        _disablePI(&cset->D.F);
    }
    
    //---update desired velocity---
    float adjustR = _stepPI(&cset->D.R, sensorR); // calculate control adjustment
    float adjustL = _stepPI(&cset->D.L, sensorL); // disabled controller will output 0
    float adjustF = _stepPI(&cset->D.F, sensorF);

    cset->desiredVelocityR += (adjustR + adjustF); // update desired velocity based on adjustment
    cset->desiredVelocityL += (adjustL + adjustF); 
    
    _setPI(&cset->V.R,cset->desiredVelocityR); // set desired values for velocity controller
    _setPI(&cset->V.L,cset->desiredVelocityL);
    
    //---clear accumulated error in velocity controllers---
    _clearPI(&cset->V.R); 
    _clearPI(&cset->V.L);
    
    onUpdate(cset->info); // calls the update in direction control
}

void velocityControl(Controllerset *cset){
    //-----------------execute once for initialization--------------------------
    static float lastEncoderL = 0; 
    static float lastEncoderR = 0;

    //----------------------regular execution-----------------------------------
    
    //---look up PWM without control---
    float lookupPWMR = _lookupPWM(cset->desiredVelocityR);
    float lookupPWML = _lookupPWM(cset->desiredVelocityL);
    
    //---read encoders---
    float currentEncoderL = getMotorLeftPosition_ticks(); 
    float currentEncoderR = getMotorRightPosition_ticks();
    
    //---compute current wheel speed(mm/s)---
    float wheelSpeedL = _getWheelSpeed(lastEncoderL, currentEncoderL, TIMER2_FREQUENCY); 
    float wheelSpeedR = _getWheelSpeed(lastEncoderR, currentEncoderR, TIMER2_FREQUENCY); 
    
    //---set final PWM with control---
    float adjustR = _stepPI(&cset->V.R, wheelSpeedR);
    float adjustL = _stepPI(&cset->V.L, wheelSpeedL);  

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
    
    //---write info for update()---
    
    float wheelDistanceL = _getWheelDistance(cset->commandStartEncoderL, currentEncoderL); // compute distance traveled since command start
    float wheelDistanceR = _getWheelDistance(cset->commandStartEncoderR, currentEncoderR);
    
    cset->info.distanceDelta = 0.5*(wheelDistanceL + wheelDistanceR); // write distance to update()
    
    int turnRight = wheelDistanceL >= wheelDistanceR;
    int turnLeft = wheelDistanceL < wheelDistanceR;
    
    float width = 40; // TODO confirm the (track width)
    
    if (cset->API == 2){ // turn mode
        if (turnRight){
            cset->info.angleDelta = wheelDistanceL/(3.142*width) *360; // write angle to update()
        }
        else if(turnLeft){
            cset->info.angleDelta = -1 * wheelDistanceR/(3.142*width) *360; // write angle to update()
        }
    }
    else if(cset->API == 3){ // spin mode
        if (turnRight){
            cset->info.angleDelta = wheelDistanceL/(3.142*0.5*width) *360; // write angle to update()
        }
        else if(turnLeft){
            cset->info.angleDelta = -1 * wheelDistanceR/(3.142*0.5*width) *360; // write angle to update()
        }
    }
    
    //---save current value to history---
    lastEncoderL = currentEncoderL; 
    lastEncoderR = currentEncoderR;
}
