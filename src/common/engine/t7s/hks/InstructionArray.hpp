#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/Instruction.hpp"

namespace t7s::hks {
	class InstructionArray {
	public:
		std::uint32_t size_;		// 0x0000
	private:
		char pad_0004[0x0004];		// 0x0004
	public:
		const Instruction* data_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(InstructionArray, 0x0010);
}
