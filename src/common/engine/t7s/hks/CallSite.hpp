#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/JmpBuf.hpp"

namespace t7s::hks {
	class CallSite {
	public:
		JmpBuf jump_buffer_;	// 0x0000
		CallSite* prev_;		// 0x0060
	};
	ENGINE_ASSERT_SZ(CallSite, 0x0068);
}
