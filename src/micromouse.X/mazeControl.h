#ifndef MAZE_CONTROL_H
#define	MAZE_CONTROL_H

#include <xc.h>
//#include "utils.h"
#include "maze.h"

#define NUMBER_OF_GOAL_STATES 4

// setups maze control
void initMazeControl();

// returns floodfillcost at position
int getCostAt(position pos);
// setter
void setCostAt(position pos, int val);
void setCostAtRelative(position pos, int val);

// path algorithm to find fastest route from start to goal (a* maybe better?)
void floodFillAlgorithm();
// one step of the floodfill (fill every space around pos and call this recursively)
void floodFillStep(position pos);

// returns the direction the robot should move next (based on floodfill values)
dir getNewRaceDirection(position curPos);
// returns the next direction in exploration mode
dir getNewExploreDirection(position curPos, dir curDirection);
// depending on explore or race-mode, calls one of the two above functions
dir getNextDirection(position curPos, dir curDirection);

// switches the module from exploration to race-mode (executing floodfill in between)
void switchToRaceMode();

#endif	/* MAZE_CONTROL_H */

