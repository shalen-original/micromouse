#ifndef UPDATE_STUCT_H
#define	UPDATE_STUCT_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "boolean.h"

typedef struct // struct that used from distanceControl to update the directionControl (TODO change name)
{
    // wall is right in front of that direction (or not)
    BOOL sensorL;
    BOOL sensorR;
    BOOL sensorF;
    float distanceDelta; // mm
    float angleDelta; // degrees
} distanceUpdateDirection;

#endif	/* UPDATE_STUCT_H */

