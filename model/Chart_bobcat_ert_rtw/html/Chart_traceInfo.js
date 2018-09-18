function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "Chart"};
	this.sidHashMap["Chart"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "testmodel2017b:8725"};
	this.sidHashMap["testmodel2017b:8725"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<S1>:17"] = {sid: "testmodel2017b:8725:17"};
	this.sidHashMap["testmodel2017b:8725:17"] = {rtwname: "<S1>:17"};
	this.rtwnameHashMap["<S1>:18"] = {sid: "testmodel2017b:8725:18"};
	this.sidHashMap["testmodel2017b:8725:18"] = {rtwname: "<S1>:18"};
	this.rtwnameHashMap["<S1>:19"] = {sid: "testmodel2017b:8725:19"};
	this.sidHashMap["testmodel2017b:8725:19"] = {rtwname: "<S1>:19"};
	this.rtwnameHashMap["<S1>:21"] = {sid: "testmodel2017b:8725:21"};
	this.sidHashMap["testmodel2017b:8725:21"] = {rtwname: "<S1>:21"};
	this.rtwnameHashMap["<S1>:24"] = {sid: "testmodel2017b:8725:24"};
	this.sidHashMap["testmodel2017b:8725:24"] = {rtwname: "<S1>:24"};
	this.rtwnameHashMap["<S1>:3"] = {sid: "testmodel2017b:8725:3"};
	this.sidHashMap["testmodel2017b:8725:3"] = {rtwname: "<S1>:3"};
	this.rtwnameHashMap["<S1>:10"] = {sid: "testmodel2017b:8725:10"};
	this.sidHashMap["testmodel2017b:8725:10"] = {rtwname: "<S1>:10"};
	this.rtwnameHashMap["<S1>:15"] = {sid: "testmodel2017b:8725:15"};
	this.sidHashMap["testmodel2017b:8725:15"] = {rtwname: "<S1>:15"};
	this.rtwnameHashMap["<S1>:11"] = {sid: "testmodel2017b:8725:11"};
	this.sidHashMap["testmodel2017b:8725:11"] = {rtwname: "<S1>:11"};
	this.rtwnameHashMap["<S1>:14"] = {sid: "testmodel2017b:8725:14"};
	this.sidHashMap["testmodel2017b:8725:14"] = {rtwname: "<S1>:14"};
	this.rtwnameHashMap["<S1>:12"] = {sid: "testmodel2017b:8725:12"};
	this.sidHashMap["testmodel2017b:8725:12"] = {rtwname: "<S1>:12"};
	this.rtwnameHashMap["<S1>:13"] = {sid: "testmodel2017b:8725:13"};
	this.sidHashMap["testmodel2017b:8725:13"] = {rtwname: "<S1>:13"};
	this.rtwnameHashMap["<S1>:25"] = {sid: "testmodel2017b:8725:25"};
	this.sidHashMap["testmodel2017b:8725:25"] = {rtwname: "<S1>:25"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
