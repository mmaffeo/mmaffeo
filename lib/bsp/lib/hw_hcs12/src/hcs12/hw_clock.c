#include "hw_clock.h"
#include "hw_config.h"
#include <limits.h>		
#include "hw_mcu.h"    // MCU register definitions
#include "hw_fps.h"
						

void hw_clock_initialize(void)
{				       
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // initialize TCNT timer. . .
    TSCR1    = 0xE0;  // << TEN=1:TSWAI=1:TSFRZ=1:TFFCA=0:0:0:0:0 >>
    TSCR2    = 0x80 | initial_TSCR2_PR;  // << TOI=1:0:0:0:TCRE=0:PR(3-bits)=passed in config >>
}

volatile uint16_t TCNT_overflows=0;
volatile uint16_t big_TCNT_overflows=0 ;

#pragma CODE_SEG __NEAR_SEG NON_BANKED // Interrupt section for this module. Placement will be in NON_BANKED area.
__interrupt void hw_clock_TCNT_overflow(void)
{
    TFLG2_TOF = 1; 
    TCNT_overflows++; 
    
    if (TCNT_overflows == 0)
        big_TCNT_overflows++; 
}  
#pragma CODE_SEG DEFAULT  
    
uint32_t hw_clock (void)
{
    uint16_t msw, lsw;    
    do 
    {        
        msw = TCNT_overflows;
        lsw = TCNT;
    } while (TCNT_overflows != msw) ;
    
    return  Rp16_UINT32(msw) + lsw;
}

    
static void read_TCNT(uint16_t *t)
{
    // make sure an atomic read of timer counters return a true 48 bit value
    do 
    {  
        t[0] = big_TCNT_overflows;      
        t[1] = TCNT_overflows;
        t[2] = TCNT;
    } while ( big_TCNT_overflows != t[0] || TCNT_overflows != t[1] || TCNT < t[2] );       
}

uint16_t hw_clock_uS(void)
{
    uint16_t TCNT_48b[3];				      
    read_TCNT(TCNT_48b);    
  
    uint16_t factor = (uint16_t) Rp11_UINT32((double)(1 << initial_TSCR2_PR) / CPU_FREQ_MHZ );  // r * 2^11
    
    //  assert (factor < Rp15_UINT16(1) )     		assume 16MHz is min CPU_FREQ
    uint32_t t_l = (uint32_t) TCNT_48b[2] * factor ;
    uint32_t t_m = (uint32_t) TCNT_48b[1] * factor ;
    uint32_t t_h = (uint32_t) TCNT_48b[0] * factor ;
    
    uint32_t rvalue =  Rn11_UINT32( t_l + Rp10_UINT16(1) ) +    // t_l * 2^(  -11)
                       Rp05_UINT32( t_m                  ) +    // t_m * 2^(16-11)
                       Rp21_UINT32( t_h                  );	    // t_h * 2^(32-11)
    return (uint16_t) rvalue;                  
}


uint16_t hw_clock_mS(void)
{
    uint16_t TCNT_48b[3];    
    read_TCNT(TCNT_48b);   
  
    uint16_t factor = (uint16_t) Rp21_UINT32((double)(1 << initial_TSCR2_PR)/ CPU_FREQ_KHZ );   // r * 2^21
    
    //  assert (factor < Rp15_UINT16(1) )      		assume 16MHz is min CPU_FREQ				     
    uint32_t t_l = (uint32_t) TCNT_48b[2] * factor ;
    uint32_t t_m = (uint32_t) TCNT_48b[1] * factor ;
    uint32_t t_h = (uint32_t) TCNT_48b[0] * factor ;
  
    uint32_t rvalue =  Rn21_UINT32( t_l + Rp20_UINT32(1) + Rp16_UINT32(t_m & 0x001F)) +   // t_l * 2^(  -21)
                       Rn05_UINT32( t_m                                             ) +   // t_m * 2^(16-21)
                       Rp11_UINT32( t_h                                             );    // t_h * 2^(32-21)
    return (uint16_t)rvalue;                  
}

uint16_t hw_clock_S(void)
{
    uint16_t TCNT_48b[3];    
    read_TCNT(TCNT_48b);   
  
    uint16_t factor = (uint16_t) Rp31_UINT32((double)(1 << initial_TSCR2_PR)/CPU_FREQ ) ;   // r * 2^31   
    
    //  assert (factor < Rp15_UINT16(1) )      		assume 16MHz is min CPU_FREQ					     
    uint32_t t_l = (uint32_t) TCNT_48b[2] * factor ; 
    uint32_t t_m = (uint32_t) TCNT_48b[1] * factor ;
    uint32_t t_h = (uint32_t) TCNT_48b[0] * factor ;
        
    uint32_t rvalue =  Rn31_UINT32( t_l + Rp30_UINT32(1) + Rp16_UINT32(t_m & 0x7FFF)) +   // t_l * 2^(  -31)
                       Rn15_UINT32( t_m                                             ) +   // t_m * 2^(16-31)
                       Rp01_UINT32( t_h                                             ) ;   // t_h * 2^(32-31) 
    return (uint16_t) rvalue;                    
}

// XuS = ticks * 2^TSCR2_PR / CPU_FREQ_MHZ        
uint32_t hw_clock_convert_clockticks_to_uS(uint32_t ticks)
{
    uint8_t prescale = 1 << initial_TSCR2_PR;
    uint32_t max_ticks = ULONG_MAX / prescale;
    
    if (ticks > max_ticks )
        ticks = max_ticks;
    
    uint32_t XuS = ticks * prescale / CPU_FREQ_MHZ;
    
    return XuS;
}


// ticks = XuS * CPU_FREQ / (10^6 * 2^TSCR2_PR)
//       = XuS * CPU_FREQ_MHz / 2^TSCR2_PR	  
#define MAX_XuS (ULONG_MAX / CPU_FREQ_MHZ)	  
uint32_t hw_clock_convert_uS_to_clockticks(uint32_t XuS)
{
    if (XuS > MAX_XuS)
        XuS = MAX_XuS;
    
    uint8_t prescale = 1 << initial_TSCR2_PR;
    uint32_t ticks = XuS * CPU_FREQ_MHZ / prescale;
    
    return ticks;    
}
    	   
