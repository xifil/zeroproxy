#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class InternStringArray {
	public:
		std::uint32_t size_;	// 0x0000
	private:
		char pad_0004[0x0004];	// 0x0004
	public:
		InternString** data_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(InternStringArray, 0x0010);
}
