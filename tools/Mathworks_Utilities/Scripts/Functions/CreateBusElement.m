function CreateBusElement(Number, Name, Type, SampleTime, ws_elems) 
% Create Bus Elements creates an element for a bus object in the MATLAB base workspace 
elems = ws_elems;
elems(Number) = Simulink.BusElement;
elems(Number).Name = Name;
elems(Number).Dimensions = 1;
elems(Number).DataType = Type;
elems(Number).SampleTime = SampleTime;
elems(Number).Complexity = 'real';
elems(Number).SamplingMode = 'Sample based';
assignin('base', 'elems', elems);



