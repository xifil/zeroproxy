#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class XBlock {
	public:
		std::uint8_t* data_;	// 0x0000
		std::uint32_t size_;	// 0x0004
	};
	ENGINE_ASSERT_SZ(XBlock, 0x0008);
}
