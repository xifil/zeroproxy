#pragma once
#include "engine/engine_common.hpp"

namespace iw4 {
	class Font_s {
	public:
		const char* font_name_;		// 0x0000
		int pixel_height_;			// 0x0008
		int glyph_count_;			// 0x000C
	private:
		char pad_0010[0x0018];		// 0x0010
	};
	ENGINE_ASSERT_SZ(Font_s, 0x0028);
}
