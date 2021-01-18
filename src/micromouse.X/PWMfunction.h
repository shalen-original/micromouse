// guard condition
#ifndef PWM_H
#define	PWM_H

// configures the Pulse-Width-Module (PWM) with a period in milliseconds (ms)
void initPWM(unsigned int period); // in ms
// sets the Duty-Cycle given a percentage float
void setDC1percentage(float percentage); // percentage goes from 0 to 1 (float)

#endif	/* PWM.h */