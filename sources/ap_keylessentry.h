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
* First written on 13 December, 2007 by Spencer Mindeman
*
* Module Description:
* Main Subroutines.
***************************************************************/
#ifndef ap_keylessentry_h
#define ap_keylessentry_h

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "hw_io.h"		 
#include "nvm_ecuid.h"	
#include "hw_can_rx.h"

//******************************************************************************
// DEFINES
//******************************************************************************

//******************************************************************************
// GLOBAL VARIBLES
//******************************************************************************
//extern uint8_t pwd_KeylessEntry[5];

//extern hw_can_rxmsg CAN_KeypadsRX;

//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************
void ap_keylessentry_initialize (void);
//void checkKeylessStale (void);
void ap_keylessEntry_Update (void);
void RequestG55Passwords(void);
uint8_t getPhoneState(void);
#endif