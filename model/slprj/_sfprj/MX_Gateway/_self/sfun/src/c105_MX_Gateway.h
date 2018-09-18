#ifndef __c105_MX_Gateway_h__
#define __c105_MX_Gateway_h__

/* Type Definitions */
#ifndef typedef_SFc105_MX_GatewayInstanceStruct
#define typedef_SFc105_MX_GatewayInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c105_sfEvent;
  uint8_T c105_tp_Non_Functional;
  uint8_T c105_tp_OptionA;
  uint8_T c105_tp_Left_Control_or_Diverter_Fault;
  uint8_T c105_tp_Mode_None_Aux1;
  uint8_T c105_tp_Fault_Mode;
  uint8_T c105_tp_INIT_SystemCheck;
  uint8_T c105_tp_Delay;
  uint8_T c105_tp_Enabled;
  uint8_T c105_tp_Aux_Enabled;
  uint8_T c105_tp_Mode_Aux2_Aux1;
  uint8_T c105_tp_Mode_Offset_Aux1;
  uint8_T c105_tp_Mode_Offset_None;
  uint8_T c105_tp_OptionB;
  uint8_T c105_b_tp_INIT_SystemCheck;
  uint8_T c105_b_tp_Delay;
  uint8_T c105_b_tp_Enabled;
  uint8_T c105_tp_Offset_Left;
  uint8_T c105_b_tp_Aux_Enabled;
  uint8_T c105_tp_Mode_Offset_Aux4;
  uint8_T c105_b_tp_Mode_Offset_Aux1;
  uint8_T c105_b_tp_Mode_Offset_None;
  uint8_T c105_tp_Control_Fault;
  uint8_T c105_tp_Offset_Right;
  uint8_T c105_c_tp_Aux_Enabled;
  uint8_T c105_tp_Mode_Aux4_Aux1;
  uint8_T c105_tp_Mode_Aux4_Offset;
  uint8_T c105_tp_Mode_None_Offset;
  uint8_T c105_tp_OptionC;
  uint8_T c105_c_tp_INIT_SystemCheck;
  uint8_T c105_c_tp_Delay;
  uint8_T c105_c_tp_Enabled;
  uint8_T c105_b_tp_Offset_Left;
  uint8_T c105_d_tp_Aux_Enabled;
  uint8_T c105_b_tp_Mode_Offset_Aux4;
  uint8_T c105_c_tp_Mode_Offset_Aux1;
  uint8_T c105_tp_Mode_Aux2_Aux4;
  uint8_T c105_b_tp_Mode_Aux2_Aux1;
  uint8_T c105_c_tp_Mode_Offset_None;
  uint8_T c105_b_tp_Control_Fault;
  uint8_T c105_b_tp_Offset_Right;
  uint8_T c105_e_tp_Aux_Enabled;
  uint8_T c105_b_tp_Mode_Aux4_Aux1;
  uint8_T c105_b_tp_Mode_Aux4_Offset;
  uint8_T c105_c_tp_Mode_Aux2_Aux1;
  uint8_T c105_b_tp_Mode_None_Offset;
  uint8_T c105_is_active_c105_MX_Gateway;
  uint8_T c105_is_c105_MX_Gateway;
  uint8_T c105_is_OptionA;
  uint8_T c105_is_Left_Control_or_Diverter_Fault;
  uint8_T c105_is_Enabled;
  uint8_T c105_is_Aux_Enabled;
  uint8_T c105_is_OptionB;
  uint8_T c105_b_is_Enabled;
  uint8_T c105_is_Offset_Left;
  uint8_T c105_b_is_Aux_Enabled;
  uint8_T c105_is_Offset_Right;
  uint8_T c105_c_is_Aux_Enabled;
  uint8_T c105_is_OptionC;
  uint8_T c105_c_is_Enabled;
  uint8_T c105_b_is_Offset_Left;
  uint8_T c105_d_is_Aux_Enabled;
  uint8_T c105_b_is_Offset_Right;
  uint8_T c105_e_is_Aux_Enabled;
  uint8_T c105_MODE_LEFT_NONE;
  uint8_T c105_MODE_LEFT_OFFSET;
  uint8_T c105_MODE_LEFT_AUX2;
  uint8_T c105_MODE_LEFT_AUX4;
  uint8_T c105_DOUBLE_SHORT_BEEP;
  uint8_T c105_SINGLE_SHORT_BEEP;
  uint8_T c105_NORMAL;
  uint8_T c105_CD_EMEA_CONTROLS_OPTION_A;
  uint8_T c105_CD_EMEA_CONTROLS_OPTION_B;
  uint8_T c105_CD_EMEA_CONTROLS_OPTION_C;
  uint8_T c105_NON_FUNCTIONAL;
  uint8_T c105_OFFSET_SELECT_LEFT;
  uint8_T c105_OFFSET_SELECT_RIGHT;
  uint8_T c105_SINGLE_MEDIUM_BEEP;
  uint8_T c105_TRIPLE_SHORT_BEEP;
  uint8_T c105_INACTIVE;
  uint8_T c105_MODE_RIGHT_AUX1;
  uint8_T c105_MODE_RIGHT_AUX4;
  uint8_T c105_MODE_RIGHT_NONE;
  uint8_T c105_MODE_RIGHT_OFFSET;
  uint8_T c105_ACTIVE;
  uint8_T c105_ENGINE_CRANKING;
  uint8_T c105_SYS_NORMAL;
  uint8_T c105_OORH;
  uint8_T c105_OORL;
  uint8_T c105_NO_COMMUNICATION;
  uint8_T c105_EE_RT_A2_A1;
  uint8_T c105_EE_LT_A2_A4;
  uint8_T c105_EE_RT_A4_A1;
  uint8_T c105_EE_RT_A4_OF;
  uint8_T c105_EE_NA_NA;
  uint8_T c105_EE_RT_NA_OF;
  uint8_T c105_EE_LT_OF_A1;
  uint8_T c105_EE_LT_OF_A4;
  uint8_T c105_EE_LT_OF_NA;
  uint8_T c105_EE_LT_A2_A1;
  uint8_T c105_stored_ControlMode;
  uint8_T c105_temporalCounter_i1;
  uint8_T c105_doSetSimStateSideEffects;
  const mxArray *c105_setSimStateSideEffectsInfo;
  uint8_T *c105_ee_ControlMode_address;
  int32_T c105__indextrolMode;
  boolean_T c105_dsmdiag_ee_ControlMode;
  uint8_T *c105__indexstate_Buzzer_address;
  int32_T c105__indexBuzzer;
  boolean_T c105_dsmdiag_state_Buzzer;
  void *c105_fEmlrtCtx;
  boolean_T *c105_flag_AuxEnableFlash;
  boolean_T *c105_change_RightControlMode;
  uint8_T *c105_state_CommSecondary;
  uint8_T *c105_mode_LeftControl;
  boolean_T *c105_change_LeftControlMode;
  boolean_T *c105_valid_LeftControl;
  boolean_T *c105_valid_RightControl;
  uint8_T *c105_mode_RightControl;
  uint8_T *c105_state_Console;
  uint8_T *c105_state_Engine;
  uint8_T *c105_state_System;
  boolean_T *c105_flag_InitEERead;
  boolean_T *c105_fault_Diverter;
  uint8_T *c105_state_AuxEnable;
  boolean_T *c105_check_LeftNeutral;
  boolean_T *c105_check_RightNeutral;
  boolean_T *c105_change_AuxEnable;
  boolean_T *c105_din_OffsetSelectSw;
  boolean_T *c105_change_OffsetSelectSw;
  boolean_T *c105_aux_inhibit;
  boolean_T *c105_display_request;
} SFc105_MX_GatewayInstanceStruct;

#endif                                 /*typedef_SFc105_MX_GatewayInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c105_MX_Gateway_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c105_MX_Gateway_get_check_sum(mxArray *plhs[]);
extern void c105_MX_Gateway_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
