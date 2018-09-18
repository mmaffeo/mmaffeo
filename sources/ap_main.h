/***************************************************************
* Project Name: GWPZ20283 - Small Loader Electronics
*
* Copyright 2005 Bobcat Company as an unpublished work.
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Bobcat Company. The use, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Bobcat Company.
*
* First written on 16 November, 2005 by Spencer Mindeman
*
* Module Description:
* Main Subroutines.
***************************************************************/
#ifndef ap_main_h
#define ap_main_h

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"
 
//******************************************************************************
// DEFINES
//******************************************************************************

//******************************************************************************
// GLOBAL VARIBLES
//*************************************************************
extern uint8_t reset_ServiceClock;

//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************
void ap_main_initialize(void);
void ap_main_update(void);


#endif