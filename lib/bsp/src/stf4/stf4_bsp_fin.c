//******************************************************************************
/**
 * \file    stf4_bsp_fin.c
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   STM32F4xx Specific Frequency Input Source
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
#include "stf4_bsp_fin.h"
#include "stf4_timer.h"
#include "stm32f4xx.h"
#include "stf4_vectors.h"
#undef STF4_INTERNAL


#if 0
# warning "FIN Debug code enabled!"
# include "bsp_dout.h"
# define FIN_DEBUG_INIT()    do{ bsp_dout_initCh(BSP_DOUT_DEBUG1, false);   \
                                 bsp_dout_initCh(BSP_DOUT_DEBUG2, false);   }while(0)
# define FIN_DEBUG1_HIGH()   do{ bsp_dout_SetValue(BSP_DOUT_DEBUG1, true);  }while(0)
# define FIN_DEBUG1_LOW()    do{ bsp_dout_SetValue(BSP_DOUT_DEBUG1, false); }while(0)
# define FIN_DEBUG2_HIGH()   do{ bsp_dout_SetValue(BSP_DOUT_DEBUG2, true);  }while(0)
# define FIN_DEBUG2_LOW()    do{ bsp_dout_SetValue(BSP_DOUT_DEBUG2, false); }while(0)
#else
# define FIN_DEBUG_INIT()    ((void)0)   ///< Initialize ROM debug output
# define FIN_DEBUG1_HIGH()   ((void)0)   ///< Set ROM debug 1 output high
# define FIN_DEBUG1_LOW()    ((void)0)   ///< Set ROM debug 1 output low
# define FIN_DEBUG2_HIGH()   ((void)0)   ///< Set ROM debug 2 output high
# define FIN_DEBUG2_LOW()    ((void)0)   ///< Set ROM debug 2 output low
#endif



#define COUNTS_DEFAULT        (0xFFFFFFFF)

#define FIN_CAPTURE_FILTER    (4)

#define FIN_NUM_SAMPLES       (8)
#define FIN_SAMPLE_MASK       (FIN_NUM_SAMPLES - 1)

#define FIN_FREQ_MIN          (1)
#define FIN_FREQ_MAX          (12000)


typedef struct fin_pinConfig_s
{
  uint32_t portClock;
  GPIO_TypeDef *port;
  uint16_t pin;
  uint16_t pinSource;
  uint8_t altFunc;
} fin_pinConfig_t;

typedef struct fin_timerConfig_s
{
  uint32_t clock;
  TIM_TypeDef * timer;
  uint16_t channel;
  uint16_t captureFlag;
  uint16_t overCaptureFlag;
  __IO uint32_t const * captureReg;
} fin_timerConfig_t;

typedef struct fin_config_s
{
  fin_pinConfig_t pin;
  fin_timerConfig_t timer;
} fin_config_t;

typedef struct fin_data_s
{
  uint32_t period[FIN_NUM_SAMPLES];
  uint32_t periodNext;
  uint32_t periodMin;
  uint32_t periodMax;
  uint32_t pulseCount;

  uint32_t timerFreq;
  uint32_t countLimitLow;
  uint32_t countLimitHigh;

  uint16_t lastTimerSample;
} fin_data_t;

typedef struct fin_sampelTimerConfig_s
{
  uint32_t clock;
  TIM_TypeDef * timer;
  uint32_t sampleFrequency;
  IRQn_Type irq;
} fin_sampelTimerConfig_t;

//******************************************************************************
// Static Function Prototypes
//******************************************************************************

static void initSampleTimer(void);
static void initTimer(fin_timerConfig_t const * timer);
static void initGPIO(fin_pinConfig_t const * pin);

static void isr_sampleTimer(void);

//******************************************************************************
// Static Variables
//******************************************************************************

static fin_config_t const fin_config[] =
{
  {// FIN1
    { RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_13, GPIO_PinSource13, GPIO_AF_TIM4 },
    { RCC_APB1Periph_TIM4, TIM4, TIM_Channel_2, TIM_FLAG_CC2, TIM_FLAG_CC2OF, &TIM4->CCR2 }
  },
  {// LC_LSD1-FIN2
    { RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_6, GPIO_PinSource6, GPIO_AF_TIM3 },
    { RCC_APB1Periph_TIM3, TIM3, TIM_Channel_1, TIM_FLAG_CC1, TIM_FLAG_CC1OF, &TIM3->CCR1 }
  },
  {// DIN11-FIN3
    { RCC_AHB1Periph_GPIOC, GPIOC, GPIO_Pin_7, GPIO_PinSource7, GPIO_AF_TIM3 },
    { RCC_APB1Periph_TIM3, TIM3, TIM_Channel_2, TIM_FLAG_CC2, TIM_FLAG_CC2OF, &TIM3->CCR2 }
  },
  {// DIN12-FIN4
    { RCC_AHB1Periph_GPIOD, GPIOD, GPIO_Pin_12, GPIO_PinSource12, GPIO_AF_TIM4 },
    { RCC_APB1Periph_TIM4, TIM4, TIM_Channel_1, TIM_FLAG_CC1, TIM_FLAG_CC1OF, &TIM4->CCR1 }
  },
};

static fin_sampelTimerConfig_t const sampelTimerConfig =
{
  RCC_APB1Periph_TIM6,
  TIM6,
  FIN_FREQ_MAX,
  TIM6_DAC_IRQn
};

static fin_data_t fin_data[BSP_ARRAY_LEN(fin_config)];


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_fin_init(void)
{
  FIN_DEBUG_INIT();

  initSampleTimer();
}

//******************************************************************************
void bsp_fin_initCh(bsp_fin_t ch)
{
  uint_fast16_t i;

  if ((uint32_t)ch < BSP_ARRAY_LEN(fin_config))
  {
    NVIC_DisableIRQ(sampelTimerConfig.irq);

    initGPIO(&fin_config[ch].pin);

    for (i = 0; i < FIN_NUM_SAMPLES; i++)
    {
      fin_data[ch].period[i] = COUNTS_DEFAULT;
    }

    fin_data[ch].periodNext = 0;
    fin_data[ch].periodMin = COUNTS_DEFAULT;
    fin_data[ch].periodMax = 0;

    fin_data[ch].pulseCount = 0;
    fin_data[ch].lastTimerSample = 0;

    fin_data[ch].timerFreq = stf4_timer_getClockFreq(fin_config[ch].timer.timer);

    fin_data[ch].countLimitLow = fin_data[ch].timerFreq;
    fin_data[ch].countLimitLow /= sampelTimerConfig.sampleFrequency;

    fin_data[ch].countLimitHigh = fin_data[ch].timerFreq;
    fin_data[ch].countLimitHigh /= FIN_FREQ_MIN;

    initTimer(&fin_config[ch].timer);

    NVIC_EnableIRQ(sampelTimerConfig.irq);
  }
}

//******************************************************************************
uint32_t bsp_fin_GetPeriodCount(bsp_fin_t ch)
{
  uint32_t counts = 0;

  if ((uint32_t)ch < BSP_ARRAY_LEN(fin_config))
  {
    uint32_t index;
    uint32_t periodNext;

    NVIC_DisableIRQ(sampelTimerConfig.irq);
    index = fin_data[ch].pulseCount & FIN_SAMPLE_MASK;
    counts = fin_data[ch].period[index];
    periodNext = fin_data[ch].periodNext;
    NVIC_EnableIRQ(sampelTimerConfig.irq);

    if ((periodNext > fin_data[ch].countLimitHigh)
        || (counts > fin_data[ch].countLimitHigh))
    {
      counts = COUNTS_DEFAULT;
    }
    else if (counts < fin_data[ch].countLimitLow)
    {
      counts = fin_data[ch].countLimitLow;
    }
  }

  return counts;
}

//******************************************************************************
uint32_t bsp_fin_GetPerioduS(bsp_fin_t ch)
{
  uint64_t uSecs = 0;

  if ((uint32_t)ch < BSP_ARRAY_LEN(fin_config))
  {
    uint32_t timerFreq_kHz = fin_data[ch].timerFreq / 1000;

    if (timerFreq_kHz)
    {
      uSecs = bsp_fin_GetPeriodCount(ch);

      if (uSecs != COUNTS_DEFAULT )
      {
        uSecs *= 1000;
        uSecs += (timerFreq_kHz / 2);
        uSecs /= timerFreq_kHz;
      }
    }
  }

  return (uint32_t)uSecs;
}

//******************************************************************************
uint32_t bsp_fin_GetFrequency(bsp_fin_t ch)
{
  uint32_t freq = 0;

  if ((uint32_t)ch < BSP_ARRAY_LEN(fin_config))
  {
    uint32_t counts = bsp_fin_GetPeriodCount(ch);

    if (counts)
    {
      freq = fin_data[ch].timerFreq;
      freq += counts / 2;  // Add half of counts for rounding
      freq /= counts;
    }
  }

  return freq;
}

//******************************************************************************
uint32_t bsp_fin_GetCountsPerSecond(bsp_fin_t ch)
{
  uint32_t timerFreq = 0;

  if (ch < BSP_ARRAY_LEN(fin_config))
  {
    timerFreq = fin_data[ch].timerFreq;
  }

  return timerFreq;
}

//******************************************************************************
// Static Function Definitions
//******************************************************************************


//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void initSampleTimer(void)
{
  TIM_TypeDef * timer = sampelTimerConfig.timer;
  //TIM_ICInitTypeDef TIM_ICInitStructure;
  uint32_t samplePeriod;

  stf4_timer_clockCmd(timer, sampelTimerConfig.clock, ENABLE);

  samplePeriod = stf4_timer_getClockFreq(sampelTimerConfig.timer);
  samplePeriod /= sampelTimerConfig.sampleFrequency;
  samplePeriod -= 1;

  // Set Timer Period
  timer->ARR = samplePeriod;
  // Set Timer Prescaler
  timer->PSC = 0;
  // Force Timer update
  timer->EGR = TIM_PSCReloadMode_Immediate;

  // Enable Timer Update Interrupt
  TIM_ITConfig(timer, TIM_IT_Update, ENABLE);

  // Setup NVIC for Timer Interrupt
  vectors_setRamVector(sampelTimerConfig.irq, isr_sampleTimer);
  NVIC_EnableIRQ(sampelTimerConfig.irq);

  // Start the Timer
  timer->CR1 |= TIM_CR1_CEN;
}

//******************************************************************************
/**
 *
 *
 * \param config
 *
 * \return void
 *******************************************************************************/
static void initTimer(fin_timerConfig_t const * config)
{
  TIM_ICInitTypeDef TIM_ICInitStructure;

  stf4_timer_clockCmd(config->timer, config->clock, ENABLE);

  // Init Input Capture module
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel = config->channel;
  TIM_ICInitStructure.TIM_ICFilter = FIN_CAPTURE_FILTER;
  TIM_ICInit(config->timer, &TIM_ICInitStructure);

  // Set Timer Period
  config->timer->ARR = 0xFFFF;

  // Set Timer Prescaler
  config->timer->PSC = 0;

  // Force Timer update
  config->timer->EGR = TIM_PSCReloadMode_Immediate;

  /* Enable the CC Interrupt Request */
  TIM_ITConfig(config->timer, config->captureFlag, ENABLE);

  // Start the Timers
  config->timer->CR1 |= TIM_CR1_CEN;

  // Clear Capture and Over Capture flags
  config->timer->SR &= ~(config->overCaptureFlag | config->captureFlag);
}

//******************************************************************************
/**
 *
 *
 * \param config
 *
 * \return void
 *******************************************************************************/
void initGPIO(fin_pinConfig_t const * config)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(config->portClock, ENABLE);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = config->pin;

  GPIO_PinAFConfig(config->port,
                   config->pinSource,
                   config->altFunc);

  GPIO_Init(config->port, &GPIO_InitStructure);
}


//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void isr_sampleTimer(void)
{
  uint32_t i;

  FIN_DEBUG1_HIGH();

  for (i = 0; i < BSP_ARRAY_LEN(fin_config); i++)
  {
    fin_config_t const *config = &fin_config[i];
    fin_data_t * data = &fin_data[i];
    TIM_TypeDef * timer = config->timer.timer;
    uint16_t delta = 0;
    bool captured = false;
    uint16_t timerSample = timer->CNT;

    // This flag must be read after sampling the timer
    if (timer->SR & config->timer.captureFlag)
    {
      // Last delta uses captured timer value
      timerSample = (uint16_t)*(config->timer.captureReg);
      captured = true;
    }

    delta = timerSample;
    delta -= data->lastTimerSample;

    if (data->periodNext < (0xFFFFFFFF - delta))
    {
      data->periodNext += delta;
    }
    else
    {
      data->periodNext = 0xFFFFFFFF;
    }

    if (timer->SR & config->timer.overCaptureFlag)
    {
      // Over Sample detected, clear Over Capture Flag and set a low period
      timer->SR &= ~config->timer.overCaptureFlag;
      data->periodNext = data->countLimitLow;
      captured = true;
    }

    if (captured)
    {
      if ((data->periodNext < data->periodMin) && (data->pulseCount))
      {
        data->periodMin = data->periodNext;
      }

      if ((data->periodNext > data->periodMax) && (data->pulseCount))
      {
        data->periodMax = data->periodNext;
      }

      data->pulseCount++;
      data->period[data->pulseCount & FIN_SAMPLE_MASK] = data->periodNext;
      data->periodNext = 0;
    }

    data->lastTimerSample = timerSample;
  }

  // Clear Update Interrupt Flag
  sampelTimerConfig.timer->SR = (uint16_t)~TIM_IT_Update;

  FIN_DEBUG1_LOW();
}

