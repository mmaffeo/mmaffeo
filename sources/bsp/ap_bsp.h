//******************************************************************************
/**
 * \file    bsp.h
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   Hardware Interface Header
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
#ifndef AP_BSP_H
#define AP_BSP_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#if DEBUG == 1
# define BSP_DEBUG_PORT           (BSP_COM_2)
# define BSP_COM_2_TXBUFF_SIZE    (512)
#endif

//******************************************************************************
/**
 * Init BSP
 *
 * \return void
 *******************************************************************************/
void bsp_init(void);

//******************************************************************************
/**
 * Run BSP, call before each app run call
 *
 * \return void
 *******************************************************************************/
void bsp_run(void);

//******************************************************************************
/**
 * Check if the system is busy
 *
 * \return bool
 *******************************************************************************/
bool bsp_isSystemBusy(void);

//******************************************************************************
/**
 * Initialize BSP Task.  This function should be called by the application
 *  task scheduler.
 *
 * \return void
 *******************************************************************************/
void bsp_taskInit(void);

//******************************************************************************
/**
 * Run BSP Task.  This function should be called by the application task
 *  scheduler.
 *
 * \return void
 *******************************************************************************/
void bsp_taskRun(void);

//******************************************************************************
/**
 * Wait until this System Tick expires
 *
 * \return void
 *******************************************************************************/
void bsp_sleep(void);


#ifdef BSP_DEBUG_PORT
# define BSP_DEBUG(a)     do{ bsp_debug_printHeader(__FILE__, __LINE__); \
                              bsp_debug_printf a ; }while(0)
void bsp_debug_printHeader(char const *file, uint32_t line);
void bsp_debug_printf(char const * format, ...);
#endif



// Include this last
#include "bsp_common.h"

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AP_BSP_H */

