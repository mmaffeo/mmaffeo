%Script to load workspace with model parameters
%
% Name: ModelParameters_Example.m
%
% Project: 
%
% Copyright 2008 Bobcat Company as an unpublished work. 
% All Rights Reserved.
%
% The information contained herein is confidential property of Bobcat
% Company. The use, copying, transfer or disclosure of such information is
% prohibited except by express written agreement with Bobcat Company.
%	
% First written on 14 May 2008 by Al Liebel.
%
% Description:
%   Used to create parameters required by the model. 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Simulation parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Set sample times
A2D_Ts = 0.010;
Ts = 0.010;


FILTER_ENABLE = boolean(false);
Tsim = 0.005;  %.00005 if filters enabled, else 0.005
Tcont = 0.005; % 0 if filters are enabled, else 0.005

EE1 = uint16(0);
EE2 = logical(0);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Function Call Definitions
% Whenever the following defined signals are written to in Simulink or
% Stateflow, a function call will be made.  Function(signal value).
% A manually created 'HeaderFile' can then be used to translate this
% function to legacy code
% i.e. #define Function(signal value) (legacyFunction(value))
% Signal value need not be used
% i.e. #define Function() (legacyFunction())
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%function CreateFunction(Name, Function, HeaderFile)
Lift_Brakes = Bobcat.Signal;  CreateFunction( Lift_Brakes, 'Lift_Brakes', '..\functions.h');
Lift_FWD    = Bobcat.Signal;  CreateFunction( Lift_FWD   , 'Lift_FWD'   , '..\functions.h');
Lift_REV    = Bobcat.Signal;  CreateFunction( Lift_REV   , 'Lift_REV'   , '..\functions.h');
Lift_Off    = Bobcat.Signal;  CreateFunction( Lift_Off   , 'Lift_Off'   , '..\functions.h');
Tilt_Brakes = Bobcat.Signal;  CreateFunction( Tilt_Brakes, 'Tilt_Brakes', '..\functions.h');
Tilt_FWD    = Bobcat.Signal;  CreateFunction( Tilt_FWD   , 'Tilt_FWD'   , '..\functions.h');
Tilt_REV    = Bobcat.Signal;  CreateFunction( Tilt_REV   , 'Tilt_REV'   , '..\functions.h');
Tilt_Off    = Bobcat.Signal;  CreateFunction( Tilt_Off   , 'Tilt_Off'   , '..\functions.h');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Create Bus Objects
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%function CreateBusElement(Number, Name, Type, SampleTime)
%function CreateBus(Name, Type, SampleTime,elems)
elems = Simulink.BusElement;

CreateBusElement(1,       'Lift_Position',  'int16', Ts, elems);
CreateBusElement(2,       'Tilt_Position',  'int16', Ts, elems);
CreateBusElement(3,        'Lift_Command', 'uint16', Ts, elems);
CreateBusElement(4,        'Tilt_Command', 'uint16', Ts, elems);
CreateBusElement(5, 'Lift_Spool_Position', 'uint16', Ts, elems);
CreateBusElement(6, 'Tilt_Spool_Position', 'uint16', Ts, elems);

CreateBus('ACS_Inputs', elems); 

clear elems;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Defines
% Used to define constant parameters for the model which may also be used
% by legacy code.
% 'HeaderFile' will be automatically generated
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%function CreateDefine(Name, Value, StrCls, CustStrCls, HeaderFile)

% Logical Defines
MODULE_ID               = Bobcat.Parameter;  CreateDefine(MODULE_ID              ,     3, 'Define', 'ap_defines.h');

ON                      = Bobcat.Parameter;  CreateDefine(ON                     ,     1, 'Define', 'ap_defines.h');
OFF                     = Bobcat.Parameter;  CreateDefine(OFF                    ,     0, 'Define', 'ap_defines.h');


TRUE                    = Bobcat.Parameter;  CreateDefine(TRUE                   ,     1, 'Define', 'ap_defines.h');
FALSE                   = Bobcat.Parameter;  CreateDefine(FALSE                  ,     0, 'Define', 'ap_defines.h');

DOWN                    = Bobcat.Parameter;  CreateDefine(DOWN                   ,     1, 'Define', 'ap_defines.h');
UP                      = Bobcat.Parameter;  CreateDefine(UP                     ,     0, 'Define', 'ap_defines.h');

ACTIVE                  = Bobcat.Parameter;  CreateDefine(ACTIVE                 ,     1, 'Define', 'ap_defines.h');
INACTIVE                = Bobcat.Parameter;  CreateDefine(INACTIVE               ,     0, 'Define', 'ap_defines.h');


SMALL                   = Bobcat.Parameter;  CreateDefine(SMALL                  ,     0, 'Define', 'ap_defines.h');
MEDIUM                  = Bobcat.Parameter;  CreateDefine(MEDIUM                 ,     1, 'Define', 'ap_defines.h');


FUNCTIONAL              = Bobcat.Parameter;  CreateDefine(FUNCTIONAL             ,     0, 'Define', 'ap_defines.h');
ERROR_ON                = Bobcat.Parameter;  CreateDefine(ERROR_ON               ,     2, 'Define', 'ap_defines.h');
ERROR_OFF               = Bobcat.Parameter;  CreateDefine(ERROR_OFF              ,     3, 'Define', 'ap_defines.h');
IN_ERROR                = Bobcat.Parameter;  CreateDefine(IN_ERROR               ,     4, 'Define', 'ap_defines.h');
STB                     = Bobcat.Parameter;  CreateDefine(STB                    ,     5, 'Define', 'ap_defines.h');
STG                     = Bobcat.Parameter;  CreateDefine(STG                    ,     6, 'Define', 'ap_defines.h');
OPEN_CIRCUIT            = Bobcat.Parameter;  CreateDefine(OPEN_CIRCUIT           ,     7, 'Define', 'ap_defines.h');
NORMAL                  = Bobcat.Parameter;  CreateDefine(NORMAL                 ,     8, 'Define', 'ap_defines.h');
NEUTRAL                 = Bobcat.Parameter;  CreateDefine(NEUTRAL                ,     8, 'Define', 'ap_defines.h');
LOW                     = Bobcat.Parameter;  CreateDefine(LOW                    ,     9, 'Define', 'ap_defines.h');
HIGH                    = Bobcat.Parameter;  CreateDefine(HIGH                   ,    10, 'Define', 'ap_defines.h');
EXT_HIGH                = Bobcat.Parameter;  CreateDefine(EXT_HIGH               ,    11, 'Define', 'ap_defines.h');
COLD                    = Bobcat.Parameter;  CreateDefine(COLD                   ,    12, 'Define', 'ap_defines.h');
NO_SIGNAL               = Bobcat.Parameter;  CreateDefine(NO_SIGNAL              ,    13, 'Define', 'ap_defines.h');
EXT_LOW                 = Bobcat.Parameter;  CreateDefine(EXT_LOW                ,    14, 'Define', 'ap_defines.h');
IN_SHUTDOWN             = Bobcat.Parameter;  CreateDefine(IN_SHUTDOWN            ,    15, 'Define', 'ap_defines.h');
NOT_CONNECTED           = Bobcat.Parameter;  CreateDefine(NOT_CONNECTED          ,    16, 'Define', 'ap_defines.h');
PLUGGED                 = Bobcat.Parameter;  CreateDefine(PLUGGED                ,    17, 'Define', 'ap_defines.h');
OUT_OF_RANGE            = Bobcat.Parameter;  CreateDefine(OUT_OF_RANGE           ,    18, 'Define', 'ap_defines.h');
ACTIVE_MODE_ONE         = Bobcat.Parameter;  CreateDefine(ACTIVE_MODE_ONE        ,    19, 'Define', 'ap_defines.h');
ACTIVE_MODE_TWO         = Bobcat.Parameter;  CreateDefine(ACTIVE_MODE_TWO        ,    20, 'Define', 'ap_defines.h');
OORH                    = Bobcat.Parameter;  CreateDefine(OORH                   ,    21, 'Define', 'ap_defines.h');
OORL                    = Bobcat.Parameter;  CreateDefine(OORL                   ,    22, 'Define', 'ap_defines.h');
NOT_CALIBRATED          = Bobcat.Parameter;  CreateDefine(NOT_CALIBRATED         ,    23, 'Define', 'ap_defines.h');
BASE_ACTIVE             = Bobcat.Parameter;  CreateDefine(BASE_ACTIVE            ,    24, 'Define', 'ap_defines.h');
ROD_ACTIVE              = Bobcat.Parameter;  CreateDefine(ROD_ACTIVE             ,    25, 'Define', 'ap_defines.h');
FAILURE                 = Bobcat.Parameter;  CreateDefine(FAILURE                ,    28, 'Define', 'ap_defines.h');
NON_FUNCTIONAL          = Bobcat.Parameter;  CreateDefine(NON_FUNCTIONAL         ,   255, 'Define', 'ap_defines.h');
TEMP_INVALID            = Bobcat.Parameter;  CreateDefine(TEMP_INVALID           ,-32768, 'Define', 'ap_defines.h');


NO_DETENT               = Bobcat.Parameter;  CreateDefine(NO_DETENT              ,     0, 'Define', 'ap_defines.h');
BASE_DETENT             = Bobcat.Parameter;  CreateDefine(BASE_DETENT            ,     1, 'Define', 'ap_defines.h');
ROD_DETENT              = Bobcat.Parameter;  CreateDefine(ROD_DETENT             ,     2, 'Define', 'ap_defines.h');


NOT_RUNNING             = Bobcat.Parameter;  CreateDefine(NOT_RUNNING            ,     1, 'Define', 'ap_defines.h');
RUNNING                 = Bobcat.Parameter;  CreateDefine(RUNNING                ,     2, 'Define', 'ap_defines.h');
CRANKING                = Bobcat.Parameter;  CreateDefine(CRANKING               ,     3, 'Define', 'ap_defines.h');
MAY_BE_RUNNING          = Bobcat.Parameter;  CreateDefine(MAY_BE_RUNNING         ,     4, 'Define', 'ap_defines.h');


KEY_OR_ATTACH_RUN       = Bobcat.Parameter;  CreateDefine(KEY_OR_ATTACH_RUN      ,     0, 'Define', 'ap_defines.h');
AUX_HYD_BUTTON          = Bobcat.Parameter;  CreateDefine(AUX_HYD_BUTTON         ,     1, 'Define', 'ap_defines.h');
LIGHTS_BUTTON           = Bobcat.Parameter;  CreateDefine(LIGHTS_BUTTON          ,     2, 'Define', 'ap_defines.h');
HOURS_BUTTON            = Bobcat.Parameter;  CreateDefine(HOURS_BUTTON           ,     3, 'Define', 'ap_defines.h');
KEYLESS_ENTER_BUTTON    = Bobcat.Parameter;  CreateDefine(KEYLESS_ENTER_BUTTON   ,     4, 'Define', 'ap_defines.h');
KEYLESS_OTHER_BUTTON    = Bobcat.Parameter;  CreateDefine(KEYLESS_OTHER_BUTTON   ,     5, 'Define', 'ap_defines.h');


POWER_UP                = Bobcat.Parameter;  CreateDefine(POWER_UP               ,     0, 'Define', 'ap_defines.h');
POWER_DOWN              = Bobcat.Parameter;  CreateDefine(POWER_DOWN             ,     1, 'Define', 'ap_defines.h');
KEYLESS_GLOW            = Bobcat.Parameter;  CreateDefine(KEYLESS_GLOW           ,     2, 'Define', 'ap_defines.h');
AUX_VERSION             = Bobcat.Parameter;  CreateDefine(AUX_VERSION            ,     3, 'Define', 'ap_defines.h');
HOURS_LIMITED           = Bobcat.Parameter;  CreateDefine(HOURS_LIMITED          ,     4, 'Define', 'ap_defines.h');
LIGHTS_LIMITED          = Bobcat.Parameter;  CreateDefine(LIGHTS_LIMITED         ,     5, 'Define', 'ap_defines.h');
KEYLESS                 = Bobcat.Parameter;  CreateDefine(KEYLESS                ,     6, 'Define', 'ap_defines.h');
NORMAL_MODE             = Bobcat.Parameter;  CreateDefine(NORMAL_MODE            ,     7, 'Define', 'ap_defines.h');
COOLDOWN                = Bobcat.Parameter;  CreateDefine(COOLDOWN               ,     8, 'Define', 'ap_defines.h');
SHUTDOWN                = Bobcat.Parameter;  CreateDefine(SHUTDOWN               ,     9, 'Define', 'ap_defines.h');


STOP                    = Bobcat.Parameter;  CreateDefine(STOP                   ,     1, 'Define', 'ap_defines.h');
ENTER_CODE              = Bobcat.Parameter;  CreateDefine(ENTER_CODE             ,     2, 'Define', 'ap_defines.h');
CHANGE_PASSWORD         = Bobcat.Parameter;  CreateDefine(CHANGE_PASSWORD        ,     3, 'Define', 'ap_defines.h');
TOGGLE_LOCK             = Bobcat.Parameter;  CreateDefine(TOGGLE_LOCK            ,     4, 'Define', 'ap_defines.h');


GO_TO_NORMAL            = Bobcat.Parameter;  CreateDefine(GO_TO_NORMAL           ,     5, 'Define', 'ap_defines.h');
KEYLESS_POWERDOWN       = Bobcat.Parameter;  CreateDefine(KEYLESS_POWERDOWN      ,     6, 'Define', 'ap_defines.h');
LOCKDOWN                = Bobcat.Parameter;  CreateDefine(LOCKDOWN               ,     7, 'Define', 'ap_defines.h');
GO_TO_NORMAL_POST       = Bobcat.Parameter;  CreateDefine(GO_TO_NORMAL_POST      ,     8, 'Define', 'ap_defines.h');
LIGHTS_CHECK            = Bobcat.Parameter;  CreateDefine(LIGHTS_CHECK           ,     9, 'Define', 'ap_defines.h');


ONE_BEEP                = Bobcat.Parameter;  CreateDefine(ONE_BEEP               ,     2, 'Define', 'ap_defines.h');
TWO_BEEPS               = Bobcat.Parameter;  CreateDefine(TWO_BEEPS              ,     4, 'Define', 'ap_defines.h');
THREE_BEEPS             = Bobcat.Parameter;  CreateDefine(THREE_BEEPS            ,     8, 'Define', 'ap_defines.h');
ONE_SHORT_BEEP          = Bobcat.Parameter;  CreateDefine(ONE_SHORT_BEEP         ,    16, 'Define', 'ap_defines.h');


FLASHING                = Bobcat.Parameter;  CreateDefine(FLASHING               ,     2, 'Define', 'ap_defines.h');


BLANK                   = Bobcat.Parameter;  CreateDefine(BLANK                  ,     0, 'Define', 'ap_defines.h');
POST                    = Bobcat.Parameter;  CreateDefine(POST                   ,     1, 'Define', 'ap_defines.h');
CD_VERSION              = Bobcat.Parameter;  CreateDefine(CD_VERSION             ,     2, 'Define', 'ap_defines.h');
CODES                   = Bobcat.Parameter;  CreateDefine(CODES                  ,     3, 'Define', 'ap_defines.h');
GLOW                    = Bobcat.Parameter;  CreateDefine(GLOW                   ,     4, 'Define', 'ap_defines.h');
HOURS                   = Bobcat.Parameter;  CreateDefine(HOURS                  ,     5, 'Define', 'ap_defines.h');
JOB                     = Bobcat.Parameter;  CreateDefine(JOB                    ,     6, 'Define', 'ap_defines.h');
RPM                     = Bobcat.Parameter;  CreateDefine(RPM                    ,     7, 'Define', 'ap_defines.h');
SPEED_MPH               = Bobcat.Parameter;  CreateDefine(SPEED_MPH              ,     8, 'Define', 'ap_defines.h');
SPEED_KPH               = Bobcat.Parameter;  CreateDefine(SPEED_KPH              ,     9, 'Define', 'ap_defines.h');
LCD_OFF                 = Bobcat.Parameter;  CreateDefine(LCD_OFF                ,    10, 'Define', 'ap_defines.h');
AUTO                    = Bobcat.Parameter;  CreateDefine(AUTO                   ,    11, 'Define', 'ap_defines.h');
DONE                    = Bobcat.Parameter;  CreateDefine(DONE                   ,    12, 'Define', 'ap_defines.h');
CODE                    = Bobcat.Parameter;  CreateDefine(CODE                   ,    13, 'Define', 'ap_defines.h');
DIGIT1                  = Bobcat.Parameter;  CreateDefine(DIGIT1                 ,    14, 'Define', 'ap_defines.h');
DIGIT2                  = Bobcat.Parameter;  CreateDefine(DIGIT2                 ,    15, 'Define', 'ap_defines.h');
DIGIT3                  = Bobcat.Parameter;  CreateDefine(DIGIT3                 ,    16, 'Define', 'ap_defines.h');
DIGIT4                  = Bobcat.Parameter;  CreateDefine(DIGIT4                 ,    17, 'Define', 'ap_defines.h');
ERROR                   = Bobcat.Parameter;  CreateDefine(ERROR                  ,    18, 'Define', 'ap_defines.h');
LOCK                    = Bobcat.Parameter;  CreateDefine(LOCK                   ,    19, 'Define', 'ap_defines.h');
LOCKED                  = Bobcat.Parameter;  CreateDefine(LOCKED                 ,    20, 'Define', 'ap_defines.h');
UNLOCKED                = Bobcat.Parameter;  CreateDefine(UNLOCKED               ,    21, 'Define', 'ap_defines.h');
COUNTDOWN               = Bobcat.Parameter;  CreateDefine(COUNTDOWN              ,    22, 'Define', 'ap_defines.h');
CODE0                   = Bobcat.Parameter;  CreateDefine(CODE0                  ,    23, 'Define', 'ap_defines.h');
CODE1                   = Bobcat.Parameter;  CreateDefine(CODE1                  ,    24, 'Define', 'ap_defines.h');
CODE2                   = Bobcat.Parameter;  CreateDefine(CODE2                  ,    25, 'Define', 'ap_defines.h');
CODE3                   = Bobcat.Parameter;  CreateDefine(CODE3                  ,    26, 'Define', 'ap_defines.h');
REPEAT                  = Bobcat.Parameter;  CreateDefine(REPEAT                 ,    27, 'Define', 'ap_defines.h');
COOL                    = Bobcat.Parameter;  CreateDefine(COOL                   ,    28, 'Define', 'ap_defines.h');
APP_VERSION             = Bobcat.Parameter;  CreateDefine(APP_VERSION            ,    29, 'Define', 'ap_defines.h');
HOT                     = Bobcat.Parameter;  CreateDefine(HOT                    ,    30, 'Define', 'ap_defines.h');
SER                     = Bobcat.Parameter;  CreateDefine(SER                    ,    31, 'Define', 'ap_defines.h');
SC_SET                  = Bobcat.Parameter;  CreateDefine(SC_SET                 ,    32, 'Define', 'ap_defines.h');
RESET                   = Bobcat.Parameter;  CreateDefine(RESET                  ,    33, 'Define', 'ap_defines.h');
COUNTDOWN2              = Bobcat.Parameter;  CreateDefine(COUNTDOWN2             ,    34, 'Define', 'ap_defines.h');


NO_LEVEL                = Bobcat.Parameter;  CreateDefine(NO_LEVEL               ,     0, 'Define', 'ap_defines.h');
USER                    = Bobcat.Parameter;  CreateDefine(USER                   ,     1, 'Define', 'ap_defines.h');
OWNER                   = Bobcat.Parameter;  CreateDefine(OWNER                  ,     2, 'Define', 'ap_defines.h');
MASTER                  = Bobcat.Parameter;  CreateDefine(MASTER                 ,     3, 'Define', 'ap_defines.h');


NEW_EVENT               = Bobcat.Parameter;  CreateDefine(NEW_EVENT              ,     1, 'Define', 'ap_defines.h');
CONTINUING_EVENT        = Bobcat.Parameter;  CreateDefine(CONTINUING_EVENT       ,     2, 'Define', 'ap_defines.h');
QUEUE                   = Bobcat.Parameter;  CreateDefine(QUEUE                  ,     3, 'Define', 'ap_defines.h');
NONE                    = Bobcat.Parameter;  CreateDefine(NONE                   ,   255, 'Define', 'ap_defines.h');


FN_HYD_FILTER           = Bobcat.Parameter;  CreateDefine(FN_HYD_FILTER          ,     2, 'Define', 'ap_defines.h');
FN_BATTERY_VOLTAGE      = Bobcat.Parameter;  CreateDefine(FN_BATTERY_VOLTAGE     ,     3, 'Define', 'ap_defines.h');
FN_EOP                  = Bobcat.Parameter;  CreateDefine(FN_EOP                 ,     4, 'Define', 'ap_defines.h');
FN_ENGINE_RPM           = Bobcat.Parameter;  CreateDefine(FN_ENGINE_RPM          ,     6, 'Define', 'ap_defines.h');
FN_HOT                  = Bobcat.Parameter;  CreateDefine(FN_HOT                 ,     7, 'Define', 'ap_defines.h');
FN_ECT                  = Bobcat.Parameter;  CreateDefine(FN_ECT                 ,     8, 'Define', 'ap_defines.h');
FN_FUEL_LEVEL           = Bobcat.Parameter;  CreateDefine(FN_FUEL_LEVEL          ,     9, 'Define', 'ap_defines.h');
FN_AUX_CONTROL          = Bobcat.Parameter;  CreateDefine(FN_AUX_CONTROL         ,    12, 'Define', 'ap_defines.h');
FN_FUEL_HOLD            = Bobcat.Parameter;  CreateDefine(FN_FUEL_HOLD           ,    13, 'Define', 'ap_defines.h');
FN_FUEL_PULL            = Bobcat.Parameter;  CreateDefine(FN_FUEL_PULL           ,    14, 'Define', 'ap_defines.h');
FN_TWO_SPEED            = Bobcat.Parameter;  CreateDefine(FN_TWO_SPEED           ,    20, 'Define', 'ap_defines.h');
FN_GLOW_PLUGS           = Bobcat.Parameter;  CreateDefine(FN_GLOW_PLUGS          ,    21, 'Define', 'ap_defines.h');
FN_STARTER              = Bobcat.Parameter;  CreateDefine(FN_STARTER             ,    22, 'Define', 'ap_defines.h');
FN_OFFSET_BASE          = Bobcat.Parameter;  CreateDefine(FN_OFFSET_BASE         ,    23, 'Define', 'ap_defines.h');
FN_OFFSET_ROD           = Bobcat.Parameter;  CreateDefine(FN_OFFSET_ROD          ,    24, 'Define', 'ap_defines.h');
FN_OFFSET_RETURN        = Bobcat.Parameter;  CreateDefine(FN_OFFSET_RETURN       ,    25, 'Define', 'ap_defines.h');
FN_FRONT_BASE           = Bobcat.Parameter;  CreateDefine(FN_FRONT_BASE          ,    26, 'Define', 'ap_defines.h');
FN_FRONT_ROD            = Bobcat.Parameter;  CreateDefine(FN_FRONT_ROD           ,    27, 'Define', 'ap_defines.h');
FN_XCHANGE              = Bobcat.Parameter;  CreateDefine(FN_XCHANGE             ,    28, 'Define', 'ap_defines.h');
FN_HIGH_FLOW            = Bobcat.Parameter;  CreateDefine(FN_HIGH_FLOW           ,    29, 'Define', 'ap_defines.h');
FN_WATCHDOG_FAILURE     = Bobcat.Parameter;  CreateDefine(FN_WATCHDOG_FAILURE    ,    30, 'Define', 'ap_defines.h');
FN_RECOVERY_FAILURE     = Bobcat.Parameter;  CreateDefine(FN_RECOVERY_FAILURE    ,    31, 'Define', 'ap_defines.h');
FN_CONSTANT_DATA        = Bobcat.Parameter;  CreateDefine(FN_CONSTANT_DATA       ,    33, 'Define', 'ap_defines.h');
FN_ANGLEBLADE_CONTROL   = Bobcat.Parameter;  CreateDefine(FN_ANGLEBLADE_CONTROL  ,    40, 'Define', 'ap_defines.h');
FN_ANGLEBLADE_BASE      = Bobcat.Parameter;  CreateDefine(FN_ANGLEBLADE_BASE     ,    41, 'Define', 'ap_defines.h');
FN_ANGLEBLADE_ROD       = Bobcat.Parameter;  CreateDefine(FN_ANGLEBLADE_ROD      ,    42, 'Define', 'ap_defines.h');
FN_OFFSET_CONTROL       = Bobcat.Parameter;  CreateDefine(FN_OFFSET_CONTROL      ,    60, 'Define', 'ap_defines.h');
FN_LOAD_MOMENT          = Bobcat.Parameter;  CreateDefine(FN_LOAD_MOMENT         ,    62, 'Define', 'ap_defines.h');
FN_CONSOLE_SW           = Bobcat.Parameter;  CreateDefine(FN_CONSOLE_SW          ,    63, 'Define', 'ap_defines.h');
FN_SW_PWR_RELAY         = Bobcat.Parameter;  CreateDefine(FN_SW_PWR_RELAY        ,    64, 'Define', 'ap_defines.h');
FN_WORKGROUP_LOCKOUT    = Bobcat.Parameter;  CreateDefine(FN_WORKGROUP_LOCKOUT   ,    65, 'Define', 'ap_defines.h');



LOC_HYD_FILTER_PLUGGED  = Bobcat.Parameter;  CreateDefine(LOC_HYD_FILTER_PLUGGED ,     1, 'Define', 'ap_defines.h');
LOC_EOP_EXTREMELY_LOW   = Bobcat.Parameter;  CreateDefine(LOC_EOP_EXTREMELY_LOW  ,     2, 'Define', 'ap_defines.h');
LOC_EOP_IN_SHUTDOWN     = Bobcat.Parameter;  CreateDefine(LOC_EOP_IN_SHUTDOWN    ,     4, 'Define', 'ap_defines.h');
LOC_ENGINE_RPM_EXT_HIGH = Bobcat.Parameter;  CreateDefine(LOC_ENGINE_RPM_EXT_HIGH,     8, 'Define', 'ap_defines.h');
LOC_ENGINE_RPM_HIGH     = Bobcat.Parameter;  CreateDefine(LOC_ENGINE_RPM_HIGH    ,     9, 'Define', 'ap_defines.h');
LOC_ENGINE_RPM_SHUTDOWN = Bobcat.Parameter;  CreateDefine(LOC_ENGINE_RPM_SHUTDOWN,    10, 'Define', 'ap_defines.h');
LOC_HOT_EXT_HIGH        = Bobcat.Parameter;  CreateDefine(LOC_HOT_EXT_HIGH       ,    11, 'Define', 'ap_defines.h');
LOC_HOT_HIGH            = Bobcat.Parameter;  CreateDefine(LOC_HOT_HIGH           ,    12, 'Define', 'ap_defines.h');
LOC_HOT_IN_SHUTDOWN     = Bobcat.Parameter;  CreateDefine(LOC_HOT_IN_SHUTDOWN    ,    13, 'Define', 'ap_defines.h');
LOC_ECT_EXT_HIGH        = Bobcat.Parameter;  CreateDefine(LOC_ECT_EXT_HIGH       ,    14, 'Define', 'ap_defines.h');
LOC_ECT_HIGH            = Bobcat.Parameter;  CreateDefine(LOC_ECT_HIGH           ,    15, 'Define', 'ap_defines.h');
LOC_ECT_IN_SHUTDOWN     = Bobcat.Parameter;  CreateDefine(LOC_ECT_IN_SHUTDOWN    ,    16, 'Define', 'ap_defines.h');
LOC_STARTER_ERROR_ON    = Bobcat.Parameter;  CreateDefine(LOC_STARTER_ERROR_ON   ,    17, 'Define', 'ap_defines.h');
LOC_WATCHDOG_FAILURE    = Bobcat.Parameter;  CreateDefine(LOC_WATCHDOG_FAILURE   ,    18, 'Define', 'ap_defines.h');
LOC_RECOVERY_FAILURE    = Bobcat.Parameter;  CreateDefine(LOC_RECOVERY_FAILURE   ,    19, 'Define', 'ap_defines.h');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Constant Data - Parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%function CreateCD(Name, Value, CustStrCls, StructName)

%% fixed point example - to avoid precision loss warnings
CD_LIFT_STROKE_AREA_BASE_TO_GPM    = Bobcat.Parameter;  CreateCD(CD_LIFT_STROKE_AREA_BASE_TO_GPM , fi(46.6528,0,16,8), 'ConstantData', 'gstConstantData');
CD_LIFT_STROKE_AREA_ROD_TO_GPM     = Bobcat.Parameter;  CreateCD(CD_LIFT_STROKE_AREA_ROD_TO_GPM  , fi(46.6528,0,16,8), 'ConstantData', 'gstConstantData');
CD_TILT_STROKE_AREA_BASE_TO_GPM    = Bobcat.Parameter;  CreateCD(CD_TILT_STROKE_AREA_BASE_TO_GPM , fi(46.6528,0,16,8), 'ConstantData', 'gstConstantData');
CD_TILT_STROKE_AREA_ROD_TO_GPM     = Bobcat.Parameter;  CreateCD(CD_TILT_STROKE_AREA_ROD_TO_GPM  , fi(46.6528,0,16,8), 'ConstantData', 'gstConstantData');

%%Fuel Level Parameters
CD_FUEL_TIMER_DURATION             = Bobcat.Parameter;  CreateCD(CD_FUEL_TIMER_DURATION            , 65535, 'ConstantData', 'gstConstantData');
CD_FUEL_TIMER_FUNCTION             = Bobcat.Parameter;  CreateCD(CD_FUEL_TIMER_FUNCTION            ,   255, 'ConstantData', 'gstConstantData');
CD_FUEL_LOW_NOTRUNNING_DB          = Bobcat.Parameter;  CreateCD(CD_FUEL_LOW_NOTRUNNING_DB         ,     2, 'ConstantData', 'gstConstantData');
CD_FUEL_TIMER_RESET                = Bobcat.Parameter;  CreateCD(CD_FUEL_TIMER_RESET               , 65535, 'ConstantData', 'gstConstantData');
CD_FUEL_TIMER_START                = Bobcat.Parameter;  CreateCD(CD_FUEL_TIMER_START               , 65535, 'ConstantData', 'gstConstantData');
CD_FUEL_FILTER_FAST_GAIN           = Bobcat.Parameter;  CreateCD(CD_FUEL_FILTER_FAST_GAIN          ,     3, 'ConstantData', 'gstConstantData');
CD_FUEL_FILTER_SLOW_GAIN           = Bobcat.Parameter;  CreateCD(CD_FUEL_FILTER_SLOW_GAIN          ,     4, 'ConstantData', 'gstConstantData');
CD_FUEL_LOW                        = Bobcat.Parameter;  CreateCD(CD_FUEL_LOW                       ,   169, 'ConstantData', 'gstConstantData');
CD_FUEL_NORMAL_DB                  = Bobcat.Parameter;  CreateCD(CD_FUEL_NORMAL_DB                 ,    31, 'ConstantData', 'gstConstantData');
CD_FUEL_ERROR_DB                   = Bobcat.Parameter;  CreateCD(CD_FUEL_ERROR_DB                  ,     6, 'ConstantData', 'gstConstantData');
CD_FUEL_OORH                       = Bobcat.Parameter;  CreateCD(CD_FUEL_OORH                      ,  3430, 'ConstantData', 'gstConstantData');
CD_FUEL_OORL                       = Bobcat.Parameter;  CreateCD(CD_FUEL_OORL                      ,   110, 'ConstantData', 'gstConstantData');
CD_FUEL_WARN_FUNCTION              = Bobcat.Parameter;  CreateCD(CD_FUEL_WARN_FUNCTION             ,     0, 'ConstantData', 'gstConstantData');
CD_FUEL_WARN_DELTA                 = Bobcat.Parameter;  CreateCD(CD_FUEL_WARN_DELTA                ,   200, 'ConstantData', 'gstConstantData');
CD_FUEL_WARN_TIMEOUT               = Bobcat.Parameter;  CreateCD(CD_FUEL_WARN_TIMEOUT              ,   375, 'ConstantData', 'gstConstantData');

%%Fuel Activation Parameters
CD_FUEL_PULL_ERROR_DB              = Bobcat.Parameter;  CreateCD(CD_FUEL_PULL_ERROR_DB             ,    11, 'ConstantData', 'gstConstantData');
CD_FUEL_PULL_ERROR_ON              = Bobcat.Parameter;  CreateCD(CD_FUEL_PULL_ERROR_ON             ,   100, 'ConstantData', 'gstConstantData');
CD_FUEL_PULL_ERROR_OFF             = Bobcat.Parameter;  CreateCD(CD_FUEL_PULL_ERROR_OFF            ,   850, 'ConstantData', 'gstConstantData');
CD_FUEL_HOLD_STG                   = Bobcat.Parameter;  CreateCD(CD_FUEL_HOLD_STG                  ,   100, 'ConstantData', 'gstConstantData');
CD_FUEL_HOLD_STB                   = Bobcat.Parameter;  CreateCD(CD_FUEL_HOLD_STB                  ,   950, 'ConstantData', 'gstConstantData');
CD_FUEL_HOLD_OPEN_LOW              = Bobcat.Parameter;  CreateCD(CD_FUEL_HOLD_OPEN_LOW             ,   950, 'ConstantData', 'gstConstantData');
CD_FUEL_HOLD_OPEN_HIGH             = Bobcat.Parameter;  CreateCD(CD_FUEL_HOLD_OPEN_HIGH            ,  1050, 'ConstantData', 'gstConstantData');
CD_FUEL_HOLD_ERROR_DB              = Bobcat.Parameter;  CreateCD(CD_FUEL_HOLD_ERROR_DB             ,     4, 'ConstantData', 'gstConstantData');
CD_FUEL_PULL_REPULL_DELAY          = Bobcat.Parameter;  CreateCD(CD_FUEL_PULL_REPULL_DELAY         ,    50, 'ConstantData', 'gstConstantData');
CD_FUEL_PULL_RELAY_THRESHOLD       = Bobcat.Parameter;  CreateCD(CD_FUEL_PULL_RELAY_THRESHOLD      ,    80, 'ConstantData', 'gstConstantData');

%%Starter Parameters
CD_STARTER_ERROR_ON                = Bobcat.Parameter;  CreateCD(CD_STARTER_ERROR_ON               ,   100, 'ConstantData', 'gstConstantData');
CD_STARTER_ERROR_OFF               = Bobcat.Parameter;  CreateCD(CD_STARTER_ERROR_OFF              ,   850, 'ConstantData', 'gstConstantData');
CD_STARTER_ERROR_DB                = Bobcat.Parameter;  CreateCD(CD_STARTER_ERROR_DB               ,    75, 'ConstantData', 'gstConstantData');
CD_STARTER_RELAY_THRESHOLD         = Bobcat.Parameter;  CreateCD(CD_STARTER_RELAY_THRESHOLD        ,    80, 'ConstantData', 'gstConstantData');
CD_STARTER_FUNCTION                = Bobcat.Parameter;  CreateCD(CD_STARTER_FUNCTION               ,   255, 'ConstantData', 'gstConstantData');
CD_STARTER_TIMEOUT                 = Bobcat.Parameter;  CreateCD(CD_STARTER_TIMEOUT                ,   375, 'ConstantData', 'gstConstantData');

%% EOP Parameters
CD_EOP_LOW_DB                      = Bobcat.Parameter;  CreateCD(CD_EOP_LOW_DB                     ,    31, 'ConstantData', 'gstConstantData');
CD_EOP_NORMAL_DB                   = Bobcat.Parameter;  CreateCD(CD_EOP_NORMAL_DB                  ,    31, 'ConstantData', 'gstConstantData');
CD_EOP_SHUTDOWN_DB                 = Bobcat.Parameter;  CreateCD(CD_EOP_SHUTDOWN_DB                ,    63, 'ConstantData', 'gstConstantData');

%%Mode Timers
CD_AUX_VERSION_TIME                = Bobcat.Parameter;  CreateCD(CD_AUX_VERSION_TIME               ,   250, 'ConstantData', 'gstConstantData');
CD_LIGHTS_LIMITED_TIME             = Bobcat.Parameter;  CreateCD(CD_LIGHTS_LIMITED_TIME            , 60000, 'ConstantData', 'gstConstantData');
CD_HOURS_LIMITED_TIME              = Bobcat.Parameter;  CreateCD(CD_HOURS_LIMITED_TIME             ,  3000, 'ConstantData', 'gstConstantData');
CD_KEYLESS_ENTER_TIME              = Bobcat.Parameter;  CreateCD(CD_KEYLESS_ENTER_TIME             ,  1000, 'ConstantData', 'gstConstantData');
CD_KEYLESS_LOCKDOWN_TIME           = Bobcat.Parameter;  CreateCD(CD_KEYLESS_LOCKDOWN_TIME          ,  4500, 'ConstantData', 'gstConstantData');
CD_KEYLESS_SHUTDOWN_TIME           = Bobcat.Parameter;  CreateCD(CD_KEYLESS_SHUTDOWN_TIME          ,   375, 'ConstantData', 'gstConstantData');
CD_KEYLESS_DISPLAY_TIME            = Bobcat.Parameter;  CreateCD(CD_KEYLESS_DISPLAY_TIME           ,    25, 'ConstantData', 'gstConstantData');
CD_POWER_DOWN_TIME                 = Bobcat.Parameter;  CreateCD(CD_POWER_DOWN_TIME                ,   100, 'ConstantData', 'gstConstantData');
CD_COOL_DOWN_TIME                  = Bobcat.Parameter;  CreateCD(CD_COOL_DOWN_TIME                 , 18000, 'ConstantData', 'gstConstantData');

%%Switched Power Parameters
CD_SW_PWR_DELAY                    = Bobcat.Parameter;  CreateCD(CD_SW_PWR_DELAY                   ,     8, 'ConstantData', 'gstConstantData');
CD_SW_PWR_ERROR_DB                 = Bobcat.Parameter;  CreateCD(CD_SW_PWR_ERROR_DB                ,     2, 'ConstantData', 'gstConstantData');
CD_SW_PWR_STG                      = Bobcat.Parameter;  CreateCD(CD_SW_PWR_STG                     ,   100, 'ConstantData', 'gstConstantData');
CD_SW_PWR_STB                      = Bobcat.Parameter;  CreateCD(CD_SW_PWR_STB                     ,   950, 'ConstantData', 'gstConstantData');
CD_SW_PWR_OPEN_LOW                 = Bobcat.Parameter;  CreateCD(CD_SW_PWR_OPEN_LOW                ,   950, 'ConstantData', 'gstConstantData');
CD_SW_PWR_OPEN_HIGH                = Bobcat.Parameter;  CreateCD(CD_SW_PWR_OPEN_HIGH               ,  1050, 'ConstantData', 'gstConstantData');

%%Icon Parameters
CD_ICON_POST_TIME                  = Bobcat.Parameter;  CreateCD(CD_ICON_POST_TIME                 ,     6, 'ConstantData', 'gstConstantData');
CD_SEATBELT_TIME                   = Bobcat.Parameter;  CreateCD(CD_SEATBELT_TIME                  ,   250, 'ConstantData', 'gstConstantData');
CD_ICON_FLASH_TIME                 = Bobcat.Parameter;  CreateCD(CD_ICON_FLASH_TIME                ,     6, 'ConstantData', 'gstConstantData');
CD_ICON_INTENSITY                  = Bobcat.Parameter;  CreateCD(CD_ICON_INTENSITY                 ,    80, 'ConstantData', 'gstConstantData');
CD_BACKLIGHT_INTENSITY             = Bobcat.Parameter;  CreateCD(CD_BACKLIGHT_INTENSITY            ,    80, 'ConstantData', 'gstConstantData');
CD_GAUGE_NORMAL_SPEED              = Bobcat.Parameter;  CreateCD(CD_GAUGE_NORMAL_SPEED             ,     4, 'ConstantData', 'gstConstantData');

%%Hydraulic Filter Parameters
CD_HYD_FILTER_NORMAL_DB            = Bobcat.Parameter;  CreateCD(CD_HYD_FILTER_NORMAL_DB           ,     3, 'ConstantData', 'gstConstantData');
CD_HYD_FILTER_RUN_TIME             = Bobcat.Parameter;  CreateCD(CD_HYD_FILTER_RUN_TIME            ,    63, 'ConstantData', 'gstConstantData');
CD_HYD_FILTER_TEMP                 = Bobcat.Parameter;  CreateCD(CD_HYD_FILTER_TEMP                ,   100, 'ConstantData', 'gstConstantData');
CD_HYD_FILTER_PLUGGED_DB           = Bobcat.Parameter;  CreateCD(CD_HYD_FILTER_PLUGGED_DB          ,     3, 'ConstantData', 'gstConstantData');
CD_HYD_FILTER_NOTCONN_DB           = Bobcat.Parameter;  CreateCD(CD_HYD_FILTER_NOTCONN_DB          ,     3, 'ConstantData', 'gstConstantData');

%%Armbar Parameters
CD_ARMBAR_STB                      = Bobcat.Parameter;  CreateCD(CD_ARMBAR_STB                     ,  1000, 'ConstantData', 'gstConstantData');
CD_ARMBAR_RATIO_LOW                = Bobcat.Parameter;  CreateCD(CD_ARMBAR_RATIO_LOW               ,   262, 'ConstantData', 'gstConstantData');
CD_ARMBAR_RATIO_HIGH               = Bobcat.Parameter;  CreateCD(CD_ARMBAR_RATIO_HIGH              ,   322, 'ConstantData', 'gstConstantData');
CD_ARMBAR_STG                      = Bobcat.Parameter;  CreateCD(CD_ARMBAR_STG                     ,    10, 'ConstantData', 'gstConstantData');
CD_ARMBAR_DB                       = Bobcat.Parameter;  CreateCD(CD_ARMBAR_DB                      ,     3, 'ConstantData', 'gstConstantData');

%% Miscellaneous Parameters
CD_SWITCH_DB                       = Bobcat.Parameter;  CreateCD(CD_SWITCH_DB                      ,    52, 'ConstantData', 'gstConstantData');
CD_CHANGE_MODE_TIME                = Bobcat.Parameter;  CreateCD(CD_CHANGE_MODE_TIME               ,    60, 'ConstantData', 'gstConstantData');
CD_MINIMUM_VBAT                    = Bobcat.Parameter;  CreateCD(CD_MINIMUM_VBAT                   ,   255, 'ConstantData', 'gstConstantData');
CD_TERMINATOR_FUNCTION             = Bobcat.Parameter;  CreateCD(CD_TERMINATOR_FUNCTION            ,     1, 'ConstantData', 'gstConstantData');
CD_MAXIMUM_VBAT                    = Bobcat.Parameter;  CreateCD(CD_MAXIMUM_VBAT                   ,   170, 'ConstantData', 'gstConstantData');
CD_BUTTON_STUCK_DB                 = Bobcat.Parameter;  CreateCD(CD_BUTTON_STUCK_DB                ,   500, 'ConstantData', 'gstConstantData');
CD_DEFAULT_CONSTANT_DATA           = Bobcat.Parameter;  CreateCD(CD_DEFAULT_CONSTANT_DATA          ,     0, 'ConstantData', 'gstConstantData');
CD_MODULE_ID                       = Bobcat.Parameter;  CreateCD(CD_MODULE_ID                      ,     3, 'ConstantData', 'gstConstantData');

%%Engine Parameters
CD_ENGINE_RUNNING_RPM              = Bobcat.Parameter;  CreateCD(CD_ENGINE_RUNNING_RPM             ,   700, 'ConstantData', 'gstConstantData');
CD_ENGINE_STOPPED_RPM              = Bobcat.Parameter;  CreateCD(CD_ENGINE_STOPPED_RPM             ,   100, 'ConstantData', 'gstConstantData');
CD_NUMBER_OF_TEETH                 = Bobcat.Parameter;  CreateCD(CD_NUMBER_OF_TEETH                ,   104, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_NO_SIGNAL          = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_NO_SIGNAL         ,     0, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_HIGH               = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_HIGH              ,  3500, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_EXT_HIGH           = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_EXT_HIGH          ,  4000, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_OOR                = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_OOR               ,  6000, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_NO_SIGNAL_VOLTS    = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_NO_SIGNAL_VOLTS   ,   135, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_FILTER_DELTA       = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_FILTER_DELTA      ,    15, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_FILTER_SLOW_GAIN   = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_FILTER_SLOW_GAIN  ,    10, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_FILTER_FAST_GAIN   = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_FILTER_FAST_GAIN  ,     2, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_OOR_DB             = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_OOR_DB            ,    13, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_ERROR_DB           = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_ERROR_DB          ,    63, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_SHUTDOWN_DB        = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_SHUTDOWN_DB       ,   125, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_NO_SIGNAL_RECOVER  = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_NO_SIGNAL_RECOVER ,     0, 'ConstantData', 'gstConstantData');
CD_ENGINE_SPEED_FILTER_DISPLAY     = Bobcat.Parameter;  CreateCD(CD_ENGINE_SPEED_FILTER_DISPLAY    ,  3277, 'ConstantData', 'gstConstantData');

%% ECT Parameters
CD_ECT_OORL                        = Bobcat.Parameter;  CreateCD(CD_ECT_OORL                       ,   135, 'ConstantData', 'gstConstantData');
CD_ECT_OORH                        = Bobcat.Parameter;  CreateCD(CD_ECT_OORH                       ,  2275, 'ConstantData', 'gstConstantData');
CD_ECT_COLD                        = Bobcat.Parameter;  CreateCD(CD_ECT_COLD                       ,    70, 'ConstantData', 'gstConstantData');
CD_ECT_HIGH                        = Bobcat.Parameter;  CreateCD(CD_ECT_HIGH                       ,   230, 'ConstantData', 'gstConstantData');
CD_ECT_EXT_HIGH                    = Bobcat.Parameter;  CreateCD(CD_ECT_EXT_HIGH                   ,   235, 'ConstantData', 'gstConstantData');
CD_ECT_OOR_DB                      = Bobcat.Parameter;  CreateCD(CD_ECT_OOR_DB                     ,     6, 'ConstantData', 'gstConstantData');
CD_ECT_NORMAL_DB                   = Bobcat.Parameter;  CreateCD(CD_ECT_NORMAL_DB                  ,    31, 'ConstantData', 'gstConstantData');
CD_ECT_COLD_DB                     = Bobcat.Parameter;  CreateCD(CD_ECT_COLD_DB                    ,    31, 'ConstantData', 'gstConstantData');
CD_ECT_HIGH_DB                     = Bobcat.Parameter;  CreateCD(CD_ECT_HIGH_DB                    ,    31, 'ConstantData', 'gstConstantData');
CD_ECT_EXT_HIGH_DB                 = Bobcat.Parameter;  CreateCD(CD_ECT_EXT_HIGH_DB                ,    63, 'ConstantData', 'gstConstantData');
CD_ECT_SHUTDOWN_DB                 = Bobcat.Parameter;  CreateCD(CD_ECT_SHUTDOWN_DB                ,   125, 'ConstantData', 'gstConstantData');
CD_ECT_FILTER_GAIN                 = Bobcat.Parameter;  CreateCD(CD_ECT_FILTER_GAIN                ,     6, 'ConstantData', 'gstConstantData');
CD_ECT_HYSTERESIS                  = Bobcat.Parameter;  CreateCD(CD_ECT_HYSTERESIS                 ,     5, 'ConstantData', 'gstConstantData');

%%HOT Parameters
CD_HOT_OORL                        = Bobcat.Parameter;  CreateCD(CD_HOT_OORL                       ,   135, 'ConstantData', 'gstConstantData');
CD_HOT_OORH                        = Bobcat.Parameter;  CreateCD(CD_HOT_OORH                       ,  2275, 'ConstantData', 'gstConstantData');
CD_HOT_COLD                        = Bobcat.Parameter;  CreateCD(CD_HOT_COLD                       ,   100, 'ConstantData', 'gstConstantData');
CD_HOT_HIGH                        = Bobcat.Parameter;  CreateCD(CD_HOT_HIGH                       ,   230, 'ConstantData', 'gstConstantData');
CD_HOT_EXT_HIGH                    = Bobcat.Parameter;  CreateCD(CD_HOT_EXT_HIGH                   ,   235, 'ConstantData', 'gstConstantData');
CD_HOT_OOR_DB                      = Bobcat.Parameter;  CreateCD(CD_HOT_OOR_DB                     ,     6, 'ConstantData', 'gstConstantData');
CD_HOT_NORMAL_DB                   = Bobcat.Parameter;  CreateCD(CD_HOT_NORMAL_DB                  ,    31, 'ConstantData', 'gstConstantData');
CD_HOT_COLD_DB                     = Bobcat.Parameter;  CreateCD(CD_HOT_COLD_DB                    ,    31, 'ConstantData', 'gstConstantData');
CD_HOT_HIGH_DB                     = Bobcat.Parameter;  CreateCD(CD_HOT_HIGH_DB                    ,    31, 'ConstantData', 'gstConstantData');
CD_HOT_EXT_HIGH_DB                 = Bobcat.Parameter;  CreateCD(CD_HOT_EXT_HIGH_DB                ,    63, 'ConstantData', 'gstConstantData');
CD_HOT_SHUTDOWN_DB                 = Bobcat.Parameter;  CreateCD(CD_HOT_SHUTDOWN_DB                ,   125, 'ConstantData', 'gstConstantData');
CD_HOT_FILTER_GAIN                 = Bobcat.Parameter;  CreateCD(CD_HOT_FILTER_GAIN                ,     6, 'ConstantData', 'gstConstantData');
CD_HOT_HYSTERESIS                  = Bobcat.Parameter;  CreateCD(CD_HOT_HYSTERESIS                 ,     5, 'ConstantData', 'gstConstantData');

%% Aux Pot Parameters
CD_AUXPOT_DEADBAND_LOW             = Bobcat.Parameter;  CreateCD(CD_AUXPOT_DEADBAND_LOW            ,   424, 'ConstantData', 'gstConstantData');
CD_AUXPOT_DEADBAND_HIGH            = Bobcat.Parameter;  CreateCD(CD_AUXPOT_DEADBAND_HIGH           ,   574, 'ConstantData', 'gstConstantData');
CD_AUXPOT_CENTER_RATIO             = Bobcat.Parameter;  CreateCD(CD_AUXPOT_CENTER_RATIO            ,   500, 'ConstantData', 'gstConstantData');
CD_AUXPOT_CENTER_DEGREES           = Bobcat.Parameter;  CreateCD(CD_AUXPOT_CENTER_DEGREES          ,    80, 'ConstantData', 'gstConstantData');
CD_AUXPOT_SPAN                     = Bobcat.Parameter;  CreateCD(CD_AUXPOT_SPAN                    ,   160, 'ConstantData', 'gstConstantData');
CD_AUXPOT_OORH                     = Bobcat.Parameter;  CreateCD(CD_AUXPOT_OORH                    ,   950, 'ConstantData', 'gstConstantData');
CD_AUXPOT_OORL                     = Bobcat.Parameter;  CreateCD(CD_AUXPOT_OORL                    ,    50, 'ConstantData', 'gstConstantData');
CD_AUXPOT_OOR_DB                   = Bobcat.Parameter;  CreateCD(CD_AUXPOT_OOR_DB                  ,    13, 'ConstantData', 'gstConstantData');
CD_AUXPOT_DEADBAND_DEGREES         = Bobcat.Parameter;  CreateCD(CD_AUXPOT_DEADBAND_DEGREES        ,     6, 'ConstantData', 'gstConstantData');

%% Aux Hydraulics Parameters
CD_AUX_LOOP_KP                     = Bobcat.Parameter;  CreateCD(CD_AUX_LOOP_KP                    ,    31, 'ConstantData', 'gstConstantData');
CD_AUX_LOOP_KI                     = Bobcat.Parameter;  CreateCD(CD_AUX_LOOP_KI                    ,    12, 'ConstantData', 'gstConstantData');
CD_AUX_ERROR_FILTER_GAIN           = Bobcat.Parameter;  CreateCD(CD_AUX_ERROR_FILTER_GAIN          ,     4, 'ConstantData', 'gstConstantData');
CD_AUX_ERROR_DEADZONE              = Bobcat.Parameter;  CreateCD(CD_AUX_ERROR_DEADZONE             ,   175, 'ConstantData', 'gstConstantData');
CD_AUX_ERROR_THRESHOLD             = Bobcat.Parameter;  CreateCD(CD_AUX_ERROR_THRESHOLD            ,   175, 'ConstantData', 'gstConstantData');
CD_AUX_ERROR_HIGH_LEVEL            = Bobcat.Parameter;  CreateCD(CD_AUX_ERROR_HIGH_LEVEL           ,  1000, 'ConstantData', 'gstConstantData');
CD_AUX_ERROR_LOW_LEVEL             = Bobcat.Parameter;  CreateCD(CD_AUX_ERROR_LOW_LEVEL            ,   900, 'ConstantData', 'gstConstantData');
CD_AUX_ERROR_PULSE_COUNT           = Bobcat.Parameter;  CreateCD(CD_AUX_ERROR_PULSE_COUNT          ,     5, 'ConstantData', 'gstConstantData');
CD_AUX_ALLOWWITHCONSOLEUP          = Bobcat.Parameter;  CreateCD(CD_AUX_ALLOWWITHCONSOLEUP         ,   255, 'ConstantData', 'gstConstantData');
CD_AUX_FULL_ON                     = Bobcat.Parameter;  CreateCD(CD_AUX_FULL_ON                    ,   950, 'ConstantData', 'gstConstantData');
CD_AUX_ERROR_DB                    = Bobcat.Parameter;  CreateCD(CD_AUX_ERROR_DB                   ,    15, 'ConstantData', 'gstConstantData');

%% Battery Parameters
CD_BATTERY_OORL                    = Bobcat.Parameter;  CreateCD(CD_BATTERY_OORL                   ,    60, 'ConstantData', 'gstConstantData');
CD_BATTERY_EXT_LOW                 = Bobcat.Parameter;  CreateCD(CD_BATTERY_EXT_LOW                ,   100, 'ConstantData', 'gstConstantData');
CD_BATTERY_LOW                     = Bobcat.Parameter;  CreateCD(CD_BATTERY_LOW                    ,   110, 'ConstantData', 'gstConstantData');
CD_BATTERY_HIGH                    = Bobcat.Parameter;  CreateCD(CD_BATTERY_HIGH                   ,   160, 'ConstantData', 'gstConstantData');
CD_BATTERY_EXT_HIGH                = Bobcat.Parameter;  CreateCD(CD_BATTERY_EXT_HIGH               ,   180, 'ConstantData', 'gstConstantData');
CD_BATTERY_OORL_DB                 = Bobcat.Parameter;  CreateCD(CD_BATTERY_OORL_DB                ,     1, 'ConstantData', 'gstConstantData');
CD_BATTERY_SHUTDOWN_DB             = Bobcat.Parameter;  CreateCD(CD_BATTERY_SHUTDOWN_DB            ,   250, 'ConstantData', 'gstConstantData');
CD_BATTERY_EXT_LOW_DB              = Bobcat.Parameter;  CreateCD(CD_BATTERY_EXT_LOW_DB             ,    25, 'ConstantData', 'gstConstantData');
CD_BATTERY_LOW_DB                  = Bobcat.Parameter;  CreateCD(CD_BATTERY_LOW_DB                 ,    25, 'ConstantData', 'gstConstantData');
CD_BATTERY_NORMAL_DB               = Bobcat.Parameter;  CreateCD(CD_BATTERY_NORMAL_DB              ,    25, 'ConstantData', 'gstConstantData');
CD_BATTERY_HIGH_DB                 = Bobcat.Parameter;  CreateCD(CD_BATTERY_HIGH_DB                ,    25, 'ConstantData', 'gstConstantData');
CD_BATTERY_EXT_HIGH_DB             = Bobcat.Parameter;  CreateCD(CD_BATTERY_EXT_HIGH_DB            ,    25, 'ConstantData', 'gstConstantData');

%% Load Moment Parameters
CD_LOAD_MOMENT_ERROR_DB            = Bobcat.Parameter;  CreateCD(CD_LOAD_MOMENT_ERROR_DB           ,     2, 'ConstantData', 'gstConstantData');
CD_LOAD_MOMENT_NORMAL_DB           = Bobcat.Parameter;  CreateCD(CD_LOAD_MOMENT_NORMAL_DB          ,     7, 'ConstantData', 'gstConstantData');

%% Glow Plug Parameters
CD_GP_AFTERGLOW_FUNCTION           = Bobcat.Parameter;  CreateCD(CD_GP_AFTERGLOW_FUNCTION          ,   255, 'ConstantData', 'gstConstantData');
CD_GP_CRANKING_FUNCTION            = Bobcat.Parameter;  CreateCD(CD_GP_CRANKING_FUNCTION           ,     0, 'ConstantData', 'gstConstantData');
CD_GP_PREHEAT_FUNCTION             = Bobcat.Parameter;  CreateCD(CD_GP_PREHEAT_FUNCTION            ,     0, 'ConstantData', 'gstConstantData');
CD_GP_PREHEAT_CYCLES               = Bobcat.Parameter;  CreateCD(CD_GP_PREHEAT_CYCLES              ,     2, 'ConstantData', 'gstConstantData');
CD_GP_ERROR_ON                     = Bobcat.Parameter;  CreateCD(CD_GP_ERROR_ON                    ,   100, 'ConstantData', 'gstConstantData');
CD_GP_ERROR_OFF                    = Bobcat.Parameter;  CreateCD(CD_GP_ERROR_OFF                   ,   600, 'ConstantData', 'gstConstantData');
CD_GP_ERROR_DB                     = Bobcat.Parameter;  CreateCD(CD_GP_ERROR_DB                    ,    12, 'ConstantData', 'gstConstantData');
CD_GP_RELAY_THRESHOLD              = Bobcat.Parameter;  CreateCD(CD_GP_RELAY_THRESHOLD             ,    80, 'ConstantData', 'gstConstantData');

%% Two Speed Parameters
CD_TWOSPEED_FUNCTION               = Bobcat.Parameter;  CreateCD(CD_TWOSPEED_FUNCTION              ,     0, 'ConstantData', 'gstConstantData');
CD_TWOSPEED_ERROR_DB               = Bobcat.Parameter;  CreateCD(CD_TWOSPEED_ERROR_DB              ,     8, 'ConstantData', 'gstConstantData');

%% Workgroup Parameters
CD_WORKGROUP_ERROR_DB              = Bobcat.Parameter;  CreateCD(CD_WORKGROUP_ERROR_DB             ,     2, 'ConstantData', 'gstConstantData');
CD_WORKGROUP_STG                   = Bobcat.Parameter;  CreateCD(CD_WORKGROUP_STG                  ,   100, 'ConstantData', 'gstConstantData');
CD_WORKGROUP_STB                   = Bobcat.Parameter;  CreateCD(CD_WORKGROUP_STB                  ,   950, 'ConstantData', 'gstConstantData');
CD_WORKGROUP_OPEN_LOW              = Bobcat.Parameter;  CreateCD(CD_WORKGROUP_OPEN_LOW             ,   950, 'ConstantData', 'gstConstantData');
CD_WORKGROUP_OPEN_HIGH             = Bobcat.Parameter;  CreateCD(CD_WORKGROUP_OPEN_HIGH            ,  1050, 'ConstantData', 'gstConstantData');
CD_XCHANGE_FUNCTION                = Bobcat.Parameter;  CreateCD(CD_XCHANGE_FUNCTION               ,   255, 'ConstantData', 'gstConstantData');
CD_XCHANGE_ERROR_DB                = Bobcat.Parameter;  CreateCD(CD_XCHANGE_ERROR_DB               ,     4, 'ConstantData', 'gstConstantData');

%%Angle Blade Parameters
CD_ANGLEBLADE_FUNCTION             = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_FUNCTION            ,     0, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_LOOP_KP              = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_LOOP_KP             ,    40, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_LOOP_KI              = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_LOOP_KI             ,    25, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_ERROR_THRESHOLD      = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_ERROR_THRESHOLD     ,   250, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_ERROR_DEADZONE       = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_ERROR_DEADZONE      ,   250, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_ERROR_FILTER_GAIN    = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_ERROR_FILTER_GAIN   ,     3, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_ERROR_PULSE_COUNT    = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_ERROR_PULSE_COUNT   ,     5, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_ERROR_HIGH_LEVEL     = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_ERROR_HIGH_LEVEL    ,  1000, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_ERROR_LOW_LEVEL      = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_ERROR_LOW_LEVEL     ,   900, 'ConstantData', 'gstConstantData');

%% AngleBlade Pot Parameters
CD_ANGLEBLADE_POT_DEADBAND_LOW     = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_POT_DEADBAND_LOW    ,   424, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_POT_DEADBAND_HIGH    = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_POT_DEADBAND_HIGH   ,   574, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_POT_CENTER_RATIO     = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_POT_CENTER_RATIO    ,   500, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_POT_CENTER_DEGREES   = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_POT_CENTER_DEGREES  ,    80, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_POT_SPAN             = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_POT_SPAN            ,   160, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_POT_OORH             = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_POT_OORH            ,   950, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_POT_OORL             = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_POT_OORL            ,    50, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_POT_OOR_DB           = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_POT_OOR_DB          ,    13, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_POT_DEADBAND_DEGREES = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_POT_DEADBAND_DEGREES,     6, 'ConstantData', 'gstConstantData');

%% AngleBlade Control Parameters
CD_ANGLEBLADE_ERROR_DB             = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_ERROR_DB            ,    25, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_STG_THRESHOLD        = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_STG_THRESHOLD       ,   100, 'ConstantData', 'gstConstantData');
CD_ANGLEBLADE_STB_THRESHOLD        = Bobcat.Parameter;  CreateCD(CD_ANGLEBLADE_STB_THRESHOLD       ,   950, 'ConstantData', 'gstConstantData');

%% Offset Pot Parameters
CD_OFFSET_POT_DEADBAND_LOW         = Bobcat.Parameter;  CreateCD(CD_OFFSET_POT_DEADBAND_LOW        ,   424, 'ConstantData', 'gstConstantData');
CD_OFFSET_POT_DEADBAND_HIGH        = Bobcat.Parameter;  CreateCD(CD_OFFSET_POT_DEADBAND_HIGH       ,   574, 'ConstantData', 'gstConstantData');
CD_OFFSET_POT_CENTER_RATIO         = Bobcat.Parameter;  CreateCD(CD_OFFSET_POT_CENTER_RATIO        ,   500, 'ConstantData', 'gstConstantData');
CD_OFFSET_POT_CENTER_DEGREES       = Bobcat.Parameter;  CreateCD(CD_OFFSET_POT_CENTER_DEGREES      ,    80, 'ConstantData', 'gstConstantData');
CD_OFFSET_POT_SPAN                 = Bobcat.Parameter;  CreateCD(CD_OFFSET_POT_SPAN                ,   160, 'ConstantData', 'gstConstantData');
CD_OFFSET_POT_OORH                 = Bobcat.Parameter;  CreateCD(CD_OFFSET_POT_OORH                ,   950, 'ConstantData', 'gstConstantData');
CD_OFFSET_POT_OORL                 = Bobcat.Parameter;  CreateCD(CD_OFFSET_POT_OORL                ,    50, 'ConstantData', 'gstConstantData');
CD_OFFSET_POT_OOR_DB               = Bobcat.Parameter;  CreateCD(CD_OFFSET_POT_OOR_DB              ,    13, 'ConstantData', 'gstConstantData');
CD_OFFSET_POT_DEADBAND_DEGREES     = Bobcat.Parameter;  CreateCD(CD_OFFSET_POT_DEADBAND_DEGREES    ,     6, 'ConstantData', 'gstConstantData');

%% Offset Control Parameters
CD_OFFSET_LOOP_KP                  = Bobcat.Parameter;  CreateCD(CD_OFFSET_LOOP_KP                 ,    31, 'ConstantData', 'gstConstantData');
CD_OFFSET_LOOP_KI                  = Bobcat.Parameter;  CreateCD(CD_OFFSET_LOOP_KI                 ,    12, 'ConstantData', 'gstConstantData');
CD_OFFSET_ERROR_DEADZONE           = Bobcat.Parameter;  CreateCD(CD_OFFSET_ERROR_DEADZONE          ,   175, 'ConstantData', 'gstConstantData');
CD_OFFSET_ERROR_THRESHOLD          = Bobcat.Parameter;  CreateCD(CD_OFFSET_ERROR_THRESHOLD         ,   175, 'ConstantData', 'gstConstantData');
CD_OFFSET_ERROR_HIGH_LEVEL         = Bobcat.Parameter;  CreateCD(CD_OFFSET_ERROR_HIGH_LEVEL        ,   600, 'ConstantData', 'gstConstantData');
CD_OFFSET_ERROR_LOW_LEVEL          = Bobcat.Parameter;  CreateCD(CD_OFFSET_ERROR_LOW_LEVEL         ,   400, 'ConstantData', 'gstConstantData');
CD_OFFSET_ERROR_PULSE_COUNT        = Bobcat.Parameter;  CreateCD(CD_OFFSET_ERROR_PULSE_COUNT       ,     6, 'ConstantData', 'gstConstantData');
CD_OFFSET_ERROR_FILTER_GAIN        = Bobcat.Parameter;  CreateCD(CD_OFFSET_ERROR_FILTER_GAIN       ,     4, 'ConstantData', 'gstConstantData');
CD_OFFSET_ERROR_DB                 = Bobcat.Parameter;  CreateCD(CD_OFFSET_ERROR_DB                ,    15, 'ConstantData', 'gstConstantData');
CD_OFFSET_FUNCTION                 = Bobcat.Parameter;  CreateCD(CD_OFFSET_FUNCTION                ,     0, 'ConstantData', 'gstConstantData');
CD_OFFSET_MAX_CURRENT              = Bobcat.Parameter;  CreateCD(CD_OFFSET_MAX_CURRENT             ,  3150, 'ConstantData', 'gstConstantData');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Constant Data - Tables
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Fixed point table example
%function CreateFiCDTable(Name, matFile, Signed, Length, Fraction, CustStrCls, StructName)
CD_FUEL_TABLE_GAUGE = Bobcat.Parameter;  CreateFiCDTable(CD_FUEL_TABLE_GAUGE,'FuelGaugeTable',0,16,8, 'ConstantData', 'gstConstantData','DataTables\');



%function CreateCDTable(Name, matFile, CustStrCls, StructName)
CD_FUEL_TABLE_GAUGE        = Bobcat.Parameter;  CreateCDTable(CD_FUEL_TABLE_GAUGE       ,        FuelTableGauge, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_FUEL_TABLE_INPUT        = Bobcat.Parameter;  CreateCDTable(CD_FUEL_TABLE_INPUT       ,        FuelTableInput, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_FUEL_PULL_TABLE         = Bobcat.Parameter;  CreateCDTable(CD_FUEL_PULL_TABLE        ,         FuelPullTable, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_ECT_TABLE_INPUT         = Bobcat.Parameter;  CreateCDTable(CD_ECT_TABLE_INPUT        ,        ECT_TableInput, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_ECT_TABLE_GAUGE         = Bobcat.Parameter;  CreateCDTable(CD_ECT_TABLE_GAUGE        ,        ECT_TableGauge, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_HOT_TABLE_INPUT         = Bobcat.Parameter;  CreateCDTable(CD_HOT_TABLE_INPUT        ,        HOT_TableInput, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_TEMP_TABLE              = Bobcat.Parameter;  CreateCDTable(CD_TEMP_TABLE             ,             TempTable, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_AUXHYD_TABLE_OUTPUT     = Bobcat.Parameter;  CreateCDTable(CD_AUXHYD_TABLE_OUTPUT    ,     AuxHydTableOutput, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_GP_TABLE_AFTERGLOW      = Bobcat.Parameter;  CreateCDTable(CD_GP_TABLE_AFTERGLOW     ,GlowPlugTableAfterGlow, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_GP_TABLE_PREHEAT        = Bobcat.Parameter;  CreateCDTable(CD_GP_TABLE_PREHEAT       ,  GlowPlugTablePreheat, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_GP_TABLE_PREHEAT_WAIT   = Bobcat.Parameter;  CreateCDTable(CD_GP_TABLE_PREHEAT_WAIT  ,     GlowPlugTableWait, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_GP_TABLE_TEMP           = Bobcat.Parameter;  CreateCDTable(CD_GP_TABLE_TEMP          ,     GlowPlugTableTemp, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_OFFSET_TABLE_OUTPUT     = Bobcat.Parameter;  CreateCDTable(CD_OFFSET_TABLE_OUTPUT    ,     OffsetTableOutput, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');
CD_ANGLEBLADE_TABLE_OUTPUT = Bobcat.Parameter;  CreateCDTable(CD_ANGLEBLADE_TABLE_OUTPUT, AngleBladeTableOutput, 'Custom', 'ConstantData', 'gstConstantData','DataTables/');

