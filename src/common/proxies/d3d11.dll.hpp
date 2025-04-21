// ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile
#pragma once
#include "proxies/proxy_base.hpp"

extern "C" {
	HRESULT PROXY_API D3D11CreateDeviceAndSwapChain_ZP(IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc, IDXGISwapChain** ppSwapChain, ID3D11Device** ppDevice, D3D_FEATURE_LEVEL* pFeatureLevel, ID3D11DeviceContext** ppImmediateContext) {
		static auto func = proxy::get_export<decltype(&D3D11CreateDeviceAndSwapChain_ZP)>("d3d11.dll", "D3D11CreateDeviceAndSwapChain");
		return func(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
	}
#	pragma comment(linker, PROXY_EXPORT(D3D11CreateDeviceAndSwapChain, 48, 1))

	HRESULT PROXY_API D3D11CreateDevice_ZP(IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, ID3D11Device** ppDevice, D3D_FEATURE_LEVEL* pFeatureLevel, ID3D11DeviceContext** ppImmediateContext) {
		static auto func = proxy::get_export<decltype(&D3D11CreateDevice_ZP)>("d3d11.dll", "D3D11CreateDevice");
		return func(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);
	}
#	pragma comment(linker, PROXY_EXPORT(D3D11CreateDevice, 40, 2))
}
