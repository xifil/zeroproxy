#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/TTFDef.hpp"

namespace iw8 {
	class GfxFont {
	public:
		const char* font_name_;	// 0x0000
		int pixel_height_;		// 0x0008
		int ttf_count_;			// 0x000C
		TTFDef* ttf_defs_[4];	// 0x0010
	};
	ENGINE_ASSERT_SZ(GfxFont, 0x0030);
}
