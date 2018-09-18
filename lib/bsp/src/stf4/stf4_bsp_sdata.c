//******************************************************************************
/**
 * \file    stf4_bsp_sdata.c
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   STM32F4xx Specific Saved Data Module Source
 * The Saved Data Module is used to share data between the bootloader and an
 * application
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

#define STF4_INTERNAL (1)
#include "stf4_bsp_sdata.h"
#include "stf4_cstartup.h"
#undef STF4_INTERNAL


#define BSP_SD_INIT_SIG             (0xA5A5A500)
#define BSP_SD_LENGTH               (0x100)

#define BSP_SD_NUM_CAN_TERMS        (8)


#ifndef BSP_SD_BB_MODE_DEFAULT
# define BSP_SD_BB_MODE_DEFAULT     (BSPSD_BB_MODE_NA)
#endif

#ifndef BSP_SD_AP_MODE_DEFAULT
# define BSP_SD_AP_MODE_DEFAULT     (0)
#endif

#ifndef BSP_SD_PP_PROTID_DEFAULT
# define BSP_SD_PP_PROTID_DEFAULT   (0x01)
#endif

#ifndef BSP_SD_PP_OPTIONS_DEFAULT
# define BSP_SD_PP_OPTIONS_DEFAULT  (0x4B)
#endif

#ifndef BSP_SD_PP_CUSTID_DEFAULT
# define BSP_SD_PP_CUSTID_DEFAULT   (0x01)
#endif

#ifndef BSP_SD_PP_SIZE_DEFAULT
# define BSP_SD_PP_SIZE_DEFAULT     (0x20)
#endif

#ifndef BSP_SD_CANTERM_DEFAULT
# define BSP_SD_CANTERM_DEFAULT     (0)
#endif


/// Saved Data Structure
typedef struct sdata_s
{
  uint32_t initSig;               ///< Initialization Signature
  uint32_t reserved_00;           ///< reserved_00
  uint32_t reserved_01;           ///< reserved_01
  uint32_t reserved_02;           ///< reserved_02

  uint8_t bbMode;                 ///< Bootblock Mode
  uint8_t apMode;                 ///< Application Mode
  uint8_t reserved_03;            ///< reserved_03
  uint8_t reserved_04;            ///< reserved_04

  uint8_t progProtocolID;         ///< Programming Protocol ID
  uint8_t progProtocolOptions;    ///< Programming Protocol Options
  uint8_t progCustomerID;         ///< Programming Protocol Customer ID
  uint8_t progDataSizeMax;        ///< Programming Protocol Data Size Max

  uint8_t canTermDisable;         ///< CAN Terminator Enable Flags

} sdata_t;

BSP_CTA(offsetof(sdata_t, initSig)              == 0  );
BSP_CTA(offsetof(sdata_t, bbMode)               == 16 );
BSP_CTA(offsetof(sdata_t, apMode)               == 17 );
BSP_CTA(offsetof(sdata_t, progProtocolID)       == 20 );
BSP_CTA(offsetof(sdata_t, progProtocolOptions)  == 21 );
BSP_CTA(offsetof(sdata_t, progCustomerID)       == 22 );
BSP_CTA(offsetof(sdata_t, progDataSizeMax)      == 23 );
BSP_CTA(offsetof(sdata_t, canTermDisable)       == 24 );
BSP_CTA(sizeof(sdata_t) <= BSP_SD_LENGTH);

//******************************************************************************
// Static Function Prototypes
//******************************************************************************


//******************************************************************************
// Static Variables
//******************************************************************************
static sdata_t * sdata = NULL;
static uint32_t sdataSize = 0;


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_sdata_init(void)
{
  sdata = (sdata_t *)cstartup_getSavedData(&sdataSize);

  if (sdataSize < BSP_SD_LENGTH)
  {
    sdata = NULL;
    BSP_DEBUG(("SDATA section too small"));
  }

  if (sdata != NULL)
  {
    bool sdataValid = (sdata->initSig == BSP_SD_INIT_SIG);

    if (!sdataValid)
    {
      memset(sdata, 0, BSP_SD_LENGTH);

      sdata->initSig = BSP_SD_INIT_SIG;

      sdata->bbMode = BSP_SD_BB_MODE_DEFAULT;
      sdata->apMode = BSP_SD_AP_MODE_DEFAULT;

      sdata->progProtocolID = BSP_SD_PP_PROTID_DEFAULT;
      sdata->progProtocolOptions = BSP_SD_PP_OPTIONS_DEFAULT;
      sdata->progCustomerID = BSP_SD_PP_CUSTID_DEFAULT;
      sdata->progDataSizeMax = BSP_SD_PP_SIZE_DEFAULT;

      sdata->canTermDisable = BSP_SD_CANTERM_DEFAULT;
    }

    BSP_DEBUG(("SDATA %s", sdataValid ? "recovered" : "set to defaults"));
  }
}

//******************************************************************************
void bsp_sdata_setAppMode(uint8_t mode)
{
  if (sdata != NULL)
  {
    sdata->apMode = mode;
  }
}

//******************************************************************************
uint8_t bsp_sdata_getAppMode(void)
{
  uint8_t apMode = BSP_SD_AP_MODE_DEFAULT;

  if (sdata != NULL)
  {
    apMode = sdata->apMode;
  }
  return apMode;
}

//******************************************************************************
void bsp_sdata_setBootBlockMode(bsp_sdata_bbmode_t mode)
{
  if (sdata != NULL)
  {
    sdata->bbMode = mode;
  }
}

//******************************************************************************
bsp_sdata_bbmode_t bsp_sdata_getBootBlockMode(void)
{
  bsp_sdata_bbmode_t bbMode = BSP_SD_BB_MODE_DEFAULT;

  if (sdata != NULL)
  {
    bbMode = (bsp_sdata_bbmode_t)sdata->bbMode;
  }

  return bbMode;
}

//******************************************************************************
void bsp_sdata_setBBProgParams(bsp_sdata_progParams_t const * params)
{
  if ((params != NULL) && (sdata != NULL))
  {
    sdata->progProtocolID = params->protocolID;
    sdata->progProtocolOptions = params->protocolOptions;
    sdata->progCustomerID = params->customerID;
    sdata->progDataSizeMax = params->dataSizeMax;
  }
}

//******************************************************************************
void bsp_sdata_getBBProgParams(bsp_sdata_progParams_t * params)
{
  if (params != NULL)
  {
    params->protocolID = BSP_SD_PP_PROTID_DEFAULT;
    params->protocolOptions = BSP_SD_PP_OPTIONS_DEFAULT;
    params->customerID = BSP_SD_PP_CUSTID_DEFAULT;
    params->dataSizeMax = BSP_SD_PP_SIZE_DEFAULT;

    if (sdata != NULL)
    {
      params->protocolID = sdata->progProtocolID;
      params->protocolOptions = sdata->progProtocolOptions;
      params->customerID = sdata->progCustomerID;
      params->dataSizeMax = sdata->progDataSizeMax;
    }
  }
}

//******************************************************************************
void bsp_sdata_setCanTermDisable(uint8_t port, bool disable)
{
  if ((sdata != NULL) && (port < BSP_SD_NUM_CAN_TERMS))
  {
    uint8_t mask = 0x01 << port;

    if (disable)
    {
      sdata->canTermDisable |= mask;
    }
    else
    {
      sdata->canTermDisable &= ~mask;
    }
  }
}

//******************************************************************************
bool bsp_sdata_getCanTermDisable(uint8_t port)
{
  uint8_t disableFlags = BSP_SD_CANTERM_DEFAULT;
  bool canPortTermDisabled = false;

  if (port < BSP_SD_NUM_CAN_TERMS)
  {
    uint8_t mask = 0x01 << port;

    if (sdata != NULL)
    {
      disableFlags = sdata->canTermDisable;
    }

    canPortTermDisabled = ((disableFlags & mask) != 0);
  }

  return canPortTermDisabled;
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************



