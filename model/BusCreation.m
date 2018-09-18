%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Create Bus Objects
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%function CreateBusElement(Number, Name, Type, SampleTime)
%function CreateBus(Name, Type, SampleTime,elems)
	elems = Simulink.BusElement;
	Ts = -1;
	CreateBusElement(1,		'outNMCStatus',		'boolean', 	Ts, elems);
	CreateBusElement(2,    'outNEBStatus',  	'boolean', 	Ts, elems);
	CreateBusElement(3,    'outA3', 				'boolean', 	Ts, elems);
	CreateBusElement(4,    'outA4', 				'boolean', 	Ts, elems);
	CreateBusElement(5, 		'outA5', 				'boolean', 	Ts, elems);
	CreateBusElement(6, 		'outA6', 				'boolean', 	Ts, elems);
	CreateBusElement(7,    'outA10', 				'boolean', 	Ts, elems);
	CreateBusElement(8,    'outA13', 				'boolean', 	Ts, elems);
	CreateBusElement(9, 		'outA19', 				'boolean', 	Ts, elems);
	CreateBusElement(10, 	'sensAckInProg', 	'boolean', 	Ts, elems);
	CreateBusElement(11,   'sensAckOK', 		'boolean', 	Ts, elems);
	CreateBusElement(12,   'watchdogBit', 		'boolean', 	Ts, elems);
	CreateBusElement(13, 	'statusByte', 		'uint8', 		Ts, elems);
	CreateBusElement(14, 	'anin01', 				'uint8', 		Ts, elems);
	CreateBusElement(15,   'anin02', 				'uint8', 		Ts, elems);
	CreateBusElement(16,   'actualCurrent', 	'uint8', 		Ts, elems);
	CreateBusElement(17, 	'actualSpeed', 		'int16', 		Ts, elems);

	CreateBus('CANOpenMsgRPDO1', elems,'Auto');
	clear elems;

	elems = Simulink.BusElement;
	Ts = -1;
	CreateBusElement(1,		'enablePower',		'boolean', 	Ts, elems);
	CreateBusElement(2,    'powerLineON',  	'boolean', 	Ts, elems);
	CreateBusElement(3,    'outNEB', 				'boolean', 	Ts, elems);
	CreateBusElement(4,    'dirFWD', 				'boolean', 	Ts, elems);
	CreateBusElement(5, 		'dirREV', 				'boolean', 	Ts, elems);
	CreateBusElement(6, 		'watchdogBit', 		'boolean', 	Ts, elems);
	CreateBusElement(7, 		'brakeReq', 			'uint8', 		Ts, elems);
	CreateBusElement(8, 		'targetSpeed', 		'uint16', 		Ts, elems);


	CreateBus('CANOpenMsgTPDO1', elems,'Auto');
	clear elems;
	
	elems = Simulink.BusElement;
	Ts = -1;
	CreateBusElement(1,		'In1',		'boolean', 	Ts, elems);
	CreateBusElement(2,    'In2',  	'boolean', 	Ts, elems);

	CreateBus('test', elems,'Auto');
	clear elems;

	elems = Simulink.BusElement;
	Ts = -1;
	CreateBusElement(1,		'Out1',		'boolean', 	Ts, elems);
	CreateBusElement(2,    'Out2',  	'uint16', 	Ts, elems);

	CreateBus('testOut', elems,'Auto');
	clear elems;
