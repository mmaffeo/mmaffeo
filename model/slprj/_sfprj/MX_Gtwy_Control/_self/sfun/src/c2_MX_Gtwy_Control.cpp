/* Include files */

#include "MX_Gtwy_Control_sfun.h"
#include "c2_MX_Gtwy_Control.h"
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
#define c2_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c2_IN_Deluxe_G55               ((uint8_T)1U)
#define c2_IN_Normal                   ((uint8_T)2U)
#define c2_IN_NonFunctional            ((uint8_T)1U)
#define c2_IN_Off                      ((uint8_T)2U)
#define c2_IN_On                       ((uint8_T)3U)
#define c2_IN_Error                    ((uint8_T)1U)
#define c2_b_IN_NonFunctional          ((uint8_T)2U)
#define c2_b_IN_Normal                 ((uint8_T)3U)
#define c2_b_IN_Off                    ((uint8_T)1U)
#define c2_b_IN_On                     ((uint8_T)2U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initialize_params_c2_MX_Gtwy_Control
  (SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void enable_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void disable_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_MX_Gtwy_Control
  (SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_MX_Gtwy_Control
  (SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void set_sim_state_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct *
  chartInstance, const mxArray *c2_st);
static void c2_set_sim_state_side_effects_c2_MX_Gtwy_Control
  (SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void finalize_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void sf_gateway_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void mdl_start_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c2_chartstep_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initSimStructsc2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c2_Deluxe_G55(SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c2_exit_internal_Normal(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static int32_T c2_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_b_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_c_tp_Normal, const char_T *c2_identifier);
static uint8_T c2_c_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int8_T c2_d_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_e_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_b_setSimStateSideEffectsInfo, const char_T
  *c2_identifier);
static const mxArray *c2_f_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static const mxArray *sf_get_hover_data_for_msg
  (SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c2_ssid);
static void c2_init_sf_message_store_memory(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static int8_T c2__s8_u8_(SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance,
  uint8_T c2_b, uint32_T c2_ssid_src_loc, int32_T c2_offset_src_loc, int32_T
  c2_length_src_loc);
static int8_T c2_get_ee_AutoIdleEnabled(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c2_elementIndex);
static void c2_set_ee_AutoIdleEnabled(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c2_elementIndex, int8_T c2_elementValue);
static int8_T *c2_access_ee_AutoIdleEnabled(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c2_rdOnly);
static void init_dsm_address_info(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_MX_Gtwy_Control(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_doSetSimStateSideEffects = 0U;
  chartInstance->c2_setSimStateSideEffectsInfo = NULL;
  chartInstance->c2_is_Deluxe_G55 = c2_IN_NO_ACTIVE_CHILD;
  chartInstance->c2_tp_Deluxe_G55 = 0U;
  chartInstance->c2_tp_Error = 0U;
  chartInstance->c2_b_tp_NonFunctional = 0U;
  chartInstance->c2_b_is_Normal = c2_IN_NO_ACTIVE_CHILD;
  chartInstance->c2_b_tp_Normal = 0U;
  chartInstance->c2_b_tp_Off = 0U;
  chartInstance->c2_b_tp_On = 0U;
  chartInstance->c2_is_Normal = c2_IN_NO_ACTIVE_CHILD;
  chartInstance->c2_tp_Normal = 0U;
  chartInstance->c2_tp_NonFunctional = 0U;
  chartInstance->c2_tp_Off = 0U;
  chartInstance->c2_tp_On = 0U;
  chartInstance->c2_is_active_c2_MX_Gtwy_Control = 0U;
  chartInstance->c2_is_c2_MX_Gtwy_Control = c2_IN_NO_ACTIVE_CHILD;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c2_state_AutoIdleEnable = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_AutoIdleEnable, 4U);
  }
}

static void initialize_params_c2_MX_Gtwy_Control
  (SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  real_T c2_d0;
  real_T c2_d1;
  real_T c2_d2;
  real_T c2_d3;
  real_T c2_d4;
  real_T c2_d5;
  real_T c2_d6;
  sf_mex_import_named("INACTIVE", sf_mex_get_sfun_param(chartInstance->S, 3, 0),
                      &c2_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_INACTIVE = (uint8_T)c2_d0;
  sf_mex_import_named("ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c2_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_ACTIVE = (uint8_T)c2_d1;
  sf_mex_import_named("NORMAL", sf_mex_get_sfun_param(chartInstance->S, 6, 0),
                      &c2_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_NORMAL = (uint8_T)c2_d2;
  sf_mex_import_named("CD_AUTOIDLE_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 1, 0), &c2_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_CD_AUTOIDLE_FUNCTION = (uint8_T)c2_d3;
  sf_mex_import_named("NON_FUNCTIONAL", sf_mex_get_sfun_param(chartInstance->S,
    5, 0), &c2_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_NON_FUNCTIONAL = (uint8_T)c2_d4;
  sf_mex_import_named("CD_DELUXE_GEN5_5_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 2, 0), &c2_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_CD_DELUXE_GEN5_5_FUNCTION = (uint8_T)c2_d5;
  sf_mex_import_named("IN_ERROR", sf_mex_get_sfun_param(chartInstance->S, 4, 0),
                      &c2_d6, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c2_IN_ERROR = (uint8_T)c2_d6;
}

static void enable_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_MX_Gtwy_Control
  (SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  uint32_T c2_prevAniVal;
  c2_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c2_is_active_c2_MX_Gtwy_Control == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_c2_MX_Gtwy_Control == c2_IN_Normal) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_Normal == c2_IN_NonFunctional) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_Normal == c2_IN_On) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_Normal == c2_IN_Off) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_c2_MX_Gtwy_Control == c2_IN_Deluxe_G55) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_Deluxe_G55 == c2_b_IN_NonFunctional) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_Deluxe_G55 == c2_b_IN_Normal) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_b_is_Normal == c2_b_IN_Off) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_b_is_Normal == c2_b_IN_On) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_Deluxe_G55 == c2_IN_Error) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  }

  _SFD_SET_ANIMATION(c2_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c2_MX_Gtwy_Control
  (SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  uint8_T c2_hoistedGlobal;
  const mxArray *c2_b_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  const mxArray *c2_c_y = NULL;
  uint8_T c2_c_hoistedGlobal;
  const mxArray *c2_d_y = NULL;
  uint8_T c2_d_hoistedGlobal;
  const mxArray *c2_e_y = NULL;
  uint8_T c2_e_hoistedGlobal;
  const mxArray *c2_f_y = NULL;
  uint8_T c2_f_hoistedGlobal;
  const mxArray *c2_g_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(6, 1), false);
  c2_hoistedGlobal = *chartInstance->c2_state_AutoIdleEnable;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_hoistedGlobal, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = chartInstance->c2_is_active_c2_MX_Gtwy_Control;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_c_hoistedGlobal = chartInstance->c2_is_c2_MX_Gtwy_Control;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_d_hoistedGlobal = chartInstance->c2_is_Normal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_e_hoistedGlobal = chartInstance->c2_is_Deluxe_G55;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_e_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c2_y, 4, c2_f_y);
  c2_f_hoistedGlobal = chartInstance->c2_b_is_Normal;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_f_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c2_y, 5, c2_g_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct *
  chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  c2_u = sf_mex_dup(c2_st);
  *chartInstance->c2_state_AutoIdleEnable = c2_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 0)), "state_AutoIdleEnable");
  chartInstance->c2_is_active_c2_MX_Gtwy_Control = c2_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
     "is_active_c2_MX_Gtwy_Control");
  chartInstance->c2_is_c2_MX_Gtwy_Control = c2_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 2)), "is_c2_MX_Gtwy_Control");
  chartInstance->c2_is_Normal = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 3)), "is_Normal");
  chartInstance->c2_is_Deluxe_G55 = c2_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 4)), "is_Deluxe_G55");
  chartInstance->c2_b_is_Normal = c2_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 5)), "is_Normal");
  sf_mex_assign(&chartInstance->c2_setSimStateSideEffectsInfo,
                c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 6)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c2_u);
  chartInstance->c2_doSetSimStateSideEffects = 1U;
  c2_update_debugger_state_c2_MX_Gtwy_Control(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void c2_set_sim_state_side_effects_c2_MX_Gtwy_Control
  (SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  if (chartInstance->c2_doSetSimStateSideEffects != 0) {
    chartInstance->c2_tp_Deluxe_G55 = (uint8_T)
      (chartInstance->c2_is_c2_MX_Gtwy_Control == c2_IN_Deluxe_G55);
    chartInstance->c2_tp_Error = (uint8_T)(chartInstance->c2_is_Deluxe_G55 ==
      c2_IN_Error);
    chartInstance->c2_b_tp_NonFunctional = (uint8_T)
      (chartInstance->c2_is_Deluxe_G55 == c2_b_IN_NonFunctional);
    chartInstance->c2_b_tp_Normal = (uint8_T)(chartInstance->c2_is_Deluxe_G55 ==
      c2_b_IN_Normal);
    chartInstance->c2_b_tp_Off = (uint8_T)(chartInstance->c2_b_is_Normal ==
      c2_b_IN_Off);
    chartInstance->c2_b_tp_On = (uint8_T)(chartInstance->c2_b_is_Normal ==
      c2_b_IN_On);
    chartInstance->c2_tp_Normal = (uint8_T)
      (chartInstance->c2_is_c2_MX_Gtwy_Control == c2_IN_Normal);
    chartInstance->c2_tp_NonFunctional = (uint8_T)(chartInstance->c2_is_Normal ==
      c2_IN_NonFunctional);
    chartInstance->c2_tp_Off = (uint8_T)(chartInstance->c2_is_Normal ==
      c2_IN_Off);
    chartInstance->c2_tp_On = (uint8_T)(chartInstance->c2_is_Normal == c2_IN_On);
    chartInstance->c2_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c2_setSimStateSideEffectsInfo);
}

static void sf_gateway_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  c2_set_sim_state_side_effects_c2_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_dlx_G55_AutoIdleEnable, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_flag_InitEERead, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_LoadSense, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_AutoIdle_RisingEdge, 0U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MX_Gtwy_ControlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  c2_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void c2_chartstep_c2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c2_out;
  boolean_T c2_temp;
  boolean_T c2_b_temp;
  boolean_T c2_b_out;
  boolean_T c2_c_out;
  boolean_T c2_d_out;
  boolean_T c2_e_out;
  boolean_T c2_f_out;
  boolean_T guard1 = false;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  if (chartInstance->c2_is_active_c2_MX_Gtwy_Control == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
    chartInstance->c2_is_active_c2_MX_Gtwy_Control = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U, chartInstance->c2_sfEvent);
    c2_out = (CV_TRANSITION_EVAL(8U, (int32_T)(_SFD_CCP_CALL(5U, 8U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 8U, 0, (real_T)
      chartInstance->c2_CD_DELUXE_GEN5_5_FUNCTION, (real_T)
      chartInstance->c2_NON_FUNCTIONAL, 0, 0U,
      chartInstance->c2_CD_DELUXE_GEN5_5_FUNCTION ==
      chartInstance->c2_NON_FUNCTIONAL) != 0U, chartInstance->c2_sfEvent) != 0U))
              != 0);
    if (c2_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
      chartInstance->c2_is_c2_MX_Gtwy_Control = c2_IN_Normal;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_Normal = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
      chartInstance->c2_is_Normal = c2_IN_NonFunctional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_NonFunctional = 1U;
      *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_AutoIdleEnable, 4U);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c2_sfEvent);
      chartInstance->c2_is_c2_MX_Gtwy_Control = c2_IN_Deluxe_G55;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_Deluxe_G55 = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
      chartInstance->c2_is_Deluxe_G55 = c2_b_IN_NonFunctional;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
      chartInstance->c2_b_tp_NonFunctional = 1U;
      *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_AutoIdleEnable, 4U);
    }
  } else {
    switch (chartInstance->c2_is_c2_MX_Gtwy_Control) {
     case c2_IN_Deluxe_G55:
      CV_CHART_EVAL(1, 0, c2_IN_Deluxe_G55);
      c2_Deluxe_G55(chartInstance);
      break;

     case c2_IN_Normal:
      CV_CHART_EVAL(1, 0, c2_IN_Normal);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                   chartInstance->c2_sfEvent);
      switch (chartInstance->c2_is_Normal) {
       case c2_IN_NonFunctional:
        CV_STATE_EVAL(6, 0, c2_IN_NonFunctional);
        *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U,
                     chartInstance->c2_sfEvent);
        c2_temp = (_SFD_CCP_CALL(5U, 0U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 0U,
          0, (real_T)chartInstance->c2_CD_AUTOIDLE_FUNCTION, (real_T)
          chartInstance->c2_NON_FUNCTIONAL, 0, 1U,
          chartInstance->c2_CD_AUTOIDLE_FUNCTION !=
          chartInstance->c2_NON_FUNCTIONAL) != 0U, chartInstance->c2_sfEvent) !=
                   0U);
        if (c2_temp) {
          c2_temp = (_SFD_CCP_CALL(5U, 0U, 1, *chartInstance->c2_flag_InitEERead
                      != 0U, chartInstance->c2_sfEvent) != 0U);
        }

        c2_c_out = (CV_TRANSITION_EVAL(0U, (int32_T)c2_temp) != 0);
        if (c2_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                       chartInstance->c2_sfEvent);
          c2_f_out = (CV_TRANSITION_EVAL(2U, (int32_T)(_SFD_CCP_CALL(5U, 2U, 0,
            (c2_get_ee_AutoIdleEnabled(chartInstance, 0) != 0) != 0U,
            chartInstance->c2_sfEvent) != 0U)) != 0);
          if (c2_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
            chartInstance->c2_tp_NonFunctional = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
            chartInstance->c2_is_Normal = c2_IN_On;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
            chartInstance->c2_tp_On = 1U;
            *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_ACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c2_state_AutoIdleEnable, 4U);
            c2_set_ee_AutoIdleEnabled(chartInstance, 0, c2__s8_u8_(chartInstance,
              chartInstance->c2_ACTIVE, 10U, 59U, 6U));
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
            chartInstance->c2_tp_NonFunctional = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
            chartInstance->c2_is_Normal = c2_IN_Off;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
            chartInstance->c2_tp_Off = 1U;
            *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c2_state_AutoIdleEnable, 4U);
            c2_set_ee_AutoIdleEnabled(chartInstance, 0, c2__s8_u8_(chartInstance,
              chartInstance->c2_INACTIVE, 4U, 62U, 8U));
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
            matlab_UpdateEEVar();
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                       chartInstance->c2_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c2_sfEvent);
        break;

       case c2_IN_Off:
        CV_STATE_EVAL(6, 0, c2_IN_Off);
        *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                     chartInstance->c2_sfEvent);
        c2_b_temp = (_SFD_CCP_CALL(5U, 3U, 0,
          (*chartInstance->c2_AutoIdle_RisingEdge != 0) != 0U,
          chartInstance->c2_sfEvent) != 0U);
        if (c2_b_temp) {
          c2_b_temp = (_SFD_CCP_CALL(5U, 3U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
            3U, 0, (real_T)*chartInstance->c2_state_LoadSense, (real_T)
            chartInstance->c2_NORMAL, 0, 0U, *chartInstance->c2_state_LoadSense ==
            chartInstance->c2_NORMAL) != 0U, chartInstance->c2_sfEvent) != 0U);
        }

        c2_d_out = (CV_TRANSITION_EVAL(3U, (int32_T)c2_b_temp) != 0);
        if (c2_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
          chartInstance->c2_tp_Off = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
          chartInstance->c2_is_Normal = c2_IN_On;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
          chartInstance->c2_tp_On = 1U;
          *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_ACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_AutoIdleEnable,
                                4U);
          c2_set_ee_AutoIdleEnabled(chartInstance, 0, c2__s8_u8_(chartInstance,
            chartInstance->c2_ACTIVE, 10U, 59U, 6U));
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                       chartInstance->c2_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c2_sfEvent);
        break;

       case c2_IN_On:
        CV_STATE_EVAL(6, 0, c2_IN_On);
        *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_ACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                     chartInstance->c2_sfEvent);
        c2_b_out = (CV_TRANSITION_EVAL(5U, (int32_T)(_SFD_CCP_CALL(5U, 5U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 5U, 0, (real_T)
          *chartInstance->c2_state_LoadSense, (real_T)chartInstance->c2_NORMAL,
          0, 1U, *chartInstance->c2_state_LoadSense != chartInstance->c2_NORMAL)
          != 0U, chartInstance->c2_sfEvent) != 0U)) != 0);
        guard1 = false;
        if (c2_b_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
          guard1 = true;
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U,
                       chartInstance->c2_sfEvent);
          c2_e_out = (CV_TRANSITION_EVAL(4U, (int32_T)(_SFD_CCP_CALL(5U, 4U, 0,
            (*chartInstance->c2_AutoIdle_RisingEdge != 0) != 0U,
            chartInstance->c2_sfEvent) != 0U)) != 0);
          if (c2_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
            guard1 = true;
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                         chartInstance->c2_sfEvent);
          }
        }

        if (guard1) {
          chartInstance->c2_tp_On = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
          chartInstance->c2_is_Normal = c2_IN_Off;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
          chartInstance->c2_tp_Off = 1U;
          *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_AutoIdleEnable,
                                4U);
          c2_set_ee_AutoIdleEnabled(chartInstance, 0, c2__s8_u8_(chartInstance,
            chartInstance->c2_INACTIVE, 4U, 62U, 8U));
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c2_sfEvent);
        break;

       default:
        CV_STATE_EVAL(6, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c2_is_Normal = c2_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
        break;
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c2_sfEvent);
      break;

     default:
      CV_CHART_EVAL(1, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c2_is_c2_MX_Gtwy_Control = c2_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_MX_Gtwy_Control(SFc2_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void c2_Deluxe_G55(SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c2_out;
  boolean_T c2_b_out;
  boolean_T c2_c_out;
  boolean_T c2_d_out;
  boolean_T c2_e_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  switch (chartInstance->c2_is_Deluxe_G55) {
   case c2_IN_Error:
    CV_STATE_EVAL(0, 0, c2_IN_Error);
    *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_IN_ERROR;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                 chartInstance->c2_sfEvent);
    c2_b_out = (CV_TRANSITION_EVAL(15U, (int32_T)(_SFD_CCP_CALL(5U, 15U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 15U, 0, (real_T)
      *chartInstance->c2_state_LoadSense, (real_T)chartInstance->c2_NORMAL, 0,
      0U, *chartInstance->c2_state_LoadSense == chartInstance->c2_NORMAL) != 0U,
      chartInstance->c2_sfEvent) != 0U)) != 0);
    if (c2_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_Error = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
      chartInstance->c2_is_Deluxe_G55 = c2_b_IN_Normal;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
      chartInstance->c2_b_tp_Normal = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c2_sfEvent);
      chartInstance->c2_b_is_Normal = c2_b_IN_Off;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
      chartInstance->c2_b_tp_Off = 1U;
      *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_AutoIdleEnable, 4U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                   chartInstance->c2_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
    break;

   case c2_b_IN_NonFunctional:
    CV_STATE_EVAL(0, 0, c2_b_IN_NonFunctional);
    *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                 chartInstance->c2_sfEvent);
    c2_c_out = (CV_TRANSITION_EVAL(10U, (int32_T)(_SFD_CCP_CALL(5U, 10U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 10U, 0, (real_T)
      chartInstance->c2_CD_AUTOIDLE_FUNCTION, (real_T)
      chartInstance->c2_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c2_CD_AUTOIDLE_FUNCTION != chartInstance->c2_NON_FUNCTIONAL)
      != 0U, chartInstance->c2_sfEvent) != 0U)) != 0);
    if (c2_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c2_sfEvent);
      chartInstance->c2_b_tp_NonFunctional = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
      chartInstance->c2_is_Deluxe_G55 = c2_b_IN_Normal;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
      chartInstance->c2_b_tp_Normal = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c2_sfEvent);
      chartInstance->c2_b_is_Normal = c2_b_IN_Off;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
      chartInstance->c2_b_tp_Off = 1U;
      *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_AutoIdleEnable, 4U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                   chartInstance->c2_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c2_sfEvent);
    break;

   case c2_b_IN_Normal:
    CV_STATE_EVAL(0, 0, c2_b_IN_Normal);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U,
                 chartInstance->c2_sfEvent);
    c2_out = (CV_TRANSITION_EVAL(13U, (int32_T)(_SFD_CCP_CALL(5U, 13U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 13U, 0, (real_T)
      *chartInstance->c2_state_LoadSense, (real_T)chartInstance->c2_NORMAL, 0,
      1U, *chartInstance->c2_state_LoadSense != chartInstance->c2_NORMAL) != 0U,
      chartInstance->c2_sfEvent) != 0U)) != 0);
    if (c2_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c2_sfEvent);
      c2_exit_internal_Normal(chartInstance);
      chartInstance->c2_b_tp_Normal = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
      chartInstance->c2_is_Deluxe_G55 = c2_IN_Error;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_Error = 1U;
      *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_IN_ERROR;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_AutoIdleEnable, 4U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                   chartInstance->c2_sfEvent);
      switch (chartInstance->c2_b_is_Normal) {
       case c2_b_IN_Off:
        CV_STATE_EVAL(3, 0, c2_b_IN_Off);
        *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                     chartInstance->c2_sfEvent);
        c2_d_out = (CV_TRANSITION_EVAL(11U, (int32_T)(_SFD_CCP_CALL(5U, 11U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 11U, 0, (real_T)
          *chartInstance->c2_dlx_G55_AutoIdleEnable, (real_T)
          chartInstance->c2_ACTIVE, 0, 0U,
          *chartInstance->c2_dlx_G55_AutoIdleEnable == chartInstance->c2_ACTIVE)
          != 0U, chartInstance->c2_sfEvent) != 0U)) != 0);
        if (c2_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c2_sfEvent);
          chartInstance->c2_b_tp_Off = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
          chartInstance->c2_b_is_Normal = c2_b_IN_On;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
          chartInstance->c2_b_tp_On = 1U;
          *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_ACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_AutoIdleEnable,
                                4U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                       chartInstance->c2_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c2_sfEvent);
        break;

       case c2_b_IN_On:
        CV_STATE_EVAL(3, 0, c2_b_IN_On);
        *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_ACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 12U,
                     chartInstance->c2_sfEvent);
        c2_e_out = (CV_TRANSITION_EVAL(12U, (int32_T)(_SFD_CCP_CALL(5U, 12U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 12U, 0, (real_T)
          *chartInstance->c2_dlx_G55_AutoIdleEnable, (real_T)
          chartInstance->c2_ACTIVE, 0, 1U,
          *chartInstance->c2_dlx_G55_AutoIdleEnable != chartInstance->c2_ACTIVE)
          != 0U, chartInstance->c2_sfEvent) != 0U)) != 0);
        if (c2_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c2_sfEvent);
          chartInstance->c2_b_tp_On = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
          chartInstance->c2_b_is_Normal = c2_b_IN_Off;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
          chartInstance->c2_b_tp_Off = 1U;
          *chartInstance->c2_state_AutoIdleEnable = chartInstance->c2_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c2_state_AutoIdleEnable,
                                4U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                       chartInstance->c2_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c2_sfEvent);
        break;

       default:
        CV_STATE_EVAL(3, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c2_b_is_Normal = c2_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c2_sfEvent);
    break;

   default:
    CV_STATE_EVAL(0, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c2_is_Deluxe_G55 = c2_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void c2_exit_internal_Normal(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c2_b_is_Normal) {
   case c2_b_IN_Off:
    CV_STATE_EVAL(3, 1, c2_b_IN_Off);
    chartInstance->c2_b_tp_Off = 0U;
    chartInstance->c2_b_is_Normal = c2_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
    break;

   case c2_b_IN_On:
    CV_STATE_EVAL(3, 1, c2_b_IN_On);
    chartInstance->c2_b_tp_On = 0U;
    chartInstance->c2_b_is_Normal = c2_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
    break;

   default:
    CV_STATE_EVAL(3, 1, 0);
    chartInstance->c2_b_is_Normal = c2_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
    break;
  }
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)(c2_machineNumber);
  (void)(c2_chartNumber);
  (void)(c2_instanceNumber);
}

const mxArray *sf_c2_MX_Gtwy_Control_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i0, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent), &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static uint8_T c2_b_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_c_tp_Normal, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_c_tp_Normal),
    &c2_thisId);
  sf_mex_destroy(&c2_c_tp_Normal);
  return c2_y;
}

static uint8_T c2_c_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_c_tp_Normal;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c2_c_tp_Normal = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_c_tp_Normal),
    &c2_thisId);
  sf_mex_destroy(&c2_c_tp_Normal);
  *(uint8_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(int8_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 2, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int8_T c2_d_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int8_T c2_y;
  int8_T c2_i1;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i1, 1, 2, 0U, 0, 0U, 0);
  c2_y = c2_i1;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_ee_AutoIdleEnabled;
  emlrtMsgIdentifier c2_thisId;
  int8_T c2_y;
  SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c2_ee_AutoIdleEnabled = sf_mex_dup(c2_mxArrayInData);
  c2_thisId.fIdentifier = (const char *)c2_varName;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_ee_AutoIdleEnabled),
    &c2_thisId);
  sf_mex_destroy(&c2_ee_AutoIdleEnabled);
  *(int8_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  boolean_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(boolean_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_b_setSimStateSideEffectsInfo, const char_T
  *c2_identifier)
{
  const mxArray *c2_y = NULL;
  emlrtMsgIdentifier c2_thisId;
  c2_y = NULL;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  sf_mex_assign(&c2_y, c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_setSimStateSideEffectsInfo), &c2_thisId), false);
  sf_mex_destroy(&c2_b_setSimStateSideEffectsInfo);
  return c2_y;
}

static const mxArray *c2_f_emlrt_marshallIn(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  const mxArray *c2_y = NULL;
  (void)chartInstance;
  (void)c2_parentId;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_u), false);
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static const mxArray *sf_get_hover_data_for_msg
  (SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c2_ssid)
{
  (void)chartInstance;
  (void)c2_ssid;
  return NULL;
}

static void c2_init_sf_message_store_memory(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static int8_T c2__s8_u8_(SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance,
  uint8_T c2_b, uint32_T c2_ssid_src_loc, int32_T c2_offset_src_loc, int32_T
  c2_length_src_loc)
{
  int8_T c2_a;
  (void)chartInstance;
  c2_a = (int8_T)c2_b;
  if (c2_a < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c2_ssid_src_loc, c2_offset_src_loc,
      c2_length_src_loc);
  }

  return c2_a;
}

static int8_T c2_get_ee_AutoIdleEnabled(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c2_elementIndex)
{
  if (chartInstance->c2_dsmdiag_ee_AutoIdleEnabled) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, "ee_AutoIdleEnabled",
      c2_elementIndex);
  }

  return *chartInstance->c2_ee_AutoIdleEnabled_address;
}

static void c2_set_ee_AutoIdleEnabled(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c2_elementIndex, int8_T c2_elementValue)
{
  if (chartInstance->c2_dsmdiag_ee_AutoIdleEnabled) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, "ee_AutoIdleEnabled",
      c2_elementIndex);
  }

  *chartInstance->c2_ee_AutoIdleEnabled_address = c2_elementValue;
}

static int8_T *c2_access_ee_AutoIdleEnabled(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c2_rdOnly)
{
  if (chartInstance->c2_dsmdiag_ee_AutoIdleEnabled) {
    ssAccessDataStore_wrapper(chartInstance->S, 0, "ee_AutoIdleEnabled",
      c2_rdOnly);
  }

  return chartInstance->c2_ee_AutoIdleEnabled_address;
}

static void init_dsm_address_info(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_AutoIdleEnabled",
    (void **)&chartInstance->c2_ee_AutoIdleEnabled_address,
    &chartInstance->c2__indexoIdleEnabled);
}

static void init_simulink_io_address(SFc2_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  chartInstance->c2_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c2_state_AutoIdleEnable = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c2_AutoIdle_RisingEdge = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 0);
  chartInstance->c2_state_LoadSense = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_flag_InitEERead = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_dlx_G55_AutoIdleEnable = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c2_dsmdiag_ee_AutoIdleEnabled = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 0,
    "ee_AutoIdleEnabled");
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

void sf_c2_MX_Gtwy_Control_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1520332181U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1830307908U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3598338260U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1175490996U);
}

mxArray* sf_c2_MX_Gtwy_Control_get_post_codegen_info(void);
mxArray *sf_c2_MX_Gtwy_Control_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("07qmQvLt6nKjj3fj1HZKJ");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
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
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_MX_Gtwy_Control_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_MX_Gtwy_Control_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_MX_Gtwy_Control_jit_fallback_info(void)
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

mxArray *sf_c2_MX_Gtwy_Control_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_MX_Gtwy_Control_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c2_MX_Gtwy_Control(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[1],T\"state_AutoIdleEnable\",},{M[8],M[0],T\"is_active_c2_MX_Gtwy_Control\",},{M[9],M[0],T\"is_c2_MX_Gtwy_Control\",},{M[9],M[73],T\"is_Normal\",},{M[9],M[77],T\"is_Deluxe_G55\",},{M[9],M[90],T\"is_Normal\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_MX_Gtwy_Control_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc2_MX_Gtwy_ControlInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc2_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MX_Gtwy_ControlMachineNumber_,
           2,
           10,
           17,
           0,
           13,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"AutoIdle_RisingEdge");
          _SFD_SET_DATA_PROPS(1,1,1,0,"state_LoadSense");
          _SFD_SET_DATA_PROPS(2,1,1,0,"flag_InitEERead");
          _SFD_SET_DATA_PROPS(3,1,1,0,"dlx_G55_AutoIdleEnable");
          _SFD_SET_DATA_PROPS(4,2,0,1,"state_AutoIdleEnable");
          _SFD_SET_DATA_PROPS(5,10,0,0,"ACTIVE");
          _SFD_SET_DATA_PROPS(6,10,0,0,"CD_AUTOIDLE_FUNCTION");
          _SFD_SET_DATA_PROPS(7,10,0,0,"CD_DELUXE_GEN5_5_FUNCTION");
          _SFD_SET_DATA_PROPS(8,10,0,0,"INACTIVE");
          _SFD_SET_DATA_PROPS(9,10,0,0,"IN_ERROR");
          _SFD_SET_DATA_PROPS(10,10,0,0,"NON_FUNCTIONAL");
          _SFD_SET_DATA_PROPS(11,10,0,0,"NORMAL");
          _SFD_SET_DATA_PROPS(12,11,0,0,"ee_AutoIdleEnabled");
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
          _SFD_CH_SUBSTATE_COUNT(2);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,6);
          _SFD_ST_SUBSTATE_COUNT(0,3);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,2);
          _SFD_ST_SUBSTATE_INDEX(0,2,3);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,2);
          _SFD_ST_SUBSTATE_INDEX(3,0,4);
          _SFD_ST_SUBSTATE_INDEX(3,1,5);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,3);
          _SFD_ST_SUBSTATE_INDEX(6,0,7);
          _SFD_ST_SUBSTATE_INDEX(6,1,8);
          _SFD_ST_SUBSTATE_INDEX(6,2,9);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,0);
        }

        _SFD_CV_INIT_CHART(2,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,3,1,0,0,0,NULL,NULL);
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

        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 44 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(8,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 44 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(8,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(14,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 46 };

          static unsigned int sEndGuardMap[] = { 39, 61 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(0,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 39 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(0,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 28 };

          static unsigned int sEndGuardMap[] = { 20, 53 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(3,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 28 };

          static unsigned int sEndRelationalopMap[] = { 53 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(3,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 20 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(4,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(5,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 26 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 39 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(10,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 39 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(10,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(13,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 26 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(13,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(15,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 26 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(15,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 33 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(11,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 33 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(11,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 33 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(12,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 33 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(12,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_INT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)c2_c_sf_marshallIn);
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
    SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc2_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)
          chartInstance->c2_state_AutoIdleEnable);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)
          chartInstance->c2_AutoIdle_RisingEdge);
        _SFD_SET_DATA_VALUE_PTR(12U, (void *)
          chartInstance->c2_ee_AutoIdleEnabled_address);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)&chartInstance->c2_INACTIVE);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)&chartInstance->c2_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c2_state_LoadSense);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)&chartInstance->c2_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)
          &chartInstance->c2_CD_AUTOIDLE_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)&chartInstance->c2_NON_FUNCTIONAL);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c2_flag_InitEERead);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)
          chartInstance->c2_dlx_G55_AutoIdleEnable);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)
          &chartInstance->c2_CD_DELUXE_GEN5_5_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)&chartInstance->c2_IN_ERROR);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "scMFRmMFG9bYgu9E22onI7D";
}

static void sf_opaque_initialize_c2_MX_Gtwy_Control(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_MX_Gtwy_Control((SFc2_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
  initialize_c2_MX_Gtwy_Control((SFc2_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_MX_Gtwy_Control(void *chartInstanceVar)
{
  enable_c2_MX_Gtwy_Control((SFc2_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_MX_Gtwy_Control(void *chartInstanceVar)
{
  disable_c2_MX_Gtwy_Control((SFc2_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_MX_Gtwy_Control(void *chartInstanceVar)
{
  sf_gateway_c2_MX_Gtwy_Control((SFc2_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_MX_Gtwy_Control(SimStruct* S)
{
  return get_sim_state_c2_MX_Gtwy_Control((SFc2_MX_Gtwy_ControlInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_MX_Gtwy_Control(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c2_MX_Gtwy_Control((SFc2_MX_Gtwy_ControlInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c2_MX_Gtwy_Control(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_MX_Gtwy_ControlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MX_Gtwy_Control_optimization_info();
    }

    finalize_c2_MX_Gtwy_Control((SFc2_MX_Gtwy_ControlInstanceStruct*)
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
  initSimStructsc2_MX_Gtwy_Control((SFc2_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_MX_Gtwy_Control(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_MX_Gtwy_Control((SFc2_MX_Gtwy_ControlInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_MX_Gtwy_Control(SimStruct *S)
{
  /* Actual parameters from chart:
     ACTIVE CD_AUTOIDLE_FUNCTION CD_DELUXE_GEN5_5_FUNCTION INACTIVE IN_ERROR NON_FUNCTIONAL NORMAL
   */
  const char_T *rtParamNames[] = { "ACTIVE", "CD_AUTOIDLE_FUNCTION",
    "CD_DELUXE_GEN5_5_FUNCTION", "INACTIVE", "IN_ERROR", "NON_FUNCTIONAL",
    "NORMAL" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_UINT8);

  /* registration for CD_AUTOIDLE_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT8);

  /* registration for CD_DELUXE_GEN5_5_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT8);

  /* registration for INACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_UINT8);

  /* registration for IN_ERROR*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_UINT8);

  /* registration for NON_FUNCTIONAL*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_UINT8);

  /* registration for NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_UINT8);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MX_Gtwy_Control_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 2);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2237567270U));
  ssSetChecksum1(S,(3226905491U));
  ssSetChecksum2(S,(2211256547U));
  ssSetChecksum3(S,(1878202086U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c2_MX_Gtwy_Control(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c2_MX_Gtwy_Control(SimStruct *S)
{
  SFc2_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc2_MX_Gtwy_ControlInstanceStruct *)utMalloc(sizeof
    (SFc2_MX_Gtwy_ControlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_MX_Gtwy_ControlInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_MX_Gtwy_Control;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_MX_Gtwy_Control;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_MX_Gtwy_Control;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_MX_Gtwy_Control;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_MX_Gtwy_Control;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_MX_Gtwy_Control;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_MX_Gtwy_Control;
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
  mdl_start_c2_MX_Gtwy_Control(chartInstance);
}

void c2_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_MX_Gtwy_Control(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_MX_Gtwy_Control_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
