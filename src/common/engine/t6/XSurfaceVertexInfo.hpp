#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class XSurfaceVertexInfo {
	public:
		std::int16_t vert_count_[4];	// 0x0000
		std::uint16_t* verts_blend_;	// 0x0008
		float* tension_data_;			// 0x000C
	};
	ENGINE_ASSERT_SZ(XSurfaceVertexInfo, 0x0010);
}
