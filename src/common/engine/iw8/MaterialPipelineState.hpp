#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/MaterialSerializedShader.hpp"

namespace iw8 {
	class MaterialPipelineState {
	public:
		std::uint32_t packet_size_;							// 0x0000
		std::uint32_t meta_data_size_;						// 0x0004
		std::uint8_t* packet_;								// 0x0008
		std::uint8_t* meta_data_;							// 0x0010
		MaterialSerializedShader* serialized_shaders_[4];	// 0x0018
		void* source_shaders_[4];							// 0x0038
		ID3D12PipelineState* derived_pso_;					// 0x0058
		ID3D12PipelineState* pso_;							// 0x0060
	};
	ENGINE_ASSERT_SZ(MaterialPipelineState, 0x0068);
}
