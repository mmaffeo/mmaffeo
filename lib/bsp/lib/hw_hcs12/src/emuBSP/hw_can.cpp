//******************************************************************************
/**
 * \file    hw_can.cpp
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Emulation of hw_can on BSP
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
#include "hw_can.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "bsp_types.h"
#include "bsp_common.h"
#include "bsp_can.h"


//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void processRxFrames(uint8_t handler);
static void frame2Msg(bsp_can_frame_t const *frame, hw_can_msg_t * msg);
static void msg2Frame(hw_can_msg_t const *msg, bsp_can_frame_t * frame);


//******************************************************************************
// Static Variables
//******************************************************************************
static bsp_can_t const bspCANMap[HWC_CAN_QTY] =
{
  BSP_CAN_1,  // HWC_CAN0
  BSP_CAN_2,  // HWC_CAN4
};


//******************************************************************************
// Global Variables
//******************************************************************************
hw_can_tx_scheduler_t hw_can_tx_scheduler[HWC_CAN_QTY];
hw_can_rx_handler_t hw_can_rx_handler[HWC_CAN_QTY];
hw_can_txq_t hw_can_txq[HWC_CAN_QTY];


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void hw_can_initialize(void)
{
  for (uint8_t i = 0; i < HWC_CAN_QTY; i++)
  {
    hw_can_tx_scheduler[i].initialize(i);
    hw_can_rx_handler[i].initialize();
    hw_can_txq[i].initialize(i);
  }
}

//******************************************************************************
void hw_can_update(void)
{
  for (uint8_t i = 0; i < HWC_CAN_QTY; i++ )
  {
    hw_can_tx_scheduler[i].update();
    hw_can_rx_handler[i].update();
    processRxFrames(i);
  }
}

//******************************************************************************
void hw_can_update_fast(void)
{
  for (uint8_t i = 0; i < HWC_CAN_QTY; i++ )
  {
    processRxFrames(i);
  }
}

//******************************************************************************
bool hw_can_TxBufferAvailiable(uint8_t port)
{
  return bsp_can_txBufferNotFull(bspCANMap[port]);
}

//******************************************************************************
void hw_can_SendFrame(uint8_t port, hw_can_msg_t *msg)
{
  static bsp_can_frame_t frame;

  msg2Frame(msg, &frame);
  bsp_can_txFrame(bspCANMap[port], &frame);
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
 *
 *
 * \param port
 *
 * \return void
 *******************************************************************************/
static void processRxFrames(uint8_t port)
{
  static bsp_can_frame_t frame;
  static hw_can_msg_t msg;

  while (bsp_can_rxFrame(bspCANMap[port], &frame))
  {
    frame2Msg(&frame, &msg);
    hw_can_rx_handler[port].process_msg(&msg);
  }
}

//******************************************************************************
/**
 * Copy a BSP CAN Frame to a HW CAN Msg
 *
 * \param frame BSP CAN Frame
 * \param msg HW CAN Msg
 *
 * \return void
 *******************************************************************************/
static void frame2Msg(bsp_can_frame_t const *frame, hw_can_msg_t * msg)
{
  if (frame->extendedID)
  {
    msg->id.set_extID(frame->id);
    // Set the SRR bit TODO
    msg->id.IDR[1] |= 0x10;
  }
  else
  {
    msg->id.set_stdID((uint16_t)frame->id);
  }

  msg->DLR = frame->dataLength;

  for (uint_fast16_t i = 0; i < BSP_ARRAY_LEN(msg->DSR); i++)
  {
    msg->DSR[i] = frame->data[i];
  }
}

//******************************************************************************
/**
 * Copy a HW CAN Msg to a BSP CAN Frame
 *
 * \param msg HW CAN Msg
 * \param frame BSP CAN Frame
 *
 * \return void
 *******************************************************************************/
static void msg2Frame(hw_can_msg_t const *msg, bsp_can_frame_t * frame)
{
  frame->extendedID = msg->id.Extended_ID();
  frame->remoteRequest = false; // TODO
  frame->id = msg->id.Get_ID();
  frame->dataLength = msg->DLR;

  for (uint_fast16_t i = 0; i < BSP_ARRAY_LEN(frame->data); i++)
  {
    frame->data[i] = msg->DSR[i];
  }
}


