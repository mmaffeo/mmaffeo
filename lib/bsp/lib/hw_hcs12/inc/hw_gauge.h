

#ifndef hw_gauge_h
#define hw_gauge_h

#include "stdint.h"



typedef enum
{
    HWC_GAUGE_1,  HWC_GAUGE_2,
    HWC_GAUGE_QTY
} hw_gauge_ch_t;

#ifndef HCS12_BSP_EMU


#pragma CODE_SEG __NEAR_SEG NON_BANKED // Interrupt section for this module. Placement will be in NON_BANKED area.
__interrupt void hw_gauge_update_isr(void);
#pragma CODE_SEG DEFAULT

#endif /* HCS12_BSP_EMU */


#define HW_GAUGE_MIN_POSITION 0x0
#define HW_GAUGE_MAX_POSITION 0xFFFFu

void     hw_gauge_SetPosition(hw_gauge_ch_t ch,
                           uint16_t position);    // % poistion for the output


uint16_t hw_gauge_GetPosition(hw_gauge_ch_t ch);   // the last value commanded to this output


/////////////////////////////////////////////////////////////////////////////////////////////////////
// hw_io diver interface "user" should not need to access this information.
void hw_gauge_initialize(void);
void hw_gauge_update    (void);


#endif
