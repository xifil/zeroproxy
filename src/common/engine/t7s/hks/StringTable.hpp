#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/StringPinner.hpp"

namespace t7s::hks {
	class StringTable {
	public:
		InternString** data_;			// 0x0000
		std::uint32_t count_;			// 0x0008
		std::uint32_t mask_;			// 0x000C
		StringPinner* pinned_strings_;	// 0x0010
	};
	ENGINE_ASSERT_SZ(StringTable, 0x0018);
}
