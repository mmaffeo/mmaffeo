//******************************************************************************
/**
 * \file    bsp_sdata.h
 * \author  Chad Swenson
 * \date    July 2013
 * \brief   Hardware Saved Data Header
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
#ifndef BSP_SDATA_H
#define BSP_SDATA_H

#include <stdint.h>
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum bsp_sdata_bbmode_e
{
  BSPSD_BB_MODE_NA = 0,
  BSPSD_BB_MODE_JUMP_TO_AP,
  BSPSD_BB_MODE_CAPTURED
} bsp_sdata_bbmode_t;

typedef struct bsp_sdata_progParams_s
{
  uint8_t protocolID;
  uint8_t protocolOptions;
  uint8_t customerID;
  uint8_t dataSizeMax;
} bsp_sdata_progParams_t;


//******************************************************************************
/**
 * Initialize hardware Saved Data module
 *
 * \return void
 *******************************************************************************/
void bsp_sdata_init(void);

//******************************************************************************
/**
 *
 *
 * \param mode
 *
 * \return void
 *******************************************************************************/
void bsp_sdata_setAppMode(uint8_t mode);

//******************************************************************************
/**
 *
 *
 * \return uint8_t
 *******************************************************************************/
uint8_t bsp_sdata_getAppMode(void);

//******************************************************************************
/**
 *
 *
 * \param mode
 *
 * \return void
 *******************************************************************************/
void bsp_sdata_setBootBlockMode(bsp_sdata_bbmode_t mode);

//******************************************************************************
/**
 *
 *
 * \return bsp_sdata_bbmode_t
 *******************************************************************************/
bsp_sdata_bbmode_t bsp_sdata_getBootBlockMode(void);

//******************************************************************************
/**
 *
 *
 * \param params
 *
 * \return void
 *******************************************************************************/
void bsp_sdata_setBBProgParams(bsp_sdata_progParams_t const * params);

//******************************************************************************
/**
 *
 *
 * \param params
 *
 * \return void
 *******************************************************************************/
void bsp_sdata_getBBProgParams(bsp_sdata_progParams_t * params);

//******************************************************************************
/**
 *
 *
 * \param port
 * \param disable
 *
 * \return void
 *******************************************************************************/
void bsp_sdata_setCanTermDisable(uint8_t port, bool disable);

//******************************************************************************
/**
 *
 *
 * \param port
 *
 * \return bool
 *******************************************************************************/
bool bsp_sdata_getCanTermDisable(uint8_t port);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BSP_SDATA_H */

