%Function for loading constant data tables to workspace
%
% Name: CreateCDTable.m
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
%   Function to create Constant Data table information in the workspace.
%   NOTES:
%   1. A .mat file must exist for each table.
%   2. The variable name in the .mat file MUST be tableData.
%
%   Name - Parameter Name (i.e. CD_FUEL_INPUT_TABLE)
%   matFile - .mat Filename that contains the table data
%   CustStrCls - Custom Storage Class name for constant data parameter
%   StructName - Constant Data structure name
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function CreateAliasCDTable(Name, matFile, CustStrCls, StructName, Path, Alias)
    Name.RTWInfo.StorageClass = 'Custom';
    Name.RTWInfo.CustomStorageClass = CustStrCls;
    Name.RTWInfo.CustomAttributes.StructName = StructName;
    load (strcat(Path,matFile));
    Name.Value = tableData;
    Name.RTWInfo.Alias = Alias;
end