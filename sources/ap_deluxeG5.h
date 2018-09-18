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
* First written on 05 November, 2008 by Spencer Mindeman
*
* Module Description:
* CAN routines to send out routines specified in requirements.
***************************************************************/

#ifndef ap_deluxeG5_h
#define ap_deluxeG5_h

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "hw_io.h"
#include "nvm_ecuid.h"
#include "hw_can_rx.h"
#include "ap_main.h"
#include "J1939_TP_tx.h"
#include "J1939_TP_rx.h"
#include "J1939_msg.h"

//******************************************************************************
// DEFINES
//******************************************************************************

#define JOB_CLOCK_NOTHING      0x00
#define AUTO_IDLE_UPDATE       0x01
#define JOB_CLOCK_ENABLE       0x02
#define JOB_CLOCK_RESET        0x04
#define USER_JOB_CLOCK_ENABLE  0x08
#define USER_JOB_CLOCK_RESET   0x10

typedef struct
{
  uint8_t icon;
  uint8_t units;
} vitalItem;



//Vital Message
typedef enum
{
  VITAL_ICON_RPM=10,
  VITAL_ICON_BATTERY=20,
  VITAL_ICON_ECT=30,
  VITAL_ICON_HOT=40,
  VITAL_ICON_EOP=50,
  VITAL_ICON_FUEL_USAGE=60,
  VITAL_ICON_EOT=70
} vital_icons;

typedef enum
{
  ICON_DEFAULT,
  ICON_YELLOW,
  ICON_RED
} icon_color;

typedef enum
{
  SCALE_ZERO,
  SCALE_ONE,
  SCALE_TWO,
} scale_type;




typedef enum
{
  NO_CHANGE,
  ACCEPT_CHANGE,
  NEW_PASSWORD,
  PASSWORD_ERROR = 0xFE
} password_states;

typedef enum
{
  DLX_STARTUP_IDLE,
  DLX_STARTUP_SEND_PASSWORDS,
  DLX_STARTUP_SEND_USER_DATA,
  DLX_STARTUP_SEND_JOB_CLOCKS,
  DLX_STARTUP_SEND_USER_NAME,
  DLX_STARTUP_SEND_DEALER_NAME,
  DLX_STARTUP_SEND_DEALER_NUMBER,
  DLX_STARTUP_SEND_SERVICE_INTERVALS,
  DLX_STARTUP_DONE
} deluxe_statup_states;

#define G5_PWD_LOCK_BIT          0x01
#define G5_JOB_CLOCK_LOCK_BIT    0x02
#define G5_MACHINE_LOCK_BIT      0x04
#define G5_DOWNGRADE_TOGGLE      0x10

#define G5_PASSWORD_ACCEPTED            0x01
#define G5_NEWLY_BOOTED_BIT             0x04
#define G5_GET_NEXT_WARNING_BIT         0x08
#define G5_GET_WARNING_HISTORY_BIT      0x08
#define G5_DOWNGRADE_TOGGLE             0x10

#define G5_IN_WARNING_PAGE              0x01
#define G5_IN_PASSWORD_SCREEN           0x02
#define G5_IN_PASSWORD_FAIL             0x04
#define G5_IN_USER_LOG_SCREEN           0x08

#define HOT_SHUTDOWN_BIT        0x01
#define HCP_SHUTDOWN_BIT        0x02
#define ECT_SHUTDOWN_BIT        0x04
#define RPM_SHUTDOWN_BIT        0x08
#define EOP_SHUTDOWN_BIT        0x10
#define DRIVE_SHUTDOWN_BIT      0x20
#define TORQUE_SHUTDOWN_BIT     0x40
#define ES_DERATE_SHUTDOWN_BIT  0x80
#define PARKED_REGEN_SHUTDOWN   0x03
#define FUEL_TEMP_SHUTDOWN      0x05

#define PASSWORD_LOCK_BIT     0x10
#define TWO_SPEED_LOCK_BIT    0x20
#define HIGH_FLOW_LOCK_BIT    0x40
#define JOB_CLOCK_LOCK_BIT    0x80

#define PASSWORD_LOCK_TOGGLE  0x10
#define TWO_SPEED_LOCK_TOGGLE 0x20
#define HIGH_FLOW_LOCK_TOGGLE 0x40
#define JOB_CLOCK_LOCK_TOGGLE 0x80

#define ACTIVE_WARNING_BIT    0x01

#define IN_WARNING_SCREEN         0x01
#define IN_PASSWORD_SCREEN        0x02
#define IN_PASSWORD_FAIL_SCREEN   0x04
#define IN_HOURS_SCREEN           0x10

#define NEW_PASSWORD_BIT          0x02
#define DELUXE_NEW_BOOT_BIT       0x04
#define DELUXE_NEXT_ERROR_BIT     0x08
#define DELUXE_DOWNGRADE_BIT      0x10
#define CLEAR_JOB_CLOCK_BIT       0x40

#define SERVICE_CLOCK_ENABLE_BIT 0x01
#define SERVICE_CLOCK_RESET_BIT  0x02
#define SERVICE_CLOCK_ALARM_BIT  0x04
#define SERVICE_CLOCK_LOCK_BIT   0x40

// Deluxe Panel Message IDs
#define CMD_NULL                    0x00
#define CMD_RESET                   0x01
#define CMD_VERSION                 0x03
#define CMD_READ_BYTE               0x04
#define CMD_WRITE_BYTE              0x05
#define CMD_READ_BYTE_I             0x06
#define CMD_WRITE_BYTE_I            0x07
#define CMD_READ_WORD               0x08
#define CMD_WRITE_WORD              0x09
#define CMD_READ_WORD_I             0x0A
#define CMD_WRITE_WORD_I            0x0B
#define CMD_PROGRAM                 0x0E

#define CMD_VIRT_GAUGES           0x10

#define CMD_BOB_STATUS            0x12
#define CMD_WARNING               0x13
#define CMD_DDP_STATUS            0x14
#define CMD_JOB_CLOCK             0x15
#define CMD_WARNING_ENHANCED      0x16
#define CMD_PW_NEW                0x17
#define CMD_VITALS                0x18
#define CMD_REQ_PGN               0x1D
#define CMD_DISP_ASCII            0x1E
#define CMD_BUCKET_ATTITUDE       0x1F

#define CMD_LED_ICON_DATA         0x26

#define CMD_PW_CURRENT0           0x40
#define CMD_PW_CURRENT1           0x41
#define CMD_PW_CURRENT2           0x42
#define CMD_PW_CURRENT3           0x43
#define CMD_PW_CURRENT4           0x44
#define CMD_PW_CURRENT5           0x45
#define CMD_PW_CURRENT6           0x46
#define CMD_PW_CURRENT7           0x47
#define CMD_PW_CURRENT8           0x48
#define CMD_PW_CURRENT9           0x49
#define CMD_PW_EXPANSION          0x4A
#define CMD_PW_USER_ID            0x4B
#define CMD_USER_JOB_CLOCK        0x4C
#define CMD_MAINTENANCE_CLOCK     0x4D
#define CMD_CLOCK_STATUS          0x4E
#define CMD_ICON_EXTENTION        0x4F
#define CMD_DEALER_PHONE          0x50
#define CMD_DEALER_NAME           0x51

#define ACK_NAK_MASK              0x20
#define SERIAL_BUFFER_SIZE        32
#define SERIAL_BUFFER_MASK        SERIAL_BUFFER_SIZE-1
#define MAX_TRANSMISSION_TRIES    3       // maximum number of tries to trans
#define RECEIVE_TIMEOUT           25     //
#define COMMAND_QUEUE_SIZE        64
#define COMMAND_QUEUE_MASK        COMMAND_QUEUE_SIZE-1 // used to mask off for head&tail inc
#define MAX_COMMANDS              0x58

#define DDP_WAKEUP_TIME           15

#define DELUXE_FIRST_START_TIME   5

#define DELUXE_DEBOUNCE_FIRST_TIME    50

#define DDP_HEARTBEAT_RESET           10

#define ICON_AIR_FILTER               0x04
#define ICON_HYD_FILTER               0x01



//******************************************************************************
// GLOBAL VARIBLES
//******************************************************************************
extern hw_can_txmsg BobStatusTX;
extern hw_can_txmsg JobClockStatusTX;

typedef struct
{
  FLAG startActive              : 1;
  FLAG newPassWordReadyEE       : 1;
  FLAG ddpNewlyBooted           : 1;
  FLAG getNextWarning           : 1;
  FLAG downgradeFromDDP         : 1;
  FLAG requestPGNReady          : 1;
  FLAG clearJobClock            : 1;
  FLAG unusedBit                : 1;

  FLAG inWarningPage              : 1;
  FLAG inInitPasswordScreen       : 1;
  FLAG inInitPasswordFailedScreen : 1;
  FLAG inBucketPositionScreen     : 1;
  FLAG inHoursScreen              : 1;
  FLAG machineLock                : 1;
  FLAG inUserLogScreen            : 1;
  FLAG unusedByte                 : 1;

  FLAG key4                     : 1;
  FLAG key3                     : 1;
  FLAG key2                     : 1;
  FLAG key1                     : 1;
  FLAG key8                     : 1;
  FLAG key7                     : 1;
  FLAG key6                     : 1;
  FLAG key5                     : 1;

  FLAG right                    : 1;
  FLAG key0                     : 1;
  FLAG key9                     : 1;
  FLAG left                     : 1;
  FLAG passWordLockToggle       : 1;
  FLAG unused3                  : 1;
  FLAG unused2                  : 1;
  FLAG jobClockLockToggle       : 1;

  FLAG unused                   : 8;

  FLAG softkey4                 : 1;
  FLAG softkey3                 : 1;
  FLAG softkey2                 : 1;
  FLAG softkey1                 : 1;
  FLAG enter                    : 1;
  FLAG stop                     : 1;
  FLAG auxrel                   : 1;
  FLAG start                    : 1;

} DDPSwitchStruct;

typedef union
{
 DDPSwitchStruct data;
 uint8_t                switchByte[6];
} DDPSwitchUnion;

//******************************************************************************
// GLOBAL VARIBLES
//******************************************************************************

extern bool flag_PasswordSent;
extern uint8_t dlxMode;
extern bool flag_SendWarningHistory;
extern hw_can_rxmsg rx_DeluxeStatus;
extern uint8_t msg_Counter;
//extern bool enable_ECUDM1;

extern DDPSwitchUnion ddpSwitchStatus;

extern J1939_msg_t Deluxe_TP_msg;
extern J1939_TP_tx Deluxe_TP_tx;
extern J1939_TP_rx Deluxe_TP_rx;

//extern uint8_t msgData[200];
//extern uint8_t ecu_SOFT[ECU_SOFT_LENGTH];
//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************
void ap_DeluxeG5_initialize (void);
void send_DeluxeG5_StartUpData(void);
void VerifyNewPasswordG5(void);
void Deluxe_Data_Update(void);
void SendDeluxeWarning(void);
void SendWarningHistory(void);
void Deluxe_TP_update(void);
void ap_DeluxeG5_VIN (uint8_t DA);

#endif