function returnTimer = autosave_mdl(mdlRoot, saveTime)
% AUTOSAVE_MDL Periodically saves a Simulink model to a temporary file.
%
%   AUTOSAVE_MDL(MDLROOT, SAVETIME) saves the Simulink .mdl file and copies 
%   it to a file MDLROOT_tmp.mdl every SAVETIME seconds.  If SAVETIME is 
%   omitted, it defaults to 15 minutes.  If MDLROOT is omitted, it defaults
%   to the default model opened as returned by the 'bdroot' command.
%
%
%   To stop the autosaver, use the command:
%       
%        autosave_mdl -quit
%
%   See also TIMER, SAVE.

% Tom Egel, The MathWorks, Inc.

defaultModel = bdroot; % set default to active model
defaultTime = 60*15;  % set default save time to 15 minutes

% Argument checking...
if (nargin == 0)
    mdlRoot = defaultModel;
    saveTime = defaultTime;
elseif (nargin == 1)
    if ~ischar(mdlRoot)
        error('FILENAME must be a string.');
    end
    
    if (strcmp(mdlRoot, '-quit'))
        stop(timerfind('Tag', 'Autosave timer'));
        delete(timerfind('Tag', 'Autosave timer'));
        return
    end
    
    saveTime = defaultTime;
elseif (nargin == 2)
    if ~ischar(mdlRoot)
        error('MDLROOT must be a string');
    elseif (~isnumeric(period) && (numel(period) ~= 1))
        error('SAVETIME must be a 1x1 number.');
    end
else
    nargchk(0,2,nargin);
end

% Call timer function
delete(timerfind('Tag', 'Autosave timer'));
t = timer('Tag', 'Autosave timer', 'Period', saveTime, 'ExecutionMode', 'fixedDelay', ...
    'StartDelay', saveTime, 'TimerFcn', @localSave, 'UserData', mdlRoot, 'TasksToExecute', inf);
start(t)

if (nargout == 1)
    returnTimer = t;
end

% Function to save model and copy to temporary location
function localSave(obj, event)
mdlRoot = obj.UserData;
mdlExist = bdroot;

% Check to make sure a model is open and it is not the Simulink library
if (strcmp(mdlExist,'')==0 && strcmp(mdlExist,'simulink')==0)
    save_system(mdlRoot);  
    copyfile([mdlRoot '.mdl'], [mdlRoot '_tmp.mdl']) 
end