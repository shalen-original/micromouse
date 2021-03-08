#include "xc.h"
#include "IOconfig.h"

void initIO()
{
    AD1PCFGL=0xFFFF; // Configure all pins to be digital
    
    // Configure the sensor pins to be analogue
    AD1PCFGLbits.PCFG1 = 0b0; // S3_OUT/AN1/RA1 is analougue
    AD1PCFGLbits.PCFG2 = 0b0; // S2_OUT/AN2/RB0 is analougue
    AD1PCFGLbits.PCFG3 = 0b0; // S1_OUT/AN3/RB1 is analougue
    
    // Configure the sensor pins to be input
    TRISAbits.TRISA1 = 0b1; // S3_OUT/AN1/RA1 is input
    TRISBbits.TRISB0 = 0b1; // S2_OUT/AN2/RB0 is input
    TRISBbits.TRISB1 = 0b1; // S1_OUT/AN3/RB1 is input
    
    // PWM1 Pair 1 -> Left Motor (M1)
    // PWM1H1 -> M1_IN1
    // PWM1L1 -> M1_IN2
    // PWM1 Pair 2 -> Right Motor (M2)
    // PWM1H2 -> M2_IN1
    // PWM1L2 -> M2_IN2

    // QEI 1 -> Left Motor (M1)
    // QEI1 A -> M1_CHA
    // QEI1 B -> M1_CHB
    
    // QEI 2 -> Right Motor (M2)
    // QEI2 A -> M2_CHA
    // QEI2 B -> M2_CHB
    
    // Configure LEDs to be outputs
    LATBbits.LATB2 = 0b0;
    LATBbits.LATB3 = 0b0;
    LATCbits.LATC0 = 0b0;
    LATCbits.LATC1 = 0b0;
    
    // Configure buttons to be inputs
    TRISCbits.TRISC3 = 0b1;
    
    
    // TODO:
    
    TRISBbits.TRISB2 = 0;// UART1 TX (newer)
    //TRISBbits.TRISB8 = 0;// UART1 TX

    //PIN MAPPING --------------------------------
    //before we map, we need to unlock
    __builtin_write_OSCCONL(OSCCON & 0xbf); // clear bit 6 (unlock, they are usually write protected)
    
    // PERIPHERAL receives data from which INPUT  
    RPINR18bits.U1RXR = 10;//9; //mapped to RP9 is U1 RX

    //PERIPHERAL QEA Encoder 1, receives data from RP10
   // RPINR14bits.QEA1R = 10; 
    //PERIPHERAL QEB Encoder 1, receives data from RP11
   // RPINR14bits.QEB1R = 11;
    
    //OUTPUT PIN receives data from which PERIPHERAL, 
    //see table 11-2 in datasheet to check peripheral codes 
    RPOR1bits.RP2R = 0b00011; //output bin RP2 gets data from peripheral U1 TX 

    //after mapping we lock again
     __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS registers (lock again!)
     
    int i;
    for (i = 0; i < 30000; i++); // short dirty delay for changes to take effect
}
