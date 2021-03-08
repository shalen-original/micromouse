#include "xc.h"
#include "qei.h"

static long _rotationCountQEI1 = 0;
static long _rotationCountQEI2 = 0;

void initQEI() 
{
    // TODO one of the two SWPABs needs to be 1
    
    QEI1CONbits.QEIM = 0b111; //4x mode, reset by MAX1CNT
    QEI1CONbits.SWPAB = 0; // Phase A and B not swapped
    POS1CNT = 0;
    IEC3bits.QEI1IE = 0b1; // Enable interrupt
    
    QEI2CONbits.QEIM = 0b111; //4x mode, reset by MAX2CNT
    QEI2CONbits.SWPAB = 0; // Phase A and B not swapped
    POS2CNT = 0;
    IEC4bits.QEI2IE = 0b1; // Enable interrupt
}

long getQEI1Position() {
    return _rotationCountQEI1 + POS1CNT;
}

long getQEI2Position() {
    return _rotationCountQEI2 + POS2CNT;
}

void __attribute__((__interrupt__, auto_psv)) _QEI1Interrupt(void)
{
    IFS3bits.QEI1IF = 0;
    
    if (POS1CNT < (MAX1CNT / 2)) {
        // Interrupt was triggered by an overflow
        _rotationCountQEI1 += MAX1CNT;
    }
    
    if (POS1CNT > (MAX1CNT / 2)) {
        // Interrupt was triggered by an underflow
        _rotationCountQEI1 -= MAX1CNT;
    }
}

void __attribute__((__interrupt__, auto_psv)) _QEI2Interrupt(void)
{
    IFS4bits.QEI2IF = 0;
    
    if (POS2CNT < (MAX2CNT / 2)) {
        // Interrupt was triggered by an overflow
        _rotationCountQEI2 += MAX2CNT;
    }
    
    if (POS2CNT > (MAX2CNT / 2)) {
        // Interrupt was triggered by an underflow
        _rotationCountQEI2 -= MAX2CNT;
    }
}