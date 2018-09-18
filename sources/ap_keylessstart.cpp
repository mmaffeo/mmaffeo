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
* First written on 13 December, 2005 by Spencer Mindeman
*
* Module Description:
* Routines for handling the keyless start panel
***************************************************************/

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "hw_io.h"
#include "nvm_ecuid.h"
#include "ap_bservice.h"
#include "cdata.h"
#include "defines.h"
#include "global.h"

#include "ap_keylessstart.h"

#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"
#include "ap_MXGWcontrol_defs.h"

#include "ap_main.h"
#include "ap_eeprom.h"

#include "ap_can.h"
#include "ap_subs.h"

//******************************************************************************
// DEFINE SECTION
//******************************************************************************


//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************
hw_can_rxmsg CAN_KeypadsRX;

hw_can_txmsg CAN_KeypadsTX;

bool flag_KeylessPwdSet;

//******************************************************************************
// FUNCTIONS
//******************************************************************************
static void checkKeylessStale (void)
{
  if(flag_InitEERead && eeMirror.keypad == ACTIVE)
  {
    if((state_Engine == ENGINE_CRANKING) || (state_System != SYS_NORMAL))
    {
      CAN_KeypadsRX.msg_age_mS = 0;
    }
    else if(((CAN_KeypadsRX.msg_age_mS > CONSTANT_DATA->KEYLESS_START_DEBOUNCE_MISSING) &&
        (state_KeylessPanel != INACTIVE))
      || (state_KeylessPanel == NO_COMMUNICATION))
    {
      state_KeylessPanel = NO_COMMUNICATION;
    }
    else if((CAN_KeypadsRX.msg_age_mS <= CONSTANT_DATA->KEYLESS_START_DEBOUNCE_MISSING) && (state_KeylessPanel != NO_COMMUNICATION))
    {
      state_KeylessPanel = NORMAL;
    }

  }
  else if(flag_InitEERead && (CAN_KeypadsRX.msg_age_mS <= CONSTANT_DATA->KEYLESS_START_DEBOUNCE_MISSING) && (state_KeylessPanel != NO_COMMUNICATION))
  {
    state_KeylessPanel = NORMAL;
    if(eeMirror.keypad != ACTIVE)
    {
      eeMirror.keypad = ACTIVE;
      eeMirror.deluxe_G5 = INACTIVE;
      UpdateEEVariables(NOW);
    }
  }
  else
  {
    state_KeylessPanel = INACTIVE;
  }
}

void Keypad_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 06 April, 2006
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  can_Keypad[0] = msg->get_byte(0);
  can_Keypad[1] = msg->get_byte(1);
  can_Keypad[2] = msg->get_byte(2);
}

static void initialize_Keypad_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 10 Jan, 2006
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  CAN_KeypadsRX.initialize();
  CAN_KeypadsRX.rx_id     .set_J1939ID(0, PROPRIETARY_B, KEYPAD_STATUS_PS, SA_KEYLESS_START);
  CAN_KeypadsRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  CAN_KeypadsRX.rx_callback = Keypad_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&CAN_KeypadsRX);
}

void update_KeypadTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 10 Jan, 2008
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  bool ind_Keypad = 1;

  msg->set_byte(0, UNDEFINED);
  msg->set_byte(1, UNDEFINED);
  msg->set_byte(2, UNDEFINED);
  msg->set_byte(3, UNDEFINED);
  if(eeMirror.keypad == ACTIVE)
  {  
    msg->set_byte(4, (ind_Unlock & 0x03) | ((ind_Lock & 0x03) << 2) | ((ind_Keypad & 0x03) << 4));
    msg->set_byte(5, CONSTANT_DATA->LOCK_BRIGHTNESS);    // Indicator brightness
    msg->set_byte(6, CONSTANT_DATA->KEYPAD_BRIGHTNESS);  // Backlight brightness
  }
  else
  {
    msg->set_byte(4, UNDEFINED);
    msg->set_byte(5, UNDEFINED);
    msg->set_byte(6, UNDEFINED);
  }  
  msg->set_byte(7, UNDEFINED);
}

static void initialize_Keypad_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 10 Jan, 2008
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  CAN_KeypadsTX.initialize();
  CAN_KeypadsTX.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, KEYPAD_STATUS_PS, nvm_ecuid.j1939_source_address);

  CAN_KeypadsTX.set_send_rate(10);
  CAN_KeypadsTX.pre_tx_callback = update_KeypadTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&CAN_KeypadsTX);
}

void ap_keylessstart_Update(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 5 Feb 2008
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  checkKeylessStale();  
    
  if(flag_InitEERead && (eeMirror.keypad == ACTIVE) && (state_KeylessPanel == NORMAL))
  {
    if((state_KSLock == KS_LOCK_MACHINE) && (state_KSPassword == PASS))
    {
      if(eeMirror.passwordLock == INACTIVE)
      {
        eeMirror.passwordLock = ACTIVE;
        UpdateEEVariables(NOW);
      }
    }

    if((state_KSLock == KS_UNLOCK_MACHINE) && (state_KSPassword == PASS))
    {
      if(eeMirror.passwordLock == ACTIVE)
      {
        eeMirror.passwordLock = INACTIVE;
        UpdateEEVariables(NOW);
      }
    }

    if(state_KSPassword == 0)
    {
      flag_KeylessPwdSet = 0;
    }

    if(state_KSPassword == NEW)
    {
      // If password is not set yet, set the new password
      if(!flag_KeylessPwdSet)
      {
        for(uint8_t i=0; i < MAX_PWD_CHAR; i++)
        {
          if(eeMirror.password[PWD_NumberSelected].value[i] != pwd_Keyless[i])
          {
            eeMirror.password[PWD_NumberSelected].checksum = 0;

            for(uint8_t j=0; j < MAX_PWD_CHAR; j++)
            {
              eeMirror.password[PWD_NumberSelected].value[j] = pwd_Keyless[j];
              eeMirror.password[PWD_NumberSelected].checksum += eeMirror.password[PWD_NumberSelected].value[j]; // calc the new checksum
            }

            //Only first 5 characters are used so make sure the rest are cleared out so checksum isn't
            //incorrect.
            for(uint8_t j=MAX_PWD_CHAR; j < PASSWORD_SIZE; j++)
            {
              eeMirror.password[PWD_NumberSelected].value[j] = 0;
            }

            eeMirror.password[PWD_NumberSelected].checksum = ~eeMirror.password[PWD_NumberSelected].checksum + 1;
            eeTimeToUpdateMirror = 1;
            flag_KeylessPwdSet = 1;

            break;
          }
        }
      }

      for(uint8_t i=0; i < MAX_PWD_CHAR; i++)
      {
        ee_OwnerPassword[i] = eeMirror.password[0].value[i];
        ee_User1Password[i] = eeMirror.password[1].value[i];
        ee_User2Password[i] = eeMirror.password[2].value[i];

      }
    }
  }
}

void ap_keylessstart_initialize (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 10 Jan, 2008
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  initialize_Keypad_rx();
  initialize_Keypad_tx();

  
  //Set keypad message to max so we only get NORMAL if it is actually connected.
//  if(eeMirror.keypad == ACTIVE)
//  {
//    CAN_KeypadsRX.msg_age_mS = 0;
//    state_KeylessPanel = NORMAL;
//  }
//  else
//  {
    CAN_KeypadsRX.msg_age_mS = 65535;
    state_KeylessPanel = INACTIVE;
//  }
}

