%Function for loading ROM tables to workspace
%
% Name: CreateROMTable.m
%
% Copyright 2008 Bobcat Company as an unpublished work. 
% All Rights Reserved.
%
% The information contained herein is confidential property of Bobcat
% Company. The use, copying, transfer or disclosure of such information is
% prohibited except by express written agreement with Bobcat Company.
%	
% First written on 31 May 2021 by A.Liebel
%	
% Description:
%   Function to create Constant Data table information in the workspace.
%
%   Name - parameter name (i.e. ROM_INPUT_TABLE)
%   vector - a column vector with the data to be placed in the table.
%       e.g. [1 2 3 4]',  fi([0:.1:10]', 0,16,8)
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function CreateROMTable(Name, vector)
    Name.RTWInfo.StorageClass = 'Custom';
	Name.RTWInfo.CustomStorageClass = 'ROMTables';	
	Name.Value = vector;
	
end