#include "xc.h"
#include "serialComms.h"
#include "IOconfig.h"
#include "pwm.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"


BOOL isCmdBuffering = FALSE;
//unsigned int commandDataBufferSize = 100;
unsigned int comandDataLength = 0;
char commandData[100]; // buffer for receiving commands

void initUART1(void) 
{
    U1MODEbits.UARTEN=0; // switch the uart off during set-up
    U1BRG=28; // baud rate register at addr 0228
    U1MODEbits.LPBACK = 0; // in loopback mode for test
    
    U1MODEbits.WAKE = 0; // do not wake up on serial port activity
    
    U1MODEbits.ABAUD = 0; // no auto baud rate detection
    U1MODEbits.PDSEL = 0; // select 8 bits date, no parity
    U1MODEbits.STSEL = 0; // one stop bit
    U1MODEbits.BRGH = 0; // No high speed mode
    
    U1STAbits.URXISEL = 0; // generate receive interrupt as soon as a character has arrived
    
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0; // reset receive (RX) and transmission (TX) interrupt flag
    
    IPC2bits.U1RXIP = 5; // set RX interrupt priority
    IPC3bits.U1TXIP = 3; // set TX interrupt priority
    
    IEC0bits.U1RXIE = 1; // enable RX interrupt
    IEC0bits.U1TXIE = 1; // enable TX interrupt
    
    U1MODEbits.UARTEN = 1; // switch the uart on
    
    U1STAbits.UTXEN = 1; // enable transmission
}

// sends a string char-by-char
void putsUART1(char *buffer)
{
    char * temp_ptr = (char *) buffer;
    
    if(U1MODEbits.PDSEL == 3) // check if TX is 8 bits or 9 bits
    {
        while(*buffer != '\0') {
            while(U1STAbits.UTXBF); // wait if buffer is full)
            U1TXREG = *buffer++; // transfer data word to TX reg
        }
    }
    else {
        while (*temp_ptr != '\0') {
            while(U1STAbits.UTXBF); // wait if buffer is full
            U1TXREG = *temp_ptr++;
        }
    }
}

// Reaction to Receives
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    IFS0bits.U1RXIF = 0; // reset interrupt flag
    unsigned char rxData;
    
    rxData = U1RXREG; // read data (and then U1RXREG should be empty)
    
    U1STAbits.OERR = 0; // clear the overflow bit if it has been set
    
    // "<" starts a command string
    if (rxData == '<') 
    {
        comandDataLength = 0;
        isCmdBuffering = TRUE;
    }
    // ">" ends a command string
    else if (rxData == '>' && isCmdBuffering == TRUE)
    {
        executeCommand(&commandData);
        isCmdBuffering = FALSE;
        comandDataLength = 0;
    }
    else if (isCmdBuffering == TRUE)
    {
        comandDataLength += sprintf(commandData + comandDataLength, "%c", (char)rxData);
    }
    else if (rxData >= '0' && rxData <= '9') // test to dim LED 5 (DELETE THIS)
    {
        float percent = (float)(rxData - 48) / 10;
        //setDC1percentage(percent);
    }
    else
    {
        U1TXREG = rxData; // sends out the data that was received
    }
}

// Reaction to own transmits
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
    IFS0bits.U1TXIF = 0; // reset interrupt flag    
    LED7 = ~LED7; // DELETE THIS
}

void executeCommand(char* cmdString)
{
    putsUART1(cmdString);
    // simple command test, CHANGE THIS
    if (!strcmp(cmdString, "LED"))
    {
        LED6 = ~LED6;
    }
}