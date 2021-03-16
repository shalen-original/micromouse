#ifndef ROBOT_H
#define	ROBOT_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "utils.h"
#include "updateStruct.h"

#define DISTANCE_PASSED_THRESHOLD 150.0 //mm
#define ANGLE_ERROR_MARGIN 5.0 //degrees
#define SPEED_NORMAL 5
#define SPEED_SPIN_NORMAL 5

typedef enum // movement state of robot
{
    IDLE=0,
    MOVE,
    TURN
} movementState;

// setups the initial robot configuration
void initRobot(void);

// is called from distanceControl on each timer interrupt
void onUpdate(distanceUpdateDirection pack);

uint8_t getSensorMeasurement(BOOL sensorR, BOOL sensorL, BOOL sensorF);

void onWallChange(uint8_t newWalls);
void switchSpinToMove();
void cellChangeInGoalDirection();
void setupNewGoalDirection();

void startDirectionControl();
// pauses/unpauses the robot directionCtronl
void switchIdle();

#endif	/* ROBOT_H */

