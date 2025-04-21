#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec3_t.hpp"
#include "engine/t6/XModelCollTri_s.hpp"

namespace t6 {
	class XModelCollSurf_s {
	public:
		XModelCollTri_s* coll_tris_;	// 0x0000
		int num_coll_tris_;				// 0x0004
		vec3_t mins_;					// 0x0008
		vec3_t maxs_;					// 0x0014
		int bone_idx_;					// 0x0020
		int contents_;					// 0x0024
		int surf_flags_;				// 0x0028
	};
	ENGINE_ASSERT_SZ(XModelCollSurf_s, 0x002C);
}
