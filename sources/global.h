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
* First written on 14 December, 2006 by Spencer Mindeman
*
* Module Description:
* Main Subroutines.
***************************************************************/
#ifndef global_h
#define global_h

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "stdbool.h"

//******************************************************************************
// DEFINES
//******************************************************************************
#define ECU_SOFT_LENGTH 30

//******************************************************************************
// GLOBAL VARIBLES
//******************************************************************************
extern uint8_t powerUpTimer;
extern uint8_t state_DeluxeRun;
extern uint8_t newlyBootedDDP;
extern uint8_t pwScreenShown;

//extern uint16_t sw_Version;

extern uint8_t ddpServiceScreenFlag;
extern uint8_t flag_SendDeluxeWarning;

extern uint8_t downgradedFromDDP;
extern uint8_t newPasswordNumber;
extern uint8_t newJobClockNumber;
extern uint8_t newUserNameNumber;
extern uint8_t newPasswordVerification;
extern uint8_t newJobClockVerification;
extern uint8_t newUserNameVerification;
extern uint8_t ddpPasswordScreenChanged;
extern uint8_t obtainedCurrentUser;
extern uint8_t flag_DeluxeProg;

extern uint8_t flag_ActiveWarning;
extern uint8_t flag_StdActiveWarn;

extern uint32_t can_FuelConsumption;
extern uint32_t start_FuelConsumption;
extern uint16_t current_FuelConsumption;

extern uint8_t flag_RxRPMMax;
extern uint8_t flag_RxRPMMin;
extern uint8_t flag_RxECUHours;
extern uint8_t flag_RxDPFHours;


extern uint8_t ecu_BarPressure;
extern uint16_t ecu_AirInletTemp;
extern uint32_t ecu_Hours;

extern uint16_t pressure_TorqueLimiter;

extern bool enable_ECUDM1;
extern uint8_t ecu_SOFT[ECU_SOFT_LENGTH];

extern uint8_t user_KeylessEntry;


//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************

#endif
