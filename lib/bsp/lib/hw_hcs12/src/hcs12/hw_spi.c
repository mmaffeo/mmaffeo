
#include "hw_spi.h"
#include "hw_config.h"	  

const hw_spi::cfg_t hw_spi::DEFAULT_CFG=
{
    0x51,   // SPICR1 <<SPIE:SPE:SPTIE:MSTR:CPOL:CPHA:SSOE:LSBFE >>
            //  SPIE=0  ;SPI interrupts disabled
            //  SPE=1   ;SPI System Enable Bit
            //  SPTIE=1 ;SPITEF interrupt disabled
            //  MSTR=1  ;Master Mode
            //  CPOL=0  ;Active High clocks selected.
            //  CPHA=0  ;The first SCK edge is issued one-half cycle 
            //          ;  into the 8-cycle transfer operation
            //  SSOE=0
            //  LSBFE=1 ;data is transfgered least siginificant bit first            
    
    0x00, 	// SPICR2 <<0:0:0:MODFEN:BIDIROE:0:SPISWAI:SPC0>>
    
    2000    // baud rate in kHz
};       
       
            
// divisor = (SPPR+1) * 2^(SPR+1)        
static uint16_t br_divisor(uint8_t SPPR, uint8_t SPR)
{
    uint16_t pr = 1 << (uint8_t)(SPR+1);
    
    return (SPPR+1) * pr;    
}


void hw_spi::initialize(reg_t * reg_, const cfg_t *cfg_ )
{
    reg = reg_;
    cfg = cfg_;
    
    reg->SPICR1 = cfg->initial_SPICR1;
    reg->SPICR2 = cfg->initial_SPICR2;
    
    // calculate the SPPR and SPR prescaler values to get the desired baud rate.
    uint16_t divisor = (uint16_t)(CPU_FREQ/1000) / cfg->baud_rate_kHz; 
    
    // Sequentally try larger SPPR and SPR values until we get a "pdiv" that is greater 
    // than or equal to the "divisor".
    uint8_t SPR_value=0;
    uint8_t SPPR_value=0;     
    uint16_t pdiv=br_divisor(SPPR_value, SPR_value);
    
    while ( SPR_value < 7 && pdiv < divisor )
    {
        SPPR_value=0;
        
        while (SPPR_value < 7 && pdiv < divisor)
        {
            ++SPPR_value;
            pdiv=br_divisor(SPPR_value, SPR_value);
        }
        
        if (pdiv < divisor)
            ++SPR_value;        
    }
    
    reg->SPIBR  = SPR_value | (SPPR_value <<4);
}


bool hw_spi::TxChar(uint8_t data)
{
    bool rvalue=false;
    if (reg->SPISR & 0x20 )     // only write if SPTEF flag is set... 
    {
        reg->SPIDR = data;
        rvalue = true;
    }
    
    return rvalue;              
}
  
  
uint8_t hw_spi::RxDataAvailiable(void)
{
    return reg->SPISR & 0x80 ? true:false; // return SPIF flag state.    
}
    
    
uint8_t hw_spi::RxChar(void)
{
    return reg->SPIDR;    
}