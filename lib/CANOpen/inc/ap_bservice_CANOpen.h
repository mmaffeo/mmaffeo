/*------------------------------------------------------------------------------
Project Name: E10 Electric

Copyright 2005 Bobcat Company as an unpublished work.
All Rights Reserved.

The information contained herein is confidential
property of Bobcat Company. The use, copying, transfer or
disclosure of such information is prohibited except
by express written agreement with Bobcat Company.

First written on 6 August 2018

Module Description:
The module broadcasts all the messages in a "CANOpen" message on the  primary 
CAN bus.
********************************************************************************/

#ifndef _ap_bservice_CANOpen_h
#define _ap_bservice_CANOpen_h

// INCLUDES
#include "hw_io.h"
#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"
// VARIABLES
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
  bool              enablePower,
                    powerLineON,
                    outNEB,
                    dirFWD,
                    dirREV,
                    watchdogBit;
  uint8_t           brakeReq;
  uint16_t          targetSpeed;
  CANOpenMsgTPDO1&  operator= (const CANOpenMsgTPDO1&);
  bool              operator!= (const CANOpenMsgTPDO1&) const;  
}; 
struct CANOpenMsgTPDO2                                                          
{
  bool      watchdogBit;
  uint8_t   motorMAXTorque,
            brakeMAXTorque;
  CANOpenMsgTPDO2&  operator= (const CANOpenMsgTPDO2&);
  bool              operator!= (const CANOpenMsgTPDO2&) const;  
};
// ENUMERATORS
enum CANOpenNodeStatus : uint8_t
{
  BOOTSTRAP             =0x00,
  STOP                  =0x04,
  OPERATIONAL           =0x05,
  PRE_OPERATIONAL       =0x7F
};
enum CANOpenFunctions  : uint8_t  
{
  GO_OPERATIONAL        =0x01,
  GO_STOP               =0x02,
  GO_PRE_OPERATIONAL    =0x80,
  RST_NODE              =0x81,
  RST_COMM              =0x82
};

//GLOBAL VARIABLES

const uint8_t               inverterNode = 0x08,
                            chargerNode  = 0x00;
static uint16_t             inverterStatusFeedback,
                            tempCmd,
                            tempCmd1;
static uint16_t             prevCycleTime,
                            cycleTime,
                            cycleTimeTPDO2,
                            cycleTimeTPDO1,
                            guardCycleTime;
extern uint16_t             cycleTimeControlMsg;

static CANOpenMsgRPDO1      RPDO1;
static CANOpenMsgRPDO2      RPDO2;
static CANOpenMsgTPDO1      TPDO1,
                            prevTPDO1;
static CANOpenMsgTPDO2      TPDO2,
                            prevTPDO2;
//DEFINES
#define MIN_CYCLE_TIME      10
#define MAX_CYCLE_TIME      20
#define GUARD_TIMEOUT       1000                                                //Timeout of the guard message in ms
#define MAX_SPEED           1500

// FUNCTION PROTOTYPE
  void CANOpenPDOInitialize(            uint8_t);
  void CANOpenNTMInitialize(            uint8_t);
  void addRPDO1Msg(                     uint8_t);
  void addRPDO2Msg(                     uint8_t);
  void addGUARDMsg(                     uint8_t);
  void sendTPDO1Msg(                    uint8_t);
  void sendTPDO2Msg(                    uint8_t);
  void sendTPDO2Msg(                    uint8_t);
  void sendNTMSyncMsg(                  void);
  void sendNTMMsg(                      uint8_t,
                                        uint8_t);
  void RPDO1_rx_callback(               hw_can_msg_t*);
  void RPDO2_rx_callback(               hw_can_msg_t*);
  void RPDO3_Fatal_rx_callback(         hw_can_msg_t*);
  void RPDO3_Standard_rx_callback(      hw_can_msg_t*);
  void RPDO3_Warning_rx_callback(       hw_can_msg_t*);
  void GUARD_rx_callback(               hw_can_msg_t*);
  void Msg2RPDO1(                       hw_can_msg_t*);
  void Msg2RPDO2(                       hw_can_msg_t*);
  uint16_t getRPDO_ID(                  uint8_t,
                                        uint8_t);
  uint16_t getTPDO_ID(                  uint8_t,
                                        uint8_t);
  uint16_t getGUARD_ID(                 uint8_t); 
  void sendMsg(                         hw_can_msg_t*);
  void addMsgHandler(                   hw_can_rxmsg*); 

  void CANOpenUpdate(                   void);
  void CANOpenInitialize(               void);
  void CANOpenChangeStatusInverter(     void); 
  void initBus(                         void);
  void getCycleTime(                    void);  
#endif

