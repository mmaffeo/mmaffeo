//******************************************************************************
/**
 * \file    stf4_bsp_romBB.c
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
 ******************************************************************************/
#include "bsp_nvm.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bsp_common.h"

#include "stf4_fifo.h"

#define STF4_INTERNAL (1)
#include "stm32f4xx.h"
#include "stf4_bsp_rom.h"
#include "stf4_vectors.h"
#include "stf4_bsp_romBB.h"
#include "stf4_bsp_ecuid.h"
#undef STF4_INTERNAL

#ifndef BSP_FLASH_SIZE
# define BSP_FLASH_SIZE                   (1024 * 1024)
#endif

#if (BSP_FLASH_SIZE != (512 * 1024)) && (BSP_FLASH_SIZE != (1024 * 1024))
# error "BSP_FLASH_SIZE unsupported Flash Size"
#endif

#define STF4_BOOTBLOCK_START              (0x08000000)
#define STF4_BOOTBLOCK_SIZE               (32 * 1024)
#define STF4_BOOTBLOCK_END                (STF4_BOOTBLOCK_START + STF4_BOOTBLOCK_SIZE)

 // 64 bytes from end, checksum is 4 bytes so the sig can be up to 60
#define STF4_BOOTBLOCK_SIG_INDEX          (STF4_BOOTBLOCK_SIZE - 64)

#define STF4_FLASH_PROGRAM_ADDRESS_MASK   ((uint32_t)0xFFFFFFFC)

#define STF4_FLASH_PSIZE                  (2) // 2 - 32bit programming size

#define STF4_FLASH_KEY1                   ((uint32_t)0x45670123)    // x
#define STF4_FLASH_KEY2                   ((uint32_t)0xCDEF89AB)    // x
#define STF4_FLASH_OPT_KEY1               ((uint32_t)0x08192A3B)
#define STF4_FLASH_OPT_KEY2               ((uint32_t)0x4C5D6E7F)

#define STF4_FLASH_SR_EOP                 ((uint32_t)0x00000001)    // x
#define STF4_FLASH_SR_OPERR               ((uint32_t)0x00000002)    // x
#define STF4_FLASH_SR_WRPERR              ((uint32_t)0x00000010)    // x
#define STF4_FLASH_SR_PGAERR              ((uint32_t)0x00000020)    // x
#define STF4_FLASH_SR_PGPERR              ((uint32_t)0x00000040)    // x
#define STF4_FLASH_SR_PGSERR              ((uint32_t)0x00000080)    // x
#define STF4_FLASH_SR_BSY                 ((uint32_t)0x00010000)    // x

#define STF4_FLASH_CR_PG                  ((uint32_t)0x00000001)
#define STF4_FLASH_CR_SER                 ((uint32_t)0x00000002)
#define STF4_FLASH_CR_MER                 ((uint32_t)0x00000004)
#define STF4_FLASH_CR_SNB_MASK            ((uint32_t)0x000000F8)
#define STF4_FLASH_CR_SNB_SHIFT           (3)
#define STF4_FLASH_CR_PSIZE_MASK          ((uint32_t)0x00000300)
#define STF4_FLASH_CR_PSIZE_SHIFT         (8)
#define STF4_FLASH_CR_STRT                ((uint32_t)0x00010000)
#define STF4_FLASH_CR_EOPIE               ((uint32_t)0x01000000)    // x
#define STF4_FLASH_CR_ERRIE               ((uint32_t)0x02000000)    // x
#define STF4_FLASH_CR_LOCK                ((uint32_t)0x80000000)    // x

#define STF4_FLASH_OPTCR_OPTLOCK          ((uint32_t)0x00000001)
#define STF4_FLASH_OPTCR_OPTSTRT          ((uint32_t)0x00000002)
#define STF4_FLASH_OPTCR_BOR_LEV_MASK     ((uint32_t)0x0000000C)
#define STF4_FLASH_OPTCR_BOR_LEV_SHIFT    (2)
#define STF4_FLASH_OPTCR_WDG_SW           ((uint32_t)0x00000020)
#define STF4_FLASH_OPTCR_nRST_STOP        ((uint32_t)0x00000040)
#define STF4_FLASH_OPTCR_nRST_STDBY       ((uint32_t)0x00000080)
#define STF4_FLASH_OPTCR_RDP_MASK         ((uint32_t)0x0000FF00)
#define STF4_FLASH_OPTCR_RDP_SHIFT        (8)
#define STF4_FLASH_OPTCR_nWRP_MASK        ((uint32_t)0x0FFF0000)
#define STF4_FLASH_OPTCR_nWRP_SHIFT       (16)

#define STF4_FLASH_IS_ADDRESS(a)          ( (((a) >= 0x08000000) && ((a) < 0x080FFFFF)) \
                                            || (((a) >= 0x1FFF7800) && ((a) < 0x1FFF7A0F)) )

#define STF4_FLASH_PROGRAM_BUFFER_LEN     (4096)

#if 0
# warning "ROM Debug code enabled!"
# include "bsp_dout.h"
# define ROM_DEBUG_INIT()    do{ bsp_dout_initCh(BSP_DOUT_DEBUG1, false);   \
                               bsp_dout_initCh(BSP_DOUT_DEBUG2, false); }while(0)
# define ROM_DEBUG1_HIGH()   do{ bsp_dout_SetValue(BSP_DOUT_DEBUG1, true);  }while(0)
# define ROM_DEBUG1_LOW()    do{ bsp_dout_SetValue(BSP_DOUT_DEBUG1, false); }while(0)
# define ROM_DEBUG2_HIGH()   do{ bsp_dout_SetValue(BSP_DOUT_DEBUG2, true);  }while(0)
# define ROM_DEBUG2_LOW()    do{ bsp_dout_SetValue(BSP_DOUT_DEBUG2, false); }while(0)
#else
# define ROM_DEBUG_INIT()    ((void)0)   ///< Initialize ROM debug output
# define ROM_DEBUG1_HIGH()   ((void)0)   ///< Set ROM debug 1 output high
# define ROM_DEBUG1_LOW()    ((void)0)   ///< Set ROM debug 1 output low
# define ROM_DEBUG2_HIGH()   ((void)0)   ///< Set ROM debug 2 output high
# define ROM_DEBUG2_LOW()    ((void)0)   ///< Set ROM debug 2 output low
#endif


typedef struct programFifoEntry_s
{
  uint32_t address;
  uint32_t data;
} programFifoEntry_t;

//******************************************************************************
// Erase times with PSIZE = x32
//  16kB sector   - 250ms typ, 500ms max
//  64kB sector   - 550ms typ, 1100ms max
//  128kB sector  - 1000ms typ, 2000ms max
//
//******************************************************************************

//******************************************************************************
// Static Variables
//******************************************************************************

static uint32_t const deviceSize = BSP_FLASH_SIZE;

static programFifoEntry_t programFifoData[STF4_FLASH_PROGRAM_BUFFER_LEN];
bsp_fifo_t programFifo;

static uint32_t sectorSum[BSP_ARRAY_LEN(bsp_rom_sectorInfo)];
static volatile uint32_t eraseMask;

static char const expectedSignature[] = "This is a STM32F407 1MB Bootloader";
static uint8_t bbData[STF4_BOOTBLOCK_SIZE];
static bool bbDataValid = false;
static bool bbDataProgramming = false;

static uint16_t const writeProtectLocked = (~BSP_ROM_MASK_BOOTBLOCK & OB_WRP_Sector_All);
static uint16_t const writeProtectUnlocked = OB_WRP_Sector_All;

static uint8_t const optionByte0Data = (OB_IWDG_HW | OB_BOR_LEVEL2 | OB_STOP_NoRST | OB_STDBY_NoRST);
static uint8_t const optionByte0Mask = 0xEC;

//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void interceptBBData(uintptr_t * dest_address,
                            uint32_t * size,
                            uint8_t const ** src);
static void verifyBBData(void);
static bool verifyBBSignature(void);
static void calcSectorSums(void);
static void irqh_flash(void);

static bool checkErase(void);
static bool checkProgram(void);
static bool checkBBProgram(void);
static bool checkOptionBytes(void);

static void programWord(uint32_t address, uint32_t data);
static void eraseSector(uint32_t sector);
static void cleanControlReg(void);
static void populateFlashBuffer(uintptr_t destination,
                                uint32_t numWords,
                                uint8_t const * const srcStart,
                                uint8_t const * const srcEnd);

//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_romBB_init(void)
{
  ROM_DEBUG_INIT();
  ROM_DEBUG2_HIGH();

  bbDataValid = false;
  bbDataProgramming = false;
  memset(bbData, 0xFF, sizeof(bbData));

  calcSectorSums();

  if (bsp_romBB_checksum(BSP_ROM_MASK_ECUID) != 0)
  {
    bsp_ecuid_setInvalid(true);
  }

  bsp_fifo_init(&programFifo,
               programFifoData,
               sizeof(programFifoData),
               sizeof(programFifoData[0]));

  eraseMask = 0;

  vectors_setRamVector(FLASH_IRQn,  irqh_flash);

  FLASH_Unlock();
  // Enable End of Operation and Operation Error Interrupts
  FLASH->CR |= STF4_FLASH_CR_EOPIE | STF4_FLASH_CR_ERRIE;

  NVIC_EnableIRQ(FLASH_IRQn);

  ROM_DEBUG2_LOW();
}

//******************************************************************************
void bsp_romBB_run(void)
{
  // Kick off an interrupt to check for any required tasks
  NVIC_SetPendingIRQ(FLASH_IRQn);
}

//******************************************************************************
bool bsp_romBB_isBusy(void)
{
  return (((FLASH->SR & STF4_FLASH_SR_BSY) != 0) || bbDataProgramming);
}

//******************************************************************************
uint32_t bsp_romBB_checksum(uint32_t section_mask)
{
  uint32_t sectorMask = section_mask;
  uint32_t compareMask = 1;
  uint32_t checksum = 0;
  uint_fast16_t i;

  for (i = 0; i < BSP_ARRAY_LEN(bsp_rom_sectorInfo); i++)
  {
    if (sectorMask & compareMask)
    {
      checksum += sectorSum[i];
    }
    compareMask <<= 1;
  }

  return checksum;
}

//******************************************************************************
bsp_nvm_status_t bsp_romBB_erase(uint32_t section_mask)
{
  bsp_nvm_status_t status = BSP_NVM_OK;
  uint32_t sectorMask = section_mask;

  // Do not allow erasing any Bootblock sectors
  sectorMask &= ~BSP_ROM_MASK_BOOTBLOCK;

  NVIC_DisableIRQ(FLASH_IRQn);
  eraseMask |= sectorMask;

  NVIC_SetPendingIRQ(FLASH_IRQn);
  NVIC_EnableIRQ(FLASH_IRQn);

  return status;
}

//******************************************************************************
bsp_nvm_status_t bsp_romBB_program(uintptr_t dest_address, uint32_t size, uint8_t const * src)
{
  bsp_nvm_status_t status = BSP_NVM_FAIL;
  uint32_t numWords = 0;

  interceptBBData(&dest_address, &size, &src);

  if (size)
  {
    uint32_t destStartWord = dest_address / sizeof(uint32_t);
    uint32_t destEndWord  = ((dest_address + size) - 1) / sizeof(uint32_t);
    numWords = (destEndWord  - destStartWord ) + 1;
  }
  else
  {
    status = BSP_NVM_OK;
  }

  if (numWords && (numWords <= bsp_fifo_available(&programFifo)))
  {
    uint8_t const *srcStart = src;
    uint8_t const *srcEnd = (src + size) - 1;

    populateFlashBuffer(dest_address, numWords, srcStart, srcEnd);

    status = BSP_NVM_OK;
    NVIC_SetPendingIRQ(FLASH_IRQn);
  }

  return status;
}

//******************************************************************************
void bsp_romBB_programComplete(void)
{
  verifyBBData();
}

//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
* Strip Bootblock data out of write commands and put it into a separate buffer
*
* \param dest_address
* \param size
* \param src
*
* \return void
******************************************************************************/
static void interceptBBData(uintptr_t * dest_address,
                            uint32_t * size,
                            uint8_t const ** src)
{
  if ((*dest_address >= STF4_BOOTBLOCK_START)
      && (*dest_address < STF4_BOOTBLOCK_END))
  {
    uint32_t index = *dest_address - STF4_BOOTBLOCK_START;
    uint32_t maxSize = (STF4_BOOTBLOCK_END - *dest_address);
    uint32_t tempSize = (*size > maxSize) ? maxSize : *size;

    // Skip buffer write if buffer is already verified
    if (!bbDataValid)
    {
      memcpy(&bbData[index], *src, tempSize);
    }

    *src += tempSize;
    *dest_address += tempSize;
    *size -= tempSize;
  }
}

//******************************************************************************
/**
*
* \param
*
* \return void
 ******************************************************************************/
static void verifyBBData(void)
{
  if (!bbDataValid)
  {
    uint32_t length = sizeof(bbData) / sizeof(uint32_t);
    uint32_t const *data = (uint32_t *)bbData;
    uint32_t checkSum = 0;

    while (length--)
    {
      checkSum += *data++;
    }

    if (!checkSum && verifyBBSignature())
    {
      bbDataValid = true;
    }

    BSP_DEBUG(("Bootblock buffer %s", bbDataValid ? "valid" : "Invalid"));

    if (bbDataValid)
    {
      NVIC_SetPendingIRQ(FLASH_IRQn);
    }
  }
}

//******************************************************************************
/**
*
* \param
*
* \return bool
******************************************************************************/
static bool verifyBBSignature(void)
{
  uint32_t i;
  bool verified = true;
  char const * signature = (char *)&bbData[STF4_BOOTBLOCK_SIG_INDEX];

  for (i = 0; i < sizeof(expectedSignature); i++)
  {
    if (expectedSignature[i] != signature[i])
    {
      verified = false;
    }
  }

  BSP_DEBUG(("Bootblock signature %s", verified ? "verified" : "not verified"));

  return verified;
}

//******************************************************************************
/**
 * Calculate the checksum for each available sector
 *
 * \return void
 ******************************************************************************/
static void calcSectorSums(void)
{
  uint32_t i;
  uint32_t const *data;
  uint32_t length;

  for (i = 0; i < BSP_ARRAY_LEN(bsp_rom_sectorInfo); i++)
  {
    sectorSum[i] = 0;

    if (deviceSize >= bsp_rom_sectorInfo[i].minDeviceSize)
    {
      data = bsp_rom_sectorInfo[i].start;
      length = bsp_rom_sectorInfo[i].size / sizeof(uint32_t);

      while (length--)
      {
        sectorSum[i] += *data++;
      }
    }
    else
    {
      // Non zero default value for unavailable sectors
      sectorSum[i] = 0xA5A5A5A5;
    }
  }
}

//******************************************************************************
/**
 *
 *
 * \return void
 ******************************************************************************/
static void irqh_flash(void)
{
  uint32_t status = FLASH->SR;
  bool flashBusy;

  ROM_DEBUG1_HIGH();

  if (FLASH->SR & STF4_FLASH_SR_EOP)
  {
    // Clear end of operation interrupt
    FLASH->SR |= STF4_FLASH_SR_EOP;
  }

  // Check for operation error
  if (FLASH->SR & STF4_FLASH_SR_OPERR)
  {
    if (FLASH->SR & STF4_FLASH_SR_WRPERR)
    { // Write protect error
      FLASH->SR |= STF4_FLASH_SR_WRPERR;
    }

    if (FLASH->SR & STF4_FLASH_SR_PGAERR)
    { // Programming alignment error
      FLASH->SR |= STF4_FLASH_SR_PGAERR;
    }

    if (FLASH->SR & STF4_FLASH_SR_PGPERR)
    { // Programming parallelism error
      FLASH->SR |= STF4_FLASH_SR_PGPERR;
    }

    if (FLASH->SR & STF4_FLASH_SR_PGSERR)
    { // Programming sequence error
      FLASH->SR |= STF4_FLASH_SR_PGSERR;
    }

    // Clear operation errror interrupt
    FLASH->SR |= STF4_FLASH_SR_OPERR;
  }

  flashBusy = ((FLASH->SR & STF4_FLASH_SR_BSY) != 0);

  // If not busy, check if there are any sectors to erase
  if (!flashBusy)
  {
    flashBusy = checkErase();
  }

  // If still not busy, check if we need to program
  if (!flashBusy)
  {
    flashBusy = checkProgram();
  }

  // If still not busy, check if we need to program the Bootblock
  if (!flashBusy)
  {
    flashBusy = checkBBProgram();
  }

  // If still not busy, check Option Bytes (Write Protection, WD, BOR)
  if (!flashBusy)
  {
    flashBusy = checkOptionBytes();
  }

  // If still not busy, Clean the Control Registers
  if (!flashBusy)
  {
    cleanControlReg();
  }

  ROM_DEBUG1_LOW();
}

//******************************************************************************
/**
 *
 *
 * \return bool
 ******************************************************************************/
static bool checkErase(void)
{
  bool operationStarted = false;
  uint32_t compareMask = 1;
  uint32_t sector;

  for (sector = 0; (sector < BSP_ARRAY_LEN(bsp_rom_sectorInfo)) && eraseMask; sector++)
  {
    if (eraseMask & compareMask)
    {
      eraseMask &= ~compareMask;

      if (deviceSize >= bsp_rom_sectorInfo[sector].minDeviceSize)
      {
        eraseSector(sector);
        operationStarted = true;
        break;
      }
    }

    compareMask <<= 1;
  }

  return operationStarted;
}

//******************************************************************************
/**
 *
 *
 * \return bool
 ******************************************************************************/
static bool checkProgram(void)
{
  bool operationStarted = false;
  programFifoEntry_t programEntry;

  if (bsp_fifo_get(&programFifo, &programEntry))
  {
    programWord(programEntry.address, programEntry.data);
    operationStarted = true;
  }

  return operationStarted;
}

//******************************************************************************
/**
*
* \param
*
* \return bool
******************************************************************************/
static bool checkBBProgram(void)
{
  bool operationStarted = false;
  static uint32_t index = 0;

  if (bbDataValid)
  {
    if (!bbDataProgramming)
    {
      BSP_DEBUG(("Preparing to program bootblock"));
      bbDataProgramming = true;
      index = 0;

      // Unlock BB Flash sections
      FLASH_OB_Unlock();
      *(__IO uint16_t*)OPTCR_BYTE2_ADDRESS = writeProtectUnlocked;
      *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS |= FLASH_OPTCR_OPTSTRT;
      operationStarted = true;

      // Mark Bootblock sections to be erased
      eraseMask |= BSP_ROM_MASK_BOOTBLOCK;
    }
    else if (bbDataProgramming && (index < sizeof(bbData)))
    {
      uint32_t data = bbData[index + 3];
      data <<= 8;
      data |= bbData[index + 2];
      data <<= 8;
      data |= bbData[index + 1];
      data <<= 8;
      data |= bbData[index];

      programWord(STF4_BOOTBLOCK_START + index, data);
      operationStarted = true;
      index += sizeof(uint32_t);
    }
    else
    {
      BSP_DEBUG(("Bootblock program complete"));
      bbDataProgramming = false;
      bbDataValid = false;
    }
  }

  return operationStarted;
}

//******************************************************************************
/**
* Check the Options Bytes (Write Protection, WD, BOR)
*
* \return bool
******************************************************************************/
static bool checkOptionBytes(void)
{
  bool operationStarted = false;
  uint16_t currentWriteProtect;
  uint8_t currentOptionByte0;

  FLASH_OB_Unlock();

  currentWriteProtect = FLASH_OB_GetWRP();

  currentOptionByte0 = *(__IO uint8_t*)OPTCR_BYTE0_ADDRESS;
  currentOptionByte0 &= optionByte0Mask;

  if ((writeProtectLocked != currentWriteProtect)
      || (currentOptionByte0 != optionByte0Data))
  {
    //BSP_DEBUG(("Bootblock sectors write protected"));
    *(__IO uint16_t*)OPTCR_BYTE2_ADDRESS = writeProtectLocked;

    *(__IO uint8_t*)OPTCR_BYTE0_ADDRESS &= ~optionByte0Mask;
    *(__IO uint8_t*)OPTCR_BYTE0_ADDRESS |= optionByte0Data;

    BSP_DEBUG(("New Option Bytes: 0x%08X", *(__IO uint32_t*)OPTCR_BYTE0_ADDRESS));

    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS |= FLASH_OPTCR_OPTSTRT;
    operationStarted = true;
  }

  // Don't lock the flash control reg while busy or the core will halt
  return operationStarted;
}

//******************************************************************************
/**
 *
 *
 * \param address
 * \param data
 *
 * \return void
 ******************************************************************************/
static void programWord(uint32_t address, uint32_t data)
{
  // Force 4 byte alignment
  address &= STF4_FLASH_PROGRAM_ADDRESS_MASK;

  // Unlock the Control Register
  if((FLASH->CR & STF4_FLASH_CR_LOCK))
  {
    FLASH->KEYR = STF4_FLASH_KEY1;
    FLASH->KEYR = STF4_FLASH_KEY2;
  }

  FLASH->CR &= (~STF4_FLASH_CR_PG);
  FLASH->CR &= (~STF4_FLASH_CR_MER);
  FLASH->CR &= (~STF4_FLASH_CR_SER);
  FLASH->CR &= (~STF4_FLASH_CR_SNB_MASK);

  FLASH->CR |= STF4_FLASH_CR_PG;
  *(__IO uint32_t*)address = data;

  // Don't lock the flash control reg while busy or the core will halt
}

//******************************************************************************
/**
 *
 *
 * \param sector
 *
 * \return void
 ******************************************************************************/
static void eraseSector(uint32_t sector)
{
  sector <<= STF4_FLASH_CR_SNB_SHIFT;
  sector &= STF4_FLASH_CR_SNB_MASK;

  // Unlock the Control Register
  if((FLASH->CR & STF4_FLASH_CR_LOCK))
  {
    FLASH->KEYR = STF4_FLASH_KEY1;
    FLASH->KEYR = STF4_FLASH_KEY2;
  }

  FLASH->CR &= (~STF4_FLASH_CR_PG);
  FLASH->CR &= (~STF4_FLASH_CR_MER);
  FLASH->CR &= (~STF4_FLASH_CR_SER);
  FLASH->CR &= (~STF4_FLASH_CR_SNB_MASK);

  FLASH->CR |= STF4_FLASH_CR_SER | sector;
  FLASH->CR |= STF4_FLASH_CR_STRT;

  // Don't lock the flash control reg while busy or the core will halt
}

//******************************************************************************
/**
 *
 *
 * \return void
 ******************************************************************************/
static void cleanControlReg(void)
{
  uint32_t psize = STF4_FLASH_PSIZE;
  psize <<= STF4_FLASH_CR_PSIZE_SHIFT;
  psize &= STF4_FLASH_CR_PSIZE_MASK;

  FLASH_Unlock();

  // Enable End of Operation and Operation Error Interrupts
  FLASH->CR |= STF4_FLASH_CR_EOPIE | STF4_FLASH_CR_ERRIE;

  FLASH->CR &= (~STF4_FLASH_CR_PG);
  FLASH->CR &= (~STF4_FLASH_CR_MER);
  FLASH->CR &= (~STF4_FLASH_CR_SER);
  FLASH->CR &= (~STF4_FLASH_CR_SNB_MASK);
  FLASH->CR &= (~STF4_FLASH_CR_PSIZE_MASK);
  FLASH->CR |= psize;
  FLASH->CR |= STF4_FLASH_CR_LOCK;

  FLASH_OB_Unlock();
  FLASH_OB_Lock();

  FLASH_Lock();
}

//******************************************************************************
/**
 *
 *
 * \param destination
 * \param numWords
 * \param srcStart
 * \param srcEnd
 *
 * \return void
 ******************************************************************************/
static void populateFlashBuffer(uintptr_t destination,
                                uint32_t numWords,
                                uint8_t const * const srcStart,
                                uint8_t const * const srcEnd)
{
  uint_fast16_t i;
  programFifoEntry_t programEntry;
  uint8_t const *source = srcStart;
  bool srcInRange;

  // 4 byte align src
  source -= (destination & ~STF4_FLASH_PROGRAM_ADDRESS_MASK);
  programEntry.address = destination & STF4_FLASH_PROGRAM_ADDRESS_MASK;

  while (numWords--)
  {
    programEntry.data = 0;

    // Jump ahead so we can populate word MSByte first (3,2,1,0, 7,6,5,4, ...)
    source += sizeof(uint32_t);

    for (i = 0; i < sizeof(uint32_t); i++)
    { // Construct word, 1 byte at a time
      source--;
      srcInRange = ((source >= srcStart) && (source <= srcEnd));
      programEntry.data  <<= 8;
      programEntry.data |= (srcInRange ? *source : 0xFF);
    }

    bsp_fifo_put(&programFifo, &programEntry);

    programEntry.address += sizeof(uint32_t);
    source += sizeof(uint32_t);
  }
}

