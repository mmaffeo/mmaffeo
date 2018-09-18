//******************************************************************************
/**
 * \file    stf4_timer.c
 * \author  Chad Swenson
 * \date    May 2014
 * \brief   STM32F4xx Hardware Timer Source
 *
 * Copyright 2013 Bobcat Company as an unpublished work.
 * All Rights Reserved.
 *
 * The information contained herein is confidential
 * property of Bobcat Company. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Bobcat Company.
 *
 *******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

#include "bsp_common.h"

#define STF4_INTERNAL (1)
#include "stf4_timer.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "stf4_bsp_mcu.h"
#undef STF4_INTERNAL

typedef struct prescalerPoint_s
{
  uint32_t minFreq;
  uint32_t divisor;
} prescalerPoint_t;

#define STF4_TIM_MIN_FREQ       (1)

//******************************************************************************
// Static Variables
//******************************************************************************

// For each entry, (divisor / minFreq) and (timerClock / divisor) must each be less than 65536
static prescalerPoint_t const prescalerTable[] =
{// Min Freq  Divisor
  { 16,       1000000   },  //      If Freq >= 16, prescaler = clock / 1000000
  { 2,        100000    },  // Else If Freq >= 2,  prescaler = clock / 100000
  { 1,        10000     }   // Else If Freq >= 1,  prescaler = clock / 10000
};


//******************************************************************************
// Global Variables
//******************************************************************************


//******************************************************************************
// Static Function Prototypes
//******************************************************************************


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void stf4_timer_init(void)
{
  RCC_TIMCLKPresConfig(RCC_TIMPrescActivated);

}

//******************************************************************************
uint32_t stf4_timer_getClockFreq(TIM_TypeDef * timer)
{
  RCC_ClocksTypeDef stf4_sysClocks;
  uint32_t clockFreq = 0;

  RCC_GetClocksFreq(&stf4_sysClocks);

  if (stf4_timer_isAPB2Timer(timer))
  {
    clockFreq = stf4_sysClocks.PCLK2_Frequency;
    if ((RCC->CFGR & RCC_CFGR_PPRE2) != RCC_CFGR_PPRE2_DIV1)
    { // Timer clock is multiplied by two if PCLK Prescaler is not 1
      clockFreq *= 2;
    }
  }
  else
  {
    clockFreq = stf4_sysClocks.PCLK1_Frequency;

    if ((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1)
    { // Timer clock is multiplied by two if PCLK Prescaler is not 1
      clockFreq *= 2;
    }
  }

  return clockFreq;
}

//******************************************************************************
uint32_t stf4_timer_getFreq(TIM_TypeDef * timer)
{
  uint32_t freq = 0;

  uint32_t tempFreq = stf4_timer_getClockFreq(timer);
  uint32_t preScaler = (uint16_t)timer->PSC;

  preScaler += 1;

  if (tempFreq && preScaler)
  {
    freq = tempFreq;
    freq /= preScaler;
  }

  return freq;
}

//******************************************************************************
uint32_t stf4_timer_getPeriod(TIM_TypeDef * timer)
{
  return timer->ARR;
}

//******************************************************************************
uint32_t stf4_timer_setFreq16(TIM_TypeDef * timer, uint16_t frequency)
{
  uint32_t prescaler = 0xFFFF;
  uint32_t period = 0xFFFF;
  uint32_t timerClkFreq = stf4_timer_getClockFreq(timer);
  uint_fast16_t i;

  if (frequency < STF4_TIM_MIN_FREQ)
  {
    frequency = STF4_TIM_MIN_FREQ;
  }
  for (i = 0; i < BSP_ARRAY_LEN(prescalerTable); i++)
  {
    if (frequency >= prescalerTable[i].minFreq)
    {
      // f_pwm = f_clk / (prescaler * period)
      // period = f_clk / (f_pwm * prescaler)
      //  if:   prescaler = f_clk / divisor
      //  then: period = divisor / f_pwmv
      // Integer Math Rounding: period = (divisor + (0.5 * f_pwmv)) / f_pwmv

      prescaler = timerClkFreq / prescalerTable[i].divisor;
      period = (prescalerTable[i].divisor + (frequency >> 1)) / frequency;

      if (prescaler)
      {
        prescaler--;
      }

      if (period)
      {
        period--;
      }

      break;
    }
  }

  timer->ARR = period;
  timer->PSC = (uint16_t)prescaler;

  return period;
}

//******************************************************************************
bool stf4_timer_isAPB2Timer(TIM_TypeDef * timer)
{
  bool retVal;

  switch ((uintptr_t)timer)
  {
  case TIM1_BASE:
  case TIM8_BASE:
  case TIM9_BASE:
  case TIM10_BASE:
  case TIM11_BASE:
    // APB2/PCLK2 Clocked Timers
    retVal = true;
    break;

  default:
    retVal = false;
    break;
  }

  return retVal;
}

//******************************************************************************
void stf4_timer_clockCmd(TIM_TypeDef * timer, uint32_t RCC_APBPeriph, FunctionalState NewState)
{
  if (stf4_timer_isAPB2Timer(timer))
  {
    RCC_APB2PeriphClockCmd(RCC_APBPeriph, NewState);
  }
  else
  {
    RCC_APB1PeriphClockCmd(RCC_APBPeriph, NewState);
  }
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************



