#pragma once
#include "engine/engine_common.hpp"

namespace t7s {
	class luaL_Reg {
	public:
		const char* name_;		// 0x0000
		lua_CFunction func_;	// 0x0008
	};
	ENGINE_ASSERT_SZ(luaL_Reg, 0x0010);
}
