#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/GCWeights.hpp"
#include "engine/t7s/hks/GreyStack.hpp"
#include "engine/t7s/hks/JmpBuf.hpp"
#include "engine/t7s/hks/MemoryManager.hpp"
#include "engine/t7s/hks/RemarkStack.hpp"
#include "engine/t7s/hks/ResumeStack.hpp"
#include "engine/t7s/hks/WeakStack.hpp"

namespace t7s::hks {
	class GarbageCollector {
	public:
		int target_;								// 0x0000
		int steps_left_;							// 0x0004
		int step_limit_;							// 0x0008
		GCWeights costs_;							// 0x000C
		int unit_;									// 0x003C
		JmpBuf* jump_point_;						// 0x0040
		lua_State* main_state_;						// 0x0048
		lua_State* finalizer_state_;				// 0x0050
		MemoryManager* memory_;						// 0x0058
		void* emergency_gc_memory_;					// 0x0060
		int phase_;									// 0x0068
	private:
		char pad_006C[0x0004];						// 0x006C
	public:
		ResumeStack resume_stack_;					// 0x0070
		GreyStack grey_stack_;						// 0x0080
		RemarkStack remark_stack_;					// 0x0098
		WeakStack weak_stack_;						// 0x00B0
		int finalizing_;							// 0x00C0
	private:
		char pad_00C4[0x0004];						// 0x00C4
	public:
		Object safe_table_value_;					// 0x00C8
		lua_State* start_of_state_stack_list_;		// 0x00D8
		lua_State* end_of_state_stack_list_;		// 0x00E0
		lua_State* current_state_;					// 0x00E8
		Object safe_value_;							// 0x00F0
		void* compiler_;							// 0x0100
		void* bytecode_reader_;						// 0x0108
		void* bytecode_writer_;						// 0x0110
		int pause_multiplier_;						// 0x0118
		int step_multiplier_;						// 0x011C
		std::size_t emergency_memory_size_;			// 0x0120
		bool stopped_;								// 0x0128
	private:
		char pad_0129[0x0007];						// 0x0129
	public:
		lua_CFunction gc_policy_;					// 0x0130
		std::size_t pause_trigger_memory_usage_;	// 0x0138
		int step_trigger_countdown_;				// 0x0140
		std::uint32_t string_table_index_;			// 0x0144
		std::uint32_t string_table_size_;			// 0x0148
	private:
		char pad_014C[0x0004];						// 0x014C
	public:
		UserData* last_black_ud_;					// 0x0150
		UserData* active_ud_;						// 0x0158
	};
	ENGINE_ASSERT_SZ(GarbageCollector, 0x0160);
}
