//******************************************************************************
/**
 * \file    stf4_timer.h
 * \author  Chad Swenson
 * \date    May 2014
 * \brief   STM32F4xx Timer Helper functions
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
#ifndef STF4_TIMER_H
#define STF4_TIMER_H

#include <stdint.h>
#include <stdbool.h>

#ifndef STF4_INTERNAL
#error "This file for internal stf4 use only"
#endif

#include "stm32f4xx_tim.h"

void stf4_timer_init(void);

uint32_t stf4_timer_getClockFreq(TIM_TypeDef * timer);

uint32_t stf4_timer_getFreq(TIM_TypeDef * timer);

uint32_t stf4_timer_getPeriod(TIM_TypeDef * timer);

uint32_t stf4_timer_setFreq16(TIM_TypeDef * timer, uint16_t frequency);

bool stf4_timer_isAPB2Timer(TIM_TypeDef * timer);

void stf4_timer_clockCmd(TIM_TypeDef * timer, uint32_t RCC_APB1Periph, FunctionalState NewState);

#endif /* STF4_TIMER_H */

