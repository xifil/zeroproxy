#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class XModelLodInfo {
	public:
		float dist_;				// 0x0000
		std::uint16_t num_surfs_;	// 0x0004
		std::uint16_t surf_index_;	// 0x0006
		int part_bits_[5];			// 0x0008
	};
	ENGINE_ASSERT_SZ(XModelLodInfo, 0x001C);
}
