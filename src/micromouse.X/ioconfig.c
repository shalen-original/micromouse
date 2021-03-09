#include "xc.h"
#include "ioconfig.h"

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
    
    // Configure LEDs to be outputs
    LATBbits.LATB2 = 0b0;
    LATBbits.LATB3 = 0b0;
    LATCbits.LATC0 = 0b0;
    LATCbits.LATC1 = 0b0;
    
    // Configure buttons to be inputs
    TRISCbits.TRISC3 = 0b1;
    
    // Remap pins (see tables 11-1 and 11-2 on the datasheet)
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    
    // PWM1 Pair 1 -> Left Motor (M1)
    //RPOR5bits.RP10R = 0b00011;   // PWM1H1 -> M1_IN1/RP23
    //RPOR5bits.RP10R = 0b00011;   // PWM1L1 -> M1_IN2/RP24
    
    // PWM1 Pair 2 -> Right Motor (M2)
    // PWM1H2 -> M2_IN1
    // PWM1L2 -> M2_IN2
    
    // QEI1 -> Left Motor (M1)
    RPINR14bits.QEA1R = 12; //QEI1A -> RP12/M1_CHA
    RPINR14bits.QEB1R = 23; //QEI1B -> RP13/M1_CHB
    
    // QEI2 -> Right Motor (M2)
    RPINR16bits.QEA2R = 9; //QEI2A -> RP9/M2_CHA
    RPINR16bits.QEB2R = 22; //QEI2B -> RP22/M2_CHB

    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    // TODO:
    
    TRISBbits.TRISB2 = 0;// UART1 TX (newer)
    //TRISBbits.TRISB8 = 0;// UART1 TX

    //PIN MAPPING --------------------------------
    //before we map, we need to unlock
    __builtin_write_OSCCONL(OSCCON & 0xbf); // clear bit 6 (unlock, they are usually write protected)
    
    // PERIPHERAL receives data from which INPUT  
    RPINR18bits.U1RXR = 10;//9; //mapped to RP9 is U1 RX
    
    //OUTPUT PIN receives data from which PERIPHERAL, 
    //see table 11-2 in datasheet to check peripheral codes 
    RPOR1bits.RP2R = 0b00011; //output bin RP2 gets data from peripheral U1 TX 

    //after mapping we lock again
     __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS registers (lock again!)
     
    int i;
    for (i = 0; i < 30000; i++); // short dirty delay for changes to take effect
}
