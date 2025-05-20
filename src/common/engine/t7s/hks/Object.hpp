#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/Value.hpp"

namespace t7s::hks {
	class Object {
	public:
		std::uint32_t t_;	// 0x0000
		Value v_;			// 0x0008
	};
	ENGINE_ASSERT_SZ(Object, 0x0010);
}
