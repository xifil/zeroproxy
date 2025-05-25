#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class GfxImageAtlasSize {
	public:
		std::uint8_t row_count_;	// 0x0000
		std::uint8_t col_count_;	// 0x0001
	};
	ENGINE_ASSERT_SZ(GfxImageAtlasSize, 0x0002);
}
