#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/cbrushside_t.hpp"
#include "engine/t6/cplane_s.hpp"
#include "engine/t6/vec3_t.hpp"

namespace t6 {
	class BrushWrapper {
	public:
		vec3_t mins_;				// 0x0000
		int contents_;				// 0x000C
		vec3_t maxs_;				// 0x0010
		std::uint32_t num_sides_;	// 0x001C
		cbrushside_t* sides_;		// 0x0020
		int axial_c_flags_[2][3];	// 0x0024
		int axial_s_flags_[2][3];	// 0x003C
		std::uint32_t num_verts_;	// 0x0054
		vec3_t* verts_;				// 0x0058
		cplane_s* planes_;			// 0x005C
	};
	ENGINE_ASSERT_SZ(BrushWrapper, 0x0060);
}
