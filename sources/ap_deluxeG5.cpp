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
* First written on 1 August, 2007 by Spencer Mindeman
*
* Module Description:
* Routines for interaction with the deluxe panel..
***************************************************************/

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "ap_can.h"
#include "ap_deluxeG5.h"
#include "ap_eeprom.h"
#include "ap_subs.h"
#include "global.h"

//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************


hw_can_txmsg tx_MainStatus;
hw_can_txmsg tx_PasswordData;
hw_can_txmsg tx_JobClock;
hw_can_txmsg tx_UserInfo;
hw_can_txmsg tx_ServiceData;
hw_can_txmsg tx_VitalData;

hw_can_rxmsg rx_DeluxeStatus;
hw_can_rxmsg rx_JobClock;
hw_can_rxmsg rx_UserData;
hw_can_rxmsg rx_ServiceData;
hw_can_rxmsg rx_PwdData;
hw_can_rxmsg rx_UserName;
hw_can_rxmsg rx_DeluxeKeypad;
hw_can_rxmsg rx_DeluxeProg;

uint8_t count_Vital;

bool flag_PasswordSent;
bool flag_Sent;
bool flag_NewUserData;
bool flag_SendWarningHistory;
bool flag_SentWarningHistory;
uint8_t flag_DeluxeProg;

uint8_t update_UserID;
uint8_t dlxMode;

uint8_t msg_Counter;

vitalItem vitalDisplay[7];

J1939_TP_tx Deluxe_TP_tx;
J1939_TP_rx Deluxe_TP_rx;

uint8_t msgData[30];
J1939_msg_t Deluxe_TP_msg;


DDPSwitchUnion ddpSwitchStatus;

#define NUMBER_REPEAT_MSGS 0


void update_ServiceData(uint8_t id)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 19 Dec, 2008
//    Description : Recalculates the checksum for the service data.
//    Notes       :
//******************************************************************************
{
  uint8_t * mPtr;
  uint8_t checksum;
  uint16_t tempWord;

  // Update checksum for service data.
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

  // Send out CAN message to update screen with new data.
  hw_can_msg_t msg_data;
  msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, SERVICE_DATA_PS ,nvm_ecuid.j1939_source_address );
  msg_data.DLR = 8;
  msg_data.set_byte(0,id);
  msg_data.set_byte(1,eeMirror.queueServiceIntervals.serviceInterval[id].state);

  tempWord = (uint16_t)((actualHourMeter - eeMirror.queueServiceIntervals.serviceInterval[id].reset_time)/HOUR_METER_TO_HOUR_FCT);
  msg_data.set_byte(2,(uint8_t)(tempWord>>8));
  msg_data.set_byte(3,(uint8_t)(tempWord));

  tempWord = eeMirror.queueServiceIntervals.serviceInterval[id].interval;
  msg_data.set_byte(4,(uint8_t)(tempWord>>8));
  msg_data.set_byte(5,(uint8_t)(tempWord));

  msg_data.set_byte(6,eeMirror.queueServiceIntervals.serviceInterval[id].text);
  hw_can_txq[HWC_CAN0].send_msg(&msg_data);
}

void send_DeluxeG5_StartUpData(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Nov, 2008
//    Description : Sends out startup messages for deluxe panel.
//    Notes       :
//******************************************************************************
{
  hw_can_msg_t msg_data;
  uint32_t tempDWord;
  uint16_t tempWord;
  uint8_t  tempByte;
  static uint16_t wait_Count = 0;
  static bool flag_TPSent = 0;

  switch(dlxMode)
  {
    case DLX_STARTUP_SEND_PASSWORDS:
      if(msg_Counter == 0)
      {
        msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, PASSWORD_DATA_PS ,nvm_ecuid.j1939_source_address );
        msg_data.DLR = 7;
        msg_data.set_byte(0,0);
        msg_data.set_byte(1,NO_CHANGE);

        msg_data.set_byte(2,((((MASTER_PWD[0] == 0)?0x0F:(MASTER_PWD[0] & 0x0F)) << 4) + ((MASTER_PWD[1] == 0)?0x0F:(MASTER_PWD[1]) & 0x0F)));
        msg_data.set_byte(3,((((MASTER_PWD[2] == 0)?0x0F:(MASTER_PWD[2] & 0x0F)) << 4) + ((MASTER_PWD[3] == 0)?0x0F:(MASTER_PWD[3]) & 0x0F)));
        msg_data.set_byte(4,((((MASTER_PWD[4] == 0)?0x0F:(MASTER_PWD[4] & 0x0F)) << 4) + ((MASTER_PWD[5] == 0)?0x0F:(MASTER_PWD[5]) & 0x0F)));
        msg_data.set_byte(5,((((MASTER_PWD[6] == 0)?0x0F:(MASTER_PWD[6] & 0x0F)) << 4) + ((MASTER_PWD[7] == 0)?0x0F:(MASTER_PWD[7]) & 0x0F)));
        msg_data.set_byte(6,((((MASTER_PWD[8] == 0)?0x0F:(MASTER_PWD[8] & 0x0F)) << 4) + ((MASTER_PWD[9] == 0)?0x0F:(MASTER_PWD[9]) & 0x0F)));
        hw_can_txq[HWC_CAN0].send_msg(&msg_data);
        msg_Counter++;
      }
      else if(msg_Counter <= NUMBER_OF_USERS)
      {
        msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, PASSWORD_DATA_PS ,nvm_ecuid.j1939_source_address );
        msg_data.DLR = 7;
        msg_data.set_byte(0,msg_Counter);
        msg_data.set_byte(1,NO_CHANGE);

        msg_data.set_byte(2,((((eeMirror.password[msg_Counter-1].value[0] == 0)?0x0F:(eeMirror.password[msg_Counter-1].value[0] & 0x0F)) << 4) + ((eeMirror.password[msg_Counter-1].value[1] == 0)?0x0F:(eeMirror.password[msg_Counter-1].value[1]) & 0x0F)));
        msg_data.set_byte(3,((((eeMirror.password[msg_Counter-1].value[2] == 0)?0x0F:(eeMirror.password[msg_Counter-1].value[2] & 0x0F)) << 4) + ((eeMirror.password[msg_Counter-1].value[3] == 0)?0x0F:(eeMirror.password[msg_Counter-1].value[3]) & 0x0F)));
        msg_data.set_byte(4,((((eeMirror.password[msg_Counter-1].value[4] == 0)?0x0F:(eeMirror.password[msg_Counter-1].value[4] & 0x0F)) << 4) + ((eeMirror.password[msg_Counter-1].value[5] == 0)?0x0F:(eeMirror.password[msg_Counter-1].value[5]) & 0x0F)));
        msg_data.set_byte(5,((((eeMirror.password[msg_Counter-1].value[6] == 0)?0x0F:(eeMirror.password[msg_Counter-1].value[6] & 0x0F)) << 4) + ((eeMirror.password[msg_Counter-1].value[7] == 0)?0x0F:(eeMirror.password[msg_Counter-1].value[7]) & 0x0F)));
        msg_data.set_byte(6,((((eeMirror.password[msg_Counter-1].value[8] == 0)?0x0F:(eeMirror.password[msg_Counter-1].value[8] & 0x0F)) << 4) + ((eeMirror.password[msg_Counter-1].value[9] == 0)?0x0F:(eeMirror.password[msg_Counter-1].value[9]) & 0x0F)));
        hw_can_txq[HWC_CAN0].send_msg(&msg_data);
        msg_Counter++;
      }
      else
      {
        dlxMode = DLX_STARTUP_SEND_JOB_CLOCKS;
        msg_Counter = 0;   // want to start counter at 2 for next set of data as owner and user (0 and 1) are not used.
      }
    break;

    case DLX_STARTUP_SEND_JOB_CLOCKS:
      if(msg_Counter <= NUMBER_OF_USERS)
      {
        msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, JOB_CLOCK_PS ,nvm_ecuid.j1939_source_address );
        msg_data.DLR = 8;

        tempWord = (uint16_t)((actualHourMeter - eeMirror.jobClock)/HOUR_METER_TO_MINUTE_FCT);
        msg_data.set_byte(0,(uint8_t)(tempWord >> 8));
        msg_data.set_byte(1,(uint8_t)tempWord);

        tempByte = (eeMirror.jobClockLock << 1) | (eeMirror.userInfo[msg_Counter].locks & USER_JOBCLOCK_TOGGLE);
        msg_data.set_byte(2, tempByte);  //Job clock status

        msg_data.set_byte(3,msg_Counter);


        tempWord = (uint16_t)(GetUserJob(msg_Counter)/HOUR_METER_TO_MINUTE_FCT);//(uint16_t)(eeMirror.userInfo[msg_Counter].jobClock/HOUR_METER_TO_MINUTE_FCT);
        msg_data.set_byte(4, (uint8_t)(tempWord >> 8));  //User Job clock
        msg_data.set_byte(5, (uint8_t)tempWord);

        if(eeMirror.ee_autoIdleTime < CONSTANT_DATA->AUTOIDLE_IDLE_DELAY/10)
        {
          msg_data.set_byte(6,(uint8_t)(CONSTANT_DATA->AUTOIDLE_IDLE_DELAY/10));
        }
        else
        {
          msg_data.set_byte(6, eeMirror.ee_autoIdleTime);
        }

        msg_data.set_byte(7, (uint8_t)(count_GlowPlug/10));

        hw_can_txq[HWC_CAN0].send_msg(&msg_data);
        msg_Counter++;
      }
      else
      {
        msg_Counter = 0;
         //dlxMode = DLX_STARTUP_SEND_USER_DATA;
        dlxMode = DLX_STARTUP_SEND_USER_NAME;
      }
    break;
    
    case DLX_STARTUP_SEND_USER_DATA:
      if(msg_Counter <= NUMBER_OF_USERS)
      {
        msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, USER_INFO_PS ,nvm_ecuid.j1939_source_address );
        msg_data.DLR = 7;
        msg_data.set_byte(0,msg_Counter); //offset user id as 0 is master and 1 is owner but they do not have user info
        msg_data.set_byte(1,(uint8_t)(eeMirror.userInfo[msg_Counter].locks));
        msg_data.set_byte(2,(uint8_t)(eeMirror.userInfo[msg_Counter].locks>>8));

        tempDWord = GetUserIdle(msg_Counter)/HOUR_METER_TO_MINUTE_FCT;
        msg_data.set_byte(3,(uint8_t)(tempDWord >> 8));
        msg_data.set_byte(4,(uint8_t)tempDWord);
        msg_data.set_byte(5,(uint8_t)(eeMirror.userInfo[msg_Counter].fuelConsumption >> 8));
        msg_data.set_byte(6,(uint8_t)(eeMirror.userInfo[msg_Counter].fuelConsumption));
        hw_can_txq[HWC_CAN0].send_msg(&msg_data);
        msg_Counter++;
      }
      else
      {
        msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, USER_INFO_PS ,nvm_ecuid.j1939_source_address );
        msg_data.DLR = 7;
        msg_data.set_byte(0,254); //offset user id as 0 is master and 1 is owner but they do not have user info
        msg_data.set_byte(1,255);
        msg_data.set_byte(2,255);

        tempDWord = eeMirror.machineIdleTime/HOUR_METER_TO_MINUTE_FCT;
        msg_data.set_byte(3,(uint8_t)(tempDWord >> 8));
        msg_data.set_byte(4,(uint8_t)tempDWord);

        tempDWord = can_FuelConsumption - eeMirror.machineFuelConsumption;
        msg_data.set_byte(5,(uint8_t)(tempDWord >> 8));
        msg_data.set_byte(6,(uint8_t)(tempDWord));
        hw_can_txq[HWC_CAN0].send_msg(&msg_data);

        msg_Counter = 0;
        //dlxMode = DLX_STARTUP_SEND_USER_NAME;
        dlxMode = DLX_STARTUP_SEND_DEALER_NAME;
      }

    break;
    
    case DLX_STARTUP_SEND_USER_NAME:
      if(msg_Counter <= NUMBER_OF_USERS)
      {
        msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, USER_NAME_PS ,nvm_ecuid.j1939_source_address );
        msg_data.DLR = 8;
        msg_data.set_byte(0,msg_Counter);
        msg_data.set_byte(1,(uint8_t)(eeMirror.userInfo[msg_Counter].user_name[0]));
        msg_data.set_byte(2,(uint8_t)(eeMirror.userInfo[msg_Counter].user_name[1]));
        msg_data.set_byte(3,(uint8_t)(eeMirror.userInfo[msg_Counter].user_name[2]));
        msg_data.set_byte(4,(uint8_t)(eeMirror.userInfo[msg_Counter].user_name[3]));
        msg_data.set_byte(5,(uint8_t)(eeMirror.userInfo[msg_Counter].user_name[4]));
        msg_data.set_byte(6,(uint8_t)(eeMirror.userInfo[msg_Counter].user_name[5]));
        msg_data.set_byte(7,(uint8_t)(eeMirror.userInfo[msg_Counter].user_name[6]));
        hw_can_txq[HWC_CAN0].send_msg(&msg_data);
        msg_Counter++;
      }
      else
      {
        msg_Counter = 0;
        //dlxMode = DLX_STARTUP_SEND_DEALER_NAME;
        dlxMode = DLX_STARTUP_SEND_USER_DATA;
        wait_Count = 0;
      }

    break;

    case DLX_STARTUP_SEND_DEALER_NAME:
      msg_Counter = 0;

      if(Deluxe_TP_tx.Idle())
      {
        Deluxe_TP_msg.id.set_J1939_DA(0xFF);
        Deluxe_TP_msg.id.set_J1939ID(PRIORITY_6,  PROPRIETARY_B, DEALER_DATA_PS,nvm_ecuid.j1939_source_address);

        msgData[0] = CMD_DEALER_NAME;

        for(uint8_t i = 0; i < 25; i++)
        {
          msgData[i+1] = DEALER_NAME[i];
        }

        Deluxe_TP_msg.length = 26;

        Deluxe_TP_msg.data = msgData;
        Deluxe_TP_tx.SendMsg(&Deluxe_TP_msg);

        dlxMode = DLX_STARTUP_SEND_DEALER_NUMBER;
        flag_TPSent = TRUE;
        wait_Count = 0;
      }
    break;

    case DLX_STARTUP_SEND_DEALER_NUMBER:
      msg_Counter = 0;

      if((flag_TPSent == TRUE) && (wait_Count < 30))
      {
        wait_Count++;
      }

      if((Deluxe_TP_tx.Idle()) && (wait_Count >= 30))
      {
        Deluxe_TP_msg.id.set_J1939_DA(0xFF);
        Deluxe_TP_msg.id.set_J1939ID(PRIORITY_6,  PROPRIETARY_B, DEALER_DATA_PS,nvm_ecuid.j1939_source_address);

        msgData[0] = CMD_DEALER_PHONE;

        for(uint8_t i = 0; i < 25; i++)
        {
          msgData[i+1] = DEALER_NUMBER[i];
        }

        Deluxe_TP_msg.length = 26;

        Deluxe_TP_msg.data = msgData;
        Deluxe_TP_tx.SendMsg(&Deluxe_TP_msg);

        dlxMode = DLX_STARTUP_SEND_SERVICE_INTERVALS;
      }
    break;

    case DLX_STARTUP_SEND_SERVICE_INTERVALS:
      if(msg_Counter == 0)
      {
        msg_data.set_byte(1,(uint8_t)eeMirror.serviceClockExpired);
        tempWord = (uint16_t)((actualHourMeter - eeMirror.serviceClockResetTime)/HOUR_METER_TO_HOUR_FCT);
        msg_data.set_byte(2,(uint8_t)(tempWord>>8));
        msg_data.set_byte(3,(uint8_t)(tempWord));

        tempWord = (uint16_t)(eeMirror.serviceClockLength/HOUR_METER_TO_HOUR_FCT);
        msg_data.set_byte(4,(uint8_t)(tempWord >> 8));
        msg_data.set_byte(5,(uint8_t)(tempWord));
        msg_Counter++;
      }
      else
      {
        msg_Counter = 0;
        dlxMode = DLX_STARTUP_DONE;
      }
    break;

    default:
    break;
  }
}


void DeluxeStatus_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Nov, 2008
//    Description : Gets the info from the deluxe status message.
//    Notes       :
//******************************************************************************
{
  uint8_t tempByte = 0;

  if((!eeMirror.deluxe_G5) && (flag_InitEERead))
  {
    eeMirror.deluxe_G5 = ACTIVE;
    eeMirror.keypad = INACTIVE;

    UpdateEEVariables(NOW);
  }

  //BYTE 1 STUFF
  tempByte = msg->get_byte(1);
  ddpSwitchStatus.data.inWarningPage = (tempByte & G5_IN_WARNING_PAGE);
  ddpSwitchStatus.data.inInitPasswordScreen = ((tempByte & G5_IN_PASSWORD_SCREEN) >> 1);
  ddpSwitchStatus.data.inInitPasswordFailedScreen = ((tempByte & G5_IN_PASSWORD_FAIL) >> 2);
  ddpSwitchStatus.data.inUserLogScreen = (tempByte & G5_IN_USER_LOG_SCREEN) >> 3;

  if(ddpSwitchStatus.data.inWarningPage)
  {
    flag_ActiveWarning = INACTIVE;
  }
  if((tempByte & G5_GET_WARNING_HISTORY_BIT) && (tempByte != UNDEFINED) && (!flag_SentWarningHistory))
  {
    flag_SendWarningHistory = TRUE;
  }
  else if((tempByte & G5_GET_WARNING_HISTORY_BIT) == 0)
  {
    flag_SendWarningHistory = FALSE;
    flag_SentWarningHistory = FALSE;
  }

  //BYTE 2 STUFF
  tempByte = msg->get_byte(2);

  ddp_MachineLock = tempByte & G5_PASSWORD_ACCEPTED;

  if((tempByte != UNDEFINED) && ((tempByte & G5_NEWLY_BOOTED_BIT) == G5_NEWLY_BOOTED_BIT) && (dlxMode == DLX_STARTUP_IDLE))
  {
    //flag_PasswordSent = TRUE;
    dlxMode = DLX_STARTUP_SEND_PASSWORDS;
    msg_Counter = 0;
  }
  else if((tempByte != UNDEFINED) && ((tempByte & G5_NEWLY_BOOTED_BIT) == 0x00))
  {
    //flag_PasswordSent = FALSE;  // Set to false so if panel starts up again due to power glitch we get back and running again.
    dlxMode = DLX_STARTUP_IDLE;
  }

  if((tempByte & G5_GET_NEXT_WARNING_BIT)  && (tempByte != UNDEFINED))
  {
    ddpSwitchStatus.data.getNextWarning = TRUE;
  }

  if(state_System == SYS_NORMAL)
  {
    //BYTE 3 STUFF
    tempByte = msg->get_byte(3);

    if((tempByte & G5_PWD_LOCK_BIT) && (tempByte != UNDEFINED) && (state_Engine != ENGINE_CRANKING))
    {
      eeMirror.passwordLock = !eeMirror.passwordLock;
      UpdateEEVariables(NOW);
      tx_MainStatus.SendRightNow();
    }

    tempByte = msg->get_byte(4);
    if((current_user == UNDEFINED) && ((msg->get_byte(2) & G5_NEWLY_BOOTED_BIT) != G5_NEWLY_BOOTED_BIT ) &&
       (tempByte != UNDEFINED))
    {
      current_user = tempByte;
      QueueCurrentUser(current_user,(uint16_t)(actualHourMeter/HOUR_METER_TO_HOUR_FCT));
    }
  }
}


static void initialize_DeluxeStatus_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Nov, 2008
//    Description : initialize CAN to receive deluxe status messages.
//    Notes       :
//******************************************************************************
{
  rx_DeluxeStatus.initialize();
  rx_DeluxeStatus.rx_id     .set_J1939ID(0, PROPRIETARY_B, DELUXE_STATUS_PS, SA_DELUXE_PANEL);
  rx_DeluxeStatus.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  rx_DeluxeStatus.rx_callback = DeluxeStatus_rx_callback;
  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_DeluxeStatus);
}


void update_MainStatus_tx (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates Engine RPM TX Message data.
//    Notes       :
//******************************************************************************
{
  uint8_t tempByte;

    // TTP#3076: Want to prevent the engine from cranking early but still want
  // to show the wait to start while the glow plugs are active.  Removed the
  // Glow plug state from the model to move from init to not running so it
  // could be used as the delay.  So if glow plugs are active and engine isn't
  // running, show the wait to start.
  if((ecu_GlowPlug == ACTIVE) && (state_Engine == ENGINE_RUNNING))
  {
    msg->set_byte(0, ENGINE_INITIALIZE);
  }
  else
  {
    msg->set_byte(0, state_Engine);
  }

  tempByte = 0;
  if(eeMirror.passwordLock)
  {
    tempByte |= G5_PWD_LOCK_BIT;
  }
  else
  {
    tempByte &= ~G5_PWD_LOCK_BIT;
  }

  if(eeMirror.jobClockLock)
  {
    tempByte |= G5_JOB_CLOCK_LOCK_BIT;
  }
  else
  {
    tempByte &= ~G5_JOB_CLOCK_LOCK_BIT;
  }

  if(state_MachineLock)
  {
    tempByte |= G5_MACHINE_LOCK_BIT;
  }
  else
  {
    tempByte &= ~G5_MACHINE_LOCK_BIT;
  }

  msg->set_byte(1, tempByte);  //Lock states
  msg->set_byte(2, 0);  //Lock states

  tempByte = 0;
  if((state_HOT == EXTREMELY_HIGH) || (state_HOT == SHUTDOWN))
  {
    tempByte = HOT_SHUTDOWN_BIT;
  }


  else if(((state_ECT == EXTREMELY_HIGH) && (CONSTANT_DATA->ECU_FUNCTION == NON_FUNCTIONAL)) || (state_ECT == PRE_SHUTDOWN) || (state_ECT == SHUTDOWN))
  {
    tempByte = ECT_SHUTDOWN_BIT;
  }

  else if((state_EngineSpeed == EXTREMELY_HIGH) || (state_EngineSpeed == SHUTDOWN))
  {
     tempByte = RPM_SHUTDOWN_BIT;
  }

  else if((state_EOP == EXTREMELY_LOW) || (state_EOP == SHUTDOWN))
  {
    tempByte = EOP_SHUTDOWN_BIT;
  }

  else if(state_EngineSpeedDerate == SHUTDOWN)
  {
    tempByte = ES_DERATE_SHUTDOWN_BIT;
  }

  else if((state_FuelTemp == PRE_SHUTDOWN) || (state_FuelTemp == SHUTDOWN))
  {
    tempByte = FUEL_TEMP_SHUTDOWN;
  }

  msg->set_byte(3, tempByte);  //Shutdowns
  msg->set_byte(4, current_user);
  msg->set_byte(5, 1); // CAN Version

  tempByte = 0;
  if(flag_ActiveWarning)
  {
    tempByte |= ACTIVE_WARNING_BIT;
  }

  if(CONSTANT_DATA->ECU_FUNCTION == ECU_J1939)
  {
    tempByte |= (2 << 1); //Setup for Doosan ECU
  }

  if(state_AutoIdleEnable == ACTIVE)
  {
    tempByte |= (1 << 4);
  }

    //Cold Display
  if(state_InfoSecondary == DISPLAY_COLD)
  {
    tempByte |= 0x40; //On
  }
  else if (state_InfoSecondary == DISPLAY_FLASH_COLD)
  {
    tempByte |= 0x80; //Flash
  }

  msg->set_byte(6, tempByte);


  //Eco Mode
  if(CONSTANT_DATA->ECO_MODE_FUNCTION == NON_FUNCTIONAL)
  {
    tempByte = 0;
  }
  else
  {
    tempByte = 1;
  }

  tempByte |= state_EcoMode << 1;

  //Adjustable Aux
  if(CONSTANT_DATA->AUX_ADJ_FLOW_FUNCTION != NON_FUNCTIONAL)
  {
    tempByte |= 0x20;
  }

  //Second Aux
  if(cmd_Diverter == ACTIVE)
  {
    tempByte |= 0x80;
  }


  msg->set_byte(7, tempByte);



}

static void initialize_MainStatus_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  tx_MainStatus.initialize();
  tx_MainStatus.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, MAIN_STATUS_PS, nvm_ecuid.j1939_source_address);
  tx_MainStatus.set_send_rate(10);
  tx_MainStatus.pre_tx_callback = update_MainStatus_tx;
  hw_can_tx_scheduler[HWC_CAN0].add_msg(&tx_MainStatus);
}

void JobClock_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Nov, 2008
//    Description : Gets state of the job clock from the deluxe.
//    Notes       :
//******************************************************************************
{
  uint8_t state_JobClockUser;
  uint8_t * bytePtr;
  uint8_t temp;

  if((state_DeluxeG5 == NORMAL) && (state_System == SYS_NORMAL))
  {
    switch(msg->get_byte(2))
    {
      case JOB_CLOCK_ENABLE:
        eeMirror.jobClockLock = !eeMirror.jobClockLock;
        UpdateEEVariables(NOW);
        newJobClockVerification = TRUE;
        newJobClockNumber = current_user;
      break;

      case JOB_CLOCK_RESET:
        eeMirror.jobClock = actualHourMeter;
        eeMirror.machineIdleTime = 0;
        eeMirror.machineFuelConsumption = can_FuelConsumption;
        UpdateEEVariables(NOW);
        newJobClockVerification = TRUE;
        newJobClockNumber = current_user;
      break;

      case USER_JOB_CLOCK_ENABLE:
        state_JobClockUser = msg->get_byte(3);

        if(state_JobClockUser < NUMBER_TOTAL_USERS)
        {
          if(eeMirror.userInfo[state_JobClockUser].locks & USER_JOBCLOCK_TOGGLE)
          {
            //Locked so unlock
            eeMirror.userInfo[state_JobClockUser].locks &= ~USER_JOBCLOCK_TOGGLE;
          }
          else
          {
            //unlocked so lock
            eeMirror.userInfo[state_JobClockUser].locks |= USER_JOBCLOCK_TOGGLE;
          }

          eeMirror.userInfo[state_JobClockUser].checksum = 0;

          bytePtr = (uint8_t *) &eeMirror.userInfo[state_JobClockUser].locks;

          for (; bytePtr < (uint8_t *) &eeMirror.userInfo[state_JobClockUser].checksum; bytePtr++)
          {
            eeMirror.userInfo[state_JobClockUser].checksum += *bytePtr;
          }// end for

          eeMirror.userInfo[state_JobClockUser].checksum = ~eeMirror.userInfo[state_JobClockUser].checksum + 1;

          eeTimeToUpdateMirror = TRUE;
          newJobClockNumber = state_JobClockUser;
          newJobClockVerification = TRUE;
        }

      break;

      case USER_JOB_CLOCK_RESET:
        state_JobClockUser = msg->get_byte(3);

        if(state_JobClockUser < NUMBER_TOTAL_USERS)
        {
          eeMirror.userInfo[state_JobClockUser].jobClock = 0;
          eeMirror.userInfo[state_JobClockUser].jobClockUpper = 0;

          eeMirror.userInfo[state_JobClockUser].idleTime = 0;
          eeMirror.userInfo[state_JobClockUser].idleTimeUpper = 0;
          eeMirror.userInfo[state_JobClockUser].fuelConsumption = 0;

          eeMirror.userInfo[state_JobClockUser].checksum = 0;

          bytePtr = (uint8_t *) &eeMirror.userInfo[state_JobClockUser].locks;

          for (; bytePtr < (uint8_t *) &eeMirror.userInfo[state_JobClockUser].checksum; bytePtr++)
          {
            eeMirror.userInfo[state_JobClockUser].checksum += *bytePtr;
          }// end for

          eeMirror.userInfo[state_JobClockUser].checksum = ~eeMirror.userInfo[state_JobClockUser].checksum + 1;

          eeTimeToUpdateMirror = TRUE;
          newJobClockVerification = TRUE;
        }
      break;

      case AUTO_IDLE_UPDATE:

        temp = msg->get_byte(6);

        if(temp < CONSTANT_DATA->AUTOIDLE_IDLE_DELAY/10)
        {
          eeMirror.ee_autoIdleTime = CONSTANT_DATA->AUTOIDLE_IDLE_DELAY/10;
        }
        else
        {
          eeMirror.ee_autoIdleTime = temp;
        }

        UpdateEEVariables(NOW);

      break;

      default:
      break;
    }
  }
}

static void initialize_JobClock_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Nov, 2008
//    Description : initialize CAN to receive deluxe status messages.
//    Notes       :
//******************************************************************************
{
  rx_JobClock.initialize();
  rx_JobClock.rx_id     .set_J1939ID(0, PROPRIETARY_B, JOB_CLOCK_PS, SA_DELUXE_PANEL);
  rx_JobClock.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  rx_JobClock.rx_callback = JobClock_rx_callback;
  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_JobClock);
}

void update_JobClock_tx (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates job clock message data.
//    Notes       :
//******************************************************************************
{
  uint16_t tempWord;
  uint8_t  tempByte;

  tempWord = (uint16_t)((actualHourMeter - eeMirror.jobClock)/HOUR_METER_TO_MINUTE_FCT);

  msg->set_byte(0, (uint8_t)(tempWord >> 8));
  msg->set_byte(1, (uint8_t)(tempWord));

  tempByte = (eeMirror.jobClockLock << 1) | (eeMirror.userInfo[current_user].locks & USER_JOBCLOCK_TOGGLE);
  msg->set_byte(2, tempByte);  //Job clock status
  msg->set_byte(3, current_user);  //user currently logged in

  tempWord = (uint16_t)(GetUserJob(current_user)/HOUR_METER_TO_MINUTE_FCT);//(eeMirror.userInfo[current_user].jobClock/HOUR_METER_TO_MINUTE_FCT);
  msg->set_byte(4, (uint8_t)(tempWord >> 8));  //User Job clock
  msg->set_byte(5, (uint8_t)tempWord);
  if(eeMirror.deluxe_G5 == ACTIVE)
  {
    if(eeMirror.ee_autoIdleTime < CONSTANT_DATA->AUTOIDLE_IDLE_DELAY/10)
    {
      msg->set_byte(6,(uint8_t)(CONSTANT_DATA->AUTOIDLE_IDLE_DELAY/10));
    }
    else
    {
      msg->set_byte(6, eeMirror.ee_autoIdleTime);
    }
  }
  else
  {
    msg->set_byte(6, UNDEFINED);
  }

  msg->set_byte(7, (uint8_t)(count_GlowPlug/10));
}

static void initialize_JobClock_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  tx_JobClock.initialize();
  tx_JobClock.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, JOB_CLOCK_PS, nvm_ecuid.j1939_source_address);
  tx_JobClock.set_send_rate(100);
  tx_JobClock.pre_tx_callback = update_JobClock_tx;
  hw_can_tx_scheduler[HWC_CAN0].add_msg(&tx_JobClock);
}

void update_UserInfo_tx (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates job clock message data.
//    Notes       :
//******************************************************************************
{
  uint32_t tempDWord;
  static uint8_t index=0;

  if(index == 0)
  {
    msg->set_byte(0,current_user); //offset user id as 0 is master and 1 is owner but they do not have user info
    msg->set_byte(1,(uint8_t)(eeMirror.userInfo[current_user].locks));
    msg->set_byte(2,(uint8_t)(eeMirror.userInfo[current_user].locks>>8));

    tempDWord = GetUserIdle(current_user)/HOUR_METER_TO_MINUTE_FCT;
    msg->set_byte(3,(uint8_t)(tempDWord >> 8));
    msg->set_byte(4,(uint8_t)tempDWord);
    msg->set_byte(5,(uint8_t)(eeMirror.userInfo[current_user].fuelConsumption >> 8));//current_FuelConsumption >> 8));
    msg->set_byte(6,(uint8_t)(eeMirror.userInfo[current_user].fuelConsumption));//current_FuelConsumption));


    index++;
  }
  else   // send overall info info
  {
    msg->set_byte(0,254); //offset user id as 0 is master and 1 is owner but they do not have user info
    msg->set_byte(1,255);
    msg->set_byte(2,255);

    tempDWord = eeMirror.machineIdleTime/HOUR_METER_TO_MINUTE_FCT;
    msg->set_byte(3,(uint8_t)(tempDWord >> 8));
    msg->set_byte(4,(uint8_t)tempDWord);

    tempDWord = can_FuelConsumption - eeMirror.machineFuelConsumption;
    msg->set_byte(5,(uint8_t)(tempDWord >> 8));
    msg->set_byte(6,(uint8_t)(tempDWord));
    index = 0;
  }

}

static void initialize_UserInfo_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  tx_UserInfo.initialize();
  tx_UserInfo.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, USER_INFO_PS, nvm_ecuid.j1939_source_address);
  tx_UserInfo.set_send_rate(250);
  tx_UserInfo.pre_tx_callback = update_UserInfo_tx;
  hw_can_tx_scheduler[HWC_CAN0].add_msg(&tx_UserInfo);
}

void update_VitalData_tx (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates job clock message data.
//    Notes       :
//******************************************************************************
{
 /**************************************************************
  0.0 4   Screen location Indicates for which screen location the data in 0 -Maintenance Clock
          the message is relevant.  Vitals and service                    1 - screen position 1
          intervals shall use this parameter to define a                  2 - screen position 2
          screen position                                                 3 - screen position 3
                                                                          4 - screen position 4
                                                                          5 - screen position 5
                                                                          6 - screen position 6
  0.4 4   Units ID  Shall indicate which units from the units
          database to be displayed.  The units shall be
          communicated in SI units.  Any conversion of
          units shall take place by the receiving unit.

  1.0 8   Radix location  Indication the location of the radix.  Amount to    0 - no radix
          offset the Radix current value  1234, scale 0 =                     1 - tenths shall be used
          1234; 1234, scale 1 = 123.4; 1234, scale 2 =                        2 - hundredths shall be used
          12.34
  1.0 16  Vitals Warning Level

  2.0 8   Color value Indicate the color to be utilized                       0 - White (default)
                                                                              1 - Yellow
                                                                              2 - Red
  3.0 16  Vitals Shutdown Level

  5.0 16  Vitals Current Level Value

  7.0 8   Icon ID number  Indicates which icon should be displayed.           0 - No icon
          Used with service and vital messages to
          indicate which ICON in the ICON database
          should be displayed
  **************************************************************/

  uint16_t tempWord;
  uint8_t num_Vitals;
  //10 = RPM,20 = BATT, 30 = ECT, 40 = HOT,  50 = EOP, 60 = Fuel Usage, 70 = EOT

  msg->set_byte(0, ((count_Vital+1) << 4) + (vitalDisplay[count_Vital].units & 0x0F));
  msg->set_byte(1, SCALE_ZERO);
  msg->set_byte(2, ICON_DEFAULT);
  msg->set_byte(7, vitalDisplay[count_Vital].icon);

  switch(vitalDisplay[count_Vital].icon)
  {
    case VITAL_ICON_RPM:
      msg->set_byte(5,(uint8_t)(flt_EngineSpeed>>8));
      msg->set_byte(6,(uint8_t)(flt_EngineSpeed));

      if(state_EngineSpeed == HIGH)
      {
        msg->set_byte(2, ICON_YELLOW);
      }
      else if((state_EngineSpeed == EXTREMELY_HIGH) || (state_EngineSpeed == SHUTDOWN))
      {
        msg->set_byte(2, ICON_RED);
      }
    break;

    case VITAL_ICON_BATTERY:
      //tempWord = calc_VBattery/256;
      tempWord = (calcFlt_VBattery * 10) >> 8;

      msg->set_byte(1, SCALE_ONE);
      msg->set_byte(5,(uint8_t)(tempWord>>8));
      msg->set_byte(6,(uint8_t)(tempWord));

      if((state_VBattery == LOW) || (state_VBattery == HIGH) || (state_Alternator == LOW))
      {
        msg->set_byte(2, ICON_YELLOW);
      }
      else if((state_VBattery == EXTREMELY_LOW) || (state_VBattery == EXTREMELY_HIGH) || (state_Alternator == HIGH))
      {
        msg->set_byte(2, ICON_RED);
      }
    break;

    case VITAL_ICON_EOP:
      if(CONSTANT_DATA->FAST_TRAVEL_FUNCTION == NON_FUNCTIONAL)   //Temporary for fast travel R&D
      {
        
      msg->set_byte(5,(uint8_t)(flt_EOP>>8));
      msg->set_byte(6,(uint8_t)flt_EOP);
      }
      else
      {
      msg->set_byte(5,(uint8_t)(pressure_TorqueLimiter>>8));
      msg->set_byte(6,(uint8_t)pressure_TorqueLimiter);
      }
        

      if(state_EOP == LOW)
      {
        msg->set_byte(2, ICON_YELLOW);
      }
      else if((state_EOP == EXTREMELY_LOW) || (state_EOP == SHUTDOWN))
      {
        msg->set_byte(2, ICON_RED);
      }

    break;

    /*case VITAL_ICON_HCP:
      msg->set_byte(5,(uint8_t)(flt_HCP>>8));
      msg->set_byte(6,(uint8_t)flt_HCP);

      if((state_HCP == LOW) || (state_HCP == HIGH))
      {
        msg->set_byte(2, ICON_YELLOW);
      }
      else if((state_HCP == EXTREMELY_LOW) || (state_HCP == EXTREMELY_HIGH) || (state_HCP == SHUTDOWN))
      {
        msg->set_byte(2, ICON_RED);
      }
    break;  */

    case VITAL_ICON_ECT:
      msg->set_byte(5,(uint8_t)(flt_ECT>>8));
      msg->set_byte(6,(uint8_t)flt_ECT);

      if(state_ECT == HIGH)
      {
        msg->set_byte(2, ICON_YELLOW);
      }
      else if((state_ECT == EXTREMELY_HIGH) || (state_ECT == PRE_SHUTDOWN) || (state_ECT == SHUTDOWN))
      //else if((state_ECT == EXTREMELY_HIGH) || (state_ECT == SHUTDOWN))
      {
        msg->set_byte(2, ICON_RED);
      }
    break;

    case VITAL_ICON_HOT:
      msg->set_byte(5,(uint8_t)(flt_HOT>>8));
      msg->set_byte(6,(uint8_t)flt_HOT);

      if(state_HOT == HIGH)
      {
        msg->set_byte(2, ICON_YELLOW);
      }
      else if((state_HOT == EXTREMELY_HIGH) || (state_HOT == SHUTDOWN))
      {
        msg->set_byte(2, ICON_RED);
      }
    break;

    case VITAL_ICON_FUEL_USAGE:
      msg->set_byte(1, SCALE_ONE);

      tempWord = (can_FuelRate * 5) / 10;
      msg->set_byte(5, (uint8_t)(tempWord>>8));
      msg->set_byte(6, (uint8_t)(tempWord));

    break;


    case VITAL_ICON_EOT:

      msg->set_byte(5,(uint8_t)(ecu_EOT>>8));
      msg->set_byte(6,(uint8_t)ecu_EOT);

      if(ecu_EOT >= CONSTANT_DATA->EOT_HIGH)
      {
        msg->set_byte(2, ICON_YELLOW);
      }
      else if(ecu_EOT >= CONSTANT_DATA->EOT_EXTREMELY_HIGH)
      {
        msg->set_byte(2, ICON_RED);
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
    num_Vitals = 7;
  }
  else
  {
    num_Vitals = 4;
  }

  if(count_Vital >= num_Vitals)
  {
    count_Vital = 0;
  }
}

static void initialize_VitalData_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  tx_VitalData.initialize();
  tx_VitalData.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, VITAL_DATA_PS, nvm_ecuid.j1939_source_address);
  tx_VitalData.set_send_rate(10);
  tx_VitalData.pre_tx_callback = update_VitalData_tx;
  hw_can_tx_scheduler[HWC_CAN0].add_msg(&tx_VitalData);
}

void ServiceData_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Nov, 2008
//    Description : Gets the updated info from the deluxe panel.
//    Notes       :
//******************************************************************************
{
  uint8_t id_Service;
  uint16_t tempWord;

  if((state_DeluxeG5 == NORMAL) && (state_System == SYS_NORMAL))
  {
    id_Service = msg->get_byte(0);

    switch(msg->get_byte(1))
    {
      case SERVICE_OFF:
        //Turn clock off, turn clock on by setting the hour below.
        if((id_Service == 0) || (id_Service == 0xFF))
        {
          if(eeMirror.serviceClockLock & SERVICE_CLOCK_LOCK_BIT)
          {
            eeMirror.serviceClockLock = INACTIVE;
            eeMirror.serviceClockExpired = FALSE;
            eeMirror.serviceClockLength = 0;
            UpdateEEVariables(NOW);
          }
        }
        else
        {
          //Do inactive first that way if in alarm state it will turn off.
          if(eeMirror.queueServiceIntervals.serviceInterval[id_Service-1].state == INACTIVE)
          {
            eeMirror.queueServiceIntervals.serviceInterval[id_Service-1].state = ACTIVE;
            update_ServiceData(id_Service-1);
            eeTimeToUpdateMirror = TRUE;
          }
          else
          {
            eeMirror.queueServiceIntervals.serviceInterval[id_Service-1].state = INACTIVE;
            update_ServiceData(id_Service-1);
            eeTimeToUpdateMirror = TRUE;
          }
        }
      break;

      case SERVICE_RESET:
        if((id_Service == 0) || (id_Service == 0xFF))
        {
          eeMirror.serviceClockResetTime = actualHourMeter;
          eeMirror.serviceClockExpired = FALSE;
          if(eeMirror.serviceClockType++ >= 4)
          {
            eeMirror.serviceClockType = 1;
          }

          UpdateEEVariables(NOW);
          QueueServiceDiag((uint16_t)(eeMirror.serviceClockResetTime/HOUR_METER_TO_HOUR_FCT), (uint16_t)(eeMirror.serviceClockLength/HOUR_METER_TO_HOUR_FCT), MANUAL, eeMirror.serviceClockType, current_user);
        }
        else
        {
          eeMirror.queueServiceIntervals.serviceInterval[id_Service-1].reset_time = actualHourMeter;
          update_ServiceData(id_Service-1);
          eeTimeToUpdateMirror = TRUE;
        }
      break;

      case SERVICE_NEW_LEVEL:
        tempWord = (msg->get_byte(4) << 8) + msg->get_byte(5);
        if((id_Service == 0) || (id_Service == 255))
        {
          if(tempWord != 0) //If it is zero do not set.
          {

            eeMirror.serviceClockLength = (uint32_t)tempWord * HOUR_METER_TO_HOUR_FCT;

            if(!(eeMirror.serviceClockLock & SERVICE_CLOCK_LOCK_BIT))
            {
              eeMirror.serviceClockLock = SERVICE_CLOCK_LOCK_BIT;
              eeMirror.serviceClockResetTime = actualHourMeter;
              UpdateEEVariables(NOW);
            }
          }
        }
        else
        {
          eeMirror.queueServiceIntervals.serviceInterval[id_Service-1].interval = tempWord;
          update_ServiceData(id_Service-1);
        }
      break;

      case SERVICE_FACTORY_RESET:

      break;

      default:
      break;
    }
  }
}

static void initialize_ServiceData_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Nov, 2008
//    Description : initialize CAN to receive deluxe status messages.
//    Notes       :
//******************************************************************************
{
  rx_ServiceData.initialize();
  rx_ServiceData.rx_id     .set_J1939ID(0, PROPRIETARY_B, SERVICE_DATA_PS, SA_DELUXE_PANEL);
  rx_ServiceData.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  rx_ServiceData.rx_callback = ServiceData_rx_callback;
  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_ServiceData);
}

void update_ServiceData_tx (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates service clock message data.
//    Notes       :
//******************************************************************************
{
  uint16_t tempWord;
  uint8_t tempByte;

  msg->set_byte(0, 0);
  tempByte = 0;
  if((eeMirror.serviceClockExpired) && (eeMirror.serviceClockLock & SERVICE_CLOCK_LOCK_BIT))
  {
    tempByte |= SERVICE_ALARM;
  }

  if(eeMirror.serviceClockLock & SERVICE_CLOCK_LOCK_BIT)
  {
    tempByte |= SERVICE_ON;
  }
  else
  {
    tempByte |= SERVICE_OFF;
  }

  msg->set_byte(1, tempByte);

  tempWord = (uint16_t)((actualHourMeter - eeMirror.serviceClockResetTime)/HOUR_METER_TO_HOUR_FCT);
  msg->set_byte(2, (uint8_t)(tempWord>>8));
  msg->set_byte(3, (uint8_t)(tempWord));
  tempWord = (uint16_t)(eeMirror.serviceClockLength/HOUR_METER_TO_HOUR_FCT);

  msg->set_byte(4, (uint8_t)(tempWord>>8));
  msg->set_byte(5, (uint8_t)(tempWord));
  msg->set_byte(7, eeMirror.serviceClockType);
}

static void initialize_ServiceData_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  tx_ServiceData.initialize();
  tx_ServiceData.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, SERVICE_DATA_PS, nvm_ecuid.j1939_source_address);
  tx_ServiceData.set_send_rate(100);
  tx_ServiceData.pre_tx_callback = update_ServiceData_tx;
  hw_can_tx_scheduler[HWC_CAN0].add_msg(&tx_ServiceData);
}

void PwdData_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Jan, 2009
//    Description : Gets new password data from the deluxe panel.
//    Notes       :
//******************************************************************************
{
  uint8_t actualNumber, i;
  if((state_DeluxeG5 == NORMAL) && (state_System == SYS_NORMAL))
  {
    if(msg->get_byte(1) == NEW_PASSWORD)
    {
      newPasswordVerification = SEND_VERIFIED_PASSWORD; //Lets us know to send ack of new password when eemode is idle again.

      // get password number off the buffer
      actualNumber = msg->get_byte(0)-1;

     // save the actual number (0 - 9) that was changed on ddp so we
     // know which one to verify and send back

      newPasswordNumber = actualNumber+1;

      if (actualNumber < NUMBER_TOTAL_PASSWORDS)
      {
        eeMirror.password[actualNumber].checksum = 0;

        eeMirror.password[actualNumber].value[0] = (uint8_t)(((msg->get_byte(2) & 0xF0) == 0xF0)?0:(0x30 + ((msg->get_byte(2) & 0xF0) >> 4)));
        eeMirror.password[actualNumber].value[1] = (uint8_t)(((msg->get_byte(2) & 0x0F) == 0x0F)?0:(0x30 + (msg->get_byte(2) & 0x0F)));
        eeMirror.password[actualNumber].value[2] = (uint8_t)(((msg->get_byte(3) & 0xF0) == 0xF0)?0:(0x30 + ((msg->get_byte(3) & 0xF0) >> 4)));
        eeMirror.password[actualNumber].value[3] = (uint8_t)(((msg->get_byte(3) & 0x0F) == 0x0F)?0:(0x30 + (msg->get_byte(3) & 0x0F)));
        eeMirror.password[actualNumber].value[4] = (uint8_t)(((msg->get_byte(4) & 0xF0) == 0xF0)?0:(0x30 + ((msg->get_byte(4) & 0xF0) >> 4)));
        eeMirror.password[actualNumber].value[5] = (uint8_t)(((msg->get_byte(4) & 0x0F) == 0x0F)?0:(0x30 + (msg->get_byte(4) & 0x0F)));
        eeMirror.password[actualNumber].value[6] = (uint8_t)(((msg->get_byte(5) & 0xF0) == 0xF0)?0:(0x30 + ((msg->get_byte(5) & 0xF0) >> 4)));
        eeMirror.password[actualNumber].value[7] = (uint8_t)(((msg->get_byte(5) & 0x0F) == 0x0F)?0:(0x30 + (msg->get_byte(5) & 0x0F)));
        eeMirror.password[actualNumber].value[8] = (uint8_t)(((msg->get_byte(6) & 0xF0) == 0xF0)?0:(0x30 + ((msg->get_byte(6) & 0xF0) >> 4)));
        eeMirror.password[actualNumber].value[9] = (uint8_t)(((msg->get_byte(6) & 0x0F) == 0x0F)?0:(0x30 + (msg->get_byte(6) & 0x0F)));

        for (i = 0; i < PASSWORD_SIZE; i++)
        {
          eeMirror.password[actualNumber].checksum += eeMirror.password[actualNumber].value[i]; // calc the new checksum
        }
        eeMirror.password[actualNumber].checksum = ~eeMirror.password[actualNumber].checksum + 1;
        eeTimeToUpdateMirror = 1;                                                // set flag to store into eeprom device
      }
    }
  }
}

static void initialize_PwdData_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Jan, 2009
//    Description : initialize CAN to receive deluxe status messages.
//    Notes       :
//******************************************************************************
{
  rx_PwdData.initialize();
  rx_PwdData.rx_id     .set_J1939ID(0, PROPRIETARY_B, PASSWORD_DATA_PS, SA_DELUXE_PANEL);
  rx_PwdData.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  rx_PwdData.rx_callback = PwdData_rx_callback;
  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_PwdData);
}

void VerifyNewPasswordG5(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Jan, 2009
//    Description : Sends password message back to deluxe verifying password has changed.
//    Notes       :
//******************************************************************************
{
  hw_can_msg_t msg_data;
  uint16_t tempWord;
  uint8_t tempByte;
  uint32_t tempDWord;

  // Send password message back verifying it was accepted.
  if ((newPasswordVerification == SEND_VERIFIED_PASSWORD) && (eeMode == EE_IDLE))
  {
    msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, PASSWORD_DATA_PS ,nvm_ecuid.j1939_source_address );
    msg_data.DLR = 7;
    msg_data.set_byte(0,newPasswordNumber);
    msg_data.set_byte(1,NO_CHANGE);

    msg_data.set_byte(2,((((eeMirror.password[newPasswordNumber-1].value[0] == 0)?0x0F:(eeMirror.password[newPasswordNumber-1].value[0] & 0x0F)) << 4) + ((eeMirror.password[newPasswordNumber-1].value[1] == 0)?0x0F:(eeMirror.password[newPasswordNumber-1].value[1]) & 0x0F)));
    msg_data.set_byte(3,((((eeMirror.password[newPasswordNumber-1].value[2] == 0)?0x0F:(eeMirror.password[newPasswordNumber-1].value[2] & 0x0F)) << 4) + ((eeMirror.password[newPasswordNumber-1].value[3] == 0)?0x0F:(eeMirror.password[newPasswordNumber-1].value[3]) & 0x0F)));
    msg_data.set_byte(4,((((eeMirror.password[newPasswordNumber-1].value[4] == 0)?0x0F:(eeMirror.password[newPasswordNumber-1].value[4] & 0x0F)) << 4) + ((eeMirror.password[newPasswordNumber-1].value[5] == 0)?0x0F:(eeMirror.password[newPasswordNumber-1].value[5]) & 0x0F)));
    msg_data.set_byte(5,((((eeMirror.password[newPasswordNumber-1].value[6] == 0)?0x0F:(eeMirror.password[newPasswordNumber-1].value[6] & 0x0F)) << 4) + ((eeMirror.password[newPasswordNumber-1].value[7] == 0)?0x0F:(eeMirror.password[newPasswordNumber-1].value[7]) & 0x0F)));
    msg_data.set_byte(6,((((eeMirror.password[newPasswordNumber-1].value[8] == 0)?0x0F:(eeMirror.password[newPasswordNumber-1].value[8] & 0x0F)) << 4) + ((eeMirror.password[newPasswordNumber-1].value[9] == 0)?0x0F:(eeMirror.password[newPasswordNumber-1].value[9]) & 0x0F)));
    hw_can_txq[HWC_CAN0].send_msg(&msg_data);

    newPasswordVerification = FALSE; // password is updated, do not need to send message again
  }

  if ((newJobClockVerification == ACTIVE) && (eeMode == EE_IDLE))
  {
    // Send out CAN message to update screen with new data.
    msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, JOB_CLOCK_PS ,nvm_ecuid.j1939_source_address );
    msg_data.DLR = 8;

    tempWord = (uint16_t)((actualHourMeter - eeMirror.jobClock)/HOUR_METER_TO_MINUTE_FCT);

    msg_data.set_byte(0, (uint8_t)(tempWord >> 8));
    msg_data.set_byte(1, (uint8_t)(tempWord));

    tempByte =  (eeMirror.jobClockLock << 1) | (eeMirror.userInfo[newJobClockNumber].locks & USER_JOBCLOCK_TOGGLE);
    msg_data.set_byte(2, tempByte);  //Job clock status
    msg_data.set_byte(3, newJobClockNumber);  //user that was changed

    tempWord = (uint16_t)(eeMirror.userInfo[newJobClockNumber].jobClock/HOUR_METER_TO_MINUTE_FCT);
    msg_data.set_byte(4, (uint8_t)(tempWord >> 8));  //User Job clock
    msg_data.set_byte(5, (uint8_t)tempWord);
    msg_data.set_byte(6, UNDEFINED);
    msg_data.set_byte(7, UNDEFINED);
    hw_can_txq[HWC_CAN0].send_msg(&msg_data);


    msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, USER_INFO_PS ,nvm_ecuid.j1939_source_address );
    msg_data.DLR = 7;
    msg_data.set_byte(0,newJobClockNumber); //offset user id as 0 is master and 1 is owner but they do not have user info
    msg_data.set_byte(1,(uint8_t)(eeMirror.userInfo[newJobClockNumber].locks));
    msg_data.set_byte(2,(uint8_t)(eeMirror.userInfo[newJobClockNumber].locks>>8));

    tempDWord = GetUserIdle(newJobClockNumber)/HOUR_METER_TO_MINUTE_FCT;
    msg_data.set_byte(3,(uint8_t)(tempDWord >> 8));
    msg_data.set_byte(4,(uint8_t)tempDWord);
    msg_data.set_byte(5,(uint8_t)(eeMirror.userInfo[newJobClockNumber].fuelConsumption >> 8));
    msg_data.set_byte(6,(uint8_t)(eeMirror.userInfo[newJobClockNumber].fuelConsumption));
    hw_can_txq[HWC_CAN0].send_msg(&msg_data);


    newJobClockVerification = FALSE;
  }

  if((newUserNameVerification == ACTIVE) && (eeMode == EE_IDLE))
  {
    // Send out CAN message to update screen with new data.
    msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, USER_NAME_PS ,nvm_ecuid.j1939_source_address );
    msg_data.DLR = 8;
    msg_data.set_byte(0,newUserNameNumber);
    msg_data.set_byte(1,(uint8_t)(eeMirror.userInfo[newUserNameNumber].user_name[0]));
    msg_data.set_byte(2,(uint8_t)(eeMirror.userInfo[newUserNameNumber].user_name[1]));
    msg_data.set_byte(3,(uint8_t)(eeMirror.userInfo[newUserNameNumber].user_name[2]));
    msg_data.set_byte(4,(uint8_t)(eeMirror.userInfo[newUserNameNumber].user_name[3]));
    msg_data.set_byte(5,(uint8_t)(eeMirror.userInfo[newUserNameNumber].user_name[4]));
    msg_data.set_byte(6,(uint8_t)(eeMirror.userInfo[newUserNameNumber].user_name[5]));
    msg_data.set_byte(7,(uint8_t)(eeMirror.userInfo[newUserNameNumber].user_name[6]));
    hw_can_txq[HWC_CAN0].send_msg(&msg_data);

    newUserNameVerification = FALSE;
  }
}

void UserData_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Jan, 2009
//    Description : Gets new password data from the deluxe panel.
//    Notes       :
//******************************************************************************
{
  uint8_t tempByte;
  uint8_t * bytePtr;
  if((state_DeluxeG5 == NORMAL) && (state_System == SYS_NORMAL))
  {
    if(!flag_NewUserData)
    {
      update_UserID = msg->get_byte(0); //Offset for master and owner

      if(update_UserID <= NUMBER_OF_USERS)
      {
        tempByte = msg->get_byte(1);

        if((tempByte & USER_2SPEED_LOCK_TOGGLE) && (tempByte != 0xFF))
        {
          if(eeMirror.userInfo[update_UserID].locks & USER_2SPEED_LOCK_TOGGLE)
          {
            eeMirror.userInfo[update_UserID].locks &= ~USER_2SPEED_LOCK_TOGGLE;
            flag_NewUserData = TRUE;
          }
          else
          {
            eeMirror.userInfo[update_UserID].locks |= USER_2SPEED_LOCK_TOGGLE;
            flag_NewUserData = TRUE;
          }
        }

        //Toggle the High Flow Lock
        if((tempByte & USER_HF_LOCK_TOGGLE) && (tempByte != 0xFF))
        {
          if(eeMirror.userInfo[update_UserID].locks & USER_HF_LOCK_TOGGLE)
          {
            eeMirror.userInfo[update_UserID].locks &= ~USER_HF_LOCK_TOGGLE;
            flag_NewUserData = TRUE;
          }
          else
          {
            eeMirror.userInfo[update_UserID].locks |= USER_HF_LOCK_TOGGLE;
            flag_NewUserData = TRUE;
          }
        }

        //Toggle thw After hour lockout
        if((tempByte & USER_AFTERHOUR_TOGGLE) && (tempByte != 0xFF))
        {
          if(eeMirror.userInfo[update_UserID].locks & USER_AFTERHOUR_TOGGLE)
          {
            eeMirror.userInfo[update_UserID].locks &= ~USER_AFTERHOUR_TOGGLE;
            flag_NewUserData = TRUE;
          }
          else
          {
            eeMirror.userInfo[update_UserID].locks |= USER_AFTERHOUR_TOGGLE;
            flag_NewUserData = TRUE;
          }
        }

       //Toggle thw After hour lockout
        if((tempByte & USER_JOBCLOCK_TOGGLE) && (tempByte != 0xFF))
        {
          if(eeMirror.userInfo[update_UserID].locks & USER_JOBCLOCK_TOGGLE)
          {
            eeMirror.userInfo[update_UserID].locks &= ~USER_JOBCLOCK_TOGGLE;
            flag_NewUserData = TRUE;
          }
          else
          {
            eeMirror.userInfo[update_UserID].locks |= USER_JOBCLOCK_TOGGLE;
            flag_NewUserData = TRUE;
          }
        }

        if(flag_NewUserData)
        {
          eeMirror.userInfo[update_UserID].checksum = 0;

          bytePtr = (uint8_t *) &eeMirror.userInfo[update_UserID].locks;

          for (; bytePtr < (uint8_t *) &eeMirror.userInfo[update_UserID].checksum; bytePtr++)
          {
            eeMirror.userInfo[update_UserID].checksum += *bytePtr;
          }// end for

          eeMirror.userInfo[update_UserID].checksum = ~eeMirror.userInfo[update_UserID].checksum + 1;

          eeTimeToUpdateMirror = TRUE;
        }
      }
    }
  }
}

static void initialize_UserData_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 05 Jan, 2009
//    Description : initialize CAN to receive deluxe status messages.
//    Notes       :
//******************************************************************************
{
  rx_UserData.initialize();
  rx_UserData.rx_id     .set_J1939ID(0, PROPRIETARY_B, USER_INFO_PS, SA_DELUXE_PANEL);
  rx_UserData.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  rx_UserData.rx_callback = UserData_rx_callback;
  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_UserData);
}

void Deluxe_Data_Update(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jan, 2009
//    Description : Sends response to updated information.
//    Notes       :
//******************************************************************************
{
  if((flag_NewUserData) && (eeMode == EE_IDLE) && (update_UserID != 0xFF))
  {
    hw_can_msg_t msg_data;
    msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, USER_INFO_PS ,nvm_ecuid.j1939_source_address );
    msg_data.DLR = 7;
    msg_data.set_byte(0,update_UserID);
    msg_data.set_byte(1,(uint8_t)(eeMirror.userInfo[update_UserID].locks));
    msg_data.set_byte(2,(uint8_t)(eeMirror.userInfo[update_UserID].locks>>8));
    msg_data.set_byte(3,(uint8_t)(eeMirror.userInfo[update_UserID].idleTime >> 8));
    msg_data.set_byte(4,(uint8_t)(eeMirror.userInfo[update_UserID].idleTime));
    msg_data.set_byte(5,(uint8_t)(eeMirror.userInfo[update_UserID].fuelConsumption >> 8));
    msg_data.set_byte(6,(uint8_t)(eeMirror.userInfo[update_UserID].fuelConsumption));
   // msg_data.set_byte(7,eeMirror.userInfo[update_UserID].litersPerHour);
    hw_can_txq[HWC_CAN0].send_msg(&msg_data);

    flag_NewUserData = FALSE;

  }
}

void SendDeluxeWarning(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jan, 2009
//    Description : Sends message to display warning information.
//    Notes       :
//******************************************************************************
{
  if(failureCode.type != TYPE_SPN)
  {
    if(failureCode.function != 0)
    {
      hw_can_msg_t msg_data;
      msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DELUXE_WARNING_PS,nvm_ecuid.j1939_source_address );
      msg_data.DLR = 6;
      msg_data.set_byte(0,0x01);
      msg_data.set_byte(1,failureCode.device);
      msg_data.set_byte(2,failureCode.function);
      msg_data.set_byte(3,failureCode.failure);
      msg_data.set_byte(4,0xFF);
      msg_data.set_byte(5,current_user);
      hw_can_txq[HWC_CAN0].send_msg(&msg_data);
    }
  }
  else //SPN send TP message
  {
    Deluxe_TP_msg.id.set_J1939_DA(0xFF);
    Deluxe_TP_msg.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DELUXE_WARNING_PS,nvm_ecuid.j1939_source_address);

    msgData[0] = 0x01;  //Active/Inactive
    msgData[1] = failureCode.device;
    msgData[2] = failureCode.function;
    msgData[3] = failureCode.failure;
    msgData[4] = 0xFF; //was spn moved to 8 & 9
    msgData[5] = current_user;
    msgData[6] = 0xFF; //Hour fault occured, not used by active warning.
    msgData[7] = 0xFF; //Hour fault occured, not used by active warning.
    msgData[8] = (uint8_t)failureCode.spn;
    msgData[9] = (uint8_t)(failureCode.spn >> 8);
    msgData[10] = failureCode.pcode[0];
    msgData[11] = failureCode.pcode[1];
    msgData[12] = failureCode.pcode[2];
    msgData[13] = failureCode.pcode[3];
    msgData[14] = failureCode.pcode[4];

    Deluxe_TP_msg.length = 15;

    Deluxe_TP_msg.data = msgData;
    Deluxe_TP_tx.SendMsg(&Deluxe_TP_msg);
  }

  ddpSwitchStatus.data.getNextWarning = FALSE;
}

void UserName_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 21 Jan, 2009
//    Description : Gets new password data from the deluxe panel.
//    Notes       :
//******************************************************************************
{
  uint8_t userID;
  uint8_t * bytePtr;

  if((state_DeluxeG5 == NORMAL) && (state_System == SYS_NORMAL))
  {
    userID = msg->get_byte(0);

    if(userID <= NUMBER_OF_USERS)
    {

      for(uint8_t i=0; i < 7; i++)
      {
        eeMirror.userInfo[userID].user_name[i] = msg->get_byte(i+1);
      }

      eeMirror.userInfo[userID].checksum = 0;

      bytePtr = (uint8_t *) &eeMirror.userInfo[userID].locks;

      for (; bytePtr < (uint8_t *) &eeMirror.userInfo[userID].checksum; bytePtr++)
      {
        eeMirror.userInfo[userID].checksum += *bytePtr;
      }// end for

      eeMirror.userInfo[userID].checksum = ~eeMirror.userInfo[userID].checksum + 1;
      eeTimeToUpdateMirror = TRUE;

      newUserNameVerification = TRUE;
      newUserNameNumber       = userID;
    }
  }
}

static void initialize_UserName_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 21 Jan, 2009
//    Description : initialize CAN to receive deluxe status messages.
//    Notes       :
//******************************************************************************
{
  rx_UserName.initialize();
  rx_UserName.rx_id     .set_J1939ID(0, PROPRIETARY_B, USER_NAME_PS, SA_DELUXE_PANEL);
  rx_UserName.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  rx_UserName.rx_callback = UserName_rx_callback;
  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_UserName);
}

#ifdef HCS12_BSP_EMU //if M4 compile this
void SendWarningHistory(void)
//******************************************************************************
//    returns     : NONE.
//
//		Created By  : SLM
//    Date Created: 09 Jan, 2009
//    Description : Sends response to updated information.
//    Notes       :
//******************************************************************************
{
  static uint8_t tempStop = 0;
  static uint8_t error_Count=0;
  static uint8_t activeCount=0;
  uint16_t tempWord;
  
  static uint8_t tempStopECU = 0;
  static uint8_t error_CountECU = 0;
  
  uint32_t spnfmi = 0;
  uint32_t temp = 0;
  uint32_t tablespnfmi = 0;
  
  uint8_t sentTPmsg = 0;
  
  #define MAX_SERVICE_HISTORY   10
  
  if(!flag_SentWarningHistory)
  {
    //setup to send 10 gateway codse
    error_Count = eeMirror.queue.pointer + 1;
     
    if(error_Count == MAX_SERVICE_HISTORY)
    {
      tempStop = EVENT_DIAG_QUEUE_SIZE - 1;
    }
    else if(error_Count < MAX_SERVICE_HISTORY)
    {
      tempStop = EVENT_DIAG_QUEUE_SIZE - (MAX_SERVICE_HISTORY - error_Count);
    }
    else
    {
      tempStop = error_Count - MAX_SERVICE_HISTORY;
    }
    
    //setup to send 10 ECU codes
    error_CountECU = eeMirror.queueECU.pointer + 1;
    if(error_CountECU == MAX_SERVICE_HISTORY)
    {
      tempStopECU = EVENT_DIAG_QUEUE_SIZE - 1;
    }
    else if(error_CountECU < MAX_SERVICE_HISTORY)
    {
      tempStopECU = EVENT_DIAG_QUEUE_SIZE - (MAX_SERVICE_HISTORY - error_CountECU);
    }
    else
    {
      tempStopECU = error_CountECU - MAX_SERVICE_HISTORY;
    }
    
    activeCount = 0;
    flag_SentWarningHistory = TRUE;
  }
  

  
  //sent one of the active messages
  if(activeCount < MAX_NUMBER_OF_FAILURES)
  {
    if(FailureQueue[activeCount].failure != 255)
    {
      if(FailureQueue[activeCount].type != TYPE_SPN)
      {
        hw_can_msg_t msg_data;
        msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DELUXE_WARNING_PS ,nvm_ecuid.j1939_source_address );
        msg_data.DLR = 6;
        msg_data.set_byte(0,0x01);
        msg_data.set_byte(1,FailureQueue[activeCount].device);
        msg_data.set_byte(2,FailureQueue[activeCount].function);
        msg_data.set_byte(3,FailureQueue[activeCount].failure);
        msg_data.set_byte(4,0xFF);
        msg_data.set_byte(5,current_user);
        hw_can_txq[HWC_CAN0].send_msg(&msg_data); 
      }
      else
      {
        sentTPmsg = 1;
        Deluxe_TP_msg.id.set_J1939_DA(0xFF);
        Deluxe_TP_msg.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DELUXE_WARNING_PS,nvm_ecuid.j1939_source_address);
       
        msgData[0] = 0x01;  //Active/Inactive
        msgData[1] = FailureQueue[activeCount].device;
        msgData[2] = FailureQueue[activeCount].function; //bottom 8 bits of spn
        msgData[3] = FailureQueue[activeCount].failure; //fmi
        msgData[4] = 0xFF; //was spn moved to 8 & 9
        msgData[5] = current_user;
        msgData[6] = 0xFF; //Hour fault occured, not used by active warning.
        msgData[7] = 0xFF; //Hour fault occured, not used by active warning.
        msgData[8] = (uint8_t)FailureQueue[activeCount].spn; //middle 8 bits of spn
        msgData[9] = (uint8_t)(FailureQueue[activeCount].spn >> 8); //top 3 bits of spn
        msgData[10] = FailureQueue[activeCount].pcode[0];
        msgData[11] = FailureQueue[activeCount].pcode[1];
        msgData[12] = FailureQueue[activeCount].pcode[2];
        msgData[13] = FailureQueue[activeCount].pcode[3];
        msgData[14] = FailureQueue[activeCount].pcode[4];
        
        Deluxe_TP_msg.length = 15; 
        Deluxe_TP_msg.data = msgData;
        Deluxe_TP_tx.SendMsg(&Deluxe_TP_msg);   
      }
    }
    activeCount++;
  }
  
  //send one gateway warning from the history
  if(error_Count != tempStop)
  {
    error_Count--;
    if((eeMirror.queue.eventDiag[error_Count].controller != 0xFF) && (eeMirror.queue.eventDiag[error_Count].time != 0))
    {
      hw_can_msg_t msg_data;
      msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DELUXE_WARNING_PS ,nvm_ecuid.j1939_source_address );
      msg_data.DLR = 8;
      msg_data.set_byte(0,0x00);
      msg_data.set_byte(1,eeMirror.queue.eventDiag[error_Count].controller);
      msg_data.set_byte(2,eeMirror.queue.eventDiag[error_Count].function);
      msg_data.set_byte(3,eeMirror.queue.eventDiag[error_Count].failure);
      msg_data.set_byte(4,0);
      
      msg_data.set_byte(5,eeMirror.queue.eventDiag[error_Count].userID);
        
      tempWord = (uint16_t)eeMirror.queue.eventDiag[error_Count].time;
      msg_data.set_byte(6,(uint8_t)(tempWord>>8));
      msg_data.set_byte(7,(uint8_t)(tempWord));
        
      hw_can_txq[HWC_CAN0].send_msg(&msg_data); 
    }
    
    if(error_Count == 0)
    {
      error_Count = EVENT_DIAG_QUEUE_SIZE;
    }
  }

  
  //if you haven't yet send a TP msg send one ECU warning from the history
  if((error_CountECU != tempStopECU) && (sentTPmsg != 1))
  {
      error_CountECU--;
      if((eeMirror.queueECU.eventDiag[error_CountECU].controller != 0xFF) && (eeMirror.queueECU.eventDiag[error_CountECU].time != 0))
      {
        sentTPmsg = 1;
        Deluxe_TP_msg.id.set_J1939_DA(0xFF);
        Deluxe_TP_msg.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DELUXE_WARNING_PS,nvm_ecuid.j1939_source_address);
       
        msgData[0] = 0x00;  //Inactive
        msgData[1] = eeMirror.queueECU.eventDiag[error_CountECU].controller;
        msgData[2] = (uint8_t)(eeMirror.queueECU.eventDiag[error_CountECU].function); //bottom 8 bits of spn
        msgData[3] = eeMirror.queueECU.eventDiag[error_CountECU].failure; //fmi
        msgData[4] = 0xFF; //was spn moved to 8 & 9
        msgData[5] = current_user;
        
        tempWord = (uint16_t)eeMirror.queueECU.eventDiag[error_CountECU].time;
        msgData[6] = (uint8_t)(tempWord>>8); //top 8 bits of hour
        msgData[7] = (uint8_t)(tempWord); //bottom 8 bits of hour
        
        msgData[8] = (uint8_t)(eeMirror.queueECU.eventDiag[error_CountECU].function >> 8); //middle 8 bits of spn
        msgData[9] = (uint8_t)(((uint8_t)(eeMirror.queueECU.eventDiag[error_CountECU].function >> 16)) & 0x07);  //top 3 bits of spn
        
        //find pcode - if functionality turned on
        if (CONSTANT_DATA->PCODE_FUNCTION != 0xFF)
        {
          spnfmi = (((uint32_t)eeMirror.queueECU.eventDiag[error_CountECU].function) << 5) | (uint32_t)eeMirror.queueECU.eventDiag[error_CountECU].failure;  //construct desired spnfmi
          for(uint16_t p = 0; p < SIZE_OF_GTW_PCODE_ECU_SPNLOOKUP; p++)
          {
            temp = GTW_PCODE_ECU_SPNLOOKUP[p];
            
            tablespnfmi = temp & 0x00FFFFFF; //get spn/fmi from table at index p
            
            if(spnfmi == tablespnfmi)
            {
              
              msgData[10] = temp >> 24; //get asci char for P or U
              temp = GTW_PCODE_ECU_ASCIIPCODE[p];  //get Ascii Chars for PCODE
              msgData[11] = (temp >> 24) & 0xFF;
              msgData[12] = (temp >> 16) & 0xFF;
              msgData[13] = (temp >> 8) & 0xFF;
              msgData[14] = temp & 0xFF;
              break;
            }
            else if(p == (SIZE_OF_GTW_PCODE_ECU_SPNLOOKUP - 1)) //if nothing matches set to ?PCOD
            {
              msgData[10] = '?';
              msgData[11] = 'P';
              msgData[12] = 'C';
              msgData[13] = 'O';
              msgData[14] = 'D';  
            }    
          }
        }
        else //disabled pcode function.. set to ?pcode to indicate to DDP to display ECode instead
        {
          msgData[10] = '?';
          msgData[11] = 'P';
          msgData[12] = 'C';
          msgData[13] = 'O';
          msgData[14] = 'D';  
        }
        
        Deluxe_TP_msg.length = 15; 
        Deluxe_TP_msg.data = msgData;
        Deluxe_TP_tx.SendMsg(&Deluxe_TP_msg);     
      } 
      
      if(error_CountECU == 0)
      {
        error_CountECU = EVENT_DIAG_QUEUE_SIZE;
      }
  }

  //if done sending all codes
  if((error_Count == tempStop)  && (error_CountECU == tempStopECU))
  {
    flag_SendWarningHistory = FALSE;
    
    error_Count = 0;
    error_CountECU = 0;
  }
}
#endif


#ifndef HCS12_BSP_EMU //if HCS12 compile this
void SendWarningHistory(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jan, 2009
//    Description : Sends response to updated information.
//    Notes       :
//******************************************************************************
{
  static uint8_t tempStop = 0;
  static uint8_t error_Count=0;
  static uint8_t activeCount=0;
  uint16_t tempWord;

  #define MAX_SERVICE_HISTORY   10

  if(!flag_SentWarningHistory)
  {
    error_Count = eeMirror.queue.pointer+1;

    if(error_Count == MAX_SERVICE_HISTORY)
    {
      tempStop = EVENT_DIAG_QUEUE_SIZE - 1;
    }
    else if(error_Count < MAX_SERVICE_HISTORY)
    {
      tempStop = EVENT_DIAG_QUEUE_SIZE - (MAX_SERVICE_HISTORY - error_Count);
    }
    else
    {
      tempStop = error_Count - MAX_SERVICE_HISTORY;
    }
    activeCount = 0;
    flag_SentWarningHistory = TRUE;
  }

  if((FailureQueue[activeCount].failure != 255) && (activeCount < MAX_NUMBER_OF_FAILURES))
  {
    if(FailureQueue[activeCount].type != TYPE_SPN)

    {
      hw_can_msg_t msg_data;
      msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DELUXE_WARNING_PS ,nvm_ecuid.j1939_source_address );
      msg_data.DLR = 6;
      msg_data.set_byte(0,0x01);
      msg_data.set_byte(1,FailureQueue[activeCount].device);
      msg_data.set_byte(2,FailureQueue[activeCount].function);
      msg_data.set_byte(3,FailureQueue[activeCount].failure);
      msg_data.set_byte(4,0xFF);
      msg_data.set_byte(5,current_user);
      hw_can_txq[HWC_CAN0].send_msg(&msg_data);
    }
    else
    {
      Deluxe_TP_msg.id.set_J1939_DA(0xFF);
      Deluxe_TP_msg.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DELUXE_WARNING_PS,nvm_ecuid.j1939_source_address);

      msgData[0] = 0x01;  //Active/Inactive
      msgData[1] = FailureQueue[activeCount].device;
      msgData[2] = FailureQueue[activeCount].function;
      msgData[3] = FailureQueue[activeCount].failure;
      msgData[4] = 0xFF; //was spn moved to 8 & 9
      msgData[5] = current_user;
      msgData[6] = 0xFF; //Hour fault occured, not used by active warning.
      msgData[7] = 0xFF; //Hour fault occured, not used by active warning.
      msgData[8] = (uint8_t)FailureQueue[activeCount].spn;
      msgData[9] = (uint8_t)(FailureQueue[activeCount].spn >> 8);
      msgData[10] = FailureQueue[activeCount].pcode[0];
      msgData[11] = FailureQueue[activeCount].pcode[1];
      msgData[12] = FailureQueue[activeCount].pcode[2];
      msgData[13] = FailureQueue[activeCount].pcode[3];
      msgData[14] = FailureQueue[activeCount].pcode[4];
      
      Deluxe_TP_msg.length = 15; 
      
      Deluxe_TP_msg.data = msgData;
      Deluxe_TP_tx.SendMsg(&Deluxe_TP_msg);    
    }
  }

  if(activeCount < MAX_NUMBER_OF_FAILURES)
  {
    activeCount++;
  }

  error_Count--;
  if((eeMirror.queue.eventDiag[error_Count].controller != 0xFF) && (eeMirror.queue.eventDiag[error_Count].time != 0))
  {
    hw_can_msg_t msg_data;
    msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DELUXE_WARNING_PS ,nvm_ecuid.j1939_source_address );
    msg_data.DLR = 8;
    msg_data.set_byte(0,0x00);
    msg_data.set_byte(1,eeMirror.queue.eventDiag[error_Count].controller);
    msg_data.set_byte(2,eeMirror.queue.eventDiag[error_Count].function);
    msg_data.set_byte(3,eeMirror.queue.eventDiag[error_Count].failure);
    msg_data.set_byte(4,0);

    msg_data.set_byte(5,eeMirror.queue.eventDiag[error_Count].userID);

    tempWord = (uint16_t)eeMirror.queue.eventDiag[error_Count].time;
    msg_data.set_byte(6,(uint8_t)(tempWord>>8));
    msg_data.set_byte(7,(uint8_t)(tempWord));

    hw_can_txq[HWC_CAN0].send_msg(&msg_data);
  }

  if(error_Count == 0)
  {
    error_Count = EVENT_DIAG_QUEUE_SIZE;
  }

  if(error_Count == tempStop)
  {
    flag_SendWarningHistory = FALSE;

    error_Count = 0;
  }
}
#endif

void process_DeluxeG5_TP_cmd(const J1939_msg_t *request)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 1 Aug 2007
//    Description :
//******************************************************************************
{
  uint8_t userID;
  uint8_t * bytePtr;
  uint8_t temp_PF;
  uint8_t temp_PS;
  uint8_t temp_SA;

  temp_PF = (uint8_t)request->id.get_J1939_PF();
  temp_PS = (uint8_t)request->id.get_J1939_PS();
  temp_SA = (uint8_t)request->id.get_J1939_SA();

  if((temp_PF == PROPRIETARY_B) && (temp_PS == USER_NAME_PS) &&
    (temp_SA == SA_DELUXE_PANEL))
  {
    if((state_DeluxeG5 == NORMAL) && (state_System == SYS_NORMAL))
    {
      userID = request->data[0];

      for(uint8_t i=0; i < 7; i++)
      {
        eeMirror.userInfo[userID].user_name[i] = request->data[i+1];
      }

      eeMirror.userInfo[userID].checksum = 0;

      bytePtr = (uint8_t *) &eeMirror.userInfo[userID].locks;

      for (; bytePtr < (uint8_t *) &eeMirror.userInfo[userID].checksum; bytePtr++)
      {
        eeMirror.userInfo[userID].checksum += *bytePtr;
      }// end for

      eeMirror.userInfo[userID].checksum = ~eeMirror.userInfo[userID].checksum + 1;
      eeTimeToUpdateMirror = TRUE;
    }
  }
}



void Deluxe_TP_update(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jun, 2006
//    Description : Update CAN TP messages.
//    Notes       :
//******************************************************************************
{
  Deluxe_TP_tx.update();
  Deluxe_TP_rx.update();


  if(Deluxe_TP_rx.MsgAvailiable())
  {
    //Process received messages
    process_DeluxeG5_TP_cmd(&Deluxe_TP_rx.jmsg);
    Deluxe_TP_rx.FreeBuffer();
  }
}

void DeluxeKeypad_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 06 April, 2006
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  msg_DeluxeButtons[0] = msg->get_byte(0);
  msg_DeluxeButtons[1] = msg->get_byte(1);
  msg_DeluxeButtons[2] = msg->get_byte(2);
  msg_DeluxeButtons[3] = msg->get_byte(3);
  msg_DeluxeButtons[4] = msg->get_byte(7);
}

static void initialize_DeluxeKeypad_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 10 Jan, 2006
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  rx_DeluxeKeypad.initialize();
  rx_DeluxeKeypad.rx_id     .set_J1939ID(0, PROPRIETARY_B, KEYPAD_STATUS_PS, SA_DELUXE_PANEL);
  rx_DeluxeKeypad.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  rx_DeluxeKeypad.rx_callback = DeluxeKeypad_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_DeluxeKeypad);
}

void DeluxeProg_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 06 April, 2006
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  flag_DeluxeProg = ACTIVE;
}

static void initialize_DeluxeProg_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 10 Jan, 2006
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  rx_DeluxeProg.initialize();
  rx_DeluxeProg.rx_id     .set_J1939ID(0, PROPRIETARY_A, SA_PROG_TOOL, SA_DELUXE_PANEL);
  rx_DeluxeProg.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  rx_DeluxeProg.rx_callback = DeluxeProg_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&rx_DeluxeProg);
}



void ap_DeluxeG5_initialize (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 5 Sept, 2007
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  flag_Sent = FALSE;
  flag_NewUserData = FALSE;
  flag_DeluxeProg = FALSE;
  update_UserID = 0xFF;

  initialize_ServiceData_tx ();
  initialize_ServiceData_rx();
  initialize_DeluxeStatus_rx();
  initialize_MainStatus_tx ();
  initialize_JobClock_rx();
  initialize_JobClock_tx ();
  initialize_VitalData_tx ();
  initialize_UserInfo_tx();
  initialize_PwdData_rx();
  initialize_UserData_rx();
  initialize_UserName_rx();
  initialize_DeluxeKeypad_rx();
  initialize_DeluxeProg_rx();

  Deluxe_TP_tx.initialize(HWC_CAN0);
  Deluxe_TP_rx.initialize(0xFF, HWC_CAN0);

  flag_PasswordSent = FALSE;

  vitalDisplay[0].icon = VITAL_ICON_RPM;
  vitalDisplay[0].units = 1;

  vitalDisplay[1].icon = VITAL_ICON_BATTERY;
  vitalDisplay[1].units = 2;

  vitalDisplay[2].icon = VITAL_ICON_ECT;
  vitalDisplay[2].units = 4;

  vitalDisplay[3].icon = VITAL_ICON_HOT;
  vitalDisplay[3].units = 4;

  vitalDisplay[4].icon = VITAL_ICON_EOP;
  vitalDisplay[4].units = 3;

  vitalDisplay[5].icon = VITAL_ICON_FUEL_USAGE;
  vitalDisplay[5].units = 5;

  vitalDisplay[6].icon = VITAL_ICON_EOT;
  vitalDisplay[6].units = 4;


}


