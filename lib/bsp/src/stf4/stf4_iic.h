//******************************************************************************
/**
 * \file    stf4_iic.h
 * \author  Chad Swenson
 * \date    August 2014
 * \brief   STM32F4xx IIC Driver Header
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
#ifndef STF4_IIC_H
#define STF4_IIC_H

#include <stdint.h>
#include <stdbool.h>

#include "stm32f4xx.h"

#ifndef STF4_INTERNAL
#error "This file for internal stf4 use only"
#endif

typedef enum iic_status_e
{
  IIC_STATUS_SUCCESS = 0,
  IIC_STATUS_FAILED,
  IIC_STATUS_BUSY,

  IIC_STATUS_INVALID_CONFIG,
  IIC_STATUS_INVALID_HANDLE
} iic_status_t;

typedef enum iic_operation_e
{
  IIC_OP_RAND_READ = 0,
  IIC_OP_WRITE,

  IIC_NUM_OPS,
  IIC_OP_NONE
} iic_operation_t;

typedef struct iic_config_s
{
  uint16_t port;
  uint8_t deviceAddress;
  uint8_t memAddressSize;

} iic_config_t;

typedef struct iic_handle_s
{
  iic_status_t status;

  iic_operation_t operation;
  uint32_t startAddress;
  uint32_t length;
  uint8_t * data;

  uint32_t startTime;
  uint32_t stopTime;

  uint32_t writeOpCount;

  iic_config_t const * config;
} iic_handle_t;


//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
void stf4_iic_init(void);

//******************************************************************************
/**
 *
 *
 * \param handle
 * \param config
 *
 * \return void
 *******************************************************************************/
void stf4_iic_initHandle(iic_handle_t * handle, iic_config_t const * config);

//******************************************************************************
/**
 *
 *
 * \param handle
 *
 * \return bool
 *******************************************************************************/
bool stf4_icc_isBusy(iic_handle_t * handle);

//******************************************************************************
/**
 *
 *
 * \param handle
 * \param operation
 * \param address
 * \param length
 * \param data
 *
 * \return iic_status_t
 *******************************************************************************/
iic_status_t stf4_iic_startOp(iic_handle_t * handle,
                              iic_operation_t operation,
                              uint32_t address,
                              uint32_t length,
                              uint8_t * data);

//******************************************************************************
/**
 *
 *
 * \param handle
 *
 * \return iic_status_t
 *******************************************************************************/
iic_status_t stf4_iic_getStatus(iic_handle_t const * handle);

//******************************************************************************
/**
*
*
* \param handle
* \param address
* \param length
*
* \return iic_operation_t
*******************************************************************************/
iic_operation_t stf4_iic_getOp(iic_handle_t const * handle,
                               uint32_t * address,
                               uint32_t * length);

//******************************************************************************
/**
 *
 *
 * \param handle
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t stf4_iic_getOpTime(iic_handle_t const * handle);

//******************************************************************************
/**
 *
 *
 * \param handle
 *
 * \return void
 *******************************************************************************/
void stf4_iic_reset(iic_handle_t const * handle);


#endif /* STF4_IIC_H */

