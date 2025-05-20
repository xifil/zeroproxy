#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/Instruction.hpp"
#include "engine/t7s/hks/Object.hpp"

namespace t7s::hks {
	class MethodCache {
	public:
		Object* consts_;				// 0x0000
		Instruction* inst_;				// 0x0008
		std::uint16_t num_registers_;	// 0x0010
		std::uint8_t flags_;			// 0x0012
		std::uint8_t num_params_;		// 0x0013
	private:
		char pad_0014[0x0004];			// 0x0014
	};
	ENGINE_ASSERT_SZ(MethodCache, 0x0018);
}
