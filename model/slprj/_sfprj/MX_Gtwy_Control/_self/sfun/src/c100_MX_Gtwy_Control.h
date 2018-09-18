#ifndef __c100_MX_Gtwy_Control_h__
#define __c100_MX_Gtwy_Control_h__

/* Type Definitions */
#ifndef typedef_SFc100_MX_Gtwy_ControlInstanceStruct
#define typedef_SFc100_MX_Gtwy_ControlInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c100_sfEvent;
  uint8_T c100_tp_Normal;
  uint8_T c100_tp_Init;
  uint8_T c100_tp_OffsetCheck;
  uint8_T c100_tp_ReminderOfLastState;
  uint8_T c100_tp_Flasher;
  uint8_T c100_tp_OF_A1FLASH;
  uint8_T c100_tp_GLOW_OFF;
  uint8_T c100_tp_ON;
  uint8_T c100_tp_OFF;
  uint8_T c100_tp_OF_A4FLASH;
  uint8_T c100_b_tp_GLOW_OFF;
  uint8_T c100_b_tp_ON;
  uint8_T c100_b_tp_OFF;
  uint8_T c100_tp_A2FLASH_A1FLASH;
  uint8_T c100_c_tp_GLOW_OFF;
  uint8_T c100_c_tp_ON;
  uint8_T c100_c_tp_OFF;
  uint8_T c100_tp_A2FLASH_A4FLASH;
  uint8_T c100_d_tp_GLOW_OFF;
  uint8_T c100_d_tp_ON;
  uint8_T c100_d_tp_OFF;
  uint8_T c100_tp_A4FLASH_OF;
  uint8_T c100_e_tp_GLOW_OFF;
  uint8_T c100_e_tp_ON;
  uint8_T c100_tp_ON1;
  uint8_T c100_tp_A4FLASH_A1FLASH;
  uint8_T c100_f_tp_GLOW_OFF;
  uint8_T c100_f_tp_ON;
  uint8_T c100_e_tp_OFF;
  uint8_T c100_tp_Default;
  uint8_T c100_tp_FlashTimer;
  uint8_T c100_tp_No_Glow;
  uint8_T c100_tp_GlowCycle1;
  uint8_T c100_tp_GlowOff;
  uint8_T c100_tp_GlowCycle2;
  uint8_T c100_tp_GlowOff1;
  uint8_T c100_tp_Expired;
  uint8_T c100_is_active_c100_MX_Gtwy_Control;
  uint8_T c100_is_c100_MX_Gtwy_Control;
  uint8_T c100_is_Flasher;
  uint8_T c100_is_active_Flasher;
  uint8_T c100_is_OF_A1FLASH;
  uint8_T c100_is_OF_A4FLASH;
  uint8_T c100_is_A2FLASH_A1FLASH;
  uint8_T c100_is_A2FLASH_A4FLASH;
  uint8_T c100_is_A4FLASH_OF;
  uint8_T c100_is_A4FLASH_A1FLASH;
  uint8_T c100_is_FlashTimer;
  uint8_T c100_is_active_FlashTimer;
  uint16_T c100_CD_EMEA_CONTROLS_FLASH_TIME;
  uint16_T c100_CD_EMEA_CONTROLS_REMINDER_TIME;
  uint8_T c100_EE_LT_OF_NA;
  uint8_T c100_EE_NA_NA;
  uint8_T c100_EE_RT_NA_OF;
  uint8_T c100_INACTIVE;
  uint8_T c100_MODE_LEFT_AUX2;
  uint8_T c100_MODE_LEFT_AUX4;
  uint8_T c100_MODE_LEFT_NONE;
  uint8_T c100_MODE_LEFT_OFFSET;
  uint8_T c100_MODE_RIGHT_AUX1;
  uint8_T c100_MODE_RIGHT_AUX4;
  uint8_T c100_MODE_RIGHT_NONE;
  uint8_T c100_MODE_RIGHT_OFFSET;
  uint8_T c100_EE_LT_A2_A1;
  uint8_T c100_EE_LT_A2_A4;
  uint8_T c100_EE_LT_OF_A1;
  uint8_T c100_EE_LT_OF_A4;
  uint8_T c100_EE_RT_A2_A1;
  uint8_T c100_EE_RT_A4_A1;
  uint8_T c100_EE_RT_A4_OF;
  uint16_T c100_flash_timer;
  uint8_T c100_CD_EMEA_CONTROLS_OPTION_A;
  uint8_T c100_NON_FUNCTIONAL;
  uint8_T c100_ACTIVE;
  uint8_T c100_ENGINE_CRANKING;
  uint8_T c100_SYS_NORMAL;
  uint16_T c100_temporalCounter_i1;
  uint8_T c100_doSetSimStateSideEffects;
  const mxArray *c100_setSimStateSideEffectsInfo;
  uint8_T *c100_ee_ControlMode_address;
  int32_T c100__indextrolMode;
  boolean_T c100_dsmdiag_ee_ControlMode;
  void *c100_fEmlrtCtx;
  uint8_T *c100_disp_LeftControl;
  uint8_T *c100_disp_RightControl;
  uint8_T *c100_mode_LeftControl;
  uint8_T *c100_mode_RightControl;
  uint8_T *c100_state_AuxEnable;
  boolean_T *c100_flag_AuxEnableFlash;
  boolean_T *c100_flag_InitEERead;
  boolean_T *c100_dout_GlowPlugs;
  uint8_T *c100_state_Console;
  uint8_T *c100_state_Engine;
  uint8_T *c100_state_System;
} SFc100_MX_Gtwy_ControlInstanceStruct;

#endif                                 /*typedef_SFc100_MX_Gtwy_ControlInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c100_MX_Gtwy_Control_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c100_MX_Gtwy_Control_get_check_sum(mxArray *plhs[]);
extern void c100_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
