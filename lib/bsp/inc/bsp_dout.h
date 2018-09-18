//******************************************************************************
/**
 * \file    bsp_dout.h
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   Digital Output header
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
#ifndef BSP_DOUT_H
#define BSP_DOUT_H

#include <stdint.h>
#include <stdbool.h>
#include "bsp_types.h"
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif


//******************************************************************************
/**
 * Initialize hardware Digital  Output module
 *
 * \return void
 *******************************************************************************/
void bsp_dout_init(void);

//******************************************************************************
/**
 * Initialize and enable the specified Digital Output
 *
 * \param ch
 * \param value
 *
 * \return void
 *******************************************************************************/
void bsp_dout_initCh(bsp_dout_t ch, bool value);

//******************************************************************************
/**
 * Deinitialize and disable the specified Digital Output
 *
 * \param ch
 *
 * \return void
 *******************************************************************************/
void bsp_dout_deinitCh(bsp_dout_t ch);

//******************************************************************************
/**
 * Get the value of a Digital Outut
 *
 * \param ch
 *
 * \return bool
 *******************************************************************************/
bool bsp_dout_GetValue(bsp_dout_t ch);

//******************************************************************************
/**
 * Set the value of a Digital Outut
 *
 * \param ch
 * \param value
 *
 * \return void
 *******************************************************************************/
void bsp_dout_SetValue(bsp_dout_t ch, bool value);

//******************************************************************************
/**
 * Enable the specified channel to generate wetting current pulses
 *
 * \param ch
 * \param enable
 *
 * \return void
 *******************************************************************************/
void bsp_dout_wettingCurrentEnable(bsp_dout_t ch, bool enable);

//******************************************************************************
/**
 *
 *
 * \param ch
 *
 * \return bool
 *******************************************************************************/
bool bsp_dout_getWettingCurrentEnable(bsp_dout_t ch);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* BSP_DOUT_H */

