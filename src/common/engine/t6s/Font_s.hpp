#pragma once
#include "engine/engine_common.hpp"

namespace t6s {
	class Font_s {
	public:
		const char* font_name_;			// 0x0000
		int pixel_height_;				// 0x0008
		int is_scaling_allowed_;		// 0x000C
		int glyph_count_;				// 0x0010
		int kerning_pairs_count_;		// 0x0014
		Material* material;				// 0x0018
		Material* glow_material_;		// 0x0020
		Glyph* glyphs_;					// 0x0028
		KerningPairs* kerning_pairs_;	// 0x0030
	};
	ENGINE_ASSERT_SZ(Font_s, 0x0038);
}
