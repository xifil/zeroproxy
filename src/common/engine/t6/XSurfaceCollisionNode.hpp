#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/XSurfaceCollisionAabb.hpp"

namespace t6 {
	class XSurfaceCollisionNode {
	public:
		XSurfaceCollisionAabb aabb_;		// 0x0000
		std::uint16_t child_begin_index_;	// 0x000C
		std::uint16_t child_count_;			// 0x000E
	};
	ENGINE_ASSERT_SZ(XSurfaceCollisionNode, 0x0010);
}
