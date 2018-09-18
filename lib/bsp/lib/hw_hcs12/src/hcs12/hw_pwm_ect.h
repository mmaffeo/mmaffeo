
#ifndef hw_pwm_ect_h
#define hw_pwm_ect_h

#include "stdint.h"


class hw_pwm_ect
{
public:
    enum ch_t
    {
        PT2, PT3, PT4, PT5, PT6,
        PWM_ECT_QTY
    };

    static void initialize_module(void);

    void SetRatio16(uint16_t ratio16_);    // % on time for the output
                                                 //      0 - output is commanded off
                                                 // 0xFFFF - output is commanded on

    static void     SetFrequency(uint16_t f);  // desired frequency (in Hz)
    static uint16_t GetFrequency(void);        // actual freuqency (in Hz)

    uint16_t GetRatio16(void)              // the last value commanded to this output
    {
        return  ratio;
    }

    static uint16_t resolution;

    void initialize(ch_t channel_) { channel = channel_; }

    enum ch_t channel;
    uint16_t  ratio;
    uint16_t  ratio_cnt;
};


extern hw_pwm_ect pwm_ect[hw_pwm_ect::PWM_ECT_QTY];

#ifndef HCS12_BSP_EMU

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void ECT7_isr(void);
#pragma CODE_SEG DEFAULT

#endif /* HCS12_BSP_EMU */


#endif
