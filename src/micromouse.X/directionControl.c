#include "xc.h"
#include "directionControl.h"
#include "utils.h"
#include "motionControl.h"
#include "mazeControl.h"

extern Controllerset controllerset;

typedef struct
{
    movementState movState;
    uint8_t walls; // walls for all cardinal directions
    position curPos;
    dir nextDirection; // goal cell is one cell in this dir
    dir curDirection; // curent direction (last known if unknown)
    float curAngleChange; // total angle change
    float distanceSinceLastCell;
} robotState;

robotState state;

void initDirectionControl()
{
    state.curPos.x = 0;
    state.curPos.y = 0;

    state.walls = SOUTH | WEST;
    state.movState = IDLE;
    state.distanceSinceLastCell = 0.0;
    state.curDirection = NORTH;
    state.nextDirection = NORTH; //will be replaced when removing IDLE
}

void onUpdate(distanceUpdateDirection pack)
{
    if (state.movState == TURN)
    {
        state.curAngleChange += pack.angleDelta; 
        // TODO no need for accumulation anymore (same for position later)
        // TODO angle is positive in clockwise direction
        // TODO use angle difference
        if (directionEqualsAngle(state.nextDirection, (dirToFloat(state.curDirection) + state.curAngleChange), ANGLE_ERROR_MARGIN))
        {
            switchSpinToMove();
        }
    } else if (state.movState == MOVE) // robot is moving straight
    {
        state.distanceSinceLastCell += pack.distanceDelta;
        uint8_t wallMeasured = getSensorMeasurement(pack.sensorR, pack.sensorL, pack.sensorF);
        if (wallMeasured != state.walls)
        {
            onWallChange(wallMeasured);
        }
        else 
        {
            if (state.distanceSinceLastCell > DISTANCE_PASSED_THRESHOLD)
            {
                cellChangeInGoalDirection();
                setupNewGoalDirection();
            }
        }
    }
    // Does nothing if being IDLE (needs signal from higherlevel module)
}

uint8_t getSensorMeasurement(BOOL sensorR, BOOL sensorL, BOOL sensorF)
{
    uint8_t wallNew = 0b0;
    if (sensorR == TRUE)
    {
        wallNew |= getClockwise(state.curDirection);
    }
    if (sensorL == TRUE)
    {
        wallNew |= getCounterClockwise(state.curDirection);
    }
    if (sensorF == TRUE)
    {
        wallNew |= state.curDirection;
    }
    return wallNew;
}

void onWallChange(uint8_t newWalls)
{
    state.walls = newWalls;
}

void switchSpinToMove()
{
    move(&controllerset, SPEED_NORMAL);
    state.movState = MOVE;
    // TODO maybe reset distance to 0?
}

void cellChangeInGoalDirection()
{
    // wall update is always one cell in advance (as cell position updates comes later)
    position posInDir = getPosInDir(state.curPos, state.nextDirection);
    onMazePosExplored(posInDir, state.walls);
    state.curPos = getPosInDir(state.curPos, state.nextDirection);
    state.curDirection = state.nextDirection;
    // reset all relative states
    state.curAngleChange = 0;
    state.distanceSinceLastCell = 0.0;
}

void setupNewGoalDirection()
{
    state.nextDirection = getNextDirection(state.curPos, state.curDirection); // receives new goal direction from mazeControl
    
    if (state.nextDirection != state.curDirection)
    {
        state.movState = TURN;
        float deltaAngle = dirToFloat(state.nextDirection) - dirToFloat(state.curDirection);
        if (deltaAngle > 0 && deltaAngle <= 180)
        {
            spin(&controllerset, (-1)*SPEED_SPIN_NORMAL); // turn counterclockwise (/left)
        } else
        {
            spin(&controllerset, SPEED_SPIN_NORMAL); // turn clockwise (/right)
        }
    } else
    {
        state.movState = MOVE;
        move(&controllerset, SPEED_NORMAL);
    }
}

void switchIdle()
{
    if (IDLE == state.movState)
    {
        startDirectionControl();
    } else
    {
        state.movState = IDLE;
        move(&controllerset, 0); // TODO is zero here correct?
    }
}

void startDirectionControl()
{
    setupNewGoalDirection();
}