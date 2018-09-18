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
* First written on 6 October, 2016 by Boston Zachmann
*
* Module Description:
* Routines for interaction with the 7" deluxe panel.
***************************************************************/

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "ap_deluxeG55.h"
#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"
#include "ap_subs.h"
#include "cancipher.h"
#include "bsp_clock.h"
#include "stdlib.h"

//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************
hw_can_txmsg tx_DeluxeMainStatus;
hw_can_txmsg tx_VitalDataG55;
hw_can_txmsg tx_AuxHydStatus;

hw_can_rxmsg rx_DeluxeStatusG55;
hw_can_rxmsg rx_OperatorSettings;
hw_can_rxmsg rx_JogButtonState;
hw_can_rxmsg rx_DeluxeAuthenticationG55;


typedef struct
{
  uint8_t icon;
  uint8_t units;
} vitalItem;

const vitalItem vitalDisplayG55[] = 
{
    {G55_VITAL_ICON_RPM,        1},
    {G55_VITAL_ICON_EOP,        3},
    {G55_VITAL_ICON_ECT,        4},
    {G55_VITAL_ICON_BATTERY,    2},
    {G55_VITAL_ICON_HCP,        3},
    {G55_VITAL_ICON_HOT,        4},
    {G55_VITAL_ICON_FUEL_USAGE, 5},
    {G55_VITAL_ICON_DPF_HOUR,   6}
};

static uint8_t   state_Phone;
static uint32_t  actual_challenge_response;
static uint32_t  expected_challenge_response;
static uint8_t   authMain;
static uint8_t   authDisplay;

static void sendChallengeResponse(uint32_t result);
static void sendChallenge(void);


//******************************************************************************
// FUNCTIONS
//******************************************************************************

static void update_DeluxeMainStatus_tx (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//		        msg : Data to be sent.
//		Created By  : Boston Zachmann
//    Date Created: 7 Oct, 2016
//    Description : Updates Engine RPM TX Message data.
//    Notes       :
//******************************************************************************
{
    uint8_t tempByte = 0;
    // byte 0: 0.0 - Main State (6 bits); 0.6 - Authentication State
    // Main State (System State)
    if(state_System <= 0x0F)
    {
        tempByte = state_System & 0x0F;
    }
    else
    {
        // Want to make sure the system state value does not exceed the allowable mask
        // value.  If it is set to an error state.
        tempByte = 0x0E;
    }
    
    // Authentication State - has main controller authenticated the deluxe
    tempByte |= (authDisplay == AUTHENTICATED) << 6;
  
    msg->set_byte(0, tempByte);
    
    // byte 1: 1.0 - Password State (2 bits); 1.2 - Machine Lock State (2 bits)
    //         1.4 - Key State        
    if(state_KeylessEntryPassword == KE_PASS)
    {
        tempByte = 0;
    }
    else
    {
        tempByte = 1;
    }
    tempByte = (tempByte) + ((state_MachineLock & 0x03) << 2);
  
    // If the key state is greater than active it is in an error condition
    // therefor set the state to error.  May look at separating the machine
    // and remote key out in the future, but for now, leave as is.
    if (state_Key > ACTIVE)
    {
        tempByte = tempByte + (0xE0);
    }
    else
    {
        tempByte = tempByte + ((state_Key & 0x0F) << 4);
    }

    msg->set_byte(1, tempByte);
    
    // byte 2: 2.0 - Engine state (8 bits)
    msg->set_byte(2, state_Engine);

    // byte 3: 3.0 - Auto Idle Mode (2 bits); 3.2 - Unused (2 bits);
    //         3.4 - MX Eco mode (2 bits);    3.6 - Unused (2 bits)
  
    // 3.0 - Auto Idle Mode (2 bits) 
    if(CONSTANT_DATA->AUTOIDLE_FUNCTION == NON_FUNCTIONAL)
    {
        tempByte = G55_AUTO_IDLE_NA;
    }
    else if(state_AutoIdleEnable == IN_ERROR)
    {
        tempByte = G55_AUTO_IDLE_ERROR; 
    } 
    else
    {
        if(cmd_AutoIdle == ACTIVE)
        {
            tempByte = G55_AUTO_IDLE_ENGAGED_ON;
        }
        else
        {
            tempByte = G55_AUTO_IDLE_ENGAGED_OFF;
        }
    }
    
    // 3.2 - Unused (2 bits)
    tempByte |= 0x0C;
  
    // 3.4 - Idle State (2 bits)
    tempByte |= ((state_Idle & 0x03) << 4);
  
    // 3.6 - Unused (2 bits)
    tempByte |= 0xC0;
    
    msg->set_byte(3, tempByte);
    
    // byte 4: 4.0 - current user (8 bits)
    msg->set_byte(4, current_user);
    
    // byte 5: 5.0 - CAN Version (8 bits)
    msg->set_byte(5, CONSTANT_DATA->DELUXE_CAN_VERSION);
  
    // byte 6: Unused
    msg->set_byte(6, 0xFF);
  
    // byte 7: Unused
    msg->set_byte(7, 0xFF);
  
}
static void initialize_DeluxeMainStatus_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//		Created By  : Boston Zachmann
//    Date Created: 7 Oct, 2016
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  tx_DeluxeMainStatus.initialize();
  tx_DeluxeMainStatus.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DELUXE_MAIN_STATUS_PS, nvm_ecuid.j1939_source_address);
  tx_DeluxeMainStatus.set_send_rate(10);
  tx_DeluxeMainStatus.pre_tx_callback = update_DeluxeMainStatus_tx;  
  hw_can_tx_scheduler[HWC_CAN0].add_msg(&tx_DeluxeMainStatus);
}

void update_VitalDataG55_tx (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//		        msg : Data to be sent.
//		Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates job clock message data.
//    Notes       :
//******************************************************************************
{  
 /**************************************************************
  0.0	4 	Screen location	Indicates for which screen location the data in	0 -Maintenance Clock
	        the message is relevant.  Vitals and service                  	1 - screen position 1
         	intervals shall use this parameter to define a                	2 - screen position 2
	        screen position                       	                        3 - screen position 3
                                                                        	4 - screen position 4
                                                                        	5 - screen position 5
                                                                        	6 - screen position 6
	0.4	4 	Units ID	Shall indicate which units from the units 
        	database to be displayed.  The units shall be 
        	communicated in SI units.  Any conversion of 
	        units shall take place by the receiving unit.
	        
	1.0	8	  Radix location	Indication the location of the radix.  Amount to  	0 - no radix
        	offset the Radix current value  1234, scale 0 =                   	1 - tenths shall be used
	        1234; 1234, scale 1 = 123.4; 1234, scale 2 =                       	2 - hundredths shall be used
        	12.34
	1.0	16	Vitals Warning Level
	
	2.0	8	  Color value	Indicate the color to be utilized	                      0 - White (default)
                                                                            	1 - Yellow
	                                                                            2 - Red
	3.0	16	Vitals Shutdown Level
	
	5.0	16	Vitals Current Level Value
	
	7.0	8	  Icon ID number	Indicates which icon should be displayed.  	        0 - No icon
        	Used with service and vital messages to 
        	indicate which ICON in the ICON database 
	        should be displayed
  **************************************************************/
  
  uint16_t tempWord;
  uint8_t num_Vitals;
  static uint8_t count_Vital = 0;
  
  //10 = RPM, 20 = EOP, 30 = ECT, 40 = BATT, 50 = HCP, 60 = HOT
  
  msg->set_byte(0, (count_Vital+1 << 4) + (vitalDisplayG55[count_Vital].units & 0x0F));
  msg->set_byte(1, G55_SCALE_ZERO);
  msg->set_byte(2, G55_ICON_DEFAULT);
  msg->set_byte(7, vitalDisplayG55[count_Vital].icon);
   
  switch(vitalDisplayG55[count_Vital].icon)
  {                                       
    case G55_VITAL_ICON_RPM:
      msg->set_byte(5,(uint8_t)(flt_EngineSpeed>>8));
      msg->set_byte(6,(uint8_t)(flt_EngineSpeed));
      
      if(state_EngineSpeed == HIGH)
      {
        msg->set_byte(2, G55_ICON_YELLOW);
      }
      else if((state_EngineSpeed == EXTREMELY_HIGH) || (state_EngineSpeed == SHUTDOWN))
      {
        msg->set_byte(2, G55_ICON_RED); 
      }
    break;
    
    case G55_VITAL_ICON_BATTERY:
      //tempWord = calc_VBattery/256;
      tempWord = (calcFlt_VBattery * 10) >> 8;
      
      msg->set_byte(1, G55_SCALE_ONE);
      msg->set_byte(5,(uint8_t)(tempWord>>8));
      msg->set_byte(6,(uint8_t)(tempWord));
      
      if((state_VBattery == LOW) || (state_VBattery == HIGH) || (state_Alternator == LOW))
      {
        msg->set_byte(2, G55_ICON_YELLOW);
      }
      else if((state_VBattery == EXTREMELY_LOW) || (state_VBattery == EXTREMELY_HIGH) || (state_Alternator == HIGH))
      {
        msg->set_byte(2, G55_ICON_RED); 
      }
    break;
    
    case G55_VITAL_ICON_EOP:
      msg->set_byte(5,(uint8_t)(flt_EOP>>8));
      msg->set_byte(6,(uint8_t)flt_EOP);
      
      
      if(state_EOP == LOW)
      {
        msg->set_byte(2, G55_ICON_YELLOW);
      }
      else if((state_EOP == EXTREMELY_LOW) || (state_EOP == SHUTDOWN))
      {
        msg->set_byte(2, G55_ICON_RED); 
      }
      
    break;
    
    case G55_VITAL_ICON_HCP:
      msg->set_byte(5,UNDEFINED);
      msg->set_byte(6,UNDEFINED);
      msg->set_byte(2, G55_ICON_DEFAULT);
    break;
    
    case G55_VITAL_ICON_ECT:
      msg->set_byte(5,(uint8_t)(flt_ECT>>8));
      msg->set_byte(6,(uint8_t)flt_ECT);
      
      if(state_ECT == HIGH)
      {
        msg->set_byte(2, G55_ICON_YELLOW);
      }
      else if((state_ECT == EXTREMELY_HIGH) || (state_ECT == SHUTDOWN) || (state_ECT == PRE_SHUTDOWN))
      {
        msg->set_byte(2, G55_ICON_RED); 
      }
    break;
    
    case G55_VITAL_ICON_HOT:
      msg->set_byte(5,(uint8_t)(flt_HOT>>8));
      msg->set_byte(6,(uint8_t)flt_HOT);
      
      if(state_HOT == HIGH)
      {
        msg->set_byte(2, G55_ICON_YELLOW);
      }
      else if((state_HOT == EXTREMELY_HIGH) || (state_HOT == SHUTDOWN))
      {
        msg->set_byte(2, G55_ICON_RED); 
      }
    break;
    
    case G55_VITAL_ICON_FUEL_USAGE:
      msg->set_byte(1, G55_SCALE_ONE);
      
      tempWord = (can_FuelRate * 5) / 10;
      msg->set_byte(5, (uint8_t)(tempWord>>8));
      msg->set_byte(6, (uint8_t)(tempWord));
        
    break;
    
    case G55_VITAL_ICON_DPF_HOUR: // G2 engine does not have a DPF so display engine oil temperature instead
      msg->set_byte(0, (count_Vital+1 << 4) + (4 & 0x0F));
      msg->set_byte(5,(uint8_t)(ecu_EOT>>8));
      msg->set_byte(6,(uint8_t)ecu_EOT);
    
      if(ecu_EOT >= CONSTANT_DATA->EOT_HIGH)
      {
        msg->set_byte(2, G55_ICON_YELLOW);
      }
      else if(ecu_EOT >= CONSTANT_DATA->EOT_EXTREMELY_HIGH)
      {
        msg->set_byte(2, G55_ICON_RED); 
      }
    break;
    
    default:
      msg->set_byte(5,0xFF);
      msg->set_byte(6,0xFF);
    break;   
  }
                  
  count_Vital++;
  
  if(CONSTANT_DATA->ECU_FUNCTION != NON_FUNCTIONAL)
  {
    num_Vitals = 8;
  }
  else
  {
    num_Vitals = 6;
  }
    
  if(count_Vital >= num_Vitals)
  {
    count_Vital = 0;
  }
}

static void initialize_VitalDataG55_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//		Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  tx_VitalDataG55.initialize();
  tx_VitalDataG55.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, VITAL_DATA_PS, nvm_ecuid.j1939_source_address);
  tx_VitalDataG55.set_send_rate(10);
  tx_VitalDataG55.pre_tx_callback = update_VitalDataG55_tx;  
  hw_can_tx_scheduler[HWC_CAN0].add_msg(&tx_VitalDataG55);
}

void DeluxeStatusG55_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : Al Liebel
//    Date Created: 20 Oct, 2016
//    Description : Gets the info from the deluxe status message.
//    Notes       :
//******************************************************************************
{
    static uint8_t previousUser = UNDEFINED;
    uint8_t tempByte = 0;
    
    // byte 0: 0.0 - DDP State (4 bits); 0.6 - Authentication State (2 bits)
    tempByte = msg->get_byte(0);

    // DDP State
    state_DeluxeG55 = tempByte & 0x0F;

    // Authentication State - main controller authenticated by display
    authMain = (tempByte >> 6) & 0x03;

    // byte 1: 1.0 - Screen (16 bits)
    // Not used by this controller
  
  
    // byte 3: 3.2 - Password State (2 bits)
    //         3.6 - Aux release status (2 bits)		
    tempByte = msg->get_byte(3);
    
    //aux release status, Byte 3.6 - 2 bits
    //dlx_G55_AuxReleaseStatus = (tempByte & G55_AUX_RELEASE_MASK) >> 6;
    
    // byte 4: 4.0 - User Logged In (8 bits)
    tempByte = msg->get_byte(4);
    if((state_System == SYS_NORMAL) && !((tempByte == UNDEFINED) && (previousUser == UNDEFINED)))
    {
          current_user = tempByte;
          previousUser = tempByte;
          //QueueCurrentUser(current_user,(uint16_t)(actualHourMeter/HOUR_METER_TO_HOUR_FCT));    
    }
    
    // byte 5: CAN Version

    // byte 6: Not Used

    // byte 7: 7.0 - Phone State (4 bits); 7.4 - Radio State (4 bits)
    state_Phone = msg->get_byte(7) & 0x0F;
}
static void initialize_DeluxeStatusG55_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 21 Oct, 2016
//    Description : initialize CAN to receive deluxe status messages.
//    Notes       :
//******************************************************************************
{
  rx_DeluxeStatusG55.initialize();
  rx_DeluxeStatusG55.rx_id     .set_J1939ID(0, PROPRIETARY_B, G55_DELUXE_STATUS_PS, SA_DISPLAY_CONTROLLER);
  rx_DeluxeStatusG55.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);  
  rx_DeluxeStatusG55.rx_callback = DeluxeStatusG55_rx_callback;   
  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_DeluxeStatusG55);
}

void OperatorSettings_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 19 Oct, 2016
//    Description : Gets the operator settings.
//    Notes       :
//******************************************************************************
{
    dlx_G55_AutoIdleTime = msg->get_byte(1);
    dlx_G55_AutoIdle = (uint8_t)((msg->get_byte(7) & 0x03) == 0x01);
    dlx_G55_EcoMode  = (uint8_t)((msg->get_byte(7) & 0x0C) == 0x04);
}

static void initialize_OperatorSettings_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 19 Oct, 2016
//    Description : initialize CAN to receive operator settings messages.
//    Notes       :
//******************************************************************************
{
  rx_OperatorSettings.initialize();
  rx_OperatorSettings.rx_id     .set_J1939ID(0, PROPRIETARY_B, OPER_SETTINGS_PS, SA_DISPLAY_CONTROLLER);
  rx_OperatorSettings.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);  
  rx_OperatorSettings.rx_callback = OperatorSettings_rx_callback;   
  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_OperatorSettings);
}

void DeluxeAuthenticationG55_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 19 Oct, 2016
//    Description : Handles any authentication messages recieved
//    Notes       :
//******************************************************************************
{
  uint32_t temp = 0;
  
  CanCipher::inst.decipher(msg);
  
  uint8_t msg_type = msg->get_byte(0);
  
  switch (msg_type)
  {
    case 0x00: //challenge response
        actual_challenge_response = (uint32_t)msg->get_word(1) | ((uint32_t)msg->get_word(2) << 16);
        if(actual_challenge_response == expected_challenge_response)
        {
            //display is authentic by main controller
            authDisplay = AUTHENTICATED;
        }
    break;
      
    case 0x01: //type 1 challenge 
        sendChallengeResponse(msg->get_word(1) * msg->get_word(2));
    break;
      
    case 0x02: //type 2 challenge
        temp = (msg->get_word(1) ^ 0xAAAA) << 16;
        temp |= (msg->get_word(2) ^ 0x5555);
        sendChallengeResponse(temp);
    break;
    
    default:
    break;
  } 
} 

static void initialize_DeluxeAuthenticationG55_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 19 Oct, 2016
//    Description : initialize CAN to receive operator settings messages.
//    Notes       :
//******************************************************************************
{
  rx_DeluxeAuthenticationG55.initialize();
  rx_DeluxeAuthenticationG55.rx_id     .set_J1939ID(0, PROPRIETARY_B, G55_AUTHENTICATION_PS, SA_DISPLAY_CONTROLLER);
  rx_DeluxeAuthenticationG55.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);  
  rx_DeluxeAuthenticationG55.rx_callback = DeluxeAuthenticationG55_rx_callback;   
  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_DeluxeAuthenticationG55);
}

static void sendChallengeResponse(uint32_t result)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 19 Oct, 2016
//    Description : initialize CAN to receive operator settings messages.
//    Notes       :
//******************************************************************************
{
  hw_can_msg_t msg_data;

  msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, G55_AUTHENTICATION_PS, nvm_ecuid.j1939_source_address );
  msg_data.DLR = 8;
  msg_data.set_byte(0, 0x00);
  msg_data.set_byte(1, UNDEFINED);
  msg_data.set_word(1, result & 0xFFFF);
  msg_data.set_word(2, result >> 16);
  msg_data.set_word(3, 0xFFFF);
  
  CanCipher::inst.encipher(&msg_data);
        
  hw_can_txq[HWC_CAN0].send_msg(&msg_data);
}

static void sendChallenge(void)
//******************************************************************************
//    returns     : NONE.
//		        msg : Data to be sent.
//		Created By  : Al Liebel
//    Date Created: 20 Oct, 2016
//    Description : Sends authentication request.
//    Notes       :
//******************************************************************************
{
    hw_can_msg_t msg_data;
    static uint8_t msg_type = 0x01;

    srand(bsp_clock_us());
    uint32_t temp = rand();

    //calculate expected challenge response
    switch (msg_type)
    {
      case 0x01:  //Challenge type 1
          expected_challenge_response = (temp & 0xFFFF) * (temp >> 16);
          msg_data.set_byte(0, msg_type);
          msg_type = 2; 
      break;
        
      case 0x02: //Challenge type 2
          expected_challenge_response =  ((temp & 0xFFFF) ^ 0xAAAA) << 16;
          expected_challenge_response |= ((temp >> 16   ) ^ 0x5555);
          msg_data.set_byte(0, msg_type);
          msg_type = 1;
      break;
      
      default:
          expected_challenge_response = 0;
          msg_type = 1;
      break;
    } 
    
    //set message data
    msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, G55_AUTHENTICATION_PS, nvm_ecuid.j1939_source_address );
    msg_data.DLR = 8;
    msg_data.set_byte(1, UNDEFINED);
    msg_data.set_word(1, temp & 0xFFFF);
    msg_data.set_word(2, temp >> 16);
    msg_data.set_word(3, 0xFFFF);
    
    CanCipher::inst.encipher(&msg_data); 
     
    hw_can_txq[HWC_CAN0].send_msg(&msg_data);

}



static void update_AuxHydStatus_tx (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//		        msg : Data to be sent.
//		Created By  : Al Liebel
//    Date Created: 20 Oct, 2016
//    Description : Updates Aux Hyd Status Message data.
//    Notes       :
//******************************************************************************
{
    uint8_t tempByte = 0;

    #define AUX_DETENT_ACTIVE       1    
    #define AUX_DETENT_ERROR        2
    
    msg->set_byte(0, UNDEFINED);
    msg->set_byte(1, (state_AuxEnable != INACTIVE) ? ACTIVE : INACTIVE);
    msg->set_byte(2, UNDEFINED);
    msg->set_byte(3, UNDEFINED);
    
    //Detent Flow State Byte 4.0 - 2 bits
    if((state_Detent == BASE_DETENT) || (state_Detent == ROD_DETENT))
    {
        tempByte = AUX_DETENT_ACTIVE;
    }
    else if(state_Detent == ERR_DETENT)
    {
        tempByte = AUX_DETENT_ERROR;
    }
    
    //Detent Enable State Byte 4.2 - 2 bits
    tempByte |= (state_DetentEnable & 0x03) << 2;
    
    //Aux Flow Byte 4.4 - 4 bits
    if(aux_Flow < AUX_RELEASE_WAIT)
    {
        tempByte |= aux_Flow << 4;
    }
    msg->set_byte(4, tempByte);
    msg->set_byte(5, UNDEFINED);
    msg->set_byte(6, UNDEFINED);
    
    // Aux Relief Mode Byte 7.0 - 2 bits
    tempByte = state_AuxRelease & 0x03;
    
    // Second Aux Mode Byte 7.2 - 4 bits
    tempByte |= (cmd_Diverter & 0x01) << 2;
    msg->set_byte(7, tempByte);
}

static void initialize_AuxHydStatus_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//		Created By  : Boston Zachmann
//    Date Created: 7 Oct, 2016
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  tx_AuxHydStatus.initialize();
  tx_AuxHydStatus.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, AUX_HYD_CONTROL_PS, nvm_ecuid.j1939_source_address);
  tx_AuxHydStatus.set_send_rate(100);
  tx_AuxHydStatus.pre_tx_callback = update_AuxHydStatus_tx;  
  hw_can_tx_scheduler[HWC_CAN0].add_msg(&tx_AuxHydStatus);
}

static void JogShuttleRx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : Boston Zachmann
//    Date Created: 14 July, 2016
//    Description : Receive info from Jog Shuttle. 
//    Notes       :
//******************************************************************************
{
  btn_JogShuttleAux =    (msg->get_byte(3) & JOG_AUX_BUTTON_MASK);    
  btn_JogShuttleLights = (msg->get_byte(2) & JOG_LIGHTS_BUTTON_MASK) >> 2;   
}

static void initialize_JogShuttleRx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : Boston Zachmann
//    Date Created: 14 July, 2016
//    Description : initialize CAN msg from Jog Shuttle.
//    Notes       :
//******************************************************************************
{
  rx_JogButtonState.initialize();
  rx_JogButtonState.rx_id     .set_J1939ID(3, PROPRIETARY_B, JOG_BUTTON_STATE_PS, SA_JOG_SHUTTLE);
  rx_JogButtonState.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);

  rx_JogButtonState.rx_callback = JogShuttleRx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_JogButtonState);
  
}

static void AuxStatusCheck(void)
//******************************************************************************
//    returns     : NONE.
//		        
//		Created By  : Al Liebel
//    Date Created: 13 Oct, 2016
//    Description : Monitor Aux Hyd Status message variables for 
//                  any changes and send message on change
//                  if necessary since normal Tx Rate is slow
//******************************************************************************
{
    static uint8_t prev_state_AuxEnable;
    static uint8_t prev_state_Detent;
    static uint8_t prev_state_DetentEnable;
    static uint8_t prev_aux_Flow;
    static uint8_t prev_state_AuxRelease;
    static uint8_t prev_cmd_Diverter;
    
    if(( prev_state_AuxEnable    != state_AuxEnable    )
     ||( prev_state_Detent       != state_Detent       )
     ||( prev_state_DetentEnable != state_DetentEnable )
     ||( prev_aux_Flow           != aux_Flow           )
     ||( prev_state_AuxRelease   != state_AuxRelease   )
     ||( prev_cmd_Diverter       != cmd_Diverter      ))
    {
        tx_AuxHydStatus.SendRightNow();
        prev_state_AuxEnable = state_AuxEnable;
        prev_state_Detent = state_Detent;
        prev_state_DetentEnable = state_DetentEnable;
        prev_aux_Flow = aux_Flow;
        prev_state_AuxRelease = state_AuxRelease;
        prev_cmd_Diverter = cmd_Diverter;
    }
}

uint8_t getPhoneState(void)
//******************************************************************************
//    returns     : Phone state
//		        
//	  Created By  : Al Liebel
//    Date Created: 01 Aug, 2017
//    Description : gets phone state
//******************************************************************************
{
    return state_Phone;
}

void ap_DeluxeG55_update(void)
//******************************************************************************
//    returns     : NONE.
//		        
//	  Created By  : Al Liebel
//    Date Created: 20 Oct, 2016
//    Description : Periodically called function to handle 
//                  updates related to the Gen5.5 Display
//******************************************************************************
{
    static uint16_t challenge_interval = 100; //1 second
    static uint16_t response_timer = 0; 
    static uint16_t challenge_timer = 0;
    
    //Ensure Gen5 deluxe and Keyless keypad are cleared if we have Gen5.5 display
    if(flag_InitEERead && (eeMirror.deluxe_G5 != INACTIVE || eeMirror.keypad != INACTIVE))
    {
        eeMirror.deluxe_G5 = INACTIVE;
        eeMirror.keypad = INACTIVE;
        UpdateEEVariables(NOW);
    }
     
    //Reset message timing during crank in case controller drops out
    if(state_Engine == ENGINE_CRANKING)
    {
        rx_DeluxeStatusG55.msg_age_mS = 0;
        rx_JogButtonState.msg_age_mS = 0;  
    }
    msgAge_DeluxeG55 = rx_DeluxeStatusG55.msg_age_mS; 
    msgAge_JogShuttle = rx_JogButtonState.msg_age_mS;

    //Check for changes in aux states that require immediate CAN message 
    AuxStatusCheck(); 
    
    //Handle authenitication tasks once we have comm 
    if(state_DeluxeG55 != DELUXE_G55_UNDEFINED)
    {
        //Challenge timer
        if(challenge_timer >= challenge_interval)
        {
            sendChallenge();
            challenge_timer = 0;
            response_timer = 0;
        }
        else
        {
            challenge_timer++;
        }
        
        if(authDisplay == AUTHENTICATED)
        {
            challenge_interval = 6000; //60 seconds
        }
        else
        {
            challenge_interval = 100; //1 second
        }
        
        //Response timer
        if(response_timer < 50) //500msec
        {
            response_timer++;
        }
        else
        {
            expected_challenge_response = 0;
        }
        
        //Overall authentication state - both Main and Display need to be happy
        if(authMain == AUTHENTICATED && authDisplay == AUTHENTICATED)
        {
            auth_DeluxeG55 =  AUTHENTICATED;
        }
        else if(authMain == NOT_AUTHENTICATED || authDisplay == NOT_AUTHENTICATED)
        {
            auth_DeluxeG55 =  NOT_AUTHENTICATED;
        }
        else
        {
            auth_DeluxeG55 =  AUTHENTICATION_NA;
        }
    }
}

void ap_DeluxeG55_initialize(void)
//******************************************************************************
//    returns     : NONE.
//
//		Created By  : Boston Zachmann
//    Date Created: 7 Oct, 2016
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  initialize_DeluxeMainStatus_tx();
  initialize_VitalDataG55_tx();
  initialize_DeluxeStatusG55_rx();
  initialize_OperatorSettings_rx();
  initialize_AuxHydStatus_tx();
  initialize_JogShuttleRx();
  initialize_DeluxeAuthenticationG55_rx();
  
  state_DeluxeG55 = DELUXE_G55_UNDEFINED;
  state_Phone = PHONE_NA;

  actual_challenge_response = 0;
  expected_challenge_response = 0;
  authMain =  AUTHENTICATION_NA;
  authDisplay =  AUTHENTICATION_NA;
  auth_DeluxeG55 =  AUTHENTICATION_NA;
  
  CanCipher::inst.setSerialNumber(BOBCAT_SERIAL_NUMBER, 9);
}