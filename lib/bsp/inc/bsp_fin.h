//******************************************************************************
/**
 * \file    bsp_fin.h
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   Frequency Input header
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
#ifndef BSP_FIN_H
#define BSP_FIN_H

#include <stdint.h>
#include "bsp_types.h"
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif


//******************************************************************************
/**
 * Initialize hardware Frequency Input module
 *
 * \return void
 *******************************************************************************/
void bsp_fin_init(void);

//******************************************************************************
/**
 * Initialize and enable the specified FIN Channel
 *
 * \param ch
 *
 * \return void
 *******************************************************************************/
void bsp_fin_initCh(bsp_fin_t ch);

//******************************************************************************
/**
 *
 * \param ch
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_fin_GetPeriodCount(bsp_fin_t ch);

//******************************************************************************
/**
 *
 *
 * \param ch
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_fin_GetPerioduS(bsp_fin_t ch);

//******************************************************************************
/**
 *
 *
 * \param ch
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_fin_GetFrequency(bsp_fin_t ch);

//******************************************************************************
/**
 *
 *
 * \param ch
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_fin_GetCountsPerSecond(bsp_fin_t ch);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* BSP_FIN_H */

