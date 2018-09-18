//******************************************************************************
/**
 * \file    hw_io.cpp
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Emulation of hw_io on BSP
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
#include "hw_io.h"
#include "nvm_ecuid.h"
#include "bsp_common.h"
#include "bsp_adc.h"
#include "bsp_can.h"
#include "bsp_din.h"
#include "bsp_dout.h"
#include "bsp_fin.h"
#include "bsp_pwm.h"
#include "bsp_rom.h"

#include <string.h>

typedef void (* readDirect_t)(uint_fast16_t section, uint32_t address, uint32_t length, uint8_t *data);

typedef struct directSection_s
{
  uint32_t start;
  uint32_t length;
  readDirect_t readFunction;
} directSection_t;

//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void readDirect(uint32_t address, uint32_t length, uint8_t *data);

static void readDirect_nvm1(uint_fast16_t section, uint32_t address, uint32_t length, uint8_t *data);
static void readDirect_nvm2(uint_fast16_t section, uint32_t address, uint32_t length, uint8_t *data);
static void readDirect_rom(uint_fast16_t section, uint32_t address, uint32_t length, uint8_t *data);
static void readDirect_ram(uint_fast16_t section, uint32_t address, uint32_t length, uint8_t *data);


//******************************************************************************
// Static Variables
//******************************************************************************

static directSection_t const directMap[] =
{// Start         Length    Read Function
  { 0x00000000,   0x00000100,   readDirect_nvm2   },
  { 0x00001000,   0x00002000,   readDirect_nvm1   },
  { 0x08000000,   0x00100000,   readDirect_rom    },
  { 0x10000000,   0x00010000,   readDirect_ram    },
  { 0x1FFF7800,   0x00000210,   readDirect_rom    },
  { 0x20000000,   0x00020000,   readDirect_ram    },
};


//******************************************************************************
// Global Variables
//******************************************************************************

uint16_t max_stack_size = 0;


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void hw_io_initialize(void)
{
  // inputs...
  hw_adc_initialize();
  hw_fin_initialize();
  hw_dio_initialize();

  // outputs...
  hw_pwm_initialize();
  hw_gauge_initialize();

  hw_can_initialize();

  hw_mcu_initialize();

  hw_nvm_initialize();

  nvm_ecuid.initialize();
}

//******************************************************************************
void hw_io_update(void)
{
  // inputs...
  hw_adc_update();
  hw_fin_update();
  hw_dio_update();

  // outputs...
  hw_pwm_update();
  hw_gauge_update();

  hw_can_update();
  hw_mcu_update();

  hw_nvm_update();

  max_stack_size = hw_reset_max_stack();
}

//******************************************************************************
uint8_t hw_readByteDirect(uint32_t address)
{
  uint8_t data = 0;

  readDirect(address, sizeof(uint8_t), &data);

  return data;
}

//******************************************************************************
uint16_t hw_readWordDirect(uint32_t address)
{
  uint8_t tempData[sizeof(uint16_t)];
  uint16_t data;

  readDirect(address, sizeof(uint16_t), tempData);

  data = tempData[1];
  data <<= 8;
  data |= tempData[0];

  return data;
}

//******************************************************************************
uint32_t hw_readDwordDirect(uint32_t address)
{
  uint8_t tempData[sizeof(uint32_t)];
  uint32_t data;

  readDirect(address, sizeof(uint32_t), tempData);
  
  data = tempData[3];
  data <<= 8;
  data |= tempData[2];
  data <<= 8;
  data |= tempData[1];
  data <<= 8;
  data |= tempData[0];

  return data;
}
//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
static void readDirect(uint32_t address, uint32_t length, uint8_t *data)
{
  uint_fast16_t section = 0;

  while (section < BSP_ARRAY_LEN(directMap))
  {
    if ((address < directMap[section].start)
        || (address >= (directMap[section].start + directMap[section].length)))
    {
      // Wrong section, move on
      section++;
    }
    else
    {
      if ((address + length) <= (directMap[section].start + directMap[section].length))
      {
        directMap[section].readFunction(section, address, length, data);
      }
      break;
    }
  }
}

//******************************************************************************
static void readDirect_nvm1(uint_fast16_t section, uint32_t address, uint32_t length, uint8_t *data)
{
  // Adjust address to device address
  address -= directMap[section].start;
  hw_nvm_eeprom_read(E10, (uint16_t)length, (uint16_t)address, data);
}

//******************************************************************************
static void readDirect_nvm2(uint_fast16_t section, uint32_t address, uint32_t length, uint8_t *data)
{
  // Adjust address to device address
  address -= directMap[section].start;
  hw_nvm_eeprom_read(E0, (uint16_t)length, (uint16_t)address, data);
}

//******************************************************************************
static void readDirect_rom(uint_fast16_t section, uint32_t address, uint32_t length, uint8_t *data)
{
  bsp_rom_readDirectROM(address,length,data);
}

//******************************************************************************
static void readDirect_ram(uint_fast16_t section, uint32_t address, uint32_t length, uint8_t *data)
{
  bsp_rom_readDirectRAM(address,length,data);
}


