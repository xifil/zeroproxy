#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class CardMemory {
	public:
		int platform_[2];	// 0x0000
	};
	ENGINE_ASSERT_SZ(CardMemory, 0x0008);
}
