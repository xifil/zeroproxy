#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class KerningPairs {
	public:
		std::uint16_t first_;	// 0x0000
		std::uint16_t second_;	// 0x0002
		int kern_amount_;		// 0x0004
	};
	ENGINE_ASSERT_SZ(KerningPairs, 0x0008);
}
