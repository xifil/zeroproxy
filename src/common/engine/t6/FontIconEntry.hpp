#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/FontIconName.hpp"
#include "engine/t6/Material.hpp"

namespace t6 {
	class FontIconEntry {
	public:
		FontIconName font_icon_name_;			// 0x0000
		Material* font_icon_material_handle_;	// 0x0008
		int font_icon_size_;					// 0x000C
		float scale_x_;							// 0x0010
		float scale_y_;							// 0x0014
	};
	ENGINE_ASSERT_SZ(FontIconEntry, 0x0018);
}
