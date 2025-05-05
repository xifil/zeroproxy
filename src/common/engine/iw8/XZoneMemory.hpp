#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/XZoneMemoryAllocation.hpp"

namespace iw8 {
	class XZoneMemory {
	public:
		XZoneMemoryAllocation alloc_[6];		// 0x0000
		XZoneTemporaryLoadData* temp_data_;		// 0x0090
		std::uint32_t dev_patch_mem_savings_;	// 0x0098
		std::uint32_t patch_mem_savings_;		// 0x009C
	};
	ENGINE_ASSERT_SZ(XZoneMemory, 0x00A0);
}
