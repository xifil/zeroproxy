#pragma once
#include "engine/engine_common.hpp"

namespace iw8 {
	class GfxImageFallback {
	public:
		std::uint8_t* pixels_;	// 0x0000
		std::uint32_t size_;	// 0x0008
		std::uint16_t width_;	// 0x000C
		std::uint16_t height_;	// 0x000E
	};
	ENGINE_ASSERT_SZ(GfxImageFallback, 0x0010);
}
