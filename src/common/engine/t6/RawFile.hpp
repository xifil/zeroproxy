#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class RawFile {
	public:
		const char* name_;		// 0x0000
		int len_;				// 0x0004
		const char* buffer_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(RawFile, 0x000C);
}
