//******************************************************************************
/**
 * \file    stf4_bsp_din.c
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   STM32F4xx Specific Digital Input Source
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
#include "stf4_bsp_din.h"
#include "stm32f4xx_gpio.h"
#undef STF4_INTERNAL

typedef struct din_pinConfig_s
{
  uint32_t clock;
  uint16_t portIndex;
  uint16_t pin;
} din_pinConfig_t;

enum din_portIndex_e
{
  DIN_PORT_A = 0,
  DIN_PORT_B,
  DIN_PORT_C,
  DIN_PORT_D,
  DIN_PORT_E,
  DIN_PORT_F,
  DIN_PORT_G,
  DIN_PORT_H,
  DIN_PORT_I,
};


//******************************************************************************
// Static Variables
//******************************************************************************

static din_pinConfig_t const din_pinConfig[] =
{// Clock                   Port Index   Pin
  { RCC_AHB1Periph_GPIOA,   DIN_PORT_A,  GPIO_Pin_0  },  //  AIN01_DIN01      - 0
  { RCC_AHB1Periph_GPIOA,   DIN_PORT_A,  GPIO_Pin_1  },  //  AIN02_DIN02      - 1
  { RCC_AHB1Periph_GPIOA,   DIN_PORT_A,  GPIO_Pin_2  },  //  AIN03_DIN03      - 2
  { RCC_AHB1Periph_GPIOA,   DIN_PORT_A,  GPIO_Pin_3  },  //  AIN04_DIN04      - 3

  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_2  },  //  DIN5             - 4
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_3  },  //  DIN6             - 5
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_4  },  //  DIN7             - 6
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_5  },  //  DIN8             - 7
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_6  },  //  DIN9             - 8
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_7  },  //  DIN10            - 9
  { RCC_AHB1Periph_GPIOC,   DIN_PORT_C,  GPIO_Pin_7  },  //  DIN11_FIN3       - 10
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_12 },  //  DIN12_FIN4       - 11
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_8  },  //  DIN13            - 12
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_9  },  //  DIN14            - 13
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_10 },  //  DIN15            - 14
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_11 },  //  DIN16            - 15
  { RCC_AHB1Periph_GPIOE,   DIN_PORT_E,  GPIO_Pin_0  },  //  DIN17            - 16
  { RCC_AHB1Periph_GPIOE,   DIN_PORT_E,  GPIO_Pin_1  },  //  DIN18            - 17

  { RCC_AHB1Periph_GPIOG,   DIN_PORT_G,  GPIO_Pin_0  },  //  LC_HSD1_DFBK     - 18
  { RCC_AHB1Periph_GPIOG,   DIN_PORT_G,  GPIO_Pin_1  },  //  LC_HSD2_DFBK     - 19
  { RCC_AHB1Periph_GPIOG,   DIN_PORT_G,  GPIO_Pin_4  },  //  LC_HSD3_DFBK     - 20
  { RCC_AHB1Periph_GPIOG,   DIN_PORT_G,  GPIO_Pin_2  },  //  LC_HSD4_DFBK     - 21
  { RCC_AHB1Periph_GPIOG,   DIN_PORT_G,  GPIO_Pin_5  },  //  LC_HSD5_DFBK     - 22
  { RCC_AHB1Periph_GPIOG,   DIN_PORT_G,  GPIO_Pin_3  },  //  LC_HSD6_DFBK     - 23
  { RCC_AHB1Periph_GPIOG,   DIN_PORT_G,  GPIO_Pin_6  },  //  LC_HSD7_DFBK     - 24
  { RCC_AHB1Periph_GPIOG,   DIN_PORT_G,  GPIO_Pin_7  },  //  LC_HSD8_DFBK     - 25

  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_14 },  //  HW_ID0           - 26
  { RCC_AHB1Periph_GPIOD,   DIN_PORT_D,  GPIO_Pin_15 },  //  HW_ID1           - 27
  { RCC_AHB1Periph_GPIOE,   DIN_PORT_E,  GPIO_Pin_7  },  //  HW_ID2           - 28
  { RCC_AHB1Periph_GPIOE,   DIN_PORT_E,  GPIO_Pin_8  },  //  HW_ID3           - 29
  { RCC_AHB1Periph_GPIOE,   DIN_PORT_E,  GPIO_Pin_10 },  //  HW_ID4           - 30
  { RCC_AHB1Periph_GPIOC,   DIN_PORT_C,  GPIO_Pin_13 },  //  HW_ID5           - 31
  { RCC_AHB1Periph_GPIOF,   DIN_PORT_F,  GPIO_Pin_15 },  //  HW_ID6           - 32
};

static GPIO_TypeDef * const dinPort[] =
{
  GPIOA,  // DIN_PORT_A
  GPIOB,  // DIN_PORT_B
  GPIOC,  // DIN_PORT_C
  GPIOD,  // DIN_PORT_D
  GPIOE,  // DIN_PORT_E
  GPIOF,  // DIN_PORT_F
  GPIOG,  // DIN_PORT_G
  GPIOH,  // DIN_PORT_H
  GPIOI,  // DIN_PORT_I
};

static uint16_t dinBuffer[BSP_ARRAY_LEN(dinPort)];


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_din_init(void)
{
  uint_fast16_t i;

  for (i = 0; i < BSP_ARRAY_LEN(dinBuffer); i++)
  {
    dinBuffer[i] = 0;
  }
}

//******************************************************************************
void bsp_din_sample(void)
{
  uint_fast16_t i;

  for (i = 0; i < BSP_ARRAY_LEN(dinBuffer); i++)
  {
    dinBuffer[i] = dinPort[i]->IDR;
  }
}

//******************************************************************************
void bsp_din_initCh(bsp_din_t ch)
{
  if ((uint32_t)ch < BSP_ARRAY_LEN(din_pinConfig))
  {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_StructInit(&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = din_pinConfig[ch].pin;

    RCC_AHB1PeriphClockCmd(din_pinConfig[ch].clock, ENABLE);
    GPIO_Init(dinPort[din_pinConfig[ch].portIndex], &GPIO_InitStructure);
  }
}

//******************************************************************************
void bsp_din_deinitCh(bsp_din_t ch)
{
  // Deinitialized state is also Input so call init
  bsp_din_initCh(ch);
}


//******************************************************************************
bool bsp_din_GetValue(bsp_din_t ch)
{
  bool retValue = false;

  if ((uint32_t)ch < BSP_ARRAY_LEN(din_pinConfig))
  {
    if (dinBuffer[din_pinConfig[ch].portIndex] & din_pinConfig[ch].pin)
    {
      retValue = true;
    }
  }

  return retValue;
}

