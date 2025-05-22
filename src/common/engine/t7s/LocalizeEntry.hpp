#pragma once
#include "engine/engine_common.hpp"

namespace t7s {
	class LocalizeEntry {
	public:
		const char* value_;	// 0x0000
		const char* name_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(LocalizeEntry, 0x0010);
}
