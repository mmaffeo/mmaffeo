function CodeDefine() { 
this.def = new Array();
this.def["cmdInverter"] = {file: "Chart1_cpp.html",line:26,type:"var"};
this.def["Chart1_DWork"] = {file: "Chart1_cpp.html",line:29,type:"var"};
this.def["Chart1_U"] = {file: "Chart1_cpp.html",line:32,type:"var"};
this.def["Chart1_Y"] = {file: "Chart1_cpp.html",line:35,type:"var"};
this.def["Chart1_step"] = {file: "Chart1_cpp.html",line:38,type:"fcn"};
this.def["Chart1_initialize"] = {file: "Chart1_cpp.html",line:148,type:"fcn"};
this.def["D_Work_Chart1"] = {file: "Chart1_h.html",line:39,type:"type"};
this.def["ExternalInputs_Chart1"] = {file: "Chart1_h.html",line:44,type:"type"};
this.def["ExternalOutputs_Chart1"] = {file: "Chart1_h.html",line:49,type:"type"};
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
	this.html2SrcPath["Chart1_cpp.html"] = "../Chart1.cpp";
	this.html2Root["Chart1_cpp.html"] = "Chart1_cpp.html";
	this.html2SrcPath["Chart1_h.html"] = "../Chart1.h";
	this.html2Root["Chart1_h.html"] = "Chart1_h.html";
	this.html2SrcPath["Chart1_private_h.html"] = "../Chart1_private.h";
	this.html2Root["Chart1_private_h.html"] = "Chart1_private_h.html";
	this.html2SrcPath["Chart1_types_h.html"] = "../Chart1_types.h";
	this.html2Root["Chart1_types_h.html"] = "Chart1_types_h.html";
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
"Chart1_cpp.html","Chart1_h.html","Chart1_private_h.html","Chart1_types_h.html","rtwtypes_h.html","rtmodel_h.html"];
