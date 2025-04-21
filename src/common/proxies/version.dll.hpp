// ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile
#pragma once
#include "proxies/proxy_base.hpp"

extern "C" {
	BOOL PROXY_API GetFileVersionInfoA_ZP(LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
		static auto func = proxy::get_export<decltype(&GetFileVersionInfoA_ZP)>("version.dll", "GetFileVersionInfoA");
		return func(lptstrFilename, dwHandle, dwLen, lpData);
	}
#	pragma comment(linker, PROXY_EXPORT(GetFileVersionInfoA, 16, 1))

	BOOL PROXY_API GetFileVersionInfoByHandle_ZP(DWORD dwFlags, HANDLE hFile, LPVOID* lplpData, PDWORD pdwLen) {
		static auto func = proxy::get_export<decltype(&GetFileVersionInfoByHandle_ZP)>("version.dll", "GetFileVersionInfoByHandle");
		return func(dwFlags, hFile, lplpData, pdwLen);
	}
#	pragma comment(linker, PROXY_EXPORT(GetFileVersionInfoByHandle, 16, 2))
	
	BOOL PROXY_API GetFileVersionInfoExA_ZP(DWORD dwFlags, LPCSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
		static auto func = proxy::get_export<decltype(&GetFileVersionInfoExA_ZP)>("version.dll", "GetFileVersionInfoExA");
		return func(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
	}
#	pragma comment(linker, PROXY_EXPORT(GetFileVersionInfoExA, 20, 3))
	
	BOOL PROXY_API GetFileVersionInfoExW_ZP(DWORD dwFlags, LPCWSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
		static auto func = proxy::get_export<decltype(&GetFileVersionInfoExW_ZP)>("version.dll", "GetFileVersionInfoExW");
		return func(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
	}
#	pragma comment(linker, PROXY_EXPORT(GetFileVersionInfoExW, 20, 4))
	
	DWORD PROXY_API GetFileVersionInfoSizeA_ZP(LPCSTR lptstrFilename, LPDWORD lpdwHandle) {
		static auto func = proxy::get_export<decltype(&GetFileVersionInfoSizeA_ZP)>("version.dll", "GetFileVersionInfoSizeA");
		return func(lptstrFilename, lpdwHandle);
	}
#	pragma comment(linker, PROXY_EXPORT(GetFileVersionInfoSizeA, 8, 5))
	
	DWORD PROXY_API GetFileVersionInfoSizeExA_ZP(DWORD dwFlags, LPCSTR lpwstrFilename, LPDWORD lpdwHandle) {
		static auto func = proxy::get_export<decltype(&GetFileVersionInfoSizeExA_ZP)>("version.dll", "GetFileVersionInfoSizeExA");
		return func(dwFlags, lpwstrFilename, lpdwHandle);
	}
#	pragma comment(linker, PROXY_EXPORT(GetFileVersionInfoSizeExA, 12, 6))
	
	DWORD PROXY_API GetFileVersionInfoSizeExW_ZP(DWORD dwFlags, LPCWSTR lpwstrFilename, LPDWORD lpdwHandle) {
		static auto func = proxy::get_export<decltype(&GetFileVersionInfoSizeExW_ZP)>("version.dll", "GetFileVersionInfoSizeExW");
		return func(dwFlags, lpwstrFilename, lpdwHandle);
	}
#	pragma comment(linker, PROXY_EXPORT(GetFileVersionInfoSizeExW, 12, 7))
	
	DWORD PROXY_API GetFileVersionInfoSizeW_ZP(LPCWSTR lptstrFilename, LPDWORD lpdwHandle) {
		static auto func = proxy::get_export<decltype(&GetFileVersionInfoSizeW_ZP)>("version.dll", "GetFileVersionInfoSizeW");
		return func(lptstrFilename, lpdwHandle);
	}
#	pragma comment(linker, PROXY_EXPORT(GetFileVersionInfoSizeW, 8, 8))
	
	BOOL PROXY_API GetFileVersionInfoW_ZP(LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData) {
		static auto func = proxy::get_export<decltype(&GetFileVersionInfoW_ZP)>("version.dll", "GetFileVersionInfoW");
		return func(lptstrFilename, dwHandle, dwLen, lpData);
	}
#	pragma comment(linker, PROXY_EXPORT(GetFileVersionInfoW, 16, 9))
	
	DWORD PROXY_API VerFindFileA_ZP(DWORD uFlags, LPCSTR szFileName, LPCSTR szWinDir, LPCSTR szAppDir, LPSTR szCurDir, PUINT puCurDirLen, LPSTR szDestDir, PUINT puDestDirLen) {
		static auto func = proxy::get_export<decltype(&VerFindFileA_ZP)>("version.dll", "VerFindFileA");
		return func(uFlags, szFileName, szWinDir, szAppDir, szCurDir, puCurDirLen, szDestDir, puDestDirLen);
	}
#	pragma comment(linker, PROXY_EXPORT(VerFindFileA, 32, 10))
	
	DWORD PROXY_API VerFindFileW_ZP(DWORD uFlags, LPCWSTR szFileName, LPCWSTR szWinDir, LPCWSTR szAppDir, LPWSTR szCurDir, PUINT puCurDirLen, LPWSTR szDestDir, PUINT puDestDirLen) {
		static auto func = proxy::get_export<decltype(&VerFindFileW_ZP)>("version.dll", "VerFindFileW");
		return func(uFlags, szFileName, szWinDir, szAppDir, szCurDir, puCurDirLen, szDestDir, puDestDirLen);
	}
#	pragma comment(linker, PROXY_EXPORT(VerFindFileW, 32, 11))
	
	DWORD PROXY_API VerInstallFileA_ZP(DWORD uFlags, LPCSTR szSrcFileName, LPCSTR szDestFileName, LPCSTR szSrcDir, LPCSTR szDestDir, LPCSTR szCurDir, LPSTR szTmpFile, PUINT puTmpFileLen) {
		static auto func = proxy::get_export<decltype(&VerInstallFileA_ZP)>("version.dll", "VerInstallFileA");
		return func(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile, puTmpFileLen);
	}
#	pragma comment(linker, PROXY_EXPORT(VerInstallFileA, 32, 12))
	
	DWORD PROXY_API VerInstallFileW_ZP(DWORD uFlags, LPCWSTR szSrcFileName, LPCWSTR szDestFileName, LPCWSTR szSrcDir, LPCWSTR szDestDir, LPCWSTR szCurDir, LPWSTR szTmpFile, PUINT puTmpFileLen) {
		static auto func = proxy::get_export<decltype(&VerInstallFileW_ZP)>("version.dll", "VerInstallFileW");
		return func(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile, puTmpFileLen);
	}
#	pragma comment(linker, PROXY_EXPORT(VerInstallFileW, 32, 13))
	
	DWORD PROXY_API VerLanguageNameA_ZP(DWORD wLang, LPSTR szLang, DWORD cchLang) {
		static auto func = proxy::get_export<decltype(&VerLanguageNameA_ZP)>("version.dll", "VerLanguageNameA");
		return func(wLang, szLang, cchLang);
	}
#	pragma comment(linker, PROXY_EXPORT(VerLanguageNameA, 12, 14))
	
	DWORD PROXY_API VerLanguageNameW_ZP(DWORD wLang, LPWSTR szLang, DWORD cchLang) {
		static auto func = proxy::get_export<decltype(&VerLanguageNameW_ZP)>("version.dll", "VerLanguageNameW");
		return func(wLang, szLang, cchLang);
	}
#	pragma comment(linker, PROXY_EXPORT(VerLanguageNameW, 12, 15))
	
	BOOL PROXY_API VerQueryValueA_ZP(LPCVOID pBlock, LPCSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen) {
		static auto func = proxy::get_export<decltype(&VerQueryValueA_ZP)>("version.dll", "VerQueryValueA");
		return func(pBlock, lpSubBlock, lplpBuffer, puLen);
	}
#	pragma comment(linker, PROXY_EXPORT(VerQueryValueA, 16, 16))
	
	BOOL PROXY_API VerQueryValueW_ZP(LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen) {
		static auto func = proxy::get_export<decltype(&VerQueryValueW_ZP)>("version.dll", "VerQueryValueW");
		return func(pBlock, lpSubBlock, lplpBuffer, puLen);
	}
#	pragma comment(linker, PROXY_EXPORT(VerQueryValueW, 16, 17))
}
