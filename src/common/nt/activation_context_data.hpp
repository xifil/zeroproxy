#pragma once
#include "common_core.hpp"

namespace nt {
	class activation_context_data {
	public:
		unsigned long magic_;					// 0x0000
		unsigned long header_size_;				// 0x0004
		unsigned long format_version_;			// 0x0008
		unsigned long total_size_;				// 0x000C
		unsigned long default_toc_offset_;		// 0x0010
		unsigned long extended_toc_offset_;		// 0x0014
		unsigned long assembly_roster_offset_;	// 0x0018
		unsigned long flags_;					// 0x001C
	};
	CLASS_ASSERT_SZ_64(activation_context_data, 0x0020);
}
