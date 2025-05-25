#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GfxStateBits.hpp"
#include "engine/iw8/MaterialPipelineState.hpp"
#include "engine/iw8/MaterialRenderTargetFormat.hpp"
#include "engine/iw8/MaterialShaderArgument.hpp"
#include "engine/iw8/enums/MaterialConstantLayout.hpp"
#include "engine/iw8/enums/MaterialStageConfig.hpp"
#include "engine/iw8/enums/MaterialTechniqueType.hpp"

namespace iw8 {
	class MaterialTechnique {
	public:
		const char* name_;									// 0x0000
		MaterialTechniqueType type_;						// 0x0008
		std::uint16_t flags_;								// 0x000C
		std::uint8_t pipeline_state_input_layout_count_;	// 0x000E
		std::uint8_t pipeline_state_map_[26];				// 0x000F
	private:
		char pad_0029[0x0007];								// 0x0029
	public:
		MaterialPipelineState* pipeline_states_;			// 0x0030
		std::uint8_t per_prim_arg_count_;					// 0x0038
		std::uint8_t per_obj_arg_count_;					// 0x0039
		std::uint8_t stable_arg_count_;						// 0x003A
		std::uint8_t never_arg_count_;						// 0x003B
		std::uint16_t per_prim_arg_size_;					// 0x003C
		std::uint16_t per_obj_arg_size_;					// 0x003E
		std::uint16_t stable_arg_size_;						// 0x0040
		std::uint8_t color_rt_count_;						// 0x0042
		MaterialRenderTargetFormat render_target_formats_;	// 0x0043
		std::uint64_t custom_buffer_flags_;					// 0x0048
		std::uint32_t custom_sampler_flags_;				// 0x0050
		MaterialConstantLayout precompiled_index_;			// 0x0054
		MaterialStageConfig stage_config_;					// 0x0055
	private:
		char pad_0056[0x0002];								// 0x0056
	public:
		GfxStateBits state_bits_;							// 0x0058
		MaterialShaderArgument* args_;						// 0x0068
	};
	ENGINE_ASSERT_SZ(MaterialTechnique, 0x0070);
}
