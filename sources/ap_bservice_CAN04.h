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
* The module broadcasts all non-"normal" error codes from the "ecode_list"
* in a "CAN04" message on the primary CAN bus.  It also handles all error code routines.
***************************************************************/

// example usage...

/*
    // an array of error codes similar to the following exists somewhere in the application 
    uint16_t ecodes[4] = {0x0108, 0x0208, 0x0302, 0x0408};
    
    // somewhere in an initialization section
    ap_bservice_CAN04_initialize(ecodes, sizeof(ecodes)/sizeof(uint16_t) );
    
    // on a periodic basis (every 10mS)
    ap_bservice_CAN04_update();
    
    
    
    // The situation described above will result result a a CAN04 message being broadcast 
    // at a 1 second rate with a "function:failure" value of "3:2"

*/

#ifndef _ap_bservice_CAN04_h
#define _ap_bservice_CAN04_h

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "hw_io.h"

//******************************************************************************
// DEFINES
//******************************************************************************
#define MAX_NUMBER_OF_FAILURES    10
#define ERROR_CODE_DISPLAY_TIME   50
#define ENGINE_ERROR_CODE_DISPLAY_TIME    100

#define MAX_NUMBER_OF_SPN         10


//******************************************************************************
// STRUCTURES
//******************************************************************************
typedef struct
{
  uint8_t  device;
  uint16_t  spn;     
  uint8_t  function;
  uint8_t  failure;
  uint8_t  beep;
  uint8_t  type;
  uint16_t timer;
  uint8_t pcode[5];
} FailureCodeStruct;

typedef struct
{
  uint32_t  SPN;
  uint8_t   FMI;
  uint8_t   OC;
  uint8_t   CM;
} EngineCodeStruct;    

typedef struct{
  uint8_t function;
  uint8_t failure;
  uint8_t severity;  
} CodeSeverityStruct;  

												
//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************
extern FailureCodeStruct FailureQueue[MAX_NUMBER_OF_FAILURES];
extern FailureCodeStruct failureCode;

extern EngineCodeStruct EngineFailureQueue[MAX_NUMBER_OF_SPN];

extern uint8_t state_Buzzer;
extern uint8_t current_user;

extern uint16_t start_timeLCD;


//extern uint16_t lamp_Engine;

//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************
void ap_bservice_CAN04_initialize(uint16_t *ecode_list, uint8_t ecode_list_size);
void ap_bservice_CAN04_update(void);
void updateErrorList(void);
void UpdateLCDErrorCodes(void);
void ErrorQueueDisplayList(uint8_t Device, uint8_t Function, uint8_t Failure, uint16_t SPN, uint8_t type);
void ErrorQueueTimerUpdate(void);

#endif

