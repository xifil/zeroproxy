#pragma once
#include "engine/engine_common.hpp"

namespace t7s::hks {
	enum class Error {
		HKS_NO_ERROR = 0,
		LUA_ERRSYNTAX = -1,
		LUA_ERRFILE = -2,
		LUA_ERRRUN = -3,
		LUA_ERRMEM = -4,
		LUA_ERRERR = -5,
		HKS_THROWING_ERROR = -6,
		HKS_GC_YIELD = 1
	};
}
