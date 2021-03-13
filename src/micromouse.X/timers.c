#include <xc.h>
#include "timers.h"

#include "utils.h"
#include "boolean.h"

#define TIMER_1_MAX_PERIOD 65535
#define TIMER_2_MAX_PERIOD TIMER_1_MAX_PERIOD
#define TIMER_3_MAX_PERIOD TIMER_1_MAX_PERIOD

typedef struct {
    unsigned int period;
    unsigned int prescaler;
} _TimerConfig;

_TimerConfig _computeTimerConfig(unsigned int desiredPeriod_us, unsigned int maxPeriod) {
    #define _TIMER_PRESCALER_COUNT 4
    const int prescalerDividers[_TIMER_PRESCALER_COUNT] = {1, 8, 64, 256};
    
    float period = desiredPeriod_us / MC_PERIOD_US;
    
    int i;
    for (i = 0; i < _TIMER_PRESCALER_COUNT; i++) {
        if ((period / prescalerDividers[i]) <= maxPeriod) {
            _TimerConfig ans = {
                (unsigned int) (period / prescalerDividers[i]),
                (unsigned int) i
            };
            
            return ans;
        }
    }
    
    // This point should never be reached
    __conditional_software_breakpoint(FALSE);
    
    _TimerConfig ans = {0, 0};
    return ans;
}

void initTimer1(unsigned int period_ms) {
    _TimerConfig c = _computeTimerConfig(period_ms * 1000, TIMER_1_MAX_PERIOD);
    
    T1CONbits.TCKPS = c.prescaler;
    PR1 = c.period;
    IEC0bits.T1IE = 1; // Enable Timer 1 interrupt
    T1CONbits.TON = 0; // Disable Timer 1
}

void initTimer2(unsigned int period_ms) {
    _TimerConfig c = _computeTimerConfig(period_ms * 1000, TIMER_2_MAX_PERIOD);
    
    T2CONbits.TCKPS = c.prescaler;
    PR2 = c.period;
    IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
    T2CONbits.TON = 0; // Disable Timer 2
}

void initTimer3() {
    // We want to match the update frequency of
    // the PWM1 generator (see pwm.c).
    
    _TimerConfig c = _computeTimerConfig(20, TIMER_3_MAX_PERIOD);
    
    T3CONbits.TCKPS = c.prescaler;
    PR3 = c.period;
    IEC0bits.T3IE = 0; // Disable Timer 3 interrupt (timer only used for OC)
    T3CONbits.TON = 0; // Disable Timer 3
}

void startTimer1(void) {
    T1CONbits.TON = 1;
}

void startTimer2(void) {
    T2CONbits.TON = 1;
}

void startTimer3(void) {
    T3CONbits.TON = 1;
}

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void) {
   IFS0bits.T1IF = 0;
   
   onTimer1Tick();
}


void __attribute__((__interrupt__, auto_psv)) _T2Interrupt(void) {
   IFS0bits.T2IF = 0;
   
   onTimer2Tick();
}