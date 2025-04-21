#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec3_t.hpp"

namespace t6 {
	class XBoneInfo {
	public:
		vec3_t bounds_[2];		// 0x0000
		vec3_t offset_;			// 0x0018
		float radius_squared_;	// 0x0024
		std::uint8_t coll_map_;	// 0x0028
	private:
		char pad_0029[0x0003];	// 0x0029
	};
	ENGINE_ASSERT_SZ(XBoneInfo, 0x002C);
}
