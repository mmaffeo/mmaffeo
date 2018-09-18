//******************************************************************************
/**
 * \file    stf4_bsp_clock.c
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   STM32F4xx Specific Hardware Clock Source
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

#define STF4_INTERNAL (1)
#include "stf4_bsp_clock.h"
#include "stf4_vectors.h"
#include "stm32f4xx.h"
#undef STF4_INTERNAL


//******************************************************************************
// Defines
//******************************************************************************
#define BSP_CLOCK_CORE_CLOCK_FREQ      (168000000ul)
#define BSP_CLOCK_CLOCKS_PER_US        (BSP_CLOCK_CORE_CLOCK_FREQ / 1000000ul)

#define BSP_CLOCK_SYS_TICK_RELOAD      (BSP_CLOCK_CORE_CLOCK_FREQ / 1000)


//******************************************************************************
// Static Variables
//******************************************************************************
static volatile uint32_t msCounter = 0;
static volatile uint32_t usCounter = 0;
static volatile uint32_t sCounter = 0;


//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void isr_sysTick(void);


//******************************************************************************
// Inline Function Definitions
//******************************************************************************

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static inline void updateCounts(void)
{
  static uint32_t lastTimerCounts = BSP_CLOCK_SYS_TICK_RELOAD;
  static uint32_t usTimer = 0;
  uint32_t timerCounts = SysTick->VAL;
  uint32_t timerDelta = lastTimerCounts;

  // Check for underflow
  timerDelta += (lastTimerCounts <= timerCounts) ? (BSP_CLOCK_SYS_TICK_RELOAD + 1) : 0;

  // Calc delta
  timerDelta -= timerCounts;

  // Update us Counter
  usTimer += timerDelta;
  usCounter += usTimer / BSP_CLOCK_CLOCKS_PER_US;
  usTimer %= BSP_CLOCK_CLOCKS_PER_US;

  lastTimerCounts = timerCounts;
}


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_clock_init(void)
{
  vectors_setRamVector(SysTick_IRQn, isr_sysTick);

  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
  SysTick->VAL = 0;

  SysTick_Config(BSP_CLOCK_SYS_TICK_RELOAD);
}

//******************************************************************************
uint32_t bsp_clock_s(void)
{
  return sCounter;
}

//******************************************************************************
uint32_t bsp_clock_ms(void)
{
  return msCounter;
}

//******************************************************************************
uint32_t bsp_clock_us(void)
{
  SysTick->CTRL &= ~(uint32_t)SysTick_CTRL_TICKINT_Msk;
  updateCounts();
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

  return usCounter;
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
static void isr_sysTick(void)
{
  static uint32_t sTimer = 1000;    // 1000ms per second

  // Call updateCounts at least once every SysTick period
  updateCounts();

  msCounter++;

  if (--sTimer == 0)
  {
    sTimer = 1000;
    sCounter++;
  }
}


