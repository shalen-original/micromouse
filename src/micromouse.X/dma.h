#ifndef DMA_H
#define	DMA_H

#include <xc.h>

#define RAW_SENSOR_RIGHT adcData[2]  // S1_OUT/AN3
#define RAW_SENSOR_FRONT adcData[1]  // S2_OUT/AN2
#define RAW_SENSOR_LEFT  adcData[0]  // S3_OUT/AN1

extern unsigned int adcData[32]__attribute__((space(dma)));

void initDMAChannel4(void);

#endif

