#include <xc.h>

#include "pwm.h"
#include "errors.h"
#include "utils.h"

#define _PWM_MAX_SAFE_DUTY_CYCLE 0.66

void initPWM1() 
{
    P1TCONbits.PTEN = 0; // Stop PWM 1 generator
    
    // Requested update frequency is 50kHz = 20 µs period, as per
    // the f_{PWM} of the DRV8833.
    // Base frequency is 26.6 MHz = 37.5 ns period.
    // max(PTPER) = MAX_UINT15 = 2^15 - 1 = 32767
    // Prescaler /1: 20 üs / 37.5 ns = 533.33 < MAX_UINT15
    
    P1TCONbits.PTCKPS = 0b00; // 1:1 prescale
    P1TPERbits.PTPER = 533; // Determines PWM period
    PWM1CON1bits.PEN1H = 0b1; // Enable PWM on PWM1H1
    PWM1CON1bits.PEN1L = 0b1; // Enable PWM on PWM1L1
    PWM1CON1bits.PEN3H = 0b1; // Enable PWM on PWM1H3
    PWM1CON1bits.PEN3L = 0b1; // Enable PWM on PWM1L3
    
    PWM1CON1bits.PMOD1 = 0b1; // Pair 1 is in independent mode
    PWM1CON1bits.PMOD3 = 0b1; // Pair 3 is in independent mode
    
    P1DC1 = 0; // Duty cycle pair 1 to zero
    P1DC3 = 0; // Duty cycle pair 3 to zero
    
    // Prepare initial configuration with all pins to 0
    overridePWM1H1_LOW();
    overridePWM1L1_LOW();
    overridePWM1H3_LOW();
    overridePWM1L3_LOW();
    
    P1TCONbits.PTEN = 1; // Start PWM 1 generator
}

int _computePwmDutyCycle(float dc) {
    dc = lerp(dc, 0, _PWM_MAX_SAFE_DUTY_CYCLE);
    if (dc < 0 || dc > _PWM_MAX_SAFE_DUTY_CYCLE) {
        return ERR_DUTY_CYCLE_INVALID;
    }
    
    // PWM1Hx, which is active low. Therefore, a x% duty cycle
    // means PTPER - (PTPER * x/100).
    // Due to the fact that PTPER is shifted left once by the PWM unit, 
    // we have to multiply it by 2
    
    return 2 * (P1TPERbits.PTPER - (P1TPERbits.PTPER * dc));
}

int setPWM1Pair1DutyCycle(float dc) {
    int ans = _computePwmDutyCycle(dc);
    
    if (ans >= 0) {
        P1DC1 = ans;
        return ERR_OK;
    }
    
    return ans;
}

int setPWM1Pair3DutyCycle(float dc) {
    int ans = _computePwmDutyCycle(dc);
    
    if (ans >= 0) {
        P1DC3 = ans;
        return ERR_OK;
    }
    
    return ans;
}

void overridePWM1H1_HIGH() {
    // TODO need to look better. POUT1H == 1 means
    // pin 'active', but active high or active low?
    P1OVDCONbits.POUT1H = 0b0;
    P1OVDCONbits.POVD1H = 0b0;
}

void overridePWM1H1_LOW() {
    P1OVDCONbits.POUT1H = 0b1;
    P1OVDCONbits.POVD1H = 0b0;
}

void disableOverridePWM1H1() {
    P1OVDCONbits.POVD1H = 0b1;
}



void overridePWM1L1_HIGH() {
    P1OVDCONbits.POUT1L = 0b0;
    P1OVDCONbits.POVD1L = 0b0;
}

void overridePWM1L1_LOW() {
    P1OVDCONbits.POUT1L = 0b1;
    P1OVDCONbits.POVD1L = 0b0;
}

void disableOverridePWM1L1() {
    P1OVDCONbits.POVD1L = 0b1;
}



void overridePWM1H3_HIGH() {
    P1OVDCONbits.POUT3H = 0b0;
    P1OVDCONbits.POVD3H = 0b0;
}

void overridePWM1H3_LOW() {
    P1OVDCONbits.POUT3H = 0b1;
    P1OVDCONbits.POVD3H = 0b0;
}

void disableOverridePWM1H3() {
    P1OVDCONbits.POVD3H = 0b1;
}



void overridePWM1L3_HIGH() {
    P1OVDCONbits.POUT3L = 0b0;
    P1OVDCONbits.POVD3L = 0b0;
}

void overridePWM1L3_LOW() {
    P1OVDCONbits.POUT3L = 0b1;
    P1OVDCONbits.POVD3L = 0b0;
}

void disableOverridePWM1L3() {
    P1OVDCONbits.POVD3L = 0b1;
}