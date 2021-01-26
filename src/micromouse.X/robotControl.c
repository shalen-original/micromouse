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

// general move function (where both motor move have to turn with same speed)
void move(int steps, int maxSpeed, int exitSpeed)
{
    //TODO
}
// uses move() to move straight ahead
void driveStraight(int steps, int maxSpeed, int exitSpeed)
{
    //TODO
}
// turn 90° smoothly (motors not with same speed)
void turn90Left(int maxSpeed)
{
    //TODO
}
void turn90Right(int maxSpeed)
{
    //TODO
}
// rotates while standing (both motors with same speed, but inversed to each other)
void spin(int steps, int maxSpeed)
{
    //TODO
}