//******************************************************************************
/**
 * \file    bsp_adc.h
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   Analog to Digital Input header
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
#ifndef BSP_ADC_H
#define BSP_ADC_H

#include <stdint.h>
#include "bsp_types.h"
#include "bsp_common.h"


#ifdef __cplusplus
extern "C" {
#endif


//******************************************************************************
/**
 * Initialize hardware ADC module
 *
 * \return void
 *******************************************************************************/
void bsp_adc_init(void);

//******************************************************************************
/**
 * Initialize and enable the specified ADC Channel
 *
 * \param ch
 *
 * \return void
 *******************************************************************************/
void bsp_adc_initCh(bsp_adc_t ch);

//******************************************************************************
/**
 * Deinitialize and disable the specified ADC Channel
 *
 * \param ch
 *
 * \return void
 *******************************************************************************/
void bsp_adc_deinitCh(bsp_adc_t ch);

//******************************************************************************
/**
 * Get the most recent 10-bit A/D sample from this channel
 *
 * \param ch
 *
 * \return uint16_t
 *******************************************************************************/
uint16_t bsp_adc_GetValue(bsp_adc_t ch);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* BSP_ADC_H */

