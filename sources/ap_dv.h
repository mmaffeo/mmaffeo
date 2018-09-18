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
* First written on 26 October, 2005 by Spencer Mindeman
*
* Module Description:
* DV table and routines for doing various diagnostic info.
***************************************************************/

#ifndef ap_dv_h
#define ap_dv_h

//******************************************************************************
// INCLUDES
//******************************************************************************


//******************************************************************************
// DEFINES
//******************************************************************************

#define DV_AUTHORIZATION  0xFA50

#define DV_TEST_DONE      0
#define DV_TEST_NOT_DONE  1
														 

// Test Commands
#define DV_TEST_NO_COMMAND                0
#define DV_TEST_CLEAR_DIAGNOSTIC_EVENTS   11
#define DV_SET_HOUR_METER                 29
#define DV_DOWNGRADE_DDP                  42
#define DV_TEST_CLEAR_SERVICE_CODES       43  //0x2B
#define DV_CLEAR_SERVICE_CLOCK_EVENTS     44  //0x2C
#define DV_ENABLE_SERVICE_CLOCK           46  //0x2E
#define DV_SET_SERVICE_CLOCK              47  //0x2F
#define DV_PANEL_TEST                     48  //0x30  
#define DV_RESTORE_VITALS                 49  //0x31
#define DV_RESET_SEATBAR_TEST             50  //0x32
#define DV_TOGGLE_ENG_DATA                51  //0x33
#define DV_DISABLE_SERVICE_CLOCK          53  //0x35
#ifdef HCS12_BSP_EMU //if M4 compile this
  #define DV_TEST_CLEAR_ECU_CODES           54  //0x36
#endif


//******************************************************************************
// GLOBAL VARIBLES
//******************************************************************************

extern bool inDVCode;

extern uint16_t newHour1;
extern uint16_t newHour2;

extern uint16_t dvPassword;
extern uint16_t dvCommand;

extern uint16_t serviceType;

extern bool dvPanelOn;

//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************

void initialize_ap_dv(void);
void initialize_ap_dv2(void);
void initialize_ap_ActiveCodes(void);
void DVTest(void);
void InitDVTest(void);

#endif

