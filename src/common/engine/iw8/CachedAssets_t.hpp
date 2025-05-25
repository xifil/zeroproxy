#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GfxFont.hpp"
#include "engine/iw8/Material.hpp"

namespace iw8 {
	class CachedAssets_t {
	public:
		Material* scroll_bar_arrow_up_;			// 0x0000
		Material* scroll_bar_arrow_down_;		// 0x0008
		Material* scroll_bar_arrow_left_;		// 0x0010
		Material* scroll_bar_arrow_right_;		// 0x0018
		Material* scroll_bar_;					// 0x0020
		Material* slider_bar_;					// 0x0028
		Material* white_material_;				// 0x0030
		Material* cursor_;						// 0x0038
		Material* text_decode_characters_;		// 0x0040
		Material* text_decode_characters_glow_;	// 0x0048
		GfxFont* big_font_;						// 0x0050
		GfxFont* small_font_;					// 0x0058
		GfxFont* console_font_;					// 0x0060
		GfxFont* bold_font_;					// 0x0068
		GfxFont* text_font_;					// 0x0070
		GfxFont* extra_big_font_;				// 0x0078
		GfxFont* objective_font_;				// 0x0080
		GfxFont* hud_big_font_;					// 0x0088
		GfxFont* hud_small_font_;				// 0x0090
		GfxFont* subtitle_font_;				// 0x0098
		GfxFont* big_noto_font_;				// 0x00A0
	};
	ENGINE_ASSERT_SZ(CachedAssets_t, 0x00A8);
}
