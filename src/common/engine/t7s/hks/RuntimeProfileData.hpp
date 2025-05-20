#pragma once
#include "engine/engine_common.hpp"
#include "engine/t7s/hks/RuntimeProfileData_Stats.hpp"

namespace t7s::hks {
	class RuntimeProfileData {
	public:
		std::int64_t stack_depth_;							// 0x0000
		std::int64_t callback_depth_;						// 0x0008
		std::uint64_t last_timer_;							// 0x0010
		RuntimeProfileData_Stats frame_stats_;				// 0x0018
		std::uint64_t gc_start_time_;						// 0x0068
		std::uint64_t finalizer_start_time_;				// 0x0070
		std::uint64_t compiler_start_time_;					// 0x0078
		std::uint64_t compiler_start_gc_time_;				// 0x0080
		std::uint64_t compiler_start_gc_finalizer_time_;	// 0x0088
		std::uint64_t compiler_callback_start_;				// 0x0090
		std::int64_t compiler_depth_;						// 0x0098
		void* out_file_;									// 0x00A0
		lua_State* root_state_;								// 0x00A8
	};
	ENGINE_ASSERT_SZ(RuntimeProfileData, 0x00B0);
}
