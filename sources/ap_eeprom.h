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
* EEPROM Subroutines.
***************************************************************/

#ifndef ap_eeprom_h
#define ap_eeprom_h

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "stdint.h"
#include "hw_nvm.h"


//******************************************************************************
// DEFINES
//******************************************************************************
//#define EE_DEVICE_SIZE_E0           (0x30)   // 0xFC0 - Manufacturing Data
#define EE_DEVICE_SIZE_E1           (0x40)   // 0xF80 - hour meter, part number
//#define EE_DEVICE_SIZE_E2           (0x40)   // 0xF40 - unused
//#define EE_DEVICE_SIZE_E3           (0x40)   // 0xF00 - mirror end (0xF3F)
//#define EE_DEVICE_SIZE_E4           (0x40)   // 0xEC0
//#define EE_DEVICE_SIZE_E5           (0x40)   // 0xE80
//#define EE_DEVICE_SIZE_E6           (0x40)   // 0xE40
//#define EE_DEVICE_SIZE_E7           (0x40)   // 0xE00
//#define EE_DEVICE_SIZE_E8           (0x200)  // 0xC00
//#define EE_DEVICE_SIZE_E9           (0x400)  // 0x800
//#define EE_DEVICE_SIZE_E10          (0x80)   // 0x780 - mirror start - this can be as large as 0x400



#define EE_MAX_HOUR_METERS          3
#define EE_BANKS_PER_HOUR_METER     4
#define EE_HOUR_METER_BANK_SIZE     1   // number of dwords

#define EE_MAX_WRITE_ATTEMPT        3

#define MAX_BYTE                    0xFF
#define MAX_WORD                    0xFFFF
#define MAX_DWORD                   0xFFFFFFFF


#define EE_UNUSED_BYTES_EVENTS          42


#define INVALID                       0xFF

#define NUMBER_OF_EVENTS                40
#define EVENT_DIAG_QUEUE_SIZE           40

#define USER_LOG_QUEUE_SIZE              5
#define SW_UPDATE_QUEUE_SIZE            10

#define NEW_EVENT                        0
#define CONTINUING_EVENT                 1

#define NUMBER_SERVICE_CLOCK_EVENTS     20
#define PASSWORD_SIZE                   10
#define USER_NAME_SIZE                   7
#define MAX_NUMBER_SERVICE_INTERVALS     6
#define MAX_NUMBER_VITALS                6

#define NUMBER_OF_PASSWORDS             10
#define NUMBER_OF_USERS                  9

#define NUMBER_TOTAL_PASSWORDS          22
#define NUMBER_OF_EE_PASSWORDS          NUMBER_TOTAL_PASSWORDS - 1   //EE Passwords are one less because Master is in constant data
#define NUMBER_TOTAL_USERS              21

#define EEPROM_VERSION                   3

//MATLAB_STOP_READING

#define EE_MIRROR_STOP_ADDRESS          (0x0F40)
#define EE_MIRROR_START_ADDRESS         (EE_MIRROR_STOP_ADDRESS - sizeof(eeMirrorRec))


#define EE_MIRROR_VAR_POINTER(v)        ((uint8_t *) &eeMirror.v)
#define EE_MIRROR_VAR_ADDRESS(v)        (EE_MIRROR_START_ADDRESS + offsetof(eeMirrorRec, v))

#define EE_MIRROR_SECT_SIZE(f, l)       ( (EE_MIRROR_VAR_ADDRESS(l) - EE_MIRROR_VAR_ADDRESS(f)) \
                                          + sizeof(eeMirror.l) )

#define EE_MIRROR_VAR_1_POINTER         EE_MIRROR_VAR_POINTER(serviceClockResetTime)
#define EE_MIRROR_VAR_1_START           EE_MIRROR_VAR_ADDRESS(serviceClockResetTime)
#define EE_MIRROR_VAR_1_SIZE            EE_MIRROR_SECT_SIZE(serviceClockResetTime, varChecksum)

#define EE_MIRROR_VAR_2_POINTER         EE_MIRROR_VAR_POINTER(UNUSED_VAR2)
#define EE_MIRROR_VAR_2_START           EE_MIRROR_VAR_ADDRESS(UNUSED_VAR2)
#define EE_MIRROR_VAR_2_SIZE            EE_MIRROR_SECT_SIZE(UNUSED_VAR2, var2Checksum)
//******************************************************************************
// STRUCTURES
//******************************************************************************

typedef struct
{
 uint32_t value;                      // RAM hour meter value, eeprom mirrow
 uint16_t pointer;                    // pointer to current bank
 uint8_t  status;                     // disabled: if each bank in block fails
 uint8_t  failures;                   // failure counter
} hourMeterRAM;

typedef struct
{
 uint16_t time;                       // hour meter when event occured
 uint16_t duration;                   // duration of event
 uint8_t  occurances;                 // Number of Occurances
 uint8_t  checksum;                   // LEAVE AT THE BOTTOM
} eventRec;

typedef struct
{
 uint8_t  controller;
 uint8_t  function;    // functions, failure code
 uint8_t  failure;
 uint8_t  userID;
 uint32_t time;
} eventDiagRec;

#ifdef HCS12_BSP_EMU //if M4 compile this
typedef struct
{
 uint32_t  function;    // SPN
 uint8_t  controller;   // 'E'
 uint8_t  failure;      // FMI
 uint8_t  userID;       // current user
 uint8_t paddding;
 uint32_t time;         // hours
} eventDiagRecSPN;

typedef struct
{
 eventDiagRecSPN eventDiag[EVENT_DIAG_QUEUE_SIZE];    // functions, failure code
 uint8_t pointer;
 uint8_t checksum;    // LEAVE AT THE BOTTOM
} queueRecSPN;
#endif

typedef struct
{
 eventDiagRec eventDiag[EVENT_DIAG_QUEUE_SIZE];    // functions, failure code
 uint8_t pointer;
 uint8_t checksum;    // LEAVE AT THE BOTTOM
} queueRec;

typedef struct
{
  uint16_t clockReset;
  uint16_t clockLength;
  uint8_t  howReset;
  uint8_t  typeOfService;
  uint8_t  userID;
  uint8_t  reserved;
} serviceDiagRec;

typedef struct
{
  serviceDiagRec serviceDiag[NUMBER_SERVICE_CLOCK_EVENTS];
  uint8_t pointer;
  uint8_t checksum;
} queueServiceClockRec;

typedef struct
{
 uint8_t value[PASSWORD_SIZE];       /* charactors */
 uint8_t checksum;
 uint8_t unused;                     /* place holder - structures must be word aligned */
} passwordRec;

typedef struct
{
  uint8_t type;
  uint8_t state;
  uint16_t interval;
  uint32_t reset_time;
  uint8_t icon;
  uint8_t text;
} serviceIntervalRec;

typedef struct
{
  serviceIntervalRec serviceInterval[MAX_NUMBER_SERVICE_INTERVALS];
  uint8_t reserved[3];
  uint8_t checksum;
} queueServiceIntervalRec;

typedef struct
{
  uint8_t icon;
  uint8_t units;
  uint16_t warning;
  uint16_t shutdown;
} vitalRec;

typedef struct
{
  vitalRec vital[6];
  uint8_t reserved[3];
  uint8_t checksum;
} queueVitalRec;

typedef struct
{
  uint8_t user;
  uint8_t reserved;
  uint16_t hour;
} userLogRec;

typedef struct
{
  userLogRec userLog[USER_LOG_QUEUE_SIZE];
  uint8_t reserved[2];
  uint8_t pointer;
  uint8_t checksum;
} queueUserLogRec;

typedef struct
{
  uint16_t locks;
  uint16_t fuelConsumption;
  uint8_t  idleTimeUpper;
  uint16_t idleTime;
  uint8_t  jobClockUpper;
  uint16_t jobClock;
  uint8_t  user_name[USER_NAME_SIZE];
  uint8_t  driveResponse;
  uint8_t  wkgpResponse;
  uint16_t  reserved;
  uint8_t  checksum;
} userInfoRec;

typedef struct
{
  uint16_t hour;
  uint16_t reserved1;
  uint8_t reserved2;
  uint8_t ap_new_type;
  uint16_t ap_new_version;
  uint16_t cd_new_version;
} swUpdateRec;

typedef struct
{
  swUpdateRec swUpdateLog[SW_UPDATE_QUEUE_SIZE];
  uint8_t reserved[2];
  uint8_t pointer;
  uint8_t checksum;
} queueSwUpdateRec;

enum returnStates
{
  EE_SUCCESSFUL,
  EE_WRITE_FAILURE,
  EE_CHECKSUM_FAILURE,
  EE_LOST_STATE
};

enum eeModeStates
{
  EE_IDLE,
  EE_WRITE_STATUS,
  EE_HM_START,
  EE_CLEAR_ALL_BLOCKS,
  EE_CLEAR_BLOCK,
  EE_HM_UPDATE,
  EE_NO_ENABLED_HOUR_METERS,
  EE_ROLL_OVER_HOUR_METERS,
  EE_MIRROR_RESTORE,
  EE_MIRROR_UPDATE
};

enum updateStatusStates
{
  EE_US_IDLE = 2,                             //2
  EE_US_WRITE_INIT,
  EE_US_READ_COMPARE,                         //4
  EE_US_WRITE,
  EE_US_READ_VERIFY,                          //6
  EE_US_COMPLETE
};

enum hmUpdateStates
{
  EE_HM_WRITE_INIT = EE_US_COMPLETE + 1,      //8
  EE_HM_READ_COMPARE,
  EE_HM_WRITE,                                //10-A
  EE_HM_READ_VERIFY,
  EE_HM_COMPLETE                              //12-C
};

enum clearBlockStates
{
  EE_CLEAR_IDLE = EE_HM_COMPLETE+1,           //13-D
  EE_CLEAR_WRITE_INIT,                        //14-E
  EE_CLEAR_READ_COMPARE,
  EE_CLEAR_WRITE,                             //16-10
  EE_CLEAR_READ_VERIFY,
  EE_CLEAR_COMPLETE                           //18-12
};

enum mirrorStates
{
  EE_MIRROR_RESTORE_VARIABLES = EE_CLEAR_COMPLETE + 1,    //19
  EE_MIRROR_RESTORE_SECURITY,                             //20
  EE_MIRROR_RESTORE_PASSWORDS,
  EE_MIRROR_RESTORE_EVENTS,                               //22
  EE_MIRROR_RESTORE_QUEUE,
  EE_MIRROR_RESTORE_SERVICE_CLOCK_QUEUE,                  //24
  EE_MIRROR_RESTORE_USER_INFO,
  EE_MIRROR_RESTORE_SERVICE_INTERVALS,                    //26
  EE_MIRROR_RESTORE_VITALS,
  EE_MIRROR_RESTORE_USER_LOG,                             //28
  EE_MIRROR_RESTORE_SOFTWARE_UPDATE,
  EE_MIRROR_WRITE_INIT,                                   //30
  EE_MIRROR_READ_COMPARE,
  EE_MIRROR_WRITE,                                        //32
  EE_MIRROR_READ_VERIFY,                                  //33
  EE_MIRROR_COMPLETE,
  #ifndef HCS12_BSP_EMU //if HCS12 compile this
  EE_MIRROR_RESTORE_VARIABLES2 //needed this becuase of the , which is contained in the next case
  #endif
  #ifdef HCS12_BSP_EMU //if M4 compile this
  EE_MIRROR_RESTORE_VARIABLES2,
  EE_MIRROR_RESTORE_ECUQUEUE,
  EE_MIRROR_RESTORE_DCUQUEUE
  #endif
};

enum when
{
  NOW,
  LATER
};

typedef struct
{
  #ifdef HCS12_BSP_EMU //if M4 compile this
  queueRecSPN queueECU;
  #endif
  //Variables 2 start (128 bytes)
  uint8_t  UNUSED_VAR2[114];
  uint16_t ee_ThrottleCalRetracted;
  uint16_t ee_ThrottleCalExtended;
  uint8_t  UNUSED_VAR3[8];
  uint8_t  ee_ThrottleCalState;
  uint8_t  var2Checksum;

  userInfoRec userInfo[NUMBER_OF_EE_PASSWORDS];

  uint8_t doNotUse_0[2];
  queueServiceIntervalRec queueServiceIntervals;

  queueVitalRec vitals;

  queueUserLogRec queueUserLog;

  queueSwUpdateRec queueSwUpdate;

  uint8_t NOT_USED[72];

  passwordRec password[NUMBER_OF_EE_PASSWORDS];

  uint32_t machineIdleTime;

  eventRec event[NUMBER_OF_EVENTS];

  queueRec queue;

  uint8_t doNotUse_1[2];

  queueServiceClockRec queueService;

  uint8_t UNUSED_EVENTS[EE_UNUSED_BYTES_EVENTS];

  //Variables start (64 bytes total)
  uint32_t serviceClockResetTime;
  uint32_t serviceClockLength;
  uint8_t  consoleTest;
  uint8_t  serviceClockExpired;
  uint32_t jobClock;
  uint8_t  ee_AuxFlow;
  uint16_t oldAppVersion;
  uint16_t oldCDVersion;
  uint8_t  serviceClockType;
  uint8_t  ee_Version;
  uint8_t  EngData;
  uint32_t oldmachineIdleTime;
  uint32_t machineFuelConsumption;
  uint8_t  ee_AutoIdleEnabled;
  uint8_t  sparevar1;
  uint8_t  ee_autoIdleTime;
  uint32_t jobClockLHP[2];
  uint8_t  deluxe_G5;
  uint8_t  keypad;
  uint8_t  sparevar2;
  uint8_t  passwordLock;
  uint8_t  jobClockLock;
  uint8_t  serviceClockLock;
  uint8_t  sparevar3[8];
  uint8_t  ee_ControlMode;
  uint8_t  ee_EcoMode;
  uint8_t  ee_HydResponse;
  uint8_t  sparevar4[4];
  uint8_t  recoveryMode;
  uint8_t  varChecksum;

} eeMirrorRec;



//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************


extern hourMeterRAM hourCounter[EE_MAX_HOUR_METERS];

extern uint8_t eeState;                 // eeprom.c
extern uint8_t eeMode;                  // eeprom.c
extern uint8_t eeBusy;                  // eeprom.c
extern uint8_t eeTimeToUpdateMirror;    // eeprom.c

extern eeMirrorRec eeMirror;
extern uint8_t eventState[NUMBER_OF_EVENTS];

extern uint8_t cnt_TryAgain;
extern uint16_t  eeWriteActualCounter;

//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************

void UpdateEEVariables(uint8_t when);
void eeServiceEEPROM(void);
void QueueEventDiag(uint8_t controller, uint8_t function, uint8_t failure, uint8_t current_user, uint32_t time);
#ifdef HCS12_BSP_EMU //if M4 compile this
void QueueEventDiagECU(uint8_t controller, uint32_t function, uint8_t failure, uint8_t user, uint32_t time);
#endif
void UpdateEvent(uint8_t location);
void QueueServiceDiag(uint16_t reset, uint16_t length, uint8_t howReset, uint8_t serviceReq, uint8_t userID);
void RestoreDefaultPassword(uint8_t eepromNumber);
//void RestorePassword(uint8_t eepromNumber);
void QueueCurrentUser(uint8_t user, uint16_t hour);
void QueueSoftwareUpdate(uint8_t ap_new_type, uint16_t app_new_version, uint16_t cd_new_version, uint16_t hour);
uint32_t GetUserJob(uint8_t user);
void SetUserJob(uint8_t user, uint32_t time);
uint32_t GetUserIdle(uint8_t user);
void SetUserIdle(uint8_t user, uint32_t time);

#endif