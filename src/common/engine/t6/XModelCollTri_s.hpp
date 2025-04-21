#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec4_t.hpp"

namespace t6 {
	class XModelCollTri_s {
		vec4_t plane_;	// 0x0000
		vec4_t s_vec_;	// 0x0010
		vec4_t t_vec_;	// 0x0020
	};
	ENGINE_ASSERT_SZ(XModelCollTri_s, 0x0030);
}
