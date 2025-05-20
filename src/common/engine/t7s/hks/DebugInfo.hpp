#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/InternStringArray.hpp"
#include "engine/t7s/hks/LocalInfoArray.hpp"
#include "engine/t7s/hks/Uint32Array.hpp"

namespace t7s::hks {
	class DebugInfo {
	public:
		std::uint32_t line_defined_;		// 0x0000
		std::uint32_t last_line_defined_;	// 0x0004
		Uint32Array line_info_;				// 0x0008
		InternStringArray upval_info_;		// 0x0018
		InternString* source_;				// 0x0028
		InternString* name_;				// 0x0030
		LocalInfoArray local_info_;			// 0x0038
	};
	ENGINE_ASSERT_SZ(DebugInfo, 0x0048);
}
