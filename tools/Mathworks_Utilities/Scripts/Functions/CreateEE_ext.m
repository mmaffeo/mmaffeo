%Function for loading constant data to workspace
%
% Name: CreateEE_ext.m
%
% Copyright 2008 Bobcat Company as an unpublished work. 
% All Rights Reserved.
%
% The information contained herein is confidential property of Bobcat
% Company. The use, copying, transfer or disclosure of such information is
% prohibited except by express written agreement with Bobcat Company.
%	
% First written on 23 Oct 2008 by Jeff Cox.
%
% Description:
%   Function to create EEProm signal information in the
%   workspace.
%   Name - Parameter Name (i.e. CD_FUEL_INPUT_TABLE)
%   InitialValue - Value the simulation starts with.  Must be a string.
%   DataType - Data type used by simulink.  Must be a string.
%   StructName - Constant Data structure name
%
%   note: Do not use a 'Data Store Memory' block with variables defined using
%     this function.
%
%   Example:
%     ee_CalTiltRodStart   = Bobcat.Signal;
%     CreateEE_ext(ee_CalTiltRodStart  ,'0' ,'fixdt(1,16,12)', 'EEMirror' ,'eeMirror');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function CreateEE_ext(Name, InitialValue, DataType, StructName)
    Name.RTWInfo.StorageClass = 'Custom';
    Name.RTWInfo.CustomStorageClass = 'EEMirror';
    Name.RTWInfo.CustomAttributes.StructName = StructName;
    Name.InitialValue = InitialValue;
    Name.DataType = DataType;
    Name.Complexity   = 'real';
    Name.SamplingMode = 'Sample Based';
    Name.Dimensions = 1;
end
