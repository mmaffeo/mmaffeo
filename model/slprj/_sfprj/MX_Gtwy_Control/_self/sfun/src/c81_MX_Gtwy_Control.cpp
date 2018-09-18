/* Include files */

#include "MX_Gtwy_Control_sfun.h"
#include "c81_MX_Gtwy_Control.h"
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
#define c81_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)
#define c81_IN_ACTIVE                  ((uint8_T)1U)
#define c81_IN_EDGE                    ((uint8_T)2U)
#define c81_IN_INACTIVE                ((uint8_T)3U)
#define c81_IN_INACTIVE_WAIT           ((uint8_T)4U)
#define c81_IN_EMEA_CONTROLS           ((uint8_T)2U)
#define c81_IN_ERROR_CODES             ((uint8_T)3U)
#define c81_b_IN_INACTIVE              ((uint8_T)4U)
#define c81_IN_SECOND_AUX              ((uint8_T)5U)
#define c81_IN_BATTERY_VOLTAGE         ((uint8_T)1U)
#define c81_IN_ECT                     ((uint8_T)2U)
#define c81_IN_EMEA_CONTROLS1          ((uint8_T)3U)
#define c81_IN_ENGINE_HOURS            ((uint8_T)4U)
#define c81_IN_ENGINE_RPM              ((uint8_T)5U)
#define c81_IN_EOP                     ((uint8_T)6U)
#define c81_b_IN_ERROR_CODES           ((uint8_T)7U)
#define c81_IN_FACTORY                 ((uint8_T)8U)
#define c81_IN_HOT2                    ((uint8_T)9U)
#define c81_IN_JOB_CLOCK_1             ((uint8_T)10U)
#define c81_IN_JOB_CLOCK_2             ((uint8_T)11U)
#define c81_IN_JOB_CLOCK_RESET1        ((uint8_T)12U)
#define c81_IN_JOB_CLOCK_RESET2        ((uint8_T)13U)
#define c81_IN_SERVICE_CLOCK           ((uint8_T)14U)
#define c81_IN_SERVICE_CLOCK_RESET     ((uint8_T)15U)
#define c81_IN_DEBOUNCE                ((uint8_T)1U)
#define c81_c_IN_INACTIVE              ((uint8_T)2U)
#define c81_IN_RESET_STATE             ((uint8_T)3U)
#define c81_b_IN_ECT                   ((uint8_T)1U)
#define c81_IN_HOT                     ((uint8_T)2U)
#define c81_IN_JUMP_STATE              ((uint8_T)3U)
#define c81_IN_DELUXE_ERROR            ((uint8_T)1U)
#define c81_IN_DELUXE_GOOD             ((uint8_T)2U)
#define c81_IN_KSS                     ((uint8_T)1U)
#define c81_IN_NON_SHUTDOWN            ((uint8_T)2U)
#define c81_IN_SHUTDOWN                ((uint8_T)3U)
#define c81_IN_VERSION                 ((uint8_T)4U)
#define c81_IN_Aux_Detent_Error        ((uint8_T)1U)
#define c81_IN_COLD                    ((uint8_T)2U)
#define c81_IN_FLASH_COLD              ((uint8_T)3U)
#define c81_IN_GLOW_PLUGS              ((uint8_T)4U)
#define c81_IN_NO_STATE                ((uint8_T)5U)
#define c81_IN_OFFSET                  ((uint8_T)6U)
#define c81_IN_SERVICE_CLOCK_ALARM     ((uint8_T)7U)
#define c81_IN_THROTTLE_CAL_DIAGNOSTICS ((uint8_T)8U)
#define c81_IN_AUX                     ((uint8_T)1U)
#define c81_IN_HOLD                    ((uint8_T)2U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initialize_params_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void enable_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void disable_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_update_debugger_state_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void set_sim_state_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c81_st);
static void c81_set_sim_state_side_effects_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void finalize_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void sf_gateway_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void mdl_start_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_chartstep_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void initSimStructsc81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_BUTTON_STATE(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_INFO_BUTTON(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_PRIMARY_STATE(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_enter_internal_ACTIVE(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_b_ACTIVE(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_exit_internal_ACTIVE(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_ENGINE_HOURS(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_exit_internal_ENGINE_HOURS(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_JOB_CLOCK_1(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_exit_internal_JOB_CLOCK_1(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_JOB_CLOCK_RESET1(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_JOB_CLOCK_2(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_exit_internal_JOB_CLOCK_2(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_JOB_CLOCK_RESET2(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_enter_internal_FACTORY(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_FACTORY(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_exit_internal_FACTORY(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_ENGINE_RPM(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_SERVICE_CLOCK_RESET(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_SERVICE_CLOCK(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_exit_internal_SERVICE_CLOCK(SFc81_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c81_ERROR_CODES(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_HOT2(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_SECOND_AUX(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_enter_atomic_ERROR_CODES(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_SECONDARY_STATE(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_exit_internal_DELUXE_GOOD(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_NON_SHUTDOWN(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_exit_internal_NON_SHUTDOWN(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_NO_STATE(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c81_THROTTLE_CAL_DIAGNOSTICS(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c81_exit_internal_Aux_Detent_Error
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c81_machineNumber, uint32_T
  c81_chartNumber, uint32_T c81_instanceNumber);
static const mxArray *c81_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData);
static int32_T c81_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId);
static void c81_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c81_mxArrayInData, const char_T *c81_varName, void *c81_outData);
static const mxArray *c81_b_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData);
static uint8_T c81_b_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_b_tp_BUTTON_STATE, const char_T
  *c81_identifier);
static uint8_T c81_c_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId);
static void c81_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c81_mxArrayInData, const char_T *c81_varName, void *c81_outData);
static const mxArray *c81_c_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData);
static uint16_T c81_d_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_b_debounceCount, const char_T
  *c81_identifier);
static uint16_T c81_e_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId);
static void c81_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c81_mxArrayInData, const char_T *c81_varName, void *c81_outData);
static const mxArray *c81_d_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData);
static const mxArray *c81_e_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData);
static void c81_f_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId,
  uint8_T c81_y[2]);
static void c81_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c81_mxArrayInData, const char_T *c81_varName, void *c81_outData);
static const mxArray *c81_f_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData);
static boolean_T c81_g_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_b_prev_SecondAux, const char_T
  *c81_identifier);
static boolean_T c81_h_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId);
static void c81_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c81_mxArrayInData, const char_T *c81_varName, void *c81_outData);
static const mxArray *c81_i_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_b_setSimStateSideEffectsInfo, const char_T *
  c81_identifier);
static const mxArray *c81_j_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId);
static const mxArray *sf_get_hover_data_for_msg
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c81_ssid);
static void c81_init_sf_message_store_memory(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static uint16_T c81__u16_s32_(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c81_b, uint32_T c81_ssid_src_loc, int32_T c81_offset_src_loc, int32_T
  c81_length_src_loc);
static uint8_T c81__u8_s32_(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c81_b, uint32_T c81_ssid_src_loc, int32_T c81_offset_src_loc, int32_T
  c81_length_src_loc);
static int32_T c81__s32_add__(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c81_b, int32_T c81_c, uint32_T c81_ssid_src_loc, int32_T
  c81_offset_src_loc, int32_T c81_length_src_loc);
static uint16_T c81__u16_u32_(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance,
  uint32_T c81_b, uint32_T c81_ssid_src_loc, int32_T c81_offset_src_loc, int32_T
  c81_length_src_loc);
static uint8_T c81_get_ee_DeluxeG5(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex);
static void c81_set_ee_DeluxeG5(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex, uint8_T c81_elementValue);
static uint8_T *c81_access_ee_DeluxeG5(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_rdOnly);
static uint8_T c81_get_ee_EngData(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex);
static void c81_set_ee_EngData(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex, uint8_T c81_elementValue);
static uint8_T *c81_access_ee_EngData(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_rdOnly);
static uint8_T c81_get_ee_JobClockLHP(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex);
static void c81_set_ee_JobClockLHP(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex, uint8_T c81_elementValue);
static uint8_T *c81_access_ee_JobClockLHP(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_rdOnly);
static uint8_T c81_get_flag_StdActiveWarn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex);
static void c81_set_flag_StdActiveWarn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex, uint8_T c81_elementValue);
static uint8_T *c81_access_flag_StdActiveWarn
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance, uint32_T c81_rdOnly);
static void init_dsm_address_info(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc81_MX_Gtwy_Control(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c81_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c81_doSetSimStateSideEffects = 0U;
  chartInstance->c81_setSimStateSideEffectsInfo = NULL;
  chartInstance->c81_is_active_BUTTON_STATE = 0U;
  chartInstance->c81_tp_BUTTON_STATE = 0U;
  chartInstance->c81_is_active_INFO_BUTTON = 0U;
  chartInstance->c81_is_INFO_BUTTON = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_INFO_BUTTON = 0U;
  chartInstance->c81_tp_ACTIVE = 0U;
  chartInstance->c81_tp_EDGE = 0U;
  chartInstance->c81_tp_INACTIVE = 0U;
  chartInstance->c81_tp_INACTIVE_WAIT = 0U;
  chartInstance->c81_is_active_MOVE_LEFT = 0U;
  chartInstance->c81_tp_MOVE_LEFT = 0U;
  chartInstance->c81_b_is_active_PANEL_BUTTON = 0U;
  chartInstance->c81_b_is_PANEL_BUTTON = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_b_tp_PANEL_BUTTON = 0U;
  chartInstance->c81_c_tp_ACTIVE = 0U;
  chartInstance->c81_c_tp_EDGE = 0U;
  chartInstance->c81_c_tp_INACTIVE = 0U;
  chartInstance->c81_c_tp_INACTIVE_WAIT = 0U;
  chartInstance->c81_is_active_MOVE_RIGHT = 0U;
  chartInstance->c81_tp_MOVE_RIGHT = 0U;
  chartInstance->c81_is_active_PANEL_BUTTON = 0U;
  chartInstance->c81_is_PANEL_BUTTON = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_PANEL_BUTTON = 0U;
  chartInstance->c81_b_tp_ACTIVE = 0U;
  chartInstance->c81_b_tp_EDGE = 0U;
  chartInstance->c81_b_tp_INACTIVE = 0U;
  chartInstance->c81_b_tp_INACTIVE_WAIT = 0U;
  chartInstance->c81_is_active_LIGHT_BUTTON_STATE = 0U;
  chartInstance->c81_is_LIGHT_BUTTON_STATE = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_LIGHT_BUTTON_STATE = 0U;
  chartInstance->c81_e_tp_ACTIVE = 0U;
  chartInstance->c81_d_tp_EDGE = 0U;
  chartInstance->c81_i_tp_INACTIVE = 0U;
  chartInstance->c81_is_active_PRIMARY_STATE = 0U;
  chartInstance->c81_is_PRIMARY_STATE = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_PRIMARY_STATE = 0U;
  chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_was_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_d_tp_ACTIVE = 0U;
  chartInstance->c81_temporalCounter_i1 = 0U;
  chartInstance->c81_tp_BATTERY_VOLTAGE = 0U;
  chartInstance->c81_b_tp_ECT = 0U;
  chartInstance->c81_tp_EMEA_CONTROLS1 = 0U;
  chartInstance->c81_is_ENGINE_HOURS = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_ENGINE_HOURS = 0U;
  chartInstance->c81_tp_DEBOUNCE = 0U;
  chartInstance->c81_d_tp_INACTIVE = 0U;
  chartInstance->c81_tp_RESET_STATE = 0U;
  chartInstance->c81_tp_ENGINE_RPM = 0U;
  chartInstance->c81_tp_EOP = 0U;
  chartInstance->c81_tp_ERROR_CODES = 0U;
  chartInstance->c81_is_FACTORY = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_FACTORY = 0U;
  chartInstance->c81_tp_ECT = 0U;
  chartInstance->c81_tp_HOT = 0U;
  chartInstance->c81_tp_HOT2 = 0U;
  chartInstance->c81_is_JOB_CLOCK_1 = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_JOB_CLOCK_1 = 0U;
  chartInstance->c81_b_tp_DEBOUNCE = 0U;
  chartInstance->c81_e_tp_INACTIVE = 0U;
  chartInstance->c81_b_tp_RESET_STATE = 0U;
  chartInstance->c81_is_JOB_CLOCK_2 = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_JOB_CLOCK_2 = 0U;
  chartInstance->c81_c_tp_DEBOUNCE = 0U;
  chartInstance->c81_f_tp_INACTIVE = 0U;
  chartInstance->c81_c_tp_RESET_STATE = 0U;
  chartInstance->c81_tp_JOB_CLOCK_RESET1 = 0U;
  chartInstance->c81_temporalCounter_i2 = 0U;
  chartInstance->c81_tp_JOB_CLOCK_RESET2 = 0U;
  chartInstance->c81_temporalCounter_i2 = 0U;
  chartInstance->c81_is_SERVICE_CLOCK = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_SERVICE_CLOCK = 0U;
  chartInstance->c81_d_tp_DEBOUNCE = 0U;
  chartInstance->c81_g_tp_INACTIVE = 0U;
  chartInstance->c81_tp_JUMP_STATE = 0U;
  chartInstance->c81_tp_SERVICE_CLOCK_RESET = 0U;
  chartInstance->c81_temporalCounter_i2 = 0U;
  chartInstance->c81_tp_EMEA_CONTROLS = 0U;
  chartInstance->c81_temporalCounter_i1 = 0U;
  chartInstance->c81_b_tp_ERROR_CODES = 0U;
  chartInstance->c81_temporalCounter_i1 = 0U;
  chartInstance->c81_h_tp_INACTIVE = 0U;
  chartInstance->c81_tp_SECOND_AUX = 0U;
  chartInstance->c81_is_active_SECONDARY_STATE = 0U;
  chartInstance->c81_is_SECONDARY_STATE = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_SECONDARY_STATE = 0U;
  chartInstance->c81_tp_DELUXE_ERROR = 0U;
  chartInstance->c81_is_DELUXE_GOOD = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_DELUXE_GOOD = 0U;
  chartInstance->c81_tp_KSS = 0U;
  chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_NON_SHUTDOWN = 0U;
  chartInstance->c81_is_Aux_Detent_Error = c81_IN_NO_ACTIVE_CHILD;
  chartInstance->c81_tp_Aux_Detent_Error = 0U;
  chartInstance->c81_temporalCounter_i3 = 0U;
  chartInstance->c81_tp_AUX = 0U;
  chartInstance->c81_temporalCounter_i4 = 0U;
  chartInstance->c81_tp_HOLD = 0U;
  chartInstance->c81_temporalCounter_i4 = 0U;
  chartInstance->c81_tp_COLD = 0U;
  chartInstance->c81_tp_FLASH_COLD = 0U;
  chartInstance->c81_tp_GLOW_PLUGS = 0U;
  chartInstance->c81_tp_NO_STATE = 0U;
  chartInstance->c81_tp_OFFSET = 0U;
  chartInstance->c81_temporalCounter_i3 = 0U;
  chartInstance->c81_tp_SERVICE_CLOCK_ALARM = 0U;
  chartInstance->c81_tp_THROTTLE_CAL_DIAGNOSTICS = 0U;
  chartInstance->c81_temporalCounter_i3 = 0U;
  chartInstance->c81_tp_SHUTDOWN = 0U;
  chartInstance->c81_tp_VERSION = 0U;
  chartInstance->c81_is_active_c81_MX_Gtwy_Control = 0U;
  chartInstance->c81_debounceCount = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
  chartInstance->c81_serviceClockAlarmTimer = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_serviceClockAlarmTimer, 7U);
  chartInstance->c81_shutdownTimer = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_shutdownTimer, 8U);
  chartInstance->c81_state_Jump = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
  chartInstance->c81_state_LightButton = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_LightButton, 10U);
  chartInstance->c81_debounceButton = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceButton, 0U);
  chartInstance->c81_debounceLeft = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceLeft, 3U);
  chartInstance->c81_debounceRight = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceRight, 4U);
  chartInstance->c81_prev_InfoSecondary = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_InfoSecondary, 5U);
  chartInstance->c81_debounceCode = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCode, 1U);
  chartInstance->c81_prev_SecondAux = false;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_SecondAux, 6U);
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c81_state_InfoPrimary = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c81_state_InfoButton = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *chartInstance->c81_state_InfoSecondary = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary, 30U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 4) != 0)) {
    *chartInstance->c81_state_LeftButton = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_LeftButton, 31U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 5) != 0)) {
    *chartInstance->c81_state_RightButton = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_RightButton, 32U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 6) != 0)) {
    *chartInstance->c81_enable_RightLeft = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
  }
}

static void initialize_params_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  real_T c81_d0;
  real_T c81_d1;
  real_T c81_d2;
  real_T c81_d3;
  real_T c81_d4;
  real_T c81_d5;
  real_T c81_d6;
  real_T c81_d7;
  real_T c81_d8;
  real_T c81_d9;
  real_T c81_d10;
  real_T c81_d11;
  real_T c81_d12;
  real_T c81_d13;
  real_T c81_d14;
  real_T c81_d15;
  real_T c81_d16;
  real_T c81_d17;
  real_T c81_d18;
  real_T c81_d19;
  real_T c81_d20;
  real_T c81_d21;
  real_T c81_d22;
  real_T c81_d23;
  real_T c81_d24;
  real_T c81_d25;
  real_T c81_d26;
  real_T c81_d27;
  real_T c81_d28;
  real_T c81_d29;
  real_T c81_d30;
  real_T c81_d31;
  real_T c81_d32;
  real_T c81_d33;
  real_T c81_d34;
  real_T c81_d35;
  real_T c81_d36;
  real_T c81_d37;
  real_T c81_d38;
  real_T c81_d39;
  real_T c81_d40;
  real_T c81_d41;
  real_T c81_d42;
  real_T c81_d43;
  real_T c81_d44;
  real_T c81_d45;
  real_T c81_d46;
  real_T c81_d47;
  real_T c81_d48;
  real_T c81_d49;
  real_T c81_d50;
  real_T c81_d51;
  real_T c81_d52;
  real_T c81_d53;
  real_T c81_d54;
  real_T c81_d55;
  real_T c81_d56;
  real_T c81_d57;
  real_T c81_d58;
  real_T c81_d59;
  real_T c81_d60;
  real_T c81_d61;
  sf_mex_import_named("ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c81_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_ACTIVE = (uint8_T)c81_d0;
  sf_mex_import_named("DISPLAY_BATTERY_VOLTAGE", sf_mex_get_sfun_param
                      (chartInstance->S, 17, 0), &c81_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_BATTERY_VOLTAGE = (uint8_T)c81_d1;
  sf_mex_import_named("DISPLAY_ENGINE_HOURS", sf_mex_get_sfun_param
                      (chartInstance->S, 23, 0), &c81_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_ENGINE_HOURS = (uint8_T)c81_d2;
  sf_mex_import_named("DISPLAY_ENGINE_RPM", sf_mex_get_sfun_param
                      (chartInstance->S, 24, 0), &c81_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_ENGINE_RPM = (uint8_T)c81_d3;
  sf_mex_import_named("DISPLAY_ERROR_CODES", sf_mex_get_sfun_param
                      (chartInstance->S, 26, 0), &c81_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_ERROR_CODES = (uint8_T)c81_d4;
  sf_mex_import_named("DISPLAY_GLOW_PLUGS", sf_mex_get_sfun_param
                      (chartInstance->S, 28, 0), &c81_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_GLOW_PLUGS = (uint8_T)c81_d5;
  sf_mex_import_named("DISPLAY_SECOND_AUX", sf_mex_get_sfun_param
                      (chartInstance->S, 35, 0), &c81_d6, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_SECOND_AUX = (uint8_T)c81_d6;
  sf_mex_import_named("INACTIVE", sf_mex_get_sfun_param(chartInstance->S, 45, 0),
                      &c81_d7, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_INACTIVE = (uint8_T)c81_d7;
  sf_mex_import_named("CD_DISPLAY_SERVICE_CLOCK_ALARM_TIME",
                      sf_mex_get_sfun_param(chartInstance->S, 9, 0), &c81_d8, 0,
                      0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_DISPLAY_SERVICE_CLOCK_ALARM_TIME = (uint16_T)c81_d8;
  sf_mex_import_named("DISPLAY_SERVICE_CLOCK_ALARM", sf_mex_get_sfun_param
                      (chartInstance->S, 37, 0), &c81_d9, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_SERVICE_CLOCK_ALARM = (uint8_T)c81_d9;
  sf_mex_import_named("CD_DISPLAY_SHUTDOWN_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 10, 0), &c81_d10, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_DISPLAY_SHUTDOWN_TIME = (uint16_T)c81_d10;
  sf_mex_import_named("SHUTDOWN", sf_mex_get_sfun_param(chartInstance->S, 61, 0),
                      &c81_d11, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_SHUTDOWN = (uint8_T)c81_d11;
  sf_mex_import_named("DISPLAY_SHUTDOWN", sf_mex_get_sfun_param(chartInstance->S,
    39, 0), &c81_d12, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_SHUTDOWN = (uint8_T)c81_d12;
  sf_mex_import_named("DISPLAY_SERVICE_CLOCK_RESET", sf_mex_get_sfun_param
                      (chartInstance->S, 38, 0), &c81_d13, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_SERVICE_CLOCK_RESET = (uint8_T)c81_d13;
  sf_mex_import_named("MULTIPLE", sf_mex_get_sfun_param(chartInstance->S, 55, 0),
                      &c81_d14, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_MULTIPLE = (uint8_T)c81_d14;
  sf_mex_import_named("DISPLAY_VERSION", sf_mex_get_sfun_param(chartInstance->S,
    40, 0), &c81_d15, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_VERSION = (uint8_T)c81_d15;
  sf_mex_import_named("DISPLAY_DELUXE_ERROR", sf_mex_get_sfun_param
                      (chartInstance->S, 20, 0), &c81_d16, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_DELUXE_ERROR = (uint8_T)c81_d16;
  sf_mex_import_named("NO_COMMUNICATION", sf_mex_get_sfun_param(chartInstance->S,
    58, 0), &c81_d17, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_NO_COMMUNICATION = (uint8_T)c81_d17;
  sf_mex_import_named("INFO_BUTTON_MASK", sf_mex_get_sfun_param(chartInstance->S,
    46, 0), &c81_d18, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_INFO_BUTTON_MASK = (uint8_T)c81_d18;
  sf_mex_import_named("INFO_BUTTON_PRESS", sf_mex_get_sfun_param
                      (chartInstance->S, 47, 0), &c81_d19, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_INFO_BUTTON_PRESS = (uint8_T)c81_d19;
  sf_mex_import_named("LIGHT_BUTTON_MASK", sf_mex_get_sfun_param
                      (chartInstance->S, 50, 0), &c81_d20, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_LIGHT_BUTTON_MASK = (uint8_T)c81_d20;
  sf_mex_import_named("LIGHT_BUTTON_PRESS", sf_mex_get_sfun_param
                      (chartInstance->S, 51, 0), &c81_d21, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_LIGHT_BUTTON_PRESS = (uint8_T)c81_d21;
  sf_mex_import_named("DISPLAY_EOP", sf_mex_get_sfun_param(chartInstance->S, 25,
    0), &c81_d22, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_EOP = (uint8_T)c81_d22;
  sf_mex_import_named("DISPLAY_ECT", sf_mex_get_sfun_param(chartInstance->S, 21,
    0), &c81_d23, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_ECT = (uint8_T)c81_d23;
  sf_mex_import_named("DISPLAY_HOT", sf_mex_get_sfun_param(chartInstance->S, 30,
    0), &c81_d24, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_HOT = (uint8_T)c81_d24;
  sf_mex_import_named("LEFT_BUTTON_MASK", sf_mex_get_sfun_param(chartInstance->S,
    48, 0), &c81_d25, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_LEFT_BUTTON_MASK = (uint8_T)c81_d25;
  sf_mex_import_named("RIGHT_BUTTON_PRESS", sf_mex_get_sfun_param
                      (chartInstance->S, 60, 0), &c81_d26, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_RIGHT_BUTTON_PRESS = (uint8_T)c81_d26;
  sf_mex_import_named("RIGHT_BUTTON_MASK", sf_mex_get_sfun_param
                      (chartInstance->S, 59, 0), &c81_d27, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_RIGHT_BUTTON_MASK = (uint8_T)c81_d27;
  sf_mex_import_named("LEFT_BUTTON_PRESS", sf_mex_get_sfun_param
                      (chartInstance->S, 49, 0), &c81_d28, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_LEFT_BUTTON_PRESS = (uint8_T)c81_d28;
  sf_mex_import_named("NON_FUNCTIONAL", sf_mex_get_sfun_param(chartInstance->S,
    56, 0), &c81_d29, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_NON_FUNCTIONAL = (uint8_T)c81_d29;
  sf_mex_import_named("CD_AUX_DETENT_FLASH_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 5, 0), &c81_d30, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_AUX_DETENT_FLASH_TIME = (uint16_T)c81_d30;
  sf_mex_import_named("ERR_DETENT", sf_mex_get_sfun_param(chartInstance->S, 42,
    0), &c81_d31, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_ERR_DETENT = (uint8_T)c81_d31;
  sf_mex_import_named("DISPLAY_HOLD", sf_mex_get_sfun_param(chartInstance->S, 29,
    0), &c81_d32, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_HOLD = (uint8_T)c81_d32;
  sf_mex_import_named("DISPLAY_AUX", sf_mex_get_sfun_param(chartInstance->S, 16,
    0), &c81_d33, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_AUX = (uint8_T)c81_d33;
  sf_mex_import_named("CD_AUX_DETENT_CYCLE_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 4, 0), &c81_d34, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_AUX_DETENT_CYCLE_TIME = (uint16_T)c81_d34;
  sf_mex_import_named("DISPLAY_JOB_CLOCK_1", sf_mex_get_sfun_param
                      (chartInstance->S, 31, 0), &c81_d35, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_JOB_CLOCK_1 = (uint8_T)c81_d35;
  sf_mex_import_named("DISPLAY_JOB_CLOCK_2", sf_mex_get_sfun_param
                      (chartInstance->S, 32, 0), &c81_d36, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_JOB_CLOCK_2 = (uint8_T)c81_d36;
  sf_mex_import_named("NORMAL", sf_mex_get_sfun_param(chartInstance->S, 57, 0),
                      &c81_d37, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_NORMAL = (uint8_T)c81_d37;
  sf_mex_import_named("DISPLAY_CAN_THROTTLE_DIAG", sf_mex_get_sfun_param
                      (chartInstance->S, 18, 0), &c81_d38, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_CAN_THROTTLE_DIAG = (uint8_T)c81_d38;
  sf_mex_import_named("CD_CAN_THROTTLE_CAL_DIAG_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 7, 0), &c81_d39, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_CAN_THROTTLE_CAL_DIAG_TIME = (uint16_T)c81_d39;
  sf_mex_import_named("DISPLAY_PRIMARY_INACTIVE", sf_mex_get_sfun_param
                      (chartInstance->S, 34, 0), &c81_d40, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_PRIMARY_INACTIVE = (uint8_T)c81_d40;
  sf_mex_import_named("ENGINE_CRANKING", sf_mex_get_sfun_param(chartInstance->S,
    41, 0), &c81_d41, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_ENGINE_CRANKING = (uint8_T)c81_d41;
  sf_mex_import_named("CD_HOT_FUNCTION", sf_mex_get_sfun_param(chartInstance->S,
    13, 0), &c81_d42, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_HOT_FUNCTION = (uint16_T)c81_d42;
  sf_mex_import_named("LOW", sf_mex_get_sfun_param(chartInstance->S, 52, 0),
                      &c81_d43, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_LOW = (uint8_T)c81_d43;
  sf_mex_import_named("EXTREMELY_LOW", sf_mex_get_sfun_param(chartInstance->S,
    44, 0), &c81_d44, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_EXTREMELY_LOW = (uint8_T)c81_d44;
  sf_mex_import_named("EVENT", sf_mex_get_sfun_param(chartInstance->S, 43, 0),
                      &c81_d45, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_EVENT = (uint8_T)c81_d45;
  sf_mex_import_named("DISPLAY_COLD", sf_mex_get_sfun_param(chartInstance->S, 19,
    0), &c81_d46, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_COLD = (uint8_T)c81_d46;
  sf_mex_import_named("DISPLAY_FLASH_COLD", sf_mex_get_sfun_param
                      (chartInstance->S, 27, 0), &c81_d47, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_FLASH_COLD = (uint8_T)c81_d47;
  sf_mex_import_named("CD_AUTO_DISPLAY_FAULT_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 3, 0), &c81_d48, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_AUTO_DISPLAY_FAULT_FUNCTION = (uint8_T)c81_d48;
  sf_mex_import_named("CD_AUTO_DISPLAY_FAULT_DEBOUNCE_ACTIVE",
                      sf_mex_get_sfun_param(chartInstance->S, 2, 0), &c81_d49, 0,
                      0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_AUTO_DISPLAY_FAULT_DEBOUNCE_ACTIVE = (uint16_T)c81_d49;
  sf_mex_import_named("CD_SECOND_AUX_OFFSET_DISP_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 15, 0), &c81_d50, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_SECOND_AUX_OFFSET_DISP_TIME = (uint16_T)c81_d50;
  sf_mex_import_named("DISPLAY_OFFSET", sf_mex_get_sfun_param(chartInstance->S,
    33, 0), &c81_d51, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_OFFSET = (uint8_T)c81_d51;
  sf_mex_import_named("DISPLAY_SERVICE_CLOCK", sf_mex_get_sfun_param
                      (chartInstance->S, 36, 0), &c81_d52, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_SERVICE_CLOCK = (uint8_T)c81_d52;
  sf_mex_import_named("CD_DELUXE_GEN5_5_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 8, 0), &c81_d53, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_DELUXE_GEN5_5_FUNCTION = (uint8_T)c81_d53;
  sf_mex_import_named("CD_AUX_FUNCTION", sf_mex_get_sfun_param(chartInstance->S,
    6, 0), &c81_d54, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_AUX_FUNCTION = (uint8_T)c81_d54;
  sf_mex_import_named("AUX_EMEA_CONTROLS", sf_mex_get_sfun_param
                      (chartInstance->S, 1, 0), &c81_d55, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_AUX_EMEA_CONTROLS = (uint8_T)c81_d55;
  sf_mex_import_named("CD_EMEA_CONTROLS_DISPLAY_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 12, 0), &c81_d56, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_EMEA_CONTROLS_DISPLAY_TIME = (uint16_T)c81_d56;
  sf_mex_import_named("CD_SECOND_AUX_FUNCTION", sf_mex_get_sfun_param
                      (chartInstance->S, 14, 0), &c81_d57, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_SECOND_AUX_FUNCTION = (uint8_T)c81_d57;
  sf_mex_import_named("DISPLAY_EMEA_CONTROLS", sf_mex_get_sfun_param
                      (chartInstance->S, 22, 0), &c81_d58, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_DISPLAY_EMEA_CONTROLS = (uint8_T)c81_d58;
  sf_mex_import_named("MODE_LEFT_NONE", sf_mex_get_sfun_param(chartInstance->S,
    53, 0), &c81_d59, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_MODE_LEFT_NONE = (uint8_T)c81_d59;
  sf_mex_import_named("MODE_RIGHT_NONE", sf_mex_get_sfun_param(chartInstance->S,
    54, 0), &c81_d60, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_MODE_RIGHT_NONE = (uint8_T)c81_d60;
  sf_mex_import_named("CD_EMEA_CONTROLS_DISPLAY_MODE", sf_mex_get_sfun_param
                      (chartInstance->S, 11, 0), &c81_d61, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c81_CD_EMEA_CONTROLS_DISPLAY_MODE = (uint8_T)c81_d61;
}

static void enable_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c81_update_debugger_state_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  uint32_T c81_prevAniVal;
  c81_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c81_is_active_c81_MX_Gtwy_Control == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 78U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_active_BUTTON_STATE == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_active_INFO_BUTTON == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_INFO_BUTTON == c81_IN_INACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_INFO_BUTTON == c81_IN_EDGE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_INFO_BUTTON == c81_IN_INACTIVE_WAIT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_INFO_BUTTON == c81_IN_ACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_active_MOVE_RIGHT == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_active_PANEL_BUTTON == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_PANEL_BUTTON == c81_IN_INACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_PANEL_BUTTON == c81_IN_EDGE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_PANEL_BUTTON == c81_IN_INACTIVE_WAIT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_PANEL_BUTTON == c81_IN_ACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_active_MOVE_LEFT == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_b_is_active_PANEL_BUTTON == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_b_is_PANEL_BUTTON == c81_IN_INACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_b_is_PANEL_BUTTON == c81_IN_EDGE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_b_is_PANEL_BUTTON == c81_IN_INACTIVE_WAIT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_b_is_PANEL_BUTTON == c81_IN_ACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_active_PRIMARY_STATE == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_PRIMARY_STATE == c81_IN_ACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_ENGINE_HOURS) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ENGINE_HOURS == c81_IN_RESET_STATE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 30U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ENGINE_HOURS == c81_c_IN_INACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ENGINE_HOURS == c81_IN_DEBOUNCE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 28U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_JOB_CLOCK_1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_JOB_CLOCK_1 == c81_IN_RESET_STATE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 41U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_JOB_CLOCK_1 == c81_c_IN_INACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_JOB_CLOCK_1 == c81_IN_DEBOUNCE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_JOB_CLOCK_RESET1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 46U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_JOB_CLOCK_2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_JOB_CLOCK_2 == c81_IN_RESET_STATE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 45U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 45U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_JOB_CLOCK_2 == c81_c_IN_INACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_JOB_CLOCK_2 == c81_IN_DEBOUNCE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_JOB_CLOCK_RESET2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 47U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 47U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_FACTORY) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 34U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_FACTORY == c81_IN_HOT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_FACTORY == c81_b_IN_ECT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_ENGINE_RPM) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_EMEA_CONTROLS1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_BATTERY_VOLTAGE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_SERVICE_CLOCK_RESET) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 52U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 52U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_SERVICE_CLOCK) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 48U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 48U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_SERVICE_CLOCK == c81_c_IN_INACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 50U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 50U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_SERVICE_CLOCK == c81_IN_JUMP_STATE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 51U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 51U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_SERVICE_CLOCK == c81_IN_DEBOUNCE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 49U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 49U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_b_IN_ERROR_CODES) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_EOP) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_ECT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_ACTIVE == c81_IN_HOT2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_PRIMARY_STATE == c81_IN_SECOND_AUX) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 56U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 56U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_PRIMARY_STATE == c81_b_IN_INACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 55U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 55U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_PRIMARY_STATE == c81_IN_ERROR_CODES) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 54U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 54U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_PRIMARY_STATE == c81_IN_EMEA_CONTROLS) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 53U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 53U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_active_SECONDARY_STATE == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 57U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 57U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_SECONDARY_STATE == c81_IN_DELUXE_GOOD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 59U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 59U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_DELUXE_GOOD == c81_IN_VERSION) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 73U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 73U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_DELUXE_GOOD == c81_IN_NON_SHUTDOWN) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_FLASH_COLD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 66U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 66U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_COLD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 65U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 65U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_SERVICE_CLOCK_ALARM) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 70U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 70U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_NO_STATE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_GLOW_PLUGS) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 67U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 67U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_THROTTLE_CAL_DIAGNOSTICS) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 71U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 71U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_OFFSET) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 69U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 69U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_Aux_Detent_Error) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 62U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 62U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_Aux_Detent_Error == c81_IN_HOLD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 64U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 64U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_Aux_Detent_Error == c81_IN_AUX) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 63U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 63U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_DELUXE_GOOD == c81_IN_KSS) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 60U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 60U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_DELUXE_GOOD == c81_IN_SHUTDOWN) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 72U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 72U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_SECONDARY_STATE == c81_IN_DELUXE_ERROR) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 58U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 58U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_active_LIGHT_BUTTON_STATE == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_LIGHT_BUTTON_STATE == c81_IN_INACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_LIGHT_BUTTON_STATE == c81_IN_EDGE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c81_sfEvent);
  }

  if (chartInstance->c81_is_LIGHT_BUTTON_STATE == c81_IN_ACTIVE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c81_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c81_sfEvent);
  }

  _SFD_SET_ANIMATION(c81_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  const mxArray *c81_st;
  const mxArray *c81_y = NULL;
  uint8_T c81_hoistedGlobal;
  const mxArray *c81_b_y = NULL;
  uint8_T c81_b_hoistedGlobal;
  const mxArray *c81_c_y = NULL;
  uint8_T c81_c_hoistedGlobal;
  const mxArray *c81_d_y = NULL;
  uint8_T c81_d_hoistedGlobal;
  const mxArray *c81_e_y = NULL;
  uint8_T c81_e_hoistedGlobal;
  const mxArray *c81_f_y = NULL;
  uint8_T c81_f_hoistedGlobal;
  const mxArray *c81_g_y = NULL;
  uint16_T c81_g_hoistedGlobal;
  const mxArray *c81_h_y = NULL;
  uint16_T c81_h_hoistedGlobal;
  const mxArray *c81_i_y = NULL;
  uint16_T c81_i_hoistedGlobal;
  const mxArray *c81_j_y = NULL;
  uint16_T c81_j_hoistedGlobal;
  const mxArray *c81_k_y = NULL;
  uint16_T c81_k_hoistedGlobal;
  const mxArray *c81_l_y = NULL;
  uint8_T c81_l_hoistedGlobal;
  const mxArray *c81_m_y = NULL;
  boolean_T c81_m_hoistedGlobal;
  const mxArray *c81_n_y = NULL;
  uint16_T c81_n_hoistedGlobal;
  const mxArray *c81_o_y = NULL;
  uint16_T c81_o_hoistedGlobal;
  const mxArray *c81_p_y = NULL;
  uint8_T c81_p_hoistedGlobal;
  const mxArray *c81_q_y = NULL;
  uint8_T c81_q_hoistedGlobal;
  const mxArray *c81_r_y = NULL;
  uint8_T c81_r_hoistedGlobal;
  const mxArray *c81_s_y = NULL;
  uint8_T c81_s_hoistedGlobal;
  const mxArray *c81_t_y = NULL;
  uint8_T c81_t_hoistedGlobal;
  const mxArray *c81_u_y = NULL;
  uint8_T c81_u_hoistedGlobal;
  const mxArray *c81_v_y = NULL;
  uint8_T c81_v_hoistedGlobal;
  const mxArray *c81_w_y = NULL;
  uint8_T c81_w_hoistedGlobal;
  const mxArray *c81_x_y = NULL;
  uint8_T c81_x_hoistedGlobal;
  const mxArray *c81_y_y = NULL;
  uint8_T c81_y_hoistedGlobal;
  const mxArray *c81_ab_y = NULL;
  uint8_T c81_ab_hoistedGlobal;
  const mxArray *c81_bb_y = NULL;
  uint8_T c81_bb_hoistedGlobal;
  const mxArray *c81_cb_y = NULL;
  uint8_T c81_cb_hoistedGlobal;
  const mxArray *c81_db_y = NULL;
  uint8_T c81_db_hoistedGlobal;
  const mxArray *c81_eb_y = NULL;
  uint8_T c81_eb_hoistedGlobal;
  const mxArray *c81_fb_y = NULL;
  uint8_T c81_fb_hoistedGlobal;
  const mxArray *c81_gb_y = NULL;
  uint8_T c81_gb_hoistedGlobal;
  const mxArray *c81_hb_y = NULL;
  uint8_T c81_hb_hoistedGlobal;
  const mxArray *c81_ib_y = NULL;
  uint8_T c81_ib_hoistedGlobal;
  const mxArray *c81_jb_y = NULL;
  uint8_T c81_jb_hoistedGlobal;
  const mxArray *c81_kb_y = NULL;
  uint8_T c81_kb_hoistedGlobal;
  const mxArray *c81_lb_y = NULL;
  uint8_T c81_lb_hoistedGlobal;
  const mxArray *c81_mb_y = NULL;
  uint8_T c81_mb_hoistedGlobal;
  const mxArray *c81_nb_y = NULL;
  uint8_T c81_nb_hoistedGlobal;
  const mxArray *c81_ob_y = NULL;
  uint8_T c81_ob_hoistedGlobal;
  const mxArray *c81_pb_y = NULL;
  uint8_T c81_pb_hoistedGlobal;
  const mxArray *c81_qb_y = NULL;
  uint8_T c81_qb_hoistedGlobal;
  const mxArray *c81_rb_y = NULL;
  uint8_T c81_rb_hoistedGlobal;
  const mxArray *c81_sb_y = NULL;
  uint16_T c81_sb_hoistedGlobal;
  const mxArray *c81_tb_y = NULL;
  uint8_T c81_tb_hoistedGlobal;
  const mxArray *c81_ub_y = NULL;
  uint16_T c81_ub_hoistedGlobal;
  const mxArray *c81_vb_y = NULL;
  uint16_T c81_vb_hoistedGlobal;
  const mxArray *c81_wb_y = NULL;
  c81_st = NULL;
  c81_st = NULL;
  c81_y = NULL;
  sf_mex_assign(&c81_y, sf_mex_createcellmatrix(47, 1), false);
  c81_hoistedGlobal = *chartInstance->c81_enable_RightLeft;
  c81_b_y = NULL;
  sf_mex_assign(&c81_b_y, sf_mex_create("y", &c81_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 0, c81_b_y);
  c81_b_hoistedGlobal = *chartInstance->c81_state_InfoButton;
  c81_c_y = NULL;
  sf_mex_assign(&c81_c_y, sf_mex_create("y", &c81_b_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 1, c81_c_y);
  c81_c_hoistedGlobal = *chartInstance->c81_state_InfoPrimary;
  c81_d_y = NULL;
  sf_mex_assign(&c81_d_y, sf_mex_create("y", &c81_c_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 2, c81_d_y);
  c81_d_hoistedGlobal = *chartInstance->c81_state_InfoSecondary;
  c81_e_y = NULL;
  sf_mex_assign(&c81_e_y, sf_mex_create("y", &c81_d_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 3, c81_e_y);
  c81_e_hoistedGlobal = *chartInstance->c81_state_LeftButton;
  c81_f_y = NULL;
  sf_mex_assign(&c81_f_y, sf_mex_create("y", &c81_e_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 4, c81_f_y);
  c81_f_hoistedGlobal = *chartInstance->c81_state_RightButton;
  c81_g_y = NULL;
  sf_mex_assign(&c81_g_y, sf_mex_create("y", &c81_f_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 5, c81_g_y);
  c81_g_hoistedGlobal = chartInstance->c81_debounceButton;
  c81_h_y = NULL;
  sf_mex_assign(&c81_h_y, sf_mex_create("y", &c81_g_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 6, c81_h_y);
  c81_h_hoistedGlobal = chartInstance->c81_debounceCode;
  c81_i_y = NULL;
  sf_mex_assign(&c81_i_y, sf_mex_create("y", &c81_h_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 7, c81_i_y);
  c81_i_hoistedGlobal = chartInstance->c81_debounceCount;
  c81_j_y = NULL;
  sf_mex_assign(&c81_j_y, sf_mex_create("y", &c81_i_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 8, c81_j_y);
  c81_j_hoistedGlobal = chartInstance->c81_debounceLeft;
  c81_k_y = NULL;
  sf_mex_assign(&c81_k_y, sf_mex_create("y", &c81_j_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 9, c81_k_y);
  c81_k_hoistedGlobal = chartInstance->c81_debounceRight;
  c81_l_y = NULL;
  sf_mex_assign(&c81_l_y, sf_mex_create("y", &c81_k_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 10, c81_l_y);
  c81_l_hoistedGlobal = chartInstance->c81_prev_InfoSecondary;
  c81_m_y = NULL;
  sf_mex_assign(&c81_m_y, sf_mex_create("y", &c81_l_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 11, c81_m_y);
  c81_m_hoistedGlobal = chartInstance->c81_prev_SecondAux;
  c81_n_y = NULL;
  sf_mex_assign(&c81_n_y, sf_mex_create("y", &c81_m_hoistedGlobal, 11, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 12, c81_n_y);
  c81_n_hoistedGlobal = chartInstance->c81_serviceClockAlarmTimer;
  c81_o_y = NULL;
  sf_mex_assign(&c81_o_y, sf_mex_create("y", &c81_n_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 13, c81_o_y);
  c81_o_hoistedGlobal = chartInstance->c81_shutdownTimer;
  c81_p_y = NULL;
  sf_mex_assign(&c81_p_y, sf_mex_create("y", &c81_o_hoistedGlobal, 5, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 14, c81_p_y);
  c81_p_hoistedGlobal = chartInstance->c81_state_Jump;
  c81_q_y = NULL;
  sf_mex_assign(&c81_q_y, sf_mex_create("y", &c81_p_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 15, c81_q_y);
  c81_q_hoistedGlobal = chartInstance->c81_state_LightButton;
  c81_r_y = NULL;
  sf_mex_assign(&c81_r_y, sf_mex_create("y", &c81_q_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 16, c81_r_y);
  c81_r_hoistedGlobal = chartInstance->c81_is_active_c81_MX_Gtwy_Control;
  c81_s_y = NULL;
  sf_mex_assign(&c81_s_y, sf_mex_create("y", &c81_r_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 17, c81_s_y);
  c81_s_hoistedGlobal = chartInstance->c81_is_active_SECONDARY_STATE;
  c81_t_y = NULL;
  sf_mex_assign(&c81_t_y, sf_mex_create("y", &c81_s_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 18, c81_t_y);
  c81_t_hoistedGlobal = chartInstance->c81_is_active_BUTTON_STATE;
  c81_u_y = NULL;
  sf_mex_assign(&c81_u_y, sf_mex_create("y", &c81_t_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 19, c81_u_y);
  c81_u_hoistedGlobal = chartInstance->c81_is_active_PRIMARY_STATE;
  c81_v_y = NULL;
  sf_mex_assign(&c81_v_y, sf_mex_create("y", &c81_u_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 20, c81_v_y);
  c81_v_hoistedGlobal = chartInstance->c81_is_active_LIGHT_BUTTON_STATE;
  c81_w_y = NULL;
  sf_mex_assign(&c81_w_y, sf_mex_create("y", &c81_v_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 21, c81_w_y);
  c81_w_hoistedGlobal = chartInstance->c81_is_active_INFO_BUTTON;
  c81_x_y = NULL;
  sf_mex_assign(&c81_x_y, sf_mex_create("y", &c81_w_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 22, c81_x_y);
  c81_x_hoistedGlobal = chartInstance->c81_is_active_MOVE_RIGHT;
  c81_y_y = NULL;
  sf_mex_assign(&c81_y_y, sf_mex_create("y", &c81_x_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c81_y, 23, c81_y_y);
  c81_y_hoistedGlobal = chartInstance->c81_is_active_MOVE_LEFT;
  c81_ab_y = NULL;
  sf_mex_assign(&c81_ab_y, sf_mex_create("y", &c81_y_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 24, c81_ab_y);
  c81_ab_hoistedGlobal = chartInstance->c81_is_active_PANEL_BUTTON;
  c81_bb_y = NULL;
  sf_mex_assign(&c81_bb_y, sf_mex_create("y", &c81_ab_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 25, c81_bb_y);
  c81_bb_hoistedGlobal = chartInstance->c81_b_is_active_PANEL_BUTTON;
  c81_cb_y = NULL;
  sf_mex_assign(&c81_cb_y, sf_mex_create("y", &c81_bb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 26, c81_cb_y);
  c81_cb_hoistedGlobal = chartInstance->c81_is_SECONDARY_STATE;
  c81_db_y = NULL;
  sf_mex_assign(&c81_db_y, sf_mex_create("y", &c81_cb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 27, c81_db_y);
  c81_db_hoistedGlobal = chartInstance->c81_is_NON_SHUTDOWN;
  c81_eb_y = NULL;
  sf_mex_assign(&c81_eb_y, sf_mex_create("y", &c81_db_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 28, c81_eb_y);
  c81_eb_hoistedGlobal = chartInstance->c81_is_PRIMARY_STATE;
  c81_fb_y = NULL;
  sf_mex_assign(&c81_fb_y, sf_mex_create("y", &c81_eb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 29, c81_fb_y);
  c81_fb_hoistedGlobal = chartInstance->c81_is_ENGINE_HOURS;
  c81_gb_y = NULL;
  sf_mex_assign(&c81_gb_y, sf_mex_create("y", &c81_fb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 30, c81_gb_y);
  c81_gb_hoistedGlobal = chartInstance->c81_is_SERVICE_CLOCK;
  c81_hb_y = NULL;
  sf_mex_assign(&c81_hb_y, sf_mex_create("y", &c81_gb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 31, c81_hb_y);
  c81_hb_hoistedGlobal = chartInstance->c81_is_DELUXE_GOOD;
  c81_ib_y = NULL;
  sf_mex_assign(&c81_ib_y, sf_mex_create("y", &c81_hb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 32, c81_ib_y);
  c81_ib_hoistedGlobal = chartInstance->c81_is_LIGHT_BUTTON_STATE;
  c81_jb_y = NULL;
  sf_mex_assign(&c81_jb_y, sf_mex_create("y", &c81_ib_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 33, c81_jb_y);
  c81_jb_hoistedGlobal = chartInstance->c81_is_INFO_BUTTON;
  c81_kb_y = NULL;
  sf_mex_assign(&c81_kb_y, sf_mex_create("y", &c81_jb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 34, c81_kb_y);
  c81_kb_hoistedGlobal = chartInstance->c81_is_PANEL_BUTTON;
  c81_lb_y = NULL;
  sf_mex_assign(&c81_lb_y, sf_mex_create("y", &c81_kb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 35, c81_lb_y);
  c81_lb_hoistedGlobal = chartInstance->c81_b_is_PANEL_BUTTON;
  c81_mb_y = NULL;
  sf_mex_assign(&c81_mb_y, sf_mex_create("y", &c81_lb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 36, c81_mb_y);
  c81_mb_hoistedGlobal = chartInstance->c81_is_JOB_CLOCK_1;
  c81_nb_y = NULL;
  sf_mex_assign(&c81_nb_y, sf_mex_create("y", &c81_mb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 37, c81_nb_y);
  c81_nb_hoistedGlobal = chartInstance->c81_is_JOB_CLOCK_2;
  c81_ob_y = NULL;
  sf_mex_assign(&c81_ob_y, sf_mex_create("y", &c81_nb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 38, c81_ob_y);
  c81_ob_hoistedGlobal = chartInstance->c81_is_Aux_Detent_Error;
  c81_pb_y = NULL;
  sf_mex_assign(&c81_pb_y, sf_mex_create("y", &c81_ob_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 39, c81_pb_y);
  c81_pb_hoistedGlobal = chartInstance->c81_is_FACTORY;
  c81_qb_y = NULL;
  sf_mex_assign(&c81_qb_y, sf_mex_create("y", &c81_pb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 40, c81_qb_y);
  c81_qb_hoistedGlobal = chartInstance->c81_is_ACTIVE;
  c81_rb_y = NULL;
  sf_mex_assign(&c81_rb_y, sf_mex_create("y", &c81_qb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 41, c81_rb_y);
  c81_rb_hoistedGlobal = chartInstance->c81_was_ACTIVE;
  c81_sb_y = NULL;
  sf_mex_assign(&c81_sb_y, sf_mex_create("y", &c81_rb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 42, c81_sb_y);
  c81_sb_hoistedGlobal = chartInstance->c81_temporalCounter_i4;
  c81_tb_y = NULL;
  sf_mex_assign(&c81_tb_y, sf_mex_create("y", &c81_sb_hoistedGlobal, 5, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 43, c81_tb_y);
  c81_tb_hoistedGlobal = chartInstance->c81_temporalCounter_i2;
  c81_ub_y = NULL;
  sf_mex_assign(&c81_ub_y, sf_mex_create("y", &c81_tb_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 44, c81_ub_y);
  c81_ub_hoistedGlobal = chartInstance->c81_temporalCounter_i3;
  c81_vb_y = NULL;
  sf_mex_assign(&c81_vb_y, sf_mex_create("y", &c81_ub_hoistedGlobal, 5, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 45, c81_vb_y);
  c81_vb_hoistedGlobal = chartInstance->c81_temporalCounter_i1;
  c81_wb_y = NULL;
  sf_mex_assign(&c81_wb_y, sf_mex_create("y", &c81_vb_hoistedGlobal, 5, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c81_y, 46, c81_wb_y);
  sf_mex_assign(&c81_st, c81_y, false);
  return c81_st;
}

static void set_sim_state_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c81_st)
{
  const mxArray *c81_u;
  c81_u = sf_mex_dup(c81_st);
  *chartInstance->c81_enable_RightLeft = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 0)), "enable_RightLeft");
  *chartInstance->c81_state_InfoButton = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 1)), "state_InfoButton");
  *chartInstance->c81_state_InfoPrimary = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 2)), "state_InfoPrimary");
  *chartInstance->c81_state_InfoSecondary = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 3)), "state_InfoSecondary");
  *chartInstance->c81_state_LeftButton = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 4)), "state_LeftButton");
  *chartInstance->c81_state_RightButton = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 5)), "state_RightButton");
  chartInstance->c81_debounceButton = c81_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 6)), "debounceButton");
  chartInstance->c81_debounceCode = c81_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 7)), "debounceCode");
  chartInstance->c81_debounceCount = c81_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 8)), "debounceCount");
  chartInstance->c81_debounceLeft = c81_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 9)), "debounceLeft");
  chartInstance->c81_debounceRight = c81_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 10)), "debounceRight");
  chartInstance->c81_prev_InfoSecondary = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 11)), "prev_InfoSecondary");
  chartInstance->c81_prev_SecondAux = c81_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 12)), "prev_SecondAux");
  chartInstance->c81_serviceClockAlarmTimer = c81_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c81_u, 13)),
     "serviceClockAlarmTimer");
  chartInstance->c81_shutdownTimer = c81_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 14)), "shutdownTimer");
  chartInstance->c81_state_Jump = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 15)), "state_Jump");
  chartInstance->c81_state_LightButton = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 16)), "state_LightButton");
  chartInstance->c81_is_active_c81_MX_Gtwy_Control = c81_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c81_u, 17)),
     "is_active_c81_MX_Gtwy_Control");
  chartInstance->c81_is_active_SECONDARY_STATE = c81_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c81_u, 18)),
     "is_active_SECONDARY_STATE");
  chartInstance->c81_is_active_BUTTON_STATE = c81_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c81_u, 19)),
     "is_active_BUTTON_STATE");
  chartInstance->c81_is_active_PRIMARY_STATE = c81_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c81_u, 20)),
     "is_active_PRIMARY_STATE");
  chartInstance->c81_is_active_LIGHT_BUTTON_STATE = c81_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c81_u, 21)),
     "is_active_LIGHT_BUTTON_STATE");
  chartInstance->c81_is_active_INFO_BUTTON = c81_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c81_u, 22)),
     "is_active_INFO_BUTTON");
  chartInstance->c81_is_active_MOVE_RIGHT = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 23)), "is_active_MOVE_RIGHT");
  chartInstance->c81_is_active_MOVE_LEFT = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 24)), "is_active_MOVE_LEFT");
  chartInstance->c81_is_active_PANEL_BUTTON = c81_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c81_u, 25)),
     "is_active_PANEL_BUTTON");
  chartInstance->c81_b_is_active_PANEL_BUTTON = c81_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c81_u, 26)),
     "is_active_PANEL_BUTTON");
  chartInstance->c81_is_SECONDARY_STATE = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 27)), "is_SECONDARY_STATE");
  chartInstance->c81_is_NON_SHUTDOWN = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 28)), "is_NON_SHUTDOWN");
  chartInstance->c81_is_PRIMARY_STATE = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 29)), "is_PRIMARY_STATE");
  chartInstance->c81_is_ENGINE_HOURS = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 30)), "is_ENGINE_HOURS");
  chartInstance->c81_is_SERVICE_CLOCK = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 31)), "is_SERVICE_CLOCK");
  chartInstance->c81_is_DELUXE_GOOD = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 32)), "is_DELUXE_GOOD");
  chartInstance->c81_is_LIGHT_BUTTON_STATE = c81_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c81_u, 33)),
     "is_LIGHT_BUTTON_STATE");
  chartInstance->c81_is_INFO_BUTTON = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 34)), "is_INFO_BUTTON");
  chartInstance->c81_is_PANEL_BUTTON = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 35)), "is_PANEL_BUTTON");
  chartInstance->c81_b_is_PANEL_BUTTON = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 36)), "is_PANEL_BUTTON");
  chartInstance->c81_is_JOB_CLOCK_1 = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 37)), "is_JOB_CLOCK_1");
  chartInstance->c81_is_JOB_CLOCK_2 = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 38)), "is_JOB_CLOCK_2");
  chartInstance->c81_is_Aux_Detent_Error = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 39)), "is_Aux_Detent_Error");
  chartInstance->c81_is_FACTORY = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 40)), "is_FACTORY");
  chartInstance->c81_is_ACTIVE = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 41)), "is_ACTIVE");
  chartInstance->c81_was_ACTIVE = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 42)), "was_ACTIVE");
  chartInstance->c81_temporalCounter_i4 = c81_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 43)), "temporalCounter_i4");
  chartInstance->c81_temporalCounter_i2 = c81_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 44)), "temporalCounter_i2");
  chartInstance->c81_temporalCounter_i3 = c81_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 45)), "temporalCounter_i3");
  chartInstance->c81_temporalCounter_i1 = c81_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c81_u, 46)), "temporalCounter_i1");
  sf_mex_assign(&chartInstance->c81_setSimStateSideEffectsInfo,
                c81_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c81_u, 47)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c81_u);
  chartInstance->c81_doSetSimStateSideEffects = 1U;
  c81_update_debugger_state_c81_MX_Gtwy_Control(chartInstance);
  sf_mex_destroy(&c81_st);
}

static void c81_set_sim_state_side_effects_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  if (chartInstance->c81_doSetSimStateSideEffects != 0) {
    chartInstance->c81_tp_BUTTON_STATE = (uint8_T)
      (chartInstance->c81_is_active_BUTTON_STATE == 1U);
    chartInstance->c81_tp_INFO_BUTTON = (uint8_T)
      (chartInstance->c81_is_active_INFO_BUTTON == 1U);
    chartInstance->c81_tp_ACTIVE = (uint8_T)(chartInstance->c81_is_INFO_BUTTON ==
      c81_IN_ACTIVE);
    chartInstance->c81_tp_EDGE = (uint8_T)(chartInstance->c81_is_INFO_BUTTON ==
      c81_IN_EDGE);
    chartInstance->c81_tp_INACTIVE = (uint8_T)(chartInstance->c81_is_INFO_BUTTON
      == c81_IN_INACTIVE);
    chartInstance->c81_tp_INACTIVE_WAIT = (uint8_T)
      (chartInstance->c81_is_INFO_BUTTON == c81_IN_INACTIVE_WAIT);
    chartInstance->c81_tp_MOVE_RIGHT = (uint8_T)
      (chartInstance->c81_is_active_MOVE_RIGHT == 1U);
    chartInstance->c81_tp_PANEL_BUTTON = (uint8_T)
      (chartInstance->c81_is_active_PANEL_BUTTON == 1U);
    chartInstance->c81_b_tp_ACTIVE = (uint8_T)
      (chartInstance->c81_is_PANEL_BUTTON == c81_IN_ACTIVE);
    chartInstance->c81_b_tp_EDGE = (uint8_T)(chartInstance->c81_is_PANEL_BUTTON ==
      c81_IN_EDGE);
    chartInstance->c81_b_tp_INACTIVE = (uint8_T)
      (chartInstance->c81_is_PANEL_BUTTON == c81_IN_INACTIVE);
    chartInstance->c81_b_tp_INACTIVE_WAIT = (uint8_T)
      (chartInstance->c81_is_PANEL_BUTTON == c81_IN_INACTIVE_WAIT);
    chartInstance->c81_tp_MOVE_LEFT = (uint8_T)
      (chartInstance->c81_is_active_MOVE_LEFT == 1U);
    chartInstance->c81_b_tp_PANEL_BUTTON = (uint8_T)
      (chartInstance->c81_b_is_active_PANEL_BUTTON == 1U);
    chartInstance->c81_c_tp_ACTIVE = (uint8_T)
      (chartInstance->c81_b_is_PANEL_BUTTON == c81_IN_ACTIVE);
    chartInstance->c81_c_tp_EDGE = (uint8_T)
      (chartInstance->c81_b_is_PANEL_BUTTON == c81_IN_EDGE);
    chartInstance->c81_c_tp_INACTIVE = (uint8_T)
      (chartInstance->c81_b_is_PANEL_BUTTON == c81_IN_INACTIVE);
    chartInstance->c81_c_tp_INACTIVE_WAIT = (uint8_T)
      (chartInstance->c81_b_is_PANEL_BUTTON == c81_IN_INACTIVE_WAIT);
    chartInstance->c81_tp_SECONDARY_STATE = (uint8_T)
      (chartInstance->c81_is_active_SECONDARY_STATE == 1U);
    chartInstance->c81_tp_DELUXE_ERROR = (uint8_T)
      (chartInstance->c81_is_SECONDARY_STATE == c81_IN_DELUXE_ERROR);
    chartInstance->c81_tp_DELUXE_GOOD = (uint8_T)
      (chartInstance->c81_is_SECONDARY_STATE == c81_IN_DELUXE_GOOD);
    chartInstance->c81_tp_KSS = (uint8_T)(chartInstance->c81_is_DELUXE_GOOD ==
      c81_IN_KSS);
    chartInstance->c81_tp_NON_SHUTDOWN = (uint8_T)
      (chartInstance->c81_is_DELUXE_GOOD == c81_IN_NON_SHUTDOWN);
    if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_Aux_Detent_Error) {
      chartInstance->c81_tp_Aux_Detent_Error = 1U;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 25) == 0.0) {
        chartInstance->c81_temporalCounter_i3 = 0U;
      }
    } else {
      chartInstance->c81_tp_Aux_Detent_Error = 0U;
    }

    if (chartInstance->c81_is_Aux_Detent_Error == c81_IN_AUX) {
      chartInstance->c81_tp_AUX = 1U;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 26) == 0.0) {
        chartInstance->c81_temporalCounter_i4 = 0U;
      }
    } else {
      chartInstance->c81_tp_AUX = 0U;
    }

    if (chartInstance->c81_is_Aux_Detent_Error == c81_IN_HOLD) {
      chartInstance->c81_tp_HOLD = 1U;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 27) == 0.0) {
        chartInstance->c81_temporalCounter_i4 = 0U;
      }
    } else {
      chartInstance->c81_tp_HOLD = 0U;
    }

    chartInstance->c81_tp_COLD = (uint8_T)(chartInstance->c81_is_NON_SHUTDOWN ==
      c81_IN_COLD);
    chartInstance->c81_tp_FLASH_COLD = (uint8_T)
      (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_FLASH_COLD);
    chartInstance->c81_tp_GLOW_PLUGS = (uint8_T)
      (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_GLOW_PLUGS);
    chartInstance->c81_tp_NO_STATE = (uint8_T)
      (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_NO_STATE);
    if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_OFFSET) {
      chartInstance->c81_tp_OFFSET = 1U;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 32) == 0.0) {
        chartInstance->c81_temporalCounter_i3 = 0U;
      }
    } else {
      chartInstance->c81_tp_OFFSET = 0U;
    }

    chartInstance->c81_tp_SERVICE_CLOCK_ALARM = (uint8_T)
      (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_SERVICE_CLOCK_ALARM);
    if (chartInstance->c81_is_NON_SHUTDOWN == c81_IN_THROTTLE_CAL_DIAGNOSTICS) {
      chartInstance->c81_tp_THROTTLE_CAL_DIAGNOSTICS = 1U;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 34) == 0.0) {
        chartInstance->c81_temporalCounter_i3 = 0U;
      }
    } else {
      chartInstance->c81_tp_THROTTLE_CAL_DIAGNOSTICS = 0U;
    }

    chartInstance->c81_tp_SHUTDOWN = (uint8_T)(chartInstance->c81_is_DELUXE_GOOD
      == c81_IN_SHUTDOWN);
    chartInstance->c81_tp_VERSION = (uint8_T)(chartInstance->c81_is_DELUXE_GOOD ==
      c81_IN_VERSION);
    chartInstance->c81_tp_PRIMARY_STATE = (uint8_T)
      (chartInstance->c81_is_active_PRIMARY_STATE == 1U);
    if (chartInstance->c81_is_PRIMARY_STATE == c81_IN_ACTIVE) {
      chartInstance->c81_d_tp_ACTIVE = 1U;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 38) == 0.0) {
        chartInstance->c81_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c81_d_tp_ACTIVE = 0U;
    }

    if (chartInstance->c81_is_ACTIVE == c81_IN_BATTERY_VOLTAGE) {
      chartInstance->c81_tp_BATTERY_VOLTAGE = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_BATTERY_VOLTAGE;
    } else {
      chartInstance->c81_tp_BATTERY_VOLTAGE = 0U;
    }

    if (chartInstance->c81_is_ACTIVE == c81_IN_ECT) {
      chartInstance->c81_b_tp_ECT = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_ECT;
    } else {
      chartInstance->c81_b_tp_ECT = 0U;
    }

    if (chartInstance->c81_is_ACTIVE == c81_IN_EMEA_CONTROLS1) {
      chartInstance->c81_tp_EMEA_CONTROLS1 = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_EMEA_CONTROLS1;
    } else {
      chartInstance->c81_tp_EMEA_CONTROLS1 = 0U;
    }

    if (chartInstance->c81_is_ACTIVE == c81_IN_ENGINE_HOURS) {
      chartInstance->c81_tp_ENGINE_HOURS = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_ENGINE_HOURS;
    } else {
      chartInstance->c81_tp_ENGINE_HOURS = 0U;
    }

    chartInstance->c81_tp_DEBOUNCE = (uint8_T)
      (chartInstance->c81_is_ENGINE_HOURS == c81_IN_DEBOUNCE);
    chartInstance->c81_d_tp_INACTIVE = (uint8_T)
      (chartInstance->c81_is_ENGINE_HOURS == c81_c_IN_INACTIVE);
    chartInstance->c81_tp_RESET_STATE = (uint8_T)
      (chartInstance->c81_is_ENGINE_HOURS == c81_IN_RESET_STATE);
    if (chartInstance->c81_is_ACTIVE == c81_IN_ENGINE_RPM) {
      chartInstance->c81_tp_ENGINE_RPM = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_ENGINE_RPM;
    } else {
      chartInstance->c81_tp_ENGINE_RPM = 0U;
    }

    if (chartInstance->c81_is_ACTIVE == c81_IN_EOP) {
      chartInstance->c81_tp_EOP = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_EOP;
    } else {
      chartInstance->c81_tp_EOP = 0U;
    }

    if (chartInstance->c81_is_ACTIVE == c81_b_IN_ERROR_CODES) {
      chartInstance->c81_tp_ERROR_CODES = 1U;
      chartInstance->c81_was_ACTIVE = c81_b_IN_ERROR_CODES;
    } else {
      chartInstance->c81_tp_ERROR_CODES = 0U;
    }

    if (chartInstance->c81_is_ACTIVE == c81_IN_FACTORY) {
      chartInstance->c81_tp_FACTORY = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_FACTORY;
    } else {
      chartInstance->c81_tp_FACTORY = 0U;
    }

    chartInstance->c81_tp_ECT = (uint8_T)(chartInstance->c81_is_FACTORY ==
      c81_b_IN_ECT);
    chartInstance->c81_tp_HOT = (uint8_T)(chartInstance->c81_is_FACTORY ==
      c81_IN_HOT);
    if (chartInstance->c81_is_ACTIVE == c81_IN_HOT2) {
      chartInstance->c81_tp_HOT2 = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_HOT2;
    } else {
      chartInstance->c81_tp_HOT2 = 0U;
    }

    if (chartInstance->c81_is_ACTIVE == c81_IN_JOB_CLOCK_1) {
      chartInstance->c81_tp_JOB_CLOCK_1 = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_1;
    } else {
      chartInstance->c81_tp_JOB_CLOCK_1 = 0U;
    }

    chartInstance->c81_b_tp_DEBOUNCE = (uint8_T)
      (chartInstance->c81_is_JOB_CLOCK_1 == c81_IN_DEBOUNCE);
    chartInstance->c81_e_tp_INACTIVE = (uint8_T)
      (chartInstance->c81_is_JOB_CLOCK_1 == c81_c_IN_INACTIVE);
    chartInstance->c81_b_tp_RESET_STATE = (uint8_T)
      (chartInstance->c81_is_JOB_CLOCK_1 == c81_IN_RESET_STATE);
    if (chartInstance->c81_is_ACTIVE == c81_IN_JOB_CLOCK_2) {
      chartInstance->c81_tp_JOB_CLOCK_2 = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_2;
    } else {
      chartInstance->c81_tp_JOB_CLOCK_2 = 0U;
    }

    chartInstance->c81_c_tp_DEBOUNCE = (uint8_T)
      (chartInstance->c81_is_JOB_CLOCK_2 == c81_IN_DEBOUNCE);
    chartInstance->c81_f_tp_INACTIVE = (uint8_T)
      (chartInstance->c81_is_JOB_CLOCK_2 == c81_c_IN_INACTIVE);
    chartInstance->c81_c_tp_RESET_STATE = (uint8_T)
      (chartInstance->c81_is_JOB_CLOCK_2 == c81_IN_RESET_STATE);
    if (chartInstance->c81_is_ACTIVE == c81_IN_JOB_CLOCK_RESET1) {
      chartInstance->c81_tp_JOB_CLOCK_RESET1 = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_RESET1;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 61) == 0.0) {
        chartInstance->c81_temporalCounter_i2 = 0U;
      }
    } else {
      chartInstance->c81_tp_JOB_CLOCK_RESET1 = 0U;
    }

    if (chartInstance->c81_is_ACTIVE == c81_IN_JOB_CLOCK_RESET2) {
      chartInstance->c81_tp_JOB_CLOCK_RESET2 = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_RESET2;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 62) == 0.0) {
        chartInstance->c81_temporalCounter_i2 = 0U;
      }
    } else {
      chartInstance->c81_tp_JOB_CLOCK_RESET2 = 0U;
    }

    if (chartInstance->c81_is_ACTIVE == c81_IN_SERVICE_CLOCK) {
      chartInstance->c81_tp_SERVICE_CLOCK = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_SERVICE_CLOCK;
    } else {
      chartInstance->c81_tp_SERVICE_CLOCK = 0U;
    }

    chartInstance->c81_d_tp_DEBOUNCE = (uint8_T)
      (chartInstance->c81_is_SERVICE_CLOCK == c81_IN_DEBOUNCE);
    chartInstance->c81_g_tp_INACTIVE = (uint8_T)
      (chartInstance->c81_is_SERVICE_CLOCK == c81_c_IN_INACTIVE);
    chartInstance->c81_tp_JUMP_STATE = (uint8_T)
      (chartInstance->c81_is_SERVICE_CLOCK == c81_IN_JUMP_STATE);
    if (chartInstance->c81_is_ACTIVE == c81_IN_SERVICE_CLOCK_RESET) {
      chartInstance->c81_tp_SERVICE_CLOCK_RESET = 1U;
      chartInstance->c81_was_ACTIVE = c81_IN_SERVICE_CLOCK_RESET;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 67) == 0.0) {
        chartInstance->c81_temporalCounter_i2 = 0U;
      }
    } else {
      chartInstance->c81_tp_SERVICE_CLOCK_RESET = 0U;
    }

    if (chartInstance->c81_is_PRIMARY_STATE == c81_IN_EMEA_CONTROLS) {
      chartInstance->c81_tp_EMEA_CONTROLS = 1U;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 68) == 0.0) {
        chartInstance->c81_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c81_tp_EMEA_CONTROLS = 0U;
    }

    if (chartInstance->c81_is_PRIMARY_STATE == c81_IN_ERROR_CODES) {
      chartInstance->c81_b_tp_ERROR_CODES = 1U;
      if (sf_mex_sub(chartInstance->c81_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 69) == 0.0) {
        chartInstance->c81_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c81_b_tp_ERROR_CODES = 0U;
    }

    chartInstance->c81_h_tp_INACTIVE = (uint8_T)
      (chartInstance->c81_is_PRIMARY_STATE == c81_b_IN_INACTIVE);
    chartInstance->c81_tp_SECOND_AUX = (uint8_T)
      (chartInstance->c81_is_PRIMARY_STATE == c81_IN_SECOND_AUX);
    chartInstance->c81_tp_LIGHT_BUTTON_STATE = (uint8_T)
      (chartInstance->c81_is_active_LIGHT_BUTTON_STATE == 1U);
    chartInstance->c81_e_tp_ACTIVE = (uint8_T)
      (chartInstance->c81_is_LIGHT_BUTTON_STATE == c81_IN_ACTIVE);
    chartInstance->c81_d_tp_EDGE = (uint8_T)
      (chartInstance->c81_is_LIGHT_BUTTON_STATE == c81_IN_EDGE);
    chartInstance->c81_i_tp_INACTIVE = (uint8_T)
      (chartInstance->c81_is_LIGHT_BUTTON_STATE == c81_IN_INACTIVE);
    chartInstance->c81_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c81_setSimStateSideEffectsInfo);
}

static void sf_gateway_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  int32_T c81_i0;
  c81_set_sim_state_side_effects_c81_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 78U, chartInstance->c81_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_mode_RightControl, 27U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_mode_LeftControl, 26U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_mode_ControlChange, 25U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_fallingedge_SecondAux, 24U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_cmd_SecondAux, 23U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_MachineLock, 22U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_KeylessPanel, 21U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_KSSDisplayState, 20U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_TC, 19U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_CANThrottleCalDiag,
                        18U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_DetentEnable, 17U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_Detent, 16U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_Key, 15U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_Engine, 14U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_ServiceClock, 13U);
  for (c81_i0 = 0; c81_i0 < 8; c81_i0++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c81_msg_PanelButtonState)
                          [c81_i0], 12U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_count_GlowPlug, 11U);
  chartInstance->c81_sfEvent = CALL_EVENT;
  if (chartInstance->c81_temporalCounter_i1 < 65535U) {
    chartInstance->c81_temporalCounter_i1 = c81__u16_s32_(chartInstance,
      chartInstance->c81_temporalCounter_i1 + 1, 0U, 0U, 0U);
  }

  if (chartInstance->c81_temporalCounter_i2 < 127U) {
    chartInstance->c81_temporalCounter_i2 = c81__u8_s32_(chartInstance,
      chartInstance->c81_temporalCounter_i2 + 1, 0U, 0U, 0U);
  }

  if (chartInstance->c81_temporalCounter_i3 < 65535U) {
    chartInstance->c81_temporalCounter_i3 = c81__u16_s32_(chartInstance,
      chartInstance->c81_temporalCounter_i3 + 1, 0U, 0U, 0U);
  }

  if (chartInstance->c81_temporalCounter_i4 < 65535U) {
    chartInstance->c81_temporalCounter_i4 = c81__u16_s32_(chartInstance,
      chartInstance->c81_temporalCounter_i4 + 1, 0U, 0U, 0U);
  }

  c81_chartstep_c81_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MX_Gtwy_ControlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c81_MX_Gtwy_Control(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  c81_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void c81_chartstep_c81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_c_out;
  boolean_T c81_d_out;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 78U, chartInstance->c81_sfEvent);
  if (chartInstance->c81_is_active_c81_MX_Gtwy_Control == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 78U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_active_c81_MX_Gtwy_Control = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 78U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_active_BUTTON_STATE = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_BUTTON_STATE = 1U;
    chartInstance->c81_is_active_INFO_BUTTON = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_INFO_BUTTON = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_INFO_BUTTON = c81_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_INACTIVE = 1U;
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    chartInstance->c81_is_active_MOVE_RIGHT = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_MOVE_RIGHT = 1U;
    chartInstance->c81_is_active_PANEL_BUTTON = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_PANEL_BUTTON = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 40U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_PANEL_BUTTON = c81_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c81_sfEvent);
    chartInstance->c81_b_tp_INACTIVE = 1U;
    *chartInstance->c81_state_RightButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_RightButton, 32U);
    chartInstance->c81_is_active_MOVE_LEFT = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_MOVE_LEFT = 1U;
    chartInstance->c81_b_is_active_PANEL_BUTTON = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c81_sfEvent);
    chartInstance->c81_b_tp_PANEL_BUTTON = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 46U, chartInstance->c81_sfEvent);
    chartInstance->c81_b_is_PANEL_BUTTON = c81_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c81_sfEvent);
    chartInstance->c81_c_tp_INACTIVE = 1U;
    *chartInstance->c81_state_LeftButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_LeftButton, 31U);
    chartInstance->c81_is_active_SECONDARY_STATE = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 57U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_SECONDARY_STATE = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 34U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_SECONDARY_STATE = c81_IN_DELUXE_GOOD;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 59U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_DELUXE_GOOD = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_DELUXE_GOOD = c81_IN_NON_SHUTDOWN;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_NON_SHUTDOWN = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_NO_STATE = 1U;
    *chartInstance->c81_state_InfoSecondary = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary, 30U);
    chartInstance->c81_is_active_PRIMARY_STATE = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_PRIMARY_STATE = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 83U, chartInstance->c81_sfEvent);
    chartInstance->c81_prev_InfoSecondary = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_InfoSecondary, 5U);
    chartInstance->c81_prev_SecondAux = (chartInstance->c81_INACTIVE != 0);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_SecondAux, 6U);
    chartInstance->c81_is_PRIMARY_STATE = c81_IN_ACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
    chartInstance->c81_temporalCounter_i1 = 0U;
    chartInstance->c81_d_tp_ACTIVE = 1U;
    c81_enter_internal_ACTIVE(chartInstance);
    chartInstance->c81_is_active_LIGHT_BUTTON_STATE = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_LIGHT_BUTTON_STATE = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_LIGHT_BUTTON_STATE = c81_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c81_sfEvent);
    chartInstance->c81_i_tp_INACTIVE = 1U;
    chartInstance->c81_state_LightButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_LightButton, 10U);
  } else {
    c81_BUTTON_STATE(chartInstance);
    c81_SECONDARY_STATE(chartInstance);
    c81_PRIMARY_STATE(chartInstance);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 18U,
                 chartInstance->c81_sfEvent);
    switch (chartInstance->c81_is_LIGHT_BUTTON_STATE) {
     case c81_IN_ACTIVE:
      CV_STATE_EVAL(18, 0, c81_IN_ACTIVE);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 29U,
                   chartInstance->c81_sfEvent);
      c81_out = (CV_TRANSITION_EVAL(29U, (int32_T)(_SFD_CCP_CALL(5U, 29U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 29U, 0, (real_T)
        chartInstance->c81_debounceCount, 100.0, 0, 5U,
        chartInstance->c81_debounceCount >= 100) != 0U,
        chartInstance->c81_sfEvent) != 0U)) != 0);
      if (c81_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
        chartInstance->c81_e_tp_ACTIVE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_LIGHT_BUTTON_STATE = c81_IN_INACTIVE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c81_sfEvent);
        chartInstance->c81_i_tp_INACTIVE = 1U;
        chartInstance->c81_state_LightButton = chartInstance->c81_INACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_LightButton, 10U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 19U,
                     chartInstance->c81_sfEvent);
        chartInstance->c81_debounceCount = c81__u16_s32_(chartInstance,
          c81__s32_add__(chartInstance, (int32_T)
                         chartInstance->c81_debounceCount, 1, 30U, 63U, 15U),
          30U, 63U, 15U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 19U, chartInstance->c81_sfEvent);
      break;

     case c81_IN_EDGE:
      CV_STATE_EVAL(18, 0, c81_IN_EDGE);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 30U,
                   chartInstance->c81_sfEvent);
      c81_b_out = (CV_TRANSITION_EVAL(30U, (int32_T)(_SFD_CCP_CALL(5U, 30U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 30U, 0, (real_T)
        chartInstance->c81_debounceCount, 60.0, 0, 5U,
        chartInstance->c81_debounceCount >= 60) != 0U,
        chartInstance->c81_sfEvent) != 0U)) != 0);
      if (c81_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 30U, chartInstance->c81_sfEvent);
        chartInstance->c81_d_tp_EDGE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_LIGHT_BUTTON_STATE = c81_IN_ACTIVE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c81_sfEvent);
        chartInstance->c81_e_tp_ACTIVE = 1U;
        chartInstance->c81_state_LightButton = chartInstance->c81_ACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_LightButton, 10U);
        chartInstance->c81_debounceCount = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 31U,
                     chartInstance->c81_sfEvent);
        c81_d_out = (CV_TRANSITION_EVAL(31U, (int32_T)(_SFD_CCP_CALL(5U, 31U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 31U, 0, (real_T)
          ((*chartInstance->c81_msg_PanelButtonState)[0] &
           chartInstance->c81_LIGHT_BUTTON_MASK), (real_T)
          chartInstance->c81_INACTIVE, 0, 0U,
          ((*chartInstance->c81_msg_PanelButtonState)[0] &
           chartInstance->c81_LIGHT_BUTTON_MASK) == chartInstance->c81_INACTIVE)
          != 0U, chartInstance->c81_sfEvent) != 0U)) != 0);
        if (c81_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 31U, chartInstance->c81_sfEvent);
          chartInstance->c81_d_tp_EDGE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_LIGHT_BUTTON_STATE = c81_IN_INACTIVE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c81_sfEvent);
          chartInstance->c81_i_tp_INACTIVE = 1U;
          chartInstance->c81_state_LightButton = chartInstance->c81_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_LightButton,
                                10U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 20U,
                       chartInstance->c81_sfEvent);
          chartInstance->c81_debounceCount = c81__u16_s32_(chartInstance,
            c81__s32_add__(chartInstance, (int32_T)
                           chartInstance->c81_debounceCount, 1, 29U, 30U, 15U),
            29U, 30U, 15U);
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 20U, chartInstance->c81_sfEvent);
      break;

     case c81_IN_INACTIVE:
      CV_STATE_EVAL(18, 0, c81_IN_INACTIVE);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 28U,
                   chartInstance->c81_sfEvent);
      c81_c_out = (CV_TRANSITION_EVAL(28U, (int32_T)(_SFD_CCP_CALL(5U, 28U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 28U, 0, (real_T)
        ((*chartInstance->c81_msg_PanelButtonState)[0] &
         chartInstance->c81_LIGHT_BUTTON_MASK), (real_T)
        chartInstance->c81_LIGHT_BUTTON_PRESS, 0, 0U,
        ((*chartInstance->c81_msg_PanelButtonState)[0] &
         chartInstance->c81_LIGHT_BUTTON_MASK) ==
        chartInstance->c81_LIGHT_BUTTON_PRESS) != 0U, chartInstance->c81_sfEvent)
        != 0U)) != 0);
      if (c81_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 28U, chartInstance->c81_sfEvent);
        chartInstance->c81_i_tp_INACTIVE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_LIGHT_BUTTON_STATE = c81_IN_EDGE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c81_sfEvent);
        chartInstance->c81_d_tp_EDGE = 1U;
        chartInstance->c81_debounceCount = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 21U,
                     chartInstance->c81_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c81_sfEvent);
      break;

     default:
      CV_STATE_EVAL(18, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c81_is_LIGHT_BUTTON_STATE = c81_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c81_sfEvent);
      break;
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 18U, chartInstance->c81_sfEvent);
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 78U, chartInstance->c81_sfEvent);
}

static void initSimStructsc81_MX_Gtwy_Control
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c81_BUTTON_STATE(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_temp;
  boolean_T c81_c_out;
  boolean_T c81_d_out;
  boolean_T c81_e_out;
  boolean_T c81_f_out;
  boolean_T c81_g_out;
  boolean_T c81_b_temp;
  boolean_T c81_h_out;
  boolean_T c81_i_out;
  boolean_T c81_j_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c81_sfEvent);
  c81_INFO_BUTTON(chartInstance);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U, chartInstance->c81_sfEvent);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U, chartInstance->c81_sfEvent);
  switch (chartInstance->c81_is_PANEL_BUTTON) {
   case c81_IN_ACTIVE:
    CV_STATE_EVAL(13, 0, c81_IN_ACTIVE);
    *chartInstance->c81_state_RightButton = chartInstance->c81_ACTIVE;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 42U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(42U, (int32_T)(_SFD_CCP_CALL(5U, 42U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 42U, 0, (real_T)
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_RIGHT_BUTTON_MASK), (real_T)
      chartInstance->c81_INACTIVE, 0, 0U,
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_RIGHT_BUTTON_MASK) == chartInstance->c81_INACTIVE) !=
      0U, chartInstance->c81_sfEvent) != 0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 42U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_tp_ACTIVE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_PANEL_BUTTON = c81_IN_INACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_tp_INACTIVE = 1U;
      *chartInstance->c81_state_RightButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_RightButton, 32U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 14U,
                   chartInstance->c81_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_EDGE:
    CV_STATE_EVAL(13, 0, c81_IN_EDGE);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 44U,
                 chartInstance->c81_sfEvent);
    c81_out = (CV_TRANSITION_EVAL(44U, (int32_T)(_SFD_CCP_CALL(5U, 44U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 44U, 0, (real_T)
      chartInstance->c81_debounceRight, 100.0, 0, 4U,
      chartInstance->c81_debounceRight > 100) != 0U, chartInstance->c81_sfEvent)
      != 0U)) != 0);
    if (c81_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 44U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_tp_EDGE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_PANEL_BUTTON = c81_IN_INACTIVE_WAIT;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_tp_INACTIVE_WAIT = 1U;
      *chartInstance->c81_state_RightButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_RightButton, 32U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 45U,
                   chartInstance->c81_sfEvent);
      c81_d_out = (CV_TRANSITION_EVAL(45U, (int32_T)(_SFD_CCP_CALL(5U, 45U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 45U, 0, (real_T)
        ((*chartInstance->c81_msg_PanelButtonState)[0] &
         chartInstance->c81_RIGHT_BUTTON_MASK), (real_T)
        chartInstance->c81_INACTIVE, 0, 0U,
        ((*chartInstance->c81_msg_PanelButtonState)[0] &
         chartInstance->c81_RIGHT_BUTTON_MASK) == chartInstance->c81_INACTIVE)
        != 0U, chartInstance->c81_sfEvent) != 0U)) != 0);
      if (c81_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 45U, chartInstance->c81_sfEvent);
        chartInstance->c81_b_tp_EDGE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_PANEL_BUTTON = c81_IN_ACTIVE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c81_sfEvent);
        chartInstance->c81_b_tp_ACTIVE = 1U;
        *chartInstance->c81_state_RightButton = chartInstance->c81_ACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_RightButton, 32U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 15U,
                     chartInstance->c81_sfEvent);
        chartInstance->c81_debounceRight = c81__u16_s32_(chartInstance,
          c81__s32_add__(chartInstance, (int32_T)
                         chartInstance->c81_debounceRight, 1, 322U, 30U, 15U),
          322U, 30U, 15U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceRight, 4U);
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_INACTIVE:
    CV_STATE_EVAL(13, 0, c81_IN_INACTIVE);
    *chartInstance->c81_state_RightButton = chartInstance->c81_INACTIVE;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 41U,
                 chartInstance->c81_sfEvent);
    c81_temp = (_SFD_CCP_CALL(5U, 41U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 41U,
      0, (real_T)((*chartInstance->c81_msg_PanelButtonState)[0] &
                  chartInstance->c81_RIGHT_BUTTON_MASK), (real_T)
      chartInstance->c81_RIGHT_BUTTON_PRESS, 0, 0U,
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_RIGHT_BUTTON_MASK) ==
      chartInstance->c81_RIGHT_BUTTON_PRESS) != 0U, chartInstance->c81_sfEvent)
                != 0U);
    if (c81_temp) {
      c81_temp = (_SFD_CCP_CALL(5U, 41U, 1,
        (*chartInstance->c81_enable_RightLeft != 0) != 0U,
        chartInstance->c81_sfEvent) != 0U);
    }

    c81_e_out = (CV_TRANSITION_EVAL(41U, (int32_T)c81_temp) != 0);
    if (c81_e_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 41U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_tp_INACTIVE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_PANEL_BUTTON = c81_IN_EDGE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_tp_EDGE = 1U;
      chartInstance->c81_debounceRight = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceRight, 4U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 16U,
                   chartInstance->c81_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_INACTIVE_WAIT:
    CV_STATE_EVAL(13, 0, c81_IN_INACTIVE_WAIT);
    *chartInstance->c81_state_RightButton = chartInstance->c81_INACTIVE;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 43U,
                 chartInstance->c81_sfEvent);
    c81_c_out = (CV_TRANSITION_EVAL(43U, (int32_T)(_SFD_CCP_CALL(5U, 43U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 43U, 0, (real_T)
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_RIGHT_BUTTON_MASK), (real_T)
      chartInstance->c81_INACTIVE, 0, 0U,
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_RIGHT_BUTTON_MASK) == chartInstance->c81_INACTIVE) !=
      0U, chartInstance->c81_sfEvent) != 0U)) != 0);
    if (c81_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 43U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_tp_INACTIVE_WAIT = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_PANEL_BUTTON = c81_IN_INACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_tp_INACTIVE = 1U;
      *chartInstance->c81_state_RightButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_RightButton, 32U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 17U,
                   chartInstance->c81_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(13, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c81_is_PANEL_BUTTON = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c81_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c81_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c81_sfEvent);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U, chartInstance->c81_sfEvent);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U, chartInstance->c81_sfEvent);
  switch (chartInstance->c81_b_is_PANEL_BUTTON) {
   case c81_IN_ACTIVE:
    CV_STATE_EVAL(7, 0, c81_IN_ACTIVE);
    *chartInstance->c81_state_LeftButton = chartInstance->c81_ACTIVE;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 48U,
                 chartInstance->c81_sfEvent);
    c81_g_out = (CV_TRANSITION_EVAL(48U, (int32_T)(_SFD_CCP_CALL(5U, 48U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 48U, 0, (real_T)
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_LEFT_BUTTON_MASK), (real_T)chartInstance->c81_INACTIVE,
      0, 0U, ((*chartInstance->c81_msg_PanelButtonState)[0] &
              chartInstance->c81_LEFT_BUTTON_MASK) ==
      chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U)) !=
                 0);
    if (c81_g_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 48U, chartInstance->c81_sfEvent);
      chartInstance->c81_c_tp_ACTIVE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_is_PANEL_BUTTON = c81_IN_INACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c81_sfEvent);
      chartInstance->c81_c_tp_INACTIVE = 1U;
      *chartInstance->c81_state_LeftButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_LeftButton, 31U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                   chartInstance->c81_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_EDGE:
    CV_STATE_EVAL(7, 0, c81_IN_EDGE);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 50U,
                 chartInstance->c81_sfEvent);
    c81_f_out = (CV_TRANSITION_EVAL(50U, (int32_T)(_SFD_CCP_CALL(5U, 50U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 50U, 0, (real_T)
      chartInstance->c81_debounceLeft, 100.0, 0, 4U,
      chartInstance->c81_debounceLeft > 100) != 0U, chartInstance->c81_sfEvent)
      != 0U)) != 0);
    if (c81_f_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 50U, chartInstance->c81_sfEvent);
      chartInstance->c81_c_tp_EDGE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_is_PANEL_BUTTON = c81_IN_INACTIVE_WAIT;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c81_sfEvent);
      chartInstance->c81_c_tp_INACTIVE_WAIT = 1U;
      *chartInstance->c81_state_LeftButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_LeftButton, 31U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 51U,
                   chartInstance->c81_sfEvent);
      c81_i_out = (CV_TRANSITION_EVAL(51U, (int32_T)(_SFD_CCP_CALL(5U, 51U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 51U, 0, (real_T)
        ((*chartInstance->c81_msg_PanelButtonState)[0] &
         chartInstance->c81_LEFT_BUTTON_MASK), (real_T)
        chartInstance->c81_INACTIVE, 0, 0U,
        ((*chartInstance->c81_msg_PanelButtonState)[0] &
         chartInstance->c81_LEFT_BUTTON_MASK) == chartInstance->c81_INACTIVE) !=
        0U, chartInstance->c81_sfEvent) != 0U)) != 0);
      if (c81_i_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 51U, chartInstance->c81_sfEvent);
        chartInstance->c81_c_tp_EDGE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c81_sfEvent);
        chartInstance->c81_b_is_PANEL_BUTTON = c81_IN_ACTIVE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c81_sfEvent);
        chartInstance->c81_c_tp_ACTIVE = 1U;
        *chartInstance->c81_state_LeftButton = chartInstance->c81_ACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_LeftButton, 31U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                     chartInstance->c81_sfEvent);
        chartInstance->c81_debounceLeft = c81__u16_s32_(chartInstance,
          c81__s32_add__(chartInstance, (int32_T)chartInstance->c81_debounceLeft,
                         1, 333U, 29U, 14U), 333U, 29U, 14U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceLeft, 3U);
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_INACTIVE:
    CV_STATE_EVAL(7, 0, c81_IN_INACTIVE);
    *chartInstance->c81_state_LeftButton = chartInstance->c81_INACTIVE;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 47U,
                 chartInstance->c81_sfEvent);
    c81_b_temp = (_SFD_CCP_CALL(5U, 47U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      47U, 0, (real_T)((*chartInstance->c81_msg_PanelButtonState)[0] &
                       chartInstance->c81_LEFT_BUTTON_MASK), (real_T)
      chartInstance->c81_LEFT_BUTTON_PRESS, 0, 0U,
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_LEFT_BUTTON_MASK) ==
      chartInstance->c81_LEFT_BUTTON_PRESS) != 0U, chartInstance->c81_sfEvent)
                  != 0U);
    if (c81_b_temp) {
      c81_b_temp = (_SFD_CCP_CALL(5U, 47U, 1,
        (*chartInstance->c81_enable_RightLeft != 0) != 0U,
        chartInstance->c81_sfEvent) != 0U);
    }

    c81_j_out = (CV_TRANSITION_EVAL(47U, (int32_T)c81_b_temp) != 0);
    if (c81_j_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 47U, chartInstance->c81_sfEvent);
      chartInstance->c81_c_tp_INACTIVE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_is_PANEL_BUTTON = c81_IN_EDGE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c81_sfEvent);
      chartInstance->c81_c_tp_EDGE = 1U;
      chartInstance->c81_debounceLeft = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceLeft, 3U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                   chartInstance->c81_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_INACTIVE_WAIT:
    CV_STATE_EVAL(7, 0, c81_IN_INACTIVE_WAIT);
    *chartInstance->c81_state_LeftButton = chartInstance->c81_INACTIVE;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 49U,
                 chartInstance->c81_sfEvent);
    c81_h_out = (CV_TRANSITION_EVAL(49U, (int32_T)(_SFD_CCP_CALL(5U, 49U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 49U, 0, (real_T)
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_LEFT_BUTTON_MASK), (real_T)chartInstance->c81_INACTIVE,
      0, 0U, ((*chartInstance->c81_msg_PanelButtonState)[0] &
              chartInstance->c81_LEFT_BUTTON_MASK) ==
      chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U)) !=
                 0);
    if (c81_h_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 49U, chartInstance->c81_sfEvent);
      chartInstance->c81_c_tp_INACTIVE_WAIT = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_is_PANEL_BUTTON = c81_IN_INACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c81_sfEvent);
      chartInstance->c81_c_tp_INACTIVE = 1U;
      *chartInstance->c81_state_LeftButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_LeftButton, 31U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                   chartInstance->c81_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(7, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c81_b_is_PANEL_BUTTON = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c81_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c81_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c81_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c81_sfEvent);
}

static void c81_INFO_BUTTON(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_out;
  boolean_T c81_temp;
  boolean_T c81_b_out;
  boolean_T c81_c_out;
  boolean_T c81_d_out;
  boolean_T c81_b_temp;
  boolean_T c81_e_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c81_sfEvent);
  switch (chartInstance->c81_is_INFO_BUTTON) {
   case c81_IN_ACTIVE:
    CV_STATE_EVAL(1, 0, c81_IN_ACTIVE);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                 chartInstance->c81_sfEvent);
    c81_out = (CV_TRANSITION_EVAL(5U, (int32_T)(_SFD_CCP_CALL(5U, 5U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 5U, 0, (real_T)
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_INFO_BUTTON_MASK), (real_T)chartInstance->c81_INACTIVE,
      0, 0U, ((*chartInstance->c81_msg_PanelButtonState)[0] &
              chartInstance->c81_INFO_BUTTON_MASK) ==
      chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U)) !=
               0);
    if (c81_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_ACTIVE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_INFO_BUTTON = c81_IN_INACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_INACTIVE = 1U;
      *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                   chartInstance->c81_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_EDGE:
    CV_STATE_EVAL(1, 0, c81_IN_EDGE);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U,
                 chartInstance->c81_sfEvent);
    c81_temp = (_SFD_CCP_CALL(5U, 13U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 13U,
      0, (real_T)chartInstance->c81_debounceButton, 100.0, 0, 4U,
      chartInstance->c81_debounceButton > 100) != 0U, chartInstance->c81_sfEvent)
                != 0U);
    if (!c81_temp) {
      c81_temp = (_SFD_CCP_CALL(5U, 13U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        13U, 1, (real_T)chartInstance->c81_state_Jump, (real_T)
        chartInstance->c81_ACTIVE, 0, 0U, chartInstance->c81_state_Jump ==
        chartInstance->c81_ACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
    }

    c81_d_out = (CV_TRANSITION_EVAL(13U, (int32_T)c81_temp) != 0);
    if (c81_d_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_EDGE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_INFO_BUTTON = c81_IN_INACTIVE_WAIT;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_INACTIVE_WAIT = 1U;
      *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U,
                   chartInstance->c81_sfEvent);
      c81_b_temp = (_SFD_CCP_CALL(5U, 4U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        4U, 0, (real_T)((*chartInstance->c81_msg_PanelButtonState)[0] &
                        chartInstance->c81_INFO_BUTTON_MASK), (real_T)
        chartInstance->c81_INACTIVE, 0, 0U,
        ((*chartInstance->c81_msg_PanelButtonState)[0] &
         chartInstance->c81_INFO_BUTTON_MASK) == chartInstance->c81_INACTIVE) !=
        0U, chartInstance->c81_sfEvent) != 0U);
      if (c81_b_temp) {
        c81_b_temp = (_SFD_CCP_CALL(5U, 4U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          4U, 1, (real_T)chartInstance->c81_state_Jump, (real_T)
          chartInstance->c81_ACTIVE, 0, 1U, chartInstance->c81_state_Jump !=
          chartInstance->c81_ACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
      }

      c81_e_out = (CV_TRANSITION_EVAL(4U, (int32_T)c81_b_temp) != 0);
      if (c81_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c81_sfEvent);
        chartInstance->c81_tp_EDGE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_INFO_BUTTON = c81_IN_ACTIVE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c81_sfEvent);
        chartInstance->c81_tp_ACTIVE = 1U;
        *chartInstance->c81_state_InfoButton = chartInstance->c81_ACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                     chartInstance->c81_sfEvent);
        chartInstance->c81_debounceButton = c81__u16_s32_(chartInstance,
          c81__s32_add__(chartInstance, (int32_T)
                         chartInstance->c81_debounceButton, 1, 9U, 31U, 16U), 9U,
          31U, 16U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceButton, 0U);
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_INACTIVE:
    CV_STATE_EVAL(1, 0, c81_IN_INACTIVE);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(3U, (int32_T)(_SFD_CCP_CALL(5U, 3U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 3U, 0, (real_T)
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_INFO_BUTTON_MASK), (real_T)
      chartInstance->c81_INFO_BUTTON_PRESS, 0, 0U,
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_INFO_BUTTON_MASK) ==
      chartInstance->c81_INFO_BUTTON_PRESS) != 0U, chartInstance->c81_sfEvent)
      != 0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_INACTIVE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_INFO_BUTTON = c81_IN_EDGE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_EDGE = 1U;
      chartInstance->c81_debounceButton = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceButton, 0U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                   chartInstance->c81_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_INACTIVE_WAIT:
    CV_STATE_EVAL(1, 0, c81_IN_INACTIVE_WAIT);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 22U,
                 chartInstance->c81_sfEvent);
    c81_c_out = (CV_TRANSITION_EVAL(22U, (int32_T)(_SFD_CCP_CALL(5U, 22U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 22U, 0, (real_T)
      ((*chartInstance->c81_msg_PanelButtonState)[0] &
       chartInstance->c81_INFO_BUTTON_MASK), (real_T)chartInstance->c81_INACTIVE,
      0, 0U, ((*chartInstance->c81_msg_PanelButtonState)[0] &
              chartInstance->c81_INFO_BUTTON_MASK) ==
      chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U)) !=
                 0);
    if (c81_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 22U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_INACTIVE_WAIT = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_INFO_BUTTON = c81_IN_INACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_INACTIVE = 1U;
      *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                   chartInstance->c81_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(1, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c81_is_INFO_BUTTON = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c81_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c81_sfEvent);
}

static void c81_PRIMARY_STATE(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_temp;
  boolean_T c81_b_temp;
  boolean_T c81_c_temp;
  boolean_T c81_d_temp;
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_c_out;
  boolean_T c81_e_temp;
  boolean_T c81_d_out;
  boolean_T c81_f_temp;
  boolean_T c81_g_temp;
  boolean_T c81_h_temp;
  boolean_T c81_i_temp;
  boolean_T c81_e_out;
  boolean_T c81_f_out;
  boolean_T c81_g_out;
  boolean_T c81_j_temp;
  uint16_T c81_u0;
  boolean_T c81_h_out;
  boolean_T c81_k_temp;
  boolean_T c81_i_out;
  boolean_T c81_l_temp;
  boolean_T c81_m_temp;
  boolean_T c81_n_temp;
  boolean_T c81_j_out;
  boolean_T guard1 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 22U, chartInstance->c81_sfEvent);
  switch (chartInstance->c81_is_PRIMARY_STATE) {
   case c81_IN_ACTIVE:
    CV_STATE_EVAL(22, 0, c81_IN_ACTIVE);
    c81_b_ACTIVE(chartInstance);
    break;

   case c81_IN_EMEA_CONTROLS:
    CV_STATE_EVAL(22, 0, c81_IN_EMEA_CONTROLS);
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_EMEA_CONTROLS;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 109U,
                 chartInstance->c81_sfEvent);
    c81_temp = (_SFD_CCP_CALL(5U, 109U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      109U, 0, (real_T)*chartInstance->c81_mode_LeftControl, (real_T)
      chartInstance->c81_MODE_LEFT_NONE, 0, 0U,
      *chartInstance->c81_mode_LeftControl == chartInstance->c81_MODE_LEFT_NONE)
      != 0U, chartInstance->c81_sfEvent) != 0U);
    if (c81_temp) {
      c81_temp = (_SFD_CCP_CALL(5U, 109U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        109U, 1, (real_T)*chartInstance->c81_mode_RightControl, (real_T)
        chartInstance->c81_MODE_RIGHT_NONE, 0, 0U,
        *chartInstance->c81_mode_RightControl ==
        chartInstance->c81_MODE_RIGHT_NONE) != 0U, chartInstance->c81_sfEvent)
                  != 0U);
    }

    c81_out = (CV_TRANSITION_EVAL(109U, (int32_T)c81_temp) != 0);
    guard1 = false;
    if (c81_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 109U, chartInstance->c81_sfEvent);
      guard1 = true;
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 108U,
                   chartInstance->c81_sfEvent);
      c81_d_out = (CV_TRANSITION_EVAL(108U, (int32_T)(_SFD_CCP_CALL(5U, 108U, 0,
        *chartInstance->c81_mode_ControlChange != 0U, chartInstance->c81_sfEvent)
        != 0U)) != 0);
      if (c81_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 108U, chartInstance->c81_sfEvent);
        chartInstance->c81_tp_EMEA_CONTROLS = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 53U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_PRIMARY_STATE = c81_IN_EMEA_CONTROLS;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 53U, chartInstance->c81_sfEvent);
        chartInstance->c81_temporalCounter_i1 = 0U;
        chartInstance->c81_tp_EMEA_CONTROLS = 1U;
        *chartInstance->c81_state_InfoPrimary =
          chartInstance->c81_DISPLAY_EMEA_CONTROLS;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
        chartInstance->c81_prev_InfoSecondary =
          *chartInstance->c81_state_InfoSecondary;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_InfoSecondary, 5U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 105U,
                     chartInstance->c81_sfEvent);
        c81_e_out = (CV_TRANSITION_EVAL(105U, (int32_T)(_SFD_CCP_CALL(5U, 105U,
          0, (boolean_T)CV_RELATIONAL_EVAL(5U, 105U, 0, (real_T)
          *chartInstance->c81_state_InfoButton, (real_T)
          chartInstance->c81_ACTIVE, 0, 0U, *chartInstance->c81_state_InfoButton
          == chartInstance->c81_ACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U))
                     != 0);
        if (c81_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 105U, chartInstance->c81_sfEvent);
          guard1 = true;
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 106U,
                       chartInstance->c81_sfEvent);
          c81_u0 = c81__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
            ((uint32_T)chartInstance->c81_CD_EMEA_CONTROLS_DISPLAY_TIME, 16U,
             106U), 966U, 1U, 5U);
          c81_h_out = (CV_TRANSITION_EVAL(106U, (int32_T)(_SFD_CCP_CALL(5U, 106U,
            0, (chartInstance->c81_temporalCounter_i1 >= c81_u0) != 0U,
            chartInstance->c81_sfEvent) != 0U)) != 0);
          if (c81_h_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 106U, chartInstance->c81_sfEvent);
            guard1 = true;
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 107U,
                         chartInstance->c81_sfEvent);
            c81_k_temp = (_SFD_CCP_CALL(5U, 107U, 0, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 107U, 0, (real_T)
                                 *chartInstance->c81_state_InfoSecondary,
                                 (real_T)chartInstance->c81_INACTIVE, 0, 1U,
                                 *chartInstance->c81_state_InfoSecondary !=
                                 chartInstance->c81_INACTIVE) != 0U,
              chartInstance->c81_sfEvent) != 0U);
            if (c81_k_temp) {
              c81_k_temp = (_SFD_CCP_CALL(5U, 107U, 1, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 107U, 1, (real_T)
                                   *chartInstance->c81_state_InfoSecondary,
                                   (real_T)chartInstance->c81_prev_InfoSecondary,
                                   0, 1U,
                                   *chartInstance->c81_state_InfoSecondary !=
                                   chartInstance->c81_prev_InfoSecondary) != 0U,
                chartInstance->c81_sfEvent) != 0U);
            }

            c81_i_out = (CV_TRANSITION_EVAL(107U, (int32_T)c81_k_temp) != 0);
            if (c81_i_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 107U,
                           chartInstance->c81_sfEvent);
              chartInstance->c81_tp_EMEA_CONTROLS = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 53U, chartInstance->c81_sfEvent);
              chartInstance->c81_is_PRIMARY_STATE = c81_b_IN_INACTIVE;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 55U, chartInstance->c81_sfEvent);
              chartInstance->c81_h_tp_INACTIVE = 1U;
              *chartInstance->c81_state_InfoPrimary =
                chartInstance->c81_DISPLAY_PRIMARY_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c81_state_InfoPrimary, 28U);
              chartInstance->c81_prev_InfoSecondary =
                *chartInstance->c81_state_InfoSecondary;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    chartInstance->c81_prev_InfoSecondary, 5U);
            } else {
              _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 110U,
                           chartInstance->c81_sfEvent);
              c81_l_temp = (_SFD_CCP_CALL(5U, 110U, 0, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 110U, 0, (real_T)
                                   chartInstance->c81_CD_AUTO_DISPLAY_FAULT_FUNCTION,
                                   (real_T)chartInstance->c81_NON_FUNCTIONAL, 0,
                                   1U,
                                   chartInstance->c81_CD_AUTO_DISPLAY_FAULT_FUNCTION
                                   != chartInstance->c81_NON_FUNCTIONAL) != 0U,
                chartInstance->c81_sfEvent) != 0U);
              if (c81_l_temp) {
                c81_l_temp = (_SFD_CCP_CALL(5U, 110U, 1,
                  (c81_get_flag_StdActiveWarn(chartInstance, 0) != 0) != 0U,
                  chartInstance->c81_sfEvent) != 0U);
              }

              c81_m_temp = c81_l_temp;
              if (c81_l_temp) {
                c81_m_temp = (_SFD_CCP_CALL(5U, 110U, 2, (boolean_T)
                  CV_RELATIONAL_EVAL(5U, 110U, 1, (real_T)c81_get_ee_DeluxeG5
                                     (chartInstance, 0), (real_T)
                                     chartInstance->c81_ACTIVE, 0, 1U,
                                     c81_get_ee_DeluxeG5(chartInstance, 0) !=
                                     chartInstance->c81_ACTIVE) != 0U,
                  chartInstance->c81_sfEvent) != 0U);
              }

              c81_n_temp = c81_m_temp;
              if (c81_m_temp) {
                c81_n_temp = (_SFD_CCP_CALL(5U, 110U, 3, (boolean_T)
                  CV_RELATIONAL_EVAL(5U, 110U, 2, (real_T)
                                     chartInstance->c81_CD_DELUXE_GEN5_5_FUNCTION,
                                     (real_T)chartInstance->c81_NON_FUNCTIONAL,
                                     0, 0U,
                                     chartInstance->c81_CD_DELUXE_GEN5_5_FUNCTION
                                     == chartInstance->c81_NON_FUNCTIONAL) != 0U,
                  chartInstance->c81_sfEvent) != 0U);
              }

              c81_j_out = (CV_TRANSITION_EVAL(110U, (int32_T)c81_n_temp) != 0);
              if (c81_j_out) {
                _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 110U,
                             chartInstance->c81_sfEvent);
                chartInstance->c81_tp_EMEA_CONTROLS = 0U;
                _SFD_CS_CALL(STATE_INACTIVE_TAG, 53U, chartInstance->c81_sfEvent);
                chartInstance->c81_is_PRIMARY_STATE = c81_IN_ERROR_CODES;
                _SFD_CS_CALL(STATE_ACTIVE_TAG, 54U, chartInstance->c81_sfEvent);
                chartInstance->c81_temporalCounter_i1 = 0U;
                chartInstance->c81_b_tp_ERROR_CODES = 1U;
                *chartInstance->c81_state_InfoPrimary =
                  chartInstance->c81_DISPLAY_ERROR_CODES;
                _SFD_DATA_RANGE_CHECK((real_T)
                                      *chartInstance->c81_state_InfoPrimary, 28U);
                *chartInstance->c81_state_InfoButton =
                  chartInstance->c81_INACTIVE;
                _SFD_DATA_RANGE_CHECK((real_T)
                                      *chartInstance->c81_state_InfoButton, 29U);
                chartInstance->c81_debounceCode = 0U;
                _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCode,
                                      1U);
              } else {
                _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 53U,
                             chartInstance->c81_sfEvent);
              }
            }
          }
        }
      }
    }

    if (guard1) {
      chartInstance->c81_tp_EMEA_CONTROLS = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 53U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_PRIMARY_STATE = c81_IN_ACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
      chartInstance->c81_temporalCounter_i1 = 0U;
      chartInstance->c81_d_tp_ACTIVE = 1U;
      c81_enter_internal_ACTIVE(chartInstance);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 53U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_ERROR_CODES:
    CV_STATE_EVAL(22, 0, c81_IN_ERROR_CODES);
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_ERROR_CODES;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 93U,
                 chartInstance->c81_sfEvent);
    c81_b_temp = (_SFD_CCP_CALL(5U, 93U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      93U, 0, (real_T)chartInstance->c81_debounceCode, (real_T)
      chartInstance->c81_CD_AUTO_DISPLAY_FAULT_DEBOUNCE_ACTIVE, 0, 5U,
      chartInstance->c81_debounceCode >=
      chartInstance->c81_CD_AUTO_DISPLAY_FAULT_DEBOUNCE_ACTIVE) != 0U,
      chartInstance->c81_sfEvent) != 0U);
    if (!c81_b_temp) {
      c81_b_temp = (_SFD_CCP_CALL(5U, 93U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        93U, 1, (real_T)*chartInstance->c81_state_InfoButton, (real_T)
        chartInstance->c81_ACTIVE, 0, 0U, *chartInstance->c81_state_InfoButton ==
        chartInstance->c81_ACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
    }

    c81_b_out = (CV_TRANSITION_EVAL(93U, (int32_T)c81_b_temp) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 93U, chartInstance->c81_sfEvent);
      chartInstance->c81_b_tp_ERROR_CODES = 0U;
      _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 54U,
                   chartInstance->c81_sfEvent);
      c81_set_flag_StdActiveWarn(chartInstance, 0, chartInstance->c81_INACTIVE);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 3);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 54U, chartInstance->c81_sfEvent);
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 54U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_PRIMARY_STATE = c81_IN_ACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
      chartInstance->c81_temporalCounter_i1 = 0U;
      chartInstance->c81_d_tp_ACTIVE = 1U;
      c81_enter_internal_ACTIVE(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 94U,
                   chartInstance->c81_sfEvent);
      c81_f_temp = (_SFD_CCP_CALL(5U, 94U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        94U, 0, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
        chartInstance->c81_INACTIVE, 0, 1U,
        *chartInstance->c81_state_InfoSecondary != chartInstance->c81_INACTIVE)
        != 0U, chartInstance->c81_sfEvent) != 0U);
      if (c81_f_temp) {
        c81_h_temp = (_SFD_CCP_CALL(5U, 94U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          94U, 1, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
          chartInstance->c81_prev_InfoSecondary, 0, 1U,
          *chartInstance->c81_state_InfoSecondary !=
          chartInstance->c81_prev_InfoSecondary) != 0U,
          chartInstance->c81_sfEvent) != 0U);
        if (!c81_h_temp) {
          c81_h_temp = (_SFD_CCP_CALL(5U, 94U, 2,
            (chartInstance->c81_temporalCounter_i1 >= 40) != 0U,
            chartInstance->c81_sfEvent) != 0U);
        }

        c81_f_temp = c81_h_temp;
      }

      c81_f_out = (CV_TRANSITION_EVAL(94U, (int32_T)c81_f_temp) != 0);
      if (c81_f_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 94U, chartInstance->c81_sfEvent);
        chartInstance->c81_b_tp_ERROR_CODES = 0U;
        _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 54U,
                     chartInstance->c81_sfEvent);
        c81_set_flag_StdActiveWarn(chartInstance, 0, chartInstance->c81_INACTIVE);
        ssUpdateDataStoreLog_wrapper(chartInstance->S, 3);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 54U, chartInstance->c81_sfEvent);
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 54U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_PRIMARY_STATE = c81_b_IN_INACTIVE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 55U, chartInstance->c81_sfEvent);
        chartInstance->c81_h_tp_INACTIVE = 1U;
        *chartInstance->c81_state_InfoPrimary =
          chartInstance->c81_DISPLAY_PRIMARY_INACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
        chartInstance->c81_prev_InfoSecondary =
          *chartInstance->c81_state_InfoSecondary;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_InfoSecondary, 5U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 54U,
                     chartInstance->c81_sfEvent);
        chartInstance->c81_debounceCode = c81__u16_s32_(chartInstance,
          c81__s32_add__(chartInstance, (int32_T)chartInstance->c81_debounceCode,
                         1, 922U, 108U, 14U), 922U, 108U, 14U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCode, 1U);
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 54U, chartInstance->c81_sfEvent);
    break;

   case c81_b_IN_INACTIVE:
    CV_STATE_EVAL(22, 0, c81_b_IN_INACTIVE);
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_PRIMARY_INACTIVE;
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 82U,
                 chartInstance->c81_sfEvent);
    c81_c_temp = (_SFD_CCP_CALL(5U, 82U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      82U, 0, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
      chartInstance->c81_INACTIVE, 0, 0U,
      *chartInstance->c81_state_InfoSecondary == chartInstance->c81_INACTIVE) !=
      0U, chartInstance->c81_sfEvent) != 0U);
    if (!c81_c_temp) {
      c81_d_temp = (_SFD_CCP_CALL(5U, 82U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
        82U, 1, (real_T)*chartInstance->c81_state_InfoButton, (real_T)
        chartInstance->c81_ACTIVE, 0, 0U, *chartInstance->c81_state_InfoButton ==
        chartInstance->c81_ACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
      if (c81_d_temp) {
        c81_d_temp = (_SFD_CCP_CALL(5U, 82U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
          82U, 2, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
          chartInstance->c81_DISPLAY_DELUXE_ERROR, 0, 1U,
          *chartInstance->c81_state_InfoSecondary !=
          chartInstance->c81_DISPLAY_DELUXE_ERROR) != 0U,
          chartInstance->c81_sfEvent) != 0U);
      }

      c81_e_temp = c81_d_temp;
      if (c81_d_temp) {
        c81_e_temp = (_SFD_CCP_CALL(5U, 82U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
          82U, 3, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
          chartInstance->c81_DISPLAY_SHUTDOWN, 0, 1U,
          *chartInstance->c81_state_InfoSecondary !=
          chartInstance->c81_DISPLAY_SHUTDOWN) != 0U, chartInstance->c81_sfEvent)
                      != 0U);
      }

      c81_i_temp = c81_e_temp;
      if (c81_e_temp) {
        c81_i_temp = (_SFD_CCP_CALL(5U, 82U, 4, (boolean_T)CV_RELATIONAL_EVAL(5U,
          82U, 4, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
          chartInstance->c81_DISPLAY_SERVICE_CLOCK_RESET, 0, 1U,
          *chartInstance->c81_state_InfoSecondary !=
          chartInstance->c81_DISPLAY_SERVICE_CLOCK_RESET) != 0U,
          chartInstance->c81_sfEvent) != 0U);
      }

      c81_j_temp = c81_i_temp;
      if (c81_i_temp) {
        c81_j_temp = (_SFD_CCP_CALL(5U, 82U, 5, (boolean_T)CV_RELATIONAL_EVAL(5U,
          82U, 5, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
          chartInstance->c81_DISPLAY_SERVICE_CLOCK_ALARM, 0, 1U,
          *chartInstance->c81_state_InfoSecondary !=
          chartInstance->c81_DISPLAY_SERVICE_CLOCK_ALARM) != 0U,
          chartInstance->c81_sfEvent) != 0U);
      }

      c81_c_temp = c81_j_temp;
    }

    c81_c_out = (CV_TRANSITION_EVAL(82U, (int32_T)c81_c_temp) != 0);
    if (c81_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 82U, chartInstance->c81_sfEvent);
      chartInstance->c81_h_tp_INACTIVE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 55U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_PRIMARY_STATE = c81_IN_ACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
      chartInstance->c81_temporalCounter_i1 = 0U;
      chartInstance->c81_d_tp_ACTIVE = 1U;
      c81_enter_internal_ACTIVE(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 102U,
                   chartInstance->c81_sfEvent);
      c81_g_temp = (_SFD_CCP_CALL(5U, 102U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        102U, 0, (real_T)*chartInstance->c81_cmd_SecondAux, (real_T)
        chartInstance->c81_ACTIVE, 0, 0U, (int32_T)
        *chartInstance->c81_cmd_SecondAux == chartInstance->c81_ACTIVE) != 0U,
        chartInstance->c81_sfEvent) != 0U);
      if (c81_g_temp) {
        c81_g_temp = (_SFD_CCP_CALL(5U, 102U, 1, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 102U, 1, (real_T)chartInstance->c81_prev_SecondAux, (real_T)
           chartInstance->c81_ACTIVE, 0, 0U, (int32_T)
           chartInstance->c81_prev_SecondAux == chartInstance->c81_ACTIVE) != 0U,
          chartInstance->c81_sfEvent) != 0U);
      }

      c81_g_out = (CV_TRANSITION_EVAL(102U, (int32_T)c81_g_temp) != 0);
      if (c81_g_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 102U, chartInstance->c81_sfEvent);
        chartInstance->c81_h_tp_INACTIVE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 55U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_PRIMARY_STATE = c81_IN_SECOND_AUX;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 56U, chartInstance->c81_sfEvent);
        chartInstance->c81_tp_SECOND_AUX = 1U;
        *chartInstance->c81_state_InfoPrimary =
          chartInstance->c81_DISPLAY_SECOND_AUX;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
        chartInstance->c81_prev_InfoSecondary =
          *chartInstance->c81_state_InfoSecondary;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_InfoSecondary, 5U);
        chartInstance->c81_prev_SecondAux = (chartInstance->c81_ACTIVE != 0);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_SecondAux, 6U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 55U,
                     chartInstance->c81_sfEvent);
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 55U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_SECOND_AUX:
    CV_STATE_EVAL(22, 0, c81_IN_SECOND_AUX);
    c81_SECOND_AUX(chartInstance);
    break;

   default:
    CV_STATE_EVAL(22, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c81_is_PRIMARY_STATE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 22U, chartInstance->c81_sfEvent);
}

static void c81_enter_internal_ACTIVE(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c81_was_ACTIVE) {
   case c81_IN_BATTERY_VOLTAGE:
    CV_STATE_EVAL(23, 2, c81_IN_BATTERY_VOLTAGE);
    chartInstance->c81_is_ACTIVE = c81_IN_BATTERY_VOLTAGE;
    chartInstance->c81_was_ACTIVE = c81_IN_BATTERY_VOLTAGE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_BATTERY_VOLTAGE = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_BATTERY_VOLTAGE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    break;

   case c81_IN_ECT:
    CV_STATE_EVAL(23, 2, c81_IN_ECT);
    chartInstance->c81_is_ACTIVE = c81_IN_ECT;
    chartInstance->c81_was_ACTIVE = c81_IN_ECT;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c81_sfEvent);
    chartInstance->c81_b_tp_ECT = 1U;
    *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_ECT;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    break;

   case c81_IN_EMEA_CONTROLS1:
    CV_STATE_EVAL(23, 2, c81_IN_EMEA_CONTROLS1);
    chartInstance->c81_is_ACTIVE = c81_IN_EMEA_CONTROLS1;
    chartInstance->c81_was_ACTIVE = c81_IN_EMEA_CONTROLS1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_EMEA_CONTROLS1 = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_EMEA_CONTROLS;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    break;

   case c81_IN_ENGINE_HOURS:
    CV_STATE_EVAL(23, 2, c81_IN_ENGINE_HOURS);
    chartInstance->c81_is_ACTIVE = c81_IN_ENGINE_HOURS;
    chartInstance->c81_was_ACTIVE = c81_IN_ENGINE_HOURS;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_ENGINE_HOURS = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_ENGINE_HOURS;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 78U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ENGINE_HOURS = c81_c_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
    chartInstance->c81_d_tp_INACTIVE = 1U;
    chartInstance->c81_state_Jump = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
    break;

   case c81_IN_ENGINE_RPM:
    CV_STATE_EVAL(23, 2, c81_IN_ENGINE_RPM);
    chartInstance->c81_is_ACTIVE = c81_IN_ENGINE_RPM;
    chartInstance->c81_was_ACTIVE = c81_IN_ENGINE_RPM;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_ENGINE_RPM = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_ENGINE_RPM;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    break;

   case c81_IN_EOP:
    CV_STATE_EVAL(23, 2, c81_IN_EOP);
    chartInstance->c81_is_ACTIVE = c81_IN_EOP;
    chartInstance->c81_was_ACTIVE = c81_IN_EOP;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_EOP = 1U;
    *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_EOP;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    break;

   case c81_b_IN_ERROR_CODES:
    CV_STATE_EVAL(23, 2, c81_b_IN_ERROR_CODES);
    chartInstance->c81_is_ACTIVE = c81_b_IN_ERROR_CODES;
    chartInstance->c81_was_ACTIVE = c81_b_IN_ERROR_CODES;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_ERROR_CODES = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_ERROR_CODES;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    break;

   case c81_IN_FACTORY:
    CV_STATE_EVAL(23, 2, c81_IN_FACTORY);
    chartInstance->c81_is_ACTIVE = c81_IN_FACTORY;
    chartInstance->c81_was_ACTIVE = c81_IN_FACTORY;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 34U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_FACTORY = 1U;
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    chartInstance->c81_state_Jump = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
    c81_enter_internal_FACTORY(chartInstance);
    break;

   case c81_IN_HOT2:
    CV_STATE_EVAL(23, 2, c81_IN_HOT2);
    chartInstance->c81_is_ACTIVE = c81_IN_HOT2;
    chartInstance->c81_was_ACTIVE = c81_IN_HOT2;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_HOT2 = 1U;
    *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_HOT;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    break;

   case c81_IN_JOB_CLOCK_1:
    CV_STATE_EVAL(23, 2, c81_IN_JOB_CLOCK_1);
    chartInstance->c81_is_ACTIVE = c81_IN_JOB_CLOCK_1;
    chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_JOB_CLOCK_1 = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_JOB_CLOCK_1;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 56U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_JOB_CLOCK_1 = c81_c_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c81_sfEvent);
    chartInstance->c81_e_tp_INACTIVE = 1U;
    chartInstance->c81_state_Jump = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
    break;

   case c81_IN_JOB_CLOCK_2:
    CV_STATE_EVAL(23, 2, c81_IN_JOB_CLOCK_2);
    chartInstance->c81_is_ACTIVE = c81_IN_JOB_CLOCK_2;
    chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_2;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_JOB_CLOCK_2 = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_JOB_CLOCK_2;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 63U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_JOB_CLOCK_2 = c81_c_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c81_sfEvent);
    chartInstance->c81_f_tp_INACTIVE = 1U;
    chartInstance->c81_state_Jump = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
    break;

   case c81_IN_JOB_CLOCK_RESET1:
    CV_STATE_EVAL(23, 2, c81_IN_JOB_CLOCK_RESET1);
    chartInstance->c81_is_ACTIVE = c81_IN_JOB_CLOCK_RESET1;
    chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_RESET1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 46U, chartInstance->c81_sfEvent);
    chartInstance->c81_temporalCounter_i2 = 0U;
    chartInstance->c81_tp_JOB_CLOCK_RESET1 = 1U;
    c81_set_ee_JobClockLHP(chartInstance, 0, 0U);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
    matlab_UpdateEEVar();
    break;

   case c81_IN_JOB_CLOCK_RESET2:
    CV_STATE_EVAL(23, 2, c81_IN_JOB_CLOCK_RESET2);
    chartInstance->c81_is_ACTIVE = c81_IN_JOB_CLOCK_RESET2;
    chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_RESET2;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 47U, chartInstance->c81_sfEvent);
    chartInstance->c81_temporalCounter_i2 = 0U;
    chartInstance->c81_tp_JOB_CLOCK_RESET2 = 1U;
    c81_set_ee_JobClockLHP(chartInstance, 1, 0U);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
    matlab_UpdateEEVar();
    break;

   case c81_IN_SERVICE_CLOCK:
    CV_STATE_EVAL(23, 2, c81_IN_SERVICE_CLOCK);
    chartInstance->c81_is_ACTIVE = c81_IN_SERVICE_CLOCK;
    chartInstance->c81_was_ACTIVE = c81_IN_SERVICE_CLOCK;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 48U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_SERVICE_CLOCK = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_SERVICE_CLOCK;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_SERVICE_CLOCK = c81_c_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 50U, chartInstance->c81_sfEvent);
    chartInstance->c81_g_tp_INACTIVE = 1U;
    chartInstance->c81_state_Jump = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
    break;

   case c81_IN_SERVICE_CLOCK_RESET:
    CV_STATE_EVAL(23, 2, c81_IN_SERVICE_CLOCK_RESET);
    chartInstance->c81_is_ACTIVE = c81_IN_SERVICE_CLOCK_RESET;
    chartInstance->c81_was_ACTIVE = c81_IN_SERVICE_CLOCK_RESET;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 52U, chartInstance->c81_sfEvent);
    chartInstance->c81_temporalCounter_i2 = 0U;
    chartInstance->c81_tp_SERVICE_CLOCK_RESET = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_SERVICE_CLOCK_RESET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    break;

   default:
    CV_STATE_EVAL(23, 2, 0);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_ENGINE_HOURS;
    chartInstance->c81_was_ACTIVE = c81_IN_ENGINE_HOURS;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_ENGINE_HOURS = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_ENGINE_HOURS;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 78U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ENGINE_HOURS = c81_c_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
    chartInstance->c81_d_tp_INACTIVE = 1U;
    chartInstance->c81_state_Jump = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
    break;
  }
}

static void c81_b_ACTIVE(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_temp;
  boolean_T c81_b_temp;
  boolean_T c81_out;
  boolean_T c81_c_temp;
  boolean_T c81_d_temp;
  boolean_T c81_e_temp;
  boolean_T c81_b_out;
  boolean_T c81_f_temp;
  boolean_T c81_g_temp;
  boolean_T c81_c_out;
  boolean_T c81_h_temp;
  boolean_T c81_i_temp;
  boolean_T c81_d_out;
  boolean_T c81_e_out;
  boolean_T c81_f_out;
  boolean_T c81_g_out;
  boolean_T c81_h_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 81U, chartInstance->c81_sfEvent);
  c81_temp = (_SFD_CCP_CALL(5U, 81U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 81U, 0,
    (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
    chartInstance->c81_INACTIVE, 0, 1U, *chartInstance->c81_state_InfoSecondary
    != chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
  if (c81_temp) {
    c81_b_temp = (_SFD_CCP_CALL(5U, 81U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      81U, 1, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
      chartInstance->c81_prev_InfoSecondary, 0, 1U,
      *chartInstance->c81_state_InfoSecondary !=
      chartInstance->c81_prev_InfoSecondary) != 0U, chartInstance->c81_sfEvent)
                  != 0U);
    if (!c81_b_temp) {
      c81_b_temp = (_SFD_CCP_CALL(5U, 81U, 2,
        (chartInstance->c81_temporalCounter_i1 >= 40) != 0U,
        chartInstance->c81_sfEvent) != 0U);
    }

    c81_temp = c81_b_temp;
  }

  c81_out = (CV_TRANSITION_EVAL(81U, (int32_T)c81_temp) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 81U, chartInstance->c81_sfEvent);
    c81_exit_internal_ACTIVE(chartInstance);
    chartInstance->c81_d_tp_ACTIVE = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_PRIMARY_STATE = c81_b_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 55U, chartInstance->c81_sfEvent);
    chartInstance->c81_h_tp_INACTIVE = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_PRIMARY_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    chartInstance->c81_prev_InfoSecondary =
      *chartInstance->c81_state_InfoSecondary;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_InfoSecondary, 5U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 92U,
                 chartInstance->c81_sfEvent);
    c81_c_temp = (_SFD_CCP_CALL(5U, 92U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
      92U, 0, (real_T)chartInstance->c81_CD_AUTO_DISPLAY_FAULT_FUNCTION, (real_T)
      chartInstance->c81_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c81_CD_AUTO_DISPLAY_FAULT_FUNCTION !=
      chartInstance->c81_NON_FUNCTIONAL) != 0U, chartInstance->c81_sfEvent) !=
                  0U);
    if (c81_c_temp) {
      c81_c_temp = (_SFD_CCP_CALL(5U, 92U, 1, (c81_get_flag_StdActiveWarn
        (chartInstance, 0) != 0) != 0U, chartInstance->c81_sfEvent) != 0U);
    }

    c81_d_temp = c81_c_temp;
    if (c81_c_temp) {
      c81_d_temp = (_SFD_CCP_CALL(5U, 92U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
        92U, 1, (real_T)c81_get_ee_DeluxeG5(chartInstance, 0), (real_T)
        chartInstance->c81_ACTIVE, 0, 1U, c81_get_ee_DeluxeG5(chartInstance, 0)
        != chartInstance->c81_ACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
    }

    c81_e_temp = c81_d_temp;
    if (c81_d_temp) {
      c81_e_temp = (_SFD_CCP_CALL(5U, 92U, 3, (boolean_T)CV_RELATIONAL_EVAL(5U,
        92U, 2, (real_T)chartInstance->c81_CD_DELUXE_GEN5_5_FUNCTION, (real_T)
        chartInstance->c81_NON_FUNCTIONAL, 0, 0U,
        chartInstance->c81_CD_DELUXE_GEN5_5_FUNCTION ==
        chartInstance->c81_NON_FUNCTIONAL) != 0U, chartInstance->c81_sfEvent) !=
                    0U);
    }

    c81_b_out = (CV_TRANSITION_EVAL(92U, (int32_T)c81_e_temp) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 92U, chartInstance->c81_sfEvent);
      c81_exit_internal_ACTIVE(chartInstance);
      chartInstance->c81_d_tp_ACTIVE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_PRIMARY_STATE = c81_IN_ERROR_CODES;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 54U, chartInstance->c81_sfEvent);
      chartInstance->c81_temporalCounter_i1 = 0U;
      chartInstance->c81_b_tp_ERROR_CODES = 1U;
      c81_enter_atomic_ERROR_CODES(chartInstance);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 104U,
                   chartInstance->c81_sfEvent);
      c81_f_temp = (_SFD_CCP_CALL(5U, 104U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        104U, 0, (real_T)chartInstance->c81_CD_EMEA_CONTROLS_DISPLAY_MODE,
        (real_T)chartInstance->c81_NON_FUNCTIONAL, 0, 1U,
        chartInstance->c81_CD_EMEA_CONTROLS_DISPLAY_MODE !=
        chartInstance->c81_NON_FUNCTIONAL) != 0U, chartInstance->c81_sfEvent) !=
                    0U);
      if (c81_f_temp) {
        c81_f_temp = (_SFD_CCP_CALL(5U, 104U, 1,
          *chartInstance->c81_mode_ControlChange != 0U,
          chartInstance->c81_sfEvent) != 0U);
      }

      c81_g_temp = c81_f_temp;
      if (c81_f_temp) {
        c81_g_temp = (_SFD_CCP_CALL(5U, 104U, 2, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 104U, 1, (real_T)*chartInstance->c81_state_InfoPrimary, (real_T)
           chartInstance->c81_DISPLAY_EMEA_CONTROLS, 0, 1U,
           *chartInstance->c81_state_InfoPrimary !=
           chartInstance->c81_DISPLAY_EMEA_CONTROLS) != 0U,
          chartInstance->c81_sfEvent) != 0U);
      }

      c81_c_out = (CV_TRANSITION_EVAL(104U, (int32_T)c81_g_temp) != 0);
      if (c81_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 104U, chartInstance->c81_sfEvent);
        c81_exit_internal_ACTIVE(chartInstance);
        chartInstance->c81_d_tp_ACTIVE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_PRIMARY_STATE = c81_IN_EMEA_CONTROLS;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 53U, chartInstance->c81_sfEvent);
        chartInstance->c81_temporalCounter_i1 = 0U;
        chartInstance->c81_tp_EMEA_CONTROLS = 1U;
        *chartInstance->c81_state_InfoPrimary =
          chartInstance->c81_DISPLAY_EMEA_CONTROLS;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
        chartInstance->c81_prev_InfoSecondary =
          *chartInstance->c81_state_InfoSecondary;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_InfoSecondary, 5U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 99U,
                     chartInstance->c81_sfEvent);
        c81_h_temp = (_SFD_CCP_CALL(5U, 99U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          99U, 0, (real_T)chartInstance->c81_CD_SECOND_AUX_FUNCTION, (real_T)
          chartInstance->c81_NON_FUNCTIONAL, 0, 1U,
          chartInstance->c81_CD_SECOND_AUX_FUNCTION !=
          chartInstance->c81_NON_FUNCTIONAL) != 0U, chartInstance->c81_sfEvent)
                      != 0U);
        if (c81_h_temp) {
          c81_h_temp = (_SFD_CCP_CALL(5U, 99U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 99U, 1, (real_T)*chartInstance->c81_cmd_SecondAux, (real_T)
             chartInstance->c81_ACTIVE, 0, 0U, (int32_T)
             *chartInstance->c81_cmd_SecondAux == chartInstance->c81_ACTIVE) !=
            0U, chartInstance->c81_sfEvent) != 0U);
        }

        c81_i_temp = c81_h_temp;
        if (c81_h_temp) {
          c81_i_temp = (_SFD_CCP_CALL(5U, 99U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 99U, 2, (real_T)chartInstance->c81_prev_SecondAux, (real_T)
             chartInstance->c81_INACTIVE, 0, 0U, (int32_T)
             chartInstance->c81_prev_SecondAux == chartInstance->c81_INACTIVE)
            != 0U, chartInstance->c81_sfEvent) != 0U);
        }

        c81_d_out = (CV_TRANSITION_EVAL(99U, (int32_T)c81_i_temp) != 0);
        if (c81_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 99U, chartInstance->c81_sfEvent);
          c81_exit_internal_ACTIVE(chartInstance);
          chartInstance->c81_d_tp_ACTIVE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_PRIMARY_STATE = c81_IN_SECOND_AUX;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 56U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_SECOND_AUX = 1U;
          *chartInstance->c81_state_InfoPrimary =
            chartInstance->c81_DISPLAY_SECOND_AUX;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary,
                                28U);
          chartInstance->c81_prev_InfoSecondary =
            *chartInstance->c81_state_InfoSecondary;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_InfoSecondary,
                                5U);
          chartInstance->c81_prev_SecondAux = (chartInstance->c81_ACTIVE != 0);
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_SecondAux, 6U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 23U,
                       chartInstance->c81_sfEvent);
          if (chartInstance->c81_temporalCounter_i1 >= 50) {
            CV_STATE_EVAL(23, 3, 2);
            chartInstance->c81_prev_SecondAux = (chartInstance->c81_INACTIVE !=
              0);
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_SecondAux, 6U);
          } else {
            CV_STATE_EVAL(23, 3, 1);
          }

          switch (chartInstance->c81_is_ACTIVE) {
           case c81_IN_BATTERY_VOLTAGE:
            CV_STATE_EVAL(23, 0, c81_IN_BATTERY_VOLTAGE);
            *chartInstance->c81_state_InfoPrimary =
              chartInstance->c81_DISPLAY_BATTERY_VOLTAGE;
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 39U,
                         chartInstance->c81_sfEvent);
            c81_e_out = (CV_TRANSITION_EVAL(39U, (int32_T)(_SFD_CCP_CALL(5U, 39U,
              0, (boolean_T)CV_RELATIONAL_EVAL(5U, 39U, 0, (real_T)
              *chartInstance->c81_state_InfoButton, (real_T)
              chartInstance->c81_ACTIVE, 0, 0U,
              *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE)
              != 0U, chartInstance->c81_sfEvent) != 0U)) != 0);
            if (c81_e_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 39U,
                           chartInstance->c81_sfEvent);
              chartInstance->c81_tp_BATTERY_VOLTAGE = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
              chartInstance->c81_is_ACTIVE = c81_IN_SERVICE_CLOCK;
              chartInstance->c81_was_ACTIVE = c81_IN_SERVICE_CLOCK;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 48U, chartInstance->c81_sfEvent);
              chartInstance->c81_tp_SERVICE_CLOCK = 1U;
              *chartInstance->c81_state_InfoPrimary =
                chartInstance->c81_DISPLAY_SERVICE_CLOCK;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c81_state_InfoPrimary, 28U);
              *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton,
                                    29U);
              *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft,
                                    33U);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U,
                           chartInstance->c81_sfEvent);
              chartInstance->c81_is_SERVICE_CLOCK = c81_c_IN_INACTIVE;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 50U, chartInstance->c81_sfEvent);
              chartInstance->c81_g_tp_INACTIVE = 1U;
              chartInstance->c81_state_Jump = 0U;
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 24U,
                           chartInstance->c81_sfEvent);
            }

            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 24U,
                         chartInstance->c81_sfEvent);
            break;

           case c81_IN_ECT:
            CV_STATE_EVAL(23, 0, c81_IN_ECT);
            *chartInstance->c81_state_InfoPrimary =
              chartInstance->c81_DISPLAY_ECT;
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 36U,
                         chartInstance->c81_sfEvent);
            c81_f_out = (CV_TRANSITION_EVAL(36U, (int32_T)(_SFD_CCP_CALL(5U, 36U,
              0, (boolean_T)CV_RELATIONAL_EVAL(5U, 36U, 0, (real_T)
              *chartInstance->c81_state_InfoButton, (real_T)
              chartInstance->c81_ACTIVE, 0, 0U,
              *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE)
              != 0U, chartInstance->c81_sfEvent) != 0U)) != 0);
            if (c81_f_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 36U,
                           chartInstance->c81_sfEvent);
              chartInstance->c81_b_tp_ECT = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c81_sfEvent);
              chartInstance->c81_is_ACTIVE = c81_IN_HOT2;
              chartInstance->c81_was_ACTIVE = c81_IN_HOT2;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 37U, chartInstance->c81_sfEvent);
              chartInstance->c81_tp_HOT2 = 1U;
              *chartInstance->c81_state_InfoPrimary =
                chartInstance->c81_DISPLAY_HOT;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c81_state_InfoPrimary, 28U);
              *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton,
                                    29U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 25U,
                           chartInstance->c81_sfEvent);
            }

            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 25U,
                         chartInstance->c81_sfEvent);
            break;

           case c81_IN_EMEA_CONTROLS1:
            CV_STATE_EVAL(23, 0, c81_IN_EMEA_CONTROLS1);
            *chartInstance->c81_state_InfoPrimary =
              chartInstance->c81_DISPLAY_EMEA_CONTROLS;
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 112U,
                         chartInstance->c81_sfEvent);
            c81_g_out = (CV_TRANSITION_EVAL(112U, (int32_T)(_SFD_CCP_CALL(5U,
              112U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 112U, 0, (real_T)
              *chartInstance->c81_state_InfoButton, (real_T)
              chartInstance->c81_ACTIVE, 0, 0U,
              *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE)
              != 0U, chartInstance->c81_sfEvent) != 0U)) != 0);
            if (c81_g_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 112U,
                           chartInstance->c81_sfEvent);
              chartInstance->c81_tp_EMEA_CONTROLS1 = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c81_sfEvent);
              chartInstance->c81_is_ACTIVE = c81_IN_BATTERY_VOLTAGE;
              chartInstance->c81_was_ACTIVE = c81_IN_BATTERY_VOLTAGE;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
              chartInstance->c81_tp_BATTERY_VOLTAGE = 1U;
              *chartInstance->c81_state_InfoPrimary =
                chartInstance->c81_DISPLAY_BATTERY_VOLTAGE;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c81_state_InfoPrimary, 28U);
              *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton,
                                    29U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 26U,
                           chartInstance->c81_sfEvent);
            }

            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 26U,
                         chartInstance->c81_sfEvent);
            break;

           case c81_IN_ENGINE_HOURS:
            CV_STATE_EVAL(23, 0, c81_IN_ENGINE_HOURS);
            c81_ENGINE_HOURS(chartInstance);
            break;

           case c81_IN_ENGINE_RPM:
            CV_STATE_EVAL(23, 0, c81_IN_ENGINE_RPM);
            c81_ENGINE_RPM(chartInstance);
            break;

           case c81_IN_EOP:
            CV_STATE_EVAL(23, 0, c81_IN_EOP);
            *chartInstance->c81_state_InfoPrimary =
              chartInstance->c81_DISPLAY_EOP;
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 35U,
                         chartInstance->c81_sfEvent);
            c81_h_out = (CV_TRANSITION_EVAL(35U, (int32_T)(_SFD_CCP_CALL(5U, 35U,
              0, (boolean_T)CV_RELATIONAL_EVAL(5U, 35U, 0, (real_T)
              *chartInstance->c81_state_InfoButton, (real_T)
              chartInstance->c81_ACTIVE, 0, 0U,
              *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE)
              != 0U, chartInstance->c81_sfEvent) != 0U)) != 0);
            if (c81_h_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 35U,
                           chartInstance->c81_sfEvent);
              chartInstance->c81_tp_EOP = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c81_sfEvent);
              chartInstance->c81_is_ACTIVE = c81_IN_ECT;
              chartInstance->c81_was_ACTIVE = c81_IN_ECT;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c81_sfEvent);
              chartInstance->c81_b_tp_ECT = 1U;
              *chartInstance->c81_state_InfoPrimary =
                chartInstance->c81_DISPLAY_ECT;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c81_state_InfoPrimary, 28U);
              *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
              _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton,
                                    29U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 32U,
                           chartInstance->c81_sfEvent);
            }

            _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 32U,
                         chartInstance->c81_sfEvent);
            break;

           case c81_b_IN_ERROR_CODES:
            CV_STATE_EVAL(23, 0, c81_b_IN_ERROR_CODES);
            c81_ERROR_CODES(chartInstance);
            break;

           case c81_IN_FACTORY:
            CV_STATE_EVAL(23, 0, c81_IN_FACTORY);
            c81_FACTORY(chartInstance);
            break;

           case c81_IN_HOT2:
            CV_STATE_EVAL(23, 0, c81_IN_HOT2);
            c81_HOT2(chartInstance);
            break;

           case c81_IN_JOB_CLOCK_1:
            CV_STATE_EVAL(23, 0, c81_IN_JOB_CLOCK_1);
            c81_JOB_CLOCK_1(chartInstance);
            break;

           case c81_IN_JOB_CLOCK_2:
            CV_STATE_EVAL(23, 0, c81_IN_JOB_CLOCK_2);
            c81_JOB_CLOCK_2(chartInstance);
            break;

           case c81_IN_JOB_CLOCK_RESET1:
            CV_STATE_EVAL(23, 0, c81_IN_JOB_CLOCK_RESET1);
            c81_JOB_CLOCK_RESET1(chartInstance);
            break;

           case c81_IN_JOB_CLOCK_RESET2:
            CV_STATE_EVAL(23, 0, c81_IN_JOB_CLOCK_RESET2);
            c81_JOB_CLOCK_RESET2(chartInstance);
            break;

           case c81_IN_SERVICE_CLOCK:
            CV_STATE_EVAL(23, 0, c81_IN_SERVICE_CLOCK);
            c81_SERVICE_CLOCK(chartInstance);
            break;

           case c81_IN_SERVICE_CLOCK_RESET:
            CV_STATE_EVAL(23, 0, c81_IN_SERVICE_CLOCK_RESET);
            c81_SERVICE_CLOCK_RESET(chartInstance);
            break;

           default:
            CV_STATE_EVAL(23, 0, 0);

            /* Unreachable state, for coverage only */
            chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
            break;
          }
        }
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 23U, chartInstance->c81_sfEvent);
}

static void c81_exit_internal_ACTIVE(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c81_is_ACTIVE) {
   case c81_IN_BATTERY_VOLTAGE:
    CV_STATE_EVAL(23, 1, c81_IN_BATTERY_VOLTAGE);
    chartInstance->c81_tp_BATTERY_VOLTAGE = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_ECT:
    CV_STATE_EVAL(23, 1, c81_IN_ECT);
    chartInstance->c81_b_tp_ECT = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_EMEA_CONTROLS1:
    CV_STATE_EVAL(23, 1, c81_IN_EMEA_CONTROLS1);
    chartInstance->c81_tp_EMEA_CONTROLS1 = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_ENGINE_HOURS:
    CV_STATE_EVAL(23, 1, c81_IN_ENGINE_HOURS);
    c81_exit_internal_ENGINE_HOURS(chartInstance);
    chartInstance->c81_tp_ENGINE_HOURS = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_ENGINE_RPM:
    CV_STATE_EVAL(23, 1, c81_IN_ENGINE_RPM);
    chartInstance->c81_tp_ENGINE_RPM = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_EOP:
    CV_STATE_EVAL(23, 1, c81_IN_EOP);
    chartInstance->c81_tp_EOP = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c81_sfEvent);
    break;

   case c81_b_IN_ERROR_CODES:
    CV_STATE_EVAL(23, 1, c81_b_IN_ERROR_CODES);
    chartInstance->c81_tp_ERROR_CODES = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_FACTORY:
    CV_STATE_EVAL(23, 1, c81_IN_FACTORY);
    c81_exit_internal_FACTORY(chartInstance);
    chartInstance->c81_tp_FACTORY = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_HOT2:
    CV_STATE_EVAL(23, 1, c81_IN_HOT2);
    chartInstance->c81_tp_HOT2 = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_JOB_CLOCK_1:
    CV_STATE_EVAL(23, 1, c81_IN_JOB_CLOCK_1);
    c81_exit_internal_JOB_CLOCK_1(chartInstance);
    chartInstance->c81_tp_JOB_CLOCK_1 = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_JOB_CLOCK_2:
    CV_STATE_EVAL(23, 1, c81_IN_JOB_CLOCK_2);
    c81_exit_internal_JOB_CLOCK_2(chartInstance);
    chartInstance->c81_tp_JOB_CLOCK_2 = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_JOB_CLOCK_RESET1:
    CV_STATE_EVAL(23, 1, c81_IN_JOB_CLOCK_RESET1);
    chartInstance->c81_tp_JOB_CLOCK_RESET1 = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_JOB_CLOCK_RESET2:
    CV_STATE_EVAL(23, 1, c81_IN_JOB_CLOCK_RESET2);
    chartInstance->c81_tp_JOB_CLOCK_RESET2 = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 47U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_SERVICE_CLOCK:
    CV_STATE_EVAL(23, 1, c81_IN_SERVICE_CLOCK);
    c81_exit_internal_SERVICE_CLOCK(chartInstance);
    chartInstance->c81_tp_SERVICE_CLOCK = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 48U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_SERVICE_CLOCK_RESET:
    CV_STATE_EVAL(23, 1, c81_IN_SERVICE_CLOCK_RESET);
    chartInstance->c81_tp_SERVICE_CLOCK_RESET = 0U;
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 52U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(23, 1, 0);
    chartInstance->c81_is_ACTIVE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
    break;
  }
}

static void c81_ENGINE_HOURS(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_c_out;
  boolean_T c81_d_out;
  boolean_T c81_temp;
  boolean_T c81_e_out;
  boolean_T c81_f_out;
  *chartInstance->c81_state_InfoPrimary =
    chartInstance->c81_DISPLAY_ENGINE_HOURS;
  *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 75U, chartInstance->c81_sfEvent);
  c81_out = (CV_TRANSITION_EVAL(75U, (int32_T)(_SFD_CCP_CALL(5U, 75U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 75U, 0, (real_T)
    chartInstance->c81_state_Jump, (real_T)chartInstance->c81_ACTIVE, 0, 0U,
    chartInstance->c81_state_Jump == chartInstance->c81_ACTIVE) != 0U,
    chartInstance->c81_sfEvent) != 0U)) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 75U, chartInstance->c81_sfEvent);
    c81_exit_internal_ENGINE_HOURS(chartInstance);
    chartInstance->c81_tp_ENGINE_HOURS = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_FACTORY;
    chartInstance->c81_was_ACTIVE = c81_IN_FACTORY;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 34U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_FACTORY = 1U;
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    chartInstance->c81_state_Jump = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
    c81_enter_internal_FACTORY(chartInstance);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 14U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(14U, (int32_T)(_SFD_CCP_CALL(5U, 14U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 14U, 0, (real_T)
      *chartInstance->c81_state_InfoButton, (real_T)chartInstance->c81_ACTIVE, 0,
      0U, *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE) !=
      0U, chartInstance->c81_sfEvent) != 0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c81_sfEvent);
      c81_exit_internal_ENGINE_HOURS(chartInstance);
      chartInstance->c81_tp_ENGINE_HOURS = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_ACTIVE = c81_IN_JOB_CLOCK_1;
      chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_1;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_JOB_CLOCK_1 = 1U;
      *chartInstance->c81_state_InfoPrimary =
        chartInstance->c81_DISPLAY_JOB_CLOCK_1;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
      *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
      *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 56U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_JOB_CLOCK_1 = c81_c_IN_INACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c81_sfEvent);
      chartInstance->c81_e_tp_INACTIVE = 1U;
      chartInstance->c81_state_Jump = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 84U,
                   chartInstance->c81_sfEvent);
      c81_c_out = (CV_TRANSITION_EVAL(84U, (int32_T)(_SFD_CCP_CALL(5U, 84U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 84U, 0, (real_T)
        *chartInstance->c81_state_Engine, (real_T)
        chartInstance->c81_ENGINE_CRANKING, 0, 0U,
        *chartInstance->c81_state_Engine == chartInstance->c81_ENGINE_CRANKING)
        != 0U, chartInstance->c81_sfEvent) != 0U)) != 0);
      if (c81_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 84U, chartInstance->c81_sfEvent);
        c81_exit_internal_ENGINE_HOURS(chartInstance);
        chartInstance->c81_tp_ENGINE_HOURS = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_ACTIVE = c81_IN_ENGINE_RPM;
        chartInstance->c81_was_ACTIVE = c81_IN_ENGINE_RPM;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c81_sfEvent);
        chartInstance->c81_tp_ENGINE_RPM = 1U;
        *chartInstance->c81_state_InfoPrimary =
          chartInstance->c81_DISPLAY_ENGINE_RPM;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
        *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 27U,
                     chartInstance->c81_sfEvent);
        switch (chartInstance->c81_is_ENGINE_HOURS) {
         case c81_IN_DEBOUNCE:
          CV_STATE_EVAL(27, 0, c81_IN_DEBOUNCE);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 77U,
                       chartInstance->c81_sfEvent);
          c81_d_out = (CV_TRANSITION_EVAL(77U, (int32_T)(_SFD_CCP_CALL(5U, 77U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 77U, 0, (real_T)
            chartInstance->c81_debounceCount, 50.0, 0, 5U,
            chartInstance->c81_debounceCount >= 50) != 0U,
            chartInstance->c81_sfEvent) != 0U)) != 0);
          if (c81_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 77U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_DEBOUNCE = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_ENGINE_HOURS = c81_IN_RESET_STATE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 30U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_RESET_STATE = 1U;
            chartInstance->c81_state_Jump = chartInstance->c81_ACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 80U,
                         chartInstance->c81_sfEvent);
            c81_e_out = (CV_TRANSITION_EVAL(80U, (int32_T)(_SFD_CCP_CALL(5U, 80U,
              0, (boolean_T)CV_RELATIONAL_EVAL(5U, 80U, 0, (real_T)
              ((*chartInstance->c81_msg_PanelButtonState)[0] &
               chartInstance->c81_INFO_BUTTON_MASK), (real_T)
              chartInstance->c81_INACTIVE, 0, 0U,
              ((*chartInstance->c81_msg_PanelButtonState)[0] &
               chartInstance->c81_INFO_BUTTON_MASK) ==
              chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) !=
              0U)) != 0);
            if (c81_e_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 80U,
                           chartInstance->c81_sfEvent);
              chartInstance->c81_tp_DEBOUNCE = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c81_sfEvent);
              chartInstance->c81_is_ENGINE_HOURS = c81_c_IN_INACTIVE;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
              chartInstance->c81_d_tp_INACTIVE = 1U;
              chartInstance->c81_state_Jump = 0U;
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 28U,
                           chartInstance->c81_sfEvent);
              chartInstance->c81_debounceCount = c81__u16_s32_(chartInstance,
                c81__s32_add__(chartInstance, (int32_T)
                               chartInstance->c81_debounceCount, 1, 867U, 34U,
                               15U), 867U, 34U, 15U);
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
            }
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 28U, chartInstance->c81_sfEvent);
          break;

         case c81_c_IN_INACTIVE:
          CV_STATE_EVAL(27, 0, c81_c_IN_INACTIVE);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 79U,
                       chartInstance->c81_sfEvent);
          c81_temp = (_SFD_CCP_CALL(5U, 79U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
            79U, 0, (real_T)((*chartInstance->c81_msg_PanelButtonState)[0] &
                             chartInstance->c81_INFO_BUTTON_MASK), (real_T)
            chartInstance->c81_INFO_BUTTON_PRESS, 0, 0U,
            ((*chartInstance->c81_msg_PanelButtonState)[0] &
             chartInstance->c81_INFO_BUTTON_MASK) ==
            chartInstance->c81_INFO_BUTTON_PRESS) != 0U,
            chartInstance->c81_sfEvent) != 0U);
          if (c81_temp) {
            c81_temp = (_SFD_CCP_CALL(5U, 79U, 1, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 79U, 1, (real_T)*chartInstance->c81_state_InfoSecondary,
               (real_T)chartInstance->c81_INACTIVE, 0, 0U,
               *chartInstance->c81_state_InfoSecondary ==
               chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent)
                        != 0U);
          }

          c81_f_out = (CV_TRANSITION_EVAL(79U, (int32_T)c81_temp) != 0);
          if (c81_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 79U, chartInstance->c81_sfEvent);
            chartInstance->c81_d_tp_INACTIVE = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_ENGINE_HOURS = c81_IN_DEBOUNCE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 28U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_DEBOUNCE = 1U;
            chartInstance->c81_debounceCount = 0U;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 29U,
                         chartInstance->c81_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 29U, chartInstance->c81_sfEvent);
          break;

         case c81_IN_RESET_STATE:
          CV_STATE_EVAL(27, 0, c81_IN_RESET_STATE);
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 30U,
                       chartInstance->c81_sfEvent);
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 30U, chartInstance->c81_sfEvent);
          break;

         default:
          CV_STATE_EVAL(27, 0, 0);

          /* Unreachable state, for coverage only */
          chartInstance->c81_is_ENGINE_HOURS = c81_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c81_sfEvent);
          break;
        }
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 27U, chartInstance->c81_sfEvent);
}

static void c81_exit_internal_ENGINE_HOURS(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c81_is_ENGINE_HOURS) {
   case c81_IN_DEBOUNCE:
    CV_STATE_EVAL(27, 1, c81_IN_DEBOUNCE);
    chartInstance->c81_tp_DEBOUNCE = 0U;
    chartInstance->c81_is_ENGINE_HOURS = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c81_sfEvent);
    break;

   case c81_c_IN_INACTIVE:
    CV_STATE_EVAL(27, 1, c81_c_IN_INACTIVE);
    chartInstance->c81_d_tp_INACTIVE = 0U;
    chartInstance->c81_is_ENGINE_HOURS = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_RESET_STATE:
    CV_STATE_EVAL(27, 1, c81_IN_RESET_STATE);
    chartInstance->c81_tp_RESET_STATE = 0U;
    chartInstance->c81_is_ENGINE_HOURS = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(27, 1, 0);
    chartInstance->c81_is_ENGINE_HOURS = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c81_sfEvent);
    break;
  }
}

static void c81_JOB_CLOCK_1(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_c_out;
  boolean_T c81_temp;
  boolean_T c81_d_out;
  boolean_T c81_e_out;
  *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_JOB_CLOCK_1;
  *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 60U, chartInstance->c81_sfEvent);
  c81_out = (CV_TRANSITION_EVAL(60U, (int32_T)(_SFD_CCP_CALL(5U, 60U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 60U, 0, (real_T)
    chartInstance->c81_state_Jump, (real_T)chartInstance->c81_ACTIVE, 0, 0U,
    chartInstance->c81_state_Jump == chartInstance->c81_ACTIVE) != 0U,
    chartInstance->c81_sfEvent) != 0U)) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 60U, chartInstance->c81_sfEvent);
    c81_exit_internal_JOB_CLOCK_1(chartInstance);
    chartInstance->c81_tp_JOB_CLOCK_1 = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_JOB_CLOCK_RESET1;
    chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_RESET1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 46U, chartInstance->c81_sfEvent);
    chartInstance->c81_temporalCounter_i2 = 0U;
    chartInstance->c81_tp_JOB_CLOCK_RESET1 = 1U;
    c81_set_ee_JobClockLHP(chartInstance, 0, 0U);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
    matlab_UpdateEEVar();
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 55U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(55U, (int32_T)(_SFD_CCP_CALL(5U, 55U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 55U, 0, (real_T)
      *chartInstance->c81_state_InfoButton, (real_T)chartInstance->c81_ACTIVE, 0,
      0U, *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE) !=
      0U, chartInstance->c81_sfEvent) != 0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 55U, chartInstance->c81_sfEvent);
      c81_exit_internal_JOB_CLOCK_1(chartInstance);
      chartInstance->c81_tp_JOB_CLOCK_1 = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 38U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_ACTIVE = c81_IN_JOB_CLOCK_2;
      chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_2;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_JOB_CLOCK_2 = 1U;
      *chartInstance->c81_state_InfoPrimary =
        chartInstance->c81_DISPLAY_JOB_CLOCK_2;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
      *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
      *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 63U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_JOB_CLOCK_2 = c81_c_IN_INACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c81_sfEvent);
      chartInstance->c81_f_tp_INACTIVE = 1U;
      chartInstance->c81_state_Jump = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 38U,
                   chartInstance->c81_sfEvent);
      switch (chartInstance->c81_is_JOB_CLOCK_1) {
       case c81_IN_DEBOUNCE:
        CV_STATE_EVAL(38, 0, c81_IN_DEBOUNCE);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 59U,
                     chartInstance->c81_sfEvent);
        c81_c_out = (CV_TRANSITION_EVAL(59U, (int32_T)(_SFD_CCP_CALL(5U, 59U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 59U, 0, (real_T)
          chartInstance->c81_debounceCount, 25.0, 0, 5U,
          chartInstance->c81_debounceCount >= 25) != 0U,
          chartInstance->c81_sfEvent) != 0U)) != 0);
        if (c81_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 59U, chartInstance->c81_sfEvent);
          chartInstance->c81_b_tp_DEBOUNCE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_JOB_CLOCK_1 = c81_IN_RESET_STATE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 41U, chartInstance->c81_sfEvent);
          chartInstance->c81_b_tp_RESET_STATE = 1U;
          chartInstance->c81_state_Jump = chartInstance->c81_ACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 58U,
                       chartInstance->c81_sfEvent);
          c81_d_out = (CV_TRANSITION_EVAL(58U, (int32_T)(_SFD_CCP_CALL(5U, 58U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 58U, 0, (real_T)
            ((*chartInstance->c81_msg_PanelButtonState)[0] &
             chartInstance->c81_INFO_BUTTON_MASK), (real_T)
            chartInstance->c81_INACTIVE, 0, 0U,
            ((*chartInstance->c81_msg_PanelButtonState)[0] &
             chartInstance->c81_INFO_BUTTON_MASK) == chartInstance->c81_INACTIVE)
            != 0U, chartInstance->c81_sfEvent) != 0U)) != 0);
          if (c81_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 58U, chartInstance->c81_sfEvent);
            chartInstance->c81_b_tp_DEBOUNCE = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_JOB_CLOCK_1 = c81_c_IN_INACTIVE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c81_sfEvent);
            chartInstance->c81_e_tp_INACTIVE = 1U;
            chartInstance->c81_state_Jump = 0U;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 39U,
                         chartInstance->c81_sfEvent);
            chartInstance->c81_debounceCount = c81__u16_s32_(chartInstance,
              c81__s32_add__(chartInstance, (int32_T)
                             chartInstance->c81_debounceCount, 1, 788U, 34U, 15U),
              788U, 34U, 15U);
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 39U, chartInstance->c81_sfEvent);
        break;

       case c81_c_IN_INACTIVE:
        CV_STATE_EVAL(38, 0, c81_c_IN_INACTIVE);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 57U,
                     chartInstance->c81_sfEvent);
        c81_temp = (_SFD_CCP_CALL(5U, 57U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          57U, 0, (real_T)((*chartInstance->c81_msg_PanelButtonState)[0] &
                           chartInstance->c81_INFO_BUTTON_MASK), (real_T)
          chartInstance->c81_INFO_BUTTON_PRESS, 0, 0U,
          ((*chartInstance->c81_msg_PanelButtonState)[0] &
           chartInstance->c81_INFO_BUTTON_MASK) ==
          chartInstance->c81_INFO_BUTTON_PRESS) != 0U,
          chartInstance->c81_sfEvent) != 0U);
        if (c81_temp) {
          c81_temp = (_SFD_CCP_CALL(5U, 57U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
            57U, 1, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
            chartInstance->c81_INACTIVE, 0, 0U,
            *chartInstance->c81_state_InfoSecondary ==
            chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) !=
                      0U);
        }

        c81_e_out = (CV_TRANSITION_EVAL(57U, (int32_T)c81_temp) != 0);
        if (c81_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 57U, chartInstance->c81_sfEvent);
          chartInstance->c81_e_tp_INACTIVE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_JOB_CLOCK_1 = c81_IN_DEBOUNCE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 39U, chartInstance->c81_sfEvent);
          chartInstance->c81_b_tp_DEBOUNCE = 1U;
          chartInstance->c81_debounceCount = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 40U,
                       chartInstance->c81_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 40U, chartInstance->c81_sfEvent);
        break;

       case c81_IN_RESET_STATE:
        CV_STATE_EVAL(38, 0, c81_IN_RESET_STATE);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 41U,
                     chartInstance->c81_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 41U, chartInstance->c81_sfEvent);
        break;

       default:
        CV_STATE_EVAL(38, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c81_is_JOB_CLOCK_1 = c81_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c81_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 38U, chartInstance->c81_sfEvent);
}

static void c81_exit_internal_JOB_CLOCK_1(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c81_is_JOB_CLOCK_1) {
   case c81_IN_DEBOUNCE:
    CV_STATE_EVAL(38, 1, c81_IN_DEBOUNCE);
    chartInstance->c81_b_tp_DEBOUNCE = 0U;
    chartInstance->c81_is_JOB_CLOCK_1 = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c81_sfEvent);
    break;

   case c81_c_IN_INACTIVE:
    CV_STATE_EVAL(38, 1, c81_c_IN_INACTIVE);
    chartInstance->c81_e_tp_INACTIVE = 0U;
    chartInstance->c81_is_JOB_CLOCK_1 = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 40U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_RESET_STATE:
    CV_STATE_EVAL(38, 1, c81_IN_RESET_STATE);
    chartInstance->c81_b_tp_RESET_STATE = 0U;
    chartInstance->c81_is_JOB_CLOCK_1 = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 41U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(38, 1, 0);
    chartInstance->c81_is_JOB_CLOCK_1 = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 39U, chartInstance->c81_sfEvent);
    break;
  }
}

static void c81_JOB_CLOCK_RESET1(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c81_temp;
  boolean_T c81_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 61U, chartInstance->c81_sfEvent);
  c81_temp = (_SFD_CCP_CALL(5U, 61U, 0, true != 0U, chartInstance->c81_sfEvent)
              != 0U);
  if (c81_temp) {
    c81_temp = (_SFD_CCP_CALL(5U, 61U, 1, (chartInstance->c81_temporalCounter_i2
      >= 10) != 0U, chartInstance->c81_sfEvent) != 0U);
  }

  c81_out = (CV_TRANSITION_EVAL(61U, (int32_T)c81_temp) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_JOB_CLOCK_RESET1 = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 46U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_JOB_CLOCK_1;
    chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 38U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_JOB_CLOCK_1 = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_JOB_CLOCK_1;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 56U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_JOB_CLOCK_1 = c81_c_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 40U, chartInstance->c81_sfEvent);
    chartInstance->c81_e_tp_INACTIVE = 1U;
    chartInstance->c81_state_Jump = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 46U,
                 chartInstance->c81_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 46U, chartInstance->c81_sfEvent);
}

static void c81_JOB_CLOCK_2(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_c_out;
  boolean_T c81_temp;
  boolean_T c81_d_out;
  boolean_T c81_e_out;
  *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_JOB_CLOCK_2;
  *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 16U, chartInstance->c81_sfEvent);
  c81_out = (CV_TRANSITION_EVAL(16U, (int32_T)(_SFD_CCP_CALL(5U, 16U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 16U, 0, (real_T)
    *chartInstance->c81_state_InfoButton, (real_T)chartInstance->c81_ACTIVE, 0,
    0U, *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE) != 0U,
    chartInstance->c81_sfEvent) != 0U)) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c81_sfEvent);
    c81_exit_internal_JOB_CLOCK_2(chartInstance);
    chartInstance->c81_tp_JOB_CLOCK_2 = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_ENGINE_RPM;
    chartInstance->c81_was_ACTIVE = c81_IN_ENGINE_RPM;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_ENGINE_RPM = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_ENGINE_RPM;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 67U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(67U, (int32_T)(_SFD_CCP_CALL(5U, 67U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 67U, 0, (real_T)
      chartInstance->c81_state_Jump, (real_T)chartInstance->c81_ACTIVE, 0, 0U,
      chartInstance->c81_state_Jump == chartInstance->c81_ACTIVE) != 0U,
      chartInstance->c81_sfEvent) != 0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 67U, chartInstance->c81_sfEvent);
      c81_exit_internal_JOB_CLOCK_2(chartInstance);
      chartInstance->c81_tp_JOB_CLOCK_2 = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 42U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_ACTIVE = c81_IN_JOB_CLOCK_RESET2;
      chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_RESET2;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 47U, chartInstance->c81_sfEvent);
      chartInstance->c81_temporalCounter_i2 = 0U;
      chartInstance->c81_tp_JOB_CLOCK_RESET2 = 1U;
      c81_set_ee_JobClockLHP(chartInstance, 1, 0U);
      ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
      matlab_UpdateEEVar();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 42U,
                   chartInstance->c81_sfEvent);
      switch (chartInstance->c81_is_JOB_CLOCK_2) {
       case c81_IN_DEBOUNCE:
        CV_STATE_EVAL(42, 0, c81_IN_DEBOUNCE);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 66U,
                     chartInstance->c81_sfEvent);
        c81_c_out = (CV_TRANSITION_EVAL(66U, (int32_T)(_SFD_CCP_CALL(5U, 66U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 66U, 0, (real_T)
          chartInstance->c81_debounceCount, 25.0, 0, 5U,
          chartInstance->c81_debounceCount >= 25) != 0U,
          chartInstance->c81_sfEvent) != 0U)) != 0);
        if (c81_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 66U, chartInstance->c81_sfEvent);
          chartInstance->c81_c_tp_DEBOUNCE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_JOB_CLOCK_2 = c81_IN_RESET_STATE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 45U, chartInstance->c81_sfEvent);
          chartInstance->c81_c_tp_RESET_STATE = 1U;
          chartInstance->c81_state_Jump = chartInstance->c81_ACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 64U,
                       chartInstance->c81_sfEvent);
          c81_d_out = (CV_TRANSITION_EVAL(64U, (int32_T)(_SFD_CCP_CALL(5U, 64U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 64U, 0, (real_T)
            ((*chartInstance->c81_msg_PanelButtonState)[0] &
             chartInstance->c81_INFO_BUTTON_MASK), (real_T)
            chartInstance->c81_INACTIVE, 0, 0U,
            ((*chartInstance->c81_msg_PanelButtonState)[0] &
             chartInstance->c81_INFO_BUTTON_MASK) == chartInstance->c81_INACTIVE)
            != 0U, chartInstance->c81_sfEvent) != 0U)) != 0);
          if (c81_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 64U, chartInstance->c81_sfEvent);
            chartInstance->c81_c_tp_DEBOUNCE = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_JOB_CLOCK_2 = c81_c_IN_INACTIVE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c81_sfEvent);
            chartInstance->c81_f_tp_INACTIVE = 1U;
            chartInstance->c81_state_Jump = 0U;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 43U,
                         chartInstance->c81_sfEvent);
            chartInstance->c81_debounceCount = c81__u16_s32_(chartInstance,
              c81__s32_add__(chartInstance, (int32_T)
                             chartInstance->c81_debounceCount, 1, 832U, 34U, 15U),
              832U, 34U, 15U);
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 43U, chartInstance->c81_sfEvent);
        break;

       case c81_c_IN_INACTIVE:
        CV_STATE_EVAL(42, 0, c81_c_IN_INACTIVE);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 65U,
                     chartInstance->c81_sfEvent);
        c81_temp = (_SFD_CCP_CALL(5U, 65U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          65U, 0, (real_T)((*chartInstance->c81_msg_PanelButtonState)[0] &
                           chartInstance->c81_INFO_BUTTON_MASK), (real_T)
          chartInstance->c81_INFO_BUTTON_PRESS, 0, 0U,
          ((*chartInstance->c81_msg_PanelButtonState)[0] &
           chartInstance->c81_INFO_BUTTON_MASK) ==
          chartInstance->c81_INFO_BUTTON_PRESS) != 0U,
          chartInstance->c81_sfEvent) != 0U);
        if (c81_temp) {
          c81_temp = (_SFD_CCP_CALL(5U, 65U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
            65U, 1, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
            chartInstance->c81_INACTIVE, 0, 0U,
            *chartInstance->c81_state_InfoSecondary ==
            chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) !=
                      0U);
        }

        c81_e_out = (CV_TRANSITION_EVAL(65U, (int32_T)c81_temp) != 0);
        if (c81_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 65U, chartInstance->c81_sfEvent);
          chartInstance->c81_f_tp_INACTIVE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_JOB_CLOCK_2 = c81_IN_DEBOUNCE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 43U, chartInstance->c81_sfEvent);
          chartInstance->c81_c_tp_DEBOUNCE = 1U;
          chartInstance->c81_debounceCount = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 44U,
                       chartInstance->c81_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 44U, chartInstance->c81_sfEvent);
        break;

       case c81_IN_RESET_STATE:
        CV_STATE_EVAL(42, 0, c81_IN_RESET_STATE);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 45U,
                     chartInstance->c81_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 45U, chartInstance->c81_sfEvent);
        break;

       default:
        CV_STATE_EVAL(42, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c81_is_JOB_CLOCK_2 = c81_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c81_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 42U, chartInstance->c81_sfEvent);
}

static void c81_exit_internal_JOB_CLOCK_2(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c81_is_JOB_CLOCK_2) {
   case c81_IN_DEBOUNCE:
    CV_STATE_EVAL(42, 1, c81_IN_DEBOUNCE);
    chartInstance->c81_c_tp_DEBOUNCE = 0U;
    chartInstance->c81_is_JOB_CLOCK_2 = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c81_sfEvent);
    break;

   case c81_c_IN_INACTIVE:
    CV_STATE_EVAL(42, 1, c81_c_IN_INACTIVE);
    chartInstance->c81_f_tp_INACTIVE = 0U;
    chartInstance->c81_is_JOB_CLOCK_2 = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 44U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_RESET_STATE:
    CV_STATE_EVAL(42, 1, c81_IN_RESET_STATE);
    chartInstance->c81_c_tp_RESET_STATE = 0U;
    chartInstance->c81_is_JOB_CLOCK_2 = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 45U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(42, 1, 0);
    chartInstance->c81_is_JOB_CLOCK_2 = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 43U, chartInstance->c81_sfEvent);
    break;
  }
}

static void c81_JOB_CLOCK_RESET2(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c81_temp;
  boolean_T c81_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 62U, chartInstance->c81_sfEvent);
  c81_temp = (_SFD_CCP_CALL(5U, 62U, 0, true != 0U, chartInstance->c81_sfEvent)
              != 0U);
  if (c81_temp) {
    c81_temp = (_SFD_CCP_CALL(5U, 62U, 1, (chartInstance->c81_temporalCounter_i2
      >= 10) != 0U, chartInstance->c81_sfEvent) != 0U);
  }

  c81_out = (CV_TRANSITION_EVAL(62U, (int32_T)c81_temp) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 62U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_JOB_CLOCK_RESET2 = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 47U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_JOB_CLOCK_2;
    chartInstance->c81_was_ACTIVE = c81_IN_JOB_CLOCK_2;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 42U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_JOB_CLOCK_2 = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_JOB_CLOCK_2;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 63U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_JOB_CLOCK_2 = c81_c_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 44U, chartInstance->c81_sfEvent);
    chartInstance->c81_f_tp_INACTIVE = 1U;
    chartInstance->c81_state_Jump = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 47U,
                 chartInstance->c81_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 47U, chartInstance->c81_sfEvent);
}

static void c81_enter_internal_FACTORY(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c81_out;
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 86U, chartInstance->c81_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 87U, chartInstance->c81_sfEvent);
  c81_out = (CV_TRANSITION_EVAL(87U, (int32_T)(_SFD_CCP_CALL(5U, 87U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 87U, 0, (real_T)
    chartInstance->c81_CD_HOT_FUNCTION, (real_T)
    chartInstance->c81_NON_FUNCTIONAL, 0, 1U, chartInstance->c81_CD_HOT_FUNCTION
    != chartInstance->c81_NON_FUNCTIONAL) != 0U, chartInstance->c81_sfEvent) !=
    0U)) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 87U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_FACTORY = c81_IN_HOT;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_HOT = 1U;
    *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_HOT;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 85U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_FACTORY = c81_b_IN_ECT;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_ECT = 1U;
    *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_ECT;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
  }
}

static void c81_FACTORY(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 76U, chartInstance->c81_sfEvent);
  c81_out = (CV_TRANSITION_EVAL(76U, (int32_T)(_SFD_CCP_CALL(5U, 76U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 76U, 0, (real_T)
    *chartInstance->c81_state_InfoButton, (real_T)chartInstance->c81_ACTIVE, 0,
    0U, *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE) != 0U,
    chartInstance->c81_sfEvent) != 0U)) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 76U, chartInstance->c81_sfEvent);
    c81_exit_internal_FACTORY(chartInstance);
    chartInstance->c81_tp_FACTORY = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_ENGINE_HOURS;
    chartInstance->c81_was_ACTIVE = c81_IN_ENGINE_HOURS;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_ENGINE_HOURS = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_ENGINE_HOURS;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 78U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ENGINE_HOURS = c81_c_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
    chartInstance->c81_d_tp_INACTIVE = 1U;
    chartInstance->c81_state_Jump = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 34U,
                 chartInstance->c81_sfEvent);
    switch (chartInstance->c81_is_FACTORY) {
     case c81_b_IN_ECT:
      CV_STATE_EVAL(34, 0, c81_b_IN_ECT);
      *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_ECT;
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 35U,
                   chartInstance->c81_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 35U, chartInstance->c81_sfEvent);
      break;

     case c81_IN_HOT:
      CV_STATE_EVAL(34, 0, c81_IN_HOT);
      *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_HOT;
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 36U,
                   chartInstance->c81_sfEvent);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 36U, chartInstance->c81_sfEvent);
      break;

     default:
      CV_STATE_EVAL(34, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c81_is_FACTORY = c81_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c81_sfEvent);
      break;
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 34U, chartInstance->c81_sfEvent);
}

static void c81_exit_internal_FACTORY(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c81_is_FACTORY) {
   case c81_b_IN_ECT:
    CV_STATE_EVAL(34, 1, c81_b_IN_ECT);
    chartInstance->c81_tp_ECT = 0U;
    chartInstance->c81_is_FACTORY = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_HOT:
    CV_STATE_EVAL(34, 1, c81_IN_HOT);
    chartInstance->c81_tp_HOT = 0U;
    chartInstance->c81_is_FACTORY = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(34, 1, 0);
    chartInstance->c81_is_FACTORY = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c81_sfEvent);
    break;
  }
}

static void c81_ENGINE_RPM(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_temp;
  boolean_T c81_out;
  boolean_T c81_b_out;
  *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_ENGINE_RPM;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 111U,
               chartInstance->c81_sfEvent);
  c81_temp = (_SFD_CCP_CALL(5U, 111U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 111U,
    0, (real_T)*chartInstance->c81_state_InfoButton, (real_T)
    chartInstance->c81_ACTIVE, 0, 0U, *chartInstance->c81_state_InfoButton ==
    chartInstance->c81_ACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
  if (c81_temp) {
    c81_temp = (_SFD_CCP_CALL(5U, 111U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      111U, 1, (real_T)chartInstance->c81_CD_EMEA_CONTROLS_DISPLAY_MODE, (real_T)
      chartInstance->c81_NON_FUNCTIONAL, 0, 1U,
      chartInstance->c81_CD_EMEA_CONTROLS_DISPLAY_MODE !=
      chartInstance->c81_NON_FUNCTIONAL) != 0U, chartInstance->c81_sfEvent) !=
                0U);
  }

  c81_out = (CV_TRANSITION_EVAL(111U, (int32_T)c81_temp) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 111U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_ENGINE_RPM = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_EMEA_CONTROLS1;
    chartInstance->c81_was_ACTIVE = c81_IN_EMEA_CONTROLS1;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_EMEA_CONTROLS1 = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_EMEA_CONTROLS;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 54U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(54U, (int32_T)(_SFD_CCP_CALL(5U, 54U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 54U, 0, (real_T)
      *chartInstance->c81_state_InfoButton, (real_T)chartInstance->c81_ACTIVE, 0,
      0U, *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE) !=
      0U, chartInstance->c81_sfEvent) != 0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 54U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_ENGINE_RPM = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_ACTIVE = c81_IN_BATTERY_VOLTAGE;
      chartInstance->c81_was_ACTIVE = c81_IN_BATTERY_VOLTAGE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_BATTERY_VOLTAGE = 1U;
      *chartInstance->c81_state_InfoPrimary =
        chartInstance->c81_DISPLAY_BATTERY_VOLTAGE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
      *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 31U,
                   chartInstance->c81_sfEvent);
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 31U, chartInstance->c81_sfEvent);
}

static void c81_SERVICE_CLOCK_RESET(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c81_temp;
  boolean_T c81_out;
  *chartInstance->c81_state_InfoPrimary =
    chartInstance->c81_DISPLAY_SERVICE_CLOCK_RESET;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U, chartInstance->c81_sfEvent);
  c81_temp = (_SFD_CCP_CALL(5U, 11U, 0, true != 0U, chartInstance->c81_sfEvent)
              != 0U);
  if (c81_temp) {
    c81_temp = (_SFD_CCP_CALL(5U, 11U, 1, (chartInstance->c81_temporalCounter_i2
      >= 70) != 0U, chartInstance->c81_sfEvent) != 0U);
  }

  c81_out = (CV_TRANSITION_EVAL(11U, (int32_T)c81_temp) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_SERVICE_CLOCK_RESET = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 52U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_SERVICE_CLOCK;
    chartInstance->c81_was_ACTIVE = c81_IN_SERVICE_CLOCK;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 48U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_SERVICE_CLOCK = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_SERVICE_CLOCK;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_SERVICE_CLOCK = c81_c_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 50U, chartInstance->c81_sfEvent);
    chartInstance->c81_g_tp_INACTIVE = 1U;
    chartInstance->c81_state_Jump = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 52U,
                 chartInstance->c81_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 52U, chartInstance->c81_sfEvent);
}

static void c81_SERVICE_CLOCK(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_c_out;
  boolean_T c81_temp;
  boolean_T c81_d_out;
  boolean_T c81_b_temp;
  boolean_T c81_e_out;
  *chartInstance->c81_state_InfoPrimary =
    chartInstance->c81_DISPLAY_SERVICE_CLOCK;
  *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 18U, chartInstance->c81_sfEvent);
  c81_out = (CV_TRANSITION_EVAL(18U, (int32_T)(_SFD_CCP_CALL(5U, 18U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 18U, 0, (real_T)
    chartInstance->c81_state_Jump, (real_T)chartInstance->c81_ACTIVE, 0, 0U,
    chartInstance->c81_state_Jump == chartInstance->c81_ACTIVE) != 0U,
    chartInstance->c81_sfEvent) != 0U)) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c81_sfEvent);
    c81_exit_internal_SERVICE_CLOCK(chartInstance);
    chartInstance->c81_tp_SERVICE_CLOCK = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 48U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_SERVICE_CLOCK_RESET;
    chartInstance->c81_was_ACTIVE = c81_IN_SERVICE_CLOCK_RESET;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 52U, chartInstance->c81_sfEvent);
    chartInstance->c81_temporalCounter_i2 = 0U;
    chartInstance->c81_tp_SERVICE_CLOCK_RESET = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_SERVICE_CLOCK_RESET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 9U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(9U, (int32_T)(_SFD_CCP_CALL(5U, 9U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 9U, 0, (real_T)
      *chartInstance->c81_state_InfoButton, (real_T)chartInstance->c81_ACTIVE, 0,
      0U, *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE) !=
      0U, chartInstance->c81_sfEvent) != 0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c81_sfEvent);
      c81_exit_internal_SERVICE_CLOCK(chartInstance);
      chartInstance->c81_tp_SERVICE_CLOCK = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 48U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_ACTIVE = c81_b_IN_ERROR_CODES;
      chartInstance->c81_was_ACTIVE = c81_b_IN_ERROR_CODES;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_ERROR_CODES = 1U;
      *chartInstance->c81_state_InfoPrimary =
        chartInstance->c81_DISPLAY_ERROR_CODES;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
      *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 48U,
                   chartInstance->c81_sfEvent);
      switch (chartInstance->c81_is_SERVICE_CLOCK) {
       case c81_IN_DEBOUNCE:
        CV_STATE_EVAL(48, 0, c81_IN_DEBOUNCE);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 25U,
                     chartInstance->c81_sfEvent);
        c81_c_out = (CV_TRANSITION_EVAL(25U, (int32_T)(_SFD_CCP_CALL(5U, 25U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 25U, 0, (real_T)
          chartInstance->c81_debounceCount, 70.0, 0, 5U,
          chartInstance->c81_debounceCount >= 70) != 0U,
          chartInstance->c81_sfEvent) != 0U)) != 0);
        if (c81_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 25U, chartInstance->c81_sfEvent);
          chartInstance->c81_d_tp_DEBOUNCE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 49U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_SERVICE_CLOCK = c81_IN_JUMP_STATE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 51U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_JUMP_STATE = 1U;
          chartInstance->c81_state_Jump = chartInstance->c81_ACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 26U,
                       chartInstance->c81_sfEvent);
          c81_d_out = (CV_TRANSITION_EVAL(26U, (int32_T)(_SFD_CCP_CALL(5U, 26U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 26U, 0, (real_T)
            ((*chartInstance->c81_msg_PanelButtonState)[0] &
             chartInstance->c81_INFO_BUTTON_MASK), (real_T)
            chartInstance->c81_INACTIVE, 0, 0U,
            ((*chartInstance->c81_msg_PanelButtonState)[0] &
             chartInstance->c81_INFO_BUTTON_MASK) == chartInstance->c81_INACTIVE)
            != 0U, chartInstance->c81_sfEvent) != 0U)) != 0);
          if (c81_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 26U, chartInstance->c81_sfEvent);
            chartInstance->c81_d_tp_DEBOUNCE = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 49U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_SERVICE_CLOCK = c81_c_IN_INACTIVE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 50U, chartInstance->c81_sfEvent);
            chartInstance->c81_g_tp_INACTIVE = 1U;
            chartInstance->c81_state_Jump = 0U;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 49U,
                         chartInstance->c81_sfEvent);
            chartInstance->c81_debounceCount = c81__u16_s32_(chartInstance,
              c81__s32_add__(chartInstance, (int32_T)
                             chartInstance->c81_debounceCount, 1, 20U, 34U, 15U),
              20U, 34U, 15U);
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
          }
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 49U, chartInstance->c81_sfEvent);
        break;

       case c81_c_IN_INACTIVE:
        CV_STATE_EVAL(48, 0, c81_c_IN_INACTIVE);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 23U,
                     chartInstance->c81_sfEvent);
        c81_temp = (_SFD_CCP_CALL(5U, 23U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          23U, 0, (real_T)((*chartInstance->c81_msg_PanelButtonState)[0] &
                           chartInstance->c81_INFO_BUTTON_MASK), (real_T)
          chartInstance->c81_INFO_BUTTON_PRESS, 0, 0U,
          ((*chartInstance->c81_msg_PanelButtonState)[0] &
           chartInstance->c81_INFO_BUTTON_MASK) ==
          chartInstance->c81_INFO_BUTTON_PRESS) != 0U,
          chartInstance->c81_sfEvent) != 0U);
        if (c81_temp) {
          c81_temp = (_SFD_CCP_CALL(5U, 23U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
            23U, 1, (real_T)*chartInstance->c81_state_ServiceClock, (real_T)
            chartInstance->c81_ACTIVE, 0, 0U,
            *chartInstance->c81_state_ServiceClock == chartInstance->c81_ACTIVE)
            != 0U, chartInstance->c81_sfEvent) != 0U);
        }

        c81_b_temp = c81_temp;
        if (c81_temp) {
          c81_b_temp = (_SFD_CCP_CALL(5U, 23U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 23U, 2, (real_T)*chartInstance->c81_state_InfoSecondary,
             (real_T)chartInstance->c81_INACTIVE, 0, 0U,
             *chartInstance->c81_state_InfoSecondary ==
             chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) !=
                        0U);
        }

        c81_e_out = (CV_TRANSITION_EVAL(23U, (int32_T)c81_b_temp) != 0);
        if (c81_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
          chartInstance->c81_g_tp_INACTIVE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 50U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_SERVICE_CLOCK = c81_IN_DEBOUNCE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 49U, chartInstance->c81_sfEvent);
          chartInstance->c81_d_tp_DEBOUNCE = 1U;
          chartInstance->c81_debounceCount = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCount, 2U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 50U,
                       chartInstance->c81_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 50U, chartInstance->c81_sfEvent);
        break;

       case c81_IN_JUMP_STATE:
        CV_STATE_EVAL(48, 0, c81_IN_JUMP_STATE);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 51U,
                     chartInstance->c81_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 51U, chartInstance->c81_sfEvent);
        break;

       default:
        CV_STATE_EVAL(48, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c81_is_SERVICE_CLOCK = c81_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 49U, chartInstance->c81_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 48U, chartInstance->c81_sfEvent);
}

static void c81_exit_internal_SERVICE_CLOCK(SFc81_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  switch (chartInstance->c81_is_SERVICE_CLOCK) {
   case c81_IN_DEBOUNCE:
    CV_STATE_EVAL(48, 1, c81_IN_DEBOUNCE);
    chartInstance->c81_d_tp_DEBOUNCE = 0U;
    chartInstance->c81_is_SERVICE_CLOCK = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 49U, chartInstance->c81_sfEvent);
    break;

   case c81_c_IN_INACTIVE:
    CV_STATE_EVAL(48, 1, c81_c_IN_INACTIVE);
    chartInstance->c81_g_tp_INACTIVE = 0U;
    chartInstance->c81_is_SERVICE_CLOCK = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 50U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_JUMP_STATE:
    CV_STATE_EVAL(48, 1, c81_IN_JUMP_STATE);
    chartInstance->c81_tp_JUMP_STATE = 0U;
    chartInstance->c81_is_SERVICE_CLOCK = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 51U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(48, 1, 0);
    chartInstance->c81_is_SERVICE_CLOCK = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 49U, chartInstance->c81_sfEvent);
    break;
  }
}

static void c81_ERROR_CODES(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_temp;
  boolean_T c81_out;
  boolean_T c81_b_out;
  *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_ERROR_CODES;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 52U, chartInstance->c81_sfEvent);
  c81_temp = (_SFD_CCP_CALL(5U, 52U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 52U, 0,
    (real_T)c81_get_ee_EngData(chartInstance, 0), 1.0, 0, 0U, c81_get_ee_EngData
    (chartInstance, 0) == 1) != 0U, chartInstance->c81_sfEvent) != 0U);
  if (c81_temp) {
    c81_temp = (_SFD_CCP_CALL(5U, 52U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 52U,
      1, (real_T)*chartInstance->c81_state_InfoButton, (real_T)
      chartInstance->c81_ACTIVE, 0, 0U, *chartInstance->c81_state_InfoButton ==
      chartInstance->c81_ACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
  }

  c81_out = (CV_TRANSITION_EVAL(52U, (int32_T)c81_temp) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 52U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_ERROR_CODES = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_EOP;
    chartInstance->c81_was_ACTIVE = c81_IN_EOP;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_EOP = 1U;
    *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_EOP;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 37U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(37U, (int32_T)(_SFD_CCP_CALL(5U, 37U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 37U, 0, (real_T)
      *chartInstance->c81_state_InfoButton, (real_T)chartInstance->c81_ACTIVE, 0,
      0U, *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE) !=
      0U, chartInstance->c81_sfEvent) != 0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 37U, chartInstance->c81_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_ERROR_CODES = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_ACTIVE = c81_IN_ENGINE_HOURS;
      chartInstance->c81_was_ACTIVE = c81_IN_ENGINE_HOURS;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_ENGINE_HOURS = 1U;
      *chartInstance->c81_state_InfoPrimary =
        chartInstance->c81_DISPLAY_ENGINE_HOURS;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
      *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
      *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 78U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_ENGINE_HOURS = c81_c_IN_INACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
      chartInstance->c81_d_tp_INACTIVE = 1U;
      chartInstance->c81_state_Jump = 0U;
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 33U,
                   chartInstance->c81_sfEvent);
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 33U, chartInstance->c81_sfEvent);
}

static void c81_HOT2(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_out;
  *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_HOT;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 38U, chartInstance->c81_sfEvent);
  c81_out = (CV_TRANSITION_EVAL(38U, (int32_T)(_SFD_CCP_CALL(5U, 38U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 38U, 0, (real_T)
    *chartInstance->c81_state_InfoButton, (real_T)chartInstance->c81_ACTIVE, 0,
    0U, *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE) != 0U,
    chartInstance->c81_sfEvent) != 0U)) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 38U, chartInstance->c81_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 53U, chartInstance->c81_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_HOT2 = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 37U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ACTIVE = c81_IN_ENGINE_HOURS;
    chartInstance->c81_was_ACTIVE = c81_IN_ENGINE_HOURS;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_ENGINE_HOURS = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_ENGINE_HOURS;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
    *chartInstance->c81_enable_RightLeft = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_enable_RightLeft, 33U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 78U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_ENGINE_HOURS = c81_c_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c81_sfEvent);
    chartInstance->c81_d_tp_INACTIVE = 1U;
    chartInstance->c81_state_Jump = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_state_Jump, 9U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 37U,
                 chartInstance->c81_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 37U, chartInstance->c81_sfEvent);
}

static void c81_SECOND_AUX(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_temp;
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_c_out;
  boolean_T guard1 = false;
  *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_SECOND_AUX;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 100U,
               chartInstance->c81_sfEvent);
  c81_temp = (_SFD_CCP_CALL(5U, 100U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 100U,
    0, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
    chartInstance->c81_INACTIVE, 0, 1U, *chartInstance->c81_state_InfoSecondary
    != chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
  if (c81_temp) {
    c81_temp = (_SFD_CCP_CALL(5U, 100U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
      100U, 1, (real_T)*chartInstance->c81_state_InfoSecondary, (real_T)
      chartInstance->c81_prev_InfoSecondary, 0, 1U,
      *chartInstance->c81_state_InfoSecondary !=
      chartInstance->c81_prev_InfoSecondary) != 0U, chartInstance->c81_sfEvent)
                != 0U);
  }

  c81_out = (CV_TRANSITION_EVAL(100U, (int32_T)c81_temp) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 100U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_SECOND_AUX = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 56U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_PRIMARY_STATE = c81_b_IN_INACTIVE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 55U, chartInstance->c81_sfEvent);
    chartInstance->c81_h_tp_INACTIVE = 1U;
    *chartInstance->c81_state_InfoPrimary =
      chartInstance->c81_DISPLAY_PRIMARY_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
    chartInstance->c81_prev_InfoSecondary =
      *chartInstance->c81_state_InfoSecondary;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_InfoSecondary, 5U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 101U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(101U, (int32_T)(_SFD_CCP_CALL(5U, 101U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 101U, 0, (real_T)
      *chartInstance->c81_state_InfoButton, (real_T)chartInstance->c81_ACTIVE, 0,
      0U, *chartInstance->c81_state_InfoButton == chartInstance->c81_ACTIVE) !=
      0U, chartInstance->c81_sfEvent) != 0U)) != 0);
    guard1 = false;
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 101U, chartInstance->c81_sfEvent);
      guard1 = true;
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 103U,
                   chartInstance->c81_sfEvent);
      c81_c_out = (CV_TRANSITION_EVAL(103U, (int32_T)(_SFD_CCP_CALL(5U, 103U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 103U, 0, (real_T)
        *chartInstance->c81_cmd_SecondAux, (real_T)chartInstance->c81_INACTIVE,
        0, 0U, (int32_T)*chartInstance->c81_cmd_SecondAux ==
        chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U))
                   != 0);
      if (c81_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 103U, chartInstance->c81_sfEvent);
        chartInstance->c81_prev_SecondAux = (chartInstance->c81_INACTIVE != 0);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_prev_SecondAux, 6U);
        guard1 = true;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 56U,
                     chartInstance->c81_sfEvent);
      }
    }

    if (guard1) {
      chartInstance->c81_tp_SECOND_AUX = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 56U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_PRIMARY_STATE = c81_IN_ACTIVE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c81_sfEvent);
      chartInstance->c81_temporalCounter_i1 = 0U;
      chartInstance->c81_d_tp_ACTIVE = 1U;
      c81_enter_internal_ACTIVE(chartInstance);
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 56U, chartInstance->c81_sfEvent);
}

static void c81_enter_atomic_ERROR_CODES(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  *chartInstance->c81_state_InfoPrimary = chartInstance->c81_DISPLAY_ERROR_CODES;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoPrimary, 28U);
  *chartInstance->c81_state_InfoButton = chartInstance->c81_INACTIVE;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoButton, 29U);
  chartInstance->c81_debounceCode = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_debounceCode, 1U);
}

static void c81_SECONDARY_STATE(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_c_out;
  boolean_T c81_d_out;
  boolean_T c81_temp;
  boolean_T c81_e_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 57U, chartInstance->c81_sfEvent);
  switch (chartInstance->c81_is_SECONDARY_STATE) {
   case c81_IN_DELUXE_ERROR:
    CV_STATE_EVAL(57, 0, c81_IN_DELUXE_ERROR);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                 chartInstance->c81_sfEvent);
    c81_out = (CV_TRANSITION_EVAL(15U, (int32_T)(_SFD_CCP_CALL(5U, 15U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 15U, 0, (real_T)
      *chartInstance->c81_state_KeylessPanel, (real_T)
      chartInstance->c81_NO_COMMUNICATION, 0, 1U,
      *chartInstance->c81_state_KeylessPanel !=
      chartInstance->c81_NO_COMMUNICATION) != 0U, chartInstance->c81_sfEvent) !=
      0U)) != 0);
    if (c81_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_DELUXE_ERROR = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 58U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_SECONDARY_STATE = c81_IN_DELUXE_GOOD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 59U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_DELUXE_GOOD = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_DELUXE_GOOD = c81_IN_NON_SHUTDOWN;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_NON_SHUTDOWN = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_NO_STATE = 1U;
      *chartInstance->c81_state_InfoSecondary = chartInstance->c81_INACTIVE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary, 30U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 58U,
                   chartInstance->c81_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 58U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_DELUXE_GOOD:
    CV_STATE_EVAL(57, 0, c81_IN_DELUXE_GOOD);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 20U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(20U, (int32_T)(_SFD_CCP_CALL(5U, 20U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 20U, 0, (real_T)
      *chartInstance->c81_state_KeylessPanel, (real_T)
      chartInstance->c81_NO_COMMUNICATION, 0, 0U,
      *chartInstance->c81_state_KeylessPanel ==
      chartInstance->c81_NO_COMMUNICATION) != 0U, chartInstance->c81_sfEvent) !=
      0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c81_sfEvent);
      c81_exit_internal_DELUXE_GOOD(chartInstance);
      chartInstance->c81_tp_DELUXE_GOOD = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 59U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_SECONDARY_STATE = c81_IN_DELUXE_ERROR;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 58U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_DELUXE_ERROR = 1U;
      *chartInstance->c81_state_InfoSecondary =
        chartInstance->c81_DISPLAY_DELUXE_ERROR;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary, 30U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 59U,
                   chartInstance->c81_sfEvent);
      switch (chartInstance->c81_is_DELUXE_GOOD) {
       case c81_IN_KSS:
        CV_STATE_EVAL(59, 0, c81_IN_KSS);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 96U,
                     chartInstance->c81_sfEvent);
        c81_c_out = (CV_TRANSITION_EVAL(96U, (int32_T)(_SFD_CCP_CALL(5U, 96U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 96U, 0, (real_T)
          *chartInstance->c81_KSSDisplayState, (real_T)
          chartInstance->c81_INACTIVE, 0, 0U,
          *chartInstance->c81_KSSDisplayState == chartInstance->c81_INACTIVE) !=
          0U, chartInstance->c81_sfEvent) != 0U)) != 0);
        if (c81_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 96U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_KSS = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 60U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_DELUXE_GOOD = c81_IN_NON_SHUTDOWN;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_NON_SHUTDOWN = 1U;
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_NO_STATE = 1U;
          *chartInstance->c81_state_InfoSecondary = chartInstance->c81_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary,
                                30U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 60U,
                       chartInstance->c81_sfEvent);
          *chartInstance->c81_state_InfoSecondary =
            *chartInstance->c81_KSSDisplayState;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary,
                                30U);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 60U, chartInstance->c81_sfEvent);
        break;

       case c81_IN_NON_SHUTDOWN:
        CV_STATE_EVAL(59, 0, c81_IN_NON_SHUTDOWN);
        c81_NON_SHUTDOWN(chartInstance);
        break;

       case c81_IN_SHUTDOWN:
        CV_STATE_EVAL(59, 0, c81_IN_SHUTDOWN);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                     chartInstance->c81_sfEvent);
        c81_d_out = (CV_TRANSITION_EVAL(1U, (int32_T)(_SFD_CCP_CALL(5U, 1U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 1U, 0, (real_T)
          chartInstance->c81_shutdownTimer, (real_T)
          chartInstance->c81_CD_DISPLAY_SHUTDOWN_TIME, 0, 5U,
          chartInstance->c81_shutdownTimer >=
          chartInstance->c81_CD_DISPLAY_SHUTDOWN_TIME) != 0U,
          chartInstance->c81_sfEvent) != 0U)) != 0);
        if (c81_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_SHUTDOWN = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 72U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_DELUXE_GOOD = c81_IN_NON_SHUTDOWN;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_NON_SHUTDOWN = 1U;
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_NO_STATE = 1U;
          *chartInstance->c81_state_InfoSecondary = chartInstance->c81_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary,
                                30U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 72U,
                       chartInstance->c81_sfEvent);
          chartInstance->c81_shutdownTimer = c81__u16_s32_(chartInstance,
            c81__s32_add__(chartInstance, (int32_T)
                           chartInstance->c81_shutdownTimer, 1, 2U, 77U, 15U),
            2U, 77U, 15U);
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_shutdownTimer, 8U);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 72U, chartInstance->c81_sfEvent);
        break;

       case c81_IN_VERSION:
        CV_STATE_EVAL(59, 0, c81_IN_VERSION);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 33U,
                     chartInstance->c81_sfEvent);
        c81_temp = (_SFD_CCP_CALL(5U, 33U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          33U, 0, (real_T)*chartInstance->c81_state_Engine, (real_T)
          chartInstance->c81_SHUTDOWN, 0, 0U, *chartInstance->c81_state_Engine ==
          chartInstance->c81_SHUTDOWN) != 0U, chartInstance->c81_sfEvent) != 0U);
        if (!c81_temp) {
          c81_temp = (_SFD_CCP_CALL(5U, 33U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
            33U, 1, (real_T)chartInstance->c81_state_LightButton, (real_T)
            chartInstance->c81_ACTIVE, 0, 1U,
            chartInstance->c81_state_LightButton != chartInstance->c81_ACTIVE)
            != 0U, chartInstance->c81_sfEvent) != 0U);
        }

        c81_e_out = (CV_TRANSITION_EVAL(33U, (int32_T)c81_temp) != 0);
        if (c81_e_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 33U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_VERSION = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 73U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_DELUXE_GOOD = c81_IN_NON_SHUTDOWN;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_NON_SHUTDOWN = 1U;
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_NO_STATE = 1U;
          *chartInstance->c81_state_InfoSecondary = chartInstance->c81_INACTIVE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary,
                                30U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 73U,
                       chartInstance->c81_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 73U, chartInstance->c81_sfEvent);
        break;

       default:
        CV_STATE_EVAL(59, 0, 0);

        /* Unreachable state, for coverage only */
        chartInstance->c81_is_DELUXE_GOOD = c81_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 60U, chartInstance->c81_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 59U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(57, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c81_is_SECONDARY_STATE = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 58U, chartInstance->c81_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 57U, chartInstance->c81_sfEvent);
}

static void c81_exit_internal_DELUXE_GOOD(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c81_is_DELUXE_GOOD) {
   case c81_IN_KSS:
    CV_STATE_EVAL(59, 1, c81_IN_KSS);
    chartInstance->c81_tp_KSS = 0U;
    chartInstance->c81_is_DELUXE_GOOD = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 60U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_NON_SHUTDOWN:
    CV_STATE_EVAL(59, 1, c81_IN_NON_SHUTDOWN);
    c81_exit_internal_NON_SHUTDOWN(chartInstance);
    chartInstance->c81_tp_NON_SHUTDOWN = 0U;
    chartInstance->c81_is_DELUXE_GOOD = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_SHUTDOWN:
    CV_STATE_EVAL(59, 1, c81_IN_SHUTDOWN);
    chartInstance->c81_tp_SHUTDOWN = 0U;
    chartInstance->c81_is_DELUXE_GOOD = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 72U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_VERSION:
    CV_STATE_EVAL(59, 1, c81_IN_VERSION);
    chartInstance->c81_tp_VERSION = 0U;
    chartInstance->c81_is_DELUXE_GOOD = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 73U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(59, 1, 0);
    chartInstance->c81_is_DELUXE_GOOD = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 60U, chartInstance->c81_sfEvent);
    break;
  }
}

static void c81_NON_SHUTDOWN(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_temp;
  boolean_T c81_b_temp;
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_c_out;
  uint16_T c81_u1;
  boolean_T c81_d_out;
  boolean_T c81_e_out;
  boolean_T c81_c_temp;
  uint16_T c81_u2;
  boolean_T c81_f_out;
  boolean_T c81_d_temp;
  boolean_T c81_g_out;
  boolean_T c81_e_temp;
  boolean_T c81_h_out;
  boolean_T c81_i_out;
  boolean_T c81_j_out;
  uint16_T c81_u3;
  uint16_T c81_u4;
  boolean_T c81_k_out;
  boolean_T c81_l_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U, chartInstance->c81_sfEvent);
  c81_temp = (_SFD_CCP_CALL(5U, 10U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 10U, 0,
    (real_T)*chartInstance->c81_state_Engine, (real_T)
    chartInstance->c81_SHUTDOWN, 0, 0U, *chartInstance->c81_state_Engine ==
    chartInstance->c81_SHUTDOWN) != 0U, chartInstance->c81_sfEvent) != 0U);
  if (c81_temp) {
    c81_temp = (_SFD_CCP_CALL(5U, 10U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 10U,
      1, (real_T)chartInstance->c81_shutdownTimer, 0.0, 0, 0U,
      chartInstance->c81_shutdownTimer == 0) != 0U, chartInstance->c81_sfEvent)
                != 0U);
  }

  c81_b_temp = c81_temp;
  if (c81_temp) {
    c81_b_temp = (_SFD_CCP_CALL(5U, 10U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
      10U, 2, (real_T)*chartInstance->c81_state_Key, (real_T)
      chartInstance->c81_MULTIPLE, 0, 1U, *chartInstance->c81_state_Key !=
      chartInstance->c81_MULTIPLE) != 0U, chartInstance->c81_sfEvent) != 0U);
  }

  c81_out = (CV_TRANSITION_EVAL(10U, (int32_T)c81_b_temp) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c81_sfEvent);
    c81_exit_internal_NON_SHUTDOWN(chartInstance);
    chartInstance->c81_tp_NON_SHUTDOWN = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_DELUXE_GOOD = c81_IN_SHUTDOWN;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 72U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_SHUTDOWN = 1U;
    *chartInstance->c81_state_InfoSecondary =
      chartInstance->c81_DISPLAY_SHUTDOWN;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary, 30U);
    chartInstance->c81_shutdownTimer = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_shutdownTimer, 8U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 32U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(32U, (int32_T)(_SFD_CCP_CALL(5U, 32U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 32U, 0, (real_T)
      chartInstance->c81_state_LightButton, (real_T)chartInstance->c81_ACTIVE, 0,
      0U, chartInstance->c81_state_LightButton == chartInstance->c81_ACTIVE) !=
      0U, chartInstance->c81_sfEvent) != 0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 32U, chartInstance->c81_sfEvent);
      c81_exit_internal_NON_SHUTDOWN(chartInstance);
      chartInstance->c81_tp_NON_SHUTDOWN = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_DELUXE_GOOD = c81_IN_VERSION;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 73U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_VERSION = 1U;
      *chartInstance->c81_state_InfoSecondary =
        chartInstance->c81_DISPLAY_VERSION;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary, 30U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 95U,
                   chartInstance->c81_sfEvent);
      c81_c_out = (CV_TRANSITION_EVAL(95U, (int32_T)(_SFD_CCP_CALL(5U, 95U, 0,
        (boolean_T)CV_RELATIONAL_EVAL(5U, 95U, 0, (real_T)
        *chartInstance->c81_KSSDisplayState, (real_T)chartInstance->c81_INACTIVE,
        0, 1U, *chartInstance->c81_KSSDisplayState !=
        chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U))
                   != 0);
      if (c81_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 95U, chartInstance->c81_sfEvent);
        c81_exit_internal_NON_SHUTDOWN(chartInstance);
        chartInstance->c81_tp_NON_SHUTDOWN = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 61U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_DELUXE_GOOD = c81_IN_KSS;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 60U, chartInstance->c81_sfEvent);
        chartInstance->c81_tp_KSS = 1U;
        *chartInstance->c81_state_InfoSecondary =
          *chartInstance->c81_KSSDisplayState;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary,
                              30U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 61U,
                     chartInstance->c81_sfEvent);
        switch (chartInstance->c81_is_NON_SHUTDOWN) {
         case c81_IN_Aux_Detent_Error:
          CV_STATE_EVAL(61, 0, c81_IN_Aux_Detent_Error);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 69U,
                       chartInstance->c81_sfEvent);
          c81_u1 = c81__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
            ((uint32_T)chartInstance->c81_CD_AUX_DETENT_FLASH_TIME, 16U, 69U),
            848U, 1U, 5U);
          c81_d_temp = (_SFD_CCP_CALL(5U, 69U, 0,
            (chartInstance->c81_temporalCounter_i3 >= c81_u1) != 0U,
            chartInstance->c81_sfEvent) != 0U);
          if (!c81_d_temp) {
            c81_d_temp = (_SFD_CCP_CALL(5U, 69U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 69U, 0, (real_T)
                                 *chartInstance->c81_state_DetentEnable, (real_T)
                                 chartInstance->c81_ACTIVE, 0, 0U,
                                 *chartInstance->c81_state_DetentEnable ==
                                 chartInstance->c81_ACTIVE) != 0U,
              chartInstance->c81_sfEvent) != 0U);
          }

          c81_j_out = (CV_TRANSITION_EVAL(69U, (int32_T)c81_d_temp) != 0);
          if (c81_j_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 69U, chartInstance->c81_sfEvent);
            c81_exit_internal_Aux_Detent_Error(chartInstance);
            chartInstance->c81_tp_Aux_Detent_Error = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 62U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_NO_STATE = 1U;
            *chartInstance->c81_state_InfoSecondary =
              chartInstance->c81_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c81_state_InfoSecondary, 30U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 62U,
                         chartInstance->c81_sfEvent);
            switch (chartInstance->c81_is_Aux_Detent_Error) {
             case c81_IN_AUX:
              CV_STATE_EVAL(62, 0, c81_IN_AUX);
              _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 72U,
                           chartInstance->c81_sfEvent);
              c81_u3 = c81__u16_u32_(chartInstance,
                _SFD_TRANS_TEMPORAL_THRESHOLD((uint32_T)
                chartInstance->c81_CD_AUX_DETENT_CYCLE_TIME, 16U, 72U), 851U, 1U,
                5U);
              c81_k_out = (CV_TRANSITION_EVAL(72U, (int32_T)(_SFD_CCP_CALL(5U,
                72U, 0, (chartInstance->c81_temporalCounter_i4 >= c81_u3) != 0U,
                chartInstance->c81_sfEvent) != 0U)) != 0);
              if (c81_k_out) {
                _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 72U,
                             chartInstance->c81_sfEvent);
                chartInstance->c81_tp_AUX = 0U;
                _SFD_CS_CALL(STATE_INACTIVE_TAG, 63U, chartInstance->c81_sfEvent);
                chartInstance->c81_is_Aux_Detent_Error = c81_IN_HOLD;
                _SFD_CS_CALL(STATE_ACTIVE_TAG, 64U, chartInstance->c81_sfEvent);
                chartInstance->c81_temporalCounter_i4 = 0U;
                chartInstance->c81_tp_HOLD = 1U;
                *chartInstance->c81_state_InfoSecondary =
                  chartInstance->c81_DISPLAY_HOLD;
                _SFD_DATA_RANGE_CHECK((real_T)
                                      *chartInstance->c81_state_InfoSecondary,
                                      30U);
              } else {
                _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 63U,
                             chartInstance->c81_sfEvent);
              }

              _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 63U,
                           chartInstance->c81_sfEvent);
              break;

             case c81_IN_HOLD:
              CV_STATE_EVAL(62, 0, c81_IN_HOLD);
              _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 71U,
                           chartInstance->c81_sfEvent);
              c81_u4 = c81__u16_u32_(chartInstance,
                _SFD_TRANS_TEMPORAL_THRESHOLD((uint32_T)
                chartInstance->c81_CD_AUX_DETENT_CYCLE_TIME, 16U, 71U), 850U, 1U,
                5U);
              c81_l_out = (CV_TRANSITION_EVAL(71U, (int32_T)(_SFD_CCP_CALL(5U,
                71U, 0, (chartInstance->c81_temporalCounter_i4 >= c81_u4) != 0U,
                chartInstance->c81_sfEvent) != 0U)) != 0);
              if (c81_l_out) {
                _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 71U,
                             chartInstance->c81_sfEvent);
                chartInstance->c81_tp_HOLD = 0U;
                _SFD_CS_CALL(STATE_INACTIVE_TAG, 64U, chartInstance->c81_sfEvent);
                chartInstance->c81_is_Aux_Detent_Error = c81_IN_AUX;
                _SFD_CS_CALL(STATE_ACTIVE_TAG, 63U, chartInstance->c81_sfEvent);
                chartInstance->c81_temporalCounter_i4 = 0U;
                chartInstance->c81_tp_AUX = 1U;
                *chartInstance->c81_state_InfoSecondary =
                  chartInstance->c81_DISPLAY_AUX;
                _SFD_DATA_RANGE_CHECK((real_T)
                                      *chartInstance->c81_state_InfoSecondary,
                                      30U);
              } else {
                _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 64U,
                             chartInstance->c81_sfEvent);
              }

              _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 64U,
                           chartInstance->c81_sfEvent);
              break;

             default:
              CV_STATE_EVAL(62, 0, 0);

              /* Unreachable state, for coverage only */
              chartInstance->c81_is_Aux_Detent_Error = c81_IN_NO_ACTIVE_CHILD;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 63U, chartInstance->c81_sfEvent);
              break;
            }
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 62U, chartInstance->c81_sfEvent);
          break;

         case c81_IN_COLD:
          CV_STATE_EVAL(61, 0, c81_IN_COLD);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 88U,
                       chartInstance->c81_sfEvent);
          c81_d_out = (CV_TRANSITION_EVAL(88U, (int32_T)(_SFD_CCP_CALL(5U, 88U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 88U, 0, (real_T)
            *chartInstance->c81_state_TC, (real_T)chartInstance->c81_NORMAL, 0,
            0U, *chartInstance->c81_state_TC == chartInstance->c81_NORMAL) != 0U,
            chartInstance->c81_sfEvent) != 0U)) != 0);
          if (c81_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 88U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_COLD = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 65U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_NO_STATE = 1U;
            *chartInstance->c81_state_InfoSecondary =
              chartInstance->c81_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c81_state_InfoSecondary, 30U);
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 90U,
                         chartInstance->c81_sfEvent);
            c81_h_out = (CV_TRANSITION_EVAL(90U, (int32_T)(_SFD_CCP_CALL(5U, 90U,
              0, (boolean_T)CV_RELATIONAL_EVAL(5U, 90U, 0, (real_T)
              *chartInstance->c81_state_TC, (real_T)chartInstance->c81_EVENT, 0,
              0U, *chartInstance->c81_state_TC == chartInstance->c81_EVENT) !=
              0U, chartInstance->c81_sfEvent) != 0U)) != 0);
            if (c81_h_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 90U,
                           chartInstance->c81_sfEvent);
              chartInstance->c81_tp_COLD = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 65U, chartInstance->c81_sfEvent);
              chartInstance->c81_is_NON_SHUTDOWN = c81_IN_FLASH_COLD;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 66U, chartInstance->c81_sfEvent);
              chartInstance->c81_tp_FLASH_COLD = 1U;
              *chartInstance->c81_state_InfoSecondary =
                chartInstance->c81_DISPLAY_FLASH_COLD;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c81_state_InfoSecondary, 30U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 65U,
                           chartInstance->c81_sfEvent);
            }
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 65U, chartInstance->c81_sfEvent);
          break;

         case c81_IN_FLASH_COLD:
          CV_STATE_EVAL(61, 0, c81_IN_FLASH_COLD);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 91U,
                       chartInstance->c81_sfEvent);
          c81_e_out = (CV_TRANSITION_EVAL(91U, (int32_T)(_SFD_CCP_CALL(5U, 91U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 91U, 0, (real_T)
            *chartInstance->c81_state_TC, (real_T)chartInstance->c81_EVENT, 0,
            1U, *chartInstance->c81_state_TC != chartInstance->c81_EVENT) != 0U,
            chartInstance->c81_sfEvent) != 0U)) != 0);
          if (c81_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 91U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_FLASH_COLD = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 66U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_NON_SHUTDOWN = c81_IN_COLD;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 65U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_COLD = 1U;
            *chartInstance->c81_state_InfoSecondary =
              chartInstance->c81_DISPLAY_COLD;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c81_state_InfoSecondary, 30U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 66U,
                         chartInstance->c81_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 66U, chartInstance->c81_sfEvent);
          break;

         case c81_IN_GLOW_PLUGS:
          CV_STATE_EVAL(61, 0, c81_IN_GLOW_PLUGS);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                       chartInstance->c81_sfEvent);
          c81_c_temp = (_SFD_CCP_CALL(5U, 8U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 8U, 0, (real_T)*chartInstance->c81_count_GlowPlug, 0.0, 0, 0U, *
             chartInstance->c81_count_GlowPlug == 0) != 0U,
            chartInstance->c81_sfEvent) != 0U);
          if (!c81_c_temp) {
            c81_e_temp = (_SFD_CCP_CALL(5U, 8U, 1, (boolean_T)CV_RELATIONAL_EVAL
              (5U, 8U, 1, (real_T)*chartInstance->c81_state_CANThrottleCalDiag,
               (real_T)chartInstance->c81_INACTIVE, 0, 1U,
               *chartInstance->c81_state_CANThrottleCalDiag !=
               chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent)
                          != 0U);
            if (c81_e_temp) {
              c81_e_temp = (_SFD_CCP_CALL(5U, 8U, 2, (boolean_T)
                CV_RELATIONAL_EVAL(5U, 8U, 2, (real_T)
                                   *chartInstance->c81_state_InfoPrimary,
                                   (real_T)
                                   chartInstance->c81_DISPLAY_ENGINE_HOURS, 0,
                                   0U, *chartInstance->c81_state_InfoPrimary ==
                                   chartInstance->c81_DISPLAY_ENGINE_HOURS) !=
                0U, chartInstance->c81_sfEvent) != 0U);
            }

            c81_c_temp = c81_e_temp;
          }

          c81_i_out = (CV_TRANSITION_EVAL(8U, (int32_T)c81_c_temp) != 0);
          if (c81_i_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_GLOW_PLUGS = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 67U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_NO_STATE = 1U;
            *chartInstance->c81_state_InfoSecondary =
              chartInstance->c81_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c81_state_InfoSecondary, 30U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 67U,
                         chartInstance->c81_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 67U, chartInstance->c81_sfEvent);
          break;

         case c81_IN_NO_STATE:
          CV_STATE_EVAL(61, 0, c81_IN_NO_STATE);
          c81_NO_STATE(chartInstance);
          break;

         case c81_IN_OFFSET:
          CV_STATE_EVAL(61, 0, c81_IN_OFFSET);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 98U,
                       chartInstance->c81_sfEvent);
          c81_u2 = c81__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
            ((uint32_T)chartInstance->c81_CD_SECOND_AUX_OFFSET_DISP_TIME, 16U,
             98U), 942U, 1U, 5U);
          c81_g_out = (CV_TRANSITION_EVAL(98U, (int32_T)(_SFD_CCP_CALL(5U, 98U,
            0, (chartInstance->c81_temporalCounter_i3 >= c81_u2) != 0U,
            chartInstance->c81_sfEvent) != 0U)) != 0);
          if (c81_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 98U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_OFFSET = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 69U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_NO_STATE = 1U;
            *chartInstance->c81_state_InfoSecondary =
              chartInstance->c81_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c81_state_InfoSecondary, 30U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 69U,
                         chartInstance->c81_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 69U, chartInstance->c81_sfEvent);
          break;

         case c81_IN_SERVICE_CLOCK_ALARM:
          CV_STATE_EVAL(61, 0, c81_IN_SERVICE_CLOCK_ALARM);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U,
                       chartInstance->c81_sfEvent);
          c81_f_out = (CV_TRANSITION_EVAL(0U, (int32_T)(_SFD_CCP_CALL(5U, 0U, 0,
            (boolean_T)CV_RELATIONAL_EVAL(5U, 0U, 0, (real_T)
            chartInstance->c81_serviceClockAlarmTimer, (real_T)
            chartInstance->c81_CD_DISPLAY_SERVICE_CLOCK_ALARM_TIME, 0, 5U,
            chartInstance->c81_serviceClockAlarmTimer >=
            chartInstance->c81_CD_DISPLAY_SERVICE_CLOCK_ALARM_TIME) != 0U,
            chartInstance->c81_sfEvent) != 0U)) != 0);
          if (c81_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_SERVICE_CLOCK_ALARM = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 70U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_NO_STATE = 1U;
            *chartInstance->c81_state_InfoSecondary =
              chartInstance->c81_INACTIVE;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c81_state_InfoSecondary, 30U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 70U,
                         chartInstance->c81_sfEvent);
            chartInstance->c81_serviceClockAlarmTimer = c81__u16_s32_
              (chartInstance, c81__s32_add__(chartInstance, (int32_T)
                chartInstance->c81_serviceClockAlarmTimer, 1, 7U, 108U, 24U), 7U,
               108U, 24U);
            _SFD_DATA_RANGE_CHECK((real_T)
                                  chartInstance->c81_serviceClockAlarmTimer, 7U);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 70U, chartInstance->c81_sfEvent);
          break;

         case c81_IN_THROTTLE_CAL_DIAGNOSTICS:
          CV_STATE_EVAL(61, 0, c81_IN_THROTTLE_CAL_DIAGNOSTICS);
          c81_THROTTLE_CAL_DIAGNOSTICS(chartInstance);
          break;

         default:
          CV_STATE_EVAL(61, 0, 0);

          /* Unreachable state, for coverage only */
          chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 62U, chartInstance->c81_sfEvent);
          break;
        }
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 61U, chartInstance->c81_sfEvent);
}

static void c81_exit_internal_NON_SHUTDOWN(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c81_is_NON_SHUTDOWN) {
   case c81_IN_Aux_Detent_Error:
    CV_STATE_EVAL(61, 1, c81_IN_Aux_Detent_Error);
    c81_exit_internal_Aux_Detent_Error(chartInstance);
    chartInstance->c81_tp_Aux_Detent_Error = 0U;
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 62U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_COLD:
    CV_STATE_EVAL(61, 1, c81_IN_COLD);
    chartInstance->c81_tp_COLD = 0U;
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 65U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_FLASH_COLD:
    CV_STATE_EVAL(61, 1, c81_IN_FLASH_COLD);
    chartInstance->c81_tp_FLASH_COLD = 0U;
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 66U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_GLOW_PLUGS:
    CV_STATE_EVAL(61, 1, c81_IN_GLOW_PLUGS);
    chartInstance->c81_tp_GLOW_PLUGS = 0U;
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 67U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_NO_STATE:
    CV_STATE_EVAL(61, 1, c81_IN_NO_STATE);
    chartInstance->c81_tp_NO_STATE = 0U;
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_OFFSET:
    CV_STATE_EVAL(61, 1, c81_IN_OFFSET);
    chartInstance->c81_tp_OFFSET = 0U;
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 69U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_SERVICE_CLOCK_ALARM:
    CV_STATE_EVAL(61, 1, c81_IN_SERVICE_CLOCK_ALARM);
    chartInstance->c81_tp_SERVICE_CLOCK_ALARM = 0U;
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 70U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_THROTTLE_CAL_DIAGNOSTICS:
    CV_STATE_EVAL(61, 1, c81_IN_THROTTLE_CAL_DIAGNOSTICS);
    chartInstance->c81_tp_THROTTLE_CAL_DIAGNOSTICS = 0U;
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 71U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(61, 1, 0);
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 62U, chartInstance->c81_sfEvent);
    break;
  }
}

static void c81_NO_STATE(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c81_temp;
  boolean_T c81_out;
  boolean_T c81_b_out;
  boolean_T c81_b_temp;
  boolean_T c81_c_temp;
  boolean_T c81_c_out;
  boolean_T c81_d_temp;
  boolean_T c81_e_temp;
  boolean_T c81_d_out;
  boolean_T c81_f_temp;
  boolean_T c81_e_out;
  boolean_T c81_g_temp;
  boolean_T c81_f_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 89U, chartInstance->c81_sfEvent);
  c81_temp = (_SFD_CCP_CALL(5U, 89U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 89U, 0,
    (real_T)*chartInstance->c81_state_TC, (real_T)chartInstance->c81_LOW, 0, 0U,
    *chartInstance->c81_state_TC == chartInstance->c81_LOW) != 0U,
    chartInstance->c81_sfEvent) != 0U);
  if (!c81_temp) {
    c81_temp = (_SFD_CCP_CALL(5U, 89U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 89U,
      1, (real_T)*chartInstance->c81_state_TC, (real_T)
      chartInstance->c81_EXTREMELY_LOW, 0, 0U, *chartInstance->c81_state_TC ==
      chartInstance->c81_EXTREMELY_LOW) != 0U, chartInstance->c81_sfEvent) != 0U);
  }

  c81_out = (CV_TRANSITION_EVAL(89U, (int32_T)c81_temp) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 89U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_NO_STATE = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_COLD;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 65U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_COLD = 1U;
    *chartInstance->c81_state_InfoSecondary = chartInstance->c81_DISPLAY_COLD;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary, 30U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                 chartInstance->c81_sfEvent);
    c81_b_out = (CV_TRANSITION_EVAL(7U, (int32_T)(_SFD_CCP_CALL(5U, 7U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 7U, 0, (real_T)
      *chartInstance->c81_count_GlowPlug, 0.0, 0, 4U,
      *chartInstance->c81_count_GlowPlug > 0) != 0U, chartInstance->c81_sfEvent)
      != 0U)) != 0);
    if (c81_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_NO_STATE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
      chartInstance->c81_is_NON_SHUTDOWN = c81_IN_GLOW_PLUGS;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 67U, chartInstance->c81_sfEvent);
      chartInstance->c81_tp_GLOW_PLUGS = 1U;
      *chartInstance->c81_state_InfoSecondary =
        chartInstance->c81_DISPLAY_GLOW_PLUGS;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary, 30U);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U,
                   chartInstance->c81_sfEvent);
      c81_b_temp = (_SFD_CCP_CALL(5U, 6U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        6U, 0, (real_T)*chartInstance->c81_state_ServiceClock, (real_T)
        chartInstance->c81_ACTIVE, 0, 0U, *chartInstance->c81_state_ServiceClock
        == chartInstance->c81_ACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
      if (c81_b_temp) {
        c81_b_temp = (_SFD_CCP_CALL(5U, 6U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          6U, 1, (real_T)chartInstance->c81_serviceClockAlarmTimer, 0.0, 0, 0U,
          chartInstance->c81_serviceClockAlarmTimer == 0) != 0U,
          chartInstance->c81_sfEvent) != 0U);
      }

      c81_c_temp = c81_b_temp;
      if (c81_b_temp) {
        c81_c_temp = (_SFD_CCP_CALL(5U, 6U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
          6U, 2, (real_T)*chartInstance->c81_state_MachineLock, (real_T)
          chartInstance->c81_ACTIVE, 0, 1U,
          *chartInstance->c81_state_MachineLock != chartInstance->c81_ACTIVE) !=
          0U, chartInstance->c81_sfEvent) != 0U);
      }

      c81_c_out = (CV_TRANSITION_EVAL(6U, (int32_T)c81_c_temp) != 0);
      if (c81_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c81_sfEvent);
        chartInstance->c81_tp_NO_STATE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
        chartInstance->c81_is_NON_SHUTDOWN = c81_IN_SERVICE_CLOCK_ALARM;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 70U, chartInstance->c81_sfEvent);
        chartInstance->c81_tp_SERVICE_CLOCK_ALARM = 1U;
        *chartInstance->c81_state_InfoSecondary =
          chartInstance->c81_DISPLAY_SERVICE_CLOCK_ALARM;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary,
                              30U);
        chartInstance->c81_serviceClockAlarmTimer = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c81_serviceClockAlarmTimer,
                              7U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 68U,
                     chartInstance->c81_sfEvent);
        c81_d_temp = (_SFD_CCP_CALL(5U, 68U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
          68U, 0, (real_T)*chartInstance->c81_state_Detent, (real_T)
          chartInstance->c81_ERR_DETENT, 0, 0U, *chartInstance->c81_state_Detent
          == chartInstance->c81_ERR_DETENT) != 0U, chartInstance->c81_sfEvent)
                      != 0U);
        if (c81_d_temp) {
          c81_d_temp = (_SFD_CCP_CALL(5U, 68U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 68U, 1, (real_T)c81_get_ee_DeluxeG5(chartInstance, 0), (real_T)
             chartInstance->c81_ACTIVE, 0, 1U, c81_get_ee_DeluxeG5(chartInstance,
            0) != chartInstance->c81_ACTIVE) != 0U, chartInstance->c81_sfEvent)
                        != 0U);
        }

        c81_e_temp = c81_d_temp;
        if (c81_d_temp) {
          c81_e_temp = (_SFD_CCP_CALL(5U, 68U, 2, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 68U, 2, (real_T)chartInstance->c81_CD_DELUXE_GEN5_5_FUNCTION,
             (real_T)chartInstance->c81_NON_FUNCTIONAL, 0, 0U,
             chartInstance->c81_CD_DELUXE_GEN5_5_FUNCTION ==
             chartInstance->c81_NON_FUNCTIONAL) != 0U,
            chartInstance->c81_sfEvent) != 0U);
        }

        c81_d_out = (CV_TRANSITION_EVAL(68U, (int32_T)c81_e_temp) != 0);
        if (c81_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
          chartInstance->c81_tp_NO_STATE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_NON_SHUTDOWN = c81_IN_Aux_Detent_Error;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 62U, chartInstance->c81_sfEvent);
          chartInstance->c81_temporalCounter_i3 = 0U;
          chartInstance->c81_tp_Aux_Detent_Error = 1U;
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 70U, chartInstance->c81_sfEvent);
          chartInstance->c81_is_Aux_Detent_Error = c81_IN_HOLD;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 64U, chartInstance->c81_sfEvent);
          chartInstance->c81_temporalCounter_i4 = 0U;
          chartInstance->c81_tp_HOLD = 1U;
          *chartInstance->c81_state_InfoSecondary =
            chartInstance->c81_DISPLAY_HOLD;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary,
                                30U);
        } else {
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 73U,
                       chartInstance->c81_sfEvent);
          c81_f_temp = (_SFD_CCP_CALL(5U, 73U, 0, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 73U, 0, (real_T)*chartInstance->c81_state_CANThrottleCalDiag,
             (real_T)chartInstance->c81_INACTIVE, 0, 1U,
             *chartInstance->c81_state_CANThrottleCalDiag !=
             chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) !=
                        0U);
          if (c81_f_temp) {
            c81_f_temp = (_SFD_CCP_CALL(5U, 73U, 1, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 73U, 1, (real_T)
                                 *chartInstance->c81_state_InfoPrimary, (real_T)
                                 chartInstance->c81_DISPLAY_ENGINE_HOURS, 0, 0U,
                                 *chartInstance->c81_state_InfoPrimary ==
                                 chartInstance->c81_DISPLAY_ENGINE_HOURS) != 0U,
              chartInstance->c81_sfEvent) != 0U);
          }

          c81_e_out = (CV_TRANSITION_EVAL(73U, (int32_T)c81_f_temp) != 0);
          if (c81_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 73U, chartInstance->c81_sfEvent);
            chartInstance->c81_tp_NO_STATE = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
            chartInstance->c81_is_NON_SHUTDOWN = c81_IN_THROTTLE_CAL_DIAGNOSTICS;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 71U, chartInstance->c81_sfEvent);
            chartInstance->c81_temporalCounter_i3 = 0U;
            chartInstance->c81_tp_THROTTLE_CAL_DIAGNOSTICS = 1U;
            *chartInstance->c81_state_InfoSecondary =
              chartInstance->c81_DISPLAY_CAN_THROTTLE_DIAG;
            _SFD_DATA_RANGE_CHECK((real_T)
                                  *chartInstance->c81_state_InfoSecondary, 30U);
          } else {
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 97U,
                         chartInstance->c81_sfEvent);
            c81_g_temp = (_SFD_CCP_CALL(5U, 97U, 0, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 97U, 0, (real_T)
                                 chartInstance->c81_CD_SECOND_AUX_FUNCTION,
                                 (real_T)chartInstance->c81_NON_FUNCTIONAL, 0,
                                 1U, chartInstance->c81_CD_SECOND_AUX_FUNCTION
                                 != chartInstance->c81_NON_FUNCTIONAL) != 0U,
              chartInstance->c81_sfEvent) != 0U);
            if (c81_g_temp) {
              c81_g_temp = (_SFD_CCP_CALL(5U, 97U, 1,
                *chartInstance->c81_fallingedge_SecondAux != 0U,
                chartInstance->c81_sfEvent) != 0U);
            }

            c81_f_out = (CV_TRANSITION_EVAL(97U, (int32_T)c81_g_temp) != 0);
            if (c81_f_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 97U,
                           chartInstance->c81_sfEvent);
              chartInstance->c81_tp_NO_STATE = 0U;
              _SFD_CS_CALL(STATE_INACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
              chartInstance->c81_is_NON_SHUTDOWN = c81_IN_OFFSET;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 69U, chartInstance->c81_sfEvent);
              chartInstance->c81_temporalCounter_i3 = 0U;
              chartInstance->c81_tp_OFFSET = 1U;
              *chartInstance->c81_state_InfoSecondary =
                chartInstance->c81_DISPLAY_OFFSET;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c81_state_InfoSecondary, 30U);
            } else {
              _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 68U,
                           chartInstance->c81_sfEvent);
            }
          }
        }
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 68U, chartInstance->c81_sfEvent);
}

static void c81_THROTTLE_CAL_DIAGNOSTICS(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  uint16_T c81_u5;
  boolean_T c81_temp;
  boolean_T c81_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 74U, chartInstance->c81_sfEvent);
  c81_u5 = c81__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD((uint32_T)
    chartInstance->c81_CD_CAN_THROTTLE_CAL_DIAG_TIME, 16U, 74U), 854U, 1U, 5U);
  c81_temp = (_SFD_CCP_CALL(5U, 74U, 0, (chartInstance->c81_temporalCounter_i3 >=
    c81_u5) != 0U, chartInstance->c81_sfEvent) != 0U);
  if (!c81_temp) {
    c81_temp = (_SFD_CCP_CALL(5U, 74U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 74U,
      0, (real_T)*chartInstance->c81_state_CANThrottleCalDiag, (real_T)
      chartInstance->c81_INACTIVE, 0, 0U,
      *chartInstance->c81_state_CANThrottleCalDiag ==
      chartInstance->c81_INACTIVE) != 0U, chartInstance->c81_sfEvent) != 0U);
  }

  c81_out = (CV_TRANSITION_EVAL(74U, (int32_T)c81_temp) != 0);
  if (c81_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 74U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_THROTTLE_CAL_DIAGNOSTICS = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 71U, chartInstance->c81_sfEvent);
    chartInstance->c81_is_NON_SHUTDOWN = c81_IN_NO_STATE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 68U, chartInstance->c81_sfEvent);
    chartInstance->c81_tp_NO_STATE = 1U;
    *chartInstance->c81_state_InfoSecondary = chartInstance->c81_INACTIVE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c81_state_InfoSecondary, 30U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 71U,
                 chartInstance->c81_sfEvent);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 71U, chartInstance->c81_sfEvent);
}

static void c81_exit_internal_Aux_Detent_Error
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c81_is_Aux_Detent_Error) {
   case c81_IN_AUX:
    CV_STATE_EVAL(62, 1, c81_IN_AUX);
    chartInstance->c81_tp_AUX = 0U;
    chartInstance->c81_is_Aux_Detent_Error = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 63U, chartInstance->c81_sfEvent);
    break;

   case c81_IN_HOLD:
    CV_STATE_EVAL(62, 1, c81_IN_HOLD);
    chartInstance->c81_tp_HOLD = 0U;
    chartInstance->c81_is_Aux_Detent_Error = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 64U, chartInstance->c81_sfEvent);
    break;

   default:
    CV_STATE_EVAL(62, 1, 0);
    chartInstance->c81_is_Aux_Detent_Error = c81_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 63U, chartInstance->c81_sfEvent);
    break;
  }
}

static void init_script_number_translation(uint32_T c81_machineNumber, uint32_T
  c81_chartNumber, uint32_T c81_instanceNumber)
{
  (void)(c81_machineNumber);
  (void)(c81_chartNumber);
  (void)(c81_instanceNumber);
}

const mxArray *sf_c81_MX_Gtwy_Control_get_eml_resolved_functions_info(void)
{
  const mxArray *c81_nameCaptureInfo = NULL;
  c81_nameCaptureInfo = NULL;
  sf_mex_assign(&c81_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c81_nameCaptureInfo;
}

static const mxArray *c81_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData)
{
  const mxArray *c81_mxArrayOutData;
  int32_T c81_u;
  const mxArray *c81_y = NULL;
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_mxArrayOutData = NULL;
  c81_mxArrayOutData = NULL;
  c81_u = *(int32_T *)c81_inData;
  c81_y = NULL;
  sf_mex_assign(&c81_y, sf_mex_create("y", &c81_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c81_mxArrayOutData, c81_y, false);
  return c81_mxArrayOutData;
}

static int32_T c81_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId)
{
  int32_T c81_y;
  int32_T c81_i1;
  (void)chartInstance;
  sf_mex_import(c81_parentId, sf_mex_dup(c81_u), &c81_i1, 1, 6, 0U, 0, 0U, 0);
  c81_y = c81_i1;
  sf_mex_destroy(&c81_u);
  return c81_y;
}

static void c81_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c81_mxArrayInData, const char_T *c81_varName, void *c81_outData)
{
  const mxArray *c81_b_sfEvent;
  emlrtMsgIdentifier c81_thisId;
  int32_T c81_y;
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_b_sfEvent = sf_mex_dup(c81_mxArrayInData);
  c81_thisId.fIdentifier = (const char *)c81_varName;
  c81_thisId.fParent = NULL;
  c81_thisId.bParentIsCell = false;
  c81_y = c81_emlrt_marshallIn(chartInstance, sf_mex_dup(c81_b_sfEvent),
    &c81_thisId);
  sf_mex_destroy(&c81_b_sfEvent);
  *(int32_T *)c81_outData = c81_y;
  sf_mex_destroy(&c81_mxArrayInData);
}

static const mxArray *c81_b_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData)
{
  const mxArray *c81_mxArrayOutData;
  uint8_T c81_u;
  const mxArray *c81_y = NULL;
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_mxArrayOutData = NULL;
  c81_mxArrayOutData = NULL;
  c81_u = *(uint8_T *)c81_inData;
  c81_y = NULL;
  sf_mex_assign(&c81_y, sf_mex_create("y", &c81_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c81_mxArrayOutData, c81_y, false);
  return c81_mxArrayOutData;
}

static uint8_T c81_b_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_b_tp_BUTTON_STATE, const char_T
  *c81_identifier)
{
  uint8_T c81_y;
  emlrtMsgIdentifier c81_thisId;
  c81_thisId.fIdentifier = (const char *)c81_identifier;
  c81_thisId.fParent = NULL;
  c81_thisId.bParentIsCell = false;
  c81_y = c81_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c81_b_tp_BUTTON_STATE),
    &c81_thisId);
  sf_mex_destroy(&c81_b_tp_BUTTON_STATE);
  return c81_y;
}

static uint8_T c81_c_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId)
{
  uint8_T c81_y;
  uint8_T c81_u6;
  (void)chartInstance;
  sf_mex_import(c81_parentId, sf_mex_dup(c81_u), &c81_u6, 1, 3, 0U, 0, 0U, 0);
  c81_y = c81_u6;
  sf_mex_destroy(&c81_u);
  return c81_y;
}

static void c81_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c81_mxArrayInData, const char_T *c81_varName, void *c81_outData)
{
  const mxArray *c81_b_tp_BUTTON_STATE;
  emlrtMsgIdentifier c81_thisId;
  uint8_T c81_y;
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_b_tp_BUTTON_STATE = sf_mex_dup(c81_mxArrayInData);
  c81_thisId.fIdentifier = (const char *)c81_varName;
  c81_thisId.fParent = NULL;
  c81_thisId.bParentIsCell = false;
  c81_y = c81_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c81_b_tp_BUTTON_STATE),
    &c81_thisId);
  sf_mex_destroy(&c81_b_tp_BUTTON_STATE);
  *(uint8_T *)c81_outData = c81_y;
  sf_mex_destroy(&c81_mxArrayInData);
}

static const mxArray *c81_c_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData)
{
  const mxArray *c81_mxArrayOutData;
  uint16_T c81_u;
  const mxArray *c81_y = NULL;
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_mxArrayOutData = NULL;
  c81_mxArrayOutData = NULL;
  c81_u = *(uint16_T *)c81_inData;
  c81_y = NULL;
  sf_mex_assign(&c81_y, sf_mex_create("y", &c81_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c81_mxArrayOutData, c81_y, false);
  return c81_mxArrayOutData;
}

static uint16_T c81_d_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_b_debounceCount, const char_T
  *c81_identifier)
{
  uint16_T c81_y;
  emlrtMsgIdentifier c81_thisId;
  c81_thisId.fIdentifier = (const char *)c81_identifier;
  c81_thisId.fParent = NULL;
  c81_thisId.bParentIsCell = false;
  c81_y = c81_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c81_b_debounceCount),
    &c81_thisId);
  sf_mex_destroy(&c81_b_debounceCount);
  return c81_y;
}

static uint16_T c81_e_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId)
{
  uint16_T c81_y;
  uint16_T c81_u7;
  (void)chartInstance;
  sf_mex_import(c81_parentId, sf_mex_dup(c81_u), &c81_u7, 1, 5, 0U, 0, 0U, 0);
  c81_y = c81_u7;
  sf_mex_destroy(&c81_u);
  return c81_y;
}

static void c81_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c81_mxArrayInData, const char_T *c81_varName, void *c81_outData)
{
  const mxArray *c81_b_debounceCount;
  emlrtMsgIdentifier c81_thisId;
  uint16_T c81_y;
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_b_debounceCount = sf_mex_dup(c81_mxArrayInData);
  c81_thisId.fIdentifier = (const char *)c81_varName;
  c81_thisId.fParent = NULL;
  c81_thisId.bParentIsCell = false;
  c81_y = c81_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c81_b_debounceCount),
    &c81_thisId);
  sf_mex_destroy(&c81_b_debounceCount);
  *(uint16_T *)c81_outData = c81_y;
  sf_mex_destroy(&c81_mxArrayInData);
}

static const mxArray *c81_d_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData)
{
  const mxArray *c81_mxArrayOutData;
  int32_T c81_i2;
  const mxArray *c81_y = NULL;
  uint8_T c81_u[8];
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_mxArrayOutData = NULL;
  c81_mxArrayOutData = NULL;
  for (c81_i2 = 0; c81_i2 < 8; c81_i2++) {
    c81_u[c81_i2] = (*(uint8_T (*)[8])c81_inData)[c81_i2];
  }

  c81_y = NULL;
  sf_mex_assign(&c81_y, sf_mex_create("y", c81_u, 3, 0U, 1U, 0U, 1, 8), false);
  sf_mex_assign(&c81_mxArrayOutData, c81_y, false);
  return c81_mxArrayOutData;
}

static const mxArray *c81_e_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData)
{
  const mxArray *c81_mxArrayOutData;
  int32_T c81_i3;
  const mxArray *c81_y = NULL;
  uint8_T c81_u[2];
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_mxArrayOutData = NULL;
  c81_mxArrayOutData = NULL;
  for (c81_i3 = 0; c81_i3 < 2; c81_i3++) {
    c81_u[c81_i3] = (*(uint8_T (*)[2])c81_inData)[c81_i3];
  }

  c81_y = NULL;
  sf_mex_assign(&c81_y, sf_mex_create("y", c81_u, 3, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c81_mxArrayOutData, c81_y, false);
  return c81_mxArrayOutData;
}

static void c81_f_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId,
  uint8_T c81_y[2])
{
  uint8_T c81_uv0[2];
  int32_T c81_i4;
  (void)chartInstance;
  sf_mex_import(c81_parentId, sf_mex_dup(c81_u), c81_uv0, 1, 3, 0U, 1, 0U, 1, 2);
  for (c81_i4 = 0; c81_i4 < 2; c81_i4++) {
    c81_y[c81_i4] = c81_uv0[c81_i4];
  }

  sf_mex_destroy(&c81_u);
}

static void c81_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c81_mxArrayInData, const char_T *c81_varName, void *c81_outData)
{
  const mxArray *c81_ee_JobClockLHP;
  emlrtMsgIdentifier c81_thisId;
  uint8_T c81_y[2];
  int32_T c81_i5;
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_ee_JobClockLHP = sf_mex_dup(c81_mxArrayInData);
  c81_thisId.fIdentifier = (const char *)c81_varName;
  c81_thisId.fParent = NULL;
  c81_thisId.bParentIsCell = false;
  c81_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c81_ee_JobClockLHP),
    &c81_thisId, c81_y);
  sf_mex_destroy(&c81_ee_JobClockLHP);
  for (c81_i5 = 0; c81_i5 < 2; c81_i5++) {
    (*(uint8_T (*)[2])c81_outData)[c81_i5] = c81_y[c81_i5];
  }

  sf_mex_destroy(&c81_mxArrayInData);
}

static const mxArray *c81_f_sf_marshallOut(void *chartInstanceVoid, void
  *c81_inData)
{
  const mxArray *c81_mxArrayOutData;
  boolean_T c81_u;
  const mxArray *c81_y = NULL;
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_mxArrayOutData = NULL;
  c81_mxArrayOutData = NULL;
  c81_u = *(boolean_T *)c81_inData;
  c81_y = NULL;
  sf_mex_assign(&c81_y, sf_mex_create("y", &c81_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c81_mxArrayOutData, c81_y, false);
  return c81_mxArrayOutData;
}

static boolean_T c81_g_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_b_prev_SecondAux, const char_T
  *c81_identifier)
{
  boolean_T c81_y;
  emlrtMsgIdentifier c81_thisId;
  c81_thisId.fIdentifier = (const char *)c81_identifier;
  c81_thisId.fParent = NULL;
  c81_thisId.bParentIsCell = false;
  c81_y = c81_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c81_b_prev_SecondAux),
    &c81_thisId);
  sf_mex_destroy(&c81_b_prev_SecondAux);
  return c81_y;
}

static boolean_T c81_h_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId)
{
  boolean_T c81_y;
  boolean_T c81_b0;
  (void)chartInstance;
  sf_mex_import(c81_parentId, sf_mex_dup(c81_u), &c81_b0, 1, 11, 0U, 0, 0U, 0);
  c81_y = c81_b0;
  sf_mex_destroy(&c81_u);
  return c81_y;
}

static void c81_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c81_mxArrayInData, const char_T *c81_varName, void *c81_outData)
{
  const mxArray *c81_b_prev_SecondAux;
  emlrtMsgIdentifier c81_thisId;
  boolean_T c81_y;
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c81_b_prev_SecondAux = sf_mex_dup(c81_mxArrayInData);
  c81_thisId.fIdentifier = (const char *)c81_varName;
  c81_thisId.fParent = NULL;
  c81_thisId.bParentIsCell = false;
  c81_y = c81_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c81_b_prev_SecondAux),
    &c81_thisId);
  sf_mex_destroy(&c81_b_prev_SecondAux);
  *(boolean_T *)c81_outData = c81_y;
  sf_mex_destroy(&c81_mxArrayInData);
}

static const mxArray *c81_i_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_b_setSimStateSideEffectsInfo, const char_T *
  c81_identifier)
{
  const mxArray *c81_y = NULL;
  emlrtMsgIdentifier c81_thisId;
  c81_y = NULL;
  c81_thisId.fIdentifier = (const char *)c81_identifier;
  c81_thisId.fParent = NULL;
  c81_thisId.bParentIsCell = false;
  sf_mex_assign(&c81_y, c81_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c81_b_setSimStateSideEffectsInfo), &c81_thisId), false);
  sf_mex_destroy(&c81_b_setSimStateSideEffectsInfo);
  return c81_y;
}

static const mxArray *c81_j_emlrt_marshallIn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c81_u, const emlrtMsgIdentifier *c81_parentId)
{
  const mxArray *c81_y = NULL;
  (void)chartInstance;
  (void)c81_parentId;
  c81_y = NULL;
  sf_mex_assign(&c81_y, sf_mex_duplicatearraysafe(&c81_u), false);
  sf_mex_destroy(&c81_u);
  return c81_y;
}

static const mxArray *sf_get_hover_data_for_msg
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c81_ssid)
{
  (void)chartInstance;
  (void)c81_ssid;
  return NULL;
}

static void c81_init_sf_message_store_memory(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static uint16_T c81__u16_s32_(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c81_b, uint32_T c81_ssid_src_loc, int32_T c81_offset_src_loc, int32_T
  c81_length_src_loc)
{
  uint16_T c81_a;
  (void)chartInstance;
  c81_a = (uint16_T)c81_b;
  if (c81_a != c81_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c81_ssid_src_loc, c81_offset_src_loc,
      c81_length_src_loc);
  }

  return c81_a;
}

static uint8_T c81__u8_s32_(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c81_b, uint32_T c81_ssid_src_loc, int32_T c81_offset_src_loc, int32_T
  c81_length_src_loc)
{
  uint8_T c81_a;
  (void)chartInstance;
  c81_a = (uint8_T)c81_b;
  if (c81_a != c81_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c81_ssid_src_loc, c81_offset_src_loc,
      c81_length_src_loc);
  }

  return c81_a;
}

static int32_T c81__s32_add__(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance,
  int32_T c81_b, int32_T c81_c, uint32_T c81_ssid_src_loc, int32_T
  c81_offset_src_loc, int32_T c81_length_src_loc)
{
  int32_T c81_a;
  (void)chartInstance;
  c81_a = c81_b + c81_c;
  if (((c81_a ^ c81_b) & (c81_a ^ c81_c)) < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c81_ssid_src_loc, c81_offset_src_loc,
      c81_length_src_loc);
  }

  return c81_a;
}

static uint16_T c81__u16_u32_(SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance,
  uint32_T c81_b, uint32_T c81_ssid_src_loc, int32_T c81_offset_src_loc, int32_T
  c81_length_src_loc)
{
  uint16_T c81_a;
  (void)chartInstance;
  c81_a = (uint16_T)c81_b;
  if (c81_a != c81_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c81_ssid_src_loc, c81_offset_src_loc,
      c81_length_src_loc);
  }

  return c81_a;
}

static uint8_T c81_get_ee_DeluxeG5(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex)
{
  if (chartInstance->c81_dsmdiag_ee_DeluxeG5) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, "ee_DeluxeG5",
      c81_elementIndex);
  }

  return *chartInstance->c81_ee_DeluxeG5_address;
}

static void c81_set_ee_DeluxeG5(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex, uint8_T c81_elementValue)
{
  if (chartInstance->c81_dsmdiag_ee_DeluxeG5) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, "ee_DeluxeG5",
      c81_elementIndex);
  }

  *chartInstance->c81_ee_DeluxeG5_address = c81_elementValue;
}

static uint8_T *c81_access_ee_DeluxeG5(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_rdOnly)
{
  if (chartInstance->c81_dsmdiag_ee_DeluxeG5) {
    ssAccessDataStore_wrapper(chartInstance->S, 0, "ee_DeluxeG5", c81_rdOnly);
  }

  return chartInstance->c81_ee_DeluxeG5_address;
}

static uint8_T c81_get_ee_EngData(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex)
{
  if (chartInstance->c81_dsmdiag_ee_EngData) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 1, "ee_EngData",
      c81_elementIndex);
  }

  return *chartInstance->c81__indexee_EngData_address;
}

static void c81_set_ee_EngData(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex, uint8_T c81_elementValue)
{
  if (chartInstance->c81_dsmdiag_ee_EngData) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 1, "ee_EngData",
      c81_elementIndex);
  }

  *chartInstance->c81__indexee_EngData_address = c81_elementValue;
}

static uint8_T *c81_access_ee_EngData(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_rdOnly)
{
  if (chartInstance->c81_dsmdiag_ee_EngData) {
    ssAccessDataStore_wrapper(chartInstance->S, 1, "ee_EngData", c81_rdOnly);
  }

  return chartInstance->c81__indexee_EngData_address;
}

static uint8_T c81_get_ee_JobClockLHP(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex)
{
  if (chartInstance->c81_dsmdiag_ee_JobClockLHP) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 2, "ee_JobClockLHP",
      c81_elementIndex);
  }

  return (*chartInstance->c81__indexee_JobClockLHP_address)[c81_elementIndex];
}

static void c81_set_ee_JobClockLHP(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex, uint8_T c81_elementValue)
{
  if (chartInstance->c81_dsmdiag_ee_JobClockLHP) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 2, "ee_JobClockLHP",
      c81_elementIndex);
  }

  (*chartInstance->c81__indexee_JobClockLHP_address)[c81_elementIndex] =
    c81_elementValue;
}

static uint8_T *c81_access_ee_JobClockLHP(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_rdOnly)
{
  if (chartInstance->c81_dsmdiag_ee_JobClockLHP) {
    ssAccessDataStore_wrapper(chartInstance->S, 2, "ee_JobClockLHP", c81_rdOnly);
  }

  return &(*chartInstance->c81__indexee_JobClockLHP_address)[0U];
}

static uint8_T c81_get_flag_StdActiveWarn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex)
{
  if (chartInstance->c81_dsmdiag_flag_StdActiveWarn) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 3, "flag_StdActiveWarn",
      c81_elementIndex);
  }

  return *chartInstance->c81__indexflag_StdActiveWarn_address;
}

static void c81_set_flag_StdActiveWarn(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c81_elementIndex, uint8_T c81_elementValue)
{
  if (chartInstance->c81_dsmdiag_flag_StdActiveWarn) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 3, "flag_StdActiveWarn",
      c81_elementIndex);
  }

  *chartInstance->c81__indexflag_StdActiveWarn_address = c81_elementValue;
}

static uint8_T *c81_access_flag_StdActiveWarn
  (SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance, uint32_T c81_rdOnly)
{
  if (chartInstance->c81_dsmdiag_flag_StdActiveWarn) {
    ssAccessDataStore_wrapper(chartInstance->S, 3, "flag_StdActiveWarn",
      c81_rdOnly);
  }

  return chartInstance->c81__indexflag_StdActiveWarn_address;
}

static void init_dsm_address_info(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_DeluxeG5", (void **)
    &chartInstance->c81_ee_DeluxeG5_address, &chartInstance->c81__indexuxeG5);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_EngData", (void **)
    &chartInstance->c81__indexee_EngData_address, &chartInstance->c81__indexData);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_JobClockLHP",
    (void **)&chartInstance->c81__indexee_JobClockLHP_address,
    &chartInstance->c81__indexClockLHP);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "flag_StdActiveWarn",
    (void **)&chartInstance->c81__indexflag_StdActiveWarn_address,
    &chartInstance->c81__indextdActiveWarn);
}

static void init_simulink_io_address(SFc81_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  chartInstance->c81_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c81_state_InfoPrimary = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c81_count_GlowPlug = (uint16_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c81_msg_PanelButtonState = (uint8_T (*)[8])
    ssGetInputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c81_state_ServiceClock = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 2);
  chartInstance->c81_state_Engine = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c81_state_Key = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c81_state_InfoButton = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c81_state_InfoSecondary = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c81_state_LeftButton = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c81_state_RightButton = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 5);
  chartInstance->c81_enable_RightLeft = (uint8_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c81_state_Detent = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c81_state_DetentEnable = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 6);
  chartInstance->c81_state_CANThrottleCalDiag = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 7);
  chartInstance->c81_state_TC = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c81_KSSDisplayState = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c81_state_KeylessPanel = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 10);
  chartInstance->c81_state_MachineLock = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 11);
  chartInstance->c81_cmd_SecondAux = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 12);
  chartInstance->c81_fallingedge_SecondAux = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 13);
  chartInstance->c81_mode_ControlChange = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 14);
  chartInstance->c81_mode_LeftControl = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 15);
  chartInstance->c81_mode_RightControl = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 16);
  chartInstance->c81_dsmdiag_ee_DeluxeG5 = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 0, "ee_DeluxeG5");
  chartInstance->c81_dsmdiag_ee_EngData = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 1, "ee_EngData");
  chartInstance->c81_dsmdiag_ee_JobClockLHP = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 2,
    "ee_JobClockLHP");
  chartInstance->c81_dsmdiag_flag_StdActiveWarn = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 3,
    "flag_StdActiveWarn");
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

void sf_c81_MX_Gtwy_Control_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2804268561U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3066266999U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1370212264U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(520232557U);
}

mxArray* sf_c81_MX_Gtwy_Control_get_post_codegen_info(void);
mxArray *sf_c81_MX_Gtwy_Control_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("328a3hA02us8wQR2ksXuEF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(8);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,62,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,48,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,48,"type",mxType);
    }

    mxSetField(mxData,48,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,49,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,49,"type",mxType);
    }

    mxSetField(mxData,49,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,50,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,50,"type",mxType);
    }

    mxSetField(mxData,50,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,51,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,51,"type",mxType);
    }

    mxSetField(mxData,51,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,52,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,52,"type",mxType);
    }

    mxSetField(mxData,52,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,53,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,53,"type",mxType);
    }

    mxSetField(mxData,53,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,54,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,54,"type",mxType);
    }

    mxSetField(mxData,54,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,55,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,55,"type",mxType);
    }

    mxSetField(mxData,55,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,56,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,56,"type",mxType);
    }

    mxSetField(mxData,56,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,57,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,57,"type",mxType);
    }

    mxSetField(mxData,57,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,58,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,58,"type",mxType);
    }

    mxSetField(mxData,58,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,59,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,59,"type",mxType);
    }

    mxSetField(mxData,59,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,60,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,60,"type",mxType);
    }

    mxSetField(mxData,60,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,61,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,61,"type",mxType);
    }

    mxSetField(mxData,61,"complexity",mxCreateDoubleScalar(0));
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
    mxArray* mxPostCodegenInfo = sf_c81_MX_Gtwy_Control_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c81_MX_Gtwy_Control_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c81_MX_Gtwy_Control_jit_fallback_info(void)
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

mxArray *sf_c81_MX_Gtwy_Control_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c81_MX_Gtwy_Control_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c81_MX_Gtwy_Control(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[347],T\"enable_RightLeft\",},{M[1],M[129],T\"state_InfoButton\",},{M[1],M[102],T\"state_InfoPrimary\",},{M[1],M[130],T\"state_InfoSecondary\",},{M[1],M[342],T\"state_LeftButton\",},{M[1],M[343],T\"state_RightButton\",},{M[3],M[179],T\"debounceButton\",},{M[3],M[929],T\"debounceCode\",},{M[3],M[103],T\"debounceCount\",},{M[3],M[338],T\"debounceLeft\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[3],M[341],T\"debounceRight\",},{M[3],M[891],T\"prev_InfoSecondary\",},{M[3],M[949],T\"prev_SecondAux\",},{M[3],M[118],T\"serviceClockAlarmTimer\",},{M[3],M[122],T\"shutdownTimer\",},{M[3],M[131],T\"state_Jump\",},{M[3],M[132],T\"state_LightButton\",},{M[8],M[0],T\"is_active_c81_MX_Gtwy_Control\",},{M[8],M[3],T\"is_active_SECONDARY_STATE\",},{M[8],M[11],T\"is_active_BUTTON_STATE\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[8],M[12],T\"is_active_PRIMARY_STATE\",},{M[8],M[27],T\"is_active_LIGHT_BUTTON_STATE\",},{M[8],M[313],T\"is_active_INFO_BUTTON\",},{M[8],M[314],T\"is_active_MOVE_RIGHT\",},{M[8],M[325],T\"is_active_MOVE_LEFT\",},{M[8],M[405],T\"is_active_PANEL_BUTTON\",},{M[8],M[438],T\"is_active_PANEL_BUTTON\",},{M[9],M[3],T\"is_SECONDARY_STATE\",},{M[9],M[4],T\"is_NON_SHUTDOWN\",},{M[9],M[12],T\"is_PRIMARY_STATE\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[9],M[15],T\"is_ENGINE_HOURS\",},{M[9],M[16],T\"is_SERVICE_CLOCK\",},{M[9],M[24],T\"is_DELUXE_GOOD\",},{M[9],M[27],T\"is_LIGHT_BUTTON_STATE\",},{M[9],M[313],T\"is_INFO_BUTTON\",},{M[9],M[405],T\"is_PANEL_BUTTON\",},{M[9],M[438],T\"is_PANEL_BUTTON\",},{M[9],M[781],T\"is_JOB_CLOCK_1\",},{M[9],M[825],T\"is_JOB_CLOCK_2\",},{M[9],M[842],T\"is_Aux_Detent_Error\",}}",
    "100 S1x7'type','srcId','name','auxInfo'{{M[9],M[862],T\"is_FACTORY\",},{M[9],M[884],T\"is_ACTIVE\",},{M[10],M[884],T\"was_ACTIVE\",},{M[11],M[0],T\"temporalCounter_i4\",S'et','os','ct'{{T\"wu\",M1x2[844 843],M[1]}}},{M[11],M[0],T\"temporalCounter_i2\",S'et','os','ct'{{T\"wu\",M1x3[819 823 18],M[1]}}},{M[11],M[0],T\"temporalCounter_i3\",S'et','os','ct'{{T\"wu\",M1x3[852 940 842],M[1]}}},{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"wu\",M1x3[884 922 961],M[1]}}}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 47, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c81_MX_Gtwy_Control_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc81_MX_Gtwy_ControlInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc81_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MX_Gtwy_ControlMachineNumber_,
           81,
           74,
           113,
           0,
           100,
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
          _SFD_SET_DATA_PROPS(0,0,0,0,"debounceButton");
          _SFD_SET_DATA_PROPS(1,0,0,0,"debounceCode");
          _SFD_SET_DATA_PROPS(2,0,0,0,"debounceCount");
          _SFD_SET_DATA_PROPS(3,0,0,0,"debounceLeft");
          _SFD_SET_DATA_PROPS(4,0,0,0,"debounceRight");
          _SFD_SET_DATA_PROPS(5,0,0,0,"prev_InfoSecondary");
          _SFD_SET_DATA_PROPS(6,0,0,0,"prev_SecondAux");
          _SFD_SET_DATA_PROPS(7,0,0,0,"serviceClockAlarmTimer");
          _SFD_SET_DATA_PROPS(8,0,0,0,"shutdownTimer");
          _SFD_SET_DATA_PROPS(9,0,0,0,"state_Jump");
          _SFD_SET_DATA_PROPS(10,0,0,0,"state_LightButton");
          _SFD_SET_DATA_PROPS(11,1,1,0,"count_GlowPlug");
          _SFD_SET_DATA_PROPS(12,1,1,0,"msg_PanelButtonState");
          _SFD_SET_DATA_PROPS(13,1,1,0,"state_ServiceClock");
          _SFD_SET_DATA_PROPS(14,1,1,0,"state_Engine");
          _SFD_SET_DATA_PROPS(15,1,1,0,"state_Key");
          _SFD_SET_DATA_PROPS(16,1,1,0,"state_Detent");
          _SFD_SET_DATA_PROPS(17,1,1,0,"state_DetentEnable");
          _SFD_SET_DATA_PROPS(18,1,1,0,"state_CANThrottleCalDiag");
          _SFD_SET_DATA_PROPS(19,1,1,0,"state_TC");
          _SFD_SET_DATA_PROPS(20,1,1,0,"KSSDisplayState");
          _SFD_SET_DATA_PROPS(21,1,1,0,"state_KeylessPanel");
          _SFD_SET_DATA_PROPS(22,1,1,0,"state_MachineLock");
          _SFD_SET_DATA_PROPS(23,1,1,0,"cmd_SecondAux");
          _SFD_SET_DATA_PROPS(24,1,1,0,"fallingedge_SecondAux");
          _SFD_SET_DATA_PROPS(25,1,1,0,"mode_ControlChange");
          _SFD_SET_DATA_PROPS(26,1,1,0,"mode_LeftControl");
          _SFD_SET_DATA_PROPS(27,1,1,0,"mode_RightControl");
          _SFD_SET_DATA_PROPS(28,2,0,1,"state_InfoPrimary");
          _SFD_SET_DATA_PROPS(29,2,0,1,"state_InfoButton");
          _SFD_SET_DATA_PROPS(30,2,0,1,"state_InfoSecondary");
          _SFD_SET_DATA_PROPS(31,2,0,1,"state_LeftButton");
          _SFD_SET_DATA_PROPS(32,2,0,1,"state_RightButton");
          _SFD_SET_DATA_PROPS(33,2,0,1,"enable_RightLeft");
          _SFD_SET_DATA_PROPS(34,10,0,0,"ACTIVE");
          _SFD_SET_DATA_PROPS(35,10,0,0,"AUX_EMEA_CONTROLS");
          _SFD_SET_DATA_PROPS(36,10,0,0,"CD_AUTO_DISPLAY_FAULT_DEBOUNCE_ACTIVE");
          _SFD_SET_DATA_PROPS(37,10,0,0,"CD_AUTO_DISPLAY_FAULT_FUNCTION");
          _SFD_SET_DATA_PROPS(38,10,0,0,"CD_AUX_DETENT_CYCLE_TIME");
          _SFD_SET_DATA_PROPS(39,10,0,0,"CD_AUX_DETENT_FLASH_TIME");
          _SFD_SET_DATA_PROPS(40,10,0,0,"CD_AUX_FUNCTION");
          _SFD_SET_DATA_PROPS(41,10,0,0,"CD_CAN_THROTTLE_CAL_DIAG_TIME");
          _SFD_SET_DATA_PROPS(42,10,0,0,"CD_DELUXE_GEN5_5_FUNCTION");
          _SFD_SET_DATA_PROPS(43,10,0,0,"CD_DISPLAY_SERVICE_CLOCK_ALARM_TIME");
          _SFD_SET_DATA_PROPS(44,10,0,0,"CD_DISPLAY_SHUTDOWN_TIME");
          _SFD_SET_DATA_PROPS(45,10,0,0,"CD_EMEA_CONTROLS_DISPLAY_MODE");
          _SFD_SET_DATA_PROPS(46,10,0,0,"CD_EMEA_CONTROLS_DISPLAY_TIME");
          _SFD_SET_DATA_PROPS(47,10,0,0,"CD_HOT_FUNCTION");
          _SFD_SET_DATA_PROPS(48,10,0,0,"CD_SECOND_AUX_FUNCTION");
          _SFD_SET_DATA_PROPS(49,10,0,0,"CD_SECOND_AUX_OFFSET_DISP_TIME");
          _SFD_SET_DATA_PROPS(50,10,0,0,"DISPLAY_AUX");
          _SFD_SET_DATA_PROPS(51,10,0,0,"DISPLAY_BATTERY_VOLTAGE");
          _SFD_SET_DATA_PROPS(52,10,0,0,"DISPLAY_CAN_THROTTLE_DIAG");
          _SFD_SET_DATA_PROPS(53,10,0,0,"DISPLAY_COLD");
          _SFD_SET_DATA_PROPS(54,10,0,0,"DISPLAY_DELUXE_ERROR");
          _SFD_SET_DATA_PROPS(55,10,0,0,"DISPLAY_ECT");
          _SFD_SET_DATA_PROPS(56,10,0,0,"DISPLAY_EMEA_CONTROLS");
          _SFD_SET_DATA_PROPS(57,10,0,0,"DISPLAY_ENGINE_HOURS");
          _SFD_SET_DATA_PROPS(58,10,0,0,"DISPLAY_ENGINE_RPM");
          _SFD_SET_DATA_PROPS(59,10,0,0,"DISPLAY_EOP");
          _SFD_SET_DATA_PROPS(60,10,0,0,"DISPLAY_ERROR_CODES");
          _SFD_SET_DATA_PROPS(61,10,0,0,"DISPLAY_FLASH_COLD");
          _SFD_SET_DATA_PROPS(62,10,0,0,"DISPLAY_GLOW_PLUGS");
          _SFD_SET_DATA_PROPS(63,10,0,0,"DISPLAY_HOLD");
          _SFD_SET_DATA_PROPS(64,10,0,0,"DISPLAY_HOT");
          _SFD_SET_DATA_PROPS(65,10,0,0,"DISPLAY_JOB_CLOCK_1");
          _SFD_SET_DATA_PROPS(66,10,0,0,"DISPLAY_JOB_CLOCK_2");
          _SFD_SET_DATA_PROPS(67,10,0,0,"DISPLAY_OFFSET");
          _SFD_SET_DATA_PROPS(68,10,0,0,"DISPLAY_PRIMARY_INACTIVE");
          _SFD_SET_DATA_PROPS(69,10,0,0,"DISPLAY_SECOND_AUX");
          _SFD_SET_DATA_PROPS(70,10,0,0,"DISPLAY_SERVICE_CLOCK");
          _SFD_SET_DATA_PROPS(71,10,0,0,"DISPLAY_SERVICE_CLOCK_ALARM");
          _SFD_SET_DATA_PROPS(72,10,0,0,"DISPLAY_SERVICE_CLOCK_RESET");
          _SFD_SET_DATA_PROPS(73,10,0,0,"DISPLAY_SHUTDOWN");
          _SFD_SET_DATA_PROPS(74,10,0,0,"DISPLAY_VERSION");
          _SFD_SET_DATA_PROPS(75,10,0,0,"ENGINE_CRANKING");
          _SFD_SET_DATA_PROPS(76,10,0,0,"ERR_DETENT");
          _SFD_SET_DATA_PROPS(77,10,0,0,"EVENT");
          _SFD_SET_DATA_PROPS(78,10,0,0,"EXTREMELY_LOW");
          _SFD_SET_DATA_PROPS(79,10,0,0,"INACTIVE");
          _SFD_SET_DATA_PROPS(80,10,0,0,"INFO_BUTTON_MASK");
          _SFD_SET_DATA_PROPS(81,10,0,0,"INFO_BUTTON_PRESS");
          _SFD_SET_DATA_PROPS(82,10,0,0,"LEFT_BUTTON_MASK");
          _SFD_SET_DATA_PROPS(83,10,0,0,"LEFT_BUTTON_PRESS");
          _SFD_SET_DATA_PROPS(84,10,0,0,"LIGHT_BUTTON_MASK");
          _SFD_SET_DATA_PROPS(85,10,0,0,"LIGHT_BUTTON_PRESS");
          _SFD_SET_DATA_PROPS(86,10,0,0,"LOW");
          _SFD_SET_DATA_PROPS(87,10,0,0,"MODE_LEFT_NONE");
          _SFD_SET_DATA_PROPS(88,10,0,0,"MODE_RIGHT_NONE");
          _SFD_SET_DATA_PROPS(89,10,0,0,"MULTIPLE");
          _SFD_SET_DATA_PROPS(90,10,0,0,"NON_FUNCTIONAL");
          _SFD_SET_DATA_PROPS(91,10,0,0,"NORMAL");
          _SFD_SET_DATA_PROPS(92,10,0,0,"NO_COMMUNICATION");
          _SFD_SET_DATA_PROPS(93,10,0,0,"RIGHT_BUTTON_MASK");
          _SFD_SET_DATA_PROPS(94,10,0,0,"RIGHT_BUTTON_PRESS");
          _SFD_SET_DATA_PROPS(95,10,0,0,"SHUTDOWN");
          _SFD_SET_DATA_PROPS(96,11,0,0,"ee_DeluxeG5");
          _SFD_SET_DATA_PROPS(97,11,0,0,"ee_EngData");
          _SFD_SET_DATA_PROPS(98,11,0,0,"ee_JobClockLHP");
          _SFD_SET_DATA_PROPS(99,11,0,0,"flag_StdActiveWarn");
          _SFD_STATE_INFO(0,1,1);
          _SFD_STATE_INFO(1,0,1);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,1,1);
          _SFD_STATE_INFO(7,0,1);
          _SFD_STATE_INFO(8,0,0);
          _SFD_STATE_INFO(9,0,0);
          _SFD_STATE_INFO(10,0,0);
          _SFD_STATE_INFO(11,0,0);
          _SFD_STATE_INFO(12,1,1);
          _SFD_STATE_INFO(13,0,1);
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
          _SFD_STATE_INFO(57,0,1);
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
          _SFD_CH_SUBSTATE_COUNT(4);
          _SFD_CH_SUBSTATE_DECOMP(1);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,57);
          _SFD_CH_SUBSTATE_INDEX(2,22);
          _SFD_CH_SUBSTATE_INDEX(3,18);
          _SFD_ST_SUBSTATE_COUNT(0,3);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,12);
          _SFD_ST_SUBSTATE_INDEX(0,2,6);
          _SFD_ST_SUBSTATE_COUNT(1,4);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,3);
          _SFD_ST_SUBSTATE_INDEX(1,2,4);
          _SFD_ST_SUBSTATE_INDEX(1,3,5);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(12,1);
          _SFD_ST_SUBSTATE_INDEX(12,0,13);
          _SFD_ST_SUBSTATE_COUNT(13,4);
          _SFD_ST_SUBSTATE_INDEX(13,0,14);
          _SFD_ST_SUBSTATE_INDEX(13,1,15);
          _SFD_ST_SUBSTATE_INDEX(13,2,16);
          _SFD_ST_SUBSTATE_INDEX(13,3,17);
          _SFD_ST_SUBSTATE_COUNT(14,0);
          _SFD_ST_SUBSTATE_COUNT(15,0);
          _SFD_ST_SUBSTATE_COUNT(16,0);
          _SFD_ST_SUBSTATE_COUNT(17,0);
          _SFD_ST_SUBSTATE_COUNT(6,1);
          _SFD_ST_SUBSTATE_INDEX(6,0,7);
          _SFD_ST_SUBSTATE_COUNT(7,4);
          _SFD_ST_SUBSTATE_INDEX(7,0,8);
          _SFD_ST_SUBSTATE_INDEX(7,1,9);
          _SFD_ST_SUBSTATE_INDEX(7,2,10);
          _SFD_ST_SUBSTATE_INDEX(7,3,11);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,0);
          _SFD_ST_SUBSTATE_COUNT(10,0);
          _SFD_ST_SUBSTATE_COUNT(11,0);
          _SFD_ST_SUBSTATE_COUNT(57,2);
          _SFD_ST_SUBSTATE_INDEX(57,0,58);
          _SFD_ST_SUBSTATE_INDEX(57,1,59);
          _SFD_ST_SUBSTATE_COUNT(58,0);
          _SFD_ST_SUBSTATE_COUNT(59,4);
          _SFD_ST_SUBSTATE_INDEX(59,0,60);
          _SFD_ST_SUBSTATE_INDEX(59,1,61);
          _SFD_ST_SUBSTATE_INDEX(59,2,72);
          _SFD_ST_SUBSTATE_INDEX(59,3,73);
          _SFD_ST_SUBSTATE_COUNT(60,0);
          _SFD_ST_SUBSTATE_COUNT(61,8);
          _SFD_ST_SUBSTATE_INDEX(61,0,62);
          _SFD_ST_SUBSTATE_INDEX(61,1,65);
          _SFD_ST_SUBSTATE_INDEX(61,2,66);
          _SFD_ST_SUBSTATE_INDEX(61,3,67);
          _SFD_ST_SUBSTATE_INDEX(61,4,68);
          _SFD_ST_SUBSTATE_INDEX(61,5,69);
          _SFD_ST_SUBSTATE_INDEX(61,6,70);
          _SFD_ST_SUBSTATE_INDEX(61,7,71);
          _SFD_ST_SUBSTATE_COUNT(62,2);
          _SFD_ST_SUBSTATE_INDEX(62,0,63);
          _SFD_ST_SUBSTATE_INDEX(62,1,64);
          _SFD_ST_SUBSTATE_COUNT(63,0);
          _SFD_ST_SUBSTATE_COUNT(64,0);
          _SFD_ST_SUBSTATE_COUNT(65,0);
          _SFD_ST_SUBSTATE_COUNT(66,0);
          _SFD_ST_SUBSTATE_COUNT(67,0);
          _SFD_ST_SUBSTATE_COUNT(68,0);
          _SFD_ST_SUBSTATE_COUNT(69,0);
          _SFD_ST_SUBSTATE_COUNT(70,0);
          _SFD_ST_SUBSTATE_COUNT(71,0);
          _SFD_ST_SUBSTATE_COUNT(72,0);
          _SFD_ST_SUBSTATE_COUNT(73,0);
          _SFD_ST_SUBSTATE_COUNT(22,5);
          _SFD_ST_SUBSTATE_INDEX(22,0,23);
          _SFD_ST_SUBSTATE_INDEX(22,1,53);
          _SFD_ST_SUBSTATE_INDEX(22,2,54);
          _SFD_ST_SUBSTATE_INDEX(22,3,55);
          _SFD_ST_SUBSTATE_INDEX(22,4,56);
          _SFD_ST_SUBSTATE_COUNT(23,15);
          _SFD_ST_SUBSTATE_INDEX(23,0,24);
          _SFD_ST_SUBSTATE_INDEX(23,1,25);
          _SFD_ST_SUBSTATE_INDEX(23,2,26);
          _SFD_ST_SUBSTATE_INDEX(23,3,27);
          _SFD_ST_SUBSTATE_INDEX(23,4,31);
          _SFD_ST_SUBSTATE_INDEX(23,5,32);
          _SFD_ST_SUBSTATE_INDEX(23,6,33);
          _SFD_ST_SUBSTATE_INDEX(23,7,34);
          _SFD_ST_SUBSTATE_INDEX(23,8,37);
          _SFD_ST_SUBSTATE_INDEX(23,9,38);
          _SFD_ST_SUBSTATE_INDEX(23,10,42);
          _SFD_ST_SUBSTATE_INDEX(23,11,46);
          _SFD_ST_SUBSTATE_INDEX(23,12,47);
          _SFD_ST_SUBSTATE_INDEX(23,13,48);
          _SFD_ST_SUBSTATE_INDEX(23,14,52);
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
          _SFD_ST_SUBSTATE_COUNT(31,0);
          _SFD_ST_SUBSTATE_COUNT(32,0);
          _SFD_ST_SUBSTATE_COUNT(33,0);
          _SFD_ST_SUBSTATE_COUNT(34,2);
          _SFD_ST_SUBSTATE_INDEX(34,0,35);
          _SFD_ST_SUBSTATE_INDEX(34,1,36);
          _SFD_ST_SUBSTATE_COUNT(35,0);
          _SFD_ST_SUBSTATE_COUNT(36,0);
          _SFD_ST_SUBSTATE_COUNT(37,0);
          _SFD_ST_SUBSTATE_COUNT(38,3);
          _SFD_ST_SUBSTATE_INDEX(38,0,39);
          _SFD_ST_SUBSTATE_INDEX(38,1,40);
          _SFD_ST_SUBSTATE_INDEX(38,2,41);
          _SFD_ST_SUBSTATE_COUNT(39,0);
          _SFD_ST_SUBSTATE_COUNT(40,0);
          _SFD_ST_SUBSTATE_COUNT(41,0);
          _SFD_ST_SUBSTATE_COUNT(42,3);
          _SFD_ST_SUBSTATE_INDEX(42,0,43);
          _SFD_ST_SUBSTATE_INDEX(42,1,44);
          _SFD_ST_SUBSTATE_INDEX(42,2,45);
          _SFD_ST_SUBSTATE_COUNT(43,0);
          _SFD_ST_SUBSTATE_COUNT(44,0);
          _SFD_ST_SUBSTATE_COUNT(45,0);
          _SFD_ST_SUBSTATE_COUNT(46,0);
          _SFD_ST_SUBSTATE_COUNT(47,0);
          _SFD_ST_SUBSTATE_COUNT(48,3);
          _SFD_ST_SUBSTATE_INDEX(48,0,49);
          _SFD_ST_SUBSTATE_INDEX(48,1,50);
          _SFD_ST_SUBSTATE_INDEX(48,2,51);
          _SFD_ST_SUBSTATE_COUNT(49,0);
          _SFD_ST_SUBSTATE_COUNT(50,0);
          _SFD_ST_SUBSTATE_COUNT(51,0);
          _SFD_ST_SUBSTATE_COUNT(52,0);
          _SFD_ST_SUBSTATE_COUNT(53,0);
          _SFD_ST_SUBSTATE_COUNT(54,0);
          _SFD_ST_SUBSTATE_COUNT(55,0);
          _SFD_ST_SUBSTATE_COUNT(56,0);
          _SFD_ST_SUBSTATE_COUNT(18,3);
          _SFD_ST_SUBSTATE_INDEX(18,0,19);
          _SFD_ST_SUBSTATE_INDEX(18,1,20);
          _SFD_ST_SUBSTATE_INDEX(18,2,21);
          _SFD_ST_SUBSTATE_COUNT(19,0);
          _SFD_ST_SUBSTATE_COUNT(20,0);
          _SFD_ST_SUBSTATE_COUNT(21,0);
        }

        _SFD_CV_INIT_CHART(4,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,3,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,4,1,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,1,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,4,1,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(12,1,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(13,4,1,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(18,3,1,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(22,5,1,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartDecMap[] = { 10 };

          static unsigned int sEndDecMap[] = { 25 };

          _SFD_CV_INIT_STATE(23,15,1,1,1,1,&(sStartDecMap[0]),&(sEndDecMap[0]));
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
          _SFD_CV_INIT_STATE(31,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(32,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(33,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(34,2,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(38,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(39,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(40,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(41,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(42,3,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(47,0,0,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(52,0,0,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(56,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(57,2,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(58,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(59,4,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(60,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(61,8,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(62,2,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(66,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(67,0,0,0,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(71,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(72,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(73,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 68 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(3,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 68 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(3,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(5,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(22,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(22,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 36 };

          static unsigned int sEndGuardMap[] = { 22, 56 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(13,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 36 };

          static unsigned int sEndRelationalopMap[] = { 22, 56 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 4, 0, 4, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(13,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 68 };

          static unsigned int sEndGuardMap[] = { 59, 88 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(4,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 68 };

          static unsigned int sEndRelationalopMap[] = { 59, 88 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(4,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(40,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 78 };

          static unsigned int sEndGuardMap[] = { 69, 94 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(41,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 69 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(41,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 60 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(42,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 60 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(42,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 60 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(43,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 60 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(43,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 21 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(44,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 21 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(44,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 60 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(45,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 60 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(45,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(46,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 76 };

          static unsigned int sEndGuardMap[] = { 67, 92 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(47,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 67 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(47,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(48,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(48,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(49,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(49,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 20 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(50,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 20 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(50,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(51,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(51,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(83,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 49, 81 };

          static unsigned int sEndGuardMap[] = { 41, 72, 107 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(99,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 49, 81 };

          static unsigned int sEndRelationalopMap[] = { 41, 72, 107 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 0, 0, 1, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(99,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(101,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(101,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 42 };

          static unsigned int sEndGuardMap[] = { 33, 83 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(100,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 42 };

          static unsigned int sEndRelationalopMap[] = { 33, 83 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 1, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(100,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(103,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 26 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(103,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 35 };

          static unsigned int sEndGuardMap[] = { 25, 59 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(102,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 35 };

          static unsigned int sEndRelationalopMap[] = { 25, 59 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(102,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 43, 89 };

          static unsigned int sEndGuardMap[] = { 33, 84, 104 };

          static int sPostFixPredicateTree[] = { 0, 1, 2, -2, -3 };

          _SFD_CV_INIT_TRANS(81,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 43 };

          static unsigned int sEndRelationalopMap[] = { 33, 84 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 1, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(81,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 42 };

          static unsigned int sEndGuardMap[] = { 33, 83 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(107,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 42 };

          static unsigned int sEndRelationalopMap[] = { 33, 83 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 1, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(107,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 43, 89 };

          static unsigned int sEndGuardMap[] = { 33, 84, 104 };

          static int sPostFixPredicateTree[] = { 0, 1, 2, -2, -3 };

          _SFD_CV_INIT_TRANS(94,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 43 };

          static unsigned int sEndRelationalopMap[] = { 33, 84 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 1, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(94,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 43, 75, 124, 172, 228 };

          static unsigned int sEndGuardMap[] = { 33, 69, 118, 163, 222, 278 };

          static int sPostFixPredicateTree[] = { 0, 1, 2, -3, 3, -3, 4, -3, 5,
            -3, -2 };

          _SFD_CV_INIT_TRANS(82,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 43, 75, 124, 172,
            228 };

          static unsigned int sEndRelationalopMap[] = { 33, 69, 118, 163, 222,
            278 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1
          };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(82,6,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 59, 86, 115 };

          static unsigned int sEndGuardMap[] = { 50, 77, 107, 158 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(92,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 86, 115 };

          static unsigned int sEndRelationalopMap[] = { 50, 107, 158 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(92,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 64 };

          static unsigned int sEndGuardMap[] = { 55, 90 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(93,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 64 };

          static unsigned int sEndRelationalopMap[] = { 55, 90 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 5, 0, 5, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(93,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 59, 86, 115 };

          static unsigned int sEndGuardMap[] = { 50, 77, 107, 158 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_TRANS(110,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 86, 115 };

          static unsigned int sEndRelationalopMap[] = { 50, 107, 158 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(110,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 57, 82 };

          static unsigned int sEndGuardMap[] = { 49, 75, 124 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(104,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 82 };

          static unsigned int sEndRelationalopMap[] = { 49, 124 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 1, 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(104,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(105,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(105,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 43 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(106,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 42 };

          static unsigned int sEndGuardMap[] = { 35, 78 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(109,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 42 };

          static unsigned int sEndRelationalopMap[] = { 35, 78 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(109,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(108,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 22 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(60,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 22 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(60,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(14,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(14,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 9, 0 };

          static unsigned int sEndGuardMap[] = { 13, 14 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(61,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(55,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(55,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(19,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 32 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(84,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 32 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(84,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 22 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(75,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 22 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(75,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(76,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(76,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 22 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(67,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 22 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(67,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 9, 0 };

          static unsigned int sEndGuardMap[] = { 13, 14 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(62,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(16,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(16,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 37 };

          static unsigned int sEndGuardMap[] = { 28, 84 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(111,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 37 };

          static unsigned int sEndRelationalopMap[] = { 28, 84 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(111,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(54,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(54,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(112,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(112,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(39,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(39,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 22 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(18,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 22 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(18,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 9, 0 };

          static unsigned int sEndGuardMap[] = { 13, 14 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(11,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(9,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(9,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(37,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(37,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(53,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 26 };

          static unsigned int sEndGuardMap[] = { 17, 52 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(52,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 26 };

          static unsigned int sEndRelationalopMap[] = { 17, 52 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(52,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(38,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(38,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(35,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(35,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(36,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(36,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(78,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 77 };

          static unsigned int sEndGuardMap[] = { 68, 108 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(79,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 77 };

          static unsigned int sEndRelationalopMap[] = { 68, 108 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(79,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(80,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(80,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 21 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(77,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 21 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(77,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(56,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(58,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(58,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 21 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(59,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 21 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(59,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 77 };

          static unsigned int sEndGuardMap[] = { 68, 108 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(57,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 77 };

          static unsigned int sEndRelationalopMap[] = { 68, 108 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(57,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(63,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(64,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(64,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 21 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(66,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 21 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(66,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 77 };

          static unsigned int sEndGuardMap[] = { 68, 108 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(65,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 77 };

          static unsigned int sEndRelationalopMap[] = { 68, 108 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(65,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(86,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 34 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(87,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 34 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(87,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(85,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(24,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 77, 114 };

          static unsigned int sEndGuardMap[] = { 68, 105, 145 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(23,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 77, 114 };

          static unsigned int sEndRelationalopMap[] = { 68, 105, 145 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(23,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(26,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(26,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 21 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(25,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 21 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(25,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(34,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(15,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(15,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 40 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(20,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 40 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(20,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(21,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 29 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(32,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 29 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(32,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 29 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(95,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 29 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(95,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 35 };

          static unsigned int sEndGuardMap[] = { 26, 62 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(33,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 35 };

          static unsigned int sEndRelationalopMap[] = { 26, 62 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(33,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 29 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(96,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 29 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(96,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 43 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 43 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 35, 62 };

          static unsigned int sEndGuardMap[] = { 26, 53, 83 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(10,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 35, 62 };

          static unsigned int sEndRelationalopMap[] = { 26, 53, 83 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(10,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(90,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 19 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(90,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 19 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(91,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 19 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(91,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 20 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(88,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 20 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(88,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 26 };

          static unsigned int sEndGuardMap[] = { 17, 51 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(89,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 26 };

          static unsigned int sEndRelationalopMap[] = { 17, 51 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(89,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 20 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(7,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 20 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(7,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 38, 74 };

          static unsigned int sEndGuardMap[] = { 29, 65, 101 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(6,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 38, 74 };

          static unsigned int sEndRelationalopMap[] = { 29, 65, 101 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(6,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 31, 76 };

          static unsigned int sEndGuardMap[] = { 21, 67, 117 };

          static int sPostFixPredicateTree[] = { 0, 1, 2, -3, -2 };

          _SFD_CV_INIT_TRANS(8,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 31, 76 };

          static unsigned int sEndRelationalopMap[] = { 21, 67, 117 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 0, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(8,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 67 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(0,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 67 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(0,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 47 };

          static unsigned int sEndGuardMap[] = { 38, 88 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(73,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2, 47 };

          static unsigned int sEndRelationalopMap[] = { 38, 88 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 0, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(73,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 51 };

          static unsigned int sEndGuardMap[] = { 43, 87 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(74,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 51 };

          static unsigned int sEndRelationalopMap[] = { 87 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(74,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 48 };

          static unsigned int sEndGuardMap[] = { 41, 69 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(97,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 41 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(97,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 44 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(98,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 34, 62 };

          static unsigned int sEndGuardMap[] = { 27, 55, 105 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(68,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 34, 62 };

          static unsigned int sEndRelationalopMap[] = { 27, 55, 105 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 0, 1, 0, 0, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(68,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 45 };

          static unsigned int sEndGuardMap[] = { 38, 73 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(69,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 45 };

          static unsigned int sEndRelationalopMap[] = { 73 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(69,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(70,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 37 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(72,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 37 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(71,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(27,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 70 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(28,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 70 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(28,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 59 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(31,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 59 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(31,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 22 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(29,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 22 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(29,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 21 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(30,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 21 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(30,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_f_sf_marshallOut,(MexInFcnForType)
          c81_e_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 8U;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c81_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(13,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_f_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_f_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_f_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(27,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(28,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(29,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(30,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(31,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(32,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(33,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(34,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(35,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(36,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(37,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(38,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(39,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(40,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(41,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(42,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(43,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(44,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(45,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(46,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(47,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(48,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(49,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_c_sf_marshallOut,(MexInFcnForType)
          c81_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(50,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(51,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(52,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(53,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(54,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(55,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(56,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(57,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(58,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(59,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(60,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(61,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(62,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(63,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(64,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(65,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(66,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(67,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(68,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(69,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(70,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(71,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(72,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(73,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(74,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(75,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(76,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(77,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(78,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(79,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(80,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(81,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(82,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(83,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(84,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(85,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(86,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(87,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(88,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(89,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(90,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(91,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(92,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(93,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(94,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(95,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(96,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(97,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2U;
          _SFD_SET_DATA_COMPILED_PROPS(98,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c81_e_sf_marshallOut,(MexInFcnForType)
            c81_d_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(99,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c81_b_sf_marshallOut,(MexInFcnForType)
          c81_b_sf_marshallIn);
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
    SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc81_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(28U, (void *)
          chartInstance->c81_state_InfoPrimary);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)&chartInstance->c81_debounceCount);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)chartInstance->c81_count_GlowPlug);
        _SFD_SET_DATA_VALUE_PTR(34U, (void *)&chartInstance->c81_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(51U, (void *)
          &chartInstance->c81_DISPLAY_BATTERY_VOLTAGE);
        _SFD_SET_DATA_VALUE_PTR(57U, (void *)
          &chartInstance->c81_DISPLAY_ENGINE_HOURS);
        _SFD_SET_DATA_VALUE_PTR(58U, (void *)
          &chartInstance->c81_DISPLAY_ENGINE_RPM);
        _SFD_SET_DATA_VALUE_PTR(60U, (void *)
          &chartInstance->c81_DISPLAY_ERROR_CODES);
        _SFD_SET_DATA_VALUE_PTR(62U, (void *)
          &chartInstance->c81_DISPLAY_GLOW_PLUGS);
        _SFD_SET_DATA_VALUE_PTR(69U, (void *)
          &chartInstance->c81_DISPLAY_SECOND_AUX);
        _SFD_SET_DATA_VALUE_PTR(79U, (void *)&chartInstance->c81_INACTIVE);
        _SFD_SET_DATA_VALUE_PTR(12U, (void *)
          chartInstance->c81_msg_PanelButtonState);
        _SFD_SET_DATA_VALUE_PTR(13U, (void *)
          chartInstance->c81_state_ServiceClock);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)
          &chartInstance->c81_serviceClockAlarmTimer);
        _SFD_SET_DATA_VALUE_PTR(43U, (void *)
          &chartInstance->c81_CD_DISPLAY_SERVICE_CLOCK_ALARM_TIME);
        _SFD_SET_DATA_VALUE_PTR(71U, (void *)
          &chartInstance->c81_DISPLAY_SERVICE_CLOCK_ALARM);
        _SFD_SET_DATA_VALUE_PTR(14U, (void *)chartInstance->c81_state_Engine);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)&chartInstance->c81_shutdownTimer);
        _SFD_SET_DATA_VALUE_PTR(44U, (void *)
          &chartInstance->c81_CD_DISPLAY_SHUTDOWN_TIME);
        _SFD_SET_DATA_VALUE_PTR(95U, (void *)&chartInstance->c81_SHUTDOWN);
        _SFD_SET_DATA_VALUE_PTR(73U, (void *)
          &chartInstance->c81_DISPLAY_SHUTDOWN);
        _SFD_SET_DATA_VALUE_PTR(72U, (void *)
          &chartInstance->c81_DISPLAY_SERVICE_CLOCK_RESET);
        _SFD_SET_DATA_VALUE_PTR(15U, (void *)chartInstance->c81_state_Key);
        _SFD_SET_DATA_VALUE_PTR(89U, (void *)&chartInstance->c81_MULTIPLE);
        _SFD_SET_DATA_VALUE_PTR(29U, (void *)chartInstance->c81_state_InfoButton);
        _SFD_SET_DATA_VALUE_PTR(30U, (void *)
          chartInstance->c81_state_InfoSecondary);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)&chartInstance->c81_state_Jump);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)
          &chartInstance->c81_state_LightButton);
        _SFD_SET_DATA_VALUE_PTR(74U, (void *)&chartInstance->c81_DISPLAY_VERSION);
        _SFD_SET_DATA_VALUE_PTR(54U, (void *)
          &chartInstance->c81_DISPLAY_DELUXE_ERROR);
        _SFD_SET_DATA_VALUE_PTR(92U, (void *)
          &chartInstance->c81_NO_COMMUNICATION);
        _SFD_SET_DATA_VALUE_PTR(80U, (void *)
          &chartInstance->c81_INFO_BUTTON_MASK);
        _SFD_SET_DATA_VALUE_PTR(81U, (void *)
          &chartInstance->c81_INFO_BUTTON_PRESS);
        _SFD_SET_DATA_VALUE_PTR(84U, (void *)
          &chartInstance->c81_LIGHT_BUTTON_MASK);
        _SFD_SET_DATA_VALUE_PTR(85U, (void *)
          &chartInstance->c81_LIGHT_BUTTON_PRESS);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)&chartInstance->c81_debounceButton);
        _SFD_SET_DATA_VALUE_PTR(59U, (void *)&chartInstance->c81_DISPLAY_EOP);
        _SFD_SET_DATA_VALUE_PTR(55U, (void *)&chartInstance->c81_DISPLAY_ECT);
        _SFD_SET_DATA_VALUE_PTR(64U, (void *)&chartInstance->c81_DISPLAY_HOT);
        _SFD_SET_DATA_VALUE_PTR(97U, (void *)
          chartInstance->c81__indexee_EngData_address);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)&chartInstance->c81_debounceLeft);
        _SFD_SET_DATA_VALUE_PTR(82U, (void *)
          &chartInstance->c81_LEFT_BUTTON_MASK);
        _SFD_SET_DATA_VALUE_PTR(94U, (void *)
          &chartInstance->c81_RIGHT_BUTTON_PRESS);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)&chartInstance->c81_debounceRight);
        _SFD_SET_DATA_VALUE_PTR(31U, (void *)chartInstance->c81_state_LeftButton);
        _SFD_SET_DATA_VALUE_PTR(32U, (void *)
          chartInstance->c81_state_RightButton);
        _SFD_SET_DATA_VALUE_PTR(93U, (void *)
          &chartInstance->c81_RIGHT_BUTTON_MASK);
        _SFD_SET_DATA_VALUE_PTR(83U, (void *)
          &chartInstance->c81_LEFT_BUTTON_PRESS);
        _SFD_SET_DATA_VALUE_PTR(33U, (void *)chartInstance->c81_enable_RightLeft);
        _SFD_SET_DATA_VALUE_PTR(90U, (void *)&chartInstance->c81_NON_FUNCTIONAL);
        _SFD_SET_DATA_VALUE_PTR(16U, (void *)chartInstance->c81_state_Detent);
        _SFD_SET_DATA_VALUE_PTR(39U, (void *)
          &chartInstance->c81_CD_AUX_DETENT_FLASH_TIME);
        _SFD_SET_DATA_VALUE_PTR(76U, (void *)&chartInstance->c81_ERR_DETENT);
        _SFD_SET_DATA_VALUE_PTR(63U, (void *)&chartInstance->c81_DISPLAY_HOLD);
        _SFD_SET_DATA_VALUE_PTR(50U, (void *)&chartInstance->c81_DISPLAY_AUX);
        _SFD_SET_DATA_VALUE_PTR(38U, (void *)
          &chartInstance->c81_CD_AUX_DETENT_CYCLE_TIME);
        _SFD_SET_DATA_VALUE_PTR(17U, (void *)
          chartInstance->c81_state_DetentEnable);
        _SFD_SET_DATA_VALUE_PTR(98U, (void *)
          chartInstance->c81__indexee_JobClockLHP_address);
        _SFD_SET_DATA_VALUE_PTR(65U, (void *)
          &chartInstance->c81_DISPLAY_JOB_CLOCK_1);
        _SFD_SET_DATA_VALUE_PTR(66U, (void *)
          &chartInstance->c81_DISPLAY_JOB_CLOCK_2);
        _SFD_SET_DATA_VALUE_PTR(91U, (void *)&chartInstance->c81_NORMAL);
        _SFD_SET_DATA_VALUE_PTR(52U, (void *)
          &chartInstance->c81_DISPLAY_CAN_THROTTLE_DIAG);
        _SFD_SET_DATA_VALUE_PTR(41U, (void *)
          &chartInstance->c81_CD_CAN_THROTTLE_CAL_DIAG_TIME);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)
          &chartInstance->c81_prev_InfoSecondary);
        _SFD_SET_DATA_VALUE_PTR(68U, (void *)
          &chartInstance->c81_DISPLAY_PRIMARY_INACTIVE);
        _SFD_SET_DATA_VALUE_PTR(75U, (void *)&chartInstance->c81_ENGINE_CRANKING);
        _SFD_SET_DATA_VALUE_PTR(18U, (void *)
          chartInstance->c81_state_CANThrottleCalDiag);
        _SFD_SET_DATA_VALUE_PTR(96U, (void *)
          chartInstance->c81_ee_DeluxeG5_address);
        _SFD_SET_DATA_VALUE_PTR(47U, (void *)&chartInstance->c81_CD_HOT_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(19U, (void *)chartInstance->c81_state_TC);
        _SFD_SET_DATA_VALUE_PTR(86U, (void *)&chartInstance->c81_LOW);
        _SFD_SET_DATA_VALUE_PTR(78U, (void *)&chartInstance->c81_EXTREMELY_LOW);
        _SFD_SET_DATA_VALUE_PTR(77U, (void *)&chartInstance->c81_EVENT);
        _SFD_SET_DATA_VALUE_PTR(53U, (void *)&chartInstance->c81_DISPLAY_COLD);
        _SFD_SET_DATA_VALUE_PTR(61U, (void *)
          &chartInstance->c81_DISPLAY_FLASH_COLD);
        _SFD_SET_DATA_VALUE_PTR(37U, (void *)
          &chartInstance->c81_CD_AUTO_DISPLAY_FAULT_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(36U, (void *)
          &chartInstance->c81_CD_AUTO_DISPLAY_FAULT_DEBOUNCE_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(99U, (void *)
          chartInstance->c81__indexflag_StdActiveWarn_address);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)&chartInstance->c81_debounceCode);
        _SFD_SET_DATA_VALUE_PTR(20U, (void *)chartInstance->c81_KSSDisplayState);
        _SFD_SET_DATA_VALUE_PTR(21U, (void *)
          chartInstance->c81_state_KeylessPanel);
        _SFD_SET_DATA_VALUE_PTR(22U, (void *)
          chartInstance->c81_state_MachineLock);
        _SFD_SET_DATA_VALUE_PTR(23U, (void *)chartInstance->c81_cmd_SecondAux);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)&chartInstance->c81_prev_SecondAux);
        _SFD_SET_DATA_VALUE_PTR(24U, (void *)
          chartInstance->c81_fallingedge_SecondAux);
        _SFD_SET_DATA_VALUE_PTR(49U, (void *)
          &chartInstance->c81_CD_SECOND_AUX_OFFSET_DISP_TIME);
        _SFD_SET_DATA_VALUE_PTR(67U, (void *)&chartInstance->c81_DISPLAY_OFFSET);
        _SFD_SET_DATA_VALUE_PTR(70U, (void *)
          &chartInstance->c81_DISPLAY_SERVICE_CLOCK);
        _SFD_SET_DATA_VALUE_PTR(42U, (void *)
          &chartInstance->c81_CD_DELUXE_GEN5_5_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(40U, (void *)&chartInstance->c81_CD_AUX_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(35U, (void *)
          &chartInstance->c81_AUX_EMEA_CONTROLS);
        _SFD_SET_DATA_VALUE_PTR(25U, (void *)
          chartInstance->c81_mode_ControlChange);
        _SFD_SET_DATA_VALUE_PTR(46U, (void *)
          &chartInstance->c81_CD_EMEA_CONTROLS_DISPLAY_TIME);
        _SFD_SET_DATA_VALUE_PTR(48U, (void *)
          &chartInstance->c81_CD_SECOND_AUX_FUNCTION);
        _SFD_SET_DATA_VALUE_PTR(56U, (void *)
          &chartInstance->c81_DISPLAY_EMEA_CONTROLS);
        _SFD_SET_DATA_VALUE_PTR(26U, (void *)chartInstance->c81_mode_LeftControl);
        _SFD_SET_DATA_VALUE_PTR(27U, (void *)
          chartInstance->c81_mode_RightControl);
        _SFD_SET_DATA_VALUE_PTR(87U, (void *)&chartInstance->c81_MODE_LEFT_NONE);
        _SFD_SET_DATA_VALUE_PTR(88U, (void *)&chartInstance->c81_MODE_RIGHT_NONE);
        _SFD_SET_DATA_VALUE_PTR(45U, (void *)
          &chartInstance->c81_CD_EMEA_CONTROLS_DISPLAY_MODE);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "somr7G2gpx595q6hnPmbO2B";
}

static void sf_opaque_initialize_c81_MX_Gtwy_Control(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc81_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c81_MX_Gtwy_Control((SFc81_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
  initialize_c81_MX_Gtwy_Control((SFc81_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c81_MX_Gtwy_Control(void *chartInstanceVar)
{
  enable_c81_MX_Gtwy_Control((SFc81_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c81_MX_Gtwy_Control(void *chartInstanceVar)
{
  disable_c81_MX_Gtwy_Control((SFc81_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c81_MX_Gtwy_Control(void *chartInstanceVar)
{
  sf_gateway_c81_MX_Gtwy_Control((SFc81_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c81_MX_Gtwy_Control(SimStruct* S)
{
  return get_sim_state_c81_MX_Gtwy_Control((SFc81_MX_Gtwy_ControlInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c81_MX_Gtwy_Control(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c81_MX_Gtwy_Control((SFc81_MX_Gtwy_ControlInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c81_MX_Gtwy_Control(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc81_MX_Gtwy_ControlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MX_Gtwy_Control_optimization_info();
    }

    finalize_c81_MX_Gtwy_Control((SFc81_MX_Gtwy_ControlInstanceStruct*)
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
  initSimStructsc81_MX_Gtwy_Control((SFc81_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c81_MX_Gtwy_Control(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c81_MX_Gtwy_Control((SFc81_MX_Gtwy_ControlInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c81_MX_Gtwy_Control(SimStruct *S)
{
  /* Actual parameters from chart:
     ACTIVE AUX_EMEA_CONTROLS CD_AUTO_DISPLAY_FAULT_DEBOUNCE_ACTIVE CD_AUTO_DISPLAY_FAULT_FUNCTION CD_AUX_DETENT_CYCLE_TIME CD_AUX_DETENT_FLASH_TIME CD_AUX_FUNCTION CD_CAN_THROTTLE_CAL_DIAG_TIME CD_DELUXE_GEN5_5_FUNCTION CD_DISPLAY_SERVICE_CLOCK_ALARM_TIME CD_DISPLAY_SHUTDOWN_TIME CD_EMEA_CONTROLS_DISPLAY_MODE CD_EMEA_CONTROLS_DISPLAY_TIME CD_HOT_FUNCTION CD_SECOND_AUX_FUNCTION CD_SECOND_AUX_OFFSET_DISP_TIME DISPLAY_AUX DISPLAY_BATTERY_VOLTAGE DISPLAY_CAN_THROTTLE_DIAG DISPLAY_COLD DISPLAY_DELUXE_ERROR DISPLAY_ECT DISPLAY_EMEA_CONTROLS DISPLAY_ENGINE_HOURS DISPLAY_ENGINE_RPM DISPLAY_EOP DISPLAY_ERROR_CODES DISPLAY_FLASH_COLD DISPLAY_GLOW_PLUGS DISPLAY_HOLD DISPLAY_HOT DISPLAY_JOB_CLOCK_1 DISPLAY_JOB_CLOCK_2 DISPLAY_OFFSET DISPLAY_PRIMARY_INACTIVE DISPLAY_SECOND_AUX DISPLAY_SERVICE_CLOCK DISPLAY_SERVICE_CLOCK_ALARM DISPLAY_SERVICE_CLOCK_RESET DISPLAY_SHUTDOWN DISPLAY_VERSION ENGINE_CRANKING ERR_DETENT EVENT EXTREMELY_LOW INACTIVE INFO_BUTTON_MASK INFO_BUTTON_PRESS LEFT_BUTTON_MASK LEFT_BUTTON_PRESS LIGHT_BUTTON_MASK LIGHT_BUTTON_PRESS LOW MODE_LEFT_NONE MODE_RIGHT_NONE MULTIPLE NON_FUNCTIONAL NORMAL NO_COMMUNICATION RIGHT_BUTTON_MASK RIGHT_BUTTON_PRESS SHUTDOWN
   */
  const char_T *rtParamNames[] = { "ACTIVE", "AUX_EMEA_CONTROLS",
    "CD_AUTO_DISPLAY_FAULT_DEBOUNCE_ACTIVE", "CD_AUTO_DISPLAY_FAULT_FUNCTION",
    "CD_AUX_DETENT_CYCLE_TIME", "CD_AUX_DETENT_FLASH_TIME", "CD_AUX_FUNCTION",
    "CD_CAN_THROTTLE_CAL_DIAG_TIME", "CD_DELUXE_GEN5_5_FUNCTION",
    "CD_DISPLAY_SERVICE_CLOCK_ALARM_TIME", "CD_DISPLAY_SHUTDOWN_TIME",
    "CD_EMEA_CONTROLS_DISPLAY_MODE", "CD_EMEA_CONTROLS_DISPLAY_TIME",
    "CD_HOT_FUNCTION", "CD_SECOND_AUX_FUNCTION",
    "CD_SECOND_AUX_OFFSET_DISP_TIME", "DISPLAY_AUX", "DISPLAY_BATTERY_VOLTAGE",
    "DISPLAY_CAN_THROTTLE_DIAG", "DISPLAY_COLD", "DISPLAY_DELUXE_ERROR",
    "DISPLAY_ECT", "DISPLAY_EMEA_CONTROLS", "DISPLAY_ENGINE_HOURS",
    "DISPLAY_ENGINE_RPM", "DISPLAY_EOP", "DISPLAY_ERROR_CODES",
    "DISPLAY_FLASH_COLD", "DISPLAY_GLOW_PLUGS", "DISPLAY_HOLD", "DISPLAY_HOT",
    "DISPLAY_JOB_CLOCK_1", "DISPLAY_JOB_CLOCK_2", "DISPLAY_OFFSET",
    "DISPLAY_PRIMARY_INACTIVE", "DISPLAY_SECOND_AUX", "DISPLAY_SERVICE_CLOCK",
    "DISPLAY_SERVICE_CLOCK_ALARM", "DISPLAY_SERVICE_CLOCK_RESET",
    "DISPLAY_SHUTDOWN", "DISPLAY_VERSION", "ENGINE_CRANKING", "ERR_DETENT",
    "EVENT", "EXTREMELY_LOW", "INACTIVE", "INFO_BUTTON_MASK",
    "INFO_BUTTON_PRESS", "LEFT_BUTTON_MASK", "LEFT_BUTTON_PRESS",
    "LIGHT_BUTTON_MASK", "LIGHT_BUTTON_PRESS", "LOW", "MODE_LEFT_NONE",
    "MODE_RIGHT_NONE", "MULTIPLE", "NON_FUNCTIONAL", "NORMAL",
    "NO_COMMUNICATION", "RIGHT_BUTTON_MASK", "RIGHT_BUTTON_PRESS", "SHUTDOWN" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_UINT8);

  /* registration for AUX_EMEA_CONTROLS*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT8);

  /* registration for CD_AUTO_DISPLAY_FAULT_DEBOUNCE_ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT16);

  /* registration for CD_AUTO_DISPLAY_FAULT_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_UINT8);

  /* registration for CD_AUX_DETENT_CYCLE_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_UINT16);

  /* registration for CD_AUX_DETENT_FLASH_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_UINT16);

  /* registration for CD_AUX_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_UINT8);

  /* registration for CD_CAN_THROTTLE_CAL_DIAG_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 7, 7, rtParamNames[7], SS_UINT16);

  /* registration for CD_DELUXE_GEN5_5_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 8, 8, rtParamNames[8], SS_UINT8);

  /* registration for CD_DISPLAY_SERVICE_CLOCK_ALARM_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 9, 9, rtParamNames[9], SS_UINT16);

  /* registration for CD_DISPLAY_SHUTDOWN_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 10, 10, rtParamNames[10], SS_UINT16);

  /* registration for CD_EMEA_CONTROLS_DISPLAY_MODE*/
  ssRegDlgParamAsRunTimeParam(S, 11, 11, rtParamNames[11], SS_UINT8);

  /* registration for CD_EMEA_CONTROLS_DISPLAY_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 12, 12, rtParamNames[12], SS_UINT16);

  /* registration for CD_HOT_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 13, 13, rtParamNames[13], SS_UINT16);

  /* registration for CD_SECOND_AUX_FUNCTION*/
  ssRegDlgParamAsRunTimeParam(S, 14, 14, rtParamNames[14], SS_UINT8);

  /* registration for CD_SECOND_AUX_OFFSET_DISP_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 15, 15, rtParamNames[15], SS_UINT16);

  /* registration for DISPLAY_AUX*/
  ssRegDlgParamAsRunTimeParam(S, 16, 16, rtParamNames[16], SS_UINT8);

  /* registration for DISPLAY_BATTERY_VOLTAGE*/
  ssRegDlgParamAsRunTimeParam(S, 17, 17, rtParamNames[17], SS_UINT8);

  /* registration for DISPLAY_CAN_THROTTLE_DIAG*/
  ssRegDlgParamAsRunTimeParam(S, 18, 18, rtParamNames[18], SS_UINT8);

  /* registration for DISPLAY_COLD*/
  ssRegDlgParamAsRunTimeParam(S, 19, 19, rtParamNames[19], SS_UINT8);

  /* registration for DISPLAY_DELUXE_ERROR*/
  ssRegDlgParamAsRunTimeParam(S, 20, 20, rtParamNames[20], SS_UINT8);

  /* registration for DISPLAY_ECT*/
  ssRegDlgParamAsRunTimeParam(S, 21, 21, rtParamNames[21], SS_UINT8);

  /* registration for DISPLAY_EMEA_CONTROLS*/
  ssRegDlgParamAsRunTimeParam(S, 22, 22, rtParamNames[22], SS_UINT8);

  /* registration for DISPLAY_ENGINE_HOURS*/
  ssRegDlgParamAsRunTimeParam(S, 23, 23, rtParamNames[23], SS_UINT8);

  /* registration for DISPLAY_ENGINE_RPM*/
  ssRegDlgParamAsRunTimeParam(S, 24, 24, rtParamNames[24], SS_UINT8);

  /* registration for DISPLAY_EOP*/
  ssRegDlgParamAsRunTimeParam(S, 25, 25, rtParamNames[25], SS_UINT8);

  /* registration for DISPLAY_ERROR_CODES*/
  ssRegDlgParamAsRunTimeParam(S, 26, 26, rtParamNames[26], SS_UINT8);

  /* registration for DISPLAY_FLASH_COLD*/
  ssRegDlgParamAsRunTimeParam(S, 27, 27, rtParamNames[27], SS_UINT8);

  /* registration for DISPLAY_GLOW_PLUGS*/
  ssRegDlgParamAsRunTimeParam(S, 28, 28, rtParamNames[28], SS_UINT8);

  /* registration for DISPLAY_HOLD*/
  ssRegDlgParamAsRunTimeParam(S, 29, 29, rtParamNames[29], SS_UINT8);

  /* registration for DISPLAY_HOT*/
  ssRegDlgParamAsRunTimeParam(S, 30, 30, rtParamNames[30], SS_UINT8);

  /* registration for DISPLAY_JOB_CLOCK_1*/
  ssRegDlgParamAsRunTimeParam(S, 31, 31, rtParamNames[31], SS_UINT8);

  /* registration for DISPLAY_JOB_CLOCK_2*/
  ssRegDlgParamAsRunTimeParam(S, 32, 32, rtParamNames[32], SS_UINT8);

  /* registration for DISPLAY_OFFSET*/
  ssRegDlgParamAsRunTimeParam(S, 33, 33, rtParamNames[33], SS_UINT8);

  /* registration for DISPLAY_PRIMARY_INACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 34, 34, rtParamNames[34], SS_UINT8);

  /* registration for DISPLAY_SECOND_AUX*/
  ssRegDlgParamAsRunTimeParam(S, 35, 35, rtParamNames[35], SS_UINT8);

  /* registration for DISPLAY_SERVICE_CLOCK*/
  ssRegDlgParamAsRunTimeParam(S, 36, 36, rtParamNames[36], SS_UINT8);

  /* registration for DISPLAY_SERVICE_CLOCK_ALARM*/
  ssRegDlgParamAsRunTimeParam(S, 37, 37, rtParamNames[37], SS_UINT8);

  /* registration for DISPLAY_SERVICE_CLOCK_RESET*/
  ssRegDlgParamAsRunTimeParam(S, 38, 38, rtParamNames[38], SS_UINT8);

  /* registration for DISPLAY_SHUTDOWN*/
  ssRegDlgParamAsRunTimeParam(S, 39, 39, rtParamNames[39], SS_UINT8);

  /* registration for DISPLAY_VERSION*/
  ssRegDlgParamAsRunTimeParam(S, 40, 40, rtParamNames[40], SS_UINT8);

  /* registration for ENGINE_CRANKING*/
  ssRegDlgParamAsRunTimeParam(S, 41, 41, rtParamNames[41], SS_UINT8);

  /* registration for ERR_DETENT*/
  ssRegDlgParamAsRunTimeParam(S, 42, 42, rtParamNames[42], SS_UINT8);

  /* registration for EVENT*/
  ssRegDlgParamAsRunTimeParam(S, 43, 43, rtParamNames[43], SS_UINT8);

  /* registration for EXTREMELY_LOW*/
  ssRegDlgParamAsRunTimeParam(S, 44, 44, rtParamNames[44], SS_UINT8);

  /* registration for INACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 45, 45, rtParamNames[45], SS_UINT8);

  /* registration for INFO_BUTTON_MASK*/
  ssRegDlgParamAsRunTimeParam(S, 46, 46, rtParamNames[46], SS_UINT8);

  /* registration for INFO_BUTTON_PRESS*/
  ssRegDlgParamAsRunTimeParam(S, 47, 47, rtParamNames[47], SS_UINT8);

  /* registration for LEFT_BUTTON_MASK*/
  ssRegDlgParamAsRunTimeParam(S, 48, 48, rtParamNames[48], SS_UINT8);

  /* registration for LEFT_BUTTON_PRESS*/
  ssRegDlgParamAsRunTimeParam(S, 49, 49, rtParamNames[49], SS_UINT8);

  /* registration for LIGHT_BUTTON_MASK*/
  ssRegDlgParamAsRunTimeParam(S, 50, 50, rtParamNames[50], SS_UINT8);

  /* registration for LIGHT_BUTTON_PRESS*/
  ssRegDlgParamAsRunTimeParam(S, 51, 51, rtParamNames[51], SS_UINT8);

  /* registration for LOW*/
  ssRegDlgParamAsRunTimeParam(S, 52, 52, rtParamNames[52], SS_UINT8);

  /* registration for MODE_LEFT_NONE*/
  ssRegDlgParamAsRunTimeParam(S, 53, 53, rtParamNames[53], SS_UINT8);

  /* registration for MODE_RIGHT_NONE*/
  ssRegDlgParamAsRunTimeParam(S, 54, 54, rtParamNames[54], SS_UINT8);

  /* registration for MULTIPLE*/
  ssRegDlgParamAsRunTimeParam(S, 55, 55, rtParamNames[55], SS_UINT8);

  /* registration for NON_FUNCTIONAL*/
  ssRegDlgParamAsRunTimeParam(S, 56, 56, rtParamNames[56], SS_UINT8);

  /* registration for NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 57, 57, rtParamNames[57], SS_UINT8);

  /* registration for NO_COMMUNICATION*/
  ssRegDlgParamAsRunTimeParam(S, 58, 58, rtParamNames[58], SS_UINT8);

  /* registration for RIGHT_BUTTON_MASK*/
  ssRegDlgParamAsRunTimeParam(S, 59, 59, rtParamNames[59], SS_UINT8);

  /* registration for RIGHT_BUTTON_PRESS*/
  ssRegDlgParamAsRunTimeParam(S, 60, 60, rtParamNames[60], SS_UINT8);

  /* registration for SHUTDOWN*/
  ssRegDlgParamAsRunTimeParam(S, 61, 61, rtParamNames[61], SS_UINT8);
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
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MX_Gtwy_Control_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      81);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,81,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 81);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,81);
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
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,81,17);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,81,6);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=6; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 17; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,81);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2483444064U));
  ssSetChecksum1(S,(4125282489U));
  ssSetChecksum2(S,(3276607282U));
  ssSetChecksum3(S,(2201903562U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c81_MX_Gtwy_Control(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c81_MX_Gtwy_Control(SimStruct *S)
{
  SFc81_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc81_MX_Gtwy_ControlInstanceStruct *)utMalloc(sizeof
    (SFc81_MX_Gtwy_ControlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc81_MX_Gtwy_ControlInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c81_MX_Gtwy_Control;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c81_MX_Gtwy_Control;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c81_MX_Gtwy_Control;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c81_MX_Gtwy_Control;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c81_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c81_MX_Gtwy_Control;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c81_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c81_MX_Gtwy_Control;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c81_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlStart = mdlStart_c81_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c81_MX_Gtwy_Control;
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
  mdl_start_c81_MX_Gtwy_Control(chartInstance);
}

void c81_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c81_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c81_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c81_MX_Gtwy_Control(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c81_MX_Gtwy_Control_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
