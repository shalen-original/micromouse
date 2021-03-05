// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef POSITION_H
#define	POSITION_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "boolean.h"

typedef struct { // general 2D maze cell position
    int x;
    int y;
} position;

// returns the absolute l1 distance from pos1 to pos2
unsigned int distL1(position pos1, position pos2);
// returns the absolute l2 distance from pos1 to pos2
float distL2(position pos1, position pos2);
// == compare between positions
BOOL equalsPos(position pos1, position pos2);
// is neighbor of
BOOL isAdjacentToEachOther(position pos1, position pos2);

#endif	/* POSITION_H */

