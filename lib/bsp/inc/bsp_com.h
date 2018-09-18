//******************************************************************************
/**
 * \file    bsp_com.h
 * \author  Chad Swenson
 * \date    September 2014
 * \brief   Serial Communication
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
#ifndef BSP_COM_H
#define BSP_COM_H

#include <stdint.h>
#include <stdbool.h>
#include "bsp_types.h"
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif


//******************************************************************************
/**
 * Initialize Serial Communication module
 *
 * \return void
 *******************************************************************************/
void bsp_com_init(void);

//******************************************************************************
/**
 * Initialize and enable the specified COM channel
 *
 * \param ch channel
 *
 * \return void
 *******************************************************************************/
void bsp_com_initCh(bsp_com_t ch);

//******************************************************************************
/**
 * Deinitialize and disable the specified COM channel
 *
 * \param ch channel
 *
 * \return void
 *******************************************************************************/
void bsp_com_deinitCh(bsp_com_t ch);

//******************************************************************************
/**
 * Write data to COM channel
 *
 * \param ch channel
 * \param data data to be written to channel
 * \param length number of byte to be written
 *
 * \return uint32_t number of bytes written
 *******************************************************************************/
uint32_t bsp_com_write(bsp_com_t ch, uint8_t const * data, uint32_t length);

//******************************************************************************
/**
 * Read data from COM channel
 *
 * \param ch channel
 * \param data data read from channel
 * \param length maximum number of bytes to read
 *
 * \return uint32_t unmber of bytes read
 *******************************************************************************/
uint32_t bsp_com_read(bsp_com_t ch, uint8_t * data, uint32_t length);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  /* BSP_COM_H */

