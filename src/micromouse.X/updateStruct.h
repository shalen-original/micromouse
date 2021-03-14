// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef UPDATE_STUCT_H
#define	UPDATE_STUCT_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "boolean.h"

typedef struct // cardinal direction enum (binary, 4 bits required)
{
    BOOL sensorL;
    BOOL sensorR;
    BOOL sensorF;
    float distanceDelta;
    float angleDelta;
} distanceUpdateDirection;

#endif	/* UPDATE_STUCT_H */

