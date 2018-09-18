//******************************************************************************
/**
 * \file    hw_clock.cpp
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Emulation of hw_clock on BSP
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
#include "hw_clock.h"
#include <stdint.h>

#include "bsp_clock.h"


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void hw_clock_initialize(void)
{

}

//******************************************************************************
uint32_t hw_clock(void)
{
  return  bsp_clock_us();
}

//******************************************************************************
uint16_t hw_clock_uS(void)
{
  return (uint16_t)bsp_clock_us();
}

//******************************************************************************
uint16_t hw_clock_mS(void)
{
  return (uint16_t)bsp_clock_ms();
}

//******************************************************************************
uint16_t hw_clock_S(void)
{
  return (uint16_t)bsp_clock_s();
}

//******************************************************************************
uint32_t hw_clock_convert_clockticks_to_uS(uint32_t ticks)
{
  return ticks;
}

//******************************************************************************
uint32_t hw_clock_convert_uS_to_clockticks(uint32_t XuS)
{
  return XuS;
}

