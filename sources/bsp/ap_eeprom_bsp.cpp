//******************************************************************************
/**
 * \file    ap_eeprom_bsp.c
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
 *******************************************************************************/
#include "hw_io.h"
#include "ap_eeprom.h"
#include <stddef.h>

#if HW_NVM_FAKE_MANUFACTURING_DATA
#warning "Fake Manufacturing Data Enabled!"
extern uint8_t const fakeManuData[] =
{
//0x-0  0x-1  0x-2  0x-3   0x-4  0x-5  0x-6  0x-7   0x-8  0x-9  0x-A  0x-B   0x-C  0x-D  0x-E  0x-F
  0x31, 0x32, 0x33, 0x34,  0x35, 0x36, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0x0-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0x1-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0x2-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0x3-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0x4-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0x5-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0x6-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0x7-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0x8-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0x9-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0xA-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0xB-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0xC-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0xD-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0xE-
  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  0xFF, 0xFF, 0xFF, 0xFF,  // 0xF-
};
HW_CTA(sizeof(fakeManuData) == 256);
#endif

HW_CTA(EE_MIRROR_VAR_ADDRESS(queueECU)                  == 0x0530); //queueRecSPN // +2 padding

// E10: Variables 2
HW_CTA(EE_MIRROR_VAR_ADDRESS(UNUSED_VAR2)               == 0x0714); // UNUSED_VAR2
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_ThrottleCalRetracted)   == 0x0786); // ee_ThrottleCalRetracted
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_ThrottleCalExtended)    == 0x0788); // ee_ThrottleCalExtended
HW_CTA(EE_MIRROR_VAR_ADDRESS(UNUSED_VAR3)               == 0x078A); // UNUSED_VAR3
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_ThrottleCalState)       == 0x0792); // ee_ThrottleCalState
HW_CTA(EE_MIRROR_VAR_ADDRESS(var2Checksum)              == 0x0793); // var2Checksum

// E9 - E4: User Info, vitals, events, ...
HW_CTA(EE_MIRROR_VAR_ADDRESS(userInfo)                  == 0x0794); // userInfoRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(doNotUse_0)                == 0x09B6); // doNotUse_0
HW_CTA(EE_MIRROR_VAR_ADDRESS(queueServiceIntervals)     == 0x09B8); // queueServiceIntervalRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(vitals)                    == 0x0A04); // queueVitalRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(queueUserLog)              == 0x0A2C); // queueUserLogRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(queueSwUpdate)             == 0x0A44); // queueSwUpdateRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(NOT_USED)                  == 0x0AAC); // NOT_USED
HW_CTA(EE_MIRROR_VAR_ADDRESS(password)                  == 0x0AF4); // passwordRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(machineIdleTime)           == 0x0BF0); // machineIdleTime
HW_CTA(EE_MIRROR_VAR_ADDRESS(event)                     == 0x0BF4); // eventRec530
HW_CTA(EE_MIRROR_VAR_ADDRESS(queue)                     == 0x0CE4); // queueRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(doNotUse_1)                == 0x0E28); // doNotUse_1
HW_CTA(EE_MIRROR_VAR_ADDRESS(queueService)              == 0x0E2A); // queueServiceClockRec
HW_CTA(EE_MIRROR_VAR_ADDRESS(UNUSED_EVENTS)             == 0x0ECC); // UNUSED_EVENTS

// E3: Variables 1
HW_CTA(EE_MIRROR_VAR_ADDRESS(serviceClockResetTime)     == 0x0EF8); // uint32_t serviceClockResetTime;
HW_CTA(EE_MIRROR_VAR_ADDRESS(serviceClockLength)        == 0x0EFC); // uint32_t serviceClockLength;
HW_CTA(EE_MIRROR_VAR_ADDRESS(consoleTest)               == 0x0F00); // uint8_t  consoleTest;
HW_CTA(EE_MIRROR_VAR_ADDRESS(serviceClockExpired)       == 0x0F01); // uint8_t  serviceClockExpired; // +2 bytes padding
HW_CTA(EE_MIRROR_VAR_ADDRESS(jobClock)                  == 0x0F04); // uint32_t jobClock;
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_AuxFlow)                == 0x0F08); // uint8_t  ee_AuxFlow;        // +1 byte padding
HW_CTA(EE_MIRROR_VAR_ADDRESS(oldAppVersion)             == 0x0F0A); // uint16_t oldAppVersion;
HW_CTA(EE_MIRROR_VAR_ADDRESS(oldCDVersion)              == 0x0F0C); // uint16_t oldCDVersion;
HW_CTA(EE_MIRROR_VAR_ADDRESS(serviceClockType)          == 0x0F0E); // uint8_t  serviceClockType;
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_Version)                == 0x0F0F); // uint8_t  ee_Version;
HW_CTA(EE_MIRROR_VAR_ADDRESS(EngData)                   == 0x0F10); // uint8_t  EngData;             // +3 bytes padding
HW_CTA(EE_MIRROR_VAR_ADDRESS(oldmachineIdleTime)        == 0x0F14); // uint32_t machineIdleTime;
HW_CTA(EE_MIRROR_VAR_ADDRESS(machineFuelConsumption)    == 0x0F18); // uint32_t machineFuelConsumption;
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_AutoIdleEnabled)        == 0x0F1C); // uint8_t  ee_AutoIdleEnabled;
HW_CTA(EE_MIRROR_VAR_ADDRESS(sparevar1)                 == 0x0F1D); // uint8_t  sparevar1;
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_autoIdleTime)           == 0x0F1E); // uint8_t  ee_autoIdleTime;     // +1 byte padding
HW_CTA(EE_MIRROR_VAR_ADDRESS(jobClockLHP)               == 0x0F20); // uint32_t jobClockLHP[2];
HW_CTA(EE_MIRROR_VAR_ADDRESS(deluxe_G5)                 == 0x0F28); // uint8_t  deluxe_G5;
HW_CTA(EE_MIRROR_VAR_ADDRESS(keypad)                    == 0x0F29); // uint8_t  keypad;
HW_CTA(EE_MIRROR_VAR_ADDRESS(sparevar2)                 == 0x0F2A); // uint8_t  sparevar2;
HW_CTA(EE_MIRROR_VAR_ADDRESS(passwordLock)              == 0x0F2B); // uint8_t  passwordLock;
HW_CTA(EE_MIRROR_VAR_ADDRESS(jobClockLock)              == 0x0F2C); // uint8_t  jobClockLock;
HW_CTA(EE_MIRROR_VAR_ADDRESS(serviceClockLock)          == 0x0F2D); // uint8_t  serviceClockLock;
HW_CTA(EE_MIRROR_VAR_ADDRESS(sparevar3)                 == 0x0F2E); // uint8_t  sparevar3[8];
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_ControlMode)            == 0x0F36); // uint8_t  ee_ControlMode
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_EcoMode)                == 0x0F37); // uint8_t  ee_EcoMode;
HW_CTA(EE_MIRROR_VAR_ADDRESS(ee_HydResponse)            == 0x0F38); // uint8_t  ee_HydResponse;
HW_CTA(EE_MIRROR_VAR_ADDRESS(sparevar4)                 == 0x0F39); // uint8_t  sparevar4[4];
HW_CTA(EE_MIRROR_VAR_ADDRESS(recoveryMode)              == 0x0F3D); // uint8_t  recoveryMode;
HW_CTA(EE_MIRROR_VAR_ADDRESS(varChecksum)               == 0x0F3E); // uint8_t  varChecksum;

HW_CTA(sizeof(eeMirrorRec)                              == 0x0A10); // 2576 bytes

HW_CTA(EE_MIRROR_VAR_2_SIZE                             == 0x0080); //  128 bytes
HW_CTA(EE_MIRROR_VAR_1_SIZE                             == 0x0047); //   71 bytes

HW_CTA(EE_MIRROR_START_ADDRESS                          == 0x0530);
HW_CTA(EE_MIRROR_STOP_ADDRESS                           == 0x0F40);
