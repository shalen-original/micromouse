#ifndef MAZE_H
#define	MAZE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "directionControl.h"
#include "utils.h"

typedef struct { // cell struct
    BOOL visited;
    uint8_t wall; // 8 bit integer, we need only 4 bits
} cell;

#define MAZE_WIDTH 16
#define MAZE_HEIGHT 16

// setups maze with border walls
void initMaze();
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
// checks whether cell at position pos has been explored
BOOL isExploredCell(position pos);

// fills buffer with maze map
void getMazeMapInBuffer(uint8_t *buffer);

#endif	/* MAZE_H */

