#include "dma.h"

unsigned int adcData[32]__attribute__((space(dma)));

void initDMAChannel4(void)
{
	DMA4CONbits.CHEN = 0; // Disable channel
	DMA4CONbits.SIZE = 0; // Transfer words (1 word = 2 bytes)
	DMA4CONbits.DIR = 0; // Read from peripheral, store to RAM
	DMA4CONbits.HALF = 0; // Interrupt on full block transfer (not half)
	DMA4CONbits.NULLW = 1; // Enable null data write to peripheral
	DMA4CONbits.AMODE = 0b10; // Channel operating mode	is Peripheral Indirect Addressing
	DMA4CONbits.MODE = 0; // Continuous transfer, ping-pong disabled

    // When this interrupt is generated, a DMA transfer will be triggered.
	DMA4REQbits.IRQSEL = 0b0001101; // Select 'ADC1 Converter Done' IRQ number (Table 8-1)

	DMA4STA = __builtin_dmaoffset(adcData); // start address of DMA RAM
	DMA4PAD = (volatile unsigned int) &ADC1BUF0; // Address from which DMA will read
    
    // The DMA channel will perform N+1 transfers before considering
    // the block transfer complete (and restarting, since we're in
    // continuous mode). We need to set DMAxCNT = N.
	DMA4CNT = 2; /* CHANGE HERE */

	IFS2bits.DMA4IF = 0; // Clear DMA ch 4 interrupt flag
	IEC2bits.DMA4IE = 0; // Disable DMA ch 4 interrupt
	IPC11bits.DMA4IP = 5; // Set priority of DMA ch 4 interrupt

	DMA4CONbits.CHEN = 1; // Enable DMA ch 4

}

void __attribute__((interrupt, auto_psv)) _DMA4Interrupt(void)
{
    // This interrupt is invoked after a 'full block transfer',
    // meaning that all three sensor values have been sampled and updated
    
	IFS2bits.DMA4IF = 0; // Clear DMA interrupt
};
