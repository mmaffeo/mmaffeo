//******************************************************************************
/**
 * \file    bsp_clock.h
 * \author  aliebel, Chad Swenson
 * \date    June 2013
 * \brief   Hardware Clock Header
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
#ifndef BSP_CLOCK_H
#define BSP_CLOCK_H

#include <stdint.h>
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif


//******************************************************************************
/**
 * Initialize the Clock Hardware
 *
 * \return void
 *******************************************************************************/
void bsp_clock_init(void);

//******************************************************************************
/**
 * Free running counter that increments once every second.
 * Overflows after 0xFFFFFFFF -> 4294967296 seconds -> ~71582788 minutes
 *    -> ~1193046 hours -> 49710 days -> ~136 years
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_clock_s(void);

//******************************************************************************
/**
 * Free running counter that increments once every millisecond.
 * Overflows after 0xFFFFFFFF -> ~4294967 seconds -> ~71582.788 minutes
 *    -> ~1193.04 hours -> ~49.7 Days
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_clock_ms(void);

//******************************************************************************
/**
 * Free running counter that increments once every microsecond.
 * Overflows after 0xFFFFFFFF -> ~4294.967 seconds -> ~71.58 minutes
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_clock_us(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BSP_CLOCK_H */

