function CreateBus(Name, ws_elems,DataScope) 
% CreateBus initializes a set of bus objects in the MATLAB base workspace 

% Bus object: ACS_Inputs
temp = sprintf(Name);
temp = Simulink.Bus;
temp.HeaderFile = '';
temp.Description = '';
temp.DataScope = DataScope;
temp.Elements = ws_elems;
assignin('base', Name, temp);
