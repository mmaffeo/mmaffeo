//******************************************************************************
/**
 * \file    stf4_fifo.h
 * \author  Chad Swenson
 * \date    Feb 2014
 * \brief   Generic FIFO
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
#ifndef BSP_FIFO_H
#define BSP_FIFO_H

#include <stdint.h>
#include <stdbool.h>

/// FIFO Object
typedef struct bsp_fifo_s
{
  uint8_t *data;        ///< Memory to be used by FIFO
  uint32_t entrySize;   ///< Size of FIFO entry
  uint32_t length;      ///< Number of entries that the FIFO can hold
  uint32_t maxUsed;     ///< The maximum number of entries in the FIFO since last flush
  uint32_t head;        ///< The index where the next entry will be gotten from
  uint32_t tail;        ///< The index where the next entry will be put
} bsp_fifo_t;

//******************************************************************************
/**
 * Initialize the FIFO Object
 *
 * \param fifo
 * \param data
 * \param dataSize
 * \param entrySize
 *
 * \return void
 *******************************************************************************/
void bsp_fifo_init(bsp_fifo_t *fifo, void *data, uint32_t dataSize, uint32_t entrySize);

//******************************************************************************
/**
 * Flush the FIFO and reset the Max Used counter
 *
 * \note Only call this from the interrupt or while the interrupt is disabled
 *
 * \param fifo
 *
 * \return void
 *******************************************************************************/
void bsp_fifo_flush(bsp_fifo_t *fifo);

//******************************************************************************
/**
 * Check if the FIFO is full
 *
 * \note fifo_notFull, bsp_fifo_available and fifo_put should only be called from
 *  the same thread for each fifo object
 *
 * \param fifo
 *
 * \return bool
 *******************************************************************************/
bool bsp_fifo_notFull(bsp_fifo_t const * fifo);

//******************************************************************************
/**
 * Calculate the number of free entries in the FIFO
 *
 * \note fifo_notFull, bsp_fifo_available and fifo_put should only be called from
 *  the same thread for each fifo object
 *
 * \param fifo
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_fifo_available(bsp_fifo_t const * fifo);

//******************************************************************************
/**
 * Attempt to put an entry into the FIFO
 *
 * \note fifo_notFull, bsp_fifo_available and fifo_put should only be called from
 *  the same thread for each fifo object
 *
 * \param fifo
 * \param entry
 *
 * \return bool
 *******************************************************************************/
bool bsp_fifo_put(bsp_fifo_t *fifo, void const * entry);

//******************************************************************************
/**
 * Check if the FIFO is empty
 *
 * \note fifo_notEmpty, bsp_fifo_pending and fifo_get should only be called from
 * the same thread for each fifo object
 *
 * \param fifo
 *
 * \return bool
 *******************************************************************************/
bool bsp_fifo_notEmpty(bsp_fifo_t const * fifo);

//******************************************************************************
/**
 * Calculate the number of used entries in the FIFO
 *
 * \note fifo_notEmpty, bsp_fifo_pending and fifo_get should only be called from
 * the same thread for each fifo object
 *
 * \param fifo
 *
 * \return uint32_t
 *******************************************************************************/
uint32_t bsp_fifo_pending(bsp_fifo_t const * fifo);

//******************************************************************************
/**
 * Attempt to get an entry out of the FIFO
 *
 * \note fifo_notEmpty, bsp_fifo_pending and fifo_get should only be called from
 * the same thread for each fifo object
 *
 * \param fifo
 * \param entry
 *
 * \return bool
 *******************************************************************************/
bool bsp_fifo_get(bsp_fifo_t *fifo, void * entry);


#endif /* BSP_FIFO_H */

