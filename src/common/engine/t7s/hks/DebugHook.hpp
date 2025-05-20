#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/Instruction.hpp"

namespace t7s::hks {
	class DebugHook {
	public:
		lua_Hook callback_;				// 0x0000
		int mask_;						// 0x0008
		int count_;						// 0x000C
		int counter_;					// 0x0010
		bool in_use_;					// 0x0014
	private:
		char pad_0015[0x0003];			// 0x0015
	public:
		const Instruction* prev_pc_;	// 0x0018
	};
	ENGINE_ASSERT_SZ(DebugHook, 0x0020);
}
