//******************************************************************************
/**
 * \file    stf4_bsp_pwm.c
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   STM32F4xx Specific Pulse Width Modulation Source
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

#include "bsp_common.h"

#define STF4_INTERNAL (1)
#include "stf4_bsp_pwm.h"
#include "stf4_timer.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#undef STF4_INTERNAL


typedef enum pwm_timerChannel_e
{
  PWM_TIMER_CH1 = 0,
  PWM_TIMER_CH2,
  PWM_TIMER_CH3,
  PWM_TIMER_CH4
} pwm_timerChannel_t;

typedef struct pwm_config_s
{
  TIM_TypeDef * timer;
  pwm_timerChannel_t timerChannel;
  GPIO_TypeDef * port;
  uint16_t pinSource;
  uint8_t altFunction;
  uint32_t ahb1Clock;
} pwm_config_t;


//******************************************************************************
// Static Variables
//******************************************************************************

static uint32_t const pwm_apb1Clocks = RCC_APB1Periph_TIM2
                                     | RCC_APB1Periph_TIM3
                                     | RCC_APB1Periph_TIM5
                                     | RCC_APB1Periph_TIM12;

static uint32_t const pwm_apb2Clocks = RCC_APB2Periph_TIM1
                                     | RCC_APB2Periph_TIM8
                                     | RCC_APB2Periph_TIM10
                                     | RCC_APB2Periph_TIM11;

static TIM_TypeDef * const pwm_timer[] =
{
  TIM1,
  TIM2,
  TIM3,
  TIM5,
  TIM8,
  TIM10,
  TIM11,
  TIM12,
};

static pwm_config_t pwmConfig[] =
{// Timer   Ch              Port    Pin Source         GPIO AltFunc   ahb1Clock
  { TIM1,   PWM_TIMER_CH1,  GPIOE,  GPIO_PinSource9,   GPIO_AF_TIM1,  RCC_AHB1Periph_GPIOE  },   // HC_HSD1
  { TIM2,   PWM_TIMER_CH3,  GPIOB,  GPIO_PinSource10,  GPIO_AF_TIM2,  RCC_AHB1Periph_GPIOB  },   // HC_HSD2
  { TIM5,   PWM_TIMER_CH1,  GPIOH,  GPIO_PinSource10,  GPIO_AF_TIM5,  RCC_AHB1Periph_GPIOH  },   // HC_HSD3
  { TIM8,   PWM_TIMER_CH1,  GPIOI,  GPIO_PinSource5,   GPIO_AF_TIM8,  RCC_AHB1Periph_GPIOI  },   // HC_HSD4
  { TIM1,   PWM_TIMER_CH2,  GPIOE,  GPIO_PinSource11,  GPIO_AF_TIM1,  RCC_AHB1Periph_GPIOE  },   // HC_HSD5
  { TIM11,  PWM_TIMER_CH1,  GPIOB,  GPIO_PinSource9,   GPIO_AF_TIM11, RCC_AHB1Periph_GPIOB  },   // HC_HSD6
  { TIM12,  PWM_TIMER_CH1,  GPIOH,  GPIO_PinSource6,   GPIO_AF_TIM12, RCC_AHB1Periph_GPIOH  },   // HC_HSD7
  { TIM10,  PWM_TIMER_CH1,  GPIOB,  GPIO_PinSource8,   GPIO_AF_TIM10, RCC_AHB1Periph_GPIOB  },   // HC_HSD8

  { TIM2,   PWM_TIMER_CH4,  GPIOB,  GPIO_PinSource11,  GPIO_AF_TIM2,  RCC_AHB1Periph_GPIOB  },   // LC_HSD1
  { TIM3,   PWM_TIMER_CH3,  GPIOC,  GPIO_PinSource8,   GPIO_AF_TIM3,  RCC_AHB1Periph_GPIOC  },   // LC_HSD2
  { TIM3,   PWM_TIMER_CH4,  GPIOC,  GPIO_PinSource9,   GPIO_AF_TIM3,  RCC_AHB1Periph_GPIOC  },   // LC_HSD3
  { TIM1,   PWM_TIMER_CH3,  GPIOE,  GPIO_PinSource13,  GPIO_AF_TIM1,  RCC_AHB1Periph_GPIOE  },   // LC_HSD4
  { TIM1,   PWM_TIMER_CH4,  GPIOE,  GPIO_PinSource14,  GPIO_AF_TIM1,  RCC_AHB1Periph_GPIOE  },   // LC_HSD5
  { TIM12,  PWM_TIMER_CH2,  GPIOH,  GPIO_PinSource9,   GPIO_AF_TIM12, RCC_AHB1Periph_GPIOH  },   // LC_HSD6
  { TIM5,   PWM_TIMER_CH2,  GPIOH,  GPIO_PinSource11,  GPIO_AF_TIM5,  RCC_AHB1Periph_GPIOH  },   // LC_HSD7
  { TIM5,   PWM_TIMER_CH3,  GPIOH,  GPIO_PinSource12,  GPIO_AF_TIM5,  RCC_AHB1Periph_GPIOH  },   // LC_HSD8

  { TIM3,   PWM_TIMER_CH1,  GPIOC,  GPIO_PinSource6,   GPIO_AF_TIM3,  RCC_AHB1Periph_GPIOC  },   // LC_LSD1
};

static uint32_t timerCompare[BSP_ARRAY_LEN(pwmConfig)];
static uint32_t requestedRatio[BSP_ARRAY_LEN(pwmConfig)];

//******************************************************************************
// Global Variables
//******************************************************************************


//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void TIM_OCInit(pwm_timerChannel_t channel,
                       TIM_TypeDef* TIMx,
                       TIM_OCInitTypeDef* TIM_OCInitStruct);
static void TIM_SetCompare(pwm_timerChannel_t channel,
                           TIM_TypeDef* TIMx,
                           uint32_t Compare);
static void TIM_OCPreloadConfig(pwm_timerChannel_t channel,
                                TIM_TypeDef* TIMx,
                                uint16_t TIM_OCPreload);


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_pwm_init(void)
{
  uint_fast16_t i;

  for (i = 0; i < BSP_ARRAY_LEN(pwmConfig); i++)
  {
    timerCompare[i] = 0;
    requestedRatio[i] = 0;
  }

  RCC_APB1PeriphClockCmd(pwm_apb1Clocks, ENABLE);
  RCC_APB2PeriphClockCmd(pwm_apb2Clocks, ENABLE);

  for (i = 0; i < BSP_ARRAY_LEN(pwm_timer); i++)
  {
    // Init timer to 100 hz
    stf4_timer_setFreq16(pwm_timer[i],  100);

    // Force Initial Timer update
    pwm_timer[i]->EGR = TIM_PSCReloadMode_Immediate;

    // Buffer future timer reload changes
    TIM_ARRPreloadConfig(pwm_timer[i],  ENABLE);
  }

  for (i = 0; i < BSP_ARRAY_LEN(pwm_timer); i++)
  {
    // Start the Timers
    pwm_timer[i]->CR1 |= TIM_CR1_CEN;
  }
}

//******************************************************************************
void bsp_pwm_initCh(bsp_pwm_t ch, uint16_t frequency, uint16_t ratio)
{
  TIM_OCInitTypeDef TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  if ((uint32_t)ch < BSP_ARRAY_LEN(pwmConfig))
  {
    stf4_timer_setFreq16(pwmConfig[ch].timer, frequency);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OCInit(pwmConfig[ch].timerChannel, pwmConfig[ch].timer, &TIM_OCInitStructure);

    // Buffer future compare values
    TIM_OCPreloadConfig(pwmConfig[ch].timerChannel, pwmConfig[ch].timer, TIM_OCPreload_Enable);

    if ((pwmConfig[ch].timer == TIM1)
        || (pwmConfig[ch].timer == TIM8))
    {
      TIM_CtrlPWMOutputs(pwmConfig[ch].timer, ENABLE);
    }

    bsp_pwm_SetRatio(ch, ratio);


    /* Enable GPIO Clock */
    RCC_AHB1PeriphClockCmd(pwmConfig[ch].ahb1Clock, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0 << pwmConfig[ch].pinSource);

    GPIO_PinAFConfig(pwmConfig[ch].port,
                     pwmConfig[ch].pinSource,
                     pwmConfig[ch].altFunction);
    GPIO_Init(pwmConfig[ch].port, &GPIO_InitStructure);
  }

}

//******************************************************************************
void bsp_pwm_deinitCh(bsp_pwm_t ch)
{
  // TODO
}

//******************************************************************************
void bsp_pwm_SetRatio(bsp_pwm_t ch, uint16_t ratio)
{
  if ((uint32_t)ch < BSP_ARRAY_LEN(pwmConfig))
  {
    uint32_t compare = stf4_timer_getPeriod(pwmConfig[ch].timer);
    compare *= ratio;
    compare += (0xFFFF / 2);
    compare /= 0xFFFF;

    timerCompare[ch] = compare;

    TIM_SetCompare(pwmConfig[ch].timerChannel, pwmConfig[ch].timer, timerCompare[ch]);

    requestedRatio[ch] = ratio;
  }
}

//******************************************************************************
uint16_t bsp_pwm_GetRatio(bsp_pwm_t ch)
{
  uint32_t ratio = 0;

  if ((uint32_t)ch < BSP_ARRAY_LEN(pwmConfig))
  {
#if 1
    uint32_t period = stf4_timer_getPeriod(pwmConfig[ch].timer);

    if (period != 0)
    {
      ratio = 0xFFFF;
      ratio *= timerCompare[ch];
      ratio /= period;
    }
#else
    ratio = requestedRatio[ch];
#endif
  }

  return ratio;
}

//******************************************************************************
void bsp_pwm_SetFrequency(bsp_pwm_t ch, uint16_t frequency)
{
  if ((uint32_t)ch < BSP_ARRAY_LEN(pwmConfig))
  {
    uint_fast16_t i;

    // TODO compare value may need to be adjusted first
    stf4_timer_setFreq16(pwmConfig[ch].timer, frequency);

    // Update all ratios
    for (i = 0; i < BSP_ARRAY_LEN(pwmConfig); i++)
    {
      bsp_pwm_SetRatio((bsp_pwm_t)i, requestedRatio[i]);
    }
  }
}

//******************************************************************************
uint16_t bsp_pwm_GetFrequency(bsp_pwm_t ch)
{
  uint32_t freq = 0;

  if ((uint32_t)ch < BSP_ARRAY_LEN(pwmConfig))
  {
    uint32_t period = stf4_timer_getPeriod(pwmConfig[ch].timer);

    if (period != 0)
    {
      freq = stf4_timer_getFreq(pwmConfig[ch].timer);
#if 0
      freq += (period / 2);
#endif
      freq /= period;

      if (freq > 0xFFFF)
      {
        freq = 0xFFFF;
      }
    }
  }

  return (uint16_t)freq;
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************


static void TIM_OCInit(pwm_timerChannel_t channel,
                       TIM_TypeDef* TIMx,
                       TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  switch (channel)
  {
  case PWM_TIMER_CH1:
    TIM_OC1Init(TIMx, TIM_OCInitStruct);
    break;

  case PWM_TIMER_CH2:
    TIM_OC2Init(TIMx, TIM_OCInitStruct);
    break;

  case PWM_TIMER_CH3:
    TIM_OC3Init(TIMx, TIM_OCInitStruct);
    break;

  case PWM_TIMER_CH4:
    TIM_OC4Init(TIMx, TIM_OCInitStruct);
    break;

  default:
    break;
  }
}

static void TIM_SetCompare(pwm_timerChannel_t channel,
                           TIM_TypeDef* TIMx,
                           uint32_t Compare)
{
  switch (channel)
  {
  case PWM_TIMER_CH1:
    TIM_SetCompare1(TIMx, Compare);
    break;

  case PWM_TIMER_CH2:
    TIM_SetCompare2(TIMx, Compare);
    break;

  case PWM_TIMER_CH3:
    TIM_SetCompare3(TIMx, Compare);
    break;

  case PWM_TIMER_CH4:
    TIM_SetCompare4(TIMx, Compare);
    break;

  default:
    break;
  }
}

static void TIM_OCPreloadConfig(pwm_timerChannel_t channel,
                                TIM_TypeDef* TIMx,
                                uint16_t TIM_OCPreload)
{
  switch (channel)
  {
  case PWM_TIMER_CH1:
    TIM_OC1PreloadConfig(TIMx, TIM_OCPreload);
    break;

  case PWM_TIMER_CH2:
    TIM_OC2PreloadConfig(TIMx, TIM_OCPreload);
    break;

  case PWM_TIMER_CH3:
    TIM_OC3PreloadConfig(TIMx, TIM_OCPreload);
    break;

  case PWM_TIMER_CH4:
    TIM_OC4PreloadConfig(TIMx, TIM_OCPreload);
    break;

  default:
    break;
  }
}

