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
* First written on 19 January, 2006 by Doug Olson
*
* Module Description:
* The module broadcasts all non-"normal" error codes from the "ecode_list"
* in a "CAN04" message on the primary CAN bus.  It also handles all error code routines.
***************************************************************/

//******************************************************************************
// INCLUDES
//******************************************************************************

#include "hw_io.h"
#include "nvm_ecuid.h"
#include "ap_bservice_CAN04.h"
#include "ap_eeprom.h"
#include "ap_subs.h"
#include "ap_can.h"
#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"
#include "global.h"
#include "ap_deluxeG5.h"
#include "defines.h"

//******************************************************************************
// DEFINES
//******************************************************************************


#define STARTUP_TIME    10
//******************************************************************************
// STRUCTURES
//******************************************************************************

//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************
hw_can_rxmsg CAN04sRX;

static uint16_t *list;
static uint8_t size;

static uint16_t start_time;
uint16_t start_timeLCD;

uint16_t delay_Buzzer = STARTUP_TIME;

FailureCodeStruct FailureQueue[MAX_NUMBER_OF_FAILURES];
FailureCodeStruct failureCode;

EngineCodeStruct EngineFailureQueue[MAX_NUMBER_OF_SPN];


uint8_t state_Buzzer;// = 0xFF;
uint8_t current_user;

const CodeSeverityStruct severityInformation[]=
{
  {FN_ENGINE_OIL_PRESSURE,           EXTREMELY_LOW,     SEVERITY_SHUTDOWN},
  {FN_ENGINE_OIL_PRESSURE,           SHUTDOWN,          SEVERITY_SHUTDOWN},
  {FN_HYDRAULIC_OIL_TEMPERATURE,     EXTREMELY_HIGH,    SEVERITY_SHUTDOWN},
  {FN_HYDRAULIC_OIL_TEMPERATURE,     SHUTDOWN,          SEVERITY_SHUTDOWN},
  {FN_ENGINE_SPEED,                  EXTREMELY_HIGH,    SEVERITY_SHUTDOWN},
  {FN_ENGINE_SPEED,                  SHUTDOWN,          SEVERITY_SHUTDOWN},
  {FN_ENGINE_COOLANT_TEMPERATURE,    EXTREMELY_HIGH,    SEVERITY_SHUTDOWN},
  {FN_ENGINE_COOLANT_TEMPERATURE,    SHUTDOWN,          SEVERITY_SHUTDOWN},
  {FN_FUEL_TEMP,                     EXTREMELY_HIGH,    SEVERITY_SHUTDOWN},
  {FN_FUEL_TEMP,                     PRE_SHUTDOWN,      SEVERITY_SHUTDOWN},
  {FN_FUEL_TEMP,                     SHUTDOWN,          SEVERITY_SHUTDOWN}
};

void CAN04_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 06 Jan, 2006
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  ErrorQueueDisplayList(msg->get_byte(1), msg->get_byte(2), msg->get_byte(3), 0, TYPE_BOBCAT);
}

static void initialize_CAN04_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 06 Jan, 2006
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  CAN04sRX.initialize();
  CAN04sRX.rx_id     .set_J1939ID(0, 0xFF, 0xFF, 0);
  CAN04sRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0);
  CAN04sRX.D0_data = 0x04;
  CAN04sRX.D0_mask = 0xFF;
  CAN04sRX.rx_callback = CAN04_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&CAN04sRX);
}


void ap_bservice_CAN04_initialize(uint16_t *ecode_list, uint8_t ecode_list_size)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : DO
//    Date Created: 19 Jan, 2006
//    Description : Initialize CAN04 transmit message.
//    Notes       :
//******************************************************************************
{

  initialize_CAN04_rx();

  count_GeneralIcon = 0;

  delay_Buzzer = STARTUP_TIME;
  start_timeLCD = 0;

  list = ecode_list;
  size = ecode_list_size;

  start_time = hw_clock_mS();

  for(uint8_t i=0; i < MAX_NUMBER_OF_FAILURES; i++)
  {
    FailureQueue[i].device = 0xFF;
    FailureQueue[i].spn = 0xFFFF;
    FailureQueue[i].function = 0xFF;
    FailureQueue[i].failure = 0xFF;
    FailureQueue[i].timer = 0;
    FailureQueue[i].type = 0;
    FailureQueue[i].beep = ACTIVE;
    FailureQueue[i].pcode[0] = 0xFF;
    FailureQueue[i].pcode[1] = 0xFF;
    FailureQueue[i].pcode[2] = 0xFF;
    FailureQueue[i].pcode[3] = 0xFF;
    FailureQueue[i].pcode[4] = 0xFF;
  }

  for(uint8_t i=0; i < MAX_NUMBER_OF_SPN; i++)
  {
    EngineFailureQueue[i].SPN = 0xFFFFFFFF;
    EngineFailureQueue[i].FMI = 0xFF;
    EngineFailureQueue[i].OC = 0xFF;
    EngineFailureQueue[i].CM = 0xFF;
  }
}
//******************************************************************************
// FUNCTIONS
//******************************************************************************
static void NumBeeps(uint8_t function, uint8_t failure)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 18 Apr, 2006
//    Description : Determines number of beeps for an error code.
//    Notes       :
//******************************************************************************
{
  switch(function)
  {

    case FN_FRONT_LIGHT_RELAY:
    case FN_FRONT_LIGHT_OUTPUT:
    case FN_SWITCHED_POWER_RELAY:
    case FN_SWITCHED_POWER_OUTPUT:
    case FN_GLOW_PLUG_OUTPUT:
    case FN_GLOW_PLUG_RELAY:
    case FN_CONTROLLER_MEMORY:
    case FN_INTERRUPTED_POWER:
    break;



    case FN_AIR_FILTER:
    case FN_IMPLEMENT_FILTER:
      if((failure == NOT_CONNECTED) || (failure == PLUGGED))
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
    break;

    case FN_BATTERY_VOLTAGE:
    case FN_ALTERNATOR_VOLTAGE:
      if((failure == LOW) || (failure == HIGH) || (failure == EXTREMELY_LOW))
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
    break;

    case FN_ENGINE_OIL_PRESSURE:
    case FN_AUX_CONTROL:
    case FN_OFFSET_CONTROL:
    case FN_LEFT_CONTROL:
    case FN_RIGHT_CONTROL:
    case FN_LOAD_SENSE:
    case FN_ENGINE_SPEED:
    case FN_HYDRAULIC_OIL_TEMPERATURE:
    case FN_THROTTLE_PRIMARY:
    case FN_AUX2_FLOW_CONTROL:
      if((failure == LOW) || (failure == HIGH) || (failure == OORL) || (failure == OORH) || (failure == NOT_IN_NEUTRAL))
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
      else if((failure == EXTREMELY_LOW) || (failure == EXTREMELY_HIGH))
      {
        state_Buzzer = CONTINUOUS_BEEP;
      }
      else if(failure == SHUTDOWN)
      {
        state_Buzzer = NO_BEEP;
      }
    break;

    case FN_FUEL_TEMP:
    case FN_ENGINE_COOLANT_TEMPERATURE:
      if((failure == LOW) || (failure == HIGH) || (failure == OORL) || (failure == OORH))
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
      else if(failure == EXTREMELY_HIGH)
      {
        state_Buzzer = SINGLE_LONG_BEEP;
      }
      else if(failure == SHUTDOWN)
      {
         state_Buzzer = NO_BEEP;
      }
    break;


    case FN_FUEL_LEVEL:
      if(failure == LOW)
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
    break;

    case FN_FUEL_SECONDARY_OUTPUT:
    case FN_AUX_BASE:
    case FN_AUX_ROD:
    case FN_OFFSET_BASE:
    case FN_OFFSET_ROD:
    case FN_DUMP_VALVE:
    case FN_ECU_OUTPUT:
    case FN_TWO_SPEED:
    case FN_HYD_ENABLE:
    case FN_HYD_BYPASS:
    case FN_DIVERTER:
      if((failure == SHORT_TO_BATTERY) || (failure == SHORT_TO_GROUND) ||
         (failure == OPEN_CIRCUIT) || (failure == OPEN_STG) || (failure == OVERCURRENT) ||
         (failure == NOT_CALIBRATED))
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
    break;

    case FN_STARTER_OUTPUT:
    case FN_STARTER_RELAY:
    case FN_FUEL_PRIMARY_RELAY:
    case FN_FUEL_PRIMARY_OUTPUT:
    case FN_PBVALVE_OUTPUT:
    case FN_PBVALVE_RELAY:
    case FN_HVAC_OUTPUT:
    case FN_HYD_EXCHANGE:
    case FN_HP_MATCH:
//    case FN_SECONDAUX_RELEASE:
      if((failure == ERROR_ON) || (failure == ERROR_OFF) || (failure == OPEN_CIRCUIT) ||
         (failure == FAILURE))
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
    break;

    case FN_SENSOR_SUPPLY_2:
    case FN_SENSOR_SUPPLY_1:
    case FN_CONSOLE_SENSOR:
    case FN_LOAD_MOMENT:
      if((failure == OORH) || (failure == OORL) || (failure == ERROR_ON) || (failure == FAILURE) || (failure == FAULT))
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
    break;

    case FN_MAIN_CONTROLLER:
      if(failure == NOT_PROGRAMMED)
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
    break;

    case FN_KEY_SWITCH:
      if(failure == MULTIPLE)
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
    break;


    case FN_SECONDARY:
    case FN_THROTTLE_CONTROLLER:
    case FN_DELUXE_PANEL_G5:
    case FN_KEYLESS_PANEL:
    case FN_ECU_FUNCTION:
    case FN_JOG_SHUTTLE:
    case FN_STANDARD_DISPLAY_PANEL:
    case FN_KEYLESS_ENTRY:
      if((failure == NO_COMMUNICATION) || (failure == NOT_CONNECTED)||
         (failure == NOT_CALIBRATED) || (failure == FAILURE))
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
    break;



    case FN_ENGINE_SPEED_DERATE:
      if(failure == UNRESPONSIVE)
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }

      else if(failure == SHUTDOWN)
      {
        state_Buzzer = NO_BEEP;
      }
    break;
      
    case FN_TURBO_PRIME:
      if(failure == ACTIVE)
      {
        state_Buzzer = TRIPLE_SHORT_BEEP;
      }
    break;

    default:
    break;
  }
}




static bool active_failure(uint8_t failure)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : DO
//    Date Created: 19 Jan, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  return (failure != 0) && (failure != 8) && (failure != 1) && (failure != 12) && (failure < 100);
}

static bool active_failure_extern(uint8_t failure)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 19 Jan, 2006
//    Description : returns failure if it isn't 0 or 255.
//    Notes       :
//******************************************************************************
{
  return (failure != 255);
}

uint8_t code_severity(uint8_t function, uint8_t failure)
//******************************************************************************
//    returns     : uint8_t
//		        
//		Created By  : Boston Zachmann
//    Date Created: 6 Oct, 2016
//    Description : returns severity of code with given function, failure.
//    Notes       : 
//******************************************************************************
{
  uint8_t severity = SEVERITY_INFO;
  for(uint8_t i = 0; i < (sizeof(severityInformation)/sizeof(CodeSeverityStruct)); i++)
  {
    if((function == severityInformation[i].function) && (failure == severityInformation[i].failure))
    {
      severity = severityInformation[i].severity;
      break;
    }
  }
  return severity;
}

void ap_bservice_CAN04_update(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : DO
//    Date Created: 19 Jan, 2006
//    Description : Send out the CAN04 message.
//    Notes       :
//******************************************************************************
{
  static uint8_t i;

  if ((uint16_t)(hw_clock_mS()-start_time) >= 1000 )
  {
    start_time += 1000;

    uint8_t last_i = i;

    do
    {
      ++i;  if (i>=size) i=0;
    } while ( !active_failure(list[i] & 0xFF) && last_i != i);


    if (last_i != i || active_failure(list[i] & 0xFF)  )
    {
      hw_can_msg_t msg_data;
      msg_data.DLR = 8;
      msg_data.id.set_J1939ID(6, 0xFF, 0xFF,nvm_ecuid.j1939_source_address );
      msg_data.set_byte(0,   4);
      msg_data.set_byte(1,'M');
      msg_data.set_byte(2,list[i] >>    8);
      msg_data.set_byte(3,list[i] &  0xFF);
      msg_data.set_byte(4, (code_severity((uint8_t)(list[i] >> 8), (uint8_t)list[i]) << 4));
      msg_data.set_byte(5,current_user);
      msg_data.set_byte(6,0xFF);
      msg_data.set_byte(7,0xFF);

      #ifdef HWC_CAN0
      hw_can_txq[HWC_CAN0].send_msg(&msg_data);
      #endif

      //#ifdef HWC_CAN4
      //hw_can_txq[HWC_CAN4].send_msg(&msg_data);
      //#endif
      
    }
  }
}

void UpdateLCDErrorCodes(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 17 Mar, 2006
//    Description : Update the error codes that display on the panel.
//    Notes       :
//******************************************************************************
{
  static uint8_t errorCount;
  static bool flag_GetNewWarning = FALSE;
  static uint8_t count_Scroll = 255;

  uint8_t lastError = errorCount;
  static uint8_t number_str[MAX_STRING_BUFF_LENGTH];
  static uint8_t number_fmi[MAX_STRING_BUFF_LENGTH];
  static uint16_t time_ScrollCount;

  if(!(ddpSwitchStatus.data.inWarningPage))
  {
    //If the deluxe panel isn't in the warnings screen, display the warnings on a cycle basis.
    //display code for max 2 seconds and then display the next error code if there is one.
    if(start_timeLCD-- == 0)
    {
      lastError = errorCount;
       do
        {
          ++errorCount;  if (errorCount >= MAX_NUMBER_OF_FAILURES) errorCount=0;
        }while ((!active_failure_extern(FailureQueue[errorCount].failure)) && (lastError != errorCount));

      if(FailureQueue[errorCount].type == TYPE_SPN)
      {
        if((CONSTANT_DATA->PCODE_FUNCTION != 0xFF) && (FailureQueue[errorCount].pcode[0] != '?')) //added
        {
          start_timeLCD = 40;
          count_Scroll = 255;   
        }
        else
        {
          start_timeLCD = 130;
          count_Scroll = 255;
        }
      }
      else
      {
        start_timeLCD = 40;
        count_Scroll = 255;
      }
    }
  }
  else
  {
    if(ddpSwitchStatus.data.getNextWarning || flag_GetNewWarning)
    {
      ddpSwitchStatus.data.getNextWarning = FALSE;
      lastError = errorCount;

      do
      {
        ++errorCount;

        if(errorCount >= MAX_NUMBER_OF_FAILURES)
          errorCount=0;

        count_Scroll = 255; //Reset to start on first character.
        start_timeLCD = 110;
      }while ((!active_failure_extern(FailureQueue[errorCount].failure)) && (lastError != errorCount));
    }

    if(state_InfoPrimary == DISPLAY_ERROR_CODES)
    {
      //If scrolling code, want to keep scrolling.
      if(start_timeLCD-- == 0)
      {
        start_timeLCD = 110;
        count_Scroll = 255;
      }
    }
    else
    {
      start_timeLCD = 20;
      count_Scroll = 255;
    }

    failureCode.function = FailureQueue[errorCount].function;
    failureCode.failure = FailureQueue[errorCount].failure;
    failureCode.device = FailureQueue[errorCount].device;
    failureCode.spn = FailureQueue[errorCount].spn;
    failureCode.type = FailureQueue[errorCount].type;
    failureCode.pcode[0] = FailureQueue[errorCount].pcode[0]; 
    failureCode.pcode[1] = FailureQueue[errorCount].pcode[1];
    failureCode.pcode[2] = FailureQueue[errorCount].pcode[2];
    failureCode.pcode[3] = FailureQueue[errorCount].pcode[3];
    failureCode.pcode[4] = FailureQueue[errorCount].pcode[4];

    if((failureCode.function != UNDEFINED) && (failureCode.failure != UNDEFINED))
    {
      flag_GetNewWarning = FALSE;

      // Should this be changed to be != 0xFF or 0?
      if((failureCode.device != 0xFF) && (failureCode.device != 0) && (failureCode.function != 0))
      {
          flag_SendDeluxeWarning = TRUE;
      }
    }
    else
    {
      flag_GetNewWarning = TRUE;  //Keep checking even though button is not pressed do this in case
                                  //a code clears then we go to the next one instead of no active warnings.
      failureCode.device = 77;
      failureCode.function = 0;
      failureCode.failure = 0;
      failureCode.type = TYPE_BOBCAT;
      failureCode.spn = 0xFFFF;
      failureCode.pcode[0] = 0xFF;
      failureCode.pcode[1] = 0xFF;
      failureCode.pcode[2] = 0xFF;
      failureCode.pcode[3] = 0xFF;
      failureCode.pcode[4] = 0xFF;
    }
  }

  if(state_InfoPrimary == DISPLAY_ERROR_CODES)
  {
    //If there are warnings available send them out, otherwise display NONE
    if(active_failure_extern(FailureQueue[errorCount].failure))
    {
      if(FailureQueue[errorCount].type == TYPE_SPN)
      {
        
        if(CONSTANT_DATA->PCODE_FUNCTION != 0xFF && (FailureQueue[errorCount].pcode[0] != '?'))//added if else
        {  
             
          if(FailureQueue[errorCount].function != 0)
          {
            
            LCD[0] = FailureQueue[errorCount].pcode[0];
            LCD[1] = FailureQueue[errorCount].pcode[1];
            LCD[2] = FailureQueue[errorCount].pcode[2];
            LCD[3] = FailureQueue[errorCount].pcode[3];
            LCD[4] = FailureQueue[errorCount].pcode[4];
            
            LCD[5] = 0x20;      
            LCD[6] = 0x00;
            LCD[7] = 0x00;
          }
          
          
        }
        else
        {
          if(count_Scroll == 255)
          {
            uint32_t tmpDWord;
            tmpDWord = ((uint32_t)FailureQueue[errorCount].spn << 8);
            tmpDWord = tmpDWord | FailureQueue[errorCount].function;
  
            number_to_str(tmpDWord, &(number_str[0]), (uint8_t)MAX_STRING_LENGTH);
             left_pad_str(number_str, 6, '0', (uint8_t)6);
  
            number_to_str(FailureQueue[errorCount].failure, &(number_fmi[0]), (uint8_t)MAX_STRING_LENGTH);
            left_pad_str(number_fmi, 2, '0', (uint8_t)2);
  
            time_ScrollCount = 10;
            count_Scroll = 0;
          }
          else
          {
            if(time_ScrollCount-- == 0)
            {
              count_Scroll++;
  
              time_ScrollCount = 10;
            }
          }
  
          switch(count_Scroll)
          {
            case 0:
              LCD[0] = ' ';
              LCD[1] = ' ';
              LCD[2] = ' ';
              LCD[3] = ' ';
              LCD[4] = FailureQueue[errorCount].device;
            break;
  
            case 1:
              LCD[0] = ' ';
              LCD[1] = ' ';
              LCD[2] = ' ';
              LCD[3] = FailureQueue[errorCount].device;
              LCD[4] = number_str[0];
            break;
  
            case 2:
              LCD[0] = ' ';
              LCD[1] = ' ';
              LCD[2] = FailureQueue[errorCount].device;
              LCD[3] = number_str[0];
              LCD[4] = number_str[1];
            break;
  
            case 3:
              LCD[0] = ' ';
              LCD[1] = FailureQueue[errorCount].device;
              LCD[2] = number_str[0];
              LCD[3] = number_str[1];
              LCD[4] = number_str[2];
            break;
  
            case 4:
              LCD[0] = FailureQueue[errorCount].device;
              LCD[1] = number_str[0];
              LCD[2] = number_str[1];
              LCD[3] = number_str[2];
              LCD[4] = number_str[3];
            break;
  
            case 5:
              LCD[0] = number_str[0];
              LCD[1] = number_str[1];
              LCD[2] = number_str[2];
              LCD[3] = number_str[3];
              LCD[4] = number_str[4];
            break;
  
            case 6:
              LCD[0] = number_str[1];
              LCD[1] = number_str[2];
              LCD[2] = number_str[3];
              LCD[3] = number_str[4];
              LCD[4] = number_str[5];
            break;
  
            case 7:
              LCD[0] = number_str[2];
              LCD[1] = number_str[3];
              LCD[2] = number_str[4];
              LCD[3] = number_str[5];
              LCD[4] = '-';
            break;
  
            case 8:
              LCD[0]   = number_str[3];
              LCD[1] = number_str[4];
              LCD[2] = number_str[5];
              LCD[3] = '-';
              LCD[4] = number_fmi[0];
            break;
  
            case 9:
              LCD[0] = number_str[4];
              LCD[1] = number_str[5];
              LCD[2] = '-';
              LCD[3] = number_fmi[0];
              LCD[4] = number_fmi[1];
  
              //count_Scroll = 255; //resets to 0 on increment
            break;
  
            default:
              //count_Scroll = 255;
            break;
          }
  
          LCD[5] = 0x20;
          LCD[6] = 0x00;
          LCD[7] = 0x00;
        }
      }
      else
      {
          //If it is M0909 code, display FUEL instead
          if(FailureQueue[errorCount].device   == GATEWAY_ERROR_ID
          && FailureQueue[errorCount].function == FN_FUEL_LEVEL
          && FailureQueue[errorCount].failure  == LOW 
          && CONSTANT_DATA->FUEL_LEVEL_LOW_DISPLAY_TEXT != NON_FUNCTIONAL)
          {
              LCD[0] =  ' '; 
              LCD[1] =  'F'; 
              LCD[2] =  'U'; 
              LCD[3] =  'E'; 
              LCD[4] =  'L'; 
              LCD[5] = 0x20;
              LCD[6] = 0x00;
              LCD[7] = 0x00;
          }
          else
          {
              LCD[0] = FailureQueue[errorCount].device;
              number_to_str(FailureQueue[errorCount].function, &(number_str[0]), (uint8_t)MAX_STRING_LENGTH);
              left_pad_str(number_str, 2, '0', (uint8_t)MAX_STRING_LENGTH);
              LCD[1] = number_str[0];
              LCD[2] = number_str[1];

              number_to_str(FailureQueue[errorCount].failure, &(number_str[0]), (uint8_t)MAX_STRING_LENGTH);
              left_pad_str(number_str, 2, '0', (uint8_t)MAX_STRING_LENGTH);
              LCD[3] = number_str[0];
              LCD[4] = number_str[1];

              LCD[5] = 0x20;
              LCD[6] = 0x00;
              LCD[7] = 0x00;
          }
      }
    }
    else
    {
      LCD[0] = ' ';
      LCD[1] = 'N';
      LCD[2] = 'O';
      LCD[3] = 'N';
      LCD[4] = 'E';
      LCD[5] = 0x20;
      LCD[6] = 0x00; // turn off radix and colon
      LCD[7] = 0x00;


    }
  }
}

void updateErrorList(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 6 Mar, 2006
//    Description : Goes through list of alarms on controller and records the alarm.
//    Notes       :
//******************************************************************************
{
  static uint8_t i;

  uint8_t last_i = i;

  //go through model ECode list until a fault is found or we get all the way through without one
  do
  {
    ++i;  if (i>=size) i=0;
  } while ( !active_failure(list[i] & 0xFF) && last_i != i);


  if (last_i != i || active_failure(list[i] & 0xFF)  ) //found a fault
  {
    //look for special cases in which we don't want fault recorded
    if((((list[i] >> 8) == FN_FUEL_LEVEL) && ((list[i] & 0xFF) == LOW)) ||
       (((list[i] >> 8) == FN_MAIN_CONTROLLER) && ((list[i] & 0xFF) == NOT_PROGRAMMED)) ||
       (((list[i] >> 8) == FN_CONSOLE_SENSOR) && ((list[i] & 0xFF) == FAILURE)) ||
       (((list[i] >> 8) == FN_LOAD_MOMENT) && ((list[i] & 0xFF) == IN_ERROR)) ||
       (((list[i] >> 8) == FN_FUEL_TEMP) && ((list[i] & 0xFF) == PRE_SHUTDOWN)) ||
       (((list[i] >> 8) == FN_ENGINE_COOLANT_TEMPERATURE) && ((list[i] & 0xFF) == PRE_SHUTDOWN)))


    {
      // do not record alarm.
    }
    else
    {
      QueueEventDiag(DEVICE_ERROR_ID, list[i] >> 8, list[i] & 0xFF, current_user, actualHourMeter/HOUR_METER_TO_HOUR_FCT);
    }

    //Handle display of codes and beeping
    ErrorQueueDisplayList(DEVICE_ERROR_ID, list[i] >> 8, list[i] & 0xFF, 0, TYPE_BOBCAT);

    // Recored stored events here.
    switch ((uint8_t)(list[i] >> 8))
    {
      case FN_AIR_FILTER:
        if((uint8_t)list[i] == PLUGGED)
        {
          UpdateEvent(LOC_AIR_FILTER_PLUGGED);
        }
      break;

      case FN_IMPLEMENT_FILTER:
        if((uint8_t)list[i] == PLUGGED)
        {
          UpdateEvent(LOC_IMPLEMENT_FILTER_PLUGGED);
        }
      break;

      case FN_ENGINE_OIL_PRESSURE:
        if((uint8_t)list[i] == LOW)
        {
          UpdateEvent(LOC_EOP_LOW);
        }
        else if((uint8_t)list[i] == EXTREMELY_LOW)
        {
          UpdateEvent(LOC_EOP_EXTREMELY_LOW);
        }
        else if((uint8_t)list[i] == SHUTDOWN)
        {
          UpdateEvent(LOC_EOP_IN_SHUTDOWN);
        }
      break;

      case FN_ENGINE_SPEED:
        if((uint8_t)list[i] == HIGH)
        {
          UpdateEvent(LOC_ENGINE_SPEED_HIGH);
        }
        else if((uint8_t)list[i] == EXTREMELY_HIGH)
        {
          UpdateEvent(LOC_ENGINE_SPEED_EXTREMELY_HIGH);
        }
        else if((uint8_t)list[i] == SHUTDOWN)
        {
          UpdateEvent(LOC_ENGINE_SPEED_IN_SHUTDOWN);
        }
      break;

      case FN_HYDRAULIC_OIL_TEMPERATURE:
        if((uint8_t)list[i] == HIGH)
        {
          UpdateEvent(LOC_HOT_HIGH);
        }
        else if((uint8_t)list[i] == EXTREMELY_HIGH)
        {
          UpdateEvent(LOC_HOT_EXTREMELY_HIGH);
        }
        else if((uint8_t)list[i] == SHUTDOWN)
        {
          UpdateEvent(LOC_HOT_IN_SHUTDOWN);
        }
      break;

      case FN_ENGINE_COOLANT_TEMPERATURE:
        if((uint8_t)list[i] == HIGH)
        {
          UpdateEvent(LOC_ECT_HIGH);
        }
        else if((uint8_t)list[i] == EXTREMELY_HIGH)
        {
          UpdateEvent(LOC_ECT_EXTREMELY_HIGH);
        }
        else if((uint8_t)list[i] == SHUTDOWN)
        {
          UpdateEvent(LOC_ECT_IN_SHUTDOWN);
        }
      break;

      case FN_STARTER_RELAY:
        if((uint8_t)list[i] == ERROR_ON)
        {
          UpdateEvent(LOC_STARTER_RELAY_ERROR_ON);
        }
      break;

      case FN_STARTER_OUTPUT:
        if((uint8_t)list[i] == ERROR_ON)
        {
          UpdateEvent(LOC_STARTER_OUTPUT_ERROR_ON);
        }
      break;

      case FN_INTERRUPTED_POWER:
        if((uint8_t)list[i] == FAILURE)
        {
          UpdateEvent(LOC_RECOVERY_FAILURE);
        }
      break;

      case FN_FUEL_TEMP:
        if((uint8_t)list[i] == HIGH)
        {
          UpdateEvent(LOC_FUEL_TEMP_HIGH);
        }
        else if((uint8_t)list[i] == EXTREMELY_HIGH)
        {
          UpdateEvent(LOC_FUEL_TEMP_EXTREMELY_HIGH);
        }
        else if((uint8_t)list[i] == SHUTDOWN)
        {
          UpdateEvent(LOC_FUEL_TEMP_IN_SHUTDOWN);
        }
      break;


      default:
      break;
    }
  }
}

void ErrorQueueDisplayList(uint8_t Device, uint8_t Function, uint8_t Failure, uint16_t SPN, uint8_t Type)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 18 Apr, 2006
//    Description : Places error code in queue so it can be displayed on the LCD.
//    Notes       :
//******************************************************************************
{ 
  uint8_t inQueue;

  inQueue = FALSE;

  if((Function == 0) && (Failure == 0) && (SPN == 0))
  {
    // Do not display alarm as it is not an alarm
  }
  else
  {
    // Per Service request, display only LOW instead of Extremely Low or OORL
    if((Device == DEVICE_ERROR_ID) && (Function == FN_BATTERY_VOLTAGE) && ((Failure == OORL) || (Failure == EXTREMELY_LOW)))
    {
      Failure = LOW;
    }

    // Per Service request, display only HIGH instead of Extremely High
    if((Device == DEVICE_ERROR_ID) && (Function == FN_BATTERY_VOLTAGE) && (Failure == EXTREMELY_HIGH))
    {
      Failure = HIGH;
    }

    //Special case for ECT and Fuel Temp, display Ext High as high
    if((Device == DEVICE_ERROR_ID) && ((Function == FN_ENGINE_COOLANT_TEMPERATURE) || (Function == FN_FUEL_TEMP)) && (CONSTANT_DATA->ECU_FUNCTION == ECU_J1939) && (Failure == EXTREMELY_HIGH))
    {
      Failure = HIGH;
    }
    //Special case for ECT and Fuel Temp, display pre_shutdown as Ext High
    if((Device == DEVICE_ERROR_ID) && ((Function == FN_ENGINE_COOLANT_TEMPERATURE) || (Function == FN_FUEL_TEMP)) && (Failure == PRE_SHUTDOWN))
    {
      Failure = EXTREMELY_HIGH;
    }


    for(uint8_t i=0; i < MAX_NUMBER_OF_FAILURES; i++)
    {
      // Determine if the code is already in the queue
      if((FailureQueue[i].device == Device) && (FailureQueue[i].function == Function) &&
        (FailureQueue[i].failure == Failure) && (FailureQueue[i].spn == SPN))

      {
        //Reset the timer
        FailureQueue[i].timer = 0;
        inQueue = TRUE;
        break;
      }
    }

    // code was not in queue, find blank spot and place it there, otherwise ignore code queue is full
    if(!inQueue)
    {
      for(uint8_t i=0; i < MAX_NUMBER_OF_FAILURES; i++)
      {
        if(FailureQueue[i].device == 0xFF)
        {
          FailureQueue[i].device = Device;
          FailureQueue[i].function = Function;
          FailureQueue[i].failure = Failure;
          FailureQueue[i].timer = 0;
          FailureQueue[i].beep = FALSE;      // Set to 0 indicating the beep hasn't been completed yet
          FailureQueue[i].spn = SPN;
          FailureQueue[i].type = Type;
          
          //if the code is a P code or U code then find the pcode and populate FailureQueue[i].pcode
          if(Type == TYPE_SPN)
          {
            //figure out and get ascii pcode
            if (CONSTANT_DATA->PCODE_FUNCTION != 0xFF)
            {
              uint32_t temp;
              uint32_t tablespnfmi;
              uint32_t spnfmi = ((((((uint32_t)SPN) << 8) | ((uint32_t)Function)) << 5 ) | ((uint32_t)Failure));  //construct desired spnfmi
              //testpcode1 = spnfmi;
              //if(Device == DCU_ERROR_ID) //if the SPN message is from DCU then parse DCU PCode Table
              //{
              //  for(uint16_t p = 0; p < SIZE_OF_GTW_PCODE_DCU_SPNLOOKUP; p++)
              //  {
              //    temp = GTW_PCODE_DCU_SPNLOOKUP[p];
              //    
              //    tablespnfmi = temp & 0x00FFFFFF; //get spn/fmi from table at index p
              //    
              //    if(spnfmi == tablespnfmi)
              //    {
              //      
              //      FailureQueue[i].pcode[0] = temp >> 24; //get asci char for P or U
              //      temp = GTW_PCODE_DCU_ASCIIPCODE[p];  //get Ascii Chars for PCODE
              //      FailureQueue[i].pcode[1] = (temp >> 24) & 0xFF;
              //      FailureQueue[i].pcode[2] = (temp >> 16) & 0xFF;
              //      FailureQueue[i].pcode[3] = (temp >> 8) & 0xFF;
              //      FailureQueue[i].pcode[4] = temp & 0xFF;
              //      break;
              //    }
              //    else if(p == (SIZE_OF_GTW_PCODE_DCU_SPNLOOKUP - 1)) //if nothing matches set to ?PCOD
              //    {
              //      FailureQueue[i].pcode[0] = '?';
              //      FailureQueue[i].pcode[1] = 'P';  
              //      FailureQueue[i].pcode[2] = 'C';  
              //      FailureQueue[i].pcode[3] = 'O';  
              //      FailureQueue[i].pcode[4] = 'D';    
              //    }    
              //  }
              //}
               //if not from DCU, then it is an ECU message
              
              for(uint16_t p = 0; p < SIZE_OF_GTW_PCODE_ECU_SPNLOOKUP; p++)
              {
                temp = GTW_PCODE_ECU_SPNLOOKUP[p];  //get spn/fmi from table at index p  
                tablespnfmi = temp & 0x00FFFFFF;
                
                //if(p == 1)
                //{
                  //testpcode2 = temp; 
                  //testpcode3 = tablespnfmi;    
                  //testpcode2 = 254;
                //}
                
                if(spnfmi == tablespnfmi)
                {
                  FailureQueue[i].pcode[0] = temp >> 24; //get asci char for P or U
                  temp = GTW_PCODE_ECU_ASCIIPCODE[p];  //get Ascii Chars for PCODE
                  FailureQueue[i].pcode[1] = (temp >> 24) & 0xFF;
                  FailureQueue[i].pcode[2] = (temp >> 16) & 0xFF;
                  FailureQueue[i].pcode[3] = (temp >> 8) & 0xFF;
                  FailureQueue[i].pcode[4] = temp & 0xFF;
                  break;
                }
                else if(p == (SIZE_OF_GTW_PCODE_ECU_SPNLOOKUP - 1)) //if nothing matches set to ?PCOD
                {
                  FailureQueue[i].pcode[0] = '?';
                  FailureQueue[i].pcode[1] = 'P';
                  FailureQueue[i].pcode[2] = 'C';
                  FailureQueue[i].pcode[3] = 'O';
                  FailureQueue[i].pcode[4] = 'D';  
                }
              }                          
            }
            else //disabled pcode function.. set to ?pcode to indicate to DDP to display ECode instead
            {
              FailureQueue[i].pcode[0] = '?';
              FailureQueue[i].pcode[1] = 'P';
              FailureQueue[i].pcode[2] = 'C';
              FailureQueue[i].pcode[3] = 'O';
              FailureQueue[i].pcode[4] = 'D';
            }
          }
          
          //if not SPN type code, the pcode should not be displayed. populate with 00000 in case is does display
          else
          {
            FailureQueue[i].pcode[0] = '0';
            FailureQueue[i].pcode[1] = '0';
            FailureQueue[i].pcode[2] = '0';
            FailureQueue[i].pcode[3] = '0';
            FailureQueue[i].pcode[4] = '0';
          }
          
          
          flag_ActiveWarning = ACTIVE;
          flag_StdActiveWarn = ACTIVE;


          break;
        }
      }
    }
  }
}

void ErrorQueueTimerUpdate(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 18 Apr, 2006
//    Description : Updates the timer in the error code display list.
//    Notes       :
//******************************************************************************
{

  uint8_t count_Warnings;
  count_GeneralIcon = 0;
  //Cycle through the queue
  count_Warnings = 0;
  for(uint8_t i=0; i < MAX_NUMBER_OF_FAILURES; i++)
  {
    // add count for existing devices that need general icon displayed for error. If non are found, icon
    // will not be displayed.
    if((FailureQueue[i].device == SEC_ERROR_ID) || (FailureQueue[i].device == ATTACHMENT_ERROR_ID) ||
      ((FailureQueue[i].device == THROTTLE_ERROR_ID) && (CONSTANT_DATA->THROTTLE_TYPE == ACTUATOR))  ||
      //((FailureQueue[i].device == ENGINE_ERROR_ID) && (CONSTANT_DATA->THROTTLE_TYPE != ACTUATOR))
       (FailureQueue[i].device == LHP_ERROR_ID))
    {
      count_GeneralIcon++;
    }

    if(FailureQueue[i].device != 0xFF)
    {
      count_Warnings++;
      //If spot has a code in it increment the timer, if timer expired, clear out code.
      if(FailureQueue[i].device == ENGINE_ERROR_ID)
      {
        if(FailureQueue[i].timer < ENGINE_ERROR_CODE_DISPLAY_TIME)
        {
          FailureQueue[i].timer++;
        }
        else
        {
          FailureQueue[i].device = 0xFF;
          FailureQueue[i].function = 0xFF;
          FailureQueue[i].failure = 0xFF;
          FailureQueue[i].timer = 0;
          FailureQueue[i].beep = ACTIVE;
          FailureQueue[i].type = 0;
          FailureQueue[i].spn = 0xFFFF;
          FailureQueue[i].pcode[0] = 0xFF;
          FailureQueue[i].pcode[1] = 0xFF;
          FailureQueue[i].pcode[2] = 0xFF;
          FailureQueue[i].pcode[3] = 0xFF;
          FailureQueue[i].pcode[4] = 0xFF;
          
        }
      }
      else
      {
        if(FailureQueue[i].timer < ERROR_CODE_DISPLAY_TIME)
        {
          FailureQueue[i].timer++;
        }
        else
        {
          //If a fault with a continuous alarm goes inactive, turn off the alarm.
          if((FailureQueue[i].function == FN_ENGINE_OIL_PRESSURE        && FailureQueue[i].failure == EXTREMELY_LOW ) ||
             (FailureQueue[i].function == FN_ENGINE_SPEED               && FailureQueue[i].failure == EXTREMELY_HIGH) ||
             (FailureQueue[i].function == FN_HYDRAULIC_OIL_TEMPERATURE  && FailureQueue[i].failure == EXTREMELY_HIGH) ||
             (FailureQueue[i].function == FN_ENGINE_COOLANT_TEMPERATURE && FailureQueue[i].failure == EXTREMELY_HIGH) ||
             (FailureQueue[i].function == FN_FUEL_TEMP                  && FailureQueue[i].failure == EXTREMELY_HIGH))
          {
            state_Buzzer = NO_BEEP;
          }

          FailureQueue[i].device = 0xFF;
          FailureQueue[i].function = 0xFF;
          FailureQueue[i].failure = 0xFF;
          FailureQueue[i].timer = 0;
          FailureQueue[i].beep = ACTIVE;
          FailureQueue[i].type = 0;
          FailureQueue[i].spn = 0xFFFF;
          FailureQueue[i].pcode[0] = 0xFF;
          FailureQueue[i].pcode[1] = 0xFF;
          FailureQueue[i].pcode[2] = 0xFF;
          FailureQueue[i].pcode[3] = 0xFF;
          FailureQueue[i].pcode[4] = 0xFF;


        }
      }
    }

    if(count_Warnings == 0)
    {
      flag_ActiveWarning = INACTIVE;
      flag_StdActiveWarn = INACTIVE;

    }

  }

  if(delay_Buzzer > 0)
  {
    delay_Buzzer--;
  }
  else
  {
    for(uint8_t i=0; i < MAX_NUMBER_OF_FAILURES; i++)
    {
      if(FailureQueue[i].beep == INACTIVE)
      {
        FailureQueue[i].beep = ACTIVE;

        if(FailureQueue[i].device == DEVICE_ERROR_ID)
        {
          NumBeeps(FailureQueue[i].function,FailureQueue[i].failure);
        }
        else
        {
          state_Buzzer = TRIPLE_SHORT_BEEP;
        }

        if(state_Buzzer == TRIPLE_SHORT_BEEP)
        {
          delay_Buzzer = 7;
        }
        else
        {
          delay_Buzzer = 2;
        }

        break;  //Break out of four loop to beep again.
      }
    }
  }
}

