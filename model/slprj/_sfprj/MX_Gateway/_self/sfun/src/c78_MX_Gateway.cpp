/* Include files */

#include "MX_Gateway_sfun.h"
#include "c78_MX_Gateway.h"
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
#define c78_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)
#define c78_IN_Init_Cal                ((uint8_T)1U)
#define c78_IN_Wait                    ((uint8_T)2U)
#define c78_IN_Init_Complete           ((uint8_T)1U)
#define c78_IN_Debounce                ((uint8_T)1U)
#define c78_IN_Fault                   ((uint8_T)2U)
#define c78_IN_Normal                  ((uint8_T)3U)
#define c78_IN_Cal_Check               ((uint8_T)1U)
#define c78_IN_Cal_In_Progress         ((uint8_T)2U)
#define c78_IN_Cal_Inhibit             ((uint8_T)3U)
#define c78_IN_Pos_High                ((uint8_T)1U)
#define c78_IN_Pos_Low                 ((uint8_T)2U)
#define c78_IN_Cal_Mode                ((uint8_T)1U)
#define c78_IN_Normal_Mode             ((uint8_T)2U)
#define c78_IN_Cal_Fail                ((uint8_T)1U)
#define c78_IN_Done                    ((uint8_T)2U)
#define c78_IN_EXTEND_ACTUATOR         ((uint8_T)3U)
#define c78_IN_INITIALIZE              ((uint8_T)4U)
#define c78_IN_RECORD_MAX              ((uint8_T)5U)
#define c78_IN_RECORD_MIN              ((uint8_T)6U)
#define c78_IN_RETRACT_ACTUATOR        ((uint8_T)7U)
#define c78_IN_VALIDATE_POLARITY       ((uint8_T)8U)
#define c78_IN_VALIDATE_RANGE          ((uint8_T)9U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance);
static void initialize_params_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance);
static void enable_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct *chartInstance);
static void disable_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct *chartInstance);
static void c78_update_debugger_state_c78_MX_Gateway
  (SFc78_MX_GatewayInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c78_MX_Gateway
  (SFc78_MX_GatewayInstanceStruct *chartInstance);
static void set_sim_state_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_st);
static void c78_set_sim_state_side_effects_c78_MX_Gateway
  (SFc78_MX_GatewayInstanceStruct *chartInstance);
static void finalize_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance);
static void sf_gateway_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance);
static void mdl_start_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance);
static void c78_chartstep_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance);
static void initSimStructsc78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance);
static void c78_Get_Cal_Values(SFc78_MX_GatewayInstanceStruct *chartInstance);
static void c78_Cal_Start(SFc78_MX_GatewayInstanceStruct *chartInstance);
static void c78_exit_internal_Cal_Check(SFc78_MX_GatewayInstanceStruct
  *chartInstance);
static void c78_Cal_Mode(SFc78_MX_GatewayInstanceStruct *chartInstance);
static void c78_exit_internal_Cal_Mode(SFc78_MX_GatewayInstanceStruct
  *chartInstance);
static void c78_VALIDATE_RANGE(SFc78_MX_GatewayInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c78_machineNumber, uint32_T
  c78_chartNumber, uint32_T c78_instanceNumber);
static const mxArray *c78_sf_marshallOut(void *chartInstanceVoid, void
  *c78_inData);
static int32_T c78_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_u, const emlrtMsgIdentifier *c78_parentId);
static void c78_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c78_mxArrayInData, const char_T *c78_varName, void *c78_outData);
static const mxArray *c78_b_sf_marshallOut(void *chartInstanceVoid, void
  *c78_inData);
static uint8_T c78_b_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_b_tp_Get_Cal_Values, const char_T
  *c78_identifier);
static uint8_T c78_c_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_u, const emlrtMsgIdentifier *c78_parentId);
static void c78_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c78_mxArrayInData, const char_T *c78_varName, void *c78_outData);
static const mxArray *c78_c_sf_marshallOut(void *chartInstanceVoid, void
  *c78_inData);
static uint16_T c78_d_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_b_CD_CAN_THROTTLE_CAL_DEADBAND, const
  char_T *c78_identifier);
static uint16_T c78_e_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_u, const emlrtMsgIdentifier *c78_parentId);
static void c78_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c78_mxArrayInData, const char_T *c78_varName, void *c78_outData);
static const mxArray *c78_d_sf_marshallOut(void *chartInstanceVoid, void
  *c78_inData);
static const mxArray *c78_f_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_b_setSimStateSideEffectsInfo, const char_T *
  c78_identifier);
static const mxArray *c78_g_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_u, const emlrtMsgIdentifier *c78_parentId);
static const mxArray *sf_get_hover_data_for_msg(SFc78_MX_GatewayInstanceStruct
  *chartInstance, int32_T c78_ssid);
static void c78_init_sf_message_store_memory(SFc78_MX_GatewayInstanceStruct
  *chartInstance);
static uint8_T c78__u8_s32_(SFc78_MX_GatewayInstanceStruct *chartInstance,
  int32_T c78_b, uint32_T c78_ssid_src_loc, int32_T c78_offset_src_loc, int32_T
  c78_length_src_loc);
static uint16_T c78__u16_s32_(SFc78_MX_GatewayInstanceStruct *chartInstance,
  int32_T c78_b, uint32_T c78_ssid_src_loc, int32_T c78_offset_src_loc, int32_T
  c78_length_src_loc);
static uint16_T c78__u16_u32_(SFc78_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c78_b, uint32_T c78_ssid_src_loc, int32_T c78_offset_src_loc, int32_T
  c78_length_src_loc);
static int32_T c78__s32_add__(SFc78_MX_GatewayInstanceStruct *chartInstance,
  int32_T c78_b, int32_T c78_c, uint32_T c78_ssid_src_loc, int32_T
  c78_offset_src_loc, int32_T c78_length_src_loc);
static uint16_T c78_get_ee_ThrottleCalExtended(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex);
static void c78_set_ee_ThrottleCalExtended(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex, uint16_T c78_elementValue);
static uint16_T *c78_access_ee_ThrottleCalExtended
  (SFc78_MX_GatewayInstanceStruct *chartInstance, uint32_T c78_rdOnly);
static uint16_T c78_get_ee_ThrottleCalRetracted(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex);
static void c78_set_ee_ThrottleCalRetracted(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex, uint16_T c78_elementValue);
static uint16_T *c78_access_ee_ThrottleCalRetracted
  (SFc78_MX_GatewayInstanceStruct *chartInstance, uint32_T c78_rdOnly);
static uint8_T c78_get_ee_ThrottleCalState(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex);
static void c78_set_ee_ThrottleCalState(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex, uint8_T c78_elementValue);
static uint8_T *c78_access_ee_ThrottleCalState(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_rdOnly);
static uint8_T c78_get_state_Buzzer(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex);
static void c78_set_state_Buzzer(SFc78_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c78_elementIndex, uint8_T c78_elementValue);
static uint8_T *c78_access_state_Buzzer(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_rdOnly);
static void init_dsm_address_info(SFc78_MX_GatewayInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc78_MX_GatewayInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc78_MX_Gateway(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c78_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c78_doSetSimStateSideEffects = 0U;
  chartInstance->c78_setSimStateSideEffectsInfo = NULL;
  chartInstance->c78_is_active_Cal_Start = 0U;
  chartInstance->c78_is_Cal_Start = c78_IN_NO_ACTIVE_CHILD;
  chartInstance->c78_tp_Cal_Start = 0U;
  chartInstance->c78_is_Cal_Check = c78_IN_NO_ACTIVE_CHILD;
  chartInstance->c78_tp_Cal_Check = 0U;
  chartInstance->c78_tp_Pos_High = 0U;
  chartInstance->c78_tp_Pos_Low = 0U;
  chartInstance->c78_tp_Cal_In_Progress = 0U;
  chartInstance->c78_tp_Cal_Inhibit = 0U;
  chartInstance->c78_temporalCounter_i1 = 0U;
  chartInstance->c78_is_active_Control = 0U;
  chartInstance->c78_is_Control = c78_IN_NO_ACTIVE_CHILD;
  chartInstance->c78_tp_Control = 0U;
  chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
  chartInstance->c78_tp_Cal_Mode = 0U;
  chartInstance->c78_tp_Cal_Fail = 0U;
  chartInstance->c78_tp_Done = 0U;
  chartInstance->c78_tp_EXTEND_ACTUATOR = 0U;
  chartInstance->c78_temporalCounter_i3 = 0U;
  chartInstance->c78_tp_INITIALIZE = 0U;
  chartInstance->c78_tp_RECORD_MAX = 0U;
  chartInstance->c78_temporalCounter_i3 = 0U;
  chartInstance->c78_tp_RECORD_MIN = 0U;
  chartInstance->c78_temporalCounter_i3 = 0U;
  chartInstance->c78_tp_RETRACT_ACTUATOR = 0U;
  chartInstance->c78_temporalCounter_i3 = 0U;
  chartInstance->c78_tp_VALIDATE_POLARITY = 0U;
  chartInstance->c78_tp_VALIDATE_RANGE = 0U;
  chartInstance->c78_tp_Normal_Mode = 0U;
  chartInstance->c78_is_active_Get_Cal_Values = 0U;
  chartInstance->c78_is_Get_Cal_Values = c78_IN_NO_ACTIVE_CHILD;
  chartInstance->c78_tp_Get_Cal_Values = 0U;
  chartInstance->c78_is_Init_Cal = c78_IN_NO_ACTIVE_CHILD;
  chartInstance->c78_tp_Init_Cal = 0U;
  chartInstance->c78_tp_Init_Complete = 0U;
  chartInstance->c78_tp_Wait = 0U;
  chartInstance->c78_is_active_Monitor = 0U;
  chartInstance->c78_is_Monitor = c78_IN_NO_ACTIVE_CHILD;
  chartInstance->c78_tp_Monitor = 0U;
  chartInstance->c78_tp_Debounce = 0U;
  chartInstance->c78_temporalCounter_i2 = 0U;
  chartInstance->c78_tp_Fault = 0U;
  chartInstance->c78_tp_Normal = 0U;
  chartInstance->c78_is_active_c78_MX_Gateway = 0U;
  chartInstance->c78_count = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c78_count, 0U);
  chartInstance->c78_previous_cal_state = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c78_previous_cal_state, 1U);
  chartInstance->c78_range = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c78_range, 2U);
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c78_cmd_CANThrottle = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c78_state_CANThrottle = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_state_CANThrottle, 11U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *chartInstance->c78_state_CANThrottleCalDiag = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_state_CANThrottleCalDiag,
                          12U);
  }
}

static void initialize_params_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  real_T c78_d0;
  real_T c78_d1;
  real_T c78_d2;
  real_T c78_d3;
  real_T c78_d4;
  real_T c78_d5;
  real_T c78_d6;
  real_T c78_d7;
  real_T c78_d8;
  real_T c78_d9;
  real_T c78_d10;
  real_T c78_d11;
  real_T c78_d12;
  real_T c78_d13;
  real_T c78_d14;
  real_T c78_d15;
  real_T c78_d16;
  sf_mex_import_named("CD_CAN_THROTTLE_CAL_DEADBAND", sf_mex_get_sfun_param
                      (chartInstance->S, 0, 0), &c78_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_CD_CAN_THROTTLE_CAL_DEADBAND = (uint16_T)c78_d0;
  sf_mex_import_named("CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT",
                      sf_mex_get_sfun_param(chartInstance->S, 2, 0), &c78_d1, 0,
                      0, 0U, 0, 0U, 0);
  chartInstance->c78_CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT = (uint16_T)c78_d1;
  sf_mex_import_named("CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT",
                      sf_mex_get_sfun_param(chartInstance->S, 7, 0), &c78_d2, 0,
                      0, 0U, 0, 0U, 0);
  chartInstance->c78_CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT = (uint16_T)c78_d2;
  sf_mex_import_named("CD_CAN_THROTTLE_CAL_DIAG_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 1, 0), &c78_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_CD_CAN_THROTTLE_CAL_DIAG_TIME = (uint16_T)c78_d3;
  sf_mex_import_named("CD_CAN_THROTTLE_CAL_MAX", sf_mex_get_sfun_param
                      (chartInstance->S, 3, 0), &c78_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_CD_CAN_THROTTLE_CAL_MAX = (uint16_T)c78_d4;
  sf_mex_import_named("CD_CAN_THROTTLE_CAL_MIN", sf_mex_get_sfun_param
                      (chartInstance->S, 4, 0), &c78_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_CD_CAN_THROTTLE_CAL_MIN = (uint16_T)c78_d5;
  sf_mex_import_named("CD_CAN_THROTTLE_CAL_RANGE_NOM", sf_mex_get_sfun_param
                      (chartInstance->S, 5, 0), &c78_d6, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_NOM = (uint16_T)c78_d6;
  sf_mex_import_named("CD_CAN_THROTTLE_CAL_RANGE_TOL", sf_mex_get_sfun_param
                      (chartInstance->S, 6, 0), &c78_d7, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_TOL = (uint16_T)c78_d7;
  sf_mex_import_named("CD_CAN_THROTTLE_DEBOUNCE_FAILURE", sf_mex_get_sfun_param
                      (chartInstance->S, 8, 0), &c78_d8, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_CD_CAN_THROTTLE_DEBOUNCE_FAILURE = (uint16_T)c78_d8;
  sf_mex_import_named("CD_CAN_THROTTLE_ERROR_MAX", sf_mex_get_sfun_param
                      (chartInstance->S, 9, 0), &c78_d9, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_CD_CAN_THROTTLE_ERROR_MAX = (uint16_T)c78_d9;
  sf_mex_import_named("DOUBLE_SHORT_BEEP", sf_mex_get_sfun_param
                      (chartInstance->S, 10, 0), &c78_d10, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_DOUBLE_SHORT_BEEP = (uint8_T)c78_d10;
  sf_mex_import_named("ENGINE_CRANKING", sf_mex_get_sfun_param(chartInstance->S,
    11, 0), &c78_d11, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_ENGINE_CRANKING = (uint8_T)c78_d11;
  sf_mex_import_named("ENGINE_RUNNING", sf_mex_get_sfun_param(chartInstance->S,
    12, 0), &c78_d12, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_ENGINE_RUNNING = (uint8_T)c78_d12;
  sf_mex_import_named("FAILURE", sf_mex_get_sfun_param(chartInstance->S, 13, 0),
                      &c78_d13, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_FAILURE = (uint8_T)c78_d13;
  sf_mex_import_named("IN_CAL_MODE", sf_mex_get_sfun_param(chartInstance->S, 14,
    0), &c78_d14, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_IN_CAL_MODE = (uint8_T)c78_d14;
  sf_mex_import_named("NORMAL", sf_mex_get_sfun_param(chartInstance->S, 15, 0),
                      &c78_d15, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_NORMAL = (uint8_T)c78_d15;
  sf_mex_import_named("NOT_CALIBRATED", sf_mex_get_sfun_param(chartInstance->S,
    16, 0), &c78_d16, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c78_NOT_CALIBRATED = (uint8_T)c78_d16;
}

static void enable_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c78_update_debugger_state_c78_MX_Gateway
  (SFc78_MX_GatewayInstanceStruct *chartInstance)
{
  uint32_T c78_prevAniVal;
  c78_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c78_is_active_c78_MX_Gateway == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 75U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_active_Get_Cal_Values == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Get_Cal_Values == c78_IN_Init_Cal) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Init_Cal == c78_IN_Init_Complete) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Get_Cal_Values == c78_IN_Wait) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_active_Monitor == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Monitor == c78_IN_Normal) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Monitor == c78_IN_Debounce) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Monitor == c78_IN_Fault) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_active_Cal_Start == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Start == c78_IN_Cal_Check) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Check == c78_IN_Pos_Low) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Check == c78_IN_Pos_High) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Start == c78_IN_Cal_Inhibit) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Start == c78_IN_Cal_In_Progress) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_active_Control == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Control == c78_IN_Normal_Mode) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Control == c78_IN_Cal_Mode) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Mode == c78_IN_Cal_Fail) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Mode == c78_IN_INITIALIZE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Mode == c78_IN_EXTEND_ACTUATOR) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Mode == c78_IN_RECORD_MAX) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Mode == c78_IN_RETRACT_ACTUATOR) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Mode == c78_IN_RECORD_MIN) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Mode == c78_IN_VALIDATE_POLARITY) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Mode == c78_IN_VALIDATE_RANGE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c78_sfEvent);
  }

  if (chartInstance->c78_is_Cal_Mode == c78_IN_Done) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c78_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c78_sfEvent);
  }

  _SFD_SET_ANIMATION(c78_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c78_MX_Gateway
  (SFc78_MX_GatewayInstanceStruct *chartInstance)
{
  const mxArray *c78_st;
  const mxArray *c78_y = NULL;
  uint16_T c78_hoistedGlobal;
  const mxArray *c78_b_y = NULL;
  uint8_T c78_b_hoistedGlobal;
  const mxArray *c78_c_y = NULL;
  uint8_T c78_c_hoistedGlobal;
  const mxArray *c78_d_y = NULL;
  uint8_T c78_d_hoistedGlobal;
  const mxArray *c78_e_y = NULL;
  uint8_T c78_e_hoistedGlobal;
  const mxArray *c78_f_y = NULL;
  uint16_T c78_f_hoistedGlobal;
  const mxArray *c78_g_y = NULL;
  uint8_T c78_g_hoistedGlobal;
  const mxArray *c78_h_y = NULL;
  uint8_T c78_h_hoistedGlobal;
  const mxArray *c78_i_y = NULL;
  uint8_T c78_i_hoistedGlobal;
  const mxArray *c78_j_y = NULL;
  uint8_T c78_j_hoistedGlobal;
  const mxArray *c78_k_y = NULL;
  uint8_T c78_k_hoistedGlobal;
  const mxArray *c78_l_y = NULL;
  uint8_T c78_l_hoistedGlobal;
  const mxArray *c78_m_y = NULL;
  uint8_T c78_m_hoistedGlobal;
  const mxArray *c78_n_y = NULL;
  uint8_T c78_n_hoistedGlobal;
  const mxArray *c78_o_y = NULL;
  uint8_T c78_o_hoistedGlobal;
  const mxArray *c78_p_y = NULL;
  uint8_T c78_p_hoistedGlobal;
  const mxArray *c78_q_y = NULL;
  uint8_T c78_q_hoistedGlobal;
  const mxArray *c78_r_y = NULL;
  uint8_T c78_r_hoistedGlobal;
  const mxArray *c78_s_y = NULL;
  uint16_T c78_s_hoistedGlobal;
  const mxArray *c78_t_y = NULL;
  uint16_T c78_t_hoistedGlobal;
  const mxArray *c78_u_y = NULL;
  uint8_T c78_u_hoistedGlobal;
  const mxArray *c78_v_y = NULL;
  c78_st = NULL;
  c78_st = NULL;
  c78_y = NULL;
  sf_mex_assign(&c78_y, sf_mex_createcellmatrix(21, 1), false);
  c78_hoistedGlobal = *chartInstance->c78_cmd_CANThrottle;
  c78_b_y = NULL;
  sf_mex_assign(&c78_b_y, sf_mex_create("y", &c78_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 0, c78_b_y);
  c78_b_hoistedGlobal = *chartInstance->c78_state_CANThrottle;
  c78_c_y = NULL;
  sf_mex_assign(&c78_c_y, sf_mex_create("y", &c78_b_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 1, c78_c_y);
  c78_c_hoistedGlobal = *chartInstance->c78_state_CANThrottleCalDiag;
  c78_d_y = NULL;
  sf_mex_assign(&c78_d_y, sf_mex_create("y", &c78_c_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 2, c78_d_y);
  c78_d_hoistedGlobal = chartInstance->c78_count;
  c78_e_y = NULL;
  sf_mex_assign(&c78_e_y, sf_mex_create("y", &c78_d_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 3, c78_e_y);
  c78_e_hoistedGlobal = chartInstance->c78_previous_cal_state;
  c78_f_y = NULL;
  sf_mex_assign(&c78_f_y, sf_mex_create("y", &c78_e_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 4, c78_f_y);
  c78_f_hoistedGlobal = chartInstance->c78_range;
  c78_g_y = NULL;
  sf_mex_assign(&c78_g_y, sf_mex_create("y", &c78_f_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 5, c78_g_y);
  c78_g_hoistedGlobal = chartInstance->c78_is_active_c78_MX_Gateway;
  c78_h_y = NULL;
  sf_mex_assign(&c78_h_y, sf_mex_create("y", &c78_g_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 6, c78_h_y);
  c78_h_hoistedGlobal = chartInstance->c78_is_active_Cal_Start;
  c78_i_y = NULL;
  sf_mex_assign(&c78_i_y, sf_mex_create("y", &c78_h_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 7, c78_i_y);
  c78_i_hoistedGlobal = chartInstance->c78_is_active_Control;
  c78_j_y = NULL;
  sf_mex_assign(&c78_j_y, sf_mex_create("y", &c78_i_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 8, c78_j_y);
  c78_j_hoistedGlobal = chartInstance->c78_is_active_Monitor;
  c78_k_y = NULL;
  sf_mex_assign(&c78_k_y, sf_mex_create("y", &c78_j_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 9, c78_k_y);
  c78_k_hoistedGlobal = chartInstance->c78_is_active_Get_Cal_Values;
  c78_l_y = NULL;
  sf_mex_assign(&c78_l_y, sf_mex_create("y", &c78_k_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 10, c78_l_y);
  c78_l_hoistedGlobal = chartInstance->c78_is_Cal_Start;
  c78_m_y = NULL;
  sf_mex_assign(&c78_m_y, sf_mex_create("y", &c78_l_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 11, c78_m_y);
  c78_m_hoistedGlobal = chartInstance->c78_is_Cal_Check;
  c78_n_y = NULL;
  sf_mex_assign(&c78_n_y, sf_mex_create("y", &c78_m_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 12, c78_n_y);
  c78_n_hoistedGlobal = chartInstance->c78_is_Cal_Mode;
  c78_o_y = NULL;
  sf_mex_assign(&c78_o_y, sf_mex_create("y", &c78_n_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 13, c78_o_y);
  c78_o_hoistedGlobal = chartInstance->c78_is_Control;
  c78_p_y = NULL;
  sf_mex_assign(&c78_p_y, sf_mex_create("y", &c78_o_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 14, c78_p_y);
  c78_p_hoistedGlobal = chartInstance->c78_is_Monitor;
  c78_q_y = NULL;
  sf_mex_assign(&c78_q_y, sf_mex_create("y", &c78_p_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 15, c78_q_y);
  c78_q_hoistedGlobal = chartInstance->c78_is_Get_Cal_Values;
  c78_r_y = NULL;
  sf_mex_assign(&c78_r_y, sf_mex_create("y", &c78_q_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 16, c78_r_y);
  c78_r_hoistedGlobal = chartInstance->c78_is_Init_Cal;
  c78_s_y = NULL;
  sf_mex_assign(&c78_s_y, sf_mex_create("y", &c78_r_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 17, c78_s_y);
  c78_s_hoistedGlobal = chartInstance->c78_temporalCounter_i1;
  c78_t_y = NULL;
  sf_mex_assign(&c78_t_y, sf_mex_create("y", &c78_s_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 18, c78_t_y);
  c78_t_hoistedGlobal = chartInstance->c78_temporalCounter_i2;
  c78_u_y = NULL;
  sf_mex_assign(&c78_u_y, sf_mex_create("y", &c78_t_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 19, c78_u_y);
  c78_u_hoistedGlobal = chartInstance->c78_temporalCounter_i3;
  c78_v_y = NULL;
  sf_mex_assign(&c78_v_y, sf_mex_create("y", &c78_u_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c78_y, 20, c78_v_y);
  sf_mex_assign(&c78_st, c78_y, false);
  return c78_st;
}

static void set_sim_state_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_st)
{
  const mxArray *c78_u;
  c78_u = sf_mex_dup(c78_st);
  *chartInstance->c78_cmd_CANThrottle = c78_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 0)), "cmd_CANThrottle");
  *chartInstance->c78_state_CANThrottle = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 1)), "state_CANThrottle");
  *chartInstance->c78_state_CANThrottleCalDiag = c78_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c78_u, 2)),
     "state_CANThrottleCalDiag");
  chartInstance->c78_count = c78_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c78_u, 3)), "count");
  chartInstance->c78_previous_cal_state = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 4)), "previous_cal_state");
  chartInstance->c78_range = c78_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c78_u, 5)), "range");
  chartInstance->c78_is_active_c78_MX_Gateway = c78_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c78_u, 6)),
     "is_active_c78_MX_Gateway");
  chartInstance->c78_is_active_Cal_Start = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 7)), "is_active_Cal_Start");
  chartInstance->c78_is_active_Control = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 8)), "is_active_Control");
  chartInstance->c78_is_active_Monitor = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 9)), "is_active_Monitor");
  chartInstance->c78_is_active_Get_Cal_Values = c78_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c78_u, 10)),
     "is_active_Get_Cal_Values");
  chartInstance->c78_is_Cal_Start = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 11)), "is_Cal_Start");
  chartInstance->c78_is_Cal_Check = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 12)), "is_Cal_Check");
  chartInstance->c78_is_Cal_Mode = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 13)), "is_Cal_Mode");
  chartInstance->c78_is_Control = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 14)), "is_Control");
  chartInstance->c78_is_Monitor = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 15)), "is_Monitor");
  chartInstance->c78_is_Get_Cal_Values = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 16)), "is_Get_Cal_Values");
  chartInstance->c78_is_Init_Cal = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 17)), "is_Init_Cal");
  chartInstance->c78_temporalCounter_i1 = c78_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 18)), "temporalCounter_i1");
  chartInstance->c78_temporalCounter_i2 = c78_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 19)), "temporalCounter_i2");
  chartInstance->c78_temporalCounter_i3 = c78_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c78_u, 20)), "temporalCounter_i3");
  sf_mex_assign(&chartInstance->c78_setSimStateSideEffectsInfo,
                c78_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c78_u, 21)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c78_u);
  chartInstance->c78_doSetSimStateSideEffects = 1U;
  c78_update_debugger_state_c78_MX_Gateway(chartInstance);
  sf_mex_destroy(&c78_st);
}

static void c78_set_sim_state_side_effects_c78_MX_Gateway
  (SFc78_MX_GatewayInstanceStruct *chartInstance)
{
  if (chartInstance->c78_doSetSimStateSideEffects != 0) {
    chartInstance->c78_tp_Get_Cal_Values = (uint8_T)
      (chartInstance->c78_is_active_Get_Cal_Values == 1U);
    chartInstance->c78_tp_Init_Cal = (uint8_T)
      (chartInstance->c78_is_Get_Cal_Values == c78_IN_Init_Cal);
    chartInstance->c78_tp_Init_Complete = (uint8_T)
      (chartInstance->c78_is_Init_Cal == c78_IN_Init_Complete);
    chartInstance->c78_tp_Wait = (uint8_T)(chartInstance->c78_is_Get_Cal_Values ==
      c78_IN_Wait);
    chartInstance->c78_tp_Cal_Start = (uint8_T)
      (chartInstance->c78_is_active_Cal_Start == 1U);
    chartInstance->c78_tp_Cal_Check = (uint8_T)(chartInstance->c78_is_Cal_Start ==
      c78_IN_Cal_Check);
    chartInstance->c78_tp_Pos_High = (uint8_T)(chartInstance->c78_is_Cal_Check ==
      c78_IN_Pos_High);
    chartInstance->c78_tp_Pos_Low = (uint8_T)(chartInstance->c78_is_Cal_Check ==
      c78_IN_Pos_Low);
    chartInstance->c78_tp_Cal_In_Progress = (uint8_T)
      (chartInstance->c78_is_Cal_Start == c78_IN_Cal_In_Progress);
    if (chartInstance->c78_is_Cal_Start == c78_IN_Cal_Inhibit) {
      chartInstance->c78_tp_Cal_Inhibit = 1U;
      if (sf_mex_sub(chartInstance->c78_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 11) == 0.0) {
        chartInstance->c78_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c78_tp_Cal_Inhibit = 0U;
    }

    chartInstance->c78_tp_Monitor = (uint8_T)
      (chartInstance->c78_is_active_Monitor == 1U);
    if (chartInstance->c78_is_Monitor == c78_IN_Debounce) {
      chartInstance->c78_tp_Debounce = 1U;
      if (sf_mex_sub(chartInstance->c78_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 13) == 0.0) {
        chartInstance->c78_temporalCounter_i2 = 0U;
      }
    } else {
      chartInstance->c78_tp_Debounce = 0U;
    }

    chartInstance->c78_tp_Fault = (uint8_T)(chartInstance->c78_is_Monitor ==
      c78_IN_Fault);
    chartInstance->c78_tp_Normal = (uint8_T)(chartInstance->c78_is_Monitor ==
      c78_IN_Normal);
    chartInstance->c78_tp_Control = (uint8_T)
      (chartInstance->c78_is_active_Control == 1U);
    chartInstance->c78_tp_Cal_Mode = (uint8_T)(chartInstance->c78_is_Control ==
      c78_IN_Cal_Mode);
    chartInstance->c78_tp_Cal_Fail = (uint8_T)(chartInstance->c78_is_Cal_Mode ==
      c78_IN_Cal_Fail);
    chartInstance->c78_tp_Done = (uint8_T)(chartInstance->c78_is_Cal_Mode ==
      c78_IN_Done);
    if (chartInstance->c78_is_Cal_Mode == c78_IN_EXTEND_ACTUATOR) {
      chartInstance->c78_tp_EXTEND_ACTUATOR = 1U;
      if (sf_mex_sub(chartInstance->c78_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 20) == 0.0) {
        chartInstance->c78_temporalCounter_i3 = 0U;
      }
    } else {
      chartInstance->c78_tp_EXTEND_ACTUATOR = 0U;
    }

    chartInstance->c78_tp_INITIALIZE = (uint8_T)(chartInstance->c78_is_Cal_Mode ==
      c78_IN_INITIALIZE);
    if (chartInstance->c78_is_Cal_Mode == c78_IN_RECORD_MAX) {
      chartInstance->c78_tp_RECORD_MAX = 1U;
      if (sf_mex_sub(chartInstance->c78_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 22) == 0.0) {
        chartInstance->c78_temporalCounter_i3 = 0U;
      }
    } else {
      chartInstance->c78_tp_RECORD_MAX = 0U;
    }

    if (chartInstance->c78_is_Cal_Mode == c78_IN_RECORD_MIN) {
      chartInstance->c78_tp_RECORD_MIN = 1U;
      if (sf_mex_sub(chartInstance->c78_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 23) == 0.0) {
        chartInstance->c78_temporalCounter_i3 = 0U;
      }
    } else {
      chartInstance->c78_tp_RECORD_MIN = 0U;
    }

    if (chartInstance->c78_is_Cal_Mode == c78_IN_RETRACT_ACTUATOR) {
      chartInstance->c78_tp_RETRACT_ACTUATOR = 1U;
      if (sf_mex_sub(chartInstance->c78_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 24) == 0.0) {
        chartInstance->c78_temporalCounter_i3 = 0U;
      }
    } else {
      chartInstance->c78_tp_RETRACT_ACTUATOR = 0U;
    }

    chartInstance->c78_tp_VALIDATE_POLARITY = (uint8_T)
      (chartInstance->c78_is_Cal_Mode == c78_IN_VALIDATE_POLARITY);
    chartInstance->c78_tp_VALIDATE_RANGE = (uint8_T)
      (chartInstance->c78_is_Cal_Mode == c78_IN_VALIDATE_RANGE);
    chartInstance->c78_tp_Normal_Mode = (uint8_T)(chartInstance->c78_is_Control ==
      c78_IN_Normal_Mode);
    chartInstance->c78_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c78_setSimStateSideEffectsInfo);
}

static void sf_gateway_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  c78_set_sim_state_side_effects_c78_MX_Gateway(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 75U, chartInstance->c78_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_scaled_ThrottlePos, 9U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_pos_Throttle, 8U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_state_CommThrottle, 7U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_state_Engine, 6U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_flag_InitEERead, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_fdbk_CANThrottle, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_pos_Error, 3U);
  chartInstance->c78_sfEvent = CALL_EVENT;
  if (chartInstance->c78_temporalCounter_i1 < 65535U) {
    chartInstance->c78_temporalCounter_i1 = c78__u16_s32_(chartInstance,
      chartInstance->c78_temporalCounter_i1 + 1, 0U, 0U, 0U);
  }

  if (chartInstance->c78_temporalCounter_i2 < 65535U) {
    chartInstance->c78_temporalCounter_i2 = c78__u16_s32_(chartInstance,
      chartInstance->c78_temporalCounter_i2 + 1, 0U, 0U, 0U);
  }

  if (chartInstance->c78_temporalCounter_i3 < 31U) {
    chartInstance->c78_temporalCounter_i3 = c78__u8_s32_(chartInstance,
      chartInstance->c78_temporalCounter_i3 + 1, 0U, 0U, 0U);
  }

  c78_chartstep_c78_MX_Gateway(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MX_GatewayMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  c78_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void c78_chartstep_c78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  boolean_T c78_temp;
  boolean_T c78_b_temp;
  boolean_T c78_out;
  boolean_T c78_b_out;
  uint16_T c78_u0;
  boolean_T c78_c_out;
  boolean_T c78_d_out;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 75U, chartInstance->c78_sfEvent);
  if (chartInstance->c78_is_active_c78_MX_Gateway == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 75U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_active_c78_MX_Gateway = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 75U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_active_Get_Cal_Values = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Get_Cal_Values = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_Get_Cal_Values = c78_IN_Wait;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Wait = 1U;
    chartInstance->c78_is_active_Cal_Start = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Cal_Start = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_Cal_Start = c78_IN_Cal_Check;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Cal_Check = 1U;
    *chartInstance->c78_state_CANThrottleCalDiag = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_state_CANThrottleCalDiag,
                          12U);
    chartInstance->c78_count = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c78_count, 0U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_Cal_Check = c78_IN_Pos_Low;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Pos_Low = 1U;
    chartInstance->c78_is_active_Monitor = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Monitor = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 33U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_Monitor = c78_IN_Normal;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Normal = 1U;
    *chartInstance->c78_state_CANThrottle = chartInstance->c78_NORMAL;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_state_CANThrottle, 11U);
    chartInstance->c78_is_active_Control = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Control = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 28U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_Control = c78_IN_Normal_Mode;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Normal_Mode = 1U;
    *chartInstance->c78_cmd_CANThrottle = *chartInstance->c78_scaled_ThrottlePos;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
  } else {
    c78_Get_Cal_Values(chartInstance);
    c78_Cal_Start(chartInstance);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 22U,
                 chartInstance->c78_sfEvent);
    switch (chartInstance->c78_is_Monitor) {
     case c78_IN_Debounce:
      CV_STATE_EVAL(22, 0, c78_IN_Debounce);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 35U,
                   chartInstance->c78_sfEvent);
      c78_temp = (_SFD_CCP_CALL(5U, 35U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        35U, 0, (real_T)*chartInstance->c78_pos_Error, (real_T)
        chartInstance->c78_CD_CAN_THROTTLE_ERROR_MAX, 0, 2U,
        *chartInstance->c78_pos_Error <
        chartInstance->c78_CD_CAN_THROTTLE_ERROR_MAX) != 0U,
        chartInstance->c78_sfEvent) != 0U);
      if (!c78_temp) {
        c78_temp = (_SFD_CCP_CALL(5U, 35U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          35U, 1, (real_T)c78_get_ee_ThrottleCalState(chartInstance, 0), (real_T)
          chartInstance->c78_NORMAL, 0, 1U, c78_get_ee_ThrottleCalState
          (chartInstance, 0) != chartInstance->c78_NORMAL) != 0U,
          chartInstance->c78_sfEvent) != 0U);
      }

      c78_out = (CV_TRANSITION_EVAL(35U, (int32_T)c78_temp) != 0);
      if (c78_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 35U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_Debounce = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Monitor = c78_IN_Normal;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_Normal = 1U;
        *chartInstance->c78_state_CANThrottle = chartInstance->c78_NORMAL;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_state_CANThrottle, 11U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 36U,
                     chartInstance->c78_sfEvent);
        c78_u0 = c78__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
          ((uint32_T)chartInstance->c78_CD_CAN_THROTTLE_DEBOUNCE_FAILURE, 16U,
           36U), 93U, 1U, 5U);
        c78_c_out = (CV_TRANSITION_EVAL(36U, (int32_T)(_SFD_CCP_CALL(5U, 36U, 0,
          (chartInstance->c78_temporalCounter_i2 >= c78_u0) != 0U,
          chartInstance->c78_sfEvent) != 0U)) != 0);
        if (c78_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 36U, chartInstance->c78_sfEvent);
          chartInstance->c78_tp_Debounce = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c78_sfEvent);
          chartInstance->c78_is_Monitor = c78_IN_Fault;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c78_sfEvent);
          chartInstance->c78_tp_Fault = 1U;
          *chartInstance->c78_state_CANThrottle = chartInstance->c78_FAILURE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_state_CANThrottle,
                                11U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 23U,
                       chartInstance->c78_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 23U, chartInstance->c78_sfEvent);
      break;

     case c78_IN_Fault:
      CV_STATE_EVAL(22, 0, c78_IN_Fault);
      *chartInstance->c78_state_CANThrottle = chartInstance->c78_FAILURE;
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 24U,
                   chartInstance->c78_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 24U, chartInstance->c78_sfEvent);
      break;

     case c78_IN_Normal:
      CV_STATE_EVAL(22, 0, c78_IN_Normal);
      *chartInstance->c78_state_CANThrottle = chartInstance->c78_NORMAL;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 34U,
                   chartInstance->c78_sfEvent);
      c78_b_temp = (_SFD_CCP_CALL(5U, 34U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        34U, 0, (real_T)*chartInstance->c78_pos_Error, (real_T)
        chartInstance->c78_CD_CAN_THROTTLE_ERROR_MAX, 0, 4U,
        *chartInstance->c78_pos_Error >
        chartInstance->c78_CD_CAN_THROTTLE_ERROR_MAX) != 0U,
        chartInstance->c78_sfEvent) != 0U);
      if (c78_b_temp) {
        c78_b_temp = (_SFD_CCP_CALL(5U, 34U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          34U, 1, (real_T)c78_get_ee_ThrottleCalState(chartInstance, 0), (real_T)
          chartInstance->c78_NORMAL, 0, 0U, c78_get_ee_ThrottleCalState
          (chartInstance, 0) == chartInstance->c78_NORMAL) != 0U,
          chartInstance->c78_sfEvent) != 0U);
      }

      c78_b_out = (CV_TRANSITION_EVAL(34U, (int32_T)c78_b_temp) != 0);
      if (c78_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 34U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_Normal = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Monitor = c78_IN_Debounce;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c78_sfEvent);
        chartInstance->c78_temporalCounter_i2 = 0U;
        chartInstance->c78_tp_Debounce = 1U;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 25U,
                     chartInstance->c78_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 25U, chartInstance->c78_sfEvent);
      break;

     default:
      CV_STATE_EVAL(22, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c78_is_Monitor = c78_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c78_sfEvent);
      break;
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 22U, chartInstance->c78_sfEvent);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U, chartInstance->c78_sfEvent);
    switch (chartInstance->c78_is_Control) {
     case c78_IN_Cal_Mode:
      CV_STATE_EVAL(6, 0, c78_IN_Cal_Mode);
      c78_Cal_Mode(chartInstance);
      break;

     case c78_IN_Normal_Mode:
      CV_STATE_EVAL(6, 0, c78_IN_Normal_Mode);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 26U,
                   chartInstance->c78_sfEvent);
      c78_d_out = (CV_TRANSITION_EVAL(26U, (int32_T)(_SFD_CCP_CALL(5U, 26U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 26U, 0, (real_T)
        c78_get_ee_ThrottleCalState(chartInstance, 0), (real_T)
        chartInstance->c78_IN_CAL_MODE, 0, 0U, c78_get_ee_ThrottleCalState
        (chartInstance, 0) == chartInstance->c78_IN_CAL_MODE) != 0U,
        chartInstance->c78_sfEvent) != 0U)) != 0);
      if (c78_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 26U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_Normal_Mode = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Control = c78_IN_Cal_Mode;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_Cal_Mode = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Cal_Mode = c78_IN_INITIALIZE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_INITIALIZE = 1U;
        *chartInstance->c78_cmd_CANThrottle = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
        c78_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c78_DOUBLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 3);
        chartInstance->c78_previous_cal_state = c78_get_ee_ThrottleCalState
          (chartInstance, 0);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c78_previous_cal_state, 1U);
        c78_set_ee_ThrottleCalState(chartInstance, 0,
          chartInstance->c78_IN_CAL_MODE);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        matlab_UpdateEEVar();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 17U,
                     chartInstance->c78_sfEvent);
        *chartInstance->c78_cmd_CANThrottle =
          *chartInstance->c78_scaled_ThrottlePos;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c78_sfEvent);
      break;

     default:
      CV_STATE_EVAL(6, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c78_is_Control = c78_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c78_sfEvent);
      break;
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c78_sfEvent);
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 75U, chartInstance->c78_sfEvent);
}

static void initSimStructsc78_MX_Gateway(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c78_Get_Cal_Values(SFc78_MX_GatewayInstanceStruct *chartInstance)
{
  boolean_T c78_out;
  boolean_T c78_temp;
  boolean_T c78_b_temp;
  boolean_T c78_c_temp;
  boolean_T c78_b_out;
  boolean_T c78_d_temp;
  boolean_T c78_c_out;
  boolean_T guard1 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 18U, chartInstance->c78_sfEvent);
  switch (chartInstance->c78_is_Get_Cal_Values) {
   case c78_IN_Init_Cal:
    CV_STATE_EVAL(18, 0, c78_IN_Init_Cal);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 19U,
                 chartInstance->c78_sfEvent);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 20U,
                 chartInstance->c78_sfEvent);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 20U, chartInstance->c78_sfEvent);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 19U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_Wait:
    CV_STATE_EVAL(18, 0, c78_IN_Wait);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 14U,
                 chartInstance->c78_sfEvent);
    c78_out = (CV_TRANSITION_EVAL(14U, (int32_T)(_SFD_CCP_CALL(5U, 14U, 0,
      *chartInstance->c78_flag_InitEERead != 0U, chartInstance->c78_sfEvent) !=
      0U)) != 0);
    if (c78_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c78_sfEvent);
      chartInstance->c78_tp_Wait = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c78_sfEvent);
      chartInstance->c78_is_Get_Cal_Values = c78_IN_Init_Cal;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c78_sfEvent);
      chartInstance->c78_tp_Init_Cal = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c78_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 16U,
                   chartInstance->c78_sfEvent);
      c78_temp = (_SFD_CCP_CALL(5U, 16U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        16U, 0, (real_T)c78_get_ee_ThrottleCalState(chartInstance, 0), (real_T)
        chartInstance->c78_NORMAL, 0, 0U, c78_get_ee_ThrottleCalState
        (chartInstance, 0) == chartInstance->c78_NORMAL) != 0U,
        chartInstance->c78_sfEvent) != 0U);
      if (c78_temp) {
        c78_temp = (_SFD_CCP_CALL(5U, 16U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          16U, 1, (real_T)c78_get_ee_ThrottleCalExtended(chartInstance, 0),
          (real_T)c78_get_ee_ThrottleCalRetracted(chartInstance, 0), 0, 4U,
          c78_get_ee_ThrottleCalExtended(chartInstance, 0) >
          c78_get_ee_ThrottleCalRetracted(chartInstance, 0)) != 0U,
          chartInstance->c78_sfEvent) != 0U);
      }

      c78_b_temp = c78_temp;
      if (c78_temp) {
        c78_b_temp = (_SFD_CCP_CALL(5U, 16U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
          16U, 2, (real_T)c78_get_ee_ThrottleCalExtended(chartInstance, 0),
          (real_T)chartInstance->c78_CD_CAN_THROTTLE_CAL_MAX, 0, 2U,
          c78_get_ee_ThrottleCalExtended(chartInstance, 0) <
          chartInstance->c78_CD_CAN_THROTTLE_CAL_MAX) != 0U,
          chartInstance->c78_sfEvent) != 0U);
      }

      c78_c_temp = c78_b_temp;
      if (c78_b_temp) {
        c78_c_temp = (_SFD_CCP_CALL(5U, 16U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
          16U, 3, (real_T)c78_get_ee_ThrottleCalRetracted(chartInstance, 0),
          (real_T)chartInstance->c78_CD_CAN_THROTTLE_CAL_MIN, 0, 4U,
          c78_get_ee_ThrottleCalRetracted(chartInstance, 0) >
          chartInstance->c78_CD_CAN_THROTTLE_CAL_MIN) != 0U,
          chartInstance->c78_sfEvent) != 0U);
      }

      c78_b_out = (CV_TRANSITION_EVAL(16U, (int32_T)c78_c_temp) != 0);
      guard1 = false;
      if (c78_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c78_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c78_sfEvent);
        chartInstance->c78_range = c78__u16_s32_(chartInstance,
          c78_get_ee_ThrottleCalExtended(chartInstance, 0) -
          c78_get_ee_ThrottleCalRetracted(chartInstance, 0), 46U, 33U, 1U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c78_range, 2U);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 24U,
                     chartInstance->c78_sfEvent);
        c78_d_temp = (_SFD_CCP_CALL(5U, 24U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          24U, 0, (real_T)chartInstance->c78_range, (real_T)
          (chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_NOM +
           chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_TOL), 0, 2U,
          chartInstance->c78_range <
          chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_NOM +
          chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_TOL) != 0U,
          chartInstance->c78_sfEvent) != 0U);
        if (c78_d_temp) {
          c78_d_temp = (_SFD_CCP_CALL(5U, 24U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 24U, 1, (real_T)chartInstance->c78_range, (real_T)
             (chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_NOM -
              chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_TOL), 0, 4U,
             chartInstance->c78_range >
             chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_NOM -
             chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_TOL) != 0U,
            chartInstance->c78_sfEvent) != 0U);
        }

        c78_c_out = (CV_TRANSITION_EVAL(24U, (int32_T)c78_d_temp) != 0);
        if (c78_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c78_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 25U, chartInstance->c78_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c78_sfEvent);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 23U, chartInstance->c78_sfEvent);
          guard1 = true;
        }
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 22U, chartInstance->c78_sfEvent);
        guard1 = true;
      }

      if (guard1) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c78_sfEvent);
        c78_set_ee_ThrottleCalState(chartInstance, 0,
          chartInstance->c78_NOT_CALIBRATED);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        c78_set_ee_ThrottleCalExtended(chartInstance, 0,
          chartInstance->c78_CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        c78_set_ee_ThrottleCalRetracted(chartInstance, 0,
          chartInstance->c78_CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        matlab_UpdateEEVar();
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c78_sfEvent);
      chartInstance->c78_is_Init_Cal = c78_IN_Init_Complete;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c78_sfEvent);
      chartInstance->c78_tp_Init_Complete = 1U;
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 21U,
                   chartInstance->c78_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c78_sfEvent);
    break;

   default:
    CV_STATE_EVAL(18, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c78_is_Get_Cal_Values = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c78_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 18U, chartInstance->c78_sfEvent);
}

static void c78_Cal_Start(SFc78_MX_GatewayInstanceStruct *chartInstance)
{
  boolean_T c78_temp;
  boolean_T c78_b_temp;
  boolean_T c78_out;
  boolean_T c78_c_temp;
  boolean_T c78_b_out;
  boolean_T c78_d_temp;
  boolean_T c78_c_out;
  boolean_T c78_d_out;
  boolean_T c78_e_out;
  boolean_T c78_f_out;
  boolean_T guard1 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c78_sfEvent);
  switch (chartInstance->c78_is_Cal_Start) {
   case c78_IN_Cal_Check:
    CV_STATE_EVAL(0, 0, c78_IN_Cal_Check);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                 chartInstance->c78_sfEvent);
    c78_temp = (_SFD_CCP_CALL(5U, 3U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 3U, 0,
      (real_T)*chartInstance->c78_state_Engine, (real_T)
      chartInstance->c78_ENGINE_CRANKING, 0, 0U,
      *chartInstance->c78_state_Engine == chartInstance->c78_ENGINE_CRANKING) !=
      0U, chartInstance->c78_sfEvent) != 0U);
    if (!c78_temp) {
      c78_temp = (_SFD_CCP_CALL(5U, 3U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 3U,
        1, (real_T)*chartInstance->c78_state_Engine, (real_T)
        chartInstance->c78_ENGINE_RUNNING, 0, 0U,
        *chartInstance->c78_state_Engine == chartInstance->c78_ENGINE_RUNNING)
        != 0U, chartInstance->c78_sfEvent) != 0U);
    }

    c78_out = (CV_TRANSITION_EVAL(3U, (int32_T)c78_temp) != 0);
    if (c78_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c78_sfEvent);
      c78_exit_internal_Cal_Check(chartInstance);
      chartInstance->c78_tp_Cal_Check = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c78_sfEvent);
      chartInstance->c78_is_Cal_Start = c78_IN_Cal_Inhibit;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c78_sfEvent);
      chartInstance->c78_temporalCounter_i1 = 0U;
      chartInstance->c78_tp_Cal_Inhibit = 1U;
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U,
                   chartInstance->c78_sfEvent);
      c78_b_out = (CV_TRANSITION_EVAL(4U, (int32_T)(_SFD_CCP_CALL(5U, 4U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 4U, 0, (real_T)
        chartInstance->c78_count, 3.0, 0, 4U, chartInstance->c78_count > 3) !=
        0U, chartInstance->c78_sfEvent) != 0U)) != 0);
      if (c78_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c78_sfEvent);
        c78_exit_internal_Cal_Check(chartInstance);
        chartInstance->c78_tp_Cal_Check = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Cal_Start = c78_IN_Cal_In_Progress;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_Cal_In_Progress = 1U;
        c78_set_state_Buzzer(chartInstance, 0,
                             chartInstance->c78_DOUBLE_SHORT_BEEP);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 3);
        chartInstance->c78_previous_cal_state = c78_get_ee_ThrottleCalState
          (chartInstance, 0);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c78_previous_cal_state, 1U);
        c78_set_ee_ThrottleCalState(chartInstance, 0,
          chartInstance->c78_IN_CAL_MODE);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        matlab_UpdateEEVar();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                     chartInstance->c78_sfEvent);
        switch (chartInstance->c78_is_Cal_Check) {
         case c78_IN_Pos_High:
          CV_STATE_EVAL(1, 0, c78_IN_Pos_High);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                       chartInstance->c78_sfEvent);
          c78_d_out = (CV_TRANSITION_EVAL(2U, (int32_T)(_SFD_CCP_CALL(5U, 2U, 0,
            (boolean_T)CV_RELATIONAL_EVAL(5U, 2U, 0, (real_T)
            *chartInstance->c78_pos_Throttle, 475.0, 0, 2U,
            *chartInstance->c78_pos_Throttle < 475) != 0U,
            chartInstance->c78_sfEvent) != 0U)) != 0);
          if (c78_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c78_sfEvent);
            chartInstance->c78_tp_Pos_High = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c78_sfEvent);
            chartInstance->c78_is_Cal_Check = c78_IN_Pos_Low;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c78_sfEvent);
            chartInstance->c78_tp_Pos_Low = 1U;
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                         chartInstance->c78_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c78_sfEvent);
          break;

         case c78_IN_Pos_Low:
          CV_STATE_EVAL(1, 0, c78_IN_Pos_Low);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                       chartInstance->c78_sfEvent);
          c78_e_out = (CV_TRANSITION_EVAL(1U, (int32_T)(_SFD_CCP_CALL(5U, 1U, 0,
            (boolean_T)CV_RELATIONAL_EVAL(5U, 1U, 0, (real_T)
            *chartInstance->c78_pos_Throttle, 525.0, 0, 4U,
            *chartInstance->c78_pos_Throttle > 525) != 0U,
            chartInstance->c78_sfEvent) != 0U)) != 0);
          if (c78_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c78_sfEvent);
            chartInstance->c78_tp_Pos_Low = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c78_sfEvent);
            chartInstance->c78_is_Cal_Check = c78_IN_Pos_High;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c78_sfEvent);
            chartInstance->c78_tp_Pos_High = 1U;
            chartInstance->c78_count = c78__u8_s32_(chartInstance,
              c78__s32_add__(chartInstance, (int32_T)chartInstance->c78_count, 1,
                             4U, 13U, 7U), 4U, 13U, 7U);
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c78_count, 0U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                         chartInstance->c78_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c78_sfEvent);
          break;

         default:
          CV_STATE_EVAL(1, 0, 0);

          /* Unreachable state, for coverage only */
          chartInstance->c78_is_Cal_Check = c78_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c78_sfEvent);
          break;
        }
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_Cal_In_Progress:
    CV_STATE_EVAL(0, 0, c78_IN_Cal_In_Progress);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                 chartInstance->c78_sfEvent);
    c78_b_temp = (_SFD_CCP_CALL(5U, 11U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      11U, 0, (real_T)*chartInstance->c78_state_CommThrottle, (real_T)
      chartInstance->c78_NORMAL, 0, 1U, *chartInstance->c78_state_CommThrottle
      != chartInstance->c78_NORMAL) != 0U, chartInstance->c78_sfEvent) != 0U);
    if (!c78_b_temp) {
      c78_b_temp = (_SFD_CCP_CALL(5U, 11U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        11U, 1, (real_T)*chartInstance->c78_state_CANThrottle, (real_T)
        chartInstance->c78_NORMAL, 0, 1U, *chartInstance->c78_state_CANThrottle
        != chartInstance->c78_NORMAL) != 0U, chartInstance->c78_sfEvent) != 0U);
    }

    c78_c_temp = c78_b_temp;
    if (!c78_b_temp) {
      c78_c_temp = (_SFD_CCP_CALL(5U, 11U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        11U, 2, (real_T)*chartInstance->c78_state_Engine, (real_T)
        chartInstance->c78_ENGINE_CRANKING, 0, 0U,
        *chartInstance->c78_state_Engine == chartInstance->c78_ENGINE_CRANKING)
        != 0U, chartInstance->c78_sfEvent) != 0U);
    }

    c78_d_temp = c78_c_temp;
    if (!c78_c_temp) {
      c78_d_temp = (_SFD_CCP_CALL(5U, 11U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
        11U, 3, (real_T)*chartInstance->c78_state_Engine, (real_T)
        chartInstance->c78_ENGINE_RUNNING, 0, 0U,
        *chartInstance->c78_state_Engine == chartInstance->c78_ENGINE_RUNNING)
        != 0U, chartInstance->c78_sfEvent) != 0U);
    }

    c78_c_out = (CV_TRANSITION_EVAL(11U, (int32_T)c78_d_temp) != 0);
    guard1 = false;
    if (c78_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c78_sfEvent);
      c78_set_ee_ThrottleCalState(chartInstance, 0,
        chartInstance->c78_previous_cal_state);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
      matlab_UpdateEEVar();
      guard1 = true;
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 21U,
                   chartInstance->c78_sfEvent);
      c78_f_out = (CV_TRANSITION_EVAL(21U, (int32_T)(_SFD_CCP_CALL(5U, 21U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 21U, 0, (real_T)
        c78_get_ee_ThrottleCalState(chartInstance, 0), (real_T)
        chartInstance->c78_IN_CAL_MODE, 0, 1U, c78_get_ee_ThrottleCalState
        (chartInstance, 0) != chartInstance->c78_IN_CAL_MODE) != 0U,
        chartInstance->c78_sfEvent) != 0U)) != 0);
      if (c78_f_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c78_sfEvent);
        guard1 = true;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                     chartInstance->c78_sfEvent);
      }
    }

    if (guard1) {
      chartInstance->c78_tp_Cal_In_Progress = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c78_sfEvent);
      chartInstance->c78_is_Cal_Start = c78_IN_Cal_Inhibit;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c78_sfEvent);
      chartInstance->c78_temporalCounter_i1 = 0U;
      chartInstance->c78_tp_Cal_Inhibit = 1U;
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_Cal_Inhibit:
    CV_STATE_EVAL(0, 0, c78_IN_Cal_Inhibit);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U, chartInstance->c78_sfEvent);
    if (chartInstance->c78_temporalCounter_i1 >= c78__u16_u32_(chartInstance,
         _SFD_STATE_TEMPORAL_THRESHOLD((uint32_T)
          chartInstance->c78_CD_CAN_THROTTLE_CAL_DIAG_TIME, 16U, 5U), 8U, 15U,
         5U)) {
      CV_STATE_EVAL(5, 0, 2);
      *chartInstance->c78_state_CANThrottleCalDiag = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_state_CANThrottleCalDiag,
                            12U);
    } else {
      CV_STATE_EVAL(5, 0, 1);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c78_sfEvent);
    break;

   default:
    CV_STATE_EVAL(0, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c78_is_Cal_Start = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c78_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c78_sfEvent);
}

static void c78_exit_internal_Cal_Check(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c78_is_Cal_Check) {
   case c78_IN_Pos_High:
    CV_STATE_EVAL(1, 1, c78_IN_Pos_High);
    chartInstance->c78_tp_Pos_High = 0U;
    chartInstance->c78_is_Cal_Check = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_Pos_Low:
    CV_STATE_EVAL(1, 1, c78_IN_Pos_Low);
    chartInstance->c78_tp_Pos_Low = 0U;
    chartInstance->c78_is_Cal_Check = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c78_sfEvent);
    break;

   default:
    CV_STATE_EVAL(1, 1, 0);
    chartInstance->c78_is_Cal_Check = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c78_sfEvent);
    break;
  }
}

static void c78_Cal_Mode(SFc78_MX_GatewayInstanceStruct *chartInstance)
{
  boolean_T c78_temp;
  boolean_T c78_out;
  boolean_T c78_b_out;
  boolean_T c78_c_out;
  boolean_T c78_b_temp;
  boolean_T c78_c_temp;
  boolean_T c78_d_out;
  boolean_T c78_d_temp;
  boolean_T c78_e_out;
  boolean_T c78_f_out;
  boolean_T c78_g_out;
  boolean_T c78_h_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 27U, chartInstance->c78_sfEvent);
  c78_temp = (_SFD_CCP_CALL(5U, 27U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 27U, 0,
    (real_T)c78_get_ee_ThrottleCalState(chartInstance, 0), (real_T)
    chartInstance->c78_NOT_CALIBRATED, 0, 0U, c78_get_ee_ThrottleCalState
    (chartInstance, 0) == chartInstance->c78_NOT_CALIBRATED) != 0U,
    chartInstance->c78_sfEvent) != 0U);
  if (!c78_temp) {
    c78_temp = (_SFD_CCP_CALL(5U, 27U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 27U,
      1, (real_T)c78_get_ee_ThrottleCalState(chartInstance, 0), (real_T)
      chartInstance->c78_NORMAL, 0, 0U, c78_get_ee_ThrottleCalState
      (chartInstance, 0) == chartInstance->c78_NORMAL) != 0U,
      chartInstance->c78_sfEvent) != 0U);
  }

  c78_out = (CV_TRANSITION_EVAL(27U, (int32_T)c78_temp) != 0);
  if (c78_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 27U, chartInstance->c78_sfEvent);
    c78_exit_internal_Cal_Mode(chartInstance);
    chartInstance->c78_tp_Cal_Mode = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_Control = c78_IN_Normal_Mode;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Normal_Mode = 1U;
    *chartInstance->c78_cmd_CANThrottle = *chartInstance->c78_scaled_ThrottlePos;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U, chartInstance->c78_sfEvent);
    switch (chartInstance->c78_is_Cal_Mode) {
     case c78_IN_Cal_Fail:
      CV_STATE_EVAL(7, 0, c78_IN_Cal_Fail);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                   chartInstance->c78_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c78_sfEvent);
      break;

     case c78_IN_Done:
      CV_STATE_EVAL(7, 0, c78_IN_Done);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                   chartInstance->c78_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c78_sfEvent);
      break;

     case c78_IN_EXTEND_ACTUATOR:
      CV_STATE_EVAL(7, 0, c78_IN_EXTEND_ACTUATOR);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 9U,
                   chartInstance->c78_sfEvent);
      c78_b_out = (CV_TRANSITION_EVAL(9U, (int32_T)(_SFD_CCP_CALL(5U, 9U, 0,
        (chartInstance->c78_temporalCounter_i3 >= 20) != 0U,
        chartInstance->c78_sfEvent) != 0U)) != 0);
      if (c78_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_EXTEND_ACTUATOR = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Cal_Mode = c78_IN_RECORD_MAX;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c78_sfEvent);
        chartInstance->c78_temporalCounter_i3 = 0U;
        chartInstance->c78_tp_RECORD_MAX = 1U;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                     chartInstance->c78_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c78_sfEvent);
      break;

     case c78_IN_INITIALIZE:
      CV_STATE_EVAL(7, 0, c78_IN_INITIALIZE);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c78_sfEvent);
      chartInstance->c78_tp_INITIALIZE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c78_sfEvent);
      chartInstance->c78_is_Cal_Mode = c78_IN_EXTEND_ACTUATOR;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c78_sfEvent);
      chartInstance->c78_temporalCounter_i3 = 0U;
      chartInstance->c78_tp_EXTEND_ACTUATOR = 1U;
      *chartInstance->c78_cmd_CANThrottle = 1000U;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c78_sfEvent);
      break;

     case c78_IN_RECORD_MAX:
      CV_STATE_EVAL(7, 0, c78_IN_RECORD_MAX);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 29U,
                   chartInstance->c78_sfEvent);
      c78_c_out = (CV_TRANSITION_EVAL(29U, (int32_T)(_SFD_CCP_CALL(5U, 29U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 29U, 0, (real_T)
        *chartInstance->c78_fdbk_CANThrottle, (real_T)
        chartInstance->c78_CD_CAN_THROTTLE_CAL_MAX, 0, 4U,
        *chartInstance->c78_fdbk_CANThrottle >
        chartInstance->c78_CD_CAN_THROTTLE_CAL_MAX) != 0U,
        chartInstance->c78_sfEvent) != 0U)) != 0);
      if (c78_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 29U, chartInstance->c78_sfEvent);
        *chartInstance->c78_state_CANThrottleCalDiag = 1U;
        _SFD_DATA_RANGE_CHECK((real_T)
                              *chartInstance->c78_state_CANThrottleCalDiag, 12U);
        chartInstance->c78_tp_RECORD_MAX = 0U;
        _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 12U,
                     chartInstance->c78_sfEvent);
        c78_set_ee_ThrottleCalExtended(chartInstance, 0, c78__u16_s32_
          (chartInstance, *chartInstance->c78_fdbk_CANThrottle -
           chartInstance->c78_CD_CAN_THROTTLE_CAL_DEADBAND, 19U, 57U, 1U));
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        matlab_UpdateEEVar();
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c78_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Cal_Mode = c78_IN_Cal_Fail;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_Cal_Fail = 1U;
        *chartInstance->c78_cmd_CANThrottle = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
        c78_set_ee_ThrottleCalState(chartInstance, 0,
          chartInstance->c78_NOT_CALIBRATED);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        c78_set_ee_ThrottleCalExtended(chartInstance, 0,
          chartInstance->c78_CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        c78_set_ee_ThrottleCalRetracted(chartInstance, 0,
          chartInstance->c78_CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        matlab_UpdateEEVar();
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                     chartInstance->c78_sfEvent);
        c78_d_temp = (_SFD_CCP_CALL(5U, 8U, 0, true != 0U,
          chartInstance->c78_sfEvent) != 0U);
        if (c78_d_temp) {
          c78_d_temp = (_SFD_CCP_CALL(5U, 8U, 1,
            (chartInstance->c78_temporalCounter_i3 >= 10) != 0U,
            chartInstance->c78_sfEvent) != 0U);
        }

        c78_g_out = (CV_TRANSITION_EVAL(8U, (int32_T)c78_d_temp) != 0);
        if (c78_g_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c78_sfEvent);
          chartInstance->c78_tp_RECORD_MAX = 0U;
          _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 12U,
                       chartInstance->c78_sfEvent);
          c78_set_ee_ThrottleCalExtended(chartInstance, 0, c78__u16_s32_
            (chartInstance, *chartInstance->c78_fdbk_CANThrottle -
             chartInstance->c78_CD_CAN_THROTTLE_CAL_DEADBAND, 19U, 57U, 1U));
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          matlab_UpdateEEVar();
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c78_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c78_sfEvent);
          chartInstance->c78_is_Cal_Mode = c78_IN_RETRACT_ACTUATOR;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c78_sfEvent);
          chartInstance->c78_temporalCounter_i3 = 0U;
          chartInstance->c78_tp_RETRACT_ACTUATOR = 1U;
          *chartInstance->c78_cmd_CANThrottle = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                       chartInstance->c78_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c78_sfEvent);
      break;

     case c78_IN_RECORD_MIN:
      CV_STATE_EVAL(7, 0, c78_IN_RECORD_MIN);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                   chartInstance->c78_sfEvent);
      c78_b_temp = (_SFD_CCP_CALL(5U, 7U, 0, true != 0U,
        chartInstance->c78_sfEvent) != 0U);
      if (c78_b_temp) {
        c78_b_temp = (_SFD_CCP_CALL(5U, 7U, 1,
          (chartInstance->c78_temporalCounter_i3 >= 10) != 0U,
          chartInstance->c78_sfEvent) != 0U);
      }

      c78_e_out = (CV_TRANSITION_EVAL(7U, (int32_T)c78_b_temp) != 0);
      if (c78_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_RECORD_MIN = 0U;
        _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 13U,
                     chartInstance->c78_sfEvent);
        c78_set_ee_ThrottleCalRetracted(chartInstance, 0, c78__u16_s32_
          (chartInstance, *chartInstance->c78_fdbk_CANThrottle +
           chartInstance->c78_CD_CAN_THROTTLE_CAL_DEADBAND, 18U, 58U, 1U));
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        matlab_UpdateEEVar();
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c78_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Cal_Mode = c78_IN_VALIDATE_POLARITY;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_VALIDATE_POLARITY = 1U;
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 30U,
                     chartInstance->c78_sfEvent);
        c78_h_out = (CV_TRANSITION_EVAL(30U, (int32_T)(_SFD_CCP_CALL(5U, 30U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 30U, 0, (real_T)
          *chartInstance->c78_fdbk_CANThrottle, (real_T)
          chartInstance->c78_CD_CAN_THROTTLE_CAL_MIN, 0, 2U,
          *chartInstance->c78_fdbk_CANThrottle <
          chartInstance->c78_CD_CAN_THROTTLE_CAL_MIN) != 0U,
          chartInstance->c78_sfEvent) != 0U)) != 0);
        if (c78_h_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 30U, chartInstance->c78_sfEvent);
          *chartInstance->c78_state_CANThrottleCalDiag = 2U;
          _SFD_DATA_RANGE_CHECK((real_T)
                                *chartInstance->c78_state_CANThrottleCalDiag,
                                12U);
          chartInstance->c78_tp_RECORD_MIN = 0U;
          _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 13U,
                       chartInstance->c78_sfEvent);
          c78_set_ee_ThrottleCalRetracted(chartInstance, 0, c78__u16_s32_
            (chartInstance, *chartInstance->c78_fdbk_CANThrottle +
             chartInstance->c78_CD_CAN_THROTTLE_CAL_DEADBAND, 18U, 58U, 1U));
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          matlab_UpdateEEVar();
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c78_sfEvent);
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c78_sfEvent);
          chartInstance->c78_is_Cal_Mode = c78_IN_Cal_Fail;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c78_sfEvent);
          chartInstance->c78_tp_Cal_Fail = 1U;
          *chartInstance->c78_cmd_CANThrottle = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
          c78_set_ee_ThrottleCalState(chartInstance, 0,
            chartInstance->c78_NOT_CALIBRATED);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
          c78_set_ee_ThrottleCalExtended(chartInstance, 0,
            chartInstance->c78_CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
          c78_set_ee_ThrottleCalRetracted(chartInstance, 0,
            chartInstance->c78_CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U,
                       chartInstance->c78_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c78_sfEvent);
      break;

     case c78_IN_RETRACT_ACTUATOR:
      CV_STATE_EVAL(7, 0, c78_IN_RETRACT_ACTUATOR);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                   chartInstance->c78_sfEvent);
      c78_c_temp = (_SFD_CCP_CALL(5U, 10U, 0, true != 0U,
        chartInstance->c78_sfEvent) != 0U);
      if (c78_c_temp) {
        c78_c_temp = (_SFD_CCP_CALL(5U, 10U, 1,
          (chartInstance->c78_temporalCounter_i3 >= 20) != 0U,
          chartInstance->c78_sfEvent) != 0U);
      }

      c78_f_out = (CV_TRANSITION_EVAL(10U, (int32_T)c78_c_temp) != 0);
      if (c78_f_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_RETRACT_ACTUATOR = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Cal_Mode = c78_IN_RECORD_MIN;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c78_sfEvent);
        chartInstance->c78_temporalCounter_i3 = 0U;
        chartInstance->c78_tp_RECORD_MIN = 1U;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 14U,
                     chartInstance->c78_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c78_sfEvent);
      break;

     case c78_IN_VALIDATE_POLARITY:
      CV_STATE_EVAL(7, 0, c78_IN_VALIDATE_POLARITY);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 38U,
                   chartInstance->c78_sfEvent);
      c78_d_out = (CV_TRANSITION_EVAL(38U, (int32_T)(_SFD_CCP_CALL(5U, 38U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 38U, 0, (real_T)
        c78_get_ee_ThrottleCalExtended(chartInstance, 0), (real_T)
        c78_get_ee_ThrottleCalRetracted(chartInstance, 0), 0, 3U,
        c78_get_ee_ThrottleCalExtended(chartInstance, 0) <=
        c78_get_ee_ThrottleCalRetracted(chartInstance, 0)) != 0U,
        chartInstance->c78_sfEvent) != 0U)) != 0);
      if (c78_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 38U, chartInstance->c78_sfEvent);
        *chartInstance->c78_state_CANThrottleCalDiag = 3U;
        _SFD_DATA_RANGE_CHECK((real_T)
                              *chartInstance->c78_state_CANThrottleCalDiag, 12U);
        chartInstance->c78_tp_VALIDATE_POLARITY = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Cal_Mode = c78_IN_Cal_Fail;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_Cal_Fail = 1U;
        *chartInstance->c78_cmd_CANThrottle = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
        c78_set_ee_ThrottleCalState(chartInstance, 0,
          chartInstance->c78_NOT_CALIBRATED);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
        c78_set_ee_ThrottleCalExtended(chartInstance, 0,
          chartInstance->c78_CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
        c78_set_ee_ThrottleCalRetracted(chartInstance, 0,
          chartInstance->c78_CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
        matlab_UpdateEEVar();
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 37U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_VALIDATE_POLARITY = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c78_sfEvent);
        chartInstance->c78_is_Cal_Mode = c78_IN_VALIDATE_RANGE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c78_sfEvent);
        chartInstance->c78_tp_VALIDATE_RANGE = 1U;
        chartInstance->c78_range = c78__u16_s32_(chartInstance,
          c78_get_ee_ThrottleCalExtended(chartInstance, 0) -
          c78_get_ee_ThrottleCalRetracted(chartInstance, 0), 17U, 50U, 1U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c78_range, 2U);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c78_sfEvent);
      break;

     case c78_IN_VALIDATE_RANGE:
      CV_STATE_EVAL(7, 0, c78_IN_VALIDATE_RANGE);
      c78_VALIDATE_RANGE(chartInstance);
      break;

     default:
      CV_STATE_EVAL(7, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c78_sfEvent);
      break;
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c78_sfEvent);
}

static void c78_exit_internal_Cal_Mode(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c78_is_Cal_Mode) {
   case c78_IN_Cal_Fail:
    CV_STATE_EVAL(7, 1, c78_IN_Cal_Fail);
    chartInstance->c78_tp_Cal_Fail = 0U;
    chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_Done:
    CV_STATE_EVAL(7, 1, c78_IN_Done);
    chartInstance->c78_tp_Done = 0U;
    chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_EXTEND_ACTUATOR:
    CV_STATE_EVAL(7, 1, c78_IN_EXTEND_ACTUATOR);
    chartInstance->c78_tp_EXTEND_ACTUATOR = 0U;
    chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_INITIALIZE:
    CV_STATE_EVAL(7, 1, c78_IN_INITIALIZE);
    chartInstance->c78_tp_INITIALIZE = 0U;
    chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_RECORD_MAX:
    CV_STATE_EVAL(7, 1, c78_IN_RECORD_MAX);
    chartInstance->c78_tp_RECORD_MAX = 0U;
    _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 12U, chartInstance->c78_sfEvent);
    c78_set_ee_ThrottleCalExtended(chartInstance, 0, c78__u16_s32_(chartInstance,
      *chartInstance->c78_fdbk_CANThrottle -
      chartInstance->c78_CD_CAN_THROTTLE_CAL_DEADBAND, 19U, 57U, 1U));
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    matlab_UpdateEEVar();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_RECORD_MIN:
    CV_STATE_EVAL(7, 1, c78_IN_RECORD_MIN);
    chartInstance->c78_tp_RECORD_MIN = 0U;
    _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 13U, chartInstance->c78_sfEvent);
    c78_set_ee_ThrottleCalRetracted(chartInstance, 0, c78__u16_s32_
      (chartInstance, *chartInstance->c78_fdbk_CANThrottle +
       chartInstance->c78_CD_CAN_THROTTLE_CAL_DEADBAND, 18U, 58U, 1U));
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
    matlab_UpdateEEVar();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_RETRACT_ACTUATOR:
    CV_STATE_EVAL(7, 1, c78_IN_RETRACT_ACTUATOR);
    chartInstance->c78_tp_RETRACT_ACTUATOR = 0U;
    chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_VALIDATE_POLARITY:
    CV_STATE_EVAL(7, 1, c78_IN_VALIDATE_POLARITY);
    chartInstance->c78_tp_VALIDATE_POLARITY = 0U;
    chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c78_sfEvent);
    break;

   case c78_IN_VALIDATE_RANGE:
    CV_STATE_EVAL(7, 1, c78_IN_VALIDATE_RANGE);
    chartInstance->c78_tp_VALIDATE_RANGE = 0U;
    chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c78_sfEvent);
    break;

   default:
    CV_STATE_EVAL(7, 1, 0);
    chartInstance->c78_is_Cal_Mode = c78_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c78_sfEvent);
    break;
  }
}

static void c78_VALIDATE_RANGE(SFc78_MX_GatewayInstanceStruct *chartInstance)
{
  boolean_T c78_temp;
  boolean_T c78_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 31U, chartInstance->c78_sfEvent);
  c78_temp = (_SFD_CCP_CALL(5U, 31U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 31U, 0,
    (real_T)chartInstance->c78_range, (real_T)
    (chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_NOM +
     chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_TOL), 0, 4U,
    chartInstance->c78_range > chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_NOM
    + chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_TOL) != 0U,
    chartInstance->c78_sfEvent) != 0U);
  if (!c78_temp) {
    c78_temp = (_SFD_CCP_CALL(5U, 31U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 31U,
      1, (real_T)chartInstance->c78_range, (real_T)
      (chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_NOM -
       chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_TOL), 0, 2U,
      chartInstance->c78_range <
      chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_NOM -
      chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_TOL) != 0U,
      chartInstance->c78_sfEvent) != 0U);
  }

  c78_out = (CV_TRANSITION_EVAL(31U, (int32_T)c78_temp) != 0);
  if (c78_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 31U, chartInstance->c78_sfEvent);
    *chartInstance->c78_state_CANThrottleCalDiag = 4U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_state_CANThrottleCalDiag,
                          12U);
    chartInstance->c78_tp_VALIDATE_RANGE = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_Cal_Mode = c78_IN_Cal_Fail;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Cal_Fail = 1U;
    *chartInstance->c78_cmd_CANThrottle = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c78_cmd_CANThrottle, 10U);
    c78_set_ee_ThrottleCalState(chartInstance, 0,
      chartInstance->c78_NOT_CALIBRATED);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
    c78_set_ee_ThrottleCalExtended(chartInstance, 0,
      chartInstance->c78_CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    c78_set_ee_ThrottleCalRetracted(chartInstance, 0,
      chartInstance->c78_CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
    matlab_UpdateEEVar();
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 32U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_VALIDATE_RANGE = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c78_sfEvent);
    chartInstance->c78_is_Cal_Mode = c78_IN_Done;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c78_sfEvent);
    chartInstance->c78_tp_Done = 1U;
    c78_set_ee_ThrottleCalState(chartInstance, 0, chartInstance->c78_NORMAL);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
    c78_set_state_Buzzer(chartInstance, 0, chartInstance->c78_DOUBLE_SHORT_BEEP);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 3);
    matlab_UpdateEEVar();
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c78_sfEvent);
}

static void init_script_number_translation(uint32_T c78_machineNumber, uint32_T
  c78_chartNumber, uint32_T c78_instanceNumber)
{
  (void)(c78_machineNumber);
  (void)(c78_chartNumber);
  (void)(c78_instanceNumber);
}

const mxArray *sf_c78_MX_Gateway_get_eml_resolved_functions_info(void)
{
  const mxArray *c78_nameCaptureInfo = NULL;
  c78_nameCaptureInfo = NULL;
  sf_mex_assign(&c78_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c78_nameCaptureInfo;
}

static const mxArray *c78_sf_marshallOut(void *chartInstanceVoid, void
  *c78_inData)
{
  const mxArray *c78_mxArrayOutData;
  int32_T c78_u;
  const mxArray *c78_y = NULL;
  SFc78_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc78_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c78_mxArrayOutData = NULL;
  c78_mxArrayOutData = NULL;
  c78_u = *(int32_T *)c78_inData;
  c78_y = NULL;
  sf_mex_assign(&c78_y, sf_mex_create("y", &c78_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c78_mxArrayOutData, c78_y, false);
  return c78_mxArrayOutData;
}

static int32_T c78_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_u, const emlrtMsgIdentifier *c78_parentId)
{
  int32_T c78_y;
  int32_T c78_i0;
  (void)chartInstance;
  sf_mex_import(c78_parentId, sf_mex_dup(c78_u), &c78_i0, 1, 6, 0U, 0, 0U, 0);
  c78_y = c78_i0;
  sf_mex_destroy(&c78_u);
  return c78_y;
}

static void c78_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c78_mxArrayInData, const char_T *c78_varName, void *c78_outData)
{
  const mxArray *c78_b_sfEvent;
  emlrtMsgIdentifier c78_thisId;
  int32_T c78_y;
  SFc78_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc78_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c78_b_sfEvent = sf_mex_dup(c78_mxArrayInData);
  c78_thisId.fIdentifier = (const char *)c78_varName;
  c78_thisId.fParent = NULL;
  c78_thisId.bParentIsCell = false;
  c78_y = c78_emlrt_marshallIn(chartInstance, sf_mex_dup(c78_b_sfEvent),
    &c78_thisId);
  sf_mex_destroy(&c78_b_sfEvent);
  *(int32_T *)c78_outData = c78_y;
  sf_mex_destroy(&c78_mxArrayInData);
}

static const mxArray *c78_b_sf_marshallOut(void *chartInstanceVoid, void
  *c78_inData)
{
  const mxArray *c78_mxArrayOutData;
  uint8_T c78_u;
  const mxArray *c78_y = NULL;
  SFc78_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc78_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c78_mxArrayOutData = NULL;
  c78_mxArrayOutData = NULL;
  c78_u = *(uint8_T *)c78_inData;
  c78_y = NULL;
  sf_mex_assign(&c78_y, sf_mex_create("y", &c78_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c78_mxArrayOutData, c78_y, false);
  return c78_mxArrayOutData;
}

static uint8_T c78_b_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_b_tp_Get_Cal_Values, const char_T
  *c78_identifier)
{
  uint8_T c78_y;
  emlrtMsgIdentifier c78_thisId;
  c78_thisId.fIdentifier = (const char *)c78_identifier;
  c78_thisId.fParent = NULL;
  c78_thisId.bParentIsCell = false;
  c78_y = c78_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c78_b_tp_Get_Cal_Values), &c78_thisId);
  sf_mex_destroy(&c78_b_tp_Get_Cal_Values);
  return c78_y;
}

static uint8_T c78_c_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_u, const emlrtMsgIdentifier *c78_parentId)
{
  uint8_T c78_y;
  uint8_T c78_u1;
  (void)chartInstance;
  sf_mex_import(c78_parentId, sf_mex_dup(c78_u), &c78_u1, 1, 3, 0U, 0, 0U, 0);
  c78_y = c78_u1;
  sf_mex_destroy(&c78_u);
  return c78_y;
}

static void c78_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c78_mxArrayInData, const char_T *c78_varName, void *c78_outData)
{
  const mxArray *c78_b_tp_Get_Cal_Values;
  emlrtMsgIdentifier c78_thisId;
  uint8_T c78_y;
  SFc78_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc78_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c78_b_tp_Get_Cal_Values = sf_mex_dup(c78_mxArrayInData);
  c78_thisId.fIdentifier = (const char *)c78_varName;
  c78_thisId.fParent = NULL;
  c78_thisId.bParentIsCell = false;
  c78_y = c78_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c78_b_tp_Get_Cal_Values), &c78_thisId);
  sf_mex_destroy(&c78_b_tp_Get_Cal_Values);
  *(uint8_T *)c78_outData = c78_y;
  sf_mex_destroy(&c78_mxArrayInData);
}

static const mxArray *c78_c_sf_marshallOut(void *chartInstanceVoid, void
  *c78_inData)
{
  const mxArray *c78_mxArrayOutData;
  uint16_T c78_u;
  const mxArray *c78_y = NULL;
  SFc78_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc78_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c78_mxArrayOutData = NULL;
  c78_mxArrayOutData = NULL;
  c78_u = *(uint16_T *)c78_inData;
  c78_y = NULL;
  sf_mex_assign(&c78_y, sf_mex_create("y", &c78_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c78_mxArrayOutData, c78_y, false);
  return c78_mxArrayOutData;
}

static uint16_T c78_d_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_b_CD_CAN_THROTTLE_CAL_DEADBAND, const
  char_T *c78_identifier)
{
  uint16_T c78_y;
  emlrtMsgIdentifier c78_thisId;
  c78_thisId.fIdentifier = (const char *)c78_identifier;
  c78_thisId.fParent = NULL;
  c78_thisId.bParentIsCell = false;
  c78_y = c78_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c78_b_CD_CAN_THROTTLE_CAL_DEADBAND), &c78_thisId);
  sf_mex_destroy(&c78_b_CD_CAN_THROTTLE_CAL_DEADBAND);
  return c78_y;
}

static uint16_T c78_e_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_u, const emlrtMsgIdentifier *c78_parentId)
{
  uint16_T c78_y;
  uint16_T c78_u2;
  (void)chartInstance;
  sf_mex_import(c78_parentId, sf_mex_dup(c78_u), &c78_u2, 1, 5, 0U, 0, 0U, 0);
  c78_y = c78_u2;
  sf_mex_destroy(&c78_u);
  return c78_y;
}

static void c78_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c78_mxArrayInData, const char_T *c78_varName, void *c78_outData)
{
  const mxArray *c78_b_CD_CAN_THROTTLE_CAL_DEADBAND;
  emlrtMsgIdentifier c78_thisId;
  uint16_T c78_y;
  SFc78_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc78_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c78_b_CD_CAN_THROTTLE_CAL_DEADBAND = sf_mex_dup(c78_mxArrayInData);
  c78_thisId.fIdentifier = (const char *)c78_varName;
  c78_thisId.fParent = NULL;
  c78_thisId.bParentIsCell = false;
  c78_y = c78_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c78_b_CD_CAN_THROTTLE_CAL_DEADBAND), &c78_thisId);
  sf_mex_destroy(&c78_b_CD_CAN_THROTTLE_CAL_DEADBAND);
  *(uint16_T *)c78_outData = c78_y;
  sf_mex_destroy(&c78_mxArrayInData);
}

static const mxArray *c78_d_sf_marshallOut(void *chartInstanceVoid, void
  *c78_inData)
{
  const mxArray *c78_mxArrayOutData;
  boolean_T c78_u;
  const mxArray *c78_y = NULL;
  SFc78_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc78_MX_GatewayInstanceStruct *)chartInstanceVoid;
  c78_mxArrayOutData = NULL;
  c78_mxArrayOutData = NULL;
  c78_u = *(boolean_T *)c78_inData;
  c78_y = NULL;
  sf_mex_assign(&c78_y, sf_mex_create("y", &c78_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c78_mxArrayOutData, c78_y, false);
  return c78_mxArrayOutData;
}

static const mxArray *c78_f_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_b_setSimStateSideEffectsInfo, const char_T *
  c78_identifier)
{
  const mxArray *c78_y = NULL;
  emlrtMsgIdentifier c78_thisId;
  c78_y = NULL;
  c78_thisId.fIdentifier = (const char *)c78_identifier;
  c78_thisId.fParent = NULL;
  c78_thisId.bParentIsCell = false;
  sf_mex_assign(&c78_y, c78_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c78_b_setSimStateSideEffectsInfo), &c78_thisId), false);
  sf_mex_destroy(&c78_b_setSimStateSideEffectsInfo);
  return c78_y;
}

static const mxArray *c78_g_emlrt_marshallIn(SFc78_MX_GatewayInstanceStruct
  *chartInstance, const mxArray *c78_u, const emlrtMsgIdentifier *c78_parentId)
{
  const mxArray *c78_y = NULL;
  (void)chartInstance;
  (void)c78_parentId;
  c78_y = NULL;
  sf_mex_assign(&c78_y, sf_mex_duplicatearraysafe(&c78_u), false);
  sf_mex_destroy(&c78_u);
  return c78_y;
}

static const mxArray *sf_get_hover_data_for_msg(SFc78_MX_GatewayInstanceStruct
  *chartInstance, int32_T c78_ssid)
{
  (void)chartInstance;
  (void)c78_ssid;
  return NULL;
}

static void c78_init_sf_message_store_memory(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static uint8_T c78__u8_s32_(SFc78_MX_GatewayInstanceStruct *chartInstance,
  int32_T c78_b, uint32_T c78_ssid_src_loc, int32_T c78_offset_src_loc, int32_T
  c78_length_src_loc)
{
  uint8_T c78_a;
  (void)chartInstance;
  c78_a = (uint8_T)c78_b;
  if (c78_a != c78_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c78_ssid_src_loc, c78_offset_src_loc,
      c78_length_src_loc);
  }

  return c78_a;
}

static uint16_T c78__u16_s32_(SFc78_MX_GatewayInstanceStruct *chartInstance,
  int32_T c78_b, uint32_T c78_ssid_src_loc, int32_T c78_offset_src_loc, int32_T
  c78_length_src_loc)
{
  uint16_T c78_a;
  (void)chartInstance;
  c78_a = (uint16_T)c78_b;
  if (c78_a != c78_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c78_ssid_src_loc, c78_offset_src_loc,
      c78_length_src_loc);
  }

  return c78_a;
}

static uint16_T c78__u16_u32_(SFc78_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c78_b, uint32_T c78_ssid_src_loc, int32_T c78_offset_src_loc, int32_T
  c78_length_src_loc)
{
  uint16_T c78_a;
  (void)chartInstance;
  c78_a = (uint16_T)c78_b;
  if (c78_a != c78_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c78_ssid_src_loc, c78_offset_src_loc,
      c78_length_src_loc);
  }

  return c78_a;
}

static int32_T c78__s32_add__(SFc78_MX_GatewayInstanceStruct *chartInstance,
  int32_T c78_b, int32_T c78_c, uint32_T c78_ssid_src_loc, int32_T
  c78_offset_src_loc, int32_T c78_length_src_loc)
{
  int32_T c78_a;
  (void)chartInstance;
  c78_a = c78_b + c78_c;
  if (((c78_a ^ c78_b) & (c78_a ^ c78_c)) < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c78_ssid_src_loc, c78_offset_src_loc,
      c78_length_src_loc);
  }

  return c78_a;
}

static uint16_T c78_get_ee_ThrottleCalExtended(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex)
{
  if (chartInstance->c78_dsmdiag_ee_ThrottleCalExtended) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 0,
      "ee_ThrottleCalExtended", c78_elementIndex);
  }

  return *chartInstance->c78_ee_ThrottleCalExtended_address;
}

static void c78_set_ee_ThrottleCalExtended(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex, uint16_T c78_elementValue)
{
  if (chartInstance->c78_dsmdiag_ee_ThrottleCalExtended) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 0,
      "ee_ThrottleCalExtended", c78_elementIndex);
  }

  *chartInstance->c78_ee_ThrottleCalExtended_address = c78_elementValue;
}

static uint16_T *c78_access_ee_ThrottleCalExtended
  (SFc78_MX_GatewayInstanceStruct *chartInstance, uint32_T c78_rdOnly)
{
  if (chartInstance->c78_dsmdiag_ee_ThrottleCalExtended) {
    ssAccessDataStore_wrapper(chartInstance->S, 0, "ee_ThrottleCalExtended",
      c78_rdOnly);
  }

  return chartInstance->c78_ee_ThrottleCalExtended_address;
}

static uint16_T c78_get_ee_ThrottleCalRetracted(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex)
{
  if (chartInstance->c78_dsmdiag_ee_ThrottleCalRetracted) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 1,
      "ee_ThrottleCalRetracted", c78_elementIndex);
  }

  return *chartInstance->c78__indexee_ThrottleCalRetracted_address;
}

static void c78_set_ee_ThrottleCalRetracted(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex, uint16_T c78_elementValue)
{
  if (chartInstance->c78_dsmdiag_ee_ThrottleCalRetracted) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 1,
      "ee_ThrottleCalRetracted", c78_elementIndex);
  }

  *chartInstance->c78__indexee_ThrottleCalRetracted_address = c78_elementValue;
}

static uint16_T *c78_access_ee_ThrottleCalRetracted
  (SFc78_MX_GatewayInstanceStruct *chartInstance, uint32_T c78_rdOnly)
{
  if (chartInstance->c78_dsmdiag_ee_ThrottleCalRetracted) {
    ssAccessDataStore_wrapper(chartInstance->S, 1, "ee_ThrottleCalRetracted",
      c78_rdOnly);
  }

  return chartInstance->c78__indexee_ThrottleCalRetracted_address;
}

static uint8_T c78_get_ee_ThrottleCalState(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex)
{
  if (chartInstance->c78_dsmdiag_ee_ThrottleCalState) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 2,
      "ee_ThrottleCalState", c78_elementIndex);
  }

  return *chartInstance->c78__indexee_ThrottleCalState_address;
}

static void c78_set_ee_ThrottleCalState(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex, uint8_T c78_elementValue)
{
  if (chartInstance->c78_dsmdiag_ee_ThrottleCalState) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 2, "ee_ThrottleCalState",
      c78_elementIndex);
  }

  *chartInstance->c78__indexee_ThrottleCalState_address = c78_elementValue;
}

static uint8_T *c78_access_ee_ThrottleCalState(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_rdOnly)
{
  if (chartInstance->c78_dsmdiag_ee_ThrottleCalState) {
    ssAccessDataStore_wrapper(chartInstance->S, 2, "ee_ThrottleCalState",
      c78_rdOnly);
  }

  return chartInstance->c78__indexee_ThrottleCalState_address;
}

static uint8_T c78_get_state_Buzzer(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_elementIndex)
{
  if (chartInstance->c78_dsmdiag_state_Buzzer) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 3, "state_Buzzer",
      c78_elementIndex);
  }

  return *chartInstance->c78__indexstate_Buzzer_address;
}

static void c78_set_state_Buzzer(SFc78_MX_GatewayInstanceStruct *chartInstance,
  uint32_T c78_elementIndex, uint8_T c78_elementValue)
{
  if (chartInstance->c78_dsmdiag_state_Buzzer) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 3, "state_Buzzer",
      c78_elementIndex);
  }

  *chartInstance->c78__indexstate_Buzzer_address = c78_elementValue;
}

static uint8_T *c78_access_state_Buzzer(SFc78_MX_GatewayInstanceStruct
  *chartInstance, uint32_T c78_rdOnly)
{
  if (chartInstance->c78_dsmdiag_state_Buzzer) {
    ssAccessDataStore_wrapper(chartInstance->S, 3, "state_Buzzer", c78_rdOnly);
  }

  return chartInstance->c78__indexstate_Buzzer_address;
}

static void init_dsm_address_info(SFc78_MX_GatewayInstanceStruct *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S,
    "ee_ThrottleCalExtended", (void **)
    &chartInstance->c78_ee_ThrottleCalExtended_address,
    &chartInstance->c78__indexottleCalExtended);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S,
    "ee_ThrottleCalRetracted", (void **)
    &chartInstance->c78__indexee_ThrottleCalRetracted_address,
    &chartInstance->c78__indexottleCalRetracted);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_ThrottleCalState",
    (void **)&chartInstance->c78__indexee_ThrottleCalState_address,
    &chartInstance->c78__indexottleCalState);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "state_Buzzer", (void **)
    &chartInstance->c78__indexstate_Buzzer_address,
    &chartInstance->c78__indexBuzzer);
}

static void init_simulink_io_address(SFc78_MX_GatewayInstanceStruct
  *chartInstance)
{
  chartInstance->c78_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c78_pos_Error = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c78_cmd_CANThrottle = (uint16_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c78_fdbk_CANThrottle = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c78_flag_InitEERead = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c78_state_CANThrottle = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 2);
  chartInstance->c78_state_Engine = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c78_state_CANThrottleCalDiag = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c78_state_CommThrottle = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 4);
  chartInstance->c78_pos_Throttle = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c78_scaled_ThrottlePos = (uint16_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 6);
  chartInstance->c78_dsmdiag_ee_ThrottleCalExtended = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 0,
    "ee_ThrottleCalExtended");
  chartInstance->c78_dsmdiag_ee_ThrottleCalRetracted = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 1,
    "ee_ThrottleCalRetracted");
  chartInstance->c78_dsmdiag_ee_ThrottleCalState = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 2,
    "ee_ThrottleCalState");
  chartInstance->c78_dsmdiag_state_Buzzer = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 3, "state_Buzzer");
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

void sf_c78_MX_Gateway_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2848324463U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1328239425U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1523977395U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2668510839U);
}

mxArray* sf_c78_MX_Gateway_get_post_codegen_info(void);
mxArray *sf_c78_MX_Gateway_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ZlmISBBjl7x0GNXIAG3l8E");
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,17,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c78_MX_Gateway_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c78_MX_Gateway_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c78_MX_Gateway_jit_fallback_info(void)
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

mxArray *sf_c78_MX_Gateway_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c78_MX_Gateway_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c78_MX_Gateway(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[118],T\"cmd_CANThrottle\",},{M[1],M[130],T\"state_CANThrottle\",},{M[1],M[133],T\"state_CANThrottleCalDiag\",},{M[3],M[119],T\"count\",},{M[3],M[127],T\"previous_cal_state\",},{M[3],M[128],T\"range\",},{M[8],M[0],T\"is_active_c78_MX_Gateway\",},{M[8],M[1],T\"is_active_Cal_Start\",},{M[8],M[29],T\"is_active_Control\",},{M[8],M[30],T\"is_active_Monitor\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[8],M[34],T\"is_active_Get_Cal_Values\",},{M[9],M[1],T\"is_Cal_Start\",},{M[9],M[2],T\"is_Cal_Check\",},{M[9],M[12],T\"is_Cal_Mode\",},{M[9],M[29],T\"is_Control\",},{M[9],M[30],T\"is_Monitor\",},{M[9],M[34],T\"is_Get_Cal_Values\",},{M[9],M[37],T\"is_Init_Cal\",},{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"wu\",M[8],M[1]}}},{M[11],M[0],T\"temporalCounter_i2\",S'et','os','ct'{{T\"wu\",M[91],M[1]}}}}",
    "100 S'type','srcId','name','auxInfo'{{M[11],M[0],T\"temporalCounter_i3\",S'et','os','ct'{{T\"wu\",M1x4[15 19 16 18],M[1]}}}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 21, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c78_MX_Gateway_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc78_MX_GatewayInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc78_MX_GatewayInstanceStruct *chartInstance =
      (SFc78_MX_GatewayInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MX_GatewayMachineNumber_,
           78,
           26,
           39,
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
          _SFD_SET_DATA_PROPS(0,0,0,0,"count");
          _SFD_SET_DATA_PROPS(1,0,0,0,"previous_cal_state");
          _SFD_SET_DATA_PROPS(2,0,0,0,"range");
          _SFD_SET_DATA_PROPS(3,1,1,0,"pos_Error");
          _SFD_SET_DATA_PROPS(4,1,1,0,"fdbk_CANThrottle");
          _SFD_SET_DATA_PROPS(5,1,1,0,"flag_InitEERead");
          _SFD_SET_DATA_PROPS(6,1,1,0,"state_Engine");
          _SFD_SET_DATA_PROPS(7,1,1,0,"state_CommThrottle");
          _SFD_SET_DATA_PROPS(8,1,1,0,"pos_Throttle");
          _SFD_SET_DATA_PROPS(9,1,1,0,"scaled_ThrottlePos");
          _SFD_SET_DATA_PROPS(10,2,0,1,"cmd_CANThrottle");
          _SFD_SET_DATA_PROPS(11,2,0,1,"state_CANThrottle");
          _SFD_SET_DATA_PROPS(12,2,0,1,"state_CANThrottleCalDiag");
          _SFD_SET_DATA_PROPS(13,10,0,0,"CD_CAN_THROTTLE_CAL_DEADBAND");
          _SFD_SET_DATA_PROPS(14,10,0,0,"CD_CAN_THROTTLE_CAL_DIAG_TIME");
          _SFD_SET_DATA_PROPS(15,10,0,0,"CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT");
          _SFD_SET_DATA_PROPS(16,10,0,0,"CD_CAN_THROTTLE_CAL_MAX");
          _SFD_SET_DATA_PROPS(17,10,0,0,"CD_CAN_THROTTLE_CAL_MIN");
          _SFD_SET_DATA_PROPS(18,10,0,0,"CD_CAN_THROTTLE_CAL_RANGE_NOM");
          _SFD_SET_DATA_PROPS(19,10,0,0,"CD_CAN_THROTTLE_CAL_RANGE_TOL");
          _SFD_SET_DATA_PROPS(20,10,0,0,"CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT");
          _SFD_SET_DATA_PROPS(21,10,0,0,"CD_CAN_THROTTLE_DEBOUNCE_FAILURE");
          _SFD_SET_DATA_PROPS(22,10,0,0,"CD_CAN_THROTTLE_ERROR_MAX");
          _SFD_SET_DATA_PROPS(23,10,0,0,"DOUBLE_SHORT_BEEP");
          _SFD_SET_DATA_PROPS(24,10,0,0,"ENGINE_CRANKING");
          _SFD_SET_DATA_PROPS(25,10,0,0,"ENGINE_RUNNING");
          _SFD_SET_DATA_PROPS(26,10,0,0,"FAILURE");
          _SFD_SET_DATA_PROPS(27,10,0,0,"IN_CAL_MODE");
          _SFD_SET_DATA_PROPS(28,10,0,0,"NORMAL");
          _SFD_SET_DATA_PROPS(29,10,0,0,"NOT_CALIBRATED");
          _SFD_SET_DATA_PROPS(30,11,0,0,"ee_ThrottleCalExtended");
          _SFD_SET_DATA_PROPS(31,11,0,0,"ee_ThrottleCalRetracted");
          _SFD_SET_DATA_PROPS(32,11,0,0,"ee_ThrottleCalState");
          _SFD_SET_DATA_PROPS(33,11,0,0,"state_Buzzer");
          _SFD_STATE_INFO(0,0,1);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,1);
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
          _SFD_STATE_INFO(18,0,1);
          _SFD_STATE_INFO(19,0,0);
          _SFD_STATE_INFO(20,0,0);
          _SFD_STATE_INFO(21,0,0);
          _SFD_STATE_INFO(22,0,1);
          _SFD_STATE_INFO(23,0,0);
          _SFD_STATE_INFO(24,0,0);
          _SFD_STATE_INFO(25,0,0);
          _SFD_CH_SUBSTATE_COUNT(4);
          _SFD_CH_SUBSTATE_DECOMP(1);
          _SFD_CH_SUBSTATE_INDEX(0,18);
          _SFD_CH_SUBSTATE_INDEX(1,0);
          _SFD_CH_SUBSTATE_INDEX(2,22);
          _SFD_CH_SUBSTATE_INDEX(3,6);
          _SFD_ST_SUBSTATE_COUNT(18,2);
          _SFD_ST_SUBSTATE_INDEX(18,0,19);
          _SFD_ST_SUBSTATE_INDEX(18,1,21);
          _SFD_ST_SUBSTATE_COUNT(19,1);
          _SFD_ST_SUBSTATE_INDEX(19,0,20);
          _SFD_ST_SUBSTATE_COUNT(20,0);
          _SFD_ST_SUBSTATE_COUNT(21,0);
          _SFD_ST_SUBSTATE_COUNT(0,3);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,4);
          _SFD_ST_SUBSTATE_INDEX(0,2,5);
          _SFD_ST_SUBSTATE_COUNT(1,2);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,3);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(22,3);
          _SFD_ST_SUBSTATE_INDEX(22,0,23);
          _SFD_ST_SUBSTATE_INDEX(22,1,24);
          _SFD_ST_SUBSTATE_INDEX(22,2,25);
          _SFD_ST_SUBSTATE_COUNT(23,0);
          _SFD_ST_SUBSTATE_COUNT(24,0);
          _SFD_ST_SUBSTATE_COUNT(25,0);
          _SFD_ST_SUBSTATE_COUNT(6,2);
          _SFD_ST_SUBSTATE_INDEX(6,0,7);
          _SFD_ST_SUBSTATE_INDEX(6,1,17);
          _SFD_ST_SUBSTATE_COUNT(7,9);
          _SFD_ST_SUBSTATE_INDEX(7,0,8);
          _SFD_ST_SUBSTATE_INDEX(7,1,9);
          _SFD_ST_SUBSTATE_INDEX(7,2,10);
          _SFD_ST_SUBSTATE_INDEX(7,3,11);
          _SFD_ST_SUBSTATE_INDEX(7,4,12);
          _SFD_ST_SUBSTATE_INDEX(7,5,13);
          _SFD_ST_SUBSTATE_INDEX(7,6,14);
          _SFD_ST_SUBSTATE_INDEX(7,7,15);
          _SFD_ST_SUBSTATE_INDEX(7,8,16);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,0);
          _SFD_ST_SUBSTATE_COUNT(10,0);
          _SFD_ST_SUBSTATE_COUNT(11,0);
          _SFD_ST_SUBSTATE_COUNT(12,0);
          _SFD_ST_SUBSTATE_COUNT(13,0);
          _SFD_ST_SUBSTATE_COUNT(14,0);
          _SFD_ST_SUBSTATE_COUNT(15,0);
          _SFD_ST_SUBSTATE_COUNT(16,0);
          _SFD_ST_SUBSTATE_COUNT(17,0);
        }

        _SFD_CV_INIT_CHART(4,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartDecMap[] = { 15 };

          static unsigned int sEndDecMap[] = { 57 };

          _SFD_CV_INIT_STATE(5,0,0,0,0,1,&(sStartDecMap[0]),&(sEndDecMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(6,2,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,9,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(18,2,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(19,1,0,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(23,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(24,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(25,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(13,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(14,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(15,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 37, 92, 147 };

          static unsigned int sEndGuardMap[] = { 30, 85, 140, 196 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(16,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 37, 92, 147 };

          static unsigned int sEndRelationalopMap[] = { 30, 85, 140, 196 };

          static int sRelationalopEps[] = { 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 4, 2, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(16,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(22,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(18,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(23,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 77 };

          static unsigned int sEndGuardMap[] = { 70, 146 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(24,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 77 };

          static unsigned int sEndRelationalopMap[] = { 70, 146 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 2, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(24,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(25,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(19,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(20,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(33,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 45 };

          static unsigned int sEndGuardMap[] = { 38, 74 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(34,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 45 };

          static unsigned int sEndRelationalopMap[] = { 38, 74 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 4, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(34,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 45 };

          static unsigned int sEndGuardMap[] = { 38, 74 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(35,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 45 };

          static unsigned int sEndRelationalopMap[] = { 38, 74 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 2, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(35,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 45 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(36,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 39 };

          static unsigned int sEndGuardMap[] = { 32, 69 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(3,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 39 };

          static unsigned int sEndRelationalopMap[] = { 32, 69 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(3,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 10 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(4,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 10 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(4,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 35 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(21,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 35 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(21,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 36, 69, 107 };

          static unsigned int sEndGuardMap[] = { 29, 63, 100, 137 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2 };

          _SFD_CV_INIT_TRANS(11,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 36, 69, 107 };

          static unsigned int sEndRelationalopMap[] = { 29, 63, 100, 137 };

          static int sRelationalopEps[] = { 0, 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(11,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 19 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,1,&(sStartRelationalopMap[0]),
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

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 19 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(28,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 35 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(26,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 35 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(26,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 46 };

          static unsigned int sEndGuardMap[] = { 38, 75 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(27,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 46 };

          static unsigned int sEndRelationalopMap[] = { 38, 75 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(27,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(9,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 43 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(29,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 43 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(29,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 9, 0 };

          static unsigned int sEndGuardMap[] = { 13, 14 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(8,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 9, 0 };

          static unsigned int sEndGuardMap[] = { 13, 14 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(10,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 43 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(30,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 43 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(30,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 9, 0 };

          static unsigned int sEndGuardMap[] = { 13, 14 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(7,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 50 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(38,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 50 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(38,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(37,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 77 };

          static unsigned int sEndGuardMap[] = { 70, 146 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(31,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 77 };

          static unsigned int sEndRelationalopMap[] = { 70, 146 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 4, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(31,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(32,0,NULL,NULL,0,NULL);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(27,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(28,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(29,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(30,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(31,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_c_sf_marshallOut,(MexInFcnForType)
          c78_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(32,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(33,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c78_b_sf_marshallOut,(MexInFcnForType)
          c78_b_sf_marshallIn);
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
    SFc78_MX_GatewayInstanceStruct *chartInstance =
      (SFc78_MX_GatewayInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c78_pos_Error);
        _SFD_SET_DATA_VALUE_PTR(13U, (void *)
          &chartInstance->c78_CD_CAN_THROTTLE_CAL_DEADBAND);
        _SFD_SET_DATA_VALUE_PTR(15U, (void *)
          &chartInstance->c78_CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT);
        _SFD_SET_DATA_VALUE_PTR(20U, (void *)
          &chartInstance->c78_CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT);
        _SFD_SET_DATA_VALUE_PTR(14U, (void *)
          &chartInstance->c78_CD_CAN_THROTTLE_CAL_DIAG_TIME);
        _SFD_SET_DATA_VALUE_PTR(16U, (void *)
          &chartInstance->c78_CD_CAN_THROTTLE_CAL_MAX);
        _SFD_SET_DATA_VALUE_PTR(17U, (void *)
          &chartInstance->c78_CD_CAN_THROTTLE_CAL_MIN);
        _SFD_SET_DATA_VALUE_PTR(18U, (void *)
          &chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_NOM);
        _SFD_SET_DATA_VALUE_PTR(19U, (void *)
          &chartInstance->c78_CD_CAN_THROTTLE_CAL_RANGE_TOL);
        _SFD_SET_DATA_VALUE_PTR(21U, (void *)
          &chartInstance->c78_CD_CAN_THROTTLE_DEBOUNCE_FAILURE);
        _SFD_SET_DATA_VALUE_PTR(22U, (void *)
          &chartInstance->c78_CD_CAN_THROTTLE_ERROR_MAX);
        _SFD_SET_DATA_VALUE_PTR(23U, (void *)
          &chartInstance->c78_DOUBLE_SHORT_BEEP);
        _SFD_SET_DATA_VALUE_PTR(24U, (void *)&chartInstance->c78_ENGINE_CRANKING);
        _SFD_SET_DATA_VALUE_PTR(25U, (void *)&chartInstance->c78_ENGINE_RUNNING);
        _SFD_SET_DATA_VALUE_PTR(26U, (void *)&chartInstance->c78_FAILURE);
        _SFD_SET_DATA_VALUE_PTR(27U, (void *)&chartInstance->c78_IN_CAL_MODE);
        _SFD_SET_DATA_VALUE_PTR(28U, (void *)&chartInstance->c78_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(29U, (void *)&chartInstance->c78_NOT_CALIBRATED);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)chartInstance->c78_cmd_CANThrottle);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)&chartInstance->c78_count);
        _SFD_SET_DATA_VALUE_PTR(30U, (void *)
          chartInstance->c78_ee_ThrottleCalExtended_address);
        _SFD_SET_DATA_VALUE_PTR(31U, (void *)
          chartInstance->c78__indexee_ThrottleCalRetracted_address);
        _SFD_SET_DATA_VALUE_PTR(32U, (void *)
          chartInstance->c78__indexee_ThrottleCalState_address);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c78_fdbk_CANThrottle);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c78_flag_InitEERead);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)
          &chartInstance->c78_previous_cal_state);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)&chartInstance->c78_range);
        _SFD_SET_DATA_VALUE_PTR(33U, (void *)
          chartInstance->c78__indexstate_Buzzer_address);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)
          chartInstance->c78_state_CANThrottle);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c78_state_Engine);
        _SFD_SET_DATA_VALUE_PTR(12U, (void *)
          chartInstance->c78_state_CANThrottleCalDiag);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)
          chartInstance->c78_state_CommThrottle);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c78_pos_Throttle);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)
          chartInstance->c78_scaled_ThrottlePos);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "srCmhmRs9Mv9hgCdexntGK";
}

static void sf_opaque_initialize_c78_MX_Gateway(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc78_MX_GatewayInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c78_MX_Gateway((SFc78_MX_GatewayInstanceStruct*)
    chartInstanceVar);
  initialize_c78_MX_Gateway((SFc78_MX_GatewayInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c78_MX_Gateway(void *chartInstanceVar)
{
  enable_c78_MX_Gateway((SFc78_MX_GatewayInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c78_MX_Gateway(void *chartInstanceVar)
{
  disable_c78_MX_Gateway((SFc78_MX_GatewayInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c78_MX_Gateway(void *chartInstanceVar)
{
  sf_gateway_c78_MX_Gateway((SFc78_MX_GatewayInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c78_MX_Gateway(SimStruct* S)
{
  return get_sim_state_c78_MX_Gateway((SFc78_MX_GatewayInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c78_MX_Gateway(SimStruct* S, const mxArray
  *st)
{
  set_sim_state_c78_MX_Gateway((SFc78_MX_GatewayInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c78_MX_Gateway(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc78_MX_GatewayInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MX_Gateway_optimization_info();
    }

    finalize_c78_MX_Gateway((SFc78_MX_GatewayInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc78_MX_Gateway((SFc78_MX_GatewayInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c78_MX_Gateway(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c78_MX_Gateway((SFc78_MX_GatewayInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c78_MX_Gateway(SimStruct *S)
{
  /* Actual parameters from chart:
     CD_CAN_THROTTLE_CAL_DEADBAND CD_CAN_THROTTLE_CAL_DIAG_TIME CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT CD_CAN_THROTTLE_CAL_MAX CD_CAN_THROTTLE_CAL_MIN CD_CAN_THROTTLE_CAL_RANGE_NOM CD_CAN_THROTTLE_CAL_RANGE_TOL CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT CD_CAN_THROTTLE_DEBOUNCE_FAILURE CD_CAN_THROTTLE_ERROR_MAX DOUBLE_SHORT_BEEP ENGINE_CRANKING ENGINE_RUNNING FAILURE IN_CAL_MODE NORMAL NOT_CALIBRATED
   */
  const char_T *rtParamNames[] = { "CD_CAN_THROTTLE_CAL_DEADBAND",
    "CD_CAN_THROTTLE_CAL_DIAG_TIME", "CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT",
    "CD_CAN_THROTTLE_CAL_MAX", "CD_CAN_THROTTLE_CAL_MIN",
    "CD_CAN_THROTTLE_CAL_RANGE_NOM", "CD_CAN_THROTTLE_CAL_RANGE_TOL",
    "CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT", "CD_CAN_THROTTLE_DEBOUNCE_FAILURE",
    "CD_CAN_THROTTLE_ERROR_MAX", "DOUBLE_SHORT_BEEP", "ENGINE_CRANKING",
    "ENGINE_RUNNING", "FAILURE", "IN_CAL_MODE", "NORMAL", "NOT_CALIBRATED" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for CD_CAN_THROTTLE_CAL_DEADBAND*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_UINT16);

  /* registration for CD_CAN_THROTTLE_CAL_DIAG_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT16);

  /* registration for CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT16);

  /* registration for CD_CAN_THROTTLE_CAL_MAX*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_UINT16);

  /* registration for CD_CAN_THROTTLE_CAL_MIN*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_UINT16);

  /* registration for CD_CAN_THROTTLE_CAL_RANGE_NOM*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_UINT16);

  /* registration for CD_CAN_THROTTLE_CAL_RANGE_TOL*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_UINT16);

  /* registration for CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT*/
  ssRegDlgParamAsRunTimeParam(S, 7, 7, rtParamNames[7], SS_UINT16);

  /* registration for CD_CAN_THROTTLE_DEBOUNCE_FAILURE*/
  ssRegDlgParamAsRunTimeParam(S, 8, 8, rtParamNames[8], SS_UINT16);

  /* registration for CD_CAN_THROTTLE_ERROR_MAX*/
  ssRegDlgParamAsRunTimeParam(S, 9, 9, rtParamNames[9], SS_UINT16);

  /* registration for DOUBLE_SHORT_BEEP*/
  ssRegDlgParamAsRunTimeParam(S, 10, 10, rtParamNames[10], SS_UINT8);

  /* registration for ENGINE_CRANKING*/
  ssRegDlgParamAsRunTimeParam(S, 11, 11, rtParamNames[11], SS_UINT8);

  /* registration for ENGINE_RUNNING*/
  ssRegDlgParamAsRunTimeParam(S, 12, 12, rtParamNames[12], SS_UINT8);

  /* registration for FAILURE*/
  ssRegDlgParamAsRunTimeParam(S, 13, 13, rtParamNames[13], SS_UINT8);

  /* registration for IN_CAL_MODE*/
  ssRegDlgParamAsRunTimeParam(S, 14, 14, rtParamNames[14], SS_UINT8);

  /* registration for NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 15, 15, rtParamNames[15], SS_UINT8);

  /* registration for NOT_CALIBRATED*/
  ssRegDlgParamAsRunTimeParam(S, 16, 16, rtParamNames[16], SS_UINT8);
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
    mxArray *infoStruct = load_MX_Gateway_optimization_info(sim_mode_is_rtw_gen
      (S), sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      78);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,78,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 78);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,78);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,78,7);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,78,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 7; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,78);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(666414050U));
  ssSetChecksum1(S,(699848421U));
  ssSetChecksum2(S,(3398101269U));
  ssSetChecksum3(S,(2883043591U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c78_MX_Gateway(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c78_MX_Gateway(SimStruct *S)
{
  SFc78_MX_GatewayInstanceStruct *chartInstance;
  chartInstance = (SFc78_MX_GatewayInstanceStruct *)utMalloc(sizeof
    (SFc78_MX_GatewayInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc78_MX_GatewayInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c78_MX_Gateway;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c78_MX_Gateway;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c78_MX_Gateway;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c78_MX_Gateway;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c78_MX_Gateway;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c78_MX_Gateway;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c78_MX_Gateway;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c78_MX_Gateway;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c78_MX_Gateway;
  chartInstance->chartInfo.mdlStart = mdlStart_c78_MX_Gateway;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c78_MX_Gateway;
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
  mdl_start_c78_MX_Gateway(chartInstance);
}

void c78_MX_Gateway_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c78_MX_Gateway(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c78_MX_Gateway(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c78_MX_Gateway(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c78_MX_Gateway_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
