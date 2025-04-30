#pragma once
#include "engine/engine_common.hpp"
#include "engine/t9/DvarValue.hpp"

namespace t9 {
	class DvarData {
	public:
		DvarValue current_;	// 0x0000
		DvarValue latched_;	// 0x0020
		DvarValue reset_;	// 0x0040
	};
	ENGINE_ASSERT_SZ(DvarData, 0x0060);
}
