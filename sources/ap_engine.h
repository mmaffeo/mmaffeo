/***************************************************************
*
* Copyright 2016 Bobcat Company as an unpublished work.
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Bobcat Company. The use, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Bobcat Company.
*
* First written on 18 October, 2016 by Al Liebel
*
* Module Description:
* Header for ECU Interface.
***************************************************************/

#ifndef ap_engine_h
#define ap_engine_h

#include "hw_can.h"
#include "J1939_TP_tx.h"
#include "J1939_TP_rx.h"

//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************
void ap_ECU_update(void);
void ap_ECU_initialize(void);

#endif