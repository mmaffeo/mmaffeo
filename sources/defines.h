#ifndef defines_h
#define defines_h

#define INACTIVE            0
#define ACTIVE              1
#define ERROR_ON            2
#define ERROR_OFF           3
#define NO_COMMUNICATION    4
#define IN_ERROR            4
#define SHORT_TO_BATTERY    5
#define SHORT_TO_GROUND     6
#define OPEN_CIRCUIT        7
#define NORMAL              8
#define LOW                 9
#define HIGH                10
#define EXTREMELY_HIGH      11
#define COLD                12
#define NO_SIGNAL           13
#define EXTREMELY_LOW       14
#define SHUTDOWN            15
#define NOT_CONNECTED       16
#define PLUGGED             17
#define OUT_OF_RANGE        18
#define OORH                21
#define OORL                22
#define NOT_PROGRAMMED      23
#define NOT_CALIBRATED      23
#define NOT_IN_NEUTRAL      24
#define UNRESPONSIVE        25
#define PRE_SHUTDOWN        26
#define FAILURE             28
#define FAULT               30
#define OPEN_STG            31
#define OVERCURRENT         32
#define INVALID_DATA        34
#define EVENT               36
#define CHANGED             39
#define MULTIPLE            48


#define NEEDS_REPROGRAMMING 72
#define OPEN                74
#define STATE_OPEN          74
#define SOFTWARE_UPDATED    97
#define IN_CAL_MODE         99

//Pot States
#define NEUTRAL           8
#define BASE_ACTIVE       253
#define ROD_ACTIVE        254

//Detent_States
#define NO_DETENT         0
#define BASE_DETENT       1
#define ROD_DETENT        2
#define ERR_DETENT        3

//Aux Release States


//Autoidle states
//#define IDLE              0
#define THROTTLE          0xFFFF

//Throttle Types
#define ACTUATOR          1
#define HYDRAULIC         2
#define ECU               3
#define CAN_ACTUATOR      4

#define PHOENIX           1
#define GATEWAY           2
//#define SIRIUS2           3

typedef enum 
{
    AUX_PHOENIX_K2 = 0,
    AUX_EMEA_CONTROLS,
    AUX_SIRIUS2 = 3,
    AUX_NON_FUNCTIONAL = 255,
}aux_config_t;

typedef enum 
{
    AUX_FLOW_INACTIVE = 0,
    AUX_FLOW_LOW,
    AUX_FLOW_MEDIUM,
    AUX_FLOW_STANDARD,
    AUX_FLOW_HIGH, //Sirius 2 power beyond
    AUX_RELEASE_WAIT =           0x10,
    AUX_RELEASE_ACK =            0x20,
    AUX_RELEASE_IN_PROGRESS =    0x21,
    AUX_RELEASE_CONFIRM =        0x22,
}aux_flow_t;



typedef enum left_control_mode 
{
  MODE_LEFT_NONE,
  MODE_LEFT_AUX1,
  MODE_LEFT_AUX2,
  MODE_LEFT_AUX4,
  MODE_LEFT_OFFSET
}left_control_mode_t;

typedef enum right_control_mode 
{
  MODE_RIGHT_NONE,
  MODE_RIGHT_AUX1,
  MODE_RIGHT_AUX2,
  MODE_RIGHT_AUX4,
  MODE_RIGHT_OFFSET
}right_control_mode_t;


typedef enum offset_select_sw 
{
  OFFSET_SELECT_LEFT,
  OFFSET_SELECT_RIGHT,
}offset_select_sw_t;

typedef enum ee_control_mode 
{
  EE_NA_NA,
  EE_LT_OF_NA,
  EE_LT_OF_A1,
  EE_LT_OF_A4,
  EE_LT_A2_A1,
  EE_LT_A2_A4,
  EE_RT_NA_OF,
  EE_RT_A4_OF,
  EE_RT_A4_A1,
  EE_RT_A2_A1,
}ee_control_mode_t;

//Aux Config
//#define AUX1              1
//#define AUX2              2
//#define AUX3              3
//#define AUX4              4

#define REF_8V            1
#define REF_5V            2


#define ENGINE_INITIALIZE   0
#define ENGINE_NOT_RUNNING  1
#define ENGINE_CRANKING     2
#define ENGINE_RUNNING      3
#define ENGINE_OFF          4

#define RESET               2
#define OVERRIDE            3
#define READY               2
#define READY_OVERRIDE      4
#define NOT_READY           5
#define ERROR               0xFE
#define NOT_AVAILABLE       0xFF

#define SWITCH_INPUT        1
#define SENDER              0

#define ERROR_FLASH         0x02
#define DONT_CARE           0x03
#define UNLIMITED           65535
#define NON_FUNCTIONAL      255

#define FULL_ON             65535  //fixdt_0_16_16

#define WORD_UNAVAIL        0xFFFF
#define WORD_ERROR          0xFFFE

#define DISABLED      0
#define ENABLED       1

#define SEVERITY_INFO           0
#define SEVERITY_WARNING        3
#define SEVERITY_CRITICAL       6
#define SEVERITY_SHUTDOWN       7


enum display_states
{
  DISPLAY_ENGINE_HOURS,
  DISPLAY_GLOW_PLUGS,
  DISPLAY_ENGINE_RPM,
  DISPLAY_BATTERY_VOLTAGE,
  DISPLAY_SERVICE_CLOCK,
  DISPLAY_ERROR_CODES,
  DISPLAY_JOB_CLOCK_1,
  DISPLAY_JOB_CLOCK_2,
  DISPLAY_GROUND_SPEED,
  DISPLAY_TIME_OF_DAY,   
  DISPLAY_DOOR_STATUS,   //10
  DISPLAY_SERVICE_CLOCK_ALARM,
  DISPLAY_SHUTDOWN,
  DISPLAY_SERVICE_CLOCK_RESET,
  DISPLAY_VERSION,
  DISPLAY_CODE,
  DISPLAY_ERROR,
  DISPLAY_DELUXE_ERROR,
  DISPLAY_DV_MODE,
  DISPLAY_ASTERISK,   
  DISPLAY_OPTIONS,  //20
  DISPLAY_METRIC,
  DISPLAY_ENGLISH,
  DISPLAY_SAVED,
  DISPLAY_OWNER1,
  DISPLAY_OWNER2,
  DISPLAY_EOP,
  DISPLAY_HCP,
  DISPLAY_ECT,         
  DISPLAY_HOT,       
  DISPLAY_HOLD,  //30
  DISPLAY_DONE,
  DISPLAY_NONE,
  DISPLAY_PRESS,
  DISPLAY_AUX,
  DISPLAY_COLD,
  DISPLAY_FLASH_COLD,
  DISPLAY_CAN_THROTTLE_DIAG,
  DISPLAY_PRIMARY_INACTIVE,
  DISPLAY_OWNER,  
  DISPLAY_USER1,  //40
  DISPLAY_USER2,
  DISPLAY_SECOND_AUX,
  DISPLAY_OFFSET,
  DISPLAY_EMEA_CONTROLS

};

enum system_states
{
  SYS_INIT,
  SYS_NORMAL,
  SYS_DV,
  SYS_LIMITED,
  SYS_POWER_DOWN,
  SYS_PHONE_LIMITED
};



enum functions
{
  NO_FUNCTION,
  FN_AIR_FILTER = 1,
  FN_IMPLEMENT_FILTER,
  FN_BATTERY_VOLTAGE,
  FN_ENGINE_OIL_PRESSURE,
  //FN_HYDRAULIC_CHARGE_PRESSURE,
  FN_ENGINE_SPEED = 6,
  FN_HYDRAULIC_OIL_TEMPERATURE,
  FN_ENGINE_COOLANT_TEMPERATURE,
  FN_FUEL_LEVEL,
  //FN_HYDRAULIC_CHARGE_FILTER,
  FN_CONSOLE_SENSOR = 11,
  FN_FUEL_SECONDARY_OUTPUT = 13,
  FN_FUEL_PRIMARY_OUTPUT,
  FN_HYD_BYPASS = 16,
  FN_HYD_ENABLE,
  FN_PBVALVE_OUTPUT,
  FN_PBVALVE_RELAY,
  FN_TWO_SPEED = 20,
  FN_GLOW_PLUG_OUTPUT,
  FN_STARTER_OUTPUT,
  FN_STARTER_RELAY,
  FN_FUEL_PRIMARY_RELAY,
  FN_LOAD_SENSE,
  FN_GLOW_PLUG_RELAY,
  FN_THROTTLE_PRIMARY,
  FN_DIVERTER,
  //FN_SECONDAUX_RELEASE = 29,
  FN_CONTROLLER_MEMORY = 30,
  FN_INTERRUPTED_POWER,
  FN_THROTTLE_CONTROLLER,
  FN_DELUXE_PANEL_G5,
  FN_DISPLAY_CONTROLLER,
  FN_HYD_EXCHANGE =37,
  FN_JOG_SHUTTLE = 39,
  FN_HP_MATCH = 40,
  FN_ALTERNATOR_VOLTAGE,
  FN_KEYLESS_ENTRY,
  FN_KEYLESS_PANEL = 43,
  FN_SECONDARY,
  //FN_WIF,
  FN_SENSOR_SUPPLY_2 = 46,
  FN_SENSOR_SUPPLY_1,
  FN_FRONT_LIGHT_RELAY,
  FN_FRONT_LIGHT_OUTPUT = 50,
  FN_OFFSET_BASE = 52,
  FN_OFFSET_ROD,
  FN_OFFSET_CONTROL,
  FN_AUX_BASE,
  FN_AUX_ROD,
  FN_AUX_CONTROL,
  FN_FUEL_TEMP,
  FN_AUX2_FLOW_CONTROL,
  FN_LEFT_CONTROL,
  FN_RIGHT_CONTROL,
  FN_LOAD_MOMENT = 62,
  FN_SWITCHED_POWER_RELAY = 64,
  FN_ECU_OUTPUT,
  FN_ECU_FUNCTION,
  FN_HVAC_OUTPUT,
  FN_DUMP_VALVE = 69,
  FN_SWITCHED_POWER_OUTPUT,
  FN_MAIN_CONTROLLER = 74,
  FN_STANDARD_DISPLAY_PANEL = 76,
  FN_KEY_SWITCH,
  FN_HOURMETER,
  //FN_DPF = 85,
  FN_ENGINE_SPEED_DERATE = 86,
  //FN_TORQUE_DERATE,
  FN_TURBO_PRIME = 97,

  MAX_NUMBER_OF_FUNCTIONS
};

enum eventLocations
{
 // static event location - MAX of 40 locations
 LOC_AIR_FILTER_PLUGGED,
 LOC_IMPLEMENT_FILTER_PLUGGED,
 LOC_EOP_EXTREMELY_LOW,
 LOC_EOP_LOW,
 LOC_EOP_IN_SHUTDOWN,
 LOC_FUEL_TEMP_EXTREMELY_HIGH,
 LOC_FUEL_TEMP_HIGH,
 LOC_FUEL_TEMP_IN_SHUTDOWN,
 LOC_ENGINE_SPEED_EXTREMELY_HIGH,
 LOC_ENGINE_SPEED_HIGH,
 LOC_ENGINE_SPEED_IN_SHUTDOWN,
 LOC_HOT_EXTREMELY_HIGH,
 LOC_HOT_HIGH,
 LOC_HOT_IN_SHUTDOWN,
 LOC_ECT_EXTREMELY_HIGH,
 LOC_ECT_HIGH,
 LOC_ECT_IN_SHUTDOWN,
 LOC_STARTER_RELAY_ERROR_ON,
 LOC_WATCHDOG_FAILURE,
 LOC_RECOVERY_FAILURE,
 LOC_STARTER_OUTPUT_ERROR_ON,
 LOC_HOURMETER,

};

#define BEEP_NONE           0xFF  //Don't care, there is no active beep
#define NO_BEEP             0x00  //Do not allow beep
#define SINGLE_SHORT_BEEP   0x10
#define DOUBLE_SHORT_BEEP   0x20
#define TRIPLE_SHORT_BEEP   0x30
#define QUAD_SHORT_BEEP     0x40
#define SINGLE_MEDIUM_BEEP  0x13
#define SINGLE_LONG_BEEP    0x1F
#define CONTINUOUS_BEEP     0x01
#define DOUBLE_MEDIUM_BEEP  0x22
#define DC_GRADE_BEEP       0x81
#define DC_WARNING_BEEP     0x82
#define DC_BELOW_GRADE_BEEP 0x83

#define ENGLISH 0
#define METRIC  1


enum pwdStates
{
  UNLOCK,
  LOCKED,
  CHANGE,
  ENTER_OWNER1,
  ENTER_OWNER2,
  PASS,
  NEW,
  FAIL,
  ENTER_PWD,
};

#define PW_MASTER         10 //uint8
#define PW_OWNER          0 //uint8
#define PW_USER1          1 //uint8
#define PW_USER2          2 //uint8

#define KS_NOTHING  0
#define KS_LOCK     1
#define KS_UNLOCK   2
#define KS_CHANGE   3
#define KS_UNLOCK_MACHINE 4
#define KS_LOCK_MACHINE   5

#define KEYPAD_MASK_1       0x03
#define KEYPAD_MASK_2       0x0C
#define KEYPAD_MASK_3       0x30
#define KEYPAD_MASK_4       0xC0
#define KEYPAD_MASK_5       0x03
#define KEYPAD_MASK_6       0x0C
#define KEYPAD_MASK_7       0x30
#define KEYPAD_MASK_8       0xC0
#define KEYPAD_MASK_9       0x03
#define KEYPAD_MASK_0       0x0C
#define KEYPAD_LOCK_MASK    0x30
#define KEYPAD_UNLOCK_MASK  0xC0

#define KEYPAD_PRESSED_1       0x01
#define KEYPAD_PRESSED_2       0x04
#define KEYPAD_PRESSED_3       0x10
#define KEYPAD_PRESSED_4       0x40
#define KEYPAD_PRESSED_5       0x01
#define KEYPAD_PRESSED_6       0x04
#define KEYPAD_PRESSED_7       0x10
#define KEYPAD_PRESSED_8       0x40
#define KEYPAD_PRESSED_9       0x01
#define KEYPAD_PRESSED_0       0x04
#define KEYPAD_LOCK_PRESSED    0x10
#define KEYPAD_UNLOCK_PRESSED  0x40



#define ASCII_0     0x30
#define ASCII_1     0x31
#define ASCII_2     0x32
#define ASCII_3     0x33
#define ASCII_4     0x34
#define ASCII_5     0x35
#define ASCII_6     0x36
#define ASCII_7     0x37
#define ASCII_8     0x38
#define ASCII_9     0x39

#define LIGHT_BUTTON_MASK       0x03
#define LIGHT_BUTTON_PRESS      0x01

#define AUTO_IDLE_BUTTON_MASK   0x0C
#define AUTO_IDLE_BUTTON_PRESS  0x04

#define AUXILIARY_BUTTON_MASK   0x30
#define AUXILIARY_BUTTON_PRESS  0x10

#define INFO_BUTTON_MASK        0xC0
#define INFO_BUTTON_PRESS       0x40

#define LEFT_BUTTON_MASK   0x0C
#define LEFT_BUTTON_PRESS  0x04

#define RIGHT_BUTTON_MASK   0x30
#define RIGHT_BUTTON_PRESS  0x10

#define JOG_BUTTON2_MASK        0x0C
#define JOG_BUTTON3_MASK        0x30
#define JOG_BUTTON4_MASK        0xC0
#define JOG_BUTTON5_MASK        0x03
#define JOG_BUTTON6_MASK        0x0C
#define JOG_LIGHTS_BUTTON_MASK  JOG_BUTTON2_MASK
#define JOG_AUX_BUTTON_MASK     JOG_BUTTON5_MASK

#define MAX_PWD_CHAR  5


#define ACTIVE_MODE_ONE       19
#define PRESENT 1

enum passwordVerification
{
 SEND_VERIFIED_PASSWORD = 1
};

enum SERVICE_CLOCK_RESET
{
  RESET_UKNOWN=0,
  SERVICE_ANALYZER,
  MANUAL
};



#define  SERVICE_OFF            0x01
#define  SERVICE_ON             0x02
#define  SERVICE_RESET          0x04
#define  SERVICE_ALARM          0x08
#define  SERVICE_NEW_LEVEL      0x10
#define  SERVICE_FACTORY_RESET  0x20

#define USER_2SPEED_LOCK_TOGGLE 0x01
#define USER_HF_LOCK_TOGGLE     0x02
#define USER_AFTERHOUR_TOGGLE   0x04
#define USER_JOBCLOCK_TOGGLE    0x08

#define DEVICE_ERROR_ID         0x4D
#define GATEWAY_ERROR_ID        0x4D
#define ATTACHMENT_ERROR_ID     0x41
#define THROTTLE_ERROR_ID       0x45
#define ENGINE_ERROR_ID         0x45
#define LHP_ERROR_ID            0x4C
#define SEC_ERROR_ID            0x48
#define SERVICE_TOOL_ERROR_ID   0x54

#define TYPE_BOBCAT   0
#define TYPE_SPN      1

#define ECU_J1939     0

#define STARTER_INHIBITED  12

//DM1 Message info
#define PROTECT_LAMP_STATUS_MASK        0x0003
#define PROTECT_LAMP_STATUS_ACTIVE      0x0001
#define AMBER_LAMP_STATUS_MASK          0x000C
#define AMBER_LAMP_STATUS_ACTIVE        0x0004
#define RED_STOP_LAMP_STATUS_MASK       0x0030
#define RED_STOP_LAMP_STATUS_ACTIVE     0x0010
#define MALFUNCTION_LAMP_STATUS_MASK    0x00C0
#define MALFUNCTION_LAMP_STATUS_ACTIVE  0x0040

#define PROTECT_LAMP_FLASH_MASK         0x0300
#define PROTECT_LAMP_FLASH_ACTIVE       0x0100
#define AMBER_LAMP_FLASH_MASK           0x0C00
#define RED_STOP_LAMP_FLASH_MASK        0x3000
#define MALFUNCTION_LAMP_FLASH_MASK     0xC000

//Load Moment
#define LOAD_MOMENT_ENABLE_NEW           0
#define LOAD_MOMENT_ENABLE_OLD           1

//Keyless Entry
#define KE_PASSWORD_SIZE                PASSWORD_SIZE
#define NUMBER_OF_KE_PASSWORDS          NUMBER_TOTAL_PASSWORDS

#define KE_UNKNOWN                      0
#define KE_FAIL                         1
#define KE_PASS                         2
#define KE_LOCK                         3
#define KE_UNLOCK                       4

#define KE_PWR_INACTIVE                 0
#define KE_PWR_ACTIVE                   1
#define KE_PWR_TIMEOUT                  2

#define TURBO_PRIME_ACTIVE             79

enum Deluxe_G55_State
{
  DELUXE_G55_INIT = 0,
  DELUXE_G55_FUNCTION_LOCKED,
  DELUXE_G55_FUNCTION_UNLOCKED,
  DELUXE_G55_ENTER_SUSPEND = 5,
  DELUXE_G55_ENTER_POWER_DOWN,
  DELUXE_G55_UNDEFINED 
};

#define NOT_AUTHENTICATED       0
#define AUTHENTICATED           1
#define AUTHENTICATION_NA       3

enum gateway_direction
{
  DIRECTION_OFF,
  DIRECTION_1_TO_2,
  DIRECTION_2_TO_1,
  DIRECTION_BOTH
};


typedef enum MAIN_screenNum {
                MAIN_nSplashScreen,                                             //  0
                MAIN_nPanelLock,                                                //  1
                MAIN_nNoCommunication,                                          //  2
                MAIN_nGauges,                                                   //  3
                MAIN_nInvalidPassword,                                          //  4
                MAIN_nOwnerPassword,                                            //  5
                MAIN_nSecurity,                                                 //  6
                MAIN_nInvalidOwnerPassword,                                     //  7
                MAIN_nNewOwnerPassword,                                         //  8
                MAIN_nReEnterOwnerPassword,                                     //  9
                MAIN_nOwnerPasswordChanged,                                     // 10
                MAIN_nSelectOperator,                                           // 11
                MAIN_nOperatorSettings,                                         // 12
                MAIN_nChangeOperatorName,                                       // 13
                MAIN_nChangeOperatorPassword,                                   // 14
                MAIN_nOperatorPasswordConfirmMessage,                           // 15
                MAIN_nShowResetOperatorJob,                                     // 16
                MAIN_nResetJobClock,                                            // 17
                MAIN_nHighFlow,                                                 // 18
                MAIN_nTwoSpeedLock,                                             // 19
                MAIN_nServiceIntervals = 21,                                    //*21
                MAIN_nDisplayOptions,                                           // 22
                MAIN_nClocks,                                                   // 23
                MAIN_nLanguages = 25,                                           //*25
                MAIN_nTime,                                                     // 26
                MAIN_nJobClock,                                                 // 27
                MAIN_nAlarm,                                                    // 28
                MAIN_nDate,                                                     // 29
                MAIN_nAlarmSettings,                                            // 30
                MAIN_nAlarmTime,                                                // 31
                MAIN_nSoundAlarm,                                               // 32
                MAIN_nAttachments,                                              // 33
                MAIN_nVitals,                                                   // 34
                MAIN_nEnterOwnerPassword,                                       // 35
                MAIN_nWarnings = 37,                                            //*37
                MAIN_nClearAllClocks,                                           // 38
                MAIN_nWaitLockAnswer,                                           // 39
                MAIN_nRequestDowngrade = 41,                                    //*41
                MAIN_nAttachmentHint,                                           // 42
                MAIN_nAttachmentDesc,                                           // 43
                MAIN_nHistory = 60,                                             //*60
                MAIN_nIndServiceCode,                                           // 61
                MAIN_nRemoveUser,                                               // 62
                MAIN_nAttachmentSpecFeature,                                    // 63
                MAIN_nAttachmentClock,                                          // 64
                MAIN_nScreenColor,                                              // 65
                MAIN_nMachineSettings,                                          // 66
                MAIN_nDisplaySettings,                                          // 67
                MAIN_nMachineHistory,                                           // 68
                MAIN_nUserLoginInfo,                                            // 69
                MAIN_nUserJobStats,                                             // 70
                MAIN_nAutoIdle,                                                 // 71
                MAIN_nAttachmentSlope,                                          // 72
                MAIN_nAttachmentSonicOffset,                                    // 73
                MAIN_nDigDepthTargetZones,                                      // 74
                MAIN_nDigDepthVarEdit,                                          // 75
                MAIN_nMachinePerformance,                                       // 76
                MAIN_nHydraulicResponse,                                        // 77
                MAIN_nAuxRelease,                                               // 78
                MAIN_nDigDepthSettings,                                         // 79
                MAIN_nDigDepthTargetSelect,                                     // 80
                MAIN_nDigDepthAttachmentSelect,                                 // 81
                MAIN_nDigDepthCalibration,                                      // 82
                MAIN_nDigDepthBoomCalibration,                                  // 83
                MAIN_nDigDepthArmLength,                                        // 84
                MAIN_nDigDepthAttachmentSetup,                                  // 85
                MAIN_nDigDepthAttachmentName,                                   // 86
                MAIN_nDigDepthDefaults,                                         // 87
                MAIN_nDigDepthArmCalibration,                                   // 88
                MAIN_nDigDepthAttachmentCalibration,                            // 89
                MAIN_nAccessDenied = 99,                                        // 99
                MAIN_nMainClock,                                                // 100
                MAIN_nShutdown,                                                 // 101
                MAIN_nShutoff = 200,                                            // 200
                MAIN_nTestMode = 255                                            // 255
} MAIN_screenNum;

enum inverter_state     //uint8
{
  INVERTER_STOP,
  INVERTER_CONNECTED,
  INVERTER_OPERATIONAL,
  INVERTER_READY,
  INVERTER_RUN_FWD,
  INVERTER_RUN_REV
};

enum inverterCmd        // uint8_t
{
  CMD_INVERTER_GOTO_STOP,
  CMD_INVERTER_GOTO_OPERATIONAL,
  CMD_INVERTER_GOTO_READY,
  CMD_INVERTER_RUN_FWD,
  CMD_INVERTER_RUN_REV
};
//MATLAB_STOP_READING
#define MASTER_PWD    (&CONSTANT_DATA->MASTER_PWD_0)
#define OWNER_PWD     (&CONSTANT_DATA->OWNER_PWD_0)
#define DEALER_NAME   (&CONSTANT_DATA->DEALER_NAME_1)
#define DEALER_NUMBER (&CONSTANT_DATA->DEALER_NUMBER_1)
#define BOBCAT_SERIAL_NUMBER          (&CONSTANT_DATA->PIN_1_1)


#endif
