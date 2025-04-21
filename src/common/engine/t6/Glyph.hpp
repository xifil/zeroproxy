#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class Glyph {
	public:
		std::uint16_t letter_;		// 0x0000
		std::int8_t x0_;			// 0x0002
		std::int8_t y0_;			// 0x0003
		std::uint8_t dx_;			// 0x0004
		std::uint8_t pixel_width_;	// 0x0005
		std::uint8_t pixel_height_;	// 0x0006
	private:
		char pad_0007[0x0001];		// 0x0007
	public:
		float s0_;					// 0x0008
		float t0_;					// 0x000C
		float s1_;					// 0x0010
		float t1_;					// 0x0014
	};
	ENGINE_ASSERT_SZ(Glyph, 0x0018);
}
