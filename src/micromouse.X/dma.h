// guard condition
#ifndef DMA_H
#define	DMA_H

#include <xc.h>

// CHANGE THIS (3 sensors, front and sides)
#define SENSOR_FRONT adcData[0] //AN0
#define SENSOR_LEFT adcData[1]  //AN5
#define SENSOR_RIGHT adcData[2]  //TBD

extern unsigned int adcData[32]__attribute__((space(dma)));

// configures the DMA channel 4
void initDmaChannel4(void);

#endif	/* DMA_H */

