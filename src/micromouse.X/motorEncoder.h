// guard condition
#ifndef MOTOR_ENCODER_H
#define	MOTOR_ENCODER_H

#include <xc.h> // include processor files - each processor file is guarded.  

// configures the Quadrature Encoder 1 and 2 (input is the starting position of the wheels)
void initQEI1(unsigned int startPos);
void initQEI2(unsigned int startPos);

#endif	/* MOTOR_ENCODER_H */