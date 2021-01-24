#include "xc.h"
#include "robotControl.h"
#include "utils.h"

typedef enum // movement state of robot
{
    IDLE=0,
    MOVE,
    TURNL,
    TURNR
} movementState;

typedef enum // environement state of robot (where are walls)
{
    LRWALL=0,
    LWALL,
    RWALL,
    NWALL
} envState;

movementState robotMoveState;
envState robotEnvironmentState;

position startPos;
position curPos;

void initRobot()
{
    startPos.x = 0, curPos.x = 0;
    startPos.y = 0, curPos.y = 0;
    
    robotMoveState = IDLE;
    robotEnvironmentState = NWALL;
}