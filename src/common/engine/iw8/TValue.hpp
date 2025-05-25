#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GCRef.hpp"

namespace iw8 {
	union TValue {
		std::uint64_t u64_;		// 0x0000
		long double n_;			// 0x0000
		GCRef gcr_;				// 0x0000
		std::int64_t it64_;		// 0x0000
		struct {
			int i_;				// 0x0000
			std::uint32_t it_;	// 0x0004
		};
		std::int64_t ftsz_;		// 0x0000
		struct {
			std::uint32_t lo_;	// 0x0000
			std::uint32_t hi_;	// 0x0004
		} u32_;
	};
	ENGINE_ASSERT_SZ(TValue, 0x0008);
}
