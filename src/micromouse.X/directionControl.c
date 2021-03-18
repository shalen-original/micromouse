#include "xc.h"
#include "directionControl.h"
#include "utils.h"
#include "motionControl.h"
#include "mazeControl.h"

extern Controllerset controllerset;

typedef struct
{
    movementState movState; // contains IDLE, MOVE or TURN
    uint8_t walls; // walls for all cardinal directions (if zero => next wallchange does not influence movement)
    position curPos; // latest cell position
    dir nextDirection; // goal cell is one cell in this dir
    dir curDirection; // last known direction of the robot
    float distanceSinceLastWallChange; // distance passed from last cell to the point of wallChange (during move straight)
} robotState;

robotState state;

void initDirectionControl()
{
    state.curPos.x = 0;
    state.curPos.y = 0;

    state.walls = WALL_SKIP_STATE;
    state.movState = IDLE;
    state.curDirection = NORTH;
    state.nextDirection = NORTH; //will be replaced when removing IDLE
}

void onUpdate(distanceUpdateDirection pack)
{
    if (state.movState == TURN)
    {
        float angleDiff = getDifferenceInDirections(state.curDirection, state.nextDirection);
        if (angleEqualsAngle(angleDiff, pack.angleDelta, ANGLE_ERROR_MARGIN))
        {
            switchSpinToMove();
        }
    } else if (state.movState == MOVE) // robot is moving straight
    {
        uint8_t wallMeasured = getSensorMeasurement(pack.sensorR, pack.sensorL, pack.sensorF);
        if (wallMeasured != state.walls)
        {
            onWallChange(wallMeasured, pack.distanceDelta);
        }
        else 
        {
            // distance check: either wallchange occured and distance from that wallchange on must be reached, or whole distance must match
            // TODO make this less ugly
            if ((state.distanceSinceLastWallChange != 0.0 && (pack.distanceDelta - state.distanceSinceLastWallChange) >= DISTANCE_PASSED_WALLCHANGE_THRESHOLD)
            || (pack.distanceDelta >= DISTANCE_PASSED_THRESHOLD))
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

void onWallChange(uint8_t newWalls, float distanceRecorded)
{
    if (state.walls != WALL_SKIP_STATE) //means the wall change comes from changing cells
    {
        state.distanceSinceLastWallChange = distanceRecorded;
    }
    state.walls = newWalls;
}

void switchSpinToMove()
{
    move(&controllerset, SPEED_NORMAL);
    state.movState = MOVE;
    state.distanceSinceLastWallChange = 0.0; //this is done just in case
}

void cellChangeInGoalDirection()
{
    // wall update is always one cell in advance (as cell position updates comes later)
    position posInDir = getPosInDir(state.curPos, state.nextDirection);
    onMazePosExplored(posInDir, state.walls);
    state.curPos = posInDir;
    state.curDirection = state.nextDirection;
    state.distanceSinceLastWallChange = 0.0;
}

void setupNewGoalDirection()
{
    state.nextDirection = getNextDirection(state.curPos, state.curDirection); // receives new goal direction from mazeControl
    
    if (state.nextDirection != state.curDirection)
    {
        state.movState = TURN;
        float deltaAngle = getDifferenceInDirections(state.curDirection, state.nextDirection);
        if (deltaAngle > 0)
        {
            spin(&controllerset, SPEED_SPIN_NORMAL); // turn clockwise (/right)
        } else
        {
            spin(&controllerset, (-1)*SPEED_SPIN_NORMAL); // turn counterclockwise (/left)
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
        state.walls = WALL_SKIP_STATE; // for safety: makes sure first wall detection is considered from the "old" cell
        startDirectionControl();
    } else
    {
        state.movState = IDLE;
        move(&controllerset, 0);
    }
}

void startDirectionControl()
{
    setupNewGoalDirection();
}