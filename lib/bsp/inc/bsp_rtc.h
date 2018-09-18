//******************************************************************************
/**
 * \file    bsp_rtc.h
 * \author  Chad Swenson
 * \date    September 2014
 * \brief   Real Time Clock header
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
#ifndef BSP_RTC_H
#define BSP_RTC_H

#include <stdint.h>
#include <stdbool.h>
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

//******************************************************************************
/**
 * Initialize hardware Real Time Clock module
 *
 * \return void
 *******************************************************************************/
void bsp_rtc_init(void);

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
void bsp_rtc_run(void);

//******************************************************************************
/**
 *
 *
 * \param time
 *
 * \return void
 *******************************************************************************/
void bsp_rtc_set(uint32_t time);

//******************************************************************************
/**
 *
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_rtc_get(void);

//******************************************************************************
/**
 *
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_rtc_getDownTime(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* BSP_RTC_H */

