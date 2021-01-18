// guard condition
#ifndef DMA_H
#define	DMA_H

#include <xc.h>

// CHANGE THIS
#define IO_1 adcData[0] //AN0
#define TEST_SENSOR adcData[1]  //AN5

extern unsigned int adcData[32]__attribute__((space(dma)));

// configures the DMA channel 4
void initDmaChannel4(void);

#endif	/* DMA_H */

