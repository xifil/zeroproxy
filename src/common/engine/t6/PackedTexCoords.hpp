#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	union PackedTexCoords {
		std::uint32_t packed_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(PackedTexCoords, 0x0004);
}
