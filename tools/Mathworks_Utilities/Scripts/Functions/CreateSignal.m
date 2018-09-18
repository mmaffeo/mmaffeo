%Function for loading constant data to workspace
%
% Name: CreateEE.m
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
%   Function to create EEProm signal information in the
%   workspace.
%   Name - Parameter Name (i.e. CD_FUEL_INPUT_TABLE)
%   Value - Workspace value to be assigned to parameter
%   CustStrCls - Custom Storage Class name for constant data parameter
%   StructName - Constant Data structure name
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function CreateSignal(Name, CustStrCls, Dim)
    Name.RTWInfo.StorageClass = CustStrCls;
    Name.Dimensions = Dim;
end