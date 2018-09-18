/* Include files */

#include "MX_Gtwy_Control_sfun.h"
#include "c1_MX_Gtwy_Control.h"
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
#define c1_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c1_IN_NORMAL                   ((uint8_T)1U)
#define c1_IN_SHUTDOWN                 ((uint8_T)2U)
#define c1_IN_ST_SHUTDOWN              ((uint8_T)3U)
#define c1_IN_CRANKING                 ((uint8_T)1U)
#define c1_IN_NOT_RUNNING              ((uint8_T)2U)
#define c1_IN_RUNNING                  ((uint8_T)3U)
#define c1_IN_FACTORY_TURBO_PRIMER     ((uint8_T)1U)
#define c1_IN_CHECK_HOUR_METER         ((uint8_T)1U)
#define c1_IN_HOUR_METER_EXCEEDED      ((uint8_T)2U)
#define c1_IN_PAUSE                    ((uint8_T)3U)
#define c1_IN_PREVENT_FUEL_MSG_ACTIVE  ((uint8_T)4U)
#define c1_IN_PREVENT_FUEL_MSG_INACTIVE ((uint8_T)5U)
#define c1_b_IN_NOT_RUNNING            ((uint8_T)1U)
#define c1_IN_WAIT_TO_START            ((uint8_T)2U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initialize_params_c1_MX_Gtwy_Control
  (SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void enable_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void disable_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_MX_Gtwy_Control
  (SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_MX_Gtwy_Control
  (SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void set_sim_state_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct *
  chartInstance, const mxArray *c1_st);
static void c1_set_sim_state_side_effects_c1_MX_Gtwy_Control
  (SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void finalize_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void sf_gateway_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void mdl_start_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initSimStructsc1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c1_enter_internal_NORMAL(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c1_b_NORMAL(SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c1_exit_internal_NORMAL(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c1_CRANKING(SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c1_exit_internal_CRANKING(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c1_exit_internal_NOT_RUNNING(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c1_RUNNING(SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static int32_T c1_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint8_T c1_b_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_b_tp_NORMAL, const char_T *c1_identifier);
static uint8_T c1_c_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint16_T c1_d_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_b_CD_ENGINE_SPEED_RUNNING, const char_T
  *c1_identifier);
static uint16_T c1_e_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint32_T c1_f_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static boolean_T c1_g_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_b_flag_PrimeComplete, const char_T
  *c1_identifier);
static boolean_T c1_h_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_i_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_b_setSimStateSideEffectsInfo, const char_T
  *c1_identifier);
static const mxArray *c1_j_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static const mxArray *sf_get_hover_data_for_msg
  (SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c1_ssid);
static void c1_init_sf_message_store_memory(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static uint16_T c1__u16_s32_(SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c1_b, uint32_T c1_ssid_src_loc, int32_T c1_offset_src_loc, int32_T
  c1_length_src_loc);
static int32_T c1__s32_add__(SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c1_b, int32_T c1_c, uint32_T c1_ssid_src_loc, int32_T
  c1_offset_src_loc, int32_T c1_length_src_loc);
static void init_dsm_address_info(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc1_MX_Gtwy_Control(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_doSetSimStateSideEffects = 0U;
  chartInstance->c1_setSimStateSideEffectsInfo = NULL;
  chartInstance->c1_is_NORMAL = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_NORMAL = 0U;
  chartInstance->c1_is_CRANKING = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_CRANKING = 0U;
  chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_FACTORY_TURBO_PRIMER = 0U;
  chartInstance->c1_tp_CHECK_HOUR_METER = 0U;
  chartInstance->c1_tp_HOUR_METER_EXCEEDED = 0U;
  chartInstance->c1_tp_PAUSE = 0U;
  chartInstance->c1_tp_PREVENT_FUEL_MSG_ACTIVE = 0U;
  chartInstance->c1_tp_PREVENT_FUEL_MSG_INACTIVE = 0U;
  chartInstance->c1_is_NOT_RUNNING = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_NOT_RUNNING = 0U;
  chartInstance->c1_b_tp_NOT_RUNNING = 0U;
  chartInstance->c1_tp_WAIT_TO_START = 0U;
  chartInstance->c1_tp_RUNNING = 0U;
  chartInstance->c1_tp_SHUTDOWN = 0U;
  chartInstance->c1_tp_ST_SHUTDOWN = 0U;
  chartInstance->c1_is_active_c1_MX_Gtwy_Control = 0U;
  chartInstance->c1_is_c1_MX_Gtwy_Control = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_debounceCount = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_debounceCount, 0U);
  chartInstance->c1_panelMissingDebounce = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_panelMissingDebounce, 3U);
  chartInstance->c1_debouncePrimer = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_debouncePrimer, 1U);
  chartInstance->c1_flag_PrimeComplete = false;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_flag_PrimeComplete, 2U);
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c1_state_Engine = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c1_state_TurboPrime = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_TurboPrime, 27U);
  }
}

static void initialize_params_c1_MX_Gtwy_Control
  (SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  real_T c1_d0;
  real_T c1_d1;
  real_T c1_d2;
  real_T c1_d3;
  real_T c1_d4;
  real_T c1_d5;
  real_T c1_d6;
  real_T c1_d7;
  real_T c1_d8;
  real_T c1_d9;
  real_T c1_d10;
  real_T c1_d11;
  real_T c1_d12;
  real_T c1_d13;
  real_T c1_d14;
  real_T c1_d15;
  real_T c1_d16;
  real_T c1_d17;
  real_T c1_d18;
  real_T c1_d19;
  real_T c1_d20;
  real_T c1_d21;
  real_T c1_d22;
  real_T c1_d23;
  real_T c1_d24;
  real_T c1_d25;
  sf_mex_import_named("CD_ENGINE_SPEED_RUNNING", sf_mex_get_sfun_param
                      (chartInstance->S, 5, 0), &c1_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_ENGINE_SPEED_RUNNING = (uint16_T)c1_d0;
  sf_mex_import_named("CD_ENGINE_SPEED_NOT_RUNNING", sf_mex_get_sfun_param
                      (chartInstance->S, 4, 0), &c1_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_ENGINE_SPEED_NOT_RUNNING = (uint16_T)c1_d1;
  sf_mex_import_named("ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c1_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_ACTIVE = (uint8_T)c1_d2;
  sf_mex_import_named("ENGINE_CRANKING", sf_mex_get_sfun_param(chartInstance->S,
    12, 0), &c1_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_ENGINE_CRANKING = (uint8_T)c1_d3;
  sf_mex_import_named("ENGINE_NOT_RUNNING", sf_mex_get_sfun_param
                      (chartInstance->S, 14, 0), &c1_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_ENGINE_NOT_RUNNING = (uint8_T)c1_d4;
  sf_mex_import_named("ENGINE_RUNNING", sf_mex_get_sfun_param(chartInstance->S,
    16, 0), &c1_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_ENGINE_RUNNING = (uint8_T)c1_d5;
  sf_mex_import_named("INACTIVE", sf_mex_get_sfun_param(chartInstance->S, 17, 0),
                      &c1_d6, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_INACTIVE = (uint8_T)c1_d6;
  sf_mex_import_named("SHUTDOWN", sf_mex_get_sfun_param(chartInstance->S, 22, 0),
                      &c1_d7, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_SHUTDOWN = (uint8_T)c1_d7;
  sf_mex_import_named("SYS_NORMAL", sf_mex_get_sfun_param(chartInstance->S, 24,
    0), &c1_d8, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_SYS_NORMAL = (uint8_T)c1_d8;
  sf_mex_import_named("NO_COMMUNICATION", sf_mex_get_sfun_param(chartInstance->S,
    21, 0), &c1_d9, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_NO_COMMUNICATION = (uint8_T)c1_d9;
  sf_mex_import_named("CD_PANEL_SHUTDOWN_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 11, 0), &c1_d10, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_PANEL_SHUTDOWN_FUNCTION = (uint8_T)c1_d10;
  sf_mex_import_named("NON_FUNCTIONAL", sf_mex_get_sfun_param(chartInstance->S,
    19, 0), &c1_d11, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_NON_FUNCTIONAL = (uint8_T)c1_d11;
  sf_mex_import_named("MULTIPLE", sf_mex_get_sfun_param(chartInstance->S, 18, 0),
                      &c1_d12, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_MULTIPLE = (uint8_T)c1_d12;
  sf_mex_import_named("ENGINE_OFF", sf_mex_get_sfun_param(chartInstance->S, 15,
    0), &c1_d13, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_ENGINE_OFF = (uint8_T)c1_d13;
  sf_mex_import_named("NORMAL", sf_mex_get_sfun_param(chartInstance->S, 20, 0),
                      &c1_d14, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_NORMAL = (uint8_T)c1_d14;
  sf_mex_import_named("CD_ECU_FUNCTION", sf_mex_get_sfun_param(chartInstance->S,
    2, 0), &c1_d15, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_ECU_FUNCTION = (uint8_T)c1_d15;
  sf_mex_import_named("ENGINE_INITIALIZE", sf_mex_get_sfun_param
                      (chartInstance->S, 13, 0), &c1_d16, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_ENGINE_INITIALIZE = (uint8_T)c1_d16;
  sf_mex_import_named("CD_ECU_DEBOUNCE_WAIT_TO_START", sf_mex_get_sfun_param
                      (chartInstance->S, 1, 0), &c1_d17, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_ECU_DEBOUNCE_WAIT_TO_START = (uint16_T)c1_d17;
  sf_mex_import_named("STARTER_INHIBITED", sf_mex_get_sfun_param
                      (chartInstance->S, 23, 0), &c1_d18, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_STARTER_INHIBITED = (uint8_T)c1_d18;
  sf_mex_import_named("CD_PANEL_SHUTDOWN_DEBOUNCE", sf_mex_get_sfun_param
                      (chartInstance->S, 10, 0), &c1_d19, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_PANEL_SHUTDOWN_DEBOUNCE = (uint16_T)c1_d19;
  sf_mex_import_named("CD_EMEA_CONSOLE_CRANK_INHIBIT", sf_mex_get_sfun_param
                      (chartInstance->S, 3, 0), &c1_d20, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_EMEA_CONSOLE_CRANK_INHIBIT = (uint8_T)c1_d20;
  sf_mex_import_named("CD_FACTORY_TURBO_PRIME_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 8, 0), &c1_d21, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_FACTORY_TURBO_PRIME_FUNCTION = (uint8_T)c1_d21;
  sf_mex_import_named("CD_FACTORY_TURBO_PRIME_HOUR_ENABLE",
                      sf_mex_get_sfun_param(chartInstance->S, 9, 0), &c1_d22, 0,
                      0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_FACTORY_TURBO_PRIME_HOUR_ENABLE = (uint32_T)c1_d22;
  sf_mex_import_named("TURBO_PRIME_ACTIVE", sf_mex_get_sfun_param
                      (chartInstance->S, 25, 0), &c1_d23, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c1_TURBO_PRIME_ACTIVE = (uint8_T)c1_d23;
  sf_mex_import_named("CD_FACTORY_TURBO_PRIME_DEBOUNCE_DISABLE_FUEL",
                      sf_mex_get_sfun_param(chartInstance->S, 6, 0), &c1_d24, 0,
                      0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_FACTORY_TURBO_PRIME_DEBOUNCE_DISABLE_FUEL = (uint16_T)
    c1_d24;
  sf_mex_import_named("CD_FACTORY_TURBO_PRIME_DEBOUNCE_WAIT",
                      sf_mex_get_sfun_param(chartInstance->S, 7, 0), &c1_d25, 0,
                      0, 0U, 0, 0U, 0);
  chartInstance->c1_CD_FACTORY_TURBO_PRIME_DEBOUNCE_WAIT = (uint16_T)c1_d25;
}

static void enable_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_MX_Gtwy_Control
  (SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  uint32_T c1_prevAniVal;
  c1_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c1_is_active_c1_MX_Gtwy_Control == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_MX_Gtwy_Control == c1_IN_NORMAL) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_NORMAL == c1_IN_CRANKING) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_CRANKING == c1_IN_FACTORY_TURBO_PRIMER) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_FACTORY_TURBO_PRIMER == c1_IN_PREVENT_FUEL_MSG_ACTIVE)
  {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_FACTORY_TURBO_PRIMER == c1_IN_CHECK_HOUR_METER) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_FACTORY_TURBO_PRIMER == c1_IN_HOUR_METER_EXCEEDED) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_FACTORY_TURBO_PRIMER ==
      c1_IN_PREVENT_FUEL_MSG_INACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_FACTORY_TURBO_PRIMER == c1_IN_PAUSE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_NORMAL == c1_IN_NOT_RUNNING) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_NOT_RUNNING == c1_b_IN_NOT_RUNNING) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_NOT_RUNNING == c1_IN_WAIT_TO_START) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_NORMAL == c1_IN_RUNNING) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_MX_Gtwy_Control == c1_IN_ST_SHUTDOWN) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_MX_Gtwy_Control == c1_IN_SHUTDOWN) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
  }

  _SFD_SET_ANIMATION(c1_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c1_MX_Gtwy_Control
  (SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  uint8_T c1_hoistedGlobal;
  const mxArray *c1_b_y = NULL;
  uint8_T c1_b_hoistedGlobal;
  const mxArray *c1_c_y = NULL;
  uint16_T c1_c_hoistedGlobal;
  const mxArray *c1_d_y = NULL;
  uint16_T c1_d_hoistedGlobal;
  const mxArray *c1_e_y = NULL;
  boolean_T c1_e_hoistedGlobal;
  const mxArray *c1_f_y = NULL;
  uint16_T c1_f_hoistedGlobal;
  const mxArray *c1_g_y = NULL;
  uint8_T c1_g_hoistedGlobal;
  const mxArray *c1_h_y = NULL;
  uint8_T c1_h_hoistedGlobal;
  const mxArray *c1_i_y = NULL;
  uint8_T c1_i_hoistedGlobal;
  const mxArray *c1_j_y = NULL;
  uint8_T c1_j_hoistedGlobal;
  const mxArray *c1_k_y = NULL;
  uint8_T c1_k_hoistedGlobal;
  const mxArray *c1_l_y = NULL;
  uint8_T c1_l_hoistedGlobal;
  const mxArray *c1_m_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(12, 1), false);
  c1_hoistedGlobal = *chartInstance->c1_state_Engine;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_hoistedGlobal, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *chartInstance->c1_state_TurboPrime;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = chartInstance->c1_debounceCount;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = chartInstance->c1_debouncePrimer;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_e_hoistedGlobal = chartInstance->c1_flag_PrimeComplete;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_hoistedGlobal, 11, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_f_hoistedGlobal = chartInstance->c1_panelMissingDebounce;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_f_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_g_hoistedGlobal = chartInstance->c1_is_active_c1_MX_Gtwy_Control;
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_g_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_h_hoistedGlobal = chartInstance->c1_is_c1_MX_Gtwy_Control;
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_h_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 7, c1_i_y);
  c1_i_hoistedGlobal = chartInstance->c1_is_NOT_RUNNING;
  c1_j_y = NULL;
  sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_i_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_j_hoistedGlobal = chartInstance->c1_is_NORMAL;
  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_j_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 9, c1_k_y);
  c1_k_hoistedGlobal = chartInstance->c1_is_CRANKING;
  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", &c1_k_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 10, c1_l_y);
  c1_l_hoistedGlobal = chartInstance->c1_is_FACTORY_TURBO_PRIMER;
  c1_m_y = NULL;
  sf_mex_assign(&c1_m_y, sf_mex_create("y", &c1_l_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c1_y, 11, c1_m_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct *
  chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  c1_u = sf_mex_dup(c1_st);
  *chartInstance->c1_state_Engine = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 0)), "state_Engine");
  *chartInstance->c1_state_TurboPrime = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 1)), "state_TurboPrime");
  chartInstance->c1_debounceCount = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 2)), "debounceCount");
  chartInstance->c1_debouncePrimer = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 3)), "debouncePrimer");
  chartInstance->c1_flag_PrimeComplete = c1_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 4)), "flag_PrimeComplete");
  chartInstance->c1_panelMissingDebounce = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 5)), "panelMissingDebounce");
  chartInstance->c1_is_active_c1_MX_Gtwy_Control = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 6)),
     "is_active_c1_MX_Gtwy_Control");
  chartInstance->c1_is_c1_MX_Gtwy_Control = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 7)), "is_c1_MX_Gtwy_Control");
  chartInstance->c1_is_NOT_RUNNING = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 8)), "is_NOT_RUNNING");
  chartInstance->c1_is_NORMAL = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 9)), "is_NORMAL");
  chartInstance->c1_is_CRANKING = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 10)), "is_CRANKING");
  chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 11)),
     "is_FACTORY_TURBO_PRIMER");
  sf_mex_assign(&chartInstance->c1_setSimStateSideEffectsInfo,
                c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 12)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c1_u);
  chartInstance->c1_doSetSimStateSideEffects = 1U;
  c1_update_debugger_state_c1_MX_Gtwy_Control(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void c1_set_sim_state_side_effects_c1_MX_Gtwy_Control
  (SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  if (chartInstance->c1_doSetSimStateSideEffects != 0) {
    chartInstance->c1_tp_NORMAL = (uint8_T)
      (chartInstance->c1_is_c1_MX_Gtwy_Control == c1_IN_NORMAL);
    chartInstance->c1_tp_CRANKING = (uint8_T)(chartInstance->c1_is_NORMAL ==
      c1_IN_CRANKING);
    chartInstance->c1_tp_FACTORY_TURBO_PRIMER = (uint8_T)
      (chartInstance->c1_is_CRANKING == c1_IN_FACTORY_TURBO_PRIMER);
    chartInstance->c1_tp_CHECK_HOUR_METER = (uint8_T)
      (chartInstance->c1_is_FACTORY_TURBO_PRIMER == c1_IN_CHECK_HOUR_METER);
    chartInstance->c1_tp_HOUR_METER_EXCEEDED = (uint8_T)
      (chartInstance->c1_is_FACTORY_TURBO_PRIMER == c1_IN_HOUR_METER_EXCEEDED);
    chartInstance->c1_tp_PAUSE = (uint8_T)
      (chartInstance->c1_is_FACTORY_TURBO_PRIMER == c1_IN_PAUSE);
    chartInstance->c1_tp_PREVENT_FUEL_MSG_ACTIVE = (uint8_T)
      (chartInstance->c1_is_FACTORY_TURBO_PRIMER ==
       c1_IN_PREVENT_FUEL_MSG_ACTIVE);
    chartInstance->c1_tp_PREVENT_FUEL_MSG_INACTIVE = (uint8_T)
      (chartInstance->c1_is_FACTORY_TURBO_PRIMER ==
       c1_IN_PREVENT_FUEL_MSG_INACTIVE);
    chartInstance->c1_tp_NOT_RUNNING = (uint8_T)(chartInstance->c1_is_NORMAL ==
      c1_IN_NOT_RUNNING);
    chartInstance->c1_b_tp_NOT_RUNNING = (uint8_T)
      (chartInstance->c1_is_NOT_RUNNING == c1_b_IN_NOT_RUNNING);
    chartInstance->c1_tp_WAIT_TO_START = (uint8_T)
      (chartInstance->c1_is_NOT_RUNNING == c1_IN_WAIT_TO_START);
    chartInstance->c1_tp_RUNNING = (uint8_T)(chartInstance->c1_is_NORMAL ==
      c1_IN_RUNNING);
    chartInstance->c1_tp_SHUTDOWN = (uint8_T)
      (chartInstance->c1_is_c1_MX_Gtwy_Control == c1_IN_SHUTDOWN);
    chartInstance->c1_tp_ST_SHUTDOWN = (uint8_T)
      (chartInstance->c1_is_c1_MX_Gtwy_Control == c1_IN_ST_SHUTDOWN);
    chartInstance->c1_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c1_setSimStateSideEffectsInfo);
}

static void sf_gateway_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c1_temp;
  boolean_T c1_out;
  c1_set_sim_state_side_effects_c1_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_dv_TurboPrime, 25U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_actualHourMeter, 24U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Console, 23U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_CommDeluxeG55, 22U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_DeluxeG5, 21U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_CommStdPanel, 20U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_FuelTemp, 19U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_EngineSpeedDerate, 18U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_ecu_EngineStarterMode, 17U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_can_ACD_EStop, 16U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_can_ST_EStop, 15U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_CommECU, 14U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_KeylessPanel, 13U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_din_RemoteKey, 12U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_System, 11U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Key, 10U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_EngineStart, 9U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_HOT, 8U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_EOP, 7U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_ECT, 6U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_EngineSpeed, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_flt_EngineSpeed, 4U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  if (chartInstance->c1_is_active_c1_MX_Gtwy_Control == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_active_c1_MX_Gtwy_Control = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_c1_MX_Gtwy_Control = c1_IN_NORMAL;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_NORMAL = 1U;
    chartInstance->c1_panelMissingDebounce = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_panelMissingDebounce, 3U);
    chartInstance->c1_flag_PrimeComplete = false;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_flag_PrimeComplete, 2U);
    *chartInstance->c1_state_TurboPrime = chartInstance->c1_NORMAL;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_TurboPrime, 27U);
    c1_enter_internal_NORMAL(chartInstance);
  } else {
    switch (chartInstance->c1_is_c1_MX_Gtwy_Control) {
     case c1_IN_NORMAL:
      CV_CHART_EVAL(0, 0, c1_IN_NORMAL);
      c1_b_NORMAL(chartInstance);
      break;

     case c1_IN_SHUTDOWN:
      CV_CHART_EVAL(0, 0, c1_IN_SHUTDOWN);
      *chartInstance->c1_state_Engine = chartInstance->c1_SHUTDOWN;
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                   chartInstance->c1_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c1_sfEvent);
      break;

     case c1_IN_ST_SHUTDOWN:
      CV_CHART_EVAL(0, 0, c1_IN_ST_SHUTDOWN);
      *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_OFF;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                   chartInstance->c1_sfEvent);
      c1_temp = (_SFD_CCP_CALL(5U, 8U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 8U,
        0, (real_T)*chartInstance->c1_can_ST_EStop, (real_T)
        chartInstance->c1_INACTIVE, 0, 0U, *chartInstance->c1_can_ST_EStop ==
        chartInstance->c1_INACTIVE) != 0U, chartInstance->c1_sfEvent) != 0U);
      if (c1_temp) {
        c1_temp = (_SFD_CCP_CALL(5U, 8U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 8U,
          1, (real_T)*chartInstance->c1_can_ACD_EStop, (real_T)
          chartInstance->c1_INACTIVE, 0, 0U, *chartInstance->c1_can_ACD_EStop ==
          chartInstance->c1_INACTIVE) != 0U, chartInstance->c1_sfEvent) != 0U);
      }

      c1_out = (CV_TRANSITION_EVAL(8U, (int32_T)c1_temp) != 0);
      if (c1_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_ST_SHUTDOWN = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_c1_MX_Gtwy_Control = c1_IN_NORMAL;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_NORMAL = 1U;
        chartInstance->c1_panelMissingDebounce = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_panelMissingDebounce, 3U);
        chartInstance->c1_flag_PrimeComplete = false;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_flag_PrimeComplete, 2U);
        *chartInstance->c1_state_TurboPrime = chartInstance->c1_NORMAL;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_TurboPrime, 27U);
        c1_enter_internal_NORMAL(chartInstance);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U,
                     chartInstance->c1_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c1_sfEvent);
      break;

     default:
      CV_CHART_EVAL(0, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c1_is_c1_MX_Gtwy_Control = c1_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MX_Gtwy_ControlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  c1_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void initSimStructsc1_MX_Gtwy_Control(SFc1_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void c1_enter_internal_NORMAL(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
  chartInstance->c1_is_NORMAL = c1_IN_NOT_RUNNING;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  chartInstance->c1_tp_NOT_RUNNING = 1U;
  chartInstance->c1_is_NOT_RUNNING = c1_IN_WAIT_TO_START;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  chartInstance->c1_tp_WAIT_TO_START = 1U;
  *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_INITIALIZE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
  chartInstance->c1_debounceCount = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_debounceCount, 0U);
}

static void c1_b_NORMAL(SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c1_temp;
  boolean_T c1_out;
  boolean_T c1_b_out;
  boolean_T c1_b_temp;
  boolean_T c1_c_out;
  boolean_T c1_c_temp;
  boolean_T c1_d_temp;
  boolean_T c1_e_temp;
  boolean_T c1_f_temp;
  boolean_T c1_g_temp;
  boolean_T c1_h_temp;
  boolean_T c1_d_out;
  boolean_T c1_i_temp;
  boolean_T c1_j_temp;
  boolean_T c1_k_temp;
  boolean_T c1_l_temp;
  boolean_T c1_e_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U, chartInstance->c1_sfEvent);
  c1_temp = (_SFD_CCP_CALL(5U, 7U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 7U, 0,
    (real_T)*chartInstance->c1_can_ST_EStop, (real_T)chartInstance->c1_ACTIVE, 0,
    0U, *chartInstance->c1_can_ST_EStop == chartInstance->c1_ACTIVE) != 0U,
              chartInstance->c1_sfEvent) != 0U);
  if (!c1_temp) {
    c1_temp = (_SFD_CCP_CALL(5U, 7U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 7U, 1,
      (real_T)*chartInstance->c1_can_ACD_EStop, (real_T)chartInstance->c1_ACTIVE,
      0, 0U, *chartInstance->c1_can_ACD_EStop == chartInstance->c1_ACTIVE) != 0U,
                chartInstance->c1_sfEvent) != 0U);
  }

  c1_out = (CV_TRANSITION_EVAL(7U, (int32_T)c1_temp) != 0);
  if (c1_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
    c1_exit_internal_NORMAL(chartInstance);
    chartInstance->c1_tp_NORMAL = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_c1_MX_Gtwy_Control = c1_IN_ST_SHUTDOWN;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_ST_SHUTDOWN = 1U;
    *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_OFF;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
    SendMsg_03_Now();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U, chartInstance->c1_sfEvent);
    c1_b_out = (CV_TRANSITION_EVAL(6U, (int32_T)(_SFD_CCP_CALL(5U, 6U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 6U, 0, (real_T)
      *chartInstance->c1_state_Key, (real_T)chartInstance->c1_MULTIPLE, 0, 0U,
      *chartInstance->c1_state_Key == chartInstance->c1_MULTIPLE) != 0U,
      chartInstance->c1_sfEvent) != 0U)) != 0);
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
      c1_exit_internal_NORMAL(chartInstance);
      chartInstance->c1_tp_NORMAL = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_c1_MX_Gtwy_Control = c1_IN_SHUTDOWN;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_SHUTDOWN = 1U;
      *chartInstance->c1_state_Engine = chartInstance->c1_SHUTDOWN;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
      SendMsg_03_Now();
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                   chartInstance->c1_sfEvent);
      switch (chartInstance->c1_is_NORMAL) {
       case c1_IN_CRANKING:
        CV_STATE_EVAL(0, 0, c1_IN_CRANKING);
        c1_CRANKING(chartInstance);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
        break;

       case c1_IN_NOT_RUNNING:
        CV_STATE_EVAL(0, 0, c1_IN_NOT_RUNNING);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                     chartInstance->c1_sfEvent);
        c1_b_temp = (_SFD_CCP_CALL(5U, 3U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          3U, 0, (real_T)*chartInstance->c1_flt_EngineSpeed, (real_T)
          chartInstance->c1_CD_ENGINE_SPEED_RUNNING, 0, 5U,
          *chartInstance->c1_flt_EngineSpeed >=
          chartInstance->c1_CD_ENGINE_SPEED_RUNNING) != 0U,
          chartInstance->c1_sfEvent) != 0U);
        if (c1_b_temp) {
          c1_b_temp = (_SFD_CCP_CALL(5U, 3U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
            3U, 1, (real_T)*chartInstance->c1_state_System, (real_T)
            chartInstance->c1_SYS_NORMAL, 0, 0U, *chartInstance->c1_state_System
            == chartInstance->c1_SYS_NORMAL) != 0U, chartInstance->c1_sfEvent)
                       != 0U);
        }

        c1_c_out = (CV_TRANSITION_EVAL(3U, (int32_T)c1_b_temp) != 0);
        if (c1_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
          c1_exit_internal_NOT_RUNNING(chartInstance);
          chartInstance->c1_tp_NOT_RUNNING = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_NORMAL = c1_IN_RUNNING;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_RUNNING = 1U;
          *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_RUNNING;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
          SendMsg_03_Now();
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U,
                       chartInstance->c1_sfEvent);
          c1_c_temp = (_SFD_CCP_CALL(5U, 0U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
            0U, 0, (real_T)*chartInstance->c1_state_EngineStart, (real_T)
            chartInstance->c1_ACTIVE, 0, 0U,
            *chartInstance->c1_state_EngineStart == chartInstance->c1_ACTIVE) !=
            0U, chartInstance->c1_sfEvent) != 0U);
          if (c1_c_temp) {
            c1_c_temp = (_SFD_CCP_CALL(5U, 0U, 1, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 0U, 1, (real_T)*chartInstance->c1_state_Key, (real_T)
               chartInstance->c1_ACTIVE, 0, 0U, *chartInstance->c1_state_Key ==
               chartInstance->c1_ACTIVE) != 0U, chartInstance->c1_sfEvent) != 0U);
          }

          c1_d_temp = c1_c_temp;
          if (c1_c_temp) {
            c1_d_temp = (_SFD_CCP_CALL(5U, 0U, 2, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 0U, 2, (real_T)*chartInstance->c1_state_System, (real_T)
               chartInstance->c1_SYS_NORMAL, 0, 0U,
               *chartInstance->c1_state_System == chartInstance->c1_SYS_NORMAL)
              != 0U, chartInstance->c1_sfEvent) != 0U);
          }

          c1_e_temp = c1_d_temp;
          if (c1_d_temp) {
            c1_f_temp = (_SFD_CCP_CALL(5U, 0U, 3, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 0U, 3, (real_T)
               chartInstance->c1_CD_EMEA_CONSOLE_CRANK_INHIBIT, (real_T)
               chartInstance->c1_NON_FUNCTIONAL, 0, 0U,
               chartInstance->c1_CD_EMEA_CONSOLE_CRANK_INHIBIT ==
               chartInstance->c1_NON_FUNCTIONAL) != 0U,
              chartInstance->c1_sfEvent) != 0U);
            if (!c1_f_temp) {
              c1_f_temp = (_SFD_CCP_CALL(5U, 0U, 4, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 0U, 4, (real_T)
                                   *chartInstance->c1_state_Console, (real_T)
                                   chartInstance->c1_INACTIVE, 0, 0U,
                                   *chartInstance->c1_state_Console ==
                                   chartInstance->c1_INACTIVE) != 0U,
                chartInstance->c1_sfEvent) != 0U);
            }

            c1_e_temp = c1_f_temp;
          }

          c1_g_temp = c1_e_temp;
          if (c1_e_temp) {
            c1_h_temp = (_SFD_CCP_CALL(5U, 0U, 5, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 0U, 5, (real_T)*chartInstance->c1_state_CommECU, (real_T)
               chartInstance->c1_NORMAL, 0, 0U, *chartInstance->c1_state_CommECU
               == chartInstance->c1_NORMAL) != 0U, chartInstance->c1_sfEvent) !=
                         0U);
            if (c1_h_temp) {
              c1_h_temp = (_SFD_CCP_CALL(5U, 0U, 6, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 0U, 6, (real_T)
                                   *chartInstance->c1_ecu_EngineStarterMode,
                                   (real_T)chartInstance->c1_STARTER_INHIBITED,
                                   0, 1U,
                                   *chartInstance->c1_ecu_EngineStarterMode !=
                                   chartInstance->c1_STARTER_INHIBITED) != 0U,
                chartInstance->c1_sfEvent) != 0U);
            }

            c1_i_temp = c1_h_temp;
            if (c1_h_temp) {
              c1_i_temp = (_SFD_CCP_CALL(5U, 0U, 7, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 0U, 7, (real_T)
                                   *chartInstance->c1_state_Engine, (real_T)
                                   chartInstance->c1_ENGINE_NOT_RUNNING, 0, 0U, *
                                   chartInstance->c1_state_Engine ==
                                   chartInstance->c1_ENGINE_NOT_RUNNING) != 0U,
                chartInstance->c1_sfEvent) != 0U);
            }

            c1_j_temp = c1_i_temp;
            if (!c1_i_temp) {
              c1_j_temp = (_SFD_CCP_CALL(5U, 0U, 8, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 0U, 8, (real_T)
                                   chartInstance->c1_CD_ECU_FUNCTION, (real_T)
                                   chartInstance->c1_NON_FUNCTIONAL, 0, 0U,
                                   chartInstance->c1_CD_ECU_FUNCTION ==
                                   chartInstance->c1_NON_FUNCTIONAL) != 0U,
                chartInstance->c1_sfEvent) != 0U);
            }

            c1_g_temp = c1_j_temp;
          }

          c1_d_out = (CV_TRANSITION_EVAL(0U, (int32_T)c1_g_temp) != 0);
          if (c1_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
            c1_exit_internal_NOT_RUNNING(chartInstance);
            chartInstance->c1_tp_NOT_RUNNING = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
            chartInstance->c1_is_NORMAL = c1_IN_CRANKING;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
            chartInstance->c1_tp_CRANKING = 1U;
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c1_sfEvent);
            chartInstance->c1_is_CRANKING = c1_IN_FACTORY_TURBO_PRIMER;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
            chartInstance->c1_tp_FACTORY_TURBO_PRIMER = 1U;
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c1_sfEvent);
            chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_CHECK_HOUR_METER;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
            chartInstance->c1_tp_CHECK_HOUR_METER = 1U;
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                         chartInstance->c1_sfEvent);
            switch (chartInstance->c1_is_NOT_RUNNING) {
             case c1_b_IN_NOT_RUNNING:
              CV_STATE_EVAL(8, 0, c1_b_IN_NOT_RUNNING);
              *chartInstance->c1_state_Engine =
                chartInstance->c1_ENGINE_NOT_RUNNING;
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                           chartInstance->c1_sfEvent);
              _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U,
                           chartInstance->c1_sfEvent);
              break;

             case c1_IN_WAIT_TO_START:
              CV_STATE_EVAL(8, 0, c1_IN_WAIT_TO_START);
              *chartInstance->c1_state_Engine =
                chartInstance->c1_ENGINE_INITIALIZE;
              _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                           chartInstance->c1_sfEvent);
              c1_k_temp = (_SFD_CCP_CALL(5U, 11U, 0, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 11U, 0, (real_T)
                                   chartInstance->c1_debounceCount, (real_T)
                                   chartInstance->c1_CD_ECU_DEBOUNCE_WAIT_TO_START,
                                   0, 5U, chartInstance->c1_debounceCount >=
                                   chartInstance->c1_CD_ECU_DEBOUNCE_WAIT_TO_START)
                != 0U, chartInstance->c1_sfEvent) != 0U);
              if (c1_k_temp) {
                c1_k_temp = (_SFD_CCP_CALL(5U, 11U, 1, (boolean_T)
                  CV_RELATIONAL_EVAL(5U, 11U, 1, (real_T)
                                     *chartInstance->c1_state_CommECU, (real_T)
                                     chartInstance->c1_NORMAL, 0, 0U,
                                     *chartInstance->c1_state_CommECU ==
                                     chartInstance->c1_NORMAL) != 0U,
                  chartInstance->c1_sfEvent) != 0U);
              }

              c1_l_temp = c1_k_temp;
              if (!c1_k_temp) {
                c1_l_temp = (_SFD_CCP_CALL(5U, 11U, 2, (boolean_T)
                  CV_RELATIONAL_EVAL(5U, 11U, 2, (real_T)
                                     chartInstance->c1_CD_ECU_FUNCTION, (real_T)
                                     chartInstance->c1_NON_FUNCTIONAL, 0, 0U,
                                     chartInstance->c1_CD_ECU_FUNCTION ==
                                     chartInstance->c1_NON_FUNCTIONAL) != 0U,
                  chartInstance->c1_sfEvent) != 0U);
              }

              c1_e_out = (CV_TRANSITION_EVAL(11U, (int32_T)c1_l_temp) != 0);
              if (c1_e_out) {
                _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U,
                             chartInstance->c1_sfEvent);
                chartInstance->c1_tp_WAIT_TO_START = 0U;
                _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
                chartInstance->c1_is_NOT_RUNNING = c1_b_IN_NOT_RUNNING;
                _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
                chartInstance->c1_b_tp_NOT_RUNNING = 1U;
                *chartInstance->c1_state_Engine =
                  chartInstance->c1_ENGINE_NOT_RUNNING;
                _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine,
                                      26U);
                SendMsg_03_Now();
              } else {
                _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                             chartInstance->c1_sfEvent);
                chartInstance->c1_debounceCount = c1__u16_s32_(chartInstance,
                  c1__s32_add__(chartInstance, (int32_T)
                                chartInstance->c1_debounceCount, 1, 121U, 76U,
                                15U), 121U, 76U, 15U);
                _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_debounceCount,
                                      0U);
              }

              _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U,
                           chartInstance->c1_sfEvent);
              break;

             default:
              CV_STATE_EVAL(8, 0, 0);

              /* Unreachable state, for coverage only */
              chartInstance->c1_is_NOT_RUNNING = c1_IN_NO_ACTIVE_CHILD;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
              break;
            }
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c1_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
        break;

       case c1_IN_RUNNING:
        CV_STATE_EVAL(0, 0, c1_IN_RUNNING);
        c1_RUNNING(chartInstance);
        if (chartInstance->c1_is_c1_MX_Gtwy_Control != c1_IN_NORMAL) {
        } else {
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
        }
        break;

       default:
        CV_STATE_EVAL(0, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c1_is_NORMAL = c1_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
        break;
      }
    }
  }
}

static void c1_exit_internal_NORMAL(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c1_is_NORMAL) {
   case c1_IN_CRANKING:
    CV_STATE_EVAL(0, 1, c1_IN_CRANKING);
    c1_exit_internal_CRANKING(chartInstance);
    chartInstance->c1_tp_CRANKING = 0U;
    _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
    *chartInstance->c1_state_TurboPrime = chartInstance->c1_NORMAL;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_TurboPrime, 27U);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_NORMAL = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_NOT_RUNNING:
    CV_STATE_EVAL(0, 1, c1_IN_NOT_RUNNING);
    c1_exit_internal_NOT_RUNNING(chartInstance);
    chartInstance->c1_tp_NOT_RUNNING = 0U;
    chartInstance->c1_is_NORMAL = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_RUNNING:
    CV_STATE_EVAL(0, 1, c1_IN_RUNNING);
    chartInstance->c1_tp_RUNNING = 0U;
    chartInstance->c1_is_NORMAL = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
    break;

   default:
    CV_STATE_EVAL(0, 1, 0);
    chartInstance->c1_is_NORMAL = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
    break;
  }
}

static void c1_CRANKING(SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c1_temp;
  boolean_T c1_b_temp;
  boolean_T c1_c_temp;
  boolean_T c1_d_temp;
  boolean_T c1_e_temp;
  boolean_T c1_out;
  boolean_T c1_b_out;
  boolean_T c1_f_temp;
  boolean_T c1_c_out;
  boolean_T c1_d_out;
  boolean_T c1_g_temp;
  boolean_T c1_h_temp;
  boolean_T c1_e_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U, chartInstance->c1_sfEvent);
  c1_temp = (_SFD_CCP_CALL(5U, 5U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 5U, 0,
    (real_T)*chartInstance->c1_state_EngineStart, (real_T)
    chartInstance->c1_ACTIVE, 0, 1U, *chartInstance->c1_state_EngineStart !=
    chartInstance->c1_ACTIVE) != 0U, chartInstance->c1_sfEvent) != 0U);
  if (!c1_temp) {
    c1_temp = (_SFD_CCP_CALL(5U, 5U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 5U, 1,
      (real_T)*chartInstance->c1_state_Key, (real_T)chartInstance->c1_ACTIVE, 0,
      1U, *chartInstance->c1_state_Key != chartInstance->c1_ACTIVE) != 0U,
                chartInstance->c1_sfEvent) != 0U);
  }

  c1_b_temp = c1_temp;
  if (!c1_temp) {
    c1_b_temp = (_SFD_CCP_CALL(5U, 5U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U, 5U,
      2, (real_T)*chartInstance->c1_state_System, (real_T)
      chartInstance->c1_SYS_NORMAL, 0, 1U, *chartInstance->c1_state_System !=
      chartInstance->c1_SYS_NORMAL) != 0U, chartInstance->c1_sfEvent) != 0U);
  }

  c1_c_temp = c1_b_temp;
  if (!c1_b_temp) {
    c1_d_temp = (_SFD_CCP_CALL(5U, 5U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U, 5U,
      3, (real_T)chartInstance->c1_CD_EMEA_CONSOLE_CRANK_INHIBIT, (real_T)
      chartInstance->c1_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c1_CD_EMEA_CONSOLE_CRANK_INHIBIT !=
      chartInstance->c1_NON_FUNCTIONAL) != 0U, chartInstance->c1_sfEvent) != 0U);
    if (c1_d_temp) {
      c1_d_temp = (_SFD_CCP_CALL(5U, 5U, 4, (boolean_T)CV_RELATIONAL_EVAL(5U, 5U,
        4, (real_T)*chartInstance->c1_state_Console, (real_T)
        chartInstance->c1_INACTIVE, 0, 1U, *chartInstance->c1_state_Console !=
        chartInstance->c1_INACTIVE) != 0U, chartInstance->c1_sfEvent) != 0U);
    }

    c1_c_temp = c1_d_temp;
  }

  c1_e_temp = c1_c_temp;
  if (!c1_c_temp) {
    c1_e_temp = (_SFD_CCP_CALL(5U, 5U, 5, (boolean_T)CV_RELATIONAL_EVAL(5U, 5U,
      5, (real_T)*chartInstance->c1_ecu_EngineStarterMode, (real_T)
      chartInstance->c1_STARTER_INHIBITED, 0, 0U,
      *chartInstance->c1_ecu_EngineStarterMode ==
      chartInstance->c1_STARTER_INHIBITED) != 0U, chartInstance->c1_sfEvent) !=
                 0U);
  }

  c1_out = (CV_TRANSITION_EVAL(5U, (int32_T)c1_e_temp) != 0);
  if (c1_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
    c1_exit_internal_CRANKING(chartInstance);
    chartInstance->c1_tp_CRANKING = 0U;
    _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
    *chartInstance->c1_state_TurboPrime = chartInstance->c1_NORMAL;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_TurboPrime, 27U);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_NORMAL = c1_IN_NOT_RUNNING;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_NOT_RUNNING = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_NOT_RUNNING = c1_b_IN_NOT_RUNNING;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
    chartInstance->c1_b_tp_NOT_RUNNING = 1U;
    *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_NOT_RUNNING;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
    SendMsg_03_Now();
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U, chartInstance->c1_sfEvent);
    c1_b_out = (CV_TRANSITION_EVAL(1U, (int32_T)(_SFD_CCP_CALL(5U, 1U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 1U, 0, (real_T)
      *chartInstance->c1_flt_EngineSpeed, (real_T)
      chartInstance->c1_CD_ENGINE_SPEED_RUNNING, 0, 5U,
      *chartInstance->c1_flt_EngineSpeed >=
      chartInstance->c1_CD_ENGINE_SPEED_RUNNING) != 0U,
      chartInstance->c1_sfEvent) != 0U)) != 0);
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
      c1_exit_internal_CRANKING(chartInstance);
      chartInstance->c1_tp_CRANKING = 0U;
      _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
      *chartInstance->c1_state_TurboPrime = chartInstance->c1_NORMAL;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_TurboPrime, 27U);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_NORMAL = c1_IN_RUNNING;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_RUNNING = 1U;
      *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_RUNNING;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
      SendMsg_03_Now();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                   chartInstance->c1_sfEvent);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                   chartInstance->c1_sfEvent);
      switch (chartInstance->c1_is_FACTORY_TURBO_PRIMER) {
       case c1_IN_CHECK_HOUR_METER:
        CV_STATE_EVAL(2, 0, c1_IN_CHECK_HOUR_METER);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 22U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 21U,
                     chartInstance->c1_sfEvent);
        c1_f_temp = (_SFD_CCP_CALL(5U, 21U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          21U, 0, (real_T)chartInstance->c1_CD_FACTORY_TURBO_PRIME_FUNCTION,
          (real_T)chartInstance->c1_NON_FUNCTIONAL, 0, 1U,
          chartInstance->c1_CD_FACTORY_TURBO_PRIME_FUNCTION !=
          chartInstance->c1_NON_FUNCTIONAL) != 0U, chartInstance->c1_sfEvent) !=
                     0U);
        if (c1_f_temp) {
          c1_g_temp = (_SFD_CCP_CALL(5U, 21U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 21U, 1, (real_T)*chartInstance->c1_actualHourMeter, (real_T)
             chartInstance->c1_CD_FACTORY_TURBO_PRIME_HOUR_ENABLE, 0, 3U,
             *chartInstance->c1_actualHourMeter <=
             chartInstance->c1_CD_FACTORY_TURBO_PRIME_HOUR_ENABLE) != 0U,
            chartInstance->c1_sfEvent) != 0U);
          if (!c1_g_temp) {
            c1_g_temp = (_SFD_CCP_CALL(5U, 21U, 2, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 21U, 2, (real_T)*chartInstance->c1_dv_TurboPrime, (real_T)
               chartInstance->c1_TURBO_PRIME_ACTIVE, 0, 0U,
               *chartInstance->c1_dv_TurboPrime ==
               chartInstance->c1_TURBO_PRIME_ACTIVE) != 0U,
              chartInstance->c1_sfEvent) != 0U);
          }

          c1_f_temp = c1_g_temp;
        }

        c1_h_temp = c1_f_temp;
        if (c1_f_temp) {
          c1_h_temp = !(_SFD_CCP_CALL(5U, 21U, 3,
            chartInstance->c1_flag_PrimeComplete != 0U,
            chartInstance->c1_sfEvent) != 0U);
        }

        c1_e_out = (CV_TRANSITION_EVAL(21U, (int32_T)c1_h_temp) != 0);
        if (c1_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_CHECK_HOUR_METER = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_FACTORY_TURBO_PRIMER =
            c1_IN_PREVENT_FUEL_MSG_ACTIVE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_PREVENT_FUEL_MSG_ACTIVE = 1U;
          *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_CRANKING;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
          SendMsg_03_Now();
          chartInstance->c1_debouncePrimer = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_debouncePrimer, 1U);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 23U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_CHECK_HOUR_METER = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_HOUR_METER_EXCEEDED;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_HOUR_METER_EXCEEDED = 1U;
          *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_CRANKING;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
          SendMsg_03_Now();
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c1_sfEvent);
        break;

       case c1_IN_HOUR_METER_EXCEEDED:
        CV_STATE_EVAL(2, 0, c1_IN_HOUR_METER_EXCEEDED);
        *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_CRANKING;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                     chartInstance->c1_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c1_sfEvent);
        break;

       case c1_IN_PAUSE:
        CV_STATE_EVAL(2, 0, c1_IN_PAUSE);
        *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_NOT_RUNNING;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 25U,
                     chartInstance->c1_sfEvent);
        c1_c_out = (CV_TRANSITION_EVAL(25U, (int32_T)(_SFD_CCP_CALL(5U, 25U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 25U, 0, (real_T)
          chartInstance->c1_debouncePrimer, (real_T)
          chartInstance->c1_CD_FACTORY_TURBO_PRIME_DEBOUNCE_WAIT, 0, 5U,
          chartInstance->c1_debouncePrimer >=
          chartInstance->c1_CD_FACTORY_TURBO_PRIME_DEBOUNCE_WAIT) != 0U,
          chartInstance->c1_sfEvent) != 0U)) != 0);
        if (c1_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 25U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_PAUSE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_FACTORY_TURBO_PRIMER =
            c1_IN_PREVENT_FUEL_MSG_INACTIVE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_PREVENT_FUEL_MSG_INACTIVE = 1U;
          *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_CRANKING;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
          SendMsg_03_Now();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                       chartInstance->c1_sfEvent);
          chartInstance->c1_debouncePrimer = c1__u16_s32_(chartInstance,
            c1__s32_add__(chartInstance, (int32_T)
                          chartInstance->c1_debouncePrimer, 1, 213U, 138U, 16U),
            213U, 138U, 16U);
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_debouncePrimer, 1U);
          SendMsg_DPM2_Now();
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c1_sfEvent);
        break;

       case c1_IN_PREVENT_FUEL_MSG_ACTIVE:
        CV_STATE_EVAL(2, 0, c1_IN_PREVENT_FUEL_MSG_ACTIVE);
        *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_CRANKING;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 24U,
                     chartInstance->c1_sfEvent);
        c1_d_out = (CV_TRANSITION_EVAL(24U, (int32_T)(_SFD_CCP_CALL(5U, 24U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 24U, 0, (real_T)
          chartInstance->c1_debouncePrimer, (real_T)
          chartInstance->c1_CD_FACTORY_TURBO_PRIME_DEBOUNCE_DISABLE_FUEL, 0, 5U,
          chartInstance->c1_debouncePrimer >=
          chartInstance->c1_CD_FACTORY_TURBO_PRIME_DEBOUNCE_DISABLE_FUEL) != 0U,
          chartInstance->c1_sfEvent) != 0U)) != 0);
        if (c1_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_PREVENT_FUEL_MSG_ACTIVE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_PAUSE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_PAUSE = 1U;
          *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_NOT_RUNNING;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
          SendMsg_03_Now();
          chartInstance->c1_debouncePrimer = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_debouncePrimer, 1U);
          chartInstance->c1_flag_PrimeComplete = true;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_flag_PrimeComplete, 2U);
          *chartInstance->c1_state_TurboPrime = chartInstance->c1_NORMAL;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_TurboPrime, 27U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                       chartInstance->c1_sfEvent);
          SendMsg_DPM2_Now();
          chartInstance->c1_debouncePrimer = c1__u16_s32_(chartInstance,
            c1__s32_add__(chartInstance, (int32_T)
                          chartInstance->c1_debouncePrimer, 1, 209U, 122U, 16U),
            209U, 122U, 16U);
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_debouncePrimer, 1U);
          *chartInstance->c1_state_TurboPrime = chartInstance->c1_ACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_TurboPrime, 27U);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c1_sfEvent);
        break;

       case c1_IN_PREVENT_FUEL_MSG_INACTIVE:
        CV_STATE_EVAL(2, 0, c1_IN_PREVENT_FUEL_MSG_INACTIVE);
        *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_CRANKING;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                     chartInstance->c1_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c1_sfEvent);
        break;

       default:
        CV_STATE_EVAL(2, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
        break;
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c1_sfEvent);
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
}

static void c1_exit_internal_CRANKING(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c1_is_FACTORY_TURBO_PRIMER) {
   case c1_IN_CHECK_HOUR_METER:
    CV_STATE_EVAL(2, 1, c1_IN_CHECK_HOUR_METER);
    chartInstance->c1_tp_CHECK_HOUR_METER = 0U;
    chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_HOUR_METER_EXCEEDED:
    CV_STATE_EVAL(2, 1, c1_IN_HOUR_METER_EXCEEDED);
    chartInstance->c1_tp_HOUR_METER_EXCEEDED = 0U;
    chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_PAUSE:
    CV_STATE_EVAL(2, 1, c1_IN_PAUSE);
    chartInstance->c1_tp_PAUSE = 0U;
    chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_PREVENT_FUEL_MSG_ACTIVE:
    CV_STATE_EVAL(2, 1, c1_IN_PREVENT_FUEL_MSG_ACTIVE);
    chartInstance->c1_tp_PREVENT_FUEL_MSG_ACTIVE = 0U;
    chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_PREVENT_FUEL_MSG_INACTIVE:
    CV_STATE_EVAL(2, 1, c1_IN_PREVENT_FUEL_MSG_INACTIVE);
    chartInstance->c1_tp_PREVENT_FUEL_MSG_INACTIVE = 0U;
    chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
    break;

   default:
    CV_STATE_EVAL(2, 1, 0);
    chartInstance->c1_is_FACTORY_TURBO_PRIMER = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
    break;
  }

  chartInstance->c1_tp_FACTORY_TURBO_PRIMER = 0U;
  chartInstance->c1_is_CRANKING = c1_IN_NO_ACTIVE_CHILD;
  _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
}

static void c1_exit_internal_NOT_RUNNING(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c1_is_NOT_RUNNING) {
   case c1_b_IN_NOT_RUNNING:
    CV_STATE_EVAL(8, 1, c1_b_IN_NOT_RUNNING);
    chartInstance->c1_b_tp_NOT_RUNNING = 0U;
    chartInstance->c1_is_NOT_RUNNING = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_WAIT_TO_START:
    CV_STATE_EVAL(8, 1, c1_IN_WAIT_TO_START);
    chartInstance->c1_tp_WAIT_TO_START = 0U;
    chartInstance->c1_is_NOT_RUNNING = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
    break;

   default:
    CV_STATE_EVAL(8, 1, 0);
    chartInstance->c1_is_NOT_RUNNING = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
    break;
  }
}

static void c1_RUNNING(SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c1_temp;
  boolean_T c1_b_temp;
  boolean_T c1_c_temp;
  boolean_T c1_d_temp;
  boolean_T c1_e_temp;
  boolean_T c1_f_temp;
  boolean_T c1_g_temp;
  boolean_T c1_h_temp;
  boolean_T c1_i_temp;
  boolean_T c1_out;
  boolean_T c1_j_temp;
  boolean_T c1_b_out;
  boolean_T c1_k_temp;
  boolean_T c1_l_temp;
  boolean_T c1_m_temp;
  boolean_T c1_c_out;
  boolean_T c1_n_temp;
  *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_RUNNING;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U, chartInstance->c1_sfEvent);
  c1_temp = (_SFD_CCP_CALL(5U, 2U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U, 0,
    (real_T)*chartInstance->c1_state_ECT, (real_T)chartInstance->c1_SHUTDOWN, 0,
    0U, *chartInstance->c1_state_ECT == chartInstance->c1_SHUTDOWN) != 0U,
              chartInstance->c1_sfEvent) != 0U);
  if (!c1_temp) {
    c1_temp = (_SFD_CCP_CALL(5U, 2U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U, 1,
      (real_T)*chartInstance->c1_state_EOP, (real_T)chartInstance->c1_SHUTDOWN,
      0, 0U, *chartInstance->c1_state_EOP == chartInstance->c1_SHUTDOWN) != 0U,
                chartInstance->c1_sfEvent) != 0U);
  }

  c1_b_temp = c1_temp;
  if (!c1_temp) {
    c1_b_temp = (_SFD_CCP_CALL(5U, 2U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U,
      2, (real_T)*chartInstance->c1_state_HOT, (real_T)
      chartInstance->c1_SHUTDOWN, 0, 0U, *chartInstance->c1_state_HOT ==
      chartInstance->c1_SHUTDOWN) != 0U, chartInstance->c1_sfEvent) != 0U);
  }

  c1_c_temp = c1_b_temp;
  if (!c1_b_temp) {
    c1_c_temp = (_SFD_CCP_CALL(5U, 2U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U,
      3, (real_T)*chartInstance->c1_state_EngineSpeed, (real_T)
      chartInstance->c1_SHUTDOWN, 0, 0U, *chartInstance->c1_state_EngineSpeed ==
      chartInstance->c1_SHUTDOWN) != 0U, chartInstance->c1_sfEvent) != 0U);
  }

  c1_d_temp = c1_c_temp;
  if (!c1_c_temp) {
    c1_d_temp = (_SFD_CCP_CALL(5U, 2U, 4, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U,
      4, (real_T)*chartInstance->c1_state_FuelTemp, (real_T)
      chartInstance->c1_SHUTDOWN, 0, 0U, *chartInstance->c1_state_FuelTemp ==
      chartInstance->c1_SHUTDOWN) != 0U, chartInstance->c1_sfEvent) != 0U);
  }

  c1_e_temp = c1_d_temp;
  if (!c1_d_temp) {
    c1_e_temp = (_SFD_CCP_CALL(5U, 2U, 5, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U,
      5, (real_T)*chartInstance->c1_state_KeylessPanel, (real_T)
      chartInstance->c1_NO_COMMUNICATION, 0, 0U,
      *chartInstance->c1_state_KeylessPanel ==
      chartInstance->c1_NO_COMMUNICATION) != 0U, chartInstance->c1_sfEvent) !=
                 0U);
  }

  c1_f_temp = c1_e_temp;
  if (!c1_e_temp) {
    c1_g_temp = (_SFD_CCP_CALL(5U, 2U, 6, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U,
      6, (real_T)*chartInstance->c1_state_CommECU, (real_T)
      chartInstance->c1_NO_COMMUNICATION, 0, 0U,
      *chartInstance->c1_state_CommECU == chartInstance->c1_NO_COMMUNICATION) !=
      0U, chartInstance->c1_sfEvent) != 0U);
    if (!c1_g_temp) {
      c1_g_temp = (_SFD_CCP_CALL(5U, 2U, 7, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U,
        7, (real_T)*chartInstance->c1_state_EngineSpeedDerate, (real_T)
        chartInstance->c1_SHUTDOWN, 0, 0U,
        *chartInstance->c1_state_EngineSpeedDerate == chartInstance->c1_SHUTDOWN)
        != 0U, chartInstance->c1_sfEvent) != 0U);
    }

    c1_i_temp = c1_g_temp;
    if (c1_g_temp) {
      c1_i_temp = (_SFD_CCP_CALL(5U, 2U, 8, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U,
        8, (real_T)chartInstance->c1_CD_ECU_FUNCTION, (real_T)
        chartInstance->c1_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c1_CD_ECU_FUNCTION != chartInstance->c1_NON_FUNCTIONAL)
        != 0U, chartInstance->c1_sfEvent) != 0U);
    }

    c1_f_temp = c1_i_temp;
  }

  c1_h_temp = c1_f_temp;
  if (!c1_f_temp) {
    c1_h_temp = (_SFD_CCP_CALL(5U, 2U, 9, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U,
      9, (real_T)chartInstance->c1_panelMissingDebounce, (real_T)
      chartInstance->c1_CD_PANEL_SHUTDOWN_DEBOUNCE, 0, 4U,
      chartInstance->c1_panelMissingDebounce >
      chartInstance->c1_CD_PANEL_SHUTDOWN_DEBOUNCE) != 0U,
      chartInstance->c1_sfEvent) != 0U);
  }

  c1_out = (CV_TRANSITION_EVAL(2U, (int32_T)c1_h_temp) != 0);
  if (c1_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_RUNNING = 0U;
    chartInstance->c1_is_NORMAL = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_NORMAL = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_c1_MX_Gtwy_Control = c1_IN_SHUTDOWN;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_SHUTDOWN = 1U;
    *chartInstance->c1_state_Engine = chartInstance->c1_SHUTDOWN;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
    SendMsg_03_Now();
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U, chartInstance->c1_sfEvent);
    c1_j_temp = (_SFD_CCP_CALL(5U, 4U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 4U,
      0, (real_T)*chartInstance->c1_flt_EngineSpeed, (real_T)
      chartInstance->c1_CD_ENGINE_SPEED_NOT_RUNNING, 0, 3U,
      *chartInstance->c1_flt_EngineSpeed <=
      chartInstance->c1_CD_ENGINE_SPEED_NOT_RUNNING) != 0U,
      chartInstance->c1_sfEvent) != 0U);
    if (!c1_j_temp) {
      c1_j_temp = (_SFD_CCP_CALL(5U, 4U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 4U,
        1, (real_T)*chartInstance->c1_state_System, (real_T)
        chartInstance->c1_SYS_NORMAL, 0, 1U, *chartInstance->c1_state_System !=
        chartInstance->c1_SYS_NORMAL) != 0U, chartInstance->c1_sfEvent) != 0U);
    }

    c1_b_out = (CV_TRANSITION_EVAL(4U, (int32_T)c1_j_temp) != 0);
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_RUNNING = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_NORMAL = c1_IN_NOT_RUNNING;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_NOT_RUNNING = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_NOT_RUNNING = c1_b_IN_NOT_RUNNING;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
      chartInstance->c1_b_tp_NOT_RUNNING = 1U;
      *chartInstance->c1_state_Engine = chartInstance->c1_ENGINE_NOT_RUNNING;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c1_state_Engine, 26U);
      SendMsg_03_Now();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                   chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                   chartInstance->c1_sfEvent);
      c1_k_temp = (_SFD_CCP_CALL(5U, 15U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        15U, 0, (real_T)chartInstance->c1_CD_PANEL_SHUTDOWN_FUNCTION, (real_T)
        chartInstance->c1_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c1_CD_PANEL_SHUTDOWN_FUNCTION !=
        chartInstance->c1_NON_FUNCTIONAL) != 0U, chartInstance->c1_sfEvent) !=
                   0U);
      if (c1_k_temp) {
        c1_k_temp = (_SFD_CCP_CALL(5U, 15U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          15U, 1, (real_T)*chartInstance->c1_din_RemoteKey, (real_T)
          chartInstance->c1_ACTIVE, 0, 1U, *chartInstance->c1_din_RemoteKey !=
          chartInstance->c1_ACTIVE) != 0U, chartInstance->c1_sfEvent) != 0U);
      }

      c1_l_temp = c1_k_temp;
      if (c1_k_temp) {
        c1_m_temp = (_SFD_CCP_CALL(5U, 15U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
          15U, 2, (real_T)*chartInstance->c1_state_CommStdPanel, (real_T)
          chartInstance->c1_NO_COMMUNICATION, 0, 0U,
          *chartInstance->c1_state_CommStdPanel ==
          chartInstance->c1_NO_COMMUNICATION) != 0U, chartInstance->c1_sfEvent)
                     != 0U);
        if (!c1_m_temp) {
          c1_m_temp = (_SFD_CCP_CALL(5U, 15U, 3, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 15U, 3, (real_T)*chartInstance->c1_state_DeluxeG5, (real_T)
             chartInstance->c1_NO_COMMUNICATION, 0, 0U,
             *chartInstance->c1_state_DeluxeG5 ==
             chartInstance->c1_NO_COMMUNICATION) != 0U,
            chartInstance->c1_sfEvent) != 0U);
        }

        c1_n_temp = c1_m_temp;
        if (!c1_m_temp) {
          c1_n_temp = (_SFD_CCP_CALL(5U, 15U, 4, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 15U, 4, (real_T)*chartInstance->c1_state_CommDeluxeG55, (real_T)
             chartInstance->c1_NO_COMMUNICATION, 0, 0U,
             *chartInstance->c1_state_CommDeluxeG55 ==
             chartInstance->c1_NO_COMMUNICATION) != 0U,
            chartInstance->c1_sfEvent) != 0U);
        }

        c1_l_temp = c1_n_temp;
      }

      c1_c_out = (CV_TRANSITION_EVAL(15U, (int32_T)c1_l_temp) != 0);
      if (c1_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c1_sfEvent);
        chartInstance->c1_panelMissingDebounce = c1__u16_s32_(chartInstance,
          c1__s32_add__(chartInstance, (int32_T)
                        chartInstance->c1_panelMissingDebounce, 1, 181U, 2U, 22U),
          181U, 2U, 22U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_panelMissingDebounce, 3U);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c1_sfEvent);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c1_sfEvent);
        chartInstance->c1_panelMissingDebounce = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_panelMissingDebounce, 3U);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c1_sfEvent);
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c1_sfEvent);
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber)
{
  (void)(c1_machineNumber);
  (void)(c1_chartNumber);
  (void)(c1_instanceNumber);
}

const mxArray *sf_c1_MX_Gtwy_Control_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c1_nameCaptureInfo;
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i0, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent), &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  uint8_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(uint8_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static uint8_T c1_b_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_b_tp_NORMAL, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_tp_NORMAL),
    &c1_thisId);
  sf_mex_destroy(&c1_b_tp_NORMAL);
  return c1_y;
}

static uint8_T c1_c_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_tp_NORMAL;
  emlrtMsgIdentifier c1_thisId;
  uint8_T c1_y;
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c1_b_tp_NORMAL = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_tp_NORMAL),
    &c1_thisId);
  sf_mex_destroy(&c1_b_tp_NORMAL);
  *(uint8_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  uint16_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(uint16_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static uint16_T c1_d_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_b_CD_ENGINE_SPEED_RUNNING, const char_T
  *c1_identifier)
{
  uint16_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_CD_ENGINE_SPEED_RUNNING), &c1_thisId);
  sf_mex_destroy(&c1_b_CD_ENGINE_SPEED_RUNNING);
  return c1_y;
}

static uint16_T c1_e_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint16_T c1_y;
  uint16_T c1_u1;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u1, 1, 5, 0U, 0, 0U, 0);
  c1_y = c1_u1;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_CD_ENGINE_SPEED_RUNNING;
  emlrtMsgIdentifier c1_thisId;
  uint16_T c1_y;
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c1_b_CD_ENGINE_SPEED_RUNNING = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_CD_ENGINE_SPEED_RUNNING), &c1_thisId);
  sf_mex_destroy(&c1_b_CD_ENGINE_SPEED_RUNNING);
  *(uint16_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  uint32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(uint32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 7, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static uint32_T c1_f_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint32_T c1_y;
  uint32_T c1_u2;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u2, 1, 7, 0U, 0, 0U, 0);
  c1_y = c1_u2;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_CD_FACTORY_TURBO_PRIME_HOUR_ENABLE;
  emlrtMsgIdentifier c1_thisId;
  uint32_T c1_y;
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c1_b_CD_FACTORY_TURBO_PRIME_HOUR_ENABLE = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_CD_FACTORY_TURBO_PRIME_HOUR_ENABLE), &c1_thisId);
  sf_mex_destroy(&c1_b_CD_FACTORY_TURBO_PRIME_HOUR_ENABLE);
  *(uint32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  boolean_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_u = *(boolean_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static boolean_T c1_g_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_b_flag_PrimeComplete, const char_T
  *c1_identifier)
{
  boolean_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_flag_PrimeComplete),
    &c1_thisId);
  sf_mex_destroy(&c1_b_flag_PrimeComplete);
  return c1_y;
}

static boolean_T c1_h_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  boolean_T c1_y;
  boolean_T c1_b0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_b0, 1, 11, 0U, 0, 0U, 0);
  c1_y = c1_b0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_flag_PrimeComplete;
  emlrtMsgIdentifier c1_thisId;
  boolean_T c1_y;
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c1_b_flag_PrimeComplete = sf_mex_dup(c1_mxArrayInData);
  c1_thisId.fIdentifier = (const char *)c1_varName;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  c1_y = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_flag_PrimeComplete),
    &c1_thisId);
  sf_mex_destroy(&c1_b_flag_PrimeComplete);
  *(boolean_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_i_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_b_setSimStateSideEffectsInfo, const char_T
  *c1_identifier)
{
  const mxArray *c1_y = NULL;
  emlrtMsgIdentifier c1_thisId;
  c1_y = NULL;
  c1_thisId.fIdentifier = (const char *)c1_identifier;
  c1_thisId.fParent = NULL;
  c1_thisId.bParentIsCell = false;
  sf_mex_assign(&c1_y, c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_setSimStateSideEffectsInfo), &c1_thisId), false);
  sf_mex_destroy(&c1_b_setSimStateSideEffectsInfo);
  return c1_y;
}

static const mxArray *c1_j_emlrt_marshallIn(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  const mxArray *c1_y = NULL;
  (void)chartInstance;
  (void)c1_parentId;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_duplicatearraysafe(&c1_u), false);
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static const mxArray *sf_get_hover_data_for_msg
  (SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c1_ssid)
{
  (void)chartInstance;
  (void)c1_ssid;
  return NULL;
}

static void c1_init_sf_message_store_memory(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static uint16_T c1__u16_s32_(SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c1_b, uint32_T c1_ssid_src_loc, int32_T c1_offset_src_loc, int32_T
  c1_length_src_loc)
{
  uint16_T c1_a;
  (void)chartInstance;
  c1_a = (uint16_T)c1_b;
  if (c1_a != c1_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c1_ssid_src_loc, c1_offset_src_loc,
      c1_length_src_loc);
  }

  return c1_a;
}

static int32_T c1__s32_add__(SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c1_b, int32_T c1_c, uint32_T c1_ssid_src_loc, int32_T
  c1_offset_src_loc, int32_T c1_length_src_loc)
{
  int32_T c1_a;
  (void)chartInstance;
  c1_a = c1_b + c1_c;
  if (((c1_a ^ c1_b) & (c1_a ^ c1_c)) < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c1_ssid_src_loc, c1_offset_src_loc,
      c1_length_src_loc);
  }

  return c1_a;
}

static void init_dsm_address_info(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  chartInstance->c1_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c1_state_Engine = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_flt_EngineSpeed = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c1_state_EngineSpeed = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_state_ECT = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_state_EOP = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_state_HOT = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_state_EngineStart = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c1_state_Key = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c1_state_System = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c1_din_RemoteKey = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c1_state_KeylessPanel = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c1_state_CommECU = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c1_can_ST_EStop = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 11);
  chartInstance->c1_can_ACD_EStop = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 12);
  chartInstance->c1_ecu_EngineStarterMode = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 13);
  chartInstance->c1_state_EngineSpeedDerate = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 14);
  chartInstance->c1_state_FuelTemp = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 15);
  chartInstance->c1_state_CommStdPanel = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 16);
  chartInstance->c1_state_DeluxeG5 = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 17);
  chartInstance->c1_state_CommDeluxeG55 = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 18);
  chartInstance->c1_state_Console = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 19);
  chartInstance->c1_actualHourMeter = (uint32_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 20);
  chartInstance->c1_dv_TurboPrime = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 21);
  chartInstance->c1_state_TurboPrime = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
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

void sf_c1_MX_Gtwy_Control_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4153949901U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1960637409U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3977340730U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1119103943U);
}

mxArray* sf_c1_MX_Gtwy_Control_get_post_codegen_info(void);
mxArray *sf_c1_MX_Gtwy_Control_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("N1Z0uUH1oEDfzi7AE0Ll0G");
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(7));
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

    mxArray *mxData = mxCreateStructMatrix(1,26,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(7));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c1_MX_Gtwy_Control_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_MX_Gtwy_Control_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_MX_Gtwy_Control_jit_fallback_info(void)
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

mxArray *sf_c1_MX_Gtwy_Control_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_MX_Gtwy_Control_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c1_MX_Gtwy_Control(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[22],T\"state_Engine\",},{M[1],M[224],T\"state_TurboPrime\",},{M[3],M[127],T\"debounceCount\",},{M[3],M[220],T\"debouncePrimer\",},{M[3],M[223],T\"flag_PrimeComplete\",},{M[3],M[187],T\"panelMissingDebounce\",},{M[8],M[0],T\"is_active_c1_MX_Gtwy_Control\",},{M[9],M[0],T\"is_c1_MX_Gtwy_Control\",},{M[9],M[1],T\"is_NOT_RUNNING\",},{M[9],M[80],T\"is_NORMAL\",}}",
    "100 S1x2'type','srcId','name','auxInfo'{{M[9],M[198],T\"is_CRANKING\",},{M[9],M[200],T\"is_FACTORY_TURBO_PRIMER\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 12, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_MX_Gtwy_Control_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc1_MX_Gtwy_ControlInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc1_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MX_Gtwy_ControlMachineNumber_,
           1,
           14,
           26,
           0,
           54,
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
          _SFD_SET_DATA_PROPS(0,0,0,0,"debounceCount");
          _SFD_SET_DATA_PROPS(1,0,0,0,"debouncePrimer");
          _SFD_SET_DATA_PROPS(2,0,0,0,"flag_PrimeComplete");
          _SFD_SET_DATA_PROPS(3,0,0,0,"panelMissingDebounce");
          _SFD_SET_DATA_PROPS(4,1,1,0,"flt_EngineSpeed");
          _SFD_SET_DATA_PROPS(5,1,1,0,"state_EngineSpeed");
          _SFD_SET_DATA_PROPS(6,1,1,0,"state_ECT");
          _SFD_SET_DATA_PROPS(7,1,1,0,"state_EOP");
          _SFD_SET_DATA_PROPS(8,1,1,0,"state_HOT");
          _SFD_SET_DATA_PROPS(9,1,1,0,"state_EngineStart");
          _SFD_SET_DATA_PROPS(10,1,1,0,"state_Key");
          _SFD_SET_DATA_PROPS(11,1,1,0,"state_System");
          _SFD_SET_DATA_PROPS(12,1,1,0,"din_RemoteKey");
          _SFD_SET_DATA_PROPS(13,1,1,0,"state_KeylessPanel");
          _SFD_SET_DATA_PROPS(14,1,1,0,"state_CommECU");
          _SFD_SET_DATA_PROPS(15,1,1,0,"can_ST_EStop");
          _SFD_SET_DATA_PROPS(16,1,1,0,"can_ACD_EStop");
          _SFD_SET_DATA_PROPS(17,1,1,0,"ecu_EngineStarterMode");
          _SFD_SET_DATA_PROPS(18,1,1,0,"state_EngineSpeedDerate");
          _SFD_SET_DATA_PROPS(19,1,1,0,"state_FuelTemp");
          _SFD_SET_DATA_PROPS(20,1,1,0,"state_CommStdPanel");
          _SFD_SET_DATA_PROPS(21,1,1,0,"state_DeluxeG5");
          _SFD_SET_DATA_PROPS(22,1,1,0,"state_CommDeluxeG55");
          _SFD_SET_DATA_PROPS(23,1,1,0,"state_Console");
          _SFD_SET_DATA_PROPS(24,1,1,0,"actualHourMeter");
          _SFD_SET_DATA_PROPS(25,1,1,0,"dv_TurboPrime");
          _SFD_SET_DATA_PROPS(26,2,0,1,"state_Engine");
          _SFD_SET_DATA_PROPS(27,2,0,1,"state_TurboPrime");
          _SFD_SET_DATA_PROPS(28,10,0,0,"ACTIVE");
          _SFD_SET_DATA_PROPS(29,10,0,0,"CD_ECU_DEBOUNCE_WAIT_TO_START");
          _SFD_SET_DATA_PROPS(30,10,0,0,"CD_ECU_FUNCTION");
          _SFD_SET_DATA_PROPS(31,10,0,0,"CD_EMEA_CONSOLE_CRANK_INHIBIT");
          _SFD_SET_DATA_PROPS(32,10,0,0,"CD_ENGINE_SPEED_NOT_RUNNING");
          _SFD_SET_DATA_PROPS(33,10,0,0,"CD_ENGINE_SPEED_RUNNING");
          _SFD_SET_DATA_PROPS(34,10,0,0,
                              "CD_FACTORY_TURBO_PRIME_DEBOUNCE_DISABLE_FUEL");
          _SFD_SET_DATA_PROPS(35,10,0,0,"CD_FACTORY_TURBO_PRIME_DEBOUNCE_WAIT");
          _SFD_SET_DATA_PROPS(36,10,0,0,"CD_FACTORY_TURBO_PRIME_FUNCTION");
          _SFD_SET_DATA_PROPS(37,10,0,0,"CD_FACTORY_TURBO_PRIME_HOUR_ENABLE");
          _SFD_SET_DATA_PROPS(38,10,0,0,"CD_PANEL_SHUTDOWN_DEBOUNCE");
          _SFD_SET_DATA_PROPS(39,10,0,0,"CD_PANEL_SHUTDOWN_FUNCTION");
          _SFD_SET_DATA_PROPS(40,10,0,0,"ENGINE_CRANKING");
          _SFD_SET_DATA_PROPS(41,10,0,0,"ENGINE_INITIALIZE");
          _SFD_SET_DATA_PROPS(42,10,0,0,"ENGINE_NOT_RUNNING");
          _SFD_SET_DATA_PROPS(43,10,0,0,"ENGINE_OFF");
          _SFD_SET_DATA_PROPS(44,10,0,0,"ENGINE_RUNNING");
          _SFD_SET_DATA_PROPS(45,10,0,0,"INACTIVE");
          _SFD_SET_DATA_PROPS(46,10,0,0,"MULTIPLE");
          _SFD_SET_DATA_PROPS(47,10,0,0,"NON_FUNCTIONAL");
          _SFD_SET_DATA_PROPS(48,10,0,0,"NORMAL");
          _SFD_SET_DATA_PROPS(49,10,0,0,"NO_COMMUNICATION");
          _SFD_SET_DATA_PROPS(50,10,0,0,"SHUTDOWN");
          _SFD_SET_DATA_PROPS(51,10,0,0,"STARTER_INHIBITED");
          _SFD_SET_DATA_PROPS(52,10,0,0,"SYS_NORMAL");
          _SFD_SET_DATA_PROPS(53,10,0,0,"TURBO_PRIME_ACTIVE");
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
          _SFD_CH_SUBSTATE_COUNT(3);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,12);
          _SFD_CH_SUBSTATE_INDEX(2,13);
          _SFD_ST_SUBSTATE_COUNT(0,3);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,8);
          _SFD_ST_SUBSTATE_INDEX(0,2,11);
          _SFD_ST_SUBSTATE_COUNT(1,1);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_COUNT(2,5);
          _SFD_ST_SUBSTATE_INDEX(2,0,3);
          _SFD_ST_SUBSTATE_INDEX(2,1,4);
          _SFD_ST_SUBSTATE_INDEX(2,2,5);
          _SFD_ST_SUBSTATE_INDEX(2,3,6);
          _SFD_ST_SUBSTATE_INDEX(2,4,7);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,2);
          _SFD_ST_SUBSTATE_INDEX(8,0,9);
          _SFD_ST_SUBSTATE_INDEX(8,1,10);
          _SFD_ST_SUBSTATE_COUNT(9,0);
          _SFD_ST_SUBSTATE_COUNT(10,0);
          _SFD_ST_SUBSTATE_COUNT(11,0);
          _SFD_ST_SUBSTATE_COUNT(12,0);
          _SFD_ST_SUBSTATE_COUNT(13,0);
        }

        _SFD_CV_INIT_CHART(3,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,1,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,5,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(10,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(11,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(12,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(13,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 35 };

          static unsigned int sEndGuardMap[] = { 26, 60 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(8,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 35 };

          static unsigned int sEndRelationalopMap[] = { 26, 60 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(8,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 33 };

          static unsigned int sEndGuardMap[] = { 24, 56 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(7,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 33 };

          static unsigned int sEndRelationalopMap[] = { 24, 56 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(7,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 32, 62, 92, 130, 165, 214,
            253, 295, 338 };

          static unsigned int sEndGuardMap[] = { 23, 53, 83, 121, 156, 203, 247,
            288, 328, 387 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2, 6, 7, -2, 8, -3, -2, 9, -2 };

          _SFD_CV_INIT_TRANS(2,10,&(sStartGuardMap[0]),&(sEndGuardMap[0]),19,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 32, 62, 92, 130,
            165, 214, 253, 295, 338 };

          static unsigned int sEndRelationalopMap[] = { 23, 53, 83, 121, 156,
            203, 247, 288, 328, 387 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 0, 0,
            0, 0, 0, 0, 0, 0, 1, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,10,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 23 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(6,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 23 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(6,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 3, 40, 68, 104, 157, 194, 223,
            271, 323 };

          static unsigned int sEndGuardMap[] = { 30, 59, 94, 151, 182, 217, 265,
            305, 356 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, 4, -2, -3,
            5, 6, -3, 7, -3, 8, -2, -3 };

          _SFD_CV_INIT_TRANS(0,9,&(sStartGuardMap[0]),&(sEndGuardMap[0]),17,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 3, 40, 68, 104, 157,
            194, 223, 271, 323 };

          static unsigned int sEndRelationalopMap[] = { 30, 59, 94, 151, 182,
            217, 265, 305, 356 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(0,9,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 3, 40, 68, 104, 157, 192 };

          static unsigned int sEndGuardMap[] = { 30, 59, 94, 151, 182, 234 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, 4, -3, -2,
            5, -2 };

          _SFD_CV_INIT_TRANS(5,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 3, 40, 68, 104, 157,
            192 };

          static unsigned int sEndRelationalopMap[] = { 30, 59, 94, 151, 182,
            234 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 53 };

          static unsigned int sEndGuardMap[] = { 44, 79 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(3,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 53 };

          static unsigned int sEndRelationalopMap[] = { 44, 79 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 5, 0, 5, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(3,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 3, 58 };

          static unsigned int sEndGuardMap[] = { 49, 84 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(4,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 3, 58 };

          static unsigned int sEndRelationalopMap[] = { 49, 84 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 3, 1, 3, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(4,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 44 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 44 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(19,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(20,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 59, 118, 163 };

          static unsigned int sEndGuardMap[] = { 50, 112, 153, 181 };

          static int sPostFixPredicateTree[] = { 0, 1, 2, -2, -3, 3, -1, -3 };

          _SFD_CV_INIT_TRANS(21,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),8,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 59, 118 };

          static unsigned int sEndRelationalopMap[] = { 50, 112, 153 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 3, 0, 1, 3, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(21,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(22,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(23,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 64 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(24,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 64 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(24,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 56 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(25,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 56 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(25,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(10,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 3, 55, 88 };

          static unsigned int sEndGuardMap[] = { 49, 78, 121 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -2 };

          _SFD_CV_INIT_TRANS(11,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 3, 55, 88 };

          static unsigned int sEndRelationalopMap[] = { 49, 78, 121 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 5, 0, 0, 5, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(11,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(13,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 52, 85, 129, 169 };

          static unsigned int sEndGuardMap[] = { 46, 75, 123, 163, 208 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, 3, -2, 4, -2, -3 };

          _SFD_CV_INIT_TRANS(15,5,&(sStartGuardMap[0]),&(sEndGuardMap[0]),9,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 52, 85, 129, 169 };

          static unsigned int sEndRelationalopMap[] = { 46, 75, 123, 163, 208 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(15,5,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(14,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(18,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)c1_e_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_UINT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(27,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(28,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(29,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(30,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(31,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(32,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(33,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(34,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(35,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(36,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(37,SF_UINT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(38,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(39,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(40,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(41,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(42,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(43,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(44,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(45,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(46,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(47,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(48,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(49,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(50,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(51,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(52,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(53,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)c1_b_sf_marshallIn);
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
    SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc1_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(26U, (void *)chartInstance->c1_state_Engine);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c1_flt_EngineSpeed);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c1_state_EngineSpeed);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c1_state_ECT);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c1_state_EOP);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c1_state_HOT);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)chartInstance->c1_state_EngineStart);
        _SFD_SET_DATA_VALUE_PTR(33U, (void *)
          &chartInstance->c1_CD_ENGINE_SPEED_RUNNING);
        _SFD_SET_DATA_VALUE_PTR(32U, (void *)
          &chartInstance->c1_CD_ENGINE_SPEED_NOT_RUNNING);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)chartInstance->c1_state_Key);
        _SFD_SET_DATA_VALUE_PTR(28U, (void *)&chartInstance->c1_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(40U, (void *)&chartInstance->c1_ENGINE_CRANKING);
        _SFD_SET_DATA_VALUE_PTR(42U, (void *)
          &chartInstance->c1_ENGINE_NOT_RUNNING);
        _SFD_SET_DATA_VALUE_PTR(44U, (void *)&chartInstance->c1_ENGINE_RUNNING);
        _SFD_SET_DATA_VALUE_PTR(45U, (void *)&chartInstance->c1_INACTIVE);
        _SFD_SET_DATA_VALUE_PTR(50U, (void *)&chartInstance->c1_SHUTDOWN);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)chartInstance->c1_state_System);
        _SFD_SET_DATA_VALUE_PTR(52U, (void *)&chartInstance->c1_SYS_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(49U, (void *)&chartInstance->c1_NO_COMMUNICATION);
        _SFD_SET_DATA_VALUE_PTR(39U, (void *)
          &chartInstance->c1_CD_PANEL_SHUTDOWN_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(47U, (void *)&chartInstance->c1_NON_FUNCTIONAL);
        _SFD_SET_DATA_VALUE_PTR(46U, (void *)&chartInstance->c1_MULTIPLE);
        _SFD_SET_DATA_VALUE_PTR(43U, (void *)&chartInstance->c1_ENGINE_OFF);
        _SFD_SET_DATA_VALUE_PTR(12U, (void *)chartInstance->c1_din_RemoteKey);
        _SFD_SET_DATA_VALUE_PTR(48U, (void *)&chartInstance->c1_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(13U, (void *)
          chartInstance->c1_state_KeylessPanel);
        _SFD_SET_DATA_VALUE_PTR(30U, (void *)&chartInstance->c1_CD_ECU_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(14U, (void *)chartInstance->c1_state_CommECU);
        _SFD_SET_DATA_VALUE_PTR(15U, (void *)chartInstance->c1_can_ST_EStop);
        _SFD_SET_DATA_VALUE_PTR(16U, (void *)chartInstance->c1_can_ACD_EStop);
        _SFD_SET_DATA_VALUE_PTR(41U, (void *)
          &chartInstance->c1_ENGINE_INITIALIZE);
        _SFD_SET_DATA_VALUE_PTR(29U, (void *)
          &chartInstance->c1_CD_ECU_DEBOUNCE_WAIT_TO_START);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)&chartInstance->c1_debounceCount);
        _SFD_SET_DATA_VALUE_PTR(51U, (void *)
          &chartInstance->c1_STARTER_INHIBITED);
        _SFD_SET_DATA_VALUE_PTR(17U, (void *)
          chartInstance->c1_ecu_EngineStarterMode);
        _SFD_SET_DATA_VALUE_PTR(18U, (void *)
          chartInstance->c1_state_EngineSpeedDerate);
        _SFD_SET_DATA_VALUE_PTR(19U, (void *)chartInstance->c1_state_FuelTemp);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)
          &chartInstance->c1_panelMissingDebounce);
        _SFD_SET_DATA_VALUE_PTR(38U, (void *)
          &chartInstance->c1_CD_PANEL_SHUTDOWN_DEBOUNCE);
        _SFD_SET_DATA_VALUE_PTR(20U, (void *)
          chartInstance->c1_state_CommStdPanel);
        _SFD_SET_DATA_VALUE_PTR(21U, (void *)chartInstance->c1_state_DeluxeG5);
        _SFD_SET_DATA_VALUE_PTR(22U, (void *)
          chartInstance->c1_state_CommDeluxeG55);
        _SFD_SET_DATA_VALUE_PTR(31U, (void *)
          &chartInstance->c1_CD_EMEA_CONSOLE_CRANK_INHIBIT);
        _SFD_SET_DATA_VALUE_PTR(23U, (void *)chartInstance->c1_state_Console);
        _SFD_SET_DATA_VALUE_PTR(36U, (void *)
          &chartInstance->c1_CD_FACTORY_TURBO_PRIME_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(24U, (void *)chartInstance->c1_actualHourMeter);
        _SFD_SET_DATA_VALUE_PTR(37U, (void *)
          &chartInstance->c1_CD_FACTORY_TURBO_PRIME_HOUR_ENABLE);
        _SFD_SET_DATA_VALUE_PTR(25U, (void *)chartInstance->c1_dv_TurboPrime);
        _SFD_SET_DATA_VALUE_PTR(53U, (void *)
          &chartInstance->c1_TURBO_PRIME_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)&chartInstance->c1_debouncePrimer);
        _SFD_SET_DATA_VALUE_PTR(34U, (void *)
          &chartInstance->c1_CD_FACTORY_TURBO_PRIME_DEBOUNCE_DISABLE_FUEL);
        _SFD_SET_DATA_VALUE_PTR(35U, (void *)
          &chartInstance->c1_CD_FACTORY_TURBO_PRIME_DEBOUNCE_WAIT);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)
          &chartInstance->c1_flag_PrimeComplete);
        _SFD_SET_DATA_VALUE_PTR(27U, (void *)chartInstance->c1_state_TurboPrime);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s8M3M9hTmqGErGRAInzYMG";
}

static void sf_opaque_initialize_c1_MX_Gtwy_Control(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_MX_Gtwy_Control((SFc1_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
  initialize_c1_MX_Gtwy_Control((SFc1_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_MX_Gtwy_Control(void *chartInstanceVar)
{
  enable_c1_MX_Gtwy_Control((SFc1_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c1_MX_Gtwy_Control(void *chartInstanceVar)
{
  disable_c1_MX_Gtwy_Control((SFc1_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_MX_Gtwy_Control(void *chartInstanceVar)
{
  sf_gateway_c1_MX_Gtwy_Control((SFc1_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_MX_Gtwy_Control(SimStruct* S)
{
  return get_sim_state_c1_MX_Gtwy_Control((SFc1_MX_Gtwy_ControlInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_MX_Gtwy_Control(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c1_MX_Gtwy_Control((SFc1_MX_Gtwy_ControlInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c1_MX_Gtwy_Control(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_MX_Gtwy_ControlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MX_Gtwy_Control_optimization_info();
    }

    finalize_c1_MX_Gtwy_Control((SFc1_MX_Gtwy_ControlInstanceStruct*)
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
  initSimStructsc1_MX_Gtwy_Control((SFc1_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_MX_Gtwy_Control(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_MX_Gtwy_Control((SFc1_MX_Gtwy_ControlInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c1_MX_Gtwy_Control(SimStruct *S)
{
  /* Actual parameters from chart:
     ACTIVE CD_ECU_DEBOUNCE_WAIT_TO_START CD_ECU_FUNCTION CD_EMEA_CONSOLE_CRANK_INHIBIT CD_ENGINE_SPEED_NOT_RUNNING CD_ENGINE_SPEED_RUNNING CD_FACTORY_TURBO_PRIME_DEBOUNCE_DISABLE_FUEL CD_FACTORY_TURBO_PRIME_DEBOUNCE_WAIT CD_FACTORY_TURBO_PRIME_FUNCTION CD_FACTORY_TURBO_PRIME_HOUR_ENABLE CD_PANEL_SHUTDOWN_DEBOUNCE CD_PANEL_SHUTDOWN_FUNCTION ENGINE_CRANKING ENGINE_INITIALIZE ENGINE_NOT_RUNNING ENGINE_OFF ENGINE_RUNNING INACTIVE MULTIPLE NON_FUNCTIONAL NORMAL NO_COMMUNICATION SHUTDOWN STARTER_INHIBITED SYS_NORMAL TURBO_PRIME_ACTIVE
   */
  const char_T *rtParamNames[] = { "ACTIVE", "CD_ECU_DEBOUNCE_WAIT_TO_START",
    "CD_ECU_FUNCTION", "CD_EMEA_CONSOLE_CRANK_INHIBIT",
    "CD_ENGINE_SPEED_NOT_RUNNING", "CD_ENGINE_SPEED_RUNNING",
    "CD_FACTORY_TURBO_PRIME_DEBOUNCE_DISABLE_FUEL",
    "CD_FACTORY_TURBO_PRIME_DEBOUNCE_WAIT", "CD_FACTORY_TURBO_PRIME_FUNCTION",
    "CD_FACTORY_TURBO_PRIME_HOUR_ENABLE", "CD_PANEL_SHUTDOWN_DEBOUNCE",
    "CD_PANEL_SHUTDOWN_FUNCTION", "ENGINE_CRANKING", "ENGINE_INITIALIZE",
    "ENGINE_NOT_RUNNING", "ENGINE_OFF", "ENGINE_RUNNING", "INACTIVE", "MULTIPLE",
    "NON_FUNCTIONAL", "NORMAL", "NO_COMMUNICATION", "SHUTDOWN",
    "STARTER_INHIBITED", "SYS_NORMAL", "TURBO_PRIME_ACTIVE" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_UINT8);

  /* registration for CD_ECU_DEBOUNCE_WAIT_TO_START*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT16);

  /* registration for CD_ECU_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT8);

  /* registration for CD_EMEA_CONSOLE_CRANK_INHIBIT*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_UINT8);

  /* registration for CD_ENGINE_SPEED_NOT_RUNNING*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_UINT16);

  /* registration for CD_ENGINE_SPEED_RUNNING*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_UINT16);

  /* registration for CD_FACTORY_TURBO_PRIME_DEBOUNCE_DISABLE_FUEL*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_UINT16);

  /* registration for CD_FACTORY_TURBO_PRIME_DEBOUNCE_WAIT*/
  ssRegDlgParamAsRunTimeParam(S, 7, 7, rtParamNames[7], SS_UINT16);

  /* registration for CD_FACTORY_TURBO_PRIME_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 8, 8, rtParamNames[8], SS_UINT8);

  /* registration for CD_FACTORY_TURBO_PRIME_HOUR_ENABLE*/
  ssRegDlgParamAsRunTimeParam(S, 9, 9, rtParamNames[9], SS_UINT32);

  /* registration for CD_PANEL_SHUTDOWN_DEBOUNCE*/
  ssRegDlgParamAsRunTimeParam(S, 10, 10, rtParamNames[10], SS_UINT16);

  /* registration for CD_PANEL_SHUTDOWN_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 11, 11, rtParamNames[11], SS_UINT8);

  /* registration for ENGINE_CRANKING*/
  ssRegDlgParamAsRunTimeParam(S, 12, 12, rtParamNames[12], SS_UINT8);

  /* registration for ENGINE_INITIALIZE*/
  ssRegDlgParamAsRunTimeParam(S, 13, 13, rtParamNames[13], SS_UINT8);

  /* registration for ENGINE_NOT_RUNNING*/
  ssRegDlgParamAsRunTimeParam(S, 14, 14, rtParamNames[14], SS_UINT8);

  /* registration for ENGINE_OFF*/
  ssRegDlgParamAsRunTimeParam(S, 15, 15, rtParamNames[15], SS_UINT8);

  /* registration for ENGINE_RUNNING*/
  ssRegDlgParamAsRunTimeParam(S, 16, 16, rtParamNames[16], SS_UINT8);

  /* registration for INACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 17, 17, rtParamNames[17], SS_UINT8);

  /* registration for MULTIPLE*/
  ssRegDlgParamAsRunTimeParam(S, 18, 18, rtParamNames[18], SS_UINT8);

  /* registration for NON_FUNCTIONAL*/
  ssRegDlgParamAsRunTimeParam(S, 19, 19, rtParamNames[19], SS_UINT8);

  /* registration for NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 20, 20, rtParamNames[20], SS_UINT8);

  /* registration for NO_COMMUNICATION*/
  ssRegDlgParamAsRunTimeParam(S, 21, 21, rtParamNames[21], SS_UINT8);

  /* registration for SHUTDOWN*/
  ssRegDlgParamAsRunTimeParam(S, 22, 22, rtParamNames[22], SS_UINT8);

  /* registration for STARTER_INHIBITED*/
  ssRegDlgParamAsRunTimeParam(S, 23, 23, rtParamNames[23], SS_UINT8);

  /* registration for SYS_NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 24, 24, rtParamNames[24], SS_UINT8);

  /* registration for TURBO_PRIME_ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 25, 25, rtParamNames[25], SS_UINT8);
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
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,1,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 1);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,1);
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
        infoStruct,1,22);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 22; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2763017705U));
  ssSetChecksum1(S,(3577960215U));
  ssSetChecksum2(S,(3648971928U));
  ssSetChecksum3(S,(2543089229U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_MX_Gtwy_Control(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c1_MX_Gtwy_Control(SimStruct *S)
{
  SFc1_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc1_MX_Gtwy_ControlInstanceStruct *)utMalloc(sizeof
    (SFc1_MX_Gtwy_ControlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc1_MX_Gtwy_ControlInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_MX_Gtwy_Control;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_MX_Gtwy_Control;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_MX_Gtwy_Control;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_MX_Gtwy_Control;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_MX_Gtwy_Control;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_MX_Gtwy_Control;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_MX_Gtwy_Control;
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
  mdl_start_c1_MX_Gtwy_Control(chartInstance);
}

void c1_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_MX_Gtwy_Control(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_MX_Gtwy_Control_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
