//******************************************************************************
/**
 * \file    hw_pwm.cpp
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Emulation of hw_pwm on BSP
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
#include "hw_pwm.h"
#include <stdint.h>

#include "bsp_pwm.h"
#include "bsp_common.h"


//******************************************************************************
// Static Variables
//******************************************************************************

static bsp_pwm_t const bsp_pwmMap[] =
{
  BSP_PWM_HC_HSD2, // HWC_PWM_HC_HSD2
  BSP_PWM_HC_HSD4, // HWC_PWM_HC_HSD4
  BSP_PWM_HC_HSD6, // HWC_PWM_HC_HSD6
  BSP_PWM_HC_HSD8, // HWC_PWM_HC_HSD8
  BSP_PWM_LC_LSD1, // HWC_PWM_LC_LSD1
  BSP_PWM_HC_HSD1, // HWC_PWM_HC_HSD1
  BSP_PWM_HC_HSD3, // HWC_PWM_HC_HSD3
  BSP_PWM_HC_HSD5, // HWC_PWM_HC_HSD5
  BSP_PWM_HC_HSD7, // HWC_PWM_HC_HSD7
};


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
uint16_t hw_pwm_GetRatio16(hw_pwm_ch_t ch)
{
  uint16_t rvalue = 0;

  if (ch < BSP_ARRAY_LEN(bsp_pwmMap))
  {
    rvalue = bsp_pwm_GetRatio(bsp_pwmMap[ch]);
  }

  return rvalue;
}

//******************************************************************************
void hw_pwm_SetRatio16(hw_pwm_ch_t ch, uint16_t ratio)
{
  if (ch < BSP_ARRAY_LEN(bsp_pwmMap))
  {
    bsp_pwm_SetRatio(bsp_pwmMap[ch], ratio);
  }
}

//******************************************************************************
void hw_pwm_SetFrequency(hw_pwm_ch_t ch, uint16_t frequency)
{
  if (ch < BSP_ARRAY_LEN(bsp_pwmMap))
  {
    bsp_pwm_SetFrequency(bsp_pwmMap[ch], frequency);
  }
}

//******************************************************************************
uint16_t hw_pwm_GetFrequency(hw_pwm_ch_t ch)
{
  uint16_t rvalue = 0;

  if (ch < BSP_ARRAY_LEN(bsp_pwmMap))
  {
    rvalue = bsp_pwm_GetFrequency(bsp_pwmMap[ch]);
  }

  return rvalue;
}

//******************************************************************************
void hw_pwm_initialize(void)
{

}

//******************************************************************************
void hw_pwm_update(void)
{

}


