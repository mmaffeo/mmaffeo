/*------------------------------------------------------------------------------
Project Name: E10 Electric

Copyright 2005 Bobcat Company as an unpublished work.
All Rights Reserved.

The information contained herein is confidential
property of Bobcat Company. The use, copying, transfer or
disclosure of such information is prohibited except
by express written agreement with Bobcat Company.

First written on 6 August 2018

********************************************************************************/

#ifndef _ap_bservice_CANStd_h
#define _ap_bservice_CANStd_h

// INCLUDES
#include "hw_io.h"
#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"
// STRUCTURES

static struct FaultMessageStruct
{
  bool      overU                       : 1,
            under_U                     : 1,
            underSOC                    : 1,
            overSOC                     : 1,
            overTempInCharge            : 1,
            overTempInDrive             : 1,
            underTempInCharge           : 1,
            underTempInDrive            : 1,
            openExternalWire            : 1,
            balancingNotActive          : 1,
            balancingLimited            : 1,
            faultLTC_ADCRegister        : 1,
            faultLTCDiagnose            : 1,
            faultLTCBoardOverTemp       : 1,
            faultLTCComm                : 1,
            faultLTCTempSensor          : 1,
            batteryOverCurrentInDrive   : 1,
            batteryOverCurrentInCharge  : 1,
            failureCANSync              : 1,
            failureCANPrivateComm       : 1,
            failureCANPublicComm        : 1,
            failureSDCard               : 1,
            failureCPUWatchdog          : 1,
            failureCPUExtOxill          : 1,
            failureCPUOverTemp          : 1,
            disconnectedCurrentSensor   : 1,
            openCircuitPilotLine        : 1,
            emergencyStop               : 1,
            underVoltageSupplyVoltage   : 1,
            failureBatteryHeater        : 1,
            failureBatteryCharger       : 1,
            failureMotorDriver          : 1,
            overTempPDU                 : 1,
            maxLifeTimePrechargeRelay   : 1,
            maxLifeTimeChargeRelay      : 1,
            maxLifeTimeHVPosRelay       : 1,
            maxLifeTimeHVNegRelay       : 1,
            failureInsulation           : 1,
            notsuccefullPrecharge       : 1,
            failureSlave                : 1,
            failureMaster               : 1,
            notAllowedRecharging        : 1,
            failureDualCharger          : 1,
            failureSoftwareUnit         : 1,
            failureParallelSystem       : 1,
            permanentActiveSignalTX     : 1; 
  uint8_t   moduleNumber;                 
}   fatalError, 
    failureError, 
    warningError;

static struct ActualDataStruct
{
  uint16_t  batteryVoltage,
            batteryCharge,
            batteryTemperature;
  int16_t   batteryCurrent;  
}   actualData;

static struct LimitDataStruct
{
  int16_t   maxDischargeCurrent,
            maxRecuperationCurrent;
  uint16_t  minDischargeVoltage,
            maxChargeVoltage;
}   limitData;

static struct PowerDataStruct
{
  int32_t   actualPower,
            maxDischargePower,
            maxRecuperationPower;
}   powerData;

static struct CapacityDataStruct
{
  uint16_t  totalBatteryCapacity,
            totalUsableBatteryCapacity,
            remainingBatteryCapacity,
            remainingUsableBatteryCapacity;   
}   capacityData;

static struct EnergyDataStruct
{
  uint32_t  totalEnergy,
            remainingEnergy,
            remainingUsableEnergy;   
}   energyData;

static struct ControlAnswerStruct
{
  uint8_t   stateBMS;
  bool      virtualPilotI208        : 1,
            heatherActive           : 1,
            cellBalancingActive     : 1,
            chargePermitted         : 1,
            chargeFinished          : 1,
            chargeSwitchPermitted   : 1;   
}   controlAnswer;

static struct ControlStruct
{
  uint8_t   requestedStateBMS;
  uint16_t  setDCBusVoltage,
            setChargeCurrent;
  ControlStruct&  operator= (const ControlStruct&);
  bool            operator!= (const ControlStruct&) const;
}   control,
    prevControl;


//FUNCTION DECLARATION

  void CANStdInitialize(                void);   
  void CANStdUpdate(                    void);
  void addFatalErrorMsg(                void);
  void addFailureErrorMsg(              void);
  void addWarningErrorMsg(              void);
  void addActualDataMsg(                void);
  void addLimitDataMsg(                 void);
  void addPowerDataMsg(                 void);
  void addCapacityDataMsg(              void);
  void addEnergyDataMsg(                void);
  void addControlAnswerMsg(             void);
  void sendControlMsg(                  void); 
  void fatalError_rx_callback(          hw_can_msg_t*);
  void failureError_rx_callback(        hw_can_msg_t*);
  void warningError_rx_callback(        hw_can_msg_t*);
  void actualData_rx_callback(          hw_can_msg_t*);
  void limitData_rx_callback(           hw_can_msg_t*);
  void powerData_rx_callback(           hw_can_msg_t*);
  void capacityData_rx_callback(        hw_can_msg_t*);
  void energyData_rx_callback(          hw_can_msg_t*);
  void controlAnswer_rx_callback(       hw_can_msg_t*);
  void SetFaultMessage(                 FaultMessageStruct*,
                                        hw_can_msg_t*);

#endif

