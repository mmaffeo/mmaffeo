//******************************************************************************
/**
 * \file    bsp_types.h
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Board specific type definitions
 *
 * \copyright
 * Copyright 2013 Bobcat Company as an unpublished work.
 * All Rights Reserved.
 *
 * \b Notice:
 * The information contained herein is confidential
 * property of Bobcat Company. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Bobcat Company.
 *
 *******************************************************************************/
#ifndef BSP_TYPES_H
#define BSP_TYPES_H

#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum bsp_adc_e
{
  BSP_ADC_AIN01 = 0,             // 0
  BSP_ADC_AIN02,                 // 1
  BSP_ADC_AIN03,                 // 2
  BSP_ADC_AIN04,                 // 3
  BSP_ADC_AIN05,                 // 4
  BSP_ADC_AIN06,                 // 5
  BSP_ADC_AIN07,                 // 6
  BSP_ADC_AIN08,                 // 7
  BSP_ADC_AIN09,                 // 8
  BSP_ADC_AIN10,                 // 9
  BSP_ADC_AIN11,                 // 10
  BSP_ADC_AIN12,                 // 11
  BSP_ADC_AIN13,                 // 12
  BSP_ADC_FIN01_AFBK,            // 13
  BSP_ADC_FIN03_AFBK,            // 14
  BSP_ADC_FIN04_AFBK,            // 15
  BSP_ADC_HC_HSD1_AFBK,          // 16
  BSP_ADC_HC_HSD2_AFBK,          // 17
  BSP_ADC_HC_HSD3_AFBK,          // 18
  BSP_ADC_HC_HSD4_AFBK,          // 19
  BSP_ADC_HC_HSD5_AFBK,          // 20
  BSP_ADC_HC_HSD6_AFBK,          // 21
  BSP_ADC_HC_HSD7_AFBK,          // 22
  BSP_ADC_HC_HSD8_AFBK,          // 23
  BSP_ADC_HC_LSD1_IFBK,          // 24
  BSP_ADC_HC_LSD2_IFBK,          // 25
  BSP_ADC_HC_LSD3_IFBK,          // 26
  BSP_ADC_HC_LSD4_IFBK,          // 27
  BSP_ADC_HC_LSD5_IFBK,          // 28
  BSP_ADC_HC_LSD6_IFBK,          // 29
  BSP_ADC_VSENSOR1_AFBK,         // 30
  BSP_ADC_VBAT_AFBK_V,           // 31
  BSP_ADC_VSW_AFBK_V             // 32
} bsp_adc_t;

typedef enum bsp_can_e
{
  BSP_CAN_1 = 0,                 // 0
  BSP_CAN_2                      // 1
} bsp_can_t;

typedef enum bsp_com_e
{
  BSP_COM_1 = 0,                 // 0
  BSP_COM_2                      // 1
} bsp_com_t;

typedef enum bsp_din_e
{
  BSP_DIN_DIN01 = 0,             // 0
  BSP_DIN_DIN02,                 // 1
  BSP_DIN_DIN03,                 // 2
  BSP_DIN_DIN04,                 // 3
  BSP_DIN_DIN05,                 // 4
  BSP_DIN_DIN06,                 // 5
  BSP_DIN_DIN07,                 // 6
  BSP_DIN_DIN08,                 // 7
  BSP_DIN_DIN09,                 // 8
  BSP_DIN_DIN10,                 // 9
  BSP_DIN_DIN11,                 // 10
  BSP_DIN_DIN12,                 // 11
  BSP_DIN_DIN13,                 // 12
  BSP_DIN_DIN14,                 // 13
  BSP_DIN_DIN15,                 // 14
  BSP_DIN_DIN16,                 // 15
  BSP_DIN_DIN17,                 // 16
  BSP_DIN_DIN18,                 // 17
  BSP_DIN_LC_HSD1_DFBK,          // 18
  BSP_DIN_LC_HSD2_DFBK,          // 19
  BSP_DIN_LC_HSD3_DFBK,          // 20
  BSP_DIN_LC_HSD4_DFBK,          // 21
  BSP_DIN_LC_HSD5_DFBK,          // 22
  BSP_DIN_LC_HSD6_DFBK,          // 23
  BSP_DIN_LC_HSD7_DFBK,          // 24
  BSP_DIN_LC_HSD8_DFBK,          // 25
  BSP_DIN_HW_ID0,                // 26
  BSP_DIN_HW_ID1,                // 27
  BSP_DIN_HW_ID2,                // 28
  BSP_DIN_HW_ID3,                // 29
  BSP_DIN_HW_ID4,                // 30
  BSP_DIN_HW_ID5,                // 31
  BSP_DIN_HW_ID6                 // 32
} bsp_din_t;

typedef enum bsp_dout_e
{
  BSP_DOUT_PWR_HOLD_ON = 0,       // 0
  BSP_DOUT_CAN_TERM_OFF1,         // 1
  BSP_DOUT_CAN_TERM_OFF2,         // 2
  BSP_DOUT_DIN01_ENABLE,          // 3
  BSP_DOUT_DIN02_ENABLE,          // 4
  BSP_DOUT_DIN03_ENABLE,          // 5
  BSP_DOUT_DIN04_ENABLE,          // 6
  BSP_DOUT_HC_LSD1_CMD,           // 7
  BSP_DOUT_HC_LSD2_CMD,           // 8
  BSP_DOUT_HC_LSD3_CMD,           // 9
  BSP_DOUT_HC_LSD4_CMD,           // 10
  BSP_DOUT_HC_LSD5_CMD,           // 11
  BSP_DOUT_HC_LSD6_CMD,           // 12
  BSP_DOUT_HC_HSD1_CMD,           // 13
  BSP_DOUT_HC_HSD2_CMD,           // 14
  BSP_DOUT_HC_HSD3_CMD,           // 15
  BSP_DOUT_HC_HSD4_CMD,           // 16
  BSP_DOUT_HC_HSD5_CMD,           // 17
  BSP_DOUT_HC_HSD6_CMD,           // 18
  BSP_DOUT_HC_HSD7_CMD,           // 19
  BSP_DOUT_HC_HSD8_CMD,           // 10
  BSP_DOUT_LC_HSD1_CMD,           // 21
  BSP_DOUT_LC_HSD2_CMD,           // 22
  BSP_DOUT_LC_HSD3_CMD,           // 23
  BSP_DOUT_LC_HSD4_CMD,           // 24
  BSP_DOUT_LC_HSD5_CMD,           // 25
  BSP_DOUT_LC_HSD6_CMD,           // 26
  BSP_DOUT_LC_HSD7_CMD,           // 27
  BSP_DOUT_LC_HSD8_CMD,           // 28
  BSP_DOUT_WC_ON1,                // 29
  BSP_DOUT_WC_ON2,                // 30
  BSP_DOUT_WC_ON3,                // 31
  BSP_DOUT_WC_ON4,                // 32
  BSP_DOUT_WC_ON5,                // 33
  BSP_DOUT_WC_ON6,                // 34
  BSP_DOUT_WC_ON7,                // 35
  BSP_DOUT_WC_ON8,                // 36
  BSP_DOUT_WC_CONFIG1,            // 37
  BSP_DOUT_WC_CONFIG2,            // 38
  BSP_DOUT_WC_CONFIG3,            // 39
  BSP_DOUT_WC_CONFIG4,            // 40
  BSP_DOUT_DEBUG1,                // 41
  BSP_DOUT_DEBUG2                 // 42
} bsp_dout_t;

typedef enum bsp_fin_e
{
  BSP_FIN_1 = 0,                  // 0
  BSP_FIN_2,                      // 1
  BSP_FIN_3,                      // 2
  BSP_FIN_4                       // 3
} bsp_fin_t;

typedef enum bsp_nvm_e
{
  BSP_NVM_1 = 0,                  // 0
  BSP_NVM_2,                      // 1
} bsp_nvm_t;

typedef enum bsp_pwm_e
{
  BSP_PWM_HC_HSD1 = 0,            // 0
  BSP_PWM_HC_HSD2,                // 1
  BSP_PWM_HC_HSD3,                // 2
  BSP_PWM_HC_HSD4,                // 3
  BSP_PWM_HC_HSD5,                // 4
  BSP_PWM_HC_HSD6,                // 5
  BSP_PWM_HC_HSD7,                // 6
  BSP_PWM_HC_HSD8,                // 7
  BSP_PWM_LC_HSD1,                // 8
  BSP_PWM_LC_HSD2,                // 9
  BSP_PWM_LC_HSD3,                // 10
  BSP_PWM_LC_HSD4,                // 11
  BSP_PWM_LC_HSD5,                // 12
  BSP_PWM_LC_HSD6,                // 13
  BSP_PWM_LC_HSD7,                // 14
  BSP_PWM_LC_HSD8,                // 15
  BSP_PWM_LC_LSD1                 // 16
} bsp_pwm_t;

#define BSP_ROM_MASK_BOOTBLOCK  (0x00000003)
#define BSP_ROM_MASK_ECUID      (0x00000004)


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BSP_TYPES_H */

