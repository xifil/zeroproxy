#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	union GfxImageSemanticSpecific {
		float atlas_fps_;						// 0x0000
		std::uint32_t albedo_map_scale_bias_;	// 0x0000
		std::uint32_t normal_map_scale_bias_;	// 0x0000
		std::uint32_t max_mip_map_;				// 0x0000
	};
	ENGINE_ASSERT_SZ(GfxImageSemanticSpecific, 0x0004);
}
