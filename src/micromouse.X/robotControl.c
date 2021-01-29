#include "xc.h"
#include "robotControl.h"
#include "utils.h"
#include "motionControl.h"

typedef struct
{
    movementState movState;
    envState walls;
    position curPos;
    dir facingRotation;
    float velocity; //in m/s
} robotState;

robotState state;

void initRobot()
{
    state.curPos.x = 0;
    state.curPos.y = 0;
        
    state.walls = NWALL;
    state.movState = IDLE;
    state.velocity = 0.0;
    state.facingRotation = NORTH;
}

void onSensorUpdate(float timeInterval, unsigned int sensorFront, unsigned int sensorLeft, unsigned int sensorRight)
{
    // set env state
    // check new cell visited?
    // update velocity
    
    // execute command
}