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
    
        // QEI1 -> Left Motor (M1)
        RPINR14bits.QEA1R = 12; //QEI1A -> RP12/M1_CHA
        RPINR14bits.QEB1R = 23; //QEI1B -> RP13/M1_CHB

        // QEI2 -> Right Motor (M2)
        RPINR16bits.QEA2R = 9; //QEI2A -> RP9/M2_CHA
        RPINR16bits.QEB2R = 22; //QEI2B -> RP22/M2_CHB

        // UART
        RPINR18bits.U1RXR = 20; //U1RX -> RP20/UART_RX
        RPINR18bits.U1CTSR = 21; //U1CTS -> RP21/BT_CTS
        RPOR3bits.RP7R = 0b00011; //U1TX -> RP7/UART_TX
        RPOR4bits.RP8R = 0b00100; //U1RTS -> RP8/BT_RTS
        
#ifdef SOFTWARE_FIX
        //Output compare
        RPOR11bits.RP23R = 0b10010; //OC1 -> RP23/M1_IN1
        RPOR12bits.RP24R = 0b10011; //OC2 -> RP24/M1_IN2
#endif

    __builtin_write_OSCCONL(OSCCON | 0x40);
     
    int i;
    for (i = 0; i < 30000; i++); // short dirty delay for changes to take effect
}
