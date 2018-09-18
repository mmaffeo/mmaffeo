
#include "af_main.h"  
#include "hw_mcu.h"
#include "hw_pwm_pp.h"


extern unsigned char ap_smode @0x3FFF;

const hw_pwm_pp::cfg_t PWM_PP_CFG =
{
    0xAA,   // PWME: PWM Enable Register                        
    0xFF,   // PWMPOL: PWM Polarity Register              
    0x00,   // PWMCLK: PWM Clock Select register  
    0x22,   // PWMPRCLK: PWM Prescale Clock Select Register 
       1,   // PWMSCLA: PWM Scale A Register
       1,   // PWMSCLB: PWM Scale B Register 
      
    // PP0  PP1	 PP2  PP3  PP4  PP5	 PP6  PP7
    {    0,   0,   0,   0,   0,   0,   0,   0 },  // initial duty cycles
    {  100, 100, 100, 100, 100, 100, 100, 100 }   // frequencies    
};


void main(void)
{
    hw_initialize();
    
    hw_pwm_pp::set_cfg(&PWM_PP_CFG);     
    
    af_main(ap_smode);  // endless loop... should never return...

    for(;;);    
}