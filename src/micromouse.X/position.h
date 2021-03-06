#ifndef POSITION_H
#define	POSITION_H

#include <xc.h>
#include "boolean.h"

/*
 * 2D position in maze
 * each position corresponds to one maze cell
 * origin (0,0) is at the bottom left
 * x axis goes to the right
 * y axis goes to the top
 */
typedef struct {
    int x;
    int y;
} position;

// returns position from tuple
position posTuple(unsigned int xi, unsigned int yi);

// returns the absolute l1 distance from pos1 to pos2
unsigned int distL1(position pos1, position pos2);
// returns the absolute l2 distance from pos1 to pos2
float distL2(position pos1, position pos2);
// returns the piecewise sum of both positions as position
position addTwoPositions(position pos1, position pos2);
// == compare between positions
BOOL equalsPos(position pos1, position pos2);
// is neighbor of
BOOL isAdjacentToEachOther(position pos1, position pos2);

#endif	/* POSITION_H */

