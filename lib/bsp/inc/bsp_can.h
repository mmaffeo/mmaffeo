//******************************************************************************
/**
 * \file    bsp_can.h
 * \author  Chad Swenson
 * \date    January 2013
 * \brief   CAN header
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
#ifndef BSP_CAN_H
#define BSP_CAN_H

#include <stdint.h>
#include <stdbool.h>
#include "bsp_types.h"
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum bsp_can_port_e
{
  BSP_CAN0 = 0,
  BSP_CAN1,
  BSP_CAN_QTY
} bsp_can_port_t;

typedef struct bsp_can_frame_s
{
  uint32_t id;
  uint8_t data[8];
  uint8_t dataLength;
  bool extendedID;
  bool remoteRequest;
} bsp_can_frame_t;

//******************************************************************************
/**
 * Initialize can module
 *
 * \return void
 *******************************************************************************/
void bsp_can_init(void);

//******************************************************************************
/**
 * Check if there is room for a frame in the Tx Buffer
 *
 * \param port
 *
 * \return bool
 * \retval true   The buffer is not full
 * \retval false  The buffer is full
 *******************************************************************************/
bool bsp_can_txBufferNotFull(bsp_can_t port);

//******************************************************************************
/**
 * Check if there are any frames in te Rx Buffer
 *
 * \param port
 *
 * \return bool
 * \retval true   The buffer is not empty
 * \retval false  The buffer is empty
 *******************************************************************************/
bool bsp_can_rxBufferNotEmpty(bsp_can_t port);

//******************************************************************************
/**
 * Attempt to send or buffer an outgoing CAN frame
 *
 * \param port
 * \param frame
 *
 * \return bool
 * \return true   Success
 *******************************************************************************/
bool bsp_can_txFrame(bsp_can_t port, bsp_can_frame_t const *frame);

//******************************************************************************
/**
 * Attempt to pull an incoming CAN frame from the receive buffer
 *
 * \param port
 * \param frame
 *
 * \return bool
 * \return true   Success
 *******************************************************************************/
bool bsp_can_rxFrame(bsp_can_t port, bsp_can_frame_t *frame);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* BSP_CAN_H */

