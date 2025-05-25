#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class TechniqueMask {
	public:
		std::uint64_t mask_[4];	// 0x0000
	};
	ENGINE_ASSERT_SZ(TechniqueMask, 0x0020);
}
