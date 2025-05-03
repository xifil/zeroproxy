#pragma once
#include "common_core.hpp"

namespace nt {
	class system_time {
	public:
		unsigned long low_part_;	// 0x0000
		long high1_time_;			// 0x0004
		long high2_time_;			// 0x0008
	};
	CLASS_ASSERT_SZ_64(system_time, 0x000C);
}
