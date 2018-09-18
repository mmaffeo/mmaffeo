//******************************************************************************
/**
 * \file    bsp_rom.h
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
#ifndef BSP_ROM_H
#define BSP_ROM_H

#include <stdint.h>
#include <stdbool.h>
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
void bsp_rom_init(void);

//******************************************************************************
/**
 * Get the start address of the first sectionin a group of sections
 *
 * \param section_mask  mask indicating sections
 *
 * \return uintptr_t first section start address
 *******************************************************************************/
uintptr_t bsp_rom_getStartAddr(uint32_t section_mask);

//******************************************************************************
/**
* Check if the address points to ROM
*
* \param address
* \param length
*
* \return bool
*******************************************************************************/
bool bsp_rom_isROM(uint32_t address, uint32_t length);

//******************************************************************************
/**
* Read ROM direct
*
* \param address
* \param length
* \param data
*
* \return bool
*******************************************************************************/
bool bsp_rom_readDirectROM(uint32_t address, uint32_t length, uint8_t *data);

//******************************************************************************
/**
* Read RAM direct
*
* \param address
* \param length
* \param data
*
* \return bool
*******************************************************************************/
bool bsp_rom_readDirectRAM(uint32_t address, uint32_t length, uint8_t *data);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BSP_ROM_H */

