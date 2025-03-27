#include "proxy.h"

#include <windows.h>

// TODO: generate this and dll.def from a list of functions.

static FARPROC GetFileVersionInfoA_;
static FARPROC GetFileVersionInfoByHandle_;
static FARPROC GetFileVersionInfoExA_;
static FARPROC GetFileVersionInfoExW_;
static FARPROC GetFileVersionInfoSizeA_;
static FARPROC GetFileVersionInfoSizeExA_;
static FARPROC GetFileVersionInfoSizeExW_;
static FARPROC GetFileVersionInfoSizeW_;
static FARPROC GetFileVersionInfoW_;
static FARPROC VerFindFileA_;
static FARPROC VerFindFileW_;
static FARPROC VerInstallFileA_;
static FARPROC VerInstallFileW_;
static FARPROC VerLanguageNameA_;
static FARPROC VerLanguageNameW_;
static FARPROC VerQueryValueA_;
static FARPROC VerQueryValueW_;
static FARPROC Private1_;
static FARPROC SvchostPushServiceGlobals_;
static FARPROC WinHttpAddRequestHeaders_;
static FARPROC WinHttpAutoProxySvcMain_;
static FARPROC WinHttpCheckPlatform_;
static FARPROC WinHttpCloseHandle_;
static FARPROC WinHttpConnect_;
static FARPROC WinHttpConnectionDeletePolicyEntries_;
static FARPROC WinHttpConnectionDeleteProxyInfo_;
static FARPROC WinHttpConnectionFreeNameList_;
static FARPROC WinHttpConnectionFreeProxyInfo_;
static FARPROC WinHttpConnectionFreeProxyList_;
static FARPROC WinHttpConnectionGetNameList_;
static FARPROC WinHttpConnectionGetProxyInfo_;
static FARPROC WinHttpConnectionGetProxyList_;
static FARPROC WinHttpConnectionSetPolicyEntries_;
static FARPROC WinHttpConnectionSetProxyInfo_;
static FARPROC WinHttpConnectionUpdateIfIndexTable_;
static FARPROC WinHttpCrackUrl_;
static FARPROC WinHttpCreateProxyResolver_;
static FARPROC WinHttpCreateUrl_;
static FARPROC WinHttpDetectAutoProxyConfigUrl_;
static FARPROC WinHttpFreeProxyResult_;
static FARPROC WinHttpFreeProxyResultEx_;
static FARPROC WinHttpFreeProxySettings_;
static FARPROC WinHttpGetDefaultProxyConfiguration_;
static FARPROC WinHttpGetIEProxyConfigForCurrentUser_;
static FARPROC WinHttpGetProxyForUrl_;
static FARPROC WinHttpGetProxyForUrlEx_;
static FARPROC WinHttpGetProxyForUrlEx2_;
static FARPROC WinHttpGetProxyForUrlHvsi_;
static FARPROC WinHttpGetProxyResult_;
static FARPROC WinHttpGetProxyResultEx_;
static FARPROC WinHttpGetProxySettingsVersion_;
static FARPROC WinHttpGetTunnelSocket_;
static FARPROC WinHttpOpen_;
static FARPROC WinHttpOpenRequest_;
static FARPROC WinHttpPacJsWorkerMain_;
static FARPROC WinHttpProbeConnectivity_;
static FARPROC WinHttpQueryAuthSchemes_;
static FARPROC WinHttpQueryDataAvailable_;
static FARPROC WinHttpQueryHeaders_;
static FARPROC WinHttpQueryOption_;
static FARPROC WinHttpReadData_;
static FARPROC WinHttpReadProxySettings_;
static FARPROC WinHttpReadProxySettingsHvsi_;
static FARPROC WinHttpReceiveResponse_;
static FARPROC WinHttpResetAutoProxy_;
static FARPROC WinHttpSaveProxyCredentials_;
static FARPROC WinHttpSendRequest_;
static FARPROC WinHttpSetCredentials_;
static FARPROC WinHttpSetDefaultProxyConfiguration_;
static FARPROC WinHttpSetOption_;
static FARPROC WinHttpSetStatusCallback_;
static FARPROC WinHttpSetTimeouts_;
static FARPROC WinHttpTimeFromSystemTime_;
static FARPROC WinHttpTimeToSystemTime_;
static FARPROC WinHttpWebSocketClose_;
static FARPROC WinHttpWebSocketCompleteUpgrade_;
static FARPROC WinHttpWebSocketQueryCloseStatus_;
static FARPROC WinHttpWebSocketReceive_;
static FARPROC WinHttpWebSocketSend_;
static FARPROC WinHttpWebSocketShutdown_;
static FARPROC WinHttpWriteData_;
static FARPROC WinHttpWriteProxySettings_;

void load_functions(void *dll) {
	GetFileVersionInfoA_ = GetProcAddress((HMODULE) dll, "GetFileVersionInfoA");
	GetFileVersionInfoByHandle_ = GetProcAddress((HMODULE) dll, "GetFileVersionInfoByHandle");
	GetFileVersionInfoExA_ = GetProcAddress((HMODULE) dll, "GetFileVersionInfoExA");
	GetFileVersionInfoExW_ = GetProcAddress((HMODULE) dll, "GetFileVersionInfoExW");
	GetFileVersionInfoSizeA_ = GetProcAddress((HMODULE) dll, "GetFileVersionInfoSizeA");
	GetFileVersionInfoSizeExA_ = GetProcAddress((HMODULE) dll, "GetFileVersionInfoSizeExA");
	GetFileVersionInfoSizeExW_ = GetProcAddress((HMODULE) dll, "GetFileVersionInfoSizeExW");
	GetFileVersionInfoSizeW_ = GetProcAddress((HMODULE) dll, "GetFileVersionInfoSizeW");
	GetFileVersionInfoW_ = GetProcAddress((HMODULE) dll, "GetFileVersionInfoW");
	VerFindFileA_ = GetProcAddress((HMODULE) dll, "VerFindFileA");
	VerFindFileW_ = GetProcAddress((HMODULE) dll, "VerFindFileW");
	VerInstallFileA_ = GetProcAddress((HMODULE) dll, "VerInstallFileA");
	VerInstallFileW_ = GetProcAddress((HMODULE) dll, "VerInstallFileW");
	VerLanguageNameA_ = GetProcAddress((HMODULE) dll, "VerLanguageNameA");
	VerLanguageNameW_ = GetProcAddress((HMODULE) dll, "VerLanguageNameW");
	VerQueryValueA_ = GetProcAddress((HMODULE) dll, "VerQueryValueA");
	VerQueryValueW_ = GetProcAddress((HMODULE) dll, "VerQueryValueW");
	Private1_ = GetProcAddress((HMODULE) dll, "Private1");
	SvchostPushServiceGlobals_ = GetProcAddress((HMODULE) dll, "SvchostPushServiceGlobals");
	WinHttpAddRequestHeaders_ = GetProcAddress((HMODULE) dll, "WinHttpAddRequestHeaders");
	WinHttpAutoProxySvcMain_ = GetProcAddress((HMODULE) dll, "WinHttpAutoProxySvcMain");
	WinHttpCheckPlatform_ = GetProcAddress((HMODULE) dll, "WinHttpCheckPlatform");
	WinHttpCloseHandle_ = GetProcAddress((HMODULE) dll, "WinHttpCloseHandle");
	WinHttpConnect_ = GetProcAddress((HMODULE) dll, "WinHttpConnect");
	WinHttpConnectionDeletePolicyEntries_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionDeletePolicyEntries");
	WinHttpConnectionDeleteProxyInfo_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionDeleteProxyInfo");
	WinHttpConnectionFreeNameList_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionFreeNameList");
	WinHttpConnectionFreeProxyInfo_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionFreeProxyInfo");
	WinHttpConnectionFreeProxyList_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionFreeProxyList");
	WinHttpConnectionGetNameList_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionGetNameList");
	WinHttpConnectionGetProxyInfo_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionGetProxyInfo");
	WinHttpConnectionGetProxyList_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionGetProxyList");
	WinHttpConnectionSetPolicyEntries_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionSetPolicyEntries");
	WinHttpConnectionSetProxyInfo_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionSetProxyInfo");
	WinHttpConnectionUpdateIfIndexTable_ = GetProcAddress((HMODULE) dll, "WinHttpConnectionUpdateIfIndexTable");
	WinHttpCrackUrl_ = GetProcAddress((HMODULE) dll, "WinHttpCrackUrl");
	WinHttpCreateProxyResolver_ = GetProcAddress((HMODULE) dll, "WinHttpCreateProxyResolver");
	WinHttpCreateUrl_ = GetProcAddress((HMODULE) dll, "WinHttpCreateUrl");
	WinHttpDetectAutoProxyConfigUrl_ = GetProcAddress((HMODULE) dll, "WinHttpDetectAutoProxyConfigUrl");
	WinHttpFreeProxyResult_ = GetProcAddress((HMODULE) dll, "WinHttpFreeProxyResult");
	WinHttpFreeProxyResultEx_ = GetProcAddress((HMODULE) dll, "WinHttpFreeProxyResultEx");
	WinHttpFreeProxySettings_ = GetProcAddress((HMODULE) dll, "WinHttpFreeProxySettings");
	WinHttpGetDefaultProxyConfiguration_ = GetProcAddress((HMODULE) dll, "WinHttpGetDefaultProxyConfiguration");
	WinHttpGetIEProxyConfigForCurrentUser_ = GetProcAddress((HMODULE) dll, "WinHttpGetIEProxyConfigForCurrentUser");
	WinHttpGetProxyForUrl_ = GetProcAddress((HMODULE) dll, "WinHttpGetProxyForUrl");
	WinHttpGetProxyForUrlEx_ = GetProcAddress((HMODULE) dll, "WinHttpGetProxyForUrlEx");
	WinHttpGetProxyForUrlEx2_ = GetProcAddress((HMODULE) dll, "WinHttpGetProxyForUrlEx2");
	WinHttpGetProxyForUrlHvsi_ = GetProcAddress((HMODULE) dll, "WinHttpGetProxyForUrlHvsi");
	WinHttpGetProxyResult_ = GetProcAddress((HMODULE) dll, "WinHttpGetProxyResult");
	WinHttpGetProxyResultEx_ = GetProcAddress((HMODULE) dll, "WinHttpGetProxyResultEx");
	WinHttpGetProxySettingsVersion_ = GetProcAddress((HMODULE) dll, "WinHttpGetProxySettingsVersion");
	WinHttpGetTunnelSocket_ = GetProcAddress((HMODULE) dll, "WinHttpGetTunnelSocket");
	WinHttpOpen_ = GetProcAddress((HMODULE) dll, "WinHttpOpen");
	WinHttpOpenRequest_ = GetProcAddress((HMODULE) dll, "WinHttpOpenRequest");
	WinHttpPacJsWorkerMain_ = GetProcAddress((HMODULE) dll, "WinHttpPacJsWorkerMain");
	WinHttpProbeConnectivity_ = GetProcAddress((HMODULE) dll, "WinHttpProbeConnectivity");
	WinHttpQueryAuthSchemes_ = GetProcAddress((HMODULE) dll, "WinHttpQueryAuthSchemes");
	WinHttpQueryDataAvailable_ = GetProcAddress((HMODULE) dll, "WinHttpQueryDataAvailable");
	WinHttpQueryHeaders_ = GetProcAddress((HMODULE) dll, "WinHttpQueryHeaders");
	WinHttpQueryOption_ = GetProcAddress((HMODULE) dll, "WinHttpQueryOption");
	WinHttpReadData_ = GetProcAddress((HMODULE) dll, "WinHttpReadData");
	WinHttpReadProxySettings_ = GetProcAddress((HMODULE) dll, "WinHttpReadProxySettings");
	WinHttpReadProxySettingsHvsi_ = GetProcAddress((HMODULE) dll, "WinHttpReadProxySettingsHvsi");
	WinHttpReceiveResponse_ = GetProcAddress((HMODULE) dll, "WinHttpReceiveResponse");
	WinHttpResetAutoProxy_ = GetProcAddress((HMODULE) dll, "WinHttpResetAutoProxy");
	WinHttpSaveProxyCredentials_ = GetProcAddress((HMODULE) dll, "WinHttpSaveProxyCredentials");
	WinHttpSendRequest_ = GetProcAddress((HMODULE) dll, "WinHttpSendRequest");
	WinHttpSetCredentials_ = GetProcAddress((HMODULE) dll, "WinHttpSetCredentials");
	WinHttpSetDefaultProxyConfiguration_ = GetProcAddress((HMODULE) dll, "WinHttpSetDefaultProxyConfiguration");
	WinHttpSetOption_ = GetProcAddress((HMODULE) dll, "WinHttpSetOption");
	WinHttpSetStatusCallback_ = GetProcAddress((HMODULE) dll, "WinHttpSetStatusCallback");
	WinHttpSetTimeouts_ = GetProcAddress((HMODULE) dll, "WinHttpSetTimeouts");
	WinHttpTimeFromSystemTime_ = GetProcAddress((HMODULE) dll, "WinHttpTimeFromSystemTime");
	WinHttpTimeToSystemTime_ = GetProcAddress((HMODULE) dll, "WinHttpTimeToSystemTime");
	WinHttpWebSocketClose_ = GetProcAddress((HMODULE) dll, "WinHttpWebSocketClose");
	WinHttpWebSocketCompleteUpgrade_ = GetProcAddress((HMODULE) dll, "WinHttpWebSocketCompleteUpgrade");
	WinHttpWebSocketQueryCloseStatus_ = GetProcAddress((HMODULE) dll, "WinHttpWebSocketQueryCloseStatus");
	WinHttpWebSocketReceive_ = GetProcAddress((HMODULE) dll, "WinHttpWebSocketReceive");
	WinHttpWebSocketSend_ = GetProcAddress((HMODULE) dll, "WinHttpWebSocketSend");
	WinHttpWebSocketShutdown_ = GetProcAddress((HMODULE) dll, "WinHttpWebSocketShutdown");
	WinHttpWriteData_ = GetProcAddress((HMODULE) dll, "WinHttpWriteData");
	WinHttpWriteProxySettings_ = GetProcAddress((HMODULE) dll, "WinHttpWriteProxySettings");
}

extern "C" {
	INT_PTR proxy_GetFileVersionInfoA() { return GetFileVersionInfoA_(); }
	INT_PTR proxy_GetFileVersionInfoByHandle() { return GetFileVersionInfoByHandle_(); }
	INT_PTR proxy_GetFileVersionInfoExA() { return GetFileVersionInfoExA_(); }
	INT_PTR proxy_GetFileVersionInfoExW() { return GetFileVersionInfoExW_(); }
	INT_PTR proxy_GetFileVersionInfoSizeA() { return GetFileVersionInfoSizeA_(); }
	INT_PTR proxy_GetFileVersionInfoSizeExA() { return GetFileVersionInfoSizeExA_(); }
	INT_PTR proxy_GetFileVersionInfoSizeExW() { return GetFileVersionInfoSizeExW_(); }
	INT_PTR proxy_GetFileVersionInfoSizeW() { return GetFileVersionInfoSizeW_(); }
	INT_PTR proxy_GetFileVersionInfoW() { return GetFileVersionInfoW_(); }
	INT_PTR proxy_VerFindFileA() { return VerFindFileA_(); }
	INT_PTR proxy_VerFindFileW() { return VerFindFileW_(); }
	INT_PTR proxy_VerInstallFileA() { return VerInstallFileA_(); }
	INT_PTR proxy_VerInstallFileW() { return VerInstallFileW_(); }
	INT_PTR proxy_VerLanguageNameA() { return VerLanguageNameA_(); }
	INT_PTR proxy_VerLanguageNameW() { return VerLanguageNameW_(); }
	INT_PTR proxy_VerQueryValueA() { return VerQueryValueA_(); }
	INT_PTR proxy_VerQueryValueW() { return VerQueryValueW_(); }
	INT_PTR proxy_Private1() { return Private1_(); }
	INT_PTR proxy_SvchostPushServiceGlobals() { return SvchostPushServiceGlobals_(); }
	INT_PTR proxy_WinHttpAddRequestHeaders() { return WinHttpAddRequestHeaders_(); }
	INT_PTR proxy_WinHttpAutoProxySvcMain() { return WinHttpAutoProxySvcMain_(); }
	INT_PTR proxy_WinHttpCheckPlatform() { return WinHttpCheckPlatform_(); }
	INT_PTR proxy_WinHttpCloseHandle() { return WinHttpCloseHandle_(); }
	INT_PTR proxy_WinHttpConnect() { return WinHttpConnect_(); }
	INT_PTR proxy_WinHttpConnectionDeletePolicyEntries() { return WinHttpConnectionDeletePolicyEntries_(); }
	INT_PTR proxy_WinHttpConnectionDeleteProxyInfo() { return WinHttpConnectionDeleteProxyInfo_(); }
	INT_PTR proxy_WinHttpConnectionFreeNameList() { return WinHttpConnectionFreeNameList_(); }
	INT_PTR proxy_WinHttpConnectionFreeProxyInfo() { return WinHttpConnectionFreeProxyInfo_(); }
	INT_PTR proxy_WinHttpConnectionFreeProxyList() { return WinHttpConnectionFreeProxyList_(); }
	INT_PTR proxy_WinHttpConnectionGetNameList() { return WinHttpConnectionGetNameList_(); }
	INT_PTR proxy_WinHttpConnectionGetProxyInfo() { return WinHttpConnectionGetProxyInfo_(); }
	INT_PTR proxy_WinHttpConnectionGetProxyList() { return WinHttpConnectionGetProxyList_(); }
	INT_PTR proxy_WinHttpConnectionSetPolicyEntries() { return WinHttpConnectionSetPolicyEntries_(); }
	INT_PTR proxy_WinHttpConnectionSetProxyInfo() { return WinHttpConnectionSetProxyInfo_(); }
	INT_PTR proxy_WinHttpConnectionUpdateIfIndexTable() { return WinHttpConnectionUpdateIfIndexTable_(); }
	INT_PTR proxy_WinHttpCrackUrl() { return WinHttpCrackUrl_(); }
	INT_PTR proxy_WinHttpCreateProxyResolver() { return WinHttpCreateProxyResolver_(); }
	INT_PTR proxy_WinHttpCreateUrl() { return WinHttpCreateUrl_(); }
	INT_PTR proxy_WinHttpDetectAutoProxyConfigUrl() { return WinHttpDetectAutoProxyConfigUrl_(); }
	INT_PTR proxy_WinHttpFreeProxyResult() { return WinHttpFreeProxyResult_(); }
	INT_PTR proxy_WinHttpFreeProxyResultEx() { return WinHttpFreeProxyResultEx_(); }
	INT_PTR proxy_WinHttpFreeProxySettings() { return WinHttpFreeProxySettings_(); }
	INT_PTR proxy_WinHttpGetDefaultProxyConfiguration() { return WinHttpGetDefaultProxyConfiguration_(); }
	INT_PTR proxy_WinHttpGetIEProxyConfigForCurrentUser() { return WinHttpGetIEProxyConfigForCurrentUser_(); }
	INT_PTR proxy_WinHttpGetProxyForUrl() { return WinHttpGetProxyForUrl_(); }
	INT_PTR proxy_WinHttpGetProxyForUrlEx() { return WinHttpGetProxyForUrlEx_(); }
	INT_PTR proxy_WinHttpGetProxyForUrlEx2() { return WinHttpGetProxyForUrlEx2_(); }
	INT_PTR proxy_WinHttpGetProxyForUrlHvsi() { return WinHttpGetProxyForUrlHvsi_(); }
	INT_PTR proxy_WinHttpGetProxyResult() { return WinHttpGetProxyResult_(); }
	INT_PTR proxy_WinHttpGetProxyResultEx() { return WinHttpGetProxyResultEx_(); }
	INT_PTR proxy_WinHttpGetProxySettingsVersion() { return WinHttpGetProxySettingsVersion_(); }
	INT_PTR proxy_WinHttpGetTunnelSocket() { return WinHttpGetTunnelSocket_(); }
	INT_PTR proxy_WinHttpOpen() { return WinHttpOpen_(); }
	INT_PTR proxy_WinHttpOpenRequest() { return WinHttpOpenRequest_(); }
	INT_PTR proxy_WinHttpPacJsWorkerMain() { return WinHttpPacJsWorkerMain_(); }
	INT_PTR proxy_WinHttpProbeConnectivity() { return WinHttpProbeConnectivity_(); }
	INT_PTR proxy_WinHttpQueryAuthSchemes() { return WinHttpQueryAuthSchemes_(); }
	INT_PTR proxy_WinHttpQueryDataAvailable() { return WinHttpQueryDataAvailable_(); }
	INT_PTR proxy_WinHttpQueryHeaders() { return WinHttpQueryHeaders_(); }
	INT_PTR proxy_WinHttpQueryOption() { return WinHttpQueryOption_(); }
	INT_PTR proxy_WinHttpReadData() { return WinHttpReadData_(); }
	INT_PTR proxy_WinHttpReadProxySettings() { return WinHttpReadProxySettings_(); }
	INT_PTR proxy_WinHttpReadProxySettingsHvsi() { return WinHttpReadProxySettingsHvsi_(); }
	INT_PTR proxy_WinHttpReceiveResponse() { return WinHttpReceiveResponse_(); }
	INT_PTR proxy_WinHttpResetAutoProxy() { return WinHttpResetAutoProxy_(); }
	INT_PTR proxy_WinHttpSaveProxyCredentials() { return WinHttpSaveProxyCredentials_(); }
	INT_PTR proxy_WinHttpSendRequest() { return WinHttpSendRequest_(); }
	INT_PTR proxy_WinHttpSetCredentials() { return WinHttpSetCredentials_(); }
	INT_PTR proxy_WinHttpSetDefaultProxyConfiguration() { return WinHttpSetDefaultProxyConfiguration_(); }
	INT_PTR proxy_WinHttpSetOption() { return WinHttpSetOption_(); }
	INT_PTR proxy_WinHttpSetStatusCallback() { return WinHttpSetStatusCallback_(); }
	INT_PTR proxy_WinHttpSetTimeouts() { return WinHttpSetTimeouts_(); }
	INT_PTR proxy_WinHttpTimeFromSystemTime() { return WinHttpTimeFromSystemTime_(); }
	INT_PTR proxy_WinHttpTimeToSystemTime() { return WinHttpTimeToSystemTime_(); }
	INT_PTR proxy_WinHttpWebSocketClose() { return WinHttpWebSocketClose_(); }
	INT_PTR proxy_WinHttpWebSocketCompleteUpgrade() { return WinHttpWebSocketCompleteUpgrade_(); }
	INT_PTR proxy_WinHttpWebSocketQueryCloseStatus() { return WinHttpWebSocketQueryCloseStatus_(); }
	INT_PTR proxy_WinHttpWebSocketReceive() { return WinHttpWebSocketReceive_(); }
	INT_PTR proxy_WinHttpWebSocketSend() { return WinHttpWebSocketSend_(); }
	INT_PTR proxy_WinHttpWebSocketShutdown() { return WinHttpWebSocketShutdown_(); }
	INT_PTR proxy_WinHttpWriteData() { return WinHttpWriteData_(); }
	INT_PTR proxy_WinHttpWriteProxySettings() { return WinHttpWriteProxySettings_(); }
}