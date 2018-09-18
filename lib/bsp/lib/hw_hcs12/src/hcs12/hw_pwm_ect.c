
/*
    This module implements PWM outputs on the HCS12 ECT module.
*/    


#include "hw_pwm_ect.h"	 
#include "hw_mcu.h"    // MCU register definitions
#include "hw_config.h"
#include "hw_clock.h"

 
hw_pwm_ect pwm_ect[hw_pwm_ect::PWM_ECT_QTY];
 
void hw_pwm_ect::initialize_module(void)
{
    TIOS |= 0xFC;   // set IOS7:IOS6:IOS5:ISO4:IOS3:IOS2 == Output Compare function.
    OC7M |= 0xFC;   // Output Compare 7 Mask Register - channels 6,5,4,3 & 2 tied to OC7

    hw_pwm_ect::SetFrequency(500);         
    
    TIE |= 0x80;    // enable the OC7 interrupt    
    
             
}


// pwm state...
//  0 - enable   - OMx:OLx=10 (clear output line)    OC7Dx=1 
//  1 - Off      - OMx:OLx=10 (clear output line)    OC7Dx=0 
//  2 - On       - OMx:OLx=11 (set   output line)    OC7Dx=1 
#define PWM_ENABLE 0
#define PWM_OFF	   1
#define PWM_ON	   2

static void set_state(hw_pwm_ect::ch_t ch_, uint8_t state)
{
    switch (ch_)
    {
    
         case hw_pwm_ect::PT2:
            switch (state)
            {
                case PWM_ENABLE: TCTL2 &= ~0x10; OC7D |=  0x04; break;
                case PWM_OFF:    TCTL2 &= ~0x10; OC7D &= ~0x04; break;
                case PWM_ON:     TCTL2 |=  0x10; OC7D |=  0x04; break;                     
            }
            break;
        case hw_pwm_ect::PT3:
            switch (state)
            {
                case PWM_ENABLE: TCTL2 &= ~0x40; OC7D |=  0x08; break;
                case PWM_OFF:    TCTL2 &= ~0x40; OC7D &= ~0x08; break;
                case PWM_ON:     TCTL2 |=  0x40; OC7D |=  0x08; break;                     
            }
            break;
        case hw_pwm_ect::PT4:
            switch (state)
            {
                case PWM_ENABLE: TCTL1 &= ~0x01; OC7D |=  0x10; break;
                case PWM_OFF:    TCTL1 &= ~0x01; OC7D &= ~0x10; break;
                case PWM_ON:     TCTL1 |=  0x01; OC7D |=  0x10; break;                     
            }
            break;
        case hw_pwm_ect::PT5:
            switch (state)
            {
                case PWM_ENABLE: TCTL1 &= ~0x04; OC7D |=  0x20; break;
                case PWM_OFF:    TCTL1 &= ~0x04; OC7D &= ~0x20; break;
                case PWM_ON:     TCTL1 |=  0x04; OC7D |=  0x20; break;                     
            }
            break;
        case hw_pwm_ect::PT6:
            switch (state)
            {
                case PWM_ENABLE: TCTL1 &= ~0x10; OC7D |=  0x40; break;
                case PWM_OFF:    TCTL1 &= ~0x10; OC7D &= ~0x40; break;
                case PWM_ON:     TCTL1 |=  0x10; OC7D |=  0x40; break;                     
            }
            break;
    }
}


uint16_t hw_pwm_ect::resolution;

#define TCNT_FREQ (uint32_t) (CPU_FREQ / (1<<initial_TSCR2_PR))  
                                                          
void hw_pwm_ect::SetFrequency(uint16_t f)         // desired frequency (in Hz)
{   
    if (f > TCNT_FREQ)
        resolution = 1;		    
    else if ( f < (TCNT_FREQ/65535u) )
        resolution = 65535;
    else
        resolution =(uint16_t)( TCNT_FREQ/f);  
    
    pwm_ect[0].SetRatio16(pwm_ect[0].GetRatio16());
    pwm_ect[1].SetRatio16(pwm_ect[1].GetRatio16());
    pwm_ect[2].SetRatio16(pwm_ect[2].GetRatio16());
    pwm_ect[3].SetRatio16(pwm_ect[3].GetRatio16());
    pwm_ect[4].SetRatio16(pwm_ect[4].GetRatio16());
}
     
    
uint16_t hw_pwm_ect::GetFrequency(void)         // actual frequency (in Hz)
{
    return (uint16_t)( (TCNT_FREQ+resolution/2)/resolution);      
}             
             
             
#define MIN_PWM_RATIO  3276u  //  5%
#define MAX_PWM_RATIO 62258u  // 95%                
                                                                                             
void hw_pwm_ect::SetRatio16(uint16_t ratio16_)    // % on time for the output
                                                        //      0 - output is commanded off
                                                        // 0xFFFF - output is commanded on          
{
    ratio     = ratio16_;    
    
    if      (ratio16_ < MIN_PWM_RATIO)	 // if ratio <  5% turn off OC and set output = off, ratio_cnt==5%
        set_state(channel,PWM_OFF);
    else if (ratio16_ > MAX_PWM_RATIO)	 // if ratio > 95% turn off OC and set output = on, ratio_cnt=95%
        set_state(channel,PWM_ON);
    else
        set_state(channel,PWM_ENABLE);		     // else enable OC 
    
    ratio_cnt = (uint16_t)( (uint32_t)(((uint32_t) ratio16_ * resolution) + 65535u/2)/65535u );        
}                                                        



#pragma CODE_SEG __NEAR_SEG NON_BANKED

__interrupt void ECT7_isr(void)
{
    TC2  = TC7 + pwm_ect[0].ratio_cnt;  // ratio_cnt
    TC3  = TC7 + pwm_ect[1].ratio_cnt;  // ratio_cnt    
    TC4  = TC7 + pwm_ect[2].ratio_cnt;  // ratio_cnt
    TC5  = TC7 + pwm_ect[3].ratio_cnt;  // ratio_cnt
    TC6  = TC7 + pwm_ect[4].ratio_cnt;  // ratio_cnt     
    TC7 += hw_pwm_ect::resolution;   
    
    TFLG1 = 0xFC;       				// clear C7F (by writing a one to it).
}

#pragma CODE_SEG DEFAULT



