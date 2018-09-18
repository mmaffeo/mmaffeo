
/*
    This module provides CPU related setup (oscillator, memory map) and
    information status for this microcontroller setup.
*/


#ifndef hw_reset_h
#define hw_reset_h

#include "stdint.h"


typedef enum bb_smode_e
{
    BB_SMODE_NA=0,
    BB_SMODE_JUMP_TO_AP=1,
    BB_SMODE_CAPTURED=2
}bb_smode_t;


              // force a microcontroller reset operation.
void hw_reset_force(uint8_t bb_smode_,
                    uint8_t ap_smode_);



extern uint8_t ap_smode;
extern uint8_t bb_smode;

extern uint8_t bservProg_protocolID;
extern uint8_t bservProg_options;
extern uint8_t bservProg_customerID;
extern uint8_t bservProg_maxDataSize;

extern uint16_t hw_reset_max_stack(void);


#ifndef HCS12_BSP_EMU

extern uint16_t pvector_base;

#pragma CODE_SEG __NEAR_SEG NON_BANKED

__interrupt void hw_PowerOn_reset(void);
__interrupt void hw_COP_reset(void);


#pragma CODE_SEG DEFAULT

#endif /* HCS12_BSP_EMU */




void hw_reset_force(uint8_t bb_smode_,     // force a microcontroller reset operation.
                    uint8_t ap_smode_);

#define hw_reset_get_bb_smode() bb_smode
#define hw_reset_get_ap_smode() ap_smode

#endif

