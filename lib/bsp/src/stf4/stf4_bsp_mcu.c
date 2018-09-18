//******************************************************************************
/**
 * \file    stf4_bsp_mcu.c
 * \author  Chad Swenson
 * \date    June 2013
 * \brief   STM32F4xx Microcontroller Source
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
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "bsp_common.h"

#define STF4_INTERNAL (1)
#include "stf4_bsp_mcu.h"
#include "stf4_vectors.h"
#include "stf4_cstartup.h"
#include "stf4_timer.h"
#include "stf4_iic.h"
#undef STF4_INTERNAL

#include <stm32f4xx.h>


/// Number of System ticks to wait befor resetting
#define BSPMCU_RESET_DELAY      (100)

#define STACK_MON_LOOP_MAX      (64)
#define STACK_MON_VALUE         (0xA5)

// Value from defenition of IS_RCC_AHB1_RESET_PERIPH()
#define RCC_AHB1_ALL  ( ~0xDD1FE800 )
// Value from defenition of IS_RCC_AHB2_PERIPH()
#define RCC_AHB2_ALL  ( ~0xFFFFFF0E )
// Value from defenition ofIS_RCC_AHB3_PERIPH()
#define RCC_AHB3_ALL  ( ~0xFFFFFFFE )
// Value from defenition IS_RCC_APB1_PERIPH()
#define RCC_APB1_ALL  ( ~0x09013600 )
// Value from defenition IS_RCC_APB2_RESET_PERIPH()
#define RCC_APB2_ALL  ( ~0xFB8886CC )

typedef struct mcu_ioDefault_s
{
  GPIO_TypeDef *port;
  uint16_t pin;
  GPIOMode_TypeDef mode;
  GPIOPuPd_TypeDef pull;

} mcu_ioDefault_t;

typedef struct mcu_nvicPriority_s
{
  IRQn_Type IRQn;
  uint32_t priority;
} mcu_nvicPriority_t;


//******************************************************************************
// Static Variables
//******************************************************************************
static volatile uint_fast8_t critCount = 0;
static bool resetRequested = false;
static uint32_t resetTickCount = 0;
bool systemBusy = false;

static uint8_t const * mcuStack = NULL;
static uint32_t mcuStackSize = 0;
static uint32_t mcuStackUsed = 0;
static volatile uint32_t mcuStackMonCount = 0;

static uint32_t taskWatchdogMask = 0;
static uint32_t taskWatchdogFlags = 0;

/**
 * CM4 Priority Grouping
 *  - 0-3,  0bxxxx., 16 groups, no subpriority bits
 *  - 4,    0bxxx.y, 8 groups
 *  - 5,    0bxx.yy, 4 groups
 *  - 6,    0bx.yyy, 2 groups
 *  - 7,    0b.yyyy, 0 groups, no preemption
 */
#define MCU_PRIORITY_GROUPING               (3)
#define MCU_PRIORITY_LOWEST                 ((1 << __NVIC_PRIO_BITS) - 1)
#define MCU_PRIORITY_HIGHEST                (0)

static mcu_nvicPriority_t const nvicPriority[] =
{
//  IRQn                      Priority
  { SysTick_IRQn,             15  },

  { CAN1_TX_IRQn,             6   },
  { CAN1_RX0_IRQn,            5   },
  { CAN1_RX1_IRQn,            5   },
  { CAN1_SCE_IRQn,            5   },

  { CAN2_TX_IRQn,             6   },
  { CAN2_RX0_IRQn,            5   },
  { CAN2_RX1_IRQn,            5   },
  { CAN2_SCE_IRQn,            5   },

  { I2C2_EV_IRQn,             5   },
  { I2C2_ER_IRQn,             5   },
  { I2C3_EV_IRQn,             5   },
  { I2C3_ER_IRQn,             5   },

  { USART1_IRQn,              5   },
  { USART6_IRQn,              5   },

  { FLASH_IRQn,               14  },

  { DMA1_Stream0_IRQn,        5   },
  { DMA1_Stream1_IRQn,        5   },
  { DMA1_Stream2_IRQn,        5   },
  { DMA1_Stream3_IRQn,        5   },
  { DMA1_Stream4_IRQn,        5   },
  { DMA1_Stream5_IRQn,        5   },
  { DMA1_Stream6_IRQn,        5   },
  { DMA1_Stream7_IRQn,        5   },

  { DMA2_Stream0_IRQn,        5   },
  { DMA2_Stream1_IRQn,        5   },
  { DMA2_Stream2_IRQn,        5   },
  { DMA2_Stream3_IRQn,        5   },
  { DMA2_Stream4_IRQn,        5   },
  { DMA2_Stream5_IRQn,        5   },
  { DMA2_Stream6_IRQn,        5   },
  { DMA2_Stream7_IRQn,        5   },

  { TIM4_IRQn,                4   },
  { TIM1_BRK_TIM9_IRQn,       4   },

  { TIM6_DAC_IRQn,            3   },

};

static mcu_ioDefault_t const mcu_ioDefault[] =
{// Port    Pin           Mode            Pull
  { GPIOA,  GPIO_Pin_0,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT1_V
  { GPIOA,  GPIO_Pin_1,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT2_V
  { GPIOA,  GPIO_Pin_2,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT3_V
  { GPIOA,  GPIO_Pin_3,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT4_V
  { GPIOA,  GPIO_Pin_4,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT17_IFBK
  { GPIOA,  GPIO_Pin_5,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT18_IFBK
  { GPIOA,  GPIO_Pin_6,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT19_IFBK
  { GPIOA,  GPIO_Pin_7,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT20_IFBK
  { GPIOA,  GPIO_Pin_8,   GPIO_Mode_IN,   GPIO_PuPd_DOWN  }, // PWR_HOLD_ON
  { GPIOA,  GPIO_Pin_9,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // DEBUG UART Tx
  { GPIOA,  GPIO_Pin_10,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // DEBUG UART Rx
  { GPIOA,  GPIO_Pin_11,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // USB_FS_DM
  { GPIOA,  GPIO_Pin_12,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // USB_FS_DP
  { GPIOA,  GPIO_Pin_13,  GPIO_Mode_AF,   GPIO_PuPd_UP    }, // JTAG_TMS     * (No pull by default)    Commenting this
  { GPIOA,  GPIO_Pin_14,  GPIO_Mode_AF,   GPIO_PuPd_DOWN  }, // JTAG_TCK     * (PD by default)         and this lets SWD work
  { GPIOA,  GPIO_Pin_15,  GPIO_Mode_AF,   GPIO_PuPd_UP    }, // JTAG_TDI     * (PU by default)

  { GPIOB,  GPIO_Pin_0,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT21_IFBK
  { GPIOB,  GPIO_Pin_1,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT22_IFBK
  { GPIOB,  GPIO_Pin_2,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // CAN_TERM_OFF1
  { GPIOB,  GPIO_Pin_3,   GPIO_Mode_AF,   GPIO_PuPd_UP    }, // JTAG_TDO     * (No pull by default)
  { GPIOB,  GPIO_Pin_4,   GPIO_Mode_AF,   GPIO_PuPd_UP    }, // JTAG_TRST    * (PU by default)
  { GPIOB,  GPIO_Pin_5,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // CAN2_RX
  { GPIOB,  GPIO_Pin_6,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // CAN2_TX
  { GPIOB,  GPIO_Pin_7,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // CAN_TERM_OFF2
  { GPIOB,  GPIO_Pin_8,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT8_ON
  { GPIOB,  GPIO_Pin_9,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT6_ON
  { GPIOB,  GPIO_Pin_10,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT2_ON
  { GPIOB,  GPIO_Pin_11,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT9_ON
  { GPIOB,  GPIO_Pin_12,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT1_DIG_EN
  { GPIOB,  GPIO_Pin_13,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT2_DIG_EN
  { GPIOB,  GPIO_Pin_14,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT3_DIG_EN
  { GPIOB,  GPIO_Pin_15,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT4_DIG_EN

  { GPIOC,  GPIO_Pin_0,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT 19_V
  { GPIOC,  GPIO_Pin_1,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT 20_V
  { GPIOC,  GPIO_Pin_2,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT 21_V
  { GPIOC,  GPIO_Pin_3,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT 23_V
  { GPIOC,  GPIO_Pin_4,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // VSENSOR1_V
  { GPIOC,  GPIO_Pin_5,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // xMUX1_OUT
  { GPIOC,  GPIO_Pin_6,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT23_ON
  { GPIOC,  GPIO_Pin_7,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT11 / FIN3
  { GPIOC,  GPIO_Pin_8,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT10_ON
  { GPIOC,  GPIO_Pin_9,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT13_ON
  { GPIOC,  GPIO_Pin_10,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // SPI_SCK
  { GPIOC,  GPIO_Pin_11,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // SPI_MISO
  { GPIOC,  GPIO_Pin_12,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // SPI_MOSI
  { GPIOC,  GPIO_Pin_13,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // HW_ID5
  { GPIOC,  GPIO_Pin_14,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OSC32_IN
  { GPIOC,  GPIO_Pin_15,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OSC32_OUT

  { GPIOD,  GPIO_Pin_0,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // CAN1_RX
  { GPIOD,  GPIO_Pin_1,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // CAN1_TX
  { GPIOD,  GPIO_Pin_2,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT5_V
  { GPIOD,  GPIO_Pin_3,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT6_V
  { GPIOD,  GPIO_Pin_4,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT7_V
  { GPIOD,  GPIO_Pin_5,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT8_V
  { GPIOD,  GPIO_Pin_6,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT9_V
  { GPIOD,  GPIO_Pin_7,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT10_V
  { GPIOD,  GPIO_Pin_8,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT13_V
  { GPIOD,  GPIO_Pin_9,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT14_V
  { GPIOD,  GPIO_Pin_10,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT15_V
  { GPIOD,  GPIO_Pin_11,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT16_V
  { GPIOD,  GPIO_Pin_12,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT12_FREQ(4)
  { GPIOD,  GPIO_Pin_13,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT27_FREQ(1)
  { GPIOD,  GPIO_Pin_14,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // HW_ID0
  { GPIOD,  GPIO_Pin_15,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // HW_ID1

  { GPIOE,  GPIO_Pin_0,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT17_V
  { GPIOE,  GPIO_Pin_1,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT18_V
  { GPIOE,  GPIO_Pin_2,   GPIO_Mode_AF,   GPIO_PuPd_UP    }, // TRACECLK      * TCRACE
  { GPIOE,  GPIO_Pin_3,   GPIO_Mode_AF,   GPIO_PuPd_UP    }, // TRACED0       * TCRACE
  { GPIOE,  GPIO_Pin_4,   GPIO_Mode_AF,   GPIO_PuPd_UP    }, // TRACED1       * TCRACE
  { GPIOE,  GPIO_Pin_5,   GPIO_Mode_AF,   GPIO_PuPd_UP    }, // TRACED2       * TCRACE
  { GPIOE,  GPIO_Pin_6,   GPIO_Mode_AF,   GPIO_PuPd_UP    }, // TRACED3       * TCRACE
  { GPIOE,  GPIO_Pin_7,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // HW_ID2
  { GPIOE,  GPIO_Pin_8,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // HW_ID3
  { GPIOE,  GPIO_Pin_9,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT1_ON
  { GPIOE,  GPIO_Pin_10,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // HW_ID4
  { GPIOE,  GPIO_Pin_11,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT5_ON
  { GPIOE,  GPIO_Pin_12,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // CAN_HS_EN1
  { GPIOE,  GPIO_Pin_13,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT11_ON
  { GPIOE,  GPIO_Pin_14,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT14_ON
  { GPIOE,  GPIO_Pin_15,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // CAN_HS_EN2

  { GPIOF,  GPIO_Pin_0,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // I2C2_SDA
  { GPIOF,  GPIO_Pin_1,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // I2C2_SCL
  { GPIOF,  GPIO_Pin_2,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // EEPROM_WP
  { GPIOF,  GPIO_Pin_3,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // SW_BATT_V
  { GPIOF,  GPIO_Pin_4,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT22_VSENSOR2_V
  { GPIOF,  GPIO_Pin_5,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // xMUX2_OUT
  { GPIOF,  GPIO_Pin_6,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT 24_V
  { GPIOF,  GPIO_Pin_7,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT 25_V
  { GPIOF,  GPIO_Pin_8,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT 26_V
  { GPIOF,  GPIO_Pin_9,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // BAT_V
  { GPIOF,  GPIO_Pin_10,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // INPUT28_V
  { GPIOF,  GPIO_Pin_11,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT19_ON
  { GPIOF,  GPIO_Pin_12,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT20_ON
  { GPIOF,  GPIO_Pin_13,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT21_ON
  { GPIOF,  GPIO_Pin_14,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT22_ON
  { GPIOF,  GPIO_Pin_15,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // HW_ID6

  { GPIOG,  GPIO_Pin_0,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT9_DFBK
  { GPIOG,  GPIO_Pin_1,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT10_DFBK
  { GPIOG,  GPIO_Pin_2,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT11_DFBK
  { GPIOG,  GPIO_Pin_3,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT12_DFBK
  { GPIOG,  GPIO_Pin_4,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT13_DFBK
  { GPIOG,  GPIO_Pin_5,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT14_DFBK
  { GPIOG,  GPIO_Pin_6,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT15_DFBK
  { GPIOG,  GPIO_Pin_7,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT16_DFBK
  { GPIOG,  GPIO_Pin_8,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // MUX1_A_EN
  { GPIOG,  GPIO_Pin_9,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // USART6_RX
  { GPIOG,  GPIO_Pin_10,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // MUX1_B_EN
  { GPIOG,  GPIO_Pin_11,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // MUX1_C_EN
  { GPIOG,  GPIO_Pin_12,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // MUX2_A_EN
  { GPIOG,  GPIO_Pin_13,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // MUX2_B_EN
  { GPIOG,  GPIO_Pin_14,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // USART6_TX
  { GPIOG,  GPIO_Pin_15,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // MUX2_C_EN

  { GPIOH,  GPIO_Pin_0,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OSC_IN
  { GPIOH,  GPIO_Pin_1,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OSC_OUT
  { GPIOH,  GPIO_Pin_2,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_CONFIG1
  { GPIOH,  GPIO_Pin_3,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_CONFIG2
  { GPIOH,  GPIO_Pin_4,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_CONFIG3
  { GPIOH,  GPIO_Pin_5,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_CONFIG4
  { GPIOH,  GPIO_Pin_6,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT7_ON
  { GPIOH,  GPIO_Pin_7,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // I2C3_SCL
  { GPIOH,  GPIO_Pin_8,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // I2C3_SDA
  { GPIOH,  GPIO_Pin_9,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT12_ON
  { GPIOH,  GPIO_Pin_10,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT3_ON
  { GPIOH,  GPIO_Pin_11,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT15_ON
  { GPIOH,  GPIO_Pin_12,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT16_ON
  { GPIOH,  GPIO_Pin_13,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // ACCEL_EN
  { GPIOH,  GPIO_Pin_14,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // CAN_EN1
  { GPIOH,  GPIO_Pin_15,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // CAN_EN2

  { GPIOI,  GPIO_Pin_0,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_ON1
  { GPIOI,  GPIO_Pin_1,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_ON2
  { GPIOI,  GPIO_Pin_2,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_ON3
  { GPIOI,  GPIO_Pin_3,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_ON4
  { GPIOI,  GPIO_Pin_4,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_ON5
  { GPIOI,  GPIO_Pin_5,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT4_ON
  { GPIOI,  GPIO_Pin_6,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT17_ON
  { GPIOI,  GPIO_Pin_7,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // OUTPUT18_ON
  { GPIOI,  GPIO_Pin_8,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_ON6
  { GPIOI,  GPIO_Pin_9,   GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_ON7
  { GPIOI,  GPIO_Pin_10,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // WC_ON8
  { GPIOI,  GPIO_Pin_11,  GPIO_Mode_IN,   GPIO_PuPd_UP    }, // RS232_EN

};

//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void isr_default(void);
static void isr_hardFault(void);
static void ioSetDefaults(void);
static void initStackMonitor(void);
static void runStackMonitor(void);
static void mcuInit(void);
static void disableAllInterrupts(void);

//******************************************************************************
// Global Variables
//******************************************************************************


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_mcu_init(void)
{
  disableAllInterrupts();

  systemBusy = false;
  taskWatchdogMask = 0;
  taskWatchdogFlags = 0;

  // Reset all peripheral registers to default values
  RCC_AHB1PeriphResetCmd(RCC_AHB1_ALL, ENABLE);
  RCC_AHB1PeriphResetCmd(RCC_AHB1_ALL, DISABLE);
  RCC_AHB2PeriphResetCmd(RCC_AHB2_ALL, ENABLE);
  RCC_AHB2PeriphResetCmd(RCC_AHB2_ALL, DISABLE);
  RCC_AHB3PeriphResetCmd(RCC_AHB3_ALL, ENABLE);
  RCC_AHB3PeriphResetCmd(RCC_AHB3_ALL, DISABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1_ALL, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1_ALL, DISABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2_ALL, ENABLE);
  RCC_APB2PeriphResetCmd(RCC_APB2_ALL, DISABLE);

  ioSetDefaults();

  vectors_initRamVectors(isr_default);
  vectors_setRamVector(HardFault_IRQn, isr_hardFault);
  vectors_setRamVector(BusFault_IRQn, isr_hardFault);
  vectors_setRamVector(UsageFault_IRQn, isr_hardFault);
  vectors_switchToRam();

  initStackMonitor();
  mcuInit();

  __enable_irq();

  stf4_timer_init();
  stf4_iic_init();
}

//******************************************************************************
void bsp_mcu_run(void)
{
  // Only kick the dog if all registered tasks have checked in
  if (taskWatchdogFlags == taskWatchdogMask)
  {
    IWDG_ReloadCounter();
    taskWatchdogFlags = 0;
  }

  if (resetRequested)
  {
    if (systemBusy)
    {
      // Do not reset if the rom or nvm module is busy
      resetTickCount = BSPMCU_RESET_DELAY;
    }
    else if (resetTickCount)
    {
      resetTickCount--;
    }
    else
    {
      disableAllInterrupts();
      NVIC_SystemReset();
    }
  }

  runStackMonitor();
}

//******************************************************************************
void bsp_mcu_kickTaskWatchdog(uint32_t task)
{
  uint32_t flag = 1 << task;

  // Task Watchdog limited to 32 tasks
  assert_param(task < 32);

  // Update the mask so we know to watch for this task in the future
  taskWatchdogMask |= flag;

  // Set the kick flag for this task
  taskWatchdogFlags |= flag;
}

//******************************************************************************
void bsp_mcu_setBusy(bool busy)
{
  systemBusy = busy;
}

//******************************************************************************
void bsp_enterCritical(void)
{
  if (++critCount == 1u)
  {
    __disable_irq();
  }
}

//******************************************************************************
void bsp_exitCritical(void)
{
  if (--critCount == 0u)
  {
    __enable_irq();
  }
}

//******************************************************************************
void bsp_mcu_requestReset(void)
{
  if (!resetRequested)
  {
    resetRequested = true;
    resetTickCount = BSPMCU_RESET_DELAY;

    BSP_DEBUG(("Resetting in %i ticks.", resetTickCount));
  }
}

//******************************************************************************
uint32_t bsp_mcu_maxStack(void)
{
  return mcuStackUsed;
}

//******************************************************************************
void bsp_mcu_jumpToApplication(uintptr_t appAddress)
{
  disableAllInterrupts();
  cstartup_jumpToApplication(appAddress);
}

//******************************************************************************
#if USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  static volatile uint32_t assertFails = 0;

  assertFails++;

  BSP_DEBUG(("ASSERT Fail (%i) at %s:%i", assertFails, file, line));
  //for (;;);
}
#endif

//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
 * Default interrupt handler
 *
 * \return void
 *******************************************************************************/
static void isr_default(void)
{
  for (;;);
}

//******************************************************************************
/**
 * Hard fault interrupt handler - in place primarily for debugging a hard fault
 *
 * \return void
 *******************************************************************************/
static void isr_hardFault(void)
{
  for (;;);
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void ioSetDefaults(void)
{
  uint32_t i;
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);

  for (i = 0; i < BSP_ARRAY_LEN(mcu_ioDefault); i++)
  {
    GPIO_InitStructure.GPIO_Pin = mcu_ioDefault[i].pin;
    GPIO_InitStructure.GPIO_Mode = mcu_ioDefault[i].mode;
    GPIO_InitStructure.GPIO_PuPd = mcu_ioDefault[i].pull;
    GPIO_Init(mcu_ioDefault[i].port, &GPIO_InitStructure);
  }
}

//******************************************************************************
/**
 * Init the Stack Monitor
 *
 * \return void
 *******************************************************************************/
static void initStackMonitor(void)
{
  uint8_t * tempStack;
  void * stackTop = cstartup_getStackTop(&mcuStackSize);

  mcuStackUsed = 0;

  mcuStack = (uint8_t *)stackTop;
  mcuStack -= mcuStackSize;

  tempStack = (uint8_t *)stackTop;
  tempStack -= mcuStackSize;

  // Preload the stack with a known value
  while ((uint32_t)tempStack < __get_MSP())
  {
    *tempStack++ = STACK_MON_VALUE;
  }
}

//******************************************************************************
/**
 * Run the Stack Monitor
 *
 * \return void
 *******************************************************************************/
static void runStackMonitor(void)
{
  static uint8_t const * stackData = NULL;

  if (mcuStack && mcuStackSize)
  {
    uint8_t const *stackEnd = mcuStack + mcuStackSize;
    uint32_t loopCount = 0;

    if ((stackData < mcuStack) || (stackData >= stackEnd))
    {
      stackData = mcuStack;
    }

    while ((stackData < stackEnd) && (loopCount++ < STACK_MON_LOOP_MAX))
    {
      if (*stackData == STACK_MON_VALUE)
      {
        stackData++;
      }
      else
      {
        uint32_t stackUsed = (uint32_t)(stackEnd - stackData);

        if (stackUsed > mcuStackUsed)
        { // Only update mcuStackUsed if stackUsed is a max
          mcuStackUsed = stackUsed;
        }

        mcuStackMonCount++;
        stackData = mcuStack;
        break;
      }
    }
  }
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void mcuInit(void)
{
  uint_fast16_t i;
  uint32_t priority;

  NVIC_SetPriorityGrouping(MCU_PRIORITY_GROUPING);

  for (i = 0; i < BSP_ARRAY_LEN(nvicPriority); i++)
  {
    priority = nvicPriority[i].priority;

    if (priority > MCU_PRIORITY_LOWEST)
    {
      priority = MCU_PRIORITY_LOWEST;
    }

    NVIC_SetPriority(nvicPriority[i].IRQn, priority);
  }
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void disableAllInterrupts(void)
{
  uint32_t i;

  __disable_irq();

  // Disable SysTick interrupts (0xE000E010-0xE000E01F)
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

  // System Control Block
  SCB->ICSR |= SCB_ICSR_PENDSVCLR_Msk;
  SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;

  // FPU

  // MPU
  MPU->CTRL = 0;

  // NVIC
  for (i = 0; i < BSP_ARRAY_LEN(NVIC->ICER); i++)
  {
    // Disable interrupts
    NVIC->ICER[i] = 0xFFFFFFFF;

    // Clear pending interrupts
    NVIC->ICPR[i] = 0xFFFFFFFF;
  }
}


