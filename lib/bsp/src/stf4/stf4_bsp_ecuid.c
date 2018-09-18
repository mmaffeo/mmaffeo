//******************************************************************************
/**
 * \file    stf4_bsp_ecuid.c
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   STM32F4 Specific Hardware ECU ID Source
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

#include "bsp_types.h"
#include "bsp_rom.h"

#define STF4_INTERNAL (1)
#include "stf4_bsp_ecuid.h"
#undef STF4_INTERNAL


typedef struct stf4_bsp_ecuid_s
{
  uint8_t j1939_source_address;
  uint8_t bobcat_module_id;
  uint8_t reserved_00;
  uint8_t reserved_01;
  uint32_t ap_sw_code_smask;
  uint32_t ap_sw_const_smask;
} stf4_bsp_ecuid_t;


//******************************************************************************
// Static Variables
//******************************************************************************
static bsp_ecuid_t ecuid;
static bool ecuidInvalid = false;

//******************************************************************************
// Global Variables
//******************************************************************************
bsp_ecuid_t const * const bsp_ecuid = &ecuid;

//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_ecuid_init(void)
{
  stf4_bsp_ecuid_t const *ecuidRaw = (stf4_bsp_ecuid_t *)bsp_rom_getStartAddr(BSP_ROM_MASK_ECUID);

  if ((ecuidRaw != NULL) && !ecuidInvalid)
  {
    // Copy ecuid from raw ROM into generic ram copy
    ecuid.j1939_source_address = ecuidRaw->j1939_source_address;
    ecuid.bobcat_module_id = ecuidRaw->bobcat_module_id;
    ecuid.ap_sw_code_smask = ecuidRaw->ap_sw_code_smask;
    ecuid.ap_sw_const_smask = ecuidRaw->ap_sw_const_smask;
  }
  else
  {
    // Use default values
    ecuid.j1939_source_address = 253;
    ecuid.bobcat_module_id = 0x00;
    ecuid.ap_sw_code_smask = 0xFFFFFFFF;
    ecuid.ap_sw_const_smask = 0xFFFFFFFF;
  }
}

//******************************************************************************
void bsp_ecuid_setInvalid(bool invalid)
{
  ecuidInvalid = invalid;
  bsp_ecuid_init();
}


