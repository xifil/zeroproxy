#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GfxConstantBuffer.hpp"

namespace iw8 {
	class MaterialConstantBufferDef {
	public:
		std::uint32_t vs_data_size_;
		std::uint32_t hs_data_size_;
		std::uint32_t ds_data_size_;
		std::uint32_t ps_data_size_;
		std::uint8_t* vs_data_;
		std::uint8_t* hs_data_;
		std::uint8_t* ds_data_;
		std::uint8_t* ps_data_;
		GfxConstantBuffer vs_constant_buffer_;
		GfxConstantBuffer hs_constant_buffer_;
		GfxConstantBuffer ds_constant_buffer_;
		GfxConstantBuffer ps_constant_buffer_;
	};
	ENGINE_ASSERT_SZ(MaterialConstantBufferDef, 0x0090);
}
