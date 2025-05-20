#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class RuntimeProfilerStats {
	public:
		int hks_time_;						// 0x0000
		int callback_time_;					// 0x0004
		int gc_time_;						// 0x0008
		int c_finalizer_time_;				// 0x000C
		std::int64_t heap_size_;			// 0x0010
		std::int64_t num_new_user_data_;	// 0x0018
		std::int64_t num_push_string_;		// 0x0020
	};
	ENGINE_ASSERT_SZ(RuntimeProfilerStats, 0x0028);
}
