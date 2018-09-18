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

#ifndef _CANOpen_h
#define _CANOpen_h

// INCLUDES
#include "hw_io.h"

// STRUCTURES
struct CANOpenMsgRPDO1                                                          
{
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
};
struct CANOpenMsgRPDO2
{
  int8_t    inverterTemp;
  uint8_t   motorTemp,
            percentBDI,
            batteryCurrent;
  uint16_t  batteryVoltage,
            warningsAlarms;                 
};
struct CANOpenMsgTPDO1                                                          
{
  bool      enablePower,
            powerLineON,
            outNEB,
            dirFWD,
            dirREV,
            watchdogBit;
  uint8_t   brakeReq;
  uint16_t  targetSpeed;
};
struct CANOpenMsgTPDO2                                                          
{
  bool      watchdogBit;
  uint8_t   motorMAXTorque,
            brakeMAXTorque;
};
// GLOBAL VARIABLES 
//extern CANOpenMsgRPDO1 RPDO1;
//extern CANOpenMsgRPDO2 RPDO2;
//extern CANOpenMsgTPDO1 TPDO1;
//extern CANOpenMsgTPDO2 TPDO2;


// FUNCTION PROTOTYPE
//void CANOpen_initialize(void);
//void CANOpen_update(void);
//Conversion function from CAN message to CANOpen 
//void Msg2RPDO(      hw_can_msg_t*,
//                    CANOpenMsgRPDO1*);
//void Msg2RPDO(      hw_can_msg_t*,
//                    CANOpenMsgRPDO2*);
//uint8_t getStatus(  hw_can_msg_t*);
//Conversion function from CANOpen to CAN messages
//void initialize(    void);
//void sendTPDO(      CANOpenMsgTPDO1*,
//                    hw_can_msg_t*);
//void sendTPDO(      CANOpenMsgTPDO2*,
//                    hw_can_msg_t* );
//void syncMsg(       hw_can_msg_t* );
//void setNTMMsg(     hw_can_msg_t* );
//void sendMsg(       hw_can_msg_t* );
//class CANOpenNTM;
//******************************************************************************
//  Class       : CANOpen
//  Description : Base class of the CANOPen messages structures
//  Notes       : 
//******************************************************************************
class CANOpenRx : public hw_can_rxmsg
{
//Member variables
public:
//  hw_can_rxmsg              CANOpenRPDO1,
//                            CANOpenRPDO2;
   
private:
    uint16_t                prevTime,
                            prevTime1;
//  uint8_t                   nodeID;
//  CANOpenMsgRPDO1           RPDO1;  
//  CANOpenMsgRPDO2           RPDO2;  
//  CANOpenMsgTPDO1           TPDO1; 
//  CANOpenMsgTPDO2           TPDO2;   
  
//Member Functions
public:
//  void sendTPDO1Msg(        void);
//  void sendTPDO2Msg(        void);

protected:
  void sendMsg(             hw_can_msg_t*); 
  uint16_t getRPDO_ID(      uint8_t,
                            uint8_t);
//  uint16_t getTPDO_ID(      uint8_t,
//                            uint8_t);
//  uint16_t getGUARD_ID(     uint8_t);
  void addMsgHandler(       hw_can_rxmsg*);  
private:
//  void addRPDO1Msg(         uint8_t);
//  void addRPDO2Msg(         uint8_t);

//  void Msg2RPDO1(           hw_can_msg_t*);
//  void Msg2RPDO2(           hw_can_msg_t*);

};
#endif

