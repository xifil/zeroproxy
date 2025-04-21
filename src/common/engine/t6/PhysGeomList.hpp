#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/PhysGeomInfo.hpp"

namespace t6 {
	class PhysGeomList {
	public:
		std::uint32_t count_;	// 0x0000
		PhysGeomInfo* geoms_;	// 0x0004
		int contents_;			// 0x0008
	};
	ENGINE_ASSERT_SZ(PhysGeomList, 0x000C);
}
