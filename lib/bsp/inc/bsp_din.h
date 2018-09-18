//******************************************************************************
/**
 * \file    bsp_din.h
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   Digital Input header
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
#ifndef BSP_DIN_H
#define BSP_DIN_H

#include <stdint.h>
#include <stdbool.h>
#include "bsp_types.h"
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif


//******************************************************************************
/**
 * Initialize hardware Digital Input / Output module
 *
 * \return void
 *******************************************************************************/
void bsp_din_init(void);

//******************************************************************************
/**
 * Sample all digital inputs
 *
 * \note Called from ADC Timer interrupt
 *
 * \return void
 *******************************************************************************/
void bsp_din_sample(void);

//******************************************************************************
/**
 * Initialize and enable the specified Digital Input
 *
 * \param ch
 *
 * \return void
 *******************************************************************************/
void bsp_din_initCh(bsp_din_t ch);

//******************************************************************************
/**
 * Deinitialize and disable the specified Digital Input
 *
 * \param ch
 *
 * \return void
 *******************************************************************************/
void bsp_din_deinitCh(bsp_din_t ch);

//******************************************************************************
/**
 * Get the value of a Digital Input
 *
 * \param ch
 *
 * \return bool
 *******************************************************************************/
bool bsp_din_GetValue(bsp_din_t ch);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* BSP_DIN_H */

