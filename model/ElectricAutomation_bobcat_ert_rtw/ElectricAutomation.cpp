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
//  Simulink model                       : ElectricAutomation


#include "ElectricAutomation.h"
#include "ElectricAutomation_private.h"

// Exported block signals
uint16_T Out2;                         // '<S1>/Data Type Conversion'
uint8_T cmdInverter;                   // '<S1>/Chart'
boolean_T Out1;                        // '<S1>/Data Type Conversion1'

// Block states (auto storage)
D_Work_ElectricAutomation ElectricAutomation_DWork;

// External inputs (root inport signals with auto storage)
ExternalInputs_ElectricAutomati ElectricAutomation_U;

// External outputs (root outports fed by signals with auto storage)
ExternalOutputs_ElectricAutomat ElectricAutomation_Y;

// Real-time model
RT_MODEL_ElectricAutomation ElectricAutomation_M_;
RT_MODEL_ElectricAutomation *const ElectricAutomation_M = &ElectricAutomation_M_;
static void rate_scheduler(void);

//
//    This function updates active task flag for each subrate.
//  The function is called at model base rate, hence the
//  generated code self-manages all its subrates.

static void rate_scheduler(void)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (ElectricAutomation_M->Timing.TaskCounters.TID[1])++;
  if ((ElectricAutomation_M->Timing.TaskCounters.TID[1]) > 9) {// Sample time: [0.1s, 0.0s] 
    ElectricAutomation_M->Timing.TaskCounters.TID[1] = 0;
  }
}

// Model step function
void ElectricAutomation_step(void)
{
  if (ElectricAutomation_M->Timing.TaskCounters.TID[1] == 0) {
    // Outputs for Atomic SubSystem: '<Root>/ElectricAutomation'
    ElectricAuto_ElectricAutomation();

    // End of Outputs for SubSystem: '<Root>/ElectricAutomation'

    // BusCreator: '<Root>/BusConversion_InsertedFor_Out1_at_inport_0' incorporates:
    //   Outport: '<Root>/Out1'

    ElectricAutomation_Y.Out1_jdzy.Out1 = Out1;
    ElectricAutomation_Y.Out1_jdzy.Out2 = Out2;
  }

  rate_scheduler();
}

// Model initialize function
void ElectricAutomation_initialize(void)
{
  // Registration code

  // initialize real-time model
  (void) memset((void *)ElectricAutomation_M, 0,
                sizeof(RT_MODEL_ElectricAutomation));

  // block I/O

  // exported global signals
  Out2 = 0U;
  cmdInverter = 0U;
  Out1 = false;

  // states (dwork)
  (void) memset((void *)&ElectricAutomation_DWork, 0,
                sizeof(D_Work_ElectricAutomation));

  // external inputs
  (void)memset((void *)&ElectricAutomation_U, 0, sizeof
               (ExternalInputs_ElectricAutomati));

  // external outputs
  (void) memset((void *)&ElectricAutomation_Y, 0,
                sizeof(ExternalOutputs_ElectricAutomat));

  // SystemInitialize for Atomic SubSystem: '<Root>/ElectricAutomation'
  Electri_ElectricAutomation_Init();

  // End of SystemInitialize for SubSystem: '<Root>/ElectricAutomation'
}

//
//  [EOF]
