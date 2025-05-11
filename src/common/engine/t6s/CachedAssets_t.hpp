#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6s/Font_s.hpp"

namespace t6s {
	namespace sp {
		class CachedAssets_t {
		public:
			Material* scroll_bar_arrow_up_;		// 0x0000
			Material* scroll_bar_arrow_down_;	// 0x0008
			Material* scroll_bar_arrow_left_;	// 0x0010
			Material* scroll_bar_arrow_right_;	// 0x0018
			Material* scroll_bar_;				// 0x0020
			Material* scroll_bar_thumb_;		// 0x0028
			Material* slider_bar_;				// 0x0030
			Material* slider_thumb_;			// 0x0038
			Material* white_material_;			// 0x0040
			Material* cursor_;					// 0x0048
			Material* dvar_list_arrow_left_;	// 0x0050
			Material* dvar_list_arrow_right_;	// 0x0058
		private:
			char pad_0060[0x0008];				// 0x0060
		public:
			Font_s* big_font_;					// 0x0068
			Font_s* small_font_;				// 0x0070
			Font_s* console_font_;				// 0x0078
			Font_s* bold_font_;					// 0x0080
			Font_s* text_font_;					// 0x0088
			Font_s* extra_big_font_;			// 0x0090
			Font_s* extra_small_font_;			// 0x0098
			Font_s* fx_font_;					// 0x00A0
			SndAliasList* item_focus_sound_;	// 0x00A8
		};
		ENGINE_ASSERT_SZ(CachedAssets_t, 0x00B0);
	}

	class CachedAssets_t {
	public:
		Material* scroll_bar_arrow_up_;		// 0x0000
		Material* scroll_bar_arrow_down_;	// 0x0008
		Material* scroll_bar_arrow_left_;	// 0x0010
		Material* scroll_bar_arrow_right_;	// 0x0018
		Material* scroll_bar_;				// 0x0020
		Material* scroll_bar_thumb_;		// 0x0028
		Material* slider_bar_;				// 0x0030
		Material* slider_thumb_;			// 0x0038
		Material* white_material_;			// 0x0040
		Material* cursor_;					// 0x0048
		Material* dvar_list_arrow_left_;	// 0x0050
		Material* dvar_list_arrow_right_;	// 0x0058
		Material* line_;					// 0x0060
		Material* blur_;					// 0x0068
		Material* line_graph_;				// 0x0070
		Font_s* big_font_;					// 0x0078
		Font_s* small_font_;				// 0x0080
		Font_s* console_font_;				// 0x0088
		Font_s* bold_font_;					// 0x0090
		Font_s* text_font_;					// 0x0098
		Font_s* extra_big_font_;			// 0x00A0
		Font_s* extra_small_font_;			// 0x00A8
		Font_s* fx_font_;					// 0x00B0
		SndAliasList* item_focus_sound_;	// 0x00B8
	};
	ENGINE_ASSERT_SZ(CachedAssets_t, 0x00C0);
}
