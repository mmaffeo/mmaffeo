/* Include files */

#include "MX_Gtwy_Control_sfun.h"
#include "c6_MX_Gtwy_Control.h"
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
#define c6_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c6_IN_NON_FUNCTIONAL           ((uint8_T)1U)
#define c6_IN_STATE                    ((uint8_T)2U)
#define c6_IN_NORMAL                   ((uint8_T)1U)
#define c6_IN_OORH                     ((uint8_T)2U)
#define c6_IN_OORL                     ((uint8_T)3U)
#define c6_IN_ABSENT                   ((uint8_T)1U)
#define c6_IN_PRESENT                  ((uint8_T)2U)
#define c6_IN_DEBOUNCE_ABSENT          ((uint8_T)2U)
#define c6_IN_DEBOUNCE_PRESENT         ((uint8_T)1U)
#define c6_IN_DEBOUNCE                 ((uint8_T)1U)
#define c6_b_IN_OORL                   ((uint8_T)2U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initialize_params_c6_MX_Gtwy_Control
  (SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void enable_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void disable_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c6_update_debugger_state_c6_MX_Gtwy_Control
  (SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c6_MX_Gtwy_Control
  (SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void set_sim_state_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct *
  chartInstance, const mxArray *c6_st);
static void c6_set_sim_state_side_effects_c6_MX_Gtwy_Control
  (SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void finalize_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void sf_gateway_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void mdl_start_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initSimStructsc6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c6_STATE(SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c6_exit_internal_STATE(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c6_b_NORMAL(SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c6_exit_internal_NORMAL(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c6_exit_internal_ABSENT(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c6_exit_internal_PRESENT(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c6_exit_internal_OORH(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c6_exit_internal_OORL(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber, uint32_T c6_instanceNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static int32_T c6_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static uint8_T c6_b_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_b_tp_NON_FUNCTIONAL, const char_T
  *c6_identifier);
static uint8_T c6_c_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static uint16_T c6_d_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_b_CD_CONSOLE_PRESENT_LOW, const char_T
  *c6_identifier);
static uint16_T c6_e_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_f_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_b_setSimStateSideEffectsInfo, const char_T
  *c6_identifier);
static const mxArray *c6_g_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static const mxArray *sf_get_hover_data_for_msg
  (SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c6_ssid);
static void c6_init_sf_message_store_memory(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static uint16_T c6__u16_s32_(SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c6_b, uint32_T c6_ssid_src_loc, int32_T c6_offset_src_loc, int32_T
  c6_length_src_loc);
static int32_T c6__s32_add__(SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c6_b, int32_T c6_c, uint32_T c6_ssid_src_loc, int32_T
  c6_offset_src_loc, int32_T c6_length_src_loc);
static void init_dsm_address_info(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc6_MX_Gtwy_Control(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c6_doSetSimStateSideEffects = 0U;
  chartInstance->c6_setSimStateSideEffectsInfo = NULL;
  chartInstance->c6_tp_NON_FUNCTIONAL = 0U;
  chartInstance->c6_is_STATE = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_tp_STATE = 0U;
  chartInstance->c6_is_NORMAL = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_tp_NORMAL = 0U;
  chartInstance->c6_is_ABSENT = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_tp_ABSENT = 0U;
  chartInstance->c6_b_tp_ABSENT = 0U;
  chartInstance->c6_tp_DEBOUNCE_ABSENT = 0U;
  chartInstance->c6_is_PRESENT = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_tp_PRESENT = 0U;
  chartInstance->c6_tp_DEBOUNCE_PRESENT = 0U;
  chartInstance->c6_b_tp_PRESENT = 0U;
  chartInstance->c6_is_OORH = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_tp_OORH = 0U;
  chartInstance->c6_tp_DEBOUNCE = 0U;
  chartInstance->c6_b_tp_OORH = 0U;
  chartInstance->c6_is_OORL = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_tp_OORL = 0U;
  chartInstance->c6_b_tp_DEBOUNCE = 0U;
  chartInstance->c6_b_tp_OORL = 0U;
  chartInstance->c6_is_active_c6_MX_Gtwy_Control = 0U;
  chartInstance->c6_is_c6_MX_Gtwy_Control = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_debounceCount = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c6_state_Console = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_Console, 8U);
  }
}

static void initialize_params_c6_MX_Gtwy_Control
  (SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  real_T c6_d0;
  real_T c6_d1;
  real_T c6_d2;
  real_T c6_d3;
  real_T c6_d4;
  real_T c6_d5;
  real_T c6_d6;
  real_T c6_d7;
  real_T c6_d8;
  real_T c6_d9;
  real_T c6_d10;
  real_T c6_d11;
  real_T c6_d12;
  real_T c6_d13;
  real_T c6_d14;
  real_T c6_d15;
  sf_mex_import_named("CD_CONSOLE_PRESENT_LOW", sf_mex_get_sfun_param
                      (chartInstance->S, 9, 0), &c6_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_CD_CONSOLE_PRESENT_LOW = (uint16_T)c6_d0;
  sf_mex_import_named("CD_CONSOLE_PRESENT_HIGH", sf_mex_get_sfun_param
                      (chartInstance->S, 8, 0), &c6_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_CD_CONSOLE_PRESENT_HIGH = (uint16_T)c6_d1;
  sf_mex_import_named("CD_CONSOLE_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 5, 0), &c6_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_CD_CONSOLE_FUNCTION = (uint8_T)c6_d2;
  sf_mex_import_named("CD_CONSOLE_DEBOUNCE_PRESENT", sf_mex_get_sfun_param
                      (chartInstance->S, 4, 0), &c6_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_CD_CONSOLE_DEBOUNCE_PRESENT = (uint16_T)c6_d3;
  sf_mex_import_named("CD_CONSOLE_DEBOUNCE_ABSENT", sf_mex_get_sfun_param
                      (chartInstance->S, 1, 0), &c6_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_CD_CONSOLE_DEBOUNCE_ABSENT = (uint16_T)c6_d4;
  sf_mex_import_named("CD_CONSOLE_OORH", sf_mex_get_sfun_param(chartInstance->S,
    6, 0), &c6_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_CD_CONSOLE_OORH = (uint16_T)c6_d5;
  sf_mex_import_named("CD_CONSOLE_DEBOUNCE_OORH", sf_mex_get_sfun_param
                      (chartInstance->S, 2, 0), &c6_d6, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_CD_CONSOLE_DEBOUNCE_OORH = (uint16_T)c6_d6;
  sf_mex_import_named("CD_CONSOLE_OORL", sf_mex_get_sfun_param(chartInstance->S,
    7, 0), &c6_d7, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_CD_CONSOLE_OORL = (uint16_T)c6_d7;
  sf_mex_import_named("CD_CONSOLE_DEBOUNCE_OORL", sf_mex_get_sfun_param
                      (chartInstance->S, 3, 0), &c6_d8, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_CD_CONSOLE_DEBOUNCE_OORL = (uint16_T)c6_d8;
  sf_mex_import_named("ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c6_d9, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_ACTIVE = (uint8_T)c6_d9;
  sf_mex_import_named("INACTIVE", sf_mex_get_sfun_param(chartInstance->S, 10, 0),
                      &c6_d10, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_INACTIVE = (uint8_T)c6_d10;
  sf_mex_import_named("OORH", sf_mex_get_sfun_param(chartInstance->S, 13, 0),
                      &c6_d11, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_OORH = (uint8_T)c6_d11;
  sf_mex_import_named("OORL", sf_mex_get_sfun_param(chartInstance->S, 14, 0),
                      &c6_d12, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_OORL = (uint8_T)c6_d12;
  sf_mex_import_named("NON_FUNCTIONAL", sf_mex_get_sfun_param(chartInstance->S,
    11, 0), &c6_d13, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_NON_FUNCTIONAL = (uint8_T)c6_d13;
  sf_mex_import_named("NORMAL", sf_mex_get_sfun_param(chartInstance->S, 12, 0),
                      &c6_d14, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_NORMAL = (uint8_T)c6_d14;
  sf_mex_import_named("SYS_NORMAL", sf_mex_get_sfun_param(chartInstance->S, 15,
    0), &c6_d15, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c6_SYS_NORMAL = (uint8_T)c6_d15;
}

static void enable_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c6_update_debugger_state_c6_MX_Gtwy_Control
  (SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  uint32_T c6_prevAniVal;
  c6_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c6_is_active_c6_MX_Gtwy_Control == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_c6_MX_Gtwy_Control == c6_IN_NON_FUNCTIONAL) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_c6_MX_Gtwy_Control == c6_IN_STATE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_STATE == c6_IN_NORMAL) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_NORMAL == c6_IN_ABSENT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_ABSENT == c6_IN_DEBOUNCE_ABSENT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_ABSENT == c6_IN_ABSENT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_NORMAL == c6_IN_PRESENT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_PRESENT == c6_IN_DEBOUNCE_PRESENT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_PRESENT == c6_IN_PRESENT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_STATE == c6_IN_OORH) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_OORH == c6_IN_DEBOUNCE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_OORH == c6_IN_OORH) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_STATE == c6_IN_OORL) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_OORL == c6_IN_DEBOUNCE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_OORL == c6_b_IN_OORL) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
  }

  _SFD_SET_ANIMATION(c6_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c6_MX_Gtwy_Control
  (SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  uint8_T c6_hoistedGlobal;
  const mxArray *c6_b_y = NULL;
  uint16_T c6_b_hoistedGlobal;
  const mxArray *c6_c_y = NULL;
  uint8_T c6_c_hoistedGlobal;
  const mxArray *c6_d_y = NULL;
  uint8_T c6_d_hoistedGlobal;
  const mxArray *c6_e_y = NULL;
  uint8_T c6_e_hoistedGlobal;
  const mxArray *c6_f_y = NULL;
  uint8_T c6_f_hoistedGlobal;
  const mxArray *c6_g_y = NULL;
  uint8_T c6_g_hoistedGlobal;
  const mxArray *c6_h_y = NULL;
  uint8_T c6_h_hoistedGlobal;
  const mxArray *c6_i_y = NULL;
  uint8_T c6_i_hoistedGlobal;
  const mxArray *c6_j_y = NULL;
  uint8_T c6_j_hoistedGlobal;
  const mxArray *c6_k_y = NULL;
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellmatrix(10, 1), false);
  c6_hoistedGlobal = *chartInstance->c6_state_Console;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_hoistedGlobal, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_b_hoistedGlobal = chartInstance->c6_debounceCount;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_b_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  c6_c_hoistedGlobal = chartInstance->c6_is_active_c6_MX_Gtwy_Control;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_c_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 2, c6_d_y);
  c6_d_hoistedGlobal = chartInstance->c6_is_c6_MX_Gtwy_Control;
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_d_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 3, c6_e_y);
  c6_e_hoistedGlobal = chartInstance->c6_is_NORMAL;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_e_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 4, c6_f_y);
  c6_f_hoistedGlobal = chartInstance->c6_is_OORH;
  c6_g_y = NULL;
  sf_mex_assign(&c6_g_y, sf_mex_create("y", &c6_f_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 5, c6_g_y);
  c6_g_hoistedGlobal = chartInstance->c6_is_OORL;
  c6_h_y = NULL;
  sf_mex_assign(&c6_h_y, sf_mex_create("y", &c6_g_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 6, c6_h_y);
  c6_h_hoistedGlobal = chartInstance->c6_is_ABSENT;
  c6_i_y = NULL;
  sf_mex_assign(&c6_i_y, sf_mex_create("y", &c6_h_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 7, c6_i_y);
  c6_i_hoistedGlobal = chartInstance->c6_is_PRESENT;
  c6_j_y = NULL;
  sf_mex_assign(&c6_j_y, sf_mex_create("y", &c6_i_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 8, c6_j_y);
  c6_j_hoistedGlobal = chartInstance->c6_is_STATE;
  c6_k_y = NULL;
  sf_mex_assign(&c6_k_y, sf_mex_create("y", &c6_j_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c6_y, 9, c6_k_y);
  sf_mex_assign(&c6_st, c6_y, false);
  return c6_st;
}

static void set_sim_state_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct *
  chartInstance, const mxArray *c6_st)
{
  const mxArray *c6_u;
  c6_u = sf_mex_dup(c6_st);
  *chartInstance->c6_state_Console = c6_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 0)), "state_Console");
  chartInstance->c6_debounceCount = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 1)), "debounceCount");
  chartInstance->c6_is_active_c6_MX_Gtwy_Control = c6_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 2)),
     "is_active_c6_MX_Gtwy_Control");
  chartInstance->c6_is_c6_MX_Gtwy_Control = c6_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 3)), "is_c6_MX_Gtwy_Control");
  chartInstance->c6_is_NORMAL = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 4)), "is_NORMAL");
  chartInstance->c6_is_OORH = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 5)), "is_OORH");
  chartInstance->c6_is_OORL = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 6)), "is_OORL");
  chartInstance->c6_is_ABSENT = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 7)), "is_ABSENT");
  chartInstance->c6_is_PRESENT = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 8)), "is_PRESENT");
  chartInstance->c6_is_STATE = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 9)), "is_STATE");
  sf_mex_assign(&chartInstance->c6_setSimStateSideEffectsInfo,
                c6_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c6_u, 10)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c6_u);
  chartInstance->c6_doSetSimStateSideEffects = 1U;
  c6_update_debugger_state_c6_MX_Gtwy_Control(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void c6_set_sim_state_side_effects_c6_MX_Gtwy_Control
  (SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  if (chartInstance->c6_doSetSimStateSideEffects != 0) {
    chartInstance->c6_tp_NON_FUNCTIONAL = (uint8_T)
      (chartInstance->c6_is_c6_MX_Gtwy_Control == c6_IN_NON_FUNCTIONAL);
    chartInstance->c6_tp_STATE = (uint8_T)
      (chartInstance->c6_is_c6_MX_Gtwy_Control == c6_IN_STATE);
    chartInstance->c6_tp_NORMAL = (uint8_T)(chartInstance->c6_is_STATE ==
      c6_IN_NORMAL);
    chartInstance->c6_tp_ABSENT = (uint8_T)(chartInstance->c6_is_NORMAL ==
      c6_IN_ABSENT);
    chartInstance->c6_b_tp_ABSENT = (uint8_T)(chartInstance->c6_is_ABSENT ==
      c6_IN_ABSENT);
    chartInstance->c6_tp_DEBOUNCE_ABSENT = (uint8_T)(chartInstance->c6_is_ABSENT
      == c6_IN_DEBOUNCE_ABSENT);
    chartInstance->c6_tp_PRESENT = (uint8_T)(chartInstance->c6_is_NORMAL ==
      c6_IN_PRESENT);
    chartInstance->c6_tp_DEBOUNCE_PRESENT = (uint8_T)
      (chartInstance->c6_is_PRESENT == c6_IN_DEBOUNCE_PRESENT);
    chartInstance->c6_b_tp_PRESENT = (uint8_T)(chartInstance->c6_is_PRESENT ==
      c6_IN_PRESENT);
    chartInstance->c6_tp_OORH = (uint8_T)(chartInstance->c6_is_STATE ==
      c6_IN_OORH);
    chartInstance->c6_tp_DEBOUNCE = (uint8_T)(chartInstance->c6_is_OORH ==
      c6_IN_DEBOUNCE);
    chartInstance->c6_b_tp_OORH = (uint8_T)(chartInstance->c6_is_OORH ==
      c6_IN_OORH);
    chartInstance->c6_tp_OORL = (uint8_T)(chartInstance->c6_is_STATE ==
      c6_IN_OORL);
    chartInstance->c6_b_tp_DEBOUNCE = (uint8_T)(chartInstance->c6_is_OORL ==
      c6_IN_DEBOUNCE);
    chartInstance->c6_b_tp_OORL = (uint8_T)(chartInstance->c6_is_OORL ==
      c6_b_IN_OORL);
    chartInstance->c6_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c6_setSimStateSideEffectsInfo);
}

static void sf_gateway_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c6_temp;
  boolean_T c6_b_temp;
  boolean_T c6_out;
  c6_set_sim_state_side_effects_c6_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_flag_InitEERead, 7U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_MachineLock, 6U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_System, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_SensorSupply2, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_SensorSupply1, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_ain_Console, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_rm_Console, 1U);
  chartInstance->c6_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  if (chartInstance->c6_is_active_c6_MX_Gtwy_Control == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
    chartInstance->c6_is_active_c6_MX_Gtwy_Control = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
    chartInstance->c6_is_c6_MX_Gtwy_Control = c6_IN_NON_FUNCTIONAL;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_NON_FUNCTIONAL = 1U;
    *chartInstance->c6_state_Console = chartInstance->c6_NON_FUNCTIONAL;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_Console, 8U);
  } else {
    switch (chartInstance->c6_is_c6_MX_Gtwy_Control) {
     case c6_IN_NON_FUNCTIONAL:
      CV_CHART_EVAL(5, 0, c6_IN_NON_FUNCTIONAL);
      *chartInstance->c6_state_Console = chartInstance->c6_NON_FUNCTIONAL;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U,
                   chartInstance->c6_sfEvent);
      c6_temp = (_SFD_CCP_CALL(5U, 4U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 4U,
        0, (real_T)chartInstance->c6_CD_CONSOLE_FUNCTION, (real_T)
        chartInstance->c6_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c6_CD_CONSOLE_FUNCTION !=
        chartInstance->c6_NON_FUNCTIONAL) != 0U, chartInstance->c6_sfEvent) !=
                 0U);
      if (c6_temp) {
        c6_temp = (_SFD_CCP_CALL(5U, 4U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 4U,
          1, (real_T)*chartInstance->c6_state_System, (real_T)
          chartInstance->c6_SYS_NORMAL, 0, 0U, *chartInstance->c6_state_System ==
          chartInstance->c6_SYS_NORMAL) != 0U, chartInstance->c6_sfEvent) != 0U);
      }

      c6_b_temp = c6_temp;
      if (c6_temp) {
        c6_b_temp = (_SFD_CCP_CALL(5U, 4U, 2, *chartInstance->c6_flag_InitEERead
          != 0U, chartInstance->c6_sfEvent) != 0U);
      }

      c6_out = (CV_TRANSITION_EVAL(4U, (int32_T)c6_b_temp) != 0);
      if (c6_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_NON_FUNCTIONAL = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
        chartInstance->c6_is_c6_MX_Gtwy_Control = c6_IN_STATE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_STATE = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c6_sfEvent);
        chartInstance->c6_is_STATE = c6_IN_NORMAL;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_NORMAL = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
        chartInstance->c6_is_NORMAL = c6_IN_ABSENT;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_ABSENT = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
        chartInstance->c6_is_ABSENT = c6_IN_DEBOUNCE_ABSENT;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_DEBOUNCE_ABSENT = 1U;
        chartInstance->c6_debounceCount = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                     chartInstance->c6_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c6_sfEvent);
      break;

     case c6_IN_STATE:
      CV_CHART_EVAL(5, 0, c6_IN_STATE);
      c6_STATE(chartInstance);
      break;

     default:
      CV_CHART_EVAL(5, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c6_is_c6_MX_Gtwy_Control = c6_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MX_Gtwy_ControlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  c6_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void initSimStructsc6_MX_Gtwy_Control(SFc6_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void c6_STATE(SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c6_out;
  boolean_T c6_temp;
  boolean_T c6_b_temp;
  boolean_T c6_c_temp;
  boolean_T c6_d_temp;
  boolean_T c6_b_out;
  boolean_T c6_c_out;
  boolean_T c6_d_out;
  boolean_T c6_e_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U, chartInstance->c6_sfEvent);
  c6_out = (CV_TRANSITION_EVAL(15U, (int32_T)(_SFD_CCP_CALL(5U, 15U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 15U, 0, (real_T)
    *chartInstance->c6_state_System, (real_T)chartInstance->c6_SYS_NORMAL, 0, 1U,
    *chartInstance->c6_state_System != chartInstance->c6_SYS_NORMAL) != 0U,
    chartInstance->c6_sfEvent) != 0U)) != 0);
  if (c6_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c6_sfEvent);
    c6_exit_internal_STATE(chartInstance);
    chartInstance->c6_tp_STATE = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
    chartInstance->c6_is_c6_MX_Gtwy_Control = c6_IN_NON_FUNCTIONAL;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_NON_FUNCTIONAL = 1U;
    *chartInstance->c6_state_Console = chartInstance->c6_NON_FUNCTIONAL;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_Console, 8U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c6_sfEvent);
    switch (chartInstance->c6_is_STATE) {
     case c6_IN_NORMAL:
      CV_STATE_EVAL(1, 0, c6_IN_NORMAL);
      c6_b_NORMAL(chartInstance);
      break;

     case c6_IN_OORH:
      CV_STATE_EVAL(1, 0, c6_IN_OORH);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 16U,
                   chartInstance->c6_sfEvent);
      c6_temp = (_SFD_CCP_CALL(5U, 16U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 16U,
        0, (real_T)*chartInstance->c6_ain_Console, (real_T)
        chartInstance->c6_CD_CONSOLE_OORH, 0, 2U, *chartInstance->c6_ain_Console
        < chartInstance->c6_CD_CONSOLE_OORH) != 0U, chartInstance->c6_sfEvent)
                 != 0U);
      if (c6_temp) {
        c6_temp = (_SFD_CCP_CALL(5U, 16U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          16U, 1, (real_T)*chartInstance->c6_state_Console, (real_T)
          chartInstance->c6_OORH, 0, 1U, *chartInstance->c6_state_Console !=
          chartInstance->c6_OORH) != 0U, chartInstance->c6_sfEvent) != 0U);
      }

      c6_c_temp = c6_temp;
      if (!c6_temp) {
        c6_c_temp = (_SFD_CCP_CALL(5U, 16U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
          16U, 2, (real_T)*chartInstance->c6_state_SensorSupply2, (real_T)
          chartInstance->c6_NORMAL, 0, 1U,
          *chartInstance->c6_state_SensorSupply2 != chartInstance->c6_NORMAL) !=
          0U, chartInstance->c6_sfEvent) != 0U);
      }

      c6_b_out = (CV_TRANSITION_EVAL(16U, (int32_T)c6_c_temp) != 0);
      if (c6_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c6_sfEvent);
        c6_exit_internal_OORH(chartInstance);
        chartInstance->c6_tp_OORH = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
        chartInstance->c6_is_STATE = c6_IN_NORMAL;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_NORMAL = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
        chartInstance->c6_is_NORMAL = c6_IN_ABSENT;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_ABSENT = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
        chartInstance->c6_is_ABSENT = c6_IN_DEBOUNCE_ABSENT;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_DEBOUNCE_ABSENT = 1U;
        chartInstance->c6_debounceCount = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                     chartInstance->c6_sfEvent);
        switch (chartInstance->c6_is_OORH) {
         case c6_IN_DEBOUNCE:
          CV_STATE_EVAL(9, 0, c6_IN_DEBOUNCE);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 9U,
                       chartInstance->c6_sfEvent);
          c6_d_out = (CV_TRANSITION_EVAL(9U, (int32_T)(_SFD_CCP_CALL(5U, 9U, 0,
            (boolean_T)CV_RELATIONAL_EVAL(5U, 9U, 0, (real_T)
            chartInstance->c6_debounceCount, (real_T)
            chartInstance->c6_CD_CONSOLE_DEBOUNCE_OORH, 0, 5U,
            chartInstance->c6_debounceCount >=
            chartInstance->c6_CD_CONSOLE_DEBOUNCE_OORH) != 0U,
            chartInstance->c6_sfEvent) != 0U)) != 0);
          if (c6_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
            chartInstance->c6_tp_DEBOUNCE = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
            chartInstance->c6_is_OORH = c6_IN_OORH;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
            chartInstance->c6_b_tp_OORH = 1U;
            *chartInstance->c6_state_Console = chartInstance->c6_OORH;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_Console, 8U);
            SendMsg_BICSControl_Now();
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                         chartInstance->c6_sfEvent);
            chartInstance->c6_debounceCount = c6__u16_s32_(chartInstance,
              c6__s32_add__(chartInstance, (int32_T)
                            chartInstance->c6_debounceCount, 1, 7U, 36U, 15U),
              7U, 36U, 15U);
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c6_sfEvent);
          break;

         case c6_IN_OORH:
          CV_STATE_EVAL(9, 0, c6_IN_OORH);
          *chartInstance->c6_state_Console = chartInstance->c6_OORH;
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                       chartInstance->c6_sfEvent);
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c6_sfEvent);
          break;

         default:
          CV_STATE_EVAL(9, 0, 0);

          /* Unreachable state, for coverage only */
          chartInstance->c6_is_OORH = c6_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
          break;
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c6_sfEvent);
      break;

     case c6_IN_OORL:
      CV_STATE_EVAL(1, 0, c6_IN_OORL);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 17U,
                   chartInstance->c6_sfEvent);
      c6_b_temp = (_SFD_CCP_CALL(5U, 17U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        17U, 0, (real_T)*chartInstance->c6_ain_Console, (real_T)
        chartInstance->c6_CD_CONSOLE_OORL, 0, 4U, *chartInstance->c6_ain_Console
        > chartInstance->c6_CD_CONSOLE_OORL) != 0U, chartInstance->c6_sfEvent)
                   != 0U);
      if (c6_b_temp) {
        c6_b_temp = (_SFD_CCP_CALL(5U, 17U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          17U, 1, (real_T)*chartInstance->c6_state_Console, (real_T)
          chartInstance->c6_OORL, 0, 1U, *chartInstance->c6_state_Console !=
          chartInstance->c6_OORL) != 0U, chartInstance->c6_sfEvent) != 0U);
      }

      c6_d_temp = c6_b_temp;
      if (!c6_b_temp) {
        c6_d_temp = (_SFD_CCP_CALL(5U, 17U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
          17U, 2, (real_T)*chartInstance->c6_state_SensorSupply2, (real_T)
          chartInstance->c6_NORMAL, 0, 1U,
          *chartInstance->c6_state_SensorSupply2 != chartInstance->c6_NORMAL) !=
          0U, chartInstance->c6_sfEvent) != 0U);
      }

      c6_c_out = (CV_TRANSITION_EVAL(17U, (int32_T)c6_d_temp) != 0);
      if (c6_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c6_sfEvent);
        c6_exit_internal_OORL(chartInstance);
        chartInstance->c6_tp_OORL = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
        chartInstance->c6_is_STATE = c6_IN_NORMAL;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_NORMAL = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
        chartInstance->c6_is_NORMAL = c6_IN_ABSENT;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_ABSENT = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
        chartInstance->c6_is_ABSENT = c6_IN_DEBOUNCE_ABSENT;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_DEBOUNCE_ABSENT = 1U;
        chartInstance->c6_debounceCount = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                     chartInstance->c6_sfEvent);
        switch (chartInstance->c6_is_OORL) {
         case c6_IN_DEBOUNCE:
          CV_STATE_EVAL(12, 0, c6_IN_DEBOUNCE);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 14U,
                       chartInstance->c6_sfEvent);
          c6_e_out = (CV_TRANSITION_EVAL(14U, (int32_T)(_SFD_CCP_CALL(5U, 14U, 0,
            (boolean_T)CV_RELATIONAL_EVAL(5U, 14U, 0, (real_T)
            chartInstance->c6_debounceCount, (real_T)
            chartInstance->c6_CD_CONSOLE_DEBOUNCE_OORL, 0, 5U,
            chartInstance->c6_debounceCount >=
            chartInstance->c6_CD_CONSOLE_DEBOUNCE_OORL) != 0U,
            chartInstance->c6_sfEvent) != 0U)) != 0);
          if (c6_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
            chartInstance->c6_b_tp_DEBOUNCE = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
            chartInstance->c6_is_OORL = c6_b_IN_OORL;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
            chartInstance->c6_b_tp_OORL = 1U;
            *chartInstance->c6_state_Console = chartInstance->c6_OORL;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_Console, 8U);
            SendMsg_BICSControl_Now();
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U,
                         chartInstance->c6_sfEvent);
            chartInstance->c6_debounceCount = c6__u16_s32_(chartInstance,
              c6__s32_add__(chartInstance, (int32_T)
                            chartInstance->c6_debounceCount, 1, 8U, 36U, 15U),
              8U, 36U, 15U);
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c6_sfEvent);
          break;

         case c6_b_IN_OORL:
          CV_STATE_EVAL(12, 0, c6_b_IN_OORL);
          *chartInstance->c6_state_Console = chartInstance->c6_OORL;
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 14U,
                       chartInstance->c6_sfEvent);
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c6_sfEvent);
          break;

         default:
          CV_STATE_EVAL(12, 0, 0);

          /* Unreachable state, for coverage only */
          chartInstance->c6_is_OORL = c6_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
          break;
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c6_sfEvent);
      break;

     default:
      CV_STATE_EVAL(1, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c6_is_STATE = c6_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
      break;
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c6_sfEvent);
}

static void c6_exit_internal_STATE(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c6_is_STATE) {
   case c6_IN_NORMAL:
    CV_STATE_EVAL(1, 1, c6_IN_NORMAL);
    c6_exit_internal_NORMAL(chartInstance);
    chartInstance->c6_tp_NORMAL = 0U;
    chartInstance->c6_is_STATE = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_OORH:
    CV_STATE_EVAL(1, 1, c6_IN_OORH);
    c6_exit_internal_OORH(chartInstance);
    chartInstance->c6_tp_OORH = 0U;
    chartInstance->c6_is_STATE = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_OORL:
    CV_STATE_EVAL(1, 1, c6_IN_OORL);
    c6_exit_internal_OORL(chartInstance);
    chartInstance->c6_tp_OORL = 0U;
    chartInstance->c6_is_STATE = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(1, 1, 0);
    chartInstance->c6_is_STATE = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
    break;
  }
}

static void c6_b_NORMAL(SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c6_temp;
  boolean_T c6_out;
  boolean_T c6_b_temp;
  boolean_T c6_b_out;
  boolean_T c6_c_temp;
  boolean_T c6_d_temp;
  boolean_T c6_e_temp;
  boolean_T c6_f_temp;
  boolean_T c6_g_temp;
  boolean_T c6_h_temp;
  boolean_T c6_i_temp;
  boolean_T c6_j_temp;
  boolean_T c6_c_out;
  boolean_T c6_d_out;
  boolean_T c6_k_temp;
  boolean_T c6_l_temp;
  boolean_T c6_e_out;
  boolean_T c6_f_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U, chartInstance->c6_sfEvent);
  c6_temp = (_SFD_CCP_CALL(5U, 13U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 13U, 0,
    (real_T)*chartInstance->c6_ain_Console, (real_T)
    chartInstance->c6_CD_CONSOLE_OORL, 0, 3U, *chartInstance->c6_ain_Console <=
    chartInstance->c6_CD_CONSOLE_OORL) != 0U, chartInstance->c6_sfEvent) != 0U);
  if (c6_temp) {
    c6_temp = (_SFD_CCP_CALL(5U, 13U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 13U,
      1, (real_T)*chartInstance->c6_state_SensorSupply2, (real_T)
      chartInstance->c6_NORMAL, 0, 0U, *chartInstance->c6_state_SensorSupply2 ==
      chartInstance->c6_NORMAL) != 0U, chartInstance->c6_sfEvent) != 0U);
  }

  c6_out = (CV_TRANSITION_EVAL(13U, (int32_T)c6_temp) != 0);
  if (c6_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
    c6_exit_internal_NORMAL(chartInstance);
    chartInstance->c6_tp_NORMAL = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
    chartInstance->c6_is_STATE = c6_IN_OORL;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_OORL = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
    chartInstance->c6_is_OORL = c6_IN_DEBOUNCE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
    chartInstance->c6_b_tp_DEBOUNCE = 1U;
    chartInstance->c6_debounceCount = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                 chartInstance->c6_sfEvent);
    c6_b_temp = (_SFD_CCP_CALL(5U, 11U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 11U,
      0, (real_T)*chartInstance->c6_ain_Console, (real_T)
      chartInstance->c6_CD_CONSOLE_OORH, 0, 5U, *chartInstance->c6_ain_Console >=
      chartInstance->c6_CD_CONSOLE_OORH) != 0U, chartInstance->c6_sfEvent) != 0U);
    if (c6_b_temp) {
      c6_b_temp = (_SFD_CCP_CALL(5U, 11U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        11U, 1, (real_T)*chartInstance->c6_state_SensorSupply2, (real_T)
        chartInstance->c6_NORMAL, 0, 0U, *chartInstance->c6_state_SensorSupply2 ==
        chartInstance->c6_NORMAL) != 0U, chartInstance->c6_sfEvent) != 0U);
    }

    c6_b_out = (CV_TRANSITION_EVAL(11U, (int32_T)c6_b_temp) != 0);
    if (c6_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
      c6_exit_internal_NORMAL(chartInstance);
      chartInstance->c6_tp_NORMAL = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
      chartInstance->c6_is_STATE = c6_IN_OORH;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_OORH = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
      chartInstance->c6_is_OORH = c6_IN_DEBOUNCE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_DEBOUNCE = 1U;
      chartInstance->c6_debounceCount = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                   chartInstance->c6_sfEvent);
      switch (chartInstance->c6_is_NORMAL) {
       case c6_IN_ABSENT:
        CV_STATE_EVAL(2, 0, c6_IN_ABSENT);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U,
                     chartInstance->c6_sfEvent);
        c6_c_temp = (_SFD_CCP_CALL(5U, 0U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          0U, 0, (real_T)*chartInstance->c6_rm_Console, (real_T)
          chartInstance->c6_CD_CONSOLE_PRESENT_LOW, 0, 5U,
          *chartInstance->c6_rm_Console >=
          chartInstance->c6_CD_CONSOLE_PRESENT_LOW) != 0U,
          chartInstance->c6_sfEvent) != 0U);
        if (c6_c_temp) {
          c6_c_temp = (_SFD_CCP_CALL(5U, 0U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
            0U, 1, (real_T)*chartInstance->c6_rm_Console, (real_T)
            chartInstance->c6_CD_CONSOLE_PRESENT_HIGH, 0, 3U,
            *chartInstance->c6_rm_Console <=
            chartInstance->c6_CD_CONSOLE_PRESENT_HIGH) != 0U,
            chartInstance->c6_sfEvent) != 0U);
        }

        c6_e_temp = c6_c_temp;
        if (c6_c_temp) {
          c6_e_temp = (_SFD_CCP_CALL(5U, 0U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
            0U, 2, (real_T)*chartInstance->c6_state_SensorSupply2, (real_T)
            chartInstance->c6_NORMAL, 0, 0U,
            *chartInstance->c6_state_SensorSupply2 == chartInstance->c6_NORMAL)
            != 0U, chartInstance->c6_sfEvent) != 0U);
        }

        c6_g_temp = c6_e_temp;
        if (c6_e_temp) {
          c6_g_temp = (_SFD_CCP_CALL(5U, 0U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
            0U, 3, (real_T)*chartInstance->c6_state_SensorSupply1, (real_T)
            chartInstance->c6_NORMAL, 0, 0U,
            *chartInstance->c6_state_SensorSupply1 == chartInstance->c6_NORMAL)
            != 0U, chartInstance->c6_sfEvent) != 0U);
        }

        c6_i_temp = c6_g_temp;
        if (c6_g_temp) {
          c6_i_temp = (_SFD_CCP_CALL(5U, 0U, 4, (boolean_T)CV_RELATIONAL_EVAL(5U,
            0U, 4, (real_T)*chartInstance->c6_state_MachineLock, (real_T)
            chartInstance->c6_INACTIVE, 0, 0U,
            *chartInstance->c6_state_MachineLock == chartInstance->c6_INACTIVE)
            != 0U, chartInstance->c6_sfEvent) != 0U);
        }

        c6_c_out = (CV_TRANSITION_EVAL(0U, (int32_T)c6_i_temp) != 0);
        if (c6_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
          c6_exit_internal_ABSENT(chartInstance);
          chartInstance->c6_tp_ABSENT = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
          chartInstance->c6_is_NORMAL = c6_IN_PRESENT;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
          chartInstance->c6_tp_PRESENT = 1U;
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
          chartInstance->c6_is_PRESENT = c6_IN_DEBOUNCE_PRESENT;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
          chartInstance->c6_tp_DEBOUNCE_PRESENT = 1U;
          chartInstance->c6_debounceCount = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                       chartInstance->c6_sfEvent);
          switch (chartInstance->c6_is_ABSENT) {
           case c6_IN_ABSENT:
            CV_STATE_EVAL(3, 0, c6_IN_ABSENT);
            *chartInstance->c6_state_Console = chartInstance->c6_INACTIVE;
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                         chartInstance->c6_sfEvent);
            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
            break;

           case c6_IN_DEBOUNCE_ABSENT:
            CV_STATE_EVAL(3, 0, c6_IN_DEBOUNCE_ABSENT);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                         chartInstance->c6_sfEvent);
            c6_k_temp = (_SFD_CCP_CALL(5U, 8U, 0, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 8U, 0, (real_T)chartInstance->c6_debounceCount, (real_T)
               chartInstance->c6_CD_CONSOLE_DEBOUNCE_ABSENT, 0, 5U,
               chartInstance->c6_debounceCount >=
               chartInstance->c6_CD_CONSOLE_DEBOUNCE_ABSENT) != 0U,
              chartInstance->c6_sfEvent) != 0U);
            if (!c6_k_temp) {
              c6_k_temp = (_SFD_CCP_CALL(5U, 8U, 1, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 8U, 1, (real_T)
                                   *chartInstance->c6_state_Console, (real_T)
                                   chartInstance->c6_INACTIVE, 0, 0U,
                                   *chartInstance->c6_state_Console ==
                                   chartInstance->c6_INACTIVE) != 0U,
                chartInstance->c6_sfEvent) != 0U);
            }

            c6_e_out = (CV_TRANSITION_EVAL(8U, (int32_T)c6_k_temp) != 0);
            if (c6_e_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
              chartInstance->c6_tp_DEBOUNCE_ABSENT = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
              chartInstance->c6_is_ABSENT = c6_IN_ABSENT;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
              chartInstance->c6_b_tp_ABSENT = 1U;
              *chartInstance->c6_state_Console = chartInstance->c6_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_Console, 8U);
              SendMsg_BICSControl_Now();
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                           chartInstance->c6_sfEvent);
              chartInstance->c6_debounceCount = c6__u16_s32_(chartInstance,
                c6__s32_add__(chartInstance, (int32_T)
                              chartInstance->c6_debounceCount, 1, 6U, 43U, 15U),
                6U, 43U, 15U);
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
            }

            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
            break;

           default:
            CV_STATE_EVAL(3, 0, 0);

            /* Unreachable state, for coverage only */
            chartInstance->c6_is_ABSENT = c6_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
            break;
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
        break;

       case c6_IN_PRESENT:
        CV_STATE_EVAL(2, 0, c6_IN_PRESENT);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                     chartInstance->c6_sfEvent);
        c6_d_temp = (_SFD_CCP_CALL(5U, 5U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          5U, 0, (real_T)*chartInstance->c6_rm_Console, (real_T)
          chartInstance->c6_CD_CONSOLE_PRESENT_LOW, 0, 2U,
          *chartInstance->c6_rm_Console <
          chartInstance->c6_CD_CONSOLE_PRESENT_LOW) != 0U,
          chartInstance->c6_sfEvent) != 0U);
        if (!c6_d_temp) {
          c6_d_temp = (_SFD_CCP_CALL(5U, 5U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
            5U, 1, (real_T)*chartInstance->c6_rm_Console, (real_T)
            chartInstance->c6_CD_CONSOLE_PRESENT_HIGH, 0, 4U,
            *chartInstance->c6_rm_Console >
            chartInstance->c6_CD_CONSOLE_PRESENT_HIGH) != 0U,
            chartInstance->c6_sfEvent) != 0U);
        }

        c6_f_temp = c6_d_temp;
        if (!c6_d_temp) {
          c6_f_temp = (_SFD_CCP_CALL(5U, 5U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
            5U, 2, (real_T)*chartInstance->c6_state_SensorSupply2, (real_T)
            chartInstance->c6_NORMAL, 0, 1U,
            *chartInstance->c6_state_SensorSupply2 != chartInstance->c6_NORMAL)
            != 0U, chartInstance->c6_sfEvent) != 0U);
        }

        c6_h_temp = c6_f_temp;
        if (!c6_f_temp) {
          c6_h_temp = (_SFD_CCP_CALL(5U, 5U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
            5U, 3, (real_T)*chartInstance->c6_state_SensorSupply1, (real_T)
            chartInstance->c6_NORMAL, 0, 1U,
            *chartInstance->c6_state_SensorSupply1 != chartInstance->c6_NORMAL)
            != 0U, chartInstance->c6_sfEvent) != 0U);
        }

        c6_j_temp = c6_h_temp;
        if (!c6_h_temp) {
          c6_j_temp = (_SFD_CCP_CALL(5U, 5U, 4, (boolean_T)CV_RELATIONAL_EVAL(5U,
            5U, 4, (real_T)*chartInstance->c6_state_MachineLock, (real_T)
            chartInstance->c6_ACTIVE, 0, 0U,
            *chartInstance->c6_state_MachineLock == chartInstance->c6_ACTIVE) !=
            0U, chartInstance->c6_sfEvent) != 0U);
        }

        c6_d_out = (CV_TRANSITION_EVAL(5U, (int32_T)c6_j_temp) != 0);
        if (c6_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
          c6_exit_internal_PRESENT(chartInstance);
          chartInstance->c6_tp_PRESENT = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
          chartInstance->c6_is_NORMAL = c6_IN_ABSENT;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
          chartInstance->c6_tp_ABSENT = 1U;
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
          chartInstance->c6_is_ABSENT = c6_IN_DEBOUNCE_ABSENT;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
          chartInstance->c6_tp_DEBOUNCE_ABSENT = 1U;
          chartInstance->c6_debounceCount = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                       chartInstance->c6_sfEvent);
          switch (chartInstance->c6_is_PRESENT) {
           case c6_IN_DEBOUNCE_PRESENT:
            CV_STATE_EVAL(6, 0, c6_IN_DEBOUNCE_PRESENT);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U,
                         chartInstance->c6_sfEvent);
            c6_l_temp = (_SFD_CCP_CALL(5U, 6U, 0, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 6U, 0, (real_T)chartInstance->c6_debounceCount, (real_T)
               chartInstance->c6_CD_CONSOLE_DEBOUNCE_PRESENT, 0, 5U,
               chartInstance->c6_debounceCount >=
               chartInstance->c6_CD_CONSOLE_DEBOUNCE_PRESENT) != 0U,
              chartInstance->c6_sfEvent) != 0U);
            if (!c6_l_temp) {
              c6_l_temp = (_SFD_CCP_CALL(5U, 6U, 1, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 6U, 1, (real_T)
                                   *chartInstance->c6_state_Console, (real_T)
                                   chartInstance->c6_ACTIVE, 0, 0U,
                                   *chartInstance->c6_state_Console ==
                                   chartInstance->c6_ACTIVE) != 0U,
                chartInstance->c6_sfEvent) != 0U);
            }

            c6_f_out = (CV_TRANSITION_EVAL(6U, (int32_T)c6_l_temp) != 0);
            if (c6_f_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
              chartInstance->c6_tp_DEBOUNCE_PRESENT = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
              chartInstance->c6_is_PRESENT = c6_IN_PRESENT;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
              chartInstance->c6_b_tp_PRESENT = 1U;
              *chartInstance->c6_state_Console = chartInstance->c6_ACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_state_Console, 8U);
              SendMsg_BICSControl_Now();
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                           chartInstance->c6_sfEvent);
              chartInstance->c6_debounceCount = c6__u16_s32_(chartInstance,
                c6__s32_add__(chartInstance, (int32_T)
                              chartInstance->c6_debounceCount, 1, 5U, 44U, 15U),
                5U, 44U, 15U);
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_debounceCount, 0U);
            }

            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c6_sfEvent);
            break;

           case c6_IN_PRESENT:
            CV_STATE_EVAL(6, 0, c6_IN_PRESENT);
            *chartInstance->c6_state_Console = chartInstance->c6_ACTIVE;
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                         chartInstance->c6_sfEvent);
            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c6_sfEvent);
            break;

           default:
            CV_STATE_EVAL(6, 0, 0);

            /* Unreachable state, for coverage only */
            chartInstance->c6_is_PRESENT = c6_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
            break;
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c6_sfEvent);
        break;

       default:
        CV_STATE_EVAL(2, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c6_is_NORMAL = c6_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c6_sfEvent);
}

static void c6_exit_internal_NORMAL(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c6_is_NORMAL) {
   case c6_IN_ABSENT:
    CV_STATE_EVAL(2, 1, c6_IN_ABSENT);
    c6_exit_internal_ABSENT(chartInstance);
    chartInstance->c6_tp_ABSENT = 0U;
    chartInstance->c6_is_NORMAL = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_PRESENT:
    CV_STATE_EVAL(2, 1, c6_IN_PRESENT);
    c6_exit_internal_PRESENT(chartInstance);
    chartInstance->c6_tp_PRESENT = 0U;
    chartInstance->c6_is_NORMAL = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(2, 1, 0);
    chartInstance->c6_is_NORMAL = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
    break;
  }
}

static void c6_exit_internal_ABSENT(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c6_is_ABSENT) {
   case c6_IN_ABSENT:
    CV_STATE_EVAL(3, 1, c6_IN_ABSENT);
    chartInstance->c6_b_tp_ABSENT = 0U;
    chartInstance->c6_is_ABSENT = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_DEBOUNCE_ABSENT:
    CV_STATE_EVAL(3, 1, c6_IN_DEBOUNCE_ABSENT);
    chartInstance->c6_tp_DEBOUNCE_ABSENT = 0U;
    chartInstance->c6_is_ABSENT = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(3, 1, 0);
    chartInstance->c6_is_ABSENT = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
    break;
  }
}

static void c6_exit_internal_PRESENT(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c6_is_PRESENT) {
   case c6_IN_DEBOUNCE_PRESENT:
    CV_STATE_EVAL(6, 1, c6_IN_DEBOUNCE_PRESENT);
    chartInstance->c6_tp_DEBOUNCE_PRESENT = 0U;
    chartInstance->c6_is_PRESENT = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_PRESENT:
    CV_STATE_EVAL(6, 1, c6_IN_PRESENT);
    chartInstance->c6_b_tp_PRESENT = 0U;
    chartInstance->c6_is_PRESENT = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(6, 1, 0);
    chartInstance->c6_is_PRESENT = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
    break;
  }
}

static void c6_exit_internal_OORH(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c6_is_OORH) {
   case c6_IN_DEBOUNCE:
    CV_STATE_EVAL(9, 1, c6_IN_DEBOUNCE);
    chartInstance->c6_tp_DEBOUNCE = 0U;
    chartInstance->c6_is_OORH = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_OORH:
    CV_STATE_EVAL(9, 1, c6_IN_OORH);
    chartInstance->c6_b_tp_OORH = 0U;
    chartInstance->c6_is_OORH = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(9, 1, 0);
    chartInstance->c6_is_OORH = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
    break;
  }
}

static void c6_exit_internal_OORL(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c6_is_OORL) {
   case c6_IN_DEBOUNCE:
    CV_STATE_EVAL(12, 1, c6_IN_DEBOUNCE);
    chartInstance->c6_b_tp_DEBOUNCE = 0U;
    chartInstance->c6_is_OORL = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
    break;

   case c6_b_IN_OORL:
    CV_STATE_EVAL(12, 1, c6_b_IN_OORL);
    chartInstance->c6_b_tp_OORL = 0U;
    chartInstance->c6_is_OORL = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(12, 1, 0);
    chartInstance->c6_is_OORL = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
    break;
  }
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber, uint32_T c6_instanceNumber)
{
  (void)(c6_machineNumber);
  (void)(c6_chartNumber);
  (void)(c6_instanceNumber);
}

const mxArray *sf_c6_MX_Gtwy_Control_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  sf_mex_assign(&c6_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c6_nameCaptureInfo;
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc6_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static int32_T c6_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i0;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i0, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc6_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_y = c6_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent), &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  uint8_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc6_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_u = *(uint8_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static uint8_T c6_b_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_b_tp_NON_FUNCTIONAL, const char_T
  *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = (const char *)c6_identifier;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_y = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_tp_NON_FUNCTIONAL),
    &c6_thisId);
  sf_mex_destroy(&c6_b_tp_NON_FUNCTIONAL);
  return c6_y;
}

static uint8_T c6_c_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u0;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u0, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_tp_NON_FUNCTIONAL;
  emlrtMsgIdentifier c6_thisId;
  uint8_T c6_y;
  SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc6_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c6_b_tp_NON_FUNCTIONAL = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_y = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_tp_NON_FUNCTIONAL),
    &c6_thisId);
  sf_mex_destroy(&c6_b_tp_NON_FUNCTIONAL);
  *(uint8_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  uint16_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc6_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_u = *(uint16_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static uint16_T c6_d_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_b_CD_CONSOLE_PRESENT_LOW, const char_T
  *c6_identifier)
{
  uint16_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = (const char *)c6_identifier;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_CD_CONSOLE_PRESENT_LOW), &c6_thisId);
  sf_mex_destroy(&c6_b_CD_CONSOLE_PRESENT_LOW);
  return c6_y;
}

static uint16_T c6_e_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint16_T c6_y;
  uint16_T c6_u1;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u1, 1, 5, 0U, 0, 0U, 0);
  c6_y = c6_u1;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_CD_CONSOLE_PRESENT_LOW;
  emlrtMsgIdentifier c6_thisId;
  uint16_T c6_y;
  SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc6_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c6_b_CD_CONSOLE_PRESENT_LOW = sf_mex_dup(c6_mxArrayInData);
  c6_thisId.fIdentifier = (const char *)c6_varName;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_CD_CONSOLE_PRESENT_LOW), &c6_thisId);
  sf_mex_destroy(&c6_b_CD_CONSOLE_PRESENT_LOW);
  *(uint16_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  boolean_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc6_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_u = *(boolean_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static const mxArray *c6_f_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_b_setSimStateSideEffectsInfo, const char_T
  *c6_identifier)
{
  const mxArray *c6_y = NULL;
  emlrtMsgIdentifier c6_thisId;
  c6_y = NULL;
  c6_thisId.fIdentifier = (const char *)c6_identifier;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  sf_mex_assign(&c6_y, c6_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_setSimStateSideEffectsInfo), &c6_thisId), false);
  sf_mex_destroy(&c6_b_setSimStateSideEffectsInfo);
  return c6_y;
}

static const mxArray *c6_g_emlrt_marshallIn(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  const mxArray *c6_y = NULL;
  (void)chartInstance;
  (void)c6_parentId;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_duplicatearraysafe(&c6_u), false);
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static const mxArray *sf_get_hover_data_for_msg
  (SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c6_ssid)
{
  (void)chartInstance;
  (void)c6_ssid;
  return NULL;
}

static void c6_init_sf_message_store_memory(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static uint16_T c6__u16_s32_(SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c6_b, uint32_T c6_ssid_src_loc, int32_T c6_offset_src_loc, int32_T
  c6_length_src_loc)
{
  uint16_T c6_a;
  (void)chartInstance;
  c6_a = (uint16_T)c6_b;
  if (c6_a != c6_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c6_ssid_src_loc, c6_offset_src_loc,
      c6_length_src_loc);
  }

  return c6_a;
}

static int32_T c6__s32_add__(SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c6_b, int32_T c6_c, uint32_T c6_ssid_src_loc, int32_T
  c6_offset_src_loc, int32_T c6_length_src_loc)
{
  int32_T c6_a;
  (void)chartInstance;
  c6_a = c6_b + c6_c;
  if (((c6_a ^ c6_b) & (c6_a ^ c6_c)) < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c6_ssid_src_loc, c6_offset_src_loc,
      c6_length_src_loc);
  }

  return c6_a;
}

static void init_dsm_address_info(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc6_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  chartInstance->c6_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c6_state_Console = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c6_rm_Console = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c6_ain_Console = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c6_state_SensorSupply1 = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 2);
  chartInstance->c6_state_SensorSupply2 = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c6_state_System = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c6_state_MachineLock = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c6_flag_InitEERead = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
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

void sf_c6_MX_Gtwy_Control_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(264866202U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3151014838U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2067991388U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(295096784U);
}

mxArray* sf_c6_MX_Gtwy_Control_get_post_codegen_info(void);
mxArray *sf_c6_MX_Gtwy_Control_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("XUr0aB6ytbqrDp6ICWQVS");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,16,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
    mxArray* mxPostCodegenInfo = sf_c6_MX_Gtwy_Control_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c6_MX_Gtwy_Control_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c6_MX_Gtwy_Control_jit_fallback_info(void)
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

mxArray *sf_c6_MX_Gtwy_Control_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c6_MX_Gtwy_Control_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c6_MX_Gtwy_Control(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[35],T\"state_Console\",},{M[3],M[42],T\"debounceCount\",},{M[8],M[0],T\"is_active_c6_MX_Gtwy_Control\",},{M[9],M[0],T\"is_c6_MX_Gtwy_Control\",},{M[9],M[3],T\"is_NORMAL\",},{M[9],M[11],T\"is_OORH\",},{M[9],M[12],T\"is_OORL\",},{M[9],M[13],T\"is_ABSENT\",},{M[9],M[14],T\"is_PRESENT\",},{M[9],M[15],T\"is_STATE\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 10, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_MX_Gtwy_Control_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc6_MX_Gtwy_ControlInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc6_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MX_Gtwy_ControlMachineNumber_,
           6,
           15,
           19,
           0,
           25,
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
          _SFD_SET_DATA_PROPS(1,1,1,0,"rm_Console");
          _SFD_SET_DATA_PROPS(2,1,1,0,"ain_Console");
          _SFD_SET_DATA_PROPS(3,1,1,0,"state_SensorSupply1");
          _SFD_SET_DATA_PROPS(4,1,1,0,"state_SensorSupply2");
          _SFD_SET_DATA_PROPS(5,1,1,0,"state_System");
          _SFD_SET_DATA_PROPS(6,1,1,0,"state_MachineLock");
          _SFD_SET_DATA_PROPS(7,1,1,0,"flag_InitEERead");
          _SFD_SET_DATA_PROPS(8,2,0,1,"state_Console");
          _SFD_SET_DATA_PROPS(9,10,0,0,"ACTIVE");
          _SFD_SET_DATA_PROPS(10,10,0,0,"CD_CONSOLE_DEBOUNCE_ABSENT");
          _SFD_SET_DATA_PROPS(11,10,0,0,"CD_CONSOLE_DEBOUNCE_OORH");
          _SFD_SET_DATA_PROPS(12,10,0,0,"CD_CONSOLE_DEBOUNCE_OORL");
          _SFD_SET_DATA_PROPS(13,10,0,0,"CD_CONSOLE_DEBOUNCE_PRESENT");
          _SFD_SET_DATA_PROPS(14,10,0,0,"CD_CONSOLE_FUNCTION");
          _SFD_SET_DATA_PROPS(15,10,0,0,"CD_CONSOLE_OORH");
          _SFD_SET_DATA_PROPS(16,10,0,0,"CD_CONSOLE_OORL");
          _SFD_SET_DATA_PROPS(17,10,0,0,"CD_CONSOLE_PRESENT_HIGH");
          _SFD_SET_DATA_PROPS(18,10,0,0,"CD_CONSOLE_PRESENT_LOW");
          _SFD_SET_DATA_PROPS(19,10,0,0,"INACTIVE");
          _SFD_SET_DATA_PROPS(20,10,0,0,"NON_FUNCTIONAL");
          _SFD_SET_DATA_PROPS(21,10,0,0,"NORMAL");
          _SFD_SET_DATA_PROPS(22,10,0,0,"OORH");
          _SFD_SET_DATA_PROPS(23,10,0,0,"OORL");
          _SFD_SET_DATA_PROPS(24,10,0,0,"SYS_NORMAL");
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
          _SFD_CH_SUBSTATE_COUNT(2);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,3);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,9);
          _SFD_ST_SUBSTATE_INDEX(1,2,12);
          _SFD_ST_SUBSTATE_COUNT(2,2);
          _SFD_ST_SUBSTATE_INDEX(2,0,3);
          _SFD_ST_SUBSTATE_INDEX(2,1,6);
          _SFD_ST_SUBSTATE_COUNT(3,2);
          _SFD_ST_SUBSTATE_INDEX(3,0,4);
          _SFD_ST_SUBSTATE_INDEX(3,1,5);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,2);
          _SFD_ST_SUBSTATE_INDEX(6,0,7);
          _SFD_ST_SUBSTATE_INDEX(6,1,8);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,2);
          _SFD_ST_SUBSTATE_INDEX(9,0,10);
          _SFD_ST_SUBSTATE_INDEX(9,1,11);
          _SFD_ST_SUBSTATE_COUNT(10,0);
          _SFD_ST_SUBSTATE_COUNT(11,0);
          _SFD_ST_SUBSTATE_COUNT(12,2);
          _SFD_ST_SUBSTATE_INDEX(12,0,13);
          _SFD_ST_SUBSTATE_INDEX(12,1,14);
          _SFD_ST_SUBSTATE_COUNT(13,0);
          _SFD_ST_SUBSTATE_COUNT(14,0);
        }

        _SFD_CV_INIT_CHART(2,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,2,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(6,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(12,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(13,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(14,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 48, 83 };

          static unsigned int sEndGuardMap[] = { 39, 74, 98 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(4,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 48 };

          static unsigned int sEndRelationalopMap[] = { 39, 74 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 0, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(4,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(15,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(15,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(18,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 3, 40, 71 };

          static unsigned int sEndGuardMap[] = { 31, 61, 100 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -2 };

          _SFD_CV_INIT_TRANS(16,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 3, 40, 71 };

          static unsigned int sEndRelationalopMap[] = { 31, 61, 100 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 2, 1, 1, 2, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(16,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 3, 41, 72 };

          static unsigned int sEndGuardMap[] = { 32, 62, 101 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -2 };

          _SFD_CV_INIT_TRANS(17,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 3, 41, 72 };

          static unsigned int sEndRelationalopMap[] = { 32, 62, 101 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 4, 1, 1, 4, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(17,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 41 };

          static unsigned int sEndGuardMap[] = { 32, 70 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(11,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 41 };

          static unsigned int sEndRelationalopMap[] = { 32, 70 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 5, 0, 5, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(11,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 41 };

          static unsigned int sEndGuardMap[] = { 32, 70 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(13,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 41 };

          static unsigned int sEndRelationalopMap[] = { 32, 70 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 3, 0, 3, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(13,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 46, 91, 129, 167 };

          static unsigned int sEndGuardMap[] = { 37, 82, 120, 158, 194 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2 };

          _SFD_CV_INIT_TRANS(5,5,&(sStartGuardMap[0]),&(sEndGuardMap[0]),9,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 46, 91, 129, 167 };

          static unsigned int sEndRelationalopMap[] = { 37, 82, 120, 158, 194 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 2, 4, 1, 1, 0, 2, 4, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,5,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 48, 94, 132, 170 };

          static unsigned int sEndGuardMap[] = { 38, 85, 123, 161, 199 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3, 4, -3 };

          _SFD_CV_INIT_TRANS(0,5,&(sStartGuardMap[0]),&(sEndGuardMap[0]),9,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 48, 94, 132, 170 };

          static unsigned int sEndRelationalopMap[] = { 38, 85, 123, 161, 199 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 5, 3, 0, 0, 0, 5, 3, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(0,5,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 54 };

          static unsigned int sEndGuardMap[] = { 45, 79 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(8,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 54 };

          static unsigned int sEndRelationalopMap[] = { 45, 79 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 5, 0, 5, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(8,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 55 };

          static unsigned int sEndGuardMap[] = { 46, 78 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(6,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 55 };

          static unsigned int sEndRelationalopMap[] = { 46, 78 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 5, 0, 5, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(6,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(10,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 43 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(9,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 43 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(9,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 43 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(14,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 43 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(14,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)c6_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)c6_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)c6_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)c6_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)c6_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)c6_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)c6_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)c6_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)c6_b_sf_marshallIn);
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
    SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc6_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c6_state_Console);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c6_rm_Console);
        _SFD_SET_DATA_VALUE_PTR(18U, (void *)
          &chartInstance->c6_CD_CONSOLE_PRESENT_LOW);
        _SFD_SET_DATA_VALUE_PTR(17U, (void *)
          &chartInstance->c6_CD_CONSOLE_PRESENT_HIGH);
        _SFD_SET_DATA_VALUE_PTR(14U, (void *)
          &chartInstance->c6_CD_CONSOLE_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(13U, (void *)
          &chartInstance->c6_CD_CONSOLE_DEBOUNCE_PRESENT);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)
          &chartInstance->c6_CD_CONSOLE_DEBOUNCE_ABSENT);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)&chartInstance->c6_debounceCount);
        _SFD_SET_DATA_VALUE_PTR(15U, (void *)&chartInstance->c6_CD_CONSOLE_OORH);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)
          &chartInstance->c6_CD_CONSOLE_DEBOUNCE_OORH);
        _SFD_SET_DATA_VALUE_PTR(16U, (void *)&chartInstance->c6_CD_CONSOLE_OORL);
        _SFD_SET_DATA_VALUE_PTR(12U, (void *)
          &chartInstance->c6_CD_CONSOLE_DEBOUNCE_OORL);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c6_ain_Console);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)
          chartInstance->c6_state_SensorSupply1);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)&chartInstance->c6_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(19U, (void *)&chartInstance->c6_INACTIVE);
        _SFD_SET_DATA_VALUE_PTR(22U, (void *)&chartInstance->c6_OORH);
        _SFD_SET_DATA_VALUE_PTR(23U, (void *)&chartInstance->c6_OORL);
        _SFD_SET_DATA_VALUE_PTR(20U, (void *)&chartInstance->c6_NON_FUNCTIONAL);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)
          chartInstance->c6_state_SensorSupply2);
        _SFD_SET_DATA_VALUE_PTR(21U, (void *)&chartInstance->c6_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c6_state_System);
        _SFD_SET_DATA_VALUE_PTR(24U, (void *)&chartInstance->c6_SYS_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c6_state_MachineLock);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c6_flag_InitEERead);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sI3MHraxPC4qQUXHVeztKnG";
}

static void sf_opaque_initialize_c6_MX_Gtwy_Control(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c6_MX_Gtwy_Control((SFc6_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
  initialize_c6_MX_Gtwy_Control((SFc6_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c6_MX_Gtwy_Control(void *chartInstanceVar)
{
  enable_c6_MX_Gtwy_Control((SFc6_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c6_MX_Gtwy_Control(void *chartInstanceVar)
{
  disable_c6_MX_Gtwy_Control((SFc6_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c6_MX_Gtwy_Control(void *chartInstanceVar)
{
  sf_gateway_c6_MX_Gtwy_Control((SFc6_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c6_MX_Gtwy_Control(SimStruct* S)
{
  return get_sim_state_c6_MX_Gtwy_Control((SFc6_MX_Gtwy_ControlInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c6_MX_Gtwy_Control(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c6_MX_Gtwy_Control((SFc6_MX_Gtwy_ControlInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c6_MX_Gtwy_Control(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_MX_Gtwy_ControlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MX_Gtwy_Control_optimization_info();
    }

    finalize_c6_MX_Gtwy_Control((SFc6_MX_Gtwy_ControlInstanceStruct*)
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
  initSimStructsc6_MX_Gtwy_Control((SFc6_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_MX_Gtwy_Control(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c6_MX_Gtwy_Control((SFc6_MX_Gtwy_ControlInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c6_MX_Gtwy_Control(SimStruct *S)
{
  /* Actual parameters from chart:
     ACTIVE CD_CONSOLE_DEBOUNCE_ABSENT CD_CONSOLE_DEBOUNCE_OORH CD_CONSOLE_DEBOUNCE_OORL CD_CONSOLE_DEBOUNCE_PRESENT CD_CONSOLE_FUNCTION CD_CONSOLE_OORH CD_CONSOLE_OORL CD_CONSOLE_PRESENT_HIGH CD_CONSOLE_PRESENT_LOW INACTIVE NON_FUNCTIONAL NORMAL OORH OORL SYS_NORMAL
   */
  const char_T *rtParamNames[] = { "ACTIVE", "CD_CONSOLE_DEBOUNCE_ABSENT",
    "CD_CONSOLE_DEBOUNCE_OORH", "CD_CONSOLE_DEBOUNCE_OORL",
    "CD_CONSOLE_DEBOUNCE_PRESENT", "CD_CONSOLE_FUNCTION", "CD_CONSOLE_OORH",
    "CD_CONSOLE_OORL", "CD_CONSOLE_PRESENT_HIGH", "CD_CONSOLE_PRESENT_LOW",
    "INACTIVE", "NON_FUNCTIONAL", "NORMAL", "OORH", "OORL", "SYS_NORMAL" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_UINT8);

  /* registration for CD_CONSOLE_DEBOUNCE_ABSENT*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT16);

  /* registration for CD_CONSOLE_DEBOUNCE_OORH*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT16);

  /* registration for CD_CONSOLE_DEBOUNCE_OORL*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_UINT16);

  /* registration for CD_CONSOLE_DEBOUNCE_PRESENT*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_UINT16);

  /* registration for CD_CONSOLE_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_UINT8);

  /* registration for CD_CONSOLE_OORH*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_UINT16);

  /* registration for CD_CONSOLE_OORL*/
  ssRegDlgParamAsRunTimeParam(S, 7, 7, rtParamNames[7], SS_UINT16);

  /* registration for CD_CONSOLE_PRESENT_HIGH*/
  ssRegDlgParamAsRunTimeParam(S, 8, 8, rtParamNames[8], SS_UINT16);

  /* registration for CD_CONSOLE_PRESENT_LOW*/
  ssRegDlgParamAsRunTimeParam(S, 9, 9, rtParamNames[9], SS_UINT16);

  /* registration for INACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 10, 10, rtParamNames[10], SS_UINT8);

  /* registration for NON_FUNCTIONAL*/
  ssRegDlgParamAsRunTimeParam(S, 11, 11, rtParamNames[11], SS_UINT8);

  /* registration for NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 12, 12, rtParamNames[12], SS_UINT8);

  /* registration for OORH*/
  ssRegDlgParamAsRunTimeParam(S, 13, 13, rtParamNames[13], SS_UINT8);

  /* registration for OORL*/
  ssRegDlgParamAsRunTimeParam(S, 14, 14, rtParamNames[14], SS_UINT8);

  /* registration for SYS_NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 15, 15, rtParamNames[15], SS_UINT8);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetInputPortDirectFeedThrough(S, 4, 1);
  ssSetInputPortDirectFeedThrough(S, 5, 1);
  ssSetInputPortDirectFeedThrough(S, 6, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MX_Gtwy_Control_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,6,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 6);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,6);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,7);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 7; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(432004679U));
  ssSetChecksum1(S,(261000958U));
  ssSetChecksum2(S,(2235979493U));
  ssSetChecksum3(S,(1289844288U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c6_MX_Gtwy_Control(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c6_MX_Gtwy_Control(SimStruct *S)
{
  SFc6_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc6_MX_Gtwy_ControlInstanceStruct *)utMalloc(sizeof
    (SFc6_MX_Gtwy_ControlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc6_MX_Gtwy_ControlInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c6_MX_Gtwy_Control;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c6_MX_Gtwy_Control;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c6_MX_Gtwy_Control;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_MX_Gtwy_Control;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c6_MX_Gtwy_Control;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c6_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c6_MX_Gtwy_Control;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c6_MX_Gtwy_Control;
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
  mdl_start_c6_MX_Gtwy_Control(chartInstance);
}

void c6_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_MX_Gtwy_Control(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_MX_Gtwy_Control_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
