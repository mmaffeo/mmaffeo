/*------------------------------------------------------------------------------
Project Name: E10 Electric

Copyright 2005 Bobcat Company as an unpublished work.
All Rights Reserved.

The information contained herein is confidential
property of Bobcat Company. The use, copying, transfer or
disclosure of such information is prohibited except
by express written agreement with Bobcat Company.

First written on 06 August, 2018 

Module Description:
The module handle messages in CAN Standard on the primary CAN bus with the  
battery management system (BMS).   
*******************************************************************************/

// INCLUDES
#include "ap_can.h"
#include "global.h"
#include "defines.h"
#include "ap_bservice_CANOpen.h"
#include "ap_bservice_CANStd.h"
#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_types.h"

//GLOBALS
  uint16_t                  cycleTimeControlMsg;
  hw_can_rxmsg              fatalErrorMsg,
                            failureErrorMsg,
                            warningErrorMsg,
                            actualDataMsg,
                            limitDataMsg,
                            powerDataMsg,
                            capacityDataMsg,
                            energyDataMsg,
                            controlAnswerMsg,
                            controlMsg;

//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : Called every cycle of the App Main to manage the messages to
//                send
//  Notes       :
//------------------------------------------------------------------------------
void CANStdUpdate(void)
{ 

  if ((cycleTimeControlMsg > 10 && control != prevControl) || 
      cycleTimeControlMsg > 1000)
  {  
    sendControlMsg();
    prevControl = control;
    cycleTimeControlMsg = 0;
  };  
}
//------------------------------------------------------------------------------
//  returns     : NONE.
//  Description : Add the messagesthat must be received to the RX message list 
//  Notes       : 
//------------------------------------------------------------------------------
void CANStdInitialize(void)
{
   addFatalErrorMsg();
   addFailureErrorMsg();
   addWarningErrorMsg();
   addActualDataMsg();
   addLimitDataMsg();
   addPowerDataMsg();
   addCapacityDataMsg();
   addEnergyDataMsg();
   addControlAnswerMsg();
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Add Fatal error message to the RX message list 
//  Notes       :
//------------------------------------------------------------------------------
void addFatalErrorMsg(void)
{
  fatalErrorMsg.initialize();
  fatalErrorMsg.rx_id.set_stdID(0x0300);
  fatalErrorMsg.rx_id_mask.set_idr(0xFFFFFFFF);  
  fatalErrorMsg.rx_callback = fatalError_rx_callback;
  addMsgHandler(&fatalErrorMsg);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Add Failure error message to the RX message list 
//  Notes       :
//------------------------------------------------------------------------------
void addFailureErrorMsg(void)
{
  failureErrorMsg.initialize();
  failureErrorMsg.rx_id.set_stdID(0x0310);
  failureErrorMsg.rx_id_mask.set_idr(0xFFFFFFFF);  
  failureErrorMsg.rx_callback = failureError_rx_callback;
  addMsgHandler(&failureErrorMsg);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Add warning error message to the RX message list 
//  Notes       :
//------------------------------------------------------------------------------
void addWarningErrorMsg(void)
{
  warningErrorMsg.initialize();
  warningErrorMsg.rx_id.set_stdID(0x0320);
  warningErrorMsg.rx_id_mask.set_idr(0xFFFFFFFF);  
  warningErrorMsg.rx_callback = warningError_rx_callback;
  addMsgHandler(&warningErrorMsg);
}

//  void addControlMsg(                   void);

//------------------------------------------------------------------------------
//  returns     : void
//  Description : Add Actual Data message to the RX message list 
//  Notes       :
//------------------------------------------------------------------------------
void addActualDataMsg(void)
{
  actualDataMsg.initialize();
  actualDataMsg.rx_id.set_stdID(0x0330);
  actualDataMsg.rx_id_mask.set_idr(0xFFFFFFFF);  
  actualDataMsg.rx_callback = actualData_rx_callback;
  addMsgHandler(&actualDataMsg);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Add Limit Data message to the RX message list 
//  Notes       :
//------------------------------------------------------------------------------
void addLimitDataMsg(void)
{
  limitDataMsg.initialize();
  limitDataMsg.rx_id.set_stdID(0x0340);
  limitDataMsg.rx_id_mask.set_idr(0xFFFFFFFF);  
  limitDataMsg.rx_callback = limitData_rx_callback;
  addMsgHandler(&limitDataMsg);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Add Power Data message to the RX message list 
//  Notes       :
//------------------------------------------------------------------------------
void addPowerDataMsg(void)
{
  powerDataMsg.initialize();
  powerDataMsg.rx_id.set_stdID(0x0341);
  powerDataMsg.rx_id_mask.set_idr(0xFFFFFFFF);  
  powerDataMsg.rx_callback = powerData_rx_callback;
  addMsgHandler(&powerDataMsg);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Add Battery Capacity Data message to the RX message list
//  Notes       :
//------------------------------------------------------------------------------
void addCapacityDataMsg(void)
{
  capacityDataMsg.initialize();
  capacityDataMsg.rx_id.set_stdID(0x0342);
  capacityDataMsg.rx_id_mask.set_idr(0xFFFFFFFF);  
  capacityDataMsg.rx_callback = capacityData_rx_callback;
  addMsgHandler(&capacityDataMsg);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Add Energy Data message to the RX message list
//  Notes       :
//------------------------------------------------------------------------------
void addEnergyDataMsg(void)
{
  energyDataMsg.initialize();
  energyDataMsg.rx_id.set_stdID(0x0343);
  energyDataMsg.rx_id_mask.set_idr(0xFFFFFFFF);  
  energyDataMsg.rx_callback = energyData_rx_callback;
  addMsgHandler(&energyDataMsg);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Add Control Feedback message to the RX message list
//  Notes       :
//------------------------------------------------------------------------------
void addControlAnswerMsg(void)
{
  controlAnswerMsg.initialize();
  controlAnswerMsg.rx_id.set_stdID(0x0350);
  controlAnswerMsg.rx_id_mask.set_idr(0xFFFFFFFF);  
  controlAnswerMsg.rx_callback = controlAnswer_rx_callback;
  addMsgHandler(&controlAnswerMsg);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Send Control message to BMS
//  Notes       :
//------------------------------------------------------------------------------
void sendControlMsg(void)
{
hw_can_msg_t msgData;
  msgData.DLR = 8;
  msgData.id.set_stdID(0x0531);                                                 
  msgData.set_byte(0,control.requestedStateBMS);                                
  msgData.set_word(1,control.setDCBusVoltage);    //to be verified                              
  msgData.set_word(2,control.setChargeCurrent);
  sendMsg(&msgData);   
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the fatal error message is received.
//    Notes       :
//------------------------------------------------------------------------------
void fatalError_rx_callback(hw_can_msg_t *Msg)
{
  SetFaultMessage(&fatalError, Msg);  
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the fatal error message is received.
//    Notes       :
//------------------------------------------------------------------------------
void failureError_rx_callback(hw_can_msg_t *Msg)
{ 
  SetFaultMessage(&failureError, Msg);    
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the fatal error message is received.
//    Notes       :
//------------------------------------------------------------------------------
void warningError_rx_callback(hw_can_msg_t *Msg)
{ 
  SetFaultMessage(&warningError, Msg);    
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the fatal error message is received.
//    Notes       :
//------------------------------------------------------------------------------
void actualData_rx_callback(hw_can_msg_t *Msg)
{ 
  actualData.batteryVoltage     = Msg->get_word(0);
  actualData.batteryCharge      = Msg->get_word(1);
  actualData.batteryTemperature = Msg->get_word(2);
  actualData.batteryCurrent     = Msg->get_word(3); 
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the fatal error message is received.
//    Notes       :
//------------------------------------------------------------------------------
void limitData_rx_callback(hw_can_msg_t *Msg)
{ 
  limitData.maxDischargeCurrent     = Msg->get_word(0);
  limitData.maxRecuperationCurrent  = Msg->get_word(1);
  limitData.minDischargeVoltage     = Msg->get_word(2);
  limitData.maxChargeVoltage        = Msg->get_word(3);
    
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the fatal error message is received.
//    Notes       :
//------------------------------------------------------------------------------
void powerData_rx_callback(hw_can_msg_t *Msg)
{ 
  powerData.actualPower             = Msg->get_dword(0);
  powerData.maxDischargePower       = Msg->get_dword(1);
  powerData.maxRecuperationPower    = Msg->get_dword(2); //to be verified   
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the fatal error message is received.
//    Notes       :
//------------------------------------------------------------------------------
void capacityData_rx_callback(hw_can_msg_t *Msg)
{ 
  capacityData.totalBatteryCapacity             = Msg->get_word(0);
  capacityData.totalUsableBatteryCapacity       = Msg->get_word(1);
  capacityData.remainingBatteryCapacity         = Msg->get_word(2);
  capacityData.remainingUsableBatteryCapacity   = Msg->get_word(3);    
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the fatal error message is received.
//    Notes       :
//------------------------------------------------------------------------------
void energyData_rx_callback(hw_can_msg_t *Msg)
{ 
  energyData.totalEnergy            = Msg->get_dword(0);
  energyData.remainingEnergy        = Msg->get_dword(1);
  energyData.remainingUsableEnergy  = Msg->get_dword(2);    
}
//------------------------------------------------------------------------------
//    returns     : NONE.
//    Description : Called when the fatal error message is received.
//    Notes       :
//------------------------------------------------------------------------------
void controlAnswer_rx_callback(hw_can_msg_t *Msg)
{ 
  uint8_t   buffer,
            *pointer;
  controlAnswer.stateBMS = Msg->get_byte(0);
  buffer = Msg->get_byte(1);
  pointer = &buffer;
  memcpy((uint8_t*) &controlAnswer, pointer,0x01);
}
//------------------------------------------------------------------------------
//  returns     : void
//  Description : Copy the content of the received fault message in the fault
//                message structure with memcopy of 2 dword       
//  Notes       :
//------------------------------------------------------------------------------

void SetFaultMessage(FaultMessageStruct *FaultMsg,  hw_can_msg_t *Msg)
{
  uint32_t buffer;
  uint32_t *pointer,
           *pntFaultMsg;
  pntFaultMsg = (uint32_t*)FaultMsg;
  buffer = Msg->get_dword(0);
  pointer = &buffer;
  memcpy(pntFaultMsg, pointer,0x04);
  buffer = Msg->get_dword(1);
  memcpy(pntFaultMsg + 0x01, pointer,0x04);
};
//------------------------------------------------------------------------------
//  returns     : ControlStruct
//  Description : Operator = overloading for the struct ControlStruct
//  Notes       :
//------------------------------------------------------------------------------

ControlStruct&  ControlStruct::operator= (const ControlStruct& OperandB)
{
  requestedStateBMS = OperandB.requestedStateBMS;
  setDCBusVoltage   = OperandB.setDCBusVoltage;
  setChargeCurrent  = OperandB.setChargeCurrent;
  return *this;
};
//------------------------------------------------------------------------------
//  returns     : ControlStruct
//  Description : Operator != overloading for the struct ControlStruct
//  Notes       :
//------------------------------------------------------------------------------
bool ControlStruct::operator!= (const ControlStruct& OperandB) const
{
  if(requestedStateBMS  != OperandB.requestedStateBMS)  {return true;}
  if(setDCBusVoltage    != OperandB.setDCBusVoltage)    {return true;}
  if(setChargeCurrent   != OperandB.setChargeCurrent)   {return true;}
  return false;
};
