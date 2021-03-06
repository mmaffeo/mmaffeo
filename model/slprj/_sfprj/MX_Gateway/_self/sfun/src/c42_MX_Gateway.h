#ifndef __c42_MX_Gateway_h__
#define __c42_MX_Gateway_h__

/* Type Definitions */
#ifndef typedef_SFc42_MX_GatewayInstanceStruct
#define typedef_SFc42_MX_GatewayInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c42_sfEvent;
  uint8_T c42_tp_Detent_State;
  uint8_T c42_tp_Non_Functional;
  uint8_T c42_tp_EMEA_CONTROLS;
  uint8_T c42_tp_Enable;
  uint8_T c42_tp_Disabled;
  uint8_T c42_tp_Enabled;
  uint8_T c42_tp_Detent;
  uint8_T c42_tp_Active_Normal;
  uint8_T c42_tp_Detent_Base;
  uint8_T c42_tp_Detent_Rod;
  uint8_T c42_tp_No_Detent;
  uint8_T c42_tp_Not_Enabled;
  uint8_T c42_tp_NORMAL_CONTROLS;
  uint8_T c42_b_tp_Enable;
  uint8_T c42_b_tp_Disabled;
  uint8_T c42_b_tp_Enabled;
  uint8_T c42_b_tp_Detent;
  uint8_T c42_b_tp_Active_Normal;
  uint8_T c42_b_tp_Detent_Base;
  uint8_T c42_b_tp_Detent_Rod;
  uint8_T c42_b_tp_No_Detent;
  uint8_T c42_b_tp_Not_Enabled;
  uint8_T c42_tp_Aux_Enable_State;
  uint8_T c42_b_tp_Non_Functional;
  uint8_T c42_tp_PHOENIX_K2;
  uint8_T c42_tp_Functional;
  uint8_T c42_c_tp_Enabled;
  uint8_T c42_tp_Off;
  uint8_T c42_tp_Active;
  uint8_T c42_tp_Low_Flow;
  uint8_T c42_tp_Medium_Flow;
  uint8_T c42_tp_Standard_Flow;
  uint8_T c42_tp_Inactive;
  uint8_T c42_tp_Inactive_Fault;
  uint8_T c42_tp_Inactive_Out_Of_Neutral;
  uint8_T c42_tp_Aux_Relief_G5;
  uint8_T c42_tp_Wait;
  uint8_T c42_tp_Ack;
  uint8_T c42_tp_Release_Base;
  uint8_T c42_tp_Release_Rod;
  uint8_T c42_tp_Confirm;
  uint8_T c42_tp_Aux_Enable_State_ST;
  uint8_T c42_tp_Inactive_Latched;
  uint8_T c42_tp_Inactive_Temp;
  uint8_T c42_b_tp_Standard_Flow;
  uint8_T c42_tp_Aux_Enable_State_ACD;
  uint8_T c42_b_tp_Inactive_Latched;
  uint8_T c42_b_tp_Inactive_Temp;
  uint8_T c42_c_tp_Standard_Flow;
  uint8_T c42_tp_SIRIUS2;
  uint8_T c42_b_tp_Functional;
  uint8_T c42_d_tp_Enabled;
  uint8_T c42_b_tp_Off;
  uint8_T c42_b_tp_Active;
  uint8_T c42_b_tp_Low_Flow;
  uint8_T c42_b_tp_Medium_Flow;
  uint8_T c42_d_tp_Standard_Flow;
  uint8_T c42_b_tp_Inactive;
  uint8_T c42_b_tp_Inactive_Fault;
  uint8_T c42_b_tp_Inactive_Out_Of_Neutral;
  uint8_T c42_b_tp_Aux_Enable_State_ST;
  uint8_T c42_c_tp_Inactive_Latched;
  uint8_T c42_c_tp_Inactive_Temp;
  uint8_T c42_e_tp_Standard_Flow;
  uint8_T c42_b_tp_Aux_Enable_State_ACD;
  uint8_T c42_d_tp_Inactive_Latched;
  uint8_T c42_d_tp_Inactive_Temp;
  uint8_T c42_f_tp_Standard_Flow;
  uint8_T c42_tp_SIRIUS2_HIFLOW;
  uint8_T c42_c_tp_Functional;
  uint8_T c42_e_tp_Enabled;
  uint8_T c42_c_tp_Off;
  uint8_T c42_c_tp_Active;
  uint8_T c42_c_tp_Low_Flow;
  uint8_T c42_c_tp_Medium_Flow;
  uint8_T c42_g_tp_Standard_Flow;
  uint8_T c42_tp_High_Flow;
  uint8_T c42_c_tp_Inactive;
  uint8_T c42_c_tp_Inactive_Fault;
  uint8_T c42_c_tp_Inactive_Out_Of_Neutral;
  uint8_T c42_c_tp_Aux_Enable_State_ST;
  uint8_T c42_e_tp_Inactive_Latched;
  uint8_T c42_e_tp_Inactive_Temp;
  uint8_T c42_h_tp_Standard_Flow;
  uint8_T c42_c_tp_Aux_Enable_State_ACD;
  uint8_T c42_f_tp_Inactive_Latched;
  uint8_T c42_f_tp_Inactive_Temp;
  uint8_T c42_i_tp_Standard_Flow;
  uint8_T c42_b_tp_EMEA_CONTROLS;
  uint8_T c42_d_tp_Functional;
  uint8_T c42_f_tp_Enabled;
  uint8_T c42_d_tp_Off;
  uint8_T c42_tp_WAIT_FOR_AUX_PRESS;
  uint8_T c42_d_tp_Active;
  uint8_T c42_d_tp_Low_Flow;
  uint8_T c42_d_tp_Medium_Flow;
  uint8_T c42_j_tp_Standard_Flow;
  uint8_T c42_d_tp_Inactive;
  uint8_T c42_d_tp_Inactive_Fault;
  uint8_T c42_d_tp_Inactive_Out_Of_Neutral;
  uint8_T c42_d_tp_Aux_Enable_State_ST;
  uint8_T c42_g_tp_Inactive_Latched;
  uint8_T c42_g_tp_Inactive_Temp;
  uint8_T c42_k_tp_Standard_Flow;
  uint8_T c42_d_tp_Aux_Enable_State_ACD;
  uint8_T c42_h_tp_Inactive_Latched;
  uint8_T c42_h_tp_Inactive_Temp;
  uint8_T c42_l_tp_Standard_Flow;
  uint8_T c42_tp_Aux_Reset;
  uint8_T c42_is_active_c42_MX_Gateway;
  uint8_T c42_is_Detent_State;
  uint8_T c42_is_active_Detent_State;
  uint8_T c42_is_Enable;
  uint8_T c42_is_active_Enable;
  uint8_T c42_is_Detent;
  uint8_T c42_is_active_Detent;
  uint8_T c42_is_Active_Normal;
  uint8_T c42_b_is_Enable;
  uint8_T c42_b_is_active_Enable;
  uint8_T c42_b_is_Detent;
  uint8_T c42_b_is_active_Detent;
  uint8_T c42_b_is_Active_Normal;
  uint8_T c42_is_Aux_Enable_State;
  uint8_T c42_is_active_Aux_Enable_State;
  uint8_T c42_is_PHOENIX_K2;
  uint8_T c42_is_Functional;
  uint8_T c42_is_Enabled;
  uint8_T c42_is_Active;
  uint8_T c42_is_Aux_Relief_G5;
  uint8_T c42_is_Aux_Enable_State_ST;
  uint8_T c42_is_Aux_Enable_State_ACD;
  uint8_T c42_is_SIRIUS2;
  uint8_T c42_b_is_Functional;
  uint8_T c42_b_is_Enabled;
  uint8_T c42_b_is_Active;
  uint8_T c42_b_is_Aux_Enable_State_ST;
  uint8_T c42_b_is_Aux_Enable_State_ACD;
  uint8_T c42_is_SIRIUS2_HIFLOW;
  uint8_T c42_c_is_Functional;
  uint8_T c42_c_is_Enabled;
  uint8_T c42_c_is_Active;
  uint8_T c42_c_is_Aux_Enable_State_ST;
  uint8_T c42_c_is_Aux_Enable_State_ACD;
  uint8_T c42_is_EMEA_CONTROLS;
  uint8_T c42_d_is_Functional;
  uint8_T c42_d_is_Enabled;
  uint8_T c42_d_is_Active;
  uint8_T c42_d_is_Aux_Enable_State_ST;
  uint8_T c42_d_is_Aux_Enable_State_ACD;
  uint8_T c42_is_active_Aux_Reset;
  uint8_T c42_ACTIVE_MODE_ONE;
  uint8_T c42_BASE_ACTIVE;
  uint8_T c42_BASE_DETENT;
  uint8_T c42_ENGINE_CRANKING;
  uint8_T c42_NON_FUNCTIONAL;
  uint8_T c42_INACTIVE;
  uint8_T c42_NO_DETENT;
  uint8_T c42_ROD_ACTIVE;
  uint8_T c42_ROD_DETENT;
  uint8_T c42_ACTIVE;
  uint8_T c42_NOT_IN_NEUTRAL;
  uint8_T c42_OORH;
  uint8_T c42_OORL;
  uint8_T c42_AUX_FLOW_LOW;
  uint8_T c42_AUX_FLOW_MEDIUM;
  uint8_T c42_AUX_FLOW_HIGH;
  uint8_T c42_CD_AUX_ADJ_FLOW_FUNCTION;
  uint8_T c42_SINGLE_SHORT_BEEP;
  uint8_T c42_CD_AUX_FUNCTION;
  uint8_T c42_ERR_DETENT;
  uint8_T c42_NORMAL;
  uint8_T c42_SYS_NORMAL;
  uint8_T c42_DOUBLE_SHORT_BEEP;
  uint8_T c42_CD_STAUX_FUNCTION;
  uint8_T c42_CD_RACD_FUNCTION;
  uint8_T c42_state_ACD_old;
  uint8_T c42_state_ST_old;
  uint16_T c42_CD_AUX_RELEASE_TIME;
  uint16_T c42_CD_AUX_CONFIRM_TIME;
  uint8_T c42_AUX_RELEASE_WAIT;
  uint8_T c42_AUX_RELEASE_ACK;
  uint8_T c42_AUX_RELEASE_IN_PROGRESS;
  uint8_T c42_AUX_RELEASE_CONFIRM;
  uint8_T c42_CD_AUX_RELEASE_FUNCTION;
  uint8_T c42_ENGINE_NOT_RUNNING;
  uint8_T c42_ENGINE_RUNNING;
  uint16_T c42_CD_AUX_DETENT_FLASH_TIME;
  uint8_T c42_ENGINE_INITIALIZE;
  uint8_T c42_AUX_SIRIUS2;
  uint8_T c42_CD_AUX_HIGH_FLOW;
  uint8_T c42_AUX_FLOW_STANDARD;
  uint8_T c42_CD_DELUXE_GEN5_5_FUNCTION;
  uint8_T c42_AUX_FLOW_INACTIVE;
  uint8_T c42_AUX_EMEA_CONTROLS;
  uint8_T c42_AUX_PHOENIX_K2;
  uint8_T c42_MODE_RIGHT_AUX1;
  uint8_T c42_NO_SIGNAL;
  boolean_T c42_previouslyActive;
  uint8_T c42_CD_EMEA_CONTROLS_OPTION_B;
  uint8_T c42_CD_EMEA_CONTROLS_OPTION_C;
  uint8_T c42_CD_RIGHT_POT_FUNCTION;
  uint32_T c42_temporalCounter_i1;
  uint16_T c42_temporalCounter_i2;
  uint8_T c42_doSetSimStateSideEffects;
  const mxArray *c42_setSimStateSideEffectsInfo;
  uint8_T *c42_ee_AuxFlow_address;
  int32_T c42__indexFlow;
  boolean_T c42_dsmdiag_ee_AuxFlow;
  uint8_T *c42__indexee_DeluxeG5_address;
  int32_T c42__indexuxeG5;
  boolean_T c42_dsmdiag_ee_DeluxeG5;
  uint8_T *c42__indexstate_Buzzer_address;
  int32_T c42__indexBuzzer;
  boolean_T c42_dsmdiag_state_Buzzer;
  void *c42_fEmlrtCtx;
  uint8_T *c42_DetentRisingEdge;
  uint8_T *c42_state_AuxEnable;
  uint8_T *c42_state_Detent;
  uint8_T *c42_state_AuxPot;
  uint8_T *c42_state_Engine;
  uint8_T *c42_state_Console;
  uint8_T *c42_aux_DebounceButton;
  uint8_T *c42_state_System;
  uint8_T *c42_aux_Flow;
  uint8_T *c42_state_DetentEnable;
  uint8_T *c42_aux_DetentHold;
  uint8_T *c42_state_Buttons;
  boolean_T *c42_flag_InitEERead;
  uint8_T *c42_can_AuxEnable_ST;
  uint8_T *c42_can_AuxEnable_ACD;
  uint8_T *c42_state_ST_CAN;
  uint8_T *c42_state_ACD_CAN;
  boolean_T *c42_button_AuxReleaseAck;
  boolean_T *c42_button_AuxReleaseBack;
  boolean_T *c42_button_AuxReleaseExit;
  uint8_T *c42_cmd_AuxRelease;
  uint8_T *c42_button_Aux;
  uint8_T *c42_state_AuxRelease;
  uint8_T *c42_state_RightPot;
  boolean_T *c42_change_OffsetSelectSw;
  uint8_T *c42_mode_RightControl;
  boolean_T *c42_aux_Inhibit;
  uint8_T *c42_state_EngineSpeed;
} SFc42_MX_GatewayInstanceStruct;

#endif                                 /*typedef_SFc42_MX_GatewayInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c42_MX_Gateway_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c42_MX_Gateway_get_check_sum(mxArray *plhs[]);
extern void c42_MX_Gateway_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
