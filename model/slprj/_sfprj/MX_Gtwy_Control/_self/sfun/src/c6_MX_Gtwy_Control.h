#ifndef __c6_MX_Gtwy_Control_h__
#define __c6_MX_Gtwy_Control_h__

/* Type Definitions */
#ifndef typedef_SFc6_MX_Gtwy_ControlInstanceStruct
#define typedef_SFc6_MX_Gtwy_ControlInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c6_sfEvent;
  uint8_T c6_tp_NON_FUNCTIONAL;
  uint8_T c6_tp_STATE;
  uint8_T c6_tp_NORMAL;
  uint8_T c6_tp_ABSENT;
  uint8_T c6_tp_DEBOUNCE_ABSENT;
  uint8_T c6_b_tp_ABSENT;
  uint8_T c6_tp_PRESENT;
  uint8_T c6_tp_DEBOUNCE_PRESENT;
  uint8_T c6_b_tp_PRESENT;
  uint8_T c6_tp_OORH;
  uint8_T c6_tp_DEBOUNCE;
  uint8_T c6_b_tp_OORH;
  uint8_T c6_tp_OORL;
  uint8_T c6_b_tp_DEBOUNCE;
  uint8_T c6_b_tp_OORL;
  uint8_T c6_is_active_c6_MX_Gtwy_Control;
  uint8_T c6_is_c6_MX_Gtwy_Control;
  uint8_T c6_is_STATE;
  uint8_T c6_is_NORMAL;
  uint8_T c6_is_ABSENT;
  uint8_T c6_is_PRESENT;
  uint8_T c6_is_OORH;
  uint8_T c6_is_OORL;
  uint16_T c6_CD_CONSOLE_PRESENT_LOW;
  uint16_T c6_CD_CONSOLE_PRESENT_HIGH;
  uint8_T c6_CD_CONSOLE_FUNCTION;
  uint16_T c6_CD_CONSOLE_DEBOUNCE_PRESENT;
  uint16_T c6_CD_CONSOLE_DEBOUNCE_ABSENT;
  uint16_T c6_debounceCount;
  uint16_T c6_CD_CONSOLE_OORH;
  uint16_T c6_CD_CONSOLE_DEBOUNCE_OORH;
  uint16_T c6_CD_CONSOLE_OORL;
  uint16_T c6_CD_CONSOLE_DEBOUNCE_OORL;
  uint8_T c6_ACTIVE;
  uint8_T c6_INACTIVE;
  uint8_T c6_OORH;
  uint8_T c6_OORL;
  uint8_T c6_NON_FUNCTIONAL;
  uint8_T c6_NORMAL;
  uint8_T c6_SYS_NORMAL;
  uint8_T c6_doSetSimStateSideEffects;
  const mxArray *c6_setSimStateSideEffectsInfo;
  void *c6_fEmlrtCtx;
  uint8_T *c6_state_Console;
  uint16_T *c6_rm_Console;
  uint16_T *c6_ain_Console;
  uint8_T *c6_state_SensorSupply1;
  uint8_T *c6_state_SensorSupply2;
  uint8_T *c6_state_System;
  uint8_T *c6_state_MachineLock;
  boolean_T *c6_flag_InitEERead;
} SFc6_MX_Gtwy_ControlInstanceStruct;

#endif                                 /*typedef_SFc6_MX_Gtwy_ControlInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c6_MX_Gtwy_Control_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c6_MX_Gtwy_Control_get_check_sum(mxArray *plhs[]);
extern void c6_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
