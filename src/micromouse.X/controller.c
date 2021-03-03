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

void distanceControl(Controllerset *cset, float sensorR, float sensorL, float sensorF){
    /* Scenario 1: Corridor 
     * achieve same distances to left and right walls
     * 
     * Scenario 2: One side opening
     * achieve constant distance to one wall
     * 
     * Scenario 3: Both side opening
     * achieve same speed on both wheels*/
    
   int validF = sensorF >= 40 && sensorF <= 300; // check whether sensors have valid values
   int validR = sensorR >= 20 && sensorR <= 150;
   int validL = sensorL >= 20 && sensorL <= 150;
   
   if (validR && validL){ //scenario 1
       float sp = 0.5 * (sensorR + sensorL);
       _setPI(&cset->D.L,sp);
       _setPI(&cset->D.R,sp);     
   }
   else if (validR && !validL){ //scenario 2 only right wall
       float sp = sensorR;
       _setPI(&cset->D.R,sp);
       _disablePI(&cset->D.L);
   }
   else if (validL && !validR){ //scenario 2 only left wall
       float sp = sensorL;
       _setPI(&cset->D.L,sp);
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
   }
   
   float adjustR = _stepPI(&cset->D.R, sensorR);
   float adjustL = _stepPI(&cset->D.L, sensorL);
   float adjustF = _stepPI(&cset->D.F, sensorF);
   
   cset->desiredVelocityR += adjustR + adjustF;
   cset->desiredVelocityL += adjustL + adjustF; 
}