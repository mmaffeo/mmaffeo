/*
 * File: rtwdemo_hyperlinks.c
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

#include "rtwdemo_hyperlinks.h"

/* Named constants for Chart: '<Root>/Chart' */
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_S1                          ((uint8_T)1U)
#define IN_S2                          ((uint8_T)2U)
#define IN_S2a                         ((uint8_T)1U)
#define IN_S2b                         ((uint8_T)2U)

/* Block signals and states (auto storage) */
D_Work rtDWork;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern const real_T rtCP_pooled_k0vK8itlPrU4[5];

#define rtCP_Constant_Value            rtCP_pooled_k0vK8itlPrU4  /* Expression: [10;-20;30;-40;50]
                                                                  * Referenced by: '<Root>/Constant'
                                                                  */

/* Forward declaration for local functions */
static real_T stgfcn(real_T in1, const real_T in2[5]);
static real_T ttfcn(real_T u1t);
static real_T emfcn(real_T u1e, const real_T u2e[5]);
static real_T gfcn(real_T ug1, const real_T ug2[5]);

/* Function for Chart: '<Root>/Chart' */
static real_T stgfcn(real_T in1, const real_T in2[5])
{
  real_T out;
  if (in1 > in2[1]) {
    out = in1;
  } else {
    out = in2[1];
  }

  return out;
}

/* Function for Chart: '<Root>/Chart' */
static real_T ttfcn(real_T u1t)
{
  real_T yt;
  boolean_T aVarTruthTableCondition_1;
  boolean_T aVarTruthTableCondition_2;
  boolean_T aVarTruthTableCondition_3;
  aVarTruthTableCondition_1 = (u1t <= 0.0);
  aVarTruthTableCondition_2 = ((u1t > 0.0) && (u1t < 5.0));
  aVarTruthTableCondition_3 = ((u1t >= 5.0) && (u1t < 10.0));
  if (aVarTruthTableCondition_1 && (!aVarTruthTableCondition_2) &&
      (!aVarTruthTableCondition_3)) {
    yt = 10.0 * -u1t;
  } else if ((!aVarTruthTableCondition_1) && aVarTruthTableCondition_2 &&
             (!aVarTruthTableCondition_3)) {
    yt = (u1t + 5.0) * 10.0;
  } else if ((!aVarTruthTableCondition_1) && (!aVarTruthTableCondition_2) &&
             aVarTruthTableCondition_3) {
    yt = (u1t + 10.0) * 10.0;
  } else {
    /*  Default  */
    yt = 100.0;
  }

  return yt;
}

/* Function for Chart: '<Root>/Chart' */
static real_T emfcn(real_T u1e, const real_T u2e[5])
{
  real_T ye;
  real_T y;
  if (u1e > u2e[0]) {
    y = fabs(u2e[0] + u2e[1]);
    ye = y * y + u1e;
  } else {
    ye = fabs(u1e - u2e[1]);
  }

  return ye;
}

/* Function for Chart: '<Root>/Chart' */
static real_T gfcn(real_T ug1, const real_T ug2[5])
{
  return (((ug1 + ug2[0]) + ug1) + fabs(ug2[1])) * 10.0;
}

/* Model step function */
void rtwdemo_hyperlinks_step(void)
{
  /* Chart: '<Root>/Chart' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/INC'
   *  Sum: '<Root>/Sum'
   *  UnitDelay: '<Root>/X'
   */
  if (rtDWork.temporalCounter_i1 < 7U) {
    rtDWork.temporalCounter_i1++;
  }

  if (rtDWork.temporalCounter_i2 < 3U) {
    rtDWork.temporalCounter_i2++;
  }

  if (rtDWork.bitsForTID0.is_active_c1_rtwdemo_hyperlinks == 0U) {
    rtDWork.bitsForTID0.is_active_c1_rtwdemo_hyperlinks = 1U;
    rtDWork.bitsForTID0.is_c1_rtwdemo_hyperlinks = IN_S1;
    rtDWork.loc = 2.0;
    rtDWork.loc++;
  } else if (rtDWork.bitsForTID0.is_c1_rtwdemo_hyperlinks == IN_S1) {
    if (rtDWork.y1 > 50.0) {
      rtDWork.y3 = gfcn(2.0 + rtDWork.X, rtCP_Constant_Value);
      rtDWork.bitsForTID0.is_c1_rtwdemo_hyperlinks = IN_S2;
      rtDWork.temporalCounter_i2 = 0U;
      rtDWork.bitsForTID0.is_S2 = IN_S2a;
      rtDWork.temporalCounter_i1 = 0U;
    } else {
      rtDWork.y1 = ttfcn(rtDWork.loc);
      rtDWork.y2 = emfcn(2.0 + rtDWork.X, rtCP_Constant_Value);
    }
  } else if (rtDWork.temporalCounter_i2 >= 2) {
    rtDWork.y3 = 0.0;
    rtDWork.y1 = 0.0;
    rtDWork.bitsForTID0.is_S2 = IN_NO_ACTIVE_CHILD;
    rtDWork.bitsForTID0.is_c1_rtwdemo_hyperlinks = IN_S1;
    rtDWork.loc = 2.0;
    rtDWork.loc++;
  } else if (rtDWork.bitsForTID0.is_S2 == IN_S2a) {
    if (rtDWork.temporalCounter_i1 >= 3) {
      rtDWork.bitsForTID0.is_S2 = IN_S2b;
    } else {
      rtDWork.y1 = stgfcn(2.0 + rtDWork.X, rtCP_Constant_Value);
      rtDWork.y2++;
    }
  } else {
    rtDWork.y1 = 40.0;
  }

  /* End of Chart: '<Root>/Chart' */

  /* Outport: '<Root>/Out1' */
  rtY.Out1[0] = rtDWork.y1;
  rtY.Out1[1] = rtDWork.y2;

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/INC'
   *  Constant: '<Root>/RESET'
   *  Sum: '<Root>/Sum'
   *  UnitDelay: '<Root>/X'
   */
  if (rtDWork.y3 >= 0.5) {
    rtDWork.X += 2.0;
  } else {
    rtDWork.X = 0.0;
  }

  /* End of Switch: '<Root>/Switch' */
}

/* Model initialize function */
void rtwdemo_hyperlinks_initialize(void)
{
  /* SystemInitialize for Chart: '<Root>/Chart' */
  rtDWork.loc = -2.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
