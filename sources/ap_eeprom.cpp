/***************************************************************
* Project Name: GWPZ20283 - Small Loader Electronics
*
* Copyright 2005 Bobcat Company as an unpublished work.
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Bobcat Company. The use, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Bobcat Company.
*
* First written on 23 November, 2005 by Spencer Mindeman
*
* Module Description:
* EEPROM subroutines.
***************************************************************/

//******************************************************************************
// INCLUDES
//******************************************************************************

#include "hw_io.h"
#include <stddef.h>
#include "ap_eeprom.h"
#include "ap_subs.h"
#include "defines.h"
#include "global.h"

#include "cdata.h"

#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"


//******************************************************************************
// DEFINES
//******************************************************************************
#define EEPROM_NUMBER_RETRYS    3


//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************
uint8_t eeCheckSum;   // eeprom.c     signed  -CLY
uint8_t eeState;      // eeprom.c
uint8_t eeMode;                 // eeprom.c
uint8_t eeBusy;                 // eeprom.c
uint8_t eeTimeToUpdateMirror;   // eeprom.c

hourMeterRAM hourCounter[EE_MAX_HOUR_METERS];

const uint8_t EE_HOUR_METER_BLOCK_BEGIN[EE_MAX_HOUR_METERS] =  {0x00, 0x10, 0x20};   // eeprom.c
const uint8_t EE_HOUR_METER_BLOCK_END[EE_MAX_HOUR_METERS]   =  {0x10, 0x20, 0x30};   // eeprom.c

uint32_t  * mirrorPtr;
uint16_t  eeDeviceAddress;
uint16_t  eeWriteDataCounter;
uint16_t  eeWriteAttemptCounter;
uint16_t  eeWriteActualCounter;
uint32_t  eeDataToWrite;


eeMirrorRec eeMirror;// @0x1800;


uint32_t eventStartTime[NUMBER_OF_EVENTS];

uint8_t eventState[NUMBER_OF_EVENTS];

uint8_t cnt_TryAgain;

bool flag_UpdateUserV3;


//******************************************************************************
// FUNCTIONS
//******************************************************************************

uint32_t GetUserJob(uint8_t user)
{
  return (((uint32_t)eeMirror.userInfo[user].jobClockUpper << 16) + eeMirror.userInfo[user].jobClock);
}

void SetUserJob(uint8_t user, uint32_t time)
{
  eeMirror.userInfo[user].jobClock = (uint16_t)time;
  eeMirror.userInfo[user].jobClockUpper = (uint8_t)(time >> 16);
}

uint32_t GetUserIdle(uint8_t user)
{
  return (((uint32_t)eeMirror.userInfo[user].idleTimeUpper << 16) + eeMirror.userInfo[user].idleTime);
}

void SetUserIdle(uint8_t user, uint32_t time)
{
  eeMirror.userInfo[user].idleTime = (uint16_t)time;
  eeMirror.userInfo[user].idleTimeUpper = (uint8_t)(time >> 16);
}


static uint8_t eeReadArray(uint16_t eeAddress, uint8_t * eeDataArray, uint16_t eeReadLength, uint16_t eeMaxSize)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 March, 2006
//    Description : Reads an array of data based on the address.
//    Notes       :
//******************************************************************************
{
  uint8_t tempReturn = 1;

  if((eeAddress + eeReadLength) > eeMaxSize)
  {
    tempReturn = 0;
  }
  else if (hw_nvm_eeprom_read(E3, eeReadLength, eeAddress, eeDataArray) != NVM_OK)
  {
    tempReturn = 0;
  }

  return tempReturn;
}

static void eeFindHourMeterBank(hourMeterRAM * counter, uint8_t hourMeter)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 5 Jan, 2006
//    Description : Finds the valid hour meter bank for each block.
//    Notes       :
//******************************************************************************
{
  uint32_t temp;
//  uint16_t eeResult;

  // Start at the end of the hourmeter block.
  counter->pointer = EE_HOUR_METER_BLOCK_END[hourMeter];
  eeCheckSum = 1;

//while((eeCheckSum) && (counter->pointer != EE_HOUR_METER_BLOCK_BEGIN[hourMeter]))
  while((uint8_t)(eeCheckSum + 1) && (counter->pointer != EE_HOUR_METER_BLOCK_BEGIN[hourMeter]))
  {
    counter->pointer -= (EE_HOUR_METER_BANK_SIZE*4);
    counter->value = 0;
    temp = 0;
    eeCheckSum = 0;

    //Read hourmeter value
    hw_nvm_eeprom_read_uint32(E1, (uint8_t)counter->pointer, &temp);

    // Valid sum of all will be  -1 or (0xFF)
    eeCheckSum = (uint8_t)(temp >> 24) + (uint8_t)(temp >> 16) + (uint8_t)(temp >> 8) + (uint8_t)(temp);
    counter->value = (temp >> 8);  // Get the value of the hour meter, minus checksum data.

  }

  if(eeCheckSum != 0xFF)
  {
    counter->pointer = INVALID;
  }
}

static uint8_t eeUpdateHourMeter(hourMeterRAM * counter)
//******************************************************************************
//    returns     : status of update (see enum returnStates in eeprom.h)
//
//    Created By  : SLM
//    Date Created: 5 Jan, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  uint8_t   returnStatus = 0;
  uint32_t  temp;
  uint16_t  eeResult;
  uint8_t   tmpCheckSum;

  switch (eeState)
  {
    case EE_HM_WRITE_INIT:

      // Calculate checksum
//    tmpCheckSum = ~((uint8_t)(counter->value >> 16) + (uint8_t)(counter->value >> 8) + (uint8_t)(counter->value)) + 1;
//    -CLY Note don't want checksum to be zero when value is zero.  We want:  value + checksum + 1 = 0

      tmpCheckSum = ~((uint8_t)(counter->value >> 16) + (uint8_t)(counter->value >> 8) + (uint8_t)(counter->value));

      eeDataToWrite = (counter->value << 8) + tmpCheckSum;

      eeDeviceAddress = counter->pointer;   // Set starting address for write
      eeWriteDataCounter = 0;               // Clear total number of bytes written
      eeWriteAttemptCounter = 0;            // Clear write atempts at current device address
      eeState = EE_HM_READ_COMPARE;
      // don't break, fall into next state

    case EE_HM_READ_COMPARE:
      eeResult = hw_nvm_eeprom_read_uint32(E1,eeDeviceAddress, &temp);

      // Check to see read completed ok.
      if(eeResult == NVM_OK)
      {
        if(eeDataToWrite == temp)
        {
          // We are done writing to EEPROM
          eeMode  = EE_IDLE;   // Exit state machine
          eeState = EE_IDLE;   // Exit state machine
          eeBusy  = FALSE;
        }
        else
        {
          eeState = EE_HM_WRITE;
        }
      }
    break;

    case EE_HM_WRITE:
      if (eeDeviceAddress < EE_DEVICE_SIZE_E1)
      {
        eeResult = hw_nvm_eeprom_write_uint32(E1,eeDeviceAddress,eeDataToWrite);

        // Make sure data was sent to write queue
        if(eeResult == NVM_OK)
        {
          eeState = EE_HM_READ_VERIFY;
        }

        eeWriteAttemptCounter++;
      }
      else
      {
        eeState = EE_HM_COMPLETE;
        eeBusy = FALSE;
      }
    break;

    case EE_HM_READ_VERIFY:
      // Rereads the previously programmed cell */
      // Check if device is done programming last cell */
      eeResult = hw_nvm_eeprom_read_uint32(E1,eeDeviceAddress,&temp);
      if(eeResult == NVM_OK)
      {
        if(eeDataToWrite == temp)
        {
          //eeWriteAttemptCounter = 0;  // if write is successfull, set for next write
          //eeDeviceAddress += 4;

          //if(++eeWriteDataCounter >= EE_HOUR_METER_BANK_SIZE)
          //{
            eeMode  = EE_IDLE;
            eeState = EE_IDLE;    // if bank write is complete, exit  state machine
            eeBusy  = FALSE;
          //}
          //else
          //{
          //  eeState = EE_HM_READ_COMPARE; // else compare next byte to be written
          //}
        }
        else
        {
          // There was a Write error
          if(eeWriteAttemptCounter > EE_MAX_WRITE_ATTEMPT)
          {
            // if max # of attemps is exceeded, return a failure
            eeBusy  = FALSE;
            eeMode  = EE_IDLE;
            eeState = EE_IDLE;
            returnStatus = EE_WRITE_FAILURE;
          }
          else
          {
            // else try to write the value again
            eeState = EE_HM_WRITE;
          }
        }
      }

    break;

    default:
      // Unknown eeState, exit state machine
      eeMode  = EE_IDLE;
      eeState = EE_IDLE;
      eeBusy  = FALSE;
      returnStatus = EE_LOST_STATE;
  }

  return returnStatus;
}

static uint8_t eeClearHourMeter(hourMeterRAM * counter)
//******************************************************************************
//    returns     : clear hourmeter
//
//    Created By  : SLM
//    Date Created: 16 Jan, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  uint8_t returnStatus;
  uint32_t temp;
  uint16_t eeResult;

  returnStatus = EE_SUCCESSFUL;

  switch (eeState)
  {
    case EE_CLEAR_WRITE_INIT:
      eeDataToWrite = 0xFFFFFFFF;
      eeDeviceAddress = EE_HOUR_METER_BLOCK_BEGIN[currentHourMeter];  // set atarting address for write
      eeWriteDataCounter = 0;                                         // clear total number of bytes written
      eeWriteAttemptCounter = 0;                                      // clear write attempts at current device address
      eeState = EE_CLEAR_READ_COMPARE;

      // don't break, fall into next state

    case EE_CLEAR_READ_COMPARE:  // if data to be written is same as the value in the eeprom, skip it

      eeResult = hw_nvm_eeprom_read_uint32(E1, eeDeviceAddress, &temp);

      if(eeResult == NVM_OK)
      {
        if(eeDeviceAddress == counter->pointer)
        {
          // don't clear bank that has valid data
          eeDeviceAddress += EE_HOUR_METER_BANK_SIZE*4;
          eeWriteDataCounter += EE_HOUR_METER_BANK_SIZE;
          eeWriteAttemptCounter = 0;

          if (eeWriteDataCounter >= EE_HOUR_METER_BANK_SIZE*EE_BANKS_PER_HOUR_METER)
          {
            eeState = EE_CLEAR_COMPLETE;  // done clearing block
            eeBusy = FALSE;
          }
        }
        else if(0xFFFFFFFF == temp)
        {
          // verify write data is different from eeprom data
          eeDeviceAddress += 4;    // if they are the same, goto the next bank

          if (++eeWriteDataCounter >= EE_HOUR_METER_BANK_SIZE*EE_BANKS_PER_HOUR_METER)
          {
            eeState = EE_CLEAR_COMPLETE;  // done clearing block
            eeBusy = FALSE;
          }
        }
        else
        {
          eeState = EE_CLEAR_WRITE;
        }
      }
    break;

    case EE_CLEAR_WRITE:
      // EE WRITE STATE

      if (eeDeviceAddress < EE_DEVICE_SIZE_E1)
      {
        eeResult = hw_nvm_eeprom_write_uint32(E1,eeDeviceAddress, 0xFFFFFFFF);

        if(eeResult == NVM_OK)
        {
          eeState = EE_CLEAR_READ_VERIFY;
          eeWriteAttemptCounter++;
        }
      }
      else
      {
        eeState = EE_CLEAR_COMPLETE;
        eeBusy = FALSE;
      }
    break;

    case EE_CLEAR_READ_VERIFY:
      // Rereads the previously programmed cell
      // Check if device is done programming last cell
      eeResult = hw_nvm_eeprom_read_uint32(E1, eeDeviceAddress, &temp);

      if(eeResult == NVM_OK)
      {
        // Write is Complete, ReRead and Verify

        // hw_nvm_eeprom_read(E1, eeDeviceAddress, &temp);
        if(0xFFFFFFFF == temp)
        {
          eeWriteAttemptCounter = 0;
          eeDeviceAddress += 4;

          if (++eeWriteDataCounter >= EE_HOUR_METER_BANK_SIZE*EE_BANKS_PER_HOUR_METER)
          {
            eeState = EE_CLEAR_COMPLETE;
            eeBusy = FALSE;
          }
          else
          {
            eeState = EE_CLEAR_READ_COMPARE;  // compare next byte
          }
        }
        else
        {
          // There was a Write error
          if (eeWriteAttemptCounter > EE_MAX_WRITE_ATTEMPT)
          {
            eeDeviceAddress += 4;     // if max # of attemps is exceeded, return a failure
            eeWriteDataCounter++;
            eeState = EE_CLEAR_READ_COMPARE;  // however here continue on with next byte
            returnStatus = EE_WRITE_FAILURE;
          }
          else
          {
            // try same byte again
            eeState = EE_CLEAR_WRITE;
          }
        }
      }
    break;

    default:
      // Unknown eeState, reset.
      eeState = EE_CLEAR_COMPLETE;     // abort clear
      eeBusy = FALSE;
      returnStatus = EE_LOST_STATE;
    break;

  } // End of Switch statement

  return returnStatus;
}

void RestoreDefaultPassword(uint8_t eepromNumber)
//******************************************************************************
//    returns     : N/A
//
//    Created By  : SLM
//    Date Created: 2 Aug, 2007
//    Description : Restores the default passwords if checkum is incorrect
//    Notes       :
//******************************************************************************
{
    uint8_t i;

    switch (eepromNumber)
    {
      case 0: // owner
        eeMirror.password[eepromNumber].checksum = 0;
        for(i = 0; i < PASSWORD_SIZE; i++)
        {
          eeMirror.password[eepromNumber].value[i] = OWNER_PWD[i];
        }
        eeMirror.password[eepromNumber].unused = 0xFF; /* not figured into the checksum calculation */
      break;

      case 1: /* user 1 - 20 */
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
      case 18:
      case 19:
      case 20:
        eeMirror.password[eepromNumber].checksum = 0;

        for (i = 0; i < PASSWORD_SIZE; i++)
        {
          eeMirror.password[eepromNumber].value[i] = 0;
        }

        eeMirror.password[eepromNumber].unused = 0xFF;   // not figured into the checksum calculation
      break;
    }
}

#if 0
void RestorePassword(uint8_t eepromNumber)
 //******************************************************************************
//    returns     : N/A
//
//    Created By  : SLM
//    Date Created: 2 Aug, 2007
//    Description : Restores the default passwords if checkum is incorrect
//    Notes       :
//******************************************************************************{
{
  uint8_t * mPtr;
  uint8_t checksum = 0;

  checksum = 0;

  mPtr = EE_MIRROR_VAR_POINTER(password[0]);
  mPtr += (sizeof(eeMirror.password[0]) * eepromNumber);

  eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(password[0]);
  eeDeviceAddress += (sizeof(eeMirror.password[0]) * eepromNumber);

  if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.password[eepromNumber]), EE_MIRROR_STOP_ADDRESS))
  {
    while (mPtr <= (uint8_t *) &eeMirror.password[eepromNumber].checksum)
    {
      if (mPtr == (uint8_t *) &eeMirror.password[eepromNumber].checksum)
      {
        if (checksum)      // reset if checksum doesn't work out
        {
          RestoreDefaultPassword(eepromNumber);
        }

        checksum = 0;
      }
      mPtr++;
    }
  }
}
#endif


void RestoreDefaultUser(uint8_t eepromNumber)
//******************************************************************************
//    returns     : N/A
//
//    Created By  : SLM
//    Date Created: 6 Nov, 2008
//    Description : Restores the default user info if checkum is incorrect
//    Notes       :
//******************************************************************************
{
    uint8_t i;

    switch (eepromNumber)
    {
      case 0: // owner
      case 1: /* user 1 - 20 */
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
      case 18:
      case 19:
      case 20:
        eeMirror.userInfo[eepromNumber].checksum        = 0;
        eeMirror.userInfo[eepromNumber].locks           = 0x08;
        eeMirror.userInfo[eepromNumber].idleTime        = 0;
        eeMirror.userInfo[eepromNumber].idleTimeUpper   = 0;
        eeMirror.userInfo[eepromNumber].fuelConsumption = 0;
        eeMirror.userInfo[eepromNumber].jobClock        = 0;
        eeMirror.userInfo[eepromNumber].jobClockUpper   = 0;
        eeMirror.userInfo[eepromNumber].driveResponse = 2;
        eeMirror.userInfo[eepromNumber].wkgpResponse = 2;

        for (i = 0; i < USER_NAME_SIZE; i++)
        {
          eeMirror.userInfo[eepromNumber].user_name[i] = 0;
        }
      break;
    }
}

#if 0
void RestoreUser(uint8_t eepromNumber)
 //******************************************************************************
//    returns     : N/A
//
//    Created By  : SLM
//    Date Created: 2 Aug, 2007
//    Description : Restores the default passwords if checkum is incorrect
//    Notes       :
//******************************************************************************{
{
  uint8_t * mPtr;
  uint8_t checksum = 0;

  checksum = 0;

  mPtr = EE_MIRROR_VAR_POINTER(userInfo[0]);
  mPtr += (sizeof(eeMirror.userInfo[0]) * eepromNumber);

  eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(userInfo[0]);
  eeDeviceAddress += (sizeof(eeMirror.userInfo[0]) * eepromNumber);

  if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.userInfo[eepromNumber]), EE_MIRROR_STOP_ADDRESS))
  {
    while (mPtr <= (uint8_t *) &eeMirror.userInfo[eepromNumber].checksum)
    {
      if (mPtr == (uint8_t *) &eeMirror.userInfo[eepromNumber].checksum)
      {
        if (checksum)      // reset if checksum doesn't work out
        {
          RestoreDefaultUser(eepromNumber);
        }

        checksum = 0;
      }
      mPtr++;
    }
  }
}
#endif


static uint8_t eeUpdateMirrorEvents(void)
//******************************************************************************
//    returns     :
//
//    Created By  : SLM
//    Date Created: 07 Feb, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  uint8_t  returnStatus;
  uint16_t eeResult;
  uint32_t temp;

  returnStatus = EE_SUCCESSFUL;

  switch (eeState)
  {
    case EE_MIRROR_WRITE_INIT:
      mirrorPtr = (uint32_t *) &eeMirror;
      eeDeviceAddress = EE_MIRROR_START_ADDRESS;   // set a starting address for write
      eeWriteDataCounter = 0;             // clear total number of bytes written
      eeWriteAttemptCounter = 0;          // clear write attempts at current device address
      eeState = EE_MIRROR_READ_COMPARE;
      // don't break, fall into next state

    case EE_MIRROR_READ_COMPARE:  // if data to be written is same as the value in the eeprom, skip it
      eeResult = hw_nvm_eeprom_read_uint32(E3, eeDeviceAddress, &temp);

      if(eeResult == NVM_OK)
      {
        if(*mirrorPtr == temp)
        {
          // verify write data is different from eeprom data
          eeDeviceAddress+=4;
          mirrorPtr++;          // if they are the same, goto the next double word

          eeWriteDataCounter+=4;
          if (eeWriteDataCounter >= sizeof(eeMirror))
          {
            // if we are done writing to eeprom
            eeMode  = EE_IDLE;      // exit state machine
            eeState = EE_IDLE;      // exit state machine
            eeBusy  = FALSE;
          }
        }
        else
        {
          eeState = EE_MIRROR_WRITE;
        }
      }
    break;

    case EE_MIRROR_WRITE:
      if(eeDeviceAddress < EE_MIRROR_STOP_ADDRESS)
      {
        eeResult = hw_nvm_eeprom_write_uint32(E3, eeDeviceAddress, *mirrorPtr);

        if(eeResult == NVM_OK)
        {
          eeState = EE_MIRROR_READ_VERIFY;
        }

        eeWriteAttemptCounter++;
        eeWriteActualCounter++;
      }
      else
      {
        eeState = EE_MIRROR_COMPLETE;
        eeBusy = FALSE;
      }
    break;

    case EE_MIRROR_READ_VERIFY:

      // Rereads the previously programmed cell
      // Check if device is done programming last cell
      eeResult = hw_nvm_eeprom_read_uint32(E3, eeDeviceAddress, &temp);

      if(eeResult == NVM_OK)
      {
        // Write is Complete, ReRead and Verify
        if(*mirrorPtr == temp)
        {
          eeWriteAttemptCounter = 0;  // if write is successfull, set for next write
          eeDeviceAddress+=4;
          mirrorPtr++;

          eeWriteDataCounter+=4;
          if(eeWriteDataCounter >= sizeof(eeMirror))
          {
            eeMode  = EE_IDLE;
            eeState = EE_IDLE;    // if bank write is complete, exit  state machine
            eeBusy  = FALSE;
          }
          else
          {
            eeState = EE_MIRROR_READ_COMPARE; // else compare next byte to be written
          }
        }
        else
        {
          // There was a Write error
          if(eeWriteAttemptCounter > EE_MAX_WRITE_ATTEMPT)
          {
            eeWriteAttemptCounter = 0;  // if write failed x times go on, set for next write
            eeDeviceAddress+=4;
            mirrorPtr++;

            eeWriteDataCounter+=4;
            if(eeWriteDataCounter >= sizeof(eeMirror))
            {
              eeMode  = EE_IDLE;
              eeState = EE_IDLE;    // if bank write is complete, exit  state machine
              eeBusy  = FALSE;
            }
            else
            {
              eeState = EE_MIRROR_READ_COMPARE; // else compare next byte to be written
            }

            returnStatus = EE_WRITE_FAILURE;
          }
          else
          {
            // else try to write the value again
            eeState = EE_MIRROR_WRITE;
          }
        }
      }
    break;

    default:
      // Unknown eeState, exit state machine
      eeMode = EE_IDLE;
      eeState = EE_IDLE;
      eeBusy = FALSE;
      returnStatus = EE_LOST_STATE;
    break;
  } // End of Switch statement

  return returnStatus;
}

void UpdateEEVariables(uint8_t when)
//******************************************************************************
//    returns     :
//
//    Created By  : SLM
//    Date Created: 09 Feb, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  uint8_t * varPtr;

  //Original variable area at end of mirror
  eeMirror.varChecksum = 0;

  for (varPtr = (uint8_t *) &eeMirror.serviceClockResetTime; varPtr < (uint8_t *) &eeMirror.varChecksum; varPtr++)
  {
    eeMirror.varChecksum += *varPtr;
  }

  eeMirror.varChecksum = ~eeMirror.varChecksum + 1;

  //Second variable area at start of mirror
  eeMirror.var2Checksum = 0;

  for (varPtr = (uint8_t *) &eeMirror.UNUSED_VAR2; varPtr < (uint8_t *) &eeMirror.var2Checksum; varPtr++)
  {
    eeMirror.var2Checksum += *varPtr;
  }

  eeMirror.var2Checksum = ~eeMirror.var2Checksum + 1;



  if (when == NOW)
  {
    eeTimeToUpdateMirror = TRUE;
  }
}

static void RestoreDefaultEEVariables(void)
//******************************************************************************
//    returns     :
//
//    Created By  : SLM
//    Date Created: 09 Feb, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  //uint16_t i;

  // restore eeMirror.xxxx to their default values

  eeMirror.serviceClockResetTime = 0xFFFFFFFF;
  eeMirror.serviceClockLength = 250;
  eeMirror.consoleTest = 0x18;
  eeMirror.serviceClockExpired = FALSE;
  eeMirror.jobClock = 0;
  eeMirror.ee_AuxFlow = 0;
  eeMirror.oldAppVersion = 0xFFFF;
  eeMirror.oldCDVersion = 0xFFFF;
  eeMirror.serviceClockType = 1;
  eeMirror.ee_Version = EEPROM_VERSION;
  eeMirror.EngData = 0xFF;
  eeMirror.machineIdleTime = 0;
  eeMirror.machineFuelConsumption = 0;
  eeMirror.ee_AutoIdleEnabled = 0;
  eeMirror.ee_autoIdleTime = (uint8_t)(CONSTANT_DATA->AUTOIDLE_IDLE_DELAY/10);  // 100ms timer, divide by 10 to get sec
  eeMirror.jobClockLHP[0] = 0;
  eeMirror.jobClockLHP[1] = 0;
  eeMirror.deluxe_G5 = INACTIVE;
  eeMirror.keypad = INACTIVE;
  //eeMirror.RFIDKey = INACTIVE;
  eeMirror.passwordLock      = FALSE;
  eeMirror.jobClockLock      = FALSE;
  eeMirror.serviceClockLock    = FALSE;
  eeMirror.ee_EcoMode = INACTIVE;
  eeMirror.ee_HydResponse = INACTIVE;
  eeMirror.ee_ControlMode = EE_NA_NA;


  //for (i = 0; i < EE_UNUSED_BYTES_E3; i++)
  //{
  //  eeMirror.var2[i] = 0xA5;
  //}

  eeMirror.recoveryMode   = TRUE;





  UpdateEEVariables(NOW);
}

static void RestoreDefaultEEVariables2(void)
//******************************************************************************
//    returns     :
//
//    Created By  : SLM
//    Date Created: 09 Feb, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  //uint16_t i;

  // restore eeMirror.xxxx to their default values

  eeMirror.ee_ThrottleCalState = NOT_CALIBRATED;

  eeMirror.ee_ThrottleCalRetracted = CONSTANT_DATA->CAN_THROTTLE_CAL_EXTENDED_DEFAULT;
  eeMirror.ee_ThrottleCalExtended = CONSTANT_DATA->CAN_THROTTLE_CAL_RETRACTED_DEFAULT;

  UpdateEEVariables(NOW);
}

static void RestoreNewEEVariables(void)
//******************************************************************************
//    returns     : NONE
//
//    Created By  : SLM
//    Date Created: 19 May, 2009
//    Description : Resets any new eeprom variables from a previous version that need to be initialized.
//    Notes       :
//******************************************************************************
{
  //uint16_t i;

  // restore eeMirror.xxxx to their default values that changed from previous versions
  // Flags
  if(eeMirror.ee_Version < 2)  //Update to get rid of bitfields in ee mirror
  {
    eeMirror.deluxe_G5 = FALSE;
    eeMirror.keypad = FALSE;
    //eeMirror.RFIDKey = FALSE;
    eeMirror.passwordLock = FALSE;
    eeMirror.jobClockLock = FALSE;
    eeMirror.serviceClockLock    = FALSE;
    eeMirror.serviceClockExpired = FALSE;
    eeMirror.ee_Version = EEPROM_VERSION;
  }
  
  if(eeMirror.ee_Version < 3)
  {
    //copy machine idle time over to the new location
    eeMirror.machineIdleTime = eeMirror.oldmachineIdleTime;
  }
  
  UpdateEEVariables(NOW);
  // TODO asm NOP;
}

static void eeRestoreMirror(void)
//******************************************************************************
//    returns     :
//
//    Created By  : SLM
//    Date Created: 09 Feb, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  uint8_t * mPtr;
  uint8_t checksum, i;
  uint8_t * bytePtr;

  checksum = 0;





  switch (eeState)
  {
    case EE_MIRROR_RESTORE_VARIABLES:
      mPtr = EE_MIRROR_VAR_1_POINTER;
      eeDeviceAddress = EE_MIRROR_VAR_1_START;

      if(eeReadArray(eeDeviceAddress, mPtr, EE_MIRROR_VAR_1_SIZE, EE_MIRROR_STOP_ADDRESS))
      {
        while(mPtr <= (uint8_t *) &eeMirror.varChecksum)
        {
          checksum += *mPtr;
          mPtr++;
        }

        if(checksum)
        {
          cnt_TryAgain++;

          if(cnt_TryAgain > EEPROM_NUMBER_RETRYS)
          {
            // if checksum fails, restore defaults
            RestoreDefaultEEVariables();
            cnt_TryAgain = 0;
            eeState = EE_MIRROR_RESTORE_VARIABLES2;
          }
        }
        else
        {
          eeState = EE_MIRROR_RESTORE_VARIABLES2;                  // goto next state
          cnt_TryAgain = 0;
        }

        //Check eeprom version number, if lower or not defined (0xA5) used as a not defined map any newly created variables
        if((eeMirror.ee_Version < EEPROM_VERSION) || (eeMirror.ee_Version == 0xFF) || (eeMirror.ee_Version == 0xA5))
        {
          RestoreNewEEVariables();
        }

      }
    break;

    case EE_MIRROR_RESTORE_VARIABLES2:
      mPtr = EE_MIRROR_VAR_2_POINTER;
      eeDeviceAddress = EE_MIRROR_VAR_2_START;

      if(eeReadArray(eeDeviceAddress, mPtr, EE_MIRROR_VAR_2_SIZE, EE_MIRROR_STOP_ADDRESS))
      {
        while(mPtr <= (uint8_t *) &eeMirror.var2Checksum)
        {
          checksum += *mPtr;
          mPtr++;
        }

        if(checksum)
        {
          cnt_TryAgain++;

          if(cnt_TryAgain > EEPROM_NUMBER_RETRYS)
          {
            // if checksum fails, restore defaults
            RestoreDefaultEEVariables2();
            cnt_TryAgain = 0;
            eeState = EE_MIRROR_RESTORE_PASSWORDS;
          }
        }
        else
        {
          eeState = EE_MIRROR_RESTORE_PASSWORDS;                  // goto next state
          cnt_TryAgain = 0;
        }

      }
    break;

    case EE_MIRROR_RESTORE_PASSWORDS:
      mPtr = EE_MIRROR_VAR_POINTER(password);
      eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(password);
      i=0;

      if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.password),EE_MIRROR_STOP_ADDRESS))
      {
        while (mPtr <= (uint8_t *) &eeMirror.password[NUMBER_OF_EE_PASSWORDS-1].checksum)
        {
          checksum += *mPtr;

          if(mPtr == (uint8_t *) &eeMirror.password[i].checksum)
          {
            // Verify that the value isn't zeros for owner and checksum isn't zero
            // if it is, this indicates that owner hasn't changed it yet, so keep restoring from constant data
              // Do not do this for Gen5.5 (7") display since it is responsible for reporting owner password/default password
            if((i == 0) && (eeMirror.password[i].value[0] == 0) && (eeMirror.password[i].checksum == 0) && (CONSTANT_DATA->DELUXE_GEN5_5_FUNCTION == NON_FUNCTIONAL))
            {
              RestoreDefaultPassword(i);
            }

            // Reset if checksum doesn't work out
            if(checksum)
            {
              RestoreDefaultPassword(i);
            }

            checksum = 0;
            mPtr++; //Skip over the unused byte
            i++;
          }
          mPtr++;
        }
        eeState = EE_MIRROR_RESTORE_USER_INFO;      // goto next state
      }

    break;

    case EE_MIRROR_RESTORE_USER_INFO:
      mPtr = EE_MIRROR_VAR_POINTER(userInfo);
      eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(userInfo);
      i=0;

      if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.userInfo),EE_MIRROR_STOP_ADDRESS))
      {
        while (mPtr <= (uint8_t *) &eeMirror.userInfo[NUMBER_OF_EE_PASSWORDS-1].checksum)
        {
          checksum += *mPtr;

          if(mPtr == (uint8_t *) &eeMirror.userInfo[i].checksum)
          {
            // Reset if checksum doesn't work out
            if(checksum)
            {
              RestoreDefaultUser(i);
            }

            checksum = 0;
            i++;
            if(i <= NUMBER_OF_EE_PASSWORDS)
            {
              mPtr = (uint8_t *) &eeMirror.userInfo[i].locks - 1; // set pointer to 1 byte before start of next user
            }
          }
          mPtr++;
        }

        //Check to see i fthe idle time and fuel consumption need to be zero'd out.  Previously they were after hourlock
        //and part of the job clock, so values need to be cleared otherwise you will get some strange values for them.
        if(flag_UpdateUserV3)
        {
          for(i = 0; i < NUMBER_OF_PASSWORDS; i++)
          {
            eeMirror.userInfo[i].idleTime        = 0;
            eeMirror.userInfo[i].idleTimeUpper   = 0;
            eeMirror.userInfo[i].fuelConsumption = 0;

            eeMirror.userInfo[i].checksum = 0;

            bytePtr = (uint8_t *) &eeMirror.userInfo[i].locks;

            for (; bytePtr < (uint8_t *) &eeMirror.userInfo[i].checksum; bytePtr++)
            {
              eeMirror.userInfo[i].checksum += *bytePtr;
            }// end for

            eeMirror.userInfo[i].checksum = ~eeMirror.userInfo[i].checksum + 1;
          }

          eeTimeToUpdateMirror = TRUE;
        }

        eeState = EE_MIRROR_RESTORE_EVENTS;     // goto next state
      }
    break;

    case EE_MIRROR_RESTORE_EVENTS:
      mPtr = EE_MIRROR_VAR_POINTER(event);
      eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(event);
      i = 0;

      // Read the array of data
      if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.event), EE_MIRROR_STOP_ADDRESS))
      {
       //while(mPtr < (&eeMirror.event[NUMBER_OF_EVENTS-1].checksum) + 1)
        while(mPtr < (uint8_t *) &eeMirror.event + sizeof(eeMirror.event))


        {
          checksum += *mPtr;

          if(mPtr == (uint8_t *) &eeMirror.event[i].checksum)
          {
            if(checksum)
            {
              // clear if checksum doesn't work out
              eeMirror.event[i].time       = 0xFFFF;
              eeMirror.event[i].duration   = 0xFFFF;
              eeMirror.event[i].occurances = 0xFF;
              eeMirror.event[i].checksum   = 0xFF;
            }

            checksum = 0;
            i++;
          }

          mPtr++;
        }

        #ifndef HCS12_BSP_EMU //if HCS12 compile this
        eeState = EE_MIRROR_RESTORE_QUEUE;
        #endif
        #ifdef HCS12_BSP_EMU //if M4 compile this
        eeState = EE_MIRROR_RESTORE_ECUQUEUE;
        #endif
      }
    break;
   
    #ifdef HCS12_BSP_EMU //if M4 compile this
    //restores ecu queue
    case EE_MIRROR_RESTORE_ECUQUEUE:
      mPtr = EE_MIRROR_VAR_POINTER(queueECU);
      eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(queueECU);

      if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.queueECU), EE_MIRROR_STOP_ADDRESS))
      {
        checksum = 0;
        while(mPtr <= (uint8_t *) &eeMirror.queueECU.checksum)
        {
          checksum += *mPtr;
          mPtr++;
        }
     
        if(checksum)
        {
          mPtr = (uint8_t *) &eeMirror.queueECU;
      
          while (mPtr <= (uint8_t *) &eeMirror.queueECU.checksum)
          {
            *mPtr = 0xFF;
            mPtr++;
          }
      
          eeMirror.queueECU.pointer = EVENT_DIAG_QUEUE_SIZE - 1; 
          eeTimeToUpdateMirror = TRUE;
        }		
        if(eeMirror.queueECU.pointer >= EVENT_DIAG_QUEUE_SIZE)
        {
          eeMirror.queueECU.pointer = EVENT_DIAG_QUEUE_SIZE - 1;  // set for first increment to be to 0 
        }		
     
        eeState = EE_MIRROR_RESTORE_QUEUE;
      }
    break;
    #endif
    
    case EE_MIRROR_RESTORE_QUEUE:
      mPtr = EE_MIRROR_VAR_POINTER(queue);
      eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(queue);

      if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.queue), EE_MIRROR_STOP_ADDRESS))
      {
        checksum = 0;
        while(mPtr <= (uint8_t *) &eeMirror.queue.checksum)
        {
          checksum += *mPtr;
          mPtr++;
        }

        if(checksum)
        {
          mPtr = (uint8_t *) &eeMirror.queue;

          while (mPtr <= (uint8_t *) &eeMirror.queue.checksum)
          {
            *mPtr = 0xFF;
            mPtr++;
          }

          eeMirror.queue.pointer = EVENT_DIAG_QUEUE_SIZE - 1;
          eeTimeToUpdateMirror = TRUE;
        }
        if(eeMirror.queue.pointer >= EVENT_DIAG_QUEUE_SIZE)
        {
          eeMirror.queue.pointer = EVENT_DIAG_QUEUE_SIZE - 1;  // set for first increment to be to 0
        }

        eeState = EE_MIRROR_RESTORE_SERVICE_CLOCK_QUEUE;
      }
    break;

    case EE_MIRROR_RESTORE_SERVICE_CLOCK_QUEUE:
      mPtr = EE_MIRROR_VAR_POINTER(queueService);
      eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(queueService);

      if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.queueService), EE_MIRROR_STOP_ADDRESS))
      {
        checksum = 0;
        while(mPtr <= (uint8_t *) &eeMirror.queueService.checksum)
        {
          checksum += *mPtr;
          mPtr++;
        }

        if(checksum)
        {
          mPtr = (uint8_t *) &eeMirror.queueService;

          while(mPtr <= (uint8_t *) &eeMirror.queueService.checksum)
          {
            *mPtr = 0xFF;
            mPtr++;
          }

          eeMirror.queueService.pointer =  NUMBER_SERVICE_CLOCK_EVENTS - 1;
          eeTimeToUpdateMirror = TRUE;
        }
        else if(eeMirror.queueService.pointer >= NUMBER_SERVICE_CLOCK_EVENTS)
        {
          eeMirror.queueService.pointer = NUMBER_SERVICE_CLOCK_EVENTS - 1;  // set for first increment to be 0
        }

        eeState = EE_MIRROR_RESTORE_SERVICE_INTERVALS;
      }
    break;

    case EE_MIRROR_RESTORE_SERVICE_INTERVALS:
      mPtr = EE_MIRROR_VAR_POINTER(queueServiceIntervals);
      eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(queueServiceIntervals);

      if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.queueServiceIntervals), EE_MIRROR_STOP_ADDRESS))
      {
        checksum = 0;
        while(mPtr <= (uint8_t *) &eeMirror.queueServiceIntervals.checksum)
        {
          checksum += *mPtr;
          mPtr++;
        }

        if(checksum)
        {
          for(uint8_t i=0; i <= MAX_NUMBER_SERVICE_INTERVALS; i++)
          {
            eeMirror.queueServiceIntervals.serviceInterval[i].type = 0;
            eeMirror.queueServiceIntervals.serviceInterval[i].state = 0;
            eeMirror.queueServiceIntervals.serviceInterval[i].interval = MXGTW_SERVICE_DEFAULT_HOURS[i];
            eeMirror.queueServiceIntervals.serviceInterval[i].reset_time = actualHourMeter;
            eeMirror.queueServiceIntervals.serviceInterval[i].icon = MXGTW_SERVICE_DEFAULT_ICON[i];
            eeMirror.queueServiceIntervals.serviceInterval[i].text = MXGTW_SERVICE_DEFAULT_TEXT[i];
          }

          eeMirror.queueServiceIntervals.reserved[0] = 0xFF;
          eeMirror.queueServiceIntervals.reserved[1] = 0xFF;
          eeMirror.queueServiceIntervals.reserved[2] = 0xFF;

          mPtr = (uint8_t *) &eeMirror.queueServiceIntervals;

          checksum = 0;
          while(mPtr < (uint8_t *) &eeMirror.queueServiceIntervals.checksum)
          {
            checksum += *mPtr;
            mPtr++;
          }

          eeMirror.queueServiceIntervals.checksum = ~checksum + 1;

          mPtr = (uint8_t *) &eeMirror.queueServiceIntervals;

          eeTimeToUpdateMirror = TRUE;
        }

        eeState = EE_MIRROR_RESTORE_VITALS;
      }
    break;

    case EE_MIRROR_RESTORE_VITALS:
      mPtr = EE_MIRROR_VAR_POINTER(vitals);
      eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(vitals);

      if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.vitals), EE_MIRROR_STOP_ADDRESS))
      {
        checksum = 0;
        while(mPtr <= (uint8_t *) &eeMirror.vitals.checksum)
        {
          checksum += *mPtr;
          mPtr++;
        }

        if(checksum)
        {
          for(uint8_t i=0; i <= MAX_NUMBER_VITALS; i++)
          {
            eeMirror.vitals.vital[i].warning = MXGTW_VITAL_DEFAULT_WARNING[i];
            eeMirror.vitals.vital[i].shutdown = MXGTW_VITAL_DEFAULT_SHUTDOWN[i];
            eeMirror.vitals.vital[i].icon = MXGTW_VITAL_DEFAULT_ICON[i];
            eeMirror.vitals.vital[i].units = MXGTW_VITAL_DEFAULT_UNITS[i];
          }

          eeMirror.vitals.reserved[0] = 0xFF;
          eeMirror.vitals.reserved[1] = 0xFF;
          eeMirror.vitals.reserved[2] = 0xFF;

          mPtr = (uint8_t *) &eeMirror.vitals;
          checksum = 0;
          while(mPtr < (uint8_t *) &eeMirror.vitals.checksum)
          {
            checksum += *mPtr;
            mPtr++;
          }

          eeMirror.vitals.checksum = ~checksum + 1;

          mPtr = (uint8_t *) &eeMirror.vitals;

          eeTimeToUpdateMirror = TRUE;
        }

        eeState = EE_MIRROR_RESTORE_USER_LOG;
      }
    break;

    case EE_MIRROR_RESTORE_USER_LOG:
      mPtr = EE_MIRROR_VAR_POINTER(queueUserLog);
      eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(queueUserLog);

      if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.queueUserLog), EE_MIRROR_STOP_ADDRESS))
      {
        checksum = 0;

       while(mPtr <= (uint8_t *) &eeMirror.queueUserLog.checksum)
        {
          checksum += *mPtr;
          mPtr++;
        }

        if(checksum)
        {
          mPtr = (uint8_t *) &eeMirror.queueUserLog;

          while(mPtr <= (uint8_t *) &eeMirror.queueUserLog.checksum)
          {
            *mPtr = 0xA8;
            mPtr++;
          }

          eeMirror.queueUserLog.pointer = USER_LOG_QUEUE_SIZE - 1;
          eeTimeToUpdateMirror = TRUE;
        }

        if(eeMirror.queueUserLog.pointer >= USER_LOG_QUEUE_SIZE)
        {
          eeMirror.queueUserLog.pointer = USER_LOG_QUEUE_SIZE - 1;  // set for first increment to be to 0
        }

        eeState = EE_MIRROR_RESTORE_SOFTWARE_UPDATE;
      }
    break;

    case EE_MIRROR_RESTORE_SOFTWARE_UPDATE:
      mPtr = EE_MIRROR_VAR_POINTER(queueSwUpdate);
      eeDeviceAddress = EE_MIRROR_VAR_ADDRESS(queueSwUpdate);

      if(eeReadArray(eeDeviceAddress, mPtr, sizeof(eeMirror.queueSwUpdate), EE_MIRROR_STOP_ADDRESS))
      {
        checksum = 0;
        while(mPtr <= (uint8_t *) &eeMirror.queueSwUpdate.checksum)
        {
          checksum += *mPtr;
          mPtr++;
        }

        if(checksum)
        {
          mPtr = (uint8_t *) &eeMirror.queueSwUpdate;

          while(mPtr <= (uint8_t *) &eeMirror.queueSwUpdate.checksum)
          {
            *mPtr = 0xA9;
            mPtr++;
          }

          eeMirror.queueSwUpdate.pointer = SW_UPDATE_QUEUE_SIZE - 1;
          eeTimeToUpdateMirror = TRUE;
        }

        if(eeMirror.queueSwUpdate.pointer >= SW_UPDATE_QUEUE_SIZE)
        {
          eeMirror.queueSwUpdate.pointer = SW_UPDATE_QUEUE_SIZE - 1;  // set for first increment to be to 0
        }

        eeMode  = EE_IDLE;
        eeState = EE_IDLE;
        flag_InitEERead = TRUE;
        HW_DEBUG(("EEPROM Restore Complete"));
      }
    break;

    default:
      eeMode  = EE_IDLE;
      eeState = EE_IDLE;
    break;
  }
}

static uint8_t eeUpdateStatus(void)
//******************************************************************************
//    returns     :
//
//    Created By  : SLM
//    Date Created: 16 Jan, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  uint8_t returnStatus;
  uint32_t temp;
  uint16_t eeResult;

  returnStatus = EE_SUCCESSFUL;

  switch (eeState)
  {
    case EE_US_WRITE_INIT:
      eeWriteAttemptCounter = 0;          // clear write attempts at current device address
      eeState = EE_US_READ_COMPARE;
      // don't break, fall into next state

    case EE_US_READ_COMPARE:  // if data to be written is same as the value in the eeprom, skip it
      eeResult = hw_nvm_eeprom_read_uint32(E1, eeDeviceAddress, &temp);

      if (eeResult == NVM_OK)
      {
        // verify write data is different from eeprom data
        eeState = EE_US_COMPLETE;
        eeBusy = FALSE;
      }
      else
      {
        eeBusy = TRUE;
      }
    break;

    default:
      // Unknown eeState, exit state machine
      eeState = EE_US_COMPLETE;
      eeBusy = FALSE;
      returnStatus = EE_LOST_STATE;
  } // End of Switch statement

  return returnStatus;
}

void eeServiceEEPROM(void)
//******************************************************************************
//    returns     : Service EEPROM
//
//    Created By  : SLM
//    Date Created: 16 Jan, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  uint16_t i;

  //If the eeprom isn't writing, we can access it
  if(!hw_nvm_eeprom_write_pending() && (state_Engine != ENGINE_CRANKING))
  {
    switch(eeMode)
    {
      case EE_WRITE_STATUS:
        switch(eeState)
        {
          case EE_US_IDLE:
            eeState = EE_US_WRITE_INIT;
            eeBusy = TRUE;
          break;

          case EE_US_COMPLETE:
            eeMode = EE_HM_START;
            eeState = EE_HM_START;
          break;

          default:
          break;
        }

        if(eeBusy)
        {
          eeUpdateStatus();
        }
      break;

      case EE_HM_START:
        //Cycle through each set of hourmeters and find the valid banks in each.
        for (i = 0; i < EE_MAX_HOUR_METERS; i++)
        {
          eeFindHourMeterBank(&hourCounter[i], (uint8_t)i);

          if(hourCounter[i].pointer != INVALID)
          {
            // if valid data found
            if(actualHourMeter < hourCounter[i].value)
            {
              actualHourMeter = hourCounter[i].value;  // done
              actualHourMeterCopy = actualHourMeter;
            }
          }
          else
          {
            // no valid data found in block
            hourCounter[i].value = 0;
          }

          hourCounter[i].status = ENABLED;
          hourCounter[i].failures = 0;      // number of bank switches during run time
        }

        eeMode = EE_CLEAR_ALL_BLOCKS; // set mode to clear all hour meter locations except the valid banks found above
        eeState = EE_CLEAR_IDLE;
        currentHourMeter = 0; // begin clearing, hourmeter block 1 first
      break;

      case EE_CLEAR_ALL_BLOCKS:
        switch(eeState)
        {
          case EE_CLEAR_IDLE:;
            eeState = EE_CLEAR_WRITE_INIT;
            eeBusy = TRUE;
          break;

          case EE_CLEAR_COMPLETE:

            if(hourCounter[currentHourMeter].pointer == INVALID)
            {

              // if valid data was not found at init, set pointer to bank one
              hourCounter[currentHourMeter].pointer = EE_HOUR_METER_BLOCK_BEGIN[currentHourMeter];
            }

            if(++currentHourMeter >= EE_MAX_HOUR_METERS)
            {
              currentHourMeter = EE_MAX_HOUR_METERS - 1; // set to MAX index so on update hour meter 1 will be the first one stored to
              eeMode = EE_MIRROR_RESTORE;    // get ready to update hour meters, don't reset currentHour
              eeState = EE_MIRROR_RESTORE_VARIABLES;
            }
            else
            {
              eeState = EE_CLEAR_IDLE;
            }
          break;

          default:
          break;
        }

        if (eeBusy)
        {
          eeClearHourMeter(&hourCounter[currentHourMeter]);  // service state machine for current hour meter
        }
      break;

      case EE_CLEAR_BLOCK:
        if(eeBusy)
        {
          eeClearHourMeter(&hourCounter[currentHourMeter]);
        }

        if(eeState == EE_CLEAR_COMPLETE)
        {
          if(hourCounter[currentHourMeter].status == ENABLED)
          {
            eeState = EE_HM_WRITE_INIT;            // force write of current hour meter when clear block is complete
            eeMode = EE_HM_UPDATE;
            eeBusy = TRUE;
          }
          else
          {
            eeState = EE_HM_WRITE_INIT;            // force write of next hour meter when clear block is complete
            eeMode = EE_HM_UPDATE;
          }
        }
      break;

      case EE_HM_UPDATE:
        if(!eeBusy)
        {
          // only increment hour meter and set flag to update
          for(i = 0; i < EE_MAX_HOUR_METERS; i++)
          {
            if (++currentHourMeter >= EE_MAX_HOUR_METERS)
            {
              // change current hour meter to next enabled hour meter
              currentHourMeter = 0;
            }

            if (hourCounter[currentHourMeter].status == ENABLED)
            {
              break;
            }
          }

          if(i >= EE_MAX_HOUR_METERS)
          {
            eeMode = EE_NO_ENABLED_HOUR_METERS;
          }

          if((hourCounter[currentHourMeter].pointer < EE_HOUR_METER_BLOCK_BEGIN[currentHourMeter]) ||
             (hourCounter[currentHourMeter].pointer >= EE_HOUR_METER_BLOCK_END[currentHourMeter]))
          {
            hourCounter[currentHourMeter].pointer = EE_HOUR_METER_BLOCK_BEGIN[currentHourMeter]; // save the pointer to use after clear is complete
            hourCounter[currentHourMeter].failures = 0;
            hourCounter[currentHourMeter].status = ENABLED;   // out of bounds pointer reset stucture
          }
          else
          {

            if(actualHourMeter == actualHourMeterCopy)
            {
              // make sure RAM did not get corrupted
              hourCounter[currentHourMeter].value = actualHourMeter;  // update RAM structure value with new hourmeter value
            }
            else
            {
              // corrupted RAM
              if(currentHourMeter)
              {
                if(hourCounter[currentHourMeter].value < hourCounter[currentHourMeter-1].value)
                {
                  // update RAM structure value with old hourmeter value
                  hourCounter[currentHourMeter].value = hourCounter[currentHourMeter-1].value;
                }

                actualHourMeter = hourCounter[currentHourMeter].value;  // restore RAM  variable - done
                actualHourMeterCopy = actualHourMeter;                  // save Copy
              }
              else
              {
                // current hour meter is 0
                if (hourCounter[currentHourMeter].value < hourCounter[EE_MAX_HOUR_METERS-1].value)
                {
                  // update RAM structure value with old hourmeter value
                  hourCounter[currentHourMeter].value = hourCounter[EE_MAX_HOUR_METERS-1].value;
                }

                actualHourMeter = hourCounter[currentHourMeter].value;  // restore RAM  variable - done
                actualHourMeterCopy = actualHourMeter;  // save Copy
              }
            }

            eeState = EE_HM_WRITE_INIT;           // init state machine variables for next eeprom write
            eeBusy = TRUE;
          }
        }

        if(eeBusy)
        {
          if(eeUpdateHourMeter(&hourCounter[currentHourMeter]) == EE_WRITE_FAILURE)
          {
            hourCounter[currentHourMeter].pointer += (EE_HOUR_METER_BANK_SIZE*4); // if write failed goto next bank

            if(hourCounter[currentHourMeter].pointer >= EE_HOUR_METER_BLOCK_END[currentHourMeter])
            {
              hourCounter[currentHourMeter].pointer = EE_HOUR_METER_BLOCK_BEGIN[currentHourMeter];                   // save the pointer to use after clear is complete
            }

            if(++hourCounter[currentHourMeter].failures >= EE_BANKS_PER_HOUR_METER)
            {
              hourCounter[currentHourMeter].status = DISABLED; // only allow 4 failures per block (one failure per bank
              hourCounter[currentHourMeter].pointer = EE_HOUR_METER_BLOCK_END[currentHourMeter]; // set to end of block + 1
            }

            eeMode = EE_CLEAR_BLOCK;     // set to clear out entire block
            eeState = EE_CLEAR_WRITE_INIT;
            eeBusy = TRUE;
          }
        }
      break;

      case EE_NO_ENABLED_HOUR_METERS:
      break;

      case EE_ROLL_OVER_HOUR_METERS: // set all data to 0xFF
        switch (eeState)
        {
          case EE_CLEAR_IDLE:
            eeState = EE_CLEAR_WRITE_INIT;
            eeBusy = TRUE;
          break;

          case EE_CLEAR_COMPLETE:
            if (hourCounter[currentHourMeter].pointer == INVALID)
            {
              // if valid data was not found at init, set pointer to bank one
              hourCounter[currentHourMeter].pointer = EE_HOUR_METER_BLOCK_BEGIN[currentHourMeter];
            }

            if (++currentHourMeter >= EE_MAX_HOUR_METERS)
            {
              currentHourMeter = EE_MAX_HOUR_METERS - 1; // set to MAX index so on update hour meter 1 will be the first one stored to
              eeMode = EE_IDLE;
              eeState = EE_IDLE;
            }
            else
            {
              // clear the next hour meter
              eeState = EE_CLEAR_IDLE;
            }
          break;

          default:
          break;
        }

        if (eeBusy)
        {
          eeClearHourMeter(&hourCounter[currentHourMeter]);  // service state machine for current hour meter
        }
      break;

      //EE MIRROR RESTORE
      case EE_MIRROR_RESTORE:
          eeRestoreMirror();
      break;

      //EE MIRROR UPDATE
      case EE_MIRROR_UPDATE:
        eeUpdateMirrorEvents();
      break;

      default:
        eeMode = EE_IDLE;
        eeState = EE_IDLE;
      break;
    }
  }
}

void UpdateEvent(uint8_t location)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 29 Mar, 2006
//    Description : Adds event to EEPROM
//    Notes       :
//******************************************************************************
{
  uint8_t  * eventPtr;
  uint8_t  checksum;
  uint16_t tempDuration;

  if(location < NUMBER_OF_EVENTS)
  {
    if(eventState[location] == NEW_EVENT)
    {
      for(eventPtr = (uint8_t *) &eeMirror.event[location], checksum = 0;
          eventPtr <= (uint8_t *) &eeMirror.event[location].checksum; eventPtr++)
      {
        checksum += *eventPtr; // verify checksum
      }

      if(checksum)
      {
        // checksum failed, clear out occurances
        eeMirror.event[location].occurances = 0;
      }

      eeMirror.event[location].time = (uint16_t)(actualHourMeter/HOUR_METER_TO_HOUR_FCT); // store hour last event started
      eventStartTime[location] = actualHourMeter;
      eeMirror.event[location].duration = 0;

      if(++eeMirror.event[location].occurances == 0)
      {
        // rail occurances at MAX_BYTE
        eeMirror.event[location].occurances = MAX_BYTE;
      }

      // QueueEventDialog? was in previous code

      for (eventPtr = (uint8_t *) &eeMirror.event[location], eeMirror.event[location].checksum = 0;
           eventPtr < (uint8_t *) &eeMirror.event[location].checksum; eventPtr++)
      {
        eeMirror.event[location].checksum += *eventPtr;                      // calc the new checksum
      }

      eeMirror.event[location].checksum = ~eeMirror.event[location].checksum + 1;
      eeTimeToUpdateMirror = 1;
      eventState[location] = CONTINUING_EVENT;
    }
    else if (eventState[location] == CONTINUING_EVENT)
    {
      // if the event is still active
      tempDuration = eeMirror.event[location].duration;
      eeMirror.event[location].duration = (uint16_t)((actualHourMeter - eventStartTime[location])/HOUR_METER_TO_MINUTE_FCT);

      if (tempDuration != eeMirror.event[location].duration)
      {
        // calc duration of event (minutes)
        if (tempDuration > eeMirror.event[location].duration)
        {
          eeMirror.event[location].duration = MAX_WORD;
        }

        for (eventPtr = (uint8_t *) &eeMirror.event[location], eeMirror.event[location].checksum = 0;
             eventPtr < (uint8_t *) &eeMirror.event[location].checksum; eventPtr++)
        {
          eeMirror.event[location].checksum += *eventPtr;                // calc checksum
        }

        eeMirror.event[location].checksum = ~eeMirror.event[location].checksum + 1;
        eeTimeToUpdateMirror = 1;                                        // set flag to store into eeprom device
      }
    }
  }
}

void QueueEventDiag(uint8_t controller, uint8_t function, uint8_t failure, uint8_t user, uint32_t time)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 7 Feb, 2006
//    Description : Adds error code to queue to get stored in EEPROM.
//    Notes       : May need to add a feature where it ignores tenths of hours.
//******************************************************************************
{
  uint8_t eventDiff;
  uint8_t * bytePtr;
  eventDiagRec * queuePtr;

  // swap bytes for correct storage
  // function = (((function & 0x00FF) << 8) | ((function & 0xFF00) >> 8));

  queuePtr = (eventDiagRec *) &eeMirror.queue.eventDiag + eeMirror.queue.pointer;

  eventDiff = TRUE;

  // Look to see if code is logged already
  if((function == FN_MAIN_CONTROLLER) && (failure == SOFTWARE_UPDATED))
  {
  }
  else
  {
    for(int i=0; i < EVENT_DIAG_QUEUE_SIZE; i++)
    {
      if(((eeMirror.queue.eventDiag[i].time) == (time)) &&
         (eeMirror.queue.eventDiag[i].function == function) &&
         (eeMirror.queue.eventDiag[i].failure == failure))
      {
        eventDiff = FALSE;
        break;
      }
    }
  }

  // only log a new or different event/diag
  if(eventDiff)
  {
    // circular queue implemented
    if(++eeMirror.queue.pointer >= EVENT_DIAG_QUEUE_SIZE)
    {
      eeMirror.queue.pointer = 0;
    }

    // re-initialize the pointers
    queuePtr = (eventDiagRec *) &eeMirror.queue.eventDiag + eeMirror.queue.pointer;

    queuePtr->controller = controller;
    queuePtr->function   = function;
    queuePtr->failure    = failure;
    queuePtr->userID     = user;
    queuePtr->time       = time;

    eeMirror.queue.checksum = 0;

    bytePtr = (uint8_t *) &eeMirror.queue.eventDiag;

    for(; bytePtr < (uint8_t *) &eeMirror.queue.checksum; bytePtr++)
    {
      eeMirror.queue.checksum += *bytePtr;
    }

    eeMirror.queue.checksum = ~eeMirror.queue.checksum + 1;

    eeTimeToUpdateMirror = TRUE;
  }
}

#ifdef HCS12_BSP_EMU //if M4 compile this
void QueueEventDiagECU(uint8_t controller, uint32_t function, uint8_t failure, uint8_t user, uint32_t time)
//******************************************************************************
//    returns     : NONE.
//
//		Created By  : Boston Zachmann
//    Date Created: 10 June, 2016
//    Description : Adds error code to ECU queue to get stored in EEPROM.
//    Notes       : 
//****************************************************************************** 
{
  uint8_t eventDiff;
  uint8_t * bytePtr;
  eventDiagRecSPN * queuePtr;
  
  queuePtr = (eventDiagRecSPN *) &eeMirror.queueECU.eventDiag + eeMirror.queueECU.pointer;

  eventDiff = TRUE;
  
  // Look to see if code is logged already

  for(int i=0; i < EVENT_DIAG_QUEUE_SIZE; i++)
  {
    if(((eeMirror.queueECU.eventDiag[i].time) == (time)) &&
       (eeMirror.queueECU.eventDiag[i].function == function) &&
       (eeMirror.queueECU.eventDiag[i].failure == failure))
    {
      eventDiff = FALSE;
      break;
    }
  }

  
  // only log a new or different event/diag   
  if(eventDiff)
  {
    // circular queue implemented 
    if(++eeMirror.queueECU.pointer >= EVENT_DIAG_QUEUE_SIZE)
    {
      eeMirror.queueECU.pointer = 0;
    }

    // re-initialize the pointers
    queuePtr = (eventDiagRecSPN *) &eeMirror.queueECU.eventDiag + eeMirror.queueECU.pointer;
   
    queuePtr->controller = controller;
    queuePtr->function   = function;
    queuePtr->failure    = failure;
    queuePtr->userID     = user;
    queuePtr->time       = time;
		  
    eeMirror.queueECU.checksum = 0;
  
    bytePtr = (uint8_t *) &eeMirror.queueECU.eventDiag;
    
    for(; bytePtr < (uint8_t *) &eeMirror.queueECU.checksum; bytePtr++)
    {
      eeMirror.queueECU.checksum += *bytePtr;
    }
  
    eeMirror.queueECU.checksum = ~eeMirror.queueECU.checksum + 1;

    eeTimeToUpdateMirror = TRUE;
  }
}
#endif

void QueueServiceDiag(uint16_t clkReset, uint16_t clkLength, uint8_t howReset, uint8_t serviceReq, uint8_t userID)
/*************************************************************************
*    returns    : NONE.
*    reset      : Time at which the service clock was reset.
*    length     : Amount of time the clock was suppose to run for.
*
*  Created By   : Spencer Mindeman
*  Date Created : 28 May, 2004
*  Description  : Places the time and length of timer into the service queue
*                 to keep track of when the clock was reset.
*  Notes        :
*************************************************************************/
{
  uint8_t * bytePtr;
  serviceDiagRec * queuePtr;

  // circular queue implemented
  if (++eeMirror.queueService.pointer >= NUMBER_SERVICE_CLOCK_EVENTS)
  {
    eeMirror.queueService.pointer = 0;
  }// end if

  queuePtr = (serviceDiagRec *) &eeMirror.queueService.serviceDiag + eeMirror.queueService.pointer;

  queuePtr->clockReset  = clkReset;
  queuePtr->clockLength = clkLength;
  queuePtr->howReset = howReset;
  queuePtr->typeOfService = serviceReq;
  queuePtr->userID = userID;

  // Calculate checksum
  eeMirror.queueService.checksum = 0;

  bytePtr = (uint8_t *) &eeMirror.queueService.serviceDiag;

  for (; bytePtr < (uint8_t *) &eeMirror.queueService.checksum; bytePtr++)
  {
    eeMirror.queueService.checksum += *bytePtr;
  }// end for

  eeMirror.queueService.checksum = ~eeMirror.queueService.checksum + 1;

  eeTimeToUpdateMirror = TRUE;
}

void QueueCurrentUser(uint8_t user, uint16_t hour)
/*************************************************************************
*    returns    : NONE.
*    user       : current user logged in.
*    hour       : Hour they logged in at.
*
*  Created By   : Spencer Mindeman
*  Date Created : 13 Nov, 2008
*  Description  : Places the user and hour the user logged into the machine
*                 to keep track of when the last user to use the machine.
*  Notes        :
*************************************************************************/
{
  uint8_t * bytePtr;
  userLogRec * queuePtr;

  // circular queue implemented
  if (++eeMirror.queueUserLog.pointer >= USER_LOG_QUEUE_SIZE)
  {
    eeMirror.queueUserLog.pointer = 0;
  }// end if

  queuePtr = (userLogRec *) &eeMirror.queueUserLog.userLog + eeMirror.queueUserLog.pointer;

  queuePtr->user  = user;
  queuePtr->hour  = hour;

  // Calculate checksum
  eeMirror.queueUserLog.checksum = 0;

  bytePtr = (uint8_t *) &eeMirror.queueUserLog.userLog;

  for (; bytePtr < (uint8_t *) &eeMirror.queueUserLog.checksum; bytePtr++)
  {
    eeMirror.queueUserLog.checksum += *bytePtr;
  }// end for

  eeMirror.queueUserLog.checksum = ~eeMirror.queueUserLog.checksum + 1;

  eeTimeToUpdateMirror = TRUE;
}

void QueueSoftwareUpdate(uint8_t ap_new_type, uint16_t ap_new_version, uint16_t cd_new_version, uint16_t hour)
/*************************************************************************
*    returns    : NONE.
*    old_version: version prior to update.
*    new_version: version after update.
*
*  Created By   : Spencer Mindeman
*  Date Created : 13 Nov, 2008
*  Description  : Place updates on queue to keep track of when software was updated.
*  Notes        :
*************************************************************************/
{
  uint8_t * bytePtr;
  swUpdateRec * queuePtr;

  // circular queue implemented
  if (++eeMirror.queueSwUpdate.pointer >= SW_UPDATE_QUEUE_SIZE)
  {
    eeMirror.queueSwUpdate.pointer = 0;
  }// end if

  queuePtr = (swUpdateRec *) &eeMirror.queueSwUpdate.swUpdateLog + eeMirror.queueSwUpdate.pointer;

  //do not record old versio as we know what is from the previous version that was programmed.
  //queuePtr->app_old_version  = app_old_version;
  queuePtr->ap_new_type     = ap_new_type;
  queuePtr->ap_new_version  = ap_new_version;
  //queuePtr->cd_old_version   = cd_old_version;
  queuePtr->cd_new_version   = cd_new_version;
  queuePtr->hour  = hour;

  // Calculate checksum
  eeMirror.queueSwUpdate.checksum = 0;

  bytePtr = (uint8_t *) &eeMirror.queueSwUpdate.swUpdateLog;

  for (; bytePtr < (uint8_t *) &eeMirror.queueSwUpdate.checksum; bytePtr++)
  {
    eeMirror.queueSwUpdate.checksum += *bytePtr;
  }// end for

  eeMirror.queueSwUpdate.checksum = ~eeMirror.queueSwUpdate.checksum + 1;

  eeTimeToUpdateMirror = TRUE;
}


