
/*
    This module provides an interface to the variable dutycyle pwm outputs.
*/

#ifndef hw_pwm_h
#define hw_pwm_h

#include "stdint.h"


typedef enum
{
    // PP1, PP3, PP5, PP7
    HWC_PWM_HC_HSD2, HWC_PWM_HC_HSD4, HWC_PWM_HC_HSD6, HWC_PWM_HC_HSD8,

    // PT2, PT3, PT4, PT5, PT6
    HWC_PWM_LC_LSD1,
    HWC_PWM_HC_HSD1,
    HWC_PWM_HC_HSD3,
    HWC_PWM_HC_HSD5,
    HWC_PWM_HC_HSD7,

    HWC_PWM_QTY
} hw_pwm_ch_t;


#define HW_PWM_MIN_RATIO 0x0
#define HW_PWM_MAX_RATIO 0xFFFFu
void     hw_pwm_SetRatio16(hw_pwm_ch_t ch,    //
                           uint16_t ratio);   // % on time for the output
                                              //      0 - output is commanded off
                                              // 0xFFFF - output is commanded on

uint16_t hw_pwm_GetRatio16(hw_pwm_ch_t ch);   // the last value commanded to this output


void     hw_pwm_SetFrequency(hw_pwm_ch_t ch, uint16_t frequency);
uint16_t hw_pwm_GetFrequency(hw_pwm_ch_t ch);

/////////////////////////////////////////////////////////////////////////////////////////////////////
// hw_io diver interface "user" should not need to access this information.
void hw_pwm_initialize(void);
void hw_pwm_update    (void);

#endif