#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class FontIconAlias {
	public:
		int alias_hash_;	// 0x0000
		int button_hash_;	// 0x0004
	};
	ENGINE_ASSERT_SZ(FontIconAlias, 0x0008);
}
