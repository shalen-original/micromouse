// guard condition
#ifndef SERIAL_COMMS_H
#define	SERIAL_COMMS_H

#include <xc.h> // include processor files - each processor file is guarded.  

// setups the Universal asynchronous receiver-transmitter (UART) 1 channel
void initUART1(void);
// sends a string char-by-char
void putsUART1(char* buffer);
// translate and execute command via string
void executeCommand(char* cmdString);

#endif	/* SERIAL_COMMS_H */