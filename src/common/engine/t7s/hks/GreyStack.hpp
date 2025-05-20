#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/Object.hpp"

namespace t7s::hks {
	class GreyStack {
	public:
		Object* storage_;			// 0x0000
		std::size_t num_entries_;	// 0x0008
		std::size_t num_allocated_;	// 0x0010
	};
	ENGINE_ASSERT_SZ(GreyStack, 0x0018);
}
