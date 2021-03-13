#include "controllerUtils.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

// distance controller
void distanceControl(Controllerset *cset);

// velocity controller
void velocityControl(Controllerset *cset);
#endif /* CONTROLLER_H */