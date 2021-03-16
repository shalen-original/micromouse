#include "xc.h"
#include "maze.h"
#include "utils.h"
#include <assert.h>

cell maze[MAZE_WIDTH][MAZE_HEIGHT]; // x is width axis (to the right), y is height axis (to the top)

void initMaze()
{
    // setting maze border walls
    unsigned int xi;
    for (xi = 0; xi < MAZE_WIDTH; xi++)
    {
        maze[xi][0].wall |= SOUTH;
        maze[xi][MAZE_HEIGHT -1].wall |= NORTH;
    }
    unsigned int yi;
    for (yi = 0; yi < MAZE_HEIGHT; yi++)
    {
        maze[0][yi].wall |= WEST;
        maze[MAZE_WIDTH -1][yi].wall |= EAST;
    }
}

void onMazePosExplored(position pos, uint8_t walls)
{
    if (getCellAt(pos)->visited == FALSE)
    {
        getCellAt(pos)->visited = TRUE;
        if ((walls & NORTH) > 0)
        {
            addMazeWall(pos, NORTH);
        }
        if ((walls & SOUTH) > 0)
        {
            addMazeWall(pos, SOUTH);
        }
        if ((walls & EAST) > 0)
        {
            addMazeWall(pos, EAST);
        }
        if ((walls & WEST) > 0)
        {
            addMazeWall(pos, WEST);
        }
    }
}

void addMazeWall(position pos, dir direction)
{
    getCellAt(pos)->wall |= direction;
    getNeighborCellInDir(pos, direction)->wall |= getInverse(direction);
}

void removeMazeWall(position pos, dir direction)
{
    getCellAt(pos)->wall &= ~direction;
    getNeighborCellInDir(pos, direction)->wall &= ~getInverse(direction);
}

cell* getNeighborCellInDir(position pos, dir direction)
{
    position neighborPos = pos;
    position posChangeFromDir = getPositionChange(direction);
    neighborPos.x += posChangeFromDir.x;
    neighborPos.y += posChangeFromDir.y;
    return getCellAt(neighborPos);
}

cell* getCellAt(position pos)
{
    __conditional_software_breakpoint(pos.x < MAZE_WIDTH && pos.x >= 0 && pos.y < MAZE_HEIGHT && pos.y >= 0);
    return &maze[pos.x][pos.y];
}

BOOL isMazeWallAt(position pos, dir direction)
{
    if (((*getCellAt(pos)).wall & direction) == direction)
    {
        return TRUE;
    } else {
        return FALSE;
    }
}

BOOL isExploredCell(position pos)
{
    __conditional_software_breakpoint(pos.x < MAZE_WIDTH && pos.x >= 0 && pos.y < MAZE_HEIGHT && pos.y >= 0);
    return maze[pos.x][pos.y].visited;
}