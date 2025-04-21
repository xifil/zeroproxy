#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/BrushWrapper.hpp"
#include "engine/t6/vec3_t.hpp"

namespace t6 {
	class PhysGeomInfo {
	public:
		BrushWrapper* brush_;	// 0x0000
		int type_;				// 0x0004
		vec3_t orientation_[3];	// 0x0008
		vec3_t offset_;			// 0x002C
		vec3_t half_lengths_;	// 0x0038
	};
	ENGINE_ASSERT_SZ(PhysGeomInfo, 0x0044);
}
