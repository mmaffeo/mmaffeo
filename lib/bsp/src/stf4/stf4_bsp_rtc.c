 //******************************************************************************
/**
 * \file    stf4_bsp_RTC.c
 * \author  Chad Swenson
 * \date    September 2014
 * \brief   STM32F4xx Specific RTC
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

#include "bsp_common.h"

#define STF4_INTERNAL (1)
#include "stf4_bsp_rtc.h"
#include "stm32f4xx.h"
#undef STF4_INTERNAL

// TODO loss of switched power for longer than 24 hour will cause corruption


//******************************************************************************
// Defines
//******************************************************************************

// Leap year every 4 years
//  Skip the leap year every 100th year, unless it is a 400th year
//  97 leap years every 400 years or 365.2425 days per year
// #define YEAR_TO_DAYS(y) ( ((y) * 365) + ((y) / 4) - ((y) / 100) + ((y) / 400) )


#define RTC_INIT_CHECK_DATA   (0x32F2)
#define RTC_INIT_CHECK_REG    (RTC_BKP_DR0)
#define RTC_TIME_BKP_REG      (RTC_BKP_DR1)
#define RTC_DTIME_BKP_REG     (RTC_BKP_DR2)
#define RTC_DEFAULT_TIME      (0)

#define RTC_TIME_OVERFLOW     (24 * 60 * 60)

#define LSE_OSC_TIMEOUT       (100)       // TODO adjust this time


//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void rtcUpdate(void);
static void decomposeTime(RTC_TimeTypeDef * RTC_Time, uint32_t time);
static uint32_t composeTime(RTC_TimeTypeDef const * RTC_Time);

//******************************************************************************
// Static Variables
//******************************************************************************
static bool rtcReady = false;

//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_rtc_init(void)
{
  uint_fast16_t i = 0;

  rtcReady = false;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  PWR_BackupAccessCmd(ENABLE);

  // Enable the BKPSRAM clock and backup regulator to test draw on holdup
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_BKPSRAM, ENABLE);
  PWR_BackupRegulatorCmd(ENABLE);

  // Check if the RTC needs to be initialized
  if (RTC_ReadBackupRegister(RTC_INIT_CHECK_REG) != RTC_INIT_CHECK_DATA)
  {
    RTC_InitTypeDef   RTC_InitStruct;

    RCC_LSEConfig(RCC_LSE_ON);

    while (!rtcReady && (++i < LSE_OSC_TIMEOUT))
    {
      rtcReady = (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != RESET);
    }

    if (rtcReady)
    {
      RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

      RCC_RTCCLKCmd(ENABLE);

      RTC_WaitForSynchro();

      RTC_StructInit(&RTC_InitStruct);
      // ck_spre(1Hz) = LSE /(RTC_AsynchPrediv + 1)*(RTC_SynchPrediv + 1)
      RTC_InitStruct.RTC_AsynchPrediv = 0x7F;
      RTC_InitStruct.RTC_SynchPrediv =  0xFF;
      RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_24;
      RTC_Init(&RTC_InitStruct);

      bsp_rtc_set(RTC_DEFAULT_TIME);

      // Access disabled by bsp_rtc_set(), reenable it
      PWR_BackupAccessCmd(ENABLE);

      RTC_WriteBackupRegister(RTC_DTIME_BKP_REG, 0);

      RTC_WriteBackupRegister(RTC_INIT_CHECK_REG, RTC_INIT_CHECK_DATA);
    }
    else
    {
      RTC_WriteBackupRegister(RTC_INIT_CHECK_REG, 0);
      RTC_WriteBackupRegister(RTC_TIME_BKP_REG, 0);
      RTC_WriteBackupRegister(RTC_DTIME_BKP_REG, 0);
    }
  }
  else
  {
    uint32_t lastTime;
    uint32_t time;

    rtcReady = true;

    lastTime = RTC_ReadBackupRegister(RTC_TIME_BKP_REG);
    time = bsp_rtc_get();

    // The bootloader may have already updated the downtime
    if (time > lastTime)
    {
      time -= lastTime;

      // Access disabled by bsp_rtc_get(), reenable it
      PWR_BackupAccessCmd(ENABLE);
      RTC_WriteBackupRegister(RTC_DTIME_BKP_REG, time);
    }
  }


  PWR_BackupAccessCmd(DISABLE);
}

//******************************************************************************
void bsp_rtc_run(void)
{
  rtcUpdate();
}

//******************************************************************************
void bsp_rtc_set(uint32_t time)
{
  if (rtcReady)
  {
    static RTC_TimeTypeDef RTC_TimeStruct;

    decomposeTime(&RTC_TimeStruct, time);

    RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);

    PWR_BackupAccessCmd(ENABLE);
    RTC_WriteBackupRegister(RTC_TIME_BKP_REG, time);
    PWR_BackupAccessCmd(DISABLE);
  }
}

//******************************************************************************
uint32_t bsp_rtc_get(void)
{
  rtcUpdate();

  return RTC_ReadBackupRegister(RTC_TIME_BKP_REG);
}

//******************************************************************************
uint32_t bsp_rtc_getDownTime(void)
{
  return RTC_ReadBackupRegister(RTC_DTIME_BKP_REG);
}

//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void rtcUpdate(void)
{
  if (rtcReady)
  {
    static RTC_TimeTypeDef RTC_TimeStruct;
    uint32_t time = RTC_ReadBackupRegister(RTC_TIME_BKP_REG);
    uint32_t rtcTime = time % RTC_TIME_OVERFLOW;
    uint32_t rtcRead;

    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);

    rtcRead = composeTime(&RTC_TimeStruct);

    if (rtcRead != rtcTime)
    {
      uint32_t delta = rtcRead;

      if (delta < rtcTime)
      {
        delta += RTC_TIME_OVERFLOW;
      }

      delta -= rtcTime;
      time += delta;

      PWR_BackupAccessCmd(ENABLE);
      RTC_WriteBackupRegister(RTC_TIME_BKP_REG, time);
      PWR_BackupAccessCmd(DISABLE);
    }
  }
}

//******************************************************************************
/**
 *
 *
 * \param RTC_Time
 * \param time
 *
 * \return void
 *******************************************************************************/
static void decomposeTime(RTC_TimeTypeDef * RTC_Time, uint32_t time)
{
  uint32_t tempTime = time;

  RTC_TimeStructInit(RTC_Time);

  RTC_Time->RTC_Seconds = (tempTime % 60);
  tempTime /= 60;
  RTC_Time->RTC_Minutes = (tempTime % 60);
  tempTime /= 60;
  RTC_Time->RTC_Hours   = (tempTime % 24);
}

//******************************************************************************
/**
 *
 *
 * \param RTC_Time
 *
 * \return uint32_t
 *******************************************************************************/
static uint32_t composeTime(RTC_TimeTypeDef const * RTC_Time)
{
  uint32_t time;
  uint32_t tempU32;

  time = RTC_Time->RTC_Seconds;

  tempU32 = RTC_Time->RTC_Minutes;
  tempU32 *= 60;
  time += tempU32;

  tempU32 = RTC_Time->RTC_Hours;
  tempU32 *= (60 * 60);
  time += tempU32;

  return time;
}


