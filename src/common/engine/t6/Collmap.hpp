#pragma once
#include "engine/engine_common.hpp"
#include "engine/t6/PhysGeomList.hpp"

namespace t6 {
	class Collmap {
	public:
		PhysGeomList* geom_list_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(Collmap, 0x0004);
}
