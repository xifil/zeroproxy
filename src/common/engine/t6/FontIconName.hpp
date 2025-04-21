#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class FontIconName {
	public:
		const char* string_;	// 0x0000
		int hash_;				// 0x0004
	};
	ENGINE_ASSERT_SZ(FontIconName, 0x0008);
}
