#pragma once
#include "engine/engine_common.hpp"

namespace t7s {
	class LUIPoolUserData {
	public:
		std::uint16_t pool_index_;	// 0x0000
		std::uint16_t iteration_;	// 0x0002
	};
	ENGINE_ASSERT_SZ(LUIPoolUserData, 0x0004)
}
