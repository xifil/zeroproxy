#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class Packed128 {
	public:
		std::uint64_t p0_;	// 0x0000
		std::uint64_t p1_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(Packed128, 0x0010);
}
