//******************************************************************************
/**
 * \file    stf4_timer.c
 * \author  Chad Swenson
 * \date    August 2014
 * \brief   STM32F4xx IIC Driver
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
#include <stddef.h>

#include "bsp_common.h"
#include "bsp_clock.h"

#define STF4_INTERNAL (1)
#include "stf4_iic.h"
#include "stm32f4xx.h"
#include "stf4_vectors.h"
#undef STF4_INTERNAL

#define IIC_CHECK_EVENT(e,m)    (((e) & (m)) == (m))

typedef enum iic_portState_e
{
  IIC_PSTATE_IDLE = 0,
  IIC_PSTATE_SEND_START,
  IIC_PSTATE_SEND_CONTROL_WRITE,
  IIC_PSTATE_WRITE_ADDRESS,
  IIC_PSTATE_WRITING,
  IIC_PSTATE_SEND_SECOND_START,
  IIC_PSTATE_SEND_CONTROL_READ,
  IIC_PSTATE_READING,
} iic_portState_t;

typedef struct iic_pinConfig_s
{
  uint32_t portClock;
  GPIO_TypeDef *port;
  uint16_t pin;
  uint16_t pinSource;
} iic_pinConfig_t;

typedef struct iic_portConfig_s
{
  iic_pinConfig_t wpPin;
  iic_pinConfig_t sclPin;
  iic_pinConfig_t sdaPin;
  I2C_TypeDef* iicBase;
  uint32_t iicClock;
  uint8_t altFunction;
  uint32_t bitRate;

  vectors_entry_t isrEvent;
  IRQn_Type irqEvent;
  vectors_entry_t isrError;
  IRQn_Type irqError;

} iic_portConfig_t;

typedef struct iic_portData_s
{
  iic_handle_t * iic_handle;
  iic_portState_t state;
  uint32_t dataIndex;
} iic_portData_t;


//******************************************************************************
// Static Function Prototypes
//******************************************************************************

static bool isConfigValid(iic_handle_t const * handle);
static bool capturePort(iic_handle_t * handle);

static void initIO(iic_portConfig_t const * portConfig);
static void initIIC(iic_portConfig_t const * portConfig);

static void resetPort(iic_portConfig_t const * portConfig, iic_portData_t * portData);

static void iic1_isr(void);
static void iic2_isr(void);


//******************************************************************************
// Static Variables
//******************************************************************************

static iic_portConfig_t const iic_portConfig[] =
{
  {
    { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_2, GPIO_PinSource2 },  // Write Protect Pin
    { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_1, GPIO_PinSource1 },  // SCL Pin
    { RCC_AHB1Periph_GPIOF,   GPIOF,  GPIO_Pin_0, GPIO_PinSource0 },  // SDA Pin
    I2C2,                                                             // IIC Peripheral Base
    RCC_APB1Periph_I2C2,                                              // IIC Clock
    GPIO_AF_I2C2,                                                     // Alternate Function
    400000,                                                           // Bit Rate
    iic1_isr,                                                         // Event ISR
    I2C2_EV_IRQn,                                                     // Event IRQn
    iic2_isr,                                                         // Error ISR
    I2C2_ER_IRQn,                                                     // Error IRQn
  },
  {
    { 0,                      NULL,   0,          0,              },  // Write Protect Pin
    { RCC_AHB1Periph_GPIOH,   GPIOH,  GPIO_Pin_7, GPIO_PinSource7 },  // SCL Pin
    { RCC_AHB1Periph_GPIOH,   GPIOH,  GPIO_Pin_8, GPIO_PinSource8 },  // SDA Pin
    I2C3,                                                             // IIC Peripheral Base
    RCC_APB1Periph_I2C3,                                              // IIC Clock
    GPIO_AF_I2C3,                                                     // Alternate Function
    400000,                                                           // Bit Rate
    iic2_isr,                                                         // Event ISR
    I2C3_EV_IRQn,                                                     // Event IRQn
    iic2_isr,                                                         // Error ISR
    I2C3_ER_IRQn,                                                     // Error IRQn
  }
};

static iic_portData_t iic_portData[BSP_ARRAY_LEN(iic_portConfig)];


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void stf4_iic_init(void)
{
  uint_fast16_t i;

  for (i = 0; i < BSP_ARRAY_LEN(iic_portConfig); i++)
  {
    iic_portData[i].iic_handle = NULL;
    iic_portData[i].state = IIC_PSTATE_IDLE;
    iic_portData[i].dataIndex = 0;

    initIO(&iic_portConfig[i]);
    initIIC(&iic_portConfig[i]);
  }
}

//******************************************************************************
void stf4_iic_initHandle(iic_handle_t * handle, iic_config_t const * config)
{
  if (handle)
  {
    handle->status = IIC_STATUS_SUCCESS;

    handle->operation = IIC_OP_NONE;
    handle->startAddress = 0;
    handle->length = 0;
    handle->data = NULL;

    handle->startTime = 0;
    handle->stopTime = 0;

    handle->writeOpCount = 0;

    handle->config = config;
  }
}

//******************************************************************************
bool stf4_icc_isBusy(iic_handle_t * handle)
{
  iic_status_t status = stf4_iic_getStatus(handle);

  return (status == IIC_STATUS_BUSY);
}

//******************************************************************************
iic_status_t stf4_iic_startOp(iic_handle_t * handle,
                              iic_operation_t operation,
                              uint32_t address,
                              uint32_t length,
                              uint8_t * data)
{
  iic_status_t status = IIC_STATUS_SUCCESS;

  if ((handle == NULL) || (operation >= IIC_NUM_OPS))
  { // NULL data is ok
    status = IIC_STATUS_INVALID_HANDLE;
  }
  else if (!isConfigValid(handle))
  {
    status = IIC_STATUS_INVALID_CONFIG;
  }
  else if (!capturePort(handle))
  {
    status = IIC_STATUS_BUSY;
  }
  else
  { // Start the Operation
    iic_config_t const * config = handle->config;
    iic_portConfig_t const * portConfig = &iic_portConfig[config->port];
    iic_portData_t * portData = &iic_portData[config->port];

    handle->status = IIC_STATUS_BUSY;

    handle->operation = operation;
    handle->startAddress = address;
    handle->length = length;
    handle->data = data;

    I2C_ITConfig(portConfig->iicBase, I2C_IT_EVT, ENABLE);
    I2C_ITConfig(portConfig->iicBase, I2C_IT_ERR, ENABLE);

    portData->state = IIC_PSTATE_SEND_START;
    portData->dataIndex = 0;
    I2C_GenerateSTART(portConfig->iicBase, ENABLE);

    if (operation == IIC_OP_WRITE)
    {
      handle->writeOpCount++;
    }

    handle->startTime = bsp_clock_us();
  }

  return status;
}

//******************************************************************************
iic_status_t stf4_iic_getStatus(iic_handle_t const * handle)
{
  iic_status_t status = IIC_STATUS_INVALID_HANDLE;

  if (handle)
  {
    status = handle->status;
  }

  return status;
}

//******************************************************************************
iic_operation_t stf4_iic_getOp(iic_handle_t const * handle,
                               uint32_t * address,
                               uint32_t * length)
{
  iic_operation_t operation = IIC_OP_NONE;

  if (handle)
  {
    operation = handle->operation;

    if (address)
    {
      *address = handle->startAddress;
    }

    if (length)
    {
      *length = handle->length;
    }
  }

  return operation;
}

//******************************************************************************
uint32_t stf4_iic_getOpTime(iic_handle_t const * handle)
{
  uint32_t opTime = 0;

  if (handle)
  {
    if (handle->status == IIC_STATUS_BUSY)
    {
      opTime = bsp_clock_us();
    }
    else
    {
      opTime = handle->stopTime;
    }

    opTime -= handle->startTime;
  }

  return opTime;
}

//******************************************************************************
void stf4_iic_reset(iic_handle_t const * handle)
{
  if (handle)
  {
    if (isConfigValid(handle))
    {
      resetPort(&iic_portConfig[handle->config->port],
                &iic_portData[handle->config->port]);
    }
  }
}

//******************************************************************************
// Static Function Definitions
//******************************************************************************


//******************************************************************************
/**
 *
 *
 * \param handle
 *
 * \return bool
 *******************************************************************************/
static bool isConfigValid(iic_handle_t const * handle)
{
  bool configValid = false;

  if (handle->config)
  {
    if (handle->config->port < BSP_ARRAY_LEN(iic_portConfig))
    {
      configValid = true;
    }
  }

  return configValid;
}

//******************************************************************************
/**
 *
 *
 * \param handle
 *
 * \return bool
 *******************************************************************************/
static bool capturePort(iic_handle_t * handle)
{
  bool success = false;

  if (iic_portData[handle->config->port].iic_handle == NULL)
  {
    iic_portData[handle->config->port].iic_handle = handle;
    success = true;
  }

  return success;
}

//******************************************************************************
/**
 *
 *
 * \param portConfig
 *
 * \return void
 *******************************************************************************/
static void initIO(iic_portConfig_t const * portConfig)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

  // Init Write Protect pins
  if (portConfig->wpPin.port)
  {
    RCC_AHB1PeriphClockCmd(portConfig->wpPin.portClock, ENABLE);

    GPIO_InitStructure.GPIO_Pin = portConfig->wpPin.pin;
    GPIO_Init(portConfig->wpPin.port, &GPIO_InitStructure);

    GPIO_ResetBits(portConfig->wpPin.port, portConfig->wpPin.pin);
  }

  // Init SDA and SCL pins
  RCC_AHB1PeriphClockCmd(portConfig->sclPin.portClock, ENABLE);
  RCC_AHB1PeriphClockCmd(portConfig->sdaPin.portClock, ENABLE);

  GPIO_PinAFConfig(portConfig->sclPin.port,
                   portConfig->sclPin.pinSource,
                   portConfig->altFunction);

  GPIO_PinAFConfig(portConfig->sdaPin.port,
                   portConfig->sdaPin.pinSource,
                   portConfig->altFunction);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;

  GPIO_InitStructure.GPIO_Pin = portConfig->sclPin.pin;
  GPIO_Init(portConfig->sclPin.port, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = portConfig->sdaPin.pin;
  GPIO_Init(portConfig->sdaPin.port, &GPIO_InitStructure);
}

//******************************************************************************
/**
 *
 *
 * \param portConfig
 *
 * \return void
 *******************************************************************************/
static void initIIC(iic_portConfig_t const * portConfig)
{
  I2C_InitTypeDef I2C_InitStruct;

  RCC_APB1PeriphClockCmd(portConfig->iicClock, ENABLE);

  I2C_DeInit(portConfig->iicBase);

  I2C_StructInit(&I2C_InitStruct);
  I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStruct.I2C_ClockSpeed = portConfig->bitRate;
  I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStruct.I2C_OwnAddress1 = 0;
  I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;

  I2C_Init(portConfig->iicBase, &I2C_InitStruct);

  I2C_ITConfig(portConfig->iicBase,
               I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR,
               DISABLE);

  vectors_setRamVector(portConfig->irqEvent,  portConfig->isrEvent);
  NVIC_EnableIRQ(portConfig->irqEvent);

  vectors_setRamVector(portConfig->irqError,  portConfig->isrEvent);
  NVIC_EnableIRQ(portConfig->irqError);
}

//******************************************************************************
static void resetPort(iic_portConfig_t const * portConfig, iic_portData_t * portData)
{
  portData->state = IIC_PSTATE_IDLE;
  portData->dataIndex = 0;

  if (portData->iic_handle)
  {
    portData->iic_handle->status = IIC_STATUS_FAILED;
    portData->iic_handle->stopTime = bsp_clock_us();
    portData->iic_handle = NULL;
  }

  initIIC(portConfig);
}


//******************************************************************************
// ISR Definitions
//******************************************************************************

//******************************************************************************
/**
 *
 *
 * \param iicEvent
 * \param portConfig
 * \param portData
 * \param iic_handle
 *
 * \return bool
 *******************************************************************************/
static inline bool sendControlWrite(uint32_t iicEvent,
                                    iic_portConfig_t const * portConfig,
                                    iic_portData_t * portData,
                                    iic_handle_t * iic_handle)
{
  bool abort = true;

  if (IIC_CHECK_EVENT(iicEvent, I2C_EVENT_MASTER_MODE_SELECT))
  {
    portData->state = IIC_PSTATE_SEND_CONTROL_WRITE;
    I2C_Send7bitAddress(portConfig->iicBase,
                        iic_handle->config->deviceAddress,
                        I2C_Direction_Transmitter);

    abort = false;
  }

  return abort;
}

//******************************************************************************
/**
 *
 *
 * \param iicEvent
 * \param portConfig
 * \param portData
 * \param iic_handle
 *
 * \return bool
 *******************************************************************************/
static inline bool writeAddress(uint32_t iicEvent,
                                iic_portConfig_t const * portConfig,
                                iic_portData_t * portData,
                                iic_handle_t * iic_handle)
{
/* BUSY, MSL and AF flags */
#define  I2C_EVENT_MASTER_FAILED_CTRL     ((uint32_t)0x00030400)

  bool abort = true;

  if (IIC_CHECK_EVENT(iicEvent, I2C_EVENT_MASTER_FAILED_CTRL))
  {
    portData->state = IIC_PSTATE_SEND_START;
    I2C_GenerateSTART(portConfig->iicBase, ENABLE);

    I2C_ClearFlag(portConfig->iicBase, I2C_FLAG_AF);

    abort = false;
  }
  else if (IIC_CHECK_EVENT(iicEvent, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    portData->state = IIC_PSTATE_WRITE_ADDRESS;

    if (iic_handle->config->memAddressSize > 1) // Two byte Address
    {
      portConfig->iicBase->DR = (uint8_t)(iic_handle->startAddress >> 8);

      // Wait for data reg to be moved to shift reg
      while (!(portConfig->iicBase->SR1 & (uint16_t)I2C_FLAG_TXE));

      portConfig->iicBase->DR = (uint8_t)iic_handle->startAddress;
    }
    else  // One Byte Address
    {
      portConfig->iicBase->DR = (uint8_t)iic_handle->startAddress;
    }

    if (iic_handle->operation == IIC_OP_WRITE)
    {
      I2C_ITConfig(portConfig->iicBase, I2C_IT_BUF, ENABLE);
    }

    abort = false;
  }

  return abort;
}

//******************************************************************************
/**
 *
 *
 * \param iicEvent
 * \param portConfig
 * \param portData
 * \param iic_handle
 *
 * \return bool
 *******************************************************************************/
static inline bool writeByte(uint32_t iicEvent,
                             iic_portConfig_t const * portConfig,
                             iic_portData_t * portData,
                             iic_handle_t * iic_handle)
{
  bool abort = true;

  if (IIC_CHECK_EVENT(iicEvent, I2C_EVENT_MASTER_BYTE_TRANSMITTING))
  {
    portData->state = IIC_PSTATE_WRITING;

    if (portData->dataIndex < iic_handle->length)
    {
      if (iic_handle->data != NULL)
      {
        portConfig->iicBase->DR = iic_handle->data[portData->dataIndex];
      }

      portData->dataIndex++;

      if (portData->dataIndex == iic_handle->length)
      {
        I2C_ITConfig(portConfig->iicBase, I2C_IT_BUF, DISABLE);
      }
    }
    else
    {
      // Trigger stop after current byte is transfered
      I2C_GenerateSTOP(portConfig->iicBase, ENABLE);
      I2C_ITConfig(portConfig->iicBase, I2C_IT_EVT | I2C_IT_BUF, DISABLE);

      iic_handle->status = IIC_STATUS_SUCCESS;
      iic_handle->stopTime = bsp_clock_us();

      portData->state = IIC_PSTATE_IDLE;
      portData->dataIndex = 0;
      portData->iic_handle = NULL;
    }

    abort = false;
  }

  return abort;
}

//******************************************************************************
/**
 *
 *
 * \param iicEvent
 * \param portConfig
 * \param portData
 * \param iic_handle
 *
 * \return bool
 *******************************************************************************/
static inline bool sendSecondStart(uint32_t iicEvent,
                                   iic_portConfig_t const * portConfig,
                                   iic_portData_t * portData,
                                   iic_handle_t * iic_handle)
{
  bool abort = true;

  if (IIC_CHECK_EVENT(iicEvent, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    portData->state = IIC_PSTATE_SEND_SECOND_START;
    I2C_GenerateSTART(portConfig->iicBase, ENABLE);

    // Dummy write to Data reg to clear ByteTransferFinished Flag
    portConfig->iicBase->DR = 0;

    abort = false;
  }

  return abort;
}

//******************************************************************************
/**
 *
 *
 * \param iicEvent
 * \param portConfig
 * \param portData
 * \param iic_handle
 *
 * \return bool
 *******************************************************************************/
static inline bool sendControlRead(uint32_t iicEvent,
                                   iic_portConfig_t const * portConfig,
                                   iic_portData_t * portData,
                                   iic_handle_t * iic_handle)
{
  bool abort = true;

  if (IIC_CHECK_EVENT(iicEvent, I2C_EVENT_MASTER_MODE_SELECT))
  {
    FunctionalState ackEnable;

    portData->state = IIC_PSTATE_SEND_CONTROL_READ;
    I2C_Send7bitAddress(portConfig->iicBase,
                        iic_handle->config->deviceAddress,
                        I2C_Direction_Receiver);

    // Only enable ACKing if we are RXing more than one byte
    ackEnable = (iic_handle->length > 1) ? ENABLE : DISABLE;
    I2C_AcknowledgeConfig(portConfig->iicBase, ackEnable);
    I2C_ITConfig(portConfig->iicBase, I2C_IT_BUF, ENABLE);

    abort = false;
  }

  return abort;
}

//******************************************************************************
/**
 *
 *
 * \param iicEvent
 * \param portConfig
 * \param portData
 * \param iic_handle
 *
 * \return bool
 *******************************************************************************/
static inline bool readByte(uint32_t iicEvent,
                            iic_portConfig_t const * portConfig,
                            iic_portData_t * portData,
                            iic_handle_t * iic_handle)
{
  bool abort = true;

  if (IIC_CHECK_EVENT(iicEvent, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    portData->state = IIC_PSTATE_READING;

    if (portData->dataIndex < iic_handle->length)
    {
      if (iic_handle->data != NULL)
      {
        iic_handle->data[portData->dataIndex] = (uint8_t)portConfig->iicBase->DR;
      }

      portData->dataIndex++;

      // Disable Acking of last recieved byte
      if (portData->dataIndex == iic_handle->length)
      {
        I2C_AcknowledgeConfig(portConfig->iicBase, DISABLE);
      }
    }
    else
    {
      I2C_GenerateSTOP(portConfig->iicBase, ENABLE);
      I2C_ITConfig(portConfig->iicBase, I2C_IT_EVT | I2C_IT_BUF, DISABLE);

      iic_handle->status = IIC_STATUS_SUCCESS;
      iic_handle->stopTime = bsp_clock_us();

      portData->state = IIC_PSTATE_IDLE;
      portData->dataIndex = 0;
      portData->iic_handle = NULL;
    }

    abort = false;
  }
  else if (IIC_CHECK_EVENT(iicEvent, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    portData->state = IIC_PSTATE_READING;

    // Master Reciever mode selected but not data yet
    // These flags are already cleared by calling I2C_GetLastEvent()

    abort = false;
  }

  return abort;
}

//******************************************************************************
/**
 *
 *
 * \param portConfig
 * \param portData
 *
 * \return void
 *******************************************************************************/
static inline void isrEvent(iic_portConfig_t const * portConfig, iic_portData_t * portData)
{
// Interrupt                                        Flag      Enable
//
// Start bit sent (Master)                          SB        ITEVFEN
// Address sent (Master) or Address matched (Slave) ADDR      ITEVFEN
// 10-bit header sent (Master)                      ADD10     ITEVFEN
// Stop received (Slave)                            STOPF     ITEVFEN
// Data byte transfer finished                      BTF       ITEVFEN
//
// Receive buffer not empty                         RxNE      ITEVFEN && ITBUFEN
// Transmit buffer empty                            TxE       ITEVFEN && ITBUFEN
//
// Bus error                                        BERR      ITERREN
// Arbitration loss (Master)                        ARLO      ITERREN
// Acknowledge failure                              AF        ITERREN
// Overrun/Underrun                                 OVR       ITERREN
// PEC error                                        PECERR    ITERREN
// Timeout/Tlow error                               TIMEOUT   ITERREN
// SMBus Alert                                      SMBALERT  ITERREN


  iic_handle_t * iic_handle = portData->iic_handle;
  uint32_t iicEvent = I2C_GetLastEvent(portConfig->iicBase);
  bool abort = false;
  uint32_t errorMask = (uint16_t)(I2C_IT_SMBALERT
                                  | I2C_IT_TIMEOUT
                                  | I2C_IT_PECERR
                                  | I2C_IT_OVR
                                  | I2C_IT_AF
                                  | I2C_IT_ARLO
                                  | I2C_IT_BERR);

  if (portData->state == IIC_PSTATE_SEND_CONTROL_WRITE)
  {
    // We need to tolerate Ack Failures when sending the write control byte
    errorMask &= ~I2C_IT_AF;
  }

  if (iicEvent & errorMask)
  {
    abort = true;
  }

  if ((iic_handle != NULL) && !abort)
  {
    switch (portData->state)
    {
    case IIC_PSTATE_SEND_START:
      abort = sendControlWrite(iicEvent, portConfig, portData, iic_handle);
      break;

    case IIC_PSTATE_SEND_CONTROL_WRITE:
      abort = writeAddress(iicEvent, portConfig, portData, iic_handle);
      break;

    case IIC_PSTATE_WRITE_ADDRESS:
      if (iic_handle->operation == IIC_OP_WRITE)
      {
        abort = writeByte(iicEvent, portConfig, portData, iic_handle);
      }
      else
      {
        abort = sendSecondStart(iicEvent, portConfig, portData, iic_handle);
      }
      break;

    case IIC_PSTATE_WRITING:
      abort = writeByte(iicEvent, portConfig, portData, iic_handle);
      break;

    case IIC_PSTATE_SEND_SECOND_START:
      abort = sendControlRead(iicEvent, portConfig, portData, iic_handle);
      break;

    case IIC_PSTATE_SEND_CONTROL_READ:
    case IIC_PSTATE_READING:
      abort = readByte(iicEvent, portConfig, portData, iic_handle);
      break;

    case IIC_PSTATE_IDLE:
    default:
      abort = true;
      break;
    }
  }

  if (abort)
  {
    resetPort(portConfig, portData);
  }
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void iic1_isr(void)
{
  isrEvent(&iic_portConfig[0], &iic_portData[0]);
}

//******************************************************************************
/**
 *
 *
 * \return void
 *******************************************************************************/
static void iic2_isr(void)
{
  isrEvent(&iic_portConfig[1], &iic_portData[1]);
}


