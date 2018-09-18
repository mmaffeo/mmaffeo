//******************************************************************************
/**
 * \file    ap_eeprom_hcs12.c
 * \author  Chad Swenson
 * \date    November 2014
 * \brief
 *
 * Copyright 2013 Bobcat Company as an unpublished work.
 * All Rights Reserved.
 *
 * The information contained herein is confidential
 * property of Bobcat Company. The use, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Bobcat Company.
 *
 ******************************************************************************/
#include "hw_io.h"
#include "ap_eeprom.h"
#include <stddef.h>


// E10: Variables 2
HW_CTA(EE_MIRROR_VAR_ADDRESS(UNUSED_VAR2)               == 0x0780);  // 780 UNUSED_VAR2
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_ThrottleCalRetracted)   == 0x07F2);  // 7F2 ee_ThrottleCalRetracted
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_ThrottleCalExtended)    == 0x07F4);  // 7F4 ee_ThrottleCalExtended
HW_CTA(EE_MIRROR_VAR_ADDRESS(UNUSED_VAR3)               == 0x07F6);  // 7F6 UNUSED_VAR3
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_ThrottleCalState)       == 0x07FE);  // 7FE ee_ThrottleCalState
HW_CTA(EE_MIRROR_VAR_ADDRESS(var2Checksum)              == 0x07FF);  // 7FF var2Checksum

// E9 - E4: User Info, vitals, events, ...
HW_CTA(EE_MIRROR_VAR_ADDRESS(userInfo)                  == 0x0800);  // 800 userInfoRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(doNotUse_0)                == 0x09CE);  // 9CE doNotUse_0
HW_CTA(EE_MIRROR_VAR_ADDRESS(queueServiceIntervals)     == 0x09D0);  // 9D0 queueServiceIntervalRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(vitals)                    == 0x0A10);  // A10 queueVitalRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(queueUserLog)              == 0x0A38);  // A38 queueUserLogRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(queueSwUpdate)             == 0x0A50);  // A50 queueSwUpdateRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(NOT_USED)                  == 0x0AB8);  // AB8 NOT_USED
HW_CTA(EE_MIRROR_VAR_ADDRESS(password)                  == 0x0B00);  // B00 passwordRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(machineIdleTime)           == 0x0BFC);  // BFC machineIdleTime
HW_CTA(EE_MIRROR_VAR_ADDRESS(event)                     == 0x0C00);  // C00 eventRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(queue)                     == 0x0CF0);  // CF0 queueRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(doNotUse_1)                == 0x0E32);  // E32 doNotUse_1
HW_CTA(EE_MIRROR_VAR_ADDRESS(queueService)              == 0x0E34);  // E34 queueServiceClockRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(UNUSED_EVENTS)             == 0x0ED6);  // ED6 UNUSED_EVENTS

// E3: Variables 1
HW_CTA(EE_MIRROR_VAR_ADDRESS(serviceClockResetTime)     == 0x0F00);  // F00 serviceClockResetTime
HW_CTA(EE_MIRROR_VAR_ADDRESS(serviceClockLength)        == 0x0F04);  // F04 serviceClockLength
HW_CTA(EE_MIRROR_VAR_ADDRESS(consoleTest)               == 0x0F08);  // F08 consoleTest
HW_CTA(EE_MIRROR_VAR_ADDRESS(serviceClockExpired)       == 0x0F09);  // F09 serviceClockExpired
HW_CTA(EE_MIRROR_VAR_ADDRESS(jobClock)                  == 0x0F0A);  // F0A jobClock
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_AuxFlow)                == 0x0F0E);  // F0E ee_AuxFlow
HW_CTA(EE_MIRROR_VAR_ADDRESS(oldAppVersion)             == 0x0F0F);  // F0F oldAppVersion
HW_CTA(EE_MIRROR_VAR_ADDRESS(oldCDVersion)              == 0x0F11);  // F11 oldCDVersion
HW_CTA(EE_MIRROR_VAR_ADDRESS(serviceClockType)          == 0x0F13);  // F13 serviceClockType
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_Version)                == 0x0F14);  // F14 ee_Version
HW_CTA(EE_MIRROR_VAR_ADDRESS(EngData)                   == 0x0F15);  // F15 EngData
HW_CTA(EE_MIRROR_VAR_ADDRESS(oldmachineIdleTime)        == 0x0F16);  // F16 oldmachineIdleTime
HW_CTA(EE_MIRROR_VAR_ADDRESS(machineFuelConsumption)    == 0x0F1A);  // F1A machineFuelConsumption
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_AutoIdleEnabled)        == 0x0F1E);  // F1E ee_AutoIdleEnabled
HW_CTA(EE_MIRROR_VAR_ADDRESS(sparevar1)                 == 0x0F1F);  // F1F sparevar1
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_autoIdleTime)           == 0x0F20);  // F20 ee_autoIdleTime
HW_CTA(EE_MIRROR_VAR_ADDRESS(jobClockLHP)               == 0x0F21);  // F21 jobClockLHP
HW_CTA(EE_MIRROR_VAR_ADDRESS(deluxe_G5)                 == 0x0F29);  // F29 deluxe_G5;
HW_CTA(EE_MIRROR_VAR_ADDRESS(keypad)                    == 0x0F2A);  // F2A keypad;
HW_CTA(EE_MIRROR_VAR_ADDRESS(sparevar2)                 == 0x0F2B);  // F2B sparevar2;
HW_CTA(EE_MIRROR_VAR_ADDRESS(passwordLock)              == 0x0F2C);  // F2C passwordLock;
HW_CTA(EE_MIRROR_VAR_ADDRESS(jobClockLock)              == 0x0F2D);  // F2D jobClockLock;
HW_CTA(EE_MIRROR_VAR_ADDRESS(serviceClockLock)          == 0x0F2E);  // F2E serviceClockLock;
HW_CTA(EE_MIRROR_VAR_ADDRESS(sparevar3)                 == 0x0F2F);  // F2F sparevar3[9];
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_EcoMode)                == 0x0F38);  // F38 ee_EcoMode
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_HydResponse)            == 0x0F39);  // F39 ee_HydResponse
HW_CTA(EE_MIRROR_VAR_ADDRESS(sparevar4)                 == 0x0F3A);  // F3A sparevar4[4]
HW_CTA(EE_MIRROR_VAR_ADDRESS(recoveryMode)              == 0x0F3E);  // F3E recoveryMode
HW_CTA(EE_MIRROR_VAR_ADDRESS(varChecksum)               == 0x0F3F);  // F3F varChecksum


HW_CTA(sizeof(eeMirrorRec)                              == 0x07C0); // 1984 bytes

HW_CTA(EE_MIRROR_VAR_2_SIZE                             == 0x0080); //  128 bytes
HW_CTA(EE_MIRROR_VAR_1_SIZE                             == 0x0040); //   64 bytes

HW_CTA(EE_MIRROR_START_ADDRESS                          == 0x0780);
HW_CTA(EE_MIRROR_STOP_ADDRESS                           == 0x0F40);

