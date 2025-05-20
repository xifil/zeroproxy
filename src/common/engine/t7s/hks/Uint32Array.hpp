#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class Uint32Array {
	public:
		std::uint32_t size_;	// 0x0000
	private:
		char pad_0004[0x0004];	// 0x0004
	public:
		std::uint32_t* data_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(Uint32Array, 0x0010);
}
