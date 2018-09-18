function CodeDefine() { 
this.def = new Array();
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:33,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:70,type:"fcn"};
this.def["rtDWork"] = {file: "rtwdemo_hyperlinks_c.html",line:26,type:"var"};
this.def["rtY"] = {file: "rtwdemo_hyperlinks_c.html",line:29,type:"var"};
this.def["rtM_"] = {file: "rtwdemo_hyperlinks_c.html",line:32,type:"var"};
this.def["rtM"] = {file: "rtwdemo_hyperlinks_c.html",line:33,type:"var"};
this.def["stgfcn"] = {file: "rtwdemo_hyperlinks_c.html",line:47,type:"fcn"};
this.def["ttfcn"] = {file: "rtwdemo_hyperlinks_c.html",line:60,type:"fcn"};
this.def["emfcn"] = {file: "rtwdemo_hyperlinks_c.html",line:87,type:"fcn"};
this.def["gfcn"] = {file: "rtwdemo_hyperlinks_c.html",line:102,type:"fcn"};
this.def["rtwdemo_hyperlinks_step"] = {file: "rtwdemo_hyperlinks_c.html",line:108,type:"fcn"};
this.def["rtwdemo_hyperlinks_initialize"] = {file: "rtwdemo_hyperlinks_c.html",line:180,type:"fcn"};
this.def["RT_MODEL"] = {file: "rtwdemo_hyperlinks_h.html",line:34,type:"type"};
this.def["D_Work"] = {file: "rtwdemo_hyperlinks_h.html",line:51,type:"type"};
this.def["ExternalOutputs"] = {file: "rtwdemo_hyperlinks_h.html",line:56,type:"type"};
this.def["rtCP_pooled_k0vK8itlPrU4"] = {file: "../../slprj/ert/_sharedutils/html/const_params_c.html",line:13,type:"var"};
this.def["int8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:42,type:"type"};
this.def["uint8_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:43,type:"type"};
this.def["int16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:44,type:"type"};
this.def["uint16_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:45,type:"type"};
this.def["int32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:46,type:"type"};
this.def["uint32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:47,type:"type"};
this.def["int64_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:48,type:"type"};
this.def["uint64_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:49,type:"type"};
this.def["real32_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:50,type:"type"};
this.def["real64_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:51,type:"type"};
this.def["real_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:57,type:"type"};
this.def["time_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:58,type:"type"};
this.def["boolean_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:59,type:"type"};
this.def["int_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:60,type:"type"};
this.def["uint_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:61,type:"type"};
this.def["ulong_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:62,type:"type"};
this.def["ulonglong_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:63,type:"type"};
this.def["char_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:64,type:"type"};
this.def["uchar_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:65,type:"type"};
this.def["byte_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:66,type:"type"};
this.def["pointer_T"] = {file: "../../slprj/ert/_sharedutils/html/rtwtypes_h.html",line:87,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["rtwdemo_hyperlinks_c.html"] = "../rtwdemo_hyperlinks.c";
	this.html2Root["rtwdemo_hyperlinks_c.html"] = "rtwdemo_hyperlinks_c.html";
	this.html2SrcPath["rtwdemo_hyperlinks_h.html"] = "../rtwdemo_hyperlinks.h";
	this.html2Root["rtwdemo_hyperlinks_h.html"] = "rtwdemo_hyperlinks_h.html";
	this.html2SrcPath["const_params_c.html"] = "../const_params.c";
	this.html2Root["const_params_c.html"] = "../../slprj/ert/_sharedutils/html/const_params_c.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "../../slprj/ert/_sharedutils/html/rtwtypes_h.html";
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
"ert_main_c.html","rtwdemo_hyperlinks_c.html","rtwdemo_hyperlinks_h.html","const_params_c.html","rtwtypes_h.html"];
