#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	union GfxColor {
		std::uint32_t packed_;	// 0x0000
		std::uint8_t array_[4];	// 0x0000
	};
	ENGINE_ASSERT_SZ(GfxColor, 0x0004);
}
