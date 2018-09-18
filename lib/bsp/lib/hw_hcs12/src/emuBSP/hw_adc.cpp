//******************************************************************************
/**
 * \file    hw_adc.cpp
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Emulation of hw_adc on BSP
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
#include "hw_adc.h"
#include <stdint.h>

#include "bsp_adc.h"
#include "bsp_common.h"

#define HWC_ADC_PRECISION_REF_CONST   (512 << 6)

//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
uint16_t hw_adc_GetValue(hw_adc_ch_t ch)
{
  uint16_t adcValue = 0;

  switch (ch)
  {
  case HWC_ADC_PRECISION_REF:
    adcValue = HWC_ADC_PRECISION_REF_CONST;
    break;
  case HWC_ADC_BATT_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_VBAT_AFBK_V);
    break;
  case HWC_ADC_SW_BATT_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_VSW_AFBK_V);
    break;
  case HWC_ADC_VSENSOR1_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_VSENSOR1_AFBK);
    break;
  case HWC_ADC_AIN08_VSENSOR2:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN08);
    break;
  case HWC_ADC_AIN11_LC_LSD1_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN11);
    break;
  case HWC_ADC_HC_LSD1_IFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_LSD1_IFBK);
    break;
  case HWC_ADC_HC_LSD2_IFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_LSD2_IFBK);
    break;
  case HWC_ADC_HC_LSD3_IFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_LSD3_IFBK);
    break;
  case HWC_ADC_HC_LSD4_IFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_LSD4_IFBK);
    break;
  case HWC_ADC_AIN01_DIN01:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN01);
    break;
  case HWC_ADC_AIN02_DIN02:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN02);
    break;
  case HWC_ADC_AIN03_DIN03:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN03);
    break;
  case HWC_ADC_AIN04_DIN04:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN04);
    break;
  case HWC_ADC_AIN05:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN05);
    break;
  case HWC_ADC_AIN06:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN06);
    break;
  case HWC_ADC_AIN07:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN07);
    break;
  case HWC_ADC_FIN1_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_FIN01_AFBK);
    break;
  case HWC_ADC_AIN09:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN09);
    break;
  case HWC_ADC_AIN10:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN10);
    break;
  case HWC_ADC_HC_HSD1_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_HSD1_AFBK);
    break;
  case HWC_ADC_HC_HSD2_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_HSD2_AFBK);
    break;
  case HWC_ADC_HC_HSD3_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_HSD3_AFBK);
    break;
  case HWC_ADC_HC_HSD4_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_HSD4_AFBK);
    break;
  case HWC_ADC_HC_HSD5_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_HSD5_AFBK);
    break;
  case HWC_ADC_HC_HSD6_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_HSD6_AFBK);
    break;
  case HWC_ADC_HC_HSD7_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_HSD7_AFBK);
    break;
  case HWC_ADC_HC_HSD8_AFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_HSD8_AFBK);
    break;
  case HWC_ADC_HC_LSD5_IFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_LSD5_IFBK);
    break;
  case HWC_ADC_HC_LSD6_IFBK:
    adcValue = bsp_adc_GetValue(BSP_ADC_HC_LSD6_IFBK);
    break;
  case HWC_ADC_AIN12:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN12);
    break;
  case HWC_ADC_AIN13:
    adcValue = bsp_adc_GetValue(BSP_ADC_AIN13);
    break;
  case HWC_ADC_HC_LSD5_AFBK:
    adcValue = 0;
    break;
  case HWC_ADC_HC_LSD6_AFBK:
    adcValue = 0;
    break;
  default:
    break;
  }


  // Convert from 16bit to 10bit
  adcValue >>= 6;

  return adcValue;
}

//******************************************************************************
void hw_adc_initialize(void)
{

}

//******************************************************************************
void hw_adc_update(void)
{

}


