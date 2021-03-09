#ifndef UART_H
#define	UART_H

void initUART();
int uartSendAsync(const uint8_t *msg, uint8_t msgLength);

// To be implemented by users. The ownership of the data pointed to by
// receivedCommand remains to uart.h. The lifetime of receivedCommand 
// is the duration of the invokation of `onCommandReceived`.
void onCommandReceived(char* receivedCommand);

#endif