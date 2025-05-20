#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class LocalInfo {
	public:
		InternString* name_;	// 0x0000
		int start_pc_;			// 0x0008
		int end_pc_;			// 0x000C
	};
	ENGINE_ASSERT_SZ(LocalInfo, 0x0010);
}
