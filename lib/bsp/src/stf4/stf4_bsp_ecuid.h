//******************************************************************************
/**
 * \file    stf4_bsp_ecuid.h
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   STM32F4 Specific Hardware ECU ID Header
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
#ifndef STF4_BSP_ECUID_H
#define STF4_BSP_ECUID_H

#ifndef STF4_INTERNAL
#error "This file for internal stf4 use only"
#endif

#include "bsp_ecuid.h"

//******************************************************************************
/**
 * Mark the ECUID as valid or invalid.  If invalid, default values will be loaded.
 *
 * \param invalid  true if ECUID isnot valid
 *
 * \return void
 *******************************************************************************/
void bsp_ecuid_setInvalid(bool invalid);

#endif /* STF4_BSP_ECUID_H */

