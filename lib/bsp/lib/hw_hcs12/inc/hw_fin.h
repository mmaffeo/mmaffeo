
#ifndef hw_fin_h
#define hw_fin_h

#include "stdint.h"

typedef enum
{
    HWC_FIN0,

    HWC_FIN_QTY
} hw_fin_ch_t;

extern uint32_t PERIOD_COUNTS_PER_SECOND;
extern uint32_t PERIOD_COUNTS_MAXIMUM;
extern uint32_t hw_fin_GetPeriodCount(hw_fin_ch_t ch);

extern uint32_t hw_fin_GetPerioduS   (hw_fin_ch_t ch);


/////////////////////////////////////////////////////////////////////////////////////////////////////
// hw_io diver interface "user" should not need to access this information.
void hw_fin_initialize(void);
void hw_fin_update    (void);

#ifndef HCS12_BSP_EMU

#pragma CODE_SEG __NEAR_SEG NON_BANKED

__interrupt void hw_fin0_OnCapture(void);

#pragma CODE_SEG DEFAULT

#endif /* HCS12_BSP_EMU */

#endif
