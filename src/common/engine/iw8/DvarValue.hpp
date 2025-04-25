#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/vec4_t.hpp"

namespace iw8 {
	union DvarValue {
		bool enabled_;					// 0x0000
		int integer_;					// 0x0000
		std::uint32_t unsigned_int_;	// 0x0000
		std::int64_t integer64_;		// 0x0000
		std::uint64_t unsigned_int64_;	// 0x0000
		float value_;					// 0x0000
		vec4_t vector_;					// 0x0000
		const char* string_;			// 0x0000
		std::uint8_t color_[4];			// 0x0000
	};
	ENGINE_ASSERT_SZ(DvarValue, 0x0010);
}
