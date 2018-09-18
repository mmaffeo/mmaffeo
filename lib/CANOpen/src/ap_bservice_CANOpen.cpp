/*------------------------------------------------------------------------------*
Project Name: E10 Electric

Copyright 2005 Bobcat Company as an unpublished work.
All Rights Reserved.

The information contained herein is confidential
property of Bobcat Company. The use, copying, transfer or
disclosure of such information is prohibited except
by express written agreement with Bobcat Company.

First written on 06 August, 2018 

Module Description:
The module broadcasts messages on CANOpen Standard between the electric devices 
on the primary CAN bus. The main device connected is the inverter that drive 
the hydraulic pump. The management of this device is done in the simulink block 
named ElectricAutomation. The interface between the model and the code is made 
using an input byte named state_Inverter for monitoring the status of the 
inverter that can assume the following value:
state_Inverter  = 0 =   inverter in STOP 
state_Inverter  = 1 =   inverter CONNECTED
state_Inverter  = 2 =   inverter in OPERATIONAL STATUS
state_Inverter  = 3 =   inverter READY
state_Inverter  = 4 =   inverter RUN in FORWARD DIRECTION
state_Inverter  = 5 =   inverter RUN in REVERSE DIRECTION
the command of the inverter is made assign a value to the output byte named 
cmdInverter. This is the the meaning of each valuee: 
   
*******************************************************************************/

// INCLUDES
#include "ap_can.h"
#include "global.h"
#include "defines.h"
#include "ap_bservice_CANOpen.h"
#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_types.h"

// GLOBAL VARIABLES
hw_can_rxmsg                CANOpenRPDO1,
                            CANOpenRPDO2,
                            CANOpenRPDO3,
                            CANOpenGUARD;
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : Add here all the CANOpen Initialization
//  Notes       :
//------------------------------------------------------------------------------
void CANOpenInitialize(void)
{
    guardCycleTime = GUARD_TIMEOUT;                                             //Start with condition of inverter not connected
    CANOpenPDOInitialize(inverterNode);
    CANOpenNTMInitialize(inverterNode);      
}
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : Called every cycle of the App Main
//  Notes       :
//------------------------------------------------------------------------------
void CANOpenUpdate(void)
{  
  getCycleTime();
// messages sent every 32 ms 
  if (cycleTime >= 32 )
  {
    sendNTMSyncMsg();
    cycleTime = 0;        
  } 
// time out of the GUARD message
  if (guardCycleTime >= GUARD_TIMEOUT )
  {
    state_Inverter = 0x00;                                                      //Inverter disconnected and not operational clear bit0 and bit1 xxxx xx00
    guardCycleTime = GUARD_TIMEOUT;    
  }
  CANOpenChangeStatusInverter();
}
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : Main routine for command the inverter in a specific state 
//                waiting for feedback. There are the following value:
//                CMD_INVERTER_GOTO_STOP - Go to stop
//                CMD_INVERTER_GOTO_OPERATIONAL - Go in operational state 
//                (logic ready)
//                CMD_INVERTER_GOTO_READY - Go in ready state 
//                (logig and power ready)
//                CMD_INVERTER_RUN_FWD - Run forward at the the target speed
//                CMD_INVERTER_RUN_REV - Run reverse at the the target speed
//  Notes       :
//------------------------------------------------------------------------------
void CANOpenChangeStatusInverter(void)
{ 
  switch (cmdInverter)
  {  
    case CMD_INVERTER_GOTO_STOP :
    {
      sendNTMMsg(GO_STOP,inverterNode);
      break;
    }
    case CMD_INVERTER_GOTO_OPERATIONAL:
    {
      if ((RPDO1.outNMCStatus) || (inverterStatusFeedback == OPERATIONAL ))
      {  
        TPDO1.dirFWD = false;
        TPDO1.dirREV = false;
        TPDO1.enablePower = false;
        TPDO1.powerLineON = false;
        sendTPDO1Msg(inverterNode);
      }
      if (!(inverterStatusFeedback == OPERATIONAL))
      { 
        if (inverterStatusFeedback == PRE_OPERATIONAL )
        {
          sendNTMMsg(GO_OPERATIONAL,inverterNode);       
        }
        else
        {
          sendNTMMsg(GO_PRE_OPERATIONAL,inverterNode);
        }
      }  
      break;
    }  
    case CMD_INVERTER_GOTO_READY:
    {
      if (inverterStatusFeedback == OPERATIONAL)
      {
        TPDO1.enablePower = true;
        if (!RPDO1.outNMCStatus)
        { 
          TPDO1.powerLineON = true;
        } 
        if (TPDO1.dirFWD || TPDO1.dirREV)
        { 
          TPDO1.dirFWD = false;
          TPDO1.dirREV = false;
        } 
      }
      TPDO1.targetSpeed = 0;
      sendTPDO1Msg(inverterNode);
      TPDO2.brakeMAXTorque = 0xFF;
      TPDO2.motorMAXTorque = 0xFF;
      sendTPDO2Msg(inverterNode); 
      break;
    }
    case CMD_INVERTER_RUN_FWD:
    {
      TPDO1.dirFWD = true;
      TPDO1.dirREV = false;
      TPDO1.targetSpeed = targetSpeed;
      sendTPDO1Msg(inverterNode);
      break;
    }
     case CMD_INVERTER_RUN_REV:
    {
      TPDO1.dirFWD = false;
      TPDO1.dirREV = true;
      TPDO1.targetSpeed = targetSpeed;
      sendTPDO1Msg(inverterNode);        
    }
  }
}
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : Calculate the cycle time
//  Notes       :
//------------------------------------------------------------------------------
void getCycleTime(void)
{ 
uint16_t    currentTime,
            tempCycleTime;
  currentTime = hw_clock_mS();
  if (currentTime > prevCycleTime)
  {
    tempCycleTime = currentTime - prevCycleTime;
  }
  else
  {
    tempCycleTime =  (0XFFFF - prevCycleTime)  + currentTime;
  }
  cycleTime += tempCycleTime;
  cycleTimeTPDO2 += tempCycleTime;
  cycleTimeTPDO1 += tempCycleTime;
  guardCycleTime += tempCycleTime;  
  cycleTimeControlMsg += tempCycleTime;
  prevCycleTime = currentTime;
}
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : Add the messagesthat must be received to the RX message list 
//  Notes       : 
//------------------------------------------------------------------------------
void CANOpenPDOInitialize(uint8_t node)
{
  addRPDO1Msg(node);
  addRPDO2Msg(node); 
}
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : 
//  Notes       : 
//------------------------------------------------------------------------------
void CANOpenNTMInitialize( uint8_t nodeID)
{
//Add the messages that must be received
  addGUARDMsg(nodeID);  
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : prepare the heading of the RPDO1 message 
//  Notes       :
//------------------------------------------------------------------------------
void addRPDO1Msg(uint8_t nodeID)
{
  CANOpenRPDO1.initialize();
  CANOpenRPDO1.rx_id.set_stdID( getRPDO_ID(1,nodeID));
  CANOpenRPDO1.rx_id_mask.set_idr(0xFFFFFFFF);  
  CANOpenRPDO1.rx_callback = RPDO1_rx_callback;
  addMsgHandler(&CANOpenRPDO1);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : prepare the heading of the RPDO2 message
//  Notes       :
//------------------------------------------------------------------------------
void addRPDO2Msg(uint8_t nodeID)
{
  CANOpenRPDO2.initialize();
  CANOpenRPDO2.rx_id.set_stdID( getRPDO_ID(2,nodeID));
  CANOpenRPDO2.rx_id_mask.set_idr(0xFFFFFFFF);
  CANOpenRPDO2.rx_callback = RPDO2_rx_callback;
  addMsgHandler(&CANOpenRPDO2);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : prepare the heading of the GUARD message
//  Notes       :
//------------------------------------------------------------------------------
void addGUARDMsg(uint8_t nodeID)
{
  CANOpenGUARD.initialize();
  CANOpenGUARD.rx_id.set_stdID( getGUARD_ID(nodeID));
  CANOpenGUARD.rx_id_mask.set_idr(0xFFFFFFFF);
  CANOpenGUARD.rx_callback = GUARD_rx_callback;
  addMsgHandler(&CANOpenGUARD);
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the RPDO1 message is received.
//                  the inverter status managed set are:
//                  state_Inverter  = 3 =   inverter READY
//                  state_Inverter  = 4 =   inverter RUN in FORWARD DIRECTION
//                  state_Inverter  = 5 =   inverter RUN in REVERSE DIRECTION
//    Notes       :
//------------------------------------------------------------------------------
void RPDO1_rx_callback(hw_can_msg_t *Msg)
{ 
  Msg2RPDO1(Msg);
  if (RPDO1.outNMCStatus == true)   
  {
    //tempCmd = 3;
  }
  if (RPDO1.outNEBStatus == true)   
  {
    //tempCmd = 4;
  }
  if (RPDO1.outNMCStatus)
  {  
    state_Inverter =3;                                                          //set the state to READY 
  }
  if (RPDO1.outNEBStatus)
  {  
    if(TPDO1.dirREV)
    {  
      state_Inverter = 5;                                                       //set the state to RUN REV
    }
  else
    {
      state_Inverter = 4;                                                       //set the state to RUN FWD    
    } 
  }
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the RPDO2 message is received.
//    Notes       :
//------------------------------------------------------------------------------

void RPDO2_rx_callback(hw_can_msg_t *Msg)
{
  Msg2RPDO2(Msg);
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the GUARD message is received from inverter. 
//                  the first 3 bits of the inverter status are managed here:
//                  state_Inverter  = 0 =   inverter in STOP 
//                  state_Inverter  = 1 =   inverter CONNECTED
//                  state_Inverter  = 2 =   inverter in OPERATIONAL STATUS
//    Notes       :
//------------------------------------------------------------------------------
void GUARD_rx_callback(hw_can_msg_t *Msg)
{
  inverterStatusFeedback = Msg->get_word(0);                                       
  state_Inverter = 1;                                                           //set the state to CONNECTED
  if(inverterStatusFeedback == OPERATIONAL)
  {  
    state_Inverter = 2;                                                         //set the state to OPERATIONAL     
  }
  guardCycleTime = 0;
}
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : send the TPDO1 message on the bus
//  Notes       :
//------------------------------------------------------------------------------
void sendTPDO1Msg(uint8_t nodeID)
{
uint16_t tmpWord = 0x0000;
hw_can_msg_t msgData;
  if (((prevTPDO1 != TPDO1) && (cycleTimeTPDO1 >= MIN_CYCLE_TIME))||
      (cycleTimeTPDO1 >= MAX_CYCLE_TIME))
  {
    msgData.DLR = 8;
    msgData.id.set_stdID(getTPDO_ID(1,nodeID));                                   
    msgData.set_word(0,TPDO1.targetSpeed);                                   
    if(TPDO1.enablePower)  tmpWord |= 0x0001;                                   // Set bit 0 byte 1
    if(TPDO1.powerLineON)  tmpWord |= 0x0002;                                   // Set bit 1 byte 1
    if(TPDO1.outNEB)       tmpWord |= 0x0004;                                   // Set bit 2 byte 1
    if(TPDO1.dirFWD)       tmpWord |= 0x0008;                                   // Set bit 3 byte 1  
    if(TPDO1.dirREV)       tmpWord |= 0x0010;                                   // Set bit 4 byte 1
    if(TPDO1.watchdogBit)  
      {
        tmpWord &= 0x7FFF;                                                      // Reset bit 7 byte 2
        TPDO1.watchdogBit = false;
      }
    else
      {
        tmpWord |= 0x8000;                                                      // Set bit 7 byte 2
        TPDO1.watchdogBit = true;
      }
    msgData.set_word(1,tmpWord); 
    msgData.set_byte(4,TPDO1.brakeReq);
    msgData.set_byte(5,0x00);  
    msgData.set_word(3,0x0000);
    sendMsg(&msgData);
    prevTPDO1 = TPDO1;
    cycleTimeTPDO1 = 0;
  }  
}  
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : send the TPDO2 message on the bus
//  Notes       :
//------------------------------------------------------------------------------
void sendTPDO2Msg(uint8_t nodeID)
{
uint16_t tmpWord = 0x0000;
hw_can_msg_t msgData;
  if (((prevTPDO2 != TPDO2) && (cycleTimeTPDO2 >= MIN_CYCLE_TIME))||
      (cycleTimeTPDO2 >= MAX_CYCLE_TIME))
  {
    msgData.DLR = 8;
    msgData.id.set_stdID(getTPDO_ID(2,nodeID));                                                   
    msgData.set_byte(0,TPDO2.motorMAXTorque);                                   
    msgData.set_byte(1,TPDO2.brakeMAXTorque);                                   
    if(TPDO2.watchdogBit)  
      {
        tmpWord = tmpWord & 0x7FFF;                                             // Reset bit 7 byte 2
        TPDO2.watchdogBit = false;
      }
    else
      {
        tmpWord = tmpWord | 0x8000;                                             // Set bit 7 byte 2
        TPDO2.watchdogBit = true;
      }
    msgData.set_word(1,tmpWord);
    msgData.set_word(2,0x0000);   
    msgData.set_word(3,0x0000);
    sendMsg(&msgData);
    prevTPDO2 = TPDO2;
    cycleTimeTPDO2 = 0;    
  }
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Send the NTM message on the bus                
//  Notes       :
//------------------------------------------------------------------------------
void sendNTMMsg(    uint8_t NTMFunction,
                    uint8_t nodeID)
{
hw_can_msg_t msgData;
  msgData.DLR = 8;
  msgData.id.set_stdID(0x0);                                                    //ID always = 0 
  msgData.set_byte(0,NTMFunction);                                              //Function =0x01.Go Operational , 0x02.Stop, 0x80.Go Pre-operational, 0x81.Reset node, 0x82.Reset communication
  msgData.set_byte(1,nodeID);                                                   //Target node =0.Every node, 1..127.Specific node  
  msgData.set_word(1,0x0000);
  msgData.set_word(2,0x0000);
  msgData.set_word(3,0x0000);  
  sendMsg(&msgData);
}
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : send the sync message on the bus
//  Notes       :
//------------------------------------------------------------------------------
void sendNTMSyncMsg( void)
{
  hw_can_msg_t msgData;  
  msgData.DLR = 0; 
  msgData.id.set_stdID(0x080);                                                  //0x80=SYNC Message  
  sendMsg(&msgData);
} 
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : Get the value from the receiving message in the corresponding
//              value in t0 member RPDO1 structure
//  Notes       :
//------------------------------------------------------------------------------
void Msg2RPDO1(hw_can_msg_t *Msg)
{

uint16_t statusWord;
  RPDO1.actualSpeed     = Msg->get_word(0);
  statusWord            = Msg->get_word(1);
  RPDO1.statusByte      = Msg->get_byte(4);
  RPDO1.anin01          = Msg->get_byte(5);
  RPDO1.anin02          = Msg->get_byte(6);
  RPDO1.actualCurrent   = Msg->get_byte(7);
  RPDO1.outNMCStatus    = statusWord & 0x0001;  
  RPDO1.outNEBStatus    = statusWord & 0x0002;
  RPDO1.outA4           = statusWord & 0x0040;
  RPDO1.outA5           = statusWord & 0x0080;
  RPDO1.outA6           = statusWord & 0x0100;
  RPDO1.outA13          = statusWord & 0x0200;
  RPDO1.outA19          = statusWord & 0x0400;
  RPDO1.outA10          = statusWord & 0x0800;
  RPDO1.outA3           = statusWord & 0x1000;
  RPDO1.sensAckInProg   = statusWord & 0x2000;
  RPDO1.sensAckOK       = statusWord & 0x4000;
  RPDO1.watchdogBit     = statusWord & 0x8000; 
}
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : Get the value from the receiving message in the corresponding
//              value in t0 member RPDO2 structure
//  Notes       :
//------------------------------------------------------------------------------
void Msg2RPDO2(hw_can_msg_t *Msg)
{
  RPDO2.warningsAlarms  = Msg->get_word(0);
  RPDO2.motorTemp       = Msg->get_byte(2);
  RPDO2.inverterTemp    = Msg->get_byte(3);
  RPDO2.percentBDI      = Msg->get_byte(4);
  RPDO2.batteryCurrent  = Msg->get_byte(5);
  RPDO2.batteryVoltage  = Msg->get_word(6);
}
//------------------------------------------------------------------------------
//  returns     : uint16_t
//  Description : prepare the CANOpen RPDO ID using the formula
//                  0x180 + 0x100*(nRPDO-1) + nodeID (0x01..0x7F)
//  Notes       :
//------------------------------------------------------------------------------
uint16_t getRPDO_ID(    uint8_t numRPDO,
                        uint8_t nodeID)
{
  if ((nodeID>=0x01) && (nodeID<=0x7B))
    {
    if ((numRPDO>=0x01) && (numRPDO<=0x08))
      { 
        return (0x180 + 0x100 * (numRPDO - 1) + nodeID);
      }
    }
  return 0x0;
}
//------------------------------------------------------------------------------
//  returns     : uint16_t
//  Description : prepare the CANOpen TPDO ID using the formula
//                  0x200 + 0x100*(nTPDO-1) + nodeID (0x01..0x7F)
//  Notes       :
//------------------------------------------------------------------------------
uint16_t getTPDO_ID(    uint8_t numTPDO,
                        uint8_t nodeID)
{
  if ((nodeID>=0x01) && (nodeID<=0x7B))
    {
    if ((numTPDO>=0x01) && (numTPDO<=0x08))
      { 
        return (0x200 + 0x100 * (numTPDO - 1) + nodeID);
      }
    }
  return 0x0;
}
//------------------------------------------------------------------------------
//  returns     : uint16_t
//  Description : 0x700 + nodeID (0x01..0x7F)
//  Notes       :
//------------------------------------------------------------------------------
uint16_t getGUARD_ID( uint8_t nodeID)
{
  if ((nodeID>=0x01) && (nodeID<=0x7B))
    {
      return (0x700 + nodeID);
    }
  return 0x0;
}
//------------------------------------------------------------------------------
//  returns     : CANOpenMsgTPDO1
//  Description : Operator = overloading for the struct TPDO1
//  Notes       :
//------------------------------------------------------------------------------

CANOpenMsgTPDO1&  CANOpenMsgTPDO1::operator= (const CANOpenMsgTPDO1& OperandB)
{
  enablePower   = OperandB.enablePower;
  powerLineON   = OperandB.powerLineON;
  outNEB        = OperandB.outNEB;
  dirFWD        = OperandB.dirFWD;
  dirREV        = OperandB.dirREV;
  brakeReq      = OperandB.brakeReq;
  targetSpeed   = OperandB.targetSpeed;
  return *this;
};
//------------------------------------------------------------------------------
//  returns     : CANOpenMsgTPDO1
//  Description : Operator != overloading for the struct TPDO1
//  Notes       :
//------------------------------------------------------------------------------
bool CANOpenMsgTPDO1::operator!= (const CANOpenMsgTPDO1& OperandB) const
{
  if(enablePower != OperandB.enablePower){return true;}
  if(powerLineON != OperandB.powerLineON){return true;}
  if(outNEB      != OperandB.outNEB)     {return true;}
  if(dirFWD      != OperandB.dirFWD)     {return true;}
  if(dirREV      != OperandB.dirREV)     {return true;}
  if(brakeReq    != OperandB.brakeReq)   {return true;}
  if(targetSpeed != OperandB.targetSpeed){return true;}
  return false;
};
//------------------------------------------------------------------------------
//  returns     : CANOpenMsgTPDO2
//  Description : Operator = overloading for the struct TPDO2
//  Notes       :
//------------------------------------------------------------------------------
CANOpenMsgTPDO2&  CANOpenMsgTPDO2::operator= (const CANOpenMsgTPDO2& OperandB)
{
  motorMAXTorque   = OperandB.motorMAXTorque;
  brakeMAXTorque   = OperandB.brakeMAXTorque;
  return *this;
};
//------------------------------------------------------------------------------
//  returns     : CANOpenMsgTPDO2
//  Description : Operator != overloading for the struct TPDO2
//  Notes       :
//------------------------------------------------------------------------------
bool CANOpenMsgTPDO2::operator!= (const CANOpenMsgTPDO2& OperandB) const
{
  if(motorMAXTorque != OperandB.motorMAXTorque){return true;}
  if(brakeMAXTorque != OperandB.brakeMAXTorque){return true;}
  return false;
};
//------------------------------------------------------------------------------
//  returns     : void
//  Description : add the specific message in to list of the messages that the
//                specific bus must receive
//  Notes       : Disabled the 2nd CAN Bus
//------------------------------------------------------------------------------
void addMsgHandler(hw_can_rxmsg* CANStdMsg)
{
#ifdef HWC_CAN0
  hw_can_rx_handler[HWC_CAN0].add_msg(CANStdMsg);
#endif
#ifdef HWC_CAN4
    //hw_can_rx_handler[HWC_CAN4].add_msg(CANStdRPDO);
#endif  
}
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : call the related function for sending the message on the 
//                desidered CAN bus
//  Notes       : Disabled the 2nd CAN Bus
//------------------------------------------------------------------------------
void sendMsg( hw_can_msg_t* msgData)
{
#ifdef HWC_CAN0
    hw_can_txq[HWC_CAN0].send_msg(msgData);
#endif
#ifdef HWC_CAN4
    //hw_can_txq[HWC_CAN4].send_msg(msgData);
#endif    
}