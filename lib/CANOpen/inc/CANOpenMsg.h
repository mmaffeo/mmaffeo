/***************************************************************
* Project Name: E10 Electric
*
* Copyright 2005 Bobcat Company as an unpublished work.
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Bobcat Company. The use, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Bobcat Company.
*
* First written on 6 August 2018
*
* Module Description:
* The module broadcasts all the messages in a "CANOpen" message on the secondary
* CAN bus.  It also handles all error code routines.
***************************************************************/

#ifndef _CANOpenMsg_h
#define _CANOpenMsg_h

// INCLUDES
#include "hw_io.h"

// STRUCTURES


//******************************************************************************
//  Class       : CANOpenDO
//  Description : Managing the PDO message exchanged with the different node
//  Notes       : Craete one object for each addressed node from this CNTLR
//  the nummber of managed PDO is limited by two. (ZAPI requirements)
//******************************************************************************
class CANOpenRPDO1 : public CANOpenRx
{
//Member variables
public:

private:
  uint8_t                   nodeID;
  bool      outNMCStatus,
            outNEBStatus,
            outA3,
            outA4,
            outA5,
            outA6,
            outA10,
            outA13,
            outA19,
            sensAckInProg,
            sensAckOK,
            watchdogBit;
  uint8_t   statusByte,
            anin01,
            anin02,
            actualCurrent;
  int16_t   actualSpeed;      
  
//Member Functions
public:
  void Initialize(          int8_t);
 
private:
  void addRPDO1Msg(         uint8_t);
  void Msg2RPDO1(           void);
};
////******************************************************************************
////  Class       : CANOpenNTM
////  Description : Managing the NTM & GUARD message exchanged with the different 
////                  node suppose that the controller is the Master
////  Notes       : 
////******************************************************************************
//class CANOpenNTM : public CANOpen
//{
////Member variables
//public:
//  hw_can_rxmsg              CANOpenGuard;   
//private:
//  uint8_t                   nodeID;
//
////Member Functions
//public:
//  CANOpenNTM(                uint8_t);
//  void sendSyncMsg(         void);  
//private:
//  void addGUARDMsg(         uint8_t);
//  void sendNTMMsg(          uint8_t,
//                            uint8_t);
//  
//};
//
////******************************************************************************
////  Class       : CANOpenManag
////  Description : Managing the CANOPen structure
////  Notes       : 
////******************************************************************************
//class CANOpenManag 
//{
//  //Member variables
//public:
////  hw_can_rxmsg              CANOpenRPDO1,
////                            CANOpenRPDO2;
//    CANOpenNTM* CANOpenNTMMsg =  new CANOpenNTM(0x08);  
//private:
//    uint16_t                prevTime,
//                            prevTime1;
//  
////  uint8_t                   nodeID;
////  CANOpenMsgRPDO1           RPDO1;  
////  CANOpenMsgRPDO2           RPDO2;  
////  CANOpenMsgTPDO1           TPDO1; 
////  CANOpenMsgTPDO2           TPDO2;   
//  
////Member Functions
//public:
//  CANOpenManag(             void);
//  void Update(              void);  
//  void Initialize(          void);
////  void sendTPDO1Msg(        void);
////  void sendTPDO2Msg(        void);  
//protected:
////  void sendMsg(             hw_can_msg_t*); 
////  uint16_t getRPDO_ID(      uint8_t,
////                            uint8_t);
////  uint16_t getTPDO_ID(      uint8_t,
////                            uint8_t);
////  uint16_t getGUARD_ID(     uint8_t);
////  void addMsgHandler(       hw_can_rxmsg*);  
//private:
////  void addRPDO1Msg(         uint8_t);
////  void addRPDO2Msg(         uint8_t);
////  void Msg2RPDO1(           hw_can_msg_t*);
////  void Msg2RPDO2(           hw_can_msg_t*);
//};
#endif

