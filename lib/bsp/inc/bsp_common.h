//******************************************************************************
/**
 * \file    bsp_common.h
 * \author  Chad Swenson
 * \date    August 2013
 * \brief   BSP Common Header
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
#ifndef BSP_COMMON_H
#define BSP_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include "ap_bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BSP_DEBUG
# define BSP_DEBUG(a)         ((void)0)
#endif

/// Compile Time Assertion Macro
#define BSP_CTA(x)         extern uint8_t bsp_cta_a[(x) ? 1 : -1]

/// Number of elements in an array
#define BSP_ARRAY_LEN(a)   ((uint32_t)(sizeof(a) / sizeof(a[0])))


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BSP_COMMON_H */

