/* Include files */

#include "MX_Gateway_sfun.h"
#include "c63_MX_Gateway.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "MX_Gateway_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c63_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)
#define c63_IN_ECU                     ((uint8_T)1U)
#define c63_IN_NO_ECU                  ((uint8_T)2U)
#define c63_IN_DERATE                  ((uint8_T)1U)
#define c63_IN_DISABLE_DERATE          ((uint8_T)2U)
#define c63_IN_NON_FUNCTIONAL          ((uint8_T)3U)
#define c63_IN_NORMAL                  ((uint8_T)4U)
#define c63_b_IN_NORMAL                ((uint8_T)1U)
#define c63_IN_SHUTDOWN                ((uint8_T)2U)
#define c63_IN_UNRESPONSIVE            ((uint8_T)3U)
#define c63_IN_DEBOUNCE                ((uint8_T)1U)
#define c63_b_IN_UNRESPONSIVE          ((uint8_T)2U)
#define c63_IN_Cranking                ((uint8_T)1U)
#define c63_b_IN_DERATE                ((uint8_T)2U)
#define c63_IN_REQUEST_RECEIVED        ((uint8_T)4U)
#define c63_IN_SEND_REQUEST            ((uint8_T)5U)
#define c63_IN_SEND_MESSAGE            ((uint8_T)1U)
#define c63_IN_WAIT_FOR_RESPONSE       ((uint8_T)2U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static void initialize_params_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static void enable_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct *chartInstance);
static void disable_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct *chartInstance);
static void c63_update_debugger_state_c63_MX_Gateway
  (SFc63_MX_GatewayInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c63_MX_Gateway
  (SFc63_MX_GatewayInstanceStruct *chartInstance);
static void set_sim_state_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_st);
static void c63_set_sim_state_side_effects_c63_MX_Gateway
  (SFc63_MX_GatewayInstanceStruct *chartInstance);
static void finalize_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static void sf_gateway_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static void mdl_start_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static void c63_chartstep_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static void initSimStructsc63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static void c63_RPM_FAULT(SFc63_MX_GatewayInstanceStruct *chartInstance);
static void c63_exit_internal_UNRESPONSIVE(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static void c63_exit_internal_SHUTDOWN(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static void c63_HP_MATCH(SFc63_MX_GatewayInstanceStruct *chartInstance);
static void c63_exit_internal_SEND_REQUEST(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c63_machineNumber, uint32_T
  c63_chartNumber, uint32_T c63_instanceNumber);
static const mxArray *c63_sf_marshallOut(void *chartInstanceVoid, void
  *c63_inData);
static int32_T c63_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_u, const emlrtMsgIdentifier *c63_parentId);
static void c63_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c63_mxArrayInData, const char_T *c63_varName, void *c63_outData);
static const mxArray *c63_b_sf_marshallOut(void *chartInstanceVoid, void
  *c63_inData);
static uint8_T c63_b_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_b_tp_ECU, const char_T *c63_identifier);
static uint8_T c63_c_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_u, const emlrtMsgIdentifier *c63_parentId);
static void c63_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c63_mxArrayInData, const char_T *c63_varName, void *c63_outData);
static const mxArray *c63_c_sf_marshallOut(void *chartInstanceVoid, void
  *c63_inData);
static int8_T c63_d_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_b_percent_Derate, const char_T
  *c63_identifier);
static int8_T c63_e_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_u, const emlrtMsgIdentifier *c63_parentId);
static void c63_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c63_mxArrayInData, const char_T *c63_varName, void *c63_outData);
static const mxArray *c63_d_sf_marshallOut(void *chartInstanceVoid, void
  *c63_inData);
static uint16_T c63_f_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_b_rpm_Derate, const char_T *c63_identifier);
static uint16_T c63_g_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_u, const emlrtMsgIdentifier *c63_parentId);
static void c63_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c63_mxArrayInData, const char_T *c63_varName, void *c63_outData);
static const mxArray *c63_h_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_b_setSimStateSideEffectsInfo, const char_T *
  c63_identifier);
static const mxArray *c63_i_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_u, const emlrtMsgIdentifier *c63_parentId);
static const mxArray *sf_get_hover_data_for_msg(SFc63_MX_GatewayInstanceStruct
  *chartInstance, int32_T c63_ssid);
static void c63_init_sf_message_store_memory(SFc63_MX_GatewayInstanceStruct
  *chartInstance);
static int32_T c63_div_nzp_s32(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int32_T c63_numerator, int32_T c63_denominator, uint32_T c63_ssid_src_loc,
  int32_T c63_offset_src_loc, int32_T c63_length_src_loc);
static uint16_T c63__u16_u32_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc);
static uint32_T c63__u32_add__(SFc63_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c63_b, uint32_T c63_c, uint32_T c63_ssid_src_loc, int32_T
  c63_offset_src_loc, int32_T c63_length_src_loc);
static uint32_T c63__u32d_div__(SFc63_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c63_b, uint32_T c63_c, uint32_T c63_ssid_src_loc, int32_T
  c63_offset_src_loc, int32_T c63_length_src_loc);
static uint32_T c63__u32_u64_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  uint64_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc);
static uint32_T c63__u32_s32_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int32_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc);
static uint32_T c63__u32_s8_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int8_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc);
static uint16_T c63__u16_s32_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int32_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc);
static int32_T c63__s32_u32_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc);
static uint16_T c63__u16_s8_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int8_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc);
static int8_T c63__s8_u8_(SFc63_MX_GatewayInstanceStruct *chartInstance, uint8_T
  c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc);
static int32_T c63__s32_add__(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int32_T c63_b, int32_T c63_c, uint32_T c63_ssid_src_loc, int32_T
  c63_offset_src_loc, int32_T c63_length_src_loc);
static uint8_T c63__u8_s32_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int32_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc);
static void init_dsm_address_info(SFc63_MX_GatewayInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc63_MX_GatewayInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc63_MX_Gateway(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c63_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c63_doSetSimStateSideEffects = 0U;
  chartInstance->c63_setSimStateSideEffectsInfo = NULL;
  chartInstance->c63_tp_ECU = 0U;
  chartInstance->c63_is_active_DERATE_LEVEL = 0U;
  chartInstance->c63_tp_DERATE_LEVEL = 0U;
  chartInstance->c63_is_active_HP_MATCH = 0U;
  chartInstance->c63_is_HP_MATCH = c63_IN_NO_ACTIVE_CHILD;
  chartInstance->c63_tp_HP_MATCH = 0U;
  chartInstance->c63_tp_Cranking = 0U;
  chartInstance->c63_b_tp_DERATE = 0U;
  chartInstance->c63_b_tp_NON_FUNCTIONAL = 0U;
  chartInstance->c63_tp_REQUEST_RECEIVED = 0U;
  chartInstance->c63_is_SEND_REQUEST = c63_IN_NO_ACTIVE_CHILD;
  chartInstance->c63_tp_SEND_REQUEST = 0U;
  chartInstance->c63_tp_SEND_MESSAGE = 0U;
  chartInstance->c63_tp_WAIT_FOR_RESPONSE = 0U;
  chartInstance->c63_is_active_RPM_FAULT = 0U;
  chartInstance->c63_is_RPM_FAULT = c63_IN_NO_ACTIVE_CHILD;
  chartInstance->c63_tp_RPM_FAULT = 0U;
  chartInstance->c63_b_tp_NORMAL = 0U;
  chartInstance->c63_is_SHUTDOWN = c63_IN_NO_ACTIVE_CHILD;
  chartInstance->c63_tp_SHUTDOWN = 0U;
  chartInstance->c63_b_tp_DEBOUNCE = 0U;
  chartInstance->c63_b_tp_SHUTDOWN = 0U;
  chartInstance->c63_is_UNRESPONSIVE = c63_IN_NO_ACTIVE_CHILD;
  chartInstance->c63_tp_UNRESPONSIVE = 0U;
  chartInstance->c63_tp_DEBOUNCE = 0U;
  chartInstance->c63_b_tp_UNRESPONSIVE = 0U;
  chartInstance->c63_is_active_SEND_MSG = 0U;
  chartInstance->c63_is_SEND_MSG = c63_IN_NO_ACTIVE_CHILD;
  chartInstance->c63_tp_SEND_MSG = 0U;
  chartInstance->c63_tp_DERATE = 0U;
  chartInstance->c63_tp_DISABLE_DERATE = 0U;
  chartInstance->c63_tp_NON_FUNCTIONAL = 0U;
  chartInstance->c63_tp_NORMAL = 0U;
  chartInstance->c63_tp_NO_ECU = 0U;
  chartInstance->c63_is_active_c63_MX_Gateway = 0U;
  chartInstance->c63_is_c63_MX_Gateway = c63_IN_NO_ACTIVE_CHILD;
  chartInstance->c63_debounceCount = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_debounceCount, 0U);
  chartInstance->c63_derate_HPMatch = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_derate_HPMatch, 2U);
  chartInstance->c63_num_Trys = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_num_Trys, 3U);
  chartInstance->c63_debounceRequest = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_debounceRequest, 1U);
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c63_percent_Derate = 0;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_percent_Derate, 13U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c63_rpm_Derate = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_rpm_Derate, 14U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *chartInstance->c63_state_EngineSpeedDerate = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_state_EngineSpeedDerate,
                          15U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 4) != 0)) {
    *chartInstance->c63_state_HPMatch = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_state_HPMatch, 16U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 5) != 0)) {
    *chartInstance->c63_torque_Derate = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_torque_Derate, 17U);
  }
}

static void initialize_params_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  real_T c63_d0;
  real_T c63_d1;
  real_T c63_d2;
  real_T c63_d3;
  real_T c63_d4;
  real_T c63_d5;
  real_T c63_d6;
  real_T c63_d7;
  real_T c63_d8;
  real_T c63_d9;
  real_T c63_d10;
  real_T c63_d11;
  real_T c63_d12;
  real_T c63_d13;
  real_T c63_d14;
  real_T c63_d15;
  sf_mex_import_named("NON_FUNCTIONAL", sf_mex_get_sfun_param(chartInstance->S,
    11, 0), &c63_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_NON_FUNCTIONAL = (uint8_T)c63_d0;
  sf_mex_import_named("CD_ECU_FUNCTION", sf_mex_get_sfun_param(chartInstance->S,
    5, 0), &c63_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_CD_ECU_FUNCTION = (uint8_T)c63_d1;
  sf_mex_import_named("SHUTDOWN", sf_mex_get_sfun_param(chartInstance->S, 13, 0),
                      &c63_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_SHUTDOWN = (uint8_T)c63_d2;
  sf_mex_import_named("NORMAL", sf_mex_get_sfun_param(chartInstance->S, 12, 0),
                      &c63_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_NORMAL = (uint8_T)c63_d3;
  sf_mex_import_named("CD_DERATE_ENGINE_SPEED_HIGH_OFFSET",
                      sf_mex_get_sfun_param(chartInstance->S, 3, 0), &c63_d4, 0,
                      0, 0U, 0, 0U, 0);
  chartInstance->c63_CD_DERATE_ENGINE_SPEED_HIGH_OFFSET = (uint16_T)c63_d4;
  sf_mex_import_named("CD_DERATE_ENGINE_SPEED_DEBOUNCE_HIGH",
                      sf_mex_get_sfun_param(chartInstance->S, 1, 0), &c63_d5, 0,
                      0, 0U, 0, 0U, 0);
  chartInstance->c63_CD_DERATE_ENGINE_SPEED_DEBOUNCE_HIGH = (uint16_T)c63_d5;
  sf_mex_import_named("CD_DERATE_ENGINE_SPEED_DEBOUNCE_SHUTDOWN",
                      sf_mex_get_sfun_param(chartInstance->S, 2, 0), &c63_d6, 0,
                      0, 0U, 0, 0U, 0);
  chartInstance->c63_CD_DERATE_ENGINE_SPEED_DEBOUNCE_SHUTDOWN = (uint16_T)c63_d6;
  sf_mex_import_named("UNRESPONSIVE", sf_mex_get_sfun_param(chartInstance->S, 15,
    0), &c63_d7, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_UNRESPONSIVE = (uint8_T)c63_d7;
  sf_mex_import_named("CD_HP_MATCH_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 6, 0), &c63_d8, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_CD_HP_MATCH_FUNCTION = (uint8_T)c63_d8;
  sf_mex_import_named("UNDEFINED", sf_mex_get_sfun_param(chartInstance->S, 14, 0),
                      &c63_d9, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_UNDEFINED = (uint8_T)c63_d9;
  sf_mex_import_named("CD_MACHINE_HP", sf_mex_get_sfun_param(chartInstance->S, 7,
    0), &c63_d10, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_CD_MACHINE_HP = (uint8_T)c63_d10;
  sf_mex_import_named("ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c63_d11, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_ACTIVE = (uint8_T)c63_d11;
  sf_mex_import_named("CD_MATCH_DERATE_PERCENT", sf_mex_get_sfun_param
                      (chartInstance->S, 8, 0), &c63_d12, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_CD_MATCH_DERATE_PERCENT = (uint8_T)c63_d12;
  sf_mex_import_named("FAILURE", sf_mex_get_sfun_param(chartInstance->S, 10, 0),
                      &c63_d13, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_FAILURE = (uint8_T)c63_d13;
  sf_mex_import_named("ENGINE_CRANKING", sf_mex_get_sfun_param(chartInstance->S,
    9, 0), &c63_d14, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_ENGINE_CRANKING = (uint8_T)c63_d14;
  sf_mex_import_named("CD_DERATE_METHOD", sf_mex_get_sfun_param(chartInstance->S,
    4, 0), &c63_d15, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c63_CD_DERATE_METHOD = (uint8_T)c63_d15;
}

static void enable_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c63_update_debugger_state_c63_MX_Gateway
  (SFc63_MX_GatewayInstanceStruct *chartInstance)
{
  uint32_T c63_prevAniVal;
  c63_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c63_is_active_c63_MX_Gateway == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 61U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_c63_MX_Gateway == c63_IN_ECU) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_active_DERATE_LEVEL == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_active_SEND_MSG == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_SEND_MSG == c63_IN_NON_FUNCTIONAL) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_SEND_MSG == c63_IN_NORMAL) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_SEND_MSG == c63_IN_DERATE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_SEND_MSG == c63_IN_DISABLE_DERATE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_active_RPM_FAULT == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_RPM_FAULT == c63_IN_UNRESPONSIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_UNRESPONSIVE == c63_b_IN_UNRESPONSIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_UNRESPONSIVE == c63_IN_DEBOUNCE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_RPM_FAULT == c63_b_IN_NORMAL) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_RPM_FAULT == c63_IN_SHUTDOWN) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_SHUTDOWN == c63_IN_SHUTDOWN) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_SHUTDOWN == c63_IN_DEBOUNCE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_active_HP_MATCH == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_HP_MATCH == c63_IN_NON_FUNCTIONAL) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_HP_MATCH == c63_IN_SEND_REQUEST) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_SEND_REQUEST == c63_IN_SEND_MESSAGE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_SEND_REQUEST == c63_IN_WAIT_FOR_RESPONSE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_HP_MATCH == c63_IN_REQUEST_RECEIVED) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_HP_MATCH == c63_IN_Cranking) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_HP_MATCH == c63_b_IN_DERATE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c63_sfEvent);
  }

  if (chartInstance->c63_is_c63_MX_Gateway == c63_IN_NO_ECU) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c63_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c63_sfEvent);
  }

  _SFD_SET_ANIMATION(c63_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c63_MX_Gateway
  (SFc63_MX_GatewayInstanceStruct *chartInstance)
{
  const mxArray *c63_st;
  const mxArray *c63_y = NULL;
  int8_T c63_hoistedGlobal;
  const mxArray *c63_b_y = NULL;
  uint16_T c63_b_hoistedGlobal;
  const mxArray *c63_c_y = NULL;
  uint8_T c63_c_hoistedGlobal;
  const mxArray *c63_d_y = NULL;
  uint8_T c63_d_hoistedGlobal;
  const mxArray *c63_e_y = NULL;
  uint16_T c63_e_hoistedGlobal;
  const mxArray *c63_f_y = NULL;
  uint16_T c63_f_hoistedGlobal;
  const mxArray *c63_g_y = NULL;
  uint16_T c63_g_hoistedGlobal;
  const mxArray *c63_h_y = NULL;
  uint8_T c63_h_hoistedGlobal;
  const mxArray *c63_i_y = NULL;
  uint8_T c63_i_hoistedGlobal;
  const mxArray *c63_j_y = NULL;
  uint8_T c63_j_hoistedGlobal;
  const mxArray *c63_k_y = NULL;
  uint8_T c63_k_hoistedGlobal;
  const mxArray *c63_l_y = NULL;
  uint8_T c63_l_hoistedGlobal;
  const mxArray *c63_m_y = NULL;
  uint8_T c63_m_hoistedGlobal;
  const mxArray *c63_n_y = NULL;
  uint8_T c63_n_hoistedGlobal;
  const mxArray *c63_o_y = NULL;
  uint8_T c63_o_hoistedGlobal;
  const mxArray *c63_p_y = NULL;
  uint8_T c63_p_hoistedGlobal;
  const mxArray *c63_q_y = NULL;
  uint8_T c63_q_hoistedGlobal;
  const mxArray *c63_r_y = NULL;
  uint8_T c63_r_hoistedGlobal;
  const mxArray *c63_s_y = NULL;
  uint8_T c63_s_hoistedGlobal;
  const mxArray *c63_t_y = NULL;
  uint8_T c63_t_hoistedGlobal;
  const mxArray *c63_u_y = NULL;
  uint8_T c63_u_hoistedGlobal;
  const mxArray *c63_v_y = NULL;
  c63_st = NULL;
  c63_st = NULL;
  c63_y = NULL;
  sf_mex_assign(&c63_y, sf_mex_createcellmatrix(21, 1), false);
  c63_hoistedGlobal = *chartInstance->c63_percent_Derate;
  c63_b_y = NULL;
  sf_mex_assign(&c63_b_y, sf_mex_create("y", &c63_hoistedGlobal, 2, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 0, c63_b_y);
  c63_b_hoistedGlobal = *chartInstance->c63_rpm_Derate;
  c63_c_y = NULL;
  sf_mex_assign(&c63_c_y, sf_mex_create("y", &c63_b_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 1, c63_c_y);
  c63_c_hoistedGlobal = *chartInstance->c63_state_EngineSpeedDerate;
  c63_d_y = NULL;
  sf_mex_assign(&c63_d_y, sf_mex_create("y", &c63_c_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 2, c63_d_y);
  c63_d_hoistedGlobal = *chartInstance->c63_state_HPMatch;
  c63_e_y = NULL;
  sf_mex_assign(&c63_e_y, sf_mex_create("y", &c63_d_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 3, c63_e_y);
  c63_e_hoistedGlobal = *chartInstance->c63_torque_Derate;
  c63_f_y = NULL;
  sf_mex_assign(&c63_f_y, sf_mex_create("y", &c63_e_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 4, c63_f_y);
  c63_f_hoistedGlobal = chartInstance->c63_debounceCount;
  c63_g_y = NULL;
  sf_mex_assign(&c63_g_y, sf_mex_create("y", &c63_f_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 5, c63_g_y);
  c63_g_hoistedGlobal = chartInstance->c63_debounceRequest;
  c63_h_y = NULL;
  sf_mex_assign(&c63_h_y, sf_mex_create("y", &c63_g_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 6, c63_h_y);
  c63_h_hoistedGlobal = chartInstance->c63_derate_HPMatch;
  c63_i_y = NULL;
  sf_mex_assign(&c63_i_y, sf_mex_create("y", &c63_h_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 7, c63_i_y);
  c63_i_hoistedGlobal = chartInstance->c63_num_Trys;
  c63_j_y = NULL;
  sf_mex_assign(&c63_j_y, sf_mex_create("y", &c63_i_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 8, c63_j_y);
  c63_j_hoistedGlobal = chartInstance->c63_is_active_c63_MX_Gateway;
  c63_k_y = NULL;
  sf_mex_assign(&c63_k_y, sf_mex_create("y", &c63_j_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 9, c63_k_y);
  c63_k_hoistedGlobal = chartInstance->c63_is_active_DERATE_LEVEL;
  c63_l_y = NULL;
  sf_mex_assign(&c63_l_y, sf_mex_create("y", &c63_k_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 10, c63_l_y);
  c63_l_hoistedGlobal = chartInstance->c63_is_active_SEND_MSG;
  c63_m_y = NULL;
  sf_mex_assign(&c63_m_y, sf_mex_create("y", &c63_l_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 11, c63_m_y);
  c63_m_hoistedGlobal = chartInstance->c63_is_active_RPM_FAULT;
  c63_n_y = NULL;
  sf_mex_assign(&c63_n_y, sf_mex_create("y", &c63_m_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 12, c63_n_y);
  c63_n_hoistedGlobal = chartInstance->c63_is_active_HP_MATCH;
  c63_o_y = NULL;
  sf_mex_assign(&c63_o_y, sf_mex_create("y", &c63_n_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 13, c63_o_y);
  c63_o_hoistedGlobal = chartInstance->c63_is_c63_MX_Gateway;
  c63_p_y = NULL;
  sf_mex_assign(&c63_p_y, sf_mex_create("y", &c63_o_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 14, c63_p_y);
  c63_p_hoistedGlobal = chartInstance->c63_is_SEND_MSG;
  c63_q_y = NULL;
  sf_mex_assign(&c63_q_y, sf_mex_create("y", &c63_p_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 15, c63_q_y);
  c63_q_hoistedGlobal = chartInstance->c63_is_RPM_FAULT;
  c63_r_y = NULL;
  sf_mex_assign(&c63_r_y, sf_mex_create("y", &c63_q_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 16, c63_r_y);
  c63_r_hoistedGlobal = chartInstance->c63_is_UNRESPONSIVE;
  c63_s_y = NULL;
  sf_mex_assign(&c63_s_y, sf_mex_create("y", &c63_r_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 17, c63_s_y);
  c63_s_hoistedGlobal = chartInstance->c63_is_SHUTDOWN;
  c63_t_y = NULL;
  sf_mex_assign(&c63_t_y, sf_mex_create("y", &c63_s_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 18, c63_t_y);
  c63_t_hoistedGlobal = chartInstance->c63_is_HP_MATCH;
  c63_u_y = NULL;
  sf_mex_assign(&c63_u_y, sf_mex_create("y", &c63_t_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 19, c63_u_y);
  c63_u_hoistedGlobal = chartInstance->c63_is_SEND_REQUEST;
  c63_v_y = NULL;
  sf_mex_assign(&c63_v_y, sf_mex_create("y", &c63_u_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c63_y, 20, c63_v_y);
  sf_mex_assign(&c63_st, c63_y, false);
  return c63_st;
}

static void set_sim_state_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_st)
{
  const mxArray *c63_u;
  c63_u = sf_mex_dup(c63_st);
  *chartInstance->c63_percent_Derate = c63_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 0)), "percent_Derate");
  *chartInstance->c63_rpm_Derate = c63_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 1)), "rpm_Derate");
  *chartInstance->c63_state_EngineSpeedDerate = c63_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c63_u, 2)),
     "state_EngineSpeedDerate");
  *chartInstance->c63_state_HPMatch = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 3)), "state_HPMatch");
  *chartInstance->c63_torque_Derate = c63_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 4)), "torque_Derate");
  chartInstance->c63_debounceCount = c63_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 5)), "debounceCount");
  chartInstance->c63_debounceRequest = c63_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 6)), "debounceRequest");
  chartInstance->c63_derate_HPMatch = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 7)), "derate_HPMatch");
  chartInstance->c63_num_Trys = c63_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c63_u, 8)), "num_Trys");
  chartInstance->c63_is_active_c63_MX_Gateway = c63_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c63_u, 9)),
     "is_active_c63_MX_Gateway");
  chartInstance->c63_is_active_DERATE_LEVEL = c63_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c63_u, 10)),
     "is_active_DERATE_LEVEL");
  chartInstance->c63_is_active_SEND_MSG = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 11)), "is_active_SEND_MSG");
  chartInstance->c63_is_active_RPM_FAULT = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 12)), "is_active_RPM_FAULT");
  chartInstance->c63_is_active_HP_MATCH = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 13)), "is_active_HP_MATCH");
  chartInstance->c63_is_c63_MX_Gateway = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 14)), "is_c63_MX_Gateway");
  chartInstance->c63_is_SEND_MSG = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 15)), "is_SEND_MSG");
  chartInstance->c63_is_RPM_FAULT = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 16)), "is_RPM_FAULT");
  chartInstance->c63_is_UNRESPONSIVE = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 17)), "is_UNRESPONSIVE");
  chartInstance->c63_is_SHUTDOWN = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 18)), "is_SHUTDOWN");
  chartInstance->c63_is_HP_MATCH = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 19)), "is_HP_MATCH");
  chartInstance->c63_is_SEND_REQUEST = c63_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c63_u, 20)), "is_SEND_REQUEST");
  sf_mex_assign(&chartInstance->c63_setSimStateSideEffectsInfo,
                c63_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c63_u, 21)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c63_u);
  chartInstance->c63_doSetSimStateSideEffects = 1U;
  c63_update_debugger_state_c63_MX_Gateway(chartInstance);
  sf_mex_destroy(&c63_st);
}

static void c63_set_sim_state_side_effects_c63_MX_Gateway
  (SFc63_MX_GatewayInstanceStruct *chartInstance)
{
  if (chartInstance->c63_doSetSimStateSideEffects != 0) {
    chartInstance->c63_tp_ECU = (uint8_T)(chartInstance->c63_is_c63_MX_Gateway ==
      c63_IN_ECU);
    chartInstance->c63_tp_DERATE_LEVEL = (uint8_T)
      (chartInstance->c63_is_active_DERATE_LEVEL == 1U);
    chartInstance->c63_tp_SEND_MSG = (uint8_T)
      (chartInstance->c63_is_active_SEND_MSG == 1U);
    chartInstance->c63_tp_DERATE = (uint8_T)(chartInstance->c63_is_SEND_MSG ==
      c63_IN_DERATE);
    chartInstance->c63_tp_DISABLE_DERATE = (uint8_T)
      (chartInstance->c63_is_SEND_MSG == c63_IN_DISABLE_DERATE);
    chartInstance->c63_tp_NON_FUNCTIONAL = (uint8_T)
      (chartInstance->c63_is_SEND_MSG == c63_IN_NON_FUNCTIONAL);
    chartInstance->c63_tp_NORMAL = (uint8_T)(chartInstance->c63_is_SEND_MSG ==
      c63_IN_NORMAL);
    chartInstance->c63_tp_RPM_FAULT = (uint8_T)
      (chartInstance->c63_is_active_RPM_FAULT == 1U);
    chartInstance->c63_b_tp_NORMAL = (uint8_T)(chartInstance->c63_is_RPM_FAULT ==
      c63_b_IN_NORMAL);
    chartInstance->c63_tp_SHUTDOWN = (uint8_T)(chartInstance->c63_is_RPM_FAULT ==
      c63_IN_SHUTDOWN);
    chartInstance->c63_b_tp_DEBOUNCE = (uint8_T)(chartInstance->c63_is_SHUTDOWN ==
      c63_IN_DEBOUNCE);
    chartInstance->c63_b_tp_SHUTDOWN = (uint8_T)(chartInstance->c63_is_SHUTDOWN ==
      c63_IN_SHUTDOWN);
    chartInstance->c63_tp_UNRESPONSIVE = (uint8_T)
      (chartInstance->c63_is_RPM_FAULT == c63_IN_UNRESPONSIVE);
    chartInstance->c63_tp_DEBOUNCE = (uint8_T)
      (chartInstance->c63_is_UNRESPONSIVE == c63_IN_DEBOUNCE);
    chartInstance->c63_b_tp_UNRESPONSIVE = (uint8_T)
      (chartInstance->c63_is_UNRESPONSIVE == c63_b_IN_UNRESPONSIVE);
    chartInstance->c63_tp_HP_MATCH = (uint8_T)
      (chartInstance->c63_is_active_HP_MATCH == 1U);
    chartInstance->c63_tp_Cranking = (uint8_T)(chartInstance->c63_is_HP_MATCH ==
      c63_IN_Cranking);
    chartInstance->c63_b_tp_DERATE = (uint8_T)(chartInstance->c63_is_HP_MATCH ==
      c63_b_IN_DERATE);
    chartInstance->c63_b_tp_NON_FUNCTIONAL = (uint8_T)
      (chartInstance->c63_is_HP_MATCH == c63_IN_NON_FUNCTIONAL);
    chartInstance->c63_tp_REQUEST_RECEIVED = (uint8_T)
      (chartInstance->c63_is_HP_MATCH == c63_IN_REQUEST_RECEIVED);
    chartInstance->c63_tp_SEND_REQUEST = (uint8_T)
      (chartInstance->c63_is_HP_MATCH == c63_IN_SEND_REQUEST);
    chartInstance->c63_tp_SEND_MESSAGE = (uint8_T)
      (chartInstance->c63_is_SEND_REQUEST == c63_IN_SEND_MESSAGE);
    chartInstance->c63_tp_WAIT_FOR_RESPONSE = (uint8_T)
      (chartInstance->c63_is_SEND_REQUEST == c63_IN_WAIT_FOR_RESPONSE);
    chartInstance->c63_tp_NO_ECU = (uint8_T)
      (chartInstance->c63_is_c63_MX_Gateway == c63_IN_NO_ECU);
    chartInstance->c63_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c63_setSimStateSideEffectsInfo);
}

static void sf_gateway_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  c63_set_sim_state_side_effects_c63_MX_Gateway(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 61U, chartInstance->c63_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_state_Engine, 12U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_ecu_HP, 11U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_state_ECUHold, 10U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_state_CommECU, 9U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_derate_Throttle, 8U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_ecu_isocMaxRPM, 7U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_ecu_isocMinRPM, 6U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_torque_Indicated, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_flt_EngineSpeed, 4U);
  chartInstance->c63_sfEvent = CALL_EVENT;
  c63_chartstep_c63_MX_Gateway(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MX_GatewayMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  c63_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void c63_chartstep_c63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  boolean_T c63_out;
  boolean_T c63_b_out;
  boolean_T c63_temp;
  boolean_T c63_c_out;
  boolean_T c63_d_out;
  boolean_T c63_e_out;
  boolean_T c63_f_out;
  boolean_T c63_g_out;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 61U, chartInstance->c63_sfEvent);
  if (chartInstance->c63_is_active_c63_MX_Gateway == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 61U, chartInstance->c63_sfEvent);
    chartInstance->c63_is_active_c63_MX_Gateway = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 61U, chartInstance->c63_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c63_sfEvent);
    chartInstance->c63_is_c63_MX_Gateway = c63_IN_NO_ECU;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c63_sfEvent);
    chartInstance->c63_tp_NO_ECU = 1U;
    *chartInstance->c63_state_HPMatch = chartInstance->c63_NORMAL;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_state_HPMatch, 16U);
  } else {
    switch (chartInstance->c63_is_c63_MX_Gateway) {
     case c63_IN_ECU:
      CV_CHART_EVAL(61, 0, c63_IN_ECU);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                   chartInstance->c63_sfEvent);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                   chartInstance->c63_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c63_sfEvent);
      *chartInstance->c63_percent_Derate = 100;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_percent_Derate, 13U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c63_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   chartInstance->c63_sfEvent);
      c63_b_out = (CV_TRANSITION_EVAL(2U, (int32_T)(_SFD_CCP_CALL(5U, 2U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 2U, 0, (real_T)
        *chartInstance->c63_derate_Throttle, (real_T)
        *chartInstance->c63_percent_Derate, 0, 2U,
        *chartInstance->c63_derate_Throttle < *chartInstance->c63_percent_Derate)
        != 0U, chartInstance->c63_sfEvent) != 0U)) != 0);
      if (c63_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c63_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c63_sfEvent);
        *chartInstance->c63_percent_Derate = c63__s8_u8_(chartInstance,
          *chartInstance->c63_derate_Throttle, 384U, 19U, 15U);
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_percent_Derate, 13U);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c63_sfEvent);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 33U, chartInstance->c63_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 31U,
                   chartInstance->c63_sfEvent);
      c63_temp = (_SFD_CCP_CALL(5U, 31U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        31U, 0, (real_T)chartInstance->c63_CD_HP_MATCH_FUNCTION, (real_T)
        chartInstance->c63_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c63_CD_HP_MATCH_FUNCTION !=
        chartInstance->c63_NON_FUNCTIONAL) != 0U, chartInstance->c63_sfEvent) !=
                  0U);
      if (c63_temp) {
        c63_temp = (_SFD_CCP_CALL(5U, 31U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          31U, 1, (real_T)chartInstance->c63_derate_HPMatch, (real_T)
          *chartInstance->c63_percent_Derate, 0, 2U,
          chartInstance->c63_derate_HPMatch < *chartInstance->c63_percent_Derate)
          != 0U, chartInstance->c63_sfEvent) != 0U);
      }

      c63_c_out = (CV_TRANSITION_EVAL(31U, (int32_T)c63_temp) != 0);
      if (c63_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 31U, chartInstance->c63_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 32U, chartInstance->c63_sfEvent);
        *chartInstance->c63_percent_Derate = c63__s8_u8_(chartInstance,
          chartInstance->c63_derate_HPMatch, 466U, 19U, 14U);
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_percent_Derate, 13U);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 30U, chartInstance->c63_sfEvent);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c63_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 36U,
                   chartInstance->c63_sfEvent);
      c63_d_out = (CV_TRANSITION_EVAL(36U, (int32_T)(_SFD_CCP_CALL(5U, 36U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 36U, 0, (real_T)
        chartInstance->c63_CD_DERATE_METHOD, 1.0, 0, 0U,
        chartInstance->c63_CD_DERATE_METHOD == 1) != 0U,
        chartInstance->c63_sfEvent) != 0U)) != 0);
      if (c63_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 36U, chartInstance->c63_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 39U, chartInstance->c63_sfEvent);
        *chartInstance->c63_torque_Derate = c63__u16_s32_(chartInstance,
          c63_div_nzp_s32(chartInstance, c63__s32_u32_(chartInstance, (uint32_T)*
          chartInstance->c63_torque_Indicated * (uint32_T)c63__u16_s8_
          (chartInstance, *chartInstance->c63_percent_Derate, 494U, 36U, 6U),
          494U, 35U, 1U), 100, 494U, 59U, 1U), 494U, 59U, 1U);
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_torque_Derate, 17U);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 37U, chartInstance->c63_sfEvent);
        *chartInstance->c63_torque_Derate = c63__u16_s8_(chartInstance,
          *chartInstance->c63_percent_Derate, 492U, 18U, 14U);
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_torque_Derate, 17U);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 38U, chartInstance->c63_sfEvent);
      *chartInstance->c63_rpm_Derate = c63__u16_u32_(chartInstance,
        c63__u32_add__(chartInstance, (uint32_T)
                       *chartInstance->c63_ecu_isocMinRPM, c63__u32d_div__
                       (chartInstance, c63__u32_u64_(chartInstance, (uint64_T)
        c63__u32_s32_(chartInstance, *chartInstance->c63_ecu_isocMaxRPM -
                      *chartInstance->c63_ecu_isocMinRPM, 493U, 34U, 6U) *
        (uint64_T)c63__u32_s8_(chartInstance, *chartInstance->c63_percent_Derate,
        493U, 76U, 6U), 493U, 74U, 1U), 100U, 493U, 100U, 1U), 493U, 30U, 1U),
        493U, 30U, 1U);
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_rpm_Derate, 14U);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c63_sfEvent);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 18U,
                   chartInstance->c63_sfEvent);
      switch (chartInstance->c63_is_SEND_MSG) {
       case c63_IN_DERATE:
        CV_STATE_EVAL(18, 0, c63_IN_DERATE);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                     chartInstance->c63_sfEvent);
        c63_e_out = (CV_TRANSITION_EVAL(10U, (int32_T)(_SFD_CCP_CALL(5U, 10U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 10U, 0, (real_T)
          *chartInstance->c63_percent_Derate, 100.0, 0, 0U,
          *chartInstance->c63_percent_Derate == 100) != 0U,
          chartInstance->c63_sfEvent) != 0U)) != 0);
        if (c63_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c63_sfEvent);
          chartInstance->c63_tp_DERATE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c63_sfEvent);
          chartInstance->c63_is_SEND_MSG = c63_IN_DISABLE_DERATE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c63_sfEvent);
          chartInstance->c63_tp_DISABLE_DERATE = 1U;
          SendMsg_Derate_Now();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 19U,
                       chartInstance->c63_sfEvent);
          SendMsg_Derate_Now();
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 19U, chartInstance->c63_sfEvent);
        break;

       case c63_IN_DISABLE_DERATE:
        CV_STATE_EVAL(18, 0, c63_IN_DISABLE_DERATE);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c63_sfEvent);
        chartInstance->c63_tp_DISABLE_DERATE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c63_sfEvent);
        chartInstance->c63_is_SEND_MSG = c63_IN_NORMAL;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c63_sfEvent);
        chartInstance->c63_tp_NORMAL = 1U;
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 20U, chartInstance->c63_sfEvent);
        break;

       case c63_IN_NON_FUNCTIONAL:
        CV_STATE_EVAL(18, 0, c63_IN_NON_FUNCTIONAL);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                     chartInstance->c63_sfEvent);
        c63_f_out = (CV_TRANSITION_EVAL(7U, (int32_T)(_SFD_CCP_CALL(5U, 7U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 7U, 0, (real_T)
          chartInstance->c63_CD_ECU_FUNCTION, (real_T)
          chartInstance->c63_NON_FUNCTIONAL, 0, 1U,
          chartInstance->c63_CD_ECU_FUNCTION !=
          chartInstance->c63_NON_FUNCTIONAL) != 0U, chartInstance->c63_sfEvent)
          != 0U)) != 0);
        if (c63_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c63_sfEvent);
          chartInstance->c63_tp_NON_FUNCTIONAL = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c63_sfEvent);
          chartInstance->c63_is_SEND_MSG = c63_IN_NORMAL;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c63_sfEvent);
          chartInstance->c63_tp_NORMAL = 1U;
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 21U,
                       chartInstance->c63_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c63_sfEvent);
        break;

       case c63_IN_NORMAL:
        CV_STATE_EVAL(18, 0, c63_IN_NORMAL);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                     chartInstance->c63_sfEvent);
        c63_g_out = (CV_TRANSITION_EVAL(8U, (int32_T)(_SFD_CCP_CALL(5U, 8U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 8U, 0, (real_T)
          *chartInstance->c63_percent_Derate, 100.0, 0, 2U,
          *chartInstance->c63_percent_Derate < 100) != 0U,
          chartInstance->c63_sfEvent) != 0U)) != 0);
        if (c63_g_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c63_sfEvent);
          chartInstance->c63_tp_NORMAL = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c63_sfEvent);
          chartInstance->c63_is_SEND_MSG = c63_IN_DERATE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c63_sfEvent);
          chartInstance->c63_tp_DERATE = 1U;
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 22U,
                       chartInstance->c63_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 22U, chartInstance->c63_sfEvent);
        break;

       default:
        CV_STATE_EVAL(18, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c63_is_SEND_MSG = c63_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c63_sfEvent);
        break;
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 18U, chartInstance->c63_sfEvent);
      c63_RPM_FAULT(chartInstance);
      c63_HP_MATCH(chartInstance);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c63_sfEvent);
      break;

     case c63_IN_NO_ECU:
      CV_CHART_EVAL(61, 0, c63_IN_NO_ECU);
      *chartInstance->c63_state_HPMatch = chartInstance->c63_NORMAL;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 21U,
                   chartInstance->c63_sfEvent);
      c63_out = (CV_TRANSITION_EVAL(21U, (int32_T)(_SFD_CCP_CALL(5U, 21U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 21U, 0, (real_T)
        chartInstance->c63_CD_ECU_FUNCTION, (real_T)
        chartInstance->c63_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c63_CD_ECU_FUNCTION != chartInstance->c63_NON_FUNCTIONAL)
        != 0U, chartInstance->c63_sfEvent) != 0U)) != 0);
      if (c63_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c63_sfEvent);
        chartInstance->c63_tp_NO_ECU = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c63_sfEvent);
        chartInstance->c63_is_c63_MX_Gateway = c63_IN_ECU;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c63_sfEvent);
        chartInstance->c63_tp_ECU = 1U;
        chartInstance->c63_is_active_DERATE_LEVEL = 1U;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c63_sfEvent);
        chartInstance->c63_tp_DERATE_LEVEL = 1U;
        chartInstance->c63_is_active_SEND_MSG = 1U;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c63_sfEvent);
        chartInstance->c63_tp_SEND_MSG = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c63_sfEvent);
        chartInstance->c63_is_SEND_MSG = c63_IN_NON_FUNCTIONAL;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c63_sfEvent);
        chartInstance->c63_tp_NON_FUNCTIONAL = 1U;
        chartInstance->c63_is_active_RPM_FAULT = 1U;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c63_sfEvent);
        chartInstance->c63_tp_RPM_FAULT = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c63_sfEvent);
        chartInstance->c63_is_RPM_FAULT = c63_b_IN_NORMAL;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c63_sfEvent);
        chartInstance->c63_b_tp_NORMAL = 1U;
        *chartInstance->c63_state_EngineSpeedDerate = chartInstance->c63_NORMAL;
        _SFD_DATA_RANGE_CHECK((real_T)
                              *chartInstance->c63_state_EngineSpeedDerate, 15U);
        chartInstance->c63_is_active_HP_MATCH = 1U;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c63_sfEvent);
        chartInstance->c63_tp_HP_MATCH = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 22U, chartInstance->c63_sfEvent);
        chartInstance->c63_is_HP_MATCH = c63_IN_NON_FUNCTIONAL;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c63_sfEvent);
        chartInstance->c63_b_tp_NON_FUNCTIONAL = 1U;
        chartInstance->c63_derate_HPMatch = 100U;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_derate_HPMatch, 2U);
        *chartInstance->c63_state_HPMatch = chartInstance->c63_NORMAL;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_state_HPMatch, 16U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 23U,
                     chartInstance->c63_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 23U, chartInstance->c63_sfEvent);
      break;

     default:
      CV_CHART_EVAL(61, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c63_is_c63_MX_Gateway = c63_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c63_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 61U, chartInstance->c63_sfEvent);
}

static void initSimStructsc63_MX_Gateway(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c63_RPM_FAULT(SFc63_MX_GatewayInstanceStruct *chartInstance)
{
  boolean_T c63_temp;
  boolean_T c63_out;
  boolean_T c63_b_temp;
  boolean_T c63_c_temp;
  boolean_T c63_b_out;
  boolean_T c63_d_temp;
  boolean_T c63_c_out;
  boolean_T c63_d_out;
  boolean_T c63_e_out;
  boolean_T c63_f_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U, chartInstance->c63_sfEvent);
  switch (chartInstance->c63_is_RPM_FAULT) {
   case c63_b_IN_NORMAL:
    CV_STATE_EVAL(10, 0, c63_b_IN_NORMAL);
    *chartInstance->c63_state_EngineSpeedDerate = chartInstance->c63_NORMAL;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 12U,
                 chartInstance->c63_sfEvent);
    c63_b_temp = (_SFD_CCP_CALL(5U, 12U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      12U, 0, (real_T)*chartInstance->c63_percent_Derate, 100.0, 0, 2U,
      *chartInstance->c63_percent_Derate < 100) != 0U,
      chartInstance->c63_sfEvent) != 0U);
    if (c63_b_temp) {
      c63_b_temp = (_SFD_CCP_CALL(5U, 12U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        12U, 1, (real_T)*chartInstance->c63_flt_EngineSpeed, (real_T)
        (*chartInstance->c63_rpm_Derate +
         chartInstance->c63_CD_DERATE_ENGINE_SPEED_HIGH_OFFSET), 0, 5U,
        *chartInstance->c63_flt_EngineSpeed >= *chartInstance->c63_rpm_Derate +
        chartInstance->c63_CD_DERATE_ENGINE_SPEED_HIGH_OFFSET) != 0U,
        chartInstance->c63_sfEvent) != 0U);
    }

    c63_c_out = (CV_TRANSITION_EVAL(12U, (int32_T)c63_b_temp) != 0);
    if (c63_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c63_sfEvent);
      chartInstance->c63_b_tp_NORMAL = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_RPM_FAULT = c63_IN_UNRESPONSIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c63_sfEvent);
      chartInstance->c63_tp_UNRESPONSIVE = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_UNRESPONSIVE = c63_IN_DEBOUNCE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c63_sfEvent);
      chartInstance->c63_tp_DEBOUNCE = 1U;
      chartInstance->c63_debounceCount = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_debounceCount, 0U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                   chartInstance->c63_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c63_sfEvent);
    break;

   case c63_IN_SHUTDOWN:
    CV_STATE_EVAL(10, 0, c63_IN_SHUTDOWN);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                 chartInstance->c63_sfEvent);
    c63_temp = (_SFD_CCP_CALL(5U, 15U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 15U,
      0, (real_T)*chartInstance->c63_state_EngineSpeedDerate, (real_T)
      chartInstance->c63_SHUTDOWN, 0, 1U,
      *chartInstance->c63_state_EngineSpeedDerate != chartInstance->c63_SHUTDOWN)
      != 0U, chartInstance->c63_sfEvent) != 0U);
    if (c63_temp) {
      c63_c_temp = (_SFD_CCP_CALL(5U, 15U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        15U, 1, (real_T)*chartInstance->c63_percent_Derate, 100.0, 0, 0U,
        *chartInstance->c63_percent_Derate == 100) != 0U,
        chartInstance->c63_sfEvent) != 0U);
      if (!c63_c_temp) {
        c63_c_temp = (_SFD_CCP_CALL(5U, 15U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
          15U, 2, (real_T)*chartInstance->c63_flt_EngineSpeed, (real_T)
          (*chartInstance->c63_rpm_Derate +
           chartInstance->c63_CD_DERATE_ENGINE_SPEED_HIGH_OFFSET), 0, 2U,
          *chartInstance->c63_flt_EngineSpeed < *chartInstance->c63_rpm_Derate +
          chartInstance->c63_CD_DERATE_ENGINE_SPEED_HIGH_OFFSET) != 0U,
          chartInstance->c63_sfEvent) != 0U);
      }

      c63_temp = c63_c_temp;
    }

    c63_b_out = (CV_TRANSITION_EVAL(15U, (int32_T)c63_temp) != 0);
    if (c63_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c63_sfEvent);
      c63_exit_internal_SHUTDOWN(chartInstance);
      chartInstance->c63_tp_SHUTDOWN = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_RPM_FAULT = c63_b_IN_NORMAL;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c63_sfEvent);
      chartInstance->c63_b_tp_NORMAL = 1U;
      *chartInstance->c63_state_EngineSpeedDerate = chartInstance->c63_NORMAL;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_state_EngineSpeedDerate,
                            15U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                   chartInstance->c63_sfEvent);
      switch (chartInstance->c63_is_SHUTDOWN) {
       case c63_IN_DEBOUNCE:
        CV_STATE_EVAL(12, 0, c63_IN_DEBOUNCE);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 19U,
                     chartInstance->c63_sfEvent);
        c63_e_out = (CV_TRANSITION_EVAL(19U, (int32_T)(_SFD_CCP_CALL(5U, 19U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 19U, 0, (real_T)
          chartInstance->c63_debounceCount, (real_T)
          chartInstance->c63_CD_DERATE_ENGINE_SPEED_DEBOUNCE_SHUTDOWN, 0, 5U,
          chartInstance->c63_debounceCount >=
          chartInstance->c63_CD_DERATE_ENGINE_SPEED_DEBOUNCE_SHUTDOWN) != 0U,
          chartInstance->c63_sfEvent) != 0U)) != 0);
        if (c63_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c63_sfEvent);
          chartInstance->c63_b_tp_DEBOUNCE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c63_sfEvent);
          chartInstance->c63_is_SHUTDOWN = c63_IN_SHUTDOWN;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c63_sfEvent);
          chartInstance->c63_b_tp_SHUTDOWN = 1U;
          *chartInstance->c63_state_EngineSpeedDerate =
            chartInstance->c63_SHUTDOWN;
          _SFD_DATA_RANGE_CHECK((real_T)
                                *chartInstance->c63_state_EngineSpeedDerate, 15U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U,
                       chartInstance->c63_sfEvent);
          chartInstance->c63_debounceCount = c63__u16_s32_(chartInstance,
            c63__s32_add__(chartInstance, (int32_T)
                           chartInstance->c63_debounceCount, 1, 417U, 34U, 15U),
            417U, 34U, 15U);
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_debounceCount, 0U);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c63_sfEvent);
        break;

       case c63_IN_SHUTDOWN:
        CV_STATE_EVAL(12, 0, c63_IN_SHUTDOWN);
        *chartInstance->c63_state_EngineSpeedDerate =
          chartInstance->c63_SHUTDOWN;
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 14U,
                     chartInstance->c63_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c63_sfEvent);
        break;

       default:
        CV_STATE_EVAL(12, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c63_is_SHUTDOWN = c63_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c63_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c63_sfEvent);
    break;

   case c63_IN_UNRESPONSIVE:
    CV_STATE_EVAL(10, 0, c63_IN_UNRESPONSIVE);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 14U,
                 chartInstance->c63_sfEvent);
    c63_out = (CV_TRANSITION_EVAL(14U, (int32_T)(_SFD_CCP_CALL(5U, 14U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 14U, 0, (real_T)
      *chartInstance->c63_state_EngineSpeedDerate, (real_T)
      chartInstance->c63_UNRESPONSIVE, 0, 0U,
      *chartInstance->c63_state_EngineSpeedDerate ==
      chartInstance->c63_UNRESPONSIVE) != 0U, chartInstance->c63_sfEvent) != 0U))
               != 0);
    if (c63_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c63_sfEvent);
      c63_exit_internal_UNRESPONSIVE(chartInstance);
      chartInstance->c63_tp_UNRESPONSIVE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_RPM_FAULT = c63_IN_SHUTDOWN;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c63_sfEvent);
      chartInstance->c63_tp_SHUTDOWN = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_SHUTDOWN = c63_IN_DEBOUNCE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c63_sfEvent);
      chartInstance->c63_b_tp_DEBOUNCE = 1U;
      chartInstance->c63_debounceCount = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_debounceCount, 0U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U,
                   chartInstance->c63_sfEvent);
      c63_d_temp = (_SFD_CCP_CALL(5U, 13U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        13U, 0, (real_T)*chartInstance->c63_percent_Derate, 100.0, 0, 0U,
        *chartInstance->c63_percent_Derate == 100) != 0U,
        chartInstance->c63_sfEvent) != 0U);
      if (!c63_d_temp) {
        c63_d_temp = (_SFD_CCP_CALL(5U, 13U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          13U, 1, (real_T)*chartInstance->c63_flt_EngineSpeed, (real_T)
          (*chartInstance->c63_rpm_Derate +
           chartInstance->c63_CD_DERATE_ENGINE_SPEED_HIGH_OFFSET), 0, 2U,
          *chartInstance->c63_flt_EngineSpeed < *chartInstance->c63_rpm_Derate +
          chartInstance->c63_CD_DERATE_ENGINE_SPEED_HIGH_OFFSET) != 0U,
          chartInstance->c63_sfEvent) != 0U);
      }

      c63_d_out = (CV_TRANSITION_EVAL(13U, (int32_T)c63_d_temp) != 0);
      if (c63_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c63_sfEvent);
        c63_exit_internal_UNRESPONSIVE(chartInstance);
        chartInstance->c63_tp_UNRESPONSIVE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c63_sfEvent);
        chartInstance->c63_is_RPM_FAULT = c63_b_IN_NORMAL;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c63_sfEvent);
        chartInstance->c63_b_tp_NORMAL = 1U;
        *chartInstance->c63_state_EngineSpeedDerate = chartInstance->c63_NORMAL;
        _SFD_DATA_RANGE_CHECK((real_T)
                              *chartInstance->c63_state_EngineSpeedDerate, 15U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 15U,
                     chartInstance->c63_sfEvent);
        switch (chartInstance->c63_is_UNRESPONSIVE) {
         case c63_IN_DEBOUNCE:
          CV_STATE_EVAL(15, 0, c63_IN_DEBOUNCE);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 17U,
                       chartInstance->c63_sfEvent);
          c63_f_out = (CV_TRANSITION_EVAL(17U, (int32_T)(_SFD_CCP_CALL(5U, 17U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 17U, 0, (real_T)
            chartInstance->c63_debounceCount, (real_T)
            chartInstance->c63_CD_DERATE_ENGINE_SPEED_DEBOUNCE_HIGH, 0, 5U,
            chartInstance->c63_debounceCount >=
            chartInstance->c63_CD_DERATE_ENGINE_SPEED_DEBOUNCE_HIGH) != 0U,
            chartInstance->c63_sfEvent) != 0U)) != 0);
          if (c63_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c63_sfEvent);
            chartInstance->c63_tp_DEBOUNCE = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c63_sfEvent);
            chartInstance->c63_is_UNRESPONSIVE = c63_b_IN_UNRESPONSIVE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c63_sfEvent);
            chartInstance->c63_b_tp_UNRESPONSIVE = 1U;
            *chartInstance->c63_state_EngineSpeedDerate =
              chartInstance->c63_UNRESPONSIVE;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c63_state_EngineSpeedDerate,
                                  15U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 16U,
                         chartInstance->c63_sfEvent);
            chartInstance->c63_debounceCount = c63__u16_s32_(chartInstance,
              c63__s32_add__(chartInstance, (int32_T)
                             chartInstance->c63_debounceCount, 1, 411U, 34U, 15U),
              411U, 34U, 15U);
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_debounceCount, 0U);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c63_sfEvent);
          break;

         case c63_b_IN_UNRESPONSIVE:
          CV_STATE_EVAL(15, 0, c63_b_IN_UNRESPONSIVE);
          *chartInstance->c63_state_EngineSpeedDerate =
            chartInstance->c63_UNRESPONSIVE;
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 17U,
                       chartInstance->c63_sfEvent);
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c63_sfEvent);
          break;

         default:
          CV_STATE_EVAL(15, 0, 0);

          /* Unreachable state, for coverage only */
          chartInstance->c63_is_UNRESPONSIVE = c63_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c63_sfEvent);
          break;
        }
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c63_sfEvent);
    break;

   default:
    CV_STATE_EVAL(10, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c63_is_RPM_FAULT = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c63_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c63_sfEvent);
}

static void c63_exit_internal_UNRESPONSIVE(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c63_is_UNRESPONSIVE) {
   case c63_IN_DEBOUNCE:
    CV_STATE_EVAL(15, 1, c63_IN_DEBOUNCE);
    chartInstance->c63_tp_DEBOUNCE = 0U;
    chartInstance->c63_is_UNRESPONSIVE = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c63_sfEvent);
    break;

   case c63_b_IN_UNRESPONSIVE:
    CV_STATE_EVAL(15, 1, c63_b_IN_UNRESPONSIVE);
    chartInstance->c63_b_tp_UNRESPONSIVE = 0U;
    chartInstance->c63_is_UNRESPONSIVE = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c63_sfEvent);
    break;

   default:
    CV_STATE_EVAL(15, 1, 0);
    chartInstance->c63_is_UNRESPONSIVE = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c63_sfEvent);
    break;
  }
}

static void c63_exit_internal_SHUTDOWN(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c63_is_SHUTDOWN) {
   case c63_IN_DEBOUNCE:
    CV_STATE_EVAL(12, 1, c63_IN_DEBOUNCE);
    chartInstance->c63_b_tp_DEBOUNCE = 0U;
    chartInstance->c63_is_SHUTDOWN = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c63_sfEvent);
    break;

   case c63_IN_SHUTDOWN:
    CV_STATE_EVAL(12, 1, c63_IN_SHUTDOWN);
    chartInstance->c63_b_tp_SHUTDOWN = 0U;
    chartInstance->c63_is_SHUTDOWN = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c63_sfEvent);
    break;

   default:
    CV_STATE_EVAL(12, 1, 0);
    chartInstance->c63_is_SHUTDOWN = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c63_sfEvent);
    break;
  }
}

static void c63_HP_MATCH(SFc63_MX_GatewayInstanceStruct *chartInstance)
{
  boolean_T c63_out;
  boolean_T c63_b_out;
  boolean_T c63_c_out;
  boolean_T c63_d_out;
  boolean_T c63_e_out;
  boolean_T c63_f_out;
  boolean_T c63_temp;
  boolean_T c63_g_out;
  boolean_T c63_h_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c63_sfEvent);
  switch (chartInstance->c63_is_HP_MATCH) {
   case c63_IN_Cranking:
    CV_STATE_EVAL(2, 0, c63_IN_Cranking);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 35U,
                 chartInstance->c63_sfEvent);
    c63_out = (CV_TRANSITION_EVAL(35U, (int32_T)(_SFD_CCP_CALL(5U, 35U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 35U, 0, (real_T)
      *chartInstance->c63_state_Engine, (real_T)
      chartInstance->c63_ENGINE_CRANKING, 0, 1U,
      *chartInstance->c63_state_Engine != chartInstance->c63_ENGINE_CRANKING) !=
      0U, chartInstance->c63_sfEvent) != 0U)) != 0);
    if (c63_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 35U, chartInstance->c63_sfEvent);
      chartInstance->c63_tp_Cranking = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_HP_MATCH = c63_IN_SEND_REQUEST;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c63_sfEvent);
      chartInstance->c63_tp_SEND_REQUEST = 1U;
      chartInstance->c63_num_Trys = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_num_Trys, 3U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 27U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_SEND_REQUEST = c63_IN_SEND_MESSAGE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c63_sfEvent);
      chartInstance->c63_tp_SEND_MESSAGE = 1U;
      SendMsg_SOFTRequest_Now();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                   chartInstance->c63_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c63_sfEvent);
    break;

   case c63_b_IN_DERATE:
    CV_STATE_EVAL(2, 0, c63_b_IN_DERATE);
    *chartInstance->c63_state_HPMatch = chartInstance->c63_FAILURE;
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c63_sfEvent);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c63_sfEvent);
    break;

   case c63_IN_NON_FUNCTIONAL:
    CV_STATE_EVAL(2, 0, c63_IN_NON_FUNCTIONAL);
    *chartInstance->c63_state_HPMatch = chartInstance->c63_NORMAL;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 23U,
                 chartInstance->c63_sfEvent);
    c63_d_out = (CV_TRANSITION_EVAL(23U, (int32_T)(_SFD_CCP_CALL(5U, 23U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 23U, 0, (real_T)
      chartInstance->c63_CD_HP_MATCH_FUNCTION, (real_T)
      chartInstance->c63_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c63_CD_HP_MATCH_FUNCTION !=
      chartInstance->c63_NON_FUNCTIONAL) != 0U, chartInstance->c63_sfEvent) !=
      0U)) != 0);
    if (c63_d_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 23U, chartInstance->c63_sfEvent);
      chartInstance->c63_b_tp_NON_FUNCTIONAL = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_HP_MATCH = c63_IN_SEND_REQUEST;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c63_sfEvent);
      chartInstance->c63_tp_SEND_REQUEST = 1U;
      chartInstance->c63_num_Trys = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_num_Trys, 3U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 27U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_SEND_REQUEST = c63_IN_SEND_MESSAGE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c63_sfEvent);
      chartInstance->c63_tp_SEND_MESSAGE = 1U;
      SendMsg_SOFTRequest_Now();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                   chartInstance->c63_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c63_sfEvent);
    break;

   case c63_IN_REQUEST_RECEIVED:
    CV_STATE_EVAL(2, 0, c63_IN_REQUEST_RECEIVED);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 25U,
                 chartInstance->c63_sfEvent);
    c63_b_out = (CV_TRANSITION_EVAL(25U, (int32_T)(_SFD_CCP_CALL(5U, 25U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 25U, 0, (real_T)
      *chartInstance->c63_ecu_HP, (real_T)chartInstance->c63_CD_MACHINE_HP, 0,
      1U, *chartInstance->c63_ecu_HP != chartInstance->c63_CD_MACHINE_HP) != 0U,
      chartInstance->c63_sfEvent) != 0U)) != 0);
    if (c63_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 25U, chartInstance->c63_sfEvent);
      chartInstance->c63_tp_REQUEST_RECEIVED = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_HP_MATCH = c63_b_IN_DERATE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c63_sfEvent);
      chartInstance->c63_b_tp_DERATE = 1U;
      chartInstance->c63_derate_HPMatch =
        chartInstance->c63_CD_MATCH_DERATE_PERCENT;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_derate_HPMatch, 2U);
      *chartInstance->c63_state_HPMatch = chartInstance->c63_FAILURE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_state_HPMatch, 16U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                   chartInstance->c63_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c63_sfEvent);
    break;

   case c63_IN_SEND_REQUEST:
    CV_STATE_EVAL(2, 0, c63_IN_SEND_REQUEST);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 24U,
                 chartInstance->c63_sfEvent);
    c63_c_out = (CV_TRANSITION_EVAL(24U, (int32_T)(_SFD_CCP_CALL(5U, 24U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 24U, 0, (real_T)
      *chartInstance->c63_ecu_HP, (real_T)chartInstance->c63_UNDEFINED, 0, 1U,
      *chartInstance->c63_ecu_HP != chartInstance->c63_UNDEFINED) != 0U,
      chartInstance->c63_sfEvent) != 0U)) != 0);
    if (c63_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c63_sfEvent);
      c63_exit_internal_SEND_REQUEST(chartInstance);
      chartInstance->c63_tp_SEND_REQUEST = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c63_sfEvent);
      chartInstance->c63_is_HP_MATCH = c63_IN_REQUEST_RECEIVED;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c63_sfEvent);
      chartInstance->c63_tp_REQUEST_RECEIVED = 1U;
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 26U,
                   chartInstance->c63_sfEvent);
      c63_e_out = (CV_TRANSITION_EVAL(26U, (int32_T)(_SFD_CCP_CALL(5U, 26U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 26U, 0, (real_T)
        chartInstance->c63_num_Trys, 3.0, 0, 4U, chartInstance->c63_num_Trys > 3)
        != 0U, chartInstance->c63_sfEvent) != 0U)) != 0);
      if (c63_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 26U, chartInstance->c63_sfEvent);
        c63_exit_internal_SEND_REQUEST(chartInstance);
        chartInstance->c63_tp_SEND_REQUEST = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c63_sfEvent);
        chartInstance->c63_is_HP_MATCH = c63_b_IN_DERATE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c63_sfEvent);
        chartInstance->c63_b_tp_DERATE = 1U;
        chartInstance->c63_derate_HPMatch =
          chartInstance->c63_CD_MATCH_DERATE_PERCENT;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_derate_HPMatch, 2U);
        *chartInstance->c63_state_HPMatch = chartInstance->c63_FAILURE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c63_state_HPMatch, 16U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 34U,
                     chartInstance->c63_sfEvent);
        c63_f_out = (CV_TRANSITION_EVAL(34U, (int32_T)(_SFD_CCP_CALL(5U, 34U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 34U, 0, (real_T)
          *chartInstance->c63_state_Engine, (real_T)
          chartInstance->c63_ENGINE_CRANKING, 0, 0U,
          *chartInstance->c63_state_Engine == chartInstance->c63_ENGINE_CRANKING)
          != 0U, chartInstance->c63_sfEvent) != 0U)) != 0);
        if (c63_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 34U, chartInstance->c63_sfEvent);
          c63_exit_internal_SEND_REQUEST(chartInstance);
          chartInstance->c63_tp_SEND_REQUEST = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c63_sfEvent);
          chartInstance->c63_is_HP_MATCH = c63_IN_Cranking;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c63_sfEvent);
          chartInstance->c63_tp_Cranking = 1U;
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                       chartInstance->c63_sfEvent);
          switch (chartInstance->c63_is_SEND_REQUEST) {
           case c63_IN_SEND_MESSAGE:
            CV_STATE_EVAL(7, 0, c63_IN_SEND_MESSAGE);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 28U,
                         chartInstance->c63_sfEvent);
            c63_temp = (_SFD_CCP_CALL(5U, 28U, 0, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 28U, 0, (real_T)*chartInstance->c63_state_CommECU, (real_T)
               chartInstance->c63_NORMAL, 0, 0U,
               *chartInstance->c63_state_CommECU == chartInstance->c63_NORMAL)
              != 0U, chartInstance->c63_sfEvent) != 0U);
            if (c63_temp) {
              c63_temp = (_SFD_CCP_CALL(5U, 28U, 1, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 28U, 1, (real_T)
                                   *chartInstance->c63_state_ECUHold, (real_T)
                                   chartInstance->c63_ACTIVE, 0, 0U,
                                   *chartInstance->c63_state_ECUHold ==
                                   chartInstance->c63_ACTIVE) != 0U,
                chartInstance->c63_sfEvent) != 0U);
            }

            c63_h_out = (CV_TRANSITION_EVAL(28U, (int32_T)c63_temp) != 0);
            if (c63_h_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 28U,
                           chartInstance->c63_sfEvent);
              chartInstance->c63_tp_SEND_MESSAGE = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c63_sfEvent);
              chartInstance->c63_is_SEND_REQUEST = c63_IN_WAIT_FOR_RESPONSE;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c63_sfEvent);
              chartInstance->c63_tp_WAIT_FOR_RESPONSE = 1U;
              chartInstance->c63_debounceRequest = 0U;
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_debounceRequest,
                                    1U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                           chartInstance->c63_sfEvent);
            }

            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U,
                         chartInstance->c63_sfEvent);
            break;

           case c63_IN_WAIT_FOR_RESPONSE:
            CV_STATE_EVAL(7, 0, c63_IN_WAIT_FOR_RESPONSE);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 29U,
                         chartInstance->c63_sfEvent);
            c63_g_out = (CV_TRANSITION_EVAL(29U, (int32_T)(_SFD_CCP_CALL(5U, 29U,
              0, (boolean_T)CV_RELATIONAL_EVAL(5U, 29U, 0, (real_T)
              chartInstance->c63_debounceRequest, 180.0, 0, 5U,
              chartInstance->c63_debounceRequest >= 180) != 0U,
              chartInstance->c63_sfEvent) != 0U)) != 0);
            if (c63_g_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 29U,
                           chartInstance->c63_sfEvent);
              chartInstance->c63_num_Trys = c63__u8_s32_(chartInstance,
                c63__s32_add__(chartInstance, (int32_T)
                               chartInstance->c63_num_Trys, 1, 459U, 29U, 10U),
                459U, 29U, 10U);
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_num_Trys, 3U);
              chartInstance->c63_tp_WAIT_FOR_RESPONSE = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c63_sfEvent);
              chartInstance->c63_is_SEND_REQUEST = c63_IN_SEND_MESSAGE;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c63_sfEvent);
              chartInstance->c63_tp_SEND_MESSAGE = 1U;
              SendMsg_SOFTRequest_Now();
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                           chartInstance->c63_sfEvent);
              chartInstance->c63_debounceRequest = c63__u16_s32_(chartInstance,
                c63__s32_add__(chartInstance, (int32_T)
                               chartInstance->c63_debounceRequest, 1, 456U, 47U,
                               17U), 456U, 47U, 17U);
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c63_debounceRequest,
                                    1U);
            }

            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U,
                         chartInstance->c63_sfEvent);
            break;

           default:
            CV_STATE_EVAL(7, 0, 0);

            /* Unreachable state, for coverage only */
            chartInstance->c63_is_SEND_REQUEST = c63_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c63_sfEvent);
            break;
          }
        }
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c63_sfEvent);
    break;

   default:
    CV_STATE_EVAL(2, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c63_is_HP_MATCH = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c63_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c63_sfEvent);
}

static void c63_exit_internal_SEND_REQUEST(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c63_is_SEND_REQUEST) {
   case c63_IN_SEND_MESSAGE:
    CV_STATE_EVAL(7, 1, c63_IN_SEND_MESSAGE);
    chartInstance->c63_tp_SEND_MESSAGE = 0U;
    chartInstance->c63_is_SEND_REQUEST = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c63_sfEvent);
    break;

   case c63_IN_WAIT_FOR_RESPONSE:
    CV_STATE_EVAL(7, 1, c63_IN_WAIT_FOR_RESPONSE);
    chartInstance->c63_tp_WAIT_FOR_RESPONSE = 0U;
    chartInstance->c63_is_SEND_REQUEST = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c63_sfEvent);
    break;

   default:
    CV_STATE_EVAL(7, 1, 0);
    chartInstance->c63_is_SEND_REQUEST = c63_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c63_sfEvent);
    break;
  }
}

static void init_script_number_translation(uint32_T c63_machineNumber, uint32_T
  c63_chartNumber, uint32_T c63_instanceNumber)
{
  (void)(c63_machineNumber);
  (void)(c63_chartNumber);
  (void)(c63_instanceNumber);
}

const mxArray *sf_c63_MX_Gateway_get_eml_resolved_functions_info(void)
{
  const mxArray *c63_nameCaptureInfo = NULL;
  c63_nameCaptureInfo = NULL;
  sf_mex_assign(&c63_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c63_nameCaptureInfo;
}

static const mxArray *c63_sf_marshallOut(void *chartInstanceVoid, void
  *c63_inData)
{
  const mxArray *c63_mxArrayOutData;
  int32_T c63_u;
  const mxArray *c63_y = NULL;
  SFc63_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc63_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c63_mxArrayOutData = NULL;
  c63_mxArrayOutData = NULL;
  c63_u = *(int32_T *)c63_inData;
  c63_y = NULL;
  sf_mex_assign(&c63_y, sf_mex_create("y", &c63_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c63_mxArrayOutData, c63_y, false);
  return c63_mxArrayOutData;
}

static int32_T c63_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_u, const emlrtMsgIdentifier *c63_parentId)
{
  int32_T c63_y;
  int32_T c63_i0;
  (void)chartInstance;
  sf_mex_import(c63_parentId, sf_mex_dup(c63_u), &c63_i0, 1, 6, 0U, 0, 0U, 0);
  c63_y = c63_i0;
  sf_mex_destroy(&c63_u);
  return c63_y;
}

static void c63_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c63_mxArrayInData, const char_T *c63_varName, void *c63_outData)
{
  const mxArray *c63_b_sfEvent;
  emlrtMsgIdentifier c63_thisId;
  int32_T c63_y;
  SFc63_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc63_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c63_b_sfEvent = sf_mex_dup(c63_mxArrayInData);
  c63_thisId.fIdentifier = (const char *)c63_varName;
  c63_thisId.fParent = NULL;
  c63_thisId.bParentIsCell = false;
  c63_y = c63_emlrt_marshallIn(chartInstance, sf_mex_dup(c63_b_sfEvent),
    &c63_thisId);
  sf_mex_destroy(&c63_b_sfEvent);
  *(int32_T *)c63_outData = c63_y;
  sf_mex_destroy(&c63_mxArrayInData);
}

static const mxArray *c63_b_sf_marshallOut(void *chartInstanceVoid, void
  *c63_inData)
{
  const mxArray *c63_mxArrayOutData;
  uint8_T c63_u;
  const mxArray *c63_y = NULL;
  SFc63_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc63_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c63_mxArrayOutData = NULL;
  c63_mxArrayOutData = NULL;
  c63_u = *(uint8_T *)c63_inData;
  c63_y = NULL;
  sf_mex_assign(&c63_y, sf_mex_create("y", &c63_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c63_mxArrayOutData, c63_y, false);
  return c63_mxArrayOutData;
}

static uint8_T c63_b_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_b_tp_ECU, const char_T *c63_identifier)
{
  uint8_T c63_y;
  emlrtMsgIdentifier c63_thisId;
  c63_thisId.fIdentifier = (const char *)c63_identifier;
  c63_thisId.fParent = NULL;
  c63_thisId.bParentIsCell = false;
  c63_y = c63_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c63_b_tp_ECU),
    &c63_thisId);
  sf_mex_destroy(&c63_b_tp_ECU);
  return c63_y;
}

static uint8_T c63_c_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_u, const emlrtMsgIdentifier *c63_parentId)
{
  uint8_T c63_y;
  uint8_T c63_u0;
  (void)chartInstance;
  sf_mex_import(c63_parentId, sf_mex_dup(c63_u), &c63_u0, 1, 3, 0U, 0, 0U, 0);
  c63_y = c63_u0;
  sf_mex_destroy(&c63_u);
  return c63_y;
}

static void c63_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c63_mxArrayInData, const char_T *c63_varName, void *c63_outData)
{
  const mxArray *c63_b_tp_ECU;
  emlrtMsgIdentifier c63_thisId;
  uint8_T c63_y;
  SFc63_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc63_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c63_b_tp_ECU = sf_mex_dup(c63_mxArrayInData);
  c63_thisId.fIdentifier = (const char *)c63_varName;
  c63_thisId.fParent = NULL;
  c63_thisId.bParentIsCell = false;
  c63_y = c63_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c63_b_tp_ECU),
    &c63_thisId);
  sf_mex_destroy(&c63_b_tp_ECU);
  *(uint8_T *)c63_outData = c63_y;
  sf_mex_destroy(&c63_mxArrayInData);
}

static const mxArray *c63_c_sf_marshallOut(void *chartInstanceVoid, void
  *c63_inData)
{
  const mxArray *c63_mxArrayOutData;
  int8_T c63_u;
  const mxArray *c63_y = NULL;
  SFc63_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc63_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c63_mxArrayOutData = NULL;
  c63_mxArrayOutData = NULL;
  c63_u = *(int8_T *)c63_inData;
  c63_y = NULL;
  sf_mex_assign(&c63_y, sf_mex_create("y", &c63_u, 2, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c63_mxArrayOutData, c63_y, false);
  return c63_mxArrayOutData;
}

static int8_T c63_d_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_b_percent_Derate, const char_T
  *c63_identifier)
{
  int8_T c63_y;
  emlrtMsgIdentifier c63_thisId;
  c63_thisId.fIdentifier = (const char *)c63_identifier;
  c63_thisId.fParent = NULL;
  c63_thisId.bParentIsCell = false;
  c63_y = c63_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c63_b_percent_Derate),
    &c63_thisId);
  sf_mex_destroy(&c63_b_percent_Derate);
  return c63_y;
}

static int8_T c63_e_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_u, const emlrtMsgIdentifier *c63_parentId)
{
  int8_T c63_y;
  int8_T c63_i1;
  (void)chartInstance;
  sf_mex_import(c63_parentId, sf_mex_dup(c63_u), &c63_i1, 1, 2, 0U, 0, 0U, 0);
  c63_y = c63_i1;
  sf_mex_destroy(&c63_u);
  return c63_y;
}

static void c63_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c63_mxArrayInData, const char_T *c63_varName, void *c63_outData)
{
  const mxArray *c63_b_percent_Derate;
  emlrtMsgIdentifier c63_thisId;
  int8_T c63_y;
  SFc63_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc63_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c63_b_percent_Derate = sf_mex_dup(c63_mxArrayInData);
  c63_thisId.fIdentifier = (const char *)c63_varName;
  c63_thisId.fParent = NULL;
  c63_thisId.bParentIsCell = false;
  c63_y = c63_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c63_b_percent_Derate),
    &c63_thisId);
  sf_mex_destroy(&c63_b_percent_Derate);
  *(int8_T *)c63_outData = c63_y;
  sf_mex_destroy(&c63_mxArrayInData);
}

static const mxArray *c63_d_sf_marshallOut(void *chartInstanceVoid, void
  *c63_inData)
{
  const mxArray *c63_mxArrayOutData;
  uint16_T c63_u;
  const mxArray *c63_y = NULL;
  SFc63_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc63_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c63_mxArrayOutData = NULL;
  c63_mxArrayOutData = NULL;
  c63_u = *(uint16_T *)c63_inData;
  c63_y = NULL;
  sf_mex_assign(&c63_y, sf_mex_create("y", &c63_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c63_mxArrayOutData, c63_y, false);
  return c63_mxArrayOutData;
}

static uint16_T c63_f_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_b_rpm_Derate, const char_T *c63_identifier)
{
  uint16_T c63_y;
  emlrtMsgIdentifier c63_thisId;
  c63_thisId.fIdentifier = (const char *)c63_identifier;
  c63_thisId.fParent = NULL;
  c63_thisId.bParentIsCell = false;
  c63_y = c63_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c63_b_rpm_Derate),
    &c63_thisId);
  sf_mex_destroy(&c63_b_rpm_Derate);
  return c63_y;
}

static uint16_T c63_g_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_u, const emlrtMsgIdentifier *c63_parentId)
{
  uint16_T c63_y;
  uint16_T c63_u1;
  (void)chartInstance;
  sf_mex_import(c63_parentId, sf_mex_dup(c63_u), &c63_u1, 1, 5, 0U, 0, 0U, 0);
  c63_y = c63_u1;
  sf_mex_destroy(&c63_u);
  return c63_y;
}

static void c63_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c63_mxArrayInData, const char_T *c63_varName, void *c63_outData)
{
  const mxArray *c63_b_rpm_Derate;
  emlrtMsgIdentifier c63_thisId;
  uint16_T c63_y;
  SFc63_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc63_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c63_b_rpm_Derate = sf_mex_dup(c63_mxArrayInData);
  c63_thisId.fIdentifier = (const char *)c63_varName;
  c63_thisId.fParent = NULL;
  c63_thisId.bParentIsCell = false;
  c63_y = c63_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c63_b_rpm_Derate),
    &c63_thisId);
  sf_mex_destroy(&c63_b_rpm_Derate);
  *(uint16_T *)c63_outData = c63_y;
  sf_mex_destroy(&c63_mxArrayInData);
}

static const mxArray *c63_h_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_b_setSimStateSideEffectsInfo, const char_T *
  c63_identifier)
{
  const mxArray *c63_y = NULL;
  emlrtMsgIdentifier c63_thisId;
  c63_y = NULL;
  c63_thisId.fIdentifier = (const char *)c63_identifier;
  c63_thisId.fParent = NULL;
  c63_thisId.bParentIsCell = false;
  sf_mex_assign(&c63_y, c63_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c63_b_setSimStateSideEffectsInfo), &c63_thisId), false);
  sf_mex_destroy(&c63_b_setSimStateSideEffectsInfo);
  return c63_y;
}

static const mxArray *c63_i_emlrt_marshallIn(SFc63_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c63_u, const emlrtMsgIdentifier *c63_parentId)
{
  const mxArray *c63_y = NULL;
  (void)chartInstance;
  (void)c63_parentId;
  c63_y = NULL;
  sf_mex_assign(&c63_y, sf_mex_duplicatearraysafe(&c63_u), false);
  sf_mex_destroy(&c63_u);
  return c63_y;
}

static const mxArray *sf_get_hover_data_for_msg(SFc63_MX_GatewayInstanceStruct
  *chartInstance, int32_T c63_ssid)
{
  (void)chartInstance;
  (void)c63_ssid;
  return NULL;
}

static void c63_init_sf_message_store_memory(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static int32_T c63_div_nzp_s32(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int32_T c63_numerator, int32_T c63_denominator, uint32_T c63_ssid_src_loc,
  int32_T c63_offset_src_loc, int32_T c63_length_src_loc)
{
  int32_T c63_quotient;
  uint32_T c63_absNumerator;
  uint32_T c63_absDenominator;
  boolean_T c63_quotientNeedsNegation;
  uint32_T c63_tempAbsQuotient;
  (void)chartInstance;
  (void)c63_ssid_src_loc;
  (void)c63_offset_src_loc;
  (void)c63_length_src_loc;
  if (c63_numerator < 0) {
    c63_absNumerator = ~(uint32_T)c63_numerator + 1U;
  } else {
    c63_absNumerator = (uint32_T)c63_numerator;
  }

  if (c63_denominator < 0) {
    c63_absDenominator = ~(uint32_T)c63_denominator + 1U;
  } else {
    c63_absDenominator = (uint32_T)c63_denominator;
  }

  c63_quotientNeedsNegation = ((c63_numerator < 0) != (c63_denominator < 0));
  c63_tempAbsQuotient = c63_absNumerator / c63_absDenominator;
  if (c63_quotientNeedsNegation) {
    c63_quotient = -(int32_T)c63_tempAbsQuotient;
  } else {
    c63_quotient = (int32_T)c63_tempAbsQuotient;
  }

  return c63_quotient;
}

static uint16_T c63__u16_u32_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc)
{
  uint16_T c63_a;
  (void)chartInstance;
  c63_a = (uint16_T)c63_b;
  if (c63_a != c63_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static uint32_T c63__u32_add__(SFc63_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c63_b, uint32_T c63_c, uint32_T c63_ssid_src_loc, int32_T
  c63_offset_src_loc, int32_T c63_length_src_loc)
{
  uint32_T c63_a;
  (void)chartInstance;
  c63_a = c63_b + c63_c;
  if (c63_a < c63_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static uint32_T c63__u32d_div__(SFc63_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c63_b, uint32_T c63_c, uint32_T c63_ssid_src_loc, int32_T
  c63_offset_src_loc, int32_T c63_length_src_loc)
{
  (void)chartInstance;
  (void)c63_ssid_src_loc;
  (void)c63_offset_src_loc;
  (void)c63_length_src_loc;
  if (c63_c == 0U) {
    _SFD_OVERFLOW_DETECTION(SFDB_DIVIDE_BY_ZERO, 0U, 0U, 0U);
  }

  return c63_b / c63_c;
}

static uint32_T c63__u32_u64_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  uint64_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc)
{
  uint32_T c63_a;
  (void)chartInstance;
  c63_a = (uint32_T)c63_b;
  if ((uint64_T)c63_a != c63_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static uint32_T c63__u32_s32_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int32_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc)
{
  uint32_T c63_a;
  (void)chartInstance;
  c63_a = (uint32_T)c63_b;
  if (c63_b < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static uint32_T c63__u32_s8_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int8_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc)
{
  uint32_T c63_a;
  (void)chartInstance;
  c63_a = (uint32_T)c63_b;
  if (c63_b < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static uint16_T c63__u16_s32_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int32_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc)
{
  uint16_T c63_a;
  (void)chartInstance;
  c63_a = (uint16_T)c63_b;
  if (c63_a != c63_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static int32_T c63__s32_u32_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc)
{
  int32_T c63_a;
  (void)chartInstance;
  c63_a = (int32_T)c63_b;
  if (c63_a < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static uint16_T c63__u16_s8_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int8_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc)
{
  uint16_T c63_a;
  (void)chartInstance;
  c63_a = (uint16_T)c63_b;
  if (c63_b < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static int8_T c63__s8_u8_(SFc63_MX_GatewayInstanceStruct *chartInstance, uint8_T
  c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc)
{
  int8_T c63_a;
  (void)chartInstance;
  c63_a = (int8_T)c63_b;
  if (c63_a < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static int32_T c63__s32_add__(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int32_T c63_b, int32_T c63_c, uint32_T c63_ssid_src_loc, int32_T
  c63_offset_src_loc, int32_T c63_length_src_loc)
{
  int32_T c63_a;
  (void)chartInstance;
  c63_a = c63_b + c63_c;
  if (((c63_a ^ c63_b) & (c63_a ^ c63_c)) < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static uint8_T c63__u8_s32_(SFc63_MX_GatewayInstanceStruct *chartInstance,
  int32_T c63_b, uint32_T c63_ssid_src_loc, int32_T c63_offset_src_loc, int32_T
  c63_length_src_loc)
{
  uint8_T c63_a;
  (void)chartInstance;
  c63_a = (uint8_T)c63_b;
  if (c63_a != c63_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c63_ssid_src_loc, c63_offset_src_loc,
      c63_length_src_loc);
  }

  return c63_a;
}

static void init_dsm_address_info(SFc63_MX_GatewayInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc63_MX_GatewayInstanceStruct
  *chartInstance)
{
  chartInstance->c63_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c63_percent_Derate = (int8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c63_rpm_Derate = (uint16_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c63_state_EngineSpeedDerate = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c63_flt_EngineSpeed = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c63_torque_Indicated = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c63_ecu_isocMinRPM = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c63_ecu_isocMaxRPM = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c63_derate_Throttle = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c63_state_HPMatch = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c63_state_CommECU = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c63_state_ECUHold = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c63_ecu_HP = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c63_state_Engine = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c63_torque_Derate = (uint16_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
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

void sf_c63_MX_Gateway_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1692710582U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(916774999U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2474019196U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1388061575U);
}

mxArray* sf_c63_MX_Gateway_get_post_codegen_info(void);
mxArray *sf_c63_MX_Gateway_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("UN4pRHyS0hdDDtekQWM6UG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,9,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(4));
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c63_MX_Gateway_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c63_MX_Gateway_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c63_MX_Gateway_jit_fallback_info(void)
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

mxArray *sf_c63_MX_Gateway_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c63_MX_Gateway_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c63_MX_Gateway(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[27],T\"percent_Derate\",},{M[1],M[193],T\"rpm_Derate\",},{M[1],M[276],T\"state_EngineSpeedDerate\",},{M[1],M[469],T\"state_HPMatch\",},{M[1],M[487],T\"torque_Derate\",},{M[3],M[284],T\"debounceCount\",},{M[3],M[473],T\"debounceRequest\",},{M[3],M[468],T\"derate_HPMatch\",},{M[3],M[470],T\"num_Trys\",},{M[8],M[0],T\"is_active_c63_MX_Gateway\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[8],M[353],T\"is_active_DERATE_LEVEL\",},{M[8],M[391],T\"is_active_SEND_MSG\",},{M[8],M[401],T\"is_active_RPM_FAULT\",},{M[8],M[445],T\"is_active_HP_MATCH\",},{M[9],M[0],T\"is_c63_MX_Gateway\",},{M[9],M[391],T\"is_SEND_MSG\",},{M[9],M[401],T\"is_RPM_FAULT\",},{M[9],M[407],T\"is_UNRESPONSIVE\",},{M[9],M[413],T\"is_SHUTDOWN\",},{M[9],M[445],T\"is_HP_MATCH\",}}",
    "100 S'type','srcId','name','auxInfo'{{M[9],M[447],T\"is_SEND_REQUEST\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 21, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c63_MX_Gateway_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc63_MX_GatewayInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc63_MX_GatewayInstanceStruct *chartInstance =
      (SFc63_MX_GatewayInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MX_GatewayMachineNumber_,
           63,
           24,
           40,
           0,
           34,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_MX_GatewayMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_MX_GatewayMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _MX_GatewayMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,0,0,0,"debounceCount");
          _SFD_SET_DATA_PROPS(1,0,0,0,"debounceRequest");
          _SFD_SET_DATA_PROPS(2,0,0,0,"derate_HPMatch");
          _SFD_SET_DATA_PROPS(3,0,0,0,"num_Trys");
          _SFD_SET_DATA_PROPS(4,1,1,0,"flt_EngineSpeed");
          _SFD_SET_DATA_PROPS(5,1,1,0,"torque_Indicated");
          _SFD_SET_DATA_PROPS(6,1,1,0,"ecu_isocMinRPM");
          _SFD_SET_DATA_PROPS(7,1,1,0,"ecu_isocMaxRPM");
          _SFD_SET_DATA_PROPS(8,1,1,0,"derate_Throttle");
          _SFD_SET_DATA_PROPS(9,1,1,0,"state_CommECU");
          _SFD_SET_DATA_PROPS(10,1,1,0,"state_ECUHold");
          _SFD_SET_DATA_PROPS(11,1,1,0,"ecu_HP");
          _SFD_SET_DATA_PROPS(12,1,1,0,"state_Engine");
          _SFD_SET_DATA_PROPS(13,2,0,1,"percent_Derate");
          _SFD_SET_DATA_PROPS(14,2,0,1,"rpm_Derate");
          _SFD_SET_DATA_PROPS(15,2,0,1,"state_EngineSpeedDerate");
          _SFD_SET_DATA_PROPS(16,2,0,1,"state_HPMatch");
          _SFD_SET_DATA_PROPS(17,2,0,1,"torque_Derate");
          _SFD_SET_DATA_PROPS(18,10,0,0,"ACTIVE");
          _SFD_SET_DATA_PROPS(19,10,0,0,"CD_DERATE_ENGINE_SPEED_DEBOUNCE_HIGH");
          _SFD_SET_DATA_PROPS(20,10,0,0,
                              "CD_DERATE_ENGINE_SPEED_DEBOUNCE_SHUTDOWN");
          _SFD_SET_DATA_PROPS(21,10,0,0,"CD_DERATE_ENGINE_SPEED_HIGH_OFFSET");
          _SFD_SET_DATA_PROPS(22,10,0,0,"CD_DERATE_METHOD");
          _SFD_SET_DATA_PROPS(23,10,0,0,"CD_ECU_FUNCTION");
          _SFD_SET_DATA_PROPS(24,10,0,0,"CD_HP_MATCH_FUNCTION");
          _SFD_SET_DATA_PROPS(25,10,0,0,"CD_MACHINE_HP");
          _SFD_SET_DATA_PROPS(26,10,0,0,"CD_MATCH_DERATE_PERCENT");
          _SFD_SET_DATA_PROPS(27,10,0,0,"ENGINE_CRANKING");
          _SFD_SET_DATA_PROPS(28,10,0,0,"FAILURE");
          _SFD_SET_DATA_PROPS(29,10,0,0,"NON_FUNCTIONAL");
          _SFD_SET_DATA_PROPS(30,10,0,0,"NORMAL");
          _SFD_SET_DATA_PROPS(31,10,0,0,"SHUTDOWN");
          _SFD_SET_DATA_PROPS(32,10,0,0,"UNDEFINED");
          _SFD_SET_DATA_PROPS(33,10,0,0,"UNRESPONSIVE");
          _SFD_STATE_INFO(0,1,0);
          _SFD_STATE_INFO(1,0,1);
          _SFD_STATE_INFO(2,0,1);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_STATE_INFO(9,0,0);
          _SFD_STATE_INFO(10,0,1);
          _SFD_STATE_INFO(11,0,0);
          _SFD_STATE_INFO(12,0,0);
          _SFD_STATE_INFO(13,0,0);
          _SFD_STATE_INFO(14,0,0);
          _SFD_STATE_INFO(15,0,0);
          _SFD_STATE_INFO(16,0,0);
          _SFD_STATE_INFO(17,0,0);
          _SFD_STATE_INFO(18,0,1);
          _SFD_STATE_INFO(19,0,0);
          _SFD_STATE_INFO(20,0,0);
          _SFD_STATE_INFO(21,0,0);
          _SFD_STATE_INFO(22,0,0);
          _SFD_STATE_INFO(23,0,0);
          _SFD_CH_SUBSTATE_COUNT(2);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,23);
          _SFD_ST_SUBSTATE_COUNT(0,4);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,18);
          _SFD_ST_SUBSTATE_INDEX(0,2,10);
          _SFD_ST_SUBSTATE_INDEX(0,3,2);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(18,4);
          _SFD_ST_SUBSTATE_INDEX(18,0,19);
          _SFD_ST_SUBSTATE_INDEX(18,1,20);
          _SFD_ST_SUBSTATE_INDEX(18,2,21);
          _SFD_ST_SUBSTATE_INDEX(18,3,22);
          _SFD_ST_SUBSTATE_COUNT(19,0);
          _SFD_ST_SUBSTATE_COUNT(20,0);
          _SFD_ST_SUBSTATE_COUNT(21,0);
          _SFD_ST_SUBSTATE_COUNT(22,0);
          _SFD_ST_SUBSTATE_COUNT(10,3);
          _SFD_ST_SUBSTATE_INDEX(10,0,11);
          _SFD_ST_SUBSTATE_INDEX(10,1,12);
          _SFD_ST_SUBSTATE_INDEX(10,2,15);
          _SFD_ST_SUBSTATE_COUNT(11,0);
          _SFD_ST_SUBSTATE_COUNT(12,2);
          _SFD_ST_SUBSTATE_INDEX(12,0,13);
          _SFD_ST_SUBSTATE_INDEX(12,1,14);
          _SFD_ST_SUBSTATE_COUNT(13,0);
          _SFD_ST_SUBSTATE_COUNT(14,0);
          _SFD_ST_SUBSTATE_COUNT(15,2);
          _SFD_ST_SUBSTATE_INDEX(15,0,16);
          _SFD_ST_SUBSTATE_INDEX(15,1,17);
          _SFD_ST_SUBSTATE_COUNT(16,0);
          _SFD_ST_SUBSTATE_COUNT(17,0);
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
          _SFD_ST_SUBSTATE_COUNT(7,2);
          _SFD_ST_SUBSTATE_INDEX(7,0,8);
          _SFD_ST_SUBSTATE_INDEX(7,1,9);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,0);
          _SFD_ST_SUBSTATE_COUNT(23,0);
        }

        _SFD_CV_INIT_CHART(2,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,4,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,5,1,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(7,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(10,3,1,0,0,0,NULL,NULL);
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

        {
          _SFD_CV_INIT_STATE(15,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(16,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(17,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(18,4,1,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(22,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(23,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(20,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 35 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(21,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 35 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(21,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 34 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 34 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(33,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 49 };

          static unsigned int sEndGuardMap[] = { 40, 80 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(31,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 49 };

          static unsigned int sEndRelationalopMap[] = { 40, 80 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(31,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(32,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(30,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 22 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(36,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 22 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(36,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(39,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(37,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(38,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 35 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(7,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 35 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(7,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 22 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(8,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 22 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(8,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 23 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(10,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 23 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(10,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(11,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 31 };

          static unsigned int sEndGuardMap[] = { 22, 99 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(12,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 31 };

          static unsigned int sEndRelationalopMap[] = { 22, 99 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 2, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(12,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 31 };

          static unsigned int sEndGuardMap[] = { 22, 98 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(13,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 31 };

          static unsigned int sEndRelationalopMap[] = { 22, 98 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(13,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(14,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 41 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(14,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 47, 83 };

          static unsigned int sEndGuardMap[] = { 37, 67, 150 };

          static int sPostFixPredicateTree[] = { 0, 1, 2, -2, -3 };

          _SFD_CV_INIT_TRANS(15,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 47, 83 };

          static unsigned int sEndRelationalopMap[] = { 37, 67, 150 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 0, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(15,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 55 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(17,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 55 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(17,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(18,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(19,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(19,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(22,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(23,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(23,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 21 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(24,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 21 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(24,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 25 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(25,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 25 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(25,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(34,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(34,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(35,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(35,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 14 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(26,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 14 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(26,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(27,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 34 };

          static unsigned int sEndGuardMap[] = { 25, 57 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(28,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 34 };

          static unsigned int sEndRelationalopMap[] = { 25, 57 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(28,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 24 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(29,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 24 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(29,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)
          c63_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)
          c63_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_INT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_c_sf_marshallOut,(MexInFcnForType)
          c63_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)
          c63_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)
          c63_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)
          c63_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)
          c63_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_d_sf_marshallOut,(MexInFcnForType)
          c63_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(27,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(28,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(29,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(30,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(31,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(32,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(33,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c63_b_sf_marshallOut,(MexInFcnForType)
          c63_b_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _MX_GatewayMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc63_MX_GatewayInstanceStruct *chartInstance =
      (SFc63_MX_GatewayInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(13U, (void *)chartInstance->c63_percent_Derate);
        _SFD_SET_DATA_VALUE_PTR(29U, (void *)&chartInstance->c63_NON_FUNCTIONAL);
        _SFD_SET_DATA_VALUE_PTR(23U, (void *)&chartInstance->c63_CD_ECU_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(14U, (void *)chartInstance->c63_rpm_Derate);
        _SFD_SET_DATA_VALUE_PTR(15U, (void *)
          chartInstance->c63_state_EngineSpeedDerate);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)&chartInstance->c63_debounceCount);
        _SFD_SET_DATA_VALUE_PTR(31U, (void *)&chartInstance->c63_SHUTDOWN);
        _SFD_SET_DATA_VALUE_PTR(30U, (void *)&chartInstance->c63_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(21U, (void *)
          &chartInstance->c63_CD_DERATE_ENGINE_SPEED_HIGH_OFFSET);
        _SFD_SET_DATA_VALUE_PTR(19U, (void *)
          &chartInstance->c63_CD_DERATE_ENGINE_SPEED_DEBOUNCE_HIGH);
        _SFD_SET_DATA_VALUE_PTR(20U, (void *)
          &chartInstance->c63_CD_DERATE_ENGINE_SPEED_DEBOUNCE_SHUTDOWN);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c63_flt_EngineSpeed);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c63_torque_Indicated);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c63_ecu_isocMinRPM);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c63_ecu_isocMaxRPM);
        _SFD_SET_DATA_VALUE_PTR(33U, (void *)&chartInstance->c63_UNRESPONSIVE);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c63_derate_Throttle);
        _SFD_SET_DATA_VALUE_PTR(24U, (void *)
          &chartInstance->c63_CD_HP_MATCH_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)&chartInstance->c63_derate_HPMatch);
        _SFD_SET_DATA_VALUE_PTR(16U, (void *)chartInstance->c63_state_HPMatch);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)&chartInstance->c63_num_Trys);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)chartInstance->c63_state_CommECU);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)chartInstance->c63_state_ECUHold);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)&chartInstance->c63_debounceRequest);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)chartInstance->c63_ecu_HP);
        _SFD_SET_DATA_VALUE_PTR(32U, (void *)&chartInstance->c63_UNDEFINED);
        _SFD_SET_DATA_VALUE_PTR(25U, (void *)&chartInstance->c63_CD_MACHINE_HP);
        _SFD_SET_DATA_VALUE_PTR(18U, (void *)&chartInstance->c63_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(26U, (void *)
          &chartInstance->c63_CD_MATCH_DERATE_PERCENT);
        _SFD_SET_DATA_VALUE_PTR(28U, (void *)&chartInstance->c63_FAILURE);
        _SFD_SET_DATA_VALUE_PTR(12U, (void *)chartInstance->c63_state_Engine);
        _SFD_SET_DATA_VALUE_PTR(27U, (void *)&chartInstance->c63_ENGINE_CRANKING);
        _SFD_SET_DATA_VALUE_PTR(17U, (void *)chartInstance->c63_torque_Derate);
        _SFD_SET_DATA_VALUE_PTR(22U, (void *)
          &chartInstance->c63_CD_DERATE_METHOD);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s4AKRTI2TbEmNI2BtdnbNCF";
}

static void sf_opaque_initialize_c63_MX_Gateway(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc63_MX_GatewayInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c63_MX_Gateway((SFc63_MX_GatewayInstanceStruct*)
    chartInstanceVar);
  initialize_c63_MX_Gateway((SFc63_MX_GatewayInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c63_MX_Gateway(void *chartInstanceVar)
{
  enable_c63_MX_Gateway((SFc63_MX_GatewayInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c63_MX_Gateway(void *chartInstanceVar)
{
  disable_c63_MX_Gateway((SFc63_MX_GatewayInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c63_MX_Gateway(void *chartInstanceVar)
{
  sf_gateway_c63_MX_Gateway((SFc63_MX_GatewayInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c63_MX_Gateway(SimStruct* S)
{
  return get_sim_state_c63_MX_Gateway((SFc63_MX_GatewayInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c63_MX_Gateway(SimStruct* S, const mxArray
  *st)
{
  set_sim_state_c63_MX_Gateway((SFc63_MX_GatewayInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c63_MX_Gateway(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc63_MX_GatewayInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MX_Gateway_optimization_info();
    }

    finalize_c63_MX_Gateway((SFc63_MX_GatewayInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc63_MX_Gateway((SFc63_MX_GatewayInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c63_MX_Gateway(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c63_MX_Gateway((SFc63_MX_GatewayInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c63_MX_Gateway(SimStruct *S)
{
  /* Actual parameters from chart:
     ACTIVE CD_DERATE_ENGINE_SPEED_DEBOUNCE_HIGH CD_DERATE_ENGINE_SPEED_DEBOUNCE_SHUTDOWN CD_DERATE_ENGINE_SPEED_HIGH_OFFSET CD_DERATE_METHOD CD_ECU_FUNCTION CD_HP_MATCH_FUNCTION CD_MACHINE_HP CD_MATCH_DERATE_PERCENT ENGINE_CRANKING FAILURE NON_FUNCTIONAL NORMAL SHUTDOWN UNDEFINED UNRESPONSIVE
   */
  const char_T *rtParamNames[] = { "ACTIVE",
    "CD_DERATE_ENGINE_SPEED_DEBOUNCE_HIGH",
    "CD_DERATE_ENGINE_SPEED_DEBOUNCE_SHUTDOWN",
    "CD_DERATE_ENGINE_SPEED_HIGH_OFFSET", "CD_DERATE_METHOD", "CD_ECU_FUNCTION",
    "CD_HP_MATCH_FUNCTION", "CD_MACHINE_HP", "CD_MATCH_DERATE_PERCENT",
    "ENGINE_CRANKING", "FAILURE", "NON_FUNCTIONAL", "NORMAL", "SHUTDOWN",
    "UNDEFINED", "UNRESPONSIVE" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_UINT8);

  /* registration for CD_DERATE_ENGINE_SPEED_DEBOUNCE_HIGH*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT16);

  /* registration for CD_DERATE_ENGINE_SPEED_DEBOUNCE_SHUTDOWN*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT16);

  /* registration for CD_DERATE_ENGINE_SPEED_HIGH_OFFSET*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_UINT16);

  /* registration for CD_DERATE_METHOD*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_UINT8);

  /* registration for CD_ECU_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_UINT8);

  /* registration for CD_HP_MATCH_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_UINT8);

  /* registration for CD_MACHINE_HP*/
  ssRegDlgParamAsRunTimeParam(S, 7, 7, rtParamNames[7], SS_UINT8);

  /* registration for CD_MATCH_DERATE_PERCENT*/
  ssRegDlgParamAsRunTimeParam(S, 8, 8, rtParamNames[8], SS_UINT8);

  /* registration for ENGINE_CRANKING*/
  ssRegDlgParamAsRunTimeParam(S, 9, 9, rtParamNames[9], SS_UINT8);

  /* registration for FAILURE*/
  ssRegDlgParamAsRunTimeParam(S, 10, 10, rtParamNames[10], SS_UINT8);

  /* registration for NON_FUNCTIONAL*/
  ssRegDlgParamAsRunTimeParam(S, 11, 11, rtParamNames[11], SS_UINT8);

  /* registration for NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 12, 12, rtParamNames[12], SS_UINT8);

  /* registration for SHUTDOWN*/
  ssRegDlgParamAsRunTimeParam(S, 13, 13, rtParamNames[13], SS_UINT8);

  /* registration for UNDEFINED*/
  ssRegDlgParamAsRunTimeParam(S, 14, 14, rtParamNames[14], SS_UINT8);

  /* registration for UNRESPONSIVE*/
  ssRegDlgParamAsRunTimeParam(S, 15, 15, rtParamNames[15], SS_UINT8);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetInputPortDirectFeedThrough(S, 4, 1);
  ssSetInputPortDirectFeedThrough(S, 5, 1);
  ssSetInputPortDirectFeedThrough(S, 6, 1);
  ssSetInputPortDirectFeedThrough(S, 7, 1);
  ssSetInputPortDirectFeedThrough(S, 8, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MX_Gateway_optimization_info(sim_mode_is_rtw_gen
      (S), sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      63);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,63,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 63);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,63);
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
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,63,9);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,63,5);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=5; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 9; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,63);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4206611857U));
  ssSetChecksum1(S,(1416155450U));
  ssSetChecksum2(S,(1967881130U));
  ssSetChecksum3(S,(1805004822U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c63_MX_Gateway(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c63_MX_Gateway(SimStruct *S)
{
  SFc63_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc63_MX_GatewayInstanceStruct *)utMalloc(sizeof
    (SFc63_MX_GatewayInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc63_MX_GatewayInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c63_MX_Gateway;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c63_MX_Gateway;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c63_MX_Gateway;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c63_MX_Gateway;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c63_MX_Gateway;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c63_MX_Gateway;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c63_MX_Gateway;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c63_MX_Gateway;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c63_MX_Gateway;
  chartInstance->chartInfo.mdlStart = mdlStart_c63_MX_Gateway;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c63_MX_Gateway;
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
  mdl_start_c63_MX_Gateway(chartInstance);
}

void c63_MX_Gateway_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c63_MX_Gateway(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c63_MX_Gateway(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c63_MX_Gateway(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c63_MX_Gateway_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
