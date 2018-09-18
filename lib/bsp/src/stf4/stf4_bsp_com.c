 //******************************************************************************
/**
 * \file    stf4_bsp_com.c
 * \author  Chad Swenson
 * \date    September 2014
 * \brief   STM32F4xx Specific Serial Communication
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

#include "stf4_fifo.h"

#define STF4_INTERNAL (1)
#include "stf4_bsp_com.h"
#include "stf4_vectors.h"
#include "stm32f4xx.h"
#undef STF4_INTERNAL


//******************************************************************************
// Defines
//******************************************************************************

#ifndef BSP_COM_1_TXBUFF_SIZE
# define BSP_COM_1_TXBUFF_SIZE  (256)
#endif
#ifndef BSP_COM_1_RTXBUFF_SIZE
# define BSP_COM_1_RXBUFF_SIZE  (256)
#endif

#ifndef BSP_COM_2_TXBUFF_SIZE
# define BSP_COM_2_TXBUFF_SIZE  (256)
#endif

#ifndef BSP_COM_2_RXBUFF_SIZE
# define BSP_COM_2_RXBUFF_SIZE  (256)
#endif

enum bsp_com_direction_e
{
  COM_DIR_TX = 0,
  COM_DIR_RX,
  COM_NUM_DIRS
};

typedef struct com_pinConfig_s
{
  uint32_t portClock;
  GPIO_TypeDef *port;
  uint16_t pin;
  uint16_t pinSource;
} com_pinConfig_t;

typedef struct uart_config_s
{
  com_pinConfig_t txPin;
  com_pinConfig_t rxPin;
  com_pinConfig_t enablePin;
  uint8_t altFunction;

  USART_TypeDef * uart;

  uint32_t apb1Clocks;
  uint32_t apb2Clocks;

  uint32_t bitRate;

  vectors_entry_t isr;
  IRQn_Type irq;

  uint8_t * rxBuffer;
  uint32_t rxBufferLength;
  uint8_t * txBuffer;
  uint32_t txBufferLength;

} uart_config_t;

//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void initIO(uart_config_t const * config);
static void initUART(uart_config_t const * config);

static void isr_com0(void);
static void isr_com1(void);

//******************************************************************************
// Static Variables
//******************************************************************************
static uint8_t com_0_rxBuffer[BSP_COM_1_RXBUFF_SIZE];
static uint8_t com_0_txBuffer[BSP_COM_1_TXBUFF_SIZE];

static uint8_t com_1_rxBuffer[BSP_COM_2_RXBUFF_SIZE];
static uint8_t com_1_txBuffer[BSP_COM_2_TXBUFF_SIZE];

static uart_config_t const uart_config[] =
{
  { // COM Port 0
    { RCC_AHB1Periph_GPIOG, GPIOG,  GPIO_Pin_14, GPIO_PinSource14 },  // Tx Pin
    { RCC_AHB1Periph_GPIOG, GPIOG,  GPIO_Pin_9,  GPIO_PinSource9  },  // Rx Pin
    { RCC_AHB1Periph_GPIOI, GPIOI,  GPIO_Pin_11, GPIO_PinSource11 },  // Enable Pin
    GPIO_AF_USART6,                                                   // Alt Function
    USART6,                                                           // USART Base
    0,                                                                // APB1 Clocks
    RCC_APB2Periph_USART6,                                            // APB2 Clocks
    230400,                                                           // Baud Rate
    isr_com0,                                                         // ISR
    USART6_IRQn,                                                      // IRQn
    com_0_rxBuffer,                                                   // Rx Buffer
    sizeof(com_0_rxBuffer),                                           // Rx Buffer length
    com_0_txBuffer,                                                   // Tx Buffer
    sizeof(com_0_txBuffer),                                           // Tx Buffer length
  },
  { // COM Port 1
    { RCC_AHB1Periph_GPIOA, GPIOA,  GPIO_Pin_9,  GPIO_PinSource9  },  // Tx Pin
    { RCC_AHB1Periph_GPIOA, GPIOA,  GPIO_Pin_10, GPIO_PinSource10 },  // Rx Pin
    { 0,                    NULL,   0,           0                },  // Enable Pin
    GPIO_AF_USART1,                                                   // Alt Function
    USART1,                                                           // USART Base
    0,                                                                // APB1 Clocks
    RCC_APB2Periph_USART1,                                            // APB2 Clocks
    921600,                                                           // Baud Rate
    isr_com1,                                                         // ISR
    USART1_IRQn,                                                      // IRQn
    com_1_rxBuffer,                                                   // Rx Buffer
    sizeof(com_1_rxBuffer),                                           // Rx Buffer length
    com_1_txBuffer,                                                   // Tx Buffer
    sizeof(com_1_txBuffer),                                           // Tx Buffer length
  },
};

static bsp_fifo_t comFIFO[BSP_ARRAY_LEN(uart_config)][COM_NUM_DIRS];


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_com_init(void)
{
  // Nothing to do
}

//******************************************************************************
void bsp_com_initCh(bsp_com_t ch)
{
  if ((uint32_t)ch < BSP_ARRAY_LEN(uart_config))
  {
    bsp_fifo_init(&comFIFO[ch][COM_DIR_RX],
                 uart_config[ch].rxBuffer,
                 uart_config[ch].rxBufferLength,
                 sizeof(uint8_t));

    bsp_fifo_init(&comFIFO[ch][COM_DIR_TX],
                 uart_config[ch].txBuffer,
                 uart_config[ch].txBufferLength,
                 sizeof(uint8_t));

    initUART(&uart_config[ch]);
    initIO(&uart_config[ch]);
  }
}

//******************************************************************************
void bsp_com_deinitCh(bsp_com_t ch)
{
  // TODO
}

//******************************************************************************
uint32_t bsp_com_write(bsp_com_t ch, uint8_t const * data, uint32_t length)
{
  uint32_t bytesWritten = 0;

  if (((uint32_t)ch < BSP_ARRAY_LEN(uart_config)) && data && length)
  {
    while (length--)
    {
      if (bsp_fifo_put(&comFIFO[ch][COM_DIR_TX], data++))
      {
        bytesWritten++;
      }
      else
      {
        break;
      }
    }

    // Enable Tx Reg Empty Interrupt
    USART_ITConfig(uart_config[ch].uart, USART_IT_TXE, ENABLE);
  }

  return bytesWritten;
}

//******************************************************************************
uint32_t bsp_com_read(bsp_com_t ch, uint8_t * data, uint32_t length)
{
  uint32_t bytesRead = 0;

  if (((uint32_t)ch < BSP_ARRAY_LEN(uart_config)) && data && length)
  {
    while (length--)
    {
      if (bsp_fifo_get(&comFIFO[ch][COM_DIR_RX], data++))
      {
        bytesRead++;
      }
      else
      {
        break;
      }
    }
  }

  return bytesRead;
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
 *
 *
 * \param config
 *
 * \return void
 *******************************************************************************/
static void initIO(uart_config_t const * config)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

  RCC_AHB1PeriphClockCmd(config->txPin.portClock, ENABLE);
  RCC_AHB1PeriphClockCmd(config->rxPin.portClock, ENABLE);

  GPIO_PinAFConfig(config->txPin.port,
                   config->txPin.pinSource,
                   config->altFunction);

  GPIO_PinAFConfig(config->rxPin.port,
                   config->rxPin.pinSource,
                   config->altFunction);

  GPIO_InitStructure.GPIO_Pin = config->txPin.pin;
  GPIO_Init(config->txPin.port, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = config->rxPin.pin;
  GPIO_Init(config->rxPin.port, &GPIO_InitStructure);

  if (config->enablePin.port != NULL)
  {
    RCC_AHB1PeriphClockCmd(config->enablePin.portClock, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = config->enablePin.pin;
    GPIO_Init(config->enablePin.port, &GPIO_InitStructure);

    GPIO_WriteBit(config->enablePin.port, config->enablePin.pin, Bit_SET);
  }
}

//******************************************************************************
/**
 *
 *
 * \param config
 *
 * \return void
 *******************************************************************************/
static void initUART(uart_config_t const * config)
{
  USART_InitTypeDef USART_InitStructure;

  if (config->apb1Clocks)
  {
    RCC_APB1PeriphClockCmd(config->apb1Clocks, ENABLE);
  }

  if (config->apb2Clocks)
  {
    RCC_APB2PeriphClockCmd(config->apb2Clocks, ENABLE);
  }

  USART_DeInit(config->uart);

  USART_StructInit(&USART_InitStructure);

  USART_InitStructure.USART_BaudRate = config->bitRate;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_2;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Parity = USART_Parity_No;

  USART_Init(config->uart, &USART_InitStructure);

  USART_ITConfig(config->uart, USART_IT_TXE, ENABLE);
  USART_ITConfig(config->uart, USART_IT_RXNE, ENABLE);

  vectors_setRamVector(config->irq,  config->isr);
  NVIC_EnableIRQ(config->irq);

  USART_Cmd(config->uart, ENABLE);
}


//******************************************************************************
/**
 *
 *
 * \param uart
 * \param fifoRx
 * \param fifoTx
 *
 * \return void
 *******************************************************************************/
static inline void uartISR(USART_TypeDef * uart,
                           bsp_fifo_t * fifoRx,
                           bsp_fifo_t * fifoTx)
{
  uint8_t data = 0;

  if (USART_GetITStatus(uart, USART_IT_RXNE))
  {
    // Byte recieved, put it in the Rx buffer
    data = uart->DR;
    bsp_fifo_put(fifoRx, &data);
  }

  if (USART_GetITStatus(uart, USART_IT_TXE))
  {
    // Tx Register empty, send the next byte
    if (bsp_fifo_get(fifoTx, &data))
    {
      uart->DR = data;
    }
    else
    {
      // Tx buffer empty, disable Tx Empty Interrupt
      USART_ITConfig(uart, USART_IT_TXE, DISABLE);
    }
  }
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void isr_com0(void)
{
  uartISR(uart_config[0].uart,
          &comFIFO[0][COM_DIR_RX],
          &comFIFO[0][COM_DIR_TX]);
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void isr_com1(void)
{
  uartISR(uart_config[1].uart,
          &comFIFO[1][COM_DIR_RX],
          &comFIFO[1][COM_DIR_TX]);
}


