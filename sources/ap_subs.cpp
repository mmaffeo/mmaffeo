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
* General subroutines.
***************************************************************/

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "ap_subs.h"
#include "global.h"
#include "hw_io.h"
#include "nvm_ecuid.h"
#include "ap_can.h"
#include "ap_dv.h"
#include "ap_bservice_CAN04.h"
#include "ap_MXGWcontrol_defs.h"
#include "cdata.h"
#include "defines.h"

#include "ap_eeprom.h"
#include "ap_deluxeG5.h"

#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"
#include "rtwtypes.h"

#include "stdlib.h"

//******************************************************************************
// DEFINES
//******************************************************************************

//******************************************************************************
// STRUCTURES
//******************************************************************************

//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************

uint8_t  hourMeterUpdateTimer;
uint8_t jobClockUpdateTimer;
uint8_t jobClockLHPUpdateTimer[2];
uint8_t idleClockUpdateTimer;
uint8_t sendFirstJobClockCmd;

uint8_t  currentHourMeter;
uint32_t actualHourMeterCopy;
//uint32_t actualHourMeter;
uint8_t flag_HourOverflow;

uint32_t eeUpdate;

uint16_t gwServiceTimer;

uint8_t status_SrvcClockDisplay;


//******************************************************************************
// FUNCTIONS
//******************************************************************************

static int8_t str_len(const uint8_t *s_ptr, const uint8_t max_length)
//******************************************************************************
//    returns     : Returns length of the string.  Returns -1 if there was an error.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Determines the lenght of the string.
//    Notes       :
//******************************************************************************
{
  int8_t i;

  i = 0;
  while ((*(s_ptr + i) != '\0') && (i <= max_length))
  {
    // search for null or max length
    i++;
  }

  if (i > max_length)
  {
    return(-1);    // If > than max length ERROR condition
  }
  else
  {
    return(i);
  }
}

void left_pad_str(uint8_t *str, int len, char pad, const uint8_t max_length)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Passed string is shifted to the right to accomadate padding
//                  which is added at the left. String needs to be at least
//                  len + 1 bytes long.
//    Notes       :
//******************************************************************************
{
  int8_t initLen, i, shift;

  if (str_len(str, max_length) >= 0)
  {
    initLen = str_len(str, max_length);

    if (initLen > len)
    {
      return;
    }

    shift = len - initLen;
    for(i = initLen; i >= 0; i--)
    {
      // shift all bytes to the right including
      str[i + shift] = str[i]; // the NULL character
    }

    len -= initLen;

    for(i = 0; i < len; i++)
    {
      // Add the pad character at the left
      str[i] = pad;
    }
  }
}

uint8_t number_to_str(uint32_t value, uint8_t * buffer, uint8_t buffer_length)
//******************************************************************************
//    returns     : uint8_t containing the string length.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Takes the numeric value passed it and converts it to the
//                  ASCII decimal equivalent and stores it into the buffer.
//    Notes       :
//******************************************************************************
{
  uint8_t string_length;
  uint32_t i, seed;
  char digit;

  // to prevent buffer overflow conditions
  if(buffer_length > MAX_STRING_LENGTH)
  {
    buffer_length = MAX_STRING_LENGTH;
  }

  //To speed things up, find the correct starting value

  if(value < 10)
  {
    seed = 1;
  }
  else if(value < 100)
  {
    seed = 10;
  }
  else if(value < 1000)
  {
    seed = 100;
  }
  else if(value < 10000)
  {
    seed = 1000;
  }
  else if(value < 100000)
  {
    seed = 10000;
  }
  else if(value < 1000000)
  {
    seed = 100000;
  }
  else if(value < 10000000)
  {
    seed = 1000000;
  }
  else if(value < 100000000)
  {
    seed = 10000000;
  }
  else if(value < 1000000000)
  {
    seed = 100000000;
  }
  else
  {
    seed = 1000000000; // This implies that the max string length is 10.  The buffer will hold 10 plus NULL character
  }

  // Calculate the correct digit values
  string_length = 0;
  for(i = seed; i > 0; i /= 10)
  {
    // if the present value >= seed value
    if(value >= i)
    {
      // digit = interger dividend + ASCII zero
      digit = value / i + '0';

      // value now = remainder
      value %= i;
    }
    else
    {
      // present value < seed so don't divide
      // set digit to zero
      digit = '0';
    }

    buffer[string_length++] = digit;  // Add digit to string
  }

  buffer[string_length] = '\0';    // terminate the string

  return string_length;       // return string l
}

void UpdateHourMeter(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 23 Jan, 2006
//    Description : Updates hourmeter.
//    Notes       :
//******************************************************************************
{
  if(state_Engine == ENGINE_RUNNING)
  {
    actualHourMeterCopy++;

    if(++actualHourMeter >= MAX_HOUR_METER_VALUE)
    {
      if(eeMode == EE_IDLE)
      {
        // If EEPROM is not busy update hourmeters.
        eeMode = EE_ROLL_OVER_HOUR_METERS;
        eeState = EE_CLEAR_IDLE;

        actualHourMeter = 0;
        actualHourMeterCopy = 0;
        flag_HourOverflow = 1;

        // Set pointers to clear out all banks
        hourCounter[0].pointer = INVALID;
        hourCounter[1].pointer = INVALID;
        hourCounter[2].pointer = INVALID;

        // Clear all hour meteres (must start at 0)
        currentHourMeter = 0;
      }
    }

    else if(hourMeterUpdateTimer)
    {
      hourMeterUpdateTimer--;  // 6 minute timer to update EEPROM hourmeter.
    }
  }
}

void UpdateUserJobClock(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 18 Feb 2009
//    Description : Updates user job clock.
//    Notes       :
//******************************************************************************
{
  uint32_t time;
  uint8_t  userID;

  userID = current_user;

  //If user is logged in and the engine is running log hours.
  if((userID != 0xFF) && (state_Engine == ENGINE_RUNNING))
  {
    //eeMirror.userInfo[userID].jobClock++;
    time = GetUserJob(userID);
    time++;

    SetUserJob(userID,time);

    //time = eeMirror.userInfo[userID].jobClock/HOUR_METER_TO_MINUTE_FCT;

    time = time/HOUR_METER_TO_MINUTE_FCT;

    if(time >= MAX_JOB_CLOCK)
    {
      SetUserJob(userID,0);
      eeTimeToUpdateMirror = TRUE;
    }
    else if(jobClockUpdateTimer)
    {
      jobClockUpdateTimer--;
    }

    // Update user fuel consumption
   if((start_FuelConsumption < can_FuelConsumption) && (CONSTANT_DATA->ECU_FUNCTION != NON_FUNCTIONAL))
    {
      current_FuelConsumption = (uint16_t)((can_FuelConsumption - start_FuelConsumption) + eeMirror.userInfo[current_user].fuelConsumption);

      eeMirror.userInfo[current_user].fuelConsumption = current_FuelConsumption;

      start_FuelConsumption = can_FuelConsumption;
    }

    //Calculate new checksum for user based on updated job clock
    uint8_t * bytePtr;

    eeMirror.userInfo[userID].checksum = 0;

    bytePtr = (uint8_t *) &eeMirror.userInfo[userID].locks;

    for (; bytePtr < (uint8_t *) &eeMirror.userInfo[userID].checksum; bytePtr++)
    {
      eeMirror.userInfo[userID].checksum += *bytePtr;
    }// end for

    eeMirror.userInfo[userID].checksum = ~eeMirror.userInfo[userID].checksum + 1;

  }

  //Check main job clock to see if it goes over

  time = (actualHourMeter - eeMirror.jobClock)/HOUR_METER_TO_MINUTE_FCT;

  if (time >= MAX_JOB_CLOCK)
  {
    // roll over to 0
    eeMirror.jobClock = actualHourMeter;    // reset jobClock time
    UpdateEEVariables(NOW);                 // store only on clear
  }
}

void UpdateLHPJobClocks(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 05 Dec 2011
//    Description : Updates LHP Job Clocks.
//    Notes       :
//******************************************************************************
{
  //If the engine is running log hours.
  if(state_Engine == ENGINE_RUNNING)
  {
    for(uint8_t i=0; i<2; i++)
    {
      eeMirror.jobClockLHP[i]++;

      if(eeMirror.jobClockLHP[i] >= 3600000) //3600000 Five second counts = 10,000 hours
      {
        eeMirror.jobClockLHP[i] = 0;
      }
      else if(jobClockLHPUpdateTimer[i])
      {
        jobClockLHPUpdateTimer[i]--;
      }
    }
    UpdateEEVariables(LATER);
  }
}


void UpdateIdleTime(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Updates LCD Hourmeter.
//    Notes       :
//******************************************************************************
{
  uint32_t time;
  uint8_t  userID;

  userID = current_user;

  //If user is logged in and machine is in idle log hours.
  if((state_Idle == ACTIVE) && (state_System == SYS_NORMAL))
  {
    if(userID != 0xFF)
    {
      time = GetUserIdle(userID);
      time++;

      SetUserIdle(userID,time);

      time = time/HOUR_METER_TO_MINUTE_FCT;

      if(time >= MAX_JOB_CLOCK)
      {
        SetUserIdle(userID,0);
        eeTimeToUpdateMirror = TRUE;
      }
      else if(idleClockUpdateTimer)
      {
        idleClockUpdateTimer--;
      }

      //Calculate new checksum for user based on updated job clock
      uint8_t * bytePtr;

      eeMirror.userInfo[userID].checksum = 0;

      bytePtr = (uint8_t *) &eeMirror.userInfo[userID].locks;

      for (; bytePtr < (uint8_t *) &eeMirror.userInfo[userID].checksum; bytePtr++)
      {
        eeMirror.userInfo[userID].checksum += *bytePtr;
      }// end for

      eeMirror.userInfo[userID].checksum = ~eeMirror.userInfo[userID].checksum + 1;
    }

    eeMirror.machineIdleTime++;
    //UpdateEEVariables(LATER);

  }

  //Roll over machine idle time
  if(eeMirror.machineIdleTime >= MAX_JOB_CLOCK)
  {
    eeMirror.machineIdleTime = 0;
    //UpdateEEVariables(0);
  }
}

void UpdateLCDHourMeter(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Updates LCD Hourmeter.
//    Notes       :
//******************************************************************************
{
  uint8_t number_str[MAX_STRING_BUFF_LENGTH];

  number_to_str(actualHourMeter/HOUR_METER_FCT, &(number_str[0]), (uint8_t)MAX_STRING_LENGTH);
  left_pad_str(number_str,5,' ',(uint8_t)MAX_STRING_LENGTH);

  if(actualHourMeter < HOUR_METER_TO_HOUR_FCT)
  {
    number_str[3] = '0'; //format 0.0
  }

  LCD[0] = number_str[0];
  LCD[1] = number_str[1];
  LCD[2] = number_str[2];
  LCD[3] = number_str[3];
  LCD[4] = number_str[4];

  LCD[5] = 0x20;
  LCD[6] = 0x01; // Turn radix on
}

void UpdateLCDJobClock(uint8_t clock)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Updates LCD Job Clocks.
//    Notes       :
//******************************************************************************
{
  uint8_t number_str[MAX_STRING_BUFF_LENGTH];

  number_to_str(eeMirror.jobClockLHP[clock]/HOUR_METER_FCT, &(number_str[0]), (uint8_t)MAX_STRING_LENGTH);
  left_pad_str(number_str,5,' ',(uint8_t)MAX_STRING_LENGTH);

  if(eeMirror.jobClockLHP[clock] < HOUR_METER_TO_HOUR_FCT)
  {
    number_str[3] = '0'; //format 0.0
  }

  LCD[0] = number_str[0];
  LCD[1] = number_str[1];
  LCD[2] = number_str[2];
  LCD[3] = number_str[3];
  LCD[4] = number_str[4];

  LCD[5] = 0x20;
  LCD[6] = 0x01; // Turn radix on
}

void UpdateLCDGlowPlugs(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Updates glow plug counter.
//    Notes       :
//******************************************************************************
{
  uint8_t number_str[MAX_STRING_BUFF_LENGTH];

  number_to_str(count_GlowPlug/10, &(number_str[0]), (uint8_t)MAX_STRING_LENGTH);
  left_pad_str(number_str,2,'0', (uint8_t)MAX_STRING_LENGTH);

  LCD[0] = ' ';
  LCD[1] = ' ';
  LCD[2] = ' ';
  LCD[3] = number_str[0];
  LCD[4] = number_str[1];

  LCD[5] = 0x20;
}

void UpdateLCDEngineRPM(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Converts engine speed to usable form for LCD.
//    Notes       :
//******************************************************************************
{
  uint8_t number_str[MAX_STRING_BUFF_LENGTH];
  uint16_t newRPM;

  if(flt_EngineSpeed > 0)
  {
    if(CONSTANT_DATA->DELUXE_GEN5_FUNCTION == NON_FUNCTIONAL)
    {
      number_to_str(flt_EngineSpeed, &(number_str[0]),(uint8_t)MAX_STRING_LENGTH);
    }
    else
    {
      newRPM = (flt_EngineSpeed + 5)/10*10;
      number_to_str(newRPM, &(number_str[0]),(uint8_t)MAX_STRING_LENGTH);
    }


    left_pad_str(number_str,4,' ', (uint8_t)MAX_STRING_LENGTH);

    LCD[1] = number_str[0];
    LCD[2] = number_str[1];
    LCD[3] = number_str[2];
    LCD[4] = 0x30;
  }
  else
  {
    LCD[4] = 0x30;
    LCD[3] = 0x20;
    LCD[2] = 0x20;
    LCD[1] = 0x20;
  }

  LCD[0] = 0x20;
  LCD[5] = 0x20;
}

void UpdateLCDBatteryVoltage(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Converts battery voltage to a usable form for LCD.
//    Notes       :
//******************************************************************************
{
  uint8_t number_str[MAX_STRING_BUFF_LENGTH];

  number_to_str(((calcFlt_VBattery * 10) >> 8), &(number_str[0]),(uint8_t)MAX_STRING_LENGTH);
  left_pad_str(number_str,3,' ', (uint8_t)MAX_STRING_LENGTH);

  LCD[0] = 0x20;
  LCD[1] = 0x20;
  LCD[2] = number_str[0];
  LCD[3] = number_str[1];
  LCD[4] = number_str[2];
  LCD[5] = 0x20;
  LCD[6] = 0x01;
}

void UpdateLCDEOP(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 14 May, 2010
//    Description : Converts engine oil pressure to a usable form for LCD.
//    Notes       :
//******************************************************************************
{
  uint8_t number_str[MAX_STRING_BUFF_LENGTH];

  number_to_str(flt_EOP, &(number_str[0]),(uint8_t)MAX_STRING_LENGTH);
  left_pad_str(number_str,3,' ', (uint8_t)MAX_STRING_LENGTH);

  LCD[0] = 0x45;
  LCD[1] = number_str[0];
  LCD[2] = number_str[1];
  LCD[3] = number_str[2];
  LCD[4] = 0x50;
  LCD[5] = 0xFF;
  LCD[6] = 0x01;
}

void UpdateLCDECT(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 14 May, 2010
//    Description : Converts engine coolant temperature to a usable form for LCD.
//    Notes       :
//******************************************************************************
{
  uint8_t number_str[MAX_STRING_BUFF_LENGTH];
  uint16_t tmp_ECT;

  if(flt_ECT >= 40)
  {
    tmp_ECT = flt_ECT - 40;
    number_to_str(tmp_ECT, &(number_str[0]),(uint8_t)MAX_STRING_LENGTH);
    left_pad_str(number_str,3,' ', (uint8_t)MAX_STRING_LENGTH);
    LCD[1] = number_str[0];
  }
  else
  {
    tmp_ECT = 40 - flt_ECT;

    number_to_str(tmp_ECT, &(number_str[0]),(uint8_t)MAX_STRING_LENGTH);
    left_pad_str(number_str,3,' ', (uint8_t)MAX_STRING_LENGTH);
    LCD[1] = '-';
  }

  LCD[0] = 0x45;
  LCD[2] = number_str[1];
  LCD[3] = number_str[2];
  LCD[4] = 0x46;
  LCD[5] = 0x20;
}

void UpdateLCDHOT(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 14 May, 2010
//    Description : Converts hydraulic oil temperature to a usable form for LCD.
//    Notes       :
//******************************************************************************
{
  uint8_t number_str[MAX_STRING_BUFF_LENGTH];
  uint16_t tmp_HOT;

  if(flt_HOT >= 40)
  {
    tmp_HOT = flt_HOT - 40;

    number_to_str(tmp_HOT, &(number_str[0]),(uint8_t)MAX_STRING_LENGTH);
    left_pad_str(number_str,3,' ', (uint8_t)MAX_STRING_LENGTH);
    LCD[1] = number_str[0];
  }
  else
  {
    tmp_HOT = 40 - flt_HOT;

    number_to_str(tmp_HOT, &(number_str[0]),(uint8_t)MAX_STRING_LENGTH);
    left_pad_str(number_str,3,' ', (uint8_t)MAX_STRING_LENGTH);
    LCD[1] = '-';
  }

  LCD[0] = 0x48;
  LCD[2] = number_str[1];
  LCD[3] = number_str[2];
  LCD[4] = 0x46;
  LCD[5] = 0x20;
}


void UpdateLCDServiceClock(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Converts Error Codes.
//    Notes       :
//******************************************************************************
{
  uint8_t  number_str[MAX_STRING_BUFF_LENGTH];
  uint32_t displayTime;
  uint8_t  overTime;

  if(actualHourMeter < eeMirror.serviceClockResetTime)
  {
    displayTime = 0;
  }
  else
  {
    displayTime = actualHourMeter - eeMirror.serviceClockResetTime;
  }

  if(displayTime > eeMirror.serviceClockLength)
  {
    displayTime = displayTime - eeMirror.serviceClockLength;
    overTime = TRUE;
  }
  else
  {
    displayTime = eeMirror.serviceClockLength - displayTime;
    overTime = FALSE;
  }

  number_to_str(displayTime/HOUR_METER_FCT, &(number_str[0]), (uint8_t)MAX_STRING_LENGTH);
  left_pad_str(number_str,5,' ',(uint8_t)MAX_STRING_LENGTH);

  if(displayTime < HOUR_METER_TO_HOUR_FCT)
  {
    number_str[3] = '0';   /* format 0.0 */
  }


  if(eeMirror.serviceClockLock & SERVICE_CLOCK_LOCK_BIT)
  {
    if(overTime)
    {
      LCD[0] = '-';
    }
    else
    {
      LCD[0] = ' ';
    }

    LCD[1] = number_str[1];
    LCD[2] = number_str[2];
    LCD[3] = number_str[3];
    LCD[4] = number_str[4];
    LCD[5] = 0x20;
    LCD[6] = 0x01;
  }
  else
  {
    LCD[0] = ' ';
    LCD[1] = ' ';
    LCD[2] = 'O';
    LCD[3] = 'F';
    LCD[4] = 'F';
    LCD[5] = 0x20;
    //LCD[6] = 0x00;
  }

  if(((gwServiceTimer-- == 0) || (status_SrvcClockDisplay == 0))&& (state_InfoSecondary == DISPLAY_SERVICE_CLOCK_ALARM))
  {
    gwServiceTimer = SERVICE_TIME_DISPLAY;
    status_SrvcClockDisplay = !status_SrvcClockDisplay;
  }
}

void UpdateServiceClock(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 4 Apr, 2006
//    Description : Update service clock timer.
//    Notes       :
//******************************************************************************

{
  uint32_t timer = 0;

  // If service clock function is active
  if(eeMirror.serviceClockLock & SERVICE_CLOCK_LOCK_BIT)
  {
    // If time has expired check the message timer.
    if(eeMirror.serviceClockExpired)
    {
      // Display message for specified time.
      // Do not run timer if glow plugs, door, or codes is active.
      if((state_InfoSecondary != DISPLAY_GLOW_PLUGS) && (state_InfoSecondary != DISPLAY_ERROR_CODES))
      {
        state_ServiceClock = ACTIVE;
      }
    }
    // If timer has not expired
    else
    {
      // Check the time
      timer = (actualHourMeter - (eeMirror.serviceClockResetTime - (10*720)));

      // If timer has expired
      if((timer > eeMirror.serviceClockLength) && (!eeMirror.serviceClockExpired))
      {
        eeMirror.serviceClockExpired = TRUE;
        state_ServiceClock = ACTIVE;

        UpdateEEVariables(NOW);
      }
    }
  }
}

void UpdateLCDServiceAlarm(void)
/*************************************************************************
*    returns    : NONE.
*
*  Created By   : Spencer Mindeman
*  Date Created : 04 April, 2006
*  Description  : Display LCD info for the service clock.
*  Notes        :
*************************************************************************/
{
  uint8_t number_str[MAX_STRING_BUFF_LENGTH];

  if(gwServiceTimer-- == 0)
  {
    gwServiceTimer = SERVICE_TIME_DISPLAY;
    status_SrvcClockDisplay = !status_SrvcClockDisplay;
  }

  if(status_SrvcClockDisplay == 0)
  {
    LCD[0] = 'S';
    LCD[1] = 'R';
    LCD[2] = 'V';
    LCD[3] = 'C';
    LCD[4] = 'E';
    LCD[5] = 0x20;
    //LCD[6] = 0x00;
  }
  else if(status_SrvcClockDisplay == 1)
  {
    number_to_str(eeMirror.serviceClockLength/HOUR_METER_FCT, &(number_str[0]), (uint8_t)MAX_STRING_LENGTH);

    left_pad_str(number_str,5,0,(uint8_t)MAX_STRING_LENGTH);

    if(actualHourMeter < HOUR_METER_TO_HOUR_FCT)
    {
      number_str[3] = '0';   /* format 0.0 */
    }

    LCD[0] = number_str[1];
    LCD[1] = number_str[2];
    LCD[2] = number_str[3];
    LCD[3] = 'H';
    LCD[4] = 'R';
    LCD[5] = 0x20;
    //LCD[6] = 0x00;
  }
}

void SetServiceClock (void)
/*************************************************************************
*    returns    : NONE.
*
*  Created By   : Spencer Mindeman
*  Date Created : 04 April, 2006
*  Description  : Reset the service clock.
*  Notes        :
*************************************************************************/
{
  if (eeMirror.serviceClockLock & SERVICE_CLOCK_LOCK_BIT)
  {
    eeMirror.serviceClockResetTime = actualHourMeter;
    eeMirror.serviceClockExpired = FALSE;

    if(eeMirror.serviceClockType++ >= 4)
    {
      eeMirror.serviceClockType = 1;
    }
    // UpdateLCDService(2);
    //UpdateEEVariables(NOW);
    QueueServiceDiag((uint16_t)(eeMirror.serviceClockResetTime/HOUR_METER_TO_HOUR_FCT), (uint16_t)(eeMirror.serviceClockLength/HOUR_METER_TO_HOUR_FCT), MANUAL, eeMirror.serviceClockType, current_user);
  }
  UpdateEEVariables(NOW);
}

void UpdateLCDVersion(void)
/*************************************************************************
*    returns    : NONE.
*
*  Created By   : Spencer Mindeman
*  Date Created : 31 Jan, 2007
*  Description  : Display constant data version.
*  Notes        :
*************************************************************************/

{
  uint8_t number_str[MAX_STRING_BUFF_LENGTH];

  number_to_str(CONSTANT_DATA->MAJOR_VERSION_NUMBER, &(number_str[0]), (uint8_t)MAX_STRING_LENGTH);
  left_pad_str(number_str,5,0,(uint8_t)MAX_STRING_LENGTH);

  LCD[0] = 'V';
  LCD[1] = number_str[3];
  LCD[2] = number_str[4];

  number_to_str(CONSTANT_DATA->MINOR_VERSION_NUMBER, &(number_str[0]), (uint8_t)MAX_STRING_LENGTH);
  left_pad_str(number_str,5,0,(uint8_t)MAX_STRING_LENGTH);

  LCD[3] = number_str[3];
  LCD[4] = number_str[4];
  LCD[5] = 0x20;
  //LCD[6] = 0x00;
}

void UpdateLCD_FlashCold(void)
//******************************************************************************
//    returns     : NONE.
//
//                            Created By  : SLM
//    Date Created: 17 July, 2013
//    Description : Display flashing code
//    Notes       :
//******************************************************************************
{
  static uint16_t debounceCount = 0;
  static bool tempState = 0;

  if(debounceCount++ >= 3)
  {
    debounceCount = 0;
    tempState = ~tempState;
  }

  if(tempState)
  {
    LCD[0] = ' ';
    LCD[1] = 'C';
    LCD[2] = 'O';
    LCD[3] = 'L';
    LCD[4] = 'D';

    LCD[5] = ' ';
    LCD[7] = 0x07;
  }
  else
  {
    LCD[0] = ' ';
    LCD[1] = ' ';
    LCD[2] = ' ';
    LCD[3] = ' ';
    LCD[4] = ' ';

    LCD[5] = ' ';
    LCD[7] = 0x07;
  }
}




