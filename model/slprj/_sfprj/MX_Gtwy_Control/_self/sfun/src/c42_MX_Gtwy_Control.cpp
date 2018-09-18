/* Include files */

#include "MX_Gtwy_Control_sfun.h"
#include "c42_MX_Gtwy_Control.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "MX_Gtwy_Control_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define c42_event_disable_aux          (0)
#define c42_event_disable_detent       (1)
#define CALL_EVENT                     (-1)
#define c42_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)
#define c42_IN_EMEA_CONTROLS           ((uint8_T)1U)
#define c42_IN_NORMAL_CONTROLS         ((uint8_T)2U)
#define c42_IN_Non_Functional          ((uint8_T)3U)
#define c42_IN_Disabled                ((uint8_T)1U)
#define c42_IN_Enabled                 ((uint8_T)2U)
#define c42_IN_Active_Normal           ((uint8_T)1U)
#define c42_IN_No_Detent               ((uint8_T)2U)
#define c42_IN_Not_Enabled             ((uint8_T)3U)
#define c42_IN_Detent_Base             ((uint8_T)1U)
#define c42_IN_Detent_Rod              ((uint8_T)2U)
#define c42_b_IN_Non_Functional        ((uint8_T)2U)
#define c42_IN_PHOENIX_K2              ((uint8_T)3U)
#define c42_IN_SIRIUS2                 ((uint8_T)4U)
#define c42_IN_SIRIUS2_HIFLOW          ((uint8_T)5U)
#define c42_IN_Aux_Enable_State_ACD    ((uint8_T)1U)
#define c42_IN_Aux_Enable_State_ST     ((uint8_T)2U)
#define c42_IN_Functional              ((uint8_T)3U)
#define c42_IN_Aux_Relief_G5           ((uint8_T)1U)
#define c42_IN_Inactive                ((uint8_T)3U)
#define c42_IN_Inactive_Fault          ((uint8_T)4U)
#define c42_IN_Inactive_Out_Of_Neutral ((uint8_T)5U)
#define c42_IN_Active                  ((uint8_T)1U)
#define c42_IN_Off                     ((uint8_T)2U)
#define c42_IN_Low_Flow                ((uint8_T)1U)
#define c42_IN_Medium_Flow             ((uint8_T)2U)
#define c42_IN_Standard_Flow           ((uint8_T)3U)
#define c42_IN_Ack                     ((uint8_T)1U)
#define c42_IN_Confirm                 ((uint8_T)2U)
#define c42_IN_Release_Base            ((uint8_T)3U)
#define c42_IN_Release_Rod             ((uint8_T)4U)
#define c42_IN_Wait                    ((uint8_T)5U)
#define c42_IN_Inactive_Latched        ((uint8_T)1U)
#define c42_IN_Inactive_Temp           ((uint8_T)2U)
#define c42_b_IN_Enabled               ((uint8_T)1U)
#define c42_b_IN_Inactive              ((uint8_T)2U)
#define c42_b_IN_Inactive_Fault        ((uint8_T)3U)
#define c42_b_IN_Inactive_Out_Of_Neutral ((uint8_T)4U)
#define c42_IN_High_Flow               ((uint8_T)1U)
#define c42_b_IN_Low_Flow              ((uint8_T)2U)
#define c42_b_IN_Medium_Flow           ((uint8_T)3U)
#define c42_b_IN_Standard_Flow         ((uint8_T)4U)
#define c42_IN_WAIT_FOR_AUX_PRESS      ((uint8_T)3U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initialize_params_c42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void enable_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void disable_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_update_debugger_state_c42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void set_sim_state_c42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c42_st);
static void c42_set_sim_state_side_effects_c42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void finalize_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void sf_gateway_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void mdl_start_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initSimStructsc42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_Detent_State(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_Non_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_Detent(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_exit_internal_Active_Normal(SFc42_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c42_b_Detent(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_b_exit_internal_Active_Normal
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_Aux_Enable_State(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_PHOENIX_K2(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_enter_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_exit_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_enter_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_exit_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_Active(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_exit_internal_Active(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_Inactive(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_Inactive_Out_Of_Neutral(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_Aux_Relief_G5(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_exit_internal_Aux_Relief_G5(SFc42_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c42_exit_internal_Aux_Enable_State_ST
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_exit_internal_Aux_Enable_State_ACD
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_SIRIUS2(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_b_enter_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c42_b_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_b_exit_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_b_enter_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_b_exit_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_b_Active(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_b_exit_internal_Active(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_Inactive_Fault(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_b_Inactive_Out_Of_Neutral(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_b_exit_internal_Aux_Enable_State_ST
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_b_exit_internal_Aux_Enable_State_ACD
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_SIRIUS2_HIFLOW(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_c_enter_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c42_c_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_c_exit_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_c_enter_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_c_exit_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_c_Active(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_c_exit_internal_Active(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_b_Inactive_Fault(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_c_Inactive_Out_Of_Neutral(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_c_exit_internal_Aux_Enable_State_ST
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_c_exit_internal_Aux_Enable_State_ACD
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_EMEA_CONTROLS(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_d_enter_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c42_d_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_d_exit_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_d_enter_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_d_exit_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_d_Active(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_d_exit_internal_Active(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_d_Inactive_Out_Of_Neutral(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c42_d_exit_internal_Aux_Enable_State_ST
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c42_d_exit_internal_Aux_Enable_State_ACD
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c42_machineNumber, uint32_T
  c42_chartNumber, uint32_T c42_instanceNumber);
static const mxArray *c42_sf_marshallOut(void *chartInstanceVoid, void
  *c42_inData);
static int32_T c42_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId);
static void c42_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c42_mxArrayInData, const char_T *c42_varName, void *c42_outData);
static const mxArray *c42_b_sf_marshallOut(void *chartInstanceVoid, void
  *c42_inData);
static uint8_T c42_b_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_b_tp_Detent_State, const char_T
  *c42_identifier);
static uint8_T c42_c_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId);
static void c42_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c42_mxArrayInData, const char_T *c42_varName, void *c42_outData);
static const mxArray *c42_c_sf_marshallOut(void *chartInstanceVoid, void
  *c42_inData);
static const mxArray *c42_d_sf_marshallOut(void *chartInstanceVoid, void
  *c42_inData);
static uint16_T c42_d_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_b_CD_AUX_RELEASE_TIME, const char_T
  *c42_identifier);
static uint16_T c42_e_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId);
static void c42_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c42_mxArrayInData, const char_T *c42_varName, void *c42_outData);
static boolean_T c42_f_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_b_previouslyActive, const char_T
  *c42_identifier);
static boolean_T c42_g_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId);
static void c42_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c42_mxArrayInData, const char_T *c42_varName, void *c42_outData);
static uint32_T c42_h_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_b_temporalCounter_i1, const char_T
  *c42_identifier);
static uint32_T c42_i_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId);
static const mxArray *c42_j_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_b_setSimStateSideEffectsInfo, const char_T *
  c42_identifier);
static const mxArray *c42_k_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId);
static const mxArray *sf_get_hover_data_for_msg
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c42_ssid);
static void c42_init_sf_message_store_memory(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static uint16_T c42__u16_s32_(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c42_b, uint32_T c42_ssid_src_loc, int32_T c42_offset_src_loc, int32_T
  c42_length_src_loc);
static uint32_T c42__u32_s32_(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c42_b, uint32_T c42_ssid_src_loc, int32_T c42_offset_src_loc, int32_T
  c42_length_src_loc);
static uint16_T c42__u16_u32_(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance,
  uint32_T c42_b, uint32_T c42_ssid_src_loc, int32_T c42_offset_src_loc, int32_T
  c42_length_src_loc);
static uint8_T c42_get_ee_AuxFlow(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex);
static void c42_set_ee_AuxFlow(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex, uint8_T c42_elementValue);
static uint8_T *c42_access_ee_AuxFlow(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_rdOnly);
static uint8_T c42_get_ee_DeluxeG5(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex);
static void c42_set_ee_DeluxeG5(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex, uint8_T c42_elementValue);
static uint8_T *c42_access_ee_DeluxeG5(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_rdOnly);
static uint8_T c42_get_state_Buzzer(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex);
static void c42_set_state_Buzzer(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex, uint8_T c42_elementValue);
static uint8_T *c42_access_state_Buzzer(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_rdOnly);
static void init_dsm_address_info(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc42_MX_Gtwy_Control(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c42_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c42_doSetSimStateSideEffects = 0U;
  chartInstance->c42_setSimStateSideEffectsInfo = NULL;
  chartInstance->c42_is_active_Aux_Enable_State = 0U;
  chartInstance->c42_is_Aux_Enable_State = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_Aux_Enable_State = 0U;
  chartInstance->c42_is_EMEA_CONTROLS = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_b_tp_EMEA_CONTROLS = 0U;
  chartInstance->c42_d_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_d_tp_Aux_Enable_State_ACD = 0U;
  chartInstance->c42_h_tp_Inactive_Latched = 0U;
  chartInstance->c42_h_tp_Inactive_Temp = 0U;
  chartInstance->c42_l_tp_Standard_Flow = 0U;
  chartInstance->c42_d_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_d_tp_Aux_Enable_State_ST = 0U;
  chartInstance->c42_g_tp_Inactive_Latched = 0U;
  chartInstance->c42_g_tp_Inactive_Temp = 0U;
  chartInstance->c42_k_tp_Standard_Flow = 0U;
  chartInstance->c42_d_is_Functional = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_d_tp_Functional = 0U;
  chartInstance->c42_d_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_f_tp_Enabled = 0U;
  chartInstance->c42_d_is_Active = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_d_tp_Active = 0U;
  chartInstance->c42_d_tp_Low_Flow = 0U;
  chartInstance->c42_d_tp_Medium_Flow = 0U;
  chartInstance->c42_j_tp_Standard_Flow = 0U;
  chartInstance->c42_d_tp_Off = 0U;
  chartInstance->c42_tp_WAIT_FOR_AUX_PRESS = 0U;
  chartInstance->c42_d_tp_Inactive = 0U;
  chartInstance->c42_d_tp_Inactive_Fault = 0U;
  chartInstance->c42_d_tp_Inactive_Out_Of_Neutral = 0U;
  chartInstance->c42_b_tp_Non_Functional = 0U;
  chartInstance->c42_is_PHOENIX_K2 = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_PHOENIX_K2 = 0U;
  chartInstance->c42_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_Aux_Enable_State_ACD = 0U;
  chartInstance->c42_b_tp_Inactive_Latched = 0U;
  chartInstance->c42_b_tp_Inactive_Temp = 0U;
  chartInstance->c42_c_tp_Standard_Flow = 0U;
  chartInstance->c42_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_Aux_Enable_State_ST = 0U;
  chartInstance->c42_tp_Inactive_Latched = 0U;
  chartInstance->c42_tp_Inactive_Temp = 0U;
  chartInstance->c42_b_tp_Standard_Flow = 0U;
  chartInstance->c42_is_Functional = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_Functional = 0U;
  chartInstance->c42_is_Aux_Relief_G5 = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_Aux_Relief_G5 = 0U;
  chartInstance->c42_tp_Ack = 0U;
  chartInstance->c42_tp_Confirm = 0U;
  chartInstance->c42_temporalCounter_i2 = 0U;
  chartInstance->c42_tp_Release_Base = 0U;
  chartInstance->c42_temporalCounter_i2 = 0U;
  chartInstance->c42_tp_Release_Rod = 0U;
  chartInstance->c42_temporalCounter_i2 = 0U;
  chartInstance->c42_tp_Wait = 0U;
  chartInstance->c42_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_c_tp_Enabled = 0U;
  chartInstance->c42_is_Active = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_Active = 0U;
  chartInstance->c42_tp_Low_Flow = 0U;
  chartInstance->c42_tp_Medium_Flow = 0U;
  chartInstance->c42_tp_Standard_Flow = 0U;
  chartInstance->c42_tp_Off = 0U;
  chartInstance->c42_tp_Inactive = 0U;
  chartInstance->c42_tp_Inactive_Fault = 0U;
  chartInstance->c42_tp_Inactive_Out_Of_Neutral = 0U;
  chartInstance->c42_is_SIRIUS2 = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_SIRIUS2 = 0U;
  chartInstance->c42_b_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_b_tp_Aux_Enable_State_ACD = 0U;
  chartInstance->c42_d_tp_Inactive_Latched = 0U;
  chartInstance->c42_d_tp_Inactive_Temp = 0U;
  chartInstance->c42_f_tp_Standard_Flow = 0U;
  chartInstance->c42_b_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_b_tp_Aux_Enable_State_ST = 0U;
  chartInstance->c42_c_tp_Inactive_Latched = 0U;
  chartInstance->c42_c_tp_Inactive_Temp = 0U;
  chartInstance->c42_e_tp_Standard_Flow = 0U;
  chartInstance->c42_b_is_Functional = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_b_tp_Functional = 0U;
  chartInstance->c42_b_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_d_tp_Enabled = 0U;
  chartInstance->c42_b_is_Active = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_b_tp_Active = 0U;
  chartInstance->c42_b_tp_Low_Flow = 0U;
  chartInstance->c42_b_tp_Medium_Flow = 0U;
  chartInstance->c42_d_tp_Standard_Flow = 0U;
  chartInstance->c42_b_tp_Off = 0U;
  chartInstance->c42_b_tp_Inactive = 0U;
  chartInstance->c42_b_tp_Inactive_Fault = 0U;
  chartInstance->c42_b_tp_Inactive_Out_Of_Neutral = 0U;
  chartInstance->c42_is_SIRIUS2_HIFLOW = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_SIRIUS2_HIFLOW = 0U;
  chartInstance->c42_c_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_c_tp_Aux_Enable_State_ACD = 0U;
  chartInstance->c42_f_tp_Inactive_Latched = 0U;
  chartInstance->c42_f_tp_Inactive_Temp = 0U;
  chartInstance->c42_i_tp_Standard_Flow = 0U;
  chartInstance->c42_c_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_c_tp_Aux_Enable_State_ST = 0U;
  chartInstance->c42_e_tp_Inactive_Latched = 0U;
  chartInstance->c42_e_tp_Inactive_Temp = 0U;
  chartInstance->c42_h_tp_Standard_Flow = 0U;
  chartInstance->c42_c_is_Functional = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_c_tp_Functional = 0U;
  chartInstance->c42_c_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_e_tp_Enabled = 0U;
  chartInstance->c42_c_is_Active = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_c_tp_Active = 0U;
  chartInstance->c42_tp_High_Flow = 0U;
  chartInstance->c42_c_tp_Low_Flow = 0U;
  chartInstance->c42_c_tp_Medium_Flow = 0U;
  chartInstance->c42_g_tp_Standard_Flow = 0U;
  chartInstance->c42_c_tp_Off = 0U;
  chartInstance->c42_c_tp_Inactive = 0U;
  chartInstance->c42_c_tp_Inactive_Fault = 0U;
  chartInstance->c42_c_tp_Inactive_Out_Of_Neutral = 0U;
  chartInstance->c42_is_active_Aux_Reset = 0U;
  chartInstance->c42_tp_Aux_Reset = 0U;
  chartInstance->c42_is_active_Detent_State = 0U;
  chartInstance->c42_is_Detent_State = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_Detent_State = 0U;
  chartInstance->c42_tp_EMEA_CONTROLS = 0U;
  chartInstance->c42_is_active_Detent = 0U;
  chartInstance->c42_is_Detent = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_Detent = 0U;
  chartInstance->c42_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_Active_Normal = 0U;
  chartInstance->c42_tp_Detent_Base = 0U;
  chartInstance->c42_tp_Detent_Rod = 0U;
  chartInstance->c42_tp_No_Detent = 0U;
  chartInstance->c42_tp_Not_Enabled = 0U;
  chartInstance->c42_temporalCounter_i1 = 0U;
  chartInstance->c42_is_active_Enable = 0U;
  chartInstance->c42_is_Enable = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_tp_Enable = 0U;
  chartInstance->c42_tp_Disabled = 0U;
  chartInstance->c42_tp_Enabled = 0U;
  chartInstance->c42_tp_NORMAL_CONTROLS = 0U;
  chartInstance->c42_b_is_active_Detent = 0U;
  chartInstance->c42_b_is_Detent = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_b_tp_Detent = 0U;
  chartInstance->c42_b_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_b_tp_Active_Normal = 0U;
  chartInstance->c42_b_tp_Detent_Base = 0U;
  chartInstance->c42_b_tp_Detent_Rod = 0U;
  chartInstance->c42_b_tp_No_Detent = 0U;
  chartInstance->c42_b_tp_Not_Enabled = 0U;
  chartInstance->c42_temporalCounter_i1 = 0U;
  chartInstance->c42_b_is_active_Enable = 0U;
  chartInstance->c42_b_is_Enable = c42_IN_NO_ACTIVE_CHILD;
  chartInstance->c42_b_tp_Enable = 0U;
  chartInstance->c42_b_tp_Disabled = 0U;
  chartInstance->c42_b_tp_Enabled = 0U;
  chartInstance->c42_tp_Non_Functional = 0U;
  chartInstance->c42_is_active_c42_MX_Gtwy_Control = 0U;
  chartInstance->c42_state_ACD_old = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_state_ACD_old, 1U);
  chartInstance->c42_state_ST_old = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_state_ST_old, 2U);
  chartInstance->c42_previouslyActive = false;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_previouslyActive, 0U);
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c42_state_AuxEnable = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c42_state_Detent = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *chartInstance->c42_aux_Flow = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 4) != 0)) {
    *chartInstance->c42_state_DetentEnable = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_DetentEnable, 28U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 5) != 0)) {
    *chartInstance->c42_cmd_AuxRelease = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 6) != 0)) {
    *chartInstance->c42_state_AuxRelease = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxRelease, 30U);
  }
}

static void initialize_params_c42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  real_T c42_d0;
  real_T c42_d1;
  real_T c42_d2;
  real_T c42_d3;
  real_T c42_d4;
  real_T c42_d5;
  real_T c42_d6;
  real_T c42_d7;
  real_T c42_d8;
  real_T c42_d9;
  real_T c42_d10;
  real_T c42_d11;
  real_T c42_d12;
  real_T c42_d13;
  real_T c42_d14;
  real_T c42_d15;
  real_T c42_d16;
  real_T c42_d17;
  real_T c42_d18;
  real_T c42_d19;
  real_T c42_d20;
  real_T c42_d21;
  real_T c42_d22;
  real_T c42_d23;
  real_T c42_d24;
  real_T c42_d25;
  real_T c42_d26;
  real_T c42_d27;
  real_T c42_d28;
  real_T c42_d29;
  real_T c42_d30;
  real_T c42_d31;
  real_T c42_d32;
  real_T c42_d33;
  real_T c42_d34;
  real_T c42_d35;
  real_T c42_d36;
  real_T c42_d37;
  real_T c42_d38;
  real_T c42_d39;
  real_T c42_d40;
  real_T c42_d41;
  real_T c42_d42;
  real_T c42_d43;
  real_T c42_d44;
  real_T c42_d45;
  real_T c42_d46;
  real_T c42_d47;
  sf_mex_import_named("ACTIVE_MODE_ONE", sf_mex_get_sfun_param(chartInstance->S,
    1, 0), &c42_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_ACTIVE_MODE_ONE = (uint8_T)c42_d0;
  sf_mex_import_named("BASE_ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 14,
    0), &c42_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_BASE_ACTIVE = (uint8_T)c42_d1;
  sf_mex_import_named("BASE_DETENT", sf_mex_get_sfun_param(chartInstance->S, 15,
    0), &c42_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_BASE_DETENT = (uint8_T)c42_d2;
  sf_mex_import_named("ENGINE_CRANKING", sf_mex_get_sfun_param(chartInstance->S,
    30, 0), &c42_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_ENGINE_CRANKING = (uint8_T)c42_d3;
  sf_mex_import_named("NON_FUNCTIONAL", sf_mex_get_sfun_param(chartInstance->S,
    37, 0), &c42_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_NON_FUNCTIONAL = (uint8_T)c42_d4;
  sf_mex_import_named("INACTIVE", sf_mex_get_sfun_param(chartInstance->S, 35, 0),
                      &c42_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_INACTIVE = (uint8_T)c42_d5;
  sf_mex_import_named("NO_DETENT", sf_mex_get_sfun_param(chartInstance->S, 40, 0),
                      &c42_d6, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_NO_DETENT = (uint8_T)c42_d6;
  sf_mex_import_named("ROD_ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 44,
    0), &c42_d7, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_ROD_ACTIVE = (uint8_T)c42_d7;
  sf_mex_import_named("ROD_DETENT", sf_mex_get_sfun_param(chartInstance->S, 45,
    0), &c42_d8, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_ROD_DETENT = (uint8_T)c42_d8;
  sf_mex_import_named("ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c42_d9, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_ACTIVE = (uint8_T)c42_d9;
  sf_mex_import_named("NOT_IN_NEUTRAL", sf_mex_get_sfun_param(chartInstance->S,
    39, 0), &c42_d10, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_NOT_IN_NEUTRAL = (uint8_T)c42_d10;
  sf_mex_import_named("OORH", sf_mex_get_sfun_param(chartInstance->S, 42, 0),
                      &c42_d11, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_OORH = (uint8_T)c42_d11;
  sf_mex_import_named("OORL", sf_mex_get_sfun_param(chartInstance->S, 43, 0),
                      &c42_d12, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_OORL = (uint8_T)c42_d12;
  sf_mex_import_named("AUX_FLOW_LOW", sf_mex_get_sfun_param(chartInstance->S, 5,
    0), &c42_d13, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_FLOW_LOW = (uint8_T)c42_d13;
  sf_mex_import_named("AUX_FLOW_MEDIUM", sf_mex_get_sfun_param(chartInstance->S,
    6, 0), &c42_d14, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_FLOW_MEDIUM = (uint8_T)c42_d14;
  sf_mex_import_named("AUX_FLOW_HIGH", sf_mex_get_sfun_param(chartInstance->S, 3,
    0), &c42_d15, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_FLOW_HIGH = (uint8_T)c42_d15;
  sf_mex_import_named("CD_AUX_ADJ_FLOW_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 16, 0), &c42_d16, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION = (uint8_T)c42_d16;
  sf_mex_import_named("SINGLE_SHORT_BEEP", sf_mex_get_sfun_param
                      (chartInstance->S, 46, 0), &c42_d17, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_SINGLE_SHORT_BEEP = (uint8_T)c42_d17;
  sf_mex_import_named("CD_AUX_FUNCTION", sf_mex_get_sfun_param(chartInstance->S,
    19, 0), &c42_d18, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_AUX_FUNCTION = (uint8_T)c42_d18;
  sf_mex_import_named("ERR_DETENT", sf_mex_get_sfun_param(chartInstance->S, 34,
    0), &c42_d19, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_ERR_DETENT = (uint8_T)c42_d19;
  sf_mex_import_named("NORMAL", sf_mex_get_sfun_param(chartInstance->S, 38, 0),
                      &c42_d20, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_NORMAL = (uint8_T)c42_d20;
  sf_mex_import_named("SYS_NORMAL", sf_mex_get_sfun_param(chartInstance->S, 47,
    0), &c42_d21, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_SYS_NORMAL = (uint8_T)c42_d21;
  sf_mex_import_named("DOUBLE_SHORT_BEEP", sf_mex_get_sfun_param
                      (chartInstance->S, 29, 0), &c42_d22, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_DOUBLE_SHORT_BEEP = (uint8_T)c42_d22;
  sf_mex_import_named("CD_STAUX_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 28, 0), &c42_d23, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_STAUX_FUNCTION = (uint8_T)c42_d23;
  sf_mex_import_named("CD_RACD_FUNCTION", sf_mex_get_sfun_param(chartInstance->S,
    26, 0), &c42_d24, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_RACD_FUNCTION = (uint8_T)c42_d24;
  sf_mex_import_named("CD_AUX_RELEASE_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 22, 0), &c42_d25, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_AUX_RELEASE_TIME = (uint16_T)c42_d25;
  sf_mex_import_named("CD_AUX_CONFIRM_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 17, 0), &c42_d26, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_AUX_CONFIRM_TIME = (uint16_T)c42_d26;
  sf_mex_import_named("AUX_RELEASE_WAIT", sf_mex_get_sfun_param(chartInstance->S,
    12, 0), &c42_d27, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_RELEASE_WAIT = (uint8_T)c42_d27;
  sf_mex_import_named("AUX_RELEASE_ACK", sf_mex_get_sfun_param(chartInstance->S,
    9, 0), &c42_d28, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_RELEASE_ACK = (uint8_T)c42_d28;
  sf_mex_import_named("AUX_RELEASE_IN_PROGRESS", sf_mex_get_sfun_param
                      (chartInstance->S, 11, 0), &c42_d29, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_RELEASE_IN_PROGRESS = (uint8_T)c42_d29;
  sf_mex_import_named("AUX_RELEASE_CONFIRM", sf_mex_get_sfun_param
                      (chartInstance->S, 10, 0), &c42_d30, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_RELEASE_CONFIRM = (uint8_T)c42_d30;
  sf_mex_import_named("CD_AUX_RELEASE_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 21, 0), &c42_d31, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_AUX_RELEASE_FUNCTION = (uint8_T)c42_d31;
  sf_mex_import_named("ENGINE_NOT_RUNNING", sf_mex_get_sfun_param
                      (chartInstance->S, 32, 0), &c42_d32, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_ENGINE_NOT_RUNNING = (uint8_T)c42_d32;
  sf_mex_import_named("ENGINE_RUNNING", sf_mex_get_sfun_param(chartInstance->S,
    33, 0), &c42_d33, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_ENGINE_RUNNING = (uint8_T)c42_d33;
  sf_mex_import_named("CD_AUX_DETENT_FLASH_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 18, 0), &c42_d34, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_AUX_DETENT_FLASH_TIME = (uint16_T)c42_d34;
  sf_mex_import_named("ENGINE_INITIALIZE", sf_mex_get_sfun_param
                      (chartInstance->S, 31, 0), &c42_d35, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_ENGINE_INITIALIZE = (uint8_T)c42_d35;
  sf_mex_import_named("AUX_SIRIUS2", sf_mex_get_sfun_param(chartInstance->S, 13,
    0), &c42_d36, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_SIRIUS2 = (uint8_T)c42_d36;
  sf_mex_import_named("CD_AUX_HIGH_FLOW", sf_mex_get_sfun_param(chartInstance->S,
    20, 0), &c42_d37, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_AUX_HIGH_FLOW = (uint8_T)c42_d37;
  sf_mex_import_named("AUX_FLOW_STANDARD", sf_mex_get_sfun_param
                      (chartInstance->S, 7, 0), &c42_d38, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_FLOW_STANDARD = (uint8_T)c42_d38;
  sf_mex_import_named("CD_DELUXE_GEN5_5_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 23, 0), &c42_d39, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_DELUXE_GEN5_5_FUNCTION = (uint8_T)c42_d39;
  sf_mex_import_named("AUX_FLOW_INACTIVE", sf_mex_get_sfun_param
                      (chartInstance->S, 4, 0), &c42_d40, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_FLOW_INACTIVE = (uint8_T)c42_d40;
  sf_mex_import_named("AUX_EMEA_CONTROLS", sf_mex_get_sfun_param
                      (chartInstance->S, 2, 0), &c42_d41, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_EMEA_CONTROLS = (uint8_T)c42_d41;
  sf_mex_import_named("AUX_PHOENIX_K2", sf_mex_get_sfun_param(chartInstance->S,
    8, 0), &c42_d42, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_AUX_PHOENIX_K2 = (uint8_T)c42_d42;
  sf_mex_import_named("MODE_RIGHT_AUX1", sf_mex_get_sfun_param(chartInstance->S,
    36, 0), &c42_d43, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_MODE_RIGHT_AUX1 = (uint8_T)c42_d43;
  sf_mex_import_named("NO_SIGNAL", sf_mex_get_sfun_param(chartInstance->S, 41, 0),
                      &c42_d44, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_NO_SIGNAL = (uint8_T)c42_d44;
  sf_mex_import_named("CD_EMEA_CONTROLS_OPTION_B", sf_mex_get_sfun_param
                      (chartInstance->S, 24, 0), &c42_d45, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_EMEA_CONTROLS_OPTION_B = (uint8_T)c42_d45;
  sf_mex_import_named("CD_EMEA_CONTROLS_OPTION_C", sf_mex_get_sfun_param
                      (chartInstance->S, 25, 0), &c42_d46, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_EMEA_CONTROLS_OPTION_C = (uint8_T)c42_d46;
  sf_mex_import_named("CD_RIGHT_POT_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 27, 0), &c42_d47, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c42_CD_RIGHT_POT_FUNCTION = (uint8_T)c42_d47;
}

static void enable_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c42_update_debugger_state_c42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  uint32_T c42_prevAniVal;
  c42_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c42_is_active_c42_MX_Gtwy_Control == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_active_Detent_State == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 87U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 87U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Detent_State == c42_IN_Non_Functional) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 108U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 108U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Detent_State == c42_IN_EMEA_CONTROLS) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 88U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 88U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_active_Enable == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 95U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 95U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Enable == c42_IN_Disabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 96U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 96U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Enable == c42_IN_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 97U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 97U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_active_Detent == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 89U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 89U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Detent == c42_IN_Active_Normal) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 90U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 90U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Active_Normal == c42_IN_Detent_Base) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 91U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 91U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Active_Normal == c42_IN_Detent_Rod) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 92U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 92U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Detent == c42_IN_No_Detent) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Detent == c42_IN_Not_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 94U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 94U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Detent_State == c42_IN_NORMAL_CONTROLS) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 98U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 98U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_active_Enable == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 105U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 105U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Enable == c42_IN_Disabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 106U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 106U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Enable == c42_IN_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 107U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 107U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_active_Detent == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 99U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 99U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Detent == c42_IN_Active_Normal) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 100U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 100U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Active_Normal == c42_IN_Detent_Base) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 101U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 101U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Active_Normal == c42_IN_Detent_Rod) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 102U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 102U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Detent == c42_IN_No_Detent) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Detent == c42_IN_Not_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 104U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 104U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_active_Aux_Enable_State == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State == c42_b_IN_Non_Functional) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State == c42_IN_PHOENIX_K2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_PHOENIX_K2 == c42_IN_Functional) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Functional == c42_IN_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Enabled == c42_IN_Off) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Enabled == c42_IN_Active) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Active == c42_IN_Low_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Active == c42_IN_Medium_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 41U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Active == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Functional == c42_IN_Inactive) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Functional == c42_IN_Inactive_Fault) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 45U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 45U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Functional == c42_IN_Inactive_Out_Of_Neutral) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 46U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Functional == c42_IN_Aux_Relief_G5) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Relief_G5 == c42_IN_Wait) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Relief_G5 == c42_IN_Ack) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Relief_G5 == c42_IN_Release_Base) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Relief_G5 == c42_IN_Release_Rod) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Relief_G5 == c42_IN_Confirm) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 34U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_PHOENIX_K2 == c42_IN_Aux_Enable_State_ST) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State_ST == c42_IN_Inactive_Latched) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 28U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State_ST == c42_IN_Inactive_Temp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 29U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State_ST == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 30U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_PHOENIX_K2 == c42_IN_Aux_Enable_State_ACD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State_ACD == c42_IN_Inactive_Latched) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State_ACD == c42_IN_Inactive_Temp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State == c42_IN_SIRIUS2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 47U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 47U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_SIRIUS2 == c42_IN_Functional) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 56U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 56U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Functional == c42_b_IN_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Enabled == c42_IN_Off) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 62U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 62U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Enabled == c42_IN_Active) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Active == c42_IN_Low_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 59U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 59U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Active == c42_IN_Medium_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 60U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 60U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Active == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 61U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 61U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Functional == c42_b_IN_Inactive) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 63U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 63U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Functional == c42_b_IN_Inactive_Fault) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 64U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 64U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Functional == c42_b_IN_Inactive_Out_Of_Neutral) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 65U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 65U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_SIRIUS2 == c42_IN_Aux_Enable_State_ST) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 52U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 52U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Aux_Enable_State_ST == c42_IN_Inactive_Latched) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 53U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 53U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Aux_Enable_State_ST == c42_IN_Inactive_Temp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 54U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 54U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Aux_Enable_State_ST == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 55U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 55U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_SIRIUS2 == c42_IN_Aux_Enable_State_ACD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 48U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 48U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Aux_Enable_State_ACD == c42_IN_Inactive_Latched) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 49U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 49U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Aux_Enable_State_ACD == c42_IN_Inactive_Temp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 50U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 50U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_b_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 51U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 51U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State == c42_IN_SIRIUS2_HIFLOW) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 66U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 66U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_SIRIUS2_HIFLOW == c42_IN_Functional) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 75U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 75U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Functional == c42_b_IN_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Enabled == c42_IN_Off) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 82U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 82U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Enabled == c42_IN_Active) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Active == c42_b_IN_Low_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 79U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 79U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Active == c42_b_IN_Medium_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 80U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 80U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Active == c42_b_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 81U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 81U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Active == c42_IN_High_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 78U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 78U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Functional == c42_b_IN_Inactive) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 83U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 83U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Functional == c42_b_IN_Inactive_Fault) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 84U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 84U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Functional == c42_b_IN_Inactive_Out_Of_Neutral) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 85U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 85U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_SIRIUS2_HIFLOW == c42_IN_Aux_Enable_State_ST) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 71U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 71U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Aux_Enable_State_ST == c42_IN_Inactive_Latched) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 72U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 72U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Aux_Enable_State_ST == c42_IN_Inactive_Temp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 73U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 73U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Aux_Enable_State_ST == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 74U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 74U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_SIRIUS2_HIFLOW == c42_IN_Aux_Enable_State_ACD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 67U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 67U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Aux_Enable_State_ACD == c42_IN_Inactive_Latched) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Aux_Enable_State_ACD == c42_IN_Inactive_Temp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 69U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 69U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_c_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 70U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 70U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_Aux_Enable_State == c42_IN_EMEA_CONTROLS) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_EMEA_CONTROLS == c42_IN_Functional) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Functional == c42_b_IN_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Enabled == c42_IN_Off) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Enabled == c42_IN_WAIT_FOR_AUX_PRESS) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Enabled == c42_IN_Active) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Active == c42_IN_Low_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Active == c42_IN_Medium_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Active == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Functional == c42_b_IN_Inactive) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Functional == c42_b_IN_Inactive_Fault) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Functional == c42_b_IN_Inactive_Out_Of_Neutral) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_EMEA_CONTROLS == c42_IN_Aux_Enable_State_ST) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Aux_Enable_State_ST == c42_IN_Inactive_Latched) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Aux_Enable_State_ST == c42_IN_Inactive_Temp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Aux_Enable_State_ST == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_EMEA_CONTROLS == c42_IN_Aux_Enable_State_ACD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Aux_Enable_State_ACD == c42_IN_Inactive_Latched) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Aux_Enable_State_ACD == c42_IN_Inactive_Temp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_d_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c42_sfEvent);
  }

  if (chartInstance->c42_is_active_Aux_Reset == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 86U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 86U, chartInstance->c42_sfEvent);
  }

  _SFD_SET_ANIMATION(c42_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  const mxArray *c42_st;
  const mxArray *c42_y = NULL;
  uint8_T c42_hoistedGlobal;
  const mxArray *c42_b_y = NULL;
  uint8_T c42_b_hoistedGlobal;
  const mxArray *c42_c_y = NULL;
  uint8_T c42_c_hoistedGlobal;
  const mxArray *c42_d_y = NULL;
  uint8_T c42_d_hoistedGlobal;
  const mxArray *c42_e_y = NULL;
  uint8_T c42_e_hoistedGlobal;
  const mxArray *c42_f_y = NULL;
  uint8_T c42_f_hoistedGlobal;
  const mxArray *c42_g_y = NULL;
  boolean_T c42_g_hoistedGlobal;
  const mxArray *c42_h_y = NULL;
  uint8_T c42_h_hoistedGlobal;
  const mxArray *c42_i_y = NULL;
  uint8_T c42_i_hoistedGlobal;
  const mxArray *c42_j_y = NULL;
  uint8_T c42_j_hoistedGlobal;
  const mxArray *c42_k_y = NULL;
  uint8_T c42_k_hoistedGlobal;
  const mxArray *c42_l_y = NULL;
  uint8_T c42_l_hoistedGlobal;
  const mxArray *c42_m_y = NULL;
  uint8_T c42_m_hoistedGlobal;
  const mxArray *c42_n_y = NULL;
  uint8_T c42_n_hoistedGlobal;
  const mxArray *c42_o_y = NULL;
  uint8_T c42_o_hoistedGlobal;
  const mxArray *c42_p_y = NULL;
  uint8_T c42_p_hoistedGlobal;
  const mxArray *c42_q_y = NULL;
  uint8_T c42_q_hoistedGlobal;
  const mxArray *c42_r_y = NULL;
  uint8_T c42_r_hoistedGlobal;
  const mxArray *c42_s_y = NULL;
  uint8_T c42_s_hoistedGlobal;
  const mxArray *c42_t_y = NULL;
  uint8_T c42_t_hoistedGlobal;
  const mxArray *c42_u_y = NULL;
  uint8_T c42_u_hoistedGlobal;
  const mxArray *c42_v_y = NULL;
  uint8_T c42_v_hoistedGlobal;
  const mxArray *c42_w_y = NULL;
  uint8_T c42_w_hoistedGlobal;
  const mxArray *c42_x_y = NULL;
  uint8_T c42_x_hoistedGlobal;
  const mxArray *c42_y_y = NULL;
  uint8_T c42_y_hoistedGlobal;
  const mxArray *c42_ab_y = NULL;
  uint8_T c42_ab_hoistedGlobal;
  const mxArray *c42_bb_y = NULL;
  uint8_T c42_bb_hoistedGlobal;
  const mxArray *c42_cb_y = NULL;
  uint8_T c42_cb_hoistedGlobal;
  const mxArray *c42_db_y = NULL;
  uint8_T c42_db_hoistedGlobal;
  const mxArray *c42_eb_y = NULL;
  uint8_T c42_eb_hoistedGlobal;
  const mxArray *c42_fb_y = NULL;
  uint8_T c42_fb_hoistedGlobal;
  const mxArray *c42_gb_y = NULL;
  uint8_T c42_gb_hoistedGlobal;
  const mxArray *c42_hb_y = NULL;
  uint8_T c42_hb_hoistedGlobal;
  const mxArray *c42_ib_y = NULL;
  uint8_T c42_ib_hoistedGlobal;
  const mxArray *c42_jb_y = NULL;
  uint8_T c42_jb_hoistedGlobal;
  const mxArray *c42_kb_y = NULL;
  uint8_T c42_kb_hoistedGlobal;
  const mxArray *c42_lb_y = NULL;
  uint8_T c42_lb_hoistedGlobal;
  const mxArray *c42_mb_y = NULL;
  uint8_T c42_mb_hoistedGlobal;
  const mxArray *c42_nb_y = NULL;
  uint8_T c42_nb_hoistedGlobal;
  const mxArray *c42_ob_y = NULL;
  uint8_T c42_ob_hoistedGlobal;
  const mxArray *c42_pb_y = NULL;
  uint8_T c42_pb_hoistedGlobal;
  const mxArray *c42_qb_y = NULL;
  uint8_T c42_qb_hoistedGlobal;
  const mxArray *c42_rb_y = NULL;
  uint8_T c42_rb_hoistedGlobal;
  const mxArray *c42_sb_y = NULL;
  uint8_T c42_sb_hoistedGlobal;
  const mxArray *c42_tb_y = NULL;
  uint8_T c42_tb_hoistedGlobal;
  const mxArray *c42_ub_y = NULL;
  uint8_T c42_ub_hoistedGlobal;
  const mxArray *c42_vb_y = NULL;
  uint8_T c42_vb_hoistedGlobal;
  const mxArray *c42_wb_y = NULL;
  uint8_T c42_wb_hoistedGlobal;
  const mxArray *c42_xb_y = NULL;
  uint8_T c42_xb_hoistedGlobal;
  const mxArray *c42_yb_y = NULL;
  uint8_T c42_yb_hoistedGlobal;
  const mxArray *c42_ac_y = NULL;
  uint32_T c42_ac_hoistedGlobal;
  const mxArray *c42_bc_y = NULL;
  uint16_T c42_bc_hoistedGlobal;
  const mxArray *c42_cc_y = NULL;
  c42_st = NULL;
  c42_st = NULL;
  c42_y = NULL;
  sf_mex_assign(&c42_y, sf_mex_createcellmatrix(52, 1), false);
  c42_hoistedGlobal = *chartInstance->c42_aux_Flow;
  c42_b_y = NULL;
  sf_mex_assign(&c42_b_y, sf_mex_create("y", &c42_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 0, c42_b_y);
  c42_b_hoistedGlobal = *chartInstance->c42_cmd_AuxRelease;
  c42_c_y = NULL;
  sf_mex_assign(&c42_c_y, sf_mex_create("y", &c42_b_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 1, c42_c_y);
  c42_c_hoistedGlobal = *chartInstance->c42_state_AuxEnable;
  c42_d_y = NULL;
  sf_mex_assign(&c42_d_y, sf_mex_create("y", &c42_c_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 2, c42_d_y);
  c42_d_hoistedGlobal = *chartInstance->c42_state_AuxRelease;
  c42_e_y = NULL;
  sf_mex_assign(&c42_e_y, sf_mex_create("y", &c42_d_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 3, c42_e_y);
  c42_e_hoistedGlobal = *chartInstance->c42_state_Detent;
  c42_f_y = NULL;
  sf_mex_assign(&c42_f_y, sf_mex_create("y", &c42_e_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 4, c42_f_y);
  c42_f_hoistedGlobal = *chartInstance->c42_state_DetentEnable;
  c42_g_y = NULL;
  sf_mex_assign(&c42_g_y, sf_mex_create("y", &c42_f_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 5, c42_g_y);
  c42_g_hoistedGlobal = chartInstance->c42_previouslyActive;
  c42_h_y = NULL;
  sf_mex_assign(&c42_h_y, sf_mex_create("y", &c42_g_hoistedGlobal, 11, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 6, c42_h_y);
  c42_h_hoistedGlobal = chartInstance->c42_state_ACD_old;
  c42_i_y = NULL;
  sf_mex_assign(&c42_i_y, sf_mex_create("y", &c42_h_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 7, c42_i_y);
  c42_i_hoistedGlobal = chartInstance->c42_state_ST_old;
  c42_j_y = NULL;
  sf_mex_assign(&c42_j_y, sf_mex_create("y", &c42_i_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 8, c42_j_y);
  c42_j_hoistedGlobal = chartInstance->c42_is_active_c42_MX_Gtwy_Control;
  c42_k_y = NULL;
  sf_mex_assign(&c42_k_y, sf_mex_create("y", &c42_j_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 9, c42_k_y);
  c42_k_hoistedGlobal = chartInstance->c42_is_active_Aux_Enable_State;
  c42_l_y = NULL;
  sf_mex_assign(&c42_l_y, sf_mex_create("y", &c42_k_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 10, c42_l_y);
  c42_l_hoistedGlobal = chartInstance->c42_is_active_Detent_State;
  c42_m_y = NULL;
  sf_mex_assign(&c42_m_y, sf_mex_create("y", &c42_l_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 11, c42_m_y);
  c42_m_hoistedGlobal = chartInstance->c42_is_active_Enable;
  c42_n_y = NULL;
  sf_mex_assign(&c42_n_y, sf_mex_create("y", &c42_m_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 12, c42_n_y);
  c42_n_hoistedGlobal = chartInstance->c42_is_active_Aux_Reset;
  c42_o_y = NULL;
  sf_mex_assign(&c42_o_y, sf_mex_create("y", &c42_n_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 13, c42_o_y);
  c42_o_hoistedGlobal = chartInstance->c42_is_active_Detent;
  c42_p_y = NULL;
  sf_mex_assign(&c42_p_y, sf_mex_create("y", &c42_o_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 14, c42_p_y);
  c42_p_hoistedGlobal = chartInstance->c42_b_is_active_Enable;
  c42_q_y = NULL;
  sf_mex_assign(&c42_q_y, sf_mex_create("y", &c42_p_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 15, c42_q_y);
  c42_q_hoistedGlobal = chartInstance->c42_b_is_active_Detent;
  c42_r_y = NULL;
  sf_mex_assign(&c42_r_y, sf_mex_create("y", &c42_q_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 16, c42_r_y);
  c42_r_hoistedGlobal = chartInstance->c42_is_Aux_Enable_State;
  c42_s_y = NULL;
  sf_mex_assign(&c42_s_y, sf_mex_create("y", &c42_r_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 17, c42_s_y);
  c42_s_hoistedGlobal = chartInstance->c42_is_Detent_State;
  c42_t_y = NULL;
  sf_mex_assign(&c42_t_y, sf_mex_create("y", &c42_s_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 18, c42_t_y);
  c42_t_hoistedGlobal = chartInstance->c42_is_Active_Normal;
  c42_u_y = NULL;
  sf_mex_assign(&c42_u_y, sf_mex_create("y", &c42_t_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 19, c42_u_y);
  c42_u_hoistedGlobal = chartInstance->c42_is_Enable;
  c42_v_y = NULL;
  sf_mex_assign(&c42_v_y, sf_mex_create("y", &c42_u_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 20, c42_v_y);
  c42_v_hoistedGlobal = chartInstance->c42_is_Enabled;
  c42_w_y = NULL;
  sf_mex_assign(&c42_w_y, sf_mex_create("y", &c42_v_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 21, c42_w_y);
  c42_w_hoistedGlobal = chartInstance->c42_is_Functional;
  c42_x_y = NULL;
  sf_mex_assign(&c42_x_y, sf_mex_create("y", &c42_w_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 22, c42_x_y);
  c42_x_hoistedGlobal = chartInstance->c42_is_Active;
  c42_y_y = NULL;
  sf_mex_assign(&c42_y_y, sf_mex_create("y", &c42_x_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c42_y, 23, c42_y_y);
  c42_y_hoistedGlobal = chartInstance->c42_is_Aux_Enable_State_ST;
  c42_ab_y = NULL;
  sf_mex_assign(&c42_ab_y, sf_mex_create("y", &c42_y_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 24, c42_ab_y);
  c42_ab_hoistedGlobal = chartInstance->c42_is_Aux_Enable_State_ACD;
  c42_bb_y = NULL;
  sf_mex_assign(&c42_bb_y, sf_mex_create("y", &c42_ab_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 25, c42_bb_y);
  c42_bb_hoistedGlobal = chartInstance->c42_is_Aux_Relief_G5;
  c42_cb_y = NULL;
  sf_mex_assign(&c42_cb_y, sf_mex_create("y", &c42_bb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 26, c42_cb_y);
  c42_cb_hoistedGlobal = chartInstance->c42_is_PHOENIX_K2;
  c42_db_y = NULL;
  sf_mex_assign(&c42_db_y, sf_mex_create("y", &c42_cb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 27, c42_db_y);
  c42_db_hoistedGlobal = chartInstance->c42_is_SIRIUS2_HIFLOW;
  c42_eb_y = NULL;
  sf_mex_assign(&c42_eb_y, sf_mex_create("y", &c42_db_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 28, c42_eb_y);
  c42_eb_hoistedGlobal = chartInstance->c42_c_is_Functional;
  c42_fb_y = NULL;
  sf_mex_assign(&c42_fb_y, sf_mex_create("y", &c42_eb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 29, c42_fb_y);
  c42_fb_hoistedGlobal = chartInstance->c42_c_is_Enabled;
  c42_gb_y = NULL;
  sf_mex_assign(&c42_gb_y, sf_mex_create("y", &c42_fb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 30, c42_gb_y);
  c42_gb_hoistedGlobal = chartInstance->c42_c_is_Active;
  c42_hb_y = NULL;
  sf_mex_assign(&c42_hb_y, sf_mex_create("y", &c42_gb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 31, c42_hb_y);
  c42_hb_hoistedGlobal = chartInstance->c42_c_is_Aux_Enable_State_ST;
  c42_ib_y = NULL;
  sf_mex_assign(&c42_ib_y, sf_mex_create("y", &c42_hb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 32, c42_ib_y);
  c42_ib_hoistedGlobal = chartInstance->c42_c_is_Aux_Enable_State_ACD;
  c42_jb_y = NULL;
  sf_mex_assign(&c42_jb_y, sf_mex_create("y", &c42_ib_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 33, c42_jb_y);
  c42_jb_hoistedGlobal = chartInstance->c42_is_SIRIUS2;
  c42_kb_y = NULL;
  sf_mex_assign(&c42_kb_y, sf_mex_create("y", &c42_jb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 34, c42_kb_y);
  c42_kb_hoistedGlobal = chartInstance->c42_b_is_Functional;
  c42_lb_y = NULL;
  sf_mex_assign(&c42_lb_y, sf_mex_create("y", &c42_kb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 35, c42_lb_y);
  c42_lb_hoistedGlobal = chartInstance->c42_b_is_Enabled;
  c42_mb_y = NULL;
  sf_mex_assign(&c42_mb_y, sf_mex_create("y", &c42_lb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 36, c42_mb_y);
  c42_mb_hoistedGlobal = chartInstance->c42_b_is_Active;
  c42_nb_y = NULL;
  sf_mex_assign(&c42_nb_y, sf_mex_create("y", &c42_mb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 37, c42_nb_y);
  c42_nb_hoistedGlobal = chartInstance->c42_b_is_Aux_Enable_State_ST;
  c42_ob_y = NULL;
  sf_mex_assign(&c42_ob_y, sf_mex_create("y", &c42_nb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 38, c42_ob_y);
  c42_ob_hoistedGlobal = chartInstance->c42_b_is_Aux_Enable_State_ACD;
  c42_pb_y = NULL;
  sf_mex_assign(&c42_pb_y, sf_mex_create("y", &c42_ob_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 39, c42_pb_y);
  c42_pb_hoistedGlobal = chartInstance->c42_is_Detent;
  c42_qb_y = NULL;
  sf_mex_assign(&c42_qb_y, sf_mex_create("y", &c42_pb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 40, c42_qb_y);
  c42_qb_hoistedGlobal = chartInstance->c42_is_EMEA_CONTROLS;
  c42_rb_y = NULL;
  sf_mex_assign(&c42_rb_y, sf_mex_create("y", &c42_qb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 41, c42_rb_y);
  c42_rb_hoistedGlobal = chartInstance->c42_d_is_Functional;
  c42_sb_y = NULL;
  sf_mex_assign(&c42_sb_y, sf_mex_create("y", &c42_rb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 42, c42_sb_y);
  c42_sb_hoistedGlobal = chartInstance->c42_d_is_Enabled;
  c42_tb_y = NULL;
  sf_mex_assign(&c42_tb_y, sf_mex_create("y", &c42_sb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 43, c42_tb_y);
  c42_tb_hoistedGlobal = chartInstance->c42_d_is_Active;
  c42_ub_y = NULL;
  sf_mex_assign(&c42_ub_y, sf_mex_create("y", &c42_tb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 44, c42_ub_y);
  c42_ub_hoistedGlobal = chartInstance->c42_d_is_Aux_Enable_State_ST;
  c42_vb_y = NULL;
  sf_mex_assign(&c42_vb_y, sf_mex_create("y", &c42_ub_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 45, c42_vb_y);
  c42_vb_hoistedGlobal = chartInstance->c42_d_is_Aux_Enable_State_ACD;
  c42_wb_y = NULL;
  sf_mex_assign(&c42_wb_y, sf_mex_create("y", &c42_vb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 46, c42_wb_y);
  c42_wb_hoistedGlobal = chartInstance->c42_b_is_Enable;
  c42_xb_y = NULL;
  sf_mex_assign(&c42_xb_y, sf_mex_create("y", &c42_wb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 47, c42_xb_y);
  c42_xb_hoistedGlobal = chartInstance->c42_b_is_Detent;
  c42_yb_y = NULL;
  sf_mex_assign(&c42_yb_y, sf_mex_create("y", &c42_xb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 48, c42_yb_y);
  c42_yb_hoistedGlobal = chartInstance->c42_b_is_Active_Normal;
  c42_ac_y = NULL;
  sf_mex_assign(&c42_ac_y, sf_mex_create("y", &c42_yb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 49, c42_ac_y);
  c42_ac_hoistedGlobal = chartInstance->c42_temporalCounter_i1;
  c42_bc_y = NULL;
  sf_mex_assign(&c42_bc_y, sf_mex_create("y", &c42_ac_hoistedGlobal, 7, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 50, c42_bc_y);
  c42_bc_hoistedGlobal = chartInstance->c42_temporalCounter_i2;
  c42_cc_y = NULL;
  sf_mex_assign(&c42_cc_y, sf_mex_create("y", &c42_bc_hoistedGlobal, 5, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c42_y, 51, c42_cc_y);
  sf_mex_assign(&c42_st, c42_y, false);
  return c42_st;
}

static void set_sim_state_c42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c42_st)
{
  const mxArray *c42_u;
  c42_u = sf_mex_dup(c42_st);
  *chartInstance->c42_aux_Flow = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 0)), "aux_Flow");
  *chartInstance->c42_cmd_AuxRelease = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 1)), "cmd_AuxRelease");
  *chartInstance->c42_state_AuxEnable = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 2)), "state_AuxEnable");
  *chartInstance->c42_state_AuxRelease = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 3)), "state_AuxRelease");
  *chartInstance->c42_state_Detent = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 4)), "state_Detent");
  *chartInstance->c42_state_DetentEnable = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 5)), "state_DetentEnable");
  chartInstance->c42_previouslyActive = c42_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 6)), "previouslyActive");
  chartInstance->c42_state_ACD_old = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 7)), "state_ACD_old");
  chartInstance->c42_state_ST_old = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 8)), "state_ST_old");
  chartInstance->c42_is_active_c42_MX_Gtwy_Control = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 9)),
     "is_active_c42_MX_Gtwy_Control");
  chartInstance->c42_is_active_Aux_Enable_State = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 10)),
     "is_active_Aux_Enable_State");
  chartInstance->c42_is_active_Detent_State = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 11)),
     "is_active_Detent_State");
  chartInstance->c42_is_active_Enable = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 12)), "is_active_Enable");
  chartInstance->c42_is_active_Aux_Reset = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 13)), "is_active_Aux_Reset");
  chartInstance->c42_is_active_Detent = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 14)), "is_active_Detent");
  chartInstance->c42_b_is_active_Enable = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 15)), "is_active_Enable");
  chartInstance->c42_b_is_active_Detent = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 16)), "is_active_Detent");
  chartInstance->c42_is_Aux_Enable_State = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 17)), "is_Aux_Enable_State");
  chartInstance->c42_is_Detent_State = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 18)), "is_Detent_State");
  chartInstance->c42_is_Active_Normal = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 19)), "is_Active_Normal");
  chartInstance->c42_is_Enable = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 20)), "is_Enable");
  chartInstance->c42_is_Enabled = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 21)), "is_Enabled");
  chartInstance->c42_is_Functional = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 22)), "is_Functional");
  chartInstance->c42_is_Active = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 23)), "is_Active");
  chartInstance->c42_is_Aux_Enable_State_ST = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 24)),
     "is_Aux_Enable_State_ST");
  chartInstance->c42_is_Aux_Enable_State_ACD = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 25)),
     "is_Aux_Enable_State_ACD");
  chartInstance->c42_is_Aux_Relief_G5 = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 26)), "is_Aux_Relief_G5");
  chartInstance->c42_is_PHOENIX_K2 = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 27)), "is_PHOENIX_K2");
  chartInstance->c42_is_SIRIUS2_HIFLOW = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 28)), "is_SIRIUS2_HIFLOW");
  chartInstance->c42_c_is_Functional = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 29)), "is_Functional");
  chartInstance->c42_c_is_Enabled = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 30)), "is_Enabled");
  chartInstance->c42_c_is_Active = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 31)), "is_Active");
  chartInstance->c42_c_is_Aux_Enable_State_ST = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 32)),
     "is_Aux_Enable_State_ST");
  chartInstance->c42_c_is_Aux_Enable_State_ACD = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 33)),
     "is_Aux_Enable_State_ACD");
  chartInstance->c42_is_SIRIUS2 = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 34)), "is_SIRIUS2");
  chartInstance->c42_b_is_Functional = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 35)), "is_Functional");
  chartInstance->c42_b_is_Enabled = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 36)), "is_Enabled");
  chartInstance->c42_b_is_Active = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 37)), "is_Active");
  chartInstance->c42_b_is_Aux_Enable_State_ST = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 38)),
     "is_Aux_Enable_State_ST");
  chartInstance->c42_b_is_Aux_Enable_State_ACD = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 39)),
     "is_Aux_Enable_State_ACD");
  chartInstance->c42_is_Detent = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 40)), "is_Detent");
  chartInstance->c42_is_EMEA_CONTROLS = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 41)), "is_EMEA_CONTROLS");
  chartInstance->c42_d_is_Functional = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 42)), "is_Functional");
  chartInstance->c42_d_is_Enabled = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 43)), "is_Enabled");
  chartInstance->c42_d_is_Active = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 44)), "is_Active");
  chartInstance->c42_d_is_Aux_Enable_State_ST = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 45)),
     "is_Aux_Enable_State_ST");
  chartInstance->c42_d_is_Aux_Enable_State_ACD = c42_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c42_u, 46)),
     "is_Aux_Enable_State_ACD");
  chartInstance->c42_b_is_Enable = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 47)), "is_Enable");
  chartInstance->c42_b_is_Detent = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 48)), "is_Detent");
  chartInstance->c42_b_is_Active_Normal = c42_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 49)), "is_Active_Normal");
  chartInstance->c42_temporalCounter_i1 = c42_h_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 50)), "temporalCounter_i1");
  chartInstance->c42_temporalCounter_i2 = c42_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c42_u, 51)), "temporalCounter_i2");
  sf_mex_assign(&chartInstance->c42_setSimStateSideEffectsInfo,
                c42_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c42_u, 52)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c42_u);
  chartInstance->c42_doSetSimStateSideEffects = 1U;
  c42_update_debugger_state_c42_MX_Gtwy_Control(chartInstance);
  sf_mex_destroy(&c42_st);
}

static void c42_set_sim_state_side_effects_c42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  if (chartInstance->c42_doSetSimStateSideEffects != 0) {
    chartInstance->c42_tp_Aux_Enable_State = (uint8_T)
      (chartInstance->c42_is_active_Aux_Enable_State == 1U);
    chartInstance->c42_b_tp_EMEA_CONTROLS = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State == c42_IN_EMEA_CONTROLS);
    chartInstance->c42_d_tp_Aux_Enable_State_ACD = (uint8_T)
      (chartInstance->c42_is_EMEA_CONTROLS == c42_IN_Aux_Enable_State_ACD);
    chartInstance->c42_h_tp_Inactive_Latched = (uint8_T)
      (chartInstance->c42_d_is_Aux_Enable_State_ACD == c42_IN_Inactive_Latched);
    chartInstance->c42_h_tp_Inactive_Temp = (uint8_T)
      (chartInstance->c42_d_is_Aux_Enable_State_ACD == c42_IN_Inactive_Temp);
    chartInstance->c42_l_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_d_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow);
    chartInstance->c42_d_tp_Aux_Enable_State_ST = (uint8_T)
      (chartInstance->c42_is_EMEA_CONTROLS == c42_IN_Aux_Enable_State_ST);
    chartInstance->c42_g_tp_Inactive_Latched = (uint8_T)
      (chartInstance->c42_d_is_Aux_Enable_State_ST == c42_IN_Inactive_Latched);
    chartInstance->c42_g_tp_Inactive_Temp = (uint8_T)
      (chartInstance->c42_d_is_Aux_Enable_State_ST == c42_IN_Inactive_Temp);
    chartInstance->c42_k_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_d_is_Aux_Enable_State_ST == c42_IN_Standard_Flow);
    chartInstance->c42_d_tp_Functional = (uint8_T)
      (chartInstance->c42_is_EMEA_CONTROLS == c42_IN_Functional);
    chartInstance->c42_f_tp_Enabled = (uint8_T)
      (chartInstance->c42_d_is_Functional == c42_b_IN_Enabled);
    chartInstance->c42_d_tp_Active = (uint8_T)(chartInstance->c42_d_is_Enabled ==
      c42_IN_Active);
    chartInstance->c42_d_tp_Low_Flow = (uint8_T)(chartInstance->c42_d_is_Active ==
      c42_IN_Low_Flow);
    chartInstance->c42_d_tp_Medium_Flow = (uint8_T)
      (chartInstance->c42_d_is_Active == c42_IN_Medium_Flow);
    chartInstance->c42_j_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_d_is_Active == c42_IN_Standard_Flow);
    chartInstance->c42_d_tp_Off = (uint8_T)(chartInstance->c42_d_is_Enabled ==
      c42_IN_Off);
    chartInstance->c42_tp_WAIT_FOR_AUX_PRESS = (uint8_T)
      (chartInstance->c42_d_is_Enabled == c42_IN_WAIT_FOR_AUX_PRESS);
    chartInstance->c42_d_tp_Inactive = (uint8_T)
      (chartInstance->c42_d_is_Functional == c42_b_IN_Inactive);
    chartInstance->c42_d_tp_Inactive_Fault = (uint8_T)
      (chartInstance->c42_d_is_Functional == c42_b_IN_Inactive_Fault);
    chartInstance->c42_d_tp_Inactive_Out_Of_Neutral = (uint8_T)
      (chartInstance->c42_d_is_Functional == c42_b_IN_Inactive_Out_Of_Neutral);
    chartInstance->c42_b_tp_Non_Functional = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State == c42_b_IN_Non_Functional);
    chartInstance->c42_tp_PHOENIX_K2 = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State == c42_IN_PHOENIX_K2);
    chartInstance->c42_tp_Aux_Enable_State_ACD = (uint8_T)
      (chartInstance->c42_is_PHOENIX_K2 == c42_IN_Aux_Enable_State_ACD);
    chartInstance->c42_b_tp_Inactive_Latched = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State_ACD == c42_IN_Inactive_Latched);
    chartInstance->c42_b_tp_Inactive_Temp = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State_ACD == c42_IN_Inactive_Temp);
    chartInstance->c42_c_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow);
    chartInstance->c42_tp_Aux_Enable_State_ST = (uint8_T)
      (chartInstance->c42_is_PHOENIX_K2 == c42_IN_Aux_Enable_State_ST);
    chartInstance->c42_tp_Inactive_Latched = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State_ST == c42_IN_Inactive_Latched);
    chartInstance->c42_tp_Inactive_Temp = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State_ST == c42_IN_Inactive_Temp);
    chartInstance->c42_b_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State_ST == c42_IN_Standard_Flow);
    chartInstance->c42_tp_Functional = (uint8_T)
      (chartInstance->c42_is_PHOENIX_K2 == c42_IN_Functional);
    chartInstance->c42_tp_Aux_Relief_G5 = (uint8_T)
      (chartInstance->c42_is_Functional == c42_IN_Aux_Relief_G5);
    chartInstance->c42_tp_Ack = (uint8_T)(chartInstance->c42_is_Aux_Relief_G5 ==
      c42_IN_Ack);
    if (chartInstance->c42_is_Aux_Relief_G5 == c42_IN_Confirm) {
      chartInstance->c42_tp_Confirm = 1U;
      if (sf_mex_sub(chartInstance->c42_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 36) == 0.0) {
        chartInstance->c42_temporalCounter_i2 = 0U;
      }
    } else {
      chartInstance->c42_tp_Confirm = 0U;
    }

    if (chartInstance->c42_is_Aux_Relief_G5 == c42_IN_Release_Base) {
      chartInstance->c42_tp_Release_Base = 1U;
      if (sf_mex_sub(chartInstance->c42_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 37) == 0.0) {
        chartInstance->c42_temporalCounter_i2 = 0U;
      }
    } else {
      chartInstance->c42_tp_Release_Base = 0U;
    }

    if (chartInstance->c42_is_Aux_Relief_G5 == c42_IN_Release_Rod) {
      chartInstance->c42_tp_Release_Rod = 1U;
      if (sf_mex_sub(chartInstance->c42_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 38) == 0.0) {
        chartInstance->c42_temporalCounter_i2 = 0U;
      }
    } else {
      chartInstance->c42_tp_Release_Rod = 0U;
    }

    chartInstance->c42_tp_Wait = (uint8_T)(chartInstance->c42_is_Aux_Relief_G5 ==
      c42_IN_Wait);
    chartInstance->c42_c_tp_Enabled = (uint8_T)(chartInstance->c42_is_Functional
      == c42_IN_Enabled);
    chartInstance->c42_tp_Active = (uint8_T)(chartInstance->c42_is_Enabled ==
      c42_IN_Active);
    chartInstance->c42_tp_Low_Flow = (uint8_T)(chartInstance->c42_is_Active ==
      c42_IN_Low_Flow);
    chartInstance->c42_tp_Medium_Flow = (uint8_T)(chartInstance->c42_is_Active ==
      c42_IN_Medium_Flow);
    chartInstance->c42_tp_Standard_Flow = (uint8_T)(chartInstance->c42_is_Active
      == c42_IN_Standard_Flow);
    chartInstance->c42_tp_Off = (uint8_T)(chartInstance->c42_is_Enabled ==
      c42_IN_Off);
    chartInstance->c42_tp_Inactive = (uint8_T)(chartInstance->c42_is_Functional ==
      c42_IN_Inactive);
    chartInstance->c42_tp_Inactive_Fault = (uint8_T)
      (chartInstance->c42_is_Functional == c42_IN_Inactive_Fault);
    chartInstance->c42_tp_Inactive_Out_Of_Neutral = (uint8_T)
      (chartInstance->c42_is_Functional == c42_IN_Inactive_Out_Of_Neutral);
    chartInstance->c42_tp_SIRIUS2 = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State == c42_IN_SIRIUS2);
    chartInstance->c42_b_tp_Aux_Enable_State_ACD = (uint8_T)
      (chartInstance->c42_is_SIRIUS2 == c42_IN_Aux_Enable_State_ACD);
    chartInstance->c42_d_tp_Inactive_Latched = (uint8_T)
      (chartInstance->c42_b_is_Aux_Enable_State_ACD == c42_IN_Inactive_Latched);
    chartInstance->c42_d_tp_Inactive_Temp = (uint8_T)
      (chartInstance->c42_b_is_Aux_Enable_State_ACD == c42_IN_Inactive_Temp);
    chartInstance->c42_f_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_b_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow);
    chartInstance->c42_b_tp_Aux_Enable_State_ST = (uint8_T)
      (chartInstance->c42_is_SIRIUS2 == c42_IN_Aux_Enable_State_ST);
    chartInstance->c42_c_tp_Inactive_Latched = (uint8_T)
      (chartInstance->c42_b_is_Aux_Enable_State_ST == c42_IN_Inactive_Latched);
    chartInstance->c42_c_tp_Inactive_Temp = (uint8_T)
      (chartInstance->c42_b_is_Aux_Enable_State_ST == c42_IN_Inactive_Temp);
    chartInstance->c42_e_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_b_is_Aux_Enable_State_ST == c42_IN_Standard_Flow);
    chartInstance->c42_b_tp_Functional = (uint8_T)(chartInstance->c42_is_SIRIUS2
      == c42_IN_Functional);
    chartInstance->c42_d_tp_Enabled = (uint8_T)
      (chartInstance->c42_b_is_Functional == c42_b_IN_Enabled);
    chartInstance->c42_b_tp_Active = (uint8_T)(chartInstance->c42_b_is_Enabled ==
      c42_IN_Active);
    chartInstance->c42_b_tp_Low_Flow = (uint8_T)(chartInstance->c42_b_is_Active ==
      c42_IN_Low_Flow);
    chartInstance->c42_b_tp_Medium_Flow = (uint8_T)
      (chartInstance->c42_b_is_Active == c42_IN_Medium_Flow);
    chartInstance->c42_d_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_b_is_Active == c42_IN_Standard_Flow);
    chartInstance->c42_b_tp_Off = (uint8_T)(chartInstance->c42_b_is_Enabled ==
      c42_IN_Off);
    chartInstance->c42_b_tp_Inactive = (uint8_T)
      (chartInstance->c42_b_is_Functional == c42_b_IN_Inactive);
    chartInstance->c42_b_tp_Inactive_Fault = (uint8_T)
      (chartInstance->c42_b_is_Functional == c42_b_IN_Inactive_Fault);
    chartInstance->c42_b_tp_Inactive_Out_Of_Neutral = (uint8_T)
      (chartInstance->c42_b_is_Functional == c42_b_IN_Inactive_Out_Of_Neutral);
    chartInstance->c42_tp_SIRIUS2_HIFLOW = (uint8_T)
      (chartInstance->c42_is_Aux_Enable_State == c42_IN_SIRIUS2_HIFLOW);
    chartInstance->c42_c_tp_Aux_Enable_State_ACD = (uint8_T)
      (chartInstance->c42_is_SIRIUS2_HIFLOW == c42_IN_Aux_Enable_State_ACD);
    chartInstance->c42_f_tp_Inactive_Latched = (uint8_T)
      (chartInstance->c42_c_is_Aux_Enable_State_ACD == c42_IN_Inactive_Latched);
    chartInstance->c42_f_tp_Inactive_Temp = (uint8_T)
      (chartInstance->c42_c_is_Aux_Enable_State_ACD == c42_IN_Inactive_Temp);
    chartInstance->c42_i_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_c_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow);
    chartInstance->c42_c_tp_Aux_Enable_State_ST = (uint8_T)
      (chartInstance->c42_is_SIRIUS2_HIFLOW == c42_IN_Aux_Enable_State_ST);
    chartInstance->c42_e_tp_Inactive_Latched = (uint8_T)
      (chartInstance->c42_c_is_Aux_Enable_State_ST == c42_IN_Inactive_Latched);
    chartInstance->c42_e_tp_Inactive_Temp = (uint8_T)
      (chartInstance->c42_c_is_Aux_Enable_State_ST == c42_IN_Inactive_Temp);
    chartInstance->c42_h_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_c_is_Aux_Enable_State_ST == c42_IN_Standard_Flow);
    chartInstance->c42_c_tp_Functional = (uint8_T)
      (chartInstance->c42_is_SIRIUS2_HIFLOW == c42_IN_Functional);
    chartInstance->c42_e_tp_Enabled = (uint8_T)
      (chartInstance->c42_c_is_Functional == c42_b_IN_Enabled);
    chartInstance->c42_c_tp_Active = (uint8_T)(chartInstance->c42_c_is_Enabled ==
      c42_IN_Active);
    chartInstance->c42_tp_High_Flow = (uint8_T)(chartInstance->c42_c_is_Active ==
      c42_IN_High_Flow);
    chartInstance->c42_c_tp_Low_Flow = (uint8_T)(chartInstance->c42_c_is_Active ==
      c42_b_IN_Low_Flow);
    chartInstance->c42_c_tp_Medium_Flow = (uint8_T)
      (chartInstance->c42_c_is_Active == c42_b_IN_Medium_Flow);
    chartInstance->c42_g_tp_Standard_Flow = (uint8_T)
      (chartInstance->c42_c_is_Active == c42_b_IN_Standard_Flow);
    chartInstance->c42_c_tp_Off = (uint8_T)(chartInstance->c42_c_is_Enabled ==
      c42_IN_Off);
    chartInstance->c42_c_tp_Inactive = (uint8_T)
      (chartInstance->c42_c_is_Functional == c42_b_IN_Inactive);
    chartInstance->c42_c_tp_Inactive_Fault = (uint8_T)
      (chartInstance->c42_c_is_Functional == c42_b_IN_Inactive_Fault);
    chartInstance->c42_c_tp_Inactive_Out_Of_Neutral = (uint8_T)
      (chartInstance->c42_c_is_Functional == c42_b_IN_Inactive_Out_Of_Neutral);
    chartInstance->c42_tp_Detent_State = (uint8_T)
      (chartInstance->c42_is_active_Detent_State == 1U);
    chartInstance->c42_tp_EMEA_CONTROLS = (uint8_T)
      (chartInstance->c42_is_Detent_State == c42_IN_EMEA_CONTROLS);
    chartInstance->c42_tp_Enable = (uint8_T)(chartInstance->c42_is_active_Enable
      == 1U);
    chartInstance->c42_tp_Disabled = (uint8_T)(chartInstance->c42_is_Enable ==
      c42_IN_Disabled);
    chartInstance->c42_tp_Enabled = (uint8_T)(chartInstance->c42_is_Enable ==
      c42_IN_Enabled);
    chartInstance->c42_tp_Detent = (uint8_T)(chartInstance->c42_is_active_Detent
      == 1U);
    chartInstance->c42_tp_Active_Normal = (uint8_T)(chartInstance->c42_is_Detent
      == c42_IN_Active_Normal);
    chartInstance->c42_tp_Detent_Base = (uint8_T)
      (chartInstance->c42_is_Active_Normal == c42_IN_Detent_Base);
    chartInstance->c42_tp_Detent_Rod = (uint8_T)
      (chartInstance->c42_is_Active_Normal == c42_IN_Detent_Rod);
    chartInstance->c42_tp_No_Detent = (uint8_T)(chartInstance->c42_is_Detent ==
      c42_IN_No_Detent);
    if (chartInstance->c42_is_Detent == c42_IN_Not_Enabled) {
      chartInstance->c42_tp_Not_Enabled = 1U;
      if (sf_mex_sub(chartInstance->c42_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 98) == 0.0) {
        chartInstance->c42_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c42_tp_Not_Enabled = 0U;
    }

    chartInstance->c42_tp_NORMAL_CONTROLS = (uint8_T)
      (chartInstance->c42_is_Detent_State == c42_IN_NORMAL_CONTROLS);
    chartInstance->c42_b_tp_Enable = (uint8_T)
      (chartInstance->c42_b_is_active_Enable == 1U);
    chartInstance->c42_b_tp_Disabled = (uint8_T)(chartInstance->c42_b_is_Enable ==
      c42_IN_Disabled);
    chartInstance->c42_b_tp_Enabled = (uint8_T)(chartInstance->c42_b_is_Enable ==
      c42_IN_Enabled);
    chartInstance->c42_b_tp_Detent = (uint8_T)
      (chartInstance->c42_b_is_active_Detent == 1U);
    chartInstance->c42_b_tp_Active_Normal = (uint8_T)
      (chartInstance->c42_b_is_Detent == c42_IN_Active_Normal);
    chartInstance->c42_b_tp_Detent_Base = (uint8_T)
      (chartInstance->c42_b_is_Active_Normal == c42_IN_Detent_Base);
    chartInstance->c42_b_tp_Detent_Rod = (uint8_T)
      (chartInstance->c42_b_is_Active_Normal == c42_IN_Detent_Rod);
    chartInstance->c42_b_tp_No_Detent = (uint8_T)(chartInstance->c42_b_is_Detent
      == c42_IN_No_Detent);
    if (chartInstance->c42_b_is_Detent == c42_IN_Not_Enabled) {
      chartInstance->c42_b_tp_Not_Enabled = 1U;
      if (sf_mex_sub(chartInstance->c42_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 108) == 0.0) {
        chartInstance->c42_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c42_b_tp_Not_Enabled = 0U;
    }

    chartInstance->c42_tp_Non_Functional = (uint8_T)
      (chartInstance->c42_is_Detent_State == c42_IN_Non_Functional);
    chartInstance->c42_tp_Aux_Reset = (uint8_T)
      (chartInstance->c42_is_active_Aux_Reset == 1U);
    chartInstance->c42_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c42_setSimStateSideEffectsInfo);
}

static void sf_gateway_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  c42_set_sim_state_side_effects_c42_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 40U, chartInstance->c42_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_EngineSpeed, 24U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Inhibit, 23U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_mode_RightControl, 22U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_change_OffsetSelectSw, 21U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_RightPot, 20U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_button_Aux, 19U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_button_AuxReleaseExit, 18U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_button_AuxReleaseBack, 17U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_button_AuxReleaseAck, 16U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_ACD_CAN, 15U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_ST_CAN, 14U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_can_AuxEnable_ACD, 13U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_can_AuxEnable_ST, 12U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_flag_InitEERead, 11U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Buttons, 10U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_DetentHold, 9U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_System, 8U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_DebounceButton, 7U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Console, 6U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Engine, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxPot, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_DetentRisingEdge, 3U);
  chartInstance->c42_sfEvent = CALL_EVENT;
  if (chartInstance->c42_temporalCounter_i1 < MAX_uint32_T) {
    chartInstance->c42_temporalCounter_i1++;
  }

  if (chartInstance->c42_temporalCounter_i2 < 65535U) {
    chartInstance->c42_temporalCounter_i2 = c42__u16_s32_(chartInstance,
      chartInstance->c42_temporalCounter_i2 + 1, 0U, 0U, 0U);
  }

  c42_c42_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MX_Gtwy_ControlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  c42_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void c42_c42_MX_Gtwy_Control(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_out;
  int32_T c42_previousEvent;
  boolean_T c42_b_temp;
  boolean_T c42_b_out;
  int32_T c42_b_previousEvent;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 40U, chartInstance->c42_sfEvent);
  if (chartInstance->c42_is_active_c42_MX_Gtwy_Control == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 40U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_active_c42_MX_Gtwy_Control = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 40U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_active_Aux_Enable_State = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Aux_Enable_State = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_is_Aux_Enable_State == c42_b_IN_Non_Functional) {
    } else {
      chartInstance->c42_is_Aux_Enable_State = c42_b_IN_Non_Functional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Non_Functional = 1U;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    }

    chartInstance->c42_is_active_Detent_State = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 87U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Detent_State = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 225U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_is_Detent_State == c42_IN_Non_Functional) {
    } else {
      chartInstance->c42_is_Detent_State = c42_IN_Non_Functional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 108U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Non_Functional = 1U;
      *chartInstance->c42_state_DetentEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_DetentEnable, 28U);
      *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
    }

    if (chartInstance->c42_is_active_Aux_Reset == 1U) {
    } else {
      chartInstance->c42_is_active_Aux_Reset = 1U;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 86U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Aux_Reset = 1U;
      chartInstance->c42_state_ACD_old = *chartInstance->c42_state_ACD_CAN;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_state_ACD_old, 1U);
      chartInstance->c42_state_ST_old = *chartInstance->c42_state_ST_CAN;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_state_ST_old, 2U);
    }
  } else {
    if (chartInstance->c42_is_active_Aux_Enable_State == 0U) {
    } else {
      c42_Aux_Enable_State(chartInstance);
    }

    if (chartInstance->c42_is_active_Detent_State == 0U) {
    } else {
      c42_Detent_State(chartInstance);
    }

    if (chartInstance->c42_is_active_Aux_Reset == 0U) {
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 86U,
                   chartInstance->c42_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 61U, chartInstance->c42_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 63U,
                   chartInstance->c42_sfEvent);
      c42_temp = (_SFD_CCP_CALL(5U, 63U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        63U, 0, (real_T)chartInstance->c42_CD_RACD_FUNCTION, (real_T)
        chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c42_CD_RACD_FUNCTION != chartInstance->c42_NON_FUNCTIONAL)
        != 0U, chartInstance->c42_sfEvent) != 0U);
      if (c42_temp) {
        c42_temp = (_SFD_CCP_CALL(5U, 63U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          63U, 1, (real_T)*chartInstance->c42_state_ACD_CAN, (real_T)
          chartInstance->c42_state_ACD_old, 0, 1U,
          *chartInstance->c42_state_ACD_CAN != chartInstance->c42_state_ACD_old)
          != 0U, chartInstance->c42_sfEvent) != 0U);
      }

      c42_out = (CV_TRANSITION_EVAL(63U, (int32_T)c42_temp) != 0);
      if (c42_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 63U, chartInstance->c42_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 64U, chartInstance->c42_sfEvent);
        c42_previousEvent = chartInstance->c42_sfEvent;
        chartInstance->c42_sfEvent = c42_event_disable_detent;
        _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c42_event_disable_detent,
                     chartInstance->c42_sfEvent);
        if (chartInstance->c42_is_active_Detent_State == 0U) {
        } else {
          c42_Detent_State(chartInstance);
        }

        _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c42_event_disable_detent,
                     chartInstance->c42_sfEvent);
        chartInstance->c42_sfEvent = c42_previousEvent;
        chartInstance->c42_state_ACD_old = *chartInstance->c42_state_ACD_CAN;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_state_ACD_old, 1U);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 65U, chartInstance->c42_sfEvent);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 62U, chartInstance->c42_sfEvent);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 66U, chartInstance->c42_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 67U,
                   chartInstance->c42_sfEvent);
      c42_b_temp = (_SFD_CCP_CALL(5U, 67U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        67U, 0, (real_T)chartInstance->c42_CD_STAUX_FUNCTION, (real_T)
        chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c42_CD_STAUX_FUNCTION !=
        chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent) !=
                    0U);
      if (c42_b_temp) {
        c42_b_temp = (_SFD_CCP_CALL(5U, 67U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          67U, 1, (real_T)*chartInstance->c42_state_ST_CAN, (real_T)
          chartInstance->c42_state_ST_old, 0, 1U,
          *chartInstance->c42_state_ST_CAN != chartInstance->c42_state_ST_old)
          != 0U, chartInstance->c42_sfEvent) != 0U);
      }

      c42_b_out = (CV_TRANSITION_EVAL(67U, (int32_T)c42_b_temp) != 0);
      if (c42_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 67U, chartInstance->c42_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 68U, chartInstance->c42_sfEvent);
        c42_b_previousEvent = chartInstance->c42_sfEvent;
        chartInstance->c42_sfEvent = c42_event_disable_detent;
        _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c42_event_disable_detent,
                     chartInstance->c42_sfEvent);
        if (chartInstance->c42_is_active_Detent_State == 0U) {
        } else {
          c42_Detent_State(chartInstance);
        }

        _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c42_event_disable_detent,
                     chartInstance->c42_sfEvent);
        chartInstance->c42_sfEvent = c42_b_previousEvent;
        chartInstance->c42_state_ST_old = *chartInstance->c42_state_ST_CAN;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_state_ST_old, 2U);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 69U, chartInstance->c42_sfEvent);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 70U, chartInstance->c42_sfEvent);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 71U, chartInstance->c42_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 86U, chartInstance->c42_sfEvent);
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 40U, chartInstance->c42_sfEvent);
}

static void initSimStructsc42_MX_Gtwy_Control
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c42_Detent_State(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_h_temp;
  boolean_T c42_i_temp;
  boolean_T c42_out;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_g_out;
  int32_T c42_previousEvent;
  boolean_T c42_h_out;
  int32_T c42_b_previousEvent;
  boolean_T c42_i_out;
  boolean_T guard1 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 87U, chartInstance->c42_sfEvent);
  switch (chartInstance->c42_is_Detent_State) {
   case c42_IN_EMEA_CONTROLS:
    CV_STATE_EVAL(87, 0, c42_IN_EMEA_CONTROLS);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 88U,
                 chartInstance->c42_sfEvent);
    if (chartInstance->c42_is_active_Enable == 0U) {
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 95U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_is_Enable) {
       case c42_IN_Disabled:
        CV_STATE_EVAL(95, 0, c42_IN_Disabled);
        *chartInstance->c42_state_DetentEnable = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 18U,
                     chartInstance->c42_sfEvent);
        c42_temp = (_SFD_CCP_CALL(5U, 18U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          18U, 0, (real_T)*chartInstance->c42_state_AuxEnable, (real_T)
          chartInstance->c42_ACTIVE_MODE_ONE, 0, 0U,
          *chartInstance->c42_state_AuxEnable ==
          chartInstance->c42_ACTIVE_MODE_ONE) != 0U, chartInstance->c42_sfEvent)
                    != 0U);
        if (c42_temp) {
          c42_temp = (_SFD_CCP_CALL(5U, 18U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
            18U, 1, (real_T)*chartInstance->c42_aux_DetentHold, (real_T)
            chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_aux_DetentHold
            == chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
                      0U);
        }

        c42_e_temp = c42_temp;
        if (c42_temp) {
          c42_e_temp = (_SFD_CCP_CALL(5U, 18U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 18U, 2, (real_T)*chartInstance->c42_state_Buttons, (real_T)
             chartInstance->c42_NORMAL, 0, 0U, *chartInstance->c42_state_Buttons
             == chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_i_temp = c42_e_temp;
        if (c42_e_temp) {
          c42_i_temp = (_SFD_CCP_CALL(5U, 18U, 3, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 18U, 3, (real_T)*chartInstance->c42_mode_RightControl, (real_T)
             chartInstance->c42_MODE_RIGHT_AUX1, 0, 0U,
             *chartInstance->c42_mode_RightControl ==
             chartInstance->c42_MODE_RIGHT_AUX1) != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_d_out = (CV_TRANSITION_EVAL(18U, (int32_T)c42_i_temp) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c42_sfEvent);
          c42_set_state_Buzzer(chartInstance, 0,
                               chartInstance->c42_SINGLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
          chartInstance->c42_tp_Disabled = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 96U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Enable = c42_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 97U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Enabled = 1U;
          *chartInstance->c42_state_DetentEnable = chartInstance->c42_ACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_DetentEnable,
                                28U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 96U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 96U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Enabled:
        CV_STATE_EVAL(95, 0, c42_IN_Enabled);
        *chartInstance->c42_state_DetentEnable = chartInstance->c42_ACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 19U,
                     chartInstance->c42_sfEvent);
        c42_b_temp = (_SFD_CCP_CALL(5U, 19U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          19U, 0, (real_T)*chartInstance->c42_state_Buttons, (real_T)
          chartInstance->c42_NORMAL, 0, 1U, *chartInstance->c42_state_Buttons !=
          chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
        if (!c42_b_temp) {
          c42_b_temp = (_SFD_CCP_CALL(5U, 19U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 19U, 1, (real_T)*chartInstance->c42_state_AuxEnable, (real_T)
             chartInstance->c42_INACTIVE, 0, 0U,
             *chartInstance->c42_state_AuxEnable == chartInstance->c42_INACTIVE)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_f_temp = c42_b_temp;
        if (!c42_b_temp) {
          c42_f_temp = (_SFD_CCP_CALL(5U, 19U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 19U, 2, (real_T)*chartInstance->c42_state_Console, (real_T)
             chartInstance->c42_ACTIVE, 0, 1U, *chartInstance->c42_state_Console
             != chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_out = (CV_TRANSITION_EVAL(19U, (int32_T)c42_f_temp) != 0);
        guard1 = false;
        if (c42_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c42_sfEvent);
          guard1 = true;
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 44U,
                       chartInstance->c42_sfEvent);
          c42_e_out = (CV_TRANSITION_EVAL(44U, (int32_T)(_SFD_CCP_CALL(5U, 44U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 44U, 0, (real_T)
            *chartInstance->c42_aux_DetentHold, (real_T)
            chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_aux_DetentHold
            == chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
            0U)) != 0);
          if (c42_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 44U, chartInstance->c42_sfEvent);
            c42_previousEvent = chartInstance->c42_sfEvent;
            chartInstance->c42_sfEvent = c42_event_disable_aux;
            _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c42_event_disable_aux,
                         chartInstance->c42_sfEvent);
            if (chartInstance->c42_is_active_Aux_Enable_State == 0U) {
            } else {
              c42_Aux_Enable_State(chartInstance);
            }

            _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c42_event_disable_aux,
                         chartInstance->c42_sfEvent);
            chartInstance->c42_sfEvent = c42_previousEvent;
            c42_set_state_Buzzer(chartInstance, 0,
                                 chartInstance->c42_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 83U,
                         chartInstance->c42_sfEvent);
            c42_g_out = (CV_TRANSITION_EVAL(83U, (int32_T)(_SFD_CCP_CALL(5U, 83U,
              0, (chartInstance->c42_sfEvent == c42_event_disable_detent) != 0U,
              chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_g_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 83U,
                           chartInstance->c42_sfEvent);
              guard1 = true;
            } else {
              _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 212U,
                           chartInstance->c42_sfEvent);
              c42_i_out = (CV_TRANSITION_EVAL(212U, (int32_T)(_SFD_CCP_CALL(5U,
                212U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 212U, 0, (real_T)
                *chartInstance->c42_mode_RightControl, (real_T)
                chartInstance->c42_MODE_RIGHT_AUX1, 0, 1U,
                *chartInstance->c42_mode_RightControl !=
                chartInstance->c42_MODE_RIGHT_AUX1) != 0U,
                chartInstance->c42_sfEvent) != 0U)) != 0);
              if (c42_i_out) {
                _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 212U,
                             chartInstance->c42_sfEvent);
                guard1 = true;
              } else {
                _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 97U,
                             chartInstance->c42_sfEvent);
              }
            }
          }
        }

        if (guard1) {
          chartInstance->c42_tp_Enabled = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 97U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Enable = c42_IN_Disabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 96U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Disabled = 1U;
          *chartInstance->c42_state_DetentEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_DetentEnable,
                                28U);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 97U, chartInstance->c42_sfEvent);
        break;

       default:
        CV_STATE_EVAL(95, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_is_Enable = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 96U, chartInstance->c42_sfEvent);
        break;
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 95U, chartInstance->c42_sfEvent);
    }

    if (chartInstance->c42_is_active_Detent == 0U) {
    } else {
      c42_Detent(chartInstance);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 88U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_NORMAL_CONTROLS:
    CV_STATE_EVAL(87, 0, c42_IN_NORMAL_CONTROLS);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 98U,
                 chartInstance->c42_sfEvent);
    if (chartInstance->c42_b_is_active_Enable == 0U) {
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 105U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_b_is_Enable) {
       case c42_IN_Disabled:
        CV_STATE_EVAL(105, 0, c42_IN_Disabled);
        *chartInstance->c42_state_DetentEnable = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 228U,
                     chartInstance->c42_sfEvent);
        c42_c_temp = (_SFD_CCP_CALL(5U, 228U, 0, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 228U, 0, (real_T)*chartInstance->c42_state_AuxEnable, (real_T)
           chartInstance->c42_ACTIVE_MODE_ONE, 0, 0U,
           *chartInstance->c42_state_AuxEnable ==
           chartInstance->c42_ACTIVE_MODE_ONE) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
        if (c42_c_temp) {
          c42_c_temp = (_SFD_CCP_CALL(5U, 228U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 228U, 1, (real_T)*chartInstance->c42_aux_DetentHold, (real_T)
             chartInstance->c42_ACTIVE, 0, 0U,
             *chartInstance->c42_aux_DetentHold == chartInstance->c42_ACTIVE) !=
            0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_g_temp = c42_c_temp;
        if (c42_c_temp) {
          c42_g_temp = (_SFD_CCP_CALL(5U, 228U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 228U, 2, (real_T)*chartInstance->c42_state_Buttons, (real_T)
             chartInstance->c42_NORMAL, 0, 0U, *chartInstance->c42_state_Buttons
             == chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_b_out = (CV_TRANSITION_EVAL(228U, (int32_T)c42_g_temp) != 0);
        if (c42_b_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 228U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Disabled = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 106U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Enable = c42_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 107U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Enabled = 1U;
          *chartInstance->c42_state_DetentEnable = chartInstance->c42_ACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_DetentEnable,
                                28U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 106U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 106U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Enabled:
        CV_STATE_EVAL(105, 0, c42_IN_Enabled);
        *chartInstance->c42_state_DetentEnable = chartInstance->c42_ACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 229U,
                     chartInstance->c42_sfEvent);
        c42_d_temp = (_SFD_CCP_CALL(5U, 229U, 0, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 229U, 0, (real_T)*chartInstance->c42_state_Buttons, (real_T)
           chartInstance->c42_NORMAL, 0, 1U, *chartInstance->c42_state_Buttons
           != chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) !=
                      0U);
        if (!c42_d_temp) {
          c42_d_temp = (_SFD_CCP_CALL(5U, 229U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 229U, 1, (real_T)*chartInstance->c42_state_AuxEnable, (real_T)
             chartInstance->c42_INACTIVE, 0, 0U,
             *chartInstance->c42_state_AuxEnable == chartInstance->c42_INACTIVE)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_h_temp = c42_d_temp;
        if (!c42_d_temp) {
          c42_h_temp = (_SFD_CCP_CALL(5U, 229U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 229U, 2, (real_T)*chartInstance->c42_state_Console, (real_T)
             chartInstance->c42_ACTIVE, 0, 1U, *chartInstance->c42_state_Console
             != chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_c_out = (CV_TRANSITION_EVAL(229U, (int32_T)c42_h_temp) != 0);
        guard1 = false;
        if (c42_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 229U, chartInstance->c42_sfEvent);
          guard1 = true;
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 230U,
                       chartInstance->c42_sfEvent);
          c42_f_out = (CV_TRANSITION_EVAL(230U, (int32_T)(_SFD_CCP_CALL(5U, 230U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 230U, 0, (real_T)
            *chartInstance->c42_aux_DetentHold, (real_T)
            chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_aux_DetentHold
            == chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
            0U)) != 0);
          if (c42_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 230U, chartInstance->c42_sfEvent);
            c42_b_previousEvent = chartInstance->c42_sfEvent;
            chartInstance->c42_sfEvent = c42_event_disable_aux;
            _SFD_CE_CALL(EVENT_BEFORE_BROADCAST_TAG, c42_event_disable_aux,
                         chartInstance->c42_sfEvent);
            if (chartInstance->c42_is_active_Aux_Enable_State == 0U) {
            } else {
              c42_Aux_Enable_State(chartInstance);
            }

            _SFD_CE_CALL(EVENT_AFTER_BROADCAST_TAG, c42_event_disable_aux,
                         chartInstance->c42_sfEvent);
            chartInstance->c42_sfEvent = c42_b_previousEvent;
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 231U,
                         chartInstance->c42_sfEvent);
            c42_h_out = (CV_TRANSITION_EVAL(231U, (int32_T)(_SFD_CCP_CALL(5U,
              231U, 0, (chartInstance->c42_sfEvent == c42_event_disable_detent)
              != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_h_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 231U,
                           chartInstance->c42_sfEvent);
              guard1 = true;
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 107U,
                           chartInstance->c42_sfEvent);
            }
          }
        }

        if (guard1) {
          chartInstance->c42_b_tp_Enabled = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 107U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Enable = c42_IN_Disabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 106U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Disabled = 1U;
          *chartInstance->c42_state_DetentEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_DetentEnable,
                                28U);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 107U, chartInstance->c42_sfEvent);
        break;

       default:
        CV_STATE_EVAL(105, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_b_is_Enable = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 106U, chartInstance->c42_sfEvent);
        break;
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 105U, chartInstance->c42_sfEvent);
    }

    if (chartInstance->c42_b_is_active_Detent == 0U) {
    } else {
      c42_b_Detent(chartInstance);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 98U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Non_Functional:
    CV_STATE_EVAL(87, 0, c42_IN_Non_Functional);
    c42_Non_Functional(chartInstance);
    break;

   default:
    CV_STATE_EVAL(87, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c42_is_Detent_State = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 88U, chartInstance->c42_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 87U, chartInstance->c42_sfEvent);
}

static void c42_Non_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_b_out;
  *chartInstance->c42_state_DetentEnable = chartInstance->c42_INACTIVE;
  *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 226U, chartInstance->c42_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 224U,
               chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(224U, (int32_T)(_SFD_CCP_CALL(5U, 224U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 224U, 0, (real_T)
    chartInstance->c42_CD_RIGHT_POT_FUNCTION, (real_T)
    chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
    chartInstance->c42_CD_RIGHT_POT_FUNCTION !=
    chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent) != 0U))
             != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 224U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Non_Functional = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 108U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_Detent_State = c42_IN_EMEA_CONTROLS;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 88U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_EMEA_CONTROLS = 1U;
    chartInstance->c42_is_active_Enable = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 95U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Enable = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_is_Enable == c42_IN_Disabled) {
    } else {
      chartInstance->c42_is_Enable = c42_IN_Disabled;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 96U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Disabled = 1U;
      *chartInstance->c42_state_DetentEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_DetentEnable, 28U);
    }

    chartInstance->c42_is_active_Detent = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 89U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Detent = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_is_Detent == c42_IN_No_Detent) {
    } else {
      chartInstance->c42_is_Detent = c42_IN_No_Detent;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_No_Detent = 1U;
      *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
    }
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 243U,
                 chartInstance->c42_sfEvent);
    c42_b_out = (CV_TRANSITION_EVAL(243U, (int32_T)(_SFD_CCP_CALL(5U, 243U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 243U, 0, (real_T)
      chartInstance->c42_CD_AUX_FUNCTION, (real_T)
      chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c42_CD_AUX_FUNCTION != chartInstance->c42_NON_FUNCTIONAL)
      != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 243U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Non_Functional = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 108U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_Detent_State = c42_IN_NORMAL_CONTROLS;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 98U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_NORMAL_CONTROLS = 1U;
      chartInstance->c42_b_is_active_Enable = 1U;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 105U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Enable = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 227U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_b_is_Enable == c42_IN_Disabled) {
      } else {
        chartInstance->c42_b_is_Enable = c42_IN_Disabled;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 106U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_Disabled = 1U;
        *chartInstance->c42_state_DetentEnable = chartInstance->c42_INACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_DetentEnable,
                              28U);
      }

      chartInstance->c42_b_is_active_Detent = 1U;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 99U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Detent = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 232U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_b_is_Detent == c42_IN_No_Detent) {
      } else {
        chartInstance->c42_b_is_Detent = c42_IN_No_Detent;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_No_Detent = 1U;
        *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 108U,
                   chartInstance->c42_sfEvent);
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 108U, chartInstance->c42_sfEvent);
}

static void c42_Detent(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  uint32_T c42_u0;
  boolean_T c42_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_b_out;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_h_temp;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_i_temp;
  boolean_T c42_f_out;
  boolean_T c42_g_out;
  boolean_T c42_h_out;
  boolean_T c42_j_temp;
  boolean_T c42_k_temp;
  boolean_T c42_l_temp;
  boolean_T c42_i_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 89U, chartInstance->c42_sfEvent);
  switch (chartInstance->c42_is_Detent) {
   case c42_IN_Active_Normal:
    CV_STATE_EVAL(89, 0, c42_IN_Active_Normal);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 13U, 0,
      (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
      chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 13U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        13U, 0, (real_T)*chartInstance->c42_state_DetentEnable, (real_T)
        chartInstance->c42_INACTIVE, 0, 0U,
        *chartInstance->c42_state_DetentEnable == chartInstance->c42_INACTIVE)
        != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_c_temp = c42_temp;
    if (!c42_temp) {
      c42_c_temp = (_SFD_CCP_CALL(5U, 13U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        13U, 1, (real_T)*chartInstance->c42_state_AuxEnable, (real_T)
        chartInstance->c42_INACTIVE, 0, 0U, *chartInstance->c42_state_AuxEnable ==
        chartInstance->c42_INACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(13U, (int32_T)c42_c_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
      c42_exit_internal_Active_Normal(chartInstance);
      chartInstance->c42_tp_Active_Normal = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 90U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_Detent = c42_IN_No_Detent;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_No_Detent = 1U;
      *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 90U, chartInstance->c42_sfEvent);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 90U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_is_Active_Normal) {
       case c42_IN_Detent_Base:
        CV_STATE_EVAL(90, 0, c42_IN_Detent_Base);
        *chartInstance->c42_state_Detent = chartInstance->c42_BASE_DETENT;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 16U,
                     chartInstance->c42_sfEvent);
        c42_g_temp = (_SFD_CCP_CALL(5U, 16U, 0,
          (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (c42_g_temp) {
          c42_g_temp = (_SFD_CCP_CALL(5U, 16U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 16U, 0, (real_T)*chartInstance->c42_state_RightPot, (real_T)
             chartInstance->c42_ROD_ACTIVE, 0, 0U,
             *chartInstance->c42_state_RightPot == chartInstance->c42_ROD_ACTIVE)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_d_out = (CV_TRANSITION_EVAL(16U, (int32_T)c42_g_temp) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Detent_Base = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 91U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Active_Normal = c42_IN_Detent_Rod;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 92U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Detent_Rod = 1U;
          *chartInstance->c42_state_Detent = chartInstance->c42_ROD_DETENT;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                       chartInstance->c42_sfEvent);
          c42_g_out = (CV_TRANSITION_EVAL(10U, (int32_T)(_SFD_CCP_CALL(5U, 10U,
            0, (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U)) != 0);
          if (c42_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_Detent_Base = 0U;
            chartInstance->c42_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 91U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_Active_Normal = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 90U, chartInstance->c42_sfEvent);
            chartInstance->c42_is_Detent = c42_IN_No_Detent;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_No_Detent = 1U;
            *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 91U,
                         chartInstance->c42_sfEvent);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 91U, chartInstance->c42_sfEvent);
        if (chartInstance->c42_is_Detent != c42_IN_Active_Normal) {
        } else {
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 90U, chartInstance->c42_sfEvent);
        }
        break;

       case c42_IN_Detent_Rod:
        CV_STATE_EVAL(90, 0, c42_IN_Detent_Rod);
        *chartInstance->c42_state_Detent = chartInstance->c42_ROD_DETENT;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                     chartInstance->c42_sfEvent);
        c42_h_temp = (_SFD_CCP_CALL(5U, 15U, 0,
          (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (c42_h_temp) {
          c42_h_temp = (_SFD_CCP_CALL(5U, 15U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 15U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_BASE_ACTIVE, 0, 0U,
             *chartInstance->c42_state_AuxPot == chartInstance->c42_BASE_ACTIVE)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_e_out = (CV_TRANSITION_EVAL(15U, (int32_T)c42_h_temp) != 0);
        if (c42_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Detent_Rod = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 92U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Active_Normal = c42_IN_Detent_Base;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 91U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Detent_Base = 1U;
          *chartInstance->c42_state_Detent = chartInstance->c42_BASE_DETENT;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 12U,
                       chartInstance->c42_sfEvent);
          c42_h_out = (CV_TRANSITION_EVAL(12U, (int32_T)(_SFD_CCP_CALL(5U, 12U,
            0, (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U)) != 0);
          if (c42_h_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_Detent_Rod = 0U;
            chartInstance->c42_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 92U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_Active_Normal = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 90U, chartInstance->c42_sfEvent);
            chartInstance->c42_is_Detent = c42_IN_No_Detent;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_No_Detent = 1U;
            *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 92U,
                         chartInstance->c42_sfEvent);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 92U, chartInstance->c42_sfEvent);
        if (chartInstance->c42_is_Detent != c42_IN_Active_Normal) {
        } else {
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 90U, chartInstance->c42_sfEvent);
        }
        break;

       default:
        CV_STATE_EVAL(90, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 91U, chartInstance->c42_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 90U, chartInstance->c42_sfEvent);
        break;
      }
    }
    break;

   case c42_IN_No_Detent:
    CV_STATE_EVAL(89, 0, c42_IN_No_Detent);
    *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                 chartInstance->c42_sfEvent);
    c42_b_temp = (_SFD_CCP_CALL(5U, 11U, 0,
      (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
      chartInstance->c42_sfEvent) != 0U);
    if (c42_b_temp) {
      c42_b_temp = (_SFD_CCP_CALL(5U, 11U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        11U, 0, (real_T)*chartInstance->c42_mode_RightControl, (real_T)
        chartInstance->c42_MODE_RIGHT_AUX1, 0, 0U,
        *chartInstance->c42_mode_RightControl ==
        chartInstance->c42_MODE_RIGHT_AUX1) != 0U, chartInstance->c42_sfEvent)
                    != 0U);
    }

    c42_d_temp = c42_b_temp;
    if (c42_b_temp) {
      c42_d_temp = (_SFD_CCP_CALL(5U, 11U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        11U, 1, (real_T)*chartInstance->c42_state_DetentEnable, (real_T)
        chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_state_DetentEnable
        == chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_e_temp = c42_d_temp;
    if (c42_d_temp) {
      c42_e_temp = (_SFD_CCP_CALL(5U, 11U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
        11U, 2, (real_T)*chartInstance->c42_state_AuxEnable, (real_T)
        chartInstance->c42_ACTIVE_MODE_ONE, 0, 0U,
        *chartInstance->c42_state_AuxEnable ==
        chartInstance->c42_ACTIVE_MODE_ONE) != 0U, chartInstance->c42_sfEvent)
                    != 0U);
    }

    c42_f_temp = c42_e_temp;
    if (c42_e_temp) {
      c42_f_temp = (_SFD_CCP_CALL(5U, 11U, 4, (boolean_T)CV_RELATIONAL_EVAL(5U,
        11U, 3, (real_T)*chartInstance->c42_state_RightPot, (real_T)
        chartInstance->c42_NOT_IN_NEUTRAL, 0, 1U,
        *chartInstance->c42_state_RightPot != chartInstance->c42_NOT_IN_NEUTRAL)
        != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_c_out = (CV_TRANSITION_EVAL(11U, (int32_T)c42_f_temp) != 0);
    if (c42_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 17U,
                   chartInstance->c42_sfEvent);
      c42_f_out = (CV_TRANSITION_EVAL(17U, (int32_T)(_SFD_CCP_CALL(5U, 17U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 17U, 0, (real_T)
        *chartInstance->c42_state_RightPot, (real_T)
        chartInstance->c42_ROD_ACTIVE, 0, 0U, *chartInstance->c42_state_RightPot
        == chartInstance->c42_ROD_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
        0U)) != 0);
      if (c42_f_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_No_Detent = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Detent = c42_IN_Active_Normal;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 90U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Active_Normal = 1U;
        if (chartInstance->c42_is_Active_Normal == c42_IN_Detent_Rod) {
        } else {
          chartInstance->c42_is_Active_Normal = c42_IN_Detent_Rod;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 92U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Detent_Rod = 1U;
          *chartInstance->c42_state_Detent = chartInstance->c42_ROD_DETENT;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
        }
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_No_Detent = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Detent = c42_IN_Active_Normal;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 90U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Active_Normal = 1U;
        if (chartInstance->c42_is_Active_Normal == c42_IN_Detent_Base) {
        } else {
          chartInstance->c42_is_Active_Normal = c42_IN_Detent_Base;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 91U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Detent_Base = 1U;
          *chartInstance->c42_state_Detent = chartInstance->c42_BASE_DETENT;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
        }
      }
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 21U,
                   chartInstance->c42_sfEvent);
      c42_i_temp = (_SFD_CCP_CALL(5U, 21U, 0,
        (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U);
      if (c42_i_temp) {
        c42_i_temp = (_SFD_CCP_CALL(5U, 21U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          21U, 0, (real_T)*chartInstance->c42_mode_RightControl, (real_T)
          chartInstance->c42_MODE_RIGHT_AUX1, 0, 0U,
          *chartInstance->c42_mode_RightControl ==
          chartInstance->c42_MODE_RIGHT_AUX1) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
      }

      c42_j_temp = c42_i_temp;
      if (c42_i_temp) {
        c42_j_temp = (_SFD_CCP_CALL(5U, 21U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
          21U, 1, (real_T)*chartInstance->c42_state_DetentEnable, (real_T)
          chartInstance->c42_INACTIVE, 0, 0U,
          *chartInstance->c42_state_DetentEnable == chartInstance->c42_INACTIVE)
          != 0U, chartInstance->c42_sfEvent) != 0U);
      }

      c42_k_temp = c42_j_temp;
      if (c42_j_temp) {
        c42_k_temp = (_SFD_CCP_CALL(5U, 21U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
          21U, 2, (real_T)*chartInstance->c42_state_AuxEnable, (real_T)
          chartInstance->c42_ACTIVE_MODE_ONE, 0, 0U,
          *chartInstance->c42_state_AuxEnable ==
          chartInstance->c42_ACTIVE_MODE_ONE) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
      }

      c42_l_temp = c42_k_temp;
      if (c42_k_temp) {
        c42_l_temp = (_SFD_CCP_CALL(5U, 21U, 4, (boolean_T)CV_RELATIONAL_EVAL(5U,
          21U, 3, (real_T)*chartInstance->c42_state_RightPot, (real_T)
          chartInstance->c42_NOT_IN_NEUTRAL, 0, 1U,
          *chartInstance->c42_state_RightPot !=
          chartInstance->c42_NOT_IN_NEUTRAL) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
      }

      c42_i_out = (CV_TRANSITION_EVAL(21U, (int32_T)c42_l_temp) != 0);
      if (c42_i_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_No_Detent = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Detent = c42_IN_Not_Enabled;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 94U, chartInstance->c42_sfEvent);
        chartInstance->c42_temporalCounter_i1 = 0U;
        chartInstance->c42_tp_Not_Enabled = 1U;
        *chartInstance->c42_state_Detent = chartInstance->c42_ERR_DETENT;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_DOUBLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 93U,
                     chartInstance->c42_sfEvent);
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 93U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Not_Enabled:
    CV_STATE_EVAL(89, 0, c42_IN_Not_Enabled);
    *chartInstance->c42_state_Detent = chartInstance->c42_ERR_DETENT;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 22U,
                 chartInstance->c42_sfEvent);
    c42_u0 = _SFD_TRANS_TEMPORAL_THRESHOLD(c42__u32_s32_(chartInstance,
      chartInstance->c42_CD_AUX_DETENT_FLASH_TIME * 10, 290U, 1U, 5U), 32U, 22U);
    c42_out = (CV_TRANSITION_EVAL(22U, (int32_T)(_SFD_CCP_CALL(5U, 22U, 0,
      (chartInstance->c42_temporalCounter_i1 >= c42_u0) != 0U,
      chartInstance->c42_sfEvent) != 0U)) != 0);
    if (c42_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 22U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Not_Enabled = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 94U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_Detent = c42_IN_No_Detent;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_No_Detent = 1U;
      *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 94U,
                   chartInstance->c42_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 94U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(89, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c42_is_Detent = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 90U, chartInstance->c42_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 89U, chartInstance->c42_sfEvent);
}

static void c42_exit_internal_Active_Normal(SFc42_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  switch (chartInstance->c42_is_Active_Normal) {
   case c42_IN_Detent_Base:
    CV_STATE_EVAL(90, 1, c42_IN_Detent_Base);
    chartInstance->c42_tp_Detent_Base = 0U;
    chartInstance->c42_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 91U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Detent_Rod:
    CV_STATE_EVAL(90, 1, c42_IN_Detent_Rod);
    chartInstance->c42_tp_Detent_Rod = 0U;
    chartInstance->c42_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 92U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(90, 1, 0);
    chartInstance->c42_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 91U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_b_Detent(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  uint32_T c42_u1;
  boolean_T c42_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_b_out;
  boolean_T c42_e_temp;
  boolean_T c42_c_out;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_h_temp;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_i_temp;
  boolean_T c42_g_out;
  boolean_T c42_h_out;
  boolean_T c42_j_temp;
  boolean_T c42_i_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 99U, chartInstance->c42_sfEvent);
  switch (chartInstance->c42_b_is_Detent) {
   case c42_IN_Active_Normal:
    CV_STATE_EVAL(99, 0, c42_IN_Active_Normal);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 238U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 238U, 0,
      (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
      chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 238U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        238U, 0, (real_T)*chartInstance->c42_state_DetentEnable, (real_T)
        chartInstance->c42_INACTIVE, 0, 0U,
        *chartInstance->c42_state_DetentEnable == chartInstance->c42_INACTIVE)
        != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_c_temp = c42_temp;
    if (!c42_temp) {
      c42_c_temp = (_SFD_CCP_CALL(5U, 238U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        238U, 1, (real_T)*chartInstance->c42_state_AuxEnable, (real_T)
        chartInstance->c42_INACTIVE, 0, 0U, *chartInstance->c42_state_AuxEnable ==
        chartInstance->c42_INACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(238U, (int32_T)c42_c_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 238U, chartInstance->c42_sfEvent);
      c42_b_exit_internal_Active_Normal(chartInstance);
      chartInstance->c42_b_tp_Active_Normal = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 100U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_is_Detent = c42_IN_No_Detent;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_No_Detent = 1U;
      *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 100U, chartInstance->c42_sfEvent);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 100U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_b_is_Active_Normal) {
       case c42_IN_Detent_Base:
        CV_STATE_EVAL(100, 0, c42_IN_Detent_Base);
        *chartInstance->c42_state_Detent = chartInstance->c42_BASE_DETENT;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 241U,
                     chartInstance->c42_sfEvent);
        c42_f_temp = (_SFD_CCP_CALL(5U, 241U, 0,
          (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (c42_f_temp) {
          c42_f_temp = (_SFD_CCP_CALL(5U, 241U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 241U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_ROD_ACTIVE, 0, 0U,
             *chartInstance->c42_state_AuxPot == chartInstance->c42_ROD_ACTIVE)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_e_out = (CV_TRANSITION_EVAL(241U, (int32_T)c42_f_temp) != 0);
        if (c42_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 241U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Detent_Base = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 101U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Active_Normal = c42_IN_Detent_Rod;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 102U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Detent_Rod = 1U;
          *chartInstance->c42_state_Detent = chartInstance->c42_ROD_DETENT;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 233U,
                       chartInstance->c42_sfEvent);
          c42_g_out = (CV_TRANSITION_EVAL(233U, (int32_T)(_SFD_CCP_CALL(5U, 233U,
            0, (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U)) != 0);
          if (c42_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 233U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_Detent_Base = 0U;
            chartInstance->c42_b_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 101U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_Active_Normal = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 100U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_is_Detent = c42_IN_No_Detent;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_No_Detent = 1U;
            *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 101U,
                         chartInstance->c42_sfEvent);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 101U, chartInstance->c42_sfEvent);
        if (chartInstance->c42_b_is_Detent != c42_IN_Active_Normal) {
        } else {
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 100U,
                       chartInstance->c42_sfEvent);
        }
        break;

       case c42_IN_Detent_Rod:
        CV_STATE_EVAL(100, 0, c42_IN_Detent_Rod);
        *chartInstance->c42_state_Detent = chartInstance->c42_ROD_DETENT;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 240U,
                     chartInstance->c42_sfEvent);
        c42_g_temp = (_SFD_CCP_CALL(5U, 240U, 0,
          (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (c42_g_temp) {
          c42_g_temp = (_SFD_CCP_CALL(5U, 240U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 240U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_BASE_ACTIVE, 0, 0U,
             *chartInstance->c42_state_AuxPot == chartInstance->c42_BASE_ACTIVE)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_f_out = (CV_TRANSITION_EVAL(240U, (int32_T)c42_g_temp) != 0);
        if (c42_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 240U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Detent_Rod = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 102U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Active_Normal = c42_IN_Detent_Base;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 101U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Detent_Base = 1U;
          *chartInstance->c42_state_Detent = chartInstance->c42_BASE_DETENT;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 237U,
                       chartInstance->c42_sfEvent);
          c42_h_out = (CV_TRANSITION_EVAL(237U, (int32_T)(_SFD_CCP_CALL(5U, 237U,
            0, (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U)) != 0);
          if (c42_h_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 237U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_Detent_Rod = 0U;
            chartInstance->c42_b_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 102U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_Active_Normal = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 100U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_is_Detent = c42_IN_No_Detent;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_No_Detent = 1U;
            *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 102U,
                         chartInstance->c42_sfEvent);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 102U, chartInstance->c42_sfEvent);
        if (chartInstance->c42_b_is_Detent != c42_IN_Active_Normal) {
        } else {
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 100U,
                       chartInstance->c42_sfEvent);
        }
        break;

       default:
        CV_STATE_EVAL(100, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_b_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 101U, chartInstance->c42_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 100U, chartInstance->c42_sfEvent);
        break;
      }
    }
    break;

   case c42_IN_No_Detent:
    CV_STATE_EVAL(99, 0, c42_IN_No_Detent);
    *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 235U,
                 chartInstance->c42_sfEvent);
    c42_b_temp = (_SFD_CCP_CALL(5U, 235U, 0,
      (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
      chartInstance->c42_sfEvent) != 0U);
    if (c42_b_temp) {
      c42_b_temp = (_SFD_CCP_CALL(5U, 235U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        235U, 0, (real_T)*chartInstance->c42_state_DetentEnable, (real_T)
        chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_state_DetentEnable
        == chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_d_temp = c42_b_temp;
    if (c42_b_temp) {
      c42_d_temp = (_SFD_CCP_CALL(5U, 235U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        235U, 1, (real_T)*chartInstance->c42_state_AuxEnable, (real_T)
        chartInstance->c42_ACTIVE_MODE_ONE, 0, 0U,
        *chartInstance->c42_state_AuxEnable ==
        chartInstance->c42_ACTIVE_MODE_ONE) != 0U, chartInstance->c42_sfEvent)
                    != 0U);
    }

    c42_e_temp = c42_d_temp;
    if (c42_d_temp) {
      c42_e_temp = (_SFD_CCP_CALL(5U, 235U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
        235U, 2, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
        chartInstance->c42_NOT_IN_NEUTRAL, 0, 1U,
        *chartInstance->c42_state_AuxPot != chartInstance->c42_NOT_IN_NEUTRAL)
        != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_c_out = (CV_TRANSITION_EVAL(235U, (int32_T)c42_e_temp) != 0);
    if (c42_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 235U, chartInstance->c42_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 242U,
                   chartInstance->c42_sfEvent);
      c42_d_out = (CV_TRANSITION_EVAL(242U, (int32_T)(_SFD_CCP_CALL(5U, 242U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 242U, 0, (real_T)
        *chartInstance->c42_state_AuxPot, (real_T)chartInstance->c42_ROD_ACTIVE,
        0, 0U, *chartInstance->c42_state_AuxPot == chartInstance->c42_ROD_ACTIVE)
        != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 242U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_No_Detent = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_is_Detent = c42_IN_Active_Normal;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 100U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_Active_Normal = 1U;
        if (chartInstance->c42_b_is_Active_Normal == c42_IN_Detent_Rod) {
        } else {
          chartInstance->c42_b_is_Active_Normal = c42_IN_Detent_Rod;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 102U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Detent_Rod = 1U;
          *chartInstance->c42_state_Detent = chartInstance->c42_ROD_DETENT;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
        }
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 239U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_No_Detent = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_is_Detent = c42_IN_Active_Normal;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 100U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_Active_Normal = 1U;
        if (chartInstance->c42_b_is_Active_Normal == c42_IN_Detent_Base) {
        } else {
          chartInstance->c42_b_is_Active_Normal = c42_IN_Detent_Base;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 101U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Detent_Base = 1U;
          *chartInstance->c42_state_Detent = chartInstance->c42_BASE_DETENT;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
        }
      }
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 234U,
                   chartInstance->c42_sfEvent);
      c42_h_temp = (_SFD_CCP_CALL(5U, 234U, 0,
        (*chartInstance->c42_DetentRisingEdge != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U);
      if (c42_h_temp) {
        c42_h_temp = (_SFD_CCP_CALL(5U, 234U, 1, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 234U, 0, (real_T)*chartInstance->c42_state_DetentEnable, (real_T)
           chartInstance->c42_INACTIVE, 0, 0U,
           *chartInstance->c42_state_DetentEnable == chartInstance->c42_INACTIVE)
          != 0U, chartInstance->c42_sfEvent) != 0U);
      }

      c42_i_temp = c42_h_temp;
      if (c42_h_temp) {
        c42_i_temp = (_SFD_CCP_CALL(5U, 234U, 2, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 234U, 1, (real_T)*chartInstance->c42_state_AuxEnable, (real_T)
           chartInstance->c42_ACTIVE_MODE_ONE, 0, 0U,
           *chartInstance->c42_state_AuxEnable ==
           chartInstance->c42_ACTIVE_MODE_ONE) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
      }

      c42_j_temp = c42_i_temp;
      if (c42_i_temp) {
        c42_j_temp = (_SFD_CCP_CALL(5U, 234U, 3, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 234U, 2, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
           chartInstance->c42_NOT_IN_NEUTRAL, 0, 1U,
           *chartInstance->c42_state_AuxPot != chartInstance->c42_NOT_IN_NEUTRAL)
          != 0U, chartInstance->c42_sfEvent) != 0U);
      }

      c42_i_out = (CV_TRANSITION_EVAL(234U, (int32_T)c42_j_temp) != 0);
      if (c42_i_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 234U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_No_Detent = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_is_Detent = c42_IN_Not_Enabled;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 104U, chartInstance->c42_sfEvent);
        chartInstance->c42_temporalCounter_i1 = 0U;
        chartInstance->c42_b_tp_Not_Enabled = 1U;
        *chartInstance->c42_state_Detent = chartInstance->c42_ERR_DETENT;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_DOUBLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 103U,
                     chartInstance->c42_sfEvent);
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 103U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Not_Enabled:
    CV_STATE_EVAL(99, 0, c42_IN_Not_Enabled);
    *chartInstance->c42_state_Detent = chartInstance->c42_ERR_DETENT;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 236U,
                 chartInstance->c42_sfEvent);
    c42_u1 = _SFD_TRANS_TEMPORAL_THRESHOLD(c42__u32_s32_(chartInstance,
      chartInstance->c42_CD_AUX_DETENT_FLASH_TIME * 10, 1315U, 1U, 5U), 32U,
      236U);
    c42_out = (CV_TRANSITION_EVAL(236U, (int32_T)(_SFD_CCP_CALL(5U, 236U, 0,
      (chartInstance->c42_temporalCounter_i1 >= c42_u1) != 0U,
      chartInstance->c42_sfEvent) != 0U)) != 0);
    if (c42_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 236U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Not_Enabled = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 104U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_is_Detent = c42_IN_No_Detent;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_No_Detent = 1U;
      *chartInstance->c42_state_Detent = chartInstance->c42_NO_DETENT;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_Detent, 26U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 104U,
                   chartInstance->c42_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 104U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(99, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c42_b_is_Detent = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 100U, chartInstance->c42_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 99U, chartInstance->c42_sfEvent);
}

static void c42_b_exit_internal_Active_Normal
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c42_b_is_Active_Normal) {
   case c42_IN_Detent_Base:
    CV_STATE_EVAL(100, 1, c42_IN_Detent_Base);
    chartInstance->c42_b_tp_Detent_Base = 0U;
    chartInstance->c42_b_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 101U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Detent_Rod:
    CV_STATE_EVAL(100, 1, c42_IN_Detent_Rod);
    chartInstance->c42_b_tp_Detent_Rod = 0U;
    chartInstance->c42_b_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 102U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(100, 1, 0);
    chartInstance->c42_b_is_Active_Normal = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 101U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_Aux_Enable_State(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c42_sfEvent);
  switch (chartInstance->c42_is_Aux_Enable_State) {
   case c42_IN_EMEA_CONTROLS:
    CV_STATE_EVAL(0, 0, c42_IN_EMEA_CONTROLS);
    c42_EMEA_CONTROLS(chartInstance);
    break;

   case c42_b_IN_Non_Functional:
    CV_STATE_EVAL(0, 0, c42_b_IN_Non_Functional);
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 177U,
                 chartInstance->c42_sfEvent);
    c42_out = (CV_TRANSITION_EVAL(177U, (int32_T)(_SFD_CCP_CALL(5U, 177U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 177U, 0, (real_T)
      chartInstance->c42_CD_AUX_FUNCTION, (real_T)
      chartInstance->c42_AUX_EMEA_CONTROLS, 0, 0U,
      chartInstance->c42_CD_AUX_FUNCTION == chartInstance->c42_AUX_EMEA_CONTROLS)
      != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
    if (c42_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 177U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Non_Functional = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_Aux_Enable_State = c42_IN_EMEA_CONTROLS;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_EMEA_CONTROLS = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 178U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_is_EMEA_CONTROLS == c42_IN_Functional) {
      } else {
        chartInstance->c42_is_EMEA_CONTROLS = c42_IN_Functional;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c42_sfEvent);
        chartInstance->c42_d_tp_Functional = 1U;
        chartInstance->c42_previouslyActive = false;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_previouslyActive, 0U);
      }

      c42_d_enter_internal_Functional(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                   chartInstance->c42_sfEvent);
      c42_b_out = (CV_TRANSITION_EVAL(1U, (int32_T)(_SFD_CCP_CALL(5U, 1U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 1U, 0, (real_T)
        chartInstance->c42_CD_AUX_FUNCTION, (real_T)
        chartInstance->c42_AUX_PHOENIX_K2, 0, 0U,
        chartInstance->c42_CD_AUX_FUNCTION == chartInstance->c42_AUX_PHOENIX_K2)
        != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_Non_Functional = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Aux_Enable_State = c42_IN_PHOENIX_K2;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_PHOENIX_K2 = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 84U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_PHOENIX_K2 = c42_IN_Functional;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Functional = 1U;
        c42_enter_internal_Functional(chartInstance);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 127U,
                     chartInstance->c42_sfEvent);
        c42_c_out = (CV_TRANSITION_EVAL(127U, (int32_T)(_SFD_CCP_CALL(5U, 127U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 127U, 0, (real_T)
          chartInstance->c42_CD_AUX_FUNCTION, (real_T)
          chartInstance->c42_AUX_SIRIUS2, 0, 0U,
          chartInstance->c42_CD_AUX_FUNCTION == chartInstance->c42_AUX_SIRIUS2)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 127U, chartInstance->c42_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 128U,
                       chartInstance->c42_sfEvent);
          c42_d_out = (CV_TRANSITION_EVAL(128U, (int32_T)(_SFD_CCP_CALL(5U, 128U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 128U, 0, (real_T)
            chartInstance->c42_CD_AUX_HIGH_FLOW, (real_T)
            chartInstance->c42_NON_FUNCTIONAL, 0, 0U,
            chartInstance->c42_CD_AUX_HIGH_FLOW ==
            chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent)
            != 0U)) != 0);
          if (c42_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 128U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_Non_Functional = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c42_sfEvent);
            chartInstance->c42_is_Aux_Enable_State = c42_IN_SIRIUS2;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 47U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_SIRIUS2 = 1U;
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 134U, chartInstance->c42_sfEvent);
            chartInstance->c42_is_SIRIUS2 = c42_IN_Functional;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 56U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_Functional = 1U;
            c42_b_enter_internal_Functional(chartInstance);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 129U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_Non_Functional = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c42_sfEvent);
            chartInstance->c42_is_Aux_Enable_State = c42_IN_SIRIUS2_HIFLOW;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 66U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_SIRIUS2_HIFLOW = 1U;
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 85U, chartInstance->c42_sfEvent);
            chartInstance->c42_is_SIRIUS2_HIFLOW = c42_IN_Functional;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 75U, chartInstance->c42_sfEvent);
            chartInstance->c42_c_tp_Functional = 1U;
            c42_c_enter_internal_Functional(chartInstance);
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 21U,
                       chartInstance->c42_sfEvent);
        }
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_PHOENIX_K2:
    CV_STATE_EVAL(0, 0, c42_IN_PHOENIX_K2);
    c42_PHOENIX_K2(chartInstance);
    break;

   case c42_IN_SIRIUS2:
    CV_STATE_EVAL(0, 0, c42_IN_SIRIUS2);
    c42_SIRIUS2(chartInstance);
    break;

   case c42_IN_SIRIUS2_HIFLOW:
    CV_STATE_EVAL(0, 0, c42_IN_SIRIUS2_HIFLOW);
    c42_SIRIUS2_HIFLOW(chartInstance);
    break;

   default:
    CV_STATE_EVAL(0, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c42_is_Aux_Enable_State = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c42_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c42_sfEvent);
}

static void c42_PHOENIX_K2(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_h_temp;
  boolean_T c42_i_temp;
  boolean_T c42_j_temp;
  boolean_T c42_k_temp;
  boolean_T c42_l_temp;
  boolean_T c42_g_out;
  boolean_T c42_h_out;
  boolean_T c42_i_out;
  boolean_T c42_j_out;
  boolean_T guard1 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 22U, chartInstance->c42_sfEvent);
  switch (chartInstance->c42_is_PHOENIX_K2) {
   case c42_IN_Aux_Enable_State_ACD:
    CV_STATE_EVAL(22, 0, c42_IN_Aux_Enable_State_ACD);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 60U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 60U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 60U,
      0, (real_T)*chartInstance->c42_can_AuxEnable_ACD, (real_T)
      chartInstance->c42_INACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ACD ==
      chartInstance->c42_INACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 60U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        60U, 1, (real_T)*chartInstance->c42_state_ACD_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 1U, *chartInstance->c42_state_ACD_CAN !=
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_out = (CV_TRANSITION_EVAL(60U, (int32_T)c42_temp) != 0);
    if (c42_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 60U, chartInstance->c42_sfEvent);
      c42_exit_internal_Aux_Enable_State_ACD(chartInstance);
      chartInstance->c42_tp_Aux_Enable_State_ACD = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_PHOENIX_K2 = c42_IN_Functional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Functional = 1U;
      c42_enter_internal_Functional(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 23U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_is_Aux_Enable_State_ACD) {
       case c42_IN_Inactive_Latched:
        CV_STATE_EVAL(23, 0, c42_IN_Inactive_Latched);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 24U,
                     chartInstance->c42_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 24U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Inactive_Temp:
        CV_STATE_EVAL(23, 0, c42_IN_Inactive_Temp);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 56U,
                     chartInstance->c42_sfEvent);
        c42_c_out = (CV_TRANSITION_EVAL(56U, (int32_T)(_SFD_CCP_CALL(5U, 56U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 56U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 1U,
          *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 56U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Inactive_Temp = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Aux_Enable_State_ACD = c42_IN_Standard_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Standard_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 25U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 25U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Standard_Flow:
        CV_STATE_EVAL(23, 0, c42_IN_Standard_Flow);
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 54U,
                     chartInstance->c42_sfEvent);
        c42_e_out = (CV_TRANSITION_EVAL(54U, (int32_T)(_SFD_CCP_CALL(5U, 54U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 54U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c42_state_Engine == chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 54U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Standard_Flow = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Aux_Enable_State_ACD = c42_IN_Inactive_Temp;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Inactive_Temp = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 55U,
                       chartInstance->c42_sfEvent);
          c42_c_temp = (_SFD_CCP_CALL(5U, 55U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 55U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_c_temp) {
            c42_c_temp = (_SFD_CCP_CALL(5U, 55U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 55U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_e_temp = c42_c_temp;
          if (!c42_c_temp) {
            c42_e_temp = (_SFD_CCP_CALL(5U, 55U, 2, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 55U, 2, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_g_temp = c42_e_temp;
          if (!c42_e_temp) {
            c42_g_temp = (_SFD_CCP_CALL(5U, 55U, 3, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 55U, 3, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORH, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORH) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_i_temp = c42_g_temp;
          if (!c42_g_temp) {
            c42_i_temp = (_SFD_CCP_CALL(5U, 55U, 4, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 55U, 4, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_k_temp = c42_i_temp;
          if (!c42_i_temp) {
            c42_k_temp = (_SFD_CCP_CALL(5U, 55U, 5, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 55U, 5, (real_T)
                                 *chartInstance->c42_state_System, (real_T)
                                 chartInstance->c42_SYS_NORMAL, 0, 1U,
                                 *chartInstance->c42_state_System !=
                                 chartInstance->c42_SYS_NORMAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_g_out = (CV_TRANSITION_EVAL(55U, (int32_T)c42_k_temp) != 0);
          guard1 = false;
          if (c42_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 55U, chartInstance->c42_sfEvent);
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 73U,
                         chartInstance->c42_sfEvent);
            c42_i_out = (CV_TRANSITION_EVAL(73U, (int32_T)(_SFD_CCP_CALL(5U, 73U,
              0, (chartInstance->c42_sfEvent == c42_event_disable_aux) != 0U,
              chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_i_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 73U,
                           chartInstance->c42_sfEvent);
              guard1 = true;
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 26U,
                           chartInstance->c42_sfEvent);
            }
          }

          if (guard1) {
            chartInstance->c42_c_tp_Standard_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c42_sfEvent);
            chartInstance->c42_is_Aux_Enable_State_ACD = c42_IN_Inactive_Latched;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_Inactive_Latched = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 26U, chartInstance->c42_sfEvent);
        break;

       default:
        CV_STATE_EVAL(23, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c42_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 23U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Aux_Enable_State_ST:
    CV_STATE_EVAL(22, 0, c42_IN_Aux_Enable_State_ST);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 58U,
                 chartInstance->c42_sfEvent);
    c42_b_temp = (_SFD_CCP_CALL(5U, 58U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      58U, 0, (real_T)*chartInstance->c42_can_AuxEnable_ST, (real_T)
      chartInstance->c42_INACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ST ==
      chartInstance->c42_INACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_b_temp) {
      c42_b_temp = (_SFD_CCP_CALL(5U, 58U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        58U, 1, (real_T)*chartInstance->c42_state_ST_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 1U, *chartInstance->c42_state_ST_CAN !=
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(58U, (int32_T)c42_b_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
      c42_exit_internal_Aux_Enable_State_ST(chartInstance);
      chartInstance->c42_tp_Aux_Enable_State_ST = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_PHOENIX_K2 = c42_IN_Functional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Functional = 1U;
      c42_enter_internal_Functional(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 27U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_is_Aux_Enable_State_ST) {
       case c42_IN_Inactive_Latched:
        CV_STATE_EVAL(27, 0, c42_IN_Inactive_Latched);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 28U,
                     chartInstance->c42_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 28U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Inactive_Temp:
        CV_STATE_EVAL(27, 0, c42_IN_Inactive_Temp);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 52U,
                     chartInstance->c42_sfEvent);
        c42_d_out = (CV_TRANSITION_EVAL(52U, (int32_T)(_SFD_CCP_CALL(5U, 52U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 52U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 1U,
          *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 52U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Inactive_Temp = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 29U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Aux_Enable_State_ST = c42_IN_Standard_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 30U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Standard_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 29U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 29U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Standard_Flow:
        CV_STATE_EVAL(27, 0, c42_IN_Standard_Flow);
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 50U,
                     chartInstance->c42_sfEvent);
        c42_f_out = (CV_TRANSITION_EVAL(50U, (int32_T)(_SFD_CCP_CALL(5U, 50U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 50U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c42_state_Engine == chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 50U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Standard_Flow = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Aux_Enable_State_ST = c42_IN_Inactive_Temp;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Inactive_Temp = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 51U,
                       chartInstance->c42_sfEvent);
          c42_d_temp = (_SFD_CCP_CALL(5U, 51U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 51U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_d_temp) {
            c42_d_temp = (_SFD_CCP_CALL(5U, 51U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 51U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_f_temp = c42_d_temp;
          if (!c42_d_temp) {
            c42_f_temp = (_SFD_CCP_CALL(5U, 51U, 2, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 51U, 2, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_h_temp = c42_f_temp;
          if (!c42_f_temp) {
            c42_h_temp = (_SFD_CCP_CALL(5U, 51U, 3, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 51U, 3, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORH, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORH) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_j_temp = c42_h_temp;
          if (!c42_h_temp) {
            c42_j_temp = (_SFD_CCP_CALL(5U, 51U, 4, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 51U, 4, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_l_temp = c42_j_temp;
          if (!c42_j_temp) {
            c42_l_temp = (_SFD_CCP_CALL(5U, 51U, 5, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 51U, 5, (real_T)
                                 *chartInstance->c42_state_System, (real_T)
                                 chartInstance->c42_SYS_NORMAL, 0, 1U,
                                 *chartInstance->c42_state_System !=
                                 chartInstance->c42_SYS_NORMAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_h_out = (CV_TRANSITION_EVAL(51U, (int32_T)c42_l_temp) != 0);
          guard1 = false;
          if (c42_h_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 51U, chartInstance->c42_sfEvent);
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 72U,
                         chartInstance->c42_sfEvent);
            c42_j_out = (CV_TRANSITION_EVAL(72U, (int32_T)(_SFD_CCP_CALL(5U, 72U,
              0, (chartInstance->c42_sfEvent == c42_event_disable_aux) != 0U,
              chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_j_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 72U,
                           chartInstance->c42_sfEvent);
              guard1 = true;
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 30U,
                           chartInstance->c42_sfEvent);
            }
          }

          if (guard1) {
            chartInstance->c42_b_tp_Standard_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c42_sfEvent);
            chartInstance->c42_is_Aux_Enable_State_ST = c42_IN_Inactive_Latched;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 28U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_Inactive_Latched = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 30U, chartInstance->c42_sfEvent);
        break;

       default:
        CV_STATE_EVAL(27, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c42_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 27U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Functional:
    CV_STATE_EVAL(22, 0, c42_IN_Functional);
    c42_Functional(chartInstance);
    break;

   default:
    CV_STATE_EVAL(22, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c42_is_PHOENIX_K2 = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c42_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 22U, chartInstance->c42_sfEvent);
}

static void c42_enter_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 31U, chartInstance->c42_sfEvent);
  if (chartInstance->c42_is_Functional == c42_IN_Inactive) {
  } else {
    chartInstance->c42_is_Functional = c42_IN_Inactive;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Inactive = 1U;
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    *chartInstance->c42_state_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxRelease, 30U);
  }
}

static void c42_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_b_out;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_h_temp;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_i_temp;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_j_temp;
  boolean_T c42_g_out;
  boolean_T c42_h_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 57U, chartInstance->c42_sfEvent);
  c42_temp = (_SFD_CCP_CALL(5U, 57U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 57U, 0,
    (real_T)*chartInstance->c42_can_AuxEnable_ST, (real_T)
    chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ST ==
    chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
  if (c42_temp) {
    c42_temp = (_SFD_CCP_CALL(5U, 57U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 57U,
      1, (real_T)*chartInstance->c42_state_ST_CAN, (real_T)
      chartInstance->c42_NORMAL, 0, 0U, *chartInstance->c42_state_ST_CAN ==
      chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_b_temp = c42_temp;
  if (c42_temp) {
    c42_b_temp = (_SFD_CCP_CALL(5U, 57U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      57U, 2, (real_T)chartInstance->c42_CD_STAUX_FUNCTION, (real_T)
      chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c42_CD_STAUX_FUNCTION != chartInstance->c42_NON_FUNCTIONAL)
      != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_out = (CV_TRANSITION_EVAL(57U, (int32_T)c42_b_temp) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
    c42_exit_internal_Functional(chartInstance);
    chartInstance->c42_tp_Functional = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_PHOENIX_K2 = c42_IN_Aux_Enable_State_ST;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Aux_Enable_State_ST = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 49U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_is_Aux_Enable_State_ST == c42_IN_Standard_Flow) {
    } else {
      chartInstance->c42_is_Aux_Enable_State_ST = c42_IN_Standard_Flow;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 30U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Standard_Flow = 1U;
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      matlab_UpdateEEVar();
    }
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 59U,
                 chartInstance->c42_sfEvent);
    c42_c_temp = (_SFD_CCP_CALL(5U, 59U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      59U, 0, (real_T)*chartInstance->c42_can_AuxEnable_ACD, (real_T)
      chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ACD ==
      chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (c42_c_temp) {
      c42_c_temp = (_SFD_CCP_CALL(5U, 59U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        59U, 1, (real_T)*chartInstance->c42_state_ACD_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 0U, *chartInstance->c42_state_ACD_CAN ==
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_d_temp = c42_c_temp;
    if (c42_c_temp) {
      c42_d_temp = (_SFD_CCP_CALL(5U, 59U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        59U, 2, (real_T)chartInstance->c42_CD_RACD_FUNCTION, (real_T)
        chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c42_CD_RACD_FUNCTION != chartInstance->c42_NON_FUNCTIONAL)
        != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(59U, (int32_T)c42_d_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 59U, chartInstance->c42_sfEvent);
      c42_exit_internal_Functional(chartInstance);
      chartInstance->c42_tp_Functional = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_PHOENIX_K2 = c42_IN_Aux_Enable_State_ACD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Aux_Enable_State_ACD = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 53U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow) {
      } else {
        chartInstance->c42_is_Aux_Enable_State_ACD = c42_IN_Standard_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_tp_Standard_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        c42_set_ee_AuxFlow(chartInstance, 0,
                           chartInstance->c42_AUX_FLOW_INACTIVE);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 31U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_is_Functional) {
       case c42_IN_Aux_Relief_G5:
        CV_STATE_EVAL(31, 0, c42_IN_Aux_Relief_G5);
        c42_Aux_Relief_G5(chartInstance);
        break;

       case c42_IN_Enabled:
        CV_STATE_EVAL(31, 0, c42_IN_Enabled);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U,
                     chartInstance->c42_sfEvent);
        c42_e_temp = (_SFD_CCP_CALL(5U, 4U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          4U, 0, (real_T)*chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c42_state_Engine == chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U);
        if (!c42_e_temp) {
          c42_e_temp = (_SFD_CCP_CALL(5U, 4U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 4U, 1, (real_T)*chartInstance->c42_state_System, (real_T)
             chartInstance->c42_SYS_NORMAL, 0, 1U,
             *chartInstance->c42_state_System != chartInstance->c42_SYS_NORMAL)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_g_temp = c42_e_temp;
        if (!c42_e_temp) {
          c42_g_temp = (_SFD_CCP_CALL(5U, 4U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 4U, 2, (real_T)*chartInstance->c42_state_Console, (real_T)
             chartInstance->c42_ACTIVE, 0, 1U, *chartInstance->c42_state_Console
             != chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_c_out = (CV_TRANSITION_EVAL(4U, (int32_T)c42_g_temp) != 0);
        if (c42_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c42_sfEvent);
          c42_exit_internal_Enabled(chartInstance);
          chartInstance->c42_c_tp_Enabled = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Functional = c42_IN_Inactive;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Inactive = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_state_AuxRelease = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxRelease,
                                30U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 29U,
                       chartInstance->c42_sfEvent);
          c42_i_temp = (_SFD_CCP_CALL(5U, 29U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 29U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_i_temp) {
            c42_i_temp = (_SFD_CCP_CALL(5U, 29U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 29U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_e_out = (CV_TRANSITION_EVAL(29U, (int32_T)c42_i_temp) != 0);
          if (c42_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 29U, chartInstance->c42_sfEvent);
            c42_exit_internal_Enabled(chartInstance);
            chartInstance->c42_c_tp_Enabled = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c42_sfEvent);
            chartInstance->c42_is_Functional = c42_IN_Inactive_Fault;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 45U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_Inactive_Fault = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 32U,
                         chartInstance->c42_sfEvent);
            c42_f_out = (CV_TRANSITION_EVAL(32U, (int32_T)(_SFD_CCP_CALL(5U, 32U,
              0, (boolean_T)CV_RELATIONAL_EVAL(5U, 32U, 0, (real_T)
              *chartInstance->c42_state_AuxPot, (real_T)
              chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
              *chartInstance->c42_state_AuxPot ==
              chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_f_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 32U,
                           chartInstance->c42_sfEvent);
              c42_exit_internal_Enabled(chartInstance);
              chartInstance->c42_c_tp_Enabled = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c42_sfEvent);
              chartInstance->c42_is_Functional = c42_IN_Inactive_Out_Of_Neutral;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 46U, chartInstance->c42_sfEvent);
              chartInstance->c42_tp_Inactive_Out_Of_Neutral = 1U;
              *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                    25U);
              *chartInstance->c42_aux_Flow =
                chartInstance->c42_AUX_FLOW_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 38U,
                           chartInstance->c42_sfEvent);
              switch (chartInstance->c42_is_Enabled) {
               case c42_IN_Active:
                CV_STATE_EVAL(38, 0, c42_IN_Active);
                c42_Active(chartInstance);
                break;

               case c42_IN_Off:
                CV_STATE_EVAL(38, 0, c42_IN_Off);
                *chartInstance->c42_aux_Flow =
                  chartInstance->c42_AUX_FLOW_INACTIVE;
                *chartInstance->c42_state_AuxEnable =
                  chartInstance->c42_INACTIVE;
                _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 23U,
                             chartInstance->c42_sfEvent);
                c42_j_temp = (_SFD_CCP_CALL(5U, 23U, 0,
                  (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
                  chartInstance->c42_sfEvent) != 0U);
                if (!c42_j_temp) {
                  c42_j_temp = (_SFD_CCP_CALL(5U, 23U, 1,
                    (*chartInstance->c42_aux_DetentHold != 0) != 0U,
                    chartInstance->c42_sfEvent) != 0U);
                }

                c42_g_out = (CV_TRANSITION_EVAL(23U, (int32_T)c42_j_temp) != 0);
                if (c42_g_out) {
                  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 23U,
                               chartInstance->c42_sfEvent);
                  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 48U,
                               chartInstance->c42_sfEvent);
                  c42_h_out = (CV_TRANSITION_EVAL(48U, (int32_T)(_SFD_CCP_CALL
                    (5U, 48U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 48U, 0,
                    (real_T)chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION, (real_T)
                    chartInstance->c42_NON_FUNCTIONAL, 0, 0U,
                    chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION ==
                    chartInstance->c42_NON_FUNCTIONAL) != 0U,
                     chartInstance->c42_sfEvent) != 0U)) != 0);
                  if (c42_h_out) {
                    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 48U,
                                 chartInstance->c42_sfEvent);
                    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 47U,
                                 chartInstance->c42_sfEvent);
                  } else {
                    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 46U,
                                 chartInstance->c42_sfEvent);
                    c42_set_state_Buzzer(chartInstance, 0,
                                         chartInstance->c42_SINGLE_SHORT_BEEP);
                    ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
                  }

                  chartInstance->c42_tp_Off = 0U;
                  _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U,
                               chartInstance->c42_sfEvent);
                  chartInstance->c42_is_Enabled = c42_IN_Active;
                  _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
                  chartInstance->c42_tp_Active = 1U;
                  if (chartInstance->c42_is_Active == c42_IN_Standard_Flow) {
                  } else {
                    chartInstance->c42_is_Active = c42_IN_Standard_Flow;
                    _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U,
                                 chartInstance->c42_sfEvent);
                    chartInstance->c42_tp_Standard_Flow = 1U;
                    *chartInstance->c42_aux_Flow =
                      chartInstance->c42_AUX_FLOW_STANDARD;
                    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow,
                                          27U);
                    c42_set_ee_AuxFlow(chartInstance, 0,
                                       chartInstance->c42_AUX_FLOW_STANDARD);
                    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
                    *chartInstance->c42_state_AuxEnable =
                      chartInstance->c42_ACTIVE_MODE_ONE;
                    _SFD_DATA_RANGE_CHECK((real_T)
                                          *chartInstance->c42_state_AuxEnable,
                                          25U);
                    matlab_UpdateEEVar();
                  }
                } else {
                  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 43U,
                               chartInstance->c42_sfEvent);
                }

                _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 43U,
                             chartInstance->c42_sfEvent);
                break;

               default:
                CV_STATE_EVAL(38, 0, 0);

                /* Unreachable state, for coverage only */
                chartInstance->c42_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
                _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
                break;
              }
            }
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 38U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Inactive:
        CV_STATE_EVAL(31, 0, c42_IN_Inactive);
        c42_Inactive(chartInstance);
        break;

       case c42_IN_Inactive_Fault:
        CV_STATE_EVAL(31, 0, c42_IN_Inactive_Fault);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 30U,
                     chartInstance->c42_sfEvent);
        c42_f_temp = (_SFD_CCP_CALL(5U, 30U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          30U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
          chartInstance->c42_OORH, 0, 1U, *chartInstance->c42_state_AuxPot !=
          chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
        if (c42_f_temp) {
          c42_f_temp = (_SFD_CCP_CALL(5U, 30U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 30U, 1, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORL, 0, 1U, *chartInstance->c42_state_AuxPot !=
             chartInstance->c42_OORL) != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_h_temp = c42_f_temp;
        if (c42_f_temp) {
          c42_h_temp = (_SFD_CCP_CALL(5U, 30U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 30U, 2, (real_T)*chartInstance->c42_state_System, (real_T)
             chartInstance->c42_SYS_NORMAL, 0, 0U,
             *chartInstance->c42_state_System == chartInstance->c42_SYS_NORMAL)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_d_out = (CV_TRANSITION_EVAL(30U, (int32_T)c42_h_temp) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 30U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Inactive_Fault = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 45U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Functional = c42_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Enabled = 1U;
          if (chartInstance->c42_is_Enabled == c42_IN_Off) {
          } else {
            chartInstance->c42_is_Enabled = c42_IN_Off;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_Off = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            c42_set_ee_AuxFlow(chartInstance, 0,
                               chartInstance->c42_AUX_FLOW_INACTIVE);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            matlab_UpdateEEVar();
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 45U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 45U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Inactive_Out_Of_Neutral:
        CV_STATE_EVAL(31, 0, c42_IN_Inactive_Out_Of_Neutral);
        c42_Inactive_Out_Of_Neutral(chartInstance);
        break;

       default:
        CV_STATE_EVAL(31, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_is_Functional = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c42_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 31U, chartInstance->c42_sfEvent);
}

static void c42_exit_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_is_Functional) {
   case c42_IN_Aux_Relief_G5:
    CV_STATE_EVAL(31, 1, c42_IN_Aux_Relief_G5);
    c42_exit_internal_Aux_Relief_G5(chartInstance);
    chartInstance->c42_tp_Aux_Relief_G5 = 0U;
    chartInstance->c42_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Enabled:
    CV_STATE_EVAL(31, 1, c42_IN_Enabled);
    c42_exit_internal_Enabled(chartInstance);
    chartInstance->c42_c_tp_Enabled = 0U;
    chartInstance->c42_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive:
    CV_STATE_EVAL(31, 1, c42_IN_Inactive);
    chartInstance->c42_tp_Inactive = 0U;
    chartInstance->c42_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive_Fault:
    CV_STATE_EVAL(31, 1, c42_IN_Inactive_Fault);
    chartInstance->c42_tp_Inactive_Fault = 0U;
    chartInstance->c42_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 45U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive_Out_Of_Neutral:
    CV_STATE_EVAL(31, 1, c42_IN_Inactive_Out_Of_Neutral);
    chartInstance->c42_tp_Inactive_Out_Of_Neutral = 0U;
    chartInstance->c42_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(31, 1, 0);
    chartInstance->c42_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_enter_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_temp;
  boolean_T c42_b_out;
  boolean_T c42_b_temp;
  boolean_T c42_c_out;
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 26U, chartInstance->c42_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 41U, chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(41U, (int32_T)(_SFD_CCP_CALL(5U, 41U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 41U, 0, (real_T)c42_get_ee_AuxFlow
    (chartInstance, 0), (real_T)chartInstance->c42_AUX_FLOW_INACTIVE, 0, 0U,
    c42_get_ee_AuxFlow(chartInstance, 0) == chartInstance->c42_AUX_FLOW_INACTIVE)
    != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 41U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_is_Enabled == c42_IN_Off) {
    } else {
      chartInstance->c42_is_Enabled = c42_IN_Off;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Off = 1U;
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      matlab_UpdateEEVar();
    }
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 5U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 5U, 0,
      (real_T)c42_get_ee_AuxFlow(chartInstance, 0), (real_T)
      chartInstance->c42_AUX_FLOW_LOW, 0, 0U, c42_get_ee_AuxFlow(chartInstance,
      0) == chartInstance->c42_AUX_FLOW_LOW) != 0U, chartInstance->c42_sfEvent)
                != 0U);
    if (c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 5U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 5U,
        1, (real_T)chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION, (real_T)
        chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION !=
        chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent) !=
                  0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(5U, (int32_T)c42_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_Enabled = c42_IN_Active;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Active = 1U;
      if (chartInstance->c42_is_Active == c42_IN_Low_Flow) {
      } else {
        chartInstance->c42_is_Active = c42_IN_Low_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Low_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_LOW);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      }
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 27U, chartInstance->c42_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                   chartInstance->c42_sfEvent);
      c42_b_temp = (_SFD_CCP_CALL(5U, 7U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        7U, 0, (real_T)c42_get_ee_AuxFlow(chartInstance, 0), (real_T)
        chartInstance->c42_AUX_FLOW_MEDIUM, 0, 0U, c42_get_ee_AuxFlow
        (chartInstance, 0) == chartInstance->c42_AUX_FLOW_MEDIUM) != 0U,
        chartInstance->c42_sfEvent) != 0U);
      if (c42_b_temp) {
        c42_b_temp = (_SFD_CCP_CALL(5U, 7U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          7U, 1, (real_T)chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION, (real_T)
          chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
          chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION !=
          chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
      }

      c42_c_out = (CV_TRANSITION_EVAL(7U, (int32_T)c42_b_temp) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Enabled = c42_IN_Active;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Active = 1U;
        if (chartInstance->c42_is_Active == c42_IN_Medium_Flow) {
        } else {
          chartInstance->c42_is_Active = c42_IN_Medium_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 41U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Medium_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_MEDIUM);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          matlab_UpdateEEVar();
        }
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 28U, chartInstance->c42_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 25U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Enabled = c42_IN_Active;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Active = 1U;
        if (chartInstance->c42_is_Active == c42_IN_Standard_Flow) {
        } else {
          chartInstance->c42_is_Active = c42_IN_Standard_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Standard_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_STANDARD);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          matlab_UpdateEEVar();
        }
      }
    }
  }
}

static void c42_exit_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_is_Enabled) {
   case c42_IN_Active:
    CV_STATE_EVAL(38, 1, c42_IN_Active);
    c42_exit_internal_Active(chartInstance);
    chartInstance->c42_tp_Active = 0U;
    chartInstance->c42_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Off:
    CV_STATE_EVAL(38, 1, c42_IN_Off);
    chartInstance->c42_tp_Off = 0U;
    chartInstance->c42_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(38, 1, 0);
    chartInstance->c42_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_Active(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_temp;
  boolean_T c42_b_out;
  boolean_T c42_b_temp;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 45U, chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(45U, (int32_T)(_SFD_CCP_CALL(5U, 45U, 0,
    (chartInstance->c42_sfEvent == c42_event_disable_aux) != 0U,
    chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 45U, chartInstance->c42_sfEvent);
    c42_exit_internal_Active(chartInstance);
    chartInstance->c42_tp_Active = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_Enabled = c42_IN_Off;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Off = 1U;
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    matlab_UpdateEEVar();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 39U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 39U,
                 chartInstance->c42_sfEvent);
    switch (chartInstance->c42_is_Active) {
     case c42_IN_Low_Flow:
      CV_STATE_EVAL(39, 0, c42_IN_Low_Flow);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   chartInstance->c42_sfEvent);
      c42_temp = (_SFD_CCP_CALL(5U, 2U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U);
      if (c42_temp) {
        c42_temp = (_SFD_CCP_CALL(5U, 2U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          2U, 0, (real_T)*chartInstance->c42_state_DetentEnable, (real_T)
          chartInstance->c42_ACTIVE, 0, 0U,
          *chartInstance->c42_state_DetentEnable == chartInstance->c42_ACTIVE)
          != 0U, chartInstance->c42_sfEvent) != 0U);
      }

      c42_c_out = (CV_TRANSITION_EVAL(2U, (int32_T)c42_temp) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        chartInstance->c42_tp_Low_Flow = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Active = c42_IN_Standard_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Standard_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0,
                           chartInstance->c42_AUX_FLOW_STANDARD);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 24U,
                     chartInstance->c42_sfEvent);
        c42_c_temp = (_SFD_CCP_CALL(5U, 24U, 0,
          (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (c42_c_temp) {
          c42_c_temp = (_SFD_CCP_CALL(5U, 24U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 24U, 0, (real_T)*chartInstance->c42_state_DetentEnable, (real_T)
             chartInstance->c42_ACTIVE, 0, 1U,
             *chartInstance->c42_state_DetentEnable != chartInstance->c42_ACTIVE)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_e_out = (CV_TRANSITION_EVAL(24U, (int32_T)c42_c_temp) != 0);
        if (c42_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c42_sfEvent);
          c42_set_state_Buzzer(chartInstance, 0,
                               chartInstance->c42_SINGLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
          chartInstance->c42_tp_Low_Flow = 0U;
          chartInstance->c42_is_Active = c42_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Active = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Enabled = c42_IN_Off;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Off = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 40U,
                       chartInstance->c42_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 40U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_is_Enabled != c42_IN_Active) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 39U, chartInstance->c42_sfEvent);
      }
      break;

     case c42_IN_Medium_Flow:
      CV_STATE_EVAL(39, 0, c42_IN_Medium_Flow);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U,
                   chartInstance->c42_sfEvent);
      c42_b_out = (CV_TRANSITION_EVAL(6U, (int32_T)(_SFD_CCP_CALL(5U, 6U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        chartInstance->c42_tp_Medium_Flow = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Active = c42_IN_Low_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Low_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_LOW);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 41U,
                     chartInstance->c42_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 41U, chartInstance->c42_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 39U, chartInstance->c42_sfEvent);
      break;

     case c42_IN_Standard_Flow:
      CV_STATE_EVAL(39, 0, c42_IN_Standard_Flow);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                   chartInstance->c42_sfEvent);
      c42_b_temp = (_SFD_CCP_CALL(5U, 8U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U);
      if (c42_b_temp) {
        c42_b_temp = (_SFD_CCP_CALL(5U, 8U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          8U, 0, (real_T)chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION, (real_T)
          chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
          chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION !=
          chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
      }

      c42_d_out = (CV_TRANSITION_EVAL(8U, (int32_T)c42_b_temp) != 0);
      if (c42_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        chartInstance->c42_tp_Standard_Flow = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Active = c42_IN_Medium_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 41U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Medium_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_MEDIUM);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 42U,
                     chartInstance->c42_sfEvent);
        c42_d_temp = (_SFD_CCP_CALL(5U, 42U, 0,
          (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (c42_d_temp) {
          c42_d_temp = (_SFD_CCP_CALL(5U, 42U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 42U, 0, (real_T)chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION,
             (real_T)chartInstance->c42_NON_FUNCTIONAL, 0, 0U,
             chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION ==
             chartInstance->c42_NON_FUNCTIONAL) != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_f_out = (CV_TRANSITION_EVAL(42U, (int32_T)c42_d_temp) != 0);
        if (c42_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 42U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Standard_Flow = 0U;
          chartInstance->c42_is_Active = c42_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Active = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Enabled = c42_IN_Off;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Off = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 42U,
                       chartInstance->c42_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 42U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_is_Enabled != c42_IN_Active) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 39U, chartInstance->c42_sfEvent);
      }
      break;

     default:
      CV_STATE_EVAL(39, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c42_is_Active = c42_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 39U, chartInstance->c42_sfEvent);
      break;
    }
  }
}

static void c42_exit_internal_Active(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_is_Active) {
   case c42_IN_Low_Flow:
    CV_STATE_EVAL(39, 1, c42_IN_Low_Flow);
    chartInstance->c42_tp_Low_Flow = 0U;
    chartInstance->c42_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Medium_Flow:
    CV_STATE_EVAL(39, 1, c42_IN_Medium_Flow);
    chartInstance->c42_tp_Medium_Flow = 0U;
    chartInstance->c42_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(39, 1, c42_IN_Standard_Flow);
    chartInstance->c42_tp_Standard_Flow = 0U;
    chartInstance->c42_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(39, 1, 0);
    chartInstance->c42_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_Inactive(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_out;
  boolean_T c42_h_temp;
  boolean_T c42_i_temp;
  boolean_T c42_j_temp;
  boolean_T c42_k_temp;
  boolean_T c42_l_temp;
  boolean_T c42_m_temp;
  boolean_T c42_n_temp;
  boolean_T c42_b_out;
  *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
  *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
  *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
  *chartInstance->c42_state_AuxRelease = chartInstance->c42_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U, chartInstance->c42_sfEvent);
  c42_temp = (_SFD_CCP_CALL(5U, 3U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 3U, 0,
    (real_T)*chartInstance->c42_state_Engine, (real_T)
    chartInstance->c42_ENGINE_CRANKING, 0, 1U, *chartInstance->c42_state_Engine
    != chartInstance->c42_ENGINE_CRANKING) != 0U, chartInstance->c42_sfEvent) !=
              0U);
  if (c42_temp) {
    c42_b_temp = (_SFD_CCP_CALL(5U, 3U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 3U,
      1, (real_T)*chartInstance->c42_state_Engine, (real_T)
      chartInstance->c42_ENGINE_RUNNING, 0, 0U, *chartInstance->c42_state_Engine
      == chartInstance->c42_ENGINE_RUNNING) != 0U, chartInstance->c42_sfEvent)
                  != 0U);
    if (!c42_b_temp) {
      c42_b_temp = (_SFD_CCP_CALL(5U, 3U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        3U, 2, (real_T)chartInstance->c42_CD_AUX_RELEASE_FUNCTION, (real_T)
        chartInstance->c42_NON_FUNCTIONAL, 0, 0U,
        chartInstance->c42_CD_AUX_RELEASE_FUNCTION ==
        chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent) !=
                    0U);
    }

    c42_d_temp = c42_b_temp;
    if (!c42_b_temp) {
      c42_f_temp = !(_SFD_CCP_CALL(5U, 3U, 3, (c42_get_ee_DeluxeG5(chartInstance,
        0) != 0) != 0U, chartInstance->c42_sfEvent) != 0U);
      if (c42_f_temp) {
        c42_f_temp = (_SFD_CCP_CALL(5U, 3U, 4, (boolean_T)CV_RELATIONAL_EVAL(5U,
          3U, 3, (real_T)chartInstance->c42_CD_DELUXE_GEN5_5_FUNCTION, (real_T)
          chartInstance->c42_NON_FUNCTIONAL, 0, 0U,
          chartInstance->c42_CD_DELUXE_GEN5_5_FUNCTION ==
          chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
      }

      c42_d_temp = c42_f_temp;
    }

    c42_temp = c42_d_temp;
  }

  c42_c_temp = c42_temp;
  if (c42_temp) {
    c42_c_temp = (_SFD_CCP_CALL(5U, 3U, 5, (boolean_T)CV_RELATIONAL_EVAL(5U, 3U,
      4, (real_T)*chartInstance->c42_state_System, (real_T)
      chartInstance->c42_SYS_NORMAL, 0, 0U, *chartInstance->c42_state_System ==
      chartInstance->c42_SYS_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_e_temp = c42_c_temp;
  if (c42_c_temp) {
    c42_e_temp = (_SFD_CCP_CALL(5U, 3U, 6, (boolean_T)CV_RELATIONAL_EVAL(5U, 3U,
      5, (real_T)*chartInstance->c42_state_Console, (real_T)
      chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_state_Console ==
      chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_g_temp = c42_e_temp;
  if (c42_e_temp) {
    c42_g_temp = (_SFD_CCP_CALL(5U, 3U, 7, *chartInstance->c42_flag_InitEERead
      != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_out = (CV_TRANSITION_EVAL(3U, (int32_T)c42_g_temp) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Inactive = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_Functional = c42_IN_Enabled;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c42_sfEvent);
    chartInstance->c42_c_tp_Enabled = 1U;
    c42_enter_internal_Enabled(chartInstance);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 74U,
                 chartInstance->c42_sfEvent);
    c42_h_temp = (_SFD_CCP_CALL(5U, 74U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      74U, 0, (real_T)chartInstance->c42_CD_AUX_RELEASE_FUNCTION, (real_T)
      chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c42_CD_AUX_RELEASE_FUNCTION !=
      chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent) !=
                  0U);
    if (c42_h_temp) {
      c42_i_temp = (_SFD_CCP_CALL(5U, 74U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        74U, 1, (real_T)*chartInstance->c42_state_Engine, (real_T)
        chartInstance->c42_ENGINE_NOT_RUNNING, 0, 0U,
        *chartInstance->c42_state_Engine ==
        chartInstance->c42_ENGINE_NOT_RUNNING) != 0U, chartInstance->c42_sfEvent)
                    != 0U);
      if (!c42_i_temp) {
        c42_i_temp = (_SFD_CCP_CALL(5U, 74U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
          74U, 2, (real_T)*chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_INITIALIZE, 0, 0U,
          *chartInstance->c42_state_Engine ==
          chartInstance->c42_ENGINE_INITIALIZE) != 0U,
          chartInstance->c42_sfEvent) != 0U);
      }

      c42_h_temp = c42_i_temp;
    }

    c42_j_temp = c42_h_temp;
    if (c42_h_temp) {
      c42_j_temp = (_SFD_CCP_CALL(5U, 74U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
        74U, 3, (real_T)*chartInstance->c42_state_EngineSpeed, (real_T)
        chartInstance->c42_NO_SIGNAL, 0, 1U,
        *chartInstance->c42_state_EngineSpeed != chartInstance->c42_NO_SIGNAL)
        != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_k_temp = c42_j_temp;
    if (c42_j_temp) {
      c42_k_temp = (_SFD_CCP_CALL(5U, 74U, 4, (boolean_T)CV_RELATIONAL_EVAL(5U,
        74U, 4, (real_T)*chartInstance->c42_state_System, (real_T)
        chartInstance->c42_SYS_NORMAL, 0, 0U, *chartInstance->c42_state_System ==
        chartInstance->c42_SYS_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_l_temp = c42_k_temp;
    if (c42_k_temp) {
      c42_l_temp = (_SFD_CCP_CALL(5U, 74U, 5, (c42_get_ee_DeluxeG5(chartInstance,
        0) != 0) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_m_temp = c42_l_temp;
    if (c42_l_temp) {
      c42_m_temp = (_SFD_CCP_CALL(5U, 74U, 6,
        *chartInstance->c42_flag_InitEERead != 0U, chartInstance->c42_sfEvent)
                    != 0U);
    }

    c42_n_temp = c42_m_temp;
    if (c42_m_temp) {
      c42_n_temp = (_SFD_CCP_CALL(5U, 74U, 7, (boolean_T)CV_RELATIONAL_EVAL(5U,
        74U, 5, (real_T)chartInstance->c42_CD_DELUXE_GEN5_5_FUNCTION, (real_T)
        chartInstance->c42_NON_FUNCTIONAL, 0, 0U,
        chartInstance->c42_CD_DELUXE_GEN5_5_FUNCTION ==
        chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent) !=
                    0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(74U, (int32_T)c42_n_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 74U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Inactive = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_Functional = c42_IN_Aux_Relief_G5;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Aux_Relief_G5 = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_is_Aux_Relief_G5 == c42_IN_Wait) {
      } else {
        chartInstance->c42_is_Aux_Relief_G5 = c42_IN_Wait;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Wait = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_RELEASE_WAIT;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 44U,
                   chartInstance->c42_sfEvent);
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 44U, chartInstance->c42_sfEvent);
}

static void c42_Inactive_Out_Of_Neutral(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_temp;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_b_temp;
  boolean_T c42_c_temp;
  boolean_T c42_d_out;
  *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
  *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 43U, chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(43U, (int32_T)(_SFD_CCP_CALL(5U, 43U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 43U, 0, (real_T)
    *chartInstance->c42_state_Console, (real_T)chartInstance->c42_ACTIVE, 0, 1U,
    *chartInstance->c42_state_Console != chartInstance->c42_ACTIVE) != 0U,
    chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 43U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Inactive_Out_Of_Neutral = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_Functional = c42_IN_Inactive;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Inactive = 1U;
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    *chartInstance->c42_state_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxRelease, 30U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 34U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 34U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 34U,
      0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
      chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
      chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 34U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        34U, 1, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
        chartInstance->c42_OORL, 0, 0U, *chartInstance->c42_state_AuxPot ==
        chartInstance->c42_OORL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(34U, (int32_T)c42_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 34U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Inactive_Out_Of_Neutral = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_Functional = c42_IN_Inactive_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 45U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_Inactive_Fault = 1U;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 35U,
                   chartInstance->c42_sfEvent);
      c42_c_out = (CV_TRANSITION_EVAL(35U, (int32_T)(_SFD_CCP_CALL(5U, 35U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 35U, 0, (real_T)
        *chartInstance->c42_state_AuxPot, (real_T)
        chartInstance->c42_NOT_IN_NEUTRAL, 0, 1U,
        *chartInstance->c42_state_AuxPot != chartInstance->c42_NOT_IN_NEUTRAL)
        != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 35U, chartInstance->c42_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 37U,
                     chartInstance->c42_sfEvent);
        c42_b_temp = (_SFD_CCP_CALL(5U, 37U, 0,
          (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (!c42_b_temp) {
          c42_b_temp = (_SFD_CCP_CALL(5U, 37U, 1,
            (*chartInstance->c42_aux_DetentHold != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_c_temp = c42_b_temp;
        if (c42_b_temp) {
          c42_c_temp = (_SFD_CCP_CALL(5U, 37U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 37U, 0, (real_T)*chartInstance->c42_aux_Flow, (real_T)
             chartInstance->c42_AUX_FLOW_INACTIVE, 0, 1U,
             *chartInstance->c42_aux_Flow !=
             chartInstance->c42_AUX_FLOW_INACTIVE) != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_d_out = (CV_TRANSITION_EVAL(37U, (int32_T)c42_c_temp) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 37U, chartInstance->c42_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 38U, chartInstance->c42_sfEvent);
          c42_set_state_Buzzer(chartInstance, 0,
                               chartInstance->c42_SINGLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 36U, chartInstance->c42_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 39U, chartInstance->c42_sfEvent);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 33U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Inactive_Out_Of_Neutral = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Functional = c42_IN_Enabled;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_tp_Enabled = 1U;
        c42_enter_internal_Enabled(chartInstance);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 46U,
                     chartInstance->c42_sfEvent);
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 46U, chartInstance->c42_sfEvent);
}

static void c42_Aux_Relief_G5(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_c_temp;
  boolean_T c42_out;
  boolean_T c42_b_out;
  uint16_T c42_u2;
  uint16_T c42_u3;
  uint16_T c42_u4;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_d_temp;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_g_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 75U, chartInstance->c42_sfEvent);
  c42_temp = (_SFD_CCP_CALL(5U, 75U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 75U, 0,
    (real_T)*chartInstance->c42_state_Engine, (real_T)
    chartInstance->c42_ENGINE_NOT_RUNNING, 0, 1U,
    *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_NOT_RUNNING)
    != 0U, chartInstance->c42_sfEvent) != 0U);
  if (c42_temp) {
    c42_temp = (_SFD_CCP_CALL(5U, 75U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 75U,
      1, (real_T)*chartInstance->c42_state_Engine, (real_T)
      chartInstance->c42_ENGINE_INITIALIZE, 0, 1U,
      *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_INITIALIZE)
      != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_b_temp = c42_temp;
  if (!c42_temp) {
    c42_b_temp = (_SFD_CCP_CALL(5U, 75U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      75U, 2, (real_T)*chartInstance->c42_state_EngineSpeed, (real_T)
      chartInstance->c42_NO_SIGNAL, 0, 0U, *chartInstance->c42_state_EngineSpeed
      == chartInstance->c42_NO_SIGNAL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_c_temp = c42_b_temp;
  if (!c42_b_temp) {
    c42_c_temp = (_SFD_CCP_CALL(5U, 75U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
      75U, 3, (real_T)*chartInstance->c42_state_System, (real_T)
      chartInstance->c42_SYS_NORMAL, 0, 1U, *chartInstance->c42_state_System !=
      chartInstance->c42_SYS_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_out = (CV_TRANSITION_EVAL(75U, (int32_T)c42_c_temp) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 75U, chartInstance->c42_sfEvent);
    c42_exit_internal_Aux_Relief_G5(chartInstance);
    chartInstance->c42_tp_Aux_Relief_G5 = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_Functional = c42_IN_Inactive;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c42_sfEvent);
    chartInstance->c42_tp_Inactive = 1U;
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    *chartInstance->c42_state_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxRelease, 30U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 32U,
                 chartInstance->c42_sfEvent);
    switch (chartInstance->c42_is_Aux_Relief_G5) {
     case c42_IN_Ack:
      CV_STATE_EVAL(32, 0, c42_IN_Ack);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_RELEASE_ACK;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 78U,
                   chartInstance->c42_sfEvent);
      c42_b_out = (CV_TRANSITION_EVAL(78U, (int32_T)(_SFD_CCP_CALL(5U, 78U, 0,
        *chartInstance->c42_button_AuxReleaseAck != 0U,
        chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 78U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Ack = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Aux_Relief_G5 = c42_IN_Release_Base;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c42_sfEvent);
        chartInstance->c42_temporalCounter_i2 = 0U;
        chartInstance->c42_tp_Release_Base = 1U;
        *chartInstance->c42_aux_Flow =
          chartInstance->c42_AUX_RELEASE_IN_PROGRESS;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_BASE_ACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 80U,
                     chartInstance->c42_sfEvent);
        c42_f_out = (CV_TRANSITION_EVAL(80U, (int32_T)(_SFD_CCP_CALL(5U, 80U, 0,
          *chartInstance->c42_button_AuxReleaseBack != 0U,
          chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 80U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Ack = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c42_sfEvent);
          chartInstance->c42_is_Aux_Relief_G5 = c42_IN_Wait;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c42_sfEvent);
          chartInstance->c42_tp_Wait = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_RELEASE_WAIT;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 33U,
                       chartInstance->c42_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 33U, chartInstance->c42_sfEvent);
      break;

     case c42_IN_Confirm:
      CV_STATE_EVAL(32, 0, c42_IN_Confirm);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_RELEASE_CONFIRM;
      *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 82U,
                   chartInstance->c42_sfEvent);
      c42_u3 = c42__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
        ((uint32_T)chartInstance->c42_CD_AUX_CONFIRM_TIME, 16U, 82U), 592U, 1U,
        5U);
      c42_d_temp = (_SFD_CCP_CALL(5U, 82U, 0,
        (chartInstance->c42_temporalCounter_i2 >= c42_u3) != 0U,
        chartInstance->c42_sfEvent) != 0U);
      if (!c42_d_temp) {
        c42_d_temp = (_SFD_CCP_CALL(5U, 82U, 1,
          *chartInstance->c42_button_AuxReleaseExit != 0U,
          chartInstance->c42_sfEvent) != 0U);
      }

      c42_g_out = (CV_TRANSITION_EVAL(82U, (int32_T)c42_d_temp) != 0);
      if (c42_g_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 82U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Confirm = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Aux_Relief_G5 = c42_IN_Wait;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Wait = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_RELEASE_WAIT;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 34U,
                     chartInstance->c42_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 34U, chartInstance->c42_sfEvent);
      break;

     case c42_IN_Release_Base:
      CV_STATE_EVAL(32, 0, c42_IN_Release_Base);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_RELEASE_IN_PROGRESS;
      *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_BASE_ACTIVE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 79U,
                   chartInstance->c42_sfEvent);
      c42_u4 = c42__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
        ((uint32_T)chartInstance->c42_CD_AUX_RELEASE_TIME, 16U, 79U), 583U, 1U,
        5U);
      c42_e_out = (CV_TRANSITION_EVAL(79U, (int32_T)(_SFD_CCP_CALL(5U, 79U, 0,
        (chartInstance->c42_temporalCounter_i2 >= c42_u4) != 0U,
        chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 79U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Release_Base = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Aux_Relief_G5 = c42_IN_Release_Rod;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c42_sfEvent);
        chartInstance->c42_temporalCounter_i2 = 0U;
        chartInstance->c42_tp_Release_Rod = 1U;
        *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_ROD_ACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 35U,
                     chartInstance->c42_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 35U, chartInstance->c42_sfEvent);
      break;

     case c42_IN_Release_Rod:
      CV_STATE_EVAL(32, 0, c42_IN_Release_Rod);
      *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_ROD_ACTIVE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 81U,
                   chartInstance->c42_sfEvent);
      c42_u2 = c42__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
        ((uint32_T)chartInstance->c42_CD_AUX_RELEASE_TIME, 16U, 81U), 590U, 1U,
        5U);
      c42_c_out = (CV_TRANSITION_EVAL(81U, (int32_T)(_SFD_CCP_CALL(5U, 81U, 0,
        (chartInstance->c42_temporalCounter_i2 >= c42_u2) != 0U,
        chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 81U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Release_Rod = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Aux_Relief_G5 = c42_IN_Confirm;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 34U, chartInstance->c42_sfEvent);
        chartInstance->c42_temporalCounter_i2 = 0U;
        chartInstance->c42_tp_Confirm = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_RELEASE_CONFIRM;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 36U,
                     chartInstance->c42_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 36U, chartInstance->c42_sfEvent);
      break;

     case c42_IN_Wait:
      CV_STATE_EVAL(32, 0, c42_IN_Wait);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_RELEASE_WAIT;
      *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 77U,
                   chartInstance->c42_sfEvent);
      c42_d_out = (CV_TRANSITION_EVAL(77U, (int32_T)(_SFD_CCP_CALL(5U, 77U, 0, (*
        chartInstance->c42_button_Aux != 0) != 0U, chartInstance->c42_sfEvent)
        != 0U)) != 0);
      if (c42_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Wait = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c42_sfEvent);
        chartInstance->c42_is_Aux_Relief_G5 = c42_IN_Ack;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_Ack = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_RELEASE_ACK;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 37U,
                     chartInstance->c42_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 37U, chartInstance->c42_sfEvent);
      break;

     default:
      CV_STATE_EVAL(32, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c42_is_Aux_Relief_G5 = c42_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c42_sfEvent);
      break;
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 32U, chartInstance->c42_sfEvent);
}

static void c42_exit_internal_Aux_Relief_G5(SFc42_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  switch (chartInstance->c42_is_Aux_Relief_G5) {
   case c42_IN_Ack:
    CV_STATE_EVAL(32, 1, c42_IN_Ack);
    chartInstance->c42_tp_Ack = 0U;
    chartInstance->c42_is_Aux_Relief_G5 = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Confirm:
    CV_STATE_EVAL(32, 1, c42_IN_Confirm);
    chartInstance->c42_tp_Confirm = 0U;
    chartInstance->c42_is_Aux_Relief_G5 = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Release_Base:
    CV_STATE_EVAL(32, 1, c42_IN_Release_Base);
    chartInstance->c42_tp_Release_Base = 0U;
    chartInstance->c42_is_Aux_Relief_G5 = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Release_Rod:
    CV_STATE_EVAL(32, 1, c42_IN_Release_Rod);
    chartInstance->c42_tp_Release_Rod = 0U;
    chartInstance->c42_is_Aux_Relief_G5 = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Wait:
    CV_STATE_EVAL(32, 1, c42_IN_Wait);
    chartInstance->c42_tp_Wait = 0U;
    chartInstance->c42_is_Aux_Relief_G5 = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(32, 1, 0);
    chartInstance->c42_is_Aux_Relief_G5 = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_exit_internal_Aux_Enable_State_ST
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c42_is_Aux_Enable_State_ST) {
   case c42_IN_Inactive_Latched:
    CV_STATE_EVAL(27, 1, c42_IN_Inactive_Latched);
    chartInstance->c42_tp_Inactive_Latched = 0U;
    chartInstance->c42_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive_Temp:
    CV_STATE_EVAL(27, 1, c42_IN_Inactive_Temp);
    chartInstance->c42_tp_Inactive_Temp = 0U;
    chartInstance->c42_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 29U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(27, 1, c42_IN_Standard_Flow);
    chartInstance->c42_b_tp_Standard_Flow = 0U;
    chartInstance->c42_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(27, 1, 0);
    chartInstance->c42_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_exit_internal_Aux_Enable_State_ACD
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c42_is_Aux_Enable_State_ACD) {
   case c42_IN_Inactive_Latched:
    CV_STATE_EVAL(23, 1, c42_IN_Inactive_Latched);
    chartInstance->c42_b_tp_Inactive_Latched = 0U;
    chartInstance->c42_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive_Temp:
    CV_STATE_EVAL(23, 1, c42_IN_Inactive_Temp);
    chartInstance->c42_b_tp_Inactive_Temp = 0U;
    chartInstance->c42_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(23, 1, c42_IN_Standard_Flow);
    chartInstance->c42_c_tp_Standard_Flow = 0U;
    chartInstance->c42_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(23, 1, 0);
    chartInstance->c42_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_SIRIUS2(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_h_temp;
  boolean_T c42_i_temp;
  boolean_T c42_j_temp;
  boolean_T c42_k_temp;
  boolean_T c42_l_temp;
  boolean_T c42_g_out;
  boolean_T c42_h_out;
  boolean_T c42_i_out;
  boolean_T c42_j_out;
  boolean_T guard1 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 47U, chartInstance->c42_sfEvent);
  switch (chartInstance->c42_is_SIRIUS2) {
   case c42_IN_Aux_Enable_State_ACD:
    CV_STATE_EVAL(47, 0, c42_IN_Aux_Enable_State_ACD);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 138U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 138U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      138U, 0, (real_T)*chartInstance->c42_can_AuxEnable_ACD, (real_T)
      chartInstance->c42_INACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ACD ==
      chartInstance->c42_INACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 138U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        138U, 1, (real_T)*chartInstance->c42_state_ACD_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 1U, *chartInstance->c42_state_ACD_CAN !=
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_out = (CV_TRANSITION_EVAL(138U, (int32_T)c42_temp) != 0);
    if (c42_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 138U, chartInstance->c42_sfEvent);
      c42_b_exit_internal_Aux_Enable_State_ACD(chartInstance);
      chartInstance->c42_b_tp_Aux_Enable_State_ACD = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 48U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_SIRIUS2 = c42_IN_Functional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 56U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Functional = 1U;
      c42_b_enter_internal_Functional(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 48U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_b_is_Aux_Enable_State_ACD) {
       case c42_IN_Inactive_Latched:
        CV_STATE_EVAL(48, 0, c42_IN_Inactive_Latched);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 49U,
                     chartInstance->c42_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 49U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Inactive_Temp:
        CV_STATE_EVAL(48, 0, c42_IN_Inactive_Temp);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 176U,
                     chartInstance->c42_sfEvent);
        c42_c_out = (CV_TRANSITION_EVAL(176U, (int32_T)(_SFD_CCP_CALL(5U, 176U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 176U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 1U,
          *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 176U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_tp_Inactive_Temp = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 50U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Aux_Enable_State_ACD = c42_IN_Standard_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 51U, chartInstance->c42_sfEvent);
          chartInstance->c42_f_tp_Standard_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 50U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 50U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Standard_Flow:
        CV_STATE_EVAL(48, 0, c42_IN_Standard_Flow);
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 173U,
                     chartInstance->c42_sfEvent);
        c42_e_out = (CV_TRANSITION_EVAL(173U, (int32_T)(_SFD_CCP_CALL(5U, 173U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 173U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c42_state_Engine == chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 173U, chartInstance->c42_sfEvent);
          chartInstance->c42_f_tp_Standard_Flow = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 51U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Aux_Enable_State_ACD = c42_IN_Inactive_Temp;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 50U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_tp_Inactive_Temp = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 174U,
                       chartInstance->c42_sfEvent);
          c42_c_temp = (_SFD_CCP_CALL(5U, 174U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 174U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_c_temp) {
            c42_c_temp = (_SFD_CCP_CALL(5U, 174U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 174U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_e_temp = c42_c_temp;
          if (!c42_c_temp) {
            c42_e_temp = (_SFD_CCP_CALL(5U, 174U, 2, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 174U, 2, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_g_temp = c42_e_temp;
          if (!c42_e_temp) {
            c42_g_temp = (_SFD_CCP_CALL(5U, 174U, 3, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 174U, 3, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORH, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORH) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_i_temp = c42_g_temp;
          if (!c42_g_temp) {
            c42_i_temp = (_SFD_CCP_CALL(5U, 174U, 4, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 174U, 4, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_k_temp = c42_i_temp;
          if (!c42_i_temp) {
            c42_k_temp = (_SFD_CCP_CALL(5U, 174U, 5, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 174U, 5, (real_T)
                                 *chartInstance->c42_state_System, (real_T)
                                 chartInstance->c42_SYS_NORMAL, 0, 1U,
                                 *chartInstance->c42_state_System !=
                                 chartInstance->c42_SYS_NORMAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_g_out = (CV_TRANSITION_EVAL(174U, (int32_T)c42_k_temp) != 0);
          guard1 = false;
          if (c42_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 174U, chartInstance->c42_sfEvent);
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 175U,
                         chartInstance->c42_sfEvent);
            c42_i_out = (CV_TRANSITION_EVAL(175U, (int32_T)(_SFD_CCP_CALL(5U,
              175U, 0, (chartInstance->c42_sfEvent == c42_event_disable_aux) !=
              0U, chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_i_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 175U,
                           chartInstance->c42_sfEvent);
              guard1 = true;
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 51U,
                           chartInstance->c42_sfEvent);
            }
          }

          if (guard1) {
            chartInstance->c42_f_tp_Standard_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 51U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_is_Aux_Enable_State_ACD =
              c42_IN_Inactive_Latched;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 49U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_tp_Inactive_Latched = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 51U, chartInstance->c42_sfEvent);
        break;

       default:
        CV_STATE_EVAL(48, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_b_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 49U, chartInstance->c42_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 48U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Aux_Enable_State_ST:
    CV_STATE_EVAL(47, 0, c42_IN_Aux_Enable_State_ST);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 136U,
                 chartInstance->c42_sfEvent);
    c42_b_temp = (_SFD_CCP_CALL(5U, 136U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      136U, 0, (real_T)*chartInstance->c42_can_AuxEnable_ST, (real_T)
      chartInstance->c42_INACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ST ==
      chartInstance->c42_INACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_b_temp) {
      c42_b_temp = (_SFD_CCP_CALL(5U, 136U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        136U, 1, (real_T)*chartInstance->c42_state_ST_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 1U, *chartInstance->c42_state_ST_CAN !=
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(136U, (int32_T)c42_b_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 136U, chartInstance->c42_sfEvent);
      c42_b_exit_internal_Aux_Enable_State_ST(chartInstance);
      chartInstance->c42_b_tp_Aux_Enable_State_ST = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 52U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_SIRIUS2 = c42_IN_Functional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 56U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Functional = 1U;
      c42_b_enter_internal_Functional(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 52U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_b_is_Aux_Enable_State_ST) {
       case c42_IN_Inactive_Latched:
        CV_STATE_EVAL(52, 0, c42_IN_Inactive_Latched);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 53U,
                     chartInstance->c42_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 53U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Inactive_Temp:
        CV_STATE_EVAL(52, 0, c42_IN_Inactive_Temp);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 170U,
                     chartInstance->c42_sfEvent);
        c42_d_out = (CV_TRANSITION_EVAL(170U, (int32_T)(_SFD_CCP_CALL(5U, 170U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 170U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 1U,
          *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 170U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Inactive_Temp = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 54U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Aux_Enable_State_ST = c42_IN_Standard_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 55U, chartInstance->c42_sfEvent);
          chartInstance->c42_e_tp_Standard_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 54U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 54U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Standard_Flow:
        CV_STATE_EVAL(52, 0, c42_IN_Standard_Flow);
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 168U,
                     chartInstance->c42_sfEvent);
        c42_f_out = (CV_TRANSITION_EVAL(168U, (int32_T)(_SFD_CCP_CALL(5U, 168U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 168U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c42_state_Engine == chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 168U, chartInstance->c42_sfEvent);
          chartInstance->c42_e_tp_Standard_Flow = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 55U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Aux_Enable_State_ST = c42_IN_Inactive_Temp;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 54U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Inactive_Temp = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 169U,
                       chartInstance->c42_sfEvent);
          c42_d_temp = (_SFD_CCP_CALL(5U, 169U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 169U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_d_temp) {
            c42_d_temp = (_SFD_CCP_CALL(5U, 169U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 169U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_f_temp = c42_d_temp;
          if (!c42_d_temp) {
            c42_f_temp = (_SFD_CCP_CALL(5U, 169U, 2, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 169U, 2, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_h_temp = c42_f_temp;
          if (!c42_f_temp) {
            c42_h_temp = (_SFD_CCP_CALL(5U, 169U, 3, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 169U, 3, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORH, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORH) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_j_temp = c42_h_temp;
          if (!c42_h_temp) {
            c42_j_temp = (_SFD_CCP_CALL(5U, 169U, 4, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 169U, 4, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_l_temp = c42_j_temp;
          if (!c42_j_temp) {
            c42_l_temp = (_SFD_CCP_CALL(5U, 169U, 5, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 169U, 5, (real_T)
                                 *chartInstance->c42_state_System, (real_T)
                                 chartInstance->c42_SYS_NORMAL, 0, 1U,
                                 *chartInstance->c42_state_System !=
                                 chartInstance->c42_SYS_NORMAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_h_out = (CV_TRANSITION_EVAL(169U, (int32_T)c42_l_temp) != 0);
          guard1 = false;
          if (c42_h_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 169U, chartInstance->c42_sfEvent);
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 171U,
                         chartInstance->c42_sfEvent);
            c42_j_out = (CV_TRANSITION_EVAL(171U, (int32_T)(_SFD_CCP_CALL(5U,
              171U, 0, (chartInstance->c42_sfEvent == c42_event_disable_aux) !=
              0U, chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_j_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 171U,
                           chartInstance->c42_sfEvent);
              guard1 = true;
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 55U,
                           chartInstance->c42_sfEvent);
            }
          }

          if (guard1) {
            chartInstance->c42_e_tp_Standard_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 55U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_is_Aux_Enable_State_ST =
              c42_IN_Inactive_Latched;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 53U, chartInstance->c42_sfEvent);
            chartInstance->c42_c_tp_Inactive_Latched = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 55U, chartInstance->c42_sfEvent);
        break;

       default:
        CV_STATE_EVAL(52, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_b_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 53U, chartInstance->c42_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 52U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Functional:
    CV_STATE_EVAL(47, 0, c42_IN_Functional);
    c42_b_Functional(chartInstance);
    break;

   default:
    CV_STATE_EVAL(47, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c42_is_SIRIUS2 = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 48U, chartInstance->c42_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 47U, chartInstance->c42_sfEvent);
}

static void c42_b_enter_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 139U, chartInstance->c42_sfEvent);
  if (chartInstance->c42_b_is_Functional == c42_b_IN_Inactive) {
  } else {
    chartInstance->c42_b_is_Functional = c42_b_IN_Inactive;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 63U, chartInstance->c42_sfEvent);
    chartInstance->c42_b_tp_Inactive = 1U;
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
  }
}

static void c42_b_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_b_out;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_c_out;
  boolean_T c42_h_temp;
  boolean_T c42_i_temp;
  boolean_T c42_j_temp;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_k_temp;
  boolean_T c42_g_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 135U,
               chartInstance->c42_sfEvent);
  c42_temp = (_SFD_CCP_CALL(5U, 135U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 135U,
    0, (real_T)*chartInstance->c42_can_AuxEnable_ST, (real_T)
    chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ST ==
    chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
  if (c42_temp) {
    c42_temp = (_SFD_CCP_CALL(5U, 135U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      135U, 1, (real_T)*chartInstance->c42_state_ST_CAN, (real_T)
      chartInstance->c42_NORMAL, 0, 0U, *chartInstance->c42_state_ST_CAN ==
      chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_b_temp = c42_temp;
  if (c42_temp) {
    c42_b_temp = (_SFD_CCP_CALL(5U, 135U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      135U, 2, (real_T)chartInstance->c42_CD_STAUX_FUNCTION, (real_T)
      chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c42_CD_STAUX_FUNCTION != chartInstance->c42_NON_FUNCTIONAL)
      != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_out = (CV_TRANSITION_EVAL(135U, (int32_T)c42_b_temp) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 135U, chartInstance->c42_sfEvent);
    c42_b_exit_internal_Functional(chartInstance);
    chartInstance->c42_b_tp_Functional = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 56U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_SIRIUS2 = c42_IN_Aux_Enable_State_ST;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 52U, chartInstance->c42_sfEvent);
    chartInstance->c42_b_tp_Aux_Enable_State_ST = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 167U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_b_is_Aux_Enable_State_ST == c42_IN_Standard_Flow) {
    } else {
      chartInstance->c42_b_is_Aux_Enable_State_ST = c42_IN_Standard_Flow;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 55U, chartInstance->c42_sfEvent);
      chartInstance->c42_e_tp_Standard_Flow = 1U;
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      matlab_UpdateEEVar();
    }
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 137U,
                 chartInstance->c42_sfEvent);
    c42_c_temp = (_SFD_CCP_CALL(5U, 137U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      137U, 0, (real_T)*chartInstance->c42_can_AuxEnable_ACD, (real_T)
      chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ACD ==
      chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (c42_c_temp) {
      c42_c_temp = (_SFD_CCP_CALL(5U, 137U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        137U, 1, (real_T)*chartInstance->c42_state_ACD_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 0U, *chartInstance->c42_state_ACD_CAN ==
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_d_temp = c42_c_temp;
    if (c42_c_temp) {
      c42_d_temp = (_SFD_CCP_CALL(5U, 137U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        137U, 2, (real_T)chartInstance->c42_CD_RACD_FUNCTION, (real_T)
        chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c42_CD_RACD_FUNCTION != chartInstance->c42_NON_FUNCTIONAL)
        != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(137U, (int32_T)c42_d_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 137U, chartInstance->c42_sfEvent);
      c42_b_exit_internal_Functional(chartInstance);
      chartInstance->c42_b_tp_Functional = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 56U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_SIRIUS2 = c42_IN_Aux_Enable_State_ACD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 48U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Aux_Enable_State_ACD = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 172U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_b_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow)
      {
      } else {
        chartInstance->c42_b_is_Aux_Enable_State_ACD = c42_IN_Standard_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 51U, chartInstance->c42_sfEvent);
        chartInstance->c42_f_tp_Standard_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        c42_set_ee_AuxFlow(chartInstance, 0,
                           chartInstance->c42_AUX_FLOW_INACTIVE);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 56U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_b_is_Functional) {
       case c42_b_IN_Enabled:
        CV_STATE_EVAL(56, 0, c42_b_IN_Enabled);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 143U,
                     chartInstance->c42_sfEvent);
        c42_e_temp = (_SFD_CCP_CALL(5U, 143U, 0, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 143U, 0, (real_T)*chartInstance->c42_state_Engine, (real_T)
           chartInstance->c42_ENGINE_CRANKING, 0, 0U,
           *chartInstance->c42_state_Engine ==
           chartInstance->c42_ENGINE_CRANKING) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
        if (!c42_e_temp) {
          c42_e_temp = (_SFD_CCP_CALL(5U, 143U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 143U, 1, (real_T)*chartInstance->c42_state_System, (real_T)
             chartInstance->c42_SYS_NORMAL, 0, 1U,
             *chartInstance->c42_state_System != chartInstance->c42_SYS_NORMAL)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_f_temp = c42_e_temp;
        if (!c42_e_temp) {
          c42_f_temp = (_SFD_CCP_CALL(5U, 143U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 143U, 2, (real_T)*chartInstance->c42_state_Console, (real_T)
             chartInstance->c42_ACTIVE, 0, 1U, *chartInstance->c42_state_Console
             != chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_c_out = (CV_TRANSITION_EVAL(143U, (int32_T)c42_f_temp) != 0);
        if (c42_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 143U, chartInstance->c42_sfEvent);
          c42_b_exit_internal_Enabled(chartInstance);
          chartInstance->c42_d_tp_Enabled = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Functional = c42_b_IN_Inactive;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 63U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Inactive = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 142U,
                       chartInstance->c42_sfEvent);
          c42_i_temp = (_SFD_CCP_CALL(5U, 142U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 142U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_i_temp) {
            c42_i_temp = (_SFD_CCP_CALL(5U, 142U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 142U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_d_out = (CV_TRANSITION_EVAL(142U, (int32_T)c42_i_temp) != 0);
          if (c42_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 142U, chartInstance->c42_sfEvent);
            c42_b_exit_internal_Enabled(chartInstance);
            chartInstance->c42_d_tp_Enabled = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_is_Functional = c42_b_IN_Inactive_Fault;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 64U, chartInstance->c42_sfEvent);
            chartInstance->c42_b_tp_Inactive_Fault = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 145U,
                         chartInstance->c42_sfEvent);
            c42_f_out = (CV_TRANSITION_EVAL(145U, (int32_T)(_SFD_CCP_CALL(5U,
              145U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 145U, 0, (real_T)
              *chartInstance->c42_state_AuxPot, (real_T)
              chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
              *chartInstance->c42_state_AuxPot ==
              chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_f_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 145U,
                           chartInstance->c42_sfEvent);
              c42_b_exit_internal_Enabled(chartInstance);
              chartInstance->c42_d_tp_Enabled = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
              chartInstance->c42_b_is_Functional =
                c42_b_IN_Inactive_Out_Of_Neutral;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 65U, chartInstance->c42_sfEvent);
              chartInstance->c42_b_tp_Inactive_Out_Of_Neutral = 1U;
              *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                    25U);
              *chartInstance->c42_aux_Flow =
                chartInstance->c42_AUX_FLOW_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 57U,
                           chartInstance->c42_sfEvent);
              switch (chartInstance->c42_b_is_Enabled) {
               case c42_IN_Active:
                CV_STATE_EVAL(57, 0, c42_IN_Active);
                c42_b_Active(chartInstance);
                break;

               case c42_IN_Off:
                CV_STATE_EVAL(57, 0, c42_IN_Off);
                *chartInstance->c42_aux_Flow =
                  chartInstance->c42_AUX_FLOW_INACTIVE;
                *chartInstance->c42_state_AuxEnable =
                  chartInstance->c42_INACTIVE;
                _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 158U,
                             chartInstance->c42_sfEvent);
                c42_k_temp = (_SFD_CCP_CALL(5U, 158U, 0,
                  (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
                  chartInstance->c42_sfEvent) != 0U);
                if (!c42_k_temp) {
                  c42_k_temp = (_SFD_CCP_CALL(5U, 158U, 1,
                    (*chartInstance->c42_aux_DetentHold != 0) != 0U,
                    chartInstance->c42_sfEvent) != 0U);
                }

                c42_g_out = (CV_TRANSITION_EVAL(158U, (int32_T)c42_k_temp) != 0);
                if (c42_g_out) {
                  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 158U,
                               chartInstance->c42_sfEvent);
                  c42_set_state_Buzzer(chartInstance, 0,
                                       chartInstance->c42_SINGLE_SHORT_BEEP);
                  ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
                  chartInstance->c42_b_tp_Off = 0U;
                  _SFD_CS_CALL(STATE_INACTIVE_TAG, 62U,
                               chartInstance->c42_sfEvent);
                  chartInstance->c42_b_is_Enabled = c42_IN_Active;
                  _SFD_CS_CALL(STATE_ACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
                  chartInstance->c42_b_tp_Active = 1U;
                  if (chartInstance->c42_b_is_Active == c42_IN_Standard_Flow) {
                  } else {
                    chartInstance->c42_b_is_Active = c42_IN_Standard_Flow;
                    _SFD_CS_CALL(STATE_ACTIVE_TAG, 61U,
                                 chartInstance->c42_sfEvent);
                    chartInstance->c42_d_tp_Standard_Flow = 1U;
                    *chartInstance->c42_aux_Flow =
                      chartInstance->c42_AUX_FLOW_STANDARD;
                    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow,
                                          27U);
                    c42_set_ee_AuxFlow(chartInstance, 0,
                                       chartInstance->c42_AUX_FLOW_STANDARD);
                    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
                    *chartInstance->c42_state_AuxEnable =
                      chartInstance->c42_ACTIVE_MODE_ONE;
                    _SFD_DATA_RANGE_CHECK((real_T)
                                          *chartInstance->c42_state_AuxEnable,
                                          25U);
                    matlab_UpdateEEVar();
                  }
                } else {
                  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 62U,
                               chartInstance->c42_sfEvent);
                }

                _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 62U,
                             chartInstance->c42_sfEvent);
                break;

               default:
                CV_STATE_EVAL(57, 0, 0);

                /* Unreachable state, for coverage only */
                chartInstance->c42_b_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
                _SFD_CS_CALL(STATE_INACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
                break;
              }
            }
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 57U, chartInstance->c42_sfEvent);
        break;

       case c42_b_IN_Inactive:
        CV_STATE_EVAL(56, 0, c42_b_IN_Inactive);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 141U,
                     chartInstance->c42_sfEvent);
        c42_g_temp = (_SFD_CCP_CALL(5U, 141U, 0, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 141U, 0, (real_T)*chartInstance->c42_state_Engine, (real_T)
           chartInstance->c42_ENGINE_CRANKING, 0, 1U,
           *chartInstance->c42_state_Engine !=
           chartInstance->c42_ENGINE_CRANKING) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
        if (c42_g_temp) {
          c42_g_temp = (_SFD_CCP_CALL(5U, 141U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 141U, 1, (real_T)*chartInstance->c42_state_System, (real_T)
             chartInstance->c42_SYS_NORMAL, 0, 0U,
             *chartInstance->c42_state_System == chartInstance->c42_SYS_NORMAL)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_h_temp = c42_g_temp;
        if (c42_g_temp) {
          c42_h_temp = (_SFD_CCP_CALL(5U, 141U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 141U, 2, (real_T)*chartInstance->c42_state_Console, (real_T)
             chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_state_Console
             == chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_j_temp = c42_h_temp;
        if (c42_h_temp) {
          c42_j_temp = (_SFD_CCP_CALL(5U, 141U, 3,
            *chartInstance->c42_flag_InitEERead != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_e_out = (CV_TRANSITION_EVAL(141U, (int32_T)c42_j_temp) != 0);
        if (c42_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 141U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Inactive = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 63U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Functional = c42_b_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_tp_Enabled = 1U;
          c42_b_enter_internal_Enabled(chartInstance);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 63U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 63U, chartInstance->c42_sfEvent);
        break;

       case c42_b_IN_Inactive_Fault:
        CV_STATE_EVAL(56, 0, c42_b_IN_Inactive_Fault);
        c42_Inactive_Fault(chartInstance);
        break;

       case c42_b_IN_Inactive_Out_Of_Neutral:
        CV_STATE_EVAL(56, 0, c42_b_IN_Inactive_Out_Of_Neutral);
        c42_b_Inactive_Out_Of_Neutral(chartInstance);
        break;

       default:
        CV_STATE_EVAL(56, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_b_is_Functional = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 56U, chartInstance->c42_sfEvent);
}

static void c42_b_exit_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_b_is_Functional) {
   case c42_b_IN_Enabled:
    CV_STATE_EVAL(56, 1, c42_b_IN_Enabled);
    c42_b_exit_internal_Enabled(chartInstance);
    chartInstance->c42_d_tp_Enabled = 0U;
    chartInstance->c42_b_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Inactive:
    CV_STATE_EVAL(56, 1, c42_b_IN_Inactive);
    chartInstance->c42_b_tp_Inactive = 0U;
    chartInstance->c42_b_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 63U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Inactive_Fault:
    CV_STATE_EVAL(56, 1, c42_b_IN_Inactive_Fault);
    chartInstance->c42_b_tp_Inactive_Fault = 0U;
    chartInstance->c42_b_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 64U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Inactive_Out_Of_Neutral:
    CV_STATE_EVAL(56, 1, c42_b_IN_Inactive_Out_Of_Neutral);
    chartInstance->c42_b_tp_Inactive_Out_Of_Neutral = 0U;
    chartInstance->c42_b_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 65U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(56, 1, 0);
    chartInstance->c42_b_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_b_enter_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 153U, chartInstance->c42_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 154U,
               chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(154U, (int32_T)(_SFD_CCP_CALL(5U, 154U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 154U, 0, (real_T)c42_get_ee_AuxFlow
    (chartInstance, 0), (real_T)chartInstance->c42_AUX_FLOW_INACTIVE, 0, 0U,
    c42_get_ee_AuxFlow(chartInstance, 0) == chartInstance->c42_AUX_FLOW_INACTIVE)
    != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 154U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_b_is_Enabled == c42_IN_Off) {
    } else {
      chartInstance->c42_b_is_Enabled = c42_IN_Off;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 62U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Off = 1U;
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      matlab_UpdateEEVar();
    }
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 155U, chartInstance->c42_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 159U,
                 chartInstance->c42_sfEvent);
    c42_b_out = (CV_TRANSITION_EVAL(159U, (int32_T)(_SFD_CCP_CALL(5U, 159U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 159U, 0, (real_T)c42_get_ee_AuxFlow
      (chartInstance, 0), (real_T)chartInstance->c42_AUX_FLOW_LOW, 0, 0U,
      c42_get_ee_AuxFlow(chartInstance, 0) == chartInstance->c42_AUX_FLOW_LOW)
      != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 159U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_is_Enabled = c42_IN_Active;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Active = 1U;
      if (chartInstance->c42_b_is_Active == c42_IN_Low_Flow) {
      } else {
        chartInstance->c42_b_is_Active = c42_IN_Low_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 59U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_Low_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_LOW);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      }
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 160U, chartInstance->c42_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 161U,
                   chartInstance->c42_sfEvent);
      c42_c_out = (CV_TRANSITION_EVAL(161U, (int32_T)(_SFD_CCP_CALL(5U, 161U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 161U, 0, (real_T)c42_get_ee_AuxFlow
        (chartInstance, 0), (real_T)chartInstance->c42_AUX_FLOW_MEDIUM, 0, 0U,
        c42_get_ee_AuxFlow(chartInstance, 0) ==
        chartInstance->c42_AUX_FLOW_MEDIUM) != 0U, chartInstance->c42_sfEvent)
        != 0U)) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 161U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_is_Enabled = c42_IN_Active;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_Active = 1U;
        if (chartInstance->c42_b_is_Active == c42_IN_Medium_Flow) {
        } else {
          chartInstance->c42_b_is_Active = c42_IN_Medium_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 60U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Medium_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_MEDIUM);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          matlab_UpdateEEVar();
        }
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 162U, chartInstance->c42_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 163U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_is_Enabled = c42_IN_Active;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_Active = 1U;
        if (chartInstance->c42_b_is_Active == c42_IN_Standard_Flow) {
        } else {
          chartInstance->c42_b_is_Active = c42_IN_Standard_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 61U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_tp_Standard_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_STANDARD);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          matlab_UpdateEEVar();
        }
      }
    }
  }
}

static void c42_b_exit_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_b_is_Enabled) {
   case c42_IN_Active:
    CV_STATE_EVAL(57, 1, c42_IN_Active);
    c42_b_exit_internal_Active(chartInstance);
    chartInstance->c42_b_tp_Active = 0U;
    chartInstance->c42_b_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Off:
    CV_STATE_EVAL(57, 1, c42_IN_Off);
    chartInstance->c42_b_tp_Off = 0U;
    chartInstance->c42_b_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 62U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(57, 1, 0);
    chartInstance->c42_b_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_b_Active(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_temp;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_b_temp;
  boolean_T c42_e_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 157U,
               chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(157U, (int32_T)(_SFD_CCP_CALL(5U, 157U, 0,
    (chartInstance->c42_sfEvent == c42_event_disable_aux) != 0U,
    chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 157U, chartInstance->c42_sfEvent);
    c42_b_exit_internal_Active(chartInstance);
    chartInstance->c42_b_tp_Active = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
    chartInstance->c42_b_is_Enabled = c42_IN_Off;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 62U, chartInstance->c42_sfEvent);
    chartInstance->c42_b_tp_Off = 1U;
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    matlab_UpdateEEVar();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 58U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 58U,
                 chartInstance->c42_sfEvent);
    switch (chartInstance->c42_b_is_Active) {
     case c42_IN_Low_Flow:
      CV_STATE_EVAL(58, 0, c42_IN_Low_Flow);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 165U,
                   chartInstance->c42_sfEvent);
      c42_temp = (_SFD_CCP_CALL(5U, 165U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U);
      if (c42_temp) {
        c42_temp = (_SFD_CCP_CALL(5U, 165U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          165U, 0, (real_T)*chartInstance->c42_state_DetentEnable, (real_T)
          chartInstance->c42_ACTIVE, 0, 0U,
          *chartInstance->c42_state_DetentEnable == chartInstance->c42_ACTIVE)
          != 0U, chartInstance->c42_sfEvent) != 0U);
      }

      c42_d_out = (CV_TRANSITION_EVAL(165U, (int32_T)c42_temp) != 0);
      if (c42_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 165U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        chartInstance->c42_b_tp_Low_Flow = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 59U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_is_Active = c42_IN_Standard_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 61U, chartInstance->c42_sfEvent);
        chartInstance->c42_d_tp_Standard_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0,
                           chartInstance->c42_AUX_FLOW_STANDARD);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 156U,
                     chartInstance->c42_sfEvent);
        c42_b_temp = (_SFD_CCP_CALL(5U, 156U, 0,
          (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (c42_b_temp) {
          c42_b_temp = (_SFD_CCP_CALL(5U, 156U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 156U, 0, (real_T)*chartInstance->c42_state_DetentEnable,
             (real_T)chartInstance->c42_ACTIVE, 0, 1U,
             *chartInstance->c42_state_DetentEnable != chartInstance->c42_ACTIVE)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_e_out = (CV_TRANSITION_EVAL(156U, (int32_T)c42_b_temp) != 0);
        if (c42_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 156U, chartInstance->c42_sfEvent);
          c42_set_state_Buzzer(chartInstance, 0,
                               chartInstance->c42_SINGLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
          chartInstance->c42_b_tp_Low_Flow = 0U;
          chartInstance->c42_b_is_Active = c42_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 59U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Active = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 58U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_is_Enabled = c42_IN_Off;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 62U, chartInstance->c42_sfEvent);
          chartInstance->c42_b_tp_Off = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 59U,
                       chartInstance->c42_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 59U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_b_is_Enabled != c42_IN_Active) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 58U, chartInstance->c42_sfEvent);
      }
      break;

     case c42_IN_Medium_Flow:
      CV_STATE_EVAL(58, 0, c42_IN_Medium_Flow);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 164U,
                   chartInstance->c42_sfEvent);
      c42_b_out = (CV_TRANSITION_EVAL(164U, (int32_T)(_SFD_CCP_CALL(5U, 164U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 164U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        chartInstance->c42_b_tp_Medium_Flow = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 60U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_is_Active = c42_IN_Low_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 59U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_Low_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_LOW);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 60U,
                     chartInstance->c42_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 60U, chartInstance->c42_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 58U, chartInstance->c42_sfEvent);
      break;

     case c42_IN_Standard_Flow:
      CV_STATE_EVAL(58, 0, c42_IN_Standard_Flow);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 166U,
                   chartInstance->c42_sfEvent);
      c42_c_out = (CV_TRANSITION_EVAL(166U, (int32_T)(_SFD_CCP_CALL(5U, 166U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 166U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        chartInstance->c42_d_tp_Standard_Flow = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 61U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_is_Active = c42_IN_Medium_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 60U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_Medium_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_MEDIUM);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 61U,
                     chartInstance->c42_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 61U, chartInstance->c42_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 58U, chartInstance->c42_sfEvent);
      break;

     default:
      CV_STATE_EVAL(58, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c42_b_is_Active = c42_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 59U, chartInstance->c42_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 58U, chartInstance->c42_sfEvent);
      break;
    }
  }
}

static void c42_b_exit_internal_Active(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_b_is_Active) {
   case c42_IN_Low_Flow:
    CV_STATE_EVAL(58, 1, c42_IN_Low_Flow);
    chartInstance->c42_b_tp_Low_Flow = 0U;
    chartInstance->c42_b_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 59U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Medium_Flow:
    CV_STATE_EVAL(58, 1, c42_IN_Medium_Flow);
    chartInstance->c42_b_tp_Medium_Flow = 0U;
    chartInstance->c42_b_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 60U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(58, 1, c42_IN_Standard_Flow);
    chartInstance->c42_d_tp_Standard_Flow = 0U;
    chartInstance->c42_b_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 61U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(58, 1, 0);
    chartInstance->c42_b_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 59U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_Inactive_Fault(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
  *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 140U,
               chartInstance->c42_sfEvent);
  c42_temp = (_SFD_CCP_CALL(5U, 140U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 140U,
    0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)chartInstance->c42_OORH,
    0, 1U, *chartInstance->c42_state_AuxPot != chartInstance->c42_OORH) != 0U,
    chartInstance->c42_sfEvent) != 0U);
  if (c42_temp) {
    c42_temp = (_SFD_CCP_CALL(5U, 140U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      140U, 1, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
      chartInstance->c42_OORL, 0, 1U, *chartInstance->c42_state_AuxPot !=
      chartInstance->c42_OORL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_b_temp = c42_temp;
  if (c42_temp) {
    c42_b_temp = (_SFD_CCP_CALL(5U, 140U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      140U, 2, (real_T)*chartInstance->c42_state_System, (real_T)
      chartInstance->c42_SYS_NORMAL, 0, 0U, *chartInstance->c42_state_System ==
      chartInstance->c42_SYS_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_out = (CV_TRANSITION_EVAL(140U, (int32_T)c42_b_temp) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 140U, chartInstance->c42_sfEvent);
    chartInstance->c42_b_tp_Inactive_Fault = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 64U, chartInstance->c42_sfEvent);
    chartInstance->c42_b_is_Functional = c42_b_IN_Enabled;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
    chartInstance->c42_d_tp_Enabled = 1U;
    if (chartInstance->c42_b_is_Enabled == c42_IN_Off) {
    } else {
      chartInstance->c42_b_is_Enabled = c42_IN_Off;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 62U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Off = 1U;
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      matlab_UpdateEEVar();
    }
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 64U,
                 chartInstance->c42_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 64U, chartInstance->c42_sfEvent);
}

static void c42_b_Inactive_Out_Of_Neutral(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_temp;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_b_temp;
  boolean_T c42_c_temp;
  boolean_T c42_d_out;
  *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
  *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 152U,
               chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(152U, (int32_T)(_SFD_CCP_CALL(5U, 152U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 152U, 0, (real_T)
    *chartInstance->c42_state_Console, (real_T)chartInstance->c42_ACTIVE, 0, 1U,
    *chartInstance->c42_state_Console != chartInstance->c42_ACTIVE) != 0U,
    chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 152U, chartInstance->c42_sfEvent);
    chartInstance->c42_b_tp_Inactive_Out_Of_Neutral = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 65U, chartInstance->c42_sfEvent);
    chartInstance->c42_b_is_Functional = c42_b_IN_Inactive;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 63U, chartInstance->c42_sfEvent);
    chartInstance->c42_b_tp_Inactive = 1U;
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 144U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 144U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      144U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
      chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
      chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 144U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        144U, 1, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
        chartInstance->c42_OORL, 0, 0U, *chartInstance->c42_state_AuxPot ==
        chartInstance->c42_OORL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(144U, (int32_T)c42_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 144U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Inactive_Out_Of_Neutral = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 65U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_is_Functional = c42_b_IN_Inactive_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 64U, chartInstance->c42_sfEvent);
      chartInstance->c42_b_tp_Inactive_Fault = 1U;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 148U,
                   chartInstance->c42_sfEvent);
      c42_c_out = (CV_TRANSITION_EVAL(148U, (int32_T)(_SFD_CCP_CALL(5U, 148U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 148U, 0, (real_T)
        *chartInstance->c42_state_AuxPot, (real_T)
        chartInstance->c42_NOT_IN_NEUTRAL, 0, 1U,
        *chartInstance->c42_state_AuxPot != chartInstance->c42_NOT_IN_NEUTRAL)
        != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 148U, chartInstance->c42_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 147U,
                     chartInstance->c42_sfEvent);
        c42_b_temp = (_SFD_CCP_CALL(5U, 147U, 0,
          (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (!c42_b_temp) {
          c42_b_temp = (_SFD_CCP_CALL(5U, 147U, 1,
            (*chartInstance->c42_aux_DetentHold != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_c_temp = c42_b_temp;
        if (c42_b_temp) {
          c42_c_temp = (_SFD_CCP_CALL(5U, 147U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 147U, 0, (real_T)*chartInstance->c42_aux_Flow, (real_T)
             chartInstance->c42_AUX_FLOW_INACTIVE, 0, 1U,
             *chartInstance->c42_aux_Flow !=
             chartInstance->c42_AUX_FLOW_INACTIVE) != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_d_out = (CV_TRANSITION_EVAL(147U, (int32_T)c42_c_temp) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 147U, chartInstance->c42_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 149U, chartInstance->c42_sfEvent);
          c42_set_state_Buzzer(chartInstance, 0,
                               chartInstance->c42_SINGLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 150U, chartInstance->c42_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 151U, chartInstance->c42_sfEvent);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 146U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_tp_Inactive_Out_Of_Neutral = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 65U, chartInstance->c42_sfEvent);
        chartInstance->c42_b_is_Functional = c42_b_IN_Enabled;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 57U, chartInstance->c42_sfEvent);
        chartInstance->c42_d_tp_Enabled = 1U;
        c42_b_enter_internal_Enabled(chartInstance);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 65U,
                     chartInstance->c42_sfEvent);
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 65U, chartInstance->c42_sfEvent);
}

static void c42_b_exit_internal_Aux_Enable_State_ST
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c42_b_is_Aux_Enable_State_ST) {
   case c42_IN_Inactive_Latched:
    CV_STATE_EVAL(52, 1, c42_IN_Inactive_Latched);
    chartInstance->c42_c_tp_Inactive_Latched = 0U;
    chartInstance->c42_b_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 53U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive_Temp:
    CV_STATE_EVAL(52, 1, c42_IN_Inactive_Temp);
    chartInstance->c42_c_tp_Inactive_Temp = 0U;
    chartInstance->c42_b_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 54U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(52, 1, c42_IN_Standard_Flow);
    chartInstance->c42_e_tp_Standard_Flow = 0U;
    chartInstance->c42_b_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 55U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(52, 1, 0);
    chartInstance->c42_b_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 53U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_b_exit_internal_Aux_Enable_State_ACD
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c42_b_is_Aux_Enable_State_ACD) {
   case c42_IN_Inactive_Latched:
    CV_STATE_EVAL(48, 1, c42_IN_Inactive_Latched);
    chartInstance->c42_d_tp_Inactive_Latched = 0U;
    chartInstance->c42_b_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 49U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive_Temp:
    CV_STATE_EVAL(48, 1, c42_IN_Inactive_Temp);
    chartInstance->c42_d_tp_Inactive_Temp = 0U;
    chartInstance->c42_b_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 50U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(48, 1, c42_IN_Standard_Flow);
    chartInstance->c42_f_tp_Standard_Flow = 0U;
    chartInstance->c42_b_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 51U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(48, 1, 0);
    chartInstance->c42_b_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 49U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_SIRIUS2_HIFLOW(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_h_temp;
  boolean_T c42_i_temp;
  boolean_T c42_j_temp;
  boolean_T c42_k_temp;
  boolean_T c42_l_temp;
  boolean_T c42_g_out;
  boolean_T c42_h_out;
  boolean_T c42_i_out;
  boolean_T c42_j_out;
  boolean_T guard1 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 66U, chartInstance->c42_sfEvent);
  switch (chartInstance->c42_is_SIRIUS2_HIFLOW) {
   case c42_IN_Aux_Enable_State_ACD:
    CV_STATE_EVAL(66, 0, c42_IN_Aux_Enable_State_ACD);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 89U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 89U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 89U,
      0, (real_T)*chartInstance->c42_can_AuxEnable_ACD, (real_T)
      chartInstance->c42_INACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ACD ==
      chartInstance->c42_INACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 89U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        89U, 1, (real_T)*chartInstance->c42_state_ACD_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 1U, *chartInstance->c42_state_ACD_CAN !=
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_out = (CV_TRANSITION_EVAL(89U, (int32_T)c42_temp) != 0);
    if (c42_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 89U, chartInstance->c42_sfEvent);
      c42_c_exit_internal_Aux_Enable_State_ACD(chartInstance);
      chartInstance->c42_c_tp_Aux_Enable_State_ACD = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 67U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_SIRIUS2_HIFLOW = c42_IN_Functional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 75U, chartInstance->c42_sfEvent);
      chartInstance->c42_c_tp_Functional = 1U;
      c42_c_enter_internal_Functional(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 67U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_c_is_Aux_Enable_State_ACD) {
       case c42_IN_Inactive_Latched:
        CV_STATE_EVAL(67, 0, c42_IN_Inactive_Latched);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 68U,
                     chartInstance->c42_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 68U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Inactive_Temp:
        CV_STATE_EVAL(67, 0, c42_IN_Inactive_Temp);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 126U,
                     chartInstance->c42_sfEvent);
        c42_c_out = (CV_TRANSITION_EVAL(126U, (int32_T)(_SFD_CCP_CALL(5U, 126U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 126U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 1U,
          *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 126U, chartInstance->c42_sfEvent);
          chartInstance->c42_f_tp_Inactive_Temp = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 69U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_is_Aux_Enable_State_ACD = c42_IN_Standard_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 70U, chartInstance->c42_sfEvent);
          chartInstance->c42_i_tp_Standard_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 69U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 69U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Standard_Flow:
        CV_STATE_EVAL(67, 0, c42_IN_Standard_Flow);
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 123U,
                     chartInstance->c42_sfEvent);
        c42_e_out = (CV_TRANSITION_EVAL(123U, (int32_T)(_SFD_CCP_CALL(5U, 123U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 123U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c42_state_Engine == chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 123U, chartInstance->c42_sfEvent);
          chartInstance->c42_i_tp_Standard_Flow = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 70U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_is_Aux_Enable_State_ACD = c42_IN_Inactive_Temp;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 69U, chartInstance->c42_sfEvent);
          chartInstance->c42_f_tp_Inactive_Temp = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 124U,
                       chartInstance->c42_sfEvent);
          c42_c_temp = (_SFD_CCP_CALL(5U, 124U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 124U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_c_temp) {
            c42_c_temp = (_SFD_CCP_CALL(5U, 124U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 124U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_e_temp = c42_c_temp;
          if (!c42_c_temp) {
            c42_e_temp = (_SFD_CCP_CALL(5U, 124U, 2, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 124U, 2, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_g_temp = c42_e_temp;
          if (!c42_e_temp) {
            c42_g_temp = (_SFD_CCP_CALL(5U, 124U, 3, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 124U, 3, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORH, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORH) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_i_temp = c42_g_temp;
          if (!c42_g_temp) {
            c42_i_temp = (_SFD_CCP_CALL(5U, 124U, 4, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 124U, 4, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_k_temp = c42_i_temp;
          if (!c42_i_temp) {
            c42_k_temp = (_SFD_CCP_CALL(5U, 124U, 5, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 124U, 5, (real_T)
                                 *chartInstance->c42_state_System, (real_T)
                                 chartInstance->c42_SYS_NORMAL, 0, 1U,
                                 *chartInstance->c42_state_System !=
                                 chartInstance->c42_SYS_NORMAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_g_out = (CV_TRANSITION_EVAL(124U, (int32_T)c42_k_temp) != 0);
          guard1 = false;
          if (c42_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 124U, chartInstance->c42_sfEvent);
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 125U,
                         chartInstance->c42_sfEvent);
            c42_i_out = (CV_TRANSITION_EVAL(125U, (int32_T)(_SFD_CCP_CALL(5U,
              125U, 0, (chartInstance->c42_sfEvent == c42_event_disable_aux) !=
              0U, chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_i_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 125U,
                           chartInstance->c42_sfEvent);
              guard1 = true;
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 70U,
                           chartInstance->c42_sfEvent);
            }
          }

          if (guard1) {
            chartInstance->c42_i_tp_Standard_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 70U, chartInstance->c42_sfEvent);
            chartInstance->c42_c_is_Aux_Enable_State_ACD =
              c42_IN_Inactive_Latched;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c42_sfEvent);
            chartInstance->c42_f_tp_Inactive_Latched = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 70U, chartInstance->c42_sfEvent);
        break;

       default:
        CV_STATE_EVAL(67, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_c_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c42_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 67U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Aux_Enable_State_ST:
    CV_STATE_EVAL(66, 0, c42_IN_Aux_Enable_State_ST);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 87U,
                 chartInstance->c42_sfEvent);
    c42_b_temp = (_SFD_CCP_CALL(5U, 87U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      87U, 0, (real_T)*chartInstance->c42_can_AuxEnable_ST, (real_T)
      chartInstance->c42_INACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ST ==
      chartInstance->c42_INACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_b_temp) {
      c42_b_temp = (_SFD_CCP_CALL(5U, 87U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        87U, 1, (real_T)*chartInstance->c42_state_ST_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 1U, *chartInstance->c42_state_ST_CAN !=
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(87U, (int32_T)c42_b_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 87U, chartInstance->c42_sfEvent);
      c42_c_exit_internal_Aux_Enable_State_ST(chartInstance);
      chartInstance->c42_c_tp_Aux_Enable_State_ST = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 71U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_SIRIUS2_HIFLOW = c42_IN_Functional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 75U, chartInstance->c42_sfEvent);
      chartInstance->c42_c_tp_Functional = 1U;
      c42_c_enter_internal_Functional(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 71U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_c_is_Aux_Enable_State_ST) {
       case c42_IN_Inactive_Latched:
        CV_STATE_EVAL(71, 0, c42_IN_Inactive_Latched);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 72U,
                     chartInstance->c42_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 72U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Inactive_Temp:
        CV_STATE_EVAL(71, 0, c42_IN_Inactive_Temp);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 120U,
                     chartInstance->c42_sfEvent);
        c42_d_out = (CV_TRANSITION_EVAL(120U, (int32_T)(_SFD_CCP_CALL(5U, 120U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 120U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 1U,
          *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 120U, chartInstance->c42_sfEvent);
          chartInstance->c42_e_tp_Inactive_Temp = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 73U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_is_Aux_Enable_State_ST = c42_IN_Standard_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 74U, chartInstance->c42_sfEvent);
          chartInstance->c42_h_tp_Standard_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 73U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 73U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Standard_Flow:
        CV_STATE_EVAL(71, 0, c42_IN_Standard_Flow);
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 118U,
                     chartInstance->c42_sfEvent);
        c42_f_out = (CV_TRANSITION_EVAL(118U, (int32_T)(_SFD_CCP_CALL(5U, 118U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 118U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c42_state_Engine == chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 118U, chartInstance->c42_sfEvent);
          chartInstance->c42_h_tp_Standard_Flow = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 74U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_is_Aux_Enable_State_ST = c42_IN_Inactive_Temp;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 73U, chartInstance->c42_sfEvent);
          chartInstance->c42_e_tp_Inactive_Temp = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 119U,
                       chartInstance->c42_sfEvent);
          c42_d_temp = (_SFD_CCP_CALL(5U, 119U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 119U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_d_temp) {
            c42_d_temp = (_SFD_CCP_CALL(5U, 119U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 119U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_f_temp = c42_d_temp;
          if (!c42_d_temp) {
            c42_f_temp = (_SFD_CCP_CALL(5U, 119U, 2, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 119U, 2, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_h_temp = c42_f_temp;
          if (!c42_f_temp) {
            c42_h_temp = (_SFD_CCP_CALL(5U, 119U, 3, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 119U, 3, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORH, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORH) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_j_temp = c42_h_temp;
          if (!c42_h_temp) {
            c42_j_temp = (_SFD_CCP_CALL(5U, 119U, 4, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 119U, 4, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_l_temp = c42_j_temp;
          if (!c42_j_temp) {
            c42_l_temp = (_SFD_CCP_CALL(5U, 119U, 5, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 119U, 5, (real_T)
                                 *chartInstance->c42_state_System, (real_T)
                                 chartInstance->c42_SYS_NORMAL, 0, 1U,
                                 *chartInstance->c42_state_System !=
                                 chartInstance->c42_SYS_NORMAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_h_out = (CV_TRANSITION_EVAL(119U, (int32_T)c42_l_temp) != 0);
          guard1 = false;
          if (c42_h_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 119U, chartInstance->c42_sfEvent);
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 121U,
                         chartInstance->c42_sfEvent);
            c42_j_out = (CV_TRANSITION_EVAL(121U, (int32_T)(_SFD_CCP_CALL(5U,
              121U, 0, (chartInstance->c42_sfEvent == c42_event_disable_aux) !=
              0U, chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_j_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 121U,
                           chartInstance->c42_sfEvent);
              guard1 = true;
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 74U,
                           chartInstance->c42_sfEvent);
            }
          }

          if (guard1) {
            chartInstance->c42_h_tp_Standard_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 74U, chartInstance->c42_sfEvent);
            chartInstance->c42_c_is_Aux_Enable_State_ST =
              c42_IN_Inactive_Latched;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 72U, chartInstance->c42_sfEvent);
            chartInstance->c42_e_tp_Inactive_Latched = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 74U, chartInstance->c42_sfEvent);
        break;

       default:
        CV_STATE_EVAL(71, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_c_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 72U, chartInstance->c42_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 71U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Functional:
    CV_STATE_EVAL(66, 0, c42_IN_Functional);
    c42_c_Functional(chartInstance);
    break;

   default:
    CV_STATE_EVAL(66, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c42_is_SIRIUS2_HIFLOW = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 67U, chartInstance->c42_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 66U, chartInstance->c42_sfEvent);
}

static void c42_c_enter_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 90U, chartInstance->c42_sfEvent);
  if (chartInstance->c42_c_is_Functional == c42_b_IN_Inactive) {
  } else {
    chartInstance->c42_c_is_Functional = c42_b_IN_Inactive;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 83U, chartInstance->c42_sfEvent);
    chartInstance->c42_c_tp_Inactive = 1U;
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
  }
}

static void c42_c_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_b_out;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_c_out;
  boolean_T c42_h_temp;
  boolean_T c42_i_temp;
  boolean_T c42_j_temp;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_k_temp;
  boolean_T c42_g_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 86U, chartInstance->c42_sfEvent);
  c42_temp = (_SFD_CCP_CALL(5U, 86U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 86U, 0,
    (real_T)*chartInstance->c42_can_AuxEnable_ST, (real_T)
    chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ST ==
    chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
  if (c42_temp) {
    c42_temp = (_SFD_CCP_CALL(5U, 86U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 86U,
      1, (real_T)*chartInstance->c42_state_ST_CAN, (real_T)
      chartInstance->c42_NORMAL, 0, 0U, *chartInstance->c42_state_ST_CAN ==
      chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_b_temp = c42_temp;
  if (c42_temp) {
    c42_b_temp = (_SFD_CCP_CALL(5U, 86U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      86U, 2, (real_T)chartInstance->c42_CD_STAUX_FUNCTION, (real_T)
      chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c42_CD_STAUX_FUNCTION != chartInstance->c42_NON_FUNCTIONAL)
      != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_out = (CV_TRANSITION_EVAL(86U, (int32_T)c42_b_temp) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 86U, chartInstance->c42_sfEvent);
    c42_c_exit_internal_Functional(chartInstance);
    chartInstance->c42_c_tp_Functional = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 75U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_SIRIUS2_HIFLOW = c42_IN_Aux_Enable_State_ST;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 71U, chartInstance->c42_sfEvent);
    chartInstance->c42_c_tp_Aux_Enable_State_ST = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 117U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_c_is_Aux_Enable_State_ST == c42_IN_Standard_Flow) {
    } else {
      chartInstance->c42_c_is_Aux_Enable_State_ST = c42_IN_Standard_Flow;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 74U, chartInstance->c42_sfEvent);
      chartInstance->c42_h_tp_Standard_Flow = 1U;
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      matlab_UpdateEEVar();
    }
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 88U,
                 chartInstance->c42_sfEvent);
    c42_c_temp = (_SFD_CCP_CALL(5U, 88U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      88U, 0, (real_T)*chartInstance->c42_can_AuxEnable_ACD, (real_T)
      chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ACD ==
      chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (c42_c_temp) {
      c42_c_temp = (_SFD_CCP_CALL(5U, 88U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        88U, 1, (real_T)*chartInstance->c42_state_ACD_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 0U, *chartInstance->c42_state_ACD_CAN ==
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_d_temp = c42_c_temp;
    if (c42_c_temp) {
      c42_d_temp = (_SFD_CCP_CALL(5U, 88U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        88U, 2, (real_T)chartInstance->c42_CD_RACD_FUNCTION, (real_T)
        chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c42_CD_RACD_FUNCTION != chartInstance->c42_NON_FUNCTIONAL)
        != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(88U, (int32_T)c42_d_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 88U, chartInstance->c42_sfEvent);
      c42_c_exit_internal_Functional(chartInstance);
      chartInstance->c42_c_tp_Functional = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 75U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_SIRIUS2_HIFLOW = c42_IN_Aux_Enable_State_ACD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 67U, chartInstance->c42_sfEvent);
      chartInstance->c42_c_tp_Aux_Enable_State_ACD = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 122U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_c_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow)
      {
      } else {
        chartInstance->c42_c_is_Aux_Enable_State_ACD = c42_IN_Standard_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 70U, chartInstance->c42_sfEvent);
        chartInstance->c42_i_tp_Standard_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        c42_set_ee_AuxFlow(chartInstance, 0,
                           chartInstance->c42_AUX_FLOW_INACTIVE);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 75U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_c_is_Functional) {
       case c42_b_IN_Enabled:
        CV_STATE_EVAL(75, 0, c42_b_IN_Enabled);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 94U,
                     chartInstance->c42_sfEvent);
        c42_e_temp = (_SFD_CCP_CALL(5U, 94U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          94U, 0, (real_T)*chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c42_state_Engine == chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U);
        if (!c42_e_temp) {
          c42_e_temp = (_SFD_CCP_CALL(5U, 94U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 94U, 1, (real_T)*chartInstance->c42_state_System, (real_T)
             chartInstance->c42_SYS_NORMAL, 0, 1U,
             *chartInstance->c42_state_System != chartInstance->c42_SYS_NORMAL)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_f_temp = c42_e_temp;
        if (!c42_e_temp) {
          c42_f_temp = (_SFD_CCP_CALL(5U, 94U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 94U, 2, (real_T)*chartInstance->c42_state_Console, (real_T)
             chartInstance->c42_ACTIVE, 0, 1U, *chartInstance->c42_state_Console
             != chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_c_out = (CV_TRANSITION_EVAL(94U, (int32_T)c42_f_temp) != 0);
        if (c42_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 94U, chartInstance->c42_sfEvent);
          c42_c_exit_internal_Enabled(chartInstance);
          chartInstance->c42_e_tp_Enabled = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_is_Functional = c42_b_IN_Inactive;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 83U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Inactive = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 93U,
                       chartInstance->c42_sfEvent);
          c42_i_temp = (_SFD_CCP_CALL(5U, 93U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 93U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_i_temp) {
            c42_i_temp = (_SFD_CCP_CALL(5U, 93U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 93U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_d_out = (CV_TRANSITION_EVAL(93U, (int32_T)c42_i_temp) != 0);
          if (c42_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 93U, chartInstance->c42_sfEvent);
            c42_c_exit_internal_Enabled(chartInstance);
            chartInstance->c42_e_tp_Enabled = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
            chartInstance->c42_c_is_Functional = c42_b_IN_Inactive_Fault;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 84U, chartInstance->c42_sfEvent);
            chartInstance->c42_c_tp_Inactive_Fault = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 96U,
                         chartInstance->c42_sfEvent);
            c42_f_out = (CV_TRANSITION_EVAL(96U, (int32_T)(_SFD_CCP_CALL(5U, 96U,
              0, (boolean_T)CV_RELATIONAL_EVAL(5U, 96U, 0, (real_T)
              *chartInstance->c42_state_AuxPot, (real_T)
              chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
              *chartInstance->c42_state_AuxPot ==
              chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_f_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 96U,
                           chartInstance->c42_sfEvent);
              c42_c_exit_internal_Enabled(chartInstance);
              chartInstance->c42_e_tp_Enabled = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
              chartInstance->c42_c_is_Functional =
                c42_b_IN_Inactive_Out_Of_Neutral;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 85U, chartInstance->c42_sfEvent);
              chartInstance->c42_c_tp_Inactive_Out_Of_Neutral = 1U;
              *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                    25U);
              *chartInstance->c42_aux_Flow =
                chartInstance->c42_AUX_FLOW_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 76U,
                           chartInstance->c42_sfEvent);
              switch (chartInstance->c42_c_is_Enabled) {
               case c42_IN_Active:
                CV_STATE_EVAL(76, 0, c42_IN_Active);
                c42_c_Active(chartInstance);
                break;

               case c42_IN_Off:
                CV_STATE_EVAL(76, 0, c42_IN_Off);
                *chartInstance->c42_aux_Flow =
                  chartInstance->c42_AUX_FLOW_INACTIVE;
                *chartInstance->c42_state_AuxEnable =
                  chartInstance->c42_INACTIVE;
                _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 130U,
                             chartInstance->c42_sfEvent);
                c42_k_temp = (_SFD_CCP_CALL(5U, 130U, 0,
                  (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
                  chartInstance->c42_sfEvent) != 0U);
                if (!c42_k_temp) {
                  c42_k_temp = (_SFD_CCP_CALL(5U, 130U, 1,
                    (*chartInstance->c42_aux_DetentHold != 0) != 0U,
                    chartInstance->c42_sfEvent) != 0U);
                }

                c42_g_out = (CV_TRANSITION_EVAL(130U, (int32_T)c42_k_temp) != 0);
                if (c42_g_out) {
                  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 130U,
                               chartInstance->c42_sfEvent);
                  c42_set_state_Buzzer(chartInstance, 0,
                                       chartInstance->c42_SINGLE_SHORT_BEEP);
                  ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
                  chartInstance->c42_c_tp_Off = 0U;
                  _SFD_CS_CALL(STATE_INACTIVE_TAG, 82U,
                               chartInstance->c42_sfEvent);
                  chartInstance->c42_c_is_Enabled = c42_IN_Active;
                  _SFD_CS_CALL(STATE_ACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
                  chartInstance->c42_c_tp_Active = 1U;
                  if (chartInstance->c42_c_is_Active == c42_IN_High_Flow) {
                  } else {
                    chartInstance->c42_c_is_Active = c42_IN_High_Flow;
                    _SFD_CS_CALL(STATE_ACTIVE_TAG, 78U,
                                 chartInstance->c42_sfEvent);
                    chartInstance->c42_tp_High_Flow = 1U;
                    *chartInstance->c42_aux_Flow =
                      chartInstance->c42_AUX_FLOW_HIGH;
                    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow,
                                          27U);
                    c42_set_ee_AuxFlow(chartInstance, 0,
                                       chartInstance->c42_AUX_FLOW_HIGH);
                    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
                    *chartInstance->c42_state_AuxEnable =
                      chartInstance->c42_ACTIVE_MODE_ONE;
                    _SFD_DATA_RANGE_CHECK((real_T)
                                          *chartInstance->c42_state_AuxEnable,
                                          25U);
                    matlab_UpdateEEVar();
                  }
                } else {
                  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 82U,
                               chartInstance->c42_sfEvent);
                }

                _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 82U,
                             chartInstance->c42_sfEvent);
                break;

               default:
                CV_STATE_EVAL(76, 0, 0);

                /* Unreachable state, for coverage only */
                chartInstance->c42_c_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
                _SFD_CS_CALL(STATE_INACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
                break;
              }
            }
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 76U, chartInstance->c42_sfEvent);
        break;

       case c42_b_IN_Inactive:
        CV_STATE_EVAL(75, 0, c42_b_IN_Inactive);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 92U,
                     chartInstance->c42_sfEvent);
        c42_g_temp = (_SFD_CCP_CALL(5U, 92U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          92U, 0, (real_T)*chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 1U,
          *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U);
        if (c42_g_temp) {
          c42_g_temp = (_SFD_CCP_CALL(5U, 92U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 92U, 1, (real_T)*chartInstance->c42_state_System, (real_T)
             chartInstance->c42_SYS_NORMAL, 0, 0U,
             *chartInstance->c42_state_System == chartInstance->c42_SYS_NORMAL)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_h_temp = c42_g_temp;
        if (c42_g_temp) {
          c42_h_temp = (_SFD_CCP_CALL(5U, 92U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 92U, 2, (real_T)*chartInstance->c42_state_Console, (real_T)
             chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_state_Console
             == chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_j_temp = c42_h_temp;
        if (c42_h_temp) {
          c42_j_temp = (_SFD_CCP_CALL(5U, 92U, 3,
            *chartInstance->c42_flag_InitEERead != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_e_out = (CV_TRANSITION_EVAL(92U, (int32_T)c42_j_temp) != 0);
        if (c42_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 92U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Inactive = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 83U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_is_Functional = c42_b_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
          chartInstance->c42_e_tp_Enabled = 1U;
          c42_c_enter_internal_Enabled(chartInstance);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 83U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 83U, chartInstance->c42_sfEvent);
        break;

       case c42_b_IN_Inactive_Fault:
        CV_STATE_EVAL(75, 0, c42_b_IN_Inactive_Fault);
        c42_b_Inactive_Fault(chartInstance);
        break;

       case c42_b_IN_Inactive_Out_Of_Neutral:
        CV_STATE_EVAL(75, 0, c42_b_IN_Inactive_Out_Of_Neutral);
        c42_c_Inactive_Out_Of_Neutral(chartInstance);
        break;

       default:
        CV_STATE_EVAL(75, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_c_is_Functional = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 75U, chartInstance->c42_sfEvent);
}

static void c42_c_exit_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_c_is_Functional) {
   case c42_b_IN_Enabled:
    CV_STATE_EVAL(75, 1, c42_b_IN_Enabled);
    c42_c_exit_internal_Enabled(chartInstance);
    chartInstance->c42_e_tp_Enabled = 0U;
    chartInstance->c42_c_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Inactive:
    CV_STATE_EVAL(75, 1, c42_b_IN_Inactive);
    chartInstance->c42_c_tp_Inactive = 0U;
    chartInstance->c42_c_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 83U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Inactive_Fault:
    CV_STATE_EVAL(75, 1, c42_b_IN_Inactive_Fault);
    chartInstance->c42_c_tp_Inactive_Fault = 0U;
    chartInstance->c42_c_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 84U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Inactive_Out_Of_Neutral:
    CV_STATE_EVAL(75, 1, c42_b_IN_Inactive_Out_Of_Neutral);
    chartInstance->c42_c_tp_Inactive_Out_Of_Neutral = 0U;
    chartInstance->c42_c_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 85U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(75, 1, 0);
    chartInstance->c42_c_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_c_enter_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 104U, chartInstance->c42_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 105U,
               chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(105U, (int32_T)(_SFD_CCP_CALL(5U, 105U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 105U, 0, (real_T)c42_get_ee_AuxFlow
    (chartInstance, 0), (real_T)chartInstance->c42_AUX_FLOW_INACTIVE, 0, 0U,
    c42_get_ee_AuxFlow(chartInstance, 0) == chartInstance->c42_AUX_FLOW_INACTIVE)
    != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 105U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_c_is_Enabled == c42_IN_Off) {
    } else {
      chartInstance->c42_c_is_Enabled = c42_IN_Off;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 82U, chartInstance->c42_sfEvent);
      chartInstance->c42_c_tp_Off = 1U;
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      matlab_UpdateEEVar();
    }
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 106U, chartInstance->c42_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 109U,
                 chartInstance->c42_sfEvent);
    c42_b_out = (CV_TRANSITION_EVAL(109U, (int32_T)(_SFD_CCP_CALL(5U, 109U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 109U, 0, (real_T)c42_get_ee_AuxFlow
      (chartInstance, 0), (real_T)chartInstance->c42_AUX_FLOW_LOW, 0, 0U,
      c42_get_ee_AuxFlow(chartInstance, 0) == chartInstance->c42_AUX_FLOW_LOW)
      != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 109U, chartInstance->c42_sfEvent);
      chartInstance->c42_c_is_Enabled = c42_IN_Active;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
      chartInstance->c42_c_tp_Active = 1U;
      if (chartInstance->c42_c_is_Active == c42_b_IN_Low_Flow) {
      } else {
        chartInstance->c42_c_is_Active = c42_b_IN_Low_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 79U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_tp_Low_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_LOW);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      }
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 110U, chartInstance->c42_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 111U,
                   chartInstance->c42_sfEvent);
      c42_c_out = (CV_TRANSITION_EVAL(111U, (int32_T)(_SFD_CCP_CALL(5U, 111U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 111U, 0, (real_T)c42_get_ee_AuxFlow
        (chartInstance, 0), (real_T)chartInstance->c42_AUX_FLOW_MEDIUM, 0, 0U,
        c42_get_ee_AuxFlow(chartInstance, 0) ==
        chartInstance->c42_AUX_FLOW_MEDIUM) != 0U, chartInstance->c42_sfEvent)
        != 0U)) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 111U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_is_Enabled = c42_IN_Active;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_tp_Active = 1U;
        if (chartInstance->c42_c_is_Active == c42_b_IN_Medium_Flow) {
        } else {
          chartInstance->c42_c_is_Active = c42_b_IN_Medium_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 80U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Medium_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_MEDIUM);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          matlab_UpdateEEVar();
        }
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 112U, chartInstance->c42_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 113U,
                     chartInstance->c42_sfEvent);
        c42_d_out = (CV_TRANSITION_EVAL(113U, (int32_T)(_SFD_CCP_CALL(5U, 113U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 113U, 0, (real_T)
          c42_get_ee_AuxFlow(chartInstance, 0), (real_T)
          chartInstance->c42_AUX_FLOW_STANDARD, 0, 0U, c42_get_ee_AuxFlow
          (chartInstance, 0) == chartInstance->c42_AUX_FLOW_STANDARD) != 0U,
          chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 113U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_is_Enabled = c42_IN_Active;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Active = 1U;
          if (chartInstance->c42_c_is_Active == c42_b_IN_Standard_Flow) {
          } else {
            chartInstance->c42_c_is_Active = c42_b_IN_Standard_Flow;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 81U, chartInstance->c42_sfEvent);
            chartInstance->c42_g_tp_Standard_Flow = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            c42_set_ee_AuxFlow(chartInstance, 0,
                               chartInstance->c42_AUX_FLOW_STANDARD);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            *chartInstance->c42_state_AuxEnable =
              chartInstance->c42_ACTIVE_MODE_ONE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            matlab_UpdateEEVar();
          }
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 132U, chartInstance->c42_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 131U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_is_Enabled = c42_IN_Active;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Active = 1U;
          if (chartInstance->c42_c_is_Active == c42_IN_High_Flow) {
          } else {
            chartInstance->c42_c_is_Active = c42_IN_High_Flow;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 78U, chartInstance->c42_sfEvent);
            chartInstance->c42_tp_High_Flow = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_HIGH;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            c42_set_ee_AuxFlow(chartInstance, 0,
                               chartInstance->c42_AUX_FLOW_HIGH);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            *chartInstance->c42_state_AuxEnable =
              chartInstance->c42_ACTIVE_MODE_ONE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            matlab_UpdateEEVar();
          }
        }
      }
    }
  }
}

static void c42_c_exit_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_c_is_Enabled) {
   case c42_IN_Active:
    CV_STATE_EVAL(76, 1, c42_IN_Active);
    c42_c_exit_internal_Active(chartInstance);
    chartInstance->c42_c_tp_Active = 0U;
    chartInstance->c42_c_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Off:
    CV_STATE_EVAL(76, 1, c42_IN_Off);
    chartInstance->c42_c_tp_Off = 0U;
    chartInstance->c42_c_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 82U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(76, 1, 0);
    chartInstance->c42_c_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_c_Active(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_b_out;
  boolean_T c42_temp;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_b_temp;
  boolean_T c42_f_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 108U,
               chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(108U, (int32_T)(_SFD_CCP_CALL(5U, 108U, 0,
    (chartInstance->c42_sfEvent == c42_event_disable_aux) != 0U,
    chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 108U, chartInstance->c42_sfEvent);
    c42_c_exit_internal_Active(chartInstance);
    chartInstance->c42_c_tp_Active = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
    chartInstance->c42_c_is_Enabled = c42_IN_Off;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 82U, chartInstance->c42_sfEvent);
    chartInstance->c42_c_tp_Off = 1U;
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    matlab_UpdateEEVar();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 77U, chartInstance->c42_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 77U,
                 chartInstance->c42_sfEvent);
    switch (chartInstance->c42_c_is_Active) {
     case c42_IN_High_Flow:
      CV_STATE_EVAL(77, 0, c42_IN_High_Flow);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_HIGH;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 133U,
                   chartInstance->c42_sfEvent);
      c42_b_out = (CV_TRANSITION_EVAL(133U, (int32_T)(_SFD_CCP_CALL(5U, 133U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 133U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        chartInstance->c42_tp_High_Flow = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 78U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_is_Active = c42_b_IN_Standard_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 81U, chartInstance->c42_sfEvent);
        chartInstance->c42_g_tp_Standard_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0,
                           chartInstance->c42_AUX_FLOW_STANDARD);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 78U,
                     chartInstance->c42_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 78U, chartInstance->c42_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 77U, chartInstance->c42_sfEvent);
      break;

     case c42_b_IN_Low_Flow:
      CV_STATE_EVAL(77, 0, c42_b_IN_Low_Flow);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 115U,
                   chartInstance->c42_sfEvent);
      c42_temp = (_SFD_CCP_CALL(5U, 115U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U);
      if (c42_temp) {
        c42_temp = (_SFD_CCP_CALL(5U, 115U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          115U, 0, (real_T)*chartInstance->c42_state_DetentEnable, (real_T)
          chartInstance->c42_ACTIVE, 0, 0U,
          *chartInstance->c42_state_DetentEnable == chartInstance->c42_ACTIVE)
          != 0U, chartInstance->c42_sfEvent) != 0U);
      }

      c42_e_out = (CV_TRANSITION_EVAL(115U, (int32_T)c42_temp) != 0);
      if (c42_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 115U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        chartInstance->c42_c_tp_Low_Flow = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 79U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_is_Active = c42_IN_High_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 78U, chartInstance->c42_sfEvent);
        chartInstance->c42_tp_High_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_HIGH;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_HIGH);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 107U,
                     chartInstance->c42_sfEvent);
        c42_b_temp = (_SFD_CCP_CALL(5U, 107U, 0,
          (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (c42_b_temp) {
          c42_b_temp = (_SFD_CCP_CALL(5U, 107U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 107U, 0, (real_T)*chartInstance->c42_state_DetentEnable,
             (real_T)chartInstance->c42_ACTIVE, 0, 1U,
             *chartInstance->c42_state_DetentEnable != chartInstance->c42_ACTIVE)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_f_out = (CV_TRANSITION_EVAL(107U, (int32_T)c42_b_temp) != 0);
        if (c42_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 107U, chartInstance->c42_sfEvent);
          c42_set_state_Buzzer(chartInstance, 0,
                               chartInstance->c42_SINGLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
          chartInstance->c42_c_tp_Low_Flow = 0U;
          chartInstance->c42_c_is_Active = c42_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 79U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Active = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 77U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_is_Enabled = c42_IN_Off;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 82U, chartInstance->c42_sfEvent);
          chartInstance->c42_c_tp_Off = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 79U,
                       chartInstance->c42_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 79U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_c_is_Enabled != c42_IN_Active) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 77U, chartInstance->c42_sfEvent);
      }
      break;

     case c42_b_IN_Medium_Flow:
      CV_STATE_EVAL(77, 0, c42_b_IN_Medium_Flow);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 114U,
                   chartInstance->c42_sfEvent);
      c42_c_out = (CV_TRANSITION_EVAL(114U, (int32_T)(_SFD_CCP_CALL(5U, 114U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 114U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        chartInstance->c42_c_tp_Medium_Flow = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 80U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_is_Active = c42_b_IN_Low_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 79U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_tp_Low_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_LOW);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 80U,
                     chartInstance->c42_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 80U, chartInstance->c42_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 77U, chartInstance->c42_sfEvent);
      break;

     case c42_b_IN_Standard_Flow:
      CV_STATE_EVAL(77, 0, c42_b_IN_Standard_Flow);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 116U,
                   chartInstance->c42_sfEvent);
      c42_d_out = (CV_TRANSITION_EVAL(116U, (int32_T)(_SFD_CCP_CALL(5U, 116U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 116U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        chartInstance->c42_g_tp_Standard_Flow = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 81U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_is_Active = c42_b_IN_Medium_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 80U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_tp_Medium_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_MEDIUM);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        matlab_UpdateEEVar();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 81U,
                     chartInstance->c42_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 81U, chartInstance->c42_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 77U, chartInstance->c42_sfEvent);
      break;

     default:
      CV_STATE_EVAL(77, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c42_c_is_Active = c42_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 78U, chartInstance->c42_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 77U, chartInstance->c42_sfEvent);
      break;
    }
  }
}

static void c42_c_exit_internal_Active(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_c_is_Active) {
   case c42_IN_High_Flow:
    CV_STATE_EVAL(77, 1, c42_IN_High_Flow);
    chartInstance->c42_tp_High_Flow = 0U;
    chartInstance->c42_c_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 78U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Low_Flow:
    CV_STATE_EVAL(77, 1, c42_b_IN_Low_Flow);
    chartInstance->c42_c_tp_Low_Flow = 0U;
    chartInstance->c42_c_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 79U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Medium_Flow:
    CV_STATE_EVAL(77, 1, c42_b_IN_Medium_Flow);
    chartInstance->c42_c_tp_Medium_Flow = 0U;
    chartInstance->c42_c_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 80U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Standard_Flow:
    CV_STATE_EVAL(77, 1, c42_b_IN_Standard_Flow);
    chartInstance->c42_g_tp_Standard_Flow = 0U;
    chartInstance->c42_c_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 81U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(77, 1, 0);
    chartInstance->c42_c_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 78U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_b_Inactive_Fault(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
  *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 91U, chartInstance->c42_sfEvent);
  c42_temp = (_SFD_CCP_CALL(5U, 91U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 91U, 0,
    (real_T)*chartInstance->c42_state_AuxPot, (real_T)chartInstance->c42_OORH, 0,
    1U, *chartInstance->c42_state_AuxPot != chartInstance->c42_OORH) != 0U,
    chartInstance->c42_sfEvent) != 0U);
  if (c42_temp) {
    c42_temp = (_SFD_CCP_CALL(5U, 91U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 91U,
      1, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
      chartInstance->c42_OORL, 0, 1U, *chartInstance->c42_state_AuxPot !=
      chartInstance->c42_OORL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_b_temp = c42_temp;
  if (c42_temp) {
    c42_b_temp = (_SFD_CCP_CALL(5U, 91U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      91U, 2, (real_T)*chartInstance->c42_state_System, (real_T)
      chartInstance->c42_SYS_NORMAL, 0, 0U, *chartInstance->c42_state_System ==
      chartInstance->c42_SYS_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_out = (CV_TRANSITION_EVAL(91U, (int32_T)c42_b_temp) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 91U, chartInstance->c42_sfEvent);
    chartInstance->c42_c_tp_Inactive_Fault = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 84U, chartInstance->c42_sfEvent);
    chartInstance->c42_c_is_Functional = c42_b_IN_Enabled;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
    chartInstance->c42_e_tp_Enabled = 1U;
    if (chartInstance->c42_c_is_Enabled == c42_IN_Off) {
    } else {
      chartInstance->c42_c_is_Enabled = c42_IN_Off;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 82U, chartInstance->c42_sfEvent);
      chartInstance->c42_c_tp_Off = 1U;
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      matlab_UpdateEEVar();
    }
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 84U,
                 chartInstance->c42_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 84U, chartInstance->c42_sfEvent);
}

static void c42_c_Inactive_Out_Of_Neutral(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_temp;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_b_temp;
  boolean_T c42_c_temp;
  boolean_T c42_d_out;
  *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
  *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 103U,
               chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(103U, (int32_T)(_SFD_CCP_CALL(5U, 103U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 103U, 0, (real_T)
    *chartInstance->c42_state_Console, (real_T)chartInstance->c42_ACTIVE, 0, 1U,
    *chartInstance->c42_state_Console != chartInstance->c42_ACTIVE) != 0U,
    chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 103U, chartInstance->c42_sfEvent);
    chartInstance->c42_c_tp_Inactive_Out_Of_Neutral = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 85U, chartInstance->c42_sfEvent);
    chartInstance->c42_c_is_Functional = c42_b_IN_Inactive;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 83U, chartInstance->c42_sfEvent);
    chartInstance->c42_c_tp_Inactive = 1U;
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 95U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 95U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 95U,
      0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
      chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
      chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 95U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        95U, 1, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
        chartInstance->c42_OORL, 0, 0U, *chartInstance->c42_state_AuxPot ==
        chartInstance->c42_OORL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(95U, (int32_T)c42_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 95U, chartInstance->c42_sfEvent);
      chartInstance->c42_c_tp_Inactive_Out_Of_Neutral = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 85U, chartInstance->c42_sfEvent);
      chartInstance->c42_c_is_Functional = c42_b_IN_Inactive_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 84U, chartInstance->c42_sfEvent);
      chartInstance->c42_c_tp_Inactive_Fault = 1U;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 99U,
                   chartInstance->c42_sfEvent);
      c42_c_out = (CV_TRANSITION_EVAL(99U, (int32_T)(_SFD_CCP_CALL(5U, 99U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 99U, 0, (real_T)
        *chartInstance->c42_state_AuxPot, (real_T)
        chartInstance->c42_NOT_IN_NEUTRAL, 0, 1U,
        *chartInstance->c42_state_AuxPot != chartInstance->c42_NOT_IN_NEUTRAL)
        != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 99U, chartInstance->c42_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 98U,
                     chartInstance->c42_sfEvent);
        c42_b_temp = (_SFD_CCP_CALL(5U, 98U, 0,
          (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (!c42_b_temp) {
          c42_b_temp = (_SFD_CCP_CALL(5U, 98U, 1,
            (*chartInstance->c42_aux_DetentHold != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_c_temp = c42_b_temp;
        if (c42_b_temp) {
          c42_c_temp = (_SFD_CCP_CALL(5U, 98U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 98U, 0, (real_T)*chartInstance->c42_aux_Flow, (real_T)
             chartInstance->c42_AUX_FLOW_INACTIVE, 0, 1U,
             *chartInstance->c42_aux_Flow !=
             chartInstance->c42_AUX_FLOW_INACTIVE) != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_d_out = (CV_TRANSITION_EVAL(98U, (int32_T)c42_c_temp) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 98U, chartInstance->c42_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 100U, chartInstance->c42_sfEvent);
          c42_set_state_Buzzer(chartInstance, 0,
                               chartInstance->c42_SINGLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 101U, chartInstance->c42_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 102U, chartInstance->c42_sfEvent);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 97U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_tp_Inactive_Out_Of_Neutral = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 85U, chartInstance->c42_sfEvent);
        chartInstance->c42_c_is_Functional = c42_b_IN_Enabled;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 76U, chartInstance->c42_sfEvent);
        chartInstance->c42_e_tp_Enabled = 1U;
        c42_c_enter_internal_Enabled(chartInstance);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 85U,
                     chartInstance->c42_sfEvent);
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 85U, chartInstance->c42_sfEvent);
}

static void c42_c_exit_internal_Aux_Enable_State_ST
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c42_c_is_Aux_Enable_State_ST) {
   case c42_IN_Inactive_Latched:
    CV_STATE_EVAL(71, 1, c42_IN_Inactive_Latched);
    chartInstance->c42_e_tp_Inactive_Latched = 0U;
    chartInstance->c42_c_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 72U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive_Temp:
    CV_STATE_EVAL(71, 1, c42_IN_Inactive_Temp);
    chartInstance->c42_e_tp_Inactive_Temp = 0U;
    chartInstance->c42_c_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 73U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(71, 1, c42_IN_Standard_Flow);
    chartInstance->c42_h_tp_Standard_Flow = 0U;
    chartInstance->c42_c_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 74U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(71, 1, 0);
    chartInstance->c42_c_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 72U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_c_exit_internal_Aux_Enable_State_ACD
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c42_c_is_Aux_Enable_State_ACD) {
   case c42_IN_Inactive_Latched:
    CV_STATE_EVAL(67, 1, c42_IN_Inactive_Latched);
    chartInstance->c42_f_tp_Inactive_Latched = 0U;
    chartInstance->c42_c_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive_Temp:
    CV_STATE_EVAL(67, 1, c42_IN_Inactive_Temp);
    chartInstance->c42_f_tp_Inactive_Temp = 0U;
    chartInstance->c42_c_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 69U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(67, 1, c42_IN_Standard_Flow);
    chartInstance->c42_i_tp_Standard_Flow = 0U;
    chartInstance->c42_c_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 70U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(67, 1, 0);
    chartInstance->c42_c_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_EMEA_CONTROLS(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_h_temp;
  boolean_T c42_i_temp;
  boolean_T c42_j_temp;
  boolean_T c42_k_temp;
  boolean_T c42_l_temp;
  boolean_T c42_g_out;
  boolean_T c42_h_out;
  boolean_T c42_i_out;
  boolean_T c42_j_out;
  boolean_T guard1 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c42_sfEvent);
  switch (chartInstance->c42_is_EMEA_CONTROLS) {
   case c42_IN_Aux_Enable_State_ACD:
    CV_STATE_EVAL(1, 0, c42_IN_Aux_Enable_State_ACD);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 182U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 182U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      182U, 0, (real_T)*chartInstance->c42_can_AuxEnable_ACD, (real_T)
      chartInstance->c42_INACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ACD ==
      chartInstance->c42_INACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 182U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        182U, 1, (real_T)*chartInstance->c42_state_ACD_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 1U, *chartInstance->c42_state_ACD_CAN !=
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_out = (CV_TRANSITION_EVAL(182U, (int32_T)c42_temp) != 0);
    if (c42_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 182U, chartInstance->c42_sfEvent);
      c42_d_exit_internal_Aux_Enable_State_ACD(chartInstance);
      chartInstance->c42_d_tp_Aux_Enable_State_ACD = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_EMEA_CONTROLS = c42_IN_Functional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c42_sfEvent);
      chartInstance->c42_d_tp_Functional = 1U;
      chartInstance->c42_previouslyActive = false;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_previouslyActive, 0U);
      c42_d_enter_internal_Functional(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_d_is_Aux_Enable_State_ACD) {
       case c42_IN_Inactive_Latched:
        CV_STATE_EVAL(2, 0, c42_IN_Inactive_Latched);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                     chartInstance->c42_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Inactive_Temp:
        CV_STATE_EVAL(2, 0, c42_IN_Inactive_Temp);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 209U,
                     chartInstance->c42_sfEvent);
        c42_c_out = (CV_TRANSITION_EVAL(209U, (int32_T)(_SFD_CCP_CALL(5U, 209U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 209U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 1U,
          *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 209U, chartInstance->c42_sfEvent);
          chartInstance->c42_h_tp_Inactive_Temp = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_is_Aux_Enable_State_ACD = c42_IN_Standard_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c42_sfEvent);
          chartInstance->c42_l_tp_Standard_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Standard_Flow:
        CV_STATE_EVAL(2, 0, c42_IN_Standard_Flow);
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 206U,
                     chartInstance->c42_sfEvent);
        c42_e_out = (CV_TRANSITION_EVAL(206U, (int32_T)(_SFD_CCP_CALL(5U, 206U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 206U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c42_state_Engine == chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 206U, chartInstance->c42_sfEvent);
          chartInstance->c42_l_tp_Standard_Flow = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_is_Aux_Enable_State_ACD = c42_IN_Inactive_Temp;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c42_sfEvent);
          chartInstance->c42_h_tp_Inactive_Temp = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 207U,
                       chartInstance->c42_sfEvent);
          c42_c_temp = (_SFD_CCP_CALL(5U, 207U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 207U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_c_temp) {
            c42_c_temp = (_SFD_CCP_CALL(5U, 207U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 207U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_e_temp = c42_c_temp;
          if (!c42_c_temp) {
            c42_e_temp = (_SFD_CCP_CALL(5U, 207U, 2, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 207U, 2, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_g_temp = c42_e_temp;
          if (!c42_e_temp) {
            c42_g_temp = (_SFD_CCP_CALL(5U, 207U, 3, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 207U, 3, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORH, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORH) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_i_temp = c42_g_temp;
          if (!c42_g_temp) {
            c42_i_temp = (_SFD_CCP_CALL(5U, 207U, 4, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 207U, 4, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_k_temp = c42_i_temp;
          if (!c42_i_temp) {
            c42_k_temp = (_SFD_CCP_CALL(5U, 207U, 5, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 207U, 5, (real_T)
                                 *chartInstance->c42_state_System, (real_T)
                                 chartInstance->c42_SYS_NORMAL, 0, 1U,
                                 *chartInstance->c42_state_System !=
                                 chartInstance->c42_SYS_NORMAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_g_out = (CV_TRANSITION_EVAL(207U, (int32_T)c42_k_temp) != 0);
          guard1 = false;
          if (c42_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 207U, chartInstance->c42_sfEvent);
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 208U,
                         chartInstance->c42_sfEvent);
            c42_i_out = (CV_TRANSITION_EVAL(208U, (int32_T)(_SFD_CCP_CALL(5U,
              208U, 0, (chartInstance->c42_sfEvent == c42_event_disable_aux) !=
              0U, chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_i_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 208U,
                           chartInstance->c42_sfEvent);
              guard1 = true;
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                           chartInstance->c42_sfEvent);
            }
          }

          if (guard1) {
            chartInstance->c42_l_tp_Standard_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_is_Aux_Enable_State_ACD =
              c42_IN_Inactive_Latched;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c42_sfEvent);
            chartInstance->c42_h_tp_Inactive_Latched = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c42_sfEvent);
        break;

       default:
        CV_STATE_EVAL(2, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_d_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c42_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Aux_Enable_State_ST:
    CV_STATE_EVAL(1, 0, c42_IN_Aux_Enable_State_ST);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 180U,
                 chartInstance->c42_sfEvent);
    c42_b_temp = (_SFD_CCP_CALL(5U, 180U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      180U, 0, (real_T)*chartInstance->c42_can_AuxEnable_ST, (real_T)
      chartInstance->c42_INACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ST ==
      chartInstance->c42_INACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_b_temp) {
      c42_b_temp = (_SFD_CCP_CALL(5U, 180U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        180U, 1, (real_T)*chartInstance->c42_state_ST_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 1U, *chartInstance->c42_state_ST_CAN !=
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(180U, (int32_T)c42_b_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 180U, chartInstance->c42_sfEvent);
      c42_d_exit_internal_Aux_Enable_State_ST(chartInstance);
      chartInstance->c42_d_tp_Aux_Enable_State_ST = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_EMEA_CONTROLS = c42_IN_Functional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c42_sfEvent);
      chartInstance->c42_d_tp_Functional = 1U;
      chartInstance->c42_previouslyActive = false;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_previouslyActive, 0U);
      c42_d_enter_internal_Functional(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_d_is_Aux_Enable_State_ST) {
       case c42_IN_Inactive_Latched:
        CV_STATE_EVAL(6, 0, c42_IN_Inactive_Latched);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                     chartInstance->c42_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Inactive_Temp:
        CV_STATE_EVAL(6, 0, c42_IN_Inactive_Temp);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 203U,
                     chartInstance->c42_sfEvent);
        c42_d_out = (CV_TRANSITION_EVAL(203U, (int32_T)(_SFD_CCP_CALL(5U, 203U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 203U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 1U,
          *chartInstance->c42_state_Engine != chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 203U, chartInstance->c42_sfEvent);
          chartInstance->c42_g_tp_Inactive_Temp = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_is_Aux_Enable_State_ST = c42_IN_Standard_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c42_sfEvent);
          chartInstance->c42_k_tp_Standard_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          c42_set_ee_AuxFlow(chartInstance, 0,
                             chartInstance->c42_AUX_FLOW_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c42_sfEvent);
        break;

       case c42_IN_Standard_Flow:
        CV_STATE_EVAL(6, 0, c42_IN_Standard_Flow);
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 201U,
                     chartInstance->c42_sfEvent);
        c42_f_out = (CV_TRANSITION_EVAL(201U, (int32_T)(_SFD_CCP_CALL(5U, 201U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 201U, 0, (real_T)
          *chartInstance->c42_state_Engine, (real_T)
          chartInstance->c42_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c42_state_Engine == chartInstance->c42_ENGINE_CRANKING)
          != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
        if (c42_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 201U, chartInstance->c42_sfEvent);
          chartInstance->c42_k_tp_Standard_Flow = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_is_Aux_Enable_State_ST = c42_IN_Inactive_Temp;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c42_sfEvent);
          chartInstance->c42_g_tp_Inactive_Temp = 1U;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 202U,
                       chartInstance->c42_sfEvent);
          c42_d_temp = (_SFD_CCP_CALL(5U, 202U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 202U, 0, (real_T)*chartInstance->c42_state_AuxPot, (real_T)
             chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_AuxPot ==
             chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
          if (!c42_d_temp) {
            c42_d_temp = (_SFD_CCP_CALL(5U, 202U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 202U, 1, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_f_temp = c42_d_temp;
          if (!c42_d_temp) {
            c42_f_temp = (_SFD_CCP_CALL(5U, 202U, 2, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 202U, 2, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORL, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_h_temp = c42_f_temp;
          if (!c42_f_temp) {
            c42_h_temp = (_SFD_CCP_CALL(5U, 202U, 3, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 202U, 3, (real_T)
                                 *chartInstance->c42_state_Console, (real_T)
                                 chartInstance->c42_OORH, 0, 0U,
                                 *chartInstance->c42_state_Console ==
                                 chartInstance->c42_OORH) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_j_temp = c42_h_temp;
          if (!c42_h_temp) {
            c42_j_temp = (_SFD_CCP_CALL(5U, 202U, 4, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 202U, 4, (real_T)
                                 *chartInstance->c42_state_AuxPot, (real_T)
                                 chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
                                 *chartInstance->c42_state_AuxPot ==
                                 chartInstance->c42_NOT_IN_NEUTRAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_l_temp = c42_j_temp;
          if (!c42_j_temp) {
            c42_l_temp = (_SFD_CCP_CALL(5U, 202U, 5, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 202U, 5, (real_T)
                                 *chartInstance->c42_state_System, (real_T)
                                 chartInstance->c42_SYS_NORMAL, 0, 1U,
                                 *chartInstance->c42_state_System !=
                                 chartInstance->c42_SYS_NORMAL) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_h_out = (CV_TRANSITION_EVAL(202U, (int32_T)c42_l_temp) != 0);
          guard1 = false;
          if (c42_h_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 202U, chartInstance->c42_sfEvent);
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 204U,
                         chartInstance->c42_sfEvent);
            c42_j_out = (CV_TRANSITION_EVAL(204U, (int32_T)(_SFD_CCP_CALL(5U,
              204U, 0, (chartInstance->c42_sfEvent == c42_event_disable_aux) !=
              0U, chartInstance->c42_sfEvent) != 0U)) != 0);
            if (c42_j_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 204U,
                           chartInstance->c42_sfEvent);
              guard1 = true;
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                           chartInstance->c42_sfEvent);
            }
          }

          if (guard1) {
            chartInstance->c42_k_tp_Standard_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_is_Aux_Enable_State_ST =
              c42_IN_Inactive_Latched;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c42_sfEvent);
            chartInstance->c42_g_tp_Inactive_Latched = 1U;
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c42_sfEvent);
        break;

       default:
        CV_STATE_EVAL(6, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_d_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c42_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Functional:
    CV_STATE_EVAL(1, 0, c42_IN_Functional);
    c42_d_Functional(chartInstance);
    break;

   default:
    CV_STATE_EVAL(1, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c42_is_EMEA_CONTROLS = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c42_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c42_sfEvent);
}

static void c42_d_enter_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 183U, chartInstance->c42_sfEvent);
  if (chartInstance->c42_d_is_Functional == c42_b_IN_Inactive) {
  } else {
    chartInstance->c42_d_is_Functional = c42_b_IN_Inactive;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c42_sfEvent);
    chartInstance->c42_d_tp_Inactive = 1U;
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    *chartInstance->c42_state_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxRelease, 30U);
  }
}

static void c42_d_Functional(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_b_out;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_g_temp;
  boolean_T c42_h_temp;
  boolean_T c42_c_out;
  boolean_T c42_i_temp;
  boolean_T c42_d_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 179U,
               chartInstance->c42_sfEvent);
  c42_temp = (_SFD_CCP_CALL(5U, 179U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 179U,
    0, (real_T)*chartInstance->c42_can_AuxEnable_ST, (real_T)
    chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ST ==
    chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
  if (c42_temp) {
    c42_temp = (_SFD_CCP_CALL(5U, 179U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      179U, 1, (real_T)*chartInstance->c42_state_ST_CAN, (real_T)
      chartInstance->c42_NORMAL, 0, 0U, *chartInstance->c42_state_ST_CAN ==
      chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_b_temp = c42_temp;
  if (c42_temp) {
    c42_b_temp = (_SFD_CCP_CALL(5U, 179U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      179U, 2, (real_T)chartInstance->c42_CD_STAUX_FUNCTION, (real_T)
      chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c42_CD_STAUX_FUNCTION != chartInstance->c42_NON_FUNCTIONAL)
      != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_out = (CV_TRANSITION_EVAL(179U, (int32_T)c42_b_temp) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 179U, chartInstance->c42_sfEvent);
    c42_d_exit_internal_Functional(chartInstance);
    chartInstance->c42_d_tp_Functional = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c42_sfEvent);
    chartInstance->c42_is_EMEA_CONTROLS = c42_IN_Aux_Enable_State_ST;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c42_sfEvent);
    chartInstance->c42_d_tp_Aux_Enable_State_ST = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 200U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_d_is_Aux_Enable_State_ST == c42_IN_Standard_Flow) {
    } else {
      chartInstance->c42_d_is_Aux_Enable_State_ST = c42_IN_Standard_Flow;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c42_sfEvent);
      chartInstance->c42_k_tp_Standard_Flow = 1U;
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      matlab_UpdateEEVar();
    }
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 181U,
                 chartInstance->c42_sfEvent);
    c42_c_temp = (_SFD_CCP_CALL(5U, 181U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      181U, 0, (real_T)*chartInstance->c42_can_AuxEnable_ACD, (real_T)
      chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_can_AuxEnable_ACD ==
      chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (c42_c_temp) {
      c42_c_temp = (_SFD_CCP_CALL(5U, 181U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        181U, 1, (real_T)*chartInstance->c42_state_ACD_CAN, (real_T)
        chartInstance->c42_NORMAL, 0, 0U, *chartInstance->c42_state_ACD_CAN ==
        chartInstance->c42_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_d_temp = c42_c_temp;
    if (c42_c_temp) {
      c42_d_temp = (_SFD_CCP_CALL(5U, 181U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        181U, 2, (real_T)chartInstance->c42_CD_RACD_FUNCTION, (real_T)
        chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c42_CD_RACD_FUNCTION != chartInstance->c42_NON_FUNCTIONAL)
        != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(181U, (int32_T)c42_d_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 181U, chartInstance->c42_sfEvent);
      c42_d_exit_internal_Functional(chartInstance);
      chartInstance->c42_d_tp_Functional = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c42_sfEvent);
      chartInstance->c42_is_EMEA_CONTROLS = c42_IN_Aux_Enable_State_ACD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c42_sfEvent);
      chartInstance->c42_d_tp_Aux_Enable_State_ACD = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 205U, chartInstance->c42_sfEvent);
      if (chartInstance->c42_d_is_Aux_Enable_State_ACD == c42_IN_Standard_Flow)
      {
      } else {
        chartInstance->c42_d_is_Aux_Enable_State_ACD = c42_IN_Standard_Flow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c42_sfEvent);
        chartInstance->c42_l_tp_Standard_Flow = 1U;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_ACTIVE_MODE_ONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                   chartInstance->c42_sfEvent);
      switch (chartInstance->c42_d_is_Functional) {
       case c42_b_IN_Enabled:
        CV_STATE_EVAL(10, 0, c42_b_IN_Enabled);
        c42_Enabled(chartInstance);
        break;

       case c42_b_IN_Inactive:
        CV_STATE_EVAL(10, 0, c42_b_IN_Inactive);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
        *chartInstance->c42_state_AuxRelease = chartInstance->c42_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 185U,
                     chartInstance->c42_sfEvent);
        c42_f_temp = (_SFD_CCP_CALL(5U, 185U, 0, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 185U, 0, (real_T)*chartInstance->c42_state_Engine, (real_T)
           chartInstance->c42_ENGINE_CRANKING, 0, 1U,
           *chartInstance->c42_state_Engine !=
           chartInstance->c42_ENGINE_CRANKING) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
        if (c42_f_temp) {
          c42_f_temp = (_SFD_CCP_CALL(5U, 185U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 185U, 1, (real_T)*chartInstance->c42_state_System, (real_T)
             chartInstance->c42_SYS_NORMAL, 0, 0U,
             *chartInstance->c42_state_System == chartInstance->c42_SYS_NORMAL)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_h_temp = c42_f_temp;
        if (c42_f_temp) {
          c42_h_temp = (_SFD_CCP_CALL(5U, 185U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 185U, 2, (real_T)*chartInstance->c42_state_Console, (real_T)
             chartInstance->c42_ACTIVE, 0, 0U, *chartInstance->c42_state_Console
             == chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_i_temp = c42_h_temp;
        if (c42_h_temp) {
          c42_i_temp = (_SFD_CCP_CALL(5U, 185U, 3,
            *chartInstance->c42_flag_InitEERead != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_d_out = (CV_TRANSITION_EVAL(185U, (int32_T)c42_i_temp) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 185U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_tp_Inactive = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_is_Functional = c42_b_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
          chartInstance->c42_f_tp_Enabled = 1U;
          c42_d_enter_internal_Enabled(chartInstance);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 18U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 18U, chartInstance->c42_sfEvent);
        break;

       case c42_b_IN_Inactive_Fault:
        CV_STATE_EVAL(10, 0, c42_b_IN_Inactive_Fault);
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 184U,
                     chartInstance->c42_sfEvent);
        c42_e_temp = (_SFD_CCP_CALL(5U, 184U, 0, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 184U, 0, (real_T)*chartInstance->c42_state_RightPot, (real_T)
           chartInstance->c42_OORH, 0, 1U, *chartInstance->c42_state_RightPot !=
           chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
        if (c42_e_temp) {
          c42_e_temp = (_SFD_CCP_CALL(5U, 184U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 184U, 1, (real_T)*chartInstance->c42_state_RightPot, (real_T)
             chartInstance->c42_OORL, 0, 1U, *chartInstance->c42_state_RightPot
             != chartInstance->c42_OORL) != 0U, chartInstance->c42_sfEvent) !=
                        0U);
        }

        c42_g_temp = c42_e_temp;
        if (c42_e_temp) {
          c42_g_temp = (_SFD_CCP_CALL(5U, 184U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 184U, 2, (real_T)*chartInstance->c42_state_System, (real_T)
             chartInstance->c42_SYS_NORMAL, 0, 0U,
             *chartInstance->c42_state_System == chartInstance->c42_SYS_NORMAL)
            != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_c_out = (CV_TRANSITION_EVAL(184U, (int32_T)c42_g_temp) != 0);
        if (c42_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 184U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_tp_Inactive_Fault = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_is_Functional = c42_b_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
          chartInstance->c42_f_tp_Enabled = 1U;
          if (chartInstance->c42_d_is_Enabled == c42_IN_Off) {
          } else {
            chartInstance->c42_d_is_Enabled = c42_IN_Off;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_tp_Off = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            c42_set_ee_AuxFlow(chartInstance, 0,
                               chartInstance->c42_AUX_FLOW_INACTIVE);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 19U,
                       chartInstance->c42_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 19U, chartInstance->c42_sfEvent);
        break;

       case c42_b_IN_Inactive_Out_Of_Neutral:
        CV_STATE_EVAL(10, 0, c42_b_IN_Inactive_Out_Of_Neutral);
        c42_d_Inactive_Out_Of_Neutral(chartInstance);
        break;

       default:
        CV_STATE_EVAL(10, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c42_d_is_Functional = c42_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c42_sfEvent);
}

static void c42_d_exit_internal_Functional(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_d_is_Functional) {
   case c42_b_IN_Enabled:
    CV_STATE_EVAL(10, 1, c42_b_IN_Enabled);
    c42_d_exit_internal_Enabled(chartInstance);
    chartInstance->c42_f_tp_Enabled = 0U;
    chartInstance->c42_d_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Inactive:
    CV_STATE_EVAL(10, 1, c42_b_IN_Inactive);
    chartInstance->c42_d_tp_Inactive = 0U;
    chartInstance->c42_d_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Inactive_Fault:
    CV_STATE_EVAL(10, 1, c42_b_IN_Inactive_Fault);
    chartInstance->c42_d_tp_Inactive_Fault = 0U;
    chartInstance->c42_d_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c42_sfEvent);
    break;

   case c42_b_IN_Inactive_Out_Of_Neutral:
    CV_STATE_EVAL(10, 1, c42_b_IN_Inactive_Out_Of_Neutral);
    chartInstance->c42_d_tp_Inactive_Out_Of_Neutral = 0U;
    chartInstance->c42_d_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(10, 1, 0);
    chartInstance->c42_d_is_Functional = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_d_enter_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_b_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_temp;
  boolean_T c42_c_out;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_d_out;
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 219U, chartInstance->c42_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 216U,
               chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(216U, (int32_T)(_SFD_CCP_CALL(5U, 216U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 216U, 0, (real_T)c42_get_ee_AuxFlow
    (chartInstance, 0), (real_T)chartInstance->c42_AUX_FLOW_INACTIVE, 0, 0U,
    c42_get_ee_AuxFlow(chartInstance, 0) == chartInstance->c42_AUX_FLOW_INACTIVE)
    != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 216U, chartInstance->c42_sfEvent);
    if (chartInstance->c42_d_is_Enabled == c42_IN_Off) {
    } else {
      chartInstance->c42_d_is_Enabled = c42_IN_Off;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c42_sfEvent);
      chartInstance->c42_d_tp_Off = 1U;
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      matlab_UpdateEEVar();
    }
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 221U, chartInstance->c42_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 214U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 214U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      214U, 0, (real_T)chartInstance->c42_CD_EMEA_CONTROLS_OPTION_B, (real_T)
      chartInstance->c42_NON_FUNCTIONAL, 0, 0U,
      chartInstance->c42_CD_EMEA_CONTROLS_OPTION_B ==
      chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent) !=
                0U);
    if (c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 214U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        214U, 1, (real_T)chartInstance->c42_CD_EMEA_CONTROLS_OPTION_C, (real_T)
        chartInstance->c42_NON_FUNCTIONAL, 0, 0U,
        chartInstance->c42_CD_EMEA_CONTROLS_OPTION_C ==
        chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent) !=
                  0U);
    }

    c42_b_temp = c42_temp;
    if (!c42_temp) {
      c42_b_temp = (_SFD_CCP_CALL(5U, 214U, 2,
        chartInstance->c42_previouslyActive != 0U, chartInstance->c42_sfEvent)
                    != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(214U, (int32_T)c42_b_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 214U, chartInstance->c42_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 244U, chartInstance->c42_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 220U,
                   chartInstance->c42_sfEvent);
      c42_c_temp = (_SFD_CCP_CALL(5U, 220U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        220U, 0, (real_T)c42_get_ee_AuxFlow(chartInstance, 0), (real_T)
        chartInstance->c42_AUX_FLOW_LOW, 0, 0U, c42_get_ee_AuxFlow(chartInstance,
        0) == chartInstance->c42_AUX_FLOW_LOW) != 0U, chartInstance->c42_sfEvent)
                    != 0U);
      if (c42_c_temp) {
        c42_c_temp = !(_SFD_CCP_CALL(5U, 220U, 1, (c42_get_ee_DeluxeG5
          (chartInstance, 0) != 0) != 0U, chartInstance->c42_sfEvent) != 0U);
      }

      c42_d_temp = c42_c_temp;
      if (c42_c_temp) {
        c42_d_temp = (_SFD_CCP_CALL(5U, 220U, 2, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 220U, 1, (real_T)chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION,
           (real_T)chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
           chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION !=
           chartInstance->c42_NON_FUNCTIONAL) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
      }

      c42_c_out = (CV_TRANSITION_EVAL(220U, (int32_T)c42_d_temp) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 220U, chartInstance->c42_sfEvent);
        if (chartInstance->c42_d_is_Enabled == c42_IN_Active) {
        } else {
          chartInstance->c42_d_is_Enabled = c42_IN_Active;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_tp_Active = 1U;
          chartInstance->c42_previouslyActive = true;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_previouslyActive, 0U);
        }

        if (chartInstance->c42_d_is_Active == c42_IN_Low_Flow) {
        } else {
          chartInstance->c42_d_is_Active = c42_IN_Low_Flow;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_tp_Low_Flow = 1U;
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
          c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_LOW);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        }
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 218U, chartInstance->c42_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 213U,
                     chartInstance->c42_sfEvent);
        c42_e_temp = (_SFD_CCP_CALL(5U, 213U, 0, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 213U, 0, (real_T)c42_get_ee_AuxFlow(chartInstance, 0), (real_T)
           chartInstance->c42_AUX_FLOW_MEDIUM, 0, 0U, c42_get_ee_AuxFlow
           (chartInstance, 0) == chartInstance->c42_AUX_FLOW_MEDIUM) != 0U,
          chartInstance->c42_sfEvent) != 0U);
        if (c42_e_temp) {
          c42_e_temp = !(_SFD_CCP_CALL(5U, 213U, 1, (c42_get_ee_DeluxeG5
            (chartInstance, 0) != 0) != 0U, chartInstance->c42_sfEvent) != 0U);
        }

        c42_f_temp = c42_e_temp;
        if (c42_e_temp) {
          c42_f_temp = (_SFD_CCP_CALL(5U, 213U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 213U, 1, (real_T)chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION,
             (real_T)chartInstance->c42_NON_FUNCTIONAL, 0, 1U,
             chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION !=
             chartInstance->c42_NON_FUNCTIONAL) != 0U,
            chartInstance->c42_sfEvent) != 0U);
        }

        c42_d_out = (CV_TRANSITION_EVAL(213U, (int32_T)c42_f_temp) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 213U, chartInstance->c42_sfEvent);
          if (chartInstance->c42_d_is_Enabled == c42_IN_Active) {
          } else {
            chartInstance->c42_d_is_Enabled = c42_IN_Active;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_tp_Active = 1U;
            chartInstance->c42_previouslyActive = true;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_previouslyActive,
                                  0U);
          }

          if (chartInstance->c42_d_is_Active == c42_IN_Medium_Flow) {
          } else {
            chartInstance->c42_d_is_Active = c42_IN_Medium_Flow;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_tp_Medium_Flow = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            *chartInstance->c42_state_AuxEnable =
              chartInstance->c42_ACTIVE_MODE_ONE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            c42_set_ee_AuxFlow(chartInstance, 0,
                               chartInstance->c42_AUX_FLOW_MEDIUM);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          }
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 215U, chartInstance->c42_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 217U, chartInstance->c42_sfEvent);
          if (chartInstance->c42_d_is_Enabled == c42_IN_Active) {
          } else {
            chartInstance->c42_d_is_Enabled = c42_IN_Active;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_tp_Active = 1U;
            chartInstance->c42_previouslyActive = true;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_previouslyActive,
                                  0U);
          }

          if (chartInstance->c42_d_is_Active == c42_IN_Standard_Flow) {
          } else {
            chartInstance->c42_d_is_Active = c42_IN_Standard_Flow;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c42_sfEvent);
            chartInstance->c42_j_tp_Standard_Flow = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            *chartInstance->c42_state_AuxEnable =
              chartInstance->c42_ACTIVE_MODE_ONE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            c42_set_ee_AuxFlow(chartInstance, 0,
                               chartInstance->c42_AUX_FLOW_STANDARD);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          }
        }
      }
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 222U, chartInstance->c42_sfEvent);
      chartInstance->c42_d_is_Enabled = c42_IN_WAIT_FOR_AUX_PRESS;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c42_sfEvent);
      chartInstance->c42_tp_WAIT_FOR_AUX_PRESS = 1U;
    }
  }
}

static void c42_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_temp;
  boolean_T c42_b_temp;
  boolean_T c42_out;
  boolean_T c42_c_temp;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_d_temp;
  boolean_T c42_e_temp;
  boolean_T c42_f_temp;
  boolean_T c42_d_out;
  boolean_T c42_g_temp;
  boolean_T c42_e_out;
  boolean_T c42_h_temp;
  boolean_T c42_i_temp;
  boolean_T c42_f_out;
  boolean_T c42_j_temp;
  boolean_T c42_k_temp;
  boolean_T c42_g_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 187U,
               chartInstance->c42_sfEvent);
  c42_temp = (_SFD_CCP_CALL(5U, 187U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 187U,
    0, (real_T)*chartInstance->c42_state_Engine, (real_T)
    chartInstance->c42_ENGINE_CRANKING, 0, 0U, *chartInstance->c42_state_Engine ==
    chartInstance->c42_ENGINE_CRANKING) != 0U, chartInstance->c42_sfEvent) != 0U);
  if (!c42_temp) {
    c42_temp = (_SFD_CCP_CALL(5U, 187U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      187U, 1, (real_T)*chartInstance->c42_state_System, (real_T)
      chartInstance->c42_SYS_NORMAL, 0, 1U, *chartInstance->c42_state_System !=
      chartInstance->c42_SYS_NORMAL) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_b_temp = c42_temp;
  if (!c42_temp) {
    c42_b_temp = (_SFD_CCP_CALL(5U, 187U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      187U, 2, (real_T)*chartInstance->c42_state_Console, (real_T)
      chartInstance->c42_ACTIVE, 0, 1U, *chartInstance->c42_state_Console !=
      chartInstance->c42_ACTIVE) != 0U, chartInstance->c42_sfEvent) != 0U);
  }

  c42_out = (CV_TRANSITION_EVAL(187U, (int32_T)c42_b_temp) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 187U, chartInstance->c42_sfEvent);
    c42_d_exit_internal_Enabled(chartInstance);
    chartInstance->c42_f_tp_Enabled = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
    chartInstance->c42_d_is_Functional = c42_b_IN_Inactive;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c42_sfEvent);
    chartInstance->c42_d_tp_Inactive = 1U;
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    *chartInstance->c42_state_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxRelease, 30U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 186U,
                 chartInstance->c42_sfEvent);
    c42_c_temp = (_SFD_CCP_CALL(5U, 186U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      186U, 0, (real_T)*chartInstance->c42_state_RightPot, (real_T)
      chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_RightPot ==
      chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_c_temp) {
      c42_c_temp = (_SFD_CCP_CALL(5U, 186U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        186U, 1, (real_T)*chartInstance->c42_state_RightPot, (real_T)
        chartInstance->c42_OORL, 0, 0U, *chartInstance->c42_state_RightPot ==
        chartInstance->c42_OORL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(186U, (int32_T)c42_c_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 186U, chartInstance->c42_sfEvent);
      c42_d_exit_internal_Enabled(chartInstance);
      chartInstance->c42_f_tp_Enabled = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
      chartInstance->c42_d_is_Functional = c42_b_IN_Inactive_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c42_sfEvent);
      chartInstance->c42_d_tp_Inactive_Fault = 1U;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 189U,
                   chartInstance->c42_sfEvent);
      c42_c_out = (CV_TRANSITION_EVAL(189U, (int32_T)(_SFD_CCP_CALL(5U, 189U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 189U, 0, (real_T)
        *chartInstance->c42_state_RightPot, (real_T)
        chartInstance->c42_NOT_IN_NEUTRAL, 0, 0U,
        *chartInstance->c42_state_RightPot == chartInstance->c42_NOT_IN_NEUTRAL)
        != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 189U, chartInstance->c42_sfEvent);
        c42_d_exit_internal_Enabled(chartInstance);
        chartInstance->c42_f_tp_Enabled = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
        chartInstance->c42_d_is_Functional = c42_b_IN_Inactive_Out_Of_Neutral;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c42_sfEvent);
        chartInstance->c42_d_tp_Inactive_Out_Of_Neutral = 1U;
        *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
        *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                     chartInstance->c42_sfEvent);
        switch (chartInstance->c42_d_is_Enabled) {
         case c42_IN_Active:
          CV_STATE_EVAL(11, 0, c42_IN_Active);
          c42_d_Active(chartInstance);
          break;

         case c42_IN_Off:
          CV_STATE_EVAL(11, 0, c42_IN_Off);
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
          *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 195U,
                       chartInstance->c42_sfEvent);
          c42_e_temp = !(_SFD_CCP_CALL(5U, 195U, 0,
            *chartInstance->c42_aux_Inhibit != 0U, chartInstance->c42_sfEvent)
                         != 0U);
          if (c42_e_temp) {
            c42_g_temp = (_SFD_CCP_CALL(5U, 195U, 1,
              (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
              chartInstance->c42_sfEvent) != 0U);
            if (!c42_g_temp) {
              c42_g_temp = (_SFD_CCP_CALL(5U, 195U, 2,
                (*chartInstance->c42_aux_DetentHold != 0) != 0U,
                chartInstance->c42_sfEvent) != 0U);
            }

            c42_e_temp = c42_g_temp;
          }

          c42_e_out = (CV_TRANSITION_EVAL(195U, (int32_T)c42_e_temp) != 0);
          if (c42_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 195U, chartInstance->c42_sfEvent);
            c42_set_state_Buzzer(chartInstance, 0,
                                 chartInstance->c42_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
            chartInstance->c42_d_tp_Off = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_is_Enabled = c42_IN_Active;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_tp_Active = 1U;
            chartInstance->c42_previouslyActive = true;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_previouslyActive,
                                  0U);
            if (chartInstance->c42_d_is_Active == c42_IN_Standard_Flow) {
            } else {
              chartInstance->c42_d_is_Active = c42_IN_Standard_Flow;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c42_sfEvent);
              chartInstance->c42_j_tp_Standard_Flow = 1U;
              *chartInstance->c42_aux_Flow =
                chartInstance->c42_AUX_FLOW_STANDARD;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
              *chartInstance->c42_state_AuxEnable =
                chartInstance->c42_ACTIVE_MODE_ONE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                    25U);
              c42_set_ee_AuxFlow(chartInstance, 0,
                                 chartInstance->c42_AUX_FLOW_STANDARD);
              ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
              matlab_UpdateEEVar();
            }
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 16U,
                         chartInstance->c42_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c42_sfEvent);
          break;

         case c42_IN_WAIT_FOR_AUX_PRESS:
          CV_STATE_EVAL(11, 0, c42_IN_WAIT_FOR_AUX_PRESS);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 223U,
                       chartInstance->c42_sfEvent);
          c42_d_temp = !(_SFD_CCP_CALL(5U, 223U, 0,
            *chartInstance->c42_aux_Inhibit != 0U, chartInstance->c42_sfEvent)
                         != 0U);
          if (c42_d_temp) {
            c42_f_temp = (_SFD_CCP_CALL(5U, 223U, 1,
              (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
              chartInstance->c42_sfEvent) != 0U);
            if (!c42_f_temp) {
              c42_f_temp = (_SFD_CCP_CALL(5U, 223U, 2,
                (*chartInstance->c42_aux_DetentHold != 0) != 0U,
                chartInstance->c42_sfEvent) != 0U);
            }

            c42_d_temp = c42_f_temp;
          }

          c42_d_out = (CV_TRANSITION_EVAL(223U, (int32_T)c42_d_temp) != 0);
          if (c42_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 223U, chartInstance->c42_sfEvent);
            c42_set_state_Buzzer(chartInstance, 0,
                                 chartInstance->c42_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 244U, chartInstance->c42_sfEvent);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 220U,
                         chartInstance->c42_sfEvent);
            c42_h_temp = (_SFD_CCP_CALL(5U, 220U, 0, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 220U, 2, (real_T)c42_get_ee_AuxFlow
                                 (chartInstance, 0), (real_T)
                                 chartInstance->c42_AUX_FLOW_LOW, 0, 0U,
                                 c42_get_ee_AuxFlow(chartInstance, 0) ==
                                 chartInstance->c42_AUX_FLOW_LOW) != 0U,
              chartInstance->c42_sfEvent) != 0U);
            if (c42_h_temp) {
              c42_h_temp = !(_SFD_CCP_CALL(5U, 220U, 1, (c42_get_ee_DeluxeG5
                (chartInstance, 0) != 0) != 0U, chartInstance->c42_sfEvent) !=
                             0U);
            }

            c42_i_temp = c42_h_temp;
            if (c42_h_temp) {
              c42_i_temp = (_SFD_CCP_CALL(5U, 220U, 2, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 220U, 3, (real_T)
                                   chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION,
                                   (real_T)chartInstance->c42_NON_FUNCTIONAL, 0,
                                   1U,
                                   chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION
                                   != chartInstance->c42_NON_FUNCTIONAL) != 0U,
                chartInstance->c42_sfEvent) != 0U);
            }

            c42_f_out = (CV_TRANSITION_EVAL(220U, (int32_T)c42_i_temp) != 0);
            if (c42_f_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 220U,
                           chartInstance->c42_sfEvent);
              chartInstance->c42_tp_WAIT_FOR_AUX_PRESS = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c42_sfEvent);
              chartInstance->c42_d_is_Enabled = c42_IN_Active;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
              chartInstance->c42_d_tp_Active = 1U;
              chartInstance->c42_previouslyActive = true;
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_previouslyActive,
                                    0U);
              if (chartInstance->c42_d_is_Active == c42_IN_Low_Flow) {
              } else {
                chartInstance->c42_d_is_Active = c42_IN_Low_Flow;
                _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
                chartInstance->c42_d_tp_Low_Flow = 1U;
                *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
                _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
                *chartInstance->c42_state_AuxEnable =
                  chartInstance->c42_ACTIVE_MODE_ONE;
                _SFD_DATA_RANGE_CHECK((real_T)
                                      *chartInstance->c42_state_AuxEnable, 25U);
                c42_set_ee_AuxFlow(chartInstance, 0,
                                   chartInstance->c42_AUX_FLOW_LOW);
                ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
                matlab_UpdateEEVar();
              }
            } else {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 218U,
                           chartInstance->c42_sfEvent);
              _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 213U,
                           chartInstance->c42_sfEvent);
              c42_j_temp = (_SFD_CCP_CALL(5U, 213U, 0, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 213U, 2, (real_T)c42_get_ee_AuxFlow
                                   (chartInstance, 0), (real_T)
                                   chartInstance->c42_AUX_FLOW_MEDIUM, 0, 0U,
                                   c42_get_ee_AuxFlow(chartInstance, 0) ==
                                   chartInstance->c42_AUX_FLOW_MEDIUM) != 0U,
                chartInstance->c42_sfEvent) != 0U);
              if (c42_j_temp) {
                c42_j_temp = !(_SFD_CCP_CALL(5U, 213U, 1, (c42_get_ee_DeluxeG5
                  (chartInstance, 0) != 0) != 0U, chartInstance->c42_sfEvent) !=
                               0U);
              }

              c42_k_temp = c42_j_temp;
              if (c42_j_temp) {
                c42_k_temp = (_SFD_CCP_CALL(5U, 213U, 2, (boolean_T)
                  CV_RELATIONAL_EVAL(5U, 213U, 3, (real_T)
                                     chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION,
                                     (real_T)chartInstance->c42_NON_FUNCTIONAL,
                                     0, 1U,
                                     chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION
                                     != chartInstance->c42_NON_FUNCTIONAL) != 0U,
                  chartInstance->c42_sfEvent) != 0U);
              }

              c42_g_out = (CV_TRANSITION_EVAL(213U, (int32_T)c42_k_temp) != 0);
              if (c42_g_out) {
                _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 213U,
                             chartInstance->c42_sfEvent);
                chartInstance->c42_tp_WAIT_FOR_AUX_PRESS = 0U;
                _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c42_sfEvent);
                chartInstance->c42_d_is_Enabled = c42_IN_Active;
                _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
                chartInstance->c42_d_tp_Active = 1U;
                chartInstance->c42_previouslyActive = true;
                _SFD_DATA_RANGE_CHECK((real_T)
                                      chartInstance->c42_previouslyActive, 0U);
                if (chartInstance->c42_d_is_Active == c42_IN_Medium_Flow) {
                } else {
                  chartInstance->c42_d_is_Active = c42_IN_Medium_Flow;
                  _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c42_sfEvent);
                  chartInstance->c42_d_tp_Medium_Flow = 1U;
                  *chartInstance->c42_aux_Flow =
                    chartInstance->c42_AUX_FLOW_MEDIUM;
                  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow,
                                        27U);
                  *chartInstance->c42_state_AuxEnable =
                    chartInstance->c42_ACTIVE_MODE_ONE;
                  _SFD_DATA_RANGE_CHECK((real_T)
                                        *chartInstance->c42_state_AuxEnable, 25U);
                  c42_set_ee_AuxFlow(chartInstance, 0,
                                     chartInstance->c42_AUX_FLOW_MEDIUM);
                  ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
                  matlab_UpdateEEVar();
                }
              } else {
                _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 215U,
                             chartInstance->c42_sfEvent);
                _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 217U,
                             chartInstance->c42_sfEvent);
                chartInstance->c42_tp_WAIT_FOR_AUX_PRESS = 0U;
                _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c42_sfEvent);
                chartInstance->c42_d_is_Enabled = c42_IN_Active;
                _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
                chartInstance->c42_d_tp_Active = 1U;
                chartInstance->c42_previouslyActive = true;
                _SFD_DATA_RANGE_CHECK((real_T)
                                      chartInstance->c42_previouslyActive, 0U);
                if (chartInstance->c42_d_is_Active == c42_IN_Standard_Flow) {
                } else {
                  chartInstance->c42_d_is_Active = c42_IN_Standard_Flow;
                  _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c42_sfEvent);
                  chartInstance->c42_j_tp_Standard_Flow = 1U;
                  *chartInstance->c42_aux_Flow =
                    chartInstance->c42_AUX_FLOW_STANDARD;
                  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow,
                                        27U);
                  *chartInstance->c42_state_AuxEnable =
                    chartInstance->c42_ACTIVE_MODE_ONE;
                  _SFD_DATA_RANGE_CHECK((real_T)
                                        *chartInstance->c42_state_AuxEnable, 25U);
                  c42_set_ee_AuxFlow(chartInstance, 0,
                                     chartInstance->c42_AUX_FLOW_STANDARD);
                  ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
                  matlab_UpdateEEVar();
                }
              }
            }
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 17U,
                         chartInstance->c42_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c42_sfEvent);
          break;

         default:
          CV_STATE_EVAL(11, 0, 0);

          /* Unreachable state, for coverage only */
          chartInstance->c42_d_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
          break;
        }
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c42_sfEvent);
}

static void c42_d_exit_internal_Enabled(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_d_is_Enabled) {
   case c42_IN_Active:
    CV_STATE_EVAL(11, 1, c42_IN_Active);
    c42_d_exit_internal_Active(chartInstance);
    chartInstance->c42_d_tp_Active = 0U;
    chartInstance->c42_d_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Off:
    CV_STATE_EVAL(11, 1, c42_IN_Off);
    chartInstance->c42_d_tp_Off = 0U;
    chartInstance->c42_d_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_WAIT_FOR_AUX_PRESS:
    CV_STATE_EVAL(11, 1, c42_IN_WAIT_FOR_AUX_PRESS);
    chartInstance->c42_tp_WAIT_FOR_AUX_PRESS = 0U;
    chartInstance->c42_d_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(11, 1, 0);
    chartInstance->c42_d_is_Enabled = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_d_Active(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_temp;
  boolean_T c42_b_out;
  boolean_T c42_b_temp;
  boolean_T c42_c_out;
  boolean_T c42_c_temp;
  boolean_T c42_d_out;
  boolean_T c42_e_out;
  boolean_T c42_f_out;
  boolean_T c42_d_temp;
  boolean_T c42_g_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 196U,
               chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(196U, (int32_T)(_SFD_CCP_CALL(5U, 196U, 0,
    (chartInstance->c42_sfEvent == c42_event_disable_aux) != 0U,
    chartInstance->c42_sfEvent) != 0U)) != 0);
  guard1 = false;
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 196U, chartInstance->c42_sfEvent);
    guard1 = true;
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 210U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 210U, 0,
      *chartInstance->c42_change_OffsetSelectSw != 0U,
      chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 210U, 1, *chartInstance->c42_aux_Inhibit !=
        0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(210U, (int32_T)c42_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 210U, chartInstance->c42_sfEvent);
      guard1 = true;
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 211U,
                   chartInstance->c42_sfEvent);
      c42_b_temp = (_SFD_CCP_CALL(5U, 211U, 0,
        (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
        chartInstance->c42_sfEvent) != 0U);
      if (c42_b_temp) {
        c42_b_temp = (_SFD_CCP_CALL(5U, 211U, 1, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 211U, 0, (real_T)*chartInstance->c42_mode_RightControl, (real_T)
           chartInstance->c42_MODE_RIGHT_AUX1, 0, 1U,
           *chartInstance->c42_mode_RightControl !=
           chartInstance->c42_MODE_RIGHT_AUX1) != 0U, chartInstance->c42_sfEvent)
                      != 0U);
      }

      c42_c_out = (CV_TRANSITION_EVAL(211U, (int32_T)c42_b_temp) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 211U, chartInstance->c42_sfEvent);
        c42_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c42_SINGLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        guard1 = true;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                     chartInstance->c42_sfEvent);
        switch (chartInstance->c42_d_is_Active) {
         case c42_IN_Low_Flow:
          CV_STATE_EVAL(12, 0, c42_IN_Low_Flow);
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 198U,
                       chartInstance->c42_sfEvent);
          c42_c_temp = (_SFD_CCP_CALL(5U, 198U, 0,
            (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U);
          if (c42_c_temp) {
            c42_c_temp = (_SFD_CCP_CALL(5U, 198U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 198U, 0, (real_T)
                                 *chartInstance->c42_state_DetentEnable, (real_T)
                                 chartInstance->c42_ACTIVE, 0, 0U,
                                 *chartInstance->c42_state_DetentEnable ==
                                 chartInstance->c42_ACTIVE) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_f_out = (CV_TRANSITION_EVAL(198U, (int32_T)c42_c_temp) != 0);
          if (c42_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 198U, chartInstance->c42_sfEvent);
            c42_set_state_Buzzer(chartInstance, 0,
                                 chartInstance->c42_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
            chartInstance->c42_d_tp_Low_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_is_Active = c42_IN_Standard_Flow;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c42_sfEvent);
            chartInstance->c42_j_tp_Standard_Flow = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            *chartInstance->c42_state_AuxEnable =
              chartInstance->c42_ACTIVE_MODE_ONE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            c42_set_ee_AuxFlow(chartInstance, 0,
                               chartInstance->c42_AUX_FLOW_STANDARD);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 194U,
                         chartInstance->c42_sfEvent);
            c42_d_temp = (_SFD_CCP_CALL(5U, 194U, 0,
              (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
              chartInstance->c42_sfEvent) != 0U);
            if (c42_d_temp) {
              c42_d_temp = (_SFD_CCP_CALL(5U, 194U, 1, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 194U, 0, (real_T)
                                   *chartInstance->c42_state_DetentEnable,
                                   (real_T)chartInstance->c42_ACTIVE, 0, 1U,
                                   *chartInstance->c42_state_DetentEnable !=
                                   chartInstance->c42_ACTIVE) != 0U,
                chartInstance->c42_sfEvent) != 0U);
            }

            c42_g_out = (CV_TRANSITION_EVAL(194U, (int32_T)c42_d_temp) != 0);
            if (c42_g_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 194U,
                           chartInstance->c42_sfEvent);
              c42_set_state_Buzzer(chartInstance, 0,
                                   chartInstance->c42_SINGLE_SHORT_BEEP);
              ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
              chartInstance->c42_d_tp_Low_Flow = 0U;
              chartInstance->c42_d_is_Active = c42_IN_NO_ACTIVE_CHILD;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
              chartInstance->c42_d_tp_Active = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
              chartInstance->c42_d_is_Enabled = c42_IN_Off;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c42_sfEvent);
              chartInstance->c42_d_tp_Off = 1U;
              *chartInstance->c42_aux_Flow =
                chartInstance->c42_AUX_FLOW_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
              *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                    25U);
              c42_set_ee_AuxFlow(chartInstance, 0,
                                 chartInstance->c42_AUX_FLOW_INACTIVE);
              ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
              matlab_UpdateEEVar();
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U,
                           chartInstance->c42_sfEvent);
            }
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c42_sfEvent);
          if (chartInstance->c42_d_is_Enabled != c42_IN_Active) {
          } else {
            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U,
                         chartInstance->c42_sfEvent);
          }
          break;

         case c42_IN_Medium_Flow:
          CV_STATE_EVAL(12, 0, c42_IN_Medium_Flow);
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 197U,
                       chartInstance->c42_sfEvent);
          c42_d_out = (CV_TRANSITION_EVAL(197U, (int32_T)(_SFD_CCP_CALL(5U, 197U,
            0, (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U)) != 0);
          if (c42_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 197U, chartInstance->c42_sfEvent);
            c42_set_state_Buzzer(chartInstance, 0,
                                 chartInstance->c42_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
            chartInstance->c42_d_tp_Medium_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_is_Active = c42_IN_Low_Flow;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_tp_Low_Flow = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_LOW;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            *chartInstance->c42_state_AuxEnable =
              chartInstance->c42_ACTIVE_MODE_ONE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_LOW);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 14U,
                         chartInstance->c42_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c42_sfEvent);
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c42_sfEvent);
          break;

         case c42_IN_Standard_Flow:
          CV_STATE_EVAL(12, 0, c42_IN_Standard_Flow);
          *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
          *chartInstance->c42_state_AuxEnable =
            chartInstance->c42_ACTIVE_MODE_ONE;
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 199U,
                       chartInstance->c42_sfEvent);
          c42_e_out = (CV_TRANSITION_EVAL(199U, (int32_T)(_SFD_CCP_CALL(5U, 199U,
            0, (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U)) != 0);
          if (c42_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 199U, chartInstance->c42_sfEvent);
            c42_set_state_Buzzer(chartInstance, 0,
                                 chartInstance->c42_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
            chartInstance->c42_j_tp_Standard_Flow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_is_Active = c42_IN_Medium_Flow;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_tp_Medium_Flow = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_MEDIUM;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            *chartInstance->c42_state_AuxEnable =
              chartInstance->c42_ACTIVE_MODE_ONE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            c42_set_ee_AuxFlow(chartInstance, 0,
                               chartInstance->c42_AUX_FLOW_MEDIUM);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 15U,
                         chartInstance->c42_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c42_sfEvent);
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c42_sfEvent);
          break;

         default:
          CV_STATE_EVAL(12, 0, 0);

          /* Unreachable state, for coverage only */
          chartInstance->c42_d_is_Active = c42_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c42_sfEvent);
          break;
        }
      }
    }
  }

  if (guard1) {
    c42_d_exit_internal_Active(chartInstance);
    chartInstance->c42_d_tp_Active = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
    chartInstance->c42_d_is_Enabled = c42_IN_Off;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c42_sfEvent);
    chartInstance->c42_d_tp_Off = 1U;
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    c42_set_ee_AuxFlow(chartInstance, 0, chartInstance->c42_AUX_FLOW_INACTIVE);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c42_sfEvent);
  }
}

static void c42_d_exit_internal_Active(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c42_d_is_Active) {
   case c42_IN_Low_Flow:
    CV_STATE_EVAL(12, 1, c42_IN_Low_Flow);
    chartInstance->c42_d_tp_Low_Flow = 0U;
    chartInstance->c42_d_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Medium_Flow:
    CV_STATE_EVAL(12, 1, c42_IN_Medium_Flow);
    chartInstance->c42_d_tp_Medium_Flow = 0U;
    chartInstance->c42_d_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(12, 1, c42_IN_Standard_Flow);
    chartInstance->c42_j_tp_Standard_Flow = 0U;
    chartInstance->c42_d_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(12, 1, 0);
    chartInstance->c42_d_is_Active = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_d_Inactive_Out_Of_Neutral(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c42_out;
  boolean_T c42_temp;
  boolean_T c42_b_out;
  boolean_T c42_c_out;
  boolean_T c42_b_temp;
  boolean_T c42_c_temp;
  boolean_T c42_d_out;
  *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
  *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 193U,
               chartInstance->c42_sfEvent);
  c42_out = (CV_TRANSITION_EVAL(193U, (int32_T)(_SFD_CCP_CALL(5U, 193U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 193U, 0, (real_T)
    *chartInstance->c42_state_Console, (real_T)chartInstance->c42_ACTIVE, 0, 1U,
    *chartInstance->c42_state_Console != chartInstance->c42_ACTIVE) != 0U,
    chartInstance->c42_sfEvent) != 0U)) != 0);
  if (c42_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 193U, chartInstance->c42_sfEvent);
    chartInstance->c42_d_tp_Inactive_Out_Of_Neutral = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c42_sfEvent);
    chartInstance->c42_d_is_Functional = c42_b_IN_Inactive;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c42_sfEvent);
    chartInstance->c42_d_tp_Inactive = 1U;
    *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
    *chartInstance->c42_cmd_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_cmd_AuxRelease, 29U);
    *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    *chartInstance->c42_state_AuxRelease = chartInstance->c42_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxRelease, 30U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 188U,
                 chartInstance->c42_sfEvent);
    c42_temp = (_SFD_CCP_CALL(5U, 188U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      188U, 0, (real_T)*chartInstance->c42_state_RightPot, (real_T)
      chartInstance->c42_OORH, 0, 0U, *chartInstance->c42_state_RightPot ==
      chartInstance->c42_OORH) != 0U, chartInstance->c42_sfEvent) != 0U);
    if (!c42_temp) {
      c42_temp = (_SFD_CCP_CALL(5U, 188U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        188U, 1, (real_T)*chartInstance->c42_state_RightPot, (real_T)
        chartInstance->c42_OORL, 0, 0U, *chartInstance->c42_state_RightPot ==
        chartInstance->c42_OORL) != 0U, chartInstance->c42_sfEvent) != 0U);
    }

    c42_b_out = (CV_TRANSITION_EVAL(188U, (int32_T)c42_temp) != 0);
    if (c42_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 188U, chartInstance->c42_sfEvent);
      chartInstance->c42_d_tp_Inactive_Out_Of_Neutral = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c42_sfEvent);
      chartInstance->c42_d_is_Functional = c42_b_IN_Inactive_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c42_sfEvent);
      chartInstance->c42_d_tp_Inactive_Fault = 1U;
      *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable, 25U);
      *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 191U,
                   chartInstance->c42_sfEvent);
      c42_c_out = (CV_TRANSITION_EVAL(191U, (int32_T)(_SFD_CCP_CALL(5U, 191U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 191U, 0, (real_T)
        *chartInstance->c42_state_RightPot, (real_T)
        chartInstance->c42_NOT_IN_NEUTRAL, 0, 1U,
        *chartInstance->c42_state_RightPot != chartInstance->c42_NOT_IN_NEUTRAL)
        != 0U, chartInstance->c42_sfEvent) != 0U)) != 0);
      if (c42_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 191U, chartInstance->c42_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 190U,
                     chartInstance->c42_sfEvent);
        c42_b_temp = !(_SFD_CCP_CALL(5U, 190U, 0,
          *chartInstance->c42_aux_Inhibit != 0U, chartInstance->c42_sfEvent) !=
                       0U);
        if (c42_b_temp) {
          c42_c_temp = (_SFD_CCP_CALL(5U, 190U, 1,
            (*chartInstance->c42_aux_DebounceButton != 0) != 0U,
            chartInstance->c42_sfEvent) != 0U);
          if (!c42_c_temp) {
            c42_c_temp = (_SFD_CCP_CALL(5U, 190U, 2,
              (*chartInstance->c42_aux_DetentHold != 0) != 0U,
              chartInstance->c42_sfEvent) != 0U);
          }

          c42_b_temp = c42_c_temp;
        }

        c42_d_out = (CV_TRANSITION_EVAL(190U, (int32_T)c42_b_temp) != 0);
        if (c42_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 190U, chartInstance->c42_sfEvent);
          c42_set_state_Buzzer(chartInstance, 0,
                               chartInstance->c42_SINGLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
          chartInstance->c42_d_tp_Inactive_Out_Of_Neutral = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_is_Functional = c42_b_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
          chartInstance->c42_f_tp_Enabled = 1U;
          if (chartInstance->c42_d_is_Enabled == c42_IN_Active) {
          } else {
            chartInstance->c42_d_is_Enabled = c42_IN_Active;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_tp_Active = 1U;
            chartInstance->c42_previouslyActive = true;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c42_previouslyActive,
                                  0U);
          }

          if (chartInstance->c42_d_is_Active == c42_IN_Standard_Flow) {
          } else {
            chartInstance->c42_d_is_Active = c42_IN_Standard_Flow;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c42_sfEvent);
            chartInstance->c42_j_tp_Standard_Flow = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_STANDARD;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            *chartInstance->c42_state_AuxEnable =
              chartInstance->c42_ACTIVE_MODE_ONE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            c42_set_ee_AuxFlow(chartInstance, 0,
                               chartInstance->c42_AUX_FLOW_STANDARD);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          }
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 192U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_tp_Inactive_Out_Of_Neutral = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c42_sfEvent);
          chartInstance->c42_d_is_Functional = c42_b_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c42_sfEvent);
          chartInstance->c42_f_tp_Enabled = 1U;
          if (chartInstance->c42_d_is_Enabled == c42_IN_Off) {
          } else {
            chartInstance->c42_d_is_Enabled = c42_IN_Off;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c42_sfEvent);
            chartInstance->c42_d_tp_Off = 1U;
            *chartInstance->c42_aux_Flow = chartInstance->c42_AUX_FLOW_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_aux_Flow, 27U);
            *chartInstance->c42_state_AuxEnable = chartInstance->c42_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c42_state_AuxEnable,
                                  25U);
            c42_set_ee_AuxFlow(chartInstance, 0,
                               chartInstance->c42_AUX_FLOW_INACTIVE);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          }
        }
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 20U,
                     chartInstance->c42_sfEvent);
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 20U, chartInstance->c42_sfEvent);
}

static void c42_d_exit_internal_Aux_Enable_State_ST
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c42_d_is_Aux_Enable_State_ST) {
   case c42_IN_Inactive_Latched:
    CV_STATE_EVAL(6, 1, c42_IN_Inactive_Latched);
    chartInstance->c42_g_tp_Inactive_Latched = 0U;
    chartInstance->c42_d_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive_Temp:
    CV_STATE_EVAL(6, 1, c42_IN_Inactive_Temp);
    chartInstance->c42_g_tp_Inactive_Temp = 0U;
    chartInstance->c42_d_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(6, 1, c42_IN_Standard_Flow);
    chartInstance->c42_k_tp_Standard_Flow = 0U;
    chartInstance->c42_d_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(6, 1, 0);
    chartInstance->c42_d_is_Aux_Enable_State_ST = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c42_sfEvent);
    break;
  }
}

static void c42_d_exit_internal_Aux_Enable_State_ACD
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c42_d_is_Aux_Enable_State_ACD) {
   case c42_IN_Inactive_Latched:
    CV_STATE_EVAL(2, 1, c42_IN_Inactive_Latched);
    chartInstance->c42_h_tp_Inactive_Latched = 0U;
    chartInstance->c42_d_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Inactive_Temp:
    CV_STATE_EVAL(2, 1, c42_IN_Inactive_Temp);
    chartInstance->c42_h_tp_Inactive_Temp = 0U;
    chartInstance->c42_d_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c42_sfEvent);
    break;

   case c42_IN_Standard_Flow:
    CV_STATE_EVAL(2, 1, c42_IN_Standard_Flow);
    chartInstance->c42_l_tp_Standard_Flow = 0U;
    chartInstance->c42_d_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c42_sfEvent);
    break;

   default:
    CV_STATE_EVAL(2, 1, 0);
    chartInstance->c42_d_is_Aux_Enable_State_ACD = c42_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c42_sfEvent);
    break;
  }
}

static void init_script_number_translation(uint32_T c42_machineNumber, uint32_T
  c42_chartNumber, uint32_T c42_instanceNumber)
{
  (void)(c42_machineNumber);
  (void)(c42_chartNumber);
  (void)(c42_instanceNumber);
}

const mxArray *sf_c42_MX_Gtwy_Control_get_eml_resolved_functions_info(void)
{
  const mxArray *c42_nameCaptureInfo = NULL;
  c42_nameCaptureInfo = NULL;
  sf_mex_assign(&c42_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c42_nameCaptureInfo;
}

static const mxArray *c42_sf_marshallOut(void *chartInstanceVoid, void
  *c42_inData)
{
  const mxArray *c42_mxArrayOutData;
  int32_T c42_u;
  const mxArray *c42_y = NULL;
  SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc42_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c42_mxArrayOutData = NULL;
  c42_mxArrayOutData = NULL;
  c42_u = *(int32_T *)c42_inData;
  c42_y = NULL;
  sf_mex_assign(&c42_y, sf_mex_create("y", &c42_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c42_mxArrayOutData, c42_y, false);
  return c42_mxArrayOutData;
}

static int32_T c42_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId)
{
  int32_T c42_y;
  int32_T c42_i0;
  (void)chartInstance;
  sf_mex_import(c42_parentId, sf_mex_dup(c42_u), &c42_i0, 1, 6, 0U, 0, 0U, 0);
  c42_y = c42_i0;
  sf_mex_destroy(&c42_u);
  return c42_y;
}

static void c42_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c42_mxArrayInData, const char_T *c42_varName, void *c42_outData)
{
  const mxArray *c42_b_sfEvent;
  emlrtMsgIdentifier c42_thisId;
  int32_T c42_y;
  SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc42_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c42_b_sfEvent = sf_mex_dup(c42_mxArrayInData);
  c42_thisId.fIdentifier = (const char *)c42_varName;
  c42_thisId.fParent = NULL;
  c42_thisId.bParentIsCell = false;
  c42_y = c42_emlrt_marshallIn(chartInstance, sf_mex_dup(c42_b_sfEvent),
    &c42_thisId);
  sf_mex_destroy(&c42_b_sfEvent);
  *(int32_T *)c42_outData = c42_y;
  sf_mex_destroy(&c42_mxArrayInData);
}

static const mxArray *c42_b_sf_marshallOut(void *chartInstanceVoid, void
  *c42_inData)
{
  const mxArray *c42_mxArrayOutData;
  uint8_T c42_u;
  const mxArray *c42_y = NULL;
  SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc42_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c42_mxArrayOutData = NULL;
  c42_mxArrayOutData = NULL;
  c42_u = *(uint8_T *)c42_inData;
  c42_y = NULL;
  sf_mex_assign(&c42_y, sf_mex_create("y", &c42_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c42_mxArrayOutData, c42_y, false);
  return c42_mxArrayOutData;
}

static uint8_T c42_b_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_b_tp_Detent_State, const char_T
  *c42_identifier)
{
  uint8_T c42_y;
  emlrtMsgIdentifier c42_thisId;
  c42_thisId.fIdentifier = (const char *)c42_identifier;
  c42_thisId.fParent = NULL;
  c42_thisId.bParentIsCell = false;
  c42_y = c42_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c42_b_tp_Detent_State),
    &c42_thisId);
  sf_mex_destroy(&c42_b_tp_Detent_State);
  return c42_y;
}

static uint8_T c42_c_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId)
{
  uint8_T c42_y;
  uint8_T c42_u5;
  (void)chartInstance;
  sf_mex_import(c42_parentId, sf_mex_dup(c42_u), &c42_u5, 1, 3, 0U, 0, 0U, 0);
  c42_y = c42_u5;
  sf_mex_destroy(&c42_u);
  return c42_y;
}

static void c42_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c42_mxArrayInData, const char_T *c42_varName, void *c42_outData)
{
  const mxArray *c42_b_tp_Detent_State;
  emlrtMsgIdentifier c42_thisId;
  uint8_T c42_y;
  SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc42_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c42_b_tp_Detent_State = sf_mex_dup(c42_mxArrayInData);
  c42_thisId.fIdentifier = (const char *)c42_varName;
  c42_thisId.fParent = NULL;
  c42_thisId.bParentIsCell = false;
  c42_y = c42_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c42_b_tp_Detent_State),
    &c42_thisId);
  sf_mex_destroy(&c42_b_tp_Detent_State);
  *(uint8_T *)c42_outData = c42_y;
  sf_mex_destroy(&c42_mxArrayInData);
}

static const mxArray *c42_c_sf_marshallOut(void *chartInstanceVoid, void
  *c42_inData)
{
  const mxArray *c42_mxArrayOutData;
  boolean_T c42_u;
  const mxArray *c42_y = NULL;
  SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc42_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c42_mxArrayOutData = NULL;
  c42_mxArrayOutData = NULL;
  c42_u = *(boolean_T *)c42_inData;
  c42_y = NULL;
  sf_mex_assign(&c42_y, sf_mex_create("y", &c42_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c42_mxArrayOutData, c42_y, false);
  return c42_mxArrayOutData;
}

static const mxArray *c42_d_sf_marshallOut(void *chartInstanceVoid, void
  *c42_inData)
{
  const mxArray *c42_mxArrayOutData;
  uint16_T c42_u;
  const mxArray *c42_y = NULL;
  SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc42_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c42_mxArrayOutData = NULL;
  c42_mxArrayOutData = NULL;
  c42_u = *(uint16_T *)c42_inData;
  c42_y = NULL;
  sf_mex_assign(&c42_y, sf_mex_create("y", &c42_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c42_mxArrayOutData, c42_y, false);
  return c42_mxArrayOutData;
}

static uint16_T c42_d_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_b_CD_AUX_RELEASE_TIME, const char_T
  *c42_identifier)
{
  uint16_T c42_y;
  emlrtMsgIdentifier c42_thisId;
  c42_thisId.fIdentifier = (const char *)c42_identifier;
  c42_thisId.fParent = NULL;
  c42_thisId.bParentIsCell = false;
  c42_y = c42_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c42_b_CD_AUX_RELEASE_TIME), &c42_thisId);
  sf_mex_destroy(&c42_b_CD_AUX_RELEASE_TIME);
  return c42_y;
}

static uint16_T c42_e_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId)
{
  uint16_T c42_y;
  uint16_T c42_u6;
  (void)chartInstance;
  sf_mex_import(c42_parentId, sf_mex_dup(c42_u), &c42_u6, 1, 5, 0U, 0, 0U, 0);
  c42_y = c42_u6;
  sf_mex_destroy(&c42_u);
  return c42_y;
}

static void c42_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c42_mxArrayInData, const char_T *c42_varName, void *c42_outData)
{
  const mxArray *c42_b_CD_AUX_RELEASE_TIME;
  emlrtMsgIdentifier c42_thisId;
  uint16_T c42_y;
  SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc42_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c42_b_CD_AUX_RELEASE_TIME = sf_mex_dup(c42_mxArrayInData);
  c42_thisId.fIdentifier = (const char *)c42_varName;
  c42_thisId.fParent = NULL;
  c42_thisId.bParentIsCell = false;
  c42_y = c42_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c42_b_CD_AUX_RELEASE_TIME), &c42_thisId);
  sf_mex_destroy(&c42_b_CD_AUX_RELEASE_TIME);
  *(uint16_T *)c42_outData = c42_y;
  sf_mex_destroy(&c42_mxArrayInData);
}

static boolean_T c42_f_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_b_previouslyActive, const char_T
  *c42_identifier)
{
  boolean_T c42_y;
  emlrtMsgIdentifier c42_thisId;
  c42_thisId.fIdentifier = (const char *)c42_identifier;
  c42_thisId.fParent = NULL;
  c42_thisId.bParentIsCell = false;
  c42_y = c42_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c42_b_previouslyActive), &c42_thisId);
  sf_mex_destroy(&c42_b_previouslyActive);
  return c42_y;
}

static boolean_T c42_g_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId)
{
  boolean_T c42_y;
  boolean_T c42_b0;
  (void)chartInstance;
  sf_mex_import(c42_parentId, sf_mex_dup(c42_u), &c42_b0, 1, 11, 0U, 0, 0U, 0);
  c42_y = c42_b0;
  sf_mex_destroy(&c42_u);
  return c42_y;
}

static void c42_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c42_mxArrayInData, const char_T *c42_varName, void *c42_outData)
{
  const mxArray *c42_b_previouslyActive;
  emlrtMsgIdentifier c42_thisId;
  boolean_T c42_y;
  SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc42_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c42_b_previouslyActive = sf_mex_dup(c42_mxArrayInData);
  c42_thisId.fIdentifier = (const char *)c42_varName;
  c42_thisId.fParent = NULL;
  c42_thisId.bParentIsCell = false;
  c42_y = c42_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c42_b_previouslyActive), &c42_thisId);
  sf_mex_destroy(&c42_b_previouslyActive);
  *(boolean_T *)c42_outData = c42_y;
  sf_mex_destroy(&c42_mxArrayInData);
}

static uint32_T c42_h_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_b_temporalCounter_i1, const char_T
  *c42_identifier)
{
  uint32_T c42_y;
  emlrtMsgIdentifier c42_thisId;
  c42_thisId.fIdentifier = (const char *)c42_identifier;
  c42_thisId.fParent = NULL;
  c42_thisId.bParentIsCell = false;
  c42_y = c42_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c42_b_temporalCounter_i1), &c42_thisId);
  sf_mex_destroy(&c42_b_temporalCounter_i1);
  return c42_y;
}

static uint32_T c42_i_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId)
{
  uint32_T c42_y;
  uint32_T c42_u7;
  (void)chartInstance;
  sf_mex_import(c42_parentId, sf_mex_dup(c42_u), &c42_u7, 1, 7, 0U, 0, 0U, 0);
  c42_y = c42_u7;
  sf_mex_destroy(&c42_u);
  return c42_y;
}

static const mxArray *c42_j_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_b_setSimStateSideEffectsInfo, const char_T *
  c42_identifier)
{
  const mxArray *c42_y = NULL;
  emlrtMsgIdentifier c42_thisId;
  c42_y = NULL;
  c42_thisId.fIdentifier = (const char *)c42_identifier;
  c42_thisId.fParent = NULL;
  c42_thisId.bParentIsCell = false;
  sf_mex_assign(&c42_y, c42_k_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c42_b_setSimStateSideEffectsInfo), &c42_thisId), false);
  sf_mex_destroy(&c42_b_setSimStateSideEffectsInfo);
  return c42_y;
}

static const mxArray *c42_k_emlrt_marshallIn(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c42_u, const emlrtMsgIdentifier *c42_parentId)
{
  const mxArray *c42_y = NULL;
  (void)chartInstance;
  (void)c42_parentId;
  c42_y = NULL;
  sf_mex_assign(&c42_y, sf_mex_duplicatearraysafe(&c42_u), false);
  sf_mex_destroy(&c42_u);
  return c42_y;
}

static const mxArray *sf_get_hover_data_for_msg
  (SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c42_ssid)
{
  (void)chartInstance;
  (void)c42_ssid;
  return NULL;
}

static void c42_init_sf_message_store_memory(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static uint16_T c42__u16_s32_(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c42_b, uint32_T c42_ssid_src_loc, int32_T c42_offset_src_loc, int32_T
  c42_length_src_loc)
{
  uint16_T c42_a;
  (void)chartInstance;
  c42_a = (uint16_T)c42_b;
  if (c42_a != c42_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c42_ssid_src_loc, c42_offset_src_loc,
      c42_length_src_loc);
  }

  return c42_a;
}

static uint32_T c42__u32_s32_(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c42_b, uint32_T c42_ssid_src_loc, int32_T c42_offset_src_loc, int32_T
  c42_length_src_loc)
{
  uint32_T c42_a;
  (void)chartInstance;
  c42_a = (uint32_T)c42_b;
  if (c42_b < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c42_ssid_src_loc, c42_offset_src_loc,
      c42_length_src_loc);
  }

  return c42_a;
}

static uint16_T c42__u16_u32_(SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance,
  uint32_T c42_b, uint32_T c42_ssid_src_loc, int32_T c42_offset_src_loc, int32_T
  c42_length_src_loc)
{
  uint16_T c42_a;
  (void)chartInstance;
  c42_a = (uint16_T)c42_b;
  if (c42_a != c42_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c42_ssid_src_loc, c42_offset_src_loc,
      c42_length_src_loc);
  }

  return c42_a;
}

static uint8_T c42_get_ee_AuxFlow(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex)
{
  if (chartInstance->c42_dsmdiag_ee_AuxFlow) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, "ee_AuxFlow",
      c42_elementIndex);
  }

  return *chartInstance->c42_ee_AuxFlow_address;
}

static void c42_set_ee_AuxFlow(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex, uint8_T c42_elementValue)
{
  if (chartInstance->c42_dsmdiag_ee_AuxFlow) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, "ee_AuxFlow",
      c42_elementIndex);
  }

  *chartInstance->c42_ee_AuxFlow_address = c42_elementValue;
}

static uint8_T *c42_access_ee_AuxFlow(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_rdOnly)
{
  if (chartInstance->c42_dsmdiag_ee_AuxFlow) {
    ssAccessDataStore_wrapper(chartInstance->S, 0, "ee_AuxFlow", c42_rdOnly);
  }

  return chartInstance->c42_ee_AuxFlow_address;
}

static uint8_T c42_get_ee_DeluxeG5(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex)
{
  if (chartInstance->c42_dsmdiag_ee_DeluxeG5) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 1, "ee_DeluxeG5",
      c42_elementIndex);
  }

  return *chartInstance->c42__indexee_DeluxeG5_address;
}

static void c42_set_ee_DeluxeG5(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex, uint8_T c42_elementValue)
{
  if (chartInstance->c42_dsmdiag_ee_DeluxeG5) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 1, "ee_DeluxeG5",
      c42_elementIndex);
  }

  *chartInstance->c42__indexee_DeluxeG5_address = c42_elementValue;
}

static uint8_T *c42_access_ee_DeluxeG5(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_rdOnly)
{
  if (chartInstance->c42_dsmdiag_ee_DeluxeG5) {
    ssAccessDataStore_wrapper(chartInstance->S, 1, "ee_DeluxeG5", c42_rdOnly);
  }

  return chartInstance->c42__indexee_DeluxeG5_address;
}

static uint8_T c42_get_state_Buzzer(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex)
{
  if (chartInstance->c42_dsmdiag_state_Buzzer) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 2, "state_Buzzer",
      c42_elementIndex);
  }

  return *chartInstance->c42__indexstate_Buzzer_address;
}

static void c42_set_state_Buzzer(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_elementIndex, uint8_T c42_elementValue)
{
  if (chartInstance->c42_dsmdiag_state_Buzzer) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 2, "state_Buzzer",
      c42_elementIndex);
  }

  *chartInstance->c42__indexstate_Buzzer_address = c42_elementValue;
}

static uint8_T *c42_access_state_Buzzer(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c42_rdOnly)
{
  if (chartInstance->c42_dsmdiag_state_Buzzer) {
    ssAccessDataStore_wrapper(chartInstance->S, 2, "state_Buzzer", c42_rdOnly);
  }

  return chartInstance->c42__indexstate_Buzzer_address;
}

static void init_dsm_address_info(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_AuxFlow", (void **)
    &chartInstance->c42_ee_AuxFlow_address, &chartInstance->c42__indexFlow);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_DeluxeG5", (void **)
    &chartInstance->c42__indexee_DeluxeG5_address,
    &chartInstance->c42__indexuxeG5);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "state_Buzzer", (void **)
    &chartInstance->c42__indexstate_Buzzer_address,
    &chartInstance->c42__indexBuzzer);
}

static void init_simulink_io_address(SFc42_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  chartInstance->c42_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c42_DetentRisingEdge = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c42_state_AuxEnable = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c42_state_Detent = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c42_state_AuxPot = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c42_state_Engine = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c42_state_Console = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c42_aux_DebounceButton = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 4);
  chartInstance->c42_state_System = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c42_aux_Flow = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c42_state_DetentEnable = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 4);
  chartInstance->c42_aux_DetentHold = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c42_state_Buttons = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c42_flag_InitEERead = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c42_can_AuxEnable_ST = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c42_can_AuxEnable_ACD = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c42_state_ST_CAN = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 11);
  chartInstance->c42_state_ACD_CAN = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 12);
  chartInstance->c42_button_AuxReleaseAck = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 13);
  chartInstance->c42_button_AuxReleaseBack = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 14);
  chartInstance->c42_button_AuxReleaseExit = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 15);
  chartInstance->c42_cmd_AuxRelease = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c42_button_Aux = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 16);
  chartInstance->c42_state_AuxRelease = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c42_state_RightPot = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 17);
  chartInstance->c42_change_OffsetSelectSw = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 18);
  chartInstance->c42_mode_RightControl = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 19);
  chartInstance->c42_aux_Inhibit = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 20);
  chartInstance->c42_state_EngineSpeed = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 21);
  chartInstance->c42_dsmdiag_ee_AuxFlow = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 0, "ee_AuxFlow");
  chartInstance->c42_dsmdiag_ee_DeluxeG5 = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 1, "ee_DeluxeG5");
  chartInstance->c42_dsmdiag_state_Buzzer = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 2, "state_Buzzer");
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c42_MX_Gtwy_Control_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3685165175U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4175277342U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(25938550U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1709559369U);
}

mxArray* sf_c42_MX_Gtwy_Control_get_post_codegen_info(void);
mxArray *sf_c42_MX_Gtwy_Control_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("pxtaD2Da8adeHzNQNCft0F");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,22,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,16,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,16,"type",mxType);
    }

    mxSetField(mxData,16,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,17,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,17,"type",mxType);
    }

    mxSetField(mxData,17,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,18,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,18,"type",mxType);
    }

    mxSetField(mxData,18,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,19,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,19,"type",mxType);
    }

    mxSetField(mxData,19,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,20,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,20,"type",mxType);
    }

    mxSetField(mxData,20,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,21,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,21,"type",mxType);
    }

    mxSetField(mxData,21,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,48,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,16,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,16,"type",mxType);
    }

    mxSetField(mxData,16,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,17,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,17,"type",mxType);
    }

    mxSetField(mxData,17,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,18,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,18,"type",mxType);
    }

    mxSetField(mxData,18,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,19,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,19,"type",mxType);
    }

    mxSetField(mxData,19,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,20,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,20,"type",mxType);
    }

    mxSetField(mxData,20,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,21,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,21,"type",mxType);
    }

    mxSetField(mxData,21,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,22,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,22,"type",mxType);
    }

    mxSetField(mxData,22,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,23,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,23,"type",mxType);
    }

    mxSetField(mxData,23,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,24,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,24,"type",mxType);
    }

    mxSetField(mxData,24,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,25,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,25,"type",mxType);
    }

    mxSetField(mxData,25,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,26,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,26,"type",mxType);
    }

    mxSetField(mxData,26,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,27,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,27,"type",mxType);
    }

    mxSetField(mxData,27,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,28,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,28,"type",mxType);
    }

    mxSetField(mxData,28,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,29,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,29,"type",mxType);
    }

    mxSetField(mxData,29,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,30,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,30,"type",mxType);
    }

    mxSetField(mxData,30,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,31,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,31,"type",mxType);
    }

    mxSetField(mxData,31,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,32,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,32,"type",mxType);
    }

    mxSetField(mxData,32,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,33,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,33,"type",mxType);
    }

    mxSetField(mxData,33,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,34,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,34,"type",mxType);
    }

    mxSetField(mxData,34,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,35,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,35,"type",mxType);
    }

    mxSetField(mxData,35,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,36,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,36,"type",mxType);
    }

    mxSetField(mxData,36,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,37,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,37,"type",mxType);
    }

    mxSetField(mxData,37,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,38,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,38,"type",mxType);
    }

    mxSetField(mxData,38,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,39,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,39,"type",mxType);
    }

    mxSetField(mxData,39,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,40,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,40,"type",mxType);
    }

    mxSetField(mxData,40,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,41,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,41,"type",mxType);
    }

    mxSetField(mxData,41,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,42,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,42,"type",mxType);
    }

    mxSetField(mxData,42,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,43,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,43,"type",mxType);
    }

    mxSetField(mxData,43,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,44,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,44,"type",mxType);
    }

    mxSetField(mxData,44,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,45,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,45,"type",mxType);
    }

    mxSetField(mxData,45,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,46,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,46,"type",mxType);
    }

    mxSetField(mxData,46,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,47,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,47,"type",mxType);
    }

    mxSetField(mxData,47,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,6,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c42_MX_Gtwy_Control_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c42_MX_Gtwy_Control_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c42_MX_Gtwy_Control_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("early");
  mxArray *fallbackReason = mxCreateString("custom_code");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c42_MX_Gtwy_Control_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c42_MX_Gtwy_Control_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c42_MX_Gtwy_Control(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[166],T\"aux_Flow\",},{M[1],M[603],T\"cmd_AuxRelease\",},{M[1],M[68],T\"state_AuxEnable\",},{M[1],M[938],T\"state_AuxRelease\",},{M[1],M[73],T\"state_Detent\",},{M[1],M[280],T\"state_DetentEnable\",},{M[3],M[1285],T\"previouslyActive\",},{M[3],M[570],T\"state_ACD_old\",},{M[3],M[571],T\"state_ST_old\",},{M[8],M[0],T\"is_active_c42_MX_Gtwy_Control\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[8],M[210],T\"is_active_Aux_Enable_State\",},{M[8],M[262],T\"is_active_Detent_State\",},{M[8],M[282],T\"is_active_Enable\",},{M[8],M[545],T\"is_active_Aux_Reset\",},{M[8],M[920],T\"is_active_Detent\",},{M[8],M[1302],T\"is_active_Enable\",},{M[8],M[1310],T\"is_active_Detent\",},{M[9],M[210],T\"is_Aux_Enable_State\",},{M[9],M[262],T\"is_Detent_State\",},{M[9],M[271],T\"is_Active_Normal\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[9],M[282],T\"is_Enable\",},{M[9],M[310],T\"is_Enabled\",},{M[9],M[395],T\"is_Functional\",},{M[9],M[452],T\"is_Active\",},{M[9],M[519],T\"is_Aux_Enable_State_ST\",},{M[9],M[527],T\"is_Aux_Enable_State_ACD\",},{M[9],M[573],T\"is_Aux_Relief_G5\",},{M[9],M[658],T\"is_PHOENIX_K2\",},{M[9],M[660],T\"is_SIRIUS2_HIFLOW\",},{M[9],M[666],T\"is_Functional\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[9],M[687],T\"is_Enabled\",},{M[9],M[705],T\"is_Active\",},{M[9],M[733],T\"is_Aux_Enable_State_ST\",},{M[9],M[742],T\"is_Aux_Enable_State_ACD\",},{M[9],M[840],T\"is_SIRIUS2\",},{M[9],M[846],T\"is_Functional\",},{M[9],M[865],T\"is_Enabled\",},{M[9],M[885],T\"is_Active\",},{M[9],M[897],T\"is_Aux_Enable_State_ST\",},{M[9],M[906],T\"is_Aux_Enable_State_ACD\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[9],M[920],T\"is_Detent\",},{M[9],M[1150],T\"is_EMEA_CONTROLS\",},{M[9],M[1156],T\"is_Functional\",},{M[9],M[1179],T\"is_Enabled\",},{M[9],M[1197],T\"is_Active\",},{M[9],M[1235],T\"is_Aux_Enable_State_ST\",},{M[9],M[1244],T\"is_Aux_Enable_State_ACD\",},{M[9],M[1302],T\"is_Enable\",},{M[9],M[1310],T\"is_Detent\",},{M[9],M[1318],T\"is_Active_Normal\",}}",
    "100 S1x2'type','srcId','name','auxInfo'{{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"wu\",M1x2[288 1327],M[1]}}},{M[11],M[0],T\"temporalCounter_i2\",S'et','os','ct'{{T\"wu\",M1x3[589 580 582],M[1]}}}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 52, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c42_MX_Gtwy_Control_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc42_MX_Gtwy_ControlInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc42_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MX_Gtwy_ControlMachineNumber_,
           42,
           109,
           245,
           0,
           82,
           2,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_MX_Gtwy_ControlMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_MX_Gtwy_ControlMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _MX_Gtwy_ControlMachineNumber_,
            chartInstance->chartNumber,
            2,
            2,
            2);
          _SFD_SET_DATA_PROPS(0,0,0,0,"previouslyActive");
          _SFD_SET_DATA_PROPS(1,0,0,0,"state_ACD_old");
          _SFD_SET_DATA_PROPS(2,0,0,0,"state_ST_old");
          _SFD_SET_DATA_PROPS(3,1,1,0,"DetentRisingEdge");
          _SFD_SET_DATA_PROPS(4,1,1,0,"state_AuxPot");
          _SFD_SET_DATA_PROPS(5,1,1,0,"state_Engine");
          _SFD_SET_DATA_PROPS(6,1,1,0,"state_Console");
          _SFD_SET_DATA_PROPS(7,1,1,0,"aux_DebounceButton");
          _SFD_SET_DATA_PROPS(8,1,1,0,"state_System");
          _SFD_SET_DATA_PROPS(9,1,1,0,"aux_DetentHold");
          _SFD_SET_DATA_PROPS(10,1,1,0,"state_Buttons");
          _SFD_SET_DATA_PROPS(11,1,1,0,"flag_InitEERead");
          _SFD_SET_DATA_PROPS(12,1,1,0,"can_AuxEnable_ST");
          _SFD_SET_DATA_PROPS(13,1,1,0,"can_AuxEnable_ACD");
          _SFD_SET_DATA_PROPS(14,1,1,0,"state_ST_CAN");
          _SFD_SET_DATA_PROPS(15,1,1,0,"state_ACD_CAN");
          _SFD_SET_DATA_PROPS(16,1,1,0,"button_AuxReleaseAck");
          _SFD_SET_DATA_PROPS(17,1,1,0,"button_AuxReleaseBack");
          _SFD_SET_DATA_PROPS(18,1,1,0,"button_AuxReleaseExit");
          _SFD_SET_DATA_PROPS(19,1,1,0,"button_Aux");
          _SFD_SET_DATA_PROPS(20,1,1,0,"state_RightPot");
          _SFD_SET_DATA_PROPS(21,1,1,0,"change_OffsetSelectSw");
          _SFD_SET_DATA_PROPS(22,1,1,0,"mode_RightControl");
          _SFD_SET_DATA_PROPS(23,1,1,0,"aux_Inhibit");
          _SFD_SET_DATA_PROPS(24,1,1,0,"state_EngineSpeed");
          _SFD_SET_DATA_PROPS(25,2,0,1,"state_AuxEnable");
          _SFD_SET_DATA_PROPS(26,2,0,1,"state_Detent");
          _SFD_SET_DATA_PROPS(27,2,0,1,"aux_Flow");
          _SFD_SET_DATA_PROPS(28,2,0,1,"state_DetentEnable");
          _SFD_SET_DATA_PROPS(29,2,0,1,"cmd_AuxRelease");
          _SFD_SET_DATA_PROPS(30,2,0,1,"state_AuxRelease");
          _SFD_SET_DATA_PROPS(31,10,0,0,"ACTIVE");
          _SFD_SET_DATA_PROPS(32,10,0,0,"ACTIVE_MODE_ONE");
          _SFD_SET_DATA_PROPS(33,10,0,0,"AUX_EMEA_CONTROLS");
          _SFD_SET_DATA_PROPS(34,10,0,0,"AUX_FLOW_HIGH");
          _SFD_SET_DATA_PROPS(35,10,0,0,"AUX_FLOW_INACTIVE");
          _SFD_SET_DATA_PROPS(36,10,0,0,"AUX_FLOW_LOW");
          _SFD_SET_DATA_PROPS(37,10,0,0,"AUX_FLOW_MEDIUM");
          _SFD_SET_DATA_PROPS(38,10,0,0,"AUX_FLOW_STANDARD");
          _SFD_SET_DATA_PROPS(39,10,0,0,"AUX_PHOENIX_K2");
          _SFD_SET_DATA_PROPS(40,10,0,0,"AUX_RELEASE_ACK");
          _SFD_SET_DATA_PROPS(41,10,0,0,"AUX_RELEASE_CONFIRM");
          _SFD_SET_DATA_PROPS(42,10,0,0,"AUX_RELEASE_IN_PROGRESS");
          _SFD_SET_DATA_PROPS(43,10,0,0,"AUX_RELEASE_WAIT");
          _SFD_SET_DATA_PROPS(44,10,0,0,"AUX_SIRIUS2");
          _SFD_SET_DATA_PROPS(45,10,0,0,"BASE_ACTIVE");
          _SFD_SET_DATA_PROPS(46,10,0,0,"BASE_DETENT");
          _SFD_SET_DATA_PROPS(47,10,0,0,"CD_AUX_ADJ_FLOW_FUNCTION");
          _SFD_SET_DATA_PROPS(48,10,0,0,"CD_AUX_CONFIRM_TIME");
          _SFD_SET_DATA_PROPS(49,10,0,0,"CD_AUX_DETENT_FLASH_TIME");
          _SFD_SET_DATA_PROPS(50,10,0,0,"CD_AUX_FUNCTION");
          _SFD_SET_DATA_PROPS(51,10,0,0,"CD_AUX_HIGH_FLOW");
          _SFD_SET_DATA_PROPS(52,10,0,0,"CD_AUX_RELEASE_FUNCTION");
          _SFD_SET_DATA_PROPS(53,10,0,0,"CD_AUX_RELEASE_TIME");
          _SFD_SET_DATA_PROPS(54,10,0,0,"CD_DELUXE_GEN5_5_FUNCTION");
          _SFD_SET_DATA_PROPS(55,10,0,0,"CD_EMEA_CONTROLS_OPTION_B");
          _SFD_SET_DATA_PROPS(56,10,0,0,"CD_EMEA_CONTROLS_OPTION_C");
          _SFD_SET_DATA_PROPS(57,10,0,0,"CD_RACD_FUNCTION");
          _SFD_SET_DATA_PROPS(58,10,0,0,"CD_RIGHT_POT_FUNCTION");
          _SFD_SET_DATA_PROPS(59,10,0,0,"CD_STAUX_FUNCTION");
          _SFD_SET_DATA_PROPS(60,10,0,0,"DOUBLE_SHORT_BEEP");
          _SFD_SET_DATA_PROPS(61,10,0,0,"ENGINE_CRANKING");
          _SFD_SET_DATA_PROPS(62,10,0,0,"ENGINE_INITIALIZE");
          _SFD_SET_DATA_PROPS(63,10,0,0,"ENGINE_NOT_RUNNING");
          _SFD_SET_DATA_PROPS(64,10,0,0,"ENGINE_RUNNING");
          _SFD_SET_DATA_PROPS(65,10,0,0,"ERR_DETENT");
          _SFD_SET_DATA_PROPS(66,10,0,0,"INACTIVE");
          _SFD_SET_DATA_PROPS(67,10,0,0,"MODE_RIGHT_AUX1");
          _SFD_SET_DATA_PROPS(68,10,0,0,"NON_FUNCTIONAL");
          _SFD_SET_DATA_PROPS(69,10,0,0,"NORMAL");
          _SFD_SET_DATA_PROPS(70,10,0,0,"NOT_IN_NEUTRAL");
          _SFD_SET_DATA_PROPS(71,10,0,0,"NO_DETENT");
          _SFD_SET_DATA_PROPS(72,10,0,0,"NO_SIGNAL");
          _SFD_SET_DATA_PROPS(73,10,0,0,"OORH");
          _SFD_SET_DATA_PROPS(74,10,0,0,"OORL");
          _SFD_SET_DATA_PROPS(75,10,0,0,"ROD_ACTIVE");
          _SFD_SET_DATA_PROPS(76,10,0,0,"ROD_DETENT");
          _SFD_SET_DATA_PROPS(77,10,0,0,"SINGLE_SHORT_BEEP");
          _SFD_SET_DATA_PROPS(78,10,0,0,"SYS_NORMAL");
          _SFD_SET_DATA_PROPS(79,11,0,0,"ee_AuxFlow");
          _SFD_SET_DATA_PROPS(80,11,0,0,"ee_DeluxeG5");
          _SFD_SET_DATA_PROPS(81,11,0,0,"state_Buzzer");
          _SFD_EVENT_SCOPE(0,0);
          _SFD_EVENT_SCOPE(1,0);
          _SFD_STATE_INFO(0,0,1);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_STATE_INFO(9,0,0);
          _SFD_STATE_INFO(10,0,0);
          _SFD_STATE_INFO(11,0,0);
          _SFD_STATE_INFO(12,0,0);
          _SFD_STATE_INFO(13,0,0);
          _SFD_STATE_INFO(14,0,0);
          _SFD_STATE_INFO(15,0,0);
          _SFD_STATE_INFO(16,0,0);
          _SFD_STATE_INFO(17,0,0);
          _SFD_STATE_INFO(18,0,0);
          _SFD_STATE_INFO(19,0,0);
          _SFD_STATE_INFO(20,0,0);
          _SFD_STATE_INFO(21,0,0);
          _SFD_STATE_INFO(22,0,0);
          _SFD_STATE_INFO(23,0,0);
          _SFD_STATE_INFO(24,0,0);
          _SFD_STATE_INFO(25,0,0);
          _SFD_STATE_INFO(26,0,0);
          _SFD_STATE_INFO(27,0,0);
          _SFD_STATE_INFO(28,0,0);
          _SFD_STATE_INFO(29,0,0);
          _SFD_STATE_INFO(30,0,0);
          _SFD_STATE_INFO(31,0,0);
          _SFD_STATE_INFO(32,0,0);
          _SFD_STATE_INFO(33,0,0);
          _SFD_STATE_INFO(34,0,0);
          _SFD_STATE_INFO(35,0,0);
          _SFD_STATE_INFO(36,0,0);
          _SFD_STATE_INFO(37,0,0);
          _SFD_STATE_INFO(38,0,0);
          _SFD_STATE_INFO(39,0,0);
          _SFD_STATE_INFO(40,0,0);
          _SFD_STATE_INFO(41,0,0);
          _SFD_STATE_INFO(42,0,0);
          _SFD_STATE_INFO(43,0,0);
          _SFD_STATE_INFO(44,0,0);
          _SFD_STATE_INFO(45,0,0);
          _SFD_STATE_INFO(46,0,0);
          _SFD_STATE_INFO(47,0,0);
          _SFD_STATE_INFO(48,0,0);
          _SFD_STATE_INFO(49,0,0);
          _SFD_STATE_INFO(50,0,0);
          _SFD_STATE_INFO(51,0,0);
          _SFD_STATE_INFO(52,0,0);
          _SFD_STATE_INFO(53,0,0);
          _SFD_STATE_INFO(54,0,0);
          _SFD_STATE_INFO(55,0,0);
          _SFD_STATE_INFO(56,0,0);
          _SFD_STATE_INFO(57,0,0);
          _SFD_STATE_INFO(58,0,0);
          _SFD_STATE_INFO(59,0,0);
          _SFD_STATE_INFO(60,0,0);
          _SFD_STATE_INFO(61,0,0);
          _SFD_STATE_INFO(62,0,0);
          _SFD_STATE_INFO(63,0,0);
          _SFD_STATE_INFO(64,0,0);
          _SFD_STATE_INFO(65,0,0);
          _SFD_STATE_INFO(66,0,0);
          _SFD_STATE_INFO(67,0,0);
          _SFD_STATE_INFO(68,0,0);
          _SFD_STATE_INFO(69,0,0);
          _SFD_STATE_INFO(70,0,0);
          _SFD_STATE_INFO(71,0,0);
          _SFD_STATE_INFO(72,0,0);
          _SFD_STATE_INFO(73,0,0);
          _SFD_STATE_INFO(74,0,0);
          _SFD_STATE_INFO(75,0,0);
          _SFD_STATE_INFO(76,0,0);
          _SFD_STATE_INFO(77,0,0);
          _SFD_STATE_INFO(78,0,0);
          _SFD_STATE_INFO(79,0,0);
          _SFD_STATE_INFO(80,0,0);
          _SFD_STATE_INFO(81,0,0);
          _SFD_STATE_INFO(82,0,0);
          _SFD_STATE_INFO(83,0,0);
          _SFD_STATE_INFO(84,0,0);
          _SFD_STATE_INFO(85,0,0);
          _SFD_STATE_INFO(86,0,1);
          _SFD_STATE_INFO(87,0,1);
          _SFD_STATE_INFO(88,1,0);
          _SFD_STATE_INFO(89,0,1);
          _SFD_STATE_INFO(90,0,0);
          _SFD_STATE_INFO(91,0,0);
          _SFD_STATE_INFO(92,0,0);
          _SFD_STATE_INFO(93,0,0);
          _SFD_STATE_INFO(94,0,0);
          _SFD_STATE_INFO(95,0,1);
          _SFD_STATE_INFO(96,0,0);
          _SFD_STATE_INFO(97,0,0);
          _SFD_STATE_INFO(98,1,0);
          _SFD_STATE_INFO(99,0,1);
          _SFD_STATE_INFO(100,0,0);
          _SFD_STATE_INFO(101,0,0);
          _SFD_STATE_INFO(102,0,0);
          _SFD_STATE_INFO(103,0,0);
          _SFD_STATE_INFO(104,0,0);
          _SFD_STATE_INFO(105,0,1);
          _SFD_STATE_INFO(106,0,0);
          _SFD_STATE_INFO(107,0,0);
          _SFD_STATE_INFO(108,0,0);
          _SFD_CH_SUBSTATE_COUNT(3);
          _SFD_CH_SUBSTATE_DECOMP(1);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,87);
          _SFD_CH_SUBSTATE_INDEX(2,86);
          _SFD_ST_SUBSTATE_COUNT(0,5);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,21);
          _SFD_ST_SUBSTATE_INDEX(0,2,22);
          _SFD_ST_SUBSTATE_INDEX(0,3,47);
          _SFD_ST_SUBSTATE_INDEX(0,4,66);
          _SFD_ST_SUBSTATE_COUNT(1,3);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,6);
          _SFD_ST_SUBSTATE_INDEX(1,2,10);
          _SFD_ST_SUBSTATE_COUNT(2,3);
          _SFD_ST_SUBSTATE_INDEX(2,0,3);
          _SFD_ST_SUBSTATE_INDEX(2,1,4);
          _SFD_ST_SUBSTATE_INDEX(2,2,5);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,3);
          _SFD_ST_SUBSTATE_INDEX(6,0,7);
          _SFD_ST_SUBSTATE_INDEX(6,1,8);
          _SFD_ST_SUBSTATE_INDEX(6,2,9);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,0);
          _SFD_ST_SUBSTATE_COUNT(10,4);
          _SFD_ST_SUBSTATE_INDEX(10,0,11);
          _SFD_ST_SUBSTATE_INDEX(10,1,18);
          _SFD_ST_SUBSTATE_INDEX(10,2,19);
          _SFD_ST_SUBSTATE_INDEX(10,3,20);
          _SFD_ST_SUBSTATE_COUNT(11,3);
          _SFD_ST_SUBSTATE_INDEX(11,0,12);
          _SFD_ST_SUBSTATE_INDEX(11,1,16);
          _SFD_ST_SUBSTATE_INDEX(11,2,17);
          _SFD_ST_SUBSTATE_COUNT(12,3);
          _SFD_ST_SUBSTATE_INDEX(12,0,13);
          _SFD_ST_SUBSTATE_INDEX(12,1,14);
          _SFD_ST_SUBSTATE_INDEX(12,2,15);
          _SFD_ST_SUBSTATE_COUNT(13,0);
          _SFD_ST_SUBSTATE_COUNT(14,0);
          _SFD_ST_SUBSTATE_COUNT(15,0);
          _SFD_ST_SUBSTATE_COUNT(16,0);
          _SFD_ST_SUBSTATE_COUNT(17,0);
          _SFD_ST_SUBSTATE_COUNT(18,0);
          _SFD_ST_SUBSTATE_COUNT(19,0);
          _SFD_ST_SUBSTATE_COUNT(20,0);
          _SFD_ST_SUBSTATE_COUNT(21,0);
          _SFD_ST_SUBSTATE_COUNT(22,3);
          _SFD_ST_SUBSTATE_INDEX(22,0,23);
          _SFD_ST_SUBSTATE_INDEX(22,1,27);
          _SFD_ST_SUBSTATE_INDEX(22,2,31);
          _SFD_ST_SUBSTATE_COUNT(23,3);
          _SFD_ST_SUBSTATE_INDEX(23,0,24);
          _SFD_ST_SUBSTATE_INDEX(23,1,25);
          _SFD_ST_SUBSTATE_INDEX(23,2,26);
          _SFD_ST_SUBSTATE_COUNT(24,0);
          _SFD_ST_SUBSTATE_COUNT(25,0);
          _SFD_ST_SUBSTATE_COUNT(26,0);
          _SFD_ST_SUBSTATE_COUNT(27,3);
          _SFD_ST_SUBSTATE_INDEX(27,0,28);
          _SFD_ST_SUBSTATE_INDEX(27,1,29);
          _SFD_ST_SUBSTATE_INDEX(27,2,30);
          _SFD_ST_SUBSTATE_COUNT(28,0);
          _SFD_ST_SUBSTATE_COUNT(29,0);
          _SFD_ST_SUBSTATE_COUNT(30,0);
          _SFD_ST_SUBSTATE_COUNT(31,5);
          _SFD_ST_SUBSTATE_INDEX(31,0,32);
          _SFD_ST_SUBSTATE_INDEX(31,1,38);
          _SFD_ST_SUBSTATE_INDEX(31,2,44);
          _SFD_ST_SUBSTATE_INDEX(31,3,45);
          _SFD_ST_SUBSTATE_INDEX(31,4,46);
          _SFD_ST_SUBSTATE_COUNT(32,5);
          _SFD_ST_SUBSTATE_INDEX(32,0,33);
          _SFD_ST_SUBSTATE_INDEX(32,1,34);
          _SFD_ST_SUBSTATE_INDEX(32,2,35);
          _SFD_ST_SUBSTATE_INDEX(32,3,36);
          _SFD_ST_SUBSTATE_INDEX(32,4,37);
          _SFD_ST_SUBSTATE_COUNT(33,0);
          _SFD_ST_SUBSTATE_COUNT(34,0);
          _SFD_ST_SUBSTATE_COUNT(35,0);
          _SFD_ST_SUBSTATE_COUNT(36,0);
          _SFD_ST_SUBSTATE_COUNT(37,0);
          _SFD_ST_SUBSTATE_COUNT(38,2);
          _SFD_ST_SUBSTATE_INDEX(38,0,39);
          _SFD_ST_SUBSTATE_INDEX(38,1,43);
          _SFD_ST_SUBSTATE_COUNT(39,3);
          _SFD_ST_SUBSTATE_INDEX(39,0,40);
          _SFD_ST_SUBSTATE_INDEX(39,1,41);
          _SFD_ST_SUBSTATE_INDEX(39,2,42);
          _SFD_ST_SUBSTATE_COUNT(40,0);
          _SFD_ST_SUBSTATE_COUNT(41,0);
          _SFD_ST_SUBSTATE_COUNT(42,0);
          _SFD_ST_SUBSTATE_COUNT(43,0);
          _SFD_ST_SUBSTATE_COUNT(44,0);
          _SFD_ST_SUBSTATE_COUNT(45,0);
          _SFD_ST_SUBSTATE_COUNT(46,0);
          _SFD_ST_SUBSTATE_COUNT(47,3);
          _SFD_ST_SUBSTATE_INDEX(47,0,48);
          _SFD_ST_SUBSTATE_INDEX(47,1,52);
          _SFD_ST_SUBSTATE_INDEX(47,2,56);
          _SFD_ST_SUBSTATE_COUNT(48,3);
          _SFD_ST_SUBSTATE_INDEX(48,0,49);
          _SFD_ST_SUBSTATE_INDEX(48,1,50);
          _SFD_ST_SUBSTATE_INDEX(48,2,51);
          _SFD_ST_SUBSTATE_COUNT(49,0);
          _SFD_ST_SUBSTATE_COUNT(50,0);
          _SFD_ST_SUBSTATE_COUNT(51,0);
          _SFD_ST_SUBSTATE_COUNT(52,3);
          _SFD_ST_SUBSTATE_INDEX(52,0,53);
          _SFD_ST_SUBSTATE_INDEX(52,1,54);
          _SFD_ST_SUBSTATE_INDEX(52,2,55);
          _SFD_ST_SUBSTATE_COUNT(53,0);
          _SFD_ST_SUBSTATE_COUNT(54,0);
          _SFD_ST_SUBSTATE_COUNT(55,0);
          _SFD_ST_SUBSTATE_COUNT(56,4);
          _SFD_ST_SUBSTATE_INDEX(56,0,57);
          _SFD_ST_SUBSTATE_INDEX(56,1,63);
          _SFD_ST_SUBSTATE_INDEX(56,2,64);
          _SFD_ST_SUBSTATE_INDEX(56,3,65);
          _SFD_ST_SUBSTATE_COUNT(57,2);
          _SFD_ST_SUBSTATE_INDEX(57,0,58);
          _SFD_ST_SUBSTATE_INDEX(57,1,62);
          _SFD_ST_SUBSTATE_COUNT(58,3);
          _SFD_ST_SUBSTATE_INDEX(58,0,59);
          _SFD_ST_SUBSTATE_INDEX(58,1,60);
          _SFD_ST_SUBSTATE_INDEX(58,2,61);
          _SFD_ST_SUBSTATE_COUNT(59,0);
          _SFD_ST_SUBSTATE_COUNT(60,0);
          _SFD_ST_SUBSTATE_COUNT(61,0);
          _SFD_ST_SUBSTATE_COUNT(62,0);
          _SFD_ST_SUBSTATE_COUNT(63,0);
          _SFD_ST_SUBSTATE_COUNT(64,0);
          _SFD_ST_SUBSTATE_COUNT(65,0);
          _SFD_ST_SUBSTATE_COUNT(66,3);
          _SFD_ST_SUBSTATE_INDEX(66,0,67);
          _SFD_ST_SUBSTATE_INDEX(66,1,71);
          _SFD_ST_SUBSTATE_INDEX(66,2,75);
          _SFD_ST_SUBSTATE_COUNT(67,3);
          _SFD_ST_SUBSTATE_INDEX(67,0,68);
          _SFD_ST_SUBSTATE_INDEX(67,1,69);
          _SFD_ST_SUBSTATE_INDEX(67,2,70);
          _SFD_ST_SUBSTATE_COUNT(68,0);
          _SFD_ST_SUBSTATE_COUNT(69,0);
          _SFD_ST_SUBSTATE_COUNT(70,0);
          _SFD_ST_SUBSTATE_COUNT(71,3);
          _SFD_ST_SUBSTATE_INDEX(71,0,72);
          _SFD_ST_SUBSTATE_INDEX(71,1,73);
          _SFD_ST_SUBSTATE_INDEX(71,2,74);
          _SFD_ST_SUBSTATE_COUNT(72,0);
          _SFD_ST_SUBSTATE_COUNT(73,0);
          _SFD_ST_SUBSTATE_COUNT(74,0);
          _SFD_ST_SUBSTATE_COUNT(75,4);
          _SFD_ST_SUBSTATE_INDEX(75,0,76);
          _SFD_ST_SUBSTATE_INDEX(75,1,83);
          _SFD_ST_SUBSTATE_INDEX(75,2,84);
          _SFD_ST_SUBSTATE_INDEX(75,3,85);
          _SFD_ST_SUBSTATE_COUNT(76,2);
          _SFD_ST_SUBSTATE_INDEX(76,0,77);
          _SFD_ST_SUBSTATE_INDEX(76,1,82);
          _SFD_ST_SUBSTATE_COUNT(77,4);
          _SFD_ST_SUBSTATE_INDEX(77,0,78);
          _SFD_ST_SUBSTATE_INDEX(77,1,79);
          _SFD_ST_SUBSTATE_INDEX(77,2,80);
          _SFD_ST_SUBSTATE_INDEX(77,3,81);
          _SFD_ST_SUBSTATE_COUNT(78,0);
          _SFD_ST_SUBSTATE_COUNT(79,0);
          _SFD_ST_SUBSTATE_COUNT(80,0);
          _SFD_ST_SUBSTATE_COUNT(81,0);
          _SFD_ST_SUBSTATE_COUNT(82,0);
          _SFD_ST_SUBSTATE_COUNT(83,0);
          _SFD_ST_SUBSTATE_COUNT(84,0);
          _SFD_ST_SUBSTATE_COUNT(85,0);
          _SFD_ST_SUBSTATE_COUNT(87,3);
          _SFD_ST_SUBSTATE_INDEX(87,0,88);
          _SFD_ST_SUBSTATE_INDEX(87,1,98);
          _SFD_ST_SUBSTATE_INDEX(87,2,108);
          _SFD_ST_SUBSTATE_COUNT(88,2);
          _SFD_ST_SUBSTATE_INDEX(88,0,95);
          _SFD_ST_SUBSTATE_INDEX(88,1,89);
          _SFD_ST_SUBSTATE_COUNT(95,2);
          _SFD_ST_SUBSTATE_INDEX(95,0,96);
          _SFD_ST_SUBSTATE_INDEX(95,1,97);
          _SFD_ST_SUBSTATE_COUNT(96,0);
          _SFD_ST_SUBSTATE_COUNT(97,0);
          _SFD_ST_SUBSTATE_COUNT(89,3);
          _SFD_ST_SUBSTATE_INDEX(89,0,90);
          _SFD_ST_SUBSTATE_INDEX(89,1,93);
          _SFD_ST_SUBSTATE_INDEX(89,2,94);
          _SFD_ST_SUBSTATE_COUNT(90,2);
          _SFD_ST_SUBSTATE_INDEX(90,0,91);
          _SFD_ST_SUBSTATE_INDEX(90,1,92);
          _SFD_ST_SUBSTATE_COUNT(91,0);
          _SFD_ST_SUBSTATE_COUNT(92,0);
          _SFD_ST_SUBSTATE_COUNT(93,0);
          _SFD_ST_SUBSTATE_COUNT(94,0);
          _SFD_ST_SUBSTATE_COUNT(98,2);
          _SFD_ST_SUBSTATE_INDEX(98,0,105);
          _SFD_ST_SUBSTATE_INDEX(98,1,99);
          _SFD_ST_SUBSTATE_COUNT(105,2);
          _SFD_ST_SUBSTATE_INDEX(105,0,106);
          _SFD_ST_SUBSTATE_INDEX(105,1,107);
          _SFD_ST_SUBSTATE_COUNT(106,0);
          _SFD_ST_SUBSTATE_COUNT(107,0);
          _SFD_ST_SUBSTATE_COUNT(99,3);
          _SFD_ST_SUBSTATE_INDEX(99,0,100);
          _SFD_ST_SUBSTATE_INDEX(99,1,103);
          _SFD_ST_SUBSTATE_INDEX(99,2,104);
          _SFD_ST_SUBSTATE_COUNT(100,2);
          _SFD_ST_SUBSTATE_INDEX(100,0,101);
          _SFD_ST_SUBSTATE_INDEX(100,1,102);
          _SFD_ST_SUBSTATE_COUNT(101,0);
          _SFD_ST_SUBSTATE_COUNT(102,0);
          _SFD_ST_SUBSTATE_COUNT(103,0);
          _SFD_ST_SUBSTATE_COUNT(104,0);
          _SFD_ST_SUBSTATE_COUNT(108,0);
          _SFD_ST_SUBSTATE_COUNT(86,0);
        }

        _SFD_CV_INIT_CHART(3,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,5,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(10,4,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(11,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(12,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(13,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(14,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(15,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(16,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(17,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(18,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(19,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(20,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(21,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(22,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(23,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(24,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(25,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(26,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(27,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(28,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(29,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(30,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(31,5,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(32,5,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(33,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(34,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(35,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(36,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(37,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(38,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(39,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(40,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(41,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(42,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(43,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(44,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(45,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(46,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(47,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(48,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(49,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(50,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(51,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(52,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(53,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(54,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(55,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(56,4,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(57,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(58,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(59,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(60,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(61,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(62,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(63,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(64,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(65,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(66,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(67,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(68,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(69,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(70,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(71,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(72,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(73,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(74,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(75,4,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(76,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(77,4,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(78,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(79,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(80,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(81,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(82,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(83,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(84,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(85,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(86,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(87,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(88,2,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(89,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(90,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(91,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(92,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(93,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(94,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(95,2,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(96,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(97,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(98,2,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(99,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(100,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(101,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(102,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(103,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(104,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(105,2,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(106,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(107,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(108,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(225,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(226,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 39 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(224,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 39 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(224,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 34 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(243,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 34 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(243,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(20,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 42, 73, 103 };

          static unsigned int sEndGuardMap[] = { 35, 66, 96, 138 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(18,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 42, 73, 103 };

          static unsigned int sEndRelationalopMap[] = { 35, 66, 96, 138 };

          static int sRelationalopEps[] = { 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(18,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 65 };

          static unsigned int sEndGuardMap[] = { 24, 58, 88 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(19,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 65 };

          static unsigned int sEndRelationalopMap[] = { 24, 58, 88 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 0, 1, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(19,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 25 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(44,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 25 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(44,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 14 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(83,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 37 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(212,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 37 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(212,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 17 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(10,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 25, 68, 106, 148 };

          static unsigned int sEndGuardMap[] = { 17, 60, 98, 140, 180 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3, 4, -3 };

          _SFD_CV_INIT_TRANS(21,5,&(sStartGuardMap[0]),&(sEndGuardMap[0]),9,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 25, 68, 106, 148 };

          static unsigned int sEndRelationalopMap[] = { 60, 98, 140, 180 };

          static int sRelationalopEps[] = { 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 1, 0, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(21,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 43 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(22,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 25, 68, 104, 146 };

          static unsigned int sEndGuardMap[] = { 17, 60, 96, 138, 178 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3, 4, -3 };

          _SFD_CV_INIT_TRANS(11,5,&(sStartGuardMap[0]),&(sEndGuardMap[0]),9,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 25, 68, 104, 146 };

          static unsigned int sEndRelationalopMap[] = { 60, 96, 138, 178 };

          static int sRelationalopEps[] = { 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 1, 0, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(11,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 17 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(12,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26, 63 };

          static unsigned int sEndGuardMap[] = { 19, 56, 90 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(13,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26, 63 };

          static unsigned int sEndRelationalopMap[] = { 56, 90 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(13,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(14,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 25 };

          static unsigned int sEndGuardMap[] = { 17, 56 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(15,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 25 };

          static unsigned int sEndRelationalopMap[] = { 56 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(15,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 25 };

          static unsigned int sEndGuardMap[] = { 17, 57 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(16,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 25 };

          static unsigned int sEndRelationalopMap[] = { 57 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(16,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 33 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(17,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 33 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(17,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(227,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 42, 73 };

          static unsigned int sEndGuardMap[] = { 35, 66, 96 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(228,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 42, 73 };

          static unsigned int sEndRelationalopMap[] = { 35, 66, 96 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(228,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 65 };

          static unsigned int sEndGuardMap[] = { 24, 58, 88 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(229,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 65 };

          static unsigned int sEndRelationalopMap[] = { 24, 58, 88 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 0, 1, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(229,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 25 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(230,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 25 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(230,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 14 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(231,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(232,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 17 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(233,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 25, 63, 105 };

          static unsigned int sEndGuardMap[] = { 17, 55, 97, 135 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(234,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 25, 63, 105 };

          static unsigned int sEndRelationalopMap[] = { 55, 97, 135 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(234,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 25, 61, 103 };

          static unsigned int sEndGuardMap[] = { 17, 53, 95, 133 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(235,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 25, 61, 103 };

          static unsigned int sEndRelationalopMap[] = { 53, 95, 133 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(235,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 43 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(236,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 17 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(237,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26, 63 };

          static unsigned int sEndGuardMap[] = { 19, 56, 90 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(238,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26, 63 };

          static unsigned int sEndRelationalopMap[] = { 56, 90 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(238,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(239,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 25 };

          static unsigned int sEndGuardMap[] = { 17, 56 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(240,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 25 };

          static unsigned int sEndRelationalopMap[] = { 56 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(240,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 25 };

          static unsigned int sEndGuardMap[] = { 17, 55 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(241,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 25 };

          static unsigned int sEndRelationalopMap[] = { 55 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(241,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 31 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(242,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 31 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(242,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 34 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 34 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 31 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(127,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 31 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(127,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 35 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(128,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 35 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(128,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(129,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 37 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(177,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 37 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(177,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(84,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 37, 68 };

          static unsigned int sEndGuardMap[] = { 28, 59, 103 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(57,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 37, 68 };

          static unsigned int sEndRelationalopMap[] = { 28, 59, 103 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(57,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 39 };

          static unsigned int sEndGuardMap[] = { 30, 61 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(58,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 39 };

          static unsigned int sEndRelationalopMap[] = { 30, 61 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(58,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 38, 70 };

          static unsigned int sEndGuardMap[] = { 29, 61, 104 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(59,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 38, 70 };

          static unsigned int sEndRelationalopMap[] = { 29, 61, 104 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(59,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 40 };

          static unsigned int sEndGuardMap[] = { 31, 63 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(60,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 40 };

          static unsigned int sEndRelationalopMap[] = { 31, 63 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(60,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(31,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57 };

          static unsigned int sEndGuardMap[] = { 21, 49, 83 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(30,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 83 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(30,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 41, 82, 136, 163, 216, 250,
            281 };

          static unsigned int sEndGuardMap[] = { 32, 71, 123, 147, 206, 242, 273,
            296 };

          static int sPostFixPredicateTree[] = { 0, 1, 2, -2, 3, -1, 4, -3, -2,
            -3, 5, -3, 6, -3, 7, -3 };

          _SFD_CV_INIT_TRANS(3,8,&(sStartGuardMap[0]),&(sEndGuardMap[0]),16,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 41, 82, 163, 216,
            250 };

          static unsigned int sEndRelationalopMap[] = { 32, 71, 123, 206, 242,
            273 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(3,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 21, 49 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(29,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29 };

          static unsigned int sEndRelationalopMap[] = { 21, 49 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(29,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 40, 74 };

          static unsigned int sEndGuardMap[] = { 32, 66, 97 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(4,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 40, 74 };

          static unsigned int sEndRelationalopMap[] = { 32, 66, 97 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 1, 1, 0, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(4,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 21, 49 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(34,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29 };

          static unsigned int sEndRelationalopMap[] = { 21, 49 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(34,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 31 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(32,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 31 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(32,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(33,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 27, 49 };

          static unsigned int sEndGuardMap[] = { 20, 41, 78 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -3 };

          _SFD_CV_INIT_TRANS(37,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 49 };

          static unsigned int sEndRelationalopMap[] = { 78 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(37,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 31 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(35,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 31 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(35,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(38,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(36,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(39,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(43,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 24 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(43,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 53, 93, 136, 175, 210, 226,
            249 };

          static unsigned int sEndGuardMap[] = { 43, 87, 126, 166, 201, 221, 241,
            292 };

          static int sPostFixPredicateTree[] = { 0, 1, 2, -2, -3, 3, -3, 4, -3,
            5, -3, 6, -3, 7, -3 };

          _SFD_CV_INIT_TRANS(74,8,&(sStartGuardMap[0]),&(sEndGuardMap[0]),15,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 53, 93, 136, 175,
            249 };

          static unsigned int sEndRelationalopMap[] = { 43, 87, 126, 166, 201,
            292 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(74,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 3, 43, 87, 127 };

          static unsigned int sEndGuardMap[] = { 37, 76, 117, 153 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -2, 3, -2 };

          _SFD_CV_INIT_TRANS(75,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 3, 43, 87, 127 };

          static unsigned int sEndRelationalopMap[] = { 37, 76, 117, 153 };

          static int sRelationalopEps[] = { 0, 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(75,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(26,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(41,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(41,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(40,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 54 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(24,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 54 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(24,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 40 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(23,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 68 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(42,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 68 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(42,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(45,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 34 };

          static unsigned int sEndGuardMap[] = { 27, 76 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(5,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 34 };

          static unsigned int sEndRelationalopMap[] = { 27, 76 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(27,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 37 };

          static unsigned int sEndGuardMap[] = { 30, 79 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(7,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 37 };

          static unsigned int sEndRelationalopMap[] = { 30, 79 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(7,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(28,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(25,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(6,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 54 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(2,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 54 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 43 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(48,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 43 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(48,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(46,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(47,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 68 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(8,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 68 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(8,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(76,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(77,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 22 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(80,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 40 };

          static unsigned int sEndGuardMap[] = { 33, 61 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(82,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 21 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(78,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 33 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(79,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 33 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(81,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(49,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(50,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(50,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57, 86, 115, 153 };

          static unsigned int sEndGuardMap[] = { 21, 49, 78, 107, 145, 179 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2 };

          _SFD_CV_INIT_TRANS(51,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57, 86, 115,
            153 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 78, 107, 145,
            179 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(51,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(52,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(52,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(72,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(53,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(54,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(54,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57, 86, 115, 153 };

          static unsigned int sEndGuardMap[] = { 21, 49, 78, 107, 145, 179 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2 };

          _SFD_CV_INIT_TRANS(55,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57, 86, 115,
            153 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 78, 107, 145,
            179 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(55,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(73,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(56,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(56,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(134,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 37, 68 };

          static unsigned int sEndGuardMap[] = { 28, 59, 103 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(135,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 37, 68 };

          static unsigned int sEndRelationalopMap[] = { 28, 59, 103 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(135,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 39 };

          static unsigned int sEndGuardMap[] = { 30, 61 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(136,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 39 };

          static unsigned int sEndRelationalopMap[] = { 30, 61 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(136,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 38, 70 };

          static unsigned int sEndGuardMap[] = { 29, 61, 104 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(137,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 38, 70 };

          static unsigned int sEndRelationalopMap[] = { 29, 61, 104 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(137,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 40 };

          static unsigned int sEndGuardMap[] = { 31, 63 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(138,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 40 };

          static unsigned int sEndRelationalopMap[] = { 31, 63 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(138,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(139,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57 };

          static unsigned int sEndGuardMap[] = { 21, 49, 83 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(140,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 83 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(140,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 40, 74, 105 };

          static unsigned int sEndGuardMap[] = { 32, 66, 97, 120 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(141,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 40, 74 };

          static unsigned int sEndRelationalopMap[] = { 32, 66, 97 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 0, 0, 1, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(141,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 21, 49 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(142,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29 };

          static unsigned int sEndRelationalopMap[] = { 21, 49 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(142,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 40, 74 };

          static unsigned int sEndGuardMap[] = { 32, 66, 97 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(143,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 40, 74 };

          static unsigned int sEndRelationalopMap[] = { 32, 66, 97 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 1, 1, 0, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(143,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 21, 49 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(144,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29 };

          static unsigned int sEndRelationalopMap[] = { 21, 49 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(144,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 31 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(145,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 31 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(145,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(146,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 27, 49 };

          static unsigned int sEndGuardMap[] = { 20, 41, 78 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -3 };

          _SFD_CV_INIT_TRANS(147,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 49 };

          static unsigned int sEndRelationalopMap[] = { 78 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(147,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 31 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(148,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 31 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(148,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(149,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(150,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(151,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(152,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 24 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(152,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(154,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(154,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(153,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(155,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 54 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(156,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 54 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(156,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 40 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(158,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(157,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(159,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(159,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(160,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(161,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(161,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(162,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(163,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(164,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 54 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(165,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 54 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(165,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(166,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(167,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(168,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(168,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57, 86, 115, 153 };

          static unsigned int sEndGuardMap[] = { 21, 49, 78, 107, 145, 179 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2 };

          _SFD_CV_INIT_TRANS(169,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57, 86, 115,
            153 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 78, 107, 145,
            179 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(169,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(170,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(170,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(171,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(172,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(173,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(173,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57, 86, 115, 153 };

          static unsigned int sEndGuardMap[] = { 21, 49, 78, 107, 145, 179 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2 };

          _SFD_CV_INIT_TRANS(174,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57, 86, 115,
            153 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 78, 107, 145,
            179 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(174,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(175,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(176,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(176,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(85,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 37, 68 };

          static unsigned int sEndGuardMap[] = { 28, 59, 103 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(86,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 37, 68 };

          static unsigned int sEndRelationalopMap[] = { 28, 59, 103 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(86,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 39 };

          static unsigned int sEndGuardMap[] = { 30, 61 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(87,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 39 };

          static unsigned int sEndRelationalopMap[] = { 30, 61 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(87,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 38, 70 };

          static unsigned int sEndGuardMap[] = { 29, 61, 104 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(88,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 38, 70 };

          static unsigned int sEndRelationalopMap[] = { 29, 61, 104 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(88,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 40 };

          static unsigned int sEndGuardMap[] = { 31, 63 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(89,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 40 };

          static unsigned int sEndRelationalopMap[] = { 31, 63 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(89,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(90,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57 };

          static unsigned int sEndGuardMap[] = { 21, 49, 83 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(91,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 83 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(91,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 40, 74, 105 };

          static unsigned int sEndGuardMap[] = { 32, 66, 97, 120 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(92,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 40, 74 };

          static unsigned int sEndRelationalopMap[] = { 32, 66, 97 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 0, 0, 1, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(92,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 21, 49 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(93,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29 };

          static unsigned int sEndRelationalopMap[] = { 21, 49 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(93,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 40, 74 };

          static unsigned int sEndGuardMap[] = { 32, 66, 97 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(94,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 40, 74 };

          static unsigned int sEndRelationalopMap[] = { 32, 66, 97 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 1, 1, 0, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(94,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 21, 49 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(95,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29 };

          static unsigned int sEndRelationalopMap[] = { 21, 49 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(95,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 31 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(96,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 31 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(96,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(97,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 27, 49 };

          static unsigned int sEndGuardMap[] = { 20, 41, 78 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -3 };

          _SFD_CV_INIT_TRANS(98,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 49 };

          static unsigned int sEndRelationalopMap[] = { 78 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(98,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 31 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(99,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 31 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(99,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(100,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(101,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(102,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(103,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 24 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(103,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(105,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(105,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(104,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(106,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 54 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(107,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 54 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(107,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 40 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(130,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(108,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(109,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(109,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(110,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(111,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(111,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(112,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(113,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(113,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(132,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(131,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(114,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 54 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(115,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 54 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(115,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(116,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(133,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(117,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(118,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(118,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57, 86, 115, 153 };

          static unsigned int sEndGuardMap[] = { 21, 49, 78, 107, 145, 179 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2 };

          _SFD_CV_INIT_TRANS(119,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57, 86, 115,
            153 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 78, 107, 145,
            179 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(119,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(120,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(120,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(121,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(122,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(123,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(123,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57, 86, 115, 153 };

          static unsigned int sEndGuardMap[] = { 21, 49, 78, 107, 145, 179 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2 };

          _SFD_CV_INIT_TRANS(124,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57, 86, 115,
            153 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 78, 107, 145,
            179 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(124,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(125,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(126,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(126,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(178,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 37, 68 };

          static unsigned int sEndGuardMap[] = { 28, 59, 103 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(179,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 37, 68 };

          static unsigned int sEndRelationalopMap[] = { 28, 59, 103 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(179,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 39 };

          static unsigned int sEndGuardMap[] = { 30, 61 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(180,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 39 };

          static unsigned int sEndRelationalopMap[] = { 30, 61 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(180,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 38, 70 };

          static unsigned int sEndGuardMap[] = { 29, 61, 104 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(181,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 38, 70 };

          static unsigned int sEndRelationalopMap[] = { 29, 61, 104 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(181,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 40 };

          static unsigned int sEndGuardMap[] = { 31, 63 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(182,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 40 };

          static unsigned int sEndRelationalopMap[] = { 31, 63 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(182,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(183,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 61 };

          static unsigned int sEndGuardMap[] = { 23, 53, 87 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(184,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 61 };

          static unsigned int sEndRelationalopMap[] = { 23, 53, 87 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(184,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 39, 72, 102 };

          static unsigned int sEndGuardMap[] = { 32, 65, 95, 117 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(185,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 39, 72 };

          static unsigned int sEndRelationalopMap[] = { 32, 65, 95 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 0, 0, 1, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(185,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(192,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31 };

          static unsigned int sEndGuardMap[] = { 23, 53 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(186,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31 };

          static unsigned int sEndRelationalopMap[] = { 23, 53 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(186,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 40, 74 };

          static unsigned int sEndGuardMap[] = { 32, 66, 97 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(187,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 40, 74 };

          static unsigned int sEndRelationalopMap[] = { 32, 66, 97 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 1, 1, 0, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(187,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 31 };

          static unsigned int sEndGuardMap[] = { 23, 53 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(188,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31 };

          static unsigned int sEndRelationalopMap[] = { 23, 53 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(188,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 33 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(189,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 33 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(189,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 20, 42 };

          static unsigned int sEndGuardMap[] = { 13, 38, 56 };

          static int sPostFixPredicateTree[] = { 0, -1, 1, 2, -2, -3 };

          _SFD_CV_INIT_TRANS(190,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),6,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 33 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(191,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 33 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(191,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(193,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 24 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(193,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(219,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(216,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(216,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(221,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(222,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 54 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(194,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 54 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(194,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(196,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 22, 40 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(210,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 20, 42 };

          static unsigned int sEndGuardMap[] = { 13, 38, 56 };

          static int sPostFixPredicateTree[] = { 0, -1, 1, 2, -2, -3 };

          _SFD_CV_INIT_TRANS(195,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),6,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 62 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(211,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 62 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(211,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 3, 55, 107 };

          static unsigned int sEndGuardMap[] = { 46, 98, 123 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -2 };

          _SFD_CV_INIT_TRANS(214,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 3, 55 };

          static unsigned int sEndRelationalopMap[] = { 46, 98 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(214,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 20, 42 };

          static unsigned int sEndGuardMap[] = { 13, 38, 56 };

          static int sPostFixPredicateTree[] = { 0, -1, 1, 2, -2, -3 };

          _SFD_CV_INIT_TRANS(223,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),6,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(244,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 35, 53 };

          static unsigned int sEndGuardMap[] = { 27, 46, 95 };

          static int sPostFixPredicateTree[] = { 0, 1, -1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(220,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),6,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 53, 1, 53 };

          static unsigned int sEndRelationalopMap[] = { 27, 95, 27, 95 };

          static int sRelationalopEps[] = { 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1, 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(220,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(218,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 38, 56 };

          static unsigned int sEndGuardMap[] = { 30, 49, 98 };

          static int sPostFixPredicateTree[] = { 0, 1, -1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(213,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),6,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 56, 1, 56 };

          static unsigned int sEndRelationalopMap[] = { 30, 98, 30, 98 };

          static int sRelationalopEps[] = { 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1, 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(213,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(215,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(217,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(197,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 26 };

          static unsigned int sEndGuardMap[] = { 19, 54 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(198,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 26 };

          static unsigned int sEndRelationalopMap[] = { 54 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(198,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(199,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(200,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(201,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(201,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57, 86, 115, 153 };

          static unsigned int sEndGuardMap[] = { 21, 49, 78, 107, 145, 179 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2 };

          _SFD_CV_INIT_TRANS(202,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57, 86, 115,
            153 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 78, 107, 145,
            179 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(202,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(203,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(203,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(204,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(205,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(206,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(206,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 57, 86, 115, 153 };

          static unsigned int sEndGuardMap[] = { 21, 49, 78, 107, 145, 179 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2 };

          _SFD_CV_INIT_TRANS(207,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 57, 86, 115,
            153 };

          static unsigned int sEndRelationalopMap[] = { 21, 49, 78, 107, 145,
            179 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(207,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 0 };

          static unsigned int sEndGuardMap[] = { 11 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(208,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(209,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(209,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(61,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 44 };

          static unsigned int sEndGuardMap[] = { 36, 74 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(63,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 44 };

          static unsigned int sEndRelationalopMap[] = { 36, 74 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 1, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(63,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(62,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(64,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(65,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(66,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 45 };

          static unsigned int sEndGuardMap[] = { 37, 73 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(67,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 45 };

          static unsigned int sEndRelationalopMap[] = { 37, 73 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 1, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(67,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(70,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(68,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(69,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(71,0,NULL,NULL,0,NULL);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_c_sf_marshallOut,(MexInFcnForType)
          c42_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(27,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(28,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(29,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(30,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(31,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(32,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(33,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(34,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(35,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(36,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(37,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(38,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(39,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(40,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(41,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(42,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(43,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(44,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(45,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(46,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(47,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(48,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_d_sf_marshallOut,(MexInFcnForType)
          c42_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(49,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_d_sf_marshallOut,(MexInFcnForType)
          c42_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(50,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(51,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(52,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(53,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_d_sf_marshallOut,(MexInFcnForType)
          c42_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(54,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(55,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(56,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(57,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(58,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(59,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(60,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(61,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(62,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(63,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(64,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(65,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(66,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(67,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(68,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(69,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(70,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(71,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(72,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(73,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(74,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(75,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(76,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(77,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(78,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(79,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(80,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(81,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c42_b_sf_marshallOut,(MexInFcnForType)
          c42_b_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _MX_Gtwy_ControlMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc42_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c42_DetentRisingEdge);
        _SFD_SET_DATA_VALUE_PTR(25U, (void *)chartInstance->c42_state_AuxEnable);
        _SFD_SET_DATA_VALUE_PTR(32U, (void *)&chartInstance->c42_ACTIVE_MODE_ONE);
        _SFD_SET_DATA_VALUE_PTR(45U, (void *)&chartInstance->c42_BASE_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(46U, (void *)&chartInstance->c42_BASE_DETENT);
        _SFD_SET_DATA_VALUE_PTR(61U, (void *)&chartInstance->c42_ENGINE_CRANKING);
        _SFD_SET_DATA_VALUE_PTR(26U, (void *)chartInstance->c42_state_Detent);
        _SFD_SET_DATA_VALUE_PTR(68U, (void *)&chartInstance->c42_NON_FUNCTIONAL);
        _SFD_SET_DATA_VALUE_PTR(66U, (void *)&chartInstance->c42_INACTIVE);
        _SFD_SET_DATA_VALUE_PTR(71U, (void *)&chartInstance->c42_NO_DETENT);
        _SFD_SET_DATA_VALUE_PTR(75U, (void *)&chartInstance->c42_ROD_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(76U, (void *)&chartInstance->c42_ROD_DETENT);
        _SFD_SET_DATA_VALUE_PTR(31U, (void *)&chartInstance->c42_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c42_state_AuxPot);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c42_state_Engine);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c42_state_Console);
        _SFD_SET_DATA_VALUE_PTR(70U, (void *)&chartInstance->c42_NOT_IN_NEUTRAL);
        _SFD_SET_DATA_VALUE_PTR(73U, (void *)&chartInstance->c42_OORH);
        _SFD_SET_DATA_VALUE_PTR(74U, (void *)&chartInstance->c42_OORL);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)
          chartInstance->c42_aux_DebounceButton);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c42_state_System);
        _SFD_SET_DATA_VALUE_PTR(27U, (void *)chartInstance->c42_aux_Flow);
        _SFD_SET_DATA_VALUE_PTR(79U, (void *)
          chartInstance->c42_ee_AuxFlow_address);
        _SFD_SET_DATA_VALUE_PTR(36U, (void *)&chartInstance->c42_AUX_FLOW_LOW);
        _SFD_SET_DATA_VALUE_PTR(37U, (void *)&chartInstance->c42_AUX_FLOW_MEDIUM);
        _SFD_SET_DATA_VALUE_PTR(34U, (void *)&chartInstance->c42_AUX_FLOW_HIGH);
        _SFD_SET_DATA_VALUE_PTR(47U, (void *)
          &chartInstance->c42_CD_AUX_ADJ_FLOW_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(81U, (void *)
          chartInstance->c42__indexstate_Buzzer_address);
        _SFD_SET_DATA_VALUE_PTR(77U, (void *)
          &chartInstance->c42_SINGLE_SHORT_BEEP);
        _SFD_SET_DATA_VALUE_PTR(50U, (void *)&chartInstance->c42_CD_AUX_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(28U, (void *)
          chartInstance->c42_state_DetentEnable);
        _SFD_SET_DATA_VALUE_PTR(65U, (void *)&chartInstance->c42_ERR_DETENT);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)chartInstance->c42_aux_DetentHold);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)chartInstance->c42_state_Buttons);
        _SFD_SET_DATA_VALUE_PTR(69U, (void *)&chartInstance->c42_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(78U, (void *)&chartInstance->c42_SYS_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(60U, (void *)
          &chartInstance->c42_DOUBLE_SHORT_BEEP);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)chartInstance->c42_flag_InitEERead);
        _SFD_SET_DATA_VALUE_PTR(12U, (void *)chartInstance->c42_can_AuxEnable_ST);
        _SFD_SET_DATA_VALUE_PTR(13U, (void *)
          chartInstance->c42_can_AuxEnable_ACD);
        _SFD_SET_DATA_VALUE_PTR(59U, (void *)
          &chartInstance->c42_CD_STAUX_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(57U, (void *)
          &chartInstance->c42_CD_RACD_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(14U, (void *)chartInstance->c42_state_ST_CAN);
        _SFD_SET_DATA_VALUE_PTR(15U, (void *)chartInstance->c42_state_ACD_CAN);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)&chartInstance->c42_state_ACD_old);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)&chartInstance->c42_state_ST_old);
        _SFD_SET_DATA_VALUE_PTR(16U, (void *)
          chartInstance->c42_button_AuxReleaseAck);
        _SFD_SET_DATA_VALUE_PTR(17U, (void *)
          chartInstance->c42_button_AuxReleaseBack);
        _SFD_SET_DATA_VALUE_PTR(18U, (void *)
          chartInstance->c42_button_AuxReleaseExit);
        _SFD_SET_DATA_VALUE_PTR(53U, (void *)
          &chartInstance->c42_CD_AUX_RELEASE_TIME);
        _SFD_SET_DATA_VALUE_PTR(48U, (void *)
          &chartInstance->c42_CD_AUX_CONFIRM_TIME);
        _SFD_SET_DATA_VALUE_PTR(43U, (void *)
          &chartInstance->c42_AUX_RELEASE_WAIT);
        _SFD_SET_DATA_VALUE_PTR(40U, (void *)&chartInstance->c42_AUX_RELEASE_ACK);
        _SFD_SET_DATA_VALUE_PTR(42U, (void *)
          &chartInstance->c42_AUX_RELEASE_IN_PROGRESS);
        _SFD_SET_DATA_VALUE_PTR(41U, (void *)
          &chartInstance->c42_AUX_RELEASE_CONFIRM);
        _SFD_SET_DATA_VALUE_PTR(52U, (void *)
          &chartInstance->c42_CD_AUX_RELEASE_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(29U, (void *)chartInstance->c42_cmd_AuxRelease);
        _SFD_SET_DATA_VALUE_PTR(63U, (void *)
          &chartInstance->c42_ENGINE_NOT_RUNNING);
        _SFD_SET_DATA_VALUE_PTR(80U, (void *)
          chartInstance->c42__indexee_DeluxeG5_address);
        _SFD_SET_DATA_VALUE_PTR(64U, (void *)&chartInstance->c42_ENGINE_RUNNING);
        _SFD_SET_DATA_VALUE_PTR(19U, (void *)chartInstance->c42_button_Aux);
        _SFD_SET_DATA_VALUE_PTR(49U, (void *)
          &chartInstance->c42_CD_AUX_DETENT_FLASH_TIME);
        _SFD_SET_DATA_VALUE_PTR(62U, (void *)
          &chartInstance->c42_ENGINE_INITIALIZE);
        _SFD_SET_DATA_VALUE_PTR(44U, (void *)&chartInstance->c42_AUX_SIRIUS2);
        _SFD_SET_DATA_VALUE_PTR(51U, (void *)
          &chartInstance->c42_CD_AUX_HIGH_FLOW);
        _SFD_SET_DATA_VALUE_PTR(38U, (void *)
          &chartInstance->c42_AUX_FLOW_STANDARD);
        _SFD_SET_DATA_VALUE_PTR(54U, (void *)
          &chartInstance->c42_CD_DELUXE_GEN5_5_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(30U, (void *)chartInstance->c42_state_AuxRelease);
        _SFD_SET_DATA_VALUE_PTR(35U, (void *)
          &chartInstance->c42_AUX_FLOW_INACTIVE);
        _SFD_SET_DATA_VALUE_PTR(33U, (void *)
          &chartInstance->c42_AUX_EMEA_CONTROLS);
        _SFD_SET_DATA_VALUE_PTR(39U, (void *)&chartInstance->c42_AUX_PHOENIX_K2);
        _SFD_SET_DATA_VALUE_PTR(20U, (void *)chartInstance->c42_state_RightPot);
        _SFD_SET_DATA_VALUE_PTR(21U, (void *)
          chartInstance->c42_change_OffsetSelectSw);
        _SFD_SET_DATA_VALUE_PTR(22U, (void *)
          chartInstance->c42_mode_RightControl);
        _SFD_SET_DATA_VALUE_PTR(67U, (void *)&chartInstance->c42_MODE_RIGHT_AUX1);
        _SFD_SET_DATA_VALUE_PTR(23U, (void *)chartInstance->c42_aux_Inhibit);
        _SFD_SET_DATA_VALUE_PTR(24U, (void *)
          chartInstance->c42_state_EngineSpeed);
        _SFD_SET_DATA_VALUE_PTR(72U, (void *)&chartInstance->c42_NO_SIGNAL);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)&chartInstance->c42_previouslyActive);
        _SFD_SET_DATA_VALUE_PTR(55U, (void *)
          &chartInstance->c42_CD_EMEA_CONTROLS_OPTION_B);
        _SFD_SET_DATA_VALUE_PTR(56U, (void *)
          &chartInstance->c42_CD_EMEA_CONTROLS_OPTION_C);
        _SFD_SET_DATA_VALUE_PTR(58U, (void *)
          &chartInstance->c42_CD_RIGHT_POT_FUNCTION);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sSZ0SoeBMBcebVfOAbY5oMG";
}

static void sf_opaque_initialize_c42_MX_Gtwy_Control(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc42_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c42_MX_Gtwy_Control((SFc42_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
  initialize_c42_MX_Gtwy_Control((SFc42_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c42_MX_Gtwy_Control(void *chartInstanceVar)
{
  enable_c42_MX_Gtwy_Control((SFc42_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c42_MX_Gtwy_Control(void *chartInstanceVar)
{
  disable_c42_MX_Gtwy_Control((SFc42_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c42_MX_Gtwy_Control(void *chartInstanceVar)
{
  sf_gateway_c42_MX_Gtwy_Control((SFc42_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c42_MX_Gtwy_Control(SimStruct* S)
{
  return get_sim_state_c42_MX_Gtwy_Control((SFc42_MX_Gtwy_ControlInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c42_MX_Gtwy_Control(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c42_MX_Gtwy_Control((SFc42_MX_Gtwy_ControlInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c42_MX_Gtwy_Control(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc42_MX_Gtwy_ControlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MX_Gtwy_Control_optimization_info();
    }

    finalize_c42_MX_Gtwy_Control((SFc42_MX_Gtwy_ControlInstanceStruct*)
      chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc42_MX_Gtwy_Control((SFc42_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c42_MX_Gtwy_Control(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c42_MX_Gtwy_Control((SFc42_MX_Gtwy_ControlInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c42_MX_Gtwy_Control(SimStruct *S)
{
  /* Actual parameters from chart:
     ACTIVE ACTIVE_MODE_ONE AUX_EMEA_CONTROLS AUX_FLOW_HIGH AUX_FLOW_INACTIVE AUX_FLOW_LOW AUX_FLOW_MEDIUM AUX_FLOW_STANDARD AUX_PHOENIX_K2 AUX_RELEASE_ACK AUX_RELEASE_CONFIRM AUX_RELEASE_IN_PROGRESS AUX_RELEASE_WAIT AUX_SIRIUS2 BASE_ACTIVE BASE_DETENT CD_AUX_ADJ_FLOW_FUNCTION CD_AUX_CONFIRM_TIME CD_AUX_DETENT_FLASH_TIME CD_AUX_FUNCTION CD_AUX_HIGH_FLOW CD_AUX_RELEASE_FUNCTION CD_AUX_RELEASE_TIME CD_DELUXE_GEN5_5_FUNCTION CD_EMEA_CONTROLS_OPTION_B CD_EMEA_CONTROLS_OPTION_C CD_RACD_FUNCTION CD_RIGHT_POT_FUNCTION CD_STAUX_FUNCTION DOUBLE_SHORT_BEEP ENGINE_CRANKING ENGINE_INITIALIZE ENGINE_NOT_RUNNING ENGINE_RUNNING ERR_DETENT INACTIVE MODE_RIGHT_AUX1 NON_FUNCTIONAL NORMAL NOT_IN_NEUTRAL NO_DETENT NO_SIGNAL OORH OORL ROD_ACTIVE ROD_DETENT SINGLE_SHORT_BEEP SYS_NORMAL
   */
  const char_T *rtParamNames[] = { "ACTIVE", "ACTIVE_MODE_ONE",
    "AUX_EMEA_CONTROLS", "AUX_FLOW_HIGH", "AUX_FLOW_INACTIVE", "AUX_FLOW_LOW",
    "AUX_FLOW_MEDIUM", "AUX_FLOW_STANDARD", "AUX_PHOENIX_K2", "AUX_RELEASE_ACK",
    "AUX_RELEASE_CONFIRM", "AUX_RELEASE_IN_PROGRESS", "AUX_RELEASE_WAIT",
    "AUX_SIRIUS2", "BASE_ACTIVE", "BASE_DETENT", "CD_AUX_ADJ_FLOW_FUNCTION",
    "CD_AUX_CONFIRM_TIME", "CD_AUX_DETENT_FLASH_TIME", "CD_AUX_FUNCTION",
    "CD_AUX_HIGH_FLOW", "CD_AUX_RELEASE_FUNCTION", "CD_AUX_RELEASE_TIME",
    "CD_DELUXE_GEN5_5_FUNCTION", "CD_EMEA_CONTROLS_OPTION_B",
    "CD_EMEA_CONTROLS_OPTION_C", "CD_RACD_FUNCTION", "CD_RIGHT_POT_FUNCTION",
    "CD_STAUX_FUNCTION", "DOUBLE_SHORT_BEEP", "ENGINE_CRANKING",
    "ENGINE_INITIALIZE", "ENGINE_NOT_RUNNING", "ENGINE_RUNNING", "ERR_DETENT",
    "INACTIVE", "MODE_RIGHT_AUX1", "NON_FUNCTIONAL", "NORMAL", "NOT_IN_NEUTRAL",
    "NO_DETENT", "NO_SIGNAL", "OORH", "OORL", "ROD_ACTIVE", "ROD_DETENT",
    "SINGLE_SHORT_BEEP", "SYS_NORMAL" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_UINT8);

  /* registration for ACTIVE_MODE_ONE*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT8);

  /* registration for AUX_EMEA_CONTROLS*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT8);

  /* registration for AUX_FLOW_HIGH*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_UINT8);

  /* registration for AUX_FLOW_INACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_UINT8);

  /* registration for AUX_FLOW_LOW*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_UINT8);

  /* registration for AUX_FLOW_MEDIUM*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_UINT8);

  /* registration for AUX_FLOW_STANDARD*/
  ssRegDlgParamAsRunTimeParam(S, 7, 7, rtParamNames[7], SS_UINT8);

  /* registration for AUX_PHOENIX_K2*/
  ssRegDlgParamAsRunTimeParam(S, 8, 8, rtParamNames[8], SS_UINT8);

  /* registration for AUX_RELEASE_ACK*/
  ssRegDlgParamAsRunTimeParam(S, 9, 9, rtParamNames[9], SS_UINT8);

  /* registration for AUX_RELEASE_CONFIRM*/
  ssRegDlgParamAsRunTimeParam(S, 10, 10, rtParamNames[10], SS_UINT8);

  /* registration for AUX_RELEASE_IN_PROGRESS*/
  ssRegDlgParamAsRunTimeParam(S, 11, 11, rtParamNames[11], SS_UINT8);

  /* registration for AUX_RELEASE_WAIT*/
  ssRegDlgParamAsRunTimeParam(S, 12, 12, rtParamNames[12], SS_UINT8);

  /* registration for AUX_SIRIUS2*/
  ssRegDlgParamAsRunTimeParam(S, 13, 13, rtParamNames[13], SS_UINT8);

  /* registration for BASE_ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 14, 14, rtParamNames[14], SS_UINT8);

  /* registration for BASE_DETENT*/
  ssRegDlgParamAsRunTimeParam(S, 15, 15, rtParamNames[15], SS_UINT8);

  /* registration for CD_AUX_ADJ_FLOW_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 16, 16, rtParamNames[16], SS_UINT8);

  /* registration for CD_AUX_CONFIRM_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 17, 17, rtParamNames[17], SS_UINT16);

  /* registration for CD_AUX_DETENT_FLASH_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 18, 18, rtParamNames[18], SS_UINT16);

  /* registration for CD_AUX_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 19, 19, rtParamNames[19], SS_UINT8);

  /* registration for CD_AUX_HIGH_FLOW*/
  ssRegDlgParamAsRunTimeParam(S, 20, 20, rtParamNames[20], SS_UINT8);

  /* registration for CD_AUX_RELEASE_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 21, 21, rtParamNames[21], SS_UINT8);

  /* registration for CD_AUX_RELEASE_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 22, 22, rtParamNames[22], SS_UINT16);

  /* registration for CD_DELUXE_GEN5_5_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 23, 23, rtParamNames[23], SS_UINT8);

  /* registration for CD_EMEA_CONTROLS_OPTION_B*/
  ssRegDlgParamAsRunTimeParam(S, 24, 24, rtParamNames[24], SS_UINT8);

  /* registration for CD_EMEA_CONTROLS_OPTION_C*/
  ssRegDlgParamAsRunTimeParam(S, 25, 25, rtParamNames[25], SS_UINT8);

  /* registration for CD_RACD_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 26, 26, rtParamNames[26], SS_UINT8);

  /* registration for CD_RIGHT_POT_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 27, 27, rtParamNames[27], SS_UINT8);

  /* registration for CD_STAUX_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 28, 28, rtParamNames[28], SS_UINT8);

  /* registration for DOUBLE_SHORT_BEEP*/
  ssRegDlgParamAsRunTimeParam(S, 29, 29, rtParamNames[29], SS_UINT8);

  /* registration for ENGINE_CRANKING*/
  ssRegDlgParamAsRunTimeParam(S, 30, 30, rtParamNames[30], SS_UINT8);

  /* registration for ENGINE_INITIALIZE*/
  ssRegDlgParamAsRunTimeParam(S, 31, 31, rtParamNames[31], SS_UINT8);

  /* registration for ENGINE_NOT_RUNNING*/
  ssRegDlgParamAsRunTimeParam(S, 32, 32, rtParamNames[32], SS_UINT8);

  /* registration for ENGINE_RUNNING*/
  ssRegDlgParamAsRunTimeParam(S, 33, 33, rtParamNames[33], SS_UINT8);

  /* registration for ERR_DETENT*/
  ssRegDlgParamAsRunTimeParam(S, 34, 34, rtParamNames[34], SS_UINT8);

  /* registration for INACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 35, 35, rtParamNames[35], SS_UINT8);

  /* registration for MODE_RIGHT_AUX1*/
  ssRegDlgParamAsRunTimeParam(S, 36, 36, rtParamNames[36], SS_UINT8);

  /* registration for NON_FUNCTIONAL*/
  ssRegDlgParamAsRunTimeParam(S, 37, 37, rtParamNames[37], SS_UINT8);

  /* registration for NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 38, 38, rtParamNames[38], SS_UINT8);

  /* registration for NOT_IN_NEUTRAL*/
  ssRegDlgParamAsRunTimeParam(S, 39, 39, rtParamNames[39], SS_UINT8);

  /* registration for NO_DETENT*/
  ssRegDlgParamAsRunTimeParam(S, 40, 40, rtParamNames[40], SS_UINT8);

  /* registration for NO_SIGNAL*/
  ssRegDlgParamAsRunTimeParam(S, 41, 41, rtParamNames[41], SS_UINT8);

  /* registration for OORH*/
  ssRegDlgParamAsRunTimeParam(S, 42, 42, rtParamNames[42], SS_UINT8);

  /* registration for OORL*/
  ssRegDlgParamAsRunTimeParam(S, 43, 43, rtParamNames[43], SS_UINT8);

  /* registration for ROD_ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 44, 44, rtParamNames[44], SS_UINT8);

  /* registration for ROD_DETENT*/
  ssRegDlgParamAsRunTimeParam(S, 45, 45, rtParamNames[45], SS_UINT8);

  /* registration for SINGLE_SHORT_BEEP*/
  ssRegDlgParamAsRunTimeParam(S, 46, 46, rtParamNames[46], SS_UINT8);

  /* registration for SYS_NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 47, 47, rtParamNames[47], SS_UINT8);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetInputPortDirectFeedThrough(S, 4, 1);
  ssSetInputPortDirectFeedThrough(S, 5, 1);
  ssSetInputPortDirectFeedThrough(S, 6, 1);
  ssSetInputPortDirectFeedThrough(S, 7, 1);
  ssSetInputPortDirectFeedThrough(S, 8, 1);
  ssSetInputPortDirectFeedThrough(S, 9, 1);
  ssSetInputPortDirectFeedThrough(S, 10, 1);
  ssSetInputPortDirectFeedThrough(S, 11, 1);
  ssSetInputPortDirectFeedThrough(S, 12, 1);
  ssSetInputPortDirectFeedThrough(S, 13, 1);
  ssSetInputPortDirectFeedThrough(S, 14, 1);
  ssSetInputPortDirectFeedThrough(S, 15, 1);
  ssSetInputPortDirectFeedThrough(S, 16, 1);
  ssSetInputPortDirectFeedThrough(S, 17, 1);
  ssSetInputPortDirectFeedThrough(S, 18, 1);
  ssSetInputPortDirectFeedThrough(S, 19, 1);
  ssSetInputPortDirectFeedThrough(S, 20, 1);
  ssSetInputPortDirectFeedThrough(S, 21, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MX_Gtwy_Control_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      42);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,42,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 42);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,42);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 13, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 14, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 15, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 16, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 17, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 18, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 19, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 20, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 21, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,42,22);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,42,6);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=6; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 22; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,42);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3954319107U));
  ssSetChecksum1(S,(1600481096U));
  ssSetChecksum2(S,(1576578738U));
  ssSetChecksum3(S,(2526305771U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c42_MX_Gtwy_Control(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c42_MX_Gtwy_Control(SimStruct *S)
{
  SFc42_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc42_MX_Gtwy_ControlInstanceStruct *)utMalloc(sizeof
    (SFc42_MX_Gtwy_ControlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc42_MX_Gtwy_ControlInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlStart = mdlStart_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c42_MX_Gtwy_Control;
  chartInstance->chartInfo.callGetHoverDataForMsg =
    sf_opaque_get_hover_data_for_msg;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c42_MX_Gtwy_Control(chartInstance);
}

void c42_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c42_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c42_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c42_MX_Gtwy_Control(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c42_MX_Gtwy_Control_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
