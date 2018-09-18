//******************************************************************************
/**
 * \file    siar_tf4_cstartup.c
 * \author  Chad Swenson
 * \date    May 2013
 * \brief   IAR specific STM32F4xx cstartup functions
 *
 * Copyright 2013 Bobcat Company as an unpublished work.
 * All Rights Reserved.
 *
 * The information contained herein is confidential
 * property of Bobcat Company. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Bobcat Company.
 *
 *******************************************************************************/
#include <stdint.h>

#define STF4_INTERNAL (1)
#include "stf4_cstartup.h"
#undef STF4_INTERNAL

#include "system_stm32f4xx.h"


//******************************************************************************
// Definitions
//******************************************************************************
typedef void (* vectorEntry_t)(void);

//******************************************************************************
// IAR Library Function Prototypes
//******************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

void __iar_program_start(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void cstartup(void);
static void default_isr(void);

//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void * cstartup_getRamVec(uint32_t *size)
{
#pragma section="RAMVEC"

  if (size)
  {
     *size = __section_size("RAMVEC");
  }

  return __section_begin("RAMVEC");
}

//******************************************************************************
void * cstartup_getStackTop(uint32_t *size)
{
#pragma section="CSTACK"

  if (size)
  {
     *size = __section_size("CSTACK");
  }

  return __section_end("CSTACK");
}

//******************************************************************************
void * cstartup_getResetVec(void)
{
  return (void *)cstartup;
}

//******************************************************************************
void * cstartup_getSavedData(uint32_t *size)
{
#pragma section="SDATA"

  if (size)
  {
     *size = __section_size("SDATA");
  }

  return __section_begin("SDATA");
}

//******************************************************************************
void cstartup_jumpToApplication(uintptr_t appAddress)
{
  // IAR will store appAddress in r0
  // Load the Stack Pointer from the first dword
  asm(" ldr sp, [r0, #0]");
  // Load the Program Counter from the second dword
  asm(" ldr pc, [r0, #4]");
}


//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
 * This is the entry point loaded into the PC at MCU startup
 *
 * \return void
 *******************************************************************************/
static void cstartup(void)
{
  SystemInit();

  // Initialize static memory and jump to main()
  __iar_program_start();
}

//******************************************************************************
/**
 * Default Interrupt Service Routine, until RAM vector initialized
 *
 * \return void
 *******************************************************************************/
static void default_isr(void)
{
  for (;;);
}

//******************************************************************************
// Vector Table   (0x0000 - 0x03FF)
//  - All initial handlers should be located in flash
//******************************************************************************

extern uint32_t __cstack_end__[];

#pragma location=".intvec"
extern vectorEntry_t const __vector_table[] =
{                                                 //                                                           Vectror Num
  (vectorEntry_t)__cstack_end__,                  //  Initial Stack Pointer                                    0
  cstartup,                                       //  Reset Handler                                            1
  default_isr,                                    //  Non-maskable Interrupt (NMI)                             2
  default_isr,                                    //  Hard Fault                                               3
  default_isr,                                    //  MPU Fault Handler                                        4
  default_isr,                                    //  Bus Fault                                                5
  default_isr,                                    //  Usage Fault                                              6
  default_isr,                                    //  Reserved                                                 7
  default_isr,                                    //  Reserved                                                 8
  default_isr,                                    //  Reserved                                                 9
  default_isr,                                    //  Reserved                                                 10
  default_isr,                                    //  Supervisor call (SVCall)                                 11
  default_isr,                                    //  Debug Monitor                                            12
  default_isr,                                    //  Reserved                                                 13
  default_isr,                                    //  Pendable request for system service                      14
  default_isr,                                    //  System tick timer (SysTick)                              15
#if 0
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 16-23
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 24-31
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 32-39
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 40-47
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 48-55
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 56-63
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 64-71
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 72-79
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 80-87
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 88-95
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 96-103
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 104-111
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 112-119
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 120-127
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 128-135
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 136-143
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 144-151
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 152-159
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 160-167
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 168-175
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 176-183
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 184-191
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 192-199
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 200-207
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 208-215
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 216-223
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 224-231
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 232-239
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr,   // 240-247
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr    // 248-255
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr    // 256-263
  default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr, default_isr    // 264-271
#endif
};


#pragma location=".checksum"
extern uint32_t const __checksum = 0;

