%%  Install Bobcat Utilities
ThisFilePath = mfilename('fullpath');
ThisFilePath = ThisFilePath(1:(end - length(mfilename)));
BobcatUtilsPath = [ ThisFilePath '.\..\tools\Mathworks_Utilities\'];

addpath([ ThisFilePath 'functions']);
run([BobcatUtilsPath 'BobcatUtils_install.m']);

clear ThisFilePath BobcatUtilsPath;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%import data from the bobcat database for hc_12
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%note - this script also updates hc12_cdata.h and hc12_cdata.c
try
	ret_str_tmp = perl ('read_CD2.pl', ...%'-C',...
		'-a', 'CONSTANT_DATA,0x4200',...
        '-r', 'CONSTANT_DATA',...
		'-o', '..\sources\hcs12\cdata.h',...
		'-p', '..\sources\hcs12\cdata.c',...
        '-m', 'eE10*A*EM',...        
		'-q', 'hc12_cdata.m',...
        '-n',...
        '-P',...
        '-A',...
        '-W', '36',...
        '-R', '0x03D8000',...
		'database\ED1287_MXGateway.sadb',...
		'MX_GATEWAY');
	disp(ret_str_tmp);
catch ME
	disp(ME.message);
	disp('PostLoadFcn.m failed to execute read_CD.pl.  cdata.m has not been updated.');
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%import data from the bobcat database for m4
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
try
	ret_str_tmp = perl ('read_CD2.pl', ...%'-C',...
        '-r', 'CONSTANT_DATA',...
		'-o', '..\sources\bsp\cdata.h',...
		'-p', '..\sources\bsp\iar_cdata.c',...
        '-m', 'eE10*A*EM',...        
		'-q', 'm4_cdata.m',...
        '-s', '..\sources\bsp\ap_cdata.cpp',...
        '-n',...
        '-P',...
        '-A',...
        '-I',...
        '-W', '36',...
        '-R', '0x08010000',...
		'database\ED1287_MXGateway.sadb',...
		'MX_GATEWAY');
	disp(ret_str_tmp);
catch ME
	disp(ME.message);
	disp('PostLoadFcn.m failed to execute read_CD.pl.  cdata.m has not been updated.');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%import data from the bobcat database for clean M4
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
try
	ret_str_tmp = perl ('read_CD2.pl', ...%'-C',...
        '-r', 'CONSTANT_DATA',...
		'-p', '..\sources\bsp\cdata.c',...
        '-m', 'eE10*A*EM',...
        '-n',...
        '-A',...
        '-G',...
        '-P',...
        '-W', '36',...
        '-R', '0x08010000',...
		'database\ED1287_MXGateway.sadb',...
		'MX_GATEWAY');
	disp(ret_str_tmp);
catch ME
	disp(ME.message);
	disp('PostLoadFcn.m failed to execute read_CD.pl.  cdata.m has not been updated.');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%import enum & #define symbols
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

try
	ret_str_tmp = perl ('read_defines.pl',...
		'-o','defines.m',...
		'../sources/ap_eeprom.h','../sources/defines.h','../sources/ap_can.h');
	disp(ret_str_tmp);
catch ME
	disp(ME.message);
	disp('PostLoadFcn.m failed to execute read_defines.pl.  defines.m has not been updated.');
end

try
	ret_str_tmp = perl ('read_enums.pl',...
		'-o','enums.m',...
		'../sources/defines.h','../sources/ap_can.h');%,'../sources/ap_dv.h');
	disp(ret_str_tmp);
catch ME
	disp(ME.message);
	disp('PostLoadFcn.m failed to execute read_enums.pl.  enums.m has not been updated.');
end

clear ret_str_tmp;
clear ME;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%run the auto-generated m-files for hc12
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
hc12_cdata;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%run the auto-generated m-files for hc12
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
hc12_cdata;
defines;
enums;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%m-files built by hand for hc12
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%LoadWorkspace;
save hc12_workspace.mat;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%run the auto-generated m-files for M4
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear;
m4_cdata;
defines;
enums;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%m-files built by hand for M4
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

LoadWorkspace;
save m4_workspace.mat;

%%optional compare of hc12 and m4
%visdiff('hc12_workspace.mat','m4_workspace.mat');
