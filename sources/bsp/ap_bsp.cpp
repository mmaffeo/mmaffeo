//******************************************************************************
/**
 * \file    ap_bsp.cpp
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   Application Specific BSP
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
#include "ap_bsp.h"
#include "bsp_common.h"
#include "bsp_rtc.h"
#include "bsp_com.h"
#include "bsp_mcu.h"
#include "bsp_clock.h"
#include "bsp_ecuid.h"
#include "bsp_sdata.h"
#include "bsp_rom.h"
#include "bsp_romBB.h"
#include "bsp_can.h"
#include "bsp_adc.h"
#include "bsp_din.h"
#include "bsp_dout.h"
#include "bsp_fin.h"
#include "bsp_pwm.h"
#include "bsp_nvm.h"
#include "ap_cdata.h"

#ifdef BSP_DEBUG_PORT
# warning "Debug code enabled"
#include <stdio.h>
#include <stdarg.h>
#endif


//******************************************************************************
// Defines
//******************************************************************************


//******************************************************************************
// Static Variables
//******************************************************************************
#ifdef BSP_DEBUG_PORT
static char debugBuffer[256];
#endif

static bsp_adc_t const bsp_adcEnable[] =
{
  BSP_ADC_AIN01, BSP_ADC_AIN02, BSP_ADC_AIN03, BSP_ADC_AIN04,
  BSP_ADC_AIN05, BSP_ADC_AIN06, BSP_ADC_AIN07, BSP_ADC_AIN08,
  BSP_ADC_AIN09, BSP_ADC_AIN10, BSP_ADC_AIN11, BSP_ADC_AIN12,
  BSP_ADC_AIN13, BSP_ADC_FIN01_AFBK, BSP_ADC_FIN03_AFBK, BSP_ADC_FIN04_AFBK,
  BSP_ADC_HC_HSD1_AFBK, BSP_ADC_HC_HSD2_AFBK, BSP_ADC_HC_HSD3_AFBK, BSP_ADC_HC_HSD4_AFBK,
  BSP_ADC_HC_HSD5_AFBK, BSP_ADC_HC_HSD6_AFBK, BSP_ADC_HC_HSD7_AFBK, BSP_ADC_HC_HSD8_AFBK,
  BSP_ADC_HC_LSD1_IFBK, BSP_ADC_HC_LSD2_IFBK,  BSP_ADC_HC_LSD3_IFBK, BSP_ADC_HC_LSD4_IFBK,
  BSP_ADC_HC_LSD5_IFBK, BSP_ADC_HC_LSD6_IFBK,
  BSP_ADC_VSENSOR1_AFBK, BSP_ADC_VBAT_AFBK_V, BSP_ADC_VSW_AFBK_V,
};

static bsp_din_t const bsp_dinEnable[] =
{
  //BSP_DIN_DIN01, BSP_DIN_DIN02, BSP_DIN_DIN03, BSP_DIN_DIN04,
  BSP_DIN_DIN05, BSP_DIN_DIN06, BSP_DIN_DIN07, BSP_DIN_DIN08,
  BSP_DIN_DIN09, BSP_DIN_DIN10, BSP_DIN_DIN11, BSP_DIN_DIN12,
  BSP_DIN_DIN13, BSP_DIN_DIN14, BSP_DIN_DIN15, BSP_DIN_DIN16,
  BSP_DIN_DIN17, BSP_DIN_DIN18,
  BSP_DIN_LC_HSD1_DFBK, BSP_DIN_LC_HSD2_DFBK, BSP_DIN_LC_HSD3_DFBK, BSP_DIN_LC_HSD4_DFBK,
  BSP_DIN_LC_HSD5_DFBK, BSP_DIN_LC_HSD6_DFBK, BSP_DIN_LC_HSD7_DFBK, BSP_DIN_LC_HSD8_DFBK,
  BSP_DIN_HW_ID0, BSP_DIN_HW_ID1, BSP_DIN_HW_ID2, BSP_DIN_HW_ID3,
  BSP_DIN_HW_ID4, BSP_DIN_HW_ID5, BSP_DIN_HW_ID6,
};

static bsp_dout_t const bsp_doutEnable[] =
{
  BSP_DOUT_PWR_HOLD_ON, BSP_DOUT_CAN_TERM_OFF1, BSP_DOUT_CAN_TERM_OFF2,
  BSP_DOUT_DIN01_ENABLE, BSP_DOUT_DIN02_ENABLE, BSP_DOUT_DIN03_ENABLE, BSP_DOUT_DIN04_ENABLE,
  BSP_DOUT_HC_LSD1_CMD, BSP_DOUT_HC_LSD2_CMD, BSP_DOUT_HC_LSD3_CMD, BSP_DOUT_HC_LSD4_CMD,
  BSP_DOUT_HC_LSD5_CMD, BSP_DOUT_HC_LSD6_CMD,
  BSP_DOUT_HC_HSD1_CMD, BSP_DOUT_HC_HSD2_CMD, BSP_DOUT_HC_HSD3_CMD, BSP_DOUT_HC_HSD4_CMD,
  BSP_DOUT_HC_HSD5_CMD, BSP_DOUT_HC_HSD6_CMD, BSP_DOUT_HC_HSD7_CMD, BSP_DOUT_HC_HSD8_CMD,
  BSP_DOUT_LC_HSD1_CMD, BSP_DOUT_LC_HSD2_CMD, BSP_DOUT_LC_HSD3_CMD, BSP_DOUT_LC_HSD4_CMD,
  BSP_DOUT_LC_HSD5_CMD, BSP_DOUT_LC_HSD6_CMD, BSP_DOUT_LC_HSD7_CMD, BSP_DOUT_LC_HSD8_CMD,
  BSP_DOUT_WC_ON1, BSP_DOUT_WC_ON2, BSP_DOUT_WC_ON3, BSP_DOUT_WC_ON4,
  BSP_DOUT_WC_ON5, BSP_DOUT_WC_ON6, BSP_DOUT_WC_ON7, BSP_DOUT_WC_ON8,
  BSP_DOUT_WC_CONFIG1, BSP_DOUT_WC_CONFIG2, BSP_DOUT_WC_CONFIG3, BSP_DOUT_WC_CONFIG4,
};

static bsp_fin_t const bsp_finEnable[] =
{
  BSP_FIN_1, //BSP_FIN_2, BSP_FIN_3, BSP_FIN_4
};

static bsp_pwm_t const bsp_pwmEnable[] =
{
  BSP_PWM_HC_HSD1, BSP_PWM_HC_HSD2, BSP_PWM_HC_HSD3, BSP_PWM_HC_HSD4,
  BSP_PWM_HC_HSD5, BSP_PWM_HC_HSD6, BSP_PWM_HC_HSD7, BSP_PWM_HC_HSD8,
  //BSP_PWM_LC_HSD1, BSP_PWM_LC_HSD2, BSP_PWM_LC_HSD3, BSP_PWM_LC_HSD4,
  //BSP_PWM_LC_HSD5, BSP_PWM_LC_HSD6, BSP_PWM_LC_HSD7, BSP_PWM_LC_HSD8,
  BSP_PWM_LC_LSD1,
};

//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void bsp_initIO(void);
static void bsp_debug_init(void);
static void bsp_debug_run(void);

//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_init(void)
{
  bsp_mcu_init();
  bsp_clock_init();
  bsp_com_init();
  bsp_debug_init();
  bsp_rtc_init();
  bsp_nvm_init();
  bsp_rom_init();
  bsp_ecuid_init();
  bsp_sdata_init();
  bsp_can_init();
  bsp_adc_init();
  bsp_din_init();
  bsp_dout_init();
  bsp_fin_init();
  bsp_pwm_init();

  bsp_initIO();

  ap_cdata_init();

  bsp_sleep();
  bsp_sleep();
  bsp_sleep();
  bsp_sleep();
  bsp_sleep();
  bsp_sleep();
  bsp_sleep();
  bsp_sleep();
  bsp_sleep();

  BSP_DEBUG(("BSP Init Complete"));

  bsp_sleep();
}

//******************************************************************************
void bsp_run(void)
{
  bsp_mcu_setBusy(bsp_isSystemBusy());
  bsp_mcu_run();
}

//******************************************************************************
bool bsp_isSystemBusy(void)
{
  return bsp_nvm_isBusy();
}

//******************************************************************************
void bsp_taskInit(void)
{
}

//******************************************************************************
void bsp_taskRun(void)
{
  bsp_nvm_run();
  bsp_rtc_run();
  bsp_debug_run();
}

//******************************************************************************
void bsp_sleep(void)
{
  static uint32_t sysTickTimer = 0;
  static uint32_t msClock;

  do
  {
    msClock = bsp_clock_ms();
  }
  while ((sysTickTimer & 1) == (msClock & 1));

  sysTickTimer++;
}

#ifdef BSP_DEBUG_PORT
//******************************************************************************
void bsp_debug_printHeader(char const *file, uint32_t line)
{
  uint32_t length;
  uint32_t msClock = bsp_clock_ms();

  length = snprintf(debugBuffer,
                     sizeof(debugBuffer),
                     "%010i %s:%i - ",
                     msClock, file, line);

  length = length > sizeof(debugBuffer) ? sizeof(debugBuffer) : length;
  bsp_com_write(BSP_DEBUG_PORT, (uint8_t *)debugBuffer, length);
}
#endif

#ifdef BSP_DEBUG_PORT
//******************************************************************************
void bsp_debug_printf(char const * format, ...)
{
  va_list args;
  uint32_t length;

  va_start(args, format);
  length = vsnprintf(debugBuffer, sizeof(debugBuffer), format, args);
  va_end(args);

  length = length > sizeof(debugBuffer) ? sizeof(debugBuffer) : length;
  bsp_com_write(BSP_DEBUG_PORT, (uint8_t *)debugBuffer, length);

  bsp_com_write(BSP_DEBUG_PORT, (uint8_t *)"\r\n", sizeof("\r\n"));
}
#endif


//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
 * Initialize Specific IO channels
 *
 * \return void
 *******************************************************************************/
static void bsp_initIO(void)
{
  uint_fast16_t i;

  for (i = 0; i < BSP_ARRAY_LEN(bsp_adcEnable); i++)
  {
    bsp_adc_initCh(bsp_adcEnable[i]);
  }

  for (i = 0; i < BSP_ARRAY_LEN(bsp_dinEnable); i++)
  {
    bsp_din_initCh(bsp_dinEnable[i]);
  }

  for (i = 0; i < BSP_ARRAY_LEN(bsp_doutEnable); i++)
  {
    bsp_dout_initCh(bsp_doutEnable[i], false);
  }

  for (i = 0; i < BSP_ARRAY_LEN(bsp_finEnable); i++)
  {
    bsp_fin_initCh(bsp_finEnable[i]);
  }

  for (i = 0; i < BSP_ARRAY_LEN(bsp_pwmEnable); i++)
  {
    bsp_pwm_initCh(bsp_pwmEnable[i], 100, 0);
  }
}

//******************************************************************************
/**
 * Initialize the Debug com port
 *
 * \return void
 *******************************************************************************/
static void bsp_debug_init(void)
{
#ifdef BSP_DEBUG_PORT
#define BSP_DEBUG_START_STR "\r\n\r\n***** Debug Port Open - App *****\r\n\r\n"

  bsp_com_initCh(BSP_DEBUG_PORT);
  bsp_com_write(BSP_DEBUG_PORT, BSP_DEBUG_START_STR, sizeof(BSP_DEBUG_START_STR) - 1);
#endif
}

//******************************************************************************
/**
 * Enter am infinite loop to force a watchdog reset
 *
 * \return void
 *******************************************************************************/
#ifdef BSP_DEBUG_PORT
static void bsp_debug_testWD(void)
{
  uint32_t startTime = bsp_clock_ms();
  uint32_t loopTime = 0;
  BSP_DEBUG(("Testing Watchdog..."));

  for (;;)
  {
    uint32_t frequency;
    uint32_t newLoopTime = (bsp_clock_ms() - startTime) / 10;
    newLoopTime *= 10;
    frequency = (8 * 2250) / newLoopTime;

    if ((newLoopTime != loopTime) && (frequency <= 80))
    {
      loopTime = newLoopTime;
      BSP_DEBUG(("WD Loop Time: %ims (~%ikhz )", loopTime, frequency));
    }
  }
}
#endif

//******************************************************************************
/**
 * Process debug commands
 *
 * \return void
 *******************************************************************************/
static void bsp_debug_run(void)
{
#ifdef BSP_DEBUG_PORT
  uint8_t debugCmd = 0;

  if ((bsp_com_read(BSP_DEBUG_PORT, &debugCmd, 1) > 0))
  {
    switch (debugCmd)
    {
    case '1':
      bsp_nvm_startTest(BSP_NVM_1, 0);
      break;

    case '2':
      bsp_nvm_startTest(BSP_NVM_1, 1);
      break;

    case 'W':
      bsp_debug_testWD();
      break;

    default:
      break;
    }
  }
#endif
}

