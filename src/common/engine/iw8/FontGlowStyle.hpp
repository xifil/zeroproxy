#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/vec2_t.hpp"
#include "engine/iw8/vec4_t.hpp"

namespace iw8 {
	class FontGlowStyle {
	public:
		float glow_min_distance_;			// 0x0000
		float glow_max_distance_;			// 0x0004
		vec2_t glow_uv_offset_;				// 0x0008
		vec4_t glow_color_;					// 0x0010
		float outline_glow_min_distance_;	// 0x0020
		float outline_glow_max_distance_;	// 0x0024
		vec4_t outline_glow_color_;			// 0x0028
	};
	ENGINE_ASSERT_SZ(FontGlowStyle, 0x0038);
}
