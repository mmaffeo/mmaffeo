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
* First written on 16 November, 2005 by Spencer Mindeman
*
* Module Description:
* Main Subroutines.
***************************************************************/
//******************************************************************************
// INCLUDES
//******************************************************************************
#include "hw_io.h"
#include "nvm_ecuid.h"
#include "ap_bservice.h"
#include "ap_gateway.h"
#include "ap_can.h"
#include "ap_dv.h"
#include "ap_eeprom.h"
#include "ap_deluxeG5.h"
#include "ap_deluxeG55.h"
#include "ap_subs.h"
#include "ap_main.h"
#include "global.h"
#include "ap_MXGWcontrol_defs.h"
#include "cdata.h"
#include "defines.h"
#include "ap_bservice_CAN04.h"
#include "ap_bservice_CANOpen.h" //Max3363
#include "ap_bservice_CANStd.h" //Max3363
#include "ap_keylessstart.h"
#include "ap_keylessentry.h"
#include "ap_engine.h"

//******************************************************************************
// Compile Time Assertions
//******************************************************************************
HW_CTA(sizeof(int8_T)   == sizeof(int8_t));
HW_CTA(sizeof(uint8_T)  == sizeof(uint8_t));
HW_CTA(sizeof(int16_T)  == sizeof(int16_t));
HW_CTA(sizeof(uint16_T) == sizeof(uint16_t));
HW_CTA(sizeof(int32_T)  == sizeof(int32_t));
HW_CTA(sizeof(uint32_T) == sizeof(uint32_t));
HW_CTA(sizeof(real32_T) == sizeof(float));
HW_CTA(sizeof(real64_T) == sizeof(double));

//******************************************************************************
// DEFINES
//******************************************************************************
#define TIME_TO_POWER_UP              7
#define TIME_TO_POWER_DOWN            20

//******************************************************************************
// GLOBAL VARIABLES
//******************************************************************************
static uint16_t previousClock5s = 0;
static uint16_t previousClock1s = 0;
static uint16_t previousClock2s = 0;
static uint16_t previousClock500ms = 0;
static uint16_t previousClock200ms = 0;
static uint16_t previousClock100ms = 0;
static uint16_t previousClock50ms = 0;
static uint16_t previousClock20ms = 0;
static uint16_t lightDelayCount;

uint8_t keylessEntryPowerUp; 

uint8_t powerDownTimer;

static uint8_t set_ServiceClock;

uint8_t flag_ACDFilter;
bool flag_DDPLock;

uint8_t dealerInfoSent;
uint8_t reset_ServiceClock;


//******************************************************************************
// FUNCTIONS
//******************************************************************************


void initialize_variables(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 27 May, 2009
//    Description : Main initialize function.
//    Notes       :
//******************************************************************************
{
  cnt_TryAgain = 0;

  state_System = SYS_INIT;

  hw_pwm_SetFrequency(AUX_BASE_HS_PWM, CONSTANT_DATA->AUX_PWM_FREQ);//HC_HSD6
  hw_pwm_SetFrequency(AUX_ROD_HS_PWM, CONSTANT_DATA->AUX_PWM_FREQ); //HC_HSD5 - note this sets frequency for HC_HSD1,3 and 7 also
  hw_pwm_SetFrequency(OFFSET_BASE_HS_PWM, CONSTANT_DATA->OFFSET_PWM_FREQ); //HC_HSD4
  hw_pwm_SetFrequency(OFFSET_ROD_HS_PWM, CONSTANT_DATA->OFFSET_PWM_FREQ); //HC_HSD2
  hw_pwm_SetFrequency(DUMP_VALVE_HS_PWM, 100);//HC_HSD8

  flag_HourOverflow = 0;

  dvPassword = 0;
  dvCommand = 0;
  inDVCode = false;

  newPasswordVerification = FALSE;
  newJobClockVerification = FALSE;
  newUserNameVerification = FALSE;
  newPasswordNumber       = NUMBER_TOTAL_PASSWORDS;
  newUserNameNumber       = NUMBER_TOTAL_USERS;
  newJobClockNumber       = NUMBER_TOTAL_USERS;
  ddpPasswordScreenChanged = TRUE;
  obtainedCurrentUser      = FALSE;
  ddpServiceScreenFlag = TRUE;


  dlxMode = DLX_STARTUP_IDLE;

  msg_Counter = 0;

  current_user = 0xFF;
  dealerInfoSent = FALSE;
  newlyBootedDDP = TRUE;
  flag_DDPLock = FALSE;
  state_ServiceClock = 0;

  if(CONSTANT_DATA->DELUXE_GEN5_FUNCTION == NON_FUNCTIONAL)
  {
    ddp_MachineLock = ACTIVE;
  }
  else
  {
    ddp_MachineLock = INACTIVE;
  }

  sendFirstJobClockCmd = TRUE;

  ddpSwitchStatus.switchByte[0] = 0;
  ddpSwitchStatus.switchByte[1] = 0;
  ddpSwitchStatus.switchByte[2] = 0;
  ddpSwitchStatus.switchByte[3] = 0;
  ddpSwitchStatus.switchByte[4] = 0;

  ddpSwitchStatus.data.machineLock = 1;

  flag_SendDeluxeWarning = FALSE;
  flag_SendWarningHistory = FALSE;
  flag_ActiveWarning = INACTIVE;
  flag_StdActiveWarn = INACTIVE;

  //Keyless panel parameters
  pwd_Position = 0;

  for(uint8_t i=0; i < 5; i++)
  {
    pwd_Keyless[i] = 0;
  }

  lightDelayCount = CONSTANT_DATA->POWER_DOWN_LIGHT_HOLD_TIME;

  //firstTimeThruPowerDown = true;
  
  gwServiceTimer = SERVICE_TIME_DISPLAY;
  set_ServiceClock = FALSE;
  powerUpTimer = TIME_TO_POWER_UP;

  state_MachineLock = ACTIVE;

  for(uint16_t i=0; i < NUMBER_OF_EVENTS; i++)
  {
    eventState[i] = NEW_EVENT;
  }

  //Determine if contant data is programmed or if it just has the default constant data in it.
  if(CONSTANT_DATA->CONSTANT_DATA_DEFAULT == 65535)
  {
    state_ConstantData = NOT_PROGRAMMED;
  }
  else
  {
    state_ConstantData = NORMAL;
  }
  reset_ServiceClock = 0;
  serviceType = 0;

}
void ap_main_initialize(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Main initialize function.
//    Notes       :
//******************************************************************************
{
  hw_mcu_SetPowerHold(TRUE);
  
  flag_InitEERead = FALSE;

  ap_can_initialize();
  ap_gateway_initialize();
  
  initialize_ap_dv();
  initialize_ap_dv2();
  initialize_ap_ActiveCodes();
  ap_bservice_CAN04_initialize(MX_Gtwy_Control_Y.Error_Codes, sizeof(MX_Gtwy_Control_Y.Error_Codes)/sizeof(uint16_t));
  CANOpenInitialize(); //Max3363
  CANStdInitialize(); //Max3363
  MX_Gtwy_Control_initialize();

  if(CONSTANT_DATA->ECU_FUNCTION != NON_FUNCTIONAL)
  {
    initialize_gateway_filters();
    ap_ECU_initialize();
  }

  previousClock100ms = 0;
  previousClock5s = 0;

  hourMeterUpdateTimer = RELOAD_6_MIN;
  jobClockUpdateTimer = RELOAD_6_MIN;
  jobClockLHPUpdateTimer[0] = RELOAD_6_MIN;
  jobClockLHPUpdateTimer[1] = RELOAD_6_MIN;
  idleClockUpdateTimer = RELOAD_6_MIN;
  actualHourMeterCopy = 0;
  actualHourMeter = 0;
  eeUpdate = 0;
  eeTimeToUpdateMirror = FALSE;
  eeBusy = FALSE;
  eeState = EE_US_IDLE;
  eeMode = EE_WRITE_STATUS;
 
  eeServiceEEPROM();
  
  initialize_variables();

  if(CONSTANT_DATA->DELUXE_GEN5_FUNCTION != NON_FUNCTIONAL)
  {
     ap_DeluxeG5_initialize();
  }

#ifdef HCS12_BSP_EMU //if M4 compile this - Gen5.5 Display and Keyless entry only supported on M4
  if(CONSTANT_DATA->DELUXE_GEN5_5_FUNCTION != NON_FUNCTIONAL)
  {
    ap_DeluxeG55_initialize();
  }
  
  if(CONSTANT_DATA->KEYLESS_ENTRY_FUNCTION == NON_FUNCTIONAL
  && CONSTANT_DATA->DELUXE_GEN5_5_FUNCTION == NON_FUNCTIONAL)
  {
    ap_keylessstart_initialize(); 
  }
  else if(CONSTANT_DATA->KEYLESS_ENTRY_FUNCTION != NON_FUNCTIONAL)
  {
    ap_keylessentry_initialize();    
  }
#else
  ap_keylessstart_initialize();
#endif

  activeCodeIndex = 0;


  //Setting the pin to FALSE turns on the terminator
  hw_dout_SetValue(HWC_DOUT_CAN_TERM_OFF1, CONSTANT_DATA->INTERNAL_TERMINATOR);
  hw_dout_SetValue(HWC_DOUT_CAN_TERM_OFF2, CONSTANT_DATA->EXTERNAL_TERMINATOR);

  //Turn off switching outputs for analog inputs.
  if((CONSTANT_DATA->EOP_FUNCTION != SWITCH_INPUT))//AIN01_DIN01
  {
    hw_dout_SetValue(HWC_DOUT_WC_CONFIG1_AUTO, FALSE);
    hw_dout_SetValue(HWC_DOUT_WC_CONFIG1,FALSE);
  }

  if(CONSTANT_DATA->HOT_FUNCTION != SWITCH_INPUT)//AIN02_DIN02
  {
    hw_dout_SetValue(HWC_DOUT_WC_CONFIG2_AUTO, FALSE);
    hw_dout_SetValue(HWC_DOUT_WC_CONFIG2,FALSE);
  }

  //AIN03_DIN03 - Analog Input
  hw_dout_SetValue(HWC_DOUT_WC_CONFIG3_AUTO, FALSE);
  hw_dout_SetValue(HWC_DOUT_WC_CONFIG3,FALSE);

  //AIN04_DIN04 - Analog Input
  hw_dout_SetValue(HWC_DOUT_WC_CONFIG4_AUTO, FALSE);
  hw_dout_SetValue(HWC_DOUT_WC_CONFIG4,FALSE);


  //AIN12 - Analog Input
  hw_dout_SetValue(HWC_DOUT_WC_ON5_AUTO, FALSE);
  hw_dout_SetValue(HWC_DOUT_WC_ON5,FALSE);

  //AIN10 - Analog Input
  hw_dout_SetValue(HWC_DOUT_WC_ON7_AUTO, FALSE);
  hw_dout_SetValue(HWC_DOUT_WC_ON7, FALSE);

  if(eeMirror.deluxe_G5 && (CONSTANT_DATA->DELUXE_GEN5_FUNCTION != NON_FUNCTIONAL))
  {
    rx_DeluxeStatus.msg_age_mS = 0;
    state_DeluxeG5 = NORMAL;
  }
  else
  {    
    rx_DeluxeStatus.msg_age_mS = 65535;
    state_DeluxeG5 = INACTIVE;
  }

  ecu_HP = 0xFF;
  SEND_CAN01_NOW;

  HW_DEBUG(("App Init complete"));
}

void powerUp(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 12 May, 2006
//    Description : Power Up proceedurs.
//    Notes       :
//******************************************************************************
{
  if (powerUpTimer)
  {
    
    // do this only at power up
    if (--powerUpTimer == 0)
    {
      // set for next tenth of hour tick */
      hourMeterUpdateTimer = RELOAD_6_MIN - (actualHourMeter - (actualHourMeter/RELOAD_6_MIN)*RELOAD_6_MIN);
      jobClockUpdateTimer = hourMeterUpdateTimer;
      idleClockUpdateTimer = hourMeterUpdateTimer;

      // update after powerup just completed */
      UpdateHourMeter();
      UpdateUserJobClock();
      UpdateIdleTime();
      
      uint8_t  tempNewType = bservice_dv_read_byte(1);
      uint16_t tempNewApp = (bservice_dv_read_byte(2) << 8) + bservice_dv_read_byte(3);
      uint16_t tempNewCD = (CONSTANT_DATA->MAJOR_VERSION_NUMBER << 8) + CONSTANT_DATA->MINOR_VERSION_NUMBER;

      if(eeMirror.recoveryMode == SOFTWARE_UPDATED)
      {
        QueueEventDiag(DEVICE_ERROR_ID, FN_MAIN_CONTROLLER, SOFTWARE_UPDATED, current_user, actualHourMeter/HOUR_METER_TO_HOUR_FCT);

        QueueSoftwareUpdate(tempNewType, tempNewApp, tempNewCD, (uint16_t)(actualHourMeter/HOUR_METER_TO_HOUR_FCT));
      }
      else if(eeMirror.recoveryMode)
      {
        UpdateEvent(LOC_RECOVERY_FAILURE);
        QueueEventDiag(0x4D, FN_INTERRUPTED_POWER, FAILURE, current_user, actualHourMeter/HOUR_METER_TO_HOUR_FCT);
      }

      eeMirror.recoveryMode = TRUE;
      UpdateEEVariables(NOW);

      //Keyless Start Passwords - 5 digits
      for(uint8_t i=0; i < MAX_PWD_CHAR; i++)
      {
        ee_OwnerPassword[i] = eeMirror.password[0].value[i];
        ee_User1Password[i] = eeMirror.password[1].value[i];
        ee_User2Password[i] = eeMirror.password[2].value[i];
        ee_MasterPassword[i] = MASTER_PWD[i];
      }
    }
  }
}

void powerDown(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 12 May, 2006
//    Description : Power Down.
//    Notes       :
//******************************************************************************
{

  static uint8_t reset_recovery = FALSE;
  static uint8_t firstTimeThruPowerDown = true;
  
  static bool powerDownAttempt = false;
  
  // If lights are active when machine is shutdown, we want to hold lights on for X amount of time unless turned off
  // Need to look at both lights for euro road light kit.
  if((state_Key == INACTIVE)
  && (dout_Lights == ACTIVE) && (lightDelayCount) && (state_VBattery == NORMAL) 
  && (state_PanelButtons == NORMAL) )
  {
    lightDelayCount--;
    state_System = SYS_LIMITED;
    SendMsg_03_Now();
    powerDownAttempt = true;
  }
#ifdef HCS12_BSP_EMU //if M4 compile this
  else if((state_Key == INACTIVE)
       && (CONSTANT_DATA->DELUXE_G55_PHONE_LIMITED_FUNCTION != NON_FUNCTIONAL)
       && (getPhoneState() == PHONE_CONNECTED_IN_CALL) && (state_CommDeluxeG55 == NORMAL))
  {
    state_System = SYS_PHONE_LIMITED;
    SendMsg_03_Now();
    powerDownAttempt = true;
  }
#endif
  else if((state_Key == INACTIVE)&&(state_KeylessEntryPowerHold == KE_PWR_INACTIVE))
  {
    powerDownAttempt = true;
    state_System = SYS_POWER_DOWN;
      
    if(firstTimeThruPowerDown)
    {
      powerUpTimer = 0;
      SendMsg_03_Now();
      eeMirror.recoveryMode = FALSE;
      UpdateEEVariables(NOW); 
      state_MachineLock = 2;
      firstTimeThruPowerDown = FALSE;
      powerDownTimer = TIME_TO_POWER_DOWN;
    }
    else
    {
      if((((eeMode == EE_IDLE) && (!eeTimeToUpdateMirror)) || (!flag_InitEERead) || (eeMode == EE_NO_ENABLED_HOUR_METERS)) && (!powerDownTimer))
      {
        hw_mcu_SetPowerHold(FALSE);
      }
      else if(powerDownTimer)
      {
        powerDownTimer--;
      }
    }
  }

  if(state_Key == ACTIVE)
  {
    //Powering back up before power down completed 
    if(powerDownAttempt)
    {
      // reset the recovery flag
      if(!reset_recovery && (eeMode == EE_IDLE))
      {
        eeMirror.recoveryMode = FALSE;
        eeMode = EE_HM_UPDATE;
        eeState = EE_HM_WRITE_INIT;
        UpdateEEVariables(NOW);
        reset_recovery = TRUE;
      }
      if(((eeMode == EE_IDLE) && (!eeTimeToUpdateMirror)) || (!flag_InitEERead) || (eeMode == EE_NO_ENABLED_HOUR_METERS))
      {
          hw_reset_force(0,0);
      }
    }
  }
}

void ap_main_update(void)
//******************************************************************************
//    returns     : NONE.
//
//    Created By  : SLM
//    Date Created: 16 Nov, 2005
//    Description : Main routine.
//    Notes       :
//******************************************************************************
{

  // Perform power up functions

  // 10ms Loop *************************************************

  // DV Mode Test
  if((dvPassword == DV_AUTHORIZATION) && hw_din_GetValue(REMOTE_KEY))
  {
    if(inDVCode == FALSE)
    {
      InitDVTest();
      inDVCode = TRUE;
      state_System = SYS_DV;
    }
    DVTest();
  }
  else if(inDVCode == TRUE)
  {
    hw_reset_force(0,0);
  }
  else
  {

    if((state_DeluxeG5 == NORMAL) && (dlxMode != DLX_STARTUP_IDLE))
    {
      send_DeluxeG5_StartUpData();
    }
 
    if(CONSTANT_DATA->ECU_FUNCTION != NON_FUNCTIONAL)
    {
      ap_ECU_update();
    }

    if(CONSTANT_DATA->DELUXE_GEN5_FUNCTION != NON_FUNCTIONAL)
    {
      Deluxe_TP_update(); 
    }    
#ifdef HCS12_BSP_EMU //if M4 compile this - Gen5.5 Display and Keyless entry only supported on M4
    if(CONSTANT_DATA->DELUXE_GEN5_5_FUNCTION != NON_FUNCTIONAL)
    {
      ap_DeluxeG55_update();
    }

    if(CONSTANT_DATA->KEYLESS_ENTRY_FUNCTION == NON_FUNCTIONAL
    && CONSTANT_DATA->DELUXE_GEN5_5_FUNCTION == NON_FUNCTIONAL)
    {
      ap_keylessstart_Update();
    }
    else if(CONSTANT_DATA->KEYLESS_ENTRY_FUNCTION != NON_FUNCTIONAL)
    {
      ap_keylessEntry_Update();
    }
#else
    ap_keylessstart_Update();
#endif


    // Setup parameters for model

    // Analog Inputs
    ain_PrecisionReference = hw_adc_GetValue(PREFERENCE_AFBK);
    ain_VBattery = hw_adc_GetValue(BATT_AFBK);
    ain_SwitchedPower = hw_adc_GetValue(SW_BATT_AFBK);
    ain_SensorSupply1 = hw_adc_GetValue(VSENSOR1_AFBK);
    ain_SensorSupply2 = hw_adc_GetValue(VSENSOR2_AFBK);

    ain_ECT = hw_adc_GetValue(ENG_COOLANT_TEMP_AIN);


    ain_FuelLevel = hw_adc_GetValue(FUEL_LEVEL_AIN);
    ain_Console = hw_adc_GetValue(CONSOLE_AIN);
    ain_LoadMoment = hw_adc_GetValue(LOAD_MOMENT_AIN);
    ain_OffsetPot = hw_adc_GetValue(OFFSET_POT_AIN);
    ain_AuxPot = hw_adc_GetValue(AUX_POT_AIN);
    ain_ThrottlePrimary = hw_adc_GetValue(THROTTLE_PRIMARY);

    freq_EngineSpeed = hw_fin_GetPeriodCount(HWC_FIN0);

    // Analog inputs with optional pullups
    adin_EOP = hw_adc_GetValue(ENG_OIL_PRESS_AIN);
    uint16_t tempValue = hw_adc_GetValue(HYD_OIL_TEMP_AIN);

    if((state_System == SYS_INIT) && (tempValue >= CONSTANT_DATA->HOT_DEBOUNCE_OORL) && (tempValue <= 400))
    {
      adin_HOT = 100;  //set value to 0 if constant data is out of range on startup
    }
    else
    {
      adin_HOT = tempValue;
    }
    adin_TravelPressureSwitch = hw_adc_GetValue(TRAVEL_LEVER_AIN);
    adin_LoadSense = hw_adc_GetValue(LOAD_SENSE_PRESS_AIN);
    ain_Aux2FlowControl = hw_adc_GetValue(AUX2_FLOW_CONTROL_AIN);

    //  Switch inputs
    din_TwoSpeedSwitch = hw_din_GetValue(TWO_SPEED_SW_DIN);
    din_Detent = hw_din_GetValue(DETENT_SW_DIN);
    din_AirFilter = hw_din_GetValue(AIR_FILTER_SW);
    din_HCFilter1 = hw_din_GetValue(HYD_OIL_FILTER_SW1);
    din_ACOn = hw_din_GetValue(AC_INPUT);
    din_RemoteKey = hw_din_GetValue(REMOTE_KEY);
    din_SecondAuxSw = hw_din_GetValue(SECOND_AUX_DIN);
    din_LeftHandleSelectSw = hw_din_GetValue(LEFT_HANDLE_SELECT_SW);

    
    // Load Moment enable switch input 
    if(CONSTANT_DATA->LOAD_MOMENT_ENABLE_INPUT == LOAD_MOMENT_ENABLE_NEW)
    {   // K25-K27 and E85 connected to analog input
        din_OWDEnableSw = (hw_adc_GetValue(OWD_ENABLE_AIN) > 200) ? true:false; //200 A2D counts ~= 6V
    }
    else if (CONSTANT_DATA->LOAD_MOMENT_ENABLE_INPUT == LOAD_MOMENT_ENABLE_OLD)
    {   // Sirius 2 connected to digital input
        din_OWDEnableSw = hw_din_GetValue(OWD_ENABLE_DIN);
    }
    else
    {
        din_OWDEnableSw = false;
    }


    if(downgradedFromDDP)
    {
      din_RunEnter = INACTIVE;
    }
    else
    {
      din_RunEnter = hw_din_GetValue(RUN_ENTER_SW);
    }

    din_EngineStart = hw_din_GetValue(START_ENGINE_SW);




    //Output feedbacks
    afbk_FuelSec = hw_adc_GetValue(FUEL_HOLD_HS_AFBK);
    afbk_OffsetBase = hw_adc_GetValue(OFFSET_BASE_HS_AFBK);
    ifbk_OffsetBase = hw_adc_GetValue(OFFSET_BASE_LS_IFBK);
    afbk_AuxBase = hw_adc_GetValue(AUX_BASE_HS_AFBK);
    ifbk_AuxBase = hw_adc_GetValue(AUX_BASE_LS_IFBK);
    afbk_HydEnable = hw_adc_GetValue(HYD_ENABLE_HS_AFBK);
    ifbk_HydEnable = hw_adc_GetValue(HYD_ENABLE_LS_IFBK);
    afbk_TwoSpeed = hw_adc_GetValue(TWO_SPEED_HS_AFBK);
    afbk_OffsetRod = hw_adc_GetValue(OFFSET_ROD_HS_AFBK);
    ifbk_OffsetRod = hw_adc_GetValue(OFFSET_ROD_LS_IFBK);
    afbk_AuxRod = hw_adc_GetValue(AUX_ROD_HS_AFBK);
    ifbk_AuxRod = hw_adc_GetValue(AUX_ROD_LS_IFBK);
    afbk_Diverter = hw_adc_GetValue(DIVERTER_HS_AFBK);
    ifbk_Diverter = hw_adc_GetValue(DIVERTER_LS_IFBK);
    afbk_HydBypass = hw_adc_GetValue(HYD_BYPASS_HS_AFBK);
    ifbk_HydBypass = hw_adc_GetValue(HYD_BYPASS_LS_IFBK);
    afbk_DumpValve = hw_adc_GetValue(DUMP_VALVE_HS_AFBK);
    ifbk_DumpValve = hw_adc_GetValue(DUMP_VALVE_LS_IFBK);

    dfbk_SwPowerOutput = hw_din_GetValue(SW_PWR_OUT_RLY_DFBK);
    din_SwPowerRelay = hw_din_GetValue(SW_PWR_OUT_RLY_DIN);
    dfbk_FuelPriOutput = hw_din_GetValue(FUEL_PULL_RLY_DFBK);
    din_FuelPriRelay = hw_din_GetValue(FUEL_PULL_RLY_DIN);
    din_GlowPlugRelay = hw_din_GetValue(GLOW_PLUG_RLY_DIN);
    dfbk_GlowPlugOutput = hw_din_GetValue(GLOW_PLUG_RLY_DFBK);
    dfbk_LightsOutput = hw_din_GetValue(LIGHTS_DFBK);
    din_StarterRelay = hw_din_GetValue(STARTER_RLY_DIN);
    dfbk_StarterOutput = hw_din_GetValue(STARTER_RLY_DFBK);
    dfbk_HVACOutput = hw_din_GetValue(HVAC_RLY_DFBK);
    dfbk_HydExchange = hw_din_GetValue(HYD_EXCHANGE_DFBK);
    dfbk_PBValveOutput = hw_din_GetValue(PBVALVE_RLY_DFBK);
    din_PBValveRelay = hw_din_GetValue(PBVALVE_RLY_DIN);

    scrn_DeluxePwdFail = (uint8_t)ddpSwitchStatus.data.inInitPasswordFailedScreen;


    // Keep machine locked until after the system is initialized
    if((eeMirror.passwordLock == ACTIVE) && !(ddpSwitchStatus.data.inInitPasswordScreen) && (!flag_DDPLock))
    {
      if(CONSTANT_DATA->DELUXE_GEN5_FUNCTION == NON_FUNCTIONAL)
      {
        ddp_MachineLock = ACTIVE;
      }
      else
      {
        ddp_MachineLock = INACTIVE;
      }
    }
    else if(ddpSwitchStatus.data.inInitPasswordScreen)
    {
      flag_DDPLock = TRUE;
    }


    // Run Simulink Model
    MX_Gtwy_Control_step();

    //Pullup control
    hw_dout_SetValue(ENG_OIL_PRESS_PUP_DOUT, outputSelect_EOP);
    hw_dout_SetValue(HYD_OIL_TEMP_PUP_DOUT, outputSelect_HOT);
    hw_dout_SetValue(TRAVEL_LEVER_PUP_DOUT, 0);
    hw_dout_SetValue(LOAD_SENSE_PUP_DOUT, 0);

    //HC Outputs
    hw_pwm_SetRatio16(FUEL_HOLD_HS_PWM, duty_FuelSec);
    hw_dout_SetValue(OFFSET_BASE_LS_DOUT, ls_OffsetBase);
    hw_pwm_SetRatio16(OFFSET_BASE_HS_PWM, hs_OffsetBase);
    hw_dout_SetValue(AUX_BASE_LS_DOUT, ls_AuxBase);
    hw_pwm_SetRatio16(AUX_BASE_HS_PWM, hs_AuxBase);
    hw_dout_SetValue(HYD_ENABLE_LS_DOUT, ls_HydEnable);
    hw_pwm_SetRatio16(HYD_ENABLE_HS_PWM, hs_HydEnable);
    hw_pwm_SetRatio16(TWO_SPEED_HS_PWM, duty_TwoSpeed);
    hw_dout_SetValue(OFFSET_ROD_LS_DOUT, ls_OffsetRod);
    hw_pwm_SetRatio16(OFFSET_ROD_HS_PWM, hs_OffsetRod);
    hw_dout_SetValue(AUX_ROD_LS_DOUT, ls_AuxRod);
    hw_pwm_SetRatio16(AUX_ROD_HS_PWM, hs_AuxRod);


    if(CONSTANT_DATA->HYD_BYPASS_FUNCTION != NON_FUNCTIONAL)
    {
      hw_dout_SetValue(HYD_BYPASS_LS_DOUT, ls_HydBypass);
      hw_pwm_SetRatio16(HYD_BYPASS_HS_PWM, hs_HydBypass);
    }

    if(CONSTANT_DATA->DUMP_VALVE_FUNCTION != NON_FUNCTIONAL)
    {
      hw_dout_SetValue(DUMP_VALVE_LS_DOUT, ls_DumpValve);
      hw_pwm_SetRatio16(DUMP_VALVE_HS_PWM, hs_DumpValve);
    }

    hw_dout_SetValue(SW_PWR_OUT_RLY_DOUT,dout_SwitchedPwr);
    hw_dout_SetValue(FUEL_PULL_RLY_DOUT, dout_FuelPri);


    if(CONSTANT_DATA->HVAC_RELAY_FUNCTION != NON_FUNCTIONAL)
    {
      hw_dout_SetValue(HVAC_RLY_DOUT, dout_HVACOutput);
    }

    hw_dout_SetValue(GLOW_PLUG_RLY_DOUT, dout_GlowPlug);
    hw_dout_SetValue(LIGHTS_DOUT, dout_Lights);
    hw_dout_SetValue(BUZZER_DOUT, dout_Buzzer);
    hw_dout_SetValue(STARTER_RLY_DOUT, dout_Starter);
    hw_dout_SetValue(HYD_EXCHANGE_DOUT, dout_HydExchange);

    if(CONSTANT_DATA->PBVALVE_FUNCTION != NON_FUNCTIONAL)
    {
      hw_dout_SetValue(PBVALVE_RLY_DOUT, dout_PBValve);
    }

    if(CONSTANT_DATA->SECOND_AUX_FUNCTION != NON_FUNCTIONAL
    || CONSTANT_DATA->EMEA_CONTROLS_OPTION_A != NON_FUNCTIONAL
    || CONSTANT_DATA->EMEA_CONTROLS_OPTION_C != NON_FUNCTIONAL)
    {
      hw_dout_SetValue(DIVERTER_LS_DOUT, ls_Diverter);
      hw_pwm_SetRatio16(DIVERTER_HS_PWM, hs_Diverter);
    }
    
    
    
    if((status_SrvcClockDisplay == 0) && (state_InfoSecondary == DISPLAY_SERVICE_CLOCK_ALARM))
    {
      if(state_Buzzer == BEEP_NONE)
      {
        state_Buzzer = DOUBLE_MEDIUM_BEEP;
      }
    }
    ap_bservice_CAN04_update();
    updateErrorList();

    ap_gateway_update();
    ap_can_update();
    
    CANOpenUpdate(); //Max3363
    CANStdUpdate(); //Max3363
    
    // checkKeylessStale();

    // Check hourmeter timer
    if(hourMeterUpdateTimer == 0)
    {
      // has 6 minute timer expired
      if(eeMode == EE_IDLE)
      {
        eeMode  = EE_HM_UPDATE;
        eeState = EE_HM_WRITE_INIT;
      }

      hourMeterUpdateTimer = RELOAD_6_MIN;
    }
    else if (jobClockUpdateTimer == 0)
    {
      if(eeMode == EE_IDLE && flag_InitEERead)
      {
        eeMode  = EE_MIRROR_UPDATE;
        eeState = EE_MIRROR_WRITE_INIT;
        jobClockUpdateTimer = RELOAD_6_MIN;
      }
    }
    else if (jobClockLHPUpdateTimer[0] == 0)
    {
      if(eeMode == EE_IDLE && flag_InitEERead)
      {
        eeMode  = EE_MIRROR_UPDATE;
        eeState = EE_MIRROR_WRITE_INIT;
        jobClockLHPUpdateTimer[0] = RELOAD_6_MIN;
      }
    }
    else if (jobClockLHPUpdateTimer[1] == 0)
    {
      if(eeMode == EE_IDLE && flag_InitEERead)
      {
        eeMode  = EE_MIRROR_UPDATE;
        eeState = EE_MIRROR_WRITE_INIT;
        jobClockLHPUpdateTimer[1] = RELOAD_6_MIN;
      }
    }
    else if (idleClockUpdateTimer == 0)
    {
      if(eeMode == EE_IDLE && flag_InitEERead)
      {
        UpdateEEVariables(NOW);
        //eeMode  = EE_MIRROR_UPDATE;
        //eeState = EE_MIRROR_WRITE_INIT;
        idleClockUpdateTimer = RELOAD_6_MIN;
      }
    }
    else if ((eeMode == EE_IDLE) && (eeTimeToUpdateMirror) && flag_InitEERead)
    {
      eeUpdate++;
      eeMode  = EE_MIRROR_UPDATE;
      eeState = EE_MIRROR_WRITE_INIT;
      eeTimeToUpdateMirror = FALSE;
    }

    uint16_t currentClock = hw_clock_S();
    uint16_t currentClockms = hw_clock_mS();

    // 20ms loop ******************************************************************

    if ((uint16_t)(currentClockms - previousClock20ms) >= 20u)
    {
      previousClock20ms += 20;
    }

    // 50ms loop ******************************************************************

    if ((uint16_t)(currentClockms - previousClock50ms) >= 50u)
    {
      previousClock50ms += 50;

      if(state_System == SYS_INIT)
      {
        state_System = SYS_NORMAL;
        state_Buzzer = SINGLE_MEDIUM_BEEP;
      }
    }

    // 100ms loop *****************************************************************
    if ((uint16_t)(currentClockms - previousClock100ms) >= 100u)
    {
      previousClock100ms += 100;

      powerUp();
      powerDown();

      ErrorQueueTimerUpdate();

      UpdateServiceClock();

      if((eeMirror.deluxe_G5) && (CONSTANT_DATA->DELUXE_GEN5_FUNCTION != NON_FUNCTIONAL))
      {
        if(state_DeluxeG5 == INACTIVE)
        {
          //Because we have the flag set we should not be inactive but set it to normal and reset the counter.
          state_DeluxeG5 = NORMAL;
          rx_DeluxeStatus.msg_age_mS = 0;
        }
        else if((state_Engine == ENGINE_CRANKING) || (state_System != SYS_NORMAL))
        {
          // If engine is cranking or system state is not normal set the message age to zero as panel may drop out.
          rx_DeluxeStatus.msg_age_mS = 0;
        }
        else if(rx_DeluxeStatus.msg_age_mS < CONSTANT_DATA->DELUXE_PANEL_DEBOUNCE_MISSING)
        {
          state_DeluxeG5 = NORMAL;
          Deluxe_Data_Update();
          VerifyNewPasswordG5();
        }
        else if((rx_DeluxeStatus.msg_age_mS >= CONSTANT_DATA->DELUXE_PANEL_DEBOUNCE_MISSING) &&
                (state_System == SYS_NORMAL) && (state_Engine != ENGINE_CRANKING) && (!flag_DeluxeProg))
        {
          state_DeluxeG5 = NO_COMMUNICATION;
          ddpSwitchStatus.data.inWarningPage = 0;  //Can get stuck on one error code if in deluxe warning screen when comm lost
        }
      }
      else
      {
        state_DeluxeG5 = INACTIVE;
      }

      // Reset the clock one time via button per power cycle.
      if((!set_ServiceClock) && (state_InfoPrimary == DISPLAY_SERVICE_CLOCK_RESET))
      {
        set_ServiceClock = TRUE;
        SetServiceClock();
      }

      if((eeMirror.deluxe_G5) && (CONSTANT_DATA->DELUXE_GEN5_FUNCTION != NON_FUNCTIONAL))
      {
        if(ddpSwitchStatus.data.inWarningPage)
        {
          UpdateLCDErrorCodes();
        }

        if(flag_SendWarningHistory)
        {
          SendWarningHistory();
          flag_SendDeluxeWarning = FALSE; //Do not send out regular warning can create multiples.
        }

        if(flag_SendDeluxeWarning)
        {
          SendDeluxeWarning();
          flag_SendDeluxeWarning = FALSE;
        }
      }
    }
    // 200ms loop *****************************************************************
    if ((uint16_t)(currentClockms - previousClock200ms) >= 200u)
    {
      previousClock200ms += 200;
    }

    // 500ms loop *****************************************************************
    if ((uint16_t)(currentClockms - previousClock500ms) >= 500u)
    {
      previousClock500ms += 500;
    }

    // 1s loop *****************************************************************
    if ((uint16_t)(currentClockms - previousClock1s) >= 1000u)
    {
      // Reset service clock through DV table
      // To set it properly, you should call DV_SET_SERVICE_CLOCK to set the hour meter
      // do enable service clock to activate it, slightly different from the actual dv
      // table command but I think it may be better for this instance.  
      switch(reset_ServiceClock)
      {
        case DV_ENABLE_SERVICE_CLOCK:
          
          eeMirror.serviceClockLock = SERVICE_CLOCK_LOCK_BIT;
          
          UpdateEEVariables(NOW);
          
          reset_ServiceClock = 0;
        
        break;
        
        case DV_SET_SERVICE_CLOCK:
        
          eeMirror.serviceClockExpired = FALSE;
          
          if(newHour1 != 0)
          {
            eeMirror.serviceClockLength = (uint32_t)newHour1 * HOUR_METER_TO_HOUR_FCT;
          }
          
          eeMirror.serviceClockResetTime = actualHourMeter;      
        
          UpdateEEVariables(NOW);
          
          QueueServiceDiag((uint16_t)(eeMirror.serviceClockResetTime/HOUR_METER_TO_HOUR_FCT), (uint16_t)(eeMirror.serviceClockLength/HOUR_METER_TO_HOUR_FCT), SERVICE_ANALYZER, (uint8_t)(serviceType), 250);
        
          reset_ServiceClock = 0;
          newHour1 = 0;
        break;
        
        case DV_DISABLE_SERVICE_CLOCK:
          eeMirror.serviceClockLock = FALSE;
          
          UpdateEEVariables(NOW);
          
          reset_ServiceClock = 0;
        break;
        
        default:
          reset_ServiceClock = 0;
        break;
      }
#ifdef HCS12_BSP_EMU //if M4 compile this      
      if(CONSTANT_DATA->DELUXE_GEN5_5_FUNCTION != NON_FUNCTIONAL && auth_DeluxeG55 == AUTHENTICATED)
      {
        RequestG55Passwords();
      }
#endif
      previousClock1s += 1000;
    }

    // 2s loop *****************************************************************
    if ((uint16_t)(currentClockms - previousClock2s) >= 2000u)
    {
      previousClock2s += 2000;

      // after 500 ms clear Deluxe G5 flag in case we had a restart during init stage we can resend
      if((state_System == SYS_NORMAL) && (dlxMode == DLX_STARTUP_DONE))
      {
        flag_PasswordSent = FALSE;
        dlxMode = DLX_STARTUP_IDLE;
        msg_Counter = 0;
      }
    }

    // 5 sec loop *****************************************************************
    if ((uint16_t)(currentClock - previousClock5s) >= 5u)
    {
      previousClock5s += 5;

      UpdateHourMeter();
      UpdateUserJobClock();
      UpdateLHPJobClocks();
      UpdateIdleTime();

      // Test console to see that we have seen both the up and down inputs.
      #define CONSOLE_UP_MASK 0x08
      #define CONSOLE_DN_MASK 0X10


      //If console is up, clear bit
      if((eeMirror.consoleTest & CONSOLE_UP_MASK) && (state_Console == INACTIVE) && (state_System == SYS_NORMAL))
      {
         eeMirror.consoleTest &= ~(uint8_t)CONSOLE_UP_MASK;
         UpdateEEVariables(NOW);
      }

      if((eeMirror.consoleTest & CONSOLE_DN_MASK) && (state_Console == ACTIVE) && (state_System == SYS_NORMAL))
      {
         eeMirror.consoleTest &= ~(uint8_t)CONSOLE_DN_MASK;
         UpdateEEVariables(NOW);
      }

      if(eeMirror.consoleTest & (CONSOLE_UP_MASK | CONSOLE_DN_MASK))
      {
        state_ConsoleTest = FAILURE;
      }
      else
      {
        state_ConsoleTest = FALSE;
      }

      if((CONSTANT_DATA->ECU_FUNCTION == ECU_J1939) && (state_CommECU == NORMAL) && (state_System == SYS_NORMAL)
         && ((state_DeluxeG5 == NORMAL) || (CONSTANT_DATA->DELUXE_GEN5_5_FUNCTION != NON_FUNCTIONAL)))
      {
        // Request fuel
        Send_Request_Message(((uint16_t)(LFC_PF << 8) + LFC_PS), SA_ECU, HWC_CAN4);
      }
    }
  }
}

