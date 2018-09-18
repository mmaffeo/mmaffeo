function myTestInfo = TestInfoHook()
myTestInfo{1} = IMT.TestInfo;
myTestInfo{1}.RelativeStartDirectory = './model';
myTestInfo{1}.rtw_generate_code_action = 'PPWSubsystemCodeGen(''MX_Gateway/MX_Gtwy_Control'')';
myTestInfo{1}.ModelName = 'MX_Gateway';
myTestInfo{1}.SupportedTestSuites = {'simulink_load' 'simulink_compile' 'rtw_generate_code' 'rtw_build_generated_code'};