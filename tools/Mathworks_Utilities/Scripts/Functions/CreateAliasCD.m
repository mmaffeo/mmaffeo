%Function for loading constant data to workspace
%
% Name: CreateCD.m
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
%   Function to create Constant Data (non-table)table information in the
%   workspace.
%   Name - Parameter Name (i.e. CD_FUEL_INPUT_TABLE)
%   Value - Workspace value to be assigned to parameter
%   CustStrCls - Custom Storage Class name for constant data parameter
%   StructName - Constant Data structure name
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function CreateAliasCD(Name, Value, CustStrCls, StructName, Alias)
    Name.RTWInfo.StorageClass = 'Custom';
    Name.RTWInfo.CustomStorageClass = CustStrCls;
    Name.RTWInfo.CustomAttributes.StructName = StructName;
    Name.Value = Value;
    Name.RTWInfo.Alias = Alias;
end