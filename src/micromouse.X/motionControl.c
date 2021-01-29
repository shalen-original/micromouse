#include "xc.h"
#include "motionControl.h"


void initMotionControl()
{
    // TODO
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