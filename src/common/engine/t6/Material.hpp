#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class Material {
	public:
		const char* name_;		// 0x0000
		int image_track_;		// 0x0004
		bool error_if_missing_;	// 0x0008
		int wait_time_;			// 0x000C
	};
	ENGINE_ASSERT_SZ(Material, 0x0010);
}
