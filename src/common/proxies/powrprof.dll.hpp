// ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile
#pragma once
#include "proxies/proxy_base.hpp"

extern "C" {
	NTSTATUS PROXY_API CallNtPowerInformation_ZP(POWER_INFORMATION_LEVEL InformationLevel, PVOID InputBuffer, ULONG InputBufferLength, PVOID OutputBuffer, ULONG OutputBufferLength) {
		static auto func = proxy::get_export<decltype(&CallNtPowerInformation_ZP)>("powrprof.dll", "CallNtPowerInformation");
		return func(InformationLevel, InputBuffer, InputBufferLength, OutputBuffer, OutputBufferLength);
	}
#	pragma comment(linker, PROXY_EXPORT(CallNtPowerInformation, 20, 1))
}
