#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class XSurfaceCollisionAabb {
	public:
		std::uint16_t mins_[3];	// 0x0000
		std::uint16_t maxs_[3];	// 0x0006
	};
	ENGINE_ASSERT_SZ(XSurfaceCollisionAabb, 0x000C);
}
