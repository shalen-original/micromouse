#include "adc.h"
#include <xc.h>

void initADC1()
{    
    // Configures ADC1 to work in 12-bit, channel scan mode relying on DMA
    // for data transfer.
    
    AD1CON1bits.ADON = 0; // Disable ADC1   
    
    AD1CON1bits.ADDMABM=1; // DMA buffers are written in order of conversion
    AD1CON1bits.AD12B=1; // 12-bit operation
    AD1CON1bits.FORM=0b00; // Output is stored as unsigned integer
    AD1CON1bits.SSRC=0b111; // Automatically end sampling and start conversion (auto-convert)
    AD1CON1bits.ASAM=0; // Sampling starts when SAMP bit is set
    AD1CON1bits.SAMP=0; // Do not sample right now (stay in 'holding' state)

    AD1CON2bits.VCFG=0b000; // Select Vref+ and Vref- as reference voltage
    AD1CON2bits.CSCNA=1; // Enable SCAN  on ANx inputs
    AD1CON2bits.ALTS=0; // Disable alternate ANx input selection (MUXA/MUXB)
    AD1CON2bits.BUFM=0; // Always fill output buffer starting at address 0x00

    // tAD = tCY * (AD1CON3bits.ADCS<7:0> + 1)
    AD1CON3bits.ADRC=0; // Use internal ADC clock source
    AD1CON3bits.SAMC=0x05; // [ONLY SSRC=0b111] Number of tAD for which to auto-sample
    AD1CON3bits.ADCS=0x06 ; // Allows to modify tAD

    AD1CON4bits.DMABL=0b000; // Allocates 1 word of DMA buffer for each ANx input

    /* CHANGE HERE */ 
    AD1CON2bits.SMPI=2; // [channel-scanning, ALTS disabled], should be the number of inputs being scanned minus one
    AD1CSSL= 0b0000000000001110; // Select which ANx pins should be scanned by ADC1
    /* END CHANGE HERE */
    
    IFS0bits.AD1IF = 0; // Clear ADC1 Interrupt Flag
    IEC0bits.AD1IE = 0; // Disable ADC1 interrupts (they are processed automatically by DMA unit)
    IPC3bits.AD1IP = 5; // Set priority of ADC1 interrupts
}

void startADC1(void)
{
    AD1CON1bits.ADON = 1; // Enable ADC1
    AD1CON1bits.ASAM = 1; // Start automatic sampling
}