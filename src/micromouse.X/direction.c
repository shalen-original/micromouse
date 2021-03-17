#include "xc.h"
#include "direction.h"
#include <assert.h>
#include <math.h>

dir getInverse(dir direction)
{
    return getClockwise(getClockwise(direction));
}

dir getClockwise(dir direction)
{
    dir clockwise = direction << 1;
    if (clockwise > MAX_DIR_INT)
    {
        clockwise = NORTH;
    }
    return clockwise;
}

dir getCounterClockwise(dir direction)
{
    dir counterClockwise = direction >> 1;
    if (direction == NORTH)
    {
        counterClockwise = WEST;
    }
    return counterClockwise;
}

position getPositionChange(dir direction)
{
    position posChange = {.x = 0, .y = 0};
    switch (direction)
    {
        case NORTH:
            posChange.y ++;
            break;
        case SOUTH:
            posChange.y --;
            break;
        case EAST:
            posChange.x ++;
            break;
        case WEST:
            posChange.x --;
            break;
    }
    return posChange;
}

dir getDirectionFromPos(position positionChange)
{
    dir direction;
    if (positionChange.x == 1 && positionChange.y == 0)
    {
        direction = EAST;
    } else if (positionChange.x == -1 && positionChange.y == 0)
    {
        direction = WEST;
    } else if (positionChange.x == 0 && positionChange.y == 1)
    {
        direction = NORTH;
    } else if (positionChange.x == 0 && positionChange.y == -1)
    {
        direction = SOUTH;
    }
    return direction;
}

position getPosInDir(position pos, dir direction)
{
    position posChange = getPositionChange(direction);
    return addTwoPositions(pos, posChange);
}

float dirToFloat(dir direction)
{
    float angle = 0;
    switch (direction)
    {
        case NORTH:
            angle = 90;
            break;
        case SOUTH:
            angle = 270;
            break;
        case EAST:
            angle = 0;
            break;
        case WEST:
            angle = 180;
            break;
    }
    return angle;
}

dir floatToDir(float angle, unsigned int errorMargin)
{
    __conditional_software_breakpoint(errorMargin > 0 && errorMargin <= 40 && angle >= 0 && angle <= 360);
    dir directions[4] = {NORTH, EAST, SOUTH, WEST};
    int dirIndex = 0;
    for (dirIndex = 0; dirIndex < 4; dirIndex ++)
    {
        float dirAngle = dirToFloat(directions[dirIndex]);
        if (angle > dirAngle - errorMargin && angle < dirAngle + errorMargin)
        {
            return directions[dirIndex];
        }
    }
    return 0; // should not happen and result in error
}

BOOL directionEqualsAngle(dir direction, float angle, unsigned int errorMargin)
{
    if (direction == floatToDir(angle, errorMargin))
    {
        return TRUE;
    }
    return FALSE;
}

BOOL angleEqualsAngle(float angle1, float angle2, unsigned int errorMargin)
{
    if (fabsf(angle2 - angle1) <= errorMargin)
    {
        return TRUE;
    }
    return FALSE;
}

//difference from dir1 to dir2
float getDifferenceInDirections(dir dir1, dir dir2)
{
    float angle1 = dirToFloat(dir1);
    float angle2 = dirToFloat(dir2);
    
    float diffAngle = angle2 - angle1;
    if ((diffAngle > 0 && diffAngle <= 180) || (diffAngle < 0 && diffAngle >= -180))
    {
        return (-1) * diffAngle;
    } else
    {
        return 360 - diffAngle;
    }
}

dir getDirectionListAt(unsigned int index)
{
    __conditional_software_breakpoint(index < NUMBER_OF_DIR);
    return (NORTH << index);
}