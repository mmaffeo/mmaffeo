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
* First written on 23 November, 2005 by Spencer Mindeman
*
* Module Description:
* General subroutines.
***************************************************************/

#ifndef ap_subs_h
#define ap_subs_h

//******************************************************************************
// INCLUDES
//******************************************************************************

#include "stdint.h"


//******************************************************************************
// DEFINES
//******************************************************************************
#define MAX_HOUR_METER_VALUE        (10000ul*HOUR_METER_TO_HOUR_FCT)  //10,000 Hours
#define RELOAD_6_MIN                72
#define HOUR_METER_FCT              RELOAD_6_MIN
#define HOUR_METER_TO_HOUR_FCT      720
#define HOUR_METER_TO_MINUTE_FCT    12

#define MAX_STRING_LENGTH			      10
#define MAX_STRING_BUFF_LENGTH		  MAX_STRING_LENGTH+1 /* for NULL termination */
#define MAX_ACTIVE_CODES            7

#define SERVICE_TIME_DISPLAY       10 

#define MAX_JOB_CLOCK               60000
//******************************************************************************
// STRUCTURES
//******************************************************************************


//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************

extern uint8_t  hourMeterUpdateTimer;
extern uint8_t  jobClockUpdateTimer;
extern uint8_t  jobClockLHPUpdateTimer[2];
extern uint8_t  idleClockUpdateTimer;
extern uint8_t  sendFirstJobClockCmd;

extern uint8_t  currentHourMeter;		  
extern uint32_t actualHourMeterCopy;
//extern uint32_t actualHourMeter;
extern uint8_t  flag_HourOverflow;

extern uint32_t eeUpdate;

extern uint16_t gwServiceTimer;

extern uint8_t status_SrvcClockDisplay;


//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************
void left_pad_str(uint8_t *str, int len, char pad, const uint8_t max_length);
uint8_t number_to_str(uint32_t value, uint8_t * buffer, uint8_t buffer_length);
void UpdateHourMeter(void);
void UpdateUserJobClock(void);
void UpdateLHPJobClocks(void);
void UpdateIdleTime(void);
void UpdateLCDHourMeter(void);
void UpdateLCDJobClock(uint8_t clock);
void UpdateLCDGlowPlugs(void);
void UpdateLCDEngineRPM(void);
void UpdateLCDBatteryVoltage(void);
void UpdateLCDEOP(void);
void UpdateLCDECT(void);
void UpdateLCDHOT(void);
void UpdateLCDServiceClock(void);
void UpdateLCDServiceAlarm(void);
void SetServiceClock(void);
void UpdateServiceClock(void);
void UpdateLCDVersion(void);
void UpdateLCD_FlashCold(void); 
//void UpdateLCDRFID(void);
//int8_t str_len(const uint8_t *s_ptr, const uint8_t max_length);



#endif