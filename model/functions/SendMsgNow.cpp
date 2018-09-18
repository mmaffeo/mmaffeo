#include "SendMsgNow.h"
#include "ap_can.h"
#include "defines.h"
#include "ap_eeprom.h"
#include "global.h"
#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"
#include "ap_subs.h"

uint16_t test2;

void SendMsg_03_Now(void)
{
  SEND_CAN03_NOW;
}

void SendMsg_BICSControl_Now(void)
{
  SEND_BICS_NOW;
}

void matlab_UpdateEEVar(void)
{
  UpdateEEVariables(NOW);
  test2++;
}

void SendMsg_Derate_Now(void)
{
  hw_can_msg_t msg_data;
  uint16_t tmpWord;

  msg_data.id.set_J1939ID(PRIORITY_3, TSC1_PF, TSC1_PS ,nvm_ecuid.j1939_source_address );
  msg_data.DLR = 8;

  if(percent_Derate < 100)
  {
    tmpWord = rpm_Derate << 3;
    msg_data.set_byte(0,0xFF); // set override control mode to 11b and override control priority to 10b
    msg_data.set_byte(1,(uint8_t) tmpWord);
    msg_data.set_byte(2,(uint8_t) (tmpWord >> 8));
    msg_data.set_byte(3, (uint8_t)(torque_Derate + 125)); // percent is offset by 125
    //msg_data.set_byte(4,0xFF);  // set byte 3-7 to equal 31 for control purpose and 0-2 to 111b for normal speed
  }
  else
  {
    msg_data.set_byte(0,0xC0);
    msg_data.set_byte(1,UNDEFINED);
    msg_data.set_byte(2,UNDEFINED);
    msg_data.set_byte(3,UNDEFINED);
  }
  msg_data.set_byte(4,UNDEFINED);
  msg_data.set_byte(5,UNDEFINED);
  msg_data.set_byte(6,UNDEFINED);
  msg_data.set_byte(7,UNDEFINED);
  hw_can_txq[HWC_CAN4].send_msg(&msg_data);
}

void SendMsg_SOFTRequest_Now(void)
{
  Send_Request_Message(((uint16_t)(SOFT_PF << 8) + SOFT_PS), 0xFF, HWC_CAN4);
}

void SendMsg_DPM2_Now(void)
{
  hw_can_msg_t msg_data;
  
  msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, DPM2_PS ,nvm_ecuid.j1939_source_address );
  msg_data.DLR = 8;
  
  if(state_Engine == ENGINE_CRANKING)
  {
    msg_data.set_byte(0, ACTIVE | 0xFC);
  }
  else
  {
    msg_data.set_byte(0, INACTIVE | 0xFC);
  }
  
  msg_data.set_byte(1, 0xFF);
  msg_data.set_byte(2, 0xFF);
  msg_data.set_byte(3, 0xFF);
  msg_data.set_byte(4, 0xFF);
  msg_data.set_byte(5, 0xFF);
  msg_data.set_byte(6, 0xFF);
  msg_data.set_byte(7, 0xFF);
  
  hw_can_txq[HWC_CAN4].send_msg(&msg_data); 
}

