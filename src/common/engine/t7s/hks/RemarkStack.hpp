#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class RemarkStack {
	public:
		HashTable** storage_;		// 0x0000
		std::size_t num_allocated_;	// 0x0008
		std::size_t num_entries_;	// 0x0010
	};
	ENGINE_ASSERT_SZ(RemarkStack, 0x0018);
}
