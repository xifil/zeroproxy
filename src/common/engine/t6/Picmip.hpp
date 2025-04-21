#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class Picmip {
	public:
		std::uint8_t platform_[2];	// 0x0000
	};
	ENGINE_ASSERT_SZ(Picmip, 0x0002);
}
