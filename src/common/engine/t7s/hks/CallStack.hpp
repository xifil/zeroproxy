#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/Instruction.hpp"
#include "engine/t7s/hks/Object.hpp"

namespace t7s::hks {
	class CallStack {
	public:
		class ActivationRecord {
		public:
			Object* base_;						// 0x0000
			const Instruction* return_address_;	// 0x0008
			std::uint16_t tail_call_depth_;		// 0x0010
			std::uint16_t num_varargs_;			// 0x0012
			int num_expected_returns_;			// 0x0014
		};
		ENGINE_ASSERT_SZ(ActivationRecord, 0x0018);

		ActivationRecord* records_;				// 0x0000
		ActivationRecord* last_record_;			// 0x0008
		ActivationRecord* current_;				// 0x0010
		const Instruction* current_lua_pc_;		// 0x0018
		const Instruction* hook_return_addr_;	// 0x0020
		int hook_level_;						// 0x0028
	private:
		char pad_002C[0x0004];					// 0x002C
	};
	ENGINE_ASSERT_SZ(CallStack, 0x0030);
}
