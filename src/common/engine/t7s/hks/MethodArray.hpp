#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class MethodArray {
	public:
		std::uint32_t size_;	// 0x0000
	private:
		char pad_0004[0x0004];	// 0x0004
	public:
		Method** data_;			// 0x0008
	};
	ENGINE_ASSERT_SZ(MethodArray, 0x0010);
}
