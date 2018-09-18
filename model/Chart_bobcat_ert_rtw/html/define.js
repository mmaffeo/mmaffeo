function CodeDefine() { 
this.def = new Array();
this.def["Chart_DW"] = {file: "Chart_cpp.html",line:25,type:"var"};
this.def["Chart_U"] = {file: "Chart_cpp.html",line:28,type:"var"};
this.def["Chart_Y"] = {file: "Chart_cpp.html",line:31,type:"var"};
this.def["Chart_M_"] = {file: "Chart_cpp.html",line:34,type:"var"};
this.def["Chart_M"] = {file: "Chart_cpp.html",line:35,type:"var"};
this.def["Chart_step"] = {file: "Chart_cpp.html",line:38,type:"fcn"};
this.def["Chart_initialize"] = {file: "Chart_cpp.html",line:116,type:"fcn"};
this.def["DW_Chart_T"] = {file: "Chart_h.html",line:45,type:"type"};
this.def["ExtU_Chart_T"] = {file: "Chart_h.html",line:52,type:"type"};
this.def["ExtY_Chart_T"] = {file: "Chart_h.html",line:57,type:"type"};
this.def["RT_MODEL_Chart_T"] = {file: "Chart_types_h.html",line:18,type:"type"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:43,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:44,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:45,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:46,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:47,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:48,type:"type"};
this.def["int64_T"] = {file: "rtwtypes_h.html",line:49,type:"type"};
this.def["uint64_T"] = {file: "rtwtypes_h.html",line:50,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:51,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:52,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:58,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:59,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:60,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:61,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:62,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:63,type:"type"};
this.def["ulonglong_T"] = {file: "rtwtypes_h.html",line:64,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:65,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:88,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["Chart_cpp.html"] = "../Chart.cpp";
	this.html2Root["Chart_cpp.html"] = "Chart_cpp.html";
	this.html2SrcPath["Chart_h.html"] = "../Chart.h";
	this.html2Root["Chart_h.html"] = "Chart_h.html";
	this.html2SrcPath["Chart_private_h.html"] = "../Chart_private.h";
	this.html2Root["Chart_private_h.html"] = "Chart_private_h.html";
	this.html2SrcPath["Chart_types_h.html"] = "../Chart_types.h";
	this.html2Root["Chart_types_h.html"] = "Chart_types_h.html";
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
"Chart_cpp.html","Chart_h.html","Chart_private_h.html","Chart_types_h.html","rtwtypes_h.html","rtmodel_h.html"];
