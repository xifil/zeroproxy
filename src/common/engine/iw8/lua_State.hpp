#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/GCRef.hpp"
#include "engine/iw8/MRef.hpp"
#include "engine/iw8/TValue.hpp"

namespace iw8 {
	class lua_State {
	public:
		GCRef next_gc_;				// 0x0000
		std::uint8_t marked_;		// 0x0008
		std::uint8_t gct_;			// 0x0009
		std::uint8_t dummy_ffid_;	// 0x000A
		std::uint8_t status_;		// 0x000B
	private:
		char pad_000C[0x0004];		// 0x000C
	public:
		MRef gl_ref_;				// 0x0010
		GCRef gc_list_;				// 0x0018
		TValue* base_;				// 0x0020
		TValue* top_;				// 0x0028
		MRef max_stack_;			// 0x0030
		MRef stack_;				// 0x0038
		GCRef open_up_val_;			// 0x0040
		GCRef env_;					// 0x0048
		void* c_frame_;				// 0x0050
		std::uint32_t stack_size_;	// 0x0058
	private:
		char pad_005C[0x0004];		// 0x005C
	};
	ENGINE_ASSERT_SZ(lua_State, 0x0060);
}
