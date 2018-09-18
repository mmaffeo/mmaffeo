//******************************************************************************
/**
 * \file    stf4_bsp_dout.h
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   STM32F4xx Specific Digital Output Header
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
#ifndef STF4_BSP_DOUT_H
#define STF4_BSP_DOUT_H

#ifndef STF4_INTERNAL
#error "This file for internal stf4 use only"
#endif


#include "bsp_dout.h"

//******************************************************************************
/**
 * Set state of all outputs enabled to generate wetting current pulses
 *
 * \note Called from ADC Timer interrupt
 *
 * \param state
 *
 * \return void
 *******************************************************************************/
void bsp_dout_setWCState(bool state);

#endif /* STF4_BSP_DOUT_H */

