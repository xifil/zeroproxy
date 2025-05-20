#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	class Instruction {
	public:
		std::uint32_t code_;	// 0x0000
	};
	ENGINE_ASSERT_SZ(Instruction, 0x0004);
}
