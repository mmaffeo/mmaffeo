%Function for loading constant data to workspace
%
% Name: CreateGlobal.m
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
%   Function to import c globals into simulink.
%   Name - Parameter Name (i.e. CD_FUEL_INPUT_TABLE)
%   InitialValue - Value the simulation starts with.  Must be a string.
%   DataType - Data type used by simulink.  Must be a string.
%   HeaderFile - Name of header file that defines this variable.
%   Dim (optional) - dimension of the variable being accessed (default = scalar)
%
%   note: Do not use a 'Data Store Memory' block with variables defined using
%     this function.
%
%   Example: (for c variable "uint16_t debug01 = 0;")
%     debug01 = Simulink.Signal;
%     CreateGlobal(debug01, '0', 'uint16','ap_subs.h');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function CreateGlobal(Name, InitialValue, DataType, HeaderFile, varargin)
	optargin = size(varargin,2);
	if optargin <= 0, Dim=1; else Dim = varargin{1}; end
	
    Name.RTWInfo.StorageClass = 'Custom';
    Name.RTWInfo.CustomStorageClass = 'ImportFromFile';
    Name.RTWInfo.CustomAttributes.HeaderFile = HeaderFile;
    Name.InitialValue = InitialValue;
    Name.DataType = DataType;
    Name.Complexity   = 'real';
    Name.SamplingMode = 'Sample Based';
    Name.Dimensions = Dim;
end
