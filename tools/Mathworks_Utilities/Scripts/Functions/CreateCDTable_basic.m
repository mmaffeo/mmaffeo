%Function for loading constant data tables to workspace
%
% Name: CreateCDTable_basic.m
%
% Copyright 2008 Bobcat Company as an unpublished work. 
% All Rights Reserved.
%
% The information contained herein is confidential property of Bobcat
% Company. The use, copying, transfer or disclosure of such information is
% prohibited except by express written agreement with Bobcat Company.
%	
% First written on 23 Oct 2008 by Jeff Cox
%	
% Description:
%   Function to create Constant Data table information in the workspace.
%
%   Name - parameter name (i.e. CD_FUEL_INPUT_TABLE)
%   StructName - constant data table structure name
%   vector - a column vector with the data to be placed in the table.
%       e.g. [1 2 3 4]',  fi([0:.1:10]', 0,16,8)
%
%  If StructName is not '', then this function assumes that your constant
%  data tables are declared as array members of the ‘StructName’ structure.
%  Accessing table entry i looks like this in generated code:
%    <StructName>.<Name>[i]
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function CreateCDTable_basic(Name, StructName, vector)
    Name.RTWInfo.StorageClass = 'Custom';
	if strcmp(StructName,'')
		Name.RTWInfo.CustomStorageClass = 'ConstantDataFreeTable';
	else
		Name.RTWInfo.CustomStorageClass = 'ConstantDataTable';	
		Name.RTWInfo.CustomAttributes.StructName = StructName;
	end
	Name.Value = vector;
	
end