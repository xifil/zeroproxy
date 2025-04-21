#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/FontIconAlias.hpp"
#include "engine/t6/FontIconEntry.hpp"

namespace t6 {
	class FontIcon {
	public:
		const char* name_;					// 0x0000
		int num_entries_;					// 0x0004
		int num_alias_entries_;				// 0x0008
		FontIconEntry* font_icon_entry_;	// 0x000C
		FontIconAlias* font_icon_alias_;	// 0x0010
	};
	ENGINE_ASSERT_SZ(FontIcon, 0x0014);
}
