/***************************************************************
*
* Copyright 2016 Bobcat Company as an unpublished work.
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Bobcat Company. The use, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Bobcat Company.
*
* First written on 18 October, 2016 by Al Liebel
*
* Module Description:
* Routines for ECU Interface.
***************************************************************/

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "ap_engine.h"
#include "ap_can.h"
#include "global.h"
#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"
#include "ap_subs.h"

hw_can_txmsg DD_CAN4TX;
hw_can_txmsg CCVS_CAN4TX;
hw_can_txmsg EEC2_CAN4TX;
hw_can_txmsg SMVCU_CAN4TX;
hw_can_txmsg AAI_CAN4_TX;

hw_can_rxmsg EEC1_RX;
hw_can_rxmsg ET1_RX;
hw_can_rxmsg AMB_RX;
hw_can_rxmsg EFL_P1_RX;
hw_can_rxmsg ActiveCodes_RX;
hw_can_rxmsg LFE_CAN4_RX;
hw_can_rxmsg LFC_RX;
hw_can_rxmsg HOURS_RX;
hw_can_rxmsg Shutdown_RX;

J1939_TP_rx ECU_TP_rx;

//************************************************************************************************
//
// ENGINE TX MESSAGES
//
//************************************************************************************************
void update_EEC2_J1939_CAN4_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates Throttle Position TX Message data for J1939 protocol.
//    Notes       :
//******************************************************************************
{
  if(cmd_Throttle <= CONSTANT_DATA->LOW_IDLE_COMMAND)
  {
    msg->set_byte(1,0);
  }
  else
  {
    msg->set_byte(1,(uint8_t)(percent_Throttle/4));
  }

}

static void initialize_EEC2_CAN4_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  EEC2_CAN4TX.initialize();

  EEC2_CAN4TX.mbuff.id.set_J1939ID(PRIORITY_3, EEC2_PF, EEC2_PS, nvm_ecuid.j1939_source_address);
  EEC2_CAN4TX.pre_tx_callback = update_EEC2_J1939_CAN4_TX;
  EEC2_CAN4TX.set_send_rate(5);


  hw_can_tx_scheduler[HWC_CAN4].add_msg(&EEC2_CAN4TX);
}

void update_SMVCU_CAN4_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates Throttle Position TX Message data for J1939 protocol.
//    Notes       :
//******************************************************************************
{
  static uint8_t counter = 0;
  uint8_t checksum;
  uint8_t temp;
  
  if(cmd_Throttle <= CONSTANT_DATA->LOW_IDLE_COMMAND)
  {
    temp = 0;
  }
  else
  {
    temp = (uint8_t)(percent_Throttle/4);
  }
 
//checksum per J1939 SPN4207
  checksum =  temp;  // byte 1
  checksum += 0xFA;  //6 x 0xFF, bytes 2-7
  checksum += counter;
  checksum += PRIORITY_6 << 2;
  checksum += PROPRIETARY_B;
  checksum += SMVCU_PS;
  checksum += nvm_ecuid.j1939_source_address;
  checksum = (((checksum >> 6) & 0x03) + (checksum >> 3) + checksum) & 0x07;

  msg->set_byte(0, temp);
  msg->set_byte(7, (counter) | (checksum << 4));
  
  counter++;
  counter &= 0x07;
}

static void initialize_SMVCU_CAN4_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  SMVCU_CAN4TX.initialize();

  SMVCU_CAN4TX.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, SMVCU_PS, nvm_ecuid.j1939_source_address);
  SMVCU_CAN4TX.pre_tx_callback = update_SMVCU_CAN4_TX;
  SMVCU_CAN4TX.set_send_rate(5);


  hw_can_tx_scheduler[HWC_CAN4].add_msg(&SMVCU_CAN4TX);
}


void update_DD_CAN4_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  msg->set_byte(1, (uint8_t)gau_FuelLevel);
}

static void initialize_DD_CAN4_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  DD_CAN4TX.initialize();
  DD_CAN4TX.mbuff.id.set_J1939ID(PRIORITY_6, DD_PF, DD_PS, nvm_ecuid.j1939_source_address);

  DD_CAN4TX.set_send_rate(100);
  DD_CAN4TX.pre_tx_callback = update_DD_CAN4_TX;

  hw_can_tx_scheduler[HWC_CAN4].add_msg(&DD_CAN4TX);
}

void update_CCVS_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 30 Mar, 2011
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  if((state_Console == INACTIVE))
  {
    msg->set_byte(0, 0x04);
  }
  else
  {
    msg->set_byte(0, 0);
  }

  msg->set_byte(1, 0);
  msg->set_byte(2, 0);
}

static void initialize_CCVS_CAN4_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  CCVS_CAN4TX.initialize();
  CCVS_CAN4TX.mbuff.id.set_J1939ID(PRIORITY_6, CCVS_PF, CCVS_PS, nvm_ecuid.j1939_source_address);

  CCVS_CAN4TX.set_send_rate(10);
  CCVS_CAN4TX.pre_tx_callback = update_CCVS_TX;

  hw_can_tx_scheduler[HWC_CAN4].add_msg(&CCVS_CAN4TX);
}

static void update_AAI_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//		        msg : Data to be sent.
//		Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//*******************f*******************************************
{
  if((state_HOT == OORL) || (state_HOT == OORH))
  {
    msg->set_byte(0, UNDEFINED);
  }
  else
  {
    msg->set_byte(0, (uint8_t)((flt_HOT * 71) >> 7));  // Convert F-40 to C-40   71/128 ~= 5/9
  }
}

static void initialize_AAI_CAN4_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//		Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  AAI_CAN4_TX.initialize();
  AAI_CAN4_TX.mbuff.id.set_J1939ID(PRIORITY_7, AAI_PF, AAI_PS, nvm_ecuid.j1939_source_address);
  																					 
  AAI_CAN4_TX.set_send_rate(100);
  AAI_CAN4_TX.pre_tx_callback = update_AAI_TX;
  
  hw_can_tx_scheduler[HWC_CAN4].add_msg(&AAI_CAN4_TX);
}

//************************************************************************************************
//
// ENGINE RX MESSAGES
//
//************************************************************************************************

static void EEC1_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 27 July, 2009
//    Description : Receive engine speed from engine controller.
//    Notes       :
//******************************************************************************
{
  ecu_EngineSpeed = ((msg->get_byte(4) << 8) + msg->get_byte(3)) >> 3;
  ecu_EngineStarterMode = msg->get_byte(6) & 0x0F;
  ecu_PercentTorque = msg->get_byte(2) - 125;
}


static void initialize_EEC1_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 27 July, 2009
//    Description : Initializes receiver CAN message setting up required filters.
//    Notes       :
//******************************************************************************
{
  EEC1_RX.initialize();
  EEC1_RX.rx_id     .set_J1939ID(0, EEC1_PF, EEC1_PS, SA_ECU);
  EEC1_RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  EEC1_RX.rx_callback = EEC1_rx_callback;

  hw_can_rx_handler[HWC_CAN4].add_msg(&EEC1_RX);
}


void ET1_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 27 July, 2009
//    Description : Receive engine coolant temperature from engine controller.
//    Notes       :
//******************************************************************************
{
  uint8_t temp_byte;
  uint16_t temp_word;
  
  temp_byte = msg->get_byte(0);
  ecu_ECT = (temp_byte == UNDEFINED) ? 0 : CelsiusToFahrenheit[temp_byte];
  state_ecuECT = NORMAL;
  
  temp_byte = msg->get_byte(1);
  can_FuelTemp = (temp_byte == UNDEFINED) ? 0 : CelsiusToFahrenheit[temp_byte];
  
  //EOT_C = data/32 - 273
  //EOT_C + 40 = data/32 - 233       we want offset by 40
  //So, data/32 - 233 must be > 0 to avoid negative number
  //    data > 233 * 32
  //    data > 7456

  temp_word = msg->get_byte(2) + (msg->get_byte(3) << 8);

  if(temp_word < 7456 || temp_word == 0xFFFF) //less than -40°C or Undefined
  {
    ecu_EOT = 0; //-40C
  }
  else
  {
    temp_word = (temp_word >> 5) - 233;  // offset is -273, change to -233 to get to -40
    ecu_EOT =  (temp_word > 255) ? 0 : CelsiusToFahrenheit[temp_word];
  }
}

static void initialize_ET1_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 27 July, 2009
//    Description : Initializes receiver CAN message setting up required filters.
//    Notes       :
//******************************************************************************
{
  ET1_RX.initialize();
  ET1_RX.rx_id     .set_J1939ID(0, ET1_PF, ET1_PS, SA_ECU);
  ET1_RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  ET1_RX.rx_callback = ET1_rx_callback;

  hw_can_rx_handler[HWC_CAN4].add_msg(&ET1_RX);
}

void EFL_P1_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 27 July, 2009
//    Description : Receive engine oil pressure from engine controller.
//    Notes       :
//******************************************************************************
{
  // 1 PSI = 6.895 KPa so multiply and round up
  // now for J1939 format 1 bit = 4 KPA shift by 2 + 16.8 format so shift by 10
  ecu_EOP = (uint8_t) ((uint16_t) (((((uint32_t)(msg->get_byte(3)) << 10)) + 0x200) / (uint32_t)(PSITOKPA))) ;


  if(CONSTANT_DATA->ECU_FUNCTION == ECU_J1939)
  {
    if((ecu_EOP > ecu_BarPressure) && (ecu_BarPressure != UNDEFINED))
    {
      ecu_EOP = ecu_EOP - ecu_BarPressure;
    }
    else
    {
      ecu_EOP = 0;
    }
  }

  state_ecuEOP = NORMAL;
}

static void initialize_EFL_P1_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 27 July, 2009
//    Description : Initializes receiver CAN message setting up required filters.
//    Notes       :
//******************************************************************************
{
  EFL_P1_RX.initialize();
  EFL_P1_RX.rx_id     .set_J1939ID(0, EFL_P1_PF, EFL_P1_PS, SA_ECU);
  EFL_P1_RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  EFL_P1_RX.rx_callback = EFL_P1_rx_callback;

  hw_can_rx_handler[HWC_CAN4].add_msg(&EFL_P1_RX);
}


void LFE_CAN4_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Feb, 2011
//    Description : Get fuel rate.
//    Notes       :
//******************************************************************************
{
  can_FuelRate = msg->get_byte(0) + (msg->get_byte(1) << 8);
}

static void initialize_LFE_CAN4_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Feb, 2011
//    Description : Initializes receiver CAN message for DPF indicator.
//    Notes       :
//******************************************************************************
{
  LFE_CAN4_RX.initialize();
  LFE_CAN4_RX.rx_id     .set_J1939ID(0, LFE_PF, LFE_PS, SA_ECU);
  LFE_CAN4_RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  LFE_CAN4_RX.rx_callback = LFE_CAN4_rx_callback;

  hw_can_rx_handler[HWC_CAN4].add_msg(&LFE_CAN4_RX);
}


void LFC_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Feb, 2011
//    Description : Get fuel rate.
//    Notes       :
//******************************************************************************
{
  can_FuelConsumption = msg->get_byte(4) + ((uint32_t)msg->get_byte(5) << 8) + ((uint32_t)msg->get_byte(6) << 16) + ((uint32_t)msg->get_byte(7) << 24);

  if(start_FuelConsumption == 0xFFFFFFFF)
  {
    start_FuelConsumption = can_FuelConsumption;
  }
}


static void initialize_LFC_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Feb, 2011
//    Description : Initializes receiver CAN message for DPF indicator.
//    Notes       :
//******************************************************************************
{
  LFC_RX.initialize();
  LFC_RX.rx_id     .set_J1939ID(0, LFC_PF, LFC_PS, SA_ECU);
  LFC_RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  LFC_RX.rx_callback = LFC_rx_callback;

  hw_can_rx_handler[HWC_CAN4].add_msg(&LFC_RX);
}


void HOURS_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Feb, 2011
//    Description : Get fuel rate.
//    Notes       :
//******************************************************************************
{
  ecu_Hours = ((uint32_t)(msg->get_byte(3)) << 24) + ((uint32_t)msg->get_byte(2) << 16) + ((uint32_t)msg->get_byte(1) << 8) + (uint32_t)msg->get_byte(0);
  ecu_Hours = (ecu_Hours*10) / 20;     // 0.05 hr/bit - 0 - 210554060.75 hr

  flag_RxECUHours = TRUE;
}

static void initialize_HOURS_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Feb, 2011
//    Description : Initializes receiver CAN message for DPF indicator.
//    Notes       :
//******************************************************************************
{
  HOURS_RX.initialize();
  HOURS_RX.rx_id     .set_J1939ID(0, ENGINE_HOURS_PF, ENGINE_HOURS_PS, SA_ECU);
  HOURS_RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  HOURS_RX.rx_callback = HOURS_rx_callback;

  hw_can_rx_handler[HWC_CAN4].add_msg(&HOURS_RX);
}


void Shutdown_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 July, 2009
//    Description : Receive glow plug state from engine controller.
//    Notes       :
//******************************************************************************
{
  ecu_GlowPlug = msg->get_byte(3) & 0x03;
}

static void initialize_Shutdown_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 July, 2009
//    Description : Initializes receiver CAN message setting up required filters.
//    Notes       :
//******************************************************************************
{
  Shutdown_RX.initialize();
  Shutdown_RX.rx_id     .set_J1939ID(0, SHUTDOWN_PF, SHUTDOWN_PS, SA_ECU);
  Shutdown_RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  Shutdown_RX.rx_callback = Shutdown_rx_callback;

  hw_can_rx_handler[HWC_CAN4].add_msg(&Shutdown_RX);
}


void AMB_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 27 July, 2009
//    Description : Receive engine coolant temperature from engine controller.
//    Notes       :
//******************************************************************************
{
  uint8_t temp_byte;
  
  // 1 kPa = 0.145 PSI
  ecu_BarPressure = msg->get_byte(0) >> 1;  // 0.5kPa per bit, 0 offset
  ecu_BarPressure = (uint8_t)(((uint16_t)ecu_BarPressure*37) >> 8);

  temp_byte = msg->get_byte(5);
  ecu_AirInletTemp = (temp_byte == UNDEFINED) ? 0 : CelsiusToFahrenheit[temp_byte];
}

static void initialize_AMB_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 27 July, 2009
//    Description : Initializes receiver CAN message setting up required filters.
//    Notes       :
//******************************************************************************
{
  AMB_RX.initialize();
  AMB_RX.rx_id     .set_J1939ID(0, AMB_PF, AMB_PS, SA_ECU);
  AMB_RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  AMB_RX.rx_callback = AMB_rx_callback;
  hw_can_rx_handler[HWC_CAN4].add_msg(&AMB_RX);
}


void ActiveCodes_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 July, 2009
//    Description : Receive error codes from engine controller.
//    Notes       :
//******************************************************************************
{
  if(enable_ECUDM1)
  {
    lamp_Engine = 0;

    //Only one code so only use zero
    EngineFailureQueue[0].SPN = ((uint32_t)((msg->get_byte(4)) & 0xE0) << 11) | ((uint16_t)(msg->get_byte(3)) << 8) | (msg->get_byte(2));
    EngineFailureQueue[0].FMI = (msg->get_byte(4)) & 0x1F;
    EngineFailureQueue[0].OC = (msg->get_byte(5) & 0x7F);
    EngineFailureQueue[0].CM = (msg->get_byte(5) & 0x80) >> 7;

    if((EngineFailureQueue[0].SPN == 1485) && (EngineFailureQueue[0].FMI == 11) && (CONSTANT_DATA->IGNORE_1485_FAULT != NON_FUNCTIONAL))
    {
    }
    else if(EngineFailureQueue[0].SPN != 0)
    {
      #ifdef HCS12_BSP_EMU //if M4 compile this
      QueueEventDiagECU(ENGINE_ERROR_ID, EngineFailureQueue[0].SPN, EngineFailureQueue[0].FMI & 0xFF, current_user, actualHourMeter/HOUR_METER_TO_HOUR_FCT);
      #endif
      ErrorQueueDisplayList(ENGINE_ERROR_ID, (uint8_t)EngineFailureQueue[0].SPN, EngineFailureQueue[0].FMI, (uint16_t)(EngineFailureQueue[0].SPN >> 8), TYPE_SPN);
      lamp_Engine = (msg->get_byte(1) << 8) | msg->get_byte(0);
    }
  }
}

static void initialize_ActiveCodes_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 July, 2009
//    Description : Initializes receiver CAN message setting up required filters.
//    Notes       :
//******************************************************************************
{
  ActiveCodes_RX.initialize();
  ActiveCodes_RX.rx_id     .set_J1939ID(0, ACTIVE_CODES_PF, ACTIVE_CODES_PS, SA_ECU);
  ActiveCodes_RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  ActiveCodes_RX.rx_callback = ActiveCodes_rx_callback;

  hw_can_rx_handler[HWC_CAN4].add_msg(&ActiveCodes_RX);
}

void process_Engine_TP_cmd(const J1939_msg_t *request)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 28 July, 2009
//    Description : Initializes receiver CAN message setting up required filters.
//    Notes       :
//******************************************************************************
{
  uint8_t temp_PF;
  uint8_t temp_PS;
  uint16_t msg_Length, count_Stop;
  uint32_t temp_SPN;
  uint8_t temp_FMI;

  temp_PF = (uint8_t)request->id.get_J1939_PF();
  temp_PS = (uint8_t)request->id.get_J1939_PS();

  if((temp_PF == ACTIVE_CODES_PF) && (temp_PS == ACTIVE_CODES_PS))
  {
    msg_Length = request->length-2;
    //Byte: 0 bits 8-7 Malfunction Indicator Lamp Status See 5.7.1.1
    //        bits 6-5 Red Stop Lamp Status See 5.7.1.2
    //        bits 4-3 Amber Warning Lamp Status See 5.7.1.3
    //        bits 2-1 Protect Lamp Status See 5.7.1.4
    //Byte: 1 bits 8-7 Flash Malfunction Indicator Lamp See 5.7.1.5
    //        bits 6-5 Flash Red Stop Lamp See 5.7.1.6
    //        bits 4-3 Flash Amber Warning Lamp See 5.7.1.7
    //        bits 2-1 Flash Protect Lamp See 5.7.1.8
    //Byte: 2 bits 8-1 SPN, 8 least significant bits of SPN See 5.7.1.9
    //        (most significant at bit 8)
    //Byte: 3 bits 8-1 SPN, second byte of SPN See 5.7.1.9
    //        (most significant at bit 8)
    //Byte: 4 bits 8-6 SPN, 3 most significant bits See 5.7.1.9
    //        (most significant at bit 8)
    //        bits 5-1 FMI
    //        (most significant at bit 5) See 5.7.1.10
    //Byte: 5 bit 8 SPN Conversion Method See 5.7.1.11
    //        bits 7-1 Occurrence Count See 5.7.1.12

    if(enable_ECUDM1)
    {
      lamp_Engine = 0;

      count_Stop = msg_Length / 4;  // Determine the number of codes, 4 bytes per code;

      if(count_Stop > MAX_NUMBER_OF_SPN)
      {
        count_Stop = MAX_NUMBER_OF_SPN;
      }

      for(uint16_t i = 0; i < count_Stop; i++)
      {
        temp_SPN = ((uint32_t)((request->data[i*4+4]) & 0xE0) << 11) | ((uint16_t)(request->data[i*4+3]) << 8) | (request->data[i*4+2]);
        temp_FMI = (request->data[i*4+4]) & 0x1F;

        if(temp_SPN != 0)
        {
          EngineFailureQueue[i].SPN = temp_SPN;
          EngineFailureQueue[i].FMI = temp_FMI;
          EngineFailureQueue[i].OC = (request->data[i*4+5] & 0x7F);
          EngineFailureQueue[i].CM = (request->data[i*4+5] & 0x80) >> 7;

          if((EngineFailureQueue[i].SPN == 1485) && (EngineFailureQueue[i].FMI == 11) && (CONSTANT_DATA->IGNORE_1485_FAULT != NON_FUNCTIONAL))
          {
          }
          else
          {
            #ifdef HCS12_BSP_EMU //if M4 compile this
              QueueEventDiagECU(ENGINE_ERROR_ID, EngineFailureQueue[i].SPN, EngineFailureQueue[i].FMI & 0xFF, current_user, actualHourMeter/HOUR_METER_TO_HOUR_FCT);
            #endif
            ErrorQueueDisplayList(ENGINE_ERROR_ID, (uint8_t)EngineFailureQueue[i].SPN, EngineFailureQueue[i].FMI, (uint16_t)((EngineFailureQueue[i].SPN >> 8)), TYPE_SPN);
            lamp_Engine = (request->data[1] << 8) | request->data[0];
          }
        }
      }
    }
  }

  if((temp_PF == EC1_PF) && (temp_PS == EC1_PS))
  {
    flag_RxRPMMin = TRUE;
    ecu_isocMinRPM = ((request->data[1] << 8) + (request->data[0])) >> 3;
  }

  if((temp_PF == SOFT_PF) && (temp_PS == SOFT_PS))
  {
    msg_Length = request->length;
                  
    for(uint8_t i=0; i<msg_Length; i++)
    {
      if(i < ECU_SOFT_LENGTH)
      {
        ecu_SOFT[i] = request->data[i];
      }
    }

    if((request->data[4] == CONSTANT_DATA->ECU_DISPLACEMENT) && (request->data[6] == CONSTANT_DATA->ECU_REGION_1)
    && (request->data[7] == CONSTANT_DATA->ECU_REGION_2) && (request->data[8] == CONSTANT_DATA->ECU_APP))
    {
      ecu_HP = ((request->data[9] - 0x30) * 10) + (request->data[10] - 0x30);
    }
  }
}


void ap_ECU_update(void)
//******************************************************************************
//    returns     : NONE.
//		        
//    Created By  : Al Liebel
//    Date Created: 20 October, 2016
//    Description : Update ECU TP messages.
//    Notes       :
//******************************************************************************
{  
    
    static uint16_t delay_ECUDM1 = 0;

    //Delay to ignore ECU DM1 messages at powerup
    if((!enable_ECUDM1) && (delay_ECUDM1++ > CONSTANT_DATA->ECU_DM1_DELAY))
    {
        enable_ECUDM1 = TRUE;
    }

    ECU_TP_rx.update();

    if(ECU_TP_rx.MsgAvailiable())
    {
        if(ECU_TP_rx.jmsg.id.get_J1939_SA() == SA_ECU)
        {
            process_Engine_TP_cmd(&ECU_TP_rx.jmsg);
            ECU_TP_rx.FreeBuffer();
        }
        process_Engine_TP_cmd(&ECU_TP_rx.jmsg);
        ECU_TP_rx.FreeBuffer();
    }
    
    //Set ECU message age to 0 if hold is inactive that way when hold becomes active it doesn't fault out right away.
    if((state_Engine == ENGINE_CRANKING) || (state_ECUHold != ACTIVE)) 
    {   
        EEC1_RX.msg_age_mS = 0;
    }
    msgAge_ECU = EEC1_RX.msg_age_mS;
}

void ap_ECU_initialize(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : Al Liebel
//    Date Created: 20 October, 2016
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
    initialize_DD_CAN4_TX();
    initialize_EEC2_CAN4_TX();
    initialize_CCVS_CAN4_TX();
    initialize_AAI_CAN4_TX();
    initialize_EEC1_rx();
    initialize_ET1_rx();
    initialize_AMB_rx();
    initialize_EFL_P1_rx();
    initialize_ActiveCodes_rx();
    initialize_LFE_CAN4_rx();
    initialize_LFC_rx();
    initialize_HOURS_rx();
    initialize_Shutdown_rx();
    
    if(CONSTANT_DATA->ECU_STAGE_V_FUNCTION != NON_FUNCTIONAL)
    {  
      initialize_SMVCU_CAN4_TX();
    }
    
    ECU_TP_rx.initialize(0xFF, HWC_CAN4);
    enable_ECUDM1 = FALSE;
    ecu_SOFT[0] = 0x00; //set first character to null for empty string
    
    start_FuelConsumption = 0xFFFFFFFF;
    can_FuelConsumption = 0xFFFFFFFF;
    flag_RxRPMMax = FALSE;
    flag_RxRPMMin = FALSE;
    flag_RxECUHours = FALSE;
    flag_RxDPFHours = FALSE;

    if(CONSTANT_DATA->ECU_FUNCTION == ECU_J1939)
    {
        ecu_isocMinRPM = CONSTANT_DATA->ECU_MIN_ENGINE_SPEED_LOW;
        ecu_isocMaxRPM = CONSTANT_DATA->ECU_MAX_ENGINE_SPEED_LOW;
    }
    else
    {
        ecu_isocMaxRPM = CONSTANT_DATA->THROTTLE_PRI_OUT_HIGH;
        ecu_isocMinRPM = CONSTANT_DATA->THROTTLE_PRI_OUT_LOW;
    }

    ecu_BarPressure = 0xFF;
    state_ecuECT = 0;
    state_ecuEOP = 0;
}