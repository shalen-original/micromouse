#ifndef DIRECTION_CONTROL_H
#define	DIRECTION_CONTROL_H

#include <xc.h>
#include "utils.h"
#include "updateStruct.h"

//TODO change these magic numbers
#define DISTANCE_PASSED_THRESHOLD 165.0 //mm
#define DISTANCE_PASSED_WALLCHANGE_THRESHOLD 130.0 //mm
#define ANGLE_ERROR_MARGIN 5.0 //degrees
#define SPEED_NORMAL 50 //mm/s
#define SPEED_SPIN_NORMAL 50 //mm/s

#define WALL_SKIP_STATE (MAX_DIR_INT << 1) // state where the next wallchange does not influence movement control

typedef enum // movement state of robot
{
    IDLE=0,
    MOVE,
    TURN
} movementState;

// setups the initial robot configuration
void initDirectionControl(void);

// is called from distanceControl on each timer interrupt
void onUpdate(distanceUpdateDirection pack);

uint8_t getSensorMeasurement(BOOL sensorR, BOOL sensorL, BOOL sensorF);

void onWallChange(uint8_t newWalls, float distanceRecorded);
void switchSpinToMove();
void cellChangeInGoalDirection();
void setupNewGoalDirection();

void startDirectionControl();
// pauses/unpauses the robot directionControl
void switchIdle();

#endif	/* DIRECTION_CONTROL_H */

