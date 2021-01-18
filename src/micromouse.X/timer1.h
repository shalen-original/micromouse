// guard condition
#ifndef TIMER1_H
#define	TIMER1_H

// initialices the timer 1 module (period in ms)
void initTimer1(unsigned int period);
// starts the timer 1 module
void startTimer1(void);
// action that is done whenever the cycle start is reached
void cycleAction(void);

#endif	/* TIMER1_H */

