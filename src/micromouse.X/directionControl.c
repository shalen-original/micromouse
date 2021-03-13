#include "xc.h"
#include "directionControl.h"
#include "utils.h"
#include "motionControl.h"
#include "mazeControl.h"

extern Controllerset controllerset;

typedef struct
{
    movementState movState;
    //envState walls;
    uint8_t walls; // walls for all cardinal directions
    position curPos;
    dir nextDirection; // goal cell is one cell in this dir
    dir curDirection; // curent direction (last known if unknown)
    float curAngleChange; // total angle change
    //float desiredAngleChange; // desired angle change
    float distanceSinceLastCell;
    //float velocity; //in m/s
} robotState;

robotState state;

void initRobot()
{
    state.curPos.x = 0;
    state.curPos.y = 0;
        
    //state.walls = NWALL;
    state.walls = SOUTH + WEST;
    state.movState = IDLE;
    state.distanceSinceLastCell = 0.0;
    //state.velocity = 0.0;
    state.curDirection = NORTH;
    state.nextDirection = getNextDirection(state.curPos);
}

void onUpdate(float sensorR, float sensorL, float sensorF, float distancePassed, float angleChange)
{
    // robot is currently turning/spinning?
    if (state.movState == TURN)
    {
        state.curAngleChange += angleChange;
        if (directionEqualsAngle(state.curAngleChange, state.nextDirection, 5)) // TODO ERROR MARGIN (5 is too low?)
        {
            onAngleReached();
        }
    } else // robot is moving straight
    {
        state.distanceSinceLastCell += distancePassed;
        uint8_t wallMeasured = getSensorMeasurement(sensorR, sensorL, sensorF);
        // wall changed?
        if (wallMeasured != state.walls)
        {
            // wall change
            onWallChange(wallMeasured);
        }
        else 
        {
            // no wall change
            if (state.distanceSinceLastCell > 8.0) // TODO distance threshold
            {
                onCellChange();
            }
        }
    }
}

BOOL sensorConvertToBool(float sensorValue)
{
    if (sensorValue < 180 && sensorValue > 40) // TODO set thresholds correctly (between 4 and 18 cm)
    {
        return TRUE;
    }
    return FALSE;
}

uint8_t getSensorMeasurement(float sensorR, float sensorL, float sensorF)
{
    uint8_t wallNew = 0b0;
    if (sensorConvertToBool(sensorR) == TRUE)
    {
        wallNew |= getClockwise(state.curDirection);
    }
    if (sensorConvertToBool(sensorL) == TRUE)
    {
        wallNew |= getCounterClockwise(state.curDirection);
    }
    if (sensorConvertToBool(sensorF) == TRUE)
    {
        wallNew |= state.curDirection;
    }
    return wallNew;
}

void onWallChange(uint8_t newWalls)
{
    state.walls = newWalls; // update internal state
}

void onAngleReached()
{
    // TODO move straight
    move(&controllerset, 20); // TODO speed (get from mazecontrol?)
    state.movState = MOVE;
    // maybe reset distance to 0?
}

void onCellChange()
{
    // report current internal wall to maze
    position posInDir = getPosInDir(state.curPos, state.nextDirection); // wall update is always one cell in advance (as cell position updates comes later)
    onMazePosExplored(posInDir, state.walls); // update maze walls
    
    state.curPos = getPosInDir(state.curPos, state.nextDirection); // position update
    state.curDirection = state.nextDirection; // next to cur override
    state.nextDirection = getNextDirection(state.curPos); // receives new moving direction from mazeControl
    
    if (state.nextDirection != state.curDirection)
    {
        state.movState = TURN;
        //calculate difference in angle
        float deltaAngle = dirToFloat(state.nextDirection) - dirToFloat(state.curDirection);
        spin(&controllerset, deltaAngle); // TODO speed is wrong here (only +- and then fixed value)
    } else
    {
        state.movState = MOVE;
        move(&controllerset, 20); // TODO speed (get from mazecontrol?)
    }
    
    // reset all relative states
    state.curAngleChange = 0;
    state.distanceSinceLastCell = 0.0;
}