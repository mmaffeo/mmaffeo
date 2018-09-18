
#ifndef ap_SLEcontrol_defs_h
#define ap_SLEcontrol_defs_h


#include "hw_adc.h"
#include "hw_dio.h"
#include "hw_fin.h"
#include "hw_pwm.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
// Analog inputs	
#define PREFERENCE_AFBK       HWC_ADC_PRECISION_REF
#define BATT_AFBK             HWC_ADC_BATT_AFBK
#define SW_BATT_AFBK          HWC_ADC_SW_BATT_AFBK
#define VSENSOR1_AFBK         HWC_ADC_VSENSOR1_AFBK
#define VSENSOR2_AFBK         HWC_ADC_AIN08_VSENSOR2
		 											   
#define ENG_COOLANT_TEMP_AIN  HWC_ADC_AIN05
#define FUEL_LEVEL_AIN        HWC_ADC_AIN06     
#define CONSOLE_AIN           HWC_ADC_AIN07		   
#define LOAD_MOMENT_AIN       HWC_ADC_AIN10
#define OFFSET_POT_AIN        HWC_ADC_AIN09	
#define AUX_POT_AIN           HWC_ADC_AIN13
#define THROTTLE_PRIMARY      HWC_ADC_AIN12
#define ENGINE_SPEED_AFBK     HWC_ADC_FIN1_AFBK
#define ENGINE_SPEED_FIN      HWC_FIN0
#define OWD_ENABLE_AIN        HWC_ADC_AIN11_LC_LSD1_AFBK


////////////////////////////////////////////////////////////////////////////////////////////////////
// Analog inputs with optional pullups
#define ENG_OIL_PRESS_AIN      HWC_ADC_AIN01_DIN01
#define ENG_OIL_PRESS_PUP_DOUT HWC_DOUT_DIN01_ENABLE
#define HYD_OIL_TEMP_AIN       HWC_ADC_AIN02_DIN02
#define HYD_OIL_TEMP_PUP_DOUT  HWC_DOUT_DIN02_ENABLE
#define TRAVEL_LEVER_AIN       HWC_ADC_AIN03_DIN03
#define TRAVEL_LEVER_PUP_DOUT  HWC_DOUT_DIN03_ENABLE
#define LOAD_SENSE_PRESS_AIN   HWC_ADC_AIN04_DIN04
#define LOAD_SENSE_PUP_DOUT    HWC_DOUT_DIN04_ENABLE        
#define AUX2_FLOW_CONTROL_AIN  HWC_ADC_AIN03_DIN03

////////////////////////////////////////////////////////////////////////////////////////////////////
//	Switch inputs
#define LEFT_HANDLE_SELECT_SW   HWC_DIN09
#define SECOND_AUX_DIN          HWC_DIN09
#define OWD_ENABLE_DIN          HWC_DIN09
#define TWO_SPEED_SW_DIN        HWC_DIN11
#define DETENT_SW_DIN           HWC_DIN12
#define AIR_FILTER_SW           HWC_DIN13
#define HYD_OIL_FILTER_SW1      HWC_DIN14
#define AC_INPUT                HWC_DIN15
#define REMOTE_KEY              HWC_DIN16
#define RUN_ENTER_SW            HWC_DIN17
#define START_ENGINE_SW         HWC_DIN18

////////////////////////////////////////////////////////////////////////////////////////////////////
// High side solenoid drivers
#define FUEL_HOLD_HS_PWM  HWC_PWM_HC_HSD1
#define FUEL_HOLD_HS_AFBK HWC_ADC_HC_HSD1_AFBK

#define TWO_SPEED_HS_PWM  HWC_PWM_HC_HSD3
#define TWO_SPEED_HS_AFBK HWC_ADC_HC_HSD3_AFBK

////////////////////////////////////////////////////////////////////////////////////////////////////
// High/Low side solenoid driver pairs
#define AUX_ROD_HS_PWM   HWC_PWM_HC_HSD5
#define AUX_ROD_HS_AFBK  HWC_ADC_HC_HSD5_AFBK
#define AUX_ROD_LS_DOUT  HWC_DOUT_HC_LSD2_CMD
#define AUX_ROD_LS_IFBK  HWC_ADC_HC_LSD2_IFBK 

#define AUX_BASE_HS_PWM     HWC_PWM_HC_HSD6
#define AUX_BASE_HS_AFBK    HWC_ADC_HC_HSD6_AFBK
#define AUX_BASE_LS_DOUT    HWC_DOUT_HC_LSD4_CMD
#define AUX_BASE_LS_IFBK    HWC_ADC_HC_LSD4_IFBK 

#define HYD_ENABLE_HS_PWM  HWC_PWM_HC_HSD7
#define HYD_ENABLE_HS_AFBK HWC_ADC_HC_HSD7_AFBK
#define HYD_ENABLE_LS_DOUT HWC_DOUT_HC_LSD5_CMD
#define HYD_ENABLE_LS_IFBK HWC_ADC_HC_LSD5_IFBK

#define DUMP_VALVE_HS_PWM  HWC_PWM_HC_HSD8
#define DUMP_VALVE_HS_AFBK HWC_ADC_HC_HSD8_AFBK 
#define DUMP_VALVE_LS_DOUT HWC_DOUT_HC_LSD6_CMD
#define DUMP_VALVE_LS_IFBK HWC_ADC_HC_LSD6_IFBK

#define HYD_BYPASS_HS_PWM  HWC_PWM_HC_HSD8
#define HYD_BYPASS_HS_AFBK HWC_ADC_HC_HSD8_AFBK 
#define HYD_BYPASS_LS_DOUT HWC_DOUT_HC_LSD6_CMD
#define HYD_BYPASS_LS_IFBK HWC_ADC_HC_LSD6_IFBK

#define OFFSET_ROD_HS_PWM  HWC_PWM_HC_HSD2
#define OFFSET_ROD_HS_AFBK HWC_ADC_HC_HSD2_AFBK 	 
#define OFFSET_ROD_LS_DOUT HWC_DOUT_HC_LSD1_CMD  
#define OFFSET_ROD_LS_IFBK HWC_ADC_HC_LSD1_IFBK 

#define OFFSET_BASE_HS_PWM  HWC_PWM_HC_HSD4
#define OFFSET_BASE_HS_AFBK HWC_ADC_HC_HSD4_AFBK 
#define OFFSET_BASE_LS_DOUT HWC_DOUT_HC_LSD3_CMD
#define OFFSET_BASE_LS_IFBK HWC_ADC_HC_LSD3_IFBK

#define DIVERTER_HS_PWM  HWC_PWM_HC_HSD8
#define DIVERTER_HS_AFBK HWC_ADC_HC_HSD8_AFBK 
#define DIVERTER_LS_DOUT HWC_DOUT_HC_LSD6_CMD
#define DIVERTER_LS_IFBK HWC_ADC_HC_LSD6_IFBK

    
////////////////////////////////////////////////////////////////////////////////////////////////////
// Relay drivers        
#define SW_PWR_OUT_RLY_DOUT HWC_DOUT_LC_HSD1_CMD
#define SW_PWR_OUT_RLY_DFBK HWC_DIN_LC_HSD1_DFBK
#define SW_PWR_OUT_RLY_DIN  HWC_DIN05

#define FUEL_PULL_RLY_DOUT HWC_DOUT_LC_HSD2_CMD
#define FUEL_PULL_RLY_DFBK HWC_DIN_LC_HSD2_DFBK
#define FUEL_PULL_RLY_DIN  HWC_DIN06
    
#define GLOW_PLUG_RLY_DOUT HWC_DOUT_LC_HSD3_CMD    
#define GLOW_PLUG_RLY_DFBK HWC_DIN_LC_HSD3_DFBK    
#define GLOW_PLUG_RLY_DIN  HWC_DIN07

#define LIGHTS_DOUT HWC_DOUT_LC_HSD4_CMD			
#define	LIGHTS_DFBK HWC_DIN_LC_HSD4_DFBK
//#define LIGHTS_RLY_DIN  HWC_DIN08

#define BUZZER_DOUT HWC_DOUT_LC_HSD5_CMD

#define STARTER_RLY_DOUT HWC_DOUT_LC_HSD6_CMD
#define STARTER_RLY_DFBK HWC_DIN_LC_HSD6_DFBK
#define STARTER_RLY_DIN  HWC_DIN10

#define SECOND_AUX_RELEASE_DOUT HWC_DOUT_LC_HSD7_CMD
#define HYD_EXCHANGE_DOUT HWC_DOUT_LC_HSD7_CMD
#define HYD_EXCHANGE_DFBK HWC_DIN_LC_HSD7_DFBK


#define HVAC_RLY_DOUT HWC_DOUT_LC_HSD8_CMD
#define HVAC_RLY_DFBK HWC_DIN_LC_HSD8_DFBK

#define PBVALVE_RLY_DOUT HWC_DOUT_LC_HSD8_CMD
#define PBVALVE_RLY_DFBK HWC_DIN_LC_HSD8_DFBK
#define PBVALVE_RLY_DIN  HWC_DIN08
	

#endif