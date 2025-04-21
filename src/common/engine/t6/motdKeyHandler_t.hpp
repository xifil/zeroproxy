#pragma once
#include "engine/engine_common.hpp"

namespace t6 {
	class motdKeyHandler_t {
	public:
		const char* key_;			// 0x0000
		bool(__cdecl* handler_)();	// 0x0004
	};
	ENGINE_ASSERT_SZ(motdKeyHandler_t, 0x0008);
}
