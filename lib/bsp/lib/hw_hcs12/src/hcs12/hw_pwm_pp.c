/*
    This module implements PWM outputs on the HCS12 PWM module.
*/    


#include "hw_pwm_pp.h"	  
#include "hw_mcu.h"    // MCU register definitions
#include "hw_config.h"

 
			  
const hw_pwm_pp::cfg_t hw_pwm_pp::DEFAULT_CFG =
{
    0xAA,   // PWME: PWM Enable Register
            //  PWME[7:0]   ;0-> channel is disabled
            //              ;1-> channel is enabled
                        
    0xFF,   // PWMPOL: PWM Polarity Register
            //  PWMPOL[7:0] ;0-> output is low  for the "ratio_cnt" part of the period.
            //              ;1-> output is high for the "ratio_cnt" part of the period.   
            
    0x00,   // PWMCLK: PWM Clock Select register  
            //         <<PCLK7:PCLK6:PCLK5:PCLK4:PCLK3:PCLK2:PCLK1:PCLK0>>
            //  PCLK7   ;0->Clock B  is the source for PWM7
            //          ;1->Clock SB is the source for PWM7
            //  PCLK6   ;0->Clock B  is the source for PWM6
            //          ;1->Clock SB is the source for PWM6
            //  PCLK5   ;0->Clock A  is the source for PWM5
            //          ;1->Clock SA is the source for PWM5
            //  PCLK4   ;0->Clock A  is the source for PWM4
            //          ;1->Clock SA is the source for PWM4
            //  PCLK3   ;0->Clock B  is the source for PWM3
            //          ;1->Clock SB is the source for PWM3
            //  PCLK2   ;0->Clock B  is the source for PWM2
            //          ;1->Clock SB is the source for PWM2 
            //  PCLK1   ;0->Clock A  is the source for PWM1
            //          ;1->Clock SA is the source for PWM1
            //  PCLK0   ;0->Clock A  is the source for PWM0
            //          ;1->Clock SA is the source for PWM0
            
    0x00,   // PWMPRCLK: PWM Prescale Clock Select Register 
            //           << 0:PCKB(3-bits):0:PCKA(3-bits) >>
            //           ; Clock A = CPU_FREQ / (2^PCKB)
            //           ; Clock B = CPU_FREQ / (2^PCKA)
             
       1,   // PWMSCLA: PWM Scale A Register
            //           ; Clock SA = Clock A / (2*PWMSCLA)
      
       1,   // PWMSCLB: PWM Scale B Register
            //           ; Clock SB = Clock B / (2*PWMSCLB)
      
    // PP0  PP1	 PP2  PP3  PP4  PP5	 PP6  PP7
    {    0,   0,   0,   0,   0,   0,   0,   0 },  // initial duty cycles
    {  100, 400, 100, 400, 100, 400, 100, 400 }   // frequencies    
};

const hw_pwm_pp::cfg_t *hw_pwm_pp::cfg=(const hw_pwm_pp::cfg_t * )0; 


// hw_io local functions 
void hw_pwm_pp::initialize_module(void)
{
    if (!cfg)
        cfg = &DEFAULT_CFG;
    
    PWMDTY01 = 0;
    PWMDTY23 = 0;
    PWMDTY45 = 0;
    PWMDTY67 = 0;

    PWMPER01 = 1;
    PWMPER23 = 1;
    PWMPER45 = 1;
    PWMPER67 = 1;

    PWMCTL   = 0xF0;    

    PWMPOL   = cfg->initial_PWMPOL;
    PWMCLK   = cfg->initial_PWMCLK;
    PWMPRCLK = cfg->initial_PWMPRCLK;
    PWMSCLA  = cfg->initial_PWMSCLA;
    PWMSCLB  = cfg->initial_PWMSCLB;       
    PWME     = cfg->initial_PWME;   
}


void hw_pwm_pp::initialize(ch_t channel_) 
{
    channel = channel_;
    
    uint8_t  a = (channel & 0x02) == 0;
     
    uint8_t prclk = a ?
                          PWMPRCLK       & 0x07:
                         (PWMPRCLK >> 4) & 0x07;
                        
    if ( PWMCLK & (1 << (channel&0x07) )  )
    {
        prescaler = (1 << prclk) * 2 * (a?PWMSCLA:PWMSCLB); 
    }
    else
    {
        prescaler = 1 << prclk;
    } 
    
    hires = 0;  
    if ( (channel & 0x1) == 1 )	  // this is an odd channel... 
    {
        uint8_t mask = 1 << (channel & 0x06);
        if ( (PWME & mask) == 0)              // corresponding even channel is inactive
        {
            //PWMCTL |= 0x10 << (channel>>1);   // set the corresponding "concatenate" bit.
            hires = 1;  
        }
    }
    
    SetFrequency(cfg->initial_frequency[channel]); 
}


void hw_pwm_pp::SetFrequency(uint16_t f)
{
    uint32_t clk_freq    = CPU_FREQ / prescaler;
    uint8_t active = PWME & (1<<channel);
     
    if ( f > clk_freq || !active )
    {
       resolution = 1; 
    }        
    else 
    {
        uint32_t long_res = clk_freq / f;
        
        if (hires)
            resolution = (uint16_t) (long_res > 0xFFFF ? 0xFFFF : long_res );
        else
            resolution = (uint8_t ) (long_res > 0xFF   ?   0xFF : long_res );                 
    }   
    
    // set the PWMPER register...
    if (active)
        if (hires)
        {
            uint16_t * p =(uint16_t *) (&PWMPER0 + channel - 1);	         
            *p = (uint16_t) resolution;
        }
        else  
        {
            uint8_t * p = (&PWMPER0 + channel);          
            *p = (uint8_t) resolution;
        }
    
    
    SetRatio16(ratio);
         
}


uint16_t hw_pwm_pp::GetFrequency(void)
{
    uint32_t clk_freq    = CPU_FREQ / prescaler;
    uint8_t active = PWME & (1<<channel);
    
    uint16_t f;
     
    if ( !active )
    {
       f = 0; 
    }        
    else 
    {
        f =(uint16_t) (clk_freq / resolution);                
    }   
    
   return f;         
}


void hw_pwm_pp::SetRatio16(uint16_t ratio16_)
{
    ratio = ratio16_;
    
    // set the PWMDTY register...
    /*uint16_t */ratio_cnt = (uint16_t)( (uint32_t)(((uint32_t) ratio16_ * resolution) + 65535/2)/65535 );
    
    uint8_t cmask = 1<<channel;
   
    if (PWME & cmask)
        if (hires)
        {
            uint16_t * p = (uint16_t *) (&PWMDTY0 + channel - 1);	         
            *p = ratio_cnt;
        }
        else
        {
            uint8_t * p = &PWMDTY0 + channel;          
            *p = (uint8_t) ratio_cnt;
        }
    else
        if (ratio_cnt!=0 && (PWMPOL&cmask))
            PTP |=  cmask;     // set   the port bit
        else
            PTP &= ~cmask;	   // clear the port bit
}



uint16_t hw_pwm_pp::GetRatio16(void)
{
    return ratio;
}