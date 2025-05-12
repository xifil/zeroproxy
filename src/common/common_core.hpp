#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <MsHTML.h>
#include <MsHtmHst.h>
#include <ExDisp.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <corecrt_io.h>
#include <fcntl.h>
#include <shellapi.h>
#include <csetjmp>
#include <ShlObj.h>
#include <winternl.h>
#include <VersionHelpers.h>
#include <Psapi.h>
#include <urlmon.h>
#include <atlbase.h>
#include <atlsafe.h>
#include <iphlpapi.h>
#include <wincrypt.h>
#include <dwmapi.h>
#include <shellscalingapi.h>
#include <d3d11.h>
#include <d3d9.h>
#include <dxgi1_6.h>
#include <DbgHelp.h>

#pragma comment(lib, "DbgHelp.lib")
#pragma comment(lib, "ws2_32.lib")

// min and max is required by gdi, therefore NOMINMAX won't work
#ifdef max
#	undef max
#endif
#ifdef min
#	undef min
#endif
#undef GetObject

#include <cassert>
#include <cctype>
#include <climits>
#include <cstring>

#include <array>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <mutex>
#include <optional>
#include <queue>
#include <random>
#include <regex>
#include <sstream>
#include <thread>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

using namespace std::literals;

#define VT_GET(ptr, idx) (*(void***)(ptr))[idx]
#define PTR_AS(type, ptr) reinterpret_cast<type>((ptr))
#define DEREF_PTR_AS(type, ptr) *PTR_AS(type*, ptr)
#define ENUM_UNDER(val) static_cast<std::underlying_type<decltype(val)>::type>(val)
#define CLASS_ASSERT_SZ(cls, sz) static_assert(sizeof(cls) == sz, #cls " is not " #sz " bytes in size.")
#if defined(_WIN64)
#	define CLASS_ASSERT_SZ_64(cls, sz) CLASS_ASSERT_SZ(cls, sz)
#	define CLASS_ASSERT_SZ_86(cls, sz) ;
#	define FMT_PTR "{:016X}"
#else
#	define CLASS_ASSERT_SZ_64(cls, sz) ;
#	define CLASS_ASSERT_SZ_86(cls, sz) CLASS_ASSERT_SZ(cls, sz)
#	define FMT_PTR "{:08X}"
#endif

#define PROTECT_VOID(var_name) \
	static bool var_name = false; \
	if (var_name) { \
		return; \
	} \
	var_name = true;

std::uintptr_t operator"" _b(unsigned long long int val);
std::string and_rel(std::uintptr_t address);

inline HMODULE client_module = nullptr;
