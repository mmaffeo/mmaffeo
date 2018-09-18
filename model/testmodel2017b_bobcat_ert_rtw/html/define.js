function CodeDefine() { 
this.def = new Array();
this.def["cmdInverter"] = {file: "testmodel2017b_cpp.html",line:34,type:"var"};
this.def["testmodel2017b_B"] = {file: "testmodel2017b_cpp.html",line:37,type:"var"};
this.def["testmodel2017b_DWork"] = {file: "testmodel2017b_cpp.html",line:40,type:"var"};
this.def["testmodel2017b_M_"] = {file: "testmodel2017b_cpp.html",line:43,type:"var"};
this.def["testmodel2017b_M"] = {file: "testmodel2017b_cpp.html",line:44,type:"var"};
this.def["testmodel2017b_step"] = {file: "testmodel2017b_cpp.html",line:47,type:"fcn"};
this.def["testmodel2017b_initialize"] = {file: "testmodel2017b_cpp.html",line:387,type:"fcn"};
this.def["BlockIO_testmodel2017b_T"] = {file: "testmodel2017b_h.html",line:50,type:"type"};
this.def["D_Work_testmodel2017b_T"] = {file: "testmodel2017b_h.html",line:70,type:"type"};
this.def["RT_MODEL_testmodel2017b_T"] = {file: "testmodel2017b_types_h.html",line:18,type:"type"};
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
	this.html2SrcPath["testmodel2017b_cpp.html"] = "../testmodel2017b.cpp";
	this.html2Root["testmodel2017b_cpp.html"] = "testmodel2017b_cpp.html";
	this.html2SrcPath["testmodel2017b_h.html"] = "../testmodel2017b.h";
	this.html2Root["testmodel2017b_h.html"] = "testmodel2017b_h.html";
	this.html2SrcPath["testmodel2017b_private_h.html"] = "../testmodel2017b_private.h";
	this.html2Root["testmodel2017b_private_h.html"] = "testmodel2017b_private_h.html";
	this.html2SrcPath["testmodel2017b_types_h.html"] = "../testmodel2017b_types.h";
	this.html2Root["testmodel2017b_types_h.html"] = "testmodel2017b_types_h.html";
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
"testmodel2017b_cpp.html","testmodel2017b_h.html","testmodel2017b_private_h.html","testmodel2017b_types_h.html","rtwtypes_h.html","rtmodel_h.html"];
