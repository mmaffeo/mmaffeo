/* Include files */

#include "MX_Gtwy_Control_sfun.h"
#include "c100_MX_Gtwy_Control.h"
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
#define c100_IN_NO_ACTIVE_CHILD        ((uint8_T)0U)
#define c100_IN_Init                   ((uint8_T)1U)
#define c100_IN_Normal                 ((uint8_T)2U)
#define c100_IN_OffsetCheck            ((uint8_T)3U)
#define c100_IN_ReminderOfLastState    ((uint8_T)4U)
#define c100_IN_A2FLASH_A1FLASH        ((uint8_T)1U)
#define c100_IN_A2FLASH_A4FLASH        ((uint8_T)2U)
#define c100_IN_A4FLASH_A1FLASH        ((uint8_T)3U)
#define c100_IN_A4FLASH_OF             ((uint8_T)4U)
#define c100_IN_Default                ((uint8_T)5U)
#define c100_IN_OF_A1FLASH             ((uint8_T)6U)
#define c100_IN_OF_A4FLASH             ((uint8_T)7U)
#define c100_IN_GLOW_OFF               ((uint8_T)1U)
#define c100_IN_OFF                    ((uint8_T)2U)
#define c100_IN_ON                     ((uint8_T)3U)
#define c100_b_IN_ON                   ((uint8_T)2U)
#define c100_IN_ON1                    ((uint8_T)3U)
#define c100_IN_Expired                ((uint8_T)1U)
#define c100_IN_GlowCycle1             ((uint8_T)2U)
#define c100_IN_GlowCycle2             ((uint8_T)3U)
#define c100_IN_GlowOff                ((uint8_T)4U)
#define c100_IN_GlowOff1               ((uint8_T)5U)
#define c100_IN_No_Glow                ((uint8_T)6U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void initialize_params_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void enable_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void disable_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c100_update_debugger_state_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void set_sim_state_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c100_st);
static void c100_set_sim_state_side_effects_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void finalize_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void sf_gateway_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void mdl_start_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct *
  chartInstance);
static void c100_chartstep_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void initSimStructsc100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c100_ReminderOfLastState(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c100_exit_internal_ReminderOfLastState
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c100_enter_internal_Flasher(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c100_Flasher(SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c100_exit_internal_Flasher(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void c100_OF_A1FLASH(SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c100_OF_A4FLASH(SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void c100_A4FLASH_OF(SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c100_machineNumber, uint32_T
  c100_chartNumber, uint32_T c100_instanceNumber);
static const mxArray *c100_sf_marshallOut(void *chartInstanceVoid, void
  *c100_inData);
static int32_T c100_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_u, const emlrtMsgIdentifier *c100_parentId);
static void c100_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c100_mxArrayInData, const char_T *c100_varName, void *c100_outData);
static const mxArray *c100_b_sf_marshallOut(void *chartInstanceVoid, void
  *c100_inData);
static uint8_T c100_b_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_b_tp_Normal, const char_T *c100_identifier);
static uint8_T c100_c_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_u, const emlrtMsgIdentifier *c100_parentId);
static void c100_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c100_mxArrayInData, const char_T *c100_varName, void *c100_outData);
static const mxArray *c100_c_sf_marshallOut(void *chartInstanceVoid, void
  *c100_inData);
static boolean_T c100_d_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_b_flag_AuxEnableFlash, const char_T
  *c100_identifier);
static boolean_T c100_e_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_u, const emlrtMsgIdentifier *c100_parentId);
static void c100_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c100_mxArrayInData, const char_T *c100_varName, void *c100_outData);
static const mxArray *c100_d_sf_marshallOut(void *chartInstanceVoid, void
  *c100_inData);
static uint16_T c100_f_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_b_CD_EMEA_CONTROLS_FLASH_TIME, const
  char_T *c100_identifier);
static uint16_T c100_g_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_u, const emlrtMsgIdentifier *c100_parentId);
static void c100_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c100_mxArrayInData, const char_T *c100_varName, void *c100_outData);
static const mxArray *c100_h_emlrt_marshallIn
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray
   *c100_b_setSimStateSideEffectsInfo, const char_T *c100_identifier);
static const mxArray *c100_i_emlrt_marshallIn
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c100_u,
   const emlrtMsgIdentifier *c100_parentId);
static const mxArray *sf_get_hover_data_for_msg
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c100_ssid);
static void c100_init_sf_message_store_memory
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance);
static int32_T c100__s32_add__(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, int32_T c100_b, int32_T c100_c, uint32_T c100_ssid_src_loc,
  int32_T c100_offset_src_loc, int32_T c100_length_src_loc);
static uint16_T c100__u16_u32_(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c100_b, uint32_T c100_ssid_src_loc, int32_T
  c100_offset_src_loc, int32_T c100_length_src_loc);
static uint8_T c100_get_ee_ControlMode(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c100_elementIndex);
static void c100_set_ee_ControlMode(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c100_elementIndex, uint8_T c100_elementValue);
static uint8_T *c100_access_ee_ControlMode(SFc100_MX_Gtwy_ControlInstanceStruct *
  chartInstance, uint32_T c100_rdOnly);
static void init_dsm_address_info(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc100_MX_Gtwy_Control(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c100_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c100_doSetSimStateSideEffects = 0U;
  chartInstance->c100_setSimStateSideEffectsInfo = NULL;
  chartInstance->c100_tp_Init = 0U;
  chartInstance->c100_tp_Normal = 0U;
  chartInstance->c100_tp_OffsetCheck = 0U;
  chartInstance->c100_tp_ReminderOfLastState = 0U;
  chartInstance->c100_is_active_FlashTimer = 0U;
  chartInstance->c100_is_FlashTimer = c100_IN_NO_ACTIVE_CHILD;
  chartInstance->c100_tp_FlashTimer = 0U;
  chartInstance->c100_tp_Expired = 0U;
  chartInstance->c100_tp_GlowCycle1 = 0U;
  chartInstance->c100_tp_GlowCycle2 = 0U;
  chartInstance->c100_tp_GlowOff = 0U;
  chartInstance->c100_tp_GlowOff1 = 0U;
  chartInstance->c100_tp_No_Glow = 0U;
  chartInstance->c100_is_active_Flasher = 0U;
  chartInstance->c100_is_Flasher = c100_IN_NO_ACTIVE_CHILD;
  chartInstance->c100_tp_Flasher = 0U;
  chartInstance->c100_is_A2FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
  chartInstance->c100_tp_A2FLASH_A1FLASH = 0U;
  chartInstance->c100_c_tp_GLOW_OFF = 0U;
  chartInstance->c100_c_tp_OFF = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_c_tp_ON = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_is_A2FLASH_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
  chartInstance->c100_tp_A2FLASH_A4FLASH = 0U;
  chartInstance->c100_d_tp_GLOW_OFF = 0U;
  chartInstance->c100_d_tp_OFF = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_d_tp_ON = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_is_A4FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
  chartInstance->c100_tp_A4FLASH_A1FLASH = 0U;
  chartInstance->c100_f_tp_GLOW_OFF = 0U;
  chartInstance->c100_e_tp_OFF = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_f_tp_ON = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_is_A4FLASH_OF = c100_IN_NO_ACTIVE_CHILD;
  chartInstance->c100_tp_A4FLASH_OF = 0U;
  chartInstance->c100_e_tp_GLOW_OFF = 0U;
  chartInstance->c100_e_tp_ON = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_tp_ON1 = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_tp_Default = 0U;
  chartInstance->c100_is_OF_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
  chartInstance->c100_tp_OF_A1FLASH = 0U;
  chartInstance->c100_tp_GLOW_OFF = 0U;
  chartInstance->c100_tp_OFF = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_tp_ON = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_is_OF_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
  chartInstance->c100_tp_OF_A4FLASH = 0U;
  chartInstance->c100_b_tp_GLOW_OFF = 0U;
  chartInstance->c100_b_tp_OFF = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_b_tp_ON = 0U;
  chartInstance->c100_temporalCounter_i1 = 0U;
  chartInstance->c100_is_active_c100_MX_Gtwy_Control = 0U;
  chartInstance->c100_is_c100_MX_Gtwy_Control = c100_IN_NO_ACTIVE_CHILD;
  chartInstance->c100_flash_timer = 0U;
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c100_flash_timer, 0U);
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c100_disp_LeftControl = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c100_disp_RightControl = 0U;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *chartInstance->c100_flag_AuxEnableFlash = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_flag_AuxEnableFlash, 11U);
  }
}

static void initialize_params_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  real_T c100_d0;
  real_T c100_d1;
  real_T c100_d2;
  real_T c100_d3;
  real_T c100_d4;
  real_T c100_d5;
  real_T c100_d6;
  real_T c100_d7;
  real_T c100_d8;
  real_T c100_d9;
  real_T c100_d10;
  real_T c100_d11;
  real_T c100_d12;
  real_T c100_d13;
  real_T c100_d14;
  real_T c100_d15;
  real_T c100_d16;
  real_T c100_d17;
  real_T c100_d18;
  real_T c100_d19;
  real_T c100_d20;
  real_T c100_d21;
  real_T c100_d22;
  real_T c100_d23;
  real_T c100_d24;
  real_T c100_d25;
  sf_mex_import_named("CD_EMEA_CONTROLS_FLASH_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 1, 0), &c100_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME = (uint16_T)c100_d0;
  sf_mex_import_named("CD_EMEA_CONTROLS_REMINDER_TIME", sf_mex_get_sfun_param
                      (chartInstance->S, 3, 0), &c100_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_CD_EMEA_CONTROLS_REMINDER_TIME = (uint16_T)c100_d1;
  sf_mex_import_named("EE_LT_OF_NA", sf_mex_get_sfun_param(chartInstance->S, 8,
    0), &c100_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_EE_LT_OF_NA = (uint8_T)c100_d2;
  sf_mex_import_named("EE_NA_NA", sf_mex_get_sfun_param(chartInstance->S, 9, 0),
                      &c100_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_EE_NA_NA = (uint8_T)c100_d3;
  sf_mex_import_named("EE_RT_NA_OF", sf_mex_get_sfun_param(chartInstance->S, 13,
    0), &c100_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_EE_RT_NA_OF = (uint8_T)c100_d4;
  sf_mex_import_named("INACTIVE", sf_mex_get_sfun_param(chartInstance->S, 15, 0),
                      &c100_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_INACTIVE = (uint8_T)c100_d5;
  sf_mex_import_named("MODE_LEFT_AUX2", sf_mex_get_sfun_param(chartInstance->S,
    16, 0), &c100_d6, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_MODE_LEFT_AUX2 = (uint8_T)c100_d6;
  sf_mex_import_named("MODE_LEFT_AUX4", sf_mex_get_sfun_param(chartInstance->S,
    17, 0), &c100_d7, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_MODE_LEFT_AUX4 = (uint8_T)c100_d7;
  sf_mex_import_named("MODE_LEFT_NONE", sf_mex_get_sfun_param(chartInstance->S,
    18, 0), &c100_d8, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_MODE_LEFT_NONE = (uint8_T)c100_d8;
  sf_mex_import_named("MODE_LEFT_OFFSET", sf_mex_get_sfun_param(chartInstance->S,
    19, 0), &c100_d9, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_MODE_LEFT_OFFSET = (uint8_T)c100_d9;
  sf_mex_import_named("MODE_RIGHT_AUX1", sf_mex_get_sfun_param(chartInstance->S,
    20, 0), &c100_d10, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_MODE_RIGHT_AUX1 = (uint8_T)c100_d10;
  sf_mex_import_named("MODE_RIGHT_AUX4", sf_mex_get_sfun_param(chartInstance->S,
    21, 0), &c100_d11, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_MODE_RIGHT_AUX4 = (uint8_T)c100_d11;
  sf_mex_import_named("MODE_RIGHT_NONE", sf_mex_get_sfun_param(chartInstance->S,
    22, 0), &c100_d12, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_MODE_RIGHT_NONE = (uint8_T)c100_d12;
  sf_mex_import_named("MODE_RIGHT_OFFSET", sf_mex_get_sfun_param
                      (chartInstance->S, 23, 0), &c100_d13, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_MODE_RIGHT_OFFSET = (uint8_T)c100_d13;
  sf_mex_import_named("EE_LT_A2_A1", sf_mex_get_sfun_param(chartInstance->S, 4,
    0), &c100_d14, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_EE_LT_A2_A1 = (uint8_T)c100_d14;
  sf_mex_import_named("EE_LT_A2_A4", sf_mex_get_sfun_param(chartInstance->S, 5,
    0), &c100_d15, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_EE_LT_A2_A4 = (uint8_T)c100_d15;
  sf_mex_import_named("EE_LT_OF_A1", sf_mex_get_sfun_param(chartInstance->S, 6,
    0), &c100_d16, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_EE_LT_OF_A1 = (uint8_T)c100_d16;
  sf_mex_import_named("EE_LT_OF_A4", sf_mex_get_sfun_param(chartInstance->S, 7,
    0), &c100_d17, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_EE_LT_OF_A4 = (uint8_T)c100_d17;
  sf_mex_import_named("EE_RT_A2_A1", sf_mex_get_sfun_param(chartInstance->S, 10,
    0), &c100_d18, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_EE_RT_A2_A1 = (uint8_T)c100_d18;
  sf_mex_import_named("EE_RT_A4_A1", sf_mex_get_sfun_param(chartInstance->S, 11,
    0), &c100_d19, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_EE_RT_A4_A1 = (uint8_T)c100_d19;
  sf_mex_import_named("EE_RT_A4_OF", sf_mex_get_sfun_param(chartInstance->S, 12,
    0), &c100_d20, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_EE_RT_A4_OF = (uint8_T)c100_d20;
  sf_mex_import_named("CD_EMEA_CONTROLS_OPTION_A", sf_mex_get_sfun_param
                      (chartInstance->S, 2, 0), &c100_d21, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_CD_EMEA_CONTROLS_OPTION_A = (uint8_T)c100_d21;
  sf_mex_import_named("NON_FUNCTIONAL", sf_mex_get_sfun_param(chartInstance->S,
    24, 0), &c100_d22, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_NON_FUNCTIONAL = (uint8_T)c100_d22;
  sf_mex_import_named("ACTIVE", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      &c100_d23, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_ACTIVE = (uint8_T)c100_d23;
  sf_mex_import_named("ENGINE_CRANKING", sf_mex_get_sfun_param(chartInstance->S,
    14, 0), &c100_d24, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_ENGINE_CRANKING = (uint8_T)c100_d24;
  sf_mex_import_named("SYS_NORMAL", sf_mex_get_sfun_param(chartInstance->S, 25,
    0), &c100_d25, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c100_SYS_NORMAL = (uint8_T)c100_d25;
}

static void enable_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c100_update_debugger_state_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  uint32_T c100_prevAniVal;
  c100_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c100_is_active_c100_MX_Gtwy_Control == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 97U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_c100_MX_Gtwy_Control == c100_IN_Normal) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_c100_MX_Gtwy_Control == c100_IN_Init) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_c100_MX_Gtwy_Control == c100_IN_OffsetCheck) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_c100_MX_Gtwy_Control == c100_IN_ReminderOfLastState)
  {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_active_Flasher == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_Flasher == c100_IN_OF_A1FLASH) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 29U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_OF_A1FLASH == c100_IN_GLOW_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 30U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_OF_A1FLASH == c100_IN_ON) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_OF_A1FLASH == c100_IN_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_Flasher == c100_IN_OF_A4FLASH) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_OF_A4FLASH == c100_IN_GLOW_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 34U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_OF_A4FLASH == c100_IN_ON) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_OF_A4FLASH == c100_IN_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_Flasher == c100_IN_A2FLASH_A1FLASH) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A2FLASH_A1FLASH == c100_IN_GLOW_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A2FLASH_A1FLASH == c100_IN_ON) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A2FLASH_A1FLASH == c100_IN_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_Flasher == c100_IN_A2FLASH_A4FLASH) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A2FLASH_A4FLASH == c100_IN_GLOW_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A2FLASH_A4FLASH == c100_IN_ON) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A2FLASH_A4FLASH == c100_IN_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_Flasher == c100_IN_A4FLASH_OF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A4FLASH_OF == c100_IN_GLOW_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A4FLASH_OF == c100_b_IN_ON) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A4FLASH_OF == c100_IN_ON1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_Flasher == c100_IN_A4FLASH_A1FLASH) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A4FLASH_A1FLASH == c100_IN_GLOW_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A4FLASH_A1FLASH == c100_IN_ON) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_A4FLASH_A1FLASH == c100_IN_OFF) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_Flasher == c100_IN_Default) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 28U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_active_FlashTimer == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_FlashTimer == c100_IN_No_Glow) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_FlashTimer == c100_IN_GlowCycle1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_FlashTimer == c100_IN_GlowOff) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_FlashTimer == c100_IN_GlowCycle2) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_FlashTimer == c100_IN_GlowOff1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c100_sfEvent);
  }

  if (chartInstance->c100_is_FlashTimer == c100_IN_Expired) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c100_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c100_sfEvent);
  }

  _SFD_SET_ANIMATION(c100_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  const mxArray *c100_st;
  const mxArray *c100_y = NULL;
  uint8_T c100_hoistedGlobal;
  const mxArray *c100_b_y = NULL;
  uint8_T c100_b_hoistedGlobal;
  const mxArray *c100_c_y = NULL;
  boolean_T c100_c_hoistedGlobal;
  const mxArray *c100_d_y = NULL;
  uint16_T c100_d_hoistedGlobal;
  const mxArray *c100_e_y = NULL;
  uint8_T c100_e_hoistedGlobal;
  const mxArray *c100_f_y = NULL;
  uint8_T c100_f_hoistedGlobal;
  const mxArray *c100_g_y = NULL;
  uint8_T c100_g_hoistedGlobal;
  const mxArray *c100_h_y = NULL;
  uint8_T c100_h_hoistedGlobal;
  const mxArray *c100_i_y = NULL;
  uint8_T c100_i_hoistedGlobal;
  const mxArray *c100_j_y = NULL;
  uint8_T c100_j_hoistedGlobal;
  const mxArray *c100_k_y = NULL;
  uint8_T c100_k_hoistedGlobal;
  const mxArray *c100_l_y = NULL;
  uint8_T c100_l_hoistedGlobal;
  const mxArray *c100_m_y = NULL;
  uint8_T c100_m_hoistedGlobal;
  const mxArray *c100_n_y = NULL;
  uint8_T c100_n_hoistedGlobal;
  const mxArray *c100_o_y = NULL;
  uint8_T c100_o_hoistedGlobal;
  const mxArray *c100_p_y = NULL;
  uint8_T c100_p_hoistedGlobal;
  const mxArray *c100_q_y = NULL;
  uint16_T c100_q_hoistedGlobal;
  const mxArray *c100_r_y = NULL;
  c100_st = NULL;
  c100_st = NULL;
  c100_y = NULL;
  sf_mex_assign(&c100_y, sf_mex_createcellmatrix(17, 1), false);
  c100_hoistedGlobal = *chartInstance->c100_disp_LeftControl;
  c100_b_y = NULL;
  sf_mex_assign(&c100_b_y, sf_mex_create("y", &c100_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c100_y, 0, c100_b_y);
  c100_b_hoistedGlobal = *chartInstance->c100_disp_RightControl;
  c100_c_y = NULL;
  sf_mex_assign(&c100_c_y, sf_mex_create("y", &c100_b_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 1, c100_c_y);
  c100_c_hoistedGlobal = *chartInstance->c100_flag_AuxEnableFlash;
  c100_d_y = NULL;
  sf_mex_assign(&c100_d_y, sf_mex_create("y", &c100_c_hoistedGlobal, 11, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 2, c100_d_y);
  c100_d_hoistedGlobal = chartInstance->c100_flash_timer;
  c100_e_y = NULL;
  sf_mex_assign(&c100_e_y, sf_mex_create("y", &c100_d_hoistedGlobal, 5, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 3, c100_e_y);
  c100_e_hoistedGlobal = chartInstance->c100_is_active_c100_MX_Gtwy_Control;
  c100_f_y = NULL;
  sf_mex_assign(&c100_f_y, sf_mex_create("y", &c100_e_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 4, c100_f_y);
  c100_f_hoistedGlobal = chartInstance->c100_is_active_Flasher;
  c100_g_y = NULL;
  sf_mex_assign(&c100_g_y, sf_mex_create("y", &c100_f_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 5, c100_g_y);
  c100_g_hoistedGlobal = chartInstance->c100_is_active_FlashTimer;
  c100_h_y = NULL;
  sf_mex_assign(&c100_h_y, sf_mex_create("y", &c100_g_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 6, c100_h_y);
  c100_h_hoistedGlobal = chartInstance->c100_is_c100_MX_Gtwy_Control;
  c100_i_y = NULL;
  sf_mex_assign(&c100_i_y, sf_mex_create("y", &c100_h_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 7, c100_i_y);
  c100_i_hoistedGlobal = chartInstance->c100_is_OF_A1FLASH;
  c100_j_y = NULL;
  sf_mex_assign(&c100_j_y, sf_mex_create("y", &c100_i_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 8, c100_j_y);
  c100_j_hoistedGlobal = chartInstance->c100_is_OF_A4FLASH;
  c100_k_y = NULL;
  sf_mex_assign(&c100_k_y, sf_mex_create("y", &c100_j_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 9, c100_k_y);
  c100_k_hoistedGlobal = chartInstance->c100_is_A2FLASH_A1FLASH;
  c100_l_y = NULL;
  sf_mex_assign(&c100_l_y, sf_mex_create("y", &c100_k_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 10, c100_l_y);
  c100_l_hoistedGlobal = chartInstance->c100_is_A4FLASH_OF;
  c100_m_y = NULL;
  sf_mex_assign(&c100_m_y, sf_mex_create("y", &c100_l_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 11, c100_m_y);
  c100_m_hoistedGlobal = chartInstance->c100_is_A2FLASH_A4FLASH;
  c100_n_y = NULL;
  sf_mex_assign(&c100_n_y, sf_mex_create("y", &c100_m_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 12, c100_n_y);
  c100_n_hoistedGlobal = chartInstance->c100_is_A4FLASH_A1FLASH;
  c100_o_y = NULL;
  sf_mex_assign(&c100_o_y, sf_mex_create("y", &c100_n_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 13, c100_o_y);
  c100_o_hoistedGlobal = chartInstance->c100_is_Flasher;
  c100_p_y = NULL;
  sf_mex_assign(&c100_p_y, sf_mex_create("y", &c100_o_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 14, c100_p_y);
  c100_p_hoistedGlobal = chartInstance->c100_is_FlashTimer;
  c100_q_y = NULL;
  sf_mex_assign(&c100_q_y, sf_mex_create("y", &c100_p_hoistedGlobal, 3, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 15, c100_q_y);
  c100_q_hoistedGlobal = chartInstance->c100_temporalCounter_i1;
  c100_r_y = NULL;
  sf_mex_assign(&c100_r_y, sf_mex_create("y", &c100_q_hoistedGlobal, 5, 0U, 0U,
    0U, 0), false);
  sf_mex_setcell(c100_y, 16, c100_r_y);
  sf_mex_assign(&c100_st, c100_y, false);
  return c100_st;
}

static void set_sim_state_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c100_st)
{
  const mxArray *c100_u;
  c100_u = sf_mex_dup(c100_st);
  *chartInstance->c100_disp_LeftControl = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 0)), "disp_LeftControl");
  *chartInstance->c100_disp_RightControl = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 1)), "disp_RightControl");
  *chartInstance->c100_flag_AuxEnableFlash = c100_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c100_u, 2)), "flag_AuxEnableFlash");
  chartInstance->c100_flash_timer = c100_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 3)), "flash_timer");
  chartInstance->c100_is_active_c100_MX_Gtwy_Control = c100_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c100_u, 4)),
     "is_active_c100_MX_Gtwy_Control");
  chartInstance->c100_is_active_Flasher = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 5)), "is_active_Flasher");
  chartInstance->c100_is_active_FlashTimer = c100_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c100_u, 6)),
     "is_active_FlashTimer");
  chartInstance->c100_is_c100_MX_Gtwy_Control = c100_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c100_u, 7)),
     "is_c100_MX_Gtwy_Control");
  chartInstance->c100_is_OF_A1FLASH = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 8)), "is_OF_A1FLASH");
  chartInstance->c100_is_OF_A4FLASH = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 9)), "is_OF_A4FLASH");
  chartInstance->c100_is_A2FLASH_A1FLASH = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 10)), "is_A2FLASH_A1FLASH");
  chartInstance->c100_is_A4FLASH_OF = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 11)), "is_A4FLASH_OF");
  chartInstance->c100_is_A2FLASH_A4FLASH = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 12)), "is_A2FLASH_A4FLASH");
  chartInstance->c100_is_A4FLASH_A1FLASH = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 13)), "is_A4FLASH_A1FLASH");
  chartInstance->c100_is_Flasher = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 14)), "is_Flasher");
  chartInstance->c100_is_FlashTimer = c100_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 15)), "is_FlashTimer");
  chartInstance->c100_temporalCounter_i1 = c100_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c100_u, 16)), "temporalCounter_i1");
  sf_mex_assign(&chartInstance->c100_setSimStateSideEffectsInfo,
                c100_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c100_u, 17)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c100_u);
  chartInstance->c100_doSetSimStateSideEffects = 1U;
  c100_update_debugger_state_c100_MX_Gtwy_Control(chartInstance);
  sf_mex_destroy(&c100_st);
}

static void c100_set_sim_state_side_effects_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  if (chartInstance->c100_doSetSimStateSideEffects != 0) {
    chartInstance->c100_tp_Init = (uint8_T)
      (chartInstance->c100_is_c100_MX_Gtwy_Control == c100_IN_Init);
    chartInstance->c100_tp_Normal = (uint8_T)
      (chartInstance->c100_is_c100_MX_Gtwy_Control == c100_IN_Normal);
    chartInstance->c100_tp_OffsetCheck = (uint8_T)
      (chartInstance->c100_is_c100_MX_Gtwy_Control == c100_IN_OffsetCheck);
    chartInstance->c100_tp_ReminderOfLastState = (uint8_T)
      (chartInstance->c100_is_c100_MX_Gtwy_Control ==
       c100_IN_ReminderOfLastState);
    chartInstance->c100_tp_Flasher = (uint8_T)
      (chartInstance->c100_is_active_Flasher == 1U);
    chartInstance->c100_tp_A2FLASH_A1FLASH = (uint8_T)
      (chartInstance->c100_is_Flasher == c100_IN_A2FLASH_A1FLASH);
    chartInstance->c100_c_tp_GLOW_OFF = (uint8_T)
      (chartInstance->c100_is_A2FLASH_A1FLASH == c100_IN_GLOW_OFF);
    if (chartInstance->c100_is_A2FLASH_A1FLASH == c100_IN_OFF) {
      chartInstance->c100_c_tp_OFF = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 9) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_c_tp_OFF = 0U;
    }

    if (chartInstance->c100_is_A2FLASH_A1FLASH == c100_IN_ON) {
      chartInstance->c100_c_tp_ON = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 10) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_c_tp_ON = 0U;
    }

    chartInstance->c100_tp_A2FLASH_A4FLASH = (uint8_T)
      (chartInstance->c100_is_Flasher == c100_IN_A2FLASH_A4FLASH);
    chartInstance->c100_d_tp_GLOW_OFF = (uint8_T)
      (chartInstance->c100_is_A2FLASH_A4FLASH == c100_IN_GLOW_OFF);
    if (chartInstance->c100_is_A2FLASH_A4FLASH == c100_IN_OFF) {
      chartInstance->c100_d_tp_OFF = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 13) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_d_tp_OFF = 0U;
    }

    if (chartInstance->c100_is_A2FLASH_A4FLASH == c100_IN_ON) {
      chartInstance->c100_d_tp_ON = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 14) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_d_tp_ON = 0U;
    }

    chartInstance->c100_tp_A4FLASH_A1FLASH = (uint8_T)
      (chartInstance->c100_is_Flasher == c100_IN_A4FLASH_A1FLASH);
    chartInstance->c100_f_tp_GLOW_OFF = (uint8_T)
      (chartInstance->c100_is_A4FLASH_A1FLASH == c100_IN_GLOW_OFF);
    if (chartInstance->c100_is_A4FLASH_A1FLASH == c100_IN_OFF) {
      chartInstance->c100_e_tp_OFF = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 17) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_e_tp_OFF = 0U;
    }

    if (chartInstance->c100_is_A4FLASH_A1FLASH == c100_IN_ON) {
      chartInstance->c100_f_tp_ON = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 18) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_f_tp_ON = 0U;
    }

    chartInstance->c100_tp_A4FLASH_OF = (uint8_T)(chartInstance->c100_is_Flasher
      == c100_IN_A4FLASH_OF);
    chartInstance->c100_e_tp_GLOW_OFF = (uint8_T)
      (chartInstance->c100_is_A4FLASH_OF == c100_IN_GLOW_OFF);
    if (chartInstance->c100_is_A4FLASH_OF == c100_b_IN_ON) {
      chartInstance->c100_e_tp_ON = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 21) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_e_tp_ON = 0U;
    }

    if (chartInstance->c100_is_A4FLASH_OF == c100_IN_ON1) {
      chartInstance->c100_tp_ON1 = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 22) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_tp_ON1 = 0U;
    }

    chartInstance->c100_tp_Default = (uint8_T)(chartInstance->c100_is_Flasher ==
      c100_IN_Default);
    chartInstance->c100_tp_OF_A1FLASH = (uint8_T)(chartInstance->c100_is_Flasher
      == c100_IN_OF_A1FLASH);
    chartInstance->c100_tp_GLOW_OFF = (uint8_T)
      (chartInstance->c100_is_OF_A1FLASH == c100_IN_GLOW_OFF);
    if (chartInstance->c100_is_OF_A1FLASH == c100_IN_OFF) {
      chartInstance->c100_tp_OFF = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 26) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_tp_OFF = 0U;
    }

    if (chartInstance->c100_is_OF_A1FLASH == c100_IN_ON) {
      chartInstance->c100_tp_ON = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 27) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_tp_ON = 0U;
    }

    chartInstance->c100_tp_OF_A4FLASH = (uint8_T)(chartInstance->c100_is_Flasher
      == c100_IN_OF_A4FLASH);
    chartInstance->c100_b_tp_GLOW_OFF = (uint8_T)
      (chartInstance->c100_is_OF_A4FLASH == c100_IN_GLOW_OFF);
    if (chartInstance->c100_is_OF_A4FLASH == c100_IN_OFF) {
      chartInstance->c100_b_tp_OFF = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 30) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_b_tp_OFF = 0U;
    }

    if (chartInstance->c100_is_OF_A4FLASH == c100_IN_ON) {
      chartInstance->c100_b_tp_ON = 1U;
      if (sf_mex_sub(chartInstance->c100_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 31) == 0.0) {
        chartInstance->c100_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c100_b_tp_ON = 0U;
    }

    chartInstance->c100_tp_FlashTimer = (uint8_T)
      (chartInstance->c100_is_active_FlashTimer == 1U);
    chartInstance->c100_tp_Expired = (uint8_T)(chartInstance->c100_is_FlashTimer
      == c100_IN_Expired);
    chartInstance->c100_tp_GlowCycle1 = (uint8_T)
      (chartInstance->c100_is_FlashTimer == c100_IN_GlowCycle1);
    chartInstance->c100_tp_GlowCycle2 = (uint8_T)
      (chartInstance->c100_is_FlashTimer == c100_IN_GlowCycle2);
    chartInstance->c100_tp_GlowOff = (uint8_T)(chartInstance->c100_is_FlashTimer
      == c100_IN_GlowOff);
    chartInstance->c100_tp_GlowOff1 = (uint8_T)
      (chartInstance->c100_is_FlashTimer == c100_IN_GlowOff1);
    chartInstance->c100_tp_No_Glow = (uint8_T)(chartInstance->c100_is_FlashTimer
      == c100_IN_No_Glow);
    chartInstance->c100_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c100_setSimStateSideEffectsInfo);
}

static void sf_gateway_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  c100_set_sim_state_side_effects_c100_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 97U, chartInstance->c100_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_state_System, 8U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_state_Engine, 7U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_state_Console, 6U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_dout_GlowPlugs, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_flag_InitEERead, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_state_AuxEnable, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_mode_RightControl, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_mode_LeftControl, 1U);
  chartInstance->c100_sfEvent = CALL_EVENT;
  if (chartInstance->c100_temporalCounter_i1 < 65535U) {
    chartInstance->c100_temporalCounter_i1++;
  }

  c100_chartstep_c100_MX_Gtwy_Control(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_MX_Gtwy_ControlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c100_MX_Gtwy_Control(SFc100_MX_Gtwy_ControlInstanceStruct *
  chartInstance)
{
  c100_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void c100_chartstep_c100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c100_temp;
  boolean_T c100_b_temp;
  boolean_T c100_c_temp;
  boolean_T c100_d_temp;
  boolean_T c100_e_temp;
  boolean_T c100_f_temp;
  boolean_T c100_out;
  boolean_T c100_g_temp;
  boolean_T c100_b_out;
  boolean_T c100_h_temp;
  boolean_T c100_i_temp;
  boolean_T c100_j_temp;
  boolean_T c100_k_temp;
  boolean_T c100_l_temp;
  boolean_T c100_c_out;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 97U, chartInstance->c100_sfEvent);
  if (chartInstance->c100_is_active_c100_MX_Gtwy_Control == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 97U,
                 chartInstance->c100_sfEvent);
    chartInstance->c100_is_active_c100_MX_Gtwy_Control = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 97U, chartInstance->c100_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c100_sfEvent);
    chartInstance->c100_is_c100_MX_Gtwy_Control = c100_IN_Init;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c100_sfEvent);
    chartInstance->c100_tp_Init = 1U;
    *chartInstance->c100_disp_LeftControl =
      *chartInstance->c100_mode_LeftControl;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
    *chartInstance->c100_disp_RightControl =
      *chartInstance->c100_mode_RightControl;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
    *chartInstance->c100_flag_AuxEnableFlash = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_flag_AuxEnableFlash, 11U);
  } else {
    switch (chartInstance->c100_is_c100_MX_Gtwy_Control) {
     case c100_IN_Init:
      CV_CHART_EVAL(97, 0, c100_IN_Init);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U,
                   chartInstance->c100_sfEvent);
      c100_temp = (_SFD_CCP_CALL(5U, 4U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 4U,
        0, (real_T)c100_get_ee_ControlMode(chartInstance, 0), (real_T)
        chartInstance->c100_EE_NA_NA, 0, 0U, c100_get_ee_ControlMode
        (chartInstance, 0) == chartInstance->c100_EE_NA_NA) != 0U,
        chartInstance->c100_sfEvent) != 0U);
      if (!c100_temp) {
        c100_temp = (_SFD_CCP_CALL(5U, 4U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          4U, 1, (real_T)c100_get_ee_ControlMode(chartInstance, 0), (real_T)
          chartInstance->c100_EE_LT_OF_NA, 0, 0U, c100_get_ee_ControlMode
          (chartInstance, 0) == chartInstance->c100_EE_LT_OF_NA) != 0U,
          chartInstance->c100_sfEvent) != 0U);
      }

      c100_c_temp = c100_temp;
      if (!c100_temp) {
        c100_c_temp = (_SFD_CCP_CALL(5U, 4U, 2, (boolean_T)CV_RELATIONAL_EVAL(5U,
          4U, 2, (real_T)c100_get_ee_ControlMode(chartInstance, 0), (real_T)
          chartInstance->c100_EE_RT_NA_OF, 0, 0U, c100_get_ee_ControlMode
          (chartInstance, 0) == chartInstance->c100_EE_RT_NA_OF) != 0U,
          chartInstance->c100_sfEvent) != 0U);
      }

      c100_f_temp = c100_c_temp;
      if (c100_c_temp) {
        c100_f_temp = (_SFD_CCP_CALL(5U, 4U, 3,
          *chartInstance->c100_flag_InitEERead != 0U,
          chartInstance->c100_sfEvent) != 0U);
      }

      c100_g_temp = c100_f_temp;
      if (!c100_f_temp) {
        c100_g_temp = (_SFD_CCP_CALL(5U, 4U, 4, (boolean_T)CV_RELATIONAL_EVAL(5U,
          4U, 3, (real_T)chartInstance->c100_CD_EMEA_CONTROLS_OPTION_A, (real_T)
          chartInstance->c100_NON_FUNCTIONAL, 0, 1U,
          chartInstance->c100_CD_EMEA_CONTROLS_OPTION_A !=
          chartInstance->c100_NON_FUNCTIONAL) != 0U, chartInstance->c100_sfEvent)
                       != 0U);
      }

      c100_b_out = (CV_TRANSITION_EVAL(4U, (int32_T)c100_g_temp) != 0);
      if (c100_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_Init = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_c100_MX_Gtwy_Control = c100_IN_Normal;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_Normal = 1U;
        *chartInstance->c100_disp_LeftControl =
          *chartInstance->c100_mode_LeftControl;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
        *chartInstance->c100_disp_RightControl =
          *chartInstance->c100_mode_RightControl;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_flag_AuxEnableFlash = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_flag_AuxEnableFlash,
                              11U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U,
                     chartInstance->c100_sfEvent);
        c100_h_temp = (_SFD_CCP_CALL(5U, 5U, 0,
          *chartInstance->c100_flag_InitEERead != 0U,
          chartInstance->c100_sfEvent) != 0U);
        if (c100_h_temp) {
          c100_i_temp = (_SFD_CCP_CALL(5U, 5U, 1, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 5U, 0, (real_T)*chartInstance->c100_mode_LeftControl, (real_T)
             chartInstance->c100_MODE_LEFT_NONE, 0, 1U,
             *chartInstance->c100_mode_LeftControl !=
             chartInstance->c100_MODE_LEFT_NONE) != 0U,
            chartInstance->c100_sfEvent) != 0U);
          if (!c100_i_temp) {
            c100_i_temp = (_SFD_CCP_CALL(5U, 5U, 2, (boolean_T)
              CV_RELATIONAL_EVAL(5U, 5U, 1, (real_T)
                                 *chartInstance->c100_mode_RightControl, (real_T)
                                 chartInstance->c100_MODE_RIGHT_NONE, 0, 1U,
                                 *chartInstance->c100_mode_RightControl !=
                                 chartInstance->c100_MODE_RIGHT_NONE) != 0U,
              chartInstance->c100_sfEvent) != 0U);
          }

          c100_h_temp = c100_i_temp;
        }

        c100_j_temp = c100_h_temp;
        if (c100_h_temp) {
          c100_j_temp = (_SFD_CCP_CALL(5U, 5U, 3, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 5U, 2, (real_T)*chartInstance->c100_state_Console, (real_T)
             chartInstance->c100_ACTIVE, 0, 0U,
             *chartInstance->c100_state_Console == chartInstance->c100_ACTIVE)
            != 0U, chartInstance->c100_sfEvent) != 0U);
        }

        c100_k_temp = c100_j_temp;
        if (c100_j_temp) {
          c100_k_temp = (_SFD_CCP_CALL(5U, 5U, 4, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 5U, 3, (real_T)*chartInstance->c100_state_System, (real_T)
             chartInstance->c100_SYS_NORMAL, 0, 0U,
             *chartInstance->c100_state_System == chartInstance->c100_SYS_NORMAL)
            != 0U, chartInstance->c100_sfEvent) != 0U);
        }

        c100_l_temp = c100_k_temp;
        if (c100_k_temp) {
          c100_l_temp = (_SFD_CCP_CALL(5U, 5U, 5, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 5U, 4, (real_T)*chartInstance->c100_state_Engine, (real_T)
             chartInstance->c100_ENGINE_CRANKING, 0, 1U,
             *chartInstance->c100_state_Engine !=
             chartInstance->c100_ENGINE_CRANKING) != 0U,
            chartInstance->c100_sfEvent) != 0U);
        }

        c100_c_out = (CV_TRANSITION_EVAL(5U, (int32_T)c100_l_temp) != 0);
        if (c100_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c100_sfEvent);
          chartInstance->c100_tp_Init = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c100_sfEvent);
          chartInstance->c100_is_c100_MX_Gtwy_Control = c100_IN_OffsetCheck;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c100_sfEvent);
          chartInstance->c100_tp_OffsetCheck = 1U;
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                       chartInstance->c100_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_Normal:
      CV_CHART_EVAL(97, 0, c100_IN_Normal);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                   chartInstance->c100_sfEvent);
      *chartInstance->c100_disp_LeftControl =
        *chartInstance->c100_mode_LeftControl;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      *chartInstance->c100_disp_RightControl =
        *chartInstance->c100_mode_RightControl;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_OffsetCheck:
      CV_CHART_EVAL(97, 0, c100_IN_OffsetCheck);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 32U,
                   chartInstance->c100_sfEvent);
      c100_b_temp = (_SFD_CCP_CALL(5U, 32U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        32U, 0, (real_T)c100_get_ee_ControlMode(chartInstance, 0), (real_T)
        chartInstance->c100_EE_RT_NA_OF, 0, 2U, c100_get_ee_ControlMode
        (chartInstance, 0) < chartInstance->c100_EE_RT_NA_OF) != 0U,
        chartInstance->c100_sfEvent) != 0U);
      if (c100_b_temp) {
        c100_b_temp = (_SFD_CCP_CALL(5U, 32U, 1, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 32U, 1, (real_T)*chartInstance->c100_mode_RightControl, (real_T)
           chartInstance->c100_MODE_RIGHT_OFFSET, 0, 0U,
           *chartInstance->c100_mode_RightControl ==
           chartInstance->c100_MODE_RIGHT_OFFSET) != 0U,
          chartInstance->c100_sfEvent) != 0U);
      }

      c100_d_temp = c100_b_temp;
      if (!c100_b_temp) {
        c100_e_temp = (_SFD_CCP_CALL(5U, 32U, 2, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 32U, 2, (real_T)c100_get_ee_ControlMode(chartInstance, 0),
           (real_T)chartInstance->c100_EE_RT_NA_OF, 0, 4U,
           c100_get_ee_ControlMode(chartInstance, 0) >
           chartInstance->c100_EE_RT_NA_OF) != 0U, chartInstance->c100_sfEvent)
                       != 0U);
        if (c100_e_temp) {
          c100_e_temp = (_SFD_CCP_CALL(5U, 32U, 3, (boolean_T)CV_RELATIONAL_EVAL
            (5U, 32U, 3, (real_T)*chartInstance->c100_mode_LeftControl, (real_T)
             chartInstance->c100_MODE_LEFT_OFFSET, 0, 0U,
             *chartInstance->c100_mode_LeftControl ==
             chartInstance->c100_MODE_LEFT_OFFSET) != 0U,
            chartInstance->c100_sfEvent) != 0U);
        }

        c100_d_temp = c100_e_temp;
      }

      c100_out = (CV_TRANSITION_EVAL(32U, (int32_T)c100_d_temp) != 0);
      if (c100_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 32U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_OffsetCheck = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_c100_MX_Gtwy_Control = c100_IN_Normal;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_Normal = 1U;
        *chartInstance->c100_disp_LeftControl =
          *chartInstance->c100_mode_LeftControl;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
        *chartInstance->c100_disp_RightControl =
          *chartInstance->c100_mode_RightControl;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_flag_AuxEnableFlash = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_flag_AuxEnableFlash,
                              11U);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 31U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_OffsetCheck = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_c100_MX_Gtwy_Control =
          c100_IN_ReminderOfLastState;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_ReminderOfLastState = 1U;
        *chartInstance->c100_flag_AuxEnableFlash = true;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_flag_AuxEnableFlash,
                              11U);
        chartInstance->c100_is_active_Flasher = 1U;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_Flasher = 1U;
        c100_enter_internal_Flasher(chartInstance);
        chartInstance->c100_is_active_FlashTimer = 1U;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_FlashTimer = 1U;
        chartInstance->c100_flash_timer = 0U;
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c100_flash_timer, 0U);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 44U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_FlashTimer = c100_IN_No_Glow;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_No_Glow = 1U;
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_ReminderOfLastState:
      CV_CHART_EVAL(97, 0, c100_IN_ReminderOfLastState);
      c100_ReminderOfLastState(chartInstance);
      break;

     default:
      CV_CHART_EVAL(97, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c100_is_c100_MX_Gtwy_Control = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c100_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 97U, chartInstance->c100_sfEvent);
}

static void initSimStructsc100_MX_Gtwy_Control
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c100_ReminderOfLastState(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c100_out;
  boolean_T c100_temp;
  uint8_T c100_u0;
  boolean_T c100_b_out;
  boolean_T c100_b_temp;
  boolean_T c100_c_temp;
  boolean_T c100_c_out;
  boolean_T c100_d_out;
  boolean_T c100_e_out;
  boolean_T c100_f_out;
  boolean_T c100_g_out;
  boolean_T c100_h_out;
  int32_T c100_i0;
  int32_T c100_i1;
  boolean_T guard1 = false;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U, chartInstance->c100_sfEvent);
  c100_out = (CV_TRANSITION_EVAL(1U, (int32_T)(_SFD_CCP_CALL(5U, 1U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 1U, 0, (real_T)
    chartInstance->c100_flash_timer, (real_T)
    chartInstance->c100_CD_EMEA_CONTROLS_REMINDER_TIME, 0, 4U,
    chartInstance->c100_flash_timer >
    chartInstance->c100_CD_EMEA_CONTROLS_REMINDER_TIME) != 0U,
    chartInstance->c100_sfEvent) != 0U)) != 0);
  guard1 = false;
  if (c100_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c100_sfEvent);
    c100_set_ee_ControlMode(chartInstance, 0, chartInstance->c100_EE_NA_NA);
    ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    c100_u0 = c100_get_ee_ControlMode(chartInstance, 0);
    sf_mex_printf("%s =\\n", "ee_ControlMode");
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 9, c100_u0);
    matlab_UpdateEEVar();
    guard1 = true;
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                 chartInstance->c100_sfEvent);
    c100_temp = (_SFD_CCP_CALL(5U, 2U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U,
      0, (real_T)*chartInstance->c100_state_AuxEnable, (real_T)
      chartInstance->c100_INACTIVE, 0, 1U, *chartInstance->c100_state_AuxEnable
      != chartInstance->c100_INACTIVE) != 0U, chartInstance->c100_sfEvent) != 0U);
    if (!c100_temp) {
      c100_temp = (_SFD_CCP_CALL(5U, 2U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U, 2U,
        1, (real_T)c100_get_ee_ControlMode(chartInstance, 0), (real_T)
        chartInstance->c100_EE_NA_NA, 0, 0U, c100_get_ee_ControlMode
        (chartInstance, 0) == chartInstance->c100_EE_NA_NA) != 0U,
        chartInstance->c100_sfEvent) != 0U);
    }

    c100_b_out = (CV_TRANSITION_EVAL(2U, (int32_T)c100_temp) != 0);
    if (c100_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c100_sfEvent);
      guard1 = true;
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 50U,
                   chartInstance->c100_sfEvent);
      c100_b_temp = (_SFD_CCP_CALL(5U, 50U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        50U, 0, (real_T)*chartInstance->c100_state_Console, (real_T)
        chartInstance->c100_ACTIVE, 0, 1U, *chartInstance->c100_state_Console !=
        chartInstance->c100_ACTIVE) != 0U, chartInstance->c100_sfEvent) != 0U);
      if (!c100_b_temp) {
        c100_b_temp = (_SFD_CCP_CALL(5U, 50U, 1, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 50U, 1, (real_T)*chartInstance->c100_state_System, (real_T)
           chartInstance->c100_SYS_NORMAL, 0, 1U,
           *chartInstance->c100_state_System != chartInstance->c100_SYS_NORMAL)
          != 0U, chartInstance->c100_sfEvent) != 0U);
      }

      c100_c_temp = c100_b_temp;
      if (!c100_b_temp) {
        c100_c_temp = (_SFD_CCP_CALL(5U, 50U, 2, (boolean_T)CV_RELATIONAL_EVAL
          (5U, 50U, 2, (real_T)*chartInstance->c100_state_Engine, (real_T)
           chartInstance->c100_ENGINE_CRANKING, 0, 0U,
           *chartInstance->c100_state_Engine ==
           chartInstance->c100_ENGINE_CRANKING) != 0U,
          chartInstance->c100_sfEvent) != 0U);
      }

      c100_c_out = (CV_TRANSITION_EVAL(50U, (int32_T)c100_c_temp) != 0);
      if (c100_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 50U, chartInstance->c100_sfEvent);
        c100_exit_internal_ReminderOfLastState(chartInstance);
        chartInstance->c100_tp_ReminderOfLastState = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_c100_MX_Gtwy_Control = c100_IN_Init;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_Init = 1U;
        *chartInstance->c100_disp_LeftControl =
          *chartInstance->c100_mode_LeftControl;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
        *chartInstance->c100_disp_RightControl =
          *chartInstance->c100_mode_RightControl;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_flag_AuxEnableFlash = false;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_flag_AuxEnableFlash,
                              11U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                     chartInstance->c100_sfEvent);
        c100_Flasher(chartInstance);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                     chartInstance->c100_sfEvent);
        switch (chartInstance->c100_is_FlashTimer) {
         case c100_IN_Expired:
          CV_STATE_EVAL(4, 0, c100_IN_Expired);
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                       chartInstance->c100_sfEvent);
          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c100_sfEvent);
          break;

         case c100_IN_GlowCycle1:
          CV_STATE_EVAL(4, 0, c100_IN_GlowCycle1);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 46U,
                       chartInstance->c100_sfEvent);
          c100_d_out = (CV_TRANSITION_EVAL(46U, !(_SFD_CCP_CALL(5U, 46U, 0,
            *chartInstance->c100_dout_GlowPlugs != 0U,
            chartInstance->c100_sfEvent) != 0U)) != 0);
          if (c100_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 46U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_GlowCycle1 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c100_sfEvent);
            chartInstance->c100_is_FlashTimer = c100_IN_GlowOff;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_GlowOff = 1U;
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                         chartInstance->c100_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c100_sfEvent);
          break;

         case c100_IN_GlowCycle2:
          CV_STATE_EVAL(4, 0, c100_IN_GlowCycle2);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 47U,
                       chartInstance->c100_sfEvent);
          c100_e_out = (CV_TRANSITION_EVAL(47U, !(_SFD_CCP_CALL(5U, 47U, 0,
            *chartInstance->c100_dout_GlowPlugs != 0U,
            chartInstance->c100_sfEvent) != 0U)) != 0);
          if (c100_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 47U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_GlowCycle2 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c100_sfEvent);
            chartInstance->c100_is_FlashTimer = c100_IN_GlowOff1;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_GlowOff1 = 1U;
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                         chartInstance->c100_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c100_sfEvent);
          break;

         case c100_IN_GlowOff:
          CV_STATE_EVAL(4, 0, c100_IN_GlowOff);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 48U,
                       chartInstance->c100_sfEvent);
          c100_f_out = (CV_TRANSITION_EVAL(48U, (int32_T)(_SFD_CCP_CALL(5U, 48U,
            0, *chartInstance->c100_dout_GlowPlugs != 0U,
            chartInstance->c100_sfEvent) != 0U)) != 0);
          if (c100_f_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 48U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_GlowOff = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c100_sfEvent);
            chartInstance->c100_is_FlashTimer = c100_IN_GlowCycle2;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_GlowCycle2 = 1U;
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                         chartInstance->c100_sfEvent);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c100_sfEvent);
          break;

         case c100_IN_GlowOff1:
          CV_STATE_EVAL(4, 0, c100_IN_GlowOff1);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 49U,
                       chartInstance->c100_sfEvent);
          c100_g_out = (CV_TRANSITION_EVAL(49U, (int32_T)(_SFD_CCP_CALL(5U, 49U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 49U, 0, (real_T)
            chartInstance->c100_flash_timer, (real_T)
            chartInstance->c100_CD_EMEA_CONTROLS_REMINDER_TIME, 0, 4U,
            chartInstance->c100_flash_timer >
            chartInstance->c100_CD_EMEA_CONTROLS_REMINDER_TIME) != 0U,
            chartInstance->c100_sfEvent) != 0U)) != 0);
          if (c100_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 49U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_GlowOff1 = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c100_sfEvent);
            chartInstance->c100_is_FlashTimer = c100_IN_Expired;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_Expired = 1U;
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                         chartInstance->c100_sfEvent);
            c100_i0 = c100__s32_add__(chartInstance, (int32_T)
              chartInstance->c100_flash_timer, 1, 157U, 13U, 13U);
            if (CV_SATURATION_EVAL(4, 9, 0, 0, c100_i0 < 0)) {
              c100_i0 = 0;
              _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 157U, 13U, 13U);
            } else {
              if (c100_i0 > 65535) {
                c100_i0 = 65535;
                _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 157U, 13U, 13U);
              }
            }

            chartInstance->c100_flash_timer = (uint16_T)c100_i0;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c100_flash_timer, 0U);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c100_sfEvent);
          break;

         case c100_IN_No_Glow:
          CV_STATE_EVAL(4, 0, c100_IN_No_Glow);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 45U,
                       chartInstance->c100_sfEvent);
          c100_h_out = (CV_TRANSITION_EVAL(45U, (int32_T)(_SFD_CCP_CALL(5U, 45U,
            0, *chartInstance->c100_dout_GlowPlugs != 0U,
            chartInstance->c100_sfEvent) != 0U)) != 0);
          if (c100_h_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 45U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_No_Glow = 0U;
            _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c100_sfEvent);
            chartInstance->c100_is_FlashTimer = c100_IN_GlowCycle1;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_GlowCycle1 = 1U;
            chartInstance->c100_flash_timer = 0U;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c100_flash_timer, 0U);
          } else {
            _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                         chartInstance->c100_sfEvent);
            c100_i1 = c100__s32_add__(chartInstance, (int32_T)
              chartInstance->c100_flash_timer, 1, 150U, 12U, 13U);
            if (CV_SATURATION_EVAL(4, 10, 0, 0, c100_i1 < 0)) {
              c100_i1 = 0;
              _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 150U, 12U, 13U);
            } else {
              if (c100_i1 > 65535) {
                c100_i1 = 65535;
                _SFD_OVERFLOW_DETECTION(SFDB_SATURATE, 150U, 12U, 13U);
              }
            }

            chartInstance->c100_flash_timer = (uint16_T)c100_i1;
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c100_flash_timer, 0U);
          }

          _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U,
                       chartInstance->c100_sfEvent);
          break;

         default:
          CV_STATE_EVAL(4, 0, 0);

          /* Unreachable state, for coverage only */
          chartInstance->c100_is_FlashTimer = c100_IN_NO_ACTIVE_CHILD;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c100_sfEvent);
          break;
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c100_sfEvent);
      }
    }
  }

  if (guard1) {
    c100_exit_internal_ReminderOfLastState(chartInstance);
    chartInstance->c100_tp_ReminderOfLastState = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c100_sfEvent);
    chartInstance->c100_is_c100_MX_Gtwy_Control = c100_IN_Normal;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c100_sfEvent);
    chartInstance->c100_tp_Normal = 1U;
    *chartInstance->c100_disp_LeftControl =
      *chartInstance->c100_mode_LeftControl;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
    *chartInstance->c100_disp_RightControl =
      *chartInstance->c100_mode_RightControl;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
    *chartInstance->c100_flag_AuxEnableFlash = false;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_flag_AuxEnableFlash, 11U);
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c100_sfEvent);
}

static void c100_exit_internal_ReminderOfLastState
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  switch (chartInstance->c100_is_FlashTimer) {
   case c100_IN_Expired:
    CV_STATE_EVAL(4, 1, c100_IN_Expired);
    chartInstance->c100_tp_Expired = 0U;
    chartInstance->c100_is_FlashTimer = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_GlowCycle1:
    CV_STATE_EVAL(4, 1, c100_IN_GlowCycle1);
    chartInstance->c100_tp_GlowCycle1 = 0U;
    chartInstance->c100_is_FlashTimer = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_GlowCycle2:
    CV_STATE_EVAL(4, 1, c100_IN_GlowCycle2);
    chartInstance->c100_tp_GlowCycle2 = 0U;
    chartInstance->c100_is_FlashTimer = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_GlowOff:
    CV_STATE_EVAL(4, 1, c100_IN_GlowOff);
    chartInstance->c100_tp_GlowOff = 0U;
    chartInstance->c100_is_FlashTimer = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_GlowOff1:
    CV_STATE_EVAL(4, 1, c100_IN_GlowOff1);
    chartInstance->c100_tp_GlowOff1 = 0U;
    chartInstance->c100_is_FlashTimer = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_No_Glow:
    CV_STATE_EVAL(4, 1, c100_IN_No_Glow);
    chartInstance->c100_tp_No_Glow = 0U;
    chartInstance->c100_is_FlashTimer = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c100_sfEvent);
    break;

   default:
    CV_STATE_EVAL(4, 1, 0);
    chartInstance->c100_is_FlashTimer = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c100_sfEvent);
    break;
  }

  chartInstance->c100_tp_FlashTimer = 0U;
  chartInstance->c100_is_active_FlashTimer = 0U;
  _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c100_sfEvent);
  c100_exit_internal_Flasher(chartInstance);
  chartInstance->c100_tp_Flasher = 0U;
  chartInstance->c100_is_active_Flasher = 0U;
  _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c100_sfEvent);
}

static void c100_enter_internal_Flasher(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  boolean_T c100_out;
  boolean_T c100_b_out;
  boolean_T c100_temp;
  boolean_T c100_c_out;
  boolean_T c100_d_out;
  boolean_T c100_e_out;
  boolean_T c100_f_out;
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c100_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U, chartInstance->c100_sfEvent);
  c100_out = (CV_TRANSITION_EVAL(6U, (int32_T)(_SFD_CCP_CALL(5U, 6U, 0,
    (boolean_T)CV_RELATIONAL_EVAL(5U, 6U, 0, (real_T)c100_get_ee_ControlMode
    (chartInstance, 0), (real_T)chartInstance->c100_EE_LT_OF_A1, 0, 0U,
    c100_get_ee_ControlMode(chartInstance, 0) == chartInstance->c100_EE_LT_OF_A1)
    != 0U, chartInstance->c100_sfEvent) != 0U)) != 0);
  if (c100_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c100_sfEvent);
    chartInstance->c100_is_Flasher = c100_IN_OF_A1FLASH;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 29U, chartInstance->c100_sfEvent);
    chartInstance->c100_tp_OF_A1FLASH = 1U;
    *chartInstance->c100_disp_LeftControl = chartInstance->c100_MODE_LEFT_OFFSET;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 33U, chartInstance->c100_sfEvent);
    chartInstance->c100_is_OF_A1FLASH = c100_IN_GLOW_OFF;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 30U, chartInstance->c100_sfEvent);
    chartInstance->c100_tp_GLOW_OFF = 1U;
    *chartInstance->c100_disp_RightControl = chartInstance->c100_MODE_RIGHT_NONE;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c100_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 17U,
                 chartInstance->c100_sfEvent);
    c100_b_out = (CV_TRANSITION_EVAL(17U, (int32_T)(_SFD_CCP_CALL(5U, 17U, 0,
      (boolean_T)CV_RELATIONAL_EVAL(5U, 17U, 0, (real_T)c100_get_ee_ControlMode
      (chartInstance, 0), (real_T)chartInstance->c100_EE_LT_OF_A4, 0, 0U,
      c100_get_ee_ControlMode(chartInstance, 0) ==
      chartInstance->c100_EE_LT_OF_A4) != 0U, chartInstance->c100_sfEvent) != 0U))
                  != 0);
    if (c100_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_Flasher = c100_IN_OF_A4FLASH;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 33U, chartInstance->c100_sfEvent);
      chartInstance->c100_tp_OF_A4FLASH = 1U;
      *chartInstance->c100_disp_LeftControl =
        chartInstance->c100_MODE_LEFT_OFFSET;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 34U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_OF_A4FLASH = c100_IN_GLOW_OFF;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 34U, chartInstance->c100_sfEvent);
      chartInstance->c100_b_tp_GLOW_OFF = 1U;
      *chartInstance->c100_disp_RightControl =
        chartInstance->c100_MODE_RIGHT_NONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c100_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 19U,
                   chartInstance->c100_sfEvent);
      c100_temp = (_SFD_CCP_CALL(5U, 19U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U,
        19U, 0, (real_T)c100_get_ee_ControlMode(chartInstance, 0), (real_T)
        chartInstance->c100_EE_LT_A2_A1, 0, 0U, c100_get_ee_ControlMode
        (chartInstance, 0) == chartInstance->c100_EE_LT_A2_A1) != 0U,
        chartInstance->c100_sfEvent) != 0U);
      if (!c100_temp) {
        c100_temp = (_SFD_CCP_CALL(5U, 19U, 1, (boolean_T)CV_RELATIONAL_EVAL(5U,
          19U, 1, (real_T)c100_get_ee_ControlMode(chartInstance, 0), (real_T)
          chartInstance->c100_EE_RT_A2_A1, 0, 0U, c100_get_ee_ControlMode
          (chartInstance, 0) == chartInstance->c100_EE_RT_A2_A1) != 0U,
          chartInstance->c100_sfEvent) != 0U);
      }

      c100_c_out = (CV_TRANSITION_EVAL(19U, (int32_T)c100_temp) != 0);
      if (c100_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_Flasher = c100_IN_A2FLASH_A1FLASH;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c100_sfEvent);
        chartInstance->c100_tp_A2FLASH_A1FLASH = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 37U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_A2FLASH_A1FLASH = c100_IN_GLOW_OFF;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c100_sfEvent);
        chartInstance->c100_c_tp_GLOW_OFF = 1U;
        *chartInstance->c100_disp_RightControl =
          chartInstance->c100_MODE_RIGHT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_disp_LeftControl =
          chartInstance->c100_MODE_LEFT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c100_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 21U,
                     chartInstance->c100_sfEvent);
        c100_d_out = (CV_TRANSITION_EVAL(21U, (int32_T)(_SFD_CCP_CALL(5U, 21U, 0,
          (boolean_T)CV_RELATIONAL_EVAL(5U, 21U, 0, (real_T)
          c100_get_ee_ControlMode(chartInstance, 0), (real_T)
          chartInstance->c100_EE_LT_A2_A4, 0, 0U, c100_get_ee_ControlMode
          (chartInstance, 0) == chartInstance->c100_EE_LT_A2_A4) != 0U,
          chartInstance->c100_sfEvent) != 0U)) != 0);
        if (c100_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c100_sfEvent);
          chartInstance->c100_is_Flasher = c100_IN_A2FLASH_A4FLASH;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c100_sfEvent);
          chartInstance->c100_tp_A2FLASH_A4FLASH = 1U;
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 39U, chartInstance->c100_sfEvent);
          chartInstance->c100_is_A2FLASH_A4FLASH = c100_IN_GLOW_OFF;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c100_sfEvent);
          chartInstance->c100_d_tp_GLOW_OFF = 1U;
          *chartInstance->c100_disp_RightControl =
            chartInstance->c100_MODE_RIGHT_NONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                                10U);
          *chartInstance->c100_disp_LeftControl =
            chartInstance->c100_MODE_LEFT_NONE;
          _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl,
                                9U);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 22U, chartInstance->c100_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 23U,
                       chartInstance->c100_sfEvent);
          c100_e_out = (CV_TRANSITION_EVAL(23U, (int32_T)(_SFD_CCP_CALL(5U, 23U,
            0, (boolean_T)CV_RELATIONAL_EVAL(5U, 23U, 0, (real_T)
            c100_get_ee_ControlMode(chartInstance, 0), (real_T)
            chartInstance->c100_EE_RT_A4_OF, 0, 0U, c100_get_ee_ControlMode
            (chartInstance, 0) == chartInstance->c100_EE_RT_A4_OF) != 0U,
            chartInstance->c100_sfEvent) != 0U)) != 0);
          if (c100_e_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 23U, chartInstance->c100_sfEvent);
            chartInstance->c100_is_Flasher = c100_IN_A4FLASH_OF;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 24U, chartInstance->c100_sfEvent);
            chartInstance->c100_tp_A4FLASH_OF = 1U;
            *chartInstance->c100_disp_RightControl =
              chartInstance->c100_MODE_RIGHT_OFFSET;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                                  10U);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 41U, chartInstance->c100_sfEvent);
            chartInstance->c100_is_A4FLASH_OF = c100_IN_GLOW_OFF;
            _SFD_CS_CALL(STATE_ACTIVE_TAG, 25U, chartInstance->c100_sfEvent);
            chartInstance->c100_e_tp_GLOW_OFF = 1U;
            *chartInstance->c100_disp_LeftControl =
              chartInstance->c100_MODE_LEFT_NONE;
            _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl,
                                  9U);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c100_sfEvent);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 25U,
                         chartInstance->c100_sfEvent);
            c100_f_out = (CV_TRANSITION_EVAL(25U, (int32_T)(_SFD_CCP_CALL(5U,
              25U, 0, (boolean_T)CV_RELATIONAL_EVAL(5U, 25U, 0, (real_T)
              c100_get_ee_ControlMode(chartInstance, 0), (real_T)
              chartInstance->c100_EE_RT_A4_A1, 0, 0U, c100_get_ee_ControlMode
              (chartInstance, 0) == chartInstance->c100_EE_RT_A4_A1) != 0U,
              chartInstance->c100_sfEvent) != 0U)) != 0);
            if (c100_f_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 25U,
                           chartInstance->c100_sfEvent);
              chartInstance->c100_is_Flasher = c100_IN_A4FLASH_A1FLASH;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 20U, chartInstance->c100_sfEvent);
              chartInstance->c100_tp_A4FLASH_A1FLASH = 1U;
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 43U,
                           chartInstance->c100_sfEvent);
              chartInstance->c100_is_A4FLASH_A1FLASH = c100_IN_GLOW_OFF;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 21U, chartInstance->c100_sfEvent);
              chartInstance->c100_f_tp_GLOW_OFF = 1U;
              *chartInstance->c100_disp_RightControl =
                chartInstance->c100_MODE_RIGHT_NONE;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c100_disp_RightControl, 10U);
              *chartInstance->c100_disp_LeftControl =
                chartInstance->c100_MODE_LEFT_NONE;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c100_disp_LeftControl, 9U);
            } else {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 26U,
                           chartInstance->c100_sfEvent);
              chartInstance->c100_is_Flasher = c100_IN_Default;
              _SFD_CS_CALL(STATE_ACTIVE_TAG, 28U, chartInstance->c100_sfEvent);
              chartInstance->c100_tp_Default = 1U;
              *chartInstance->c100_disp_LeftControl =
                *chartInstance->c100_mode_LeftControl;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c100_disp_LeftControl, 9U);
              *chartInstance->c100_disp_RightControl =
                *chartInstance->c100_mode_RightControl;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c100_disp_RightControl, 10U);
              *chartInstance->c100_flag_AuxEnableFlash = false;
              _SFD_DATA_RANGE_CHECK((real_T)
                                    *chartInstance->c100_flag_AuxEnableFlash,
                                    11U);
            }
          }
        }
      }
    }
  }
}

static void c100_Flasher(SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c100_out;
  uint16_T c100_u1;
  uint16_T c100_u2;
  boolean_T c100_b_out;
  uint16_T c100_u3;
  uint16_T c100_u4;
  boolean_T c100_c_out;
  uint16_T c100_u5;
  uint16_T c100_u6;
  boolean_T c100_d_out;
  boolean_T c100_e_out;
  boolean_T c100_f_out;
  boolean_T c100_g_out;
  boolean_T c100_h_out;
  boolean_T c100_i_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U, chartInstance->c100_sfEvent);
  switch (chartInstance->c100_is_Flasher) {
   case c100_IN_A2FLASH_A1FLASH:
    CV_STATE_EVAL(11, 0, c100_IN_A2FLASH_A1FLASH);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                 chartInstance->c100_sfEvent);
    switch (chartInstance->c100_is_A2FLASH_A1FLASH) {
     case c100_IN_GLOW_OFF:
      CV_STATE_EVAL(12, 0, c100_IN_GLOW_OFF);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 36U,
                   chartInstance->c100_sfEvent);
      c100_out = (CV_TRANSITION_EVAL(36U, !(_SFD_CCP_CALL(5U, 36U, 0,
        *chartInstance->c100_dout_GlowPlugs != 0U, chartInstance->c100_sfEvent)
        != 0U)) != 0);
      if (c100_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 36U, chartInstance->c100_sfEvent);
        chartInstance->c100_c_tp_GLOW_OFF = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_A2FLASH_A1FLASH = c100_IN_ON;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c100_sfEvent);
        chartInstance->c100_temporalCounter_i1 = 0U;
        chartInstance->c100_c_tp_ON = 1U;
        *chartInstance->c100_disp_RightControl =
          chartInstance->c100_MODE_RIGHT_AUX1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_disp_LeftControl =
          chartInstance->c100_MODE_LEFT_AUX2;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U,
                     chartInstance->c100_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_OFF:
      CV_STATE_EVAL(12, 0, c100_IN_OFF);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U,
                   chartInstance->c100_sfEvent);
      c100_u1 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
        ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 13U),
        37U, 1U, 5U);
      c100_d_out = (CV_TRANSITION_EVAL(13U, (int32_T)(_SFD_CCP_CALL(5U, 13U, 0,
        (chartInstance->c100_temporalCounter_i1 >= c100_u1) != 0U,
        chartInstance->c100_sfEvent) != 0U)) != 0);
      if (c100_d_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c100_sfEvent);
        chartInstance->c100_c_tp_OFF = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_A2FLASH_A1FLASH = c100_IN_ON;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c100_sfEvent);
        chartInstance->c100_temporalCounter_i1 = 0U;
        chartInstance->c100_c_tp_ON = 1U;
        *chartInstance->c100_disp_RightControl =
          chartInstance->c100_MODE_RIGHT_AUX1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_disp_LeftControl =
          chartInstance->c100_MODE_LEFT_AUX2;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 14U,
                     chartInstance->c100_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_ON:
      CV_STATE_EVAL(12, 0, c100_IN_ON);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 12U,
                   chartInstance->c100_sfEvent);
      c100_u2 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
        ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 12U),
        36U, 1U, 5U);
      c100_e_out = (CV_TRANSITION_EVAL(12U, (int32_T)(_SFD_CCP_CALL(5U, 12U, 0,
        (chartInstance->c100_temporalCounter_i1 >= c100_u2) != 0U,
        chartInstance->c100_sfEvent) != 0U)) != 0);
      if (c100_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c100_sfEvent);
        chartInstance->c100_c_tp_ON = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_A2FLASH_A1FLASH = c100_IN_OFF;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c100_sfEvent);
        chartInstance->c100_temporalCounter_i1 = 0U;
        chartInstance->c100_c_tp_OFF = 1U;
        *chartInstance->c100_disp_RightControl =
          chartInstance->c100_MODE_RIGHT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_disp_LeftControl =
          chartInstance->c100_MODE_LEFT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 15U,
                     chartInstance->c100_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c100_sfEvent);
      break;

     default:
      CV_STATE_EVAL(12, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c100_is_A2FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c100_sfEvent);
      break;
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_A2FLASH_A4FLASH:
    CV_STATE_EVAL(11, 0, c100_IN_A2FLASH_A4FLASH);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 16U,
                 chartInstance->c100_sfEvent);
    switch (chartInstance->c100_is_A2FLASH_A4FLASH) {
     case c100_IN_GLOW_OFF:
      CV_STATE_EVAL(16, 0, c100_IN_GLOW_OFF);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 38U,
                   chartInstance->c100_sfEvent);
      c100_b_out = (CV_TRANSITION_EVAL(38U, !(_SFD_CCP_CALL(5U, 38U, 0,
        *chartInstance->c100_dout_GlowPlugs != 0U, chartInstance->c100_sfEvent)
        != 0U)) != 0);
      if (c100_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 38U, chartInstance->c100_sfEvent);
        chartInstance->c100_d_tp_GLOW_OFF = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_A2FLASH_A4FLASH = c100_IN_ON;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c100_sfEvent);
        chartInstance->c100_temporalCounter_i1 = 0U;
        chartInstance->c100_d_tp_ON = 1U;
        *chartInstance->c100_disp_RightControl =
          chartInstance->c100_MODE_RIGHT_AUX4;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_disp_LeftControl =
          chartInstance->c100_MODE_LEFT_AUX2;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 17U,
                     chartInstance->c100_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_OFF:
      CV_STATE_EVAL(16, 0, c100_IN_OFF);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 28U,
                   chartInstance->c100_sfEvent);
      c100_u3 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
        ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 28U),
        78U, 1U, 5U);
      c100_f_out = (CV_TRANSITION_EVAL(28U, (int32_T)(_SFD_CCP_CALL(5U, 28U, 0,
        (chartInstance->c100_temporalCounter_i1 >= c100_u3) != 0U,
        chartInstance->c100_sfEvent) != 0U)) != 0);
      if (c100_f_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 28U, chartInstance->c100_sfEvent);
        chartInstance->c100_d_tp_OFF = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_A2FLASH_A4FLASH = c100_IN_ON;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c100_sfEvent);
        chartInstance->c100_temporalCounter_i1 = 0U;
        chartInstance->c100_d_tp_ON = 1U;
        *chartInstance->c100_disp_RightControl =
          chartInstance->c100_MODE_RIGHT_AUX4;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_disp_LeftControl =
          chartInstance->c100_MODE_LEFT_AUX2;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 18U,
                     chartInstance->c100_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 18U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_ON:
      CV_STATE_EVAL(16, 0, c100_IN_ON);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 27U,
                   chartInstance->c100_sfEvent);
      c100_u4 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
        ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 27U),
        77U, 1U, 5U);
      c100_g_out = (CV_TRANSITION_EVAL(27U, (int32_T)(_SFD_CCP_CALL(5U, 27U, 0,
        (chartInstance->c100_temporalCounter_i1 >= c100_u4) != 0U,
        chartInstance->c100_sfEvent) != 0U)) != 0);
      if (c100_g_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 27U, chartInstance->c100_sfEvent);
        chartInstance->c100_d_tp_ON = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_A2FLASH_A4FLASH = c100_IN_OFF;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c100_sfEvent);
        chartInstance->c100_temporalCounter_i1 = 0U;
        chartInstance->c100_d_tp_OFF = 1U;
        *chartInstance->c100_disp_RightControl =
          chartInstance->c100_MODE_RIGHT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_disp_LeftControl =
          chartInstance->c100_MODE_LEFT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 19U,
                     chartInstance->c100_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 19U, chartInstance->c100_sfEvent);
      break;

     default:
      CV_STATE_EVAL(16, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c100_is_A2FLASH_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c100_sfEvent);
      break;
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_A4FLASH_A1FLASH:
    CV_STATE_EVAL(11, 0, c100_IN_A4FLASH_A1FLASH);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 20U,
                 chartInstance->c100_sfEvent);
    switch (chartInstance->c100_is_A4FLASH_A1FLASH) {
     case c100_IN_GLOW_OFF:
      CV_STATE_EVAL(20, 0, c100_IN_GLOW_OFF);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 42U,
                   chartInstance->c100_sfEvent);
      c100_c_out = (CV_TRANSITION_EVAL(42U, !(_SFD_CCP_CALL(5U, 42U, 0,
        *chartInstance->c100_dout_GlowPlugs != 0U, chartInstance->c100_sfEvent)
        != 0U)) != 0);
      if (c100_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 42U, chartInstance->c100_sfEvent);
        chartInstance->c100_f_tp_GLOW_OFF = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_A4FLASH_A1FLASH = c100_IN_ON;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c100_sfEvent);
        chartInstance->c100_temporalCounter_i1 = 0U;
        chartInstance->c100_f_tp_ON = 1U;
        *chartInstance->c100_disp_RightControl =
          chartInstance->c100_MODE_RIGHT_AUX1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_disp_LeftControl =
          chartInstance->c100_MODE_LEFT_AUX4;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 21U,
                     chartInstance->c100_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_OFF:
      CV_STATE_EVAL(20, 0, c100_IN_OFF);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 30U,
                   chartInstance->c100_sfEvent);
      c100_u5 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
        ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 30U),
        84U, 1U, 5U);
      c100_h_out = (CV_TRANSITION_EVAL(30U, (int32_T)(_SFD_CCP_CALL(5U, 30U, 0,
        (chartInstance->c100_temporalCounter_i1 >= c100_u5) != 0U,
        chartInstance->c100_sfEvent) != 0U)) != 0);
      if (c100_h_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 30U, chartInstance->c100_sfEvent);
        chartInstance->c100_e_tp_OFF = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_A4FLASH_A1FLASH = c100_IN_ON;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 23U, chartInstance->c100_sfEvent);
        chartInstance->c100_temporalCounter_i1 = 0U;
        chartInstance->c100_f_tp_ON = 1U;
        *chartInstance->c100_disp_RightControl =
          chartInstance->c100_MODE_RIGHT_AUX1;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_disp_LeftControl =
          chartInstance->c100_MODE_LEFT_AUX4;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 22U,
                     chartInstance->c100_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 22U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_ON:
      CV_STATE_EVAL(20, 0, c100_IN_ON);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 29U,
                   chartInstance->c100_sfEvent);
      c100_u6 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
        ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 29U),
        83U, 1U, 5U);
      c100_i_out = (CV_TRANSITION_EVAL(29U, (int32_T)(_SFD_CCP_CALL(5U, 29U, 0,
        (chartInstance->c100_temporalCounter_i1 >= c100_u6) != 0U,
        chartInstance->c100_sfEvent) != 0U)) != 0);
      if (c100_i_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 29U, chartInstance->c100_sfEvent);
        chartInstance->c100_f_tp_ON = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c100_sfEvent);
        chartInstance->c100_is_A4FLASH_A1FLASH = c100_IN_OFF;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 22U, chartInstance->c100_sfEvent);
        chartInstance->c100_temporalCounter_i1 = 0U;
        chartInstance->c100_e_tp_OFF = 1U;
        *chartInstance->c100_disp_RightControl =
          chartInstance->c100_MODE_RIGHT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl,
                              10U);
        *chartInstance->c100_disp_LeftControl =
          chartInstance->c100_MODE_LEFT_NONE;
        _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 23U,
                     chartInstance->c100_sfEvent);
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 23U, chartInstance->c100_sfEvent);
      break;

     default:
      CV_STATE_EVAL(20, 0, 0);

      /* Unreachable state, for coverage only */
      chartInstance->c100_is_A4FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c100_sfEvent);
      break;
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 20U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_A4FLASH_OF:
    CV_STATE_EVAL(11, 0, c100_IN_A4FLASH_OF);
    c100_A4FLASH_OF(chartInstance);
    break;

   case c100_IN_Default:
    CV_STATE_EVAL(11, 0, c100_IN_Default);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 28U,
                 chartInstance->c100_sfEvent);
    *chartInstance->c100_disp_LeftControl =
      *chartInstance->c100_mode_LeftControl;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
    *chartInstance->c100_disp_RightControl =
      *chartInstance->c100_mode_RightControl;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 28U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_OF_A1FLASH:
    CV_STATE_EVAL(11, 0, c100_IN_OF_A1FLASH);
    c100_OF_A1FLASH(chartInstance);
    break;

   case c100_IN_OF_A4FLASH:
    CV_STATE_EVAL(11, 0, c100_IN_OF_A4FLASH);
    c100_OF_A4FLASH(chartInstance);
    break;

   default:
    CV_STATE_EVAL(11, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c100_is_Flasher = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c100_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c100_sfEvent);
}

static void c100_exit_internal_Flasher(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c100_is_Flasher) {
   case c100_IN_A2FLASH_A1FLASH:
    CV_STATE_EVAL(11, 1, c100_IN_A2FLASH_A1FLASH);
    switch (chartInstance->c100_is_A2FLASH_A1FLASH) {
     case c100_IN_GLOW_OFF:
      CV_STATE_EVAL(12, 1, c100_IN_GLOW_OFF);
      chartInstance->c100_c_tp_GLOW_OFF = 0U;
      chartInstance->c100_is_A2FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_OFF:
      CV_STATE_EVAL(12, 1, c100_IN_OFF);
      chartInstance->c100_c_tp_OFF = 0U;
      chartInstance->c100_is_A2FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_ON:
      CV_STATE_EVAL(12, 1, c100_IN_ON);
      chartInstance->c100_c_tp_ON = 0U;
      chartInstance->c100_is_A2FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c100_sfEvent);
      break;

     default:
      CV_STATE_EVAL(12, 1, 0);
      chartInstance->c100_is_A2FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c100_sfEvent);
      break;
    }

    chartInstance->c100_tp_A2FLASH_A1FLASH = 0U;
    chartInstance->c100_is_Flasher = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_A2FLASH_A4FLASH:
    CV_STATE_EVAL(11, 1, c100_IN_A2FLASH_A4FLASH);
    switch (chartInstance->c100_is_A2FLASH_A4FLASH) {
     case c100_IN_GLOW_OFF:
      CV_STATE_EVAL(16, 1, c100_IN_GLOW_OFF);
      chartInstance->c100_d_tp_GLOW_OFF = 0U;
      chartInstance->c100_is_A2FLASH_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_OFF:
      CV_STATE_EVAL(16, 1, c100_IN_OFF);
      chartInstance->c100_d_tp_OFF = 0U;
      chartInstance->c100_is_A2FLASH_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_ON:
      CV_STATE_EVAL(16, 1, c100_IN_ON);
      chartInstance->c100_d_tp_ON = 0U;
      chartInstance->c100_is_A2FLASH_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c100_sfEvent);
      break;

     default:
      CV_STATE_EVAL(16, 1, 0);
      chartInstance->c100_is_A2FLASH_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c100_sfEvent);
      break;
    }

    chartInstance->c100_tp_A2FLASH_A4FLASH = 0U;
    chartInstance->c100_is_Flasher = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_A4FLASH_A1FLASH:
    CV_STATE_EVAL(11, 1, c100_IN_A4FLASH_A1FLASH);
    switch (chartInstance->c100_is_A4FLASH_A1FLASH) {
     case c100_IN_GLOW_OFF:
      CV_STATE_EVAL(20, 1, c100_IN_GLOW_OFF);
      chartInstance->c100_f_tp_GLOW_OFF = 0U;
      chartInstance->c100_is_A4FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_OFF:
      CV_STATE_EVAL(20, 1, c100_IN_OFF);
      chartInstance->c100_e_tp_OFF = 0U;
      chartInstance->c100_is_A4FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 22U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_ON:
      CV_STATE_EVAL(20, 1, c100_IN_ON);
      chartInstance->c100_f_tp_ON = 0U;
      chartInstance->c100_is_A4FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 23U, chartInstance->c100_sfEvent);
      break;

     default:
      CV_STATE_EVAL(20, 1, 0);
      chartInstance->c100_is_A4FLASH_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 21U, chartInstance->c100_sfEvent);
      break;
    }

    chartInstance->c100_tp_A4FLASH_A1FLASH = 0U;
    chartInstance->c100_is_Flasher = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 20U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_A4FLASH_OF:
    CV_STATE_EVAL(11, 1, c100_IN_A4FLASH_OF);
    switch (chartInstance->c100_is_A4FLASH_OF) {
     case c100_IN_GLOW_OFF:
      CV_STATE_EVAL(24, 1, c100_IN_GLOW_OFF);
      chartInstance->c100_e_tp_GLOW_OFF = 0U;
      chartInstance->c100_is_A4FLASH_OF = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c100_sfEvent);
      break;

     case c100_b_IN_ON:
      CV_STATE_EVAL(24, 1, c100_b_IN_ON);
      chartInstance->c100_e_tp_ON = 0U;
      chartInstance->c100_is_A4FLASH_OF = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_ON1:
      CV_STATE_EVAL(24, 1, c100_IN_ON1);
      chartInstance->c100_tp_ON1 = 0U;
      chartInstance->c100_is_A4FLASH_OF = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c100_sfEvent);
      break;

     default:
      CV_STATE_EVAL(24, 1, 0);
      chartInstance->c100_is_A4FLASH_OF = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c100_sfEvent);
      break;
    }

    chartInstance->c100_tp_A4FLASH_OF = 0U;
    chartInstance->c100_is_Flasher = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 24U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_Default:
    CV_STATE_EVAL(11, 1, c100_IN_Default);
    chartInstance->c100_tp_Default = 0U;
    chartInstance->c100_is_Flasher = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 28U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_OF_A1FLASH:
    CV_STATE_EVAL(11, 1, c100_IN_OF_A1FLASH);
    switch (chartInstance->c100_is_OF_A1FLASH) {
     case c100_IN_GLOW_OFF:
      CV_STATE_EVAL(29, 1, c100_IN_GLOW_OFF);
      chartInstance->c100_tp_GLOW_OFF = 0U;
      chartInstance->c100_is_OF_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_OFF:
      CV_STATE_EVAL(29, 1, c100_IN_OFF);
      chartInstance->c100_tp_OFF = 0U;
      chartInstance->c100_is_OF_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_ON:
      CV_STATE_EVAL(29, 1, c100_IN_ON);
      chartInstance->c100_tp_ON = 0U;
      chartInstance->c100_is_OF_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c100_sfEvent);
      break;

     default:
      CV_STATE_EVAL(29, 1, 0);
      chartInstance->c100_is_OF_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c100_sfEvent);
      break;
    }

    chartInstance->c100_tp_OF_A1FLASH = 0U;
    chartInstance->c100_is_Flasher = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 29U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_OF_A4FLASH:
    CV_STATE_EVAL(11, 1, c100_IN_OF_A4FLASH);
    switch (chartInstance->c100_is_OF_A4FLASH) {
     case c100_IN_GLOW_OFF:
      CV_STATE_EVAL(33, 1, c100_IN_GLOW_OFF);
      chartInstance->c100_b_tp_GLOW_OFF = 0U;
      chartInstance->c100_is_OF_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_OFF:
      CV_STATE_EVAL(33, 1, c100_IN_OFF);
      chartInstance->c100_b_tp_OFF = 0U;
      chartInstance->c100_is_OF_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c100_sfEvent);
      break;

     case c100_IN_ON:
      CV_STATE_EVAL(33, 1, c100_IN_ON);
      chartInstance->c100_b_tp_ON = 0U;
      chartInstance->c100_is_OF_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c100_sfEvent);
      break;

     default:
      CV_STATE_EVAL(33, 1, 0);
      chartInstance->c100_is_OF_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c100_sfEvent);
      break;
    }

    chartInstance->c100_tp_OF_A4FLASH = 0U;
    chartInstance->c100_is_Flasher = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 33U, chartInstance->c100_sfEvent);
    break;

   default:
    CV_STATE_EVAL(11, 1, 0);
    chartInstance->c100_is_Flasher = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c100_sfEvent);
    break;
  }
}

static void c100_OF_A1FLASH(SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c100_out;
  uint16_T c100_u7;
  uint16_T c100_u8;
  boolean_T c100_b_out;
  boolean_T c100_c_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 29U, chartInstance->c100_sfEvent);
  switch (chartInstance->c100_is_OF_A1FLASH) {
   case c100_IN_GLOW_OFF:
    CV_STATE_EVAL(29, 0, c100_IN_GLOW_OFF);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U,
                 chartInstance->c100_sfEvent);
    c100_out = (CV_TRANSITION_EVAL(7U, !(_SFD_CCP_CALL(5U, 7U, 0,
      *chartInstance->c100_dout_GlowPlugs != 0U, chartInstance->c100_sfEvent) !=
      0U)) != 0);
    if (c100_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c100_sfEvent);
      chartInstance->c100_tp_GLOW_OFF = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_OF_A1FLASH = c100_IN_ON;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c100_sfEvent);
      chartInstance->c100_temporalCounter_i1 = 0U;
      chartInstance->c100_tp_ON = 1U;
      *chartInstance->c100_disp_RightControl =
        chartInstance->c100_MODE_RIGHT_AUX1;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 30U,
                   chartInstance->c100_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 30U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_OFF:
    CV_STATE_EVAL(29, 0, c100_IN_OFF);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 9U,
                 chartInstance->c100_sfEvent);
    c100_u7 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
      ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 9U), 27U,
      1U, 5U);
    c100_b_out = (CV_TRANSITION_EVAL(9U, (int32_T)(_SFD_CCP_CALL(5U, 9U, 0,
      (chartInstance->c100_temporalCounter_i1 >= c100_u7) != 0U,
      chartInstance->c100_sfEvent) != 0U)) != 0);
    if (c100_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c100_sfEvent);
      chartInstance->c100_tp_OFF = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 31U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_OF_A1FLASH = c100_IN_ON;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 32U, chartInstance->c100_sfEvent);
      chartInstance->c100_temporalCounter_i1 = 0U;
      chartInstance->c100_tp_ON = 1U;
      *chartInstance->c100_disp_RightControl =
        chartInstance->c100_MODE_RIGHT_AUX1;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 31U,
                   chartInstance->c100_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 31U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_ON:
    CV_STATE_EVAL(29, 0, c100_IN_ON);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                 chartInstance->c100_sfEvent);
    c100_u8 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
      ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 8U), 26U,
      1U, 5U);
    c100_c_out = (CV_TRANSITION_EVAL(8U, (int32_T)(_SFD_CCP_CALL(5U, 8U, 0,
      (chartInstance->c100_temporalCounter_i1 >= c100_u8) != 0U,
      chartInstance->c100_sfEvent) != 0U)) != 0);
    if (c100_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c100_sfEvent);
      chartInstance->c100_tp_ON = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 32U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_OF_A1FLASH = c100_IN_OFF;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 31U, chartInstance->c100_sfEvent);
      chartInstance->c100_temporalCounter_i1 = 0U;
      chartInstance->c100_tp_OFF = 1U;
      *chartInstance->c100_disp_RightControl =
        chartInstance->c100_MODE_RIGHT_NONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 32U,
                   chartInstance->c100_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 32U, chartInstance->c100_sfEvent);
    break;

   default:
    CV_STATE_EVAL(29, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c100_is_OF_A1FLASH = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 30U, chartInstance->c100_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 29U, chartInstance->c100_sfEvent);
}

static void c100_OF_A4FLASH(SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c100_out;
  uint16_T c100_u9;
  uint16_T c100_u10;
  boolean_T c100_b_out;
  boolean_T c100_c_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 33U, chartInstance->c100_sfEvent);
  switch (chartInstance->c100_is_OF_A4FLASH) {
   case c100_IN_GLOW_OFF:
    CV_STATE_EVAL(33, 0, c100_IN_GLOW_OFF);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 35U,
                 chartInstance->c100_sfEvent);
    c100_out = (CV_TRANSITION_EVAL(35U, !(_SFD_CCP_CALL(5U, 35U, 0,
      *chartInstance->c100_dout_GlowPlugs != 0U, chartInstance->c100_sfEvent) !=
      0U)) != 0);
    if (c100_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 35U, chartInstance->c100_sfEvent);
      chartInstance->c100_b_tp_GLOW_OFF = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_OF_A4FLASH = c100_IN_ON;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c100_sfEvent);
      chartInstance->c100_temporalCounter_i1 = 0U;
      chartInstance->c100_b_tp_ON = 1U;
      *chartInstance->c100_disp_RightControl =
        chartInstance->c100_MODE_RIGHT_AUX4;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 34U,
                   chartInstance->c100_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 34U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_OFF:
    CV_STATE_EVAL(33, 0, c100_IN_OFF);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                 chartInstance->c100_sfEvent);
    c100_u9 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
      ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 11U), 31U,
      1U, 5U);
    c100_b_out = (CV_TRANSITION_EVAL(11U, (int32_T)(_SFD_CCP_CALL(5U, 11U, 0,
      (chartInstance->c100_temporalCounter_i1 >= c100_u9) != 0U,
      chartInstance->c100_sfEvent) != 0U)) != 0);
    if (c100_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c100_sfEvent);
      chartInstance->c100_b_tp_OFF = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 35U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_OF_A4FLASH = c100_IN_ON;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 36U, chartInstance->c100_sfEvent);
      chartInstance->c100_temporalCounter_i1 = 0U;
      chartInstance->c100_b_tp_ON = 1U;
      *chartInstance->c100_disp_RightControl =
        chartInstance->c100_MODE_RIGHT_AUX4;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 35U,
                   chartInstance->c100_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 35U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_ON:
    CV_STATE_EVAL(33, 0, c100_IN_ON);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                 chartInstance->c100_sfEvent);
    c100_u10 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
      ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 10U), 30U,
      1U, 5U);
    c100_c_out = (CV_TRANSITION_EVAL(10U, (int32_T)(_SFD_CCP_CALL(5U, 10U, 0,
      (chartInstance->c100_temporalCounter_i1 >= c100_u10) != 0U,
      chartInstance->c100_sfEvent) != 0U)) != 0);
    if (c100_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c100_sfEvent);
      chartInstance->c100_b_tp_ON = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 36U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_OF_A4FLASH = c100_IN_OFF;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 35U, chartInstance->c100_sfEvent);
      chartInstance->c100_temporalCounter_i1 = 0U;
      chartInstance->c100_b_tp_OFF = 1U;
      *chartInstance->c100_disp_RightControl =
        chartInstance->c100_MODE_RIGHT_NONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_RightControl, 10U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 36U,
                   chartInstance->c100_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 36U, chartInstance->c100_sfEvent);
    break;

   default:
    CV_STATE_EVAL(33, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c100_is_OF_A4FLASH = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 34U, chartInstance->c100_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 33U, chartInstance->c100_sfEvent);
}

static void c100_A4FLASH_OF(SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  boolean_T c100_out;
  uint16_T c100_u11;
  uint16_T c100_u12;
  boolean_T c100_b_out;
  boolean_T c100_c_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 24U, chartInstance->c100_sfEvent);
  switch (chartInstance->c100_is_A4FLASH_OF) {
   case c100_IN_GLOW_OFF:
    CV_STATE_EVAL(24, 0, c100_IN_GLOW_OFF);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 40U,
                 chartInstance->c100_sfEvent);
    c100_out = (CV_TRANSITION_EVAL(40U, !(_SFD_CCP_CALL(5U, 40U, 0,
      *chartInstance->c100_dout_GlowPlugs != 0U, chartInstance->c100_sfEvent) !=
      0U)) != 0);
    if (c100_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 40U, chartInstance->c100_sfEvent);
      chartInstance->c100_e_tp_GLOW_OFF = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_A4FLASH_OF = c100_b_IN_ON;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c100_sfEvent);
      chartInstance->c100_temporalCounter_i1 = 0U;
      chartInstance->c100_e_tp_ON = 1U;
      *chartInstance->c100_disp_LeftControl = chartInstance->c100_MODE_LEFT_AUX4;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 25U,
                   chartInstance->c100_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 25U, chartInstance->c100_sfEvent);
    break;

   case c100_b_IN_ON:
    CV_STATE_EVAL(24, 0, c100_b_IN_ON);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 14U,
                 chartInstance->c100_sfEvent);
    c100_u11 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
      ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 14U), 48U,
      1U, 5U);
    c100_b_out = (CV_TRANSITION_EVAL(14U, (int32_T)(_SFD_CCP_CALL(5U, 14U, 0,
      (chartInstance->c100_temporalCounter_i1 >= c100_u11) != 0U,
      chartInstance->c100_sfEvent) != 0U)) != 0);
    if (c100_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c100_sfEvent);
      chartInstance->c100_e_tp_ON = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 26U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_A4FLASH_OF = c100_IN_ON1;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 27U, chartInstance->c100_sfEvent);
      chartInstance->c100_temporalCounter_i1 = 0U;
      chartInstance->c100_tp_ON1 = 1U;
      *chartInstance->c100_disp_LeftControl = chartInstance->c100_MODE_LEFT_NONE;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 26U,
                   chartInstance->c100_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 26U, chartInstance->c100_sfEvent);
    break;

   case c100_IN_ON1:
    CV_STATE_EVAL(24, 0, c100_IN_ON1);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                 chartInstance->c100_sfEvent);
    c100_u12 = c100__u16_u32_(chartInstance, _SFD_TRANS_TEMPORAL_THRESHOLD
      ((uint32_T)chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME, 16U, 15U), 49U,
      1U, 5U);
    c100_c_out = (CV_TRANSITION_EVAL(15U, (int32_T)(_SFD_CCP_CALL(5U, 15U, 0,
      (chartInstance->c100_temporalCounter_i1 >= c100_u12) != 0U,
      chartInstance->c100_sfEvent) != 0U)) != 0);
    if (c100_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c100_sfEvent);
      chartInstance->c100_tp_ON1 = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 27U, chartInstance->c100_sfEvent);
      chartInstance->c100_is_A4FLASH_OF = c100_b_IN_ON;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 26U, chartInstance->c100_sfEvent);
      chartInstance->c100_temporalCounter_i1 = 0U;
      chartInstance->c100_e_tp_ON = 1U;
      *chartInstance->c100_disp_LeftControl = chartInstance->c100_MODE_LEFT_AUX4;
      _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c100_disp_LeftControl, 9U);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 27U,
                   chartInstance->c100_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 27U, chartInstance->c100_sfEvent);
    break;

   default:
    CV_STATE_EVAL(24, 0, 0);

    /* Unreachable state, for coverage only */
    chartInstance->c100_is_A4FLASH_OF = c100_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 25U, chartInstance->c100_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 24U, chartInstance->c100_sfEvent);
}

static void init_script_number_translation(uint32_T c100_machineNumber, uint32_T
  c100_chartNumber, uint32_T c100_instanceNumber)
{
  (void)(c100_machineNumber);
  (void)(c100_chartNumber);
  (void)(c100_instanceNumber);
}

const mxArray *sf_c100_MX_Gtwy_Control_get_eml_resolved_functions_info(void)
{
  const mxArray *c100_nameCaptureInfo = NULL;
  c100_nameCaptureInfo = NULL;
  sf_mex_assign(&c100_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c100_nameCaptureInfo;
}

static const mxArray *c100_sf_marshallOut(void *chartInstanceVoid, void
  *c100_inData)
{
  const mxArray *c100_mxArrayOutData;
  int32_T c100_u;
  const mxArray *c100_y = NULL;
  SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc100_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c100_mxArrayOutData = NULL;
  c100_mxArrayOutData = NULL;
  c100_u = *(int32_T *)c100_inData;
  c100_y = NULL;
  sf_mex_assign(&c100_y, sf_mex_create("y", &c100_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c100_mxArrayOutData, c100_y, false);
  return c100_mxArrayOutData;
}

static int32_T c100_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_u, const emlrtMsgIdentifier *c100_parentId)
{
  int32_T c100_y;
  int32_T c100_i2;
  (void)chartInstance;
  sf_mex_import(c100_parentId, sf_mex_dup(c100_u), &c100_i2, 1, 6, 0U, 0, 0U, 0);
  c100_y = c100_i2;
  sf_mex_destroy(&c100_u);
  return c100_y;
}

static void c100_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c100_mxArrayInData, const char_T *c100_varName, void *c100_outData)
{
  const mxArray *c100_b_sfEvent;
  emlrtMsgIdentifier c100_thisId;
  int32_T c100_y;
  SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc100_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c100_b_sfEvent = sf_mex_dup(c100_mxArrayInData);
  c100_thisId.fIdentifier = (const char *)c100_varName;
  c100_thisId.fParent = NULL;
  c100_thisId.bParentIsCell = false;
  c100_y = c100_emlrt_marshallIn(chartInstance, sf_mex_dup(c100_b_sfEvent),
    &c100_thisId);
  sf_mex_destroy(&c100_b_sfEvent);
  *(int32_T *)c100_outData = c100_y;
  sf_mex_destroy(&c100_mxArrayInData);
}

static const mxArray *c100_b_sf_marshallOut(void *chartInstanceVoid, void
  *c100_inData)
{
  const mxArray *c100_mxArrayOutData;
  uint8_T c100_u;
  const mxArray *c100_y = NULL;
  SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc100_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c100_mxArrayOutData = NULL;
  c100_mxArrayOutData = NULL;
  c100_u = *(uint8_T *)c100_inData;
  c100_y = NULL;
  sf_mex_assign(&c100_y, sf_mex_create("y", &c100_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c100_mxArrayOutData, c100_y, false);
  return c100_mxArrayOutData;
}

static uint8_T c100_b_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_b_tp_Normal, const char_T *c100_identifier)
{
  uint8_T c100_y;
  emlrtMsgIdentifier c100_thisId;
  c100_thisId.fIdentifier = (const char *)c100_identifier;
  c100_thisId.fParent = NULL;
  c100_thisId.bParentIsCell = false;
  c100_y = c100_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c100_b_tp_Normal),
    &c100_thisId);
  sf_mex_destroy(&c100_b_tp_Normal);
  return c100_y;
}

static uint8_T c100_c_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_u, const emlrtMsgIdentifier *c100_parentId)
{
  uint8_T c100_y;
  uint8_T c100_u13;
  (void)chartInstance;
  sf_mex_import(c100_parentId, sf_mex_dup(c100_u), &c100_u13, 1, 3, 0U, 0, 0U, 0);
  c100_y = c100_u13;
  sf_mex_destroy(&c100_u);
  return c100_y;
}

static void c100_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c100_mxArrayInData, const char_T *c100_varName, void *c100_outData)
{
  const mxArray *c100_b_tp_Normal;
  emlrtMsgIdentifier c100_thisId;
  uint8_T c100_y;
  SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc100_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c100_b_tp_Normal = sf_mex_dup(c100_mxArrayInData);
  c100_thisId.fIdentifier = (const char *)c100_varName;
  c100_thisId.fParent = NULL;
  c100_thisId.bParentIsCell = false;
  c100_y = c100_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c100_b_tp_Normal),
    &c100_thisId);
  sf_mex_destroy(&c100_b_tp_Normal);
  *(uint8_T *)c100_outData = c100_y;
  sf_mex_destroy(&c100_mxArrayInData);
}

static const mxArray *c100_c_sf_marshallOut(void *chartInstanceVoid, void
  *c100_inData)
{
  const mxArray *c100_mxArrayOutData;
  boolean_T c100_u;
  const mxArray *c100_y = NULL;
  SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc100_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c100_mxArrayOutData = NULL;
  c100_mxArrayOutData = NULL;
  c100_u = *(boolean_T *)c100_inData;
  c100_y = NULL;
  sf_mex_assign(&c100_y, sf_mex_create("y", &c100_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c100_mxArrayOutData, c100_y, false);
  return c100_mxArrayOutData;
}

static boolean_T c100_d_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_b_flag_AuxEnableFlash, const char_T
  *c100_identifier)
{
  boolean_T c100_y;
  emlrtMsgIdentifier c100_thisId;
  c100_thisId.fIdentifier = (const char *)c100_identifier;
  c100_thisId.fParent = NULL;
  c100_thisId.bParentIsCell = false;
  c100_y = c100_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c100_b_flag_AuxEnableFlash), &c100_thisId);
  sf_mex_destroy(&c100_b_flag_AuxEnableFlash);
  return c100_y;
}

static boolean_T c100_e_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_u, const emlrtMsgIdentifier *c100_parentId)
{
  boolean_T c100_y;
  boolean_T c100_b0;
  (void)chartInstance;
  sf_mex_import(c100_parentId, sf_mex_dup(c100_u), &c100_b0, 1, 11, 0U, 0, 0U, 0);
  c100_y = c100_b0;
  sf_mex_destroy(&c100_u);
  return c100_y;
}

static void c100_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c100_mxArrayInData, const char_T *c100_varName, void *c100_outData)
{
  const mxArray *c100_b_flag_AuxEnableFlash;
  emlrtMsgIdentifier c100_thisId;
  boolean_T c100_y;
  SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc100_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c100_b_flag_AuxEnableFlash = sf_mex_dup(c100_mxArrayInData);
  c100_thisId.fIdentifier = (const char *)c100_varName;
  c100_thisId.fParent = NULL;
  c100_thisId.bParentIsCell = false;
  c100_y = c100_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c100_b_flag_AuxEnableFlash), &c100_thisId);
  sf_mex_destroy(&c100_b_flag_AuxEnableFlash);
  *(boolean_T *)c100_outData = c100_y;
  sf_mex_destroy(&c100_mxArrayInData);
}

static const mxArray *c100_d_sf_marshallOut(void *chartInstanceVoid, void
  *c100_inData)
{
  const mxArray *c100_mxArrayOutData;
  uint16_T c100_u;
  const mxArray *c100_y = NULL;
  SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc100_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c100_mxArrayOutData = NULL;
  c100_mxArrayOutData = NULL;
  c100_u = *(uint16_T *)c100_inData;
  c100_y = NULL;
  sf_mex_assign(&c100_y, sf_mex_create("y", &c100_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c100_mxArrayOutData, c100_y, false);
  return c100_mxArrayOutData;
}

static uint16_T c100_f_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_b_CD_EMEA_CONTROLS_FLASH_TIME, const
  char_T *c100_identifier)
{
  uint16_T c100_y;
  emlrtMsgIdentifier c100_thisId;
  c100_thisId.fIdentifier = (const char *)c100_identifier;
  c100_thisId.fParent = NULL;
  c100_thisId.bParentIsCell = false;
  c100_y = c100_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c100_b_CD_EMEA_CONTROLS_FLASH_TIME), &c100_thisId);
  sf_mex_destroy(&c100_b_CD_EMEA_CONTROLS_FLASH_TIME);
  return c100_y;
}

static uint16_T c100_g_emlrt_marshallIn(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, const mxArray *c100_u, const emlrtMsgIdentifier *c100_parentId)
{
  uint16_T c100_y;
  uint16_T c100_u14;
  (void)chartInstance;
  sf_mex_import(c100_parentId, sf_mex_dup(c100_u), &c100_u14, 1, 5, 0U, 0, 0U, 0);
  c100_y = c100_u14;
  sf_mex_destroy(&c100_u);
  return c100_y;
}

static void c100_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c100_mxArrayInData, const char_T *c100_varName, void *c100_outData)
{
  const mxArray *c100_b_CD_EMEA_CONTROLS_FLASH_TIME;
  emlrtMsgIdentifier c100_thisId;
  uint16_T c100_y;
  SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc100_MX_Gtwy_ControlInstanceStruct *)chartInstanceVoid;
  c100_b_CD_EMEA_CONTROLS_FLASH_TIME = sf_mex_dup(c100_mxArrayInData);
  c100_thisId.fIdentifier = (const char *)c100_varName;
  c100_thisId.fParent = NULL;
  c100_thisId.bParentIsCell = false;
  c100_y = c100_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c100_b_CD_EMEA_CONTROLS_FLASH_TIME), &c100_thisId);
  sf_mex_destroy(&c100_b_CD_EMEA_CONTROLS_FLASH_TIME);
  *(uint16_T *)c100_outData = c100_y;
  sf_mex_destroy(&c100_mxArrayInData);
}

static const mxArray *c100_h_emlrt_marshallIn
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray
   *c100_b_setSimStateSideEffectsInfo, const char_T *c100_identifier)
{
  const mxArray *c100_y = NULL;
  emlrtMsgIdentifier c100_thisId;
  c100_y = NULL;
  c100_thisId.fIdentifier = (const char *)c100_identifier;
  c100_thisId.fParent = NULL;
  c100_thisId.bParentIsCell = false;
  sf_mex_assign(&c100_y, c100_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c100_b_setSimStateSideEffectsInfo), &c100_thisId), false);
  sf_mex_destroy(&c100_b_setSimStateSideEffectsInfo);
  return c100_y;
}

static const mxArray *c100_i_emlrt_marshallIn
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance, const mxArray *c100_u,
   const emlrtMsgIdentifier *c100_parentId)
{
  const mxArray *c100_y = NULL;
  (void)chartInstance;
  (void)c100_parentId;
  c100_y = NULL;
  sf_mex_assign(&c100_y, sf_mex_duplicatearraysafe(&c100_u), false);
  sf_mex_destroy(&c100_u);
  return c100_y;
}

static const mxArray *sf_get_hover_data_for_msg
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance, int32_T c100_ssid)
{
  (void)chartInstance;
  (void)c100_ssid;
  return NULL;
}

static void c100_init_sf_message_store_memory
  (SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static int32_T c100__s32_add__(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, int32_T c100_b, int32_T c100_c, uint32_T c100_ssid_src_loc,
  int32_T c100_offset_src_loc, int32_T c100_length_src_loc)
{
  int32_T c100_a;
  (void)chartInstance;
  c100_a = c100_b + c100_c;
  if (((c100_a ^ c100_b) & (c100_a ^ c100_c)) < 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c100_ssid_src_loc,
      c100_offset_src_loc, c100_length_src_loc);
  }

  return c100_a;
}

static uint16_T c100__u16_u32_(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c100_b, uint32_T c100_ssid_src_loc, int32_T
  c100_offset_src_loc, int32_T c100_length_src_loc)
{
  uint16_T c100_a;
  (void)chartInstance;
  c100_a = (uint16_T)c100_b;
  if (c100_a != c100_b) {
    _SFD_OVERFLOW_DETECTION(SFDB_OVERFLOW, c100_ssid_src_loc,
      c100_offset_src_loc, c100_length_src_loc);
  }

  return c100_a;
}

static uint8_T c100_get_ee_ControlMode(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c100_elementIndex)
{
  if (chartInstance->c100_dsmdiag_ee_ControlMode) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, "ee_ControlMode",
      c100_elementIndex);
  }

  return *chartInstance->c100_ee_ControlMode_address;
}

static void c100_set_ee_ControlMode(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance, uint32_T c100_elementIndex, uint8_T c100_elementValue)
{
  if (chartInstance->c100_dsmdiag_ee_ControlMode) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, "ee_ControlMode",
      c100_elementIndex);
  }

  *chartInstance->c100_ee_ControlMode_address = c100_elementValue;
}

static uint8_T *c100_access_ee_ControlMode(SFc100_MX_Gtwy_ControlInstanceStruct *
  chartInstance, uint32_T c100_rdOnly)
{
  if (chartInstance->c100_dsmdiag_ee_ControlMode) {
    ssAccessDataStore_wrapper(chartInstance->S, 0, "ee_ControlMode", c100_rdOnly);
  }

  return chartInstance->c100_ee_ControlMode_address;
}

static void init_dsm_address_info(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "ee_ControlMode",
    (void **)&chartInstance->c100_ee_ControlMode_address,
    &chartInstance->c100__indextrolMode);
}

static void init_simulink_io_address(SFc100_MX_Gtwy_ControlInstanceStruct
  *chartInstance)
{
  chartInstance->c100_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c100_disp_LeftControl = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c100_disp_RightControl = (uint8_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 2);
  chartInstance->c100_mode_LeftControl = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c100_mode_RightControl = (uint8_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c100_state_AuxEnable = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c100_flag_AuxEnableFlash = (boolean_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c100_flag_InitEERead = (boolean_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c100_dout_GlowPlugs = (boolean_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c100_state_Console = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c100_state_Engine = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c100_state_System = (uint8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c100_dsmdiag_ee_ControlMode = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 0,
    "ee_ControlMode");
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

void sf_c100_MX_Gtwy_Control_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2707660928U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1978379932U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1411779295U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1329260889U);
}

mxArray* sf_c100_MX_Gtwy_Control_get_post_codegen_info(void);
mxArray *sf_c100_MX_Gtwy_Control_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("Cl6irihn7evt2wW54IxUVH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c100_MX_Gtwy_Control_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c100_MX_Gtwy_Control_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c100_MX_Gtwy_Control_jit_fallback_info(void)
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

mxArray *sf_c100_MX_Gtwy_Control_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c100_MX_Gtwy_Control_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c100_MX_Gtwy_Control(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[88],T\"disp_LeftControl\",},{M[1],M[89],T\"disp_RightControl\",},{M[1],M[93],T\"flag_AuxEnableFlash\",},{M[3],M[149],T\"flash_timer\",},{M[8],M[0],T\"is_active_c100_MX_Gtwy_Control\",},{M[8],M[141],T\"is_active_Flasher\",},{M[8],M[142],T\"is_active_FlashTimer\",},{M[9],M[0],T\"is_c100_MX_Gtwy_Control\",},{M[9],M[19],T\"is_OF_A1FLASH\",},{M[9],M[28],T\"is_OF_A4FLASH\",}}",
    "100 S1x7'type','srcId','name','auxInfo'{{M[9],M[34],T\"is_A2FLASH_A1FLASH\",},{M[9],M[46],T\"is_A4FLASH_OF\",},{M[9],M[75],T\"is_A2FLASH_A4FLASH\",},{M[9],M[81],T\"is_A4FLASH_A1FLASH\",},{M[9],M[141],T\"is_Flasher\",},{M[9],M[142],T\"is_FlashTimer\",},{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"wu\",M1x12[23 25 32 33 38 39 79 80 50 51 85 86],M[1]}}}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 17, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c100_MX_Gtwy_Control_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc100_MX_Gtwy_ControlInstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc100_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _MX_Gtwy_ControlMachineNumber_,
           100,
           37,
           51,
           0,
           39,
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
          _SFD_SET_DATA_PROPS(0,0,0,0,"flash_timer");
          _SFD_SET_DATA_PROPS(1,1,1,0,"mode_LeftControl");
          _SFD_SET_DATA_PROPS(2,1,1,0,"mode_RightControl");
          _SFD_SET_DATA_PROPS(3,1,1,0,"state_AuxEnable");
          _SFD_SET_DATA_PROPS(4,1,1,0,"flag_InitEERead");
          _SFD_SET_DATA_PROPS(5,1,1,0,"dout_GlowPlugs");
          _SFD_SET_DATA_PROPS(6,1,1,0,"state_Console");
          _SFD_SET_DATA_PROPS(7,1,1,0,"state_Engine");
          _SFD_SET_DATA_PROPS(8,1,1,0,"state_System");
          _SFD_SET_DATA_PROPS(9,2,0,1,"disp_LeftControl");
          _SFD_SET_DATA_PROPS(10,2,0,1,"disp_RightControl");
          _SFD_SET_DATA_PROPS(11,2,0,1,"flag_AuxEnableFlash");
          _SFD_SET_DATA_PROPS(12,10,0,0,"ACTIVE");
          _SFD_SET_DATA_PROPS(13,10,0,0,"CD_EMEA_CONTROLS_FLASH_TIME");
          _SFD_SET_DATA_PROPS(14,10,0,0,"CD_EMEA_CONTROLS_OPTION_A");
          _SFD_SET_DATA_PROPS(15,10,0,0,"CD_EMEA_CONTROLS_REMINDER_TIME");
          _SFD_SET_DATA_PROPS(16,10,0,0,"EE_LT_A2_A1");
          _SFD_SET_DATA_PROPS(17,10,0,0,"EE_LT_A2_A4");
          _SFD_SET_DATA_PROPS(18,10,0,0,"EE_LT_OF_A1");
          _SFD_SET_DATA_PROPS(19,10,0,0,"EE_LT_OF_A4");
          _SFD_SET_DATA_PROPS(20,10,0,0,"EE_LT_OF_NA");
          _SFD_SET_DATA_PROPS(21,10,0,0,"EE_NA_NA");
          _SFD_SET_DATA_PROPS(22,10,0,0,"EE_RT_A2_A1");
          _SFD_SET_DATA_PROPS(23,10,0,0,"EE_RT_A4_A1");
          _SFD_SET_DATA_PROPS(24,10,0,0,"EE_RT_A4_OF");
          _SFD_SET_DATA_PROPS(25,10,0,0,"EE_RT_NA_OF");
          _SFD_SET_DATA_PROPS(26,10,0,0,"ENGINE_CRANKING");
          _SFD_SET_DATA_PROPS(27,10,0,0,"INACTIVE");
          _SFD_SET_DATA_PROPS(28,10,0,0,"MODE_LEFT_AUX2");
          _SFD_SET_DATA_PROPS(29,10,0,0,"MODE_LEFT_AUX4");
          _SFD_SET_DATA_PROPS(30,10,0,0,"MODE_LEFT_NONE");
          _SFD_SET_DATA_PROPS(31,10,0,0,"MODE_LEFT_OFFSET");
          _SFD_SET_DATA_PROPS(32,10,0,0,"MODE_RIGHT_AUX1");
          _SFD_SET_DATA_PROPS(33,10,0,0,"MODE_RIGHT_AUX4");
          _SFD_SET_DATA_PROPS(34,10,0,0,"MODE_RIGHT_NONE");
          _SFD_SET_DATA_PROPS(35,10,0,0,"MODE_RIGHT_OFFSET");
          _SFD_SET_DATA_PROPS(36,10,0,0,"NON_FUNCTIONAL");
          _SFD_SET_DATA_PROPS(37,10,0,0,"SYS_NORMAL");
          _SFD_SET_DATA_PROPS(38,11,0,0,"ee_ControlMode");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,1,0);
          _SFD_STATE_INFO(4,0,1);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_STATE_INFO(9,0,0);
          _SFD_STATE_INFO(10,0,0);
          _SFD_STATE_INFO(11,0,1);
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
          _SFD_CH_SUBSTATE_COUNT(4);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,2);
          _SFD_CH_SUBSTATE_INDEX(3,3);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,2);
          _SFD_ST_SUBSTATE_INDEX(3,0,11);
          _SFD_ST_SUBSTATE_INDEX(3,1,4);
          _SFD_ST_SUBSTATE_COUNT(11,7);
          _SFD_ST_SUBSTATE_INDEX(11,0,12);
          _SFD_ST_SUBSTATE_INDEX(11,1,16);
          _SFD_ST_SUBSTATE_INDEX(11,2,20);
          _SFD_ST_SUBSTATE_INDEX(11,3,24);
          _SFD_ST_SUBSTATE_INDEX(11,4,28);
          _SFD_ST_SUBSTATE_INDEX(11,5,29);
          _SFD_ST_SUBSTATE_INDEX(11,6,33);
          _SFD_ST_SUBSTATE_COUNT(12,3);
          _SFD_ST_SUBSTATE_INDEX(12,0,13);
          _SFD_ST_SUBSTATE_INDEX(12,1,14);
          _SFD_ST_SUBSTATE_INDEX(12,2,15);
          _SFD_ST_SUBSTATE_COUNT(13,0);
          _SFD_ST_SUBSTATE_COUNT(14,0);
          _SFD_ST_SUBSTATE_COUNT(15,0);
          _SFD_ST_SUBSTATE_COUNT(16,3);
          _SFD_ST_SUBSTATE_INDEX(16,0,17);
          _SFD_ST_SUBSTATE_INDEX(16,1,18);
          _SFD_ST_SUBSTATE_INDEX(16,2,19);
          _SFD_ST_SUBSTATE_COUNT(17,0);
          _SFD_ST_SUBSTATE_COUNT(18,0);
          _SFD_ST_SUBSTATE_COUNT(19,0);
          _SFD_ST_SUBSTATE_COUNT(20,3);
          _SFD_ST_SUBSTATE_INDEX(20,0,21);
          _SFD_ST_SUBSTATE_INDEX(20,1,22);
          _SFD_ST_SUBSTATE_INDEX(20,2,23);
          _SFD_ST_SUBSTATE_COUNT(21,0);
          _SFD_ST_SUBSTATE_COUNT(22,0);
          _SFD_ST_SUBSTATE_COUNT(23,0);
          _SFD_ST_SUBSTATE_COUNT(24,3);
          _SFD_ST_SUBSTATE_INDEX(24,0,25);
          _SFD_ST_SUBSTATE_INDEX(24,1,26);
          _SFD_ST_SUBSTATE_INDEX(24,2,27);
          _SFD_ST_SUBSTATE_COUNT(25,0);
          _SFD_ST_SUBSTATE_COUNT(26,0);
          _SFD_ST_SUBSTATE_COUNT(27,0);
          _SFD_ST_SUBSTATE_COUNT(28,0);
          _SFD_ST_SUBSTATE_COUNT(29,3);
          _SFD_ST_SUBSTATE_INDEX(29,0,30);
          _SFD_ST_SUBSTATE_INDEX(29,1,31);
          _SFD_ST_SUBSTATE_INDEX(29,2,32);
          _SFD_ST_SUBSTATE_COUNT(30,0);
          _SFD_ST_SUBSTATE_COUNT(31,0);
          _SFD_ST_SUBSTATE_COUNT(32,0);
          _SFD_ST_SUBSTATE_COUNT(33,3);
          _SFD_ST_SUBSTATE_INDEX(33,0,34);
          _SFD_ST_SUBSTATE_INDEX(33,1,35);
          _SFD_ST_SUBSTATE_INDEX(33,2,36);
          _SFD_ST_SUBSTATE_COUNT(34,0);
          _SFD_ST_SUBSTATE_COUNT(35,0);
          _SFD_ST_SUBSTATE_COUNT(36,0);
          _SFD_ST_SUBSTATE_COUNT(4,6);
          _SFD_ST_SUBSTATE_INDEX(4,0,5);
          _SFD_ST_SUBSTATE_INDEX(4,1,6);
          _SFD_ST_SUBSTATE_INDEX(4,2,7);
          _SFD_ST_SUBSTATE_INDEX(4,3,8);
          _SFD_ST_SUBSTATE_INDEX(4,4,9);
          _SFD_ST_SUBSTATE_INDEX(4,5,10);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,0);
          _SFD_ST_SUBSTATE_COUNT(10,0);
        }

        _SFD_CV_INIT_CHART(4,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,2,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,6,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartSaturateMap[] = { 13 };

          static unsigned int sEndSaturateMap[] = { 26 };

          _SFD_CV_INIT_STATE_SATURATION(9,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(10,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartSaturateMap[] = { 12 };

          static unsigned int sEndSaturateMap[] = { 25 };

          _SFD_CV_INIT_STATE_SATURATION(10,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          _SFD_CV_INIT_STATE(11,7,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(16,3,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(20,3,1,1,0,0,NULL,NULL);
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

        {
          _SFD_CV_INIT_STATE(24,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(25,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(26,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(27,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(28,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(29,3,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(33,3,1,1,0,0,NULL,NULL);
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

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 31, 64 };

          static unsigned int sEndGuardMap[] = { 24, 57, 95 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2 };

          _SFD_CV_INIT_TRANS(50,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 31, 64 };

          static unsigned int sEndRelationalopMap[] = { 24, 57, 95 };

          static int sRelationalopEps[] = { 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 1, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(50,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 60, 93, 129, 167, 190 };

          static unsigned int sEndGuardMap[] = { 86, 122, 158, 182, 233 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -3, 4, -2 };

          _SFD_CV_INIT_TRANS(4,5,&(sStartGuardMap[0]),&(sEndGuardMap[0]),9,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 60, 93, 129, 190 };

          static unsigned int sEndRelationalopMap[] = { 86, 122, 158, 233 };

          static int sRelationalopEps[] = { 0, 0, 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 1, 0, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(4,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 34, 57, 98, 142, 172, 205 };

          static unsigned int sEndGuardMap[] = { 49, 91, 134, 165, 198, 236 };

          static int sPostFixPredicateTree[] = { 0, 1, 2, -2, -3, 3, -3, 4, -3,
            5, -3 };

          _SFD_CV_INIT_TRANS(5,6,&(sStartGuardMap[0]),&(sEndGuardMap[0]),11,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 57, 98, 142, 172, 205
          };

          static unsigned int sEndRelationalopMap[] = { 91, 134, 165, 198, 236 };

          static int sRelationalopEps[] = { 0, 0, 0, 0, 0 };

          static int sRelationalopType[] = { 1, 1, 0, 0, 1, 1, 1, 0, 0, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(5,5,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 36, 68, 115, 147 };

          static unsigned int sEndGuardMap[] = { 64, 106, 143, 183 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, 3, -3, -2 };

          _SFD_CV_INIT_TRANS(32,4,&(sStartGuardMap[0]),&(sEndGuardMap[0]),7,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 36, 68, 115, 147 };

          static unsigned int sEndRelationalopMap[] = { 64, 106, 143, 183 };

          static int sRelationalopEps[] = { 0, 0, 0, 0 };

          static int sRelationalopType[] = { 2, 0, 4, 0, 2, 0, 4, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(32,4,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(31,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 58 };

          static unsigned int sEndGuardMap[] = { 102 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(1,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 58 };

          static unsigned int sEndRelationalopMap[] = { 102 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 55, 89 };

          static unsigned int sEndGuardMap[] = { 82, 115 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(2,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 55, 89 };

          static unsigned int sEndRelationalopMap[] = { 82, 115 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 1, 0, 1, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(6,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(6,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(17,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(17,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(18,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 37 };

          static unsigned int sEndGuardMap[] = { 30, 65 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(19,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 37 };

          static unsigned int sEndRelationalopMap[] = { 30, 65 };

          static int sRelationalopEps[] = { 0, 0 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(19,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(20,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(21,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(21,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(22,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(23,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(23,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(24,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(25,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(25,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(26,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(33,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0, -1 };

          _SFD_CV_INIT_TRANS(7,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),2,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(8,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(9,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(34,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0, -1 };

          _SFD_CV_INIT_TRANS(35,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),2,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(10,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(11,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(37,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0, -1 };

          _SFD_CV_INIT_TRANS(36,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),2,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(12,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(13,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(39,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0, -1 };

          _SFD_CV_INIT_TRANS(38,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),2,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(27,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(28,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(41,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0, -1 };

          _SFD_CV_INIT_TRANS(40,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),2,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(14,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(15,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(43,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0, -1 };

          _SFD_CV_INIT_TRANS(42,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),2,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(29,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(30,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(44,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(45,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0, -1 };

          _SFD_CV_INIT_TRANS(46,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),2,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 15 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(48,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0, -1 };

          _SFD_CV_INIT_TRANS(47,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),2,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 45 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(49,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 45 };

          static int sRelationalopEps[] = { 0 };

          static int sRelationalopType[] = { 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(49,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_d_sf_marshallOut,(MexInFcnForType)
          c100_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_c_sf_marshallOut,(MexInFcnForType)
          c100_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_d_sf_marshallOut,(MexInFcnForType)
          c100_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_d_sf_marshallOut,(MexInFcnForType)
          c100_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(27,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(28,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(29,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(30,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(31,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(32,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(33,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(34,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(35,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(36,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(37,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(38,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c100_b_sf_marshallOut,(MexInFcnForType)
          c100_b_sf_marshallIn);
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
    SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance =
      (SFc100_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(38U, (void *)
          chartInstance->c100_ee_ControlMode_address);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)chartInstance->c100_disp_LeftControl);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)
          chartInstance->c100_disp_RightControl);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c100_mode_LeftControl);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)
          chartInstance->c100_mode_RightControl);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c100_state_AuxEnable);
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)
          chartInstance->c100_flag_AuxEnableFlash);
        _SFD_SET_DATA_VALUE_PTR(13U, (void *)
          &chartInstance->c100_CD_EMEA_CONTROLS_FLASH_TIME);
        _SFD_SET_DATA_VALUE_PTR(15U, (void *)
          &chartInstance->c100_CD_EMEA_CONTROLS_REMINDER_TIME);
        _SFD_SET_DATA_VALUE_PTR(20U, (void *)&chartInstance->c100_EE_LT_OF_NA);
        _SFD_SET_DATA_VALUE_PTR(21U, (void *)&chartInstance->c100_EE_NA_NA);
        _SFD_SET_DATA_VALUE_PTR(25U, (void *)&chartInstance->c100_EE_RT_NA_OF);
        _SFD_SET_DATA_VALUE_PTR(27U, (void *)&chartInstance->c100_INACTIVE);
        _SFD_SET_DATA_VALUE_PTR(28U, (void *)&chartInstance->c100_MODE_LEFT_AUX2);
        _SFD_SET_DATA_VALUE_PTR(29U, (void *)&chartInstance->c100_MODE_LEFT_AUX4);
        _SFD_SET_DATA_VALUE_PTR(30U, (void *)&chartInstance->c100_MODE_LEFT_NONE);
        _SFD_SET_DATA_VALUE_PTR(31U, (void *)
          &chartInstance->c100_MODE_LEFT_OFFSET);
        _SFD_SET_DATA_VALUE_PTR(32U, (void *)
          &chartInstance->c100_MODE_RIGHT_AUX1);
        _SFD_SET_DATA_VALUE_PTR(33U, (void *)
          &chartInstance->c100_MODE_RIGHT_AUX4);
        _SFD_SET_DATA_VALUE_PTR(34U, (void *)
          &chartInstance->c100_MODE_RIGHT_NONE);
        _SFD_SET_DATA_VALUE_PTR(35U, (void *)
          &chartInstance->c100_MODE_RIGHT_OFFSET);
        _SFD_SET_DATA_VALUE_PTR(16U, (void *)&chartInstance->c100_EE_LT_A2_A1);
        _SFD_SET_DATA_VALUE_PTR(17U, (void *)&chartInstance->c100_EE_LT_A2_A4);
        _SFD_SET_DATA_VALUE_PTR(18U, (void *)&chartInstance->c100_EE_LT_OF_A1);
        _SFD_SET_DATA_VALUE_PTR(19U, (void *)&chartInstance->c100_EE_LT_OF_A4);
        _SFD_SET_DATA_VALUE_PTR(22U, (void *)&chartInstance->c100_EE_RT_A2_A1);
        _SFD_SET_DATA_VALUE_PTR(23U, (void *)&chartInstance->c100_EE_RT_A4_A1);
        _SFD_SET_DATA_VALUE_PTR(24U, (void *)&chartInstance->c100_EE_RT_A4_OF);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c100_flag_InitEERead);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c100_dout_GlowPlugs);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)&chartInstance->c100_flash_timer);
        _SFD_SET_DATA_VALUE_PTR(14U, (void *)
          &chartInstance->c100_CD_EMEA_CONTROLS_OPTION_A);
        _SFD_SET_DATA_VALUE_PTR(36U, (void *)&chartInstance->c100_NON_FUNCTIONAL);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c100_state_Console);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c100_state_Engine);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c100_state_System);
        _SFD_SET_DATA_VALUE_PTR(12U, (void *)&chartInstance->c100_ACTIVE);
        _SFD_SET_DATA_VALUE_PTR(26U, (void *)
          &chartInstance->c100_ENGINE_CRANKING);
        _SFD_SET_DATA_VALUE_PTR(37U, (void *)&chartInstance->c100_SYS_NORMAL);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s0dZTa6OSP8YXP03DoFV56D";
}

static void sf_opaque_initialize_c100_MX_Gtwy_Control(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc100_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c100_MX_Gtwy_Control((SFc100_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
  initialize_c100_MX_Gtwy_Control((SFc100_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c100_MX_Gtwy_Control(void *chartInstanceVar)
{
  enable_c100_MX_Gtwy_Control((SFc100_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c100_MX_Gtwy_Control(void *chartInstanceVar)
{
  disable_c100_MX_Gtwy_Control((SFc100_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c100_MX_Gtwy_Control(void *chartInstanceVar)
{
  sf_gateway_c100_MX_Gtwy_Control((SFc100_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c100_MX_Gtwy_Control(SimStruct* S)
{
  return get_sim_state_c100_MX_Gtwy_Control
    ((SFc100_MX_Gtwy_ControlInstanceStruct *)sf_get_chart_instance_ptr(S));/* raw sim ctx */
}

static void sf_opaque_set_sim_state_c100_MX_Gtwy_Control(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c100_MX_Gtwy_Control((SFc100_MX_Gtwy_ControlInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c100_MX_Gtwy_Control(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc100_MX_Gtwy_ControlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_MX_Gtwy_Control_optimization_info();
    }

    finalize_c100_MX_Gtwy_Control((SFc100_MX_Gtwy_ControlInstanceStruct*)
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
  initSimStructsc100_MX_Gtwy_Control((SFc100_MX_Gtwy_ControlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c100_MX_Gtwy_Control(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c100_MX_Gtwy_Control((SFc100_MX_Gtwy_ControlInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c100_MX_Gtwy_Control(SimStruct *S)
{
  /* Actual parameters from chart:
     ACTIVE CD_EMEA_CONTROLS_FLASH_TIME CD_EMEA_CONTROLS_OPTION_A CD_EMEA_CONTROLS_REMINDER_TIME EE_LT_A2_A1 EE_LT_A2_A4 EE_LT_OF_A1 EE_LT_OF_A4 EE_LT_OF_NA EE_NA_NA EE_RT_A2_A1 EE_RT_A4_A1 EE_RT_A4_OF EE_RT_NA_OF ENGINE_CRANKING INACTIVE MODE_LEFT_AUX2 MODE_LEFT_AUX4 MODE_LEFT_NONE MODE_LEFT_OFFSET MODE_RIGHT_AUX1 MODE_RIGHT_AUX4 MODE_RIGHT_NONE MODE_RIGHT_OFFSET NON_FUNCTIONAL SYS_NORMAL
   */
  const char_T *rtParamNames[] = { "ACTIVE", "CD_EMEA_CONTROLS_FLASH_TIME",
    "CD_EMEA_CONTROLS_OPTION_A", "CD_EMEA_CONTROLS_REMINDER_TIME", "EE_LT_A2_A1",
    "EE_LT_A2_A4", "EE_LT_OF_A1", "EE_LT_OF_A4", "EE_LT_OF_NA", "EE_NA_NA",
    "EE_RT_A2_A1", "EE_RT_A4_A1", "EE_RT_A4_OF", "EE_RT_NA_OF",
    "ENGINE_CRANKING", "INACTIVE", "MODE_LEFT_AUX2", "MODE_LEFT_AUX4",
    "MODE_LEFT_NONE", "MODE_LEFT_OFFSET", "MODE_RIGHT_AUX1", "MODE_RIGHT_AUX4",
    "MODE_RIGHT_NONE", "MODE_RIGHT_OFFSET", "NON_FUNCTIONAL", "SYS_NORMAL" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for ACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_UINT8);

  /* registration for CD_EMEA_CONTROLS_FLASH_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_UINT16);

  /* registration for CD_EMEA_CONTROLS_OPTION_A*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_UINT8);

  /* registration for CD_EMEA_CONTROLS_REMINDER_TIME*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_UINT16);

  /* registration for EE_LT_A2_A1*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_UINT8);

  /* registration for EE_LT_A2_A4*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_UINT8);

  /* registration for EE_LT_OF_A1*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_UINT8);

  /* registration for EE_LT_OF_A4*/
  ssRegDlgParamAsRunTimeParam(S, 7, 7, rtParamNames[7], SS_UINT8);

  /* registration for EE_LT_OF_NA*/
  ssRegDlgParamAsRunTimeParam(S, 8, 8, rtParamNames[8], SS_UINT8);

  /* registration for EE_NA_NA*/
  ssRegDlgParamAsRunTimeParam(S, 9, 9, rtParamNames[9], SS_UINT8);

  /* registration for EE_RT_A2_A1*/
  ssRegDlgParamAsRunTimeParam(S, 10, 10, rtParamNames[10], SS_UINT8);

  /* registration for EE_RT_A4_A1*/
  ssRegDlgParamAsRunTimeParam(S, 11, 11, rtParamNames[11], SS_UINT8);

  /* registration for EE_RT_A4_OF*/
  ssRegDlgParamAsRunTimeParam(S, 12, 12, rtParamNames[12], SS_UINT8);

  /* registration for EE_RT_NA_OF*/
  ssRegDlgParamAsRunTimeParam(S, 13, 13, rtParamNames[13], SS_UINT8);

  /* registration for ENGINE_CRANKING*/
  ssRegDlgParamAsRunTimeParam(S, 14, 14, rtParamNames[14], SS_UINT8);

  /* registration for INACTIVE*/
  ssRegDlgParamAsRunTimeParam(S, 15, 15, rtParamNames[15], SS_UINT8);

  /* registration for MODE_LEFT_AUX2*/
  ssRegDlgParamAsRunTimeParam(S, 16, 16, rtParamNames[16], SS_UINT8);

  /* registration for MODE_LEFT_AUX4*/
  ssRegDlgParamAsRunTimeParam(S, 17, 17, rtParamNames[17], SS_UINT8);

  /* registration for MODE_LEFT_NONE*/
  ssRegDlgParamAsRunTimeParam(S, 18, 18, rtParamNames[18], SS_UINT8);

  /* registration for MODE_LEFT_OFFSET*/
  ssRegDlgParamAsRunTimeParam(S, 19, 19, rtParamNames[19], SS_UINT8);

  /* registration for MODE_RIGHT_AUX1*/
  ssRegDlgParamAsRunTimeParam(S, 20, 20, rtParamNames[20], SS_UINT8);

  /* registration for MODE_RIGHT_AUX4*/
  ssRegDlgParamAsRunTimeParam(S, 21, 21, rtParamNames[21], SS_UINT8);

  /* registration for MODE_RIGHT_NONE*/
  ssRegDlgParamAsRunTimeParam(S, 22, 22, rtParamNames[22], SS_UINT8);

  /* registration for MODE_RIGHT_OFFSET*/
  ssRegDlgParamAsRunTimeParam(S, 23, 23, rtParamNames[23], SS_UINT8);

  /* registration for NON_FUNCTIONAL*/
  ssRegDlgParamAsRunTimeParam(S, 24, 24, rtParamNames[24], SS_UINT8);

  /* registration for SYS_NORMAL*/
  ssRegDlgParamAsRunTimeParam(S, 25, 25, rtParamNames[25], SS_UINT8);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetInputPortDirectFeedThrough(S, 3, 1);
  ssSetInputPortDirectFeedThrough(S, 4, 1);
  ssSetInputPortDirectFeedThrough(S, 5, 1);
  ssSetInputPortDirectFeedThrough(S, 6, 1);
  ssSetInputPortDirectFeedThrough(S, 7, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_MX_Gtwy_Control_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      100);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,100,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 100);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,100);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,100,8);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,100,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 8; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,100);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3940938934U));
  ssSetChecksum1(S,(3787065830U));
  ssSetChecksum2(S,(1121548218U));
  ssSetChecksum3(S,(640433657U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c100_MX_Gtwy_Control(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c100_MX_Gtwy_Control(SimStruct *S)
{
  SFc100_MX_Gtwy_ControlInstanceStruct *chartInstance;
  chartInstance = (SFc100_MX_Gtwy_ControlInstanceStruct *)utMalloc(sizeof
    (SFc100_MX_Gtwy_ControlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc100_MX_Gtwy_ControlInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c100_MX_Gtwy_Control;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c100_MX_Gtwy_Control;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c100_MX_Gtwy_Control;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c100_MX_Gtwy_Control;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c100_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c100_MX_Gtwy_Control;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c100_MX_Gtwy_Control;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c100_MX_Gtwy_Control;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c100_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlStart = mdlStart_c100_MX_Gtwy_Control;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c100_MX_Gtwy_Control;
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
  mdl_start_c100_MX_Gtwy_Control(chartInstance);
}

void c100_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c100_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c100_MX_Gtwy_Control(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c100_MX_Gtwy_Control(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c100_MX_Gtwy_Control_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
