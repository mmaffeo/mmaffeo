%    Adds paths for utilities
%    File           :   BobcatUtils_install.m
%    Creator(s)          : $Author: aliebel$
%    Date created       : $Date: Monday, June 02, 2008 9:43:26 AM$
%    Date last modified : DATE_STRING
%    Modified by        : CREATOR_STRING
%    Description        :
%                              Used to add the necessary paths for the
%                              libraries, custom storage classes and the
%                              bobcat target and other utilities
%    Notes              :
% 
%                  Copyright (c) 1984-YEAR_STRING The MathWorks, Inc.
% 
% Revision: $Id: BobcatUtils_install.m 54 2008-04-25 13:58:09Z jgattu $
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Find the Installation/Root Directory
filePath = mfilename('fullpath');
fileName = mfilename;
rootDir = filePath(1:end-length(fileName));
rawPath=genpath(rootDir);
rawPathCell=textscan(rawPath,'%s','delimiter',';');
rawPathCell=rawPathCell{1};

% remove undesired paths
SCMFilteredPath=strfind(rawPathCell,'.MySCMServerInfo');
slprjFilteredPath=strfind(rawPathCell,'slprj');
sfprjFilteredPath=strfind(rawPathCell,'sfprj');
rtwFilteredPath=strfind(rawPathCell,'_ert_rtw');
svnFilteredPath=strfind(rawPathCell,'.svn');

% repository specific filters
exampleFilteredPath=strfind(rawPathCell,'ExampleScripts');
%contrFilteredPath=strfind(rawPathCell,'contract');
%docFilteredPath=strfind(rawPathCell,'documentation');
%origFilteredPath=strfind(rawPathCell,'orig');

disp('Adding Custom Paths for Bobcat Utilities');
disp('-------------------');

% loop through path and remove all the .svn entries
for pCount=1:length(SCMFilteredPath),
    filterCheck=[SCMFilteredPath{pCount},...
        slprjFilteredPath{pCount},...
        sfprjFilteredPath{pCount},...
        rtwFilteredPath{pCount},...
        exampleFilteredPath{pCount},...
        svnFilteredPath{pCount}...
 %       contrFilteredPath{pCount},...
 %       origFilteredPath{pCount},...
 %       docFilteredPath{pCount}
        ];
    if isempty(filterCheck)
        disp(['Adding ',rawPathCell{pCount}]);
        addpath(rawPathCell{pCount});
    else
        % ignore
    end
end

clear;