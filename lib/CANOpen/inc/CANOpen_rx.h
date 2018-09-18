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
***************************************************************/
#ifndef _ap_bservice_CANOpen_rx_h
#define _ap_bservice_CANOpen_rx_h

#include "CANOpen.h"
#include "hw_can_msg.h"
#include "hw_io.h"


#ifndef RX_BUFFER_SIZE
#define RX_BUFFER_SIZE 216
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// receive

class CANOpenR : hw_can_rxmsg
{
public:

private:

protected:
  uint8_t CAN_Data[7];
};

class PDO1:public CANOpenR
{
public:
  bool      OutNMCStatus;
  PDO1();
  void initialize(void);
private:  
  hw_can_id CANOpenID;
};


#endif
