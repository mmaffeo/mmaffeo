/* Include files */

#include "MX_Gtwy_Control_sfun.h"
#include "c83_MX_Gtwy_Control.h"
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
#define c83_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)
#define c83_IN_Deluxe_G55              ((uint8_T)1U)
#define c83_IN_Normal                  ((uint8_T)2U)
#define c83_IN_Init                    ((uint8_T)1U)
#define c83_IN_Off                     ((uint8_T)2U)
#define c83_IN_On                      ((uint8_T)3U)
#define c83_b_IN_Off                   ((uint8_T)1U)
#define c83_b_IN_On                    ((uint8_T)2U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initialize_params_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void enable_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void disable_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c83_update_debugger_state_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void set_sim_state_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c83_st);
static void c83_set_sim_state_side_effects_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void finalize_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void sf_gateway_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void mdl_start_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c83_chartstep_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void initSimStructsc83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c83_machineNumber, uint32_T
  c83_chartNumber, uint32_T c83_instanceNumber);
static const mxArray *c83_sf_marshallOut(void *chartInstanceVoid, void
  *c83_inData);
static int32_T c83_emlrt_marshallIn(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c83_u, const emlrtMsgIdentifier *c83_parentId);
static void c83_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c83_mxArrayInData, const char_T *c83_varName, void *c83_outData);
static const mxArray *c83_b_sf_marshallOut(void *chartInstanceVoid, void
  *c83_inData);
static uint8_T c83_b_emlrt_marshallIn(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c83_b_tp_Normal, const char_T *c83_identifier);
static uint8_T c83_c_emlrt_marshallIn(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c83_u, const emlrtMsgIdentifier *c83_parentId);
static void c83_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c83_mxArrayInData, const char_T *c83_varName, void *c83_outData);
static const mxArray *c83_c_sf_marshallOut(void *chartInstanceVoid, void
  *c83_inData);
static const mxArray *c83_d_emlrt_marshallIn(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c83_b_setSimStateSideEffectsInfo, const char_T *
  c83_identifier);
static const mxArray *c83_e_emlrt_marshallIn(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c83_u, const emlrtMsgIdentifier *c83_parentId);
static const mxArray *sf_get_hover_data_for_msg
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c83_ssid);
static void c83_init_sf_message_store_memory(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static uint8_T c83_get_ee_DeluxeG5(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_elementIndex);
static void c83_set_ee_DeluxeG5(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_elementIndex, uint8_T c83_elementValue);
static uint8_T *c83_access_ee_DeluxeG5(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_rdOnly);
static uint8_T c83_get_ee_EcoMode(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_elementIndex);
static void c83_set_ee_EcoMode(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_elementIndex, uint8_T c83_elementValue);
static uint8_T *c83_access_ee_EcoMode(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_rdOnly);
static void init_dsm_address_info(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc83_MX_Gtwy_Control(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c83_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c83_doSetSimStateSideEffects = 0U;
  chartInstance->c83_setSimStateSideEffectsInfo = NULL;
  chartInstance->c83_is_Deluxe_G55 = c83_IN_NO_ACTIVE_CHILD;
  chartInstance->c83_tp_Deluxe_G55 = 0U;
  chartInstance->c83_b_tp_Off = 0U;
  chartInstance->c83_b_tp_On = 0U;
  chartInstance->c83_is_Normal = c83_IN_NO_ACTIVE_CHILD;
  chartInstance->c83_tp_Normal = 0U;
  chartInstance->c83_tp_Init = 0U;
  chartInstance->c83_tp_Off = 0U;
  chartInstance->c83_tp_On = 0U;
  chartInstance->c83_is_active_c83_MX_Gtwy_Control = 0U;
  chartInstance->c83_is_c83_MX_Gtwy_Control = c83_IN_NO_ACTIVE_CHILD;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c83_state_EcoMode = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_state_EcoMode, 3U);
  }
}

static void initialize_params_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  real_T c83_d0;
  real_T c83_d1;
  real_T c83_d2;
  real_T c83_d3;
  sf_mex_import_named("INACTIVE", sf_mex_get_sfun_param(chartInstance->S, 2, 0),
                      &c83_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c83_INACTIVE = (uint8_T)c83_d0;
  sf_mex_import_named("ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c83_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c83_ACTIVE = (uint8_T)c83_d1;
  sf_mex_import_named("CD_DELUXE_GEN5_5_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 1, 0), &c83_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c83_CD_DELUXE_GEN5_5_FUNCTION = (uint8_T)c83_d2;
  sf_mex_import_named("NON_FUNCTIONAL", sf_mex_get_sfun_param(chartInstance->S,
    3, 0), &c83_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c83_NON_FUNCTIONAL = (uint8_T)c83_d3;
}

static void enable_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c83_update_debugger_state_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  uint32_T c83_prevAniVal;
  c83_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c83_is_active_c83_MX_Gtwy_Control == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 80U, chartInstance->c83_sfEvent);
  }

  if (chartInstance->c83_is_c83_MX_Gtwy_Control == c83_IN_Normal) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c83_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c83_sfEvent);
  }

  if (chartInstance->c83_is_Normal == c83_IN_On) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c83_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c83_sfEvent);
  }

  if (chartInstance->c83_is_Normal == c83_IN_Init) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c83_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c83_sfEvent);
  }

  if (chartInstance->c83_is_Normal == c83_IN_Off) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c83_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c83_sfEvent);
  }

  if (chartInstance->c83_is_c83_MX_Gtwy_Control == c83_IN_Deluxe_G55) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c83_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c83_sfEvent);
  }

  if (chartInstance->c83_is_Deluxe_G55 == c83_b_IN_Off) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c83_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c83_sfEvent);
  }

  if (chartInstance->c83_is_Deluxe_G55 == c83_b_IN_On) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c83_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c83_sfEvent);
  }

  _SFD_SET_ANIMATION(c83_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  const mxArray *c83_st;
  const mxArray *c83_y = NULL;
  uint8_T c83_hoistedGlobal;
  const mxArray *c83_b_y = NULL;
  uint8_T c83_b_hoistedGlobal;
  const mxArray *c83_c_y = NULL;
  uint8_T c83_c_hoistedGlobal;
  const mxArray *c83_d_y = NULL;
  uint8_T c83_d_hoistedGlobal;
  const mxArray *c83_e_y = NULL;
  uint8_T c83_e_hoistedGlobal;
  const mxArray *c83_f_y = NULL;
  c83_st = NULL;
  c83_st = NULL;
  c83_y = NULL;
  sf_mex_assign(&c83_y, sf_mex_createcellmatrix(5, 1), false);
  c83_hoistedGlobal = *chartInstance->c83_state_EcoMode;
  c83_b_y = NULL;
  sf_mex_assign(&c83_b_y, sf_mex_create("y", &c83_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c83_y, 0, c83_b_y);
  c83_b_hoistedGlobal = chartInstance->c83_is_active_c83_MX_Gtwy_Control;
  c83_c_y = NULL;
  sf_mex_assign(&c83_c_y, sf_mex_create("y", &c83_b_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c83_y, 1, c83_c_y);
  c83_c_hoistedGlobal = chartInstance->c83_is_c83_MX_Gtwy_Control;
  c83_d_y = NULL;
  sf_mex_assign(&c83_d_y, sf_mex_create("y", &c83_c_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c83_y, 2, c83_d_y);
  c83_d_hoistedGlobal = chartInstance->c83_is_Deluxe_G55;
  c83_e_y = NULL;
  sf_mex_assign(&c83_e_y, sf_mex_create("y", &c83_d_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c83_y, 3, c83_e_y);
  c83_e_hoistedGlobal = chartInstance->c83_is_Normal;
  c83_f_y = NULL;
  sf_mex_assign(&c83_f_y, sf_mex_create("y", &c83_e_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c83_y, 4, c83_f_y);
  sf_mex_assign(&c83_st, c83_y, false);
  return c83_st;
}

static void set_sim_state_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c83_st)
{
  const mxArray *c83_u;
  c83_u = sf_mex_dup(c83_st);
  *chartInstance->c83_state_EcoMode = c83_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c83_u, 0)), "state_EcoMode");
  chartInstance->c83_is_active_c83_MX_Gtwy_Control = c83_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c83_u, 1)),
     "is_active_c83_MX_Gtwy_Control");
  chartInstance->c83_is_c83_MX_Gtwy_Control = c83_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c83_u, 2)),
     "is_c83_MX_Gtwy_Control");
  chartInstance->c83_is_Deluxe_G55 = c83_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c83_u, 3)), "is_Deluxe_G55");
  chartInstance->c83_is_Normal = c83_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c83_u, 4)), "is_Normal");
  sf_mex_assign(&chartInstance->c83_setSimStateSideEffectsInfo,
                c83_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c83_u, 5)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c83_u);
  chartInstance->c83_doSetSimStateSideEffects = 1U;
  c83_update_debugger_state_c83_MX_Gtwy_Control(chartInstance);
  sf_mex_destroy(&c83_st);
}

static void c83_set_sim_state_side_effects_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  if (chartInstance->c83_doSetSimStateSideEffects != 0) {
    chartInstance->c83_tp_Deluxe_G55 = (uint8_T)
      (chartInstance->c83_is_c83_MX_Gtwy_Control == c83_IN_Deluxe_G55);
    chartInstance->c83_b_tp_Off = (uint8_T)(chartInstance->c83_is_Deluxe_G55 ==
      c83_b_IN_Off);
    chartInstance->c83_b_tp_On = (uint8_T)(chartInstance->c83_is_Deluxe_G55 ==
      c83_b_IN_On);
    chartInstance->c83_tp_Normal = (uint8_T)
      (chartInstance->c83_is_c83_MX_Gtwy_Control == c83_IN_Normal);
    chartInstance->c83_tp_Init = (uint8_T)(chartInstance->c83_is_Normal ==
      c83_IN_Init);
    chartInstance->c83_tp_Off = (uint8_T)(chartInstance->c83_is_Normal ==
      c83_IN_Off);
    chartInstance->c83_tp_On = (uint8_T)(chartInstance->c83_is_Normal ==
      c83_IN_On);
    chartInstance->c83_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c83_setSimStateSideEffectsInfo);
}

static void sf_gateway_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  c83_set_sim_state_side_effects_c83_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 80U, chartInstance->c83_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_dlx_G55_EcoMode, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_flag_InitEERead, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_button_EcoMode, 0U);
  chartInstance->c83_sfEvent = CALL_EVENT;
  c83_chartstep_c83_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MX_Gtwy_ControlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c83_MX_Gtwy_Control(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  c83_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void c83_chartstep_c83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c83_out;
  boolean_T c83_b_out;
  boolean_T c83_c_out;
  boolean_T c83_d_out;
  boolean_T c83_e_out;
  boolean_T c83_f_out;
  boolean_T c83_temp;
  boolean_T c83_b_temp;
  boolean_T c83_g_out;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 80U, chartInstance->c83_sfEvent);
  if (chartInstance->c83_is_active_c83_MX_Gtwy_Control == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 80U, chartInstance->c83_sfEvent);
    chartInstance->c83_is_active_c83_MX_Gtwy_Control = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 80U, chartInstance->c83_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c83_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                 chartInstance->c83_sfEvent);
    c83_out = (CV_TRANSITION_EVAL(11U, (int32_T)(_SFD_CCP_CALL(5U, 11U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 11U, 0, (real_T)
      chartInstance->c83_CD_DELUXE_GEN5_5_FUNCTION, (real_T)
      chartInstance->c83_NON_FUNCTIONAL, 0, 0U,
      chartInstance->c83_CD_DELUXE_GEN5_5_FUNCTION ==
      chartInstance->c83_NON_FUNCTIONAL) != 0U, chartInstance->c83_sfEvent) !=
      0U)) != 0);
    if (c83_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c83_sfEvent);
      chartInstance->c83_is_c83_MX_Gtwy_Control = c83_IN_Normal;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c83_sfEvent);
      chartInstance->c83_tp_Normal = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c83_sfEvent);
      chartInstance->c83_is_Normal = c83_IN_Init;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c83_sfEvent);
      chartInstance->c83_tp_Init = 1U;
      *chartInstance->c83_state_EcoMode = chartInstance->c83_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_state_EcoMode, 3U);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c83_sfEvent);
      chartInstance->c83_is_c83_MX_Gtwy_Control = c83_IN_Deluxe_G55;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c83_sfEvent);
      chartInstance->c83_tp_Deluxe_G55 = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c83_sfEvent);
      chartInstance->c83_is_Deluxe_G55 = c83_b_IN_Off;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c83_sfEvent);
      chartInstance->c83_b_tp_Off = 1U;
      *chartInstance->c83_state_EcoMode = chartInstance->c83_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_state_EcoMode, 3U);
    }
  } else {
    switch (chartInstance->c83_is_c83_MX_Gtwy_Control) {
     case c83_IN_Deluxe_G55:
      CV_CHART_EVAL(80, 0, c83_IN_Deluxe_G55);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                   chartInstance->c83_sfEvent);
      switch (chartInstance->c83_is_Deluxe_G55) {
       case c83_b_IN_Off:
        CV_STATE_EVAL(0, 0, c83_b_IN_Off);
        *chartInstance->c83_state_EcoMode = chartInstance->c83_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                     chartInstance->c83_sfEvent);
        c83_b_out = (CV_TRANSITION_EVAL(2U, (int32_T)(_SFD_CCP_CALL(5U, 2U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 2U, 0, (real_T)
          *chartInstance->c83_dlx_G55_EcoMode, (real_T)chartInstance->c83_ACTIVE,
          0, 0U, *chartInstance->c83_dlx_G55_EcoMode ==
          chartInstance->c83_ACTIVE) != 0U, chartInstance->c83_sfEvent) != 0U))
                     != 0);
        if (c83_b_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c83_sfEvent);
          chartInstance->c83_b_tp_Off = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c83_sfEvent);
          chartInstance->c83_is_Deluxe_G55 = c83_b_IN_On;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c83_sfEvent);
          chartInstance->c83_b_tp_On = 1U;
          *chartInstance->c83_state_EcoMode = chartInstance->c83_ACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_state_EcoMode, 3U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                       chartInstance->c83_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c83_sfEvent);
        break;

       case c83_b_IN_On:
        CV_STATE_EVAL(0, 0, c83_b_IN_On);
        *chartInstance->c83_state_EcoMode = chartInstance->c83_ACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                     chartInstance->c83_sfEvent);
        c83_c_out = (CV_TRANSITION_EVAL(1U, (int32_T)(_SFD_CCP_CALL(5U, 1U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 1U, 0, (real_T)
          *chartInstance->c83_dlx_G55_EcoMode, (real_T)chartInstance->c83_ACTIVE,
          0, 1U, *chartInstance->c83_dlx_G55_EcoMode !=
          chartInstance->c83_ACTIVE) != 0U, chartInstance->c83_sfEvent) != 0U))
                     != 0);
        if (c83_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c83_sfEvent);
          chartInstance->c83_b_tp_On = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c83_sfEvent);
          chartInstance->c83_is_Deluxe_G55 = c83_b_IN_Off;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c83_sfEvent);
          chartInstance->c83_b_tp_Off = 1U;
          *chartInstance->c83_state_EcoMode = chartInstance->c83_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_state_EcoMode, 3U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                       chartInstance->c83_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c83_sfEvent);
        break;

       default:
        CV_STATE_EVAL(0, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c83_is_Deluxe_G55 = c83_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c83_sfEvent);
        break;
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c83_sfEvent);
      break;

     case c83_IN_Normal:
      CV_CHART_EVAL(80, 0, c83_IN_Normal);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                   chartInstance->c83_sfEvent);
      switch (chartInstance->c83_is_Normal) {
       case c83_IN_Init:
        CV_STATE_EVAL(3, 0, c83_IN_Init);
        *chartInstance->c83_state_EcoMode = chartInstance->c83_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U,
                     chartInstance->c83_sfEvent);
        c83_d_out = (CV_TRANSITION_EVAL(4U, (int32_T)(_SFD_CCP_CALL(5U, 4U, 0,
          *chartInstance->c83_flag_InitEERead != 0U, chartInstance->c83_sfEvent)
          != 0U)) != 0);
        if (c83_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c83_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                       chartInstance->c83_sfEvent);
          c83_temp = (_SFD_CCP_CALL(5U, 5U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
            5U, 0, (real_T)c83_get_ee_EcoMode(chartInstance, 0), (real_T)
            chartInstance->c83_ACTIVE, 0, 0U, c83_get_ee_EcoMode(chartInstance,
            0) == chartInstance->c83_ACTIVE) != 0U, chartInstance->c83_sfEvent)
                      != 0U);
          if (c83_temp) {
            c83_b_temp = (_SFD_CCP_CALL(5U, 5U, 1, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 5U, 1, (real_T)c83_get_ee_DeluxeG5(chartInstance, 0), (real_T)
               chartInstance->c83_ACTIVE, 0, 0U, c83_get_ee_DeluxeG5
               (chartInstance, 0) == chartInstance->c83_ACTIVE) != 0U,
              chartInstance->c83_sfEvent) != 0U);
            if (!c83_b_temp) {
              c83_b_temp = (_SFD_CCP_CALL(5U, 5U, 2, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 5U, 2, (real_T)
                                   chartInstance->c83_CD_DELUXE_GEN5_5_FUNCTION,
                                   (real_T)chartInstance->c83_NON_FUNCTIONAL, 0,
                                   1U,
                                   chartInstance->c83_CD_DELUXE_GEN5_5_FUNCTION
                                   != chartInstance->c83_NON_FUNCTIONAL) != 0U,
                chartInstance->c83_sfEvent) != 0U);
            }

            c83_temp = c83_b_temp;
          }

          c83_g_out = (CV_TRANSITION_EVAL(5U, (int32_T)c83_temp) != 0);
          if (c83_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c83_sfEvent);
            chartInstance->c83_tp_Init = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c83_sfEvent);
            chartInstance->c83_is_Normal = c83_IN_On;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c83_sfEvent);
            chartInstance->c83_tp_On = 1U;
            *chartInstance->c83_state_EcoMode = chartInstance->c83_ACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_state_EcoMode, 3U);
            c83_set_ee_EcoMode(chartInstance, 0, chartInstance->c83_ACTIVE);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            matlab_UpdateEEVar();
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c83_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c83_sfEvent);
            chartInstance->c83_tp_Init = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c83_sfEvent);
            chartInstance->c83_is_Normal = c83_IN_Off;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c83_sfEvent);
            chartInstance->c83_tp_Off = 1U;
            *chartInstance->c83_state_EcoMode = chartInstance->c83_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_state_EcoMode, 3U);
            c83_set_ee_EcoMode(chartInstance, 0, chartInstance->c83_INACTIVE);
            ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
            matlab_UpdateEEVar();
          }
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                       chartInstance->c83_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c83_sfEvent);
        break;

       case c83_IN_Off:
        CV_STATE_EVAL(3, 0, c83_IN_Off);
        *chartInstance->c83_state_EcoMode = chartInstance->c83_INACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                     chartInstance->c83_sfEvent);
        c83_e_out = (CV_TRANSITION_EVAL(8U, (int32_T)(_SFD_CCP_CALL(5U, 8U, 0,
          *chartInstance->c83_button_EcoMode != 0U, chartInstance->c83_sfEvent)
          != 0U)) != 0);
        if (c83_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c83_sfEvent);
          chartInstance->c83_tp_Off = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c83_sfEvent);
          chartInstance->c83_is_Normal = c83_IN_On;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c83_sfEvent);
          chartInstance->c83_tp_On = 1U;
          *chartInstance->c83_state_EcoMode = chartInstance->c83_ACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_state_EcoMode, 3U);
          c83_set_ee_EcoMode(chartInstance, 0, chartInstance->c83_ACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                       chartInstance->c83_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c83_sfEvent);
        break;

       case c83_IN_On:
        CV_STATE_EVAL(3, 0, c83_IN_On);
        *chartInstance->c83_state_EcoMode = chartInstance->c83_ACTIVE;
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                     chartInstance->c83_sfEvent);
        c83_f_out = (CV_TRANSITION_EVAL(7U, (int32_T)(_SFD_CCP_CALL(5U, 7U, 0,
          *chartInstance->c83_button_EcoMode != 0U, chartInstance->c83_sfEvent)
          != 0U)) != 0);
        if (c83_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c83_sfEvent);
          chartInstance->c83_tp_On = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c83_sfEvent);
          chartInstance->c83_is_Normal = c83_IN_Off;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c83_sfEvent);
          chartInstance->c83_tp_Off = 1U;
          *chartInstance->c83_state_EcoMode = chartInstance->c83_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c83_state_EcoMode, 3U);
          c83_set_ee_EcoMode(chartInstance, 0, chartInstance->c83_INACTIVE);
          ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
          matlab_UpdateEEVar();
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                       chartInstance->c83_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c83_sfEvent);
        break;

       default:
        CV_STATE_EVAL(3, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c83_is_Normal = c83_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c83_sfEvent);
        break;
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c83_sfEvent);
      break;

     default:
      CV_CHART_EVAL(80, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c83_is_c83_MX_Gtwy_Control = c83_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c83_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 80U, chartInstance->c83_sfEvent);
}

static void initSimStructsc83_MX_Gtwy_Control
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c83_machineNumber, uint32_T
  c83_chartNumber, uint32_T c83_instanceNumber)
{
  (void)(c83_machineNumber);
  (void)(c83_chartNumber);
  (void)(c83_instanceNumber);
}

const mxArray *sf_c83_MX_Gtwy_Control_get_eml_resolved_functions_info(void)
{
  const mxArray *c83_nameCaptureInfo = NULL;
  c83_nameCaptureInfo = NULL;
  sf_mex_assign(&c83_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c83_nameCaptureInfo;
}

static const mxArray *c83_sf_marshallOut(void *chartInstanceVoid, void
  *c83_inData)
{
  const mxArray *c83_mxArrayOutData;
  int32_T c83_u;
  const mxArray *c83_y = NULL;
  SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc83_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c83_mxArrayOutData = NULL;
  c83_mxArrayOutData = NULL;
  c83_u = *(int32_T *)c83_inData;
  c83_y = NULL;
  sf_mex_assign(&c83_y, sf_mex_create("y", &c83_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c83_mxArrayOutData, c83_y, false);
  return c83_mxArrayOutData;
}

static int32_T c83_emlrt_marshallIn(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c83_u, const emlrtMsgIdentifier *c83_parentId)
{
  int32_T c83_y;
  int32_T c83_i0;
  (void)chartInstance;
  sf_mex_import(c83_parentId, sf_mex_dup(c83_u), &c83_i0, 1, 6, 0U, 0, 0U, 0);
  c83_y = c83_i0;
  sf_mex_destroy(&c83_u);
  return c83_y;
}

static void c83_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c83_mxArrayInData, const char_T *c83_varName, void *c83_outData)
{
  const mxArray *c83_b_sfEvent;
  emlrtMsgIdentifier c83_thisId;
  int32_T c83_y;
  SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc83_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c83_b_sfEvent = sf_mex_dup(c83_mxArrayInData);
  c83_thisId.fIdentifier = (const char *)c83_varName;
  c83_thisId.fParent = NULL;
  c83_thisId.bParentIsCell = false;
  c83_y = c83_emlrt_marshallIn(chartInstance, sf_mex_dup(c83_b_sfEvent),
    &c83_thisId);
  sf_mex_destroy(&c83_b_sfEvent);
  *(int32_T *)c83_outData = c83_y;
  sf_mex_destroy(&c83_mxArrayInData);
}

static const mxArray *c83_b_sf_marshallOut(void *chartInstanceVoid, void
  *c83_inData)
{
  const mxArray *c83_mxArrayOutData;
  uint8_T c83_u;
  const mxArray *c83_y = NULL;
  SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc83_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c83_mxArrayOutData = NULL;
  c83_mxArrayOutData = NULL;
  c83_u = *(uint8_T *)c83_inData;
  c83_y = NULL;
  sf_mex_assign(&c83_y, sf_mex_create("y", &c83_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c83_mxArrayOutData, c83_y, false);
  return c83_mxArrayOutData;
}

static uint8_T c83_b_emlrt_marshallIn(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c83_b_tp_Normal, const char_T *c83_identifier)
{
  uint8_T c83_y;
  emlrtMsgIdentifier c83_thisId;
  c83_thisId.fIdentifier = (const char *)c83_identifier;
  c83_thisId.fParent = NULL;
  c83_thisId.bParentIsCell = false;
  c83_y = c83_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c83_b_tp_Normal),
    &c83_thisId);
  sf_mex_destroy(&c83_b_tp_Normal);
  return c83_y;
}

static uint8_T c83_c_emlrt_marshallIn(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c83_u, const emlrtMsgIdentifier *c83_parentId)
{
  uint8_T c83_y;
  uint8_T c83_u0;
  (void)chartInstance;
  sf_mex_import(c83_parentId, sf_mex_dup(c83_u), &c83_u0, 1, 3, 0U, 0, 0U, 0);
  c83_y = c83_u0;
  sf_mex_destroy(&c83_u);
  return c83_y;
}

static void c83_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c83_mxArrayInData, const char_T *c83_varName, void *c83_outData)
{
  const mxArray *c83_b_tp_Normal;
  emlrtMsgIdentifier c83_thisId;
  uint8_T c83_y;
  SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc83_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c83_b_tp_Normal = sf_mex_dup(c83_mxArrayInData);
  c83_thisId.fIdentifier = (const char *)c83_varName;
  c83_thisId.fParent = NULL;
  c83_thisId.bParentIsCell = false;
  c83_y = c83_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c83_b_tp_Normal),
    &c83_thisId);
  sf_mex_destroy(&c83_b_tp_Normal);
  *(uint8_T *)c83_outData = c83_y;
  sf_mex_destroy(&c83_mxArrayInData);
}

static const mxArray *c83_c_sf_marshallOut(void *chartInstanceVoid, void
  *c83_inData)
{
  const mxArray *c83_mxArrayOutData;
  boolean_T c83_u;
  const mxArray *c83_y = NULL;
  SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc83_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c83_mxArrayOutData = NULL;
  c83_mxArrayOutData = NULL;
  c83_u = *(boolean_T *)c83_inData;
  c83_y = NULL;
  sf_mex_assign(&c83_y, sf_mex_create("y", &c83_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c83_mxArrayOutData, c83_y, false);
  return c83_mxArrayOutData;
}

static const mxArray *c83_d_emlrt_marshallIn(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c83_b_setSimStateSideEffectsInfo, const char_T *
  c83_identifier)
{
  const mxArray *c83_y = NULL;
  emlrtMsgIdentifier c83_thisId;
  c83_y = NULL;
  c83_thisId.fIdentifier = (const char *)c83_identifier;
  c83_thisId.fParent = NULL;
  c83_thisId.bParentIsCell = false;
  sf_mex_assign(&c83_y, c83_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c83_b_setSimStateSideEffectsInfo), &c83_thisId), false);
  sf_mex_destroy(&c83_b_setSimStateSideEffectsInfo);
  return c83_y;
}

static const mxArray *c83_e_emlrt_marshallIn(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c83_u, const emlrtMsgIdentifier *c83_parentId)
{
  const mxArray *c83_y = NULL;
  (void)chartInstance;
  (void)c83_parentId;
  c83_y = NULL;
  sf_mex_assign(&c83_y, sf_mex_duplicatearraysafe(&c83_u), false);
  sf_mex_destroy(&c83_u);
  return c83_y;
}

static const mxArray *sf_get_hover_data_for_msg
  (SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c83_ssid)
{
  (void)chartInstance;
  (void)c83_ssid;
  return NULL;
}

static void c83_init_sf_message_store_memory(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static uint8_T c83_get_ee_DeluxeG5(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_elementIndex)
{
  if (chartInstance->c83_dsmdiag_ee_DeluxeG5) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, "ee_DeluxeG5",
      c83_elementIndex);
  }

  return *chartInstance->c83_ee_DeluxeG5_address;
}

static void c83_set_ee_DeluxeG5(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_elementIndex, uint8_T c83_elementValue)
{
  if (chartInstance->c83_dsmdiag_ee_DeluxeG5) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, "ee_DeluxeG5",
      c83_elementIndex);
  }

  *chartInstance->c83_ee_DeluxeG5_address = c83_elementValue;
}

static uint8_T *c83_access_ee_DeluxeG5(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_rdOnly)
{
  if (chartInstance->c83_dsmdiag_ee_DeluxeG5) {
    ssAccessDataStore_wrapper(chartInstance->S, 0, "ee_DeluxeG5", c83_rdOnly);
  }

  return chartInstance->c83_ee_DeluxeG5_address;
}

static uint8_T c83_get_ee_EcoMode(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_elementIndex)
{
  if (chartInstance->c83_dsmdiag_ee_EcoMode) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 1, "ee_EcoMode",
      c83_elementIndex);
  }

  return *chartInstance->c83__indexee_EcoMode_address;
}

static void c83_set_ee_EcoMode(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_elementIndex, uint8_T c83_elementValue)
{
  if (chartInstance->c83_dsmdiag_ee_EcoMode) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 1, "ee_EcoMode",
      c83_elementIndex);
  }

  *chartInstance->c83__indexee_EcoMode_address = c83_elementValue;
}

static uint8_T *c83_access_ee_EcoMode(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c83_rdOnly)
{
  if (chartInstance->c83_dsmdiag_ee_EcoMode) {
    ssAccessDataStore_wrapper(chartInstance->S, 1, "ee_EcoMode", c83_rdOnly);
  }

  return chartInstance->c83__indexee_EcoMode_address;
}

static void init_dsm_address_info(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_DeluxeG5", (void **)
    &chartInstance->c83_ee_DeluxeG5_address, &chartInstance->c83__indexuxeG5);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_EcoMode", (void **)
    &chartInstance->c83__indexee_EcoMode_address, &chartInstance->c83__indexMode);
}

static void init_simulink_io_address(SFc83_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  chartInstance->c83_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c83_state_EcoMode = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c83_button_EcoMode = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c83_flag_InitEERead = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c83_dlx_G55_EcoMode = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c83_dsmdiag_ee_DeluxeG5 = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 0, "ee_DeluxeG5");
  chartInstance->c83_dsmdiag_ee_EcoMode = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 1, "ee_EcoMode");
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

void sf_c83_MX_Gtwy_Control_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4073369158U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(263497405U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2092628378U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1018114967U);
}

mxArray* sf_c83_MX_Gtwy_Control_get_post_codegen_info(void);
mxArray *sf_c83_MX_Gtwy_Control_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("kGMWstsmFMHu1cek21TMN");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
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
    mxArray* mxPostCodegenInfo = sf_c83_MX_Gtwy_Control_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c83_MX_Gtwy_Control_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c83_MX_Gtwy_Control_jit_fallback_info(void)
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

mxArray *sf_c83_MX_Gtwy_Control_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c83_MX_Gtwy_Control_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c83_MX_Gtwy_Control(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[6],T\"state_EcoMode\",},{M[8],M[0],T\"is_active_c83_MX_Gtwy_Control\",},{M[9],M[0],T\"is_c83_MX_Gtwy_Control\",},{M[9],M[22],T\"is_Deluxe_G55\",},{M[9],M[24],T\"is_Normal\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c83_MX_Gtwy_Control_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc83_MX_Gtwy_ControlInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc83_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MX_Gtwy_ControlMachineNumber_,
           83,
           7,
           13,
           0,
           10,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"button_EcoMode");
          _SFD_SET_DATA_PROPS(1,1,1,0,"flag_InitEERead");
          _SFD_SET_DATA_PROPS(2,1,1,0,"dlx_G55_EcoMode");
          _SFD_SET_DATA_PROPS(3,2,0,1,"state_EcoMode");
          _SFD_SET_DATA_PROPS(4,10,0,0,"ACTIVE");
          _SFD_SET_DATA_PROPS(5,10,0,0,"CD_DELUXE_GEN5_5_FUNCTION");
          _SFD_SET_DATA_PROPS(6,10,0,0,"INACTIVE");
          _SFD_SET_DATA_PROPS(7,10,0,0,"NON_FUNCTIONAL");
          _SFD_SET_DATA_PROPS(8,11,0,0,"ee_DeluxeG5");
          _SFD_SET_DATA_PROPS(9,11,0,0,"ee_EcoMode");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_CH_SUBSTATE_COUNT(2);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,3);
          _SFD_ST_SUBSTATE_COUNT(0,2);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,2);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,3);
          _SFD_ST_SUBSTATE_INDEX(3,0,4);
          _SFD_ST_SUBSTATE_INDEX(3,1,5);
          _SFD_ST_SUBSTATE_INDEX(3,2,6);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
        }

        _SFD_CV_INIT_CHART(2,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,2,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,3,1,0,0,0,NULL,NULL);
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

        _SFD_CV_INIT_TRANS(10,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 44 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(11,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 44 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(11,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(4,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29, 58 };

          static unsigned int sEndGuardMap[] = { 21, 50, 101 };

          static int sPostFixPredicateTree[] = { 0, 1, 2, -2, -3 };

          _SFD_CV_INIT_TRANS(5,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29, 58 };

          static unsigned int sEndRelationalopMap[] = { 21, 50, 101 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(7,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(8,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 26 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 26 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c83_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c83_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c83_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c83_b_sf_marshallOut,(MexInFcnForType)
          c83_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c83_b_sf_marshallOut,(MexInFcnForType)
          c83_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c83_b_sf_marshallOut,(MexInFcnForType)
          c83_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c83_b_sf_marshallOut,(MexInFcnForType)
          c83_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c83_b_sf_marshallOut,(MexInFcnForType)
          c83_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c83_b_sf_marshallOut,(MexInFcnForType)
          c83_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c83_b_sf_marshallOut,(MexInFcnForType)
          c83_b_sf_marshallIn);
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
    SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc83_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c83_state_EcoMode);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c83_button_EcoMode);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)&chartInstance->c83_INACTIVE);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)&chartInstance->c83_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)
          chartInstance->c83__indexee_EcoMode_address);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)
          chartInstance->c83_ee_DeluxeG5_address);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c83_flag_InitEERead);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)
          &chartInstance->c83_CD_DELUXE_GEN5_5_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)&chartInstance->c83_NON_FUNCTIONAL);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c83_dlx_G55_EcoMode);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sQsW2oTHToYb8lybBaGBH6G";
}

static void sf_opaque_initialize_c83_MX_Gtwy_Control(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc83_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c83_MX_Gtwy_Control((SFc83_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
  initialize_c83_MX_Gtwy_Control((SFc83_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c83_MX_Gtwy_Control(void *chartInstanceVar)
{
  enable_c83_MX_Gtwy_Control((SFc83_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c83_MX_Gtwy_Control(void *chartInstanceVar)
{
  disable_c83_MX_Gtwy_Control((SFc83_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c83_MX_Gtwy_Control(void *chartInstanceVar)
{
  sf_gateway_c83_MX_Gtwy_Control((SFc83_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c83_MX_Gtwy_Control(SimStruct* S)
{
  return get_sim_state_c83_MX_Gtwy_Control((SFc83_MX_Gtwy_ControlInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c83_MX_Gtwy_Control(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c83_MX_Gtwy_Control((SFc83_MX_Gtwy_ControlInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c83_MX_Gtwy_Control(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc83_MX_Gtwy_ControlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MX_Gtwy_Control_optimization_info();
    }

    finalize_c83_MX_Gtwy_Control((SFc83_MX_Gtwy_ControlInstanceStruct*)
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
  initSimStructsc83_MX_Gtwy_Control((SFc83_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c83_MX_Gtwy_Control(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c83_MX_Gtwy_Control((SFc83_MX_Gtwy_ControlInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c83_MX_Gtwy_Control(SimStruct *S)
{
  /* Actual parameters from chart:
     ACTIVE CD_DELUXE_GEN5_5_FUNCTION INACTIVE NON_FUNCTIONAL
   */
  const char_T *rtParamNames[] = { "ACTIVE", "CD_DELUXE_GEN5_5_FUNCTION",
    "INACTIVE", "NON_FUNCTIONAL" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_UINT8);

  /* registration for CD_DELUXE_GEN5_5_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT8);

  /* registration for INACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT8);

  /* registration for NON_FUNCTIONAL*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_UINT8);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MX_Gtwy_Control_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      83);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,83,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 83);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,83);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,83,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,83,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,83);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1974004115U));
  ssSetChecksum1(S,(3220125909U));
  ssSetChecksum2(S,(1984310426U));
  ssSetChecksum3(S,(3032263138U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c83_MX_Gtwy_Control(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c83_MX_Gtwy_Control(SimStruct *S)
{
  SFc83_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc83_MX_Gtwy_ControlInstanceStruct *)utMalloc(sizeof
    (SFc83_MX_Gtwy_ControlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc83_MX_Gtwy_ControlInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c83_MX_Gtwy_Control;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c83_MX_Gtwy_Control;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c83_MX_Gtwy_Control;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c83_MX_Gtwy_Control;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c83_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c83_MX_Gtwy_Control;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c83_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c83_MX_Gtwy_Control;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c83_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlStart = mdlStart_c83_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c83_MX_Gtwy_Control;
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
  mdl_start_c83_MX_Gtwy_Control(chartInstance);
}

void c83_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c83_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c83_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c83_MX_Gtwy_Control(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c83_MX_Gtwy_Control_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
