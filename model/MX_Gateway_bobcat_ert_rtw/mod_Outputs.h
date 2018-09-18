//
//  Copyright (c) 2009 Bobcat Company as an unpublished work.
//  All Rights Reserved.
//
//  The information contained herein is confidential property of Bobcat Company.
//  The use, copying, transfer or disclosure of such information is prohibited except
//  by express written agreement with Bobcat Company.
//
//  Code Generated by Simulink Real-Time Workshop
//
//  Simulink model                       : MX_Gateway


#ifndef RTW_HEADER_mod_Outputs_h_
#define RTW_HEADER_mod_Outputs_h_
#ifndef MX_Gateway_COMMON_INCLUDES_
# define MX_Gateway_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 // MX_Gateway_COMMON_INCLUDES_

#include "MX_Gateway_types.h"

// Child system includes
#include "mod_Library.h"

// Block signals for system '<S428>/dout_chk'
typedef struct {
  uint8_T state;                       // '<S437>/Fault monitor'
} rtB_dout_chk_MX_Gateway;

// Block states (auto storage) for system '<S428>/dout_chk'
typedef struct {
  struct {
    uint_T is_diagnostics:2;           // '<S437>/Fault monitor'
    uint_T is_active_c60_MX_Library:1; // '<S437>/Fault monitor'
  } bitsForTID1;

  uint16_T db_cnt;                     // '<S437>/Fault monitor'
  uint16_T db_limit;                   // '<S437>/Fault monitor'
  uint8_T db_state;                    // '<S437>/Fault monitor'
  boolean_T dout_chk_MODE;             // '<S428>/dout_chk'
} rtDW_dout_chk_MX_Gateway;

extern void MX_Gateway_dout_chk_Init(uint8_T *rty_state, rtB_dout_chk_MX_Gateway
  *localB, rtDW_dout_chk_MX_Gateway *localDW);
extern void MX_Gateway_dout_chk_Reset(rtB_dout_chk_MX_Gateway *localB,
  rtDW_dout_chk_MX_Gateway *localDW);
extern void MX_Gateway_dout_chk_Disable(uint8_T *rty_state,
  rtDW_dout_chk_MX_Gateway *localDW);
extern void MX_Gateway_dout_chk(boolean_T rtu_Enable, boolean_T rtu_cmd,
  boolean_T rtu_fbk, uint8_T *rty_state, rtB_dout_chk_MX_Gateway *localB,
  rtDW_dout_chk_MX_Gateway *localDW, uint16_T rtp_ERR_OFF_DB_CNT, uint16_T
  rtp_ERR_ON_DB_CNT);
extern void MX_Gateway_Aux_Hydraulics_Init(void);
extern void MX_Gateway_Aux_Hydraulics(void);
extern void MX_Gateway_Buzzer_Init(void);
extern void MX_Gateway_Buzzer(void);
extern void MX_Gateway_Diverter_Init(void);
extern void MX_Gateway_Diverter(void);
extern void MX_Gateway_Dump_Valve_Init(void);
extern void MX_Gateway_Dump_Valve(void);
extern void MX_Gate_Fuel_Primary_Relay_Init(void);
extern void MX_Gateway_Fuel_Primary_Relay(void);
extern void MX_Gateway_HVAC_Relay_Init(void);
extern void MX_Gateway_HVAC_Relay(void);
extern void MX_Gateway_FuelPri_HVAC_Init(void);
extern void MX_Gateway_FuelPri_HVAC(void);
extern void MX_Gateway_FuelSec_ECUHold_Init(void);
extern void MX_Gateway_FuelSec_ECUHold(void);
extern void MX_G_Fuel_Resolution_Timer_Init(void);
extern void MX_Gatewa_Fuel_Resolution_Timer(void);
extern void MX_Gateway_GlowPlug_Init(void);
extern void MX_Gateway_GlowPlug(void);
extern void MX_Gateway_Hyd_Bypass_Init(void);
extern void MX_Gateway_Hyd_Bypass(void);
extern void MX_Gateway_Hyd_Enable_Init(void);
extern void MX_Gateway_Hyd_Enable(void);
extern void MX_Gate_Hydraulic_Exchange_Init(void);
extern void MX_Gateway_Hydraulic_Exchange(void);
extern void MX_Gateway_Lights_Init(void);
extern void MX_Gateway_Lights(void);
extern void MX_Gateway_Offset_Init(void);
extern void MX_Gateway_Offset(void);
extern void MX_Gateway_PB_Valve_Init(void);
extern void MX_Gateway_PB_Valve(void);
extern void MX_Gateway_Starter_Init(void);
extern void MX_Gateway_Starter(void);
extern void MX_Gateway_SwitchedPower_Init(void);
extern void MX_Gateway_SwitchedPower(void);
extern void MX_Gateway_Two_Speed_Init(void);
extern void MX_Gateway_Two_Speed(void);

#endif                                 // RTW_HEADER_mod_Outputs_h_

//
//  [EOF]

