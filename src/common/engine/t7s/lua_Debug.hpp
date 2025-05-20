#pragma once
#include "engine/engine_common.hpp"

namespace t7s {
	class lua_Debug {
	public:
		int event_;				// 0x0000
	private:
		char pad_0004[0x0004];	// 0x0004
	public:
		const char* name_;		// 0x0008
		const char* name_what_;	// 0x0010
		const char* what_;		// 0x0018
		const char* source_;	// 0x0020
		int current_line_;		// 0x0028
		int n_ups_;				// 0x002C
		int n_params_;			// 0x0030
		int is_hks_func_;		// 0x0034
		int line_defined_;		// 0x0038
		int last_line_defined_;	// 0x003C
		char short_src_[512];	// 0x0040
		int callstack_level_;	// 0x0240
		int is_tail_call_;		// 0x0244
	};
	ENGINE_ASSERT_SZ(lua_Debug, 0x0248);
}
