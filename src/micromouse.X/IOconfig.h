// guard condition
#ifndef IOCONFIG_H
#define	IOCONFIG_H

#define LED4 LATBbits.LATB15
#define LED5 LATBbits.LATB14
#define LED6 LATBbits.LATB13
#define LED7 LATBbits.LATB12

#define LEDON 0
#define LEDOFF 1

#define True 1
#define False 0 

// configures the IO management
void initIO();

#endif	/* IOCONFIG_H */

