#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/Mem_PageRange.hpp"

namespace iw8 {
	class XZoneMemoryAllocation {
	public:
		Mem_PageRange page_range_;	// 0x0000
		std::uint8_t* alloc_;		// 0x0008
		std::uint64_t size_;		// 0x0010
	};
	ENGINE_ASSERT_SZ(XZoneMemoryAllocation, 0x0018);
}
