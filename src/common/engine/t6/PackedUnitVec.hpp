#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	union PackedUnitVec {
		std::uint32_t m_Packed;	// 0x0000
	};
	ENGINE_ASSERT_SZ(PackedUnitVec, 0x0004);
}
