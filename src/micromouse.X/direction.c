#include "xc.h"
#include "direction.h"
#include <assert.h>

dir getInverse(dir direction)
{
    dir inverse;
    switch (direction)
    {
        case NORTH:
            inverse = SOUTH;
            break;
        case SOUTH:
            inverse = NORTH;
            break;
        case EAST:
            inverse = WEST;
            break;
        case WEST:
            inverse = EAST;
            break;
    }
    return inverse;
}

dir getClockwise(dir direction)
{
    dir clockwise;
    if (direction == WEST)
    {
        direction = NORTH;
    } else
    {
        clockwise = direction << 1;
    }
    return clockwise;
}

dir getCounterClockwise(dir direction)
{
    dir counterClockwise;
    if (direction == NORTH)
    {
        counterClockwise = WEST;
    } else 
    {
        counterClockwise = direction >> 1;
    }
    return counterClockwise;
}

position getPositionChange(dir direction)
{
    position posChange;
    posChange.x = 0;
    posChange.y = 0;
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
    position neighborPos = pos;
    switch (direction)
    {
        case NORTH:
            neighborPos.y ++;
            break;
        case SOUTH:
            neighborPos.y --;
            break;
        case EAST:
            neighborPos.x ++;
            break;
        case WEST:
            neighborPos.x --;
            break;
    }
    return neighborPos;
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

dir floatToDir(float angle, int errorMargin)
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

BOOL directionEqualsAngle(dir direction, float angle, int errorMargin)
{
    if (direction == floatToDir(angle, errorMargin))
    {
        return TRUE;
    }
    return FALSE;
}