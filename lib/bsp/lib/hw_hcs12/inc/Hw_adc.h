
/* 
    Hardware specific A/D input functionality.
*/ 

#ifndef hw_adc_h
#define hw_adc_h

#include "stdint.h"


typedef enum 
{
    // ADC0
    HWC_ADC_PRECISION_REF,  HWC_ADC_BATT_AFBK,          HWC_ADC_SW_BATT_AFBK, HWC_ADC_VSENSOR1_AFBK, 
    HWC_ADC_AIN08_VSENSOR2, HWC_ADC_AIN11_LC_LSD1_AFBK, HWC_ADC_HC_LSD1_IFBK, HWC_ADC_HC_LSD2_IFBK,
    
    // ADC1 
    HWC_ADC_HC_LSD3_IFBK,   HWC_ADC_HC_LSD4_IFBK, 
    
    //-----MUX1_X
    HWC_ADC_AIN01_DIN01,  HWC_ADC_AIN02_DIN02,  HWC_ADC_AIN03_DIN03,  HWC_ADC_AIN04_DIN04,     
     
    // ----MUX1_Y  
    HWC_ADC_AIN05,        HWC_ADC_AIN06,        HWC_ADC_AIN07,        HWC_ADC_FIN1_AFBK, 
    
    // ----MUX2_X 
    HWC_ADC_AIN09, 		  HWC_ADC_AIN10,        HWC_ADC_HC_HSD1_AFBK, HWC_ADC_HC_HSD2_AFBK, 
    
    // ----MUX2_Y
    HWC_ADC_HC_HSD3_AFBK, HWC_ADC_HC_HSD4_AFBK, HWC_ADC_HC_HSD5_AFBK, HWC_ADC_HC_HSD6_AFBK,
    
    // ----MUX3_X
    HWC_ADC_HC_HSD7_AFBK, HWC_ADC_HC_HSD8_AFBK, HWC_ADC_HC_LSD5_IFBK, HWC_ADC_HC_LSD6_IFBK,
     
    // ----MUX3_Y    
    HWC_ADC_AIN12,	      HWC_ADC_AIN13,      HWC_ADC_HC_LSD5_AFBK, HWC_ADC_HC_LSD6_AFBK,

    HWC_ADC_QTY 
} hw_adc_ch_t;


uint16_t hw_adc_GetValue(hw_adc_ch_t ch);  // returns the most recent 
                                           // 10-bit A/D sample from this channel


/////////////////////////////////////////////////////////////////////////////////////////////////////
// hw_io diver interface, the user of the "hw_io" modules should not need to access this information.
void hw_adc_initialize(void);
void hw_adc_update    (void);		  

#endif