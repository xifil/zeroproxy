// ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile
#pragma once
#include "proxies/proxy_base.hpp"

#include <Xinput.h>

extern "C" {
	BOOL PROXY_API DllMain_ZP(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
		static auto func = proxy::get_export<decltype(&DllMain_ZP)>("XInput9_1_0.dll", "DllMain");
		return func(hinstDLL, fdwReason, lpvReserved);
	}
#	pragma comment(linker, PROXY_EXPORT(DllMain, 12, 1))

	DWORD PROXY_API XInputGetCapabilities_ZP(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES* pCapabilities) {
		static auto func = proxy::get_export<decltype(&XInputGetCapabilities_ZP)>("XInput9_1_0.dll", "XInputGetCapabilities");
		return func(dwUserIndex, dwFlags, pCapabilities);
	}
#	pragma comment(linker, PROXY_EXPORT(XInputGetCapabilities, 12, 2))
	
	DWORD PROXY_API XInputGetDSoundAudioDeviceGuids_ZP(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid) {
		static auto func = proxy::get_export<decltype(&XInputGetDSoundAudioDeviceGuids_ZP)>("XInput9_1_0.dll", "XInputGetDSoundAudioDeviceGuids");
		return func(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
	}
#	pragma comment(linker, PROXY_EXPORT(XInputGetDSoundAudioDeviceGuids, 12, 3))
	
	DWORD PROXY_API XInputGetState_ZP(DWORD dwUserIndex, XINPUT_STATE* pState) {
		static auto func = proxy::get_export<decltype(&XInputGetState_ZP)>("XInput9_1_0.dll", "XInputGetState");
		return func(dwUserIndex, pState);
	}
#	pragma comment(linker, PROXY_EXPORT(XInputGetState, 8, 4))
	
	DWORD PROXY_API XInputSetState_ZP(DWORD dwUserIndex, XINPUT_VIBRATION* pVibration) {
		static auto func = proxy::get_export<decltype(&XInputSetState_ZP)>("XInput9_1_0.dll", "XInputSetState");
		return func(dwUserIndex, pVibration);
	}
#	pragma comment(linker, PROXY_EXPORT(XInputSetState, 8, 5))
}
