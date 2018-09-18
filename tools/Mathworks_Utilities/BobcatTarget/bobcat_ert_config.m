function bobcat_ert_config(hDlg, hSrc)
% 
%    Function           :   bobcat_ert_config.m
%    Creator(s)         : $Author: aliebel$
%    Date created       : $Date: Monday, May 16, 2011 3:02:47 PM$
%    Date last modified : DATE_STRING
%    Modified by        : CREATOR_STRING
%    Description        :
%                              bobcat Configuration file for use with RTW-EC
%                              This file provides the default settings for the RTW
%                               configuration pane.
%    Notes              :
% 
%                  Copyright (c) 1984-YEAR_STRING The MathWorks, Inc.
% 
% Revision: $Id: bobcat_ert_config.m 54 2008-04-25 13:58:09Z jgattu $
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

allowMods = true;

%% Solver                                          
%slConfigUISetVal(hDlg, hSrc, 'StartTime','0.0')
%slConfigUISetEnabled(hDlg, hSrc, 'StartTime', allowMods)
 
%slConfigUISetVal(hDlg, hSrc, 'StopTime','10.0')
%slConfigUISetEnabled(hDlg, hSrc, 'StopTime', allowMods)
 
%slConfigUISetVal(hDlg, hSrc, 'Solver','FixedStepDiscrete')
%slConfigUISetEnabled(hDlg, hSrc, 'Solver', allowMods)
 
%slConfigUISetVal(hDlg, hSrc, 'SolverName','FixedStepDiscrete')
%slConfigUISetEnabled(hDlg, hSrc, 'SolverName', allowMods)
 
%slConfigUISetVal(hDlg, hSrc, 'SolverType','Fixed-step')
%slConfigUISetEnabled(hDlg, hSrc, 'SolverType', allowMods)
 
% slConfigUISetVal(hDlg, hSrc, 'SolverMode','Auto')
% slConfigUISetEnabled(hDlg, hSrc, 'SolverMode', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ZeroCrossControl','UseLocalSettings')
% slConfigUISetEnabled(hDlg, hSrc, 'ZeroCrossControl', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SolverResetMethod','Fast')
% slConfigUISetEnabled(hDlg, hSrc, 'SolverResetMethod', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'PositivePriorityOrder','off')
% slConfigUISetEnabled(hDlg, hSrc, 'PositivePriorityOrder', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'AutoInsertRateTranBlk','off')
% slConfigUISetEnabled(hDlg, hSrc, 'AutoInsertRateTranBlk', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SampleTimeConstraint','Unconstrained')
% slConfigUISetEnabled(hDlg, hSrc, 'SampleTimeConstraint', allowMods)


%% Data Import/Export                              
% slConfigUISetVal(hDlg, hSrc, 'Decimation','1')
% slConfigUISetEnabled(hDlg, hSrc, 'Decimation', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'LoadExternalInput','off')
% slConfigUISetEnabled(hDlg, hSrc, 'LoadExternalInput', allowMods)
% 
% % External input is ignored when LoadExternalInput is 'off'
% % slConfigUISetVal(hDlg, hSrc, 'ExternalInput','[t, u]')
% % slConfigUISetEnabled(hDlg, hSrc, 'ExternalInput', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SaveFinalState','off')
% slConfigUISetEnabled(hDlg, hSrc, 'SaveFinalState', allowMods)

% FinalStateName is ignored when SaveFinalState is 'off'
% slConfigUISetVal(hDlg, hSrc, 'FinalStateName','xFinal')
% slConfigUISetEnabled(hDlg, hSrc, 'FinalStateName', allowMods)

% slConfigUISetVal(hDlg, hSrc, 'LoadInitialState','off')
% slConfigUISetEnabled(hDlg, hSrc, 'LoadInitialState', allowMods)
% 
% % InitialState is ignored when LoadInitialState is off
% % slConfigUISetVal(hDlg, hSrc, 'InitialState','xInitial')
% % slConfigUISetEnabled(hDlg, hSrc, 'InitialState', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'LimitDataPoints','on')
% slConfigUISetEnabled(hDlg, hSrc, 'LimitDataPoints', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MaxDataPoints','1000')
% slConfigUISetEnabled(hDlg, hSrc, 'MaxDataPoints', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SaveFormat','Array')
% slConfigUISetEnabled(hDlg, hSrc, 'SaveFormat', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SaveOutput','off')
% slConfigUISetEnabled(hDlg, hSrc, 'SaveOutput', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SaveState','off')
% slConfigUISetEnabled(hDlg, hSrc, 'SaveState', allowMods)
% StateSaveName is ignored when SaveState is 'off'
% slConfigUISetVal(hDlg, hSrc, 'StateSaveName','xout')
% slConfigUISetEnabled(hDlg, hSrc, 'StateSaveName', allowMods)
% OutputSaveName is ignored when SaveState is 'off'
% slConfigUISetVal(hDlg, hSrc, 'OutputSaveName','yout')
% slConfigUISetEnabled(hDlg, hSrc, 'OutputSaveName', allowMods)

% slConfigUISetVal(hDlg, hSrc, 'SignalLogging','on')
% slConfigUISetEnabled(hDlg, hSrc, 'SignalLogging', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'InspectSignalLogs','off')
% slConfigUISetEnabled(hDlg, hSrc, 'InspectSignalLogs', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SaveTime','off')
% slConfigUISetEnabled(hDlg, hSrc, 'SaveTime', allowMods)
% % TimeSaveName is ignored when SaveTime is 'off'
% % slConfigUISetVal(hDlg, hSrc, 'TimeSaveName','tout')
% % slConfigUISetEnabled(hDlg, hSrc, 'TimeSaveName', allowMods)
% 
% 
% slConfigUISetVal(hDlg, hSrc, 'SignalLoggingName','sigsOut')
% slConfigUISetEnabled(hDlg, hSrc, 'SignalLoggingName', allowMods)
% 
% % OutputOption is ignored when solver is Fixed-Step
% % slConfigUISetVal(hDlg, hSrc, 'OutputOption','RefineOutputTimes')
% % slConfigUISetEnabled(hDlg, hSrc, 'OutputOption', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'OutputTimes','[]')
% slConfigUISetEnabled(hDlg, hSrc, 'OutputTimes', allowMods)
% 
% % Refine is ignored when solver is Fixed-Step
% % slConfigUISetVal(hDlg, hSrc, 'Refine','1')
% % slConfigUISetEnabled(hDlg, hSrc, 'Refine', allowMods)
                                   
%% Optimization
 slConfigUISetVal(hDlg, hSrc, 'BlockReduction','on')
 slConfigUISetEnabled(hDlg, hSrc, 'BlockReduction', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'ConditionallyExecuteInputs','on')
 slConfigUISetEnabled(hDlg, hSrc, 'ConditionallyExecuteInputs', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'BooleanDataType','on')
 slConfigUISetEnabled(hDlg, hSrc, 'BooleanDataType', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'OptimizeBlockIOStorage','on')
 slConfigUISetEnabled(hDlg, hSrc, 'OptimizeBlockIOStorage', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'InlineParams','on')
 slConfigUISetEnabled(hDlg, hSrc, 'InlineParams', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'LifeSpan','5')
 slConfigUISetEnabled(hDlg, hSrc, 'LifeSpan', allowMods)
 

 slConfigUISetVal(hDlg, hSrc, 'InlinedParameterPlacement','NonHierarchical')
 slConfigUISetEnabled(hDlg, hSrc, 'InlinedParameterPlacement', allowMods)

 slConfigUISetVal(hDlg, hSrc, 'LocalBlockOutputs','on')
 slConfigUISetEnabled(hDlg, hSrc, 'LocalBlockOutputs', allowMods)

 slConfigUISetVal(hDlg, hSrc, 'BufferReuse','on')
 slConfigUISetEnabled(hDlg, hSrc, 'BufferReuse', allowMods)
 
 %slConfigUISetVal(hDlg, hSrc, 'EnforceIntegerDowncast','off')
 %slConfigUISetEnabled(hDlg, hSrc, 'EnforceIntegerDowncast', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'InlineInvariantSignals','on')
 slConfigUISetEnabled(hDlg, hSrc, 'InlineInvariantSignals', allowMods) 

 slConfigUISetVal(hDlg, hSrc, 'ExpressionFolding','on')
 slConfigUISetEnabled(hDlg, hSrc, 'ExpressionFolding', allowMods)

 
 slConfigUISetVal(hDlg, hSrc, 'ZeroExternalMemoryAtStartup','on')
 slConfigUISetEnabled(hDlg, hSrc, 'ZeroExternalMemoryAtStartup', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'InitFltsAndDblsToZero','off')
 slConfigUISetEnabled(hDlg, hSrc, 'InitFltsAndDblsToZero', allowMods)

 slConfigUISetVal(hDlg, hSrc, 'ZeroInternalMemoryAtStartup','on')
 slConfigUISetEnabled(hDlg, hSrc, 'ZeroInternalMemoryAtStartup', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'OptimizeModelRefInitCode','on')
 slConfigUISetEnabled(hDlg, hSrc, 'OptimizeModelRefInitCode', allowMods)

 
 slConfigUISetVal(hDlg, hSrc, 'EfficientFloat2IntCast','off')
 slConfigUISetEnabled(hDlg, hSrc, 'EfficientFloat2IntCast', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'NoFixptDivByZeroProtection','off')
 slConfigUISetEnabled(hDlg, hSrc, 'NoFixptDivByZeroProtection', allowMods) 

 
 slConfigUISetVal(hDlg, hSrc, 'StateBitsets','on')
 slConfigUISetEnabled(hDlg, hSrc, 'StateBitsets', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'UseTempVars','on')
 slConfigUISetEnabled(hDlg, hSrc, 'UseTempVars', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'DataBitsets','on')
 slConfigUISetEnabled(hDlg, hSrc, 'DataBitsets', allowMods) 

 
 slConfigUISetVal(hDlg, hSrc, 'SimCompilerOptimization','off')
 slConfigUISetEnabled(hDlg, hSrc, 'SimCompilerOptimization', allowMods)

 slConfigUISetVal(hDlg, hSrc, 'AccelVerboseBuild','off')
 slConfigUISetEnabled(hDlg, hSrc, 'AccelVerboseBuild', allowMods)
% 
% Mathworks use only
% slConfigUISetVal(hDlg, hSrc, 'FoldNonRolledExpr','on')
% slConfigUISetEnabled(hDlg, hSrc, 'FoldNonRolledExpr', allowMods)
%
% slConfigUISetVal(hDlg, hSrc, 'SystemCodeInlineAuto','off')
% slConfigUISetEnabled(hDlg, hSrc, 'SystemCodeInlineAuto', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'BufferReusableBoundary','on')
% slConfigUISetEnabled(hDlg, hSrc, 'BufferReusableBoundary', allowMods)  
% 
%% Diagnostics                                     
% slConfigUISetVal(hDlg, hSrc, 'RTPrefix','error')
% slConfigUISetEnabled(hDlg, hSrc, 'RTPrefix', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ConsistencyChecking','none')
% slConfigUISetEnabled(hDlg, hSrc, 'ConsistencyChecking', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ArrayBoundsChecking','none')
% slConfigUISetEnabled(hDlg, hSrc, 'ArrayBoundsChecking', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SignalInfNanChecking','none')
% slConfigUISetEnabled(hDlg, hSrc, 'SignalInfNanChecking', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ReadBeforeWriteMsg','UseLocalSettings')
% slConfigUISetEnabled(hDlg, hSrc, 'ReadBeforeWriteMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'WriteAfterWriteMsg','UseLocalSettings')
% slConfigUISetEnabled(hDlg, hSrc, 'WriteAfterWriteMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'WriteAfterReadMsg','UseLocalSettings')
% slConfigUISetEnabled(hDlg, hSrc, 'WriteAfterReadMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'AlgebraicLoopMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'AlgebraicLoopMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ArtificialAlgebraicLoopMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'ArtificialAlgebraicLoopMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CheckSSInitialOutputMsg','on')
% slConfigUISetEnabled(hDlg, hSrc, 'CheckSSInitialOutputMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CheckExecutionContextPreStartOutputMsg','on')
% slConfigUISetEnabled(hDlg, hSrc, 'CheckExecutionContextPreStartOutputMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CheckExecutionContextRuntimeOutputMsg','on')
% slConfigUISetEnabled(hDlg, hSrc, 'CheckExecutionContextRuntimeOutputMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SignalResolutionControl','TryResolveAllWithWarning')
% slConfigUISetEnabled(hDlg, hSrc, 'SignalResolutionControl', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'BlockPriorityViolationMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'BlockPriorityViolationMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MinStepSizeMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'MinStepSizeMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'TimeAdjustmentMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'TimeAdjustmentMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MaxConsecutiveZCsMsg','error')
% slConfigUISetEnabled(hDlg, hSrc, 'MaxConsecutiveZCsMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SolverPrmCheckMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'SolverPrmCheckMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'InheritedTsInSrcMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'InheritedTsInSrcMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'DiscreteInheritContinuousMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'DiscreteInheritContinuousMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MultiTaskDSMMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'MultiTaskDSMMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MultiTaskCondExecSysMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'MultiTaskCondExecSysMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MultiTaskRateTransMsg','error')
% slConfigUISetEnabled(hDlg, hSrc, 'MultiTaskRateTransMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SingleTaskRateTransMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'SingleTaskRateTransMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'TasksWithSamePriorityMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'TasksWithSamePriorityMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SigSpecEnsureSampleTimeMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'SigSpecEnsureSampleTimeMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CheckMatrixSingularityMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'CheckMatrixSingularityMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'IntegerOverflowMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'IntegerOverflowMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'Int32ToFloatConvMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'Int32ToFloatConvMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ParameterDowncastMsg','error')
% slConfigUISetEnabled(hDlg, hSrc, 'ParameterDowncastMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ParameterOverflowMsg','error')
% slConfigUISetEnabled(hDlg, hSrc, 'ParameterOverflowMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ParameterUnderflowMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'ParameterUnderflowMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ParameterPrecisionLossMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'ParameterPrecisionLossMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'UnderSpecifiedDataTypeMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'UnderSpecifiedDataTypeMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'UnnecessaryDatatypeConvMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'UnnecessaryDatatypeConvMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'VectorMatrixConversionMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'VectorMatrixConversionMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'InvalidFcnCallConnMsg','error')
% slConfigUISetEnabled(hDlg, hSrc, 'InvalidFcnCallConnMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'FcnCallInpInsideContextMsg','Use local settings')
% slConfigUISetEnabled(hDlg, hSrc, 'FcnCallInpInsideContextMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SignalLabelMismatchMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'SignalLabelMismatchMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'UnconnectedInputMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'UnconnectedInputMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'UnconnectedOutputMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'UnconnectedOutputMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'UnconnectedLineMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'UnconnectedLineMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SFcnCompatibilityMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'SFcnCompatibilityMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'UniqueDataStoreMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'UniqueDataStoreMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'BusObjectLabelMismatch','error')
% slConfigUISetEnabled(hDlg, hSrc, 'BusObjectLabelMismatch', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'RootOutportRequireBusObject','error')
% slConfigUISetEnabled(hDlg, hSrc, 'RootOutportRequireBusObject', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'AssertControl','UseLocalSettings')
% slConfigUISetEnabled(hDlg, hSrc, 'AssertControl', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'Echo','')
% slConfigUISetEnabled(hDlg, hSrc, 'Echo', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'EnableOverflowDetection','off')
% slConfigUISetEnabled(hDlg, hSrc, 'EnableOverflowDetection', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferenceIOMsg','none')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceIOMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferenceVersionMismatchMessage','none')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceVersionMismatchMessage', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferenceIOMismatchMessage','none')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceIOMismatchMessage', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferenceCSMismatchMessage','none')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceCSMismatchMessage', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferenceSimTargetVerbose','off')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceSimTargetVerbose', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'UnknownTsInhSupMsg','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'UnknownTsInhSupMsg', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferenceDataLoggingMessage','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceDataLoggingMessage', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferenceSymbolNameMessage','warning')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceSymbolNameMessage', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferenceExtraNoncontSigs','error')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceExtraNoncontSigs', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'StrictBusMsg','None')
% slConfigUISetEnabled(hDlg, hSrc, 'StrictBusMsg', allowMods)



%% Hardware Implementation                         
% 
% slConfigUISetVal(hDlg, hSrc, 'ProdHWDeviceType','32-bit Embedded Processor')
% slConfigUISetEnabled(hDlg, hSrc, 'ProdHWDeviceType', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ProdIntDivRoundTo','Zero')
% slConfigUISetEnabled(hDlg, hSrc, 'ProdIntDivRoundTo', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ProdEndianess','LittleEndian')
% slConfigUISetEnabled(hDlg, hSrc, 'ProdEndianess', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ProdEqTarget','on')
% slConfigUISetEnabled(hDlg, hSrc, 'ProdEqTarget', allowMods)



%% Model Referencing                               
% slConfigUISetVal(hDlg, hSrc, 'UpdateModelReferenceTargets','IfOutOfDateOrStructuralChange')
% slConfigUISetEnabled(hDlg, hSrc, 'UpdateModelReferenceTargets', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CheckModelReferenceTargetMessage','error')
% slConfigUISetEnabled(hDlg, hSrc, 'CheckModelReferenceTargetMessage', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferenceNumInstancesAllowed','Multi')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceNumInstancesAllowed', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelDependencies','')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelDependencies', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferencePassRootInputsByReference','on')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferencePassRootInputsByReference', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModelReferenceMinAlgLoopOccurrences','off')
% slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceMinAlgLoopOccurrences', allowMods)



%% Real-Time Workshop                              

slConfigUISetVal(hDlg, hSrc, 'TargetLang','C')
slConfigUISetEnabled(hDlg, hSrc, 'TargetLang', allowMods)

% slConfigUISetVal(hDlg, hSrc, 'TLCOptions','-p0 -aWarnNonSaturatedBlocks=0')
% slConfigUISetEnabled(hDlg, hSrc, 'TLCOptions', allowMods)

slConfigUISetVal(hDlg, hSrc, 'GenerateMakefile','off')
slConfigUISetEnabled(hDlg, hSrc, 'GenerateMakefile', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MakeCommand','make_rtw')
% slConfigUISetEnabled(hDlg, hSrc, 'MakeCommand', allowMods)
% % IB: Here is wher you can: set a custom template makefile
% % slConfigUISetVal(hDlg, hSrc, 'TemplateMakefile','bobcat_default_tmf')
% % slConfigUISetEnabled(hDlg, hSrc, 'TemplateMakefile', allowMods)
 
slConfigUISetVal(hDlg, hSrc, 'IgnoreCustomStorageClasses','off')
slConfigUISetEnabled(hDlg, hSrc, 'IgnoreCustomStorageClasses', allowMods)

slConfigUISetVal(hDlg, hSrc, 'GenCodeOnly','on')
slConfigUISetEnabled(hDlg, hSrc, 'GenCodeOnly', allowMods)
% Not in GUI
slConfigUISetVal(hDlg, hSrc, 'IncludeERTFirstTime','off')
slConfigUISetEnabled(hDlg, hSrc, 'IncludeERTFirstTime', allowMods)
 
slConfigUISetVal(hDlg, hSrc, 'ERTFirstTimeCompliant','off')
slConfigUISetEnabled(hDlg, hSrc, 'ERTFirstTimeCompliant', false)
% 
% slConfigUISetVal(hDlg, hSrc, 'SaveLog','off')
% slConfigUISetEnabled(hDlg, hSrc, 'SaveLog', allowMods)

%%RTW-Report
% slConfigUISetVal(hDlg, hSrc, 'GenerateReport','on')
% slConfigUISetEnabled(hDlg, hSrc, 'GenerateReport', allowMods)
%
% slConfigUISetVal(hDlg, hSrc, 'LaunchReport','on')
% slConfigUISetEnabled(hDlg, hSrc, 'LaunchReport', true)
%
% slConfigUISetVal(hDlg, hSrc, 'IncludeHyperlinkInReport','on')
% slConfigUISetEnabled(hDlg, hSrc, 'IncludeHyperlinkInReport', true)

%%RTW-Comments
slConfigUISetVal(hDlg, hSrc, 'GenerateComments','on')
slConfigUISetEnabled(hDlg, hSrc, 'GenerateComments', allowMods)

slConfigUISetVal(hDlg, hSrc, 'InsertBlockDesc','off')
slConfigUISetEnabled(hDlg, hSrc, 'InsertBlockDesc', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SimulinkBlockComments','on')
% slConfigUISetEnabled(hDlg, hSrc, 'SimulinkBlockComments', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ForceParamTrailComments','on')
% slConfigUISetEnabled(hDlg, hSrc, 'ForceParamTrailComments', allowMods)

% slConfigUISetVal(hDlg, hSrc, 'SFDataObjDesc','off')
% slConfigUISetEnabled(hDlg, hSrc, 'SFDataObjDesc', true)
%
% slConfigUISetVal(hDlg, hSrc, 'SimulinkDataObjDesc','on')
% slConfigUISetEnabled(hDlg, hSrc, 'SimulinkDataObjDesc', allowMods)
%
% slConfigUISetVal(hDlg, hSrc, 'ReqsInCode','off')
% slConfigUISetEnabled(hDlg, hSrc, 'ReqsInCode', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'EnableCustomComments','off')
% slConfigUISetEnabled(hDlg, hSrc, 'EnableCustomComments', allowMods)
%
% slConfigUISetVal(hDlg, hSrc, 'CustomCommentsFcn','')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomCommentsFcn', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ShowEliminatedStatement','off')
% slConfigUISetEnabled(hDlg, hSrc, 'ShowEliminatedStatement', true)


%%RTW-Symbols
% slConfigUISetVal(hDlg, hSrc, 'CustomSymbolStrGlobalVar','$R$N$M')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomSymbolStrGlobalVar', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CustomSymbolStrType','$N$R$M')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomSymbolStrType', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CustomSymbolStrField','$N$M')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomSymbolStrField', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CustomSymbolStrFcn','$R$N$M$F')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomSymbolStrFcn', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CustomSymbolStrBlkIO','rtb_$N$M')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomSymbolStrBlkIO', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CustomSymbolStrTmpVar','$N$M')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomSymbolStrTmpVar', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CustomSymbolStrMacro','$R$N$M')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomSymbolStrMacro', allowMods)
% 
slConfigUISetVal(hDlg, hSrc, 'MaxIdLength','31')
slConfigUISetEnabled(hDlg, hSrc, 'MaxIdLength', allowMods)

%slConfigUISetVal(hDlg, hSrc, 'InlinedPrmAccess','Literals')
%slConfigUISetEnabled(hDlg, hSrc, 'InlinedPrmAccess', allowMods)

% slConfigUISetVal(hDlg, hSrc, 'SignalNamingRule','Custom')
% slConfigUISetEnabled(hDlg, hSrc, 'SignalNamingRule', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'SignalNamingFcn','bobcat_naming')
% slConfigUISetEnabled(hDlg, hSrc, 'SignalNamingFcn', allowMods)
%
% slConfigUISetVal(hDlg, hSrc, 'ParamNamingRule','Custom')
% slConfigUISetEnabled(hDlg, hSrc, 'ParamNamingRule', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ParamNamingFcn','bobcat_naming')
% slConfigUISetEnabled(hDlg, hSrc, 'ParamNamingFcn', allowMods)
%
% slConfigUISetVal(hDlg, hSrc, 'DefineNamingRule','None')
% slConfigUISetEnabled(hDlg, hSrc, 'DefineNamingRule', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'DefineNamingFcn','')
% slConfigUISetEnabled(hDlg, hSrc, 'DefineNamingFcn', allowMods)
%
% slConfigUISetVal(hDlg, hSrc, 'IncHierarchyInIds','off')
% slConfigUISetEnabled(hDlg, hSrc, 'IncHierarchyInIds', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'IncDataTypeInIds','off')
% slConfigUISetEnabled(hDlg, hSrc, 'IncDataTypeInIds', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'PrefixModelToSubsysFcnNames','off')
% slConfigUISetEnabled(hDlg, hSrc, 'PrefixModelToSubsysFcnNames',
% allowMods)

%%RTW - Custom Code
% slConfigUISetVal(hDlg, hSrc, 'CustomSourceCode','')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomSourceCode', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CustomHeaderCode','')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomHeaderCode', allowMods)
%  
% slConfigUISetVal(hDlg, hSrc, 'CustomInitializer','')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomInitializer', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CustomTerminator','')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomTerminator', allowMods)
%
% slConfigUISetVal(hDlg, hSrc, 'CustomInclude','')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomInclude', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CustomSource','')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomSource', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'CustomLibrary','')
% slConfigUISetEnabled(hDlg, hSrc, 'CustomLibrary', allowMods)

%%RTW - Debug
 slConfigUISetVal(hDlg, hSrc, 'RTWVerbose','off')
 slConfigUISetEnabled(hDlg, hSrc, 'RTWVerbose', allowMods)
 
 slConfigUISetVal(hDlg, hSrc, 'RetainRTWFile','off')
 slConfigUISetEnabled(hDlg, hSrc, 'RetainRTWFile', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ProfileTLC','off')
% slConfigUISetEnabled(hDlg, hSrc, 'ProfileTLC', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'TLCDebug','off')
% slConfigUISetEnabled(hDlg, hSrc, 'TLCDebug', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'TLCCoverage','off')
% slConfigUISetEnabled(hDlg, hSrc, 'TLCCoverage', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'TLCAssert','off')
% slConfigUISetEnabled(hDlg, hSrc, 'TLCAssert', allowMods)
 
%%RTW - Interface
% slConfigUISetVal(hDlg, hSrc, 'GenFloatMathFcnCalls','ANSI_C')
% slConfigUISetEnabled(hDlg, hSrc, 'GenFloatMathFcnCalls', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'UtilityFuncGeneration','Auto')
% slConfigUISetEnabled(hDlg, hSrc, 'UtilityFuncGeneration', allowMods)
% 
slConfigUISetVal(hDlg, hSrc, 'PurelyIntegerCode','on')
slConfigUISetEnabled(hDlg, hSrc, 'PurelyIntegerCode', allowMods)
 
slConfigUISetVal(hDlg, hSrc, 'SupportNonFinite','off')
slConfigUISetEnabled(hDlg, hSrc, 'SupportNonFinite', allowMods)
 
slConfigUISetVal(hDlg, hSrc, 'SupportComplex','off')
slConfigUISetEnabled(hDlg, hSrc, 'SupportComplex', allowMods)

slConfigUISetVal(hDlg, hSrc, 'SupportAbsoluteTime','off')
slConfigUISetEnabled(hDlg, hSrc, 'SupportAbsoluteTime', allowMods)
 
slConfigUISetVal(hDlg, hSrc, 'SupportContinuousTime','off')
slConfigUISetEnabled(hDlg, hSrc, 'SupportContinuousTime', allowMods)
 
slConfigUISetVal(hDlg, hSrc, 'SupportNonInlinedSFcns','off')
slConfigUISetEnabled(hDlg, hSrc, 'SupportNonInlinedSFcns', allowMods)
 
slConfigUISetVal(hDlg, hSrc, 'GRTInterface','off')
slConfigUISetEnabled(hDlg, hSrc, 'GRTInterface', allowMods)

slConfigUISetVal(hDlg, hSrc, 'CombineOutputUpdateFcns','on')
slConfigUISetEnabled(hDlg, hSrc, 'CombineOutputUpdateFcns', allowMods)

slConfigUISetVal(hDlg, hSrc, 'IncludeMdlTerminateFcn','off')
slConfigUISetEnabled(hDlg, hSrc, 'IncludeMdlTerminateFcn', allowMods)
 
%slConfigUISetVal(hDlg, hSrc, 'MultiInstanceERTCode','off')
%slConfigUISetEnabled(hDlg, hSrc, 'MultiInstanceERTCode', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MultiInstanceErrorCode','Error')
% slConfigUISetEnabled(hDlg, hSrc, 'MultiInstanceErrorCode', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'RootIOFormat','Individual arguments')
% slConfigUISetEnabled(hDlg, hSrc, 'RootIOFormat', allowMods)

slConfigUISetVal(hDlg, hSrc, 'SuppressErrorStatus','on')
slConfigUISetEnabled(hDlg, hSrc, 'SuppressErrorStatus', allowMods)
 
slConfigUISetVal(hDlg, hSrc, 'GenerateErtSFunction','off')
slConfigUISetEnabled(hDlg, hSrc, 'GenerateErtSFunction', allowMods)
 
slConfigUISetVal(hDlg, hSrc, 'MatFileLogging','off')
slConfigUISetEnabled(hDlg, hSrc, 'MatFileLogging', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'LogVarNameModifier','rt_')
% slConfigUISetEnabled(hDlg, hSrc, 'LogVarNameModifier', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'RTWCAPISignals','off')
% slConfigUISetEnabled(hDlg, hSrc, 'RTWCAPISignals', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'RTWCAPIParams','off')
% slConfigUISetEnabled(hDlg, hSrc, 'RTWCAPIParams', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'RTWCAPIStates','off')
% slConfigUISetEnabled(hDlg, hSrc, 'RTWCAPIStates', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'GenerateASAP2','off')
% slConfigUISetEnabled(hDlg, hSrc, 'GenerateASAP2', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ExtMode','off')
% slConfigUISetEnabled(hDlg, hSrc, 'ExtMode', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ExtModeStaticAlloc','off')
% slConfigUISetEnabled(hDlg, hSrc, 'ExtModeStaticAlloc', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ExtModeTesting','off')
% slConfigUISetEnabled(hDlg, hSrc, 'ExtModeTesting', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ExtModeMexFile','ext_comm')
% slConfigUISetEnabled(hDlg, hSrc, 'ExtModeMexFile', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ExtModeMexArgs','')
% slConfigUISetEnabled(hDlg, hSrc, 'ExtModeMexArgs', allowMods)
 
%%RTW - Code Style
% 
% slConfigUISetVal(hDlg, hSrc, 'ParenthesesLevel','Nominal')
% slConfigUISetEnabled(hDlg, hSrc, 'ParenthesesLevel', allowMods)

%%RTW - Templates
slConfigUISetVal(hDlg, hSrc, 'ERTSrcFileBannerTemplate','bobcat_ert_template.cgt')
slConfigUISetEnabled(hDlg, hSrc, 'ERTSrcFileBannerTemplate', allowMods)
  
slConfigUISetVal(hDlg, hSrc, 'ERTHdrFileBannerTemplate','bobcat_ert_template.cgt')
slConfigUISetEnabled(hDlg, hSrc, 'ERTHdrFileBannerTemplate', allowMods)
  
slConfigUISetVal(hDlg, hSrc, 'ERTDataSrcFileTemplate','bobcat_ert_template.cgt')
slConfigUISetEnabled(hDlg, hSrc, 'ERTDataSrcFileTemplate', allowMods)
  
slConfigUISetVal(hDlg, hSrc, 'ERTDataHdrFileTemplate','bobcat_ert_template.cgt')
slConfigUISetEnabled(hDlg, hSrc, 'ERTDataHdrFileTemplate', allowMods)

% IB: Here is where you put the custom TLC file process
slConfigUISetVal(hDlg, hSrc, 'ERTCustomFileTemplate','bobcat_file_process.tlc')
slConfigUISetEnabled(hDlg, hSrc, 'ERTCustomFileTemplate', allowMods)
% IB - disabled main generation 
slConfigUISetVal(hDlg, hSrc, 'GenerateSampleERTMain','off')
slConfigUISetEnabled(hDlg, hSrc, 'GenerateSampleERTMain', false)

% slConfigUISetVal(hDlg, hSrc, 'TargetOS','BareBoardExample')
% slConfigUISetEnabled(hDlg, hSrc, 'TargetOS', false)

%%RTW - Data Placement
% slConfigUISetVal(hDlg, hSrc, 'GlobalDataDefinition','Auto')
% slConfigUISetEnabled(hDlg, hSrc, 'GlobalDataDefinition', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'DataDefinitionFile','global.c')
% slConfigUISetEnabled(hDlg, hSrc, 'DataDefinitionFile', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'GlobalDataReference','Auto')
% slConfigUISetEnabled(hDlg, hSrc, 'GlobalDataReference', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'DataReferenceFile','global.h')
% slConfigUISetEnabled(hDlg, hSrc, 'DataReferenceFile', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'IncludeFileDelimiter','Auto')
% slConfigUISetEnabled(hDlg, hSrc, 'IncludeFileDelimiter', allowMods)
 
% slConfigUISetVal(hDlg, hSrc, 'ModuleNamingRule','Unspecified')
% slConfigUISetEnabled(hDlg, hSrc, 'ModuleNamingRule', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ModuleName','')
% slConfigUISetEnabled(hDlg, hSrc, 'ModuleName', allowMods)
 
%%RTW - Data Type Replacement 
% slConfigUISetVal(hDlg, hSrc, 'EnableUserReplacementTypes','off')
% slConfigUISetEnabled(hDlg, hSrc, 'EnableUserReplacementTypes', allowMods)

% Replacement types
% F64=Simulink.AliasType; F64.BaseType =  'double';
% F32=Simulink.AliasType; F32.BaseType =  'single';
% S32=Simulink.AliasType; S32.BaseType =  'int32';
% tempstruct.double = 'F64';
% tempstruct.single = 'F32';
% tempstruct.int32 = 'S32';
% tempstruct.int16 = '';
% tempstruct.int8 = '';
% tempstruct.uint32 = '';
% tempstruct.uint16 = '';
% tempstruct.uint8 = '';
% tempstruct.boolean = '';
% tempstruct.int = '';
% tempstruct.uint = '';
% tempstruct.char = '';
% 
% slConfigUISetVal(hDlg, hSrc, 'ReplacementTypes', tempstruct)
% slConfigUISetEnabled(hDlg, hSrc, 'ReplacementTypes', allowMods)

%%RTW - Memory Sections
% slConfigUISetVal(hDlg, hSrc, 'MemSecPackage','--- None ---')
% slConfigUISetEnabled(hDlg, hSrc, 'MemSecPackage', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MemSecDataConstants','Default')
% slConfigUISetEnabled(hDlg, hSrc, 'MemSecDataConstants', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MemSecDataIO','Default')
% slConfigUISetEnabled(hDlg, hSrc, 'MemSecDataIO', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MemSecDataInternal','Default')
% slConfigUISetEnabled(hDlg, hSrc, 'MemSecDataInternal', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MemSecDataParameters','Default')
% slConfigUISetEnabled(hDlg, hSrc, 'MemSecDataParameters', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'MemSecFuncInitTerm','Default')
% slConfigUISetEnabled(hDlg, hSrc, 'MemSecFuncInitTerm', allowMods)








%% Stateflow Custom code properties
% slConfigUISetVal(hDlg, hSrc, 'CodeGenDirectory','')
% slConfigUISetEnabled(hDlg, hSrc, 'CodeGenDirectory', allowMods)



% Not in GUI
% slConfigUISetVal(hDlg, hSrc, 'PostCodeGenCommand','')
% slConfigUISetEnabled(hDlg, hSrc, 'PostCodeGenCommand', allowMods)
% 

% Mathworks use only
% slConfigUISetVal(hDlg, hSrc, 'ProcessScriptMode','Default')
% slConfigUISetEnabled(hDlg, hSrc, 'ProcessScriptMode', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ConfigurationMode','Optimized')
% slConfigUISetEnabled(hDlg, hSrc, 'ConfigurationMode', allowMods)
% 
% %IB: Here is wher you can: call the code gen hook file
% % slConfigUISetVal(hDlg, hSrc, 'ProcessScript','bobcat_ert_make_rtw_hook')
% % slConfigUISetEnabled(hDlg, hSrc, 'ProcessScript', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ConfigurationScript','')
% slConfigUISetEnabled(hDlg, hSrc, 'ConfigurationScript', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'ConfigAtBuild','off')
% slConfigUISetEnabled(hDlg, hSrc, 'ConfigAtBuild', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'IncludeRootSignalInRTWFile','off')
% slConfigUISetEnabled(hDlg, hSrc, 'IncludeRootSignalInRTWFile', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'IncludeVirtualBlocksInRTWFileBlockHierarchyMap','off')
% slConfigUISetEnabled(hDlg, hSrc, 'IncludeVirtualBlocksInRTWFileBlockHierarchyMap', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'IncludeBusHierarchyInRTWFileBlockHierarchyMap','off')
% slConfigUISetEnabled(hDlg, hSrc, 'IncludeBusHierarchyInRTWFileBlockHierarchyMap', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'IncludeRegionsInRTWFileBlockHierarchyMap','off')
% slConfigUISetEnabled(hDlg, hSrc, 'IncludeRegionsInRTWFileBlockHierarchyMap', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'Comment','')
% slConfigUISetEnabled(hDlg, hSrc, 'Comment', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'PreserveName','off')
% slConfigUISetEnabled(hDlg, hSrc, 'PreserveName', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'PreserveNameWithParent','off')
% slConfigUISetEnabled(hDlg, hSrc, 'PreserveNameWithParent', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'IncAutoGenComments','on')
% slConfigUISetEnabled(hDlg, hSrc, 'IncAutoGenComments', true)

%% Target                                          
% slConfigUISetVal(hDlg, hSrc, 'IsERTTarget','on')
% slConfigUISetEnabled(hDlg, hSrc, 'IsERTTarget', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'TargetFcnLib','ansi_tfl_tmw.mat')
% slConfigUISetEnabled(hDlg, hSrc, 'TargetFcnLib', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'TargetLibSuffix','')
% slConfigUISetEnabled(hDlg, hSrc, 'TargetLibSuffix', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'TargetPreCompLibLocation','')
% slConfigUISetEnabled(hDlg, hSrc, 'TargetPreCompLibLocation', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'GenerateFullHeader','on')
% slConfigUISetEnabled(hDlg, hSrc, 'GenerateFullHeader', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'GenerateTestInterfaces','off')
% slConfigUISetEnabled(hDlg, hSrc, 'GenerateTestInterfaces', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'IsPILTarget','off')
% slConfigUISetEnabled(hDlg, hSrc, 'IsPILTarget', allowMods)
 
  slConfigUISetVal(hDlg, hSrc, 'ModelReferenceCompliant','on')
  slConfigUISetEnabled(hDlg, hSrc, 'ModelReferenceCompliant', false)
% 
% slConfigUISetVal(hDlg, hSrc, 'ERTCustomFileBanners','on')
% slConfigUISetEnabled(hDlg, hSrc, 'ERTCustomFileBanners', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'RateGroupingCode','on')
% slConfigUISetEnabled(hDlg, hSrc, 'RateGroupingCode', allowMods)
% 
% slConfigUISetVal(hDlg, hSrc, 'InitialValueSource','Model')
% slConfigUISetEnabled(hDlg, hSrc, 'InitialValueSource', allowMods)
%
%Notes:(KEG)
%This change allows RTW to copy the model reference archive files over to
%the base model code generation directory for linking.
% set_param(hSrc,'TargetLibSuffix','.a');
%slConfigUISetVal(hDlg, hSrc, 'TargetLibSuffix', '.a')

% Notes: 
% I changed the fileseperator to a UNIX style fileseperator
% I escape the \ with a \\ as I cannot use a literal here.

% From:
% http://www.mathworks.com/access/helpdesk/help/toolbox/rtw/index.html?/access/helpdesk/help/toolbox/rtw/rn/bqoxby3-1.html
% Support for literal string added
% If a string constant is preceded by an L format specifier (as in L"string"), the Target Language Compiler performs no escape character processing on that string. This is useful for specifying PC-style paths without using double back slash characters.
% %addincludepath L"C:\mytlc"
% The following examples are equivalent.
%       L"d:\this\is\a\path"
%       "d:\\this\\is\\a\\path"




