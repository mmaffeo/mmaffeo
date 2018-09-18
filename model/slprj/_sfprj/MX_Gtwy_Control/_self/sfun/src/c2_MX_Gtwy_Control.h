#ifndef __c2_MX_Gtwy_Control_h__
#define __c2_MX_Gtwy_Control_h__

/* Type Definitions */
#ifndef typedef_SFc2_MX_Gtwy_ControlInstanceStruct
#define typedef_SFc2_MX_Gtwy_ControlInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  uint8_T c2_tp_Normal;
  uint8_T c2_tp_NonFunctional;
  uint8_T c2_tp_On;
  uint8_T c2_tp_Off;
  uint8_T c2_tp_Deluxe_G55;
  uint8_T c2_b_tp_NonFunctional;
  uint8_T c2_b_tp_Normal;
  uint8_T c2_b_tp_Off;
  uint8_T c2_b_tp_On;
  uint8_T c2_tp_Error;
  uint8_T c2_is_active_c2_MX_Gtwy_Control;
  uint8_T c2_is_c2_MX_Gtwy_Control;
  uint8_T c2_is_Normal;
  uint8_T c2_is_Deluxe_G55;
  uint8_T c2_b_is_Normal;
  uint8_T c2_INACTIVE;
  uint8_T c2_ACTIVE;
  uint8_T c2_NORMAL;
  uint8_T c2_CD_AUTOIDLE_FUNCTION;
  uint8_T c2_NON_FUNCTIONAL;
  uint8_T c2_CD_DELUXE_GEN5_5_FUNCTION;
  uint8_T c2_IN_ERROR;
  uint8_T c2_doSetSimStateSideEffects;
  const mxArray *c2_setSimStateSideEffectsInfo;
  int8_T *c2_ee_AutoIdleEnabled_address;
  int32_T c2__indexoIdleEnabled;
  boolean_T c2_dsmdiag_ee_AutoIdleEnabled;
  void *c2_fEmlrtCtx;
  uint8_T *c2_state_AutoIdleEnable;
  uint8_T *c2_AutoIdle_RisingEdge;
  uint8_T *c2_state_LoadSense;
  boolean_T *c2_flag_InitEERead;
  uint8_T *c2_dlx_G55_AutoIdleEnable;
} SFc2_MX_Gtwy_ControlInstanceStruct;

#endif                                 /*typedef_SFc2_MX_Gtwy_ControlInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_MX_Gtwy_Control_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_MX_Gtwy_Control_get_check_sum(mxArray *plhs[]);
extern void c2_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
