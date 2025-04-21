#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec3_t.hpp"

namespace t6 {
	class cplane_s {
	public:
		vec3_t normal_;				// 0x0000
		float dist_;				// 0x000C
		std::uint8_t type_;			// 0x0010
		std::uint8_t sign_bits_;	// 0x0011
		std::uint8_t pad_[2];		// 0x0012
	};
	ENGINE_ASSERT_SZ(cplane_s, 0x0014);
}
