#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class field_t {
	public:
		int cursor_;			// 0x0000
		int scroll_;			// 0x0004
		int draw_width_;		// 0x0008
		int width_in_pixels_;	// 0x000C
		float char_height_;		// 0x0010
		int fixed_size_;		// 0x0014
		char buffer_[256];		// 0x0018
	};
	ENGINE_ASSERT_SZ(field_t, 0x0118);
}
