#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/Instruction.hpp"
#include "engine/t7s/hks/RuntimeProfilerStats.hpp"

namespace t7s::hks {
	class DebugInstance {
	public:
		int saved_objects_;										// 0x0000
		int keep_alive_objects_;								// 0x0004
		lua_State* active_state_;								// 0x0008
		lua_State* main_state_;									// 0x0010
		void* owner_;											// 0x0018
		int debugger_level_;									// 0x0020
		int stored_hook_level_;									// 0x0024
		bool clear_hook_;										// 0x0028
	private:
		char pad_0029[0x0007];									// 0x0029
	public:
		const Instruction* stored_hook_return_addr_;			// 0x0030
		int debug_step_last_line_;								// 0x0038
	private:
		char pad_003C[0x0004];									// 0x003C
	public:
		DebugInstance* next_;									// 0x0040
		const Instruction* active_pc_;							// 0x0048
		int runtime_profile_send_buffer_write_position_;		// 0x0050
	private:
		char pad_0054[0x0004];									// 0x0054
	public:
		RuntimeProfilerStats runtime_profile_send_buffer_[30];	// 0x0058
	};
	ENGINE_ASSERT_SZ(DebugInstance, 0x0508);
}
