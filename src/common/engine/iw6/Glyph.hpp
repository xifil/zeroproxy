#pragma once
#include "engine/engine_common.hpp"

namespace iw6 {
	class Glyph {
	public:
		unsigned short letter_;	// 0x0000
		char x0_;				// 0x0002
		char y0_;				// 0x0003
		char dx_;				// 0x0004
		char pixel_width_;		// 0x0005
		char pixel_height_;		// 0x0006
	private:
		char pad_0007[0x0001];	// 0x0007
	public:
		float s0_;				// 0x0008
		float t0_;				// 0x000C
		float s1_;				// 0x0010
		float t1_;				// 0x0014
	};
	ENGINE_ASSERT_SZ(Glyph, 0x0018);
}
