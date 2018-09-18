
  
#include "hw_atd.h"
#include "hw_config.h"


 
#define PRS_value	 (CPU_FREQ / 4000000u)
 
const hw_atd::cfg_t hw_atd::DEFAULT_CFG=
{
    0x00 | PRS_value, // ATDCTL4  <<SRES8:SMP(2-bits):PRS(5-bits)>>
                      //    SRES8=0 ;10-bit resolution
                      //    SMP=0   ;2 A/D clock cycles for sampling
                      //    PRS=PRS_value 
                      //            ;ATD_clock >= 0.5 MHz 
                      //            ;ATD_clock <= 2.0 MHz                       
                      //            ;ATD_clock = CPU_FREQ *0.5 / (PRS+1)
                      //            ; solve for ATD_clock<=2.0MHz
                      //            ;   CPU_FREQ * 0.5 / (PRS+1) <= 2.0MHz 
                      //            ;   PRS  >= (CPU_FREQ / 2 * 2MHz) - 1
                      
    0x80              // ATDCTL5  <<DJM:DSGN:SCAN:MULT:0:CC:CB:CA>>   
                      //    DJM=1   ;right justify data in the result registers
                      //    DSGN=0  ;unsigned data representation in the result register             
};       
       
        
void hw_atd::initialize(reg_t * reg_, const cfg_t *cfg_ )
{
    reg = reg_;
    cfg = cfg_;
    
    reg->atdctl2 = 0xC0; // ADPU=1:AFFC=1:AWAI=0:ETRIGLE=0:ETRIGP=0:ETRIGE=0:ASCIE=0:ASCIF
    reg->atdctl3 = 0x00; // ????
    reg->atdctl4 = cfg->initial_ATDCTL4;
    reg->atdctl5 = cfg->initial_ATDCTL5;
}


void hw_atd::StartMeasurement(ch_t channel)
{
    uint8_t cmd = reg->atdctl5 & 0xC0;  // maintain DJM and DSGN bits
    
    switch (channel)
    {
        case CH_ALL: 
            cmd |= 0x10;  // MULT=1, CC:CB:CA=0:0:0 
            break;
        case CH0: case CH1: case CH2: case CH3:
        case CH4: case CH5: case CH6: case CH7:
            cmd |= (uint8_t)channel;
            break;
    }
    
    reg->atdctl5 = cmd;  // start the conversion sequence    
}

    
bool hw_atd::MeasurementDone(ch_t channel)
{
    bool rvalue=true;
    switch (channel)
    {
        case CH0:    rvalue = reg->atdstat1 & 0x01? true: false;  break;
        case CH1:    rvalue = reg->atdstat1 & 0x02? true: false;  break;
        case CH2:    rvalue = reg->atdstat1 & 0x04? true: false;  break;
        case CH3:    rvalue = reg->atdstat1 & 0x08? true: false;  break;
        case CH4:    rvalue = reg->atdstat1 & 0x10? true: false;  break;
        case CH5:    rvalue = reg->atdstat1 & 0x20? true: false;  break;
        case CH6:    rvalue = reg->atdstat1 & 0x40? true: false;  break;
        case CH7:    rvalue = reg->atdstat1 & 0x80? true: false;  break;
        case CH_ALL: rvalue = reg->atdstat1 == 0xFF? true: false;  break;
    }    
    return rvalue;
}

    
void hw_atd::GetData(ch_t channel, uint16_t *buffer)
{
    switch (channel)
    {
        case CH_ALL: 
            for (uint8_t i=0; i<=7; ++i )
                buffer[i] = reg->atddr[i];
    		break;
            
        case CH0: case CH1: case CH2: case CH3:
        case CH4: case CH5: case CH6: case CH7:
            *buffer = reg->atddr[channel];
            break;
    }
}