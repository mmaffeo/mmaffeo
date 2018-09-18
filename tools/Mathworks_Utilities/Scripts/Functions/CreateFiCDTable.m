%Function for loading fixed point constant data tables to workspace
%
% Name: CreateFiCDTable.m
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
%   Signed - 0 = Unsigned, 1 = Signed
%   Length = 8,16,32
%   Fraction = Fraction Length
%   CustStrCls - Custom Storage Class name for constant data parameter
%   StructName - Constant Data structure name
%   Path - Optional path for subfolder
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function CreateFiCDTable(Name, matFile, Signed, Length, Fraction, CustStrCls, StructName, Path)
    Name.RTWInfo.StorageClass = 'Custom';
    Name.RTWInfo.CustomStorageClass = CustStrCls;
    Name.RTWInfo.CustomAttributes.StructName = StructName;
    load (strcat(Path,matFile))
    Name.Value = fi(eval(sprintf(matFile)),Signed,Length,Fraction);
end