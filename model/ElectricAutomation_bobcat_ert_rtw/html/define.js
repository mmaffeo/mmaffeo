function CodeDefine() { 
this.def = new Array();
this.def["Out2"] = {file: "ElectricAutomation_cpp.html",line:18,type:"var"};
this.def["cmdInverter"] = {file: "ElectricAutomation_cpp.html",line:19,type:"var"};
this.def["Out1"] = {file: "ElectricAutomation_cpp.html",line:20,type:"var"};
this.def["ElectricAutomation_DWork"] = {file: "ElectricAutomation_cpp.html",line:23,type:"var"};
this.def["ElectricAutomation_U"] = {file: "ElectricAutomation_cpp.html",line:26,type:"var"};
this.def["ElectricAutomation_Y"] = {file: "ElectricAutomation_cpp.html",line:29,type:"var"};
this.def["ElectricAutomation_M_"] = {file: "ElectricAutomation_cpp.html",line:32,type:"var"};
this.def["ElectricAutomation_M"] = {file: "ElectricAutomation_cpp.html",line:33,type:"var"};
this.def["rate_scheduler"] = {file: "ElectricAutomation_cpp.html",line:41,type:"fcn"};
this.def["ElectricAutomation_step"] = {file: "ElectricAutomation_cpp.html",line:54,type:"fcn"};
this.def["ElectricAutomation_initialize"] = {file: "ElectricAutomation_cpp.html",line:73,type:"fcn"};
this.def["D_Work_ElectricAutomation"] = {file: "ElectricAutomation_h.html",line:42,type:"type"};
this.def["ExternalInputs_ElectricAutomati"] = {file: "ElectricAutomation_h.html",line:49,type:"type"};
this.def["ExternalOutputs_ElectricAutomat"] = {file: "ElectricAutomation_h.html",line:54,type:"type"};
this.def["CANOpenMsgRPDO1"] = {file: "ElectricAutomation_types_h.html",line:38,type:"type"};
this.def["test"] = {file: "ElectricAutomation_types_h.html",line:48,type:"type"};
this.def["testOut"] = {file: "ElectricAutomation_types_h.html",line:58,type:"type"};
this.def["RT_MODEL_ElectricAutomation"] = {file: "ElectricAutomation_types_h.html",line:63,type:"type"};
this.def["Electri_ElectricAutomation_Init"] = {file: "mod_System_cpp.html",line:26,type:"fcn"};
this.def["ElectricAuto_ElectricAutomation"] = {file: "mod_System_cpp.html",line:35,type:"fcn"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:52,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:55,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:56,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:57,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:58,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:59,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:65,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:69,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:70,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:71,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:72,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:73,type:"type"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:83,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:84,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:85,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:86,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:87,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:88,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:89,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:90,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:96,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:97,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:98,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:99,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:100,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:101,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:102,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:103,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:104,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:124,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ElectricAutomation_cpp.html"] = "../ElectricAutomation.cpp";
	this.html2Root["ElectricAutomation_cpp.html"] = "ElectricAutomation_cpp.html";
	this.html2SrcPath["ElectricAutomation_h.html"] = "../ElectricAutomation.h";
	this.html2Root["ElectricAutomation_h.html"] = "ElectricAutomation_h.html";
	this.html2SrcPath["ElectricAutomation_private_h.html"] = "../ElectricAutomation_private.h";
	this.html2Root["ElectricAutomation_private_h.html"] = "ElectricAutomation_private_h.html";
	this.html2SrcPath["ElectricAutomation_types_h.html"] = "../ElectricAutomation_types.h";
	this.html2Root["ElectricAutomation_types_h.html"] = "ElectricAutomation_types_h.html";
	this.html2SrcPath["mod_System_cpp.html"] = "../mod_System.cpp";
	this.html2Root["mod_System_cpp.html"] = "mod_System_cpp.html";
	this.html2SrcPath["mod_System_h.html"] = "../mod_System.h";
	this.html2Root["mod_System_h.html"] = "mod_System_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.html2SrcPath["rtmodel_h.html"] = "../rtmodel.h";
	this.html2Root["rtmodel_h.html"] = "rtmodel_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ElectricAutomation_cpp.html","ElectricAutomation_h.html","ElectricAutomation_private_h.html","ElectricAutomation_types_h.html","mod_System_cpp.html","mod_System_h.html","rtwtypes_h.html","rtmodel_h.html"];
