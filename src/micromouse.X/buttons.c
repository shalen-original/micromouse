#include <xc.h>

#include "buttons.h"

#define _SWITCH_1 PORTCbits.RC3
#define _SWITCH_PRESSED 0
#define _SWITCH_RELEASED 1

void initButtons() {
    CNEN2bits.CN28IE = 0b1; // Enable change notification interrupt
    IEC1bits.CNIE = 0b1; // Enable change notification interrupts
}

void __attribute__((__interrupt__, auto_psv)) _CNInterrupt(void) {
    IFS1bits.CNIF = 0;
    
    onButtonChanged(_SWITCH_1 == _SWITCH_PRESSED);
    
    if (_SWITCH_1 == _SWITCH_RELEASED) {
        onButtonClicked();
    }
}