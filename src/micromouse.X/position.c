#include "xc.h"
#include "position.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int distL1(position pos1, position pos2)
{
    return abs(pos2.x - pos1.x + pos2.y - pos1.y);
}

float distL2(position pos1, position pos2)
{
    return sqrt(abs(pow(pos2.x,2) - pow(pos1.x,2) + pow(pos2.y,2) - pow(pos1.y,2)));
}