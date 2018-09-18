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
* First written on 26 October, 2005 by Spencer Mindeman
*
* Module Description:
* CAN routines to send out routines specified in requirements.
***************************************************************/

//******************************************************************************
// INCLUDES
//******************************************************************************
#include "hw_io.h"
#include "nvm_ecuid.h"
#include "ap_bservice.h"
#include "cdata.h"
#include "defines.h"

#include "MX_Gtwy_Control.h"
#include "MX_Gtwy_Control_private.h"
#include "ap_MXGWcontrol_defs.h"
#include "ap_main.h"
#include "ap_subs.h"
#include "ap_dv.h"
#include "ap_eeprom.h"
#include "ap_can.h"
#include "ap_gateway.h"
#include "ap_deluxeG5.h"
#include "global.h"

//******************************************************************************
// DEFINE SECTION
//******************************************************************************


//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************
//RECEIVE MESSAGES
hw_can_rxmsg CAN_STsRX; // Auxiliary Start/Stop Command
hw_can_rxmsg CAN_ACDsRX;
hw_can_rxmsg PanelButtonStateIntRX; 
hw_can_rxmsg HWJ1939PanelExternalIORX;
hw_can_rxmsg CAN01_ThrottleRX;
hw_can_rxmsg CAN01_SecondaryRX;
hw_can_rxmsg HWJ1939RequestMsgIntRX;
hw_can_rxmsg HoursUpdatesRX;
hw_can_rxmsg SOFT_RX;
hw_can_rxmsg DigDepthStatusRX;
hw_can_rxmsg LFE_CAN0_RX;
hw_can_rxmsg BJM2RightRX;
hw_can_rxmsg BJM2LeftRX;
hw_can_rxmsg msgRX_SecondaryControls;
hw_can_rxmsg msgRX_HydControlSettings;
//hw_can_rxmsg Test44RX;//Temporary for fast travel R&D

//TRANSMIT MESSAGES
hw_can_txmsg HWJ1939EngineHoursIntTX;
hw_can_txmsg EEC1_CAN0TX;
hw_can_txmsg VEP_CAN0_TX;
hw_can_txmsg TFAC_TX;
hw_can_txmsg msgTX_PanelTellTales;
hw_can_txmsg msgTX_PanelButtons;
hw_can_txmsg msgTX_PanelGauge;
hw_can_txmsg msgTX_PanelLCD;
hw_can_txmsg msgTX_PanelLCDIcons;
hw_can_txmsg ET1_CAN0TX;
hw_can_txmsg EFL_P1_CAN0TX;
hw_can_txmsg HWJ1939BICSControlTX;
hw_can_txmsg HWJ1939AcknowledgeMsgIntTX;
hw_can_txmsg HWJ1939ConfigMsgIntTX;
hw_can_txmsg msgTX_PrimaryControls;
hw_can_txmsg DD_CAN0TX;
hw_can_txmsg EEC2_CAN0TX;
hw_can_txmsg AAI_CAN0_TX;
hw_can_txmsg msgTX_AuxControlMode;

hw_can_txmsg CAN01sTX;
hw_can_txmsg CAN02sTX;
hw_can_txmsg CAN03sTX;  // Auxiliary Start/Stop Command
hw_can_txmsg CAN05sTX;
hw_can_txmsg CAN06sTX;
hw_can_txmsg CAN21sTX;  // Auxiliary Hydraulics Information
hw_can_txmsg CAN21extTX;
hw_can_txmsg CAN20sTX; // Auxiliary Hydraulics Control Command
//hw_can_txmsg TestCAN45sTX;
//hw_can_txmsg TestCAN46sTX;

J1939_TP_tx SOFT_TP_tx; 
J1939_msg_t SOFT_TP_msg;
uint8_t SOFTmsgData[100];

J1939_TP_tx VIN_TP_tx; 
J1939_msg_t VIN_TP_msg;
uint8_t VINmsgData[VIN_MSG_LENGTH];

uint8_t STAuxOverrideDebounce;
uint8_t STAuxOverridePressed;
uint8_t ACDAuxOverrideDebounce;
uint8_t ACDAuxOverridePressed;
uint8_t previousAuxEnable;
uint8_t previousAuxBaseState;
uint8_t previousAuxBaseActive;
uint8_t previousAuxRodState;
uint8_t previousAuxRodActive;

uint8_t LCD[8]; // 0-4 are main segments, 5 is the gear #, 6 is radix and colon. 7 is priority
uint8_t activeCodeIndex;
uint8_t AcknowledgeData[8];
uint8_t count_GeneralIcon;  //Used to for secondary controllers errors, display general warning icon.
uint16_t can_FuelRate;


//******************************************************************************
// FUNCTIONS
//******************************************************************************




//************************************************************************************************
//
// LEGACY CAN## MESSAGES
//
//************************************************************************************************
void update_CAN01sTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  msg->set_byte(0,1);
  msg->set_byte(1, nvm_ecuid.bobcat_module_id );
  msg->set_byte(2, nvm_ecuid.j1939_source_address );
  msg->set_byte(3, bservice_dv_read_byte(1));//sw_type;
  msg->set_byte(4, bservice_dv_read_byte(2));//sw_version_major;
  msg->set_byte(5, bservice_dv_read_byte(3));//sw_version_minor;
  msg->set_byte(6, 0xFF);
  msg->set_byte(7, 0xFF);
}

static void initialize_CAN01sTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  CAN01sTX.initialize();
  CAN01sTX.mbuff.id.set_J1939ID(PRIORITY_6, 0xFF, 0xFF, nvm_ecuid.j1939_source_address);

  CAN01sTX.set_send_rate(250);
  CAN01sTX.pre_tx_callback = update_CAN01sTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&CAN01sTX);
  //hw_can_tx_scheduler[HWC_CAN4].add_msg(&CAN01sTX);
}

void update_CAN02sTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  uint8_t temp;

  msg->set_byte(0, CAN02);
  msg->set_byte(1, TYPE_1);

  //Determine if base is active
  if(state_AuxBase != NORMAL)
  {
    temp = state_AuxBase;
  }
  else if (hs_AuxBase > 0 && ls_AuxBase == ACTIVE)
  {
    temp = ACTIVE;
  }
  else
  {
    temp = INACTIVE;
  }
  msg->set_byte(2, temp);


  //Determine if rod is active
  if(state_AuxRod != NORMAL)
  {
    temp = state_AuxRod;
  }
  else if (hs_AuxRod > 0 && ls_AuxRod == ACTIVE)
  {
    temp = ACTIVE;
  }
  else
  {
    temp = INACTIVE;
  }
  msg->set_byte(3, temp);
}

static void initialize_CAN02sTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  CAN02sTX.initialize();
  CAN02sTX.mbuff.id.set_J1939ID(PRIORITY_6, 0xFF, 0xFF, nvm_ecuid.j1939_source_address);

  CAN02sTX.set_send_rate(100);
  CAN02sTX.pre_tx_callback = update_CAN02sTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&CAN02sTX);
}



void update_CAN05sTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  uint8_t tempByte = 0;

  msg->set_byte(0, 0x05);
  msg->set_byte(1, TYPE_2);


  if(state_HydEnable == ACTIVE)
  {
    tempByte = 0x01;
  }
  else
  {
    tempByte = 0x00;
  }
  msg->set_byte(2, tempByte);
  msg->set_byte(3, tempByte);
  msg->set_byte(6, state_Console);
}

static void initialize_CAN05sTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       : Need to keep for legacy service tools
//******************************************************************************
{
  CAN05sTX.initialize();
  CAN05sTX.mbuff.id.set_J1939ID(PRIORITY_6, 0xFF, 0xFF, nvm_ecuid.j1939_source_address);

  CAN05sTX.set_send_rate(100);
  CAN05sTX.pre_tx_callback = update_CAN05sTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&CAN05sTX);
}



void update_CAN06sTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 27 Nov, 2006
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  msg->set_byte(0, CAN06);
  msg->set_byte(1, TYPE_1);
  msg->set_word(1, 0); //No ACD commands at this time - only sending to make RACD work
}

static void initialize_CAN06sTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 27 Nov, 2006
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  CAN06sTX.initialize();
  CAN06sTX.mbuff.id.set_J1939ID(PRIORITY_5, 0xFF, 0xFF, nvm_ecuid.j1939_source_address);

  CAN06sTX.set_send_rate(10);
  CAN06sTX.pre_tx_callback = update_CAN06sTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&CAN06sTX);
}

void CAN_ST_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 06 April, 2006
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  switch(msg->get_byte(0))
  {
    case CAN03:
      can_ST_EngineStart = msg->get_byte(2);

      if(msg->get_byte(3) == ACTIVE)// latch stop
      {
        can_ST_EStop = msg->get_byte(3);
      }
    break;


    case CAN20:
      if(CONSTANT_DATA->STAUX_FUNCTION != NON_FUNCTIONAL)
      {
        if((msg->get_byte(2) == HYDRAULIC_LOCK_MASK) ||
           (msg->get_byte(2) == 0))
        {
          if(msg->get_byte(2))
          {
            if(!STAuxOverrideDebounce)
            {
              STAuxOverridePressed = TRUE;
              STAuxOverrideDebounce = TRUE;
            }
          }
          else
          {
            STAuxOverrideDebounce = FALSE;
          }
        }

        if(STAuxOverridePressed)
        {
          STAuxOverridePressed = FALSE;

          if(cmd_AuxEnable_ST == INACTIVE)
          {
            cmd_AuxEnable_ST = ACTIVE;
          }
          else
          {
            cmd_AuxEnable_ST = INACTIVE;
          }
        }
      }

    break;

    default:
    break;
  }
}

static void initialize_CAN_ST_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 06 April, 2006
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  CAN_STsRX.initialize();
  CAN_STsRX.rx_id     .set_J1939ID(0, 0xFF, 0xFF, SA_SERVICE_TOOL);
  CAN_STsRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  CAN_STsRX.rx_callback = CAN_ST_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&CAN_STsRX);
}

void update_CAN20sTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  msg->set_byte(0, CAN20);
  msg->set_byte(1, TYPE_2);
  msg->set_byte(2, state_AuxEnable);
}


static void initialize_CAN20sTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  CAN20sTX.initialize();
  CAN20sTX.mbuff.id.set_J1939ID(PRIORITY_6, 0xFF, 0xFF, nvm_ecuid.j1939_source_address);
  CAN20sTX.mbuff.DLR = 5;
  CAN20sTX.set_send_rate(100);
  CAN20sTX.pre_tx_callback = update_CAN20sTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&CAN20sTX);
}

void update_CAN21sTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  msg->set_byte(0, CAN21);


  if((state_HOT == OORL) || (state_HOT == OORH))
  {
    msg->set_byte(3, UNDEFINED);
  }
  else
  {
    msg->set_byte(3, (uint8_t)(FahrenheitToCelsius[(uint16_t)(flt_HOT)]));
  }

}

static void initialize_CAN21sTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  CAN21sTX.initialize();
  CAN21sTX.mbuff.id.set_J1939ID(PRIORITY_6, 0xFF, 0xFF, nvm_ecuid.j1939_source_address);
  CAN21sTX.mbuff.DLR = 4;
  CAN21sTX.set_send_rate(100);
  CAN21sTX.pre_tx_callback = update_CAN21sTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&CAN21sTX);
}

static void initialize_CAN21extTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  CAN21extTX.initialize();
  CAN21extTX.mbuff.id.set_J1939ID(PRIORITY_6, 0xFF, 0xFF, nvm_ecuid.j1939_source_address);
  CAN21extTX.mbuff.DLR = 4;
  CAN21extTX.set_send_rate(100);
  CAN21extTX.pre_tx_callback = update_CAN21sTX;

  hw_can_tx_scheduler[HWC_CAN4].add_msg(&CAN21extTX);
}


void CAN_ACD_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 06 April, 2006
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  switch(msg->get_byte(0))
  {
    case CAN03:

      can_ACD_EngineStart = msg->get_byte(2);
      if(msg->get_byte(3) == ACTIVE)
      {
        can_ACD_EStop = msg->get_byte(3);
      }
      else
      {
        can_ACD_EStop = 0;
      }
    break;


    case CAN06:
      can_ACD_AuxCommand = msg->get_byte(2);
    break;


    case CAN20:
      if((msg->get_byte(2) == HYDRAULIC_LOCK_MASK) ||
         (msg->get_byte(2) == 0))
      {
        if(msg->get_byte(2))
        {
          if(!ACDAuxOverrideDebounce)
          {
            ACDAuxOverridePressed = TRUE;
            ACDAuxOverrideDebounce = TRUE;
          }
        }
        else
        {
          ACDAuxOverrideDebounce = FALSE;
        }
      }

      if(ACDAuxOverridePressed)
      {
        ACDAuxOverridePressed = FALSE;

        if(cmd_AuxEnable_ACD == INACTIVE)
        {
          cmd_AuxEnable_ACD = ACTIVE;
        }
        else
        {
          cmd_AuxEnable_ACD = INACTIVE;
        }
      }
    break;

    default:
    break;
  }
}

static void initialize_CAN_ACD_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 06 April, 2006
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  CAN_ACDsRX.initialize();
  CAN_ACDsRX.rx_id     .set_J1939ID(0, 0xFF, 0xFF, SA_ATTACHMENT);
  CAN_ACDsRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  CAN_ACDsRX.rx_callback = CAN_ACD_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&CAN_ACDsRX);
}

void update_EEC1_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates Engine RPM TX Message data.
//    Notes       :
//******************************************************************************
{
  uint16_t tempWord;


  if(flt_EngineSpeed <= CONSTANT_DATA->ENGINE_SPEED_OUT_OF_RANGE)
  {
    // 0.125 rpm/bit 0 offset
    tempWord = (uint16_t)(flt_EngineSpeed << 3);
  }
  else
  {
    tempWord = 0xFFFF;
  }

  msg->set_byte(3, (uint8_t)(tempWord));
  msg->set_byte(4, (uint8_t)(tempWord >> 8));
  msg->set_byte(5, nvm_ecuid.j1939_source_address);
}

static void initialize_EEC1_CAN0_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  EEC1_CAN0TX.initialize();
  EEC1_CAN0TX.mbuff.id.set_J1939ID(PRIORITY_3, EEC1_PF, EEC1_PS, nvm_ecuid.j1939_source_address);

  EEC1_CAN0TX.set_send_rate(4);
  EEC1_CAN0TX.pre_tx_callback = update_EEC1_TX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&EEC1_CAN0TX);
}

void update_VEP_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  uint32_t tempDWord;

  tempDWord = calc_VBattery / VOLTAGE_RESOLUTION;

  msg->set_byte(6, (uint8_t)(tempDWord));
  msg->set_byte(7, (uint8_t)(tempDWord >> 8));
}

static void initialize_VEP_CAN0_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  VEP_CAN0_TX.initialize();
  VEP_CAN0_TX.mbuff.id.set_J1939ID(PRIORITY_6, BATTERY_VOLTAGE_PF, BATTERY_VOLTAGE_PS, nvm_ecuid.j1939_source_address);

  VEP_CAN0_TX.set_send_rate(100);
  VEP_CAN0_TX.pre_tx_callback = update_VEP_TX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&VEP_CAN0_TX);
}

void update_ET1_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  if((state_ECT == OORL) || (state_ECT == OORH))
  {
     msg->set_byte(0, UNDEFINED);
  }
  else
  {
    msg->set_byte(0, (uint8_t)(FahrenheitToCelsius[flt_ECT]));
  }
}

static void initialize_ET1_CAN0_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  ET1_CAN0TX.initialize();
  ET1_CAN0TX.mbuff.id.set_J1939ID(PRIORITY_6, ET1_PF, ET1_PS, nvm_ecuid.j1939_source_address);
  ET1_CAN0TX.set_send_rate(100);
  ET1_CAN0TX.pre_tx_callback = update_ET1_TX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&ET1_CAN0TX);
}

void update_EFL_P1_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  uint16_t tempWord;

  if(((uint8_t)flt_EOP > MAXENGINEPSI) ||
     (state_EOP == OORL) ||
     (state_EOP == OORH) ||
     (CONSTANT_DATA->ECU_FUNCTION == NON_FUNCTIONAL))
  {
    msg->set_byte(3, UNDEFINED);
  }
  else
  {
    // 1 PSI = 6.895 KPa so multiply and round up
    // now for J1939 format 1 bit = 4 KPA shift by 2 + 16.8 format so shift by 10

    tempWord = (uint16_t)((((uint32_t)(flt_EOP) * (uint32_t)(PSITOKPA)) + 0x200) >> 10);

    if(tempWord > 250)
    {
      // then somthing is wrong should not be possible
      msg->set_byte(3, UNDEFINED);
    }
    else
    {
      msg->set_byte(3, (uint8_t)(tempWord));
    }
  }
}

static void initialize_EFL_P1_CAN0_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  EFL_P1_CAN0TX.initialize();
  EFL_P1_CAN0TX.mbuff.id.set_J1939ID(PRIORITY_6, EFL_P1_PF, EFL_P1_PS, nvm_ecuid.j1939_source_address);

  EFL_P1_CAN0TX.set_send_rate(100);
  EFL_P1_CAN0TX.pre_tx_callback = update_EFL_P1_TX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&EFL_P1_CAN0TX);
}


void update_EEC2_J1939_CAN0_TX (hw_can_msg_t *msg)
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

static void initialize_EEC2_CAN0_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  EEC2_CAN0TX.initialize();

  EEC2_CAN0TX.mbuff.id.set_J1939ID(PRIORITY_3, EEC2_PF, EEC2_PS, nvm_ecuid.j1939_source_address);
  EEC2_CAN0TX.pre_tx_callback = update_EEC2_J1939_CAN0_TX;
  EEC2_CAN0TX.set_send_rate(5);


  hw_can_tx_scheduler[HWC_CAN0].add_msg(&EEC2_CAN0TX);
}


void update_DD_CAN0_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  //uint16_t tempWord;

  //tempWord = (gau_FuelLevel << 8) / 261;  // Fuel level is 0-255, convert to 0-250 by dividing by 1.02

  msg->set_byte(1, (uint8_t)gau_FuelLevel);
}

static void initialize_DD_CAN0_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  DD_CAN0TX.initialize();
  DD_CAN0TX.mbuff.id.set_J1939ID(PRIORITY_6, DD_PF, DD_PS, nvm_ecuid.j1939_source_address);

  DD_CAN0TX.set_send_rate(100);
  DD_CAN0TX.pre_tx_callback = update_DD_CAN0_TX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&DD_CAN0TX);
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

static void initialize_AAI_CAN0_TX (void)
//******************************************************************************
//    returns     : NONE.
//
//		Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  AAI_CAN0_TX.initialize();
  AAI_CAN0_TX.mbuff.id.set_J1939ID(PRIORITY_7, AAI_PF, AAI_PS, nvm_ecuid.j1939_source_address);
  																					 
  AAI_CAN0_TX.set_send_rate(100);
  AAI_CAN0_TX.pre_tx_callback = update_AAI_TX;
  
  hw_can_tx_scheduler[HWC_CAN0].add_msg(&AAI_CAN0_TX);
}


//************************************************************************************************
//
// SECONDARY CONTROLLERS
//
//************************************************************************************************

static void initialize_CAN01_Throttle_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 27 Jul, 2011
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  CAN01_ThrottleRX.initialize();
  CAN01_ThrottleRX.rx_id     .set_J1939ID(0, 0xFF, 0xFF, SA_THROTTLE);
  CAN01_ThrottleRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  CAN01_ThrottleRX.rx_callback = NULL;
  CAN01_ThrottleRX.D0_data = 0x01;
  CAN01_ThrottleRX.D0_mask = 0xFF;

  hw_can_rx_handler[HWC_CAN0].add_msg(&CAN01_ThrottleRX);
}

static void initialize_CAN01_Secondary_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 27 Jul, 2011
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  CAN01_SecondaryRX.initialize();
  CAN01_SecondaryRX.rx_id     .set_J1939ID(0, 0xFF, 0xFF, SA_SECONDARY);
  CAN01_SecondaryRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  CAN01_SecondaryRX.rx_callback = NULL;
  CAN01_SecondaryRX.D0_data = 0x01;
  CAN01_SecondaryRX.D0_mask = 0xFF;

  hw_can_rx_handler[HWC_CAN0].add_msg(&CAN01_SecondaryRX);
}

void update_CAN03sTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  msg->set_byte(0, 0x03);
  msg->set_byte(1, TYPE_2);

  if(state_Engine == ENGINE_CRANKING)
  {
    msg->set_byte(2, 1);
  }
  else
  {
    msg->set_byte(2, 0);
  }

  if(state_Engine == ENGINE_RUNNING)
  {
    msg->set_byte(3, 0);
  }
  else if(state_Engine == SHUTDOWN)
  {
    msg->set_byte(3, 15);
  }
  else
  {
    msg->set_byte(3, 1);
  }


  msg->set_byte(4, hw_din_GetValue(RUN_ENTER_SW));
  msg->set_byte(5, UNDEFINED);
  msg->set_byte(6, hw_din_GetValue(REMOTE_KEY));

  if((state_System == SYS_POWER_DOWN) || (state_System == SYS_LIMITED))
  {
    msg->set_byte(7, 1);
  }
  else
  {
    msg->set_byte(7, 0);
  }
}

static void initialize_CAN03sTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Dec, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  CAN03sTX.initialize();
  CAN03sTX.mbuff.id.set_J1939ID(PRIORITY_6, 0xFF, 0xFF, nvm_ecuid.j1939_source_address);

  CAN03sTX.set_send_rate(30);
  CAN03sTX.pre_tx_callback = update_CAN03sTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&CAN03sTX);
}

void HoursUpdatesRX_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 15 Mar, 2006
//    Description :
//    Notes       :
//******************************************************************************
{
  uint32_t newHours;

  if(msg->get_byte(4) == 2)
  {
    newHours = msg->get_dword(0);
    newHours = newHours*36;

    // if newHours is greater than the current hour meter and hour meter is less than 1 hour
    // use the value from the auxiliary controller.
    if((newHours > actualHourMeter) && (actualHourMeter < HOUR_METER_TO_HOUR_FCT) && (CONSTANT_DATA->SECONDARY_HOURMETER_UPDATE_FUNCTION != NON_FUNCTIONAL))
    {
      actualHourMeter = newHours;
      actualHourMeterCopy = actualHourMeter;

      if(eeMode == EE_IDLE)
      {
        eeMode  = EE_HM_UPDATE;
        eeState = EE_HM_WRITE_INIT;
      }
    }
  }
}

static void initialize_HoursUpdatesRX_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 15 Mar, 2006
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  HoursUpdatesRX.initialize();
  HoursUpdatesRX.rx_id     .set_J1939ID(0, ENGINE_HOURS_PF, ENGINE_HOURS_PS, SA_SECONDARY);
  HoursUpdatesRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0x00);

  HoursUpdatesRX.rx_callback = HoursUpdatesRX_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&HoursUpdatesRX);
}

void update_HWJ1939EngineHoursTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates Engine RPM TX Message data.
//    Notes       :
//******************************************************************************
{
  uint32_t J1939HourMeter;

  J1939HourMeter = actualHourMeter/HOUR_METER_RESOLUTION;
  msg->set_byte(0, (uint8_t)(J1939HourMeter));
  msg->set_byte(1, (uint8_t)(J1939HourMeter >> 8));
  msg->set_byte(2, (uint8_t)(J1939HourMeter >> 16));
  msg->set_byte(3, (uint8_t)(J1939HourMeter >> 24));
  msg->set_byte(4, flag_HourOverflow);

}

static void initialize_HWJ1939EngineHoursIntTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  HWJ1939EngineHoursIntTX.initialize();
  HWJ1939EngineHoursIntTX.mbuff.id.set_J1939ID(PRIORITY_6, ENGINE_HOURS_PF, ENGINE_HOURS_PS, nvm_ecuid.j1939_source_address);
  HWJ1939EngineHoursIntTX.set_send_rate(250);
  HWJ1939EngineHoursIntTX.pre_tx_callback = update_HWJ1939EngineHoursTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&HWJ1939EngineHoursIntTX);
}


//************************************************************************************************
//
// DISPLAY PANEL
//
//************************************************************************************************


void PanelButtonRX_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 15 Mar, 2006
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  for(uint8_t i=0; i < 8; i++)
  {
    msg_PanelButtonState[i] = msg->get_byte(i);
  }

}

static void initialize_PanelButtonRX(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 15 Mar, 2006
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  PanelButtonStateIntRX.initialize();
  PanelButtonStateIntRX.rx_id     .set_J1939ID(0, PROPRIETARY_B, PANEL_BUTTON_STATE_PS, 0x04);
  PanelButtonStateIntRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0x84);

  PanelButtonStateIntRX.rx_callback = PanelButtonRX_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&PanelButtonStateIntRX);
}




void update_PanelTellTalesTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  uint8_t tempByte = 0;

  if(inDVCode == FALSE)
  {
    if(count_GeneralIcon > 0)
    {
      icon_General = ACTIVE;
    }

    tempByte = (DONT_CARE +
               ((icon_General & 0x03) << 2) +
               ((icon_Rabbit  & 0x03) << 4) +
               ((icon_Engine  & 0x03) << 6));
    msg->set_byte(0, tempByte);

    tempByte = (icon_ECT & 0x03) +
               (DONT_CARE << 2) +
               (DONT_CARE << 4) +
               (DONT_CARE << 6);
    msg->set_byte(1, tempByte);

    tempByte = (icon_Hydraulic & 0x03) +
               ((icon_Fuel & 0x03) << 2) +
               ((icon_Seatbelt & 0x03) << 4) +
               (DONT_CARE  << 6);
    msg->set_byte(2, tempByte);

    tempByte = (DONT_CARE +
               ((icon_Lockout & 0x03) << 2) +
               (DONT_CARE << 4) +
               (DONT_CARE << 6));


    msg->set_byte(3, tempByte);
    msg->set_byte(4, UNDEFINED);
    msg->set_byte(5, UNDEFINED);

    msg->set_byte(6, 0x05);

    if(state_System == SYS_LIMITED || state_System == SYS_PHONE_LIMITED)
    {
      msg->set_byte(0, 0);
      msg->set_byte(1, 0);
      msg->set_byte(2, 0);
      msg->set_byte(3, 0);
      msg->set_byte(4, 0);
      msg->set_byte(5, 0);
      msg->set_byte(7, 0);
    }
    else
    {
      msg->set_byte(7, level_DisplayBacklight);
    }
  }
  else
  {
    if(dvPanelOn == TRUE)
    {
      msg->set_byte(0, 0x55);
      msg->set_byte(1, 0x55);
      msg->set_byte(2, 0x55);
      msg->set_byte(3, 0x55);
      msg->set_byte(4, UNDEFINED);
      msg->set_byte(5, UNDEFINED);
      msg->set_byte(6, 0x05);
      msg->set_byte(7, 0x05);
    }
    else
    {
      msg->set_byte(0, 0x00);
      msg->set_byte(1, 0x00);
      msg->set_byte(2, 0x00);
      msg->set_byte(3, 0x00);
      msg->set_byte(4, UNDEFINED);
      msg->set_byte(5, UNDEFINED);
      msg->set_byte(6, 0x05);
      msg->set_byte(7, 0x00);
    }
  }
}

static void initialize_PanelTellTalesTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  msgTX_PanelTellTales.initialize();
  msgTX_PanelTellTales.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, PANEL_TELL_TALES_PS, nvm_ecuid.j1939_source_address);

  msgTX_PanelTellTales.set_send_rate(10);
  msgTX_PanelTellTales.pre_tx_callback = update_PanelTellTalesTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&msgTX_PanelTellTales);
}


void update_PanelButtonsTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  if(inDVCode == FALSE)
  {

    msg->set_byte(0, 0xFF);
    msg->set_byte(1, 0xFF);
    msg->set_byte(2, 0xFF);
    msg->set_byte(3, 0xCC | ((ind_Light1 & 0x03) + ((ind_AutoIdle & 0x03) << 4)));
    msg->set_byte(4, 0xF0 | ((ind_Aux1   & 0x03) + ((ind_Aux2     & 0x03) << 2)));
    msg->set_byte(5, 0xFF);
    msg->set_byte(6, 0xFF);
    msg->set_byte(7, 0xFF);
  }
  else
  {
    msg->set_byte(0, 0);
    msg->set_byte(1, 0);
    msg->set_byte(2, 0);
    msg->set_byte(3, 0);
    msg->set_byte(4, 0);
    msg->set_byte(5, 0);
    msg->set_byte(6, 0);
    msg->set_byte(7, 0);

    if((msg_PanelButtonState[0] & LIGHT_BUTTON_MASK) == LIGHT_BUTTON_PRESS)
    {
      msg->set_byte(3, 0x05);
    }

    if((msg_PanelButtonState[0] & AUTO_IDLE_BUTTON_MASK) == AUTO_IDLE_BUTTON_PRESS)
    {
      msg->set_byte(3, 0x50);
    }

    if((msg_PanelButtonState[0] & AUXILIARY_BUTTON_MASK) == AUXILIARY_BUTTON_PRESS)
    {
      msg->set_byte(4, 0x05);
    }

    if((msg_PanelButtonState[0] & INFO_BUTTON_MASK) == INFO_BUTTON_PRESS)
    {
      msg->set_byte(4, 0x50);
    }
  }
}

static void initialize_PanelButtonsTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  msgTX_PanelButtons.initialize();
  msgTX_PanelButtons.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, PANEL_BUTTON_STATE_PS, nvm_ecuid.j1939_source_address);

  msgTX_PanelButtons.set_send_rate(10);
  msgTX_PanelButtons.pre_tx_callback = update_PanelButtonsTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&msgTX_PanelButtons);
}



void update_PanelGaugeTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  uint8_t tempByte = 0;

  msg->DLR = 6;
  if(state_System == SYS_LIMITED || state_System == SYS_PHONE_LIMITED)
  {
    msg->set_byte(0,0);
    msg->set_byte(1,0);
    msg->set_byte(2,0);
    msg->set_byte(3,0);
    msg->set_byte(4,0);
    msg->set_byte(5,0);
  }
  else
  {
    msg->set_byte(0,(uint8_t)(gau_ECT));
    msg->set_byte(1,(uint8_t)(gau_FuelLevel));
    msg->set_byte(2,(uint8_t)(UNDEFINED));

    tempByte = ((calcFlt_VBattery *4) >> 8);
    msg->set_byte(3, MXGTW_VBATTERYGAUGE[tempByte]);
    msg->set_byte(4,(uint8_t)(gau_EOP));
    msg->set_byte(5,(uint8_t)(gau_HOT));
  }

}

static void initialize_PanelGaugeTX(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  msgTX_PanelGauge.initialize();
  msgTX_PanelGauge.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, PANEL_GAUGE_POSITION_PS, nvm_ecuid.j1939_source_address);

  msgTX_PanelGauge.set_send_rate(10);
  msgTX_PanelGauge.pre_tx_callback = update_PanelGaugeTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&msgTX_PanelGauge);
}


void update_PanelLCDTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  static bool flag_Reset = FALSE;
  static bool flag_Aux = FALSE;

  LCD[6] = 0x00; //Default decimal off
  LCD[7] = 0x00; //Default Priority 0

  if(state_InfoPrimary != DISPLAY_PRIMARY_INACTIVE)
  {

    switch(state_InfoPrimary)
    {
      case DISPLAY_ENGINE_RPM:
        UpdateLCDEngineRPM();
      break;

      case DISPLAY_BATTERY_VOLTAGE:
        UpdateLCDBatteryVoltage();
      break;

      case DISPLAY_EOP:
        UpdateLCDEOP();
      break;

      case DISPLAY_ECT:
        UpdateLCDECT();
      break;

      case DISPLAY_HOT:
        UpdateLCDHOT();
      break;

      case DISPLAY_SERVICE_CLOCK:
        UpdateLCDServiceClock();
      break;

      case DISPLAY_ERROR_CODES:
        if(flag_Reset == FALSE)
        {
          flag_Reset = TRUE;
          start_timeLCD = 0;
        }
        UpdateLCDErrorCodes();
      break;

      case DISPLAY_SERVICE_CLOCK_RESET:
        LCD[0] = 'R';
        LCD[1] = 'E';
        LCD[2] = 'S';
        LCD[3] = 'E';
        LCD[4] = 'T';
        LCD[5] = ' ';

      break;

      case DISPLAY_JOB_CLOCK_1:
        UpdateLCDJobClock(0);
      break;

      case DISPLAY_JOB_CLOCK_2:
        UpdateLCDJobClock(1);
      break;

      case DISPLAY_GROUND_SPEED:
      break;

      case DISPLAY_TIME_OF_DAY:
      break;
           
      case DISPLAY_SECOND_AUX:
        LCD[0] = '2';
        LCD[1] = ' ';
        LCD[2] = 'A';
        LCD[3] = 'U';
        LCD[4] = 'X';
      break;

      case DISPLAY_EMEA_CONTROLS:
        if(disp_LeftControl == MODE_LEFT_OFFSET)
        {
            LCD[0] = 'O';
            LCD[1] = 'F';
        }
        else if (disp_LeftControl == MODE_LEFT_AUX2)
        {
            LCD[0] = 'A';
            LCD[1] = '2';
        } 
        else if(disp_LeftControl == MODE_LEFT_AUX4)
        {
            LCD[0] = 'A';
            LCD[1] = '4';
        }
        else 
        {
            LCD[0] = ' ';
            LCD[1] = ' ';
        }
        
       
        if(disp_RightControl == MODE_RIGHT_OFFSET)
        {
            LCD[2] = 'O';
            LCD[3] = 'F';
        }
        else if (disp_RightControl == MODE_RIGHT_AUX1)
        {
            LCD[2] = 'A';
            LCD[3] = '1';
        } 
        else if(disp_RightControl == MODE_RIGHT_AUX4)
        {
            LCD[2] = 'A';
            LCD[3] = '4';
        }
        else 
        {
            LCD[2] = ' ';
            LCD[3] = ' ';
        }
        LCD[4] = ' ';
        LCD[6] = 0x04; // Turn colon on
        
      break;
      
      default:
        flag_Reset = FALSE;
        UpdateLCDHourMeter();
      break;
    }
  }
  else
  {
    switch(state_InfoSecondary)
    {
      case DISPLAY_GLOW_PLUGS:
        UpdateLCDGlowPlugs();
      break;

      case DISPLAY_SERVICE_CLOCK_ALARM:
        UpdateLCDServiceClock();
      break;

      case DISPLAY_SHUTDOWN:
        LCD[0] = 'S';
        LCD[1] = 'H';
        LCD[2] = 'T';
        LCD[3] = 'D';
        LCD[4] = 'N';
        LCD[5] = ' ';

      break;

      case DISPLAY_DELUXE_ERROR:

        LCD[0] = 'M';
        LCD[1] = '4';
        LCD[2] = '3';
        LCD[3] = '0';
        LCD[4] = '4';
        LCD[5] = ' ';

      break;

      case DISPLAY_VERSION:
        UpdateLCDVersion();
      break;

      case DISPLAY_DV_MODE:
        if(dvPanelOn == TRUE)
        {
          LCD[0] = '#';
          LCD[1] = '#';
          LCD[2] = '#';
          LCD[3] = '#';
          LCD[4] = '#';

          LCD[5] = '#';
          LCD[6] = 0x05;
        }
        else
        {
          LCD[0] = ' ';
          LCD[1] = ' ';
          LCD[2] = ' ';
          LCD[3] = ' ';
          LCD[4] = ' ';

          LCD[5] = ' ';
        }
      break;

      case DISPLAY_CODE:
        LCD[0] = ' ';
        LCD[1] = 'C';
        LCD[2] = 'O';
        LCD[3] = 'D';
        LCD[4] = 'E';
      break;

      case DISPLAY_ERROR:
        LCD[0] = 'E';
        LCD[1] = 'R';
        LCD[2] = 'R';
        LCD[3] = 'O';
        LCD[4] = 'R';
      break;

      case DISPLAY_ASTERISK:
        LCD[0] = ' ';
        LCD[1] = ' ';
        LCD[2] = ' ';
        LCD[3] = ' ';
        LCD[4] = ' ';

        switch(pwd_Position)
        {
          case 1:
            LCD[4] = '*';
          break;

          case 2:
            LCD[4] = '*';
            LCD[3] = '*';
          break;

          case 3:
            LCD[4] = '*';
            LCD[3] = '*';
            LCD[2] = '*';
          break;

          case 4:
            LCD[4] = '*';
            LCD[3] = '*';
            LCD[2] = '*';
            LCD[1] = '*';
          break;

          case 5:
            LCD[4] = '*';
            LCD[3] = '*';
            LCD[2] = '*';
            LCD[1] = '*';
            LCD[0] = '*';
          break;

          default:
          break;
        }
      break;

      case DISPLAY_OWNER1:
        LCD[0] = 'E';
        LCD[1] = 'N';
        LCD[2] = 'T';
        LCD[3] = 'E';
        LCD[4] = 'R';
      break;

      case DISPLAY_OWNER2:
        LCD[0] = 'A';
        LCD[1] = 'G';
        LCD[2] = 'A';
        LCD[3] = 'I';
        LCD[4] = 'N';
      break;

      case DISPLAY_HOLD:
        LCD[0] = 'H';
        LCD[1] = 'O';
        LCD[2] = 'L';
        LCD[3] = 'D';
        LCD[4] = ' ';
      break;

      case DISPLAY_AUX:
        LCD[0] = ' ';
        LCD[1] = 'A';
        LCD[2] = 'U';
        LCD[3] = 'X';
        LCD[4] = ' ';
      break;

      case DISPLAY_CAN_THROTTLE_DIAG:
        LCD[0] = 'C';
        LCD[1] = 'A';
        LCD[2] = 'L';
        LCD[3] = ' ';
        LCD[4] = state_CANThrottleCalDiag + 0x30;
      break;

      case DISPLAY_COLD:
        LCD[0] = ' ';
        LCD[1] = 'C';
        LCD[2] = 'O';
        LCD[3] = 'L';
        LCD[4] = 'D';
      break;

      case DISPLAY_FLASH_COLD:
        UpdateLCD_FlashCold();
      break;

      case DISPLAY_OWNER:
        LCD[0] = 'O';
        LCD[1] = 'W';
        LCD[2] = 'N';
        LCD[3] = 'E';
        LCD[4] = 'R';
      break;

      case DISPLAY_USER1:
        LCD[0] = 'U';
        LCD[1] = 'S';
        LCD[2] = 'E';
        LCD[3] = 'R';
        LCD[4] = '1';
      break;

      case DISPLAY_USER2:
        LCD[0] = 'U';
        LCD[1] = 'S';
        LCD[2] = 'E';
        LCD[3] = 'R';
        LCD[4] = '2';
      break;
      
      case DISPLAY_OFFSET:
        LCD[0] = 'O';
        LCD[1] = 'F';
        LCD[2] = 'F';
        LCD[3] = 'S';
        LCD[4] = 'T';
      break;
      

      
      default:
        UpdateLCDHourMeter();
      break;
    }
  }

  if(state_System == SYS_INIT)
  {
    UpdateLCDHourMeter();
  }

  if((state_System == SYS_LIMITED) || (state_System == SYS_POWER_DOWN))
  {
    LCD[0] = ' ';
    LCD[1] = ' ';
    LCD[2] = ' ';
    LCD[3] = ' ';
    LCD[4] = ' ';
    LCD[5] = ' ';
  }

  msg->set_byte(0, (LCD[7]));
  msg->set_byte(1, (LCD[0]));
  msg->set_byte(2, (LCD[1]));
  msg->set_byte(3, (LCD[2]));
  msg->set_byte(4, (LCD[3]));
  msg->set_byte(5, (LCD[4]));

  uint8_t temp = ' '; // blank

  if(eeMirror.deluxe_G5 && CONSTANT_DATA->DELUXE_GEN5_FUNCTION != NON_FUNCTIONAL
     && CONSTANT_DATA->DELUXE_GEN5_5_FUNCTION == NON_FUNCTIONAL)//Gen 5 Deluxe panel
  {
    if(CONSTANT_DATA->AUX_ADJ_FLOW_FUNCTION != NON_FUNCTIONAL)//Aux config functional
    {
      temp = aux_Flow + 0x30; //Indicate aux config
    }
    else //deluxe with no aux config (small phoenix)
    {
      if(state_AuxEnable && !flag_Aux) //Aux active first time
      {
        temp = 0x30; //Maintain off state for one cylce - hack to fix glitch on deluxe panel icon
        flag_Aux = TRUE;
      }
      else if(state_AuxEnable && flag_Aux)//Aux active for at least one step
      {
        temp = 0;//0 tells deluxe to turn on aux icon without config bars
      }
      else //Aux not active
      {
        temp = aux_Flow + 0x30; //Indicate aux release state
        flag_Aux = FALSE;
      }
    }
    if(state_Detent == ERR_DETENT)//Trigger presses without detent enabled
    {
      temp |= 0x80; //Set flag to turn on HOLD AUX BUTTON message on deluxe
    }
  }
  else //Standard Panel or Gen5.5 Deluxe
  {
    if(CONSTANT_DATA->AUX_ADJ_FLOW_FUNCTION != NON_FUNCTIONAL)//Standard Panel - Aux config functional
    {
      if(CONSTANT_DATA->AUX_DISPLAY_MODE != NON_FUNCTIONAL)//Sirius2 aux config
      {
        switch(aux_Flow)
        {
          case AUX_FLOW_LOW:
            temp = '1';
            break;
          case AUX_FLOW_MEDIUM:
            temp = '2';
            break;
          case AUX_FLOW_STANDARD:
            temp = '3';
            break;
          case AUX_FLOW_HIGH:
            temp = 'H';
            break;
          default:
          break;
        }
      }
      else if(state_AuxEnable && CONSTANT_DATA->AUX_FUNCTION == AUX_EMEA_CONTROLS && mode_RightControl == MODE_RIGHT_AUX1)//EMEA Controls - only display flow if in AUX1 mode
      {
        temp = aux_Flow + 0x30; //Indicate aux config
      }
      else if(state_AuxEnable && CONSTANT_DATA->EMEA_CONTROLS_DISPLAY_MODE == NON_FUNCTIONAL)//Normal displaying of aux flow
      {
        temp = aux_Flow + 0x30; //Indicate aux config
      }
    }
  }

  msg->set_byte(6, temp);

  msg->set_byte(7, LCD[6]);
}

static void initialize_PanelLCDTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  msgTX_PanelLCD.initialize();
  msgTX_PanelLCD.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, PANEL_LCD_DATA_DISPLAY_PS, nvm_ecuid.j1939_source_address);

  msgTX_PanelLCD.set_send_rate(10);
  msgTX_PanelLCD.pre_tx_callback = update_PanelLCDTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&msgTX_PanelLCD);
}


void update_PanelLCDIconsTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Updates TX Message data.
//    Notes       :
//******************************************************************************
{
  uint8_t tempByte = 0;

  if(inDVCode == FALSE)
  {
    tempByte = (icon_JobClock2 << 4) +
               (icon_JobClock1 << 2) +
               (icon_Hourmeter);
    msg->set_byte(0, tempByte);

    msg->set_byte(1, 0x00);

    tempByte = (icon_Battery << 6) +
               (icon_GlowPlug << 4) +
               (icon_RPM << 2) ;

    msg->set_byte(2, tempByte);


    tempByte = (icon_Aux << 2) +
               (icon_Service & 0x03);

    msg->set_byte(3, tempByte);


    msg->set_byte(4, UNDEFINED);
    msg->set_byte(5, UNDEFINED);
    msg->set_byte(6, UNDEFINED);
    msg->set_byte(7, UNDEFINED);

    if((state_System == SYS_LIMITED) || (state_System == SYS_POWER_DOWN) || state_System == SYS_PHONE_LIMITED)
    {
      msg->set_byte(0, 0);
      msg->set_byte(1, 0);
      msg->set_byte(2, 0);
      msg->set_byte(3, 0);
      msg->set_byte(4, 0);
      msg->set_byte(5, 0);
      msg->set_byte(6, 0);
      msg->set_byte(7, 0);
    }
  }
  else
  {
    if(dvPanelOn == TRUE)
    {
      msg->set_byte(0, 0x55);
      msg->set_byte(1, 0x55);
      msg->set_byte(2, 0x55);
      msg->set_byte(3, 0x05);
      msg->set_byte(4, UNDEFINED);
      msg->set_byte(5, UNDEFINED);
      msg->set_byte(6, UNDEFINED);
      msg->set_byte(7, UNDEFINED);
    }
    else
    {
      msg->set_byte(0, 0x00);
      msg->set_byte(1, 0x00);
      msg->set_byte(2, 0x00);
      msg->set_byte(3, 0x00);
      msg->set_byte(4, UNDEFINED);
      msg->set_byte(5, UNDEFINED);
      msg->set_byte(6, UNDEFINED);
      msg->set_byte(7, UNDEFINED);
    }
  }
}

static void initialize_PanelLCDIconsTX (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 18 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  msgTX_PanelLCDIcons.initialize();
  msgTX_PanelLCDIcons.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, PANEL_LCD_DATA_DISPLAY2_PS, nvm_ecuid.j1939_source_address);

  msgTX_PanelLCDIcons.set_send_rate(10);
  msgTX_PanelLCDIcons.pre_tx_callback = update_PanelLCDIconsTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&msgTX_PanelLCDIcons);
}


void update_TFAC_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates TFAC message to command throttle actuator.
//    Notes       :
//******************************************************************************
{
  if(CONSTANT_DATA->THROTTLE_TYPE != CAN_ACTUATOR)
  {
    if(cmd_Throttle == WORD_UNAVAIL)
    {
      msg->set_word(0, WORD_UNAVAIL);
    }
    else
    {
      msg->set_word(0, cmd_Throttle * 40);
    }
  }
  else
  {
    if((cmd_Throttle == 0) && (eeMirror.ee_ThrottleCalState != IN_CAL_MODE))
    {
      msg->set_word(0, WORD_UNAVAIL);
    }
    else
    {
      msg->set_word(0, cmd_Throttle * 40);
    }
  }
}

static void initialize_TFAC_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  TFAC_TX.initialize();
  TFAC_TX.mbuff.id.set_J1939ID(PRIORITY_4, TFAC_PF, TFAC_PS, nvm_ecuid.j1939_source_address);

  TFAC_TX.set_send_rate(5);
  TFAC_TX.pre_tx_callback = update_TFAC_TX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&TFAC_TX);
}

void update_PrimaryControls_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates primary controller control settings.
//    Notes       :
//******************************************************************************
{
    uint16_t temp_position;
    uint8_t  temp_state;
    
    msg->set_byte(0, state_KeylessEntryLock);
    
    if(mode_LeftControl == MODE_LEFT_AUX4)
    {
        temp_position = position_LeftPot;
        temp_state = state_LeftPot;
    }
    else if(mode_RightControl == MODE_RIGHT_AUX4)
    {
        temp_position = position_RightPot;
        temp_state = state_RightPot;
    }
    else
    {
        temp_position = 500;
        temp_state = NORMAL;
    }
    msg->set_byte(1, temp_state);
    msg->set_word(1, temp_position); //bytes 2 & 3
    
    msg->set_byte(4, mode_LeftControl);
    msg->set_byte(5, mode_RightControl);

}

static void initialize_PrimaryControls_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  msgTX_PrimaryControls.initialize();
  msgTX_PrimaryControls.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, PRIMARY_CONTROLS_PS, nvm_ecuid.j1939_source_address);

  msgTX_PrimaryControls.set_send_rate(10);
  msgTX_PrimaryControls.pre_tx_callback = update_PrimaryControls_TX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&msgTX_PrimaryControls);
}

void SecondaryControls_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 19 Oct, 2016
//    Description : Gets the operator settings.
//    Notes       :
//******************************************************************************
{
   uint8_t temp;
   temp = msg->get_byte(7);
  
   //7.4 Offset Select Switch
   //7.6 Right Handle Switch   
   can_OffsetSelectSw = ((temp & 0x30) == 0x10);
   can_RightHandleSelectSw = ((temp & 0xC0) == 0x40);
}

static void initialize_SecondaryControls_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 19 Oct, 2016
//    Description : initialize CAN to receive operator settings messages.
//    Notes       :
//******************************************************************************
{
  msgRX_SecondaryControls.initialize();
  msgRX_SecondaryControls.rx_id     .set_J1939ID(0, PROPRIETARY_B, AUX_HYD_CONTROL_PS, SA_SECONDARY);
  msgRX_SecondaryControls.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);  
  msgRX_SecondaryControls.rx_callback = SecondaryControls_rx_callback;   
  hw_can_rx_handler[HWC_CAN0].add_msg(&msgRX_SecondaryControls);
}


void update_AuxControlMode_TX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates primary controller control settings.
//    Notes       :
//******************************************************************************
{
    uint8_t temp;
    
    //0.0 4 bits - Control Mode Options
    if(CONSTANT_DATA->EMEA_CONTROLS_OPTION_A != NON_FUNCTIONAL)
    {
        temp = 0;
    }
    else if(CONSTANT_DATA->EMEA_CONTROLS_OPTION_B != NON_FUNCTIONAL)
    {
        temp = 1;
    }
    else if(CONSTANT_DATA->EMEA_CONTROLS_OPTION_C != NON_FUNCTIONAL)
    {
        temp = 2;
    }
    else
    {
        temp = 0x0F;
    }
    msg->set_byte(0, temp);         
        
    //1.0 4 bits - Left Control Mode
    temp = mode_LeftControl;
    
    //1.4 4 bits - Right Control Mode
    temp |= (mode_RightControl << 4);
    
    msg->set_byte(1, temp);
    
    //2.0 2 bits - Control Mode Flag 1 - Aux Reminder Flag
    temp = flag_AuxEnableFlash;
    
    //2.2 2 bits - Control Mode Flag 2 - Previous Reminder Flag
    temp |= (flag_AuxModeReminder << 2);
    
    msg->set_byte(2, temp);
}

static void initialize_AuxControlMode_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  msgTX_AuxControlMode.initialize();
  msgTX_AuxControlMode.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, AUX_CONTROL_MODE_PS, nvm_ecuid.j1939_source_address);

  msgTX_AuxControlMode.set_send_rate(10);
  msgTX_AuxControlMode.pre_tx_callback = update_AuxControlMode_TX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&msgTX_AuxControlMode);
}

void HydControlSettings_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 19 Oct, 2016
//    Description : Gets the operator settings.
//    Notes       :
//******************************************************************************
{
    flow_Aux1Percent   = msg->get_byte(0);
    flow_Aux2Percent   = msg->get_byte(1);
    flow_Aux4Percent   = msg->get_byte(2);
    flow_OffsetPercent = msg->get_byte(3);
}

static void initialize_HydControlSettings_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//	  Created By  : Al Liebel
//    Date Created: 19 Oct, 2016
//    Description : initialize CAN to receive operator settings messages.
//    Notes       :
//******************************************************************************
{
  msgRX_HydControlSettings.initialize();
  msgRX_HydControlSettings.rx_id     .set_J1939ID(0, PROPRIETARY_B, HYD_CONTROL_SETTINGS_PS, 0x00);
  msgRX_HydControlSettings.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0x00);  
  msgRX_HydControlSettings.rx_callback = HydControlSettings_rx_callback;   
  hw_can_rx_handler[HWC_CAN0].add_msg(&msgRX_HydControlSettings);
}


void Send_Request_Message(uint16_t PGN, uint8_t DA, uint8_t direction)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 13 May 2011
//    Description : Send out request message based on PGN and Destination address.
//    Notes       :
//******************************************************************************
{
  hw_can_msg_t msg_data;

  msg_data.id.set_J1939ID(PRIORITY_6, 0xEA, DA ,nvm_ecuid.j1939_source_address );
  msg_data.DLR = 3;
  msg_data.set_byte(0, (uint8_t)PGN);
  msg_data.set_byte(1, (uint8_t)(PGN >> 8));
  msg_data.set_byte(2, 0);

  if(direction == HWC_CAN4)
  {
    hw_can_txq[HWC_CAN4].send_msg(&msg_data);
  }
  else
  {
    hw_can_txq[HWC_CAN0].send_msg(&msg_data);
  }

}


void LFE_CAN0_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Feb, 2011
//    Description : Get fuel rate.
//    Notes       :
//******************************************************************************
{
  fdbk_CANThrottle = (uint16_t)(msg->get_byte(6)) << 2; //Change scale from 0-250, to 0-1000
}

static void initialize_LFE_CAN0_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 22 Feb, 2011
//    Description : Initializes receiver CAN message for DPF indicator.
//    Notes       :
//******************************************************************************
{
  LFE_CAN0_RX.initialize();
  LFE_CAN0_RX.rx_id     .set_J1939ID(0, LFE_PF, LFE_PS, SA_CAN_ACTUATOR);
  LFE_CAN0_RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  LFE_CAN0_RX.rx_callback = LFE_CAN0_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&LFE_CAN0_RX);
}




void PanelIORX_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 15 Mar, 2006
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  uint8_t temp = msg->get_byte(4);
  
  if(temp != UNDEFINED)// if not don't care
  {
    state_Buzzer = temp;
  }


}

static void initialize_PanelIORX(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 15 Mar, 2006
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  HWJ1939PanelExternalIORX.initialize();
  HWJ1939PanelExternalIORX.rx_id     .set_J1939ID(0, PROPRIETARY_B, PANEL_EXTERNAL_IO_PS, 0);
  HWJ1939PanelExternalIORX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0);

  HWJ1939PanelExternalIORX.rx_callback = PanelIORX_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&HWJ1939PanelExternalIORX);
}


void update_HWJ1939BICSControl_tx (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Updates status of workgroup.
//    Notes       :
//******************************************************************************
{
  uint8_t tempByte;

  //0.0 Seatbar/Console Status
  if((state_Console == OORH) || (state_Console == OORL))
  {
    tempByte = 14;
  }
  else
  {
    tempByte = state_Console;
  }
  //0.4 Door Status - Undefined
  tempByte |= 0xF0;

  msg->set_byte(0,tempByte);

  //1.0 PTOL Status - Undefined
  //1.4 Engine Shutdown - Undefined
  msg->set_byte(1,UNDEFINED);

  //2.0 Workgroup State
  //3.0 Drive State
  if((state_HydEnable != ACTIVE) && (state_HydEnable != INACTIVE))
  {
    tempByte = ERROR;
  }
  else
  {
    tempByte = state_HydEnable;
  }
  msg->set_byte(2, tempByte);
  
  if(adin_TravelPressureSwitch > 512)
  {
    tempByte |= 0x40; //Travel commanded
  }
  msg->set_byte(3, tempByte);

  //4.0 Traction Lock Override - Undefined
  //4.4 Workgroup Override - Undefined
  msg->set_byte(4, UNDEFINED);

}

static void initialize_HWJ1939BICSControl_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 31 Jan, 2006
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
    HWJ1939BICSControlTX.initialize();
    HWJ1939BICSControlTX.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, BICS_CONTROL_PS, nvm_ecuid.j1939_source_address);

    HWJ1939BICSControlTX.set_send_rate(10);
    HWJ1939BICSControlTX.pre_tx_callback = update_HWJ1939BICSControl_tx;

    hw_can_tx_scheduler[HWC_CAN0].add_msg(&HWJ1939BICSControlTX);
}




void BJM2Right_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 21 May 2012
//    Description : Receiver message for rev fan.
//    Notes       :
//******************************************************************************
{
  for(uint8_t i=0; i < 8; i++)
  {
    msg_BJM2Right[i] = msg->get_byte(i);
  }
}

static void initialize_BJM2_Right_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 21 May 2012
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  BJM2RightRX.initialize();
  BJM2RightRX.rx_id     .set_J1939ID(0, PROPRIETARY_B , BJM2_PS, SA_RIGHT_JOYSTICK);
  BJM2RightRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  BJM2RightRX.rx_callback = BJM2Right_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&BJM2RightRX);
}

void BJM2Left_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 21 May 2012
//    Description : Receiver message for rev fan.
//    Notes       :
//******************************************************************************
{
  for(uint8_t i=0; i < 8; i++)
  {
    msg_BJM2Left[i] = msg->get_byte(i);
  }
}

static void initialize_BJM2_Left_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 21 May 2012
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  BJM2LeftRX.initialize();
  BJM2LeftRX.rx_id     .set_J1939ID(0, PROPRIETARY_B , BJM2_PS, SA_LEFT_JOYSTICK);
  BJM2LeftRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  BJM2LeftRX.rx_callback = BJM2Left_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&BJM2LeftRX);
}


void DigDepthStatus_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 21 May 2012
//    Description : Receiver message for rev fan.
//    Notes       :
//******************************************************************************
{
  state_DepthBeep = msg->get_byte(1);
  delay_DepthBeep = msg->get_word(1);
}

static void initialize_DigDepthStatus_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 21 May 2012
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  DigDepthStatusRX.initialize();
  DigDepthStatusRX.rx_id     .set_J1939ID(0, PROPRIETARY_B , DIG_DEPTH_STATUS_PS, SA_SECONDARY);
  DigDepthStatusRX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);
  DigDepthStatusRX.rx_callback = DigDepthStatus_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&DigDepthStatusRX);
}
//************************************************************************************************
//
// SOFT Message Support
//
//************************************************************************************************

static void getAsciiSOFTID(uint8_t *ID, uint8_t size)
////******************************************************************************
////    returns     : NONE.
////
////    Created By  : Boston Zachmann
////    Date Created: 22 Dec, 2005
////    Description : Returns the string representation of module ID
////    Notes       :
////******************************************************************************
{
  uint8_t mIDValue = bservice_dv_read_byte(5);
  uint8_t mIDhundreds = mIDValue / 100;
  uint8_t mIDtens = (uint8_t)((mIDValue % 100) / 10);
  uint8_t mIDones = (uint8_t)(mIDValue % 10);
  
  uint8_t index = 0;
  
  if(index <= size)
  {
    ID[index] = mIDhundreds + '0'; //ascii representation of hundreds place
    index++; 
  }
  if(index <= size)
  {
    ID[index] = mIDtens + '0'; //ascii representation of tens place
    index++; 
  }
  if(index <= size)
  {
    ID[index] = mIDones + '0'; //ascii representation of ones place
    index++; 
  }
  
}

static void getAsciiSOFTApp(uint8_t *ID, uint8_t size)
////******************************************************************************
////    returns     : NONE.
////
////    Created By  : Boston Zachmann
////    Date Created: 22 Dec, 2005
////    Description : Returns the string representation of App version
////    Notes       : 
////******************************************************************************
{
  uint8_t asciiType = bservice_dv_read_byte(1);
  uint8_t majorValue = bservice_dv_read_byte(2);
  uint8_t minorValue = bservice_dv_read_byte(3);
  
  uint8_t majortens = majorValue / 10;
  uint8_t majorones = (uint8_t)(majorValue % 10);
  uint8_t minortens = minorValue / 10;
  uint8_t minorones = (uint8_t)(minorValue % 10);
  
  uint8_t index = 0;
  
  if(index <= size)
  {
    ID[index] = asciiType;
    index++; 
  }
  if(index <= size)
  {
    ID[index] = majortens + '0'; //ascii representation of major tens
    index++; 
  }
  if(index <= size)
  {
    ID[index] = majorones + '0'; //ascii representation of major ones
    index++; 
  }
  if(index <= size)
  {
    ID[index] = '.';
    index++; 
  }
  if(index <= size)
  {
    ID[index] = minortens + '0'; //ascii representation of minor tens
    index++; 
  }
  if(index <= size)
  {
    ID[index] = minorones + '0'; //ascii representation of minor ones
    index++; 
  }
  
  
}

static void getAsciiSOFTCD(uint8_t *CD, uint8_t size)
////******************************************************************************
////    returns     : NONE.
////
////    Created By  : Boston Zachmann
////    Date Created: 22 Dec, 2005
////    Description : Returns the string representation of Constant
////                    Data version
////    Notes       :
////******************************************************************************
{
  uint8_t majorValue = CONSTANT_DATA->MAJOR_VERSION_NUMBER;
  uint8_t minorValue = CONSTANT_DATA->MINOR_VERSION_NUMBER;
  
  uint8_t majortens = majorValue / 10;
  uint8_t majorones = (uint8_t)(majorValue % 10);
  uint8_t minortens = minorValue / 10;
  uint8_t minorones = (uint8_t)(minorValue % 10);
  
  uint8_t index = 0;
  
  if(index <= size)
  {
    CD[index] = majortens + '0'; //ascii representation of major tens
    index++; 
  }
  if(index <= size)
  {
    CD[index] = majorones + '0'; //ascii representation of major ones
    index++; 
  }
  if(index <= size)
  {
    CD[index] = '.';
    index++; 
  }
  if(index <= size)
  {
    CD[index] = minortens + '0'; //ascii representation of minor tens
    index++; 
  }
  if(index <= size)
  {
    CD[index] = minorones + '0'; //ascii representation of minor ones
    index++; 
  }
}

static void SendSOFTMsg(uint8_t *customField = 0, uint8_t customSize = 0)
////******************************************************************************
////    returns     : NONE.
////
////    Created By  : Boston Zachmann
////    Date Created: 22 Dec, 2005
////    Description : constructs and initiates the sending of the
////                  SOFT message.
////    Notes       : Can append a custom field to the end of message
////******************************************************************************
{
  bool appendCustom =  false;
  uint8_t softID[3];
  uint8_t softApp[6];
  uint8_t softCD[5];
  uint8_t msgIndex = 0;
  uint8_t i = 0;
  
  getAsciiSOFTID(softID, sizeof(softID));
  getAsciiSOFTApp(softApp, sizeof(softApp));
  getAsciiSOFTCD(softCD, sizeof(softCD));
  
  //field specifier + SOFTID + * + SOFTApp + * + SOFTCD + * + (optionally)SOFTCustom + *
  uint8_t msgSize = 1 + sizeof(softID) + 1 + sizeof(softApp) + 1 + sizeof(softCD) + 1;
  
  if((customSize != 0) && (customField != 0))
  {
    if(msgSize + customSize + 1 > sizeof(SOFTmsgData))
    {
      appendCustom = false;
      SOFTmsgData[0] = 3;
    } 
    else 
    {
      msgSize = msgSize + customSize + 1;
      appendCustom = true;
      SOFTmsgData[0] = 4;
    }
  }
  else
  {
    appendCustom = false;
    SOFTmsgData[0] = 3;
  }
  
  msgIndex++;
  
  //append softID
  for(i = 0; i < sizeof(softID); i++)
  {
    SOFTmsgData[msgIndex] = softID[i];
    msgIndex++;
  } 
  SOFTmsgData[msgIndex] = '*';
  msgIndex++;
  
  //append softApp
  for(i = 0; i < sizeof(softApp); i++)
  {
     SOFTmsgData[msgIndex] = softApp[i];
     msgIndex++;
  }
  SOFTmsgData[msgIndex] = '*';
  msgIndex++;
  
  //append softCD
  for(i = 0; i < sizeof(softCD); i++)
  {
     SOFTmsgData[msgIndex] = softCD[i];
     msgIndex++;
  }
  SOFTmsgData[msgIndex] = '*';
  msgIndex++;
  
  //append custom field if needed
  if(appendCustom)
  {
    for(i = 0; i < customSize; i++)
    {
      SOFTmsgData[msgIndex] = customField[i];
      msgIndex++;
    }
    SOFTmsgData[msgIndex] = '*';
    msgIndex++;
  }
  
  SOFT_TP_msg.id.set_J1939ID(PRIORITY_6, SOFT_PF, SOFT_PS,nvm_ecuid.j1939_source_address);
    
  SOFT_TP_msg.length = msgSize; 
  SOFT_TP_msg.data = SOFTmsgData;
  SOFT_TP_tx.SendMsg(&SOFT_TP_msg);    
  
}

void SendVINMsg()
//******************************************************************************
//    returns     : NONE.
//
//		Created By  : SLM
//    Date Created: 7 Feb, 2014
//    Description : Send out VIN TP message
//    Notes       :
//******************************************************************************
{  
  if(VIN_TP_tx.Idle())
  {
    VIN_TP_msg.id.set_J1939ID(PRIORITY_6,  VIN_PF, VIN_PS, nvm_ecuid.j1939_source_address);
      
    for(uint8_t i = 0; i < VIN_MSG_LENGTH; i++)
    {
      VINmsgData[i] = BOBCAT_SERIAL_NUMBER[i];
    }
    
    VIN_TP_msg.length = 20; 		
      
    VIN_TP_msg.data = VINmsgData;
    VIN_TP_tx.SendMsg(&VIN_TP_msg);
  }
}

//************************************************************************************************
//
// MACHINE CONFIG MESSAGES
//
//************************************************************************************************
void update_HWJ1939AcknowledgeMsg_tx(hw_can_msg_t *msg)
{
  msg->set_byte(0, AcknowledgeData[0]);
  msg->set_byte(1, AcknowledgeData[1]);
  msg->set_byte(2, AcknowledgeData[2]);
  msg->set_byte(3, AcknowledgeData[3]);
  msg->set_byte(4, AcknowledgeData[4]);
  msg->set_byte(5, AcknowledgeData[5]);
  msg->set_byte(6, AcknowledgeData[6]);
  msg->set_byte(7, AcknowledgeData[7]);
}

static void initialize_HWJ1939AcknowledgeMsgInt_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jan, 2007
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  HWJ1939AcknowledgeMsgIntTX.initialize();
  HWJ1939AcknowledgeMsgIntTX.mbuff.id.set_J1939ID(PRIORITY_6, ACKNOWLEDGE_PF, GLOBAL_ADDR, nvm_ecuid.j1939_source_address);

  HWJ1939AcknowledgeMsgIntTX.pre_tx_callback = update_HWJ1939AcknowledgeMsg_tx;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&HWJ1939AcknowledgeMsgIntTX);
}


void update_HWJ1939MachineConfigMsg_tx(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jan, 2007
//    Description : Transmit machine config message.
//    Notes       :
//******************************************************************************
{

  msg->set_byte(0, (uint8_t)(((uint16_t)CONSTANT_DATA->AUTOIDLE_IDLE_DELAY * 5) >> 2));//convert from 0.1 sec counts to 0.08 sec counts
  msg->set_byte(1, CONSTANT_DATA->AUX_ADJ_FLOW_FUNCTION);
  msg->set_byte(2, GATEWAY);
  msg->set_byte(3, UNDEFINED);
  msg->set_word(2, CONSTANT_DATA->ECO_MODE_THROTTLE_REDUCTION);
  msg->set_byte(6, UNDEFINED);
  msg->set_byte(7, UNDEFINED);
}

static void initialize_HWJ1939MachineConfigMsgInt_tx (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jan, 2007
//    Description : Initializes CAN message.
//    Notes       :
//******************************************************************************
{
  HWJ1939ConfigMsgIntTX.initialize();
  HWJ1939ConfigMsgIntTX.mbuff.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, MACHINE_CONFIG_PS, nvm_ecuid.j1939_source_address);

  HWJ1939ConfigMsgIntTX.pre_tx_callback = update_HWJ1939MachineConfigMsg_tx;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&HWJ1939ConfigMsgIntTX);
}


void HWJ1939RequestMsg_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jan, 2007
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  hw_can_msg_t msg_data;
  uint8_t msg_DA, msg_PF, msg_PS, msg_SA;
    
  msg_DA = msg->id.get_J1939_DA();
  msg_SA = msg->id.get_J1939_SA();
  msg_PF = msg->get_byte(1);
  msg_PS = msg->get_byte(0);
  
  
  if((msg_DA == nvm_ecuid.j1939_source_address) || (msg_DA == GLOBAL_ADDR))
  {
    // MACHINE CONFIG 1 MESSAGE RESPONSE 
    if((msg_PF == PROPRIETARY_B) && (msg_PS == MACHINE_CONFIG_PS))
    {
      msg_data.id.set_J1939ID(PRIORITY_6, PROPRIETARY_B, MACHINE_CONFIG_PS, nvm_ecuid.j1939_source_address );
      msg_data.DLR = 8;
      msg_data.set_byte(0, (uint8_t)(((uint16_t)CONSTANT_DATA->AUTOIDLE_IDLE_DELAY * 5) >> 2));//convert from 0.1 sec counts to 0.08 sec counts
      msg_data.set_byte(1, CONSTANT_DATA->AUX_ADJ_FLOW_FUNCTION);
      msg_data.set_byte(2, GATEWAY);
      msg_data.set_byte(3, UNDEFINED);
      msg_data.set_word(2, CONSTANT_DATA->ECO_MODE_THROTTLE_REDUCTION);
      msg_data.set_byte(6, UNDEFINED);
      msg_data.set_byte(7, UNDEFINED);
        
      hw_can_txq[HWC_CAN0].send_msg(&msg_data);

    }
  
    else if((msg_PF == SERV_PF) && (msg_PS == SERV_PS))
    {
      uint16_t tempTime;
      
      msg_data.id.set_J1939ID(PRIORITY_6, SERV_PF, SERV_PS, nvm_ecuid.j1939_source_address );
      msg_data.DLR = 8;
      
      tempTime = (uint16_t)((actualHourMeter - eeMirror.serviceClockResetTime)/HOUR_METER_TO_HOUR_FCT);
      tempTime = (uint16_t)(eeMirror.serviceClockLength/HOUR_METER_TO_HOUR_FCT) - tempTime;
      tempTime = tempTime + 32127; // Offset by 32127  
      
      msg_data.set_byte(0, NOT_AVAILABLE);
      msg_data.set_byte(1, NOT_AVAILABLE);
      msg_data.set_byte(2, NOT_AVAILABLE);
      msg_data.set_byte(3, NOT_AVAILABLE);
      msg_data.set_byte(4, NOT_AVAILABLE);
      msg_data.set_byte(5, 0); //Set to service check for entire machine
      msg_data.set_byte(6, (uint8_t)(tempTime));
      msg_data.set_byte(7, (uint8_t)(tempTime >> 8));
      
      hw_can_txq[HWC_CAN0].send_msg(&msg_data);
    }

    else if((msg_PF == VIN_PF) && (msg_PS == VIN_PS))
    {
      SendVINMsg();
    }
    
    else if((msg_PF == SOFT_PF) && (msg_PS == SOFT_PS))
    {
      SendSOFTMsg();      
    }
    
    // DEFAULT NAK
    else
    {
      if(msg_DA != GLOBAL_ADDR) // Do not NAK a global request
      {
        msg_data.id.set_J1939ID(PRIORITY_6, ACKNOWLEDGE_PF, msg_SA, nvm_ecuid.j1939_source_address );
        msg_data.DLR = 8;
        msg_data.set_byte(0, NAK);
        msg_data.set_byte(1, NOT_AVAILABLE);
        msg_data.set_byte(2, 0xFF);
        msg_data.set_byte(3, 0xFF);
        msg_data.set_byte(4, 0xFF);
        msg_data.set_byte(5, 0);	 
        msg_data.set_byte(6, msg->get_byte(1));
        msg_data.set_byte(7, msg->get_byte(2));
        
        hw_can_txq[HWC_CAN0].send_msg(&msg_data);
      }
    }
  }
}

static void initialize_HWJ1939RequestMsgInt_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jan 2007
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  HWJ1939RequestMsgIntRX.initialize();
  HWJ1939RequestMsgIntRX.rx_id     .set_J1939ID(0, REQUEST_PF, 0, 0);
  HWJ1939RequestMsgIntRX.rx_id_mask.set_J1939ID(0, 0xFF, 0, 0);

  HWJ1939RequestMsgIntRX.rx_callback = HWJ1939RequestMsg_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&HWJ1939RequestMsgIntRX);
}



//************************************************************************************************
//
// TEST MESSAGES
//
//************************************************************************************************
#if 0
#warning "CAN Test message turned on"

void Test44_rx_callback(hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jan, 2007
//    Description : Receive info from CAN.
//    Notes       :
//******************************************************************************
{
  pressure_TorqueLimiter = msg->get_word(0);
}

static void initialize_Test44_rx(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 09 Jan 2007
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  Test44RX.initialize();
  Test44RX.rx_id     .set_J1939ID(0, 0xFF, 0x44, 0x48);
  Test44RX.rx_id_mask.set_J1939ID(0, 0xFF, 0xFF, 0xFF);

  Test44RX.rx_callback = Test44_rx_callback;

  hw_can_rx_handler[HWC_CAN0].add_msg(&Test44RX);
}



void update_TestCAN45sTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 01 June, 2006
//    Description : Updates data in Hydraulics and BICS control TX message.
//    Notes       :
//******************************************************************************
{

msg->set_byte(0, flag_InitEERead);
msg->set_byte(1, state_Buzzer);
msg->set_word(1, rm_Console);
msg->set_byte(4, cabKeyDetect);
msg->set_byte(5, din_RunEnter);
msg->set_byte(6, din_SwPowerRelay);
msg->set_byte(7, state_System);




}

static void initialize_TestCAN45sTX(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 01 June, 2006
//    Description : Initialize Hydraulics and BICS control TX message.
//    Notes       :
//******************************************************************************
{
  TestCAN45sTX.initialize();
  TestCAN45sTX.mbuff.id.set_J1939ID(PRIORITY_6, 0xFF, 0x45, nvm_ecuid.j1939_source_address);

  TestCAN45sTX.set_send_rate(1);
  TestCAN45sTX.pre_tx_callback = update_TestCAN45sTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&TestCAN45sTX);
}


void update_TestCAN46sTX (hw_can_msg_t *msg)
//******************************************************************************
//    returns     : NONE.
//            msg : Data to be sent.
//    Created By  : SLM
//    Date Created: 01 June, 2006
//    Description : Updates data in Hydraulics and BICS control TX message.
//    Notes       :
//******************************************************************************
{

msg->set_word(0,calc_ifbk_AuxBase);
msg->set_word(1,calc_ifbk_AuxRod);
msg->set_word(2,calc_ifbk_OffsetBase);
msg->set_word(3,calc_ifbk_OffsetRod);


}

static void initialize_TestCAN46sTX(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 01 June, 2006
//    Description : Initialize Hydraulics and BICS control TX message.
//    Notes       :
//******************************************************************************
{
  TestCAN46sTX.initialize();
  TestCAN46sTX.mbuff.id.set_J1939ID(PRIORITY_6, 0xFF, 0x46, nvm_ecuid.j1939_source_address);

  TestCAN46sTX.set_send_rate(1);
  TestCAN46sTX.pre_tx_callback = update_TestCAN46sTX;

  hw_can_tx_scheduler[HWC_CAN0].add_msg(&TestCAN46sTX);
}

#endif


void ap_can_update(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : AAL
//    Date Created: 28 Oct 2016
//    Description : Application specific update for CAN.
//    Notes       :
//******************************************************************************
{

  //Only check it system state is normal, shutdown and init we don't care
  if(state_System == SYS_NORMAL)
  {

    // Check for Service Tool CAN stale messages ******************************************
    if(CAN_STsRX.msg_age_mS < CAN_ST_TIMEOUT)
    {
      state_ST_CAN = NORMAL;
    }
    else
    {
      state_ST_CAN = NO_COMMUNICATION;
      STAuxOverrideDebounce = 0;
      STAuxOverridePressed = 0;
      cmd_AuxEnable_ST = 0;
    }


    // Check for ACD CAN stale messages ***************************************************
    if(CONSTANT_DATA->RACD_FUNCTION != NON_FUNCTIONAL)
    {
       // Check for CAN stale on ACD CAN
      if(CAN_ACDsRX.msg_age_mS < CAN_ACD_TIMEOUT)
      {
        state_ACD_CAN = NORMAL;
      }
      else
      {
        state_ACD_CAN = NO_COMMUNICATION;
        ACDAuxOverrideDebounce = 0;
        ACDAuxOverridePressed = 0;
        cmd_AuxEnable_ACD = 0;
      }
    }

    // Message times to model inputs   ***************************************************************
    if(state_Engine == ENGINE_CRANKING)
    {
      CAN01_ThrottleRX.msg_age_mS = 0;
      CAN01_SecondaryRX.msg_age_mS = 0;
      PanelButtonStateIntRX.msg_age_mS = 0;
      LFE_CAN0_RX.msg_age_mS = 0;
    }

    if(CONSTANT_DATA->THROTTLE_TYPE == ACTUATOR)
    {
       msgAge_Throttle = CAN01_ThrottleRX.msg_age_mS;
    }
    if(CONSTANT_DATA->THROTTLE_TYPE == CAN_ACTUATOR)
    {
      msgAge_Throttle = LFE_CAN0_RX.msg_age_mS;
    }
    msgAge_Secondary = CAN01_SecondaryRX.msg_age_mS;
    msgAge_StdDisplay = PanelButtonStateIntRX.msg_age_mS;

  }

  if(state_System == SYS_POWER_DOWN)
  {
    SEND_CAN03_NOW;
  }

  if(previousAuxEnable != state_AuxEnable)
  {
    SEND_CAN20_NOW;
    previousAuxEnable = state_AuxEnable;
  }

  if( (previousAuxBaseState  != state_AuxBase  )
    ||(previousAuxBaseActive != (uint8_t)(hs_AuxBase > 0))
    ||(previousAuxRodState   != state_AuxRod   )
    ||(previousAuxRodActive  != (uint8_t)(hs_AuxRod  > 0)))
  {
    SEND_CAN02_NOW;
    previousAuxBaseState  = state_AuxBase;
    previousAuxBaseActive = (hs_AuxBase > 0);
    previousAuxRodState   = state_AuxRod;
    previousAuxRodActive  = (hs_AuxRod  > 0);
  }
  
  SOFT_TP_tx.update();
  VIN_TP_tx.update();
}


//************************************************************************************************
//
// INITIALIZATION
//
//************************************************************************************************

void ap_can_initialize (void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 5 Sept, 2007
//    Description : Calls functions to initialize CAN messages.
//    Notes       :
//******************************************************************************
{
  //initialize_TestCAN45sTX();
    
  //initialize_Test44_rx();
  
  initialize_CAN_ST_rx();
  initialize_HoursUpdatesRX_rx();
  
  if(CONSTANT_DATA->DELUXE_GEN5_5_FUNCTION == NON_FUNCTIONAL)
  {
    initialize_PanelButtonRX();
  }
  
  initialize_PanelIORX();
  initialize_HWJ1939RequestMsgInt_rx();

  if(CONSTANT_DATA->RACD_FUNCTION != NON_FUNCTIONAL)
  {
    initialize_CAN_ACD_rx();
    initialize_CAN02sTX();
    initialize_CAN06sTX();
  }

  initialize_HWJ1939BICSControl_tx();
  initialize_HWJ1939AcknowledgeMsgInt_tx();
  initialize_HWJ1939MachineConfigMsgInt_tx();
  SOFT_TP_tx.initialize(HWC_CAN0);
  VIN_TP_tx.initialize(HWC_CAN0);

  initialize_CAN01sTX();
  initialize_CAN03sTX();
  initialize_CAN05sTX();
  initialize_CAN20sTX();
  initialize_CAN21sTX();
  initialize_HWJ1939EngineHoursIntTX();
  initialize_VEP_CAN0_TX();
  initialize_PanelTellTalesTX();
  initialize_PanelButtonsTX();
  initialize_PanelGaugeTX();
  initialize_PanelLCDTX();
  initialize_PanelLCDIconsTX();
  initialize_EEC1_CAN0_TX();
  initialize_ET1_CAN0_TX();
  initialize_EFL_P1_CAN0_TX();
  initialize_PrimaryControls_tx();
  initialize_DD_CAN0_TX();
  initialize_AAI_CAN0_TX();
  
  if(CONSTANT_DATA->THROTTLE_TYPE != ACTUATOR)
  {
    initialize_EEC2_CAN0_TX();
  }
  

  if(CONSTANT_DATA->ECU_FUNCTION != NON_FUNCTIONAL)
  {
    initialize_CAN21extTX();
  }
  
  if(CONSTANT_DATA->THROTTLE_TYPE == ACTUATOR)
  {
    initialize_CAN01_Throttle_rx();
    initialize_TFAC_tx();
  }
  else if(CONSTANT_DATA->THROTTLE_TYPE == CAN_ACTUATOR)
  {
    initialize_TFAC_tx();
    initialize_LFE_CAN0_rx();
  }

  if(CONSTANT_DATA->SECONDARY_FUNCTION != NON_FUNCTIONAL)
  {
    initialize_CAN01_Secondary_rx();
    initialize_SecondaryControls_rx();
  }
  
  if((CONSTANT_DATA->EMEA_CONTROLS_OPTION_A != NON_FUNCTIONAL)
  || (CONSTANT_DATA->EMEA_CONTROLS_OPTION_B != NON_FUNCTIONAL)
  || (CONSTANT_DATA->EMEA_CONTROLS_OPTION_C != NON_FUNCTIONAL)
  || (CONSTANT_DATA->EMEA_CONTROLS_REVERSE != NON_FUNCTIONAL))
  {
    initialize_AuxControlMode_tx();
    initialize_HydControlSettings_rx();
  }

  if(CONSTANT_DATA->DEPTH_CHECK_FUNCTION != NON_FUNCTIONAL)
  {
    initialize_DigDepthStatus_rx();
  }

  if(CONSTANT_DATA->WORKGROUP_FUNCTION != NON_FUNCTIONAL)
  {
    initialize_BJM2_Right_rx();
    initialize_BJM2_Left_rx();
   // initialize_TestCAN45sTX();
   // initialize_TestCAN46sTX();
  }

  STAuxOverrideDebounce = 0;
  STAuxOverridePressed = 0;
  ACDAuxOverrideDebounce = 0;
  ACDAuxOverridePressed = 0;
  can_OffsetSelectSw = 0;
  can_RightHandleSelectSw = 1; //set to high until incoming CAN message clears it

}




