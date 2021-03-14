// guard condition  
#ifndef ROBOT_H
#define	ROBOT_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "utils.h"
#include "updateStruct.h"

typedef enum // movement state of robot
{
    IDLE=0,
    MOVE,
    TURN
} movementState;
/*
typedef enum // environement state of robot (where are walls)
{
    LRWALL=0,
    LWALL,
    RWALL,
    NWALL
} envState;
*/

// setups the initial robot configuration
void initRobot(void);

// is called whenever the sensors are read
void onUpdate(distanceUpdateDirection pack);

uint8_t getSensorMeasurement(BOOL sensorR, BOOL sensorL, BOOL sensorF);

void onWallChange(uint8_t newWalls);
void onAngleReached();
void onCellChange();

#endif	/* ROBOT_H */

