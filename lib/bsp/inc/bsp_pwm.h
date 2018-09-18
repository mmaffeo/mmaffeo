//******************************************************************************
/**
 * \file    bsp_pwm.h
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   Pulse Width Modulation header
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
#ifndef BSP_PWM_H
#define BSP_PWM_H

#include <stdint.h>
#include <stdbool.h>
#include "bsp_types.h"
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif


#define BSP_PWM_MIN_RATIO 0x0
#define BSP_PWM_MAX_RATIO 0xFFFFu


//******************************************************************************
/**
 * Initialize hardware Pulse Width Modulation module
 *
 * \return void
 *******************************************************************************/
void bsp_pwm_init(void);

//******************************************************************************
/**
 * Initialize and enable the specified PWM Channel
 *
 * \param ch
 * \param frequency
 * \param ratio
 *
 * \return void
 *******************************************************************************/
void bsp_pwm_initCh(bsp_pwm_t ch, uint16_t frequency, uint16_t ratio);

//******************************************************************************
/**
 * Deinitialize and disable the specified PWM Channel
 *
 * \param ch
 *
 * \return void
 *******************************************************************************/
void bsp_pwm_deinitCh(bsp_pwm_t ch);


//******************************************************************************
/**
 * Set duty cycle.  0 for off, 0xFFFF for 100% duty cycle
 *
 * \param ch
 * \param ratio
 *
 * \return void
 *******************************************************************************/
void bsp_pwm_SetRatio(bsp_pwm_t ch, uint16_t ratio);

//******************************************************************************
/**
 * Get Duty Cycle
 *
 * \param ch
 *
 * \return uint16_t
 *******************************************************************************/
uint16_t bsp_pwm_GetRatio(bsp_pwm_t ch);

//******************************************************************************
/**
 * Set the PWM frequency
 *
 * \param ch
 * \param frequency
 *
 * \return void
 *******************************************************************************/
void bsp_pwm_SetFrequency(bsp_pwm_t ch, uint16_t frequency);

//******************************************************************************
/**
 * Get the PWM frequency
 *
 * \param ch
 *
 * \return uint16_t
 *******************************************************************************/
uint16_t bsp_pwm_GetFrequency(bsp_pwm_t ch);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* BSP_PWM_H */

