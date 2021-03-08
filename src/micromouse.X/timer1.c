#include "xc.h"
#include "timer1.h"
#include "IOconfig.h"
#include "pwm.h"
#include "serialComms.h"
#include <stdio.h>
#include <math.h>
#include "robotControl.h"
#include "controller.h"
#include "dma.h"
#include "halapi.h"

char sendData[100]; // buffer to send data
unsigned int timerInterruptFrequency = 1; // timer interrupt call frequency in ms
unsigned int cycleInMilliSeconds = 2000; // fixed cycle length in milliseconds
extern Controllerset controllerset; // connect to global variable

void initTimer1(unsigned int period) 
{
    timerInterruptFrequency = period;
    T1CON = 0;              // ensure Timer 1 is in reset state
    T1CONbits.TGATE = 0;    // gated time accumulation disabled
    
    T1CONbits.TCKPS = 0b00; // FCY divide by 1 (default)
    // Calculate right divisor
    int fcydivisorssize = 4;
    int fcydivisors[4] = {1, 8, 64, 256};
    float tRide = period / 0.0000375;
    float tRideNow = tRide;
    int i;
    for (i = 0; i < fcydivisorssize; i++) {
        if ((tRideNow / fcydivisors[i]) <= 65535) {
            tRide = tRideNow / fcydivisors[i];
            T1CONbits.TCKPS = i;
            break;
        }
    }
    
    
    T1CONbits.TCS = 0;      // select internal FCY clock source
    TMR1 = 0;
    PR1 = (int)tRide;       // set Timer 1 period register ()
    IFS0bits.T1IF = 0;      // reset Timer 1 interrupt flag
    IPC0bits.T1IP = 4;      // set Timer1 interrupt priority level to 4
    IEC0bits.T1IE = 1;      // enable Timer 1 interrupt
    T1CONbits.TON = 0;      // leave timer disabled initially
}

void startTimer1(void) 
{
    T1CONbits.TON = 1;      // enables the timer
}

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void)
{
   static int count=0;
   static float time=0.0;
   unsigned int maxCycleCount = cycleInMilliSeconds / timerInterruptFrequency;
    
   IFS0bits.T1IF = 0;           // reset Timer 1 interrupt flag 
   
   time += ((float)timerInterruptFrequency / 1000);
   LED4=~LED4;
   
   sprintf(sendData, "%f, %d, %d, %d\n", (double) time, RAW_SENSOR_FRONT, RAW_SENSOR_LEFT, RAW_SENSOR_RIGHT);
   putsUART1(sendData);
   
   onSensorUpdate(timerInterruptFrequency, RAW_SENSOR_FRONT, RAW_SENSOR_LEFT, RAW_SENSOR_RIGHT);
   
   // ------------------------Control part begins-----------------------------
    float sensorR = getDistanceRight_mm();
    float sensorL = getDistanceLeft_mm();
    float sensorF = getDistanceFront_mm();
    
    distanceControl(&controllerset, sensorR, sensorL, sensorF);
   
    // ------------------------Control part ends------------------------------
  

   if (count >= maxCycleCount)
   {
       cycleAction();
       count = 0;
   }
   // end of actions
   count++;
}

void cycleAction()
{
    return;
}