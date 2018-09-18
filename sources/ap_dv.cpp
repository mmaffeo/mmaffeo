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
* First written on 31 January, 2006 by Spencer Mindeman
*
* Module Description:
* DV table and routines for doing various diagnostic info.
***************************************************************/

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"

#include "ap_dv.h"
#include "global.h"
#include "ap_eeprom.h"
#include "ap_subs.h"
#include "defines.h"
#include "ap_MXGWcontrol_defs.h"
#include "ap_bservice_dv.h"
#include "ap_can.h"
#include "hw_io.h"
#include "ap_deluxeG5.h"
#include "stdbool.h"

//******************************************************************************
// DEFINE SECTION
//******************************************************************************

//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************
dv_table_block DV;
dv_table_block DV2;
dv_table_block ActiveCodes;

uint8_t dvTestHourMeter;
uint8_t dvTest;

bool dvRamDoneFlag;
uint8_t dvTestDone;

bool inDVCode;
bool dvPanelOn;

uint16_t newHour1;
uint16_t newHour2;

uint16_t dvPassword;
uint16_t dvCommand;

uint16_t serviceType;

uint8_t hourMeter;

J1939_TP_tx CommandedAddress_TP_tx;
J1939_msg_t CommandedAddress_TP_msg;
uint8_t TPmsgData[9];

uint8_t * p_ecu_SOFT = ecu_SOFT;



void * const dv_table[] =  //0x20##
{
  //EOP
  &adin_EOP ,                 //  0x00
  &state_EOP ,                //  0x01 - Do not move, SA monitor
  &rm_EOP ,                   //  0x02
  &flt_EOP  ,                 //  0x03
  &gau_EOP  ,                 //  0x04
  &outputSelect_EOP ,         //  0x05
  &level_ShutdownEOP,         //  0x06
  &level_WarningEOP,          //  0x07
  (void *)0,                  //  0x08
  (void *)0,                  //  0x09
  (void *)0,                  //  0x0A

  //Alternator
  &state_Alternator,          //  0x0B

  //ECT
  &ain_ECT  ,                 //  0x0C
  &state_ECT  ,               //  0x0D - Do not move, SA monitor
  &rm_ECT ,                   //  0x0E
  &flt_ECT  ,                 //  0x0F - Do not move, SA monitor
  &gau_ECT  ,                 //  0x10

  //HOT
  &adin_HOT ,                 //  0x11
  &state_HOT  ,               //  0x12 - Do not move, SA monitor
  &rm_HOT ,                   //  0x13
  &flt_HOT  ,                 //  0x14 - Do not move, SA monitor
  &gau_HOT  ,                 //  0x15
  &outputSelect_HOT ,         //  0x16

  //Glow Plugs
  &dfbk_GlowPlugOutput  ,     //  0x17
  &din_GlowPlugRelay  ,       //  0x18
  &dout_GlowPlug  ,           //  0x19
  &state_GlowPlugOutput ,     //  0x1A
  &state_GlowPlugRelay  ,     //  0x1B
  &count_GlowPlug ,           //  0x1C

  //Battery
  &ain_VBattery ,             //  0x1D
  &state_VBattery ,           //  0x1E - Do not move, SA monitor
  &calc_VBattery  ,           //  0x1F
  &calcFlt_VBattery ,         //  0x20 - Do not move, SA monitor

  //Sensor Supplies
  &ain_SensorSupply1  ,       //  0x21 - Do not move, SA monitor
  &state_SensorSupply1  ,     //  0x22 - Do not move, SA monitor
  &ain_SensorSupply2  ,       //  0x23 - Do not move, SA monitor
  &state_SensorSupply2  ,     //  0x24 - Do not move, SA monitor


  //Switched Power
  &dfbk_SwPowerOutput ,       //  0x25
  &din_SwPowerRelay ,         //  0x26
  &dout_SwitchedPwr ,         //  0x27
  &state_SwitchedPwrOutput  , //  0x28
  &state_SwitchedPwrRelay ,   //  0x29

  //Air Filter
  &din_AirFilter  ,           //  0x2A
  &state_AirFilter  ,         //  0x2B - Do not move, SA monitor

  //Hyd Filter
  &din_HCFilter1  ,           //  0x2C
  &state_HCFilter1  ,         //  0x2D - Do not move, SA monitor
  (void *)0,                  //  0x2E
  (void *)0,                  //  0x2F

  //Console
  &ain_Console  ,             //  0x30
  &rm_Console ,               //  0x31
  &state_Console  ,           //  0x32

  //Key
  &din_RunEnter ,             //  0x33
  &din_RemoteKey  ,           //  0x34
  &state_Key,                 //  0x35

  //Engine Speed
  &calc_EngineSpeed,          //  0x36
  &gain_EngineSpeed,          //  0x37
  (uint16_t *)&freq_EngineSpeed + 1 , // 0x38
  (uint16_t *)&freq_EngineSpeed ,     // 0x39
  &flt_EngineSpeed  ,         //  0x3A - Do not move, SA monitor
  &state_EngineSpeed  ,       //  0x3B - Do not move, SA monitor

  //Starter
  &dfbk_StarterOutput ,       //  0x3C
  &din_StarterRelay ,         //  0x3D
  &dout_Starter ,             //  0x3E
  &state_StarterOutput ,      //  0x3F
  &state_StarterRelay ,       //  0x40

  //Fuel Level
  &ain_FuelLevel  ,           //  0x41
  &rm_FuelLevel ,             //  0x42
  &gau_FuelLevel  ,           //  0x43 - Do not move, SA monitor
  &state_FuelLevel  ,         //  0x44

  //Fuel Pull/Hold
  &dfbk_FuelPriOutput ,       //  0x45
  &din_FuelPriRelay ,         //  0x46
  &dout_FuelPri       ,       //  0x47
  &state_FuelPriOutput  ,     //  0x48
  &state_FuelPriRelay ,       //  0x49
  &afbk_FuelSec ,             //  0x4A
  &duty_FuelSec ,             //  0x4B
  &state_FuelSec ,            //  0x4C
  &error_FuelSec ,            //  0x4D
  &timer_FuelResolution,      //  0x4E
  (void *)0,                  //  0x4F
  (void *)0,                  //  0x50
  (void *)0,                  //  0x51

  //Auxiliaries
  &ain_AuxPot,                //  0x52
  &position_AuxPot,           //  0x53
  &rm_AuxPot,                 //  0x54
  &state_AuxPot,              //  0x55
  &aux_DebounceButton,        //  0x56
  &state_AuxEnable,           //  0x57
  &din_Detent,                //  0x58
  &state_Detent,              //  0x59
  &aux_Flow,                  //  0x5A
  &state_DetentEnable,        //  0x5B
  &afbk_AuxBase,              //  0x5C
  &ifbk_AuxBase,              //  0x5D
  &afbk_AuxRod,               //  0x5E
  &ifbk_AuxRod,               //  0x5F
  &hs_AuxBase,                //  0x60
  &ls_AuxBase,                //  0x61
  &errorCC_AuxBase,           //  0x62
  &calc_ifbk_AuxBase,         //  0x63
  &state_AuxBase,             //  0x64
  &hs_AuxRod,                 //  0x65
  &ls_AuxRod,                 //  0x66
  &errorCC_AuxRod,            //  0x67
  &calc_ifbk_AuxRod,          //  0x68
  &state_AuxRod,              //  0x69
  &state_DetentEnable,        //  0x6A
  &state_AuxRelease,          //  0x6B
  (void *)0,                  //  0x6C
  //Hydraulics Enable
  &afbk_HydEnable,            //  0x6D
  &ifbk_HydEnable,            //  0x6E
  &state_HydEnable,           //  0x6F
  &hs_HydEnable,              //  0x70
  &ls_HydEnable,              //  0x71
  &afbk_HydBypass,            //  0x72
  &ifbk_HydBypass,            //  0x73
  &state_HydBypass,           //  0x74
  &hs_HydBypass,              //  0x75
  &ls_HydBypass,              //  0x76
  //Lights
  &dfbk_LightsOutput  ,       //  0x77
  &din_LightsRelay ,          //  0x78
  &state_LightsOutput ,       //  0x79
  (void *)0,                  //  0x7A
  (void *)0,                  //  0x7B
  (void *)0,                  //  0x7C
  &dout_Lights  ,             //  0x7D
  (void *)0,                  //  0x7E

  //LHP Icons
  &icon_Seatbelt  ,           //  0x7F
  &icon_Lockout ,             //  0x80
  (void *)0,                  //  0x81
  &count_GeneralIcon  ,       //  0x82
  &icon_Engine  ,             //  0x83
  &icon_Hydraulic,            //  0x84
  &icon_General ,             //  0x85
  &icon_ECT ,                 //  0x86
  &icon_Fuel  ,               //  0x87
  &icon_GlowPlug  ,           //  0x88
  &icon_RPM ,                 //  0x89
  &icon_Battery ,             //  0x8A
  &icon_Service ,             //  0x8B
  &icon_Hourmeter ,           //  0x8C
  &icon_JobClock1 ,           //  0x8D
  &icon_JobClock2 ,           //  0x8E
  &level_DisplayBacklight ,   //  0x8F
  &level_IconBacklight  ,     //  0x90
  &icon_Rabbit,               //  0x91
  (void *)0,                  //  0x92
  (void *)0,                  //  0x93
  (void *)0,                  //  0x94


  //DV_Service Analyzer
  &newHour1 ,                 //  0x95
  &newHour2 ,                 //  0x96
  &serviceType    ,           //  0x97
  (uint16_t *)&actualHourMeter+1  ,     //  0x98
  (uint16_t *)&actualHourMeter  ,       //  0x99
  (uint16_t *)&actualHourMeterCopy+1  , //  0x9A
  (uint16_t *)&actualHourMeterCopy  ,   //  0x9B
  &dvPassword ,               //  0x9C
  &dvCommand  ,               //  0x9D

  //Controller
  &state_System,              //  0x9E
  &max_stack_size,            //  0x9F
  &hourMeterUpdateTimer,      //  0xA0
  &hourMeter,                 //  0xA1
  &currentHourMeter,          //  0xA2
  &eeMode,                    //  0xA3
  &eeState,                   //  0xA4
  &eeBusy,                    //  0xA5
  &state_ConsoleTest,         //  0xA6
  &state_ConstantData,        //  0xA7
  &flag_StdActiveWarn,        //  0xA8
  &dropped_message,           //  0xA9
  &state_Buzzer,              //  0xAA
  &ain_SwitchedPower,         //  0xAB
  &ain_PrecisionReference,    //  0xAC
  &eeWriteActualCounter,      //  0xAD
  &eeTimeToUpdateMirror,      //  0xAE
  &flag_InitEERead,           //  0xAF

  //LHP Buttons
  (void *)0,                  //  0xB0
  (void *)0,                  //  0xB1
  (void *)0,                  //  0xB2
  &ind_Light1,                //  0xB3
  (void *)0,                  //  0xB4
  &ind_Aux1,                  //  0xB5
  &ind_AutoIdle,              //  0xB6
  &msg_PanelButtonState[0]  , //  0xB7
  &msg_PanelButtonState[1]  , //  0xB8
  &msg_PanelButtonState[2],   //  0xB9
  &msg_PanelButtonState[3],   //  0xBA
  &msg_PanelButtonState[4],   //  0xBB
  &msg_PanelButtonState[5],   //  0xBC
  &msg_PanelButtonState[6],   //  0xBD
  &msg_PanelButtonState[7],   //  0xBE
  &state_CommStdPanel,        //  0xBF
  &ind_Aux2,                  //  0xC0

  //Service Tool
  &can_ST_EStop,              //  0xC1
  &state_ST_CAN,              //  0xC2
  &cmd_AuxEnable_ST,          //  0xC3

  //Deluxe Panel
  &ddp_MachineLock,           //  0xC4
  &rx_DeluxeStatus.msg_age_mS,//  0xC5
  (void *)0,//&downgradedG5Deluxe,        //  0xC6
  &dlxMode,                   //  0xC7
  &flag_SendDeluxeWarning,    //  0xC8
  &ddpSwitchStatus.switchByte[0], //  0xC9
  &ddpSwitchStatus.switchByte[1], //  0xCA
  &ddpSwitchStatus.switchByte[2], //  0xCB
  &ddpSwitchStatus.switchByte[3], //  0xCC
  &ddpSwitchStatus.switchByte[4], //  0xCD
  &newlyBootedDDP,            //  0xCE
  &current_user,              //  0xCF
  &obtainedCurrentUser,       //  0xD0
  &downgradedFromDDP,         //  0xD1
  &newPasswordNumber,         //  0xD2
  &newPasswordVerification,   //  0xD3
  &ddpPasswordScreenChanged,  //  0xD4
  &scrn_DeluxePwdFail,        //  0xD5
  &state_DeluxeG5,            //  0xD6
  (void *)0,                  //  0xD7

  //Keyless
  &pwd_Position,              //  0xD8
  &state_KSLock,              //  0xD9
  &state_KSPassword,          //  0xDA
  &pwd_Keyless[0],            //  0xDB
  &pwd_Keyless[1],            //  0xDC
  &pwd_Keyless[2],            //  0xDD
  &pwd_Keyless[3],            //  0xDE
  &pwd_Keyless[4],            //  0xDF
  &can_Keypad[0],             //  0xE0
  &can_Keypad[1],             //  0xE1
  &can_Keypad[2],             //  0xE2
  &state_KeylessPanel,        //  0xE3
  &state_MachineLock,         //  0xE4
  &ind_Lock,                  //  0xE5
  &ind_Unlock,                //  0xE6
  &eeMirror.passwordLock,     //  0xE7
  &eeMirror.keypad,           //  0xE8

  //Engine
  &din_EngineStart  ,         //  0xE9
  &can_ST_EngineStart ,       //  0xEA
  &can_ACD_EngineStart,       //  0xEB
  &state_EngineStart ,        //  0xEC
  &state_Engine ,             //  0xED
  &state_Idle,                //  0xEE
  (void *)0,                  //  0xEF

  //LHP LCD
  &state_InfoSecondary,       //  0xF0
  &state_InfoPrimary  ,       //  0xF1
  &LCD[0],                    //  0xF2
  &LCD[1],                    //  0xF3
  &LCD[2],                    //  0xF4
  &LCD[3],                    //  0xF5
  &LCD[4],                    //  0xF6
  &LCD[5],                    //  0xF7
  &LCD[6],                    //  0xF8
  &LCD[7],                    //  0xF9
  (void *)0,                  //  0xFA

  //ACD
  &cmd_AuxEnable_ACD,         //  0xFB
  &state_ACD_CAN,             //  0xFC
  &can_ACD_EStop,             //  0xFD
  &can_ACD_AuxCommand,        //  0xFE
  (void *)0,                  //  0xFF



};

void * const activeCodes_table[] =
{
  &FailureQueue[0].device ,   //  0x00
  &FailureQueue[0].function , //  0x01
  &FailureQueue[0].failure  , //  0x02
  &FailureQueue[0].timer  ,   //  0x03
  &FailureQueue[1].device ,   //  0x04
  &FailureQueue[1].function , //  0x05
  &FailureQueue[1].failure  , //  0x06
  &FailureQueue[1].timer  ,   //  0x07
  &FailureQueue[2].device ,   //  0x08
  &FailureQueue[2].function , //  0x09
  &FailureQueue[2].failure  , //  0x0A
  &FailureQueue[2].timer  ,   //  0x0B
  &FailureQueue[3].device ,   //  0x0C
  &FailureQueue[3].function , //  0x0D
  &FailureQueue[3].failure  , //  0x0E
  &FailureQueue[3].timer  ,   //  0x0F
  &FailureQueue[4].device ,   //  0x10
  &FailureQueue[4].function , //  0x11
  &FailureQueue[4].failure  , //  0x12
  &FailureQueue[4].timer  ,   //  0x13
  &FailureQueue[5].device ,   //  0x14
  &FailureQueue[5].function , //  0x15
  &FailureQueue[5].failure  , //  0x16
  &FailureQueue[5].timer  ,   //  0x17
  &FailureQueue[6].device ,   //  0x18
  &FailureQueue[6].function , //  0x19
  &FailureQueue[6].failure  , //  0x1A
  &FailureQueue[6].timer  ,   //  0x1B
  &FailureQueue[7].device ,   //  0x1C
  &FailureQueue[7].function , //  0x1D
  &FailureQueue[7].failure  , //  0x1E
  &FailureQueue[7].timer  ,   //  0x1F
  &FailureQueue[8].device ,   //  0x20
  &FailureQueue[8].function , //  0x21
  &FailureQueue[8].failure  , //  0x22
  &FailureQueue[8].timer  ,   //  0x23
  &FailureQueue[9].device ,   //  0x24
  &FailureQueue[9].function , //  0x25
  &FailureQueue[9].failure  , //  0x26
  &FailureQueue[9].timer  ,   //  0x27

  //Throttle Controller
  &state_CommThrottle,        //  0x28
  &msgAge_Throttle,           //  0x29

  //Throttle
  &ain_ThrottlePrimary,       //  0x2A
  &pos_ThrottlePrimary,       //  0x2B
  &state_ThrottlePrimary,     //  0x2C
  &percent_Throttle,          //  0x2D
  (void *)0,                  //  0x2E
  (void *)0,                  //  0x2F

   //Offset
  &ain_OffsetPot,             //  0x30
  (void *)0,                  //  0x31
  (void *)0,                  //  0x32
  &state_OffsetPot,           //  0x33
  &position_OffsetPot,        //  0x34
  &rm_OffsetPot,              //  0x35
  &afbk_OffsetBase,           //  0x36
  &ifbk_OffsetBase,           //  0x37
  &afbk_OffsetRod,            //  0x38
  &ifbk_OffsetRod,            //  0x39
  &hs_OffsetBase,             //  0x3A
  &ls_OffsetBase,             //  0x3B
  &errorCC_OffsetBase,        //  0x3C
  &calc_ifbk_OffsetBase,      //  0x3D
  &state_OffsetBase,          //  0x3E
  &hs_OffsetRod,              //  0x3F
  &ls_OffsetRod,              //  0x40
  &errorCC_OffsetRod,         //  0x41
  &calc_ifbk_OffsetRod,       //  0x42
  &state_OffsetRod,           //  0x43
  (void *)0,                  //  0x44
  (void *)0,                  //  0x45
  (void *)0,                  //  0x46
  (void *)0,                  //  0x47

  //Load Moment
  &ain_LoadMoment,            //  0x48
  &state_LoadMoment,          //  0x49
  &bar_LoadMoment,            //  0x4A
  &volts_LoadMoment,          //  0x4B
  (void *)0,                  //  0x4C
  (void *)0,                  //  0x4D

  //Load Sense
  &adin_LoadSense,            //  0x4E
  &state_LoadSense,           //  0x4F
  &psi_LoadSense,             //  0x50
  &bar_LoadSense,             //  0x51
  &volts_LoadSense,           //  0x52
  &din_OWDEnableSw,           //  0x53
  (void *)0,                  //  0x54
  (void *)0,                  //  0x55
  (void *)0,                  //  0x56

  //Auto Idle
  &state_AutoIdleEnable ,     //  0x57
  &cmd_Throttle,              //  0x58
  (void *)0,//&cmd_AutoIdle,              //  0x59
  &eeMirror.ee_AutoIdleEnabled,//  0x5A
  (void *)0,                  //  0x5B
  (void *)0,                  //  0x5C

  //Two Speed
  &din_TwoSpeedSwitch,        //  0x5D
  (void *)0,                  //  0x5E
  &adin_TravelPressureSwitch, //  0x5F
  &afbk_TwoSpeed,             //  0x60
  (void *)0,                  //  0x61
  &duty_TwoSpeed,             //  0x62
  (void *)0,                  //  0x63
  &state_TwoSpeed,            //  0x64
  &state_TwoSpeedIcon,        //  0x65
  (void *)0,                  //  0x66
  (void *)0,                  //  0x67
  (void *)0,                  //  0x68
  (void *)0,                  //  0x69

  //Secondary Controller
  &msgAge_Secondary,          //  0x6A
  &state_CommSecondary,       //  0x6B
  (void *)0,                  //  0x6C
  (void *)0,                  //  0x6D
  (void *)0,                  //  0x6E
  (void *)0,                  //  0x6F
  (void *)0,                  //  0x70
  (void *)0,                  //  0x71
  (void *)0,                  //  0x72
  (void *)0,                  //  0x73
  (void *)0,                  //  0x74
  &eeMirror.serviceClockLength + 5,           //  0x75
  (void *)0,                  //  0x76
  (void *)0,                  //  0x77

  //Hyd Exchange
  &dfbk_HydExchange,          //  0x78
  &dout_HydExchange,          //  0x79
  &state_HydExchange,         //  0x7A
  (void *)0,                  //  0x7B
  (void *)0,                  //  0x7C
  (void *)0,                  //  0x7D
  (void *)0,                  //  0x7E
  (void *)0,                  //  0x7F

  //HVAC
  &dout_HVACOutput,           //  0x80
  &state_HVACOutput,          //  0x81
  &dfbk_HVACOutput,           //  0x82
  (void *)0,                  //  0x83
  (void *)0,                  //  0x84
  (void *)0,                  //  0x85

  //ECU
  &ecu_EOP,                   //  0x86
  &ecu_ECT,                   //  0x87
  &ecu_GlowPlug,              //  0x88
  &ecu_EngineSpeed,           //  0x89
  &ecu_EngineStarterMode,     //  0x8A
  &lamp_Engine,               //  0x8B
  &state_CommECU,             //  0x8C
  &msgAge_ECU,                //  0x8D
  &state_ECUHold,             //  0x8E
  &ecu_EOT,                   //  0x8F
  &ecu_BarPressure,           //  0x90
  &ecu_AirInletTemp,          //  0x91
  &ecu_HP,                    //  0x92
  &can_FuelTemp,              //  0x93
  &state_FuelTemp,            //  0x94
  //Derate
  &ecu_PercentTorque,         //  0x95
  &ecu_isocMinRPM,            //  0x96
  &ecu_isocMaxRPM,            //  0x97
  &percent_Derate,            //  0x98
  &rpm_Derate,                //  0x99
  &state_EngineSpeedDerate,   //  0x9A
  &state_EOT,                 //  0x9B
  &state_TC,                  //  0x9C
  &derate_Throttle,           //  0x9D
  &torque_Derate,             //  0x9E
  &dv_TurboPrime,             //  0x9F
  //SecondAux
  &afbk_Diverter,             //  0xA0
  &ifbk_Diverter,             //  0xA1
  &state_Diverter,            //  0xA2
  &hs_Diverter,               //  0xA3
  &ls_Diverter,               //  0xA4
  &cmd_Diverter,              //  0xA5
  &din_SecondAuxSw,           //  0xA6
  (void *)0,                  //  0xA7
  (void *)0,                  //  0xA8
  (void *)0,                  //  0xA9
  (void *)0,                  //  0xAA
  (void *)0,                  //  0xAB
  (void *)0,                  //  0xAC
  (void *)0,                  //  0xAD
  (void *)0,                  //  0xAE
  (void *)0,                  //  0xAF
  
  //Gen5.5 Deluxe
  &msgAge_DeluxeG55,          //  0xB0
  &dlx_G55_AutoIdle,          //  0xB1
  &dlx_G55_EcoMode,           //  0xB2
  &auth_DeluxeG55,            //  0xB3
  &dlx_G55_AutoIdleTime,      //  0xB4
  &state_CommDeluxeG55,       //  0xB5
  (void *)0,//&dlx_G55_AuxReleaseStatus,  //  0xB6
  &msgAge_JogShuttle,         //  0xB7
  &btn_JogShuttleAux,         //  0xB8
  &btn_JogShuttleLights,      //  0xB9
  &state_CommJogShuttle,      //  0xBA
  (void *)0,                  //  0xBB

  //ECU Fuel
  &can_FuelRate,                        //  0xBC
  (uint16_t *)&can_FuelConsumption+1,   //  0xBD
  (uint16_t *)&can_FuelConsumption,     //  0xBE
  (uint16_t *)&start_FuelConsumption+1, //  0xBF
  (uint16_t *)&start_FuelConsumption,   //  0xC0
  &eeMirror.userInfo[1].fuelConsumption,//  0xC1
  &current_FuelConsumption,             //  0xC2
  &state_ecuECT,                  //  0xC3
  (void *)0,                  //  0xC4
  &p_ecu_SOFT,                //  0xC5
  (void *)0,                  //  0xC6
  (void *)0,                  //  0xC7
  (void *)0,                  //  0xC8
  (void *)0,                  //  0xC9
  (void *)0,                  //  0xCA
  (void *)0,                  //  0xCB
  (void *)0,                  //  0xCC
  (void *)0,                  //  0xCD
  (void *)0,                  //  0xCE
  (void *)0,                  //  0xCF
  
  //Keyless Entry
  &can_KeylessEntry[0],         //  0xD0
  &can_KeylessEntry[1],         //  0xD1
  &can_KeylessEntry[2],         //  0xD2
  &state_KeylessEntryPowerHold, //  0xD3
  &state_KeylessEntryLock,      //  0xD4
  &user_KeylessEntry,           //  0xD5
  &state_KeylessEntryPassword,  //  0xD6
  &cabKeyDetect,                //  0xD7
};

void * const dv_table2[] =  //0x22##
{

  (void *)0,                  //  0x00
  &reset_ServiceClock,        //0x2201
  (void *)0,                  //  0x02
  (void *)0,                  //  0x03
  (void *)0,                  //  0x04
  (void *)0,                  //  0x05
  &state_EcoMode,             //  0x06

  (void *)0,                  //  0x07
  (void *)0,                  //  0x08
  (void *)0,                  //  0x09
  (void *)0,                  //  0x0A
  (void *)0,                  //  0x0B
  (void *)0,                  //  0x0C
  (void *)0,                  //  0x0D
  (void *)0,                  //  0x0E
  (void *)0,                  //  0x0F


  //CAN Throttle Actuator
  &eeMirror.ee_ThrottleCalState,      //  0x10
  &eeMirror.ee_ThrottleCalRetracted,  //  0x11
  &eeMirror.ee_ThrottleCalExtended,   //  0x12
  &fdbk_CANThrottle,                  //  0x13
  (void *)0,                  //  0x14
  (void *)0,                  //  0x15
  (void *)0,                  //  0x16
  (void *)0,                  //  0x17
  (void *)0,                  //  0x18
  (void *)0,                  //  0x19
  (void *)0,                  //  0x1A
  (void *)0,                  //  0x1B
  (void *)0,                  //  0x1C
  (void *)0,                  //  0x1D
  (void *)0,                  //  0x1E
  (void *)0,                  //  0x1F


  //ECU Hours
  (uint16_t *)&ecu_Hours+1,   //  0x20
  (uint16_t *)&ecu_Hours,     //  0x21
  &flag_RxECUHours,           //  0x22

  // Dump Valve
  &afbk_DumpValve,            //  0x23
  &ifbk_DumpValve,            //  0x24
  &state_DumpValve,           //  0x25
  &hs_DumpValve,              //  0x26
  &ls_DumpValve,              //  0x27
  &errorCC_DumpValve,         //  0x28
  &calc_ifbk_DumpValve,       //  0x29
  (void *)0,                  //  0x2A
  (void *)0,                  //  0x2B
  (void *)0,                  //  0x2C
  (void *)0,                  //  0x2D
  (void *)0,                  //  0x2E
  (void *)0,                  //  0x2F

  //PB Valve
  &dfbk_PBValveOutput ,       //  0x30
  &din_PBValveRelay ,         //  0x31
  &dout_PBValve ,             //  0x32
  &state_PBValveOutput  ,     //  0x33
  &state_PBValveRelay ,       //  0x34

  //Passwords
  &ee_OwnerPassword[0],       // 0x35
  &ee_OwnerPassword[1],       // 0x36
  &ee_OwnerPassword[2],       // 0x37
  &ee_OwnerPassword[3],       // 0x38
  &ee_OwnerPassword[4],       // 0x39
  &eeMirror.password[1].value[0], // 0x3A
  &eeMirror.password[1].value[1], // 0x3B
  &eeMirror.password[1].value[2], // 0x3C
  &eeMirror.password[1].value[3], // 0x3D
  &eeMirror.password[1].value[4], // 0x3E
  &eeMirror.password[2].value[0], // 0x3F
  &eeMirror.password[2].value[1], // 0x40
  &eeMirror.password[2].value[2], // 0x41
  &eeMirror.password[2].value[3], // 0x42
  &eeMirror.password[2].value[4], // 0x43
  &PWD_NumberSelected,            // 0x44
  (void *)0,                      // 0x45
  (void *)0,                      // 0x46
  (void *)0,                      // 0x47
  //Active Codes - ECU
  &FailureQueue[0].type,                // 0x48
  &FailureQueue[0].spn,                 // 0x49
  &FailureQueue[1].type,                // 0x4A      
  &FailureQueue[1].spn,                 // 0x4B
  &FailureQueue[2].type,                // 0x4C
  &FailureQueue[2].spn,                 // 0x4D
  &FailureQueue[3].type,                // 0x4E
  &FailureQueue[3].spn,                 // 0x4F
  &FailureQueue[4].type,                // 0x50
  &FailureQueue[4].spn,                 // 0x51
  &FailureQueue[5].type,                // 0x52
  &FailureQueue[5].spn,                 // 0x53
  &FailureQueue[6].type,                // 0x54
  &FailureQueue[6].spn,                 // 0x55
  &FailureQueue[7].type,                // 0x56
  &FailureQueue[7].spn,                 // 0x57
  &FailureQueue[8].type,                // 0x58
  &FailureQueue[8].spn,                 // 0x59
  &FailureQueue[9].type,                // 0x5A
  &FailureQueue[9].spn,                 // 0x5B  
  (void *)0,                            // 0x5C
  (void *)0,                            // 0x5D
  (void *)0,                            // 0x5E
  (void *)0,                            // 0x5F
  
  //EMEA Controls
  &din_LeftHandleSelectSw,              // 0x60
  &ain_Aux2FlowControl,                 // 0x61
  &can_OffsetSelectSw,                  // 0x62
  &can_RightHandleSelectSw,             // 0x63
  &mode_LeftControl,                    // 0x64
  &mode_RightControl,                   // 0x65
  &aux_Inhibit,                         // 0x66
  (void *)0,                            // 0x67
  (void *)0,                            // 0x68
  (void *)0,                            // 0x69
  (void *)0,                            // 0x6A
  (void *)0,                            // 0x6B
  &state_LeftPot,                       // 0x6C
  &position_LeftPot,                    // 0x6D
  &rm_LeftPot,                          // 0x6E
  &state_RightPot,                      // 0x6F
  &position_RightPot,                   // 0x70
  &rm_RightPot,                         // 0x71
  &eeMirror.ee_ControlMode,             // 0x72
  &mode_ControlChange,                  // 0x73
  &disp_LeftControl,                    // 0x74
  &disp_RightControl,                   // 0x75
  &flow_Aux1Percent,                    // 0x76
  &flow_Aux2Percent,                    // 0x77
  &flow_Aux4Percent,                    // 0x78
  &flow_OffsetPercent,                  // 0x79  
  &flag_AuxEnableFlash,                 // 0x7A
  &flag_AuxModeReminder                 // 0x7B
};

//******************************************************************************
// FUNCTIONS
//******************************************************************************

uint8_t DV_read_uint8(uint16_t i)
//******************************************************************************
//    returns     : Returns value of variable read from table.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Handles byte reads to the DV table.
//    Notes       :
//******************************************************************************
{
    uint8_t rvalue=0 ;

    if ( i < (sizeof(dv_table) / sizeof(const uint8_t * const)) )
    {
        rvalue = *(uint8_t*)dv_table[i];
    }

    return rvalue;
}

uint16_t DV_read_uint16(uint16_t i)
//******************************************************************************
//    returns     : Returns value of variable read from the table.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Handles word reads to the DV table.
//    Notes       :
//******************************************************************************
{
    uint16_t rvalue=0 ;

    if ( i < (sizeof(dv_table) / sizeof(const uint16_t * const)) )
    {
        rvalue = *(uint16_t*)dv_table[i];
    }

    return rvalue;
}

uint32_t DV_read_uint32(uint16_t i)
//******************************************************************************
//    returns     : Returns value of variable read from the table.
//
//    Created By  : AL
//    Date Created: 01 Aug, 2013
//    Description : Handles dword reads to the DV table.
//    Notes       :
//******************************************************************************
{
    uint32_t rvalue=0 ;

    if ( i < (sizeof(dv_table) / sizeof(const uint16_t * const)) )
    {
        rvalue = *(uint32_t*)dv_table[i];
    }

    return rvalue;
}

void DV_write_uint8(uint16_t i, uint8_t data)
//******************************************************************************
//    returns     : NONE
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Handles byte writes to the DV table.
//    Notes       :
//******************************************************************************
{
  uint8_t *msg_addr;

  if ( i < (sizeof(dv_table) / sizeof(const uint16_t * const)) )
  {
    msg_addr = (uint8_t *)dv_table[i];

    *msg_addr = data;
  }
}

void DV_write_uint16(uint16_t i, uint16_t data)
//******************************************************************************
//    returns     : NONE
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Handles word writes to the DV table.
//    Notes       :
//******************************************************************************
{
  uint16_t *msg_addr;

  if ( i < (sizeof(dv_table) / sizeof(const uint16_t * const)) )
  {
    msg_addr = (uint16_t*)dv_table[i];

    *msg_addr = data;
  }
}

void DV_write_uint32(uint16_t i, uint32_t data)
//******************************************************************************
//    returns     : NONE
//
//    Created By  : AL
//    Date Created: 01 Aug, 2013
//    Description : Handles dword writes to the DV table.
//    Notes       :
//******************************************************************************
{
  uint32_t *msg_addr;

  if ( i < (sizeof(dv_table) / sizeof(const uint16_t * const)) )
  {
    msg_addr = (uint32_t*)dv_table[i];

    *msg_addr = data;
  }
}

uint8_t ActiveCodes_read_uint8(uint16_t i)
//******************************************************************************
//    returns     : Returns value of variable read from table.
//
//    Created By  : SLM
//    Date Created: 07 June, 2006
//    Description : Handles word reads to the Active Codes table.
//    Notes       :
//******************************************************************************
{
    uint8_t rvalue=0 ;

    if ( i < (sizeof(activeCodes_table) / sizeof(const uint8_t * const)) )
    {
        rvalue = *(uint8_t*)activeCodes_table[i];
    }

    return rvalue;
}

uint16_t ActiveCodes_read_uint16(uint16_t i)
//******************************************************************************
//    returns     : Returns value of variable read from the table.
//
//    Created By  : SLM
//    Date Created: 07 June, 2006
//    Description : Handles word reads to the Active Codes table.
//    Notes       :
//******************************************************************************
{
    uint16_t rvalue=0 ;

    if ( i < (sizeof(activeCodes_table) / sizeof(const uint16_t * const)) )
    {
        rvalue = *(uint16_t*)activeCodes_table[i];
    }

    return rvalue;
}

uint32_t ActiveCodes_read_uint32(uint16_t i)
//******************************************************************************
//    returns     : Returns value of variable read from the table.
//
//    Created By  : AL
//    Date Created: 01 Aug, 2013
//    Description : Handles dword reads to the Active Codes table.
//    Notes       :
//******************************************************************************
{
    uint32_t rvalue=0 ;

    if ( i < (sizeof(activeCodes_table) / sizeof(const uint16_t * const)) )
    {
        rvalue = *(uint32_t*)activeCodes_table[i];
    }

    return rvalue;
}

uint8_t DV2_read_uint8(uint16_t i)
//******************************************************************************
//    returns     : Returns value of variable read from table.
//
//    Created By  : SLM
//    Date Created: 07 June, 2006
//    Description : Handles word reads to the Active Codes table.
//    Notes       :
//******************************************************************************
{
    uint8_t rvalue=0 ;

    if ( i < (sizeof(dv_table2) / sizeof(const uint8_t * const)) )
    {
        rvalue = *(uint8_t*)dv_table2[i];
    }

    return rvalue;
}

uint16_t DV2_read_uint16(uint16_t i)
//******************************************************************************
//    returns     : Returns value of variable read from the table.
//
//    Created By  : SLM
//    Date Created: 07 June, 2006
//    Description : Handles word reads to the Active Codes table.
//    Notes       :
//******************************************************************************
{
    uint16_t rvalue=0 ;

    if ( i < (sizeof(dv_table2) / sizeof(const uint16_t * const)) )
    {
        rvalue = *(uint16_t*)dv_table2[i];
    }

    return rvalue;
}

uint32_t DV2_read_uint32(uint16_t i)
//******************************************************************************
//    returns     : Returns value of variable read from the table.
//
//    Created By  : AL
//    Date Created: 01 Aug, 2013
//    Description : Handles word reads to the Active Codes table.
//    Notes       :
//******************************************************************************
{
    uint32_t rvalue=0 ;

    if ( i < (sizeof(dv_table2) / sizeof(const uint16_t * const)) )
    {
        rvalue = *(uint32_t*)dv_table2[i];
    }

    return rvalue;
}

void initialize_ap_dv(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Initializes standard DV table info
//    Notes       :
//******************************************************************************
{
    DV.initialize     (0x20);
    DV.set_read_byte_f(DV_read_uint8);
    DV.set_read_word_f(DV_read_uint16);
    DV.set_read_dword_f(DV_read_uint32);
    DV.set_write_byte_f(DV_write_uint8);
    DV.set_write_word_f(DV_write_uint16);
    DV.set_write_dword_f(DV_write_uint32);
    dv_list.add_block      (&DV);
}

void initialize_ap_ActiveCodes(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 7 Jun, 2006
//    Description : Initializes standard Active Codes table info
//    Notes       :
//******************************************************************************
{
    ActiveCodes.initialize     (0x21);
    ActiveCodes.set_read_byte_f(ActiveCodes_read_uint8);
    ActiveCodes.set_read_word_f(ActiveCodes_read_uint16);
    ActiveCodes.set_read_dword_f(ActiveCodes_read_uint32);
    dv_list.add_block      (&ActiveCodes);
}

void initialize_ap_dv2(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 7 Jun, 2006
//    Description : Initializes standard Active Codes table info
//    Notes       :
//******************************************************************************
{
    DV2.initialize     (0x22);
    DV2.set_read_byte_f(DV2_read_uint8);
    DV2.set_read_word_f(DV2_read_uint16);
    DV2.set_read_dword_f(DV2_read_uint32);
    dv_list.add_block      (&DV2);
}

static void ClearServiceCodes(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 Mar, 2006
//    Description : Clear service codes
//    Notes       :
//******************************************************************************
{
  uint8_t * dvMirrorPtr;
  uint8_t * firstAddress;
  uint8_t * endAddress;

  firstAddress = (uint8_t*) &eeMirror.queue;              // Set starting address for restore
  endAddress   = (uint8_t*) &eeMirror.queue + sizeof(eeMirror.queue); // address of queue ptr

  if(dvRamDoneFlag == FALSE)
  {
    // Clear mirror in RAM
    for(dvMirrorPtr = firstAddress; dvMirrorPtr < endAddress; dvMirrorPtr++)
    {
      *dvMirrorPtr = 0xFF;
    }

    dvRamDoneFlag = TRUE;
    eeMode  = EE_MIRROR_UPDATE;
    eeState = EE_MIRROR_WRITE_INIT;
  }

  if(eeMode != EE_IDLE)
  {
    eeServiceEEPROM();
  }
  else
  {
    dvTest = DV_TEST_DONE;
    dvRamDoneFlag = dvTestDone;
  }
}

#ifdef HCS12_BSP_EMU //if M4 compile this
static void ClearECUCodes(void)
//******************************************************************************
//    returns     : NONE.
//
//		Created By  : Boston Zachmann
//    Date Created: 17 June, 2016
//    Description : Clear ECU service codes
//    Notes       :
//******************************************************************************
{
  uint8_t * dvMirrorPtr;
  uint8_t * firstAddress;
  uint8_t * endAddress;
  
  firstAddress = (uint8_t*) &eeMirror.queueECU;						  // Set starting address for restore
  endAddress   = (uint8_t*) &eeMirror.queueECU + sizeof(eeMirror.queueECU); // address of queue ptr

  if(dvRamDoneFlag == FALSE)
  {
    // Clear mirror in RAM
    for(dvMirrorPtr = firstAddress; dvMirrorPtr < endAddress; dvMirrorPtr++)
    {
      *dvMirrorPtr = 0xFF;
    }
    
    dvRamDoneFlag = TRUE;
    eeMode  = EE_MIRROR_UPDATE;
    eeState = EE_MIRROR_WRITE_INIT;
  }
  
  if(eeMode != EE_IDLE)
  {
    eeServiceEEPROM();
  }
  else
  {
    dvTest = DV_TEST_DONE;
    dvRamDoneFlag = dvTestDone;
  }
}
#endif

static void ClearEvents(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 Mar, 2006
//    Description : Clear service codes
//    Notes       :
//******************************************************************************
{
  uint8_t * dvMirrorPtr;
  uint8_t * firstAddress;
  uint8_t * endAddress;

  firstAddress = (uint8_t*) &eeMirror.event[0];             // Set starting address for restore
  endAddress   = (uint8_t*) &eeMirror.event[NUMBER_OF_EVENTS - 1] + sizeof(&eeMirror.event); // address of queue ptr

  if(dvRamDoneFlag == FALSE)
  {
    // Clear mirror in RAM
    for(dvMirrorPtr = firstAddress; dvMirrorPtr < endAddress; dvMirrorPtr++)
    {
      *dvMirrorPtr = 0xFF;
    }

    dvRamDoneFlag = TRUE;
    eeMode  = EE_MIRROR_UPDATE;
    eeState = EE_MIRROR_WRITE_INIT;
  }

  if(eeMode != EE_IDLE)
  {
    eeServiceEEPROM();
  }
  else
  {
    dvTest = DV_TEST_DONE;
    dvRamDoneFlag = dvTestDone;
  }
}

static void ClearServiceClock(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 17 May, 2006
//    Description : Clear service clock queue
//    Notes       :
//******************************************************************************

{
  uint8_t * dvMirrorPtr;
  uint8_t * firstAddress;
  uint8_t * endAddress;

  firstAddress = (uint8_t*) &eeMirror.queueService;             // Set starting address for restore
  endAddress   = (uint8_t*) &eeMirror.queueService + sizeof(eeMirror.queueService); // address of queue ptr

  if(dvRamDoneFlag == FALSE)
  {
    // Clear mirror in RAM
    for(dvMirrorPtr = firstAddress; dvMirrorPtr < endAddress; dvMirrorPtr++)
    {
      *dvMirrorPtr = 0xFF;
    }

    dvRamDoneFlag = TRUE;
    eeMode  = EE_MIRROR_UPDATE;
    eeState = EE_MIRROR_WRITE_INIT;
  }

  if(eeMode != EE_IDLE)
  {
    eeServiceEEPROM();
  }
  else
  {
    dvTest = DV_TEST_DONE;
    dvRamDoneFlag = dvTestDone;
  }
}

static void SetHourMeter(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 Mar, 2006
//    Description : Resets hourmeter
//    Notes       :
//******************************************************************************
{
  uint32_t temp1;
  uint16_t temp2;


  if(dvRamDoneFlag == FALSE)
  {
    temp1 = (uint32_t)newHour1 * HOUR_METER_TO_HOUR_FCT;
    temp2 = (newHour2 * HOUR_METER_TO_HOUR_FCT) / 10;

    actualHourMeter = temp1 + temp2;
    actualHourMeterCopy = actualHourMeter;

   // QueueEventDiag(0x4D, FN_HOURMETER, CHANGED, current_user, actualHourMeter/HOUR_METER_TO_HOUR_FCT);
    UpdateEvent(LOC_HOURMETER);

    eeMode = EE_HM_UPDATE;
    eeState = EE_HM_WRITE_INIT;
    dvRamDoneFlag = TRUE;
    hourMeter = 0;
    currentHourMeter = 0;
    
    eeMirror.jobClockLHP[0] = 0; //Reset job clocks so they won't be higher than the hours
    eeMirror.jobClockLHP[1] = 0;
    
    //-------------commented out to allow testing with SA ----------------
    //eeMirror.serviceClockResetTime = actualHourMeter;  
    
    UpdateEEVariables(NOW);
  }

  if(eeMode != EE_IDLE)
  {
    eeServiceEEPROM();
  }
  else
  {
    if(hourMeter <= EE_MAX_HOUR_METERS)
  //  if(hourMeter < EE_MAX_HOUR_METERS)  // was this line changed to above line to fix update issue
    {
      hourMeter++;
      currentHourMeter++;
      eeMode = EE_HM_UPDATE;
      eeState = EE_HM_WRITE_INIT;
    }
    else if (hourMeter == (EE_MAX_HOUR_METERS + 1))
    {
      //Update mirror for error codes
      hourMeter++;
      eeMode  = EE_MIRROR_UPDATE;
      eeState = EE_MIRROR_WRITE_INIT;
    }
    else
    {
      dvTestHourMeter = DV_TEST_DONE;
      dvRamDoneFlag = FALSE;
    }
  }
}

void InitDVTest(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 Mar, 2006
//    Description : Initialize DV Mode
//    Notes       :
//******************************************************************************
{
  dvRamDoneFlag = 0;
  dvTestDone = 0;
  dvTest = DV_TEST_NOT_DONE;
  dvTestHourMeter = DV_TEST_NOT_DONE;

  // Reset recovery mode to prevent error on powerup.
  eeMirror.recoveryMode = FALSE;

  UpdateEEVariables(NOW);

  CommandedAddress_TP_tx.initialize(HWC_CAN0);
}

void DVTest(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 Mar, 2006
//    Description : Performs DV Test items
//    Notes       :
//******************************************************************************
{

  hw_pwm_SetRatio16(FUEL_HOLD_HS_PWM, INACTIVE);
  hw_pwm_SetRatio16(TWO_SPEED_HS_PWM, INACTIVE);

  hw_dout_SetValue(HYD_ENABLE_LS_DOUT, INACTIVE);
  hw_pwm_SetRatio16(HYD_ENABLE_HS_PWM, INACTIVE);
  hw_dout_SetValue(DUMP_VALVE_LS_DOUT, INACTIVE);
  hw_pwm_SetRatio16(DUMP_VALVE_HS_PWM, INACTIVE);

  hw_dout_SetValue(AUX_BASE_LS_DOUT, INACTIVE);
  hw_pwm_SetRatio16(AUX_BASE_HS_PWM, INACTIVE);
  hw_dout_SetValue(AUX_ROD_LS_DOUT, INACTIVE);
  hw_pwm_SetRatio16(AUX_ROD_HS_PWM, INACTIVE);

  hw_dout_SetValue(OFFSET_BASE_LS_DOUT, INACTIVE);
  hw_pwm_SetRatio16(OFFSET_BASE_HS_PWM, INACTIVE);
  hw_dout_SetValue(OFFSET_ROD_LS_DOUT, INACTIVE);
  hw_pwm_SetRatio16(OFFSET_ROD_HS_PWM, INACTIVE);

  hw_dout_SetValue(FUEL_PULL_RLY_DOUT, INACTIVE);
  hw_dout_SetValue(GLOW_PLUG_RLY_DOUT, INACTIVE);
  hw_dout_SetValue(LIGHTS_DOUT, INACTIVE);
  hw_dout_SetValue(BUZZER_DOUT, INACTIVE);
  hw_dout_SetValue(STARTER_RLY_DOUT, INACTIVE);
  hw_dout_SetValue(HYD_EXCHANGE_DOUT, INACTIVE);
  hw_dout_SetValue(HVAC_RLY_DOUT, INACTIVE);
//  hw_dout_SetValue(REGEN_INHIBIT_LAMP_DOUT, INACTIVE);
//  hw_dout_SetValue(FORCED_REGEN_LAMP_DOUT, INACTIVE);

  switch(dvCommand)
  {
    case DV_TEST_CLEAR_SERVICE_CODES:
      if(dvTest == DV_TEST_DONE)
      {
        dvCommand = DV_TEST_NO_COMMAND;
      }
      else
      {
        ClearServiceCodes();
      }
    break;
    
    #ifdef HCS12_BSP_EMU //if M4 compile this
    case DV_TEST_CLEAR_ECU_CODES:
      if(dvTest == DV_TEST_DONE)
      {
        dvCommand = DV_TEST_NO_COMMAND;
      }
      else
      {
        ClearECUCodes();
      }
    break;
    #endif

    case DV_TEST_CLEAR_DIAGNOSTIC_EVENTS:
      if(dvTest == DV_TEST_DONE)
      {
        dvCommand = DV_TEST_NO_COMMAND;
      }
      else
      {
        ClearEvents();
      }
    break;

    case DV_SET_HOUR_METER:
      if(dvTestHourMeter == DV_TEST_DONE)
      {
        dvCommand = DV_TEST_NO_COMMAND;
      }
      else
      {
        SetHourMeter();
      }
    break;

    case DV_CLEAR_SERVICE_CLOCK_EVENTS:
      if(dvTest == DV_TEST_DONE)
      {
        dvCommand = DV_TEST_NO_COMMAND;
      }
      else
      {
        ClearServiceClock();
      }
    break;

    case DV_ENABLE_SERVICE_CLOCK:
      if(dvRamDoneFlag == FALSE)
      {
        if(!(eeMirror.serviceClockLock & SERVICE_CLOCK_LOCK_BIT))
        {
          eeMirror.serviceClockLock = SERVICE_CLOCK_LOCK_BIT;
        }
        else
        {
          eeMirror.serviceClockLock = FALSE;
          eeMirror.serviceClockExpired = FALSE;
        }

        UpdateEEVariables(NOW);

        eeMode = EE_MIRROR_UPDATE;
        eeState = EE_MIRROR_WRITE_INIT;

        dvRamDoneFlag = TRUE;
      }

      if(eeMode != EE_IDLE)
      {
        eeServiceEEPROM();
      }
      else
      {
        // If service clock is turned on, set the hours as well
        if(eeMirror.serviceClockLock & SERVICE_CLOCK_LOCK_BIT)
        {
          dvCommand = DV_SET_SERVICE_CLOCK;
        }
        else
        {
          dvCommand = DV_TEST_NO_COMMAND;
        }
        dvRamDoneFlag = FALSE;

      }
    break;

    case DV_SET_SERVICE_CLOCK:
      if(dvRamDoneFlag == FALSE)
      {
        eeMirror.serviceClockExpired = FALSE;

        if(newHour1 != 0)
        {
          eeMirror.serviceClockLength = (uint32_t)newHour1 * HOUR_METER_TO_HOUR_FCT;
        }

        if(serviceType != 0)
        {
          eeMirror.serviceClockType = (uint8_t)(serviceType);
        }


        eeMirror.serviceClockResetTime = actualHourMeter;

        UpdateEEVariables(NOW);

        QueueServiceDiag((uint16_t)(eeMirror.serviceClockResetTime/HOUR_METER_TO_HOUR_FCT), (uint16_t)(eeMirror.serviceClockLength/HOUR_METER_TO_HOUR_FCT), SERVICE_ANALYZER, (uint8_t)(serviceType), current_user);

        eeMode = EE_MIRROR_UPDATE;                             /* then update the mirror */
        eeState = EE_MIRROR_WRITE_INIT;

        dvRamDoneFlag = TRUE;
      }

      if(eeMode != EE_IDLE)
      {
        eeServiceEEPROM();
      }
      else
      {
        dvCommand = DV_TEST_NO_COMMAND;
        dvRamDoneFlag = FALSE;
      }
    break;

    case DV_PANEL_TEST:

      if(dvRamDoneFlag == FALSE)
      {
        hw_dout_SetValue(SW_PWR_OUT_RLY_DOUT, TRUE);
        // initialize CAN messages
        dvRamDoneFlag = TRUE;

        //ap_CAN_initialize();
      }
      else
      {
        static uint16_t pnlCounter = 0;

        state_InfoSecondary = DISPLAY_DV_MODE;

        if(pnlCounter < 255)
        {
          pnlCounter++;
          gau_ECT = pnlCounter;
          gau_FuelLevel = pnlCounter;
        }
        else
        {
          dvPanelOn = !dvPanelOn;
          pnlCounter = 0;
        }
      }
    break;

    case DV_DOWNGRADE_DDP:
      if(dvRamDoneFlag == FALSE)
      {

        eeMirror.deluxe_G5 = INACTIVE;
        eeMirror.keypad    = INACTIVE;

        //Reset the lockouts
        eeMirror.passwordLock = FALSE;
        UpdateEEVariables(NOW);

        eeMode = EE_MIRROR_UPDATE;
        eeState = EE_MIRROR_WRITE_INIT;

        dvRamDoneFlag = TRUE;
      }

      if(eeMode != EE_IDLE)
      {
        eeServiceEEPROM();
      }
      else
      {
        dvCommand = DV_TEST_NO_COMMAND;
        dvRamDoneFlag = FALSE;
      }
    break;

    case DV_RESTORE_VITALS:
      if(dvRamDoneFlag == FALSE)
      {
        uint8_t * mPtr;
        uint8_t checksum;

        for(uint8_t i=0; i <= MAX_NUMBER_VITALS; i++)
        {
          eeMirror.vitals.vital[i].warning = MXGTW_VITAL_DEFAULT_WARNING[i];
          eeMirror.vitals.vital[i].shutdown = MXGTW_VITAL_DEFAULT_SHUTDOWN[i];
          eeMirror.vitals.vital[i].icon = MXGTW_VITAL_DEFAULT_ICON[i];
          eeMirror.vitals.vital[i].units = MXGTW_VITAL_DEFAULT_UNITS[i];
        }

        eeMirror.vitals.reserved[0] = 0xFF;
        eeMirror.vitals.reserved[1] = 0xFF;
        eeMirror.vitals.reserved[2] = 0xFF;

        mPtr = (uint8_t *) &eeMirror.vitals;
        checksum = 0;
        while(mPtr < (uint8_t *) &eeMirror.vitals.checksum)
        {
          checksum += *mPtr;
          mPtr++;
        }

        eeMirror.vitals.checksum = ~checksum + 1;

        eeMode = EE_MIRROR_UPDATE;
        eeState = EE_MIRROR_WRITE_INIT;

        dvRamDoneFlag = TRUE;

      }

      if(eeMode != EE_IDLE)
      {
        eeServiceEEPROM();
      }
      else
      {
        dvCommand = DV_TEST_NO_COMMAND;
        dvRamDoneFlag = FALSE;
      }
    break;

    case DV_RESET_SEATBAR_TEST:
      if(dvRamDoneFlag == FALSE)
      {
        eeMirror.consoleTest |= 0x18;

        UpdateEEVariables(NOW);

        eeMode = EE_MIRROR_UPDATE;
        eeState = EE_MIRROR_WRITE_INIT;

        dvRamDoneFlag = TRUE;
      }

      if(eeMode != EE_IDLE)
      {
        eeServiceEEPROM();
      }
      else
      {
        dvCommand = DV_TEST_NO_COMMAND;
        dvRamDoneFlag = FALSE;
      }
    break;

    case DV_TOGGLE_ENG_DATA:
      if(dvRamDoneFlag == FALSE)
      {
        if(eeMirror.EngData == NON_FUNCTIONAL)
        {
          eeMirror.EngData = 1;
        }
        else
        {
          eeMirror.EngData = NON_FUNCTIONAL;
        }

        UpdateEEVariables(NOW);

        eeMode = EE_MIRROR_UPDATE;
        eeState = EE_MIRROR_WRITE_INIT;

        dvRamDoneFlag = TRUE;
      }

      if(eeMode != EE_IDLE)
      {
        eeServiceEEPROM();
      }
      else
      {
        dvCommand = DV_TEST_NO_COMMAND;
        dvRamDoneFlag = FALSE;
      }
    break;

    default:
      dvCommand = DV_TEST_NO_COMMAND;
    break;
  }
}
