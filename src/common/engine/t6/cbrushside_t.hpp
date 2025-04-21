#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/cplane_s.hpp"

namespace t6 {
	class cbrushside_t {
	public:
		cplane_s* plane_;	// 0x0000
		int c_flags_;		// 0x0004
		int s_flags_;		// 0x0008
	};
	ENGINE_ASSERT_SZ(cbrushside_t, 0x000C);
}
