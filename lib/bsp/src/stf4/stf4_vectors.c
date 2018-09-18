//******************************************************************************
/**
 * \file    stf4_vectors.c
 * \author  Chad Swenson
 * \date    Jan 2014
 * \brief   Ram Vector Implementation
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
#include <stdint.h>
#include <stddef.h>

#define STF4_INTERNAL (1)
#include "stf4_vectors.h"
#include "stf4_cstartup.h"
#include "stm32f4xx.h"
#undef STF4_INTERNAL

//******************************************************************************
// Defines
//******************************************************************************

//******************************************************************************
// Static Variables
//******************************************************************************
static vectors_entry_t *ramVector = NULL;
static uint32_t remVectorLength = 0;

//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void vectors_initRamVectors(vectors_entry_t defaultIsr)
{

  uint_fast16_t i = 0;
  uint32_t ramVactorSize = 0;

  ramVector = (vectors_entry_t *)cstartup_getRamVec(&ramVactorSize);
  remVectorLength = ramVactorSize / sizeof(vectors_entry_t);

  if (i < remVectorLength)
  {
    ramVector[i++] = (vectors_entry_t)cstartup_getStackTop(NULL);
  }

  if (i < remVectorLength)
  {
    ramVector[i++] = (vectors_entry_t)cstartup_getResetVec();
  }

  for (; i < remVectorLength; i++)
  {
    ramVector[i] = defaultIsr;
  }
}

//******************************************************************************
void vectors_setRamVector(IRQn_Type irqn, vectors_entry_t isr)
{
  int32_t index = irqn;

  // Do not allow the Stack pointer or Reset Vector to be set
  if ((ramVector != NULL) && (irqn >= NonMaskableInt_IRQn))
  {
    // IRQn_t alignes 0 to the first non core vector
    // Subtract StackBase_IRQn to realign to the first vector
    index -= (int32_t)StackBase_IRQn;

    if (index < remVectorLength)
    {
      ramVector[index] = isr;
    }
  }
}

//******************************************************************************
void vectors_switchToRam(void)
{
  if (ramVector != NULL)
  {
    SCB->VTOR = (uint32_t)cstartup_getRamVec(NULL);
  }
}

