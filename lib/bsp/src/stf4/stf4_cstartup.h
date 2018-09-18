//******************************************************************************
/**
 * \file    stf4_cstartup.h
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   STM32F4xx cstartup header
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
#ifndef STF4_CSTARTUP_H
#define STF4_CSTARTUP_H

#ifndef STF4_INTERNAL
#error "This file for internal stf4 use only"
#endif

#include <stdint.h>

// TODO separate cstartup from the following functions, they do not need to be in flash


//******************************************************************************
/**
 * Get a pointer to the RAM Vector
 *
 * \param size  size fo section in bytes
 *
 * \return void *
 *******************************************************************************/
void * cstartup_getRamVec(uint32_t *size);

//******************************************************************************
/**
 * Get a pointer to the top of the stack
 *
 * \param size  size fo section in bytes
 *
 * \return void *
 *******************************************************************************/
void * cstartup_getStackTop(uint32_t *size);

//******************************************************************************
/**
 * Get a pointer to the reset Vector
 *
 * \return void *
 *******************************************************************************/
void * cstartup_getResetVec(void);

//******************************************************************************
/**
 * Get a pointer to the Saved Data
 *
 * \param size  size fo section in bytes
 *
 * \return void*
 *******************************************************************************/
void * cstartup_getSavedData(uint32_t *size);

//******************************************************************************
/**
 * Jump to the application at the given address
 *
 * \note This function will not return
 *
 * \param appAddress Start Address of application
 *
 * \return void
 *******************************************************************************/
void cstartup_jumpToApplication(uintptr_t appAddress);

#endif /* STF4_CSTARTUP_H */

