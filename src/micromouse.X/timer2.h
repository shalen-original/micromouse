// guard condition
#ifndef TIMER2_H
#define	TIMER2_H

// initialices the timer 1 module (period in ms)
void initTimer2(unsigned int period);
// starts the timer 1 module
void startTimer2(void);
// action that is done whenever the cycle start is reached
void cycle2Action(void);

#endif	/* TIMER2_H */

