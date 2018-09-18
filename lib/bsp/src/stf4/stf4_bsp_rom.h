//******************************************************************************
/**
 * \file    stf4_bsp_flash.h
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   STM32F4xx Specific Hardware Read Only Memory header file
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
#ifndef STF4_BSP_ROM_H
#define STF4_BSP_ROM_H

#ifndef STF4_INTERNAL
#error "This file for internal stf4 use only"
#endif

#include <stdint.h>
#include "bsp_rom.h"

typedef struct bsp_rom_sectorInfo_s
{
  uint32_t const * start;
  uint32_t size;
  uint32_t minDeviceSize;
} bsp_rom_sectorInfo_t;

#define BSP_ROM_NUMSECTORS  (24)
extern bsp_rom_sectorInfo_t const bsp_rom_sectorInfo[BSP_ROM_NUMSECTORS];

#endif /* STF4_BSP_ROM_H */

