#include <xc.h>
#include "timers.h"

#include "utils.h"
#include "boolean.h"

#define TIMER_1_MAX_PERIOD 65535
#define TIMER_2_MAX_PERIOD TIMER_1_MAX_PERIOD

typedef struct {
    unsigned int period;
    unsigned int prescaler;
} _TimerConfig;

_TimerConfig _computeTimerConfig(unsigned int desiredPeriod_ms, unsigned int maxPeriod) {
    #define _TIMER_PRESCALER_COUNT 4
    const int prescalerDividers[_TIMER_PRESCALER_COUNT] = {1, 8, 64, 256};
    
    float period = desiredPeriod_ms / (MC_PERIOD_MS / 1000);
    
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
    _TimerConfig c = _computeTimerConfig(period_ms, TIMER_1_MAX_PERIOD);
    
    T1CONbits.TCKPS = c.prescaler;
    PR1 = c.period;
    IEC0bits.T1IE = 1; // Enable Timer 1 interrupt
    T1CONbits.TON = 0; // Disable Timer 1
}

void initTimer2(unsigned int period_ms) {
    _TimerConfig c = _computeTimerConfig(period_ms, TIMER_2_MAX_PERIOD);
    
    T2CONbits.TCKPS = c.prescaler;
    PR2 = c.period;
    IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
    T2CONbits.TON = 0; // Disable Timer 2
}

void startTimer1(void) {
    T1CONbits.TON = 1;
}

void startTimer2(void) {
    T2CONbits.TON = 1;
}

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void) {
   IFS0bits.T1IF = 0;
   
   onTimer1Tick();
}


void __attribute__((__interrupt__, auto_psv)) _T2Interrupt(void) {
   IFS0bits.T2IF = 0;
   
   onTimer2Tick();
}