function busNameCreator(busObject, busCreator)
% busNameCreator - Description
% Populates the names of the input ports of a Bus Creator block with the
% signal names specified by a Bus Object
% -------------------------------------------------------------------------
% Syntax:
%           busNameCreator(<busObject>, <busCreator>)
%
% Inputs:
%           1st Argument - Takes the Bus Object
%           2nd Argument - Takes the Bus Creator block
%
% Outputs:
%           none
%
% Examples:
%           busNameCreator(COUNTERBUS, gcb)
%
% Notes: none
%
% Copyright <YEAR> The MathWorks, Inc.
%
% Auth/Revision:
%   The MathWorks Consulting Group
%   $Author: aliebel$
%   $Revision: 1$  $Date: Monday, June 02, 2008 9:43:25 AM$
% -------------------------------------------------------------------------

%% Test if the inputs are valid inputs
if(~isa(busObject,'Simulink.Bus'))
    error('The 1st argument is expected to be a ''Simulink.Bus'' object');
end
if(~strcmp(get_param(gcb, 'BlockType'), 'BusCreator'))
    error('The 2nd argument is expected to be a ''BusCreator'' block');
end

%% Implementation
% Get the inport handles
inportHandles = get_param(busCreator, 'PortHandles');
% Verify if the number of inport handles and the number of elements in the
% bus Object match
if(length(inportHandles.Inport)~=length(busObject.Elements))
    error('The number of input ports to the Bus Creator did not match the number of elements in the bus object');
end
for i=1:length(inportHandles.Inport)
   inputSignalHandle = get(inportHandles.Inport(i),'Line');
   set(inputSignalHandle,'Name', busObject.Elements(i).Name);
end

end