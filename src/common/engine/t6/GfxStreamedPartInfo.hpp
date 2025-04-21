#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class GfxStreamedPartInfo {
	public:
		std::uint32_t level_count_and_size_;	// 0x0000
		std::uint32_t hash_;					// 0x0004
		std::uint16_t width_;					// 0x0008
		std::uint16_t height_;					// 0x000A
		std::uint32_t offset_ : 32;				// 0x000C.0
		std::uint32_t size_ : 28;				// 0x0010.0
		std::uint32_t ipak_index_ : 4;			// 0x0010.28
		std::uint32_t adjacent_left_ : 15;		// 0x0014.0
		std::uint32_t adjacent_right_ : 15;		// 0x0014.15
		std::uint32_t compressed_ : 1;			// 0x0014.30
		std::uint32_t valid_ : 1;				// 0x0014.31
	};
	ENGINE_ASSERT_SZ(GfxStreamedPartInfo, 0x0018);
}
