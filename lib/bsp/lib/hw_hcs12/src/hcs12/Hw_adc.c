
////////////////////////////////////////////////////////////////////////////////////////////////////
// Hardware specific A/D input functionality.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "hw_adc.h"
#include "hw_atd.h"
#include "hw_clock.h"


uint16_t hw_adc_data[HWC_ADC_QTY];
uint16_t hw_adc_GetValue(hw_adc_ch_t ch) {return hw_adc_data[ch];}

									 
////////////////////////////////////////////////////////////////////////////////////////////////////
// main A/D task functionality
////////////////////////////////////////////////////////////////////////////////////////////////////
static hw_atd ATD0, ATD1;  

void hw_adc_initialize(void)
{
    ATD0.initialize( (hw_atd::reg_t *) 0x0080);
    ATD1.initialize( (hw_atd::reg_t *) 0x0120);
    
    DDRJ |= 0xC0;
    hw_mcu_MuxSel_PutVal(0); // Initialize Mux hardware.  
    
    hw_adc_update();   // get an initial sample of all the channels
}


void hw_adc_update(void)			 // called every 10mS
{		
    ATD0.StartMeasurement(hw_atd::CH_ALL);
    
    for (uint8_t i=1; i<=4; ++i)
    {
        ATD1.StartMeasurement(hw_atd::CH_ALL);
        
        while (!ATD1.MeasurementDone(hw_atd::CH_ALL) )
            ;  // wait until the conversion is complete
            
        // switch mux.
        hw_mcu_MuxSel_PutVal(i);  // switch mux for next sample...
        
        // delay to allow the MUX to sabilize
        uint16_t mux_switch_start_time = hw_clock_uS();
		
		uint8_t j = i-1;	 // j is the mux value when the A/D reading occured
		
		if (j==0)
		{
		    ATD1.GetData(hw_atd::CH0, &hw_adc_data[8] ); 
	        ATD1.GetData(hw_atd::CH1, &hw_adc_data[9] );  
		}
		
	    ATD1.GetData(hw_atd::CH2, &hw_adc_data[10+j] ); 
	    ATD1.GetData(hw_atd::CH3, &hw_adc_data[14+j] ); 
	    ATD1.GetData(hw_atd::CH4, &hw_adc_data[18+j] ); 
	    ATD1.GetData(hw_atd::CH5, &hw_adc_data[22+j] );
	    ATD1.GetData(hw_atd::CH6, &hw_adc_data[26+j] ); 
	    ATD1.GetData(hw_atd::CH7, &hw_adc_data[30+j] );  
        
        while ((hw_clock_uS() - mux_switch_start_time) <= 5 )
            ;
    }
   
    while (!ATD0.MeasurementDone(hw_atd::CH_ALL) )
            ;  // wait until the conversion is complete
            
    ATD0.GetData(hw_atd::CH_ALL, &hw_adc_data[0] );
    
    hw_mcu_MuxSel_PutVal(0);              
}

