
#ifndef hw_pwm_pp_h
#define hw_pwm_pp_h

#include "stdint.h"
#include "stdbool.h"

class hw_pwm_pp
{
public:
    enum ch_t
    {
        PP0, PP1, PP2, PP3,
        PP4, PP5, PP6, PP7,
        PWM_QTY        
    } ;
       
    void initialize(ch_t channel_);
    
    void SetRatio16(uint16_t ratio16_);    // % on time for the output
                                                        //      0 - output is commanded off
                                                        // 0xFFFF - output is commanded on
                                                        
    void     SetFrequency(uint16_t f);  // desired frequency (in Hz)
    uint16_t GetFrequency(void);        // actual  frequency (in Hz)
                                                                                             
    uint16_t GetRatio16(void);          // the last value commanded to this output 
    
    struct cfg_t 
    {
        uint8_t  initial_PWME;     // initial value for the PWM Enable Register
        uint8_t  initial_PWMPOL;   // initial value for the PWM Polarity Register
        uint8_t  initial_PWMCLK;   // initial value for the PWM Clock Select Register
        uint8_t  initial_PWMPRCLK; // initial value for the PWM Prescale Clock Select Register
        uint8_t  initial_PWMSCLA;  // initial value for the PWM Scale A Register
        uint8_t  initial_PWMSCLB;  // initial value for the PWM Scale B Register
    
        uint16_t initial_ratio[8];
        uint16_t initial_frequency[8];
  
    } ;                                                           
    static const cfg_t DEFAULT_CFG;
    static void  set_cfg          (const cfg_t * cfg_) { cfg = cfg_; }
    static void  initialize_module(void);

private:					 
    ch_t channel;
    
    static const cfg_t *cfg ;
    	     
    uint16_t ratio;      
    
    uint16_t ratio_cnt;
    uint16_t resolution;
    
    bool     hires;      
    uint16_t prescaler;
};

#endif