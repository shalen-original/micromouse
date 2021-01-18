#include "xc.h"
#include "PWMfunction.h"

void initPWM(unsigned int period) 
{
    P1TCONbits.PTEN = 0; // switch off PWM generator
    P1TCONbits.PTCKPS = 0b00; // prescaler 1, 4, 16, 64
    
    period /= 0.0000375; // ms divided by 37.5 nsec
    
    while(period > 32767 && P1TCONbits.PTCKPS != 0b11) {
        P1TCONbits.PTCKPS += 0b1;
        period /= 4;
    }
    P1TPER = period; // 15 bit register
    PWM1CON1bits.PMOD1 = 1; // set PWM Unit 1 to independent mode
    
    PWM1CON1bits.PEN1H = 1; // enable PWM driver PWM1H1
    PWM1CON1bits.PEN2H = 0; // enable PWM driver PWM1H1
    PWM1CON1bits.PEN3H = 0; // enable PWM driver PWM1H1
    PWM1CON1bits.PEN1L = 0; // enable PWM driver PWM1H1
    PWM1CON1bits.PEN2L = 0; // enable PWM driver PWM1H1
    PWM1CON1bits.PEN3L = 0; // enable PWM driver PWM1H1
    
    P1TCONbits.PTEN = 1; // switch on PWM generator
    // To reach 100% DC we need to put 26666 * 2 into the DC register
    // 16 bit registers (65535 bzw. 32767)
    P1DC1 = 0;
    P1DC2 = 0;
    P1DC3 = 0;
    setDC1percentage(0);
}

void setDC1percentage(float percentage) 
{
    if (percentage > 1 || percentage < 0) {return;}
    P1DC1 = (P1TPER * 2) * (1-percentage);
}