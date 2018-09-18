#ifndef __c83_MX_Gateway_h__
#define __c83_MX_Gateway_h__

/* Type Definitions */
#ifndef typedef_SFc83_MX_GatewayInstanceStruct
#define typedef_SFc83_MX_GatewayInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c83_sfEvent;
  uint8_T c83_tp_Normal;
  uint8_T c83_tp_On;
  uint8_T c83_tp_Init;
  uint8_T c83_tp_Off;
  uint8_T c83_tp_Deluxe_G55;
  uint8_T c83_b_tp_Off;
  uint8_T c83_b_tp_On;
  uint8_T c83_is_active_c83_MX_Gateway;
  uint8_T c83_is_c83_MX_Gateway;
  uint8_T c83_is_Normal;
  uint8_T c83_is_Deluxe_G55;
  uint8_T c83_INACTIVE;
  uint8_T c83_ACTIVE;
  uint8_T c83_CD_DELUXE_GEN5_5_FUNCTION;
  uint8_T c83_NON_FUNCTIONAL;
  uint8_T c83_doSetSimStateSideEffects;
  const mxArray *c83_setSimStateSideEffectsInfo;
  uint8_T *c83_ee_DeluxeG5_address;
  int32_T c83__indexuxeG5;
  boolean_T c83_dsmdiag_ee_DeluxeG5;
  uint8_T *c83__indexee_EcoMode_address;
  int32_T c83__indexMode;
  boolean_T c83_dsmdiag_ee_EcoMode;
  void *c83_fEmlrtCtx;
  uint8_T *c83_state_EcoMode;
  boolean_T *c83_button_EcoMode;
  boolean_T *c83_flag_InitEERead;
  uint8_T *c83_dlx_G55_EcoMode;
} SFc83_MX_GatewayInstanceStruct;

#endif                                 /*typedef_SFc83_MX_GatewayInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c83_MX_Gateway_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c83_MX_Gateway_get_check_sum(mxArray *plhs[]);
extern void c83_MX_Gateway_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
