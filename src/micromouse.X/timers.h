#ifndef TIMERS_H
#define	TIMERS_H

void initTimer1(unsigned int period_ms);
void initTimer2(unsigned int period_ms);
void initTimer3(); // Used for OC

void startTimer1();
void startTimer2();
void startTimer3();

// To be implemented by users
void onTimer1Tick();
void onTimer2Tick();

#endif

