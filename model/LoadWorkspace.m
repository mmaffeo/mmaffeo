%Script to load workspace with model parameters
%
% Name: LoadWorkspace.m
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
% First written on 02 June 2008 by Spencer Mindeman.
%
% Description:
%   Used to create parameters required by the model. 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Simulation parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

srate     = 0.010;
srate100  = 0.1;
srate20   = 0.020;
srate1000 = 1;

%Load custom tlc files to add far qualifier to lookup tables
%copyfile(fullfile(matlabroot,'rtw\c\tlc\fixpt\fixptlook_search.tlcfar'),fullfile(matlabroot,'rtw\c\tlc\fixpt\fixptlook_search.tlc'),'f');
%copyfile(fullfile(matlabroot,'rtw\c\tlc\fixpt\fixptlook1D.tlcfar'),fullfile(matlabroot,'rtw\c\tlc\fixpt\fixptlook1D.tlc'),'f');

%EEPROM variables
ee_AuxFlow          = Bobcat.Signal; CreateEE(ee_AuxFlow,'EEMirror','eeMirror');
ee_AuxFlow.Dimensions = 1;
ee_AuxFlow.DataType = 'uint8';
ee_AuxFlow.Complexity = 'real';
ee_AuxFlow.SamplingMode = 'Sample based';

ee_ControlMode      = Bobcat.Signal; CreateEE(ee_ControlMode,'EEMirror','eeMirror');
ee_ControlMode.Dimensions = 1;
ee_ControlMode.DataType = 'uint8';
ee_ControlMode.Complexity = 'real';
ee_ControlMode.SamplingMode = 'Sample based';

ee_EcoMode          = Bobcat.Signal; CreateEE(ee_EcoMode,'EEMirror','eeMirror');
ee_EcoMode.Dimensions = 1;
ee_EcoMode.DataType = 'uint8';
ee_EcoMode.Complexity = 'real';
ee_EcoMode.SamplingMode = 'Sample based';

%ee_HydResponse          = Bobcat.Signal; CreateEE(ee_HydResponse,'EEMirror','eeMirror');
%ee_HydResponse.Dimensions = 1;
%ee_HydResponse.DataType = 'uint8';
%ee_HydResponse.Complexity = 'real';
%ee_HydResponse.SamplingMode = 'Sample based';

ee_EngData          = Bobcat.Signal; CreateEE(ee_EngData,'EEMirror','eeMirror');
ee_EngData.Dimensions = 1;
ee_EngData.DataType = 'uint8';
ee_EngData.Complexity = 'real';
ee_EngData.SamplingMode = 'Sample based';
ee_EngData.RTWInfo.Alias = 'EngData';

ee_DeluxeG5          = Bobcat.Signal; CreateEE(ee_DeluxeG5,'EEMirror','eeMirror');
ee_DeluxeG5.Dimensions = 1;
ee_DeluxeG5.DataType = 'uint8';
ee_DeluxeG5.Complexity = 'real';
ee_DeluxeG5.SamplingMode = 'Sample based';
ee_DeluxeG5.RTWInfo.Alias = 'deluxe_G5';

ee_Keypad          = Bobcat.Signal; CreateEE(ee_Keypad,'EEMirror','eeMirror');
ee_Keypad.Dimensions = 1;
ee_Keypad.DataType = 'uint8';
ee_Keypad.Complexity = 'real';
ee_Keypad.SamplingMode = 'Sample based';
ee_Keypad.RTWInfo.Alias = 'keypad';

ee_RFIDKey          = Bobcat.Signal; CreateEE(ee_RFIDKey,'EEMirror','eeMirror');
ee_RFIDKey.Dimensions = 1;
ee_RFIDKey.DataType = 'uint8';
ee_RFIDKey.Complexity = 'real';
ee_RFIDKey.SamplingMode = 'Sample based';
ee_RFIDKey.RTWInfo.Alias = 'RFIDKey';

ee_laserMode          = Bobcat.Signal; CreateEE(ee_laserMode,'EEMirror','eeMirror');
ee_laserMode.Dimensions = 1;
ee_laserMode.DataType = 'uint8';
ee_laserMode.Complexity = 'real';
ee_laserMode.SamplingMode = 'Sample based';
ee_laserMode.RTWInfo.Alias = 'laserMode';

ee_PasswordLock          = Bobcat.Signal; CreateEE(ee_PasswordLock,'EEMirror','eeMirror');
ee_PasswordLock.Dimensions = 1;
ee_PasswordLock.DataType = 'uint8';
ee_PasswordLock.Complexity = 'real';
ee_PasswordLock.SamplingMode = 'Sample based';
ee_PasswordLock.RTWInfo.Alias = 'passwordLock';

ee_JobClockLHP          = Bobcat.Signal; CreateEE(ee_JobClockLHP,'EEMirror','eeMirror');
ee_JobClockLHP.Dimensions = 2;
ee_JobClockLHP.DataType = 'uint8';
ee_JobClockLHP.Complexity = 'real';
ee_JobClockLHP.SamplingMode = 'Sample based';
ee_JobClockLHP.RTWInfo.Alias = 'jobClockLHP';

ee_AutoIdleEnabled          = Bobcat.Signal; CreateEE(ee_AutoIdleEnabled,'EEMirror','eeMirror');
ee_AutoIdleEnabled.Dimensions = 1;
ee_AutoIdleEnabled.DataType = 'int8';
ee_AutoIdleEnabled.Complexity = 'real';
ee_AutoIdleEnabled.SamplingMode = 'Sample based';

ee_autoIdleTime          = Bobcat.Signal; CreateEE(ee_autoIdleTime,'EEMirror','eeMirror');
ee_autoIdleTime.Dimensions = 1;
ee_autoIdleTime.DataType = 'uint8';
ee_autoIdleTime.Complexity = 'real';
ee_autoIdleTime.SamplingMode = 'Sample based';

ee_ThrottleCalState          = Bobcat.Signal; CreateEE(ee_ThrottleCalState,'EEMirror','eeMirror');
ee_ThrottleCalState.Dimensions = 1;
ee_ThrottleCalState.DataType = 'uint8';
ee_ThrottleCalState.Complexity = 'real';
ee_ThrottleCalState.SamplingMode = 'Sample based';

ee_ThrottleCalExtended       = Bobcat.Signal; CreateEE(ee_ThrottleCalExtended,'EEMirror','eeMirror');
ee_ThrottleCalExtended.Dimensions = 1;
ee_ThrottleCalExtended.DataType = 'uint16';
ee_ThrottleCalExtended.Complexity = 'real';
ee_ThrottleCalExtended.SamplingMode = 'Sample based';

ee_ThrottleCalRetracted      = Bobcat.Signal; CreateEE(ee_ThrottleCalRetracted,'EEMirror','eeMirror');
ee_ThrottleCalRetracted.Dimensions = 1;
ee_ThrottleCalRetracted.DataType = 'uint16';
ee_ThrottleCalRetracted.Complexity = 'real';
ee_ThrottleCalRetracted.SamplingMode = 'Sample based';

flag_StdActiveWarn = Bobcat.Signal; CreateSignal(flag_StdActiveWarn, 'ImportedExtern', 1);
flag_StdActiveWarn.DataType = 'uint8';
flag_StdActiveWarn.Complexity = 'real';
flag_StdActiveWarn.SamplingMode = 'Sample based';



%Global Data
ee_MasterPassword    = Bobcat.Signal; CreateSignal(ee_MasterPassword,    'ImportedExtern', 5);
msg_PanelButtonState = Bobcat.Signal; CreateSignal(msg_PanelButtonState, 'ImportedExtern', 8);
can_Keypad           = Bobcat.Signal; CreateSignal(can_Keypad,           'ImportedExtern', 3);
can_KeylessEntry     = Bobcat.Signal; CreateSignal(can_KeylessEntry,     'ImportedExtern', 3);
msg_PanelACDButton   = Bobcat.Signal; CreateSignal(msg_PanelACDButton,   'ImportedExtern', 8);
msg_DeluxeButtons    = Bobcat.Signal; CreateSignal(msg_DeluxeButtons,    'ImportedExtern', 5);
pwd_Keyless          = Bobcat.Signal; CreateSignal(pwd_Keyless,          'ImportedExtern', 5);
pwd_Keyless.DataType = 'uint8';

ee_OwnerPassword     = Bobcat.Signal; CreateSignal(ee_OwnerPassword,     'ImportedExtern', 5);
ee_User1Password     = Bobcat.Signal; CreateSignal(ee_User1Password,     'ImportedExtern', 5);
ee_User2Password     = Bobcat.Signal; CreateSignal(ee_User2Password,     'ImportedExtern', 5);
ee_KeylessEntryPasswords     = Bobcat.Signal; CreateSignal(ee_KeylessEntryPasswords,     'ImportedExtern', [10,22]);

eeTimeToUpdateMirror = Bobcat.Signal; CreateSignal(eeTimeToUpdateMirror, 'ImportedExtern', 1);
eeTimeToUpdateMirror.DataType = 'uint8';
eeTimeToUpdateMirror.Complexity = 'real';
eeTimeToUpdateMirror.SamplingMode = 'Sample based';

state_Buzzer = Bobcat.Signal; CreateSignal(state_Buzzer, 'ImportedExtern', 1);
state_Buzzer.DataType = 'uint8';
state_Buzzer.Complexity = 'real';
state_Buzzer.SamplingMode = 'Sample based';

msg_BJM2Left  = Bobcat.Signal; CreateSignal(msg_BJM2Left,  'ImportedExtern', 8);
msg_BJM2Right = Bobcat.Signal; CreateSignal(msg_BJM2Right, 'ImportedExtern', 8);


%Special define for initializing states to normal
INIT_NORMAL = uint8(8);

%HW Fin driver
PERIOD_COUNTS_PER_SECOND = Bobcat.Parameter;  CreateDefine(PERIOD_COUNTS_PER_SECOND ,     3125000, 'Define', 'hw_fin.h');

