//******************************************************************************
/**
 * \file    bsp_romBB.h
 * \author  Al Liebel, Chad Swenson
 * \date    Feb 2013
 * \brief   Read Only Memory Interface Header
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
#ifndef BSP_ROMBB_H
#define BSP_ROMBB_H

#include <stdint.h>
#include <stdbool.h>
#include "bsp_nvm.h"
#include "bsp_common.h"

#ifdef __cplusplus
extern "C" {
#endif

//******************************************************************************
/**
 * Initialize Kinetis Read Only Memory
 *
 * \return void
 *******************************************************************************/
void bsp_romBB_init(void);

//******************************************************************************
/**
 * Run romBB module
 *
 * \return void
 *******************************************************************************/
void bsp_romBB_run(void);

//******************************************************************************
/**
 * Determin if the BSP ROM module is busy erasing or programming ROM
 *
 * \return bool
 *******************************************************************************/
bool bsp_romBB_isBusy(void);

//******************************************************************************
/**
 * Calculate the checksum for a group of sections
 *
 * \param section_mask  mask indicating sectrions to include in calculation
 *
 * \return uint16_t checksum
 *******************************************************************************/
uint32_t bsp_romBB_checksum(uint32_t section_mask);

//******************************************************************************
/**
 * Erase ROM sections
 *
 * \note This function returns before the sections are erased.
 *
 * \param section_mask  mask indicating sectrions to erase
 *
 * \return bsp_nvm_status_t
 * \retval NVM_OK     if all sections are erasable
 * \retval NVM_FAIL   if not all sections can be reased
 *******************************************************************************/
bsp_nvm_status_t bsp_romBB_erase(uint32_t section_mask);

//******************************************************************************
/**
 * Buffer data to be written to ROM
 *
 * \note This function returns before the sections are erased.
 * \note "src_address" can't be in the same flash block as "dest_address"
 *
 * \param dest_address    flash address to write to
 * \param size            number of bytes to write
 * \param src             address of source data
 *
 * \return bsp_nvm_status_t
 * \retval NVM_OK     if all sections are erasable
 * \retval NVM_FAIL   if not all sections can be reased
 *******************************************************************************/
bsp_nvm_status_t bsp_romBB_program(uintptr_t dest_address, uint32_t size, uint8_t const * src);

//******************************************************************************
/**
 * Mark all fragmented flash words complete.  Unfilled bytes will be programmed
 *  to FFs
 *
 * \return void
 *******************************************************************************/
void bsp_romBB_programComplete(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BSP_ROMBB_H */

