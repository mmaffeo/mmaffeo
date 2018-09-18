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
//  Simulink model                       : MX_Gtwy_Control


#ifndef RTW_HEADER_mod_Library_h_
#define RTW_HEADER_mod_Library_h_
#ifndef MX_Gtwy_Control_COMMON_INCLUDES_
# define MX_Gtwy_Control_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 // MX_Gtwy_Control_COMMON_INCLUDES_

#include "MX_Gtwy_Control_types.h"

// Block states (auto storage) for system '<S74>/LP_Filter'
typedef struct {
  int16_T FixPtUnitDelay1_DSTATE;      // '<S149>/FixPt Unit Delay1'
  uint8_T FixPtUnitDelay2_DSTATE;      // '<S149>/FixPt Unit Delay2'
} rtDW_LP_Filter_MX_Gtwy_Control;

// Block states (auto storage) for system '<S151>/LP_Filter'
typedef struct {
  int16_T FixPtUnitDelay1_DSTATE;      // '<S158>/FixPt Unit Delay1'
  uint8_T FixPtUnitDelay2_DSTATE;      // '<S158>/FixPt Unit Delay2'
} rtDW_LP_Filter_MX_Gtwy_Con_ntkm;

// Block states (auto storage) for system '<S151>/LP_Filter_Adj_Gain'
typedef struct {
  struct {
    uint_T is_c1_MX_Library:2;         // '<S155>/LP_Filter_Adj_Gain'
    uint_T is_active_c1_MX_Library:1;  // '<S155>/LP_Filter_Adj_Gain'
  } bitsForTID1;
} rtDW_LP_Filter_Adj_Gain_MX_Gtwy;

// Block states (auto storage) for system '<S151>/Remove_OOR_Levels'
typedef struct {
  uint16_T fltValue_old;               // '<S157>/RemoveOORLevels'
} rtDW_Remove_OOR_Levels_MX_Gtwy_;

// Block states (auto storage) for system '<S83>/LP_Filter_Adj_Gain'
typedef struct {
  struct {
    uint_T is_c1_MX_Library:2;         // '<S201>/LP_Filter_Adj_Gain'
    uint_T is_active_c1_MX_Library:1;  // '<S201>/LP_Filter_Adj_Gain'
  } bitsForTID1;
} rtDW_LP_Filter_Adj_Gain_MX_j5ng;

// Block states (auto storage) for system '<S217>/LP_Filter_Adj_System'
typedef struct {
  struct {
    uint_T is_c2_MX_Library:2;         // '<S219>/LP_Fitler_Adj_Gain'
    uint_T is_active_c2_MX_Library:1;  // '<S219>/LP_Fitler_Adj_Gain'
  } bitsForTID1;
} rtDW_LP_Filter_Adj_System_MX_Gt;

// Block signals for system '<S329>/control_loop'
typedef struct {
  int16_T DiscreteTimeIntegrator;      // '<S337>/Discrete-Time Integrator'
} rtB_control_loop_MX_Gtwy_Contro;

// Block states (auto storage) for system '<S329>/control_loop'
typedef struct {
  int16_T DiscreteTimeIntegrator_DSTATE;// '<S337>/Discrete-Time Integrator'
  boolean_T control_loop_MODE;         // '<S329>/control_loop'
} rtDW_control_loop_MX_Gtwy_Contr;

// Block states (auto storage) for system '<S329>/hc_pair_OpenLoop'
typedef struct {
  struct {
    uint_T is_ACTIVE:3;                // '<S339>/Fault monitor'
    uint_T is_OUTPUT:3;                // '<S339>/Fault monitor'
    uint_T is_OC_STG:2;                // '<S339>/Fault monitor'
    uint_T is_OPEN_CIRCUIT:2;          // '<S339>/Fault monitor'
    uint_T is_SHORT_TO_GROUND:2;       // '<S339>/Fault monitor'
    uint_T is_SHORT_TO_BATTERY:2;      // '<S339>/Fault monitor'
    uint_T is_FAULT:2;                 // '<S339>/Fault monitor'
    uint_T is_OVERCURRENT:2;           // '<S339>/Fault monitor'
    uint_T is_active_c63_MX_Library:1; // '<S339>/Fault monitor'
  } bitsForTID0;

  uint16_T db_cnt;                     // '<S339>/Fault monitor'
  uint16_T db_cnt_oc;                  // '<S339>/Fault monitor'
  uint8_T temporalCounter_i1;          // '<S339>/Fault monitor'
} rtDW_hc_pair_OpenLoop_MX_Gtwy_C;

// Block signals for system '<S306>/hc_pair_ClosedLoop_v5'
typedef struct {
  uint16_T DataTypeConversion;         // '<S337>/Data Type Conversion'
  rtB_control_loop_MX_Gtwy_Contro control_loop;// '<S329>/control_loop'
} rtB_hc_pair_ClosedLoop_v5_MX_Gt;

// Block states (auto storage) for system '<S306>/hc_pair_ClosedLoop_v5'
typedef struct {
  uint8_T UnitDelay1_DSTATE;           // '<S329>/Unit Delay1'
  boolean_T UnitDelay_DSTATE;          // '<S329>/Unit Delay'
  rtDW_hc_pair_OpenLoop_MX_Gtwy_C hc_pair_OpenLoop;// '<S329>/hc_pair_OpenLoop'
  rtDW_control_loop_MX_Gtwy_Contr control_loop;// '<S329>/control_loop'
} rtDW_hc_pair_ClosedLoop_v5_MX_G;

// Block states (auto storage) for system '<S306>/oc_stg_detection'
typedef struct {
  struct {
    uint_T is_c5_MX_Library:3;         // '<S330>/oc_operation_detection'
    uint_T is_active_c5_MX_Library:1;  // '<S330>/oc_operation_detection'
  } bitsForTID0;

  uint16_T debounceCount;              // '<S330>/oc_operation_detection'
  uint8_T temporalCounter_i1;          // '<S330>/oc_operation_detection'
} rtDW_oc_stg_detection_MX_Gtwy_C;

// Block signals for system '<S299>/hc_pair_control'
typedef struct {
  int32_T Output;                      // '<S332>/LP_Filter_Adj_Gain'
  uint16_T icmd_Out;                   // '<S306>/control'
  uint8_T diag_state_out;              // '<S330>/oc_operation_detection'
  uint8_T diag_state;                  // '<S339>/Fault monitor'
  uint8_T oc_state;                    // '<S339>/Fault monitor'
  boolean_T enable_LoSide;             // '<S306>/control'
  rtB_hc_pair_ClosedLoop_v5_MX_Gt hc_pair_ClosedLoop_v5;// '<S306>/hc_pair_ClosedLoop_v5' 
} rtB_output_pair_ClosedLoop_MX_G;

// Block states (auto storage) for system '<S299>/hc_pair_control'
typedef struct {
  struct {
    uint_T is_c39_MX_Library:2;        // '<S306>/control'
    uint_T is_STGOFF_DIAG_ACTIVE:2;    // '<S306>/control'
    uint_T is_STGOFF_DIAG_INACTIVE:2;  // '<S306>/control'
    uint_T is_DIAG_CHECK:2;            // '<S306>/control'
    uint_T is_FUNCTIONAL:2;            // '<S306>/control'
    uint_T is_active_c39_MX_Library:1; // '<S306>/control'
  } bitsForTID0;

  uint16_T debounceCount;              // '<S306>/control'
  uint8_T UnitDelay1_DSTATE;           // '<S306>/Unit Delay1'
  uint8_T UnitDelay4_DSTATE;           // '<S306>/Unit Delay4'
  rtDW_oc_stg_detection_MX_Gtwy_C oc_stg_detection;// '<S306>/oc_stg_detection'
  rtDW_hc_pair_ClosedLoop_v5_MX_G hc_pair_ClosedLoop_v5;// '<S306>/hc_pair_ClosedLoop_v5' 
  rtDW_LP_Filter_Adj_Gain_MX_Gtwy LP_Filter_Adj_Gain;// '<S327>/LP_Filter_Adj_Gain' 
} rtDW_output_pair_ClosedLoop_MX_;

// Block signals for system '<S364>/output_pair_open_loop'
typedef struct {
  int32_T Output;                      // '<S377>/LP_Filter_Adj_Gain'
  uint8_T diag_state_out;              // '<S375>/oc_operation_detection'
  uint8_T diag_state;                  // '<S379>/Fault monitor'
  uint8_T oc_state;                    // '<S379>/Fault monitor'
  boolean_T enable_LoSide;             // '<S367>/control'
} rtB_output_pair_OpenLoop_MX_Gtw;

// Block states (auto storage) for system '<S364>/output_pair_open_loop'
typedef struct {
  struct {
    uint_T is_c51_MX_Library:2;        // '<S367>/control'
    uint_T is_STGOFF_DIAG_ACTIVE:2;    // '<S367>/control'
    uint_T is_STGOFF_DIAG_INACTIVE:2;  // '<S367>/control'
    uint_T is_DIAG_CHECK:2;            // '<S367>/control'
    uint_T is_FUNCTIONAL:2;            // '<S367>/control'
    uint_T is_active_c51_MX_Library:1; // '<S367>/control'
  } bitsForTID0;

  uint16_T debounceCount;              // '<S367>/control'
  uint8_T UnitDelay2_DSTATE;           // '<S367>/Unit Delay2'
  uint8_T UnitDelay3_DSTATE;           // '<S367>/Unit Delay3'
  rtDW_oc_stg_detection_MX_Gtwy_C oc_stg_detection;// '<S367>/oc_stg_detection'
  rtDW_hc_pair_OpenLoop_MX_Gtwy_C hc_pair_OpenLoop;// '<S367>/hc_pair_OpenLoop'
  rtDW_LP_Filter_Adj_Gain_MX_Gtwy LP_Filter_Adj_Gain;// '<S372>/LP_Filter_Adj_Gain' 
} rtDW_output_pair_OpenLoop_MX_Gt;

// Block signals for system '<S405>/relay_oc'
typedef struct {
  uint8_T state_Relay;                 // '<S410>/relay_error_state'
  uint8_T state_Output;                // '<S410>/relay_error_state'
} rtB_relay_oc_MX_Gtwy_Control;

// Block states (auto storage) for system '<S405>/relay_oc'
typedef struct {
  struct {
    uint_T is_OUTPUT:3;                // '<S410>/relay_error_state'
    uint_T is_NORMAL:2;                // '<S410>/relay_error_state'
    uint_T is_ERROR_OFF:2;             // '<S410>/relay_error_state'
    uint_T is_ERROR_ON:2;              // '<S410>/relay_error_state'
    uint_T is_STATE_OUTPUT:2;          // '<S410>/relay_error_state'
    uint_T is_NORMAL_food:2;           // '<S410>/relay_error_state'
    uint_T is_ERROR_ON_lmya:2;         // '<S410>/relay_error_state'
    uint_T is_ERROR_OFF_cild:2;        // '<S410>/relay_error_state'
    uint_T is_OPEN_CIRCUIT:2;          // '<S410>/relay_error_state'
    uint_T is_FAILURE:2;               // '<S410>/relay_error_state'
    uint_T is_STATE_RELAY:2;           // '<S410>/relay_error_state'
    uint_T is_RELAY:2;                 // '<S410>/relay_error_state'
    uint_T is_active_c3_MX_Library:1;  // '<S410>/relay_error_state'
  } bitsForTID0;

  uint16_T debounceOutput;             // '<S410>/relay_error_state'
  uint16_T debounceRelay;              // '<S410>/relay_error_state'
  boolean_T relay_oc_MODE;             // '<S405>/relay_oc'
} rtDW_relay_oc_MX_Gtwy_Control;

// Block signals for system '<S286>/hc_hsd'
typedef struct {
  uint8_T state;                       // '<S421>/Fault monitor'
} rtB_hc_hsd_MX_Gtwy_Control;

// Block states (auto storage) for system '<S286>/hc_hsd'
typedef struct {
  struct {
    uint_T is_c4_MX_Library:3;         // '<S421>/Fault monitor'
    uint_T is_OPEN_CIRCUIT:2;          // '<S421>/Fault monitor'
    uint_T is_SHORT_TO_GROUND:2;       // '<S421>/Fault monitor'
    uint_T is_SHORT_TO_BATTERY:2;      // '<S421>/Fault monitor'
    uint_T is_active_c4_MX_Library:1;  // '<S421>/Fault monitor'
  } bitsForTID0;

  uint16_T db_cnt;                     // '<S421>/Fault monitor'
  boolean_T hc_hsd_MODE;               // '<S286>/hc_hsd'
} rtDW_hc_hsd_MX_Gtwy_Control;

// Block signals for system '<S561>/hc_Output'
typedef struct {
  uint16_T duty_Output;                // '<S565>/control'
  uint8_T state;                       // '<S572>/Fault monitor'
  rtB_hc_hsd_MX_Gtwy_Control hc_hsd;   // '<S565>/hc_hsd'
} rtB_output_single_OpenLoop_MX_G;

// Block states (auto storage) for system '<S561>/hc_Output'
typedef struct {
  struct {
    uint_T is_c41_MX_Library:2;        // '<S565>/control'
    uint_T is_FUNCTIONAL:2;            // '<S565>/control'
    uint_T is_active_c41_MX_Library:1; // '<S565>/control'
  } bitsForTID0;

  uint8_T UnitDelay_DSTATE;            // '<S565>/Unit Delay'
  rtDW_hc_hsd_MX_Gtwy_Control hc_hsd;  // '<S565>/hc_hsd'
} rtDW_output_single_OpenLoop_MX_;

extern void MX_Gtwy_Control_ErrorCode(uint8_T rtu_failure, uint16_T *rty_ecode,
  uint16_T rtp_FUNCTION);
extern void MX_Gtwy_Control_LP_Filter_Init(rtDW_LP_Filter_MX_Gtwy_Control
  *localDW);
extern void MX_Gtwy_Control_LP_Filter(int16_T rtu_In, int16_T *rty_Out,
  rtDW_LP_Filter_MX_Gtwy_Control *localDW);
extern void MX_Gtwy_C_Ratiometric_Converter(uint16_T rtu_SensorInput, uint16_T
  rtu_SensorSupply, uint16_T *rty_Ratiometric, uint16_T rtp_multiplier);
extern void MX_Gtwy_Con_LP_Filter_as2q_Init(rtDW_LP_Filter_MX_Gtwy_Con_ntkm
  *localDW);
extern void MX_Gtwy_Co_LP_Filter_j43b_Reset(rtDW_LP_Filter_MX_Gtwy_Con_ntkm
  *localDW);
extern void MX_Gtwy_Control_LP_Filter_dijo(uint16_T rtu_In, int16_T *rty_Out,
  rtDW_LP_Filter_MX_Gtwy_Con_ntkm *localDW);
extern void MX_Gtwy_LP_Filter_Adj_Gain_Init(int32_T *rty_Output,
  rtDW_LP_Filter_Adj_Gain_MX_Gtwy *localDW);
extern void MX_Gtw_LP_Filter_Adj_Gain_Reset(int32_T *rty_Output,
  rtDW_LP_Filter_Adj_Gain_MX_Gtwy *localDW);
extern void MX_Gtwy_Cont_LP_Filter_Adj_Gain(uint8_T rtu_Gain, int16_T rtu_Input,
  int32_T *rty_Output, rtDW_LP_Filter_Adj_Gain_MX_Gtwy *localDW);
extern void MX_Gtwy__Remove_OOR_Levels_Init(uint16_T *rty_fltValue_out,
  rtDW_Remove_OOR_Levels_MX_Gtwy_ *localDW);
extern void MX_Gtwy_Remove_OOR_Levels_Reset(uint16_T *rty_fltValue_out,
  rtDW_Remove_OOR_Levels_MX_Gtwy_ *localDW);
extern void MX_Gtwy_Contr_Remove_OOR_Levels(uint16_T rtu_fltValue_in, uint16_T
  *rty_fltValue_out, rtDW_Remove_OOR_Levels_MX_Gtwy_ *localDW, uint16_T
  rtp_OORH_LEVEL, uint16_T rtp_OORL_LEVEL);
extern void MX_LP_Filter_Adj_Gain_gfud_Init(int32_T *rty_Output,
  rtDW_LP_Filter_Adj_Gain_MX_j5ng *localDW);
extern void MX_Gtwy_LP_Filter_Adj_Gain_hwrc(uint8_T rtu_Gain, int16_T rtu_Input,
  int32_T *rty_Output, rtDW_LP_Filter_Adj_Gain_MX_j5ng *localDW);
extern void MX_Gt_LP_Filter_Adj_System_Init(int32_T *rty_Output,
  rtDW_LP_Filter_Adj_System_MX_Gt *localDW);
extern void MX_G_LP_Filter_Adj_System_Reset(int32_T *rty_Output,
  rtDW_LP_Filter_Adj_System_MX_Gt *localDW);
extern void MX_Gtwy_Co_LP_Filter_Adj_System(uint8_T rtu_Gain, int16_T rtu_Input,
  uint8_T rtu_state_System, int32_T *rty_Output, rtDW_LP_Filter_Adj_System_MX_Gt
  *localDW);
extern void MX_Gtwy_Contr_control_loop_Init(rtDW_control_loop_MX_Gtwy_Contr
  *localDW);
extern void MX_Gtwy_Cont_control_loop_Reset(rtDW_control_loop_MX_Gtwy_Contr
  *localDW);
extern void MX_Gtwy_Co_control_loop_Disable(int16_T *rty_error, uint16_T
  *rty_duty, rtB_control_loop_MX_Gtwy_Contro *localB,
  rtDW_control_loop_MX_Gtwy_Contr *localDW);
extern void MX_Gtwy_Control_control_loop(boolean_T rtu_Enable, uint16_T
  rtu_i_cmd, uint16_T rtu_i_fbk, int16_T *rty_error, uint16_T *rty_duty,
  rtB_control_loop_MX_Gtwy_Contro *localB, rtDW_control_loop_MX_Gtwy_Contr
  *localDW, uint16_T rtp_KP, uint16_T rtp_KI);
extern void MX_Gtwy_C_hc_pair_OpenLoop_Init(uint16_T *rty_hs_cmd, boolean_T
  *rty_ls_cmd, uint8_T *rty_oc_state, uint8_T *rty_diag_state,
  rtDW_hc_pair_OpenLoop_MX_Gtwy_C *localDW);
extern void MX_Gtwy__hc_pair_OpenLoop_Reset(uint16_T *rty_hs_cmd, boolean_T
  *rty_ls_cmd, uint8_T *rty_oc_state, uint8_T *rty_diag_state,
  rtDW_hc_pair_OpenLoop_MX_Gtwy_C *localDW);
extern void MX_Gtwy_Contro_hc_pair_OpenLoop(uint16_T rtu_duty, boolean_T
  rtu_enable, boolean_T rtu_diag_enable, uint16_T rtu_afbk, uint16_T rtu_Vbatt,
  uint16_T rtu_ifbk, uint8_T rtu_ocstg_check, uint16_T *rty_hs_cmd, boolean_T
  *rty_ls_cmd, uint8_T *rty_oc_state, uint8_T *rty_diag_state,
  rtDW_hc_pair_OpenLoop_MX_Gtwy_C *localDW, uint16_T rtp_IFBK_MAX, uint16_T
  rtp_NZ_DUTY, uint16_T rtp_NZ_IFBK, uint16_T rtp_OC_DB_CNT, uint16_T
  rtp_OPEN_DB_CNT, uint16_T rtp_OSTG_DB_CNT, uint16_T rtp_STB_DB_CNT, uint16_T
  rtp_STG_DB_CNT);
extern void MX_G_hc_pair_ClosedLoop_v5_Init(uint16_T *rty_hs_cmd, boolean_T
  *rty_ls_cmd, uint8_T *rty_oc_state, uint8_T *rty_diag_state,
  rtDW_hc_pair_ClosedLoop_v5_MX_G *localDW);
extern void MX__hc_pair_ClosedLoop_v5_Reset(uint16_T *rty_hs_cmd, boolean_T
  *rty_ls_cmd, uint8_T *rty_oc_state, uint8_T *rty_diag_state,
  rtDW_hc_pair_ClosedLoop_v5_MX_G *localDW);
extern void M_hc_pair_ClosedLoop_v5_Disable(int16_T *rty_error,
  rtB_hc_pair_ClosedLoop_v5_MX_Gt *localB, rtDW_hc_pair_ClosedLoop_v5_MX_G
  *localDW);
extern void MX_Gtwy_C_hc_pair_ClosedLoop_v5(uint16_T rtu_i_cmd, boolean_T
  rtu_enable_LoSide, boolean_T rtu_diag_enable, uint16_T rtu_afbk, uint16_T
  rtu_Vbatt, uint16_T rtu_i_fbk, uint8_T rtu_ocstg_check, uint16_T *rty_hs_cmd,
  boolean_T *rty_ls_cmd, uint8_T *rty_oc_state, uint8_T *rty_diag_state, int16_T
  *rty_error, rtB_hc_pair_ClosedLoop_v5_MX_Gt *localB,
  rtDW_hc_pair_ClosedLoop_v5_MX_G *localDW, uint16_T rtp_KP, uint16_T rtp_KI,
  uint16_T rtp_IFBK_MAX, uint16_T rtp_NZ_DUTY, uint16_T rtp_NZ_IFBK, uint16_T
  rtp_OC_DB_CNT, uint16_T rtp_OPEN_DB_CNT, uint16_T rtp_OSTG_DB_CNT, uint16_T
  rtp_STB_DB_CNT, uint16_T rtp_STG_DB_CNT, uint8_T rtp_BIDIRECTIONAL_CTRL);
extern void MX_Gtwy_C_oc_stg_detection_Init(uint8_T *rty_diag_state_out, uint8_T
  *rty_ocstg_check, rtDW_oc_stg_detection_MX_Gtwy_C *localDW);
extern void MX_Gtwy__oc_stg_detection_Reset(uint8_T *rty_diag_state_out, uint8_T
  *rty_ocstg_check, rtDW_oc_stg_detection_MX_Gtwy_C *localDW);
extern void MX_Gtwy_Contro_oc_stg_detection(uint8_T rtu_oc_state, uint8_T
  rtu_diag_state_in, uint8_T *rty_diag_state_out, uint8_T *rty_ocstg_check,
  rtDW_oc_stg_detection_MX_Gtwy_C *localDW, uint16_T rtp_OPEN_DB_CNT, uint16_T
  rtp_STG_DB_CNT);
extern void MX__output_pair_ClosedLoop_Init(uint16_T *rty_hs_cmd, boolean_T
  *rty_ls_cmd, uint8_T *rty_state_Output, rtB_output_pair_ClosedLoop_MX_G
  *localB, rtDW_output_pair_ClosedLoop_MX_ *localDW);
extern void MX_output_pair_ClosedLoop_Reset(uint16_T *rty_hs_cmd, boolean_T
  *rty_ls_cmd, uint8_T *rty_state_Output, rtB_output_pair_ClosedLoop_MX_G
  *localB, rtDW_output_pair_ClosedLoop_MX_ *localDW);
extern void output_pair_ClosedLoop_Disable(int16_T *rty_errorCC,
  rtB_output_pair_ClosedLoop_MX_G *localB, rtDW_output_pair_ClosedLoop_MX_
  *localDW);
extern void MX_Gtwy__output_pair_ClosedLoop(uint16_T rtu_i_cmd, boolean_T
  rtu_enable_STGOffDiag, uint16_T rtu_afbk_A2D, uint16_T rtu_ifbk_A2D, uint8_T
  rtu_state_Vbattery, uint8_T rtu_state_Engine, uint16_T rtu_calc_Vbattery,
  uint16_T rtu_ain_PrecRef, uint16_T *rty_hs_cmd, boolean_T *rty_ls_cmd, int16_T
  *rty_errorCC, uint16_T *rty_calc_ifbk, uint8_T *rty_state_Output,
  rtB_output_pair_ClosedLoop_MX_G *localB, rtDW_output_pair_ClosedLoop_MX_
  *localDW, uint16_T rtp_OPEN_DB_CNT, uint16_T rtp_STG_DB_CNT, uint16_T rtp_KP,
  uint16_T rtp_KI, uint16_T rtp_IFBK_MAX, uint16_T rtp_NZ_DUTY, uint16_T
  rtp_NZ_IFBK, uint16_T rtp_OC_DB_CNT, uint16_T rtp_OSTG_DB_CNT, uint16_T
  rtp_STB_DB_CNT, uint8_T rtp_BIDIRECTIONAL_CTRL, uint16_T rtp_AFBK_GAIN,
  uint16_T rtp_IFBK_GAIN);
extern void MX_Gtwy_Control_Voltage_Limiter(uint16_T rtu_calc_VBattery, uint16_T
  rtu_duty_in, uint16_T *rty_duty_out, uint16_T rtp_MAX_VOLTS);
extern void MX_Gt_output_pair_OpenLoop_Init(uint16_T *rty_hs_cmd, boolean_T
  *rty_ls_cmd, uint8_T *rty_state_Output, rtB_output_pair_OpenLoop_MX_Gtw
  *localB, rtDW_output_pair_OpenLoop_MX_Gt *localDW);
extern void MX_G_output_pair_OpenLoop_Reset(uint16_T *rty_hs_cmd, boolean_T
  *rty_ls_cmd, uint8_T *rty_state_Output, rtB_output_pair_OpenLoop_MX_Gtw
  *localB, rtDW_output_pair_OpenLoop_MX_Gt *localDW);
extern void MX_Gtwy_Co_output_pair_OpenLoop(boolean_T rtu_cmd_Output, boolean_T
  rtu_enable_STGOffDiag, uint8_T rtu_state_Engine, uint16_T rtu_afbk_A2D,
  uint16_T rtu_ifbk_A2D, uint8_T rtu_state_VBattery, uint16_T rtu_calc_VBattery,
  uint16_T rtu_ain_PrecRef, uint16_T *rty_hs_cmd, boolean_T *rty_ls_cmd, uint8_T
  *rty_state_Output, rtB_output_pair_OpenLoop_MX_Gtw *localB,
  rtDW_output_pair_OpenLoop_MX_Gt *localDW, uint16_T rtp_MAX_VOLTS, uint16_T
  rtp_OPEN_DB_CNT, uint16_T rtp_STG_DB_CNT, uint16_T rtp_IFBK_MAX, uint16_T
  rtp_NZ_DUTY, uint16_T rtp_NZ_IFBK, uint16_T rtp_OC_DB_CNT, uint16_T
  rtp_OSTG_DB_CNT, uint16_T rtp_STB_DB_CNT, uint8_T rtp_FEEDBACK_ENABLE,
  uint16_T rtp_AFBK_GAIN, uint16_T rtp_IFBK_GAIN);
extern void MX_Gtwy_Control_relay_oc_Init(uint8_T *rty_state_Output, uint8_T
  *rty_state_Relay, rtB_relay_oc_MX_Gtwy_Control *localB,
  rtDW_relay_oc_MX_Gtwy_Control *localDW);
extern void MX_Gtwy_Contro_relay_oc_Disable(uint8_T *rty_state_Output, uint8_T
  *rty_state_Relay, rtDW_relay_oc_MX_Gtwy_Control *localDW);
extern void MX_Gtwy_Control_relay_oc(boolean_T rtu_Enable, boolean_T rtu_cmd,
  boolean_T rtu_dfbk, boolean_T rtu_din, uint8_T *rty_state_Output, uint8_T
  *rty_state_Relay, rtB_relay_oc_MX_Gtwy_Control *localB,
  rtDW_relay_oc_MX_Gtwy_Control *localDW, uint16_T rtp_ERROR_OFF_DB_CNT,
  uint16_T rtp_ERROR_ON_DB_CNT, uint16_T rtp_NORMAL_DB_CNT);
extern void MX_Gtwy_Control_hc_hsd_Init(uint8_T *rty_state,
  rtB_hc_hsd_MX_Gtwy_Control *localB, rtDW_hc_hsd_MX_Gtwy_Control *localDW);
extern void MX_Gtwy_Control_hc_hsd_Reset(rtB_hc_hsd_MX_Gtwy_Control *localB,
  rtDW_hc_hsd_MX_Gtwy_Control *localDW);
extern void MX_Gtwy_Control_hc_hsd_Disable(uint8_T *rty_state,
  rtDW_hc_hsd_MX_Gtwy_Control *localDW);
extern void MX_Gtwy_Control_hc_hsd(boolean_T rtu_Enable, uint16_T rtu_duty,
  uint16_T rtu_afbk, uint16_T rtu_Vbatt, uint8_T *rty_state,
  rtB_hc_hsd_MX_Gtwy_Control *localB, rtDW_hc_hsd_MX_Gtwy_Control *localDW,
  uint16_T rtp_OPEN_DB_CNT, uint16_T rtp_STB_DB_CNT, uint16_T rtp_STG_DB_CNT);
extern void MX__output_single_OpenLoop_Init(uint8_T *rty_state,
  rtB_output_single_OpenLoop_MX_G *localB, rtDW_output_single_OpenLoop_MX_
  *localDW);
extern void MX_output_single_OpenLoop_Reset(uint8_T *rty_state,
  rtB_output_single_OpenLoop_MX_G *localB, rtDW_output_single_OpenLoop_MX_
  *localDW);
extern void output_single_OpenLoop_Disable(rtB_output_single_OpenLoop_MX_G
  *localB, rtDW_output_single_OpenLoop_MX_ *localDW);
extern void MX_Gtwy__output_single_OpenLoop(uint16_T rtu_cmd, uint8_T
  rtu_state_Vbattery, uint16_T rtu_calc_VBattery, uint16_T rtu_afbk_A2D, uint8_T
  *rty_state, uint16_T *rty_duty_Output, rtB_output_single_OpenLoop_MX_G *localB,
  rtDW_output_single_OpenLoop_MX_ *localDW, uint16_T rtp_MAX_VOLTS, uint16_T
  rtp_OPEN_DB_CNT, uint16_T rtp_STB_DB_CNT, uint16_T rtp_STG_DB_CNT, uint8_T
  rtp_FUNCTION, uint16_T rtp_AFBK_GAIN);

#endif                                 // RTW_HEADER_mod_Library_h_

//
//  [EOF]

