/* Include files */

#include "MX_Gtwy_Control_sfun.h"
#include "c105_MX_Gtwy_Control.h"
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
#define CALL_EVENT                     (-1)
#define c105_IN_NO_ACTIVE_CHILD        ((uint8_T)0U)
#define c105_IN_Non_Functional         ((uint8_T)1U)
#define c105_IN_OptionA                ((uint8_T)2U)
#define c105_IN_OptionB                ((uint8_T)3U)
#define c105_IN_OptionC                ((uint8_T)4U)
#define c105_IN_Delay                  ((uint8_T)1U)
#define c105_IN_Enabled                ((uint8_T)2U)
#define c105_IN_INIT_SystemCheck       ((uint8_T)3U)
#define c105_IN_Left_Control_or_Diverter_Fault ((uint8_T)4U)
#define c105_IN_Fault_Mode             ((uint8_T)1U)
#define c105_IN_Mode_None_Aux1         ((uint8_T)2U)
#define c105_IN_Aux_Enabled            ((uint8_T)1U)
#define c105_IN_Mode_Offset_None       ((uint8_T)2U)
#define c105_IN_Mode_Aux2_Aux1         ((uint8_T)1U)
#define c105_IN_Mode_Offset_Aux1       ((uint8_T)2U)
#define c105_IN_Control_Fault          ((uint8_T)1U)
#define c105_IN_Offset_Left            ((uint8_T)2U)
#define c105_IN_Offset_Right           ((uint8_T)3U)
#define c105_b_IN_Mode_Offset_Aux1     ((uint8_T)1U)
#define c105_IN_Mode_Offset_Aux4       ((uint8_T)2U)
#define c105_IN_Mode_None_Offset       ((uint8_T)2U)
#define c105_IN_Mode_Aux4_Aux1         ((uint8_T)1U)
#define c105_IN_Mode_Aux4_Offset       ((uint8_T)2U)
#define c105_IN_Mode_Aux2_Aux4         ((uint8_T)2U)
#define c105_c_IN_Mode_Offset_Aux1     ((uint8_T)3U)
#define c105_b_IN_Mode_Offset_Aux4     ((uint8_T)4U)
#define c105_b_IN_Mode_Aux4_Aux1       ((uint8_T)2U)
#define c105_b_IN_Mode_Aux4_Offset     ((uint8_T)3U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initialize_params_c105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void enable_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void disable_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_update_debugger_state_c105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void set_sim_state_c105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c105_st);
static void c105_set_sim_state_side_effects_c105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void finalize_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void sf_gateway_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void mdl_start_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void initSimStructsc105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_OptionA(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_Left_Control_or_Diverter_Fault
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_exit_internal_Left_Control_or_Diverter_Fault
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_exit_internal_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_enter_internal_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_exit_internal_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c105_OptionB(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_enter_atomic_INIT_SystemCheck
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_b_exit_internal_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_enter_internal_Offset_Left(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_Offset_Left(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_exit_internal_Offset_Left(SFc105_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c105_b_enter_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_b_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_b_exit_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_enter_atomic_Control_Fault(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_enter_internal_Offset_Right
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_Offset_Right(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_exit_internal_Offset_Right(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_c_enter_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_c_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_c_exit_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_OptionC(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_b_enter_atomic_INIT_SystemCheck
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_b_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_c_exit_internal_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_b_enter_internal_Offset_Left
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_b_Offset_Left(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_b_exit_internal_Offset_Left
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_d_enter_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_d_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_d_exit_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_Mode_Offset_Aux4(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_Mode_Offset_Aux1(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_enter_atomic_Mode_Offset_None
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_b_enter_atomic_Control_Fault
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_b_enter_internal_Offset_Right
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_b_Offset_Right(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_b_exit_internal_Offset_Right
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_e_enter_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_e_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c105_e_exit_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c105_Mode_Aux4_Offset(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c105_machineNumber, uint32_T
  c105_chartNumber, uint32_T c105_instanceNumber);
static void c105_DiverterFaultOverrideLeft(SFc105_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c105_DiverterFaultOverrideRight(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static const mxArray *c105_sf_marshallOut(void *chartInstanceVoid, void
  *c105_inData);
static int32_T c105_emlrt_marshallIn(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c105_u, const emlrtMsgIdentifier *c105_parentId);
static void c105_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c105_mxArrayInData, const char_T *c105_varName, void *c105_outData);
static const mxArray *c105_b_sf_marshallOut(void *chartInstanceVoid, void
  *c105_inData);
static uint8_T c105_b_emlrt_marshallIn(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c105_b_tp_Non_Functional, const char_T
  *c105_identifier);
static uint8_T c105_c_emlrt_marshallIn(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c105_u, const emlrtMsgIdentifier *c105_parentId);
static void c105_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c105_mxArrayInData, const char_T *c105_varName, void *c105_outData);
static const mxArray *c105_c_sf_marshallOut(void *chartInstanceVoid, void
  *c105_inData);
static boolean_T c105_d_emlrt_marshallIn(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c105_b_flag_AuxEnableFlash, const char_T
  *c105_identifier);
static boolean_T c105_e_emlrt_marshallIn(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c105_u, const emlrtMsgIdentifier *c105_parentId);
static void c105_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c105_mxArrayInData, const char_T *c105_varName, void *c105_outData);
static const mxArray *c105_f_emlrt_marshallIn
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray
   *c105_b_setSimStateSideEffectsInfo, const char_T *c105_identifier);
static const mxArray *c105_g_emlrt_marshallIn
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c105_u,
   const emlrtMsgIdentifier *c105_parentId);
static const mxArray *sf_get_hover_data_for_msg
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c105_ssid);
static void c105_init_sf_message_store_memory
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance);
static uint8_T c105__u8_s32_(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c105_b, uint32_T c105_ssid_src_loc, int32_T c105_offset_src_loc,
  int32_T c105_length_src_loc);
static uint8_T c105_get_ee_ControlMode(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c105_elementIndex);
static void c105_set_ee_ControlMode(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c105_elementIndex, uint8_T c105_elementValue);
static uint8_T *c105_access_ee_ControlMode(SFc105_MX_Gtwy_ControlInstanceStruct *
  chartInstance, uint32_T c105_rdOnly);
static uint8_T c105_get_state_Buzzer(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c105_elementIndex);
static void c105_set_state_Buzzer(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c105_elementIndex, uint8_T c105_elementValue);
static uint8_T *c105_access_state_Buzzer(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c105_rdOnly);
static void init_dsm_address_info(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc105_MX_Gtwy_Control(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c105_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c105_doSetSimStateSideEffects = 0U;
  chartInstance->c105_setSimStateSideEffectsInfo = NULL;
  chartInstance->c105_tp_Non_Functional = 0U;
  chartInstance->c105_is_OptionA = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_tp_OptionA = 0U;
  chartInstance->c105_tp_Delay = 0U;
  chartInstance->c105_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_tp_Enabled = 0U;
  chartInstance->c105_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_tp_Aux_Enabled = 0U;
  chartInstance->c105_tp_Mode_Aux2_Aux1 = 0U;
  chartInstance->c105_tp_Mode_Offset_Aux1 = 0U;
  chartInstance->c105_tp_Mode_Offset_None = 0U;
  chartInstance->c105_temporalCounter_i1 = 0U;
  chartInstance->c105_tp_INIT_SystemCheck = 0U;
  chartInstance->c105_is_Left_Control_or_Diverter_Fault =
    c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_tp_Left_Control_or_Diverter_Fault = 0U;
  chartInstance->c105_tp_Fault_Mode = 0U;
  chartInstance->c105_tp_Mode_None_Aux1 = 0U;
  chartInstance->c105_is_OptionB = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_tp_OptionB = 0U;
  chartInstance->c105_b_tp_Delay = 0U;
  chartInstance->c105_temporalCounter_i1 = 0U;
  chartInstance->c105_b_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_b_tp_Enabled = 0U;
  chartInstance->c105_tp_Control_Fault = 0U;
  chartInstance->c105_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_tp_Offset_Left = 0U;
  chartInstance->c105_b_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_b_tp_Aux_Enabled = 0U;
  chartInstance->c105_b_tp_Mode_Offset_Aux1 = 0U;
  chartInstance->c105_tp_Mode_Offset_Aux4 = 0U;
  chartInstance->c105_b_tp_Mode_Offset_None = 0U;
  chartInstance->c105_temporalCounter_i1 = 0U;
  chartInstance->c105_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_tp_Offset_Right = 0U;
  chartInstance->c105_c_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_c_tp_Aux_Enabled = 0U;
  chartInstance->c105_tp_Mode_Aux4_Aux1 = 0U;
  chartInstance->c105_tp_Mode_Aux4_Offset = 0U;
  chartInstance->c105_temporalCounter_i1 = 0U;
  chartInstance->c105_tp_Mode_None_Offset = 0U;
  chartInstance->c105_temporalCounter_i1 = 0U;
  chartInstance->c105_b_tp_INIT_SystemCheck = 0U;
  chartInstance->c105_is_OptionC = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_tp_OptionC = 0U;
  chartInstance->c105_c_tp_Delay = 0U;
  chartInstance->c105_temporalCounter_i1 = 0U;
  chartInstance->c105_c_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_c_tp_Enabled = 0U;
  chartInstance->c105_b_tp_Control_Fault = 0U;
  chartInstance->c105_b_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_b_tp_Offset_Left = 0U;
  chartInstance->c105_d_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_d_tp_Aux_Enabled = 0U;
  chartInstance->c105_b_tp_Mode_Aux2_Aux1 = 0U;
  chartInstance->c105_tp_Mode_Aux2_Aux4 = 0U;
  chartInstance->c105_c_tp_Mode_Offset_Aux1 = 0U;
  chartInstance->c105_b_tp_Mode_Offset_Aux4 = 0U;
  chartInstance->c105_c_tp_Mode_Offset_None = 0U;
  chartInstance->c105_temporalCounter_i1 = 0U;
  chartInstance->c105_b_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_b_tp_Offset_Right = 0U;
  chartInstance->c105_e_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_e_tp_Aux_Enabled = 0U;
  chartInstance->c105_c_tp_Mode_Aux2_Aux1 = 0U;
  chartInstance->c105_temporalCounter_i1 = 0U;
  chartInstance->c105_b_tp_Mode_Aux4_Aux1 = 0U;
  chartInstance->c105_b_tp_Mode_Aux4_Offset = 0U;
  chartInstance->c105_temporalCounter_i1 = 0U;
  chartInstance->c105_b_tp_Mode_None_Offset = 0U;
  chartInstance->c105_temporalCounter_i1 = 0U;
  chartInstance->c105_c_tp_INIT_SystemCheck = 0U;
  chartInstance->c105_is_active_c105_MX_Gtwy_Control = 0U;
  chartInstance->c105_is_c105_MX_Gtwy_Control = c105_IN_NO_ACTIVE_CHILD;
  chartInstance->c105_stored_ControlMode = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode, 0U);
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c105_flag_AuxEnableFlash = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash, 15U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c105_mode_LeftControl = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *chartInstance->c105_mode_RightControl = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 4) != 0)) {
    *chartInstance->c105_check_LeftNeutral = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 5) != 0)) {
    *chartInstance->c105_check_RightNeutral = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 6) != 0)) {
    *chartInstance->c105_aux_inhibit = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 7) != 0)) {
    *chartInstance->c105_display_request = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
  }
}

static void initialize_params_c105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  real_T c105_d0;
  real_T c105_d1;
  real_T c105_d2;
  real_T c105_d3;
  real_T c105_d4;
  real_T c105_d5;
  real_T c105_d6;
  real_T c105_d7;
  real_T c105_d8;
  real_T c105_d9;
  real_T c105_d10;
  real_T c105_d11;
  real_T c105_d12;
  real_T c105_d13;
  real_T c105_d14;
  real_T c105_d15;
  real_T c105_d16;
  real_T c105_d17;
  real_T c105_d18;
  real_T c105_d19;
  real_T c105_d20;
  real_T c105_d21;
  real_T c105_d22;
  real_T c105_d23;
  real_T c105_d24;
  real_T c105_d25;
  real_T c105_d26;
  real_T c105_d27;
  real_T c105_d28;
  real_T c105_d29;
  real_T c105_d30;
  real_T c105_d31;
  real_T c105_d32;
  real_T c105_d33;
  real_T c105_d34;
  real_T c105_d35;
  sf_mex_import_named("MODE_LEFT_NONE", sf_mex_get_sfun_param(chartInstance->S,
    19, 0), &c105_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_MODE_LEFT_NONE = (uint8_T)c105_d0;
  sf_mex_import_named("MODE_LEFT_OFFSET", sf_mex_get_sfun_param(chartInstance->S,
    20, 0), &c105_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_MODE_LEFT_OFFSET = (uint8_T)c105_d1;
  sf_mex_import_named("MODE_LEFT_AUX2", sf_mex_get_sfun_param(chartInstance->S,
    17, 0), &c105_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_MODE_LEFT_AUX2 = (uint8_T)c105_d2;
  sf_mex_import_named("MODE_LEFT_AUX4", sf_mex_get_sfun_param(chartInstance->S,
    18, 0), &c105_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_MODE_LEFT_AUX4 = (uint8_T)c105_d3;
  sf_mex_import_named("DOUBLE_SHORT_BEEP", sf_mex_get_sfun_param
                      (chartInstance->S, 4, 0), &c105_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_DOUBLE_SHORT_BEEP = (uint8_T)c105_d4;
  sf_mex_import_named("SINGLE_SHORT_BEEP", sf_mex_get_sfun_param
                      (chartInstance->S, 33, 0), &c105_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_SINGLE_SHORT_BEEP = (uint8_T)c105_d5;
  sf_mex_import_named("NORMAL", sf_mex_get_sfun_param(chartInstance->S, 26, 0),
                      &c105_d6, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_NORMAL = (uint8_T)c105_d6;
  sf_mex_import_named("CD_EMEA_CONTROLS_OPTION_A", sf_mex_get_sfun_param
                      (chartInstance->S, 1, 0), &c105_d7, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_CD_EMEA_CONTROLS_OPTION_A = (uint8_T)c105_d7;
  sf_mex_import_named("CD_EMEA_CONTROLS_OPTION_B", sf_mex_get_sfun_param
                      (chartInstance->S, 2, 0), &c105_d8, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_CD_EMEA_CONTROLS_OPTION_B = (uint8_T)c105_d8;
  sf_mex_import_named("CD_EMEA_CONTROLS_OPTION_C", sf_mex_get_sfun_param
                      (chartInstance->S, 3, 0), &c105_d9, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_CD_EMEA_CONTROLS_OPTION_C = (uint8_T)c105_d9;
  sf_mex_import_named("NON_FUNCTIONAL", sf_mex_get_sfun_param(chartInstance->S,
    25, 0), &c105_d10, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_NON_FUNCTIONAL = (uint8_T)c105_d10;
  sf_mex_import_named("OFFSET_SELECT_LEFT", sf_mex_get_sfun_param
                      (chartInstance->S, 28, 0), &c105_d11, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_OFFSET_SELECT_LEFT = (uint8_T)c105_d11;
  sf_mex_import_named("OFFSET_SELECT_RIGHT", sf_mex_get_sfun_param
                      (chartInstance->S, 29, 0), &c105_d12, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_OFFSET_SELECT_RIGHT = (uint8_T)c105_d12;
  sf_mex_import_named("SINGLE_MEDIUM_BEEP", sf_mex_get_sfun_param
                      (chartInstance->S, 32, 0), &c105_d13, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_SINGLE_MEDIUM_BEEP = (uint8_T)c105_d13;
  sf_mex_import_named("TRIPLE_SHORT_BEEP", sf_mex_get_sfun_param
                      (chartInstance->S, 35, 0), &c105_d14, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_TRIPLE_SHORT_BEEP = (uint8_T)c105_d14;
  sf_mex_import_named("INACTIVE", sf_mex_get_sfun_param(chartInstance->S, 16, 0),
                      &c105_d15, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_INACTIVE = (uint8_T)c105_d15;
  sf_mex_import_named("MODE_RIGHT_AUX1", sf_mex_get_sfun_param(chartInstance->S,
    21, 0), &c105_d16, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_MODE_RIGHT_AUX1 = (uint8_T)c105_d16;
  sf_mex_import_named("MODE_RIGHT_AUX4", sf_mex_get_sfun_param(chartInstance->S,
    22, 0), &c105_d17, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_MODE_RIGHT_AUX4 = (uint8_T)c105_d17;
  sf_mex_import_named("MODE_RIGHT_NONE", sf_mex_get_sfun_param(chartInstance->S,
    23, 0), &c105_d18, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_MODE_RIGHT_NONE = (uint8_T)c105_d18;
  sf_mex_import_named("MODE_RIGHT_OFFSET", sf_mex_get_sfun_param
                      (chartInstance->S, 24, 0), &c105_d19, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_MODE_RIGHT_OFFSET = (uint8_T)c105_d19;
  sf_mex_import_named("ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c105_d20, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_ACTIVE = (uint8_T)c105_d20;
  sf_mex_import_named("ENGINE_CRANKING", sf_mex_get_sfun_param(chartInstance->S,
    15, 0), &c105_d21, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_ENGINE_CRANKING = (uint8_T)c105_d21;
  sf_mex_import_named("SYS_NORMAL", sf_mex_get_sfun_param(chartInstance->S, 34,
    0), &c105_d22, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_SYS_NORMAL = (uint8_T)c105_d22;
  sf_mex_import_named("OORH", sf_mex_get_sfun_param(chartInstance->S, 30, 0),
                      &c105_d23, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_OORH = (uint8_T)c105_d23;
  sf_mex_import_named("OORL", sf_mex_get_sfun_param(chartInstance->S, 31, 0),
                      &c105_d24, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_OORL = (uint8_T)c105_d24;
  sf_mex_import_named("NO_COMMUNICATION", sf_mex_get_sfun_param(chartInstance->S,
    27, 0), &c105_d25, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_NO_COMMUNICATION = (uint8_T)c105_d25;
  sf_mex_import_named("EE_RT_A2_A1", sf_mex_get_sfun_param(chartInstance->S, 11,
    0), &c105_d26, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_EE_RT_A2_A1 = (uint8_T)c105_d26;
  sf_mex_import_named("EE_LT_A2_A4", sf_mex_get_sfun_param(chartInstance->S, 6,
    0), &c105_d27, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_EE_LT_A2_A4 = (uint8_T)c105_d27;
  sf_mex_import_named("EE_RT_A4_A1", sf_mex_get_sfun_param(chartInstance->S, 12,
    0), &c105_d28, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_EE_RT_A4_A1 = (uint8_T)c105_d28;
  sf_mex_import_named("EE_RT_A4_OF", sf_mex_get_sfun_param(chartInstance->S, 13,
    0), &c105_d29, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_EE_RT_A4_OF = (uint8_T)c105_d29;
  sf_mex_import_named("EE_NA_NA", sf_mex_get_sfun_param(chartInstance->S, 10, 0),
                      &c105_d30, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_EE_NA_NA = (uint8_T)c105_d30;
  sf_mex_import_named("EE_RT_NA_OF", sf_mex_get_sfun_param(chartInstance->S, 14,
    0), &c105_d31, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_EE_RT_NA_OF = (uint8_T)c105_d31;
  sf_mex_import_named("EE_LT_OF_A1", sf_mex_get_sfun_param(chartInstance->S, 7,
    0), &c105_d32, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_EE_LT_OF_A1 = (uint8_T)c105_d32;
  sf_mex_import_named("EE_LT_OF_A4", sf_mex_get_sfun_param(chartInstance->S, 8,
    0), &c105_d33, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_EE_LT_OF_A4 = (uint8_T)c105_d33;
  sf_mex_import_named("EE_LT_OF_NA", sf_mex_get_sfun_param(chartInstance->S, 9,
    0), &c105_d34, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_EE_LT_OF_NA = (uint8_T)c105_d34;
  sf_mex_import_named("EE_LT_A2_A1", sf_mex_get_sfun_param(chartInstance->S, 5,
    0), &c105_d35, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c105_EE_LT_A2_A1 = (uint8_T)c105_d35;
}

static void enable_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c105_update_debugger_state_c105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  uint32_T c105_prevAniVal;
  c105_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c105_is_active_c105_MX_Gtwy_Control == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 101U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_c105_MX_Gtwy_Control == c105_IN_Non_Functional) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_c105_MX_Gtwy_Control == c105_IN_OptionA) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_OptionA == c105_IN_Left_Control_or_Diverter_Fault)
  {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_Left_Control_or_Diverter_Fault ==
      c105_IN_Mode_None_Aux1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_Left_Control_or_Diverter_Fault ==
      c105_IN_Fault_Mode) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_OptionA == c105_IN_INIT_SystemCheck) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_OptionA == c105_IN_Delay) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_OptionA == c105_IN_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_Enabled == c105_IN_Aux_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_Aux_Enabled == c105_IN_Mode_Aux2_Aux1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_Aux_Enabled == c105_IN_Mode_Offset_Aux1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_Enabled == c105_IN_Mode_Offset_None) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_c105_MX_Gtwy_Control == c105_IN_OptionB) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_OptionB == c105_IN_INIT_SystemCheck) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_OptionB == c105_IN_Delay) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_OptionB == c105_IN_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_b_is_Enabled == c105_IN_Offset_Left) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_Offset_Left == c105_IN_Aux_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_b_is_Aux_Enabled == c105_IN_Mode_Offset_Aux4) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_b_is_Aux_Enabled == c105_b_IN_Mode_Offset_Aux1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_Offset_Left == c105_IN_Mode_Offset_None) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_b_is_Enabled == c105_IN_Control_Fault) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_b_is_Enabled == c105_IN_Offset_Right) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_Offset_Right == c105_IN_Aux_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_c_is_Aux_Enabled == c105_IN_Mode_Aux4_Aux1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_c_is_Aux_Enabled == c105_IN_Mode_Aux4_Offset) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_Offset_Right == c105_IN_Mode_None_Offset) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_c105_MX_Gtwy_Control == c105_IN_OptionC) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_OptionC == c105_IN_INIT_SystemCheck) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 46U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_OptionC == c105_IN_Delay) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 28U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_is_OptionC == c105_IN_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_c_is_Enabled == c105_IN_Offset_Left) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_b_is_Offset_Left == c105_IN_Aux_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_d_is_Aux_Enabled == c105_b_IN_Mode_Offset_Aux4) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_d_is_Aux_Enabled == c105_c_IN_Mode_Offset_Aux1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_d_is_Aux_Enabled == c105_IN_Mode_Aux2_Aux4) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_d_is_Aux_Enabled == c105_IN_Mode_Aux2_Aux1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_b_is_Offset_Left == c105_IN_Mode_Offset_None) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_c_is_Enabled == c105_IN_Control_Fault) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_c_is_Enabled == c105_IN_Offset_Right) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_b_is_Offset_Right == c105_IN_Aux_Enabled) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_e_is_Aux_Enabled == c105_b_IN_Mode_Aux4_Aux1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_e_is_Aux_Enabled == c105_b_IN_Mode_Aux4_Offset) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_e_is_Aux_Enabled == c105_IN_Mode_Aux2_Aux1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
  }

  if (chartInstance->c105_b_is_Offset_Right == c105_IN_Mode_None_Offset) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 45U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 45U, chartInstance->c105_sfEvent);
  }

  _SFD_SET_ANIMATION(c105_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  const mxArray *c105_st;
  const mxArray *c105_y = NULL;
  boolean_T c105_hoistedGlobal;
  const mxArray *c105_b_y = NULL;
  boolean_T c105_b_hoistedGlobal;
  const mxArray *c105_c_y = NULL;
  boolean_T c105_c_hoistedGlobal;
  const mxArray *c105_d_y = NULL;
  boolean_T c105_d_hoistedGlobal;
  const mxArray *c105_e_y = NULL;
  boolean_T c105_e_hoistedGlobal;
  const mxArray *c105_f_y = NULL;
  uint8_T c105_f_hoistedGlobal;
  const mxArray *c105_g_y = NULL;
  uint8_T c105_g_hoistedGlobal;
  const mxArray *c105_h_y = NULL;
  uint8_T c105_h_hoistedGlobal;
  const mxArray *c105_i_y = NULL;
  uint8_T c105_i_hoistedGlobal;
  const mxArray *c105_j_y = NULL;
  uint8_T c105_j_hoistedGlobal;
  const mxArray *c105_k_y = NULL;
  uint8_T c105_k_hoistedGlobal;
  const mxArray *c105_l_y = NULL;
  uint8_T c105_l_hoistedGlobal;
  const mxArray *c105_m_y = NULL;
  uint8_T c105_m_hoistedGlobal;
  const mxArray *c105_n_y = NULL;
  uint8_T c105_n_hoistedGlobal;
  const mxArray *c105_o_y = NULL;
  uint8_T c105_o_hoistedGlobal;
  const mxArray *c105_p_y = NULL;
  uint8_T c105_p_hoistedGlobal;
  const mxArray *c105_q_y = NULL;
  uint8_T c105_q_hoistedGlobal;
  const mxArray *c105_r_y = NULL;
  uint8_T c105_r_hoistedGlobal;
  const mxArray *c105_s_y = NULL;
  uint8_T c105_s_hoistedGlobal;
  const mxArray *c105_t_y = NULL;
  uint8_T c105_t_hoistedGlobal;
  const mxArray *c105_u_y = NULL;
  uint8_T c105_u_hoistedGlobal;
  const mxArray *c105_v_y = NULL;
  uint8_T c105_v_hoistedGlobal;
  const mxArray *c105_w_y = NULL;
  uint8_T c105_w_hoistedGlobal;
  const mxArray *c105_x_y = NULL;
  uint8_T c105_x_hoistedGlobal;
  const mxArray *c105_y_y = NULL;
  uint8_T c105_y_hoistedGlobal;
  const mxArray *c105_ab_y = NULL;
  uint8_T c105_ab_hoistedGlobal;
  const mxArray *c105_bb_y = NULL;
  uint8_T c105_bb_hoistedGlobal;
  const mxArray *c105_cb_y = NULL;
  c105_st = NULL;
  c105_st = NULL;
  c105_y = NULL;
  sf_mex_assign(&c105_y, sf_mex_createcellmatrix(27, 1), false);
  c105_hoistedGlobal = *chartInstance->c105_aux_inhibit;
  c105_b_y = NULL;
  sf_mex_assign(&c105_b_y, sf_mex_create("y", &c105_hoistedGlobal, 11, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 0, c105_b_y);
  c105_b_hoistedGlobal = *chartInstance->c105_check_LeftNeutral;
  c105_c_y = NULL;
  sf_mex_assign(&c105_c_y, sf_mex_create("y", &c105_b_hoistedGlobal, 11, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 1, c105_c_y);
  c105_c_hoistedGlobal = *chartInstance->c105_check_RightNeutral;
  c105_d_y = NULL;
  sf_mex_assign(&c105_d_y, sf_mex_create("y", &c105_c_hoistedGlobal, 11, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 2, c105_d_y);
  c105_d_hoistedGlobal = *chartInstance->c105_display_request;
  c105_e_y = NULL;
  sf_mex_assign(&c105_e_y, sf_mex_create("y", &c105_d_hoistedGlobal, 11, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 3, c105_e_y);
  c105_e_hoistedGlobal = *chartInstance->c105_flag_AuxEnableFlash;
  c105_f_y = NULL;
  sf_mex_assign(&c105_f_y, sf_mex_create("y", &c105_e_hoistedGlobal, 11, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 4, c105_f_y);
  c105_f_hoistedGlobal = *chartInstance->c105_mode_LeftControl;
  c105_g_y = NULL;
  sf_mex_assign(&c105_g_y, sf_mex_create("y", &c105_f_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 5, c105_g_y);
  c105_g_hoistedGlobal = *chartInstance->c105_mode_RightControl;
  c105_h_y = NULL;
  sf_mex_assign(&c105_h_y, sf_mex_create("y", &c105_g_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 6, c105_h_y);
  c105_h_hoistedGlobal = chartInstance->c105_stored_ControlMode;
  c105_i_y = NULL;
  sf_mex_assign(&c105_i_y, sf_mex_create("y", &c105_h_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 7, c105_i_y);
  c105_i_hoistedGlobal = chartInstance->c105_is_active_c105_MX_Gtwy_Control;
  c105_j_y = NULL;
  sf_mex_assign(&c105_j_y, sf_mex_create("y", &c105_i_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 8, c105_j_y);
  c105_j_hoistedGlobal = chartInstance->c105_is_c105_MX_Gtwy_Control;
  c105_k_y = NULL;
  sf_mex_assign(&c105_k_y, sf_mex_create("y", &c105_j_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 9, c105_k_y);
  c105_k_hoistedGlobal = chartInstance->c105_is_OptionA;
  c105_l_y = NULL;
  sf_mex_assign(&c105_l_y, sf_mex_create("y", &c105_k_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 10, c105_l_y);
  c105_l_hoistedGlobal = chartInstance->c105_is_OptionC;
  c105_m_y = NULL;
  sf_mex_assign(&c105_m_y, sf_mex_create("y", &c105_l_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 11, c105_m_y);
  c105_m_hoistedGlobal = chartInstance->c105_b_is_Offset_Left;
  c105_n_y = NULL;
  sf_mex_assign(&c105_n_y, sf_mex_create("y", &c105_m_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 12, c105_n_y);
  c105_n_hoistedGlobal = chartInstance->c105_b_is_Offset_Right;
  c105_o_y = NULL;
  sf_mex_assign(&c105_o_y, sf_mex_create("y", &c105_n_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 13, c105_o_y);
  c105_o_hoistedGlobal = chartInstance->c105_d_is_Aux_Enabled;
  c105_p_y = NULL;
  sf_mex_assign(&c105_p_y, sf_mex_create("y", &c105_o_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 14, c105_p_y);
  c105_p_hoistedGlobal = chartInstance->c105_e_is_Aux_Enabled;
  c105_q_y = NULL;
  sf_mex_assign(&c105_q_y, sf_mex_create("y", &c105_p_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 15, c105_q_y);
  c105_q_hoistedGlobal = chartInstance->c105_is_Enabled;
  c105_r_y = NULL;
  sf_mex_assign(&c105_r_y, sf_mex_create("y", &c105_q_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 16, c105_r_y);
  c105_r_hoistedGlobal = chartInstance->c105_c_is_Enabled;
  c105_s_y = NULL;
  sf_mex_assign(&c105_s_y, sf_mex_create("y", &c105_r_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 17, c105_s_y);
  c105_s_hoistedGlobal = chartInstance->c105_is_Left_Control_or_Diverter_Fault;
  c105_t_y = NULL;
  sf_mex_assign(&c105_t_y, sf_mex_create("y", &c105_s_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 18, c105_t_y);
  c105_t_hoistedGlobal = chartInstance->c105_is_Aux_Enabled;
  c105_u_y = NULL;
  sf_mex_assign(&c105_u_y, sf_mex_create("y", &c105_t_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 19, c105_u_y);
  c105_u_hoistedGlobal = chartInstance->c105_is_OptionB;
  c105_v_y = NULL;
  sf_mex_assign(&c105_v_y, sf_mex_create("y", &c105_u_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 20, c105_v_y);
  c105_v_hoistedGlobal = chartInstance->c105_b_is_Enabled;
  c105_w_y = NULL;
  sf_mex_assign(&c105_w_y, sf_mex_create("y", &c105_v_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 21, c105_w_y);
  c105_w_hoistedGlobal = chartInstance->c105_is_Offset_Left;
  c105_x_y = NULL;
  sf_mex_assign(&c105_x_y, sf_mex_create("y", &c105_w_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 22, c105_x_y);
  c105_x_hoistedGlobal = chartInstance->c105_b_is_Aux_Enabled;
  c105_y_y = NULL;
  sf_mex_assign(&c105_y_y, sf_mex_create("y", &c105_x_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 23, c105_y_y);
  c105_y_hoistedGlobal = chartInstance->c105_is_Offset_Right;
  c105_ab_y = NULL;
  sf_mex_assign(&c105_ab_y, sf_mex_create("y", &c105_y_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 24, c105_ab_y);
  c105_ab_hoistedGlobal = chartInstance->c105_c_is_Aux_Enabled;
  c105_bb_y = NULL;
  sf_mex_assign(&c105_bb_y, sf_mex_create("y", &c105_ab_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 25, c105_bb_y);
  c105_bb_hoistedGlobal = chartInstance->c105_temporalCounter_i1;
  c105_cb_y = NULL;
  sf_mex_assign(&c105_cb_y, sf_mex_create("y", &c105_bb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c105_y, 26, c105_cb_y);
  sf_mex_assign(&c105_st, c105_y, false);
  return c105_st;
}

static void set_sim_state_c105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c105_st)
{
  const mxArray *c105_u;
  c105_u = sf_mex_dup(c105_st);
  *chartInstance->c105_aux_inhibit = c105_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 0)), "aux_inhibit");
  *chartInstance->c105_check_LeftNeutral = c105_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 1)), "check_LeftNeutral");
  *chartInstance->c105_check_RightNeutral = c105_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c105_u, 2)), "check_RightNeutral");
  *chartInstance->c105_display_request = c105_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 3)), "display_request");
  *chartInstance->c105_flag_AuxEnableFlash = c105_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c105_u, 4)), "flag_AuxEnableFlash");
  *chartInstance->c105_mode_LeftControl = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 5)), "mode_LeftControl");
  *chartInstance->c105_mode_RightControl = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 6)), "mode_RightControl");
  chartInstance->c105_stored_ControlMode = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 7)), "stored_ControlMode");
  chartInstance->c105_is_active_c105_MX_Gtwy_Control = c105_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c105_u, 8)),
     "is_active_c105_MX_Gtwy_Control");
  chartInstance->c105_is_c105_MX_Gtwy_Control = c105_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c105_u, 9)),
     "is_c105_MX_Gtwy_Control");
  chartInstance->c105_is_OptionA = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 10)), "is_OptionA");
  chartInstance->c105_is_OptionC = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 11)), "is_OptionC");
  chartInstance->c105_b_is_Offset_Left = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 12)), "is_Offset_Left");
  chartInstance->c105_b_is_Offset_Right = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 13)), "is_Offset_Right");
  chartInstance->c105_d_is_Aux_Enabled = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 14)), "is_Aux_Enabled");
  chartInstance->c105_e_is_Aux_Enabled = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 15)), "is_Aux_Enabled");
  chartInstance->c105_is_Enabled = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 16)), "is_Enabled");
  chartInstance->c105_c_is_Enabled = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 17)), "is_Enabled");
  chartInstance->c105_is_Left_Control_or_Diverter_Fault =
    c105_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c105_u, 18)),
    "is_Left_Control_or_Diverter_Fault");
  chartInstance->c105_is_Aux_Enabled = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 19)), "is_Aux_Enabled");
  chartInstance->c105_is_OptionB = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 20)), "is_OptionB");
  chartInstance->c105_b_is_Enabled = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 21)), "is_Enabled");
  chartInstance->c105_is_Offset_Left = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 22)), "is_Offset_Left");
  chartInstance->c105_b_is_Aux_Enabled = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 23)), "is_Aux_Enabled");
  chartInstance->c105_is_Offset_Right = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 24)), "is_Offset_Right");
  chartInstance->c105_c_is_Aux_Enabled = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 25)), "is_Aux_Enabled");
  chartInstance->c105_temporalCounter_i1 = c105_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c105_u, 26)), "temporalCounter_i1");
  sf_mex_assign(&chartInstance->c105_setSimStateSideEffectsInfo,
                c105_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c105_u, 27)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c105_u);
  chartInstance->c105_doSetSimStateSideEffects = 1U;
  c105_update_debugger_state_c105_MX_Gtwy_Control(chartInstance);
  sf_mex_destroy(&c105_st);
}

static void c105_set_sim_state_side_effects_c105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  if (chartInstance->c105_doSetSimStateSideEffects != 0) {
    chartInstance->c105_tp_Non_Functional = (uint8_T)
      (chartInstance->c105_is_c105_MX_Gtwy_Control == c105_IN_Non_Functional);
    chartInstance->c105_tp_OptionA = (uint8_T)
      (chartInstance->c105_is_c105_MX_Gtwy_Control == c105_IN_OptionA);
    chartInstance->c105_tp_Delay = (uint8_T)(chartInstance->c105_is_OptionA ==
      c105_IN_Delay);
    chartInstance->c105_tp_Enabled = (uint8_T)(chartInstance->c105_is_OptionA ==
      c105_IN_Enabled);
    chartInstance->c105_tp_Aux_Enabled = (uint8_T)
      (chartInstance->c105_is_Enabled == c105_IN_Aux_Enabled);
    chartInstance->c105_tp_Mode_Aux2_Aux1 = (uint8_T)
      (chartInstance->c105_is_Aux_Enabled == c105_IN_Mode_Aux2_Aux1);
    chartInstance->c105_tp_Mode_Offset_Aux1 = (uint8_T)
      (chartInstance->c105_is_Aux_Enabled == c105_IN_Mode_Offset_Aux1);
    if (chartInstance->c105_is_Enabled == c105_IN_Mode_Offset_None) {
      chartInstance->c105_tp_Mode_Offset_None = 1U;
      if (sf_mex_sub(chartInstance->c105_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 9) == 0.0) {
        chartInstance->c105_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c105_tp_Mode_Offset_None = 0U;
    }

    chartInstance->c105_tp_INIT_SystemCheck = (uint8_T)
      (chartInstance->c105_is_OptionA == c105_IN_INIT_SystemCheck);
    chartInstance->c105_tp_Left_Control_or_Diverter_Fault = (uint8_T)
      (chartInstance->c105_is_OptionA == c105_IN_Left_Control_or_Diverter_Fault);
    chartInstance->c105_tp_Fault_Mode = (uint8_T)
      (chartInstance->c105_is_Left_Control_or_Diverter_Fault ==
       c105_IN_Fault_Mode);
    chartInstance->c105_tp_Mode_None_Aux1 = (uint8_T)
      (chartInstance->c105_is_Left_Control_or_Diverter_Fault ==
       c105_IN_Mode_None_Aux1);
    chartInstance->c105_tp_OptionB = (uint8_T)
      (chartInstance->c105_is_c105_MX_Gtwy_Control == c105_IN_OptionB);
    if (chartInstance->c105_is_OptionB == c105_IN_Delay) {
      chartInstance->c105_b_tp_Delay = 1U;
      if (sf_mex_sub(chartInstance->c105_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 15) == 0.0) {
        chartInstance->c105_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c105_b_tp_Delay = 0U;
    }

    chartInstance->c105_b_tp_Enabled = (uint8_T)(chartInstance->c105_is_OptionB ==
      c105_IN_Enabled);
    chartInstance->c105_tp_Control_Fault = (uint8_T)
      (chartInstance->c105_b_is_Enabled == c105_IN_Control_Fault);
    chartInstance->c105_tp_Offset_Left = (uint8_T)
      (chartInstance->c105_b_is_Enabled == c105_IN_Offset_Left);
    chartInstance->c105_b_tp_Aux_Enabled = (uint8_T)
      (chartInstance->c105_is_Offset_Left == c105_IN_Aux_Enabled);
    chartInstance->c105_b_tp_Mode_Offset_Aux1 = (uint8_T)
      (chartInstance->c105_b_is_Aux_Enabled == c105_b_IN_Mode_Offset_Aux1);
    chartInstance->c105_tp_Mode_Offset_Aux4 = (uint8_T)
      (chartInstance->c105_b_is_Aux_Enabled == c105_IN_Mode_Offset_Aux4);
    if (chartInstance->c105_is_Offset_Left == c105_IN_Mode_Offset_None) {
      chartInstance->c105_b_tp_Mode_Offset_None = 1U;
      if (sf_mex_sub(chartInstance->c105_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 22) == 0.0) {
        chartInstance->c105_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c105_b_tp_Mode_Offset_None = 0U;
    }

    chartInstance->c105_tp_Offset_Right = (uint8_T)
      (chartInstance->c105_b_is_Enabled == c105_IN_Offset_Right);
    chartInstance->c105_c_tp_Aux_Enabled = (uint8_T)
      (chartInstance->c105_is_Offset_Right == c105_IN_Aux_Enabled);
    chartInstance->c105_tp_Mode_Aux4_Aux1 = (uint8_T)
      (chartInstance->c105_c_is_Aux_Enabled == c105_IN_Mode_Aux4_Aux1);
    if (chartInstance->c105_c_is_Aux_Enabled == c105_IN_Mode_Aux4_Offset) {
      chartInstance->c105_tp_Mode_Aux4_Offset = 1U;
      if (sf_mex_sub(chartInstance->c105_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 26) == 0.0) {
        chartInstance->c105_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c105_tp_Mode_Aux4_Offset = 0U;
    }

    if (chartInstance->c105_is_Offset_Right == c105_IN_Mode_None_Offset) {
      chartInstance->c105_tp_Mode_None_Offset = 1U;
      if (sf_mex_sub(chartInstance->c105_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 27) == 0.0) {
        chartInstance->c105_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c105_tp_Mode_None_Offset = 0U;
    }

    chartInstance->c105_b_tp_INIT_SystemCheck = (uint8_T)
      (chartInstance->c105_is_OptionB == c105_IN_INIT_SystemCheck);
    chartInstance->c105_tp_OptionC = (uint8_T)
      (chartInstance->c105_is_c105_MX_Gtwy_Control == c105_IN_OptionC);
    if (chartInstance->c105_is_OptionC == c105_IN_Delay) {
      chartInstance->c105_c_tp_Delay = 1U;
      if (sf_mex_sub(chartInstance->c105_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 30) == 0.0) {
        chartInstance->c105_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c105_c_tp_Delay = 0U;
    }

    chartInstance->c105_c_tp_Enabled = (uint8_T)(chartInstance->c105_is_OptionC ==
      c105_IN_Enabled);
    chartInstance->c105_b_tp_Control_Fault = (uint8_T)
      (chartInstance->c105_c_is_Enabled == c105_IN_Control_Fault);
    chartInstance->c105_b_tp_Offset_Left = (uint8_T)
      (chartInstance->c105_c_is_Enabled == c105_IN_Offset_Left);
    chartInstance->c105_d_tp_Aux_Enabled = (uint8_T)
      (chartInstance->c105_b_is_Offset_Left == c105_IN_Aux_Enabled);
    chartInstance->c105_b_tp_Mode_Aux2_Aux1 = (uint8_T)
      (chartInstance->c105_d_is_Aux_Enabled == c105_IN_Mode_Aux2_Aux1);
    chartInstance->c105_tp_Mode_Aux2_Aux4 = (uint8_T)
      (chartInstance->c105_d_is_Aux_Enabled == c105_IN_Mode_Aux2_Aux4);
    chartInstance->c105_c_tp_Mode_Offset_Aux1 = (uint8_T)
      (chartInstance->c105_d_is_Aux_Enabled == c105_c_IN_Mode_Offset_Aux1);
    chartInstance->c105_b_tp_Mode_Offset_Aux4 = (uint8_T)
      (chartInstance->c105_d_is_Aux_Enabled == c105_b_IN_Mode_Offset_Aux4);
    if (chartInstance->c105_b_is_Offset_Left == c105_IN_Mode_Offset_None) {
      chartInstance->c105_c_tp_Mode_Offset_None = 1U;
      if (sf_mex_sub(chartInstance->c105_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 39) == 0.0) {
        chartInstance->c105_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c105_c_tp_Mode_Offset_None = 0U;
    }

    chartInstance->c105_b_tp_Offset_Right = (uint8_T)
      (chartInstance->c105_c_is_Enabled == c105_IN_Offset_Right);
    chartInstance->c105_e_tp_Aux_Enabled = (uint8_T)
      (chartInstance->c105_b_is_Offset_Right == c105_IN_Aux_Enabled);
    if (chartInstance->c105_e_is_Aux_Enabled == c105_IN_Mode_Aux2_Aux1) {
      chartInstance->c105_c_tp_Mode_Aux2_Aux1 = 1U;
      if (sf_mex_sub(chartInstance->c105_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 42) == 0.0) {
        chartInstance->c105_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c105_c_tp_Mode_Aux2_Aux1 = 0U;
    }

    chartInstance->c105_b_tp_Mode_Aux4_Aux1 = (uint8_T)
      (chartInstance->c105_e_is_Aux_Enabled == c105_b_IN_Mode_Aux4_Aux1);
    if (chartInstance->c105_e_is_Aux_Enabled == c105_b_IN_Mode_Aux4_Offset) {
      chartInstance->c105_b_tp_Mode_Aux4_Offset = 1U;
      if (sf_mex_sub(chartInstance->c105_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 44) == 0.0) {
        chartInstance->c105_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c105_b_tp_Mode_Aux4_Offset = 0U;
    }

    if (chartInstance->c105_b_is_Offset_Right == c105_IN_Mode_None_Offset) {
      chartInstance->c105_b_tp_Mode_None_Offset = 1U;
      if (sf_mex_sub(chartInstance->c105_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 45) == 0.0) {
        chartInstance->c105_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c105_b_tp_Mode_None_Offset = 0U;
    }

    chartInstance->c105_c_tp_INIT_SystemCheck = (uint8_T)
      (chartInstance->c105_is_OptionC == c105_IN_INIT_SystemCheck);
    chartInstance->c105_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c105_setSimStateSideEffectsInfo);
}

static void sf_gateway_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  c105_set_sim_state_side_effects_c105_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c105_temporalCounter_i1 < 255U) {
    chartInstance->c105_temporalCounter_i1 = c105__u8_s32_(chartInstance,
      chartInstance->c105_temporalCounter_i1 + 1, 0U, 0U, 0U);
  }

  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 101U, chartInstance->c105_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_change_OffsetSelectSw, 14U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_din_OffsetSelectSw, 13U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_change_AuxEnable, 12U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_state_AuxEnable, 11U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_fault_Diverter, 10U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_InitEERead, 9U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_state_System, 8U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_state_Engine, 7U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_state_Console, 6U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_valid_RightControl, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_valid_LeftControl, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_change_LeftControlMode, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_state_CommSecondary, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_change_RightControlMode, 1U);
  chartInstance->c105_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 101U,
               chartInstance->c105_sfEvent);
  if (chartInstance->c105_is_active_c105_MX_Gtwy_Control == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 101U,
                 chartInstance->c105_sfEvent);
    chartInstance->c105_is_active_c105_MX_Gtwy_Control = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 101U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c105_sfEvent);
    chartInstance->c105_is_c105_MX_Gtwy_Control = c105_IN_Non_Functional;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c105_sfEvent);
    chartInstance->c105_tp_Non_Functional = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_AUX1;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    *chartInstance->c105_check_LeftNeutral = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
    *chartInstance->c105_check_RightNeutral = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
    *chartInstance->c105_flag_AuxEnableFlash = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash, 15U);
    *chartInstance->c105_aux_inhibit = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
    *chartInstance->c105_display_request = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
    chartInstance->c105_stored_ControlMode = chartInstance->c105_EE_NA_NA;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode, 0U);
  } else {
    switch (chartInstance->c105_is_c105_MX_Gtwy_Control) {
     case c105_IN_Non_Functional:
      CV_CHART_EVAL(101, 0, c105_IN_Non_Functional);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                   chartInstance->c105_sfEvent);
      c105_out = (CV_TRANSITION_EVAL(5U, (int32_T)(_SFD_CCP_CALL(5U, 5U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 5U, 0, (real_T)
        chartInstance->c105_CD_EMEA_CONTROLS_OPTION_A, (real_T)
        chartInstance->c105_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c105_CD_EMEA_CONTROLS_OPTION_A !=
        chartInstance->c105_NON_FUNCTIONAL) != 0U, chartInstance->c105_sfEvent)
        != 0U)) != 0);
      if (c105_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Non_Functional = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_c105_MX_Gtwy_Control = c105_IN_OptionA;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_OptionA = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_OptionA = c105_IN_INIT_SystemCheck;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_INIT_SystemCheck = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        *chartInstance->c105_display_request = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
        *chartInstance->c105_flag_AuxEnableFlash = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                              15U);
        *chartInstance->c105_check_LeftNeutral = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                              18U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U,
                     chartInstance->c105_sfEvent);
        c105_b_out = (CV_TRANSITION_EVAL(6U, (int32_T)(_SFD_CCP_CALL(5U, 6U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 6U, 0, (real_T)
          chartInstance->c105_CD_EMEA_CONTROLS_OPTION_B, (real_T)
          chartInstance->c105_NON_FUNCTIONAL, 0, 1U,
          chartInstance->c105_CD_EMEA_CONTROLS_OPTION_B !=
          chartInstance->c105_NON_FUNCTIONAL) != 0U, chartInstance->c105_sfEvent)
          != 0U)) != 0);
        if (c105_b_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Non_Functional = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c105_sfEvent);
          chartInstance->c105_is_c105_MX_Gtwy_Control = c105_IN_OptionB;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_OptionB = 1U;
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 127U, chartInstance->c105_sfEvent);
          chartInstance->c105_is_OptionB = c105_IN_INIT_SystemCheck;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_INIT_SystemCheck = 1U;
          c105_enter_atomic_INIT_SystemCheck(chartInstance);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                       chartInstance->c105_sfEvent);
          c105_c_out = (CV_TRANSITION_EVAL(7U, (int32_T)(_SFD_CCP_CALL(5U, 7U, 0,
            (boolean_T)CV_RELATIONAL_EVAL(5U, 7U, 0, (real_T)
            chartInstance->c105_CD_EMEA_CONTROLS_OPTION_C, (real_T)
            chartInstance->c105_NON_FUNCTIONAL, 0, 1U,
            chartInstance->c105_CD_EMEA_CONTROLS_OPTION_C !=
            chartInstance->c105_NON_FUNCTIONAL) != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_c_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Non_Functional = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_c105_MX_Gtwy_Control = c105_IN_OptionC;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_OptionC = 1U;
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 40U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_OptionC = c105_IN_INIT_SystemCheck;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 46U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_tp_INIT_SystemCheck = 1U;
            c105_b_enter_atomic_INIT_SystemCheck(chartInstance);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                         chartInstance->c105_sfEvent);
          }
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c105_sfEvent);
      break;

     case c105_IN_OptionA:
      CV_CHART_EVAL(101, 0, c105_IN_OptionA);
      c105_OptionA(chartInstance);
      break;

     case c105_IN_OptionB:
      CV_CHART_EVAL(101, 0, c105_IN_OptionB);
      c105_OptionB(chartInstance);
      break;

     case c105_IN_OptionC:
      CV_CHART_EVAL(101, 0, c105_IN_OptionC);
      c105_OptionC(chartInstance);
      break;

     default:
      CV_CHART_EVAL(101, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c105_is_c105_MX_Gtwy_Control = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c105_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 101U, chartInstance->c105_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MX_Gtwy_ControlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c105_MX_Gtwy_Control(SFc105_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  c105_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void initSimStructsc105_MX_Gtwy_Control
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c105_OptionA(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_temp;
  boolean_T c105_b_temp;
  boolean_T c105_c_temp;
  boolean_T c105_d_temp;
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T c105_e_temp;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T c105_f_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c105_sfEvent);
  switch (chartInstance->c105_is_OptionA) {
   case c105_IN_Delay:
    CV_STATE_EVAL(1, 0, c105_IN_Delay);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 197U, chartInstance->c105_sfEvent);
    chartInstance->c105_tp_Delay = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c105_sfEvent);
    chartInstance->c105_is_OptionA = c105_IN_Enabled;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c105_sfEvent);
    chartInstance->c105_tp_Enabled = 1U;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 195U,
                 chartInstance->c105_sfEvent);
    c105_out = (CV_TRANSITION_EVAL(195U, (int32_T)(_SFD_CCP_CALL(5U, 195U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 195U, 0, (real_T)
      *chartInstance->c105_state_AuxEnable, (real_T)chartInstance->c105_INACTIVE,
      0, 1U, *chartInstance->c105_state_AuxEnable !=
      chartInstance->c105_INACTIVE) != 0U, chartInstance->c105_sfEvent) != 0U))
                != 0);
    if (c105_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 195U, chartInstance->c105_sfEvent);
      chartInstance->c105_is_Enabled = c105_IN_Aux_Enabled;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Aux_Enabled = 1U;
      *chartInstance->c105_flag_AuxEnableFlash = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      c105_enter_internal_Aux_Enabled(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 26U, chartInstance->c105_sfEvent);
      chartInstance->c105_is_Enabled = c105_IN_Mode_Offset_None;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c105_sfEvent);
      chartInstance->c105_temporalCounter_i1 = 0U;
      chartInstance->c105_tp_Mode_Offset_None = 1U;
      *chartInstance->c105_mode_LeftControl =
        chartInstance->c105_MODE_LEFT_OFFSET;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
      *chartInstance->c105_mode_RightControl =
        chartInstance->c105_MODE_RIGHT_NONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
      chartInstance->c105_stored_ControlMode = chartInstance->c105_EE_LT_OF_NA;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode, 0U);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Enabled:
    CV_STATE_EVAL(1, 0, c105_IN_Enabled);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 25U,
                 chartInstance->c105_sfEvent);
    c105_temp = (_SFD_CCP_CALL(5U, 25U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 25U,
      0, (real_T)*chartInstance->c105_state_Console, (real_T)
      chartInstance->c105_ACTIVE, 0, 1U, *chartInstance->c105_state_Console !=
      chartInstance->c105_ACTIVE) != 0U, chartInstance->c105_sfEvent) != 0U);
    if (!c105_temp) {
      c105_temp = (_SFD_CCP_CALL(5U, 25U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        25U, 1, (real_T)*chartInstance->c105_state_System, (real_T)
        chartInstance->c105_SYS_NORMAL, 0, 1U, *chartInstance->c105_state_System
        != chartInstance->c105_SYS_NORMAL) != 0U, chartInstance->c105_sfEvent)
                   != 0U);
    }

    c105_c_temp = c105_temp;
    if (!c105_temp) {
      c105_c_temp = (_SFD_CCP_CALL(5U, 25U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        25U, 2, (real_T)*chartInstance->c105_state_Engine, (real_T)
        chartInstance->c105_ENGINE_CRANKING, 0, 0U,
        *chartInstance->c105_state_Engine == chartInstance->c105_ENGINE_CRANKING)
        != 0U, chartInstance->c105_sfEvent) != 0U);
    }

    c105_b_out = (CV_TRANSITION_EVAL(25U, (int32_T)c105_c_temp) != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 25U, chartInstance->c105_sfEvent);
      c105_exit_internal_Enabled(chartInstance);
      chartInstance->c105_tp_Enabled = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c105_sfEvent);
      chartInstance->c105_is_OptionA = c105_IN_INIT_SystemCheck;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_INIT_SystemCheck = 1U;
      *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
      *chartInstance->c105_mode_RightControl =
        chartInstance->c105_MODE_RIGHT_NONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
      *chartInstance->c105_display_request = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
      *chartInstance->c105_flag_AuxEnableFlash = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      *chartInstance->c105_check_LeftNeutral = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c105_sfEvent);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                   chartInstance->c105_sfEvent);
      switch (chartInstance->c105_is_Enabled) {
       case c105_IN_Aux_Enabled:
        CV_STATE_EVAL(3, 0, c105_IN_Aux_Enabled);
        c105_Aux_Enabled(chartInstance);
        if (chartInstance->c105_is_OptionA != c105_IN_Enabled) {
        } else {
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c105_sfEvent);
        }
        break;

       case c105_IN_Mode_Offset_None:
        CV_STATE_EVAL(3, 0, c105_IN_Mode_Offset_None);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                     chartInstance->c105_sfEvent);
        c105_d_out = (CV_TRANSITION_EVAL(10U, (int32_T)(_SFD_CCP_CALL(5U, 10U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 10U, 0, (real_T)
          *chartInstance->c105_state_AuxEnable, (real_T)
          chartInstance->c105_INACTIVE, 0, 1U,
          *chartInstance->c105_state_AuxEnable != chartInstance->c105_INACTIVE)
          != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Mode_Offset_None = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c105_sfEvent);
          chartInstance->c105_is_Enabled = c105_IN_Aux_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Aux_Enabled = 1U;
          *chartInstance->c105_flag_AuxEnableFlash = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                                15U);
          c105_enter_internal_Aux_Enabled(chartInstance);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                       chartInstance->c105_sfEvent);
          c105_f_out = (CV_TRANSITION_EVAL(8U, (int32_T)(_SFD_CCP_CALL(5U, 8U, 0,
            *chartInstance->c105_change_LeftControlMode != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c105_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c105_sfEvent);
            c105_set_state_Buzzer(chartInstance, 0,
                                  chartInstance->c105_TRIPLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            *chartInstance->c105_display_request = true;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                  21U);
            *chartInstance->c105_flag_AuxEnableFlash = true;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Offset_None = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_Enabled = c105_IN_Mode_Offset_None;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c105_sfEvent);
            chartInstance->c105_temporalCounter_i1 = 0U;
            chartInstance->c105_tp_Mode_Offset_None = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_OFFSET;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_NONE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            chartInstance->c105_stored_ControlMode =
              chartInstance->c105_EE_LT_OF_NA;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode,
                                  0U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                         chartInstance->c105_sfEvent);
            *chartInstance->c105_check_LeftNeutral = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                  18U);
            if (chartInstance->c105_temporalCounter_i1 >= 10U) {
              CV_STATE_EVAL(7, 0, 2);
              *chartInstance->c105_display_request = false;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                    21U);
            } else {
              CV_STATE_EVAL(7, 0, 1);
            }

            if (chartInstance->c105_temporalCounter_i1 >= 200U) {
              CV_STATE_EVAL(7, 1, 2);
              *chartInstance->c105_flag_AuxEnableFlash = false;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c105_flag_AuxEnableFlash,
                                    15U);
            } else {
              CV_STATE_EVAL(7, 1, 1);
            }
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c105_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c105_sfEvent);
        break;

       default:
        CV_STATE_EVAL(3, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c105_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c105_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c105_sfEvent);
        break;
      }
    }
    break;

   case c105_IN_INIT_SystemCheck:
    CV_STATE_EVAL(1, 0, c105_IN_INIT_SystemCheck);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                 chartInstance->c105_sfEvent);
    c105_b_temp = (_SFD_CCP_CALL(5U, 1U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 1U,
      0, (real_T)*chartInstance->c105_state_Console, (real_T)
      chartInstance->c105_ACTIVE, 0, 0U, *chartInstance->c105_state_Console ==
      chartInstance->c105_ACTIVE) != 0U, chartInstance->c105_sfEvent) != 0U);
    if (c105_b_temp) {
      c105_b_temp = (_SFD_CCP_CALL(5U, 1U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        1U, 1, (real_T)*chartInstance->c105_state_Engine, (real_T)
        chartInstance->c105_ENGINE_CRANKING, 0, 1U,
        *chartInstance->c105_state_Engine != chartInstance->c105_ENGINE_CRANKING)
        != 0U, chartInstance->c105_sfEvent) != 0U);
    }

    c105_d_temp = c105_b_temp;
    if (c105_b_temp) {
      c105_d_temp = (_SFD_CCP_CALL(5U, 1U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        1U, 2, (real_T)*chartInstance->c105_state_System, (real_T)
        chartInstance->c105_SYS_NORMAL, 0, 0U, *chartInstance->c105_state_System
        == chartInstance->c105_SYS_NORMAL) != 0U, chartInstance->c105_sfEvent)
                     != 0U);
    }

    c105_e_temp = c105_d_temp;
    if (c105_d_temp) {
      c105_e_temp = (_SFD_CCP_CALL(5U, 1U, 3,
        *chartInstance->c105_flag_InitEERead != 0U, chartInstance->c105_sfEvent)
                     != 0U);
    }

    c105_c_out = (CV_TRANSITION_EVAL(1U, (int32_T)c105_e_temp) != 0);
    if (c105_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 106U,
                   chartInstance->c105_sfEvent);
      c105_e_out = (CV_TRANSITION_EVAL(106U, (int32_T)(_SFD_CCP_CALL(5U, 106U, 0,
        *chartInstance->c105_valid_LeftControl != 0U,
        chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 106U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_INIT_SystemCheck = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_OptionA = c105_IN_Delay;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Delay = 1U;
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 107U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_INIT_SystemCheck = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_OptionA = c105_IN_Left_Control_or_Diverter_Fault;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Left_Control_or_Diverter_Fault = 1U;
        *chartInstance->c105_flag_AuxEnableFlash = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                              15U);
        *chartInstance->c105_check_LeftNeutral = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                              18U);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 108U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_Left_Control_or_Diverter_Fault =
          c105_IN_Fault_Mode;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Fault_Mode = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        chartInstance->c105_stored_ControlMode = chartInstance->c105_EE_NA_NA;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode, 0U);
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                   chartInstance->c105_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Left_Control_or_Diverter_Fault:
    CV_STATE_EVAL(1, 0, c105_IN_Left_Control_or_Diverter_Fault);
    c105_Left_Control_or_Diverter_Fault(chartInstance);
    break;

   default:
    CV_STATE_EVAL(1, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c105_is_OptionA = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c105_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c105_sfEvent);
}

static void c105_Left_Control_or_Diverter_Fault
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_temp;
  boolean_T c105_b_temp;
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 111U,
               chartInstance->c105_sfEvent);
  c105_temp = (_SFD_CCP_CALL(5U, 111U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 111U,
    0, (real_T)*chartInstance->c105_state_Console, (real_T)
    chartInstance->c105_ACTIVE, 0, 1U, *chartInstance->c105_state_Console !=
    chartInstance->c105_ACTIVE) != 0U, chartInstance->c105_sfEvent) != 0U);
  if (!c105_temp) {
    c105_temp = (_SFD_CCP_CALL(5U, 111U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      111U, 1, (real_T)*chartInstance->c105_state_System, (real_T)
      chartInstance->c105_SYS_NORMAL, 0, 1U, *chartInstance->c105_state_System
      != chartInstance->c105_SYS_NORMAL) != 0U, chartInstance->c105_sfEvent) !=
                 0U);
  }

  c105_b_temp = c105_temp;
  if (!c105_temp) {
    c105_b_temp = (_SFD_CCP_CALL(5U, 111U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      111U, 2, (real_T)*chartInstance->c105_state_Engine, (real_T)
      chartInstance->c105_ENGINE_CRANKING, 0, 0U,
      *chartInstance->c105_state_Engine == chartInstance->c105_ENGINE_CRANKING)
      != 0U, chartInstance->c105_sfEvent) != 0U);
  }

  c105_out = (CV_TRANSITION_EVAL(111U, (int32_T)c105_b_temp) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 111U, chartInstance->c105_sfEvent);
    c105_exit_internal_Left_Control_or_Diverter_Fault(chartInstance);
    chartInstance->c105_tp_Left_Control_or_Diverter_Fault = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c105_sfEvent);
    chartInstance->c105_is_OptionA = c105_IN_INIT_SystemCheck;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c105_sfEvent);
    chartInstance->c105_tp_INIT_SystemCheck = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    *chartInstance->c105_display_request = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
    *chartInstance->c105_flag_AuxEnableFlash = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash, 15U);
    *chartInstance->c105_check_LeftNeutral = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                 chartInstance->c105_sfEvent);
    switch (chartInstance->c105_is_Left_Control_or_Diverter_Fault) {
     case c105_IN_Fault_Mode:
      CV_STATE_EVAL(9, 0, c105_IN_Fault_Mode);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 109U,
                   chartInstance->c105_sfEvent);
      c105_b_out = (CV_TRANSITION_EVAL(109U, (int32_T)(_SFD_CCP_CALL(5U, 109U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 109U, 0, (real_T)
        *chartInstance->c105_state_AuxEnable, (real_T)
        chartInstance->c105_INACTIVE, 0, 1U,
        *chartInstance->c105_state_AuxEnable != chartInstance->c105_INACTIVE) !=
        0U, chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 109U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Fault_Mode = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_Left_Control_or_Diverter_Fault =
          c105_IN_Mode_None_Aux1;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Mode_None_Aux1 = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_AUX1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                     chartInstance->c105_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c105_sfEvent);
      break;

     case c105_IN_Mode_None_Aux1:
      CV_STATE_EVAL(9, 0, c105_IN_Mode_None_Aux1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 110U,
                   chartInstance->c105_sfEvent);
      c105_c_out = (CV_TRANSITION_EVAL(110U, (int32_T)(_SFD_CCP_CALL(5U, 110U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 110U, 0, (real_T)
        *chartInstance->c105_state_AuxEnable, (real_T)
        chartInstance->c105_INACTIVE, 0, 0U,
        *chartInstance->c105_state_AuxEnable == chartInstance->c105_INACTIVE) !=
        0U, chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 110U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Mode_None_Aux1 = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_Left_Control_or_Diverter_Fault =
          c105_IN_Fault_Mode;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Fault_Mode = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        chartInstance->c105_stored_ControlMode = chartInstance->c105_EE_NA_NA;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode, 0U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                     chartInstance->c105_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c105_sfEvent);
      break;

     default:
      CV_STATE_EVAL(9, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c105_is_Left_Control_or_Diverter_Fault =
        c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c105_sfEvent);
      break;
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c105_sfEvent);
}

static void c105_exit_internal_Left_Control_or_Diverter_Fault
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c105_is_Left_Control_or_Diverter_Fault) {
   case c105_IN_Fault_Mode:
    CV_STATE_EVAL(9, 1, c105_IN_Fault_Mode);
    chartInstance->c105_tp_Fault_Mode = 0U;
    chartInstance->c105_is_Left_Control_or_Diverter_Fault =
      c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Mode_None_Aux1:
    CV_STATE_EVAL(9, 1, c105_IN_Mode_None_Aux1);
    chartInstance->c105_tp_Mode_None_Aux1 = 0U;
    chartInstance->c105_is_Left_Control_or_Diverter_Fault =
      c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(9, 1, 0);
    chartInstance->c105_is_Left_Control_or_Diverter_Fault =
      c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_exit_internal_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c105_is_Enabled) {
   case c105_IN_Aux_Enabled:
    CV_STATE_EVAL(3, 1, c105_IN_Aux_Enabled);
    c105_exit_internal_Aux_Enabled(chartInstance);
    chartInstance->c105_tp_Aux_Enabled = 0U;
    chartInstance->c105_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Mode_Offset_None:
    CV_STATE_EVAL(3, 1, c105_IN_Mode_Offset_None);
    chartInstance->c105_tp_Mode_Offset_None = 0U;
    chartInstance->c105_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(3, 1, 0);
    chartInstance->c105_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_enter_internal_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 196U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(196U, (int32_T)(_SFD_CCP_CALL(5U, 196U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 196U, 0, (real_T)
    chartInstance->c105_stored_ControlMode, (real_T)
    chartInstance->c105_EE_LT_A2_A1, 0, 0U,
    chartInstance->c105_stored_ControlMode == chartInstance->c105_EE_LT_A2_A1)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 196U, chartInstance->c105_sfEvent);
    chartInstance->c105_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
    chartInstance->c105_tp_Mode_Aux2_Aux1 = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_AUX2;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_AUX1;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    chartInstance->c105_stored_ControlMode = chartInstance->c105_EE_LT_A2_A1;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode, 0U);
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 113U, chartInstance->c105_sfEvent);
    chartInstance->c105_is_Aux_Enabled = c105_IN_Mode_Offset_Aux1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c105_sfEvent);
    chartInstance->c105_tp_Mode_Offset_Aux1 = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_AUX1;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    chartInstance->c105_stored_ControlMode = chartInstance->c105_EE_LT_OF_A1;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode, 0U);
    *chartInstance->c105_display_request = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
  }
}

static void c105_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T c105_f_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 9U, chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(9U, (int32_T)(_SFD_CCP_CALL(5U, 9U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 9U, 0, (real_T)
    *chartInstance->c105_state_AuxEnable, (real_T)chartInstance->c105_INACTIVE,
    0, 0U, *chartInstance->c105_state_AuxEnable == chartInstance->c105_INACTIVE)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c105_sfEvent);
    c105_exit_internal_Aux_Enabled(chartInstance);
    chartInstance->c105_tp_Aux_Enabled = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c105_sfEvent);
    chartInstance->c105_is_Enabled = c105_IN_Mode_Offset_None;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_tp_Mode_Offset_None = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    chartInstance->c105_stored_ControlMode = chartInstance->c105_EE_LT_OF_NA;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode, 0U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 112U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(112U, (int32_T)(_SFD_CCP_CALL(5U, 112U, 0, *
      chartInstance->c105_fault_Diverter != 0U, chartInstance->c105_sfEvent) !=
      0U)) != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 112U, chartInstance->c105_sfEvent);
      c105_exit_internal_Aux_Enabled(chartInstance);
      chartInstance->c105_tp_Aux_Enabled = 0U;
      chartInstance->c105_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Enabled = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c105_sfEvent);
      chartInstance->c105_is_OptionA = c105_IN_Left_Control_or_Diverter_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Left_Control_or_Diverter_Fault = 1U;
      *chartInstance->c105_flag_AuxEnableFlash = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      *chartInstance->c105_check_LeftNeutral = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 108U, chartInstance->c105_sfEvent);
      chartInstance->c105_is_Left_Control_or_Diverter_Fault = c105_IN_Fault_Mode;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Fault_Mode = 1U;
      *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
      *chartInstance->c105_mode_RightControl =
        chartInstance->c105_MODE_RIGHT_NONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
      chartInstance->c105_stored_ControlMode = chartInstance->c105_EE_NA_NA;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode, 0U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                   chartInstance->c105_sfEvent);
      switch (chartInstance->c105_is_Aux_Enabled) {
       case c105_IN_Mode_Aux2_Aux1:
        CV_STATE_EVAL(4, 0, c105_IN_Mode_Aux2_Aux1);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 30U,
                     chartInstance->c105_sfEvent);
        c105_c_out = (CV_TRANSITION_EVAL(30U, (int32_T)(_SFD_CCP_CALL(5U, 30U, 0,
          *chartInstance->c105_change_LeftControlMode != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 30U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                       chartInstance->c105_sfEvent);
          c105_e_out = (CV_TRANSITION_EVAL(3U, (int32_T)(_SFD_CCP_CALL(5U, 3U, 0,
            *chartInstance->c105_valid_LeftControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c105_sfEvent);
            c105_set_state_Buzzer(chartInstance, 0,
                                  chartInstance->c105_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            chartInstance->c105_tp_Mode_Aux2_Aux1 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_Aux_Enabled = c105_IN_Mode_Offset_Aux1;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Offset_Aux1 = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_OFFSET;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_AUX1;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            chartInstance->c105_stored_ControlMode =
              chartInstance->c105_EE_LT_OF_A1;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode,
                                  0U);
            *chartInstance->c105_display_request = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                  21U);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 31U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Aux2_Aux1 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux1;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Aux2_Aux1 = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_AUX2;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_AUX1;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            chartInstance->c105_stored_ControlMode =
              chartInstance->c105_EE_LT_A2_A1;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode,
                                  0U);
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c105_sfEvent);
        break;

       case c105_IN_Mode_Offset_Aux1:
        CV_STATE_EVAL(4, 0, c105_IN_Mode_Offset_Aux1);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 28U,
                     chartInstance->c105_sfEvent);
        c105_d_out = (CV_TRANSITION_EVAL(28U, (int32_T)(_SFD_CCP_CALL(5U, 28U, 0,
          *chartInstance->c105_change_LeftControlMode != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 28U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                       chartInstance->c105_sfEvent);
          c105_f_out = (CV_TRANSITION_EVAL(2U, (int32_T)(_SFD_CCP_CALL(5U, 2U, 0,
            *chartInstance->c105_valid_LeftControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c105_sfEvent);
            c105_set_state_Buzzer(chartInstance, 0,
                                  chartInstance->c105_DOUBLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            chartInstance->c105_tp_Mode_Offset_Aux1 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux1;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Aux2_Aux1 = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_AUX2;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_AUX1;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            chartInstance->c105_stored_ControlMode =
              chartInstance->c105_EE_LT_A2_A1;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode,
                                  0U);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 29U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Offset_Aux1 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_Aux_Enabled = c105_IN_Mode_Offset_Aux1;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Offset_Aux1 = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_OFFSET;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_AUX1;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            chartInstance->c105_stored_ControlMode =
              chartInstance->c105_EE_LT_OF_A1;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c105_stored_ControlMode,
                                  0U);
            *chartInstance->c105_display_request = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                  21U);
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c105_sfEvent);
        break;

       default:
        CV_STATE_EVAL(4, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c105_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c105_sfEvent);
}

static void c105_exit_internal_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  switch (chartInstance->c105_is_Aux_Enabled) {
   case c105_IN_Mode_Aux2_Aux1:
    CV_STATE_EVAL(4, 1, c105_IN_Mode_Aux2_Aux1);
    chartInstance->c105_tp_Mode_Aux2_Aux1 = 0U;
    chartInstance->c105_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Mode_Offset_Aux1:
    CV_STATE_EVAL(4, 1, c105_IN_Mode_Offset_Aux1);
    chartInstance->c105_tp_Mode_Offset_Aux1 = 0U;
    chartInstance->c105_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(4, 1, 0);
    chartInstance->c105_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_OptionB(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_temp;
  boolean_T c105_b_out;
  boolean_T c105_b_temp;
  boolean_T c105_c_out;
  boolean_T c105_c_temp;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T c105_f_out;
  boolean_T c105_g_out;
  boolean_T c105_h_out;
  boolean_T c105_i_out;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U, chartInstance->c105_sfEvent);
  switch (chartInstance->c105_is_OptionB) {
   case c105_IN_Delay:
    CV_STATE_EVAL(12, 0, c105_IN_Delay);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 132U,
                 chartInstance->c105_sfEvent);
    c105_out = (CV_TRANSITION_EVAL(132U, (int32_T)(_SFD_CCP_CALL(5U, 132U, 0,
      (chartInstance->c105_temporalCounter_i1 >= 20U) != 0U,
      chartInstance->c105_sfEvent) != 0U)) != 0);
    guard1 = false;
    guard2 = false;
    if (c105_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 132U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 135U,
                   chartInstance->c105_sfEvent);
      c105_c_out = (CV_TRANSITION_EVAL(135U, (int32_T)(_SFD_CCP_CALL(5U, 135U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 135U, 0, (real_T)
        *chartInstance->c105_din_OffsetSelectSw, (real_T)
        chartInstance->c105_OFFSET_SELECT_RIGHT, 0, 0U, (int32_T)
        *chartInstance->c105_din_OffsetSelectSw ==
        chartInstance->c105_OFFSET_SELECT_RIGHT) != 0U,
        chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 135U, chartInstance->c105_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 134U,
                     chartInstance->c105_sfEvent);
        c105_d_out = (CV_TRANSITION_EVAL(134U, (int32_T)(_SFD_CCP_CALL(5U, 134U,
          0, *chartInstance->c105_valid_RightControl != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 134U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 136U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 146U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Delay = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c105_sfEvent);
          chartInstance->c105_is_OptionB = c105_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Enabled = 1U;
          chartInstance->c105_b_is_Enabled = c105_IN_Offset_Right;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Offset_Right = 1U;
          c105_enter_internal_Offset_Right(chartInstance);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 137U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_RightNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          guard1 = true;
        }
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 138U, chartInstance->c105_sfEvent);
        guard2 = true;
      }
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 133U,
                   chartInstance->c105_sfEvent);
      c105_b_out = (CV_TRANSITION_EVAL(133U, (int32_T)(_SFD_CCP_CALL(5U, 133U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 133U, 0, (real_T)
        *chartInstance->c105_state_CommSecondary, (real_T)
        chartInstance->c105_NO_COMMUNICATION, 0, 0U,
        *chartInstance->c105_state_CommSecondary ==
        chartInstance->c105_NO_COMMUNICATION) != 0U, chartInstance->c105_sfEvent)
        != 0U)) != 0);
      if (c105_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 133U, chartInstance->c105_sfEvent);
        guard2 = true;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U,
                     chartInstance->c105_sfEvent);
      }
    }

    if (guard2) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 142U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 144U,
                   chartInstance->c105_sfEvent);
      c105_e_out = (CV_TRANSITION_EVAL(144U, (int32_T)(_SFD_CCP_CALL(5U, 144U, 0,
        *chartInstance->c105_valid_LeftControl != 0U,
        chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 144U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_Delay = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_OptionB = c105_IN_Enabled;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_Enabled = 1U;
        chartInstance->c105_b_is_Enabled = c105_IN_Offset_Left;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Offset_Left = 1U;
        c105_enter_internal_Offset_Left(chartInstance);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 141U, chartInstance->c105_sfEvent);
        *chartInstance->c105_check_LeftNeutral = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                              18U);
        guard1 = true;
      }
    }

    if (guard1) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 140U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 143U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 145U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Delay = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c105_sfEvent);
      chartInstance->c105_is_OptionB = c105_IN_Enabled;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Enabled = 1U;
      chartInstance->c105_b_is_Enabled = c105_IN_Control_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Control_Fault = 1U;
      c105_enter_atomic_Control_Fault(chartInstance);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Enabled:
    CV_STATE_EVAL(12, 0, c105_IN_Enabled);
    c105_Enabled(chartInstance);
    break;

   case c105_IN_INIT_SystemCheck:
    CV_STATE_EVAL(12, 0, c105_IN_INIT_SystemCheck);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 129U,
                 chartInstance->c105_sfEvent);
    c105_temp = (_SFD_CCP_CALL(5U, 129U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      129U, 0, (real_T)*chartInstance->c105_state_Console, (real_T)
      chartInstance->c105_ACTIVE, 0, 0U, *chartInstance->c105_state_Console ==
      chartInstance->c105_ACTIVE) != 0U, chartInstance->c105_sfEvent) != 0U);
    if (c105_temp) {
      c105_temp = (_SFD_CCP_CALL(5U, 129U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        129U, 1, (real_T)*chartInstance->c105_state_System, (real_T)
        chartInstance->c105_SYS_NORMAL, 0, 0U, *chartInstance->c105_state_System
        == chartInstance->c105_SYS_NORMAL) != 0U, chartInstance->c105_sfEvent)
                   != 0U);
    }

    c105_b_temp = c105_temp;
    if (c105_temp) {
      c105_b_temp = (_SFD_CCP_CALL(5U, 129U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        129U, 2, (real_T)*chartInstance->c105_state_Engine, (real_T)
        chartInstance->c105_ENGINE_CRANKING, 0, 1U,
        *chartInstance->c105_state_Engine != chartInstance->c105_ENGINE_CRANKING)
        != 0U, chartInstance->c105_sfEvent) != 0U);
    }

    c105_c_temp = c105_b_temp;
    if (c105_b_temp) {
      c105_c_temp = (_SFD_CCP_CALL(5U, 129U, 3,
        *chartInstance->c105_flag_InitEERead != 0U, chartInstance->c105_sfEvent)
                     != 0U);
    }

    c105_f_out = (CV_TRANSITION_EVAL(129U, (int32_T)c105_c_temp) != 0);
    if (c105_f_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 129U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 130U,
                   chartInstance->c105_sfEvent);
      c105_g_out = (CV_TRANSITION_EVAL(130U, (int32_T)(_SFD_CCP_CALL(5U, 130U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 130U, 0, (real_T)
        *chartInstance->c105_state_CommSecondary, (real_T)
        chartInstance->c105_NORMAL, 0, 0U,
        *chartInstance->c105_state_CommSecondary == chartInstance->c105_NORMAL)
        != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_g_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 130U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_INIT_SystemCheck = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_OptionB = c105_IN_Delay;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c105_sfEvent);
        chartInstance->c105_temporalCounter_i1 = 0U;
        chartInstance->c105_b_tp_Delay = 1U;
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 131U, chartInstance->c105_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 139U,
                     chartInstance->c105_sfEvent);
        c105_h_out = (CV_TRANSITION_EVAL(139U, (int32_T)(_SFD_CCP_CALL(5U, 139U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 139U, 0, (real_T)
          *chartInstance->c105_state_CommSecondary, (real_T)
          chartInstance->c105_NO_COMMUNICATION, 0, 0U,
          *chartInstance->c105_state_CommSecondary ==
          chartInstance->c105_NO_COMMUNICATION) != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_h_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 139U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 142U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 144U,
                       chartInstance->c105_sfEvent);
          c105_i_out = (CV_TRANSITION_EVAL(144U, (int32_T)(_SFD_CCP_CALL(5U,
            144U, 0, *chartInstance->c105_valid_LeftControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_i_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 144U,
                         chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_INIT_SystemCheck = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_OptionB = c105_IN_Enabled;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_Enabled = 1U;
            chartInstance->c105_b_is_Enabled = c105_IN_Offset_Left;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Offset_Left = 1U;
            c105_enter_internal_Offset_Left(chartInstance);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 141U,
                         chartInstance->c105_sfEvent);
            *chartInstance->c105_check_LeftNeutral = true;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                  18U);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 140U,
                         chartInstance->c105_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 143U,
                         chartInstance->c105_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 145U,
                         chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_INIT_SystemCheck = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_OptionB = c105_IN_Enabled;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_Enabled = 1U;
            chartInstance->c105_b_is_Enabled = c105_IN_Control_Fault;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Control_Fault = 1U;
            c105_enter_atomic_Control_Fault(chartInstance);
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 26U,
                       chartInstance->c105_sfEvent);
        }
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 26U,
                   chartInstance->c105_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 26U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(12, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c105_is_OptionB = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c105_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c105_sfEvent);
}

static void c105_enter_atomic_INIT_SystemCheck
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
  *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
  *chartInstance->c105_flag_AuxEnableFlash = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash, 15U);
  *chartInstance->c105_aux_inhibit = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
  *chartInstance->c105_display_request = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
  *chartInstance->c105_check_LeftNeutral = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
  *chartInstance->c105_check_RightNeutral = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
}

static void c105_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_temp;
  boolean_T c105_b_temp;
  boolean_T c105_out;
  boolean_T c105_c_temp;
  boolean_T c105_d_temp;
  boolean_T c105_b_out;
  boolean_T c105_e_temp;
  boolean_T c105_f_temp;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 128U,
               chartInstance->c105_sfEvent);
  c105_temp = (_SFD_CCP_CALL(5U, 128U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 128U,
    0, (real_T)*chartInstance->c105_state_Console, (real_T)
    chartInstance->c105_ACTIVE, 0, 1U, *chartInstance->c105_state_Console !=
    chartInstance->c105_ACTIVE) != 0U, chartInstance->c105_sfEvent) != 0U);
  if (!c105_temp) {
    c105_temp = (_SFD_CCP_CALL(5U, 128U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      128U, 1, (real_T)*chartInstance->c105_state_System, (real_T)
      chartInstance->c105_SYS_NORMAL, 0, 1U, *chartInstance->c105_state_System
      != chartInstance->c105_SYS_NORMAL) != 0U, chartInstance->c105_sfEvent) !=
                 0U);
  }

  c105_b_temp = c105_temp;
  if (!c105_temp) {
    c105_b_temp = (_SFD_CCP_CALL(5U, 128U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      128U, 2, (real_T)*chartInstance->c105_state_Engine, (real_T)
      chartInstance->c105_ENGINE_CRANKING, 0, 0U,
      *chartInstance->c105_state_Engine == chartInstance->c105_ENGINE_CRANKING)
      != 0U, chartInstance->c105_sfEvent) != 0U);
  }

  c105_out = (CV_TRANSITION_EVAL(128U, (int32_T)c105_b_temp) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 128U, chartInstance->c105_sfEvent);
    c105_b_exit_internal_Enabled(chartInstance);
    chartInstance->c105_b_tp_Enabled = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c105_sfEvent);
    chartInstance->c105_is_OptionB = c105_IN_INIT_SystemCheck;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c105_sfEvent);
    chartInstance->c105_b_tp_INIT_SystemCheck = 1U;
    c105_enter_atomic_INIT_SystemCheck(chartInstance);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 14U,
                 chartInstance->c105_sfEvent);
    switch (chartInstance->c105_b_is_Enabled) {
     case c105_IN_Control_Fault:
      CV_STATE_EVAL(14, 0, c105_IN_Control_Fault);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 149U,
                   chartInstance->c105_sfEvent);
      c105_c_temp = (_SFD_CCP_CALL(5U, 149U, 0,
        *chartInstance->c105_change_OffsetSelectSw != 0U,
        chartInstance->c105_sfEvent) != 0U);
      if (c105_c_temp) {
        c105_c_temp = (_SFD_CCP_CALL(5U, 149U, 1, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 149U, 0, (real_T)*chartInstance->c105_din_OffsetSelectSw, (real_T)
           chartInstance->c105_OFFSET_SELECT_RIGHT, 0, 0U, (int32_T)
           *chartInstance->c105_din_OffsetSelectSw ==
           chartInstance->c105_OFFSET_SELECT_RIGHT) != 0U,
          chartInstance->c105_sfEvent) != 0U);
      }

      c105_d_temp = c105_c_temp;
      if (c105_c_temp) {
        c105_d_temp = (_SFD_CCP_CALL(5U, 149U, 2, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 149U, 1, (real_T)*chartInstance->c105_state_CommSecondary,
           (real_T)chartInstance->c105_NORMAL, 0, 0U,
           *chartInstance->c105_state_CommSecondary ==
           chartInstance->c105_NORMAL) != 0U, chartInstance->c105_sfEvent) != 0U);
      }

      c105_b_out = (CV_TRANSITION_EVAL(149U, (int32_T)c105_d_temp) != 0);
      guard1 = false;
      if (c105_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 149U, chartInstance->c105_sfEvent);
        *chartInstance->c105_check_RightNeutral = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                              19U);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 151U, chartInstance->c105_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 158U,
                     chartInstance->c105_sfEvent);
        c105_c_out = (CV_TRANSITION_EVAL(158U, (int32_T)(_SFD_CCP_CALL(5U, 158U,
          0, *chartInstance->c105_valid_RightControl != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 158U, chartInstance->c105_sfEvent);
          c105_set_state_Buzzer(chartInstance, 0,
                                chartInstance->c105_SINGLE_MEDIUM_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          *chartInstance->c105_flag_AuxEnableFlash = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                                15U);
          chartInstance->c105_tp_Control_Fault = 0U;
          _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 15U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_aux_inhibit = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U,
                       chartInstance->c105_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_is_Enabled = c105_IN_Offset_Right;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Offset_Right = 1U;
          c105_enter_internal_Offset_Right(chartInstance);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 156U, chartInstance->c105_sfEvent);
          guard1 = true;
        }
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 157U,
                     chartInstance->c105_sfEvent);
        c105_e_temp = (_SFD_CCP_CALL(5U, 157U, 0,
          *chartInstance->c105_change_OffsetSelectSw != 0U,
          chartInstance->c105_sfEvent) != 0U);
        if (c105_e_temp) {
          c105_e_temp = (_SFD_CCP_CALL(5U, 157U, 1, (boolean_T)
            CV_RELATIONAL_EVAL(5U, 157U, 0, (real_T)
                               *chartInstance->c105_din_OffsetSelectSw, (real_T)
                               chartInstance->c105_OFFSET_SELECT_LEFT, 0, 0U,
                               (int32_T)*chartInstance->c105_din_OffsetSelectSw ==
                               chartInstance->c105_OFFSET_SELECT_LEFT) != 0U,
            chartInstance->c105_sfEvent) != 0U);
        }

        c105_f_temp = c105_e_temp;
        if (c105_e_temp) {
          c105_f_temp = (_SFD_CCP_CALL(5U, 157U, 2, (boolean_T)
            CV_RELATIONAL_EVAL(5U, 157U, 1, (real_T)
                               *chartInstance->c105_state_CommSecondary, (real_T)
                               chartInstance->c105_NORMAL, 0, 0U,
                               *chartInstance->c105_state_CommSecondary ==
                               chartInstance->c105_NORMAL) != 0U,
            chartInstance->c105_sfEvent) != 0U);
        }

        c105_d_out = (CV_TRANSITION_EVAL(157U, (int32_T)c105_f_temp) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 157U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 152U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 148U,
                       chartInstance->c105_sfEvent);
          c105_e_out = (CV_TRANSITION_EVAL(148U, (int32_T)(_SFD_CCP_CALL(5U,
            148U, 0, *chartInstance->c105_valid_LeftControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 148U,
                         chartInstance->c105_sfEvent);
            c105_set_state_Buzzer(chartInstance, 0,
                                  chartInstance->c105_SINGLE_MEDIUM_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            *chartInstance->c105_flag_AuxEnableFlash = true;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
            chartInstance->c105_tp_Control_Fault = 0U;
            _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 15U,
                         chartInstance->c105_sfEvent);
            *chartInstance->c105_aux_inhibit = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U,
                         chartInstance->c105_sfEvent);
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_is_Enabled = c105_IN_Offset_Left;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Offset_Left = 1U;
            c105_enter_internal_Offset_Left(chartInstance);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 150U,
                         chartInstance->c105_sfEvent);
            guard1 = true;
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 15U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          *chartInstance->c105_check_RightNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
        }
      }

      if (guard1) {
        chartInstance->c105_tp_Control_Fault = 0U;
        _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 15U,
                     chartInstance->c105_sfEvent);
        *chartInstance->c105_aux_inhibit = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c105_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_is_Enabled = c105_IN_Control_Fault;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Control_Fault = 1U;
        c105_enter_atomic_Control_Fault(chartInstance);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c105_sfEvent);
      break;

     case c105_IN_Offset_Left:
      CV_STATE_EVAL(14, 0, c105_IN_Offset_Left);
      c105_Offset_Left(chartInstance);
      break;

     case c105_IN_Offset_Right:
      CV_STATE_EVAL(14, 0, c105_IN_Offset_Right);
      c105_Offset_Right(chartInstance);
      break;

     default:
      CV_STATE_EVAL(14, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c105_b_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
      break;
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c105_sfEvent);
}

static void c105_b_exit_internal_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c105_b_is_Enabled) {
   case c105_IN_Control_Fault:
    CV_STATE_EVAL(14, 1, c105_IN_Control_Fault);
    chartInstance->c105_tp_Control_Fault = 0U;
    _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 15U, chartInstance->c105_sfEvent);
    *chartInstance->c105_aux_inhibit = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c105_sfEvent);
    chartInstance->c105_b_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Offset_Left:
    CV_STATE_EVAL(14, 1, c105_IN_Offset_Left);
    c105_exit_internal_Offset_Left(chartInstance);
    chartInstance->c105_tp_Offset_Left = 0U;
    chartInstance->c105_b_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Offset_Right:
    CV_STATE_EVAL(14, 1, c105_IN_Offset_Right);
    c105_exit_internal_Offset_Right(chartInstance);
    chartInstance->c105_tp_Offset_Right = 0U;
    chartInstance->c105_b_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(14, 1, 0);
    chartInstance->c105_b_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_enter_internal_Offset_Left(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 160U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(160U, (int32_T)(_SFD_CCP_CALL(5U, 160U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 160U, 0, (real_T)
    *chartInstance->c105_state_AuxEnable, (real_T)chartInstance->c105_INACTIVE,
    0, 1U, *chartInstance->c105_state_AuxEnable != chartInstance->c105_INACTIVE)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  guard1 = false;
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 160U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 162U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(162U, (int32_T)(_SFD_CCP_CALL(5U, 162U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 162U, 0, (real_T)c105_get_ee_ControlMode
      (chartInstance, 0), (real_T)chartInstance->c105_EE_RT_NA_OF, 0, 2U,
      c105_get_ee_ControlMode(chartInstance, 0) <
      chartInstance->c105_EE_RT_NA_OF) != 0U, chartInstance->c105_sfEvent) != 0U))
                  != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 162U, chartInstance->c105_sfEvent);
      chartInstance->c105_is_Offset_Left = c105_IN_Aux_Enabled;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Aux_Enabled = 1U;
      *chartInstance->c105_flag_AuxEnableFlash = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      c105_b_enter_internal_Aux_Enabled(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 163U, chartInstance->c105_sfEvent);
      *chartInstance->c105_aux_inhibit = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 165U, chartInstance->c105_sfEvent);
      guard1 = true;
    }
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 161U, chartInstance->c105_sfEvent);
    guard1 = true;
  }

  if (guard1) {
    chartInstance->c105_is_Offset_Left = c105_IN_Mode_Offset_None;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_b_tp_Mode_Offset_None = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
  }
}

static void c105_Offset_Left(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_temp;
  boolean_T c105_b_temp;
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 147U,
               chartInstance->c105_sfEvent);
  c105_temp = (_SFD_CCP_CALL(5U, 147U, 0,
    *chartInstance->c105_change_OffsetSelectSw != 0U,
    chartInstance->c105_sfEvent) != 0U);
  if (c105_temp) {
    c105_temp = (_SFD_CCP_CALL(5U, 147U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      147U, 0, (real_T)*chartInstance->c105_din_OffsetSelectSw, (real_T)
      chartInstance->c105_OFFSET_SELECT_RIGHT, 0, 0U, (int32_T)
      *chartInstance->c105_din_OffsetSelectSw ==
      chartInstance->c105_OFFSET_SELECT_RIGHT) != 0U,
      chartInstance->c105_sfEvent) != 0U);
  }

  c105_b_temp = c105_temp;
  if (c105_temp) {
    c105_b_temp = (_SFD_CCP_CALL(5U, 147U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      147U, 1, (real_T)*chartInstance->c105_state_CommSecondary, (real_T)
      chartInstance->c105_NORMAL, 0, 0U,
      *chartInstance->c105_state_CommSecondary == chartInstance->c105_NORMAL) !=
      0U, chartInstance->c105_sfEvent) != 0U);
  }

  c105_out = (CV_TRANSITION_EVAL(147U, (int32_T)c105_b_temp) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 147U, chartInstance->c105_sfEvent);
    *chartInstance->c105_check_RightNeutral = true;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 151U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 158U,
                 chartInstance->c105_sfEvent);
    c105_c_out = (CV_TRANSITION_EVAL(158U, (int32_T)(_SFD_CCP_CALL(5U, 158U, 0, *
      chartInstance->c105_valid_RightControl != 0U, chartInstance->c105_sfEvent)
      != 0U)) != 0);
    if (c105_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 158U, chartInstance->c105_sfEvent);
      c105_set_state_Buzzer(chartInstance, 0,
                            chartInstance->c105_SINGLE_MEDIUM_BEEP);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
      *chartInstance->c105_flag_AuxEnableFlash = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      c105_exit_internal_Offset_Left(chartInstance);
      chartInstance->c105_tp_Offset_Left = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_is_Enabled = c105_IN_Offset_Right;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Offset_Right = 1U;
      c105_enter_internal_Offset_Right(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 156U, chartInstance->c105_sfEvent);
      c105_exit_internal_Offset_Left(chartInstance);
      chartInstance->c105_tp_Offset_Left = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_is_Enabled = c105_IN_Control_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Control_Fault = 1U;
      c105_enter_atomic_Control_Fault(chartInstance);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 16U,
                 chartInstance->c105_sfEvent);
    switch (chartInstance->c105_is_Offset_Left) {
     case c105_IN_Aux_Enabled:
      CV_STATE_EVAL(16, 0, c105_IN_Aux_Enabled);
      c105_b_Aux_Enabled(chartInstance);
      if (chartInstance->c105_b_is_Enabled != c105_IN_Offset_Left) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c105_sfEvent);
      }
      break;

     case c105_IN_Mode_Offset_None:
      CV_STATE_EVAL(16, 0, c105_IN_Mode_Offset_None);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 164U,
                   chartInstance->c105_sfEvent);
      c105_b_out = (CV_TRANSITION_EVAL(164U, (int32_T)(_SFD_CCP_CALL(5U, 164U, 0,
        *chartInstance->c105_change_RightControlMode != 0U,
        chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 164U, chartInstance->c105_sfEvent);
        c105_set_state_Buzzer(chartInstance, 0,
                              chartInstance->c105_TRIPLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        *chartInstance->c105_display_request = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
        *chartInstance->c105_flag_AuxEnableFlash = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                              15U);
        chartInstance->c105_b_tp_Mode_Offset_None = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_Offset_Left = c105_IN_Mode_Offset_None;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c105_sfEvent);
        chartInstance->c105_temporalCounter_i1 = 0U;
        chartInstance->c105_b_tp_Mode_Offset_None = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_OFFSET;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 166U,
                     chartInstance->c105_sfEvent);
        c105_d_out = (CV_TRANSITION_EVAL(166U, (int32_T)(_SFD_CCP_CALL(5U, 166U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 166U, 0, (real_T)
          *chartInstance->c105_state_AuxEnable, (real_T)
          chartInstance->c105_INACTIVE, 0, 1U,
          *chartInstance->c105_state_AuxEnable != chartInstance->c105_INACTIVE)
          != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 166U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Mode_Offset_None = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c105_sfEvent);
          chartInstance->c105_is_Offset_Left = c105_IN_Aux_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Aux_Enabled = 1U;
          *chartInstance->c105_flag_AuxEnableFlash = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                                15U);
          c105_b_enter_internal_Aux_Enabled(chartInstance);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 20U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          *chartInstance->c105_check_RightNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          *chartInstance->c105_aux_inhibit = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
          if (chartInstance->c105_temporalCounter_i1 >= 10U) {
            CV_STATE_EVAL(20, 0, 2);
            *chartInstance->c105_display_request = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                  21U);
          } else {
            CV_STATE_EVAL(20, 0, 1);
          }

          if (chartInstance->c105_temporalCounter_i1 >= 200U) {
            CV_STATE_EVAL(20, 1, 2);
            *chartInstance->c105_flag_AuxEnableFlash = false;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
          } else {
            CV_STATE_EVAL(20, 1, 1);
          }
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 20U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c105_sfEvent);
      break;

     default:
      CV_STATE_EVAL(16, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c105_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c105_sfEvent);
      break;
    }
  }
}

static void c105_exit_internal_Offset_Left(SFc105_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  switch (chartInstance->c105_is_Offset_Left) {
   case c105_IN_Aux_Enabled:
    CV_STATE_EVAL(16, 1, c105_IN_Aux_Enabled);
    c105_b_exit_internal_Aux_Enabled(chartInstance);
    chartInstance->c105_b_tp_Aux_Enabled = 0U;
    chartInstance->c105_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Mode_Offset_None:
    CV_STATE_EVAL(16, 1, c105_IN_Mode_Offset_None);
    chartInstance->c105_b_tp_Mode_Offset_None = 0U;
    chartInstance->c105_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(16, 1, 0);
    chartInstance->c105_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_b_enter_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 168U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(168U, (int32_T)(_SFD_CCP_CALL(5U, 168U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 168U, 0, (real_T)c105_get_ee_ControlMode
    (chartInstance, 0), (real_T)chartInstance->c105_EE_LT_OF_A4, 0, 0U,
    c105_get_ee_ControlMode(chartInstance, 0) == chartInstance->c105_EE_LT_OF_A4)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 168U, chartInstance->c105_sfEvent);
    chartInstance->c105_b_is_Aux_Enabled = c105_IN_Mode_Offset_Aux4;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c105_sfEvent);
    chartInstance->c105_tp_Mode_Offset_Aux4 = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_AUX4;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_LT_OF_A4);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 169U, chartInstance->c105_sfEvent);
    chartInstance->c105_b_is_Aux_Enabled = c105_b_IN_Mode_Offset_Aux1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
    chartInstance->c105_b_tp_Mode_Offset_Aux1 = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_AUX1;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    *chartInstance->c105_flag_AuxEnableFlash = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash, 15U);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_LT_OF_A1);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
  }
}

static void c105_b_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_temp;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T c105_f_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 167U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(167U, (int32_T)(_SFD_CCP_CALL(5U, 167U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 167U, 0, (real_T)
    *chartInstance->c105_state_AuxEnable, (real_T)chartInstance->c105_INACTIVE,
    0, 0U, *chartInstance->c105_state_AuxEnable == chartInstance->c105_INACTIVE)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 167U, chartInstance->c105_sfEvent);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_NA_NA);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
    c105_b_exit_internal_Aux_Enabled(chartInstance);
    chartInstance->c105_b_tp_Aux_Enabled = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c105_sfEvent);
    chartInstance->c105_is_Offset_Left = c105_IN_Mode_Offset_None;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_b_tp_Mode_Offset_None = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 17U,
                 chartInstance->c105_sfEvent);
    switch (chartInstance->c105_b_is_Aux_Enabled) {
     case c105_b_IN_Mode_Offset_Aux1:
      CV_STATE_EVAL(17, 0, c105_b_IN_Mode_Offset_Aux1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 170U,
                   chartInstance->c105_sfEvent);
      c105_temp = (_SFD_CCP_CALL(5U, 170U, 0,
        *chartInstance->c105_change_RightControlMode != 0U,
        chartInstance->c105_sfEvent) != 0U);
      if (c105_temp) {
        c105_temp = (_SFD_CCP_CALL(5U, 170U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          170U, 0, (real_T)*chartInstance->c105_state_CommSecondary, (real_T)
          chartInstance->c105_NORMAL, 0, 0U,
          *chartInstance->c105_state_CommSecondary == chartInstance->c105_NORMAL)
          != 0U, chartInstance->c105_sfEvent) != 0U);
      }

      c105_c_out = (CV_TRANSITION_EVAL(170U, (int32_T)c105_temp) != 0);
      if (c105_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 170U, chartInstance->c105_sfEvent);
        *chartInstance->c105_check_RightNeutral = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                              19U);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 171U,
                     chartInstance->c105_sfEvent);
        c105_f_out = (CV_TRANSITION_EVAL(171U, (int32_T)(_SFD_CCP_CALL(5U, 171U,
          0, *chartInstance->c105_valid_RightControl != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 171U, chartInstance->c105_sfEvent);
          c105_set_state_Buzzer(chartInstance, 0,
                                chartInstance->c105_DOUBLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          chartInstance->c105_b_tp_Mode_Offset_Aux1 = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_is_Aux_Enabled = c105_IN_Mode_Offset_Aux4;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Mode_Offset_Aux4 = 1U;
          *chartInstance->c105_mode_LeftControl =
            chartInstance->c105_MODE_LEFT_OFFSET;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                16U);
          *chartInstance->c105_mode_RightControl =
            chartInstance->c105_MODE_RIGHT_AUX4;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                17U);
          c105_set_ee_ControlMode(chartInstance, 0,
            chartInstance->c105_EE_LT_OF_A4);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 172U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Mode_Offset_Aux1 = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_is_Aux_Enabled = c105_b_IN_Mode_Offset_Aux1;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Mode_Offset_Aux1 = 1U;
          *chartInstance->c105_mode_LeftControl =
            chartInstance->c105_MODE_LEFT_OFFSET;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                16U);
          *chartInstance->c105_mode_RightControl =
            chartInstance->c105_MODE_RIGHT_AUX1;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                17U);
          *chartInstance->c105_flag_AuxEnableFlash = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                                15U);
          c105_set_ee_ControlMode(chartInstance, 0,
            chartInstance->c105_EE_LT_OF_A1);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        }
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 18U,
                     chartInstance->c105_sfEvent);
        *chartInstance->c105_check_LeftNeutral = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                              18U);
        *chartInstance->c105_check_RightNeutral = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                              19U);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 18U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c105_sfEvent);
      break;

     case c105_IN_Mode_Offset_Aux4:
      CV_STATE_EVAL(17, 0, c105_IN_Mode_Offset_Aux4);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 175U,
                   chartInstance->c105_sfEvent);
      c105_b_out = (CV_TRANSITION_EVAL(175U, (int32_T)(_SFD_CCP_CALL(5U, 175U, 0,
        *chartInstance->c105_change_RightControlMode != 0U,
        chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 175U, chartInstance->c105_sfEvent);
        *chartInstance->c105_check_RightNeutral = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                              19U);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 174U,
                     chartInstance->c105_sfEvent);
        c105_e_out = (CV_TRANSITION_EVAL(174U, (int32_T)(_SFD_CCP_CALL(5U, 174U,
          0, *chartInstance->c105_valid_RightControl != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 174U, chartInstance->c105_sfEvent);
          c105_set_state_Buzzer(chartInstance, 0,
                                chartInstance->c105_SINGLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          chartInstance->c105_tp_Mode_Offset_Aux4 = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_is_Aux_Enabled = c105_b_IN_Mode_Offset_Aux1;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Mode_Offset_Aux1 = 1U;
          *chartInstance->c105_mode_LeftControl =
            chartInstance->c105_MODE_LEFT_OFFSET;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                16U);
          *chartInstance->c105_mode_RightControl =
            chartInstance->c105_MODE_RIGHT_AUX1;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                17U);
          *chartInstance->c105_flag_AuxEnableFlash = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                                15U);
          c105_set_ee_ControlMode(chartInstance, 0,
            chartInstance->c105_EE_LT_OF_A1);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 176U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Mode_Offset_Aux4 = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_is_Aux_Enabled = c105_IN_Mode_Offset_Aux4;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Mode_Offset_Aux4 = 1U;
          *chartInstance->c105_mode_LeftControl =
            chartInstance->c105_MODE_LEFT_OFFSET;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                16U);
          *chartInstance->c105_mode_RightControl =
            chartInstance->c105_MODE_RIGHT_AUX4;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                17U);
          c105_set_ee_ControlMode(chartInstance, 0,
            chartInstance->c105_EE_LT_OF_A4);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        }
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 173U,
                     chartInstance->c105_sfEvent);
        c105_d_out = (CV_TRANSITION_EVAL(173U, (int32_T)(_SFD_CCP_CALL(5U, 173U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 173U, 0, (real_T)
          *chartInstance->c105_state_CommSecondary, (real_T)
          chartInstance->c105_NO_COMMUNICATION, 0, 0U,
          *chartInstance->c105_state_CommSecondary ==
          chartInstance->c105_NO_COMMUNICATION) != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 173U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 154U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 153U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Mode_Offset_Aux4 = 0U;
          chartInstance->c105_b_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Aux_Enabled = 0U;
          chartInstance->c105_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Offset_Left = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_is_Enabled = c105_IN_Control_Fault;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Control_Fault = 1U;
          c105_enter_atomic_Control_Fault(chartInstance);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 19U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          *chartInstance->c105_check_RightNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 19U, chartInstance->c105_sfEvent);
      if (chartInstance->c105_is_Offset_Left != c105_IN_Aux_Enabled) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c105_sfEvent);
      }
      break;

     default:
      CV_STATE_EVAL(17, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c105_b_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c105_sfEvent);
      break;
    }
  }
}

static void c105_b_exit_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c105_b_is_Aux_Enabled) {
   case c105_b_IN_Mode_Offset_Aux1:
    CV_STATE_EVAL(17, 1, c105_b_IN_Mode_Offset_Aux1);
    chartInstance->c105_b_tp_Mode_Offset_Aux1 = 0U;
    chartInstance->c105_b_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Mode_Offset_Aux4:
    CV_STATE_EVAL(17, 1, c105_IN_Mode_Offset_Aux4);
    chartInstance->c105_tp_Mode_Offset_Aux4 = 0U;
    chartInstance->c105_b_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(17, 1, 0);
    chartInstance->c105_b_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_enter_atomic_Control_Fault(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
  *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
  *chartInstance->c105_aux_inhibit = true;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
  *chartInstance->c105_flag_AuxEnableFlash = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash, 15U);
  c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_NA_NA);
  ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
  matlab_UpdateEEVar();
}

static void c105_enter_internal_Offset_Right
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 177U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(177U, (int32_T)(_SFD_CCP_CALL(5U, 177U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 177U, 0, (real_T)
    *chartInstance->c105_state_AuxEnable, (real_T)chartInstance->c105_INACTIVE,
    0, 1U, *chartInstance->c105_state_AuxEnable != chartInstance->c105_INACTIVE)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  guard1 = false;
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 177U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 179U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(179U, (int32_T)(_SFD_CCP_CALL(5U, 179U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 179U, 0, (real_T)c105_get_ee_ControlMode
      (chartInstance, 0), (real_T)chartInstance->c105_EE_RT_NA_OF, 0, 5U,
      c105_get_ee_ControlMode(chartInstance, 0) >=
      chartInstance->c105_EE_RT_NA_OF) != 0U, chartInstance->c105_sfEvent) != 0U))
                  != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 179U, chartInstance->c105_sfEvent);
      chartInstance->c105_is_Offset_Right = c105_IN_Aux_Enabled;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c105_sfEvent);
      chartInstance->c105_c_tp_Aux_Enabled = 1U;
      *chartInstance->c105_flag_AuxEnableFlash = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      c105_c_enter_internal_Aux_Enabled(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 180U, chartInstance->c105_sfEvent);
      *chartInstance->c105_aux_inhibit = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 181U, chartInstance->c105_sfEvent);
      guard1 = true;
    }
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 178U, chartInstance->c105_sfEvent);
    guard1 = true;
  }

  if (guard1) {
    chartInstance->c105_is_Offset_Right = c105_IN_Mode_None_Offset;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_tp_Mode_None_Offset = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl =
      chartInstance->c105_MODE_RIGHT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
  }
}

static void c105_Offset_Right(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_temp;
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_b_temp;
  boolean_T c105_c_temp;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 159U,
               chartInstance->c105_sfEvent);
  c105_temp = (_SFD_CCP_CALL(5U, 159U, 0,
    *chartInstance->c105_change_OffsetSelectSw != 0U,
    chartInstance->c105_sfEvent) != 0U);
  if (c105_temp) {
    c105_temp = (_SFD_CCP_CALL(5U, 159U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      159U, 0, (real_T)*chartInstance->c105_din_OffsetSelectSw, (real_T)
      chartInstance->c105_OFFSET_SELECT_LEFT, 0, 0U, (int32_T)
      *chartInstance->c105_din_OffsetSelectSw ==
      chartInstance->c105_OFFSET_SELECT_LEFT) != 0U, chartInstance->c105_sfEvent)
                 != 0U);
  }

  c105_out = (CV_TRANSITION_EVAL(159U, (int32_T)c105_temp) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 159U, chartInstance->c105_sfEvent);
    *chartInstance->c105_check_LeftNeutral = true;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 152U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 148U,
                 chartInstance->c105_sfEvent);
    c105_c_out = (CV_TRANSITION_EVAL(148U, (int32_T)(_SFD_CCP_CALL(5U, 148U, 0, *
      chartInstance->c105_valid_LeftControl != 0U, chartInstance->c105_sfEvent)
      != 0U)) != 0);
    if (c105_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 148U, chartInstance->c105_sfEvent);
      c105_set_state_Buzzer(chartInstance, 0,
                            chartInstance->c105_SINGLE_MEDIUM_BEEP);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
      *chartInstance->c105_flag_AuxEnableFlash = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      c105_exit_internal_Offset_Right(chartInstance);
      chartInstance->c105_tp_Offset_Right = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_is_Enabled = c105_IN_Offset_Left;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Offset_Left = 1U;
      c105_enter_internal_Offset_Left(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 150U, chartInstance->c105_sfEvent);
      c105_exit_internal_Offset_Right(chartInstance);
      chartInstance->c105_tp_Offset_Right = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_is_Enabled = c105_IN_Control_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Control_Fault = 1U;
      c105_enter_atomic_Control_Fault(chartInstance);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 21U,
                 chartInstance->c105_sfEvent);
    switch (chartInstance->c105_is_Offset_Right) {
     case c105_IN_Aux_Enabled:
      CV_STATE_EVAL(21, 0, c105_IN_Aux_Enabled);
      c105_c_Aux_Enabled(chartInstance);
      if (chartInstance->c105_b_is_Enabled != c105_IN_Offset_Right) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c105_sfEvent);
      }
      break;

     case c105_IN_Mode_None_Offset:
      CV_STATE_EVAL(21, 0, c105_IN_Mode_None_Offset);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 185U,
                   chartInstance->c105_sfEvent);
      c105_b_out = (CV_TRANSITION_EVAL(185U, (int32_T)(_SFD_CCP_CALL(5U, 185U, 0,
        *chartInstance->c105_change_RightControlMode != 0U,
        chartInstance->c105_sfEvent) != 0U)) != 0);
      guard1 = false;
      if (c105_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 185U, chartInstance->c105_sfEvent);
        c105_set_state_Buzzer(chartInstance, 0,
                              chartInstance->c105_TRIPLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        *chartInstance->c105_display_request = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
        *chartInstance->c105_flag_AuxEnableFlash = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                              15U);
        guard1 = true;
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 182U,
                     chartInstance->c105_sfEvent);
        c105_b_temp = (_SFD_CCP_CALL(5U, 182U, 0,
          *chartInstance->c105_change_AuxEnable != 0U,
          chartInstance->c105_sfEvent) != 0U);
        if (c105_b_temp) {
          c105_b_temp = (_SFD_CCP_CALL(5U, 182U, 1, (boolean_T)
            CV_RELATIONAL_EVAL(5U, 182U, 0, (real_T)
                               *chartInstance->c105_state_AuxEnable, (real_T)
                               chartInstance->c105_INACTIVE, 0, 1U,
                               *chartInstance->c105_state_AuxEnable !=
                               chartInstance->c105_INACTIVE) != 0U,
            chartInstance->c105_sfEvent) != 0U);
        }

        c105_c_temp = c105_b_temp;
        if (c105_b_temp) {
          c105_c_temp = (_SFD_CCP_CALL(5U, 182U, 2, (boolean_T)
            CV_RELATIONAL_EVAL(5U, 182U, 1, (real_T)
                               *chartInstance->c105_state_CommSecondary, (real_T)
                               chartInstance->c105_NORMAL, 0, 0U,
                               *chartInstance->c105_state_CommSecondary ==
                               chartInstance->c105_NORMAL) != 0U,
            chartInstance->c105_sfEvent) != 0U);
        }

        c105_d_out = (CV_TRANSITION_EVAL(182U, (int32_T)c105_c_temp) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 182U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 183U,
                       chartInstance->c105_sfEvent);
          c105_e_out = (CV_TRANSITION_EVAL(183U, (int32_T)(_SFD_CCP_CALL(5U,
            183U, 0, *chartInstance->c105_valid_LeftControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 183U,
                         chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_None_Offset = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_Offset_Right = c105_IN_Aux_Enabled;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_tp_Aux_Enabled = 1U;
            *chartInstance->c105_flag_AuxEnableFlash = false;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
            c105_c_enter_internal_Aux_Enabled(chartInstance);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 184U,
                         chartInstance->c105_sfEvent);
            *chartInstance->c105_aux_inhibit = true;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
            guard1 = true;
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 25U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          *chartInstance->c105_check_RightNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          *chartInstance->c105_aux_inhibit = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
          if (chartInstance->c105_temporalCounter_i1 >= 10U) {
            CV_STATE_EVAL(25, 0, 2);
            *chartInstance->c105_display_request = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                  21U);
          } else {
            CV_STATE_EVAL(25, 0, 1);
          }

          if (chartInstance->c105_temporalCounter_i1 >= 200U) {
            CV_STATE_EVAL(25, 1, 2);
            *chartInstance->c105_flag_AuxEnableFlash = false;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
          } else {
            CV_STATE_EVAL(25, 1, 1);
          }
        }
      }

      if (guard1) {
        chartInstance->c105_tp_Mode_None_Offset = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_Offset_Right = c105_IN_Mode_None_Offset;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c105_sfEvent);
        chartInstance->c105_temporalCounter_i1 = 0U;
        chartInstance->c105_tp_Mode_None_Offset = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_OFFSET;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 25U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c105_sfEvent);
      break;

     default:
      CV_STATE_EVAL(21, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c105_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c105_sfEvent);
      break;
    }
  }
}

static void c105_exit_internal_Offset_Right(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c105_is_Offset_Right) {
   case c105_IN_Aux_Enabled:
    CV_STATE_EVAL(21, 1, c105_IN_Aux_Enabled);
    c105_c_exit_internal_Aux_Enabled(chartInstance);
    chartInstance->c105_c_tp_Aux_Enabled = 0U;
    chartInstance->c105_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Mode_None_Offset:
    CV_STATE_EVAL(21, 1, c105_IN_Mode_None_Offset);
    chartInstance->c105_tp_Mode_None_Offset = 0U;
    chartInstance->c105_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(21, 1, 0);
    chartInstance->c105_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_c_enter_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 188U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(188U, (int32_T)(_SFD_CCP_CALL(5U, 188U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 188U, 0, (real_T)c105_get_ee_ControlMode
    (chartInstance, 0), (real_T)chartInstance->c105_EE_RT_A4_A1, 0, 0U,
    c105_get_ee_ControlMode(chartInstance, 0) == chartInstance->c105_EE_RT_A4_A1)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 188U, chartInstance->c105_sfEvent);
    chartInstance->c105_c_is_Aux_Enabled = c105_IN_Mode_Aux4_Aux1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
    chartInstance->c105_tp_Mode_Aux4_Aux1 = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_AUX4;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_AUX1;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_RT_A4_A1);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 187U, chartInstance->c105_sfEvent);
    chartInstance->c105_c_is_Aux_Enabled = c105_IN_Mode_Aux4_Offset;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_tp_Mode_Aux4_Offset = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_AUX4;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl =
      chartInstance->c105_MODE_RIGHT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    *chartInstance->c105_flag_AuxEnableFlash = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash, 15U);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_RT_A4_OF);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
  }
}

static void c105_c_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T c105_f_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 186U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(186U, (int32_T)(_SFD_CCP_CALL(5U, 186U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 186U, 0, (real_T)
    *chartInstance->c105_state_AuxEnable, (real_T)chartInstance->c105_INACTIVE,
    0, 0U, *chartInstance->c105_state_AuxEnable == chartInstance->c105_INACTIVE)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 186U, chartInstance->c105_sfEvent);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_NA_NA);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
    c105_c_exit_internal_Aux_Enabled(chartInstance);
    chartInstance->c105_c_tp_Aux_Enabled = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c105_sfEvent);
    chartInstance->c105_is_Offset_Right = c105_IN_Mode_None_Offset;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_tp_Mode_None_Offset = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl =
      chartInstance->c105_MODE_RIGHT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 155U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(155U, (int32_T)(_SFD_CCP_CALL(5U, 155U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 155U, 0, (real_T)
      *chartInstance->c105_state_CommSecondary, (real_T)
      chartInstance->c105_NO_COMMUNICATION, 0, 0U,
      *chartInstance->c105_state_CommSecondary ==
      chartInstance->c105_NO_COMMUNICATION) != 0U, chartInstance->c105_sfEvent)
      != 0U)) != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 155U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 154U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 153U, chartInstance->c105_sfEvent);
      c105_c_exit_internal_Aux_Enabled(chartInstance);
      chartInstance->c105_c_tp_Aux_Enabled = 0U;
      chartInstance->c105_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Offset_Right = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_is_Enabled = c105_IN_Control_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
      chartInstance->c105_tp_Control_Fault = 1U;
      c105_enter_atomic_Control_Fault(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 22U,
                   chartInstance->c105_sfEvent);
      switch (chartInstance->c105_c_is_Aux_Enabled) {
       case c105_IN_Mode_Aux4_Aux1:
        CV_STATE_EVAL(22, 0, c105_IN_Mode_Aux4_Aux1);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 193U,
                     chartInstance->c105_sfEvent);
        c105_c_out = (CV_TRANSITION_EVAL(193U, (int32_T)(_SFD_CCP_CALL(5U, 193U,
          0, *chartInstance->c105_change_RightControlMode != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 193U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_RightNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 192U,
                       chartInstance->c105_sfEvent);
          c105_e_out = (CV_TRANSITION_EVAL(192U, (int32_T)(_SFD_CCP_CALL(5U,
            192U, 0, *chartInstance->c105_valid_RightControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 192U,
                         chartInstance->c105_sfEvent);
            c105_set_state_Buzzer(chartInstance, 0,
                                  chartInstance->c105_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            chartInstance->c105_tp_Mode_Aux4_Aux1 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_is_Aux_Enabled = c105_IN_Mode_Aux4_Offset;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c105_sfEvent);
            chartInstance->c105_temporalCounter_i1 = 0U;
            chartInstance->c105_tp_Mode_Aux4_Offset = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_AUX4;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_OFFSET;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            *chartInstance->c105_flag_AuxEnableFlash = false;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
            c105_set_ee_ControlMode(chartInstance, 0,
              chartInstance->c105_EE_RT_A4_OF);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 194U,
                         chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Aux4_Aux1 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_is_Aux_Enabled = c105_IN_Mode_Aux4_Aux1;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Aux4_Aux1 = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_AUX4;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_AUX1;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            c105_set_ee_ControlMode(chartInstance, 0,
              chartInstance->c105_EE_RT_A4_A1);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 23U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          *chartInstance->c105_check_RightNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 23U, chartInstance->c105_sfEvent);
        break;

       case c105_IN_Mode_Aux4_Offset:
        CV_STATE_EVAL(22, 0, c105_IN_Mode_Aux4_Offset);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 189U,
                     chartInstance->c105_sfEvent);
        c105_d_out = (CV_TRANSITION_EVAL(189U, (int32_T)(_SFD_CCP_CALL(5U, 189U,
          0, *chartInstance->c105_change_RightControlMode != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 189U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_RightNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 190U,
                       chartInstance->c105_sfEvent);
          c105_f_out = (CV_TRANSITION_EVAL(190U, (int32_T)(_SFD_CCP_CALL(5U,
            190U, 0, *chartInstance->c105_valid_RightControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 190U,
                         chartInstance->c105_sfEvent);
            c105_set_state_Buzzer(chartInstance, 0,
                                  chartInstance->c105_DOUBLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            chartInstance->c105_tp_Mode_Aux4_Offset = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_is_Aux_Enabled = c105_IN_Mode_Aux4_Aux1;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Aux4_Aux1 = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_AUX4;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_AUX1;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            c105_set_ee_ControlMode(chartInstance, 0,
              chartInstance->c105_EE_RT_A4_A1);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 191U,
                         chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Aux4_Offset = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_is_Aux_Enabled = c105_IN_Mode_Aux4_Offset;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c105_sfEvent);
            chartInstance->c105_temporalCounter_i1 = 0U;
            chartInstance->c105_tp_Mode_Aux4_Offset = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_AUX4;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_OFFSET;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            *chartInstance->c105_flag_AuxEnableFlash = false;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
            c105_set_ee_ControlMode(chartInstance, 0,
              chartInstance->c105_EE_RT_A4_OF);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 24U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          *chartInstance->c105_check_RightNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          if (chartInstance->c105_temporalCounter_i1 >= 10U) {
            CV_STATE_EVAL(24, 0, 2);
            *chartInstance->c105_display_request = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                  21U);
          } else {
            CV_STATE_EVAL(24, 0, 1);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 24U, chartInstance->c105_sfEvent);
        break;

       default:
        CV_STATE_EVAL(22, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c105_c_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 22U, chartInstance->c105_sfEvent);
}

static void c105_c_exit_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c105_c_is_Aux_Enabled) {
   case c105_IN_Mode_Aux4_Aux1:
    CV_STATE_EVAL(22, 1, c105_IN_Mode_Aux4_Aux1);
    chartInstance->c105_tp_Mode_Aux4_Aux1 = 0U;
    chartInstance->c105_c_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Mode_Aux4_Offset:
    CV_STATE_EVAL(22, 1, c105_IN_Mode_Aux4_Offset);
    chartInstance->c105_tp_Mode_Aux4_Offset = 0U;
    chartInstance->c105_c_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(22, 1, 0);
    chartInstance->c105_c_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_OptionC(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_temp;
  boolean_T c105_b_out;
  boolean_T c105_b_temp;
  boolean_T c105_c_out;
  boolean_T c105_c_temp;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T c105_f_out;
  boolean_T c105_g_out;
  boolean_T c105_h_out;
  boolean_T c105_i_out;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 27U, chartInstance->c105_sfEvent);
  switch (chartInstance->c105_is_OptionC) {
   case c105_IN_Delay:
    CV_STATE_EVAL(27, 0, c105_IN_Delay);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 104U,
                 chartInstance->c105_sfEvent);
    c105_out = (CV_TRANSITION_EVAL(104U, (int32_T)(_SFD_CCP_CALL(5U, 104U, 0,
      (chartInstance->c105_temporalCounter_i1 >= 20U) != 0U,
      chartInstance->c105_sfEvent) != 0U)) != 0);
    guard1 = false;
    guard2 = false;
    if (c105_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 104U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 36U,
                   chartInstance->c105_sfEvent);
      c105_c_out = (CV_TRANSITION_EVAL(36U, (int32_T)(_SFD_CCP_CALL(5U, 36U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 36U, 0, (real_T)
        *chartInstance->c105_din_OffsetSelectSw, (real_T)
        chartInstance->c105_OFFSET_SELECT_RIGHT, 0, 0U, (int32_T)
        *chartInstance->c105_din_OffsetSelectSw ==
        chartInstance->c105_OFFSET_SELECT_RIGHT) != 0U,
        chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 32U,
                     chartInstance->c105_sfEvent);
        c105_d_out = (CV_TRANSITION_EVAL(32U, (int32_T)(_SFD_CCP_CALL(5U, 32U, 0,
          *chartInstance->c105_valid_RightControl != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
          chartInstance->c105_c_tp_Delay = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c105_sfEvent);
          chartInstance->c105_is_OptionC = c105_IN_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c105_sfEvent);
          chartInstance->c105_c_tp_Enabled = 1U;
          chartInstance->c105_c_is_Enabled = c105_IN_Offset_Right;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Offset_Right = 1U;
          c105_b_enter_internal_Offset_Right(chartInstance);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_RightNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          guard1 = true;
        }
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
        guard2 = true;
      }
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 105U,
                   chartInstance->c105_sfEvent);
      c105_b_out = (CV_TRANSITION_EVAL(105U, (int32_T)(_SFD_CCP_CALL(5U, 105U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 105U, 0, (real_T)
        *chartInstance->c105_state_CommSecondary, (real_T)
        chartInstance->c105_NO_COMMUNICATION, 0, 0U,
        *chartInstance->c105_state_CommSecondary ==
        chartInstance->c105_NO_COMMUNICATION) != 0U, chartInstance->c105_sfEvent)
        != 0U)) != 0);
      if (c105_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 105U, chartInstance->c105_sfEvent);
        guard2 = true;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 28U,
                     chartInstance->c105_sfEvent);
      }
    }

    if (guard2) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 33U,
                   chartInstance->c105_sfEvent);
      c105_e_out = (CV_TRANSITION_EVAL(33U, (int32_T)(_SFD_CCP_CALL(5U, 33U, 0, *
        chartInstance->c105_valid_LeftControl != 0U, chartInstance->c105_sfEvent)
        != 0U)) != 0);
      if (c105_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
        chartInstance->c105_c_tp_Delay = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_OptionC = c105_IN_Enabled;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c105_sfEvent);
        chartInstance->c105_c_tp_Enabled = 1U;
        chartInstance->c105_c_is_Enabled = c105_IN_Offset_Left;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_Offset_Left = 1U;
        c105_b_enter_internal_Offset_Left(chartInstance);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
        *chartInstance->c105_check_LeftNeutral = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                              18U);
        guard1 = true;
      }
    }

    if (guard1) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 91U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 92U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 93U, chartInstance->c105_sfEvent);
      chartInstance->c105_c_tp_Delay = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c105_sfEvent);
      chartInstance->c105_is_OptionC = c105_IN_Enabled;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c105_sfEvent);
      chartInstance->c105_c_tp_Enabled = 1U;
      chartInstance->c105_c_is_Enabled = c105_IN_Control_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Control_Fault = 1U;
      c105_b_enter_atomic_Control_Fault(chartInstance);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 28U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Enabled:
    CV_STATE_EVAL(27, 0, c105_IN_Enabled);
    c105_b_Enabled(chartInstance);
    break;

   case c105_IN_INIT_SystemCheck:
    CV_STATE_EVAL(27, 0, c105_IN_INIT_SystemCheck);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 35U,
                 chartInstance->c105_sfEvent);
    c105_temp = (_SFD_CCP_CALL(5U, 35U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 35U,
      0, (real_T)*chartInstance->c105_state_Console, (real_T)
      chartInstance->c105_ACTIVE, 0, 0U, *chartInstance->c105_state_Console ==
      chartInstance->c105_ACTIVE) != 0U, chartInstance->c105_sfEvent) != 0U);
    if (c105_temp) {
      c105_temp = (_SFD_CCP_CALL(5U, 35U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        35U, 1, (real_T)*chartInstance->c105_state_System, (real_T)
        chartInstance->c105_SYS_NORMAL, 0, 0U, *chartInstance->c105_state_System
        == chartInstance->c105_SYS_NORMAL) != 0U, chartInstance->c105_sfEvent)
                   != 0U);
    }

    c105_b_temp = c105_temp;
    if (c105_temp) {
      c105_b_temp = (_SFD_CCP_CALL(5U, 35U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        35U, 2, (real_T)*chartInstance->c105_state_Engine, (real_T)
        chartInstance->c105_ENGINE_CRANKING, 0, 1U,
        *chartInstance->c105_state_Engine != chartInstance->c105_ENGINE_CRANKING)
        != 0U, chartInstance->c105_sfEvent) != 0U);
    }

    c105_c_temp = c105_b_temp;
    if (c105_b_temp) {
      c105_c_temp = (_SFD_CCP_CALL(5U, 35U, 3,
        *chartInstance->c105_flag_InitEERead != 0U, chartInstance->c105_sfEvent)
                     != 0U);
    }

    c105_f_out = (CV_TRANSITION_EVAL(35U, (int32_T)c105_c_temp) != 0);
    if (c105_f_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 94U,
                   chartInstance->c105_sfEvent);
      c105_g_out = (CV_TRANSITION_EVAL(94U, (int32_T)(_SFD_CCP_CALL(5U, 94U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 94U, 0, (real_T)
        *chartInstance->c105_state_CommSecondary, (real_T)
        chartInstance->c105_NORMAL, 0, 0U,
        *chartInstance->c105_state_CommSecondary == chartInstance->c105_NORMAL)
        != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_g_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 94U, chartInstance->c105_sfEvent);
        chartInstance->c105_c_tp_INIT_SystemCheck = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c105_sfEvent);
        chartInstance->c105_is_OptionC = c105_IN_Delay;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 28U, chartInstance->c105_sfEvent);
        chartInstance->c105_temporalCounter_i1 = 0U;
        chartInstance->c105_c_tp_Delay = 1U;
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 95U, chartInstance->c105_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 96U,
                     chartInstance->c105_sfEvent);
        c105_h_out = (CV_TRANSITION_EVAL(96U, (int32_T)(_SFD_CCP_CALL(5U, 96U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 96U, 0, (real_T)
          *chartInstance->c105_state_CommSecondary, (real_T)
          chartInstance->c105_NO_COMMUNICATION, 0, 0U,
          *chartInstance->c105_state_CommSecondary ==
          chartInstance->c105_NO_COMMUNICATION) != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_h_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 96U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 33U,
                       chartInstance->c105_sfEvent);
          c105_i_out = (CV_TRANSITION_EVAL(33U, (int32_T)(_SFD_CCP_CALL(5U, 33U,
            0, *chartInstance->c105_valid_LeftControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_i_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_tp_INIT_SystemCheck = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_OptionC = c105_IN_Enabled;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_tp_Enabled = 1U;
            chartInstance->c105_c_is_Enabled = c105_IN_Offset_Left;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_Offset_Left = 1U;
            c105_b_enter_internal_Offset_Left(chartInstance);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
            *chartInstance->c105_check_LeftNeutral = true;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                  18U);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 91U, chartInstance->c105_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 92U, chartInstance->c105_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 93U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_tp_INIT_SystemCheck = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c105_sfEvent);
            chartInstance->c105_is_OptionC = c105_IN_Enabled;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_tp_Enabled = 1U;
            chartInstance->c105_c_is_Enabled = c105_IN_Control_Fault;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_Control_Fault = 1U;
            c105_b_enter_atomic_Control_Fault(chartInstance);
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 46U,
                       chartInstance->c105_sfEvent);
        }
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 46U,
                   chartInstance->c105_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 46U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(27, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c105_is_OptionC = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c105_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 27U, chartInstance->c105_sfEvent);
}

static void c105_b_enter_atomic_INIT_SystemCheck
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
  *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
  *chartInstance->c105_flag_AuxEnableFlash = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash, 15U);
  *chartInstance->c105_aux_inhibit = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
  *chartInstance->c105_display_request = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
  *chartInstance->c105_check_LeftNeutral = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
  *chartInstance->c105_check_RightNeutral = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
}

static void c105_b_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_temp;
  boolean_T c105_b_temp;
  boolean_T c105_out;
  boolean_T c105_c_temp;
  boolean_T c105_d_temp;
  boolean_T c105_b_out;
  boolean_T c105_e_temp;
  boolean_T c105_f_temp;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 39U,
               chartInstance->c105_sfEvent);
  c105_temp = (_SFD_CCP_CALL(5U, 39U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 39U,
    0, (real_T)*chartInstance->c105_state_Console, (real_T)
    chartInstance->c105_ACTIVE, 0, 1U, *chartInstance->c105_state_Console !=
    chartInstance->c105_ACTIVE) != 0U, chartInstance->c105_sfEvent) != 0U);
  if (!c105_temp) {
    c105_temp = (_SFD_CCP_CALL(5U, 39U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 39U,
      1, (real_T)*chartInstance->c105_state_System, (real_T)
      chartInstance->c105_SYS_NORMAL, 0, 1U, *chartInstance->c105_state_System
      != chartInstance->c105_SYS_NORMAL) != 0U, chartInstance->c105_sfEvent) !=
                 0U);
  }

  c105_b_temp = c105_temp;
  if (!c105_temp) {
    c105_b_temp = (_SFD_CCP_CALL(5U, 39U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      39U, 2, (real_T)*chartInstance->c105_state_Engine, (real_T)
      chartInstance->c105_ENGINE_CRANKING, 0, 0U,
      *chartInstance->c105_state_Engine == chartInstance->c105_ENGINE_CRANKING)
      != 0U, chartInstance->c105_sfEvent) != 0U);
  }

  c105_out = (CV_TRANSITION_EVAL(39U, (int32_T)c105_b_temp) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 39U, chartInstance->c105_sfEvent);
    c105_c_exit_internal_Enabled(chartInstance);
    chartInstance->c105_c_tp_Enabled = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c105_sfEvent);
    chartInstance->c105_is_OptionC = c105_IN_INIT_SystemCheck;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 46U, chartInstance->c105_sfEvent);
    chartInstance->c105_c_tp_INIT_SystemCheck = 1U;
    c105_b_enter_atomic_INIT_SystemCheck(chartInstance);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 31U,
                 chartInstance->c105_sfEvent);
    switch (chartInstance->c105_c_is_Enabled) {
     case c105_IN_Control_Fault:
      CV_STATE_EVAL(31, 0, c105_IN_Control_Fault);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 52U,
                   chartInstance->c105_sfEvent);
      c105_c_temp = (_SFD_CCP_CALL(5U, 52U, 0,
        *chartInstance->c105_change_OffsetSelectSw != 0U,
        chartInstance->c105_sfEvent) != 0U);
      if (c105_c_temp) {
        c105_c_temp = (_SFD_CCP_CALL(5U, 52U, 1, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 52U, 0, (real_T)*chartInstance->c105_din_OffsetSelectSw, (real_T)
           chartInstance->c105_OFFSET_SELECT_RIGHT, 0, 0U, (int32_T)
           *chartInstance->c105_din_OffsetSelectSw ==
           chartInstance->c105_OFFSET_SELECT_RIGHT) != 0U,
          chartInstance->c105_sfEvent) != 0U);
      }

      c105_d_temp = c105_c_temp;
      if (c105_c_temp) {
        c105_d_temp = (_SFD_CCP_CALL(5U, 52U, 2, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 52U, 1, (real_T)*chartInstance->c105_state_CommSecondary, (real_T)
           chartInstance->c105_NORMAL, 0, 0U,
           *chartInstance->c105_state_CommSecondary ==
           chartInstance->c105_NORMAL) != 0U, chartInstance->c105_sfEvent) != 0U);
      }

      c105_b_out = (CV_TRANSITION_EVAL(52U, (int32_T)c105_d_temp) != 0);
      guard1 = false;
      if (c105_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 52U, chartInstance->c105_sfEvent);
        *chartInstance->c105_check_RightNeutral = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                              19U);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 51U, chartInstance->c105_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 49U,
                     chartInstance->c105_sfEvent);
        c105_c_out = (CV_TRANSITION_EVAL(49U, (int32_T)(_SFD_CCP_CALL(5U, 49U, 0,
          *chartInstance->c105_valid_RightControl != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 49U, chartInstance->c105_sfEvent);
          c105_set_state_Buzzer(chartInstance, 0,
                                chartInstance->c105_SINGLE_MEDIUM_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          *chartInstance->c105_flag_AuxEnableFlash = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                                15U);
          chartInstance->c105_b_tp_Control_Fault = 0U;
          _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 32U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_aux_inhibit = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 32U,
                       chartInstance->c105_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
          chartInstance->c105_c_is_Enabled = c105_IN_Offset_Right;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Offset_Right = 1U;
          c105_b_enter_internal_Offset_Right(chartInstance);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 50U, chartInstance->c105_sfEvent);
          guard1 = true;
        }
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 53U,
                     chartInstance->c105_sfEvent);
        c105_e_temp = (_SFD_CCP_CALL(5U, 53U, 0,
          *chartInstance->c105_change_OffsetSelectSw != 0U,
          chartInstance->c105_sfEvent) != 0U);
        if (c105_e_temp) {
          c105_e_temp = (_SFD_CCP_CALL(5U, 53U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 53U, 0, (real_T)*chartInstance->c105_din_OffsetSelectSw,
             (real_T)chartInstance->c105_OFFSET_SELECT_LEFT, 0, 0U, (int32_T)
             *chartInstance->c105_din_OffsetSelectSw ==
             chartInstance->c105_OFFSET_SELECT_LEFT) != 0U,
            chartInstance->c105_sfEvent) != 0U);
        }

        c105_f_temp = c105_e_temp;
        if (c105_e_temp) {
          c105_f_temp = (_SFD_CCP_CALL(5U, 53U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 53U, 1, (real_T)*chartInstance->c105_state_CommSecondary,
             (real_T)chartInstance->c105_NORMAL, 0, 0U,
             *chartInstance->c105_state_CommSecondary ==
             chartInstance->c105_NORMAL) != 0U, chartInstance->c105_sfEvent) !=
                         0U);
        }

        c105_d_out = (CV_TRANSITION_EVAL(53U, (int32_T)c105_f_temp) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 53U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 46U, chartInstance->c105_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 47U,
                       chartInstance->c105_sfEvent);
          c105_e_out = (CV_TRANSITION_EVAL(47U, (int32_T)(_SFD_CCP_CALL(5U, 47U,
            0, *chartInstance->c105_valid_LeftControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 47U, chartInstance->c105_sfEvent);
            c105_set_state_Buzzer(chartInstance, 0,
                                  chartInstance->c105_SINGLE_MEDIUM_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            *chartInstance->c105_flag_AuxEnableFlash = true;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
            chartInstance->c105_b_tp_Control_Fault = 0U;
            _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 32U,
                         chartInstance->c105_sfEvent);
            *chartInstance->c105_aux_inhibit = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 32U,
                         chartInstance->c105_sfEvent);
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_is_Enabled = c105_IN_Offset_Left;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_Offset_Left = 1U;
            c105_b_enter_internal_Offset_Left(chartInstance);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 45U, chartInstance->c105_sfEvent);
            guard1 = true;
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 32U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          *chartInstance->c105_check_RightNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
        }
      }

      if (guard1) {
        chartInstance->c105_b_tp_Control_Fault = 0U;
        _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 32U,
                     chartInstance->c105_sfEvent);
        *chartInstance->c105_aux_inhibit = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 32U, chartInstance->c105_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
        chartInstance->c105_c_is_Enabled = c105_IN_Control_Fault;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_Control_Fault = 1U;
        c105_b_enter_atomic_Control_Fault(chartInstance);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 32U, chartInstance->c105_sfEvent);
      break;

     case c105_IN_Offset_Left:
      CV_STATE_EVAL(31, 0, c105_IN_Offset_Left);
      c105_b_Offset_Left(chartInstance);
      break;

     case c105_IN_Offset_Right:
      CV_STATE_EVAL(31, 0, c105_IN_Offset_Right);
      c105_b_Offset_Right(chartInstance);
      break;

     default:
      CV_STATE_EVAL(31, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c105_c_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
      break;
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 31U, chartInstance->c105_sfEvent);
}

static void c105_c_exit_internal_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c105_c_is_Enabled) {
   case c105_IN_Control_Fault:
    CV_STATE_EVAL(31, 1, c105_IN_Control_Fault);
    chartInstance->c105_b_tp_Control_Fault = 0U;
    _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 32U, chartInstance->c105_sfEvent);
    *chartInstance->c105_aux_inhibit = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 32U, chartInstance->c105_sfEvent);
    chartInstance->c105_c_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Offset_Left:
    CV_STATE_EVAL(31, 1, c105_IN_Offset_Left);
    c105_b_exit_internal_Offset_Left(chartInstance);
    chartInstance->c105_b_tp_Offset_Left = 0U;
    chartInstance->c105_c_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Offset_Right:
    CV_STATE_EVAL(31, 1, c105_IN_Offset_Right);
    c105_b_exit_internal_Offset_Right(chartInstance);
    chartInstance->c105_b_tp_Offset_Right = 0U;
    chartInstance->c105_c_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(31, 1, 0);
    chartInstance->c105_c_is_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_b_enter_internal_Offset_Left
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(13U, (int32_T)(_SFD_CCP_CALL(5U, 13U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 13U, 0, (real_T)
    *chartInstance->c105_state_AuxEnable, (real_T)chartInstance->c105_INACTIVE,
    0, 1U, *chartInstance->c105_state_AuxEnable != chartInstance->c105_INACTIVE)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  guard1 = false;
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 121U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(121U, (int32_T)(_SFD_CCP_CALL(5U, 121U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 121U, 0, (real_T)c105_get_ee_ControlMode
      (chartInstance, 0), (real_T)chartInstance->c105_EE_RT_NA_OF, 0, 2U,
      c105_get_ee_ControlMode(chartInstance, 0) <
      chartInstance->c105_EE_RT_NA_OF) != 0U, chartInstance->c105_sfEvent) != 0U))
                  != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 121U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_is_Offset_Left = c105_IN_Aux_Enabled;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
      chartInstance->c105_d_tp_Aux_Enabled = 1U;
      *chartInstance->c105_flag_AuxEnableFlash = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      c105_d_enter_internal_Aux_Enabled(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 123U, chartInstance->c105_sfEvent);
      *chartInstance->c105_aux_inhibit = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 122U, chartInstance->c105_sfEvent);
      guard1 = true;
    }
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 114U, chartInstance->c105_sfEvent);
    guard1 = true;
  }

  if (guard1) {
    chartInstance->c105_b_is_Offset_Left = c105_IN_Mode_Offset_None;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_c_tp_Mode_Offset_None = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    c105_DiverterFaultOverrideLeft(chartInstance);
  }
}

static void c105_b_Offset_Left(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_temp;
  boolean_T c105_b_temp;
  boolean_T c105_out;
  boolean_T c105_c_temp;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 48U,
               chartInstance->c105_sfEvent);
  c105_temp = (_SFD_CCP_CALL(5U, 48U, 0,
    *chartInstance->c105_change_OffsetSelectSw != 0U,
    chartInstance->c105_sfEvent) != 0U);
  if (c105_temp) {
    c105_temp = (_SFD_CCP_CALL(5U, 48U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 48U,
      0, (real_T)*chartInstance->c105_din_OffsetSelectSw, (real_T)
      chartInstance->c105_OFFSET_SELECT_RIGHT, 0, 0U, (int32_T)
      *chartInstance->c105_din_OffsetSelectSw ==
      chartInstance->c105_OFFSET_SELECT_RIGHT) != 0U,
      chartInstance->c105_sfEvent) != 0U);
  }

  c105_b_temp = c105_temp;
  if (c105_temp) {
    c105_b_temp = (_SFD_CCP_CALL(5U, 48U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      48U, 1, (real_T)*chartInstance->c105_state_CommSecondary, (real_T)
      chartInstance->c105_NORMAL, 0, 0U,
      *chartInstance->c105_state_CommSecondary == chartInstance->c105_NORMAL) !=
      0U, chartInstance->c105_sfEvent) != 0U);
  }

  c105_out = (CV_TRANSITION_EVAL(48U, (int32_T)c105_b_temp) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 48U, chartInstance->c105_sfEvent);
    *chartInstance->c105_check_RightNeutral = true;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 51U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 49U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(49U, (int32_T)(_SFD_CCP_CALL(5U, 49U, 0,
      *chartInstance->c105_valid_RightControl != 0U, chartInstance->c105_sfEvent)
      != 0U)) != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 49U, chartInstance->c105_sfEvent);
      c105_set_state_Buzzer(chartInstance, 0,
                            chartInstance->c105_SINGLE_MEDIUM_BEEP);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
      *chartInstance->c105_flag_AuxEnableFlash = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      c105_b_exit_internal_Offset_Left(chartInstance);
      chartInstance->c105_b_tp_Offset_Left = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
      chartInstance->c105_c_is_Enabled = c105_IN_Offset_Right;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Offset_Right = 1U;
      c105_b_enter_internal_Offset_Right(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 50U, chartInstance->c105_sfEvent);
      c105_b_exit_internal_Offset_Left(chartInstance);
      chartInstance->c105_b_tp_Offset_Left = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
      chartInstance->c105_c_is_Enabled = c105_IN_Control_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Control_Fault = 1U;
      c105_b_enter_atomic_Control_Fault(chartInstance);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 33U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 33U,
                 chartInstance->c105_sfEvent);
    switch (chartInstance->c105_b_is_Offset_Left) {
     case c105_IN_Aux_Enabled:
      CV_STATE_EVAL(33, 0, c105_IN_Aux_Enabled);
      c105_d_Aux_Enabled(chartInstance);
      if (chartInstance->c105_c_is_Enabled != c105_IN_Offset_Left) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 33U, chartInstance->c105_sfEvent);
      }
      break;

     case c105_IN_Mode_Offset_None:
      CV_STATE_EVAL(33, 0, c105_IN_Mode_Offset_None);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                   chartInstance->c105_sfEvent);
      c105_c_temp = (_SFD_CCP_CALL(5U, 15U, 0,
        *chartInstance->c105_change_LeftControlMode != 0U,
        chartInstance->c105_sfEvent) != 0U);
      if (!c105_c_temp) {
        c105_c_temp = (_SFD_CCP_CALL(5U, 15U, 1,
          *chartInstance->c105_change_RightControlMode != 0U,
          chartInstance->c105_sfEvent) != 0U);
      }

      c105_c_out = (CV_TRANSITION_EVAL(15U, (int32_T)c105_c_temp) != 0);
      if (c105_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c105_sfEvent);
        c105_set_state_Buzzer(chartInstance, 0,
                              chartInstance->c105_TRIPLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        *chartInstance->c105_display_request = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
        *chartInstance->c105_flag_AuxEnableFlash = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                              15U);
        chartInstance->c105_c_tp_Mode_Offset_None = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_is_Offset_Left = c105_IN_Mode_Offset_None;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c105_sfEvent);
        chartInstance->c105_temporalCounter_i1 = 0U;
        chartInstance->c105_c_tp_Mode_Offset_None = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_OFFSET;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        c105_DiverterFaultOverrideLeft(chartInstance);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 14U,
                     chartInstance->c105_sfEvent);
        c105_d_out = (CV_TRANSITION_EVAL(14U, (int32_T)(_SFD_CCP_CALL(5U, 14U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 14U, 0, (real_T)
          *chartInstance->c105_state_AuxEnable, (real_T)
          chartInstance->c105_INACTIVE, 0, 1U,
          *chartInstance->c105_state_AuxEnable != chartInstance->c105_INACTIVE)
          != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c105_sfEvent);
          chartInstance->c105_c_tp_Mode_Offset_None = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_is_Offset_Left = c105_IN_Aux_Enabled;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
          chartInstance->c105_d_tp_Aux_Enabled = 1U;
          *chartInstance->c105_flag_AuxEnableFlash = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                                15U);
          c105_d_enter_internal_Aux_Enabled(chartInstance);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 39U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          *chartInstance->c105_check_RightNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          *chartInstance->c105_aux_inhibit = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
          c105_DiverterFaultOverrideLeft(chartInstance);
          if (chartInstance->c105_temporalCounter_i1 >= 10U) {
            CV_STATE_EVAL(39, 0, 2);
            *chartInstance->c105_display_request = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                  21U);
          } else {
            CV_STATE_EVAL(39, 0, 1);
          }

          if (chartInstance->c105_temporalCounter_i1 >= 200U) {
            CV_STATE_EVAL(39, 1, 2);
            *chartInstance->c105_flag_AuxEnableFlash = false;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
          } else {
            CV_STATE_EVAL(39, 1, 1);
          }
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 39U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 33U, chartInstance->c105_sfEvent);
      break;

     default:
      CV_STATE_EVAL(33, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c105_b_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 33U, chartInstance->c105_sfEvent);
      break;
    }
  }
}

static void c105_b_exit_internal_Offset_Left
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c105_b_is_Offset_Left) {
   case c105_IN_Aux_Enabled:
    CV_STATE_EVAL(33, 1, c105_IN_Aux_Enabled);
    c105_d_exit_internal_Aux_Enabled(chartInstance);
    chartInstance->c105_d_tp_Aux_Enabled = 0U;
    chartInstance->c105_b_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Mode_Offset_None:
    CV_STATE_EVAL(33, 1, c105_IN_Mode_Offset_None);
    chartInstance->c105_c_tp_Mode_Offset_None = 0U;
    chartInstance->c105_b_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(33, 1, 0);
    chartInstance->c105_b_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_d_enter_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 115U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(115U, (int32_T)(_SFD_CCP_CALL(5U, 115U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 115U, 0, (real_T)c105_get_ee_ControlMode
    (chartInstance, 0), (real_T)chartInstance->c105_EE_LT_OF_A4, 0, 0U,
    c105_get_ee_ControlMode(chartInstance, 0) == chartInstance->c105_EE_LT_OF_A4)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 115U, chartInstance->c105_sfEvent);
    chartInstance->c105_d_is_Aux_Enabled = c105_b_IN_Mode_Offset_Aux4;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
    chartInstance->c105_b_tp_Mode_Offset_Aux4 = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_AUX4;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_LT_OF_A4);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
    c105_DiverterFaultOverrideLeft(chartInstance);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 116U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(116U, (int32_T)(_SFD_CCP_CALL(5U, 116U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 116U, 0, (real_T)c105_get_ee_ControlMode
      (chartInstance, 0), (real_T)chartInstance->c105_EE_LT_A2_A1, 0, 0U,
      c105_get_ee_ControlMode(chartInstance, 0) ==
      chartInstance->c105_EE_LT_A2_A1) != 0U, chartInstance->c105_sfEvent) != 0U))
                  != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 116U, chartInstance->c105_sfEvent);
      chartInstance->c105_d_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux1;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Mode_Aux2_Aux1 = 1U;
      *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_AUX2;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
      *chartInstance->c105_mode_RightControl =
        chartInstance->c105_MODE_RIGHT_AUX1;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
      c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_LT_A2_A1);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      matlab_UpdateEEVar();
      c105_DiverterFaultOverrideLeft(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 117U,
                   chartInstance->c105_sfEvent);
      c105_c_out = (CV_TRANSITION_EVAL(117U, (int32_T)(_SFD_CCP_CALL(5U, 117U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 117U, 0, (real_T)
        c105_get_ee_ControlMode(chartInstance, 0), (real_T)
        chartInstance->c105_EE_LT_A2_A4, 0, 0U, c105_get_ee_ControlMode
        (chartInstance, 0) == chartInstance->c105_EE_LT_A2_A4) != 0U,
        chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 117U, chartInstance->c105_sfEvent);
        chartInstance->c105_d_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux4;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Mode_Aux2_Aux4 = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_AUX2;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_AUX4;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        c105_set_ee_ControlMode(chartInstance, 0,
          chartInstance->c105_EE_LT_A2_A4);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
        c105_DiverterFaultOverrideLeft(chartInstance);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c105_sfEvent);
        chartInstance->c105_d_is_Aux_Enabled = c105_c_IN_Mode_Offset_Aux1;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
        chartInstance->c105_c_tp_Mode_Offset_Aux1 = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_OFFSET;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_AUX1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        c105_set_ee_ControlMode(chartInstance, 0,
          chartInstance->c105_EE_LT_OF_A1);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
        c105_DiverterFaultOverrideLeft(chartInstance);
      }
    }
  }
}

static void c105_d_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_temp;
  boolean_T c105_b_temp;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_c_temp;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T c105_f_out;
  boolean_T c105_g_out;
  boolean_T c105_h_out;
  boolean_T c105_i_out;
  boolean_T c105_j_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 16U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(16U, (int32_T)(_SFD_CCP_CALL(5U, 16U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 16U, 0, (real_T)
    *chartInstance->c105_state_AuxEnable, (real_T)chartInstance->c105_INACTIVE,
    0, 0U, *chartInstance->c105_state_AuxEnable == chartInstance->c105_INACTIVE)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c105_sfEvent);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_NA_NA);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
    c105_d_exit_internal_Aux_Enabled(chartInstance);
    chartInstance->c105_d_tp_Aux_Enabled = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
    chartInstance->c105_b_is_Offset_Left = c105_IN_Mode_Offset_None;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_c_tp_Mode_Offset_None = 1U;
    c105_enter_atomic_Mode_Offset_None(chartInstance);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 34U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 34U,
                 chartInstance->c105_sfEvent);
    switch (chartInstance->c105_d_is_Aux_Enabled) {
     case c105_IN_Mode_Aux2_Aux1:
      CV_STATE_EVAL(34, 0, c105_IN_Mode_Aux2_Aux1);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 64U,
                   chartInstance->c105_sfEvent);
      c105_temp = (_SFD_CCP_CALL(5U, 64U, 0,
        *chartInstance->c105_change_RightControlMode != 0U,
        chartInstance->c105_sfEvent) != 0U);
      if (c105_temp) {
        c105_temp = (_SFD_CCP_CALL(5U, 64U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          64U, 0, (real_T)*chartInstance->c105_state_CommSecondary, (real_T)
          chartInstance->c105_NORMAL, 0, 0U,
          *chartInstance->c105_state_CommSecondary == chartInstance->c105_NORMAL)
          != 0U, chartInstance->c105_sfEvent) != 0U);
      }

      c105_b_out = (CV_TRANSITION_EVAL(64U, (int32_T)c105_temp) != 0);
      guard1 = false;
      if (c105_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 64U, chartInstance->c105_sfEvent);
        *chartInstance->c105_check_RightNeutral = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                              19U);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 60U,
                     chartInstance->c105_sfEvent);
        c105_f_out = (CV_TRANSITION_EVAL(60U, (int32_T)(_SFD_CCP_CALL(5U, 60U, 0,
          *chartInstance->c105_valid_RightControl != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 60U, chartInstance->c105_sfEvent);
          c105_set_state_Buzzer(chartInstance, 0,
                                chartInstance->c105_DOUBLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          chartInstance->c105_b_tp_Mode_Aux2_Aux1 = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
          chartInstance->c105_d_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux4;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
          chartInstance->c105_tp_Mode_Aux2_Aux4 = 1U;
          *chartInstance->c105_mode_LeftControl =
            chartInstance->c105_MODE_LEFT_AUX2;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                16U);
          *chartInstance->c105_mode_RightControl =
            chartInstance->c105_MODE_RIGHT_AUX4;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                17U);
          c105_set_ee_ControlMode(chartInstance, 0,
            chartInstance->c105_EE_LT_A2_A4);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
          c105_DiverterFaultOverrideLeft(chartInstance);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 61U, chartInstance->c105_sfEvent);
          guard1 = true;
        }
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 68U,
                     chartInstance->c105_sfEvent);
        c105_c_temp = (_SFD_CCP_CALL(5U, 68U, 0,
          *chartInstance->c105_change_LeftControlMode != 0U,
          chartInstance->c105_sfEvent) != 0U);
        if (c105_c_temp) {
          c105_c_temp = !(_SFD_CCP_CALL(5U, 68U, 1,
            *chartInstance->c105_fault_Diverter != 0U,
            chartInstance->c105_sfEvent) != 0U);
        }

        c105_e_out = (CV_TRANSITION_EVAL(68U, (int32_T)c105_c_temp) != 0);
        if (c105_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 68U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 21U,
                       chartInstance->c105_sfEvent);
          c105_j_out = (CV_TRANSITION_EVAL(21U, (int32_T)(_SFD_CCP_CALL(5U, 21U,
            0, *chartInstance->c105_valid_LeftControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_j_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c105_sfEvent);
            c105_set_state_Buzzer(chartInstance, 0,
                                  chartInstance->c105_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            chartInstance->c105_b_tp_Mode_Aux2_Aux1 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
            chartInstance->c105_d_is_Aux_Enabled = c105_c_IN_Mode_Offset_Aux1;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_tp_Mode_Offset_Aux1 = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_OFFSET;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_AUX1;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            c105_set_ee_ControlMode(chartInstance, 0,
              chartInstance->c105_EE_LT_OF_A1);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
            c105_DiverterFaultOverrideLeft(chartInstance);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 69U, chartInstance->c105_sfEvent);
            guard1 = true;
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 35U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          *chartInstance->c105_check_RightNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          c105_DiverterFaultOverrideLeft(chartInstance);
        }
      }

      if (guard1) {
        chartInstance->c105_b_tp_Mode_Aux2_Aux1 = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
        chartInstance->c105_d_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux1;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_Mode_Aux2_Aux1 = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_AUX2;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_AUX1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        c105_set_ee_ControlMode(chartInstance, 0,
          chartInstance->c105_EE_LT_A2_A1);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
        c105_DiverterFaultOverrideLeft(chartInstance);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 35U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 34U, chartInstance->c105_sfEvent);
      break;

     case c105_IN_Mode_Aux2_Aux4:
      CV_STATE_EVAL(34, 0, c105_IN_Mode_Aux2_Aux4);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 74U,
                   chartInstance->c105_sfEvent);
      c105_b_temp = (_SFD_CCP_CALL(5U, 74U, 0,
        *chartInstance->c105_change_LeftControlMode != 0U,
        chartInstance->c105_sfEvent) != 0U);
      if (c105_b_temp) {
        c105_b_temp = !(_SFD_CCP_CALL(5U, 74U, 1,
          *chartInstance->c105_fault_Diverter != 0U, chartInstance->c105_sfEvent)
                        != 0U);
      }

      c105_c_out = (CV_TRANSITION_EVAL(74U, (int32_T)c105_b_temp) != 0);
      guard1 = false;
      if (c105_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 74U, chartInstance->c105_sfEvent);
        *chartInstance->c105_check_LeftNeutral = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                              18U);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 72U,
                     chartInstance->c105_sfEvent);
        c105_h_out = (CV_TRANSITION_EVAL(72U, (int32_T)(_SFD_CCP_CALL(5U, 72U, 0,
          *chartInstance->c105_valid_LeftControl != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_h_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 72U, chartInstance->c105_sfEvent);
          c105_set_state_Buzzer(chartInstance, 0,
                                chartInstance->c105_SINGLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          chartInstance->c105_tp_Mode_Aux2_Aux4 = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
          chartInstance->c105_d_is_Aux_Enabled = c105_b_IN_Mode_Offset_Aux4;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Mode_Offset_Aux4 = 1U;
          *chartInstance->c105_mode_LeftControl =
            chartInstance->c105_MODE_LEFT_OFFSET;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                16U);
          *chartInstance->c105_mode_RightControl =
            chartInstance->c105_MODE_RIGHT_AUX4;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                17U);
          c105_set_ee_ControlMode(chartInstance, 0,
            chartInstance->c105_EE_LT_OF_A4);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
          c105_DiverterFaultOverrideLeft(chartInstance);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 75U, chartInstance->c105_sfEvent);
          guard1 = true;
        }
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 65U,
                     chartInstance->c105_sfEvent);
        c105_d_out = (CV_TRANSITION_EVAL(65U, (int32_T)(_SFD_CCP_CALL(5U, 65U, 0,
          *chartInstance->c105_change_RightControlMode != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 65U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_RightNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 62U,
                       chartInstance->c105_sfEvent);
          c105_i_out = (CV_TRANSITION_EVAL(62U, (int32_T)(_SFD_CCP_CALL(5U, 62U,
            0, *chartInstance->c105_valid_RightControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_i_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 62U, chartInstance->c105_sfEvent);
            c105_set_state_Buzzer(chartInstance, 0,
                                  chartInstance->c105_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            chartInstance->c105_tp_Mode_Aux2_Aux4 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
            chartInstance->c105_d_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux1;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_Mode_Aux2_Aux1 = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_AUX2;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_AUX1;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            c105_set_ee_ControlMode(chartInstance, 0,
              chartInstance->c105_EE_LT_A2_A1);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
            c105_DiverterFaultOverrideLeft(chartInstance);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 63U, chartInstance->c105_sfEvent);
            guard1 = true;
          }
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 97U,
                       chartInstance->c105_sfEvent);
          c105_g_out = (CV_TRANSITION_EVAL(97U, (int32_T)(_SFD_CCP_CALL(5U, 97U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 97U, 0, (real_T)
            *chartInstance->c105_state_CommSecondary, (real_T)
            chartInstance->c105_NO_COMMUNICATION, 0, 0U,
            *chartInstance->c105_state_CommSecondary ==
            chartInstance->c105_NO_COMMUNICATION) != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 97U, chartInstance->c105_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 98U, chartInstance->c105_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 99U, chartInstance->c105_sfEvent);
            chartInstance->c105_tp_Mode_Aux2_Aux4 = 0U;
            chartInstance->c105_d_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
            chartInstance->c105_d_tp_Aux_Enabled = 0U;
            chartInstance->c105_b_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_Offset_Left = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
            chartInstance->c105_c_is_Enabled = c105_IN_Control_Fault;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_Control_Fault = 1U;
            c105_b_enter_atomic_Control_Fault(chartInstance);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 36U,
                         chartInstance->c105_sfEvent);
            *chartInstance->c105_check_LeftNeutral = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                  18U);
            *chartInstance->c105_check_RightNeutral = false;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_check_RightNeutral, 19U);
            c105_DiverterFaultOverrideLeft(chartInstance);
          }
        }
      }

      if (guard1) {
        chartInstance->c105_tp_Mode_Aux2_Aux4 = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
        chartInstance->c105_d_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux4;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Mode_Aux2_Aux4 = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_AUX2;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_AUX4;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        c105_set_ee_ControlMode(chartInstance, 0,
          chartInstance->c105_EE_LT_A2_A4);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
        c105_DiverterFaultOverrideLeft(chartInstance);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 36U, chartInstance->c105_sfEvent);
      if (chartInstance->c105_b_is_Offset_Left != c105_IN_Aux_Enabled) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 34U, chartInstance->c105_sfEvent);
      }
      break;

     case c105_c_IN_Mode_Offset_Aux1:
      CV_STATE_EVAL(34, 0, c105_c_IN_Mode_Offset_Aux1);
      c105_Mode_Offset_Aux1(chartInstance);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 34U, chartInstance->c105_sfEvent);
      break;

     case c105_b_IN_Mode_Offset_Aux4:
      CV_STATE_EVAL(34, 0, c105_b_IN_Mode_Offset_Aux4);
      c105_Mode_Offset_Aux4(chartInstance);
      if (chartInstance->c105_b_is_Offset_Left != c105_IN_Aux_Enabled) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 34U, chartInstance->c105_sfEvent);
      }
      break;

     default:
      CV_STATE_EVAL(34, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c105_d_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 34U, chartInstance->c105_sfEvent);
      break;
    }
  }
}

static void c105_d_exit_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c105_d_is_Aux_Enabled) {
   case c105_IN_Mode_Aux2_Aux1:
    CV_STATE_EVAL(34, 1, c105_IN_Mode_Aux2_Aux1);
    chartInstance->c105_b_tp_Mode_Aux2_Aux1 = 0U;
    chartInstance->c105_d_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Mode_Aux2_Aux4:
    CV_STATE_EVAL(34, 1, c105_IN_Mode_Aux2_Aux4);
    chartInstance->c105_tp_Mode_Aux2_Aux4 = 0U;
    chartInstance->c105_d_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
    break;

   case c105_c_IN_Mode_Offset_Aux1:
    CV_STATE_EVAL(34, 1, c105_c_IN_Mode_Offset_Aux1);
    chartInstance->c105_c_tp_Mode_Offset_Aux1 = 0U;
    chartInstance->c105_d_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
    break;

   case c105_b_IN_Mode_Offset_Aux4:
    CV_STATE_EVAL(34, 1, c105_b_IN_Mode_Offset_Aux4);
    chartInstance->c105_b_tp_Mode_Offset_Aux4 = 0U;
    chartInstance->c105_d_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(34, 1, 0);
    chartInstance->c105_d_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_Mode_Offset_Aux4(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_temp;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 59U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(59U, (int32_T)(_SFD_CCP_CALL(5U, 59U, 0,
    *chartInstance->c105_change_RightControlMode != 0U,
    chartInstance->c105_sfEvent) != 0U)) != 0);
  guard1 = false;
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 59U, chartInstance->c105_sfEvent);
    *chartInstance->c105_check_RightNeutral = true;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 57U,
                 chartInstance->c105_sfEvent);
    c105_c_out = (CV_TRANSITION_EVAL(57U, (int32_T)(_SFD_CCP_CALL(5U, 57U, 0,
      *chartInstance->c105_valid_RightControl != 0U, chartInstance->c105_sfEvent)
      != 0U)) != 0);
    if (c105_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 57U, chartInstance->c105_sfEvent);
      c105_set_state_Buzzer(chartInstance, 0,
                            chartInstance->c105_SINGLE_SHORT_BEEP);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
      chartInstance->c105_b_tp_Mode_Offset_Aux4 = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
      chartInstance->c105_d_is_Aux_Enabled = c105_c_IN_Mode_Offset_Aux1;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
      chartInstance->c105_c_tp_Mode_Offset_Aux1 = 1U;
      *chartInstance->c105_mode_LeftControl =
        chartInstance->c105_MODE_LEFT_OFFSET;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
      *chartInstance->c105_mode_RightControl =
        chartInstance->c105_MODE_RIGHT_AUX1;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
      c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_LT_OF_A1);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      matlab_UpdateEEVar();
      c105_DiverterFaultOverrideLeft(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 58U, chartInstance->c105_sfEvent);
      guard1 = true;
    }
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 71U,
                 chartInstance->c105_sfEvent);
    c105_temp = (_SFD_CCP_CALL(5U, 71U, 0,
      *chartInstance->c105_change_LeftControlMode != 0U,
      chartInstance->c105_sfEvent) != 0U);
    if (c105_temp) {
      c105_temp = !(_SFD_CCP_CALL(5U, 71U, 1,
        *chartInstance->c105_fault_Diverter != 0U, chartInstance->c105_sfEvent)
                    != 0U);
    }

    c105_b_out = (CV_TRANSITION_EVAL(71U, (int32_T)c105_temp) != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 71U, chartInstance->c105_sfEvent);
      *chartInstance->c105_check_LeftNeutral = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 70U,
                   chartInstance->c105_sfEvent);
      c105_e_out = (CV_TRANSITION_EVAL(70U, (int32_T)(_SFD_CCP_CALL(5U, 70U, 0, *
        chartInstance->c105_valid_LeftControl != 0U, chartInstance->c105_sfEvent)
        != 0U)) != 0);
      if (c105_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 70U, chartInstance->c105_sfEvent);
        c105_set_state_Buzzer(chartInstance, 0,
                              chartInstance->c105_DOUBLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        chartInstance->c105_b_tp_Mode_Offset_Aux4 = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
        chartInstance->c105_d_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux4;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c105_sfEvent);
        chartInstance->c105_tp_Mode_Aux2_Aux4 = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_AUX2;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_AUX4;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        c105_set_ee_ControlMode(chartInstance, 0,
          chartInstance->c105_EE_LT_A2_A4);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
        c105_DiverterFaultOverrideLeft(chartInstance);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 73U, chartInstance->c105_sfEvent);
        guard1 = true;
      }
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 100U,
                   chartInstance->c105_sfEvent);
      c105_d_out = (CV_TRANSITION_EVAL(100U, (int32_T)(_SFD_CCP_CALL(5U, 100U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 100U, 0, (real_T)
        *chartInstance->c105_state_CommSecondary, (real_T)
        chartInstance->c105_NO_COMMUNICATION, 0, 0U,
        *chartInstance->c105_state_CommSecondary ==
        chartInstance->c105_NO_COMMUNICATION) != 0U, chartInstance->c105_sfEvent)
        != 0U)) != 0);
      if (c105_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 100U, chartInstance->c105_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 101U, chartInstance->c105_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 102U, chartInstance->c105_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 98U, chartInstance->c105_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 99U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_Mode_Offset_Aux4 = 0U;
        chartInstance->c105_d_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
        chartInstance->c105_d_tp_Aux_Enabled = 0U;
        chartInstance->c105_b_is_Offset_Left = c105_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_Offset_Left = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
        chartInstance->c105_c_is_Enabled = c105_IN_Control_Fault;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_Control_Fault = 1U;
        c105_b_enter_atomic_Control_Fault(chartInstance);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 38U,
                     chartInstance->c105_sfEvent);
        *chartInstance->c105_check_LeftNeutral = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                              18U);
        *chartInstance->c105_check_RightNeutral = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                              19U);
        c105_DiverterFaultOverrideLeft(chartInstance);
      }
    }
  }

  if (guard1) {
    chartInstance->c105_b_tp_Mode_Offset_Aux4 = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
    chartInstance->c105_d_is_Aux_Enabled = c105_b_IN_Mode_Offset_Aux4;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
    chartInstance->c105_b_tp_Mode_Offset_Aux4 = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_AUX4;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_LT_OF_A4);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
    c105_DiverterFaultOverrideLeft(chartInstance);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 38U, chartInstance->c105_sfEvent);
}

static void c105_Mode_Offset_Aux1(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_temp;
  boolean_T c105_out;
  boolean_T c105_b_temp;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 22U,
               chartInstance->c105_sfEvent);
  c105_temp = (_SFD_CCP_CALL(5U, 22U, 0,
    *chartInstance->c105_change_LeftControlMode != 0U,
    chartInstance->c105_sfEvent) != 0U);
  if (c105_temp) {
    c105_temp = !(_SFD_CCP_CALL(5U, 22U, 1, *chartInstance->c105_fault_Diverter
      != 0U, chartInstance->c105_sfEvent) != 0U);
  }

  c105_out = (CV_TRANSITION_EVAL(22U, (int32_T)c105_temp) != 0);
  guard1 = false;
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 22U, chartInstance->c105_sfEvent);
    *chartInstance->c105_check_LeftNeutral = true;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 66U,
                 chartInstance->c105_sfEvent);
    c105_c_out = (CV_TRANSITION_EVAL(66U, (int32_T)(_SFD_CCP_CALL(5U, 66U, 0,
      *chartInstance->c105_valid_LeftControl != 0U, chartInstance->c105_sfEvent)
      != 0U)) != 0);
    if (c105_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 66U, chartInstance->c105_sfEvent);
      c105_set_state_Buzzer(chartInstance, 0,
                            chartInstance->c105_DOUBLE_SHORT_BEEP);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
      chartInstance->c105_c_tp_Mode_Offset_Aux1 = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
      chartInstance->c105_d_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux1;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Mode_Aux2_Aux1 = 1U;
      *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_AUX2;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
      *chartInstance->c105_mode_RightControl =
        chartInstance->c105_MODE_RIGHT_AUX1;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
      c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_LT_A2_A1);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      matlab_UpdateEEVar();
      c105_DiverterFaultOverrideLeft(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 67U, chartInstance->c105_sfEvent);
      guard1 = true;
    }
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 56U,
                 chartInstance->c105_sfEvent);
    c105_b_temp = (_SFD_CCP_CALL(5U, 56U, 0,
      *chartInstance->c105_change_RightControlMode != 0U,
      chartInstance->c105_sfEvent) != 0U);
    if (c105_b_temp) {
      c105_b_temp = (_SFD_CCP_CALL(5U, 56U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        56U, 0, (real_T)*chartInstance->c105_state_CommSecondary, (real_T)
        chartInstance->c105_NORMAL, 0, 0U,
        *chartInstance->c105_state_CommSecondary == chartInstance->c105_NORMAL)
        != 0U, chartInstance->c105_sfEvent) != 0U);
    }

    c105_b_out = (CV_TRANSITION_EVAL(56U, (int32_T)c105_b_temp) != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 56U, chartInstance->c105_sfEvent);
      *chartInstance->c105_check_RightNeutral = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 54U,
                   chartInstance->c105_sfEvent);
      c105_d_out = (CV_TRANSITION_EVAL(54U, (int32_T)(_SFD_CCP_CALL(5U, 54U, 0, *
        chartInstance->c105_valid_RightControl != 0U,
        chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 54U, chartInstance->c105_sfEvent);
        c105_set_state_Buzzer(chartInstance, 0,
                              chartInstance->c105_DOUBLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        chartInstance->c105_c_tp_Mode_Offset_Aux1 = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
        chartInstance->c105_d_is_Aux_Enabled = c105_b_IN_Mode_Offset_Aux4;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_Mode_Offset_Aux4 = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_OFFSET;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_AUX4;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        c105_set_ee_ControlMode(chartInstance, 0,
          chartInstance->c105_EE_LT_OF_A4);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
        c105_DiverterFaultOverrideLeft(chartInstance);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 55U, chartInstance->c105_sfEvent);
        guard1 = true;
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 37U,
                   chartInstance->c105_sfEvent);
      *chartInstance->c105_check_LeftNeutral = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
      *chartInstance->c105_check_RightNeutral = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
      c105_DiverterFaultOverrideLeft(chartInstance);
    }
  }

  if (guard1) {
    chartInstance->c105_c_tp_Mode_Offset_Aux1 = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
    chartInstance->c105_d_is_Aux_Enabled = c105_c_IN_Mode_Offset_Aux1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c105_sfEvent);
    chartInstance->c105_c_tp_Mode_Offset_Aux1 = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_AUX1;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_LT_OF_A1);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
    c105_DiverterFaultOverrideLeft(chartInstance);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 37U, chartInstance->c105_sfEvent);
}

static void c105_enter_atomic_Mode_Offset_None
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_OFFSET;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
  *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
  c105_DiverterFaultOverrideLeft(chartInstance);
}

static void c105_b_enter_atomic_Control_Fault
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
  *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
  *chartInstance->c105_aux_inhibit = true;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
  *chartInstance->c105_flag_AuxEnableFlash = false;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash, 15U);
  c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_NA_NA);
  ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
  matlab_UpdateEEVar();
}

static void c105_b_enter_internal_Offset_Right
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 120U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(120U, (int32_T)(_SFD_CCP_CALL(5U, 120U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 120U, 0, (real_T)
    *chartInstance->c105_state_AuxEnable, (real_T)chartInstance->c105_INACTIVE,
    0, 1U, *chartInstance->c105_state_AuxEnable != chartInstance->c105_INACTIVE)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  guard1 = false;
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 120U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 126U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(126U, (int32_T)(_SFD_CCP_CALL(5U, 126U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 126U, 0, (real_T)c105_get_ee_ControlMode
      (chartInstance, 0), (real_T)chartInstance->c105_EE_RT_NA_OF, 0, 5U,
      c105_get_ee_ControlMode(chartInstance, 0) >=
      chartInstance->c105_EE_RT_NA_OF) != 0U, chartInstance->c105_sfEvent) != 0U))
                  != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 126U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_is_Offset_Right = c105_IN_Aux_Enabled;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
      chartInstance->c105_e_tp_Aux_Enabled = 1U;
      *chartInstance->c105_flag_AuxEnableFlash = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      c105_e_enter_internal_Aux_Enabled(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 125U, chartInstance->c105_sfEvent);
      *chartInstance->c105_aux_inhibit = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 124U, chartInstance->c105_sfEvent);
      guard1 = true;
    }
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c105_sfEvent);
    guard1 = true;
  }

  if (guard1) {
    chartInstance->c105_b_is_Offset_Right = c105_IN_Mode_None_Offset;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 45U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_b_tp_Mode_None_Offset = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl =
      chartInstance->c105_MODE_RIGHT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    c105_DiverterFaultOverrideRight(chartInstance);
  }
}

static void c105_b_Offset_Right(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_temp;
  boolean_T c105_out;
  boolean_T c105_b_temp;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_c_temp;
  boolean_T c105_d_temp;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 44U,
               chartInstance->c105_sfEvent);
  c105_temp = (_SFD_CCP_CALL(5U, 44U, 0,
    *chartInstance->c105_change_OffsetSelectSw != 0U,
    chartInstance->c105_sfEvent) != 0U);
  if (c105_temp) {
    c105_temp = (_SFD_CCP_CALL(5U, 44U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 44U,
      0, (real_T)*chartInstance->c105_din_OffsetSelectSw, (real_T)
      chartInstance->c105_OFFSET_SELECT_LEFT, 0, 0U, (int32_T)
      *chartInstance->c105_din_OffsetSelectSw ==
      chartInstance->c105_OFFSET_SELECT_LEFT) != 0U, chartInstance->c105_sfEvent)
                 != 0U);
  }

  c105_out = (CV_TRANSITION_EVAL(44U, (int32_T)c105_temp) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 44U, chartInstance->c105_sfEvent);
    *chartInstance->c105_check_LeftNeutral = true;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 46U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 47U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(47U, (int32_T)(_SFD_CCP_CALL(5U, 47U, 0,
      *chartInstance->c105_valid_LeftControl != 0U, chartInstance->c105_sfEvent)
      != 0U)) != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 47U, chartInstance->c105_sfEvent);
      c105_set_state_Buzzer(chartInstance, 0,
                            chartInstance->c105_SINGLE_MEDIUM_BEEP);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
      *chartInstance->c105_flag_AuxEnableFlash = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                            15U);
      c105_b_exit_internal_Offset_Right(chartInstance);
      chartInstance->c105_b_tp_Offset_Right = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c105_sfEvent);
      chartInstance->c105_c_is_Enabled = c105_IN_Offset_Left;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Offset_Left = 1U;
      c105_b_enter_internal_Offset_Left(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 45U, chartInstance->c105_sfEvent);
      c105_b_exit_internal_Offset_Right(chartInstance);
      chartInstance->c105_b_tp_Offset_Right = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c105_sfEvent);
      chartInstance->c105_c_is_Enabled = c105_IN_Control_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Control_Fault = 1U;
      c105_b_enter_atomic_Control_Fault(chartInstance);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 40U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 40U,
                 chartInstance->c105_sfEvent);
    switch (chartInstance->c105_b_is_Offset_Right) {
     case c105_IN_Aux_Enabled:
      CV_STATE_EVAL(40, 0, c105_IN_Aux_Enabled);
      c105_e_Aux_Enabled(chartInstance);
      if (chartInstance->c105_c_is_Enabled != c105_IN_Offset_Right) {
      } else {
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 40U, chartInstance->c105_sfEvent);
      }
      break;

     case c105_IN_Mode_None_Offset:
      CV_STATE_EVAL(40, 0, c105_IN_Mode_None_Offset);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 18U,
                   chartInstance->c105_sfEvent);
      c105_b_temp = (_SFD_CCP_CALL(5U, 18U, 0,
        *chartInstance->c105_change_LeftControlMode != 0U,
        chartInstance->c105_sfEvent) != 0U);
      if (!c105_b_temp) {
        c105_b_temp = (_SFD_CCP_CALL(5U, 18U, 1,
          *chartInstance->c105_change_RightControlMode != 0U,
          chartInstance->c105_sfEvent) != 0U);
      }

      c105_c_out = (CV_TRANSITION_EVAL(18U, (int32_T)c105_b_temp) != 0);
      guard1 = false;
      if (c105_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c105_sfEvent);
        c105_set_state_Buzzer(chartInstance, 0,
                              chartInstance->c105_TRIPLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        *chartInstance->c105_display_request = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
        *chartInstance->c105_flag_AuxEnableFlash = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_flag_AuxEnableFlash,
                              15U);
        guard1 = true;
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 90U,
                     chartInstance->c105_sfEvent);
        c105_c_temp = (_SFD_CCP_CALL(5U, 90U, 0,
          *chartInstance->c105_change_AuxEnable != 0U,
          chartInstance->c105_sfEvent) != 0U);
        if (c105_c_temp) {
          c105_c_temp = (_SFD_CCP_CALL(5U, 90U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 90U, 0, (real_T)*chartInstance->c105_state_AuxEnable, (real_T)
             chartInstance->c105_INACTIVE, 0, 1U,
             *chartInstance->c105_state_AuxEnable !=
             chartInstance->c105_INACTIVE) != 0U, chartInstance->c105_sfEvent)
                         != 0U);
        }

        c105_d_temp = c105_c_temp;
        if (c105_c_temp) {
          c105_d_temp = (_SFD_CCP_CALL(5U, 90U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 90U, 1, (real_T)*chartInstance->c105_state_CommSecondary,
             (real_T)chartInstance->c105_NORMAL, 0, 0U,
             *chartInstance->c105_state_CommSecondary ==
             chartInstance->c105_NORMAL) != 0U, chartInstance->c105_sfEvent) !=
                         0U);
        }

        c105_d_out = (CV_TRANSITION_EVAL(90U, (int32_T)c105_d_temp) != 0);
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 90U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 89U,
                       chartInstance->c105_sfEvent);
          c105_e_out = (CV_TRANSITION_EVAL(89U, (int32_T)(_SFD_CCP_CALL(5U, 89U,
            0, *chartInstance->c105_valid_LeftControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 89U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_tp_Mode_None_Offset = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 45U, chartInstance->c105_sfEvent);
            chartInstance->c105_b_is_Offset_Right = c105_IN_Aux_Enabled;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
            chartInstance->c105_e_tp_Aux_Enabled = 1U;
            *chartInstance->c105_flag_AuxEnableFlash = false;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
            c105_e_enter_internal_Aux_Enabled(chartInstance);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 88U, chartInstance->c105_sfEvent);
            *chartInstance->c105_aux_inhibit = true;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
            guard1 = true;
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 45U,
                       chartInstance->c105_sfEvent);
          *chartInstance->c105_check_LeftNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                18U);
          *chartInstance->c105_check_RightNeutral = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          *chartInstance->c105_aux_inhibit = false;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_aux_inhibit, 20U);
          c105_DiverterFaultOverrideRight(chartInstance);
          if (chartInstance->c105_temporalCounter_i1 >= 10U) {
            CV_STATE_EVAL(45, 0, 2);
            *chartInstance->c105_display_request = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                  21U);
          } else {
            CV_STATE_EVAL(45, 0, 1);
          }

          if (chartInstance->c105_temporalCounter_i1 >= 200U) {
            CV_STATE_EVAL(45, 1, 2);
            *chartInstance->c105_flag_AuxEnableFlash = false;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_flag_AuxEnableFlash, 15U);
          } else {
            CV_STATE_EVAL(45, 1, 1);
          }
        }
      }

      if (guard1) {
        chartInstance->c105_b_tp_Mode_None_Offset = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 45U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_is_Offset_Right = c105_IN_Mode_None_Offset;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 45U, chartInstance->c105_sfEvent);
        chartInstance->c105_temporalCounter_i1 = 0U;
        chartInstance->c105_b_tp_Mode_None_Offset = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_OFFSET;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        c105_DiverterFaultOverrideRight(chartInstance);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 45U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 40U, chartInstance->c105_sfEvent);
      break;

     default:
      CV_STATE_EVAL(40, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c105_b_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 40U, chartInstance->c105_sfEvent);
      break;
    }
  }
}

static void c105_b_exit_internal_Offset_Right
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c105_b_is_Offset_Right) {
   case c105_IN_Aux_Enabled:
    CV_STATE_EVAL(40, 1, c105_IN_Aux_Enabled);
    c105_e_exit_internal_Aux_Enabled(chartInstance);
    chartInstance->c105_e_tp_Aux_Enabled = 0U;
    chartInstance->c105_b_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
    break;

   case c105_IN_Mode_None_Offset:
    CV_STATE_EVAL(40, 1, c105_IN_Mode_None_Offset);
    chartInstance->c105_b_tp_Mode_None_Offset = 0U;
    chartInstance->c105_b_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 45U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(40, 1, 0);
    chartInstance->c105_b_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_e_enter_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 118U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(118U, (int32_T)(_SFD_CCP_CALL(5U, 118U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 118U, 0, (real_T)c105_get_ee_ControlMode
    (chartInstance, 0), (real_T)chartInstance->c105_EE_RT_A4_A1, 0, 0U,
    c105_get_ee_ControlMode(chartInstance, 0) == chartInstance->c105_EE_RT_A4_A1)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 118U, chartInstance->c105_sfEvent);
    chartInstance->c105_e_is_Aux_Enabled = c105_b_IN_Mode_Aux4_Aux1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
    chartInstance->c105_b_tp_Mode_Aux4_Aux1 = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_AUX4;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_AUX1;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_RT_A4_A1);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 119U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(119U, (int32_T)(_SFD_CCP_CALL(5U, 119U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 119U, 0, (real_T)c105_get_ee_ControlMode
      (chartInstance, 0), (real_T)chartInstance->c105_EE_RT_A2_A1, 0, 0U,
      c105_get_ee_ControlMode(chartInstance, 0) ==
      chartInstance->c105_EE_RT_A2_A1) != 0U, chartInstance->c105_sfEvent) != 0U))
                  != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 119U, chartInstance->c105_sfEvent);
      chartInstance->c105_e_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux1;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
      chartInstance->c105_temporalCounter_i1 = 0U;
      chartInstance->c105_c_tp_Mode_Aux2_Aux1 = 1U;
      *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_AUX2;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
      *chartInstance->c105_mode_RightControl =
        chartInstance->c105_MODE_RIGHT_AUX1;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
      c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_RT_A2_A1);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      matlab_UpdateEEVar();
      c105_DiverterFaultOverrideLeft(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 27U, chartInstance->c105_sfEvent);
      chartInstance->c105_e_is_Aux_Enabled = c105_b_IN_Mode_Aux4_Offset;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c105_sfEvent);
      chartInstance->c105_temporalCounter_i1 = 0U;
      chartInstance->c105_b_tp_Mode_Aux4_Offset = 1U;
      *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_AUX4;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
      *chartInstance->c105_mode_RightControl =
        chartInstance->c105_MODE_RIGHT_OFFSET;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
      c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_RT_A4_OF);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
      matlab_UpdateEEVar();
      c105_DiverterFaultOverrideRight(chartInstance);
    }
  }
}

static void c105_e_Aux_Enabled(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T c105_d_out;
  boolean_T c105_e_out;
  boolean_T c105_temp;
  boolean_T c105_f_out;
  boolean_T c105_g_out;
  boolean_T c105_h_out;
  boolean_T c105_i_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 19U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(19U, (int32_T)(_SFD_CCP_CALL(5U, 19U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 19U, 0, (real_T)
    *chartInstance->c105_state_AuxEnable, (real_T)chartInstance->c105_INACTIVE,
    0, 0U, *chartInstance->c105_state_AuxEnable == chartInstance->c105_INACTIVE)
    != 0U, chartInstance->c105_sfEvent) != 0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c105_sfEvent);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_NA_NA);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
    c105_e_exit_internal_Aux_Enabled(chartInstance);
    chartInstance->c105_e_tp_Aux_Enabled = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
    chartInstance->c105_b_is_Offset_Right = c105_IN_Mode_None_Offset;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 45U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_b_tp_Mode_None_Offset = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl =
      chartInstance->c105_MODE_RIGHT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    c105_DiverterFaultOverrideRight(chartInstance);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 103U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(103U, (int32_T)(_SFD_CCP_CALL(5U, 103U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 103U, 0, (real_T)
      *chartInstance->c105_state_CommSecondary, (real_T)
      chartInstance->c105_NO_COMMUNICATION, 0, 0U,
      *chartInstance->c105_state_CommSecondary ==
      chartInstance->c105_NO_COMMUNICATION) != 0U, chartInstance->c105_sfEvent)
      != 0U)) != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 103U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 98U, chartInstance->c105_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 99U, chartInstance->c105_sfEvent);
      c105_e_exit_internal_Aux_Enabled(chartInstance);
      chartInstance->c105_e_tp_Aux_Enabled = 0U;
      chartInstance->c105_b_is_Offset_Right = c105_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Offset_Right = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c105_sfEvent);
      chartInstance->c105_c_is_Enabled = c105_IN_Control_Fault;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c105_sfEvent);
      chartInstance->c105_b_tp_Control_Fault = 1U;
      c105_b_enter_atomic_Control_Fault(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 41U,
                   chartInstance->c105_sfEvent);
      switch (chartInstance->c105_e_is_Aux_Enabled) {
       case c105_IN_Mode_Aux2_Aux1:
        CV_STATE_EVAL(41, 0, c105_IN_Mode_Aux2_Aux1);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 24U,
                     chartInstance->c105_sfEvent);
        c105_c_out = (CV_TRANSITION_EVAL(24U, (int32_T)(_SFD_CCP_CALL(5U, 24U, 0,
          *chartInstance->c105_change_RightControlMode != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        guard1 = false;
        if (c105_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c105_sfEvent);
          c105_set_state_Buzzer(chartInstance, 0,
                                chartInstance->c105_TRIPLE_SHORT_BEEP);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          *chartInstance->c105_display_request = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                21U);
          guard1 = true;
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 85U,
                       chartInstance->c105_sfEvent);
          c105_e_out = (CV_TRANSITION_EVAL(85U, (int32_T)(_SFD_CCP_CALL(5U, 85U,
            0, *chartInstance->c105_change_LeftControlMode != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 85U, chartInstance->c105_sfEvent);
            *chartInstance->c105_check_LeftNeutral = true;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                  18U);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 82U,
                         chartInstance->c105_sfEvent);
            c105_h_out = (CV_TRANSITION_EVAL(82U, (int32_T)(_SFD_CCP_CALL(5U,
              82U, 0, *chartInstance->c105_valid_LeftControl != 0U,
              chartInstance->c105_sfEvent) != 0U)) != 0);
            if (c105_h_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 82U,
                           chartInstance->c105_sfEvent);
              c105_set_state_Buzzer(chartInstance, 0,
                                    chartInstance->c105_SINGLE_SHORT_BEEP);
              ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
              chartInstance->c105_c_tp_Mode_Aux2_Aux1 = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
              chartInstance->c105_e_is_Aux_Enabled = c105_b_IN_Mode_Aux4_Aux1;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
              chartInstance->c105_b_tp_Mode_Aux4_Aux1 = 1U;
              *chartInstance->c105_mode_LeftControl =
                chartInstance->c105_MODE_LEFT_AUX4;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c105_mode_LeftControl, 16U);
              *chartInstance->c105_mode_RightControl =
                chartInstance->c105_MODE_RIGHT_AUX1;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c105_mode_RightControl, 17U);
              c105_set_ee_ControlMode(chartInstance, 0,
                chartInstance->c105_EE_RT_A4_A1);
              ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
              matlab_UpdateEEVar();
            } else {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 84U,
                           chartInstance->c105_sfEvent);
              guard1 = true;
            }
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 42U,
                         chartInstance->c105_sfEvent);
            *chartInstance->c105_check_LeftNeutral = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                  18U);
            c105_DiverterFaultOverrideLeft(chartInstance);
            if (chartInstance->c105_temporalCounter_i1 >= 10U) {
              CV_STATE_EVAL(42, 0, 2);
              *chartInstance->c105_display_request = false;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request,
                                    21U);
            } else {
              CV_STATE_EVAL(42, 0, 1);
            }
          }
        }

        if (guard1) {
          chartInstance->c105_c_tp_Mode_Aux2_Aux1 = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
          chartInstance->c105_e_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux1;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
          chartInstance->c105_temporalCounter_i1 = 0U;
          chartInstance->c105_c_tp_Mode_Aux2_Aux1 = 1U;
          *chartInstance->c105_mode_LeftControl =
            chartInstance->c105_MODE_LEFT_AUX2;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                16U);
          *chartInstance->c105_mode_RightControl =
            chartInstance->c105_MODE_RIGHT_AUX1;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                17U);
          c105_set_ee_ControlMode(chartInstance, 0,
            chartInstance->c105_EE_RT_A2_A1);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
          c105_DiverterFaultOverrideLeft(chartInstance);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 42U, chartInstance->c105_sfEvent);
        break;

       case c105_b_IN_Mode_Aux4_Aux1:
        CV_STATE_EVAL(41, 0, c105_b_IN_Mode_Aux4_Aux1);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 81U,
                     chartInstance->c105_sfEvent);
        c105_d_out = (CV_TRANSITION_EVAL(81U, (int32_T)(_SFD_CCP_CALL(5U, 81U, 0,
          *chartInstance->c105_change_RightControlMode != 0U,
          chartInstance->c105_sfEvent) != 0U)) != 0);
        guard1 = false;
        if (c105_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 81U, chartInstance->c105_sfEvent);
          *chartInstance->c105_check_RightNeutral = true;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral,
                                19U);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 78U,
                       chartInstance->c105_sfEvent);
          c105_g_out = (CV_TRANSITION_EVAL(78U, (int32_T)(_SFD_CCP_CALL(5U, 78U,
            0, *chartInstance->c105_valid_RightControl != 0U,
            chartInstance->c105_sfEvent) != 0U)) != 0);
          if (c105_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 78U, chartInstance->c105_sfEvent);
            c105_set_state_Buzzer(chartInstance, 0,
                                  chartInstance->c105_SINGLE_SHORT_BEEP);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            chartInstance->c105_b_tp_Mode_Aux4_Aux1 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
            chartInstance->c105_e_is_Aux_Enabled = c105_b_IN_Mode_Aux4_Offset;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c105_sfEvent);
            chartInstance->c105_temporalCounter_i1 = 0U;
            chartInstance->c105_b_tp_Mode_Aux4_Offset = 1U;
            *chartInstance->c105_mode_LeftControl =
              chartInstance->c105_MODE_LEFT_AUX4;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                  16U);
            *chartInstance->c105_mode_RightControl =
              chartInstance->c105_MODE_RIGHT_OFFSET;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                  17U);
            c105_set_ee_ControlMode(chartInstance, 0,
              chartInstance->c105_EE_RT_A4_OF);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
            c105_DiverterFaultOverrideRight(chartInstance);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 79U, chartInstance->c105_sfEvent);
            guard1 = true;
          }
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 86U,
                       chartInstance->c105_sfEvent);
          c105_temp = (_SFD_CCP_CALL(5U, 86U, 0,
            *chartInstance->c105_change_LeftControlMode != 0U,
            chartInstance->c105_sfEvent) != 0U);
          if (c105_temp) {
            c105_temp = !(_SFD_CCP_CALL(5U, 86U, 1,
              *chartInstance->c105_fault_Diverter != 0U,
              chartInstance->c105_sfEvent) != 0U);
          }

          c105_f_out = (CV_TRANSITION_EVAL(86U, (int32_T)c105_temp) != 0);
          if (c105_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 86U, chartInstance->c105_sfEvent);
            *chartInstance->c105_check_LeftNeutral = true;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                  18U);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 87U,
                         chartInstance->c105_sfEvent);
            c105_i_out = (CV_TRANSITION_EVAL(87U, (int32_T)(_SFD_CCP_CALL(5U,
              87U, 0, *chartInstance->c105_valid_LeftControl != 0U,
              chartInstance->c105_sfEvent) != 0U)) != 0);
            if (c105_i_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 87U,
                           chartInstance->c105_sfEvent);
              c105_set_state_Buzzer(chartInstance, 0,
                                    chartInstance->c105_DOUBLE_SHORT_BEEP);
              ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
              chartInstance->c105_b_tp_Mode_Aux4_Aux1 = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
              chartInstance->c105_e_is_Aux_Enabled = c105_IN_Mode_Aux2_Aux1;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
              chartInstance->c105_temporalCounter_i1 = 0U;
              chartInstance->c105_c_tp_Mode_Aux2_Aux1 = 1U;
              *chartInstance->c105_mode_LeftControl =
                chartInstance->c105_MODE_LEFT_AUX2;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c105_mode_LeftControl, 16U);
              *chartInstance->c105_mode_RightControl =
                chartInstance->c105_MODE_RIGHT_AUX1;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c105_mode_RightControl, 17U);
              c105_set_ee_ControlMode(chartInstance, 0,
                chartInstance->c105_EE_RT_A2_A1);
              ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
              matlab_UpdateEEVar();
              c105_DiverterFaultOverrideLeft(chartInstance);
            } else {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 83U,
                           chartInstance->c105_sfEvent);
              guard1 = true;
            }
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 43U,
                         chartInstance->c105_sfEvent);
            *chartInstance->c105_check_LeftNeutral = false;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral,
                                  18U);
            *chartInstance->c105_check_RightNeutral = false;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c105_check_RightNeutral, 19U);
          }
        }

        if (guard1) {
          chartInstance->c105_b_tp_Mode_Aux4_Aux1 = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
          chartInstance->c105_e_is_Aux_Enabled = c105_b_IN_Mode_Aux4_Aux1;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
          chartInstance->c105_b_tp_Mode_Aux4_Aux1 = 1U;
          *chartInstance->c105_mode_LeftControl =
            chartInstance->c105_MODE_LEFT_AUX4;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl,
                                16U);
          *chartInstance->c105_mode_RightControl =
            chartInstance->c105_MODE_RIGHT_AUX1;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                                17U);
          c105_set_ee_ControlMode(chartInstance, 0,
            chartInstance->c105_EE_RT_A4_A1);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 43U, chartInstance->c105_sfEvent);
        break;

       case c105_b_IN_Mode_Aux4_Offset:
        CV_STATE_EVAL(41, 0, c105_b_IN_Mode_Aux4_Offset);
        c105_Mode_Aux4_Offset(chartInstance);
        break;

       default:
        CV_STATE_EVAL(41, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c105_e_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 41U, chartInstance->c105_sfEvent);
}

static void c105_e_exit_internal_Aux_Enabled
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c105_e_is_Aux_Enabled) {
   case c105_IN_Mode_Aux2_Aux1:
    CV_STATE_EVAL(41, 1, c105_IN_Mode_Aux2_Aux1);
    chartInstance->c105_c_tp_Mode_Aux2_Aux1 = 0U;
    chartInstance->c105_e_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
    break;

   case c105_b_IN_Mode_Aux4_Aux1:
    CV_STATE_EVAL(41, 1, c105_b_IN_Mode_Aux4_Aux1);
    chartInstance->c105_b_tp_Mode_Aux4_Aux1 = 0U;
    chartInstance->c105_e_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
    break;

   case c105_b_IN_Mode_Aux4_Offset:
    CV_STATE_EVAL(41, 1, c105_b_IN_Mode_Aux4_Offset);
    chartInstance->c105_b_tp_Mode_Aux4_Offset = 0U;
    chartInstance->c105_e_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c105_sfEvent);
    break;

   default:
    CV_STATE_EVAL(41, 1, 0);
    chartInstance->c105_e_is_Aux_Enabled = c105_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c105_sfEvent);
    break;
  }
}

static void c105_Mode_Aux4_Offset(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_out;
  boolean_T c105_b_out;
  boolean_T c105_c_out;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 23U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(23U, (int32_T)(_SFD_CCP_CALL(5U, 23U, 0,
    *chartInstance->c105_change_LeftControlMode != 0U,
    chartInstance->c105_sfEvent) != 0U)) != 0);
  guard1 = false;
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 23U, chartInstance->c105_sfEvent);
    c105_set_state_Buzzer(chartInstance, 0,
                          chartInstance->c105_TRIPLE_SHORT_BEEP);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
    *chartInstance->c105_display_request = true;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
    guard1 = true;
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 80U,
                 chartInstance->c105_sfEvent);
    c105_b_out = (CV_TRANSITION_EVAL(80U, (int32_T)(_SFD_CCP_CALL(5U, 80U, 0,
      *chartInstance->c105_change_RightControlMode != 0U,
      chartInstance->c105_sfEvent) != 0U)) != 0);
    if (c105_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 80U, chartInstance->c105_sfEvent);
      *chartInstance->c105_check_RightNeutral = true;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 76U,
                   chartInstance->c105_sfEvent);
      c105_c_out = (CV_TRANSITION_EVAL(76U, (int32_T)(_SFD_CCP_CALL(5U, 76U, 0, *
        chartInstance->c105_valid_RightControl != 0U,
        chartInstance->c105_sfEvent) != 0U)) != 0);
      if (c105_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 76U, chartInstance->c105_sfEvent);
        c105_set_state_Buzzer(chartInstance, 0,
                              chartInstance->c105_DOUBLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        chartInstance->c105_b_tp_Mode_Aux4_Offset = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c105_sfEvent);
        chartInstance->c105_e_is_Aux_Enabled = c105_b_IN_Mode_Aux4_Aux1;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c105_sfEvent);
        chartInstance->c105_b_tp_Mode_Aux4_Aux1 = 1U;
        *chartInstance->c105_mode_LeftControl =
          chartInstance->c105_MODE_LEFT_AUX4;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
        *chartInstance->c105_mode_RightControl =
          chartInstance->c105_MODE_RIGHT_AUX1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl,
                              17U);
        c105_set_ee_ControlMode(chartInstance, 0,
          chartInstance->c105_EE_RT_A4_A1);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 77U, chartInstance->c105_sfEvent);
        guard1 = true;
      }
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 44U,
                   chartInstance->c105_sfEvent);
      *chartInstance->c105_check_LeftNeutral = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_LeftNeutral, 18U);
      *chartInstance->c105_check_RightNeutral = false;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_check_RightNeutral, 19U);
      c105_DiverterFaultOverrideRight(chartInstance);
      if (chartInstance->c105_temporalCounter_i1 >= 10U) {
        CV_STATE_EVAL(44, 0, 2);
        *chartInstance->c105_display_request = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_display_request, 21U);
      } else {
        CV_STATE_EVAL(44, 0, 1);
      }
    }
  }

  if (guard1) {
    chartInstance->c105_b_tp_Mode_Aux4_Offset = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c105_sfEvent);
    chartInstance->c105_e_is_Aux_Enabled = c105_b_IN_Mode_Aux4_Offset;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c105_sfEvent);
    chartInstance->c105_temporalCounter_i1 = 0U;
    chartInstance->c105_b_tp_Mode_Aux4_Offset = 1U;
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_AUX4;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    *chartInstance->c105_mode_RightControl =
      chartInstance->c105_MODE_RIGHT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    c105_set_ee_ControlMode(chartInstance, 0, chartInstance->c105_EE_RT_A4_OF);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
    c105_DiverterFaultOverrideRight(chartInstance);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 44U, chartInstance->c105_sfEvent);
}

static void init_script_number_translation(uint32_T c105_machineNumber, uint32_T
  c105_chartNumber, uint32_T c105_instanceNumber)
{
  (void)(c105_machineNumber);
  (void)(c105_chartNumber);
  (void)(c105_instanceNumber);
}

const mxArray *sf_c105_MX_Gtwy_Control_get_eml_resolved_functions_info(void)
{
  const mxArray *c105_nameCaptureInfo = NULL;
  c105_nameCaptureInfo = NULL;
  sf_mex_assign(&c105_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c105_nameCaptureInfo;
}

static void c105_DiverterFaultOverrideLeft(SFc105_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  boolean_T c105_out;
  _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 29U, chartInstance->c105_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 29U, chartInstance->c105_sfEvent);
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 198U, chartInstance->c105_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 199U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(199U, (int32_T)(_SFD_CCP_CALL(5U, 199U, 0,
    *chartInstance->c105_fault_Diverter != 0U, chartInstance->c105_sfEvent) !=
    0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 199U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 202U, chartInstance->c105_sfEvent);
    *chartInstance->c105_mode_LeftControl = chartInstance->c105_MODE_LEFT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_LeftControl, 16U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 203U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 201U, chartInstance->c105_sfEvent);
  }

  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 200U, chartInstance->c105_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 29U, chartInstance->c105_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 29U, chartInstance->c105_sfEvent);
}

static void c105_DiverterFaultOverrideRight(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c105_out;
  _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 30U, chartInstance->c105_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 30U, chartInstance->c105_sfEvent);
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 204U, chartInstance->c105_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 205U,
               chartInstance->c105_sfEvent);
  c105_out = (CV_TRANSITION_EVAL(205U, (int32_T)(_SFD_CCP_CALL(5U, 205U, 0,
    *chartInstance->c105_fault_Diverter != 0U, chartInstance->c105_sfEvent) !=
    0U)) != 0);
  if (c105_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 205U, chartInstance->c105_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 207U, chartInstance->c105_sfEvent);
    *chartInstance->c105_mode_RightControl = chartInstance->c105_MODE_RIGHT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c105_mode_RightControl, 17U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 208U, chartInstance->c105_sfEvent);
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 206U, chartInstance->c105_sfEvent);
  }

  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 209U, chartInstance->c105_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 30U, chartInstance->c105_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 30U, chartInstance->c105_sfEvent);
}

static const mxArray *c105_sf_marshallOut(void *chartInstanceVoid, void
  *c105_inData)
{
  const mxArray *c105_mxArrayOutData;
  int32_T c105_u;
  const mxArray *c105_y = NULL;
  SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc105_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c105_mxArrayOutData = NULL;
  c105_mxArrayOutData = NULL;
  c105_u = *(int32_T *)c105_inData;
  c105_y = NULL;
  sf_mex_assign(&c105_y, sf_mex_create("y", &c105_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c105_mxArrayOutData, c105_y, false);
  return c105_mxArrayOutData;
}

static int32_T c105_emlrt_marshallIn(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c105_u, const emlrtMsgIdentifier *c105_parentId)
{
  int32_T c105_y;
  int32_T c105_i0;
  (void)chartInstance;
  sf_mex_import(c105_parentId, sf_mex_dup(c105_u), &c105_i0, 1, 6, 0U, 0, 0U, 0);
  c105_y = c105_i0;
  sf_mex_destroy(&c105_u);
  return c105_y;
}

static void c105_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c105_mxArrayInData, const char_T *c105_varName, void *c105_outData)
{
  const mxArray *c105_b_sfEvent;
  emlrtMsgIdentifier c105_thisId;
  int32_T c105_y;
  SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc105_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c105_b_sfEvent = sf_mex_dup(c105_mxArrayInData);
  c105_thisId.fIdentifier = (const char *)c105_varName;
  c105_thisId.fParent = NULL;
  c105_thisId.bParentIsCell = false;
  c105_y = c105_emlrt_marshallIn(chartInstance, sf_mex_dup(c105_b_sfEvent),
    &c105_thisId);
  sf_mex_destroy(&c105_b_sfEvent);
  *(int32_T *)c105_outData = c105_y;
  sf_mex_destroy(&c105_mxArrayInData);
}

static const mxArray *c105_b_sf_marshallOut(void *chartInstanceVoid, void
  *c105_inData)
{
  const mxArray *c105_mxArrayOutData;
  uint8_T c105_u;
  const mxArray *c105_y = NULL;
  SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc105_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c105_mxArrayOutData = NULL;
  c105_mxArrayOutData = NULL;
  c105_u = *(uint8_T *)c105_inData;
  c105_y = NULL;
  sf_mex_assign(&c105_y, sf_mex_create("y", &c105_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c105_mxArrayOutData, c105_y, false);
  return c105_mxArrayOutData;
}

static uint8_T c105_b_emlrt_marshallIn(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c105_b_tp_Non_Functional, const char_T
  *c105_identifier)
{
  uint8_T c105_y;
  emlrtMsgIdentifier c105_thisId;
  c105_thisId.fIdentifier = (const char *)c105_identifier;
  c105_thisId.fParent = NULL;
  c105_thisId.bParentIsCell = false;
  c105_y = c105_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c105_b_tp_Non_Functional), &c105_thisId);
  sf_mex_destroy(&c105_b_tp_Non_Functional);
  return c105_y;
}

static uint8_T c105_c_emlrt_marshallIn(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c105_u, const emlrtMsgIdentifier *c105_parentId)
{
  uint8_T c105_y;
  uint8_T c105_u0;
  (void)chartInstance;
  sf_mex_import(c105_parentId, sf_mex_dup(c105_u), &c105_u0, 1, 3, 0U, 0, 0U, 0);
  c105_y = c105_u0;
  sf_mex_destroy(&c105_u);
  return c105_y;
}

static void c105_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c105_mxArrayInData, const char_T *c105_varName, void *c105_outData)
{
  const mxArray *c105_b_tp_Non_Functional;
  emlrtMsgIdentifier c105_thisId;
  uint8_T c105_y;
  SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc105_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c105_b_tp_Non_Functional = sf_mex_dup(c105_mxArrayInData);
  c105_thisId.fIdentifier = (const char *)c105_varName;
  c105_thisId.fParent = NULL;
  c105_thisId.bParentIsCell = false;
  c105_y = c105_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c105_b_tp_Non_Functional), &c105_thisId);
  sf_mex_destroy(&c105_b_tp_Non_Functional);
  *(uint8_T *)c105_outData = c105_y;
  sf_mex_destroy(&c105_mxArrayInData);
}

static const mxArray *c105_c_sf_marshallOut(void *chartInstanceVoid, void
  *c105_inData)
{
  const mxArray *c105_mxArrayOutData;
  boolean_T c105_u;
  const mxArray *c105_y = NULL;
  SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc105_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c105_mxArrayOutData = NULL;
  c105_mxArrayOutData = NULL;
  c105_u = *(boolean_T *)c105_inData;
  c105_y = NULL;
  sf_mex_assign(&c105_y, sf_mex_create("y", &c105_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c105_mxArrayOutData, c105_y, false);
  return c105_mxArrayOutData;
}

static boolean_T c105_d_emlrt_marshallIn(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c105_b_flag_AuxEnableFlash, const char_T
  *c105_identifier)
{
  boolean_T c105_y;
  emlrtMsgIdentifier c105_thisId;
  c105_thisId.fIdentifier = (const char *)c105_identifier;
  c105_thisId.fParent = NULL;
  c105_thisId.bParentIsCell = false;
  c105_y = c105_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c105_b_flag_AuxEnableFlash), &c105_thisId);
  sf_mex_destroy(&c105_b_flag_AuxEnableFlash);
  return c105_y;
}

static boolean_T c105_e_emlrt_marshallIn(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c105_u, const emlrtMsgIdentifier *c105_parentId)
{
  boolean_T c105_y;
  boolean_T c105_b0;
  (void)chartInstance;
  sf_mex_import(c105_parentId, sf_mex_dup(c105_u), &c105_b0, 1, 11, 0U, 0, 0U, 0);
  c105_y = c105_b0;
  sf_mex_destroy(&c105_u);
  return c105_y;
}

static void c105_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c105_mxArrayInData, const char_T *c105_varName, void *c105_outData)
{
  const mxArray *c105_b_flag_AuxEnableFlash;
  emlrtMsgIdentifier c105_thisId;
  boolean_T c105_y;
  SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc105_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c105_b_flag_AuxEnableFlash = sf_mex_dup(c105_mxArrayInData);
  c105_thisId.fIdentifier = (const char *)c105_varName;
  c105_thisId.fParent = NULL;
  c105_thisId.bParentIsCell = false;
  c105_y = c105_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c105_b_flag_AuxEnableFlash), &c105_thisId);
  sf_mex_destroy(&c105_b_flag_AuxEnableFlash);
  *(boolean_T *)c105_outData = c105_y;
  sf_mex_destroy(&c105_mxArrayInData);
}

static const mxArray *c105_f_emlrt_marshallIn
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray
   *c105_b_setSimStateSideEffectsInfo, const char_T *c105_identifier)
{
  const mxArray *c105_y = NULL;
  emlrtMsgIdentifier c105_thisId;
  c105_y = NULL;
  c105_thisId.fIdentifier = (const char *)c105_identifier;
  c105_thisId.fParent = NULL;
  c105_thisId.bParentIsCell = false;
  sf_mex_assign(&c105_y, c105_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c105_b_setSimStateSideEffectsInfo), &c105_thisId), false);
  sf_mex_destroy(&c105_b_setSimStateSideEffectsInfo);
  return c105_y;
}

static const mxArray *c105_g_emlrt_marshallIn
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c105_u,
   const emlrtMsgIdentifier *c105_parentId)
{
  const mxArray *c105_y = NULL;
  (void)chartInstance;
  (void)c105_parentId;
  c105_y = NULL;
  sf_mex_assign(&c105_y, sf_mex_duplicatearraysafe(&c105_u), false);
  sf_mex_destroy(&c105_u);
  return c105_y;
}

static const mxArray *sf_get_hover_data_for_msg
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c105_ssid)
{
  (void)chartInstance;
  (void)c105_ssid;
  return NULL;
}

static void c105_init_sf_message_store_memory
  (SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static uint8_T c105__u8_s32_(SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c105_b, uint32_T c105_ssid_src_loc, int32_T c105_offset_src_loc,
  int32_T c105_length_src_loc)
{
  uint8_T c105_a;
  (void)chartInstance;
  c105_a = (uint8_T)c105_b;
  if (c105_a != c105_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c105_ssid_src_loc,
      c105_offset_src_loc, c105_length_src_loc);
  }

  return c105_a;
}

static uint8_T c105_get_ee_ControlMode(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c105_elementIndex)
{
  if (chartInstance->c105_dsmdiag_ee_ControlMode) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, "ee_ControlMode",
      c105_elementIndex);
  }

  return *chartInstance->c105_ee_ControlMode_address;
}

static void c105_set_ee_ControlMode(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c105_elementIndex, uint8_T c105_elementValue)
{
  if (chartInstance->c105_dsmdiag_ee_ControlMode) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, "ee_ControlMode",
      c105_elementIndex);
  }

  *chartInstance->c105_ee_ControlMode_address = c105_elementValue;
}

static uint8_T *c105_access_ee_ControlMode(SFc105_MX_Gtwy_ControlInstanceStruct *
  chartInstance, uint32_T c105_rdOnly)
{
  if (chartInstance->c105_dsmdiag_ee_ControlMode) {
    ssAccessDataStore_wrapper(chartInstance->S, 0, "ee_ControlMode", c105_rdOnly);
  }

  return chartInstance->c105_ee_ControlMode_address;
}

static uint8_T c105_get_state_Buzzer(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c105_elementIndex)
{
  if (chartInstance->c105_dsmdiag_state_Buzzer) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 1, "state_Buzzer",
      c105_elementIndex);
  }

  return *chartInstance->c105__indexstate_Buzzer_address;
}

static void c105_set_state_Buzzer(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c105_elementIndex, uint8_T c105_elementValue)
{
  if (chartInstance->c105_dsmdiag_state_Buzzer) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 1, "state_Buzzer",
      c105_elementIndex);
  }

  *chartInstance->c105__indexstate_Buzzer_address = c105_elementValue;
}

static uint8_T *c105_access_state_Buzzer(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c105_rdOnly)
{
  if (chartInstance->c105_dsmdiag_state_Buzzer) {
    ssAccessDataStore_wrapper(chartInstance->S, 1, "state_Buzzer", c105_rdOnly);
  }

  return chartInstance->c105__indexstate_Buzzer_address;
}

static void init_dsm_address_info(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_ControlMode",
    (void **)&chartInstance->c105_ee_ControlMode_address,
    &chartInstance->c105__indextrolMode);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "state_Buzzer", (void **)
    &chartInstance->c105__indexstate_Buzzer_address,
    &chartInstance->c105__indexBuzzer);
}

static void init_simulink_io_address(SFc105_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  chartInstance->c105_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c105_flag_AuxEnableFlash = (boolean_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c105_change_RightControlMode = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 0);
  chartInstance->c105_state_CommSecondary = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c105_mode_LeftControl = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 2);
  chartInstance->c105_change_LeftControlMode = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 2);
  chartInstance->c105_valid_LeftControl = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c105_valid_RightControl = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 4);
  chartInstance->c105_mode_RightControl = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c105_state_Console = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c105_state_Engine = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c105_state_System = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c105_flag_InitEERead = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 8);
  chartInstance->c105_fault_Diverter = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c105_state_AuxEnable = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c105_check_LeftNeutral = (boolean_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 4);
  chartInstance->c105_check_RightNeutral = (boolean_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 5);
  chartInstance->c105_change_AuxEnable = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 11);
  chartInstance->c105_din_OffsetSelectSw = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 12);
  chartInstance->c105_change_OffsetSelectSw = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 13);
  chartInstance->c105_aux_inhibit = (boolean_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c105_display_request = (boolean_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 7);
  chartInstance->c105_dsmdiag_ee_ControlMode = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 0,
    "ee_ControlMode");
  chartInstance->c105_dsmdiag_state_Buzzer = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 1, "state_Buzzer");
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

void sf_c105_MX_Gtwy_Control_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3744372537U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3791332206U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2602556291U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(972780902U);
}

mxArray* sf_c105_MX_Gtwy_Control_get_post_codegen_info(void);
mxArray *sf_c105_MX_Gtwy_Control_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("fjLyx6I1Caw87W6FwgaW0G");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,14,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,36,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
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
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c105_MX_Gtwy_Control_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c105_MX_Gtwy_Control_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c105_MX_Gtwy_Control_jit_fallback_info(void)
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

mxArray *sf_c105_MX_Gtwy_Control_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c105_MX_Gtwy_Control_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c105_MX_Gtwy_Control(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[479],T\"aux_inhibit\",},{M[1],M[320],T\"check_LeftNeutral\",},{M[1],M[326],T\"check_RightNeutral\",},{M[1],M[989],T\"display_request\",},{M[1],M[300],T\"flag_AuxEnableFlash\",},{M[1],M[135],T\"mode_LeftControl\",},{M[1],M[301],T\"mode_RightControl\",},{M[3],M[1452],T\"stored_ControlMode\",},{M[8],M[0],T\"is_active_c105_MX_Gtwy_Control\",},{M[9],M[0],T\"is_c105_MX_Gtwy_Control\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[9],M[162],T\"is_OptionA\",},{M[9],M[247],T\"is_OptionC\",},{M[9],M[254],T\"is_Offset_Left\",},{M[9],M[265],T\"is_Offset_Right\",},{M[9],M[276],T\"is_Aux_Enabled\",},{M[9],M[287],T\"is_Aux_Enabled\",},{M[9],M[307],T\"is_Enabled\",},{M[9],M[395],T\"is_Enabled\",},{M[9],M[964],T\"is_Left_Control_or_Diverter_Fault\",},{M[9],M[986],T\"is_Aux_Enabled\",}}",
    "100 S1x7'type','srcId','name','auxInfo'{{M[9],M[1262],T\"is_OptionB\",},{M[9],M[1299],T\"is_Enabled\",},{M[9],M[1325],T\"is_Offset_Left\",},{M[9],M[1336],T\"is_Aux_Enabled\",},{M[9],M[1381],T\"is_Offset_Right\",},{M[9],M[1395],T\"is_Aux_Enabled\",},{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"at\",M1x10[113 1379 1420 1422 262 275 290 273 1297 522],M[1]}}}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 27, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c105_MX_Gtwy_Control_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc105_MX_Gtwy_ControlInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc105_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MX_Gtwy_ControlMachineNumber_,
           105,
           47,
           210,
           0,
           60,
           0,
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
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,0,0,0,"stored_ControlMode");
          _SFD_SET_DATA_PROPS(1,1,1,0,"change_RightControlMode");
          _SFD_SET_DATA_PROPS(2,1,1,0,"state_CommSecondary");
          _SFD_SET_DATA_PROPS(3,1,1,0,"change_LeftControlMode");
          _SFD_SET_DATA_PROPS(4,1,1,0,"valid_LeftControl");
          _SFD_SET_DATA_PROPS(5,1,1,0,"valid_RightControl");
          _SFD_SET_DATA_PROPS(6,1,1,0,"state_Console");
          _SFD_SET_DATA_PROPS(7,1,1,0,"state_Engine");
          _SFD_SET_DATA_PROPS(8,1,1,0,"state_System");
          _SFD_SET_DATA_PROPS(9,1,1,0,"flag_InitEERead");
          _SFD_SET_DATA_PROPS(10,1,1,0,"fault_Diverter");
          _SFD_SET_DATA_PROPS(11,1,1,0,"state_AuxEnable");
          _SFD_SET_DATA_PROPS(12,1,1,0,"change_AuxEnable");
          _SFD_SET_DATA_PROPS(13,1,1,0,"din_OffsetSelectSw");
          _SFD_SET_DATA_PROPS(14,1,1,0,"change_OffsetSelectSw");
          _SFD_SET_DATA_PROPS(15,2,0,1,"flag_AuxEnableFlash");
          _SFD_SET_DATA_PROPS(16,2,0,1,"mode_LeftControl");
          _SFD_SET_DATA_PROPS(17,2,0,1,"mode_RightControl");
          _SFD_SET_DATA_PROPS(18,2,0,1,"check_LeftNeutral");
          _SFD_SET_DATA_PROPS(19,2,0,1,"check_RightNeutral");
          _SFD_SET_DATA_PROPS(20,2,0,1,"aux_inhibit");
          _SFD_SET_DATA_PROPS(21,2,0,1,"display_request");
          _SFD_SET_DATA_PROPS(22,10,0,0,"ACTIVE");
          _SFD_SET_DATA_PROPS(23,10,0,0,"CD_EMEA_CONTROLS_OPTION_A");
          _SFD_SET_DATA_PROPS(24,10,0,0,"CD_EMEA_CONTROLS_OPTION_B");
          _SFD_SET_DATA_PROPS(25,10,0,0,"CD_EMEA_CONTROLS_OPTION_C");
          _SFD_SET_DATA_PROPS(26,10,0,0,"DOUBLE_SHORT_BEEP");
          _SFD_SET_DATA_PROPS(27,10,0,0,"EE_LT_A2_A1");
          _SFD_SET_DATA_PROPS(28,10,0,0,"EE_LT_A2_A4");
          _SFD_SET_DATA_PROPS(29,10,0,0,"EE_LT_OF_A1");
          _SFD_SET_DATA_PROPS(30,10,0,0,"EE_LT_OF_A4");
          _SFD_SET_DATA_PROPS(31,10,0,0,"EE_LT_OF_NA");
          _SFD_SET_DATA_PROPS(32,10,0,0,"EE_NA_NA");
          _SFD_SET_DATA_PROPS(33,10,0,0,"EE_RT_A2_A1");
          _SFD_SET_DATA_PROPS(34,10,0,0,"EE_RT_A4_A1");
          _SFD_SET_DATA_PROPS(35,10,0,0,"EE_RT_A4_OF");
          _SFD_SET_DATA_PROPS(36,10,0,0,"EE_RT_NA_OF");
          _SFD_SET_DATA_PROPS(37,10,0,0,"ENGINE_CRANKING");
          _SFD_SET_DATA_PROPS(38,10,0,0,"INACTIVE");
          _SFD_SET_DATA_PROPS(39,10,0,0,"MODE_LEFT_AUX2");
          _SFD_SET_DATA_PROPS(40,10,0,0,"MODE_LEFT_AUX4");
          _SFD_SET_DATA_PROPS(41,10,0,0,"MODE_LEFT_NONE");
          _SFD_SET_DATA_PROPS(42,10,0,0,"MODE_LEFT_OFFSET");
          _SFD_SET_DATA_PROPS(43,10,0,0,"MODE_RIGHT_AUX1");
          _SFD_SET_DATA_PROPS(44,10,0,0,"MODE_RIGHT_AUX4");
          _SFD_SET_DATA_PROPS(45,10,0,0,"MODE_RIGHT_NONE");
          _SFD_SET_DATA_PROPS(46,10,0,0,"MODE_RIGHT_OFFSET");
          _SFD_SET_DATA_PROPS(47,10,0,0,"NON_FUNCTIONAL");
          _SFD_SET_DATA_PROPS(48,10,0,0,"NORMAL");
          _SFD_SET_DATA_PROPS(49,10,0,0,"NO_COMMUNICATION");
          _SFD_SET_DATA_PROPS(50,10,0,0,"OFFSET_SELECT_LEFT");
          _SFD_SET_DATA_PROPS(51,10,0,0,"OFFSET_SELECT_RIGHT");
          _SFD_SET_DATA_PROPS(52,10,0,0,"OORH");
          _SFD_SET_DATA_PROPS(53,10,0,0,"OORL");
          _SFD_SET_DATA_PROPS(54,10,0,0,"SINGLE_MEDIUM_BEEP");
          _SFD_SET_DATA_PROPS(55,10,0,0,"SINGLE_SHORT_BEEP");
          _SFD_SET_DATA_PROPS(56,10,0,0,"SYS_NORMAL");
          _SFD_SET_DATA_PROPS(57,10,0,0,"TRIPLE_SHORT_BEEP");
          _SFD_SET_DATA_PROPS(58,11,0,0,"ee_ControlMode");
          _SFD_SET_DATA_PROPS(59,11,0,0,"state_Buzzer");
          _SFD_STATE_INFO(0,0,0);
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
          _SFD_STATE_INFO(29,0,2);
          _SFD_STATE_INFO(30,0,2);
          _SFD_CH_SUBSTATE_COUNT(4);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,12);
          _SFD_CH_SUBSTATE_INDEX(3,27);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,4);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,3);
          _SFD_ST_SUBSTATE_INDEX(1,2,8);
          _SFD_ST_SUBSTATE_INDEX(1,3,9);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,2);
          _SFD_ST_SUBSTATE_INDEX(3,0,4);
          _SFD_ST_SUBSTATE_INDEX(3,1,7);
          _SFD_ST_SUBSTATE_COUNT(4,2);
          _SFD_ST_SUBSTATE_INDEX(4,0,5);
          _SFD_ST_SUBSTATE_INDEX(4,1,6);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,2);
          _SFD_ST_SUBSTATE_INDEX(9,0,10);
          _SFD_ST_SUBSTATE_INDEX(9,1,11);
          _SFD_ST_SUBSTATE_COUNT(10,0);
          _SFD_ST_SUBSTATE_COUNT(11,0);
          _SFD_ST_SUBSTATE_COUNT(12,3);
          _SFD_ST_SUBSTATE_INDEX(12,0,13);
          _SFD_ST_SUBSTATE_INDEX(12,1,14);
          _SFD_ST_SUBSTATE_INDEX(12,2,26);
          _SFD_ST_SUBSTATE_COUNT(13,0);
          _SFD_ST_SUBSTATE_COUNT(14,3);
          _SFD_ST_SUBSTATE_INDEX(14,0,15);
          _SFD_ST_SUBSTATE_INDEX(14,1,16);
          _SFD_ST_SUBSTATE_INDEX(14,2,21);
          _SFD_ST_SUBSTATE_COUNT(15,0);
          _SFD_ST_SUBSTATE_COUNT(16,2);
          _SFD_ST_SUBSTATE_INDEX(16,0,17);
          _SFD_ST_SUBSTATE_INDEX(16,1,20);
          _SFD_ST_SUBSTATE_COUNT(17,2);
          _SFD_ST_SUBSTATE_INDEX(17,0,18);
          _SFD_ST_SUBSTATE_INDEX(17,1,19);
          _SFD_ST_SUBSTATE_COUNT(18,0);
          _SFD_ST_SUBSTATE_COUNT(19,0);
          _SFD_ST_SUBSTATE_COUNT(20,0);
          _SFD_ST_SUBSTATE_COUNT(21,2);
          _SFD_ST_SUBSTATE_INDEX(21,0,22);
          _SFD_ST_SUBSTATE_INDEX(21,1,25);
          _SFD_ST_SUBSTATE_COUNT(22,2);
          _SFD_ST_SUBSTATE_INDEX(22,0,23);
          _SFD_ST_SUBSTATE_INDEX(22,1,24);
          _SFD_ST_SUBSTATE_COUNT(23,0);
          _SFD_ST_SUBSTATE_COUNT(24,0);
          _SFD_ST_SUBSTATE_COUNT(25,0);
          _SFD_ST_SUBSTATE_COUNT(26,0);
          _SFD_ST_SUBSTATE_COUNT(27,3);
          _SFD_ST_SUBSTATE_INDEX(27,0,28);
          _SFD_ST_SUBSTATE_INDEX(27,1,31);
          _SFD_ST_SUBSTATE_INDEX(27,2,46);
          _SFD_ST_SUBSTATE_COUNT(28,0);
          _SFD_ST_SUBSTATE_COUNT(31,3);
          _SFD_ST_SUBSTATE_INDEX(31,0,32);
          _SFD_ST_SUBSTATE_INDEX(31,1,33);
          _SFD_ST_SUBSTATE_INDEX(31,2,40);
          _SFD_ST_SUBSTATE_COUNT(32,0);
          _SFD_ST_SUBSTATE_COUNT(33,2);
          _SFD_ST_SUBSTATE_INDEX(33,0,34);
          _SFD_ST_SUBSTATE_INDEX(33,1,39);
          _SFD_ST_SUBSTATE_COUNT(34,4);
          _SFD_ST_SUBSTATE_INDEX(34,0,35);
          _SFD_ST_SUBSTATE_INDEX(34,1,36);
          _SFD_ST_SUBSTATE_INDEX(34,2,37);
          _SFD_ST_SUBSTATE_INDEX(34,3,38);
          _SFD_ST_SUBSTATE_COUNT(35,0);
          _SFD_ST_SUBSTATE_COUNT(36,0);
          _SFD_ST_SUBSTATE_COUNT(37,0);
          _SFD_ST_SUBSTATE_COUNT(38,0);
          _SFD_ST_SUBSTATE_COUNT(39,0);
          _SFD_ST_SUBSTATE_COUNT(40,2);
          _SFD_ST_SUBSTATE_INDEX(40,0,41);
          _SFD_ST_SUBSTATE_INDEX(40,1,45);
          _SFD_ST_SUBSTATE_COUNT(41,3);
          _SFD_ST_SUBSTATE_INDEX(41,0,42);
          _SFD_ST_SUBSTATE_INDEX(41,1,43);
          _SFD_ST_SUBSTATE_INDEX(41,2,44);
          _SFD_ST_SUBSTATE_COUNT(42,0);
          _SFD_ST_SUBSTATE_COUNT(43,0);
          _SFD_ST_SUBSTATE_COUNT(44,0);
          _SFD_ST_SUBSTATE_COUNT(45,0);
          _SFD_ST_SUBSTATE_COUNT(46,0);
        }

        _SFD_CV_INIT_CHART(4,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,4,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartDecMap[] = { 161, 204 };

          static unsigned int sEndDecMap[] = { 177, 221 };

          _SFD_CV_INIT_STATE(7,0,0,0,0,2,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(10,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(11,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(12,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(13,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(14,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(15,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(16,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(17,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(18,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(19,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartDecMap[] = { 168, 211 };

          static unsigned int sEndDecMap[] = { 184, 228 };

          _SFD_CV_INIT_STATE(20,0,0,0,0,2,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(21,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(22,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(23,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartDecMap[] = { 227 };

          static unsigned int sEndDecMap[] = { 243 };

          _SFD_CV_INIT_STATE(24,0,0,0,0,1,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          static unsigned int sStartDecMap[] = { 169, 212 };

          static unsigned int sEndDecMap[] = { 185, 229 };

          _SFD_CV_INIT_STATE(25,0,0,0,0,2,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(26,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(27,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(28,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(31,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(32,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(33,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(34,4,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(38,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartDecMap[] = { 227, 270 };

          static unsigned int sEndDecMap[] = { 243, 287 };

          _SFD_CV_INIT_STATE(39,0,0,0,0,2,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(40,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(41,3,1,1,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartDecMap[] = { 232 };

          static unsigned int sEndDecMap[] = { 248 };

          _SFD_CV_INIT_STATE(42,0,0,0,0,1,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(43,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartDecMap[] = { 262 };

          static unsigned int sEndDecMap[] = { 278 };

          _SFD_CV_INIT_STATE(44,0,0,0,0,1,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          static unsigned int sStartDecMap[] = { 228, 271 };

          static unsigned int sEndDecMap[] = { 244, 288 };

          _SFD_CV_INIT_STATE(45,0,0,0,0,2,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(46,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(29,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(30,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 44 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(5,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 44 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 44 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(6,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 44 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(6,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 44 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(7,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 44 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(7,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 64 };

          static unsigned int sEndGuardMap[] = { 24, 57, 95 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(111,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 64 };

          static unsigned int sEndRelationalopMap[] = { 24, 57, 95 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(111,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 64 };

          static unsigned int sEndGuardMap[] = { 24, 57, 95 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(25,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 64 };

          static unsigned int sEndRelationalopMap[] = { 24, 57, 95 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(25,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 69, 102 };

          static unsigned int sEndGuardMap[] = { 24, 62, 95, 117 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(1,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 69 };

          static unsigned int sEndRelationalopMap[] = { 24, 62, 95 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 0, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(107,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(106,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(112,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(197,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(108,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(109,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(109,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(110,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(110,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(26,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(195,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(195,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(10,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(10,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(9,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(9,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 23 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(8,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(11,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 34 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(196,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 34 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(196,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(113,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 23 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(28,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(29,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(3,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 23 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(30,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(31,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(127,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 64, 102 };

          static unsigned int sEndGuardMap[] = { 24, 57, 95, 117 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(129,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 64 };

          static unsigned int sEndRelationalopMap[] = { 24, 57, 95 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(129,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 64 };

          static unsigned int sEndGuardMap[] = { 24, 57, 95 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(128,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 64 };

          static unsigned int sEndRelationalopMap[] = { 24, 57, 95 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(128,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(130,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(130,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(131,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 17 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(132,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(133,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(133,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(134,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 42 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(135,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 42 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(135,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(136,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(137,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(138,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(139,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(139,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(140,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(141,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(142,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(143,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(144,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(145,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(146,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(173,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(173,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 77 };

          static unsigned int sEndGuardMap[] = { 22, 70, 106 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(147,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 29, 77 };

          static unsigned int sEndRelationalopMap[] = { 70, 106 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(147,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(148,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 77 };

          static unsigned int sEndGuardMap[] = { 22, 70, 106 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(149,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 29, 77 };

          static unsigned int sEndRelationalopMap[] = { 70, 106 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(149,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(150,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(151,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(152,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(153,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(154,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(155,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(155,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(156,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 76 };

          static unsigned int sEndGuardMap[] = { 22, 69, 105 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(157,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 29, 76 };

          static unsigned int sEndRelationalopMap[] = { 69, 105 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(157,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(158,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 22, 69 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(159,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 29 };

          static unsigned int sEndRelationalopMap[] = { 69 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(159,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(160,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(160,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(161,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 29 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(162,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 29 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 2, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(162,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(163,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 25 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(164,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(165,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(166,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(166,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(167,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(167,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(168,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(168,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(169,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31 };

          static unsigned int sEndGuardMap[] = { 24, 60 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(170,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 31 };

          static unsigned int sEndRelationalopMap[] = { 60 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(170,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(171,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(172,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(174,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(175,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(176,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(177,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(177,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(178,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(179,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(179,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(180,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(181,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 24, 58 };

          static unsigned int sEndGuardMap[] = { 17, 51, 87 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(182,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 24, 58 };

          static unsigned int sEndRelationalopMap[] = { 51, 87 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 0, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(182,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(183,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(184,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(185,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(186,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(186,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(187,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(188,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(188,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(189,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(190,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(191,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(192,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(193,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(194,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(40,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 64, 102 };

          static unsigned int sEndGuardMap[] = { 24, 57, 95, 117 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(35,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 64 };

          static unsigned int sEndRelationalopMap[] = { 24, 57, 95 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(35,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 64 };

          static unsigned int sEndGuardMap[] = { 24, 57, 95 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(39,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 64 };

          static unsigned int sEndRelationalopMap[] = { 24, 57, 95 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(39,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(94,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(94,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(95,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 17 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(104,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(105,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(105,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(32,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 42 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(36,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 42 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(36,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(42,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(38,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(34,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(96,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(96,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(91,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(41,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(37,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(92,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(33,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(93,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(43,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(198,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(199,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(201,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(202,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(203,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(200,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(204,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(205,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(206,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(207,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(208,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(209,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(101,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(97,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(97,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 77 };

          static unsigned int sEndGuardMap[] = { 22, 70, 106 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(48,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 29, 77 };

          static unsigned int sEndRelationalopMap[] = { 70, 106 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(48,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(47,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 77 };

          static unsigned int sEndGuardMap[] = { 22, 70, 106 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(52,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 29, 77 };

          static unsigned int sEndRelationalopMap[] = { 70, 106 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(52,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(45,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(51,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(46,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(99,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(98,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(102,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(103,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(103,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(50,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 76 };

          static unsigned int sEndGuardMap[] = { 22, 69, 105 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(53,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 29, 76 };

          static unsigned int sEndRelationalopMap[] = { 69, 105 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(53,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(49,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 22, 69 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(44,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 29 };

          static unsigned int sEndRelationalopMap[] = { 69 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(44,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(13,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(13,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(114,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 29 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(121,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 29 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 2, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(121,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(123,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 31 };

          static unsigned int sEndGuardMap[] = { 24, 54 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(15,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(122,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(14,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(14,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(16,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(16,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(115,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(115,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(20,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31 };

          static unsigned int sEndGuardMap[] = { 24, 60 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(56,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 31 };

          static unsigned int sEndRelationalopMap[] = { 60 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(56,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(54,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(55,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(100,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(100,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(57,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(59,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(58,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(73,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31 };

          static unsigned int sEndGuardMap[] = { 23, 45 };

          static int sPostFixPredicateTree[] = { 0, 1, -1, -3 };

          _SFD_CV_INIT_TRANS(71,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),4,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(72,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(67,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31 };

          static unsigned int sEndGuardMap[] = { 23, 45 };

          static int sPostFixPredicateTree[] = { 0, 1, -1, -3 };

          _SFD_CV_INIT_TRANS(22,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),4,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(21,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(69,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(75,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31 };

          static unsigned int sEndGuardMap[] = { 23, 45 };

          static int sPostFixPredicateTree[] = { 0, 1, -1, -3 };

          _SFD_CV_INIT_TRANS(68,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),4,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(70,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 31 };

          static unsigned int sEndGuardMap[] = { 23, 45 };

          static int sPostFixPredicateTree[] = { 0, 1, -1, -3 };

          _SFD_CV_INIT_TRANS(74,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),4,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(66,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 31 };

          static unsigned int sEndGuardMap[] = { 24, 60 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(64,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 31 };

          static unsigned int sEndRelationalopMap[] = { 60 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(64,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(60,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(61,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(116,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(116,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(117,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(117,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(62,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(65,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(63,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(120,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(120,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(126,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(126,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(125,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(124,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 24, 58 };

          static unsigned int sEndGuardMap[] = { 17, 51, 87 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(90,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 24, 58 };

          static unsigned int sEndRelationalopMap[] = { 51, 87 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 0, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(90,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(89,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(88,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 30 };

          static unsigned int sEndGuardMap[] = { 23, 53 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(18,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(19,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(19,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(27,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(118,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(118,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(80,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(76,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(77,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(78,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(81,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(79,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(83,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31 };

          static unsigned int sEndGuardMap[] = { 23, 45 };

          static int sPostFixPredicateTree[] = { 0, 1, -1, -3 };

          _SFD_CV_INIT_TRANS(86,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),4,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(82,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 23 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(23,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 18 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(87,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(84,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 23 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(85,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(24,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(119,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(119,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)
          c105_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)
          c105_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)
          c105_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)
          c105_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_c_sf_marshallOut,(MexInFcnForType)
          c105_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(27,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(28,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(29,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(30,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(31,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(32,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(33,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(34,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(35,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(36,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(37,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(38,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(39,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(40,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(41,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(42,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(43,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(44,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(45,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(46,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(47,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(48,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(49,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(50,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(51,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(52,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(53,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(54,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(55,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(56,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(57,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(58,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(59,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c105_b_sf_marshallOut,(MexInFcnForType)
          c105_b_sf_marshallIn);
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
    SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc105_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(15U, (void *)
          chartInstance->c105_flag_AuxEnableFlash);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)
          chartInstance->c105_change_RightControlMode);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)
          chartInstance->c105_state_CommSecondary);
        _SFD_SET_DATA_VALUE_PTR(16U, (void *)
          chartInstance->c105_mode_LeftControl);
        _SFD_SET_DATA_VALUE_PTR(41U, (void *)&chartInstance->c105_MODE_LEFT_NONE);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)
          chartInstance->c105_change_LeftControlMode);
        _SFD_SET_DATA_VALUE_PTR(42U, (void *)
          &chartInstance->c105_MODE_LEFT_OFFSET);
        _SFD_SET_DATA_VALUE_PTR(39U, (void *)&chartInstance->c105_MODE_LEFT_AUX2);
        _SFD_SET_DATA_VALUE_PTR(40U, (void *)&chartInstance->c105_MODE_LEFT_AUX4);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)
          chartInstance->c105_valid_LeftControl);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)
          chartInstance->c105_valid_RightControl);
        _SFD_SET_DATA_VALUE_PTR(59U, (void *)
          chartInstance->c105__indexstate_Buzzer_address);
        _SFD_SET_DATA_VALUE_PTR(26U, (void *)
          &chartInstance->c105_DOUBLE_SHORT_BEEP);
        _SFD_SET_DATA_VALUE_PTR(55U, (void *)
          &chartInstance->c105_SINGLE_SHORT_BEEP);
        _SFD_SET_DATA_VALUE_PTR(48U, (void *)&chartInstance->c105_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(23U, (void *)
          &chartInstance->c105_CD_EMEA_CONTROLS_OPTION_A);
        _SFD_SET_DATA_VALUE_PTR(24U, (void *)
          &chartInstance->c105_CD_EMEA_CONTROLS_OPTION_B);
        _SFD_SET_DATA_VALUE_PTR(25U, (void *)
          &chartInstance->c105_CD_EMEA_CONTROLS_OPTION_C);
        _SFD_SET_DATA_VALUE_PTR(47U, (void *)&chartInstance->c105_NON_FUNCTIONAL);
        _SFD_SET_DATA_VALUE_PTR(50U, (void *)
          &chartInstance->c105_OFFSET_SELECT_LEFT);
        _SFD_SET_DATA_VALUE_PTR(51U, (void *)
          &chartInstance->c105_OFFSET_SELECT_RIGHT);
        _SFD_SET_DATA_VALUE_PTR(54U, (void *)
          &chartInstance->c105_SINGLE_MEDIUM_BEEP);
        _SFD_SET_DATA_VALUE_PTR(57U, (void *)
          &chartInstance->c105_TRIPLE_SHORT_BEEP);
        _SFD_SET_DATA_VALUE_PTR(17U, (void *)
          chartInstance->c105_mode_RightControl);
        _SFD_SET_DATA_VALUE_PTR(38U, (void *)&chartInstance->c105_INACTIVE);
        _SFD_SET_DATA_VALUE_PTR(43U, (void *)
          &chartInstance->c105_MODE_RIGHT_AUX1);
        _SFD_SET_DATA_VALUE_PTR(44U, (void *)
          &chartInstance->c105_MODE_RIGHT_AUX4);
        _SFD_SET_DATA_VALUE_PTR(45U, (void *)
          &chartInstance->c105_MODE_RIGHT_NONE);
        _SFD_SET_DATA_VALUE_PTR(46U, (void *)
          &chartInstance->c105_MODE_RIGHT_OFFSET);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c105_state_Console);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c105_state_Engine);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c105_state_System);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)chartInstance->c105_flag_InitEERead);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)chartInstance->c105_fault_Diverter);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)chartInstance->c105_state_AuxEnable);
        _SFD_SET_DATA_VALUE_PTR(18U, (void *)
          chartInstance->c105_check_LeftNeutral);
        _SFD_SET_DATA_VALUE_PTR(22U, (void *)&chartInstance->c105_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(37U, (void *)
          &chartInstance->c105_ENGINE_CRANKING);
        _SFD_SET_DATA_VALUE_PTR(56U, (void *)&chartInstance->c105_SYS_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(19U, (void *)
          chartInstance->c105_check_RightNeutral);
        _SFD_SET_DATA_VALUE_PTR(12U, (void *)
          chartInstance->c105_change_AuxEnable);
        _SFD_SET_DATA_VALUE_PTR(13U, (void *)
          chartInstance->c105_din_OffsetSelectSw);
        _SFD_SET_DATA_VALUE_PTR(14U, (void *)
          chartInstance->c105_change_OffsetSelectSw);
        _SFD_SET_DATA_VALUE_PTR(20U, (void *)chartInstance->c105_aux_inhibit);
        _SFD_SET_DATA_VALUE_PTR(52U, (void *)&chartInstance->c105_OORH);
        _SFD_SET_DATA_VALUE_PTR(53U, (void *)&chartInstance->c105_OORL);
        _SFD_SET_DATA_VALUE_PTR(49U, (void *)
          &chartInstance->c105_NO_COMMUNICATION);
        _SFD_SET_DATA_VALUE_PTR(21U, (void *)chartInstance->c105_display_request);
        _SFD_SET_DATA_VALUE_PTR(58U, (void *)
          chartInstance->c105_ee_ControlMode_address);
        _SFD_SET_DATA_VALUE_PTR(33U, (void *)&chartInstance->c105_EE_RT_A2_A1);
        _SFD_SET_DATA_VALUE_PTR(28U, (void *)&chartInstance->c105_EE_LT_A2_A4);
        _SFD_SET_DATA_VALUE_PTR(34U, (void *)&chartInstance->c105_EE_RT_A4_A1);
        _SFD_SET_DATA_VALUE_PTR(35U, (void *)&chartInstance->c105_EE_RT_A4_OF);
        _SFD_SET_DATA_VALUE_PTR(32U, (void *)&chartInstance->c105_EE_NA_NA);
        _SFD_SET_DATA_VALUE_PTR(36U, (void *)&chartInstance->c105_EE_RT_NA_OF);
        _SFD_SET_DATA_VALUE_PTR(29U, (void *)&chartInstance->c105_EE_LT_OF_A1);
        _SFD_SET_DATA_VALUE_PTR(30U, (void *)&chartInstance->c105_EE_LT_OF_A4);
        _SFD_SET_DATA_VALUE_PTR(31U, (void *)&chartInstance->c105_EE_LT_OF_NA);
        _SFD_SET_DATA_VALUE_PTR(27U, (void *)&chartInstance->c105_EE_LT_A2_A1);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)
          &chartInstance->c105_stored_ControlMode);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sShGWn5L2HPiQsOJQjIcAaF";
}

static void sf_opaque_initialize_c105_MX_Gtwy_Control(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc105_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c105_MX_Gtwy_Control((SFc105_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
  initialize_c105_MX_Gtwy_Control((SFc105_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c105_MX_Gtwy_Control(void *chartInstanceVar)
{
  enable_c105_MX_Gtwy_Control((SFc105_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c105_MX_Gtwy_Control(void *chartInstanceVar)
{
  disable_c105_MX_Gtwy_Control((SFc105_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c105_MX_Gtwy_Control(void *chartInstanceVar)
{
  sf_gateway_c105_MX_Gtwy_Control((SFc105_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c105_MX_Gtwy_Control(SimStruct* S)
{
  return get_sim_state_c105_MX_Gtwy_Control
    ((SFc105_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S));/* raw sim ctx */
}

static void sf_opaque_set_sim_state_c105_MX_Gtwy_Control(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c105_MX_Gtwy_Control((SFc105_MX_Gtwy_ControlInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c105_MX_Gtwy_Control(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc105_MX_Gtwy_ControlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MX_Gtwy_Control_optimization_info();
    }

    finalize_c105_MX_Gtwy_Control((SFc105_MX_Gtwy_ControlInstanceStruct*)
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
  initSimStructsc105_MX_Gtwy_Control((SFc105_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c105_MX_Gtwy_Control(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c105_MX_Gtwy_Control((SFc105_MX_Gtwy_ControlInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c105_MX_Gtwy_Control(SimStruct *S)
{
  /* Actual parameters from chart:
     ACTIVE CD_EMEA_CONTROLS_OPTION_A CD_EMEA_CONTROLS_OPTION_B CD_EMEA_CONTROLS_OPTION_C DOUBLE_SHORT_BEEP EE_LT_A2_A1 EE_LT_A2_A4 EE_LT_OF_A1 EE_LT_OF_A4 EE_LT_OF_NA EE_NA_NA EE_RT_A2_A1 EE_RT_A4_A1 EE_RT_A4_OF EE_RT_NA_OF ENGINE_CRANKING INACTIVE MODE_LEFT_AUX2 MODE_LEFT_AUX4 MODE_LEFT_NONE MODE_LEFT_OFFSET MODE_RIGHT_AUX1 MODE_RIGHT_AUX4 MODE_RIGHT_NONE MODE_RIGHT_OFFSET NON_FUNCTIONAL NORMAL NO_COMMUNICATION OFFSET_SELECT_LEFT OFFSET_SELECT_RIGHT OORH OORL SINGLE_MEDIUM_BEEP SINGLE_SHORT_BEEP SYS_NORMAL TRIPLE_SHORT_BEEP
   */
  const char_T *rtParamNames[] = { "ACTIVE", "CD_EMEA_CONTROLS_OPTION_A",
    "CD_EMEA_CONTROLS_OPTION_B", "CD_EMEA_CONTROLS_OPTION_C",
    "DOUBLE_SHORT_BEEP", "EE_LT_A2_A1", "EE_LT_A2_A4", "EE_LT_OF_A1",
    "EE_LT_OF_A4", "EE_LT_OF_NA", "EE_NA_NA", "EE_RT_A2_A1", "EE_RT_A4_A1",
    "EE_RT_A4_OF", "EE_RT_NA_OF", "ENGINE_CRANKING", "INACTIVE",
    "MODE_LEFT_AUX2", "MODE_LEFT_AUX4", "MODE_LEFT_NONE", "MODE_LEFT_OFFSET",
    "MODE_RIGHT_AUX1", "MODE_RIGHT_AUX4", "MODE_RIGHT_NONE", "MODE_RIGHT_OFFSET",
    "NON_FUNCTIONAL", "NORMAL", "NO_COMMUNICATION", "OFFSET_SELECT_LEFT",
    "OFFSET_SELECT_RIGHT", "OORH", "OORL", "SINGLE_MEDIUM_BEEP",
    "SINGLE_SHORT_BEEP", "SYS_NORMAL", "TRIPLE_SHORT_BEEP" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_UINT8);

  /* registration for CD_EMEA_CONTROLS_OPTION_A*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT8);

  /* registration for CD_EMEA_CONTROLS_OPTION_B*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT8);

  /* registration for CD_EMEA_CONTROLS_OPTION_C*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_UINT8);

  /* registration for DOUBLE_SHORT_BEEP*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_UINT8);

  /* registration for EE_LT_A2_A1*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_UINT8);

  /* registration for EE_LT_A2_A4*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_UINT8);

  /* registration for EE_LT_OF_A1*/
  ssRegDlgParamAsRunTimeParam(S, 7, 7, rtParamNames[7], SS_UINT8);

  /* registration for EE_LT_OF_A4*/
  ssRegDlgParamAsRunTimeParam(S, 8, 8, rtParamNames[8], SS_UINT8);

  /* registration for EE_LT_OF_NA*/
  ssRegDlgParamAsRunTimeParam(S, 9, 9, rtParamNames[9], SS_UINT8);

  /* registration for EE_NA_NA*/
  ssRegDlgParamAsRunTimeParam(S, 10, 10, rtParamNames[10], SS_UINT8);

  /* registration for EE_RT_A2_A1*/
  ssRegDlgParamAsRunTimeParam(S, 11, 11, rtParamNames[11], SS_UINT8);

  /* registration for EE_RT_A4_A1*/
  ssRegDlgParamAsRunTimeParam(S, 12, 12, rtParamNames[12], SS_UINT8);

  /* registration for EE_RT_A4_OF*/
  ssRegDlgParamAsRunTimeParam(S, 13, 13, rtParamNames[13], SS_UINT8);

  /* registration for EE_RT_NA_OF*/
  ssRegDlgParamAsRunTimeParam(S, 14, 14, rtParamNames[14], SS_UINT8);

  /* registration for ENGINE_CRANKING*/
  ssRegDlgParamAsRunTimeParam(S, 15, 15, rtParamNames[15], SS_UINT8);

  /* registration for INACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 16, 16, rtParamNames[16], SS_UINT8);

  /* registration for MODE_LEFT_AUX2*/
  ssRegDlgParamAsRunTimeParam(S, 17, 17, rtParamNames[17], SS_UINT8);

  /* registration for MODE_LEFT_AUX4*/
  ssRegDlgParamAsRunTimeParam(S, 18, 18, rtParamNames[18], SS_UINT8);

  /* registration for MODE_LEFT_NONE*/
  ssRegDlgParamAsRunTimeParam(S, 19, 19, rtParamNames[19], SS_UINT8);

  /* registration for MODE_LEFT_OFFSET*/
  ssRegDlgParamAsRunTimeParam(S, 20, 20, rtParamNames[20], SS_UINT8);

  /* registration for MODE_RIGHT_AUX1*/
  ssRegDlgParamAsRunTimeParam(S, 21, 21, rtParamNames[21], SS_UINT8);

  /* registration for MODE_RIGHT_AUX4*/
  ssRegDlgParamAsRunTimeParam(S, 22, 22, rtParamNames[22], SS_UINT8);

  /* registration for MODE_RIGHT_NONE*/
  ssRegDlgParamAsRunTimeParam(S, 23, 23, rtParamNames[23], SS_UINT8);

  /* registration for MODE_RIGHT_OFFSET*/
  ssRegDlgParamAsRunTimeParam(S, 24, 24, rtParamNames[24], SS_UINT8);

  /* registration for NON_FUNCTIONAL*/
  ssRegDlgParamAsRunTimeParam(S, 25, 25, rtParamNames[25], SS_UINT8);

  /* registration for NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 26, 26, rtParamNames[26], SS_UINT8);

  /* registration for NO_COMMUNICATION*/
  ssRegDlgParamAsRunTimeParam(S, 27, 27, rtParamNames[27], SS_UINT8);

  /* registration for OFFSET_SELECT_LEFT*/
  ssRegDlgParamAsRunTimeParam(S, 28, 28, rtParamNames[28], SS_UINT8);

  /* registration for OFFSET_SELECT_RIGHT*/
  ssRegDlgParamAsRunTimeParam(S, 29, 29, rtParamNames[29], SS_UINT8);

  /* registration for OORH*/
  ssRegDlgParamAsRunTimeParam(S, 30, 30, rtParamNames[30], SS_UINT8);

  /* registration for OORL*/
  ssRegDlgParamAsRunTimeParam(S, 31, 31, rtParamNames[31], SS_UINT8);

  /* registration for SINGLE_MEDIUM_BEEP*/
  ssRegDlgParamAsRunTimeParam(S, 32, 32, rtParamNames[32], SS_UINT8);

  /* registration for SINGLE_SHORT_BEEP*/
  ssRegDlgParamAsRunTimeParam(S, 33, 33, rtParamNames[33], SS_UINT8);

  /* registration for SYS_NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 34, 34, rtParamNames[34], SS_UINT8);

  /* registration for TRIPLE_SHORT_BEEP*/
  ssRegDlgParamAsRunTimeParam(S, 35, 35, rtParamNames[35], SS_UINT8);
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
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  ssSetModelReferenceSampleTimeDisallowInheritance(S);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MX_Gtwy_Control_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      105);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,105,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 105);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,105);
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
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,105,14);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,105,7);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=7; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 14; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,105);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3451740607U));
  ssSetChecksum1(S,(476510771U));
  ssSetChecksum2(S,(3339431802U));
  ssSetChecksum3(S,(2416132682U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c105_MX_Gtwy_Control(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c105_MX_Gtwy_Control(SimStruct *S)
{
  SFc105_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc105_MX_Gtwy_ControlInstanceStruct *)utMalloc(sizeof
    (SFc105_MX_Gtwy_ControlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc105_MX_Gtwy_ControlInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c105_MX_Gtwy_Control;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c105_MX_Gtwy_Control;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c105_MX_Gtwy_Control;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c105_MX_Gtwy_Control;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c105_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c105_MX_Gtwy_Control;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c105_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c105_MX_Gtwy_Control;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c105_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlStart = mdlStart_c105_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c105_MX_Gtwy_Control;
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
  mdl_start_c105_MX_Gtwy_Control(chartInstance);
}

void c105_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c105_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c105_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c105_MX_Gtwy_Control(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c105_MX_Gtwy_Control_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
