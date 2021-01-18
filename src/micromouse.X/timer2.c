#include "xc.h"
#include "timer2.h"
#include "IOconfig.h"
#include "PWMfunction.h"
#include <stdio.h>
#include <math.h>
#include "dma.h"

#define PI 3.14159265

char sendData[100]; // buffer to send data
unsigned int timerInterruptFrequency = 1; // timer interrupt call frequency in ms

void initTimer2(unsigned int period) 
{
    timerInterruptFrequency = period;
    T2CON = 0;              // ensure Timer 2 is in reset state
    
    T2CONbits.TCKPS = 0b00; // FCY divide by 1, 8, 64, 256
    
    int fcydivisorssize = 4;
    int fcydivisors[4] = {1, 8, 64, 256};
    float Tride = period / 0.0000375;
    float Tridenow = Tride;
    int i;
    for (i = 0; i < fcydivisorssize; i++) {
        if ((Tridenow / fcydivisors[i]) <= 65535) {
            Tride = Tridenow / fcydivisors[i];
            T2CONbits.TCKPS = i;
            break;
        }
    }
    T2CONbits.TGATE = 0;    // gated time accumulation disabled
    //T2CONbits.TCKPS = 0b10; // FCY divide by 64: tick = 2.4us
    T2CONbits.TCS = 0;      // select internal FCY clock source
    TMR2 = 0;
    PR2 = (int)Tride; // set Timer 2 period register ()
    IFS0bits.T2IF = 0;
    //IFS1bits.T2IF = 0;      // reset Timer 1 interrupt flag
    IPC1bits.T2IP = 4;      // set Timer1 interrupt priority level to 4
    IEC0bits.T2IE = 1;      // enable Timer 1 interrupt
    //IEC1bits.T4IE //TODO DAFUQ?
    T2CONbits.TON = 0;      // leave timer disabled initially
}

void startTimer2(void) 
{
    T2CONbits.TON = 1; //
 
}

void __attribute__((__interrupt__, auto_psv)) _T2Interrupt(void)
{
   static unsigned int count=0;
   static unsigned int pwmCount = 0;
   static float time=0.0;
   static unsigned char myChar = 'A';
    
   unsigned int maxPWMcount = (int)getCycleInMilliSeconds() / timerInterruptFrequency; // determines the max value the PWM counter counts (it will always count to a number so the Cycle value time is reached)
   
   IFS0bits.T2IF = 0;           // reset Timer 2 interrupt flag 
   
   time += ((float)timerInterruptFrequency / 1000);
   LED4=~LED4;
   //LED5 = LEDOFF;
   //LED6 = LEDOFF;
   //LED7 = LEDOFF;
   
   //U1TXREG = myChar; // should now send A to Z
   
   //setDC1percentage((sin((pwmCount * 2 * PI) / maxPWMcount)+1)/2);
   
   //if (pwmCount % (maxPWMcount / (2*2)) == 0) { // 2*2 (2 ticks on, 2 ticks off)
       //LED7 = ~LED7;
   //}
   
   sprintf(sendData, "%f, %d, %d \n", (double) time, TEST_SENSOR, IO_1);
   putsUART1(sendData);
   
   // Reset counters upon reaching max value
   if (count >= MAX_COUNT) {
       count = 0;
   }
   if (pwmCount >= maxPWMcount) {
       //LED6=~LED6; // led6 shows on/off for each pwm cycle
       pwmCount = 0;
   }
   if (myChar == 'Z') {
       myChar = 'A' - 1;
   }
   
   count ++;
   pwmCount ++;
   myChar ++;
}

