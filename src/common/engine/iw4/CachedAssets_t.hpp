#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw4/Font_s.hpp"

namespace iw4 {
	class CachedAssets_t {
	public:
		Material* scroll_bar_arrow_up_;
		Material* scroll_bar_arrow_down_;
		Material* scroll_bar_arrow_left_;
		Material* scroll_bar_arrow_right_;
		Material* scroll_bar_;
		Material* scroll_bar_thumb_;
		Material* slider_bar_;
		Material* slider_thumb_;
		Material* white_material_;
		Material* cursor_;
		Material* text_decode_characters_;
		Material* text_decode_characters_glow_;
		Font_s* big_font_;
		Font_s* small_font_;
		Font_s* console_font_;
		Font_s* bold_font_;
		Font_s* text_font_;
		Font_s* extra_big_font_;
		Font_s* objective_font_;
		Font_s* hud_big_font_;
		Font_s* hud_small_font_;
	};
	ENGINE_ASSERT_SZ(CachedAssets_t, 0x00A8);
}
