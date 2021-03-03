#include "controllerUtils.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

// initialize controller set
void initControllerset(Controllerset *cset);

// distance controller
void distanceControl(Controllerset *cset, float sensorR, float sensorL, float sensorF);

#endif /* CONTROLLER_H */