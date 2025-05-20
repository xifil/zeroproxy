#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/LocalInfo.hpp"

namespace t7s::hks {
	class LocalInfoArray {
	public:
		std::uint32_t size_;	// 0x0000
	private:
		char pad_0004[0x0004];	// 0x0004
	public:
		LocalInfo* data_;		// 0x0008
	};
	ENGINE_ASSERT_SZ(LocalInfoArray, 0x0010);
}
