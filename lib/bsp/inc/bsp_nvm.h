//******************************************************************************
/**
 * \file    bsp_nvm.h
 * \author  Al Liebel, Chad Swenson
 * \date    Feb 2013
 * \brief   Non-Volatile Memory Interface Header
 *
 *    Clarification concerning eeprom read/write function arguments...
 *
 *    1) Each address contains 8-bits of data.
 *       An address for uint16 data -> least significant bit is don't care (assumed zero)
 *       An address for uint32 data -> least significant 2 bits are don't care (assumed zero)
 *
 *    2) Multibyte data is stored and retrieved in the format native to the
 *       machine the code is executing on.
 *         Example:
 *          On a Motorola (Big Endian) processor
 *                     ...write_uint32(E0,0,0x12345678);   // will result in
 *                     ....read_uint8 (E0,0, &d0);         //    d0==0x12
 *                     ....read_uint8 (E0,1, &d1);         //    d1==0x34
 *                     ....read_uint8 (E0,2, &d2);         //    d2==0x56
 *                     ....read_uint8 (E0,3, &d3);         //    d3==0x78
 *
 *          On an Intel (Little Endian) processor
 *                     ...write_uint32(E0,0,0x12345678);   // will result in
 *                     ....read_uint8 (E0,0, &d0);         //    d0==0x78
 *                     ....read_uint8 (E0,1, &d1);         //    d1==0x56
 *                     ....read_uint8 (E0,2, &d2);         //    d2==0x34
 *                     ....read_uint8 (E0,3, &d3);         //    d3==0x12
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

#ifndef BSP_NVM_H
#define BSP_NVM_H

#include <stdint.h>
#include <stdbool.h>
#include "bsp_types.h"
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum bsp_nvm_status_e
{
  BSP_NVM_OK = 0,
  BSP_NVM_FAIL,
  BSP_NVM_BUSY,
  BSP_NVM_NOTAVAIL,
  BSP_NVM_RANGE
} bsp_nvm_status_t;

typedef enum bsp_nvm_test_s
{
  BSP_NVM_TEST_0 = 1,
  BSP_NVM_TEST_1,
  BSP_NVM_NUM_TESTS,

  BSP_NVM_TEST_NONE = 0xFF
} bsp_nvm_test_t;

//******************************************************************************
/**
*
* \param
*
* \return void
*******************************************************************************/
void bsp_nvm_init(void);

//******************************************************************************
/**
*
* \param
*
* \return void
*******************************************************************************/
void bsp_nvm_run(void);

//******************************************************************************
/**
*
* \param
*
* \return bool
*******************************************************************************/
bool bsp_nvm_isBusy(void);

//******************************************************************************
/**
 *
 *
 * \param sect
 * \param address
 * \param length
 * \param data
 *
 * \return bsp_nvm_status_t
 *******************************************************************************/
bsp_nvm_status_t bsp_nvm_read(bsp_nvm_t sect,
                              uint32_t address,
                              uint32_t length,
                              uint8_t * data);

//******************************************************************************
/**
 *
 *
 * \param sect
 * \param address
 * \param length
 * \param data
 *
 * \return bsp_nvm_status_t
 *******************************************************************************/
bsp_nvm_status_t bsp_nvm_write(bsp_nvm_t sect,
                               uint32_t address,
                               uint32_t length,
                               uint8_t  const * data);

//******************************************************************************
/**
 *
 *
 * \param sect
 * \param address
 * \param length
 * \param checksum
 *
 * \return bsp_nvm_status_t
 *******************************************************************************/
bsp_nvm_status_t bsp_nvm_checksum(bsp_nvm_t sect,
                                  uint32_t address,
                                  uint32_t length,
                                  uint16_t * checksum);

//******************************************************************************
/**
 *
 *
 * \param sect
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_nvm_getSize(bsp_nvm_t sect);

//******************************************************************************
/**
 *
 *
 * \param sect
 * \param test
 *
 * \return bsp_nvm_status_t
 *******************************************************************************/
bsp_nvm_status_t bsp_nvm_startTest(bsp_nvm_t sect, uint16_t test);

//******************************************************************************
/**
 *
 *
 * \param sect
 * \param failures
 *
 * \return bsp_nvm_status_t
 *******************************************************************************/
bsp_nvm_status_t bsp_nvm_getTestStatus(bsp_nvm_t sect, uint32_t *failures);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BSP_NVM_H */

