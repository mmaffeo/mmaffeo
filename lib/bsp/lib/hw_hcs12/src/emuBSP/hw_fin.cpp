//******************************************************************************
/**
 * \file    hw_fin.cpp
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Emulation of hw_fin on BSP
 *
 * \copyright
 * Copyright 2013 Bobcat Company as an unpublished work.
 * All Rights Reserved.
 *
 * \b Notice:
 * The information contained herein is confidential
 * property of Bobcat Company. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Bobcat Company.
 *
 *******************************************************************************/
#include "hw_fin.h"
#include <stdint.h>

#include "bsp_fin.h"


//******************************************************************************
// Static Function Prototypes
//******************************************************************************


//******************************************************************************
// Static Variables
//******************************************************************************


//******************************************************************************
// Global Variables
//******************************************************************************
uint32_t PERIOD_COUNTS_PER_SECOND;
//uint32_t PERIOD_COUNTS_MAXIMUM;


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
uint32_t hw_fin_GetPeriodCount(hw_fin_ch_t ch)
{
  return bsp_fin_GetPeriodCount(BSP_FIN_1)/2;
}

//******************************************************************************
uint32_t hw_fin_GetPerioduS(hw_fin_ch_t ch)
{
  return bsp_fin_GetPerioduS(BSP_FIN_1);
}

//******************************************************************************
void hw_fin_initialize(void)
{
  PERIOD_COUNTS_PER_SECOND = bsp_fin_GetCountsPerSecond(BSP_FIN_1)/2;
}

//******************************************************************************
void hw_fin_update(void)
{

}


//******************************************************************************
// Static Function Definitions
//******************************************************************************



