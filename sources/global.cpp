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
* First written on 17 December, 2006 by Spencer Mindeman
*
* Module Description:
* Global Variables.
***************************************************************/

#include "nvm_ecuid.h"
#include "rtwtypes.h"
#include "global.h"


uint8_t powerUpTimer;
uint8_t state_DeluxeRun;
uint8_t newlyBootedDDP;
uint8_t pwScreenShown;

//uint16_t sw_Version;

uint8_t  ddpServiceScreenFlag;
uint8_t flag_SendDeluxeWarning;

uint8_t downgradedFromDDP;
uint8_t newPasswordNumber;
uint8_t newJobClockNumber;
uint8_t newUserNameNumber;
uint8_t newPasswordVerification;
uint8_t newJobClockVerification;
uint8_t newUserNameVerification;
uint8_t ddpPasswordScreenChanged;
uint8_t obtainedCurrentUser;

uint8_t flag_ActiveWarning;
uint8_t flag_StdActiveWarn;

uint8_t flag_RxRPMMax;
uint8_t flag_RxRPMMin;
uint8_t flag_RxECUHours;
uint8_t flag_RxDPFHours;

uint8_t ecu_BarPressure;
uint16_t ecu_AirInletTemp;
uint32_t ecu_Hours;

uint32_t can_FuelConsumption;
uint32_t start_FuelConsumption;
uint16_t current_FuelConsumption;

uint16_t pressure_TorqueLimiter;

bool enable_ECUDM1;
uint8_t ecu_SOFT[ECU_SOFT_LENGTH];

uint8_t user_KeylessEntry;


//******************************************************************************
// MODEL GLOBAL VARIABLES
//******************************************************************************
uint8_T pwd_Keyless[5];         // '<S594>/Panel_Lock'
uint16_T ain_Console;           // '<Root>/ain_Console'
uint16_T ain_SensorSupply1;     // '<Root>/ain_SensorSupply1'
uint16_T ain_SensorSupply2;     // '<Root>/ain_SensorSupply2'
uint16_T ain_OffsetPot;         // '<Root>/ain_OffsetPot'
uint16_T ain_VBattery;          // '<Root>/ain_VBattery'
uint16_T ain_SwitchedPower;     // '<Root>/ain_SwitchedPower'
uint16_T ain_ECT;               // '<Root>/ain_ECT'
uint16_T ain_FuelLevel;         // '<Root>/ain_FuelLevel'
uint16_T ain_AuxPot;            // '<Root>/ain_AuxPot'
uint16_T ain_PrecisionReference;// '<Root>/ain_PrecisionReference'
uint16_T ain_LoadMoment;        // '<Root>/ain_LoadMoment'
uint16_T ain_ThrottlePrimary;   // '<Root>/ain_ThrottlePrimary'
uint16_T ain_Aux2FlowControl;   // '<Root>/ain_Aux2FlowControl'
uint8_T din_AirFilter;          // '<Root>/din_AirFilter'
uint8_T din_HCFilter1;          // '<Root>/din_HCFilter1'
uint8_T din_ACOn;               // '<Root>/din_ACOn'
uint8_T din_TwoSpeedSwitch;     // '<Root>/din_TwoSpeedSwitch'
boolean_T dfbk_StarterOutput;   // '<Root>/dfbk_StarterOutput'
uint8_T din_RunEnter;           // '<Root>/din_RunEnter'
uint8_T din_RemoteKey;          // '<Root>/din_RemoteKey'
uint8_T din_EngineStart;        // '<Root>/din_EngineStart'
boolean_T din_SwPowerRelay;     // '<Root>/din_SwPowerRelay'
boolean_T dfbk_SwPowerOutput;   // '<Root>/dfbk_SwPowerOutput'
boolean_T din_GlowPlugRelay;    // '<Root>/din_GlowPlugRelay'
boolean_T dfbk_GlowPlugOutput;  // '<Root>/dfbk_GlowPlugOutput'
boolean_T din_FuelPriRelay;     // '<Root>/din_FuelPriRelay'
boolean_T dfbk_FuelPriOutput;   // '<Root>/dfbk_FuelPriOutput'
boolean_T din_StarterRelay;     // '<Root>/din_StarterRelay'
uint8_T dfbk_Buzzer;            // '<Root>/dfbk_Buzzer'
boolean_T dfbk_LightsOutput;    // '<Root>/dfbk_LightsOutput'
boolean_T dfbk_HydExchange;     // '<Root>/dfbk_HydExchange'
boolean_T din_HVACRelay;        // '<Root>/din_HVACRelay'
boolean_T dfbk_HVACOutput;      // '<Root>/dfbk_HVACOutput'
uint8_T din_Detent;             // '<Root>/din_Detent'
boolean_T din_LightsRelay;      // '<Root>/din_LightsRelay'
boolean_T din_SecondAuxSw;      // '<Root>/din_SecondAuxSw'
boolean_T din_PBValveRelay;     // '<Root>/din_PBValveRelay'
boolean_T dfbk_PBValveOutput;   // '<Root>/dfbk_PBValveOutput'
boolean_T din_OWDEnableSw;      // '<Root>/din_OWDInhibitSw'
boolean_T din_LeftHandleSelectSw;// '<Root>/din_LeftHandleSelectSw'
uint16_T adin_HOT;              // '<Root>/adin_HOT'
uint16_T adin_EOP;              // '<Root>/adin_EOP'
uint16_T adin_LoadSense;        // '<Root>/adin_LoadSense'
uint16_T adin_TravelPressureSwitch;// '<Root>/adin_TravelPressureSwitch'
uint16_T afbk_HydEnable;        // '<Root>/afbk_HydEnable'
uint16_T afbk_OffsetRod;        // '<Root>/afbk_OffsetRod'
uint16_T afbk_AuxRod;           // '<Root>/afbk_AuxRod'
uint16_T afbk_FuelSec;          // '<Root>/afbk_FuelSec'
uint16_T afbk_TwoSpeed;         // '<Root>/afbk_TwoSpeed'
uint16_T afbk_TwoSpeedSecondary;// '<Root>/afbk_TwoSpeedSecondary'
uint16_T afbk_OffsetBase;       // '<Root>/afbk_OffsetBase'
uint16_T afbk_AuxBase;          // '<Root>/afbk_AuxBase'
uint16_T afbk_DumpValve;        // '<Root>/afbk_DumpValve'
uint16_T afbk_HydBypass;        // '<Root>/afbk_HydBypass'
uint16_T afbk_Diverter;        // '<Root>/afbk_SecondAux'
uint16_T ifbk_HydEnable;        // '<Root>/ifbk_HydEnable'
uint16_T ifbk_OffsetRod;        // '<Root>/ifbk_OffsetRod'
uint16_T ifbk_AuxRod;           // '<Root>/ifbk_AuxRod'
uint16_T ifbk_OffsetBase;       // '<Root>/ifbk_OffsetBase'
uint16_T ifbk_AuxBase;          // '<Root>/ifbk_AuxBase'
uint16_T ifbk_DumpValve;        // '<Root>/ifbk_DumpValve'
uint16_T ifbk_HydBypass;        // '<Root>/ifbk_HydBypass'
uint16_T ifbk_Diverter;        // '<Root>/ifbk_SecondAux'
uint8_T msg_PanelButtonState[8];// '<Root>/msg_PanelButtonState'
uint16_T msgAge_StdDisplay;     // '<Root>/msgAge_StdDisplay'
uint16_T msgAge_Secondary;      // '<Root>/msgAge_Secondary'
uint8_T can_AlternateAuxMode;   // '<Root>/can_AlternateAuxMode'
uint8_T can_OffsetPot;          // '<Root>/can_OffsetPot'
uint8_T btn_SnakeEyes;          // '<Root>/btn_SnakeEyes'
uint16_T delay_DepthBeep;       // '<Root>/delay_DepthBeep'
uint8_T state_DepthBeep;        // '<Root>/state_DepthBeep'
boolean_T can_OffsetSelectSw;   // '<Root>/can_OffsetSelectSw'
boolean_T can_RightHandleSelectSw;// '<Root>/can_RightHandleSelectSw'
uint16_T msgAge_Throttle;       // '<Root>/msgAge_Throttle'
uint16_T fdbk_CANThrottle;      // '<Root>/fdbk_CANThrottle'
uint8_T can_ST_EngineStart;     // '<Root>/can_ST_EngineStart'
uint8_T state_ST_CAN;           // '<Root>/state_ST_CAN'
uint8_T can_ST_EStop;           // '<Root>/can_ST_EStop'
uint8_T cmd_AuxEnable_ST;       // '<Root>/cmd_AuxEnable_ST'
uint8_T ecu_EOP;                // '<Root>/ecu_EOP'
uint16_T ecu_ECT;               // '<Root>/ecu_ECT'
uint16_T ecu_EngineSpeed;       // '<Root>/ecu_EngineSpeed'
uint8_T state_ecuECT;           // '<Root>/state_ecuECT'
uint8_T state_ecuEOP;           // '<Root>/state_ecuEOP'
uint8_T ecu_GlowPlug;           // '<Root>/ecu_GlowPlug'
uint16_T msgAge_ECU;            // '<Root>/msgAge_ECU'
uint8_T ecu_EngineStarterMode;  // '<Root>/ecu_EngineStarterMode'
uint16_T ecu_isocMaxRPM;        // '<Root>/ecu_isocMaxRPM'
uint16_T ecu_isocMinRPM;        // '<Root>/ecu_isocMinRPM'
int8_T ecu_PercentTorque;       // '<Root>/ecu_PercentTorque'
uint16_T lamp_Engine;           // '<Root>/lamp_Engine'
uint8_T ecu_HP;                 // '<Root>/ecu_HP'
uint16_T can_FuelTemp;          // '<Root>/can_FuelTemp'
uint16_T ecu_EOT;               // '<Root>/ecu_EOT'
uint8_T state_DeluxeG5;         // '<Root>/state_DeluxeG5'
uint8_T flow_Aux1Percent;       // '<Root>/flow_Aux1Percent'
uint8_T flow_Aux2Percent;       // '<Root>/flow_Aux2Percent'
uint8_T flow_Aux4Percent;       // '<Root>/flow_Aux4Percent'
uint8_T flow_OffsetPercent;     // '<Root>/flow_OffsetPercent'
uint8_T msg_DeluxeButtons[5];   // '<Root>/msg_DeluxeButtons'
uint8_T can_Keypad[3];          // '<Root>/can_Keypad'
uint8_T state_KeylessPanel;     // '<Root>/state_KeylessPanel'
uint8_T msg_BJM2Left[8];        // '<Root>/msg_BJM2Left'
uint16_T msgAge_BJM2Left;       // '<Root>/msgAge_BJM2Left'
uint8_T msg_BJM2Right[8];       // '<Root>/msg_BJM2Right'
uint16_T msgAge_BJM2Right;      // '<Root>/msgAge_BJM2Right'
uint8_T can_ACD_EngineStart;    // '<Root>/can_ACD_EngineStart'
uint8_T state_ACD_CAN;          // '<Root>/state_ACD_CAN'
uint8_T can_ACD_EStop;          // '<Root>/can_ACD_EStop'
uint8_T can_ACD_AuxCommand;     // '<Root>/can_ACD_AuxCommand'
uint8_T cmd_AuxEnable_ACD;      // '<Root>/cmd_AuxEnable_ACD'
uint16_T msgAge_DeluxeG55;      // '<Root>/msgAge_DeluxeG55'
uint8_T dlx_G55_AutoIdle;       // '<Root>/btn_dlx_G55_AutoIdle'
uint8_T dlx_G55_EcoMode;        // '<Root>/btn_dlx_G55_EcoMode'
uint8_T dlx_G55_AutoIdleTime;   // '<Root>/dlx_G55_AutoIdleTime'
uint8_T dlx_G55_AuxReleaseStatus;// '<Root>/dlx_G55_AuxReleaseStatus'
uint8_T auth_DeluxeG55;         // '<Root>/auth_DeluxeG55'
uint8_T state_DeluxeG55;        // '<Root>/state_DeluxeG55'
uint16_T msgAge_JogShuttle;     // '<Root>/msgAge_JogShuttle'
uint8_T btn_JogShuttleAux;      // '<Root>/btn_JogShuttleAux'
uint8_T btn_JogShuttleLights;   // '<Root>/btn_JogShuttleLights'
uint8_T can_KeylessEntry[3];    // '<Root>/can_KeylessEntry'
uint16_T msgAge_KeylessEntry;   // '<Root>/msgAge_KeylessEntry'
uint32_T freq_EngineSpeed;      // '<Root>/freq_EngineSpeed'
uint8_T ee_OwnerPassword[5];    // '<Root>/ee_OwnerPassword'
uint8_T ee_MasterPassword[5];   // '<Root>/ee_MasterPassword'
uint8_T state_ConstantData;     // '<Root>/state_ConstantData'
uint8_T state_TwoSpeedLock;     // '<Root>/state_TwoSpeedLock'
uint8_T ddp_MachineLock;        // '<Root>/ddp_MachineLock'
uint8_T state_ConsoleTest;      // '<Root>/state_ConsoleTest'
uint8_T state_ServiceClock;     // '<Root>/state_ServiceClock'
uint8_T state_System;           // '<Root>/state_System'
boolean_T flag_InitEERead;      // '<Root>/flag_InitEERead'
boolean_T downgradedG5Deluxe;   // '<Root>/downgradedG5Deluxe'
uint8_T scrn_DeluxePwdFail;     // '<Root>/scrn_DeluxePwdFail'
uint32_T actualHourMeter;       // '<Root>/actualHourMeter'
uint8_T dv_TurboPrime;          // '<Root>/dv_TurboPrime'
uint8_T state_KeylessEntryPassword;// '<Root>/state_KeylessEntryPassword' 
uint8_T state_KeylessEntryLock; // '<Root>/state_KeylessEntryLock'
uint8_T ee_User1Password[5];    // '<Root>/ee_User1Password'
uint8_T ee_User2Password[5];    // '<Root>/ee_User2Password'
uint8_T state_Inverter;         // '<Root>/inverterStatus'

//uint8_T ee_KeylessEntryPasswords[220];// '<Root>/ee_KeylessEntryPasswords'



