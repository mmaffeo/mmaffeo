//******************************************************************************
/**
 * \file    stf4_bsp_dout.c
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   STM32F4xx Specific Digital Output Source
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
#include "bsp_common.h"

#define STF4_INTERNAL (1)
#include "stf4_bsp_dout.h"
#include "stm32f4xx_gpio.h"
#undef STF4_INTERNAL

#define DOUT_WC_FIRST   (BSP_DOUT_WC_ON1)
#define DOUT_WC_LAST    (BSP_DOUT_WC_CONFIG4)

typedef struct dout_pinConfig_s
{
  uint32_t clock;
  GPIO_TypeDef *port;
  uint16_t pin;
} dout_pinConfig_t;

// PI0  - WC_ON1 - DIN_05, DIN_06, DIN_07, DIN_08
// PI1  - WC_ON2 - DIN_09, DIN_10, DIN_11, DIN_12
// PI2  - WC_ON3 - DIN_13, DIN_14, DIN_15
// PI3  - WC_ON4 - DIN_16, DIN_17
// PI4  - WC_ON5 - AIN_12
// PI8  - WC_ON6 - AIN_13
// PI9  - WC_ON7 - AIN_10
// PI10 - WC_ON8 - DIN_18
//
// PH2  - WC_CONFIG1 - DIN_01_AIN_01
// PH3  - WC_CONFIG2 - DIN_02_AIN_02
// PH4  - WC_CONFIG3 - DIN_03_AIN_03
// PH5  - WC_CONFIG4 - DIN_04_AIN_04


//******************************************************************************
// Static Variables
//******************************************************************************

static dout_pinConfig_t const dout_pinConfig[] =
{// Clock                   Port    Pin
  { RCC_AHB1Periph_GPIOA,   GPIOA,  GPIO_Pin_8  },  // PWR_HOLD_ON      0

  { RCC_AHB1Periph_GPIOB,   GPIOB,  GPIO_Pin_2  },  // CAN_TERM_OFF1    1
  { RCC_AHB1Periph_GPIOB,   GPIOB,  GPIO_Pin_7  },  // CAN_TERM_OFF2    2

  { RCC_AHB1Periph_GPIOB,   GPIOB,  GPIO_Pin_12 },  // DIN01_ENABLE     3
  { RCC_AHB1Periph_GPIOB,   GPIOB,  GPIO_Pin_13 },  // DIN02_ENABLE
  { RCC_AHB1Periph_GPIOB,   GPIOB,  GPIO_Pin_14 },  // DIN03_ENABLE
  { RCC_AHB1Periph_GPIOB,   GPIOB,  GPIO_Pin_15 },  // DIN04_ENABLE

  { RCC_AHB1Periph_GPIOI,   GPIOI,  GPIO_Pin_6  },  // HC_LSD1_CMD      7
  { RCC_AHB1Periph_GPIOI,   GPIOI,  GPIO_Pin_7  },  // HC_LSD2_CMD
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_11 },  // HC_LSD3_CMD
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_12 },  // HC_LSD4_CMD
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_13 },  // HC_LSD5_CMD
  { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_14 },  // HC_LSD6_CMD      12

  { RCC_AHB1Periph_GPIOE,  GPIOE,   GPIO_Pin_9  },  // HC_HSD1_CMD      13
  { RCC_AHB1Periph_GPIOB,  GPIOB,   GPIO_Pin_10 },  // HC_HSD2_CMD
  { RCC_AHB1Periph_GPIOH,  GPIOH,   GPIO_Pin_10 },  // HC_HSD3_CMD
  { RCC_AHB1Periph_GPIOI,  GPIOI,   GPIO_Pin_5  },  // HC_HSD4_CMD
  { RCC_AHB1Periph_GPIOE,  GPIOE,   GPIO_Pin_11 },  // HC_HSD5_CMD
  { RCC_AHB1Periph_GPIOB,  GPIOB,   GPIO_Pin_9  },  // HC_HSD6_CMD
  { RCC_AHB1Periph_GPIOH,  GPIOH,   GPIO_Pin_6  },  // HC_HSD7_CMD
  { RCC_AHB1Periph_GPIOB,  GPIOB,   GPIO_Pin_8  },  // HC_HSD8_CMD      20

  { RCC_AHB1Periph_GPIOB,  GPIOB,   GPIO_Pin_11 },  // LC_HSD1_CMD      21
  { RCC_AHB1Periph_GPIOC,  GPIOC,   GPIO_Pin_8  },  // LC_HSD2_CMD
  { RCC_AHB1Periph_GPIOC,  GPIOC,   GPIO_Pin_9  },  // LC_HSD3_CMD
  { RCC_AHB1Periph_GPIOE,  GPIOE,   GPIO_Pin_13 },  // LC_HSD4_CMD
  { RCC_AHB1Periph_GPIOE,  GPIOE,   GPIO_Pin_14 },  // LC_HSD5_CMD
  { RCC_AHB1Periph_GPIOH,  GPIOH,   GPIO_Pin_9  },  // LC_HSD6_CMD
  { RCC_AHB1Periph_GPIOH,  GPIOH,   GPIO_Pin_11 },  // LC_HSD7_CMD
  { RCC_AHB1Periph_GPIOH,  GPIOH,   GPIO_Pin_12 },  // LC_HSD8_CMD      28

  { RCC_AHB1Periph_GPIOI,  GPIOI,   GPIO_Pin_0  },  // WC_ON1           29
  { RCC_AHB1Periph_GPIOI,  GPIOI,   GPIO_Pin_1  },  // WC_ON2
  { RCC_AHB1Periph_GPIOI,  GPIOI,   GPIO_Pin_2  },  // WC_ON3
  { RCC_AHB1Periph_GPIOI,  GPIOI,   GPIO_Pin_3  },  // WC_ON4
  { RCC_AHB1Periph_GPIOI,  GPIOI,   GPIO_Pin_4  },  // WC_ON5
  { RCC_AHB1Periph_GPIOI,  GPIOI,   GPIO_Pin_8  },  // WC_ON6
  { RCC_AHB1Periph_GPIOI,  GPIOI,   GPIO_Pin_9  },  // WC_ON7
  { RCC_AHB1Periph_GPIOI,  GPIOI,   GPIO_Pin_10 },  // WC_ON8
  { RCC_AHB1Periph_GPIOH,  GPIOH,   GPIO_Pin_2  },  // WC_CONFIG1
  { RCC_AHB1Periph_GPIOH,  GPIOH,   GPIO_Pin_3  },  // WC_CONFIG2
  { RCC_AHB1Periph_GPIOH,  GPIOH,   GPIO_Pin_4  },  // WC_CONFIG3
  { RCC_AHB1Periph_GPIOH,  GPIOH,   GPIO_Pin_5  },  // WC_CONFIG4

  { RCC_AHB1Periph_GPIOA,  GPIOA,   GPIO_Pin_11 },  // BSP_DOUT_DEBUG1
  { RCC_AHB1Periph_GPIOA,  GPIOA,   GPIO_Pin_12 },  // BSP_DOUT_DEBUG2
};

static GPIO_TypeDef * const wcPorts[] =
{
  GPIOA,
  GPIOB,
  GPIOC,
  GPIOE,
  GPIOF,
  GPIOH,
  GPIOI,
};

static volatile uint16_t wcPinEnable[BSP_ARRAY_LEN(wcPorts)];


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_dout_init(void)
{
  uint32_t i;

  for (i = 0; i < BSP_ARRAY_LEN(wcPinEnable); i++)
  {
    wcPinEnable[i] = 0;
  }

  // Enable all wetting current outputs
  for (i = DOUT_WC_FIRST; i <= DOUT_WC_LAST; i++)
  {
    bsp_dout_initCh((bsp_dout_t)i, false);
    bsp_dout_wettingCurrentEnable((bsp_dout_t)i, true);
  }
}

//******************************************************************************
void bsp_dout_setWCState(bool state)
{
  uint_fast16_t i;

  if (state)
  {
    for (i = 0; i < BSP_ARRAY_LEN(wcPorts); i++)
    {
      wcPorts[i]->BSRRL = wcPinEnable[i];
    }
  }
  else
  {
    for (i = 0; i < BSP_ARRAY_LEN(wcPorts); i++)
    {
      wcPorts[i]->BSRRH = wcPinEnable[i];
    }
  }
}

//******************************************************************************
void bsp_dout_initCh(bsp_dout_t ch, bool value)
{
  if ((uint32_t)ch < BSP_ARRAY_LEN(dout_pinConfig))
  {
    if (dout_pinConfig[ch].port)
    {
      GPIO_InitTypeDef GPIO_InitStructure;

      GPIO_StructInit(&GPIO_InitStructure);
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_Pin = dout_pinConfig[ch].pin;

      RCC_AHB1PeriphClockCmd(dout_pinConfig[ch].clock, ENABLE);

      bsp_dout_SetValue(ch, value);

      GPIO_Init(dout_pinConfig[ch].port, &GPIO_InitStructure);
    }
  }
}

//******************************************************************************
void bsp_dout_deinitCh(bsp_dout_t ch)
{
  if ((uint32_t)ch < BSP_ARRAY_LEN(dout_pinConfig))
  {
    if (dout_pinConfig[ch].port)
    {
      GPIO_InitTypeDef GPIO_InitStructure;

      GPIO_StructInit(&GPIO_InitStructure);

      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
      GPIO_InitStructure.GPIO_Pin = dout_pinConfig[ch].pin;

      RCC_AHB1PeriphClockCmd(dout_pinConfig[ch].clock, ENABLE);
      GPIO_Init(dout_pinConfig[ch].port, &GPIO_InitStructure);
    }
  }
}

//******************************************************************************
bool bsp_dout_GetValue(bsp_dout_t ch)
{
  bool retValue = false;

  if ((uint32_t)ch < BSP_ARRAY_LEN(dout_pinConfig))
  {
    if (dout_pinConfig[ch].port)
    {
      if (dout_pinConfig[ch].port->IDR & dout_pinConfig[ch].pin)
      {
        retValue = true;
      }
    }
  }

  return retValue;
}

//******************************************************************************
void bsp_dout_SetValue(bsp_dout_t ch, bool value)
{
  if ((uint32_t)ch < BSP_ARRAY_LEN(dout_pinConfig))
  {
    if (dout_pinConfig[ch].port)
    {
      if (value)
      {
        dout_pinConfig[ch].port->BSRRL = dout_pinConfig[ch].pin;
      }
      else
      {
        dout_pinConfig[ch].port->BSRRH = dout_pinConfig[ch].pin;
      }
    }
  }
}

//******************************************************************************
void bsp_dout_wettingCurrentEnable(bsp_dout_t ch, bool enable)
{
  uint_fast16_t i;

  if ((uint32_t)ch < BSP_ARRAY_LEN(dout_pinConfig))
  {
    for (i = 0; i < BSP_ARRAY_LEN(wcPorts); i++)
    {
      if (wcPorts[i] == dout_pinConfig[ch].port)
      {
        if (enable)
        {
          wcPinEnable[i] |= dout_pinConfig[ch].pin;
        }
        else
        {
          wcPinEnable[i] &= ~dout_pinConfig[ch].pin;

          // Force pin low
          bsp_dout_SetValue(ch, false);
        }

        break;
      }
    }
  }
}

//******************************************************************************
bool bsp_dout_getWettingCurrentEnable(bsp_dout_t ch)
{
  uint_fast16_t i;
  bool retValue = false;

  if ((uint32_t)ch < BSP_ARRAY_LEN(dout_pinConfig))
  {
    for (i = 0; i < BSP_ARRAY_LEN(wcPorts); i++)
    {
      if (wcPorts[i] == dout_pinConfig[ch].port)
      {
        retValue = ((wcPinEnable[i] & dout_pinConfig[ch].pin) != 0);
        break;
      }
    }
  }

  return retValue;
}
