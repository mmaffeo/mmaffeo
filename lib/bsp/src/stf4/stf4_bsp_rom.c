//******************************************************************************
/**
 * \file    stf4_bsp_rom.c
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   STM32F4xx Specific Hardware Read Only Memory source file
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
#include <stdbool.h>
#include "bsp_common.h"

#include <string.h>

#define STF4_INTERNAL (1)
#include "stm32f4xx.h"
#include "stf4_bsp_rom.h"
#undef STF4_INTERNAL


#define STF4_FLASH_IS_ADDRESS(a)          ( (((a) >= 0x08000000) && ((a) < 0x080FFFFF)) \
                                            || (((a) >= 0x1FFF7800) && ((a) < 0x1FFF7A0F)) )


//******************************************************************************
// Static Variables
//******************************************************************************


//******************************************************************************
// Global Variables
//******************************************************************************
bsp_rom_sectorInfo_t const bsp_rom_sectorInfo[BSP_ROM_NUMSECTORS] =
{// Sector Start            Sector Size   Min Device Size
  { (uint32_t *)0x08000000, ( 16 * 1024), ( 512 * 1024) },    // Section 0  - 0x08000000 to 0x08003FFF
  { (uint32_t *)0x08004000, ( 16 * 1024), ( 512 * 1024) },    // Section 1  - 0x08004000 to 0x08007FFF
  { (uint32_t *)0x08008000, ( 16 * 1024), ( 512 * 1024) },    // Section 2  - 0x08008000 to 0x0800BFFF
  { (uint32_t *)0x0800C000, ( 16 * 1024), ( 512 * 1024) },    // Section 3  - 0x0800C000 to 0x0800FFFF
  { (uint32_t *)0x08010000, ( 64 * 1024), ( 512 * 1024) },    // Section 4  - 0x08010000 to 0x0801FFFF
  { (uint32_t *)0x08020000, (128 * 1024), ( 512 * 1024) },    // Section 5  - 0x08020000 to 0x0803FFFF
  { (uint32_t *)0x08040000, (128 * 1024), ( 512 * 1024) },    // Section 6  - 0x08040000 to 0x0805FFFF
  { (uint32_t *)0x08060000, (128 * 1024), ( 512 * 1024) },    // Section 7  - 0x08060000 to 0x0807FFFF
  { (uint32_t *)0x08080000, (128 * 1024), (1024 * 1024) },    // Section 8  - 0x08080000 to 0x0809FFFF
  { (uint32_t *)0x080A0000, (128 * 1024), (1024 * 1024) },    // Section 9  - 0x080A0000 to 0x080BFFFF
  { (uint32_t *)0x080C0000, (128 * 1024), (1024 * 1024) },    // Section 10 - 0x080C0000 to 0x080DFFFF
  { (uint32_t *)0x080E0000, (128 * 1024), (1024 * 1024) },    // Section 11 - 0x080E0000 to 0x080FFFFF

  { (uint32_t *)0x08100000, ( 16 * 1024), (2048 * 1024) },    // Section 12 - 0x08100000 to 0x08103FFF
  { (uint32_t *)0x08104000, ( 16 * 1024), (2048 * 1024) },    // Section 13 - 0x08104000 to 0x08107FFF
  { (uint32_t *)0x08108000, ( 16 * 1024), (2048 * 1024) },    // Section 14 - 0x08108000 to 0x0810BFFF
  { (uint32_t *)0x0810C000, ( 16 * 1024), (2048 * 1024) },    // Section 15 - 0x0810C000 to 0x0810FFFF
  { (uint32_t *)0x08110000, ( 64 * 1024), (2048 * 1024) },    // Section 16 - 0x08110000 to 0x0811FFFF
  { (uint32_t *)0x08120000, (128 * 1024), (2048 * 1024) },    // Section 17 - 0x08120000 to 0x0813FFFF
  { (uint32_t *)0x08140000, (128 * 1024), (2048 * 1024) },    // Section 18 - 0x08140000 to 0x0815FFFF
  { (uint32_t *)0x08160000, (128 * 1024), (2048 * 1024) },    // Section 19 - 0x08160000 to 0x0817FFFF
  { (uint32_t *)0x08180000, (128 * 1024), (2048 * 1024) },    // Section 20 - 0x08180000 to 0x0819FFFF
  { (uint32_t *)0x081A0000, (128 * 1024), (2048 * 1024) },    // Section 21 - 0x081A0000 to 0x081BFFFF
  { (uint32_t *)0x081C0000, (128 * 1024), (2048 * 1024) },    // Section 22 - 0x081C0000 to 0x081DFFFF
  { (uint32_t *)0x081E0000, (128 * 1024), (2048 * 1024) },    // Section 23 - 0x081E0000 to 0x081FFFFF
};


//******************************************************************************
// Static Function Prototypes
//******************************************************************************


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_rom_init(void)
{
}

//******************************************************************************
uintptr_t bsp_rom_getStartAddr(uint32_t section_mask)
{
  uintptr_t address = 0;
  uint32_t sectorMask = section_mask;
  uint32_t compareMask = 1;
  uint32_t sector;

  for (sector = 0; (sector < BSP_ARRAY_LEN(bsp_rom_sectorInfo)) && sectorMask; sector++)
  {
    if (sectorMask & compareMask)
    {
      address = (uintptr_t)bsp_rom_sectorInfo[sector].start;
      break;
    }

    compareMask <<= 1;
  }

  return address;
}

//******************************************************************************
bool bsp_rom_isROM(uint32_t address, uint32_t length)
{
  // TODO This only checks if the first and last addresses are in flash
  return (STF4_FLASH_IS_ADDRESS(address) && STF4_FLASH_IS_ADDRESS(address + length));
}

//******************************************************************************
bool bsp_rom_readDirectROM(uint32_t address, uint32_t length, uint8_t *data)
{
  bool success = false;

  if (bsp_rom_isROM(address, length))
  {
    memcpy(data, (void *)address, length);
    success = true;
  }

  return success;
}

//******************************************************************************
bool bsp_rom_readDirectRAM(uint32_t address, uint32_t length, uint8_t *data)
{
  bool success = true;

  // TODO check if address is RAM
  memcpy(data, (void *)address, length);

  return success;
}

//******************************************************************************
// Static Function Definitions
//******************************************************************************


