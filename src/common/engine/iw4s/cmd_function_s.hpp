#pragma once
#include "engine/engine_common.hpp"

namespace iw4s {
	class cmd_function_s {
	public:
		cmd_function_s* next_;			// 0x0000
		const char* name_;				// 0x0008
		const char* auto_complete_dir_;	// 0x0010
		const char* auto_complete_ext_;	// 0x0018
		void(__fastcall* function_)();	// 0x0020
	};
	ENGINE_ASSERT_SZ(cmd_function_s, 0x28);
}
