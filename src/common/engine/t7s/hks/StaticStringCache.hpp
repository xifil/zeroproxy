#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/Object.hpp"

namespace t7s::hks {
	class StaticStringCache {
	public:
		Object objects_[42];	// 0x0000
	};
	ENGINE_ASSERT_SZ(StaticStringCache, 0x02A0);
}
