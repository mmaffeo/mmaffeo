function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["rtDWork"] = {file: "C:\\Projects\\SVNrepo\\dibh-prod-esEMex\\model\\rtwdemo_hyperlinks_ert_rtw\\rtwdemo_hyperlinks.c",
	size: 43};
	 this.metricsArray.var["rtM_"] = {file: "C:\\Projects\\SVNrepo\\dibh-prod-esEMex\\model\\rtwdemo_hyperlinks_ert_rtw\\rtwdemo_hyperlinks.c",
	size: 8};
	 this.metricsArray.var["rtY"] = {file: "C:\\Projects\\SVNrepo\\dibh-prod-esEMex\\model\\rtwdemo_hyperlinks_ert_rtw\\rtwdemo_hyperlinks.c",
	size: 16};
	 this.metricsArray.fcn["fabs"] = {file: "C:\\Program Files\\MATLAB\\R2017b\\sys\\lcc\\include\\math.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtwdemo_hyperlinks.c:emfcn"] = {file: "C:\\Projects\\SVNrepo\\dibh-prod-esEMex\\model\\rtwdemo_hyperlinks_ert_rtw\\rtwdemo_hyperlinks.c",
	stack: 16,
	stackTotal: 16};
	 this.metricsArray.fcn["rtwdemo_hyperlinks.c:gfcn"] = {file: "C:\\Projects\\SVNrepo\\dibh-prod-esEMex\\model\\rtwdemo_hyperlinks_ert_rtw\\rtwdemo_hyperlinks.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtwdemo_hyperlinks.c:stgfcn"] = {file: "C:\\Projects\\SVNrepo\\dibh-prod-esEMex\\model\\rtwdemo_hyperlinks_ert_rtw\\rtwdemo_hyperlinks.c",
	stack: 8,
	stackTotal: 8};
	 this.metricsArray.fcn["rtwdemo_hyperlinks.c:ttfcn"] = {file: "C:\\Projects\\SVNrepo\\dibh-prod-esEMex\\model\\rtwdemo_hyperlinks_ert_rtw\\rtwdemo_hyperlinks.c",
	stack: 11,
	stackTotal: 11};
	 this.metricsArray.fcn["rtwdemo_hyperlinks_initialize"] = {file: "C:\\Projects\\SVNrepo\\dibh-prod-esEMex\\model\\rtwdemo_hyperlinks_ert_rtw\\rtwdemo_hyperlinks.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["rtwdemo_hyperlinks_step"] = {file: "C:\\Projects\\SVNrepo\\dibh-prod-esEMex\\model\\rtwdemo_hyperlinks_ert_rtw\\rtwdemo_hyperlinks.c",
	stack: 0,
	stackTotal: 16};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="rtwdemo_hyperlinks_metrics.html">Global Memory: 67(bytes) Maximum Stack: 16(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
