//******************************************************************************
/**
 * \file    hw_nvm.cpp
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Emulation of hw_nvm on BSP
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
#include "hw_nvm.h"
#include "bsp_nvm.h"
#include "hw_adc.h"


typedef struct
{
  uint16_t section;
  uint32_t min_addr;
  uint32_t max_addr;
  bsp_nvm_t nvmDevice;
} section_t;


#define MINIMUM_BATTERY_LEVEL     (204)


//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static uint8_t eeprom_write(bsp_nvm_t nvmDevice, uint8_t size_, uint16_t address, uint8_t const *data);
static uint8_t eeprom_read(bsp_nvm_t nvmDevice, uint16_t size_, uint16_t address, uint8_t *data);
static uint8_t nvmStatusConvert(bsp_nvm_status_t status);
static hw_nvm_status get_eeprom_address(hw_nvm_eeprom_section_t s,
                                        uint16_t nvm_address,
                                        uint16_t *eeprom_address,
                                        bsp_nvm_t *nvmDevice);

//******************************************************************************
// Static Variables
//******************************************************************************
static section_t const EEPROM_SECTIONS[]=
{
    {(uint16_t)  E0,  0x0000, 0x00FF, BSP_NVM_2 },  // NVM 2 Full, Manufacturing Data
    {(uint16_t)  E1,  0x0F80, 0x0FBF, BSP_NVM_1 },  // Hour Meter
    {(uint16_t)  E2,  0x0F40, 0x0F7F, BSP_NVM_1 },  // Unused
    {(uint16_t)  E3,  0x0000, 0x0F3F, BSP_NVM_1 },  // Mirror
    {(uint16_t)  E10, 0x0000, 0x1FFF, BSP_NVM_1 },  // NVM 1 Full
};

static uint8_t const EEPROM_SECTION_QTY = sizeof(EEPROM_SECTIONS)/sizeof(section_t);


//******************************************************************************
// Global Variables
//******************************************************************************
hwt_eeprom_tstate_t hwt_eeprom_tstate;
uint16_t hwt_eeprom_tcmd;
uint16_t hwt_eeprom_tfailures;


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
hw_nvm_status hw_nvm_eeprom_read(hw_nvm_eeprom_section_t s, uint16_t size_, uint16_t address, uint8_t *data)
{
  uint16_t ee_address;
  bsp_nvm_t nvmDevice;

  hw_nvm_status status = get_eeprom_address(s, address, &ee_address, &nvmDevice);

  if (status == NVM_OK)
  {
    status = (hw_nvm_status)eeprom_read(nvmDevice, size_, ee_address, data);
  }

  return status;
}

//******************************************************************************
hw_nvm_status hw_nvm_eeprom_read_uint8(hw_nvm_eeprom_section_t s, uint16_t address, uint8_t *data)
{
  uint16_t ee_address;
  bsp_nvm_t nvmDevice;

  hw_nvm_status status = get_eeprom_address(s, address, &ee_address, &nvmDevice);

  if (status == NVM_OK)
  {
    status = (hw_nvm_status)eeprom_read(nvmDevice, sizeof(uint8_t), ee_address, data);
  }

  return status;
}

//******************************************************************************
hw_nvm_status hw_nvm_eeprom_read_uint16(hw_nvm_eeprom_section_t s, uint16_t address, uint16_t *data)
{
  uint16_t ee_address;
  bsp_nvm_t nvmDevice;

  hw_nvm_status status = get_eeprom_address(s, address, &ee_address, &nvmDevice);

  if (status == NVM_OK)
  {
    uint8_t tempData[sizeof(uint16_t)];
    status = (hw_nvm_status)eeprom_read(nvmDevice, sizeof(tempData), ee_address, tempData);

    *data = tempData[1];
    *data <<= 8;
    *data |= tempData[0];
  }

  return status;
}

//******************************************************************************
hw_nvm_status hw_nvm_eeprom_read_uint32(hw_nvm_eeprom_section_t s, uint16_t address, uint32_t *data)
{
  uint16_t ee_address;
  bsp_nvm_t nvmDevice;

  hw_nvm_status status = get_eeprom_address(s, address, &ee_address, &nvmDevice);

  if (status == NVM_OK)
  {
    uint8_t tempData[sizeof(uint32_t)];
    status = (hw_nvm_status)eeprom_read(nvmDevice, sizeof(tempData), ee_address, tempData);

    *data = tempData[3];
    *data <<= 8;
    *data |= tempData[2];
    *data <<= 8;
    *data |= tempData[1];
    *data <<= 8;
    *data |= tempData[0];
  }

  return status;
}

//******************************************************************************
hw_nvm_status hw_nvm_eeprom_write_uint16(hw_nvm_eeprom_section_t s, uint16_t address, uint16_t data)
{
  uint16_t ee_address;
  bsp_nvm_t nvmDevice;

  hw_nvm_status status = get_eeprom_address(s, address, &ee_address, &nvmDevice);

  if (status == NVM_OK)
  {
    uint8_t tempData[sizeof(uint16_t)];

    tempData[0] = (uint8_t)data;
    data >>= 8;
    tempData[1] = (uint8_t)data;

    status = (hw_nvm_status)eeprom_write(nvmDevice, sizeof(tempData), ee_address, tempData);
  }

  return status;
}

//******************************************************************************
hw_nvm_status hw_nvm_eeprom_write_uint32(hw_nvm_eeprom_section_t s, uint16_t address, uint32_t data)
{
  uint16_t ee_address;
  bsp_nvm_t nvmDevice;

  hw_nvm_status status = get_eeprom_address(s, address, &ee_address, &nvmDevice);

  if (status == NVM_OK)
  {
    uint8_t tempData[sizeof(uint32_t)];

    tempData[0] = (uint8_t)data;
    data >>= 8;
    tempData[1] = (uint8_t)data;
    data >>= 8;
    tempData[2] = (uint8_t)data;
    data >>= 8;
    tempData[3] = (uint8_t)data;

    status = (hw_nvm_status)eeprom_write(nvmDevice, sizeof(tempData), ee_address, tempData);
  }

  return status;
}

//******************************************************************************
uint16_t hw_nvm_eeprom_checksum(uint16_t section_mask)
{
  uint16_t checksum = 0;

  for (uint8_t i = 0; i < EEPROM_SECTION_QTY; ++i)
  {
    if (EEPROM_SECTIONS[i].section & section_mask)
    {
      uint32_t address = EEPROM_SECTIONS[i].min_addr;
      uint32_t length = (EEPROM_SECTIONS[i].max_addr - EEPROM_SECTIONS[i].min_addr) + 1;

      bsp_nvm_checksum(EEPROM_SECTIONS[i].nvmDevice, address, length, &checksum);
    }
  }

  return checksum;
}

//******************************************************************************
bool hw_nvm_eeprom_write_pending(void)
{
  // We do not care with the BSP, return false
  return false;
}

//******************************************************************************
void hw_nvm_initialize(void)
{
  hwt_eeprom_tstate = HWT_EETS_IDLE;
  hwt_eeprom_tcmd = 0;
  hwt_eeprom_tfailures = 0;
}

//******************************************************************************
void hw_nvm_update(void)
{
  bsp_nvm_status_t testStatus;
  uint32_t tFailures = 0;

  if (hwt_eeprom_tcmd > 0)
  {
    bsp_nvm_startTest(BSP_NVM_1, hwt_eeprom_tcmd - 1);
    hwt_eeprom_tcmd = 0;
  }

  testStatus = bsp_nvm_getTestStatus(BSP_NVM_1, &tFailures);

  switch (testStatus)
  {
  case BSP_NVM_BUSY:
    hwt_eeprom_tstate = HWT_EETS_RUNNING;
    break;

  case BSP_NVM_FAIL:
    hwt_eeprom_tstate = HWT_EETS_IDLE_FAILURE;
    break;

  case BSP_NVM_OK:
    hwt_eeprom_tstate = HWT_EETS_IDLE_SUCCESS;
    break;

  case BSP_NVM_NOTAVAIL:
  default:
    hwt_eeprom_tstate = HWT_EETS_IDLE;
    break;
  }

  hwt_eeprom_tfailures = tFailures < 0xFFFF ? tFailures : 0xFFFF;
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************


//******************************************************************************
/**
 *
 *
 * \param nvmDevice
 * \param size_
 * \param address
 * \param data
 *
 * \return uint8_t
 *******************************************************************************/
static uint8_t eeprom_write(bsp_nvm_t nvmDevice, uint8_t size_, uint16_t address, uint8_t const *data)
{
  uint8_t status = NVM_OK;
  uint16_t tempVBattery = hw_adc_GetValue(HWC_ADC_BATT_AFBK);

  if ( hw_nvm_eeprom_write_pending() )
  {
    status  = NVM_BUSY;
  }
  else if (tempVBattery <= MINIMUM_BATTERY_LEVEL)
  {
    status  = NVM_BATT;
  }
  else
  {
    bsp_nvm_status_t bspStatus = bsp_nvm_write(nvmDevice, address, size_, data);
    status = nvmStatusConvert(bspStatus);
  }

  return status;
}

#if HW_NVM_FAKE_MANUFACTURING_DATA
#include <string.h>
//******************************************************************************
/**
 *
 *
 * \param size_
 * \param address
 * \param data
 *
 * \return bsp_nvm_status_t
 *******************************************************************************/
static bsp_nvm_status_t readFakeManuData(uint16_t size_, uint16_t address, uint8_t *data)
{
  extern uint8_t const fakeManuData[256];
  bsp_nvm_status_t status = BSP_NVM_OK;

  uint32_t endAddress = address;
  endAddress += size_;

  if (endAddress > sizeof(fakeManuData))
  {
    status = BSP_NVM_RANGE;
  }
  else
  {
    memcpy(data, &fakeManuData[address], size_);
  }

  return status;
}
#endif

//******************************************************************************
/**
 *
 *
 * \param nvmDevice
 * \param size_
 * \param address
 * \param data
 *
 * \return uint8_t
 *******************************************************************************/
static uint8_t eeprom_read(bsp_nvm_t nvmDevice, uint16_t size_, uint16_t address, uint8_t *data)
{
  bsp_nvm_status_t bspStatus = BSP_NVM_OK;

#if HW_NVM_FAKE_MANUFACTURING_DATA
  if (nvmDevice == BSP_NVM_2)
  {
    bspStatus = readFakeManuData(size_, address, data);
  }
  else
#endif
  {
    bspStatus = bsp_nvm_read(nvmDevice, address, size_, data);
  }

  return nvmStatusConvert(bspStatus);
}

//******************************************************************************
/**
 *
 *
 * \param status
 *
 * \return uint8_t
 *******************************************************************************/
static uint8_t nvmStatusConvert(bsp_nvm_status_t status)
{
  uint8_t hwStatus = NVM_OK;

  switch (status)
  {
  case BSP_NVM_OK:
    hwStatus = NVM_OK;
    break;

  case BSP_NVM_BUSY:
    hwStatus = NVM_BUSY;
    break;

  case BSP_NVM_RANGE:
    hwStatus = NVM_RANGE;
    break;

  case BSP_NVM_FAIL:
  case BSP_NVM_NOTAVAIL:
  default:
    hwStatus = NVM_NOTAVAIL;
    break;
  }

  return hwStatus;
}

//******************************************************************************
/**
 *
 *
 * \param s
 * \param nvm_address
 * \param eeprom_address
 * \param nvmDevice
 *
 * \return hw_nvm_status
 *******************************************************************************/
static hw_nvm_status get_eeprom_address(hw_nvm_eeprom_section_t s,
                                        uint16_t nvm_address,
                                        uint16_t *eeprom_address,
                                        bsp_nvm_t *nvmDevice)
{
  uint8_t i = 0;

  while (i < EEPROM_SECTION_QTY && s!=EEPROM_SECTIONS[i].section)
  {
    ++i;
  }

  if (i == EEPROM_SECTION_QTY)
  {
    return NVM_RANGE;
  }

  uint32_t s_size = 1 + (EEPROM_SECTIONS[i].max_addr - EEPROM_SECTIONS[i].min_addr);

  if (nvm_address >= s_size)
  {
    return NVM_RANGE;
  }

  *eeprom_address = (uint16_t)(EEPROM_SECTIONS[i].min_addr + nvm_address);
  *nvmDevice = EEPROM_SECTIONS[i].nvmDevice;

  return NVM_OK;
}


