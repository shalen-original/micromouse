#ifndef CONTROLLER_H
#define	CONTROLLER_H

// define a class to represent PI controller
typedef struct PI;
// define a set to contain all controllers (VR,VL,DR,DL)
typedef struct Controllerset;
// initialize the set
Controllerset initControllerset();
// reset controller to new desired sp (set point)
void resetPI (PI *controller, float sp);
// receive pv (measurement), step controller and return control value
float stepPI(PI *controller, float pv);

#endif	/* CONTROLLER_H */


