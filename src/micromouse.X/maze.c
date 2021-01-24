#include "xc.h"
#include "maze.h"
#include "utils.h"
#include <assert.h>

unsigned int mazeWidth;
unsigned int mazeHeight;
cell maze[16][16]; // x is width axis (to the right), y is height axis (to the top)

void initMaze(int width, int height)
{
    mazeWidth = width;
    mazeHeight = height;
    //maze = cell[width][height];
    
    // setting maze border walls
    unsigned int xi;
    for (xi = 0; xi < width; xi++)
    {
        maze[xi][0].wall |= SOUTH;
        maze[xi][mazeHeight-1].wall |= NORTH;
    }
    unsigned int yi;
    for (yi = 0; yi < height; yi++)
    {
        maze[0][yi].wall |= WEST;
        maze[mazeWidth -1][yi].wall |= EAST;
    }
}

void addMazeWall(position pos, dir direction)
{
    cell curCell = *getCellAt(pos);
    cell nextCellInDir = *getNeighborCellInDir(pos, direction);
    
    switch (direction)
    {
        case NORTH:
            curCell.wall |= NORTH;
            nextCellInDir.wall |= SOUTH;
            break;
        case SOUTH:
            curCell.wall |= SOUTH;
            nextCellInDir.wall |= NORTH;
            break;
        case EAST:
            curCell.wall |= EAST;
            nextCellInDir.wall |= WEST;
            break;
        case WEST:
            curCell.wall |= WEST;
            nextCellInDir.wall |= EAST;
            break;
    }
}

void removeMazeWall(position pos, dir direction)
{
    cell curCell = *getCellAt(pos);
    cell nextCellInDir = *getNeighborCellInDir(pos, direction);
    switch (direction)
    {
        case NORTH:
            curCell.wall &= ~NORTH;
            nextCellInDir.wall &= ~SOUTH;
            break;
        case SOUTH:
            curCell.wall &= ~SOUTH;
            nextCellInDir.wall &= ~NORTH;
            break;
        case EAST:
            curCell.wall &= ~EAST;
            nextCellInDir.wall &= ~WEST;
            break;
        case WEST:
            curCell.wall &= ~WEST;
            nextCellInDir.wall &= ~EAST;
            break;
    }
}

cell* getNeighborCellInDir(position pos, dir direction)
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
    return getCellAt(neighborPos);
}

cell* getCellAt(position pos)
{
    assert(pos.x < mazeWidth && pos.x >= 0 && pos.y < mazeHeight && pos.y >= 0);
    return &maze[pos.x][pos.y];
}

void floodFillAlgorithm(position startPos, position goalPos)
{
    return; // TODO
}