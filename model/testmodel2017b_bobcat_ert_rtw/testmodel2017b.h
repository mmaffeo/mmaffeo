//
//  Copyright (c) 2009 Bobcat Company as an unpublished work.
//  All Rights Reserved.
//
//  The information contained herein is confidential property of Bobcat Company.
//  The use, copying, transfer or disclosure of such information is prohibited except
//  by express written agreement with Bobcat Company.
//
//  Code Generated by Simulink Real-Time Workshop
//
//  Simulink model                       : testmodel2017b


#ifndef RTW_HEADER_testmodel2017b_h_
#define RTW_HEADER_testmodel2017b_h_
#include <math.h>
#include <string.h>
#ifndef testmodel2017b_COMMON_INCLUDES_
# define testmodel2017b_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 // testmodel2017b_COMMON_INCLUDES_

#include "testmodel2017b_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

// user code (top of header file)
#include "cdata.h"
#include "ap_can.h"
#include "SendMsgNow.h"
#include "ap_eeprom.h"
#include "ap_bservice_CAN04.h"

// Block signals (auto storage)
typedef struct {
  real_T FromWs[5];                    // '<S3>/FromWs'
} BlockIO_testmodel2017b_T;

// Block states (auto storage) for system '<Root>'
typedef struct {
  struct {
    void *TimePtr;
    void *DataPtr;
    void *RSimInfoPtr;
  } FromWs_PWORK;                      // '<S3>/FromWs'

  struct {
    int_T PrevIndex;
  } FromWs_IWORK;                      // '<S3>/FromWs'

  struct {
    uint_T is_c4_testmodel2017b:3;     // '<S1>/State Transition Table'
    uint_T is_c3_testmodel2017b:3;     // '<S1>/Chart'
    uint_T is_active_c4_testmodel2017b:1;// '<S1>/State Transition Table'
    uint_T is_active_c3_testmodel2017b:1;// '<S1>/Chart'
  } bitsForTID1;
} D_Work_testmodel2017b_T;

// Real-time Model Data Structure
struct tag_RTM_testmodel2017b_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

// Block signals (auto storage)
extern BlockIO_testmodel2017b_T testmodel2017b_B;

// Block states (auto storage)
extern D_Work_testmodel2017b_T testmodel2017b_DWork;

//
//  Exported Global Signals
//
//  Note: Exported global signals are block signals with an exported global
//  storage class designation.  Code generation will declare the memory for
//  these signals and export their symbols.
//

extern real_T cmdInverter;             // '<S1>/Chart'

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void testmodel2017b_initialize(void);
  extern void testmodel2017b_step(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_testmodel2017b_T *const testmodel2017b_M;

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S1>/Add' : Unused code path elimination
//  Block '<S1>/Bitwise Operator' : Unused code path elimination
//  Block '<S1>/Bitwise Operator1' : Unused code path elimination
//  Block '<S1>/Bitwise Operator2' : Unused code path elimination
//  Block '<S1>/Bitwise Operator3' : Unused code path elimination
//  Block '<S1>/Bitwise Operator4' : Unused code path elimination
//  Block '<S1>/Bitwise Operator5' : Unused code path elimination
//  Block '<S1>/Bitwise Operator6' : Unused code path elimination
//  Block '<S1>/Bitwise Operator7' : Unused code path elimination
//  Block '<S1>/Constant1' : Unused code path elimination
//  Block '<S1>/Constant2' : Unused code path elimination
//  Block '<S1>/Constant3' : Unused code path elimination
//  Block '<S1>/Constant4' : Unused code path elimination
//  Block '<S1>/Constant5' : Unused code path elimination
//  Block '<S1>/Constant6' : Unused code path elimination
//  Block '<S1>/Constant7' : Unused code path elimination
//  Block '<S1>/Constant8' : Unused code path elimination
//  Block '<S1>/Data Type Conversion' : Unused code path elimination
//  Block '<S1>/Data Type Conversion1' : Unused code path elimination
//  Block '<S1>/Logical Operator' : Unused code path elimination
//  Block '<S1>/Logical Operator1' : Unused code path elimination
//  Block '<S1>/Logical Operator2' : Unused code path elimination
//  Block '<S1>/Logical Operator3' : Unused code path elimination
//  Block '<S1>/Logical Operator4' : Unused code path elimination
//  Block '<S1>/Logical Operator5' : Unused code path elimination
//  Block '<S1>/Logical Operator6' : Unused code path elimination
//  Block '<S1>/Logical Operator7' : Unused code path elimination
//  Block '<S1>/Scope' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'testmodel2017b'
//  '<S1>'   : 'testmodel2017b/Subsystem'
//  '<S2>'   : 'testmodel2017b/Subsystem/Chart'
//  '<S3>'   : 'testmodel2017b/Subsystem/Signal Builder'
//  '<S4>'   : 'testmodel2017b/Subsystem/State Transition Table'
//  '<S5>'   : 'testmodel2017b/Subsystem/Truth Table'


//-
//  Requirements for '<Root>': testmodel2017b

#endif                                 // RTW_HEADER_testmodel2017b_h_

//
//  [EOF]

