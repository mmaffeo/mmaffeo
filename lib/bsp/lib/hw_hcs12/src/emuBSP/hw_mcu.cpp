//******************************************************************************
/**
 * \file    hw_mcu.cpp
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Emulation of hw_mcu and hs_reset on BSP
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
#include "hw_mcu.h"
#include "hw_reset.h"
#include "bsp_mcu.h"
#include "bsp_dout.h"
#include "bsp_din.h"
#include "bsp_sdata.h"

uint8_t  bb_smode = 0;
uint8_t  ap_smode = 0;

uint8_t bservProg_protocolID  = 0x01;
uint8_t bservProg_options     = 0x4B;
uint8_t bservProg_customerID  = 0x01;
uint8_t bservProg_maxDataSize = 0x20;


////////////////////////////////////////////////////////////////////////////////////////////////////
// Green status LED functionality... (// Status LED not available on M4)

status_LED_t hw_mcu_heartbeatLED;
void status_LED_t::initialize(void){}
void status_LED_t::update(void){}
void status_LED_t::SetFlashRate(uint16_t periodmS){}


////////////////////////////////////////////////////////////////////////////////////////////////////
// hardware ID

//******************************************************************************
uint16_t hw_mcu_HardwareID(void)
{
  uint16_t hwID = 0;
  uint16_t mask = 1;

  for (uint_fast16_t din = BSP_DIN_HW_ID0; din <= BSP_DIN_HW_ID6; din++)
  {
    hwID |= bsp_din_GetValue((bsp_din_t)din) ? mask : 0;
    mask <<= 1;
  }

  return hwID;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Power hold circuitry

//******************************************************************************
void hw_mcu_SetPowerHold(bool state)
{
  bsp_dout_SetValue(BSP_DOUT_PWR_HOLD_ON, state);
}

//******************************************************************************
bool hw_mcu_GetPowerHold(void)
{
  return bsp_dout_GetValue(BSP_DOUT_PWR_HOLD_ON);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// hw_mcu task

//******************************************************************************
void hw_mcu_initialize(void)
{
  bsp_sdata_progParams_t progParams;

  bb_smode = (uint8_t)bsp_sdata_getBootBlockMode();
  ap_smode = bsp_sdata_getAppMode();

  bsp_sdata_getBBProgParams(&progParams);

  bservProg_protocolID  = progParams.protocolID;
  bservProg_options     = progParams.protocolOptions;
  bservProg_customerID  = progParams.customerID;
  bservProg_maxDataSize = progParams.dataSizeMax;
}

//******************************************************************************
void hw_mcu_update(void)
{
  bsp_sdata_setBootBlockMode((bsp_sdata_bbmode_t)bb_smode);
  bsp_sdata_setAppMode(ap_smode);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// hw_reset functins

//******************************************************************************
void hw_reset_force(uint8_t bb_smode_,
                    uint8_t ap_smode_)
{
  bb_smode = bb_smode_;
  ap_smode = ap_smode_;

  bsp_sdata_setBootBlockMode((bsp_sdata_bbmode_t)bb_smode);
  bsp_sdata_setAppMode(ap_smode);

  bsp_mcu_requestReset();
}

//******************************************************************************
uint16_t hw_reset_max_stack(void)
{
  return (uint16_t)bsp_mcu_maxStack();
}

