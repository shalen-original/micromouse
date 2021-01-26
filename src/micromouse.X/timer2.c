#include "xc.h"
#include "timer2.h"
#include "IOconfig.h"
#include "PWMfunction.h"
#include "serialComms.h"
#include <stdio.h>
#include <math.h>
#include "dma.h"

unsigned int timer2InterruptFrequency = 1; // timer interrupt call frequency in ms
unsigned int cycle2InMilliSeconds = 2000; // fixed cycle length in milliseconds

void initTimer2(unsigned int period) 
{
    timer2InterruptFrequency = period;
    T2CON = 0;              // ensure Timer 1 is in reset state
    T2CONbits.TGATE = 0;    // gated time accumulation disabled
    
    T2CONbits.TCKPS = 0b00; // FCY divide by 1 (default)
    // Calculate right divisor
    int fcydivisorssize = 4;
    int fcydivisors[4] = {1, 8, 64, 256};
    float tRide = period / 0.0000375;
    float tRideNow = tRide;
    int i;
    for (i = 0; i < fcydivisorssize; i++) {
        if ((tRideNow / fcydivisors[i]) <= 65535) {
            tRide = tRideNow / fcydivisors[i];
            T2CONbits.TCKPS = i;
            break;
        }
    }
    
    
    T2CONbits.TCS = 0;      // select internal FCY clock source
    TMR2 = 0;
    PR2 = (int)tRide;       // set Timer 1 period register ()
    IFS0bits.T2IF = 0;      // reset Timer 1 interrupt flag
    IPC1bits.T2IP = 4;      // set Timer1 interrupt priority level to 4
    IEC0bits.T2IE = 1;      // enable Timer 1 interrupt
    T2CONbits.TON = 0;      // leave timer disabled initially
}

void startTimer2(void) 
{
    T2CONbits.TON = 1;      // enables the timer
}

void __attribute__((__interrupt__, auto_psv)) _T2Interrupt(void)
{
   static int count=0;
   static float time=0.0;
   unsigned int maxCycleCount = cycle2InMilliSeconds / timer2InterruptFrequency;
    
   IFS0bits.T2IF = 0;           // reset Timer 1 interrupt flag 
   
   time += ((float)timer2InterruptFrequency / 1000);
   
  
   if (count >= maxCycleCount)
   {
       cycleAction();
       count = 0;
   }
   // end of actions
   count++;
}

void cycle2Action()
{
    return;
}