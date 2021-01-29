#include "xc.h"
#include "direction.h"

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
    switch (direction)
    {
        case NORTH:
            clockwise = EAST;
            break;
        case SOUTH:
            clockwise = WEST;
            break;
        case EAST:
            clockwise = SOUTH;
            break;
        case WEST:
            clockwise = NORTH;
            break;
    }
    return clockwise;
}

dir getCounterClockwise(dir direction)
{
    dir counterClockwise;
    switch (direction)
    {
        case NORTH:
            counterClockwise = WEST;
            break;
        case SOUTH:
            counterClockwise = EAST;
            break;
        case EAST:
            counterClockwise = NORTH;
            break;
        case WEST:
            counterClockwise = SOUTH;
            break;
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