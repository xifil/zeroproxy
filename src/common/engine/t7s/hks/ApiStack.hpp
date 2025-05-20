#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/Object.hpp"

namespace t7s::hks {
	class ApiStack {
	public:
		Object* top_;		// 0x0000
		Object* base_;		// 0x0008
		Object* alloc_top_;	// 0x0010
		Object* bottom_;	// 0x0018
	};
	ENGINE_ASSERT_SZ(ApiStack, 0x0020);
}
