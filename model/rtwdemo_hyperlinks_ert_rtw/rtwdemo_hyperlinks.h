/*
 * File: rtwdemo_hyperlinks.h
 *
 * Code generated for Simulink model 'rtwdemo_hyperlinks'.
 *
 * Model version                  : 1.318
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Tue Sep  4 09:17:50 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Specified
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rtwdemo_hyperlinks_h_
#define RTW_HEADER_rtwdemo_hyperlinks_h_
#include <math.h>
#ifndef rtwdemo_hyperlinks_COMMON_INCLUDES_
# define rtwdemo_hyperlinks_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* rtwdemo_hyperlinks_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  real_T y1;                           /* '<Root>/Chart' */
  real_T y2;                           /* '<Root>/Chart' */
  real_T y3;                           /* '<Root>/Chart' */
  real_T X;                            /* '<Root>/X' */
  real_T loc;                          /* '<Root>/Chart' */
  struct {
    uint_T is_c1_rtwdemo_hyperlinks:2; /* '<Root>/Chart' */
    uint_T is_S2:2;                    /* '<Root>/Chart' */
    uint_T is_active_c1_rtwdemo_hyperlinks:1;/* '<Root>/Chart' */
  } bitsForTID0;

  uint8_T temporalCounter_i1;          /* '<Root>/Chart' */
  uint8_T temporalCounter_i2;          /* '<Root>/Chart' */
} D_Work;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T Out1[2];                      /* '<Root>/Out1' */
} ExternalOutputs;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (auto storage) */
extern D_Work rtDWork;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs rtY;

/* Model entry point functions */
extern void rtwdemo_hyperlinks_initialize(void);
extern void rtwdemo_hyperlinks_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'rtwdemo_hyperlinks'
 * '<S1>'   : 'rtwdemo_hyperlinks/Chart'
 */
#endif                                 /* RTW_HEADER_rtwdemo_hyperlinks_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
