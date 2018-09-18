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
* CAN routines to send out routines specified in requirements.
***************************************************************/

#ifndef ap_can_h
#define ap_can_h

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "hw_io.h"
#include "nvm_ecuid.h"
#include "hw_can_rx.h"


//******************************************************************************
// DEFINES
//******************************************************************************
#define PRIORITY_0 0
#define PRIORITY_1 1
#define PRIORITY_2 2
#define PRIORITY_3 3
#define PRIORITY_4 4
#define PRIORITY_5 5
#define PRIORITY_6 6
#define PRIORITY_7 7

#define PROPRIETARY_A       0xEF
#define PROPRIETARY_B       0xFF
#define GLOBAL_ADDR         0xFF
#define UNDEFINED           0xFF

#define TYPE_1              1
#define TYPE_2              2


// DEFINITIONS FOR J1939 MESSAGES
#define ENGINE_HOURS_PF     254  //0xFE
#define ENGINE_HOURS_PS     229  //0xE5
#define BATTERY_VOLTAGE_PF  254  //0xFE
#define BATTERY_VOLTAGE_PS  247  //0xF7
#define ACKNOWLEDGE_PF      232
#define REQUEST_PF          234
#define ADDRESS_CLAIM_PF   0xEE
#define TFAC_PF                     0xF0
#define TFAC_PS                     0x1A

//Proprietary B message PS
#define DELUXE_MAIN_STATUS_PS       0x26
#define G55_DELUXE_STATUS_PS        0x27
#define G55_AUTHENTICATION_PS       0x28
#define MACHINE_CONFIG_PS           0x29
#define PANEL_TELL_TALES_PS         0x2D
#define PANEL_BUTTON_STATE_PS       0x2E
#define PANEL_GAUGE_POSITION_PS     0x2F

#define PANEL_LCD_DATA_DISPLAY_PS   0x30
#define PANEL_LCD_DATA_DISPLAY2_PS  0x31
#define PANEL_EXTERNAL_IO_PS        0x32
#define PANEL_ANALOG_IO_PS          0x33
#define AUX_HYD_CONTROL_PS          0x35
#define BICS_CONTROL_PS             0x38
#define KEYPAD_STATUS_PS            0x3A
#define DELUXE_STATUS_PS            0x3B
#define PASSWORD_DATA_PS            0x3C
#define DEALER_DATA_PS              0x3D
#define JOB_CLOCK_PS                0x3E
#define MAIN_STATUS_PS              0x3F

#define USER_INFO_PS                0x4F
#define JOG_BUTTON_STATE_PS         0x50
#define SERVICE_DATA_PS             0x50 // Note duplicate
#define VITAL_DATA_PS               0x51
#define USER_NAME_PS                0x52
#define DELUXE_WARNING_PS           0x54

#define DIG_DEPTH_STATUS_PS         0x61
#define BJM2_PS                     0x69

#define OPER_SETTINGS_PS            0x74
#define PRIMARY_CONTROLS_PS         0x76
#define G55_PASSWORD_DATA_PS        0x77
#define AUX_CONTROL_MODE_PS         0x79
#define HYD_CONTROL_SETTINGS_PS     0x7A

//ECU J1939 PGNs
#define TSC1_PF                     0
#define TSC1_PS                     0
#define EEC2_PF                     0xF0 //PGN 61443
#define EEC2_PS                     0x03
#define EEC1_PF                     0xF0 //PGN 61444
#define EEC1_PS                     0x04
#define EEC4_PF                     0xFE
#define EEC4_PS                     0xBE
#define EC1_PF                      0xFE
#define EC1_PS                      0xE3
#define ET1_PF                      0xFE //PGN 65262
#define ET1_PS                      0xEE
#define EFL_P1_PF                   0xFE //PGN 65263
#define EFL_P1_PS                   0xEF
#define DD_PF                       0xFE //PGN 65276
#define DD_PS                       0xFC
#define CCVS_PF                     0xFE
#define CCVS_PS                     0xF1
#define WFI_PF                      0xFE //PGN 65279
#define WFI_PS                      0xFF
#define LFE_PF                      0xFE //PGN 65266
#define LFE_PS                      0xF2
#define LFC_PF                      0xFE //PGN 65257
#define LFC_PS                      0xE9
#define AT1S_PF                     0xFD
#define AT1S_PS                     0x7B
#define EOI_PF                      0xFD //PGN 64914
#define EOI_PS                      0x92
#define SOFT_PF                     0xFE //PGN 65242
#define SOFT_PS                     0xDA
#define SHUTDOWN_PF                 0xFE //PGN 65252
#define SHUTDOWN_PS                 0xE4
#define TD_PF                       0xFE
#define TD_PS                       0xE6
#define AMB_PF                      0xFE
#define AMB_PS                      0xF5
#define ACTIVE_CODES_PF             0xFE
#define ACTIVE_CODES_PS             0xCA
#define PREV_ACTIVE_CODES_PF        0xFE
#define PREV_ACTIVE_CODES_PS        0xCB
#define VIN_PF                      0xFE
#define VIN_PS                      0xEC
#define SERV_PF                     0xFE
#define SERV_PS                     0xC0
#define AAI_PF                      0xFE
#define AAI_PS                      0x8C

//ECU Proprietary PGNs
#define DPM2_PS                     0x03  //PGN 65283
#define SMVCU_PS                    0xA4


#define SA_ECU                      0x00
#define SA_CAN_ACTUATOR             0x12
#define SA_LEFT_PANEL               0x17
#define SA_GATEWAY                  0xB0
#define SA_SERVICE_TOOL             0xB3
#define SA_ATTACHMENT               0xB4
#define SA_SECONDARY                0x48
#define SA_KEYLESS_START            0x1D
#define SA_KEYLESS_ENTRY            0x1F
#define SA_DELUXE_PANEL             0x54
#define SA_DISPLAY_CONTROLLER       0x41
#define SA_THROTTLE                 0xFC
#define SA_LEFT_JOYSTICK            0xEB
#define SA_RIGHT_JOYSTICK           0xEC
#define SA_PROG_TOOL                0xFA
#define SA_JOG_SHUTTLE              0xF0


#define CAN_ST_TIMEOUT              850
#define CAN_ACD_TIMEOUT             300

// Mask Values
#define HYDRAULIC_LOCK_MASK         0x01


#define VOLTAGE_RESOLUTION 13

#define PSITOKPA     0x06E5  //1765d
#define MAXENGINEPSI    145

#define HOUR_METER_RESOLUTION   36    // our timer is 5 second resolution

#define ACK 0
#define NAK 1

#define VIN_MSG_LENGTH 20

enum CAN_MESSAGES
{
  CAN01 = 1,
  CAN02,
  CAN03,
  CAN04,
  CAN05,
  CAN06,
  CAN07,
  CAN08,
  CAN09,
  CAN20 = 0x20,
  CAN21,
  CAN22,
};

//MATLAB_STOP_READING


typedef struct
{
  uint8_t data[8];
} ca_name_t;

const uint8_t FahrenheitToCelsius[451] =
{
 // this is an offset table location 0 returns 0 but is -40 degress C
 0,1,1,2,2,3,3,4,4,5,6,6,7,7,8,8,9,9,10,11,                                        // -40 to -21
 11,12,12,13,13,14,14,15,16,16,17,17,18,18,19,19,20,21,21,22,                      // -20 to - 1
 22,23,23,24,24,25,26,26,27,27,28,28,29,29,30,31,31,32,32,33,                      //  0  to  19
 33,34,34,35,36,36,37,37,38,38,39,39,40,41,41,42,42,43,43,44,                      //  20 to  39
 44,45,46,46,47,47,48,48,49,49,50,51,51,52,52,53,53,54,54,55,                      //  40 to  59
 56,56,57,57,58,58,59,59,60,61,61,62,62,63,63,64,64,65,66,66,                      //  60 to  79
 67,67,68,68,69,69,70,71,71,72,72,73,73,74,74,75,76,76,77,77,                      //  80 to  99
 78,78,79,79,80,81,81,82,82,83,83,84,84,85,86,86,87,87,88,88,                      // 100 to 119
 89,89,90,91,91,92,92,93,93,94,94,95,96,96,97,97,98,98,99,99,                      // 120 to 139
 100,101,101,102,102,103,103,104,104,105,106,106,107,107,108,108,109,109,110,111,  // 140 to 159
 111,112,112,113,113,114,114,115,116,116,117,117,118,118,119,119,120,121,121,122,  // 160 to 179
 122,123,123,124,124,125,126,126,127,127,128,128,129,129,130,131,131,132,132,133,  // 180 to 199
 133,134,134,135,136,136,137,137,138,138,139,139,140,141,141,142,142,143,143,144,  // 200 to 219
 144,145,146,146,147,147,148,148,149,149,150,151,151,152,152,153,153,154,154,155,  // 220 to 239
 156,156,157,157,158,158,159,159,160,161,161,162,162,163,163,164,164,165,166,166,  // 240 to 259
 167,167,168,168,169,169,170,171,171,172,172,173,173,174,174,175,176,176,177,177,  // 260 to 279
 178,178,179,179,180,181,181,182,182,183,183,184,184,185,186,186,187,187,188,188,  // 280 to 299
 189,189,190,191,191,192,192,193,193,194,194,195,196,196,197,197,198,198,199,199,  // 300 to 319
 200,201,201,202,202,203,203,204,204,205,206,206,207,207,208,208,209,209,210,211,  // 320 to 339
 211,212,212,213,213,214,214,215,216,216,217,217,218,218,219,219,220,221,221,222,  // 340 to 359
 222,223,223,224,224,225,226,226,227,227,228,228,229,229,230,231,231,232,232,233,  // 360 to 379
 233,234,234,235,236,236,237,237,238,238,239,239,240,241,241,242,242,243,243,244,  // 380 to 399
 244,245,246,246,247,247,248,248,249,249,250                                       // 400 to 410
};

const uint16_t CelsiusToFahrenheit[256] =
{
  0,2,4,5,7,9,11,13,14,16,18,20,22,23,25,27,29,31,32,34,
  36,38,40,41,43,45,47,49,50,52,54,56,58,59,61,63,65,67,68,70,
  72,74,76,77,79,81,83,85,86,88,90,92,94,95,97,99,101,103,104,106,
  108,110,112,113,115,117,119,121,122,124,126,128,130,131,133,135,137,139,140,142,
  144,146,148,149,151,153,155,157,158,160,162,164,166,167,169,171,173,175,176,178,
  180,182,184,185,187,189,191,193,194,196,198,200,202,203,205,207,209,211,212,214,
  216,218,220,221,223,225,227,229,230,232,234,236,238,239,241,243,245,247,248,250,
  252,254,256,257,259,261,263,265,266,268,270,272,274,275,277,279,281,283,284,286,
  288,290,292,293,295,297,299,301,302,304,306,308,310,311,313,315,317,319,320,322,
  324,326,328,329,331,333,335,337,338,340,342,344,346,347,349,351,353,355,356,358,
  360,362,364,365,367,369,371,373,374,376,378,380,382,383,385,387,389,391,392,394,
  396,398,400,401,403,405,407,409,410,412,414,416,418,419,421,423,425,427,428,430,
  432,434,436,437,439,441,443,445,446,448,450,452,454,455,457,459
};


//******************************************************************************
// MACROS
//******************************************************************************
#define SEND_CAN01_NOW          CAN01sTX.SendRightNow();
#define SEND_CAN02_NOW          CAN02sTX.SendRightNow();
#define SEND_CAN03_NOW          CAN03sTX.SendRightNow();
#define SEND_CAN20_NOW          CAN20sTX.SendRightNow();
#define SEND_BICS_NOW           HWJ1939BICSControlTX.SendRightNow();


//******************************************************************************
// GLOBAL VARIBLES
//******************************************************************************
extern uint8_t LCD[8]; // 0-4 are main segments, 5 is the gear #, 7 is radix and colon.
extern uint8_t activeCodeIndex;

extern uint8_t count_GeneralIcon;  //Used to for secondary controllers errors, display general warning icon.


extern hw_can_rxmsg PanelButtonStateIntRX;
extern hw_can_txmsg HWJ1939BICSControlTX;
extern hw_can_txmsg CAN01sTX;  // Auxiliary Start/Stop Command
extern hw_can_txmsg CAN03sTX;  // Auxiliary Start/Stop Command

extern uint16_t can_FuelRate;


//******************************************************************************
// FUNCTION PROTOTYPE
//******************************************************************************
void ap_can_initialize(void);
void ap_can_update (void);
void Send_Request_Message(uint16_t PGN, uint8_t DA, uint8_t direction);



#endif