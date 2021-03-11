#include "xc.h"
#include "mazeControl.h"
#include "direction.h"

int costs[16][16];

void initMazeControl(int width, int height, position startPos, position goalPos[])
{
    int maxCost = width * height; // initially set everything here (later, only non explored should have this value)
    int xi = 0;
    int yi = 0;
    for(xi = 0; xi < width; xi++)
    {
        for(yi = 0; yi < height; yi++)
        {
            position pos = {.x = xi, .y = yi};
            setCostAt(pos, maxCost);
        }
    }
    
    int goalIndex = 0;
    int totalGoalStates = (int)(sizeof(goalPos) / sizeof(goalPos[0]));
    for (goalIndex = 0; goalIndex < totalGoalStates; goalIndex++)
    {
        setCostAt(goalPos[goalIndex], 0);
    }
}

int getCostAt(position pos)
{
    return costs[pos.x][pos.y];
}

void setCostAt(position pos, int val)
{
    costs[pos.x][pos.y] = val;
}

void setCostAtRelative(position pos, int val)
{
    costs[pos.x][pos.y] += val;
}

// path algorithm to find fastest route from start to goal (a* maybe better?)
void floodFillAlgorithm(position startPos, position goalPos[])
{
    //init floodfill from each goal position:
    int goalIndex = 0;
    int totalGoalStates = (int)(sizeof(goalPos) / sizeof(goalPos[0]));
    for (goalIndex = 0; goalIndex < totalGoalStates; goalIndex++)
    {
        floodFillStep(goalPos[goalIndex]);
    }
}

//
void floodFillStep(position pos)
{
    dir directions[4] = {NORTH, EAST, SOUTH, WEST};
    int dirIndex = 0;
    // iterate over every possible direction
    int curCost = getCostAt(pos);
    dir curDirection = NORTH;
    for (dirIndex = 0; dirIndex < 4; dirIndex++)
    {
        dir direction = directions[dirIndex];
        position posInDir = getPosInDir(pos, direction);
        // conditions: no wall, is explored and cost update would be valuable
        if (isMazeWallAt(pos, direction) == FALSE && isExploredCell(posInDir) == TRUE && getCostAt(posInDir) > (curCost + 1))
        {
            curDirection = direction;
            setCostAt(posInDir, curCost + 1);
            // recursive call for each position updated this way
            floodFillStep(posInDir);
        }
    }
}

//
dir getNewRaceDirection(position curPos)
{
    dir directions[4] = {NORTH, EAST, SOUTH, WEST};
    int dirIndex = 0;
    // iterate over every possible direction
    int curCost = getCostAt(curPos);
    dir curDirection = 0;
    for (dirIndex = 0; dirIndex < 4; dirIndex++)
    {
        dir direction = directions[dirIndex];
        position posInDir = getPosInDir(curPos, direction);
        
        if (isMazeWallAt(curPos, direction) == FALSE && getCostAt(posInDir) < curCost)
        {
            curDirection = direction;
            curCost = getCostAt(posInDir);
        }
    }
    
    if (curDirection == 0)
    {
        //TODO: Throw Error (no space to move to!)
    } else
    {
        return curDirection;
    }
    return 0;
}

dir getNextDirection(position curPos)
{
    // TODO implement this (returns depend on explore or race mode)
    return NORTH;
}