//******************************************************************************
/**
 * \file    bsp_MCU.h
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   Microcontroller header
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
#ifndef BSP_MCU_H
#define BSP_MCU_H

#include <stdint.h>
#include <stdbool.h>
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

//******************************************************************************
/**
 * Initialize hardware Microcontroller module
 *
 * \return void
 *******************************************************************************/
void bsp_mcu_init(void);

//******************************************************************************
/**
 * Reset the micro if required.
 *
 * \note This function should be called from the bsp_sleep function
 *
 * \return void
 *******************************************************************************/
void bsp_mcu_run(void);

//******************************************************************************
/**
 * Kick the task specific watchdog. This also rigsters the specific task
 *
 * \param task
 *
 * \return void
 *******************************************************************************/
void bsp_mcu_kickTaskWatchdog(uint32_t task);

//******************************************************************************
/**
 * Request a microcontroller reset.  The reset will occur after a preset period
 *  of time.
 *
 * \return void
 *******************************************************************************/
void bsp_mcu_requestReset(void);

//******************************************************************************
/**
 *
 *
 * \return uint32_t
********************************************************************************/
uint32_t bsp_mcu_maxStack(void);

//******************************************************************************
/**
 * Jump to the application at the given address
 *
 * \note This function will not return
 *
 * \param appAddress Start Address of application
 *
 * \return void
********************************************************************************/
void bsp_mcu_jumpToApplication(uintptr_t appAddress);

//******************************************************************************
/**
*
*
* \param busy
*
* \return void
*******************************************************************************/
void bsp_mcu_setBusy(bool busy);

//******************************************************************************
/**
 * Enter a Critical Section
 *
 * \return void
 *******************************************************************************/
void bsp_enterCritical(void);

//******************************************************************************
/**
 * Exit a Critical Section
 *
 * \return void
 *******************************************************************************/
void bsp_exitCritical(void);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* BSP_MCU_H */

