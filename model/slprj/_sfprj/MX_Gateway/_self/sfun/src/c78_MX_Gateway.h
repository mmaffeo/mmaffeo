#ifndef __c78_MX_Gateway_h__
#define __c78_MX_Gateway_h__

/* Type Definitions */
#ifndef typedef_SFc78_MX_GatewayInstanceStruct
#define typedef_SFc78_MX_GatewayInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c78_sfEvent;
  uint8_T c78_tp_Get_Cal_Values;
  uint8_T c78_tp_Init_Cal;
  uint8_T c78_tp_Init_Complete;
  uint8_T c78_tp_Wait;
  uint8_T c78_tp_Monitor;
  uint8_T c78_tp_Normal;
  uint8_T c78_tp_Debounce;
  uint8_T c78_tp_Fault;
  uint8_T c78_tp_Cal_Start;
  uint8_T c78_tp_Cal_Check;
  uint8_T c78_tp_Pos_Low;
  uint8_T c78_tp_Pos_High;
  uint8_T c78_tp_Cal_Inhibit;
  uint8_T c78_tp_Cal_In_Progress;
  uint8_T c78_tp_Control;
  uint8_T c78_tp_Normal_Mode;
  uint8_T c78_tp_Cal_Mode;
  uint8_T c78_tp_Cal_Fail;
  uint8_T c78_tp_INITIALIZE;
  uint8_T c78_tp_EXTEND_ACTUATOR;
  uint8_T c78_tp_RECORD_MAX;
  uint8_T c78_tp_RETRACT_ACTUATOR;
  uint8_T c78_tp_RECORD_MIN;
  uint8_T c78_tp_VALIDATE_POLARITY;
  uint8_T c78_tp_VALIDATE_RANGE;
  uint8_T c78_tp_Done;
  uint8_T c78_is_active_c78_MX_Gateway;
  uint8_T c78_is_Get_Cal_Values;
  uint8_T c78_is_active_Get_Cal_Values;
  uint8_T c78_is_Init_Cal;
  uint8_T c78_is_Monitor;
  uint8_T c78_is_active_Monitor;
  uint8_T c78_is_Cal_Start;
  uint8_T c78_is_active_Cal_Start;
  uint8_T c78_is_Cal_Check;
  uint8_T c78_is_Control;
  uint8_T c78_is_active_Control;
  uint8_T c78_is_Cal_Mode;
  uint16_T c78_CD_CAN_THROTTLE_CAL_DEADBAND;
  uint16_T c78_CD_CAN_THROTTLE_CAL_EXTENDED_DEFAULT;
  uint16_T c78_CD_CAN_THROTTLE_CAL_RETRACTED_DEFAULT;
  uint16_T c78_CD_CAN_THROTTLE_CAL_DIAG_TIME;
  uint16_T c78_CD_CAN_THROTTLE_CAL_MAX;
  uint16_T c78_CD_CAN_THROTTLE_CAL_MIN;
  uint16_T c78_CD_CAN_THROTTLE_CAL_RANGE_NOM;
  uint16_T c78_CD_CAN_THROTTLE_CAL_RANGE_TOL;
  uint16_T c78_CD_CAN_THROTTLE_DEBOUNCE_FAILURE;
  uint16_T c78_CD_CAN_THROTTLE_ERROR_MAX;
  uint8_T c78_DOUBLE_SHORT_BEEP;
  uint8_T c78_ENGINE_CRANKING;
  uint8_T c78_ENGINE_RUNNING;
  uint8_T c78_FAILURE;
  uint8_T c78_IN_CAL_MODE;
  uint8_T c78_NORMAL;
  uint8_T c78_NOT_CALIBRATED;
  uint8_T c78_count;
  uint8_T c78_previous_cal_state;
  uint16_T c78_range;
  uint16_T c78_temporalCounter_i1;
  uint16_T c78_temporalCounter_i2;
  uint8_T c78_temporalCounter_i3;
  uint8_T c78_doSetSimStateSideEffects;
  const mxArray *c78_setSimStateSideEffectsInfo;
  uint16_T *c78_ee_ThrottleCalExtended_address;
  int32_T c78__indexottleCalExtended;
  boolean_T c78_dsmdiag_ee_ThrottleCalExtended;
  uint16_T *c78__indexee_ThrottleCalRetracted_address;
  int32_T c78__indexottleCalRetracted;
  boolean_T c78_dsmdiag_ee_ThrottleCalRetracted;
  uint8_T *c78__indexee_ThrottleCalState_address;
  int32_T c78__indexottleCalState;
  boolean_T c78_dsmdiag_ee_ThrottleCalState;
  uint8_T *c78__indexstate_Buzzer_address;
  int32_T c78__indexBuzzer;
  boolean_T c78_dsmdiag_state_Buzzer;
  void *c78_fEmlrtCtx;
  uint16_T *c78_pos_Error;
  uint16_T *c78_cmd_CANThrottle;
  uint16_T *c78_fdbk_CANThrottle;
  boolean_T *c78_flag_InitEERead;
  uint8_T *c78_state_CANThrottle;
  uint8_T *c78_state_Engine;
  uint8_T *c78_state_CANThrottleCalDiag;
  uint8_T *c78_state_CommThrottle;
  uint16_T *c78_pos_Throttle;
  uint16_T *c78_scaled_ThrottlePos;
} SFc78_MX_GatewayInstanceStruct;

#endif                                 /*typedef_SFc78_MX_GatewayInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c78_MX_Gateway_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c78_MX_Gateway_get_check_sum(mxArray *plhs[]);
extern void c78_MX_Gateway_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
