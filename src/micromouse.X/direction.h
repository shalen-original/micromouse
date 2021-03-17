#ifndef DIRECTION_H
#define	DIRECTION_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "position.h"

#define MAX_DIR_INT 8
#define NUMBER_OF_DIR 4
/*
 * Cardinal direction with global axis
 * NORTH is in positive y direction (explained in position.h)
 * expressed as bitfield to utilize bitwise operators
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

// converts direction to float and vice versa
float dirToFloat(dir direction);
dir floatToDir(float angle, unsigned int errorMargin);

// equality functions with errorMargin
BOOL directionEqualsAngle(dir direction, float angle, unsigned int errorMargin);
BOOL angleEqualsAngle(float angle1, float angle2, unsigned int errorMargin);

//difference from dir1 to dir2
float getDifferenceInDirections(dir dir1, dir dir2);
// returns a direction at index in clockwise order starting from NORTH
dir getDirectionListAt(unsigned int index);

#endif	/* DIRECTION_H */

