//******************************************************************************
/**
 * \file    bsp_ecuid.h
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   Hardware ECU ID Header
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
#ifndef BSP_ECUID_H
#define BSP_ECUID_H

#include <stdint.h>
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct bsp_ecuid_s
{
  uint8_t j1939_source_address;
  uint8_t bobcat_module_id;
  uint32_t ap_sw_code_smask;
  uint32_t ap_sw_const_smask;
} bsp_ecuid_t;

extern bsp_ecuid_t const * const bsp_ecuid;

//******************************************************************************
/**
 * Initialize ECUID module
 *
 * \return void
 *******************************************************************************/
void bsp_ecuid_init(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BSP_ECUID_H */

