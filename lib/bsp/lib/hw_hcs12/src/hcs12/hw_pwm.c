
/*
    This module provides PWM outputs for the control.
*/


#include "hw_pwm.h"
#include "hw_pwm_pp.h"
#include "hw_pwm_ect.h"

hw_pwm_pp pwm_pp[4];


uint16_t hw_pwm_GetRatio16(hw_pwm_ch_t ch)
{
    uint16_t rvalue=0;

    switch (ch)
    {
        case HWC_PWM_HC_HSD2: rvalue = pwm_pp [0].GetRatio16(); break;
        case HWC_PWM_HC_HSD4: rvalue = pwm_pp [1].GetRatio16(); break;
        case HWC_PWM_HC_HSD6: rvalue = pwm_pp [2].GetRatio16(); break;
        case HWC_PWM_HC_HSD8: rvalue = pwm_pp [3].GetRatio16(); break;
        case HWC_PWM_LC_LSD1: rvalue = pwm_ect[0].GetRatio16(); break;
        case HWC_PWM_HC_HSD1: rvalue = pwm_ect[1].GetRatio16(); break;
        case HWC_PWM_HC_HSD3: rvalue = pwm_ect[2].GetRatio16(); break;
        case HWC_PWM_HC_HSD5: rvalue = pwm_ect[3].GetRatio16(); break;
        case HWC_PWM_HC_HSD7: rvalue = pwm_ect[4].GetRatio16(); break;
    }

    return rvalue;
}

void hw_pwm_SetRatio16(hw_pwm_ch_t ch, uint16_t ratio)
{
    switch (ch)
    {
        case HWC_PWM_HC_HSD2: pwm_pp [0].SetRatio16(ratio);       break;
        case HWC_PWM_HC_HSD4: pwm_pp [1].SetRatio16(ratio);       break;
        case HWC_PWM_HC_HSD6: pwm_pp [2].SetRatio16(ratio);       break;
        case HWC_PWM_HC_HSD8: pwm_pp [3].SetRatio16(ratio);       break;
        case HWC_PWM_LC_LSD1: pwm_ect[0].SetRatio16(ratio);       break;
        case HWC_PWM_HC_HSD1: pwm_ect[1].SetRatio16(ratio);       break;
        case HWC_PWM_HC_HSD3: pwm_ect[2].SetRatio16(ratio);       break;
        case HWC_PWM_HC_HSD5: pwm_ect[3].SetRatio16(ratio);       break;
        case HWC_PWM_HC_HSD7: pwm_ect[4].SetRatio16(ratio);       break;
    }
}


void hw_pwm_SetFrequency(hw_pwm_ch_t ch, uint16_t frequency)
{
    switch (ch)
    {
        case HWC_PWM_HC_HSD2: pwm_pp [0].SetFrequency(frequency); break;
        case HWC_PWM_HC_HSD4: pwm_pp [1].SetFrequency(frequency); break;
        case HWC_PWM_HC_HSD6: pwm_pp [2].SetFrequency(frequency); break;
        case HWC_PWM_HC_HSD8: pwm_pp [3].SetFrequency(frequency); break;
        case HWC_PWM_LC_LSD1:
        case HWC_PWM_HC_HSD1:
        case HWC_PWM_HC_HSD3:
        case HWC_PWM_HC_HSD5:
        case HWC_PWM_HC_HSD7: hw_pwm_ect::SetFrequency(frequency); break;
    }
}

uint16_t hw_pwm_GetFrequency(hw_pwm_ch_t ch)
{
    uint16_t rvalue = 0;

    switch (ch)
    {
        case HWC_PWM_HC_HSD2: rvalue = pwm_pp[0].GetFrequency(); break;
        case HWC_PWM_HC_HSD4: rvalue = pwm_pp[1].GetFrequency(); break;
        case HWC_PWM_HC_HSD6: rvalue = pwm_pp[2].GetFrequency(); break;
        case HWC_PWM_HC_HSD8: rvalue = pwm_pp[3].GetFrequency(); break;
        case HWC_PWM_LC_LSD1:
        case HWC_PWM_HC_HSD1:
        case HWC_PWM_HC_HSD3:
        case HWC_PWM_HC_HSD5:
        case HWC_PWM_HC_HSD7: rvalue = hw_pwm_ect::GetFrequency(); break;
    }

    return rvalue;
}


// hw_io local functions
void hw_pwm_initialize(void)
{
    hw_pwm_pp::initialize_module();
    pwm_pp[0].initialize( hw_pwm_pp::PP1 );
    pwm_pp[1].initialize( hw_pwm_pp::PP3 );
    pwm_pp[2].initialize( hw_pwm_pp::PP5 );
    pwm_pp[3].initialize( hw_pwm_pp::PP7 );

    hw_pwm_ect::initialize_module();
    pwm_ect[0].initialize(hw_pwm_ect::PT2 );
    pwm_ect[1].initialize(hw_pwm_ect::PT3 );
    pwm_ect[2].initialize(hw_pwm_ect::PT4  );
    pwm_ect[3].initialize(hw_pwm_ect::PT5  );
    pwm_ect[4].initialize(hw_pwm_ect::PT6  );
}


void hw_pwm_update    (void)
{
}

