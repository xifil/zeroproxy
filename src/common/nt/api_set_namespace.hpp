#pragma once
#include "common_core.hpp"

namespace nt {
	class api_set_namespace {
	public:
		unsigned long version_;			// 0x0000
		unsigned long size_;			// 0x0004
		unsigned long flags_;			// 0x0008
		unsigned long count_;			// 0x000C
		unsigned long entry_offset_;	// 0x0010
		unsigned long hash_offset_;		// 0x0014
		unsigned long hash_factor_;		// 0x0018
	};
	CLASS_ASSERT_SZ_64(api_set_namespace, 0x001C);
}
