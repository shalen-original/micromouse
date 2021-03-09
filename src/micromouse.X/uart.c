#include <xc.h>
#include "uart.h"
#include "boolean.h"
#include "errors.h"

#define UART_MAX_TX_MSG_SIZE 50
static uint8_t _uartTxBuffer[UART_MAX_TX_MSG_SIZE];
static uint8_t _uartTxCurrentPos = 0;
static uint8_t _uartTxMsgLength = 0;
static BOOL _uartTxInProgress = FALSE;

#define UART_MAX_RX_CMD_SIZE 50
static char _uartRxCmdBuffer[UART_MAX_RX_CMD_SIZE];
static uint8_t _uartRxCurrentPos = 0;
static BOOL _uartRxCmdReceptionInProgress = FALSE;

void initUART() {
    U1MODEbits.UARTEN = 0;
    
    U1BRG = 29; // Baudrate of 57327.59 bit/s
    
    U1MODEbits.PDSEL = 0; // 8-bit data, no parity
    U1MODEbits.STSEL = 0; // 1 stop bit
    //U1MODEbits.LPBACK = 1; // Enable loop back mode
    U1MODEbits.UEN = 0b0; // UART controls only TX/RX pins
    //U1MODEbits.UEN = 0b10; // UART controls TX/RX/CTS/RTS pins
    //TODO bluetooth change U1MODEbits.UEN
    
    U1STAbits.URXISEL = 0b00; // Trigger an interrupt for every received byte
    IEC0bits.U1RXIE = 0b1; // Actually enable UART RX interrupts
    
    // Trigger an interrupt whenever there is an empty spot in TX buffer
    U1STAbits.UTXISEL0 = 0;
    U1STAbits.UTXISEL1 = 0;
    
    // Transmission interrupts are automatically
    // enabled and disabled by uartSendAsync
    
    //NOTE: The order of these two is important!
    U1MODEbits.UARTEN = 0b1; // Enable UART
    U1STAbits.UTXEN = 0b1; // Enable transmission
    
    // Short delay is required for config to be effective,
    // already taken care by halapi.c::initHAL())
}

void _uart1SendSync(const char *msg) {
    // This function is sync and blocks execution until the
    // entire message is sent. Useful for debugging, but normally
    // it's better to use the async version.
    
    while(*msg != '\0') {
        while(U1STAbits.UTXBF); // Wait if TX buffer is full
        U1TXREG = *(msg++); // Transfer data word to TX reg
    }
}

void _uartSendAsMuchAsPossible() {
    
    // While there still is space in the UART1 TX hardware buffer
    while (0 == U1STAbits.UTXBF) {
        U1TXREG = _uartTxBuffer[_uartTxCurrentPos];
        _uartTxCurrentPos++;
        
        if (_uartTxCurrentPos >= _uartTxMsgLength) {
            // Transmission is over
            _uartTxInProgress = FALSE;
            _uartTxMsgLength = 0;
            _uartTxCurrentPos = 0;
            
            IEC0bits.U1TXIE = 0;
            
            return;
        }
    }
    
}

int uartSendAsync(const uint8_t *msg, uint8_t msgLength) {
    
    if (msgLength > UART_MAX_TX_MSG_SIZE) {
        return ERR_UART_TX_MSG_TOO_LONG;
    }
    
    if (TRUE == _uartTxInProgress) {
        return ERR_UART_CANNOT_SEND_MULTIPLE_MESSAGES;
    }
    
    int i;
    for (i = 0; i < msgLength; i++){
        _uartTxBuffer[i] = msg[i];
    }
    
    _uartTxCurrentPos = 0;
    _uartTxMsgLength = msgLength;
    _uartTxInProgress = TRUE;
    
    IEC0bits.U1TXIE = 1; // Enable interrupt
    
    _uartSendAsMuchAsPossible();
    
    return 0;
}

void __attribute__((__interrupt__, auto_psv)) _U1TXInterrupt(void)
{
    IFS0bits.U1TXIF = 0;
    _uartSendAsMuchAsPossible();
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    IFS0bits.U1RXIF = 0; // reset interrupt flag
    
    // Read received data (one interrupt is generated for each byte)
    unsigned char rxByte = U1RXREG;
    
    // Clears overflow if it happened.
    // Clearing OERR when an overflow has actually happened
    // resets the receive buffer
    U1STAbits.OERR = 0;
    
    if (rxByte == '<') {
        // "<" starts a command string
        _uartRxCurrentPos = 0;
        _uartRxCmdReceptionInProgress = TRUE;
    } else if (rxByte == '>' && _uartRxCmdReceptionInProgress == TRUE) {
        // ">" ends a command string
        
        // Before invoking the call back, we must ensure that
        // the content of _uartRxCmdBuffer is a properly
        // null-terminated string.
        if (_uartRxCmdBuffer[_uartRxCurrentPos - 1] != '\0') {
            // invariant: _uartRxCurrentPos < UART_MAX_RX_CMD_SIZE + 1
            _uartRxCmdBuffer[_uartRxCurrentPos] = '\0';
        }
        
        onCommandReceived(_uartRxCmdBuffer);
        
        _uartRxCurrentPos = 0;
        _uartRxCmdReceptionInProgress = FALSE;
    } else if (_uartRxCmdReceptionInProgress == TRUE && _uartRxCurrentPos >= UART_MAX_RX_CMD_SIZE) {
        // Current message is too big. No action is taken, as continuing to
        // write to _uartRxCmdBuffer would corrupt memory
    } else if (_uartRxCmdReceptionInProgress == TRUE) {
        _uartRxCmdBuffer[_uartRxCurrentPos] = rxByte;
        _uartRxCurrentPos++;
    } else {
        U1TXREG = rxByte; // sends out the data that was received
    }
}