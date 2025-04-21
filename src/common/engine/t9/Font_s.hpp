#pragma once
#include "engine/engine_common.hpp"

namespace t0 {
	class Font_s {
	public:
		char name_[0x0010];	    // 0x0000
		int font_height_;		// 0x0010
	private:
		char pad_0014[0x000C];	// 0x0014
	};
	ENGINE_ASSERT_SZ(Font_s, 0x0020);
}