#include "xc.h"
#include "motionControl.h"
#include "controllerUtils.h"

extern Controllerset controllerset;

void initMotionControl(Controllerset *cset){
    // Below are settings for Controller parameters
    // (PI){kp, ki, e_sum, sp, enable}  
    //(distanceUpdateDirection){wallLeft,wallRight,wallFront,distance,angle}
    cset->D.R = (PI){0.1, 0.1, 0, 0, 0};
    cset->D.L = (PI){0.1, 0.1, 0, 0, 0};
    cset->D.F = (PI){0.1, 0.1, 0, 84, 0}; // Front sensor keep 84mm to front wall(middle of maze)
    cset->V.R = (PI){0.1, 0.1, 0, 0, 1}; // velocity controllers are always ON
    cset->V.L = (PI){0.1, 0.1, 0, 0, 1};
    cset->commandStartEncoderL = 0;
    cset->commandStartEncoderR= 0;
    cset->rawVelocityL = 0;
    cset->rawVelocityR = 0;
    cset->desiredVelocityL = 0;
    cset->desiredVelocityR = 0;
    cset->info = (distanceUpdateDirection){TRUE,TRUE,TRUE,0,0};
    cset->API = 0;
}

void move(Controllerset *cset, float rawVelocity)
{   
    _recordStartPosition(cset);
    _selectAPI(cset,1);
    _setRawVelocityL(cset,rawVelocity); // set raw velocity
    _setRawVelocityR(cset,rawVelocity);
    _clearPI(&cset->D.R); // clear the accumulated error inside distance controllers
    _clearPI(&cset->D.L);
    _clearPI(&cset->D.F);
    _enablePI(&cset->D.R); // switch on distance controllers
    _enablePI(&cset->D.L);
    _enablePI(&cset->D.F);
}

void turn(Controllerset *cset, float rawVelocity)
{   
    _recordStartPosition(cset);
    _selectAPI(cset,2);
    int turnRight =  (rawVelocity >= 0); // switch cases for right /left 
    int turnLeft = (rawVelocity < 0);
    
    if (turnRight){
        _setRawVelocityL(cset,rawVelocity);
        _setRawVelocityR(cset,0);
    }
    else if (turnLeft){
        _setRawVelocityL(cset,0);
        _setRawVelocityR(cset,rawVelocity);
    }
    
    _clearPI(&cset->D.R); // clear the accumulated error inside distance controllers
    _clearPI(&cset->D.L);
    _clearPI(&cset->D.F);
    _disablePI(&cset->D.R); // when turning, switch off distance controllers
    _disablePI(&cset->D.L);
    _disablePI(&cset->D.F);

}

void spin(Controllerset *cset, float rawVelocity)
{
    _recordStartPosition(cset);
    _selectAPI(cset,3);
    int turnRight =  rawVelocity >= 0; // switch cases for right /left 
    int turnLeft = rawVelocity < 0;
    
    if (turnRight){
        _setRawVelocityL(cset,rawVelocity);
        _setRawVelocityR(cset,-rawVelocity);
    }
    else if (turnLeft){
        _setRawVelocityL(cset,-rawVelocity);
        _setRawVelocityR(cset,rawVelocity);
    }
    
    _clearPI(&cset->D.R); // clear the accumulated error inside distance controllers
    _clearPI(&cset->D.L);
    _clearPI(&cset->D.F);
    _disablePI(&cset->D.R); // when spinning, switch off distance controllers
    _disablePI(&cset->D.L);
    _disablePI(&cset->D.F);
}

distanceUpdateDirection update(Controllerset *cset){

    return cset->info;
}
