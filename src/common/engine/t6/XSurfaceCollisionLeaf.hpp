#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class XSurfaceCollisionLeaf {
	public:
		std::uint16_t triangle_begin_index_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(XSurfaceCollisionLeaf, 0x0002);
}
