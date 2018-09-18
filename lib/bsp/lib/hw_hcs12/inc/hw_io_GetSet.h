// Interface for the MATLAB/SIMULINK RTW embedded coder custom storage class "GetSet"

#ifndef hw_io_GetSet_h
#define hw_io_GetSet_h

#include "hw_io.h"    


#define hw_adc_GetValue_PRECISION_REF()     (hw_adc_GetValue(HWC_ADC_PRECISION_REF))
#define hw_adc_GetValue_BATT_AFBK()         (hw_adc_GetValue(HWC_ADC_BATT_AFBK    ))
#define hw_adc_GetValue_SW_BATT_AFBK()      (hw_adc_GetValue(HWC_ADC_SW_BATT_AFBK ))
#define hw_adc_GetValue_VSENSOR1_AFBK()     (hw_adc_GetValue(HWC_ADC_VSENSOR1_AFBK))
#define hw_adc_GetValue_AIN08_VSENSOR2()    (hw_adc_GetValue(HWC_ADC_AIN08_VSENSOR2    ))
#define hw_adc_GetValue_AIN11_LC_LSD1_AFBK()(hw_adc_GetValue(HWC_ADC_AIN11_LC_LSD1_AFBK))
#define hw_adc_GetValue_HC_LSD1_IFBK()      (hw_adc_GetValue(HWC_ADC_HC_LSD1_IFBK))
#define hw_adc_GetValue_HC_LSD2_IFBK()      (hw_adc_GetValue(HWC_ADC_HC_LSD2_IFBK))
#define hw_adc_GetValue_HC_LSD3_IFBK()      (hw_adc_GetValue(HWC_ADC_HC_LSD3_IFBK))
#define hw_adc_GetValue_HC_LSD4_IFBK()      (hw_adc_GetValue(HWC_ADC_HC_LSD4_IFBK))
#define hw_adc_GetValue_AIN01_DIN01()       (hw_adc_GetValue(HWC_ADC_AIN01_DIN01))
#define hw_adc_GetValue_AIN02_DIN02()       (hw_adc_GetValue(HWC_ADC_AIN02_DIN02))
#define hw_adc_GetValue_AIN03_DIN03()       (hw_adc_GetValue(HWC_ADC_AIN03_DIN03))
#define hw_adc_GetValue_AIN04_DIN04()       (hw_adc_GetValue(HWC_ADC_AIN04_DIN04))
#define hw_adc_GetValue_AIN05()             (hw_adc_GetValue(HWC_ADC_AIN05))
#define hw_adc_GetValue_AIN06()             (hw_adc_GetValue(HWC_ADC_AIN06))
#define hw_adc_GetValue_AIN07()             (hw_adc_GetValue(HWC_ADC_AIN07))
#define hw_adc_GetValue_FIN1_AFBK()         (hw_adc_GetValue(HWC_ADC_FIN1_AFBK))
#define hw_adc_GetValue_AIN09()             (hw_adc_GetValue(HWC_ADC_AIN09))
#define hw_adc_GetValue_AIN10()             (hw_adc_GetValue(HWC_ADC_AIN10))
#define hw_adc_GetValue_AIN12()             (hw_adc_GetValue(HWC_ADC_AIN12))
#define hw_adc_GetValue_AIN13()             (hw_adc_GetValue(HWC_ADC_AIN13))    
#define hw_adc_GetValue_HC_HSD1_AFBK()      (hw_adc_GetValue(HWC_ADC_HC_HSD1_AFBK))
#define hw_adc_GetValue_HC_HSD2_AFBK()      (hw_adc_GetValue(HWC_ADC_HC_HSD2_AFBK))
#define hw_adc_GetValue_HC_HSD3_AFBK()      (hw_adc_GetValue(HWC_ADC_HC_HSD3_AFBK))
#define hw_adc_GetValue_HC_HSD4_AFBK()      (hw_adc_GetValue(HWC_ADC_HC_HSD4_AFBK))
#define hw_adc_GetValue_HC_HSD5_AFBK()      (hw_adc_GetValue(HWC_ADC_HC_HSD5_AFBK))
#define hw_adc_GetValue_HC_HSD6_AFBK()      (hw_adc_GetValue(HWC_ADC_HC_HSD6_AFBK))
#define hw_adc_GetValue_HC_HSD7_AFBK()      (hw_adc_GetValue(HWC_ADC_HC_HSD7_AFBK))
#define hw_adc_GetValue_HC_HSD8_AFBK()      (hw_adc_GetValue(HWC_ADC_HC_HSD8_AFBK))
#define hw_adc_GetValue_HC_LSD5_IFBK()      (hw_adc_GetValue(HWC_ADC_HC_LSD5_IFBK))
#define hw_adc_GetValue_HC_LSD6_IFBK()      (hw_adc_GetValue(HWC_ADC_HC_LSD6_IFBK))
#define hw_adc_GetValue_HC_LSD5_AFBK()      (hw_adc_GetValue(HWC_ADC_HC_LSD5_AFBK))
#define hw_adc_GetValue_HC_LSD6_AFBK()      (hw_adc_GetValue(HWC_ADC_HC_LSD6_AFBK))

#define hw_din_GetValue_DIN18()             (hw_din_GetValue(HWC_DIN18))
#define hw_din_GetValue_DIN17()             (hw_din_GetValue(HWC_DIN17))
#define hw_din_GetValue_DIN16()             (hw_din_GetValue(HWC_DIN16))
#define hw_din_GetValue_DIN15()             (hw_din_GetValue(HWC_DIN15))
#define hw_din_GetValue_DIN14()             (hw_din_GetValue(HWC_DIN14))
#define hw_din_GetValue_DIN13()             (hw_din_GetValue(HWC_DIN13))
#define hw_din_GetValue_DIN12()             (hw_din_GetValue(HWC_DIN12))
#define hw_din_GetValue_DIN11()             (hw_din_GetValue(HWC_DIN11))
#define hw_din_GetValue_DIN10()             (hw_din_GetValue(HWC_DIN10))
#define hw_din_GetValue_DIN09()             (hw_din_GetValue(HWC_DIN09))
#define hw_din_GetValue_DIN08()             (hw_din_GetValue(HWC_DIN08))
#define hw_din_GetValue_DIN07()             (hw_din_GetValue(HWC_DIN07))
#define hw_din_GetValue_DIN06()             (hw_din_GetValue(HWC_DIN06))
#define hw_din_GetValue_DIN05()             (hw_din_GetValue(HWC_DIN05))		
#define hw_din_GetValue_LC_HSD1_DFBK()      (hw_din_GetValue(HWC_DIN_LC_HSD1_DFBK))
#define hw_din_GetValue_LC_HSD2_DFBK()      (hw_din_GetValue(HWC_DIN_LC_HSD2_DFBK))
#define hw_din_GetValue_LC_HSD3_DFBK()      (hw_din_GetValue(HWC_DIN_LC_HSD3_DFBK))
#define hw_din_GetValue_LC_HSD4_DFBK()      (hw_din_GetValue(HWC_DIN_LC_HSD4_DFBK))
#define hw_din_GetValue_LC_HSD5_DFBK()      (hw_din_GetValue(HWC_DIN_LC_HSD5_DFBK))
#define hw_din_GetValue_LC_HSD6_DFBK()      (hw_din_GetValue(HWC_DIN_LC_HSD6_DFBK))
#define hw_din_GetValue_LC_HSD7_DFBK()      (hw_din_GetValue(HWC_DIN_LC_HSD7_DFBK))
#define hw_din_GetValue_LC_HSD8_DFBK()      (hw_din_GetValue(HWC_DIN_LC_HSD8_DFBK))

#define hw_fin_GetPeriod_FIN1()             (hw_fin_GetPerioduS(HWC_FIN0) ) 
			   
#define hw_dout_GetValue_HC_LSD1()          (hw_dout_GetValue (HWC_DOUT_HC_LSD1_CMD        ))
#define hw_dout_GetValue_HC_LSD2()          (hw_dout_GetValue (HWC_DOUT_HC_LSD2_CMD        ))
#define hw_dout_GetValue_HC_LSD3()          (hw_dout_GetValue (HWC_DOUT_HC_LSD3_CMD        ))
#define hw_dout_GetValue_HC_LSD4()          (hw_dout_GetValue (HWC_DOUT_HC_LSD4_CMD        ))
#define hw_dout_GetValue_HC_LSD5()          (hw_dout_GetValue (HWC_DOUT_HC_LSD5_CMD        ))
#define hw_dout_GetValue_HC_LSD6()          (hw_dout_GetValue (HWC_DOUT_HC_LSD6_CMD        ))
#define hw_dout_GetValue_LC_HSD1()          (hw_dout_GetValue (HWC_DOUT_LC_HSD1_CMD        ))
#define hw_dout_GetValue_LC_HSD2()          (hw_dout_GetValue (HWC_DOUT_LC_HSD2_CMD        ))
#define hw_dout_GetValue_LC_HSD3()          (hw_dout_GetValue (HWC_DOUT_LC_HSD3_CMD        ))
#define hw_dout_GetValue_LC_HSD4()          (hw_dout_GetValue (HWC_DOUT_LC_HSD4_CMD        ))
#define hw_dout_GetValue_LC_HSD5()          (hw_dout_GetValue (HWC_DOUT_LC_HSD5_CMD        ))
#define hw_dout_GetValue_LC_HSD6()          (hw_dout_GetValue (HWC_DOUT_LC_HSD6_CMD        ))
#define hw_dout_GetValue_LC_HSD7()          (hw_dout_GetValue (HWC_DOUT_LC_HSD7_CMD        ))
#define hw_dout_GetValue_LC_HSD8()          (hw_dout_GetValue (HWC_DOUT_LC_HSD8_CMD        ))
#define hw_dout_GetValue_DIN01_ENABLE()     (hw_dout_GetValue (HWC_DOUT_DIN01_ENABLE       ))
#define hw_dout_GetValue_DIN02_ENABLE()     (hw_dout_GetValue (HWC_DOUT_DIN02_ENABLE       ))
#define hw_dout_GetValue_DIN03_ENABLE()     (hw_dout_GetValue (HWC_DOUT_DIN03_ENABLE       ))
#define hw_dout_GetValue_DIN04_ENABLE()     (hw_dout_GetValue (HWC_DOUT_DIN04_ENABLE       ))
#define hw_dout_SetValue_HC_LSD1(value)     (hw_dout_SetValue(HWC_DOUT_HC_LSD1_CMD  ,value ))
#define hw_dout_SetValue_HC_LSD2(value)     (hw_dout_SetValue(HWC_DOUT_HC_LSD2_CMD  ,value ))
#define hw_dout_SetValue_HC_LSD3(value)     (hw_dout_SetValue(HWC_DOUT_HC_LSD3_CMD  ,value ))
#define hw_dout_SetValue_HC_LSD4(value)     (hw_dout_SetValue(HWC_DOUT_HC_LSD4_CMD  ,value ))
#define hw_dout_SetValue_HC_LSD5(value)     (hw_dout_SetValue(HWC_DOUT_HC_LSD5_CMD  ,value ))
#define hw_dout_SetValue_HC_LSD6(value)     (hw_dout_SetValue(HWC_DOUT_HC_LSD6_CMD  ,value ))
#define hw_dout_SetValue_LC_HSD1(value)     (hw_dout_SetValue(HWC_DOUT_LC_HSD1_CMD  ,value ))
#define hw_dout_SetValue_LC_HSD2(value)     (hw_dout_SetValue(HWC_DOUT_LC_HSD2_CMD  ,value ))
#define hw_dout_SetValue_LC_HSD3(value)     (hw_dout_SetValue(HWC_DOUT_LC_HSD3_CMD  ,value ))
#define hw_dout_SetValue_LC_HSD4(value)     (hw_dout_SetValue(HWC_DOUT_LC_HSD4_CMD  ,value ))
#define hw_dout_SetValue_LC_HSD5(value)     (hw_dout_SetValue(HWC_DOUT_LC_HSD5_CMD  ,value ))
#define hw_dout_SetValue_LC_HSD6(value)     (hw_dout_SetValue(HWC_DOUT_LC_HSD6_CMD  ,value ))
#define hw_dout_SetValue_LC_HSD7(value)     (hw_dout_SetValue(HWC_DOUT_LC_HSD7_CMD  ,value ))
#define hw_dout_SetValue_LC_HSD8(value)     (hw_dout_SetValue(HWC_DOUT_LC_HSD8_CMD  ,value ))
#define hw_dout_SetValue_DIN01_ENABLE(value)(hw_dout_SetValue(HWC_DOUT_DIN01_ENABLE ,value ))
#define hw_dout_SetValue_DIN02_ENABLE(value)(hw_dout_SetValue(HWC_DOUT_DIN02_ENABLE ,value ))
#define hw_dout_SetValue_DIN03_ENABLE(value)(hw_dout_SetValue(HWC_DOUT_DIN03_ENABLE ,value ))
#define hw_dout_SetValue_DIN04_ENABLE(value)(hw_dout_SetValue(HWC_DOUT_DIN04_ENABLE ,value ))

#define hw_pwm_GetRatio16_HC_HSD1()         (hw_pwm_GetRatio16(HWC_PWM_HC_HSD1         ))
#define hw_pwm_GetRatio16_HC_HSD2()         (hw_pwm_GetRatio16(HWC_PWM_HC_HSD2         ))
#define hw_pwm_GetRatio16_HC_HSD3()         (hw_pwm_GetRatio16(HWC_PWM_HC_HSD3         ))
#define hw_pwm_GetRatio16_HC_HSD4()         (hw_pwm_GetRatio16(HWC_PWM_HC_HSD4         ))
#define hw_pwm_GetRatio16_HC_HSD5()         (hw_pwm_GetRatio16(HWC_PWM_HC_HSD5         ))
#define hw_pwm_GetRatio16_HC_HSD6()         (hw_pwm_GetRatio16(HWC_PWM_HC_HSD6         ))
#define hw_pwm_GetRatio16_HC_HSD7()         (hw_pwm_GetRatio16(HWC_PWM_HC_HSD7         ))
#define hw_pwm_GetRatio16_HC_HSD8()         (hw_pwm_GetRatio16(HWC_PWM_HC_HSD8         ))
#define hw_pwm_GetRatio16_LC_LSD1()         (hw_pwm_GetRatio16(HWC_PWM_LC_LSD1         ))
#define hw_pwm_SetRatio16_HC_HSD1(value)    (hw_pwm_SetRatio16(HWC_PWM_HC_HSD1,  value ))
#define hw_pwm_SetRatio16_HC_HSD2(value)    (hw_pwm_SetRatio16(HWC_PWM_HC_HSD2,  value ))
#define hw_pwm_SetRatio16_HC_HSD3(value)    (hw_pwm_SetRatio16(HWC_PWM_HC_HSD3,  value ))
#define hw_pwm_SetRatio16_HC_HSD4(value)    (hw_pwm_SetRatio16(HWC_PWM_HC_HSD4,  value ))
#define hw_pwm_SetRatio16_HC_HSD5(value)    (hw_pwm_SetRatio16(HWC_PWM_HC_HSD5,  value ))
#define hw_pwm_SetRatio16_HC_HSD6(value)    (hw_pwm_SetRatio16(HWC_PWM_HC_HSD6,  value ))
#define hw_pwm_SetRatio16_HC_HSD7(value)    (hw_pwm_SetRatio16(HWC_PWM_HC_HSD7,  value ))
#define hw_pwm_SetRatio16_HC_HSD8(value)    (hw_pwm_SetRatio16(HWC_PWM_HC_HSD8,  value ))
#define hw_pwm_SetRatio16_LC_LSD1(value)    (hw_pwm_SetRatio16(HWC_PWM_LC_LSD1,  value ))



#endif

  
  
