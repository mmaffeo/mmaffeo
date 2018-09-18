//******************************************************************************
/**
 * \file    nvm_ecuid.cpp
 * \author  Chad Swenson
 * \date    November 2014
 * \brief   Emulation of nvm_ecuid on BSP
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
#include "nvm_ecuid.h"
#include "bsp_ecuid.h"

nvm_ecuid_t nvm_ecuid;

void nvm_ecuid_t::initialize(void)
{
  j1939_source_address = bsp_ecuid->j1939_source_address;
  bobcat_module_id     = bsp_ecuid->bobcat_module_id;
  ap_sw_code_smask     = bsp_ecuid->ap_sw_code_smask;
  ap_sw_const_smask    = bsp_ecuid->ap_sw_const_smask;
}


