#pragma once
#include "engine/engine_common.hpp"
#include "engine/iw8/lua_State.hpp"

namespace iw8 {
	class luaL_Reg {
	public:
		const char* name_;					// 0x0000
		int(__fastcall* func_)(lua_State*);	// 0x0008
	};
	ENGINE_ASSERT_SZ(luaL_Reg, 0x0010);
}
