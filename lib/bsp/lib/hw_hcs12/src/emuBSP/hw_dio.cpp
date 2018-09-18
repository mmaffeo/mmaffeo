//******************************************************************************
/**
 * \file    hw_dio.cpp
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Emulation of hw_dio on BSP
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
#include "hw_dio.h"
#include <stdint.h>

#include "bsp_din.h"
#include "bsp_dout.h"
#include "bsp_sdata.h"


//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void dinUpdate(void);
static void doutUpdate(void);
static void canTermUpdate(void);
static void hw_din_SetValue(hw_din_ch_t ch, bool value);

//******************************************************************************
// Static Variables
//******************************************************************************
static uint16_t hw_din_data[HW_DIN_BANK_QTY];
static uint16_t hw_dout_data[HW_DOUT_BANK_QTY];

//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
bool hw_din_GetValue(hw_din_ch_t ch)
{
  uint8_t bank = (uint8_t)  ch >> 4;
  uint16_t mask = 0x01u << ((uint8_t)ch  & 0x0F);

  return hw_din_data[bank] & mask ? true : false ;
}

//******************************************************************************
uint16_t hw_din_GetBank(uint16_t bank)
{
  return hw_din_data[bank];
}

//******************************************************************************
void hw_dout_SetValue(hw_dout_ch_t ch, bool value)
{
  uint8_t bank = (uint8_t) ch >> 4;
  uint16_t mask = 0x01 << ((uint8_t)ch  & 0x0F);

  if (value)
  {
    hw_dout_data[bank] |= mask;
  }
  else
  {
    hw_dout_data[bank] &= ~mask;
  }
}

//******************************************************************************
bool hw_dout_GetValue(hw_dout_ch_t ch )
{
  uint8_t bank = (uint8_t) ch >> 4;
  uint16_t mask = 0x01 << ((uint8_t)ch  & 0x0F);

  return hw_dout_data[bank]&mask ? true: false;
}

//******************************************************************************
uint16_t hw_dout_GetBank(uint8_t bank)
{
  return hw_dout_data[bank];
}

//******************************************************************************
void hw_dout_SetBank(uint8_t bank, uint16_t data)
{
  hw_dout_data[bank] = data;
}

//******************************************************************************
void hw_dio_initialize(void)
{
  //Need to initialize hw_dout wetting currents since bsp turns them on by default - AL
  hw_dout_SetValue(HWC_DOUT_WC_ON1_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_ON1));
  hw_dout_SetValue(HWC_DOUT_WC_ON2_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_ON2));
  hw_dout_SetValue(HWC_DOUT_WC_ON3_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_ON3));
  hw_dout_SetValue(HWC_DOUT_WC_ON4_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_ON4));
  hw_dout_SetValue(HWC_DOUT_WC_ON5_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_ON5));
  hw_dout_SetValue(HWC_DOUT_WC_ON6_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_ON6));
  hw_dout_SetValue(HWC_DOUT_WC_ON7_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_ON7));
  hw_dout_SetValue(HWC_DOUT_WC_ON8_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_ON8));
  hw_dout_SetValue(HWC_DOUT_WC_CONFIG1_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_CONFIG1));
  hw_dout_SetValue(HWC_DOUT_WC_CONFIG2_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_CONFIG2));
  hw_dout_SetValue(HWC_DOUT_WC_CONFIG3_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_CONFIG3));
  hw_dout_SetValue(HWC_DOUT_WC_CONFIG4_AUTO, bsp_dout_getWettingCurrentEnable(BSP_DOUT_WC_CONFIG4));

  hw_dio_update();

}

//******************************************************************************
void hw_dio_update(void)
{
  dinUpdate();
  doutUpdate();
  canTermUpdate();
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
static void dinUpdate(void)
{
  // serial latch 1
  hw_din_SetValue(HWC_DIN_NU1,           false);
  hw_din_SetValue(HWC_DIN_NU2,           false);
  hw_din_SetValue(HWC_DIN18,             bsp_din_GetValue(BSP_DIN_DIN18));
  hw_din_SetValue(HWC_DIN17,             bsp_din_GetValue(BSP_DIN_DIN17));
  hw_din_SetValue(HWC_DIN16,             bsp_din_GetValue(BSP_DIN_DIN16));
  hw_din_SetValue(HWC_DIN15,             bsp_din_GetValue(BSP_DIN_DIN15));
  hw_din_SetValue(HWC_DIN14,             bsp_din_GetValue(BSP_DIN_DIN14));
  hw_din_SetValue(HWC_DIN13,             bsp_din_GetValue(BSP_DIN_DIN13));

  // serial latch 2
  hw_din_SetValue(HWC_DIN12,             bsp_din_GetValue(BSP_DIN_DIN12));
  hw_din_SetValue(HWC_DIN11,             bsp_din_GetValue(BSP_DIN_DIN11));
  hw_din_SetValue(HWC_DIN10,             bsp_din_GetValue(BSP_DIN_DIN10));
  hw_din_SetValue(HWC_DIN09,             bsp_din_GetValue(BSP_DIN_DIN09));
  hw_din_SetValue(HWC_DIN08,             bsp_din_GetValue(BSP_DIN_DIN08));
  hw_din_SetValue(HWC_DIN07,             bsp_din_GetValue(BSP_DIN_DIN07));
  hw_din_SetValue(HWC_DIN06,             bsp_din_GetValue(BSP_DIN_DIN06));
  hw_din_SetValue(HWC_DIN05,             bsp_din_GetValue(BSP_DIN_DIN05));

  // serial latch 3
  hw_din_SetValue(HWC_DIN_LC_HSD8_DFBK,  bsp_din_GetValue(BSP_DIN_LC_HSD8_DFBK));
  hw_din_SetValue(HWC_DIN_LC_HSD7_DFBK,  bsp_din_GetValue(BSP_DIN_LC_HSD7_DFBK));
  hw_din_SetValue(HWC_DIN_LC_HSD6_DFBK,  bsp_din_GetValue(BSP_DIN_LC_HSD6_DFBK));
  hw_din_SetValue(HWC_DIN_LC_HSD5_DFBK,  bsp_din_GetValue(BSP_DIN_LC_HSD5_DFBK));
  hw_din_SetValue(HWC_DIN_LC_HSD4_DFBK,  bsp_din_GetValue(BSP_DIN_LC_HSD4_DFBK));
  hw_din_SetValue(HWC_DIN_LC_HSD3_DFBK,  bsp_din_GetValue(BSP_DIN_LC_HSD3_DFBK));
  hw_din_SetValue(HWC_DIN_LC_HSD2_DFBK,  bsp_din_GetValue(BSP_DIN_LC_HSD2_DFBK));
  hw_din_SetValue(HWC_DIN_LC_HSD1_DFBK,  bsp_din_GetValue(BSP_DIN_LC_HSD1_DFBK));
}

//******************************************************************************
static void doutUpdate(void)
{
  // >>>>>>>>BANK0
  bsp_dout_SetValue(BSP_DOUT_HC_LSD1_CMD,             hw_dout_GetValue(HWC_DOUT_HC_LSD1_CMD));
  bsp_dout_SetValue(BSP_DOUT_HC_LSD2_CMD,             hw_dout_GetValue(HWC_DOUT_HC_LSD2_CMD));
  bsp_dout_SetValue(BSP_DOUT_HC_LSD3_CMD,             hw_dout_GetValue(HWC_DOUT_HC_LSD3_CMD));
  bsp_dout_SetValue(BSP_DOUT_HC_LSD4_CMD,             hw_dout_GetValue(HWC_DOUT_HC_LSD4_CMD));
  bsp_dout_SetValue(BSP_DOUT_HC_LSD5_CMD,             hw_dout_GetValue(HWC_DOUT_HC_LSD5_CMD));
  bsp_dout_SetValue(BSP_DOUT_HC_LSD6_CMD,             hw_dout_GetValue(HWC_DOUT_HC_LSD6_CMD));
  // Ignore Unused output                             hw_dout_GetValue(HWC_DOUT_NU1));
  // Ignore Unused output                             hw_dout_GetValue(HWC_DOUT_NU2));
  bsp_dout_SetValue(BSP_DOUT_LC_HSD1_CMD,             hw_dout_GetValue(HWC_DOUT_LC_HSD1_CMD));
  bsp_dout_SetValue(BSP_DOUT_LC_HSD3_CMD,             hw_dout_GetValue(HWC_DOUT_LC_HSD3_CMD));
  bsp_dout_SetValue(BSP_DOUT_LC_HSD5_CMD,             hw_dout_GetValue(HWC_DOUT_LC_HSD5_CMD));
  bsp_dout_SetValue(BSP_DOUT_LC_HSD7_CMD,             hw_dout_GetValue(HWC_DOUT_LC_HSD7_CMD));
  bsp_dout_SetValue(BSP_DOUT_DIN01_ENABLE,            hw_dout_GetValue(HWC_DOUT_DIN01_ENABLE));
  bsp_dout_SetValue(BSP_DOUT_DIN02_ENABLE,            hw_dout_GetValue(HWC_DOUT_DIN02_ENABLE));
  bsp_dout_SetValue(BSP_DOUT_DIN03_ENABLE,            hw_dout_GetValue(HWC_DOUT_DIN03_ENABLE));
  bsp_dout_SetValue(BSP_DOUT_DIN04_ENABLE,            hw_dout_GetValue(HWC_DOUT_DIN04_ENABLE));

  // >>>>>>>>BANK1
  bsp_dout_SetValue(BSP_DOUT_LC_HSD2_CMD,             hw_dout_GetValue(HWC_DOUT_LC_HSD2_CMD));
  bsp_dout_SetValue(BSP_DOUT_LC_HSD4_CMD,             hw_dout_GetValue(HWC_DOUT_LC_HSD4_CMD));
  bsp_dout_SetValue(BSP_DOUT_LC_HSD6_CMD,             hw_dout_GetValue(HWC_DOUT_LC_HSD6_CMD));
  bsp_dout_SetValue(BSP_DOUT_LC_HSD8_CMD,             hw_dout_GetValue(HWC_DOUT_LC_HSD8_CMD)); 
  bsp_dout_SetValue(BSP_DOUT_CAN_TERM_OFF1,           hw_dout_GetValue(HWC_DOUT_CAN_TERM_OFF1));
  bsp_dout_SetValue(BSP_DOUT_CAN_TERM_OFF2,           hw_dout_GetValue(HWC_DOUT_CAN_TERM_OFF2));
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_ON1,      hw_dout_GetValue(HWC_DOUT_WC_ON1_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_ON1,                  hw_dout_GetValue(HWC_DOUT_WC_ON1));
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_ON2,      hw_dout_GetValue(HWC_DOUT_WC_ON2_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_ON2,                  hw_dout_GetValue(HWC_DOUT_WC_ON2));
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_ON3,      hw_dout_GetValue(HWC_DOUT_WC_ON3_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_ON3,                  hw_dout_GetValue(HWC_DOUT_WC_ON3));
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_ON4,      hw_dout_GetValue(HWC_DOUT_WC_ON4_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_ON4,                  hw_dout_GetValue(HWC_DOUT_WC_ON4));
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_ON5,      hw_dout_GetValue(HWC_DOUT_WC_ON5_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_ON5,                  hw_dout_GetValue(HWC_DOUT_WC_ON5));

  // >>>>>>>>BANK2
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_ON6,      hw_dout_GetValue(HWC_DOUT_WC_ON6_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_ON6,                  hw_dout_GetValue(HWC_DOUT_WC_ON6));
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_ON7,      hw_dout_GetValue(HWC_DOUT_WC_ON7_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_ON7,                  hw_dout_GetValue(HWC_DOUT_WC_ON7));
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_ON8,      hw_dout_GetValue(HWC_DOUT_WC_ON8_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_ON8,                  hw_dout_GetValue(HWC_DOUT_WC_ON8));

  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_CONFIG1,  hw_dout_GetValue(HWC_DOUT_WC_CONFIG1_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_CONFIG1,              hw_dout_GetValue(HWC_DOUT_WC_CONFIG1));
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_CONFIG2,  hw_dout_GetValue(HWC_DOUT_WC_CONFIG2_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_CONFIG2,              hw_dout_GetValue(HWC_DOUT_WC_CONFIG2));
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_CONFIG3,  hw_dout_GetValue(HWC_DOUT_WC_CONFIG3_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_CONFIG3,              hw_dout_GetValue(HWC_DOUT_WC_CONFIG3));
  bsp_dout_wettingCurrentEnable(BSP_DOUT_WC_CONFIG4,  hw_dout_GetValue(HWC_DOUT_WC_CONFIG4_AUTO));
  bsp_dout_SetValue(BSP_DOUT_WC_CONFIG4,              hw_dout_GetValue(HWC_DOUT_WC_CONFIG4));

}

//******************************************************************************
static void canTermUpdate(void)
{
  bool can1Disable = hw_dout_GetValue(HWC_DOUT_CAN_TERM_OFF1);
  bool can2Disable = hw_dout_GetValue(HWC_DOUT_CAN_TERM_OFF2);

  bsp_sdata_setCanTermDisable(0, can1Disable);
  bsp_sdata_setCanTermDisable(1, can2Disable);
}

//******************************************************************************
static void hw_din_SetValue(hw_din_ch_t ch, bool value)
{
  uint8_t bank = (uint8_t) ch >> 4;
  uint16_t mask = 0x01 << ((uint8_t)ch  & 0x0F);

  if (value)
  {
    hw_din_data[bank] |= mask;
  }
  else
  {
    hw_din_data[bank] &= ~mask;
  }
}

