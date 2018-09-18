// This module provides code to measure the period present on frequency inputs.

#include "hw_fin.h"
#include "hw_mcu.h"    // MCU register definitions
#include "hw_clock.h"
#include "hw_config.h"
#include "hw_mscan.h"

typedef enum
{
    fins_WAITING_FOR_FIRST_EDGE,
    fins_WAITING_FOR_SECOND_EDGE,
    fins_PERIOD_SAMPLED
}fin_state_t;


#define SECONDS_TO_CNTS(sec)  (uint32_t)((float)(sec)*(CPU_FREQ/(1<<initial_TSCR2_PR)))

uint32_t PERIOD_COUNTS_MAXIMUM = SECONDS_TO_CNTS(2.000);
uint32_t PERIOD_CNT_MIN = SECONDS_TO_CNTS(0.004);

uint32_t PERIOD_COUNTS_PER_SECOND=SECONDS_TO_CNTS(1.000);


typedef struct
{
    uint32_t period_cnt;
    uint32_t start_cnt;
    uint32_t stop_cnt;
    fin_state_t  state;
    uint32_t period;
}hw_hw_fin_data_t;

//static hw_hw_fin_data_t hw_fin_data[HWC_FIN_QTY]; removed array
static hw_hw_fin_data_t hw_fin_data;


uint32_t hw_fin_GetPeriodCount(hw_fin_ch_t ch)
{
    uint32_t retval;

    // Retrieve the period atomically
    EnterCritical();
    retval = hw_fin_data.period;
    ExitCritical();

    return retval;
}

uint32_t hw_fin_GetPerioduS(hw_fin_ch_t ch)
{
    return hw_clock_convert_clockticks_to_uS(hw_fin_data.period);
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED /* Interrupt section for this module. Placement will be in NON_BANKED area. */
static void hw_fin_Enable(hw_fin_ch_t ch)
{
    switch(ch)
    {
        case HWC_FIN0: TFLG1 = 0x01; TIE_C0I = 1; TCTL4 |= 0x01; break;
    }
}

static void hw_fin_Disable(hw_fin_ch_t ch)
{
    switch(ch)
    {
        case HWC_FIN0: TIE_C0I = 0; TCTL4 &= ~0x03; break;
    }
}

/*static uint16_t hw_fin_GetCaptureValue(hw_fin_ch_t ch)
{
    uint16_t rvalue;
    switch(ch)
    {
        default:
        case HWC_FIN0: rvalue = TC0; break;
    }
    return rvalue;
}         */

static void hw_fin_OnCapture(hw_fin_ch_t ch)
{
    uint16_t value, tof;
    uint32_t long_cap;

    if (ignore_FIN_input)
    {
        hw_fin_Disable(ch);
        hw_fin_data.state = fins_PERIOD_SAMPLED;
        ignore_FIN_input = FALSE;
        return;
    }

    value = TC0; //hw_fin_GetCaptureValue(ch);

    if (TFLG2_TOF && (value < 0x7FFF))
    {
        tof = TCNT_overflows +1;
    }
    else
        tof = TCNT_overflows;

    long_cap = tof * 0x00010000L + value;

    switch (hw_fin_data.state)
    {
        case fins_WAITING_FOR_FIRST_EDGE:
            hw_fin_data.start_cnt = long_cap;
            hw_fin_data.state = fins_WAITING_FOR_SECOND_EDGE;
            break;
        case fins_WAITING_FOR_SECOND_EDGE:
            hw_fin_data.stop_cnt = long_cap;
            hw_fin_data.period_cnt = hw_fin_data.stop_cnt - hw_fin_data.start_cnt;

            if (hw_fin_data.period_cnt < PERIOD_CNT_MIN )
            {
                hw_fin_Disable(ch);
                hw_fin_data.state = fins_PERIOD_SAMPLED;
            }
            else
            {
                hw_fin_data.start_cnt = hw_fin_data.stop_cnt;
            }
            break;
    }
}

__interrupt void hw_fin0_OnCapture(void) { hw_fin_OnCapture(HWC_FIN0); TFLG1 = 0x01;}

#pragma CODE_SEG DEFAULT

////////////////////////////////////////////////////////////////////////////////////////////////////

void hw_fin_initialize(void)
{
    for (uint8_t i=0;i<(uint8_t)HWC_FIN_QTY; ++i)
    {
        hw_fin_data.state      = fins_PERIOD_SAMPLED;
        hw_fin_data.period_cnt = PERIOD_COUNTS_MAXIMUM;
        hw_fin_Disable((hw_fin_ch_t) i);
    }
}


void hw_fin_update(void)
{
    for (uint8_t i=0; i<(uint8_t)HWC_FIN_QTY; ++i)
    {
        EnterCritical();

        uint32_t current_time = hw_clock();

        switch (hw_fin_data.state)
        {
            case fins_PERIOD_SAMPLED:
                hw_fin_data.state = fins_WAITING_FOR_FIRST_EDGE;
                hw_fin_data.start_cnt = current_time;
                hw_fin_Enable((hw_fin_ch_t) i );
                break;
            case fins_WAITING_FOR_SECOND_EDGE:
            case fins_WAITING_FOR_FIRST_EDGE:
                uint32_t period_est = current_time - hw_fin_data.start_cnt;
                if ( hw_fin_data.period_cnt                < PERIOD_COUNTS_MAXIMUM )
                {
                    if ( period_est > PERIOD_COUNTS_MAXIMUM     )
                    {
                        hw_fin_data.period_cnt = PERIOD_COUNTS_MAXIMUM;
                        hw_fin_data.state      = fins_WAITING_FOR_FIRST_EDGE;
                    }
                    else if ( period_est > (hw_fin_data.period_cnt * 2 ) )
                    {
                        hw_fin_data.period_cnt = period_est;
                    }
                }
        break;
        }
        hw_fin_data.period    =  hw_fin_data.period_cnt;

        ExitCritical();
    }
}


