#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class cmd_function_s {
	public:
		cmd_function_s* next_;			// 0x0000
		const char* name_;				// 0x0004
		const char* auto_complete_dir_;	// 0x0008
		const char* auto_complete_ext_;	// 0x000C
		void(__cdecl* function_)();		// 0x0010
	};
	ENGINE_ASSERT_SZ(cmd_function_s, 0x0014);
}
