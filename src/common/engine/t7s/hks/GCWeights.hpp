#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class GCWeights {
	public:
		int remove_string_;				// 0x0000
		int finalize_user_data_no_mm_;	// 0x0004
		int finalize_user_data_gc_mm_;	// 0x0008
		int clean_coroutine_;			// 0x000C
		int remove_weak_;				// 0x0010
		int mark_object_;				// 0x0014
		int traverse_string_;			// 0x0018
		int traverse_user_data_;		// 0x001C
		int traverse_coroutine_;		// 0x0020
		int traverse_weak_table_;		// 0x0024
		int free_chunk_;				// 0x0028
		int sweep_traverse_;			// 0x002C
	};
	ENGINE_ASSERT_SZ(GCWeights, 0x0030);
}
