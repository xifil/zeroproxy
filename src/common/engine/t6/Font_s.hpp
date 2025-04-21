#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/Glyph.hpp"
#include "engine/t6/KerningPairs.hpp"
#include "engine/t6/Material.hpp"

namespace t6 {
	class Font_s {
	public:
		const char* font_name_;			// 0x0000
		int pixel_height_;				// 0x0004
		int is_scaling_allowed_;		// 0x0008
		int glyph_count_;				// 0x000C
		int kerning_pairs_allowed_;		// 0x0010
		Material* material_;			// 0x0014
		Material* glow_material_;		// 0x0018
		Glyph* glyphs_;					// 0x001C
		KerningPairs* kerning_pairs_;	// 0x0020
	};
	ENGINE_ASSERT_SZ(Font_s, 0x0024);
}
