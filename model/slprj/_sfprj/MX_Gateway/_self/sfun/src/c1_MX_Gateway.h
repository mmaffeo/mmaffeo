#ifndef __c1_MX_Gateway_h__
#define __c1_MX_Gateway_h__

/* Type Definitions */
#ifndef typedef_SFc1_MX_GatewayInstanceStruct
#define typedef_SFc1_MX_GatewayInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  uint8_T c1_tp_NORMAL;
  uint8_T c1_tp_CRANKING;
  uint8_T c1_tp_FACTORY_TURBO_PRIMER;
  uint8_T c1_tp_PREVENT_FUEL_MSG_ACTIVE;
  uint8_T c1_tp_CHECK_HOUR_METER;
  uint8_T c1_tp_HOUR_METER_EXCEEDED;
  uint8_T c1_tp_PREVENT_FUEL_MSG_INACTIVE;
  uint8_T c1_tp_PAUSE;
  uint8_T c1_tp_NOT_RUNNING;
  uint8_T c1_b_tp_NOT_RUNNING;
  uint8_T c1_tp_WAIT_TO_START;
  uint8_T c1_tp_RUNNING;
  uint8_T c1_tp_ST_SHUTDOWN;
  uint8_T c1_tp_SHUTDOWN;
  uint8_T c1_is_active_c1_MX_Gateway;
  uint8_T c1_is_c1_MX_Gateway;
  uint8_T c1_is_NORMAL;
  uint8_T c1_is_CRANKING;
  uint8_T c1_is_FACTORY_TURBO_PRIMER;
  uint8_T c1_is_NOT_RUNNING;
  uint16_T c1_CD_ENGINE_SPEED_RUNNING;
  uint16_T c1_CD_ENGINE_SPEED_NOT_RUNNING;
  uint8_T c1_ACTIVE;
  uint8_T c1_ENGINE_CRANKING;
  uint8_T c1_ENGINE_NOT_RUNNING;
  uint8_T c1_ENGINE_RUNNING;
  uint8_T c1_INACTIVE;
  uint8_T c1_SHUTDOWN;
  uint8_T c1_SYS_NORMAL;
  uint8_T c1_NO_COMMUNICATION;
  uint8_T c1_CD_PANEL_SHUTDOWN_FUNCTION;
  uint8_T c1_NON_FUNCTIONAL;
  uint8_T c1_MULTIPLE;
  uint8_T c1_ENGINE_OFF;
  uint8_T c1_NORMAL;
  uint8_T c1_CD_ECU_FUNCTION;
  uint8_T c1_ENGINE_INITIALIZE;
  uint16_T c1_CD_ECU_DEBOUNCE_WAIT_TO_START;
  uint16_T c1_debounceCount;
  uint8_T c1_STARTER_INHIBITED;
  uint16_T c1_panelMissingDebounce;
  uint16_T c1_CD_PANEL_SHUTDOWN_DEBOUNCE;
  uint8_T c1_CD_EMEA_CONSOLE_CRANK_INHIBIT;
  uint8_T c1_CD_FACTORY_TURBO_PRIME_FUNCTION;
  uint32_T c1_CD_FACTORY_TURBO_PRIME_HOUR_ENABLE;
  uint8_T c1_TURBO_PRIME_ACTIVE;
  uint16_T c1_debouncePrimer;
  uint16_T c1_CD_FACTORY_TURBO_PRIME_DEBOUNCE_DISABLE_FUEL;
  uint16_T c1_CD_FACTORY_TURBO_PRIME_DEBOUNCE_WAIT;
  boolean_T c1_flag_PrimeComplete;
  uint8_T c1_doSetSimStateSideEffects;
  const mxArray *c1_setSimStateSideEffectsInfo;
  void *c1_fEmlrtCtx;
  uint8_T *c1_state_Engine;
  uint16_T *c1_flt_EngineSpeed;
  uint8_T *c1_state_EngineSpeed;
  uint8_T *c1_state_ECT;
  uint8_T *c1_state_EOP;
  uint8_T *c1_state_HOT;
  uint8_T *c1_state_EngineStart;
  uint8_T *c1_state_Key;
  uint8_T *c1_state_System;
  uint8_T *c1_din_RemoteKey;
  uint8_T *c1_state_KeylessPanel;
  uint8_T *c1_state_CommECU;
  uint8_T *c1_can_ST_EStop;
  uint8_T *c1_can_ACD_EStop;
  uint8_T *c1_ecu_EngineStarterMode;
  uint8_T *c1_state_EngineSpeedDerate;
  uint8_T *c1_state_FuelTemp;
  uint8_T *c1_state_CommStdPanel;
  uint8_T *c1_state_DeluxeG5;
  uint8_T *c1_state_CommDeluxeG55;
  uint8_T *c1_state_Console;
  uint32_T *c1_actualHourMeter;
  uint8_T *c1_dv_TurboPrime;
  uint8_T *c1_state_TurboPrime;
} SFc1_MX_GatewayInstanceStruct;

#endif                                 /*typedef_SFc1_MX_GatewayInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_MX_Gateway_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_MX_Gateway_get_check_sum(mxArray *plhs[]);
extern void c1_MX_Gateway_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
