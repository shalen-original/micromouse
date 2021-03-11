// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAZE_CONTROL_H
#define	MAZE_CONTROL_H

#include <xc.h>
//#include "utils.h"
#include "maze.h"

// setups maze control
void initMazeControl();
// returns floodfillcost at position
int getCostAt(position pos);
// setter
void setCostAt(position pos, int val);
void setCostAtRelative(position pos, int val);
// path algorithm to find fastest route from start to goal (a* maybe better?)
void floodFillAlgorithm(position startPos, position goalPos[]);
// one step of the floodfill (fill every space around pos and call this recursively)
void floodFillStep(position pos);
// returns the direction the robot should move next (based on floodfill values)
dir getNewRaceDirection(position curPos);

dir getNextDirection(position curPos);
#endif	/* MAZE_CONTROL_H */

