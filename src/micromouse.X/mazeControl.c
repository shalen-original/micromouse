#include "xc.h"
#include "mazeControl.h"
#include "direction.h"
#include <assert.h>

int costs[16][16];
BOOL inExplorationMode = TRUE; //Race-mode <=> FALSE
position goalStates[NUMBER_OF_GOAL_STATES];

void initMazeControl()
{
    int maxCost = MAZE_WIDTH * MAZE_HEIGHT; // initially set everything here (later, only non explored should have this value)
    int xi = 0;
    int yi = 0;
    for(xi = 0; xi < MAZE_WIDTH; xi++)
    {
        for(yi = 0; yi < MAZE_HEIGHT; yi++)
        {
            position pos = {.x = xi, .y = yi};
            setCostAt(pos, maxCost);
        }
    }
    
    // setting the goal states (TODO make this more beautiful)
    goalStates[0] = posTuple(MAZE_WIDTH/2, MAZE_HEIGHT/2);
    goalStates[1] = posTuple(MAZE_WIDTH/2 - 1, MAZE_HEIGHT/2);
    goalStates[2] = posTuple(MAZE_WIDTH/2, MAZE_HEIGHT/2 - 1);
    goalStates[3] = posTuple(MAZE_WIDTH/2 - 1, MAZE_HEIGHT/2 - 1);
    
    int goalIndex = 0;
    for (goalIndex = 0; goalIndex < NUMBER_OF_GOAL_STATES; goalIndex++)
    {
        setCostAt(goalStates[goalIndex], 0);
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

// path algorithm to find fastest route from start to goal
void floodFillAlgorithm()
{
    //init floodfill from each goal position:
    int goalIndex = 0;
    for (goalIndex = 0; goalIndex < NUMBER_OF_GOAL_STATES; goalIndex++)
    {
        floodFillStep(goalStates[goalIndex]);
    }
}

//
void floodFillStep(position pos)
{
    int curCost = getCostAt(pos);
    dir curDirection = NORTH;
    // iterate over every possible direction
    int dirIndex = 0;
    for (dirIndex = 0; dirIndex < NUMBER_OF_DIR; dirIndex++)
    {
        dir direction = getDirectionListAt(dirIndex);
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
    int curCost = getCostAt(curPos);
    dir goalDirection = 0;
    int dirIndex = 0;
    // iterate over every possible direction
    for (dirIndex = 0; dirIndex < NUMBER_OF_DIR; dirIndex++)
    {
        dir direction = getDirectionListAt(dirIndex);
        position posInDir = getPosInDir(curPos, direction);
        
        if (isMazeWallAt(curPos, direction) == FALSE && getCostAt(posInDir) < curCost)
        {
            goalDirection = direction;
            curCost = getCostAt(posInDir);
        }
    }
    
    __conditional_software_breakpoint(goalDirection != 0);
    return goalDirection;
}

dir getNewExploreDirection(position curPos, dir curDirection)
{
    // Hug right wall algorithm (TODO make it more advanced)
    dir goalDirection = 0;
    dir tryDirection = getClockwise(curDirection); // dir to robot's right
    
    while (tryDirection != getInverse(curDirection))
    {
        if (isMazeWallAt(curPos, tryDirection) == FALSE)
        {
            goalDirection = tryDirection;
        }
        tryDirection = getCounterClockwise(tryDirection);
    }
    
    __conditional_software_breakpoint(goalDirection != 0);
    return goalDirection;
}

dir getNextDirection(position curPos, dir curDirection)
{
    // TODO if curPos is a goalState, switch to race mode?
    if (TRUE == inExplorationMode)
    {
        return getNewExploreDirection(curPos, curDirection);
    } else
    {
        return getNewRaceDirection(curPos);
    }
}