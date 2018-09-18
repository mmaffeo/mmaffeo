
#ifndef hw_io_h
#define hw_io_h

typedef unsigned FLAG;

#include "hw_timer.h"
#include "hw_adc.h"
#include "hw_dio.h"
#include "hw_fin.h"
#include "hw_pwm.h"
#include "hw_gauge.h"
#include "hw_can.h"
//#include "hw_serial.h"
#include "hw_reset.h"
#include "hw_nvm.h"
#include "hw_clock.h"

#define HW_CTA(x)   extern uint8_t hw_cta_a[(x) ? 1 : -1]

#ifdef HCS12_BSP_EMU
#include "ap_bsp.h"
#define HW_DEBUG(a) BSP_DEBUG(a)
#else
#define HW_DEBUG(a)
#endif

void hw_io_initialize(void);
void hw_io_update    (void);

uint8_t hw_readByteDirect(uint32_t address);
uint16_t hw_readWordDirect(uint32_t address);
uint32_t hw_readDwordDirect(uint32_t address);

extern uint16_t max_stack_size;
#endif




