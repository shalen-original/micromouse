// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAZE_H
#define	MAZE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "directionControl.h"
#include "utils.h"

typedef struct { // cell struct
    BOOL visited;
    uint8_t wall; // 8 bit integer, we need only 4 bits
} cell;

// setups maze with border walls
void initMaze(int width, int height);
// gets cell at target maze position
cell* getCellAt(position pos);
// get cell at (pos + moving once in direction)
cell* getNeighborCellInDir(position pos, dir direction);

// adds all walls encoded in int
void onMazePosExplored(position pos, uint8_t walls);
// adds a wall to maze pos and direction
void addMazeWall(position pos, dir direction);
// same for removal
void removeMazeWall(position pos, dir direction);
// checks if wall at specified pos and dir exists
BOOL isMazeWallAt(position pos, dir direction);
//
BOOL isExploredCell(position pos);

#endif	/* MAZE_H */

