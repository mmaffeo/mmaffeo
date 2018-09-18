

%% Prepare Base Workspase

fprintf('\nGenerating Model Code\n-------------------\n');
MX_GW_Startup

%% 

model = 'MX_Gateway';
subsys = 'MX_Gtwy_Control';
modelIsOpen = bdIsLoaded(model);

%% Load model if it is not already open or loaded
if ~modelIsOpen
    load_system(model);
end

%% Generate code
rtwbuild([model '/' subsys]);

%% Close model if it was not already open or loaded
if ~modelIsOpen
    close_system(model);
end

%% Copy Generated source files to source directory

% codeDir = fullfile(fileparts(mfilename('fullpath')), 'MX_Gtwy_Control_bobcat_ert_rtw');
% tempCodeDir = fullfile(fileparts(mfilename('fullpath')), [subsys '_ert_rtw']);
% copyfile(fullfile(tempCodeDir, '*.c'), codeDir);
% copyfile(fullfile(tempCodeDir, '*.h'), codeDir);


clear model subsys modelIsOpen %codeDir tempCodeDir