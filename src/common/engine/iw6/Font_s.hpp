#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw6/Glyph.hpp"

namespace iw6 {
	class Font_s {
	public:
		const char* font_name_;		// 0x0000
		int pixel_height_;			// 0x0008
		int glyph_count_;			// 0x000C
		Material* material_;		// 0x0010
		Material* glow_material_;	// 0x0018
		Glyph* glyphs_;				// 0x0020
	};
	ENGINE_ASSERT_SZ(Font_s, 0x0028);
}
