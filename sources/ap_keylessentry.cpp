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
* Routines for handling the keyless entry panel
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

#include "cancipher.h"
#include "passwordverifier.h"

//#warning 
//#include "bsp_dout.h"
//******************************************************************************
// DEFINE SECTION
//******************************************************************************


//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************
hw_can_rxmsg KeylessEntryRX;
hw_can_txmsg KeylessEntryTX;
hw_can_rxmsg DeluxePasswordsRX;

bool passwords_received;
uint8_t buffer_password[KE_PASSWORD_SIZE];

//******************************************************************************
// FUNCTIONS
//******************************************************************************

void KeylessEntry_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 25 Jul, 2017
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  can_KeylessEntry[0] = msg->get_byte(0);
  can_KeylessEntry[1] = msg->get_byte(1);
  can_KeylessEntry[2] = msg->get_byte(2);

}

static void initialize_KeylessEntry_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 25 Jul, 2017
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  KeylessEntryRX.initialize();
  KeylessEntryRX.rx_id     .set_J1939ID(0, PROPRIETARY_B, KEYPAD_STATUS_PS, SA_KEYLESS_ENTRY);
  KeylessEntryRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  KeylessEntryRX.rx_callback = KeylessEntry_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&KeylessEntryRX);
}

void update_KeylessEntryTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : AAL
//    Date Created: 25 Jul, 2017
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  msg->set_byte(0, UNDEFINED);
  msg->set_byte(1, UNDEFINED);
  msg->set_byte(2, UNDEFINED);
  msg->set_byte(3, UNDEFINED);
  msg->set_byte(4, (ind_KeylessEntryLock & 0x03) | ((ind_KeylessEntryUnlock & 0x03) << 2));
  msg->set_byte(5, 5);    // Indicator brightness
  msg->set_byte(6, 100);  // Backlight brightness
  msg->set_byte(7, UNDEFINED);
 
}

static void initialize_KeylessEntry_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 10 Jan, 2008
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  KeylessEntryTX.initialize();
  KeylessEntryTX.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, KEYPAD_STATUS_PS, nvm_ecuid.j1939_source_address);
  KeylessEntryTX.Disable();
  KeylessEntryTX.set_send_rate(10);
  KeylessEntryTX.pre_tx_callback = update_KeylessEntryTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&KeylessEntryTX);
}

void DeluxePasswords_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 25 Jul, 2017
//    Description : Receive password data from CAN.
//    Notes       :
//******************************************************************************
{
  uint8_t i;
  uint8_t user;
  static uint32_t passwordFlags = 0;
  #define ALL_PASSWORDS  0x001FFFFF // 21 passwords
 
    if(auth_DeluxeG55 == AUTHENTICATED)
    {
        CanCipher::inst.decipher(msg);
        user = msg->get_byte(0);
         
        if(user < NUMBER_OF_EE_PASSWORDS) //0-20 allowed
        {
            
                
            //write passwords to eeprom mirror
            for(i = 1; i < 8; i++)
            {
               eeMirror.password[user].value[i-1] = msg->get_byte(i); // only storing 7 byte
            }
            eeMirror.password[user].value[7] = 0xFF;
            eeMirror.password[user].value[8] = 0xFF;
            eeMirror.password[user].value[9] = 0xFF;
            
            //calculate checksum
            eeMirror.password[user].checksum = 0;   
            for (i = 0; i < PASSWORD_SIZE; i++)
            {
                eeMirror.password[user].checksum += eeMirror.password[user].value[i]; 
            }
            eeMirror.password[user].checksum = ~eeMirror.password[user].checksum + 1;
            eeTimeToUpdateMirror = 1;                                                // set flag to store into eeprom device
            
            //set bits as individual passwords are received
            passwordFlags |= (1 << user);
            passwords_received = ((passwordFlags & ALL_PASSWORDS) == ALL_PASSWORDS);
        }
    }
}

static void initialize_DeluxePasswords_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 25 Jul, 2017
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  DeluxePasswordsRX.initialize();
  DeluxePasswordsRX.rx_id     .set_J1939ID(0, PROPRIETARY_B, G55_PASSWORD_DATA_PS, SA_DISPLAY_CONTROLLER);
  DeluxePasswordsRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  DeluxePasswordsRX.rx_callback = DeluxePasswords_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&DeluxePasswordsRX);
}

void RequestG55Passwords(void)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 24 Jul, 2017
//    Description : request PGN for Gen 5.5 Deluxe passwords
//    Notes       :
//******************************************************************************
{
  hw_can_msg_t msg_data;
  if(!passwords_received)
  {
      msg_data.id.set_J1939ID(PRIORITY_6, REQUEST_PF, SA_DISPLAY_CONTROLLER ,nvm_ecuid.j1939_source_address );
      msg_data.DLR = 3;
      
      msg_data.set_byte(0, 0x77);
      msg_data.set_byte(1, 0xFF);
      msg_data.set_byte(2, 0x00);
      
      hw_can_txq[HWC_CAN0].send_msg(&msg_data);
  }
}

static uint8_t PasswordValidation(uint8_t *buffer)
//******************************************************************************
//    returns     : user number if valid, 0xFF if invalid
//
//    Created By  : AAL
//    Date Created: 25 Jul, 2017
//    Description : Validate password 
//    Notes       :
//******************************************************************************
{
    uint8_t user = 0U;
    bool valid = false;
      
    // check master password - assume 6 digits only
    if(buffer[0] == MASTER_PWD[0] && buffer[1] == MASTER_PWD[1]
    && buffer[2] == MASTER_PWD[2] && buffer[3] == MASTER_PWD[3]
    && buffer[4] == MASTER_PWD[4] && buffer[5] == MASTER_PWD[5]
    && buffer[6] == NULL          && buffer[7] == NULL
    && buffer[8] == NULL          && buffer[9] == NULL)
    {
      //master password valid
      user = 0;
      valid = true;
    }
    else //check deluxe passwords
    {
      while (user < NUMBER_OF_EE_PASSWORDS) 
      {
        
        uint64_t hash = 0;
        for(uint8_t i = 0; i < 7;i++)
        {
            hash += (uint64_t)eeMirror.password[user].value[6 - i] << i*8;
        }
                          
        if(PasswordVerifier::validateHash(buffer, hash))
        {
          valid = true;
          break;
        }
        user++;
      }
    }
    if(!valid)
    {
        user = UNDEFINED;
    }

    return user;
}
void PasswordEntry(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 25 Jul, 2017
//    Description : Handle password entry from keypad 
//    Notes       :
//******************************************************************************
{
  // Named constants for Chart: '<S638>/Password_Entry'
  #define IN_WAIT_FOR_KEYPRESS   ((uint8_T)6U)
  #define IN_CLEAR_BUFFER        ((uint8_T)4U)
  #define IN_CAPTURE_KEYPRESS    ((uint8_T)2U)
  #define IN_CHECK_PASSWORD      ((uint8_T)3U)
  #define IN_AUTHENTICATED       ((uint8_T)1U)
      
  #define IN_BUTTON_0    ((uint8_T)1U)
  #define IN_BUTTON_1    ((uint8_T)2U)
  #define IN_BUTTON_2    ((uint8_T)3U)
  #define IN_BUTTON_3    ((uint8_T)4U)
  #define IN_BUTTON_4    ((uint8_T)5U)
  #define IN_BUTTON_5    ((uint8_T)6U)
  #define IN_BUTTON_6    ((uint8_T)7U)
  #define IN_BUTTON_7    ((uint8_T)8U)
  #define IN_BUTTON_8    ((uint8_T)9U)
  #define IN_BUTTON_9    ((uint8_T)10U)
  #define IN_NONE        ((uint8_T)11U)
      
  //#define MX_Gtwy_Control_IN_INIT_cvj5   ((uint8_T)5U)
  #define IN_LOCK   ((uint8_T)1U)
  #define IN_UNLOCK ((uint8_T)2U)
      
  static uint8_t state_entry = IN_CLEAR_BUFFER; //MX_Gtwy_Control_DWork.bitsForTID0.is_c68_MX_Gtwy_Control  
  static uint8_t state_lock = 0;  //MX_Gtwy_Control_DWork.bitsForTID0.is_AUTHENTICATED
  static uint8_t state_keypress = IN_NONE; //MX_Gtwy_Control_DWork.bitsForTID0.is_CAPTURE_KEYPRESS
  static bool flag_lock = 0;
  static uint16_t counter = 0;
  static uint8_t position = 0;
  
  // Gateway: MX_Gtwy_Control/System/Keyless_Entry/Password_Entry
  if (counter < MAX_uint16_T) 
  {
      counter++;
  }     
    
  switch (state_entry)
  {
    case IN_AUTHENTICATED:
    if (state_lock == IN_LOCK)
    {
      // During 'LOCK': '<S672>:668'
      if (((can_KeylessEntry[2] & KEYPAD_UNLOCK_MASK) == KEYPAD_UNLOCK_PRESSED) &&
           (counter >= CONSTANT_DATA->DOOR_LOCK_PULSE_LENGTH)) 
      {
        state_lock = IN_UNLOCK;
        counter = 0U;
 
        // Entry 'UNLOCK': '<S672>:669'
        state_KeylessEntryLock = KE_UNLOCK;
      }
    } 
    else
    {
      // During 'UNLOCK': '<S672>:669'
      if (((can_KeylessEntry[2] & KEYPAD_LOCK_MASK) == KEYPAD_LOCK_PRESSED) &&
          (counter >= CONSTANT_DATA->DOOR_LOCK_PULSE_LENGTH))
      {
        state_lock = IN_LOCK;
        counter = 0U;

        // Entry 'LOCK': '<S672>:668'
        state_KeylessEntryLock = KE_LOCK;
      }
    }
    break;

    case IN_CAPTURE_KEYPRESS:
    // During 'CAPTURE_KEYPRESS': '<S672>:605'
    if((can_KeylessEntry[0] == 0) && (can_KeylessEntry[1] == 0) && (can_KeylessEntry[2] == 0))
    {
      state_keypress = 0;
      state_entry = IN_WAIT_FOR_KEYPRESS;
    } 
    else
    {
      switch (state_keypress)
      {
        case IN_BUTTON_0:
        case IN_BUTTON_1:
        case IN_BUTTON_2:
        case IN_BUTTON_3:
        case IN_BUTTON_4:
        case IN_BUTTON_5:
        case IN_BUTTON_6:
        case IN_BUTTON_7:
        case IN_BUTTON_8:
        case IN_BUTTON_9:
        break;

        default:
        // During 'NONE': '<S672>:621'
        if ((can_KeylessEntry[2] & KEYPAD_MASK_9) == KEYPAD_PRESSED_9)
        {
          // Exit 'NONE': '<S672>:621'
          state_Buzzer = SINGLE_SHORT_BEEP;
          state_keypress = IN_BUTTON_9;

          // Entry 'BUTTON_9': '<S672>:617'
          buffer_password[position] = ASCII_9;
          position++;
        }
        else if ((can_KeylessEntry[1] & KEYPAD_MASK_8) == KEYPAD_PRESSED_8)
        {
          // Exit 'NONE': '<S672>:621'
          state_Buzzer = SINGLE_SHORT_BEEP;
          state_keypress = IN_BUTTON_8;

          // Entry 'BUTTON_8': '<S672>:618'
          buffer_password[position] = ASCII_8;
          position++;
        }
        else if ((can_KeylessEntry[1] & KEYPAD_MASK_7) == KEYPAD_PRESSED_7)
        {
          // Exit 'NONE': '<S672>:621'
          state_Buzzer = SINGLE_SHORT_BEEP;
          state_keypress = IN_BUTTON_7;

          // Entry 'BUTTON_7': '<S672>:619'
          buffer_password[position] = ASCII_7;
          position++;
        }
        else if ((can_KeylessEntry[1] & KEYPAD_MASK_6) == KEYPAD_PRESSED_6)
        {
          // Exit 'NONE': '<S672>:621'
          state_Buzzer = SINGLE_SHORT_BEEP;
          state_keypress = IN_BUTTON_6;

          // Entry 'BUTTON_6': '<S672>:623'
          buffer_password[position] = ASCII_6;
          position++;
        }
        else if ((can_KeylessEntry[1] & KEYPAD_MASK_5) == KEYPAD_PRESSED_5)
        {
          // Exit 'NONE': '<S672>:621'
          state_Buzzer = SINGLE_SHORT_BEEP;
          state_keypress = IN_BUTTON_5;

          // Entry 'BUTTON_5': '<S672>:624'
          buffer_password[position] = ASCII_5;
          position++;
        }
        else if ((can_KeylessEntry[0] & KEYPAD_MASK_4) == KEYPAD_PRESSED_4)
        {
          // Exit 'NONE': '<S672>:621'
          state_Buzzer = SINGLE_SHORT_BEEP;
          state_keypress = IN_BUTTON_4;

          // Entry 'BUTTON_4': '<S672>:626'
          buffer_password[position] = ASCII_4;
          position++;
        }
        else if ((can_KeylessEntry[0] & KEYPAD_MASK_3) == KEYPAD_PRESSED_3)
        {
          // Exit 'NONE': '<S672>:621'
          state_Buzzer = SINGLE_SHORT_BEEP;
          state_keypress = IN_BUTTON_3;

          // Entry 'BUTTON_3': '<S672>:627'
          buffer_password[position] = ASCII_3;
          position++;
        }
        else if ((can_KeylessEntry[0] & KEYPAD_MASK_2) == KEYPAD_PRESSED_2)
        {
          // Exit 'NONE': '<S672>:621'
          state_Buzzer = SINGLE_SHORT_BEEP;
          state_keypress = IN_BUTTON_2;

          // Entry 'BUTTON_2': '<S672>:625'
          buffer_password[position] = ASCII_2;
          position++;
        }
        else if ((can_KeylessEntry[0] & KEYPAD_MASK_1) == KEYPAD_PRESSED_1)
        {
          // Exit 'NONE': '<S672>:621'
          state_Buzzer = SINGLE_SHORT_BEEP;
          state_keypress = IN_BUTTON_1;

          // Entry 'BUTTON_1': '<S672>:622'
          buffer_password[position] = ASCII_1;
          position++;
        } 
        else
        {
          if ((can_KeylessEntry[2] & KEYPAD_MASK_0) == KEYPAD_PRESSED_0)
          {
            // Exit 'NONE': '<S672>:621'
            state_Buzzer = SINGLE_SHORT_BEEP;
            state_keypress = IN_BUTTON_0;

            // Entry 'BUTTON_0': '<S672>:620'
            buffer_password[position] = ASCII_0;
            position++;
          }
        }
        break;
      }
    }
    break;

    case IN_CHECK_PASSWORD:
    // During 'CHECK_PASSWORD': '<S672>:632'
    if (state_KeylessEntryPassword == KE_FAIL)
    {
      state_Buzzer = TRIPLE_SHORT_BEEP;
      state_entry = IN_CLEAR_BUFFER;

      // Entry Internal 'CLEAR_BUFFER': '<S672>:591'
      position = 0U;
      while (position < KE_PASSWORD_SIZE) 
      {
        buffer_password[position] = NULL;
        position++;
      }

      position = 0U;
      //buffer_password[0] = UNDEFINED;
    } 
    else
    {
      if (state_KeylessEntryPassword == KE_PASS)
      {
        state_entry = IN_AUTHENTICATED;

        // Entry Internal 'AUTHENTICATED': '<S672>:659'
        if (flag_lock) 
        {
          state_lock = IN_LOCK;
          counter = 0U;

          // Entry 'LOCK': '<S672>:668'
          state_KeylessEntryLock = KE_LOCK;
        } 
        else
        {
          state_lock = IN_UNLOCK;
          counter = 0U;

          // Entry 'UNLOCK': '<S672>:669'
          state_KeylessEntryLock = KE_UNLOCK;
        }
      }
    }
    break;

    case IN_CLEAR_BUFFER:
    // During 'CLEAR_BUFFER': '<S672>:591'
    state_entry = IN_WAIT_FOR_KEYPRESS;

    // Entry 'WAIT_FOR_KEYPRESS': '<S672>:604'
 //   state_Buzzer = BEEP_NONE;
    break;

    default:
    // During 'WAIT_FOR_KEYPRESS': '<S672>:604'
    if (((can_KeylessEntry[0] != 0) || (can_KeylessEntry[1] != 0) || ((can_KeylessEntry[2] & 0x0F) != 0)) &&
        (position < KE_PASSWORD_SIZE))
    {
      state_entry = IN_CAPTURE_KEYPRESS;

      // Entry Internal 'CAPTURE_KEYPRESS': '<S672>:605'
      state_keypress = IN_NONE;

      // Entry 'NONE': '<S672>:621'
      state_KeylessEntryPassword = KE_UNKNOWN;
    }
    else if ((can_KeylessEntry[2] & KEYPAD_LOCK_MASK) == KEYPAD_LOCK_PRESSED)
    {
      flag_lock = true;
      state_entry = IN_CHECK_PASSWORD;
    
      user_KeylessEntry = PasswordValidation(buffer_password);
      if(user_KeylessEntry != UNDEFINED)
      {
        state_KeylessEntryPassword = KE_PASS;
      }
      else
      {
        state_KeylessEntryPassword = KE_FAIL; 
      }
    } 
    else if ((can_KeylessEntry[2] & KEYPAD_UNLOCK_MASK) == KEYPAD_UNLOCK_PRESSED)
    {
      flag_lock = false;
      state_entry = IN_CHECK_PASSWORD;
    
      user_KeylessEntry = PasswordValidation(buffer_password);
      if(user_KeylessEntry != UNDEFINED)
      {
        state_KeylessEntryPassword = KE_PASS;
      }
      else
      {
        state_KeylessEntryPassword = KE_FAIL; 
      }
    }
      
    break;
  }
}

void ap_keylessEntry_Update(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 25 Jul, 2017
//    Description : Periodic update functions for keyless entry.
//    Notes       :
//******************************************************************************
{
  //static bool msg_active = false;
  static bool user_defined = false;
  static bool prev_SwPowerRelay = false;
  //if((state_KeylessEntryPowerHold != KE_PWR_INACTIVE) && !msg_active)
  //{
  //  KeylessEntryTX.set_send_rate(10);
  //  msg_active = true;    
  //}
  
  //If we see switched power turn on for first time, Tx message to keypad right away to get it to drop out wake ASAP
  if(din_SwPowerRelay && !prev_SwPowerRelay)
  {
    KeylessEntryTX.SendRightNow();
    prev_SwPowerRelay = true;
  }
  
  if(state_Engine == ENGINE_CRANKING)
  {
    KeylessEntryRX.msg_age_mS = 0;
  }
  msgAge_KeylessEntry = KeylessEntryRX.msg_age_mS; 

  PasswordEntry();

  if(state_KeylessEntryPassword == KE_PASS & !user_defined)
  {
    current_user = user_KeylessEntry;
    user_defined = true;
  }
}


void ap_keylessentry_initialize (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 25 Jul, 2017
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
    initialize_KeylessEntry_rx();
    initialize_KeylessEntry_tx();
    initialize_DeluxePasswords_rx();
    CanCipher::inst.setSerialNumber(BOBCAT_SERIAL_NUMBER, 9);

    passwords_received = 0;
    
    can_KeylessEntry[0] = UNDEFINED;
    can_KeylessEntry[1] = UNDEFINED;
    can_KeylessEntry[2] = UNDEFINED;
    user_KeylessEntry = UNDEFINED;
    state_KeylessEntryLock = KE_UNKNOWN;
    state_KeylessEntryPassword = KE_UNKNOWN;
    uint8_t i = 0;
    while ( i < KE_PASSWORD_SIZE) 
    {
        buffer_password[i] = NULL;
        i++;
    }
}

