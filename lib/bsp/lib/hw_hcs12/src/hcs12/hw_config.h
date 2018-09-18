/*
    This module provides CPU related setup (oscillator, memory map) and 
    information status for this microcontroller setup.  
    (shared between bootblock and application)
*/


#ifndef hw_config_h
#define hw_config_h

#include "stdint.h"

static const uint16_t AP_VECTOR_BASE=0x7F80;


// clock setup.....
#define OSCCLK_FREQ        4000000uL        // external oscilator frequecy (Hz) 
#define OSCCLK_FREQ_KHZ (OSCCLK_FREQ/1000u)
#define OSCCLK_FREQ_MHZ (OSCCLK_FREQ/1000000u)
#define SYNR_init_value  24		      // 6 bits (0->63)
#define REFDV_init_value  3		      // 4 bits (0->15)

#define PLL_frequency (uint32_t) (2uL*OSCCLK_FREQ*(SYNR_init_value+1) / (REFDV_init_value+1))

#define CPU_FREQ (uint32_t) (PLL_frequency/2)	  // frequecny of CPU operation (Hz)
#define CPU_FREQ_KHZ (CPU_FREQ/1000u)
#define CPU_FREQ_MHZ (CPU_FREQ/1000000u)

#endif   

