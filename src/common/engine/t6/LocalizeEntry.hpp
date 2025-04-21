#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class LocalizeEntry {
	public:
		const char* value_;	// 0x0000
		const char* name_;	// 0x0004
	};
	ENGINE_ASSERT_SZ(LocalizeEntry, 0x0008);
}
