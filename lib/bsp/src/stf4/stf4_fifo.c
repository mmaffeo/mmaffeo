//******************************************************************************
/**
 * \file    stf4_fifo.c
 * \author  Chad Swenson
 * \date    Feb 2014
 * \brief   Generic FIFO
 *
 * Copyright 2013, 2015 Bobcat Company as an unpublished work.
 * All Rights Reserved.
 *
 * The information contained herein is confidential
 * property of Bobcat Company. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Bobcat Company.
 *
 *******************************************************************************/
#include "stf4_fifo.h"
#include <stdbool.h>
#include <stdint.h>


//******************************************************************************
// Static Function Prototypes
//******************************************************************************


//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void bsp_fifo_init(bsp_fifo_t *fifo, void *data, uint32_t dataSize, uint32_t entrySize)
{
  fifo->data = (uint8_t *)data;
  fifo->entrySize = entrySize;
  fifo->length = dataSize / entrySize;

  bsp_fifo_flush(fifo);
}

//******************************************************************************
void bsp_fifo_flush(bsp_fifo_t *fifo)
{
  fifo->head = 0;
  fifo->tail = 0;
  fifo->maxUsed = 0;
}

//******************************************************************************
bool bsp_fifo_notFull(bsp_fifo_t const * fifo)
{
  uint32_t pending = fifo->tail - fifo->head;
  uint32_t available = fifo->length - pending;

  return (available != 0);
}

//******************************************************************************
uint32_t bsp_fifo_available(bsp_fifo_t const * fifo)
{
  uint32_t pending = fifo->tail - fifo->head;

  return (fifo->length - pending);
}

//******************************************************************************
bool bsp_fifo_put(bsp_fifo_t *fifo, void const * entry)
{
  uint32_t pending = (fifo->tail - fifo->head) + 1;
  bool success = (pending <= fifo->length);

  if (success)
  {
    uint32_t entrySize = fifo->entrySize;
    uint32_t index = (fifo->tail % fifo->length) * entrySize;
    uint8_t const * from = (uint8_t const *)entry;
    uint8_t * to = &fifo->data[index];

    while (entrySize--)
    {
      *to++ = *from++;
    }

    fifo->tail++;

    if (pending > fifo->maxUsed)
    {
      fifo->maxUsed = pending;
    }
  }

  return success;
}

//******************************************************************************
bool bsp_fifo_notEmpty(bsp_fifo_t const * fifo)
{
  // The head and tail are only equal when the FIFO is empty
  return (fifo->head != fifo->tail);
}

//******************************************************************************
uint32_t bsp_fifo_pending(bsp_fifo_t const * fifo)
{
  return (fifo->tail - fifo->head);
}

//******************************************************************************
bool bsp_fifo_get(bsp_fifo_t *fifo, void * entry)
{
  bool success = (fifo->head != fifo->tail); // True if buffer not already empty

  if (success)
  {
    uint32_t entrySize = fifo->entrySize;
    uint32_t index = (fifo->head % fifo->length) * entrySize;
    uint8_t const * from = &fifo->data[index];
    uint8_t * to = (uint8_t *)entry;

    while (entrySize--)
    {
      *to++ = *from++;
    }

    fifo->head++;
  }

  return success;
}

//******************************************************************************
// Static Function Definitions
//******************************************************************************


