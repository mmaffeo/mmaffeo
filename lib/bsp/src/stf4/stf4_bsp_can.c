//******************************************************************************
/**
 * \file    stf4_bsp_can.c
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   STM32F4xx Specific Hardware can Source
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
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


#include "stf4_fifo.h"

#define STF4_INTERNAL (1)
#include "stf4_bsp_can.h"
#include "stm32f4xx.h"
#include "stm32f4xx_can.h"
#include "stf4_vectors.h"
#undef STF4_INTERNAL


//******************************************************************************
// Defines
//******************************************************************************
#if 0 //DB_WS_OPEN407I

#define CAN_1_ENABLE         (1)
#define CAN_2_ENABLE         (1)

#define CAN_1_PORT           (0)     // CAN 1 mapped to PORT 1
#define CAN_2_PORT           (1)     // CAN 2 mapped to PORT 2

#define CAN_1_RX_GPIO_CLK    (RCC_AHB1Periph_GPIOI)
#define CAN_1_RX_GPIO_PORT   (GPIOI)
#define CAN_1_RX_PIN         (GPIO_Pin_9)
#define CAN_1_RX_SOURCE      (GPIO_PinSource9)

#define CAN_1_TX_GPIO_CLK    (RCC_AHB1Periph_GPIOH)
#define CAN_1_TX_GPIO_PORT   (GPIOH)
#define CAN_1_TX_PIN         (GPIO_Pin_13)
#define CAN_1_TX_SOURCE      (GPIO_PinSource13)

#define CAN_2_RX_GPIO_CLK    (RCC_AHB1Periph_GPIOB)
#define CAN_2_RX_GPIO_PORT   (GPIOB)
#define CAN_2_RX_PIN         (GPIO_Pin_5)
#define CAN_2_RX_SOURCE      (GPIO_PinSource5)

#define CAN_2_TX_GPIO_CLK    (RCC_AHB1Periph_GPIOB)
#define CAN_2_TX_GPIO_PORT   (GPIOB)
#define CAN_2_TX_PIN         (GPIO_Pin_6)
#define CAN_2_TX_SOURCE      (GPIO_PinSource6)

#else

#define CAN_1_ENABLE         (1)
#define CAN_2_ENABLE         (1)

#define CAN_1_PORT           (0)     // CAN 1 mapped to PORT 1
#define CAN_2_PORT           (1)     // CAN 2 mapped to PORT 2

#define CAN_1_RX_GPIO_CLK    (RCC_AHB1Periph_GPIOD)
#define CAN_1_RX_GPIO_PORT   (GPIOD)
#define CAN_1_RX_PIN         (GPIO_Pin_0)
#define CAN_1_RX_SOURCE      (GPIO_PinSource0)

#define CAN_1_TX_GPIO_CLK    (RCC_AHB1Periph_GPIOD)
#define CAN_1_TX_GPIO_PORT   (GPIOD)
#define CAN_1_TX_PIN         (GPIO_Pin_1)
#define CAN_1_TX_SOURCE      (GPIO_PinSource1)

#define CAN_2_RX_GPIO_CLK    (RCC_AHB1Periph_GPIOB)
#define CAN_2_RX_GPIO_PORT   (GPIOB)
#define CAN_2_RX_PIN         (GPIO_Pin_5)
#define CAN_2_RX_SOURCE      (GPIO_PinSource5)

#define CAN_2_TX_GPIO_CLK    (RCC_AHB1Periph_GPIOB)
#define CAN_2_TX_GPIO_PORT   (GPIOB)
#define CAN_2_TX_PIN         (GPIO_Pin_6)
#define CAN_2_TX_SOURCE      (GPIO_PinSource6)

#endif

enum can_direction_e
{
  CAN_DIR_TX = 0,
  CAN_DIR_RX,
  CAN_NUM_DIRS
};

//******************************************************************************
// Static Variables
//******************************************************************************
static bsp_can_frame_t txBufferDataPort0[48];    // TODO buffer native STM32 frames
static bsp_can_frame_t rxBufferDataPort0[48];    //  to maybe reduce interrupt time
static bsp_can_frame_t txBufferDataPort1[48];
static bsp_can_frame_t rxBufferDataPort1[48];

static bsp_fifo_t canFIFO[BSP_CAN_QTY][CAN_NUM_DIRS];
static CAN_TypeDef * const canRegs[BSP_CAN_QTY] =
{
#if CAN_1_PORT == 0
  CAN1,   // PORT 0 connected to CAN 1
  CAN2    // PORT 1 connected to CAN 2
#else
  CAN2,   // PORT 0 connected to CAN 2
  CAN1    // PORT 1 connected to CAN 1
#endif
};

//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void initFIFOs(void);
static void initGPIO(void);
static void initCAN(void);

static void irqh_CAN1_TX(void);
static void irqh_CAN2_TX(void);
static void irqh_CAN1_RX0(void);
static void irqh_CAN2_RX0(void);
static void irqh_CAN1_SCE(void);
static void irqh_CAN2_SCE(void);

//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_can_init(void)
{
  initFIFOs();
  initGPIO();
  initCAN();

  vectors_setRamVector(CAN1_TX_IRQn,  irqh_CAN1_TX);
  vectors_setRamVector(CAN1_RX0_IRQn, irqh_CAN1_RX0);
  vectors_setRamVector(CAN1_SCE_IRQn, irqh_CAN1_SCE);

  vectors_setRamVector(CAN2_TX_IRQn,  irqh_CAN2_TX);
  vectors_setRamVector(CAN2_RX0_IRQn, irqh_CAN2_RX0);
  vectors_setRamVector(CAN2_SCE_IRQn, irqh_CAN2_SCE);

#if CAN_1_ENABLE
  NVIC_EnableIRQ(CAN1_TX_IRQn);
  NVIC_EnableIRQ(CAN1_RX0_IRQn);
  //NVIC_EnableIRQ(CAN1_SCE_IRQn);
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
#endif

#if CAN_2_ENABLE
  NVIC_EnableIRQ(CAN2_TX_IRQn);
  NVIC_EnableIRQ(CAN2_RX0_IRQn);
  //NVIC_EnableIRQ(CAN2_SCE_IRQn);
  CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
#endif

}

//******************************************************************************
bool bsp_can_txBufferNotFull(bsp_can_t port)
{
  bool notFull = false;

  if ((uint32_t)port < BSP_CAN_QTY)
  {
    notFull = bsp_fifo_notFull(&canFIFO[port][CAN_DIR_TX]);
  }

  return notFull;
}

//******************************************************************************
bool bsp_can_rxBufferNotEmpty(bsp_can_t port)
{
  bool notEmpty = false;

  if ((uint32_t)port < BSP_CAN_QTY)
  {
    notEmpty = bsp_fifo_notEmpty(&canFIFO[port][CAN_DIR_RX]);
  }

  return notEmpty;
}

//******************************************************************************
bool bsp_can_txFrame(bsp_can_t port, bsp_can_frame_t const *frame)
{
  bool success = false;

  if (((uint32_t)port < BSP_CAN_QTY) && (frame != NULL))
  {
    success = bsp_fifo_put(&canFIFO[port][CAN_DIR_TX], frame);

    // Kick off the Tx Interrupt
    NVIC_SetPendingIRQ((canRegs[port] == CAN1) ? CAN1_TX_IRQn : CAN2_TX_IRQn);
  }

  return success;
}

//******************************************************************************
bool bsp_can_rxFrame(bsp_can_t port, bsp_can_frame_t *frame)
{
  bool success = false;

  if (((uint32_t)port < BSP_CAN_QTY) && (frame != NULL))
  {
    success = bsp_fifo_get(&canFIFO[port][CAN_DIR_RX], frame);
  }

  return success;
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
static void initFIFOs(void)
{
  bsp_fifo_init(&canFIFO[BSP_CAN0][CAN_DIR_TX],
               txBufferDataPort0,
               sizeof(txBufferDataPort0),
               sizeof(bsp_can_frame_t));
  bsp_fifo_init(&canFIFO[BSP_CAN0][CAN_DIR_RX],
               rxBufferDataPort0,
               sizeof(rxBufferDataPort0),
               sizeof(bsp_can_frame_t));

  bsp_fifo_init(&canFIFO[BSP_CAN1][CAN_DIR_TX],
               txBufferDataPort1,
               sizeof(txBufferDataPort1),
               sizeof(bsp_can_frame_t));
  bsp_fifo_init(&canFIFO[BSP_CAN1][CAN_DIR_RX],
               rxBufferDataPort1,
               sizeof(rxBufferDataPort1),
               sizeof(bsp_can_frame_t));
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void initGPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

#if CAN_1_ENABLE
  RCC_AHB1PeriphClockCmd(CAN_1_RX_GPIO_CLK | CAN_1_TX_GPIO_CLK, ENABLE);
  GPIO_PinAFConfig(CAN_1_RX_GPIO_PORT, CAN_1_RX_SOURCE, GPIO_AF_CAN1);
  GPIO_PinAFConfig(CAN_1_TX_GPIO_PORT, CAN_1_TX_SOURCE, GPIO_AF_CAN1);

  GPIO_InitStructure.GPIO_Pin = CAN_1_RX_PIN;
  GPIO_Init(CAN_1_RX_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = CAN_1_TX_PIN;
  GPIO_Init(CAN_1_TX_GPIO_PORT, &GPIO_InitStructure);
#endif

#if CAN_2_ENABLE
  RCC_AHB1PeriphClockCmd(CAN_2_RX_GPIO_CLK | CAN_2_TX_GPIO_CLK, ENABLE);
  GPIO_PinAFConfig(CAN_2_RX_GPIO_PORT, CAN_2_RX_SOURCE, GPIO_AF_CAN2);
  GPIO_PinAFConfig(CAN_2_TX_GPIO_PORT, CAN_2_TX_SOURCE, GPIO_AF_CAN2);

  GPIO_InitStructure.GPIO_Pin = CAN_2_RX_PIN;
  GPIO_Init(CAN_2_RX_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = CAN_2_TX_PIN;
  GPIO_Init(CAN_2_TX_GPIO_PORT, &GPIO_InitStructure);
#endif
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void initCAN(void)
{
  CAN_InitTypeDef CAN_InitStructure;
  CAN_FilterInitTypeDef CAN_FilterInitStructure;

  // We need CAN1 on to use CAN2
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

#if CAN_2_ENABLE
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
#endif

  /* CAN register init */
  CAN_DeInit(CAN1);
  CAN_DeInit(CAN2);

  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = ENABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = ENABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

  /* CAN Baudrate = 250 kbps (CAN clocked at 42 MHz) sasmple point 85.7%*/
  CAN_InitStructure.CAN_BS1 = CAN_BS1_11tq;
  CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
  CAN_InitStructure.CAN_Prescaler = 12;

#if CAN_1_ENABLE
  CAN_Init(CAN1, &CAN_InitStructure);
#endif

#if CAN_2_ENABLE
  CAN_Init(CAN2, &CAN_InitStructure);
#endif

  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;

#if CAN_1_ENABLE
  CAN_FilterInitStructure.CAN_FilterNumber = 0;
  CAN_FilterInit(&CAN_FilterInitStructure);
#endif

#if CAN_2_ENABLE
  CAN_FilterInitStructure.CAN_FilterNumber = 14;
  CAN_FilterInit(&CAN_FilterInitStructure);
#endif
}

//******************************************************************************
/**
 *
 *
 * \param canReg
 * \param port
 * \param txMsg
 * \param frame
 *
 * \return void
 *******************************************************************************/
static inline void irqh_CANn_TX(CAN_TypeDef *canReg,
                                uint16_t port,
                                CanTxMsg *txMsg,
                                bsp_can_frame_t *frame)
{
  // Make sure there is a mailbox open before pulling from the buffer
  if (canReg->TSR & CAN_TSR_TME)
  {
    if (bsp_fifo_get(&canFIFO[port][CAN_DIR_TX], frame))
    {
      txMsg->IDE = frame->extendedID ? CAN_ID_EXT : CAN_ID_STD;
      txMsg->ExtId = frame->extendedID ? frame->id : 0;
      txMsg->StdId = frame->extendedID ? 0 : frame->id;
      txMsg->RTR = frame->remoteRequest ? CAN_RTR_Remote : CAN_RTR_Data;

      txMsg->DLC = frame->dataLength;
      txMsg->Data[0] = frame->data[0];
      txMsg->Data[1] = frame->data[1];
      txMsg->Data[2] = frame->data[2];
      txMsg->Data[3] = frame->data[3];
      txMsg->Data[4] = frame->data[4];
      txMsg->Data[5] = frame->data[5];
      txMsg->Data[6] = frame->data[6];
      txMsg->Data[7] = frame->data[7];

      CAN_Transmit(canReg, txMsg);
    }
  }

  if (bsp_fifo_notEmpty(&canFIFO[port][CAN_DIR_TX]))
  {
    CAN_ITConfig(canReg, CAN_IT_TME, ENABLE);
  }
  else
  {
    CAN_ITConfig(canReg, CAN_IT_TME, DISABLE);
  }
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void irqh_CAN1_TX(void)
{
  static CanTxMsg txMsg;
  static bsp_can_frame_t frame;
  irqh_CANn_TX(CAN1, CAN_1_PORT, &txMsg, &frame);
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void irqh_CAN2_TX(void)
{
  static CanTxMsg txMsg;
  static bsp_can_frame_t frame;
  irqh_CANn_TX(CAN2, CAN_2_PORT, &txMsg, &frame);
}

//******************************************************************************
/**
 *
 *
 * \param canReg
 * \param port
 * \param rxMessage
 * \param frame
 *
 * \return void
 *******************************************************************************/
static inline void irqh_CANn_RX0(CAN_TypeDef *canReg,
                                 uint16_t port,
                                 CanRxMsg *rxMsg,
                                 bsp_can_frame_t *frame)
{
  CAN_Receive(canReg, CAN_FIFO0, rxMsg);

  frame->extendedID = (rxMsg->IDE == CAN_ID_EXT);
  frame->id = frame->extendedID ? rxMsg->ExtId : rxMsg->StdId;
  frame->remoteRequest = (rxMsg->RTR == CAN_RTR_Remote);

  frame->dataLength = rxMsg->DLC;
  frame->data[0] = rxMsg->Data[0];
  frame->data[1] = rxMsg->Data[1];
  frame->data[2] = rxMsg->Data[2];
  frame->data[3] = rxMsg->Data[3];
  frame->data[4] = rxMsg->Data[4];
  frame->data[5] = rxMsg->Data[5];
  frame->data[6] = rxMsg->Data[6];
  frame->data[7] = rxMsg->Data[7];

  bsp_fifo_put(&canFIFO[port][CAN_DIR_RX], frame);
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void irqh_CAN1_RX0(void)
{
  static CanRxMsg rxMessage;
  static bsp_can_frame_t frame;
  irqh_CANn_RX0(CAN1, CAN_1_PORT, &rxMessage, &frame);
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void irqh_CAN2_RX0(void)
{
  static CanRxMsg rxMessage;
  static bsp_can_frame_t frame;
  irqh_CANn_RX0(CAN2, CAN_2_PORT, &rxMessage, &frame);
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void irqh_CAN1_SCE(void)
{

}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void irqh_CAN2_SCE(void)
{

}

