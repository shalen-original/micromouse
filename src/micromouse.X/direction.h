#ifndef DIRECTION_H
#define	DIRECTION_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "position.h"

/*
 * Cardinal direction with global axis
 * NORTH is in positive y direction (explained in position.h)
 * expressed as binary to utilize bitwise operators
 */
typedef enum
{
    NORTH = 0b0001,
    EAST = 0b0010,
    SOUTH = 0b0100,
    WEST = 0b1000
} dir;

dir getInverse(dir direction);
dir getClockwise(dir direction);
dir getCounterClockwise(dir direction);

position getPositionChange(dir direction);
dir getDirectionFromPos(position positionChange);

position getPosInDir(position pos, dir direction);

float dirToFloat(dir direction);
dir floatToDir(float angle, int errorMargin);
BOOL directionEqualsAngle(dir direction, float angle, int errorMargin);

#endif	/* DIRECTION_H */

