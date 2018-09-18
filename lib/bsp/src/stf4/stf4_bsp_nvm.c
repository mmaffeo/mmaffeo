 //******************************************************************************
/**
 * \file    stf4_bsp_nvm.c
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   STM32F4xx Specific Hardware Non-Volatile memory source file
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
#include <string.h>

#include "bsp_common.h"

#define STF4_INTERNAL (1)
#include "stf4_bsp_nvm.h"
#include "stm32f4xx.h"
#include "stf4_iic.h"
#undef STF4_INTERNAL


/// Calculate the number of bytes needed to hold all page flags for an eeprom buffer
#define EE_PAGE_FLAG_LEN(bSize, pSize)   ((((bSize)/(pSize)) + 7) / 8)

#define EE1_SIZE        (8 * 1024)
#define EE1_PAGE_SIZE   (32)
#define EE1_FLAG_SIZE   (EE_PAGE_FLAG_LEN(EE1_SIZE, EE1_PAGE_SIZE))

#define EE2_SIZE        (256)
#define EE2_PAGE_SIZE   (8)
#define EE2_FLAG_SIZE   (EE_PAGE_FLAG_LEN(EE1_SIZE, EE1_PAGE_SIZE))

typedef enum nvm_test_0_stage_e
{
  NVM_TEST_0_STAGE_INIT = 0,
  NVM_TEST_0_STAGE_WRITE,
  NVM_TEST_0_STAGE_READ,
  NVM_TEST_0_STAGE_CLEAR
} nvm_test_0_stage_t;

typedef enum nvm_state_e
{
  NVM_STATE_IDLE = 0,
  NVM_STATE_READ_DEVICE,
  NVM_STATE_PAGE_WRITE
} nvm_state_t;

typedef struct nvm_eepromConfig_s
{
  uint8_t *buffer;
  uint8_t *flags;
  uint32_t bufferSize;
  uint32_t pageSize;
  uint32_t flagSize;

  uint32_t opTimeout;


} nvm_eepromConfig_t;

typedef struct nvm_eepromData_s
{
  bool busy;
  bool current;

  bsp_nvm_status_t testStatus;
  uint16_t testType;
  uint32_t testStage;
  uint32_t testFailures;
} nvm_eepromData_t;


//******************************************************************************
// Static Function Prototypes
//******************************************************************************

static bsp_nvm_status_t nvm_read(bsp_nvm_t sect,
                                 uint32_t address,
                                 uint32_t length,
                                 uint8_t * data);
static bsp_nvm_status_t nvm_write(bsp_nvm_t sect,
                                  uint32_t address,
                                  uint32_t length,
                                  uint8_t  const * data);
static bool findNexWrite(uint_fast16_t eepromIndex, uint32_t * address, uint32_t * length);
static void setWriteFlags(uint_fast16_t eepromIndex, uint32_t address, uint32_t length);

static void runTest(bsp_nvm_t sect);
static void runTest_0(bsp_nvm_t sect);


//******************************************************************************
// Static Variables
//******************************************************************************
static uint8_t ee1_buffer[EE1_SIZE];
static uint8_t ee1_bufferFlags[EE1_FLAG_SIZE];
static uint8_t ee2_buffer[EE2_SIZE];
static uint8_t ee2_bufferFlags[EE2_FLAG_SIZE];

static iic_config_t const iic_config[] =
{// IIC Port  IIC Address     Mem Address Width
  { 0,        0xA0,           2                 },  // EEPROM 1  - 4LC64-E/SN - 64kbit
  { 1,        0xA0,           1                 },  // EEPROM 2  - 24LC02BH-E/OT - 2kbit
};

static iic_handle_t iic_handle[BSP_ARRAY_LEN(iic_config)];

static nvm_eepromConfig_t const eepromConfig[BSP_ARRAY_LEN(iic_config)] =
{// Buffer        Flags             Buffer Size    Page Size        Flag Size        Op Timeout
  { ee1_buffer,   ee1_bufferFlags,  EE1_SIZE,      EE1_PAGE_SIZE,   EE1_FLAG_SIZE,   500000    },
  { ee2_buffer,   ee2_bufferFlags,  EE2_SIZE,      EE2_PAGE_SIZE,   EE2_FLAG_SIZE,   500000    },
};

static nvm_eepromData_t eepromData[BSP_ARRAY_LEN(eepromConfig)];




//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_nvm_init(void)
{
  uint_fast16_t i;

  for (i = 0; i < BSP_ARRAY_LEN(iic_config); i++)
  {
    eepromData[i].busy = false;
    eepromData[i].current = false;

    eepromData[i].testStatus = BSP_NVM_NOTAVAIL;
    eepromData[i].testType = 0;
    eepromData[i].testStage = 0;
    eepromData[i].testFailures = 0;

    stf4_iic_initHandle(&iic_handle[i], &iic_config[i]);

    BSP_DEBUG(("NVM%i initialized...", i + 1));

    stf4_iic_startOp(&iic_handle[i],
                     IIC_OP_RAND_READ,
                     0,
                     eepromConfig[i].bufferSize,
                     eepromConfig[i].buffer);
  }

#if 0
#warning "Debug code enabled!"
#define TEST_STRING1 ("Chad's test string")

# if 0
  while (iic_handle[0].status == IIC_STATUS_BUSY);
# else
  stf4_iic_reset(&iic_handle[0]);
# endif

  stf4_iic_startOp(&iic_handle[0],
                   IIC_OP_WRITE,
                   0,
                   sizeof(TEST_STRING1),
                   TEST_STRING1);

#elif 0
#warning "Debug code enabled!"
#define TEST_STRING1 ("Chad   ")

  while (iic_handle[0].status == IIC_STATUS_BUSY);

  stf4_iic_startOp(&iic_handle[1],
                   IIC_OP_WRITE,
                   0,
                   sizeof(TEST_STRING1),
                   TEST_STRING1);

#endif
}

//******************************************************************************
void bsp_nvm_run(void)
{
  uint_fast16_t i;

  for (i = 0; i < BSP_ARRAY_LEN(eepromConfig); i++)
  {
    bool tempBusy = true;
    uint32_t address = 0;
    uint32_t length = 0;
    iic_status_t status = stf4_iic_getStatus(&iic_handle[i]);
    iic_operation_t operation = stf4_iic_getOp(&iic_handle[i],
                                               &address,
                                               &length);

    if (status == IIC_STATUS_BUSY)
    {
      // IIC busy, check for timeout
      if (stf4_iic_getOpTime(&iic_handle[i]) >= eepromConfig[i].opTimeout)
      {
        stf4_iic_reset(&iic_handle[i]);
      }
    }
    else if (!eepromData[i].current)
    {
      // A read will only occur if a different operation
      // has occured since the last read
      if ((status == IIC_STATUS_SUCCESS)
          && (operation == IIC_OP_RAND_READ)
          && (address == 0)
          && (length = eepromConfig[i].bufferSize))
      {
        // We have successfully read the entire eeprom
        eepromData[i].current = true;

        BSP_DEBUG(("NVM%i read complete", i + 1));
#if 0
#warning "Debug code enabled!"
        address = i == 0 ? 0x0F20 : 0;
        BSP_DEBUG(("NVM%i@%04X: %02X %02X %02X %02X",
                   i + 1,
                   address,
                   eepromConfig[i].buffer[address + 0],
                   eepromConfig[i].buffer[address + 1],
                   eepromConfig[i].buffer[address + 2],
                   eepromConfig[i].buffer[address + 3]));
#endif
      }
      else
      {
        // Not current, read the device
        stf4_iic_startOp(&iic_handle[i],
                         IIC_OP_RAND_READ,
                         0,
                         eepromConfig[i].bufferSize,
                         eepromConfig[i].buffer);
      }
    }
    else if (findNexWrite(i, &address, &length))
    {
      stf4_iic_startOp(&iic_handle[i],
                       IIC_OP_WRITE,
                       address,
                       length,
                       &eepromConfig[i].buffer[address]);

    }
    else
    {
      tempBusy = false;
    }

    eepromData[i].busy = tempBusy;

    runTest((bsp_nvm_t)i);
  }
}

//******************************************************************************
bool bsp_nvm_isBusy(void)
{
  uint_fast16_t i;
  bool busy = false;

  for (i = 0; i < BSP_ARRAY_LEN(eepromConfig); i++)
  {
    busy |= eepromData[i].busy;
  }

  return busy;
}

//******************************************************************************
bsp_nvm_status_t bsp_nvm_read(bsp_nvm_t sect,
                              uint32_t address,
                              uint32_t length,
                              uint8_t * data)
{
  bsp_nvm_status_t status = BSP_NVM_OK;

  if ((uint32_t)sect >= BSP_ARRAY_LEN(eepromConfig))
  {
    status = BSP_NVM_NOTAVAIL;
  }
  else if (!eepromData[sect].current
           || (eepromData[sect].testStatus == BSP_NVM_BUSY))
  {
    status = BSP_NVM_BUSY;
  }
  else
  {
    status = nvm_read(sect, address, length, data);
  }

  return status;
}

//******************************************************************************
bsp_nvm_status_t bsp_nvm_write(bsp_nvm_t sect,
                               uint32_t address,
                               uint32_t length,
                               uint8_t  const * data)
{
  bsp_nvm_status_t status = BSP_NVM_OK;

  if ((uint32_t)sect >= BSP_ARRAY_LEN(eepromConfig))
  {
    status = BSP_NVM_NOTAVAIL;
  }
  else if (!eepromData[sect].current
           || (eepromData[sect].testStatus == BSP_NVM_BUSY))
  {
    status = BSP_NVM_BUSY;
  }
  else
  {
    status = nvm_write(sect,address,length,data);
  }

  return status;
}

//******************************************************************************
bsp_nvm_status_t bsp_nvm_checksum(bsp_nvm_t sect,
                                  uint32_t address,
                                  uint32_t length,
                                  uint16_t * checksum)
{
  bsp_nvm_status_t status = BSP_NVM_OK;
  nvm_eepromConfig_t const * config = &eepromConfig[sect];

  if ((uint32_t)sect >= BSP_ARRAY_LEN(eepromConfig))
  {
    status = BSP_NVM_NOTAVAIL;
  }
  else if (!eepromData[sect].current
           || (eepromData[sect].testStatus == BSP_NVM_BUSY))
  {
    status = BSP_NVM_BUSY;
  }
  else if ((address + length) > config->bufferSize)
  {
    status = BSP_NVM_RANGE;
  }
  else if (length && checksum)
  {
    uint8_t const * buffer = config->buffer;
    uint16_t temp;

    while (length >= sizeof(*checksum))
    {
      temp = buffer[address++];
      temp <<= 8;
      temp |= buffer[address++];

      *checksum += temp;

      length -= sizeof(*checksum);
    }
  }

  return status;
}

//******************************************************************************
uint32_t bsp_nvm_getSize(bsp_nvm_t sect)
{
  uint32_t size = 0;

  if ((uint32_t)sect < BSP_ARRAY_LEN(eepromConfig))
  {
    size = eepromConfig[sect].bufferSize;
  }

  return size;
}

//******************************************************************************
bsp_nvm_status_t bsp_nvm_startTest(bsp_nvm_t sect, uint16_t test)
{
  bsp_nvm_status_t returnStatus = BSP_NVM_BUSY;

  if (eepromData[sect].testStatus != BSP_NVM_BUSY)
  {
    eepromData[sect].testType = test;
    eepromData[sect].testStage = 0;
    eepromData[sect].testFailures = 0;
    eepromData[sect].testStatus = BSP_NVM_BUSY;
    returnStatus = BSP_NVM_OK;
  }

  BSP_DEBUG(("NVM%i Test %i started with status %i", sect + 1, test, returnStatus));

  return returnStatus;
}

//******************************************************************************
bsp_nvm_status_t bsp_nvm_getTestStatus(bsp_nvm_t sect, uint32_t *failures)
{
  bsp_nvm_status_t returnStatus = BSP_NVM_NOTAVAIL;

  if ((uint32_t)sect < BSP_ARRAY_LEN(eepromConfig))
  {
    returnStatus = eepromData[sect].testStatus;

    if (failures)
    {
      *failures = eepromData[sect].testFailures;
    }
  }

  return returnStatus;
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
*
*
* \param sect
* \param address
* \param length
* \param data
*
* \return bsp_nvm_status_t
*******************************************************************************/
static bsp_nvm_status_t nvm_read(bsp_nvm_t sect,
                                 uint32_t address,
                                 uint32_t length,
                                 uint8_t * data)
{
  bsp_nvm_status_t status = BSP_NVM_OK;
  nvm_eepromConfig_t const * config = &eepromConfig[sect];

  if ((address + length) > config->bufferSize)
  {
    status = BSP_NVM_RANGE;
  }
  else if (length)
  {
    uint8_t const * buffer = &config->buffer[address];

    while (length--)
    {
      *data++ = *buffer++;
    }
  }

  return status;
}

//******************************************************************************
/**
*
*
* \param sect
* \param address
* \param length
* \param data
*
* \return bsp_nvm_status_t
*******************************************************************************/
static bsp_nvm_status_t nvm_write(bsp_nvm_t sect,
                                  uint32_t address,
                                  uint32_t length,
                                  uint8_t  const * data)
{
  bsp_nvm_status_t status = BSP_NVM_OK;
  nvm_eepromConfig_t const * config = &eepromConfig[sect];

  if ((address + length) > config->bufferSize)
  {
    status = BSP_NVM_RANGE;
  }
  else if (length)
  {
    uint8_t * buffer = &config->buffer[address];
    uint32_t tempLength = length;

    while (tempLength--)
    {
      *buffer++ = *data++;
    }

    setWriteFlags(sect, address, length);
  }

  return status;
}

//******************************************************************************
/**
 *
 *
 * \param eepromIndex
 * \param address
 * \param length
 *
 * \return bool
 *******************************************************************************/
static bool findNexWrite(uint_fast16_t eepromIndex, uint32_t * address, uint32_t * length)
{
  bool success = false;
  uint_fast16_t i;
  nvm_eepromConfig_t const * config = &eepromConfig[eepromIndex];
  uint8_t * flags = config->flags;

  for (i = 0; i < eepromConfig->flagSize; i++)
  {
    // Find first Falgs byte with a flag set
    if (flags[i])
    {
      uint8_t flagMask = 1;
      uint32_t tempAddress = (config->pageSize * i * 8);

      // Find the first flag set
      while (flagMask && ((flags[i] & flagMask) == 0))
      {
        flagMask <<= 1;
        tempAddress += config->pageSize;
      }

      // Clear the flag
      flags[i] &= ~flagMask;

      *address = tempAddress;
      *length = config->pageSize;

      success = true;

      break;
    }
  }

  return success;
}

//******************************************************************************
/**
 *
 *
 * \param eepromIndex
 * \param address
 * \param length
 *
 * \return void
 *******************************************************************************/
static void setWriteFlags(uint_fast16_t eepromIndex, uint32_t address, uint32_t length)
{
  nvm_eepromConfig_t const * config = &eepromConfig[eepromIndex];
  uint8_t * flags = config->flags;
  uint8_t flagMask = 1;

  // Find first flag byte (8 page flags per byte)
  flags = &flags[address / (config->pageSize * 8)];

  // Find the first flag to set
  address %= (config->pageSize * 8);
  flagMask <<= (address / config->pageSize);

  // Adjust length  include begining byts of first page
  address %= config->pageSize;
  length += address;

  // Calc number of flags to set, add (config->pageSize - 1) to include last page
  length += (config->pageSize - 1);
  length /= config->pageSize;

  // Set the flags
  while (length--)
  {
    if (flagMask == 0)
    {
      flags++;
      flagMask = 1;
    }

    *flags |= flagMask;
    flagMask <<= 1;
  }
}

//******************************************************************************
/**
*
*
* \param sect
*
* \return void
*******************************************************************************/
static void runTest(bsp_nvm_t sect)
{
  if (eepromData[sect].testStatus == BSP_NVM_BUSY)
  {
    switch (eepromData[sect].testType)
    {
    case 0:
      runTest_0(sect);
      break;

    default:
      eepromData[sect].testStatus = BSP_NVM_FAIL;
      eepromData[sect].testStage = 0;
      eepromData[sect].testFailures = 0;
      break;
    }
  }
}

//******************************************************************************
/**
*
*
* \param sect
*
* \return void
*******************************************************************************/
static void runTest_0(bsp_nvm_t sect)
{
// 0x0102,0x0408, 0x1020,0x4080,
// 0xA55A,0xFEFD, 0xFBF7,0xEFDF,
// 0xBF7F,0x00FF
  static uint8_t testPattern[] =
  {
    0x02, 0x01, 0x08, 0x04, 0x20, 0x10, 0x80, 0x40,
    0x5A, 0xA5, 0xFD, 0xFE, 0xF7, 0xFB, 0xDF, 0xEF,
    0x7F, 0xBF, 0x00, 0xFF, 0x01, 0x02, 0x04, 0x08,
    0x5A, 0xA5, 0xFD, 0xFE, 0xF7, 0xFB, 0xDF, 0xEF,
  };
  nvm_test_0_stage_t stage = (nvm_test_0_stage_t)eepromData[sect].testStage;
  uint32_t address;
  bsp_nvm_status_t status;

  switch (stage)
  {
  case NVM_TEST_0_STAGE_INIT:

    address = 0;

    do
    {
      status = nvm_write(sect, address, sizeof(testPattern), testPattern);
      address += sizeof(testPattern);
    }
    while (status != BSP_NVM_RANGE);

    stage = NVM_TEST_0_STAGE_WRITE;
    BSP_DEBUG(("NVM%i Test 0 Init Stage complete", sect + 1));
    break;

  case NVM_TEST_0_STAGE_WRITE:
    if (!eepromData[sect].busy)
    {
      // Clear the EEPROM buffer
      memset(eepromConfig[sect].buffer, 0, eepromConfig[sect].bufferSize);

      // set current flag false to trigger re-read of eeprom
      eepromData[sect].current = false;

      stage = NVM_TEST_0_STAGE_READ;
      BSP_DEBUG(("NVM%i Test 0 Write Stage complete", sect + 1));
    }
    break;

  case NVM_TEST_0_STAGE_READ:
    if (!eepromData[sect].busy)
    {
      uint8_t * buffer = eepromConfig[sect].buffer;
      address = 0;

      while (address < eepromConfig[sect].bufferSize)
      {
        if (buffer[address] != testPattern[address % sizeof(testPattern)])
        {
          eepromData[sect].testFailures++;
        }
        buffer[address] = 0xFF;
        address++;
      }

      nvm_write(sect, 0, eepromConfig[sect].bufferSize, buffer);

      stage = NVM_TEST_0_STAGE_CLEAR;
      BSP_DEBUG(("NVM%i Test 0 Read Stage complete", sect + 1));
    }
    break;

  case NVM_TEST_0_STAGE_CLEAR:
    if (!eepromData[sect].busy)
    {
      eepromData[sect].testStatus = eepromData[sect].testFailures ?
                                    BSP_NVM_FAIL : BSP_NVM_OK;
      BSP_DEBUG(("NVM%i Test 0 complete. Status: %i, Failures: %i",
                 sect + 1,
                 eepromData[sect].testStatus,
                 eepromData[sect].testFailures));
    }
    break;

  default:
    eepromData[sect].testStatus = BSP_NVM_FAIL;
    break;
  }

  eepromData[sect].testStage = (uint32_t)stage;
}

