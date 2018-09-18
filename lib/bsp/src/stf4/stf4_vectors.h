//******************************************************************************
/**
 * \file    stf4_vectors.h
 * \author  Chad Swenson
 * \date    Jan 2014
 * \brief   Ram Vector header
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
#ifndef STF4_VECTORS_H
#define STF4_VECTORS_H

#ifndef STF4_INTERNAL
#error "This file for internal stf4 use only"
#endif

#include "stm32f4xx.h"

/// Vector Entry Type
typedef void (* vectors_entry_t)(void);

//******************************************************************************
/**
 * Initialize the RAM Vector block and preload all ISR to defaultIsr
 *
 * \param defaultIsr
 *
 * \return void
 *******************************************************************************/
void vectors_initRamVectors(vectors_entry_t defaultIsr);

//******************************************************************************
/**
 * Set the specified Interrupt Vector
 *
 * \param irqn
 * \param isr
 *
 * \return void
 *******************************************************************************/
void vectors_setRamVector(IRQn_Type irqn, vectors_entry_t isr);

//******************************************************************************
/**
 * Switch the core to the RAM vectors
 *
 * \return void
 *******************************************************************************/
void vectors_switchToRam(void);

#endif /* STF4_VECTORS_H */

