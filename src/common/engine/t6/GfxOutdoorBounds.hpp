#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec3_t.hpp"

namespace t6 {
	class GfxOutdoorBounds {
	public:
		vec3_t bounds_[2];	// 0x0000
	};
	ENGINE_ASSERT_SZ(GfxOutdoorBounds, 0x0018);
}
