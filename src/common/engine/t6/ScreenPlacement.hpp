#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/vec2_t.hpp"

namespace t6 {
	class ScreenPlacement {
	public:
		vec2_t scale_virtual_to_real_;	// 0x0000
		vec2_t scale_virtual_to_full_;	// 0x0008
		vec2_t scale_real_to_virtual_;	// 0x0010
		vec2_t virtual_viewable_min_;	// 0x0018
		vec2_t virtual_viewable_max_;	// 0x0020
		vec2_t virtual_tweakable_min_;	// 0x0028
		vec2_t virtual_tweakable_max_;	// 0x0030
		vec2_t real_viewport_base_;		// 0x0038
		vec2_t real_viewport_size_;		// 0x0040
		vec2_t real_viewport_mid_;		// 0x0048
		vec2_t real_viewable_min_;		// 0x0050
		vec2_t real_viewable_max_;		// 0x0058
		vec2_t real_tweakable_min_;		// 0x0060
		vec2_t real_tweakable_max_;		// 0x0068
		vec2_t sub_screen_;				// 0x0070
		float hud_splitscreen_scale_;	// 0x0078
	};
	ENGINE_ASSERT_SZ(ScreenPlacement, 0x007C);
}
