#ifndef __c63_MX_Gtwy_Control_h__
#define __c63_MX_Gtwy_Control_h__

/* Type Definitions */
#ifndef typedef_SFc63_MX_Gtwy_ControlInstanceStruct
#define typedef_SFc63_MX_Gtwy_ControlInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c63_sfEvent;
  uint8_T c63_tp_ECU;
  uint8_T c63_tp_DERATE_LEVEL;
  uint8_T c63_tp_SEND_MSG;
  uint8_T c63_tp_NON_FUNCTIONAL;
  uint8_T c63_tp_NORMAL;
  uint8_T c63_tp_DERATE;
  uint8_T c63_tp_DISABLE_DERATE;
  uint8_T c63_tp_RPM_FAULT;
  uint8_T c63_tp_UNRESPONSIVE;
  uint8_T c63_b_tp_UNRESPONSIVE;
  uint8_T c63_tp_DEBOUNCE;
  uint8_T c63_b_tp_NORMAL;
  uint8_T c63_tp_SHUTDOWN;
  uint8_T c63_b_tp_SHUTDOWN;
  uint8_T c63_b_tp_DEBOUNCE;
  uint8_T c63_tp_HP_MATCH;
  uint8_T c63_b_tp_NON_FUNCTIONAL;
  uint8_T c63_tp_SEND_REQUEST;
  uint8_T c63_tp_SEND_MESSAGE;
  uint8_T c63_tp_WAIT_FOR_RESPONSE;
  uint8_T c63_tp_REQUEST_RECEIVED;
  uint8_T c63_tp_Cranking;
  uint8_T c63_b_tp_DERATE;
  uint8_T c63_tp_NO_ECU;
  uint8_T c63_is_active_c63_MX_Gtwy_Control;
  uint8_T c63_is_c63_MX_Gtwy_Control;
  uint8_T c63_is_active_DERATE_LEVEL;
  uint8_T c63_is_SEND_MSG;
  uint8_T c63_is_active_SEND_MSG;
  uint8_T c63_is_RPM_FAULT;
  uint8_T c63_is_active_RPM_FAULT;
  uint8_T c63_is_UNRESPONSIVE;
  uint8_T c63_is_SHUTDOWN;
  uint8_T c63_is_HP_MATCH;
  uint8_T c63_is_active_HP_MATCH;
  uint8_T c63_is_SEND_REQUEST;
  uint8_T c63_NON_FUNCTIONAL;
  uint8_T c63_CD_ECU_FUNCTION;
  uint16_T c63_debounceCount;
  uint8_T c63_SHUTDOWN;
  uint8_T c63_NORMAL;
  uint16_T c63_CD_DERATE_ENGINE_SPEED_HIGH_OFFSET;
  uint16_T c63_CD_DERATE_ENGINE_SPEED_DEBOUNCE_HIGH;
  uint16_T c63_CD_DERATE_ENGINE_SPEED_DEBOUNCE_SHUTDOWN;
  uint8_T c63_UNRESPONSIVE;
  uint8_T c63_CD_HP_MATCH_FUNCTION;
  uint8_T c63_derate_HPMatch;
  uint8_T c63_num_Trys;
  uint16_T c63_debounceRequest;
  uint8_T c63_UNDEFINED;
  uint8_T c63_CD_MACHINE_HP;
  uint8_T c63_ACTIVE;
  uint8_T c63_CD_MATCH_DERATE_PERCENT;
  uint8_T c63_FAILURE;
  uint8_T c63_ENGINE_CRANKING;
  uint8_T c63_CD_DERATE_METHOD;
  uint8_T c63_doSetSimStateSideEffects;
  const mxArray *c63_setSimStateSideEffectsInfo;
  void *c63_fEmlrtCtx;
  int8_T *c63_percent_Derate;
  uint16_T *c63_rpm_Derate;
  uint8_T *c63_state_EngineSpeedDerate;
  uint16_T *c63_flt_EngineSpeed;
  uint16_T *c63_torque_Indicated;
  uint16_T *c63_ecu_isocMinRPM;
  uint16_T *c63_ecu_isocMaxRPM;
  uint8_T *c63_derate_Throttle;
  uint8_T *c63_state_HPMatch;
  uint8_T *c63_state_CommECU;
  uint8_T *c63_state_ECUHold;
  uint8_T *c63_ecu_HP;
  uint8_T *c63_state_Engine;
  uint16_T *c63_torque_Derate;
} SFc63_MX_Gtwy_ControlInstanceStruct;

#endif                                 /*typedef_SFc63_MX_Gtwy_ControlInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c63_MX_Gtwy_Control_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c63_MX_Gtwy_Control_get_check_sum(mxArray *plhs[]);
extern void c63_MX_Gtwy_Control_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
