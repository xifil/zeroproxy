// ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile
#pragma once
#include "proxies/proxy_base.hpp"

extern "C" {
	BOOL PROXY_API EmptyWorkingSet_ZP(HANDLE hProcess) {
		static auto func = proxy::get_export<decltype(&EmptyWorkingSet_ZP)>("psapi.dll", "EmptyWorkingSet");
		return func(hProcess);
	}
#	pragma comment(linker, PROXY_EXPORT(EmptyWorkingSet, 4, 1))

	BOOL PROXY_API EnumDeviceDrivers_ZP(LPVOID* lpImageBase, DWORD cb, LPDWORD lpcbNeeded) {
		static auto func = proxy::get_export<decltype(&EnumDeviceDrivers_ZP)>("psapi.dll", "EnumDeviceDrivers");
		return func(lpImageBase, cb, lpcbNeeded);
	}
#	pragma comment(linker, PROXY_EXPORT(EnumDeviceDrivers, 12, 2))

	BOOL PROXY_API EnumPageFilesA_ZP(PENUM_PAGE_FILE_CALLBACKA pCallBackRoutine, LPVOID pContext) {
		static auto func = proxy::get_export<decltype(&EnumPageFilesA_ZP)>("psapi.dll", "EnumPageFilesA");
		return func(pCallBackRoutine, pContext);
	}
#	pragma comment(linker, PROXY_EXPORT(EnumPageFilesA, 8, 3))

	BOOL PROXY_API EnumPageFilesW_ZP(PENUM_PAGE_FILE_CALLBACKW pCallBackRoutine, LPVOID pContext) {
		static auto func = proxy::get_export<decltype(&EnumPageFilesW_ZP)>("psapi.dll", "EnumPageFilesW");
		return func(pCallBackRoutine, pContext);
	}
#	pragma comment(linker, PROXY_EXPORT(EnumPageFilesW, 8, 4))

	BOOL PROXY_API EnumProcessModules_ZP(HANDLE hProcess, HMODULE* lphModule, DWORD cb, LPDWORD lpcbNeeded) {
		static auto func = proxy::get_export<decltype(&EnumProcessModules_ZP)>("psapi.dll", "EnumProcessModules");
		return func(hProcess, lphModule, cb, lpcbNeeded);
	}
#	pragma comment(linker, PROXY_EXPORT(EnumProcessModules, 16, 5))

	BOOL PROXY_API EnumProcessModulesEx_ZP(HANDLE hProcess, HMODULE* lphModule, DWORD cb, LPDWORD lpcbNeeded, DWORD dwFilterFlag) {
		static auto func = proxy::get_export<decltype(&EnumProcessModulesEx_ZP)>("psapi.dll", "EnumProcessModulesEx");
		return func(hProcess, lphModule, cb, lpcbNeeded, dwFilterFlag);
	}
#	pragma comment(linker, PROXY_EXPORT(EnumProcessModulesEx, 20, 6))

	BOOL PROXY_API EnumProcesses_ZP(DWORD* lpidProcess, DWORD cb, LPDWORD lpcbNeeded) {
		static auto func = proxy::get_export<decltype(&EnumProcesses_ZP)>("psapi.dll", "EnumProcesses");
		return func(lpidProcess, cb, lpcbNeeded);
	}
#	pragma comment(linker, PROXY_EXPORT(EnumProcesses, 12, 7))

	DWORD PROXY_API GetDeviceDriverBaseNameA_ZP(LPVOID ImageBase, LPSTR lpFilename, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetDeviceDriverBaseNameA_ZP)>("psapi.dll", "GetDeviceDriverBaseNameA");
		return func(ImageBase, lpFilename, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetDeviceDriverBaseNameA, 12, 8))

	DWORD PROXY_API GetDeviceDriverBaseNameW_ZP(LPVOID ImageBase, LPWSTR lpBaseName, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetDeviceDriverBaseNameW_ZP)>("psapi.dll", "GetDeviceDriverBaseNameW");
		return func(ImageBase, lpBaseName, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetDeviceDriverBaseNameW, 12, 9))

	DWORD PROXY_API GetDeviceDriverFileNameA_ZP(LPVOID ImageBase, LPSTR lpFilename, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetDeviceDriverFileNameA_ZP)>("psapi.dll", "GetDeviceDriverFileNameA");
		return func(ImageBase, lpFilename, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetDeviceDriverFileNameA, 12, 10))

	DWORD PROXY_API GetDeviceDriverFileNameW_ZP(LPVOID ImageBase, LPWSTR lpFilename, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetDeviceDriverFileNameW_ZP)>("psapi.dll", "GetDeviceDriverFileNameW");
		return func(ImageBase, lpFilename, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetDeviceDriverFileNameW, 12, 11))

	DWORD PROXY_API GetMappedFileNameA_ZP(HANDLE hProcess, LPVOID lpv, LPSTR lpFilename, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetMappedFileNameA_ZP)>("psapi.dll", "GetMappedFileNameA");
		return func(hProcess, lpv, lpFilename, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetMappedFileNameA, 16, 12))

	DWORD PROXY_API GetMappedFileNameW_ZP(HANDLE hProcess, LPVOID lpv, LPWSTR lpFilename, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetMappedFileNameW_ZP)>("psapi.dll", "GetMappedFileNameW");
		return func(hProcess, lpv, lpFilename, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetMappedFileNameW, 16, 13))

	DWORD PROXY_API GetModuleBaseNameA_ZP(HANDLE hProcess, HMODULE hModule, LPSTR lpBaseName, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetModuleBaseNameA_ZP)>("psapi.dll", "GetModuleBaseNameA");
		return func(hProcess, hModule, lpBaseName, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetModuleBaseNameA, 16, 14))

	DWORD PROXY_API GetModuleBaseNameW_ZP(HANDLE hProcess, HMODULE hModule, LPWSTR lpBaseName, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetModuleBaseNameW_ZP)>("psapi.dll", "GetModuleBaseNameW");
		return func(hProcess, hModule, lpBaseName, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetModuleBaseNameW, 16, 15))

	DWORD PROXY_API GetModuleFileNameExA_ZP(HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetModuleFileNameExA_ZP)>("psapi.dll", "GetModuleFileNameExA");
		return func(hProcess, hModule, lpFilename, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetModuleFileNameExA, 16, 16))

	DWORD PROXY_API GetModuleFileNameExW_ZP(HANDLE hProcess, HMODULE hModule, LPWSTR lpFilename, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetModuleFileNameExW_ZP)>("psapi.dll", "GetModuleFileNameExW");
		return func(hProcess, hModule, lpFilename, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetModuleFileNameExW, 16, 17))

	BOOL PROXY_API GetModuleInformation_ZP(HANDLE hProcess, HMODULE hModule, LPMODULEINFO lpmodinfo, DWORD cb) {
		static auto func = proxy::get_export<decltype(&GetModuleInformation_ZP)>("psapi.dll", "GetModuleInformation");
		return func(hProcess, hModule, lpmodinfo, cb);
	}
#	pragma comment(linker, PROXY_EXPORT(GetModuleInformation, 16, 18))

	BOOL PROXY_API GetPerformanceInfo_ZP(PPERFORMANCE_INFORMATION pPerformanceInformation, DWORD cb) {
		static auto func = proxy::get_export<decltype(&GetPerformanceInfo_ZP)>("psapi.dll", "GetPerformanceInfo");
		return func(pPerformanceInformation, cb);
	}
#	pragma comment(linker, PROXY_EXPORT(GetPerformanceInfo, 8, 19))

	DWORD PROXY_API GetProcessImageFileNameA_ZP(HANDLE hProcess, LPSTR lpImageFileName, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetProcessImageFileNameA_ZP)>("psapi.dll", "GetProcessImageFileNameA");
		return func(hProcess, lpImageFileName, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetProcessImageFileNameA, 12, 20))

	DWORD PROXY_API GetProcessImageFileNameW_ZP(HANDLE hProcess, LPWSTR lpImageFileName, DWORD nSize) {
		static auto func = proxy::get_export<decltype(&GetProcessImageFileNameW_ZP)>("psapi.dll", "GetProcessImageFileNameW");
		return func(hProcess, lpImageFileName, nSize);
	}
#	pragma comment(linker, PROXY_EXPORT(GetProcessImageFileNameW, 12, 21))

	BOOL PROXY_API GetProcessMemoryInfo_ZP(HANDLE Process, PPROCESS_MEMORY_COUNTERS ppsmemCounters, DWORD cb) {
		static auto func = proxy::get_export<decltype(&GetProcessMemoryInfo_ZP)>("psapi.dll", "GetProcessMemoryInfo");
		return func(Process, ppsmemCounters, cb);
	}
#	pragma comment(linker, PROXY_EXPORT(GetProcessMemoryInfo, 12, 22))

	BOOL PROXY_API GetWsChanges_ZP(HANDLE hProcess, PPSAPI_WS_WATCH_INFORMATION lpWatchInfo, DWORD cb) {
		static auto func = proxy::get_export<decltype(&GetWsChanges_ZP)>("psapi.dll", "GetWsChanges");
		return func(hProcess, lpWatchInfo, cb);
	}
#	pragma comment(linker, PROXY_EXPORT(GetWsChanges, 12, 23))

	BOOL PROXY_API GetWsChangesEx_ZP(HANDLE hProcess, PPSAPI_WS_WATCH_INFORMATION_EX lpWatchInfoEx, PDWORD cb) {
		static auto func = proxy::get_export<decltype(&GetWsChangesEx_ZP)>("psapi.dll", "GetWsChangesEx");
		return func(hProcess, lpWatchInfoEx, cb);
	}
#	pragma comment(linker, PROXY_EXPORT(GetWsChangesEx, 12, 24))

	BOOL PROXY_API InitializeProcessForWsWatch_ZP(HANDLE hProcess) {
		static auto func = proxy::get_export<decltype(&InitializeProcessForWsWatch_ZP)>("psapi.dll", "InitializeProcessForWsWatch");
		return func(hProcess);
	}
#	pragma comment(linker, PROXY_EXPORT(InitializeProcessForWsWatch, 4, 25))

	BOOL PROXY_API QueryWorkingSet_ZP(HANDLE hProcess, PVOID pv, DWORD cb) {
		static auto func = proxy::get_export<decltype(&QueryWorkingSet_ZP)>("psapi.dll", "QueryWorkingSet");
		return func(hProcess, pv, cb);
	}
#	pragma comment(linker, PROXY_EXPORT(QueryWorkingSet, 12, 26))

	BOOL PROXY_API QueryWorkingSetEx_ZP(HANDLE hProcess, PVOID pv, DWORD cb) {
		static auto func = proxy::get_export<decltype(&QueryWorkingSetEx_ZP)>("psapi.dll", "QueryWorkingSetEx");
		return func(hProcess, pv, cb);
	}
#	pragma comment(linker, PROXY_EXPORT(QueryWorkingSetEx, 12, 27))
}
